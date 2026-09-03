#ifndef ZPrime_ZPrimeHistGroup_cxx
#define ZPrime_ZPrimeHistGroup_cxx
#include "ZPrime/HistsZPrime.h"

using namespace std;

ZPrimeHistGroup::ZPrimeHistGroup()
{
}

void ZPrimeHistGroup::Initial(int iThread, TString MCType)
{
 this->MCType[iThread - 1] = MCType;

 if(this->MCType[iThread - 1] == "Data") isData[iThread - 1] = true;
 else isData[iThread - 1] = false;

 if(this->MCType[iThread - 1] == "TopQuark") isTop[iThread - 1] = true;
 else isTop[iThread - 1] = false;

}

void ZPrimeHistGroup::Fill(int iThread, double par, double weight, EventZPrime ProcessEvent)
{
 SR_ee_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl);
 SR_mm_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu);
 SR_em_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu);

 SSM_ee_0p5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_0p5TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_0p6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_0p6TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_0p8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_0p8TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_1TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_1TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_2TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_2TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_3TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_3TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_4TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_4TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_5TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_6TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_7TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_7TeV * ProcessEvent.kfactor_nnlo);
 SSM_ee_8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_SSM_8TeV * ProcessEvent.kfactor_nnlo);

 E6Chi_ee_0p5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_0p5TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_0p6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_0p6TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_0p8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_0p8TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_1TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_1TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_2TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_2TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_3TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_3TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_4TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_4TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_5TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_6TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_7TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_7TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_ee_8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Chi_8TeV * ProcessEvent.kfactor_nnlo);

 E6Psi_ee_0p5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_0p5TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_0p6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_0p6TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_0p8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_0p8TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_1TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_1TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_2TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_2TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_3TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_3TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_4TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_4TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_5TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_6TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_7TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_7TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_ee_8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl * ProcessEvent.ReweightFactor_E6Psi_8TeV * ProcessEvent.kfactor_nnlo);

 SSM_mm_0p5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_0p5TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_0p6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_0p6TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_0p8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_0p8TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_1TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_1TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_2TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_2TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_3TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_3TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_4TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_4TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_5TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_6TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_7TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_7TeV * ProcessEvent.kfactor_nnlo);
 SSM_mm_8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_SSM_8TeV * ProcessEvent.kfactor_nnlo);

 E6Chi_mm_0p5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_0p5TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_0p6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_0p6TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_0p8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_0p8TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_1TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_1TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_2TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_2TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_3TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_3TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_4TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_4TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_5TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_6TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_7TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_7TeV * ProcessEvent.kfactor_nnlo);
 E6Chi_mm_8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Chi_8TeV * ProcessEvent.kfactor_nnlo);

 E6Psi_mm_0p5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_0p5TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_0p6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_0p6TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_0p8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_0p8TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_1TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_1TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_2TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_2TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_3TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_3TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_4TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_4TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_5TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_5TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_6TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_6TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_7TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_7TeV * ProcessEvent.kfactor_nnlo);
 E6Psi_mm_8TeV->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu * ProcessEvent.ReweightFactor_E6Psi_8TeV * ProcessEvent.kfactor_nnlo);

 if(isData[iThread - 1]){
   topDD_ee->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl);
   topDD_mm->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu);

   topDD_HighMass_CosTheta_ee->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_CosTheta);
   topDD_HighMass_CosTheta_mm->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_CosTheta);

   topDD_HighMass_Rapidity_ee->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_Rapidity);
   topDD_HighMass_Rapidity_mm->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_Rapidity);
 }

 if(MCType[iThread - 1] == "DrellYan" || MCType[iThread - 1] == "Diboson" || MCType[iThread - 1] == "Ztautau" || MCType[iThread - 1] == "Wjets"){
   topDD_ee->HistPtr(iThread - 1)->Fill(par, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl);
   topDD_mm->HistPtr(iThread - 1)->Fill(par, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu);

   topDD_HighMass_CosTheta_ee->HistPtr(iThread - 1)->Fill(par, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_CosTheta);
   topDD_HighMass_CosTheta_mm->HistPtr(iThread - 1)->Fill(par, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_CosTheta);

   topDD_HighMass_Rapidity_ee->HistPtr(iThread - 1)->Fill(par, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_Rapidity);
   topDD_HighMass_Rapidity_mm->HistPtr(iThread - 1)->Fill(par, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_Rapidity);
 }

 if(MCType[iThread - 1] == "Wjets_DD"){
   Fake_MM_FourTerm_TT->at(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionEl * ProcessEvent.RecoWeight_FourTerm_TT);
   Fake_MM_FourTerm_TL->at(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionEl * ProcessEvent.RecoWeight_FourTerm_TL);
   Fake_MM_FourTerm_LT->at(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionEl * ProcessEvent.RecoWeight_FourTerm_LT);
   Fake_MM_FourTerm_LL->at(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionEl * ProcessEvent.RecoWeight_FourTerm_LL);
 }


 ElFakeCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeightLoose
                                                      * ProcessEvent.Lepton1_PrescaleFactor
                                                      * ProcessEvent.SingleElectron
                                                      * ProcessEvent.passElFake);

 MuFakeCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeightLoose
                                                      * ProcessEvent.Lepton1_TightWeight
                                                      * ProcessEvent.Lepton2_TightWeight
                                                      * ProcessEvent.eeChannel_withmuon
                                                      * ProcessEvent.passMuFake);

 if(isFillFakeUnc && MCType[iThread - 1] == "Wjets_DD") FillFakeUnc(iThread, par, weight, ProcessEvent);
}

void ZPrimeHistGroup::FillFakeUnc(int iThread, double par, double weight, EventZPrime ProcessEvent)
{
 Fake_El_Stat_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_Stat_up * ProcessEvent.passSelectionEl);
 Fake_El_Stat_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_Stat_down * ProcessEvent.passSelectionEl);
 Fake_El_PromptSubtr_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_PromptSubtr_up * ProcessEvent.passSelectionEl);
 Fake_El_PromptSubtr_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_PromptSubtr_down * ProcessEvent.passSelectionEl);
 Fake_El_MET_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_MET_up * ProcessEvent.passSelectionEl);
 Fake_El_MET_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_MET_down * ProcessEvent.passSelectionEl);
 Fake_El_RealStat_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_RealStat_up * ProcessEvent.passSelectionEl);
 Fake_El_RealStat_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_RealStat_down * ProcessEvent.passSelectionEl);

 Fake_Mu_Stat_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_Stat_up * ProcessEvent.passSelectionMu);
 Fake_Mu_Stat_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_Stat_down * ProcessEvent.passSelectionMu);
 Fake_Mu_PromptSubtr_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_PromptSubtr_up * ProcessEvent.passSelectionMu);
 Fake_Mu_PromptSubtr_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_PromptSubtr_down * ProcessEvent.passSelectionMu);
 Fake_Mu_d0sig_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_d0sig_up * ProcessEvent.passSelectionMu);
 Fake_Mu_d0sig_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_d0sig_down * ProcessEvent.passSelectionMu);
 Fake_Mu_RealStat_up->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_RealStat_up * ProcessEvent.passSelectionMu);
 Fake_Mu_RealStat_down->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.RecoWeight_RealStat_down * ProcessEvent.passSelectionMu);

}

void ZPrimeHistGroup::Fill(int iThread, double par1, double par2, double weight, EventZPrime ProcessEvent)
{
 SR_2D_ee_bkg->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl);
 SR_2D_mm_bkg->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu);
 SR_2D_em_bkg->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu);

 if(isData[iThread - 1]){
   topDD_2D_ee->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl);
   topDD_2D_mm->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu);

   topDD_HighMass_CosTheta_2D_ee->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_CosTheta);
   topDD_HighMass_CosTheta_2D_mm->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_CosTheta);

   topDD_HighMass_Rapidity_2D_ee->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_Rapidity);
   topDD_HighMass_Rapidity_2D_mm->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_Rapidity);
 }
 if(MCType[iThread - 1] == "DrellYan" || MCType[iThread - 1] == "Diboson" || MCType[iThread - 1] == "Ztautau" || MCType[iThread - 1] == "Wjets"){
   topDD_2D_ee->HistPtr(iThread - 1)->Fill(par1, par2, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl);
   topDD_2D_mm->HistPtr(iThread - 1)->Fill(par1, par2, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu);

   topDD_HighMass_CosTheta_2D_ee->HistPtr(iThread - 1)->Fill(par1, par2, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_CosTheta);
   topDD_HighMass_CosTheta_2D_mm->HistPtr(iThread - 1)->Fill(par1, par2, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_CosTheta);

   topDD_HighMass_Rapidity_2D_ee->HistPtr(iThread - 1)->Fill(par1, par2, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferEl_HighMass_Rapidity);
   topDD_HighMass_Rapidity_2D_mm->HistPtr(iThread - 1)->Fill(par1, par2, (-1.0) * weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu * ProcessEvent.topTransferMu_HighMass_Rapidity);
 }

 ElFakeCR_2D_bkg->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeightLoose
                                                                * ProcessEvent.Lepton1_PrescaleFactor
                                                                * ProcessEvent.SingleElectron
                                                                * ProcessEvent.passElFake);

 MuFakeCR_2D_bkg->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.TotalWeightLoose
                                                                * ProcessEvent.Lepton1_TightWeight
                                                                * ProcessEvent.Lepton2_TightWeight
                                                                * ProcessEvent.eeChannel_withmuon
                                                                * ProcessEvent.passMuFake);

 if(isFillFakeUnc && MCType[iThread - 1] == "Wjets_DD") FillFakeUnc(iThread, par1, par2, weight, ProcessEvent);
}

void ZPrimeHistGroup::FillFakeUnc(int iThread, double par1, double par2, double weight, EventZPrime ProcessEvent)
{
 Fake2D_El_Stat_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_Stat_up * ProcessEvent.passSelectionEl);
 Fake2D_El_Stat_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_Stat_down * ProcessEvent.passSelectionEl);
 Fake2D_El_PromptSubtr_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_PromptSubtr_up * ProcessEvent.passSelectionEl);
 Fake2D_El_PromptSubtr_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_PromptSubtr_down * ProcessEvent.passSelectionEl);
 Fake2D_El_MET_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_MET_up * ProcessEvent.passSelectionEl);
 Fake2D_El_MET_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_MET_down * ProcessEvent.passSelectionEl);
 Fake2D_El_RealStat_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_RealStat_up * ProcessEvent.passSelectionEl);
 Fake2D_El_RealStat_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_RealStat_down * ProcessEvent.passSelectionEl);

 Fake2D_Mu_Stat_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_Stat_up * ProcessEvent.passSelectionMu);
 Fake2D_Mu_Stat_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_Stat_down * ProcessEvent.passSelectionMu);
 Fake2D_Mu_PromptSubtr_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_PromptSubtr_up * ProcessEvent.passSelectionMu);
 Fake2D_Mu_PromptSubtr_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_PromptSubtr_down * ProcessEvent.passSelectionMu);
 Fake2D_Mu_d0sig_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_d0sig_up * ProcessEvent.passSelectionMu);
 Fake2D_Mu_d0sig_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_d0sig_down * ProcessEvent.passSelectionMu);
 Fake2D_Mu_RealStat_up->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_RealStat_up * ProcessEvent.passSelectionMu);
 Fake2D_Mu_RealStat_down->HistPtr(iThread - 1)->Fill(par1, par2, weight * ProcessEvent.RecoWeight_RealStat_down * ProcessEvent.passSelectionMu);
}

void ZPrimeHistGroup::FillTruth(int iThread, double par1, double weight, EventZPrime ProcessEvent)
{

}

void ZPrimeHistGroup::FillTruth(int iThread, double par1, double par2, double weight, EventZPrime ProcessEvent)
{

}

void ZPrimeHistGroup::FillUnfold(int iThread, double reco, double truth, double weight, int passReco, int passTruth, EventZPrime ProcessEvent)
{

}

void HistsZPrime::bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double left, double right)
{
 hist = new ZPrimeHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, left, right);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsZPrime::bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 hist = new ZPrimeHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, xbins);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsZPrime::bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 hist = new ZPrimeHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsZPrime::bookAllProcessHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 hist = new ZPrimeHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbinx, xbins, nbiny, ybins);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsZPrime::DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double left, double right)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_ee_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_mm_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_SR_em";
 BookBkgHist(hist->SR_em_bkg, "ZPrime", name, title, nbin, left, right);

 subName =    "_SSM_ee_0p5TeV";
 BookHist(hist->SSM_ee_0p5TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_0p6TeV";
 BookHist(hist->SSM_ee_0p6TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_0p8TeV";
 BookHist(hist->SSM_ee_0p8TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_1TeV";
 BookHist(hist->SSM_ee_1TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_2TeV";
 BookHist(hist->SSM_ee_2TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_3TeV";
 BookHist(hist->SSM_ee_3TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_4TeV";
 BookHist(hist->SSM_ee_4TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_5TeV";
 BookHist(hist->SSM_ee_5TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_6TeV";
 BookHist(hist->SSM_ee_6TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_7TeV";
 BookHist(hist->SSM_ee_7TeV, name, title, nbin, left, right);

 subName =    "_SSM_ee_8TeV";
 BookHist(hist->SSM_ee_8TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_0p5TeV";
 BookHist(hist->E6Chi_ee_0p5TeV, name, title, nbin, left, right);
 
 subName =    "_E6Chi_ee_0p6TeV";
 BookHist(hist->E6Chi_ee_0p6TeV, name, title, nbin, left, right);
 
 subName =    "_E6Chi_ee_0p8TeV";
 BookHist(hist->E6Chi_ee_0p8TeV, name, title, nbin, left, right);
 
 subName =    "_E6Chi_ee_1TeV";
 BookHist(hist->E6Chi_ee_1TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_2TeV";
 BookHist(hist->E6Chi_ee_2TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_3TeV";
 BookHist(hist->E6Chi_ee_3TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_4TeV";
 BookHist(hist->E6Chi_ee_4TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_5TeV";
 BookHist(hist->E6Chi_ee_5TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_6TeV";
 BookHist(hist->E6Chi_ee_6TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_7TeV";
 BookHist(hist->E6Chi_ee_7TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_ee_8TeV";
 BookHist(hist->E6Chi_ee_8TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_0p5TeV";
 BookHist(hist->E6Psi_ee_0p5TeV, name, title, nbin, left, right);
 
 subName =    "_E6Psi_ee_0p6TeV";
 BookHist(hist->E6Psi_ee_0p6TeV, name, title, nbin, left, right);
 
 subName =    "_E6Psi_ee_0p8TeV";
 BookHist(hist->E6Psi_ee_0p8TeV, name, title, nbin, left, right);
 
 subName =    "_E6Psi_ee_1TeV";
 BookHist(hist->E6Psi_ee_1TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_2TeV";
 BookHist(hist->E6Psi_ee_2TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_3TeV";
 BookHist(hist->E6Psi_ee_3TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_4TeV";
 BookHist(hist->E6Psi_ee_4TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_5TeV";
 BookHist(hist->E6Psi_ee_5TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_6TeV";
 BookHist(hist->E6Psi_ee_6TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_7TeV";
 BookHist(hist->E6Psi_ee_7TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_ee_8TeV";
 BookHist(hist->E6Psi_ee_8TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_0p5TeV";
 BookHist(hist->SSM_mm_0p5TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_0p6TeV";
 BookHist(hist->SSM_mm_0p6TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_0p8TeV";
 BookHist(hist->SSM_mm_0p8TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_1TeV";
 BookHist(hist->SSM_mm_1TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_2TeV";
 BookHist(hist->SSM_mm_2TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_3TeV";
 BookHist(hist->SSM_mm_3TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_4TeV";
 BookHist(hist->SSM_mm_4TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_5TeV";
 BookHist(hist->SSM_mm_5TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_6TeV";
 BookHist(hist->SSM_mm_6TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_7TeV";
 BookHist(hist->SSM_mm_7TeV, name, title, nbin, left, right);

 subName =    "_SSM_mm_8TeV";
 BookHist(hist->SSM_mm_8TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_0p5TeV";
 BookHist(hist->E6Chi_mm_0p5TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_0p6TeV";
 BookHist(hist->E6Chi_mm_0p6TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_0p8TeV";
 BookHist(hist->E6Chi_mm_0p8TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_1TeV";
 BookHist(hist->E6Chi_mm_1TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_2TeV";
 BookHist(hist->E6Chi_mm_2TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_3TeV";
 BookHist(hist->E6Chi_mm_3TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_4TeV";
 BookHist(hist->E6Chi_mm_4TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_5TeV";
 BookHist(hist->E6Chi_mm_5TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_6TeV";
 BookHist(hist->E6Chi_mm_6TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_7TeV";
 BookHist(hist->E6Chi_mm_7TeV, name, title, nbin, left, right);

 subName =    "_E6Chi_mm_8TeV";
 BookHist(hist->E6Chi_mm_8TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_0p5TeV";
 BookHist(hist->E6Psi_mm_0p5TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_0p6TeV";
 BookHist(hist->E6Psi_mm_0p6TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_0p8TeV";
 BookHist(hist->E6Psi_mm_0p8TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_1TeV";
 BookHist(hist->E6Psi_mm_1TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_2TeV";
 BookHist(hist->E6Psi_mm_2TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_3TeV";
 BookHist(hist->E6Psi_mm_3TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_4TeV";
 BookHist(hist->E6Psi_mm_4TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_5TeV";
 BookHist(hist->E6Psi_mm_5TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_6TeV";
 BookHist(hist->E6Psi_mm_6TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_7TeV";
 BookHist(hist->E6Psi_mm_7TeV, name, title, nbin, left, right);

 subName =    "_E6Psi_mm_8TeV";
 BookHist(hist->E6Psi_mm_8TeV, name, title, nbin, left, right);

 subName = "_topDD_ee";
 BookHist(hist->topDD_ee, name, title, nbin, left, right);

 subName = "_topDD_mm";
 BookHist(hist->topDD_mm, name, title, nbin, left, right);

 subName = "_topDD_HighMass_CosTheta_ee";
 BookHist(hist->topDD_HighMass_CosTheta_ee, name, title, nbin, left, right);
 
 subName = "_topDD_HighMass_CosTheta_mm";
 BookHist(hist->topDD_HighMass_CosTheta_mm, name, title, nbin, left, right);

 subName = "_topDD_HighMass_Rapidity_ee";
 BookHist(hist->topDD_HighMass_Rapidity_ee, name, title, nbin, left, right);

 subName = "_topDD_HighMass_Rapidity_mm";
 BookHist(hist->topDD_HighMass_Rapidity_mm, name, title, nbin, left, right);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_bkg, "ZPrime_MuFakes", name, title, nbin, left, right);

 subName = "_ElFake_TT";
 BookBkgHist(hist->ElFake_TT_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_ElFake_TL";
 BookBkgHist(hist->ElFake_TL_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_ElFake_LT";
 BookBkgHist(hist->ElFake_LT_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_ElFake_LL";
 BookBkgHist(hist->ElFake_LL_bkg, "ZPrime", name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_TT";
 BookHist(hist->Fake_MM_FourTerm_TT, name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_TL";
 BookHist(hist->Fake_MM_FourTerm_TL, name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_LT";
 BookHist(hist->Fake_MM_FourTerm_LT, name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_LL";
 BookHist(hist->Fake_MM_FourTerm_LL, name, title, nbin, left, right);

 subName = "_Fake_El_Stat_up";
 BookHist(hist->Fake_El_Stat_up, name, title, nbin, left, right);

 subName = "_Fake_El_Stat_down";
 BookHist(hist->Fake_El_Stat_down, name, title, nbin, left, right);

 subName = "_Fake_El_PromptSubtr_up";
 BookHist(hist->Fake_El_PromptSubtr_up, name, title, nbin, left, right);

 subName = "_Fake_El_PromptSubtr_down";
 BookHist(hist->Fake_El_PromptSubtr_down, name, title, nbin, left, right);

 subName = "_Fake_El_MET_up";
 BookHist(hist->Fake_El_MET_up, name, title, nbin, left, right);

 subName = "_Fake_El_MET_down";
 BookHist(hist->Fake_El_MET_down, name, title, nbin, left, right);

 subName = "_Fake_El_RealStat_up";
 BookHist(hist->Fake_El_RealStat_up, name, title, nbin, left, right);

 subName = "_Fake_El_RealStat_down";
 BookHist(hist->Fake_El_RealStat_down, name, title, nbin, left, right);

 subName = "_Fake_Mu_Stat_up";
 BookHist(hist->Fake_Mu_Stat_up, name, title, nbin, left, right);

 subName = "_Fake_Mu_Stat_down";
 BookHist(hist->Fake_Mu_Stat_down, name, title, nbin, left, right);

 subName = "_Fake_Mu_PromptSubtr_up";
 BookHist(hist->Fake_Mu_PromptSubtr_up, name, title, nbin, left, right);

 subName = "_Fake_Mu_PromptSubtr_down";
 BookHist(hist->Fake_Mu_PromptSubtr_down, name, title, nbin, left, right);

 subName = "_Fake_Mu_d0sig_up";
 BookHist(hist->Fake_Mu_d0sig_up, name, title, nbin, left, right);

 subName = "_Fake_Mu_d0sig_down";
 BookHist(hist->Fake_Mu_d0sig_down, name, title, nbin, left, right);

 subName = "_Fake_Mu_RealStat_up";
 BookHist(hist->Fake_Mu_RealStat_up, name, title, nbin, left, right);

 subName = "_Fake_Mu_RealStat_down";
 BookHist(hist->Fake_Mu_RealStat_down, name, title, nbin, left, right);

 hist->Dimension = 1;
}

void HistsZPrime::DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_ee_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_mm_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_SR_em";
 BookBkgHist(hist->SR_em_bkg, "ZPrime", name, title, nbin, xbins);

 subName =    "_SSM_ee_0p5TeV";
 BookHist(hist->SSM_ee_0p5TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_0p6TeV";
 BookHist(hist->SSM_ee_0p6TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_0p8TeV";
 BookHist(hist->SSM_ee_0p8TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_1TeV";
 BookHist(hist->SSM_ee_1TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_2TeV";
 BookHist(hist->SSM_ee_2TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_3TeV";
 BookHist(hist->SSM_ee_3TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_4TeV";
 BookHist(hist->SSM_ee_4TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_5TeV";
 BookHist(hist->SSM_ee_5TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_6TeV";
 BookHist(hist->SSM_ee_6TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_7TeV";
 BookHist(hist->SSM_ee_7TeV, name, title, nbin, xbins);

 subName =    "_SSM_ee_8TeV";
 BookHist(hist->SSM_ee_8TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_0p5TeV";
 BookHist(hist->E6Chi_ee_0p5TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_0p6TeV";
 BookHist(hist->E6Chi_ee_0p6TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_0p8TeV";
 BookHist(hist->E6Chi_ee_0p8TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_1TeV";
 BookHist(hist->E6Chi_ee_1TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_2TeV";
 BookHist(hist->E6Chi_ee_2TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_3TeV";
 BookHist(hist->E6Chi_ee_3TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_4TeV";
 BookHist(hist->E6Chi_ee_4TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_5TeV";
 BookHist(hist->E6Chi_ee_5TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_6TeV";
 BookHist(hist->E6Chi_ee_6TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_7TeV";
 BookHist(hist->E6Chi_ee_7TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_ee_8TeV";
 BookHist(hist->E6Chi_ee_8TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_0p5TeV";
 BookHist(hist->E6Psi_ee_0p5TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_0p6TeV";
 BookHist(hist->E6Psi_ee_0p6TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_0p8TeV";
 BookHist(hist->E6Psi_ee_0p8TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_1TeV";
 BookHist(hist->E6Psi_ee_1TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_2TeV";
 BookHist(hist->E6Psi_ee_2TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_3TeV";
 BookHist(hist->E6Psi_ee_3TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_4TeV";
 BookHist(hist->E6Psi_ee_4TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_5TeV";
 BookHist(hist->E6Psi_ee_5TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_6TeV";
 BookHist(hist->E6Psi_ee_6TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_7TeV";
 BookHist(hist->E6Psi_ee_7TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_ee_8TeV";
 BookHist(hist->E6Psi_ee_8TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_0p5TeV";
 BookHist(hist->SSM_mm_0p5TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_0p6TeV";
 BookHist(hist->SSM_mm_0p6TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_0p8TeV";
 BookHist(hist->SSM_mm_0p8TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_1TeV";
 BookHist(hist->SSM_mm_1TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_2TeV";
 BookHist(hist->SSM_mm_2TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_3TeV";
 BookHist(hist->SSM_mm_3TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_4TeV";
 BookHist(hist->SSM_mm_4TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_5TeV";
 BookHist(hist->SSM_mm_5TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_6TeV";
 BookHist(hist->SSM_mm_6TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_7TeV";
 BookHist(hist->SSM_mm_7TeV, name, title, nbin, xbins);

 subName =    "_SSM_mm_8TeV";
 BookHist(hist->SSM_mm_8TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_0p5TeV";
 BookHist(hist->E6Chi_mm_0p5TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_0p6TeV";
 BookHist(hist->E6Chi_mm_0p6TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_0p8TeV";
 BookHist(hist->E6Chi_mm_0p8TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_1TeV";
 BookHist(hist->E6Chi_mm_1TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_2TeV";
 BookHist(hist->E6Chi_mm_2TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_3TeV";
 BookHist(hist->E6Chi_mm_3TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_4TeV";
 BookHist(hist->E6Chi_mm_4TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_5TeV";
 BookHist(hist->E6Chi_mm_5TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_6TeV";
 BookHist(hist->E6Chi_mm_6TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_7TeV";
 BookHist(hist->E6Chi_mm_7TeV, name, title, nbin, xbins);

 subName =    "_E6Chi_mm_8TeV";
 BookHist(hist->E6Chi_mm_8TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_0p5TeV";
 BookHist(hist->E6Psi_mm_0p5TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_0p6TeV";
 BookHist(hist->E6Psi_mm_0p6TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_0p8TeV";
 BookHist(hist->E6Psi_mm_0p8TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_1TeV";
 BookHist(hist->E6Psi_mm_1TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_2TeV";
 BookHist(hist->E6Psi_mm_2TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_3TeV";
 BookHist(hist->E6Psi_mm_3TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_4TeV";
 BookHist(hist->E6Psi_mm_4TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_5TeV";
 BookHist(hist->E6Psi_mm_5TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_6TeV";
 BookHist(hist->E6Psi_mm_6TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_7TeV";
 BookHist(hist->E6Psi_mm_7TeV, name, title, nbin, xbins);

 subName =    "_E6Psi_mm_8TeV";
 BookHist(hist->E6Psi_mm_8TeV, name, title, nbin, xbins);

 subName = "_topDD_ee";
 BookHist(hist->topDD_ee, name, title, nbin, xbins);

 subName = "_topDD_mm";
 BookHist(hist->topDD_mm, name, title, nbin, xbins);

 subName = "_topDD_HighMass_CosTheta_ee";
 BookHist(hist->topDD_HighMass_CosTheta_ee, name, title, nbin, xbins);

 subName = "_topDD_HighMass_CosTheta_mm";
 BookHist(hist->topDD_HighMass_CosTheta_mm, name, title, nbin, xbins);

 subName = "_topDD_HighMass_Rapidity_ee";
 BookHist(hist->topDD_HighMass_Rapidity_ee, name, title, nbin, xbins);

 subName = "_topDD_HighMass_Rapidity_mm";
 BookHist(hist->topDD_HighMass_Rapidity_mm, name, title, nbin, xbins);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_bkg, "ZPrime_MuFakes", name, title, nbin, xbins);

 subName = "_ElFake_TT";
 BookBkgHist(hist->ElFake_TT_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_ElFake_TL";
 BookBkgHist(hist->ElFake_TL_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_ElFake_LT";
 BookBkgHist(hist->ElFake_LT_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_ElFake_LL";
 BookBkgHist(hist->ElFake_LL_bkg, "ZPrime", name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_TT";
 BookHist(hist->Fake_MM_FourTerm_TT, name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_TL";
 BookHist(hist->Fake_MM_FourTerm_TL, name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_LT";
 BookHist(hist->Fake_MM_FourTerm_LT, name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_LL";
 BookHist(hist->Fake_MM_FourTerm_LL, name, title, nbin, xbins);

 subName = "_Fake_El_Stat_up";
 BookHist(hist->Fake_El_Stat_up, name, title, nbin, xbins);

 subName = "_Fake_El_Stat_down";
 BookHist(hist->Fake_El_Stat_down, name, title, nbin, xbins);

 subName = "_Fake_El_PromptSubtr_up";
 BookHist(hist->Fake_El_PromptSubtr_up, name, title, nbin, xbins);

 subName = "_Fake_El_PromptSubtr_down";
 BookHist(hist->Fake_El_PromptSubtr_down, name, title, nbin, xbins);

 subName = "_Fake_El_MET_up";
 BookHist(hist->Fake_El_MET_up, name, title, nbin, xbins);

 subName = "_Fake_El_MET_down";
 BookHist(hist->Fake_El_MET_down, name, title, nbin, xbins);

 subName = "_Fake_El_RealStat_up";
 BookHist(hist->Fake_El_RealStat_up, name, title, nbin, xbins);

 subName = "_Fake_El_RealStat_down";
 BookHist(hist->Fake_El_RealStat_down, name, title, nbin, xbins);

 subName = "_Fake_Mu_Stat_up";
 BookHist(hist->Fake_Mu_Stat_up, name, title, nbin, xbins);

 subName = "_Fake_Mu_Stat_down";
 BookHist(hist->Fake_Mu_Stat_down, name, title, nbin, xbins);

 subName = "_Fake_Mu_PromptSubtr_up";
 BookHist(hist->Fake_Mu_PromptSubtr_up, name, title, nbin, xbins);

 subName = "_Fake_Mu_PromptSubtr_down";
 BookHist(hist->Fake_Mu_PromptSubtr_down, name, title, nbin, xbins);

 subName = "_Fake_Mu_d0sig_up";
 BookHist(hist->Fake_Mu_d0sig_up, name, title, nbin, xbins);

 subName = "_Fake_Mu_d0sig_down";
 BookHist(hist->Fake_Mu_d0sig_down, name, title, nbin, xbins);

 subName = "_Fake_Mu_RealStat_up";
 BookHist(hist->Fake_Mu_RealStat_up, name, title, nbin, xbins);

 subName = "_Fake_Mu_RealStat_down";
 BookHist(hist->Fake_Mu_RealStat_down, name, title, nbin, xbins);

 hist->Dimension = 1;
}

void HistsZPrime::DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_2D_ee_bkg, "ZPrime", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_2D_mm_bkg, "ZPrime", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_SR_em";
 BookBkgHist(hist->SR_2D_em_bkg, "ZPrime", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_topDD_ee";
 Book2DHist(hist->topDD_2D_ee, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);
 
 subName = "_topDD_mm";
 Book2DHist(hist->topDD_2D_mm, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_topDD_HighMass_CosTheta_ee";
 Book2DHist(hist->topDD_HighMass_CosTheta_2D_ee, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_topDD_HighMass_CosTheta_mm";
 Book2DHist(hist->topDD_HighMass_CosTheta_2D_mm, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_topDD_HighMass_Rapidity_ee";
 Book2DHist(hist->topDD_HighMass_Rapidity_2D_ee, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_topDD_HighMass_Rapidity_mm";
 Book2DHist(hist->topDD_HighMass_Rapidity_2D_mm, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_2D_bkg, "ZPrime", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_2D_bkg, "ZPrime_MuFakes", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_Stat_up";
 Book2DHist(hist->Fake2D_El_Stat_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_Stat_down";
 Book2DHist(hist->Fake2D_El_Stat_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_PromptSubtr_up";
 Book2DHist(hist->Fake2D_El_PromptSubtr_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_PromptSubtr_down";
 Book2DHist(hist->Fake2D_El_PromptSubtr_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_MET_up";
 Book2DHist(hist->Fake2D_El_MET_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_MET_down";
 Book2DHist(hist->Fake2D_El_MET_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_RealStat_up";
 Book2DHist(hist->Fake2D_El_RealStat_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_El_RealStat_down";
 Book2DHist(hist->Fake2D_El_RealStat_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_Stat_up";
 Book2DHist(hist->Fake2D_Mu_Stat_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_Stat_down";
 Book2DHist(hist->Fake2D_Mu_Stat_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_PromptSubtr_up";
 Book2DHist(hist->Fake2D_Mu_PromptSubtr_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_PromptSubtr_down";
 Book2DHist(hist->Fake2D_Mu_PromptSubtr_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_d0sig_up";
 Book2DHist(hist->Fake2D_Mu_d0sig_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_d0sig_down";
 Book2DHist(hist->Fake2D_Mu_d0sig_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_RealStat_up";
 Book2DHist(hist->Fake2D_Mu_RealStat_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Fake_Mu_RealStat_down";
 Book2DHist(hist->Fake2D_Mu_RealStat_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 hist->Dimension = 2;
}

void HistsZPrime::DefineHist(ZPrimeHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_2D_ee_bkg, "ZPrime", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_2D_mm_bkg, "ZPrime", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_SR_em";
 BookBkgHist(hist->SR_2D_em_bkg, "ZPrime", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_topDD_ee";
 Book2DHist(hist->topDD_2D_ee, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_topDD_mm";
 Book2DHist(hist->topDD_2D_mm, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_topDD_HighMass_CosTheta_ee";
 Book2DHist(hist->topDD_HighMass_CosTheta_2D_ee, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_topDD_HighMass_CosTheta_mm";
 Book2DHist(hist->topDD_HighMass_CosTheta_2D_mm, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_topDD_HighMass_Rapidity_ee";
 Book2DHist(hist->topDD_HighMass_Rapidity_2D_ee, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_topDD_HighMass_Rapidity_mm";
 Book2DHist(hist->topDD_HighMass_Rapidity_2D_mm, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_2D_bkg, "ZPrime", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_2D_bkg, "ZPrime_MuFakes", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_Stat_up";
 Book2DHist(hist->Fake2D_El_Stat_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_Stat_down";
 Book2DHist(hist->Fake2D_El_Stat_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_PromptSubtr_up";
 Book2DHist(hist->Fake2D_El_PromptSubtr_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_PromptSubtr_down";
 Book2DHist(hist->Fake2D_El_PromptSubtr_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_MET_up";
 Book2DHist(hist->Fake2D_El_MET_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_MET_down";
 Book2DHist(hist->Fake2D_El_MET_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_RealStat_up";
 Book2DHist(hist->Fake2D_El_RealStat_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_El_RealStat_down";
 Book2DHist(hist->Fake2D_El_RealStat_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_Mu_Stat_up";
 Book2DHist(hist->Fake2D_Mu_Stat_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_Mu_Stat_down";
 Book2DHist(hist->Fake2D_Mu_Stat_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_Mu_PromptSubtr_up";
 Book2DHist(hist->Fake2D_Mu_PromptSubtr_up, name, title, nbinx, xbins, nbiny, ybins);
 
 subName = "_Fake_Mu_PromptSubtr_down";
 Book2DHist(hist->Fake2D_Mu_PromptSubtr_down, name, title, nbinx, xbins, nbiny, ybins);
 
 subName = "_Fake_Mu_d0sig_up";
 Book2DHist(hist->Fake2D_Mu_d0sig_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_Mu_d0sig_down";
 Book2DHist(hist->Fake2D_Mu_d0sig_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_Mu_RealStat_up";
 Book2DHist(hist->Fake2D_Mu_RealStat_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Fake_Mu_RealStat_down";
 Book2DHist(hist->Fake2D_Mu_RealStat_down, name, title, nbinx, xbins, nbiny, ybins);

 hist->Dimension = 2;
}

void ZPrimeHistGroup::ResetHist()
{
 cout<<"Reset "<<HistName<<endl;

 if(Dimension == 1){
   SR_ee_bkg->Reset();
   SR_mm_bkg->Reset();
   SR_em_bkg->Reset();
   topDD_ee->Reset();
   topDD_mm->Reset();
   topDD_HighMass_CosTheta_ee->Reset();
   topDD_HighMass_CosTheta_mm->Reset();
   topDD_HighMass_Rapidity_ee->Reset();
   topDD_HighMass_Rapidity_mm->Reset();
   ElFakeCR_bkg->Reset();
   MuFakeCR_bkg->Reset();
   ElFake_TT_bkg->Reset();
   ElFake_TL_bkg->Reset();
   ElFake_LT_bkg->Reset();
   ElFake_LL_bkg->Reset();

 }

 if(Dimension == 2){
   SR_2D_ee_bkg->Reset();
   SR_2D_mm_bkg->Reset();
   SR_2D_em_bkg->Reset();
   topDD_2D_ee->Reset();
   topDD_2D_mm->Reset();
   topDD_HighMass_CosTheta_2D_ee->Reset();
   topDD_HighMass_CosTheta_2D_mm->Reset();
   topDD_HighMass_Rapidity_2D_ee->Reset();
   topDD_HighMass_Rapidity_2D_mm->Reset();
   ElFakeCR_2D_bkg->Reset();
   MuFakeCR_2D_bkg->Reset();
 }
}

void ZPrimeHistGroup::ApplyFakeUnc()
{
 // This function is called before doing saveHist, so dealing with negative bins is after this function.

 if(Dimension == 1){
   ElFake_Nominal = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD")->Clone((TString)SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD")->GetName() + "_Nominal");
   MuFake_Nominal = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD")->Clone((TString)SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD")->GetName() + "_Nominal");
 }
 else if(Dimension == 2){
   ElFake2D_Nominal = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD")->Clone((TString)SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD")->GetName() + "_Nominal");
   MuFake2D_Nominal = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD")->Clone((TString)SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD")->GetName() + "_Nominal");
 }

 if(!isFillFakeUnc){
   if(Dimension == 1){
     ElFake_Nominal->Write();
     MuFake_Nominal->Write();
   }
   else if(Dimension == 2){
     ElFake2D_Nominal->Write();
     MuFake2D_Nominal->Write();
   }

   return;
 }

 if(Dimension == 1){
   for(int ibin = 1; ibin <= Fake_El_PromptSubtr_up->at(0)->GetNbinsX(); ibin++){
     double Central = SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD")->GetBinContent(ibin);
     double StatErr = SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD")->GetBinError(ibin);

     double PromptSubtr_up = Fake_El_PromptSubtr_up->at(0)->GetBinContent(ibin);
     double PromptSubtr_down = Fake_El_PromptSubtr_down->at(0)->GetBinContent(ibin);
     double Stat_up = Fake_El_Stat_up->at(0)->GetBinContent(ibin);
     double Stat_down = Fake_El_Stat_down->at(0)->GetBinContent(ibin);
     double MET_up = Fake_El_MET_up->at(0)->GetBinContent(ibin);
     double MET_down = Fake_El_MET_down->at(0)->GetBinContent(ibin);
     double RealStat_up = Fake_El_RealStat_up->at(0)->GetBinContent(ibin);
     double RealStat_down = Fake_El_RealStat_down->at(0)->GetBinContent(ibin);

     if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
     if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
     if(Stat_up < 1e-10) Stat_up = Central;
     if(Stat_down < 1e-10) Stat_down = Central;
     if(MET_up < 1e-10) MET_up = Central;
     if(MET_down < 1e-10) MET_down = Central;
     if(RealStat_up < 1e-10) RealStat_up = Central;
     if(RealStat_down < 1e-10) RealStat_down = Central;

     double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                              + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                              + pow(max(fabs(Central - MET_up), fabs(Central - MET_down)), 2)
                              + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2));

     SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD")->SetBinContent(ibin, Central + CombineError);
     ElFake_Nominal->SetBinContent(ibin, Central);
     ElFake_Nominal->SetBinError(ibin, sqrt(StatErr * StatErr + CombineError * CombineError));
   }

   for(int ibin = 1; ibin <= Fake_Mu_Stat_up->at(0)->GetNbinsX(); ibin++){
     double Central = SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD")->GetBinContent(ibin);
     double StatErr = SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD")->GetBinError(ibin);

     double PromptSubtr_up = Fake_Mu_PromptSubtr_up->at(0)->GetBinContent(ibin);
     double PromptSubtr_down = Fake_Mu_PromptSubtr_down->at(0)->GetBinContent(ibin);
     double Stat_up = Fake_Mu_Stat_up->at(0)->GetBinContent(ibin);
     double Stat_down = Fake_Mu_Stat_down->at(0)->GetBinContent(ibin);
     double d0sig_up = Fake_Mu_d0sig_up->at(0)->GetBinContent(ibin);
     double d0sig_down = Fake_Mu_d0sig_down->at(0)->GetBinContent(ibin);
     double RealStat_up = Fake_Mu_RealStat_up->at(0)->GetBinContent(ibin);
     double RealStat_down = Fake_Mu_RealStat_down->at(0)->GetBinContent(ibin);

     if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
     if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
     if(Stat_up < 1e-10) Stat_up = Central;
     if(Stat_down < 1e-10) Stat_down = Central;
     if(d0sig_up < 1e-10) d0sig_up = Central;
     if(d0sig_down < 1e-10) d0sig_down = Central;
     if(RealStat_up < 1e-10) RealStat_up = Central;
     if(RealStat_down < 1e-10) RealStat_down = Central;

     double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                              + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                              + pow(max(fabs(Central - d0sig_up), fabs(Central - d0sig_down)), 2)
                              + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2));

     SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD")->SetBinContent(ibin, Central + CombineError);
     MuFake_Nominal->SetBinContent(ibin, Central);
     MuFake_Nominal->SetBinError(ibin, sqrt(StatErr * StatErr + CombineError * CombineError));
   }

   ElFake_Nominal->Write();
   MuFake_Nominal->Write();
 }
 else if(Dimension == 2){
   for(int ibinx = 1; ibinx <= Fake2D_El_PromptSubtr_up->at(0)->GetNbinsX(); ibinx++){
       for(int ibiny = 1; ibiny <= Fake2D_El_PromptSubtr_up->at(0)->GetNbinsY(); ibiny++){

       double Central = SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD")->GetBinContent(ibinx, ibiny);
       double StatErr = SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD")->GetBinError(ibinx, ibiny);

       double PromptSubtr_up = Fake2D_El_PromptSubtr_up->at(0)->GetBinContent(ibinx, ibiny);
       double PromptSubtr_down = Fake2D_El_PromptSubtr_down->at(0)->GetBinContent(ibinx, ibiny);
       double Stat_up = Fake2D_El_Stat_up->at(0)->GetBinContent(ibinx, ibiny);
       double Stat_down = Fake2D_El_Stat_down->at(0)->GetBinContent(ibinx, ibiny);
       double RealStat_up = Fake2D_El_RealStat_up->at(0)->GetBinContent(ibinx, ibiny);
       double RealStat_down = Fake2D_El_RealStat_down->at(0)->GetBinContent(ibinx, ibiny);

       if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
       if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
       if(Stat_up < 1e-10) Stat_up = Central;
       if(Stat_down < 1e-10) Stat_down = Central;
       if(RealStat_up < 1e-10) RealStat_up = Central;
       if(RealStat_down < 1e-10) RealStat_down = Central;

       double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                                + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                                + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2));

       SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD")->SetBinContent(ibinx, ibiny, Central + CombineError);
       ElFake2D_Nominal->SetBinContent(ibinx, ibiny, Central);
       ElFake2D_Nominal->SetBinError(ibinx, ibiny, StatErr);
     }
   }

   for(int ibinx = 1; ibinx <= Fake2D_Mu_Stat_up->at(0)->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= Fake2D_Mu_Stat_up->at(0)->GetNbinsY(); ibiny++){

       double Central = SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD")->GetBinContent(ibinx, ibiny);
       double StatErr = SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD")->GetBinError(ibinx, ibiny);

       double PromptSubtr_up = Fake2D_Mu_PromptSubtr_up->at(0)->GetBinContent(ibinx, ibiny);
       double PromptSubtr_down = Fake2D_Mu_PromptSubtr_down->at(0)->GetBinContent(ibinx, ibiny);
       double Stat_up = Fake2D_Mu_Stat_up->at(0)->GetBinContent(ibinx, ibiny);
       double Stat_down = Fake2D_Mu_Stat_down->at(0)->GetBinContent(ibinx, ibiny);
       double d0sig_up = Fake2D_Mu_d0sig_up->at(0)->GetBinContent(ibinx, ibiny);
       double d0sig_down = Fake2D_Mu_d0sig_down->at(0)->GetBinContent(ibinx, ibiny);
       double RealStat_up = Fake2D_Mu_RealStat_up->at(0)->GetBinContent(ibinx, ibiny);
       double RealStat_down = Fake2D_Mu_RealStat_down->at(0)->GetBinContent(ibinx, ibiny);

       if(PromptSubtr_up < 1e-10) PromptSubtr_up = Central;
       if(PromptSubtr_down < 1e-10) PromptSubtr_down = Central;
       if(Stat_up < 1e-10) Stat_up = Central;
       if(Stat_down < 1e-10) Stat_down = Central;
       if(d0sig_up < 1e-10) d0sig_up = Central;
       if(d0sig_down < 1e-10) d0sig_down = Central;
       if(RealStat_up < 1e-10) RealStat_up = Central;
       if(RealStat_down < 1e-10) RealStat_down = Central;

       double CombineError = sqrt(pow(max(fabs(Stat_up - Central), fabs(Central - Stat_down)), 2)
                                + pow(max(fabs(PromptSubtr_down - Central), fabs(Central - PromptSubtr_up)), 2)
                                + pow(max(fabs(Central - d0sig_up), fabs(Central - d0sig_down)), 2)
                                + pow(max(fabs(RealStat_up - Central), fabs(Central - RealStat_down)), 2));

       SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD")->SetBinContent(ibinx, ibiny, Central + CombineError);
       MuFake2D_Nominal->SetBinContent(ibinx, ibiny, Central);
       MuFake2D_Nominal->SetBinError(ibinx, ibiny, StatErr);
     }
   }

   ElFake2D_Nominal->Write();
   MuFake2D_Nominal->Write();
 }
}

void ZPrimeHistGroup::GetFinalData()
{
 if(Dimension == 1){
 }

 if(Dimension == 2){
 }

}




#endif
