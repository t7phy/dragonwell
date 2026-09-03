#define loopResBosD0_cxx
#include <iostream>
#include "Analysis/loopResBosD0.h"

using namespace std;

loopResBosD0::loopResBosD0(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopResBosD0::InputHist(HistsResBosD0* &myhists)
{
 this->myhists = myhists;

}

void loopResBosD0::InputTree(TreeForResBosD0 *ResBosD0Tree)
{
 this->ResBosD0Tree = ResBosD0Tree;
 this->RootNames = ResBosD0Tree->RootNames;
 this->isFSR = ResBosD0Tree->isFSR;
 this->isDilution = ResBosD0Tree->isDilution;

 this->FirstFile = ResBosD0Tree->FirstFile;
 this->EndFile = ResBosD0Tree->EndFile;

 this->OneFilePerJob = ResBosD0Tree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ResBosD0Tree->TotalEntries[ifile];
 }

}

void loopResBosD0::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   ResBosD0Tree->GetEntry(ifile, iEvent);

   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(ResBosD0Tree->ElectronPx, ResBosD0Tree->ElectronPy, ResBosD0Tree->ElectronPz, ResBosD0Tree->ElectronE);
   Positron.SetPxPyPzE(ResBosD0Tree->PositronPx, ResBosD0Tree->PositronPy, ResBosD0Tree->PositronPz, ResBosD0Tree->PositronE);

   Weight = ResBosD0Tree->Weight;
   if(!isfinite(Weight)) continue;

   ZBoson = Electron + Positron;

   double ZRapidity=ZBoson.Rapidity();

   cos_theta = calculate_theta(ZBoson, Electron, Positron);
   phi = calculate_phi(Electron, Positron, (double)ECM / 2.0);
   phi_eta = calculate_phi_eta(Electron, Positron);

   if(cos_theta > 1) cos_theta = 1.0;
   if(cos_theta < -1) cos_theta = -1.0;

   bool isF = false;
   bool isB = false;
   isF = (cos_theta > 0);
   isB = (cos_theta < 0);

   int isWrong;
   if(isDilution){
     bool isUUB = false;
     bool isDDB = false;
     bool isSSB = false;
     bool isCCB = false;
     bool isBBB = false;
     bool isGG = false;
     isUUB = (fabs(fabs(ResBosD0Tree->Type) - 1.0) < 1e-10);
     isDDB = (fabs(fabs(ResBosD0Tree->Type) - 2.0) < 1e-10);
     isSSB = (fabs(fabs(ResBosD0Tree->Type) - 3.0) < 1e-10);
     isCCB = (fabs(fabs(ResBosD0Tree->Type) - 4.0) < 1e-10);
     isBBB = (fabs(fabs(ResBosD0Tree->Type) - 5.0) < 1e-10);
     isGG = isSSB || isCCB || isBBB;

     if(isTest){
       if(isUUB) cout<<"Initial state: uub, Type = "<<ResBosD0Tree->Type<<endl;
       if(isDDB) cout<<"Initial state: ddb, Type = "<<ResBosD0Tree->Type<<endl;
       if(isSSB) cout<<"Initial state: ssb, Type = "<<ResBosD0Tree->Type<<endl;
       if(isCCB) cout<<"Initial state: ccb, Type = "<<ResBosD0Tree->Type<<endl;
       if(isBBB) cout<<"Initial state: bbb, Type = "<<ResBosD0Tree->Type<<endl;
     }

     if(ResBosD0Tree->Type > 0){
       isWrong = 0;
     }
     if(ResBosD0Tree->Type < 0){
       isWrong = 1;
     }

     double CosThetaQ;
     if(ResBosD0Tree->Type > 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron);
     if(ResBosD0Tree->Type < 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron) * (-1.0);
     double PhiQ;
     if(ResBosD0Tree->Type > 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0);
     if(ResBosD0Tree->Type < 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0) * (-1.0);

     bool isQuarkF = false;
     bool isQuarkB = false;
     isQuarkF = (CosThetaQ > 0);
     isQuarkB = (CosThetaQ < 0);

     myhists->ZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
     myhists->ZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
     myhists->ZMass_ZY_QT_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isSSB);
     myhists->ZMass_ZY_QT_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCCB);
     myhists->ZMass_ZY_QT_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isBBB);

     myhists->FZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isUUB);
     myhists->BZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isUUB);
     myhists->FZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isDDB);
     myhists->BZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isDDB);

     myhists->ZMass_ZY_QT_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
     myhists->ZMass_ZY_QT_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * isWrong);
     myhists->ZMass_ZY_QT_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
     myhists->ZMass_ZY_QT_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * isWrong);

     myhists->ZMass_ZY_QT_uu_right->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * (!isWrong));
     myhists->ZMass_ZY_QT_dd_right->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * (!isWrong));

   }

   myhists->ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);
   myhists->FZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
   myhists->BZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);

 }

}

void loopResBosD0::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!ResBosD0Tree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ResBosD0Tree->fChain[RootNumber]->GetCurrentFile();
}

void loopResBosD0::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete ResBosD0Tree;

}

loopResBosD0::~loopResBosD0()
{
}
