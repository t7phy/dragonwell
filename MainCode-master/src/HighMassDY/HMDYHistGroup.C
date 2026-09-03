#ifndef WZPol_HMDYHistGroup_cxx
#define WZPol_HMDYHistGroup_cxx
#include "HighMassDY/HistsHMDY.h"

using namespace std;

HMDYHistGroup::HMDYHistGroup()
{
}

void HMDYHistGroup::Initial(int iThread, TString MCType)
{
 this->MCType[iThread - 1] = MCType;

 if(this->MCType[iThread - 1] == "Data") isData[iThread - 1] = true;
 else isData[iThread - 1] = false;

 if(this->MCType[iThread - 1] == "TopQuark") isTop[iThread - 1] = true;
 else isTop[iThread - 1] = false;

}

void HMDYHistGroup::Fill(int iThread, double par, double weight, EventHMDY ProcessEvent)
{
 SR_ee_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionEl);
 SR_mm_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionMu);
 SR_em_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeight * ProcessEvent.passSelectionElMu);

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

 //LowMass_ee_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionEl_LowMass);
 //LowMass_mm_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionMu_LowMass);
 //LowMass_em_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passSelectionElMu_LowMass);

 ElFakeCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeightLoose
                                                      * ProcessEvent.Lepton1_PrescaleFactor
                                                      * ProcessEvent.SingleElectron
                                                      * ProcessEvent.passElFake);

 MuFakeCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.TotalWeightLoose
                                                      * ProcessEvent.Lepton1_TightWeight
                                                      * ProcessEvent.Lepton2_TightWeight
                                                      * ProcessEvent.eeChannel_withmuon
                                                      * ProcessEvent.passMuFake);

 // For closure test
 //ProcessEvent.Lepton1_isTruthMatch = 1;
 //ProcessEvent.Lepton2_isTruthMatch = 1;

 if(ProcessEvent.Lepton1_FakeRate >= 0.0){
   double F1 = ProcessEvent.Lepton1_FakeRate;
   double F2 = ProcessEvent.Lepton2_FakeRate;

   double TotalWeightLoose = weight * ProcessEvent.TotalWeightLoose;

   double FakeWeight = TotalWeightLoose * ProcessEvent.passSelectionEl 
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_Stat_up;
   F2 = ProcessEvent.Lepton2_FakeRate_Stat_up;
   double FakeWeight_Stat_up = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_Stat_down;
   F2 = ProcessEvent.Lepton2_FakeRate_Stat_down;
   double FakeWeight_Stat_down = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_PromptSubtr_up;
   F2 = ProcessEvent.Lepton2_FakeRate_PromptSubtr_up;
   double FakeWeight_PromptSubtr_up = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_PromptSubtr_down;
   F2 = ProcessEvent.Lepton2_FakeRate_PromptSubtr_down;
   double FakeWeight_PromptSubtr_down = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_MET_up;
   F2 = ProcessEvent.Lepton2_FakeRate_MET_up;
   double FakeWeight_MET_up = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_MET_down;
   F2 = ProcessEvent.Lepton2_FakeRate_MET_down;
   double FakeWeight_MET_down = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   if(isData[iThread - 1]){
     ElFake_FakeRate->at(iThread - 1)->Fill(par, FakeWeight);
     ElFake_FakeRate_Stat_up->at(iThread - 1)->Fill(par, FakeWeight_Stat_up);
     ElFake_FakeRate_Stat_down->at(iThread - 1)->Fill(par, FakeWeight_Stat_down);
     ElFake_FakeRate_PromptSubtr_up->at(iThread - 1)->Fill(par, FakeWeight_PromptSubtr_up);
     ElFake_FakeRate_PromptSubtr_down->at(iThread - 1)->Fill(par, FakeWeight_PromptSubtr_down);
     ElFake_FakeRate_MET_up->at(iThread - 1)->Fill(par, FakeWeight_MET_up);
     ElFake_FakeRate_MET_down->at(iThread - 1)->Fill(par, FakeWeight_MET_down);
     ElFake_FakeRate_RealPromptSubtr_up->at(iThread - 1)->Fill(par, FakeWeight);
     ElFake_FakeRate_RealPromptSubtr_down->at(iThread - 1)->Fill(par, FakeWeight);
   }
   else if(MCType[iThread - 1] == "DrellYan" || MCType[iThread - 1] == "Diboson" || MCType[iThread - 1] == "Ztautau" || MCType[iThread - 1] == "TopQuark" || MCType[iThread - 1] == "PhotonInduced"){
     ElFake_FakeRate->at(iThread - 1)->Fill(par, FakeWeight * (-1.0));
     ElFake_FakeRate_Stat_up->at(iThread - 1)->Fill(par, FakeWeight_Stat_up * (-1.0));
     ElFake_FakeRate_Stat_down->at(iThread - 1)->Fill(par, FakeWeight_Stat_down * (-1.0));
     ElFake_FakeRate_PromptSubtr_up->at(iThread - 1)->Fill(par, FakeWeight_PromptSubtr_up * (-1.0));
     ElFake_FakeRate_PromptSubtr_down->at(iThread - 1)->Fill(par, FakeWeight_PromptSubtr_down * (-1.0));
     ElFake_FakeRate_MET_up->at(iThread - 1)->Fill(par, FakeWeight_MET_up * (-1.0));
     ElFake_FakeRate_MET_down->at(iThread - 1)->Fill(par, FakeWeight_MET_down * (-1.0));
     ElFake_FakeRate_RealPromptSubtr_up->at(iThread - 1)->Fill(par, FakeWeight * (-0.9));
     ElFake_FakeRate_RealPromptSubtr_down->at(iThread - 1)->Fill(par, FakeWeight * (-1.1));
   }

   // Remind: TotalWeightLoose = weight * ProcessEvent.TotalWeightLoose
   ElFake_TT_bkg->HistPtr(iThread - 1)->Fill(par, TotalWeightLoose * ProcessEvent.passSelectionEl
                                                                   * ProcessEvent.pass_ee_TT
                                                                   * ProcessEvent.Lepton1_TightWeight
                                                                   * ProcessEvent.Lepton2_TightWeight
                                                                   * ProcessEvent.Lepton1_isTruthMatch
                                                                   * ProcessEvent.Lepton2_isTruthMatch);

   ElFake_TL_bkg->HistPtr(iThread - 1)->Fill(par, TotalWeightLoose * ProcessEvent.passSelectionEl 
                                                                   * ProcessEvent.pass_ee_TL 
                                                                   * ProcessEvent.Lepton1_TightWeight
                                                                   * ProcessEvent.Lepton2_LooseWeight
                                                                   * ProcessEvent.Lepton1_isTruthMatch
                                                                   * ProcessEvent.Lepton2_isTruthMatch);

   ElFake_LT_bkg->HistPtr(iThread - 1)->Fill(par, TotalWeightLoose * ProcessEvent.passSelectionEl
                                                                   * ProcessEvent.pass_ee_LT
                                                                   * ProcessEvent.Lepton1_LooseWeight
                                                                   * ProcessEvent.Lepton2_TightWeight
                                                                   * ProcessEvent.Lepton1_isTruthMatch
                                                                   * ProcessEvent.Lepton2_isTruthMatch);

   ElFake_LL_bkg->HistPtr(iThread - 1)->Fill(par, TotalWeightLoose * ProcessEvent.passSelectionEl
                                                                   * ProcessEvent.pass_ee_LL
                                                                   * ProcessEvent.Lepton1_LooseWeight
                                                                   * ProcessEvent.Lepton2_LooseWeight
                                                                   * ProcessEvent.Lepton1_isTruthMatch
                                                                   * ProcessEvent.Lepton2_isTruthMatch);
 }

 if(isFillFakeUnc && MCType[iThread - 1] == "Wjets_DD") FillFakeUnc(iThread, par, weight, ProcessEvent);
}

void HMDYHistGroup::FillFakeUnc(int iThread, double par, double weight, EventHMDY ProcessEvent)
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

 /*
 Fake_PromptSubtrUp->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_PromptSubtrUp * ProcessEvent.passSelectionEl);
 Fake_PromptSubtrDown->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_PromptSubtrDown * ProcessEvent.passSelectionEl);
 Fake_noW->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_noW * ProcessEvent.passSelectionEl);
 Fake_noDY->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_noDY * ProcessEvent.passSelectionEl);
 Fake_noZMass->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_noZMass * ProcessEvent.passSelectionEl);
 Fake_StatsUp->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_StatsUp * ProcessEvent.passSelectionEl);
 Fake_StatsDown->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_StatsDown * ProcessEvent.passSelectionEl);

 Fake_stats_1up->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_stats_1up * ProcessEvent.passSelectionMu);
 Fake_stats_1down->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_stats_1down * ProcessEvent.passSelectionMu);
 Fake_d0Sig_1up->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_d0Sig_1up * ProcessEvent.passSelectionMu);
 Fake_d0Sig_1down->HistPtr(iThread - 1)->Fill(par, ProcessEvent.RecoWeight_d0Sig_1down * ProcessEvent.passSelectionMu);
 */
}

void HMDYHistGroup::Fill(int iThread, double par1, double par2, double weight, EventHMDY ProcessEvent)
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
 if(ProcessEvent.Lepton1_FakeRate >= 0.0){
   double F1 = ProcessEvent.Lepton1_FakeRate;
   double F2 = ProcessEvent.Lepton2_FakeRate;

   double TotalWeightLoose = weight * ProcessEvent.TotalWeightLoose;

   double FakeWeight = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_Stat_up;
   F2 = ProcessEvent.Lepton2_FakeRate_Stat_up;
   double FakeWeight_Stat_up = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_Stat_down;
   F2 = ProcessEvent.Lepton2_FakeRate_Stat_down;
   double FakeWeight_Stat_down = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_PromptSubtr_up;
   F2 = ProcessEvent.Lepton2_FakeRate_PromptSubtr_up;
   double FakeWeight_PromptSubtr_up = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_PromptSubtr_down;
   F2 = ProcessEvent.Lepton2_FakeRate_PromptSubtr_down;
   double FakeWeight_PromptSubtr_down = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_MET_up;
   F2 = ProcessEvent.Lepton2_FakeRate_MET_up;
   double FakeWeight_MET_up = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   F1 = ProcessEvent.Lepton1_FakeRate_MET_down;
   F2 = ProcessEvent.Lepton2_FakeRate_MET_down;
   double FakeWeight_MET_down = TotalWeightLoose * ProcessEvent.passSelectionEl
                     * (ProcessEvent.pass_ee_TL * ProcessEvent.Lepton1_TightWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F2
                      + ProcessEvent.pass_ee_LT * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_TightWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1
                      - ProcessEvent.pass_ee_LL * ProcessEvent.Lepton1_LooseWeight * ProcessEvent.Lepton2_LooseWeight * ProcessEvent.Lepton1_isTruthMatch * ProcessEvent.Lepton2_isTruthMatch * F1 * F2);

   if(isData[iThread - 1]){
     ElFake2D_FakeRate->at(iThread - 1)->Fill(par1, par2, FakeWeight);
     ElFake2D_FakeRate_Stat_up->at(iThread - 1)->Fill(par1, par2, FakeWeight_Stat_up);
     ElFake2D_FakeRate_Stat_down->at(iThread - 1)->Fill(par1, par2, FakeWeight_Stat_down);
     ElFake2D_FakeRate_PromptSubtr_up->at(iThread - 1)->Fill(par1, par2, FakeWeight_PromptSubtr_up);
     ElFake2D_FakeRate_PromptSubtr_down->at(iThread - 1)->Fill(par1, par2, FakeWeight_PromptSubtr_down);
     ElFake2D_FakeRate_MET_up->at(iThread - 1)->Fill(par1, par2, FakeWeight_MET_up);
     ElFake2D_FakeRate_MET_down->at(iThread - 1)->Fill(par1, par2, FakeWeight_MET_down);
     ElFake2D_FakeRate_RealPromptSubtr_up->at(iThread - 1)->Fill(par1, par2, FakeWeight);
     ElFake2D_FakeRate_RealPromptSubtr_down->at(iThread - 1)->Fill(par1, par2, FakeWeight);
   }
   else if(MCType[iThread - 1] == "DrellYan" || MCType[iThread - 1] == "Diboson" || MCType[iThread - 1] == "Ztautau" || MCType[iThread - 1] == "TopQuark" || MCType[iThread - 1] == "PhotonInduced"){
     ElFake2D_FakeRate->at(iThread - 1)->Fill(par1, par2, FakeWeight * (-1.0));
     ElFake2D_FakeRate_Stat_up->at(iThread - 1)->Fill(par1, par2, FakeWeight_Stat_up * (-1.0));
     ElFake2D_FakeRate_Stat_down->at(iThread - 1)->Fill(par1, par2, FakeWeight_Stat_down * (-1.0));
     ElFake2D_FakeRate_PromptSubtr_up->at(iThread - 1)->Fill(par1, par2, FakeWeight_PromptSubtr_up * (-1.0));
     ElFake2D_FakeRate_PromptSubtr_down->at(iThread - 1)->Fill(par1, par2, FakeWeight_PromptSubtr_down * (-1.0));
     ElFake2D_FakeRate_MET_up->at(iThread - 1)->Fill(par1, par2, FakeWeight_MET_up * (-1.0));
     ElFake2D_FakeRate_MET_down->at(iThread - 1)->Fill(par1, par2, FakeWeight_MET_down * (-1.0));
     ElFake2D_FakeRate_RealPromptSubtr_up->at(iThread - 1)->Fill(par1, par2, FakeWeight * (-0.9));
     ElFake2D_FakeRate_RealPromptSubtr_down->at(iThread - 1)->Fill(par1, par2, FakeWeight * (-1.1));
   }
 }

 if(isFillFakeUnc && MCType[iThread - 1] == "Wjets_DD") FillFakeUnc(iThread, par1, par2, weight, ProcessEvent);
}

void HMDYHistGroup::FillFakeUnc(int iThread, double par1, double par2, double weight, EventHMDY ProcessEvent)
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

void HMDYHistGroup::FillTruth(int iThread, double par1, double weight, EventHMDY ProcessEvent)
{
 double TruthWeight = ProcessEvent.RecoWeight * ProcessEvent.Weight_kFactor_New_CT18ANNLO;

 if(MCType[iThread - 1] == "DrellYan"){
   Truth_DrellYan_El->HistPtr(iThread - 1)->Fill(par1, weight * TruthWeight * ProcessEvent.passSelectionEl_Truth);
   Truth_DrellYan_Mu->HistPtr(iThread - 1)->Fill(par1, weight * TruthWeight * ProcessEvent.passSelectionMu_Truth);
 }

 if(MCType[iThread - 1] == "PhotonInduced"){
   Truth_PI_El->HistPtr(iThread - 1)->Fill(par1, weight * TruthWeight * ProcessEvent.passSelectionEl_Truth);
   Truth_PI_Mu->HistPtr(iThread - 1)->Fill(par1, weight * TruthWeight * ProcessEvent.passSelectionMu_Truth);
 }

}

void HMDYHistGroup::FillTruth(int iThread, double par1, double par2, double weight, EventHMDY ProcessEvent)
{
 double TruthWeight = ProcessEvent.RecoWeight * ProcessEvent.Weight_kFactor_New_CT18ANNLO;
 //double TruthWeight = ProcessEvent.RecoWeight * ProcessEvent.Weight_kFactor_New_CT18NNLO;

 if(MCType[iThread - 1] == "DrellYan"){
   Truth_DrellYan_El_2D->HistPtr(iThread - 1)->Fill(par1, par2, weight * TruthWeight * ProcessEvent.passSelectionEl_Truth);
   Truth_DrellYan_Mu_2D->HistPtr(iThread - 1)->Fill(par1, par2, weight * TruthWeight * ProcessEvent.passSelectionMu_Truth);
 }

 if(MCType[iThread - 1] == "PhotonInduced"){
   Truth_PI_El_2D->HistPtr(iThread - 1)->Fill(par1, par2, weight * TruthWeight * ProcessEvent.passSelectionEl_Truth);
   Truth_PI_Mu_2D->HistPtr(iThread - 1)->Fill(par1, par2, weight * TruthWeight * ProcessEvent.passSelectionMu_Truth);
 }

}

void HMDYHistGroup::FillUnfold(int iThread, double reco, double truth, double weight, int passReco, int passTruth, EventHMDY ProcessEvent)
{
 double TruthWeight = ProcessEvent.RecoWeight * ProcessEvent.Weight_kFactor_New_CT18ANNLO;
 //double TruthWeight = ProcessEvent.RecoWeight * ProcessEvent.Weight_kFactor_New_CT18NNLO;

 if(MCType[iThread - 1] == "DrellYan"){
   if(passReco && passTruth){
     if(ProcessEvent.isElSample) Response_DrellYan_El->HistPtr(iThread - 1)->Fill(reco, truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isElSample) TruthForUnfold_DrellYan_El->HistPtr(iThread - 1)->Fill(truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isElSample) RecoForUnfold_DrellYan_El->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) Response_DrellYan_Mu->HistPtr(iThread - 1)->Fill(reco, truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) TruthForUnfold_DrellYan_Mu->HistPtr(iThread - 1)->Fill(truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) RecoForUnfold_DrellYan_Mu->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
   }
   else if(passReco && !passTruth){
     if(ProcessEvent.isElSample) RecoForUnfold_DrellYan_El->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) RecoForUnfold_DrellYan_Mu->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
   }
   else if(!passReco && passTruth){
     if(ProcessEvent.isElSample) TruthForUnfold_DrellYan_El->HistPtr(iThread - 1)->Fill(truth, weight * TruthWeight);
     if(ProcessEvent.isMuSample) TruthForUnfold_DrellYan_Mu->HistPtr(iThread - 1)->Fill(truth, weight * TruthWeight);
   }
 }

 if(MCType[iThread - 1] == "PhotonInduced"){
   if(passReco && passTruth){
     if(ProcessEvent.isElSample) Response_PI_El->HistPtr(iThread - 1)->Fill(reco, truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isElSample) TruthForUnfold_PI_El->HistPtr(iThread - 1)->Fill(truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isElSample) RecoForUnfold_PI_El->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) Response_PI_Mu->HistPtr(iThread - 1)->Fill(reco, truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) TruthForUnfold_PI_Mu->HistPtr(iThread - 1)->Fill(truth, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) RecoForUnfold_PI_Mu->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
   }
   else if(passReco && !passTruth){
     if(ProcessEvent.isElSample) RecoForUnfold_PI_El->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
     if(ProcessEvent.isMuSample) RecoForUnfold_PI_Mu->HistPtr(iThread - 1)->Fill(reco, weight * ProcessEvent.TotalWeight);
   }
   else if(!passReco && passTruth){
     if(ProcessEvent.isElSample) TruthForUnfold_PI_El->HistPtr(iThread - 1)->Fill(truth, weight * TruthWeight);
     if(ProcessEvent.isMuSample) TruthForUnfold_PI_Mu->HistPtr(iThread - 1)->Fill(truth, weight * TruthWeight);
   }
 }

}

void HistsHMDY::bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double left, double right)
{
 hist = new HMDYHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, left, right);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsHMDY::bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 hist = new HMDYHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, xbins);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsHMDY::bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 hist = new HMDYHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsHMDY::bookAllProcessHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 hist = new HMDYHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbinx, xbins, nbiny, ybins);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsHMDY::DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double left, double right)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_ee_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_mm_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_SR_em";
 BookBkgHist(hist->SR_em_bkg, "HMDY", name, title, nbin, left, right);

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

 //subName = "_LowMass_ee";
 //BookBkgHist(hist->LowMass_ee_bkg, "HMDY", name, title, nbin, left, right);

 //subName = "_LowMass_mm";
 //BookBkgHist(hist->LowMass_mm_bkg, "HMDY", name, title, nbin, left, right);

 //subName = "_LowMass_em";
 //BookBkgHist(hist->LowMass_em_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_Truth_DrellYan_El";
 BookHist(hist->Truth_DrellYan_El, name, title, nbin, left, right);

 subName = "_Truth_DrellYan_Mu";
 BookHist(hist->Truth_DrellYan_Mu, name, title, nbin, left, right);

 subName = "_Truth_PI_El";
 BookHist(hist->Truth_PI_El, name, title, nbin, left, right);

 subName = "_Truth_PI_Mu";
 BookHist(hist->Truth_PI_Mu, name, title, nbin, left, right);

 subName = "_Response_DrellYan_El";
 Book2DHist(hist->Response_DrellYan_El, name, title, nbin, left, right, nbin, left, right);

 subName = "_Response_DrellYan_Mu";
 Book2DHist(hist->Response_DrellYan_Mu, name, title, nbin, left, right, nbin, left, right);

 subName = "_TruthForUnfold_DrellYan_El";
 BookHist(hist->TruthForUnfold_DrellYan_El, name, title, nbin, left, right);

 subName = "_TruthForUnfold_DrellYan_Mu";
 BookHist(hist->TruthForUnfold_DrellYan_Mu, name, title, nbin, left, right);

 subName = "_RecoForUnfold_DrellYan_El";
 BookHist(hist->RecoForUnfold_DrellYan_El, name, title, nbin, left, right);

 subName = "_RecoForUnfold_DrellYan_Mu";
 BookHist(hist->RecoForUnfold_DrellYan_Mu, name, title, nbin, left, right);

 subName = "_Response_PI_El";
 Book2DHist(hist->Response_PI_El, name, title, nbin, left, right, nbin, left, right);

 subName = "_Response_PI_Mu";
 Book2DHist(hist->Response_PI_Mu, name, title, nbin, left, right, nbin, left, right);

 subName = "_TruthForUnfold_PI_El";
 BookHist(hist->TruthForUnfold_PI_El, name, title, nbin, left, right);

 subName = "_TruthForUnfold_PI_Mu";
 BookHist(hist->TruthForUnfold_PI_Mu, name, title, nbin, left, right);

 subName = "_RecoForUnfold_PI_El";
 BookHist(hist->RecoForUnfold_PI_El, name, title, nbin, left, right);

 subName = "_RecoForUnfold_PI_Mu";
 BookHist(hist->RecoForUnfold_PI_Mu, name, title, nbin, left, right);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_bkg, "HMDY_MuFakes", name, title, nbin, left, right);

 subName = "_Wjets_FakeRate";
 BookHist(hist->ElFake_FakeRate, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_Stat_up";
 BookHist(hist->ElFake_FakeRate_Stat_up, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_Stat_down";
 BookHist(hist->ElFake_FakeRate_Stat_down, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_PromptSubtr_up";
 BookHist(hist->ElFake_FakeRate_PromptSubtr_up, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_PromptSubtr_down";
 BookHist(hist->ElFake_FakeRate_PromptSubtr_down, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_MET_up";
 BookHist(hist->ElFake_FakeRate_MET_up, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_MET_down";
 BookHist(hist->ElFake_FakeRate_MET_down, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_RealPromptSubtr_up";
 BookHist(hist->ElFake_FakeRate_RealPromptSubtr_up, name, title, nbin, left, right);

 subName = "_Wjets_FakeRate_RealPromptSubtr_down";
 BookHist(hist->ElFake_FakeRate_RealPromptSubtr_down, name, title, nbin, left, right);

 subName = "_ElFake_TT";
 BookBkgHist(hist->ElFake_TT_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_ElFake_TL";
 BookBkgHist(hist->ElFake_TL_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_ElFake_LT";
 BookBkgHist(hist->ElFake_LT_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_ElFake_LL";
 BookBkgHist(hist->ElFake_LL_bkg, "HMDY", name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_TT";
 BookHist(hist->Fake_MM_FourTerm_TT, name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_TL";
 BookHist(hist->Fake_MM_FourTerm_TL, name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_LT";
 BookHist(hist->Fake_MM_FourTerm_LT, name, title, nbin, left, right);

 subName = "_Fake_MM_FourTerm_LL";
 BookHist(hist->Fake_MM_FourTerm_LL, name, title, nbin, left, right);

 // Electron Fake
 /*subName = "_Fake_PromptSubtrUp";
 BookHist(hist->Fake_PromptSubtrUp, name, title, nbin, left, right);

 subName = "_Fake_PromptSubtrDown";
 BookHist(hist->Fake_PromptSubtrDown, name, title, nbin, left, right);

 subName = "_Fake_noW";
 BookHist(hist->Fake_noW, name, title, nbin, left, right);

 subName = "_Fake_noDY";
 BookHist(hist->Fake_noDY, name, title, nbin, left, right);

 subName = "_Fake_noZMass";
 BookHist(hist->Fake_noZMass, name, title, nbin, left, right);

 subName = "_Fake_StatsUp";
 BookHist(hist->Fake_StatsUp, name, title, nbin, left, right);

 subName = "_Fake_StatsDown";
 BookHist(hist->Fake_StatsDown, name, title, nbin, left, right);
 */

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

 // Muon Fake
 /*subName = "_Fake_stats_1up";
 BookHist(hist->Fake_stats_1up, name, title, nbin, left, right);

 subName = "_Fake_stats_1down";
 BookHist(hist->Fake_stats_1down, name, title, nbin, left, right);

 subName = "_Fake_d0Sig_1up";
 BookHist(hist->Fake_d0Sig_1up, name, title, nbin, left, right);

 subName = "_Fake_d0Sig_1down";
 BookHist(hist->Fake_d0Sig_1down, name, title, nbin, left, right);
 */

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

void HistsHMDY::DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_ee_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_mm_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_SR_em";
 BookBkgHist(hist->SR_em_bkg, "HMDY", name, title, nbin, xbins);

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

 //subName = "_LowMass_ee";
 //BookBkgHist(hist->LowMass_ee_bkg, "HMDY", name, title, nbin, xbins);

 //subName = "_LowMass_mm";
 //BookBkgHist(hist->LowMass_mm_bkg, "HMDY", name, title, nbin, xbins);

 //subName = "_LowMass_em";
 //BookBkgHist(hist->LowMass_em_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_Truth_DrellYan_El";
 BookHist(hist->Truth_DrellYan_El, name, title, nbin, xbins);

 subName = "_Truth_DrellYan_Mu";
 BookHist(hist->Truth_DrellYan_Mu, name, title, nbin, xbins);

 subName = "_Truth_PI_El";
 BookHist(hist->Truth_PI_El, name, title, nbin, xbins);

 subName = "_Truth_PI_Mu";
 BookHist(hist->Truth_PI_Mu, name, title, nbin, xbins);

 subName = "_Response_DrellYan_El";
 Book2DHist(hist->Response_DrellYan_El, name, title, nbin, xbins, nbin, xbins);

 subName = "_Response_DrellYan_Mu";
 Book2DHist(hist->Response_DrellYan_Mu, name, title, nbin, xbins, nbin, xbins);

 subName = "_TruthForUnfold_DrellYan_El";
 BookHist(hist->TruthForUnfold_DrellYan_El, name, title, nbin, xbins);

 subName = "_TruthForUnfold_DrellYan_Mu";
 BookHist(hist->TruthForUnfold_DrellYan_Mu, name, title, nbin, xbins);

 subName = "_RecoForUnfold_DrellYan_El";
 BookHist(hist->RecoForUnfold_DrellYan_El, name, title, nbin, xbins);

 subName = "_RecoForUnfold_DrellYan_Mu";
 BookHist(hist->RecoForUnfold_DrellYan_Mu, name, title, nbin, xbins);

 subName = "_Response_PI_El";
 Book2DHist(hist->Response_PI_El, name, title, nbin, xbins, nbin, xbins);
 
 subName = "_Response_PI_Mu";
 Book2DHist(hist->Response_PI_Mu, name, title, nbin, xbins, nbin, xbins);

 subName = "_TruthForUnfold_PI_El";
 BookHist(hist->TruthForUnfold_PI_El, name, title, nbin, xbins);

 subName = "_TruthForUnfold_PI_Mu";
 BookHist(hist->TruthForUnfold_PI_Mu, name, title, nbin, xbins);

 subName = "_RecoForUnfold_PI_El";
 BookHist(hist->RecoForUnfold_PI_El, name, title, nbin, xbins);

 subName = "_RecoForUnfold_PI_Mu";
 BookHist(hist->RecoForUnfold_PI_Mu, name, title, nbin, xbins);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_bkg, "HMDY_MuFakes", name, title, nbin, xbins);

 subName = "_Wjets_FakeRate";
 BookHist(hist->ElFake_FakeRate, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_Stat_up";
 BookHist(hist->ElFake_FakeRate_Stat_up, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_Stat_down";
 BookHist(hist->ElFake_FakeRate_Stat_down, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_PromptSubtr_up";
 BookHist(hist->ElFake_FakeRate_PromptSubtr_up, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_PromptSubtr_down";
 BookHist(hist->ElFake_FakeRate_PromptSubtr_down, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_MET_up";
 BookHist(hist->ElFake_FakeRate_MET_up, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_MET_down";
 BookHist(hist->ElFake_FakeRate_MET_down, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_RealPromptSubtr_up";
 BookHist(hist->ElFake_FakeRate_RealPromptSubtr_up, name, title, nbin, xbins);

 subName = "_Wjets_FakeRate_RealPromptSubtr_down";
 BookHist(hist->ElFake_FakeRate_RealPromptSubtr_down, name, title, nbin, xbins);

 subName = "_ElFake_TT";
 BookBkgHist(hist->ElFake_TT_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_ElFake_TL";
 BookBkgHist(hist->ElFake_TL_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_ElFake_LT";
 BookBkgHist(hist->ElFake_LT_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_ElFake_LL";
 BookBkgHist(hist->ElFake_LL_bkg, "HMDY", name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_TT";
 BookHist(hist->Fake_MM_FourTerm_TT, name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_TL";
 BookHist(hist->Fake_MM_FourTerm_TL, name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_LT";
 BookHist(hist->Fake_MM_FourTerm_LT, name, title, nbin, xbins);

 subName = "_Fake_MM_FourTerm_LL";
 BookHist(hist->Fake_MM_FourTerm_LL, name, title, nbin, xbins);

 // Electron Fake
 /*
 subName = "_Fake_PromptSubtrUp";
 BookHist(hist->Fake_PromptSubtrUp, name, title, nbin, xbins);

 subName = "_Fake_PromptSubtrDown";
 BookHist(hist->Fake_PromptSubtrDown, name, title, nbin, xbins);

 subName = "_Fake_noW";
 BookHist(hist->Fake_noW, name, title, nbin, xbins);

 subName = "_Fake_noDY";
 BookHist(hist->Fake_noDY, name, title, nbin, xbins);

 subName = "_Fake_noZMass";
 BookHist(hist->Fake_noZMass, name, title, nbin, xbins);

 subName = "_Fake_StatsUp";
 BookHist(hist->Fake_StatsUp, name, title, nbin, xbins);

 subName = "_Fake_StatsDown";
 BookHist(hist->Fake_StatsDown, name, title, nbin, xbins);
 */
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

 // Muon Fake
 /*subName = "_Fake_stats_1up";
 BookHist(hist->Fake_stats_1up, name, title, nbin, xbins);

 subName = "_Fake_stats_1down";
 BookHist(hist->Fake_stats_1down, name, title, nbin, xbins);

 subName = "_Fake_d0Sig_1up";
 BookHist(hist->Fake_d0Sig_1up, name, title, nbin, xbins);

 subName = "_Fake_d0Sig_1down";
 BookHist(hist->Fake_d0Sig_1down, name, title, nbin, xbins);
 */
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

void HistsHMDY::DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_2D_ee_bkg, "HMDY", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_2D_mm_bkg, "HMDY", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_SR_em";
 BookBkgHist(hist->SR_2D_em_bkg, "HMDY", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

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

 subName = "_Truth_DrellYan_El";
 Book2DHist(hist->Truth_DrellYan_El_2D, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Truth_DrellYan_Mu";
 Book2DHist(hist->Truth_DrellYan_Mu_2D, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Truth_PI_El";
 Book2DHist(hist->Truth_PI_El_2D, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Truth_PI_Mu";
 Book2DHist(hist->Truth_PI_Mu_2D, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_2D_bkg, "HMDY", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_2D_bkg, "HMDY_MuFakes", name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate";
 Book2DHist(hist->ElFake2D_FakeRate, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_Stat_up";
 Book2DHist(hist->ElFake2D_FakeRate_Stat_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_Stat_down";
 Book2DHist(hist->ElFake2D_FakeRate_Stat_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_PromptSubtr_up";
 Book2DHist(hist->ElFake2D_FakeRate_PromptSubtr_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_PromptSubtr_down";
 Book2DHist(hist->ElFake2D_FakeRate_PromptSubtr_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_MET_up";
 Book2DHist(hist->ElFake2D_FakeRate_MET_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_MET_down";
 Book2DHist(hist->ElFake2D_FakeRate_MET_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_RealPromptSubtr_up";
 Book2DHist(hist->ElFake2D_FakeRate_RealPromptSubtr_up, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 subName = "_Wjets_FakeRate_RealPromptSubtr_down";
 Book2DHist(hist->ElFake2D_FakeRate_RealPromptSubtr_down, name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

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

void HistsHMDY::DefineHist(HMDYHistGroup* &hist, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_SR_ee";
 BookBkgHist(hist->SR_2D_ee_bkg, "HMDY", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_SR_mm";
 BookBkgHist(hist->SR_2D_mm_bkg, "HMDY", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_SR_em";
 BookBkgHist(hist->SR_2D_em_bkg, "HMDY", name, title, nbinx, xbins, nbiny, ybins);

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

 subName = "_Truth_DrellYan_El";
 Book2DHist(hist->Truth_DrellYan_El_2D, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Truth_DrellYan_Mu";
 Book2DHist(hist->Truth_DrellYan_Mu_2D, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Truth_PI_El";
 Book2DHist(hist->Truth_PI_El_2D, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Truth_PI_Mu";
 Book2DHist(hist->Truth_PI_Mu_2D, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_ElFakeCR";
 BookBkgHist(hist->ElFakeCR_2D_bkg, "HMDY", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_MuFakeCR";
 BookBkgHist(hist->MuFakeCR_2D_bkg, "HMDY_MuFakes", name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate";
 Book2DHist(hist->ElFake2D_FakeRate, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_Stat_up";
 Book2DHist(hist->ElFake2D_FakeRate_Stat_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_Stat_down";
 Book2DHist(hist->ElFake2D_FakeRate_Stat_down, name, title, nbinx, xbins, nbiny, ybins);
 
 subName = "_Wjets_FakeRate_PromptSubtr_up";
 Book2DHist(hist->ElFake2D_FakeRate_PromptSubtr_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_PromptSubtr_down";
 Book2DHist(hist->ElFake2D_FakeRate_PromptSubtr_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_MET_up";
 Book2DHist(hist->ElFake2D_FakeRate_MET_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_MET_down";
 Book2DHist(hist->ElFake2D_FakeRate_MET_down, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_RealPromptSubtr_up";
 Book2DHist(hist->ElFake2D_FakeRate_RealPromptSubtr_up, name, title, nbinx, xbins, nbiny, ybins);

 subName = "_Wjets_FakeRate_RealPromptSubtr_down";
 Book2DHist(hist->ElFake2D_FakeRate_RealPromptSubtr_down, name, title, nbinx, xbins, nbiny, ybins);

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

void HMDYHistGroup::ResetHist()
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
   //LowMass_ee_bkg->Reset();
   //LowMass_mm_bkg->Reset();
   //LowMass_em_bkg->Reset();
   Truth_DrellYan_El->Reset();
   Truth_DrellYan_Mu->Reset();
   Truth_PI_El->Reset();
   Truth_PI_Mu->Reset();
   ElFakeCR_bkg->Reset();
   MuFakeCR_bkg->Reset();
   ElFake_FakeRate->Reset();
   ElFake_FakeRate_Stat_up->Reset();
   ElFake_FakeRate_Stat_down->Reset();
   ElFake_FakeRate_PromptSubtr_up->Reset();
   ElFake_FakeRate_PromptSubtr_down->Reset();
   ElFake_FakeRate_RealPromptSubtr_up->Reset();
   ElFake_FakeRate_RealPromptSubtr_down->Reset();
   ElFake_TT_bkg->Reset();
   ElFake_TL_bkg->Reset();
   ElFake_LT_bkg->Reset();
   ElFake_LL_bkg->Reset();

   /*Fake_PromptSubtrUp->Reset();
   Fake_PromptSubtrDown->Reset();
   Fake_noW->Reset();
   Fake_noDY->Reset();
   Fake_noZMass->Reset();
   Fake_StatsUp->Reset();
   Fake_StatsDown->Reset();
   Fake_stats_1up->Reset();
   Fake_stats_1down->Reset();
   Fake_d0Sig_1up->Reset();
   Fake_d0Sig_1down->Reset();
   */
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
   Truth_DrellYan_El_2D->Reset();
   Truth_DrellYan_Mu_2D->Reset();
   Truth_PI_El_2D->Reset();
   Truth_PI_Mu_2D->Reset();
   ElFakeCR_2D_bkg->Reset();
   MuFakeCR_2D_bkg->Reset();
   ElFake2D_FakeRate->Reset();
   ElFake2D_FakeRate_Stat_up->Reset();
   ElFake2D_FakeRate_Stat_down->Reset();
   ElFake2D_FakeRate_PromptSubtr_up->Reset();
   ElFake2D_FakeRate_PromptSubtr_down->Reset();
   ElFake2D_FakeRate_RealPromptSubtr_up->Reset();
   ElFake2D_FakeRate_RealPromptSubtr_down->Reset();
 }
}

void HMDYHistGroup::ApplyFakeUnc()
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

void HMDYHistGroup::GetFinalData()
{
 if(Dimension == 1){
   FinalData_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_ee_FinalData");
   FinalData_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("DrellYan"), -1);
   FinalData_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("TopQuark"), -1);
   FinalData_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   FinalData_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_mm_FinalData");
   FinalData_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("DrellYan"), -1); 
   FinalData_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("TopQuark"), -1);
   FinalData_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   FinalData_topDD_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_ee_topDD_FinalData");
   FinalData_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("DrellYan"), -1); 
   FinalData_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_topDD_ee->Add(topDD_ee->at(0), -1);
   FinalData_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   FinalData_topDD_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_mm_topDD_FinalData");
   FinalData_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("DrellYan"), -1);
   FinalData_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_topDD_mm->Add(topDD_mm->at(0), -1);
   FinalData_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   FinalData_topDD_HighMass_CosTheta_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_ee_topDD_HighMass_CosTheta_FinalData");
   FinalData_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("DrellYan"), -1);
   FinalData_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_topDD_HighMass_CosTheta_ee->Add(topDD_HighMass_CosTheta_ee->at(0), -1);
   FinalData_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   FinalData_topDD_HighMass_CosTheta_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_mm_topDD_HighMass_CosTheta_FinalData");
   FinalData_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("DrellYan"), -1);
   FinalData_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_topDD_HighMass_CosTheta_mm->Add(topDD_HighMass_CosTheta_mm->at(0), -1);
   FinalData_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   FinalData_topDD_HighMass_Rapidity_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_ee_topDD_HighMass_Rapidity_FinalData");
   FinalData_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("DrellYan"), -1);
   FinalData_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_topDD_HighMass_Rapidity_ee->Add(topDD_HighMass_Rapidity_ee->at(0), -1);
   FinalData_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"), -1);
 
   FinalData_topDD_HighMass_Rapidity_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("Data")->Clone(HistName + "_SR_mm_topDD_HighMass_Rapidity_FinalData");
   FinalData_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("DrellYan"), -1);
   FinalData_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"), -1);
   FinalData_topDD_HighMass_Rapidity_mm->Add(topDD_HighMass_Rapidity_mm->at(0), -1);
   FinalData_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"), -1);
   FinalData_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"), -1);
   FinalData_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"), -1);

   SumMC_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_ee_SumMC");
   SumMC_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("TopQuark"));
   SumMC_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_mm_SumMC");
   SumMC_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("TopQuark"));
   SumMC_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_topDD_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_ee_topDD_SumMC");
   SumMC_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_topDD_ee->Add(topDD_ee->at(0));
   SumMC_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_topDD_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_topDD_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_mm_topDD_SumMC");
   SumMC_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_topDD_mm->Add(topDD_mm->at(0));
   SumMC_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_topDD_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_topDD_HighMass_CosTheta_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_ee_topDD_HighMass_CosTheta_SumMC");
   SumMC_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_topDD_HighMass_CosTheta_ee->Add(topDD_HighMass_CosTheta_ee->at(0));
   SumMC_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_topDD_HighMass_CosTheta_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_topDD_HighMass_CosTheta_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_mm_topDD_HighMass_CosTheta_SumMC");
   SumMC_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_topDD_HighMass_CosTheta_mm->Add(topDD_HighMass_CosTheta_mm->at(0));
   SumMC_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_topDD_HighMass_CosTheta_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_topDD_HighMass_Rapidity_ee = (TH1D *)SR_ee_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_ee_topDD_HighMass_Rapidity_SumMC");
   SumMC_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_topDD_HighMass_Rapidity_ee->Add(topDD_HighMass_Rapidity_ee->at(0));
   SumMC_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_topDD_HighMass_Rapidity_ee->Add(SR_ee_bkg->at(0)->GetHistPtr("Ztautau"));

   SumMC_topDD_HighMass_Rapidity_mm = (TH1D *)SR_mm_bkg->at(0)->GetHistPtr("DrellYan")->Clone(HistName + "_SR_mm_topDD_HighMass_Rapidity_SumMC");
   SumMC_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("PhotonInduced"));
   SumMC_topDD_HighMass_Rapidity_mm->Add(topDD_HighMass_Rapidity_mm->at(0));
   SumMC_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Diboson"));
   SumMC_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Wjets_DD"));
   SumMC_topDD_HighMass_Rapidity_mm->Add(SR_mm_bkg->at(0)->GetHistPtr("Ztautau"));

   FinalData_ee->Write();
   FinalData_mm->Write();
   FinalData_topDD_ee->Write();
   FinalData_topDD_mm->Write();
   FinalData_topDD_HighMass_CosTheta_ee->Write();
   FinalData_topDD_HighMass_CosTheta_mm->Write();
   FinalData_topDD_HighMass_Rapidity_ee->Write();
   FinalData_topDD_HighMass_Rapidity_mm->Write();

   SumMC_ee->Write();
   SumMC_mm->Write();
   SumMC_topDD_ee->Write();
   SumMC_topDD_mm->Write();
   SumMC_topDD_HighMass_CosTheta_ee->Write();
   SumMC_topDD_HighMass_CosTheta_mm->Write();
   SumMC_topDD_HighMass_Rapidity_ee->Write();
   SumMC_topDD_HighMass_Rapidity_mm->Write();
 }

 if(Dimension == 2){
   FinalData_2D_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_ee_FinalData");
   FinalData_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan"), -1);
   FinalData_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("TopQuark"), -1);
   FinalData_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   FinalData_2D_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_mm_FinalData");
   FinalData_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan"), -1); 
   FinalData_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("TopQuark"), -1);
   FinalData_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   FinalData_2D_topDD_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_ee_topDD_FinalData");
   FinalData_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan"), -1); 
   FinalData_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_topDD_ee->Add(topDD_2D_ee->at(0), -1);
   FinalData_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   FinalData_2D_topDD_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_mm_topDD_FinalData");
   FinalData_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan"), -1);
   FinalData_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_topDD_mm->Add(topDD_2D_mm->at(0), -1);
   FinalData_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   FinalData_2D_topDD_HighMass_CosTheta_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_ee_topDD_HighMass_CosTheta_FinalData");
   FinalData_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_ee->Add(topDD_HighMass_CosTheta_2D_ee->at(0), -1);
   FinalData_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   FinalData_2D_topDD_HighMass_CosTheta_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_mm_topDD_HighMass_CosTheta_FinalData");
   FinalData_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_mm->Add(topDD_HighMass_CosTheta_2D_mm->at(0), -1);
   FinalData_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   FinalData_2D_topDD_HighMass_Rapidity_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_ee_topDD_HighMass_Rapidity_FinalData");
   FinalData_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_ee->Add(topDD_HighMass_Rapidity_2D_ee->at(0), -1);
   FinalData_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);
 
   FinalData_2D_topDD_HighMass_Rapidity_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("Data")->Clone(HistName + "_SR_mm_topDD_HighMass_Rapidity_FinalData");
   FinalData_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_mm->Add(topDD_HighMass_Rapidity_2D_mm->at(0), -1);
   FinalData_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"), -1);
   FinalData_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"), -1);

   SumMC_2D_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_ee_SumMC");
   SumMC_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("TopQuark"));
   SumMC_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_mm_SumMC");
   SumMC_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("TopQuark"));
   SumMC_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_topDD_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_ee_topDD_SumMC");
   SumMC_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_topDD_ee->Add(topDD_2D_ee->at(0));
   SumMC_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_topDD_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_topDD_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_mm_topDD_SumMC");
   SumMC_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_topDD_mm->Add(topDD_2D_mm->at(0));
   SumMC_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_topDD_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_topDD_HighMass_CosTheta_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_ee_topDD_HighMass_CosTheta_SumMC");
   SumMC_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_topDD_HighMass_CosTheta_ee->Add(topDD_HighMass_CosTheta_2D_ee->at(0));
   SumMC_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_topDD_HighMass_CosTheta_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_topDD_HighMass_CosTheta_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_mm_topDD_HighMass_CosTheta_SumMC");
   SumMC_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_topDD_HighMass_CosTheta_mm->Add(topDD_HighMass_CosTheta_2D_mm->at(0));
   SumMC_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_topDD_HighMass_CosTheta_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_topDD_HighMass_Rapidity_ee = (TH2D *)SR_2D_ee_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_ee_topDD_HighMass_Rapidity_SumMC");
   SumMC_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_topDD_HighMass_Rapidity_ee->Add(topDD_HighMass_Rapidity_2D_ee->at(0));
   SumMC_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_topDD_HighMass_Rapidity_ee->Add(SR_2D_ee_bkg->at(0)->GetHistPtr2D("Ztautau"));

   SumMC_2D_topDD_HighMass_Rapidity_mm = (TH2D *)SR_2D_mm_bkg->at(0)->GetHistPtr2D("DrellYan")->Clone(HistName + "_SR_mm_topDD_HighMass_Rapidity_SumMC");
   SumMC_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("PhotonInduced"));
   SumMC_2D_topDD_HighMass_Rapidity_mm->Add(topDD_HighMass_Rapidity_2D_mm->at(0));
   SumMC_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Diboson"));
   SumMC_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Wjets_DD"));
   SumMC_2D_topDD_HighMass_Rapidity_mm->Add(SR_2D_mm_bkg->at(0)->GetHistPtr2D("Ztautau"));

   FinalData_2D_ee->Write();
   FinalData_2D_mm->Write();
   FinalData_2D_topDD_ee->Write();
   FinalData_2D_topDD_mm->Write();
   FinalData_2D_topDD_HighMass_CosTheta_ee->Write();
   FinalData_2D_topDD_HighMass_CosTheta_mm->Write();
   FinalData_2D_topDD_HighMass_Rapidity_ee->Write();
   FinalData_2D_topDD_HighMass_Rapidity_mm->Write();

   SumMC_2D_ee->Write();
   SumMC_2D_mm->Write();
   SumMC_2D_topDD_ee->Write();
   SumMC_2D_topDD_mm->Write();
   SumMC_2D_topDD_HighMass_CosTheta_ee->Write();
   SumMC_2D_topDD_HighMass_CosTheta_mm->Write();
   SumMC_2D_topDD_HighMass_Rapidity_ee->Write();
   SumMC_2D_topDD_HighMass_Rapidity_mm->Write();
 }

}




#endif
