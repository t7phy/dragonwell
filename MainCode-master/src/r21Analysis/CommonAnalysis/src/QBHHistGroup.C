#ifndef WZPol_QBHHistGroup_cxx
#define WZPol_QBHHistGroup_cxx
#include "QBH/HistsQBH.h"

using namespace std;

QBHHistGroup::QBHHistGroup()
{
}

void QBHHistGroup::Initial(int iThread, int MCType)
{

}

void QBHHistGroup::Fill(int iThread, double par, double weight, EventQBH ProcessEvent)
{

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

}

void HistsQBH::DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins)
{
 cout<<getTime()<<" Defining "<<name<<"..."<<endl;

}

void QBHHistGroup::ResetHist()
{
 cout<<"Reset "<<HistName<<endl;

}

void QBHHistGroup::GetFinalData()
{

}

#endif
