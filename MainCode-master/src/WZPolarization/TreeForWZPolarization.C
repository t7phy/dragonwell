#define TreeForWZPolarization_cxx
#include "WZPolarization/TreeForWZPolarization.h"

using namespace std;

void TreeForWZPolarization::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   PDFWeights = 0;
   QCDWeights = 0;
}

TreeForWZPolarization::TreeForWZPolarization()
{
 Init();
}

TreeForWZPolarization::~TreeForWZPolarization()
{

}

void TreeForWZPolarization::ConfigFile(int NFilePerJob, int iRound)
{
 FirstFile = iRound * NFilePerJob;
 EndFile = (iRound + 1) * NFilePerJob;

 if(EndFile >= RootNames.size()) EndFile = RootNames.size();

 for(int i = FirstFile; i < EndFile; i++){
   rootfile[i] = new TFile(RootNames.at(i));

   nchannel = GetRootType(RootNames.at(i));
   RootTypes.push_back(nchannel);

   SetBranch(i);

//   CrossSections.push_back(CrossSection);
//   SumOfWeights.push_back(SumOfWeight);
 }
}

void TreeForWZPolarization::ConfigFile(int ifile)
{
 OneFilePerJob = true;
 FirstFile = 0;
 EndFile = 1;

 rootfile[0] = new TFile(RootNames.at(ifile));

 nchannel = GetRootType(RootNames.at(ifile));

 RootTypes.clear();
// CrossSections.clear();
// SumOfWeights.clear();

 RootTypes.push_back(nchannel);

 SetBranch(0);

// CrossSections.push_back(CrossSection);
// SumOfWeights.push_back(SumOfWeight);
}

void TreeForWZPolarization::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForWZPolarization::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;
}

void TreeForWZPolarization::LinkHist(HistsWZPolarization* myhists)
{
 this->fHist = myhists;
 this->SysNameIndex = fHist->SysNameIndexSignalWZ;
 this->SystematicName = fHist->SystematicName;
}

int TreeForWZPolarization::GetRootType(TString RootName)
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
 else if(RootName.Contains("data1516") || RootName.Contains("data15") || RootName.Contains("data16") || RootName.Contains("data17") || RootName.Contains("data18") || RootName.Contains("Pseudodata_")){
   nchannel = -1;
 }
 else{
   nchannel = -999;
 }

// this->CrossSection = GetCrossSection(nchannel);
// this->SumOfWeight = GetSumOfWeight(nchannel);

 return nchannel;
}

void TreeForWZPolarization::SetBranch(int ifile)
{
   ////////////////////////////////////////////////////////////////
   //  Give a SystematicName, only one tree will be initialized  //
   //  The SystematicName must be defined in the SysNameIndex    //
   //  Except the systematic relative to the fake background     //
   //  (eg: FakeBkg_MetCut_1up)                                  //
   //  (In this case, the nominal tree will be initialized)      //
   ////////////////////////////////////////////////////////////////

   SavedSystematicName = SystematicName;
   if(SystematicName.Contains("FakeBkg")) SavedSystematicName = "nominal";

   if(RootTypes.at(ifile) == -1 && SavedSystematicName != "nominal"){ 
     cout<<"INFO: move to the nominal tree for data."<<endl;
     SavedSystematicName = "nominal";
   }

   map<TString, int>::iterator sysIter;
   for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
     int isys = sysIter->second;

     if(SystematicName == ""){
       if(fHist->OnlyNominal && isys != 0) continue;
     }
     else{
       if(sysIter->first != SavedSystematicName) continue;
     }

     fChain[ifile][isys] = (TTree *)rootfile[ifile]->Get(sysIter->first);

     fChain[ifile][isys]->SetBranchAddress("Flavor", &Flavor, &b_Flavor);
     fChain[ifile][isys]->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
     fChain[ifile][isys]->SetBranchAddress("Yields", &Yields, &b_Yields);
     fChain[ifile][isys]->SetBranchAddress("isMC", &isMC, &b_isMC);
     fChain[ifile][isys]->SetBranchAddress("Channel", &Channel, &b_Channel);
     fChain[ifile][isys]->SetBranchAddress("Year", &Year, &b_Year);
     fChain[ifile][isys]->SetBranchAddress("NormSF", &NormSF, &b_NormSF);
     fChain[ifile][isys]->SetBranchAddress("WeightSign", &WeightSign, &b_WeightSign);
     fChain[ifile][isys]->SetBranchAddress("WeightNormalized", &WeightNormalized, &b_WeightNormalized);
     fChain[ifile][isys]->SetBranchAddress("Weight", &Weight, &b_Weight);
     fChain[ifile][isys]->SetBranchAddress("TotalWeight", &TotalWeight, &b_TotalWeight);
     fChain[ifile][isys]->SetBranchAddress("WeightNormalizedNoKFactor", &WeightNormalizedNoKFactor, &b_WeightNormalizedNoKFactor);
     fChain[ifile][isys]->SetBranchAddress("WeightNoKFactor", &WeightNoKFactor, &b_WeightNoKFactor);
     fChain[ifile][isys]->SetBranchAddress("TotalWeightNoKFactor", &TotalWeightNoKFactor, &b_TotalWeightNoKFactor);
     fChain[ifile][isys]->SetBranchAddress("M_WZ", &M_WZ, &b_M_WZ);
     fChain[ifile][isys]->SetBranchAddress("M_3l", &M_3l, &b_M_3l);
     fChain[ifile][isys]->SetBranchAddress("Mt_WZ", &Mt_WZ, &b_Mt_WZ);
     fChain[ifile][isys]->SetBranchAddress("M_Z", &M_Z, &b_M_Z);
     fChain[ifile][isys]->SetBranchAddress("Mt_W", &Mt_W, &b_Mt_W);
     fChain[ifile][isys]->SetBranchAddress("Met", &Met, &b_Met);
     fChain[ifile][isys]->SetBranchAddress("Njets", &Njets, &b_Njets);
     fChain[ifile][isys]->SetBranchAddress("NBjets", &NBjets, &b_NBjets);
     fChain[ifile][isys]->SetBranchAddress("SumOfWeight", &SumOfWeight, &b_SumOfWeight);
     fChain[ifile][isys]->SetBranchAddress("Luminosity", &Luminosity, &b_Luminosity);
     fChain[ifile][isys]->SetBranchAddress("CrossSection", &CrossSection, &b_CrossSection);
     fChain[ifile][isys]->SetBranchAddress("Lep1Pt", &Lep1Pt, &b_Lep1Pt);
     fChain[ifile][isys]->SetBranchAddress("Lep2Pt", &Lep2Pt, &b_Lep2Pt);
     fChain[ifile][isys]->SetBranchAddress("Lep3Pt", &Lep3Pt, &b_Lep3Pt);
     fChain[ifile][isys]->SetBranchAddress("Lep1Eta", &Lep1Eta, &b_Lep1Eta);
     fChain[ifile][isys]->SetBranchAddress("Lep2Eta", &Lep2Eta, &b_Lep2Eta);
     fChain[ifile][isys]->SetBranchAddress("Lep3Eta", &Lep3Eta, &b_Lep3Eta);
     fChain[ifile][isys]->SetBranchAddress("Lep1Phi", &Lep1Phi, &b_Lep1Phi);
     fChain[ifile][isys]->SetBranchAddress("Lep2Phi", &Lep2Phi, &b_Lep2Phi);
     fChain[ifile][isys]->SetBranchAddress("Lep3Phi", &Lep3Phi, &b_Lep3Phi);
     fChain[ifile][isys]->SetBranchAddress("Lep1Flavor", &Lep1Flavor, &b_Lep1Flavor);
     fChain[ifile][isys]->SetBranchAddress("Lep2Flavor", &Lep2Flavor, &b_Lep2Flavor);
     fChain[ifile][isys]->SetBranchAddress("Lep3Flavor", &Lep3Flavor, &b_Lep3Flavor);
     fChain[ifile][isys]->SetBranchAddress("Lep1Charge", &Lep1Charge, &b_Lep1Charge);
     fChain[ifile][isys]->SetBranchAddress("Lep2Charge", &Lep2Charge, &b_Lep2Charge);
     fChain[ifile][isys]->SetBranchAddress("Lep3Charge", &Lep3Charge, &b_Lep3Charge);
     fChain[ifile][isys]->SetBranchAddress("Lep1Ambiguity", &Lep1Ambiguity, &b_Lep1Ambiguity);
     fChain[ifile][isys]->SetBranchAddress("Lep2Ambiguity", &Lep2Ambiguity, &b_Lep2Ambiguity);
     fChain[ifile][isys]->SetBranchAddress("Lep3Ambiguity", &Lep3Ambiguity, &b_Lep3Ambiguity);
     fChain[ifile][isys]->SetBranchAddress("TruthLep1Pt", &TruthLep1Pt, &b_TruthLep1Pt);
     fChain[ifile][isys]->SetBranchAddress("TruthLep2Pt", &TruthLep2Pt, &b_TruthLep2Pt);
     fChain[ifile][isys]->SetBranchAddress("TruthLep3Pt", &TruthLep3Pt, &b_TruthLep3Pt);
     fChain[ifile][isys]->SetBranchAddress("TruthLep1Eta", &TruthLep1Eta, &b_TruthLep1Eta);
     fChain[ifile][isys]->SetBranchAddress("TruthLep2Eta", &TruthLep2Eta, &b_TruthLep2Eta);
     fChain[ifile][isys]->SetBranchAddress("TruthLep3Eta", &TruthLep3Eta, &b_TruthLep3Eta);
     fChain[ifile][isys]->SetBranchAddress("TruthLep1Phi", &TruthLep1Phi, &b_TruthLep1Phi);
     fChain[ifile][isys]->SetBranchAddress("TruthLep2Phi", &TruthLep2Phi, &b_TruthLep2Phi);
     fChain[ifile][isys]->SetBranchAddress("TruthLep3Phi", &TruthLep3Phi, &b_TruthLep3Phi);
     fChain[ifile][isys]->SetBranchAddress("TruthLep1Flavor", &TruthLep1Flavor, &b_TruthLep1Flavor);
     fChain[ifile][isys]->SetBranchAddress("TruthLep2Flavor", &TruthLep2Flavor, &b_TruthLep2Flavor);
     fChain[ifile][isys]->SetBranchAddress("TruthLep3Flavor", &TruthLep3Flavor, &b_TruthLep3Flavor);
     fChain[ifile][isys]->SetBranchAddress("Mpx", &Mpx, &b_Mpx);
     fChain[ifile][isys]->SetBranchAddress("Mpy", &Mpy, &b_Mpy);
     fChain[ifile][isys]->SetBranchAddress("Mpz", &Mpz, &b_Mpz);
     fChain[ifile][isys]->SetBranchAddress("LWTNNNuPz", &LWTNNNuPz, &b_LWTNNNuPz);
     fChain[ifile][isys]->SetBranchAddress("TruthNuPz", &TruthNuPz, &b_TruthNuPz);
     fChain[ifile][isys]->SetBranchAddress("LWTNNpLL", &LWTNNpLL, &b_LWTNNpLL);
     fChain[ifile][isys]->SetBranchAddress("LWTNNpLT", &LWTNNpLT, &b_LWTNNpLT);
     fChain[ifile][isys]->SetBranchAddress("LWTNNpTL", &LWTNNpTL, &b_LWTNNpTL);
     fChain[ifile][isys]->SetBranchAddress("LWTNNpTT", &LWTNNpTT, &b_LWTNNpTT);
     fChain[ifile][isys]->SetBranchAddress("LLNLOWeight", &LLNLOWeight, &b_LLNLOWeight);
     fChain[ifile][isys]->SetBranchAddress("LTNLOWeight", &LTNLOWeight, &b_LTNLOWeight);
     fChain[ifile][isys]->SetBranchAddress("TLNLOWeight", &TLNLOWeight, &b_TLNLOWeight);
     fChain[ifile][isys]->SetBranchAddress("TTNLOWeight", &TTNLOWeight, &b_TTNLOWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep1WeightZ", &Lep1WeightZ, &b_Lep1WeightZ);
     fChain[ifile][isys]->SetBranchAddress("Lep2WeightZ", &Lep2WeightZ, &b_Lep2WeightZ);
     fChain[ifile][isys]->SetBranchAddress("Lep3WeightZ", &Lep3WeightZ, &b_Lep3WeightZ);
     fChain[ifile][isys]->SetBranchAddress("Lep1WeightW", &Lep1WeightW, &b_Lep1WeightW);
     fChain[ifile][isys]->SetBranchAddress("Lep2WeightW", &Lep2WeightW, &b_Lep2WeightW);
     fChain[ifile][isys]->SetBranchAddress("Lep3WeightW", &Lep3WeightW, &b_Lep3WeightW);
     fChain[ifile][isys]->SetBranchAddress("Pt_W", &Pt_W, &b_Pt_W);
     fChain[ifile][isys]->SetBranchAddress("Pt_Z", &Pt_Z, &b_Pt_Z);
     fChain[ifile][isys]->SetBranchAddress("Pt_WZ", &Pt_WZ, &b_Pt_WZ);
     fChain[ifile][isys]->SetBranchAddress("SumJetPt", &SumJetPt, &b_SumJetPt);
     fChain[ifile][isys]->SetBranchAddress("CosThetaV", &CosThetaV, &b_CosThetaV);
     fChain[ifile][isys]->SetBranchAddress("CosThetaLepW", &CosThetaLepW, &b_CosThetaLepW);
     fChain[ifile][isys]->SetBranchAddress("CosThetaLepZ", &CosThetaLepZ, &b_CosThetaLepZ);
     fChain[ifile][isys]->SetBranchAddress("DY_WZ", &DY_WZ, &b_DY_WZ);
     fChain[ifile][isys]->SetBranchAddress("DY_3Z", &DY_3Z, &b_DY_3Z);
     fChain[ifile][isys]->SetBranchAddress("DY_3N", &DY_3N, &b_DY_3N);
     fChain[ifile][isys]->SetBranchAddress("Truth_Pt_WZ", &Truth_Pt_WZ, &b_Truth_Pt_WZ);
     fChain[ifile][isys]->SetBranchAddress("DeltaPhiLepWLepZ", &DeltaPhiLepWLepZ, &b_DeltaPhiLepWLepZ);
     fChain[ifile][isys]->SetBranchAddress("DeltaPhiLepWLepZWZFrame", &DeltaPhiLepWLepZWZFrame, &b_DeltaPhiLepWLepZWZFrame);
     fChain[ifile][isys]->SetBranchAddress("R21", &R21, &b_R21);
     fChain[ifile][isys]->SetBranchAddress("WLepPt", &WLepPt, &b_WLepPt);
     fChain[ifile][isys]->SetBranchAddress("ZLeadingLepPt", &ZLeadingLepPt, &b_ZLeadingLepPt);
     fChain[ifile][isys]->SetBranchAddress("ZSubleadingLepPt", &ZSubleadingLepPt, &b_ZSubleadingLepPt);
     fChain[ifile][isys]->SetBranchAddress("WLepEta", &WLepEta, &b_WLepEta);
     fChain[ifile][isys]->SetBranchAddress("ZLeadingLepEta", &ZLeadingLepEta, &b_ZLeadingLepEta);
     fChain[ifile][isys]->SetBranchAddress("ZSubleadingLepEta", &ZSubleadingLepEta, &b_ZSubleadingLepEta);
     fChain[ifile][isys]->SetBranchAddress("WLepPhi", &WLepPhi, &b_WLepPhi);
     fChain[ifile][isys]->SetBranchAddress("ZLeadingLepPhi", &ZLeadingLepPhi, &b_ZLeadingLepPhi);
     fChain[ifile][isys]->SetBranchAddress("ZSubleadingLepPhi", &ZSubleadingLepPhi, &b_ZSubleadingLepPhi);

     fChain[ifile][isys]->SetBranchAddress("Lep1MediumIDWeight", &Lep1MediumIDWeight, &b_Lep1MediumIDWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep2MediumIDWeight", &Lep2MediumIDWeight, &b_Lep2MediumIDWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep3MediumIDWeight", &Lep3MediumIDWeight, &b_Lep3MediumIDWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep1TightIDWeight", &Lep1TightIDWeight, &b_Lep1TightIDWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep2TightIDWeight", &Lep2TightIDWeight, &b_Lep2TightIDWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep3TightIDWeight", &Lep3TightIDWeight, &b_Lep3TightIDWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep1MediumIsoWeight", &Lep1MediumIsoWeight, &b_Lep1MediumIsoWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep2MediumIsoWeight", &Lep2MediumIsoWeight, &b_Lep2MediumIsoWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep3MediumIsoWeight", &Lep3MediumIsoWeight, &b_Lep3MediumIsoWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep1TightIsoWeight", &Lep1TightIsoWeight, &b_Lep1TightIsoWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep2TightIsoWeight", &Lep2TightIsoWeight, &b_Lep2TightIsoWeight);
     fChain[ifile][isys]->SetBranchAddress("Lep3TightIsoWeight", &Lep3TightIsoWeight, &b_Lep3TightIsoWeight);

     //if(doFakeRate){
       fChain[ifile][isys]->SetBranchAddress("passZZCR", &passZZCR, &b_passZZCR);
       fChain[ifile][isys]->SetBranchAddress("passTopCR", &passTopCR, &b_passTopCR);
       fChain[ifile][isys]->SetBranchAddress("passZFakeElCR", &passZFakeElCR, &b_passZFakeElCR);
       fChain[ifile][isys]->SetBranchAddress("passZFakeElCR_UpSys", &passZFakeElCR_UpSys, &b_passZFakeElCR_UpSys);
       fChain[ifile][isys]->SetBranchAddress("passZFakeElCR_DownSys", &passZFakeElCR_DownSys, &b_passZFakeElCR_DownSys);
       fChain[ifile][isys]->SetBranchAddress("passZFakeMuCR", &passZFakeMuCR, &b_passZFakeMuCR);
       fChain[ifile][isys]->SetBranchAddress("passTopElCR", &passTopElCR, &b_passTopElCR);
       fChain[ifile][isys]->SetBranchAddress("passTopMuCR", &passTopMuCR, &b_passTopMuCR);
       fChain[ifile][isys]->SetBranchAddress("passWZInclusive", &passWZInclusive, &b_passWZInclusive);
       fChain[ifile][isys]->SetBranchAddress("passHardWZInclusive", &passHardWZInclusive, &b_passHardWZInclusive);
       fChain[ifile][isys]->SetBranchAddress("passWZInclusiveLoose", &passWZInclusiveLoose, &b_passWZInclusiveLoose);
       fChain[ifile][isys]->SetBranchAddress("passHardWZInclusiveLoose", &passHardWZInclusiveLoose, &b_passHardWZInclusiveLoose);
       fChain[ifile][isys]->SetBranchAddress("passWZqqSR", &passWZqqSR, &b_passWZqqSR);
       fChain[ifile][isys]->SetBranchAddress("passWZqqCR", &passWZqqCR, &b_passWZqqCR);
       fChain[ifile][isys]->SetBranchAddress("passWZVBSSR", &passWZVBSSR, &b_passWZVBSSR);
       fChain[ifile][isys]->SetBranchAddress("passWZVBSCR", &passWZVBSCR, &b_passWZVBSCR);
       fChain[ifile][isys]->SetBranchAddress("passWZInclusiveNoMET", &passWZInclusiveNoMET, &b_passWZInclusiveNoMET);
       fChain[ifile][isys]->SetBranchAddress("passTopEnrichCR", &passTopEnrichCR, &b_passTopEnrichCR);
       fChain[ifile][isys]->SetBranchAddress("passTTT", &passTTT, &b_passTTT);
       fChain[ifile][isys]->SetBranchAddress("passTTL", &passTTL, &b_passTTL);
       fChain[ifile][isys]->SetBranchAddress("passTLT", &passTLT, &b_passTLT);
       fChain[ifile][isys]->SetBranchAddress("passLTT", &passLTT, &b_passLTT);
       fChain[ifile][isys]->SetBranchAddress("passTLL", &passTLL, &b_passTLL);
       fChain[ifile][isys]->SetBranchAddress("passLTL", &passLTL, &b_passLTL);
       fChain[ifile][isys]->SetBranchAddress("passLLT", &passLLT, &b_passLLT);
       fChain[ifile][isys]->SetBranchAddress("passZCondition", &passZCondition, &b_passZCondition);
       fChain[ifile][isys]->SetBranchAddress("passWCondition", &passWCondition, &b_passWCondition);
       fChain[ifile][isys]->SetBranchAddress("passSignalRegion", &passSignalRegion, &b_passSignalRegion);
       fChain[ifile][isys]->SetBranchAddress("pass100SignalRegion", &pass100SignalRegion, &b_pass100SignalRegion);
       fChain[ifile][isys]->SetBranchAddress("passHighPtWZCR", &passHighPtWZCR, &b_passHighPtWZCR);
       fChain[ifile][isys]->SetBranchAddress("passLowPtZCR", &passLowPtZCR, &b_passLowPtZCR);
       fChain[ifile][isys]->SetBranchAddress("passTruthMatch1", &passTruthMatch1, &b_passTruthMatch1);
       fChain[ifile][isys]->SetBranchAddress("passTruthMatch2", &passTruthMatch2, &b_passTruthMatch2);
       fChain[ifile][isys]->SetBranchAddress("passTruthMatch3", &passTruthMatch3, &b_passTruthMatch3);
       fChain[ifile][isys]->SetBranchAddress("passZCondition1", &passZCondition1, &b_passZCondition1);
       fChain[ifile][isys]->SetBranchAddress("passZCondition2", &passZCondition2, &b_passZCondition2);
       fChain[ifile][isys]->SetBranchAddress("passZCondition3", &passZCondition3, &b_passZCondition3);
       fChain[ifile][isys]->SetBranchAddress("passWCondition1", &passWCondition1, &b_passWCondition1);
       fChain[ifile][isys]->SetBranchAddress("passWCondition2", &passWCondition2, &b_passWCondition2);
       fChain[ifile][isys]->SetBranchAddress("passWCondition3", &passWCondition3, &b_passWCondition3);
       fChain[ifile][isys]->SetBranchAddress("passMediumID1", &passMediumID1, &b_passMediumID1);
       fChain[ifile][isys]->SetBranchAddress("passMediumID2", &passMediumID2, &b_passMediumID2);
       fChain[ifile][isys]->SetBranchAddress("passMediumID3", &passMediumID3, &b_passMediumID3);
       fChain[ifile][isys]->SetBranchAddress("passTightID1", &passTightID1, &b_passTightID1);
       fChain[ifile][isys]->SetBranchAddress("passTightID2", &passTightID2, &b_passTightID2);
       fChain[ifile][isys]->SetBranchAddress("passTightID3", &passTightID3, &b_passTightID3);
       fChain[ifile][isys]->SetBranchAddress("passIPID1", &passIPID1, &b_passIPID1);
       fChain[ifile][isys]->SetBranchAddress("passIPID2", &passIPID2, &b_passIPID2);
       fChain[ifile][isys]->SetBranchAddress("passIPID3", &passIPID3, &b_passIPID3);
       fChain[ifile][isys]->SetBranchAddress("isTauEvent", &isTauEvent, &b_isTauEvent);
       fChain[ifile][isys]->SetBranchAddress("passDeltaR", &passDeltaR, &b_passDeltaR);
       fChain[ifile][isys]->SetBranchAddress("passThreeBaseline", &passThreeBaseline, &b_passThreeBaseline);
     //}
     if(doRunPDFAndQCDUnc) fChain[ifile][isys]->SetBranchAddress("PDFWeights", &PDFWeights, &b_PDFWeights);
     if(doRunPDFAndQCDUnc) fChain[ifile][isys]->SetBranchAddress("QCDWeights", &QCDWeights, &b_QCDWeights);

     TotalEntries[ifile][isys] = fChain[ifile][isys]->GetEntries();
  }
}

void TreeForWZPolarization::GetEntry(int ifile, int isys, long i)
{
 fChain[ifile][isys]->GetEntry(i);
}

void TreeForWZPolarization::GenerateFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void TreeForWZPolarization::DefineTree(int isys, TString TreeName)
{
 cout<<"Defining the tree "<<TreeName<<endl;

 GenerateTree[isys] = new TTree(TreeName, TreeName);

 GenerateTree[isys]->Branch("Flavor", &Flavor, "Flavor/I");
 GenerateTree[isys]->Branch("EventNumber", &EventNumber, "EventNumber/L");
 GenerateTree[isys]->Branch("Yields", &Yields, "Yields/I");
 GenerateTree[isys]->Branch("isMC", &isMC, "isMC/I");
 GenerateTree[isys]->Branch("Channel", &Channel, "Channel/I");
 GenerateTree[isys]->Branch("Year", &Year, "Year/I");
 GenerateTree[isys]->Branch("NormSF", &NormSF, "NormSF/F");
 GenerateTree[isys]->Branch("WeightSign", &WeightSign, "WeightSign/F");
 GenerateTree[isys]->Branch("WeightNormalized", &WeightNormalized, "WeightNormalized/F");
 GenerateTree[isys]->Branch("Weight", &Weight, "Weight/F");
 GenerateTree[isys]->Branch("TotalWeight", &TotalWeight, "TotalWeight/F");
 GenerateTree[isys]->Branch("WeightNormalizedNoKFactor", &WeightNormalizedNoKFactor, "WeightNormalizedNoKFactor/F");
 GenerateTree[isys]->Branch("WeightNoKFactor", &WeightNoKFactor, "WeightNoKFactor/F");
 GenerateTree[isys]->Branch("TotalWeightNoKFactor", &TotalWeightNoKFactor, "TotalWeightNoKFactor/F");
 GenerateTree[isys]->Branch("M_WZ", &M_WZ, "M_WZ/F");
 GenerateTree[isys]->Branch("M_3l", &M_3l, "M_3l/F");
 GenerateTree[isys]->Branch("Mt_WZ", &Mt_WZ, "Mt_WZ/F");
 GenerateTree[isys]->Branch("M_Z", &M_Z, "M_Z/F");
 GenerateTree[isys]->Branch("Mt_W", &Mt_W, "Mt_W/F");
 GenerateTree[isys]->Branch("Met", &Met, "Met/F");
 GenerateTree[isys]->Branch("Njets", &Njets, "Njets/I");
 GenerateTree[isys]->Branch("NBjets", &NBjets, "NBjets/I");
 GenerateTree[isys]->Branch("SumOfWeight", &SumOfWeight, "SumOfWeight/D");
 GenerateTree[isys]->Branch("Luminosity", &Luminosity, "Luminosity/D");
 GenerateTree[isys]->Branch("CrossSection", &CrossSection, "CrossSection/D");
 GenerateTree[isys]->Branch("Lep1Pt", &Lep1Pt, "Lep1Pt/F");
 GenerateTree[isys]->Branch("Lep2Pt", &Lep2Pt, "Lep2Pt/F");
 GenerateTree[isys]->Branch("Lep3Pt", &Lep3Pt, "Lep3Pt/F");
 GenerateTree[isys]->Branch("Lep1Eta", &Lep1Eta, "Lep1Eta/F");
 GenerateTree[isys]->Branch("Lep2Eta", &Lep2Eta, "Lep2Eta/F");
 GenerateTree[isys]->Branch("Lep3Eta", &Lep3Eta, "Lep3Eta/F");
 GenerateTree[isys]->Branch("Lep1Phi", &Lep1Phi, "Lep1Phi/F");
 GenerateTree[isys]->Branch("Lep2Phi", &Lep2Phi, "Lep2Phi/F");
 GenerateTree[isys]->Branch("Lep3Phi", &Lep3Phi, "Lep3Phi/F");
 GenerateTree[isys]->Branch("Lep1Flavor", &Lep1Flavor, "Lep1Flavor/I");
 GenerateTree[isys]->Branch("Lep2Flavor", &Lep2Flavor, "Lep2Flavor/I");
 GenerateTree[isys]->Branch("Lep3Flavor", &Lep3Flavor, "Lep3Flavor/I");
 GenerateTree[isys]->Branch("Lep1Charge", &Lep1Charge, "Lep1Charge/I");
 GenerateTree[isys]->Branch("Lep2Charge", &Lep2Charge, "Lep2Charge/I");
 GenerateTree[isys]->Branch("Lep3Charge", &Lep3Charge, "Lep3Charge/I");
 GenerateTree[isys]->Branch("Lep1Ambiguity", &Lep1Ambiguity, "Lep1Ambiguity/I");
 GenerateTree[isys]->Branch("Lep2Ambiguity", &Lep2Ambiguity, "Lep2Ambiguity/I");
 GenerateTree[isys]->Branch("Lep3Ambiguity", &Lep3Ambiguity, "Lep3Ambiguity/I");
 GenerateTree[isys]->Branch("TruthLep1Pt", &TruthLep1Pt, "TruthLep1Pt/F");
 GenerateTree[isys]->Branch("TruthLep2Pt", &TruthLep2Pt, "TruthLep2Pt/F");
 GenerateTree[isys]->Branch("TruthLep3Pt", &TruthLep3Pt, "TruthLep3Pt/F");
 GenerateTree[isys]->Branch("TruthLep1Eta", &TruthLep1Eta, "TruthLep1Eta/F");
 GenerateTree[isys]->Branch("TruthLep2Eta", &TruthLep2Eta, "TruthLep2Eta/F");
 GenerateTree[isys]->Branch("TruthLep3Eta", &TruthLep3Eta, "TruthLep3Eta/F");
 GenerateTree[isys]->Branch("TruthLep1Phi", &TruthLep1Phi, "TruthLep1Phi/F");
 GenerateTree[isys]->Branch("TruthLep2Phi", &TruthLep2Phi, "TruthLep2Phi/F");
 GenerateTree[isys]->Branch("TruthLep3Phi", &TruthLep3Phi, "TruthLep3Phi/F");
 GenerateTree[isys]->Branch("TruthLep1Flavor", &TruthLep1Flavor, "TruthLep1Flavor/I");
 GenerateTree[isys]->Branch("TruthLep2Flavor", &TruthLep2Flavor, "TruthLep2Flavor/I");
 GenerateTree[isys]->Branch("TruthLep3Flavor", &TruthLep3Flavor, "TruthLep3Flavor/I");
 GenerateTree[isys]->Branch("Mpx", &Mpx, "Mpx/F");
 GenerateTree[isys]->Branch("Mpy", &Mpy, "Mpy/F");
 GenerateTree[isys]->Branch("Mpz", &Mpz, "Mpz/F");
 GenerateTree[isys]->Branch("LWTNNNuPz", &LWTNNNuPz, "LWTNNNuPz/F");
 GenerateTree[isys]->Branch("TruthNuPz", &TruthNuPz, "TruthNuPz/F");
 GenerateTree[isys]->Branch("LWTNNpLL", &LWTNNpLL, "LWTNNpLL/F");
 GenerateTree[isys]->Branch("LWTNNpLT", &LWTNNpLT, "LWTNNpLT/F");
 GenerateTree[isys]->Branch("LWTNNpTL", &LWTNNpTL, "LWTNNpTL/F");
 GenerateTree[isys]->Branch("LWTNNpTT", &LWTNNpTT, "LWTNNpTT/F");
 GenerateTree[isys]->Branch("LLNLOWeight", &LLNLOWeight, "LLNLOWeight/F");
 GenerateTree[isys]->Branch("LTNLOWeight", &LTNLOWeight, "LTNLOWeight/F");
 GenerateTree[isys]->Branch("TLNLOWeight", &TLNLOWeight, "TLNLOWeight/F");
 GenerateTree[isys]->Branch("TTNLOWeight", &TTNLOWeight, "TTNLOWeight/F");
 GenerateTree[isys]->Branch("Lep1WeightZ", &Lep1WeightZ, "Lep1WeightZ/F");
 GenerateTree[isys]->Branch("Lep2WeightZ", &Lep2WeightZ, "Lep2WeightZ/F");
 GenerateTree[isys]->Branch("Lep3WeightZ", &Lep3WeightZ, "Lep3WeightZ/F");
 GenerateTree[isys]->Branch("Lep1WeightW", &Lep1WeightW, "Lep1WeightW/F");
 GenerateTree[isys]->Branch("Lep2WeightW", &Lep2WeightW, "Lep2WeightW/F");
 GenerateTree[isys]->Branch("Lep3WeightW", &Lep3WeightW, "Lep3WeightW/F");
 GenerateTree[isys]->Branch("Pt_W", &Pt_W, "Pt_W/F");
 GenerateTree[isys]->Branch("Pt_Z", &Pt_Z, "Pt_Z/F");
 GenerateTree[isys]->Branch("Pt_WZ", &Pt_WZ, "Pt_WZ/F");
 GenerateTree[isys]->Branch("SumJetPt", &SumJetPt, "SumJetPt/F");
 GenerateTree[isys]->Branch("CosThetaV", &CosThetaV, "CosThetaV/F");
 GenerateTree[isys]->Branch("CosThetaLepW", &CosThetaLepW, "CosThetaLepW/F");
 GenerateTree[isys]->Branch("CosThetaLepZ", &CosThetaLepZ, "CosThetaLepZ/F");
 GenerateTree[isys]->Branch("DY_WZ", &DY_WZ, "DY_WZ/F");
 GenerateTree[isys]->Branch("DY_3Z", &DY_3Z, "DY_3Z/F");
 GenerateTree[isys]->Branch("DY_3N", &DY_3N, "DY_3N/F");
 GenerateTree[isys]->Branch("Truth_Pt_WZ", &Truth_Pt_WZ, "Truth_Pt_WZ/F");
 GenerateTree[isys]->Branch("DeltaPhiLepWLepZ", &DeltaPhiLepWLepZ, "DeltaPhiLepWLepZ/F");
 GenerateTree[isys]->Branch("DeltaPhiLepWLepZWZFrame", &DeltaPhiLepWLepZWZFrame, "DeltaPhiLepWLepZWZFrame/F");
 GenerateTree[isys]->Branch("R21", &R21, "R21/F");
 GenerateTree[isys]->Branch("WLepPt", &WLepPt, "WLepPt/F");
 GenerateTree[isys]->Branch("ZLeadingLepPt", &ZLeadingLepPt, "ZLeadingLepPt/F");
 GenerateTree[isys]->Branch("ZSubleadingLepPt", &ZSubleadingLepPt, "ZSubleadingLepPt/F");
 GenerateTree[isys]->Branch("WLepEta", &WLepEta, "WLepEta/F");
 GenerateTree[isys]->Branch("ZLeadingLepEta", &ZLeadingLepEta, "ZLeadingLepEta/F");
 GenerateTree[isys]->Branch("ZSubleadingLepEta", &ZSubleadingLepEta, "ZSubleadingLepEta/F");
 GenerateTree[isys]->Branch("WLepPhi", &WLepPhi, "WLepPhi/F");
 GenerateTree[isys]->Branch("ZLeadingLepPhi", &ZLeadingLepPhi, "ZLeadingLepPhi/F");
 GenerateTree[isys]->Branch("ZSubleadingLepPhi", &ZSubleadingLepPhi, "ZSubleadingLepPhi/F");
 GenerateTree[isys]->Branch("Lep1D0Sig", &Lep1D0Sig, "Lep1D0Sig/F");
 GenerateTree[isys]->Branch("Lep2D0Sig", &Lep2D0Sig, "Lep2D0Sig/F");
 GenerateTree[isys]->Branch("Lep3D0Sig", &Lep3D0Sig, "Lep3D0Sig/F");

 GenerateTree[isys]->Branch("Lep1MediumIDWeight", &Lep1MediumIDWeight, "Lep1MediumIDWeight/F");
 GenerateTree[isys]->Branch("Lep2MediumIDWeight", &Lep2MediumIDWeight, "Lep2MediumIDWeight/F");
 GenerateTree[isys]->Branch("Lep3MediumIDWeight", &Lep3MediumIDWeight, "Lep3MediumIDWeight/F");
 GenerateTree[isys]->Branch("Lep1TightIDWeight", &Lep1TightIDWeight, "Lep1TightIDWeight/F");
 GenerateTree[isys]->Branch("Lep2TightIDWeight", &Lep2TightIDWeight, "Lep2TightIDWeight/F");
 GenerateTree[isys]->Branch("Lep3TightIDWeight", &Lep3TightIDWeight, "Lep3TightIDWeight/F");
 GenerateTree[isys]->Branch("Lep1MediumIsoWeight", &Lep1MediumIsoWeight, "Lep1MediumIsoWeight/F");
 GenerateTree[isys]->Branch("Lep2MediumIsoWeight", &Lep2MediumIsoWeight, "Lep2MediumIsoWeight/F");
 GenerateTree[isys]->Branch("Lep3MediumIsoWeight", &Lep3MediumIsoWeight, "Lep3MediumIsoWeight/F");
 GenerateTree[isys]->Branch("Lep1TightIsoWeight", &Lep1TightIsoWeight, "Lep1TightIsoWeight/F");
 GenerateTree[isys]->Branch("Lep2TightIsoWeight", &Lep2TightIsoWeight, "Lep2TightIsoWeight/F");
 GenerateTree[isys]->Branch("Lep3TightIsoWeight", &Lep3TightIsoWeight, "Lep3TightIsoWeight/F");

 GenerateTree[isys]->Branch("passZZCR", &passZZCR, "passZZCR/I");
 GenerateTree[isys]->Branch("passTopCR", &passTopCR, "passTopCR/I");
 GenerateTree[isys]->Branch("passZFakeElCR", &passZFakeElCR, "passZFakeElCR/I");
 GenerateTree[isys]->Branch("passZFakeElCR_UpSys", &passZFakeElCR_UpSys, "passZFakeElCR_UpSys/I");
 GenerateTree[isys]->Branch("passZFakeElCR_DownSys", &passZFakeElCR_DownSys, "passZFakeElCR_DownSys/I");
 GenerateTree[isys]->Branch("passZFakeMuCR", &passZFakeMuCR, "passZFakeMuCR/I");
 GenerateTree[isys]->Branch("passTopElCR", &passTopElCR, "passTopElCR/I");
 GenerateTree[isys]->Branch("passTopMuCR", &passTopMuCR, "passTopMuCR/I");
 GenerateTree[isys]->Branch("passWZInclusive", &passWZInclusive, "passWZInclusive/I");
 GenerateTree[isys]->Branch("passHardWZInclusive", &passHardWZInclusive, "passHardWZInclusive/I");
 GenerateTree[isys]->Branch("passWZInclusiveLoose", &passWZInclusiveLoose, "passWZInclusiveLoose/I");
 GenerateTree[isys]->Branch("passHardWZInclusiveLoose", &passHardWZInclusiveLoose, "passHardWZInclusiveLoose/I");
 GenerateTree[isys]->Branch("passWZqqSR", &passWZqqSR, "passWZqqSR/I");
 GenerateTree[isys]->Branch("passWZqqCR", &passWZqqCR, "passWZqqCR/I");
 GenerateTree[isys]->Branch("passWZVBSSR", &passWZVBSSR, "passWZVBSSR/I");
 GenerateTree[isys]->Branch("passWZVBSCR", &passWZVBSCR, "passWZVBSCR/I");
 GenerateTree[isys]->Branch("passWZInclusiveNoMET", &passWZInclusiveNoMET, "passWZInclusiveNoMET/I");
 GenerateTree[isys]->Branch("passTopEnrichCR", &passTopEnrichCR, "passTopEnrichCR/I");
 GenerateTree[isys]->Branch("passTTT", &passTTT, "passTTT/I");
 GenerateTree[isys]->Branch("passTTL", &passTTL, "passTTL/I");
 GenerateTree[isys]->Branch("passTLT", &passTLT, "passTLT/I");
 GenerateTree[isys]->Branch("passLTT", &passLTT, "passLTT/I");
 GenerateTree[isys]->Branch("passTLL", &passTLL, "passTLL/I");
 GenerateTree[isys]->Branch("passLTL", &passLTL, "passLTL/I");
 GenerateTree[isys]->Branch("passLLT", &passLLT, "passLLT/I");
 GenerateTree[isys]->Branch("passZCondition", &passZCondition, "passZCondition/I");
 GenerateTree[isys]->Branch("passWCondition", &passWCondition, "passWCondition/I");
 GenerateTree[isys]->Branch("passSignalRegion", &passSignalRegion, "passSignalRegion/I");
 GenerateTree[isys]->Branch("pass100SignalRegion", &pass100SignalRegion, "pass100SignalRegion/I");
 GenerateTree[isys]->Branch("passHighPtWZCR", &passHighPtWZCR, "passHighPtWZCR/I");
 GenerateTree[isys]->Branch("passLowPtZCR", &passLowPtZCR, "passLowPtZCR/I");
 GenerateTree[isys]->Branch("passTruthMatch1", &passTruthMatch1, "passTruthMatch1/I");
 GenerateTree[isys]->Branch("passTruthMatch2", &passTruthMatch2, "passTruthMatch2/I");
 GenerateTree[isys]->Branch("passTruthMatch3", &passTruthMatch3, "passTruthMatch3/I");
 GenerateTree[isys]->Branch("passZCondition1", &passZCondition1, "passZCondition1/I");
 GenerateTree[isys]->Branch("passZCondition2", &passZCondition2, "passZCondition2/I");
 GenerateTree[isys]->Branch("passZCondition3", &passZCondition3, "passZCondition3/I");
 GenerateTree[isys]->Branch("passWCondition1", &passWCondition1, "passWCondition1/I");
 GenerateTree[isys]->Branch("passWCondition2", &passWCondition2, "passWCondition2/I");
 GenerateTree[isys]->Branch("passWCondition3", &passWCondition3, "passWCondition3/I");
 GenerateTree[isys]->Branch("passMediumID1", &passMediumID1, "passMediumID1/I");
 GenerateTree[isys]->Branch("passMediumID2", &passMediumID2, "passMediumID2/I");
 GenerateTree[isys]->Branch("passMediumID3", &passMediumID3, "passMediumID3/I");
 GenerateTree[isys]->Branch("passTightID1", &passTightID1, "passTightID1/I");
 GenerateTree[isys]->Branch("passTightID2", &passTightID2, "passTightID2/I");
 GenerateTree[isys]->Branch("passTightID3", &passTightID3, "passTightID3/I");
 GenerateTree[isys]->Branch("passIPID1", &passIPID1, "passIPID1/I");
 GenerateTree[isys]->Branch("passIPID2", &passIPID2, "passIPID2/I");
 GenerateTree[isys]->Branch("passIPID3", &passIPID3, "passIPID3/I");
 GenerateTree[isys]->Branch("isTauEvent", &isTauEvent, "isTauEvent/I");
 GenerateTree[isys]->Branch("passDeltaR", &passDeltaR, "passDeltaR/I");
 GenerateTree[isys]->Branch("passThreeBaseline", &passThreeBaseline, "passThreeBaseline/I");
 GenerateTree[isys]->Branch("passZZVeto", &passZZVeto, "passZZVeto/I");
 GenerateTree[isys]->Branch("PDFWeights", "vector<double>", &vPDFWeights);
 GenerateTree[isys]->Branch("QCDWeights", "vector<double>", &vQCDWeights);

 if(isys == 0){
   Event_CutFlow = new TH1D("Event_CutFlow", "Event_CutFlow", 30, 0, 30);
   Event_CutFlow->SetDirectory(hf);
   Electron_CutFlow = new TH1D("Electron_CutFlow", "Electron_CutFlow", 20, 0, 20);
   Electron_CutFlow->SetDirectory(hf);
   Muon_CutFlow = new TH1D("Muon_CutFlow", "Muon_CutFlow", 20, 0, 20);
   Muon_CutFlow->SetDirectory(hf);

   Event_CutNameMap = new std::map<std::string, double>();
   Electron_CutNameMap = new std::map<std::string, double>();
   Muon_CutNameMap = new std::map<std::string, double>();

   Event_WeightedCutFlow = new TH1D("Event_WeightedCutFlow", "Event_WeightedCutFlow", 30, 0, 30);
   Event_WeightedCutFlow->SetDirectory(hf);
   Electron_WeightedCutFlow = new TH1D("Electron_WeightedCutFlow", "Electron_WeightedCutFlow", 20, 0, 20);
   Electron_WeightedCutFlow->SetDirectory(hf);
   Muon_WeightedCutFlow = new TH1D("Muon_WeightedCutFlow", "Muon_WeightedCutFlow", 20, 0, 20);
   Muon_WeightedCutFlow->SetDirectory(hf);

   Event_WeightedCutNameMap = new std::map<std::string, double>();
   Electron_WeightedCutNameMap = new std::map<std::string, double>();
   Muon_WeightedCutNameMap = new std::map<std::string, double>();

/*   Event_CutFlow->GetXaxis()->SetBinLabel(1, "all");
   Event_CutFlow->GetXaxis()->SetBinLabel(2, ">=3 baselineHard");
   Event_CutFlow->GetXaxis()->SetBinLabel(3, "Pass Trig");
   Event_CutFlow->GetXaxis()->SetBinLabel(4, "Leading Pt > 27GeV");
   Event_CutFlow->GetXaxis()->SetBinLabel(5, "==3 baselineHard");
   Event_CutFlow->GetXaxis()->SetBinLabel(6, "SFOS");
   Event_CutFlow->GetXaxis()->SetBinLabel(7, "|ZBoson.M() - 91.1876| < 20GeV");
   Event_CutFlow->GetXaxis()->SetBinLabel(8, "Met > 25GeV");
   Event_CutFlow->GetXaxis()->SetBinLabel(9, "Pass WZInclusive");
   Event_CutFlow->GetXaxis()->SetBinLabel(10, "Pass pT_Z");
   Event_CutFlow->GetXaxis()->SetBinLabel(11, "Pass pT_WZ");
*/
 }


}

void TreeForWZPolarization::FillTree(int isys)
{
 GenerateTree[isys]->Fill();
}

void TreeForWZPolarization::DefineTruthTree()
{
 TruthTree = new TTree("Truth", "Truth");

 TruthTree->Branch("Flavor", &Flavor, "Flavor/I");
 TruthTree->Branch("EventNumber", &EventNumber, "EventNumber/L");
 TruthTree->Branch("NormSF", &NormSF, "NormSF/F");
 TruthTree->Branch("WeightSign", &WeightSign, "WeightSign/F");
 TruthTree->Branch("WeightNormalized", &WeightNormalized, "WeightNormalized/F");
 TruthTree->Branch("Weight", &Weight, "Weight/F");
 TruthTree->Branch("TotalWeight", &TotalWeight, "TotalWeight/F");
 TruthTree->Branch("WeightNormalizedNoKFactor", &WeightNormalizedNoKFactor, "WeightNormalizedNoKFactor/F");
 TruthTree->Branch("WeightNoKFactor", &WeightNoKFactor, "WeightNoKFactor/F");
 TruthTree->Branch("TotalWeightNoKFactor", &TotalWeightNoKFactor, "TotalWeightNoKFactor/F");
 TruthTree->Branch("M_WZ", &M_WZ, "M_WZ/F");
 TruthTree->Branch("Mt_WZ", &Mt_WZ, "Mt_WZ/F");
 TruthTree->Branch("M_Z", &M_Z, "M_Z/F");
 TruthTree->Branch("Mt_W", &Mt_W, "Mt_W/F");
 TruthTree->Branch("Met", &Met, "Met/F");
 TruthTree->Branch("Lep1Pt", &Lep1Pt, "Lep1Pt/F");
 TruthTree->Branch("Lep2Pt", &Lep2Pt, "Lep2Pt/F");
 TruthTree->Branch("Lep3Pt", &Lep3Pt, "Lep3Pt/F");
 TruthTree->Branch("Lep1Eta", &Lep1Eta, "Lep1Eta/F");
 TruthTree->Branch("Lep2Eta", &Lep2Eta, "Lep2Eta/F");
 TruthTree->Branch("Lep3Eta", &Lep3Eta, "Lep3Eta/F");
 TruthTree->Branch("Lep1Phi", &Lep1Phi, "Lep1Phi/F");
 TruthTree->Branch("Lep2Phi", &Lep2Phi, "Lep2Phi/F");
 TruthTree->Branch("Lep3Phi", &Lep3Phi, "Lep3Phi/F");
 TruthTree->Branch("Mpx", &Mpx, "Mpx/F");
 TruthTree->Branch("Mpy", &Mpy, "Mpy/F");
 TruthTree->Branch("Mpz", &Mpz, "Mpz/F");
 TruthTree->Branch("LWTNNNuPz", &LWTNNNuPz, "LWTNNNuPz/F");
 TruthTree->Branch("TruthNuPz", &TruthNuPz, "TruthNuPz/F");
 TruthTree->Branch("Pt_W", &Pt_W, "Pt_W/F");
 TruthTree->Branch("Pt_Z", &Pt_Z, "Pt_Z/F");
 TruthTree->Branch("Pt_WZ", &Pt_WZ, "Pt_WZ/F");
 TruthTree->Branch("CosThetaV", &CosThetaV, "CosThetaV/F");
 TruthTree->Branch("CosThetaLepW", &CosThetaLepW, "CosThetaLepW/F");
 TruthTree->Branch("CosThetaLepZ", &CosThetaLepZ, "CosThetaLepZ/F");
 TruthTree->Branch("DY_WZ", &DY_WZ, "DY_WZ/F");
 TruthTree->Branch("DY_3Z", &DY_3Z, "DY_3Z/F");
 TruthTree->Branch("DY_3N", &DY_3N, "DY_3N/F");
 TruthTree->Branch("DeltaPhiLepWLepZ", &DeltaPhiLepWLepZ, "DeltaPhiLepWLepZ/F");
 TruthTree->Branch("DeltaPhiLepWLepZWZFrame", &DeltaPhiLepWLepZWZFrame, "DeltaPhiLepWLepZWZFrame/F");
 TruthTree->Branch("R21", &R21, "R21/F");
 TruthTree->Branch("passWZInclusive", &passWZInclusive, "passWZInclusive/I");
 TruthTree->Branch("passHardWZInclusive", &passHardWZInclusive, "passHardWZInclusive/I");
 TruthTree->Branch("isTauEvent", &isTauEvent, "isTauEvent/I");

}

void TreeForWZPolarization::FillTruthTree()
{
 TruthTree->Fill();
}

void TreeForWZPolarization::updateCutFlow(TH1D *inCutFlow, std::map<std::string, double> *inLabelMap, std::string cutName, double step, bool doUpdate){
  if(!doUpdate) return;
  double Xpos = -1;
  if(inLabelMap->count(cutName)){
    Xpos = (*inLabelMap)[cutName];
  }
  else{
    (*inLabelMap)[cutName] = inLabelMap->size() * 1.; //this will gives 1 when first call, strange ... doesn't happen with stand alone root run
    std::cout<<"registering new cut "<<cutName<<" at position "<<(*inLabelMap)[cutName]<<std::endl;
    inCutFlow->GetXaxis()->SetBinLabel(inLabelMap->size()+1, cutName.c_str());
    Xpos = (*inLabelMap)[cutName];
  }
  inCutFlow->Fill(Xpos,step);
}


void TreeForWZPolarization::SaveFile()
{
 hf->cd();

 hf->Write();
 hf->Close();
}
