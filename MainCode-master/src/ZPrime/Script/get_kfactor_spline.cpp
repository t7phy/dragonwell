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
#include "TSpline.h"
#include "/afs/cern.ch/user/y/yafu/figure/Graph.h"

void get_kfactor_spline()
{
 auto dump_tspline3_coeff = [&](TSpline3* s, TString FunctionName){
   const int np = s->GetNp();           // number of knots (x_i)
   const int nseg = np - 1;             // number of segments
   //cout << "Spline name = " << s->GetName()
   //     << ", Np = " << np
   //     << ", Nseg = " << nseg << "\n\n";

   vector<double> fX;
   vector<double> fY;
   vector<double> fB;
   vector<double> fC;
   vector<double> fD;

   for (int i = 0; i < nseg; ++i) {
     Double_t x0 = 0.0, x1 = 0.0;

     Double_t A=0, B=0, C=0, D=0;
     // TSplinePoly stores the coefficients in local variable dx = x - x0
     s->GetCoeff(i, x0, A, B, C, D);

     fX.push_back(x0);
     fY.push_back(A);
     fB.push_back(B);
     fC.push_back(C);
     fD.push_back(D);
     //cout << "Segment " << i
     //     << " : " << x0  "\n"
     //     << "  Local form: y = A + B*(x-x0) + C*(x-x0)^2 + D*(x-x0)^3\n"
     //     << "  A=" << A << "  B=" << B << "  C=" << C << "  D=" << D << "\n\n";
   }

   cout<<"double "<<FunctionName<<"(double x)"<<endl;
   cout<<"{"<<endl;
   cout<<"  const int fNp = "<<nseg<<", fKstep = 0;"<<endl;
   cout<<"  const double fDelta = -1, fXmin = "<<fX.at(0)<<", fXmax = "<<fX.at(fX.size() - 1)<<";"<<endl;
   cout<<"  const double fX["<<nseg<<"] = {";
   for(int i = 0; i < nseg; i++){
     if(i != nseg - 1) cout<<fX.at(i)<<", ";
     else cout<<fX.at(i);

     if(i != 0 && i % 5 == 0){
       cout<<endl;
       cout<<"                         ";
     }
     if(i == nseg - 1) cout<<"};"<<endl;
   }
   cout<<"  const double fY["<<nseg<<"] = {";
   for(int i = 0; i < nseg; i++){
     if(i != nseg - 1) cout<<fY.at(i)<<", ";
     else cout<<fY.at(i);

     if(i != 0 && i % 5 == 0){
       cout<<endl;
       cout<<"                         ";
     }
     if(i == nseg - 1) cout<<"};"<<endl;
   }
   cout<<"  const double fB["<<nseg<<"] = {";
   for(int i = 0; i < nseg; i++){
     if(i != nseg - 1) cout<<fB.at(i)<<", ";
     else cout<<fB.at(i);

     if(i != 0 && i % 5 == 0){
       cout<<endl;
       cout<<"                         ";
     }
     if(i == nseg - 1) cout<<"};"<<endl;
   }
   cout<<"  const double fC["<<nseg<<"] = {";
   for(int i = 0; i < nseg; i++){
     if(i != nseg - 1) cout<<fC.at(i)<<", ";
     else cout<<fC.at(i);

     if(i != 0 && i % 5 == 0){
       cout<<endl;
       cout<<"                         ";
     }
     if(i == nseg - 1) cout<<"};"<<endl;
   }
   cout<<"  const double fD["<<nseg<<"] = {";
   for(int i = 0; i < nseg; i++){
     if(i != nseg - 1) cout<<fD.at(i)<<", ";
     else cout<<fD.at(i);

     if(i != 0 && i % 5 == 0){
       cout<<endl;
       cout<<"                         ";
     }
     if(i == nseg - 1) cout<<"};"<<endl;
   }
   cout<<"  int klow = 0;"<<endl;
   cout<<"  if (x <= fXmin)"<<endl;
   cout<<"    klow = 0;"<<endl;
   cout<<"  else if (x >= fXmax)"<<endl;
   cout<<"    klow = fNp - 1;"<<endl;
   cout<<"  else"<<endl;
   cout<<"  {"<<endl;
   cout<<"    if (fKstep)"<<endl;
   cout<<"    {"<<endl;
   cout<<"      // Equidistant knots, use histogramming"<<endl;
   cout<<"      klow = int((x - fXmin) / fDelta);"<<endl;
   cout<<"      if (klow < fNp - 1)"<<endl;
   cout<<"        klow = fNp - 1;"<<endl;
   cout<<"    }"<<endl;
   cout<<"    else"<<endl;
   cout<<"    {"<<endl;
   cout<<"      int khig = fNp - 1, khalf;"<<endl;
   cout<<"      // Non equidistant knots, binary search"<<endl;
   cout<<"      while (khig - klow > 1)"<<endl;
   cout<<"        if (x > fX[khalf = (klow + khig) / 2])"<<endl;
   cout<<"          klow = khalf;"<<endl;
   cout<<"        else"<<endl;
   cout<<"          khig = khalf;"<<endl;
   cout<<"    }"<<endl;
   cout<<"  }"<<endl;
   cout<<"  // Evaluate now"<<endl;
   cout<<"  double dx = x - fX[klow];"<<endl;
   cout<<"  return (fY[klow] + dx * (fB[klow] + dx * (fC[klow] + dx * fD[klow])));"<<endl;
   cout<<"}"<<endl;
   cout<<endl;

 };

 auto GetSpline = [&](TString name_numer, TString name_denom, TString HistName){
   string FileLine;

   ifstream infile_numer(name_numer);
   vector<vector<double>> FullTable_numer;

   while(getline(infile_numer, FileLine)){
     vector<double> LineVector;
     double Value;
     stringstream LineStream(FileLine);
     while(LineStream >> Value){
       LineVector.push_back(Value);
     }
     if(LineVector.size() == 0) break;

     FullTable_numer.push_back(LineVector); // FullTable.at(i).at(j) is i row and j column
   }

   ifstream infile_denom(name_denom);
   vector<vector<double>> FullTable_denom;

   while(getline(infile_denom, FileLine)){
     vector<double> LineVector;
     double Value;
     stringstream LineStream(FileLine);
     while(LineStream >> Value){
       LineVector.push_back(Value);
     }
     if(LineVector.size() == 0) break;

     FullTable_denom.push_back(LineVector); // FullTable.at(i).at(j) is i row and j column
   }

   if(FullTable_numer.size() != FullTable_denom.size()){
     cout<<"Numerator and Denomenator mismatch. Numerator: "<<FullTable_numer.size()<<" Denomenator: "<<FullTable_denom.size()<<endl;
     return;
   }

   vector<double> x(FullTable_numer.size());
   vector<double> y(FullTable_numer.size());
   vector<double> y_up(FullTable_numer.size());
   vector<double> y_down(FullTable_numer.size());

   for(int i = 0; i < FullTable_numer.size(); i++){
     x.at(i) = FullTable_numer.at(i).at(0);
     y.at(i) = FullTable_numer.at(i).at(2) / FullTable_denom.at(i).at(2);
     y_down.at(i) = y.at(i) * (1.0 + FullTable_numer.at(i).at(6) / 100.0);
     y_up.at(i) = y.at(i) * (1.0 + FullTable_numer.at(i).at(7) / 100.0);

     cout<<x.at(i)<<":  "<<y.at(i)<<endl;
   }

   TGraph* nominal = new TGraph(FullTable_numer.size());
   TGraph* up = new TGraph(FullTable_numer.size());
   TGraph* down = new TGraph(FullTable_numer.size());

   for(int i = 0; i < FullTable_numer.size(); i++){
     nominal->SetPointX(i, x.at(i));
     nominal->SetPointY(i, y.at(i));
     up->SetPointX(i, x.at(i));
     up->SetPointY(i, y_up.at(i));
     down->SetPointX(i, x.at(i));
     down->SetPointY(i, y_down.at(i));
   }

   TSpline3* nominal_spline = new TSpline3(HistName + "_nominal", nominal);
   TSpline3* up_spline = new TSpline3(HistName + "_up", up);
   TSpline3* down_spline = new TSpline3(HistName + "_down", down);

   Graph* g;

   TH1D* nominal_hist = new TH1D(HistName + "_nominal_hist", HistName + "_nominal_hist", 9990, 10.0, 10000.0);
   TH1D* up_hist = new TH1D(HistName + "_up_hist", HistName + "_up_hist", 9990, 10.0, 10000.0);
   TH1D* down_hist = new TH1D(HistName + "_down_hist", HistName + "_down_hist", 9990, 10.0, 10000.0);

   for(int ibin = 1; ibin < nominal_hist->GetNbinsX(); ibin++){
     nominal_hist->SetBinContent(ibin, nominal_spline->Eval(nominal_hist->GetBinCenter(ibin)));
     nominal_hist->SetBinError(ibin, 0.0);
     up_hist->SetBinContent(ibin, up_spline->Eval(up_hist->GetBinCenter(ibin)));
     up_hist->SetBinError(ibin, 0.0);
     down_hist->SetBinContent(ibin, down_spline->Eval(down_hist->GetBinCenter(ibin)));
     down_hist->SetBinError(ibin, 0.0);
   }

   g = new Graph(HistName + "_KFactor.pdf", "M [GeV]", "KFactor");
   g->SetMode("CUSTOM");
   g->Input(1, nominal_hist, "nominal");
   g->Input(2, up_hist, "up");
   g->Input(3, down_hist, "down");
   g->Compare("MultiSimple");
   g->SetLogX();
   g->SetLegendPosition(0.05, 0.3, 0.5, 0.6);
   g->AddText(1, "Vrap #sqrt{s} = 13.6 TeV");
   g->Draw();

   TString FunctionName;
   FunctionName = "loopZPrime::Zgamma_13p6TeV_" + HistName + "_Central_spline";
   dump_tspline3_coeff(nominal_spline, FunctionName);

   FunctionName = "loopZPrime::Zgamma_13p6TeV_" + HistName + "_Up_spline";
   dump_tspline3_coeff(up_spline, FunctionName);

   FunctionName = "loopZPrime::Zgamma_13p6TeV_" + HistName + "_Down_spline";
   dump_tspline3_coeff(down_spline, FunctionName);

 };

 GetSpline("Zgamma_13600_NNLO_CT18ANNLO.vec", "Zgamma_13600_NLO_CT10.vec", "CT18ANNLO_CT10");

}



