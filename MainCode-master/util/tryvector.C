#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "Analysis/control.h"
#include "ePump/ePump.h"
#include "ePump/Cholesky.h"
#include "WZPolarization/HistsWZPolarization.h"
#include "Tools/Interpolation.h"
#include "Tools/LatexOutput.h"
#include "Tools/SimpleIntegral.h"
#include "ElectroweakTheory/ResBosEW.h"
#include "Analysis/treeDrawThread.h"
#include "Calculation/CTUtil.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "CTEQHelper/sumReader.h"
#include "Calculation/ApplGridHelper.h"

using namespace std;
using namespace std::placeholders;

void TryStatic(bool isEnter)
{
 static double a, b;

 if(isEnter){
   a = 5.0;
   b = 3.0;
 }
 else{

 }
 cout<<a<<"  "<<b<<endl;

}

void TryStatic2(bool isEnter)
{
 static double a, b;

 if(isEnter){
   a = 15.0;
   b = 13.0;
 }
 else{

 }
 cout<<a<<"  "<<b<<endl;

}

map<int, void(*)(double &)> threadfunction;

void TryFunction(void (*fcn)(double &))
{
 double input;
 fcn(input);

 cout<<input<<endl;
}

void TryPointer(int* a)
{
 a[0] = 10;
 a[1] = 20;
 a[2] = 30;
}

double Gaus(double x)
{
 double Value = (1.0 / sqrt(2 * 3.1415926)) * exp((-1) * 0.5 * x * x);

 return Value;
}

class TestPointer
{
 public:

 TH1D* h1 = 0;
 void Initialize(){
   TH1D hist("h1", "h1", 10, 1, 10);
   h1 = &hist;
 }
 void Test(){
   cout<<h1<<endl;
 }
};

int main(int argc, char** argv)
{

/* ifstream infile;
  infile.open("data.list", ios::in);

 vector<TString> RootNames;
 TString RootName;

 while(infile>>RootName){
   RootNames.push_back(RootName);
 }

 TString SaveName;
 TString BkgName = "InclusiveAndPolarized";


 vector<TString> SysNames;

 SysNames.push_back("MET_SoftTrk_ScaleDown__1down");
 SysNames.push_back("MET_SoftTrk_ScaleUp__1up");

 SysNames.at(0).ReplaceAll("Down__1down", "");
 SysNames.at(1).ReplaceAll("Up__1up", "");

 cout<<SysNames.at(0)<<endl;
 cout<<SysNames.at(1)<<endl;

 map<int, int> ListFlag;
 TString Name = "364253_Sherpa_222_NNPDF30NNLO_lllv";
 TString ChannelNumber = Name(0, 6);
 ListFlag[stoi(ChannelNumber.Data())] = 1;

 cout<<ListFlag[364253]<<endl;
 cout<<ListFlag[364250]<<endl;
*/

/* map<vector<int>, TString> IndexMap;
 vector<int> Index1 = {0, 1, 1, 1};
 vector<int> Index2 = {0, 1, 2, 3};
 IndexMap[Index1] = "Index1";
 IndexMap[Index2] = "Index2";

 vector<int> Try1;
 vector<int> Try2;
 Try1.push_back(0);
 Try1.push_back(1);
 Try1.push_back(1);
 Try1.push_back(1);

 Try2.push_back(0);
 Try2.push_back(1);
 Try2.push_back(2);
 Try2.push_back(3);

 cout<<IndexMap[Try1]<<endl;
 cout<<IndexMap[Try2]<<endl;
*/

/* TFile* file = new TFile("save.root");
 TH2D* uuDelta = (TH2D *)file->Get("uuDelta");
 TH2D* uuError = (TH2D *)file->Get("uuError");
 TH2D* ddDelta = (TH2D *)file->Get("ddDelta");
 TH2D* ddError = (TH2D *)file->Get("ddError");

 TFile* writefile = new TFile("Chi2.root", "RECREATE");
 writefile->cd();

 TH1D* uuChi2 = new TH1D("uuChi2", "uuChi2", 10, -1, 1);
 TH1D* ddChi2 = new TH1D("ddChi2", "ddChi2", 10, -1, 1);

 for(int ibinx = 1; ibinx <= uuDelta->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= uuDelta->GetNbinsX(); ibiny++){
     uuChi2->Fill(uuDelta->GetBinContent(ibinx, ibiny) / uuError->GetBinContent(ibinx, ibiny), 1);
     ddChi2->Fill(ddDelta->GetBinContent(ibinx, ibiny) / ddError->GetBinContent(ibinx, ibiny), 1);
   }
 }

 writefile->Write();
 writefile->Close();
*/

// LOG_INFO("try log", " :", " ...");

/* vector<double> tmpYBin = {0.0, 1.0};

 tmpYBin = {1.0, 2.0};

 tmpYBin = {3.0, 4.0, 5.0};

 for(int i = 0; i < tmpYBin.size(); i++){
   cout<<tmpYBin.at(i)<<endl;
 }

 tmpYBin = {1.0, 2.0};

 for(int i = 0; i < tmpYBin.size(); i++){
   cout<<tmpYBin.at(i)<<endl;
 }
*/

/*
 TFile* file = new TFile("MC_results.root");

 TH1D* y1 = (TH1D *)file->Get("CutEff_ZPt_y1");
 TH1D* y2 = (TH1D *)file->Get("CutEff_ZPt_y2");
 TH1D* y3 = (TH1D *)file->Get("CutEff_ZPt_y3");
 TH1D* y4 = (TH1D *)file->Get("CutEff_ZPt_y4");
 TH1D* y5 = (TH1D *)file->Get("CutEff_ZPt_y5");
 TH1D* y6 = (TH1D *)file->Get("CutEff_ZPt_y6");

 ifstream infile;
   infile.open("ATLAS_rap.dat");
 string FileLine;
 double skip;
 for(int i = 0; i < 5; i++){
   getline(infile, FileLine);
 }
 vector<double> QMin;
 vector<double> QMax;
 vector<double> ymin;
 vector<double> ymax;
 vector<double> pT;
 vector<double> data;
 vector<double> eff;

 while(infile >> skip){
   QMin.push_back(skip);
   infile >> skip;
   QMax.push_back(skip);
   infile >> skip;
   ymin.push_back(skip);
   infile >> skip;
   ymax.push_back(skip);
   infile >> skip;
   pT.push_back(skip);
   infile >> skip;
   data.push_back(skip);
   infile >> skip >> skip >> skip;
   eff.push_back(skip);
   infile >> skip >> skip >> skip;
 }

 vector<double> effIY6;

 for(int i = 1; i <= 8; i++){
   cout<<y1->GetBinContent(i) * 0.033632<<endl;
   effIY6.push_back(y1->GetBinContent(i) * 0.033632);
 }
 for(int i = 1; i <= 8; i++){
   cout<<y2->GetBinContent(i) * 0.033632<<endl;
   effIY6.push_back(y2->GetBinContent(i) * 0.033632);
 }
 for(int i = 1; i <= 8; i++){
   cout<<y3->GetBinContent(i) * 0.033632<<endl;
   effIY6.push_back(y3->GetBinContent(i) * 0.033632);
 }
 for(int i = 1; i <= 8; i++){
   cout<<y4->GetBinContent(i) * 0.033632<<endl;
   effIY6.push_back(y4->GetBinContent(i) * 0.033632);
 }
 for(int i = 1; i <= 8; i++){
   cout<<y5->GetBinContent(i) * 0.033632<<endl;
   effIY6.push_back(y5->GetBinContent(i) * 0.033632);
 }
 for(int i = 1; i <= 8; i++){
   cout<<y6->GetBinContent(i) * 0.033632<<endl;
   effIY6.push_back(y6->GetBinContent(i) * 0.033632);
 }

 for(int i = 0; i < effIY6.size(); i++){
   cout<<fixed<<setprecision(3)<<QMin.at(i)<<" "<<QMax.at(i)<<" "<<ymin.at(i)<<" "<<ymax.at(i);
   cout<<setw(2)<<*right<<fixed<<setprecision(3)<<" "<<pT.at(i);
   cout<<setw(2)<<setprecision(3)<<" "<<data.at(i);
   cout<<setw(2)<<setprecision(8)<<" "<<eff.at(i);
   cout<<setw(2)<<setprecision(8)<<" "<<effIY6.at(i);
   cout<<setw(2)<<setprecision(8)<<" "<<effIY6.at(i) - eff.at(i)<<endl;
*/

/* ofstream trylog;
 Logstream myLog;
 myLog.Initial(cout, trylog);
 trylog.open("try.log");

 TString mystring = "This is a TString.";

 myLog<<INFO<<"Try: "<<mystring<<" "<<1.1<<endl;

 Control process;
 process.LinkLog(myLog);
 process.ReadFile("cardfile.in");
*/

/* vector<double> x = {94, 87, 81, 76, 71, 65, 61, 56, 51, 48, 44, 41, 37, 34, 31, 28, 26, 25, 23, 22, 21, 23, 24, 25, 26, 29, 33,
                     36, 40, 46, 52, 58, 65, 72, 79, 86, 93, 100, 107, 113, 119, 124, 130, 135, 140, 144, 148, 151, 155, 157};

 for(int i = 0; i < x.size(); i++){
   cout<<" MtW_CDF_Data->SetBinContent("<<i+1<<", "<<(184.0-x.at(i))*70.0/171.0*1000.0<<");"<<endl;
 }

 vector<double> x1 = {309, 305, 302, 299, 296, 293, 289, 286, 283, 279, 276, 273, 269, 267, 263, 261, 257, 254, 252, 249, 247, 245, 243, 242, 241, 241, 242, 244, 246, 250,
                      253, 258, 264, 270, 278, 285, 292, 299, 306, 313, 320, 325, 331, 337, 341, 346, 350, 354, 358, 361, 364, 367, 370, 372, 374, 377, 378, 381, 382,
                      384, 386, 387, 388, 389};

 for(int i = 0; i < x1.size(); i++){
   cout<<" LeptonPt_CDF_Data->SetBinContent("<<i+1<<", "<<(403.0-x1.at(i))*60.0/171.0*1000.0<<");"<<endl;
 }

 vector<double> x2 = {509, 506, 502, 499, 495, 492, 489, 485, 483, 480, 478, 475, 472, 470, 468, 466, 465, 463, 462, 461, 460,
                      460, 460, 460, 461, 463, 464, 465, 468, 471, 474, 477, 481, 485, 489, 494, 499, 504, 508, 514, 518, 524,
                      528, 534, 539, 543, 548, 552, 556, 560, 564, 568, 572, 575, 578, 581, 584, 587, 590, 592, 595, 597, 599, 601};

 for(int i = 0; i < x2.size(); i++){
   cout<<" NuPt_CDF_Data->SetBinContent("<<i+1<<", "<<(622.0-x2.at(i))*51.875/171.0*1000.0<<");"<<endl;
 }
*/

/* vector<double> x = {396, 368, 343, 318, 294, 269, 249, 227, 208, 190, 175, 160, 146, 136, 122, 114, 109, 105, 102, 102, 104, 110, 116,
                     122, 133, 147, 161, 181, 203, 226, 252, 278, 306, 333, 363, 389, 421, 449, 475, 499, 525, 552, 572, 595, 614, 631,
                     646, 660, 673, 684};

 for(int i = 0; i < x.size(); i++){
   cout<<" MtW_CDF_Electron->SetBinContent("<<i+1<<", "<<(791.0-x.at(i))*49.106/728.0*1000.0<<");"<<endl;
 }

 vector<double> x1 = {382, 366, 351, 335, 320, 305, 288, 274, 259, 242, 228, 214, 200, 187, 171, 162, 146, 136, 122, 114, 106, 97, 92,
                      91, 89, 93, 96, 104, 113, 129, 149, 169, 194, 221, 247, 279, 305, 342, 371, 399, 431, 460, 483, 511, 533, 556, 573,
                      592, 608, 622, 637, 650, 661, 672, 683, 692, 701, 708, 716, 724, 731, 737, 741, 745};

 for(int i = 0; i < x1.size(); i++){
   cout<<" LeptonPt_CDF_Electron->SetBinContent("<<i+1<<", "<<(803.0-x1.at(i))*43.924/750.0*1000.0<<");"<<endl;
 }

 vector<double> x2 = {290, 275, 258, 243, 227, 216, 203, 189, 177, 163, 153, 142, 133, 123, 114, 107, 101, 95, 93, 90, 88, 91, 91, 96, 101,
                      109, 117, 127, 139, 153, 170, 183, 201, 222, 238, 261, 282, 301, 325, 346, 367, 391, 413, 429, 453, 472, 493, 512, 529,
                      548, 566, 583, 594, 610, 623, 637, 651, 662, 673, 685, 693, 703, 710, 717};

 for(int i = 0; i < x2.size(); i++){
   cout<<" NuPt_CDF_Electron->SetBinContent("<<i+1<<", "<<(807.0-x2.at(i))*39.108/760.0*1000.0<<");"<<endl;
 }
*/

/* TFile* file = new TFile("LinearDilutionFitting.root", "RECREATE");
 file->cd();

 TH1D* Delta_uu = new TH1D("Delta_uu", "Delta_uu", 4, 0, 4);
 TH1D* Delta_dd = new TH1D("Delta_dd", "Delta_dd", 4, 0, 4);
 TH1D* Error_uu = new TH1D("Error_uu", "Error_uu", 4, 0, 4);
 TH1D* Error_dd = new TH1D("Error_dd", "Error_dd", 4, 0, 4);
 TH1D* Delta_uu_Slope = new TH1D("Delta_uu_Slope", "Delta_uu_Slope", 4, 0, 4);
 TH1D* Delta_dd_Slope = new TH1D("Delta_dd_Slope", "Delta_dd_Slope", 4, 0, 4);
 TH1D* Error_uu_Slope = new TH1D("Error_uu_Slope", "Error_uu_Slope", 4, 0, 4);
 TH1D* Error_dd_Slope = new TH1D("Error_dd_Slope", "Error_dd_Slope", 4, 0, 4);
 TH1D* Fitted_stw = new TH1D("Fitted_stw", "Fitted_stw", 4, 0, 4);
 TH1D* Input_stw = new TH1D("Input_stw", "Input_stw", 4, 0, 4);

 Delta_uu->SetBinContent(1, 0.00084955);
 Delta_uu->SetBinError(1, 0.0);
 Delta_uu->SetBinContent(2, 0.000133765);
 Delta_uu->SetBinError(2, 0.0);
 Delta_uu->SetBinContent(3, 0.000192806);
 Delta_uu->SetBinError(3, 0.0);
 Delta_uu->SetBinContent(4, 0.0079303);
 Delta_uu->SetBinError(4, 0.0);

 Delta_dd->SetBinContent(1, 0.00293632);
 Delta_dd->SetBinError(1, 0.0);
 Delta_dd->SetBinContent(2, 0.00356118);
 Delta_dd->SetBinError(2, 0.0);
 Delta_dd->SetBinContent(3, 0.00710498);
 Delta_dd->SetBinError(3, 0.0);
 Delta_dd->SetBinContent(4, 0.00605801);
 Delta_dd->SetBinError(4, 0.0);

 Error_uu->SetBinContent(1, 0.00278398);
 Error_uu->SetBinError(1, 0.0);
 Error_uu->SetBinContent(2, 0.00581457);
 Error_uu->SetBinError(2, 0.0);
 Error_uu->SetBinContent(3, 0.00899915);
 Error_uu->SetBinError(3, 0.0);
 Error_uu->SetBinContent(4, 0.0142071);
 Error_uu->SetBinError(4, 0.0);

 Error_dd->SetBinContent(1, 0.00824059);
 Error_dd->SetBinError(1, 0.0);
 Error_dd->SetBinContent(2, 0.01198);
 Error_dd->SetBinError(2, 0.0);
 Error_dd->SetBinContent(3, 0.0169173);
 Error_dd->SetBinError(3, 0.0);
 Error_dd->SetBinContent(4, 0.0257903);
 Error_dd->SetBinError(4, 0.0);

 Delta_uu_Slope->SetBinContent(1, 0.00344165);
 Delta_uu_Slope->SetBinError(1, 0.0);
 Delta_uu_Slope->SetBinContent(2, 0.00635406);
 Delta_uu_Slope->SetBinError(2, 0.0);
 Delta_uu_Slope->SetBinContent(3, 0.00664727);
 Delta_uu_Slope->SetBinError(3, 0.0);
 Delta_uu_Slope->SetBinContent(4, 0.0029593);
 Delta_uu_Slope->SetBinError(4, 0.0);

 Delta_dd_Slope->SetBinContent(1, 0.0101908);
 Delta_dd_Slope->SetBinError(1, 0.0);
 Delta_dd_Slope->SetBinContent(2, 0.00639455);
 Delta_dd_Slope->SetBinError(2, 0.0);
 Delta_dd_Slope->SetBinContent(3, 0.00561497);
 Delta_dd_Slope->SetBinError(3, 0.0);
 Delta_dd_Slope->SetBinContent(4, 0.00174814);
 Delta_dd_Slope->SetBinError(4, 0.0);

 Error_uu_Slope->SetBinContent(1, 0.0161326);
 Error_uu_Slope->SetBinError(1, 0.0);
 Error_uu_Slope->SetBinContent(2, 0.0130488);
 Error_uu_Slope->SetBinError(2, 0.0);
 Error_uu_Slope->SetBinContent(3, 0.00432416);
 Error_uu_Slope->SetBinError(3, 0.0);
 Error_uu_Slope->SetBinContent(4, 0.00318306);
 Error_uu_Slope->SetBinError(4, 0.0);

 Error_dd_Slope->SetBinContent(1, 0.0192008);
 Error_dd_Slope->SetBinError(1, 0.0);
 Error_dd_Slope->SetBinContent(2, 0.0152143);
 Error_dd_Slope->SetBinError(2, 0.0);
 Error_dd_Slope->SetBinContent(3, 0.018863);
 Error_dd_Slope->SetBinError(3, 0.0);
 Error_dd_Slope->SetBinContent(4, 0.017056);
 Error_dd_Slope->SetBinError(4, 0.0);

 Fitted_stw->SetBinContent(1, 0.232232);
 Fitted_stw->SetBinError(1, 0.00253987);
 Fitted_stw->SetBinContent(2, 0.231525);
 Fitted_stw->SetBinError(2, 0.0004812);
 Fitted_stw->SetBinContent(3, 0.231461);
 Fitted_stw->SetBinError(3, 0.000322577);
 Fitted_stw->SetBinContent(4, 0.231252);
 Fitted_stw->SetBinError(4, 0.00041968);

 Input_stw->SetBinContent(1, 0.2315);
 Input_stw->SetBinError(1, 0.0);
 Input_stw->SetBinContent(2, 0.2315);
 Input_stw->SetBinError(2, 0.0);
 Input_stw->SetBinContent(3, 0.2315);
 Input_stw->SetBinError(3, 0.0);
 Input_stw->SetBinContent(4, 0.2315);
 Input_stw->SetBinError(4, 0.0);

 file->Write();
 file->Close();
*/

// for(int i = 0; i < 40; i++){
//   cout<<32+0.25*i<<"_dp, ";
//   cout<<-5+i*0.25<<"_dp, ";
// }

/* cout<<ResBosRandom(40000)<<endl;
 cout<<ResBosRandom(40000)<<endl;
 cout<<ResBosRandom(40010)<<endl;
 cout<<ResBosRandom(40020)<<endl;
 cout<<ResBosRandom(40030)<<endl;
*/

/* cout<<"p-Value = "<<2.87e-7<<" Z = "<<TranslatePValueToZ(2.87e-7)<<endl;
 cout<<"p-Value = "<<0.05<<" Z = "<<TranslatePValueToZ(0.05)<<endl;
 cout<<"p-Value = "<<0.025<<" Z = "<<TranslatePValueToZ(0.025)<<endl;
 cout<<"p-Value = "<<0.32<<" Z = "<<TranslatePValueToZ(0.32)<<endl;
 cout<<"p-Value = "<<0.16<<" Z = "<<TranslatePValueToZ(0.16)<<endl;

 std::string myString = " test";
 std::string myString1 = trim(myString);
 cout<<myString<<"|"<<myString1<<endl;

 TH1D* Linear = new TH1D("Linear", "Linear", 5, -0.5, 4.5);
 Linear->SetBinContent(1, 5); Linear->SetBinError(1,  0.1 * 10);
 Linear->SetBinContent(2, 7); Linear->SetBinError(2,  0.2 * 10);
 Linear->SetBinContent(3, 11); Linear->SetBinError(3, 0.1 * 10);
 Linear->SetBinContent(4, 12); Linear->SetBinError(4, 0.2 * 10);
 Linear->SetBinContent(5, 14); Linear->SetBinError(5, 0.1 * 10);

 double* Par;
 double* ParErr;
 TF1* Fit;
 LinearFitting(Linear, Fit, Par, ParErr);
*/

/* vector<double> X2 = {1.0, 2.0};
 vector<double> Y2 = {2.0, 2.0};
 vector<double> X3 = {1.0, 2.0, 3.0};
 vector<double> Y3 = {2.0, 8.0, 18.0};
 vector<double> X4 = {127.5, 175, 550};
 vector<double> Y4 = {2.01045363151E+01, 5.83691964125E+00, 2.35990877551E-01};

 Interpolation* interp = new Interpolation();

 cout<<"2interp: "<<0.9<<" "<<interp->Polint(X2, Y2, 0.9)<<endl;
 cout<<"2interp: "<<1.2<<" "<<interp->Polint(X2, Y2, 1.2)<<endl;
 cout<<"2interp: "<<1.4<<" "<<interp->Polint(X2, Y2, 1.4)<<endl;
 cout<<"2interp: "<<1.6<<" "<<interp->Polint(X2, Y2, 1.6)<<endl;
 cout<<"2interp: "<<1.8<<" "<<interp->Polint(X2, Y2, 1.8)<<endl;
 cout<<"2interp: "<<2.0<<" "<<interp->Polint(X2, Y2, 2.0)<<endl;
 cout<<"2interp: "<<2.1<<" "<<interp->Polint(X2, Y2, 2.1)<<endl;

 cout<<"3interp: "<<0.9<<" "<<interp->Polint(X3, Y3, 0.9)<<endl;
 cout<<"3interp: "<<1.2<<" "<<interp->Polint(X3, Y3, 1.2)<<endl;
 cout<<"3interp: "<<1.4<<" "<<interp->Polint(X3, Y3, 1.4)<<endl;
 cout<<"3interp: "<<1.6<<" "<<interp->Polint(X3, Y3, 1.6)<<endl;
 cout<<"3interp: "<<1.8<<" "<<interp->Polint(X3, Y3, 1.8)<<endl;
 cout<<"3interp: "<<2.0<<" "<<interp->Polint(X3, Y3, 2.0)<<endl;
 cout<<"3interp: "<<2.2<<" "<<interp->Polint(X3, Y3, 2.2)<<endl;
 cout<<"3interp: "<<2.4<<" "<<interp->Polint(X3, Y3, 2.4)<<endl;
 cout<<"3interp: "<<2.6<<" "<<interp->Polint(X3, Y3, 2.6)<<endl;
 cout<<"3interp: "<<2.8<<" "<<interp->Polint(X3, Y3, 2.8)<<endl;
 cout<<"3interp: "<<3.0<<" "<<interp->Polint(X3, Y3, 3.0)<<endl;
 cout<<"3interp: "<<3.1<<" "<<interp->Polint(X3, Y3, 3.1)<<endl;

 cout<<"3interp: "<<127.5<<" "<<interp->Polint(X4, Y4, 127.5)<<endl;
 cout<<"3interp: "<<130.0<<" "<<interp->Polint(X4, Y4, 130.0)<<endl;
 cout<<"3interp: "<<175.0<<" "<<interp->Polint(X4, Y4, 175.0)<<endl;
 cout<<"3interp: "<<176.0<<" "<<interp->Polint(X4, Y4, 176.0)<<endl;
 cout<<"3interp: "<<200.0<<" "<<interp->Polint(X4, Y4, 200.0)<<endl;
 cout<<"3interp: "<<550.0<<" "<<interp->Polint(X4, Y4, 550.0)<<endl;
*/

/* cout<<"Position: "<<0.9<<" "<<interp->Locate(X3, 0.9)<<endl;
 cout<<"Position: "<<1.2<<" "<<interp->Locate(X3, 1.2)<<endl;
 cout<<"Position: "<<1.4<<" "<<interp->Locate(X3, 1.4)<<endl;
 cout<<"Position: "<<1.6<<" "<<interp->Locate(X3, 1.6)<<endl;
 cout<<"Position: "<<1.8<<" "<<interp->Locate(X3, 1.8)<<endl;
 cout<<"Position: "<<2.0<<" "<<interp->Locate(X3, 2.0)<<endl;
 cout<<"Position: "<<2.2<<" "<<interp->Locate(X3, 2.2)<<endl;
 cout<<"Position: "<<2.4<<" "<<interp->Locate(X3, 2.4)<<endl;
 cout<<"Position: "<<2.6<<" "<<interp->Locate(X3, 2.6)<<endl;
 cout<<"Position: "<<2.8<<" "<<interp->Locate(X3, 2.8)<<endl;
*/

/* int ATLAS8TeVZPtBin3 = 43;
 double ATLAS8TeVZPtBinning3[44] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.5, 25.0, 27.5, 30.0, 33.0,
                                 36.0, 39.0, 42.0, 45.0, 48.0, 51.0, 54.0, 57.0, 61.0, 65.0, 70.0, 75.0, 80.0, 85.0, 95.0, 105.0,
                                 125.0, 150.0, 175.0, 200.0, 250.0, 300.0, 350.0, 400.0, 470.0, 550.0, 650.0, 900.0};

 vector<double> CT18Data;
 vector<double> newCT18Data;

 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();
 TH1D* ZPt_CT18 = new TH1D("ZPt_CT18", "ZPt_CT18", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);
 TH1D* ZPt_newCT18 = new TH1D("ZPt_newCT18", "ZPt_newCT18", ATLAS8TeVZPtBin3, ATLAS8TeVZPtBinning3);

 double Value = 0.0;

 ifstream infile;
  infile.open("zpt+ct18.txt");
 while(infile >> Value){
   infile >> Value;
   CT18Data.push_back(Value);
   infile >> Value;
   newCT18Data.push_back(Value);
 }

 for(int ibin = 1; ibin <= ZPt_CT18->GetNbinsX(); ibin++){
   ZPt_CT18->SetBinContent(ibin, CT18Data.at(ibin - 1));
   ZPt_CT18->SetBinError(ibin, 0.0);
   ZPt_newCT18->SetBinContent(ibin, newCT18Data.at(ibin - 1));
   ZPt_newCT18->SetBinError(ibin, 0.0);
 }

 file->Write();
 file->Close();
*/

// vector<double> A = {0.225, 0.262, 0.217, 0.240, 0.230, 0.229, 0.235, 0.217};
// vector<double> B = {0.209, 0.205, 0.196, 0.210, 0.202, 0.207, 0.224, 0.223, 0.220, 0.201};

// cout<<CalculateMean(A)<<" "<<CalculateRMS(A)<<endl;
// cout<<CalculateMean(B)<<" "<<CalculateRMS(B)<<endl;

/*
 vector<double> CT18Data;

 int CMS13TeVyZBin = 12;
 double CMS13TeVyZBinning[13] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4};

 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();
 TH1D* ZY_CT18 = new TH1D("ZY_CT18", "ZY_CT18", CMS13TeVyZBin, CMS13TeVyZBinning);

 double Value = 0.0;

 string FileLine;
 ifstream infile;
  infile.open("Z_only_nnlo_CT18NNLO_1.00_1.00_1.0E-4_CMS13Z_y34.txt");

 for(int i = 0; i < 5; i++){
   getline(infile, FileLine);
 }

 while(infile >> Value){
   infile >> Value;
   infile >> Value;
   CT18Data.push_back(Value);
   infile >> Value;
 }

 for(int ibin = 1; ibin <= ZY_CT18->GetNbinsX(); ibin++){
   ZY_CT18->SetBinContent(ibin, CT18Data.at(ibin - 1) / 0.2 / 1000.0);
   ZY_CT18->SetBinError(ibin, 0.0);
 }

 file->Write();
 file->Close();
*/

/* TFile* file = new TFile("TryEllipse.root", "RECREATE");
 TGraph* f = GenerateEllipse(10, 3, 10, 3, 0.7);
 file->cd();
 f->Write("Ellipse");
 file->Close();
*/

// TryStatic(true);
// TryStatic2(true);
// TryStatic(false);
// TryStatic2(false);

/* map<int, double> LeptonPtTrig;
 LeptonPtTrig[1] = 1.0;
 LeptonPtTrig[1] = 50.0;
 LeptonPtTrig[0] = 10.0;

 auto LeptonPtTrigIter = LeptonPtTrig.end();
 cout<<((--LeptonPtTrigIter)->second)<<" "<<((LeptonPtTrigIter)->first)<<endl;
*/

/* int A[10] = {0};
 A[0] = 1;
 A[1] = 2;
 A[2] = 3;
 A[3] = 4;
 A[4] = 5;

 TryPointer(A);

 for(int i = 0; i < 10; i++){
   cout<<A[i]<<endl;
 }
*/

/* int nMassPoints = 10;
 double pelimit = 0;
 vector<double> vecLimit[nMassPoints];

 TFile* pefile = new TFile("/msu/data/t3work5/yfu/LimitSetting/output/TEST/Expected/zprime_ensembles_mass0_run0_mm.root");

 TTree* petree = (TTree*)pefile->Get("ensemble_test");

 string branchname = "95quantile_marginalized_2";   // 0.Neebkg; 1.Nmmbkg; 2.signal

 TBranch* b_marg = petree->GetBranch(branchname.c_str());
 TObjArray* objarr_leaves = b_marg->GetListOfLeaves();
 TLeaf* l_marg = b_marg->GetLeaf(objarr_leaves->At(0)->GetName());

 for (int j=0; j < nMassPoints; j++) {

   for (int i=0; i < petree->GetEntries(); i++) {
     petree->GetEntry(i);
     pelimit = l_marg->GetValue();
     vecLimit[j].push_back(pelimit);
     cout<<"j: "<<j<<" i: "<<i<<" "<<pelimit<<endl;
   }
 }
*/

/*
 vector<vector<double>> Matrix;
 vector<vector<double>> InverseMatrix;
 vector<vector<double>> InverseMatrix2;

 vector<double> Beta(2);
 vector<double> Sigma(2);

 Matrix.resize(2);
 InverseMatrix.resize(2);
 InverseMatrix2.resize(2);
 for(int i = 0; i < 2; i++){
   Matrix.at(i).resize(2);
   InverseMatrix.at(i).resize(2);
   InverseMatrix2.at(i).resize(2);
 }

 Matrix[0][0] = 0.0360812 * 0.0360812;
 Matrix[0][1] = 0.0360812 * 0.0664527 * (-0.957);
 Matrix[1][0] = 0.0360812 * 0.0664527 * (-0.957);
 Matrix[1][1] = 0.0664527 * 0.0664527;


 Matrix[0][0] = 2.59784E+00;
 Matrix[0][1] = 1.13716E+00;
 Matrix[1][0] = 1.13716E+00;
 Matrix[1][1] = 2.22104E+00;

 Beta[0] = -3.86020E-02;
 Beta[1] = -3.45577E-02;

 Sigma[0] = 3.24731E-02;
 Sigma[1] = 5.98074E-02;

 CalculateInverseMatrix(Matrix, InverseMatrix);
 Cholesky(Matrix, InverseMatrix2, 2);

 double Value = 1.0 / Sigma[0] / Sigma[0];
 for(int i = 0; i < Matrix.size(); i++){
   for(int j = 0; j < Matrix.size(); j++){
     Value -= Beta[i] * InverseMatrix[i][j] * Beta[j] / Sigma[0] / Sigma[0] / Sigma[0] / Sigma[0];
   }
 }

 cout<<"Result: "<<Value<<endl;

 cout<<"Inverse Matrix:"<<endl;
 for(int i = 0; i < Matrix.size(); i++){
   for(int j = 0; j < Matrix.size(); j++){
     cout<<InverseMatrix.at(i).at(j)<<"  ";
   }
   cout<<endl;
 }

 cout<<"Cholesky:"<<endl;
 for(int i = 0; i < Matrix.size(); i++){
   for(int j = 0; j < Matrix.size(); j++){
     cout<<InverseMatrix2.at(i).at(j)<<"  ";
   }
   cout<<endl;
 }
*/

/*
 TFile* file = new TFile("parabola.root", "RECREATE");
 file->cd();

 TF1* f1 = new TF1("f1", "[0]*x*x+[1]*x+[2]", -1, 1);
 f1->SetParameter(0, 100.0);
 f1->SetParameter(1, 0.0);
 f1->SetParameter(2, 0.0);

 TF1* f2 = new TF1("f2", "[0]*x*x+[1]*x+[2]", -1, 1);
 f2->SetParameter(0, 400.0);
 f2->SetParameter(1, 0.0);
 f2->SetParameter(2, 0.0);

 double a = 400.0;
 double b = -5.0 * 2 * 20.0 / 4.0 * 3.0;
 double c = 25.0 / 4.0 * 3.0;

 TF1* f3 = new TF1("f3", "[0]*x*x+[1]*x+[2]", -1, 1);
 f3->SetParameter(0, a);
 f3->SetParameter(1, b);
 f3->SetParameter(2, c);

 double solution1 = (-1.0 * b + sqrt(b * b - 4.0 * a * (c - 100.0))) / (2.0 * a);
 double solution2 = (-1.0 * b - sqrt(b * b - 4.0 * a * (c - 100.0))) / (2.0 * a);

 cout<<-1 * b / 2.0 / a<<"  "<<c - b * b / 4.0 / a<<"  "<<solution1<<"  "<<solution2<<endl;

 f1->Write();
 f2->Write();
 f3->Write();

 file->Close();
*/

// double data1 = 10.0, data2 = 5.0;
// double delta1 = 1.0, delta2 = 0.5;

/* double data1 = stod(argv[1]);
 double data2 = stod(argv[2]);
 double delta1 = stod(argv[3]);
 double delta2 = stod(argv[4]);

 double combine1 = data1 + data2;
 double error1 = sqrt(delta1 * delta1 + delta2 * delta2);

 double combine2 = (data1 / delta1 / delta1 + data2 / delta2 / delta2) / (1.0 / delta1 / delta1 + 1.0 / delta2 / delta2);
 double error2 = 1.0 / sqrt(1.0 / delta1 / delta1 + 1.0 / delta2 / delta2);

 double sensitivity1 = (data1 + data2) * (data1 + data2) / (delta1 * delta1 + delta2 * delta2);
 double sensitivity2 = data1 * data1 / delta1 / delta1 + data2 * data2 / delta2 / delta2;

 cout<<"Delta: "<<sensitivity1<<"  Independent combine: "<<sensitivity2<<endl;
*/

/* TFile* Theory = new TFile("i2Tn3.00/MC_results.root");
 TFile* PDFUnc = new TFile("PDFUnc_Symmetry.root");

 TFile* writefile = new TFile("ChangeP0.root", "RECREATE");
 writefile->cd();

 TH1D* AFB_uu = (TH1D *)Theory->Get("AFB_Full_uu");
 TH1D* AFB_dd = (TH1D *)Theory->Get("AFB_Full_dd");

 TH1D* Delta_uu = (TH1D *)Theory->Get("CoefficientZMass_Full_uu_wrong_Residual");
 TH1D* Delta_dd = (TH1D *)Theory->Get("CoefficientZMass_Full_dd_wrong_Residual");

 TH1D* P0_uu = (TH1D *)PDFUnc->Get("CoefficientZMass_Full_uu_wrong_Average_PDFCentral");
 TH1D* P0_dd = (TH1D *)PDFUnc->Get("CoefficientZMass_Full_dd_wrong_Average_PDFCentral");

 double P0_uu_Central = P0_uu->GetBinContent(1);
 double P0_uu_1Up = P0_uu->GetBinContent(1) + P0_uu->GetBinError(1);
 double P0_uu_1Down = P0_uu->GetBinContent(1) - P0_uu->GetBinError(1);

 double P0_dd_Central = P0_dd->GetBinContent(1);
 double P0_dd_1Up = P0_dd->GetBinContent(1) + P0_dd->GetBinError(1);
 double P0_dd_1Down = P0_dd->GetBinContent(1) - P0_dd->GetBinError(1);

 TH1D* AFB_Central = (TH1D *)AFB_uu->Clone("AFB_Central");
 TH1D* AFB_P0u_1Up = (TH1D *)AFB_uu->Clone("AFB_P0u_1Up");
 TH1D* AFB_P0u_1Down = (TH1D *)AFB_uu->Clone("AFB_P0u_1Down");
 TH1D* AFB_P0d_1Up = (TH1D *)AFB_uu->Clone("AFB_P0d_1Up");
 TH1D* AFB_P0d_1Down = (TH1D *)AFB_uu->Clone("AFB_P0d_1Down");

 GetHadronAFB(AFB_uu, AFB_dd, Delta_uu, Delta_dd, P0_uu_Central, P0_dd_Central, AFB_Central);
 GetHadronAFB(AFB_uu, AFB_dd, Delta_uu, Delta_dd, P0_uu_1Up, P0_dd_Central, AFB_P0u_1Up);
 GetHadronAFB(AFB_uu, AFB_dd, Delta_uu, Delta_dd, P0_uu_1Down, P0_dd_Central, AFB_P0u_1Down);
 GetHadronAFB(AFB_uu, AFB_dd, Delta_uu, Delta_dd, P0_uu_Central, P0_dd_1Up, AFB_P0d_1Up);
 GetHadronAFB(AFB_uu, AFB_dd, Delta_uu, Delta_dd, P0_uu_Central, P0_dd_1Down, AFB_P0d_1Down);

 writefile->cd();

 AFB_Central->Write();
 AFB_P0u_1Up->Write();
 AFB_P0u_1Down->Write();
 AFB_P0d_1Up->Write();
 AFB_P0d_1Down->Write();

 writefile->Close();
*/

/* TFile* writefile = new TFile("WZFraction.root", "RECREATE");
 writefile->cd();

 vector<double> Binning = {0.0, 200.0, 400.0, 600.0, 800.0, 1000.0, 1500.0};
 TH1D* SM_00 = new TH1D("SM_00", "SM_00", Binning.size() - 1, &Binning[0]);
 TH1D* SM_0T = new TH1D("SM_0T", "SM_0T", Binning.size() - 1, &Binning[0]);
 TH1D* SM_TT = new TH1D("SM_TT", "SM_TT", Binning.size() - 1, &Binning[0]);
 TH1D* NP_00 = new TH1D("NP_00", "NP_00", Binning.size() - 1, &Binning[0]);
 TH1D* NP_0T = new TH1D("NP_0T", "NP_0T", Binning.size() - 1, &Binning[0]);
 TH1D* NP_TT = new TH1D("NP_TT", "NP_TT", Binning.size() - 1, &Binning[0]);

 double Lambda = 1.0;

 double Fraction_SM_00[6];
 double Fraction_SM_0T[6];
 double Fraction_SM_TT[6];

 double Fraction_NP_00[6];
 double Fraction_NP_0T[6];
 double Fraction_NP_TT[6];

 Fraction_SM_00[0] = 784.0  ;
 Fraction_SM_00[1] = 58.5   ;
 Fraction_SM_00[2] = 4.84   ;
 Fraction_SM_00[3] = 0.799  ;
 Fraction_SM_00[4] = 0.188  ;
 Fraction_SM_00[5] = 0.0749 ;

 Fraction_SM_0T[0] = 1614.0 ;
 Fraction_SM_0T[1] = 23.0   ;
 Fraction_SM_0T[2] = 0.598  ;
 Fraction_SM_0T[3] = 0.0471 ;
 Fraction_SM_0T[4] = 0.00634;
 Fraction_SM_0T[5] = 0.00149;

 Fraction_SM_TT[0] = 5755.0 ;
 Fraction_SM_TT[1] = 164.0  ;
 Fraction_SM_TT[2] = 12.0   ;
 Fraction_SM_TT[3] = 1.74   ;
 Fraction_SM_TT[4] = 0.357  ;
 Fraction_SM_TT[5] = 0.121  ;

 Fraction_NP_00[0] = 784.0  * (1.0 + 0.116 / Lambda / Lambda + 0.00625 / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_00[1] = 58.5   * (1.0 + 0.682 / Lambda / Lambda + 0.141   / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_00[2] = 4.84   * (1.0 + 2.09  / Lambda / Lambda + 1.24    / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_00[3] = 0.799  * (1.0 + 4.30  / Lambda / Lambda + 4.87    / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_00[4] = 0.188  * (1.0 + 6.92  / Lambda / Lambda + 13.4    / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_00[5] = 0.0749 * (1.0 + 11.9  / Lambda / Lambda + 39.1    / Lambda / Lambda / Lambda / Lambda);

 Fraction_NP_0T[0] = 1614.0   * (1.0 + 0.0610 / Lambda / Lambda + 0.00181  / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_0T[1] = 23.0     * (1.0 + 0.419  / Lambda / Lambda + 0.0611   / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_0T[2] = 0.598    * (1.0 + 1.40   / Lambda / Lambda + 0.623    / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_0T[3] = 0.0471   * (1.0 + 2.91   / Lambda / Lambda + 2.60     / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_0T[4] = 0.00634  * (1.0 + 4.89   / Lambda / Lambda + 7.34     / Lambda / Lambda / Lambda / Lambda);
 Fraction_NP_0T[5] = 0.00149  * (1.0 + 8.01   / Lambda / Lambda + 20.6     / Lambda / Lambda / Lambda / Lambda);

 Fraction_NP_TT[0] = 5755.0 ;
 Fraction_NP_TT[1] = 164.0  ;
 Fraction_NP_TT[2] = 12.0   ;
 Fraction_NP_TT[3] = 1.74   ;
 Fraction_NP_TT[4] = 0.357  ;
 Fraction_NP_TT[5] = 0.121  ;

 for(int i = 1; i <= Binning.size() - 1; i++){
   SM_00->SetBinContent(i, Fraction_SM_00[i - 1] / (Fraction_SM_00[i - 1] + Fraction_SM_0T[i - 1] + Fraction_SM_TT[i - 1]));
   SM_0T->SetBinContent(i, Fraction_SM_0T[i - 1] / (Fraction_SM_00[i - 1] + Fraction_SM_0T[i - 1] + Fraction_SM_TT[i - 1]));
   SM_TT->SetBinContent(i, Fraction_SM_TT[i - 1] / (Fraction_SM_00[i - 1] + Fraction_SM_0T[i - 1] + Fraction_SM_TT[i - 1]));
   NP_00->SetBinContent(i, Fraction_NP_00[i - 1] / (Fraction_NP_00[i - 1] + Fraction_NP_0T[i - 1] + Fraction_NP_TT[i - 1]));
   NP_0T->SetBinContent(i, Fraction_NP_0T[i - 1] / (Fraction_NP_00[i - 1] + Fraction_NP_0T[i - 1] + Fraction_NP_TT[i - 1]));
   NP_TT->SetBinContent(i, Fraction_NP_TT[i - 1] / (Fraction_NP_00[i - 1] + Fraction_NP_0T[i - 1] + Fraction_NP_TT[i - 1]));
 }

 writefile->Write();
 writefile->Close();
*/

/* vector<double> Binning = {0.0, 0.142, 0.222, 0.4, 0.56, 1.0, 1.23, 1.5, 2.0, 5.1, 10.0, 12.2, 15.567, 18.88888};

 TH1D* h1 = new TH1D("h1", "h1", Binning.size() - 1, &Binning[0]);

 LatexOutput* output = new LatexOutput();
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   cout<<h1->GetXaxis()->GetBinLowEdge(ibin)<<"  "<<output->GetNDigit(h1->GetXaxis()->GetBinLowEdge(ibin))<<endl;
 }
 cout<<h1->GetXaxis()->GetBinUpEdge(h1->GetNbinsX())<<"  "<<output->GetNDigit(h1->GetXaxis()->GetBinUpEdge(h1->GetNbinsX()))<<endl;
*/

// for(int i = 0; i < 80; i++){
//   cout<<fixed<<setprecision(1)<<-4.0 + 0.1 * i<<" ";
// }

// map<tuple<double, double>, int> TestTuple;
// TestTuple[make_tuple(1.0, 10.0)] = 1;
// TestTuple[make_tuple(1.3, 100.0)] = 2;

// cout<<TestTuple[make_tuple(1.0, 0.0)]<<" "<<TestTuple[make_tuple(1.0, 10.0)]<<" "<<TestTuple[make_tuple(1.3, 100.0)]<<endl;

// vector<double> Binning = Logspace(1e-5, 1.0, 5000, 10.0);
// cout<<Binning.at(4998)<<"  "<<Binning.at(4999)<<endl;

/* vector<double> x;
 x.push_back(1);
 x.push_back(2);
 x.push_back(3);
 x.resize(10);
 for(int i = 0; i < x.size(); i++){
   cout<<x.at(i)<<endl;
 }
*/

/*
 TFile* file = new TFile("g5term.root", "RECREATE");
 file->cd();

 TF1* f1 = new TF1("f1", "13.45*(tanh(1.468*5.0)+tanh(1.468*(x-5.0)))", 0, 5);
 TF1* f2 = new TF1("f2", "1.034", 0, 5);

 f1->Write();
 f2->Write();

 file->Write();
 file->Close();
*/
// for(int i = 2147483248; i < 274877906944; i++){
//   cout<<i<<endl;
// }

/* vector<int> BineryNum(22);
 for(int i = 0; i < 4194304; i++){
   BineryNum.at(0) = i / (int)pow(2, 21);
   BineryNum.at(1) = i % (int)pow(2, 21) / (int)pow(2, 20);
   BineryNum.at(2) = i % (int)pow(2, 20) / (int)pow(2, 19);
   BineryNum.at(3) = i % (int)pow(2, 19) / (int)pow(2, 18);
   BineryNum.at(4) = i % (int)pow(2, 18) / (int)pow(2, 17);
   BineryNum.at(5) = i % (int)pow(2, 17) / (int)pow(2, 16);
   BineryNum.at(6) = i % (int)pow(2, 16) / (int)pow(2, 15);
   BineryNum.at(7) = i % (int)pow(2, 15) / (int)pow(2, 14);
   BineryNum.at(8) = i % (int)pow(2, 14) / (int)pow(2, 13);
   BineryNum.at(9) = i % (int)pow(2, 13) / (int)pow(2, 12);
   BineryNum.at(10) = i % (int)pow(2, 12) / (int)pow(2, 11);
   BineryNum.at(11) = i % (int)pow(2, 11) / (int)pow(2, 10);
   BineryNum.at(12) = i % (int)pow(2, 10) / (int)pow(2, 9);
   BineryNum.at(13) = i % (int)pow(2, 9) / (int)pow(2, 8);
   BineryNum.at(14) = i % (int)pow(2, 8) / (int)pow(2, 7);
   BineryNum.at(15) = i % (int)pow(2, 7) / (int)pow(2, 6);
   BineryNum.at(16) = i % (int)pow(2, 6) / (int)pow(2, 5);
   BineryNum.at(17) = i % (int)pow(2, 5) / (int)pow(2, 4);
   BineryNum.at(18) = i % (int)pow(2, 4) / (int)pow(2, 3);
   BineryNum.at(19) = i % (int)pow(2, 3) / (int)pow(2, 2);
   BineryNum.at(20) = i % (int)pow(2, 2) / (int)pow(2, 1);
   BineryNum.at(21) = i % (int)pow(2, 1);

   cout<<i<<": ";
   for(int j = 0; j < 22; j++){
     cout<<BineryNum.at(j);
   }
   cout<<endl;
   BineryNum.clear();
   BineryNum.resize(22);
 }
*/

/* map<double, vector<int>> FourCombination;
 FourCombination[1.0] = vector<int>{0, 0, 0, 0};
 FourCombination[10.0] = vector<int>{0, 0, 0, 1};
 FourCombination[5.0] = vector<int>{0, 0, 1, 0};
 FourCombination[3.0] = vector<int>{0, 1, 0, 0};
 FourCombination[20.0] = vector<int>{1, 0, 0, 0};

 for(auto iter = FourCombination.begin(); iter != FourCombination.end(); iter++){
   cout<<iter->first<<" ";
   for(int i = 0; i < 4; i++){
     cout<<iter->second.at(i);
   }
   cout<<endl;
 }
*/

/*
 double T2 = 100.0;
 double lambda = 10.0;

 TFile* file = new TFile("parabola.root", "RECREATE");
 file->cd();

 TF1* f1 = new TF1("f1", "[0]*x*x+[1]*x+[2]", -1, 1);
 f1->SetParameter(0, 100.0);
 f1->SetParameter(1, 0.0);
 f1->SetParameter(2, 0.0);

 TF1* f2 = new TF1("f2", "[0]*x*x+[1]*x+[2]", -1, 1);
 f2->SetParameter(0, 100.0);
 f2->SetParameter(1, 10 * 20.0);
 f2->SetParameter(2, 10 * 100.0);

 TF1* f3 = new TF1("f3", "[0]*x*x+[1]*x+[2]", -1, 1);
 f3->SetParameter(0, 100.0);
 f3->SetParameter(1, 5 * 20.0);
 f3->SetParameter(2, 5 * 100.0);

 TF1* f4 = new TF1("f4", "[0]*x*x+[1]*x+[2]", -1, 1);
 f4->SetParameter(0, 100.0);
 f4->SetParameter(1, 1 * 20.0);
 f4->SetParameter(2, 1 * 100.0);

 TF1* f5 = new TF1("f5", "[0]*x*x+[1]*x+[2]", -1, 1);
 f5->SetParameter(0, 100.0);
 f5->SetParameter(1, -5 * 20.0);
 f5->SetParameter(2, -5 * 100.0);

 TF1* f6 = new TF1("f6", "[0]*x*x+[1]*x+[2]", -1, 1);
 f6->SetParameter(0, 100.0);
 f6->SetParameter(1, -10 * 20.0);
 f6->SetParameter(2, -10 * 100.0);

 f1->Write();
 f2->Write();
 f3->Write();
 f4->Write();
 f5->Write();
 f6->Write();
*/

/* SimpleIntegral* run = new SimpleIntegral();
 run->InputFormula("gaus(0)");
 run->SetParameters(1.0 / sqrt(2.0 * M_PI), 0, 1);

 function<double(double)> f = bind(&SimpleIntegral::Gaus, run, _1);
 function<double(double, double)> f1 = bind(&SimpleIntegral::GausPlus, run, _1, _2);
 auto f2 = bind(&SimpleIntegral::GausPlus, run, _1, 1.0);
 auto f3 = bind(&SimpleIntegral::GausPlus, run, _1, 2.0);
 auto f4 = bind(&SimpleIntegral::GausPlus2, run, _1, 2.0, 3.0);

 cout<<Simpson(f, -1, 1, 10000, -1, true)<<endl;
 cout<<Simpson(f1, -1, 1, 1.0, 10000, -1, true)<<endl;
 cout<<Simpson(f2, -1, 1, 10000, -1, true)<<endl;
 cout<<Simpson(f3, -1, 1, 10000, -1, true)<<endl;
 cout<<Simpson(f4, -1, 1, 10000, -1, true)<<endl;

 cout<<f2(0.0)<<endl;

 cout<<run->GetIntegral(-1, 1)<<endl;
*/


/* TGraph* g = new TGraph(10);
 g->SetPointX(1, 1.3315E-01);
 g->SetPointY(1, 1567.4315);
 g->SetPointX(2, 1.2978E-01);
 g->SetPointY(2, 1003.1562);
 g->SetPointX(3, 1.2641E-01);
 g->SetPointY(3, 564.2753);
 g->SetPointX(4, 1.2304E-01);
 g->SetPointY(4, 250.7890);
 g->SetPointX(5, 1.1967E-01);
 g->SetPointY(5, 62.6973);
 g->SetPointX(6, 1.1630E-01);
 g->SetPointY(6, 0.0);
 g->SetPointX(7, 1.1293E-01);
 g->SetPointY(7, 62.6973);
 g->SetPointX(8, 1.0956E-01);
 g->SetPointY(8, 250.7890);
 g->SetPointX(9, 1.0619E-01);
 g->SetPointY(9, 564.2753);
 g->SetPointX(10, 1.0282E-01);
 g->SetPointY(10, 1003.1562);
*/
/*
 string origin = "*this is a string.";
 string str = origin.substr(origin.find_first_not_of(" \t\n\r\f\v"), 1);
 string str2 = origin.substr(0, 5);
 string str3 = origin.substr(3, 10);
 string str4 = origin.substr(2);

 string origin2 = "     *this is another string.";
 string str5 = origin2.substr(origin2.find_first_not_of(" \t\n\r\f\v"), 1);

 cout<<str<<endl;
 cout<<str2<<endl;
 cout<<str3<<endl;
 cout<<str4<<endl;
 cout<<str5<<endl;
 cout<<origin2<<origin2.find_first_not_of(" \t\n\r\f\v")<<endl;

 string origin3 = "   0.15    3     38.8";
 stringstream s(origin3);
 double ErrNorm;
 s >> ErrNorm;
 int Ncorr;
 s >> Ncorr;

 cout<<ErrNorm<<"| |"<<Ncorr<<endl;

// string origin4 = "-0.100  7.10    1.831E-01 2.450E+00  5.767E-01  0.0  0.0  15.0  1.48500    1.29031";
 string origin4 = "";

 stringstream line(origin4);
 vector<double> vec;
 double value;
 while(line >> value){
   vec.push_back(value);
 }
 for(int i = 0; i < vec.size(); i++){
   cout<<vec.at(i)<<"   ";
 }
 cout<<endl;
 cout<<vec.size()<<endl;
*/

// ResBosEW* ew = new ResBosEW();
// cout<<"ResBos1: "<<ew->pyalem(7.1*7.1)<<endl;
// cout<<"ResBos2: "<<ew->GetAlphaEM(7.1*7.1)<<endl;

// TestPointer* test = new TestPointer();
// test->Initialize();
// test->Test();

/* TFile* file = new TFile("LJSkim_v6.0_file_Run3_data_merged.root");
 TDirectoryFile* dir = (TDirectoryFile *)file->Get("LJAlgo");
 TTree* tree = (TTree *)dir->Get("nominal");
 TTree* tree2 = (TTree *)file->Get("LJAlgo/nominal");

 TFile* file1 = new TFile("LJSkim_v6.0_file_Run3_data_merged.root");
 TFile* file2 = new TFile("LJSkim_v6.0_file_Run3_data_merged.root");
 TFile* file3 = new TFile("LJSkim_v6.0_file_Run3_data_merged.root");
 TFile* file4 = new TFile("LJSkim_v6.0_file_Run3_data_merged.root");

 TTree* tree3 = (TTree *)file1->Get("LJAlgo/nominal");
 TTree* tree4 = (TTree *)file2->Get("LJAlgo/nominal");
 TTree* tree5 = (TTree *)file3->Get("LJAlgo/nominal");
 TTree* tree6 = (TTree *)file4->Get("LJAlgo/nominal");

 cout<<"file:"<<endl;
 cout<<file<<endl;
 cout<<file1<<endl;
 cout<<file2<<endl;
 cout<<file3<<endl;
 cout<<file4<<endl;

 cout<<"tree:"<<endl;
 cout<<tree<<endl;
 cout<<tree->GetCurrentFile()<<endl;
 cout<<tree2<<endl;
 cout<<tree2->GetCurrentFile()<<endl;
 cout<<tree3<<endl;
 cout<<tree4<<endl;
 cout<<tree5<<endl;
 cout<<tree6<<endl;
*/

/* ofstream outputfile;
 Logstream myLog;
 outputfile.open("save.log");
 myLog.Initial(cout, outputfile);

 Control process;
 process.LinkLog(myLog);
 process.ReadFile("cardfile.in");

 TreeDrawThread* run = new TreeDrawThread();
 run->InputFile(process.RootNames, "LJAlgo/nominal");
 run->DefineHist("ElFakeTight", "ElFakeTight", 5, 130, 500, 5, 0.0, 2.5);
 run->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");

 TString passTrig = "HLT_singleLep*HLT_singleJet*lepton_singleleptrigMatched";
 TString isEl = "(lepton1_isEl==1)";
 TString isMu = "(lepton1_isEl==0)";

 TString FakeCR = "(dphiLepJet>2.8)*(detaLepJet<3.25)*(metFinalTrkSignificance>3.5)*(n_signal_lep<1)";
 TString RealCR = "(dphiLepJet>2.8)*(detaLepJet<3.25)*(metFinalTrkSignificance>3.5)*lepton1_isSig*(n_signal_lep>0)";

 TString passTight = "lepton1_isIso";

 TString MCWeight = "mcEventWeight*beamSpotWeight*weight_gen*weight_lumi*weight_norm*weight_singleleptonTrigSF*weight_pileup*weight_lepton*(-1.0)";

 vector<TString> info;
 for(int i = 0; i < process.RootNames.size(); i++){
   if(process.RootNames.at(i).Contains("Run3_data")) info.push_back(passTrig + "*" + FakeCR + "*" + isEl + "*" + passTight);
   else info.push_back(MCWeight + "*" + passTrig + "*" + FakeCR + "*" + isEl + "*" + passTight);
 }
 run->InputWeightInfo(info);
 run->SubmitTreeDrawJobs();
 run->WaitTreeDrawJobs();
 run->GetFinalHist();

 TH2D* h2 = run->FinalHist2D;

 for(int ibinx = 1; ibinx <= h2->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= h2->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<h2->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<h2->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }
*/

 auto func = [&](double x){
   return 3.0 * x * x - exp(x);
 };

/* int irt;

 CTUtil* run = new CTUtil();
 CTUtil* run1 = run;
 CTUtil* run2 = run;

 cout<<run<<endl;
 cout<<run1<<endl;
 cout<<run2<<endl;

 delete run;
 cout<<"after delete run"<<endl;
 cout<<run<<endl;
 cout<<run1<<endl;
 cout<<run2<<endl;

 if(run == nullptr) cout<<"run is nullptr"<<endl;
 if(run1 == nullptr) cout<<"run1 is nullptr"<<endl;
 if(run2 == nullptr) cout<<"run2 is nullptr"<<endl;

 if(run1) cout<<"enter run1"<<endl;
 if(run2) cout<<"enter run2"<<endl;
*/

// double num = 0.001415926;
// TString str = TString::Format("%.5f", num);
// cout<<str<<endl;

// double solution = run->zbrnt(func, 0.0, 1.0, 0.00001, irt);
// cout<<solution<<endl;
// cout<<func(solution)<<endl;


/*
 TString skip;
 double number;
 vector<double> xsecs_pdf;
 vector<double> xsecs_alphas;

 ifstream infile("xsec_pdf.out");
 while(infile >> skip){
   infile >> skip;
   infile >> number;
   xsecs_pdf.push_back(number);
 }

 ifstream infile2("xsec_alphas.out");
 while(infile2 >> skip){
   infile2 >> skip;
   infile2 >> number;
   xsecs_alphas.push_back(number);
 }

 vector<TH1D *> Theory_PDF(xsecs_pdf.size());
 vector<TH1D *> Theory_AlphaS(xsecs_alphas.size());

 for(int i = 0; i < Theory_PDF.size(); i++){
   Theory_PDF.at(i) = new TH1D((TString)"xsec_pdf" + i, (TString)"xsec_pdf" + i, 1, 0, 1);
   Theory_PDF.at(i)->SetBinContent(1, xsecs_pdf.at(i));
   Theory_PDF.at(i)->SetBinError(1, xsecs_pdf.at(i) * 0.01);
 }
 for(int i = 0; i < Theory_AlphaS.size(); i++){
   Theory_AlphaS.at(i) = new TH1D((TString)"xsec_alphas" + i, (TString)"xsec_alphas" + i, 1, 0, 1);
   Theory_AlphaS.at(i)->SetBinContent(1, xsecs_alphas.at(i));
   Theory_AlphaS.at(i)->SetBinError(1, xsecs_alphas.at(i) * 0.01);
 }


 FileForEPUMP* run;

 run = new FileForEPUMP("ggHiggsXsec");
 run->InputData(Theory_PDF.at(0));
 run->InputTheory(Theory_PDF);
 run->writedata();
 run->writetheory();

 run = new FileForEPUMP("ggHiggsXsecAlphaS");
 run->InputData(Theory_AlphaS.at(0));
 run->InputTheory(Theory_AlphaS);
 run->writedata();
 run->writetheory();
*/

/*
 TString name;
 vector<TString> Theory;

 ifstream infile("theory.list");
 while(infile >> name){
   Theory.push_back(name);
 }

 FileForEPUMP* run;
 run = new FileForEPUMP("ZpT_as0118");
 run->InputTheory(Theory, "ATLAS8TeV_pT_Mass66_116_Theory_Final");
 run->writetheory(1, 18);
*/

/* TString skip;
 vector<TString> Cluster1;
 vector<TString> Cluster2;
 vector<TString> Mix;

 ifstream infile1("Cluster1.list");
 ifstream infile2("Cluster2.list");
 ifstream infile3("pairname.list");

 vector<sumReader *> Summary1;
 vector<sumReader *> Summary2;
 vector<sumReader *> SummaryMix;

 while(infile1 >> skip){
   Cluster1.push_back(skip);
 }
 while(infile2 >> skip){
   Cluster2.push_back(skip);
 }
 while(infile3 >> skip){
   Mix.push_back(skip);
 }

 Summary1.resize(Cluster1.size());
 Summary2.resize(Cluster2.size());
 SummaryMix.resize(Mix.size());

 for(int i = 0; i < Summary1.size(); i++){
   Summary1.at(i) = new sumReader();
   Summary1.at(i)->Initialize(Cluster1.at(i));
 }
 for(int i = 0; i < Summary2.size(); i++){
   Summary2.at(i) = new sumReader();
   Summary2.at(i)->Initialize(Cluster2.at(i));
 }
 for(int i = 0; i < SummaryMix.size(); i++){
   SummaryMix.at(i) = new sumReader();
   SummaryMix.at(i)->Initialize(Mix.at(i));
 }

 int count = 0;
 for(int i = 0; i < Summary1.size(); i++){
   for(int j = 0; j < Summary2.size(); j++){
     TString Name1 = Cluster1.at(i);
     TString Name2 = Cluster2.at(j);
     TString Name3 = Mix.at(count);

     Name1.ReplaceAll(".sum", "");
     Name2.ReplaceAll(".sum", "");
     Name3.ReplaceAll(".sum", "");

     cout<<"{"<<Name1<<", "<<Summary1.at(i)->Chi2F<<"}, {"<<Name2<<", "<<Summary2.at(j)->Chi2F<<"}, {"<<Name3<<", "<<SummaryMix.at(count)->Chi2F<<"}"<<endl;
     count++;
   }
 }

*/

/*
 TString GridName1 = "/mnt/home/fuyao3/FittingCode/ApplGridtables/CMS13Z_mcfm_grid_Zonly_yll.root";
 TString GridName2 = "/mnt/home/fuyao3/FittingCode/ApplGridtables/212_grid-40-6-15-3-CMS13TeV_Z.root";

 ApplGridHelper* run = new ApplGridHelper();
 run->openFile("saveApplGrid.root");
 run->InitialPDF("CT18NNLO", 0);
 run->InitialGrid(GridName1);
 run->InitialGrid(GridName2);

 TH1D* hist1 = run->ConvoluteBasic(GridName1, "212_Old");
 TH1D* hist2 = run->ConvoluteBasic(GridName2, "212_New");
 run->SaveFile();
*/

 TString GridName1 = "/msu/data/t3work12/yaofu/MCFM_ApplGrid/HMDYb/grid-40-6-15-3-Zb_y_-2.4_2.4.root";
 TString GridName2 = "/msu/data/t3work12/yaofu/MCFM_ApplGrid/HMDYb_real/grid-40-6-15-3-Zbbbar_y_-2.4_2.4.root";

 ApplGridHelper* run = new ApplGridHelper();
 run->openFile("saveApplGrid.root");
 run->InitialGrid(GridName1);
 run->InitialGrid(GridName2);

 function<void(TString, int, TH1D* &)> Convolute = [&](TString PDFName, int iSet, TH1D* &h){
   run->InitialPDF(PDFName, iSet);
   TH1D* hist1 = run->ConvoluteBasic(GridName1, "Zb");
   TH1D* hist2 = run->ConvoluteBasic(GridName2, "Zbbbar");

   TString HistName = hist1->GetName();
   HistName.ReplaceAll("Zb", "");
   h = (TH1D *)hist1->Clone("HMDYb_Final" + HistName);
 };

 TH1D* hist_CT18_0;
 TH1D* hist_CT18_57;
 TH1D* hist_CT18_58;
 TH1D* hist_MSHT20_0;
 TH1D* hist_NNPDF40_0;

 Convolute("CT18NNLO", 0, hist_CT18_0);
 Convolute("CT18NNLO", 57, hist_CT18_57);
 Convolute("CT18NNLO", 58, hist_CT18_58);
 Convolute("MSHT20nnlo_as118", 0, hist_MSHT20_0);
 Convolute("NNPDF40_nnlo_as_01180", 0, hist_NNPDF40_0);

 hist_CT18_0->Write();
 hist_CT18_57->Write();
 hist_CT18_58->Write();
 hist_MSHT20_0->Write();
 hist_NNPDF40_0->Write();

 run->SaveFile();

 return 1;
}
