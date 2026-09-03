#define loopPythiaW_cxx
#include <iostream>
#include "Analysis/loopPythiaW.h"

using namespace std;

loopPythiaW::loopPythiaW(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopPythiaW::InputHist(HistsPythiaW* &myhists)
{
 this->myhists = myhists;

}

void loopPythiaW::InputTree(TreeForPythiaW *PythiaWTree)
{
 this->PythiaWTree = PythiaWTree;
 this->RootNames = PythiaWTree->RootNames;

 this->FirstFile = PythiaWTree->FirstFile;
 this->EndFile = PythiaWTree->EndFile;

 this->OneFilePerJob = PythiaWTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PythiaWTree->TotalEntries[ifile];
 }

}

void loopPythiaW::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   PythiaWTree->GetEntry(ifile, iEvent);

   int ieta1=0;
   int ieta2=0;

   Muon.SetPxPyPzE(PythiaWTree->MuonPx, PythiaWTree->MuonPy, PythiaWTree->MuonPz, PythiaWTree->MuonE);
   Neutrino.SetPxPyPzE(PythiaWTree->NeutrinoPx, PythiaWTree->NeutrinoPy, PythiaWTree->NeutrinoPz, PythiaWTree->NeutrinoE);
   WBoson.SetPxPyPzE(PythiaWTree->WbosonPx, PythiaWTree->WbosonPy, PythiaWTree->WbosonPz, PythiaWTree->WbosonE);

//   WBoson = Muon + Neutrino;

   if(isPDFReweight) PDFReweightFactor = myPDFReweight->GetPDFReweightFactor(PythiaWTree->QuarkFlavour[0], PythiaWTree->QuarkFlavour[1], PythiaWTree->QuarkE[0] / 6500, PythiaWTree->QuarkE[1] / 6500, WBoson.M());

   if(isTest){
     cout<<"PDF reweight factor = "<<PDFReweightFactor<<endl;
     cout<<endl;
   }

//   if(isTest) cout<<"ZPt = "<<ZBoson.Pt()<<" ZY = "<<ZBoson.Rapidity()<<" ZMass = "<<ZBoson.M()<<endl;

   double WRapidity=WBoson.Rapidity();

   double Weight = 1.0 * PDFReweightFactor;

   if(fabs(PythiaWTree->QuarkFlavour[0]) == 2 || fabs(PythiaWTree->QuarkFlavour[0]) == 1){
     myhists->WPt_ud->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
     myhists->WRapidity_ud->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
     myhists->WMass_ud->at(iThread - 1)->Fill(WBoson.M(), Weight);
     myhists->LeptonEta_ud->at(iThread - 1)->Fill(Muon.Eta(), Weight);
     if(Muon.Pt() > 20 && Muon.Eta() > 2.0 && Muon.Eta() < 4.5) myhists->LeptonEta_LHCb_ud->at(iThread - 1)->Fill(Muon.Eta(), Weight);
   }
   if(fabs(PythiaWTree->QuarkFlavour[0]) == 3 || fabs(PythiaWTree->QuarkFlavour[0]) == 4){
     myhists->WPt_cs->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
     myhists->WRapidity_cs->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
     myhists->WMass_cs->at(iThread - 1)->Fill(WBoson.M(), Weight);
     myhists->LeptonEta_cs->at(iThread - 1)->Fill(Muon.Eta(), Weight);
     if(Muon.Pt() > 20 && Muon.Eta() > 2.0 && Muon.Eta() < 4.5) myhists->LeptonEta_LHCb_cs->at(iThread - 1)->Fill(Muon.Eta(), Weight);
   }
   if((fabs(PythiaWTree->QuarkFlavour[0]) == 2 && fabs(PythiaWTree->QuarkFlavour[1]) == 3) || (fabs(PythiaWTree->QuarkFlavour[0]) == 3 && fabs(PythiaWTree->QuarkFlavour[1]) == 2)){
     myhists->WPt_us->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
     myhists->WRapidity_us->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
     myhists->WMass_us->at(iThread - 1)->Fill(WBoson.M(), Weight);
     myhists->LeptonEta_us->at(iThread - 1)->Fill(Muon.Eta(), Weight);
     if(Muon.Pt() > 20 && Muon.Eta() > 2.0 && Muon.Eta() < 4.5) myhists->LeptonEta_LHCb_us->at(iThread - 1)->Fill(Muon.Eta(), Weight);
   }


 }

}

void loopPythiaW::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!PythiaWTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete PythiaWTree->fChain[RootNumber]->GetCurrentFile();
}

void loopPythiaW::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete PythiaWTree;

}

loopPythiaW::~loopPythiaW()
{
}
