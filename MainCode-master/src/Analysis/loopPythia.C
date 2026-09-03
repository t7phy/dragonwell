#define loopPythia_cxx
#include <iostream>
#include "Analysis/loopPythia.h"

using namespace std;

loopPythia::loopPythia(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopPythia::InputHist(HistsPythia* &myhists)
{
 this->myhists = myhists;

}

void loopPythia::InputTree(TreeForPythia *PythiaTree)
{
 this->PythiaTree = PythiaTree;
 this->RootNames = PythiaTree->RootNames;

 this->FirstFile = PythiaTree->FirstFile;
 this->EndFile = PythiaTree->EndFile;

 this->OneFilePerJob = PythiaTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = PythiaTree->TotalEntries[ifile];
 }

}

void loopPythia::ReadTree(int ifile)
{
 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){ 
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }
  
   PythiaTree->GetEntry(ifile, iEvent);

   int ieta1=0;
   int ieta2=0;

   Electron.SetPxPyPzE(PythiaTree->ElectronPx, PythiaTree->ElectronPy, PythiaTree->ElectronPz, PythiaTree->ElectronE);
   Positron.SetPxPyPzE(PythiaTree->PositronPx, PythiaTree->PositronPy, PythiaTree->PositronPz, PythiaTree->PositronE);

   ZBoson = Electron + Positron;

   if(isPDFReweight){
     if(!isPPbar) PDFReweightFactor = myPDFReweight->GetPDFReweightFactor(PythiaTree->quark_flavour[0], PythiaTree->quark_flavour[1], PythiaTree->QuarkE[0] / (ECM / 2.0), PythiaTree->QuarkE[1] / (ECM / 2.0), ZBoson.M());
     if(isPPbar) PDFReweightFactor = myPDFReweight->GetPDFReweightFactor(PythiaTree->quark_flavour[0], PythiaTree->quark_flavour[1] * (-1), PythiaTree->QuarkE[0] / (ECM / 2.0), PythiaTree->QuarkE[1] / (ECM / 2.0), ZBoson.M());
   }

   if(isTest){
     cout<<PythiaTree->ZPx<<" "<<PythiaTree->ZPy<<" "<<PythiaTree->ZPz<<" "<<PythiaTree->ZE<<endl;
     cout<<PythiaTree->PositronPx<<" "<<PythiaTree->PositronPy<<" "<<PythiaTree->PositronPz<<" "<<PythiaTree->PositronE<<endl;
     cout<<PythiaTree->ElectronPx<<" "<<PythiaTree->ElectronPy<<" "<<PythiaTree->ElectronPz<<" "<<PythiaTree->ElectronE<<endl;
     cout<<"PDF reweight factor = "<<PDFReweightFactor<<endl;
     cout<<endl;
   }

   if(PDFReweightFactor < 0){
     cout<<"Event "<<Sta_TotalNumber<<" x1: "<<PythiaTree->QuarkE[0] / (ECM / 2.0)<<" x2: "<<PythiaTree->QuarkE[1] / (ECM / 2.0)<<" ZRapidity: "<<ZBoson.Rapidity()<<endl;
     cout<<"Flavor: "<<PythiaTree->quark_flavour[0]<<" PDF reweight factor = "<<PDFReweightFactor;
     if(!isPPbar) cout<<" old: "<<myPDFReweight->GetOldPDF(PythiaTree->quark_flavour[0], PythiaTree->quark_flavour[1], PythiaTree->QuarkE[0] / (ECM / 2.0), PythiaTree->QuarkE[1] / (ECM / 2.0), ZBoson.M());
     if(!isPPbar) cout<<" new: "<<myPDFReweight->GetNewPDF(PythiaTree->quark_flavour[0], PythiaTree->quark_flavour[1], PythiaTree->QuarkE[0] / (ECM / 2.0), PythiaTree->QuarkE[1] / (ECM / 2.0), ZBoson.M())<<endl;;
     if(isPPbar) cout<<" old: "<<myPDFReweight->GetOldPDF(PythiaTree->quark_flavour[0], PythiaTree->quark_flavour[1] * (-1), PythiaTree->QuarkE[0] / (ECM / 2.0), PythiaTree->QuarkE[1] / (ECM / 2.0), ZBoson.M());
     if(isPPbar) cout<<" new: "<<myPDFReweight->GetNewPDF(PythiaTree->quark_flavour[0], PythiaTree->quark_flavour[1] * (-1), PythiaTree->QuarkE[0] / (ECM / 2.0), PythiaTree->QuarkE[1] / (ECM / 2.0), ZBoson.M())<<endl;;
   }

//   if(isTest) cout<<"ZPt = "<<ZBoson.Pt()<<" ZY = "<<ZBoson.Rapidity()<<" ZMass = "<<ZBoson.M()<<endl;

   double ZRapidity=ZBoson.Rapidity();

   double Weight = 1.0 * PDFReweightFactor;
   double WeightAfterDilution = 1.0 * PDFReweightFactor;

   if(!isPPbar) cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZRapidity / fabs(ZRapidity);
   if(isPPbar) cos_theta = calculate_theta(ZBoson, Electron, Positron);
//   cos_theta = calculate_theta(ZBoson, Electron, Positron) * (PythiaTree->QuarkE[0] - PythiaTree->QuarkE[1]) / fabs(PythiaTree->QuarkE[0] - PythiaTree->QuarkE[1]);
   double CosThetaQ = calculate_theta(ZBoson, Electron, Positron) * PythiaTree->quark_flavour[0] / fabs(PythiaTree->quark_flavour[0]);
   if(!isPPbar) phi = calculate_phi(Electron, Positron, ECM / 2.0) * ZRapidity / fabs(ZRapidity);
   if(isPPbar) phi = calculate_phi(Electron, Positron, ECM / 2.0);
   phi_eta = calculate_phi_eta(Electron, Positron);

   if(cos_theta > 1) cos_theta = 1.0;
   if(cos_theta < -1) cos_theta = -1.0;

   int isWrong = 0;
//   if((PythiaTree->QuarkE[0] - PythiaTree->QuarkE[1]) * PythiaTree->quark_flavour[0] > 0) isWrong = 0;
//   if((PythiaTree->QuarkE[0] - PythiaTree->QuarkE[1]) * PythiaTree->quark_flavour[0] < 0) isWrong = 1;
//   if((fabs(PythiaTree->QuarkPz[0]) - fabs(PythiaTree->QuarkPz[1])) * PythiaTree->quark_flavour[0] > 0) isWrong = 0;
//   if((fabs(PythiaTree->QuarkPz[0]) - fabs(PythiaTree->QuarkPz[1])) * PythiaTree->quark_flavour[0] < 0) isWrong = 1;
   if(ZRapidity * PythiaTree->quark_flavour[0] > 0) isWrong = 0;
   if(ZRapidity * PythiaTree->quark_flavour[0] < 0) isWrong = 1;

   bool isZU = false;
   bool isZD = false;
   if(fabs(PythiaTree->quark_flavour[0]) == 2 || fabs(PythiaTree->quark_flavour[0]) == 4 || fabs(PythiaTree->quark_flavour[0]) == 6) isZU = true;
   if(fabs(PythiaTree->quark_flavour[0]) == 1 || fabs(PythiaTree->quark_flavour[0]) == 3 || fabs(PythiaTree->quark_flavour[0]) == 5) isZD = true;

   bool isUUB = false;
   bool isDDB = false;
   bool isSSB = false;
   bool isCCB = false;
   bool isBBB = false;
   bool isGG = false;
   isUUB = (fabs(PythiaTree->quark_flavour[0]) == 2);//uu
   isDDB = (fabs(PythiaTree->quark_flavour[0]) == 1);//dd
   isSSB = (fabs(PythiaTree->quark_flavour[0]) == 3);//ss
   isCCB = (fabs(PythiaTree->quark_flavour[0]) == 4);//cc
   isBBB = (fabs(PythiaTree->quark_flavour[0]) == 5);//bb
   isGG = (fabs(PythiaTree->quark_flavour[0]) == 3 || fabs(PythiaTree->quark_flavour[0]) == 4 || fabs(PythiaTree->quark_flavour[0]) == 5 || fabs(PythiaTree->quark_flavour[0]) == 6);//gg

   bool isCC = false;
   bool isCF = false;
   if(fabs(Electron.Eta()) > 2.5 && fabs(Electron.Eta()) < 4.9) ieta1=1;//1F
   if(fabs(Electron.Eta()) < 2.5) ieta1=2;                              //1C
   if(fabs(Positron.Eta()) > 2.5 && fabs(Positron.Eta()) < 4.9) ieta2=3;//2F
   if(fabs(Positron.Eta()) < 2.5) ieta2=4;                              //2C

   isCC = (ieta1 * ieta2 == 8) && (Electron.Pt() > 25 && Positron.Pt() > 25);
   isCF = (ieta1 * ieta2 == 4 || ieta1 * ieta2 == 6) && (Electron.Pt() > 25 && Positron.Pt() > 25);

   bool isLepPtCut = false;
   isLepPtCut = (Electron.Pt() > 25 && Positron.Pt() > 25);
   bool isNoLepPtCut = false;
   isNoLepPtCut = !(Electron.Pt() > 25 && Positron.Pt() > 25);

   bool isF = false;
   bool isB = false;
   bool isQuarkF = false;
   bool isQuarkB = false;
   isF = (cos_theta > 0);
   isB = (cos_theta < 0);
   isQuarkF = (CosThetaQ > 0);
   isQuarkB = (CosThetaQ < 0);

   isCut = false;
   for(int icut = 0; icut < CutInfo.size(); icut++){
     CutForPythia(CutInfo.at(icut), CutLeft.at(icut), CutRight.at(icut), isCut);
   }
   if(isCut) continue;

   double QuarkPzZPzBalance = (PythiaTree->QuarkPz[0] + PythiaTree->QuarkPz[1]) / ZBoson.Pz();

/////////////////////////////////////////////////////////////

   ///////////////////////////
   //  Get Reweight Factor  //
   ///////////////////////////

   /*if(isRunReweightingFactor){
     if(cos_theta > 0){
       myhists->FZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
       myhists->FZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC);
       myhists->FZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF);
     }
     if(cos_theta < 0){
       myhists->BZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
       myhists->BZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC);
       myhists->BZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF);
     }

     if(CosThetaQ > 0){
       if(isZU) myhists->FZRapidity_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
       if(isZD) myhists->FZRapidity_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
       if(isZU) myhists->FZRapidity_CC_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC);
       if(isZD) myhists->FZRapidity_CC_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC);
       if(isZU) myhists->FZRapidity_CF_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF);
       if(isZD) myhists->FZRapidity_CF_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF);
     }
     if(CosThetaQ < 0){
       if(isZU) myhists->BZRapidity_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
       if(isZD) myhists->BZRapidity_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
       if(isZU) myhists->BZRapidity_CC_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC);
       if(isZD) myhists->BZRapidity_CC_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC);
       if(isZU) myhists->BZRapidity_CF_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF);
       if(isZD) myhists->BZRapidity_CF_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF);
     }

     continue;
   }*/
/////////////////////////////////////////////////////////////

   /*if(isHaveReweightingFactor){
     myhists->RetrieveWeight(fabs(ZBoson.Rapidity()), DilutionWeight_FZRapidity, DilutionWeight_BZRapidity, 
                                                      DilutionWeight_FZRapidity_CC, DilutionWeight_BZRapidity_CC, 
                                                      DilutionWeight_FZRapidity_CF, DilutionWeight_BZRapidity_CF);

     if(CosThetaQ > 0){
       myhists->FZmass_qq_ApplyDilution->at(iThread - 1)->Fill(ZBoson.M(), Weight * DilutionWeight_FZRapidity);
       myhists->FZmass_qq_ApplyDilution_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * DilutionWeight_FZRapidity_CC);
       myhists->FZmass_qq_ApplyDilution_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * DilutionWeight_FZRapidity_CF);
     }
     if(CosThetaQ < 0){
       myhists->BZmass_qq_ApplyDilution->at(iThread - 1)->Fill(ZBoson.M(), Weight * DilutionWeight_BZRapidity);
       myhists->BZmass_qq_ApplyDilution_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * DilutionWeight_BZRapidity_CC);
       myhists->BZmass_qq_ApplyDilution_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * DilutionWeight_BZRapidity_CF);
     }

     if(isTest) cout<<"Dilution Weight: "<<DilutionWeight_FZRapidity<<" "<<DilutionWeight_BZRapidity<<endl;
   }*/

   myhists->ZMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->ZMass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC);
   myhists->ZMass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF);

   myhists->FZmass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZmass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FZmass_Hadron_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isUUB);
   myhists->BZmass_Hadron_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isUUB);
   myhists->FZmass_Hadron_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isDDB);
   myhists->BZmass_Hadron_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isDDB);
   myhists->FZmass_Hadron_utype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isZU);
   myhists->BZmass_Hadron_utype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isZU);
   myhists->FZmass_Hadron_dtype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isZD);
   myhists->BZmass_Hadron_dtype->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isZD);
   myhists->FZmass_LepPtCut->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isLepPtCut);
   myhists->BZmass_LepPtCut->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isLepPtCut);
   myhists->FZmass_NoLepPtCut->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isNoLepPtCut);
   myhists->BZmass_NoLepPtCut->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isNoLepPtCut);
   myhists->FZmass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isCC);
   myhists->BZmass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isCC);
   myhists->FZmass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isCF);
   myhists->BZmass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isCF);

   myhists->ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->ZRapidity->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
   myhists->ZPt_LepPtCut->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLepPtCut);
   myhists->ZRapidity_LepPtCut->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isLepPtCut);
   myhists->ZPt_NoLepPtCut->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isNoLepPtCut);
   myhists->ZRapidity_NoLepPtCut->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isNoLepPtCut);
   myhists->ZRapidityAbs->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
   myhists->ZPzPtBalance->at(iThread - 1)->Fill(fabs(ZBoson.Pz()) / ZBoson.Pt(), Weight);
   myhists->ZPzPtBalance_CC->at(iThread - 1)->Fill(fabs(ZBoson.Pz()) / ZBoson.Pt(), Weight * isCC);
   myhists->ZPzPtBalance_CF->at(iThread - 1)->Fill(fabs(ZBoson.Pz()) / ZBoson.Pt(), Weight * isCF);
   myhists->QuarkPzZPzBalance->at(iThread - 1)->Fill(QuarkPzZPzBalance, Weight);
   myhists->QuarkPzZPzBalance_CC->at(iThread - 1)->Fill(QuarkPzZPzBalance, Weight * isCC);
   myhists->QuarkPzZPzBalance_CF->at(iThread - 1)->Fill(QuarkPzZPzBalance, Weight * isCF);
   myhists->Quark1Pz->at(iThread - 1)->Fill(PythiaTree->QuarkPz[0], Weight);
   myhists->Quark2Pz->at(iThread - 1)->Fill(PythiaTree->QuarkPz[1], Weight);

   myhists->ZMass_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight);
   myhists->ZMass_ZY_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC);
   myhists->ZMass_ZY_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF);

   myhists->FZMass_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF);
   myhists->BZMass_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB);
   myhists->FZMass_ZY_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF * isCC);
   myhists->BZMass_ZY_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB * isCC);
   myhists->FZMass_ZY_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF * isCF);
   myhists->BZMass_ZY_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB * isCF);

   myhists->ZMass_ZPt->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight);
   myhists->ZMass_ZPt_CC->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC);
   myhists->ZMass_ZPt_CF->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF);

   myhists->FZMass_ZPt->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isF);
   myhists->BZMass_ZPt->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isB);
   myhists->FZMass_ZPt_CC->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isF * isCC);
   myhists->BZMass_ZPt_CC->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isB * isCC);
   myhists->FZMass_ZPt_CF->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isF * isCF);
   myhists->BZMass_ZPt_CF->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isB * isCF);

//   myhists->FZMass_ZY_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF);
//   myhists->BZMass_ZY_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB);
//   myhists->FZMass_ZY_CC_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF * isCC);
//   myhists->BZMass_ZY_CC_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB * isCC);
//   myhists->FZMass_ZY_CF_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF * isCF);
//   myhists->BZMass_ZY_CF_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB * isCF);

   myhists->ZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);
   myhists->FZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isF);
   myhists->BZMass_ZY_QT->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isB);

   myhists->CosTheta->at(iThread - 1)->Fill(cos_theta, Weight);
   myhists->CosTheta_LepPtCut->at(iThread - 1)->Fill(cos_theta, Weight * isLepPtCut);
   myhists->CosThetaQ->at(iThread - 1)->Fill(CosThetaQ, Weight);
   myhists->CollinsPhi->at(iThread - 1)->Fill(phi, Weight);
   myhists->plot_phi_eta->at(iThread - 1)->Fill(phi_eta, Weight);
   //myhists->leptonPt->at(iThread - 1)->Fill(Electron.Pt(), Weight);
   myhists->leptonPt->at(iThread - 1)->Fill(Positron.Pt(), Weight * (Positron.Pt() < 40));
   myhists->leptonEta->at(iThread - 1)->Fill(Electron.Eta(), Weight);
   myhists->leptonEta->at(iThread - 1)->Fill(Positron.Eta(), Weight);

   myhists->LepEtaAbs->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight);
   myhists->AntiLepEtaAbs->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight);
   myhists->LepEtaAbs_CC->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isCC);
   myhists->AntiLepEtaAbs_CC->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isCC);
   myhists->LepEtaAbs_CF->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isCF);
   myhists->AntiLepEtaAbs_CF->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isCF);

   myhists->LepEta->at(iThread - 1)->Fill(Electron.Eta(), Weight);
   myhists->AntiLepEta->at(iThread - 1)->Fill(Positron.Eta(), Weight);
   myhists->LepEta_CC->at(iThread - 1)->Fill(Electron.Eta(), Weight * isCC);
   myhists->AntiLepEta_CC->at(iThread - 1)->Fill(Positron.Eta(), Weight * isCC);
   myhists->LepEta_CF->at(iThread - 1)->Fill(Electron.Eta(), Weight * isCF);
   myhists->AntiLepEta_CF->at(iThread - 1)->Fill(Positron.Eta(), Weight * isCF);

   myhists->FZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isF);
   myhists->BZRapidity->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isB);
   myhists->FZRapidity_LepPtCut->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isF * isLepPtCut);
   myhists->BZRapidity_LepPtCut->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isB * isLepPtCut);
   myhists->FZRapidity_NoLepPtCut->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isF * isNoLepPtCut);
   myhists->BZRapidity_NoLepPtCut->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isB * isNoLepPtCut);
   myhists->FZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isF * isCC);
   myhists->BZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isB * isCC);
   myhists->FZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isF * isCF);
   myhists->BZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isB * isCF);

   myhists->FZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isF);
   myhists->BZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isB);
   myhists->FZPt_LepPtCut->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isF * isLepPtCut);
   myhists->BZPt_LepPtCut->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isB * isLepPtCut);
   myhists->FZPt_NoLepPtCut->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isF * isNoLepPtCut);
   myhists->BZPt_NoLepPtCut->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isB * isNoLepPtCut);

   myhists->AverageZPt_ZY_numer->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * ZBoson.Pt() * (ZBoson.Pt() < 50));
   myhists->AverageZPt_ZY_denom->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * (ZBoson.Pt() < 50));
   myhists->AverageZPt_lnQ_numer->at(iThread - 1)->Fill(log(ZBoson.M())/log(exp(1)), Weight * ZBoson.Pt() * (ZBoson.Pt() < 50));
   myhists->AverageZPt_lnQ_denom->at(iThread - 1)->Fill(log(ZBoson.M())/log(exp(1)), Weight * (ZBoson.Pt() < 50));
   myhists->AverageZY_ZY_numer->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * fabs(ZBoson.Rapidity()));
   myhists->AverageZY_ZY_denom->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);

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

/*   myhists->ZMass_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isUUB);
   myhists->ZMass_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isDDB);
   myhists->ZMass_ZY_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isSSB);
   myhists->ZMass_ZY_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCCB);
   myhists->ZMass_ZY_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isBBB);
   myhists->ZMass_ZY_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isUUB);
   myhists->ZMass_ZY_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isDDB);
   myhists->ZMass_ZY_CC_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isSSB);
   myhists->ZMass_ZY_CC_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isCCB);
   myhists->ZMass_ZY_CC_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isBBB);
   myhists->ZMass_ZY_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isUUB);
   myhists->ZMass_ZY_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isDDB);
   myhists->ZMass_ZY_CF_ss->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isSSB);
   myhists->ZMass_ZY_CF_cc->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isCCB);
   myhists->ZMass_ZY_CF_bb->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isBBB);
   myhists->FZmass_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isUUB);
   myhists->BZmass_ZY_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isUUB);
   myhists->FZmass_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isDDB);
   myhists->BZmass_ZY_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isDDB);
   myhists->FZmass_ZY_gg->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isGG);
   myhists->BZmass_ZY_gg->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isGG);
   myhists->FZmass_ZY_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isUUB);
   myhists->BZmass_ZY_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isUUB);
   myhists->FZmass_ZY_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isDDB);
   myhists->BZmass_ZY_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isDDB);
   myhists->FZmass_ZY_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isGG);
   myhists->BZmass_ZY_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isGG);
   myhists->FZmass_ZY_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isUUB);
   myhists->BZmass_ZY_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isUUB);
   myhists->FZmass_ZY_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isDDB);
   myhists->BZmass_ZY_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isDDB);
   myhists->FZmass_ZY_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isGG);
   myhists->BZmass_ZY_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isGG);

   myhists->ZMass_ZPt_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isUUB);
   myhists->ZMass_ZPt_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isDDB);
   myhists->ZMass_ZPt_ss->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isSSB);
   myhists->ZMass_ZPt_cc->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCCB);
   myhists->ZMass_ZPt_bb->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isBBB);
   myhists->ZMass_ZPt_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isUUB);
   myhists->ZMass_ZPt_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isDDB);
   myhists->ZMass_ZPt_CC_ss->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isSSB);
   myhists->ZMass_ZPt_CC_cc->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isCCB);
   myhists->ZMass_ZPt_CC_bb->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isBBB);
   myhists->ZMass_ZPt_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isUUB);
   myhists->ZMass_ZPt_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isDDB);
   myhists->ZMass_ZPt_CF_ss->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isSSB);
   myhists->ZMass_ZPt_CF_cc->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isCCB);
   myhists->ZMass_ZPt_CF_bb->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isBBB);
*/
   myhists->FZmass_ZPt_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkF * isUUB);
   myhists->BZmass_ZPt_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkB * isUUB);
   myhists->FZmass_ZPt_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkF * isDDB);
   myhists->BZmass_ZPt_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkB * isDDB);

/*   myhists->FZmass_ZPt_gg->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkF * isGG);
   myhists->BZmass_ZPt_gg->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isQuarkB * isGG);
   myhists->FZmass_ZPt_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isQuarkF * isUUB);
   myhists->BZmass_ZPt_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isQuarkB * isUUB);
   myhists->FZmass_ZPt_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isQuarkF * isDDB);
   myhists->BZmass_ZPt_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isQuarkB * isDDB);
   myhists->FZmass_ZPt_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isQuarkF * isGG);
   myhists->BZmass_ZPt_CC_gg->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isQuarkB * isGG);
   myhists->FZmass_ZPt_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isQuarkF * isUUB);
   myhists->BZmass_ZPt_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isQuarkB * isUUB);
   myhists->FZmass_ZPt_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isQuarkF * isDDB);
   myhists->BZmass_ZPt_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isQuarkB * isDDB);
   myhists->FZmass_ZPt_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isQuarkF * isGG);
   myhists->BZmass_ZPt_CF_gg->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isQuarkB * isGG);
*/
/*   myhists->FZmass_ZY_uu_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isUUB);
   myhists->BZmass_ZY_uu_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isUUB);
   myhists->FZmass_ZY_dd_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isDDB);
   myhists->BZmass_ZY_dd_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isDDB);
   myhists->FZmass_ZY_gg_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isGG);
   myhists->BZmass_ZY_gg_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isGG);
   myhists->FZmass_ZY_CC_uu_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isUUB);
   myhists->BZmass_ZY_CC_uu_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isUUB);
   myhists->FZmass_ZY_CC_dd_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isDDB);
   myhists->BZmass_ZY_CC_dd_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isDDB);
   myhists->FZmass_ZY_CC_gg_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isGG);
   myhists->BZmass_ZY_CC_gg_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isGG);
   myhists->FZmass_ZY_CF_uu_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isUUB);
   myhists->BZmass_ZY_CF_uu_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isUUB);
   myhists->FZmass_ZY_CF_dd_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isDDB);
   myhists->BZmass_ZY_CF_dd_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isDDB);
   myhists->FZmass_ZY_CF_gg_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isGG);
   myhists->BZmass_ZY_CF_gg_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isGG);
*/
   myhists->FZRapidity_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isQuarkF * isUUB);
   myhists->BZRapidity_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isQuarkB * isUUB);
   myhists->FZRapidity_CC_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isUUB);
   myhists->BZRapidity_CC_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isUUB);
   myhists->FZRapidity_CF_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isUUB);
   myhists->BZRapidity_CF_uu->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isUUB);
   myhists->FZRapidity_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isQuarkF * isDDB);
   myhists->BZRapidity_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isQuarkB * isDDB);
   myhists->FZRapidity_CC_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isDDB);
   myhists->BZRapidity_CC_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isDDB);
   myhists->FZRapidity_CF_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isDDB);
   myhists->BZRapidity_CF_dd->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isDDB);
   myhists->FZRapidity_gg->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isQuarkF * isGG);
   myhists->BZRapidity_gg->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isQuarkB * isGG);
   myhists->FZRapidity_CC_gg->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkF * isGG);
   myhists->BZRapidity_CC_gg->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCC * isQuarkB * isGG);
   myhists->FZRapidity_CF_gg->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkF * isGG);
   myhists->BZRapidity_CF_gg->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isCF * isQuarkB * isGG);

   myhists->ZPt_uub->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isUUB);
   myhists->ZRapidity_uub->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isUUB);
   myhists->ZMass_uub->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
   myhists->ZPt_ddb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isDDB);
   myhists->ZRapidity_ddb->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isDDB);
   myhists->ZMass_ddb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
   myhists->ZPt_ssb->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isSSB);
   myhists->ZRapidity_ssb->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isSSB);
   myhists->ZMass_ssb->at(iThread - 1)->Fill(ZBoson.M(), Weight * isSSB);

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

   myhists->FZmass_CC_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isUUB);
   myhists->FZmass_CC_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isUUB * isWrong);
   myhists->BZmass_CC_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isUUB);
   myhists->BZmass_CC_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isUUB * isWrong);
   myhists->FZmass_CC_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isDDB);
   myhists->FZmass_CC_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkF * isDDB * isWrong);
   myhists->BZmass_CC_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isDDB);
   myhists->BZmass_CC_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCC * isQuarkB * isDDB * isWrong);
   myhists->FZmass_CF_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isUUB);
   myhists->FZmass_CF_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isUUB * isWrong);
   myhists->BZmass_CF_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isUUB);
   myhists->BZmass_CF_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isUUB * isWrong);
   myhists->FZmass_CF_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isDDB);
   myhists->FZmass_CF_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkF * isDDB * isWrong);
   myhists->BZmass_CF_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isDDB);
   myhists->BZmass_CF_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isCF * isQuarkB * isDDB * isWrong);
   myhists->FZmass_Full_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isUUB);
   myhists->FZmass_Full_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isUUB * isWrong);
   myhists->BZmass_Full_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isUUB);
   myhists->BZmass_Full_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isUUB * isWrong);
   myhists->FZmass_Full_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isDDB);
   myhists->FZmass_Full_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isDDB * isWrong);
   myhists->BZmass_Full_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isDDB);
   myhists->BZmass_Full_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isDDB * isWrong);

/*   myhists->ZMass_ZY_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight);
   myhists->ZMass_ZY_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isWrong);
   myhists->ZMass_ZY_CC_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC);
   myhists->ZMass_ZY_CC_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isWrong);
   myhists->ZMass_ZY_CF_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF);
   myhists->ZMass_ZY_CF_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isWrong);
   myhists->ZMass_ZY_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isUUB);
   myhists->ZMass_ZY_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isUUB * isWrong);
   myhists->ZMass_ZY_CC_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isUUB);
   myhists->ZMass_ZY_CC_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isUUB * isWrong);
   myhists->ZMass_ZY_CF_uu_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isUUB);
   myhists->ZMass_ZY_CF_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isUUB * isWrong);
   myhists->ZMass_ZY_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isDDB);
   myhists->ZMass_ZY_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isDDB * isWrong);
   myhists->ZMass_ZY_CC_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isDDB);
   myhists->ZMass_ZY_CC_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isDDB * isWrong);
   myhists->ZMass_ZY_CF_dd_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isDDB);
   myhists->ZMass_ZY_CF_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isDDB * isWrong);
   myhists->FZMass_ZY_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF);
   myhists->FZMass_ZY_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkF * isWrong);
   myhists->BZMass_ZY_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB);
   myhists->BZMass_ZY_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isQuarkB * isWrong);

   myhists->ZMass_ZPt_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight);
   myhists->ZMass_ZPt_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isWrong); 
   myhists->ZMass_ZPt_CC_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC);
   myhists->ZMass_ZPt_CC_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isWrong); 
   myhists->ZMass_ZPt_CF_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF);
   myhists->ZMass_ZPt_CF_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isWrong); 
   myhists->ZMass_ZPt_uu_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isUUB);
   myhists->ZMass_ZPt_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isUUB * isWrong); 
   myhists->ZMass_ZPt_CC_uu_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isUUB);
   myhists->ZMass_ZPt_CC_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isUUB * isWrong); 
   myhists->ZMass_ZPt_CF_uu_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isUUB);
   myhists->ZMass_ZPt_CF_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isUUB * isWrong); 
   myhists->ZMass_ZPt_dd_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isDDB);
   myhists->ZMass_ZPt_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isDDB * isWrong); 
   myhists->ZMass_ZPt_CC_dd_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isDDB);
   myhists->ZMass_ZPt_CC_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCC * isDDB * isWrong); 
   myhists->ZMass_ZPt_CF_dd_total->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isDDB);
   myhists->ZMass_ZPt_CF_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), ZBoson.Pt(), Weight * isCF * isDDB * isWrong); 

   myhists->ZMass_ZY_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight);
   myhists->ZMass_ZY_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isWrong);
   myhists->ZMass_ZY_CC_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC);
   myhists->ZMass_ZY_CC_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isWrong);
   myhists->ZMass_ZY_CF_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF);
   myhists->ZMass_ZY_CF_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isWrong);
   myhists->ZMass_ZY_uu_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isUUB);
   myhists->ZMass_ZY_uu_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isUUB * isWrong);
   myhists->ZMass_ZY_CC_uu_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isUUB);
   myhists->ZMass_ZY_CC_uu_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isUUB * isWrong);
   myhists->ZMass_ZY_CF_uu_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isUUB);
   myhists->ZMass_ZY_CF_uu_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isUUB * isWrong);
   myhists->ZMass_ZY_dd_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isDDB);
   myhists->ZMass_ZY_dd_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isDDB * isWrong);
   myhists->ZMass_ZY_CC_dd_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isDDB);
   myhists->ZMass_ZY_CC_dd_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCC * isDDB * isWrong);
   myhists->ZMass_ZY_CF_dd_total_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isDDB);
   myhists->ZMass_ZY_CF_dd_wrong_multi->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isCF * isDDB * isWrong);

   myhists->ZMass_ZY_QT_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight);
   myhists->ZMass_ZY_QT_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isWrong);
   myhists->ZMass_ZY_QT_CC_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCC);
   myhists->ZMass_ZY_QT_CC_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCC * isWrong);
   myhists->ZMass_ZY_QT_CF_total->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCF);
   myhists->ZMass_ZY_QT_CF_wrong->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), ZBoson.Pt(), Weight * isCF * isWrong);
*/
   myhists->ZPt_total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);
   myhists->ZPt_wrong->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isWrong);
   myhists->ZPt_LepPtCut_total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLepPtCut);
   myhists->ZPt_LepPtCut_wrong->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isLepPtCut * isWrong);
   myhists->ZPt_NoLepPtCut_total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isNoLepPtCut);
   myhists->ZPt_NoLepPtCut_wrong->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * isNoLepPtCut * isWrong);
   myhists->ZRapidity_total->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight);
   myhists->ZRapidity_wrong->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isWrong);
   myhists->ZRapidity_LepPtCut_total->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isLepPtCut);
   myhists->ZRapidity_LepPtCut_wrong->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isLepPtCut * isWrong);
   myhists->ZRapidity_NoLepPtCut_total->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isNoLepPtCut);
   myhists->ZRapidity_NoLepPtCut_wrong->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isNoLepPtCut * isWrong);
   myhists->ZRapidity_uu_total->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isUUB);
   myhists->ZRapidity_uu_wrong->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isUUB * isWrong);
   myhists->ZRapidity_dd_total->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isDDB);
   myhists->ZRapidity_dd_wrong->at(iThread - 1)->Fill(ZBoson.Rapidity(), Weight * isDDB * isWrong);
   myhists->ZRapidityAbs_total->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight);
   myhists->ZRapidityAbs_wrong->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isWrong);
   myhists->CosThetaQ_total->at(iThread - 1)->Fill(CosThetaQ, Weight);
   myhists->CosThetaQ_wrong->at(iThread - 1)->Fill(CosThetaQ, Weight * isWrong);

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

}

void loopPythia::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!PythiaTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete PythiaTree->fChain[RootNumber]->GetCurrentFile();
}

void loopPythia::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete PythiaTree;

}

loopPythia::~loopPythia()
{
}
