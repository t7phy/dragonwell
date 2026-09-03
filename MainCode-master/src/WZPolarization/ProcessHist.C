#ifndef WZPol_ProcessHist_cxx
#define WZPol_ProcessHist_cxx
#include "WZPolarization/HistsWZPolarization.h"

using namespace std;

ProcessHist::ProcessHist()
{
}

void ProcessHist::Initial(int iThread, int MCType)
{
 this->MCType[iThread - 1] = MCType;

 isData[iThread - 1] = false;
 isSignal[iThread - 1] = false;

 if(this->MCType[iThread - 1] == -1) isData[iThread - 1] = true;
 if(this->MCType[iThread - 1] == 364253 || this->MCType[iThread - 1] == 364991 || this->MCType[iThread - 1] == 364992 || this->MCType[iThread - 1] == 364993 || this->MCType[iThread - 1] == 364994) isSignal[iThread - 1] = true;
 if(this->MCType[iThread - 1] == 500290 || this->MCType[iThread - 1] == 500291 || this->MCType[iThread - 1] == 500292 || this->MCType[iThread - 1] == 500293 || this->MCType[iThread - 1] == 500294 || this->MCType[iThread - 1] == 500295 || this->MCType[iThread - 1] == 500296 || this->MCType[iThread - 1] == 500297) isSignal[iThread - 1] = true;
 if(this->MCType[iThread - 1] == 501793 || this->MCType[iThread - 1] == 501794 || this->MCType[iThread - 1] == 501795 || this->MCType[iThread - 1] == 501796 || this->MCType[iThread - 1] == 501797 || this->MCType[iThread - 1] == 501798 || this->MCType[iThread - 1] == 501799 || this->MCType[iThread - 1] == 501800) isSignal[iThread - 1] = true;
 if(this->MCType[iThread - 1] == 507019 || this->MCType[iThread - 1] == 507020 || this->MCType[iThread - 1] == 507021 || this->MCType[iThread - 1] == 507022 || this->MCType[iThread - 1] == 507023 || this->MCType[iThread - 1] == 507024 || this->MCType[iThread - 1] == 507025 || this->MCType[iThread - 1] == 507026) isSignal[iThread - 1] = true;
 if(this->MCType[iThread - 1] == 507027 || this->MCType[iThread - 1] == 507028 || this->MCType[iThread - 1] == 507029 || this->MCType[iThread - 1] == 507030 || this->MCType[iThread - 1] == 507031 || this->MCType[iThread - 1] == 507032 || this->MCType[iThread - 1] == 507033 || this->MCType[iThread - 1] == 507034) isSignal[iThread - 1] = true;

 this->OnlyNominal[iThread - 1] = fHist->OnlyNominal;
 this->doBkg[iThread - 1] = fHist->doBkg;
 this->doControlRegion[iThread - 1] = fHist->doControlRegion;
 this->doFakeRate[iThread - 1] = fHist->doFakeRate;
}

void ProcessHist::Fill(int iThread, double par, double weight, EventWZPolarization ProcessEvent)
{
   InclusivePolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive);
   SignalPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
   SignalPtWZPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
   ZZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZZCR * ProcessEvent.passTTT);
   //TopCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passTopCR);
   HighPtWZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ > 70));
   LowPtWZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70));
   //HighR21CRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 > 0.8));
   //LowR21CRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 < 0.8));
   //LowPtZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passLowPtZCR);
   HighPtZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
   PtWZ10CRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 10));
   PtWZ20CRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 20));
   PtWZ40CRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 40));

   if(this->MCType[iThread - 1] == 364253){
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507019);
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507019);
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * LLNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * LLNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507021);
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507021);
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * LTNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * LTNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507023);
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507023);
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * TLNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * TLNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507025);
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Initial(507025);
     SignalNLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * TTNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
     Signal100NLOPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * TTNLOWeight[iThread - 1] * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
   }

   if(isData[iThread - 1]){
     Inclusive_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive);
     Signal_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
     SignalPtWZ_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
     ZZCRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZZCR * ProcessEvent.passTTT);
     //TopCRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passTopCR);
     HighPtWZCRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ > 70));
     LowPtWZCRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70));
     //HighR21CRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 > 0.8));
     //LowR21CRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 < 0.8));
     //LowPtZCRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passLowPtZCR);
     HighPtZCRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
     PtWZ10CRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 10));
     PtWZ20CRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 20));
     PtWZ40CRPolarized_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 40));
     TopEnrichCR_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopEnrichCR * ProcessEvent.passTTT);
     ZjetEnrichCR_Data->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZjetEnrichCR * ProcessEvent.passTTT);
   }

   if(doBkg[iThread - 1]){
     //if(!isData[iThread - 1] && !isSignal[iThread - 1]){
       Inclusive_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive);
       Signal_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
       SignalPtWZ_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
       ZZCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZZCR * ProcessEvent.passTTT);
       //TopCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passTopCR);
       HighPtWZCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ > 70));
       LowPtWZCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 70));
       //HighR21CR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 > 0.8));
       //LowR21CR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.R21 < 0.8));
       //LowPtZCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passLowPtZCR);
       HighPtZCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_Z > 200));
       PtWZ10CR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 10));
       PtWZ20CR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 20));
       PtWZ40CR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * (ProcessEvent.Pt_WZ < 40));
       WZInclusiveNoMETCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveNoMET * ProcessEvent.passTTT);
       //int passTTT = ProcessEvent.passZCondition1 * ProcessEvent.passZCondition2 * ProcessEvent.passZCondition3 * ProcessEvent.passIPID1 * ProcessEvent.passIPID2 * ProcessEvent.passIPID3;
       int passTTT = ProcessEvent.passTTT;
       TopEnrichCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopEnrichCR * passTTT);
       ZjetEnrichCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZjetEnrichCR * passTTT);
       //ZFakeElCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZFakeElCR * ProcessEvent.passTTT);
       //ZFakeMuCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZFakeMuCR * ProcessEvent.passTTT);
       //TopElCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopElCR * ProcessEvent.passTTT);
       //TopMuCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopMuCR * ProcessEvent.passTTT);
     //}
   }

/* if(!OnlyNominal[iThread - 1]){//Systematic plot
   int isys = fHist->FindSysIndex(ProcessEvent.SystematicName, "SignalWZ");
   if(isSignal[iThread - 1]){
     InclusivePolarized_sys->HistPtr(iThread - 1)->Fill(isys, par, weight * ProcessEvent.passWZInclusive);
     SignalPolarized_sys->HistPtr(iThread - 1)->Fill(isys, par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passSignalRegion);
     ZZCRPolarized_sys->HistPtr(iThread - 1)->Fill(isys, par, weight * ProcessEvent.passZZCR * ProcessEvent.passTTT);
     TopCRPolarized_sys->HistPtr(iThread - 1)->Fill(isys, par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passTopCR);
     HighPtWZCRPolarized_sys->HistPtr(iThread - 1)->Fill(isys, par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passHighPtWZCR);
     LowPtZCRPolarized_sys->HistPtr(iThread - 1)->Fill(isys, par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passLowPtZCR);
   }

 }
*/

}

void ProcessHist::FillFake(int iThread, double par, double weight, EventWZPolarization ProcessEvent)
{
 if(doFakeRate[iThread - 1] == 1){
   Inclusive_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose);
   Signal_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
   SignalPtWZ_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 200));
   ZZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZZCR);
   //TopCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * ProcessEvent.passTopCR);
   HighPtWZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ > 70));
   LowPtWZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 70));
   //HighR21CR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.R21 > 0.8));
   //LowR21CR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.R21 < 0.8));
   //LowPtZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * ProcessEvent.passLowPtZCR);
   HighPtZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_Z > 200));
   PtWZ10CR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 10));
   PtWZ20CR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 20));
   PtWZ40CR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 40));
   //WZInclusiveNoMETCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusiveNoMET);
   //TopEnrichCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopEnrichCR);
   ZjetEnrichCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZjetEnrichCR);
   //ZFakeElCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZFakeElCR);
   //ZFakeMuCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZFakeMuCR);
   //TopElCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopElCR);
   //TopMuCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passTopMuCR);
 }

 if(doFakeRate[iThread - 1] == 2){
   Inclusive_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passWZInclusiveLoose);
   Signal_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passWZInclusiveLoose * (ProcessEvent.Pt_WZ < 70) * (ProcessEvent.Pt_Z > 100));
   //ZZCR_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passZZCR);
   //TopCR_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passWZInclusiveLoose * ProcessEvent.passTopCR);
   //HighPtWZCR_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passWZInclusiveLoose * ProcessEvent.passHighPtWZCR);
   //LowPtZCR_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passWZInclusiveLoose * ProcessEvent.passLowPtZCR);
   //WZInclusiveNoMETCR_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passWZInclusiveNoMET);
   //TopEnrichCR_Fake->HistPtr(iThread - 1)->FillFullMatrix(par, weight * ProcessEvent.passTopEnrichCR);
 }
}

void ProcessHist::FillTruth(int iThread, double par, double weight, EventWZPolarization ProcessEvent)
{
 TruthInclusive_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive);
 TruthSignal_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passSignalRegion);
 TruthZZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passZZCR);
 TruthTopCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passTopCR);
 TruthHighPtWZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passHighPtWZCR);
 TruthLowPtZCRPolarized_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passWZInclusive * ProcessEvent.passLowPtZCR);
}


void HistsWZPolarization::bookAllProcessHist(ProcessHist* &hist, TString name, TString title, int nbin, double left, double right)
{
 hist = new ProcessHist();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, left, right);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsWZPolarization::bookAllProcessHist(ProcessHist* &hist, TString name, TString title, int nbin, double* xbins)
{
 hist = new ProcessHist();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, xbins);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsWZPolarization::DefineHist(ProcessHist* &hist, TString name, TString title, int nbin, double left, double right)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

//WZQCD and Polarized
 subName = "_Inclusive";
 BookBkgHist(hist->InclusivePolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_SignalPtZ100";
 BookBkgHist(hist->SignalPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_SignalPtWZ";
 BookBkgHist(hist->SignalPtWZPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_ZZCR";
 BookBkgHist(hist->ZZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_TopCR";
 BookBkgHist(hist->TopCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_HighPtWZCR";
 BookBkgHist(hist->HighPtWZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_LowPtWZCR";
 BookBkgHist(hist->LowPtWZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 //subName = "_HighR21CR";
 //BookBkgHist(hist->HighR21CRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 //subName = "_LowR21CR";
 //BookBkgHist(hist->LowR21CRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 //subName = "_LowPtZCR";
 //BookBkgHist(hist->LowPtZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_HighPtZCR";
 BookBkgHist(hist->HighPtZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_PtWZ10CR";
 BookBkgHist(hist->PtWZ10CRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_PtWZ20CR";
 BookBkgHist(hist->PtWZ20CRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_PtWZ40CR";
 BookBkgHist(hist->PtWZ40CRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_SignalNLOPtWZ";
 BookBkgHist(hist->SignalNLOPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_SignalNLOPtZ100";
 BookBkgHist(hist->Signal100NLOPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

//Truth
 subName = "_TruthInclusive";
 BookBkgHist(hist->TruthInclusive_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_TruthSignal";
 BookBkgHist(hist->TruthSignal_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_TruthZZCR";
 BookBkgHist(hist->TruthZZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_TruthTopCR";
 BookBkgHist(hist->TruthTopCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_TruthHighPtWZCR";
 BookBkgHist(hist->TruthHighPtWZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

 subName = "_TruthLowPtZCR";
 BookBkgHist(hist->TruthLowPtZCRPolarized_bkg, "WZPolarized", name, title, nbin, left, right);

//Data
 subName = "_DataInclusive";
 BookHist(hist->Inclusive_Data, name, title, nbin, left, right);

 subName = "_DataSignalPtZ100";
 BookHist(hist->Signal_Data, name, title, nbin, left, right);

 subName = "_DataSignalPtWZ";
 BookHist(hist->SignalPtWZ_Data, name, title, nbin, left, right);

 subName = "_DataZZCR";
 BookHist(hist->ZZCRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataTopCR";
 BookHist(hist->TopCRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataHighPtWZCR";
 BookHist(hist->HighPtWZCRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataLowPtWZCR";
 BookHist(hist->LowPtWZCRPolarized_Data, name, title, nbin, left, right);

 //subName = "_DataHighR21CR";
 //BookHist(hist->HighR21CRPolarized_Data, name, title, nbin, left, right);

 //subName = "_DataLowR21CR";
 //BookHist(hist->LowR21CRPolarized_Data, name, title, nbin, left, right);

 //subName = "_DataLowPtZCR";
 //BookHist(hist->LowPtZCRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataHighPtZCR";
 BookHist(hist->HighPtZCRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataPtWZ10CR";
 BookHist(hist->PtWZ10CRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataPtWZ20CR";
 BookHist(hist->PtWZ20CRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataPtWZ40CR";
 BookHist(hist->PtWZ40CRPolarized_Data, name, title, nbin, left, right);

 subName = "_DataTopEnrichCR";
 BookHist(hist->TopEnrichCR_Data, name, title, nbin, left, right);

 subName = "_DataZjetEnrichCR";
 BookHist(hist->ZjetEnrichCR_Data, name, title, nbin, left, right);

 //subName = "_DataZFakeElCR";
 //BookHist(hist->ZFakeElCR_Data, name, title, nbin, left, right);

 //subName = "_DataZFakeMuCR";
 //BookHist(hist->ZFakeMuCR_Data, name, title, nbin, left, right);

 //subName = "_DataTopElCR";
 //BookHist(hist->TopElCR_Data, name, title, nbin, left, right);

 //subName = "_DataTopMuCR";
 //BookHist(hist->TopMuCR_Data, name, title, nbin, left, right);

//Fake
 if(doFakeRate){
   subName = "_Inclusive";
   BookFakeHist(hist->Inclusive_Fake, name, title, nbin, left, right);

   subName = "_SignalPtZ100";
   BookFakeHist(hist->Signal_Fake, name, title, nbin, left, right);

   subName = "_SignalPtWZ";
   BookFakeHist(hist->SignalPtWZ_Fake, name, title, nbin, left, right);

   subName = "_ZZCR";
   BookFakeHist(hist->ZZCR_Fake, name, title, nbin, left, right);

   //subName = "_TopCR";
   //BookFakeHist(hist->TopCR_Fake, name, title, nbin, left, right);

   subName = "_HighPtWZCR";
   BookFakeHist(hist->HighPtWZCR_Fake, name, title, nbin, left, right);

   subName = "_LowPtWZCR";
   BookFakeHist(hist->LowPtWZCR_Fake, name, title, nbin, left, right);

   //subName = "_HighR21CR";
   //BookFakeHist(hist->HighR21CR_Fake, name, title, nbin, left, right);

   //subName = "_LowR21CR";
   //BookFakeHist(hist->LowR21CR_Fake, name, title, nbin, left, right);

   //subName = "_LowPtZCR";
   //BookFakeHist(hist->LowPtZCR_Fake, name, title, nbin, left, right);

   subName = "_HighPtZCR";
   BookFakeHist(hist->HighPtZCR_Fake, name, title, nbin, left, right);

   subName = "_PtWZ10CR";
   BookFakeHist(hist->PtWZ10CR_Fake, name, title, nbin, left, right);

   subName = "_PtWZ20CR";
   BookFakeHist(hist->PtWZ20CR_Fake, name, title, nbin, left, right);

   subName = "_PtWZ40CR";
   BookFakeHist(hist->PtWZ40CR_Fake, name, title, nbin, left, right);

   //subName = "_WZInclusiveNoMETCR";
   //BookFakeHist(hist->WZInclusiveNoMETCR_Fake, name, title, nbin, left, right);

   //subName = "_ZFakeElCR";
   //BookFakeHist(hist->ZFakeElCR_Fake, name, title, nbin, left, right);

   //subName = "_ZFakeMuCR";
   //BookFakeHist(hist->ZFakeMuCR_Fake, name, title, nbin, left, right);

   //subName = "_TopEnrichCR";
   //BookFakeHist(hist->TopEnrichCR_Fake, name, title, nbin, left, right);

   subName = "_ZjetEnrichCR";
   BookFakeHist(hist->ZjetEnrichCR_Fake, name, title, nbin, left, right);

   //subName = "_TopElCR";
   //BookFakeHist(hist->TopElCR_Fake, name, title, nbin, left, right);

   //subName = "_TopMuCR";
   //BookFakeHist(hist->TopMuCR_Fake, name, title, nbin, left, right);
 }

//WZQCD systematic
/* if(!OnlyNominal){
   subName = "_Inclusive";
   BookSysHist(hist->InclusivePolarized_sys, SysNameSignalWZ, name, title, nbin, left, right);

   subName = "_Signal";
   BookSysHist(hist->SignalPolarized_sys, SysNameSignalWZ, name, title, nbin, left, right);

   subName = "_ZZCR";
   BookSysHist(hist->ZZCRPolarized_sys, SysNameSignalWZ, name, title, nbin, left, right);

   subName = "_TopCR";
   BookSysHist(hist->TopCRPolarized_sys, SysNameSignalWZ, name, title, nbin, left, right);

   subName = "_HighPtWZCR";
   BookSysHist(hist->HighPtWZCRPolarized_sys, SysNameSignalWZ, name, title, nbin, left, right);

   subName = "_LowPtZCR";
   BookSysHist(hist->LowPtZCRPolarized_sys, SysNameSignalWZ, name, title, nbin, left, right);
 }
*/
//All Bkg
 if(doBkg){
   subName = "_Inclusive";
   BookBkgHist(hist->Inclusive_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_SignalPtZ100";
   BookBkgHist(hist->Signal_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_SignalPtWZ";
   BookBkgHist(hist->SignalPtWZ_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_ZZCR";
   BookBkgHist(hist->ZZCR_bkg, "ZZControlRegion", name, title, nbin, left, right);

   subName = "_TopCR";
   BookBkgHist(hist->TopCR_bkg, "TopControlRegion", name, title, nbin, left, right);

   subName = "_HighPtWZCR";
   BookBkgHist(hist->HighPtWZCR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_LowPtWZCR";
   BookBkgHist(hist->LowPtWZCR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_HighR21CR";
   //BookBkgHist(hist->HighR21CR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_LowR21CR";
   //BookBkgHist(hist->LowR21CR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_LowPtZCR";
   //BookBkgHist(hist->LowPtZCR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_HighPtZCR";
   BookBkgHist(hist->HighPtZCR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_PtWZ10CR";
   BookBkgHist(hist->PtWZ10CR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_PtWZ20CR";
   BookBkgHist(hist->PtWZ20CR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_PtWZ40CR";
   BookBkgHist(hist->PtWZ40CR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_WZInclusiveNoMETCR";
   BookBkgHist(hist->WZInclusiveNoMETCR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_ZFakeElCR";
   //BookBkgHist(hist->ZFakeElCR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_ZFakeMuCR";
   //BookBkgHist(hist->ZFakeMuCR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_TopEnrichCR";
   BookBkgHist(hist->TopEnrichCR_bkg, "SignalWZ", name, title, nbin, left, right);

   subName = "_ZjetEnrichCR";
   BookBkgHist(hist->ZjetEnrichCR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_TopElCR";
   //BookBkgHist(hist->TopElCR_bkg, "SignalWZ", name, title, nbin, left, right);

   //subName = "_TopMuCR";
   //BookBkgHist(hist->TopMuCR_bkg, "SignalWZ", name, title, nbin, left, right);
 }


}

void HistsWZPolarization::DefineHist(ProcessHist* &hist, TString name, TString title, int nbin, double* xbins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

//WZQCD and Polarized
 subName = "_Inclusive";
 BookBkgHist(hist->InclusivePolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_SignalPtZ100";
 BookBkgHist(hist->SignalPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_SignalPtWZ";
 BookBkgHist(hist->SignalPtWZPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_ZZCR";
 BookBkgHist(hist->ZZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_TopCR";
 BookBkgHist(hist->TopCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_HighPtWZCR";
 BookBkgHist(hist->HighPtWZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_LowPtWZCR";
 BookBkgHist(hist->LowPtWZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 //subName = "_HighR21CR";
 //BookBkgHist(hist->HighR21CRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 //subName = "_LowR21CR";
 //BookBkgHist(hist->LowR21CRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 //subName = "_LowPtZCR";
 //BookBkgHist(hist->LowPtZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_HighPtZCR";
 BookBkgHist(hist->HighPtZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_PtWZ10CR";
 BookBkgHist(hist->PtWZ10CRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_PtWZ20CR";
 BookBkgHist(hist->PtWZ20CRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_PtWZ40CR";
 BookBkgHist(hist->PtWZ40CRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_SignalNLOPtWZ";
 BookBkgHist(hist->SignalNLOPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_SignalNLOPtZ100";
 BookBkgHist(hist->Signal100NLOPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

//Truth
 subName = "_TruthInclusive";
 BookBkgHist(hist->TruthInclusive_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_TruthSignal";
 BookBkgHist(hist->TruthSignal_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_TruthZZCR";
 BookBkgHist(hist->TruthZZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_TruthTopCR";
 BookBkgHist(hist->TruthTopCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_TruthHighPtWZCR";
 BookBkgHist(hist->TruthHighPtWZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

 subName = "_TruthLowPtZCR";
 BookBkgHist(hist->TruthLowPtZCRPolarized_bkg, "WZPolarized", name, title, nbin, xbins);

//Data
 subName = "_DataInclusive";
 BookHist(hist->Inclusive_Data, name, title, nbin, xbins);

 subName = "_DataSignalPtZ100";
 BookHist(hist->Signal_Data, name, title, nbin, xbins);

 subName = "_DataSignalPtWZ";
 BookHist(hist->SignalPtWZ_Data, name, title, nbin, xbins);

 subName = "_DataZZCR";
 BookHist(hist->ZZCRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataTopCR";
 BookHist(hist->TopCRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataHighPtWZCR";
 BookHist(hist->HighPtWZCRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataLowPtWZCR";
 BookHist(hist->LowPtWZCRPolarized_Data, name, title, nbin, xbins);

 //subName = "_DataHighR21CR";
 //BookHist(hist->HighR21CRPolarized_Data, name, title, nbin, xbins);

 //subName = "_DataLowR21CR";
 //BookHist(hist->LowR21CRPolarized_Data, name, title, nbin, xbins);

 //subName = "_DataLowPtZCR";
 //BookHist(hist->LowPtZCRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataHighPtZCR";
 BookHist(hist->HighPtZCRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataPtWZ10CR";
 BookHist(hist->PtWZ10CRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataPtWZ20CR";
 BookHist(hist->PtWZ20CRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataPtWZ40CR";
 BookHist(hist->PtWZ40CRPolarized_Data, name, title, nbin, xbins);

 subName = "_DataTopEnrichCR";
 BookHist(hist->TopEnrichCR_Data, name, title, nbin, xbins);

 subName = "_DataZjetEnrichCR";
 BookHist(hist->ZjetEnrichCR_Data, name, title, nbin, xbins);

 //subName = "_DataZFakeElCR";
 //BookHist(hist->ZFakeElCR_Data, name, title, nbin, xbins);

 //subName = "_DataZFakeMuCR";
 //BookHist(hist->ZFakeMuCR_Data, name, title, nbin, xbins);

 //subName = "_DataTopElCR";
 //BookHist(hist->TopElCR_Data, name, title, nbin, xbins);

 //subName = "_DataTopMuCR";
 //BookHist(hist->TopMuCR_Data, name, title, nbin, xbins);

//Fake
 if(doFakeRate){
   subName = "_Inclusive";
   BookFakeHist(hist->Inclusive_Fake, name, title, nbin, xbins);

   subName = "_SignalPtZ100";
   BookFakeHist(hist->Signal_Fake, name, title, nbin, xbins);

   subName = "_SignalPtWZ";
   BookFakeHist(hist->SignalPtWZ_Fake, name, title, nbin, xbins);

   subName = "_ZZCR";
   BookFakeHist(hist->ZZCR_Fake, name, title, nbin, xbins);

   //subName = "_TopCR";
   //BookFakeHist(hist->TopCR_Fake, name, title, nbin, xbins);

   subName = "_HighPtWZCR";
   BookFakeHist(hist->HighPtWZCR_Fake, name, title, nbin, xbins);

   subName = "_LowPtWZCR";
   BookFakeHist(hist->LowPtWZCR_Fake, name, title, nbin, xbins);

   //subName = "_HighR21CR";
   //BookFakeHist(hist->HighR21CR_Fake, name, title, nbin, xbins);

   //subName = "_LowR21CR";
   //BookFakeHist(hist->LowR21CR_Fake, name, title, nbin, xbins);

   //subName = "_LowPtZCR";
   //BookFakeHist(hist->LowPtZCR_Fake, name, title, nbin, xbins);

   subName = "_HighPtZCR";
   BookFakeHist(hist->HighPtZCR_Fake, name, title, nbin, xbins);

   subName = "_PtWZ10CR";
   BookFakeHist(hist->PtWZ10CR_Fake, name, title, nbin, xbins);

   subName = "_PtWZ20CR";
   BookFakeHist(hist->PtWZ20CR_Fake, name, title, nbin, xbins);

   subName = "_PtWZ40CR";
   BookFakeHist(hist->PtWZ40CR_Fake, name, title, nbin, xbins);

   //subName = "_WZInclusiveNoMETCR";
   //BookFakeHist(hist->WZInclusiveNoMETCR_Fake, name, title, nbin, xbins);

   //subName = "_ZFakeElCR";
   //BookFakeHist(hist->ZFakeElCR_Fake, name, title, nbin, xbins);

   //subName = "_ZFakeMuCR";
   //BookFakeHist(hist->ZFakeMuCR_Fake, name, title, nbin, xbins);

   //subName = "_TopEnrichCR";
   //BookFakeHist(hist->TopEnrichCR_Fake, name, title, nbin, xbins);

   subName = "_ZjetEnrichCR";
   BookFakeHist(hist->ZjetEnrichCR_Fake, name, title, nbin, xbins);

   //subName = "_TopElCR";
   //BookFakeHist(hist->TopElCR_Fake, name, title, nbin, xbins);

   //subName = "_TopMuCR";
   //BookFakeHist(hist->TopMuCR_Fake, name, title, nbin, xbins);
 }

//WZQCD systematic
/* if(!OnlyNominal){
   subName = "_Inclusive";
   BookSysHist(hist->InclusivePolarized_sys, SysNameSignalWZ, name, title, nbin, xbins);

   subName = "_Signal";
   BookSysHist(hist->SignalPolarized_sys, SysNameSignalWZ, name, title, nbin, xbins);

   subName = "_ZZCR";
   BookSysHist(hist->ZZCRPolarized_sys, SysNameSignalWZ, name, title, nbin, xbins);

   subName = "_TopCR";
   BookSysHist(hist->TopCRPolarized_sys, SysNameSignalWZ, name, title, nbin, xbins);

   subName = "_HighPtWZCR";
   BookSysHist(hist->HighPtWZCRPolarized_sys, SysNameSignalWZ, name, title, nbin, xbins);

   subName = "_LowPtZCR";
   BookSysHist(hist->LowPtZCRPolarized_sys, SysNameSignalWZ, name, title, nbin, xbins);
 }
*/
//All Bkg
 if(doBkg){
   subName = "_Inclusive";
   BookBkgHist(hist->Inclusive_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_SignalPtZ100";
   BookBkgHist(hist->Signal_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_SignalPtWZ";
   BookBkgHist(hist->SignalPtWZ_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_ZZCR";
   BookBkgHist(hist->ZZCR_bkg, "ZZControlRegion", name, title, nbin, xbins);

   subName = "_TopCR";
   BookBkgHist(hist->TopCR_bkg, "TopControlRegion", name, title, nbin, xbins);

   subName = "_HighPtWZCR";
   BookBkgHist(hist->HighPtWZCR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_LowPtWZCR";
   BookBkgHist(hist->LowPtWZCR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_HighR21CR";
   //BookBkgHist(hist->HighR21CR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_LowR21CR";
   //BookBkgHist(hist->LowR21CR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_LowPtZCR";
   //BookBkgHist(hist->LowPtZCR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_HighPtZCR";
   BookBkgHist(hist->HighPtZCR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_PtWZ10CR";
   BookBkgHist(hist->PtWZ10CR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_PtWZ20CR";
   BookBkgHist(hist->PtWZ20CR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_PtWZ40CR";
   BookBkgHist(hist->PtWZ40CR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_WZInclusiveNoMETCR";
   BookBkgHist(hist->WZInclusiveNoMETCR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_ZFakeElCR";
   //BookBkgHist(hist->ZFakeElCR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_ZFakeMuCR";
   //BookBkgHist(hist->ZFakeMuCR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_TopEnrichCR";
   BookBkgHist(hist->TopEnrichCR_bkg, "SignalWZ", name, title, nbin, xbins);

   subName = "_ZjetEnrichCR";
   BookBkgHist(hist->ZjetEnrichCR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_TopElCR";
   //BookBkgHist(hist->TopElCR_bkg, "SignalWZ", name, title, nbin, xbins);

   //subName = "_TopMuCR";
   //BookBkgHist(hist->TopMuCR_bkg, "SignalWZ", name, title, nbin, xbins);
 }

}

void ProcessHist::ResetHist()
{
 cout<<"Reset "<<HistName<<endl;

 InclusivePolarized_bkg->Reset();
 SignalPolarized_bkg->Reset();
 SignalPtWZPolarized_bkg->Reset();
 ZZCRPolarized_bkg->Reset();
 TopCRPolarized_bkg->Reset();
 HighPtWZCRPolarized_bkg->Reset();
 LowPtWZCRPolarized_bkg->Reset();
 //HighR21CRPolarized_bkg->Reset();
 //LowR21CRPolarized_bkg->Reset();
 //LowPtZCRPolarized_bkg->Reset();
 HighPtZCRPolarized_bkg->Reset();
 PtWZ10CRPolarized_bkg->Reset();
 PtWZ20CRPolarized_bkg->Reset();
 PtWZ40CRPolarized_bkg->Reset();
 SignalNLOPolarized_bkg->Reset();
 Signal100NLOPolarized_bkg->Reset();

 TruthInclusive_bkg->Reset();
 TruthSignal_bkg->Reset();
 TruthZZCRPolarized_bkg->Reset();
 TruthTopCRPolarized_bkg->Reset();
 TruthHighPtWZCRPolarized_bkg->Reset();
 TruthLowPtZCRPolarized_bkg->Reset();

 Inclusive_Data->Reset();
 Signal_Data->Reset();
 SignalPtWZ_Data->Reset();
 ZZCRPolarized_Data->Reset();
 TopCRPolarized_Data->Reset();
 HighPtWZCRPolarized_Data->Reset();
 LowPtWZCRPolarized_Data->Reset();
 //HighR21CRPolarized_Data->Reset();
 //LowR21CRPolarized_Data->Reset();
 //LowPtZCRPolarized_Data->Reset();
 HighPtZCRPolarized_Data->Reset();
 PtWZ10CRPolarized_Data->Reset();
 PtWZ20CRPolarized_Data->Reset();
 PtWZ40CRPolarized_Data->Reset();
 TopEnrichCR_Data->Reset();
 ZjetEnrichCR_Data->Reset();
 //ZFakeElCR_Data->Reset();
 //ZFakeMuCR_Data->Reset();
 //TopElCR_Data->Reset();
 //TopMuCR_Data->Reset();

 if(doFakeRate[0]){
   Inclusive_Fake->Reset();
   Signal_Fake->Reset();
   SignalPtWZ_Fake->Reset();
   ZZCR_Fake->Reset();
   //TopCR_Fake->Reset();
   HighPtWZCR_Fake->Reset();
   LowPtWZCR_Fake->Reset();
   //HighR21CR_Fake->Reset();
   //LowR21CR_Fake->Reset();
   //LowPtZCR_Fake->Reset();
   HighPtZCR_Fake->Reset();
   PtWZ10CR_Fake->Reset();
   PtWZ20CR_Fake->Reset();
   PtWZ40CR_Fake->Reset();
   //WZInclusiveNoMETCR_Fake->Reset();
   //ZFakeElCR_Fake->Reset();
   //ZFakeMuCR_Fake->Reset();
   //TopEnrichCR_Fake->Reset();
   ZjetEnrichCR_Fake->Reset();
   //TopElCR_Fake->Reset();
   //TopMuCR_Fake->Reset();
 }

 if(doBkg[0]){
   Inclusive_bkg->Reset();
   Signal_bkg->Reset();
   SignalPtWZ_bkg->Reset();
   ZZCR_bkg->Reset();
   TopCR_bkg->Reset();
   HighPtWZCR_bkg->Reset();
   LowPtWZCR_bkg->Reset();
   //HighR21CR_bkg->Reset();
   //LowR21CR_bkg->Reset();
   //LowPtZCR_bkg->Reset();
   HighPtZCR_bkg->Reset();
   PtWZ10CR_bkg->Reset();
   PtWZ20CR_bkg->Reset();
   PtWZ40CR_bkg->Reset();
   WZInclusiveNoMETCR_bkg->Reset();
   //ZFakeElCR_bkg->Reset();
   //ZFakeMuCR_bkg->Reset();
   TopEnrichCR_bkg->Reset();
   //TopElCR_bkg->Reset();
   //TopMuCR_bkg->Reset();
 }

/* if(!OnlyNominal[0]){//Systematic plot
   InclusivePolarized_sys->Reset();
   SignalPolarized_sys->Reset();
   ZZCRPolarized_sys->Reset();
   TopCRPolarized_sys->Reset();
   HighPtWZCRPolarized_sys->Reset();
   LowPtZCRPolarized_sys->Reset();
 } 
*/

}

void ProcessHist::InputReweightingFactor(int iThread, double weight)
{
 this->ReweightingFactor[iThread - 1] = weight;

 InclusivePolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 SignalPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 SignalPtWZPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 ZZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 TopCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 HighPtWZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 LowPtWZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 //HighR21CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 //LowR21CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 //LowPtZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 HighPtZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 PtWZ10CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 PtWZ20CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 PtWZ40CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);


/* InclusivePolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor);
 SignalPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_Signal);
 SignalPtWZPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_SignalPtWZ);
 ZZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_ZZCR);
 TopCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 HighPtWZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_HighPtWZCR);
 LowPtWZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_LowPtWZCR);
 HighR21CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_HighR21CR);
 LowR21CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_LowR21CR);
 LowPtZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 HighPtZCRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(NLOKFactor_HighPtZCR);
 PtWZ10CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 PtWZ20CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
 PtWZ40CRPolarized_bkg->HistPtr(iThread - 1)->InputKFactor(weight);
*/

}

void ProcessHist::GetFinalData()
{
 if(doBkg[0] && doFakeRate[0]){

   if(SystematicName == "FakeBkg_20per__1down"){
     ChangeHistPercentErr(Inclusive_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
     ChangeHistPercentErr(SignalPtWZ_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
     ChangeHistPercentErr(Signal_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
     ChangeHistPercentErr(PtWZ10CR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
     ChangeHistPercentErr(PtWZ20CR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
     ChangeHistPercentErr(PtWZ40CR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
     ChangeHistPercentErr(LowPtWZCR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Down");
   }
   else if(SystematicName == "FakeBkg_20per__1up"){
     ChangeHistPercentErr(Inclusive_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
     ChangeHistPercentErr(SignalPtWZ_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
     ChangeHistPercentErr(Signal_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
     ChangeHistPercentErr(PtWZ10CR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
     ChangeHistPercentErr(PtWZ20CR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
     ChangeHistPercentErr(PtWZ40CR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
     ChangeHistPercentErr(LowPtWZCR_Fake->HistPtr(0)->FinalFakeHist, 0.2, "Up");
   }

   //Final Data (Data - Bkg)

   Inclusive_FinalData = (TH1D *)Inclusive_Data->HistPtr(0)->Clone(HistName + "_Inclusive_FinalData");
   Inclusive_FinalData->Add(Inclusive_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   Inclusive_FinalData->Add(Inclusive_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   Inclusive_FinalData->Add(Inclusive_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   Inclusive_FinalData->Add(Inclusive_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   Inclusive_FinalData->Add(Inclusive_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   Inclusive_FinalData->Add(Inclusive_Fake->HistPtr(0)->FinalFakeHist, -1);

   Signal_FinalData = (TH1D *)SignalPtWZ_Data->HistPtr(0)->Clone(HistName + "_Signal_FinalData");
   Signal_FinalData->Add(SignalPtWZ_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   Signal_FinalData->Add(SignalPtWZ_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   Signal_FinalData->Add(SignalPtWZ_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   Signal_FinalData->Add(SignalPtWZ_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   Signal_FinalData->Add(SignalPtWZ_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   Signal_FinalData->Add(SignalPtWZ_Fake->HistPtr(0)->FinalFakeHist, -1);

/*   HighPtWZCR_FinalData = (TH1D *)HighPtWZCRPolarized_Data->HistPtr(0)->Clone(HistName + "_HighPtWZCR_FinalData");
   HighPtWZCR_FinalData->Add(HighPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   HighPtWZCR_FinalData->Add(HighPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   HighPtWZCR_FinalData->Add(HighPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   HighPtWZCR_FinalData->Add(HighPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   HighPtWZCR_FinalData->Add(HighPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   HighPtWZCR_FinalData->Add(HighPtWZCR_Fake->HistPtr(0)->FinalFakeHist, -1);

   LowPtZCR_FinalData = (TH1D *)LowPtZCRPolarized_Data->HistPtr(0)->Clone(HistName + "_LowPtZCR_FinalData");
   LowPtZCR_FinalData->Add(LowPtZCR_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   LowPtZCR_FinalData->Add(LowPtZCR_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   LowPtZCR_FinalData->Add(LowPtZCR_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   LowPtZCR_FinalData->Add(LowPtZCR_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   LowPtZCR_FinalData->Add(LowPtZCR_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   LowPtZCR_FinalData->Add(LowPtZCR_Fake->HistPtr(0)->FinalFakeHist, -1);
*/

   Inclusive_FinalData->Write();
   Signal_FinalData->Write();
// HighPtWZCR_FinalData->Write();
// LowPtZCR_FinalData->Write();

   //Final TT (Data - Bkg - LL - LT - TL)
   PtWZ10CR_FinalTT = (TH1D *)PtWZ10CRPolarized_Data->HistPtr(0)->Clone(HistName + "_PtWZ10CR_FinalTT");
   PtWZ10CR_FinalTT->Add(PtWZ10CR_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CR_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CR_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CR_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CR_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CR_Fake->HistPtr(0)->FinalFakeHist, -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CRPolarized_bkg->HistPtr(0)->GetHistPtr("LL"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CRPolarized_bkg->HistPtr(0)->GetHistPtr("LT"), -1);
   PtWZ10CR_FinalTT->Add(PtWZ10CRPolarized_bkg->HistPtr(0)->GetHistPtr("TL"), -1);

   PtWZ20CR_FinalTT = (TH1D *)PtWZ20CRPolarized_Data->HistPtr(0)->Clone(HistName + "_PtWZ20CR_FinalTT");
   PtWZ20CR_FinalTT->Add(PtWZ20CR_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CR_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CR_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CR_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CR_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CR_Fake->HistPtr(0)->FinalFakeHist, -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CRPolarized_bkg->HistPtr(0)->GetHistPtr("LL"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CRPolarized_bkg->HistPtr(0)->GetHistPtr("LT"), -1);
   PtWZ20CR_FinalTT->Add(PtWZ20CRPolarized_bkg->HistPtr(0)->GetHistPtr("TL"), -1);

   PtWZ40CR_FinalTT = (TH1D *)PtWZ40CRPolarized_Data->HistPtr(0)->Clone(HistName + "_PtWZ40CR_FinalTT");
   PtWZ40CR_FinalTT->Add(PtWZ40CR_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CR_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CR_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CR_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CR_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CR_Fake->HistPtr(0)->FinalFakeHist, -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CRPolarized_bkg->HistPtr(0)->GetHistPtr("LL"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CRPolarized_bkg->HistPtr(0)->GetHistPtr("LT"), -1);
   PtWZ40CR_FinalTT->Add(PtWZ40CRPolarized_bkg->HistPtr(0)->GetHistPtr("TL"), -1);

   LowPtWZCR_FinalTT = (TH1D *)LowPtWZCRPolarized_Data->HistPtr(0)->Clone(HistName + "_LowPtWZCR_FinalTT");
   LowPtWZCR_FinalTT->Add(LowPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgZZ"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgVVV"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgWZEW"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgttbarV"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCR_bkg->HistPtr(0)->GetHistPtr("BkgtZ"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCR_Fake->HistPtr(0)->FinalFakeHist, -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCRPolarized_bkg->HistPtr(0)->GetHistPtr("LL"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCRPolarized_bkg->HistPtr(0)->GetHistPtr("LT"), -1);
   LowPtWZCR_FinalTT->Add(LowPtWZCRPolarized_bkg->HistPtr(0)->GetHistPtr("TL"), -1);

   PtWZ10CR_FinalTT->Write();
   PtWZ20CR_FinalTT->Write();
   PtWZ40CR_FinalTT->Write();
   LowPtWZCR_FinalTT->Write();
 }

}

#endif
