#define loopPythiaWW_cxx
#include <iostream>
#include "Analysis/loopPythiaWW.h"

using namespace std;

loopPythiaWW::loopPythiaWW(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopPythiaWW::InputHist(HistsPythiaWW* &myhists)
{
 this->myhists = myhists;

}

void loopPythiaWW::InputTree(TreeForPythiaWW *PythiaWWTree)
{
 this->PythiaWWTree = PythiaWWTree;
 this->RootNames = PythiaWWTree->RootNames;

 this->FirstFile = PythiaWWTree->FirstFile;
 this->EndFile = PythiaWWTree->EndFile;

 this->OneFilePerJob = PythiaWWTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PythiaWWTree->TotalEntries[ifile];
 }

}

void loopPythiaWW::ReadTree(int ifile)
{
 TLorentzVector lab_z1(0.0, 0.0, 1.0, 1.0);

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"\r"<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<flush;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"\r"<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
     if(!isThread) cout<<"\r"<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<flush;
   }
  
   PythiaWWTree->GetEntry(ifile, iEvent);

   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(PythiaWWTree->ElectronPx, PythiaWWTree->ElectronPy, PythiaWWTree->ElectronPz, PythiaWWTree->ElectronE);
   eNeutrino.SetPxPyPzE(PythiaWWTree->eNeutrinoPx, PythiaWWTree->eNeutrinoPy, PythiaWWTree->eNeutrinoPz, PythiaWWTree->eNeutrinoE);
   Muon.SetPxPyPzE(PythiaWWTree->MuonPx, PythiaWWTree->MuonPy, PythiaWWTree->MuonPz, PythiaWWTree->MuonE);
   mNeutrino.SetPxPyPzE(PythiaWWTree->mNeutrinoPx, PythiaWWTree->mNeutrinoPy, PythiaWWTree->mNeutrinoPz, PythiaWWTree->mNeutrinoE);

   DiNeutrino = eNeutrino + mNeutrino;

   if(PythiaWWTree->ElectronFlavor > 0 && PythiaWWTree->MuonFlavor < 0){
     WPlus = Electron + eNeutrino;
     WMinus = Muon + mNeutrino;
     PositiveLepton = Electron;
     NegativeLepton = Muon;
     Neutrino = eNeutrino;
     AntiNeutrino = mNeutrino;
   }
   if(PythiaWWTree->ElectronFlavor < 0 && PythiaWWTree->MuonFlavor > 0){ 
     WPlus = Muon + mNeutrino;
     WMinus = Electron + eNeutrino;
     PositiveLepton = Muon;
     NegativeLepton = Electron;
     Neutrino = mNeutrino;
     AntiNeutrino = eNeutrino;
   }
   WW = WPlus + WMinus;

   WPlus_CMS = WPlus;
   WMinus_CMS = WMinus;

   WPlus_CMS.Boost(-WW.BoostVector());
   WMinus_CMS.Boost(-WW.BoostVector());

   PositiveLepton_WPlusFrame = PositiveLepton;
   PositiveLepton_WPlusFrame.Boost(-WPlus.BoostVector());
   NegativeLepton_WMinusFrame = NegativeLepton;
   NegativeLepton_WMinusFrame.Boost(-WMinus.BoostVector());
//   PositiveLepton.SetPxPyPzE(PythiaWWTree->AntiLeptonPx, PythiaWWTree->AntiLeptonPy, PythiaWWTree->AntiLeptonPz, PythiaWWTree->AntiLeptonE);
//   NegativeLepton.SetPxPyPzE(PythiaWWTree->LeptonPx, PythiaWWTree->LeptonPy, PythiaWWTree->LeptonPz, PythiaWWTree->LeptonE);

   if(isPDFReweight) PDFReweightFactor = myPDFReweight->GetPDFReweightFactor(PythiaWWTree->quark_flavour[0], PythiaWWTree->quark_flavour[1], PythiaWWTree->QuarkE[0] / 6500, PythiaWWTree->QuarkE[1] / 6500, WW.M());

   if(isTest){
     cout<<"PDF reweight factor = "<<PDFReweightFactor<<endl;
     cout<<endl;
   }

   double Weight = 1.0 * PDFReweightFactor;

   bool isZU = false;
   bool isZD = false;
   if(fabs(PythiaWWTree->quark_flavour[0]) == 2 || fabs(PythiaWWTree->quark_flavour[0]) == 4 || fabs(PythiaWWTree->quark_flavour[0]) == 6) isZU = true;
   if(fabs(PythiaWWTree->quark_flavour[0]) == 1 || fabs(PythiaWWTree->quark_flavour[0]) == 3 || fabs(PythiaWWTree->quark_flavour[0]) == 5) isZD = true;
//   if(fabs(PythiaWWTree->QuarkID) == 2 || fabs(PythiaWWTree->QuarkID) == 4 || fabs(PythiaWWTree->QuarkID) == 6) isZU = true;
//   if(fabs(PythiaWWTree->QuarkID) == 1 || fabs(PythiaWWTree->QuarkID) == 3 || fabs(PythiaWWTree->QuarkID) == 5) isZD = true;

   bool isUUB = false;
   bool isDDB = false;
   bool isSSB = false;
   bool isCCB = false;
   bool isBBB = false;
   bool isGG = false;
   isUUB = (fabs(PythiaWWTree->quark_flavour[0]) == 2);//uu
   isDDB = (fabs(PythiaWWTree->quark_flavour[0]) == 1);//dd
   isSSB = (fabs(PythiaWWTree->quark_flavour[0]) == 3);//ss
   isCCB = (fabs(PythiaWWTree->quark_flavour[0]) == 4);//cc
   isBBB = (fabs(PythiaWWTree->quark_flavour[0]) == 5);//bb
   isGG = (fabs(PythiaWWTree->quark_flavour[0]) == 3 || fabs(PythiaWWTree->quark_flavour[0]) == 4 || fabs(PythiaWWTree->quark_flavour[0]) == 5 || fabs(PythiaWWTree->quark_flavour[0]) == 6);//gg

//   isUUB = (fabs(PythiaWWTree->QuarkID) == 2);//uu
//   isDDB = (fabs(PythiaWWTree->QuarkID) == 1);//dd
//   isSSB = (fabs(PythiaWWTree->QuarkID) == 3);//ss
//   isCCB = (fabs(PythiaWWTree->QuarkID) == 4);//cc
//   isBBB = (fabs(PythiaWWTree->QuarkID) == 5);//bb
//   isGG = (fabs(PythiaWWTree->QuarkID) == 3 || fabs(PythiaWWTree->QuarkID) == 4 || fabs(PythiaWWTree->QuarkID) == 5 || fabs(PythiaWWTree->QuarkID) == 6);//gg

   bool isWrongW = fabs(WPlus.Rapidity()) < fabs(WMinus.Rapidity());
   bool isRightW = fabs(WPlus.Rapidity()) > fabs(WMinus.Rapidity());

   bool isWrong = fabs(PositiveLepton.Eta()) < fabs(NegativeLepton.Eta());
   bool isRight = fabs(PositiveLepton.Eta()) > fabs(NegativeLepton.Eta());

   bool isWrongLepE = PositiveLepton.E() < NegativeLepton.E();
   bool isRightLepE = PositiveLepton.E() > NegativeLepton.E();

   double WYDiff = fabs(fabs(WPlus.Rapidity()) - fabs(WMinus.Rapidity()));
   double EtaDiff = fabs(fabs(PositiveLepton.Eta()) - fabs(NegativeLepton.Eta()));
   double LepEDiff = fabs(PositiveLepton.E() - NegativeLepton.E());

//   double CosThetaPlusDiff = cos(WPlus.Vect().Angle(PositiveLepton.Vect()));
//   double CosThetaMinusDiff = cos(WMinus.Vect().Angle(NegativeLepton.Vect()));
   double CosThetaPlusDiff = PositiveLepton_WPlusFrame.CosTheta();
   double CosThetaMinusDiff = NegativeLepton_WMinusFrame.CosTheta();

   double CosThetaPositiveLeptonNu = cos(PositiveLepton.Vect().Angle(Neutrino.Vect()));
   double CosThetaNegativeLeptonNu = cos(NegativeLepton.Vect().Angle(AntiNeutrino.Vect()));

   int WPlusDecayStatus = -1.0;
   int WMinusDecayStatus = -1.0;
//   if(cos(PositiveLepton.Vect().Angle(lab_z1.Vect())) > 0 && cos(Neutrino.Vect().Angle(lab_z1.Vect())) > 0) WPlusDecayStatus = 0.5;
//   if(cos(PositiveLepton.Vect().Angle(lab_z1.Vect())) > 0 && cos(Neutrino.Vect().Angle(lab_z1.Vect())) < 0) WPlusDecayStatus = 1.5;
//   if(cos(PositiveLepton.Vect().Angle(lab_z1.Vect())) < 0 && cos(Neutrino.Vect().Angle(lab_z1.Vect())) > 0) WPlusDecayStatus = 2.5;
//   if(cos(PositiveLepton.Vect().Angle(lab_z1.Vect())) < 0 && cos(Neutrino.Vect().Angle(lab_z1.Vect())) < 0) WPlusDecayStatus = 3.5;

//   if(cos(NegativeLepton.Vect().Angle(lab_z1.Vect())) > 0 && cos(AntiNeutrino.Vect().Angle(lab_z1.Vect())) > 0) WMinusDecayStatus = 0.5;
//   if(cos(NegativeLepton.Vect().Angle(lab_z1.Vect())) > 0 && cos(AntiNeutrino.Vect().Angle(lab_z1.Vect())) < 0) WMinusDecayStatus = 1.5;
//   if(cos(NegativeLepton.Vect().Angle(lab_z1.Vect())) < 0 && cos(AntiNeutrino.Vect().Angle(lab_z1.Vect())) > 0) WMinusDecayStatus = 2.5;
//   if(cos(NegativeLepton.Vect().Angle(lab_z1.Vect())) < 0 && cos(AntiNeutrino.Vect().Angle(lab_z1.Vect())) < 0) WMinusDecayStatus = 3.5;

//   if(NegativeLepton.CosTheta() > 0 && AntiNeutrino.CosTheta() > 0) WMinusDecayStatus = 0.5;
//   if(NegativeLepton.CosTheta() > 0 && AntiNeutrino.CosTheta() < 0) WMinusDecayStatus = 1.5;
//   if(NegativeLepton.CosTheta() < 0 && AntiNeutrino.CosTheta() > 0) WMinusDecayStatus = 2.5;
//   if(NegativeLepton.CosTheta() < 0 && AntiNeutrino.CosTheta() < 0) WMinusDecayStatus = 3.5;

   if(PositiveLepton.Pz() > 0 && Neutrino.Pz() > 0) WPlusDecayStatus = 0.5;
   if(PositiveLepton.Pz() > 0 && Neutrino.Pz() < 0) WPlusDecayStatus = 1.5;
   if(PositiveLepton.Pz() < 0 && Neutrino.Pz() > 0) WPlusDecayStatus = 2.5;
   if(PositiveLepton.Pz() < 0 && Neutrino.Pz() < 0) WPlusDecayStatus = 3.5;

   if(NegativeLepton.Pz() > 0 && AntiNeutrino.Pz() > 0) WMinusDecayStatus = 0.5;
   if(NegativeLepton.Pz() > 0 && AntiNeutrino.Pz() < 0) WMinusDecayStatus = 1.5;
   if(NegativeLepton.Pz() < 0 && AntiNeutrino.Pz() > 0) WMinusDecayStatus = 2.5;
   if(NegativeLepton.Pz() < 0 && AntiNeutrino.Pz() < 0) WMinusDecayStatus = 3.5;

   if(PositiveLepton.Pt() < 25 || NegativeLepton.Pt() < 25) continue;
   if(DiNeutrino.Pt() < 25) continue;
   if(WW.M() < 160 || WW.M() > 400) continue;
   if(fabs(PositiveLepton.Eta()) > 2.5 || fabs(NegativeLepton.Eta()) > 2.5) continue;


   myhists->Wrong_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong * isUUB);
   myhists->Right_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight * isUUB);
   myhists->Total_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isUUB);

   myhists->Wrong_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong * isDDB);
   myhists->Right_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight * isDDB);
   myhists->Total_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isDDB);

   myhists->Wrong_ss->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong * isSSB);
   myhists->Right_ss->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight * isSSB);
   myhists->Total_ss->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isSSB);

   myhists->Wrong_cc->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong * isCCB);
   myhists->Right_cc->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight * isCCB);
   myhists->Total_cc->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isCCB);

   myhists->Wrong_bb->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong * isBBB);
   myhists->Right_bb->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight * isBBB);
   myhists->Total_bb->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isBBB);

   myhists->Wrong_AllFlavor->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isWrong);
   myhists->Right_AllFlavor->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isRight);
   myhists->Total_AllFlavor->at(iThread - 1)->Fill(fabs(EtaDiff), Weight);

   myhists->WrongW_uu->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrong * isUUB);
   myhists->RightW_uu->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRight * isUUB);
   myhists->TotalW_uu->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isUUB);

   myhists->WrongW_dd->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrong * isDDB);
   myhists->RightW_dd->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRight * isDDB);
   myhists->TotalW_dd->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isDDB);

   myhists->WrongW_ss->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrong * isSSB);
   myhists->RightW_ss->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRight * isSSB);
   myhists->TotalW_ss->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isSSB);

   myhists->WrongW_cc->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrong * isCCB);
   myhists->RightW_cc->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRight * isCCB);
   myhists->TotalW_cc->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isCCB);

   myhists->WrongW_bb->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrong * isBBB);
   myhists->RightW_bb->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRight * isBBB);
   myhists->TotalW_bb->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isBBB);

   myhists->WrongW_AllFlavor->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isWrongW);
   myhists->RightW_AllFlavor->at(iThread - 1)->Fill(fabs(WYDiff), Weight * isRightW);
   myhists->TotalW_AllFlavor->at(iThread - 1)->Fill(fabs(WYDiff), Weight);

   myhists->WrongLepE_AllFlavor->at(iThread - 1)->Fill(fabs(LepEDiff), Weight * isWrongLepE);
   myhists->RightLepE_AllFlavor->at(iThread - 1)->Fill(fabs(LepEDiff), Weight * isRightLepE);
   myhists->TotalLepE_AllFlavor->at(iThread - 1)->Fill(fabs(LepEDiff), Weight);

   myhists->LeptonEta->at(iThread - 1)->Fill(NegativeLepton.Eta(), Weight);
   myhists->AntiLeptonEta->at(iThread - 1)->Fill(PositiveLepton.Eta(), Weight);

   myhists->WPlusRapidity->at(iThread - 1)->Fill(WPlus.Rapidity(), Weight);
   myhists->WMinusRapidity->at(iThread - 1)->Fill(WMinus.Rapidity(), Weight);
   myhists->WPlusPt->at(iThread - 1)->Fill(WPlus.Pt(), Weight);
   myhists->WMinusPt->at(iThread - 1)->Fill(WMinus.Pt(), Weight);

   myhists->WWMass->at(iThread - 1)->Fill(WW.M(), Weight);
   myhists->WWMass_uu->at(iThread - 1)->Fill(WW.M(), Weight * isUUB);
   myhists->WWMass_dd->at(iThread - 1)->Fill(WW.M(), Weight * isDDB);
   myhists->EtaDiff_uu->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isUUB);
   myhists->EtaDiff_dd->at(iThread - 1)->Fill(fabs(EtaDiff), Weight * isDDB);
   myhists->CosThetaPlusDiff->at(iThread - 1)->Fill(CosThetaPlusDiff, Weight);
   myhists->CosThetaMinusDiff->at(iThread - 1)->Fill(CosThetaMinusDiff, Weight);
   myhists->CosThetaPositiveLeptonNu->at(iThread - 1)->Fill(CosThetaPositiveLeptonNu, Weight);
   myhists->CosThetaNegativeLeptonNu->at(iThread - 1)->Fill(CosThetaNegativeLeptonNu, Weight);
   myhists->WPlusDecayStatus->at(iThread - 1)->Fill(WPlusDecayStatus, Weight);
   myhists->WMinusDecayStatus->at(iThread - 1)->Fill(WMinusDecayStatus, Weight);

   myhists->WPlusRapidity_CMS->at(iThread - 1)->Fill(WPlus_CMS.Rapidity(), Weight);
   myhists->WMinusRapidity_CMS->at(iThread - 1)->Fill(WMinus_CMS.Rapidity(), Weight);

 }

}

void loopPythiaWW::End(int RootNumber)
{
 cout<<"\r"<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<"  "<<flush;

 if(!PythiaWWTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete PythiaWWTree->fChain[RootNumber]->GetCurrentFile();
}

void loopPythiaWW::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete PythiaWWTree;

}

loopPythiaWW::~loopPythiaWW()
{
}
