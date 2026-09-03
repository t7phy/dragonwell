#define loopResBosCMS_cxx
#include <iostream>
#include "Analysis/loopResBosCMS.h"

using namespace std;

loopResBosCMS::loopResBosCMS(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 if(RootType == "FittingCMSData"){
   myReweighting = new DilutionReweighting();
   //myReweighting->Initial();
 }

 isThread = false;
}

void loopResBosCMS::InputHist(HistsResBosCMS* &myhists)
{
 this->myhists = myhists;

}

void loopResBosCMS::InputTree(TreeForResBosCMS *ResBosCMSTree)
{
 this->ResBosCMSTree = ResBosCMSTree;
 this->RootNames = ResBosCMSTree->RootNames;
 this->isFSR = ResBosCMSTree->isFSR;
 this->isDilution = ResBosCMSTree->isDilution;

 this->FirstFile = ResBosCMSTree->FirstFile;
 this->EndFile = ResBosCMSTree->EndFile;

 this->OneFilePerJob = ResBosCMSTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ResBosCMSTree->TotalEntries[ifile];
 }

}

void loopResBosCMS::ReadTree(int ifile)
{
 isZU = false;
 isZD = false;
 isWPlus = false;
 isWMinus = false;

 if(RootNames.at(ifile).Contains("zu")) isZU = true;
 if(RootNames.at(ifile).Contains("zd")) isZD = true;
 if(RootNames.at(ifile).Contains("wp")) isWPlus = true;
 if(RootNames.at(ifile).Contains("wm")) isWMinus = true;

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   ResBosCMSTree->GetEntry(ifile, iEvent);

   isZEvents = isZU || isZD;
   isWEvents = isWPlus || isWMinus;
     
   if(isZEvents) FillZEvents();
   if(isWEvents) FillWEvents();
 }
}

void loopResBosCMS::FillZEvents()
{
   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(ResBosCMSTree->ElectronPx, ResBosCMSTree->ElectronPy, ResBosCMSTree->ElectronPz, ResBosCMSTree->ElectronE);
   Positron.SetPxPyPzE(ResBosCMSTree->PositronPx, ResBosCMSTree->PositronPy, ResBosCMSTree->PositronPz, ResBosCMSTree->PositronE);

   Weight = ResBosCMSTree->Weight;
   if(!isfinite(Weight)) return;

   ZBoson = Electron + Positron;

   double ZRapidity=ZBoson.Rapidity();

   double LargeX = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(fabs(ZBoson.Rapidity()));
   double SmallX = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(fabs(ZBoson.Rapidity()) * (-1.0));

   cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZRapidity / fabs(ZRapidity);
   phi = calculate_phi(Electron, Positron, (double)ECM / 2.0) * ZRapidity / fabs(ZRapidity);
   phi_eta = calculate_phi_eta(Electron, Positron);

   if(cos_theta > 1) cos_theta = 1.0;
   if(cos_theta < -1) cos_theta = -1.0;

   bool isCC = false;
   bool isCF = false;
   bool isLHCb = false;

   bool isATLAS8TeVZPt = false;
   bool isATLAS13TeVZPt = false;
   bool isCMS13TeVZPt = false;
   bool isLHCb13TeVZPt = false;

   bool isATLAS8TeVAngular = false;

   bool isATLAS8TeVWEta = false;

   bool isATLAS7TeVZPt = false;
   bool isCMS8TeVZPt = false;
   bool isCMS7TeVZPt = false;
   bool isATLAS7TeVPhi = false;

   bool isCMS = false;
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

   isATLAS8TeVZPt = (fabs(ZBoson.Rapidity()) < 2.4)
                 && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
                 && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4);

   isATLAS13TeVZPt = (Electron.Pt() > 27.0 && Positron.Pt() > 27.0)
                  && (fabs(Electron.Eta()) < 2.5 && fabs(Positron.Eta()) < 2.5)
                  && (ZBoson.M() > 66.0 && ZBoson.M() < 116.0);

   isCMS13TeVZPt = (Electron.Pt() > 25.0 && Positron.Pt() > 25.0)
                && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4)
                && (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876)
                && (fabs(ZBoson.Rapidity()) < 2.4);

   isLHCb13TeVZPt = (Electron.Eta() > 2.0 && Electron.Eta() < 4.5)
                 && (Positron.Eta() > 2.0 && Positron.Eta() < 4.5)
                 && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
                 && (ZBoson.M() > 60.0 && ZBoson.M() < 120.0);

   isATLAS8TeVAngular = (ZBoson.M() > 80.0 && ZBoson.M() < 100.0);

   isATLAS7TeVZPt = (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
                 && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4)
                 && (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
                 && (fabs(ZBoson.Rapidity()) < 2.4);

   isCMS8TeVZPt = (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
               && (fabs(Electron.Eta()) < 2.1 && fabs(Positron.Eta()) < 2.1)
               && (ZBoson.M() > 60.0 && ZBoson.M() < 120.0);

   isCMS7TeVZPt = (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
               && (fabs(Electron.Eta()) < 2.1 && fabs(Positron.Eta()) < 2.1)
               && (ZBoson.M() > 60.0 && ZBoson.M() < 120.0);

   isATLAS7TeVPhi = (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
                 && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4)
                 && (ZBoson.M() > 66.0 && ZBoson.M() < 116.0);

   bool is8TeVTot = (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
                 && (fabs(Electron.Eta()) < 2.5 && fabs(Positron.Eta()) < 2.5)
                 && (ZBoson.M() > 60.0 && ZBoson.M() < 110.0);


   double WMT = CalculateTransverseMass(Positron, Electron);
   isATLAS8TeVWEta = (Electron.Pt() > 25.0) //missing ET
                  && (Positron.Pt() > 25.0) //lepton pt
                  && (fabs(Positron.Eta() < 2.4)) //lepton eta
                  && (WMT > 40.0);

   isCMS = 1;

   isCMS = isCMS * (fabs(ZBoson.Rapidity()) > 1.5 && fabs(ZBoson.Rapidity()) < 2.4);

   if(!isCMS && RootType == "FittingCMSData") return;

   bool isF = false;
   bool isB = false;
   isF = (cos_theta > 0);
   isB = (cos_theta < 0);

   if(RootType == "FittingCMSData"){
     ReweightingFactor = myReweighting->GetReweightingFactor(cos_theta, ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), StwValue, P0uValue, P0dValue);
     Weight = ResBosCMSTree->Weight * ReweightingFactor;
   }

   int isWrong;
   if(isDilution){
     bool isUUB = false;
     bool isDDB = false;
     bool isSSB = false;
     bool isCCB = false;
     bool isBBB = false;
     bool isGG = false;
     isUUB = (fabs(fabs(ResBosCMSTree->Type) - 1.0) < 1e-10);
     isDDB = (fabs(fabs(ResBosCMSTree->Type) - 2.0) < 1e-10);
     isSSB = (fabs(fabs(ResBosCMSTree->Type) - 3.0) < 1e-10);
     isCCB = (fabs(fabs(ResBosCMSTree->Type) - 4.0) < 1e-10);
     isBBB = (fabs(fabs(ResBosCMSTree->Type) - 5.0) < 1e-10);
     isGG = isSSB || isCCB || isBBB;

     if(isTest){
       if(isUUB) cout<<"Initial state: uub, Type = "<<ResBosCMSTree->Type<<endl;
       if(isDDB) cout<<"Initial state: ddb, Type = "<<ResBosCMSTree->Type<<endl;
       if(isSSB) cout<<"Initial state: ssb, Type = "<<ResBosCMSTree->Type<<endl;
       if(isCCB) cout<<"Initial state: ccb, Type = "<<ResBosCMSTree->Type<<endl;
       if(isBBB) cout<<"Initial state: bbb, Type = "<<ResBosCMSTree->Type<<endl;
     }

     double CosThetaQ;
     if(ResBosCMSTree->Type > 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron);
     if(ResBosCMSTree->Type < 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron) * (-1.0);
     double PhiQ;
     if(ResBosCMSTree->Type > 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0);
     if(ResBosCMSTree->Type < 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0) * (-1.0);

     if(ResBosCMSTree->Type > 0){
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 0;
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 1;
     }
     if(ResBosCMSTree->Type < 0){
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 1;
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 0;
     }

     bool isQuarkF = false;
     bool isQuarkB = false;
     isQuarkF = (CosThetaQ > 0);
     isQuarkB = (CosThetaQ < 0);

     if(RootType != "FittingCMSData"){
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

       myhists->ZMass_ZY_QT_uu_YP_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * (ZBoson.Rapidity() > 0.0) * isWrong);
       myhists->ZMass_ZY_QT_uu_YP_right->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * (ZBoson.Rapidity() > 0.0) * (!isWrong));
       myhists->ZMass_ZY_QT_uu_YM_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * (ZBoson.Rapidity() < 0.0) * isWrong);
       myhists->ZMass_ZY_QT_uu_YM_right->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * (ZBoson.Rapidity() < 0.0) * (!isWrong));
       myhists->ZMass_ZY_QT_dd_YP_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * (ZBoson.Rapidity() > 0.0) * isWrong);
       myhists->ZMass_ZY_QT_dd_YP_right->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * (ZBoson.Rapidity() > 0.0) * (!isWrong));
       myhists->ZMass_ZY_QT_dd_YM_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * (ZBoson.Rapidity() < 0.0) * isWrong);
       myhists->ZMass_ZY_QT_dd_YM_right->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * (ZBoson.Rapidity() < 0.0) * (!isWrong));

     }
   }

   if(RootType != "FittingCMSData"){
     myhists->ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);
     myhists->ZMass_ZY_QT_YP->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * (ZBoson.Rapidity() > 0.0));
     myhists->ZMass_ZY_QT_YM->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * (ZBoson.Rapidity() < 0.0));
     myhists->ZY_x1->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * (fabs(LargeX - 0.05) < 0.01));
     myhists->ZY_x2->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * (fabs(LargeX - 0.08) < 0.01));
     myhists->ZY_x3->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * (fabs(LargeX - 0.11) < 0.01));

   }

   myhists->FZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
   myhists->BZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);

   //////////////////////////////
   //  For NonPertFit pT Data  //
   //////////////////////////////

   myhists->ZpT_Inclusive->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->ATLAS8TeV_pT_Mass12_20_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 12 && ZBoson.M() < 20));
   myhists->ATLAS8TeV_pT_Mass20_30_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 20 && ZBoson.M() < 30));
   myhists->ATLAS8TeV_pT_Mass30_46_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 30 && ZBoson.M() < 46));
   myhists->ATLAS8TeV_pT_Mass46_66_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 46 && ZBoson.M() < 66));
   myhists->ATLAS8TeV_pT_Mass66_116_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116));
   myhists->ATLAS8TeV_pT_Mass116_150_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 116 && ZBoson.M() < 150));
   myhists->ATLAS8TeV_Phi_Y1_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4));
   myhists->ATLAS8TeV_Phi_Y2_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8));
   myhists->ATLAS8TeV_Phi_Y3_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2));
   myhists->ATLAS8TeV_Phi_Y4_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6));
   myhists->ATLAS8TeV_Phi_Y5_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0));
   myhists->ATLAS8TeV_Phi_Y6_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4));
   myhists->ATLAS8TeV_pT_Y1_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4));
   myhists->ATLAS8TeV_pT_Y2_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8));
   myhists->ATLAS8TeV_pT_Y3_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2));
   myhists->ATLAS8TeV_pT_Y4_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6));
   myhists->ATLAS8TeV_pT_Y5_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0));
   myhists->ATLAS8TeV_pT_Y6_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4));
   myhists->ATLAS8TeV_pT_Y1_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4));
   myhists->ATLAS8TeV_pT_Y2_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8));
   myhists->ATLAS8TeV_pT_Y3_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2));
   myhists->ATLAS8TeV_pT_Y4_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6));
   myhists->ATLAS8TeV_pT_Y5_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0));
   myhists->ATLAS8TeV_pT_Y6_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4));
   myhists->ATLAS8TeV_pT_Y1_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4) * isZU);
   myhists->ATLAS8TeV_pT_Y2_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8) * isZU);
   myhists->ATLAS8TeV_pT_Y3_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2) * isZU);
   myhists->ATLAS8TeV_pT_Y4_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6) * isZU);
   myhists->ATLAS8TeV_pT_Y5_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0) * isZU);
   myhists->ATLAS8TeV_pT_Y6_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4) * isZU);
   myhists->ATLAS8TeV_pT_Y1_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4) * isZD);
   myhists->ATLAS8TeV_pT_Y2_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8) * isZD);
   myhists->ATLAS8TeV_pT_Y3_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2) * isZD);
   myhists->ATLAS8TeV_pT_Y4_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6) * isZD);
   myhists->ATLAS8TeV_pT_Y5_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.0) * isZD);
   myhists->ATLAS8TeV_pT_Y6_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVZPt * (ZBoson.M() > 66 && ZBoson.M() < 116) * (fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4) * isZD);
   myhists->ATLAS13TeV_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS13TeVZPt);
   myhists->ATLAS13TeV_Phi_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS13TeVZPt);
   myhists->CMS13TeV_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt);
   myhists->CMS13TeV_Phi_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isCMS13TeVZPt);
   myhists->LHCb13TeV_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLHCb13TeVZPt);
   myhists->LHCb13TeV_pT_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 60.0 && ZBoson.M() < 120.0) * (ZBoson.Rapidity() > 2.0 && ZBoson.Rapidity() < 4.5));
   myhists->LHCb13TeV_pT_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLHCb13TeVZPt * isZU);
   myhists->LHCb13TeV_pT_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLHCb13TeVZPt * isZD);
   myhists->LHCb13TeV_Phi_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isLHCb13TeVZPt);
   myhists->CMS13TeV_pT_Y1_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4));
   myhists->CMS13TeV_pT_Y2_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8));
   myhists->CMS13TeV_pT_Y3_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2));
   myhists->CMS13TeV_pT_Y4_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6));
   myhists->CMS13TeV_pT_Y5_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.4));
   myhists->CMS13TeV_pT_Y1_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876) * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4));
   myhists->CMS13TeV_pT_Y2_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876) * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8));
   myhists->CMS13TeV_pT_Y3_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876) * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2));
   myhists->CMS13TeV_pT_Y4_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876) * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6));
   myhists->CMS13TeV_pT_Y5_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876) * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.4));
   myhists->CMS13TeV_pT_Y1_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4) * isZU);
   myhists->CMS13TeV_pT_Y2_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8) * isZU);
   myhists->CMS13TeV_pT_Y3_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2) * isZU);
   myhists->CMS13TeV_pT_Y4_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6) * isZU);
   myhists->CMS13TeV_pT_Y5_uu_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.4) * isZU);
   myhists->CMS13TeV_pT_Y1_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.4) * isZD);
   myhists->CMS13TeV_pT_Y2_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.4 && fabs(ZBoson.Rapidity()) < 0.8) * isZD);
   myhists->CMS13TeV_pT_Y3_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.2) * isZD);
   myhists->CMS13TeV_pT_Y4_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 1.2 && fabs(ZBoson.Rapidity()) < 1.6) * isZD);
   myhists->CMS13TeV_pT_Y5_dd_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS13TeVZPt * (fabs(ZBoson.Rapidity()) > 1.6 && fabs(ZBoson.Rapidity()) < 2.4) * isZD);
   myhists->CMS13TeV_yZ_Theory->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCMS13TeVZPt);
   myhists->CMS13TeV_yZ_Total->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * (ZBoson.M() > 76.1876 && ZBoson.M() < 106.1876));
   myhists->LHCb13TeV_yZ_Theory->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isLHCb13TeVZPt);

   myhists->ATLAS8TeV_WPlus_Eta_Theory->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isATLAS8TeVWEta * isWPlus);
   myhists->ATLAS8TeV_WMinus_Eta_Theory->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isATLAS8TeVWEta * isWMinus);

   myhists->ATLAS7TeV_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS7TeVZPt);
   myhists->ATLAS7TeV_pT_Y1_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS7TeVZPt * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 1.0));
   myhists->ATLAS7TeV_pT_Y2_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS7TeVZPt * (fabs(ZBoson.Rapidity()) > 1.0 && fabs(ZBoson.Rapidity()) < 2.0));
   myhists->ATLAS7TeV_pT_Y3_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS7TeVZPt * (fabs(ZBoson.Rapidity()) > 2.0 && fabs(ZBoson.Rapidity()) < 2.4));
   myhists->CMS8TeV_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS8TeVZPt);
   myhists->CMS7TeV_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isCMS7TeVZPt);
   myhists->ATLAS7TeV_Phi_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS7TeVPhi);
   myhists->ATLAS7TeV_Phi_Y1_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS7TeVPhi * (fabs(ZBoson.Rapidity()) > 0.0 && fabs(ZBoson.Rapidity()) < 0.8));
   myhists->ATLAS7TeV_Phi_Y2_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS7TeVPhi * (fabs(ZBoson.Rapidity()) > 0.8 && fabs(ZBoson.Rapidity()) < 1.6));
   myhists->ATLAS7TeV_Phi_Y3_Theory->at(iThread - 1)->Fill(phi_eta, Weight * isATLAS7TeVPhi * (fabs(ZBoson.Rapidity()) > 1.6));

   myhists->ATLAS8TeV_A0_pT_Theory->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->ATLAS8TeV_A0_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVAngular);
   myhists->ATLAS8TeV_A1_pT_Theory->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->ATLAS8TeV_A1_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVAngular);
   myhists->ATLAS8TeV_A2_pT_Theory->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->ATLAS8TeV_A2_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVAngular);
   myhists->ATLAS8TeV_A3_pT_Theory->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->ATLAS8TeV_A3_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVAngular);
   myhists->ATLAS8TeV_A4_pT_Theory->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->ATLAS8TeV_A4_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVAngular);
   myhists->ATLAS8TeV_A02_pT_Theory->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->ATLAS8TeV_A02_pT_Theory->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isATLAS8TeVAngular);

   myhists->ZPt_FineBin->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->ZPt_FineBin_HighPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);

   myhists->TotalCrossSection_8TeV->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * is8TeVTot);

   myhists->WPlusYQT->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * (ZBoson.M() > 30.0 && ZBoson.M() < 85.0));

   /////////////////////////////
   // CTEQ Drell-Yan k-factor //
   /////////////////////////////

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

void loopResBosCMS::FillWEvents()
{
   Neutrino.SetPxPyPzE(ResBosCMSTree->ElectronPx, ResBosCMSTree->ElectronPy, ResBosCMSTree->ElectronPz, ResBosCMSTree->ElectronE);
   Lepton.SetPxPyPzE(ResBosCMSTree->PositronPx, ResBosCMSTree->PositronPy, ResBosCMSTree->PositronPz, ResBosCMSTree->PositronE);
   Weight = ResBosCMSTree->Weight;
   if(!isfinite(Weight)) return;

   WBoson = Neutrino + Lepton;

   WMT = CalculateTransverseMass(Lepton, Neutrino);

   bool isE245_LHCb7TeV = (Lepton.Pt() > 20.0)
                       && (Lepton.Eta() > 2.0 && Lepton.Eta() < 4.5);

   bool isE248_ATLAS7TeV = (Lepton.Pt() > 25.0)
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

void loopResBosCMS::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!ResBosCMSTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ResBosCMSTree->fChain[RootNumber]->GetCurrentFile();
}

void loopResBosCMS::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete ResBosCMSTree;
 if(RootType == "FittingCMSData") myReweighting->Close();

}

loopResBosCMS::~loopResBosCMS()
{
}
