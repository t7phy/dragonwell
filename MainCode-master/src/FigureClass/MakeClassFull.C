/*
 Program for creating a Multiple-thread Loop Event Framework
 Created by Yao Fu
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLeaf.h"
#include "TLeafObject.h"
#include "TBranchObject.h"
#include "TBranchElement.h"
#include "TStreamerElement.h"
#include "TString.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 4){
   cout<<"usage: ./MakeClass rootfile treeName ClassName"<<endl;
   return 0;
 }

 ofstream LoopHeader;
 ofstream LoopSource;
 ofstream HistHeader;
 ofstream HistSource;
 ofstream TreeHeader;
 ofstream TreeSource;
 ofstream MainFunction;

 ofstream RootCommonHeader;

 ofstream LoopBasicHeader;
 ofstream LoopBasicSource;
 ofstream HistBasicHeader;
 ofstream HistBasicSource;
 ofstream ControlHeader;
 ofstream ControlSource;
 ofstream CommonHeader;
 ofstream CommonSource;

 ofstream CMakeRoot;
 ofstream CMakeSRC;
 ofstream CMakeTools;
 ofstream CMakeAnalysis;

 ofstream ToolsHeader;
 ofstream TimeSource;

 ofstream LogHeader;
 ofstream LogSource;

 ofstream MainCode;

 LoopHeader.open((TString)"loop" + (TString)argv[3] + (TString)".h");
 LoopSource.open((TString)"loop" + (TString)argv[3] + (TString)".C");
 HistHeader.open((TString)"Hists" + (TString)argv[3] + (TString)".h");
 HistSource.open((TString)"Hists" + (TString)argv[3] + (TString)".C");
 TreeHeader.open((TString)"TreeFor" + (TString)argv[3] + (TString)".h");
 TreeSource.open((TString)"TreeFor" + (TString)argv[3] + (TString)".C");
 MainFunction.open((TString)"ThreadRun" + (TString)argv[3] + (TString)".C");

 RootCommonHeader.open("RootCommon.h");
 LoopBasicHeader.open("loopMC.h");
 LoopBasicSource.open("loopMC.C");
 HistBasicHeader.open("makeHists.h");
 HistBasicSource.open("makeHists.C");
 ControlHeader.open("control.h");
 ControlSource.open("control.C");
 CommonHeader.open("Common.h");
 CommonSource.open("Common.C");
 CMakeRoot.open("CMakeLists.txt");
 CMakeSRC.open("CMakeLists.txt.src");
 CMakeTools.open("CMakeLists.txt.Tools");
 CMakeAnalysis.open("CMakeLists.txt.Analysis");
 ToolsHeader.open("Tools.h");
 TimeSource.open("GetTime.C");
 LogHeader.open("Log.h");
 LogSource.open("Log.C");
 MainCode.open("main.C");

 ////////////////
 // LoopHeader //
 ////////////////

 LoopHeader<<"#ifndef loop"<<argv[3]<<"_h"<<endl;
 LoopHeader<<"#define loop"<<argv[3]<<"_h"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"#include \"Analysis/loopMC.h\""<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"#include \"Analysis/Hists"<<argv[3]<<".h\""<<endl;
 LoopHeader<<"#include \"Analysis/TreeFor"<<argv[3]<<".h\""<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"using namespace std;"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"class loop"<<argv[3]<<" : public loopMC"<<endl;
 LoopHeader<<"{"<<endl;
 LoopHeader<<" public:"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<" Hists"<<argv[3]<<" *myhists;"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<" TreeFor"<<argv[3]<<" *"<<argv[3]<<"Tree;"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<" bool isCut = false;"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<" loop"<<argv[3]<<"(TString RootType);"<<endl;
 LoopHeader<<" virtual void InputHist(Hists"<<argv[3]<<"* &myhists);"<<endl;
 LoopHeader<<" virtual void InputTree(TreeFor"<<argv[3]<<" *"<<argv[3]<<"Tree);"<<endl;
 LoopHeader<<" virtual void ReadTree(int ifile);"<<endl;
 LoopHeader<<" virtual void End(int RootNumber);"<<endl;
 LoopHeader<<" virtual void Finish();"<<endl;
 LoopHeader<<" virtual ~loop"<<argv[3]<<"();"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"};"<<endl;
 LoopHeader<<"#endif"<<endl;

 ////////////////
 // LoopSource //
 ////////////////

 LoopSource<<"#define loop"<<argv[3]<<"_cxx"<<endl;
 LoopSource<<"#include <iostream>"<<endl;
 LoopSource<<"#include \"Analysis/loop"<<argv[3]<<".h\""<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"using namespace std;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"loop"<<argv[3]<<"::loop"<<argv[3]<<"(TString RootType)"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" this->RootType = RootType;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" Sta_TotalNumber = 0;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" isThread = false;"<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"void loop"<<argv[3]<<"::InputHist(Hists"<<argv[3]<<"* &myhists)"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" this->myhists = myhists;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"void loop"<<argv[3]<<"::InputTree(TreeFor"<<argv[3]<<" *"<<argv[3]<<"Tree)"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" this->"<<argv[3]<<"Tree = "<<argv[3]<<"Tree;"<<endl;
 LoopSource<<" this->RootNames = "<<argv[3]<<"Tree->RootNames;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" this->FirstFile = "<<argv[3]<<"Tree->FirstFile;"<<endl;
 LoopSource<<" this->EndFile = "<<argv[3]<<"Tree->EndFile;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" this->OneFilePerJob = "<<argv[3]<<"Tree->OneFilePerJob;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" for(int ifile = FirstFile; ifile < EndFile; ifile++){"<<endl;
 LoopSource<<"   TotalEntries[ifile] = "<<argv[3]<<"Tree->TotalEntries[ifile];"<<endl;
 LoopSource<<" }"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"void loop"<<argv[3]<<"::ReadTree(int ifile)"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){"<<endl;
 LoopSource<<"   Sta_TotalNumber++;"<<endl;
 LoopSource<<"   if(isTest) cout<<\"Thread No.\"<<iThread<<\": The No.\"<<Sta_TotalNumber<<\" event.\"<<endl;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"   if(Sta_TotalNumber % 1000000 == 0){"<<endl;
 LoopSource<<"     if(isThread) cout<<\"Thread No.\"<<iThread<<\": \"<<Sta_TotalNumber<<\" events have finished.\"<<endl;"<<endl;
 LoopSource<<"     if(!isThread) cout<<\"Condor No.\"<<iThread<<\": \"<<Sta_TotalNumber<<\" events have finished.\"<<endl;"<<endl;
 LoopSource<<"   }"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"   "<<argv[3]<<"Tree->GetEntry(ifile, iEvent);"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"   //Retrieve information from root files:"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"   /////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
 LoopSource<<"   //  Fill histograms:                                                                                       //"<<endl;
 LoopSource<<"   //                                                                                                         //"<<endl;
 LoopSource<<"   //  1d histogram example:                                                                                  //"<<endl;
 LoopSource<<"   //  myhists->ZMass->HistPtr(iThread - 1)->Fill(ZBoson.M(), Weight);                                        //"<<endl;
 LoopSource<<"   //                                                                                                         //"<<endl;
 LoopSource<<"   //  2d histogram example:                                                                                  //"<<endl;
 LoopSource<<"   //  myhists->ZMass_ZY->HistPtr(iThread - 1)->Fill(ZBoson.M(), ZBoson.Rapidity(), Weight);                  //"<<endl;
 LoopSource<<"   //                                                                                                         //"<<endl;
 LoopSource<<"   //  3d histogram example:                                                                                  //"<<endl;
 LoopSource<<"   //  myhists->ZMass_ZY_QT->HistPtr(iThread - 1)->Fill(ZBoson.M(), ZBoson.Rapidity(), ZBoson.Pt(), Weight);  //"<<endl;
 LoopSource<<"   /////////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<""<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" }"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"void loop"<<argv[3]<<"::End(int RootNumber)"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" cout<<\"Thread No.\"<<this->iThread<<\": **Running: Free Rootfile: \"<<RootNumber + 1<<endl;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" if(!"<<argv[3]<<"Tree->fChain[RootNumber])"<<endl;
 LoopSource<<"  {"<<endl;
 LoopSource<<"   cout<<\"XXXXX**Runing: BIG ERROR!!! No File loadead!\"<<endl;"<<endl;
 LoopSource<<"   return;"<<endl;
 LoopSource<<"  }"<<endl;
 LoopSource<<" delete "<<argv[3]<<"Tree->fChain[RootNumber]->GetCurrentFile();"<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"void loop"<<argv[3]<<"::Finish()"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" cout<<\"Thread No.\"<<this->iThread<<\": **Total Event Number: \"<<this->Sta_TotalNumber<<endl;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" if(EndFile == RootNames.size()) delete "<<argv[3]<<"Tree;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"loop"<<argv[3]<<"::~loop"<<argv[3]<<"()"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<"}"<<endl;

 ////////////////
 // HistHeader //
 ////////////////

 HistHeader<<"#ifndef __Hists"<<argv[3]<<"_H_"<<endl;
 HistHeader<<"#define __Hists"<<argv[3]<<"_H_"<<endl;
 HistHeader<<"#include <iostream>"<<endl;
 HistHeader<<"#include \"TH1D.h\""<<endl;
 HistHeader<<"#include \"TH2D.h\""<<endl;
 HistHeader<<"#include \"TH3D.h\""<<endl;
 HistHeader<<"#include \"TH2F.h\""<<endl;
 HistHeader<<"#include \"TH3F.h\""<<endl;
 HistHeader<<"#include \"TFile.h\""<<endl;
 HistHeader<<"#include \"TProfile.h\""<<endl;
 HistHeader<<"#include \"TProfile2D.h\""<<endl;
 HistHeader<<"#include \"TMath.h\""<<endl;
 HistHeader<<"#include \"TTree.h\""<<endl;
 HistHeader<<"#include <vector>"<<endl;
 HistHeader<<"#include \"Analysis/makeHists.h\""<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"using namespace std;"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"class Hists"<<argv[3]<<" : public makeHists"<<endl;
 HistHeader<<"{"<<endl;
 HistHeader<<" public:"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"  ////////////////////////////////////////"<<endl;
 HistHeader<<"  //  Define histograms:                //"<<endl;
 HistHeader<<"  //                                    //"<<endl;
 HistHeader<<"  //  1d histogram example:             //"<<endl;
 HistHeader<<"  //  ThreadHist<TH1D *>* ZMass;        //"<<endl;
 HistHeader<<"  //                                    //"<<endl;
 HistHeader<<"  //  2d histogram example:             //"<<endl;
 HistHeader<<"  //  ThreadHist<TH2D *>* ZMass_ZY;     //"<<endl;
 HistHeader<<"  //                                    //"<<endl;
 HistHeader<<"  //  3d histogram example:             //"<<endl;
 HistHeader<<"  //  ThreadHist<TH3D *>* ZMass_ZY_QT;  //"<<endl;
 HistHeader<<"  ////////////////////////////////////////"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<""<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"//member function"<<endl;
 HistHeader<<" Hists"<<argv[3]<<"(int TotalThread){this->TotalThread = TotalThread;};"<<endl;
 HistHeader<<" vector<TString> sysName;"<<endl;
 HistHeader<<" virtual void InitialSysName();"<<endl;
 HistHeader<<" virtual void bookHists(int TotalThread);"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"// template<class T>"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"};"<<endl;
 HistHeader<<"#endif"<<endl;

 ////////////////
 // HistSource //
 ////////////////

 HistSource<<"#include \"Analysis/Hists"<<argv[3]<<".h\""<<endl;
 HistSource<<""<<endl;
 HistSource<<"using namespace std;"<<endl;
 HistSource<<""<<endl;
 HistSource<<"void Hists"<<argv[3]<<"::bookHists(int TotalThread)"<<endl;
 HistSource<<"{"<<endl;
 HistSource<<" this->TotalThread = TotalThread;"<<endl;
 HistSource<<""<<endl;
 HistSource<<""<<endl;
 HistSource<<" //////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
 HistSource<<" //  Define histograms:                                                                              //"<<endl;
 HistSource<<" //                                                                                                  //"<<endl;
 HistSource<<" //  1d histogram example:                                                                           //"<<endl;
 HistSource<<" //  BookHist(ZMass, \"ZMass\", \"ZMass\", 100, 2000, 5000);                                             //"<<endl;
 HistSource<<" //                                                                                                  //"<<endl;
 HistSource<<" //  2d histogram example:                                                                           //"<<endl;
 HistSource<<" //  Book2DHist(ZMass_ZY, \"ZMass_ZY\", \"ZMass_ZY\", 100, 2000, 5000, 10, -5, 5);                       //"<<endl;
 HistSource<<" //                                                                                                  //"<<endl;
 HistSource<<" //  3d histogram example:                                                                           //"<<endl;
 HistSource<<" //  Book3DHist(ZMass_ZY_QT, \"ZMass_ZY_QT\", \"ZMass_ZY_QT\", 100, 2000, 5000, 10, -5, 5, 10, 0, 100);  //"<<endl;
 HistSource<<" //////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl;
 HistSource<<""<<endl;
 HistSource<<""<<endl;
 HistSource<<""<<endl;
 HistSource<<"}"<<endl;
 HistSource<<""<<endl;
 HistSource<<"void Hists"<<argv[3]<<"::InitialSysName()"<<endl;
 HistSource<<"{"<<endl;
 HistSource<<""<<endl;
 HistSource<<"}"<<endl;

 ////////////////
 // TreeHeader //
 ////////////////

 TreeHeader<<"#ifndef TreeFor"<<argv[3]<<"_h"<<endl;
 TreeHeader<<"#define TreeFor"<<argv[3]<<"_h"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"#include <TROOT.h>"<<endl;
 TreeHeader<<"#include <TChain.h>"<<endl;
 TreeHeader<<"#include <TFile.h>"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"using namespace std;"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"class TreeFor"<<argv[3]<<endl;
 TreeHeader<<"{"<<endl;
 TreeHeader<<" public :"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"   TFile *rootfile[1000];"<<endl;
 TreeHeader<<"   TTree *fChain[1000];"<<endl;
 TreeHeader<<"   long TotalEntries[1000];"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"   vector<TString> RootNames;"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"   vector<int> RootTypes;"<<endl;
 TreeHeader<<"   vector<double> CrossSections;"<<endl;
 TreeHeader<<"   vector<double> SumOfWeights;"<<endl;
 TreeHeader<<"   int nchannel;"<<endl;
 TreeHeader<<"   double CrossSection;"<<endl;
 TreeHeader<<"   double SumOfWeight;"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"   int FirstFile, EndFile;"<<endl;
 TreeHeader<<"   bool OneFilePerJob = false;"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"// Fixed size dimensions of array or collections stored in the TTree if any."<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"   // Declaration of leaf types"<<endl;

 TFile* file = new TFile(argv[1]);
 TTree* tree = (TTree *)file->Get(argv[2]);

 TObjArray *leaves = tree->GetListOfLeaves();
 Int_t nleaves = leaves ? leaves->GetEntriesFast() : 0;
 Int_t l;
 TList listOfHeaders;
 listOfHeaders.SetOwner();

 Int_t len, lenb;
 char blen[1024];
 char *bname;
 Int_t *leaflen = new Int_t[nleaves];
 TObjArray *leafs = new TObjArray(nleaves);

 TLeaf *leafcount;
 TLeafObject *leafobj;
 TBranchElement *bre=0;
 const char *headOK  = "   ";
 const char *headcom = " //";
 const char *head;
 char branchname[1024];
 char aprefix[1024];
 TObjArray branches(100);
 TObjArray mustInit(100);
 TObjArray mustInitArr(100);
 mustInitArr.SetOwner(kFALSE);
 Int_t *leafStatus = new Int_t[nleaves];
 for (l=0;l<nleaves;l++) {
//    TLeaf *leaf = (TLeaf*)leaves->UncheckedAt(l);
//    TBranch *branch = leaf->GetBranch();
//    TClass *cl = TClass::GetClass(branch->GetClassName());
//    printf("%-15s %s;\n",leaf->GetTypeName(), leaf->GetName());
//    TreeHeader<<"   "<<left<<setw(15)<<leaf->GetTypeName()<<" "<<leaf->GetName()<<";"<<endl;
    Int_t kmax = 0;
    head = headOK;
    leafStatus[l] = 0;
    TLeaf *leaf = (TLeaf*)leaves->UncheckedAt(l);
    len = leaf->GetLen(); if (len<=0) len = 1;
    leafcount =leaf->GetLeafCount();
    TBranch *branch = leaf->GetBranch();
    branchname[0] = 0;
    strlcpy(branchname,branch->GetName(),sizeof(branchname));
    strlcpy(aprefix,branch->GetName(),sizeof(aprefix));
    if (!branches.FindObject(branch)) branches.Add(branch);
    else leafStatus[l] = 1;
    if ( branch->GetNleaves() > 1) {
       // More than one leaf for the branch we need to distinguish them
       strlcat(branchname,".",sizeof(branchname));
       strlcat(branchname,leaf->GetTitle(),sizeof(branchname));
       if (leafcount) {
          // remove any dimension in title
          char *dim =  (char*)strstr(branchname,"["); if (dim) dim[0] = 0;
       }
    } else {
       strlcpy(branchname,branch->GetName(),sizeof(branchname));
    }
    char *twodim = (char*)strstr(leaf->GetTitle(),"][");
    bname = branchname;
    while (*bname) {
       if (*bname == '.') *bname='_';
       if (*bname == ',') *bname='_';
       if (*bname == ':') *bname='_';
       if (*bname == '<') *bname='_';
       if (*bname == '>') *bname='_';
       bname++;
    }
    if (branch->IsA() == TBranchObject::Class()) {
       if (branch->GetListOfBranches()->GetEntriesFast()) {leafStatus[l] = 1; continue;}
       leafobj = (TLeafObject*)leaf;
       if (!leafobj->GetClass()) {leafStatus[l] = 1; head = headcom;}
       TreeHeader<<head<<left<<setw(15)<<leafobj->GetTypeName()<<" "<<leafobj->GetName()<<";"<<endl;
       if (leafStatus[l] == 0) mustInit.Add(leafobj);
       continue;
    }
    if (leafcount) {
       len = leafcount->GetMaximum();
       if (len<=0) len = 1;
       strlcpy(blen,leafcount->GetName(),sizeof(blen));
       bname = &blen[0];
       while (*bname) {
          if (*bname == '.') *bname='_';
          if (*bname == ',') *bname='_';
          if (*bname == ':') *bname='_';
          if (*bname == '<') *bname='_';
          if (*bname == '>') *bname='_';
          bname++;
       }
       lenb = strlen(blen);
       if (blen[lenb-1] == '_') {blen[lenb-1] = 0; kmax = 1;}
       else                     snprintf(blen,sizeof(blen),"%d",len);
    }
    if (branch->IsA() == TBranchElement::Class()) {
       bre = (TBranchElement*)branch;
       if (bre->GetType() != 3 && bre->GetType() != 4
           && bre->GetStreamerType() <= 0 && bre->GetListOfBranches()->GetEntriesFast()) {
          leafStatus[l] = 0;
       }
       if (bre->GetType() == 3 || bre->GetType() == 4) {
          TreeHeader<<"   "<<left<<setw(15)<<"Int_t "<<branchname<<"_;"<<endl;
          continue;
       }
       if (bre->IsBranchFolder()) {
          TreeHeader<<"   "<<left<<setw(15)<<bre->GetClassName()<<" *"<<branchname<<";"<<endl;
          mustInit.Add(bre);
          continue;
       } else {
          if (branch->GetListOfBranches()->GetEntriesFast()) {leafStatus[l] = 1;}
       }
       if (bre->GetStreamerType() < 0) {
          if (branch->GetListOfBranches()->GetEntriesFast()) {
             TreeHeader<<headcom<<left<<setw(15)<<bre->GetClassName()<<" *"<<branchname<<";"<<endl;
          } else {
             TreeHeader<<head<<left<<setw(15)<<bre->GetClassName()<<" *"<<branchname<<";"<<endl;
             mustInit.Add(bre);
          }
          continue;
       }
       if (bre->GetStreamerType() == 0) {
          if (!TClass::GetClass(bre->GetClassName())->HasInterpreterInfo()) {leafStatus[l] = 1; head = headcom;}
          TreeHeader<<head<<left<<setw(15)<<bre->GetClassName()<<" *"<<branchname<<";"<<endl;
          if (leafStatus[l] == 0) mustInit.Add(bre);
          continue;
       }
       if (bre->GetStreamerType() > 60) {
          TClass *cle = TClass::GetClass(bre->GetClassName());
          if (!cle) {leafStatus[l] = 1; continue;}
          if (bre->GetStreamerType() == 66) leafStatus[l] = 0;
          char brename[256];
          strlcpy(brename,bre->GetName(),255);
          char *bren = brename;
          char *adot = strrchr(bren,'.');
          if (adot) bren = adot+1;
          char *brack = strchr(bren,'[');
          if (brack) *brack = 0;
          TStreamerElement *elem = (TStreamerElement*)cle->GetStreamerInfo()->GetElements()->FindObject(bren);
          if (elem) {
             if (elem->IsA() == TStreamerBase::Class()) {leafStatus[l] = 1; continue;}
               if (!TClass::GetClass(elem->GetTypeName())) {leafStatus[l] = 1; continue;}
               if (!TClass::GetClass(elem->GetTypeName())->HasInterpreterInfo()) {leafStatus[l] = 1; head = headcom;}
               //if (leafcount) fprintf(fp,"%s%-15s %s[kMax%s];\n",head,elem->GetTypeName(), branchname,blen);
               if (leafcount) TreeHeader<<head<<left<<setw(15)<<elem->GetTypeName()<<" "<<branchname<<"[kMax"<<blen<<"];"<<endl;
               //else           fprintf(fp,"%s%-15s %s;\n",head,elem->GetTypeName(), branchname);
               else           TreeHeader<<head<<left<<setw(15)<<elem->GetTypeName()<<" "<<branchname<<";"<<endl;
            } else {
               if (!TClass::GetClass(bre->GetClassName())->HasInterpreterInfo()) {leafStatus[l] = 1; head = headcom;}
               //fprintf(fp,"%s%-15s %s;\n",head,bre->GetClassName(), branchname);
               TreeHeader<<head<<left<<setw(15)<<elem->GetTypeName()<<" "<<branchname<<";"<<endl;
          }
          continue;
       }
    }
    if (strlen(leaf->GetTypeName()) == 0) {leafStatus[l] = 1; continue;}
      if (leafcount) {
         //len = leafcount->GetMaximum();
         //strlcpy(blen,leafcount->GetName(),sizeof(blen));
         //bname = &blen[0];
         //while (*bname) {if (*bname == '.') *bname='_'; bname++;}
         //lenb = strlen(blen);
         //Int_t kmax = 0;
         //if (blen[lenb-1] == '_') {blen[lenb-1] = 0; kmax = 1;}
         //else                     sprintf(blen,"%d",len);
 
         const char *stars = " ";
         if (bre && bre->GetBranchCount2()) {
            stars = "*";
         }
         // Dimensions can be in the branchname for a split Object with a fix length C array.
         // Theses dimensions HAVE TO be placed after the dimension explicited by leafcount
         TString dimensions;
         char *dimInName = (char*) strstr(branchname,"[");
         if ( twodim || dimInName ) {
            if (dimInName) {
               dimensions = dimInName;
               dimInName[0] = 0; // terminate branchname before the array dimensions.
            }
            if (twodim) dimensions += (char*)(twodim+1);
         }
         const char* leafcountName = leafcount->GetName();
         char b2len[1024];
         if (bre && bre->GetBranchCount2()) {
            TLeaf * l2 = (TLeaf*)bre->GetBranchCount2()->GetListOfLeaves()->At(0);
            strlcpy(b2len,l2->GetName(),sizeof(b2len));
            bname = &b2len[0];
            while (*bname) {
               if (*bname == '.') *bname='_';
               if (*bname == ',') *bname='_';
               if (*bname == ':') *bname='_';
               if (*bname == '<') *bname='_';
               if (*bname == '>') *bname='_';
               bname++;
            }
            leafcountName = b2len;
         }
         if (dimensions.Length()) {
            //if (kmax) fprintf(fp,"   %-14s %s%s[kMax%s]%s;   //[%s]\n",leaf->GetTypeName(), stars,
            //                  branchname,blen,dimensions.Data(),leafcountName);
            if (kmax) TreeHeader<<"   "<<left<<setw(14)<<leaf->GetTypeName()<<" "<<stars<<branchname<<"[kMax"<<blen<<"]"<<dimensions.Data()<<";   //["<<leafcountName<<"]"<<endl;
            //else      fprintf(fp,"   %-14s %s%s[%d]%s;   //[%s]\n",leaf->GetTypeName(), stars,
            //                  branchname,len,dimensions.Data(),leafcountName);
            else      TreeHeader<<"   "<<left<<setw(14)<<leaf->GetTypeName()<<" "<<stars<<branchname<<"["<<len<<"]"<<dimensions.Data()<<";   //["<<leafcountName<<"]"<<endl;
         } else {
            //if (kmax) fprintf(fp,"   %-14s %s%s[kMax%s];   //[%s]\n",leaf->GetTypeName(), stars, branchname,blen,leafcountName);
            if (kmax) TreeHeader<<"   "<<left<<setw(14)<<leaf->GetTypeName()<<" "<<stars<<branchname<<"[kMax"<<blen<<"]"<<";   //["<<leafcountName<<endl;
            //else      fprintf(fp,"   %-14s %s%s[%d];   //[%s]\n",leaf->GetTypeName(), stars, branchname,len,leafcountName);
            else      TreeHeader<<"   "<<left<<setw(14)<<leaf->GetTypeName()<<" "<<stars<<branchname<<"["<<len<<"]"<<";   //["<<leafcountName<<"]"<<endl;
         }
         if (stars[0]=='*') {
            TNamed *n;
            if (kmax) n = new TNamed(branchname, Form("kMax%s",blen));
            else n = new TNamed(branchname, Form("%d",len));
            mustInitArr.Add(n);
         }
      } else {
         if (strstr(branchname,"[")) len = 1;
         //if (len < 2) fprintf(fp,"   %-15s %s;\n",leaf->GetTypeName(), branchname);
         if (len < 2) TreeHeader<<"   "<<left<<setw(15)<<leaf->GetTypeName()<<" "<<branchname<<";"<<endl;
         else {
            //if (twodim) fprintf(fp,"   %-15s %s%s;\n",leaf->GetTypeName(), branchname,(char*)strstr(leaf->GetTitle(),"["));
            if (twodim) TreeHeader<<"   "<<left<<setw(15)<<leaf->GetTypeName()<<" "<<branchname<<(char*)strstr(leaf->GetTitle(),"[")<<";"<<endl;
            //else        fprintf(fp,"   %-15s %s[%d];\n",leaf->GetTypeName(), branchname,len);
            else        TreeHeader<<"   "<<left<<setw(15)<<leaf->GetTypeName()<<" "<<branchname<<"["<<len<<"];"<<endl;
         }
      }
 }

 TreeHeader<<""<<endl;
 TreeHeader<<"   // List of branches"<<endl;
 for (l=0;l<nleaves;l++) {
    if (leafStatus[l]) continue;
    TLeaf *leaf = (TLeaf*)leaves->UncheckedAt(l);
//    TreeHeader<<"   TBranch        *b_"<<R__GetBranchPointerName(leaf).Data()<<";   //!"<<endl;
    TreeHeader<<"   TBranch        *b_"<<leaf->GetName()<<";   //!"<<endl;
 }


 TreeHeader<<""<<endl;
 TreeHeader<<"   TreeFor"<<argv[3]<<"();"<<endl;
 TreeHeader<<"   virtual ~TreeFor"<<argv[3]<<"();"<<endl;
 TreeHeader<<"   virtual void ConfigFile(int NFilePerJob, int iRound);"<<endl;
 TreeHeader<<"   virtual void ConfigFile(int ifile);"<<endl;
 TreeHeader<<"   virtual void InputFile(vector<TString> RootNames);"<<endl;
 TreeHeader<<"   virtual void SetBranch(int ifile);"<<endl;
 TreeHeader<<"   virtual void GetEntry(int ifile, long i);"<<endl;
 TreeHeader<<"   virtual void Init();"<<endl;
 TreeHeader<<"};"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"#endif"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"#ifdef TreeFor"<<argv[3]<<"_cxx"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"void TreeFor"<<argv[3]<<"::Init()"<<endl;
 TreeHeader<<"{"<<endl;
 TreeHeader<<"   // The Init() function is called when the selector needs to initialize"<<endl;
 TreeHeader<<"   // a new tree or chain. Typically here the branch addresses and branch"<<endl;
 TreeHeader<<"   // pointers of the tree will be set."<<endl;
 TreeHeader<<"   // It is normally not necessary to make changes to the generated"<<endl;
 TreeHeader<<"   // code, but the routine can be extended by the user if needed."<<endl;
 TreeHeader<<"   // Init() will be called many times when running on PROOF"<<endl;
 TreeHeader<<"   // (once per file to be processed)."<<endl;
 TreeHeader<<""<<endl;

   if (mustInit.Last()) {
      TIter next(&mustInit);
      TObject *obj;
      TreeHeader<<"   // Set object pointer"<<endl;
      while( (obj = next()) ) {
         if (obj->InheritsFrom(TBranch::Class())) {
            strlcpy(branchname,((TBranch*)obj)->GetName(),sizeof(branchname));
         } else if (obj->InheritsFrom(TLeaf::Class())) {
            strlcpy(branchname,((TLeaf*)obj)->GetName(),sizeof(branchname));
         }
         branchname[1023]=0;
         bname = branchname;
         while (*bname) {
            if (*bname == '.') *bname='_';
            if (*bname == ',') *bname='_';
            if (*bname == ':') *bname='_';
            if (*bname == '<') *bname='_';
            if (*bname == '>') *bname='_';
            bname++;
         }
         TreeHeader<<"   "<<branchname<<" = 0;"<<endl;
      }
   }
   if (mustInitArr.Last()) {
      TIter next(&mustInitArr);
      TNamed *info;
      TreeHeader<<"   // Set array pointer"<<endl;
      while( (info = (TNamed*)next()) ) {
         TreeHeader<<"   for(int i=0; i<"<<info->GetTitle()<<"; ++i) "<<info->GetName()<<"[i] = 0;"<<endl;
      }
      TreeHeader<<""<<endl;
   }

 TreeHeader<<"   // Set branch addresses and branch pointers"<<endl;
 TreeHeader<<"}"<<endl;
 TreeHeader<<""<<endl;
 TreeHeader<<"#endif"<<endl;

 ////////////////
 // TreeSource //
 ////////////////

 TreeSource<<"#define TreeFor"<<argv[3]<<"_cxx"<<endl;
 TreeSource<<"#include \"Analysis/TreeFor"<<argv[3]<<".h\""<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"using namespace std;"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"TreeFor"<<argv[3]<<"::TreeFor"<<argv[3]<<"()"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<" Init();"<<endl;
 TreeSource<<"}"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"TreeFor"<<argv[3]<<"::~TreeFor"<<argv[3]<<"()"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"}"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"void TreeFor"<<argv[3]<<"::ConfigFile(int NFilePerJob, int iRound)"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<" FirstFile = iRound * NFilePerJob;"<<endl;
 TreeSource<<" EndFile = (iRound + 1) * NFilePerJob;"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<" if(EndFile >= RootNames.size()) EndFile = RootNames.size();"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<" for(int i = FirstFile; i < EndFile; i++){"<<endl;
 TreeSource<<"   rootfile[i] = new TFile(RootNames.at(i));"<<endl;
 TreeSource<<"   SetBranch(i);"<<endl;
 TreeSource<<" }"<<endl;
 TreeSource<<"}"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"void TreeFor"<<argv[3]<<"::ConfigFile(int ifile)"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<" OneFilePerJob = true;"<<endl;
 TreeSource<<" FirstFile = 0;"<<endl;
 TreeSource<<" EndFile = 1;"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<" rootfile[0] = new TFile(RootNames.at(ifile));"<<endl;
 TreeSource<<" SetBranch(0);"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"}"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"void TreeFor"<<argv[3]<<"::InputFile(vector<TString> RootNames)"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<" this->RootNames = RootNames;"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"}"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"void TreeFor"<<argv[3]<<"::SetBranch(int ifile)"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<"   fChain[ifile] = (TTree *)rootfile[ifile]->Get(\""<<argv[2]<<"\");"<<endl;
 TreeSource<<""<<endl;


 TreeSource<<"   // Set branch addresses and branch pointers"<<endl; 
   for (l=0;l<nleaves;l++) {
      if (leafStatus[l]) continue;
      TLeaf *leaf = (TLeaf*)leaves->UncheckedAt(l);
      len = leaf->GetLen();
      leafcount =leaf->GetLeafCount();
      TBranch *branch = leaf->GetBranch();
      strlcpy(aprefix,branch->GetName(),sizeof(aprefix));
 
      if ( branch->GetNleaves() > 1) {
         // More than one leaf for the branch we need to distinguish them
         strlcpy(branchname,branch->GetName(),sizeof(branchname));
         strlcat(branchname,".",sizeof(branchname));
         strlcat(branchname,leaf->GetTitle(),sizeof(branchname));
         if (leafcount) {
            // remove any dimension in title
            char *dim =  (char*)strstr(branchname,"["); if (dim) dim[0] = 0;
         }
      } else {
         strlcpy(branchname,branch->GetName(),sizeof(branchname));
         if (branch->IsA() == TBranchElement::Class()) {
            bre = (TBranchElement*)branch;
            if (bre->GetType() == 3 || bre->GetType()==4) strlcat(branchname,"_",sizeof(branchname));
         }
      }
      bname = branchname;
      char *brak = strstr(branchname,"[");     if (brak) *brak = 0;
      char *twodim = (char*)strstr(bname,"["); if (twodim) *twodim = 0;
      while (*bname) {
         if (*bname == '.') *bname='_';
         if (*bname == ',') *bname='_';
         if (*bname == ':') *bname='_';
         if (*bname == '<') *bname='_';
         if (*bname == '>') *bname='_';
         bname++;
      }
      const char *maybedisable = "";
      if (branch != tree->GetBranch(branch->GetName())) {
//         Error("MakeClass","The branch named %s (full path name: %s) is hidden by another branch of the same name and its data will not be loaded.",branch->GetName(),R__GetBranchPointerName(leaf,kFALSE).Data());
         maybedisable = "// ";
      }
      if (branch->IsA() == TBranchObject::Class()) {
         if (branch->GetListOfBranches()->GetEntriesFast()) {
            //fprintf(fp,"%s   fChain->SetBranchAddress(\"%s\",(void*)-1,&b_%s);\n",maybedisable,branch->GetName(),R__GetBranchPointerName(leaf).Data());
            TreeSource<<maybedisable<<"   fChain[ifile]->SetBranchAddress(\""<<branch->GetName()<<"\",(void*)-1,&b_"<<leaf->GetName()<<");"<<endl;
            continue;
         }
         strlcpy(branchname,branch->GetName(),sizeof(branchname));
      }
      if (branch->IsA() == TBranchElement::Class()) {
         if (((TBranchElement*)branch)->GetType() == 3) len =1;
         if (((TBranchElement*)branch)->GetType() == 4) len =1;
      }
      if (leafcount) len = leafcount->GetMaximum()+1;
      //if (len > 1) fprintf(fp,"%s   fChain->SetBranchAddress(\"%s\", %s, &b_%s);\n",
      //                     maybedisable,branch->GetName(), branchname, R__GetBranchPointerName(leaf).Data());
      if (len > 1) TreeSource<<maybedisable<<"   fChain[ifile]->SetBranchAddress(\""<<branch->GetName()<<"\", "<<branchname<<", &b_"<<leaf->GetName()<<");"<<endl;
      //else         fprintf(fp,"%s   fChain->SetBranchAddress(\"%s\", &%s, &b_%s);\n",
      //                     maybedisable,branch->GetName(), branchname, R__GetBranchPointerName(leaf).Data());
      else         TreeSource<<maybedisable<<"   fChain[ifile]->SetBranchAddress(\""<<branch->GetName()<<"\", &"<<branchname<<", &b_"<<leaf->GetName()<<");"<<endl;
   }

 TreeSource<<""<<endl;
 TreeSource<<"   TotalEntries[ifile] = fChain[ifile]->GetEntries();"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"}"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"void TreeFor"<<argv[3]<<"::GetEntry(int ifile, long i)"<<endl;
 TreeSource<<"{"<<endl;
 TreeSource<<" fChain[ifile]->GetEntry(i);"<<endl;
 TreeSource<<""<<endl;
 TreeSource<<"}"<<endl;


 //////////////////
 // MainFunction //
 //////////////////

 MainFunction<<"#ifndef ThreadRun"<<argv[3]<<"_cxx"<<endl;
 MainFunction<<"#define ThreadRun"<<argv[3]<<"_cxx"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"#include \"Analysis/Common.h\""<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"void ThreadRun"<<argv[3]<<"(Control process)"<<endl;
 MainFunction<<"{"<<endl;
 MainFunction<<"     bool OneFilePerJob = process.OneFilePerJob;"<<endl;
 MainFunction<<"     int TotalThread = process.TotalThread;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     pthread_t thread[TotalThread];"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     loop"<<argv[3]<<" *Run[TotalThread];"<<endl;
 MainFunction<<"     TreeFor"<<argv[3]<<" *"<<argv[3]<<"Tree[TotalThread];"<<endl;
 MainFunction<<"     Hists"<<argv[3]<<"* myhists;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     myhists = new Hists"<<argv[3]<<"(TotalThread);"<<endl;
 MainFunction<<"     myhists->openFile(process.SaveName);"<<endl;
 MainFunction<<"     myhists->bookHists(TotalThread);"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     for(int j = 0; j < TotalThread; j++){"<<endl;
 MainFunction<<"       "<<argv[3]<<"Tree[j] = new TreeFor"<<argv[3]<<"();"<<endl;
 MainFunction<<"       "<<argv[3]<<"Tree[j]->InputFile(process.RootNames);"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"       Run[j] = new loop"<<argv[3]<<"(process.RootType);"<<endl;
 MainFunction<<"       Run[j]->InputHist(myhists);"<<endl;
 MainFunction<<"       Run[j]->InputThreadInfo(TotalThread, j + 1);"<<endl;
 MainFunction<<"       Run[j]->ConfigCut(process.CutFile);"<<endl;
 MainFunction<<"       if(process.isTest) Run[j]->Test();"<<endl;
 MainFunction<<"     }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     for(int iround = 0; iround < process.TotalRound; iround++){"<<endl;
 MainFunction<<"       int ifile = 0;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"       if(process.TotalRound > 1){"<<endl;
 MainFunction<<"         cout<<\"The \"<<iround + 1<<\" time for submit thread job.\"<<endl;"<<endl;
 MainFunction<<"         cout<<endl;"<<endl;
 MainFunction<<"       }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"       for(int j = 0; j < TotalThread; j++){"<<endl;
 MainFunction<<"         if(!OneFilePerJob) "<<argv[3]<<"Tree[j]->ConfigFile(process.NFilePerJob, iround);"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         if(OneFilePerJob){"<<endl;
 MainFunction<<"           ifile = iround * TotalThread + j;"<<endl;
 MainFunction<<"           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;"<<endl;
 MainFunction<<"           "<<argv[3]<<"Tree[j]->ConfigFile(ifile);"<<endl;
 MainFunction<<"         }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         Run[j]->InputTree("<<argv[3]<<"Tree[j]);"<<endl;
 MainFunction<<"         cout<<\"Initialize the rootfile finish\"<<endl;"<<endl;
 MainFunction<<"       }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"       for(int j = 0; j < TotalThread; j++){"<<endl;
 MainFunction<<"         ifile = iround * TotalThread + j;"<<endl;
 MainFunction<<"         if(OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         pthread_create(&thread[j], NULL, StartThread, Run[j]);"<<endl;
 MainFunction<<"         cout<<\"Thread No.\"<<j + 1<<\" has created.\"<<endl;"<<endl;
 MainFunction<<"         sleep(1);"<<endl;
 MainFunction<<"       }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"       for(int j = 0; j < TotalThread; j++){"<<endl;
 MainFunction<<"         ifile = iround * TotalThread + j;"<<endl;
 MainFunction<<"         if(OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         pthread_join(thread[j], NULL);"<<endl;
 MainFunction<<"         cout<<\"Thread No.\"<<j + 1<<\" has finished.\"<<endl;"<<endl;
 MainFunction<<"       }"<<endl;
 MainFunction<<"     }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     myhists->MergeHists();"<<endl;
 MainFunction<<"     myhists->saveHists();"<<endl;
 MainFunction<<"     delete myhists;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"}"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"void CondorRun"<<argv[3]<<"(Control process)"<<endl;
 MainFunction<<"{"<<endl;
 MainFunction<<"     loop"<<argv[3]<<" *Run;"<<endl;
 MainFunction<<"     TreeFor"<<argv[3]<<" *"<<argv[3]<<"Tree;"<<endl;
 MainFunction<<"     Hists"<<argv[3]<<"* myhists;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     myhists = new Hists"<<argv[3]<<"(1);"<<endl;
 MainFunction<<"     myhists->openFile(process.SaveName);"<<endl;
 MainFunction<<"     myhists->bookHists(1);"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     "<<argv[3]<<"Tree = new TreeFor"<<argv[3]<<"();"<<endl;
 MainFunction<<"     "<<argv[3]<<"Tree->InputFile(process.RootNames);"<<endl;
 MainFunction<<"     "<<argv[3]<<"Tree->ConfigFile(process.NFilePerJob, 0);"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     Run = new loop"<<argv[3]<<"(process.RootType);"<<endl;
 MainFunction<<"     Run->InputHist(myhists);"<<endl;
 MainFunction<<"     Run->InputTree("<<argv[3]<<"Tree);"<<endl;
 MainFunction<<"     Run->ConfigCut(process.CutFile);"<<endl;
 MainFunction<<"     if(process.isTest) Run->Test();"<<endl;
 MainFunction<<"     cout<<\"Initialize the rootfile finish\"<<endl;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){"<<endl;
 MainFunction<<"       Run->Initial(ifile);"<<endl;
 MainFunction<<"       Run->ReadTree(ifile);"<<endl;
 MainFunction<<"       Run->End(ifile);"<<endl;
 MainFunction<<"     }"<<endl;
 MainFunction<<"     Run->Finish();"<<endl;
 MainFunction<<"     myhists->saveHists();"<<endl;
 MainFunction<<"     delete myhists;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"}"<<endl;
 MainFunction<<"#endif"<<endl;

 //////////////////////
 // RootCommonHeader //
 //////////////////////

 RootCommonHeader<<"#include <iomanip>"<<endl;
 RootCommonHeader<<"#include <TROOT.h>"<<endl;
 RootCommonHeader<<"#include <TChain.h>"<<endl;
 RootCommonHeader<<"#include <TFile.h>"<<endl;
 RootCommonHeader<<"#include \"TMath.h\""<<endl;
 RootCommonHeader<<"#include \"TH1F.h\""<<endl;
 RootCommonHeader<<"#include <iostream>"<<endl;
 RootCommonHeader<<"#include <vector>"<<endl;
 RootCommonHeader<<"#include <fstream>"<<endl;
 RootCommonHeader<<"#include <TH2.h>"<<endl;
 RootCommonHeader<<"#include <TStyle.h>"<<endl;
 RootCommonHeader<<"#include <TCanvas.h>"<<endl;
 RootCommonHeader<<"#include \"TLorentzVector.h\""<<endl;
 RootCommonHeader<<"#include \"TString.h\""<<endl;
 RootCommonHeader<<"#include \"TH3F.h\""<<endl;
 RootCommonHeader<<"#include <TRandom3.h>"<<endl;
 RootCommonHeader<<"#include <TMinuit.h>"<<endl;
 RootCommonHeader<<"#include <TApplication.h>"<<endl;
 RootCommonHeader<<"#include \"TEnv.h\""<<endl;
 RootCommonHeader<<"#include <TComplex.h>"<<endl;
 RootCommonHeader<<"#include \"TH2D.h\""<<endl;
 RootCommonHeader<<"#include \"TH3D.h\""<<endl;
 RootCommonHeader<<"#include \"TF1.h\""<<endl;
 RootCommonHeader<<"#include \"TF2.h\""<<endl;
 RootCommonHeader<<"#include \"TLegend.h\""<<endl;
 RootCommonHeader<<"#include <TProfile.h>"<<endl;
 RootCommonHeader<<"#include \"TH1D.h\""<<endl;
 RootCommonHeader<<"#include \"TGraph.h\""<<endl;
 RootCommonHeader<<"#include \"TLeaf.h\""<<endl;
 RootCommonHeader<<"#include \"TLeafObject.h\""<<endl;
 RootCommonHeader<<"#include \"TBranchObject.h\""<<endl;
 RootCommonHeader<<"#include \"TBranchElement.h\""<<endl;
 RootCommonHeader<<"#include \"TStreamerElement.h\""<<endl;

 /////////////////////
 // LoopBasicHeader //
 /////////////////////

 LoopBasicHeader<<"#ifndef loopMC_h"<<endl;
 LoopBasicHeader<<"#define loopMC_h"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<"#include \"RootCommon.h\""<<endl;
 LoopBasicHeader<<"#include <iostream>"<<endl;
 LoopBasicHeader<<"#include <vector>"<<endl;
 LoopBasicHeader<<"#include <fstream>"<<endl;
 LoopBasicHeader<<"#include <pthread.h>"<<endl;
 LoopBasicHeader<<"#include <mutex>"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<"#include \"Analysis/makeHists.h\""<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<"#include \"Tools/Tools.h\""<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<"using namespace std;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<"class loopMC"<<endl;
 LoopBasicHeader<<"{"<<endl;
 LoopBasicHeader<<" public:"<<endl;
 LoopBasicHeader<<" Int_t Sta_TotalNumber;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" vector<TString> RootNames;"<<endl;
 LoopBasicHeader<<" TString RootType;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" vector<int> RootTypes;"<<endl;
 LoopBasicHeader<<" vector<double> CrossSections;"<<endl;
 LoopBasicHeader<<" vector<double> SumOfWeights;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" double TotalWeight;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" int TotalThread;"<<endl;
 LoopBasicHeader<<" int iThread;"<<endl;
 LoopBasicHeader<<" bool isThread;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" long NEvents;"<<endl;
 LoopBasicHeader<<" long TotalEntries[1000];"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" long InitialEntry;"<<endl;
 LoopBasicHeader<<" long Nentries;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" int FirstFile, EndFile;"<<endl;
 LoopBasicHeader<<" bool OneFilePerJob = false;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" bool isTest = false;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" vector<TString> CutInfo;"<<endl;
 LoopBasicHeader<<" vector<double> CutLeft;"<<endl;
 LoopBasicHeader<<" vector<double> CutRight;"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<" loopMC();"<<endl;
 LoopBasicHeader<<" virtual void InputThreadInfo(int TotalThread, int iThread);"<<endl;
 LoopBasicHeader<<" virtual void Initial(int ifile);"<<endl;
 LoopBasicHeader<<" virtual void OutputFileInfo();"<<endl;
 LoopBasicHeader<<" virtual void ConfigCut(const char* CutFile);"<<endl;
 LoopBasicHeader<<" virtual void Test() {isTest = true;}"<<endl;
 LoopBasicHeader<<" virtual void End();"<<endl;
 LoopBasicHeader<<" virtual ~loopMC();"<<endl;
 LoopBasicHeader<<""<<endl;
 LoopBasicHeader<<"};"<<endl;
 LoopBasicHeader<<"#endif"<<endl;

 /////////////////////
 // LoopBasicSource //
 /////////////////////

 LoopBasicSource<<"#define loopMC_cxx"<<endl;
 LoopBasicSource<<"#include <iostream>"<<endl;
 LoopBasicSource<<"#include \"Analysis/loopMC.h\""<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"using namespace std;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"loopMC::loopMC()"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<" Sta_TotalNumber = 0;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" isThread = false;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" isTest = false;"<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"void loopMC::Initial(int ifile)"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<" if(isThread){"<<endl;
 LoopBasicSource<<"   if(!OneFilePerJob){"<<endl;
 LoopBasicSource<<"     NEvents = TotalEntries[ifile] / TotalThread;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"     InitialEntry = (iThread - 1) * NEvents + 1;"<<endl;
 LoopBasicSource<<"     Nentries = iThread * NEvents;"<<endl;
 LoopBasicSource<<"     if(iThread == TotalThread) Nentries = TotalEntries[ifile];"<<endl;
 LoopBasicSource<<"   }"<<endl;
 LoopBasicSource<<"   if(OneFilePerJob){"<<endl;
 LoopBasicSource<<"     InitialEntry = 1;"<<endl;
 LoopBasicSource<<"     Nentries = TotalEntries[ifile];"<<endl;
 LoopBasicSource<<"   }"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<" else{"<<endl;
 LoopBasicSource<<"   InitialEntry = 1;"<<endl;
 LoopBasicSource<<"   Nentries = TotalEntries[ifile];"<<endl;
 LoopBasicSource<<"   iThread = 1;"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" if(isTest){"<<endl;
 LoopBasicSource<<"   Nentries = InitialEntry + 10;"<<endl;
 LoopBasicSource<<"   if(Nentries > TotalEntries[ifile]) Nentries = TotalEntries[ifile];"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"void loopMC::InputThreadInfo(int TotalThread, int iThread)"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<" isThread = true;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" this->TotalThread = TotalThread;"<<endl;
 LoopBasicSource<<" this->iThread = iThread;"<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"void loopMC::OutputFileInfo()"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<" if(!OneFilePerJob){"<<endl;
 LoopBasicSource<<"   cout<<\"There is \"<<(EndFile - FirstFile)<<\" files.\"<<endl;"<<endl;
 LoopBasicSource<<"   for(int i = FirstFile; i < EndFile; i++){"<<endl;
 LoopBasicSource<<"     cout<<RootNames.at(i)<<endl;"<<endl;
 LoopBasicSource<<"   }"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"void loopMC::ConfigCut(const char* CutFile)"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<" if((TString)CutFile == \"0\"){"<<endl;
 LoopBasicSource<<"   CutInfo.push_back(\"0\");"<<endl;
 LoopBasicSource<<"   CutLeft.push_back(0);"<<endl;
 LoopBasicSource<<"   CutRight.push_back(0);"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"   if(iThread == 1 || !isThread){"<<endl;
 LoopBasicSource<<"     cout<<endl;"<<endl;
 LoopBasicSource<<"     cout<<\"Not impose global cut.\"<<endl;"<<endl;
 LoopBasicSource<<"     cout<<endl;"<<endl;
 LoopBasicSource<<"   }"<<endl;
 LoopBasicSource<<"   return;"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" ifstream cutfile;"<<endl;
 LoopBasicSource<<"  cutfile.open(CutFile, ios::in);"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" if(iThread == 1 || !isThread){"<<endl;
 LoopBasicSource<<"   cout<<endl;"<<endl;
 LoopBasicSource<<"   cout<<\"Config cut file: \"<<CutFile<<endl;"<<endl;
 LoopBasicSource<<"   cout<<endl;"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<" TString skip;"<<endl;
 LoopBasicSource<<" double config;"<<endl;
 LoopBasicSource<<" string FileLine;"<<endl;
 LoopBasicSource<<" while(cutfile>>skip){"<<endl;
 LoopBasicSource<<"  getline(cutfile, FileLine);"<<endl;
 LoopBasicSource<<"  CutInfo.push_back(skip);"<<endl;
 LoopBasicSource<<"  if(iThread == 1 || !isThread) cout<<skip<<FileLine<<endl;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"  cutfile>>config;"<<endl;
 LoopBasicSource<<"  getline(cutfile, FileLine);"<<endl;
 LoopBasicSource<<"  CutLeft.push_back(config);"<<endl;
 LoopBasicSource<<"  if(iThread == 1 || !isThread) cout<<config<<FileLine<<endl;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"  cutfile>>config;"<<endl;
 LoopBasicSource<<"  getline(cutfile, FileLine);"<<endl;
 LoopBasicSource<<"  CutRight.push_back(config);"<<endl;
 LoopBasicSource<<"  if(iThread == 1 || !isThread) cout<<config<<FileLine<<endl;"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"  if(iThread == 1 || !isThread) cout<<endl;"<<endl;
 LoopBasicSource<<" }"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"void loopMC::End()"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<" cout<<\"Thread No.\"<<this->iThread<<\" **Running: Free Rootfile: \"<<this->Sta_TotalNumber<<endl;"<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;
 LoopBasicSource<<"loopMC::~loopMC()"<<endl;
 LoopBasicSource<<"{"<<endl;
 LoopBasicSource<<"}"<<endl;
 LoopBasicSource<<""<<endl;

 /////////////////////
 // HistBasicHeader //
 /////////////////////

 HistBasicHeader<<"#ifndef _MAKE_HISTS_H_"<<endl;
 HistBasicHeader<<"#define _MAKE_HISTS_H_"<<endl;
 HistBasicHeader<<"#include <iostream>"<<endl;
 HistBasicHeader<<"#include <fstream>"<<endl;
 HistBasicHeader<<"#include \"RootCommon.h\""<<endl;
 HistBasicHeader<<"#include <vector>"<<endl;
 HistBasicHeader<<"#include <string>"<<endl;
 HistBasicHeader<<"#include <iomanip>"<<endl;
 HistBasicHeader<<"#include <sstream>"<<endl;
 HistBasicHeader<<"#include <map>"<<endl;
 HistBasicHeader<<"#include \"Tools/Tools.h\""<<endl;
 HistBasicHeader<<"#include \"Tools/Log.h\""<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<"using namespace std;"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<"template<class T1>"<<endl;
 HistBasicHeader<<"class ThreadHist"<<endl;
 HistBasicHeader<<"{"<<endl;
 HistBasicHeader<<" public:"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" int TotalThread;"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" vector<T1> HistVector;"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" ThreadHist(int TotalThread){"<<endl;
 HistBasicHeader<<"   this->TotalThread = TotalThread;"<<endl;
 HistBasicHeader<<"   HistVector.resize(TotalThread);"<<endl;
 HistBasicHeader<<" }"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" T1 HistPtr(int iThread){"<<endl;
 HistBasicHeader<<"   return HistVector.at(iThread);"<<endl;
 HistBasicHeader<<" }"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" virtual void Merge(){"<<endl;
 HistBasicHeader<<"   for(int i = 1; i < TotalThread; i++){"<<endl;
 HistBasicHeader<<"     HistVector.at(0)->Add(HistVector.at(i));"<<endl;
 HistBasicHeader<<"   }"<<endl;
 HistBasicHeader<<" }"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" virtual void Reset(){"<<endl;
 HistBasicHeader<<"   for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicHeader<<"     HistVector.at(i)->Reset();"<<endl;
 HistBasicHeader<<"   }"<<endl;
 HistBasicHeader<<" }"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" virtual void Save(){"<<endl;
 HistBasicHeader<<"   HistVector.at(0)->Write();"<<endl;
 HistBasicHeader<<" }"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<"};"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<"class makeHists"<<endl;
 HistBasicHeader<<"{"<<endl;
 HistBasicHeader<<" public:"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" int TotalThread;"<<endl;
 HistBasicHeader<<" TString subName = \"\";"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" ThreadHist<TH1D *>* h1;"<<endl;
 HistBasicHeader<<" ThreadHist<TH2D *>* h2;"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" vector<ThreadHist<TH1D *> *> hist_1d;"<<endl;
 HistBasicHeader<<" vector<ThreadHist<TH2D *> *> hist_2d;"<<endl;
 HistBasicHeader<<" vector<ThreadHist<TH3D *> *> hist_3d;"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" makeHists(){};"<<endl;
 HistBasicHeader<<" makeHists(int TotalThread){this->TotalThread = TotalThread;};"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" virtual void BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx);"<<endl;
 HistBasicHeader<<" virtual void BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double* xbins);"<<endl;
 HistBasicHeader<<" virtual void Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);"<<endl;
 HistBasicHeader<<" virtual void Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins);"<<endl;
 HistBasicHeader<<" virtual void Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty, int nbinz, double leftz, double rightz);"<<endl;
 HistBasicHeader<<" virtual void Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins, int nbinz, double* zbins);"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" virtual void MergeHists();"<<endl;
 HistBasicHeader<<" virtual void ResetHists();"<<endl;
 HistBasicHeader<<" virtual void saveHists();"<<endl;
 HistBasicHeader<<" virtual void outputInformation(){};"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" TString RootType;"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" TFile *hf;"<<endl;
 HistBasicHeader<<" virtual void openFile(const char* fName){hf = new TFile(fName, \"RECREATE\");};"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<" ofstream outputfile;"<<endl;
 HistBasicHeader<<" Logstream myLog;"<<endl;
 HistBasicHeader<<" virtual void LinkLog(Logstream log){this->myLog = log;}"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<"};"<<endl;
 HistBasicHeader<<""<<endl;
 HistBasicHeader<<"#endif"<<endl;
 HistBasicHeader<<""<<endl;

 /////////////////////
 // HistBasicSource //
 /////////////////////

 HistBasicSource<<"#include \"Analysis/makeHists.h\""<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx)"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" h = new ThreadHist<TH1D *>(TotalThread);"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" TString tail = \"\";"<<endl;
 HistBasicSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicSource<<"   h->HistVector.at(i) = new TH1D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);"<<endl;
 HistBasicSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hist_1d.push_back(h);"<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double* xbins)"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" h = new ThreadHist<TH1D *>(TotalThread);"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" TString tail = \"\";"<<endl;
 HistBasicSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicSource<<"   h->HistVector.at(i) = new TH1D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins);"<<endl;
 HistBasicSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hist_1d.push_back(h);"<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" h = new ThreadHist<TH2D *>(TotalThread);"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" TString tail = \"\";"<<endl;
 HistBasicSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicSource<<"   h->HistVector.at(i) = new TH2D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx, nbiny, lefty, righty);"<<endl;
 HistBasicSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hist_2d.push_back(h);"<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" h = new ThreadHist<TH2D *>(TotalThread);"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" TString tail = \"\";"<<endl;
 HistBasicSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicSource<<"   h->HistVector.at(i) = new TH2D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins, nbiny, ybins);"<<endl;
 HistBasicSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hist_2d.push_back(h);"<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty, int nbinz, double leftz, double rightz)"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" h = new ThreadHist<TH3D *>(TotalThread);"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" TString tail = \"\";"<<endl;
 HistBasicSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicSource<<"   h->HistVector.at(i) = new TH3D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx, nbiny, lefty, righty, nbinz, leftz, rightz);"<<endl;
 HistBasicSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hist_3d.push_back(h);"<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins, int nbinz, double* zbins)"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" h = new ThreadHist<TH3D *>(TotalThread);"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" TString tail = \"\";"<<endl;
 HistBasicSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistBasicSource<<"   h->HistVector.at(i) = new TH3D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins, nbiny, ybins, nbinz, zbins);"<<endl;
 HistBasicSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hist_3d.push_back(h);"<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::MergeHists()"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" if(hist_1d.size() != 0) cout<<\"Start to merge the 1D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_1d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_1d.at(ihist)->Merge();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_2d.size() != 0) cout<<\"Start to merge the 2D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_2d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_2d.at(ihist)->Merge();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_3d.size() != 0) cout<<\"Start to merge the 3D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_3d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_3d.at(ihist)->Merge();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::ResetHists()"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" cout<<\"Now, reset the histogram.\"<<endl;"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_1d.size() != 0) cout<<\"Start to reset the 1D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_1d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_1d.at(ihist)->Reset();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_2d.size() != 0) cout<<\"Start to reset the 2D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_2d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_2d.at(ihist)->Reset();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_3d.size() != 0) cout<<\"Start to reset the 3D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_3d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_3d.at(ihist)->Reset();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"void makeHists::saveHists()"<<endl;
 HistBasicSource<<"{"<<endl;
 HistBasicSource<<" hf->cd();"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" cout<<\"Now, save the histogram.\"<<endl;"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_1d.size() != 0) cout<<\"Start to write the 1D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_1d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_1d.at(ihist)->Save();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_2d.size() != 0) cout<<\"Start to write the 2D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_2d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_2d.at(ihist)->Save();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_3d.size() != 0) cout<<\"Start to write the 3D plot.\"<<endl;"<<endl;
 HistBasicSource<<" for(int ihist = 0; ihist < hist_3d.size(); ihist++){"<<endl;
 HistBasicSource<<"   hist_3d.at(ihist)->Save();"<<endl;
 HistBasicSource<<" }"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" if(hist_1d.size() != 0 || hist_2d.size() != 0 || hist_3d.size() != 0) outputInformation();"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<" hf->Close();"<<endl;
 HistBasicSource<<""<<endl;
 HistBasicSource<<"}"<<endl;
 HistBasicSource<<""<<endl;

 ///////////////////
 // ControlHeader //
 ///////////////////

 ControlHeader<<"#ifndef Control_h"<<endl;
 ControlHeader<<"#define Control_h"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<"#include <iostream>"<<endl;
 ControlHeader<<"#include <fstream>"<<endl;
 ControlHeader<<"#include <string>"<<endl;
 ControlHeader<<"#include \"TString.h\""<<endl;
 ControlHeader<<"#include <vector>"<<endl;
 ControlHeader<<"#include \"Tools/Log.h\""<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<"using namespace std;"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<"class Control"<<endl;
 ControlHeader<<"{"<<endl;
 ControlHeader<<" public:"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<" int TotalThread = 0;"<<endl;
 ControlHeader<<" bool isReweight = false;"<<endl;
 ControlHeader<<" bool isFSR = false;"<<endl;
 ControlHeader<<" bool isTest = false;"<<endl;
 ControlHeader<<" bool isRunAllSystematic = false;"<<endl;
 ControlHeader<<" TString RunType = \"\";"<<endl;
 ControlHeader<<" TString RootType = \"\";"<<endl;
 ControlHeader<<" TString FileList = \"\";"<<endl;
 ControlHeader<<" TString SaveName = \"\";"<<endl;
 ControlHeader<<" TString CutFile = \"\";"<<endl;
 ControlHeader<<" TString SystematicList = \"\";"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<"//not input parameter"<<endl;
 ControlHeader<<" TString RootName;"<<endl;
 ControlHeader<<" vector<TString> RootNames;"<<endl;
 ControlHeader<<" int TotalFileNumber;"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<" int NFilePerJob;"<<endl;
 ControlHeader<<" int TotalRound = 1;"<<endl;
 ControlHeader<<" bool OneFilePerJob = false;"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<" Control(){}"<<endl;
 ControlHeader<<" virtual void ReadFile(const char* FileName);"<<endl;
 ControlHeader<<" Control& operator=(const Control &myClass);"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<" virtual void GetRunningType(int recall = 0);"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<" Logstream myLog;"<<endl;
 ControlHeader<<" virtual void LinkLog(Logstream log){this->myLog = log;}"<<endl;
 ControlHeader<<""<<endl;
 ControlHeader<<" virtual void Help();"<<endl;
 ControlHeader<<"};"<<endl;
 ControlHeader<<"#endif"<<endl;
 ControlHeader<<""<<endl;

 ///////////////////
 // ControlSource //
 ///////////////////

 ControlSource<<"#include \"Analysis/control.h\""<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"using namespace std;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"void Control::ReadFile(const char* FileName)"<<endl;
 ControlSource<<"{"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<\"Start to read the card file: \"<<FileName<<endl;"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<" ifstream infile;"<<endl;
 ControlSource<<"   infile.open(FileName, ios::in);"<<endl;
 ControlSource<<" string FileLine;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<" TString skip;"<<endl;
 ControlSource<<" int config;"<<endl;
 ControlSource<<" double config_double;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//running method"<<endl;
 ControlSource<<" infile>>skip;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<skip<<FileLine<<endl;"<<endl;
 ControlSource<<" RunType = skip;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//total thread"<<endl;
 ControlSource<<" infile>>config;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<config<<FileLine<<endl;"<<endl;
 ControlSource<<" TotalThread = config;"<<endl;
 ControlSource<<" if(RunType == \"Condor\") TotalThread = 1;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//root type"<<endl;
 ControlSource<<" infile>>skip;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<skip<<FileLine<<endl;"<<endl;
 ControlSource<<" RootType = skip;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//file list"<<endl;
 ControlSource<<" infile>>skip;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<skip<<FileLine<<endl;"<<endl;
 ControlSource<<" FileList = skip;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<" if(FileList != \"\"){"<<endl;
 ControlSource<<"   ifstream myfile;"<<endl;
 ControlSource<<"     myfile.open(FileList, ios::in);"<<endl;
 ControlSource<<"   while(myfile>>RootName){"<<endl;
 ControlSource<<"     RootNames.push_back(RootName);"<<endl;
 ControlSource<<"   }"<<endl;
 ControlSource<<"   TotalFileNumber = RootNames.size();"<<endl;
 ControlSource<<"   NFilePerJob = TotalFileNumber;"<<endl;
 ControlSource<<" }"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//save name"<<endl;
 ControlSource<<" infile>>skip;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<skip<<FileLine<<endl;"<<endl;
 ControlSource<<" SaveName = skip;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//cut info"<<endl;
 ControlSource<<" infile>>skip;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<skip<<FileLine<<endl;"<<endl;
 ControlSource<<" CutFile = skip;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//isTest"<<endl;
 ControlSource<<" infile>>config;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<config<<FileLine<<endl;"<<endl;
 ControlSource<<" isTest = config;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//isRunAllSystematic"<<endl;
 ControlSource<<" infile>>config;"<<endl;
 ControlSource<<" getline(infile, FileLine);"<<endl;
 ControlSource<<" myLog<<LOG_INFO<<config<<FileLine<<endl;"<<endl;
 ControlSource<<" isRunAllSystematic = config;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<" myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<"}"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"Control& Control::operator=(const Control &myClass)"<<endl;
 ControlSource<<"{"<<endl;
 ControlSource<<" if(this != &myClass){"<<endl;
 ControlSource<<"   this->TotalThread = myClass.TotalThread;"<<endl;
 ControlSource<<"   this->isReweight = myClass.isReweight;"<<endl;
 ControlSource<<"   this->isFSR = myClass.isFSR;"<<endl;
 ControlSource<<"   this->isTest = myClass.isTest;"<<endl;
 ControlSource<<"   this->isRunAllSystematic = myClass.isRunAllSystematic;"<<endl;
 ControlSource<<"   this->RunType = myClass.RunType;"<<endl;
 ControlSource<<"   this->RootType = myClass.RootType;"<<endl;
 ControlSource<<"   this->FileList = myClass.FileList;"<<endl;
 ControlSource<<"   this->SaveName = myClass.SaveName;"<<endl;
 ControlSource<<"   this->CutFile = myClass.CutFile;"<<endl;
 ControlSource<<"   this->SystematicList = myClass.SystematicList;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//not input parameter"<<endl;
 ControlSource<<"   this->RootName = myClass.RootName;"<<endl;
 ControlSource<<"   this->RootNames = myClass.RootNames;"<<endl;
 ControlSource<<"   this->TotalFileNumber = myClass.TotalFileNumber;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"   this->NFilePerJob = myClass.NFilePerJob;"<<endl;
 ControlSource<<"   this->TotalRound = myClass.TotalRound;"<<endl;
 ControlSource<<"   this->OneFilePerJob = myClass.OneFilePerJob;"<<endl;
 ControlSource<<"   this->myLog = myClass.myLog;"<<endl;
 ControlSource<<" }"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<" return *this;"<<endl;
 ControlSource<<"}"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"void Control::Help()"<<endl;
 ControlSource<<"{"<<endl;
 ControlSource<<" myLog<<\"Thread                                          *Running method (Thread/Condor)\"<<endl;"<<endl;
 ControlSource<<" myLog<<\"2                                               *Thread Number\"<<endl;"<<endl;
 ControlSource<<" myLog<<\""<<argv[3]<<"                                          *Rootfile Type (Wasymmetry/ResBos/ResBosW/....)\"<<endl;"<<endl;
 ControlSource<<" myLog<<\"data.list                                       *file list\"<<endl;"<<endl;
 ControlSource<<" myLog<<\"MC_results.root                                 *save rootfile name\"<<endl;"<<endl;
 ControlSource<<" myLog<<\"0                                               *global cut information\"<<endl;"<<endl;
 ControlSource<<" myLog<<\"0                                               *is Test(1: test, 0: normal run)\"<<endl;"<<endl;
 ControlSource<<" myLog<<\"0                                               *run all systematic\"<<endl;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"}"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"void Control::GetRunningType(int recall)"<<endl;
 ControlSource<<"{"<<endl;
 ControlSource<<" int TotalThread = this->TotalThread;"<<endl;
 ControlSource<<" int TotalRound = 1;"<<endl;
 ControlSource<<" int NFilePerJob = this->TotalFileNumber;"<<endl;
 ControlSource<<" int FileMaximum = 1000;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<" if(TotalThread * this->TotalFileNumber >= FileMaximum){"<<endl;
 ControlSource<<"//this is the strategy for not too many files but with big thread number running."<<endl;
 ControlSource<<"   NFilePerJob = FileMaximum / TotalThread;"<<endl;
 ControlSource<<"   TotalRound = this->TotalFileNumber / NFilePerJob + 1;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"   this->NFilePerJob = NFilePerJob;"<<endl;
 ControlSource<<"   this->TotalRound = TotalRound;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"//this is the strategy for too many files in thread running."<<endl;
 ControlSource<<"   if(this->TotalFileNumber >= this->TotalThread && this->TotalRound > 1){"<<endl;
 ControlSource<<"     this->OneFilePerJob = true;"<<endl;
 ControlSource<<"     this->TotalRound = this->TotalFileNumber / this->TotalThread + 1;"<<endl;
 ControlSource<<"   }"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"   if(recall == 0) myLog<<LOG_INFO<<\"First call the function to get the running type.\"<<endl;"<<endl;
 ControlSource<<"   if(recall == 1) myLog<<LOG_INFO<<\"The total file number has changed to \"<<this->TotalFileNumber<<\", recalculate the running type.\"<<endl;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"   if(!this->OneFilePerJob){"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<\"Number of files are too many, submit thread job for \"<<TotalRound<<\" times.\"<<endl;"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<\"Number of files per Job are \"<<NFilePerJob<<endl;"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<"   }"<<endl;
 ControlSource<<"   else{"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<\"Using the strategy of one file per thread.\"<<endl;"<<endl;
 ControlSource<<"     myLog<<LOG_INFO<<endl;"<<endl;
 ControlSource<<"   }"<<endl;
 ControlSource<<" }"<<endl;
 ControlSource<<" else{"<<endl;
 ControlSource<<"   this->NFilePerJob = NFilePerJob;"<<endl;
 ControlSource<<"   this->TotalRound = TotalRound;"<<endl;
 ControlSource<<"   this->OneFilePerJob = false;"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"   if(recall == 0) myLog<<LOG_INFO<<\"First call the function to get the running type.\"<<endl;"<<endl;
 ControlSource<<"   if(recall == 1) myLog<<LOG_INFO<<\"The total file number has changed to \"<<this->TotalFileNumber<<\", recalculate the running type.\"<<endl;"<<endl;
 ControlSource<<" }"<<endl;
 ControlSource<<""<<endl;
 ControlSource<<"}"<<endl;
 ControlSource<<""<<endl;

 //////////////////
 // CommonHeader //
 //////////////////

 CommonHeader<<"#ifndef Common_h"<<endl;
 CommonHeader<<"#define Common_h"<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"#include <iostream>"<<endl;
 CommonHeader<<"#include <fstream>"<<endl;
 CommonHeader<<"#include <pthread.h>"<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"#include \"Analysis/loopMC.h\""<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"#include \"Tools/Tools.h\""<<endl;
 CommonHeader<<"#include \"Tools/Log.h\""<<endl;
 CommonHeader<<"#include \"RootCommon.h\""<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"#include \"Analysis/loopMC.h\""<<endl;
 CommonHeader<<"#include \"Analysis/control.h\""<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"#include \"Analysis/loop"<<argv[3]<<".h\""<<endl;
 CommonHeader<<"#include \"Analysis/Hists"<<argv[3]<<".h\""<<endl;
 CommonHeader<<"#include \"Analysis/TreeFor"<<argv[3]<<".h\""<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"extern pthread_mutex_t mtx;"<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"void* StartThread(void* arg);"<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"void ThreadRun"<<argv[3]<<"(Control process);"<<endl;
 CommonHeader<<"void CondorRun"<<argv[3]<<"(Control process);"<<endl;
 CommonHeader<<""<<endl;
 CommonHeader<<"#endif"<<endl;
 CommonHeader<<""<<endl;

 //////////////////
 // CommonSource //
 //////////////////

 CommonSource<<"#ifndef Common_cxx"<<endl;
 CommonSource<<"#define Common_cxx"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"#include \"Analysis/Common.h\""<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"void* StartThread(void* arg)"<<endl;
 CommonSource<<"{"<<endl;
 CommonSource<<" loopMC* tmp = (loopMC *)arg;"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<" if(tmp->RootType == \""<<argv[3]<<"\"){"<<endl;
 CommonSource<<"   loop"<<argv[3]<<"* ptr = (loop"<<argv[3]<<" *)arg;"<<endl;
 CommonSource<<"   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){"<<endl;
 CommonSource<<"     ptr->Initial(ifile);"<<endl;
 CommonSource<<"     ptr->ReadTree(ifile);"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"     if(pthread_mutex_lock(&mtx) != 0){"<<endl;
 CommonSource<<"       cout<<\"Error: lock failed\"<<endl;"<<endl;
 CommonSource<<"     }"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"     ptr->End(ifile);"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"     if(pthread_mutex_unlock(&mtx) != 0){"<<endl;
 CommonSource<<"       cout<<\"Error: unlock failed\"<<endl;"<<endl;
 CommonSource<<"     }"<<endl;
 CommonSource<<"   }"<<endl;
 CommonSource<<"   ptr->Finish();"<<endl;
 CommonSource<<" }"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<" sleep(0.1);"<<endl;
 CommonSource<<" pthread_exit(NULL);"<<endl;
 CommonSource<<"}"<<endl;
 CommonSource<<""<<endl;
 CommonSource<<"#endif"<<endl;
 CommonSource<<""<<endl;

 ///////////////
 // CMakeRoot //
 ///////////////

 CMakeRoot<<"cmake_minimum_required(VERSION 3.9)"<<endl;
 CMakeRoot<<"cmake_policy(SET CMP0074 NEW)"<<endl;
 CMakeRoot<<"project(loopMC)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"find_package(ROOT)"<<endl;
 CMakeRoot<<"include_directories(${ROOT_INCLUDE_DIRS})"<<endl;
 CMakeRoot<<"set(CMAKE_CXX_STANDARD 17)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -lpthread\")"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"option(USE_LHAPDF ON)"<<endl;
 CMakeRoot<<"option(USE_LWTNN ON)"<<endl;
 CMakeRoot<<"option(USE_TMVA ON)"<<endl;
 CMakeRoot<<"option(USE_ROOFIT ON)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"#change the option here"<<endl;
 CMakeRoot<<"set(USE_LHAPDF OFF)"<<endl;
 CMakeRoot<<"set(USE_LWTNN OFF)"<<endl;
 CMakeRoot<<"set(USE_TMVA OFF)"<<endl;
 CMakeRoot<<"set(USE_ROOFIT OFF)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"#LHAPDF"<<endl;
 CMakeRoot<<"if(USE_LHAPDF)"<<endl;
 CMakeRoot<<"    add_definitions(-DUSE_LHAPDF)"<<endl;
 CMakeRoot<<"    set(LHAPDF_ROOT $ENV{LHAPDF_ROOT_DIR})"<<endl;
 CMakeRoot<<"    set(LHAPDF_INCLUDE_DIRS $ENV{LHAPDF_ROOT_DIR}/include)"<<endl;
 CMakeRoot<<"    include_directories(${LHAPDF_INCLUDE_DIRS})"<<endl;
 CMakeRoot<<"endif(USE_LHAPDF)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"#LWTNN"<<endl;
 CMakeRoot<<"if(USE_LWTNN)"<<endl;
 CMakeRoot<<"    add_definitions(-DUSE_LWTNN)"<<endl;
 CMakeRoot<<"    set(LWTNN_ROOT $ENV{LWTNN_ROOT_DIR})"<<endl;
 CMakeRoot<<"    set(LWTNN_INCLUDE_DIRS $ENV{LWTNN_ROOT_DIR}/include)"<<endl;
 CMakeRoot<<"    set(LWTNN_LIBRARIES $ENV{LWTNN_ROOT_DIR}/lib/liblwtnn.so)"<<endl;
 CMakeRoot<<"    include_directories(${LWTNN_INCLUDE_DIRS})"<<endl;
 CMakeRoot<<"endif(USE_LWTNN)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"include_directories(include)"<<endl;
 CMakeRoot<<"add_subdirectory(src)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"#TMinuit"<<endl;
 CMakeRoot<<"set(ROOT_LIBRARIES \"${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libMinuit.so\")#for cvmfs"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"#TMVA"<<endl;
 CMakeRoot<<"if(USE_TMVA)"<<endl;
 CMakeRoot<<"    add_definitions(-DUSE_TMVA)"<<endl;
 CMakeRoot<<"    set(ROOT_LIBRARIES \"${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libTMVA.so\")#for cvmfs"<<endl;
 CMakeRoot<<"endif(USE_TMVA)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"#RooFit"<<endl;
 CMakeRoot<<"if(USE_ROOFIT)"<<endl;
 CMakeRoot<<"    add_definitions(-DUSE_ROOFIT)"<<endl;
 CMakeRoot<<"    set(ROOT_LIBRARIES \"${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFit.so\")"<<endl;
 CMakeRoot<<"    set(ROOT_LIBRARIES \"${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooStats.so\")"<<endl;
 CMakeRoot<<"    set(ROOT_LIBRARIES \"${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFitCore.so\")"<<endl;
 CMakeRoot<<"    set(ROOT_LIBRARIES \"${ROOT_LIBRARIES};${ROOT_DIR}/../lib/libRooFitMore.so\")"<<endl;
 CMakeRoot<<"endif(USE_ROOFIT)"<<endl;
 CMakeRoot<<""<<endl;
 CMakeRoot<<"add_executable(loopMC util/main.C)"<<endl;
 CMakeRoot<<"target_link_libraries(loopMC Analysis TOOL ${ROOT_LIBRARIES})"<<endl;
 CMakeRoot<<"install(TARGETS loopMC DESTINATION bin)"<<endl;
 CMakeRoot<<""<<endl;

 //////////////
 // CMakeSRC //
 //////////////

 CMakeSRC<<"add_subdirectory(Tools)"<<endl;
 CMakeSRC<<"add_subdirectory(Analysis)"<<endl;
 CMakeSRC<<""<<endl;
 CMakeSRC<<"if(USE_TMVA)"<<endl;
 CMakeSRC<<"    add_definitions(-DUSE_TMVA)"<<endl;
 CMakeSRC<<"endif(USE_TMVA)"<<endl;
 CMakeSRC<<""<<endl;
 CMakeSRC<<"file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/*.h)"<<endl;
 CMakeSRC<<"install(FILES ${loop_headers} DESTINATION include)"<<endl;
 CMakeSRC<<""<<endl;

 ////////////////
 // CMakeTools //
 ////////////////

 CMakeTools<<""<<endl;
 CMakeTools<<"aux_source_directory(. DIR_TOOL_SRC)"<<endl;
 CMakeTools<<"add_library(TOOL SHARED ${DIR_TOOL_SRC})"<<endl;
 CMakeTools<<"target_link_libraries(TOOL ${LHAPDF_LIBRARIES} ${LWTNN_LIBRARIES})"<<endl;
 CMakeTools<<""<<endl;
 CMakeTools<<"install(TARGETS TOOL"<<endl;
 CMakeTools<<"        ARCHIVE DESTINATION lib"<<endl;
 CMakeTools<<"        LIBRARY DESTINATION lib"<<endl;
 CMakeTools<<"        RUNTIME DESTINATION bin)"<<endl;
 CMakeTools<<""<<endl;
 CMakeTools<<"file(GLOB tools_headers ${CMAKE_SOURCE_DIR}/include/Tools/*.h)"<<endl;
 CMakeTools<<"install(FILES ${tools_headers} DESTINATION include/Tools)"<<endl;
 CMakeTools<<""<<endl;

 ///////////////////
 // CMakeAnalysis //
 ///////////////////

 CMakeAnalysis<<"include_directories(${CMAKE_SOURCE_DIR}/include/Analysis)"<<endl;
 CMakeAnalysis<<""<<endl;
 CMakeAnalysis<<"aux_source_directory(. DIR_ANALYSIS_SRC)"<<endl;
 CMakeAnalysis<<"add_library(Analysis SHARED ${DIR_ANALYSIS_SRC})"<<endl;
 CMakeAnalysis<<"target_link_libraries(Analysis TOOL ${ROOT_LIBRARIES})"<<endl;
 CMakeAnalysis<<""<<endl;
 CMakeAnalysis<<"install(TARGETS Analysis"<<endl;
 CMakeAnalysis<<"        ARCHIVE DESTINATION lib"<<endl;
 CMakeAnalysis<<"        LIBRARY DESTINATION lib"<<endl;
 CMakeAnalysis<<"        RUNTIME DESTINATION bin)"<<endl;
 CMakeAnalysis<<""<<endl;
 CMakeAnalysis<<"file(GLOB loop_headers ${CMAKE_SOURCE_DIR}/include/Analysis/*.h)"<<endl;
 CMakeAnalysis<<"install(FILES ${loop_headers} DESTINATION include/Analysis)"<<endl;


 /////////////////
 // ToolsHeader //
 /////////////////

 ToolsHeader<<"#ifndef Tools_h"<<endl;
 ToolsHeader<<"#define Tools_h"<<endl;
 ToolsHeader<<""<<endl;
 ToolsHeader<<"#include \"RootCommon.h\""<<endl;
 ToolsHeader<<"#include \"Math/ProbFunc.h\""<<endl;
 ToolsHeader<<"#include <iostream>"<<endl;
 ToolsHeader<<"#include <vector>"<<endl;
 ToolsHeader<<"#include <fstream>"<<endl;
 ToolsHeader<<"#include <string>"<<endl;
 ToolsHeader<<"#include <time.h>"<<endl;
 ToolsHeader<<"#include <pthread.h>"<<endl;
 ToolsHeader<<""<<endl;
 ToolsHeader<<"using namespace std;"<<endl;
 ToolsHeader<<""<<endl;
 ToolsHeader<<"string getTime();"<<endl;
 ToolsHeader<<""<<endl;
 ToolsHeader<<"#endif"<<endl;
 ToolsHeader<<""<<endl;

 ////////////////
 // TimeSource //
 ////////////////

 TimeSource<<"#ifndef Tools_GetTime_cxx"<<endl;
 TimeSource<<"#define Tools_GetTime_cxx"<<endl;
 TimeSource<<""<<endl;
 TimeSource<<"#include \"Tools/Tools.h\""<<endl;
 TimeSource<<""<<endl;
 TimeSource<<"string getTime()"<<endl;
 TimeSource<<"{"<<endl;
 TimeSource<<"    time_t timep;"<<endl;
 TimeSource<<"    time (&timep);"<<endl;
 TimeSource<<"    char tmp[64];"<<endl;
 TimeSource<<"    strftime(tmp, sizeof(tmp), \"%Y-%m-%d %H:%M:%S\",localtime(&timep) );"<<endl;
 TimeSource<<"    return tmp;"<<endl;
 TimeSource<<"}"<<endl;
 TimeSource<<""<<endl;
 TimeSource<<"#endif"<<endl;

 ///////////////
 // LogHeader //
 ///////////////

 LogHeader<<"#ifndef Tools_Log_h"<<endl;
 LogHeader<<"#define Tools_Log_h"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"#include <iostream>"<<endl;
 LogHeader<<"#include <fstream>"<<endl;
 LogHeader<<"#include \"TString.h\""<<endl;
 LogHeader<<"#include \"Tools/Tools.h\""<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"/*namespace mylog"<<endl;
 LogHeader<<"{"<<endl;
 LogHeader<<" void log(const char* format, ...);"<<endl;
 LogHeader<<"}"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"#define LOG_INFO(...) \\"<<endl;
 LogHeader<<" mylog::log(__VA_ARGS__)"<<endl;
 LogHeader<<"*/"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"class Logbuf : public std::streambuf"<<endl;
 LogHeader<<"{"<<endl;
 LogHeader<<" public:"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" Logbuf(std::streambuf* stream1, std::streambuf* stream2)"<<endl;
 LogHeader<<" : stream1(stream1), stream2(stream2){}"<<endl;
 LogHeader<<" Logbuf(){}"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" virtual void Initial(std::streambuf* stream1, std::streambuf* stream2)"<<endl;
 LogHeader<<" {"<<endl;
 LogHeader<<"   this->stream1 = stream1;"<<endl;
 LogHeader<<"   this->stream2 = stream2;"<<endl;
 LogHeader<<" }"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" Logbuf(const Logbuf& myClass)"<<endl;
 LogHeader<<" {"<<endl;
 LogHeader<<"   this->stream1 = myClass.stream1;"<<endl;
 LogHeader<<"   this->stream2 = myClass.stream2;"<<endl;
 LogHeader<<" }"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" Logbuf& operator=(const Logbuf &myClass)"<<endl;
 LogHeader<<" {"<<endl;
 LogHeader<<"   if(this != &myClass){"<<endl;
 LogHeader<<"     this->stream1 = myClass.stream1;"<<endl;
 LogHeader<<"     this->stream2 = myClass.stream2;"<<endl;
 LogHeader<<"   }"<<endl;
 LogHeader<<"   return *this;"<<endl;
 LogHeader<<" }"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" private:"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" virtual int overflow(int c)"<<endl;
 LogHeader<<" {"<<endl;
 LogHeader<<"   if(c == EOF){"<<endl;
 LogHeader<<"     return !EOF;"<<endl;
 LogHeader<<"   }"<<endl;
 LogHeader<<"   else{"<<endl;
 LogHeader<<"     int const r1 = stream1->sputc(c);"<<endl;
 LogHeader<<"     int const r2 = stream2->sputc(c);"<<endl;
 LogHeader<<"     return r1 == EOF || r2 == EOF ? EOF : c;"<<endl;
 LogHeader<<"   }"<<endl;
 LogHeader<<" }"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" virtual int sync()"<<endl;
 LogHeader<<" {"<<endl;
 LogHeader<<"   int const r1 = stream1->pubsync();"<<endl;
 LogHeader<<"   int const r2 = stream2->pubsync();"<<endl;
 LogHeader<<"   return r1 == 0 || r2 == 0 ? 0 : -1;"<<endl;
 LogHeader<<" }"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" private:"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" std::streambuf* stream1;"<<endl;
 LogHeader<<" std::streambuf* stream2;"<<endl;
 LogHeader<<"};"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"class Logstream : public std::ostream"<<endl;
 LogHeader<<"{"<<endl;
 LogHeader<<" public:"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" Logstream(std::ostream& o1, std::ostream& o2);"<<endl;
 LogHeader<<" Logstream();"<<endl;
 LogHeader<<" Logstream(const Logstream& myClass)"<<endl;
 LogHeader<<" {"<<endl;
 LogHeader<<"   this->mybuf = myClass.mybuf;"<<endl;
 LogHeader<<" }"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" virtual void Initial(std::ostream& o1, std::ostream& o2);"<<endl;
 LogHeader<<" Logstream& operator=(const Logstream &myClass);"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" private:"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<" Logbuf mybuf;"<<endl;
 LogHeader<<"};"<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"#define LOG_INFO getTime()<<\"  INFO| \""<<endl;
 LogHeader<<"#define LOG_ERROR getTime()<<\"  ERROR| \""<<endl;
 LogHeader<<""<<endl;
 LogHeader<<"#endif"<<endl;
 LogHeader<<""<<endl;

 ///////////////
 // LogSource //
 ///////////////

 LogSource<<"#include \"Tools/Log.h\""<<endl;
 LogSource<<""<<endl;
 LogSource<<"Logstream::Logstream(std::ostream& o1, std::ostream& o2)"<<endl;
 LogSource<<": std::ostream(&mybuf), mybuf(o1.rdbuf(), o2.rdbuf())"<<endl;
 LogSource<<"{"<<endl;
 LogSource<<""<<endl;
 LogSource<<"}"<<endl;
 LogSource<<""<<endl;
 LogSource<<"Logstream::Logstream()"<<endl;
 LogSource<<": std::ostream(&mybuf)"<<endl;
 LogSource<<"{"<<endl;
 LogSource<<""<<endl;
 LogSource<<"}"<<endl;
 LogSource<<""<<endl;
 LogSource<<"void Logstream::Initial(std::ostream& o1, std::ostream& o2)"<<endl;
 LogSource<<"{"<<endl;
 LogSource<<" mybuf.Initial(o1.rdbuf(), o2.rdbuf());"<<endl;
 LogSource<<"}"<<endl;
 LogSource<<""<<endl;
 LogSource<<"Logstream& Logstream::operator=(const Logstream &myClass)"<<endl;
 LogSource<<"{"<<endl;
 LogSource<<" if(this != &myClass){"<<endl;
 LogSource<<"   this->mybuf = myClass.mybuf;"<<endl;
 LogSource<<" }"<<endl;
 LogSource<<""<<endl;
 LogSource<<" return *this;"<<endl;
 LogSource<<"}"<<endl;
 LogSource<<""<<endl;

 //////////////
 // MainCode //
 //////////////

 MainCode<<"#include \"Analysis/Common.h\""<<endl;
 MainCode<<""<<endl;
 MainCode<<"using namespace std;"<<endl;
 MainCode<<""<<endl;
 MainCode<<"int main(int argc, char** argv)"<<endl;
 MainCode<<"{"<<endl;
 MainCode<<" if(argc != 2){"<<endl;
 MainCode<<"   cout<<\"usage ./loopMC cardfile\"<<endl;"<<endl;
 MainCode<<"   ofstream outputfile;"<<endl;
 MainCode<<"   Logstream myLog;"<<endl;
 MainCode<<"   outputfile.open(\"save.log\");"<<endl;
 MainCode<<"   myLog.Initial(cout, outputfile);"<<endl;
 MainCode<<"   Control process;"<<endl;
 MainCode<<"   process.LinkLog(myLog);"<<endl;
 MainCode<<"   cout<<\"Please construct cardfile as following:\"<<endl;"<<endl;
 MainCode<<"   process.Help();"<<endl;
 MainCode<<"   return 0;"<<endl;
 MainCode<<" }"<<endl;
 MainCode<<""<<endl;
 MainCode<<" ofstream outputfile;"<<endl;
 MainCode<<" Logstream myLog;"<<endl;
 MainCode<<" outputfile.open(\"save.log\");"<<endl;
 MainCode<<" myLog.Initial(cout, outputfile);"<<endl;
 MainCode<<""<<endl;
 MainCode<<" myLog<<LOG_INFO<<\"// ----------------------------- //\"<<endl;"<<endl;
 MainCode<<" myLog<<LOG_INFO<<\"//       Loop Events Begin       //\"<<endl;"<<endl;
 MainCode<<" myLog<<LOG_INFO<<\"// ----------------------------- //\"<<endl;"<<endl;
 MainCode<<""<<endl;
 MainCode<<" Control process;"<<endl;
 MainCode<<" process.LinkLog(myLog);"<<endl;
 MainCode<<" process.ReadFile(argv[1]);"<<endl;
 MainCode<<""<<endl;
 MainCode<<" if(process.RunType != \"Thread\" && process.RunType != \"Condor\"){"<<endl;
 MainCode<<"    myLog<<LOG_ERROR<<\"For RunType, please use \\\"Thread\\\" or \\\"Condor\\\"\"<<endl;"<<endl;
 MainCode<<"    myLog<<LOG_ERROR<<\"Please construct cardfile as following:\"<<endl;"<<endl;
 MainCode<<"    myLog<<LOG_ERROR<<\"\"<<endl;"<<endl;
 MainCode<<"    process.Help();"<<endl;
 MainCode<<"    return 0;"<<endl;
 MainCode<<" }"<<endl;
 MainCode<<""<<endl;
 MainCode<<" if(process.RootType != \""<<argv[3]<<"\"){"<<endl;
 MainCode<<"    myLog<<LOG_ERROR<<\"For RootType, please use \\\""<<argv[3]<<"\\\"\"<<endl;"<<endl;
 MainCode<<"    myLog<<LOG_ERROR<<\"Please construct cardfile as following:\"<<endl;"<<endl;
 MainCode<<"    myLog<<LOG_ERROR<<\"\"<<endl;"<<endl;
 MainCode<<"    process.Help();"<<endl;
 MainCode<<""<<endl;
 MainCode<<"    return 0;"<<endl;
 MainCode<<" }"<<endl;
 MainCode<<""<<endl;
 MainCode<<" if(process.RunType == \"Thread\"){"<<endl;
 MainCode<<"   myLog<<LOG_INFO<<\"Thread: Start Time: \"<<getTime()<<endl;"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   process.GetRunningType();"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   TString RootType = process.RootType;"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   if(RootType == \""<<argv[3]<<"\"){"<<endl;
 MainCode<<"     ThreadRun"<<argv[3]<<"(process);"<<endl;
 MainCode<<"   }"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   myLog<<LOG_INFO<<\"Thread: End Time:   \"<<getTime()<<endl;"<<endl;
 MainCode<<" }"<<endl;
 MainCode<<""<<endl;
 MainCode<<" if(process.RunType == \"Condor\"){"<<endl;
 MainCode<<"   myLog<<LOG_INFO<<\"Condor: Start Time: \"<<getTime()<<endl;"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   TString RootType = process.RootType;"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   if(RootType == \""<<argv[3]<<"\"){"<<endl;
 MainCode<<"     CondorRun"<<argv[3]<<"(process);"<<endl;
 MainCode<<"   }"<<endl;
 MainCode<<""<<endl;
 MainCode<<"   myLog<<LOG_INFO<<\"Condor: End Time: \"<<getTime()<<endl;"<<endl;
 MainCode<<" }"<<endl;
 MainCode<<""<<endl;
 MainCode<<" myLog<<LOG_INFO<<\"Master thread is end.\"<<endl;"<<endl;
 MainCode<<""<<endl;
 MainCode<<" return 1;"<<endl;
 MainCode<<"}"<<endl;
 MainCode<<""<<endl;


 //////////////////
 // Other things //
 //////////////////

 cout<<"Please do following things:"<<endl;
 cout<<""<<endl;
 cout<<"build a Root directory(for example: AnalysisCode):"<<endl;
 cout<<""<<endl;
 cout<<"mkdir AnalysisCode"<<endl;
 cout<<"mkdir AnalysisCode/include"<<endl;
 cout<<"mkdir AnalysisCode/src"<<endl;
 cout<<"mkdir AnalysisCode/util"<<endl;
 cout<<"mkdir AnalysisCode/build"<<endl;
 cout<<"mkdir AnalysisCode/include/Tools"<<endl;
 cout<<"mkdir AnalysisCode/src/Tools"<<endl;
 cout<<"mkdir AnalysisCode/include/Analysis"<<endl;
 cout<<"mkdir AnalysisCode/src/Analysis"<<endl;
 cout<<"mv Common.h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv control.h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv loopMC.h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv makeHists.h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv RootCommon.h AnalysisCode/include"<<endl;
 cout<<"mv loop"<<argv[3]<<".h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv Hists"<<argv[3]<<".h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv TreeFor"<<argv[3]<<".h AnalysisCode/include/Analysis"<<endl;
 cout<<"mv Common.C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv control.C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv loopMC.C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv makeHists.C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv loop"<<argv[3]<<".C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv Hists"<<argv[3]<<".C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv TreeFor"<<argv[3]<<".C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv ThreadRun"<<argv[3]<<".C AnalysisCode/src/Analysis"<<endl;
 cout<<"mv Tools.h AnalysisCode/include/Tools"<<endl;
 cout<<"mv Log.h AnalysisCode/include/Tools"<<endl;
 cout<<"mv GetTime.C AnalysisCode/src/Tools"<<endl;
 cout<<"mv Log.C AnalysisCode/src/Tools"<<endl;
 cout<<"mv main.C AnalysisCode/util"<<endl;
 cout<<"mv CMakeLists.txt AnalysisCode"<<endl;
 cout<<"mv CMakeLists.txt.src AnalysisCode/src/CMakeLists.txt"<<endl;
 cout<<"mv CMakeLists.txt.Tools AnalysisCode/src/Tools/CMakeLists.txt"<<endl;
 cout<<"mv CMakeLists.txt.Analysis AnalysisCode/src/Analysis/CMakeLists.txt"<<endl;
 cout<<""<<endl;
 cout<<"For compile:"<<endl;
 cout<<""<<endl;
 cout<<"cd AnalysisCode/build"<<endl;
 cout<<"cmake .."<<endl;
 cout<<"make -j install"<<endl;
 cout<<""<<endl;

 return 1;
}
