#include <iostream>
#include <fstream>
#include "RootCommon.h"

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

 LoopHeader.open((TString)"loop" + (TString)argv[3] + (TString)".h");
 LoopSource.open((TString)"loop" + (TString)argv[3] + (TString)".C");
 HistHeader.open((TString)"Hists" + (TString)argv[3] + (TString)".h");
 HistSource.open((TString)"Hists" + (TString)argv[3] + (TString)".C");
 TreeHeader.open((TString)"TreeFor" + (TString)argv[3] + (TString)".h");
 TreeSource.open((TString)"TreeFor" + (TString)argv[3] + (TString)".C");
 MainFunction.open((TString)"ThreadRun" + (TString)argv[3] + (TString)".C");

 ////////////////
 // LoopHeader //
 ////////////////

 LoopHeader<<"#ifndef loop"<<argv[3]<<"_h"<<endl;
 LoopHeader<<"#define loop"<<argv[3]<<"_h"<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"#include \"loopMC.h\""<<endl;
 LoopHeader<<""<<endl;
 LoopHeader<<"#include \"Hists"<<argv[3]<<".h\""<<endl;
 LoopHeader<<"#include \"TreeFor"<<argv[3]<<".h\""<<endl;
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
 LoopSource<<"#include \"loop"<<argv[3]<<".h\""<<endl;
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
 LoopSource<<" this->DivideFile = "<<argv[3]<<"Tree->DivideFile;"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<" for(int ifile = FirstFile; ifile < EndFile; ifile++){"<<endl;
 LoopSource<<"   TotalEntries[ifile] = "<<argv[3]<<"Tree->TotalEntries[ifile];"<<endl;
 LoopSource<<" }"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"}"<<endl;
 LoopSource<<""<<endl;
 LoopSource<<"void loop"<<argv[3]<<"::ReadTree(int ifile)"<<endl;
 LoopSource<<"{"<<endl;
 LoopSource<<" for(int iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){"<<endl;
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
 HistHeader<<"#include \"makeHists.h\""<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"using namespace std;"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"class Hists"<<argv[3]<<" : public makeHists"<<endl;
 HistHeader<<"{"<<endl;
 HistHeader<<" public:"<<endl;
 HistHeader<<""<<endl;
 HistHeader<<"//member function"<<endl;
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

 HistSource<<"#include \"Hists"<<argv[3]<<".h\""<<endl;
 HistSource<<""<<endl;
 HistSource<<"using namespace std;"<<endl;
 HistSource<<""<<endl;
 HistSource<<"void Hists"<<argv[3]<<"::bookHists(int TotalThread)"<<endl;
 HistSource<<"{"<<endl;
 HistSource<<" this->TotalThread = TotalThread;"<<endl;
 HistSource<<" TString tail = \"\";"<<endl;
 HistSource<<""<<endl;
 HistSource<<" for(int i = 0; i < TotalThread; i++){"<<endl;
 HistSource<<""<<endl;
 HistSource<<"   tail = (TString)\"_\" + (int)i;"<<endl;
 HistSource<<" }"<<endl;
 HistSource<<""<<endl;
 HistSource<<" tail = \"\";"<<endl;
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
 TreeHeader<<"   int TotalEntries[1000];"<<endl;
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
 TreeHeader<<"   bool DivideFile = false;"<<endl;
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
 TreeHeader<<"   virtual void GetEntry(int ifile, int i);"<<endl;
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
 TreeSource<<"#include \"TreeFor"<<argv[3]<<".h\""<<endl;
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
 TreeSource<<" DivideFile = true;"<<endl;
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
 TreeSource<<"void TreeFor"<<argv[3]<<"::GetEntry(int ifile, int i)"<<endl;
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
 MainFunction<<"#include \"ThreadRun.h\""<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"void ThreadRun"<<argv[3]<<"(Control process)"<<endl;
 MainFunction<<"{"<<endl;
 MainFunction<<"     bool DivideFile = process.DivideFile;"<<endl;
 MainFunction<<"     int TotalThread = process.TotalThread;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     pthread_t thread[TotalThread];"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     loop"<<argv[3]<<" *Run[TotalThread];"<<endl;
 MainFunction<<"     TreeFor"<<argv[3]<<" *"<<argv[3]<<"Tree[TotalThread];"<<endl;
 MainFunction<<"     Hists"<<argv[3]<<"* myhists;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     myhists = new Hists"<<argv[3]<<"();"<<endl;
 MainFunction<<"     myhists->openFile(process.SaveName);"<<endl;
 MainFunction<<"     myhists->LinkLog(process.myLog);"<<endl;
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
 MainFunction<<"       if(process.newPDFset != -1) Run[j]->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);"<<endl;
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
 MainFunction<<"         if(!DivideFile) "<<argv[3]<<"Tree[j]->ConfigFile(process.NFilePerJob, iround);"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         if(DivideFile){"<<endl;
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
 MainFunction<<"         if(DivideFile && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         pthread_create(&thread[j], NULL, StartThread, Run[j]);"<<endl;
 MainFunction<<"         cout<<\"Thread No.\"<<j + 1<<\" has created.\"<<endl;"<<endl;
 MainFunction<<"         sleep(1);"<<endl;
 MainFunction<<"       }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"       for(int j = 0; j < TotalThread; j++){"<<endl;
 MainFunction<<"         ifile = iround * TotalThread + j;"<<endl;
 MainFunction<<"         if(DivideFile && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"         pthread_join(thread[j], NULL);"<<endl;
 MainFunction<<"         cout<<\"Thread No.\"<<j + 1<<\" has finished.\"<<endl;"<<endl;
 MainFunction<<"       }"<<endl;
 MainFunction<<"     }"<<endl;
 MainFunction<<""<<endl;
 MainFunction<<"     myhists->MergeHists(TotalThread);"<<endl;
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
 MainFunction<<"     myhists = new Hists"<<argv[3]<<"();"<<endl;
 MainFunction<<"     myhists->openFile(process.SaveName);"<<endl;
 MainFunction<<"     myhists->LinkLog(process.myLog);"<<endl;
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
 MainFunction<<"     if(process.newPDFset != -1) Run->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);"<<endl;
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


 //////////////////
 // Other things //
 //////////////////

 cout<<"Please move loop"<<argv[3]<<".h Hists"<<argv[3]<<".h TreeFor"<<argv[3]<<".h to the include directory"<<endl;
 cout<<"Please move loop"<<argv[3]<<".C Hists"<<argv[3]<<".C TreeFor"<<argv[3]<<".C ThreadRun"<<argv[3]<<".C to the src directory"<<endl;
 cout<<""<<endl;
 cout<<"///////////////////////////////////////////////////"<<endl;
 cout<<"// Please add the following lines to util/main.C //"<<endl;
 cout<<"///////////////////////////////////////////////////"<<endl;
 cout<<""<<endl;
 cout<<"   if(RootType == \""<<argv[3]<<"\"){"<<endl;
 cout<<"     ThreadRun"<<argv[3]<<"(process);"<<endl;
 cout<<"   }"<<endl;
 cout<<endl;
 cout<<"   if(RootType == \""<<argv[3]<<"\"){"<<endl;
 cout<<"     CondorRun"<<argv[3]<<"(process);"<<endl;
 cout<<"   }"<<endl;
 cout<<""<<endl;
 cout<<"/////////////////////////////////////////////////////"<<endl;
 cout<<"// Please add the following lines to src/control.C //"<<endl;
 cout<<"/////////////////////////////////////////////////////"<<endl;
 cout<<""<<endl;
 cout<<"to be added..."<<endl;
 cout<<""<<endl;
 cout<<"////////////////////////////////////////////////////"<<endl;
 cout<<"// Please add the following lines to src/Common.C //"<<endl;
 cout<<"////////////////////////////////////////////////////"<<endl;
 cout<<""<<endl;
 cout<<" if(tmp->RootType == \""<<argv[3]<<"\"){"<<endl;
 cout<<"   loop"<<argv[3]<<"* ptr = (loop"<<argv[3]<<" *)arg;"<<endl;
 cout<<"   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){"<<endl;
 cout<<"     ptr->Initial(ifile);"<<endl;
 cout<<"     ptr->ReadTree(ifile);"<<endl;
 cout<<""<<endl;
 cout<<"     if(pthread_mutex_lock(&mtx) != 0){"<<endl;
 cout<<"       cout<<\"Error: lock failed\"<<endl;"<<endl;
 cout<<"     }"<<endl;
 cout<<""<<endl;
 cout<<"     ptr->End(ifile);"<<endl;
 cout<<""<<endl;
 cout<<"     if(pthread_mutex_unlock(&mtx) != 0){"<<endl;
 cout<<"       cout<<\"Error: unlock failed\"<<endl;"<<endl;
 cout<<"     }"<<endl;
 cout<<"   }"<<endl;
 cout<<"   ptr->Finish();"<<endl;
 cout<<" }"<<endl;
 cout<<""<<endl;
 cout<<"////////////////////////////////////////////////////////"<<endl;
 cout<<"// Please add the following lines to include/Common.h //"<<endl;
 cout<<"////////////////////////////////////////////////////////"<<endl;
 cout<<""<<endl;
 cout<<"#include \"loop"<<argv[3]<<".h\""<<endl;
 cout<<""<<endl;
 cout<<"///////////////////////////////////////////////////////////"<<endl;
 cout<<"// Please add the following lines to include/ThreadRun.h //"<<endl;
 cout<<"///////////////////////////////////////////////////////////"<<endl;
 cout<<""<<endl;
 cout<<"#include \"loop"<<argv[3]<<".h\""<<endl;
 cout<<"#include \"Hists"<<argv[3]<<".h\""<<endl;
 cout<<"#include \"TreeFor"<<argv[3]<<".h\""<<endl;
 cout<<""<<endl;
 cout<<"void ThreadRun"<<argv[3]<<"(Control process);"<<endl;
 cout<<"void CondorRun"<<argv[3]<<"(Control process);"<<endl;
 cout<<""<<endl;

 return 1;
}
