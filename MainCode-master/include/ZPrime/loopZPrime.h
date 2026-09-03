#ifndef ZPrime_loopZPrime_h
#define ZPrime_loopZPrime_h

#include "Analysis/loopMC.h"

#include "ZPrime/HistsZPrime.h"
#include "ZPrime/TreeForZPrime.h"
#include "ZPrime/TreeForPreZPrime.h"
#include "ZPrime/CutForZPrime.h"
#include "ZPrime/ZPrimetopDDHelper.h"
#include "SpecialHist/DataDriven.h"
#include "ZPrime/ZPrimeTripletSignalModule.h"
#include <Eigen/Dense>

class loopZPrime;
class HistsZPrime;
class TreeForZPrime;
class TreeForPreZPrime;

using namespace std;

class ZPrimeLepton
{
 public:

   Int_t           Flavor;
   Int_t           Charge = 0;
   Int_t           isTight;
   Int_t           isTruthMatch;
   Int_t           TrigMatch;

   Int_t           looseID;
   Int_t           mediumID;
   Int_t           tightID;
   Int_t           FCLooseIso;
   Int_t           FCTightIso;

   Double_t        z0;
   Double_t        d0Sig;

   Double_t        TriggerSF;
   Double_t        IsoSF;
   Double_t        RecoSF;
   Double_t        IDSF;
   Double_t        TTVASF;

   Double_t        LooseIDSF;

   Double_t        TightWeight;
   Double_t        LooseWeight;

   Double_t        PrescaleFactor;

   TLorentzVector  P4;

   ZPrimeLepton(){ P4.SetPtEtaPhiM(0,0,0,0);ResetEvent();}
   virtual void ResetEvent();
   virtual ~ZPrimeLepton(){ }
};

class EventZPrime
{
 public:

   ZPrimeLepton Lepton1;
   ZPrimeLepton Lepton2;
   ZPrimeLepton Lepton3;

   ZPrimeLepton TruthLepton1_Born;
   ZPrimeLepton TruthLepton2_Born;
   ZPrimeLepton TruthLepton1_Bare;
   ZPrimeLepton TruthLepton2_Bare;
   ZPrimeLepton TruthLepton1_Dressed;
   ZPrimeLepton TruthLepton2_Dressed;

   Double_t        TotalWeight = 0.0;
   Double_t        TotalWeightLoose = 0.0;
   Int_t           passSelection = 0;
   Int_t           passSelectionEl = 0;
   Int_t           passSelectionMu = 0;
   Int_t           passSelectionEl_Truth = 0;
   Int_t           passSelectionMu_Truth = 0;
   Int_t           passSelectionElMu = 0;
   Double_t        topTransferEl = 0.0;
   Double_t        topTransferMu = 0.0;
   Double_t        topTransferEl_HighMass_CosTheta = 0.0;
   Double_t        topTransferMu_HighMass_CosTheta = 0.0;
   Double_t        topTransferEl_HighMass_Rapidity = 0.0;
   Double_t        topTransferMu_HighMass_Rapidity = 0.0;
   Double_t        AdditionalWeight = 1.0;
   Double_t        Normalization = 1.0;

   Double_t        RecoWeight_PromptSubtrUp;
   Double_t        RecoWeight_PromptSubtrDown;
   Double_t        RecoWeight_noW;
   Double_t        RecoWeight_noDY;
   Double_t        RecoWeight_noZMass;
   Double_t        RecoWeight_StatsUp;
   Double_t        RecoWeight_StatsDown;
   Double_t        RecoWeight_stats_1up;
   Double_t        RecoWeight_stats_1down;
   Double_t        RecoWeight_d0Sig_1up;
   Double_t        RecoWeight_d0Sig_1down;

   Int_t           passSelectionEl_LowMass = 0;
   Int_t           passSelectionMu_LowMass = 0;
   Int_t           passSelectionElMu_LowMass = 0;

   Double_t        Weight_Lepton1_SF;
   Double_t        Weight_Lepton2_SF;
   Int_t           RunNumber;
   Int_t           RandomRunNumber;
   ULong64_t       EventNumber;
   Double_t        mcChannelNumber;
   Double_t        RecoDilRapidity;
   Double_t        RecoDilPhi;
   Double_t        RecoDilMass;
   Double_t        RecoPseudoDilMass;
   Double_t        RecoDilPt;
   Double_t        RecoPhiStar;
   Double_t        RecoCosThetaStar;
   Double_t        RecoWeight = 0.0;
   Double_t        RecoWeight_Stat_up = 0.0;
   Double_t        RecoWeight_Stat_down = 0.0;
   Double_t        RecoWeight_PromptSubtr_up = 0.0;
   Double_t        RecoWeight_PromptSubtr_down = 0.0;
   Double_t        RecoWeight_MET_up = 0.0;
   Double_t        RecoWeight_MET_down = 0.0;
   Double_t        RecoWeight_d0sig_up = 0.0;
   Double_t        RecoWeight_d0sig_down = 0.0;
   Double_t        RecoWeight_RealStat_up = 0.0;
   Double_t        RecoWeight_RealStat_down = 0.0;
   Double_t        RecoWeight_FourTerm_TT = 0.0;
   Double_t        RecoWeight_FourTerm_TL = 0.0;
   Double_t        RecoWeight_FourTerm_LT = 0.0;
   Double_t        RecoWeight_FourTerm_LL = 0.0;
   Bool_t          eeChannel;
   Bool_t          mumuChannel;
   Bool_t          emuChannel;
   Bool_t          eeChannel_withmuon;
   Bool_t          SingleElectron;
   Double_t        TruthDilMass_Born;
   Double_t        TruthDilRapidity_Born;
   Double_t        Lepton1_Pt;
   Double_t        Lepton2_Pt;
   Double_t        Lepton3_Pt;
   Double_t        Lepton1_Phi;
   Double_t        Lepton2_Phi;
   Double_t        Lepton3_Phi;
   Double_t        Lepton1_Eta;
   Double_t        Lepton2_Eta;
   Double_t        Lepton3_Eta;
   Double_t        pTllReweight;
   Double_t        ChargeMisIDSFWeight;
   Double_t        ChargeIDSFWeight;
   Double_t        LeptonSFWeight;
   Double_t        PileupWeight;
   Double_t        TriggerSF;
   Int_t           n_Bjets;
   Double_t        MET_Et;
   Double_t        Lepton1_z0;
   Double_t        Lepton2_z0;
   Double_t        Lepton3_z0;
   Double_t        Lepton1_d0sig;
   Double_t        Lepton2_d0sig;
   Double_t        Lepton3_d0sig;
   Double_t        Lepton1_DeltaR;
   Double_t        Lepton2_DeltaR;
   Double_t        Mu;
   Double_t        MuActual;
   Double_t        PhiRF;
   Double_t        Weight_kFactor_Old;
   Double_t        Weight_kFactor_QCDEW;
   Double_t        Weight_kFactor_New_CT18NNLO;
   Double_t        Weight_kFactor_New_CT18ANNLO;
   Double_t        Weight_kFactor_PowhegtoSherpa;

   Double_t        Weight_indiv_SF_EL_ChargeMisID_STAT_UP;
   Double_t        Weight_indiv_SF_EL_ChargeMisID_STAT_DOWN;
   Double_t        Weight_indiv_SF_EL_ChargeMisID_SYST_UP;
   Double_t        Weight_indiv_SF_EL_ChargeMisID_SYST_DOWN;

   Double_t        Lepton_Pt_born;
   Double_t        AntiLepton_Pt_born;
   Double_t        Lepton_Eta_born;
   Double_t        AntiLepton_Eta_born;
   Double_t        Lepton_Phi_born;
   Double_t        AntiLepton_Phi_born;
   Double_t        Lepton_m_born;
   Double_t        AntiLepton_m_born;
   Double_t        Lepton_Pt_bare;
   Double_t        AntiLepton_Pt_bare;
   Double_t        Lepton_Eta_bare;
   Double_t        AntiLepton_Eta_bare;
   Double_t        Lepton_Phi_bare;
   Double_t        AntiLepton_Phi_bare;
   Double_t        Lepton_Pt_dressed;
   Double_t        Lepton_Eta_dressed;
   Double_t        Lepton_Phi_dressed;
   Double_t        Lepton_Charge_dressed;
   Double_t        AntiLepton_Pt_dressed;
   Double_t        AntiLepton_Eta_dressed;
   Double_t        AntiLepton_Phi_dressed;
   Double_t        AntiLepton_Charge_dressed;

   Bool_t          pass_ee_TT;
   Bool_t          pass_ee_TL;
   Bool_t          pass_ee_LT;
   Bool_t          pass_ee_LL;
   Bool_t          pass_mm_TT;
   Bool_t          pass_mm_TL;
   Bool_t          pass_mm_LT;
   Bool_t          pass_mm_LL;
   Int_t           Lepton1_isTight;
   Int_t           Lepton2_isTight;
   Int_t           Lepton3_isTight;
   Int_t           Lepton1_passMediumID;
   Int_t           Lepton2_passMediumID;
   Int_t           Lepton3_passMediumID;
   Int_t           Lepton1_passLooseID;
   Int_t           Lepton2_passLooseID;
   Int_t           Lepton3_passLooseID;
   Int_t           Lepton1_passIso;
   Int_t           Lepton2_passIso;
   Double_t        Lepton1_IsoWeight;
   Double_t        Lepton2_IsoWeight;

   Int_t           Lepton1_Charge;
   Int_t           Lepton2_Charge;
   Int_t           Lepton1_isTruthMatch;
   Int_t           Lepton2_isTruthMatch;
   Double_t        Lepton1_TightWeight;
   Double_t        Lepton2_TightWeight;
   Double_t        Lepton3_TightWeight;
   Double_t        Lepton1_LooseWeight;
   Double_t        Lepton2_LooseWeight;
   Double_t        Lepton3_LooseWeight;
   Double_t        Lepton1_MediumIDWeight;
   Double_t        Lepton2_MediumIDWeight;

   Double_t        PrescaleFactor;
   Double_t        Lepton1_PrescaleFactor;
   Double_t        Lepton2_PrescaleFactor;

   Int_t           passElFake;
   Int_t           passElFake_MET_up;
   Int_t           passElFake_MET_down;
   Int_t           passMuFake;
   Int_t           passMuFake_d0sig_up;
   Int_t           passMuFake_d0sig_down;

   Double_t        Lepton1_FakeRate;
   Double_t        Lepton2_FakeRate;
   Double_t        Lepton1_FakeRate_Stat_up;
   Double_t        Lepton2_FakeRate_Stat_up;
   Double_t        Lepton1_FakeRate_Stat_down;
   Double_t        Lepton2_FakeRate_Stat_down;
   Double_t        Lepton1_FakeRate_PromptSubtr_up;
   Double_t        Lepton2_FakeRate_PromptSubtr_up;
   Double_t        Lepton1_FakeRate_PromptSubtr_down;
   Double_t        Lepton2_FakeRate_PromptSubtr_down;
   Double_t        Lepton1_FakeRate_MET_up;
   Double_t        Lepton2_FakeRate_MET_up;
   Double_t        Lepton1_FakeRate_MET_down;
   Double_t        Lepton2_FakeRate_MET_down;

   Bool_t          isElSample;
   Bool_t          isMuSample;

   Int_t           passElTrigger;
   Int_t           passMuTrigger;

   Bool_t          isZeeIncOverlap;

   Float_t         born_lepton1_E;
   Float_t         born_lepton1_pt;
   Float_t         born_lepton1_eta;
   Float_t         born_lepton1_phi;
   Int_t           born_lepton1_pdgid;
   Float_t         born_lepton2_E;
   Float_t         born_lepton2_pt;
   Float_t         born_lepton2_eta;
   Float_t         born_lepton2_phi;
   Int_t           born_lepton2_pdgid;
   Int_t           pdf_pdgId1;
   Int_t           pdf_pdgId2;
   Int_t           n_born_lepton;
   Double_t        born_CosThetaCS;
   Double_t        born_PhiCS;
   Double_t        born_dilepton_mass;
   Double_t        born_dilepton_pt;
   Double_t        born_dilepton_rapidity;

   Double_t        ReweightFactor_SSM_0p5TeV;
   Double_t        ReweightFactor_SSM_0p6TeV;
   Double_t        ReweightFactor_SSM_0p8TeV;
   Double_t        ReweightFactor_SSM_1TeV;
   Double_t        ReweightFactor_SSM_2TeV;
   Double_t        ReweightFactor_SSM_3TeV;
   Double_t        ReweightFactor_SSM_4TeV;
   Double_t        ReweightFactor_SSM_5TeV;
   Double_t        ReweightFactor_SSM_6TeV;
   Double_t        ReweightFactor_SSM_7TeV;
   Double_t        ReweightFactor_SSM_8TeV;

   Double_t        ReweightFactor_E6Chi_0p5TeV;
   Double_t        ReweightFactor_E6Chi_0p6TeV;
   Double_t        ReweightFactor_E6Chi_0p8TeV;
   Double_t        ReweightFactor_E6Chi_1TeV;
   Double_t        ReweightFactor_E6Chi_2TeV;
   Double_t        ReweightFactor_E6Chi_3TeV;
   Double_t        ReweightFactor_E6Chi_4TeV;
   Double_t        ReweightFactor_E6Chi_5TeV;
   Double_t        ReweightFactor_E6Chi_6TeV;
   Double_t        ReweightFactor_E6Chi_7TeV;
   Double_t        ReweightFactor_E6Chi_8TeV;

   Double_t        ReweightFactor_E6Psi_0p5TeV;
   Double_t        ReweightFactor_E6Psi_0p6TeV;
   Double_t        ReweightFactor_E6Psi_0p8TeV;
   Double_t        ReweightFactor_E6Psi_1TeV;
   Double_t        ReweightFactor_E6Psi_2TeV;
   Double_t        ReweightFactor_E6Psi_3TeV;
   Double_t        ReweightFactor_E6Psi_4TeV;
   Double_t        ReweightFactor_E6Psi_5TeV;
   Double_t        ReweightFactor_E6Psi_6TeV;
   Double_t        ReweightFactor_E6Psi_7TeV;
   Double_t        ReweightFactor_E6Psi_8TeV;

   Double_t        kfactor_nnlo;
   Double_t        kfactor_nnlo_up;
   Double_t        kfactor_nnlo_down;
   Double_t        kfactor_ew;

   virtual void ResetEvent();
};

class ZPrimeFakeWeight
{
 public:

 TH2D* FakeEff = 0;
 TH2D* RealEff = 0;
 TH2D* LeadingRealEff = 0;
 TH2D* SubleadingRealEff = 0;
 TH2D* LeadingRealEff_AddCut_Left = 0;
 TH2D* SubleadingRealEff_AddCut_Left = 0;
 TH2D* LeadingRealEff_AddCut_Right = 0;
 TH2D* SubleadingRealEff_AddCut_Right = 0;
 TH3D* LeadingRealEff3D = 0;
 TH3D* SubleadingRealEff3D = 0;

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

 ZPrimeFakeWeight(){};

 void InputEff(TH2D* FakeEff, TH2D* RealEff){
   this->FakeEff = FakeEff;
   this->RealEff = RealEff;
 }

 void InputEff(TH2D* FakeEff, TH2D* LeadingRealEff, TH2D* SubleadingRealEff){
   this->FakeEff = FakeEff;
   this->LeadingRealEff = LeadingRealEff;
   this->SubleadingRealEff = SubleadingRealEff;
 }

 void InputEff(TH2D* FakeEff, TH3D* LeadingRealEff3D, TH3D* SubleadingRealEff3D){
   this->FakeEff = FakeEff;
   this->LeadingRealEff3D = LeadingRealEff3D;
   this->SubleadingRealEff3D = SubleadingRealEff3D;
 }

 void InputEff(TH2D* FakeEff, TH2D* LeadingRealEff_AddCut_Left, TH2D* SubleadingRealEff_AddCut_Left, TH2D* LeadingRealEff_AddCut_Right, TH2D* SubleadingRealEff_AddCut_Right){
   this->FakeEff = FakeEff;
   this->LeadingRealEff_AddCut_Left = LeadingRealEff_AddCut_Left;
   this->SubleadingRealEff_AddCut_Left = SubleadingRealEff_AddCut_Left;
   this->LeadingRealEff_AddCut_Right = LeadingRealEff_AddCut_Right;
   this->SubleadingRealEff_AddCut_Right = SubleadingRealEff_AddCut_Right;
 }

 void InputSelection(int passTT, int passTL, int passLT, int passLL){
   this->passTT = passTT;
   this->passTL = passTL;
   this->passLT = passLT;
   this->passLL = passLL;
 }

 bool leading_isleft = false;
 bool subleading_isleft = false;
 void InputCut(bool leading_isleft, bool subleading_isleft){
   this->leading_isleft = leading_isleft;
   this->subleading_isleft = subleading_isleft;
 }

 int realbinx1_PtD0Sig = 0;
 int realbiny1_PtD0Sig = 0;
 int realbinx2_PtD0Sig = 0;
 int realbiny2_PtD0Sig = 0;
 void FindRealBin_PtD0Sig(double pt1, double d0sig1, double pt2, double d0sig2){
   int realbin1 = LeadingRealEff->FindBin(pt1, d0sig1);
   realbinx1_PtD0Sig = realbin1 % (LeadingRealEff->GetNbinsX() + 2);
   realbiny1_PtD0Sig = realbin1 / (LeadingRealEff->GetNbinsX() + 2);

   int realbin2 = SubleadingRealEff->FindBin(pt2, d0sig2);
   realbinx2_PtD0Sig = realbin2 % (SubleadingRealEff->GetNbinsX() + 2);
   realbiny2_PtD0Sig = realbin2 / (SubleadingRealEff->GetNbinsX() + 2);
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

   if(f1 > 1.0) f1 = 1.0;

   if(f2 > 1.0) f2 = 1.0;

   double e1, e2;
   int realbinx1, realbiny1, realbinx2, realbiny2;

   if(RealEff){
     int realbin1 = RealEff->FindBin(pt1, eta1);
     realbinx1 = realbin1 % (RealEff->GetNbinsX() + 2);
     realbiny1 = realbin1 / (RealEff->GetNbinsX() + 2);
  
     int realbin2 = RealEff->FindBin(pt2, eta2);
     realbinx2 = realbin2 % (RealEff->GetNbinsX() + 2);
     realbiny2 = realbin2 / (RealEff->GetNbinsX() + 2);
  
     e1 = RealEff->GetBinContent(realbinx1, realbiny1);
     e2 = RealEff->GetBinContent(realbinx2, realbiny2);
   }

   if(LeadingRealEff){
     int realbin1 = LeadingRealEff->FindBin(pt1, eta1);
     realbinx1 = realbin1 % (LeadingRealEff->GetNbinsX() + 2); 
     realbiny1 = realbin1 / (LeadingRealEff->GetNbinsX() + 2); 

     int realbin2 = SubleadingRealEff->FindBin(pt2, eta2);
     realbinx2 = realbin2 % (SubleadingRealEff->GetNbinsX() + 2); 
     realbiny2 = realbin2 / (SubleadingRealEff->GetNbinsX() + 2); 

     e1 = LeadingRealEff->GetBinContent(realbinx1, realbiny1);
     e2 = SubleadingRealEff->GetBinContent(realbinx2, realbiny2);
   }

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

 double GetFakeWeight(double pt1, double eta1, double d0sig1, double pt2, double eta2, double d0sig2){

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

   if(f1 > 1.0) f1 = 1.0;

   if(f2 > 1.0) f2 = 1.0;

   double e1, e2;
   int realbinx1, realbiny1, realbinz1, realbinx2, realbiny2, realbinz2;

   int realbin1 = LeadingRealEff3D->FindBin(pt1, eta1, d0sig1);

   realbinx1 = realbin1 % (LeadingRealEff3D->GetNbinsX() + 2);
   realbiny1 = realbin1 / (LeadingRealEff3D->GetNbinsX() + 2) % (LeadingRealEff3D->GetNbinsY() + 2);
   realbinz1 = realbin1 / (LeadingRealEff3D->GetNbinsX() + 2) / (LeadingRealEff3D->GetNbinsY() + 2);

   e1 = LeadingRealEff3D->GetBinContent(realbinx1, realbiny1, realbinz1);

   int realbin2 = SubleadingRealEff3D->FindBin(pt2, eta2, d0sig2);

   realbinx2 = realbin2 % (SubleadingRealEff3D->GetNbinsX() + 2);
   realbiny2 = realbin2 / (SubleadingRealEff3D->GetNbinsX() + 2) % (SubleadingRealEff3D->GetNbinsY() + 2);
   realbinz2 = realbin2 / (SubleadingRealEff3D->GetNbinsX() + 2) / (SubleadingRealEff3D->GetNbinsY() + 2);
 
   e2 = SubleadingRealEff3D->GetBinContent(realbinx2, realbiny2, realbinz2);

   Eigen::MatrixXd FakeMatrix = Eigen::MatrixXd(4, 4);

   FakeMatrix(0, 0) = e1 * e2;                 FakeMatrix(0, 1) = e1 * f2;                 FakeMatrix(0, 2) = f1 * e2;                 FakeMatrix(0, 3) = f1 * f2;
   FakeMatrix(1, 0) = e1 * (1.0 - e2);         FakeMatrix(1, 1) = e1 * (1.0 - f2);         FakeMatrix(1, 2) = f1 * (1.0 - e2);         FakeMatrix(1, 3) = f1 * (1.0 - f2);
   FakeMatrix(2, 0) = (1.0 - e1) * e2;         FakeMatrix(2, 1) = (1.0 - e1) * f2;         FakeMatrix(2, 2) = (1.0 - f1) * e2;         FakeMatrix(2, 3) = (1.0 - f1) * f2;
   FakeMatrix(3, 0) = (1.0 - e1) * (1.0 - e2); FakeMatrix(3, 1) = (1.0 - e1) * (1.0 - f2); FakeMatrix(3, 2) = (1.0 - f1) * (1.0 - e2); FakeMatrix(3, 3) = (1.0 - f1) * (1.0 - f2);

   Eigen::MatrixXd InverseFakeMatrix = FakeMatrix.inverse();

   double weight = (double)passTT - e1 * e2 * InverseFakeMatrix(0, 0) * (double)passTT
                                  - e1 * e2 * InverseFakeMatrix(0, 1) * (double)passTL
                                  - e1 * e2 * InverseFakeMatrix(0, 2) * (double)passLT
                                  - e1 * e2 * InverseFakeMatrix(0, 3) * (double)passLL;

   if(!isfinite(weight)) weight = 0.0;

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

 double Lepton1_FakeRate = 0.0;
 double Lepton2_FakeRate = 0.0;

 void GetFakeRate(double pt1, double eta1, double pt2, double eta2){

   int fakebin1 = FakeEff->FindBin(pt1, eta1);
   int fakebinx1 = fakebin1 % (FakeEff->GetNbinsX() + 2);
   int fakebiny1 = fakebin1 / (FakeEff->GetNbinsX() + 2);

   int fakebin2 = FakeEff->FindBin(pt2, eta2);
   int fakebinx2 = fakebin2 % (FakeEff->GetNbinsX() + 2);
   int fakebiny2 = fakebin2 / (FakeEff->GetNbinsX() + 2);

   double f1 = FakeEff->GetBinContent(fakebinx1, fakebiny1);
   double f2 = FakeEff->GetBinContent(fakebinx2, fakebiny2);

   Lepton1_FakeRate = f1 / (1.0 - f1);
   Lepton2_FakeRate = f2 / (1.0 - f2);

   if(Lepton1_FakeRate < 0.0) Lepton1_FakeRate = 0.0;
   if(Lepton2_FakeRate < 0.0) Lepton2_FakeRate = 0.0;

   if(!isfinite(Lepton1_FakeRate)) Lepton1_FakeRate = 0.0;
   if(!isfinite(Lepton2_FakeRate)) Lepton2_FakeRate = 0.0;
 }

};

class loopZPrime : public loopMC
{
 public:

 double ZPeakMass = 91.1876;
 double WPeakMass = 80.385;

 bool isData = false;

 HistsZPrime *myhists;

 TreeForZPrime *ZPrimeTree;
 TreeForPreZPrime *PreZPrimeTree;

 EventZPrime DefaultEvent;
 EventZPrime ProcessEvent;
 EventZPrime SelectedEvent;
 EventZPrime TruthEvent;

 double CrossSection = 1.0;
 double SumOfWeight = 1.0;
 map<pair<int, int>, double> SumOfWeightsMap;

 vector<TString> RootTypes;
 vector<int> Years;
 vector<int> DSIDs;
 bool isLooseTree = true;
 TString MCType = "";
 TString BkgShortName = "";

 bool isAdditionalWeight = false;
 bool isChangeNorm = false;

 bool isElFake_up = false;
 bool isElFake_down = false;
 bool isMuFake_up = false;
 bool isMuFake_down = false;

 bool isNormalRun = false;
 bool isFakeEffRun = false;
 bool isElRealEffRun = false;
 bool isMuRealEffRun = false;
 bool isElFakeEffRun = false;
 bool isMuFakeEffRun = false;
 bool isUnfoldRun = false;
 bool isTruthRun = false;

 bool isZPrimeinclusiveWP = true;

 loopZPrime(TString RootType);
 virtual void InputHist(HistsZPrime* &myhists);
 virtual void InputTree(TreeForZPrime *ZPrimeTree);
 virtual void InputTree(TreeForPreZPrime *PreZPrimeTree);
 virtual void ReadTree(int ifile);
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopZPrime();

 bool doFakeBkg = false;
 TFile* FakeEffFile;
 TH2D* FakeEff_El;
 TH2D* FakeEff_El_Stat_up;
 TH2D* FakeEff_El_Stat_down;
 TH2D* FakeEff_El_PromptSubtr_up;
 TH2D* FakeEff_El_PromptSubtr_down;
 TH2D* FakeEff_El_MET_up;
 TH2D* FakeEff_El_MET_down;

 TH2D* RealEff_El;
 TH2D* RealEff_El_Lepton1;
 TH2D* RealEff_El_Lepton2;
 TH2D* RealEff_El_Lepton1_Stat_up;
 TH2D* RealEff_El_Lepton2_Stat_up;
 TH2D* RealEff_El_Lepton1_Stat_down;
 TH2D* RealEff_El_Lepton2_Stat_down;

 TH2D* FakeEff_Mu;
 TH2D* FakeEff_Mu_Stat_up;
 TH2D* FakeEff_Mu_Stat_down;
 TH2D* FakeEff_Mu_PromptSubtr_up;
 TH2D* FakeEff_Mu_PromptSubtr_down;
 TH2D* FakeEff_Mu_d0sig_up;
 TH2D* FakeEff_Mu_d0sig_down;

 TH2D* RealEff_Mu;
 TH2D* RealEff_Mu_Stat_up;
 TH2D* RealEff_Mu_Stat_down;

 ZPrimeFakeWeight* WeightRun;
 ZPrimeFakeWeight* WeightRun_Stat_up;
 ZPrimeFakeWeight* WeightRun_Stat_down;
 ZPrimeFakeWeight* WeightRun_PromptSubtr_up;
 ZPrimeFakeWeight* WeightRun_PromptSubtr_down;
 ZPrimeFakeWeight* WeightRun_MET_up;
 ZPrimeFakeWeight* WeightRun_MET_down;
 ZPrimeFakeWeight* WeightRun_d0sig_up;
 ZPrimeFakeWeight* WeightRun_d0sig_down;
 ZPrimeFakeWeight* WeightRun_RealStat_up;
 ZPrimeFakeWeight* WeightRun_RealStat_down;

 bool doElFakeBkg = false;
 bool doMuFakeBkg = false;
 virtual void InputFakeEff(TString name){
   doFakeBkg = true;
   FakeEffFile = new TFile(name);

   TObject* obj_el = 0;
   obj_el = FakeEffFile->Get("FakeEfficiency2D_el_pt_eta");

   TObject* obj_mu = 0;
   obj_mu = FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta");

   if(obj_el && !obj_mu){
     doElFakeBkg = true;
     cout<<"Run electron fake background:"<<endl;

     FakeEff_El = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta");
     FakeEff_El_Stat_up = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta_Stat_up");
     FakeEff_El_Stat_down = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta_Stat_down");
     FakeEff_El_PromptSubtr_up = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta_PromptSubtr_up");
     FakeEff_El_PromptSubtr_down = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta_PromptSubtr_down");
     FakeEff_El_MET_up = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta_MET_up");
     FakeEff_El_MET_down = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_el_pt_eta_MET_down");
     //RealEff_El = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta");
     RealEff_El_Lepton1 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_Lepton1");
     RealEff_El_Lepton2 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_Lepton2");
     RealEff_El_Lepton1_Stat_up = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_Lepton1_Stat_up");
     RealEff_El_Lepton2_Stat_up = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_Lepton2_Stat_up");
     RealEff_El_Lepton1_Stat_down = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_Lepton1_Stat_down");
     RealEff_El_Lepton2_Stat_down = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_Lepton2_Stat_down");
     //RealEff_El_PtEtaD0Sig_Lepton1 = (TH3D *)FakeEffFile->Get("RealEfficiency3D_el_pt_eta_d0sig_Lepton1");
     //RealEff_El_PtEtaD0Sig_Lepton2 = (TH3D *)FakeEffFile->Get("RealEfficiency3D_el_pt_eta_d0sig_Lepton2");

     //RealEff_El_Lepton1 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_d0sig_Lepton1");
     //RealEff_El_Lepton2 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_d0sig_Lepton2");

     //RealEff_El_LowD0Sig_Lepton1 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_LowD0Sig_Lepton1");
     //RealEff_El_LowD0Sig_Lepton2 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_LowD0Sig_Lepton2");
     //RealEff_El_HighD0Sig_Lepton1 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_HighD0Sig_Lepton1");
     //RealEff_El_HighD0Sig_Lepton2 = (TH2D *)FakeEffFile->Get("RealEfficiency2D_el_pt_eta_HighD0Sig_Lepton2");

     WeightRun = new ZPrimeFakeWeight();
     //WeightRun->InputEff(FakeEff_El, RealEff_El);
     WeightRun->InputEff(FakeEff_El, RealEff_El_Lepton1, RealEff_El_Lepton2);
     //WeightRun->InputEff(FakeEff_El, RealEff_El_PtEtaD0Sig_Lepton1, RealEff_El_PtEtaD0Sig_Lepton2);
     //WeightRun->InputEff(FakeEff_El, RealEff_El_LowD0Sig_Lepton1, RealEff_El_LowD0Sig_Lepton2, RealEff_El_HighD0Sig_Lepton1, RealEff_El_HighD0Sig_Lepton2);

     WeightRun_Stat_up = new ZPrimeFakeWeight();
     WeightRun_Stat_up->InputEff(FakeEff_El_Stat_up, RealEff_El_Lepton1, RealEff_El_Lepton2);
     WeightRun_Stat_down = new ZPrimeFakeWeight();
     WeightRun_Stat_down->InputEff(FakeEff_El_Stat_down, RealEff_El_Lepton1, RealEff_El_Lepton2);

     WeightRun_PromptSubtr_up = new ZPrimeFakeWeight();
     WeightRun_PromptSubtr_up->InputEff(FakeEff_El_PromptSubtr_up, RealEff_El_Lepton1, RealEff_El_Lepton2);
     WeightRun_PromptSubtr_down = new ZPrimeFakeWeight();
     WeightRun_PromptSubtr_down->InputEff(FakeEff_El_PromptSubtr_down, RealEff_El_Lepton1, RealEff_El_Lepton2);

     WeightRun_MET_up = new ZPrimeFakeWeight();
     WeightRun_MET_up->InputEff(FakeEff_El_MET_up, RealEff_El_Lepton1, RealEff_El_Lepton2);
     WeightRun_MET_down = new ZPrimeFakeWeight();
     WeightRun_MET_down->InputEff(FakeEff_El_MET_down, RealEff_El_Lepton1, RealEff_El_Lepton2);

     WeightRun_RealStat_up = new ZPrimeFakeWeight();
     WeightRun_RealStat_up->InputEff(FakeEff_El, RealEff_El_Lepton1_Stat_up, RealEff_El_Lepton2_Stat_up);
     WeightRun_RealStat_down = new ZPrimeFakeWeight();
     WeightRun_RealStat_down->InputEff(FakeEff_El, RealEff_El_Lepton1_Stat_down, RealEff_El_Lepton2_Stat_down);

   }
   else if(!obj_el && obj_mu){
     doMuFakeBkg = true;
     cout<<"Run muon fake background:"<<endl;

     FakeEff_Mu = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta");
     FakeEff_Mu_Stat_up = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta_Stat_up");
     FakeEff_Mu_Stat_down = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta_Stat_down");
     FakeEff_Mu_PromptSubtr_up = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta_PromptSubtr_up");
     FakeEff_Mu_PromptSubtr_down = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta_PromptSubtr_down");
     FakeEff_Mu_d0sig_up = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta_d0sig_up");
     FakeEff_Mu_d0sig_down = (TH2D *)FakeEffFile->Get("FakeEfficiency2D_mu_pt_eta_d0sig_down");

     RealEff_Mu = (TH2D *)FakeEffFile->Get("RealEfficiency2D_mu_pt_eta");
     RealEff_Mu_Stat_up = (TH2D *)FakeEffFile->Get("RealEfficiency2D_mu_pt_eta_Stat_up");
     RealEff_Mu_Stat_down = (TH2D *)FakeEffFile->Get("RealEfficiency2D_mu_pt_eta_Stat_down");

     WeightRun = new ZPrimeFakeWeight();
     WeightRun->InputEff(FakeEff_Mu, RealEff_Mu);

     WeightRun_Stat_up = new ZPrimeFakeWeight();
     WeightRun_Stat_up->InputEff(FakeEff_Mu_Stat_up, RealEff_Mu);
     WeightRun_Stat_down = new ZPrimeFakeWeight();
     WeightRun_Stat_down->InputEff(FakeEff_Mu_Stat_down, RealEff_Mu);

     WeightRun_PromptSubtr_up = new ZPrimeFakeWeight();
     WeightRun_PromptSubtr_up->InputEff(FakeEff_Mu_PromptSubtr_up, RealEff_Mu);
     WeightRun_PromptSubtr_down = new ZPrimeFakeWeight();
     WeightRun_PromptSubtr_down->InputEff(FakeEff_Mu_PromptSubtr_down, RealEff_Mu);

     WeightRun_d0sig_up = new ZPrimeFakeWeight();
     WeightRun_d0sig_up->InputEff(FakeEff_Mu_d0sig_up, RealEff_Mu);
     WeightRun_d0sig_down = new ZPrimeFakeWeight();
     WeightRun_d0sig_down->InputEff(FakeEff_Mu_d0sig_down, RealEff_Mu);

     WeightRun_RealStat_up = new ZPrimeFakeWeight();
     WeightRun_RealStat_up->InputEff(FakeEff_Mu, RealEff_Mu_Stat_up);
     WeightRun_RealStat_down = new ZPrimeFakeWeight();
     WeightRun_RealStat_down->InputEff(FakeEff_Mu, RealEff_Mu_Stat_down);
   }
   else if(obj_el && obj_mu){
     cout<<"WARNING! Do NOT run electron and muon fake background together!"<<endl;
   }
   else if(!obj_el && !obj_mu){
     cout<<"ERROR! No fake/real efficiency found!"<<endl;
   }
 }

 bool doApplyKFactor = true;
 TFile* KFactorFile;
 TH1D* KFactorHist;
 virtual void InputKFactor(TString name){
   KFactorFile = new TFile(name);
   KFactorHist = (TH1D *)KFactorFile->Get("KFactor");

   doApplyKFactor = true;
 }

 TString AngularFileName = "";
 virtual void InputAngularFile(TString name){
   AngularFileName = name;
 }

 virtual void ControlNormalRun(TString RunType){
   if(RunType == "NormalRun"){
     isNormalRun = true;
     isFakeEffRun = false;
   }
   else if(RunType == "FakeEffRun"){
     isNormalRun = false;
     isFakeEffRun = true;
   }
   else if(RunType == "ElRealEffRun"){
     isNormalRun = false;
     isFakeEffRun = false;
     isElRealEffRun = true;
   }
   else if(RunType == "MuRealEffRun"){
     isNormalRun = false;
     isFakeEffRun = false;
     isMuRealEffRun = true;
   }
   else if(RunType == "ElFakeEffRun"){
     isElFakeEffRun = true;
   }
   else if(RunType == "MuFakeEffRun"){
     isMuFakeEffRun = true;
   }
   else if(RunType == "UnfoldRun"){
     isUnfoldRun = true;
   }
   else if(RunType == "TruthRun"){
     isTruthRun = true;
   }
 }

 bool isInputPreTree = false;
 TString NtupleName;

 virtual void InputNtupleName(TString NtupleName);
 virtual void PreLoop(int ifile);
 virtual bool FillEvents();

 virtual void FillHist(EventZPrime ProcessEvent);
 virtual void FillTopDDHist(EventZPrime ProcessEvent);

 virtual void GetCutInformation();
 virtual void FillCutFlow();
 virtual void FillWeightedCutFlow();

 bool doTopDD = false;
 ZPrimetopDDHelper* topDD;
 ZPrimetopDDHelper* topDD_HighMass_CosTheta;
 ZPrimetopDDHelper* topDD_HighMass_Rapidity;

 bool doSignalReweight = true;
 ZPrimeTripletSignalModule* SSMModel_0p5TeV;
 ZPrimeTripletSignalModule* SSMModel_0p6TeV;
 ZPrimeTripletSignalModule* SSMModel_0p8TeV;
 ZPrimeTripletSignalModule* SSMModel_1TeV;
 ZPrimeTripletSignalModule* SSMModel_2TeV;
 ZPrimeTripletSignalModule* SSMModel_3TeV;
 ZPrimeTripletSignalModule* SSMModel_4TeV;
 ZPrimeTripletSignalModule* SSMModel_5TeV;
 ZPrimeTripletSignalModule* SSMModel_6TeV;
 ZPrimeTripletSignalModule* SSMModel_7TeV;
 ZPrimeTripletSignalModule* SSMModel_8TeV;

 ZPrimeTripletSignalModule* E6ChiModel_0p5TeV;
 ZPrimeTripletSignalModule* E6ChiModel_0p6TeV;
 ZPrimeTripletSignalModule* E6ChiModel_0p8TeV;
 ZPrimeTripletSignalModule* E6ChiModel_1TeV;
 ZPrimeTripletSignalModule* E6ChiModel_2TeV;
 ZPrimeTripletSignalModule* E6ChiModel_3TeV;
 ZPrimeTripletSignalModule* E6ChiModel_4TeV;
 ZPrimeTripletSignalModule* E6ChiModel_5TeV;
 ZPrimeTripletSignalModule* E6ChiModel_6TeV;
 ZPrimeTripletSignalModule* E6ChiModel_7TeV;
 ZPrimeTripletSignalModule* E6ChiModel_8TeV;

 ZPrimeTripletSignalModule* E6PsiModel_0p5TeV;
 ZPrimeTripletSignalModule* E6PsiModel_0p6TeV;
 ZPrimeTripletSignalModule* E6PsiModel_0p8TeV;
 ZPrimeTripletSignalModule* E6PsiModel_1TeV;
 ZPrimeTripletSignalModule* E6PsiModel_2TeV;
 ZPrimeTripletSignalModule* E6PsiModel_3TeV;
 ZPrimeTripletSignalModule* E6PsiModel_4TeV;
 ZPrimeTripletSignalModule* E6PsiModel_5TeV;
 ZPrimeTripletSignalModule* E6PsiModel_6TeV;
 ZPrimeTripletSignalModule* E6PsiModel_7TeV;
 ZPrimeTripletSignalModule* E6PsiModel_8TeV;

 ///////////////
 //  Control  //
 ///////////////

 bool JustGenerateTree = false;
 bool FinishProcess = false;
 virtual void ProcessOption(int iflag){
   if(iflag == 1){
     JustGenerateTree = true;
     FinishProcess = false;
   }
   if(iflag == 2){
     JustGenerateTree = false;
     FinishProcess = true;
   }
 }

 TFile* TriggerFile = 0;
 virtual double GetGlobalTriggerSF(int randomRunNumber, double el1_pt, double el1_eta, double el2_pt, double el2_eta);

 virtual double Zgamma_CT14nnlo_CT10_New(double x);
 virtual double Zgamma_CT18NNLO_CT14nnlo_Central_spline(double x);
 virtual double Zgamma_CT18ANNLO_CT14nnlo_Central_spline(double x);
 virtual double Zgamma_CT18ANNLO_CT14nnlo_Up_spline(double x);
 virtual double Zgamma_CT18ANNLO_CT14nnlo_Down_spline(double x);
 virtual double ew_z_spline(double x);
 virtual double Zgamma_CT10nnlo_CT10nnlo(double x);

 virtual double Zgamma_13p6TeV_CT18ANNLO_CT10_Central_spline(double x);
 virtual double Zgamma_13p6TeV_CT18ANNLO_CT10_Up_spline(double x);
 virtual double Zgamma_13p6TeV_CT18ANNLO_CT10_Down_spline(double x);

 virtual double GetZPrimeCrossSection(int mcChannelNumber);

};
#endif
