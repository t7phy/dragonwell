#include "SpecialHist/SysHist.h"

using namespace std;

SysHist::SysHist(vector<TString> sysName)
{
 this->sysName = sysName;
}

void SysHist::DefineHist(TString name, TString title, int nbin, double left, double right)
{
 this->HistName = name;

 for(int isys = 0; isys < sysName.size(); isys++){
   myHist[isys] = new TH1D(name + "_" + sysName.at(isys), title + "_" + sysName.at(isys), nbin, left, right);
   myHist[isys]->Sumw2();

   SysHist_1d.push_back(myHist[isys]);
 }
}

void SysHist::DefineHist(TString name, TString title, int nbin, double* xbins)
{
 this->HistName = name;

 for(int isys = 0; isys < sysName.size(); isys++){
   myHist[isys] = new TH1D(name + "_" + sysName.at(isys), title + "_" + sysName.at(isys), nbin, xbins);
   myHist[isys]->Sumw2();

   SysHist_1d.push_back(myHist[isys]);
 }
}

void SysHist::Fill(int isys, double par, double weight)
{
 myHist[isys]->Fill(par, weight);
}

void SysHist::DeleteHist()
{
 for(int isys = 0; isys < sysName.size(); isys++){
   cout<<getTime()<<" Delete "<<sysName.at(isys)<<endl;
   delete myHist[isys];
 }
 SysHist_1d.clear();
}

void SysHist::Add(SysHist* hist1)
{
 for(int i = 0; i < SysHist_1d.size(); i++){
   SysHist_1d.at(i)->Add((hist1->SysHist_1d).at(i));
 }
}

void SysHist::Reset()
{
 for(int isys = 0; isys < sysName.size(); isys++){
   myHist[isys]->Reset();
 }
}

void SysHist::Write()
{
 for(int isys = 0; isys < sysName.size(); isys++){
   myHist[isys]->Write();
 }

}
