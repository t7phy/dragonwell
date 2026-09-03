#define loopResBos_cxx
#include <iostream>
#include "Analysis/loopResBos.h"

using namespace std;

loopResBos::loopResBos(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;

}

void loopResBos::InputHist(HistsResBos* &myhists)
{
 this->myhists = myhists;

}

void loopResBos::InputTree(TreeForResBos *ResBosTree)
{
 this->ResBosTree = ResBosTree;
 this->RootNames = ResBosTree->RootNames;
 this->isFSR = ResBosTree->isFSR;
 this->isDilution = ResBosTree->isDilution;
 
 this->FirstFile = ResBosTree->FirstFile;
 this->EndFile = ResBosTree->EndFile;

 this->OneFilePerJob = ResBosTree->OneFilePerJob;

 this->RootTypesForResBos = ResBosTree->RootTypes;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ResBosTree->TotalEntries[ifile];
 }

}

void loopResBos::InputECM(double ECM)
{
 this->ECM = ECM;
}

void loopResBos::InputScaleAndSmear(double Scale, double Smear)
{
 doCalibration = true;

 this->Scale = Scale;
 this->Smear = Smear;
}

void loopResBos::ReadTree(int ifile)
{
 TRandom3 random(0);

 bool isZU = false;
 bool isZD = false;

 if(RootTypesForResBos.at(ifile) == "zu") isZU = true;
 if(RootTypesForResBos.at(ifile) == "zd") isZD = true;

 for(long i = InitialEntry - 1; i < Nentries; i++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }

   int ieta1=0;
   int ieta2=0;

   ResBosTree->GetEntry(ifile, i);
   Electron.SetPxPyPzE(ResBosTree->ElectronPx, ResBosTree->ElectronPy, ResBosTree->ElectronPz, ResBosTree->ElectronE);
   Positron.SetPxPyPzE(ResBosTree->PositronPx, ResBosTree->PositronPy, ResBosTree->PositronPz, ResBosTree->PositronE);
   if(isFSR) Gamma1.SetPxPyPzE(ResBosTree->Photon1Px, ResBosTree->Photon1Py, ResBosTree->Photon1Pz, ResBosTree->Photon1E);
   if(isFSR) Gamma2.SetPxPyPzE(ResBosTree->Photon2Px, ResBosTree->Photon2Py, ResBosTree->Photon2Pz, ResBosTree->Photon2E);

   if(isFSR && Electron.DeltaR(Gamma1) < 0.1) Electron = Electron;

   Weight = ResBosTree->Weight;

   if(!isfinite(Weight)) continue;
//Some special options//
   if(isAddEnergyScale) AddEnergyScale(Electron, Positron);
   if(doCalibration){
     myGausRandom = random.Gaus(0, 1);
     Electron = Electron * Scale * (1 + Smear * myGausRandom);
     myGausRandom = random.Gaus(0, 1);
     Positron = Positron * Scale * (1 + Smear * myGausRandom);
   }
///////////////////////

   ZBoson = Electron + Positron;

   if(isTest){
     cout<<ResBosTree->ZPx<<" "<<ResBosTree->ZPy<<" "<<ResBosTree->ZPz<<" "<<ResBosTree->ZE<<endl;
     cout<<ResBosTree->PositronPx<<" "<<ResBosTree->PositronPy<<" "<<ResBosTree->PositronPz<<" "<<ResBosTree->PositronE<<endl;
     cout<<ResBosTree->ElectronPx<<" "<<ResBosTree->ElectronPy<<" "<<ResBosTree->ElectronPz<<" "<<ResBosTree->ElectronE<<endl;
     cout<<ResBosTree->Photon1Px<<" "<<ResBosTree->Photon1Py<<" "<<ResBosTree->Photon1Pz<<" "<<ResBosTree->Photon1E<<endl;
     cout<<ResBosTree->Photon2Px<<" "<<ResBosTree->Photon2Py<<" "<<ResBosTree->Photon2Pz<<" "<<ResBosTree->Photon2E<<endl;
     cout<<endl;
   }

   double ZRapidity=ZBoson.Rapidity();

   cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZRapidity / fabs(ZRapidity);
   phi = calculate_phi(Electron, Positron, (double)ECM / 2.0) * ZRapidity / fabs(ZRapidity);
   phi_eta = calculate_phi_eta(Electron, Positron);

   if(cos_theta > 1) cos_theta = 1.0;
   if(cos_theta < -1) cos_theta = -1.0;

   bool isCC = false;
   bool isCF = false;
   bool isLHCb = false;
   bool isATLASZPt = false;
   if(fabs(Electron.Eta()) > 2.5 && fabs(Electron.Eta()) < 4.9) ieta1=1;//1F
   if(fabs(Electron.Eta()) < 2.5) ieta1=2;                              //1C
   if(fabs(Positron.Eta()) > 2.5 && fabs(Positron.Eta()) < 4.9) ieta2=3;//2F
   if(fabs(Positron.Eta()) < 2.5) ieta2=4;                              //2C

   isCC = (ieta1 * ieta2 == 8) && (Electron.Pt() > 25 && Positron.Pt() > 25);
   isCF = (ieta1 * ieta2 == 4 || ieta1 * ieta2 == 6) && (Electron.Pt() > 25 && Positron.Pt() > 25);
   isLHCb = (Electron.Eta() > 2.0 && Electron.Eta() < 4.5)
          && (Positron.Eta() > 2.0 && Positron.Eta() < 4.5)
          && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
          && (ZBoson.M() > 60.0 && ZBoson.M() < 120.0);

   isATLASZPt = (fabs(ZBoson.Rapidity()) < 2.4)
             && (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
             && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
             && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4);

   bool isF = false;
   bool isB = false;
   isF = (cos_theta > 0);
   isB = (cos_theta < 0);

   if(isDilution){
     bool isUUB = false;
     bool isDDB = false;
     bool isSSB = false;
     bool isCCB = false;
     bool isBBB = false;
     bool isGG = false;
     isUUB = (fabs(fabs(ResBosTree->Type) - 1.0) < 1e-10);
     isDDB = (fabs(fabs(ResBosTree->Type) - 2.0) < 1e-10);
     isSSB = (fabs(fabs(ResBosTree->Type) - 3.0) < 1e-10);
     isCCB = (fabs(fabs(ResBosTree->Type) - 4.0) < 1e-10);
     isBBB = (fabs(fabs(ResBosTree->Type) - 5.0) < 1e-10);
     int flavor1, flavor2;
     if(isUUB && ResBosTree->Type > 0){flavor1 = 2; flavor2 = -2;}
     if(isUUB && ResBosTree->Type < 0){flavor1 = -2; flavor2 = 2;}
     if(isDDB && ResBosTree->Type > 0){flavor1 = 1; flavor2 = -1;}
     if(isDDB && ResBosTree->Type < 0){flavor1 = -1; flavor2 = 1;}
     if(isSSB && ResBosTree->Type > 0){flavor1 = 3; flavor2 = -3;}
     if(isSSB && ResBosTree->Type < 0){flavor1 = -3; flavor2 = 3;}
     if(isCCB && ResBosTree->Type > 0){flavor1 = 4; flavor2 = -4;}
     if(isCCB && ResBosTree->Type < 0){flavor1 = -4; flavor2 = 4;}
     if(isBBB && ResBosTree->Type > 0){flavor1 = 5; flavor2 = -5;}
     if(isBBB && ResBosTree->Type < 0){flavor1 = -5; flavor2 = 5;}
     double x1 = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(ZBoson.Rapidity());
     double x2 = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(ZBoson.Rapidity() * (-1.0));
     PDFReweightFactor = GetPDFReweightingFactor(x1, x2, flavor1, flavor2, ZBoson.M());
     Weight = Weight * PDFReweightFactor;
   }

   if(ZBoson.M() > 80 && ZBoson.M() < 100){
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
   }

   if(isLHCb){
     myhists->A0_ZPt_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->A1_ZPt_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A1_ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->A2_ZPt_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A2_ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->A3_ZPt_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A3_ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->A4_ZPt_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A4_ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->A02_ZPt_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A02_ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);

     myhists->A0_ZY_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_ZY_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
     myhists->A1_ZY_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A1_ZY_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
     myhists->A2_ZY_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A2_ZY_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
     myhists->A3_ZY_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A3_ZY_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
     myhists->A4_ZY_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A4_ZY_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
     myhists->A02_ZY_LHCb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A02_ZY_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);

   }

   if(1){
     if(fabs(ZBoson.Rapidity()) < 0.4) myhists->ZPt_y1_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     if(fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8) myhists->ZPt_y2_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     if(fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2) myhists->ZPt_y3_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     if(fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6) myhists->ZPt_y4_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     if(fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0) myhists->ZPt_y5_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     if(fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4) myhists->ZPt_y6_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->ATLASZPt_2D_Total->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight);
     myhists->ATLASZPt_2D_Total_uu->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * isZU);
     myhists->ATLASZPt_2D_Total_dd->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * isZD);
     myhists->ATLASZPt_2D_Total_MassWindow->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * (ZBoson.M() > 85 && ZBoson.M() < 95));
     myhists->ATLASZPt_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (fabs(ZBoson.Rapidity()) < 2.4));

     if(ZBoson.M() > 66 && ZBoson.M() < 116 && fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4 && Electron.Pt() > 20.0 && Positron.Pt() > 20.0){
       if(fabs(ZBoson.Rapidity()) < 0.4) myhists->ZPt_y1_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
       if(fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8) myhists->ZPt_y2_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
       if(fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2) myhists->ZPt_y3_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
       if(fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6) myhists->ZPt_y4_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
       if(fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0) myhists->ZPt_y5_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
       if(fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4) myhists->ZPt_y6_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
       myhists->ATLASZPt_2D_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight);
       myhists->ATLASZPt_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (fabs(ZBoson.Rapidity()) < 2.4));
     }
   }

   isCut = false;
   for(int icut = 0; icut < CutInfo.size(); icut++){
     CutForResBos(CutInfo.at(icut), CutLeft.at(icut), CutRight.at(icut), isCut);
   }
   if(isCut) continue;

   if(isTest){
     cout<<"ZPt = "<<ZBoson.Pt()<<" ZY = "<<ZBoson.Rapidity()<<" ZMass = "<<ZBoson.M()<<endl;
     cout<<"LeptonPt = "<<Electron.Pt()<<" AntiLeptonPt = "<<Positron.Pt()<<" LeptonEta = "<<Electron.Eta()<<" AntiLeptonEta = "<<Positron.Eta()<<endl;
   }


   myhists->ZMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->ZMass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC);
   myhists->ZMass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF);

   myhists->FZmass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZmass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FZmass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isF);
   myhists->BZmass_CC->at(iThread - 1)->Fill(ZBoson.M(),Weight * isCC * isB);
   myhists->FZmass_CF->at(iThread - 1)->Fill(ZBoson.M(),Weight * isCF * isF);
   myhists->BZmass_CF->at(iThread - 1)->Fill(ZBoson.M(),Weight * isCF * isB);
   myhists->FZmass_LHCb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isLHCb * isF);
   myhists->BZmass_LHCb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isLHCb * isB);

   if(isATLASZPt) myhists->ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->ZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
   myhists->ZE->at(iThread - 1)->Fill(ZBoson.E(), Weight);
   myhists->ZYE->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), ZBoson.E(), Weight);

   myhists->ZRapidity_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isLHCb);
   myhists->ZPt_LHCb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLHCb);
   myhists->phi_eta_LHCb->at(iThread - 1)->Fill(phi_eta, Weight * isLHCb);

   myhists->ZRapidityAbs->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
   myhists->ZPzPtBalance->at(iThread - 1)->Fill(fabs(ZBoson.Pz()) / ZBoson.Pt(), Weight);
   myhists->ZPzPtBalance_CC->at(iThread - 1)->Fill(fabs(ZBoson.Pz()) / ZBoson.Pt(), Weight * isCC);
   myhists->ZPzPtBalance_CF->at(iThread - 1)->Fill(fabs(ZBoson.Pz()) / ZBoson.Pt(), Weight * isCF);

   myhists->CosTheta->at(iThread - 1)->Fill(cos_theta, Weight);
   myhists->CosTheta_q->at(iThread - 1)->Fill(ResBosTree->costhe_q, Weight);
   myhists->CosTheta_h->at(iThread - 1)->Fill(ResBosTree->costhe_h, Weight);

   myhists->CollinsPhi->at(iThread - 1)->Fill(phi, Weight);
   myhists->plot_phi_eta->at(iThread - 1)->Fill(phi_eta, Weight);
   myhists->leptonPt->at(iThread - 1)->Fill(Electron.Pt(), Weight);
   myhists->leptonPt->at(iThread - 1)->Fill(Positron.Pt(), Weight);
   myhists->leptonEta->at(iThread - 1)->Fill(Electron.Eta(), Weight);
   myhists->leptonEta->at(iThread - 1)->Fill(Positron.Eta(), Weight);

   myhists->LepEtaAbs->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight);
   myhists->AntiLepEtaAbs->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight);
   myhists->LepEtaAbs_CC->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isCC);
   myhists->AntiLepEtaAbs_CC->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isCC);
   myhists->LepEtaAbs_CF->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isCF);
   myhists->AntiLepEtaAbs_CF->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isCF);
   myhists->LepEtaAbs_LHCb->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isLHCb);
   myhists->AntiLepEtaAbs_LHCb->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isLHCb);

   myhists->LepEta->at(iThread - 1)->Fill(Electron.Eta(), Weight);
   myhists->AntiLepEta->at(iThread - 1)->Fill(Positron.Eta(), Weight);
   myhists->LepEta_CC->at(iThread - 1)->Fill(Electron.Eta(), Weight * isCC);
   myhists->AntiLepEta_CC->at(iThread - 1)->Fill(Positron.Eta(), Weight * isCC);
   myhists->LepEta_CF->at(iThread - 1)->Fill(Electron.Eta(), Weight * isCF);
   myhists->AntiLepEta_CF->at(iThread - 1)->Fill(Positron.Eta(), Weight * isCF);
   myhists->LepEta_LHCb->at(iThread - 1)->Fill(Electron.Eta(), Weight * isLHCb);
   myhists->AntiLepEta_LHCb->at(iThread - 1)->Fill(Positron.Eta(), Weight * isLHCb);
   myhists->LepEta_HighMass->at(iThread - 1)->Fill(Electron.Eta(), Weight * (ZBoson.M() > 100.0));
   myhists->AntiLepEta_HighMass->at(iThread - 1)->Fill(Positron.Eta(), Weight * (ZBoson.M() > 100.0));

   myhists->FZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isF);
   myhists->BZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isB);
   myhists->FZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isF);
   myhists->BZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isB);
   myhists->FZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isF);
   myhists->BZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isB);
   myhists->FZRapidity_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isLHCb * isF);
   myhists->BZRapidity_LHCb->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isLHCb * isB);

   if(ZBoson.M() > 60.0 && ZBoson.M() < 120.0) myhists->FAveZMass_ZY_QT->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
   if(ZBoson.M() > 60.0 && ZBoson.M() < 120.0) myhists->BAveZMass_ZY_QT->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);

   myhists->FZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
   myhists->BZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);
   myhists->CMS_FZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
   myhists->CMS_BZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);

   myhists->AverageZPt_ZY_numer->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * ZBoson.Pt() * (ZBoson.Pt() < 50));
   myhists->AverageZPt_ZY_denom->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * (ZBoson.Pt() < 50));
   myhists->AverageZPt_lnQ_numer->at(iThread - 1)->Fill(log(ZBoson.M())/log(exp(1)), Weight * ZBoson.Pt() * (ZBoson.Pt() < 50));
   myhists->AverageZPt_lnQ_denom->at(iThread - 1)->Fill(log(ZBoson.M())/log(exp(1)), Weight * (ZBoson.Pt() < 50));
   myhists->AverageLepE_ZY_numer->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * Electron.E());
   myhists->AverageLepE_ZY_denom->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
   myhists->AverageAntiLepE_ZY_numer->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * Positron.E());
   myhists->AverageAntiLepE_ZY_denom->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);

   myhists->ZPt_Threshold->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->XSection_M_Y_CosTheta->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Rapidity(), cos_theta, Weight);
   myhists->ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);
   myhists->CMS_ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);

   int isWrong;
   if(isDilution){
     bool isUUB = false;
     bool isDDB = false;
     bool isSSB = false;
     bool isCCB = false;
     bool isBBB = false;
     bool isGG = false;
     isUUB = (fabs(fabs(ResBosTree->Type) - 1.0) < 1e-10);
     isDDB = (fabs(fabs(ResBosTree->Type) - 2.0) < 1e-10);
     isSSB = (fabs(fabs(ResBosTree->Type) - 3.0) < 1e-10);
     isCCB = (fabs(fabs(ResBosTree->Type) - 4.0) < 1e-10);
     isBBB = (fabs(fabs(ResBosTree->Type) - 5.0) < 1e-10);
     isGG = isSSB || isCCB || isBBB;

     if(isTest){
       if(isUUB) cout<<"Initial state: uub, Type = "<<ResBosTree->Type<<endl;
       if(isDDB) cout<<"Initial state: ddb, Type = "<<ResBosTree->Type<<endl;
       if(isSSB) cout<<"Initial state: ssb, Type = "<<ResBosTree->Type<<endl;
       if(isCCB) cout<<"Initial state: ccb, Type = "<<ResBosTree->Type<<endl;
       if(isBBB) cout<<"Initial state: bbb, Type = "<<ResBosTree->Type<<endl;
     }

     double CosThetaQ;
     if(ResBosTree->Type > 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron);
     if(ResBosTree->Type < 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron) * (-1.0);
     double PhiQ;
     if(ResBosTree->Type > 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0);
     if(ResBosTree->Type < 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0) * (-1.0);

     if(ResBosTree->Type > 0){//uubar
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 0;//u > ubar
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 1;//u < ubar
     }
     if(ResBosTree->Type < 0){//ubaru
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 1;//ubar > u
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 0;//ubar < u
     }

     bool isQuarkF = false;
     bool isQuarkB = false;
     isQuarkF = (CosThetaQ > 0);
     isQuarkB = (CosThetaQ < 0);

     myhists->FZY_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isUUB * isQuarkF);
     myhists->BZY_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isUUB * isQuarkB);
     myhists->FZY_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isDDB * isQuarkF);
     myhists->BZY_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isDDB * isQuarkB);
     myhists->ZY_uu_total->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isUUB);
     myhists->ZY_uu_wrong->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isUUB * isWrong);
     myhists->ZY_dd_total->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isDDB);
     myhists->ZY_dd_wrong->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isDDB * isWrong);

/*     myhists->QuarkA4_ZPt_uu->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkA4_ZPt_uu->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isUUB);
     myhists->QuarkA4_ZY_uu->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkA4_ZY_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isUUB);
     myhists->QuarkA4_ZPt_dd->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkA4_ZPt_dd->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isDDB);
     myhists->QuarkA4_ZY_dd->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkA4_ZY_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isDDB);
     myhists->QuarkL0_ZPt_uu->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkL0_ZPt_uu->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isUUB);
     myhists->QuarkL0_ZY_uu->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkL0_ZY_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isUUB);
     myhists->QuarkL0_ZPt_dd->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkL0_ZPt_dd->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isDDB);
     myhists->QuarkL0_ZY_dd->at(iThread - 1)->Initial(CosThetaQ, PhiQ);
     myhists->QuarkL0_ZY_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isDDB);

     myhists->A0_Mass_ZY_QT_uu->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_Mass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
     myhists->A0_Mass_ZY_QT_dd->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_Mass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
     myhists->A0_Mass_ZY_QT_ss->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_Mass_ZY_QT_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isSSB);
     myhists->A0_Mass_ZY_QT_cc->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_Mass_ZY_QT_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCCB);
     myhists->A0_Mass_ZY_QT_bb->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_Mass_ZY_QT_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isBBB);


     myhists->CosThetaQ->at(iThread - 1)->Fill(CosThetaQ, Weight);
     if(ResBosTree->Type > 0) myhists->ZRapidity_qqbar->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isWrong);
     if(ResBosTree->Type < 0) myhists->ZRapidity_qbarq->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isWrong);

     myhists->FZmass_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isUUB);
     myhists->BZmass_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isUUB);
     myhists->FZmass_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isDDB);
     myhists->BZmass_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isDDB);
     myhists->FZmass_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isGG);
     myhists->BZmass_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isGG);
     myhists->FZmass_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isUUB);
     myhists->BZmass_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isUUB);
     myhists->FZmass_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isDDB);
     myhists->BZmass_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isDDB);
     myhists->FZmass_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isGG);
     myhists->BZmass_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isGG);
     myhists->FZmass_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isUUB);
     myhists->BZmass_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isUUB);
     myhists->FZmass_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isDDB);
     myhists->BZmass_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isDDB);
     myhists->FZmass_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isGG);
     myhists->BZmass_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isGG);

     myhists->FZPt_uu->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isQuarkF * isUUB);
     myhists->BZPt_uu->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isQuarkB * isUUB);
     myhists->FZPt_dd->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isQuarkF * isDDB);
     myhists->BZPt_dd->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isQuarkB * isDDB);

     myhists->FZmass_ZPt_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkF * isUUB);
     myhists->BZmass_ZPt_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkB * isUUB);
     myhists->FZmass_ZPt_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkF * isDDB);
     myhists->BZmass_ZPt_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkB * isDDB);

     myhists->ZMass_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
     myhists->ZMass_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
     myhists->ZMass_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isGG);
     myhists->ZMass_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB);
     myhists->ZMass_cc->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCCB);
     myhists->ZMass_bb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isBBB);
     myhists->ZMass_utype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isZU);
     myhists->ZMass_dtype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isZD);
     myhists->ZMass_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isUUB);
     myhists->ZMass_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isDDB);
     myhists->ZMass_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isGG);
     myhists->ZMass_CC_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isSSB);
     myhists->ZMass_CC_cc->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isCCB);
     myhists->ZMass_CC_bb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isBBB);
     myhists->ZMass_CC_utype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isZU);
     myhists->ZMass_CC_dtype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isZD);
     myhists->ZMass_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isUUB);
     myhists->ZMass_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isDDB);
     myhists->ZMass_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isGG);
     myhists->ZMass_CF_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isSSB);
     myhists->ZMass_CF_cc->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isCCB);
     myhists->ZMass_CF_bb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isBBB);
     myhists->ZMass_CF_utype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isZU);
     myhists->ZMass_CF_dtype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isZD);

     myhists->FZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isUUB);
     myhists->BZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isUUB);
     myhists->FZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isDDB);
     myhists->BZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isDDB);

     myhists->ZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
     myhists->ZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
     myhists->ZMass_ZY_QT_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isSSB);
     myhists->ZMass_ZY_QT_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCCB);
     myhists->ZMass_ZY_QT_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isBBB);
     myhists->CMS_FZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isUUB);
     myhists->CMS_BZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isUUB);
     myhists->CMS_FZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isDDB);
     myhists->CMS_BZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isDDB);


     myhists->ZPt_uub->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isUUB);
     myhists->ZRapidity_uub->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isUUB);
     myhists->ZMass_uub->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
     myhists->ZPt_ddb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isDDB);
     myhists->ZRapidity_ddb->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isDDB);
     myhists->ZMass_ddb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
     myhists->ZPt_ssb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isSSB);
     myhists->ZRapidity_ssb->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isSSB);
     myhists->ZMass_ssb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB);
*/

/*     myhists->LepEta_ss->at(iThread - 1)->Fill(Electron.Eta(), Weight * isSSB);
     myhists->AntiLepEta_ss->at(iThread - 1)->Fill(Positron.Eta(), Weight * isSSB);
     myhists->LepEta_uubar->at(iThread - 1)->Fill(Electron.Eta(), Weight * isUUB * (ResBosTree->Type > 0) * (ZBoson.M() > 100.0));
     myhists->AntiLepEta_uubar->at(iThread - 1)->Fill(Positron.Eta(), Weight * isUUB * (ResBosTree->Type > 0) * (ZBoson.M() > 100.0));
     myhists->LepEta_ubaru->at(iThread - 1)->Fill(Electron.Eta(), Weight * isUUB * (ResBosTree->Type < 0) * (ZBoson.M() > 100.0));
     myhists->AntiLepEta_ubaru->at(iThread - 1)->Fill(Positron.Eta(), Weight * isUUB * (ResBosTree->Type < 0) * (ZBoson.M() > 100.0));
     myhists->ZRapidity_uubar->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isUUB * (ResBosTree->Type > 0));
     myhists->ZRapidity_ubaru->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isUUB * (ResBosTree->Type < 0));
*/


/*
     myhists->ZMass_CC_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC);
     myhists->ZMass_CC_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isWrong);
     myhists->ZMass_CF_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF);
     myhists->ZMass_CF_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isWrong);
     myhists->ZMass_Full_total->at(iThread - 1)->Fill(ZBoson.M(), Weight);
     myhists->ZMass_Full_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong);

     myhists->ZMass_CC_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isUUB);
     myhists->ZMass_CC_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isUUB * isWrong);
     myhists->ZMass_CC_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isDDB);
     myhists->ZMass_CC_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isDDB * isWrong);
     myhists->ZMass_CF_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isUUB);
     myhists->ZMass_CF_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isUUB * isWrong);
     myhists->ZMass_CF_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isDDB);
     myhists->ZMass_CF_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isDDB * isWrong);
     myhists->ZMass_Full_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
     myhists->ZMass_Full_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB * isWrong);
     myhists->ZMass_Full_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
     myhists->ZMass_Full_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB * isWrong);
     myhists->ZMass_Full_ss_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB);
     myhists->ZMass_Full_ss_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB * isWrong);
     myhists->ZMass_Full_cc_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCCB);
     myhists->ZMass_Full_cc_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCCB * isWrong);
     myhists->ZMass_Full_bb_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isBBB);
     myhists->ZMass_Full_bb_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isBBB * isWrong);

     myhists->ZPt_total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
     myhists->ZPt_wrong->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isWrong);
     myhists->ZRapidity_total->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
     myhists->ZRapidity_wrong->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isWrong);

     myhists->ZMass_ZY_QT_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
     myhists->ZMass_ZY_QT_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * isWrong);
     myhists->ZMass_ZY_QT_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
     myhists->ZMass_ZY_QT_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * isWrong);

     myhists->CMS_ZMass_ZY_QT_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
     myhists->CMS_ZMass_ZY_QT_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * isWrong);
     myhists->CMS_ZMass_ZY_QT_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
     myhists->CMS_ZMass_ZY_QT_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * isWrong);
*/
   }

 }

}

double loopResBos::GetPDFReweightingFactor(double x1, double x2, int flavor1, int flavor2, double Q)
{
 double Value = 1.0;
 if(!isPDFReweight){
   //cout<<"ERROR! Please initialize PDF at first."<<endl;
   return 1.0;
 }

 Value = myPDFReweight->GetPDFReweightFactor(flavor1, flavor2, x1, x2, Q);

 if(Value > 5000.0 || Value < 0.0){
   ProblemEventNumber++;
   Value = 1.0;
 }

 return Value;
}

void loopResBos::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;

 if(!ResBosTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ResBosTree->fChain[RootNumber]->GetCurrentFile();
}

void loopResBos::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;
 if(isPDFReweight && ProblemEventNumber > 0) cout<<"Thread No."<<this->iThread<<": Problem Event Number: "<<this->ProblemEventNumber<<endl;

 if(EndFile == RootNames.size()) delete ResBosTree;

}


loopResBos::~loopResBos()
{
}
