#include <iomanip>
#include <set>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1F.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <TH2.h>
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TDecompSVD.h"

void prepareDataTable()
{
 auto Decomposition = [&](TH1D* Data_nominal, TH2D* Covariance){
   vector<double> DATA(Data_nominal->GetNbinsX());
   for(int i = 0; i < DATA.size(); i++){
     DATA.at(i) = Data_nominal->GetBinContent(i + 1);
   }

   TMatrixD input(Covariance->GetNbinsX(), Covariance->GetNbinsY());
   for(int ibinx = 1; ibinx <= Covariance->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= Covariance->GetNbinsY(); ibiny++){
       input[ibinx - 1][ibiny - 1] = Covariance->GetBinContent(ibinx, ibiny);
     }
   }

   bool isTest = false;

   int MatrixRank = input.GetNcols();

   TDecompSVD DecompM(input);
   TMatrixD U = DecompM.GetU();
   TVectorD S = DecompM.GetSig();
   TMatrixD V = DecompM.GetV();

   TMatrixD FinalBeta(MatrixRank, MatrixRank);
   TMatrixD CovarianceBeta(MatrixRank, MatrixRank);

   TMatrixD SigmSqrt(MatrixRank, MatrixRank);
   for(int i = 0;  i < MatrixRank; i++){
     SigmSqrt[i][i] = sqrt(S[i]);
   }
   TMatrixD BT = U * SigmSqrt;

   vector<vector<double>> CorrErrs(MatrixRank);

   for(int j = 0; j < MatrixRank; j++){
     CorrErrs.at(j).resize(MatrixRank);
     for(int i = 0;  i < MatrixRank; i++){
        FinalBeta[j][i] = BT[j][i];
        CorrErrs.at(j).at(i) = BT[j][i] / DATA[j] * 100.0;
     }
   }

   if(isTest){

     cout<<"Real Beta:"<<endl;
     for(int j = 0; j < MatrixRank; j++){
       for(int i = 0;  i < MatrixRank; i++){
          cout << BT[j][i] << "  ";
       }
       std::cout << std::endl;
     }

     TMatrixD BT_T = BT;
     BT_T = BT_T.Transpose(BT_T);

     TMatrixD Final = BT * BT_T;

     for(int i = 0; i < MatrixRank; i++){
       for(int j = 0; j < MatrixRank; j++){
         for(int k = 0; k < MatrixRank; k++){
           CovarianceBeta[i][j] += FinalBeta[i][k] * FinalBeta[j][k];
         }
       }
     }

     cout<<"Beta Covariance:"<<endl;
     for(int i = 0; i < MatrixRank; i++){
       for(int j = 0; j < MatrixRank; j++){
         cout<<CovarianceBeta[i][j]<<"  ";
       }
       cout<<endl;
     }

     cout<<"input Covariance:"<<endl;
     for(int i = 0; i < MatrixRank; i++){
       for(int j = 0; j < MatrixRank; j++){
         cout<<input[i][j]<<"  ";
       }
       cout<<endl;
     }
   }

   return CorrErrs;
 };

 TString InputFileName_Mass = "HMDY/DY_Mass_ee_born_New.root";
 TString InputFileName_MassRapidity = "HMDY/DY_Mass_Rapidity_ee_born_New.root";
 TString InputFileName_MassCosTheta = "HMDY/DY_mass_costheta_ee_born_New.root";

 TString DirectoryName = "Final/";

 TString HistName = DirectoryName + "Final_Nominal_Unfolded_Normalized";
 TString HistName_StatUnc = DirectoryName + "Final_Statistical_Uncertainty";
 TString HistName_BackgroundCovariance = DirectoryName + "Final_BackgroundCovariance";
 TString HistName_StatCovariance = DirectoryName + "Final_StatCovarianceMatrix";
 TString HistName_SystBkgCovariance = DirectoryName + "Final_SystBkgCovarianceMatrix";
 TString HistName_SystematicCovariance = DirectoryName + "Final_SystematicCovariance";

 TFile* InputFile_Mass = new TFile(InputFileName_Mass);
 TFile* InputFile_MassRapidity = new TFile(InputFileName_MassRapidity);
 TFile* InputFile_MassCosTheta = new TFile(InputFileName_MassCosTheta);

 TH1D* Mass_Nominal = (TH1D *)InputFile_Mass->Get(HistName);
 TH1D* Mass_StatUnc = (TH1D *)InputFile_Mass->Get(HistName_StatUnc);
 TH2D* Mass_BackgroundCovariance = (TH2D *)InputFile_Mass->Get(HistName_BackgroundCovariance);
 TH2D* Mass_StatCovariance = (TH2D *)InputFile_Mass->Get(HistName_StatCovariance);
 TH2D* Mass_SystBkgCovariance = (TH2D *)InputFile_Mass->Get(HistName_SystBkgCovariance);
 TH2D* Mass_SystematicCovariance = (TH2D *)InputFile_Mass->Get(HistName_SystematicCovariance);

 TH1D* MassRapidity_Nominal = (TH1D *)InputFile_MassRapidity->Get(HistName);
 TH1D* MassRapidity_StatUnc = (TH1D *)InputFile_MassRapidity->Get(HistName_StatUnc);
 TH2D* MassRapidity_BackgroundCovariance = (TH2D *)InputFile_MassRapidity->Get(HistName_BackgroundCovariance);
 TH2D* MassRapidity_StatCovariance = (TH2D *)InputFile_MassRapidity->Get(HistName_StatCovariance);
 TH2D* MassRapidity_SystBkgCovariance = (TH2D *)InputFile_MassRapidity->Get(HistName_SystBkgCovariance);
 TH2D* MassRapidity_SystematicCovariance = (TH2D *)InputFile_MassRapidity->Get(HistName_SystematicCovariance);

 TH1D* MassCosTheta_Nominal = (TH1D *)InputFile_MassCosTheta->Get(HistName);
 TH1D* MassCosTheta_StatUnc = (TH1D *)InputFile_MassCosTheta->Get(HistName_StatUnc);
 TH2D* MassCosTheta_BackgroundCovariance = (TH2D *)InputFile_MassCosTheta->Get(HistName_BackgroundCovariance);
 TH2D* MassCosTheta_StatCovariance = (TH2D *)InputFile_MassCosTheta->Get(HistName_StatCovariance);
 TH2D* MassCosTheta_SystBkgCovariance = (TH2D *)InputFile_MassCosTheta->Get(HistName_SystBkgCovariance);
 TH2D* MassCosTheta_SystematicCovariance = (TH2D *)InputFile_MassCosTheta->Get(HistName_SystematicCovariance);

 vector<double> Mass_BinWidth(Mass_Nominal->GetNbinsX());
 for(int ibin = 1; ibin <= Mass_Nominal->GetNbinsX(); ibin++){
   Mass_BinWidth.at(ibin - 1) = Mass_Nominal->GetXaxis()->GetBinUpEdge(ibin) - Mass_Nominal->GetXaxis()->GetBinLowEdge(ibin);
 }

 vector<double> MassRapidity_BinWidth;
 for(int i = 1; i <= 48; i++) MassRapidity_BinWidth.push_back(0.2);
 for(int i = 1; i <= 8; i++) MassRapidity_BinWidth.push_back(0.3);
 MassRapidity_BinWidth.push_back(Mass_BinWidth.at(Mass_BinWidth.size() - 1));

 vector<double> MassCosTheta_BinWidth;
 for(int i = 1; i <= 40; i++) MassCosTheta_BinWidth.push_back(0.2);
 for(int i = 1; i <= 8; i++) MassCosTheta_BinWidth.push_back(0.25);
 MassCosTheta_BinWidth.push_back(Mass_BinWidth.at(Mass_BinWidth.size() - 1));

 TFile* ResBos_w432 = new TFile("MC_results_w432.root");
 TFile* ResBos_nlo = new TFile("MC_results_NLO.root");

 TH1D* Mass_w432 = (TH1D *)ResBos_w432->Get("ATLAS_Mll_HighMass");
 TH1D* MassRapidity_w432 = (TH1D *)ResBos_w432->Get("ATLAS_Mll_HighMass_DilRapidity_NewBinning");
 TH1D* MassCosTheta_w432 = (TH1D *)ResBos_w432->Get("ATLAS_Mll_HighMass_costheta_NewBinning");

 TH1D* Mass_nlo = (TH1D *)ResBos_nlo->Get("ATLAS_Mll_HighMass");
 TH1D* MassRapidity_nlo = (TH1D *)ResBos_nlo->Get("ATLAS_Mll_HighMass_DilRapidity_NewBinning");
 TH1D* MassCosTheta_nlo = (TH1D *)ResBos_nlo->Get("ATLAS_Mll_HighMass_costheta_NewBinning");

 TH1D* Mass_kfactor = (TH1D *)Mass_w432->Clone("Mass_kfactor");
 Mass_kfactor->Divide(Mass_nlo);
 TH1D* MassRapidity_kfactor = (TH1D *)MassRapidity_w432->Clone("MassRapidity_kfactor");
 MassRapidity_kfactor->Divide(MassRapidity_nlo);
 TH1D* MassCosTheta_kfactor = (TH1D *)MassCosTheta_w432->Clone("MassCosTheta_kfactor");
 MassCosTheta_kfactor->Divide(MassCosTheta_nlo);

 auto PrepareDataTable = [&](TString name, TH1D* Nominal, TH1D* StatUnc, TH2D* BackgroundCovariance, TH2D* StatCovariance, TH2D* SystBkgCovariance, TH2D* SystematicCovariance, vector<double> BinWidth, TH1D* kfactor){

   vector<vector<double>> Background_CorrErr = Decomposition(Nominal, BackgroundCovariance);
   vector<vector<double>> Stat_CorrErr = Decomposition(Nominal, StatCovariance);
   vector<vector<double>> SystBkg_CorrErr = Decomposition(Nominal, SystBkgCovariance);
   vector<vector<double>> Systematic_CorrErr = Decomposition(Nominal, SystematicCovariance);

   ofstream datafile(name.Data());
   datafile << "* ATLAS preliminary" << endl;
   datafile << "* yfu produces" << endl;
   datafile << "* description" << endl;
   datafile << "2 Norm #CorrErro  Ecm  |# grids|# KF|# col|(which grid has one BW)" << endl;
   datafile << "0.0      ";
   datafile << Background_CorrErr.size()
             + Stat_CorrErr.size()
             + SystBkg_CorrErr.size()
             + Systematic_CorrErr.size();
   datafile << "        13000   888111" << endl;
   datafile << "bin      bin_low   bin_high       xsec          stat           Totsys  uncorsys  cor_sys%" << endl;
   for(int ibin = 1; ibin <= Nominal->GetNbinsX(); ibin++){
     datafile << setw(12) << fixed << setprecision(4) << Nominal->GetBinCenter(ibin);
     datafile << setw(12) << fixed << setprecision(4) << Nominal->GetXaxis()->GetBinLowEdge(ibin);
     datafile << setw(12) << fixed << setprecision(4) << Nominal->GetXaxis()->GetBinUpEdge(ibin);
     datafile << setw(12) << scientific << setprecision(4) << Nominal->GetBinContent(ibin) / 140000.0 / BinWidth.at(ibin - 1);
     datafile << setw(12) << scientific << setprecision(4) << StatUnc->GetBinContent(ibin) / 140000.0 / BinWidth.at(ibin - 1);
     datafile << setw(12) << fixed << setprecision(4) << 0.0;
     datafile << setw(12) << fixed << setprecision(4) << 0.0;
     for(int icorr = 0; icorr < Background_CorrErr.at(ibin - 1).size(); icorr++){
       datafile << setw(12) << scientific << setprecision(4) << Background_CorrErr.at(ibin - 1).at(icorr);
     }
     for(int icorr = 0; icorr < Stat_CorrErr.at(ibin - 1).size(); icorr++){
       datafile << setw(12) << scientific << setprecision(4) << Stat_CorrErr.at(ibin - 1).at(icorr);
     }
     for(int icorr = 0; icorr < SystBkg_CorrErr.at(ibin - 1).size(); icorr++){
       datafile << setw(12) << scientific << setprecision(4) << SystBkg_CorrErr.at(ibin - 1).at(icorr);
     }
     for(int icorr = 0; icorr < Systematic_CorrErr.at(ibin - 1).size(); icorr++){
       datafile << setw(12) << scientific << setprecision(4) << Systematic_CorrErr.at(ibin - 1).at(icorr);
     }
     datafile << setw(12) << fixed << setprecision(4) << 1.0;
     datafile << setw(12) << fixed << setprecision(4) << kfactor->GetBinContent(ibin);
     datafile << endl;
   }
 };

 PrepareDataTable("ATL13HMDY_Mass", Mass_Nominal,
                                    Mass_StatUnc,
                                    Mass_BackgroundCovariance,
                                    Mass_StatCovariance,
                                    Mass_SystBkgCovariance,
                                    Mass_SystematicCovariance,
                                    Mass_BinWidth,
                                    Mass_kfactor);

 PrepareDataTable("ATL13HMDY_MassRapidity", MassRapidity_Nominal,
                                            MassRapidity_StatUnc,
                                            MassRapidity_BackgroundCovariance,
                                            MassRapidity_StatCovariance,
                                            MassRapidity_SystBkgCovariance,
                                            MassRapidity_SystematicCovariance,
                                            MassRapidity_BinWidth,
                                            MassRapidity_kfactor);

 PrepareDataTable("ATL13HMDY_MassCosTheta", MassCosTheta_Nominal,
                                            MassCosTheta_StatUnc,
                                            MassCosTheta_BackgroundCovariance,
                                            MassCosTheta_StatCovariance,
                                            MassCosTheta_SystBkgCovariance,
                                            MassCosTheta_SystematicCovariance,
                                            MassCosTheta_BinWidth,
                                            MassCosTheta_kfactor);

}
