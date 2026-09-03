#define loopResBosHighMassZ_cxx
#include <iostream>
#include "Analysis/loopResBosHighMassZ.h"

using namespace std;

loopResBosHighMassZ::loopResBosHighMassZ(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;
}

void loopResBosHighMassZ::InputHist(HistsResBosHighMassZ* &myhists)
{
 this->myhists = myhists;

}

void loopResBosHighMassZ::InputTree(TreeForResBosHighMassZ *ResBosHighMassZTree)
{
 this->ResBosHighMassZTree = ResBosHighMassZTree;
 this->RootNames = ResBosHighMassZTree->RootNames;
 this->isDilution = ResBosHighMassZTree->isDilution;

 this->FirstFile = ResBosHighMassZTree->FirstFile;
 this->EndFile = ResBosHighMassZTree->EndFile;

 this->OneFilePerJob = ResBosHighMassZTree->OneFilePerJob;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ResBosHighMassZTree->TotalEntries[ifile];
 }

}

void loopResBosHighMassZ::ReadTree(int ifile)
{
 isZU = false;
 isZD = false;
 isWP = false;
 isWM = false;

 if(RootNames.at(ifile).Contains("zu")) isZU = true;
 if(RootNames.at(ifile).Contains("zd")) isZD = true;
 if(RootNames.at(ifile).Contains("wp")) isWP = true;
 if(RootNames.at(ifile).Contains("wm")) isWM = true;

 for(long iEvent = InitialEntry - 1; iEvent < Nentries; iEvent++){
   Sta_TotalNumber++;
   if(isTest) cout<<"Thread No."<<iThread<<": The No."<<Sta_TotalNumber<<" event."<<endl;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   ResBosHighMassZTree->GetEntry(ifile, iEvent);

   isZEvents = isZU || isZD;
   isWEvents = isWP || isWM;
     
   if(isZEvents) FillZEvents();
   if(isWEvents) FillWEvents();
 }

}

void loopResBosHighMassZ::FillZEvents()
{
   Electron.SetPxPyPzE(ResBosHighMassZTree->Px_d2, ResBosHighMassZTree->Py_d2, ResBosHighMassZTree->Pz_d2, ResBosHighMassZTree->E_d2);
   Positron.SetPxPyPzE(ResBosHighMassZTree->Px_d1, ResBosHighMassZTree->Py_d1, ResBosHighMassZTree->Pz_d1, ResBosHighMassZTree->E_d1);
   Weight = ResBosHighMassZTree->Weight;
   if(!isfinite(Weight)) return;

   ZBoson = Electron + Positron;

   bool isElecC = (fabs(Electron.Eta()) < 2.47);
   bool isPosiC = (fabs(Positron.Eta()) < 2.47);
   bool isElecF = (fabs(Electron.Eta()) > 2.47) && (fabs(Electron.Eta()) < 3.6);
   bool isPosiF = (fabs(Positron.Eta()) > 2.47) && (fabs(Positron.Eta()) < 3.6);

   bool isCC = isElecC && isPosiC;
   bool isCF = (isElecC && isPosiF) || (isElecF && isPosiC);

   bool LepPtCut = false;
   if(ZBoson.M() > 80.0) LepPtCut = (Electron.Pt() > 30.0) && (Positron.Pt() > 30.0);
   if(ZBoson.M() < 80.0) LepPtCut = (Electron.Pt() > 15.0) && (Positron.Pt() > 15.0);

   bool isLowMass = (ZBoson.M() > 40.0) && (ZBoson.M() < 1000.0);

   bool isATLASZPt = false;
   isATLASZPt = (fabs(ZBoson.Rapidity()) < 2.4)
             && (ZBoson.M() > 66.0 && ZBoson.M() < 116.0)
             && (Electron.Pt() > 20.0 && Positron.Pt() > 20.0)
             && (fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4);

   bool isATLASElecC = (Electron.Pt() > 25.0) && (fabs(Electron.Eta()) < 2.4);
   bool isATLASPosiC = (Positron.Pt() > 25.0) && (fabs(Positron.Eta()) < 2.4);
   bool isATLASElecF = (Electron.Pt() > 20.0) && (fabs(Electron.Eta()) > 2.4 && fabs(Electron.Eta()) < 4.9);
   bool isATLASPosiF = (Positron.Pt() > 20.0) && (fabs(Positron.Eta()) > 2.4 && fabs(Positron.Eta()) < 4.9);

   bool isATLASCC = false;
   isATLASCC = (isATLASElecC && isATLASPosiC);

   bool isATLASCF = false;
   isATLASCF = (isATLASElecC * isATLASPosiF)
            || (isATLASElecF * isATLASPosiC);

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

   double cos_theta = calculate_theta(ZBoson, Electron, Positron) * ZBoson.Rapidity() / fabs(ZBoson.Rapidity());
   bool isF = cos_theta > 0.0;
   bool isB = cos_theta < 0.0;

   myhists->ZMass_utype->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isZU);
   myhists->ZMass_dtype->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isZD);

   myhists->Xsec_3D_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCC);
   myhists->Xsec_3D_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCF);
   myhists->Xsec_3D_CC_LowMass->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCC);
   myhists->Xsec_3D_CF_LowMass->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCF);
   myhists->Xsec_3D_CC_HighMass->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCC);
   myhists->Xsec_3D_CF_HighMass->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCF);
   myhists->Xsec_3D_CC_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCC * isZU);
   myhists->Xsec_3D_CF_uu->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCF * isZU);
   myhists->Xsec_3D_CC_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCC * isZD);
   myhists->Xsec_3D_CF_dd->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * LepPtCut * isCF * isZD);
   myhists->Xsec_2D_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCC);
   myhists->Xsec_2D_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCF);
   myhists->Xsec_1D_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC);
   myhists->Xsec_1D_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF);

   myhists->ZMass_CosTheta_uu->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isZU);
   myhists->ZMass_CosTheta_dd->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isZD);
   myhists->ZMass_CosTheta->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight);

   myhists->ZRapidity_CC->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCC * isLowMass);
   myhists->ZRapidity_CF->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCF * isLowMass);
   myhists->ZRapidity_CF_Low->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCF * isLowMass);

   myhists->ZPt->at(iThread - 1)->Fill(ZBoson.Pt(), Weight);

   myhists->FZMass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC * isF);
   myhists->BZMass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC * isB);
   myhists->FZMass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isF);
   myhists->BZMass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isB);
   myhists->FZMass_ZY_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCC * isF);
   myhists->BZMass_ZY_CC->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCC * isB);
   myhists->FZMass_ZY_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCF * isF);
   myhists->BZMass_ZY_CF->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * LepPtCut * isCF * isB);

   myhists->FZMass_LowRegion_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC * isF);
   myhists->BZMass_LowRegion_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC * isB);
   myhists->FZMass_LowRegion_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isF);
   myhists->BZMass_LowRegion_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isB);
   myhists->FZMass_HighRegion_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC * isF);
   myhists->BZMass_HighRegion_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC * isB);
   myhists->FZMass_HighRegion_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isF);
   myhists->BZMass_HighRegion_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF * isB);

   myhists->ZHighMass_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC);
   myhists->ZHighMass_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF);
   myhists->ZHighMass_CC_PerTeV->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCC);
   myhists->ZHighMass_CF_PerTeV->at(iThread - 1)->Fill(ZBoson.M(), Weight * LepPtCut * isCF);

   myhists->FZMass_ATLAS_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isATLASCC * isF);
   myhists->BZMass_ATLAS_CC->at(iThread - 1)->Fill(ZBoson.M(), Weight * isATLASCC * isB);
   myhists->FZMass_ATLAS_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isATLASCF * isF);
   myhists->BZMass_ATLAS_CF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isATLASCF * isB);

   myhists->CrossSection->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->CrossSectionF->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->CrossSectionB->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);

   if(1){
     myhists->ATLASZPt_2D_Total->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight);
     myhists->ATLASZPt_2D_Total_uu->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * isZU);
     myhists->ATLASZPt_2D_Total_dd->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * isZD);
     myhists->ATLASZPt_2D_Total_MassWindow->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * (ZBoson.M() > 85 && ZBoson.M() < 95));
     myhists->ATLASZPt_Total->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (fabs(ZBoson.Rapidity()) < 2.4));

     if(ZBoson.M() > 66 && ZBoson.M() < 116 && fabs(Electron.Eta()) < 2.4 && fabs(Positron.Eta()) < 2.4 && Electron.Pt() > 20.0 && Positron.Pt() > 20.0){
       myhists->ATLASZPt_2D_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight);
       myhists->ATLASZPt_Fiduc->at(iThread - 1)->Fill(ZBoson.Pt(), Weight * (fabs(ZBoson.Rapidity()) < 2.4));
     }
   }

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

   myhists->ATLAS_Mll_HighMass_FineBin->at(iThread - 1)->Fill(ZBoson.M(), Weight * isATLASHMDY);
   myhists->ATLAS_costheta_FineBin->at(iThread - 1)->Fill(cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_DilRapidity_FineBin->at(iThread - 1)->Fill(fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_costheta_FineBin->at(iThread - 1)->Fill(ZBoson.M(), cos_theta, Weight * isATLASHMDY);
   myhists->ATLAS_Mll_HighMass_DilRapidity_FineBin->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isATLASHMDY);
   myhists->ATLAS_HMDY_Xsec_3D_FineBin->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), cos_theta, Weight * isATLASHMDY);

   myhists->FZMass_Full->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_Full->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FZMass_Full_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isZU);
   myhists->BZMass_Full_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isZU);
   myhists->FZMass_Full_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF * isZD);
   myhists->BZMass_Full_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB * isZD);

   int isWrong = 0;
   if(isDilution){
     bool isUUB = false;
     bool isDDB = false;
     bool isSSB = false;
     bool isCCB = false;
     bool isBBB = false;
     bool isGG = false;
     isUUB = (fabs(fabs(ResBosHighMassZTree->Type) - 1.0) < 1e-10);
     isDDB = (fabs(fabs(ResBosHighMassZTree->Type) - 2.0) < 1e-10);
     isSSB = (fabs(fabs(ResBosHighMassZTree->Type) - 3.0) < 1e-10);
     isCCB = (fabs(fabs(ResBosHighMassZTree->Type) - 4.0) < 1e-10);
     isBBB = (fabs(fabs(ResBosHighMassZTree->Type) - 5.0) < 1e-10);
     isGG = isSSB || isCCB || isBBB;

     int flavor1, flavor2;
     if(isUUB && ResBosHighMassZTree->Type > 0){flavor1 = 2; flavor2 = -2;}
     if(isUUB && ResBosHighMassZTree->Type < 0){flavor1 = -2; flavor2 = 2;}
     if(isDDB && ResBosHighMassZTree->Type > 0){flavor1 = 1; flavor2 = -1;}
     if(isDDB && ResBosHighMassZTree->Type < 0){flavor1 = -1; flavor2 = 1;}
     if(isSSB && ResBosHighMassZTree->Type > 0){flavor1 = 3; flavor2 = -3;}
     if(isSSB && ResBosHighMassZTree->Type < 0){flavor1 = -3; flavor2 = 3;}
     if(isCCB && ResBosHighMassZTree->Type > 0){flavor1 = 4; flavor2 = -4;}
     if(isCCB && ResBosHighMassZTree->Type < 0){flavor1 = -4; flavor2 = 4;}
     if(isBBB && ResBosHighMassZTree->Type > 0){flavor1 = 5; flavor2 = -5;}
     if(isBBB && ResBosHighMassZTree->Type < 0){flavor1 = -5; flavor2 = 5;}
     double x1 = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(ZBoson.Rapidity());
     double x2 = (sqrt(ZBoson.M() * ZBoson.M() + ZBoson.Pt() * ZBoson.Pt()) / ECM) * exp(ZBoson.Rapidity() * (-1.0));
     PDFReweightFactor = GetPDFReweightingFactor(x1, x2, flavor1, flavor2, ZBoson.M());
     Weight = Weight * PDFReweightFactor;

     double CosThetaQ;
     if(ResBosHighMassZTree->Type > 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron);
     if(ResBosHighMassZTree->Type < 0) CosThetaQ = calculate_theta(ZBoson, Electron, Positron) * (-1.0);
     double PhiQ;
     if(ResBosHighMassZTree->Type > 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0);
     if(ResBosHighMassZTree->Type < 0) PhiQ = calculate_phi(Electron, Positron, (double)ECM / 2.0) * (-1.0);

     if(ResBosHighMassZTree->Type > 0){//uubar
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 0;//u > ubar
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 1;//u < ubar
     }
     if(ResBosHighMassZTree->Type < 0){//ubaru
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) > 0) isWrong = 1;//ubar > u
       if(ZBoson.Rapidity() / fabs(ZBoson.Rapidity()) < 0) isWrong = 0;//ubar < u
     }

     bool isQuarkF = false;
     bool isQuarkB = false;
     isQuarkF = (CosThetaQ > 0);
     isQuarkB = (CosThetaQ < 0);

     myhists->FZMass_HighMass_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isUUB);
     myhists->BZMass_HighMass_uu->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isUUB);
     myhists->FZMass_HighMass_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkF * isDDB);
     myhists->BZMass_HighMass_dd->at(iThread - 1)->Fill(ZBoson.M(), Weight * isQuarkB * isDDB);

     myhists->ZHighMass_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong);
     myhists->ZHighMass_total->at(iThread - 1)->Fill(ZBoson.M(), Weight);
     myhists->ZHighMass2_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong);
     myhists->ZHighMass2_total->at(iThread - 1)->Fill(ZBoson.M(), Weight);
     myhists->ZHighMass_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong * isUUB);
     myhists->ZHighMass_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
     myhists->ZHighMass_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong * isDDB);
     myhists->ZHighMass_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
     myhists->ZHighMass2_uu_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong * isUUB);
     myhists->ZHighMass2_uu_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isUUB);
     myhists->ZHighMass2_dd_wrong->at(iThread - 1)->Fill(ZBoson.M(), Weight * isWrong * isDDB);
     myhists->ZHighMass2_dd_total->at(iThread - 1)->Fill(ZBoson.M(), Weight * isDDB);
   }

   myhists->ZMass_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);
   myhists->ZMass_HighMass_PerTeV->at(iThread - 1)->Fill(ZBoson.M(), Weight);

   myhists->ZMass_FullMass->at(iThread - 1)->Fill(ZBoson.M(), Weight);

   myhists->FZMass_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_HighMass->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FZMass_HighMass2->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_HighMass2->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FZMass_HighMass_upto10000->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_HighMass_upto10000->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);

   myhists->FZMass_LowMass1->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_LowMass1->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);
   myhists->FZMass_LowMass2->at(iThread - 1)->Fill(ZBoson.M(), Weight * isF);
   myhists->BZMass_LowMass2->at(iThread - 1)->Fill(ZBoson.M(), Weight * isB);

   myhists->FZMass_LowMass1_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF);
   myhists->BZMass_LowMass1_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB);
   myhists->FZMass_LowMass2_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isF);
   myhists->BZMass_LowMass2_ZY->at(iThread - 1)->Fill(ZBoson.M(), fabs(ZBoson.Rapidity()), Weight * isB);

   myhists->CrossSectionPtY->at(iThread - 1)->Fill(ZBoson.Pt(), fabs(ZBoson.Rapidity()), Weight * (ZBoson.M() > 500.0 && ZBoson.M() < 5000.0));

   myhists->ForwardPosiLeptonEta->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isF);
   myhists->BackwardPosiLeptonEta->at(iThread - 1)->Fill(fabs(Positron.Eta()), Weight * isB);
   myhists->ForwardNegaLeptonEta->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isF);
   myhists->BackwardNegaLeptonEta->at(iThread - 1)->Fill(fabs(Electron.Eta()), Weight * isB);

   double ZMT = CalculateTransverseMass(Electron, Positron);
   myhists->ZMass_ZMT->at(iThread - 1)->Fill(ZBoson.M(), ZMT, Weight);
}

void loopResBosHighMassZ::FillWEvents()
{
   Neutrino.SetPxPyPzE(ResBosHighMassZTree->Px_d2, ResBosHighMassZTree->Py_d2, ResBosHighMassZTree->Pz_d2, ResBosHighMassZTree->E_d2);
   Lepton.SetPxPyPzE(ResBosHighMassZTree->Px_d1, ResBosHighMassZTree->Py_d1, ResBosHighMassZTree->Pz_d1, ResBosHighMassZTree->E_d1);
   Weight = ResBosHighMassZTree->Weight;
   if(!isfinite(Weight)) return;

   WBoson = Neutrino + Lepton;

   WMT = CalculateTransverseMass(Lepton, Neutrino);

   double Largex = sqrt(WBoson.M() * WBoson.M() + WBoson.Pt() * WBoson.Pt()) / ECM * exp(fabs(WBoson.Rapidity()));

   double cos_theta = 0.0;
   if(isWP) cos_theta = calculate_theta(WBoson, Neutrino, Lepton) * WBoson.Rapidity() / fabs(WBoson.Rapidity());
   if(isWM) cos_theta = calculate_theta(WBoson, Lepton, Neutrino) * WBoson.Rapidity() / fabs(WBoson.Rapidity());
   double phi = 0.0;
   if(isWP) phi = calculate_phi(Neutrino, Lepton, (double)ECM / 2.0);
   if(isWM) phi = calculate_phi(Lepton, Neutrino, (double)ECM / 2.0);

   TLorentzVector Neutrino_ExpPz, Neutrino_ExpEta, WBoson_ExpPz, WBoson_ExpEta;
   Neutrino_ExpPz.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), 0.0, Neutrino.Et());
   Neutrino_ExpEta.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), 0.0, Neutrino.Et());
   int WCharge = 0;
   if(isWP) WCharge = 1;
   if(isWM) WCharge = -1;
   double NuExpPz = CalculateNeutrinoPz(Lepton, Neutrino_ExpPz, 80.385);
   double NuExpPz_Eta = CalculateNeutrinoPz_Eta(Lepton, Neutrino_ExpEta, 80.385, WCharge);
   Neutrino_ExpPz.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), NuExpPz, sqrt(Neutrino.Et() * Neutrino.Et() + NuExpPz * NuExpPz));
   Neutrino_ExpEta.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), NuExpPz_Eta, sqrt(Neutrino.Et() * Neutrino.Et() + NuExpPz_Eta * NuExpPz_Eta));
   WBoson_ExpPz = Lepton + Neutrino_ExpPz;
   WBoson_ExpEta = Lepton + Neutrino_ExpEta;

   double cos_theta_ExpPz = 0.0;
   if(isWP) cos_theta_ExpPz = calculate_theta(WBoson_ExpPz, Neutrino_ExpPz, Lepton) * WBoson_ExpPz.Rapidity() / fabs(WBoson_ExpPz.Rapidity());
   if(isWM) cos_theta_ExpPz = calculate_theta(WBoson_ExpPz, Lepton, Neutrino_ExpPz) * WBoson_ExpPz.Rapidity() / fabs(WBoson_ExpPz.Rapidity());

   double cos_theta_ExpEta = 0.0;
   if(isWP) cos_theta_ExpEta = calculate_theta(WBoson_ExpEta, Neutrino_ExpEta, Lepton) * WBoson_ExpEta.Rapidity() / fabs(WBoson_ExpEta.Rapidity());
   if(isWM) cos_theta_ExpEta = calculate_theta(WBoson_ExpEta, Lepton, Neutrino_ExpEta) * WBoson_ExpEta.Rapidity() / fabs(WBoson_ExpEta.Rapidity());

   double isCorrectEta_ExpPz, isCorrectEta_ExpEta;
   if(Neutrino.Eta() * Neutrino_ExpPz.Eta() > 0) isCorrectEta_ExpPz = 0.5;
   else isCorrectEta_ExpPz = 1.5;

   if(Neutrino.Eta() * Neutrino_ExpEta.Eta() > 0) isCorrectEta_ExpEta = 0.5;
   else isCorrectEta_ExpEta = 1.5;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   TLorentzVector Neutrino_ExpEta2, WBoson_ExpEta2;
   Neutrino_ExpEta2.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), 0.0, Neutrino.Et());
   pair<double, int> NuExpPz_Eta2 = CalculateNeutrinoPz_Eta2(Lepton, Neutrino_ExpEta, 80.385, WCharge);
   Neutrino_ExpEta2.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), NuExpPz_Eta2.first, sqrt(Neutrino.Et() * Neutrino.Et() + NuExpPz_Eta2.first * NuExpPz_Eta2.first));
   WBoson_ExpEta2 = Lepton + Neutrino_ExpEta2;

   double cos_theta_ExpEta2 = 0.0;
   if(isWP) cos_theta_ExpEta2 = calculate_theta(WBoson_ExpEta2, Neutrino_ExpEta2, Lepton) * WBoson_ExpEta2.Rapidity() / fabs(WBoson_ExpEta2.Rapidity());
   if(isWM) cos_theta_ExpEta2 = calculate_theta(WBoson_ExpEta2, Lepton, Neutrino_ExpEta2) * WBoson_ExpEta2.Rapidity() / fabs(WBoson_ExpEta2.Rapidity());

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   bool SelectionCut = (Lepton.Pt() > 30.0)
                    && (Neutrino.Pt() > 30.0)
                    //&& (fabs(Lepton.Eta()) < 2.47)
                    //&& (WBoson.Pt() < 40.0)
                    && (WMT > 50);

   bool SelectionCut_NoPtCut = (Lepton.Pt() > 30.0)
                    && (Neutrino.Pt() > 30.0)
                    //&& (fabs(Lepton.Eta()) < 2.47)
                    && (WMT > 50);

   bool SelectionCutFullEta = (Lepton.Pt() > 30.0)
                    && (Neutrino.Pt() > 30.0)
                    //&& (WBoson.Pt() < 15)
                    && (WMT > 50);

   bool isLowMT = (WMT < 500.0);

   bool isRHIC = (Lepton.Pt() > 25.0) && (Lepton.Pt() < 50.0);

   myhists->PositiveLeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->NegativeLeptonEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);
   myhists->PositiveLeptonEta_NoPtCut->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut_NoPtCut * isLowMT * isWP);
   myhists->NegativeLeptonEta_NoPtCut->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut_NoPtCut * isLowMT * isWM);
   myhists->PositiveLeptonHighEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->NegativeLeptonHighEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);
   myhists->PositiveLeptonLowEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->NegativeLeptonLowEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->PositiveLeptonEtaFull->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCutFullEta * isLowMT * isWP);
   myhists->NegativeLeptonEtaFull->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCutFullEta * isLowMT * isWM);
   myhists->PositiveNeutrinoEtaFull->at(iThread - 1)->Fill(fabs(Neutrino.Eta()), Weight * SelectionCutFullEta * isLowMT * isWP);
   myhists->NegativeNeutrinoEtaFull->at(iThread - 1)->Fill(fabs(Neutrino.Eta()), Weight * SelectionCutFullEta * isLowMT * isWM);

   myhists->PositiveLeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight * SelectionCut * isLowMT * isWP);
   myhists->NegativeLeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight * SelectionCut * isLowMT * isWM);
   myhists->WLeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight * SelectionCut * isLowMT);

   myhists->PositiveLeptonPtEta->at(iThread - 1)->Fill(Lepton.Pt(), fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->NegativeLeptonPtEta->at(iThread - 1)->Fill(Lepton.Pt(), fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);
   myhists->WPlusMTEta->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTEta->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);
   myhists->WPlusMTEta_NoPtCut->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut_NoPtCut * isLowMT * isWP);
   myhists->WMinusMTEta_NoPtCut->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut_NoPtCut * isLowMT * isWM);
   myhists->WPlusMTEta_Above100->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTEta_Above100->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->WPlusMTEta_FullEta->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTEta_FullEta->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);
   myhists->WPlusMTEta_FullEta_Above100->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTEta_FullEta_Above100->at(iThread - 1)->Fill(WMT, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->WMTx->at(iThread - 1)->Fill(WMT, Largex, Weight * SelectionCut * isLowMT);
   myhists->WPlusMTCosThetaEta->at(iThread - 1)->Fill(WMT, cos_theta, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMTCosThetaEta->at(iThread - 1)->Fill(WMT, cos_theta, fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->WPlusNeutrinoPt->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusNeutrinoPt->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * SelectionCut * isLowMT * isWM);
   myhists->NeutrinoPt->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * SelectionCut * isLowMT);

   myhists->WPlusMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWM);
   myhists->WPlusMT_NoPtCut->at(iThread - 1)->Fill(WMT, Weight * SelectionCut_NoPtCut * isLowMT * isWP);
   myhists->WMinusMT_NoPtCut->at(iThread - 1)->Fill(WMT, Weight * SelectionCut_NoPtCut * isLowMT * isWM);
   myhists->WPlusMT_Above100->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusMT_Above100->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT * isWM);
   myhists->WBosonMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isLowMT);

   myhists->WPlusXsec->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWP);
   myhists->WMinusXsec->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * SelectionCut * isLowMT * isWM);

   myhists->WHighMassMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut);
   myhists->WPlusHighMassMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWP);
   myhists->WMinusHighMassMT->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWM);
   myhists->WHighMassMT_NoPtCut->at(iThread - 1)->Fill(WMT, Weight * SelectionCut_NoPtCut);
   myhists->WPlusHighMassMT_NoPtCut->at(iThread - 1)->Fill(WMT, Weight * SelectionCut_NoPtCut * isWP);
   myhists->WMinusHighMassMT_NoPtCut->at(iThread - 1)->Fill(WMT, Weight * SelectionCut_NoPtCut * isWM);
   myhists->WHighMassMT_PerTeV->at(iThread - 1)->Fill(WMT, Weight * SelectionCut);
   myhists->WPlusHighMassMT_PerTeV->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWP);
   myhists->WMinusHighMassMT_PerTeV->at(iThread - 1)->Fill(WMT, Weight * SelectionCut * isWM);

   myhists->WPlusForwardEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWP * (cos_theta > 0.0));
   myhists->WPlusBackwardEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWP * (cos_theta < 0.0));
   myhists->WMinusForwardEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWM * (cos_theta > 0.0));
   myhists->WMinusBackwardEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWM * (cos_theta < 0.0));

   myhists->WPlusAverageRapidity->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * fabs(WBoson.Rapidity()) * isWP);
   myhists->WMinusAverageRapidity->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * fabs(WBoson.Rapidity()) * isWM);

   myhists->WPlusCosTheta->at(iThread - 1)->Fill(cos_theta, Weight * isWP);
   myhists->WMinusCosTheta->at(iThread - 1)->Fill(cos_theta, Weight * isWM);

   myhists->WPlusCosTheta_ExpPz->at(iThread - 1)->Fill(cos_theta_ExpPz, Weight * isWP);
   myhists->WMinusCosTheta_ExpPz->at(iThread - 1)->Fill(cos_theta_ExpPz, Weight * isWM);

   myhists->WPlusCosTheta_ExpEta->at(iThread - 1)->Fill(cos_theta_ExpEta2, Weight * isWP);
   myhists->WMinusCosTheta_ExpEta->at(iThread - 1)->Fill(cos_theta_ExpEta2, Weight * isWM);

   myhists->WPlusForwardEta_ExpPz->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWP * (cos_theta_ExpPz > 0.0));
   myhists->WPlusBackwardEta_ExpPz->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWP * (cos_theta_ExpPz < 0.0));
   myhists->WMinusForwardEta_ExpPz->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWM * (cos_theta_ExpPz > 0.0));
   myhists->WMinusBackwardEta_ExpPz->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWM * (cos_theta_ExpPz < 0.0));

   myhists->WPlusForwardEta_ExpEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWP * (cos_theta_ExpEta > 0.0));
   myhists->WPlusBackwardEta_ExpEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWP * (cos_theta_ExpEta < 0.0));
   myhists->WMinusForwardEta_ExpEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWM * (cos_theta_ExpEta > 0.0));
   myhists->WMinusBackwardEta_ExpEta->at(iThread - 1)->Fill(fabs(Lepton.Eta()), Weight * isWM * (cos_theta_ExpEta < 0.0));

   myhists->WPlusForwardDeta->at(iThread - 1)->Fill(fabs(Lepton.Eta()) - fabs(Neutrino.Eta()), Weight * isWP * (cos_theta > 0.0));
   myhists->WPlusBackwardDeta->at(iThread - 1)->Fill(fabs(Lepton.Eta()) - fabs(Neutrino.Eta()), Weight * isWP * (cos_theta < 0.0));
   myhists->WMinusForwardDeta->at(iThread - 1)->Fill(fabs(Lepton.Eta()) - fabs(Neutrino.Eta()), Weight * isWM * (cos_theta > 0.0));
   myhists->WMinusBackwardDeta->at(iThread - 1)->Fill(fabs(Lepton.Eta()) - fabs(Neutrino.Eta()), Weight * isWM * (cos_theta < 0.0));

   myhists->WPlusLepNuEta->at(iThread - 1)->Fill(Lepton.Eta() - Neutrino.Eta(), Lepton.Eta() + Neutrino.Eta(), Weight * isWP);
   myhists->WMinusLepNuEta->at(iThread - 1)->Fill(Lepton.Eta() - Neutrino.Eta(), Lepton.Eta() + Neutrino.Eta(), Weight * isWM);

   myhists->WPlusPzMethodFraction->at(iThread - 1)->Fill(isCorrectEta_ExpPz, Weight * isWP);
   myhists->WMinusPzMethodFraction->at(iThread - 1)->Fill(isCorrectEta_ExpPz, Weight * isWM);
   myhists->WPlusEtaMethodFraction->at(iThread - 1)->Fill(isCorrectEta_ExpEta, Weight * isWP);
   myhists->WMinusEtaMethodFraction->at(iThread - 1)->Fill(isCorrectEta_ExpEta, Weight * isWM);

   myhists->WPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * (fabs(Lepton.Eta()) < 2.4));

   myhists->RHIC_WPlus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isRHIC * isWP);
   myhists->RHIC_WMinus->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isRHIC * isWM);

   int Selection = (WBoson.M() > 30.0) && (WBoson.M() < 95.0)
                && (fabs(WBoson.Rapidity()) > 1.0) && (fabs(WBoson.Rapidity()) < 1.5);
   myhists->TotalXsec_WPlus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWP * Selection);
   myhists->TotalXsec_WMinus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWM * Selection);

   myhists->A0_ZPt_WPlus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A0_ZPt_WPlus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWP * Selection);
   myhists->A1_ZPt_WPlus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A1_ZPt_WPlus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWP * Selection);
   myhists->A2_ZPt_WPlus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A2_ZPt_WPlus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWP * Selection);
   myhists->A3_ZPt_WPlus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A3_ZPt_WPlus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWP * Selection);
   myhists->A4_ZPt_WPlus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A4_ZPt_WPlus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWP * Selection);
   myhists->A0_ZPt_WMinus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A0_ZPt_WMinus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWM * Selection);
   myhists->A1_ZPt_WMinus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A1_ZPt_WMinus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWM * Selection);
   myhists->A2_ZPt_WMinus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A2_ZPt_WMinus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWM * Selection);
   myhists->A3_ZPt_WMinus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A3_ZPt_WMinus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWM * Selection);
   myhists->A4_ZPt_WMinus->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A4_ZPt_WMinus->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isWM * Selection);
}

double loopResBosHighMassZ::GetPDFReweightingFactor(double x1, double x2, int flavor1, int flavor2, double Q)
{
 double Value = 1.0;
 if(!isPDFReweight){
   //cout<<"ERROR! Please initialize PDF at first."<<endl;
   return 1.0;
 }

 Value = myPDFReweight->GetPDFReweightFactor(flavor1, flavor2, x1, x2, Q);

// if(Value > 5000.0 || Value < 0.0){
//   ProblemEventNumber++;
//   Value = 1.0;
// }

 return Value;
}

void loopResBosHighMassZ::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!ResBosHighMassZTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ResBosHighMassZTree->fChain[RootNumber]->GetCurrentFile();
}

void loopResBosHighMassZ::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete ResBosHighMassZTree;

}

loopResBosHighMassZ::~loopResBosHighMassZ()
{
}
