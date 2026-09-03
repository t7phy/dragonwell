#ifndef _MAKE_HISTS_H_
#define _MAKE_HISTS_H_
#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "Tools/LatexOutput.h"
#include "SpecialHist/AngularFunction.h"
#include "SpecialHist/BkgHist.h"
#include "SpecialHist/FakeHist.h"
#include "SpecialHist/CovHist.h"
#include "SpecialHist/MultiBinHist.h"
#include "SpecialHist/ResolutionHist.h"
#include "SpecialHist/SysHist.h"
#include "SpecialHist/MultiWeightHist.h"

using namespace std;

template<class T1>
class ThreadHist
{
 public:

 int TotalThread;

 vector<T1> HistVector;

 ThreadHist(int TotalThread){
   this->TotalThread = TotalThread;
   HistVector.resize(TotalThread);
 }

 T1 HistPtr(int iThread){
   return HistVector.at(iThread);
 }

 T1 at(int iThread){
   return HistVector.at(iThread);
 }

 virtual void Merge(){
   for(int i = 1; i < TotalThread; i++){
     HistVector.at(0)->Add(HistVector.at(i));
   }
 }

 virtual void Reset(){
   for(int i = 0; i < TotalThread; i++){
     HistVector.at(i)->Reset();
   }
 }

 virtual void Save(){
   HistVector.at(0)->Write();
 }

};


class makeHists
{
 public:

 int TotalThread;
 TString subName = "";

 ThreadHist<TH1D *>* h1;
 ThreadHist<TH2D *>* h2;

 vector<ThreadHist<TH1D *> *> hist_1d;
 vector<ThreadHist<TH2D *> *> hist_2d;
 vector<ThreadHist<TH3D *> *> hist_3d;
 vector<ThreadHist<AngularFunction *> *> hist_angular;
 vector<ThreadHist<BkgHist *> *> BkgHist_1d;
 vector<ThreadHist<FakeHist *> *> FakeHist_1d;
 vector<ThreadHist<CovHist *> *> CovHist_1d;
 vector<ThreadHist<MultiBinHist *> *> MultiBinHist_1d;
 vector<ThreadHist<ResolutionHist *> *> ResolutionHist_1d;
 vector<ThreadHist<SysHist *> *> SysHist_1d;
 vector<ThreadHist<MultiWeightHist *> *> MultiWeightHist_1d;

 bool HaveMerged = false;
 bool isSaveCustomFakePlot = false;

 makeHists(){};
 makeHists(int TotalThread){this->TotalThread = TotalThread;};

 virtual void BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx);
 virtual void BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double* xbins);
 virtual void Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty, int nbinz, double leftz, double rightz);
 virtual void Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins, int nbinz, double* zbins);

 virtual void BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double leftx, double rightx);
 virtual void BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double* xbins);
 virtual void BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double* xbins, int nbiny, double* ybins);
 virtual void BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double* xbins, int nbiny, double* ybins, int nbinz, double* zbins);

 virtual void BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double leftx, double rightx);
 virtual void BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double* xbins);
 virtual void BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);
 virtual void BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);

 virtual void BookFakeHist(ThreadHist<FakeHist *>* &h, TString name, TString title, int nbinx, double leftx, double rightx);
 virtual void BookFakeHist(ThreadHist<FakeHist *>* &h, TString name, TString title, int nbinx, double* xbins);

 virtual void BookCovHist(ThreadHist<CovHist *>* &h, TString name, TString title, int nbinx, double leftx, double rightx);

 virtual void BookMultiBinHist(ThreadHist<MultiBinHist *>* &h, vector<vector<double>> MultiBinVector, TString name, TString title, int nbinx, double* xbins);

 virtual void BookResolutionHist(ThreadHist<ResolutionHist *>* &h, TString name, TString type, int nbinx, double leftx, double rightx);

 virtual void BookSysHist(ThreadHist<SysHist *>* &h, vector<TString> sysName, TString name, TString title, int nbinx, double leftx, double rightx);

 virtual void BookMultiWeightHist(ThreadHist<MultiWeightHist *>* &h, int nWeight, TString name, TString title, int nbinx, double leftx, double rightx);

 virtual void MergeHists();
 virtual void ResetHists();
 virtual void saveHists();
 virtual void outputInformation(){};

 TString RootType;

 TFile *hf;
 virtual void openFile(const char* fName){hf = new TFile(fName, "RECREATE");};

 ofstream outputfile;
 Logstream myLog;
 virtual void LinkLog(Logstream log){this->myLog = log;}

};

#endif

