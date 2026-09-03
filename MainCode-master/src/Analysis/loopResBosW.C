#define loopResBosW_cxx
#include <iostream>
#include "Analysis/loopResBosW.h"

using namespace std;

loopResBosW::loopResBosW(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;

}

void loopResBosW::InputHist(HistsResBosW* &myhists)
{
 this->myhists = myhists;

}

void loopResBosW::InputTree(TreeForResBos *ResBosTree)
{
 this->ResBosTree = ResBosTree;
 this->RootNames = ResBosTree->RootNames;
 this->isFSR = ResBosTree->isFSR;

 this->FirstFile = ResBosTree->FirstFile;
 this->EndFile = ResBosTree->EndFile;

 this->OneFilePerJob = ResBosTree->OneFilePerJob;

 this->RootTypesForResBosW = ResBosTree->RootTypes;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ResBosTree->TotalEntries[ifile];
 }

}

void loopResBosW::ReadTree(int ifile)
{
 float Weight;

 isAntiLepton = false;
 isLepton = false;

 if(RootTypesForResBosW.at(ifile) == "wp") isAntiLepton = true; //Make the first file is W+
 if(RootTypesForResBosW.at(ifile) == "wm") isLepton = true;     //Make the second file is W-

 if(isAntiLepton) cout<<"Loop W+ sample"<<endl;
 if(isLepton) cout<<"Loop W- sample"<<endl;
 cout<<endl;

 for(long i = InitialEntry - 1; i < Nentries; i++){
   Sta_TotalNumber++;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   ResBosTree->GetEntry(ifile, i);
   Neutrino.SetPxPyPzE(ResBosTree->ElectronPx, ResBosTree->ElectronPy, ResBosTree->ElectronPz, ResBosTree->ElectronE);
   Lepton.SetPxPyPzE(ResBosTree->PositronPx, ResBosTree->PositronPy, ResBosTree->PositronPz, ResBosTree->PositronE);
   WBoson = Neutrino + Lepton;

   Weight = ResBosTree->Weight;

   WMT = CalculateTransverseMass(Lepton, Neutrino);

   /*
   if((Lepton.Eta() > 2.0 && Lepton.Eta() < 4.5)){//LHCb
     if(Lepton.Pt() > 20.0){
       if(isLepton) myhists->LeptonEtaAbs_LHCb->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
       if(isAntiLepton) myhists->AntiLeptonEtaAbs_LHCb->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
     }
   }*/

   myhists->E605_Q1->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 7.0 && WBoson.M() <= 7.2));
   myhists->E605_Q2->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 7.21 && WBoson.M() <= 7.41));
   myhists->E605_Q3->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 7.41 && WBoson.M() <= 7.61));
   myhists->E605_Q4->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 7.61 && WBoson.M() <= 7.81));
   myhists->E605_Q5->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 7.81 && WBoson.M() <= 8.01));
   myhists->E605_Q6->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 8.01 && WBoson.M() <= 8.21));
   myhists->E605_Q7->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 8.21 && WBoson.M() <= 8.41));
   myhists->E605_Q8->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 8.4 && WBoson.M() <= 8.6));
   myhists->E605_Q9->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 8.61 && WBoson.M() <= 8.81));
   myhists->E605_Q10->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 8.81 && WBoson.M() <= 9.01));
   myhists->E605_Q11->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 10.41 && WBoson.M() <= 10.61));
   myhists->E605_Q12->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 10.61 && WBoson.M() <= 10.81));
   myhists->E605_Q13->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 10.81 && WBoson.M() <= 11.01));
   myhists->E605_Q14->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 11.21 && WBoson.M() <= 11.41));
   myhists->E605_Q15->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 12.01 && WBoson.M() <= 12.21));
   myhists->E605_Q16->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 13.21 && WBoson.M() <= 13.41));
   myhists->E605_Q17->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 14.81 && WBoson.M() <= 15.01));
   myhists->E605_Q18->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (WBoson.M() >= 16.81 && WBoson.M() <= 17.01));


/*   if(isLepton) myhists->LeptonEta->at(iThread - 1)->Fill(Lepton.Eta(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEta->at(iThread - 1)->Fill(Lepton.Eta(), Weight);
   if(isLepton) myhists->WMinusRapidity->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
   if(isAntiLepton) myhists->WPlusRapidity->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
   if(isLepton) myhists->WMinusPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
   if(isAntiLepton) myhists->WPlusPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
   if(isLepton) myhists->WMinusE->at(iThread - 1)->Fill(WBoson.E(), Weight);
   if(isAntiLepton) myhists->WPlusE->at(iThread - 1)->Fill(WBoson.E(), Weight);
   if(isLepton) myhists->WMinusYPt->at(iThread - 1)->Fill(fabs(WBoson.Rapidity()), WBoson.Pt(), Weight);
   if(isAntiLepton) myhists->WPlusYPt->at(iThread - 1)->Fill(fabs(WBoson.Rapidity()), WBoson.Pt(), Weight);
   if(isLepton) myhists->WMinusYE->at(iThread - 1)->Fill(fabs(WBoson.Rapidity()), WBoson.E(), Weight);
   if(isAntiLepton) myhists->WPlusYE->at(iThread - 1)->Fill(fabs(WBoson.Rapidity()), WBoson.E(), Weight);

   if(isLepton) myhists->LeptonEtaMET->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Neutrino.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaMET->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Neutrino.Pt(), Weight);

   if(isLepton) myhists->LeptonEtaPt->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaPt->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Weight);

   if(isLepton) myhists->WMinusMET->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);
   if(isAntiLepton) myhists->WPlusMET->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);

   if(isLepton) myhists->LeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight);

   if(fabs(Lepton.Eta()) < 2.0){
     if(isLepton) myhists->WMinusMET_LowEta->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);
     if(isAntiLepton) myhists->WPlusMET_LowEta->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);
     if(isLepton) myhists->LeptonPt_LowEta->at(iThread - 1)->Fill(Lepton.Pt(), Weight);
     if(isAntiLepton) myhists->AntiLeptonPt_LowEta->at(iThread - 1)->Fill(Lepton.Pt(), Weight);
   }
   if(fabs(Lepton.Eta()) >= 2.0){
     if(isLepton) myhists->WMinusMET_HighEta->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);
     if(isAntiLepton) myhists->WPlusMET_HighEta->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);
     if(isLepton) myhists->LeptonPt_HighEta->at(iThread - 1)->Fill(Lepton.Pt(), Weight);
     if(isAntiLepton) myhists->AntiLeptonPt_HighEta->at(iThread - 1)->Fill(Lepton.Pt(), Weight);
   }


   if(fabs(Lepton.Eta()) > 2.5) continue;

   if(isLepton) myhists->LeptonEtaAbs->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);

   if(isLepton) myhists->LeptonEtaAbs2D->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs2D->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Weight);

   if(isLepton) myhists->LeptonEtaAbs3D_cut30->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Neutrino.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs3D_cut30->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Neutrino.Pt(), Weight);

   if(isLepton) myhists->LeptonEtaAbs3D_cut35->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Neutrino.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs3D_cut35->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Neutrino.Pt(), Weight);

   if(isLepton) myhists->LeptonEtaAbs3D_cut40->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Neutrino.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs3D_cut40->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Lepton.Pt(), Neutrino.Pt(), Weight);

   if(isLepton) myhists->LeptonEtaAbs_MT2D->at(iThread - 1)->Fill(fabs(Lepton.Eta()), WMT, Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs_MT2D->at(iThread - 1)->Fill(fabs(Lepton.Eta()), WMT, Weight);

   if(isLepton) myhists->LeptonEtaAbs_ut2D->at(iThread - 1)->Fill(fabs(Lepton.Eta()), WBoson.Pt(), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs_ut2D->at(iThread - 1)->Fill(fabs(Lepton.Eta()), WBoson.Pt(), Weight);

   if(Lepton.Pt() < 35){
     if(isLepton) myhists->LeptonEtaAbs_pt25_35->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
     if(isAntiLepton) myhists->AntiLeptonEtaAbs_pt25_35->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
   }

   if(Lepton.Pt() < 35) continue;
   if(isLepton) myhists->LeptonEtaAbs_pt35->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
   if(isAntiLepton) myhists->AntiLeptonEtaAbs_pt35->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight);
*/
 }

}

void loopResBosW::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!ResBosTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ResBosTree->fChain[RootNumber]->GetCurrentFile();
}

void loopResBosW::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete ResBosTree;

}

loopResBosW::~loopResBosW()
{
}
