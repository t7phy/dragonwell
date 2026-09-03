#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> Operator(309);

 Operator[0]="lambda"; 

 Operator[1]="ceuRe1111";
 Operator[2]="cedRe1111";
 Operator[3]="cluRe1111";
 Operator[4]="cldRe1111";
 Operator[5]="clq1Re1111";
 Operator[6]="clq3Re1111";
 Operator[7]="cqeRe1111";
 Operator[8]="cllRe1111";

 int iOperator = stoi(argv[1]);

 bool isRelative = stoi(argv[2]);

 vector<double> Lambda = {1000, 2000, 3000, 4000, 5000};

 vector<TString> Coefficient = {"0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1.0"};
 vector<TString> LambdaLabel = {"3.16", "2.24", "1.83", "1.58", "1.41", "1.29", "1.20", "1.12", "1.05", "1.0"};

 TString FileName;
 if(!isRelative) FileName = "Parameterize.root";
 if(isRelative) FileName = "RelativeParameterize.root";

 TFile* writefile = new TFile(FileName, "RECREATE");

 vector<vector<double>> CrossSections;
 vector<vector<double>> OriginCrossSections;
 CrossSections.resize(Coefficient.size());
 OriginCrossSections.resize(Coefficient.size());

 vector<vector<double>> CrossSectionsF;
 vector<vector<double>> OriginCrossSectionsF;
 CrossSectionsF.resize(Coefficient.size());
 OriginCrossSectionsF.resize(Coefficient.size());

 vector<vector<double>> CrossSectionsB;
 vector<vector<double>> OriginCrossSectionsB;
 CrossSectionsB.resize(Coefficient.size());
 OriginCrossSectionsB.resize(Coefficient.size());

 vector<vector<double>> CrossSectionsAFB;
 vector<vector<double>> OriginCrossSectionsAFB;
 CrossSectionsAFB.resize(Coefficient.size());
 OriginCrossSectionsAFB.resize(Coefficient.size());

 TFile* file_SM = new TFile((TString)"MC_results_SMEFT_" + Operator[iOperator] + (TString)"_c_0.0.root");
 TH1D* h_SM = (TH1D *)file_SM->Get("CrossSection_Pseudodata");
 TH1D* h_SM_F = (TH1D *)file_SM->Get("CrossSectionF_Pseudodata");
 TH1D* h_SM_B = (TH1D *)file_SM->Get("CrossSectionB_Pseudodata");
 TH1D* h_SM_AFB = (TH1D *)file_SM->Get("CrossSectionAFB");

 vector<TH1D *> OriginHists(h_SM->GetNbinsX());
 vector<TH1D *> Hists(h_SM->GetNbinsX());
 vector<TF1 *> Funcs(h_SM->GetNbinsX());
 vector<TString> Names(h_SM->GetNbinsX());

 vector<TH1D *> HistsF(h_SM_F->GetNbinsX());
 vector<TF1 *> FuncsF(h_SM_F->GetNbinsX());
 vector<TString> NamesF(h_SM_F->GetNbinsX());

 vector<TH1D *> HistsB(h_SM_B->GetNbinsX());
 vector<TF1 *> FuncsB(h_SM_B->GetNbinsX());
 vector<TString> NamesB(h_SM_B->GetNbinsX());

 vector<TH1D *> HistsAFB(h_SM_AFB->GetNbinsX());
 vector<TF1 *> FuncsAFB(h_SM_AFB->GetNbinsX());
 vector<TString> NamesAFB(h_SM_AFB->GetNbinsX());

 for(int i = iOperator; i <= iOperator; i++){

   Names.at(0) = "CrossSection_1000_1300_" + Operator[i];
   Names.at(1) = "CrossSection_1300_1800_" + Operator[i];
   Names.at(2) = "CrossSection_1800_2500_" + Operator[i];
   Names.at(3) = "CrossSection_2500_3200_" + Operator[i];
   Names.at(4) = "CrossSection_3200_4000_" + Operator[i];
   Names.at(5) = "CrossSection_4000_5000_" + Operator[i];
   NamesF.at(0) = "CrossSectionF_1000_1300_" + Operator[i];
   NamesF.at(1) = "CrossSectionF_1300_1800_" + Operator[i];
   NamesF.at(2) = "CrossSectionF_1800_2500_" + Operator[i];
   NamesF.at(3) = "CrossSectionF_2500_3200_" + Operator[i];
   NamesF.at(4) = "CrossSectionF_3200_4000_" + Operator[i];
   NamesF.at(5) = "CrossSectionF_4000_5000_" + Operator[i];
   NamesB.at(0) = "CrossSectionB_1000_1300_" + Operator[i];
   NamesB.at(1) = "CrossSectionB_1300_1800_" + Operator[i];
   NamesB.at(2) = "CrossSectionB_1800_2500_" + Operator[i];
   NamesB.at(3) = "CrossSectionB_2500_3200_" + Operator[i];
   NamesB.at(4) = "CrossSectionB_3200_4000_" + Operator[i];
   NamesB.at(5) = "CrossSectionB_4000_5000_" + Operator[i];
   NamesAFB.at(0) = "CrossSectionAFB_1000_1300_" + Operator[i];
   NamesAFB.at(1) = "CrossSectionAFB_1300_1800_" + Operator[i];
   NamesAFB.at(2) = "CrossSectionAFB_1800_2500_" + Operator[i];
   NamesAFB.at(3) = "CrossSectionAFB_2500_3200_" + Operator[i];
   NamesAFB.at(4) = "CrossSectionAFB_3200_4000_" + Operator[i];
   NamesAFB.at(5) = "CrossSectionAFB_4000_5000_" + Operator[i];

   for(int j = 0; j < Coefficient.size(); j++){

     TFile* file = new TFile("MC_results_SMEFT_" + Operator[i] + "_c_"+ Coefficient.at(j) +".root");
     TH1D* h1 = (TH1D *)file->Get("CrossSection_Pseudodata");
     TH1D* h1F = (TH1D *)file->Get("CrossSectionF_Pseudodata");
     TH1D* h1B = (TH1D *)file->Get("CrossSectionB_Pseudodata");
     TH1D* h1AFB = (TH1D *)file->Get("CrossSectionAFB");

     CrossSections.at(j).resize(h1->GetNbinsX());
     OriginCrossSections.at(j).resize(h1->GetNbinsX());

     CrossSectionsF.at(j).resize(h1F->GetNbinsX());
     OriginCrossSectionsF.at(j).resize(h1F->GetNbinsX());

     CrossSectionsB.at(j).resize(h1B->GetNbinsX());
     OriginCrossSectionsB.at(j).resize(h1B->GetNbinsX());

     CrossSectionsAFB.at(j).resize(h1AFB->GetNbinsX());
     OriginCrossSectionsAFB.at(j).resize(h1AFB->GetNbinsX());

     for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
       OriginCrossSections.at(j).at(ibin - 1) = h1->GetBinContent(ibin);
       if(!isRelative) CrossSections.at(j).at(ibin - 1) = h1->GetBinContent(ibin) - h_SM->GetBinContent(ibin);
       if(isRelative) CrossSections.at(j).at(ibin - 1) = (h1->GetBinContent(ibin) - h_SM->GetBinContent(ibin)) / h_SM->GetBinContent(ibin);
     }

     for(int ibin = 1; ibin <= h1F->GetNbinsX(); ibin++){
       OriginCrossSectionsF.at(j).at(ibin - 1) = h1F->GetBinContent(ibin);
       if(!isRelative) CrossSectionsF.at(j).at(ibin - 1) = h1F->GetBinContent(ibin) - h_SM_F->GetBinContent(ibin);
       if(isRelative) CrossSectionsF.at(j).at(ibin - 1) = (h1F->GetBinContent(ibin) - h_SM_F->GetBinContent(ibin)) / h_SM_F->GetBinContent(ibin);
     }

     for(int ibin = 1; ibin <= h1B->GetNbinsX(); ibin++){
       OriginCrossSectionsB.at(j).at(ibin - 1) = h1B->GetBinContent(ibin);
       if(!isRelative) CrossSectionsB.at(j).at(ibin - 1) = h1B->GetBinContent(ibin) - h_SM_B->GetBinContent(ibin);
       if(isRelative) CrossSectionsB.at(j).at(ibin - 1) = (h1B->GetBinContent(ibin) - h_SM_B->GetBinContent(ibin)) / h_SM_B->GetBinContent(ibin);
     }

     for(int ibin = 1; ibin <= h1AFB->GetNbinsX(); ibin++){
       OriginCrossSectionsAFB.at(j).at(ibin - 1) = h1AFB->GetBinContent(ibin);
       if(!isRelative) CrossSectionsAFB.at(j).at(ibin - 1) = h1AFB->GetBinContent(ibin);
       if(isRelative) CrossSectionsAFB.at(j).at(ibin - 1) = (h1AFB->GetBinContent(ibin));
     }

     file->Close();
     delete file;
   }

   int NBins = 10;
   double BinLeft = 0.1 - 0.1 / 2.0;
   double BinRight = 1.0 + 0.1 / 2.0;

   writefile->cd();

   ParameterizeFunc(CrossSections, Hists, Funcs, Names, BinLeft, BinRight);
   ParameterizeFunc(CrossSectionsF, HistsF, FuncsF, NamesF, BinLeft, BinRight);
   ParameterizeFunc(CrossSectionsB, HistsB, FuncsB, NamesB, BinLeft, BinRight);
   ParameterizeAFBFunc(CrossSectionsAFB, HistsAFB, h_SM_F, h_SM_B, FuncsF, FuncsB, FuncsAFB, NamesAFB, BinLeft, BinRight);

   for(int ibin = 1; ibin <= h_SM->GetNbinsX(); ibin++){
     Hists.at(ibin - 1)->Write();
     Funcs.at(ibin - 1)->Write();
     HistsF.at(ibin - 1)->Write();
     FuncsF.at(ibin - 1)->Write();
     HistsB.at(ibin - 1)->Write();
     FuncsB.at(ibin - 1)->Write();
     HistsAFB.at(ibin - 1)->Write();
     FuncsAFB.at(ibin - 1)->Write();
   }
 }

 writefile->Close();

 return 1;
}
