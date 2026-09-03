#define loopQBH_cxx
#include <iostream>
#include "QBH/loopQBH.h"

using namespace std;

loopQBH::loopQBH(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopQBH::InputHist(HistsQBH* &myhists)
{
 this->myhists = myhists;
}

void loopQBH::InputTree(TreeForQBH *QBHTree)
{
 this->QBHTree = QBHTree;
 this->RootNames = QBHTree->RootNames;

 this->FirstFile = QBHTree->FirstFile;
 this->EndFile = QBHTree->EndFile;

 this->OneFilePerJob = QBHTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = QBHTree->TotalEntries[ifile];
 }
}

void loopQBH::InputTree(TreeForPreQBH *PreQBHTree)
{
 isInputPreTree = true;

 this->PreQBHTree = PreQBHTree;
 this->RootNames = PreQBHTree->RootNames;

 this->FirstFile = PreQBHTree->FirstFile;
 this->EndFile = PreQBHTree->EndFile;

 this->OneFilePerJob = PreQBHTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PreQBHTree->TotalEntries[ifile];
 }

 this->QBHTree = new TreeForQBH();

 if(JustGenerateTree){
   if(!NtupleName.Contains("root")) NtupleName = PreQBHTree->SaveName;
   this->QBHTree->GenerateFile(NtupleName);
   //this->QBHTree->DefineTree(sysIter->second, sysIter->first);
 }
}

void loopQBH::InputNtupleName(TString NtupleName)
{
//this name will be override by the automatic name
 this->NtupleName = NtupleName;
}

void loopQBH::ReadTree(int ifile)
{

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   QBHTree->GetEntry(ifile, iEvent);
 }

}

void loopQBH::PreLoop(int ifile)
{

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

 }
}

bool loopQBH::FillEvents()
{
 SelectedEvent.ResetEvent();

 return true;
}

void EventQBH::ResetEvent()
{

}

void QBHLepton::ResetEvent()
{

}

void loopQBH::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;//yfu

 if(!isInputPreTree){
   if(!QBHTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   QBHTree->CloseFile(RootNumber);
   delete QBHTree->fChain[RootNumber]->GetCurrentFile();
 }

 if(isInputPreTree){
   if(!PreQBHTree->fChain[RootNumber])
    {
     cout<<"XXXXX**Runing: BIG ERROR!!! No File loaded!"<<endl;
     return;
    }
   PreQBHTree->CloseFile(RootNumber);
   delete PreQBHTree->fChain[RootNumber]->GetCurrentFile();
 }
}

void loopQBH::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(!isInputPreTree){
   if(EndFile == RootNames.size()) delete QBHTree;
 }

 if(isInputPreTree){
   if(EndFile == RootNames.size()) delete PreQBHTree;
 }

 if(JustGenerateTree){
   QBHTree->SaveFile();
 }

 //for multi-run the loop function
 if(isInputPreTree){
   delete QBHTree;
 }

}

loopQBH::~loopQBH()
{
}


