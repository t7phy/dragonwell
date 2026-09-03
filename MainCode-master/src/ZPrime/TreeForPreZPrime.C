#define ZPrime_TreeForPreZPrime_cxx
#include "ZPrime/TreeForPreZPrime.h"

using namespace std;

TreeForPreZPrime::TreeForPreZPrime()
{
 Init();
}

TreeForPreZPrime::~TreeForPreZPrime()
{

}

void TreeForPreZPrime::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);

   TString RootType = GetRootType(RootNames.at(i));
   RootTypes.push_back(RootType);

   int Year = GetYear(RootNames.at(i));
   Years.push_back(Year);

   /*TTree* metaTree = (TTree *)rootfile[i]->Get("sumWeights");
   metaTree->GetEntry(0);
   int DSID = metaTree->GetLeaf("dsid")->GetValue();
   DSIDs.push_back(DSID);
   delete metaTree;
   */
 }

 InitialSysName();
}

void TreeForPreZPrime::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

 TString RootType = GetRootType(RootNames.at(ifile));
 RootTypes.clear();
 RootTypes.push_back(RootType);

 int Year = GetYear(RootNames.at(ifile));
 Years.clear();
 Years.push_back(Year);

 /*TTree* metaTree = (TTree *)rootfile[0]->Get("sumWeights");
 metaTree->GetEntry(0);
 int DSID = metaTree->GetLeaf("dsid")->GetValue();
 DSIDs.clear();
 DSIDs.push_back(DSID);
 delete metaTree;
 */

 cout<<"There is "<<EndFile<<" files."<<endl;
 cout<<RootNames.at(ifile)<<endl;

 InitialSysName();

}

void TreeForPreZPrime::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForPreZPrime::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPreZPrime::InputSumOfWeight(map<pair<int, int>, double> SumOfWeightsMap)
{
 this->SumOfWeightsMap = SumOfWeightsMap;
}

void TreeForPreZPrime::InputLuminosity(double Lumi1516, double Lumi17, double Lumi18)
{
 this->Lumi1516 = Lumi1516;
 this->Lumi17 = Lumi17;
 this->Lumi18 = Lumi18;
}

TString TreeForPreZPrime::GetRootType(TString name)
{
 TString RootType;

 if(name.Contains("data15_") || name.Contains("data16_") || name.Contains("data17_") || name.Contains("data18_")
 || name.Contains("data22")  || name.Contains("data23")  || name.Contains("data24") || name.Contains("data_merged")){
   RootType = "Data";
 }
 else if(name.Contains("DrellYan") || name.Contains("Zee") || name.Contains("Zmm")){
   RootType = "DrellYan";
 }
 else if(name.Contains("PI_")){
   RootType = "PhotonInduced";
 }
 else if(name.Contains("ttbar") || name.Contains("singletop")){
   RootType = "TopQuark";
 }
 else if(name.Contains("diboson")){
   RootType = "Diboson";
 }
 else if(name.Contains("Triboson")){
   RootType = "Triboson";
 }
 else if(name.Contains("ttV")){
   RootType = "ttV";
 }
 else if(name.Contains("ntuple_MM") || name.Contains("matrix_Data_all_Dimuon")){
   RootType = "Wjets_DD";
 }
 else if(name.Contains("Ztautau")){
   RootType = "Ztautau";
 }
 else if(name.Contains("Wjets_")){
   RootType = "Wjets";
 }

 return RootType;
}

int TreeForPreZPrime::GetYear(TString RootName)
{
 int Year = 0;
 if(RootName.Contains("mc16a")) Year = 1516;
 else if(RootName.Contains("mc16d")) Year = 17;
 else if(RootName.Contains("mc16e")) Year = 18;
 else Year = 0;

 return Year;
}

void TreeForPreZPrime::SetBranch(int ifile)
{
   if(TreeName == "LJAlgo/nominal") isLooseTree = true;
   else if(TreeName == "LJAlgo/nominal_Loose") isLooseTree = true;

   fChain[ifile] = (TTree *)rootfile[ifile]->Get(TreeName);

   fChain[ifile]->SetBranchAddress("DFCommonJets_eventClean_LooseBad", &DFCommonJets_eventClean_LooseBad, &b_DFCommonJets_eventClean_LooseBad);
   fChain[ifile]->SetBranchAddress("jet_ConeTruthLabelID", &jet_ConeTruthLabelID, &b_jet_ConeTruthLabelID);
   fChain[ifile]->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain[ifile]->SetBranchAddress("jet_Jvt", &jet_Jvt, &b_jet_Jvt);
   fChain[ifile]->SetBranchAddress("jet_PartonTruthLabelID", &jet_PartonTruthLabelID, &b_jet_PartonTruthLabelID);
   fChain[ifile]->SetBranchAddress("jet_btag", &jet_btag, &b_jet_btag);
   fChain[ifile]->SetBranchAddress("jet_btag_score", &jet_btag_score, &b_jet_btag_score);
   fChain[ifile]->SetBranchAddress("jet_btag_sf", &jet_btag_sf, &b_jet_btag_sf);
   fChain[ifile]->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain[ifile]->SetBranchAddress("jet_isJvtHS", &jet_isJvtHS, &b_jet_isJvtHS);
   fChain[ifile]->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain[ifile]->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);

   //signal sample
   fChain[ifile]->SetBranchAddress("truth_jet_ConeTruthLabelID", &truth_jet_ConeTruthLabelID, &b_truth_jet_ConeTruthLabelID);
   fChain[ifile]->SetBranchAddress("truth_jet_E", &truth_jet_E, &b_truth_jet_E);
   fChain[ifile]->SetBranchAddress("truth_jet_Jvt", &truth_jet_Jvt, &b_truth_jet_Jvt);
   fChain[ifile]->SetBranchAddress("truth_jet_PartonTruthLabelID", &truth_jet_PartonTruthLabelID, &b_truth_jet_PartonTruthLabelID);
   fChain[ifile]->SetBranchAddress("truth_jet_eta", &truth_jet_eta, &b_truth_jet_eta);
   fChain[ifile]->SetBranchAddress("truth_jet_phi", &truth_jet_phi, &b_truth_jet_phi);
   fChain[ifile]->SetBranchAddress("truth_jet_pt", &truth_jet_pt, &b_truth_jet_pt);

   fChain[ifile]->SetBranchAddress("weight_norm", &weight_norm, &b_weight_norm);
   fChain[ifile]->SetBranchAddress("weight_lumi", &weight_lumi, &b_weight_lumi);
   fChain[ifile]->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain[ifile]->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain[ifile]->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain[ifile]->SetBranchAddress("coreFlags", &coreFlags, &b_coreFlags);
   fChain[ifile]->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain[ifile]->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain[ifile]->SetBranchAddress("actualInteractionsPerCrossing", &actualInteractionsPerCrossing, &b_actualInteractionsPerCrossing);
   fChain[ifile]->SetBranchAddress("averageInteractionsPerCrossing", &averageInteractionsPerCrossing, &b_averageInteractionsPerCrossing);
   fChain[ifile]->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain[ifile]->SetBranchAddress("correctedAverageMu", &correctedAverageMu, &b_correctedAverageMu);
   fChain[ifile]->SetBranchAddress("correctedAndScaledAverageMu", &correctedAndScaledAverageMu, &b_correctedAndScaledAverageMu);
   fChain[ifile]->SetBranchAddress("correctedActualMu", &correctedActualMu, &b_correctedActualMu);
   fChain[ifile]->SetBranchAddress("correctedAndScaledActualMu", &correctedAndScaledActualMu, &b_correctedAndScaledActualMu);

   //signal sample
   fChain[ifile]->SetBranchAddress("weight_pileup_up", &weight_pileup_up, &b_weight_pileup_up);
   fChain[ifile]->SetBranchAddress("weight_pileup_down", &weight_pileup_down, &b_weight_pileup_down);

   fChain[ifile]->SetBranchAddress("beamSpotWeight", &beamSpotWeight, &b_beamSpotWeight);

   //signal sample
   fChain[ifile]->SetBranchAddress("ntruth_jet", &ntruth_jet, &b_ntruth_jet);

   fChain[ifile]->SetBranchAddress("njet", &njet, &b_njet);
   fChain[ifile]->SetBranchAddress("metFinalTrk", &metFinalTrk, &b_metFinalTrk);
   fChain[ifile]->SetBranchAddress("metFinalTrkPx", &metFinalTrkPx, &b_metFinalTrkPx);
   fChain[ifile]->SetBranchAddress("metFinalTrkPy", &metFinalTrkPy, &b_metFinalTrkPy);
   fChain[ifile]->SetBranchAddress("metFinalTrkSumEt", &metFinalTrkSumEt, &b_metFinalTrkSumEt);
   fChain[ifile]->SetBranchAddress("metFinalTrkPhi", &metFinalTrkPhi, &b_metFinalTrkPhi);
   fChain[ifile]->SetBranchAddress("metFinalTrkOverSqrtSumEt", &metFinalTrkOverSqrtSumEt, &b_metFinalTrkOverSqrtSumEt);
   fChain[ifile]->SetBranchAddress("metFinalTrkOverSqrtHt", &metFinalTrkOverSqrtHt, &b_metFinalTrkOverSqrtHt);
   fChain[ifile]->SetBranchAddress("metFinalTrkSignificance", &metFinalTrkSignificance, &b_metFinalTrkSignificance);
   fChain[ifile]->SetBranchAddress("metFinalTrkSigDirectional", &metFinalTrkSigDirectional, &b_metFinalTrkSigDirectional);
   fChain[ifile]->SetBranchAddress("metEle", &metEle, &b_metEle);
   fChain[ifile]->SetBranchAddress("metEleSumEt", &metEleSumEt, &b_metEleSumEt);
   fChain[ifile]->SetBranchAddress("metElePhi", &metElePhi, &b_metElePhi);
   fChain[ifile]->SetBranchAddress("metMuons", &metMuons, &b_metMuons);
   fChain[ifile]->SetBranchAddress("metMuonsSumEt", &metMuonsSumEt, &b_metMuonsSumEt);
   fChain[ifile]->SetBranchAddress("metMuonsPhi", &metMuonsPhi, &b_metMuonsPhi);
   fChain[ifile]->SetBranchAddress("metJet", &metJet, &b_metJet);
   fChain[ifile]->SetBranchAddress("metJetSumEt", &metJetSumEt, &b_metJetSumEt);
   fChain[ifile]->SetBranchAddress("metJetPhi", &metJetPhi, &b_metJetPhi);
   fChain[ifile]->SetBranchAddress("metSoftTrk", &metSoftTrk, &b_metSoftTrk);
   fChain[ifile]->SetBranchAddress("metSoftTrkSumEt", &metSoftTrkSumEt, &b_metSoftTrkSumEt);
   fChain[ifile]->SetBranchAddress("metSoftTrkPhi", &metSoftTrkPhi, &b_metSoftTrkPhi);
   fChain[ifile]->SetBranchAddress("HLT_e120_lhvloose_L1EM22VHI", &HLT_e120_lhvloose_L1EM22VHI, &b_HLT_e120_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e120_lhvloose_L1EM22VHI", &prescale_HLT_e120_lhvloose_L1EM22VHI, &b_prescale_HLT_e120_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e100_lhvloose_L1EM22VHI", &HLT_e100_lhvloose_L1EM22VHI, &b_HLT_e100_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e100_lhvloose_L1EM22VHI", &prescale_HLT_e100_lhvloose_L1EM22VHI, &b_prescale_HLT_e100_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e80_lhvloose_L1EM22VHI", &HLT_e80_lhvloose_L1EM22VHI, &b_HLT_e80_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e80_lhvloose_L1EM22VHI", &prescale_HLT_e80_lhvloose_L1EM22VHI, &b_prescale_HLT_e80_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e60_lhvloose_L1EM22VHI", &HLT_e60_lhvloose_L1EM22VHI, &b_HLT_e60_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e60_lhvloose_L1EM22VHI", &prescale_HLT_e60_lhvloose_L1EM22VHI, &b_prescale_HLT_e60_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e40_lhvloose_L1EM22VHI", &HLT_e40_lhvloose_L1EM22VHI, &b_HLT_e40_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e40_lhvloose_L1EM22VHI", &prescale_HLT_e40_lhvloose_L1EM22VHI, &b_prescale_HLT_e40_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e30_lhvloose_L1EM22VHI", &HLT_e30_lhvloose_L1EM22VHI, &b_HLT_e30_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e30_lhvloose_L1EM22VHI", &prescale_HLT_e30_lhvloose_L1EM22VHI, &b_prescale_HLT_e30_lhvloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e20_lhvloose_L1EM15VH", &HLT_e20_lhvloose_L1EM15VH, &b_HLT_e20_lhvloose_L1EM15VH);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e20_lhvloose_L1EM15VH", &prescale_HLT_e20_lhvloose_L1EM15VH, &b_prescale_HLT_e20_lhvloose_L1EM15VH);
   fChain[ifile]->SetBranchAddress("HLT_e120_lhvloose_L1eEM28M", &HLT_e120_lhvloose_L1eEM28M, &b_HLT_e120_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e120_lhvloose_L1eEM28M", &prescale_HLT_e120_lhvloose_L1eEM28M, &b_prescale_HLT_e120_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("HLT_e100_lhvloose_L1eEM28M", &HLT_e100_lhvloose_L1eEM28M, &b_HLT_e100_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e100_lhvloose_L1eEM28M", &prescale_HLT_e100_lhvloose_L1eEM28M, &b_prescale_HLT_e100_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("HLT_e80_lhvloose_L1eEM28M", &HLT_e80_lhvloose_L1eEM28M, &b_HLT_e80_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e80_lhvloose_L1eEM28M", &prescale_HLT_e80_lhvloose_L1eEM28M, &b_prescale_HLT_e80_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("HLT_e60_lhvloose_L1eEM28M", &HLT_e60_lhvloose_L1eEM28M, &b_HLT_e60_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e60_lhvloose_L1eEM28M", &prescale_HLT_e60_lhvloose_L1eEM28M, &b_prescale_HLT_e60_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("HLT_e40_lhvloose_L1eEM28M", &HLT_e40_lhvloose_L1eEM28M, &b_HLT_e40_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e40_lhvloose_L1eEM28M", &prescale_HLT_e40_lhvloose_L1eEM28M, &b_prescale_HLT_e40_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("HLT_e30_lhvloose_L1eEM28M", &HLT_e30_lhvloose_L1eEM28M, &b_HLT_e30_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e30_lhvloose_L1eEM28M", &prescale_HLT_e30_lhvloose_L1eEM28M, &b_prescale_HLT_e30_lhvloose_L1eEM28M);
   fChain[ifile]->SetBranchAddress("HLT_e20_lhvloose_L1eEM18L", &HLT_e20_lhvloose_L1eEM18L, &b_HLT_e20_lhvloose_L1eEM18L);
   fChain[ifile]->SetBranchAddress("prescale_HLT_e20_lhvloose_L1eEM18L", &prescale_HLT_e20_lhvloose_L1eEM18L, &b_prescale_HLT_e20_lhvloose_L1eEM18L);

   //signal sample
   fChain[ifile]->SetBranchAddress("HLT_mu20_iloose_L1MU15", &HLT_mu20_iloose_L1MU15, &b_HLT_mu20_iloose_L1MU15);
   fChain[ifile]->SetBranchAddress("HLT_mu26_ivarmedium", &HLT_mu26_ivarmedium, &b_HLT_mu26_ivarmedium);
   fChain[ifile]->SetBranchAddress("HLT_mu50", &HLT_mu50, &b_HLT_mu50);
   fChain[ifile]->SetBranchAddress("HLT_mu40", &HLT_mu40, &b_HLT_mu40);
   fChain[ifile]->SetBranchAddress("HLT_mu24_ivarmedium_L1MU14FCH", &HLT_mu24_ivarmedium_L1MU14FCH, &b_HLT_mu24_ivarmedium_L1MU14FCH);
   fChain[ifile]->SetBranchAddress("HLT_mu50_L1MU14FCH", &HLT_mu50_L1MU14FCH, &b_HLT_mu50_L1MU14FCH);
   fChain[ifile]->SetBranchAddress("HLT_2e12_lhloose_L12EM10VH", &HLT_2e12_lhloose_L12EM10VH, &b_HLT_2e12_lhloose_L12EM10VH);
   fChain[ifile]->SetBranchAddress("HLT_2e17_lhvloose_nod0", &HLT_2e17_lhvloose_nod0, &b_HLT_2e17_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("HLT_2e24_lhvloose_nod0", &HLT_2e24_lhvloose_nod0, &b_HLT_2e24_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("HLT_2e24_lhvloose_L12EM20VH", &HLT_2e24_lhvloose_L12EM20VH, &b_HLT_2e24_lhvloose_L12EM20VH);
   fChain[ifile]->SetBranchAddress("HLT_2e24_lhvloose_L12eEM24L", &HLT_2e24_lhvloose_L12eEM24L, &b_HLT_2e24_lhvloose_L12eEM24L);

   fChain[ifile]->SetBranchAddress("HLT_singleLep", &HLT_singleLep, &b_HLT_singleLep);
   fChain[ifile]->SetBranchAddress("HLT_singleJet", &HLT_singleJet, &b_HLT_singleJet);
   fChain[ifile]->SetBranchAddress("randomRunNumber", &randomRunNumber, &b_randomRunNumber);
   fChain[ifile]->SetBranchAddress("datasetNumber", &datasetNumber, &b_datasetNumber);
   fChain[ifile]->SetBranchAddress("year", &year, &b_year);
   fChain[ifile]->SetBranchAddress("mcEventWeight", &mcEventWeight, &b_mcEventWeight);
   fChain[ifile]->SetBranchAddress("sample_xSec", &sample_xSec, &b_sample_xSec);
   fChain[ifile]->SetBranchAddress("sample_xSec_up_rel", &sample_xSec_up_rel, &b_sample_xSec_up_rel);
   fChain[ifile]->SetBranchAddress("sample_xSec_down_rel", &sample_xSec_down_rel, &b_sample_xSec_down_rel);
   fChain[ifile]->SetBranchAddress("sample_kFactor", &sample_kFactor, &b_sample_kFactor);
   fChain[ifile]->SetBranchAddress("sample_filterEff", &sample_filterEff, &b_sample_filterEff);
   fChain[ifile]->SetBranchAddress("weight_gen", &weight_gen, &b_weight_gen);
   fChain[ifile]->SetBranchAddress("weight_lepton", &weight_lepton, &b_weight_lepton);
   fChain[ifile]->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);
   fChain[ifile]->SetBranchAddress("weight_btag", &weight_btag, &b_weight_btag);
   fChain[ifile]->SetBranchAddress("weight_singleleptonTrigSF", &weight_singleleptonTrigSF, &b_weight_singleleptonTrigSF);
   fChain[ifile]->SetBranchAddress("weight_dileptonTrigSF", &weight_dileptonTrigSF, &b_weight_dileptonTrigSF);
   fChain[ifile]->SetBranchAddress("fakeweight", &fakeweight, &b_fakeweight);
   fChain[ifile]->SetBranchAddress("n_truth_el", &n_truth_el, &b_n_truth_el);
   fChain[ifile]->SetBranchAddress("n_truth_mu", &n_truth_mu, &b_n_truth_mu);
   fChain[ifile]->SetBranchAddress("n_truth_lep", &n_truth_lep, &b_n_truth_lep);
   fChain[ifile]->SetBranchAddress("n_el", &n_el, &b_n_el);
   fChain[ifile]->SetBranchAddress("n_mu", &n_mu, &b_n_mu);
   fChain[ifile]->SetBranchAddress("n_lep", &n_lep, &b_n_lep);
   fChain[ifile]->SetBranchAddress("n_signal_el", &n_signal_el, &b_n_signal_el);
   fChain[ifile]->SetBranchAddress("n_signal_mu", &n_signal_mu, &b_n_signal_mu);
   fChain[ifile]->SetBranchAddress("n_signal_lep", &n_signal_lep, &b_n_signal_lep);
   fChain[ifile]->SetBranchAddress("n_bjets_65", &n_bjets_65, &b_n_bjets_65);
   fChain[ifile]->SetBranchAddress("n_bjets_70", &n_bjets_70, &b_n_bjets_70);
   fChain[ifile]->SetBranchAddress("n_bjets_77", &n_bjets_77, &b_n_bjets_77);
   fChain[ifile]->SetBranchAddress("n_bjets_85", &n_bjets_85, &b_n_bjets_85);
   fChain[ifile]->SetBranchAddress("n_bjets_90", &n_bjets_90, &b_n_bjets_90);
   fChain[ifile]->SetBranchAddress("n_bjets", &n_bjets, &b_n_bjets);
   fChain[ifile]->SetBranchAddress("lepton1_isEl", &lepton1_isEl, &b_lepton1_isEl);
   fChain[ifile]->SetBranchAddress("lepton1_m", &lepton1_m, &b_lepton1_m);
   fChain[ifile]->SetBranchAddress("lepton1_E", &lepton1_E, &b_lepton1_E);
   fChain[ifile]->SetBranchAddress("lepton1_pt", &lepton1_pt, &b_lepton1_pt);
   fChain[ifile]->SetBranchAddress("lepton1_phi", &lepton1_phi, &b_lepton1_phi);
   fChain[ifile]->SetBranchAddress("lepton1_eta", &lepton1_eta, &b_lepton1_eta);
   fChain[ifile]->SetBranchAddress("lepton1_caloeta", &lepton1_caloeta, &b_lepton1_caloeta);
   fChain[ifile]->SetBranchAddress("lepton1_charge", &lepton1_charge, &b_lepton1_charge);
   fChain[ifile]->SetBranchAddress("lepton1_truthType", &lepton1_truthType, &b_lepton1_truthType);
   fChain[ifile]->SetBranchAddress("lepton1_truthOrigin", &lepton1_truthOrigin, &b_lepton1_truthOrigin);
   fChain[ifile]->SetBranchAddress("lepton1_IFFType", &lepton1_IFFType, &b_lepton1_IFFType);
   fChain[ifile]->SetBranchAddress("lepton1_isPromptIFF", &lepton1_isPromptIFF, &b_lepton1_isPromptIFF);
   fChain[ifile]->SetBranchAddress("lepton1_isIsoHighPtCaloOnly", &lepton1_isIsoHighPtCaloOnly, &b_lepton1_isIsoHighPtCaloOnly);
   fChain[ifile]->SetBranchAddress("lepton1_isIsoLoose_VarRad", &lepton1_isIsoLoose_VarRad, &b_lepton1_isIsoLoose_VarRad);
   fChain[ifile]->SetBranchAddress("lepton1_isIsoTight_VarRad", &lepton1_isIsoTight_VarRad, &b_lepton1_isIsoTight_VarRad);
   fChain[ifile]->SetBranchAddress("lepton1_isIDLoose", &lepton1_isIDLoose, &b_lepton1_isIDLoose);
   fChain[ifile]->SetBranchAddress("lepton1_isIDMedium", &lepton1_isIDMedium, &b_lepton1_isIDMedium);
   fChain[ifile]->SetBranchAddress("lepton1_isIDTight", &lepton1_isIDTight, &b_lepton1_isIDTight);
   fChain[ifile]->SetBranchAddress("lepton1_RecoWeight", &lepton1_RecoWeight, &b_lepton1_RecoWeight);
   fChain[ifile]->SetBranchAddress("lepton1_IsoHighPtCaloOnlyWeight", &lepton1_IsoHighPtCaloOnlyWeight, &b_lepton1_IsoHighPtCaloOnlyWeight);
   fChain[ifile]->SetBranchAddress("lepton1_IsoLoose_VarRadWeight", &lepton1_IsoLoose_VarRadWeight, &b_lepton1_IsoLoose_VarRadWeight);
   fChain[ifile]->SetBranchAddress("lepton1_IsoTight_VarRadWeight", &lepton1_IsoTight_VarRadWeight, &b_lepton1_IsoTight_VarRadWeight);
   fChain[ifile]->SetBranchAddress("lepton1_IDLooseWeight", &lepton1_IDLooseWeight, &b_lepton1_IDLooseWeight);
   fChain[ifile]->SetBranchAddress("lepton1_IDMediumWeight", &lepton1_IDMediumWeight, &b_lepton1_IDMediumWeight);
   fChain[ifile]->SetBranchAddress("lepton1_IDTightWeight", &lepton1_IDTightWeight, &b_lepton1_IDTightWeight);
   fChain[ifile]->SetBranchAddress("lepton1_ambiguityType", &lepton1_ambiguityType, &b_lepton1_ambiguityType);
   fChain[ifile]->SetBranchAddress("lepton1_addAmbiguity", &lepton1_addAmbiguity, &b_lepton1_addAmbiguity);
   fChain[ifile]->SetBranchAddress("lepton1_d0sig", &lepton1_d0sig, &b_lepton1_d0sig);
   fChain[ifile]->SetBranchAddress("lepton1_z0sinTheta", &lepton1_z0sinTheta, &b_lepton1_z0sinTheta);
   fChain[ifile]->SetBranchAddress("lepton1_d0", &lepton1_d0, &b_lepton1_d0);
   fChain[ifile]->SetBranchAddress("lepton1_z0", &lepton1_z0, &b_lepton1_z0);
   fChain[ifile]->SetBranchAddress("lepton1_isSig", &lepton1_isSig, &b_lepton1_isSig);
   fChain[ifile]->SetBranchAddress("lepton1_isIso", &lepton1_isIso, &b_lepton1_isIso);
   fChain[ifile]->SetBranchAddress("lepton1_isTruthMatched", &lepton1_isTruthMatched, &b_lepton1_isTruthMatched);

   //signal sample
   fChain[ifile]->SetBranchAddress("lepton1_isMatched", &lepton1_isMatched, &b_lepton1_isMatched);

   fChain[ifile]->SetBranchAddress("lepton1_truthE", &lepton1_truthE, &b_lepton1_truthE);
   fChain[ifile]->SetBranchAddress("lepton1_truthpt", &lepton1_truthpt, &b_lepton1_truthpt);
   fChain[ifile]->SetBranchAddress("lepton1_truthphi", &lepton1_truthphi, &b_lepton1_truthphi);
   fChain[ifile]->SetBranchAddress("lepton1_trutheta", &lepton1_trutheta, &b_lepton1_trutheta);
   fChain[ifile]->SetBranchAddress("lepton1_truthpdgid", &lepton1_truthpdgid, &b_lepton1_truthpdgid);
   fChain[ifile]->SetBranchAddress("lepton2_isEl", &lepton2_isEl, &b_lepton2_isEl);
   fChain[ifile]->SetBranchAddress("lepton2_m", &lepton2_m, &b_lepton2_m);
   fChain[ifile]->SetBranchAddress("lepton2_E", &lepton2_E, &b_lepton2_E);
   fChain[ifile]->SetBranchAddress("lepton2_pt", &lepton2_pt, &b_lepton2_pt);
   fChain[ifile]->SetBranchAddress("lepton2_phi", &lepton2_phi, &b_lepton2_phi);
   fChain[ifile]->SetBranchAddress("lepton2_eta", &lepton2_eta, &b_lepton2_eta);
   fChain[ifile]->SetBranchAddress("lepton2_caloeta", &lepton2_caloeta, &b_lepton2_caloeta);
   fChain[ifile]->SetBranchAddress("lepton2_charge", &lepton2_charge, &b_lepton2_charge);
   fChain[ifile]->SetBranchAddress("lepton2_truthType", &lepton2_truthType, &b_lepton2_truthType);
   fChain[ifile]->SetBranchAddress("lepton2_truthOrigin", &lepton2_truthOrigin, &b_lepton2_truthOrigin);
   fChain[ifile]->SetBranchAddress("lepton2_IFFType", &lepton2_IFFType, &b_lepton2_IFFType);
   fChain[ifile]->SetBranchAddress("lepton2_isPromptIFF", &lepton2_isPromptIFF, &b_lepton2_isPromptIFF);
   fChain[ifile]->SetBranchAddress("lepton2_isIsoHighPtCaloOnly", &lepton2_isIsoHighPtCaloOnly, &b_lepton2_isIsoHighPtCaloOnly);
   fChain[ifile]->SetBranchAddress("lepton2_isIsoLoose_VarRad", &lepton2_isIsoLoose_VarRad, &b_lepton2_isIsoLoose_VarRad);
   fChain[ifile]->SetBranchAddress("lepton2_isIsoTight_VarRad", &lepton2_isIsoTight_VarRad, &b_lepton2_isIsoTight_VarRad);
   fChain[ifile]->SetBranchAddress("lepton2_isIDLoose", &lepton2_isIDLoose, &b_lepton2_isIDLoose);
   fChain[ifile]->SetBranchAddress("lepton2_isIDMedium", &lepton2_isIDMedium, &b_lepton2_isIDMedium);
   fChain[ifile]->SetBranchAddress("lepton2_isIDTight", &lepton2_isIDTight, &b_lepton2_isIDTight);
   fChain[ifile]->SetBranchAddress("lepton2_RecoWeight", &lepton2_RecoWeight, &b_lepton2_RecoWeight);
   fChain[ifile]->SetBranchAddress("lepton2_IsoHighPtCaloOnlyWeight", &lepton2_IsoHighPtCaloOnlyWeight, &b_lepton2_IsoHighPtCaloOnlyWeight);
   fChain[ifile]->SetBranchAddress("lepton2_IsoLoose_VarRadWeight", &lepton2_IsoLoose_VarRadWeight, &b_lepton2_IsoLoose_VarRadWeight);
   fChain[ifile]->SetBranchAddress("lepton2_IsoTight_VarRadWeight", &lepton2_IsoTight_VarRadWeight, &b_lepton2_IsoTight_VarRadWeight);
   fChain[ifile]->SetBranchAddress("lepton2_IDLooseWeight", &lepton2_IDLooseWeight, &b_lepton2_IDLooseWeight);
   fChain[ifile]->SetBranchAddress("lepton2_IDMediumWeight", &lepton2_IDMediumWeight, &b_lepton2_IDMediumWeight);
   fChain[ifile]->SetBranchAddress("lepton2_IDTightWeight", &lepton2_IDTightWeight, &b_lepton2_IDTightWeight);
   fChain[ifile]->SetBranchAddress("lepton2_ambiguityType", &lepton2_ambiguityType, &b_lepton2_ambiguityType);
   fChain[ifile]->SetBranchAddress("lepton2_addAmbiguity", &lepton2_addAmbiguity, &b_lepton2_addAmbiguity);
   fChain[ifile]->SetBranchAddress("lepton2_d0sig", &lepton2_d0sig, &b_lepton2_d0sig);
   fChain[ifile]->SetBranchAddress("lepton2_z0sinTheta", &lepton2_z0sinTheta, &b_lepton2_z0sinTheta);
   fChain[ifile]->SetBranchAddress("lepton2_d0", &lepton2_d0, &b_lepton2_d0);
   fChain[ifile]->SetBranchAddress("lepton2_z0", &lepton2_z0, &b_lepton2_z0);
   fChain[ifile]->SetBranchAddress("lepton2_isSig", &lepton2_isSig, &b_lepton2_isSig);
   fChain[ifile]->SetBranchAddress("lepton2_isIso", &lepton2_isIso, &b_lepton2_isIso);
   fChain[ifile]->SetBranchAddress("lepton2_isTruthMatched", &lepton2_isTruthMatched, &b_lepton2_isTruthMatched);

   //signal sample
   fChain[ifile]->SetBranchAddress("lepton2_isMatched", &lepton2_isMatched, &b_lepton2_isMatched);

   fChain[ifile]->SetBranchAddress("lepton2_truthE", &lepton2_truthE, &b_lepton2_truthE);
   fChain[ifile]->SetBranchAddress("lepton2_truthpt", &lepton2_truthpt, &b_lepton2_truthpt);
   fChain[ifile]->SetBranchAddress("lepton2_truthphi", &lepton2_truthphi, &b_lepton2_truthphi);
   fChain[ifile]->SetBranchAddress("lepton2_trutheta", &lepton2_trutheta, &b_lepton2_trutheta);
   fChain[ifile]->SetBranchAddress("lepton2_truthpdgid", &lepton2_truthpdgid, &b_lepton2_truthpdgid);
   fChain[ifile]->SetBranchAddress("lepton_singleleptrigMatched", &lepton_singleleptrigMatched, &b_lepton_singleleptrigMatched);
   fChain[ifile]->SetBranchAddress("lepton_dileptrigMatched", &lepton_dileptrigMatched, &b_lepton_dileptrigMatched);
   fChain[ifile]->SetBranchAddress("jet1_pt", &jet1_pt, &b_jet1_pt);
   fChain[ifile]->SetBranchAddress("jet1_phi", &jet1_phi, &b_jet1_phi);
   fChain[ifile]->SetBranchAddress("jet1_eta", &jet1_eta, &b_jet1_eta);
   fChain[ifile]->SetBranchAddress("jet1_E", &jet1_E, &b_jet1_E);
   fChain[ifile]->SetBranchAddress("jet1_PartonTruthLabelID", &jet1_PartonTruthLabelID, &b_jet1_PartonTruthLabelID);
   fChain[ifile]->SetBranchAddress("jet1_ConeTruthLabelID", &jet1_ConeTruthLabelID, &b_jet1_ConeTruthLabelID);
   fChain[ifile]->SetBranchAddress("jet1_Jvt", &jet1_Jvt, &b_jet1_Jvt);
   fChain[ifile]->SetBranchAddress("jet1_btag_65", &jet1_btag_65, &b_jet1_btag_65);
   fChain[ifile]->SetBranchAddress("jet1_btag_70", &jet1_btag_70, &b_jet1_btag_70);
   fChain[ifile]->SetBranchAddress("jet1_btag_77", &jet1_btag_77, &b_jet1_btag_77);
   fChain[ifile]->SetBranchAddress("jet1_btag_85", &jet1_btag_85, &b_jet1_btag_85);
   fChain[ifile]->SetBranchAddress("jet1_btag_90", &jet1_btag_90, &b_jet1_btag_90);
   fChain[ifile]->SetBranchAddress("jet1_btag", &jet1_btag, &b_jet1_btag);

   //signal sample
   fChain[ifile]->SetBranchAddress("mLepJet", &mLepJet, &b_mLepJet);
   fChain[ifile]->SetBranchAddress("dRLepJet", &dRLepJet, &b_dRLepJet);
   fChain[ifile]->SetBranchAddress("detaLepJet", &detaLepJet, &b_detaLepJet);
   fChain[ifile]->SetBranchAddress("dphiLepJet", &dphiLepJet, &b_dphiLepJet);
   fChain[ifile]->SetBranchAddress("LepOvermLepJet", &LepOvermLepJet, &b_LepOvermLepJet);
   fChain[ifile]->SetBranchAddress("matched_mLepJet", &matched_mLepJet, &b_matched_mLepJet);
   fChain[ifile]->SetBranchAddress("truth_mLepJet", &truth_mLepJet, &b_truth_mLepJet);
   fChain[ifile]->SetBranchAddress("truth_dRLepJet", &truth_dRLepJet, &b_truth_dRLepJet);
   fChain[ifile]->SetBranchAddress("mindphiJetMet", &mindphiJetMet, &b_mindphiJetMet);
   fChain[ifile]->SetBranchAddress("dphiLepMet", &dphiLepMet, &b_dphiLepMet);

   fChain[ifile]->SetBranchAddress("born_lepton1_E", &born_lepton1_E, &b_born_lepton1_E);
   fChain[ifile]->SetBranchAddress("born_lepton1_pt", &born_lepton1_pt, &b_born_lepton1_pt);
   fChain[ifile]->SetBranchAddress("born_lepton1_eta", &born_lepton1_eta, &b_born_lepton1_eta);
   fChain[ifile]->SetBranchAddress("born_lepton1_phi", &born_lepton1_phi, &b_born_lepton1_phi);
   fChain[ifile]->SetBranchAddress("born_lepton1_pdgid", &born_lepton1_pdgid, &b_born_lepton1_pdgid);
   fChain[ifile]->SetBranchAddress("born_lepton2_E", &born_lepton2_E, &b_born_lepton2_E);
   fChain[ifile]->SetBranchAddress("born_lepton2_pt", &born_lepton2_pt, &b_born_lepton2_pt);
   fChain[ifile]->SetBranchAddress("born_lepton2_eta", &born_lepton2_eta, &b_born_lepton2_eta);
   fChain[ifile]->SetBranchAddress("born_lepton2_phi", &born_lepton2_phi, &b_born_lepton2_phi);
   fChain[ifile]->SetBranchAddress("born_lepton2_pdgid", &born_lepton2_pdgid, &b_born_lepton2_pdgid);
   fChain[ifile]->SetBranchAddress("born_dilepton_m", &born_dilepton_m, &b_born_dilepton_m);
   fChain[ifile]->SetBranchAddress("born_dilepton_pt", &born_dilepton_pt, &b_born_dilepton_pt);
   fChain[ifile]->SetBranchAddress("born_dilepton_rapidity", &born_dilepton_rapidity, &b_born_dilepton_rapidity);
   fChain[ifile]->SetBranchAddress("n_born_lepton", &n_born_lepton, &b_n_born_lepton);
   fChain[ifile]->SetBranchAddress("n_truth_boson", &n_truth_boson, &b_n_truth_boson);
   fChain[ifile]->SetBranchAddress("truth_boson_m", &truth_boson_m, &b_truth_boson_m);
   fChain[ifile]->SetBranchAddress("hardscatter_W_m", &hardscatter_W_m, &b_hardscatter_W_m);
   fChain[ifile]->SetBranchAddress("dilepton_m", &dilepton_m, &b_dilepton_m);
   fChain[ifile]->SetBranchAddress("dilepton_pt", &dilepton_pt, &b_dilepton_pt);
   fChain[ifile]->SetBranchAddress("dilepton_phi", &dilepton_phi, &b_dilepton_phi);
   fChain[ifile]->SetBranchAddress("dilepton_eta", &dilepton_eta, &b_dilepton_eta);
   fChain[ifile]->SetBranchAddress("dilepton_DeltaR", &dilepton_DeltaR, &b_dilepton_DeltaR);
   fChain[ifile]->SetBranchAddress("dilepton_DeltaEta", &dilepton_DeltaEta, &b_dilepton_DeltaEta);
   fChain[ifile]->SetBranchAddress("dilepton_DeltaPhi", &dilepton_DeltaPhi, &b_dilepton_DeltaPhi);
   fChain[ifile]->SetBranchAddress("dilepton_CosThetaStar", &dilepton_CosThetaStar, &b_dilepton_CosThetaStar);
   fChain[ifile]->SetBranchAddress("mt_lep1", &mt_lep1, &b_mt_lep1);
   fChain[ifile]->SetBranchAddress("mt_lep2", &mt_lep2, &b_mt_lep2);
   fChain[ifile]->SetBranchAddress("jets_HT", &jets_HT, &b_jets_HT);
   fChain[ifile]->SetBranchAddress("meff", &meff, &b_meff);

   fChain[ifile]->SetBranchAddress("truth_sHat", &truth_sHat, &b_truth_sHat);
   fChain[ifile]->SetBranchAddress("truth_tHat", &truth_tHat, &b_truth_tHat);
   fChain[ifile]->SetBranchAddress("truth_uHat", &truth_uHat, &b_truth_uHat);
   fChain[ifile]->SetBranchAddress("truth_CosThetaCS", &truth_CosThetaCS, &b_truth_CosThetaCS);
   fChain[ifile]->SetBranchAddress("pdf_pdgId1", &pdf_pdgId1, &b_pdf_pdgId1);
   fChain[ifile]->SetBranchAddress("pdf_pdgId2", &pdf_pdgId2, &b_pdf_pdgId2);
   fChain[ifile]->SetBranchAddress("pdf_pdfId1", &pdf_pdfId1, &b_pdf_pdfId1);
   fChain[ifile]->SetBranchAddress("pdf_pdfId2", &pdf_pdfId2, &b_pdf_pdfId2);
   fChain[ifile]->SetBranchAddress("pdf_x1", &pdf_x1, &b_pdf_x1);
   fChain[ifile]->SetBranchAddress("pdf_x2", &pdf_x2, &b_pdf_x2);
   fChain[ifile]->SetBranchAddress("pdf_Q", &pdf_Q, &b_pdf_Q);
   fChain[ifile]->SetBranchAddress("pdf_xf1", &pdf_xf1, &b_pdf_xf1);
   fChain[ifile]->SetBranchAddress("pdf_xf2", &pdf_xf2, &b_pdf_xf2);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();
}

void TreeForPreZPrime::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}

void TreeForPreZPrime::GetTruthEntry(int ifile, long i)
{
 TruthTree[ifile]->GetEntry(i);

}

double TreeForPreZPrime::GetSumOfWeight(int nchannel, int Year)
{
 if(EndFile < RootNames.size()){
   cout<<"ERROR: to calculate the SumOfWeight, all of the files should be included."<<endl;
   return 0;
 }

 double SumOfWeight = 0.0;
 return SumOfWeight;
}

void TreeForPreZPrime::GetPDFAndQCDIndex(int ifile)
{

}

void TreeForPreZPrime::BkgSelection(TString BkgName)
{
 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){

   if((BkgName == "364991") && !((*it).Contains("364991_"))){
     it = RootNames.erase(it);
     SaveName = "364991_MGPy8EG_WZ_CKKWL_lvll_LO_WLZLPol_myOutput.root";
   }
   else if((BkgName == "data18") && !((*it).Contains("data18"))){
     it = RootNames.erase(it);
     SaveName = "data18_myOutput.root";
     isData = true;
   }
   else{
     ++it;
     if(!(SaveName.Contains("root"))) SaveName = "Unknown.root";
   }

 }


 if(BkgName == "345705") SaveName = "345705_Sherpa_222_NNPDF30NNLO_ggllll_0M4l130_myOutput.root";
 else if(BkgName == "data18") SaveName = "data18_myOutput.root";
 else SaveName = "Unknown.root";
}

void TreeForPreZPrime::YearSelection(int Year)
{
 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){
   if((Year == 1516) && !((*it).Contains("MC16a"))){
     it = RootNames.erase(it);
   }
   else{
     ++it;
   }

 }

 if(Year == 1516 || Year == 17 || Year == 18 || Year == 1718){
   if(isData) return;
   SaveName = (int)Year + (TString)"_" + SaveName;
 }
 else{
   if(isData) return;
   SaveName = (TString)"allYears_" + SaveName;
 }

}

void TreeForPreZPrime::InitialSysName()
{

}
