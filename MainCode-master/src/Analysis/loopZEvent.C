#define loopZEvent_cxx
#include <iostream>
#include "Analysis/loopZEvent.h"

using namespace std;

loopZEvent::loopZEvent(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopZEvent::InputHist(HistsZEvent* &myhists)
{
 this->myhists = myhists;

}

void loopZEvent::InputTree(TreeForZEvent *ZEventTree)
{
 this->ZEventTree = ZEventTree;
 this->RootNames = ZEventTree->RootNames;

 this->FirstFile = ZEventTree->FirstFile;
 this->EndFile = ZEventTree->EndFile;

 this->OneFilePerJob = ZEventTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ZEventTree->TotalEntries[ifile];
 }

}

void loopZEvent::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   ZEventTree->GetEntry(ifile, iEvent);

   //Retrieve information from root files:


   /////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //  Fill histograms:                                                                                       //
   //                                                                                                         //
   //  1d histogram example:                                                                                  //
   //  myhists->ZMass->HistPtr(iThread - 1)->Fill(ZBoson.M(), Weight);                                        //
   //                                                                                                         //
   //  2d histogram example:                                                                                  //
   //  myhists->ZMass_ZY->HistPtr(iThread - 1)->Fill(ZBoson.M(), ZBoson.Rapidity(), Weight);                  //
   //                                                                                                         //
   //  3d histogram example:                                                                                  //
   //  myhists->ZMass_ZY_QT->HistPtr(iThread - 1)->Fill(ZBoson.M(), ZBoson.Rapidity(), ZBoson.Pt(), Weight);  //
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////



 }

}

void loopZEvent::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!ZEventTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ZEventTree->fChain[RootNumber]->GetCurrentFile();
}

void loopZEvent::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete ZEventTree;

}

loopZEvent::~loopZEvent()
{
}
