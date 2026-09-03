#define TreeForPreWZPolarization_cxx
#include "WZPolarization/TreeForPreWZPolarization.h"

using namespace std;

TreeForPreWZPolarization::TreeForPreWZPolarization()
{
 Init();
}

TreeForPreWZPolarization::~TreeForPreWZPolarization()
{

}

void TreeForPreWZPolarization::ConfigFile(int NFilePerJob, int iRound)
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

void TreeForPreWZPolarization::ConfigFile(int ifile)
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

void TreeForPreWZPolarization::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForPreWZPolarization::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPreWZPolarization::InputSumOfWeight(map<pair<int, int>, double> SumOfWeightsMap)
{
 this->SumOfWeightsMap = SumOfWeightsMap;
}

void TreeForPreWZPolarization::InputLuminosity(double Lumi1516, double Lumi17, double Lumi18)
{
 this->Lumi1516 = Lumi1516;
 this->Lumi17 = Lumi17;
 this->Lumi18 = Lumi18;
}

int TreeForPreWZPolarization::GetRootType(TString RootName)
{
 int nchannel;

 if(RootName.Contains("364253_")){
   nchannel = 364253;
 }
 else if(RootName.Contains("364991_")){
   nchannel = 364991;
 }
 else if(RootName.Contains("364992_")){
   nchannel = 364992;
 }
 else if(RootName.Contains("364993_")){
   nchannel = 364993;
 }
 else if(RootName.Contains("364994_")){
   nchannel = 364994;
 }
 else if(RootName.Contains("500290_")){
   nchannel = 500290;
 }
 else if(RootName.Contains("500291_")){
   nchannel = 500291;
 }
 else if(RootName.Contains("500292_")){
   nchannel = 500292;
 }
 else if(RootName.Contains("500293_")){
   nchannel = 500293;
 }
 else if(RootName.Contains("500294_")){
   nchannel = 500294;
 }
 else if(RootName.Contains("500295_")){
   nchannel = 500295;
 }
 else if(RootName.Contains("500296_")){
   nchannel = 500296;
 }
 else if(RootName.Contains("500297_")){
   nchannel = 500297;
 }
 else if(RootName.Contains("501793_")){
   nchannel = 501793;
 }
 else if(RootName.Contains("501794_")){
   nchannel = 501794;
 }
 else if(RootName.Contains("501795_")){
   nchannel = 501795;
 }
 else if(RootName.Contains("501796_")){
   nchannel = 501796;
 }
 else if(RootName.Contains("501797_")){
   nchannel = 501797;
 }
 else if(RootName.Contains("501798_")){
   nchannel = 501798;
 }
 else if(RootName.Contains("501799_")){
   nchannel = 501799;
 }
 else if(RootName.Contains("501800_")){
   nchannel = 501800;
 }
 else if(RootName.Contains("507019_")){
   nchannel = 507019;
 }
 else if(RootName.Contains("507020_")){
   nchannel = 507020;
 }
 else if(RootName.Contains("507021_")){
   nchannel = 507021;
 }
 else if(RootName.Contains("507022_")){
   nchannel = 507022;
 }
 else if(RootName.Contains("507023_")){
   nchannel = 507023;
 }
 else if(RootName.Contains("507024_")){
   nchannel = 507024;
 }
 else if(RootName.Contains("507025_")){
   nchannel = 507025;
 }
 else if(RootName.Contains("507026_")){
   nchannel = 507026;
 }
 else if(RootName.Contains("507027_")){
   nchannel = 507027;
 }
 else if(RootName.Contains("507028_")){
   nchannel = 507028;
 }
 else if(RootName.Contains("507029_")){
   nchannel = 507029;
 }
 else if(RootName.Contains("507030_")){
   nchannel = 507030;
 }
 else if(RootName.Contains("507031_")){
   nchannel = 507031;
 }
 else if(RootName.Contains("507032_")){
   nchannel = 507032;
 }
 else if(RootName.Contains("507033_")){
   nchannel = 507033;
 }
 else if(RootName.Contains("507034_")){
   nchannel = 507034;
 }
 else if(RootName.Contains("345705_")){ 
   nchannel = 345705;
 }
 else if(RootName.Contains("345706_")){ 
   nchannel = 345706;
 }
 else if(RootName.Contains("361106_")){ 
   nchannel = 361106;
 }
 else if(RootName.Contains("361107_")){ 
   nchannel = 361107;
 }
 else if(RootName.Contains("361108_")){ 
   nchannel = 361108;
 }
 else if(RootName.Contains("361292_")){ 
   nchannel = 361292;
 }
 else if(RootName.Contains("361293_")){ 
   nchannel = 361293;
 }
 else if(RootName.Contains("361601_")){
   nchannel = 361601;
 }
 else if(RootName.Contains("364242_")){ 
   nchannel = 364242;
 }
 else if(RootName.Contains("364243_")){ 
   nchannel = 364243;
 }
 else if(RootName.Contains("364244_")){ 
   nchannel = 364244;
 }
 else if(RootName.Contains("364245_")){ 
   nchannel = 364245;
 }
 else if(RootName.Contains("364246_")){ 
   nchannel = 364246;
 }
 else if(RootName.Contains("364247_")){ 
   nchannel = 364247;
 }
 else if(RootName.Contains("364248_")){ 
   nchannel = 364248;
 }
 else if(RootName.Contains("364249_")){ 
   nchannel = 364249;
 }
 else if(RootName.Contains("364250_")){ 
   nchannel = 364250;
 }
 else if(RootName.Contains("364254_")){ 
   nchannel = 364254;
 }
 else if(RootName.Contains("364283_")){ 
   nchannel = 364283;
 }
 else if(RootName.Contains("364284_")){ 
   nchannel = 364284;
 }
 else if(RootName.Contains("364739_")){ 
   nchannel = 364739;
 }
 else if(RootName.Contains("364740_")){ 
   nchannel = 364740;
 }
 else if(RootName.Contains("364741_")){ 
   nchannel = 364741;
 }
 else if(RootName.Contains("364742_")){ 
   nchannel = 364742;
 }
 else if(RootName.Contains("366140_")){ 
   nchannel = 366140;
 }
 else if(RootName.Contains("366141_")){ 
   nchannel = 366141;
 }
 else if(RootName.Contains("366142_")){ 
   nchannel = 366142;
 }
 else if(RootName.Contains("366143_")){ 
   nchannel = 366143;
 }
 else if(RootName.Contains("366144_")){ 
   nchannel = 366144;
 }
 else if(RootName.Contains("366145_")){ 
   nchannel = 366145;
 }
 else if(RootName.Contains("366146_")){ 
   nchannel = 366146;
 }
 else if(RootName.Contains("366147_")){ 
   nchannel = 366147;
 }
 else if(RootName.Contains("366148_")){ 
   nchannel = 366148;
 }
 else if(RootName.Contains("366149_")){ 
   nchannel = 366149;
 }
 else if(RootName.Contains("366150_")){ 
   nchannel = 366150;
 }
 else if(RootName.Contains("366151_")){ 
   nchannel = 366151;
 }
 else if(RootName.Contains("366152_")){ 
   nchannel = 366152;
 }
 else if(RootName.Contains("366153_")){ 
   nchannel = 366153;
 }
 else if(RootName.Contains("366154_")){ 
   nchannel = 366154;
 }
 else if(RootName.Contains("410155_")){ 
   nchannel = 410155;
 }
 else if(RootName.Contains("410218_")){ 
   nchannel = 410218;
 }
 else if(RootName.Contains("410219_")){ 
   nchannel = 410219;
 }
 else if(RootName.Contains("410470_")){ 
   nchannel = 410470;
 }
 else if(RootName.Contains("410550_")){ 
   nchannel = 410550;
 }
 else if(RootName.Contains("410644_")){ 
   nchannel = 410644;
 }
 else if(RootName.Contains("410645_")){ 
   nchannel = 410645;
 }
 else if(RootName.Contains("410646_")){ 
   nchannel = 410646;
 }
 else if(RootName.Contains("410647_")){ 
   nchannel = 410647;
 }
 else if(RootName.Contains("410648_")){ 
   nchannel = 410648;
 }
 else if(RootName.Contains("410649_")){ 
   nchannel = 410649;
 }
 else if(RootName.Contains("410658_")){ 
   nchannel = 410658;
 }
 else if(RootName.Contains("410659_")){ 
   nchannel = 410659;
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

int TreeForPreWZPolarization::GetYear(TString RootName)
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

void TreeForPreWZPolarization::SetBranch(int ifile)
{
   fChain[ifile] = (TTree *)rootfile[ifile]->Get("SelectedEvents");

   fChain[ifile]->SetBranchAddress("Systematic", &Systematic, &b_Systematic);
   fChain[ifile]->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain[ifile]->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain[ifile]->SetBranchAddress("OriginRunNumber", &OriginRunNumber, &b_OriginRunNumber);
   fChain[ifile]->SetBranchAddress("ChannelNumber", &ChannelNumber, &b_ChannelNumber);
   fChain[ifile]->SetBranchAddress("AverageMu", &AverageMu, &b_AverageMu);
   fChain[ifile]->SetBranchAddress("MCEventWeight", &MCEventWeight, &b_MCEventWeight);
   fChain[ifile]->SetBranchAddress("MCPileupWeight", &MCPileupWeight, &b_MCPileupWeight);
   fChain[ifile]->SetBranchAddress("JetWeight", &JetWeight, &b_JetWeight);
   fChain[ifile]->SetBranchAddress("KFactor", &KFactor, &b_KFactor);
   fChain[ifile]->SetBranchAddress("VertexWeight", &VertexWeight, &b_VertexWeight);
   fChain[ifile]->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain[ifile]->SetBranchAddress("met_px", &met_px, &b_met_px);
   fChain[ifile]->SetBranchAddress("met_py", &met_py, &b_met_py);
   fChain[ifile]->SetBranchAddress("nSoftMuons", &nSoftMuons, &b_nSoftMuons);
   fChain[ifile]->SetBranchAddress("nSoftElectrons", &nSoftElectrons, &b_nSoftElectrons);
   fChain[ifile]->SetBranchAddress("nSoftJets", &nSoftJets, &b_nSoftJets);
   fChain[ifile]->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain[ifile]->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain[ifile]->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain[ifile]->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain[ifile]->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain[ifile]->SetBranchAddress("el_d0Sig", &el_d0Sig, &b_el_d0Sig);
   fChain[ifile]->SetBranchAddress("el_mediumID", &el_mediumID, &b_el_mediumID);
   fChain[ifile]->SetBranchAddress("el_mediumIDWeight", &el_mediumIDWeight, &b_el_mediumIDWeight);
   fChain[ifile]->SetBranchAddress("el_tightID", &el_tightID, &b_el_tightID);
   fChain[ifile]->SetBranchAddress("el_tightIDWeight", &el_tightIDWeight, &b_el_tightIDWeight);
   fChain[ifile]->SetBranchAddress("el_FCLooseIso", &el_FCLooseIso, &b_el_FCLooseIso);
   fChain[ifile]->SetBranchAddress("el_FCLooseIsoWeight", &el_FCLooseIsoWeight, &b_el_FCLooseIsoWeight);
   fChain[ifile]->SetBranchAddress("el_FCTightIso", &el_FCTightIso, &b_el_FCTightIso);
   fChain[ifile]->SetBranchAddress("el_FCTightIsoWeight", &el_FCTightIsoWeight, &b_el_FCTightIsoWeight);
//   fChain[ifile]->SetBranchAddress("el_FCHighPtIso", &el_FCHighPtIso, &b_el_FCHighPtIso);
//   fChain[ifile]->SetBranchAddress("el_FCHighPtIsoWeight", &el_FCHighPtIsoWeight, &b_el_FCHighPtIsoWeight);
   fChain[ifile]->SetBranchAddress("el_HighPtCaloOnlyIso", &el_HighPtCaloOnlyIso, &b_el_HighPtCaloOnlyIso);
   fChain[ifile]->SetBranchAddress("el_HighPtCaloOnly_MediumID_IsoWeight", &el_HighPtCaloOnly_MediumID_IsoWeight, &b_el_HighPtCaloOnly_MediumID_IsoWeight);
   fChain[ifile]->SetBranchAddress("el_HighPtCaloOnly_TightID_IsoWeight", &el_HighPtCaloOnly_TightID_IsoWeight, &b_el_HighPtCaloOnly_TightID_IsoWeight);
   fChain[ifile]->SetBranchAddress("el_Tight_VarRadIso", &el_Tight_VarRadIso, &b_el_Tight_VarRadIso);
   fChain[ifile]->SetBranchAddress("el_Tight_VarRad_MediumID_IsoWeight", &el_Tight_VarRad_MediumID_IsoWeight, &b_el_Tight_VarRad_MediumID_IsoWeight);
   fChain[ifile]->SetBranchAddress("el_Tight_VarRad_TightID_IsoWeight", &el_Tight_VarRad_TightID_IsoWeight, &b_el_Tight_VarRad_TightID_IsoWeight);
   fChain[ifile]->SetBranchAddress("el_Loose_VarRadIso", &el_Loose_VarRadIso, &b_el_Loose_VarRadIso);
   fChain[ifile]->SetBranchAddress("el_Loose_VarRad_MediumID_IsoWeight", &el_Loose_VarRad_MediumID_IsoWeight, &b_el_Loose_VarRad_MediumID_IsoWeight);
   fChain[ifile]->SetBranchAddress("el_Loose_VarRad_TightID_IsoWeight", &el_Loose_VarRad_TightID_IsoWeight, &b_el_Loose_VarRad_TightID_IsoWeight);
   fChain[ifile]->SetBranchAddress("el_triggerMatched", &el_triggerMatched, &b_el_triggerMatched);
   fChain[ifile]->SetBranchAddress("el_truthMatched", &el_truthMatched, &b_el_truthMatched);
   fChain[ifile]->SetBranchAddress("el_recoWeight", &el_recoWeight, &b_el_recoWeight);
   fChain[ifile]->SetBranchAddress("el_isbaseline", &el_isbaseline, &b_el_isbaseline);
   fChain[ifile]->SetBranchAddress("el_isAmbiguity", &el_isAmbiguity, &b_el_isAmbiguity);
   fChain[ifile]->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain[ifile]->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain[ifile]->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain[ifile]->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain[ifile]->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain[ifile]->SetBranchAddress("mu_d0Sig", &mu_d0Sig, &b_mu_d0Sig);
   fChain[ifile]->SetBranchAddress("mu_mediumID", &mu_mediumID, &b_mu_mediumID);
   fChain[ifile]->SetBranchAddress("mu_mediumIDWeight", &mu_mediumIDWeight, &b_mu_mediumIDWeight);
   fChain[ifile]->SetBranchAddress("mu_tightID", &mu_tightID, &b_mu_tightID);
   fChain[ifile]->SetBranchAddress("mu_tightIDWeight", &mu_tightIDWeight, &b_mu_tightIDWeight);
   fChain[ifile]->SetBranchAddress("mu_FCLooseIso", &mu_FCLooseIso, &b_mu_FCLooseIso);
   fChain[ifile]->SetBranchAddress("mu_FCLooseIsoWeight", &mu_FCLooseIsoWeight, &b_mu_FCLooseIsoWeight);
   fChain[ifile]->SetBranchAddress("mu_FCTightIso", &mu_FCTightIso, &b_mu_FCTightIso);
   fChain[ifile]->SetBranchAddress("mu_FCTightIsoWeight", &mu_FCTightIsoWeight, &b_mu_FCTightIsoWeight);
   fChain[ifile]->SetBranchAddress("mu_PflowLooseIso", &mu_PflowLooseIso, &b_mu_PflowLooseIso);
   fChain[ifile]->SetBranchAddress("mu_PflowLooseIsoWeight", &mu_PflowLooseIsoWeight, &b_mu_PflowLooseIsoWeight);
   fChain[ifile]->SetBranchAddress("mu_PflowTightIso", &mu_PflowTightIso, &b_mu_PflowTightIso);
   fChain[ifile]->SetBranchAddress("mu_PflowTightIsoWeight", &mu_PflowTightIsoWeight, &b_mu_PflowTightIsoWeight);
   fChain[ifile]->SetBranchAddress("mu_triggerMatched", &mu_triggerMatched, &b_mu_triggerMatched);
   fChain[ifile]->SetBranchAddress("mu_truthMatched", &mu_truthMatched, &b_mu_truthMatched);
   fChain[ifile]->SetBranchAddress("mu_IPWeight", &mu_IPWeight, &b_mu_IPWeight);
   fChain[ifile]->SetBranchAddress("mu_isbaseline", &mu_isbaseline, &b_mu_isbaseline);
   fChain[ifile]->SetBranchAddress("jt_e", &jt_e, &b_jt_e);
   fChain[ifile]->SetBranchAddress("jt_eta", &jt_eta, &b_jt_eta);
   fChain[ifile]->SetBranchAddress("jt_phi", &jt_phi, &b_jt_phi);
   fChain[ifile]->SetBranchAddress("jt_pt", &jt_pt, &b_jt_pt);
   fChain[ifile]->SetBranchAddress("jt_passJVT", &jt_passJVT, &b_jt_passJVT);
   fChain[ifile]->SetBranchAddress("jt_passBtag", &jt_passBtag, &b_jt_passBtag);

   if(doPDFAndQCDUnc) fChain[ifile]->SetBranchAddress("MCEventWeights", &MCEventWeights, &b_MCEventWeights);

//   if(doTruthSelection){
     fChain[ifile]->SetBranchAddress("truth_e", &truth_e, &b_truth_e);
     fChain[ifile]->SetBranchAddress("truth_eta", &truth_eta, &b_truth_eta);
     fChain[ifile]->SetBranchAddress("truth_phi", &truth_phi, &b_truth_phi);
     fChain[ifile]->SetBranchAddress("truth_pt", &truth_pt, &b_truth_pt);
     fChain[ifile]->SetBranchAddress("truth_pid", &truth_pid, &b_truth_pid);
     fChain[ifile]->SetBranchAddress("truth_mid", &truth_mid, &b_truth_mid);
//   }

   fChain[ifile]->SetBranchAddress("truthPropagator_px", &truthPropagator_px, &b_truthPropagator_px);
   fChain[ifile]->SetBranchAddress("truthPropagator_py", &truthPropagator_py, &b_truthPropagator_py);
   fChain[ifile]->SetBranchAddress("truthPropagator_pz", &truthPropagator_pz, &b_truthPropagator_pz);
   fChain[ifile]->SetBranchAddress("truthPropagator_e", &truthPropagator_e, &b_truthPropagator_e);
   fChain[ifile]->SetBranchAddress("pdgSequence", &pdgSequence, &b_pdgSequence);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();


   metaTree[ifile] = (TTree *)rootfile[ifile]->Get("metaTree");

   metaTree[ifile]->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   metaTree[ifile]->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   metaTree[ifile]->SetBranchAddress("totalWeightedEntries", &totalWeightedEntries, &b_totalWeightedEntries);
   metaTree[ifile]->SetBranchAddress("crossSection", &crossSection, &b_crossSection);
   metaTree[ifile]->SetBranchAddress("inputFileName", &inputFileName, &b_inputFileName);
   if(doPDFAndQCDUnc) metaTree[ifile]->SetBranchAddress("WeightNames", &WeightNames, &b_WeightNames);

   metaTreeEntries[ifile] = metaTree[ifile]->GetEntries();

   if(doTruthSelection){
     TruthTree[ifile] = (TTree *)rootfile[ifile]->Get("TruthEvents");

     TruthTree[ifile]->SetBranchAddress("EventNumber", &TruthEventNumber, &b_TruthEventNumber);
     TruthTree[ifile]->SetBranchAddress("RunNumber", &TruthRunNumber, &b_TruthRunNumber);
     TruthTree[ifile]->SetBranchAddress("OriginRunNumber", &TruthOriginRunNumber, &b_TruthOriginRunNumber);
     TruthTree[ifile]->SetBranchAddress("ChannelNumber", &TruthChannelNumber, &b_TruthChannelNumber);
     TruthTree[ifile]->SetBranchAddress("AverageMu", &TruthAverageMu, &b_TruthAverageMu);
     TruthTree[ifile]->SetBranchAddress("Year", &TruthYear, &b_TruthYear);
     TruthTree[ifile]->SetBranchAddress("MCEventWeight", &TruthMCEventWeight, &b_TruthMCEventWeight);
     if(doPDFAndQCDUnc) TruthTree[ifile]->SetBranchAddress("MCEventWeights", &TruthMCEventWeights, &b_TruthMCEventWeights);
     TruthTree[ifile]->SetBranchAddress("MCPileupWeight", &TruthMCPileupWeight, &b_TruthMCPileupWeight);
     TruthTree[ifile]->SetBranchAddress("JetWeight", &TruthJetWeight, &b_TruthJetWeight);
     TruthTree[ifile]->SetBranchAddress("KFactor", &TruthKFactor, &b_TruthKFactor);
     TruthTree[ifile]->SetBranchAddress("VertexWeight", &TruthVertexWeight, &b_TruthVertexWeight);
     TruthTree[ifile]->SetBranchAddress("truth_e", &truth_e, &b_truth_e);
     TruthTree[ifile]->SetBranchAddress("truth_eta", &truth_eta, &b_truth_eta);
     TruthTree[ifile]->SetBranchAddress("truth_phi", &truth_phi, &b_truth_phi);
     TruthTree[ifile]->SetBranchAddress("truth_pt", &truth_pt, &b_truth_pt);
     TruthTree[ifile]->SetBranchAddress("truth_pid", &truth_pid, &b_truth_pid);
     TruthTree[ifile]->SetBranchAddress("truth_mid", &truth_mid, &b_truth_mid);

     TruthTreeEntries[ifile] = TruthTree[ifile]->GetEntries();

     TotalEntries[ifile] = TruthTreeEntries[ifile];
   }
}

void TreeForPreWZPolarization::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}

void TreeForPreWZPolarization::GetTruthEntry(int ifile, long i)
{
 TruthTree[ifile]->GetEntry(i);

}

double TreeForPreWZPolarization::GetSumOfWeight(int nchannel, int Year)
{
 if(EndFile < RootNames.size()){
   cout<<"ERROR: to calculate the SumOfWeight, all of the files should be included."<<endl;
   return 0;
 }

 double SumOfWeight = 0.0;
 for(int ifile = 0; ifile < RootNames.size(); ifile++){
   if(nchannel != GetRootType(RootNames.at(ifile))) continue;
   if(Year != GetYear(RootNames.at(ifile))) continue;

   for(long i = 0; i < metaTreeEntries[ifile]; i++){
     metaTree[ifile]->GetEntry(i);
     SumOfWeight = SumOfWeight + totalWeightedEntries;
   }
 }
 return SumOfWeight;
}

void TreeForPreWZPolarization::GetPDFAndQCDIndex(int ifile)
{
 metaTree[ifile]->GetEntry(0);
 for(int iunc = 0; iunc < WeightNames->size(); iunc++){
   TString ErrorType = "";
   if(RootTypes.at(ifile) == 364253){
     TString ErrorName = WeightNames->at(iunc).c_str();
     if(ErrorName.Contains("MUR0.5") || ErrorName.Contains("MUF0.5") || ErrorName.Contains("MUR2") || ErrorName.Contains("MUF2")) ErrorType = "QCD";
     else if(ErrorName.Contains("MUR1_MUF1_PDF261")) ErrorType = "PDF";
     else ErrorType = "";

     pair<int, int> TypeUncPair;
     TypeUncPair = make_pair(RootTypes.at(ifile), iunc);
     TheoryErrorType[TypeUncPair] = ErrorType;
   }
   else if(RootTypes.at(ifile) >= 500000){
     TString ErrorName = WeightNames->at(iunc).c_str();
     if(ErrorName.Contains("MUR0.5") || ErrorName.Contains("MUF0.5") || ErrorName.Contains("MUR2") || ErrorName.Contains("MUF2")) ErrorType = "QCD";
     else if(ErrorName.Contains("MUR1.0_MUF1.0_PDF260")) ErrorType = "PDF";
     else ErrorType = "";

     if(ErrorName.Contains("MUR2.0_MUF0.5") || ErrorName.Contains("MUR0.5_MUF2.0")) ErrorType = "";

     pair<int, int> TypeUncPair;
     TypeUncPair = make_pair(RootTypes.at(ifile), iunc);
     TheoryErrorType[TypeUncPair] = ErrorType;
   }
   cout<<WeightNames->at(iunc)<<endl;
 }

}

void TreeForPreWZPolarization::BkgSelection(TString BkgName)
{
 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){

   if((BkgName == "364991") && !((*it).Contains("364991_"))){
     it = RootNames.erase(it);
     SaveName = "364991_MGPy8EG_WZ_CKKWL_lvll_LO_WLZLPol_myOutput.root";
   }
   else if((BkgName == "364992") && !((*it).Contains("364992_"))){
     it = RootNames.erase(it);
     SaveName = "364992_MGPy8EG_WZ_CKKWL_lvll_LO_WLZTPol_myOutput.root";
   }
   else if((BkgName == "364993") && !((*it).Contains("364993_"))){
     it = RootNames.erase(it);
     SaveName = "364993_MGPy8EG_WZ_CKKWL_lvll_LO_WTZLPol_myOutput.root";
   }
   else if((BkgName == "364994") && !((*it).Contains("364994_"))){
     it = RootNames.erase(it);
     SaveName = "364994_MGPy8EG_WZ_CKKWL_lvll_LO_WTZTPol_myOutput.root";
   }
   else if((BkgName == "500290") && !((*it).Contains("500290_"))){
     it = RootNames.erase(it);
     SaveName = "500290_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "500291") && !((*it).Contains("500291_"))){
     it = RootNames.erase(it);
     SaveName = "500291_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "500292") && !((*it).Contains("500292_"))){
     it = RootNames.erase(it);
     SaveName = "500292_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "500293") && !((*it).Contains("500293_"))){
     it = RootNames.erase(it);
     SaveName = "500293_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "500294") && !((*it).Contains("500294_"))){
     it = RootNames.erase(it);
     SaveName = "500294_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "500295") && !((*it).Contains("500295_"))){
     it = RootNames.erase(it);
     SaveName = "500295_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "500296") && !((*it).Contains("500296_"))){
     it = RootNames.erase(it);
     SaveName = "500296_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "500297") && !((*it).Contains("500297_"))){
     it = RootNames.erase(it);
     SaveName = "500297_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "501793") && !((*it).Contains("501793_"))){
     it = RootNames.erase(it);
     SaveName = "501793_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "501794") && !((*it).Contains("501794_"))){
     it = RootNames.erase(it);
     SaveName = "501794_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "501795") && !((*it).Contains("501795_"))){
     it = RootNames.erase(it);
     SaveName = "501795_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "501796") && !((*it).Contains("501796_"))){
     it = RootNames.erase(it);
     SaveName = "501796_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "501797") && !((*it).Contains("501797_"))){
     it = RootNames.erase(it);
     SaveName = "501797_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "501798") && !((*it).Contains("501798_"))){
     it = RootNames.erase(it);
     SaveName = "501798_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "501799") && !((*it).Contains("501799_"))){
     it = RootNames.erase(it);
     SaveName = "501799_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "501800") && !((*it).Contains("501800_"))){
     it = RootNames.erase(it);
     SaveName = "501800_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507019") && !((*it).Contains("507019_"))){
     it = RootNames.erase(it);
     SaveName = "507019_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507020") && !((*it).Contains("507020_"))){
     it = RootNames.erase(it);
     SaveName = "507020_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507021") && !((*it).Contains("507021_"))){
     it = RootNames.erase(it);
     SaveName = "507021_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507022") && !((*it).Contains("507022_"))){
     it = RootNames.erase(it);
     SaveName = "507022_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507023") && !((*it).Contains("507023_"))){
     it = RootNames.erase(it);
     SaveName = "507023_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507024") && !((*it).Contains("507024_"))){
     it = RootNames.erase(it);
     SaveName = "507024_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507025") && !((*it).Contains("507025_"))){
     it = RootNames.erase(it);
     SaveName = "507025_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507026") && !((*it).Contains("507026_"))){
     it = RootNames.erase(it);
     SaveName = "507026_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507027") && !((*it).Contains("507027_"))){
     it = RootNames.erase(it);
     SaveName = "507027_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507028") && !((*it).Contains("507028_"))){
     it = RootNames.erase(it);
     SaveName = "507028_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507029") && !((*it).Contains("507029_"))){
     it = RootNames.erase(it);
     SaveName = "507029_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507030") && !((*it).Contains("507030_"))){
     it = RootNames.erase(it);
     SaveName = "507030_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507031") && !((*it).Contains("507031_"))){
     it = RootNames.erase(it);
     SaveName = "507031_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507032") && !((*it).Contains("507032_"))){
     it = RootNames.erase(it);
     SaveName = "507032_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "507033") && !((*it).Contains("507033_"))){
     it = RootNames.erase(it);
     SaveName = "507033_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
   }
   else if((BkgName == "507034") && !((*it).Contains("507034_"))){
     it = RootNames.erase(it);
     SaveName = "507034_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
   }
   else if((BkgName == "345705") && !((*it).Contains("345705_"))){
     it = RootNames.erase(it);
     SaveName = "345705_Sherpa_222_NNPDF30NNLO_ggllll_0M4l130_myOutput.root";
   }
   else if((BkgName == "345706") && !((*it).Contains("345706_"))){
     it = RootNames.erase(it);
     SaveName = "345706_Sherpa_222_NNPDF30NNLO_ggllll_130M4l_myOutput.root";
   }
   else if((BkgName == "361106") && !((*it).Contains("361106_"))){
     it = RootNames.erase(it);
     SaveName = "361106_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee_myOutput.root";
   }
   else if((BkgName == "361107") && !((*it).Contains("361107_"))){
     it = RootNames.erase(it);
     SaveName = "361107_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu_myOutput.root";
   }
   else if((BkgName == "361108") && !((*it).Contains("361108_"))){
     it = RootNames.erase(it);
     SaveName = "361108_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau_myOutput.root";
   }
   else if((BkgName == "361292") && !((*it).Contains("361292_"))){
     it = RootNames.erase(it);
     SaveName = "361292_MGaMcAtNloPy8EG_NNPDF30LO_A14NNPDF23LO_WZ_lvll_FxFx_myOutput.root";
   }
   else if((BkgName == "361293") && !((*it).Contains("361293_"))){
     it = RootNames.erase(it);
     SaveName = "361293_MGaMcAtNloPy8EG_NNPDF30LO_A14NNPDF23LO_WZ_lvll_FxFx_myOutput.root";
   }
   else if((BkgName == "361601") && !((*it).Contains("361601_"))){
     it = RootNames.erase(it);
     SaveName = "361601_PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4_myOutput.root";
   }
   else if((BkgName == "364242") && !((*it).Contains("364242_"))){
     it = RootNames.erase(it);
     SaveName = "364242_Sherpa_222_NNPDF30NNLO_WWW_3l3v_EW6_myOutput.root";
   }
   else if((BkgName == "364243") && !((*it).Contains("364243_"))){
     it = RootNames.erase(it);
     SaveName = "364243_Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6_myOutput.root";
   }
   else if((BkgName == "364244") && !((*it).Contains("364244_"))){
     it = RootNames.erase(it);
     SaveName = "364244_Sherpa_222_NNPDF30NNLO_WWZ_2l4v_EW6_myOutput.root";
   }
   else if((BkgName == "364245") && !((*it).Contains("364245_"))){
     it = RootNames.erase(it);
     SaveName = "364245_Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6_myOutput.root";
   }
   else if((BkgName == "364246") && !((*it).Contains("364246_"))){
     it = RootNames.erase(it);
     SaveName = "364246_Sherpa_222_NNPDF30NNLO_WZZ_3l3v_EW6_myOutput.root";
   }
   else if((BkgName == "364247") && !((*it).Contains("364247_"))){
     it = RootNames.erase(it);
     SaveName = "364247_Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6_myOutput.root";
   }
   else if((BkgName == "364248") && !((*it).Contains("364248_"))){
     it = RootNames.erase(it);
     SaveName = "364248_Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6_myOutput.root";
   }
   else if((BkgName == "364249") && !((*it).Contains("364249_"))){
     it = RootNames.erase(it);
     SaveName = "364249_Sherpa_222_NNPDF30NNLO_ZZZ_2l4v_EW6_myOutput.root";
   }
   else if((BkgName == "364250") && !((*it).Contains("364250_"))){
     it = RootNames.erase(it);
     SaveName = "364250_Sherpa_222_NNPDF30NNLO_llll_myOutput.root";
   }
   else if((BkgName == "364253") && !((*it).Contains("364253_"))){
     it = RootNames.erase(it);
     SaveName = "364253_Sherpa_222_NNPDF30NNLO_lllv_myOutput.root";
   }
   else if((BkgName == "364254") && !((*it).Contains("364254_"))){
     it = RootNames.erase(it);
     SaveName = "364254_Sherpa_222_NNPDF30NNLO_llvv_myOutput.root";
   }
   else if((BkgName == "364283") && !((*it).Contains("364283_"))){
     it = RootNames.erase(it);
     SaveName = "364283_Sherpa_222_NNPDF30NNLO_lllljj_EW6_myOutput.root";
   }
   else if((BkgName == "364284") && !((*it).Contains("364284_"))){
     it = RootNames.erase(it);
     SaveName = "364284_Sherpa_222_NNPDF30NNLO_lllvjj_EW6_myOutput.root";
   }
   else if((BkgName == "364739") && !((*it).Contains("364739_"))){
     it = RootNames.erase(it);
     SaveName = "364739_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_OFMinus_myOutput.root";
   }
   else if((BkgName == "364740") && !((*it).Contains("364740_"))){
     it = RootNames.erase(it);
     SaveName = "364740_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_OFPlus_myOutput.root";
   }
   else if((BkgName == "364741") && !((*it).Contains("364741_"))){
     it = RootNames.erase(it);
     SaveName = "364741_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_SFMinus_myOutput.root";
   }
   else if((BkgName == "364742") && !((*it).Contains("364742_"))){
     it = RootNames.erase(it);
     SaveName = "364742_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_SFPlus_myOutput.root";
   }
   else if((BkgName == "366140") && !((*it).Contains("366140_"))){
     it = RootNames.erase(it);
     SaveName = "366140_Sh_224_NN30NNLO_eegamma_LO_pty_7_15_myOutput.root";
   }
   else if((BkgName == "366141") && !((*it).Contains("366141_"))){
     it = RootNames.erase(it);
     SaveName = "366141_Sh_224_NN30NNLO_eegamma_LO_pty_15_35_myOutput.root";
   }
   else if((BkgName == "366142") && !((*it).Contains("366142_"))){
     it = RootNames.erase(it);
     SaveName = "366142_Sh_224_NN30NNLO_eegamma_LO_pty_35_70_myOutput.root";
   }
   else if((BkgName == "366143") && !((*it).Contains("366143_"))){
     it = RootNames.erase(it);
     SaveName = "366143_Sh_224_NN30NNLO_eegamma_LO_pty_70_140_myOutput.root";
   }
   else if((BkgName == "366144") && !((*it).Contains("366144_"))){
     it = RootNames.erase(it);
     SaveName = "366144_Sh_224_NN30NNLO_eegamma_LO_pty_140_E_CMS_myOutput.root";
   }
   else if((BkgName == "366145") && !((*it).Contains("366145_"))){
     it = RootNames.erase(it);
     SaveName = "366145_Sh_224_NN30NNLO_mumugamma_LO_pty_7_15_myOutput.root";
   }
   else if((BkgName == "366146") && !((*it).Contains("366146_"))){
     it = RootNames.erase(it);
     SaveName = "366146_Sh_224_NN30NNLO_mumugamma_LO_pty_15_35_myOutput.root";
   }
   else if((BkgName == "366147") && !((*it).Contains("366147_"))){
     it = RootNames.erase(it);
     SaveName = "366147_Sh_224_NN30NNLO_mumugamma_LO_pty_35_70_myOutput.root";
   }
   else if((BkgName == "366148") && !((*it).Contains("366148_"))){
     it = RootNames.erase(it);
     SaveName = "366148_Sh_224_NN30NNLO_mumugamma_LO_pty_70_140_myOutput.root";
   }
   else if((BkgName == "366149") && !((*it).Contains("366149_"))){
     it = RootNames.erase(it);
     SaveName = "366149_Sh_224_NN30NNLO_mumugamma_LO_pty_140_E_CMS_myOutput.root";
   }
   else if((BkgName == "366150") && !((*it).Contains("366150_"))){
     it = RootNames.erase(it);
     SaveName = "366150_Sh_224_NN30NNLO_tautaugamma_LO_pty_7_15_myOutput.root";
   }
   else if((BkgName == "366151") && !((*it).Contains("366151_"))){
     it = RootNames.erase(it);
     SaveName = "366151_Sh_224_NN30NNLO_tautaugamma_LO_pty_15_35_myOutput.root";
   }
   else if((BkgName == "366152") && !((*it).Contains("366152_"))){
     it = RootNames.erase(it);
     SaveName = "366152_Sh_224_NN30NNLO_tautaugamma_LO_pty_35_70_myOutput.root";
   }
   else if((BkgName == "366153") && !((*it).Contains("366153_"))){
     it = RootNames.erase(it);
     SaveName = "366153_Sh_224_NN30NNLO_tautaugamma_LO_pty_70_140_myOutput.root";
   }
   else if((BkgName == "366154") && !((*it).Contains("366154_"))){
     it = RootNames.erase(it);
     SaveName = "366154_Sh_224_NN30NNLO_tautaugamma_LO_pty_140_E_CMS_myOutput.root";
   }
   else if((BkgName == "410155") && !((*it).Contains("410155_"))){
     it = RootNames.erase(it);
     SaveName = "410155_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW_myOutput.root";
   }
   else if((BkgName == "410218") && !((*it).Contains("410218_"))){
     it = RootNames.erase(it);
     SaveName = "410218_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee_myOutput.root";
   }
   else if((BkgName == "410219") && !((*it).Contains("410219_"))){
     it = RootNames.erase(it);
     SaveName = "410219_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu_myOutput.root";
   }
   else if((BkgName == "410470") && !((*it).Contains("410470_"))){
     it = RootNames.erase(it);
     SaveName = "410470_PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_myOutput.root";
   }
   else if((BkgName == "410550") && !((*it).Contains("410550_"))){
     it = RootNames.erase(it);
     SaveName = "410550_MadGraphPythia8EvtGen_A14_tZ_4fl_tchan_trilepton_myOutput.root";
   }
   else if((BkgName == "410644") && !((*it).Contains("410644_"))){
     it = RootNames.erase(it);
     SaveName = "410644_PowhegPythia8EvtGen_A14_singletop_schan_lept_top_myOutput.root";
   }
   else if((BkgName == "410645") && !((*it).Contains("410645_"))){
     it = RootNames.erase(it);
     SaveName = "410645_PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop_myOutput.root";
   }
   else if((BkgName == "410646") && !((*it).Contains("410646_"))){
     it = RootNames.erase(it);
     SaveName = "410646_PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top_myOutput.root";
   }
   else if((BkgName == "410647") && !((*it).Contains("410647_"))){
     it = RootNames.erase(it);
     SaveName = "410647_PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop_myOutput.root";
   }
   else if((BkgName == "410648") && !((*it).Contains("410648_"))){
     it = RootNames.erase(it);
     SaveName = "410648_PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top_myOutput.root";
   }
   else if((BkgName == "410649") && !((*it).Contains("410649_"))){
     it = RootNames.erase(it);
     SaveName = "410649_PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop_myOutput.root";
   }
   else if((BkgName == "410658") && !((*it).Contains("410658_"))){
     it = RootNames.erase(it);
     SaveName = "410658_PhPy8EG_A14_tchan_BW50_lept_top_myOutput.root";
   }
   else if((BkgName == "410659") && !((*it).Contains("410659_"))){
     it = RootNames.erase(it);
     SaveName = "410659_PhPy8EG_A14_tchan_BW50_lept_antitop_myOutput.root";
   }
//   else if((BkgName == "InclusiveAndPolarized") && !((*it).Contains("364253_") || (*it).Contains("364991_") || (*it).Contains("364992_") || (*it).Contains("364993_") || (*it).Contains("364994_") || (*it).Contains("500290_") || (*it).Contains("500291_") || (*it).Contains("500292_") || (*it).Contains("500293_") || (*it).Contains("500294_") || (*it).Contains("500295_") || (*it).Contains("500296_") || (*it).Contains("500297_") || (*it).Contains("501793_") || (*it).Contains("501794_") || (*it).Contains("501795_") || (*it).Contains("501796_") || (*it).Contains("501797_") || (*it).Contains("501798_") || (*it).Contains("501799_") || (*it).Contains("501800_"))){
   else if((BkgName == "InclusiveAndPolarized") && !((*it).Contains("364253_") || (*it).Contains("500290_") || (*it).Contains("500291_") || (*it).Contains("500292_") || (*it).Contains("500293_") || (*it).Contains("500294_") || (*it).Contains("500295_") || (*it).Contains("500296_") || (*it).Contains("500297_") || (*it).Contains("501793_") || (*it).Contains("501794_") || (*it).Contains("501795_") || (*it).Contains("501796_") || (*it).Contains("501797_") || (*it).Contains("501798_") || (*it).Contains("501799_") || (*it).Contains("501800_"))){
     it = RootNames.erase(it);
     SaveName = "InclusiveAndPolarized.root";
   }
   else if((BkgName == "data1516") && !(((*it).Contains("data15")) || ((*it).Contains("data16")))){
     it = RootNames.erase(it);
     SaveName = "data1516_myOutput.root";
     isData = true;
   }
   else if((BkgName == "data17") && !((*it).Contains("data17"))){
     it = RootNames.erase(it);
     SaveName = "data17_myOutput.root";
     isData = true;
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
 else if(BkgName == "345706") SaveName = "345706_Sherpa_222_NNPDF30NNLO_ggllll_130M4l_myOutput.root";
 else if(BkgName == "361106") SaveName = "361106_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zee_myOutput.root";
 else if(BkgName == "361107") SaveName = "361107_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu_myOutput.root";
 else if(BkgName == "361108") SaveName = "361108_PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau_myOutput.root";
 else if(BkgName == "361292") SaveName = "361292_MGaMcAtNloPy8EG_NNPDF30LO_A14NNPDF23LO_WZ_lvll_FxFx_myOutput.root";
 else if(BkgName == "361293") SaveName = "361293_MGaMcAtNloPy8EG_NNPDF30LO_A14NNPDF23LO_WZ_lvll_FxFx_myOutput.root";
 else if(BkgName == "361601") SaveName = "361601_PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_WZlvll_mll4_myOutput.root";
 else if(BkgName == "364242") SaveName = "364242_Sherpa_222_NNPDF30NNLO_WWW_3l3v_EW6_myOutput.root";
 else if(BkgName == "364243") SaveName = "364243_Sherpa_222_NNPDF30NNLO_WWZ_4l2v_EW6_myOutput.root";
 else if(BkgName == "364244") SaveName = "364244_Sherpa_222_NNPDF30NNLO_WWZ_2l4v_EW6_myOutput.root";
 else if(BkgName == "364245") SaveName = "364245_Sherpa_222_NNPDF30NNLO_WZZ_5l1v_EW6_myOutput.root";
 else if(BkgName == "364246") SaveName = "364246_Sherpa_222_NNPDF30NNLO_WZZ_3l3v_EW6_myOutput.root";
 else if(BkgName == "364247") SaveName = "364247_Sherpa_222_NNPDF30NNLO_ZZZ_6l0v_EW6_myOutput.root";
 else if(BkgName == "364248") SaveName = "364248_Sherpa_222_NNPDF30NNLO_ZZZ_4l2v_EW6_myOutput.root";
 else if(BkgName == "364249") SaveName = "364249_Sherpa_222_NNPDF30NNLO_ZZZ_2l4v_EW6_myOutput.root";
 else if(BkgName == "364250") SaveName = "364250_Sherpa_222_NNPDF30NNLO_llll_myOutput.root";
 else if(BkgName == "364253") SaveName = "364253_Sherpa_222_NNPDF30NNLO_lllv_myOutput.root";
 else if(BkgName == "364254") SaveName = "364254_Sherpa_222_NNPDF30NNLO_llvv_myOutput.root";
 else if(BkgName == "364283") SaveName = "364283_Sherpa_222_NNPDF30NNLO_lllljj_EW6_myOutput.root";
 else if(BkgName == "364284") SaveName = "364284_Sherpa_222_NNPDF30NNLO_lllvjj_EW6_myOutput.root";
 else if(BkgName == "364739") SaveName = "364739_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_OFMinus_myOutput.root";
 else if(BkgName == "364740") SaveName = "364740_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_OFPlus_myOutput.root";
 else if(BkgName == "364741") SaveName = "364741_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_SFMinus_myOutput.root";
 else if(BkgName == "364742") SaveName = "364742_MGPy8EG_NNPDF30NLO_A14NNPDF23LO_lvlljjEW6_SFPlus_myOutput.root";
 else if(BkgName == "366140") SaveName = "366140_Sh_224_NN30NNLO_eegamma_LO_pty_7_15_myOutput.root";
 else if(BkgName == "366141") SaveName = "366141_Sh_224_NN30NNLO_eegamma_LO_pty_15_35_myOutput.root";
 else if(BkgName == "366142") SaveName = "366142_Sh_224_NN30NNLO_eegamma_LO_pty_35_70_myOutput.root";
 else if(BkgName == "366143") SaveName = "366143_Sh_224_NN30NNLO_eegamma_LO_pty_70_140_myOutput.root";
 else if(BkgName == "366144") SaveName = "366144_Sh_224_NN30NNLO_eegamma_LO_pty_140_E_CMS_myOutput.root";
 else if(BkgName == "366145") SaveName = "366145_Sh_224_NN30NNLO_mumugamma_LO_pty_7_15_myOutput.root";
 else if(BkgName == "366146") SaveName = "366146_Sh_224_NN30NNLO_mumugamma_LO_pty_15_35_myOutput.root";
 else if(BkgName == "366147") SaveName = "366147_Sh_224_NN30NNLO_mumugamma_LO_pty_35_70_myOutput.root";
 else if(BkgName == "366148") SaveName = "366148_Sh_224_NN30NNLO_mumugamma_LO_pty_70_140_myOutput.root";
 else if(BkgName == "366149") SaveName = "366149_Sh_224_NN30NNLO_mumugamma_LO_pty_140_E_CMS_myOutput.root";
 else if(BkgName == "366150") SaveName = "366150_Sh_224_NN30NNLO_tautaugamma_LO_pty_7_15_myOutput.root";
 else if(BkgName == "366151") SaveName = "366151_Sh_224_NN30NNLO_tautaugamma_LO_pty_15_35_myOutput.root";
 else if(BkgName == "366152") SaveName = "366152_Sh_224_NN30NNLO_tautaugamma_LO_pty_35_70_myOutput.root";
 else if(BkgName == "366153") SaveName = "366153_Sh_224_NN30NNLO_tautaugamma_LO_pty_70_140_myOutput.root";
 else if(BkgName == "366154") SaveName = "366154_Sh_224_NN30NNLO_tautaugamma_LO_pty_140_E_CMS_myOutput.root";
 else if(BkgName == "410155") SaveName = "410155_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW_myOutput.root";
 else if(BkgName == "410218") SaveName = "410218_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee_myOutput.root";
 else if(BkgName == "410219") SaveName = "410219_aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu_myOutput.root";
 else if(BkgName == "410470") SaveName = "410470_PhPy8EG_A14_ttbar_hdamp258p75_nonallhad_myOutput.root";
 else if(BkgName == "410550") SaveName = "410550_MadGraphPythia8EvtGen_A14_tZ_4fl_tchan_trilepton_myOutput.root";
 else if(BkgName == "410644") SaveName = "410644_PowhegPythia8EvtGen_A14_singletop_schan_lept_top_myOutput.root";
 else if(BkgName == "410645") SaveName = "410645_PowhegPythia8EvtGen_A14_singletop_schan_lept_antitop_myOutput.root";
 else if(BkgName == "410646") SaveName = "410646_PowhegPythia8EvtGen_A14_Wt_DR_inclusive_top_myOutput.root";
 else if(BkgName == "410647") SaveName = "410647_PowhegPythia8EvtGen_A14_Wt_DR_inclusive_antitop_myOutput.root";
 else if(BkgName == "410648") SaveName = "410648_PowhegPythia8EvtGen_A14_Wt_DR_dilepton_top_myOutput.root";
 else if(BkgName == "410649") SaveName = "410649_PowhegPythia8EvtGen_A14_Wt_DR_dilepton_antitop_myOutput.root";
 else if(BkgName == "410658") SaveName = "410658_PhPy8EG_A14_tchan_BW50_lept_top_myOutput.root";
 else if(BkgName == "410659") SaveName = "410659_PhPy8EG_A14_tchan_BW50_lept_antitop_myOutput.root";
 else if(BkgName == "500290") SaveName = "500290_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "500291") SaveName = "500291_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "500292") SaveName = "500292_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "500293") SaveName = "500293_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "500294") SaveName = "500294_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "500295") SaveName = "500295_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "500296") SaveName = "500296_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "500297") SaveName = "500297_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "501793") SaveName = "501793_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "501794") SaveName = "501794_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "501795") SaveName = "501795_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "501796") SaveName = "501796_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "501797") SaveName = "501797_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "501798") SaveName = "501798_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "501799") SaveName = "501799_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "501800") SaveName = "501800_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507019") SaveName = "507019_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "507020") SaveName = "507020_MGPy8EG_W0Z0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507021") SaveName = "507021_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "507022") SaveName = "507022_MGPy8EG_W0ZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507023") SaveName = "507023_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "507024") SaveName = "507024_MGPy8EG_WTZ0_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507025") SaveName = "507025_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZge150GeV_myOutput.root";
 else if(BkgName == "507026") SaveName = "507026_MGPy8EG_WTZT_lvll_lvllj_LO_emu_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507027") SaveName = "507027_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "507028") SaveName = "507028_MGPy8EG_W0Z0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507029") SaveName = "507029_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "507030") SaveName = "507030_MGPy8EG_W0ZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507031") SaveName = "507031_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "507032") SaveName = "507032_MGPy8EG_WTZ0_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "507033") SaveName = "507033_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZge150GeV_myOutput.root";
 else if(BkgName == "507034") SaveName = "507034_MGPy8EG_WTZT_lvll_lvllj_LO_min1tau_PtZlt150GeV_myOutput.root";
 else if(BkgName == "data1516") SaveName = "data1516_myOutput.root";
 else if(BkgName == "data17") SaveName = "data17_myOutput.root";
 else if(BkgName == "data18") SaveName = "data18_myOutput.root";
 else SaveName = "Unknown.root";
}

void TreeForPreWZPolarization::YearSelection(int Year)
{
 for(vector<TString>::iterator it = RootNames.begin(); it != RootNames.end();){
   if((Year == 1516) && !((*it).Contains("MC16a"))){
     it = RootNames.erase(it);
   }
   else if((Year == 17) && !((*it).Contains("MC16d"))){
     it = RootNames.erase(it);
   }
   else if((Year == 18) && !((*it).Contains("MC16e"))){
     it = RootNames.erase(it);
   }
   else if((Year == 1718) && !(((*it).Contains("MC16d")) || ((*it).Contains("MC16e")))){
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

void TreeForPreWZPolarization::InitialSysName()
{
   TFile *rootfile = new TFile(RootNames.at(0));

   TTree *fChain = (TTree *)rootfile->Get("SelectedEvents");

   fChain->SetBranchAddress("Systematic", &Systematic, &b_Systematic);

   set<TString> SysNameSet;
   for(int i = 0; i < 200; i++){
     fChain->GetEntry(i);
     SysNameSignalWZ.push_back((TString)Systematic->c_str());
     SysNameSet.insert((TString)Systematic->c_str());
   }

   for(int i = 0; i < SysNameSet.size(); i++){
     SysNameIndexSignalWZ[SysNameSignalWZ[i]] = i;
   }

   cout<<"using this set of sys names:"<<endl;
   for(int i = 0; i < SysNameSet.size(); i++){
     cout<<"   DefineSysName("<<i<<", \""<<SysNameSignalWZ.at(i)<<"\", ProcessName);"<<endl;
   }
   for(int i = 0; i < SysNameSet.size(); i++){
     cout<<"sysname["<<i<<"]="<<SysNameSignalWZ.at(i)<<endl;
   }

   delete fChain->GetCurrentFile();
}
