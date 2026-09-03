#include "RootCommon.h"
#include "Tools/Tools.h"
#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

double MinChi2 = 100000.0;

TH1D* global_CosThetaV_WLZL_LL;
TH1D* global_CosThetaV_WLZL_LT;
TH1D* global_CosThetaV_WLZL_TL;
TH1D* global_CosThetaV_WLZL_TT;

TH1D* global_CosThetaV_WLZH_LL;
TH1D* global_CosThetaV_WLZH_LT;
TH1D* global_CosThetaV_WLZH_TL;
TH1D* global_CosThetaV_WLZH_TT;

TH1D* global_CosThetaV_WHZL_LL;
TH1D* global_CosThetaV_WHZL_LT;
TH1D* global_CosThetaV_WHZL_TL;
TH1D* global_CosThetaV_WHZL_TT;

TH1D* global_CosThetaV_WHZH_LL;
TH1D* global_CosThetaV_WHZH_LT;
TH1D* global_CosThetaV_WHZH_TL;
TH1D* global_CosThetaV_WHZH_TT;

TH1D* global_CosThetaV_WLZL_Data;
TH1D* global_CosThetaV_WLZH_Data;
TH1D* global_CosThetaV_WHZL_Data;
TH1D* global_CosThetaV_WHZH_Data;

TH1D* global_BDTScore_Data;
TH1D* global_BDTScore_LL;
TH1D* global_BDTScore_LT;
TH1D* global_BDTScore_TL;
TH1D* global_BDTScore_TT;
TH1D* global_BDTScore_BkgZZ;
TH1D* global_BDTScore_BkgWZEW;
TH1D* global_BDTScore_BkgVVV;
TH1D* global_BDTScore_BkgttbarV;
TH1D* global_BDTScore_Fake;

TH1D* global_BDTScore_WLZL_Data;
TH1D* global_BDTScore_WLZL_LL;
TH1D* global_BDTScore_WLZL_LT;
TH1D* global_BDTScore_WLZL_TL;
TH1D* global_BDTScore_WLZL_TT;
TH1D* global_BDTScore_WLZL_BkgZZ;
TH1D* global_BDTScore_WLZL_BkgWZEW;
TH1D* global_BDTScore_WLZL_BkgVVV;
TH1D* global_BDTScore_WLZL_BkgttbarV;
TH1D* global_BDTScore_WLZL_Fake;

TH1D* global_BDTScore_WLZH_Data;
TH1D* global_BDTScore_WLZH_LL;
TH1D* global_BDTScore_WLZH_LT;
TH1D* global_BDTScore_WLZH_TL;
TH1D* global_BDTScore_WLZH_TT;
TH1D* global_BDTScore_WLZH_BkgZZ;
TH1D* global_BDTScore_WLZH_BkgWZEW;
TH1D* global_BDTScore_WLZH_BkgVVV;
TH1D* global_BDTScore_WLZH_BkgttbarV;
TH1D* global_BDTScore_WLZH_Fake;

TH1D* global_BDTScore_WHZL_Data;
TH1D* global_BDTScore_WHZL_LL;
TH1D* global_BDTScore_WHZL_LT;
TH1D* global_BDTScore_WHZL_TL;
TH1D* global_BDTScore_WHZL_TT;
TH1D* global_BDTScore_WHZL_BkgZZ;
TH1D* global_BDTScore_WHZL_BkgWZEW;
TH1D* global_BDTScore_WHZL_BkgVVV;
TH1D* global_BDTScore_WHZL_BkgttbarV;
TH1D* global_BDTScore_WHZL_Fake;

TH1D* global_BDTScore_WHZH_Data;
TH1D* global_BDTScore_WHZH_LL;
TH1D* global_BDTScore_WHZH_LT;
TH1D* global_BDTScore_WHZH_TL;
TH1D* global_BDTScore_WHZH_TT;
TH1D* global_BDTScore_WHZH_BkgZZ;
TH1D* global_BDTScore_WHZH_BkgWZEW;
TH1D* global_BDTScore_WHZH_BkgVVV;
TH1D* global_BDTScore_WHZH_BkgttbarV;
TH1D* global_BDTScore_WHZH_Fake;

vector<double> global_DataFactorial;

vector<double> global_DataFactorial_WLZL;
vector<double> global_DataFactorial_WLZH;
vector<double> global_DataFactorial_WHZL;
vector<double> global_DataFactorial_WHZH;

int global_NParameters;

void WZPolFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 TH1D* CosThetaV_WLZL_LL = (TH1D *)global_CosThetaV_WLZL_LL->Clone("CosThetaV_WLZL_LL");
 TH1D* CosThetaV_WLZL_LT = (TH1D *)global_CosThetaV_WLZL_LT->Clone("CosThetaV_WLZL_LT");
 TH1D* CosThetaV_WLZL_TL = (TH1D *)global_CosThetaV_WLZL_TL->Clone("CosThetaV_WLZL_TL");
 TH1D* CosThetaV_WLZL_TT = (TH1D *)global_CosThetaV_WLZL_TT->Clone("CosThetaV_WLZL_TT");

 TH1D* CosThetaV_WLZH_LL = (TH1D *)global_CosThetaV_WLZH_LL->Clone("CosThetaV_WLZH_LT");
 TH1D* CosThetaV_WLZH_LT = (TH1D *)global_CosThetaV_WLZH_LT->Clone("CosThetaV_WLZH_LT");
 TH1D* CosThetaV_WLZH_TL = (TH1D *)global_CosThetaV_WLZH_TL->Clone("CosThetaV_WLZH_TL");
 TH1D* CosThetaV_WLZH_TT = (TH1D *)global_CosThetaV_WLZH_TT->Clone("CosThetaV_WLZH_TT");

 TH1D* CosThetaV_WHZL_LL = (TH1D *)global_CosThetaV_WHZL_LL->Clone("CosThetaV_WHZL_LL");
 TH1D* CosThetaV_WHZL_LT = (TH1D *)global_CosThetaV_WHZL_LT->Clone("CosThetaV_WHZL_LT");
 TH1D* CosThetaV_WHZL_TL = (TH1D *)global_CosThetaV_WHZL_TL->Clone("CosThetaV_WHZL_TL");
 TH1D* CosThetaV_WHZL_TT = (TH1D *)global_CosThetaV_WHZL_TT->Clone("CosThetaV_WHZL_TT");

 TH1D* CosThetaV_WHZH_LL = (TH1D *)global_CosThetaV_WHZH_LL->Clone("CosThetaV_WHZH_LL");
 TH1D* CosThetaV_WHZH_LT = (TH1D *)global_CosThetaV_WHZH_LT->Clone("CosThetaV_WHZH_LT");
 TH1D* CosThetaV_WHZH_TL = (TH1D *)global_CosThetaV_WHZH_TL->Clone("CosThetaV_WHZH_TL");
 TH1D* CosThetaV_WHZH_TT = (TH1D *)global_CosThetaV_WHZH_TT->Clone("CosThetaV_WHZH_TT");

 TH1D* CosThetaV_WLZL_Data = (TH1D *)global_CosThetaV_WLZL_Data->Clone("CosThetaV_WLZL_Data");
 TH1D* CosThetaV_WLZH_Data = (TH1D *)global_CosThetaV_WLZH_Data->Clone("CosThetaV_WLZH_Data");
 TH1D* CosThetaV_WHZL_Data = (TH1D *)global_CosThetaV_WHZL_Data->Clone("CosThetaV_WHZL_Data");
 TH1D* CosThetaV_WHZH_Data = (TH1D *)global_CosThetaV_WHZH_Data->Clone("CosThetaV_WHZH_Data");

 TH1D* CosThetaV_LL = (TH1D *)CosThetaV_WLZL_LL->Clone("CosThetaV_LL");
 CosThetaV_LL->Add(CosThetaV_WLZH_LL);
 CosThetaV_LL->Add(CosThetaV_WHZL_LL);
 CosThetaV_LL->Add(CosThetaV_WHZH_LL);
 TH1D* CosThetaV_LT = (TH1D *)CosThetaV_WLZL_LT->Clone("CosThetaV_LT");
 CosThetaV_LT->Add(CosThetaV_WLZH_LT);
 CosThetaV_LT->Add(CosThetaV_WHZL_LT);
 CosThetaV_LT->Add(CosThetaV_WHZH_LT);
 TH1D* CosThetaV_TL = (TH1D *)CosThetaV_WLZL_TL->Clone("CosThetaV_TL");
 CosThetaV_TL->Add(CosThetaV_WLZH_TL);
 CosThetaV_TL->Add(CosThetaV_WHZL_TL);
 CosThetaV_TL->Add(CosThetaV_WHZH_TL);
 TH1D* CosThetaV_TT = (TH1D *)CosThetaV_WLZL_TT->Clone("CosThetaV_TT");
 CosThetaV_TT->Add(CosThetaV_WLZH_TT);
 CosThetaV_TT->Add(CosThetaV_WHZL_TT);
 CosThetaV_TT->Add(CosThetaV_WHZH_TT);
 TH1D* CosThetaV_Data = (TH1D *)CosThetaV_WLZL_Data->Clone("CosThetaV_Data");
 CosThetaV_Data->Add(CosThetaV_WLZH_Data);
 CosThetaV_Data->Add(CosThetaV_WHZL_Data);
 CosThetaV_Data->Add(CosThetaV_WHZH_Data);

 TH1D* CosThetaV_Total = (TH1D *)CosThetaV_LL->Clone("CosThetaV_Total");
 CosThetaV_Total->Add(CosThetaV_LT);
 CosThetaV_Total->Add(CosThetaV_TL);
 CosThetaV_Total->Add(CosThetaV_TT);

 double LLFraction = CosThetaV_LL->Integral() / CosThetaV_Data->Integral();
 double LTFraction = CosThetaV_LT->Integral() / CosThetaV_Data->Integral();
 double TLFraction = CosThetaV_TL->Integral() / CosThetaV_Data->Integral();
 double TTFraction = CosThetaV_TT->Integral() / CosThetaV_Data->Integral();

 CosThetaV_WLZL_LL->Scale(par[0] / LLFraction);
 CosThetaV_WLZL_LT->Scale(par[1] / LTFraction);
 CosThetaV_WLZL_TL->Scale(par[2] / TLFraction);
 CosThetaV_WLZL_TT->Scale(par[3] / TTFraction);

 CosThetaV_WLZH_LL->Scale(par[0] / LLFraction);
 CosThetaV_WLZH_LT->Scale(par[1] / LTFraction);
 CosThetaV_WLZH_TL->Scale(par[2] / TLFraction);
 CosThetaV_WLZH_TT->Scale(par[3] / TTFraction);

 CosThetaV_WHZL_LL->Scale(par[0] / LLFraction);
 CosThetaV_WHZL_LT->Scale(par[1] / LTFraction);
 CosThetaV_WHZL_TL->Scale(par[2] / TLFraction);
 CosThetaV_WHZL_TT->Scale(par[3] / TTFraction);

 CosThetaV_WHZH_LL->Scale(par[0] / LLFraction);
 CosThetaV_WHZH_LT->Scale(par[1] / LTFraction);
 CosThetaV_WHZH_TL->Scale(par[2] / TLFraction);
 CosThetaV_WHZH_TT->Scale(par[3] / TTFraction);

 TH1D* CosThetaV_WLZL = (TH1D *)CosThetaV_WLZL_LL->Clone("CosThetaV_WLZL");
 CosThetaV_WLZL->Add(CosThetaV_WLZL_LT);
 CosThetaV_WLZL->Add(CosThetaV_WLZL_TL);
 CosThetaV_WLZL->Add(CosThetaV_WLZL_TT);
 TH1D* CosThetaV_WLZH = (TH1D *)CosThetaV_WLZH_LL->Clone("CosThetaV_WLZH");
 CosThetaV_WLZH->Add(CosThetaV_WLZH_LT);
 CosThetaV_WLZH->Add(CosThetaV_WLZH_TL);
 CosThetaV_WLZH->Add(CosThetaV_WLZH_TT);
 TH1D* CosThetaV_WHZL = (TH1D *)CosThetaV_WHZL_LL->Clone("CosThetaV_WHZL");
 CosThetaV_WHZL->Add(CosThetaV_WHZL_LT);
 CosThetaV_WHZL->Add(CosThetaV_WHZL_TL);
 CosThetaV_WHZL->Add(CosThetaV_WHZL_TT);
 TH1D* CosThetaV_WHZH = (TH1D *)CosThetaV_WHZH_LL->Clone("CosThetaV_WHZH");
 CosThetaV_WHZH->Add(CosThetaV_WHZH_LT);
 CosThetaV_WHZH->Add(CosThetaV_WHZH_TL);
 CosThetaV_WHZH->Add(CosThetaV_WHZH_TT);

 double Chi2_WLZL = CalculateChi2(CosThetaV_WLZL, CosThetaV_WLZL_Data);
 double Chi2_WLZH = CalculateChi2(CosThetaV_WLZH, CosThetaV_WLZH_Data);
 double Chi2_WHZL = CalculateChi2(CosThetaV_WHZL, CosThetaV_WHZL_Data);
 double Chi2_WHZH = CalculateChi2(CosThetaV_WHZH, CosThetaV_WHZH_Data);

 f = Chi2_WLZL + Chi2_WLZH + Chi2_WHZL + Chi2_WHZH;
 if(f < MinChi2) MinChi2 = f;

 cout<<"Min Chi2 = "<<MinChi2<<endl;

}

void WZPolFittingLLH(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 int NParameters = global_NParameters;

 TH1D* BDTScore_Data = (TH1D *)global_BDTScore_Data->Clone("BDTScore_Data");
 TH1D* BDTScore_LL = (TH1D *)global_BDTScore_LL->Clone("BDTScore_LL");
 TH1D* BDTScore_LT = (TH1D *)global_BDTScore_LT->Clone("BDTScore_LT");
 TH1D* BDTScore_TL = (TH1D *)global_BDTScore_TL->Clone("BDTScore_TL");
 TH1D* BDTScore_TT = (TH1D *)global_BDTScore_TT->Clone("BDTScore_TT");
 TH1D* BDTScore_BkgZZ = (TH1D *)global_BDTScore_BkgZZ->Clone("BDTScore_BkgZZ");
 TH1D* BDTScore_BkgWZEW = (TH1D *)global_BDTScore_BkgWZEW->Clone("BDTScore_BkgWZEW");
 TH1D* BDTScore_BkgVVV = (TH1D *)global_BDTScore_BkgVVV->Clone("BDTScore_BkgVVV");
 TH1D* BDTScore_BkgttbarV = (TH1D *)global_BDTScore_BkgttbarV->Clone("BDTScore_BkgttbarV");
 TH1D* BDTScore_Fake = (TH1D *)global_BDTScore_Fake->Clone("BDTScore_Fake");

 TH1D* BDTScore_WLZL_Data = (TH1D *)global_BDTScore_WLZL_Data->Clone("BDTScore_WLZL_Data");
 TH1D* BDTScore_WLZL_LL = (TH1D *)global_BDTScore_WLZL_LL->Clone("BDTScore_WLZL_LL");
 TH1D* BDTScore_WLZL_LT = (TH1D *)global_BDTScore_WLZL_LT->Clone("BDTScore_WLZL_LT");
 TH1D* BDTScore_WLZL_TL = (TH1D *)global_BDTScore_WLZL_TL->Clone("BDTScore_WLZL_TL");
 TH1D* BDTScore_WLZL_TT = (TH1D *)global_BDTScore_WLZL_TT->Clone("BDTScore_WLZL_TT");
 TH1D* BDTScore_WLZL_BkgZZ = (TH1D *)global_BDTScore_WLZL_BkgZZ->Clone("BDTScore_WLZL_BkgZZ");
 TH1D* BDTScore_WLZL_BkgWZEW = (TH1D *)global_BDTScore_WLZL_BkgWZEW->Clone("BDTScore_WLZL_BkgWZEW");
 TH1D* BDTScore_WLZL_BkgVVV = (TH1D *)global_BDTScore_WLZL_BkgVVV->Clone("BDTScore_WLZL_BkgVVV");
 TH1D* BDTScore_WLZL_BkgttbarV = (TH1D *)global_BDTScore_WLZL_BkgttbarV->Clone("BDTScore_WLZL_BkgttbarV");
 TH1D* BDTScore_WLZL_Fake = (TH1D *)global_BDTScore_WLZL_Fake->Clone("BDTScore_WLZL_Fake");

 TH1D* BDTScore_WLZH_Data = (TH1D *)global_BDTScore_WLZH_Data->Clone("BDTScore_WLZH_Data");
 TH1D* BDTScore_WLZH_LL = (TH1D *)global_BDTScore_WLZH_LL->Clone("BDTScore_WLZH_LL");
 TH1D* BDTScore_WLZH_LT = (TH1D *)global_BDTScore_WLZH_LT->Clone("BDTScore_WLZH_LT");
 TH1D* BDTScore_WLZH_TL = (TH1D *)global_BDTScore_WLZH_TL->Clone("BDTScore_WLZH_TL");
 TH1D* BDTScore_WLZH_TT = (TH1D *)global_BDTScore_WLZH_TT->Clone("BDTScore_WLZH_TT");
 TH1D* BDTScore_WLZH_BkgZZ = (TH1D *)global_BDTScore_WLZH_BkgZZ->Clone("BDTScore_WLZH_BkgZZ");
 TH1D* BDTScore_WLZH_BkgWZEW = (TH1D *)global_BDTScore_WLZH_BkgWZEW->Clone("BDTScore_WLZH_BkgWZEW");
 TH1D* BDTScore_WLZH_BkgVVV = (TH1D *)global_BDTScore_WLZH_BkgVVV->Clone("BDTScore_WLZH_BkgVVV");
 TH1D* BDTScore_WLZH_BkgttbarV = (TH1D *)global_BDTScore_WLZH_BkgttbarV->Clone("BDTScore_WLZH_BkgttbarV");
 TH1D* BDTScore_WLZH_Fake = (TH1D *)global_BDTScore_WLZH_Fake->Clone("BDTScore_WLZH_Fake");

 TH1D* BDTScore_WHZL_Data = (TH1D *)global_BDTScore_WHZL_Data->Clone("BDTScore_WHZL_Data");
 TH1D* BDTScore_WHZL_LL = (TH1D *)global_BDTScore_WHZL_LL->Clone("BDTScore_WHZL_LL");
 TH1D* BDTScore_WHZL_LT = (TH1D *)global_BDTScore_WHZL_LT->Clone("BDTScore_WHZL_LT");
 TH1D* BDTScore_WHZL_TL = (TH1D *)global_BDTScore_WHZL_TL->Clone("BDTScore_WHZL_TL");
 TH1D* BDTScore_WHZL_TT = (TH1D *)global_BDTScore_WHZL_TT->Clone("BDTScore_WHZL_TT");
 TH1D* BDTScore_WHZL_BkgZZ = (TH1D *)global_BDTScore_WHZL_BkgZZ->Clone("BDTScore_WHZL_BkgZZ");
 TH1D* BDTScore_WHZL_BkgWZEW = (TH1D *)global_BDTScore_WHZL_BkgWZEW->Clone("BDTScore_WHZL_BkgWZEW");
 TH1D* BDTScore_WHZL_BkgVVV = (TH1D *)global_BDTScore_WHZL_BkgVVV->Clone("BDTScore_WHZL_BkgVVV");
 TH1D* BDTScore_WHZL_BkgttbarV = (TH1D *)global_BDTScore_WHZL_BkgttbarV->Clone("BDTScore_WHZL_BkgttbarV");
 TH1D* BDTScore_WHZL_Fake = (TH1D *)global_BDTScore_WHZL_Fake->Clone("BDTScore_WHZL_Fake");

 TH1D* BDTScore_WHZH_Data = (TH1D *)global_BDTScore_WHZH_Data->Clone("BDTScore_WHZH_Data");
 TH1D* BDTScore_WHZH_LL = (TH1D *)global_BDTScore_WHZH_LL->Clone("BDTScore_WHZH_LL");
 TH1D* BDTScore_WHZH_LT = (TH1D *)global_BDTScore_WHZH_LT->Clone("BDTScore_WHZH_LT");
 TH1D* BDTScore_WHZH_TL = (TH1D *)global_BDTScore_WHZH_TL->Clone("BDTScore_WHZH_TL");
 TH1D* BDTScore_WHZH_TT = (TH1D *)global_BDTScore_WHZH_TT->Clone("BDTScore_WHZH_TT");
 TH1D* BDTScore_WHZH_BkgZZ = (TH1D *)global_BDTScore_WHZH_BkgZZ->Clone("BDTScore_WHZH_BkgZZ");
 TH1D* BDTScore_WHZH_BkgWZEW = (TH1D *)global_BDTScore_WHZH_BkgWZEW->Clone("BDTScore_WHZH_BkgWZEW");
 TH1D* BDTScore_WHZH_BkgVVV = (TH1D *)global_BDTScore_WHZH_BkgVVV->Clone("BDTScore_WHZH_BkgVVV");
 TH1D* BDTScore_WHZH_BkgttbarV = (TH1D *)global_BDTScore_WHZH_BkgttbarV->Clone("BDTScore_WHZH_BkgttbarV");
 TH1D* BDTScore_WHZH_Fake = (TH1D *)global_BDTScore_WHZH_Fake->Clone("BDTScore_WHZH_Fake");

 TH1D* BDTScore_Signal = (TH1D *)BDTScore_LL->Clone("BDTScore_Signal");
 BDTScore_Signal->Add(BDTScore_LT);
 BDTScore_Signal->Add(BDTScore_TL);
 BDTScore_Signal->Add(BDTScore_TT);

 TH1D* BDTScore_Prompt = (TH1D *)BDTScore_BkgZZ->Clone("BDTScore_Prompt");
 BDTScore_Prompt->Add(BDTScore_BkgWZEW);
 BDTScore_Prompt->Add(BDTScore_BkgVVV);
 BDTScore_Prompt->Add(BDTScore_BkgttbarV);

 TH1D* BDTScore_NonPrompt = (TH1D *)BDTScore_Fake->Clone("BDTScore_NonPrompt");

 TH1D* BDTScore_WLZL_Prompt = (TH1D *)BDTScore_WLZL_BkgZZ->Clone("BDTScore_WLZL_Prompt");
 BDTScore_WLZL_Prompt->Add(BDTScore_WLZL_BkgWZEW);
 BDTScore_WLZL_Prompt->Add(BDTScore_WLZL_BkgVVV);
 BDTScore_WLZL_Prompt->Add(BDTScore_WLZL_BkgttbarV);

 TH1D* BDTScore_WLZH_Prompt = (TH1D *)BDTScore_WLZH_BkgZZ->Clone("BDTScore_WLZH_Prompt");
 BDTScore_WLZH_Prompt->Add(BDTScore_WLZH_BkgWZEW);
 BDTScore_WLZH_Prompt->Add(BDTScore_WLZH_BkgVVV);
 BDTScore_WLZH_Prompt->Add(BDTScore_WLZH_BkgttbarV);

 TH1D* BDTScore_WHZL_Prompt = (TH1D *)BDTScore_WHZL_BkgZZ->Clone("BDTScore_WHZL_Prompt");
 BDTScore_WHZL_Prompt->Add(BDTScore_WHZL_BkgWZEW);
 BDTScore_WHZL_Prompt->Add(BDTScore_WHZL_BkgVVV);
 BDTScore_WHZL_Prompt->Add(BDTScore_WHZL_BkgttbarV);

 TH1D* BDTScore_WHZH_Prompt = (TH1D *)BDTScore_WHZH_BkgZZ->Clone("BDTScore_WHZH_Prompt");
 BDTScore_WHZH_Prompt->Add(BDTScore_WHZH_BkgWZEW);
 BDTScore_WHZH_Prompt->Add(BDTScore_WHZH_BkgVVV);
 BDTScore_WHZH_Prompt->Add(BDTScore_WHZH_BkgttbarV);

 TH1D* BDTScore_WLZL_NonPrompt = (TH1D *)BDTScore_WLZL_Fake->Clone("BDTScore_WLZL_NonPrompt");
 TH1D* BDTScore_WLZH_NonPrompt = (TH1D *)BDTScore_WLZH_Fake->Clone("BDTScore_WLZH_NonPrompt");
 TH1D* BDTScore_WHZL_NonPrompt = (TH1D *)BDTScore_WHZL_Fake->Clone("BDTScore_WHZL_NonPrompt");
 TH1D* BDTScore_WHZH_NonPrompt = (TH1D *)BDTScore_WHZH_Fake->Clone("BDTScore_WHZH_NonPrompt");

 double LLFraction = BDTScore_LL->Integral() / BDTScore_Signal->Integral();
 double LTFraction = BDTScore_LT->Integral() / BDTScore_Signal->Integral();
 double TLFraction = BDTScore_TL->Integral() / BDTScore_Signal->Integral();
 double TTFraction = BDTScore_TT->Integral() / BDTScore_Signal->Integral();

 double LT_TLFraction = (BDTScore_LT->Integral() + BDTScore_TL->Integral()) / BDTScore_Signal->Integral();
 double LT_TL_TTFraction = (BDTScore_LT->Integral() + BDTScore_TL->Integral() + BDTScore_TT->Integral()) / BDTScore_Signal->Integral();

 if(NParameters == 2){
   BDTScore_LL->Scale(par[0] / LLFraction);
   BDTScore_LT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_TL->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_TT->Scale(par[1] / LT_TL_TTFraction);
   //BDTScore_Prompt->Scale(par[4]);
   //BDTScore_NonPrompt->Scale(par[5]);

   BDTScore_WLZL_LL->Scale(par[0] / LLFraction);
   BDTScore_WLZH_LL->Scale(par[0] / LLFraction);
   BDTScore_WHZL_LL->Scale(par[0] / LLFraction);
   BDTScore_WHZH_LL->Scale(par[0] / LLFraction);

   BDTScore_WLZL_LT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WLZH_LT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WHZL_LT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WHZH_LT->Scale(par[1] / LT_TL_TTFraction);

   BDTScore_WLZL_TL->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WLZH_TL->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WHZL_TL->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WHZH_TL->Scale(par[1] / LT_TL_TTFraction);

   BDTScore_WLZL_TT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WLZH_TT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WHZL_TT->Scale(par[1] / LT_TL_TTFraction);
   BDTScore_WHZH_TT->Scale(par[1] / LT_TL_TTFraction);
 }
 if(NParameters == 3){
   BDTScore_LL->Scale(par[0] / LLFraction);
   BDTScore_LT->Scale(par[1] / LT_TLFraction);
   BDTScore_TL->Scale(par[1] / LT_TLFraction);
   BDTScore_TT->Scale(par[3] / TTFraction);
   //BDTScore_Prompt->Scale(par[4]);
   //BDTScore_NonPrompt->Scale(par[5]);

   BDTScore_WLZL_LL->Scale(par[0] / LLFraction);
   BDTScore_WLZH_LL->Scale(par[0] / LLFraction);
   BDTScore_WHZL_LL->Scale(par[0] / LLFraction);
   BDTScore_WHZH_LL->Scale(par[0] / LLFraction);

   BDTScore_WLZL_LT->Scale(par[1] / LT_TLFraction);
   BDTScore_WLZH_LT->Scale(par[1] / LT_TLFraction);
   BDTScore_WHZL_LT->Scale(par[1] / LT_TLFraction);
   BDTScore_WHZH_LT->Scale(par[1] / LT_TLFraction);

   BDTScore_WLZL_TL->Scale(par[1] / LT_TLFraction);
   BDTScore_WLZH_TL->Scale(par[1] / LT_TLFraction);
   BDTScore_WHZL_TL->Scale(par[1] / LT_TLFraction);
   BDTScore_WHZH_TL->Scale(par[1] / LT_TLFraction);

   BDTScore_WLZL_TT->Scale(par[3] / TTFraction);
   BDTScore_WLZH_TT->Scale(par[3] / TTFraction);
   BDTScore_WHZL_TT->Scale(par[3] / TTFraction);
   BDTScore_WHZH_TT->Scale(par[3] / TTFraction);
 }


 TH1D* BDTScore_MC = (TH1D *)BDTScore_LL->Clone("BDTScore_MC");
 BDTScore_MC->Add(BDTScore_LT);
 BDTScore_MC->Add(BDTScore_TL);
 BDTScore_MC->Add(BDTScore_TT);
 BDTScore_MC->Add(BDTScore_Prompt);
 BDTScore_MC->Add(BDTScore_NonPrompt);

 TH1D* BDTScore_WLZL_MC = (TH1D *)BDTScore_WLZL_LL->Clone("BDTScore_WLZL_MC");
 BDTScore_WLZL_MC->Add(BDTScore_WLZL_LT);
 BDTScore_WLZL_MC->Add(BDTScore_WLZL_TL);
 BDTScore_WLZL_MC->Add(BDTScore_WLZL_TT);
 BDTScore_WLZL_MC->Add(BDTScore_WLZL_Prompt);
 BDTScore_WLZL_MC->Add(BDTScore_WLZL_NonPrompt);

 TH1D* BDTScore_WLZH_MC = (TH1D *)BDTScore_WLZH_LL->Clone("BDTScore_WLZH_MC");
 BDTScore_WLZH_MC->Add(BDTScore_WLZH_LT);
 BDTScore_WLZH_MC->Add(BDTScore_WLZH_TL);
 BDTScore_WLZH_MC->Add(BDTScore_WLZH_TT);
 BDTScore_WLZH_MC->Add(BDTScore_WLZH_Prompt);
 BDTScore_WLZH_MC->Add(BDTScore_WLZH_NonPrompt);

 TH1D* BDTScore_WHZL_MC = (TH1D *)BDTScore_WHZL_LL->Clone("BDTScore_WHZL_MC");
 BDTScore_WHZL_MC->Add(BDTScore_WHZL_LT);
 BDTScore_WHZL_MC->Add(BDTScore_WHZL_TL);
 BDTScore_WHZL_MC->Add(BDTScore_WHZL_TT);
 BDTScore_WHZL_MC->Add(BDTScore_WHZL_Prompt);
 BDTScore_WHZL_MC->Add(BDTScore_WHZL_NonPrompt);

 TH1D* BDTScore_WHZH_MC = (TH1D *)BDTScore_WHZH_LL->Clone("BDTScore_WHZH_MC");
 BDTScore_WHZH_MC->Add(BDTScore_WHZH_LT);
 BDTScore_WHZH_MC->Add(BDTScore_WHZH_TL);
 BDTScore_WHZH_MC->Add(BDTScore_WHZH_TT);
 BDTScore_WHZH_MC->Add(BDTScore_WHZH_Prompt);
 BDTScore_WHZH_MC->Add(BDTScore_WHZH_NonPrompt);

 bool isCategories = true;

 if(!isCategories) f = CalculateLLH(BDTScore_Data, BDTScore_MC, global_DataFactorial);

 if(isCategories) f = CalculateLLH(BDTScore_WLZL_Data, BDTScore_WLZL_MC, global_DataFactorial_WLZL)
                    + CalculateLLH(BDTScore_WLZH_Data, BDTScore_WLZH_MC, global_DataFactorial_WLZH)
                    + CalculateLLH(BDTScore_WHZL_Data, BDTScore_WHZL_MC, global_DataFactorial_WHZL)
                    + CalculateLLH(BDTScore_WHZH_Data, BDTScore_WHZH_MC, global_DataFactorial_WHZH);

 //f = CalculateChi2(BDTScore_Data, BDTScore_MC);

 if(f < MinChi2) MinChi2 = f;

 cout<<"Min Chi2 = "<<MinChi2<<endl;
 cout<<"Original LLFraction = "<<LLFraction<<endl;
 cout<<"Original LTFraction = "<<LTFraction<<endl;
 cout<<"Original TLFraction = "<<TLFraction<<endl;
 cout<<"Original TTFraction = "<<TTFraction<<endl;
 cout<<"Original LT_TLFraction = "<<LT_TLFraction<<endl;
 cout<<"Original LT_TL_TTFraction = "<<LT_TL_TTFraction<<endl;
 cout<<"LLScaleFactor = "<<par[0] / LLFraction<<endl;
 cout<<"LTScaleFactor = "<<par[1] / LTFraction<<endl;
 cout<<"TLScaleFactor = "<<par[1] / TLFraction<<endl;
 cout<<"TTScaleFactor = "<<par[3] / TTFraction<<endl;
 cout<<"LT_TLScaleFactor = "<<par[1] / LT_TLFraction<<endl;
 cout<<"LT_TL_TTScaleFactor = "<<par[1] / LT_TL_TTFraction<<endl;
 cout<<"Data = "<<BDTScore_Data->Integral()<<endl;
 cout<<"LL = "<<BDTScore_LL->Integral()<<endl;
 cout<<"LT = "<<BDTScore_LT->Integral()<<endl;
 cout<<"TL = "<<BDTScore_TL->Integral()<<endl;
 cout<<"TT = "<<BDTScore_TT->Integral()<<endl;
 cout<<"BkgZZ = "<<BDTScore_BkgZZ->Integral()<<endl;
 cout<<"BkgWZEW = "<<BDTScore_BkgWZEW->Integral()<<endl;
 cout<<"BkgVVV = "<<BDTScore_BkgVVV->Integral()<<endl;
 cout<<"BkgttbarV = "<<BDTScore_BkgttbarV->Integral()<<endl;
 cout<<"Fake = "<<BDTScore_Fake->Integral()<<endl;
 cout<<"Total = "<<BDTScore_LL->Integral()+BDTScore_LT->Integral()+BDTScore_TL->Integral()+BDTScore_TT->Integral()+BDTScore_BkgZZ->Integral()+BDTScore_BkgWZEW->Integral()+BDTScore_BkgVVV->Integral()+BDTScore_BkgttbarV->Integral()+BDTScore_Fake->Integral()<<endl;

}

int main(int argc, char** argv)
{
 TFile *file = new TFile("MC_results.root");

 TString Process = "LLH";

 TString Region = "Inclusive";
 TString isSR = "";
 if(Region == "Signal" || Region == "SignalPtWZ") isSR = "SR";

 TH1D* CosThetaV_WLZL_LL = (TH1D *)file->Get("CosThetaV_WLZL_" + Region + "_LL");
 TH1D* CosThetaV_WLZL_LT = (TH1D *)file->Get("CosThetaV_WLZL_" + Region + "_LT");
 TH1D* CosThetaV_WLZL_TL = (TH1D *)file->Get("CosThetaV_WLZL_" + Region + "_TL");
 TH1D* CosThetaV_WLZL_TT = (TH1D *)file->Get("CosThetaV_WLZL_" + Region + "_TT");

 TH1D* CosThetaV_WLZH_LL = (TH1D *)file->Get("CosThetaV_WLZH_" + Region + "_LL");
 TH1D* CosThetaV_WLZH_LT = (TH1D *)file->Get("CosThetaV_WLZH_" + Region + "_LT");
 TH1D* CosThetaV_WLZH_TL = (TH1D *)file->Get("CosThetaV_WLZH_" + Region + "_TL");
 TH1D* CosThetaV_WLZH_TT = (TH1D *)file->Get("CosThetaV_WLZH_" + Region + "_TT");

 TH1D* CosThetaV_WHZL_LL = (TH1D *)file->Get("CosThetaV_WHZL_" + Region + "_LL");
 TH1D* CosThetaV_WHZL_LT = (TH1D *)file->Get("CosThetaV_WHZL_" + Region + "_LT");
 TH1D* CosThetaV_WHZL_TL = (TH1D *)file->Get("CosThetaV_WHZL_" + Region + "_TL");
 TH1D* CosThetaV_WHZL_TT = (TH1D *)file->Get("CosThetaV_WHZL_" + Region + "_TT");

 TH1D* CosThetaV_WHZH_LL = (TH1D *)file->Get("CosThetaV_WHZH_" + Region + "_LL");
 TH1D* CosThetaV_WHZH_LT = (TH1D *)file->Get("CosThetaV_WHZH_" + Region + "_LT");
 TH1D* CosThetaV_WHZH_TL = (TH1D *)file->Get("CosThetaV_WHZH_" + Region + "_TL");
 TH1D* CosThetaV_WHZH_TT = (TH1D *)file->Get("CosThetaV_WHZH_" + Region + "_TT");

// TH1D* CosThetaV_WLZL_Data = (TH1D *)file->Get("CosThetaV_WLZL_" + Region + "_FinalData");
// TH1D* CosThetaV_WLZH_Data = (TH1D *)file->Get("CosThetaV_WLZH_" + Region + "_FinalData");
// TH1D* CosThetaV_WHZL_Data = (TH1D *)file->Get("CosThetaV_WHZL_" + Region + "_FinalData");
// TH1D* CosThetaV_WHZH_Data = (TH1D *)file->Get("CosThetaV_WHZH_" + Region + "_FinalData");

 TH1D* CosThetaV_WLZL_Data = (TH1D *)file->Get("CosThetaV_WLZL_Data" + Region);
 TH1D* CosThetaV_WLZH_Data = (TH1D *)file->Get("CosThetaV_WLZH_Data" + Region);
 TH1D* CosThetaV_WHZL_Data = (TH1D *)file->Get("CosThetaV_WHZL_Data" + Region);
 TH1D* CosThetaV_WHZH_Data = (TH1D *)file->Get("CosThetaV_WHZH_Data" + Region);

 TH1D* BDTScore_Data = (TH1D *)file->Get("BDTScore" + isSR + "_" + "Data" + Region);
 TH1D* BDTScore_LL = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_LL");
 TH1D* BDTScore_LT = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_LT");
 TH1D* BDTScore_TL = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_TL");
 TH1D* BDTScore_TT = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_TT");
 TH1D* BDTScore_BkgZZ = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_BkgZZ");
 TH1D* BDTScore_BkgWZEW = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_BkgWZEW");
 TH1D* BDTScore_BkgVVV = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_BkgVVV");
 TH1D* BDTScore_BkgttbarV = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_BkgttbarV");
 TH1D* BDTScore_Fake = (TH1D *)file->Get("BDTScore" + isSR + "_" + Region + "_Fake");

 TH1D* BDTScore_WLZL_Data = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + "Data" + Region);
 TH1D* BDTScore_WLZL_LL = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_LL");
 TH1D* BDTScore_WLZL_LT = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_LT");
 TH1D* BDTScore_WLZL_TL = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_TL");
 TH1D* BDTScore_WLZL_TT = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_TT");
 TH1D* BDTScore_WLZL_BkgZZ = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_BkgZZ");
 TH1D* BDTScore_WLZL_BkgWZEW = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_BkgWZEW");
 TH1D* BDTScore_WLZL_BkgVVV = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_BkgVVV");
 TH1D* BDTScore_WLZL_BkgttbarV = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_BkgttbarV");
 TH1D* BDTScore_WLZL_Fake = (TH1D *)file->Get("BDTScore" + isSR + "_WLZL" + "_" + Region + "_Fake");

 TH1D* BDTScore_WLZH_Data = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + "Data" + Region);
 TH1D* BDTScore_WLZH_LL = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_LL");
 TH1D* BDTScore_WLZH_LT = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_LT");
 TH1D* BDTScore_WLZH_TL = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_TL");
 TH1D* BDTScore_WLZH_TT = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_TT");
 TH1D* BDTScore_WLZH_BkgZZ = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_BkgZZ");
 TH1D* BDTScore_WLZH_BkgWZEW = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_BkgWZEW");
 TH1D* BDTScore_WLZH_BkgVVV = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_BkgVVV");
 TH1D* BDTScore_WLZH_BkgttbarV = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_BkgttbarV");
 TH1D* BDTScore_WLZH_Fake = (TH1D *)file->Get("BDTScore" + isSR + "_WLZH" + "_" + Region + "_Fake");

 TH1D* BDTScore_WHZL_Data = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + "Data" + Region);
 TH1D* BDTScore_WHZL_LL = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_LL");
 TH1D* BDTScore_WHZL_LT = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_LT");
 TH1D* BDTScore_WHZL_TL = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_TL");
 TH1D* BDTScore_WHZL_TT = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_TT");
 TH1D* BDTScore_WHZL_BkgZZ = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_BkgZZ");
 TH1D* BDTScore_WHZL_BkgWZEW = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_BkgWZEW");
 TH1D* BDTScore_WHZL_BkgVVV = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_BkgVVV");
 TH1D* BDTScore_WHZL_BkgttbarV = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_BkgttbarV");
 TH1D* BDTScore_WHZL_Fake = (TH1D *)file->Get("BDTScore" + isSR + "_WHZL" + "_" + Region + "_Fake");

 TH1D* BDTScore_WHZH_Data = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + "Data" + Region);
 TH1D* BDTScore_WHZH_LL = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_LL");
 TH1D* BDTScore_WHZH_LT = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_LT");
 TH1D* BDTScore_WHZH_TL = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_TL");
 TH1D* BDTScore_WHZH_TT = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_TT");
 TH1D* BDTScore_WHZH_BkgZZ = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_BkgZZ");
 TH1D* BDTScore_WHZH_BkgWZEW = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_BkgWZEW");
 TH1D* BDTScore_WHZH_BkgVVV = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_BkgVVV");
 TH1D* BDTScore_WHZH_BkgttbarV = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_BkgttbarV");
 TH1D* BDTScore_WHZH_Fake = (TH1D *)file->Get("BDTScore" + isSR + "_WHZH" + "_" + Region + "_Fake");

 BDTScore_WLZL_Data->Rebin(2);
 BDTScore_WLZL_LL->Rebin(2);
 BDTScore_WLZL_LT->Rebin(2);
 BDTScore_WLZL_TL->Rebin(2);
 BDTScore_WLZL_TT->Rebin(2);
 BDTScore_WLZL_BkgZZ->Rebin(2);
 BDTScore_WLZL_BkgWZEW->Rebin(2);
 BDTScore_WLZL_BkgVVV->Rebin(2);
 BDTScore_WLZL_BkgttbarV->Rebin(2);
 BDTScore_WLZL_Fake->Rebin(2);

 BDTScore_WLZH_Data->Rebin(2);
 BDTScore_WLZH_LL->Rebin(2);
 BDTScore_WLZH_LT->Rebin(2);
 BDTScore_WLZH_TL->Rebin(2);
 BDTScore_WLZH_TT->Rebin(2);
 BDTScore_WLZH_BkgZZ->Rebin(2);
 BDTScore_WLZH_BkgWZEW->Rebin(2);
 BDTScore_WLZH_BkgVVV->Rebin(2);
 BDTScore_WLZH_BkgttbarV->Rebin(2);
 BDTScore_WLZH_Fake->Rebin(2);

 BDTScore_WHZL_Data->Rebin(2);
 BDTScore_WHZL_LL->Rebin(2);
 BDTScore_WHZL_LT->Rebin(2);
 BDTScore_WHZL_TL->Rebin(2);
 BDTScore_WHZL_TT->Rebin(2);
 BDTScore_WHZL_BkgZZ->Rebin(2);
 BDTScore_WHZL_BkgWZEW->Rebin(2);
 BDTScore_WHZL_BkgVVV->Rebin(2);
 BDTScore_WHZL_BkgttbarV->Rebin(2);
 BDTScore_WHZL_Fake->Rebin(2);

 BDTScore_WHZH_Data->Rebin(2);
 BDTScore_WHZH_LL->Rebin(2);
 BDTScore_WHZH_LT->Rebin(2);
 BDTScore_WHZH_TL->Rebin(2);
 BDTScore_WHZH_TT->Rebin(2);
 BDTScore_WHZH_BkgZZ->Rebin(2);
 BDTScore_WHZH_BkgWZEW->Rebin(2);
 BDTScore_WHZH_BkgVVV->Rebin(2);
 BDTScore_WHZH_BkgttbarV->Rebin(2);
 BDTScore_WHZH_Fake->Rebin(2);


 vector<double> DataFactorial;
 vector<double> DataFactorial_WLZL;
 vector<double> DataFactorial_WLZH;
 vector<double> DataFactorial_WHZL;
 vector<double> DataFactorial_WHZH;
 for(int ibin = 1; ibin <= BDTScore_Data->GetNbinsX(); ibin++){
   DataFactorial.push_back(CalLogFactorial(BDTScore_Data->GetBinContent(ibin)));
 }

 for(int ibin = 1; ibin <= BDTScore_WLZL_Data->GetNbinsX(); ibin++){
   DataFactorial_WLZL.push_back(CalLogFactorial(BDTScore_WLZL_Data->GetBinContent(ibin)));
   DataFactorial_WLZH.push_back(CalLogFactorial(BDTScore_WLZH_Data->GetBinContent(ibin)));
   DataFactorial_WHZL.push_back(CalLogFactorial(BDTScore_WHZL_Data->GetBinContent(ibin)));
   DataFactorial_WHZH.push_back(CalLogFactorial(BDTScore_WHZH_Data->GetBinContent(ibin)));
 }


 global_CosThetaV_WLZL_LL = CosThetaV_WLZL_LL;
 global_CosThetaV_WLZL_LT = CosThetaV_WLZL_LT;
 global_CosThetaV_WLZL_TL = CosThetaV_WLZL_TL;
 global_CosThetaV_WLZL_TT = CosThetaV_WLZL_TT;

 global_CosThetaV_WLZH_LL = CosThetaV_WLZH_LL;
 global_CosThetaV_WLZH_LT = CosThetaV_WLZH_LT;
 global_CosThetaV_WLZH_TL = CosThetaV_WLZH_TL;
 global_CosThetaV_WLZH_TT = CosThetaV_WLZH_TT;

 global_CosThetaV_WHZL_LL = CosThetaV_WHZL_LL;
 global_CosThetaV_WHZL_LT = CosThetaV_WHZL_LT;
 global_CosThetaV_WHZL_TL = CosThetaV_WHZL_TL;
 global_CosThetaV_WHZL_TT = CosThetaV_WHZL_TT;

 global_CosThetaV_WHZH_LL = CosThetaV_WHZH_LL;
 global_CosThetaV_WHZH_LT = CosThetaV_WHZH_LT;
 global_CosThetaV_WHZH_TL = CosThetaV_WHZH_TL;
 global_CosThetaV_WHZH_TT = CosThetaV_WHZH_TT;

 global_CosThetaV_WLZL_Data = CosThetaV_WLZL_Data;
 global_CosThetaV_WLZH_Data = CosThetaV_WLZH_Data;
 global_CosThetaV_WHZL_Data = CosThetaV_WHZL_Data;
 global_CosThetaV_WHZH_Data = CosThetaV_WHZH_Data;

 global_BDTScore_Data = BDTScore_Data;
 global_BDTScore_LL = BDTScore_LL;
 global_BDTScore_LT = BDTScore_LT;
 global_BDTScore_TL = BDTScore_TL;
 global_BDTScore_TT = BDTScore_TT;
 global_BDTScore_BkgZZ = BDTScore_BkgZZ;
 global_BDTScore_BkgWZEW = BDTScore_BkgWZEW;
 global_BDTScore_BkgVVV = BDTScore_BkgVVV;
 global_BDTScore_BkgttbarV = BDTScore_BkgttbarV;
 global_BDTScore_Fake = BDTScore_Fake;
 global_DataFactorial = DataFactorial;

 global_BDTScore_WLZL_Data = BDTScore_WLZL_Data;
 global_BDTScore_WLZL_LL = BDTScore_WLZL_LL;
 global_BDTScore_WLZL_LT = BDTScore_WLZL_LT;
 global_BDTScore_WLZL_TL = BDTScore_WLZL_TL;
 global_BDTScore_WLZL_TT = BDTScore_WLZL_TT;
 global_BDTScore_WLZL_BkgZZ = BDTScore_WLZL_BkgZZ;
 global_BDTScore_WLZL_BkgWZEW = BDTScore_WLZL_BkgWZEW;
 global_BDTScore_WLZL_BkgVVV = BDTScore_WLZL_BkgVVV;
 global_BDTScore_WLZL_BkgttbarV = BDTScore_WLZL_BkgttbarV;
 global_BDTScore_WLZL_Fake = BDTScore_WLZL_Fake;
 global_DataFactorial_WLZL = DataFactorial_WLZL;

 global_BDTScore_WLZH_Data = BDTScore_WLZH_Data;
 global_BDTScore_WLZH_LL = BDTScore_WLZH_LL;
 global_BDTScore_WLZH_LT = BDTScore_WLZH_LT;
 global_BDTScore_WLZH_TL = BDTScore_WLZH_TL;
 global_BDTScore_WLZH_TT = BDTScore_WLZH_TT;
 global_BDTScore_WLZH_BkgZZ = BDTScore_WLZH_BkgZZ;
 global_BDTScore_WLZH_BkgWZEW = BDTScore_WLZH_BkgWZEW;
 global_BDTScore_WLZH_BkgVVV = BDTScore_WLZH_BkgVVV;
 global_BDTScore_WLZH_BkgttbarV = BDTScore_WLZH_BkgttbarV;
 global_BDTScore_WLZH_Fake = BDTScore_WLZH_Fake;
 global_DataFactorial_WLZH = DataFactorial_WLZH;

 global_BDTScore_WHZL_Data = BDTScore_WHZL_Data;
 global_BDTScore_WHZL_LL = BDTScore_WHZL_LL;
 global_BDTScore_WHZL_LT = BDTScore_WHZL_LT;
 global_BDTScore_WHZL_TL = BDTScore_WHZL_TL;
 global_BDTScore_WHZL_TT = BDTScore_WHZL_TT;
 global_BDTScore_WHZL_BkgZZ = BDTScore_WHZL_BkgZZ;
 global_BDTScore_WHZL_BkgWZEW = BDTScore_WHZL_BkgWZEW;
 global_BDTScore_WHZL_BkgVVV = BDTScore_WHZL_BkgVVV;
 global_BDTScore_WHZL_BkgttbarV = BDTScore_WHZL_BkgttbarV;
 global_BDTScore_WHZL_Fake = BDTScore_WHZL_Fake;
 global_DataFactorial_WHZL = DataFactorial_WHZL;

 global_BDTScore_WHZH_Data = BDTScore_WHZH_Data;
 global_BDTScore_WHZH_LL = BDTScore_WHZH_LL;
 global_BDTScore_WHZH_LT = BDTScore_WHZH_LT;
 global_BDTScore_WHZH_TL = BDTScore_WHZH_TL;
 global_BDTScore_WHZH_TT = BDTScore_WHZH_TT;
 global_BDTScore_WHZH_BkgZZ = BDTScore_WHZH_BkgZZ;
 global_BDTScore_WHZH_BkgWZEW = BDTScore_WHZH_BkgWZEW;
 global_BDTScore_WHZH_BkgVVV = BDTScore_WHZH_BkgVVV;
 global_BDTScore_WHZH_BkgttbarV = BDTScore_WHZH_BkgttbarV;
 global_BDTScore_WHZH_Fake = BDTScore_WHZH_Fake;
 global_DataFactorial_WHZH = DataFactorial_WHZH;

 int NParameters = 2;
 global_NParameters = NParameters;

 TMinuitHelper *myMinuit = new TMinuitHelper(4);

 if(Process == "Chi2"){
   myMinuit->SetFCN(WZPolFitting);
   myMinuit->Input(0, "LLFraction", 0.5, 0.5, 0.0, 1.0);
   myMinuit->Input(1, "LTFraction", 0.5, 0.5, 0.0, 1.0);
   myMinuit->Input(2, "TLFraction", 0.5, 0.5, 0.0, 1.0);
   myMinuit->Input(3, "TTFraction", 0.5, 0.5, 0.0, 1.0);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[4];
   double* SParError = new double[4];
   myMinuit->GetParametersAndError(SPar, SParError);
 }
 if(Process == "LLH"){
   myMinuit->SetFCN(WZPolFittingLLH);
   myMinuit->SetErrorDef(0.5);
   myMinuit->Input(0, "LLFraction", 0.06, 0.5, 0.0, 1.0);
   myMinuit->Input(1, "LTFraction", 0.16, 0.5, 0.0, 1.0);
   myMinuit->Input(2, "TLFraction", 0.5, 0.0, 0.0, 1.0);
   myMinuit->Input(3, "TTFraction", 0.62, 0.0, 0.0, 1.0);
   //myMinuit->Input(4, "PromptBkgScale", 1.0, 0.5, 0.5, 2.0);
   //myMinuit->Input(5, "NonPromptBkgScale", 1.0, 0.5, 0.5, 2.0);
   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   myMinuit->GetParameter();
   double* SPar = new double[4];
   double* SParError = new double[4];
   myMinuit->GetParametersAndError(SPar, SParError);
 }

 return 1;
}
