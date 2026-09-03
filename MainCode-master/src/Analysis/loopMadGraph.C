#define loopMadGraph_cxx
#include <iostream>
#include "Analysis/loopMadGraph.h"

using namespace std;

loopMadGraph::loopMadGraph(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopMadGraph::InputHist(HistsMadGraph* &myhists)
{
 this->myhists = myhists;

}

void loopMadGraph::InputTree(TreeForMadGraph *MadGraphTree)
{
 this->MadGraphTree = MadGraphTree;
 this->RootNames = MadGraphTree->RootNames;

 this->FirstFile = MadGraphTree->FirstFile;
 this->EndFile = MadGraphTree->EndFile;

 this->OneFilePerJob = MadGraphTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = MadGraphTree->TotalEntries[ifile];
   MadGraphNEvent += TotalEntries[ifile];
 }

}

void loopMadGraph::ReadTree(int ifile)
{
 ThisFile = ifile;

 isZ = false;
 isWPlus = false;
 isWMinus = false;

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   MadGraphTree->GetEntry(ifile, iEvent);

   int lepton1_pid = 0;
   int lepton2_pid = 0;
   if(MadGraphTree->Particle_size == 4){
     lepton1_pid = MadGraphTree->Particle_PID[2];
     lepton2_pid = MadGraphTree->Particle_PID[3];
   }

   if(MadGraphTree->Particle_size == 5){
     lepton1_pid = MadGraphTree->Particle_PID[3];
     lepton2_pid = MadGraphTree->Particle_PID[4];
   }

   if(abs(lepton1_pid) == abs(lepton2_pid)) isZ = true;

   if(abs(lepton1_pid) != abs(lepton2_pid)){
     if(lepton1_pid == -11 || lepton2_pid == -11) isWPlus = true;
     if(lepton1_pid == 11 || lepton2_pid == 11) isWMinus = true;
   }

   isZEvents = isZ;
   isWEvents = (isWPlus || isWMinus);

   if(isZEvents) FillZEvents();
   if(isWEvents) FillWEvents();
 }

}

void loopMadGraph::FillZEvents()
{
   int lepton1_pid = 0;
   int lepton2_pid = 0;

   int ElectronID = 0;
   int PositronID = 0;

   if(MadGraphTree->Particle_size == 4){
     lepton1_pid = MadGraphTree->Particle_PID[2];
     lepton2_pid = MadGraphTree->Particle_PID[3];

     if(lepton1_pid == 11 && lepton2_pid == -11){
       ElectronID = 2;
       PositronID = 3;
     }
     else if(lepton1_pid == -11 && lepton2_pid == 11){
       ElectronID = 3;
       PositronID = 2;
     }
     else{
       cout<<"ERROR! unknown final state."<<endl;
     }
   }
   else if(MadGraphTree->Particle_size == 5){
     lepton1_pid = MadGraphTree->Particle_PID[3];
     lepton2_pid = MadGraphTree->Particle_PID[4];
     
     if(lepton1_pid == 11 && lepton2_pid == -11){
       ElectronID = 3;
       PositronID = 4;
     }
     else if(lepton1_pid == -11 && lepton2_pid == 11){
       ElectronID = 4;
       PositronID = 3;
     }
     else{
       cout<<"ERROR! unknown final state."<<endl;
     }
   }
   else{
     cout<<"ERROR! unknown initial state. Particle size = "<<MadGraphTree->Particle_size<<endl;
   }

   bool isZU = false;
   bool isZD = false;
   int quark1_pid = MadGraphTree->Particle_PID[0];
   if(abs(quark1_pid) == 2 || abs(quark1_pid) == 4){
     isZU = true;
   }
   else if(abs(quark1_pid) == 1 || abs(quark1_pid) == 3 || abs(quark1_pid) == 5){
     isZD = true;
   }

   Electron.SetPxPyPzE(MadGraphTree->Particle_Px[ElectronID], MadGraphTree->Particle_Py[ElectronID], MadGraphTree->Particle_Pz[ElectronID], MadGraphTree->Particle_E[ElectronID]);
   Positron.SetPxPyPzE(MadGraphTree->Particle_Px[PositronID], MadGraphTree->Particle_Py[PositronID], MadGraphTree->Particle_Pz[PositronID], MadGraphTree->Particle_E[PositronID]);

   if(ReweightID == 0){
     CrossSection = MadGraphTree->Event_Weight[0];
   }
   else{
     if(ReweightID <= MadGraphTree->Rwgt_size){
       CrossSection = MadGraphTree->Rwgt_Weight[ReweightID - 1];
     }
     else{
       cout<<"ERROR! wrong ReweightID, "<<ReweightID<<endl;
     }
   }

   ZBoson = Electron + Positron;

   double cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZBoson.Rapidity() / fabs(ZBoson.Rapidity());

   bool isF = false;
   bool isB = false;
   isF = (cos_theta > 0.0);
   isB = (cos_theta < 0.0);

   bool isElecC = (fabs(Electron.Eta()) < 2.47);
   bool isPosiC = (fabs(Positron.Eta()) < 2.47);
   bool isElecF = (fabs(Electron.Eta()) > 2.47) && (fabs(Electron.Eta()) < 3.6);
   bool isPosiF = (fabs(Positron.Eta()) > 2.47) && (fabs(Positron.Eta()) < 3.6);

   bool isCC = isElecC && isPosiC;
   bool isCF = (isElecC && isPosiF) || (isElecF && isPosiC);

   bool LepPtCut = false;
   if(ZBoson.M() > 80.0) LepPtCut = (Electron.Pt() > 30.0) && (Positron.Pt() > 30.0);
   if(ZBoson.M() < 80.0) LepPtCut = (Electron.Pt() > 15.0) && (Positron.Pt() > 15.0);

   TLorentzVector LeadingLepton, SubleadingLepton;
   if(Electron.Pt() > Positron.Pt()){
     LeadingLepton = Electron;
     SubleadingLepton = Positron;
   }
   else{
     LeadingLepton = Positron;
     SubleadingLepton = Electron;
   }

   bool isATLASHMDY = false;
   isATLASHMDY = (ZBoson.M() > 116.0)
              && (LeadingLepton.Pt() > 40.0)
              && (SubleadingLepton.Pt() > 30.0)
              && (fabs(LeadingLepton.Eta()) < 2.5)
              && (fabs(SubleadingLepton.Eta()) < 2.5);

   double Weight = CrossSection / (double)TotalEntries[ThisFile];

   myhists->Xsec_3D_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCC);
   myhists->Xsec_3D_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCF);
   myhists->Xsec_2D_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCC);
   myhists->Xsec_2D_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCF);
   myhists->Xsec_1D_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC);
   myhists->Xsec_1D_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF);

   myhists->ZMass_CosTheta_uu->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isZU);
   myhists->ZMass_CosTheta_dd->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isZD);
   myhists->ZMass_CosTheta->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight);

   myhists->ZMass_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->ZMass_HighMass_PerTeV->at(iThread - 1)->Fill(ZBoson.M(), Weight);

   myhists->ZMass_FullMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);

   myhists->ATLAS_Mll_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isATLASHMDY);
   myhists->ATLAS_costheta->at(iThread - 1)->Fill(cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_DilRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_costheta->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_DilRapidity->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_costheta_1->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_DilRapidity_1->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_costheta_2->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_DilRapidity_2->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_costheta_3->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_DilRapidity_3->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_HMDY_Xsec_3D->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * isATLASHMDY);

   myhists->ZMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->ZRapidity->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
   myhists->ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->LeptonEta->at(iThread - 1)->Fill(Electron.Eta(), Weight);
   myhists->LeptonEta->at(iThread - 1)->Fill(Positron.Eta(), Weight);
   myhists->LeptonPt->at(iThread - 1)->Fill(Electron.Pt(), Weight);
   myhists->LeptonPt->at(iThread - 1)->Fill(Electron.Pt(), Weight);

   myhists->FZMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);

   myhists->ZHighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->FZMass_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);

   myhists->CrossSection->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->CrossSectionF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->CrossSectionB->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FullCrossSection->at(iThread - 1)->Fill(ZBoson.M(), Weight);

   bool isE245_LHCb7TeV = (ZBoson.M() > 60.0 && ZBoson.M() < 120.0)
                       && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                       && (Electron.Eta() > 2.0 && Electron.Eta() < 4.5)
                       && (Positron.Eta() > 2.0 && Positron.Eta() < 4.5);

   bool isE246_LHCb8TeV = (ZBoson.M() > 60.0 && ZBoson.M() < 120.0)
                       && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                       && (Electron.Eta() > 2.0 && Electron.Eta() < 4.5)
                       && (Positron.Eta() > 2.0 && Positron.Eta() < 4.5);

   bool isE248_ATLAS7TeV = (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
                        && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                        && (fabs(Electron.Eta()) < 2.5)
                        && (fabs(Positron.Eta()) < 2.5);

   bool isE268_ATLAS7TeV = (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
                        && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0);

   bool isE250_LHCb8TeV = (ZBoson.M() > 60.0 && ZBoson.M() < 120.0)
                       && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                       && (Electron.Eta() > 2.0 && Electron.Eta() < 4.5)
                       && (Positron.Eta() > 2.0 && Positron.Eta() < 4.5);

   bool isE253_ATLAS8TeV = (fabs(ZBoson.Rapidity()) < 2.4)
                 && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
                 && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4);

   bool isE260_D01p96TeV = (ZBoson.M() > 71.0 && ZBoson.M() < 111.0);

   bool isE261_CDF1p96TeV = (ZBoson.M() > 66.0 && ZBoson.M() < 116.0);

   bool isE212_CMS13TeV = (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876)
                       && (Electron.Pt() > 25.0 && Positron.Pt() > 25.0)
                       && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4)
                       && (fabs(ZBoson.Rapidity()) < 2.4);

   bool isE218_LHCb13TeV = (ZBoson.M() > 60.0 && ZBoson.M() < 120.0)
                        && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                        && (Electron.Eta() > 2.0 && Electron.Eta() < 4.5)
                        && (Positron.Eta() > 2.0 && Positron.Eta() < 4.5);

   bool isE214_ATLAS8TeV = (ZBoson.M() > 46.0 && ZBoson.M() < 200.0)
                        && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                        && (fabs(Electron.Eta()) < 2.4)
                        && (fabs(Positron.Eta()) < 2.4);

   bool isE215_ATLAS5TeV = (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
                        && (Electron.Pt() > 20.0) && (Positron.Pt() > 20.0)
                        && (fabs(Electron.Eta()) < 2.5)
                        && (fabs(Positron.Eta()) < 2.5);

   myhists->E245_LHCb7TeV_Z->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isE245_LHCb7TeV);
   myhists->E246_LHCb8TeV_Z->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isE246_LHCb8TeV);
   myhists->E248_ATLAS7TeV_Z->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isE248_ATLAS7TeV);
   myhists->E268_ATLAS7TeV_Z->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isE268_ATLAS7TeV);
   myhists->E250_LHCb8TeV_Z->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isE250_LHCb8TeV);
   myhists->E253_ATLAS8TeV_ZPt1->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isE253_ATLAS8TeV * (ZBoson.M() > 46.0 && ZBoson.M() < 66.0));
   myhists->E253_ATLAS8TeV_ZPt2->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isE253_ATLAS8TeV * (ZBoson.M() > 66.0 && ZBoson.M() < 116.0));
   myhists->E253_ATLAS8TeV_ZPt3->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isE253_ATLAS8TeV * (ZBoson.M() > 116.0 && ZBoson.M() < 150.0));
   myhists->E260_D01p96TeV_Z->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isE260_D01p96TeV);
   myhists->E261_CDF1p96TeV_Z->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isE261_CDF1p96TeV);
   myhists->E212_CMS13TeV_Z->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isE212_CMS13TeV);
   myhists->E218_LHCb13TeV_Z->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isE218_LHCb13TeV);
   myhists->E214_ATLAS8TeV_Z1->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), cos_theta, Weight * isE214_ATLAS8TeV * (ZBoson.M() > 66.0 && ZBoson.M() < 80.0));
   myhists->E214_ATLAS8TeV_Z2->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), cos_theta, Weight * isE214_ATLAS8TeV * (ZBoson.M() > 80.0 && ZBoson.M() < 91.0));
   myhists->E214_ATLAS8TeV_Z3->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), cos_theta, Weight * isE214_ATLAS8TeV * (ZBoson.M() > 91.0 && ZBoson.M() < 102.0));
   myhists->E214_ATLAS8TeV_Z4->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), cos_theta, Weight * isE214_ATLAS8TeV * (ZBoson.M() > 102.0 && ZBoson.M() < 116.0));
   myhists->E214_ATLAS8TeV_Z5->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), cos_theta, Weight * isE214_ATLAS8TeV * (ZBoson.M() > 116.0 && ZBoson.M() < 150.0));
   myhists->E214_ATLAS8TeV_Z6->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), cos_theta, Weight * isE214_ATLAS8TeV * (ZBoson.M() > 150.0 && ZBoson.M() < 200.0));
   myhists->E215_ATLAS5TeV_Z->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isE215_ATLAS5TeV);
}

void loopMadGraph::FillWEvents()
{
   int lepton1_pid = 0;
   int lepton2_pid = 0;

   int LeptonID = 0;
   int NeutrinoID = 0;

   if(MadGraphTree->Particle_size == 4){
     lepton1_pid = MadGraphTree->Particle_PID[2];
     lepton2_pid = MadGraphTree->Particle_PID[3];

     if(abs(lepton1_pid) == 11 && abs(lepton2_pid) == 12){
       LeptonID = 2;
       NeutrinoID = 3;
     }
     else if(abs(lepton1_pid) == 12 && abs(lepton2_pid) == 11){
       LeptonID = 3;
       NeutrinoID = 2;
     }
     else{
       cout<<"ERROR! unknown final state."<<endl;
     }
   }
   else if(MadGraphTree->Particle_size == 5){
     lepton1_pid = MadGraphTree->Particle_PID[3];
     lepton2_pid = MadGraphTree->Particle_PID[4];

     if(abs(lepton1_pid) == 11 && abs(lepton2_pid) == 12){
       LeptonID = 3;
       NeutrinoID = 4;
     }
     else if(abs(lepton1_pid) == 12 && abs(lepton2_pid) == 11){
       LeptonID = 4;
       NeutrinoID = 3;
     }
     else{
       cout<<"ERROR! unknown final state."<<endl;
     }
   }
   else{
     cout<<"ERROR! unknown initial state. Particle size = "<<MadGraphTree->Particle_size<<endl;
   }

   Lepton.SetPxPyPzE(MadGraphTree->Particle_Px[LeptonID], MadGraphTree->Particle_Py[LeptonID], MadGraphTree->Particle_Pz[LeptonID], MadGraphTree->Particle_E[LeptonID]);
   Neutrino.SetPxPyPzE(MadGraphTree->Particle_Px[NeutrinoID], MadGraphTree->Particle_Py[NeutrinoID], MadGraphTree->Particle_Pz[NeutrinoID], MadGraphTree->Particle_E[NeutrinoID]);

   if(ReweightID == 0){
     CrossSection = MadGraphTree->Event_Weight[0];
   }
   else{
     if(ReweightID <= MadGraphTree->Rwgt_size){
       CrossSection = MadGraphTree->Rwgt_Weight[ReweightID - 1];
     }
     else{
       cout<<"ERROR! wrong ReweightID, "<<ReweightID<<endl;
     }
   }

   double Weight = CrossSection / (double)TotalEntries[ThisFile];

   WBoson = Lepton + Neutrino;

   WMT = CalculateTransverseMass(Lepton, Neutrino);

   bool SelectionCut = (Lepton.Pt() > 30.0)
                    && (Neutrino.Pt() > 30.0)
                    && (fabs(Lepton.Eta()) < 2.47)
                    //&& (WBoson.Pt() < 40.0)
                    && (WMT > 50);

   bool isLowMT = (WMT < 500.0);

   bool isWP = isWPlus;
   bool isWM = isWMinus;

   myhists->PositiveLeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->NegativeLeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->WPlusMTEta->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTEta->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);
   myhists->WPlusMTEta_Above100->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTEta_Above100->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->WPlusMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWM);
   myhists->WPlusMT_Above100->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMT_Above100->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWM);

   myhists->WPlusHighMassMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWP);
   myhists->WMinusHighMassMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWM);
   myhists->WPlusHighMassMT_PerTeV->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWP);
   myhists->WMinusHighMassMT_PerTeV->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWM);

   bool isE245_LHCb7TeV = (Lepton.Pt() > 20.0)
                       && (Lepton.Eta() > 2.0 && Lepton.Eta() < 4.5);

   bool isE248_ATLAS7TeV = (Lepton.Pt() > 25.0)
                        && (Neutrino.Pt() > 25.0)
                        && (fabs(Lepton.Eta()) < 2.5)
                        && (WMT > 40.0);

   bool isE268_ATLAS7TeV = (Lepton.Pt() > 25.0)
                        && (Neutrino.Pt() > 25.0)
                        && (fabs(Lepton.Eta()) < 2.5)
                        && (WMT > 40.0);

   bool isE249_CMS8TeV = (Lepton.Pt() > 25.0);

   bool isE250_LHCb8TeV = (Lepton.Pt() > 20.0)
                       && (Lepton.Eta() > 2.0 && Lepton.Eta() < 4.5);

   bool isE225_CDF1p8TeV = (Lepton.Pt() > 25.0) && (Lepton.Pt() < 900.0)
                        && (Neutrino.Pt() > 25.0);

   bool isE227_CDF1p96TeV = (Lepton.Pt() > 25.0) && (Lepton.Pt() < 980.0)
                         && (Neutrino.Pt() > 25.0);

   bool isE234_D01p96TeV = (Lepton.Pt() > 20.0)
                        && (Neutrino.Pt() > 20.0);

   bool isE266_CMS7TeV = (Lepton.Pt() > 35.0) && (Lepton.Pt() < 10000.0);

   bool isE267_CMS7TeV = (Lepton.Pt() > 35.0) && (Lepton.Pt() < 1000.0);

   bool isE281_D01p96TeV = (Lepton.Pt() > 25.0) && (Lepton.Pt() < 980.0)
                        && (Neutrino.Pt() > 25.0);

   bool isE211_ATLAS8TeV = (Lepton.Pt() > 25.0)
                        && (Neutrino.Pt() > 25.0)
                        && (fabs(Lepton.Eta()) < 2.4)
                        && (WMT > 40.0);

   bool isE215_ATLAS5TeV = (Lepton.Pt() > 25.0)
                        && (Neutrino.Pt() > 25.0)
                        && (fabs(Lepton.Eta()) < 2.5)
                        && (WMT > 40.0);

   bool isE217_LHCb8TeV = (Lepton.Pt() > 20.0)
                       && (Lepton.Eta() > 2.0 && Lepton.Eta() < 4.5);

   myhists->E245_LHCb7TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE245_LHCb7TeV);
   myhists->E245_LHCb7TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE245_LHCb7TeV);
   myhists->E248_ATLAS7TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE248_ATLAS7TeV);
   myhists->E248_ATLAS7TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE248_ATLAS7TeV);
   myhists->E268_ATLAS7TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE268_ATLAS7TeV);
   myhists->E268_ATLAS7TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE268_ATLAS7TeV);
   myhists->E249_CMS8TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE249_CMS8TeV);
   myhists->E249_CMS8TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE249_CMS8TeV);
   myhists->E250_LHCb8TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE250_LHCb8TeV);
   myhists->E250_LHCb8TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE250_LHCb8TeV);
   myhists->E225_CDF1p8TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE225_CDF1p8TeV);
   myhists->E225_CDF1p8TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE225_CDF1p8TeV);
   myhists->E227_CDF1p96TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE227_CDF1p96TeV);
   myhists->E227_CDF1p96TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE227_CDF1p96TeV);
   myhists->E234_D01p96TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE234_D01p96TeV);
   myhists->E234_D01p96TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE234_D01p96TeV);
   myhists->E266_CMS7TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE266_CMS7TeV);
   myhists->E266_CMS7TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE266_CMS7TeV);
   myhists->E267_CMS7TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE267_CMS7TeV);
   myhists->E267_CMS7TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE267_CMS7TeV);
   myhists->E281_D01p96TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE281_D01p96TeV);
   myhists->E281_D01p96TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE281_D01p96TeV);
   myhists->E211_ATLAS8TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE211_ATLAS8TeV);
   myhists->E211_ATLAS8TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE211_ATLAS8TeV);
   myhists->E215_ATLAS5TeV_WPlus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus * isE215_ATLAS5TeV);
   myhists->E215_ATLAS5TeV_WMinus->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus * isE215_ATLAS5TeV);
   myhists->E217_LHCb8TeV_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWPlus * isE217_LHCb8TeV);
   myhists->E217_LHCb8TeV_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isWMinus * isE217_LHCb8TeV);
}

void loopMadGraph::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!MadGraphTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete MadGraphTree->fChain[RootNumber]->GetCurrentFile();
}

void loopMadGraph::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete MadGraphTree;

}

loopMadGraph::~loopMadGraph()
{
}
