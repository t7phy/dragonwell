#define loopMC_cxx
#include <iostream>
#include "Analysis/loopMC.h"

using namespace std;

loopMC::loopMC()
{
 Sta_TotalNumber = 0;

 isThread = false;

 isTest = false;
}

void loopMC::Initial(int ifile)
{
 if(isThread){
   if(!OneFilePerJob){
     NEvents = TotalEntries[ifile] / TotalThread;

     InitialEntry = (iThread - 1) * NEvents + 1;
     Nentries = iThread * NEvents;
     if(iThread == TotalThread) Nentries = TotalEntries[ifile];
   }
   if(OneFilePerJob){
     InitialEntry = 1;
     Nentries = TotalEntries[ifile];
   }
 }
 else{
   InitialEntry = 1;
   Nentries = TotalEntries[ifile];
   iThread = 1;
 }

 if(isTest){
   Nentries = InitialEntry + 10;
   if(Nentries > TotalEntries[ifile]) Nentries = TotalEntries[ifile];
 }

}

void loopMC::InputThreadInfo(int TotalThread, int iThread)
{
 isThread = true;

 this->TotalThread = TotalThread;
 this->iThread = iThread;
}

void loopMC::OutputFileInfo()
{
 if(!OneFilePerJob){
   myLog<<LOG_INFO<<"There is "<<(EndFile - FirstFile)<<" files."<<endl;
   for(int i = FirstFile; i < EndFile; i++){
     myLog<<LOG_INFO<<RootNames.at(i)<<endl;
   }
 }

}

void loopMC::ConfigCut(const char* CutFile)
{
 if((TString)CutFile == "0"){
   CutInfo.push_back("0");
   CutLeft.push_back(0);
   CutRight.push_back(0);

   if(iThread == 1 || !isThread){
     cout<<endl;
     cout<<"Not impose global cut."<<endl;
     cout<<endl;
   }
   return;
 }

 ifstream cutfile;
  cutfile.open(CutFile, ios::in);

 if(iThread == 1 || !isThread){
   cout<<endl;
   cout<<"Config cut file: "<<CutFile<<endl;
   cout<<endl;
 }

 TString skip;
 double config;
 string FileLine;
 while(cutfile>>skip){
  getline(cutfile, FileLine);
  CutInfo.push_back(skip);
  if(iThread == 1 || !isThread) cout<<skip<<FileLine<<endl;

  cutfile>>config;
  getline(cutfile, FileLine);
  CutLeft.push_back(config);
  if(iThread == 1 || !isThread) cout<<config<<FileLine<<endl;

  cutfile>>config;
  getline(cutfile, FileLine);
  CutRight.push_back(config);
  if(iThread == 1 || !isThread) cout<<config<<FileLine<<endl;

  if(iThread == 1 || !isThread) cout<<endl;
 }

}

void loopMC::InputPDFReweightInfo(const char* oldPDFName, const char* newPDFName, int oldPDFset, int newPDFset)
{
 isPDFReweight = true;
 
 this->oldPDFName = (TString)oldPDFName;
 this->newPDFName = (TString)newPDFName;
 
 this->oldPDFset = oldPDFset;
 this->newPDFset = newPDFset;
 
 myPDFReweight = new PDFReweight();
 myPDFReweight->InitialPDFReweightFactor(oldPDFName, newPDFName, oldPDFset, newPDFset);
}

void loopMC::InitialPDFInfo(const char* oldPDFName, int oldPDFset)
{
 this->oldPDFName = (TString)oldPDFName;
 this->oldPDFset = oldPDFset;

 myPDFReweight = new PDFReweight();
 myPDFReweight->InitialPDF(oldPDFName, oldPDFset);
}

void loopMC::End()
{
 cout<<"Thread No."<<this->iThread<<" **Running: Free Rootfile: "<<this->Sta_TotalNumber<<endl;
}

loopMC::~loopMC()
{
}

