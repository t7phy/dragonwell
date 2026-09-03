#define loopFwdReco_cxx
#include <iostream>
#include "Analysis/loopFwdReco.h"

using namespace std;

loopFwdReco::loopFwdReco(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopFwdReco::InputHist(HistsFwdReco* &myhists)
{
 this->myhists = myhists;

}

void loopFwdReco::InputTree(TreeForFwdReco *FwdRecoTree)
{
 this->FwdRecoTree = FwdRecoTree;
 this->RootNames = FwdRecoTree->RootNames;

 this->FirstFile = FwdRecoTree->FirstFile;
 this->EndFile = FwdRecoTree->EndFile;

 this->OneFilePerJob = FwdRecoTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = FwdRecoTree->TotalEntries[ifile];
 }

}

void loopFwdReco::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   FwdRecoTree->GetEntry(ifile, iEvent);

//   cout<<"Thread No."<<iThread<<": Event Number: "<<FwdRecoTree->EventNumber<<endl;

   myhists->AverageMu->at(iThread - 1)->Fill(FwdRecoTree->AverageMu, 1);

   for(int k = 0; k < FwdRecoTree->fwdel_eta->size(); k++){
     FwdElectron.SetPtEtaPhiM(FwdRecoTree->fwdel_pt->at(k), FwdRecoTree->fwdel_eta->at(k), FwdRecoTree->fwdel_phi->at(k), 0.511 * 0.001);

     isfwdMatched = 0;
     for(int j = 0; j < FwdRecoTree->truthel_eta->size(); j++){
       TLorentzVector tmpTruthElectron;
       tmpTruthElectron.SetPtEtaPhiM(FwdRecoTree->truthel_pt->at(j), FwdRecoTree->truthel_eta->at(j), FwdRecoTree->truthel_phi->at(j), 0.511 * 0.001);
       if(FwdElectron.DeltaR(tmpTruthElectron) < 0.2) isfwdMatched = 1;
     }

//     isfwdMatched = FwdRecoTree->fwdel_truthMatched->at(k);
//     isfwdMatched = 1;  

     recoFwdClusterPt = FwdRecoTree->fwdel_clpt->at(k);

//     myhists->FwdElectronEta->at(iThread - 1)->Fill(fabs(FwdElectron.Eta()), isfwdMatched);
     myhists->FwdElectronEta->at(iThread - 1)->Fill(FwdElectron.Eta(), isfwdMatched);
     myhists->FwdElectronPhi->at(iThread - 1)->Fill(FwdElectron.Phi(), isfwdMatched);
     myhists->FwdElectronPt->at(iThread - 1)->Fill(FwdElectron.Pt(), isfwdMatched);
     myhists->FwdElectronEt->at(iThread - 1)->Fill(recoFwdClusterPt, isfwdMatched);

   }

   myhists->RecoSize->at(iThread - 1)->Fill(FwdRecoTree->fwdel_eta->size(), 1);

   int TruthCount = 0;
   for(int j = 0; j < FwdRecoTree->truthel_eta->size(); j++){
     if(!(FwdRecoTree->truthel_Region->at(j) == 2)) continue;

     TruthCount++;

     TruthElectron.SetPtEtaPhiM(FwdRecoTree->truthel_pt->at(j), FwdRecoTree->truthel_eta->at(j), FwdRecoTree->truthel_phi->at(j), 0.511 * 0.001);
//     if(fabs(TruthElectron.Eta()) > 3.17 && fabs(TruthElectron.Eta()) < 3.35) continue;

     isMatched = FwdRecoTree->truthel_truthMatched->at(j);

     myhists->TruthElectronEta->at(iThread - 1)->Fill(TruthElectron.Eta(), 1);
     myhists->TruthElectronPhi->at(iThread - 1)->Fill(TruthElectron.Phi(), 1);
     myhists->TruthElectronEt->at(iThread - 1)->Fill(TruthElectron.Et(), 1);
     myhists->TruthElectronPt->at(iThread - 1)->Fill(TruthElectron.Pt(), 1);
     myhists->TruthElectronEtEta->at(iThread - 1)->Fill(TruthElectron.Et(), TruthElectron.Eta(), 1);
     myhists->TruthElectronEtaPhi->at(iThread - 1)->Fill(TruthElectron.Eta(), TruthElectron.Phi(), 1);
     myhists->TruthElectronEtaAbs->at(iThread - 1)->Fill(fabs(TruthElectron.Eta()), 1);

     myhists->MatchedElectronEta->at(iThread - 1)->Fill(TruthElectron.Eta(), isMatched);
     myhists->MatchedElectronPhi->at(iThread - 1)->Fill(TruthElectron.Phi(), isMatched);
     myhists->MatchedElectronEt->at(iThread - 1)->Fill(TruthElectron.Et(), isMatched);
     myhists->MatchedElectronPt->at(iThread - 1)->Fill(TruthElectron.Pt(), isMatched);
     myhists->MatchedElectronEtEta->at(iThread - 1)->Fill(TruthElectron.Et(), TruthElectron.Eta(), isMatched);
     myhists->MatchedElectronEtaPhi->at(iThread - 1)->Fill(TruthElectron.Eta(), TruthElectron.Phi(), isMatched);
     myhists->MatchedElectronEtaAbs->at(iThread - 1)->Fill(fabs(TruthElectron.Eta()), isMatched);

     deltaE = FwdRecoTree->truthel_deltaE->at(j);
     deltaPt = FwdRecoTree->truthel_deltaPt->at(j);
     deltaEt = FwdRecoTree->truthel_deltaEt->at(j);

     if(isTest) cout<<"electron eta: "<<TruthElectron.Eta()<<endl;
//     if(TruthElectron.Phi() > 3.14) cout<<"Event: "<<iEvent<<" Event Number: "<<FwdRecoTree->EventNumber<<" electron phi: "<<TruthElectron.Phi()<<endl;

     if(FwdRecoTree->truthel_pt->at(j) < 20000) continue;
     if(fabs(TruthElectron.Eta()) > 3.17 && fabs(TruthElectron.Eta()) < 3.35) continue;

     myhists->EResolutionEta->at(iThread - 1)->Fill(deltaE, isMatched);
     myhists->EResolutionEta->at(iThread - 1)->FillResolution(fabs(TruthElectron.Eta()));

     myhists->EtResolutionEta->at(iThread - 1)->Fill(deltaEt, isMatched);
     myhists->EtResolutionEta->at(iThread - 1)->FillResolution(fabs(TruthElectron.Eta()));

     myhists->PtResolutionEta->at(iThread - 1)->Fill(deltaPt, isMatched);
     myhists->PtResolutionEta->at(iThread - 1)->FillResolution(fabs(TruthElectron.Eta()));

     myhists->PtResolutionPt->at(iThread - 1)->Fill(deltaPt, isMatched);
     myhists->PtResolutionPt->at(iThread - 1)->FillResolution(fabs(TruthElectron.Pt()));

     if(FwdRecoTree->AverageMu < 30) myhists->PtResolutionEta_LowMu->at(iThread - 1)->Fill(deltaPt, isMatched);
     if(FwdRecoTree->AverageMu < 30) myhists->PtResolutionEta_LowMu->at(iThread - 1)->FillResolution(fabs(TruthElectron.Eta()));

     if(FwdRecoTree->AverageMu > 30) myhists->PtResolutionEta_HighMu->at(iThread - 1)->Fill(deltaPt, isMatched);
     if(FwdRecoTree->AverageMu > 30) myhists->PtResolutionEta_HighMu->at(iThread - 1)->FillResolution(fabs(TruthElectron.Eta()));

   }
   myhists->TruthSize->at(iThread - 1)->Fill(TruthCount, 1);

 }

}

void loopFwdReco::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!FwdRecoTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete FwdRecoTree->fChain[RootNumber]->GetCurrentFile();
}

void loopFwdReco::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete FwdRecoTree;

}

loopFwdReco::~loopFwdReco()
{
}
