#define TreeForPreQBH_cxx
#include "QBH/TreeForPreQBH.h"

using namespace std;

TreeForPreQBH::TreeForPreQBH()
{
 Init();
}

TreeForPreQBH::~TreeForPreQBH()
{

}

void TreeForPreQBH::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));
   SetBranch(i);

   nchannel = GetRootType(RootNames.at(i));
   RootTypes.push_back(nchannel);
   CrossSections.push_back(CrossSection);
   Years.push_back(Year);
   UniqueYears.push_back(UniqueYear);

   if(nchannel == -1) doPDFAndQCDUnc = false;
   if(doPDFAndQCDUnc) GetPDFAndQCDIndex(i);
//   SumOfWeights.push_back(SumOfWeight);
 }

/* if(iRound == 0){
   for(int i = 0; i < RootNames.size(); i++){
     pair<int, int> RootTypePair;
     RootTypePair = make_pair(RootTypes.at(i), 1516);
     SumOfWeightsMap[RootTypePair] = GetSumOfWeight(RootTypes.at(i), 1516);
     RootTypePair = make_pair(RootTypes.at(i), 17);
     SumOfWeightsMap[RootTypePair] = GetSumOfWeight(RootTypes.at(i), 17);
     RootTypePair = make_pair(RootTypes.at(i), 18);
     SumOfWeightsMap[RootTypePair] = GetSumOfWeight(RootTypes.at(i), 18);
   }
 }
*/
 InitialSysName();
}

void TreeForPreQBH::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));
 SetBranch(0);

 nchannel = GetRootType(RootNames.at(ifile));

 RootTypes.clear();
 CrossSections.clear();
 Years.clear();
 UniqueYears.clear();
 SumOfWeightsMap.clear();
// SumOfWeights.clear();

 RootTypes.push_back(nchannel);
 CrossSections.push_back(CrossSection);
 Years.push_back(Year);
 UniqueYears.push_back(UniqueYear);
// SumOfWeights.push_back(SumOfWeight);

// pair<int, int> RootTypePair;
// RootTypePair = make_pair(RootTypes.at(0), Years.at(0));
// SumOfWeightsMap[RootTypePair] = GetSumOfWeight(RootTypes.at(0), Years.at(0));

 if(doPDFAndQCDUnc) GetPDFAndQCDIndex(0);

 cout<<"There is "<<EndFile<<" files."<<endl;
 cout<<RootNames.at(ifile)<<endl;

 InitialSysName();

}

void TreeForPreQBH::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForPreQBH::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPreQBH::InputSumOfWeight(map<pair<int, int>, double> SumOfWeightsMap)
{
 this->SumOfWeightsMap = SumOfWeightsMap;
}

void TreeForPreQBH::InputLuminosity(double Lumi1516, double Lumi17, double Lumi18)
{
 this->Lumi1516 = Lumi1516;
 this->Lumi17 = Lumi17;
 this->Lumi18 = Lumi18;
}

int TreeForPreQBH::GetRootType(TString RootName)
{
 int nchannel;

 if(RootName.Contains("364253_")){
   nchannel = 364253;
 }
 else if(RootName.Contains("data15") || RootName.Contains("data16") || RootName.Contains("data17") || RootName.Contains("data18")){
   nchannel = -1;
 }
 else{
   nchannel = -999;
 }
 this->CrossSection = GetCrossSection(nchannel);
 this->Year = GetYear(RootName);
// this->SumOfWeight = GetSumOfWeight(nchannel);


// This is used for reading the channel number from the branch.
// nchannel = mcChannelNumber;
///////////////////////////////////////////////////////////////

 return nchannel;
}

int TreeForPreQBH::GetYear(TString RootName)
{
 int Year = 0;
 if(RootName.Contains("MC16a") || RootName.Contains("sub30aM") || RootName.Contains("sub55aM") || RootName.Contains("data15") || RootName.Contains("data16")) Year = 1516;
 else if(RootName.Contains("MC16d") || RootName.Contains("sub30dM") || RootName.Contains("sub55dM") || RootName.Contains("data17")) Year = 17;
 else if(RootName.Contains("MC16e") || RootName.Contains("sub30eM") || RootName.Contains("sub55eM") || RootName.Contains("data18")) Year = 18;
 else Year = 0;

 if(RootName.Contains("data15")) UniqueYear = 15;
 else UniqueYear = 0;

 return Year;
}

void TreeForPreQBH::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("LJAlgo/nominal");

   fChain[ifile]->SetBranchAddress("DFCommonJets_eventClean_LooseBad", &DFCommonJets_eventClean_LooseBad, &b_DFCommonJets_eventClean_LooseBad);
   fChain[ifile]->SetBranchAddress("jet_ConeTruthLabelID", &jet_ConeTruthLabelID, &b_jet_ConeTruthLabelID);
   fChain[ifile]->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain[ifile]->SetBranchAddress("jet_Jvt", &jet_Jvt, &b_jet_Jvt);
   fChain[ifile]->SetBranchAddress("jet_PartonTruthLabelID", &jet_PartonTruthLabelID, &b_jet_PartonTruthLabelID);
   fChain[ifile]->SetBranchAddress("jet_btag", &jet_btag, &b_jet_btag);
   fChain[ifile]->SetBranchAddress("jet_btag_sf", &jet_btag_sf, &b_jet_btag_sf);
   fChain[ifile]->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain[ifile]->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain[ifile]->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain[ifile]->SetBranchAddress("truth_el_E", &truth_el_E, &b_truth_el_E);
   fChain[ifile]->SetBranchAddress("truth_el_barcode", &truth_el_barcode, &b_truth_el_barcode);
   fChain[ifile]->SetBranchAddress("truth_el_eta", &truth_el_eta, &b_truth_el_eta);
   fChain[ifile]->SetBranchAddress("truth_el_parentID", &truth_el_parentID, &b_truth_el_parentID);
   fChain[ifile]->SetBranchAddress("truth_el_pdgId", &truth_el_pdgId, &b_truth_el_pdgId);
   fChain[ifile]->SetBranchAddress("truth_el_phi", &truth_el_phi, &b_truth_el_phi);
   fChain[ifile]->SetBranchAddress("truth_el_pt", &truth_el_pt, &b_truth_el_pt);
   fChain[ifile]->SetBranchAddress("truth_el_status", &truth_el_status, &b_truth_el_status);
   fChain[ifile]->SetBranchAddress("truth_el_truthOrigin", &truth_el_truthOrigin, &b_truth_el_truthOrigin);
   fChain[ifile]->SetBranchAddress("truth_el_truthType", &truth_el_truthType, &b_truth_el_truthType);
   fChain[ifile]->SetBranchAddress("truth_jet_ConeTruthLabelID", &truth_jet_ConeTruthLabelID, &b_truth_jet_ConeTruthLabelID);
   fChain[ifile]->SetBranchAddress("truth_jet_E", &truth_jet_E, &b_truth_jet_E);
   fChain[ifile]->SetBranchAddress("truth_jet_Jvt", &truth_jet_Jvt, &b_truth_jet_Jvt);
   fChain[ifile]->SetBranchAddress("truth_jet_PartonTruthLabelID", &truth_jet_PartonTruthLabelID, &b_truth_jet_PartonTruthLabelID);
   fChain[ifile]->SetBranchAddress("truth_jet_eta", &truth_jet_eta, &b_truth_jet_eta);
   fChain[ifile]->SetBranchAddress("truth_jet_phi", &truth_jet_phi, &b_truth_jet_phi);
   fChain[ifile]->SetBranchAddress("truth_jet_pt", &truth_jet_pt, &b_truth_jet_pt);
   fChain[ifile]->SetBranchAddress("truth_muon_E", &truth_muon_E, &b_truth_muon_E);
   fChain[ifile]->SetBranchAddress("truth_muon_barcode", &truth_muon_barcode, &b_truth_muon_barcode);
   fChain[ifile]->SetBranchAddress("truth_muon_eta", &truth_muon_eta, &b_truth_muon_eta);
   fChain[ifile]->SetBranchAddress("truth_muon_parentID", &truth_muon_parentID, &b_truth_muon_parentID);
   fChain[ifile]->SetBranchAddress("truth_muon_pdgId", &truth_muon_pdgId, &b_truth_muon_pdgId);
   fChain[ifile]->SetBranchAddress("truth_muon_phi", &truth_muon_phi, &b_truth_muon_phi);
   fChain[ifile]->SetBranchAddress("truth_muon_pt", &truth_muon_pt, &b_truth_muon_pt);
   fChain[ifile]->SetBranchAddress("truth_muon_status", &truth_muon_status, &b_truth_muon_status);
   fChain[ifile]->SetBranchAddress("truth_muon_truthOrigin", &truth_muon_truthOrigin, &b_truth_muon_truthOrigin);
   fChain[ifile]->SetBranchAddress("truth_muon_truthType", &truth_muon_truthType, &b_truth_muon_truthType);
   fChain[ifile]->SetBranchAddress("weight_norm", &weight_norm, &b_weight_norm);
   fChain[ifile]->SetBranchAddress("weight_lumi", &weight_lumi, &b_weight_lumi);
   fChain[ifile]->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain[ifile]->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain[ifile]->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain[ifile]->SetBranchAddress("coreFlags", &coreFlags, &b_coreFlags);
   fChain[ifile]->SetBranchAddress("bcid", &bcid, &b_bcid);

   if(!isData){
     fChain[ifile]->SetBranchAddress("mcEventNumber", &mcEventNumber, &b_mcEventNumber);
     fChain[ifile]->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   }

   fChain[ifile]->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain[ifile]->SetBranchAddress("actualInteractionsPerCrossing", &actualInteractionsPerCrossing, &b_actualInteractionsPerCrossing);
   fChain[ifile]->SetBranchAddress("averageInteractionsPerCrossing", &averageInteractionsPerCrossing, &b_averageInteractionsPerCrossing);
   fChain[ifile]->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain[ifile]->SetBranchAddress("correctedAverageMu", &correctedAverageMu, &b_correctedAverageMu);
   fChain[ifile]->SetBranchAddress("correctedAndScaledAverageMu", &correctedAndScaledAverageMu, &b_correctedAndScaledAverageMu);
   fChain[ifile]->SetBranchAddress("correctedActualMu", &correctedActualMu, &b_correctedActualMu);
   fChain[ifile]->SetBranchAddress("correctedAndScaledActualMu", &correctedAndScaledActualMu, &b_correctedAndScaledActualMu);
   fChain[ifile]->SetBranchAddress("weight_pileup_up", &weight_pileup_up, &b_weight_pileup_up);
   fChain[ifile]->SetBranchAddress("weight_pileup_down", &weight_pileup_down, &b_weight_pileup_down);

   if(!isData){
     fChain[ifile]->SetBranchAddress("rand_run_nr", &rand_run_nr, &b_rand_run_nr);
     fChain[ifile]->SetBranchAddress("rand_lumiblock_nr", &rand_lumiblock_nr, &b_rand_lumiblock_nr);
   }

   fChain[ifile]->SetBranchAddress("beamSpotWeight", &beamSpotWeight, &b_beamSpotWeight);
   fChain[ifile]->SetBranchAddress("passL1", &passL1, &b_passL1);
   fChain[ifile]->SetBranchAddress("passHLT", &passHLT, &b_passHLT);
   fChain[ifile]->SetBranchAddress("ntruth_muon", &ntruth_muon, &b_ntruth_muon);
   fChain[ifile]->SetBranchAddress("ntruth_el", &ntruth_el, &b_ntruth_el);
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
   fChain[ifile]->SetBranchAddress("HLT_j360", &HLT_j360, &b_HLT_j360);
   fChain[ifile]->SetBranchAddress("HLT_j380", &HLT_j380, &b_HLT_j380);
   fChain[ifile]->SetBranchAddress("HLT_j420", &HLT_j420, &b_HLT_j420);
   fChain[ifile]->SetBranchAddress("HLT_j420_pf_ftf_preselj225_L1J100", &HLT_j420_pf_ftf_preselj225_L1J100, &b_HLT_j420_pf_ftf_preselj225_L1J100);
   fChain[ifile]->SetBranchAddress("HLT_e24_lhmedium_L1EM20VH", &HLT_e24_lhmedium_L1EM20VH, &b_HLT_e24_lhmedium_L1EM20VH);
   fChain[ifile]->SetBranchAddress("HLT_e60_lhmedium", &HLT_e60_lhmedium, &b_HLT_e60_lhmedium);
   fChain[ifile]->SetBranchAddress("HLT_e120_lhloose", &HLT_e120_lhloose, &b_HLT_e120_lhloose);
   fChain[ifile]->SetBranchAddress("HLT_e26_lhtight_nod0_ivarloose", &HLT_e26_lhtight_nod0_ivarloose, &b_HLT_e26_lhtight_nod0_ivarloose);
   fChain[ifile]->SetBranchAddress("HLT_e60_lhmedium_nod0", &HLT_e60_lhmedium_nod0, &b_HLT_e60_lhmedium_nod0);
   fChain[ifile]->SetBranchAddress("HLT_e140_lhloose_nod0", &HLT_e140_lhloose_nod0, &b_HLT_e140_lhloose_nod0);
   fChain[ifile]->SetBranchAddress("HLT_e26_lhtight_ivarloose_L1EM22VHI", &HLT_e26_lhtight_ivarloose_L1EM22VHI, &b_HLT_e26_lhtight_ivarloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e26_lhtight_ivarloose_L1eEM26M", &HLT_e26_lhtight_ivarloose_L1eEM26M, &b_HLT_e26_lhtight_ivarloose_L1eEM26M);
   fChain[ifile]->SetBranchAddress("HLT_e60_lhmedium_L1EM22VHI", &HLT_e60_lhmedium_L1EM22VHI, &b_HLT_e60_lhmedium_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e60_lhmedium_L1eEM26M", &HLT_e60_lhmedium_L1eEM26M, &b_HLT_e60_lhmedium_L1eEM26M);
   fChain[ifile]->SetBranchAddress("HLT_e140_lhloose_L1EM22VHI", &HLT_e140_lhloose_L1EM22VHI, &b_HLT_e140_lhloose_L1EM22VHI);
   fChain[ifile]->SetBranchAddress("HLT_e140_lhloose_L1eEM26M", &HLT_e140_lhloose_L1eEM26M, &b_HLT_e140_lhloose_L1eEM26M);
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
   fChain[ifile]->SetBranchAddress("n_bjets", &n_bjets, &b_n_bjets);
   fChain[ifile]->SetBranchAddress("lepton1_isEl", &lepton1_isEl, &b_lepton1_isEl);
   fChain[ifile]->SetBranchAddress("lepton1_m", &lepton1_m, &b_lepton1_m);
   fChain[ifile]->SetBranchAddress("lepton1_E", &lepton1_E, &b_lepton1_E);
   fChain[ifile]->SetBranchAddress("lepton1_pt", &lepton1_pt, &b_lepton1_pt);
   fChain[ifile]->SetBranchAddress("lepton1_phi", &lepton1_phi, &b_lepton1_phi);
   fChain[ifile]->SetBranchAddress("lepton1_eta", &lepton1_eta, &b_lepton1_eta);
   fChain[ifile]->SetBranchAddress("lepton1_charge", &lepton1_charge, &b_lepton1_charge);
   fChain[ifile]->SetBranchAddress("lepton1_truthType", &lepton1_truthType, &b_lepton1_truthType);
   fChain[ifile]->SetBranchAddress("lepton1_truthOrigin", &lepton1_truthOrigin, &b_lepton1_truthOrigin);
   fChain[ifile]->SetBranchAddress("lepton1_IFFType", &lepton1_IFFType, &b_lepton1_IFFType);
   fChain[ifile]->SetBranchAddress("lepton1_isPromptIFF", &lepton1_isPromptIFF, &b_lepton1_isPromptIFF);
   fChain[ifile]->SetBranchAddress("lepton1_d0sig", &lepton1_d0sig, &b_lepton1_d0sig);
   fChain[ifile]->SetBranchAddress("lepton1_z0sinTheta", &lepton1_z0sinTheta, &b_lepton1_z0sinTheta);
   fChain[ifile]->SetBranchAddress("lepton1_d0", &lepton1_d0, &b_lepton1_d0);
   fChain[ifile]->SetBranchAddress("lepton1_z0", &lepton1_z0, &b_lepton1_z0);
   fChain[ifile]->SetBranchAddress("lepton1_isSig", &lepton1_isSig, &b_lepton1_isSig);
   fChain[ifile]->SetBranchAddress("lepton1_isIso", &lepton1_isIso, &b_lepton1_isIso);
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
   fChain[ifile]->SetBranchAddress("lepton2_charge", &lepton2_charge, &b_lepton2_charge);
   fChain[ifile]->SetBranchAddress("lepton2_truthType", &lepton2_truthType, &b_lepton2_truthType);
   fChain[ifile]->SetBranchAddress("lepton2_truthOrigin", &lepton2_truthOrigin, &b_lepton2_truthOrigin);
   fChain[ifile]->SetBranchAddress("lepton2_IFFType", &lepton2_IFFType, &b_lepton2_IFFType);
   fChain[ifile]->SetBranchAddress("lepton2_isPromptIFF", &lepton2_isPromptIFF, &b_lepton2_isPromptIFF);
   fChain[ifile]->SetBranchAddress("lepton2_d0sig", &lepton2_d0sig, &b_lepton2_d0sig);
   fChain[ifile]->SetBranchAddress("lepton2_z0sinTheta", &lepton2_z0sinTheta, &b_lepton2_z0sinTheta);
   fChain[ifile]->SetBranchAddress("lepton2_d0", &lepton2_d0, &b_lepton2_d0);
   fChain[ifile]->SetBranchAddress("lepton2_z0", &lepton2_z0, &b_lepton2_z0);
   fChain[ifile]->SetBranchAddress("lepton2_isSig", &lepton2_isSig, &b_lepton2_isSig);
   fChain[ifile]->SetBranchAddress("lepton2_isIso", &lepton2_isIso, &b_lepton2_isIso);
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
   fChain[ifile]->SetBranchAddress("jet1_btag_DL1dv01_FixedCutBEff_77", &jet1_btag_DL1dv01_FixedCutBEff_77, &b_jet1_btag_DL1dv01_FixedCutBEff_77);
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

   TotalEntries[ifile] = fChain[ifile]->GetEntries();
}

void TreeForPreQBH::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}

void TreeForPreQBH::GetTruthEntry(int ifile, long i)
{
 TruthTree[ifile]->GetEntry(i);

}

double TreeForPreQBH::GetSumOfWeight(int nchannel, int Year)
{
 if(EndFile < RootNames.size()){
   cout<<"ERROR: to calculate the SumOfWeight, all of the files should be included."<<endl;
   return 0;
 }

 double SumOfWeight = 0.0;
 return SumOfWeight;
}

void TreeForPreQBH::GetPDFAndQCDIndex(int ifile)
{

}

void TreeForPreQBH::BkgSelection(TString BkgName)
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

void TreeForPreQBH::YearSelection(int Year)
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

void TreeForPreQBH::InitialSysName()
{

}
