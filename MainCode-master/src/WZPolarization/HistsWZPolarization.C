#define HistsWZPolarization_cxx
#include "WZPolarization/HistsWZPolarization.h"

using namespace std;

HistsWZPolarization::HistsWZPolarization()
{
 InitialBkgName("SignalWZ");
 InitialSysName("SignalWZ");
 InitialBkgName("WZPolarized");
 InitialBkgName("ZZControlRegion");
 InitialBkgName("TopControlRegion");
}

void HistsWZPolarization::bookHists(int TotalThread)
{
 this->TotalThread = TotalThread;
 TString tail = "";

 M_WZ_bin = 50;  M_WZ_left = 30.0; M_WZ_right = 1000.0;
 M_3l_bin = 50;  M_3l_left = 30.0; M_3l_right = 200.0;
 Mt_WZ_bin = 50; Mt_WZ_left = 0.0; Mt_WZ_right = 1000.0;
 M_Z_bin = 15; M_Z_left = 80.0; M_Z_right = 110.0;
 Mt_W_bin = 10; Mt_W_left = 0.0; Mt_W_right = 200.0;
 Met_bin = 42;  Met_left = 0.0; Met_right = 420.0;
 Njets_bin = 10; Njets_left = 0.0; Njets_right = 10.0;
 NBjets_bin = 6; NBjets_left = 0.0; NBjets_right = 6.0;
 Lep1Pt_bin = 40;  Lep1Pt_left = 20.0; Lep1Pt_right = 420.0;
 Lep2Pt_bin = 40;  Lep2Pt_left = 20.0; Lep2Pt_right = 420.0;
 Lep3Pt_bin = 50;  Lep3Pt_left = 20.0; Lep3Pt_right = 120.0;
 Lep1Eta_bin = 27;  Lep1Eta_left = -2.7; Lep1Eta_right = 2.7;
 Lep2Eta_bin = 27;  Lep2Eta_left = -2.7; Lep2Eta_right = 2.7;
 Lep3Eta_bin = 10;  Lep3Eta_left = -2.7; Lep3Eta_right = 2.7;
 Lep1Phi_bin = 20;  Lep1Phi_left = -3.14; Lep1Phi_right = 3.14;
 Lep2Phi_bin = 20;  Lep2Phi_left = -3.14; Lep2Phi_right = 3.14;
 Lep3Phi_bin = 20;  Lep3Phi_left = -3.14; Lep3Phi_right = 3.14;
 Mpx_bin = 20;  Mpx_left = 0.0; Mpx_right = 200.0;
 Mpy_bin = 20;  Mpy_left = 0.0; Mpy_right = 200.0;
 Mpz_bin = 40;  Mpz_left = -1500.0; Mpz_right = 1500.0;
 MpzDiff_bin = 40;  MpzDiff_left = -100.0; MpzDiff_right = 100.0;
 LWTNNpLL_bin = 20; LWTNNpLL_left = 0.0; LWTNNpLL_right = 1.0;
 Pt_W_bin = 60;  Pt_W_left = 0.0; Pt_W_right = 600.0;
 Pt_Z_bin = 31;  Pt_Z_left = 0.0; Pt_Z_right = 1000.0;
 Pt_WZ_bin = 40;  Pt_WZ_left = 0.0; Pt_WZ_right = 200.0;
 SumJetPt_bin = 50; SumJetPt_left = 0.0; SumJetPt_right = 1000.0;
 CosThetaV_bin = 20;  CosThetaV_left = -1.0; CosThetaV_right = 1.0;
 CosThetaVAbs_bin = 10;  CosThetaVAbs_left = 0.0; CosThetaVAbs_right = 1.0;
 CosThetaLepW_bin = 10;  CosThetaLepW_left = -1.0; CosThetaLepW_right = 1.0;
 CosThetaLepZ_bin = 10;  CosThetaLepZ_left = -1.0; CosThetaLepZ_right = 1.0;
 DY_WZ_bin = 24;  DY_WZ_left = -6.0; DY_WZ_right = 6.0;
 DY_3Z_bin = 24;  DY_3Z_left = -6.0; DY_3Z_right = 6.0;
 DY_3N_bin = 24;  DY_3N_left = -6.0; DY_3N_right = 6.0;
 Truth_Pt_WZ_bin = 20;  Truth_Pt_WZ_left = 0.0; Truth_Pt_WZ_right = 200000.0;
 DeltaPhi_bin = 40; DeltaPhi_left = -3.14; DeltaPhi_right = 3.14;
 R21_bin = 20; R21_left = 0.0; R21_right = 1.0;
 Channel_bin = 6; Channel_left = 0.0; Channel_right = 6.0;
 BDTScore_bin = 40; BDTScore_left = -1.0; BDTScore_right = 1.0;
 EtaDiff_bin = 5; EtaDiff_left = 0.0; EtaDiff_right = 2.5;

 this->subName = "";

 BookBkgHist(Yield_CutFlow_bkg, "WZPolarized", "Yield_CutFlow", "Yield_CutFlow", 20, 0.0, 20.0);
 BookBkgHist(NormalizedYield_CutFlow_bkg, "WZPolarized", "NormalizedYield_CutFlow", "NormalizedYield_CutFlow", 20, 0.0, 20.0);
 BookBkgHist(Polarized_CutFlow_bkg, "WZPolarized", "Polarized_CutFlow", "Polarized_CutFlow", 20, 0.0, 20.0);

 BookBkgHist(BkgYield_bkg, "SignalWZ", "BkgYield", "BkgYield", 20, 0.0, 20.0);//For fake rate 
 BookBkgHist(PolarizedYield_bkg, "WZPolarized", "PolarizedYield", "PolarizedYield", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_ZZCR_bkg, "WZPolarized", "PolarizedYield_ZZCR", "PolarizedYield_ZZCR", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_HighPtZCR_bkg, "WZPolarized", "PolarizedYield_HighPtZCR", "PolarizedYield_HighPtZCR", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_Signal_bkg, "WZPolarized", "PolarizedYield_Signal", "PolarizedYield_Signal", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_SignalPtWZ_bkg, "WZPolarized", "PolarizedYield_SignalPtWZ", "PolarizedYield_SignalPtWZ", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_HighPtWZCR_bkg, "WZPolarized", "PolarizedYield_HighPtWZCR", "PolarizedYield_HighPtWZCR", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_LowPtWZCR_bkg, "WZPolarized", "PolarizedYield_LowPtWZCR", "PolarizedYield_LowPtWZCR", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_HighR21CR_bkg, "WZPolarized", "PolarizedYield_HighR21CR", "PolarizedYield_HighR21CR", 10, 0.0, 10);
 BookBkgHist(PolarizedYield_LowR21CR_bkg, "WZPolarized", "PolarizedYield_LowR21CR", "PolarizedYield_LowR21CR", 10, 0.0, 10);


 BookHist(MpzDiff, "MpzDiff", "MpzDiff", MpzDiff_bin, MpzDiff_left, MpzDiff_right);
 BookHist(LWTNNNuPzDiff, "LWTNNNuPzDiff", "LWTNNNuPzDiff", MpzDiff_bin, MpzDiff_left, MpzDiff_right);

 BookHist(LeptonCount, "LeptonCount", "LeptonCount", 10, 0, 10);

 if(doFakeRate) bookProcessHists((TString)"Fake", (TString)"");

 if(OnlyNominal){
   bookAllProcessHist(M_WZ, "M_WZ", "M_WZ", M_WZ_bin, M_WZ_left, M_WZ_right);
   bookAllProcessHist(M_3l, "M_3l", "M_3l", M_3l_bin, M_3l_left, M_3l_right);
   bookAllProcessHist(Mt_WZ, "Mt_WZ", "Mt_WZ", Mt_WZ_bin, Mt_WZ_left, Mt_WZ_right);
   bookAllProcessHist(M_Z, "M_Z", "M_Z", M_Z_bin, M_Z_left, M_Z_right);
   bookAllProcessHist(Mt_W, "Mt_W", "Mt_W", Mt_W_bin, Mt_W_left, Mt_W_right);
   bookAllProcessHist(Met, "Met", "Met", Met_bin, Met_left, Met_right);
   bookAllProcessHist(Njets, "Njets", "Njets", Njets_bin, Njets_left, Njets_right);
   bookAllProcessHist(NBjets, "NBjets", "NBjets", NBjets_bin, NBjets_left, NBjets_right);
   //bookAllProcessHist(Lep1Pt, "Lep1Pt", "Lep1Pt", Lep1Pt_bin, Lep1Pt_left, Lep1Pt_right);
   //bookAllProcessHist(Lep2Pt, "Lep2Pt", "Lep2Pt", Lep2Pt_bin, Lep2Pt_left, Lep2Pt_right);
   //bookAllProcessHist(Lep3Pt, "Lep3Pt", "Lep3Pt", Lep3Pt_bin, Lep3Pt_left, Lep3Pt_right);
   //bookAllProcessHist(Lep1Eta, "Lep1Eta", "Lep1Eta", Lep1Eta_bin, Lep1Eta_left, Lep1Eta_right);
   //bookAllProcessHist(Lep2Eta, "Lep2Eta", "Lep2Eta", Lep2Eta_bin, Lep2Eta_left, Lep2Eta_right);
   //bookAllProcessHist(Lep3Eta, "Lep3Eta", "Lep3Eta", Lep3Eta_bin, Lep3Eta_left, Lep3Eta_right);
   //bookAllProcessHist(Lep1Phi, "Lep1Phi", "Lep1Phi", Lep1Phi_bin, Lep1Phi_left, Lep1Phi_right);
   //bookAllProcessHist(Lep2Phi, "Lep2Phi", "Lep2Phi", Lep2Phi_bin, Lep2Phi_left, Lep2Phi_right);
   //bookAllProcessHist(Lep3Phi, "Lep3Phi", "Lep3Phi", Lep3Phi_bin, Lep3Phi_left, Lep3Phi_right);
   bookAllProcessHist(LepPt, "LepPt", "LepPt", Lep1Pt_bin, Lep1Pt_left, Lep1Pt_right);
   bookAllProcessHist(LepEta, "LepEta", "LepEta", Lep1Eta_bin, Lep1Eta_left, Lep1Eta_right);
   bookAllProcessHist(LepPhi, "LepPhi", "LepPhi", Lep1Phi_bin, Lep1Phi_left, Lep1Phi_right);
   //bookAllProcessHist(Lep2Pt_mmm, "Lep2Pt_mmm", "Lep2Pt_mmm", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep2Pt_mme, "Lep2Pt_mme", "Lep2Pt_mme", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep2Pt_eem, "Lep2Pt_eem", "Lep2Pt_eem", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep2Pt_eee, "Lep2Pt_eee", "Lep2Pt_eee", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep3Pt_mmm, "Lep3Pt_mmm", "Lep3Pt_mmm", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep3Pt_mme, "Lep3Pt_mme", "Lep3Pt_mme", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep3Pt_eem, "Lep3Pt_eem", "Lep3Pt_eem", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep3Pt_eee, "Lep3Pt_eee", "Lep3Pt_eee", FakeEl1_bin, FakeEl1_binning);
   //bookAllProcessHist(Lep3Eta_mmm, "Lep3Eta_mmm", "Lep3Eta_mmm", Lep3Eta_bin, Lep3Eta_left, Lep3Eta_right);
   //bookAllProcessHist(Lep3Eta_mme, "Lep3Eta_mme", "Lep3Eta_mme", Lep3Eta_bin, Lep3Eta_left, Lep3Eta_right);
   //bookAllProcessHist(Lep3Eta_eem, "Lep3Eta_eem", "Lep3Eta_eem", Lep3Eta_bin, Lep3Eta_left, Lep3Eta_right);
   //bookAllProcessHist(Lep3Eta_eee, "Lep3Eta_eee", "Lep3Eta_eee", Lep3Eta_bin, Lep3Eta_left, Lep3Eta_right);
   bookAllProcessHist(Mt_W_mmm, "Mt_W_mmm", "Mt_W_mmm", Mt_W_bin, Mt_W_left, Mt_W_right);
   bookAllProcessHist(Mt_W_mme, "Mt_W_mme", "Mt_W_mme", Mt_W_bin, Mt_W_left, Mt_W_right);
   bookAllProcessHist(Mt_W_eem, "Mt_W_eem", "Mt_W_eem", Mt_W_bin, Mt_W_left, Mt_W_right);
   bookAllProcessHist(Mt_W_eee, "Mt_W_eee", "Mt_W_eee", Mt_W_bin, Mt_W_left, Mt_W_right);
   bookAllProcessHist(Met_mmm, "Met_mmm", "Met_mmm", Met_bin, Met_left, Met_right);
   bookAllProcessHist(Met_mme, "Met_mme", "Met_mme", Met_bin, Met_left, Met_right);
   bookAllProcessHist(Met_eem, "Met_eem", "Met_eem", Met_bin, Met_left, Met_right);
   bookAllProcessHist(Met_eee, "Met_eee", "Met_eee", Met_bin, Met_left, Met_right);
   //bookAllProcessHist(Mpx, "Mpx", "Mpx", Mpx_bin, Mpx_left, Mpx_right);
   //bookAllProcessHist(Mpy, "Mpy", "Mpy", Mpy_bin, Mpy_left, Mpy_right);
   //bookAllProcessHist(Mpz, "Mpz", "Mpz", Mpz_bin, Mpz_left, Mpz_right);
   //bookAllProcessHist(LWTNNNuPz, "LWTNNNuPz", "LWTNNNuPz", Mpz_bin, Mpz_left, Mpz_right);
   //bookAllProcessHist(TruthNuPz, "TruthNuPz", "TruthNuPz", Mpz_bin, Mpz_left, Mpz_right);
   //bookAllProcessHist(MpzDiff, "MpzDiff", "MpzDiff", MpzDiff_bin, MpzDiff_left, MpzDiff_right);
   //bookAllProcessHist(LWTNNNuPzDiff, "LWTNNNuPzDiff", "LWTNNNuPzDiff", MpzDiff_bin, MpzDiff_left, MpzDiff_right);
   //bookAllProcessHist(LWTNNpLL, "LWTNNpLL", "LWTNNpLL", LWTNNpLL_bin, LWTNNpLL_left, LWTNNpLL_right);
   //bookAllProcessHist(LWTNNpLT, "LWTNNpLT", "LWTNNpLT", LWTNNpLL_bin, LWTNNpLL_left, LWTNNpLL_right);
   //bookAllProcessHist(LWTNNpTL, "LWTNNpTL", "LWTNNpTL", LWTNNpLL_bin, LWTNNpLL_left, LWTNNpLL_right);
   //bookAllProcessHist(LWTNNpTT, "LWTNNpTT", "LWTNNpTT", LWTNNpLL_bin, LWTNNpLL_left, LWTNNpLL_right);
   bookAllProcessHist(Pt_W, "Pt_W", "Pt_W", Pt_W_bin, Pt_W_left, Pt_W_right);
   bookAllProcessHist(Pt_Z, "Pt_Z", "Pt_Z", Pt_Z_bin, Pt_Z_binning);
   bookAllProcessHist(Pt_Z_mmm, "Pt_Z_mmm", "Pt_Z_mmm", Pt_Z_bin, Pt_Z_binning);
   bookAllProcessHist(Pt_Z_mme, "Pt_Z_mme", "Pt_Z_mme", Pt_Z_bin, Pt_Z_binning);
   bookAllProcessHist(Pt_Z_eem, "Pt_Z_eem", "Pt_Z_eem", Pt_Z_bin, Pt_Z_binning);
   bookAllProcessHist(Pt_Z_eee, "Pt_Z_eee", "Pt_Z_eee", Pt_Z_bin, Pt_Z_binning);
   bookAllProcessHist(Pt_WZ, "Pt_WZ", "Pt_WZ", Pt_WZ_bin, Pt_WZ_left, Pt_WZ_right);
   bookAllProcessHist(SumJetPt, "SumJetPt", "SumJetPt", SumJetPt_bin, SumJetPt_left, SumJetPt_right);
   bookAllProcessHist(CosThetaV, "CosThetaV", "CosThetaV", CosThetaV_bin, CosThetaV_left, CosThetaV_right);
   bookAllProcessHist(CosThetaV_WLZL, "CosThetaV_WLZL", "CosThetaV_WLZL", CosThetaV_bin, CosThetaV_left, CosThetaV_right);
   bookAllProcessHist(CosThetaV_WLZH, "CosThetaV_WLZH", "CosThetaV_WLZH", CosThetaV_bin, CosThetaV_left, CosThetaV_right);
   bookAllProcessHist(CosThetaV_WHZL, "CosThetaV_WHZL", "CosThetaV_WHZL", CosThetaV_bin, CosThetaV_left, CosThetaV_right);
   bookAllProcessHist(CosThetaV_WHZH, "CosThetaV_WHZH", "CosThetaV_WHZH", CosThetaV_bin, CosThetaV_left, CosThetaV_right);
   bookAllProcessHist(CosThetaVAbs, "CosThetaVAbs", "CosThetaVAbs", CosThetaVAbs_bin, CosThetaVAbs_left, CosThetaVAbs_right);
   bookAllProcessHist(CosThetaLepW, "CosThetaLepW", "CosThetaLepW", CosThetaLepW_bin, CosThetaLepW_left, CosThetaLepW_right);
   bookAllProcessHist(CosThetaLepZ, "CosThetaLepZ", "CosThetaLepZ", CosThetaLepZ_bin, CosThetaLepZ_left, CosThetaLepZ_right);
   bookAllProcessHist(DY_3N, "DY_3N", "DY_3N", DY_3N_bin, DY_3N_left, DY_3N_right);
   //bookAllProcessHist(DY_WPlusZ, "DY_WPlusZ", "DY_WPlusZ", DY_WZ_bin, DY_WZ_left, DY_WZ_right);
   //bookAllProcessHist(DY_WMinusZ, "DY_WMinusZ", "DY_WMinusZ", DY_WZ_bin, DY_WZ_left, DY_WZ_right);
   //bookAllProcessHist(DY_3PlusZ, "DY_3PlusZ", "DY_3PlusZ", DY_3Z_bin, DY_3Z_left, DY_3Z_right);
   //bookAllProcessHist(DY_3MinusZ, "DY_3MinusZ", "DY_3MinusZ", DY_3Z_bin, DY_3Z_left, DY_3Z_right);
   bookAllProcessHist(DeltaPhiLepWLepZ, "DeltaPhiLepWLepZ", "DeltaPhiLepWLepZ", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   bookAllProcessHist(DeltaPhiLepWLepZ_WLZL, "DeltaPhiLepWLepZ_WLZL", "DeltaPhiLepWLepZ_WLZL", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   bookAllProcessHist(DeltaPhiLepWLepZ_WLZH, "DeltaPhiLepWLepZ_WLZH", "DeltaPhiLepWLepZ_WLZH", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   bookAllProcessHist(DeltaPhiLepWLepZ_WHZL, "DeltaPhiLepWLepZ_WHZL", "DeltaPhiLepWLepZ_WHZL", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   bookAllProcessHist(DeltaPhiLepWLepZ_WHZH, "DeltaPhiLepWLepZ_WHZH", "DeltaPhiLepWLepZ_WHZH", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   //bookAllProcessHist(DeltaPhiLepWLepZWZFrame, "DeltaPhiLepWLepZWZFrame", "DeltaPhiLepWLepZWZFrame", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   //bookAllProcessHist(DeltaPhiLepWLepZWZFrame_WLZL, "DeltaPhiLepWLepZWZFrame_WLZL", "DeltaPhiLepWLepZWZFrame_WLZL", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   //bookAllProcessHist(DeltaPhiLepWLepZWZFrame_WLZH, "DeltaPhiLepWLepZWZFrame_WLZH", "DeltaPhiLepWLepZWZFrame_WLZH", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   //bookAllProcessHist(DeltaPhiLepWLepZWZFrame_WHZL, "DeltaPhiLepWLepZWZFrame_WHZL", "DeltaPhiLepWLepZWZFrame_WHZL", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   //bookAllProcessHist(DeltaPhiLepWLepZWZFrame_WHZH, "DeltaPhiLepWLepZWZFrame_WHZH", "DeltaPhiLepWLepZWZFrame_WHZH", DeltaPhi_bin, DeltaPhi_left, DeltaPhi_right);
   bookAllProcessHist(R21, "R21", "R21", R21_bin, R21_left, R21_right);
   //bookAllProcessHist(R21_WLZL, "R21_WLZL", "R21_WLZL", R21_bin, R21_left, R21_right);
   //bookAllProcessHist(R21_WLZH, "R21_WLZH", "R21_WLZH", R21_bin, R21_left, R21_right);
   //bookAllProcessHist(R21_WHZL, "R21_WHZL", "R21_WHZL", R21_bin, R21_left, R21_right);
   //bookAllProcessHist(R21_WHZH, "R21_WHZH", "R21_WHZH", R21_bin, R21_left, R21_right);
   bookAllProcessHist(RightZYWLepEta, "RightZYWLepEta", "RightZYWLepEta", EtaDiff_bin, EtaDiff_left, EtaDiff_right);
   bookAllProcessHist(WrongZYWLepEta, "WrongZYWLepEta", "WrongZYWLepEta", EtaDiff_bin, EtaDiff_left, EtaDiff_right);
   bookAllProcessHist(WDecayStatus, "WDecayStatus", "WDecayStatus", 4, 0, 4);
   bookAllProcessHist(ZDecayStatus, "ZDecayStatus", "ZDecayStatus", 4, 0, 4);
 }
 bookAllProcessHist(Channel, "Channel", "Channel", Channel_bin, Channel_left, Channel_right);
 bookAllProcessHist(DY_WZ, "DY_WZ", "DY_WZ", DY_WZ_bin, DY_WZ_left, DY_WZ_right);//systematic
 bookAllProcessHist(DY_3Z, "DY_3Z", "DY_3Z", DY_3Z_bin, DY_3Z_left, DY_3Z_right);//systematic
 bookAllProcessHist(BDTScore, "BDTScore", "BDTScore", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScore_WLZL, "BDTScore_WLZL", "BDTScore_WLZL", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScore_WLZH, "BDTScore_WLZH", "BDTScore_WLZH", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScore_WHZL, "BDTScore_WHZL", "BDTScore_WHZL", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScore_WHZH, "BDTScore_WHZH", "BDTScore_WHZH", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScoreSR, "BDTScoreSR", "BDTScoreSR", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScoreSR_WLZL, "BDTScoreSR_WLZL", "BDTScoreSR_WLZL", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScoreSR_WLZH, "BDTScoreSR_WLZH", "BDTScoreSR_WLZH", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScoreSR_WHZL, "BDTScoreSR_WHZL", "BDTScoreSR_WHZL", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScoreSR_WHZH, "BDTScoreSR_WHZH", "BDTScoreSR_WHZH", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic
 bookAllProcessHist(BDTScoreSR100, "BDTScoreSR100", "BDTScoreSR100", BDTScore_bin, BDTScore_left, BDTScore_right);//systematic

 ReweightFactor = new TH1D("ReweighFactor", "ReweightFactor", Pt_WZ_bin, Pt_WZ_left, Pt_WZ_right);
 ReweightFactor_Truth = new TH1D("ReweighFactor_Truth", "ReweightFactor_Truth", Pt_WZ_bin, Pt_WZ_left, Pt_WZ_right);
}

void HistsWZPolarization::bookProcessHists(TString ProcessName, TString subName)
{
 this->subName = subName;

 TString tail = "";

 if(ProcessName == "Fake"){

   BookHist(Lep3Pt_ZFakeEl_PassZ, "Lep3Pt_ZFakeEl_PassZ", "Lep3Pt_ZFakeEl_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_UpSys_PassZ, "Lep3Pt_ZFakeEl_UpSys_PassZ", "Lep3Pt_ZFakeEl_UpSys_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_DownSys_PassZ, "Lep3Pt_ZFakeEl_DownSys_PassZ", "Lep3Pt_ZFakeEl_DownSys_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_PassZ, "Lep3Pt_ZFakeMu_PassZ", "Lep3Pt_ZFakeMu_PassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_PassZ, "Lep3Pt_TopEl_PassZ", "Lep3Pt_TopEl_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_PassZ, "Lep3Pt_TopMu_PassZ", "Lep3Pt_TopMu_PassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_ZFakeEl_PassW, "Lep3Pt_ZFakeEl_PassW", "Lep3Pt_ZFakeEl_PassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_UpSys_PassW, "Lep3Pt_ZFakeEl_UpSys_PassW", "Lep3Pt_ZFakeEl_UpSys_PassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_DownSys_PassW, "Lep3Pt_ZFakeEl_DownSys_PassW", "Lep3Pt_ZFakeEl_DownSys_PassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_PassW, "Lep3Pt_ZFakeMu_PassW", "Lep3Pt_ZFakeMu_PassW", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_PassW, "Lep3Pt_TopEl_PassW", "Lep3Pt_TopEl_PassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_PassW, "Lep3Pt_TopMu_PassW", "Lep3Pt_TopMu_PassW", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_ZFakeEl_UnPassZ, "Lep3Pt_ZFakeEl_UnPassZ", "Lep3Pt_ZFakeEl_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_UpSys_UnPassZ, "Lep3Pt_ZFakeEl_UpSys_UnPassZ", "Lep3Pt_ZFakeEl_UpSys_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_DownSys_UnPassZ, "Lep3Pt_ZFakeEl_DownSys_UnPassZ", "Lep3Pt_ZFakeEl_DownSys_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_UnPassZ, "Lep3Pt_ZFakeMu_UnPassZ", "Lep3Pt_ZFakeMu_UnPassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_UnPassZ, "Lep3Pt_TopEl_UnPassZ", "Lep3Pt_TopEl_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_UnPassZ, "Lep3Pt_TopMu_UnPassZ", "Lep3Pt_TopMu_UnPassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_ZFakeEl_UnPassW, "Lep3Pt_ZFakeEl_UnPassW", "Lep3Pt_ZFakeEl_UnPassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_UpSys_UnPassW, "Lep3Pt_ZFakeEl_UpSys_UnPassW", "Lep3Pt_ZFakeEl_UpSys_UnPassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_DownSys_UnPassW, "Lep3Pt_ZFakeEl_DownSys_UnPassW", "Lep3Pt_ZFakeEl_DownSys_UnPassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_UnPassW, "Lep3Pt_ZFakeMu_UnPassW", "Lep3Pt_ZFakeMu_UnPassW", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_UnPassW, "Lep3Pt_TopEl_UnPassW", "Lep3Pt_TopEl_UnPassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_UnPassW, "Lep3Pt_TopMu_UnPassW", "Lep3Pt_TopMu_UnPassW", FakeMu_bin, FakeMu_binning);

   BookHist(Lep3Pt_ZFakeEl_Loose, "Lep3Pt_ZFakeEl_Loose", "Lep3Pt_ZFakeEl_Loose", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_UpSys_Loose, "Lep3Pt_ZFakeEl_UpSys_Loose", "Lep3Pt_ZFakeEl_UpSys_Loose", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeEl_DownSys_Loose, "Lep3Pt_ZFakeEl_DownSys_Loose", "Lep3Pt_ZFakeEl_DownSys_Loose", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_Loose, "Lep3Pt_ZFakeMu_Loose", "Lep3Pt_ZFakeMu_Loose", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_Loose, "Lep3Pt_TopEl_Loose", "Lep3Pt_TopEl_Loose", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_Loose, "Lep3Pt_TopMu_Loose", "Lep3Pt_TopMu_Loose", FakeMu_bin, FakeMu_binning);

   BookHist(Lep3Pt_ZFakeEl_PassMedium, "Lep3Pt_ZFakeEl_PassMedium", "Lep3Pt_ZFakeEl_PassMedium", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_PassMedium, "Lep3Pt_ZFakeMu_PassMedium", "Lep3Pt_ZFakeMu_PassMedium", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_PassMedium, "Lep3Pt_TopEl_PassMedium", "Lep3Pt_TopEl_PassMedium", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_PassMedium, "Lep3Pt_TopMu_PassMedium", "Lep3Pt_TopMu_PassMedium", FakeMu_bin, FakeMu_binning);

   BookHist(Lep3Pt_ZFakeEl_PassTight, "Lep3Pt_ZFakeEl_PassTight", "Lep3Pt_ZFakeEl_PassTight", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_ZFakeMu_PassTight, "Lep3Pt_ZFakeMu_PassTight", "Lep3Pt_ZFakeMu_PassTight", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_TopEl_PassTight, "Lep3Pt_TopEl_PassTight", "Lep3Pt_TopEl_PassTight", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_TopMu_PassTight, "Lep3Pt_TopMu_PassTight", "Lep3Pt_TopMu_PassTight", FakeMu_bin, FakeMu_binning);

   BookHist(Lep3Pt_ZFakeEl_LargeMtW_PassW, "Lep3Pt_ZFakeEl_LargeMtW_PassW", "Lep3Pt_ZFakeEl_LargeMtW_PassW", FakeElCorrection_bin, FakeElCorrection_binning);
   BookHist(Lep3Pt_ZFakeEl_LargeMtW_UnPassW, "Lep3Pt_ZFakeEl_LargeMtW_UnPassW", "Lep3Pt_ZFakeEl_LargeMtW_UnPassW", FakeElCorrection_bin, FakeElCorrection_binning);
   BookHist(Lep3Pt_ZFakeMu_LargeMtW_PassW, "Lep3Pt_ZFakeMu_LargeMtW_PassW", "Lep3Pt_ZFakeMu_LargeMtW_PassW", FakeMuCorrection_bin, FakeMuCorrection_binning);
   BookHist(Lep3Pt_ZFakeMu_LargeMtW_UnPassW, "Lep3Pt_ZFakeMu_LargeMtW_UnPassW", "Lep3Pt_ZFakeMu_LargeMtW_UnPassW", FakeMuCorrection_bin, FakeMuCorrection_binning);

   BookHist(Lep3Pt_ZFakeEl_LowMtW_PassW, "Lep3Pt_ZFakeEl_LowMtW_PassW", "Lep3Pt_ZFakeEl_LowMtW_PassW", FakeElCorrection_bin, FakeElCorrection_binning);
   BookHist(Lep3Pt_ZFakeEl_LowMtW_UnPassW, "Lep3Pt_ZFakeEl_LowMtW_UnPassW", "Lep3Pt_ZFakeEl_LowMtW_UnPassW", FakeElCorrection_bin, FakeElCorrection_binning);
   BookHist(Lep3Pt_ZFakeMu_LowMtW_PassW, "Lep3Pt_ZFakeMu_LowMtW_PassW", "Lep3Pt_ZFakeMu_LowMtW_PassW", FakeMuCorrection_bin, FakeMuCorrection_binning);
   BookHist(Lep3Pt_ZFakeMu_LowMtW_UnPassW, "Lep3Pt_ZFakeMu_LowMtW_UnPassW", "Lep3Pt_ZFakeMu_LowMtW_UnPassW", FakeMuCorrection_bin, FakeMuCorrection_binning);

   BookHist(Lep3Pt_RealEl_PassZ, "Lep3Pt_RealEl_PassZ", "Lep3Pt_RealEl_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_RealEl_UnPassZ, "Lep3Pt_RealEl_UnPassZ", "Lep3Pt_RealEl_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_RealEl_PassW, "Lep3Pt_RealEl_PassW", "Lep3Pt_RealEl_PassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_RealEl_UnPassW, "Lep3Pt_RealEl_UnPassW", "Lep3Pt_RealEl_UnPassW", FakeEl_bin, FakeEl_binning);
   BookHist(Lep3Pt_RealEl_Loose, "Lep3Pt_RealEl_Loose", "Lep3Pt_RealEl_Loose", FakeEl_bin, FakeEl_binning);

   BookHist(Lep3Pt_RealMu_PassZ, "Lep3Pt_RealMu_PassZ", "Lep3Pt_RealMu_PassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_RealMu_UnPassZ, "Lep3Pt_RealMu_UnPassZ", "Lep3Pt_RealMu_UnPassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_RealMu_PassW, "Lep3Pt_RealMu_PassW", "Lep3Pt_RealMu_PassW", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_RealMu_UnPassW, "Lep3Pt_RealMu_UnPassW", "Lep3Pt_RealMu_UnPassW", FakeMu_bin, FakeMu_binning);
   BookHist(Lep3Pt_RealMu_Loose, "Lep3Pt_RealMu_Loose", "Lep3Pt_RealMu_Loose", FakeMu_bin, FakeMu_binning);

   BookHist(Lep2Pt_ZFakeEl_PassZ, "Lep2Pt_ZFakeEl_PassZ", "Lep2Pt_ZFakeEl_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep2Pt_ZFakeMu_PassZ, "Lep2Pt_ZFakeMu_PassZ", "Lep2Pt_ZFakeMu_PassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep2Pt_TopEl_PassZ, "Lep2Pt_TopEl_PassZ", "Lep2Pt_TopEl_PassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep2Pt_TopMu_PassZ, "Lep2Pt_TopMu_PassZ", "Lep2Pt_TopMu_PassZ", FakeMu_bin, FakeMu_binning);

   BookHist(Lep2Pt_ZFakeEl_UnPassZ, "Lep2Pt_ZFakeEl_UnPassZ", "Lep2Pt_ZFakeEl_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep2Pt_ZFakeMu_UnPassZ, "Lep2Pt_ZFakeMu_UnPassZ", "Lep2Pt_ZFakeMu_UnPassZ", FakeMu_bin, FakeMu_binning);
   BookHist(Lep2Pt_TopEl_UnPassZ, "Lep2Pt_TopEl_UnPassZ", "Lep2Pt_TopEl_UnPassZ", FakeEl_bin, FakeEl_binning);
   BookHist(Lep2Pt_TopMu_UnPassZ, "Lep2Pt_TopMu_UnPassZ", "Lep2Pt_TopMu_UnPassZ", FakeMu_bin, FakeMu_binning);

   BookHist(Lep3MET_ZFakeEl_PassW, "Lep3MET_ZFakeEl_PassW", "Lep3MET_ZFakeEl_PassW", FakeMET_bin, FakeMET_binning);
   BookHist(Lep3MET_ZFakeEl_UnPassW, "Lep3MET_ZFakeEl_UnPassW", "Lep3MET_ZFakeEl_UnPassW", FakeMET_bin, FakeMET_binning);
   BookHist(Lep3MET_ZFakeMu_PassW, "Lep3MET_ZFakeMu_PassW", "Lep3MET_ZFakeMu_PassW", FakeMET_bin, FakeMET_binning);
   BookHist(Lep3MET_ZFakeMu_UnPassW, "Lep3MET_ZFakeMu_UnPassW", "Lep3MET_ZFakeMu_UnPassW", FakeMET_bin, FakeMET_binning);

   Book2DHist(Lep3PtMET_ZFakeEl_PassW, "Lep3PtMET_ZFakeEl_PassW", "Lep3PtMET_ZFakeEl_PassW", FakeEl_bin, FakeEl_binning, FakeMET_bin, FakeMET_binning);
   Book2DHist(Lep3PtMET_ZFakeEl_UnPassW, "Lep3PtMET_ZFakeEl_UnPassW", "Lep3PtMET_ZFakeEl_UnPassW", FakeEl_bin, FakeEl_binning, FakeMET_bin, FakeMET_binning);
   Book2DHist(Lep3PtMET_ZFakeMu_PassW, "Lep3PtMET_ZFakeMu_PassW", "Lep3PtMET_ZFakeMu_PassW", FakeMu_bin, FakeMu_binning, FakeMET_bin, FakeMET_binning);
   Book2DHist(Lep3PtMET_ZFakeMu_UnPassW, "Lep3PtMET_ZFakeMu_UnPassW", "Lep3PtMET_ZFakeMu_UnPassW", FakeMu_bin, FakeMu_binning, FakeMET_bin, FakeMET_binning);

   BookHist(AverageLep3Pt_Lep3MET_ZFakeEl_Loose_numer, "AverageLep3Pt_Lep3MET_ZFakeEl_Loose_numer", "AverageLep3Pt_Lep3MET_ZFakeEl_Loose_numer", FakeMET_bin, FakeMET_binning);
   BookHist(AverageLep3Pt_Lep3MET_ZFakeEl_Loose_denom, "AverageLep3Pt_Lep3MET_ZFakeEl_Loose_denom", "AverageLep3Pt_Lep3MET_ZFakeEl_Loose_denom", FakeMET_bin, FakeMET_binning);
   BookHist(AverageLep3Pt_Lep3MET_ZFakeMu_Loose_numer, "AverageLep3Pt_Lep3MET_ZFakeMu_Loose_numer", "AverageLep3Pt_Lep3MET_ZFakeMu_Loose_numer", FakeMET_bin, FakeMET_binning);
   BookHist(AverageLep3Pt_Lep3MET_ZFakeMu_Loose_denom, "AverageLep3Pt_Lep3MET_ZFakeMu_Loose_denom", "AverageLep3Pt_Lep3MET_ZFakeMu_Loose_denom", FakeMET_bin, FakeMET_binning);

   BookHist(AverageLep3Pt_Lep3MET_ZFakeEl_PassW_numer, "AverageLep3Pt_Lep3MET_ZFakeEl_PassW_numer", "AverageLep3Pt_Lep3MET_ZFakeEl_PassW_numer", FakeMET_bin, FakeMET_binning);
   BookHist(AverageLep3Pt_Lep3MET_ZFakeMu_PassW_numer, "AverageLep3Pt_Lep3MET_ZFakeMu_PassW_numer", "AverageLep3Pt_Lep3MET_ZFakeMu_PassW_numer", FakeMET_bin, FakeMET_binning);
   BookHist(AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW_numer, "AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW_numer", "AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW_numer", FakeMET_bin, FakeMET_binning);
   BookHist(AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW_numer, "AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW_numer", "AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW_numer", FakeMET_bin, FakeMET_binning);

 } 

}

void HistsWZPolarization::InputSystematicName(TString SystematicName)
{
 this->SystematicName = SystematicName;
}

int HistsWZPolarization::FindSysIndex(TString SysName, TString ProcessName)
{
 int index;
 if(ProcessName == "SignalWZ") index = SysNameIndexSignalWZ[SysName];
 
 return index;
}

void HistsWZPolarization::DefineSysName(int index, TString Name, TString ProcessName)
{
 if(ProcessName == "SignalWZ"){
   SysNameIndexSignalWZ[Name] = index;
   SysNameSignalWZ.push_back(Name);
 }

}

void HistsWZPolarization::InitialSysName(TString ProcessName)
{
 if(ProcessName == "SignalWZ"){
   DefineSysName(0, "nominal", ProcessName);
//   DefineSysName(1, "FakeBkg_MetCut__1down", ProcessName);
//   DefineSysName(2, "FakeBkg_MetCut__1up", ProcessName);

   DefineSysName(1, "EG_RESOLUTION_ALL__1down", ProcessName);
   DefineSysName(2, "EG_RESOLUTION_ALL__1up", ProcessName);
   DefineSysName(3, "EG_SCALE_AF2__1down", ProcessName);
   DefineSysName(4, "EG_SCALE_AF2__1up", ProcessName);
   DefineSysName(5, "EG_SCALE_ALL__1down", ProcessName);
   DefineSysName(6, "EG_SCALE_ALL__1up", ProcessName);
   DefineSysName(7, "EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down", ProcessName);
   DefineSysName(8, "EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up", ProcessName);
   DefineSysName(9, "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down", ProcessName);
   DefineSysName(10, "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up", ProcessName);
   DefineSysName(11, "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down", ProcessName);
   DefineSysName(12, "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up", ProcessName);
   DefineSysName(13, "FT_EFF_Eigen_B_0__1down", ProcessName);
   DefineSysName(14, "FT_EFF_Eigen_B_0__1up", ProcessName);
   DefineSysName(15, "FT_EFF_Eigen_B_1__1down", ProcessName);
   DefineSysName(16, "FT_EFF_Eigen_B_1__1up", ProcessName);
   DefineSysName(17, "FT_EFF_Eigen_B_2__1down", ProcessName);
   DefineSysName(18, "FT_EFF_Eigen_B_2__1up", ProcessName);
   DefineSysName(19, "FT_EFF_Eigen_B_3__1down", ProcessName);
   DefineSysName(20, "FT_EFF_Eigen_B_3__1up", ProcessName);
   DefineSysName(21, "FT_EFF_Eigen_B_4__1down", ProcessName);
   DefineSysName(22, "FT_EFF_Eigen_B_4__1up", ProcessName);
   DefineSysName(23, "FT_EFF_Eigen_B_5__1down", ProcessName);
   DefineSysName(24, "FT_EFF_Eigen_B_5__1up", ProcessName);
   DefineSysName(25, "FT_EFF_Eigen_B_6__1down", ProcessName);
   DefineSysName(26, "FT_EFF_Eigen_B_6__1up", ProcessName);
   DefineSysName(27, "FT_EFF_Eigen_B_7__1down", ProcessName);
   DefineSysName(28, "FT_EFF_Eigen_B_7__1up", ProcessName);
   DefineSysName(29, "FT_EFF_Eigen_B_8__1down", ProcessName);
   DefineSysName(30, "FT_EFF_Eigen_B_8__1up", ProcessName);
   DefineSysName(31, "FT_EFF_Eigen_C_0__1down", ProcessName);
   DefineSysName(32, "FT_EFF_Eigen_C_0__1up", ProcessName);
   DefineSysName(33, "FT_EFF_Eigen_C_1__1down", ProcessName);
   DefineSysName(34, "FT_EFF_Eigen_C_1__1up", ProcessName);
   DefineSysName(35, "FT_EFF_Eigen_C_2__1down", ProcessName);
   DefineSysName(36, "FT_EFF_Eigen_C_2__1up", ProcessName);
   DefineSysName(37, "FT_EFF_Eigen_C_3__1down", ProcessName);
   DefineSysName(38, "FT_EFF_Eigen_C_3__1up", ProcessName);
   DefineSysName(39, "FT_EFF_Eigen_Light_0__1down", ProcessName);
   DefineSysName(40, "FT_EFF_Eigen_Light_0__1up", ProcessName);
   DefineSysName(41, "FT_EFF_Eigen_Light_1__1down", ProcessName);
   DefineSysName(42, "FT_EFF_Eigen_Light_1__1up", ProcessName);
   DefineSysName(43, "FT_EFF_Eigen_Light_2__1down", ProcessName);
   DefineSysName(44, "FT_EFF_Eigen_Light_2__1up", ProcessName);
   DefineSysName(45, "FT_EFF_Eigen_Light_3__1down", ProcessName);
   DefineSysName(46, "FT_EFF_Eigen_Light_3__1up", ProcessName);
   DefineSysName(47, "FT_EFF_extrapolation__1down", ProcessName);
   DefineSysName(48, "FT_EFF_extrapolation__1up", ProcessName);
   DefineSysName(49, "FT_EFF_extrapolation_from_charm__1down", ProcessName);
   DefineSysName(50, "FT_EFF_extrapolation_from_charm__1up", ProcessName);

   //new jet systematic
   DefineSysName(51, "JET_BJES_Response__1down", ProcessName);
   DefineSysName(52, "JET_BJES_Response__1up", ProcessName);
   DefineSysName(53, "JET_EffectiveNP_1__1down", ProcessName);
   DefineSysName(54, "JET_EffectiveNP_1__1up", ProcessName);
   DefineSysName(55, "JET_EffectiveNP_2__1down", ProcessName);
   DefineSysName(56, "JET_EffectiveNP_2__1up", ProcessName);
   DefineSysName(57, "JET_EffectiveNP_3__1down", ProcessName);
   DefineSysName(58, "JET_EffectiveNP_3__1up", ProcessName);
   DefineSysName(59, "JET_EffectiveNP_4__1down", ProcessName);
   DefineSysName(60, "JET_EffectiveNP_4__1up", ProcessName);
   DefineSysName(61, "JET_EffectiveNP_5__1down", ProcessName);
   DefineSysName(62, "JET_EffectiveNP_5__1up", ProcessName);
   DefineSysName(63, "JET_EffectiveNP_6__1down", ProcessName);
   DefineSysName(64, "JET_EffectiveNP_6__1up", ProcessName);
   DefineSysName(65, "JET_EffectiveNP_7__1down", ProcessName);
   DefineSysName(66, "JET_EffectiveNP_7__1up", ProcessName);
   DefineSysName(67, "JET_EffectiveNP_8restTerm__1down", ProcessName);
   DefineSysName(68, "JET_EffectiveNP_8restTerm__1up", ProcessName);
   DefineSysName(69, "JET_EtaIntercalibration_Modelling__1down", ProcessName);
   DefineSysName(70, "JET_EtaIntercalibration_Modelling__1up", ProcessName);
   //

   DefineSysName(71, "JET_EtaIntercalibration_NonClosure_2018data__1down", ProcessName);
   DefineSysName(72, "JET_EtaIntercalibration_NonClosure_2018data__1up", ProcessName);
   DefineSysName(73, "JET_EtaIntercalibration_NonClosure_highE__1down", ProcessName);
   DefineSysName(74, "JET_EtaIntercalibration_NonClosure_highE__1up", ProcessName);
   DefineSysName(75, "JET_EtaIntercalibration_NonClosure_negEta__1down", ProcessName);
   DefineSysName(76, "JET_EtaIntercalibration_NonClosure_negEta__1up", ProcessName);
   DefineSysName(77, "JET_EtaIntercalibration_NonClosure_posEta__1down", ProcessName);
   DefineSysName(78, "JET_EtaIntercalibration_NonClosure_posEta__1up", ProcessName);

   //new jet systematic
   DefineSysName(79, "JET_EtaIntercalibration_TotalStat__1down", ProcessName);
   DefineSysName(80, "JET_EtaIntercalibration_TotalStat__1up", ProcessName);
   DefineSysName(81, "JET_Flavor_Composition__1down", ProcessName);
   DefineSysName(82, "JET_Flavor_Composition__1up", ProcessName);
   //

   DefineSysName(83, "JET_Flavor_Response__1down", ProcessName);
   DefineSysName(84, "JET_Flavor_Response__1up", ProcessName);

   //old jet systematic (do not remove)
   DefineSysName(85, "JET_GroupedNP_1__1down", ProcessName);
   DefineSysName(86, "JET_GroupedNP_1__1up", ProcessName);
   DefineSysName(87, "JET_GroupedNP_2__1down", ProcessName);
   DefineSysName(88, "JET_GroupedNP_2__1up", ProcessName);
   DefineSysName(89, "JET_GroupedNP_3__1down", ProcessName);
   DefineSysName(90, "JET_GroupedNP_3__1up", ProcessName);
   //

   DefineSysName(91, "JET_JER_DataVsMC_MC16__1down", ProcessName);
   DefineSysName(92, "JET_JER_DataVsMC_MC16__1up", ProcessName);
   DefineSysName(93, "JET_JER_EffectiveNP_1__1down", ProcessName);
   DefineSysName(94, "JET_JER_EffectiveNP_1__1up", ProcessName);
   DefineSysName(95, "JET_JER_EffectiveNP_2__1down", ProcessName);
   DefineSysName(96, "JET_JER_EffectiveNP_2__1up", ProcessName);
   DefineSysName(97, "JET_JER_EffectiveNP_3__1down", ProcessName);
   DefineSysName(98, "JET_JER_EffectiveNP_3__1up", ProcessName);
   DefineSysName(99, "JET_JER_EffectiveNP_4__1down", ProcessName);
   DefineSysName(100, "JET_JER_EffectiveNP_4__1up", ProcessName);
   DefineSysName(101, "JET_JER_EffectiveNP_5__1down", ProcessName);
   DefineSysName(102, "JET_JER_EffectiveNP_5__1up", ProcessName);
   DefineSysName(103, "JET_JER_EffectiveNP_6__1down", ProcessName);
   DefineSysName(104, "JET_JER_EffectiveNP_6__1up", ProcessName);
   DefineSysName(105, "JET_JER_EffectiveNP_7restTerm__1down", ProcessName);
   DefineSysName(106, "JET_JER_EffectiveNP_7restTerm__1up", ProcessName);
   DefineSysName(107, "JET_JvtEfficiency__1down", ProcessName);
   DefineSysName(108, "JET_JvtEfficiency__1up", ProcessName);

   //new jet systematic
   DefineSysName(109, "JET_Pileup_OffsetMu__1down", ProcessName);
   DefineSysName(110, "JET_Pileup_OffsetMu__1up", ProcessName);
   DefineSysName(111, "JET_Pileup_OffsetNPV__1down", ProcessName);
   DefineSysName(112, "JET_Pileup_OffsetNPV__1up", ProcessName);
   DefineSysName(113, "JET_Pileup_PtTerm__1down", ProcessName);
   DefineSysName(114, "JET_Pileup_PtTerm__1up", ProcessName);
   DefineSysName(115, "JET_Pileup_RhoTopology__1down", ProcessName);
   DefineSysName(116, "JET_Pileup_RhoTopology__1up", ProcessName);
   DefineSysName(117, "JET_PunchThrough_MC16__1down", ProcessName);
   DefineSysName(118, "JET_PunchThrough_MC16__1up", ProcessName);
   DefineSysName(119, "JET_SingleParticle_HighPt__1down", ProcessName);
   DefineSysName(120, "JET_SingleParticle_HighPt__1up", ProcessName);
   //

   DefineSysName(121, "JET_fJvtEfficiency__1down", ProcessName);
   DefineSysName(122, "JET_fJvtEfficiency__1up", ProcessName);

   DefineSysName(123, "MET_SoftTrk_ResoPara__1down", ProcessName);
   DefineSysName(124, "MET_SoftTrk_ResoPara__1up", ProcessName);
   DefineSysName(125, "MET_SoftTrk_ResoPerp__1down", ProcessName);
   DefineSysName(126, "MET_SoftTrk_ResoPerp__1up", ProcessName);
   DefineSysName(127, "MET_SoftTrk_ScaleDown__1down", ProcessName);
   DefineSysName(128, "MET_SoftTrk_ScaleUp__1up", ProcessName);
   DefineSysName(129, "MUON_EFF_ISO_STAT__1down", ProcessName);
   DefineSysName(130, "MUON_EFF_ISO_STAT__1up", ProcessName);
   DefineSysName(131, "MUON_EFF_ISO_SYS__1down", ProcessName);
   DefineSysName(132, "MUON_EFF_ISO_SYS__1up", ProcessName);
   DefineSysName(133, "MUON_EFF_RECO_STAT__1down", ProcessName);
   DefineSysName(134, "MUON_EFF_RECO_STAT__1up", ProcessName);
   DefineSysName(135, "MUON_EFF_RECO_STAT_LOWPT__1down", ProcessName);
   DefineSysName(136, "MUON_EFF_RECO_STAT_LOWPT__1up", ProcessName);
   DefineSysName(137, "MUON_EFF_RECO_SYS__1down", ProcessName);
   DefineSysName(138, "MUON_EFF_RECO_SYS__1up", ProcessName);
   DefineSysName(139, "MUON_EFF_RECO_SYS_LOWPT__1down", ProcessName);
   DefineSysName(140, "MUON_EFF_RECO_SYS_LOWPT__1up", ProcessName);
   DefineSysName(141, "MUON_EFF_TTVA_STAT__1down", ProcessName);
   DefineSysName(142, "MUON_EFF_TTVA_STAT__1up", ProcessName);
   DefineSysName(143, "MUON_EFF_TTVA_SYS__1down", ProcessName);
   DefineSysName(144, "MUON_EFF_TTVA_SYS__1up", ProcessName);
   DefineSysName(145, "MUON_ID__1down", ProcessName);
   DefineSysName(146, "MUON_ID__1up", ProcessName);
   DefineSysName(147, "MUON_MS__1down", ProcessName);
   DefineSysName(148, "MUON_MS__1up", ProcessName);
   DefineSysName(149, "MUON_SAGITTA_RESBIAS__1down", ProcessName);
   DefineSysName(150, "MUON_SAGITTA_RESBIAS__1up", ProcessName);
   DefineSysName(151, "MUON_SAGITTA_RHO__1down", ProcessName);
   DefineSysName(152, "MUON_SAGITTA_RHO__1up", ProcessName);
   DefineSysName(153, "MUON_SCALE__1down", ProcessName);
   DefineSysName(154, "MUON_SCALE__1up", ProcessName);
   DefineSysName(155, "PRW_DATASF__1down", ProcessName);
   DefineSysName(156, "PRW_DATASF__1up", ProcessName);

   DefineSysName(157, "FakeBkg_Stat__1down", ProcessName);
   DefineSysName(158, "FakeBkg_Stat__1up", ProcessName);
   DefineSysName(159, "FakeBkg_MetCut__1down", ProcessName);
   DefineSysName(160, "FakeBkg_MetCut__1up", ProcessName);
   DefineSysName(161, "PDFUncertainty__1down", ProcessName);
   DefineSysName(162, "PDFUncertainty__1up", ProcessName);
   DefineSysName(163, "ScaleUncertainty__1down", ProcessName);
   DefineSysName(164, "ScaleUncertainty__1up", ProcessName);
   //DefineSysName(165, "FakeBkg_20per__1down", ProcessName);
   //DefineSysName(166, "FakeBkg_20per__1up", ProcessName);

 }

}

void HistsWZPolarization::InitialBkgName(TString ProcessName)
{
 if(ProcessName == "SignalWZ"){
   BkgNameSignalWZ.push_back("BkgZZ");
   BkgNameSignalWZ.push_back("BkgZjet");
   BkgNameSignalWZ.push_back("BkgVVV");
   BkgNameSignalWZ.push_back("BkgWZEW");
   BkgNameSignalWZ.push_back("BkgZgamma");
   BkgNameSignalWZ.push_back("BkgttbarV");
   BkgNameSignalWZ.push_back("BkgTop");
   BkgNameSignalWZ.push_back("BkgtZ");
   BkgNameSignalWZ.push_back("BkgWZQCD");
   BkgNameSignalWZ.push_back("Data");

   for(int i = 0; i < BkgNameSignalWZ.size(); i++){
     BkgNameIndexSignalWZ[BkgNameSignalWZ.at(i)] = i;
   }

 }

 if(ProcessName == "ZZControlRegion"){
   BkgNameZZControlRegion.push_back("BkgZZ");
   BkgNameZZControlRegion.push_back("BkgZjet");
   BkgNameZZControlRegion.push_back("BkgVVV");
   BkgNameZZControlRegion.push_back("BkgWZEW");
   BkgNameZZControlRegion.push_back("BkgZgamma");
   BkgNameZZControlRegion.push_back("BkgttbarV");
   BkgNameZZControlRegion.push_back("BkgTop");
   BkgNameZZControlRegion.push_back("BkgtZ");
   BkgNameZZControlRegion.push_back("BkgWZQCD");
   BkgNameZZControlRegion.push_back("Data");

   for(int i = 0; i < BkgNameZZControlRegion.size(); i++){
     BkgNameIndexZZControlRegion[BkgNameZZControlRegion.at(i)] = i;
   }

 }

 if(ProcessName == "TopControlRegion"){
   BkgNameTopControlRegion.push_back("BkgZZ");
   BkgNameTopControlRegion.push_back("BkgZjet");
   BkgNameTopControlRegion.push_back("BkgVVV");
   BkgNameTopControlRegion.push_back("BkgWZEW");
   BkgNameTopControlRegion.push_back("BkgZgamma");
   BkgNameTopControlRegion.push_back("BkgttbarV");
   BkgNameTopControlRegion.push_back("BkgTop");
   BkgNameTopControlRegion.push_back("BkgtZ");
   BkgNameTopControlRegion.push_back("BkgWZQCD");
   BkgNameTopControlRegion.push_back("Data");

   for(int i = 0; i < BkgNameTopControlRegion.size(); i++){
     BkgNameIndexTopControlRegion[BkgNameTopControlRegion.at(i)] = i;
   } 
   
 } 

 if(ProcessName == "WZPolarized"){
   BkgNameWZPolarized.push_back("Total");
   BkgNameWZPolarized.push_back("LL");
   BkgNameWZPolarized.push_back("LT");
   BkgNameWZPolarized.push_back("TL");
   BkgNameWZPolarized.push_back("TT");

   for(int i = 0; i < BkgNameWZPolarized.size(); i++){
     BkgNameIndexWZPolarized[BkgNameWZPolarized.at(i)] = i;
   }

 }

}

void HistsWZPolarization::GetReweightFactor()
{
 myLog<<LOG_INFO<<"Calculate the reweighting factor:"<<endl;

 TH1D* denomHist = (TH1D *)((Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL"))->Clone("Pt_WZ_Merged");
 denomHist->Add((Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT"));
 denomHist->Add((Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL"));
 denomHist->Add((Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT"));

 ReweightFactor = (TH1D *)((Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("Total"))->Clone("ReweightFactor");
 ReweightFactor->Divide(denomHist);

 (Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("Total")->Reset();
 (Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Reset();
 (Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Reset();
 (Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Reset();
 (Pt_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Reset();

 delete denomHist;

 TH1D* denomHistTruth = (TH1D *)((Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("LL"))->Clone("Pt_WZ_Merged_Truth");
 denomHistTruth->Add((Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("LT"));
 denomHistTruth->Add((Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("TL"));
 denomHistTruth->Add((Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("TT"));

 ReweightFactor_Truth = (TH1D *)((Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("Total"))->Clone("ReweightFactor_Truth");
 ReweightFactor_Truth->Divide(denomHistTruth);

 (Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("Total")->Reset();
 (Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("LL")->Reset();
 (Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("LT")->Reset();
 (Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("TL")->Reset();
 (Pt_WZ->TruthInclusive_bkg->HistPtr(0))->GetHistPtr("TT")->Reset();

 delete denomHistTruth;

 hf->cd();
 ReweightFactor->Write();
 ReweightFactor_Truth->Write();

 isHaveReweightingFactor = true;

 myLog<<LOG_INFO<<"Reweighting Factor:"<<endl;
 myLog<<LOG_INFO;
 for(int i = 0; i < ReweightFactor->GetNbinsX(); i++){
   myLog<<fixed<<setprecision(3)<<ReweightFactor->GetBinCenter(i + 1);
   myLog<<": ";
   myLog<<fixed<<setprecision(3)<<ReweightFactor->GetBinContent(i + 1);
   myLog<<" +- ";
   myLog<<fixed<<setprecision(3)<<ReweightFactor->GetBinError(i + 1)<<endl;
 }

 Pt_WZ->ResetHist();

 myLog<<LOG_INFO<<"Get Reweight Factor Finished."<<endl;
}

void HistsWZPolarization::GetFakeRate()
{
 if(doFakeRate){
   myLog<<LOG_INFO<<"Calculate fake rate."<<endl;

//Fake Rate
   ZElFakeRate = (TH1D *)Lep3Pt_TopEl_PassZ->HistPtr(0)->Clone("ZElFakeRate");
   //ZElFakeRate->Divide(Lep3Pt_TopEl_UnPassZ->HistPtr(0));
   ZElFakeRate->Reset();
   for(int ibin = 1; ibin <= Lep3Pt_TopEl_PassZ->HistPtr(0)->GetNbinsX(); ibin++){
     double Numer = Lep3Pt_TopEl_PassZ->HistPtr(0)->GetBinContent(ibin);
     double Denom = Lep3Pt_TopEl_UnPassZ->HistPtr(0)->GetBinContent(ibin);

     double NumerError = Lep3Pt_TopEl_PassZ->HistPtr(0)->GetBinError(ibin);
     double DenomError = Lep3Pt_TopEl_UnPassZ->HistPtr(0)->GetBinError(ibin);

     double Value = 0.0;
     double ValueError = 0.0;
     if(Denom < 1e-5) continue;
     Value = Numer / Denom;
     ValueError = sqrt(Numer * Numer * DenomError * DenomError + Denom * Denom * NumerError * NumerError) / (Denom * Denom);

     ZElFakeRate->SetBinContent(ibin, Value);
     ZElFakeRate->SetBinError(ibin, ValueError);
   }

   ZMuFakeRate = (TH1D *)Lep3Pt_TopMu_PassZ->HistPtr(0)->Clone("ZMuFakeRate");
   //ZMuFakeRate->Divide(Lep3Pt_TopMu_UnPassZ->HistPtr(0));
   ZMuFakeRate->Reset();
   for(int ibin = 1; ibin <= Lep3Pt_TopMu_PassZ->HistPtr(0)->GetNbinsX(); ibin++){
     double Numer = Lep3Pt_TopMu_PassZ->HistPtr(0)->GetBinContent(ibin);
     double Denom = Lep3Pt_TopMu_UnPassZ->HistPtr(0)->GetBinContent(ibin);

     double NumerError = Lep3Pt_TopMu_PassZ->HistPtr(0)->GetBinError(ibin);
     double DenomError = Lep3Pt_TopMu_UnPassZ->HistPtr(0)->GetBinError(ibin);

     double Value = 0.0;
     double ValueError = 0.0;
     if(Denom < 1e-5) continue;
     Value = Numer / Denom;
     ValueError = sqrt(Numer * Numer * DenomError * DenomError + Denom * Denom * NumerError * NumerError) / (Denom * Denom);

     ZMuFakeRate->SetBinContent(ibin, Value);
     ZMuFakeRate->SetBinError(ibin, ValueError);
   }

   WElFakeRate = (TH1D *)Lep3Pt_ZFakeEl_PassW->HistPtr(0)->Clone("WElFakeRate");
   //WElFakeRate->Divide(Lep3Pt_ZFakeEl_UnPassW->HistPtr(0));
   WElFakeRate->Reset();
   for(int ibin = 1; ibin <= Lep3Pt_ZFakeEl_PassW->HistPtr(0)->GetNbinsX(); ibin++){
     double Numer = Lep3Pt_ZFakeEl_PassW->HistPtr(0)->GetBinContent(ibin);
     double Denom = Lep3Pt_ZFakeEl_UnPassW->HistPtr(0)->GetBinContent(ibin);

     double NumerError = Lep3Pt_ZFakeEl_PassW->HistPtr(0)->GetBinError(ibin);
     double DenomError = Lep3Pt_ZFakeEl_UnPassW->HistPtr(0)->GetBinError(ibin);

     double Value = 0.0;
     double ValueError = 0.0;
     if(Denom < 1e-5) continue;
     Value = Numer / Denom;
     ValueError = sqrt(Numer * Numer * DenomError * DenomError + Denom * Denom * NumerError * NumerError) / (Denom * Denom);

     WElFakeRate->SetBinContent(ibin, Value);
     WElFakeRate->SetBinError(ibin, ValueError);
   }

   WElFakeRate_UpSys = (TH1D *)Lep3Pt_ZFakeEl_UpSys_PassW->HistPtr(0)->Clone("WElFakeRate_UpSys");
   WElFakeRate_UpSys->Divide(Lep3Pt_ZFakeEl_UpSys_UnPassW->HistPtr(0));

   WElFakeRate_DownSys = (TH1D *)Lep3Pt_ZFakeEl_DownSys_PassW->HistPtr(0)->Clone("WElFakeRate_DownSys");
   WElFakeRate_DownSys->Divide(Lep3Pt_ZFakeEl_DownSys_UnPassW->HistPtr(0));

   WMuFakeRate = (TH1D *)Lep3Pt_ZFakeMu_PassW->HistPtr(0)->Clone("WMuFakeRate");
   //WMuFakeRate->Divide(Lep3Pt_ZFakeMu_UnPassW->HistPtr(0));
   WMuFakeRate->Reset();
   for(int ibin = 1; ibin <= Lep3Pt_ZFakeMu_PassW->HistPtr(0)->GetNbinsX(); ibin++){
     double Numer = Lep3Pt_ZFakeMu_PassW->HistPtr(0)->GetBinContent(ibin);
     double Denom = Lep3Pt_ZFakeMu_UnPassW->HistPtr(0)->GetBinContent(ibin);

     double NumerError = Lep3Pt_ZFakeMu_PassW->HistPtr(0)->GetBinError(ibin);
     double DenomError = Lep3Pt_ZFakeMu_UnPassW->HistPtr(0)->GetBinError(ibin);

     double Value = 0.0;
     double ValueError = 0.0;
     if(Denom < 1e-5) continue;
     Value = Numer / Denom;
     ValueError = sqrt(Numer * Numer * DenomError * DenomError + Denom * Denom * NumerError * NumerError) / (Denom * Denom);

     WMuFakeRate->SetBinContent(ibin, Value);
     WMuFakeRate->SetBinError(ibin, ValueError);
   }

//Fake Efficiency
   ZElFakeEff = (TH1D *)Lep3Pt_TopEl_PassZ->HistPtr(0)->Clone("ZElFakeEff");
   ZElFakeEff->Divide(Lep3Pt_TopEl_Loose->HistPtr(0));

   ZMuFakeEff = (TH1D *)Lep3Pt_TopMu_PassZ->HistPtr(0)->Clone("ZMuFakeEff");
   ZMuFakeEff->Divide(Lep3Pt_TopMu_Loose->HistPtr(0));

   WElFakeEff = (TH1D *)Lep3Pt_ZFakeEl_PassW->HistPtr(0)->Clone("WElFakeEff");
   WElFakeEff->Divide(Lep3Pt_ZFakeEl_Loose->HistPtr(0));

   WMuFakeEff = (TH1D *)Lep3Pt_ZFakeMu_PassW->HistPtr(0)->Clone("WMuFakeEff");
   WMuFakeEff->Divide(Lep3Pt_ZFakeMu_Loose->HistPtr(0));

//Real Efficiency
   ZElRealEff = (TH1D *)Lep3Pt_RealEl_PassZ->HistPtr(0)->Clone("ZElRealEff");
   ZElRealEff->Divide(Lep3Pt_RealEl_Loose->HistPtr(0));

   ZMuRealEff = (TH1D *)Lep3Pt_RealMu_PassZ->HistPtr(0)->Clone("ZMuRealEff");
   ZMuRealEff->Divide(Lep3Pt_RealMu_Loose->HistPtr(0));

   WElRealEff = (TH1D *)Lep3Pt_RealEl_PassW->HistPtr(0)->Clone("WElRealEff");
   WElRealEff->Divide(Lep3Pt_RealEl_Loose->HistPtr(0));

   WMuRealEff = (TH1D *)Lep3Pt_RealMu_PassW->HistPtr(0)->Clone("WMuRealEff");
   WMuRealEff->Divide(Lep3Pt_RealMu_Loose->HistPtr(0));

//for validation test
   ZFakeElCR_ZRate = (TH1D *)Lep3Pt_ZFakeEl_PassZ->HistPtr(0)->Clone("ZFakeElCR_ZRate");
   ZFakeElCR_ZRate->Divide(Lep3Pt_ZFakeEl_UnPassZ->HistPtr(0));

   ZFakeElCR_UpSys_ZRate = (TH1D *)Lep3Pt_ZFakeEl_UpSys_PassZ->HistPtr(0)->Clone("ZFakeElCR_ZRate_UpSys");
   ZFakeElCR_UpSys_ZRate->Divide(Lep3Pt_ZFakeEl_UpSys_UnPassZ->HistPtr(0));

   ZFakeElCR_DownSys_ZRate = (TH1D *)Lep3Pt_ZFakeEl_DownSys_PassZ->HistPtr(0)->Clone("ZFakeElCR_ZRate_DownSys");
   ZFakeElCR_DownSys_ZRate->Divide(Lep3Pt_ZFakeEl_DownSys_UnPassZ->HistPtr(0));

   ZFakeElCR_WRate = (TH1D *)Lep3Pt_ZFakeEl_PassW->HistPtr(0)->Clone("ZFakeElCR_WRate");
   ZFakeElCR_WRate->Divide(Lep3Pt_ZFakeEl_UnPassW->HistPtr(0));

   ZFakeElCR_UpSys_WRate = (TH1D *)Lep3Pt_ZFakeEl_UpSys_PassW->HistPtr(0)->Clone("ZFakeElCR_WRate_UpSys");
   ZFakeElCR_UpSys_WRate->Divide(Lep3Pt_ZFakeEl_UpSys_UnPassW->HistPtr(0));

   ZFakeElCR_DownSys_WRate = (TH1D *)Lep3Pt_ZFakeEl_DownSys_PassW->HistPtr(0)->Clone("ZFakeElCR_WRate_DownSys");
   ZFakeElCR_DownSys_WRate->Divide(Lep3Pt_ZFakeEl_DownSys_UnPassW->HistPtr(0));

   ZFakeMuCR_ZRate = (TH1D *)Lep3Pt_ZFakeMu_PassZ->HistPtr(0)->Clone("ZFakeMuCR_ZRate");
   ZFakeMuCR_ZRate->Divide(Lep3Pt_ZFakeMu_UnPassZ->HistPtr(0));

   ZFakeMuCR_WRate = (TH1D *)Lep3Pt_ZFakeMu_PassW->HistPtr(0)->Clone("ZFakeMuCR_WRate");
   ZFakeMuCR_WRate->Divide(Lep3Pt_ZFakeMu_UnPassW->HistPtr(0));

   TopElCR_ZRate = (TH1D *)Lep3Pt_TopEl_PassZ->HistPtr(0)->Clone("TopElCR_ZRate");
   TopElCR_ZRate->Divide(Lep3Pt_TopEl_UnPassZ->HistPtr(0));

   TopElCR_WRate = (TH1D *)Lep3Pt_TopEl_PassW->HistPtr(0)->Clone("TopElCR_WRate");
   TopElCR_WRate->Divide(Lep3Pt_TopEl_UnPassW->HistPtr(0));

   TopMuCR_ZRate = (TH1D *)Lep3Pt_TopMu_PassZ->HistPtr(0)->Clone("TopMuCR_ZRate");
   TopMuCR_ZRate->Divide(Lep3Pt_TopMu_UnPassZ->HistPtr(0));

   TopMuCR_WRate = (TH1D *)Lep3Pt_TopMu_PassW->HistPtr(0)->Clone("TopMuCR_WRate");
   TopMuCR_WRate->Divide(Lep3Pt_TopMu_UnPassW->HistPtr(0));


   ZFakeElCR_ZRate2 = (TH1D *)Lep2Pt_ZFakeEl_PassZ->HistPtr(0)->Clone("ZFakeElCR_ZRate2");
   ZFakeElCR_ZRate2->Divide(Lep2Pt_ZFakeEl_UnPassZ->HistPtr(0));

   ZFakeMuCR_ZRate2 = (TH1D *)Lep2Pt_ZFakeMu_PassZ->HistPtr(0)->Clone("ZFakeMuCR_ZRate2");
   ZFakeMuCR_ZRate2->Divide(Lep2Pt_ZFakeMu_UnPassZ->HistPtr(0));

   TopElCR_ZRate2 = (TH1D *)Lep2Pt_TopEl_PassZ->HistPtr(0)->Clone("TopElCR_ZRate2");
   TopElCR_ZRate2->Divide(Lep2Pt_TopEl_UnPassZ->HistPtr(0));

   TopMuCR_ZRate2 = (TH1D *)Lep2Pt_TopMu_PassZ->HistPtr(0)->Clone("TopMuCR_ZRate2");
   TopMuCR_ZRate2->Divide(Lep2Pt_TopMu_UnPassZ->HistPtr(0));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fake rate correction
   ZFakeEl_LargeMtW = (TH1D *)Lep3Pt_ZFakeEl_LargeMtW_PassW->HistPtr(0)->Clone("ZFakeEl_LargeMtW");
   ZFakeEl_LargeMtW->Divide(Lep3Pt_ZFakeEl_LargeMtW_UnPassW->HistPtr(0));

   ZFakeMu_LargeMtW = (TH1D *)Lep3Pt_ZFakeMu_LargeMtW_PassW->HistPtr(0)->Clone("ZFakeMu_LargeMtW");
   ZFakeMu_LargeMtW->Divide(Lep3Pt_ZFakeMu_LargeMtW_UnPassW->HistPtr(0));

   ZFakeEl_LowMtW = (TH1D *)Lep3Pt_ZFakeEl_LowMtW_PassW->HistPtr(0)->Clone("ZFakeEl_LowMtW");
   ZFakeEl_LowMtW->Divide(Lep3Pt_ZFakeEl_LowMtW_UnPassW->HistPtr(0));

   ZFakeMu_LowMtW = (TH1D *)Lep3Pt_ZFakeMu_LowMtW_PassW->HistPtr(0)->Clone("ZFakeMu_LowMtW");
   ZFakeMu_LowMtW->Divide(Lep3Pt_ZFakeMu_LowMtW_UnPassW->HistPtr(0));

   ZFakeEl_Correction = (TH1D *)ZFakeEl_LargeMtW->Clone("ZFakeEl_Correction");
   ZFakeEl_Correction->Divide(ZFakeEl_LowMtW);

   ZFakeMu_Correction = (TH1D *)ZFakeMu_LargeMtW->Clone("ZFakeMu_Correction");
   ZFakeMu_Correction->Divide(ZFakeMu_LowMtW);

   myLog<<LOG_INFO<<"ZFakeElCorrectionValue: ";
   for(int ibin = 1; ibin <= ZFakeEl_Correction->GetNbinsX(); ibin++){
     double ZFakeElCorrectionValue = ZFakeEl_Correction->GetBinContent(ibin);
     double ZFakeElCorrectionError = ZFakeEl_Correction->GetBinError(ibin);
     myLog<<fixed<<setprecision(3)<<ZFakeElCorrectionValue;
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeElCorrectionError;
     myLog<<"   ";

     double FakeRate = WElFakeRate->GetBinContent(ibin);
     //WElFakeRate->SetBinContent(ibin, FakeRate * ZFakeElCorrectionValue);
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZFakeMuCorrectionValue: ";
   for(int ibin = 1; ibin <= ZFakeMu_Correction->GetNbinsX(); ibin++){
     double ZFakeMuCorrectionValue = ZFakeMu_Correction->GetBinContent(ibin);
     double ZFakeMuCorrectionError = ZFakeMu_Correction->GetBinError(ibin);
     myLog<<fixed<<setprecision(3)<<ZFakeMuCorrectionValue;
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeMuCorrectionError;
     myLog<<"   ";

     double FakeRate = WMuFakeRate->GetBinContent(ibin);
     //WMuFakeRate->SetBinContent(ibin, FakeRate * ZFakeMuCorrectionValue);
   }
   myLog<<endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// using Ioannis' fake rate

   //InputCustomFakeRate();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   myLog<<LOG_INFO<<"ZEl Fake rate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZElFakeRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZElFakeRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZElFakeRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;
   myLog<<LOG_INFO<<"ZEl Fake control region:"<<endl;
   myLog<<LOG_INFO<<"Loose   Medium   passZCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_TopEl_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopEl_PassMedium->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopEl_PassZ->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<"Loose   Tight    passWCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_TopEl_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopEl_PassTight->HistPtr(0)->Integral();
   myLog<<"    ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopEl_PassW->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<endl;

   myLog<<LOG_INFO<<"ZMu Fake rate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZMuFakeRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZMuFakeRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZMuFakeRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;
   myLog<<LOG_INFO<<"ZMu Fake control region:"<<endl;
   myLog<<LOG_INFO<<"Loose   Medium   passZCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_TopMu_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopMu_PassMedium->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopMu_PassZ->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<"Loose   Tight    passWCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_TopMu_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopMu_PassTight->HistPtr(0)->Integral();
   myLog<<"    ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_TopMu_PassW->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<endl;

   myLog<<LOG_INFO<<"WEl Fake rate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < WElFakeRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<WElFakeRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<WElFakeRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;
   myLog<<LOG_INFO<<"WEl Fake control region:"<<endl;
   myLog<<LOG_INFO<<"Loose   Medium   passZCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_ZFakeEl_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeEl_PassMedium->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeEl_PassZ->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<"Loose   Tight    passWCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_ZFakeEl_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeEl_PassTight->HistPtr(0)->Integral();
   myLog<<"    ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeEl_PassW->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<endl;

   myLog<<LOG_INFO<<"WMu Fake rate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < WMuFakeRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<WMuFakeRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<WMuFakeRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;
   myLog<<LOG_INFO<<"WMu Fake control region:"<<endl;
   myLog<<LOG_INFO<<"Loose   Medium   passZCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_ZFakeMu_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeMu_PassMedium->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeMu_PassZ->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<"Loose   Tight    passWCondition"<<endl;
   myLog<<LOG_INFO<<fixed<<setprecision(3)<<Lep3Pt_ZFakeMu_Loose->HistPtr(0)->Integral();
   myLog<<"   ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeMu_PassTight->HistPtr(0)->Integral();
   myLog<<"    ";
   myLog<<fixed<<setprecision(3)<<Lep3Pt_ZFakeMu_PassW->HistPtr(0)->Integral()<<endl;
   myLog<<LOG_INFO<<endl;

   myLog<<LOG_INFO<<endl;

   myLog<<LOG_INFO<<"ZFakeEl ZRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZFakeElCR_ZRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZFakeElCR_ZRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeElCR_ZRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZFakeEl WRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZFakeElCR_WRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZFakeElCR_WRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeElCR_WRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZFakeMu ZRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZFakeMuCR_ZRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZFakeMuCR_ZRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeMuCR_ZRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZFakeMu WRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZFakeMuCR_WRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZFakeMuCR_WRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeMuCR_WRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"TopEl ZRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < TopElCR_ZRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<TopElCR_ZRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<TopElCR_ZRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"TopEl WRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < TopElCR_WRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<TopElCR_WRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<TopElCR_WRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"TopMu ZRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < TopMuCR_ZRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<TopMuCR_ZRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<TopMuCR_ZRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"TopMu WRate:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < TopMuCR_WRate->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<TopMuCR_WRate->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<TopMuCR_WRate->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZFakeEl ZRate2:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZFakeElCR_ZRate2->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZFakeElCR_ZRate2->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeElCR_ZRate2->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZFakeMu ZRate2:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZFakeMuCR_ZRate2->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZFakeMuCR_ZRate2->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZFakeMuCR_ZRate2->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"TopEl ZRate2:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < TopElCR_ZRate2->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<TopElCR_ZRate2->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<TopElCR_ZRate2->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"TopMu ZRate2:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < TopMuCR_ZRate2->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<TopMuCR_ZRate2->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<TopMuCR_ZRate2->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;



   myLog<<LOG_INFO<<"ZEl Fake efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZElFakeEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZElFakeEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZElFakeEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZMu Fake efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZMuFakeEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZMuFakeEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZMuFakeEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"WEl Fake efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < WElFakeEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<WElFakeEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<WElFakeEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"WMu Fake efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < WMuFakeEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<WMuFakeEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<WMuFakeEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<endl;

   myLog<<LOG_INFO<<"ZEl Real efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZElRealEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZElRealEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZElRealEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"ZMu Real efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < ZMuRealEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<ZMuRealEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ZMuRealEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"WEl Real efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < WElRealEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<WElRealEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<WElRealEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   myLog<<LOG_INFO<<"WMu Real efficiency:"<<endl;
   myLog<<LOG_INFO;
   for(int i = 0; i < WMuRealEff->GetNbinsX(); i++){
     myLog<<fixed<<setprecision(3)<<WMuRealEff->GetBinContent(i + 1);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<WMuRealEff->GetBinError(i + 1)<<"   ";
   }
   myLog<<endl;

   ZFakeElCR_MET_WRate = (TH1D *)Lep3MET_ZFakeEl_PassW->HistPtr(0)->Clone("ZFakeElCR_MET_WRate");
   ZFakeElCR_MET_WRate->Divide(Lep3MET_ZFakeEl_UnPassW->HistPtr(0));

   ZFakeMuCR_MET_WRate = (TH1D *)Lep3MET_ZFakeMu_PassW->HistPtr(0)->Clone("ZFakeMuCR_MET_WRate");
   ZFakeMuCR_MET_WRate->Divide(Lep3MET_ZFakeMu_UnPassW->HistPtr(0));

   ZFakeElCR_PtMET_WRate = (TH2D *)Lep3PtMET_ZFakeEl_PassW->HistPtr(0)->Clone("ZFakeElCR_PtMET_WRate");
   ZFakeElCR_PtMET_WRate->Divide(Lep3PtMET_ZFakeEl_UnPassW->HistPtr(0));

   ZFakeMuCR_PtMET_WRate = (TH2D *)Lep3PtMET_ZFakeMu_PassW->HistPtr(0)->Clone("ZFakeMuCR_PtMET_WRate");
   ZFakeMuCR_PtMET_WRate->Divide(Lep3PtMET_ZFakeMu_UnPassW->HistPtr(0));

   AverageLep3Pt_Lep3MET_ZFakeEl_Loose = (TH1D *)AverageLep3Pt_Lep3MET_ZFakeEl_Loose_numer->HistPtr(0)->Clone("AverageLep3Pt_Lep3MET_ZFakeEl_Loose");
   AverageLep3Pt_Lep3MET_ZFakeEl_Loose->Divide(AverageLep3Pt_Lep3MET_ZFakeEl_Loose_denom->HistPtr(0));
   AverageLep3Pt_Lep3MET_ZFakeMu_Loose = (TH1D *)AverageLep3Pt_Lep3MET_ZFakeMu_Loose_numer->HistPtr(0)->Clone("AverageLep3Pt_Lep3MET_ZFakeMu_Loose");
   AverageLep3Pt_Lep3MET_ZFakeMu_Loose->Divide(AverageLep3Pt_Lep3MET_ZFakeMu_Loose_denom->HistPtr(0));

   AverageLep3Pt_Lep3MET_ZFakeEl_PassW = (TH1D *)AverageLep3Pt_Lep3MET_ZFakeEl_PassW_numer->HistPtr(0)->Clone("AverageLep3Pt_Lep3MET_ZFakeEl_PassW");
   AverageLep3Pt_Lep3MET_ZFakeEl_PassW->Divide(Lep3MET_ZFakeEl_PassW->HistPtr(0));
   AverageLep3Pt_Lep3MET_ZFakeMu_PassW = (TH1D *)AverageLep3Pt_Lep3MET_ZFakeMu_PassW_numer->HistPtr(0)->Clone("AverageLep3Pt_Lep3MET_ZFakeMu_PassW");
   AverageLep3Pt_Lep3MET_ZFakeMu_PassW->Divide(Lep3MET_ZFakeMu_PassW->HistPtr(0));

   AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW = (TH1D *)AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW_numer->HistPtr(0)->Clone("AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW");
   AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW->Divide(Lep3MET_ZFakeEl_UnPassW->HistPtr(0));
   AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW = (TH1D *)AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW_numer->HistPtr(0)->Clone("AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW");
   AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW->Divide(Lep3MET_ZFakeMu_UnPassW->HistPtr(0));

   double NLOError = 0.0;
   double LOError = 0.0;
   double LLError = 0.0;
   double LTError = 0.0;
   double TLError = 0.0;
   double TTError = 0.0;

   int NBins = (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("Total")->GetNbinsX();

   double NLO = (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   double LO = (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
             + (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
             + (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
             + (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor = NLO / LO;
   NLOKFactorError = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_ZZCR_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_ZZCR = NLO / LO;
   NLOKFactorError_ZZCR = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_ZZCR_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_HighPtZCR = NLO / LO;
   NLOKFactorError_HighPtZCR = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_HighPtZCR_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_Signal_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_Signal = NLO / LO;
   NLOKFactorError_Signal = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_Signal_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_SignalPtWZ = NLO / LO;
   NLOKFactorError_SignalPtWZ = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_SignalPtWZ_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_HighPtWZCR = NLO / LO;
   NLOKFactorError_HighPtWZCR = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_HighPtWZCR_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_LowPtWZCR = NLO / LO;
   NLOKFactorError_LowPtWZCR = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_LowPtWZCR_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_HighR21CR_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_HighR21CR = NLO / LO;
   NLOKFactorError_HighR21CR = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_HighR21CR_bkg->HistPtr(0))->Reset();

   NLO = (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
   LO = (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()
      + (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()
      + (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()
      + (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();

   (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("Total")->IntegralAndError(1, NBins, NLOError);
   (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("LL")->IntegralAndError(1, NBins, LLError);
   (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("LT")->IntegralAndError(1, NBins, LTError);
   (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("TL")->IntegralAndError(1, NBins, TLError);
   (PolarizedYield_LowR21CR_bkg->HistPtr(0))->GetHistPtr("TT")->IntegralAndError(1, NBins, TTError);

   LOError = sqrt(pow(LLError, 2) + pow(LTError, 2) + pow(TLError, 2) + pow(TTError, 2));

   NLOKFactor_LowR21CR = NLO / LO;
   NLOKFactorError_LowR21CR = DivideUncertainty(NLO, LO, NLOError, LOError);
   (PolarizedYield_LowR21CR_bkg->HistPtr(0))->Reset();


   myLog<<LOG_INFO<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(Inclusive): "<<NLOKFactor<<" +- "<<NLOKFactorError<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(ZZCR): "<<NLOKFactor_ZZCR<<" +- "<<NLOKFactorError_ZZCR<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(HighPtZCR): "<<NLOKFactor_HighPtZCR<<" +- "<<NLOKFactorError_HighPtZCR<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(Signal): "<<NLOKFactor_Signal<<" +- "<<NLOKFactorError_Signal<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(SignalPtWZ): "<<NLOKFactor_SignalPtWZ<<" +- "<<NLOKFactorError_SignalPtWZ<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(HighPtWZCR): "<<NLOKFactor_HighPtWZCR<<" +- "<<NLOKFactorError_HighPtWZCR<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(LowPtWZCR): "<<NLOKFactor_LowPtWZCR<<" +- "<<NLOKFactorError_LowPtWZCR<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(HighR21CR): "<<NLOKFactor_HighR21CR<<" +- "<<NLOKFactorError_HighR21CR<<endl;
   myLog<<LOG_INFO<<"NLO/LO KFactor(LowR21CR): "<<NLOKFactor_LowR21CR<<" +- "<<NLOKFactorError_LowR21CR<<endl;
   myLog<<LOG_INFO<<endl;


   hf->cd();
   ZFakeEl_Correction->Write();
   ZFakeMu_Correction->Write();
   ZElFakeRate->Write();
   ZMuFakeRate->Write();
   WElFakeRate->Write();
   WElFakeRate_UpSys->Write();
   WElFakeRate_DownSys->Write();
   WMuFakeRate->Write();

   ZElFakeEff->Write();
   ZMuFakeEff->Write();
   WElFakeEff->Write();
   WMuFakeEff->Write();

   ZElRealEff->Write();
   ZMuRealEff->Write();
   WElRealEff->Write();
   WMuRealEff->Write();

   ZFakeElCR_MET_WRate->Write();
   ZFakeMuCR_MET_WRate->Write();
   ZFakeElCR_PtMET_WRate->Write();
   ZFakeMuCR_PtMET_WRate->Write();

   AverageLep3Pt_Lep3MET_ZFakeEl_Loose->Write();
   AverageLep3Pt_Lep3MET_ZFakeMu_Loose->Write();
   AverageLep3Pt_Lep3MET_ZFakeEl_PassW->Write();
   AverageLep3Pt_Lep3MET_ZFakeMu_PassW->Write();
   AverageLep3Pt_Lep3MET_ZFakeEl_UnPassW->Write();
   AverageLep3Pt_Lep3MET_ZFakeMu_UnPassW->Write();

/*   v_Lep3Pt_TopEl_PassZ.at(0)->Write();
   v_Lep3Pt_TopEl_UnPassZ.at(0)->Write();
   v_Lep3Pt_TopEl_Loose.at(0)->Write();

   v_Lep3Pt_TopMu_PassZ.at(0)->Write();
   v_Lep3Pt_TopMu_UnPassZ.at(0)->Write();
   v_Lep3Pt_TopMu_Loose.at(0)->Write();

   v_Lep3Pt_ZFakeEl_PassW.at(0)->Write();
   v_Lep3Pt_ZFakeEl_UnPassW.at(0)->Write();
   v_Lep3Pt_ZFakeEl_Loose.at(0)->Write();

   v_Lep3Pt_ZFakeMu_PassW.at(0)->Write();
   v_Lep3Pt_ZFakeMu_UnPassW.at(0)->Write();
   v_Lep3Pt_ZFakeMu_Loose.at(0)->Write();

   v_Lep3Pt_RealEl_PassZ.at(0)->Write();
   v_Lep3Pt_RealEl_PassW.at(0)->Write();
   v_Lep3Pt_RealEl_Loose.at(0)->Write();

   v_Lep3Pt_RealMu_PassZ.at(0)->Write();
   v_Lep3Pt_RealMu_PassW.at(0)->Write();
   v_Lep3Pt_RealMu_Loose.at(0)->Write();
*/
   isHaveFakeRate = true;

   //if(doFakeRate != 3) ResetHists(TotalThread);
 }

}

void HistsWZPolarization::InputCustomFakeRate()
{

 //combined closure test
 WElFakeRate->SetBinContent(1, 0.0);
 WElFakeRate->SetBinContent(2, 0.0734687);
 WElFakeRate->SetBinContent(3, 0.0783253);
 WElFakeRate->SetBinContent(4, 0.0910589);
 WElFakeRate->SetBinError(1, 0.0);
 WElFakeRate->SetBinError(2, 0.0040881);
 WElFakeRate->SetBinError(3, 0.00565102);
 WElFakeRate->SetBinError(4, 0.00822201);

 WMuFakeRate->SetBinContent(1, 0.0);
 WMuFakeRate->SetBinContent(2, 0.0302803);
 WMuFakeRate->SetBinContent(3, 0.0505094);
 WMuFakeRate->SetBinContent(4, 0.346358);
 WMuFakeRate->SetBinError(1, 0.0);
 WMuFakeRate->SetBinError(2, 0.030301737);
 WMuFakeRate->SetBinError(3, 0.0084411);
 WMuFakeRate->SetBinError(4, 0.0684006);

/* ZElFakeRate->SetBinContent(1, 0.228279);
 ZElFakeRate->SetBinContent(2, 0.206844);
 ZElFakeRate->SetBinContent(3, 0.213209);
 ZElFakeRate->SetBinContent(4, 0.147465);
 ZElFakeRate->SetBinError(1, 0.0249397);
 ZElFakeRate->SetBinError(2, 0.0258126);
 ZElFakeRate->SetBinError(3, 0.0402289);
 ZElFakeRate->SetBinError(4, 0.0901404);

 ZMuFakeRate->SetBinContent(1, 0.0750562);
 ZMuFakeRate->SetBinContent(2, 0.0814114);
 ZMuFakeRate->SetBinContent(3, 0.115873);
 ZMuFakeRate->SetBinContent(4, 0.104415);
 ZMuFakeRate->SetBinError(1, 0.0116506);
 ZMuFakeRate->SetBinError(2, 0.0111932);
 ZMuFakeRate->SetBinError(3, 0.0173762);
 ZMuFakeRate->SetBinError(4, 0.0418808);
*/

/* 
 //Ioannis's result
 WElFakeRate->SetBinContent(1, 0.105930842);
 WElFakeRate->SetBinContent(2, 0.118513748);
 WElFakeRate->SetBinContent(3, 0.126037002);
 WElFakeRate->SetBinContent(4, 0.259912997);
 WElFakeRate->SetBinError(1, 0.004627747);
 WElFakeRate->SetBinError(2, 0.010312725);
 WElFakeRate->SetBinError(3, 0.03413394);
 WElFakeRate->SetBinError(4, 0.096576357);

 WMuFakeRate->SetBinContent(1, 0.021923086);
 WMuFakeRate->SetBinContent(2, 0.011866352);
 WMuFakeRate->SetBinContent(3, 0.0102319);
 WMuFakeRate->SetBinContent(4, 0.009915921);
 WMuFakeRate->SetBinError(1, 0.00273531);
 WMuFakeRate->SetBinError(2, 0.005767134);
 WMuFakeRate->SetBinError(3, 0.017088026);
 WMuFakeRate->SetBinError(4, 0.069377611);

 ZElFakeRate->SetBinContent(1, 0.263735324);
 ZElFakeRate->SetBinContent(2, 0.202896118);
 ZElFakeRate->SetBinContent(3, 0.126730695);
 ZElFakeRate->SetBinContent(4, 0.080129869);
 ZElFakeRate->SetBinError(1, 0.015698031);
 ZElFakeRate->SetBinError(2, 0.014737782);
 ZElFakeRate->SetBinError(3, 0.018542121);
 ZElFakeRate->SetBinError(4, 0.036672801);

 ZMuFakeRate->SetBinContent(1, 0.047517333);
 ZMuFakeRate->SetBinContent(2, 0.037170377);
 ZMuFakeRate->SetBinContent(3, 0.038069926);
 ZMuFakeRate->SetBinContent(4, 0.036758758);
 ZMuFakeRate->SetBinError(1, 0.004080116);
 ZMuFakeRate->SetBinError(2, 0.003724336);
 ZMuFakeRate->SetBinError(3, 0.004796156);
 ZMuFakeRate->SetBinError(4, 0.008475961);
*/

}

void HistsWZPolarization::SaveCustomFakePlot()
{
// isSaveCustomFakePlot = true;

 if(isSaveCustomFakePlot){
   cout<<"Save Custom Fake Plot:"<<endl;
   for(int ihist = 0; ihist < FakeHist_1d.size(); ihist++){
     if(FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Pt_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Channel_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "LepPt_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep1Pt_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep2Pt_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep2Pt_mmm_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep2Pt_mme_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep2Pt_eem_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep2Pt_eee_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Pt_mmm_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Pt_mme_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Pt_eem_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Pt_eee_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Eta_mmm_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Eta_mme_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Eta_eem_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Lep3Eta_eee_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Mt_W_mmm_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Mt_W_mme_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Mt_W_eem_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Mt_W_eee_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Met_mmm_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Met_mme_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Met_eem_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Met_eee_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Met_Inclusive"
     || FakeHist_1d.at(ihist)->HistPtr(0)->HistName == "Mt_W_Inclusive"){
       cout<<"Save "<<FakeHist_1d.at(ihist)->HistPtr(0)->HistName<<" fake plot."<<endl;
       FakeHist_1d.at(ihist)->HistPtr(0)->Write();
     }
   }
 }
}

void HistsWZPolarization::LinkClass(HistsWZPolarization *hist)
{
 FinalHists = hist;
}

void HistsWZPolarization::outputInformation()
{
//////////////////////////////////////////////////////////////////////////////////////////////

 if(doBkg && doFakeRate){
   for(int iprocesshist = 0; iprocesshist < hist_process.size(); iprocesshist++){
     hist_process.at(iprocesshist)->GetFinalData();
   }

   if(OnlyNominal){
     Ratio_Inclusive = (TH1D *)RightZYWLepEta->Inclusive_FinalData->Clone("Ratio_InclusiveData");
     Ratio_Inclusive->Divide(WrongZYWLepEta->Inclusive_FinalData);

     Ratio_Signal = (TH1D *)RightZYWLepEta->Signal_FinalData->Clone("Ratio_SignalData");
     Ratio_Signal->Divide(WrongZYWLepEta->Signal_FinalData);
// Ratio_HighPtWZCR = (TH1D *)RightZYWLepEta->HighPtWZCR_FinalData->Clone("Ratio_HighPtWZCRData");
// Ratio_HighPtWZCR->Divide(WrongZYWLepEta->HighPtWZCR_FinalData);

// Ratio_LowPtZCR = (TH1D *)RightZYWLepEta->LowPtZCR_FinalData->Clone("Ratio_LowPtZCRData");
// Ratio_LowPtZCR->Divide(WrongZYWLepEta->LowPtZCR_FinalData);

     Ratio_Inclusive->Write();
     Ratio_Signal->Write();
// Ratio_HighPtWZCR->Write();
// Ratio_LowPtZCR->Write();
  }
 }
//////////////////////////////////////////////////////////////////////////////////////////////

 if(doFakeRate) outputTeXInfo();

//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////

 /////////////////////////////////////////////////////
 //  Calculate the deep for testing the RAZ effect  //
 /////////////////////////////////////////////////////

 if(doBkg && doFakeRate){

   double DeepBinning[5] = {0, 10, 20, 40, 70};
   double DY_WZ_Binning[4] = {-1.5, -0.5, 0.5, 1.5};

   Deep_DY_WZ_TT = new TH1D("Deep_DY_WZ_TT", "Deep_DY_WZ_TT", 4, DeepBinning);
   Deep_DY_3Z_TT = new TH1D("Deep_DY_3Z_TT", "Deep_DY_3Z_TT", 4, DeepBinning);

   double DeepNumer, DeepDenom, DeepNumerError, DeepDenomError, DeepValue, DeepError;
   TH1D* Rebinned_DY_WZ_TT;

   //DY_WZ PtWZ < 10GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_WZ->PtWZ10CRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT->SetBinContent(1, DeepValue);
   Deep_DY_WZ_TT->SetBinError(1, DeepError);
   delete Rebinned_DY_WZ_TT;
   //DY_WZ PtWZ < 20GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_WZ->PtWZ20CRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT->SetBinContent(2, DeepValue);
   Deep_DY_WZ_TT->SetBinError(2, DeepError);
   delete Rebinned_DY_WZ_TT;
   //DY_WZ PtWZ < 40GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_WZ->PtWZ40CRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT->SetBinContent(3, DeepValue);
   Deep_DY_WZ_TT->SetBinError(3, DeepError);
   delete Rebinned_DY_WZ_TT;
   //DY_WZ PtWZ < 70GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_WZ->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT->SetBinContent(4, DeepValue);
   Deep_DY_WZ_TT->SetBinError(4, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //DY_3Z PtWZ < 10GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_3Z->PtWZ10CRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT->SetBinContent(1, DeepValue);
   Deep_DY_3Z_TT->SetBinError(1, DeepError);
   delete Rebinned_DY_WZ_TT;
   //DY_3Z PtWZ < 20GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_3Z->PtWZ20CRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT->SetBinContent(2, DeepValue);
   Deep_DY_3Z_TT->SetBinError(2, DeepError);
   delete Rebinned_DY_WZ_TT;
   //DY_3Z PtWZ < 40GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_3Z->PtWZ40CRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT->SetBinContent(3, DeepValue);
   Deep_DY_3Z_TT->SetBinError(3, DeepError);
   delete Rebinned_DY_WZ_TT;
   //DY_3Z PtWZ < 70GeV
   Rebinned_DY_WZ_TT = (TH1D *)((DY_3Z->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT"))->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT->SetBinContent(4, DeepValue);
   Deep_DY_3Z_TT->SetBinError(4, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   Deep_DY_WZ_TT->Write();
   Deep_DY_3Z_TT->Write();
  
   ///////////////////////
   //  Data Subtracted  //
   ///////////////////////
  
   Deep_DY_WZ_TT_DataSubtracted = new TH1D("Deep_DY_WZ_TT_DataSubtracted", "Deep_DY_WZ_TT_DataSubtracted", 4, DeepBinning);
   Deep_DY_3Z_TT_DataSubtracted = new TH1D("Deep_DY_3Z_TT_DataSubtracted", "Deep_DY_3Z_TT_DataSubtracted", 4, DeepBinning);
  
   //Data Subtracted DY_WZ PtWZ < 10GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_WZ->PtWZ10CR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT_DataSubtracted->SetBinContent(1, DeepValue);
   Deep_DY_WZ_TT_DataSubtracted->SetBinError(1, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_WZ PtWZ < 20GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_WZ->PtWZ20CR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT_DataSubtracted->SetBinContent(2, DeepValue);
   Deep_DY_WZ_TT_DataSubtracted->SetBinError(2, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_WZ PtWZ < 40GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_WZ->PtWZ40CR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT_DataSubtracted->SetBinContent(3, DeepValue);
   Deep_DY_WZ_TT_DataSubtracted->SetBinError(3, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_WZ PtWZ < 70GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_WZ->LowPtWZCR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_WZ_TT_DataSubtracted->SetBinContent(4, DeepValue);
   Deep_DY_WZ_TT_DataSubtracted->SetBinError(4, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_3Z PtWZ < 10GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_3Z->PtWZ10CR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT_DataSubtracted->SetBinContent(1, DeepValue);
   Deep_DY_3Z_TT_DataSubtracted->SetBinError(1, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_3Z PtWZ < 20GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_3Z->PtWZ20CR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT_DataSubtracted->SetBinContent(2, DeepValue);
   Deep_DY_3Z_TT_DataSubtracted->SetBinError(2, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_3Z PtWZ < 40GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_3Z->PtWZ40CR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT_DataSubtracted->SetBinContent(3, DeepValue);
   Deep_DY_3Z_TT_DataSubtracted->SetBinError(3, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   //Data Subtracted DY_3Z PtWZ < 70GeV
   Rebinned_DY_WZ_TT = (TH1D *)(DY_3Z->LowPtWZCR_FinalTT)->Rebin(3, "Rebinned_DY_WZ_TT", DY_WZ_Binning);
   DeepNumer = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0 - Rebinned_DY_WZ_TT->GetBinContent(2);
   DeepDenom = Rebinned_DY_WZ_TT->GetBinContent(1) / 2.0 + Rebinned_DY_WZ_TT->GetBinContent(3) / 2.0;
   DeepNumerError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(2) * Rebinned_DY_WZ_TT->GetBinError(2));
   DeepDenomError = sqrt(Rebinned_DY_WZ_TT->GetBinError(1) * Rebinned_DY_WZ_TT->GetBinError(1) * 0.25
                       + Rebinned_DY_WZ_TT->GetBinError(3) * Rebinned_DY_WZ_TT->GetBinError(3) * 0.25);
   DeepValue = DeepNumer / DeepDenom;
   DeepError = DivideUncertainty2(DeepNumer, DeepDenom, DeepNumerError, DeepDenomError);
   Deep_DY_3Z_TT_DataSubtracted->SetBinContent(4, DeepValue);
   Deep_DY_3Z_TT_DataSubtracted->SetBinError(4, DeepError);
   delete Rebinned_DY_WZ_TT;
  
   Deep_DY_WZ_TT_DataSubtracted->Write();
   Deep_DY_3Z_TT_DataSubtracted->Write();
 }
 
//////////////////////////////////////////////////////////////////////////////////////////////


 double Total;
 double LL, LT, TL, TT;

 myLog<<fixed<<setprecision(3);

 myLog<<LOG_INFO<<"Yield:"<<endl;
 myLog<<LOG_INFO<<"                LL          LT          TL          TT          Total          LL          LT          TL          TT"<<endl;
 LL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(1);
 LT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(1);
 TL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(1);
 TT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(1);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"All:           "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(2);
 LT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(2);
 TL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(2);
 TT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(2);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"WZInclusive:   "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(3);
 LT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(3);
 TL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(3);
 TT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(3);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"pT_Z > 200GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(4);
 LT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(4);
 TL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(4);
 TT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(4);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"R21 > 0.8: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(5);
 LT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(5);
 TL = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(5);
 TT = (Yield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(5);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"Pt_WZ < 70GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 myLog<<LOG_INFO<<endl;

 myLog<<LOG_INFO<<"Normalized Yield:"<<endl;
 myLog<<LOG_INFO<<"                LL          LT          TL          TT          Total          LL          LT          TL          TT"<<endl;
 LL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(1);
 LT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(1);
 TL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(1);
 TT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(1);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"All:           "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(2);
 LT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(2);
 TL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(2);
 TT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(2);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"WZInclusive:   "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(3);
 LT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(3);
 TL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(3);
 TT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(3);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"pT_Z > 200GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(4);
 LT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(4);
 TL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(4);
 TT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(4);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"R21 > 0.8: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(5);
 LT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(5);
 TL = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(5);
 TT = (NormalizedYield_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(5);
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"Pt_WZ < 70GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 myLog<<LOG_INFO<<endl;

 myLog<<LOG_INFO<<"Figure Integral:"<<endl;
 myLog<<LOG_INFO<<"                LL          LT          TL          TT          Total          LL          LT          TL          TT"<<endl;
 LL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(1) * NLOKFactor;
 LT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(1) * NLOKFactor;
 TL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(1) * NLOKFactor;
 TT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(1) * NLOKFactor;
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"All:           "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(2) * NLOKFactor;
 LT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(2) * NLOKFactor;
 TL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(2) * NLOKFactor;
 TT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(2) * NLOKFactor;
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"WZInclusive:   "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(6) * NLOKFactor;
 LT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(6) * NLOKFactor;
 TL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(6) * NLOKFactor;
 TT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(6) * NLOKFactor;
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"Pt_WZ < 70GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(3) * NLOKFactor;
 LT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(3) * NLOKFactor;
 TL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(3) * NLOKFactor;
 TT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(3) * NLOKFactor;
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"pT_Z > 200GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(4) * NLOKFactor;
 LT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(4) * NLOKFactor;
 TL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(4) * NLOKFactor;
 TT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(4) * NLOKFactor;
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"pT_Z > 100GeV && Pt_WZ > 70GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 LL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(5) * NLOKFactor;
 LT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(5) * NLOKFactor;
 TL = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(5) * NLOKFactor;
 TT = (Polarized_CutFlow_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(5) * NLOKFactor;
 Total = LL + LT + TL + TT;
 myLog<<LOG_INFO<<"pT_Z > 200GeV && Pt_WZ < 70GeV: "<<LL<<"      "<<LT<<"      "<<TL<<"      "<<TT<<"      "<<Total<<"      "<<LL/Total<<"      "<<LT/Total<<"      "<<TL/Total<<"      "<<TT/Total<<endl;

 myLog<<LOG_INFO<<endl;


 myLog<<LOG_INFO<<"       Inclusive        SignalRegion         HighPtWZCR        LowPtZCR"<<endl;
 Total = (DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
 LL = (DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Integral();
 LT = (DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Integral();
 TL = (DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Integral();
 TT = (DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();
 myLog<<LOG_INFO<<"Inclusive: Total: "<<Total<<" LL: "<<LL<<" LT: "<<LT<<" TL: "<<TL<<" TT: "<<TT<<" Ratio: "<<(Total / (LL + LT + TL + TT))<<endl;
 Total = (DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
 LL = (DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Integral();
 LT = (DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Integral();
 TL = (DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Integral();
 TT = (DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();
 myLog<<LOG_INFO<<"Signal: Total: "<<Total<<" LL: "<<LL<<" LT: "<<LT<<" TL: "<<TL<<" TT: "<<TT<<" Ratio: "<<(Total / (LL + LT + TL + TT))<<endl;
 Total = (DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("Total")->Integral();
 LL = (DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Integral();
 LT = (DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Integral();
 TL = (DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Integral();
 TT = (DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Integral();
 myLog<<LOG_INFO<<"HighPtWZ: Total: "<<Total<<" LL: "<<LL<<" LT: "<<LT<<" TL: "<<TL<<" TT: "<<TT<<" Ratio: "<<(Total / (LL + LT + TL + TT))<<endl;

 myLog<<LOG_INFO<<"Signal Yield:"<<endl;
 myLog<<LOG_INFO<<"Total: "<<(BkgYield_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(1)<<endl;
 myLog<<LOG_INFO<<"Inclusive: "<<(BkgYield_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(2)<<endl;
 myLog<<LOG_INFO<<"pT_Z > 200GeV: "<<(BkgYield_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(3)<<endl;
 myLog<<LOG_INFO<<"pT_WZ < 70GeV: "<<(BkgYield_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(4)<<endl;
 myLog<<LOG_INFO<<endl;

 myLog<<LOG_INFO<<endl;
 myLog<<LOG_INFO<<"       Inclusive        SignalRegion         HighPtWZCR        LowPtZCR"<<endl;
 myLog<<LOG_INFO<<"WLZL "<<(DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()<<"        "<<(DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()<<"         "<<(DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Integral()<<"        "<<endl;
 myLog<<LOG_INFO<<"WLZT "<<(DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()<<"        "<<(DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()<<"         "<<(DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Integral()<<"        "<<endl;
 myLog<<LOG_INFO<<"WTZL "<<(DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()<<"        "<<(DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()<<"         "<<(DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Integral()<<"        "<<endl;
 myLog<<LOG_INFO<<"WTZT "<<(DY_WZ->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Integral()<<"        "<<(DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Integral()<<"         "<<(DY_WZ->HighPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Integral()<<"        "<<endl;

 if(!doBkg) return;

 myLog<<LOG_INFO<<endl;
 myLog<<LOG_INFO<<"Inclusive:"<<endl;
 myLog<<LOG_INFO<<"       mmm             mme             eem             eee"<<endl;
 myLog<<LOG_INFO<<"Data: "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(2)<<"+-"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(2)<<"  ";
 myLog<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(3)<<"+-"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(3)<<"  ";
 myLog<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(4)<<"+-"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(4)<<"  ";
 myLog<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(5)<<"+-"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"WZQCD: "<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(2)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(2)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(3)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(3)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(4)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(4)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(5)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"LL: "<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(2)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(2)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(3)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(3)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(4)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(4)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(5)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"LT: "<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(2)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(2)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(3)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(3)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(4)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(4)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(5)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"TL: "<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(2)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(2)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(3)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(3)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(4)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(4)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(5)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"TT: "<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(2)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(2)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(3)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(3)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(4)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(4)<<"  ";
 myLog<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(5)<<"+-"<<(Channel->InclusivePolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"WZEW: "<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(2)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(2)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(3)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(3)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(4)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(4)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(5)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"ZZ: "<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(2)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(2)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(3)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(3)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(4)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(4)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(5)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"VVV: "<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(2)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(2)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(3)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(3)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(4)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(4)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(5)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"ttbarV: "<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(2)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(2)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(3)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(3)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(4)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(4)<<"  ";
 myLog<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(5)<<"+-"<<(Channel->Inclusive_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(5)<<endl;
 if(doFakeRate){
   myLog<<LOG_INFO<<"Fake: "<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(2)<<"+-"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(2)<<"  ";
   myLog<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(3)<<"+-"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(3)<<"  ";
   myLog<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(4)<<"+-"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(4)<<"  ";
   myLog<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(5)<<"+-"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(5)<<endl;
 }

 myLog<<LOG_INFO<<endl;
 myLog<<LOG_INFO<<"Pt_WZ < 70GeV:"<<endl;
 myLog<<LOG_INFO<<"       mmm             mme             eem             eee"<<endl;
 myLog<<LOG_INFO<<"Data: "<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCRPolarized_Data->HistPtr(0))->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"WZQCD: "<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"LL: "<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"LT: "<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"TL: "<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"TT: "<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCRPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"WZEW: "<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"ZZ: "<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"VVV: "<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"ttbarV: "<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(2)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(3)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(4)<<"  ";
 myLog<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCR_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(5)<<endl;
 if(doFakeRate){
   myLog<<LOG_INFO<<"Fake: "<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(2)<<"+-"<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinError(2)<<"  ";
   myLog<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(3)<<"+-"<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinError(3)<<"  ";
   myLog<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(4)<<"+-"<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinError(4)<<"  ";
   myLog<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(5)<<"+-"<<(Channel->LowPtWZCR_Fake->HistPtr(0))->FinalFakeHist->GetBinError(5)<<endl;
 }
 myLog<<LOG_INFO<<endl;
 myLog<<LOG_INFO<<"Pt_WZ < 70GeV && Pt_Z > 200GeV:"<<endl;
 myLog<<LOG_INFO<<"       mmm             mme             eem             eee"<<endl;
 myLog<<LOG_INFO<<"Data: "<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_Data->HistPtr(0))->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"WZQCD: "<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZQCD")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"LL: "<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"LT: "<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"TL: "<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"TT: "<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"WZEW: "<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgWZEW")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"ZZ: "<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgZZ")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"VVV: "<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgVVV")->GetBinError(5)<<endl;
 myLog<<LOG_INFO<<"ttbarV: "<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(2)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(3)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(4)<<"  ";
 myLog<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_bkg->HistPtr(0))->GetHistPtr("BkgttbarV")->GetBinError(5)<<endl;
 if(doFakeRate){
   myLog<<LOG_INFO<<"Fake: "<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(2)<<"+-"<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinError(2)<<"  ";
   myLog<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(3)<<"+-"<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinError(3)<<"  ";
   myLog<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(4)<<"+-"<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinError(4)<<"  ";
   myLog<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(5)<<"+-"<<(Channel->SignalPtWZ_Fake->HistPtr(0))->FinalFakeHist->GetBinError(5)<<endl;
 }

 for(int ihist = 0; ihist < hist_process.size(); ihist++){
   delete hist_process.at(ihist);
 }

}


////////////////////////////////////////
//////////   fitting code   ////////////
////////////////////////////////////////

void ScaleFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 if(!FinalHists->HaveMerged){
   cout<<"ERROR: The histogram has not been merged."<<endl;
   return;
 }

 double Chi2 = 0.0;

 TH1D* h1[4];

 h1[0] = (TH1D *)(FinalHists->DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LL")->Clone("LL");
 h1[0]->Scale(par[0]);
 h1[1] = (TH1D *)(FinalHists->DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("LT")->Clone("LT");
 h1[1]->Scale(par[1]);
 h1[2] = (TH1D *)(FinalHists->DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TL")->Clone("TL");
 h1[2]->Scale(par[2]);
 h1[3] = (TH1D *)(FinalHists->DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0))->GetHistPtr("TT")->Clone("TT");
 h1[3]->Scale(par[3]);

 h1[0]->Add(h1[1]);
 h1[0]->Add(h1[2]);
 h1[0]->Add(h1[3]);

 Chi2 = CalculateChi2WithData(h1[0], FinalHists->DY_WZ->SignalPtWZPolarized_bkg->HistPtr(0)->GetHistPtr("Total"));

 f = Chi2;

 if(f < Min_Chi2) Min_Chi2 = f;

 cout<<"Min Chi2 = "<<Min_Chi2<<endl;
}

