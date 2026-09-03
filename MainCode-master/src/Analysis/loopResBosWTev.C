#define loopResBosWTev_cxx
#include <iostream>
#include "Analysis/loopResBosWTev.h"

using namespace std;

loopResBosWTev::loopResBosWTev(TString RootType)
{
 this->RootType = RootType;

 Sta_TotalNumber = 0;

 isThread = false;

 EW = new ResBosEW();
}

void loopResBosWTev::InputHist(HistsResBosWTev* &myhists)
{
 this->myhists = myhists;

}

void loopResBosWTev::InputTree(TreeForResBos *ResBosTree)
{
 this->ResBosTree = ResBosTree;
 this->RootNames = ResBosTree->RootNames;
 this->isFSR = ResBosTree->isFSR;

 this->FirstFile = ResBosTree->FirstFile;
 this->EndFile = ResBosTree->EndFile;

 this->OneFilePerJob = ResBosTree->OneFilePerJob;

 this->RootTypesForResBosW = ResBosTree->RootTypes;

 for(int ifile = FirstFile; ifile < EndFile; ifile++){
   TotalEntries[ifile] = ResBosTree->TotalEntries[ifile];
 }

}

void loopResBosWTev::ReadTree(int ifile)
{
// For pseudodata
// TRandom3 random_lepton(0);
// TRandom3 random_neutrino(0);
// TRandom3 random_electron(0);
// TRandom3 random_positron(0);

// For WMass template
 random_lepton.SetSeed(100);
 random_neutrino.SetSeed(200);
 random_electron.SetSeed(300);
 random_positron.SetSeed(400);

 isAntiLepton = false;
 isLepton = false;

 bool isZEvent = false;
 bool isWEvent = false;

 if(RootTypesForResBosW.at(ifile) == "wp") isAntiLepton = true;
 if(RootTypesForResBosW.at(ifile) == "wm") isLepton = true;
 if(RootTypesForResBosW.at(ifile) == "zu" || RootTypesForResBosW.at(ifile) == "zd") isZEvent = true;

 if(isAntiLepton || isLepton) isWEvent = true;

 if(isAntiLepton) cout<<"Loop W+ sample"<<endl;
 if(isLepton) cout<<"Loop W- sample"<<endl;

 for(long i = InitialEntry - 1; i < Nentries; i++){
   Sta_TotalNumber++;

   if(Sta_TotalNumber % 1000000 == 0){
     if(isThread) cout<<"Thread No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
     if(!isThread) cout<<"Condor No."<<iThread<<": "<<Sta_TotalNumber<<" events have finished."<<endl;
   }

   ResBosTree->GetEntry(ifile, i);
   Neutrino.SetPxPyPzE(ResBosTree->ElectronPx, ResBosTree->ElectronPy, ResBosTree->ElectronPz, ResBosTree->ElectronE);
   AntiLepton.SetPxPyPzE(ResBosTree->PositronPx, ResBosTree->PositronPy, ResBosTree->PositronPz, ResBosTree->PositronE);
   Lepton.SetPxPyPzE(ResBosTree->PositronPx, ResBosTree->PositronPy, ResBosTree->PositronPz, ResBosTree->PositronE);
   WBoson = Neutrino + Lepton;

   Weight = ResBosTree->Weight;

   if(!isfinite(Weight)) continue;

   if(isWEvent) FillWEvents();
   if(isZEvent) FillZEvents();
 }

}

void loopResBosWTev::FillWEvents()
{
///////////////////////////////////////////////////////////////////////

   /////////////////////////
   //  WMass Reweighting  //
   /////////////////////////

   double WMassWeight = GetWMassReweightingFactor(WBoson.M(), OriginWMass, NewWMass);
   Weight = Weight * WMassWeight;

///////////////////////////////////////////////////////////////////////

   /////////////////////////////////////
   //  pT(W)/pT(Z) Scale Reweighting  //
   /////////////////////////////////////

   double ScaleUpWeight = GetWPtReweightingFactor(WBoson.Pt(), 1.0);
   double ScaleDownWeight = GetWPtReweightingFactor(WBoson.Pt(), -1.0);
   double ScaleVariWeight = GetWPtReweightingFactor(WBoson.Pt(), ScaleSlope);
   Weight = Weight * ScaleVariWeight;

///////////////////////////////////////////////////////////////////////

   ///////////////////////////
   //  Detector resolution  //
   ///////////////////////////

/*
   myGausRandom = random_lepton.Gaus(0, 1);
   Lepton_Smear = Lepton * (1 + 0.05 * myGausRandom);
   myGausRandom = random_neutrino.Gaus(0, 1);
   Neutrino_Smear = Neutrino * (1 + 0.11 * myGausRandom);

   myGausRandom = random_electron.Gaus(0, 1);
   Electron_Smear = Neutrino * (1 + 0.05 * myGausRandom);
   myGausRandom = random_positron.Gaus(0, 1);
   Positron_Smear = Lepton * (1 + 0.05 * myGausRandom);
*/


   //Fit for lepton and neutrino seperately
   LepPara1 = 0.05144;
   LepPara2 = 0.131928;
   LepPara3 = 0.0381294;
   NuPara1 = 0.0851759;
   NuPara2 = 0.0882579;
   NuPara3 = 0.0288224;
   LepScale = 1.00249;
   NuScale = 1.00628;


/*
   //best fit for MT, Lepton.Pt() > 0
   LepPara1 = 0.0595494;
   LepPara2 = 0.00866242;
   LepPara3 = 0.0090333;
   NuPara1 = 0.11189;
   NuPara2 = 0.161067;
   NuPara3 = 0.499477;
   LepScale = 0.996653;
   NuScale = 0.998692;
*/

/*
   //Lepton.Pt() > 36
   LepPara1 = 0.0751461;
   LepPara2 = 0.148747;
   LepPara3 = 0.0103548;
   NuPara1 = 0.193632;
   NuPara2 = 0.000690897;
   NuPara3 = 0.0948634;
   LepScale = 0.967382;
   NuScale = 0.94288;
*/

/*
   //best fit for MT, MT > 70, pT(l) > 35, pT(v) > 35
   LepPara1 = 0.039799;
   LepPara2 = 0.000425894;
   LepPara3 = 0.235452;
   NuPara1 = 0.130599;
   NuPara2 = 0.0835558;
   NuPara3 = 0.49995;
   LepScale = 1.00082;
   NuScale = 0.981288;
*/

   myGausRandom = random_lepton.Gaus(0, 1);
   Lepton_Smear = Lepton * LepScale * (1 + sqrt(LepPara1 * LepPara1 + LepPara2 * LepPara2 / Lepton.E() / Lepton.E() + LepPara3 * LepPara3 / Lepton.E()) * myGausRandom);
   myGausRandom = random_neutrino.Gaus(0, 1);
   Neutrino_Smear = Neutrino * NuScale * (1 + sqrt(NuPara1 * NuPara1 + NuPara2 * NuPara2 / Neutrino.E() / Neutrino.E() + NuPara3 * NuPara3 / Neutrino.E()) * myGausRandom);

   myGausRandom = random_electron.Gaus(0, 1);
   Electron_Smear = Neutrino * LepScale * (1 + sqrt(LepPara1 * LepPara1 + LepPara2 * LepPara2 / Neutrino.E() / Neutrino.E() + LepPara3 * LepPara3 / Neutrino.E()) * myGausRandom);
   myGausRandom = random_positron.Gaus(0, 1);
   Positron_Smear = Lepton * LepScale * (1 + sqrt(LepPara1 * LepPara1 + LepPara2 * LepPara2 / Lepton.E() / Lepton.E() + LepPara3 * LepPara3 / Lepton.E()) * myGausRandom);


   WBoson_Smear = Lepton_Smear + Neutrino_Smear;
   ZBoson_Smear = Electron_Smear + Positron_Smear;

///////////////////////////////////////////////////////////////////////

   cos_theta = calculate_theta(WBoson, Neutrino, AntiLepton);
   phi = calculate_phi(Neutrino, AntiLepton, (double)ECM / 2);

   WMT = CalculateTransverseMass(Lepton, Neutrino);
   double WMT_Smear = CalculateTransverseMass(Lepton_Smear, Neutrino_Smear);

   double DeltaPhiLeptonNu = DeltaPhi(Lepton.Phi(), Neutrino.Phi());
   double DeltaPhiLeptonNu_Smear = DeltaPhi(Lepton_Smear.Phi(), Neutrino_Smear.Phi());

   double WMT_new = sqrt(WMT * WMT + WBoson.Pt() * WBoson.Pt());
   double WMT_new_Smear = sqrt(WMT_Smear * WMT_Smear + WBoson_Smear.Pt() * WBoson_Smear.Pt());

   //double WMT_real = sqrt(WBoson.M() * WBoson.M() + WBoson.Pt() * WBoson.Pt());
   //double M_construct = sqrt(WMT * WMT - WBoson.Pt() * WBoson.Pt());
   //double M_construct2 = sqrt(WMT * WMT + WBoson.E() * WBoson.E() * WBoson.Pz() * WBoson.Pz() / (WBoson.E() * WBoson.E() - WBoson.M() * WBoson.M()) - WBoson.Pz() * WBoson.Pz());
   //double WMT_2 = sqrt(WBoson.Et() * WBoson.Et() - WBoson.Pt() * WBoson.Pt());
   //double WMZ_2 = sqrt(WBoson.M() * WBoson.M() * WBoson.Pz() * WBoson.Pz() / (WBoson.E() * WBoson.E() - WBoson.M() * WBoson.M()));
   //double WMZ = sqrt(2.0 * (Lepton.E() * Neutrino.E() - Lepton.Pt() * Neutrino.Pt() - Lepton.Pz() * Neutrino.Pz()));

   //cout<<"WMT real = "<<WMT_real<<" WMT = "<<WMT<<" M real = "<<WBoson.M()<<" M (construct) = "<<M_construct<<" M (construct 2) = "<<M_construct2<<" WMT (Et^2 - Pt^2) = "<<WMT_2<<" WMZ (Ez^2 - Pz^2) = "<<WMZ_2<<" WMZ = "<<WMZ<<endl;
   //cout<<"Et = "<<WBoson.Et()<<" E = "<<WBoson.E()<<" Pt = "<<WBoson.Pt()<<" P = "<<sqrt(WBoson.E() * WBoson.E() - WBoson.M() * WBoson.M())<<" Calculation = "<<WBoson.E() * WBoson.Pt() / sqrt(WBoson.E() * WBoson.E() - WBoson.M() * WBoson.M())<<endl;
   //cout<<"E1 = "<<Lepton.E()<<" Px1 = "<<Lepton.Px()<<" Py1 = "<<Lepton.Py()<<" Pz1 = "<<Lepton.Pz()<<" E2 = "<<Neutrino.E()<<" Px2 = "<<Neutrino.Px()<<" Py2 = "<<Neutrino.Py()<<" Pz2 = "<<Neutrino.Pz()<<endl;

   pass_w225 = (Lepton.Pt() > 25)
             && (fabs(Lepton.Eta()) < 2.5)
             && (Neutrino.Pt() > 25);

   pass_w227 = (Lepton.Pt() > 25)
             && (fabs(Lepton.Eta()) < 4.5)
             && (Neutrino.Pt() > 25)
             && (WMT > 50)
             && (WMT < 100);

   pass_w234 = (Lepton.Pt() > 20)
             && (fabs(Lepton.Eta()) < 2.0)
             && (Neutrino.Pt() > 20)
             && (WMT > 40)
             && (WMT < 1000);

   pass_w281 = (Lepton.Pt() > 25)
             && (fabs(Lepton.Eta()) < 3.2)
             && (Neutrino.Pt() > 25)
             && (WMT > 50)
             && (WMT < 130);

   bool isCDF = (Lepton.Pt() > 30) && (Lepton.Pt() < 55)
             && (Neutrino.Pt() > 30) && (Neutrino.Pt() < 55)
             && (WBoson.Pt() < 15)
             && (WMT > 60) && (WMT < 100)
             && (fabs(Lepton.Eta()) < 1.0);

   bool isCDFZ = (WBoson.M() > 66) && (WBoson.M() < 116)
              && (WBoson.Pt() < 30)
              && (Neutrino.Pt() > 30)
              && (Lepton.Pt() > 30)
              && (fabs(Lepton.Eta()) < 1.0)
              && (fabs(Neutrino.Eta()) < 1.0);

   bool isCDF_Smear = (Lepton_Smear.Pt() > 30) && (Lepton_Smear.Pt() < 55)
                   && (Neutrino_Smear.Pt() > 30) && (Neutrino_Smear.Pt() < 55)
                   && (WBoson_Smear.Pt() < 15)
                   && (WMT_Smear > 60) && (WMT_Smear < 100)
                   && (fabs(Lepton_Smear.Eta()) < 1.0);

   bool isCDFZ_Smear = (ZBoson_Smear.M() > 66) && (ZBoson_Smear.M() < 116)
                    && (ZBoson_Smear.Pt() < 30)
                    && (Electron_Smear.Pt() > 30)
                    && (Positron_Smear.Pt() > 30)
                    && (fabs(Electron_Smear.Eta()) < 1.0)
                    && (fabs(Positron_Smear.Eta()) < 1.0);

   bool isJacobianAsym = (WBoson.M() > 66) && (WBoson.M() < 116)
                      && (WMT > 27)
                      && (Lepton.Pt() > 20)
                      && (fabs(Lepton.Eta()) < 2.5);

   bool isJacobianAsymLowQT = (Neutrino.Pt() > 30)
                           && (WMT > 60)
                           && (WBoson.Pt() < 30)
                           && (Lepton.Pt() > 30)
                           && (fabs(Lepton.Eta()) < 2.4);

   vector<double> MultiWMassWeight(21);
   vector<double> MultiWMassWeightLowQT(21);

   for(int iWeight = 0; iWeight < MultiWMassWeight.size(); iWeight++){
     MultiWMassWeight.at(iWeight) = ResBosTree->Weight * isJacobianAsym * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.329 + iWeight * 0.005);
   }
   for(int iWeight = 0; iWeight < MultiWMassWeight.size(); iWeight++){
     MultiWMassWeightLowQT.at(iWeight) = ResBosTree->Weight * isJacobianAsymLowQT * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.329 + iWeight * 0.005);
   }

   myhists->LeptonPt->at(iThread - 1)->Fill(Lepton.Pt(), Weight);

   myhists->MtW_CDF->at(iThread - 1)->Fill(WMT, Weight * isCDF);
   myhists->LeptonPt_CDF->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isCDF);
   myhists->NuPt_CDF->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * isCDF);
   myhists->LeptonPt_WPlus_CDF->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isCDF * isAntiLepton);
   myhists->NuPt_WPlus_CDF->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * isCDF * isAntiLepton);
   myhists->LeptonPt_WMinus_CDF->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isCDF * isLepton);
   myhists->NuPt_WMinus_CDF->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * isCDF * isLepton);
   myhists->DeltaPhi_CDF->at(iThread - 1)->Fill(fabs(DeltaPhiLeptonNu), Weight * isCDF);
   myhists->WPt_CDF->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDF);
   //myhists->ZPt_CDF->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDFZ);
   myhists->WPt_CDF_FineBin->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDF);
   //myhists->ZPt_CDF_FineBin->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDFZ);
   myhists->WPt_CDF_ScaleUp->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDF * ScaleUpWeight);
   myhists->WPt_CDF_ScaleDown->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDF * ScaleDownWeight);
   myhists->WPt_CDF_ScaleVari->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDF * ScaleVariWeight);

   myhists->MtW_CDF_Smear->at(iThread - 1)->Fill(WMT_Smear, Weight * isCDF_Smear);
   myhists->LeptonPt_CDF_Smear->at(iThread - 1)->Fill(Lepton_Smear.Pt(), Weight * isCDF_Smear);
   myhists->NuPt_CDF_Smear->at(iThread - 1)->Fill(Neutrino_Smear.Pt(), Weight * isCDF_Smear);
   myhists->DeltaPhi_CDF_Smear->at(iThread - 1)->Fill(fabs(DeltaPhiLeptonNu_Smear), Weight * isCDF_Smear);
   myhists->WPt_CDF_Smear->at(iThread - 1)->Fill(WBoson_Smear.Pt(), Weight * isCDF_Smear);
   //myhists->ZPt_CDF_Smear->at(iThread - 1)->Fill(ZBoson_Smear.Pt(), Weight * isCDFZ_Smear);

   myhists->MtW_Inclusive->at(iThread - 1)->Fill(WMT, Weight);
   myhists->LeptonPt_Inclusive->at(iThread - 1)->Fill(Lepton.Pt(), Weight);
   myhists->NuPt_Inclusive->at(iThread - 1)->Fill(Neutrino.Pt(), Weight);
   myhists->LeptonPt_WPlus_Inclusive->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isAntiLepton);
   myhists->NuPt_WPlus_Inclusive->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * isAntiLepton);
   myhists->LeptonPt_WMinus_Inclusive->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isLepton);
   myhists->NuPt_WMinus_Inclusive->at(iThread - 1)->Fill(Neutrino.Pt(), Weight * isLepton);
   myhists->LeptonEta_WPlus_Inclusive->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isAntiLepton);
   myhists->NuEta_WPlus_Inclusive->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * isAntiLepton);
   myhists->LeptonEta_WMinus_Inclusive->at(iThread - 1)->Fill(Lepton.Eta(), Weight * isLepton);
   myhists->NuEta_WMinus_Inclusive->at(iThread - 1)->Fill(Neutrino.Eta(), Weight * isLepton);
   myhists->DeltaPhi_Inclusive->at(iThread - 1)->Fill(fabs(DeltaPhiLeptonNu), Weight);
   myhists->WPt_Inclusive->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
   //myhists->ZPt_Inclusive->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
   myhists->WPt_Inclusive_LargeRange->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
   //myhists->ZPt_Inclusive_LargeRange->at(iThread - 1)->Fill(WBoson.Pt(), Weight);

   myhists->WMass_Inclusive->at(iThread - 1)->Fill(WBoson.M(), Weight);

   myhists->MtW_EventCount->at(iThread - 1)->Fill(WMT, isCDF);
   myhists->MtW_Smear_EventCount->at(iThread - 1)->Fill(WMT, isCDF_Smear);

   myhists->MtW_new_CDF->at(iThread - 1)->Fill(WMT_new, Weight * isCDF);
   myhists->MtW_new_CDF_Smear->at(iThread - 1)->Fill(WMT_new_Smear, Weight * isCDF_Smear);

   myhists->LeptonPt_LHC_Low_multiweight->at(iThread - 1)->Fill(Lepton.Pt(), MultiWMassWeight);
   myhists->LeptonPt_LHC_High_multiweight->at(iThread - 1)->Fill(Lepton.Pt(), MultiWMassWeight);

   myhists->LeptonPt_LHC->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsym * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.379));
   myhists->LeptonPt_LHC_WPlus->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsym * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.379) * isAntiLepton);
   myhists->LeptonPt_LHC_WMinus->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsym * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.379) * isLepton);

   myhists->LeptonPt_LHC_Low->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsym * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.379));
   myhists->LeptonPt_LHC_High->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsym * GetWMassReweightingFactor(WBoson.M(), OriginWMass, 80.379));

   myhists->LeptonPt_LowQT_LHC_Low_multiweight->at(iThread - 1)->Fill(Lepton.Pt(), MultiWMassWeightLowQT);
   myhists->LeptonPt_LowQT_LHC_High_multiweight->at(iThread - 1)->Fill(Lepton.Pt(), MultiWMassWeightLowQT);

   myhists->LeptonPt_LowQT_LHC->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isJacobianAsymLowQT);
   myhists->LeptonPt_LowQT_LHC_Tail->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isJacobianAsymLowQT);
   myhists->LeptonPt_LowQT_LHC_Low->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isJacobianAsymLowQT);
   myhists->LeptonPt_LowQT_LHC_High->at(iThread - 1)->Fill(Lepton.Pt(), Weight * isJacobianAsymLowQT);
   myhists->MtW_LowQT_LHC->at(iThread - 1)->Fill(WMT, Weight * isJacobianAsymLowQT);

   MultiWMassWeight.clear();
   MultiWMassWeightLowQT.clear();

   if(isAntiLepton){
     myhists->LeptonEta_w225->at(iThread - 1)->Fill(AntiLepton.Eta() * (-1), Weight * pass_w225);
     myhists->AntiLeptonEta_w225->at(iThread - 1)->Fill(AntiLepton.Eta(), Weight * pass_w225);

     myhists->LeptonEta_w227->at(iThread - 1)->Fill(AntiLepton.Eta() * (-1), Weight * pass_w227);
     myhists->AntiLeptonEta_w227->at(iThread - 1)->Fill(AntiLepton.Eta(), Weight * pass_w227);

     myhists->LeptonEta_w234->at(iThread - 1)->Fill(AntiLepton.Eta() * (-1), Weight * pass_w234);
     myhists->AntiLeptonEta_w234->at(iThread - 1)->Fill(AntiLepton.Eta(), Weight * pass_w234);

     myhists->LeptonEta_w281->at(iThread - 1)->Fill(AntiLepton.Eta() * (-1), Weight * pass_w281);
     myhists->AntiLeptonEta_w281->at(iThread - 1)->Fill(AntiLepton.Eta(), Weight * pass_w281);

     myhists->WPlusRapidity->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
     myhists->WPlusPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight);

     myhists->AntiLeptonEta->at(iThread - 1)->Fill(AntiLepton.Eta(), Weight);
   }
   if(isLepton){
     myhists->WMinusRapidity->at(iThread - 1)->Fill(WBoson.Rapidity(), Weight);
     myhists->WMinusPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight);

     myhists->LeptonEta->at(iThread - 1)->Fill(AntiLepton.Eta(), Weight);
   }

   myhists->A0_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A0_ZPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);
   myhists->A1_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A1_ZPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);
   myhists->A2_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A2_ZPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);
   myhists->A3_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A3_ZPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);
   myhists->A4_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->A4_ZPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);
   myhists->L0_ZPt->at(iThread - 1)->Initial(cos_theta, phi);
   myhists->L0_ZPt->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);

   if(WBoson.Pt() < 20){
     myhists->A0_ZY->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A0_ZY->at(iThread - 1)->Fill((WBoson.Rapidity()), Weight * isAntiLepton);
     myhists->A1_ZY->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A1_ZY->at(iThread - 1)->Fill((WBoson.Rapidity()), Weight * isAntiLepton);
     myhists->A2_ZY->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A2_ZY->at(iThread - 1)->Fill((WBoson.Rapidity()), Weight * isAntiLepton);
     myhists->A3_ZY->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A3_ZY->at(iThread - 1)->Fill((WBoson.Rapidity()), Weight * isAntiLepton);
     myhists->A4_ZY->at(iThread - 1)->Initial(cos_theta, phi);
     myhists->A4_ZY->at(iThread - 1)->Fill((WBoson.Rapidity()), Weight * isAntiLepton);
   }

   myhists->WPlusPt_LHC->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isAntiLepton);
   myhists->WMinusPt_LHC->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isLepton);
}

void loopResBosWTev::FillZEvents()
{
   //Fit for lepton and neutrino seperately
   LepPara1 = 0.05144;
   LepPara2 = 0.131928;
   LepPara3 = 0.0381294;
   NuPara1 = 0.0851759;
   NuPara2 = 0.0882579;
   NuPara3 = 0.0288224;
   LepScale = 1.00249;
   NuScale = 1.00628;

   myGausRandom = random_lepton.Gaus(0, 1);
   Lepton_Smear = Lepton * LepScale * (1 + sqrt(LepPara1 * LepPara1 + LepPara2 * LepPara2 / Lepton.E() / Lepton.E() + LepPara3 * LepPara3 / Lepton.E()) * myGausRandom);
   myGausRandom = random_neutrino.Gaus(0, 1);
   Neutrino_Smear = Neutrino * NuScale * (1 + sqrt(NuPara1 * NuPara1 + NuPara2 * NuPara2 / Neutrino.E() / Neutrino.E() + NuPara3 * NuPara3 / Neutrino.E()) * myGausRandom);

   myGausRandom = random_electron.Gaus(0, 1);
   Electron_Smear = Neutrino * LepScale * (1 + sqrt(LepPara1 * LepPara1 + LepPara2 * LepPara2 / Neutrino.E() / Neutrino.E() + LepPara3 * LepPara3 / Neutrino.E()) * myGausRandom);
   myGausRandom = random_positron.Gaus(0, 1);
   Positron_Smear = Lepton * LepScale * (1 + sqrt(LepPara1 * LepPara1 + LepPara2 * LepPara2 / Lepton.E() / Lepton.E() + LepPara3 * LepPara3 / Lepton.E()) * myGausRandom);


   WBoson_Smear = Lepton_Smear + Neutrino_Smear;
   ZBoson_Smear = Electron_Smear + Positron_Smear;

   bool isCDFZ = (WBoson.M() > 66) && (WBoson.M() < 116)
              && (WBoson.Pt() < 30)
              && (Neutrino.Pt() > 30)
              && (Lepton.Pt() > 30)
              && (fabs(Lepton.Eta()) < 1.0)
              && (fabs(Neutrino.Eta()) < 1.0);

   bool isCDFZ_Smear = (ZBoson_Smear.M() > 66) && (ZBoson_Smear.M() < 116)
                    && (ZBoson_Smear.Pt() < 30)
                    && (Electron_Smear.Pt() > 30)
                    && (Positron_Smear.Pt() > 30)
                    && (fabs(Electron_Smear.Eta()) < 1.0)
                    && (fabs(Positron_Smear.Eta()) < 1.0);

   bool isJacobianAsymLowQTZ = (WBoson.M() > 66) && (WBoson.M() < 116)
                            && (WBoson.Pt() < 15)
                            && (Lepton.Pt() > 20)
                            && (Neutrino.Pt() > 20)
                            && (fabs(Lepton.Eta()) < 2.5)
                            && (fabs(Neutrino.Eta()) < 2.5);

   myhists->LeptonPt_LowQT_Z_LHC_Low->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsymLowQTZ);
   myhists->LeptonPt_LowQT_Z_LHC_High->at(iThread - 1)->Fill(Lepton.Pt(), ResBosTree->Weight * isJacobianAsymLowQTZ);

   myhists->LeptonPt_LowQT_Z_LHC_Low->at(iThread - 1)->Fill(Neutrino.Pt(), ResBosTree->Weight * isJacobianAsymLowQTZ);
   myhists->LeptonPt_LowQT_Z_LHC_High->at(iThread - 1)->Fill(Neutrino.Pt(), ResBosTree->Weight * isJacobianAsymLowQTZ);

   myhists->ZPt_LHC->at(iThread - 1)->Fill(WBoson.Pt(), Weight);

   myhists->ZPt_CDF->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDFZ);
   myhists->ZPt_CDF_FineBin->at(iThread - 1)->Fill(WBoson.Pt(), Weight * isCDFZ);
   myhists->ZPt_CDF_Smear->at(iThread - 1)->Fill(ZBoson_Smear.Pt(), Weight * isCDFZ_Smear);

   myhists->ZPt_Inclusive->at(iThread - 1)->Fill(WBoson.Pt(), Weight);
   myhists->ZPt_Inclusive_LargeRange->at(iThread - 1)->Fill(WBoson.Pt(), Weight);

}

double loopResBosWTev::GetWMassReweightingFactor(double Q, double OriginWMass, double NewWMass)
{
/*
      [(s-M_{W0^}2)^2 + s^2/M_{W0}^2 \Gamma_W^2]/[(s-M_{Wi}^2)^2 + s^2/M_{Wi}^2 \Gamma_W^2]
      1/((s - M_W^2)^2 + s^2/M_W^2 \Gamma_W^2)

      GMU = 1.16637D-5/UNIT**2

      AEM = Sqrt(2.d0)*XMW2*GMU*SWS/Pi

      GFERMI=PI*AEM/SQRT(2.d0)/SWS/XMW2

      GAMW=GFERMI*XMW**3/6./PI/SQRT(2.)*(9.)

      GAMW_NLO_R=GAMW*(1.0+2.0*ALPHAS_MW/PI/3.0)
*/
 double GMU = 1.16637e-5;

 double SWS = 1 - (OriginWMass * OriginWMass) / (91.1876 * 91.1876);
 double AEM = sqrt(2.0) * OriginWMass * OriginWMass * GMU * SWS / TMath::Pi();
 double GFERMI = TMath::Pi() * AEM / sqrt(2.0) / SWS / OriginWMass / OriginWMass;
 double GAMW = GFERMI * pow(OriginWMass, 3) / 6.0 / TMath::Pi() / sqrt(2.0) * 9.0;
 double OriginGammaW = GAMW * (1.0 + 2.0 * EW->alphas(OriginWMass) / TMath::Pi() / 3.0);

 SWS = 1 - (NewWMass * NewWMass) / (91.1876 * 91.1876);
 AEM = sqrt(2.0) * NewWMass * NewWMass * GMU * SWS / TMath::Pi();
 GFERMI = TMath::Pi() * AEM / sqrt(2.0) / SWS / NewWMass / NewWMass;
 GAMW = GFERMI * pow(NewWMass, 3) / 6.0 / TMath::Pi() / sqrt(2.0) * 9.0;
 double NewGammaW = GAMW * (1.0 + 2.0 * EW->alphas(NewWMass) / TMath::Pi() / 3.0);

 double Value = 1.0;

 if(WWidth < 0){
// GAMW_NLO_R
   double Numer = (Q * Q - OriginWMass * OriginWMass) * (Q * Q - OriginWMass * OriginWMass) + (Q * Q * Q * Q) / (OriginWMass * OriginWMass * OriginGammaW * OriginGammaW);
   double Denom = (Q * Q - NewWMass * NewWMass) * (Q * Q - NewWMass * NewWMass) + (Q * Q * Q * Q) / (NewWMass * NewWMass * NewGammaW * NewGammaW);

   Value = Numer / Denom;
 }
 else{
//Fixed GammaW
   double GammaW = WWidth;

   double Numer = (Q * Q - OriginWMass * OriginWMass) * (Q * Q - OriginWMass * OriginWMass) + (Q * Q * Q * Q) / (OriginWMass * OriginWMass * GammaW * GammaW);
   double Denom = (Q * Q - NewWMass * NewWMass) * (Q * Q - NewWMass * NewWMass) + (Q * Q * Q * Q) / (NewWMass * NewWMass * GammaW * GammaW);
//   double Denom = (Q * Q - NewWMass * NewWMass) * (Q * Q - NewWMass * NewWMass) + (Q * Q * Q * Q) / (NewWMass * NewWMass * 2.084 * 2.084);

   Value = Numer / Denom;
 }

 return Value;
}

double loopResBosWTev::GetWPtReweightingFactor(double QT, double a)
{
 if(fabs(a) > 1.0){
   cout<<"ERROR! parameter should NOT be larger than 1.0"<<endl;
   return 1.0;
 }

 int ibin = myhists->RatioWZ_ScaleEnvelope->FindBin(QT);

 return a * (myhists->RatioWZ_ScaleEnvelope->GetBinContent(ibin) - 1.0) + 1.0;
}

void loopResBosWTev::End(int RootNumber)
{
 cout<<"Thread No."<<this->iThread<<": **Running: Free Rootfile: "<<RootNumber + 1<<endl;

 if(!ResBosTree->fChain[RootNumber])
  {
   cout<<"XXXXX**Runing: BIG ERROR!!! No File loadead!"<<endl;
   return;
  }
 delete ResBosTree->fChain[RootNumber]->GetCurrentFile();
}

void loopResBosWTev::Finish()
{
 cout<<"Thread No."<<this->iThread<<": **Total Event Number: "<<this->Sta_TotalNumber<<endl;

 if(EndFile == RootNames.size()) delete ResBosTree;

}

loopResBosWTev::~loopResBosWTev()
{
}
