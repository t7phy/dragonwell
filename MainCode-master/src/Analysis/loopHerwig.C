#define loopHerwig_cxx
#include <iostream>
#include "Analysis/loopHerwig.h"

using namespace std;

loopHerwig::loopHerwig(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopHerwig::InputHist(HistsHerwig* &myhists)
{
 this->myhists = myhists;

}

void loopHerwig::InputTree(TreeForHerwig *HerwigTree)
{
 this->HerwigTree = HerwigTree;
 this->RootNames = HerwigTree->RootNames;

 this->FirstFile = HerwigTree->FirstFile;
 this->EndFile = HerwigTree->EndFile;

 this->OneFilePerJob = HerwigTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = HerwigTree->TotalEntries[ifile];
 }

}

void loopHerwig::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   HerwigTree->GetEntry(ifile, iEvent);

   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(HerwigTree->LeptonPx, HerwigTree->LeptonPy, HerwigTree->LeptonPz, HerwigTree->LeptonE);
   Positron.SetPxPyPzE(HerwigTree->AntiLeptonPx, HerwigTree->AntiLeptonPy, HerwigTree->AntiLeptonPz, HerwigTree->AntiLeptonE);

   ZBoson = Electron + Positron;

   if(isPDFReweight) PDFReweightFactor = myPDFReweight->GetPDFReweightFactor(HerwigTree->PartonID[0], HerwigTree->PartonID[1], HerwigTree->PartonFraction[0], HerwigTree->PartonFraction[1], ZBoson.M());

   if(isTest){
     cout<<HerwigTree->ZPx<<" "<<HerwigTree->ZPy<<" "<<HerwigTree->ZPz<<" "<<HerwigTree->ZE<<endl;
     cout<<HerwigTree->LeptonPx<<" "<<HerwigTree->LeptonPy<<" "<<HerwigTree->LeptonPz<<" "<<HerwigTree->LeptonE<<endl;
     cout<<HerwigTree->AntiLeptonPx<<" "<<HerwigTree->AntiLeptonPy<<" "<<HerwigTree->AntiLeptonPz<<" "<<HerwigTree->AntiLeptonE<<endl;
     cout<<"PDF reweight factor = "<<PDFReweightFactor<<endl;
     cout<<endl;
   }

//   if(isTest) cout<<"ZPt = "<<ZBoson.Pt()<<" ZY = "<<ZBoson.Rapidity()<<" ZMass = "<<ZBoson.M()<<endl;

   double ZRapidity=ZBoson.Rapidity();

   double Weight = HerwigTree->Weight * PDFReweightFactor;

   cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZRapidity / fabs(ZRapidity);
   phi = calculate_phi(Electron, Positron, 13000.0) * ZRapidity / fabs(ZRapidity);
   phi_eta = calculate_phi_eta(Electron, Positron);

   if(cos_theta > 1) cos_theta = 1.0;
   if(cos_theta < -1) cos_theta = -1.0;

   myhists->ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->ZRapidity->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
   myhists->ZMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->CosTheta->at(iThread - 1)->Fill(cos_theta, Weight);
   myhists->CollinsPhi->at(iThread - 1)->Fill(phi, Weight);
   myhists->plot_phi_eta->at(iThread - 1)->Fill(phi_eta, Weight);
   myhists->leptonPt->at(iThread - 1)->Fill(Electron.Pt(), Weight);
   myhists->leptonPt->at(iThread - 1)->Fill(Positron.Pt(), Weight);
   myhists->leptonEta->at(iThread - 1)->Fill(Electron.Eta(), Weight);
   myhists->leptonEta->at(iThread - 1)->Fill(Positron.Eta(), Weight);

   myhists->A0_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A0_ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->A1_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A1_ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->A2_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A2_ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->A3_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A3_ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->A4_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A4_ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->L0_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->L0_ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);

   if(cos_theta>0){
     myhists->FZmass->at(iThread - 1)->Fill(ZBoson.M(),Weight);
   }
   if(cos_theta<0){
     myhists->BZmass->at(iThread - 1)->Fill(ZBoson.M(),Weight);
   }

   if(Electron.Pt()<25 || Positron.Pt()<25) continue;
   if(fabs(Electron.Eta()) > 2.5 && fabs(Electron.Eta()) < 4.9) ieta1=1;//1F
   if(fabs(Electron.Eta()) < 2.5) ieta1=2;                              //1C
   if(fabs(Positron.Eta()) > 2.5 && fabs(Positron.Eta()) < 4.9) ieta2=3;//2F
   if(fabs(Positron.Eta()) < 2.5) ieta2=4;                              //2C

//CC
   if(ieta1 * ieta2 == 8){
     if(cos_theta>0){
       myhists->FZmass_CC->at(iThread - 1)->Fill(ZBoson.M(),Weight);
     }
     if(cos_theta<0){
       myhists->BZmass_CC->at(iThread - 1)->Fill(ZBoson.M(),Weight);
     }
   }
//CF
   if(ieta1 * ieta2 == 4 || ieta1 * ieta2 == 6){
     if(cos_theta>0){
       myhists->FZmass_CF->at(iThread - 1)->Fill(ZBoson.M(),Weight);
     }
     if(cos_theta<0){
       myhists->BZmass_CF->at(iThread - 1)->Fill(ZBoson.M(),Weight);
     }
   }

 }

}

void loopHerwig::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!HerwigTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete HerwigTree->fChain[RootNumber]->GetCurrentFile();
}

void loopHerwig::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete HerwigTree;

}

loopHerwig::~loopHerwig()
{
}
