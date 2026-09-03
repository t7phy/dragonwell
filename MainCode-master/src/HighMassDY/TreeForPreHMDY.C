#define TreeForPreHMDY_cxx
#include "HighMassDY/TreeForPreHMDY.h"

using namespace std;

TreeForPreHMDY::TreeForPreHMDY()
{
 Init();
}

TreeForPreHMDY::~TreeForPreHMDY()
{

}

void TreeForPreHMDY::ConfigFile(int NFilePerJob, int iRound)
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

   TTree* metaTree = (TTree *)rootfile[i]->Get("sumWeights");
   metaTree->GetEntry(0);
   int DSID = metaTree->GetLeaf("dsid")->GetValue();
   DSIDs.push_back(DSID);
   delete metaTree;
 }

 InitialSysName();
}

void TreeForPreHMDY::ConfigFile(int ifile)
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

 TTree* metaTree = (TTree *)rootfile[0]->Get("sumWeights");
 metaTree->GetEntry(0);
 int DSID = metaTree->GetLeaf("dsid")->GetValue();
 DSIDs.clear();
 DSIDs.push_back(DSID);
 delete metaTree;

 cout<<"There is "<<EndFile<<" files."<<endl;
 cout<<RootNames.at(ifile)<<endl;

 InitialSysName();

}

void TreeForPreHMDY::CloseFile(int ifile)
{
 rootfile[ifile]->Close();
}

void TreeForPreHMDY::InputFile(vector<TString> RootNames)
{
 this->RootNames = RootNames;

}

void TreeForPreHMDY::InputSumOfWeight(map<pair<int, int>, double> SumOfWeightsMap)
{
 this->SumOfWeightsMap = SumOfWeightsMap;
}

void TreeForPreHMDY::InputLuminosity(double Lumi1516, double Lumi17, double Lumi18)
{
 this->Lumi1516 = Lumi1516;
 this->Lumi17 = Lumi17;
 this->Lumi18 = Lumi18;
}

TString TreeForPreHMDY::GetRootType(TString name)
{
 TString RootType;

 if(name.Contains("data15_") || name.Contains("data16_") || name.Contains("data17_") || name.Contains("data18_")){
   RootType = "Data";
 }
 else if(name.Contains("DrellYan") || name.Contains("Ztoee") || name.Contains("Ztomumu")){
   RootType = "DrellYan";
 }
 else if(name.Contains("PI_")){
   RootType = "PhotonInduced";
 }
 else if(name.Contains("TopQuark") || name.Contains("singleTop")){
   RootType = "TopQuark";
 }
 else if(name.Contains("Diboson")){
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

int TreeForPreHMDY::GetYear(TString RootName)
{
 int Year = 0;
 if(RootName.Contains("mc16a") || RootName.Contains("r9364")) Year = 1516;
 else if(RootName.Contains("mc16d") || RootName.Contains("r10201")) Year = 17;
 else if(RootName.Contains("mc16e") || RootName.Contains("r10724")) Year = 18;
 else Year = 0;

 return Year;
}

void TreeForPreHMDY::SetBranch(int ifile)
{
   if(TreeName == "nominal") isLooseTree = false;
   else if(TreeName == "nominal_Loose") isLooseTree = true;

   fChain[ifile] = (TTree *)rootfile[ifile]->Get(TreeName);

   fChain[ifile]->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain[ifile]->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain[ifile]->SetBranchAddress("randomRunNumber", &randomRunNumber, &b_randomRunNumber);
   fChain[ifile]->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain[ifile]->SetBranchAddress("mu", &mu, &b_mu);
   fChain[ifile]->SetBranchAddress("mu_actual", &mu_actual, &b_mu_actual);
   fChain[ifile]->SetBranchAddress("mu_original_xAOD", &mu_original_xAOD, &b_mu_original_xAOD);
   fChain[ifile]->SetBranchAddress("mu_actual_original_xAOD", &mu_actual_original_xAOD, &b_mu_actual_original_xAOD);
   fChain[ifile]->SetBranchAddress("backgroundFlags", &backgroundFlags, &b_backgroundFlags);
   fChain[ifile]->SetBranchAddress("hasBadMuon", &hasBadMuon, &b_hasBadMuon);

   fChain[ifile]->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain[ifile]->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain[ifile]->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain[ifile]->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain[ifile]->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain[ifile]->SetBranchAddress("el_charge", &el_charge, &b_el_charge);

   // HMDY+b sample
   /*fChain[ifile]->SetBranchAddress("reco_lep_pt", &el_pt, &b_el_pt);
   fChain[ifile]->SetBranchAddress("reco_lep_eta", &el_eta, &b_el_eta);
   fChain[ifile]->SetBranchAddress("reco_lep_phi", &el_phi, &b_el_phi);
   fChain[ifile]->SetBranchAddress("reco_lep_e", &el_e, &b_el_e);
   fChain[ifile]->SetBranchAddress("reco_lep_charge", &el_charge, &b_el_charge);
   */

   fChain[ifile]->SetBranchAddress("el_topoetcone20", &el_topoetcone20, &b_el_topoetcone20);
   fChain[ifile]->SetBranchAddress("el_ptvarcone20", &el_ptvarcone20, &b_el_ptvarcone20);
   if(isLooseTree) fChain[ifile]->SetBranchAddress("el_isTight", &el_isTight, &b_el_isTight);
   fChain[ifile]->SetBranchAddress("el_CF", &el_CF, &b_el_CF);
   fChain[ifile]->SetBranchAddress("el_d0sig", &el_d0sig, &b_el_d0sig);
   fChain[ifile]->SetBranchAddress("el_delta_z0_sintheta", &el_delta_z0_sintheta, &b_el_delta_z0_sintheta);
   fChain[ifile]->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain[ifile]->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain[ifile]->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain[ifile]->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain[ifile]->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain[ifile]->SetBranchAddress("mu_topoetcone20", &mu_topoetcone20, &b_mu_topoetcone20);
   fChain[ifile]->SetBranchAddress("mu_ptvarcone30", &mu_ptvarcone30, &b_mu_ptvarcone30);
   if(isLooseTree) fChain[ifile]->SetBranchAddress("mu_isTight", &mu_isTight, &b_mu_isTight);
   fChain[ifile]->SetBranchAddress("mu_d0sig", &mu_d0sig, &b_mu_d0sig);
   fChain[ifile]->SetBranchAddress("mu_delta_z0_sintheta", &mu_delta_z0_sintheta, &b_mu_delta_z0_sintheta);
   fChain[ifile]->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain[ifile]->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain[ifile]->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain[ifile]->SetBranchAddress("jet_e", &jet_e, &b_jet_e);
   fChain[ifile]->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);
   fChain[ifile]->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain[ifile]->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain[ifile]->SetBranchAddress("mumuSelection", &mumuSelection, &b_mumuSelection);
   fChain[ifile]->SetBranchAddress("emu", &emu, &b_emu);
   fChain[ifile]->SetBranchAddress("eeSelection", &eeSelection, &b_eeSelection);
   //fChain[ifile]->SetBranchAddress("ee_pre", &eeSelection, &b_eeSelection); // HMDY+b Sample
   fChain[ifile]->SetBranchAddress("eeSelection_withmuon", &eeSelection_withmuon, &b_eeSelection_withmuon);
   fChain[ifile]->SetBranchAddress("SingleElectron", &SingleElectron, &b_SingleElectron);

   fChain[ifile]->SetBranchAddress("HLT_mu50",                                    &HLT_mu50                                   , &b_HLT_mu50                                   );
   fChain[ifile]->SetBranchAddress("HLT_2mu10",                                   &HLT_2mu10                                  , &b_HLT_2mu10                                  );
   fChain[ifile]->SetBranchAddress("HLT_mu18_mu8noL1",                            &HLT_mu18_mu8noL1                           , &b_HLT_mu18_mu8noL1                           );
   fChain[ifile]->SetBranchAddress("HLT_2e12_lhloose_L12EM10VH",                  &HLT_2e12_lhloose_L12EM10VH                 , &b_HLT_2e12_lhloose_L12EM10VH                 );
   fChain[ifile]->SetBranchAddress("HLT_e120_lhloose",                            &HLT_e120_lhloose                           , &b_HLT_e120_lhloose                           );
   fChain[ifile]->SetBranchAddress("HLT_mu20_iloose_L1MU15",                      &HLT_mu20_iloose_L1MU15                     , &b_HLT_mu20_iloose_L1MU15                     );
   fChain[ifile]->SetBranchAddress("HLT_e24_lhmedium_L1EM20VH",                   &HLT_e24_lhmedium_L1EM20VH                  , &b_HLT_e24_lhmedium_L1EM20VH                  );
   fChain[ifile]->SetBranchAddress("HLT_e60_lhmedium",                            &HLT_e60_lhmedium                           , &b_HLT_e60_lhmedium                           );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e60_lhmedium",               &el_trigMatch_HLT_e60_lhmedium              , &b_el_trigMatch_HLT_e60_lhmedium              );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e120_lhloose",               &el_trigMatch_HLT_e120_lhloose              , &b_el_trigMatch_HLT_e120_lhloose              );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e24_lhmedium_L1EM20VH",      &el_trigMatch_HLT_e24_lhmedium_L1EM20VH     , &b_el_trigMatch_HLT_e24_lhmedium_L1EM20VH     );
   fChain[ifile]->SetBranchAddress("mu_trigMatch_HLT_mu50",                       &mu_trigMatch_HLT_mu50                      , &b_mu_trigMatch_HLT_mu50                      );
   fChain[ifile]->SetBranchAddress("mu_trigMatch_HLT_mu18_mu8noL1",               &mu_trigMatch_HLT_mu18_mu8noL1              , &b_mu_trigMatch_HLT_mu18_mu8noL1              );
   fChain[ifile]->SetBranchAddress("mu_trigMatch_HLT_mu20_iloose_L1MU15",         &mu_trigMatch_HLT_mu20_iloose_L1MU15        , &b_mu_trigMatch_HLT_mu20_iloose_L1MU15        );
   fChain[ifile]->SetBranchAddress("HLT_mu26_ivarmedium",                         &HLT_mu26_ivarmedium                        , &b_HLT_mu26_ivarmedium                        );
   fChain[ifile]->SetBranchAddress("HLT_2mu14",                                   &HLT_2mu14                                  , &b_HLT_2mu14                                  );
   fChain[ifile]->SetBranchAddress("HLT_2e17_lhvloose_nod0",                      &HLT_2e17_lhvloose_nod0                     , &b_HLT_2e17_lhvloose_nod0                     );
   fChain[ifile]->SetBranchAddress("HLT_e140_lhloose_nod0",                       &HLT_e140_lhloose_nod0                      , &b_HLT_e140_lhloose_nod0                      );
   fChain[ifile]->SetBranchAddress("HLT_e26_lhtight_nod0_ivarloose",              &HLT_e26_lhtight_nod0_ivarloose             , &b_HLT_e26_lhtight_nod0_ivarloose             );
   fChain[ifile]->SetBranchAddress("HLT_e60_lhmedium_nod0",                       &HLT_e60_lhmedium_nod0                      , &b_HLT_e60_lhmedium_nod0                      );
   fChain[ifile]->SetBranchAddress("HLT_mu22_mu8noL1",                            &HLT_mu22_mu8noL1                           , &b_HLT_mu22_mu8noL1                           );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e60_lhmedium_nod0",          &el_trigMatch_HLT_e60_lhmedium_nod0         , &b_el_trigMatch_HLT_e60_lhmedium_nod0         );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e140_lhloose_nod0",          &el_trigMatch_HLT_e140_lhloose_nod0         , &b_el_trigMatch_HLT_e140_lhloose_nod0         );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e26_lhtight_nod0_ivarloose", &el_trigMatch_HLT_e26_lhtight_nod0_ivarloose, &b_el_trigMatch_HLT_e26_lhtight_nod0_ivarloose);
   fChain[ifile]->SetBranchAddress("mu_trigMatch_HLT_mu22_mu8noL1",               &mu_trigMatch_HLT_mu22_mu8noL1              , &b_mu_trigMatch_HLT_mu22_mu8noL1              );
   fChain[ifile]->SetBranchAddress("mu_trigMatch_HLT_mu26_ivarmedium",            &mu_trigMatch_HLT_mu26_ivarmedium           , &b_mu_trigMatch_HLT_mu26_ivarmedium           );
   fChain[ifile]->SetBranchAddress("HLT_2e24_lhvloose_nod0",                      &HLT_2e24_lhvloose_nod0                     , &b_HLT_2e24_lhvloose_nod0                     );
   fChain[ifile]->SetBranchAddress("HLT_2e17_lhvloose_nod0_L12EM15VHI",           &HLT_2e17_lhvloose_nod0_L12EM15VHI          , &b_HLT_2e17_lhvloose_nod0_L12EM15VHI          );

   fChain[ifile]->SetBranchAddress("HLT_e60_lhvloose_nod0", &HLT_e60_lhvloose_nod0, &b_HLT_e60_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("HLT_e300_etcut", &HLT_e300_etcut, &b_HLT_e300_etcut);
   fChain[ifile]->SetBranchAddress("HLT_e120_lhvloose_nod0", &HLT_e120_lhvloose_nod0, &b_HLT_e120_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("HLT_e140_lhvloose_nod0", &HLT_e140_lhvloose_nod0, &b_HLT_e140_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("HLT_e26_lhvloose_nod0_L1EM20VH", &HLT_e26_lhvloose_nod0_L1EM20VH, &b_HLT_e26_lhvloose_nod0_L1EM20VH);
   fChain[ifile]->SetBranchAddress("HLT_e26_lhvloose_nod0_L1EM22VH", &HLT_e26_lhvloose_nod0_L1EM22VH, &b_HLT_e26_lhvloose_nod0_L1EM22VH);
   fChain[ifile]->SetBranchAddress("HLT_e200_etcut", &HLT_e200_etcut, &b_HLT_e200_etcut);

   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH", &el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH, &b_el_trigMatch_HLT_e26_lhvloose_nod0_L1EM20VH);
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH", &el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH, &b_el_trigMatch_HLT_e26_lhvloose_nod0_L1EM22VH);
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e60_lhvloose_nod0",          &el_trigMatch_HLT_e60_lhvloose_nod0         , &b_el_trigMatch_HLT_e60_lhvloose_nod0         );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e120_lhvloose_nod0",         &el_trigMatch_HLT_e120_lhvloose_nod0        , &b_el_trigMatch_HLT_e120_lhvloose_nod0        );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e140_lhvloose_nod0",         &el_trigMatch_HLT_e140_lhvloose_nod0        , &b_el_trigMatch_HLT_e140_lhvloose_nod0        );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e200_etcut",                 &el_trigMatch_HLT_e200_etcut                , &b_el_trigMatch_HLT_e200_etcut                );
   fChain[ifile]->SetBranchAddress("el_trigMatch_HLT_e300_etcut",                 &el_trigMatch_HLT_e300_etcut                , &b_el_trigMatch_HLT_e300_etcut                );

   fChain[ifile]->SetBranchAddress("weight_KFactor", &weight_KFactor, &b_weight_KFactor);
   fChain[ifile]->SetBranchAddress("mu_isMedium", &mu_isMedium, &b_mu_isMedium);
   fChain[ifile]->SetBranchAddress("mu_isHighPt", &mu_isHighPt, &b_mu_isHighPt);
   fChain[ifile]->SetBranchAddress("mu_PtID", &mu_PtID, &b_mu_PtID);
   fChain[ifile]->SetBranchAddress("mu_PtMS", &mu_PtMS, &b_mu_PtMS);
   fChain[ifile]->SetBranchAddress("mu_isolation_FixedCutTight", &mu_isolation_FixedCutTight, &b_mu_isolation_FixedCutTight);
   fChain[ifile]->SetBranchAddress("mu_isolation_FixedCutLoose", &mu_isolation_FixedCutLoose, &b_mu_isolation_FixedCutLoose);
   fChain[ifile]->SetBranchAddress("mu_isolation_FixedCutPflowTight", &mu_isolation_FixedCutPflowTight, &b_mu_isolation_FixedCutPflowTight);
   fChain[ifile]->SetBranchAddress("mu_isolation_FixedCutPflowLoose", &mu_isolation_FixedCutPflowLoose, &b_mu_isolation_FixedCutPflowLoose);
   fChain[ifile]->SetBranchAddress("mu_isolation_FCTightTrackOnly_FixedRad", &mu_isolation_FCTightTrackOnly_FixedRad, &b_mu_isolation_FCTightTrackOnly_FixedRad);
   fChain[ifile]->SetBranchAddress("mu_isolation_TightTrackOnly_VarRad", &mu_isolation_TightTrackOnly_VarRad, &b_mu_isolation_TightTrackOnly_VarRad);
   fChain[ifile]->SetBranchAddress("el_isolation_FixedCutLoose", &el_isolation_FixedCutLoose, &b_el_isolation_FixedCutLoose);
   fChain[ifile]->SetBranchAddress("el_isolation_FixedCutTight", &el_isolation_FixedCutTight, &b_el_isolation_FixedCutTight);
   fChain[ifile]->SetBranchAddress("el_isolation_PflowTight", &el_isolation_PflowTight, &b_el_isolation_PflowTight);
   fChain[ifile]->SetBranchAddress("el_isolation_TightTrackOnly", &el_isolation_TightTrackOnly, &b_el_isolation_TightTrackOnly);
   fChain[ifile]->SetBranchAddress("el_isolation_TightTrackOnly_FixedRad", &el_isolation_TightTrackOnly_FixedRad, &b_el_isolation_TightTrackOnly_FixedRad);
   fChain[ifile]->SetBranchAddress("el_isElTight", &el_isElTight, &b_el_isElTight);

   fChain[ifile]->SetBranchAddress("el_SF_Reco", &el_SF_Reco, &b_el_SF_Reco);
   fChain[ifile]->SetBranchAddress("el_SF_Reco_Corr", &el_SF_Reco_Corr, &b_el_SF_Reco_Corr);
   fChain[ifile]->SetBranchAddress("el_SF_ID_LooseAndBLayerLH", &el_SF_ID_LooseAndBLayerLH, &b_el_SF_ID_LooseAndBLayerLH);
   fChain[ifile]->SetBranchAddress("el_SF_ID_MediumLH", &el_SF_ID_MediumLH, &b_el_SF_ID_MediumLH);
   fChain[ifile]->SetBranchAddress("el_SF_Iso_FCTight", &el_SF_Iso_FCTight, &b_el_SF_Iso_FCTight);
   fChain[ifile]->SetBranchAddress("mu_SF_TTVA", &mu_SF_TTVA, &b_mu_SF_TTVA);
   fChain[ifile]->SetBranchAddress("mu_SF_ID_HighPt", &mu_SF_ID_HighPt, &b_mu_SF_ID_HighPt);
   fChain[ifile]->SetBranchAddress("mu_SF_ID_Loose", &mu_SF_ID_Loose, &b_mu_SF_ID_Loose);
   fChain[ifile]->SetBranchAddress("mu_SF_ID_Medium", &mu_SF_ID_Medium, &b_mu_SF_ID_Medium);
   fChain[ifile]->SetBranchAddress("mu_SF_Iso_FCTightTrackOnly_FixedRad", &mu_SF_Iso_FCTightTrackOnly_FixedRad, &b_mu_SF_Iso_FCTightTrackOnly_FixedRad);
   fChain[ifile]->SetBranchAddress("mu_SF_Iso_TightTrackOnly_VarRad", &mu_SF_Iso_TightTrackOnly_VarRad, &b_mu_SF_Iso_TightTrackOnly_VarRad);

   if(isLooseTree) fChain[ifile]->SetBranchAddress("fwdel_isTight", &fwdel_isTight, &b_fwdel_isTight);
   fChain[ifile]->SetBranchAddress("fwdel_isMedium", &fwdel_isMedium, &b_fwdel_isMedium);
   fChain[ifile]->SetBranchAddress("fwdel_isLoose", &fwdel_isLoose, &b_fwdel_isLoose);
   fChain[ifile]->SetBranchAddress("el_isElMedium", &el_isElMedium, &b_el_isElMedium);
   fChain[ifile]->SetBranchAddress("el_isElLoose", &el_isElLoose, &b_el_isElLoose);
   fChain[ifile]->SetBranchAddress("el_DFCommonElectronsECIDS", &el_DFCommonElectronsECIDS, &b_el_DFCommonElectronsECIDS);
   fChain[ifile]->SetBranchAddress("el_DFCommonElectronsECIDSResult", &el_DFCommonElectronsECIDSResult, &b_el_DFCommonElectronsECIDSResult);
   fChain[ifile]->SetBranchAddress("el_isPromptLepton", &el_isPromptLepton, &b_el_isPromptLepton);

   // MC
   fChain[ifile]->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain[ifile]->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain[ifile]->SetBranchAddress("weight_leptonSF", &weight_leptonSF, &b_weight_leptonSF);
   fChain[ifile]->SetBranchAddress("weight_globalLeptonTriggerSF", &weight_globalLeptonTriggerSF, &b_weight_globalLeptonTriggerSF);
   fChain[ifile]->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);
   fChain[ifile]->SetBranchAddress("weight_pileup_UP", &weight_pileup_UP, &b_weight_pileup_UP);
   fChain[ifile]->SetBranchAddress("weight_pileup_DOWN", &weight_pileup_DOWN, &b_weight_pileup_DOWN);
   fChain[ifile]->SetBranchAddress("weight_indiv_SF_EL_ChargeMisID", &weight_indiv_SF_EL_ChargeMisID, &b_weight_indiv_SF_EL_ChargeMisID);
   fChain[ifile]->SetBranchAddress("weight_indiv_SF_EL_ChargeMisID_STAT_UP", &weight_indiv_SF_EL_ChargeMisID_STAT_UP, &b_weight_indiv_SF_EL_ChargeMisID_STAT_UP);
   fChain[ifile]->SetBranchAddress("weight_indiv_SF_EL_ChargeMisID_STAT_DOWN", &weight_indiv_SF_EL_ChargeMisID_STAT_DOWN, &b_weight_indiv_SF_EL_ChargeMisID_STAT_DOWN);
   fChain[ifile]->SetBranchAddress("weight_indiv_SF_EL_ChargeMisID_SYST_UP", &weight_indiv_SF_EL_ChargeMisID_SYST_UP, &b_weight_indiv_SF_EL_ChargeMisID_SYST_UP);
   fChain[ifile]->SetBranchAddress("weight_indiv_SF_EL_ChargeMisID_SYST_DOWN", &weight_indiv_SF_EL_ChargeMisID_SYST_DOWN, &b_weight_indiv_SF_EL_ChargeMisID_SYST_DOWN);
   fChain[ifile]->SetBranchAddress("Lepton_Pt_born", &Lepton_Pt_born, &b_Lepton_Pt_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_Pt_born", &AntiLepton_Pt_born, &b_AntiLepton_Pt_born);
   fChain[ifile]->SetBranchAddress("Lepton_Eta_born", &Lepton_Eta_born, &b_Lepton_Eta_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_Eta_born", &AntiLepton_Eta_born, &b_AntiLepton_Eta_born);
   fChain[ifile]->SetBranchAddress("Lepton_Phi_born", &Lepton_Phi_born, &b_Lepton_Phi_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_Phi_born", &AntiLepton_Phi_born, &b_AntiLepton_Phi_born);
   fChain[ifile]->SetBranchAddress("Lepton_m_born", &Lepton_m_born, &b_Lepton_m_born);
   fChain[ifile]->SetBranchAddress("AntiLepton_m_born", &AntiLepton_m_born, &b_AntiLepton_m_born);
   fChain[ifile]->SetBranchAddress("Lepton_Pt_bare", &Lepton_Pt_bare, &b_Lepton_Pt_bare);
   fChain[ifile]->SetBranchAddress("AntiLepton_Pt_bare", &AntiLepton_Pt_bare, &b_AntiLepton_Pt_bare);
   fChain[ifile]->SetBranchAddress("Lepton_Eta_bare", &Lepton_Eta_bare, &b_Lepton_Eta_bare);
   fChain[ifile]->SetBranchAddress("AntiLepton_Eta_bare", &AntiLepton_Eta_bare, &b_AntiLepton_Eta_bare);
   fChain[ifile]->SetBranchAddress("Lepton_Phi_bare", &Lepton_Phi_bare, &b_Lepton_Phi_bare);
   fChain[ifile]->SetBranchAddress("AntiLepton_Phi_bare", &AntiLepton_Phi_bare, &b_AntiLepton_Phi_bare);
   fChain[ifile]->SetBranchAddress("Lepton_Pt_dressed", &Lepton_Pt_dressed, &b_Lepton_Pt_dressed);
   fChain[ifile]->SetBranchAddress("Lepton_Eta_dressed", &Lepton_Eta_dressed, &b_Lepton_Eta_dressed);
   fChain[ifile]->SetBranchAddress("Lepton_Phi_dressed", &Lepton_Phi_dressed, &b_Lepton_Phi_dressed);
   fChain[ifile]->SetBranchAddress("Lepton_Charge_dressed", &Lepton_Charge_dressed, &b_Lepton_Charge_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Pt_dressed", &AntiLepton_Pt_dressed, &b_AntiLepton_Pt_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Eta_dressed", &AntiLepton_Eta_dressed, &b_AntiLepton_Eta_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Phi_dressed", &AntiLepton_Phi_dressed, &b_AntiLepton_Phi_dressed);
   fChain[ifile]->SetBranchAddress("AntiLepton_Charge_dressed", &AntiLepton_Charge_dressed, &b_AntiLepton_Charge_dressed);
   fChain[ifile]->SetBranchAddress("Dilepton_Pt_born", &Dilepton_Pt_born, &b_Dilepton_Pt_born);
   fChain[ifile]->SetBranchAddress("Dilepton_Rapidity_born", &Dilepton_Rapidity_born, &b_Dilepton_Rapidity_born);
   fChain[ifile]->SetBranchAddress("Dilepton_Eta_born", &Dilepton_Eta_born, &b_Dilepton_Eta_born);
   fChain[ifile]->SetBranchAddress("Dilepton_Phi_born", &Dilepton_Phi_born, &b_Dilepton_Phi_born);
   fChain[ifile]->SetBranchAddress("Dilepton_Mass_born", &Dilepton_Mass_born, &b_Dilepton_Mass_born);

   fChain[ifile]->SetBranchAddress("PS_HLT_e26_lhvloose_nod0_L1EM20VH", &PS_HLT_e26_lhvloose_nod0_L1EM20VH, &b_PS_HLT_e26_lhvloose_nod0_L1EM20VH);
   fChain[ifile]->SetBranchAddress("PS_HLT_e26_lhvloose_nod0_L1EM22VH", &PS_HLT_e26_lhvloose_nod0_L1EM22VH, &b_PS_HLT_e26_lhvloose_nod0_L1EM22VH);
   fChain[ifile]->SetBranchAddress("PS_HLT_e60_lhvloose_nod0", &PS_HLT_e60_lhvloose_nod0, &b_PS_HLT_e60_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("PS_HLT_e200_etcut", &PS_HLT_e200_etcut, &b_PS_HLT_e200_etcut);
   fChain[ifile]->SetBranchAddress("PS_HLT_e120_lhvloose_nod0", &PS_HLT_e120_lhvloose_nod0, &b_PS_HLT_e120_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("PS_HLT_e140_lhvloose_nod0", &PS_HLT_e140_lhvloose_nod0, &b_PS_HLT_e140_lhvloose_nod0);
   fChain[ifile]->SetBranchAddress("PS_HLT_e300_etcut", &PS_HLT_e300_etcut, &b_PS_HLT_e300_etcut);

   TotalEntries[ifile] = fChain[ifile]->GetEntries();
}

void TreeForPreHMDY::GetEntry(int ifile, long i)
{
 fChain[ifile]->GetEntry(i);

}

void TreeForPreHMDY::GetTruthEntry(int ifile, long i)
{
 TruthTree[ifile]->GetEntry(i);

}

double TreeForPreHMDY::GetSumOfWeight(int nchannel, int Year)
{
 if(EndFile < RootNames.size()){
   cout<<"ERROR: to calculate the SumOfWeight, all of the files should be included."<<endl;
   return 0;
 }

 double SumOfWeight = 0.0;
 return SumOfWeight;
}

void TreeForPreHMDY::GetPDFAndQCDIndex(int ifile)
{

}

void TreeForPreHMDY::BkgSelection(TString BkgName)
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

void TreeForPreHMDY::YearSelection(int Year)
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

void TreeForPreHMDY::InitialSysName()
{

}
