#define loopFlavorAsym_cxx
#include <iostream>
#include "Analysis/loopFlavorAsym.h"

using namespace std;

loopFlavorAsym::loopFlavorAsym(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopFlavorAsym::InputHist(HistsFlavorAsym* &myhists)
{
 this->myhists = myhists;

}

void loopFlavorAsym::InputTree(TreeForFlavorAsym *FlavorAsymTree)
{
 this->FlavorAsymTree = FlavorAsymTree;
 this->RootNames = FlavorAsymTree->RootNames;
 this->isFSR = FlavorAsymTree->isFSR;
 this->isDilution = FlavorAsymTree->isDilution;

 this->FirstFile = FlavorAsymTree->FirstFile;
 this->EndFile = FlavorAsymTree->EndFile;

 this->OneFilePerJob = FlavorAsymTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = FlavorAsymTree->TotalEntries[ifile];
 }

}

void loopFlavorAsym::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   FlavorAsymTree->GetEntry(ifile, iEvent);

   isZEvents = false;
   isWEvents = false;

   if(fabs(FlavorAsymTree->Type) < 10) isZEvents = true;
   if(fabs(FlavorAsymTree->Type) > 10) isWEvents = true;

   if(isZEvents) FillZEvents();
   if(isWEvents) FillWEvents();
 }

}

void loopFlavorAsym::FillZEvents()
{
   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, FlavorAsymTree->ElectronPz, FlavorAsymTree->ElectronE);
   Positron.SetPxPyPzE(FlavorAsymTree->PositronPx, FlavorAsymTree->PositronPy, FlavorAsymTree->PositronPz, FlavorAsymTree->PositronE);

   Weight = FlavorAsymTree->Weight;
   if(!isfinite(Weight)) return;

   ZBoson = Electron + Positron;

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

   isATLASZPt = (fabs(ZBoson.Rapidity()) < 2.4)
             && (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
             && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
             && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4);

   isCMS = 1;

   isCMS = isCMS * (fabs(ZBoson.Rapidity()) > 1.5 && fabs(ZBoson.Rapidity()) < 2.4);

   if(!isCMS && RootType == "FittingCMSData") return;

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
     bool isOther = false;
     isUUB = (fabs(fabs(FlavorAsymTree->Type) - 1.0) < 1e-10);
     isDDB = (fabs(fabs(FlavorAsymTree->Type) - 2.0) < 1e-10);
     isSSB = (fabs(fabs(FlavorAsymTree->Type) - 3.0) < 1e-10);
     isCCB = (fabs(fabs(FlavorAsymTree->Type) - 4.0) < 1e-10);
     isBBB = (fabs(fabs(FlavorAsymTree->Type) - 5.0) < 1e-10);
     isGG = isSSB || isCCB || isBBB;
     isOther = isCCB || isBBB;

     if(isTest){
       if(isUUB) cout<<"Initial state: uub, Type = "<<FlavorAsymTree->Type<<endl;
       if(isDDB) cout<<"Initial state: ddb, Type = "<<FlavorAsymTree->Type<<endl;
       if(isSSB) cout<<"Initial state: ssb, Type = "<<FlavorAsymTree->Type<<endl;
       if(isCCB) cout<<"Initial state: ccb, Type = "<<FlavorAsymTree->Type<<endl;
       if(isBBB) cout<<"Initial state: bbb, Type = "<<FlavorAsymTree->Type<<endl;
     }

     double CosThetaQ;
     if(FlavorAsymTree->Type > 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron);
     if(FlavorAsymTree->Type < 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron) * (-1.0);
     double PhiQ;
     if(FlavorAsymTree->Type > 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0);
     if(FlavorAsymTree->Type < 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0) * (-1.0);

     if(FlavorAsymTree->Type > 0){
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 0;
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 1;
     }
     if(FlavorAsymTree->Type < 0){
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 1;
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 0;
     }

     if(isUUB && FlavorAsymTree->Type > 0) QuarkFlavor = 2;
     if(isDDB && FlavorAsymTree->Type > 0) QuarkFlavor = 1;
     if(isSSB && FlavorAsymTree->Type > 0) QuarkFlavor = 3;
     if(isCCB && FlavorAsymTree->Type > 0) QuarkFlavor = 4;
     if(isBBB && FlavorAsymTree->Type > 0) QuarkFlavor = 5;
     if(isUUB && FlavorAsymTree->Type < 0) QuarkFlavor = -2;
     if(isDDB && FlavorAsymTree->Type < 0) QuarkFlavor = -1;
     if(isSSB && FlavorAsymTree->Type < 0) QuarkFlavor = -3;
     if(isCCB && FlavorAsymTree->Type < 0) QuarkFlavor = -4;
     if(isBBB && FlavorAsymTree->Type < 0) QuarkFlavor = -5;

     bool isQuarkF = false;
     bool isQuarkB = false;
     isQuarkF = (CosThetaQ > 0);
     isQuarkB = (CosThetaQ < 0);

     /*********************************/
     /*   Get PDF Reweighting factor  */
     /*********************************/

     ZEventPDFWeight = 1.0;
     if(fabs(ZBoson.Rapidity()) < 2.5 && fabs(ZBoson.Rapidity()) > 2.2 && isWrong == 0){//add weight on small x(second one) events(right)
       double LargeX = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(fabs(ZBoson.Rapidity()));
       double SmallX = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(fabs(ZBoson.Rapidity()) * (-1.0));
       //if(isUUB) ZEventPDFWeight = GetZPDFWeight(LargeX, SmallX, 2, ZBoson.M(), PDFDelta);
       //if(isDDB) ZEventPDFWeight = GetZPDFWeight(LargeX, SmallX, 1, ZBoson.M(), PDFDelta);
     }
     if(fabs(ZBoson.Rapidity()) < 2.5 && fabs(ZBoson.Rapidity()) > 2.2 && isWrong == 1){//add weight on small x(first one) events(wrong) for compensating the sum rule
       double LargeX = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(fabs(ZBoson.Rapidity()));
       double SmallX = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(fabs(ZBoson.Rapidity()) * (-1.0));
       //if(isUUB) ZEventPDFWeight = GetZPDFWeight(LargeX, SmallX, -2, ZBoson.M(), PDFDelta);
       //if(isDDB) ZEventPDFWeight = GetZPDFWeight(LargeX, SmallX, -1, ZBoson.M(), PDFDelta);
     }

     double x1 = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(ZBoson.Rapidity());
     double x2 = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(ZBoson.Rapidity() * (-1.0));
     //ZEventPDFWeight = GetZStrangeWeight(x1, x2, QuarkFlavor, ZBoson.M(), 2.0);
     //if(fabs(ZBoson.Rapidity()) > 3.0 && fabs(ZBoson.Rapidity()) < 3.5 && ZEventPDFWeight < 1){
     //  cout<<"QuarkFlavor: "<<QuarkFlavor<<" x1: "<<x1<<" x2: "<<x2<<" Weight: "<<Weight<<" ZEventPDFWeight: "<<ZEventPDFWeight<<endl;
     //}

     myhists->ZY_ssbar->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isSSB * (FlavorAsymTree->Type > 0));
     myhists->ZY_sbars->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isSSB * (FlavorAsymTree->Type < 0));
     myhists->ZPositiveLeptonEta_uu->at(iThread - 1)->Fill(Positron.Eta(), Weight * isUUB * (ZBoson.M() > 100.0) * (fabs(ZBoson.Rapidity()) > 3.5));
     myhists->ZNegativeLeptonEta_uu->at(iThread - 1)->Fill(Electron.Eta(), Weight * isUUB * (ZBoson.M() > 100.0) * (fabs(ZBoson.Rapidity()) > 3.5));
     myhists->ZPositiveLeptonEta_dd->at(iThread - 1)->Fill(Positron.Eta(), Weight * isDDB * (ZBoson.M() > 100.0) * (fabs(ZBoson.Rapidity()) > 3.5));
     myhists->ZNegativeLeptonEta_dd->at(iThread - 1)->Fill(Electron.Eta(), Weight * isDDB * (ZBoson.M() > 100.0) * (fabs(ZBoson.Rapidity()) > 3.5));
     myhists->ZPositiveLeptonEta_ss->at(iThread - 1)->Fill(Positron.Eta(), Weight * isSSB * (ZBoson.M() > 100.0) * (fabs(ZBoson.Rapidity()) > 3.5));
     myhists->ZNegativeLeptonEta_ss->at(iThread - 1)->Fill(Electron.Eta(), Weight * isSSB * (ZBoson.M() > 100.0) * (fabs(ZBoson.Rapidity()) > 3.5));

     double EtaCutDef = 3.8;
     myhists->ZMass_ForwardEtaPlus->at(iThread - 1)->Fill(ZBoson.M(), Weight * (fabs(Positron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaPlus->at(iThread - 1)->Fill(ZBoson.M(), Weight * (fabs(Positron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaMinus->at(iThread - 1)->Fill(ZBoson.M(), Weight * (fabs(Electron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaMinus->at(iThread - 1)->Fill(ZBoson.M(), Weight * (fabs(Electron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaPlus_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB * (fabs(Positron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaPlus_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB * (fabs(Positron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaMinus_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB * (fabs(Electron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaMinus_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB * (fabs(Electron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaPlus_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB * (fabs(Positron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaPlus_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB * (fabs(Positron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaMinus_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB * (fabs(Electron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaMinus_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB * (fabs(Electron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaPlus_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB * (fabs(Positron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaPlus_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB * (fabs(Positron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaMinus_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB * (fabs(Electron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaMinus_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB * (fabs(Electron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaPlus_other->at(iThread - 1)->Fill(ZBoson.M(), Weight * isOther * (fabs(Positron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaPlus_other->at(iThread - 1)->Fill(ZBoson.M(), Weight * isOther * (fabs(Positron.Eta()) < EtaCutDef));
     myhists->ZMass_ForwardEtaMinus_other->at(iThread - 1)->Fill(ZBoson.M(), Weight * isOther * (fabs(Electron.Eta()) > EtaCutDef));
     myhists->ZMass_CentralEtaMinus_other->at(iThread - 1)->Fill(ZBoson.M(), Weight * isOther * (fabs(Electron.Eta()) < EtaCutDef));
  
     myhists->ZMass_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
     myhists->ZMass_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
     myhists->ZMass_ss->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB);
     myhists->ZMass_other->at(iThread - 1)->Fill(ZBoson.M(), Weight * isOther);
     myhists->ZMass_total->at(iThread - 1)->Fill(ZBoson.M(), Weight);

     myhists->ZMassAddEta->at(iThread - 1)->Fill(ZBoson.M() * (fabs(Electron.Eta()) + 1.0), Weight);

     if(RootType != "FittingCMSData"){
/*       myhists->ZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
       myhists->ZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
       myhists->ZMass_ZY_QT_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isSSB);
       myhists->ZMass_ZY_QT_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCCB);
       myhists->ZMass_ZY_QT_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isBBB);

       myhists->FZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isUUB);
       myhists->BZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isUUB);
       myhists->FZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkF * isDDB);
       myhists->BZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isQuarkB * isDDB);

       myhists->ChangePDF_FZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isQuarkF * isUUB);
       myhists->ChangePDF_BZMass_ZY_QT_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isQuarkB * isUUB);
       myhists->ChangePDF_FZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isQuarkF * isDDB);
       myhists->ChangePDF_BZMass_ZY_QT_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isQuarkB * isDDB);

       myhists->ZMass_ZY_QT_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB);
       myhists->ZMass_ZY_QT_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isUUB * isWrong);
       myhists->ZMass_ZY_QT_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB);
       myhists->ZMass_ZY_QT_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isDDB * isWrong);

       myhists->ChangePDF_ZMass_ZY_QT_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isUUB);
       myhists->ChangePDF_ZMass_ZY_QT_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isUUB * isWrong);
       myhists->ChangePDF_ZMass_ZY_QT_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isDDB);
       myhists->ChangePDF_ZMass_ZY_QT_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight * isDDB * isWrong);
*/
     }
   }

   if(RootType != "FittingCMSData"){
//     myhists->ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);
//     myhists->ChangePDF_ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * ZEventPDFWeight);
   }

//   myhists->FZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
//   myhists->BZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);

//   myhists->ZRapidity->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
//   myhists->ChangePDF_ZRapidity->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * ZEventPDFWeight);

}

void loopFlavorAsym::FillWEvents()
{
   WEventPDFWeight = 1.0;
   Neutrino.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, FlavorAsymTree->ElectronPz, FlavorAsymTree->ElectronE);
   Lepton.SetPxPyPzE(FlavorAsymTree->PositronPx, FlavorAsymTree->PositronPy, FlavorAsymTree->PositronPz, FlavorAsymTree->PositronE);
   WBoson = Neutrino + Lepton;

   Weight = FlavorAsymTree->Weight;

   bool isJacobianAsym = (WBoson.M() > 66) && (WBoson.M() < 116)
                      && (WMT > 27)
                      && (Lepton.Pt() > 20)
                      && (fabs(Lepton.Eta()) < 2.5);

   bool isJacobianAsymLowQT = (WBoson.M() > 66) && (WBoson.M() < 116)
                           && (WMT > 27)
                           && (WBoson.Pt() < 15)
                           && (Lepton.Pt() > 20)
                           && (fabs(Lepton.Eta()) < 2.5);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////
   //  Calculate neutrino pz in reconstructed level  //
   ////////////////////////////////////////////////////

/*
   double Met = Neutrino.Pt();

   TLorentzVector Neutrino_reco_80385;
   TLorentzVector Neutrino_reco_80395;
   TLorentzVector Neutrino_reco_80375;
   Neutrino_reco_80385.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, 0.0, Met);
   Neutrino_reco_80395.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, 0.0, Met);
   Neutrino_reco_80375.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, 0.0, Met);

   double Mpz_80385 = CalculateNeutrinoPz(Lepton, Neutrino_reco_80385, 80.385);
   double Mpz_80395 = CalculateNeutrinoPz(Lepton, Neutrino_reco_80395, 80.395);
   double Mpz_80375 = CalculateNeutrinoPz(Lepton, Neutrino_reco_80375, 80.375);

   double NeutrinoE_80385 = sqrt(Mpz_80385 * Mpz_80385 + Met * Met);
   double NeutrinoE_80395 = sqrt(Mpz_80395 * Mpz_80395 + Met * Met);
   double NeutrinoE_80375 = sqrt(Mpz_80375 * Mpz_80375 + Met * Met);

   Neutrino_reco_80385.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, Mpz_80385, NeutrinoE_80385);
   Neutrino_reco_80395.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, Mpz_80395, NeutrinoE_80395);
   Neutrino_reco_80375.SetPxPyPzE(FlavorAsymTree->ElectronPx, FlavorAsymTree->ElectronPy, Mpz_80375, NeutrinoE_80375);

   TLorentzVector WBoson_reco_80385;
   TLorentzVector WBoson_reco_80395;
   TLorentzVector WBoson_reco_80375;
   WBoson_reco_80385 = Neutrino_reco_80385 + Lepton;
   WBoson_reco_80395 = Neutrino_reco_80395 + Lepton;
   WBoson_reco_80375 = Neutrino_reco_80375 + Lepton;

*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   WMT = CalculateTransverseMass(Lepton, Neutrino);

   bool is_udbar = (fabs(fabs(FlavorAsymTree->Type) - 112.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_usbar = (fabs(fabs(FlavorAsymTree->Type) - 113.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_ubbar = (fabs(fabs(FlavorAsymTree->Type) - 115.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_cdbar = (fabs(fabs(FlavorAsymTree->Type) - 142.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_csbar = (fabs(fabs(FlavorAsymTree->Type) - 143.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_cbbar = (fabs(fabs(FlavorAsymTree->Type) - 145.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_dbaru = (fabs(fabs(FlavorAsymTree->Type) - 112.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_sbaru = (fabs(fabs(FlavorAsymTree->Type) - 113.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_bbaru = (fabs(fabs(FlavorAsymTree->Type) - 115.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_dbarc = (fabs(fabs(FlavorAsymTree->Type) - 142.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_sbarc = (fabs(fabs(FlavorAsymTree->Type) - 143.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_bbarc = (fabs(fabs(FlavorAsymTree->Type) - 145.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_dubar = (fabs(fabs(FlavorAsymTree->Type) - 212.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_subar = (fabs(fabs(FlavorAsymTree->Type) - 213.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_bubar = (fabs(fabs(FlavorAsymTree->Type) - 215.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_dcbar = (fabs(fabs(FlavorAsymTree->Type) - 242.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_scbar = (fabs(fabs(FlavorAsymTree->Type) - 243.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_bcbar = (fabs(fabs(FlavorAsymTree->Type) - 245.0) < 1e-10) && FlavorAsymTree->Type > 0;
   bool is_ubard = (fabs(fabs(FlavorAsymTree->Type) - 212.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_ubars = (fabs(fabs(FlavorAsymTree->Type) - 213.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_ubarb = (fabs(fabs(FlavorAsymTree->Type) - 215.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_cbard = (fabs(fabs(FlavorAsymTree->Type) - 242.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_cbars = (fabs(fabs(FlavorAsymTree->Type) - 243.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_cbarb = (fabs(fabs(FlavorAsymTree->Type) - 245.0) < 1e-10) && FlavorAsymTree->Type < 0;
   bool is_other = is_usbar || is_ubbar || is_cdbar || is_cbbar || is_sbaru || is_bbaru || is_dbarc || is_bbarc
                || is_subar || is_bubar || is_dcbar || is_bcbar || is_ubars || is_ubarb || is_cbard || is_cbarb;
   
   if(is_udbar){Quark1Flavor = 2; Quark2Flavor = -1;}
   if(is_usbar){Quark1Flavor = 2; Quark2Flavor = -3;}
   if(is_ubbar){Quark1Flavor = 2; Quark2Flavor = -5;}
   if(is_cdbar){Quark1Flavor = 4; Quark2Flavor = -1;}
   if(is_csbar){Quark1Flavor = 4; Quark2Flavor = -3;}
   if(is_cbbar){Quark1Flavor = 4; Quark2Flavor = -5;}
   if(is_dbaru){Quark1Flavor = -1; Quark2Flavor = 2;}
   if(is_sbaru){Quark1Flavor = -3; Quark2Flavor = 2;}
   if(is_bbaru){Quark1Flavor = -5; Quark2Flavor = 2;}
   if(is_dbarc){Quark1Flavor = -1; Quark2Flavor = 4;}
   if(is_sbarc){Quark1Flavor = -3; Quark2Flavor = 4;}
   if(is_bbarc){Quark1Flavor = -5; Quark2Flavor = 4;}
   if(is_dubar){Quark1Flavor = 1; Quark2Flavor = -2;}
   if(is_subar){Quark1Flavor = 3; Quark2Flavor = -2;}
   if(is_bubar){Quark1Flavor = 5; Quark2Flavor = -2;}
   if(is_dcbar){Quark1Flavor = 1; Quark2Flavor = -4;}
   if(is_scbar){Quark1Flavor = 3; Quark2Flavor = -4;}
   if(is_bcbar){Quark1Flavor = 5; Quark2Flavor = -4;}
   if(is_ubard){Quark1Flavor = -2; Quark2Flavor = 1;}
   if(is_ubars){Quark1Flavor = -2; Quark2Flavor = 3;}
   if(is_ubarb){Quark1Flavor = -2; Quark2Flavor = 5;}
   if(is_cbard){Quark1Flavor = -4; Quark2Flavor = 1;}
   if(is_cbars){Quark1Flavor = -4; Quark2Flavor = 3;}
   if(is_cbarb){Quark1Flavor = -4; Quark2Flavor = 5;}

   bool is_d = is_dubar || is_ubard || is_dcbar || is_cbard;
   bool is_s = is_subar || is_ubars || is_scbar || is_cbars;

   double x1 = (sqrt(WBoson.M() * WBoson.M() + WBoson.Pt() * WBoson.Pt()) / ECM) * exp(WBoson.Rapidity());
   double x2 = (sqrt(WBoson.M() * WBoson.M() + WBoson.Pt() * WBoson.Pt()) / ECM) * exp(WBoson.Rapidity() * (-1.0));
   //WEventPDFWeight = GetWStrangeWeight(x1, x2, Quark1Flavor, Quark2Flavor, WBoson.M(), 2.0);

   double PDFWeight = 1.0;
   //PDFWeight = GetPDFReweightingFactor(x1, x2, Quark1Flavor, Quark2Flavor, WBoson.M());
   Weight = Weight * PDFWeight;

   bool isWPlus = false;
   bool isWMinus = false;
   if(fabs(FlavorAsymTree->Type) > 100 && fabs(FlavorAsymTree->Type) < 200) isWPlus = true;
   if(fabs(FlavorAsymTree->Type) > 200) isWMinus = true;

   double cos_theta;
   if(isWPlus) cos_theta = (-1.0) * calculate_theta(WBoson, Lepton, Neutrino) * WBoson.Rapidity() / fabs(WBoson.Rapidity());
   if(isWMinus) cos_theta = calculate_theta(WBoson, Lepton, Neutrino) * WBoson.Rapidity() / fabs(WBoson.Rapidity());
   bool isF = false;
   bool isB = false;
   isF = (cos_theta > 0);
   isB = (cos_theta < 0);

   double CosThetaQ;
   if(isWPlus){
     if(FlavorAsymTree->Type > 0) CosThetaQ = calculate_theta(WBoson, Neutrino, Lepton);
     if(FlavorAsymTree->Type < 0) CosThetaQ = calculate_theta(WBoson, Neutrino, Lepton) * (-1.0);
   }
   if(isWMinus){
     if(FlavorAsymTree->Type > 0) CosThetaQ = calculate_theta(WBoson, Lepton, Neutrino);
     if(FlavorAsymTree->Type < 0) CosThetaQ = calculate_theta(WBoson, Lepton, Neutrino) * (-1.0);
   }
   bool isQuarkF = false;
   bool isQuarkB = false;
   isQuarkF = (CosThetaQ > 0);
   isQuarkB = (CosThetaQ < 0);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////
   //  Calculate cos theta in reconstructed level  //
   //////////////////////////////////////////////////

/*
   double cos_theta_reco_80385;
   if(isWPlus) cos_theta_reco_80385 = (-1.0) * calculate_theta(WBoson_reco_80385, Lepton, Neutrino_reco_80385) * WBoson_reco_80385.Rapidity() / fabs(WBoson_reco_80385.Rapidity());
   if(isWMinus) cos_theta_reco_80385 = calculate_theta(WBoson_reco_80385, Lepton, Neutrino_reco_80385) * WBoson_reco_80385.Rapidity() / fabs(WBoson_reco_80385.Rapidity());
   bool isF_reco_80385 = false;
   bool isB_reco_80385 = false;
   isF_reco_80385 = (cos_theta_reco_80385 > 0);
   isB_reco_80385 = (cos_theta_reco_80385 < 0);

   double cos_theta_reco_80395;
   if(isWPlus) cos_theta_reco_80395 = (-1.0) * calculate_theta(WBoson_reco_80395, Lepton, Neutrino_reco_80395) * WBoson_reco_80395.Rapidity() / fabs(WBoson_reco_80395.Rapidity());
   if(isWMinus) cos_theta_reco_80395 = calculate_theta(WBoson_reco_80395, Lepton, Neutrino_reco_80395) * WBoson_reco_80395.Rapidity() / fabs(WBoson_reco_80395.Rapidity());
   bool isF_reco_80395 = false;
   bool isB_reco_80395 = false;
   isF_reco_80395 = (cos_theta_reco_80395 > 0);
   isB_reco_80395 = (cos_theta_reco_80395 < 0);

   double cos_theta_reco_80375;
   if(isWPlus) cos_theta_reco_80375 = (-1.0) * calculate_theta(WBoson_reco_80375, Lepton, Neutrino_reco_80375) * WBoson_reco_80375.Rapidity() / fabs(WBoson_reco_80375.Rapidity());
   if(isWMinus) cos_theta_reco_80375 = calculate_theta(WBoson_reco_80375, Lepton, Neutrino_reco_80375) * WBoson_reco_80375.Rapidity() / fabs(WBoson_reco_80375.Rapidity());
   bool isF_reco_80375 = false;
   bool isB_reco_80375 = false;
   isF_reco_80375 = (cos_theta_reco_80375 > 0);
   isB_reco_80375 = (cos_theta_reco_80375 < 0);
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   int isWrong = 0;
   if(FlavorAsymTree->Type > 0){
     if(WBoson.Rapidity() / fabs(WBoson.Rapidity()) > 0) isWrong = 0;
     if(WBoson.Rapidity() / fabs(WBoson.Rapidity()) < 0) isWrong = 1;
   }
   if(FlavorAsymTree->Type < 0){
     if(WBoson.Rapidity() / fabs(WBoson.Rapidity()) > 0) isWrong = 1;
     if(WBoson.Rapidity() / fabs(WBoson.Rapidity()) < 0) isWrong = 0;
   }

   myhists->WY_udbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_udbar);
   myhists->WY_usbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_usbar);
   myhists->WY_ubbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_ubbar);
   myhists->WY_cdbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_cdbar);
   myhists->WY_csbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_csbar);
   myhists->WY_cbbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_cbbar);
   myhists->WY_dbaru->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_dbaru);
   myhists->WY_sbaru->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_sbaru);
   myhists->WY_bbaru->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_bbaru);
   myhists->WY_dbarc->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_dbarc);
   myhists->WY_sbarc->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_sbarc);
   myhists->WY_bbarc->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_bbarc);
   myhists->WY_dubar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_dubar);
   myhists->WY_subar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_subar);
   myhists->WY_bubar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_bubar);
   myhists->WY_dcbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_dcbar);
   myhists->WY_scbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_scbar);
   myhists->WY_bcbar->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_bcbar);
   myhists->WY_ubard->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_ubard);
   myhists->WY_ubars->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_ubars);
   myhists->WY_ubarb->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_ubarb);
   myhists->WY_cbard->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_cbard);
   myhists->WY_cbars->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_cbars);
   myhists->WY_cbarb->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * is_cbarb);

   myhists->LeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isJacobianAsymLowQT);
   myhists->LeptonPt_WMinus->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isWMinus * isJacobianAsymLowQT);
   myhists->LeptonPt_d->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_d * isJacobianAsymLowQT);
   myhists->LeptonPt_s->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_s * isJacobianAsymLowQT);
   myhists->LeptonPt_udbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_udbar * isJacobianAsymLowQT);
   myhists->LeptonPt_usbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_usbar * isJacobianAsymLowQT);
   myhists->LeptonPt_ubbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_ubbar * isJacobianAsymLowQT);
   myhists->LeptonPt_cdbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_cdbar * isJacobianAsymLowQT);
   myhists->LeptonPt_csbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_csbar * isJacobianAsymLowQT);
   myhists->LeptonPt_cbbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_cbbar * isJacobianAsymLowQT);
   myhists->LeptonPt_dbaru->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_dbaru * isJacobianAsymLowQT);
   myhists->LeptonPt_sbaru->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_sbaru * isJacobianAsymLowQT);
   myhists->LeptonPt_bbaru->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_bbaru * isJacobianAsymLowQT);
   myhists->LeptonPt_dbarc->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_dbarc * isJacobianAsymLowQT);
   myhists->LeptonPt_sbarc->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_sbarc * isJacobianAsymLowQT);
   myhists->LeptonPt_bbarc->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_bbarc * isJacobianAsymLowQT);
   myhists->LeptonPt_dubar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_dubar * isJacobianAsymLowQT);
   myhists->LeptonPt_subar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_subar * isJacobianAsymLowQT);
   myhists->LeptonPt_bubar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_bubar * isJacobianAsymLowQT);
   myhists->LeptonPt_dcbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_dcbar * isJacobianAsymLowQT);
   myhists->LeptonPt_scbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_scbar * isJacobianAsymLowQT);
   myhists->LeptonPt_bcbar->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_bcbar * isJacobianAsymLowQT);
   myhists->LeptonPt_ubard->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_ubard * isJacobianAsymLowQT);
   myhists->LeptonPt_ubars->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_ubars * isJacobianAsymLowQT);
   myhists->LeptonPt_ubarb->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_ubarb * isJacobianAsymLowQT);
   myhists->LeptonPt_cbard->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_cbard * isJacobianAsymLowQT);
   myhists->LeptonPt_cbars->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_cbars * isJacobianAsymLowQT);
   myhists->LeptonPt_cbarb->at(iThread - 1)->Fill(Lepton.Pt(), Weight * is_cbarb * isJacobianAsymLowQT);

   myhists->PositiveLeptonEta_udbar->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_udbar);
   myhists->PositiveLeptonEta_csbar->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_csbar);
   myhists->PositiveLeptonEta_dbaru->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_dbaru);
   myhists->PositiveLeptonEta_sbarc->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_sbarc);
   myhists->PositiveLeptonEta_other->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_other * isWPlus);

   myhists->PositiveLeptonEta_ud->at(iThread - 1)->Fill(Lepton.Eta(), Weight * (is_udbar || is_dbaru));
   myhists->PositiveLeptonEta_cs->at(iThread - 1)->Fill(Lepton.Eta(), Weight * (is_csbar || is_sbarc));

   myhists->NegativeLeptonEta_dubar->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_dubar);
   myhists->NegativeLeptonEta_scbar->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_scbar);
   myhists->NegativeLeptonEta_ubard->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_ubard);
   myhists->NegativeLeptonEta_cbars->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_cbars);
   myhists->NegativeLeptonEta_other->at(iThread - 1)->Fill(Lepton.Eta(), Weight * is_other * isWMinus);

   myhists->NegativeLeptonEta_ud->at(iThread - 1)->Fill(Lepton.Eta(), Weight * (is_dubar || is_ubard));
   myhists->NegativeLeptonEta_cs->at(iThread - 1)->Fill(Lepton.Eta(), Weight * (is_scbar || is_cbars));

   myhists->PositiveLeptonEtaMT_udbar->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_udbar);
   myhists->PositiveLeptonEtaMT_csbar->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_csbar);
   myhists->PositiveLeptonEtaMT_dbaru->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_dbaru);
   myhists->PositiveLeptonEtaMT_sbarc->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_sbarc);
   myhists->PositiveLeptonEtaMT_other->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_other * isWPlus);

   myhists->PositiveLeptonEtaMT_ud->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * (is_udbar || is_dbaru));
   myhists->PositiveLeptonEtaMT_cs->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * (is_csbar || is_sbarc));

   myhists->NegativeLeptonEtaMT_dubar->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_dubar);
   myhists->NegativeLeptonEtaMT_scbar->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_scbar);
   myhists->NegativeLeptonEtaMT_ubard->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_ubard);
   myhists->NegativeLeptonEtaMT_cbars->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_cbars);
   myhists->NegativeLeptonEtaMT_other->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * is_other * isWMinus);

   myhists->NegativeLeptonEtaMT_ud->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * (is_dubar || is_ubard));
   myhists->NegativeLeptonEtaMT_cs->at(iThread - 1)->Fill(Lepton.Eta(), WMT, Weight * (is_scbar || is_cbars));

   myhists->PositiveNeutrinoEta_udbar->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_udbar);
   myhists->PositiveNeutrinoEta_csbar->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_csbar);
   myhists->PositiveNeutrinoEta_dbaru->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_dbaru);
   myhists->PositiveNeutrinoEta_sbarc->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_sbarc);
   myhists->PositiveNeutrinoEta_other->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_other * isWPlus);

   myhists->PositiveNeutrinoEta_ud->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * (is_udbar || is_dbaru));
   myhists->PositiveNeutrinoEta_cs->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * (is_csbar || is_sbarc));

   myhists->NegativeNeutrinoEta_dubar->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_dubar);
   myhists->NegativeNeutrinoEta_scbar->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_scbar);
   myhists->NegativeNeutrinoEta_ubard->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_ubard);
   myhists->NegativeNeutrinoEta_cbars->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_cbars);
   myhists->NegativeNeutrinoEta_other->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * is_other * isWMinus);

   myhists->NegativeNeutrinoEta_ud->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * (is_dubar || is_ubard));
   myhists->NegativeNeutrinoEta_cs->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * (is_scbar || is_cbars));

   myhists->PositiveNeutrinoEtaMT_udbar->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_udbar);
   myhists->PositiveNeutrinoEtaMT_csbar->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_csbar);
   myhists->PositiveNeutrinoEtaMT_dbaru->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_dbaru);
   myhists->PositiveNeutrinoEtaMT_sbarc->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_sbarc);
   myhists->PositiveNeutrinoEtaMT_other->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_other * isWPlus);

   myhists->PositiveNeutrinoEtaMT_ud->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * (is_udbar || is_dbaru));
   myhists->PositiveNeutrinoEtaMT_cs->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * (is_csbar || is_sbarc));

   myhists->NegativeNeutrinoEtaMT_dubar->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_dubar);
   myhists->NegativeNeutrinoEtaMT_scbar->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_scbar);
   myhists->NegativeNeutrinoEtaMT_ubard->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_ubard);
   myhists->NegativeNeutrinoEtaMT_cbars->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_cbars);
   myhists->NegativeNeutrinoEtaMT_other->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * is_other * isWMinus);

   myhists->NegativeNeutrinoEtaMT_ud->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * (is_dubar || is_ubard));
   myhists->NegativeNeutrinoEtaMT_cs->at(iThread - 1)->Fill(Neutrino.Eta(), WMT, Weight * (is_scbar || is_cbars));

   myhists->WPlusForwardMT_quark->at(iThread - 1)->Fill(WMT, Weight * isWPlus * isQuarkF);
   myhists->WPlusBackwardMT_quark->at(iThread - 1)->Fill(WMT, Weight * isWPlus * isQuarkB);
   myhists->WMinusForwardMT_quark->at(iThread - 1)->Fill(WMT, Weight * isWMinus * isQuarkF);
   myhists->WMinusBackwardMT_quark->at(iThread - 1)->Fill(WMT, Weight * isWMinus * isQuarkB);

   double EtaCutDef = 3.8;
   myhists->WPlusMT_ForwardEta->at(iThread - 1)->Fill(WMT, Weight * isWPlus * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WPlusMT_CentralEta->at(iThread - 1)->Fill(WMT, Weight * isWPlus * (fabs(Lepton.Eta()) < EtaCutDef));
   myhists->WMinusMT_ForwardEta->at(iThread - 1)->Fill(WMT, Weight * isWMinus * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WMinusMT_CentralEta->at(iThread - 1)->Fill(WMT, Weight * isWMinus * (fabs(Lepton.Eta()) < EtaCutDef));

   myhists->WPlusMT_ForwardEta_ud->at(iThread - 1)->Fill(WMT, Weight * (is_udbar || is_dbaru) * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WPlusMT_CentralEta_ud->at(iThread - 1)->Fill(WMT, Weight * (is_udbar || is_dbaru) * (fabs(Lepton.Eta()) < EtaCutDef));
   myhists->WMinusMT_ForwardEta_ud->at(iThread - 1)->Fill(WMT, Weight * (is_dubar || is_ubard) * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WMinusMT_CentralEta_ud->at(iThread - 1)->Fill(WMT, Weight * (is_dubar || is_ubard) * (fabs(Lepton.Eta()) < EtaCutDef));

   myhists->WPlusMT_ForwardEta_cs->at(iThread - 1)->Fill(WMT, Weight * (is_csbar || is_sbarc) * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WPlusMT_CentralEta_cs->at(iThread - 1)->Fill(WMT, Weight * (is_csbar || is_sbarc) * (fabs(Lepton.Eta()) < EtaCutDef));
   myhists->WMinusMT_ForwardEta_cs->at(iThread - 1)->Fill(WMT, Weight * (is_scbar || is_cbars) * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WMinusMT_CentralEta_cs->at(iThread - 1)->Fill(WMT, Weight * (is_scbar || is_cbars) * (fabs(Lepton.Eta()) < EtaCutDef));

   myhists->WPlusMT_ForwardEta_other->at(iThread - 1)->Fill(WMT, Weight * is_other * isWPlus * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WPlusMT_CentralEta_other->at(iThread - 1)->Fill(WMT, Weight * is_other * isWPlus * (fabs(Lepton.Eta()) < EtaCutDef));
   myhists->WMinusMT_ForwardEta_other->at(iThread - 1)->Fill(WMT, Weight * is_other * isWMinus * (fabs(Lepton.Eta()) > EtaCutDef));
   myhists->WMinusMT_CentralEta_other->at(iThread - 1)->Fill(WMT, Weight * is_other * isWMinus * (fabs(Lepton.Eta()) < EtaCutDef));

   myhists->WPlusMT_ud->at(iThread - 1)->Fill(WMT, Weight * (is_udbar || is_dbaru));
   myhists->WMinusMT_ud->at(iThread - 1)->Fill(WMT, Weight * (is_dubar || is_ubard));
   myhists->WPlusMT_cs->at(iThread - 1)->Fill(WMT, Weight * (is_csbar || is_sbarc));
   myhists->WMinusMT_cs->at(iThread - 1)->Fill(WMT, Weight * (is_scbar || is_cbars));
   myhists->WPlusMT_other->at(iThread - 1)->Fill(WMT, Weight * is_other * isWPlus);
   myhists->WMinusMT_other->at(iThread - 1)->Fill(WMT, Weight * is_other * isWMinus);
   myhists->WPlusMT_total->at(iThread - 1)->Fill(WMT, Weight * isWPlus);
   myhists->WMinusMT_total->at(iThread - 1)->Fill(WMT, Weight * isWMinus);



/*   myhists->WY_udbar_total->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (is_udbar || is_dbaru));
   myhists->WY_csbar_total->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (is_csbar || is_sbarc));
   myhists->WY_dubar_total->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (is_dubar || is_ubard));
   myhists->WY_scbar_total->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * (is_scbar || is_cbars));
   myhists->WPlusY->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWPlus);
   myhists->WMinusY->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWMinus);

   myhists->AntiLeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWPlus);
   myhists->LeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWMinus);
   myhists->ChangePDF_AntiLeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), FlavorAsymTree->Weight * isWPlus * WEventPDFWeight);
   myhists->ChangePDF_LeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), FlavorAsymTree->Weight * isWMinus * WEventPDFWeight);

   myhists->FWPlusY->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWPlus * isF);
   myhists->BWPlusY->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWPlus * isB);
   myhists->FWMinusY->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWMinus * isF);
   myhists->BWMinusY->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWMinus * isB);
   myhists->FWPlusY_reco_80385->at(iThread - 1)->Fill(WBoson_reco_80385.Rapidity(), Weight * isWPlus * isF_reco_80385);
   myhists->BWPlusY_reco_80385->at(iThread - 1)->Fill(WBoson_reco_80385.Rapidity(), Weight * isWPlus * isB_reco_80385);
   myhists->FWMinusY_reco_80385->at(iThread - 1)->Fill(WBoson_reco_80385.Rapidity(), Weight * isWMinus * isF_reco_80385);
   myhists->BWMinusY_reco_80385->at(iThread - 1)->Fill(WBoson_reco_80385.Rapidity(), Weight * isWMinus * isB_reco_80385);
   myhists->FWPlusY_reco_80395->at(iThread - 1)->Fill(WBoson_reco_80395.Rapidity(), Weight * isWPlus * isF_reco_80395);
   myhists->BWPlusY_reco_80395->at(iThread - 1)->Fill(WBoson_reco_80395.Rapidity(), Weight * isWPlus * isB_reco_80395);
   myhists->FWMinusY_reco_80395->at(iThread - 1)->Fill(WBoson_reco_80395.Rapidity(), Weight * isWMinus * isF_reco_80395);
   myhists->BWMinusY_reco_80395->at(iThread - 1)->Fill(WBoson_reco_80395.Rapidity(), Weight * isWMinus * isB_reco_80395);
   myhists->FWPlusY_reco_80375->at(iThread - 1)->Fill(WBoson_reco_80375.Rapidity(), Weight * isWPlus * isF_reco_80375);
   myhists->BWPlusY_reco_80375->at(iThread - 1)->Fill(WBoson_reco_80375.Rapidity(), Weight * isWPlus * isB_reco_80375);
   myhists->FWMinusY_reco_80375->at(iThread - 1)->Fill(WBoson_reco_80375.Rapidity(), Weight * isWMinus * isF_reco_80375);
   myhists->BWMinusY_reco_80375->at(iThread - 1)->Fill(WBoson_reco_80375.Rapidity(), Weight * isWMinus * isB_reco_80375);
   myhists->FWPlusMass->at(iThread - 1)->Fill(WBoson.M(), Weight * isWPlus * isF);
   myhists->BWPlusMass->at(iThread - 1)->Fill(WBoson.M(), Weight * isWPlus * isB);
   myhists->FWMinusMass->at(iThread - 1)->Fill(WBoson.M(), Weight * isWMinus * isF);
   myhists->BWMinusMass->at(iThread - 1)->Fill(WBoson.M(), Weight * isWMinus * isB);
   myhists->WPlusY_total->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWPlus);
   myhists->WPlusY_wrong->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWPlus * isWrong);
   myhists->WMinusY_total->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWMinus);
   myhists->WMinusY_wrong->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight * isWMinus * isWrong);
*/

}

double loopFlavorAsym::GetPDFReweightingFactor(double x1, double x2, int flavor1, int flavor2, double Q)
{
 double Value = 1.0;
 if(!isPDFReweight){
   //cout<<"ERROR! Please initialize PDF at first."<<endl;
   return 1.0;
 }

 Value = myPDFReweight->GetPDFReweightFactor(flavor1, flavor2, x1, x2, Q);

 if(Value > 5000.0 || Value < 0.0){
   //ProblemEventNumber++;
   Value = 1.0;
 }

 return Value;
}

double loopFlavorAsym::GetZPDFWeight(double LargeX, double SmallX, int flavor, double Q, double Delta)
{
 double Value = 1.0;

 if(flavor == 2){//uubar + delta (right events)
   double OriginF1 = myPDFReweight->Getf(2, LargeX, Q);
   double OriginF2 = myPDFReweight->Getf(-2, SmallX, Q);
   double ChangeF1 = myPDFReweight->Getf(2, LargeX, Q);
   double ChangeF2 = myPDFReweight->Getf(-2, SmallX, Q) + Delta;

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor == 1){//ddbar - delta (right events)
   double OriginF1 = myPDFReweight->Getf(1, LargeX, Q);
   double OriginF2 = myPDFReweight->Getf(-1, SmallX, Q);
   double ChangeF1 = myPDFReweight->Getf(1, LargeX, Q);
   double ChangeF2 = myPDFReweight->Getf(-1, SmallX, Q) - Delta;
 
   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor == -2){//uubar + delta (wrong events)
   double OriginF1 = myPDFReweight->Getf(2, SmallX, Q);
   double OriginF2 = myPDFReweight->Getf(-2, LargeX, Q);
   double ChangeF1 = myPDFReweight->Getf(2, SmallX, Q) + Delta;
   double ChangeF2 = myPDFReweight->Getf(-2, LargeX, Q);

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor == -1){//ddbar - delta (wrong events)
   double OriginF1 = myPDFReweight->Getf(1, SmallX, Q);
   double OriginF2 = myPDFReweight->Getf(-1, LargeX, Q);
   double ChangeF1 = myPDFReweight->Getf(1, SmallX, Q) - Delta;
   double ChangeF2 = myPDFReweight->Getf(-1, LargeX, Q);

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }


 return Value;
}

double loopFlavorAsym::GetWPDFWeight(double LargeX, double SmallX, int flavor, double Q, double Delta)
{
 return 1.0;
}

double loopFlavorAsym::GetZStrangeWeight(double x1, double x2, int flavor, double Q, double Delta)
{
 double Value = 1.0;

 bool inRange = (x1 > 0.001 && x1 < 0.05) && (x2 > 0.001 && x2 < 0.05);

/* if(flavor == 1 && inRange){
   double OriginF1 = myPDFReweight->Getf(1, x1, Q);
   double OriginF2 = myPDFReweight->Getf(-1, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(1, x1, Q);
   double ChangeF2 = myPDFReweight->Getf(-1, x2, Q) + Delta;

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor == -1 && inRange){
   double OriginF1 = myPDFReweight->Getf(-1, x1, Q);
   double OriginF2 = myPDFReweight->Getf(1, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(-1, x1, Q) + Delta;
   double ChangeF2 = myPDFReweight->Getf(1, x2, Q);

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
*/ if(flavor == 2 && inRange){
   double OriginF1 = myPDFReweight->Getf(2, x1, Q);
   double OriginF2 = myPDFReweight->Getf(-2, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(2, x1, Q);
   double ChangeF2 = myPDFReweight->Getf(-2, x2, Q) - Delta;

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor == -2 && inRange){
   double OriginF1 = myPDFReweight->Getf(-2, x1, Q);
   double OriginF2 = myPDFReweight->Getf(2, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(-2, x1, Q) - Delta;
   double ChangeF2 = myPDFReweight->Getf(2, x2, Q);

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }



 //if(Value > 1.001) Value = 1.0;

 return Value;
}

double loopFlavorAsym::GetWStrangeWeight(double x1, double x2, int flavor1, int flavor2, double Q, double Delta)
{
 double Value = 1.0;

 bool inRange = (x1 > 0.001 && x1 < 0.05) && (x2 > 0.001 && x2 < 0.05);

/* if(flavor1 == -1 && inRange){
   double OriginF1 = myPDFReweight->Getf(flavor1, x1, Q);
   double OriginF2 = myPDFReweight->Getf(flavor2, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(flavor1, x1, Q) + Delta;
   double ChangeF2 = myPDFReweight->Getf(flavor2, x2, Q);

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor2 == -1 && inRange){
   double OriginF1 = myPDFReweight->Getf(flavor1, x1, Q);
   double OriginF2 = myPDFReweight->Getf(flavor2, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(flavor1, x1, Q);
   double ChangeF2 = myPDFReweight->Getf(flavor2, x2, Q) + Delta;

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
*/ if(flavor1 == -2 && inRange){
   double OriginF1 = myPDFReweight->Getf(flavor1, x1, Q);
   double OriginF2 = myPDFReweight->Getf(flavor2, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(flavor1, x1, Q) - Delta;
   double ChangeF2 = myPDFReweight->Getf(flavor2, x2, Q);

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }
 if(flavor2 == -2 && inRange){
   double OriginF1 = myPDFReweight->Getf(flavor1, x1, Q);
   double OriginF2 = myPDFReweight->Getf(flavor2, x2, Q);
   double ChangeF1 = myPDFReweight->Getf(flavor1, x1, Q);
   double ChangeF2 = myPDFReweight->Getf(flavor2, x2, Q) - Delta;

   Value = (ChangeF1 * ChangeF2) / (OriginF1 * OriginF2);
 }

 //if(Value > 1.1) Value = 1.0;

 return Value;
}

void loopFlavorAsym::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!FlavorAsymTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete FlavorAsymTree->fChain[RootNumber]->GetCurrentFile();
}

void loopFlavorAsym::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete FlavorAsymTree;

}

loopFlavorAsym::~loopFlavorAsym()
{
}
