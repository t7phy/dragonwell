#ifndef Analysis_treeDrawThread_h
#define Analysis_treeDrawThread_h

#include "RootCommon.h"

using namespace std;

void* ThreadTreeDrawLinker(void* arg);

class TreeDrawMacro
{
 public:

 TH1D* h1;
 TH2D* h2;
 bool is1D = false;
 bool is2D = false;

 TFile* file;
 TTree* tree;

 TString VarName;
 TString VarNameX;
 TString VarNameY;

 TString FlowInfo = "";
 TString WeightInfo = "";

 TreeDrawMacro(){
   //ROOT::EnableThreadSafety();
   //TDirectory::AddDirectory(kFALSE);
   //TH1::AddDirectory(kFALSE);
 };

 virtual ~TreeDrawMacro(){
   //delete tree;
   file->Close("R");
   delete file;
 }

 void DefineHist(TString name, TString title, int nbin, double left, double right){
   h1 = new TH1D(name, title, nbin, left, right);
   h1->Sumw2();
   is1D = true;
 }

 void DefineHist(TString name, TString title, int nbin, double* xbins){
   h1 = new TH1D(name, title, nbin, xbins);
   h1->Sumw2();
   is1D = true;
 }

 void DefineHist(TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty){
   h2 = new TH2D(name, title, nbinx, leftx, rightx, nbiny, lefty, righty);
   h2->Sumw2();
   is2D = true;
 }

 void DefineHist(TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins){
   h2 = new TH2D(name, title, nbinx, xbins, nbiny, ybins);
   h2->Sumw2();
   is2D = true;
 }

 void InputVariableName(TString name){
   VarName = name;
   is1D = true;
 }

 void InputVariableName(TString namex, TString namey){
   VarNameX = namex;
   VarNameY = namey;
   is2D = true;
 }

 void InputWeightInfo(TString info){WeightInfo = info;}

 void TreeDraw(){
   if(is1D) FlowInfo = VarName + ">>" + h1->GetName();
   if(is2D) FlowInfo = VarNameY + ":" + VarNameX + ">>" + h2->GetName();

   tree->Draw(FlowInfo, WeightInfo, "goff");
 }

 void Initialize(TString FileName, TString TreeName){
   file = new TFile(FileName);
   tree = (TTree *)file->Get(TreeName);
 }

 TH1D* GetHist1DPtr(){return h1;}
 TH2D* GetHist2DPtr(){return h2;}
};

class TreeDrawThread
{
 public:

 int nFiles = 0;
 vector<TString> RootNames;
 TString TreeName;

 vector<TreeDrawMacro *> TreeDrawVector = {};
 vector<pthread_t> threadTreeDraw = {};

 TH1D* FinalHist1D;
 TH2D* FinalHist2D;

 bool is1D = false;
 bool is2D = false;

 TString VarName;
 TString VarNameX;
 TString VarNameY;

 vector<TString> WeightInfos;

 TreeDrawThread(){
   //ROOT::EnableThreadSafety();
   //TDirectory::AddDirectory(kFALSE);
   //TH1::AddDirectory(kFALSE);
 };

 void InputFile(vector<TString> RootNames, TString TreeName){
   this->RootNames = RootNames;
   nFiles = this->RootNames.size();
   this->TreeName = TreeName;

   TreeDrawVector.resize(RootNames.size());
   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i) = new TreeDrawMacro();
     TreeDrawVector.at(i)->Initialize(RootNames.at(i), TreeName);
   }

 }

 void DefineHist(TString name, TString title, int nbin, double left, double right){
   FinalHist1D = new TH1D(name, title, nbin, left, right);
   is1D = true;

   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->DefineHist(name + "_" + i, title + "_" + i, nbin, left, right);
   }
 }

 void DefineHist(TString name, TString title, int nbin, double* xbins){
   FinalHist1D = new TH1D(name, title, nbin, xbins);
   is1D = true;

   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->DefineHist(name + "_" + i, title + "_" + i, nbin, xbins);
   }
 }

 void DefineHist(TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty){
   FinalHist2D = new TH2D(name, title, nbinx, leftx, rightx, nbiny, lefty, righty);
   is2D = true;

   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->DefineHist(name + "_" + i, title + "_" + i, nbinx, leftx, rightx, nbiny, lefty, righty);
   }
 }

 void DefineHist(TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins){
   FinalHist2D = new TH2D(name, title, nbinx, xbins, nbiny, ybins);
   is2D = true;

   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->DefineHist(name + "_" + i, title + "_" + i, nbinx, xbins, nbiny, ybins);
   }
 }

 void InputVariableName(TString name){
   VarName = name;
   is1D = true;
   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->InputVariableName(name);
   }
 }

 void InputVariableName(TString namex, TString namey){
   VarNameX = namex;
   VarNameY = namey;
   is2D = true;
   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->InputVariableName(namex, namey);
   }
 }

 void InputWeightInfo(vector<TString> info){
   WeightInfos = info;
   for(int i = 0; i < TreeDrawVector.size(); i++){
     TreeDrawVector.at(i)->InputWeightInfo(info.at(i));
   }
 }

 void SubmitTreeDrawJobs();
 void WaitTreeDrawJobs();
 void GetFinalHist();

};
#endif
