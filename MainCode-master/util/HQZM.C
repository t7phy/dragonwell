#include <iostream>
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/HoppetInterface.h"
#include "Calculation/QCDSet.h"
#include "Calculation/Config.h"
#include "Calculation/CalcDIS.h"
//#include "Calculation/N3LODIS.h"

using namespace std;

int main(int argc, char** argv)
{
 Config setting;

 setting.ParseParameter("Parameters.yml");
 setting.ParseConfig("Config.yml");

 QCDSet* m_qcd = new QCDSet();
 m_qcd->SetNfTotal(setting.Nflv);
 m_qcd->SetPoleMasscbt(setting.mc, setting.mb, setting.mt);
 m_qcd->SetAmhatf();
 setting.Amhat = m_qcd->Amhat;
 delete m_qcd;

 PDFEvolve* m_pdf_Q0 = new PDFEvolve();

 vector<TString> FlavorList = setting.FlavorList;
 vector<int> FlagList = setting.FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetInitialgluonMomentum(setting.InitialgluonMomentum);
 m_pdf_Q0->SetInitialStrangeB0(setting.InitialStrangeB0);

 m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);

 HoppetInterface* m_hoppet = new HoppetInterface();
 m_hoppet->SetAlphaSQ0(setting.AlphaS, setting.AlphaS_Q0);
 m_hoppet->SetMcbt(setting.Amhat(4), setting.Amhat(5), setting.Amhat(6));
 m_hoppet->SetEvolveOrder(setting.IorEvl);
 m_hoppet->SetAlphaSOrder(setting.IorQCD);
 m_hoppet->Initialize(m_pdf_Q0, setting.Qini);

 m_hoppet->SetQArray();
 m_hoppet->SetXArray();
 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();

 if(setting.PDFInputType == "None"){
   setting.ConfigPDF(pdftable);
 }
 else if(setting.PDFInputType == "LHAPDF"){
   setting.ConfigPDF(setting.PDFInput, setting.PDFiSet);
 }

 CalcDIS* run = new CalcDIS();

 if(setting.PDFInputType == "None"){
   run->InitialCTEQPDF(setting.m_cteqpdf);
 }
 else if(setting.PDFInputType == "LHAPDF"){
   run->InitialPDF(setting.PDFName, setting.iSet);
 }

 run->mSetDis();

// vector<double> xVector = {1e-9, 5e-9, 1e-8, 5e-8, 1e-7, 5e-7, 1e-6, 5e-6, 1e-5, 5e-5, 1e-4, 5e-4, 1e-3, 5e-3, 1e-2, 5e-2, 1e-1, 0.5};
 vector<double> xVector = {0.1};
 double Q = 10.0;
 int iFn = 2;
 int igq = 1;
 int ord = 2;
 int iAB = 1;
 int nf = 5;
 double mu = Q;
 double mh = 1.3;

 double fac = 4.0 / 9.0 * pow(run->GetAlphaS(Q), ord + 2) / 2.0;
 for(int ix = 0; ix < xVector.size(); ix++){
   double x = xVector.at(ix);
   double result = fac * run->FahiNNLO(x, Q, iFn, igq, ord, iAB, nf, mu, mh);
   cout<<"x = "<<x<<" result = "<<result<<endl;
 }

// N3LODIS* run = new N3LODIS();

// run->InitialCTEQPDF(setting.m_cteqpdf);
// run->Initialize();


 return 1;
}
