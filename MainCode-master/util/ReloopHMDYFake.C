#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include <Eigen/Dense>

using namespace std;

class FakeWeight
{
 public:

 TH2D* FakeEff;
 TH2D* RealEff;

 int passTT;
 int passTL;
 int passLT;
 int passLL;

 map<tuple<int, int, int, int, int, int, int, int>, Eigen::MatrixXd> MatrixMap;
 map<tuple<int, int, int, int, int, int, int, int>, Eigen::MatrixXd> InverseMatrixMap;

 double WeightRR;
 double WeightTL;
 double WeightTLirr;
 double WeightLT;
 double WeightLTirr;
 double WeightLL;
 double WeightLLirr;

 double FourTermTT;
 double FourTermTL;
 double FourTermLT;
 double FourTermLL;

 FakeWeight(){};

 void InputEff(TH2D* FakeEff, TH2D* RealEff){
   this->FakeEff = FakeEff;
   this->RealEff = RealEff;
 }

 void InputSelection(int passTT, int passTL, int passLT, int passLL){
   this->passTT = passTT;
   this->passTL = passTL;
   this->passLT = passLT;
   this->passLL = passLL;
 }

 double GetFakeWeight(double pt1, double eta1, double pt2, double eta2){

   int fakebin1 = FakeEff->FindBin(pt1, eta1);
   int fakebinx1 = fakebin1 % (FakeEff->GetNbinsX() + 2);
   int fakebiny1 = fakebin1 / (FakeEff->GetNbinsX() + 2);

   int fakebin2 = FakeEff->FindBin(pt2, eta2);
   int fakebinx2 = fakebin2 % (FakeEff->GetNbinsX() + 2);
   int fakebiny2 = fakebin2 / (FakeEff->GetNbinsX() + 2);

   double f1 = FakeEff->GetBinContent(fakebinx1, fakebiny1);
   double f2 = FakeEff->GetBinContent(fakebinx2, fakebiny2);

   if(f1 < 0.0) f1 = 0.0;
   if(f2 < 0.0) f2 = 0.0;

   int realbin1 = RealEff->FindBin(pt1, eta1);
   int realbinx1 = realbin1 % (RealEff->GetNbinsX() + 2);
   int realbiny1 = realbin1 / (RealEff->GetNbinsX() + 2);

   int realbin2 = RealEff->FindBin(pt2, eta2);
   int realbinx2 = realbin2 % (RealEff->GetNbinsX() + 2);
   int realbiny2 = realbin2 / (RealEff->GetNbinsX() + 2);

   double e1 = RealEff->GetBinContent(realbinx1, realbiny1);
   double e2 = RealEff->GetBinContent(realbinx2, realbiny2);

   if(MatrixMap.count(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2)) == 0){

     Eigen::MatrixXd FakeMatrix = Eigen::MatrixXd(4, 4);

     FakeMatrix(0, 0) = e1 * e2;                 FakeMatrix(0, 1) = e1 * f2;                 FakeMatrix(0, 2) = f1 * e2;                 FakeMatrix(0, 3) = f1 * f2;
     FakeMatrix(1, 0) = e1 * (1.0 - e2);         FakeMatrix(1, 1) = e1 * (1.0 - f2);         FakeMatrix(1, 2) = f1 * (1.0 - e2);         FakeMatrix(1, 3) = f1 * (1.0 - f2);
     FakeMatrix(2, 0) = (1.0 - e1) * e2;         FakeMatrix(2, 1) = (1.0 - e1) * f2;         FakeMatrix(2, 2) = (1.0 - f1) * e2;         FakeMatrix(2, 3) = (1.0 - f1) * f2;
     FakeMatrix(3, 0) = (1.0 - e1) * (1.0 - e2); FakeMatrix(3, 1) = (1.0 - e1) * (1.0 - f2); FakeMatrix(3, 2) = (1.0 - f1) * (1.0 - e2); FakeMatrix(3, 3) = (1.0 - f1) * (1.0 - f2);

     Eigen::MatrixXd InverseFakeMatrix = FakeMatrix.inverse();

     MatrixMap[make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2)] = FakeMatrix;
     InverseMatrixMap[make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2)] = InverseFakeMatrix;
   }

   double weight = (double)passTT - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 0) * (double)passTT
                                  - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 1) * (double)passTL
                                  - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 2) * (double)passLT
                                  - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 3) * (double)passLL;

   if(!isfinite(weight)) weight = 0.0;

   WeightRR = InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 0) * (double)passTT
            + InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 1) * (double)passTL
            + InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 2) * (double)passLT
            + InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 3) * (double)passLL;

   if(!isfinite(WeightRR)) WeightRR = 0.0;

   WeightTL = (double)passTL * f2 / (1.0 - f2);
   WeightTLirr = e1 * (1.0 - e2) * WeightRR * f2 / (1.0 - f2);
   WeightLT = (double)passLT * f1 / (1.0 - f1);
   WeightLTirr = (1.0 - e1) * e2 * WeightRR * f1 / (1.0 - f1);
   WeightLL = (double)passLL * f1 / (1.0 - f1) * f2 / (1.0 - f2);
   WeightLLirr = (1.0 - e1) * (1.0 - e2) * WeightRR * f1 / (1.0 - f1) * f2 / (1.0 - f2);

   FourTermTT = (double)passTT - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 0) * (double)passTT;
   FourTermTL =                - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 1) * (double)passTL;
   FourTermLT =                - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 2) * (double)passLT;
   FourTermLL =                - e1 * e2 * InverseMatrixMap.at(make_tuple(fakebinx1, fakebiny1, fakebinx2, fakebiny2, realbinx1, realbiny1, realbinx2, realbiny2))(0, 3) * (double)passLL;

   if(!isfinite(WeightTL)) WeightTL = 0.0;
   if(!isfinite(WeightTLirr)) WeightTLirr = 0.0;
   if(!isfinite(WeightLT)) WeightLT = 0.0;
   if(!isfinite(WeightLTirr)) WeightLTirr = 0.0;
   if(!isfinite(WeightLL)) WeightLL = 0.0;
   if(!isfinite(WeightLLirr)) WeightLLirr = 0.0;

   if(!isfinite(FourTermTT)) FourTermTT = 0.0;
   if(!isfinite(FourTermTL)) FourTermTL = 0.0;
   if(!isfinite(FourTermLT)) FourTermLT = 0.0;
   if(!isfinite(FourTermLL)) FourTermLL = 0.0;

   return weight;
 }

 double GetFakeWeightAppro(double pt1, double eta1, double pt2, double eta2){
   int fakebin1 = FakeEff->FindBin(pt1, eta1);
   int fakebinx1 = fakebin1 % (FakeEff->GetNbinsX() + 2);
   int fakebiny1 = fakebin1 / (FakeEff->GetNbinsX() + 2);

   int fakebin2 = FakeEff->FindBin(pt2, eta2);
   int fakebinx2 = fakebin2 % (FakeEff->GetNbinsX() + 2);
   int fakebiny2 = fakebin2 / (FakeEff->GetNbinsX() + 2);

   double f1 = FakeEff->GetBinContent(fakebinx1, fakebiny1);
   double f2 = FakeEff->GetBinContent(fakebinx2, fakebiny2);

   int realbin1 = RealEff->FindBin(pt1, eta1);
   int realbinx1 = realbin1 % (RealEff->GetNbinsX() + 2);
   int realbiny1 = realbin1 / (RealEff->GetNbinsX() + 2);

   int realbin2 = RealEff->FindBin(pt2, eta2);
   int realbinx2 = realbin2 % (RealEff->GetNbinsX() + 2);
   int realbiny2 = realbin2 / (RealEff->GetNbinsX() + 2);

   double e1 = RealEff->GetBinContent(realbinx1, realbiny1);
   double e2 = RealEff->GetBinContent(realbinx2, realbiny2);

   double weight =  (double)passTL * f2 / (1.0 - f2) + (double)passLT * f1 / (1.0 - f1) - (double)passLL * f1 / (1.0 - f1) * f2 / (1.0 - f2);

   double FinalWeight = GetFakeWeight(pt1, eta1, pt2, eta2);

   if(!isfinite(weight)) weight = 0.0;

   WeightTL = (double)passTL * f2 / (1.0 - f2);
   WeightTLirr = e1 * (1.0 - e2) * WeightRR * f2 / (1.0 - f2);
   WeightLT = (double)passLT * f1 / (1.0 - f1);
   WeightLTirr = (1.0 - e1) * e2 * WeightRR * f1 / (1.0 - f1);
   WeightLL = (double)passLL * f1 / (1.0 - f1) * f2 / (1.0 - f2);
   WeightLLirr = (1.0 - e1) * (1.0 - e2) * WeightRR * f1 / (1.0 - f1) * f2 / (1.0 - f2);

   if(!isfinite(WeightTL)) WeightTL = 0.0;
   if(!isfinite(WeightTLirr)) WeightTLirr = 0.0;
   if(!isfinite(WeightLT)) WeightLT = 0.0;
   if(!isfinite(WeightLTirr)) WeightLTirr = 0.0;
   if(!isfinite(WeightLL)) WeightLL = 0.0;
   if(!isfinite(WeightLLirr)) WeightLLirr = 0.0;

   return weight;
 }
};

int main(int argc, char** argv)
{
 TFile* file = new TFile("/msu/data/t3work12/yaofu/HMDYSamples/ForPlots_LAPP/v1/debug/output_nominal_Loose_Data_TOPQ1_nomWeight.root");
 TTree* tree = (TTree *)file->Get("hmdyTree");

   Double_t        Weight_Lepton1_SF;
   Double_t        Weight_Lepton2_SF;
   Int_t           RunNumber;
   ULong64_t       EventNumber;
   Double_t        mcChannelNumber;
   Double_t        RecoDilRapidity;
   Double_t        RecoDilPhi;
   Double_t        RecoDilMass;
   Double_t        RecoPseudoDilMass;
   Double_t        RecoDilPt;
   Double_t        RecoPhiStar;
   Double_t        RecoCosThetaStar;
   Bool_t          eeChannel;
   Bool_t          mumuChannel;
   Bool_t          emuChannel;
   Double_t        TruthDilMass_Born;
   Double_t        TruthDilRapidity_Born;
   Double_t        Lepton1_Pt;
   Double_t        Lepton2_Pt;
   Double_t        Lepton1_Phi;
   Double_t        Lepton2_Phi;
   Double_t        Lepton1_Eta;
   Double_t        Lepton2_Eta;
   Double_t        pTllReweight;
   Double_t        ChargeMisIDSFWeight;
   Double_t        LeptonSFWeight;
   Double_t        PileupWeight;
   Int_t           n_Bjets;
   Double_t        MET_Et;
   Double_t        Lepton1_z0;
   Double_t        Lepton2_z0;
   Double_t        Lepton1_d0sig;
   Double_t        Lepton2_d0sig;
   Double_t        Mu;
   Double_t        MuActual;
   Double_t        PhiRF;
   Double_t        Weight_kFactor_Old;
   Double_t        Weight_kFactor_QCDEW;
   Double_t        Weight_kFactor_New_CT18NNLO;
   Double_t        Weight_kFactor_New_CT18ANNLO;
   Double_t        Weight_kFactor_PowhegtoSherpa;
   Bool_t          pass_ee_TT;
   Bool_t          pass_ee_TL;
   Bool_t          pass_ee_LT;
   Bool_t          pass_ee_LL;
   Bool_t          pass_mm_TT;
   Bool_t          pass_mm_TL;
   Bool_t          pass_mm_LT;
   Bool_t          pass_mm_LL;
   vector<int>     *ele_isLHLoose;
   vector<int>     *ele_isLHMedium;
   vector<int>     *ele_isFixedCutTightIso;
   Double_t        RecoWeight;
   Double_t        RecoWeight_PromptSubtrUp;
   Double_t        RecoWeight_PromptSubtrDown;
   Double_t        RecoWeight_noW;
   Double_t        RecoWeight_noDY;
   Double_t        RecoWeight_noZMass;
   Double_t        RecoWeight_StatsUp;
   Double_t        RecoWeight_StatsDown;
   Double_t        RecoWeight_CombineError;
   Double_t        RecoWeight_matrix_1up;
   Double_t        RecoWeight_matrix_1down;
   Double_t        RecoWeight_Appro;
   Double_t        WeightTL;
   Double_t        WeightTLirr;
   Double_t        WeightLT;
   Double_t        WeightLTirr;
   Double_t        WeightLL;
   Double_t        WeightLLirr;
   Double_t        FourTermTT;
   Double_t        FourTermTL;
   Double_t        FourTermLT;
   Double_t        FourTermLL;
   Bool_t          pass_OtherTT;
   Bool_t          pass_OtherTL;
   Bool_t          pass_OtherLT;
   Bool_t          pass_OtherLL;
   Double_t        FourTerm_OtherTT;
   Double_t        FourTerm_OtherTL;
   Double_t        FourTerm_OtherLT;
   Double_t        FourTerm_OtherLL;
   Double_t        RecoWeight_AddOther;

   TBranch        *b_Weight_Lepton1_SF;   //!
   TBranch        *b_Weight_Lepton2_SF;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_RecoDilRapidity;   //!
   TBranch        *b_RecoDilPhi;   //!
   TBranch        *b_RecoDilMass;   //!
   TBranch        *b_RecoPseudoDilMass;   //!
   TBranch        *b_RecoDilPt;   //!
   TBranch        *b_RecoPhiStar;   //!
   TBranch        *b_RecoCosThetaStar;   //!
   TBranch        *b_eeChannel;   //!
   TBranch        *b_mumuChannel;   //!
   TBranch        *b_emuChannel;   //!
   TBranch        *b_TruthDilMass_Born;   //!
   TBranch        *b_TruthDilRapidity_Born;   //!
   TBranch        *b_Lepton1_Pt;   //!
   TBranch        *b_Lepton2_Pt;   //!
   TBranch        *b_Lepton1_Phi;   //!
   TBranch        *b_Lepton2_Phi;   //!
   TBranch        *b_Lepton1_Eta;   //!
   TBranch        *b_Lepton2_Eta;   //!
   TBranch        *b_pTllReweight;   //!
   TBranch        *b_ChargeMisIDSFWeight;   //!
   TBranch        *b_LeptonSFWeight;   //!
   TBranch        *b_PileupWeight;   //!
   TBranch        *b_n_Bjets;   //!
   TBranch        *b_MET_Et;   //!
   TBranch        *b_Lepton1_z0;   //!
   TBranch        *b_Lepton2_z0;   //!
   TBranch        *b_Lepton1_d0sig;   //!
   TBranch        *b_Lepton2_d0sig;   //!
   TBranch        *b_Mu;   //!
   TBranch        *b_MuActual;   //!
   TBranch        *b_PhiRF;   //!
   TBranch        *b_Weight_kFactor_Old;   //!
   TBranch        *b_Weight_kFactor_QCDEW;   //!
   TBranch        *b_Weight_kFactor_New_CT18NNLO;   //!
   TBranch        *b_Weight_kFactor_New_CT18ANNLO;   //!
   TBranch        *b_Weight_kFactor_PowhegtoSherpa;   //!
   TBranch        *b_pass_ee_TT;   //!
   TBranch        *b_pass_ee_TL;   //!
   TBranch        *b_pass_ee_LT;   //!
   TBranch        *b_pass_ee_LL;   //!
   TBranch        *b_pass_mm_TT;   //!
   TBranch        *b_pass_mm_TL;   //!
   TBranch        *b_pass_mm_LT;   //!
   TBranch        *b_pass_mm_LL;   //!
   TBranch        *b_ele_isLHLoose;   //!
   TBranch        *b_ele_isLHMedium;   //!
   TBranch        *b_ele_isFixedCutTightIso;   //!
   TBranch        *b_RecoWeight;   //!
   TBranch        *b_RecoWeight_PromptSubtrUp;   //!
   TBranch        *b_RecoWeight_PromptSubtrDown;   //!
   TBranch        *b_RecoWeight_noW;   //!
   TBranch        *b_RecoWeight_noDY;   //!
   TBranch        *b_RecoWeight_noZMass;   //!
   TBranch        *b_RecoWeight_StatsUp;   //!
   TBranch        *b_RecoWeight_StatsDown;   //!
   TBranch        *b_RecoWeight_CombineError;   //!
   TBranch        *b_RecoWeight_matrix_1up;   //!
   TBranch        *b_RecoWeight_matrix_1down;   //!

   ele_isLHLoose = 0;
   ele_isLHMedium = 0;
   ele_isFixedCutTightIso = 0;

   vector<int> v_ele_isLHLoose;
   vector<int> v_ele_isLHMedium;
   vector<int> v_ele_isFixedCutTightIso;

   tree->SetBranchAddress("Weight_Lepton1_SF", &Weight_Lepton1_SF, &b_Weight_Lepton1_SF);
   tree->SetBranchAddress("Weight_Lepton2_SF", &Weight_Lepton2_SF, &b_Weight_Lepton2_SF);
   tree->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   tree->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   tree->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   tree->SetBranchAddress("RecoDilRapidity", &RecoDilRapidity, &b_RecoDilRapidity);
   tree->SetBranchAddress("RecoDilPhi", &RecoDilPhi, &b_RecoDilPhi);
   tree->SetBranchAddress("RecoDilMass", &RecoDilMass, &b_RecoDilMass);
   tree->SetBranchAddress("RecoPseudoDilMass", &RecoPseudoDilMass, &b_RecoPseudoDilMass);
   tree->SetBranchAddress("RecoDilPt", &RecoDilPt, &b_RecoDilPt);
   tree->SetBranchAddress("RecoPhiStar", &RecoPhiStar, &b_RecoPhiStar);
   tree->SetBranchAddress("RecoCosThetaStar", &RecoCosThetaStar, &b_RecoCosThetaStar);
   tree->SetBranchAddress("eeChannel", &eeChannel, &b_eeChannel);
   tree->SetBranchAddress("mumuChannel", &mumuChannel, &b_mumuChannel);
   tree->SetBranchAddress("emuChannel", &emuChannel, &b_emuChannel);
   tree->SetBranchAddress("TruthDilMass_Born", &TruthDilMass_Born, &b_TruthDilMass_Born);
   tree->SetBranchAddress("TruthDilRapidity_Born", &TruthDilRapidity_Born, &b_TruthDilRapidity_Born);
   tree->SetBranchAddress("Lepton1_Pt", &Lepton1_Pt, &b_Lepton1_Pt);
   tree->SetBranchAddress("Lepton2_Pt", &Lepton2_Pt, &b_Lepton2_Pt);
   tree->SetBranchAddress("Lepton1_Phi", &Lepton1_Phi, &b_Lepton1_Phi);
   tree->SetBranchAddress("Lepton2_Phi", &Lepton2_Phi, &b_Lepton2_Phi);
   tree->SetBranchAddress("Lepton1_Eta", &Lepton1_Eta, &b_Lepton1_Eta);
   tree->SetBranchAddress("Lepton2_Eta", &Lepton2_Eta, &b_Lepton2_Eta);
   tree->SetBranchAddress("pTllReweight", &pTllReweight, &b_pTllReweight);
   tree->SetBranchAddress("ChargeMisIDSFWeight", &ChargeMisIDSFWeight, &b_ChargeMisIDSFWeight);
   tree->SetBranchAddress("LeptonSFWeight", &LeptonSFWeight, &b_LeptonSFWeight);
   tree->SetBranchAddress("PileupWeight", &PileupWeight, &b_PileupWeight);
   tree->SetBranchAddress("n_Bjets", &n_Bjets, &b_n_Bjets);
   tree->SetBranchAddress("MET_Et", &MET_Et, &b_MET_Et);
   tree->SetBranchAddress("Lepton1_z0", &Lepton1_z0, &b_Lepton1_z0);
   tree->SetBranchAddress("Lepton2_z0", &Lepton2_z0, &b_Lepton2_z0);
   tree->SetBranchAddress("Lepton1_d0sig", &Lepton1_d0sig, &b_Lepton1_d0sig);
   tree->SetBranchAddress("Lepton2_d0sig", &Lepton2_d0sig, &b_Lepton2_d0sig);
   tree->SetBranchAddress("Mu", &Mu, &b_Mu);
   tree->SetBranchAddress("MuActual", &MuActual, &b_MuActual);
   tree->SetBranchAddress("PhiRF", &PhiRF, &b_PhiRF);
   tree->SetBranchAddress("Weight_kFactor_Old", &Weight_kFactor_Old, &b_Weight_kFactor_Old);
   tree->SetBranchAddress("Weight_kFactor_QCDEW", &Weight_kFactor_QCDEW, &b_Weight_kFactor_QCDEW);
   tree->SetBranchAddress("Weight_kFactor_New_CT18NNLO", &Weight_kFactor_New_CT18NNLO, &b_Weight_kFactor_New_CT18NNLO);
   tree->SetBranchAddress("Weight_kFactor_New_CT18ANNLO", &Weight_kFactor_New_CT18ANNLO, &b_Weight_kFactor_New_CT18ANNLO);
   tree->SetBranchAddress("Weight_kFactor_PowhegtoSherpa", &Weight_kFactor_PowhegtoSherpa, &b_Weight_kFactor_PowhegtoSherpa);
   tree->SetBranchAddress("pass_ee_TT", &pass_ee_TT, &b_pass_ee_TT);
   tree->SetBranchAddress("pass_ee_TL", &pass_ee_TL, &b_pass_ee_TL);
   tree->SetBranchAddress("pass_ee_LT", &pass_ee_LT, &b_pass_ee_LT);
   tree->SetBranchAddress("pass_ee_LL", &pass_ee_LL, &b_pass_ee_LL);
   tree->SetBranchAddress("pass_mm_TT", &pass_mm_TT, &b_pass_mm_TT);
   tree->SetBranchAddress("pass_mm_TL", &pass_mm_TL, &b_pass_mm_TL);
   tree->SetBranchAddress("pass_mm_LT", &pass_mm_LT, &b_pass_mm_LT);
   tree->SetBranchAddress("pass_mm_LL", &pass_mm_LL, &b_pass_mm_LL);
   tree->SetBranchAddress("ele_isLHLoose", &ele_isLHLoose, &b_ele_isLHLoose);
   tree->SetBranchAddress("ele_isLHMedium", &ele_isLHMedium, &b_ele_isLHMedium);
   tree->SetBranchAddress("ele_isFixedCutTightIso", &ele_isFixedCutTightIso, &b_ele_isFixedCutTightIso);
/*   tree->SetBranchAddress("RecoWeight", &RecoWeight, &b_RecoWeight);
   tree->SetBranchAddress("RecoWeight_PromptSubtrUp", &RecoWeight_PromptSubtrUp, &b_RecoWeight_PromptSubtrUp);
   tree->SetBranchAddress("RecoWeight_PromptSubtrDown", &RecoWeight_PromptSubtrDown, &b_RecoWeight_PromptSubtrDown);
   tree->SetBranchAddress("RecoWeight_noW", &RecoWeight_noW, &b_RecoWeight_noW);
   tree->SetBranchAddress("RecoWeight_noDY", &RecoWeight_noDY, &b_RecoWeight_noDY);
   tree->SetBranchAddress("RecoWeight_noZMass", &RecoWeight_noZMass, &b_RecoWeight_noZMass);
   tree->SetBranchAddress("RecoWeight_StatsUp", &RecoWeight_StatsUp, &b_RecoWeight_StatsUp);
   tree->SetBranchAddress("RecoWeight_StatsDown", &RecoWeight_StatsDown, &b_RecoWeight_StatsDown);
   tree->SetBranchAddress("RecoWeight_CombineError", &RecoWeight_CombineError, &b_RecoWeight_CombineError);
   tree->SetBranchAddress("RecoWeight_matrix_1up", &RecoWeight_matrix_1up, &b_RecoWeight_matrix_1up);
   tree->SetBranchAddress("RecoWeight_matrix_1down", &RecoWeight_matrix_1down, &b_RecoWeight_matrix_1down);
*/

 TFile* outfile = new TFile("output_ntuple_MM_2024_fixed.root", "RECREATE");
 outfile->cd();
 TTree* outtree = new TTree("hmdyTree", "hmdyTree");
 outtree->Branch("Weight_Lepton1_SF",                &Weight_Lepton1_SF,            "Weight_Lepton1_SF/D");
 outtree->Branch("Weight_Lepton2_SF",                &Weight_Lepton2_SF,            "Weight_Lepton2_SF/D");
 outtree->Branch("RunNumber",                        &RunNumber,                    "RunNumber/I");
 outtree->Branch("EventNumber",                      &EventNumber);
 outtree->Branch("mcChannelNumber",                  &mcChannelNumber,              "mcChannelNumber/D");
 outtree->Branch("RecoDilRapidity",                  &RecoDilRapidity,              "RecoDilRapidity/D");
 outtree->Branch("RecoDilPhi",                       &RecoDilPhi,                   "RecoDilPhi/D");
 outtree->Branch("RecoDilMass",                      &RecoDilMass,                  "RecoDilMass/D");
 outtree->Branch("RecoPseudoDilMass",                &RecoPseudoDilMass,            "RecoPseudoDilMass/D");
 outtree->Branch("RecoDilPt",                        &RecoDilPt,                    "RecoDilPt/D");
 outtree->Branch("RecoPhiStar",                      &RecoPhiStar,                  "RecoPhiStar/D");
 outtree->Branch("RecoCosThetaStar",                 &RecoCosThetaStar,             "RecoCosThetaStar/D");
 outtree->Branch("eeChannel",                        &eeChannel);
 outtree->Branch("mumuChannel",                      &mumuChannel);
 outtree->Branch("emuChannel",                       &emuChannel);
 outtree->Branch("TruthDilMass_Born",                &TruthDilMass_Born,            "TruthDilMass_Born/D");
 outtree->Branch("TruthDilRapidity_Born",            &TruthDilRapidity_Born,        "TruthDilRapidity_Born/D");
 outtree->Branch("Lepton1_Pt",                       &Lepton1_Pt,                   "Lepton1_Pt/D");
 outtree->Branch("Lepton2_Pt",                       &Lepton2_Pt,                   "Lepton2_Pt/D");
 outtree->Branch("Lepton1_Phi",                      &Lepton1_Phi,                  "Lepton1_Phi/D");
 outtree->Branch("Lepton2_Phi",                      &Lepton2_Phi,                  "Lepton2_Phi/D");
 outtree->Branch("Lepton1_Eta",                      &Lepton1_Eta,                  "Lepton1_Eta/D");
 outtree->Branch("Lepton2_Eta",                      &Lepton2_Eta,                  "Lepton2_Eta/D");
 outtree->Branch("pTllReweight",                     &pTllReweight,                 "pTllReweight/D");
 outtree->Branch("ChargeMisIDSFWeight",              &ChargeMisIDSFWeight,          "ChargeMisIDSFWeight/D");
 outtree->Branch("LeptonSFWeight",                   &LeptonSFWeight,               "LeptonSFWeight/D");
 outtree->Branch("PileupWeight",                     &PileupWeight,                 "PileupWeight/D");
 outtree->Branch("n_Bjets",                          &n_Bjets,                      "n_Bjets/I");
 outtree->Branch("MET_Et",                           &MET_Et,                       "MET_Et/D");
 outtree->Branch("Lepton1_z0",                       &Lepton1_z0,                   "Lepton1_z0/D");
 outtree->Branch("Lepton2_z0",                       &Lepton2_z0,                   "Lepton2_z0/D");
 outtree->Branch("Lepton1_d0sig",                    &Lepton1_d0sig,                "Lepton1_d0sig/D");
 outtree->Branch("Lepton2_d0sig",                    &Lepton2_d0sig,                "Lepton2_d0sig/D");
 outtree->Branch("Mu",                               &Mu,                           "Mu/D");
 outtree->Branch("MuActual",                         &MuActual,                     "MuActual/D");
 outtree->Branch("PhiRF",                            &PhiRF,                        "PhiRF/D");
 outtree->Branch("Weight_kFactor_Old",               &Weight_kFactor_Old,           "Weight_kFactor_Old/D");
 outtree->Branch("Weight_kFactor_QCDEW",             &Weight_kFactor_QCDEW,         "Weight_kFactor_QCDEW/D");
 outtree->Branch("Weight_kFactor_New_CT18NNLO",      &Weight_kFactor_New_CT18NNLO,  "Weight_kFactor_New_CT18NNLO/D");
 outtree->Branch("Weight_kFactor_New_CT18ANNLO",     &Weight_kFactor_New_CT18ANNLO, "Weight_kFactor_New_CT18ANNLO/D");
 outtree->Branch("Weight_kFactor_PowhegtoSherpa",    &Weight_kFactor_PowhegtoSherpa,"Weight_kFactor_PowhegtoSherpa/D");
 outtree->Branch("pass_ee_TT",                       &pass_ee_TT);
 outtree->Branch("pass_ee_TL",                       &pass_ee_TL);
 outtree->Branch("pass_ee_LT",                       &pass_ee_LT);
 outtree->Branch("pass_ee_LL",                       &pass_ee_LL);
 outtree->Branch("pass_mm_TT",                       &pass_mm_TT);
 outtree->Branch("pass_mm_TL",                       &pass_mm_TL);
 outtree->Branch("pass_mm_LT",                       &pass_mm_LT);
 outtree->Branch("pass_mm_LL",                       &pass_mm_LL);
 outtree->Branch("ele_isLHLoose",                    "vector<int>",  &v_ele_isLHLoose);
 outtree->Branch("ele_isLHMedium",                   "vector<int>",  &v_ele_isLHMedium);
 outtree->Branch("ele_isFixedCutTightIso",           "vector<int>",  &v_ele_isFixedCutTightIso);
 outtree->Branch("RecoWeight",                       &RecoWeight,                    "RecoWeight/D");
 outtree->Branch("RecoWeight_PromptSubtrUp",         &RecoWeight_PromptSubtrUp,      "RecoWeight_PromptSubtrUp/D");
 outtree->Branch("RecoWeight_PromptSubtrDown",       &RecoWeight_PromptSubtrDown,    "RecoWeight_PromptSubtrDown/D");
 outtree->Branch("RecoWeight_noW",                   &RecoWeight_noW,                "RecoWeight_noW/D");
 outtree->Branch("RecoWeight_noDY",                  &RecoWeight_noDY,               "RecoWeight_noDY/D");
 outtree->Branch("RecoWeight_noZMass",               &RecoWeight_noZMass,            "RecoWeight_noZMass/D");
 outtree->Branch("RecoWeight_StatsUp",               &RecoWeight_StatsUp,            "RecoWeight_StatsUp/D");
 outtree->Branch("RecoWeight_StatsDown",             &RecoWeight_StatsDown,          "RecoWeight_StatsDown/D");
 outtree->Branch("RecoWeight_CombineError",          &RecoWeight_CombineError,       "RecoWeight_CombineError/D");
 outtree->Branch("RecoWeight_matrix_1up",            &RecoWeight_matrix_1up,         "RecoWeight_matrix_1up/D");
 outtree->Branch("RecoWeight_matrix_1down",          &RecoWeight_matrix_1down,       "RecoWeight_matrix_1down/D");
 outtree->Branch("WeightTL",                         &WeightTL,                      "WeightTL/D");
 outtree->Branch("WeightTLirr",                      &WeightTLirr,                   "WeightTLirr/D");
 outtree->Branch("WeightLT",                         &WeightLT,                      "WeightLT/D");
 outtree->Branch("WeightLTirr",                      &WeightLTirr,                   "WeightLTirr/D");
 outtree->Branch("WeightLL",                         &WeightLL,                      "WeightLL/D");
 outtree->Branch("WeightLLirr",                      &WeightLLirr,                   "WeightLLirr/D");
 outtree->Branch("FourTermTT",                       &FourTermTT,                    "FourTermTT/D");
 outtree->Branch("FourTermTL",                       &FourTermTL,                    "FourTermTL/D");
 outtree->Branch("FourTermLT",                       &FourTermLT,                    "FourTermLT/D");
 outtree->Branch("FourTermLL",                       &FourTermLL,                    "FourTermLL/D");
 outtree->Branch("pass_OtherTT",                     &pass_OtherTT);
 outtree->Branch("pass_OtherTL",                     &pass_OtherTL);
 outtree->Branch("pass_OtherLT",                     &pass_OtherLT);
 outtree->Branch("pass_OtherLL",                     &pass_OtherLL);
 outtree->Branch("FourTerm_OtherTT",                 &FourTerm_OtherTT,              "FourTerm_OtherTT/D");
 outtree->Branch("FourTerm_OtherTL",                 &FourTerm_OtherTL,              "FourTerm_OtherTL/D");
 outtree->Branch("FourTerm_OtherLT",                 &FourTerm_OtherLT,              "FourTerm_OtherLT/D");
 outtree->Branch("FourTerm_OtherLL",                 &FourTerm_OtherLL,              "FourTerm_OtherLL/D");
 outtree->Branch("RecoWeight_AddOther",              &RecoWeight_AddOther,           "RecoWeight_AddOther/D");


 vector<double> v_RecoWeight;
 vector<double> v_RecoWeight_PromptSubtrUp;
 vector<double> v_RecoWeight_PromptSubtrDown;
 vector<double> v_RecoWeight_noW;
 vector<double> v_RecoWeight_noDY;
 vector<double> v_RecoWeight_noZMass;
 vector<double> v_RecoWeight_StatsUp;
 vector<double> v_RecoWeight_StatsDown;
 vector<double> v_RecoWeight_CombineError;
 vector<double> v_RecoWeight_matrix_1up;
 vector<double> v_RecoWeight_matrix_1down;

/* TFile* FakeEffFile = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_Nominal.root");
 TFile* FakeEffFile_PromptSubtrUp = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_Sys_PromptSubtrUp.root");
 TFile* FakeEffFile_PromptSubtrDown = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_Sys_PromptSubtrDown.root");
 TFile* FakeEffFile_noW = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_Sys_noW.root");
 TFile* FakeEffFile_noDY = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_Sys_noDY.root");
 TFile* FakeEffFile_noZMass = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_Sys_noZMass.root");
 TFile* FakeEffFile_StatUncUp = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_StatUncUp.root");
 TFile* FakeEffFile_StatUncDown = new TFile("FakeEfficiency/HMDY_RealFakeEffs_Run2_HighPt_StatUncDown.root");
*/


 TFile* FakeEffFile = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_Nominal.root");
 TFile* FakeEffFile_PromptSubtrUp = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_Sys_PromptSubtrUp.root");
 TFile* FakeEffFile_PromptSubtrDown = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_Sys_PromptSubtrDown.root");
 TFile* FakeEffFile_noW = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_Sys_noW.root");
 TFile* FakeEffFile_noDY = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_Sys_noDY.root");
 TFile* FakeEffFile_noZMass = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_Sys_noZMass.root");
 TFile* FakeEffFile_StatUncUp = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_StatUncUp.root");
 TFile* FakeEffFile_StatUncDown = new TFile("FakeEfficiency_FullRun2/HMDY_RealFakeEffs_FullRun2_StatUncDown.root");

 TH2D* FakeEff = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_PromptSubtrUp = (TH2D *)FakeEffFile_PromptSubtrUp->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_PromptSubtrUp = (TH2D *)FakeEffFile_PromptSubtrUp->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_PromptSubtrDown = (TH2D *)FakeEffFile_PromptSubtrDown->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_PromptSubtrDown = (TH2D *)FakeEffFile_PromptSubtrDown->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_noW = (TH2D *)FakeEffFile_noW->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_noW = (TH2D *)FakeEffFile_noW->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_noDY = (TH2D *)FakeEffFile_noDY->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_noDY = (TH2D *)FakeEffFile_noDY->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_noZMass = (TH2D *)FakeEffFile_noZMass->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_noZMass = (TH2D *)FakeEffFile_noZMass->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_StatUncUp = (TH2D *)FakeEffFile_StatUncUp->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_StatUncUp = (TH2D *)FakeEffFile_StatUncUp->Get("RealEfficiency2D_el_pt_eta");

 TH2D* FakeEff_StatUncDown = (TH2D *)FakeEffFile_StatUncDown->Get("FakeEfficiency2D_el_pt_eta");
 TH2D* RealEff_StatUncDown = (TH2D *)FakeEffFile_StatUncDown->Get("RealEfficiency2D_el_pt_eta");

 FakeWeight* WeightRun = new FakeWeight();
 FakeWeight* WeightRun_PromptSubtrUp = new FakeWeight();
 FakeWeight* WeightRun_PromptSubtrDown = new FakeWeight();
 FakeWeight* WeightRun_noW = new FakeWeight();
 FakeWeight* WeightRun_noDY = new FakeWeight();
 FakeWeight* WeightRun_noZMass = new FakeWeight();
 FakeWeight* WeightRun_StatUncUp = new FakeWeight();
 FakeWeight* WeightRun_StatUncDown = new FakeWeight();

 WeightRun->InputEff(FakeEff, RealEff);
 WeightRun_PromptSubtrUp->InputEff(FakeEff_PromptSubtrUp, RealEff_PromptSubtrUp);
 WeightRun_PromptSubtrDown->InputEff(FakeEff_PromptSubtrDown, RealEff_PromptSubtrDown);
 WeightRun_noW->InputEff(FakeEff_noW, RealEff_noW);
 WeightRun_noDY->InputEff(FakeEff_noDY, RealEff_noDY);
 WeightRun_noZMass->InputEff(FakeEff_noZMass, RealEff_noZMass);
 WeightRun_StatUncUp->InputEff(FakeEff_StatUncUp, RealEff_StatUncUp);
 WeightRun_StatUncDown->InputEff(FakeEff_StatUncDown, RealEff_StatUncDown);

 FakeWeight* WeightRun_AddOther = new FakeWeight();
 WeightRun_AddOther->InputEff(FakeEff, RealEff);
 TH1D* OtherTight = new TH1D("OtherTight", "OtherTight", 40, 30, 500);
 for(int ibin = 1; ibin <= OtherTight->GetNbinsX(); ibin++){
   OtherTight->SetBinContent(ibin, 1.0 - ibin * 0.0025);
 }


 TRandom3 r(0);

 int Entries = tree->GetEntries();

 int ientry = 0;
 for(int i = 0; i < Entries; i++){
   tree->GetEntry(i);

   if(!eeChannel) continue;
   if(Lepton1_Pt < 30.0 || Lepton2_Pt < 30.0) continue;

   if(i % 1000000 == 0) cout<<i<<" events have finished."<<endl;

   int passTT = 0, passTL = 0, passLT = 0, passLL = 0;
   if(pass_ee_TT) passTT = 1;
   if(pass_ee_TL) passTL = 1;
   if(pass_ee_LT) passLT = 1;
   if(pass_ee_LL) passLL = 1;

   if(passLT) RecoCosThetaStar = RecoCosThetaStar * (-1.0);

   WeightRun->InputSelection(passTT, passTL, passLT, passLL);
   RecoWeight = WeightRun->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_PromptSubtrUp->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_PromptSubtrUp = WeightRun_PromptSubtrUp->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_PromptSubtrDown->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_PromptSubtrDown = WeightRun_PromptSubtrDown->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_noW->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_noW = WeightRun_noW->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_noDY->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_noDY = WeightRun_noDY->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_noZMass->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_noZMass = WeightRun_noZMass->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_StatUncUp->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_StatsUp = WeightRun_StatUncUp->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   WeightRun_StatUncDown->InputSelection(passTT, passTL, passLT, passLL);
//   RecoWeight_StatsDown = WeightRun_StatUncDown->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

//   RecoWeight_CombineError = sqrt(pow(max(fabs(RecoWeight_StatsUp-RecoWeight),fabs(RecoWeight-RecoWeight_StatsDown)),2)
//                                + pow(fabs(RecoWeight-RecoWeight_noW),2)
//                                + pow(fabs(RecoWeight-RecoWeight_noZMass),2)
//                                + pow(fabs(RecoWeight-RecoWeight_noDY),2)
//                                + pow(max(fabs(RecoWeight_PromptSubtrDown-RecoWeight),fabs(RecoWeight-RecoWeight_PromptSubtrUp)),2));

//   RecoWeight_matrix_1up = RecoWeight + RecoWeight_CombineError;
//   RecoWeight_matrix_1down = RecoWeight - RecoWeight_CombineError;


//   RecoWeight_Appro = WeightRun->GetFakeWeightAppro(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

   WeightTL = WeightRun->WeightTL;
   WeightTLirr = WeightRun->WeightTLirr;
   WeightLT = WeightRun->WeightLT;
   WeightLTirr = WeightRun->WeightLTirr;
   WeightLL = WeightRun->WeightLL;
   WeightLLirr = WeightRun->WeightLLirr;

   FourTermTT = WeightRun->FourTermTT;
   FourTermTL = WeightRun->FourTermTL;
   FourTermLT = WeightRun->FourTermLT;
   FourTermLL = WeightRun->FourTermLL;

   double random1 = r.Uniform(0.0, 1.0);
   double random2 = r.Uniform(0.0, 1.0);

   int Lepton1PtBin = OtherTight->FindBin(Lepton1_Pt);
   int Lepton2PtBin = OtherTight->FindBin(Lepton2_Pt);

   bool passOtherTight1 = true;
   if(random1 >= OtherTight->GetBinContent(Lepton1PtBin)) passOtherTight1 = false;

   bool passOtherTight2 = true;
   if(random2 >= OtherTight->GetBinContent(Lepton2PtBin)) passOtherTight2 = false;

   pass_OtherTT = false;
   pass_OtherTL = false;
   pass_OtherLT = false;
   pass_OtherLL = false;
   if(pass_ee_TT && passOtherTight1 && passOtherTight2) pass_OtherTT = true;
   //if(pass_ee_TT && !passOtherTight1 && passOtherTight2) pass_OtherLT = true;
   //if(pass_ee_TT && passOtherTight1 && !passOtherTight2) pass_OtherTL = true;
   if(pass_ee_TL && passOtherTight1) pass_OtherTL = true;
   //if(pass_ee_TL && !passOtherTight1) pass_OtherLL = true;
   if(pass_ee_LT && passOtherTight2) pass_OtherLT = true;
   //if(pass_ee_LT && !passOtherTight2) pass_OtherLL = true;
   if(pass_ee_LL) pass_OtherLL = true;

   WeightRun_AddOther->InputSelection(pass_OtherTT, pass_OtherTL, pass_OtherLT, pass_OtherLL);
   RecoWeight_AddOther = WeightRun_AddOther->GetFakeWeight(Lepton1_Pt, fabs(Lepton1_Eta), Lepton2_Pt, fabs(Lepton2_Eta));

   FourTerm_OtherTT = WeightRun_AddOther->FourTermTT;
   FourTerm_OtherTL = WeightRun_AddOther->FourTermTL;
   FourTerm_OtherLT = WeightRun_AddOther->FourTermLT;
   FourTerm_OtherLL = WeightRun_AddOther->FourTermLL;

/*
   RecoWeight = v_RecoWeight.at(ientry);
   RecoWeight_PromptSubtrUp = v_RecoWeight_PromptSubtrUp.at(ientry);
   RecoWeight_PromptSubtrDown = v_RecoWeight_PromptSubtrDown.at(ientry);
   RecoWeight_noW = v_RecoWeight_noW.at(ientry);
   RecoWeight_noDY = v_RecoWeight_noDY.at(ientry);
   RecoWeight_noZMass = v_RecoWeight_noZMass.at(ientry);
   RecoWeight_StatsUp = v_RecoWeight_StatsUp.at(ientry);
   RecoWeight_StatsDown = v_RecoWeight_StatsDown.at(ientry);
   RecoWeight_CombineError = v_RecoWeight_CombineError.at(ientry);
   RecoWeight_matrix_1up = v_RecoWeight_matrix_1up.at(ientry);
   RecoWeight_matrix_1down = v_RecoWeight_matrix_1down.at(ientry);

   ientry++;
*/
   v_ele_isLHLoose.clear();
   v_ele_isLHMedium.clear();
   v_ele_isFixedCutTightIso.clear();

   for(int iel = 0; iel < ele_isLHLoose->size(); iel++){
     v_ele_isLHLoose.push_back(ele_isLHLoose->at(iel));
   }
   for(int iel = 0; iel < ele_isLHMedium->size(); iel++){
     v_ele_isLHMedium.push_back(ele_isLHMedium->at(iel));
   }
   for(int iel = 0; iel < ele_isFixedCutTightIso->size(); iel++){
     v_ele_isFixedCutTightIso.push_back(ele_isFixedCutTightIso->at(iel));
   }

   outtree->Fill();
 }

 cout<<"Tree Entries = "<<outtree->GetEntries()<<endl;

 outfile->cd();
 outtree->Write();
 outfile->Close();

 return 1;
}
