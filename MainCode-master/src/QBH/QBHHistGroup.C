#ifndef WZPol_QBHHistGroup_cxx
#define WZPol_QBHHistGroup_cxx
#include "QBH/HistsQBH.h"

using namespace std;

QBHHistGroup::QBHHistGroup()
{
}

void QBHHistGroup::Initial(int iThread, TString MCType)
{
 if(MCType == "data") isData[iThread - 1] = true;
}

void QBHHistGroup::Fill(int iThread, double par, double weight, EventQBH ProcessEvent)
{
 Inclusive_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passInclusive);
 FakeCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passFakeCR);
 WCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passWCR);
 WVR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passWVR);
 ZCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passZCR);
 ZVR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passZVR);
 TCR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passTCR);
 TVR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passTVR);
 SR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passSR);
 SVR_bkg->HistPtr(iThread - 1)->Fill(par, weight * ProcessEvent.passLeadingLepTight * ProcessEvent.passSVR);

 Inclusive_Loose_bkg->HistPtr(iThread - 1)->Fill(par, ProcessEvent.TotalWeightLoose);

 if(isData[iThread - 1]){
   double FakeFactor = 0.0;

   if(fabs(ProcessEvent.RealEff - ProcessEvent.FakeEff) > 1e-10){
     FakeFactor = (ProcessEvent.FakeEff / (ProcessEvent.RealEff - ProcessEvent.FakeEff))
                * (ProcessEvent.RealEff - ProcessEvent.passLeadingLepTight);
   }

   Inclusive_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passInclusive);
   FakeCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passFakeCR);
   WCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passWCR);
   WVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passWVR);
   ZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passZCR);
   ZVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passZVR);
   TCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passTCR);
   TVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passTVR);
   SR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passSR);
   SVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passSVR);
 }

}

void QBHHistGroup::FillFake(int iThread, double par, double weight, EventQBH ProcessEvent)
{
 double FakeFactor = 0.0;

 if(fabs(ProcessEvent.RealEff - ProcessEvent.FakeEff) > 1e-10){
   FakeFactor = (ProcessEvent.FakeEff / (ProcessEvent.RealEff - ProcessEvent.FakeEff))
              * (ProcessEvent.RealEff - ProcessEvent.passLeadingLepTight);
 }

 Inclusive_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passInclusive);
 FakeCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passFakeCR);
 WCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passWCR);
 WVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passWVR);
 ZCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passZCR);
 ZVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passZVR);
 TCR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passTCR);
 TVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passTVR);
 SR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passSR);
 SVR_Fake->HistPtr(iThread - 1)->Fill(par, weight * FakeFactor * ProcessEvent.passSVR);

}

void HistsQBH::bookAllProcessHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double left, double right)
{
 hist = new QBHHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, left, right);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsQBH::bookAllProcessHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 hist = new QBHHistGroup();
 hist->fHist = this;
 hist->SystematicName = SystematicName;
 DefineHist(hist, name, title, nbin, xbins);

 hist->HistName = name;
 hist->TotalThread = this->TotalThread;
 hist_process.push_back(hist);

 HistNames.push_back(name);
}

void HistsQBH::DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double left, double right)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_Inclusive";
 BookBkgHist(hist->Inclusive_bkg, "QBH", name, title, nbin, left, right);

 subName = "_FakeCR";
 BookBkgHist(hist->FakeCR_bkg, "QBH", name, title, nbin, left, right);

 subName = "_WCR";
 BookBkgHist(hist->WCR_bkg, "QBH", name, title, nbin, left, right);

 subName = "_WVR";
 BookBkgHist(hist->WVR_bkg, "QBH", name, title, nbin, left, right);

 subName = "_ZCR";
 BookBkgHist(hist->ZCR_bkg, "QBH", name, title, nbin, left, right);
 
 subName = "_ZVR";
 BookBkgHist(hist->ZVR_bkg, "QBH", name, title, nbin, left, right);

 subName = "_TCR";
 BookBkgHist(hist->TCR_bkg, "QBH", name, title, nbin, left, right);
 
 subName = "_TVR";
 BookBkgHist(hist->TVR_bkg, "QBH", name, title, nbin, left, right);

 subName = "_SR";
 BookBkgHist(hist->SR_bkg, "QBH", name, title, nbin, left, right);
 
 subName = "_SVR";
 BookBkgHist(hist->SVR_bkg, "QBH", name, title, nbin, left, right);

 subName = "_Inclusive_Fake";
 BookHist(hist->Inclusive_Fake, name, title, nbin, left, right);

 subName = "_FakeCR_Fake";
 BookHist(hist->FakeCR_Fake, name, title, nbin, left, right);

 subName = "_WCR_Fake";
 BookHist(hist->WCR_Fake, name, title, nbin, left, right);

 subName = "_WVR_Fake";
 BookHist(hist->WVR_Fake, name, title, nbin, left, right);

 subName = "_ZCR_Fake";
 BookHist(hist->ZCR_Fake, name, title, nbin, left, right);

 subName = "_ZVR_Fake";
 BookHist(hist->ZVR_Fake, name, title, nbin, left, right);

 subName = "_TCR_Fake";
 BookHist(hist->TCR_Fake, name, title, nbin, left, right);

 subName = "_TVR_Fake";
 BookHist(hist->TVR_Fake, name, title, nbin, left, right);

 subName = "_SR_Fake";
 BookHist(hist->SR_Fake, name, title, nbin, left, right);

 subName = "_SVR_Fake";
 BookHist(hist->SVR_Fake, name, title, nbin, left, right);

 subName = "_Inclusive_Loose";
 BookBkgHist(hist->Inclusive_Loose_bkg, "QBH", name, title, nbin, left, right);

}

void HistsQBH::DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

 subName = "_Inclusive";
 BookBkgHist(hist->Inclusive_bkg, "QBH", name, title, nbin, xbins);

 subName = "_FakeCR";
 BookBkgHist(hist->FakeCR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_WCR";
 BookBkgHist(hist->WCR_bkg, "QBH", name, title, nbin, xbins);
 
 subName = "_WVR";
 BookBkgHist(hist->WVR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_ZCR";
 BookBkgHist(hist->ZCR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_ZVR";
 BookBkgHist(hist->ZVR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_TCR";
 BookBkgHist(hist->TCR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_TVR";
 BookBkgHist(hist->TVR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_SR";
 BookBkgHist(hist->SR_bkg, "QBH", name, title, nbin, xbins);
 
 subName = "_SVR";
 BookBkgHist(hist->SVR_bkg, "QBH", name, title, nbin, xbins);

 subName = "_Inclusive_Fake";
 BookHist(hist->Inclusive_Fake, name, title, nbin, xbins);

 subName = "_FakeCR_Fake";
 BookHist(hist->FakeCR_Fake, name, title, nbin, xbins);

 subName = "_WCR_Fake";
 BookHist(hist->WCR_Fake, name, title, nbin, xbins);

 subName = "_WVR_Fake";
 BookHist(hist->WVR_Fake, name, title, nbin, xbins);

 subName = "_ZCR_Fake";
 BookHist(hist->ZCR_Fake, name, title, nbin, xbins);

 subName = "_ZVR_Fake";
 BookHist(hist->ZVR_Fake, name, title, nbin, xbins);

 subName = "_TCR_Fake";
 BookHist(hist->TCR_Fake, name, title, nbin, xbins);

 subName = "_TVR_Fake";
 BookHist(hist->TVR_Fake, name, title, nbin, xbins);

 subName = "_SR_Fake";
 BookHist(hist->SR_Fake, name, title, nbin, xbins);

 subName = "_SVR_Fake";
 BookHist(hist->SVR_Fake, name, title, nbin, xbins);

 subName = "_Inclusive_Loose";
 BookBkgHist(hist->Inclusive_Loose_bkg, "QBH", name, title, nbin, xbins);

}

void QBHHistGroup::ResetHist()
{
 cout<<"Reset "<<HistName<<endl;

 Inclusive_bkg->Reset();
 FakeCR_bkg->Reset();
 WCR_bkg->Reset();
 WVR_bkg->Reset();
 ZCR_bkg->Reset();
 ZVR_bkg->Reset();
 TCR_bkg->Reset();
 TVR_bkg->Reset();
 SR_bkg->Reset();
 SVR_bkg->Reset();

 Inclusive_Fake->Reset();
 FakeCR_Fake->Reset();
 WCR_Fake->Reset();
 WVR_Fake->Reset();
 ZCR_Fake->Reset();
 ZVR_Fake->Reset();
 TCR_Fake->Reset();
 TVR_Fake->Reset();
 SR_Fake->Reset();
 SVR_Fake->Reset();

 Inclusive_Loose_bkg->Reset();
}

void QBHHistGroup::GetFinalData()
{

}

#endif
