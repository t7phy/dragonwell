#include "RootCommon.h"
#include "Tools/Tools.h"

void ParameterizeFunc(vector<vector<double>> &hists, vector<TH1D *> &outhists, vector<TF1 *> &funcs, vector<TString> names, double BinLeft, double BinRight)
{
 vector<TString> LambdaLabel = {"3.16", "2.24", "1.83", "1.58", "1.41", "1.29", "1.20", "1.12", "1.05", "1.0"};

 for(int i = 0; i < outhists.size(); i++){
   outhists.at(i) = new TH1D(names.at(i), names.at(i), hists.size(), BinLeft, BinRight);
 }

 for(int ibin = 0; ibin < outhists.size(); ibin++){
   for(int ic = 0; ic < hists.size(); ic++){
     outhists.at(ibin)->SetBinContent(ic + 1, hists.at(ic).at(ibin));
     outhists.at(ibin)->SetBinError(ic + 1, 0.0);
     outhists.at(ibin)->GetXaxis()->SetBinLabel(ic + 1, LambdaLabel.at(ic));
   }
 }


 for(int ibin = 0; ibin < outhists.size(); ibin++){
   double ScaleFactor = 1e3;

   double* Par;
   double* ParErr;
   FunctionFitting(outhists.at(ibin), funcs.at(ibin), "[0]*x*x+[1]*x+[2]", Par, ParErr, 3, ScaleFactor);
   cout<<names.at(ibin)<<": Par1: "<<Par[0]<<" +- "<<ParErr[0]<<" Par2: "<<Par[1]<<" +- "<<ParErr[1]<<" Par3: "<<Par[2]<<" +- "<<ParErr[2]<<endl;
   funcs.at(ibin)->SetRange(-0.1, 1.1);
   for(int ic = 0; ic < hists.size(); ic++){
     funcs.at(ibin)->GetXaxis()->SetBinLabel(ic + 1, LambdaLabel.at(ic));
   }
   funcs.at(ibin)->SetParameter(2, 0.0);
 }

}

void ParameterizeAFBFunc(vector<vector<double>> &hists, vector<TH1D *> &outhists, TH1D* SM_F, TH1D* SM_B, vector<TF1 *> &funcsF, vector<TF1 *> &funcsB, vector<TF1 *> &funcs, vector<TString> names, double BinLeft, double BinRight)
{
 vector<TString> LambdaLabel = {"3.16", "2.24", "1.83", "1.58", "1.41", "1.29", "1.20", "1.12", "1.05", "1.0"};

 for(int i = 0; i < outhists.size(); i++){
   outhists.at(i) = new TH1D(names.at(i), names.at(i), hists.size(), BinLeft, BinRight);
 }

 for(int ibin = 0; ibin < outhists.size(); ibin++){
   for(int ic = 0; ic < hists.size(); ic++){
     outhists.at(ibin)->SetBinContent(ic + 1, hists.at(ic).at(ibin));
     outhists.at(ibin)->SetBinError(ic + 1, 0.0);
     outhists.at(ibin)->GetXaxis()->SetBinLabel(ic + 1, LambdaLabel.at(ic));
   }
 }


 for(int ibin = 0; ibin < outhists.size(); ibin++){
   funcs.at(ibin) = new TF1(names.at(ibin) + "_Fitting", "([0]*x*x+[1]*x+[2])/([3]*x*x+[4]*x+[5])", outhists.at(ibin)->GetBinCenter(1), outhists.at(ibin)->GetBinCenter(outhists.at(ibin)->GetNbinsX()));
   funcs.at(ibin)->SetParameter(0, funcsF.at(ibin)->GetParameter(0) - funcsB.at(ibin)->GetParameter(0));
   funcs.at(ibin)->SetParameter(1, funcsF.at(ibin)->GetParameter(1) - funcsB.at(ibin)->GetParameter(1));
   funcs.at(ibin)->SetParameter(2, SM_F->GetBinContent(ibin + 1) + funcsF.at(ibin)->GetParameter(2) - SM_B->GetBinContent(ibin + 1) - funcsB.at(ibin)->GetParameter(2));
   funcs.at(ibin)->SetParameter(3, funcsF.at(ibin)->GetParameter(0) + funcsB.at(ibin)->GetParameter(0));
   funcs.at(ibin)->SetParameter(4, funcsF.at(ibin)->GetParameter(1) + funcsB.at(ibin)->GetParameter(1));
   funcs.at(ibin)->SetParameter(5, SM_F->GetBinContent(ibin + 1) + funcsF.at(ibin)->GetParameter(2) + SM_B->GetBinContent(ibin + 1) + funcsB.at(ibin)->GetParameter(2));

   funcs.at(ibin)->SetRange(0.0, 1.1);
   for(int ic = 0; ic < hists.size(); ic++){
     funcs.at(ibin)->GetXaxis()->SetBinLabel(ic + 1, LambdaLabel.at(ic));
   }
 }

}

