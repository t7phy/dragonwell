#include "Calculation/ThreadChi2.h"
#include "Calculation/PDFChi2.h"
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
#include "Calculation/GlobalFittingCore.h"
#include "TMinuitHelper/TMinuitHelper.h"

GlobalFittingCore* global_instance;

void GlobalFitting_TMinuit(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 vector<double> v_par((global_instance->setting).GetNPar());

 for(int i = 0; i < v_par.size(); i++){
   v_par[i] = par[i];
 }

 f = global_instance->chi2(v_par);
}

void FittingPDF()
{
 GlobalFittingCore* m_instance = new GlobalFittingCore();

 m_instance->Initialize();

 global_instance = m_instance;

 for(int ifit = 0; ifit < (m_instance->setting).LFit; ifit++){

   cout<<"Starting "<<ifit + 1<<" Fit: "<<endl;
   m_instance->ResetFit();

   TMinuitHelper* run = new TMinuitHelper((m_instance->setting).GetNPar());
   run->SetFCN(GlobalFitting_TMinuit);
   for(int i = 0; i < (m_instance->setting).GetNPar(); i++){
   run->Input(i, (m_instance->setting).GetParName(i),
                 (m_instance->setting).GetParCentral(i),
                 (m_instance->setting).GetParStep(i));
   }
   //run->Exec("SIMPLEX", 10000, 1);//tolerance*0.001
   run->Exec("MIGRAD", (m_instance->setting).MaxCall, 1e-6);

   // Retrieve Bestfit parameters
   double* Par;
   double* ParErr;

   run->GetParametersAndError(Par, ParErr);

   vector<double> pars((m_instance->setting).GetNPar());
   vector<double> parerrs((m_instance->setting).GetNPar());

   for(int i = 0; i < pars.size(); i++){
     pars[i] = Par[i];
     parerrs[i] = ParErr[i];
   }

   m_instance->Finalize(pars, parerrs);

   m_instance->UpdateParameterCentral();

   if(fabs(m_instance->DeltaChi2) < 0.1) break;
 }
}

