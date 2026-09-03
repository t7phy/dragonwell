#include <iostream>
#include "RootCommon.h"
#include "CTEQHelper/PDFEvolve.h"
#include "CTEQHelper/HoppetInterface.h"

using namespace std;

int main(int argc, char** argv)
{
 int Mellinxf = 0;
 int Mellinf = -1;

 readfantosteer_();

 int ifl_dv = 2;
 int ifl_uv = 1;
 int ifl_gluon = 0;
 int ifl_ubar = -1;
 int ifl_dbar = -2;
 int ifl_str = -3;

 double uvInt = fantomellinmoment_(ifl_uv, Mellinf);
 double dvInt = fantomellinmoment_(ifl_dv, Mellinf);
 double uvxInt = fantomellinmoment_(ifl_uv, Mellinxf);
 double dvxInt = fantomellinmoment_(ifl_dv, Mellinxf);
 double ubarxInt = fantomellinmoment_(ifl_ubar, Mellinxf);
 double dbarxInt = fantomellinmoment_(ifl_dbar, Mellinxf);
 double gluonxInt = fantomellinmoment_(ifl_gluon, Mellinxf);
 double strxInt = fantomellinmoment_(ifl_str, Mellinxf);

 cout<<"uvInt = "<<uvInt<<endl;
 cout<<"dvInt = "<<dvInt<<endl;
 cout<<"uvxInt = "<<uvxInt<<endl;
 cout<<"dvxInt = "<<dvxInt<<endl;
 cout<<"ubarxInt = "<<ubarxInt<<endl;
 cout<<"dbarxInt = "<<dbarxInt<<endl;
 cout<<"gluonxInt = "<<gluonxInt<<endl;
 cout<<"strxInt = "<<strxInt<<endl;

 /*

 // Baseline CT18 PDF
 vector<TString> FlavorList_CT18 = {"dv", "uv", "gluon", "dmu", "dpu", "str"};
 vector<int> FlagList_CT18 = {981, 981, 848, 219, 218, 220};

 PDFEvolve* pdf = new PDFEvolve();

 pdf->SetParameter("dv",    vector<double>{ 0.76317,  3.03609, 2.61407,  1.82746,  2.72032,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("uv",    vector<double>{ 0.76317,  3.03609, 1.50192, -0.14666,  1.67108,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("gluon", vector<double>{ 0.53101,  3.14810, 3.03140, -1.70494,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetParameter("dmu",   vector<double>{-0.02194,  7.73657, 4.00000,  0.29223,  0.64695,  0.47492,  0.74137,  0.61791,  0.19493,  0.87087,  0.26669,  0.73317});
 pdf->SetParameter("dpu",   vector<double>{-0.02194,  7.73657, 4.00000,  0.29223,  0.64695,  0.47492,  0.74137,  0.61791,  0.19493,  0.87087,  0.26669,  0.73317});
 pdf->SetParameter("str",   vector<double>{-0.02194, 10.30986, 4.00000,  0.46599,  0.46599,  0.22525,  0.22525,  1.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 pdf->SetInitialgluonMomentum(0.3846129);
 pdf->SetInitialStrangeB0(0.5146522);

 pdf->Initialize(1, FlavorList_CT18, FlagList_CT18);

 HoppetInterface* hoppet = new HoppetInterface();
 hoppet->SetAlphaSQ0(0.118, 91.19);
 hoppet->Initialize(pdf, 1.295);

 pdsReader* mypdf = hoppet->PrepareCTEQTable();
 cout<<"CT18:"<<endl;
 cout<<"x = 0.001 gluon = "<<mypdf->xfxQ(0, 0.001, 1.295)<<endl;
 cout<<"x = 0.01 gluon = "<<mypdf->xfxQ(0, 0.01, 1.295)<<endl;
 cout<<"x = 0.1 gluon = "<<mypdf->xfxQ(0, 0.1, 1.295)<<endl;
 cout<<"x = 0.4 gluon = "<<mypdf->xfxQ(0, 0.4, 1.295)<<endl;
 cout<<"x = 1e-9 uv = "<<1e-9 * pdf->Q0_uv(1e-9)<<endl;
 cout<<"x = 0.0001 uv = "<<0.0001 * pdf->Q0_uv(0.0001)<<endl;
 cout<<"x = 0.001 uv = "<<0.001 * pdf->Q0_uv(0.001)<<endl;
 cout<<"x = 0.01 uv = "<<0.01 * pdf->Q0_uv(0.01)<<endl;
 cout<<"x = 0.1 uv = "<<0.1 * pdf->Q0_uv(0.1)<<endl;
 cout<<"x = 0.4 uv = "<<0.4 * pdf->Q0_uv(0.4)<<endl;
 cout<<"x = 1e-9 dv = "<<1e-9 * pdf->Q0_dv(1e-9)<<endl;
 cout<<"x = 0.0001 dv = "<<0.0001 * pdf->Q0_dv(0.0001)<<endl;
 cout<<"x = 0.001 dv = "<<0.001 * pdf->Q0_dv(0.001)<<endl;
 cout<<"x = 0.01 dv = "<<0.01 * pdf->Q0_dv(0.01)<<endl;
 cout<<"x = 0.1 dv = "<<0.1 * pdf->Q0_dv(0.1)<<endl;
 cout<<"x = 0.4 dv = "<<0.4 * pdf->Q0_dv(0.4)<<endl;
 cout<<"x = 1e-9 ubar = "<<1e-9 * pdf->Q0_ubar(1e-9)<<endl;
 cout<<"x = 0.0001 ubar = "<<0.0001 * pdf->Q0_ubar(0.0001)<<endl;
 cout<<"x = 0.001 ubar = "<<0.001 * pdf->Q0_ubar(0.001)<<endl;
 cout<<"x = 0.01 ubar = "<<0.01 * pdf->Q0_ubar(0.01)<<endl;
 cout<<"x = 0.1 ubar = "<<0.1 * pdf->Q0_ubar(0.1)<<endl;
 cout<<"x = 0.4 ubar = "<<0.4 * pdf->Q0_ubar(0.4)<<endl;
 cout<<"x = 1e-9 dbar = "<<1e-9 * pdf->Q0_dbar(1e-9)<<endl;
 cout<<"x = 0.0001 dbar = "<<0.0001 * pdf->Q0_dbar(0.0001)<<endl;
 cout<<"x = 0.001 dbar = "<<0.001 * pdf->Q0_dbar(0.001)<<endl;
 cout<<"x = 0.01 dbar = "<<0.01 * pdf->Q0_dbar(0.01)<<endl;
 cout<<"x = 0.1 dbar = "<<0.1 * pdf->Q0_dbar(0.1)<<endl;
 cout<<"x = 0.4 dbar = "<<0.4 * pdf->Q0_dbar(0.4)<<endl;
 cout<<"x = 1e-9 str = "<<1e-9 * (pdf->Q0_s(1e-9) + pdf->Q0_sbar(1e-9))<<endl;
 cout<<"x = 0.0001 str = "<<0.0001 * (pdf->Q0_s(0.0001) + pdf->Q0_sbar(0.0001))<<endl;
 cout<<"x = 0.001 str = "<<0.001 * (pdf->Q0_s(0.001) + pdf->Q0_sbar(0.001))<<endl;
 cout<<"x = 0.01 str = "<<0.01 * (pdf->Q0_s(0.01) + pdf->Q0_sbar(0.01))<<endl;
 cout<<"x = 0.1 str = "<<0.1 * (pdf->Q0_s(0.1) + pdf->Q0_sbar(0.1))<<endl;
 cout<<"x = 0.4 str = "<<0.4 * (pdf->Q0_s(0.4) + pdf->Q0_sbar(0.4))<<endl;

 auto GetBFun_gluon = [&](double x){
   double a1 = pdf->fun_gluon->a1;
   double a2 = pdf->fun_gluon->a2;
   double aa2;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   return pdf->Q0_gluon(x) / (pdf->gluonNorm * pow(x, a1 - 1) * pow(1 - x, aa2)) - 1.0;
 };

 double x;
 cout<<"gluon:"<<endl;
 x = 1e-9;
 cout<<"x = 1e-9 B = "<<GetBFun_gluon(x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 B = "<<GetBFun_gluon(x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 B = "<<GetBFun_gluon(x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 B = "<<GetBFun_gluon(x)<<endl;
 x = 0.8;
 cout<<"x = 0.8 B = "<<GetBFun_gluon(x)<<endl;

 double err = 1e-13;
 int irt;

 cout<<"uv:"<<endl;

 auto GetBFun_uv = [&](double x){
   double a1 = pdf->fun_uv->a1;
   double a2 = pdf->fun_uv->a2;
   double aa2;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   return pdf->Q0_uv(x) / (pdf->uvNorm * pow(x, a1 - 1) * pow(1 - x, aa2)) - 1.0;
 };

 x = 1e-9;
 cout<<"x = 1e-9 B = "<<GetBFun_uv(x)<<endl;
 x = 0.0001;
 cout<<"x = 0.0001 B = "<<GetBFun_uv(x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 B = "<<GetBFun_uv(x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 B = "<<GetBFun_uv(x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 B = "<<GetBFun_uv(x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 B = "<<GetBFun_uv(x)<<endl;
 x = 0.8;
 cout<<"x = 0.8 B = "<<GetBFun_uv(x)<<endl;

 cout<<"dv:"<<endl;

 auto GetBFun_dv = [&](double x){
   double a1 = pdf->fun_dv->a1;
   double a2 = pdf->fun_dv->a2;
   double aa2;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   return pdf->Q0_dv(x) / (pdf->dvNorm * pow(x, a1 - 1) * pow(1 - x, aa2)) - 1.0;
 };

 x = 1e-9;
 cout<<"x = 1e-9 B = "<<GetBFun_dv(x)<<endl;
 x = 0.0001;
 cout<<"x = 0.0001 B = "<<GetBFun_dv(x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 B = "<<GetBFun_dv(x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 B = "<<GetBFun_dv(x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 B = "<<GetBFun_dv(x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 B = "<<GetBFun_dv(x)<<endl;
 x = 0.8;
 cout<<"x = 0.8 B = "<<GetBFun_dv(x)<<endl;

 cout<<"dbar:"<<endl;

 auto GetBFun_dbar = [&](double x){
   double a1 = pdf->fun_dpu->a1;
   double a2 = pdf->fun_dpu->a2;
   double aa2;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   return pdf->Q0_dbar(x) / (pdf->dpuNorm / 2.0 * pow(x, a1 - 1) * pow(1 - x, aa2)) - 1.0;
 };

 auto GetBFun_ubar = [&](double x){
   double a1 = pdf->fun_dpu->a1;
   double a2 = pdf->fun_dpu->a2;
   double aa2;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{ 
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   return pdf->Q0_ubar(x) / (pdf->dpuNorm / 2.0 * pow(x, a1 - 1) * pow(1 - x, aa2)) - 1.0;
 };

 x = 1e-9;
 cout<<"x = 1e-9 B = "<<GetBFun_dbar(x)<<endl;
 x = 0.0001;
 cout<<"x = 0.0001 B = "<<GetBFun_dbar(x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 B = "<<GetBFun_dbar(x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 B = "<<GetBFun_dbar(x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 B = "<<GetBFun_dbar(x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 B = "<<GetBFun_dbar(x)<<endl;
 x = 0.8;
 cout<<"x = 0.8 B = "<<GetBFun_dbar(x)<<endl;

 cout<<"ubar:"<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 B = "<<GetBFun_ubar(x)<<endl;
 x = 0.0001;
 cout<<"x = 0.0001 B = "<<GetBFun_ubar(x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 B = "<<GetBFun_ubar(x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 B = "<<GetBFun_ubar(x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 B = "<<GetBFun_ubar(x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 B = "<<GetBFun_ubar(x)<<endl;
 x = 0.8;
 cout<<"x = 0.8 B = "<<GetBFun_ubar(x)<<endl;

 auto GetBFun_str = [&](double x){
   double a1 = pdf->fun_str->a1;
   double a2 = pdf->fun_str->a2;
   double aa2;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   //cout<<pdf->Q0_s(x)<<"  "<<pdf->sNorm * pdf->fun_str->fcn(x)<<"  "<<pdf->sNorm<<"  "<<(pdf->sNorm * pow(x, a1 - 1) * pow(1 - x, aa2))<<endl;
   return pdf->fun_str->fcn(x) / (pow(x, a1 - 1) * pow(1 - x, aa2)) - 1.0;
 };

 cout<<"sbar:"<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 B = "<<GetBFun_str(x)<<endl;
 x = 0.0001;
 cout<<"x = 0.0001 B = "<<GetBFun_str(x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 B = "<<GetBFun_str(x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 B = "<<GetBFun_str(x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 B = "<<GetBFun_str(x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 B = "<<GetBFun_str(x)<<endl;
 x = 0.8;
 cout<<"x = 0.8 B = "<<GetBFun_str(x)<<endl;

 ////////////////////////////////////////////////////////////////////////////////////////////

 cout<<endl;
 cout<<"Fantomas:"<<endl;

 PDFEvolve* m_pdf_Q0 = new PDFEvolve();

 vector<TString> FlavorList = {"dv", "uv", "gluon", "ubar", "dbar", "str"};
 vector<int> FlagList = {2, 1, 0, -1, -2, -3};

 m_pdf_Q0->SetParameter("dv",    vector<double>{0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 m_pdf_Q0->SetParameter("uv",    vector<double>{0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 m_pdf_Q0->SetParameter("gluon", vector<double>{0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 m_pdf_Q0->SetParameter("ubar",   vector<double>{0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 m_pdf_Q0->SetParameter("dbar",   vector<double>{0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});
 m_pdf_Q0->SetParameter("str",   vector<double>{0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000});

 m_pdf_Q0->Initialize(999, FlavorList, FlagList);

 m_pdf_Q0->OutputFantoCT18();
*/

 return 1;
}
