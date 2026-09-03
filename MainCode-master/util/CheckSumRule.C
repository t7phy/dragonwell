#include <iostream>
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/PDFEvolve.h"
#include "PDFHelper/PDFHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: ./CheckSumRule xxx.pds"<<endl;
   return 0;
 }

 pdsReader* pdf = new pdsReader();
 pdf->Initialize(argv[1]);

 double Q0 = pdf->QINI;

 PDFEvolve* m_pdf_Q0 = new PDFEvolve();

 auto uv_Q0 = [&](double x){
   return pdf->CT14PDF(1, x, Q0) - pdf->CT14PDF(-1, x, Q0);
 };

 auto dv_Q0 = [&](double x){
   return pdf->CT14PDF(2, x, Q0) - pdf->CT14PDF(-2, x, Q0);
 };

 auto sv_Q0 = [&](double x){
   return pdf->CT14PDF(3, x, Q0) - pdf->CT14PDF(-3, x, Q0);
 };

 auto cv_Q0 = [&](double x){
   return pdf->CT14PDF(4, x, Q0) - pdf->CT14PDF(-4, x, Q0);
 };

 auto bv_Q0 = [&](double x){
   return pdf->CT14PDF(5, x, Q0) - pdf->CT14PDF(-5, x, Q0);
 };

 auto momentum_Q0 = [&](double x){
   double Value = 0.0;
   for(int i = -5; i <= 5; i++){
     Value += x * pdf->CT14PDF(i, x, Q0);
   };
   return Value;
 };

 double uv_NumberInt_Q0 = m_pdf_Q0->PDFIntegral(uv_Q0);
 double dv_NumberInt_Q0 = m_pdf_Q0->PDFIntegral(dv_Q0);
 double sv_NumberInt_Q0 = m_pdf_Q0->PDFIntegral(sv_Q0);
 double cv_NumberInt_Q0 = m_pdf_Q0->PDFIntegral(cv_Q0);
 double bv_NumberInt_Q0 = m_pdf_Q0->PDFIntegral(bv_Q0);
 double MomentumInt_Q0 = m_pdf_Q0->PDFIntegral(momentum_Q0);

 auto uv_Q100 = [&](double x){
   return pdf->CT14PDF(1, x, 100.0) - pdf->CT14PDF(-1, x, 100.0);
 };

 auto dv_Q100 = [&](double x){
   return pdf->CT14PDF(2, x, 100.0) - pdf->CT14PDF(-2, x, 100.0);
 };

 auto sv_Q100 = [&](double x){
   return pdf->CT14PDF(3, x, 100.0) - pdf->CT14PDF(-3, x, 100.0);
 };

 auto cv_Q100 = [&](double x){
   return pdf->CT14PDF(4, x, 100.0) - pdf->CT14PDF(-4, x, 100.0);
 };

 auto bv_Q100 = [&](double x){
   return pdf->CT14PDF(5, x, 100.0) - pdf->CT14PDF(-5, x, 100.0);
 };

 auto momentum_Q100 = [&](double x){
   double Value = 0.0;
   for(int i = -5; i <= 5; i++){
     Value += x * pdf->CT14PDF(i, x, 100.0);
   };
   return Value;
 };

 double uv_NumberInt_Q100 = m_pdf_Q0->PDFIntegral(uv_Q100);
 double dv_NumberInt_Q100 = m_pdf_Q0->PDFIntegral(dv_Q100);
 double sv_NumberInt_Q100 = m_pdf_Q0->PDFIntegral(sv_Q100);
 double cv_NumberInt_Q100 = m_pdf_Q0->PDFIntegral(cv_Q100);
 double bv_NumberInt_Q100 = m_pdf_Q0->PDFIntegral(bv_Q100);
 double MomentumInt_Q100 = m_pdf_Q0->PDFIntegral(momentum_Q100);

 PDFHelper* pdf_helper = new PDFHelper();
 pdf_helper->InitialCTEQPDF(argv[1], "CT18", 0);
 double uv_NumberInt_Q0_ph = pdf_helper->PDFIntegral(Q0, 2) - pdf_helper->PDFIntegral(Q0, -2);
 double dv_NumberInt_Q0_ph = pdf_helper->PDFIntegral(Q0, 1) - pdf_helper->PDFIntegral(Q0, -1);
 double sv_NumberInt_Q0_ph = pdf_helper->PDFIntegral(Q0, 3) - pdf_helper->PDFIntegral(Q0, -3);
 double cv_NumberInt_Q0_ph = pdf_helper->PDFIntegral(Q0, 4) - pdf_helper->PDFIntegral(Q0, -4);
 double bv_NumberInt_Q0_ph = pdf_helper->PDFIntegral(Q0, 5) - pdf_helper->PDFIntegral(Q0, -5);

 double uv_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, 2) - pdf_helper->xPDFIntegral(Q0, -2);
 double dv_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, 1) - pdf_helper->xPDFIntegral(Q0, -1);
 double ubar_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, -2);
 double dbar_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, -1);
 double ssbar_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, 3) + pdf_helper->xPDFIntegral(Q0, -3);
 double gluon_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, 0);
 double rest_MomentumInt_Q0_ph = pdf_helper->xPDFIntegral(Q0, 4) + pdf_helper->xPDFIntegral(Q0, -4) + pdf_helper->xPDFIntegral(Q0, 5) + pdf_helper->xPDFIntegral(Q0, -5);

 double uv_NumberInt_Q100_ph = pdf_helper->PDFIntegral(100.0, 2) - pdf_helper->PDFIntegral(100.0, -2);
 double dv_NumberInt_Q100_ph = pdf_helper->PDFIntegral(100.0, 1) - pdf_helper->PDFIntegral(100.0, -1);
 double sv_NumberInt_Q100_ph = pdf_helper->PDFIntegral(100.0, 3) - pdf_helper->PDFIntegral(100.0, -3);
 double cv_NumberInt_Q100_ph = pdf_helper->PDFIntegral(100.0, 4) - pdf_helper->PDFIntegral(100.0, -4);
 double bv_NumberInt_Q100_ph = pdf_helper->PDFIntegral(100.0, 5) - pdf_helper->PDFIntegral(100.0, -5);

 cout<<endl;
 cout<<"Number/Momentum sum rule in Q0 = "<<Q0<<" GeV:"<<endl;
 cout<<"u - ubar integral = "<<uv_NumberInt_Q0<<endl;
 cout<<"d - dbar integral = "<<dv_NumberInt_Q0<<endl;
 cout<<"s - sbar integral = "<<sv_NumberInt_Q0<<endl;
 cout<<"c - cbar integral = "<<cv_NumberInt_Q0<<endl;
 cout<<"b - bbar integral = "<<bv_NumberInt_Q0<<endl;
 cout<<"Momentum integral = "<<MomentumInt_Q0<<endl;
 cout<<endl;
 cout<<"Number/Momentum sum rule in Q = 100.0 GeV:"<<endl;
 cout<<"u - ubar integral = "<<uv_NumberInt_Q100<<endl;
 cout<<"d - dbar integral = "<<dv_NumberInt_Q100<<endl;
 cout<<"s - sbar integral = "<<sv_NumberInt_Q100<<endl;
 cout<<"c - cbar integral = "<<cv_NumberInt_Q100<<endl;
 cout<<"b - bbar integral = "<<bv_NumberInt_Q100<<endl;
 cout<<"Momentum integral = "<<MomentumInt_Q100<<endl;
 cout<<endl;

 cout<<"Number/Momentum sum rule in Q0 = "<<Q0<<" GeV (PDFHelper):"<<endl;
 cout<<"u - ubar integral = "<<uv_NumberInt_Q0_ph<<endl;
 cout<<"d - dbar integral = "<<dv_NumberInt_Q0_ph<<endl;
 cout<<"s - sbar integral = "<<sv_NumberInt_Q0_ph<<endl;
 cout<<"c - cbar integral = "<<cv_NumberInt_Q0_ph<<endl;
 cout<<"b - bbar integral = "<<bv_NumberInt_Q0_ph<<endl;
 cout<<endl;
 cout<<"Number/Momentum sum rule in Q = 100.0 GeV (PDFHelper):"<<endl;
 cout<<"u - ubar integral = "<<uv_NumberInt_Q100_ph<<endl;
 cout<<"d - dbar integral = "<<dv_NumberInt_Q100_ph<<endl;
 cout<<"s - sbar integral = "<<sv_NumberInt_Q100_ph<<endl;
 cout<<"c - cbar integral = "<<cv_NumberInt_Q100_ph<<endl;
 cout<<"b - bbar integral = "<<bv_NumberInt_Q100_ph<<endl;
 cout<<endl;
 cout<<"uv momentum = "<<uv_MomentumInt_Q0_ph<<endl;
 cout<<"dv momentum = "<<dv_MomentumInt_Q0_ph<<endl;
 cout<<"gluon momentum = "<<gluon_MomentumInt_Q0_ph<<endl;
 cout<<"ubar momentum = "<<ubar_MomentumInt_Q0_ph<<endl;
 cout<<"dbar momentum = "<<dbar_MomentumInt_Q0_ph<<endl;
 cout<<"s+sbar momentum = "<<ssbar_MomentumInt_Q0_ph<<endl;
 cout<<"rest momentum = "<<rest_MomentumInt_Q0_ph<<endl;

 if(fabs(uv_NumberInt_Q0 - 2.0) < 1e-1
 && fabs(dv_NumberInt_Q0 - 1.0) < 1e-1
 && fabs(sv_NumberInt_Q0 - 0.0) < 1e-1
 && fabs(MomentumInt_Q0 - 1.0) < 1e-1
 && fabs(uv_NumberInt_Q100 - 2.0) < 1e-1
 && fabs(dv_NumberInt_Q100 - 1.0) < 1e-1
 && fabs(sv_NumberInt_Q100 - 0.0) < 1e-1
 && fabs(cv_NumberInt_Q100 - 0.0) < 1e-1
 && fabs(bv_NumberInt_Q100 - 0.0) < 1e-1
 && fabs(MomentumInt_Q100 - 1.0) < 1e-1){
   cout<<"PDF sum rule check ok."<<endl;
 }
 else{
   cout<<"PDF sum rule check failed."<<endl;
 }

 return 1;
}
