#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include "Calculation/ThreadChi2.h"
#include "Calculation/PDFChi2.h"
#include "Calculation/Iterate.h"
#include "Calculation/GlobalFittingCore.h"

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

 map<TString, double> p = setting.FittingParameter;

 vector<TString> FlavorList = setting.FlavorList;
 vector<int> FlagList = setting.FlagList;

 for(int iflavor = 0; iflavor < FlavorList.size(); iflavor++){
   m_pdf_Q0->SetParameter(FlavorList.at(iflavor), setting.ShapeParameterValue.at(FlavorList.at(iflavor)));
 }

 m_pdf_Q0->SetInitialgluonMomentum(setting.InitialgluonMomentum);
 m_pdf_Q0->SetInitialStrangeB0(setting.InitialStrangeB0);

 m_pdf_Q0->Initialize(setting.IFun, FlavorList, FlagList);
 m_pdf_Q0->ParameterOutput();

 HoppetInterface* m_hoppet = new HoppetInterface();
 m_hoppet->SetAlphaSQ0(setting.AlphaS, setting.AlphaS_Q0);
 m_hoppet->SetMcbt(setting.Amhat(4), setting.Amhat(5), setting.Amhat(6));
 m_hoppet->SetEvolveOrder(setting.IorEvl);
 m_hoppet->SetAlphaSOrder(setting.IorQCD);

 if(setting.isEvolveSmallx) m_hoppet->SetEvolveSmallx(); // Just need to be done once. All the other Initialize() call will use the same setting.

 if(setting.EvolveType == "Hoppet"){
   m_hoppet->Initialize(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFEL"){
   m_hoppet->InitializeAPFEL(m_pdf_Q0, setting.Qini);
 }
 else if(setting.EvolveType == "APFELxx"){
   m_hoppet->InitializeAPFELxx(m_pdf_Q0, setting.Qini);
 }

 m_hoppet->SetQArray();
 m_hoppet->SetXArray();
 pdsReader* pdftable = m_hoppet->PrepareCTEQTable();

 pdftable->OutputPDF("mypdf_bestfit.pds");
 if(setting.IFun == 999 || setting.IFun == 99901) m_pdf_Q0->OutputFantoCT18();

 return 1;
}

