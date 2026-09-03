#include "Analysis/makeHists.h"

void makeHists::BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<TH1D *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new TH1D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);
   h->HistVector.at(i)->Sumw2();
   tail = (TString)"_" + (int)i;
 }

 hist_1d.push_back(h);
}

void makeHists::BookHist(ThreadHist<TH1D *>* &h, TString name, TString title, int nbinx, double* xbins)
{
 h = new ThreadHist<TH1D *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new TH1D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins);
   h->HistVector.at(i)->Sumw2();
   tail = (TString)"_" + (int)i;
 }

 hist_1d.push_back(h);
}

void makeHists::Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 h = new ThreadHist<TH2D *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new TH2D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx, nbiny, lefty, righty);
   h->HistVector.at(i)->Sumw2();
   tail = (TString)"_" + (int)i;
 }

 hist_2d.push_back(h);
}

void makeHists::Book2DHist(ThreadHist<TH2D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 h = new ThreadHist<TH2D *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new TH2D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins, nbiny, ybins);
   h->HistVector.at(i)->Sumw2();
   tail = (TString)"_" + (int)i;
 }

 hist_2d.push_back(h);
}

void makeHists::Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty, int nbinz, double leftz, double rightz)
{
 h = new ThreadHist<TH3D *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new TH3D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx, nbiny, lefty, righty, nbinz, leftz, rightz);
   h->HistVector.at(i)->Sumw2();
   tail = (TString)"_" + (int)i;
 }

 hist_3d.push_back(h);
}

void makeHists::Book3DHist(ThreadHist<TH3D *>* &h, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins, int nbinz, double* zbins)
{
 h = new ThreadHist<TH3D *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new TH3D((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins, nbiny, ybins, nbinz, zbins);
   h->HistVector.at(i)->Sumw2();
   tail = (TString)"_" + (int)i;
 }

 hist_3d.push_back(h);
}

void makeHists::BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<AngularFunction *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new AngularFunction(type, i);
   h->HistVector.at(i)->SetHist((TString)name + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }

 hist_angular.push_back(h);
}

void makeHists::BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double* xbins)
{
 h = new ThreadHist<AngularFunction *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new AngularFunction(type, i);
   h->HistVector.at(i)->SetHist((TString)name + subName + tail, nbinx, xbins);
   tail = (TString)"_" + (int)i;
 }

 hist_angular.push_back(h);
}

void makeHists::BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double* xbins, int nbiny, double* ybins)
{
 h = new ThreadHist<AngularFunction *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new AngularFunction(type, i);
   h->HistVector.at(i)->SetHist((TString)name + subName + tail, nbinx, xbins, nbiny, ybins);
   tail = (TString)"_" + (int)i;
 }

 hist_angular.push_back(h);
}

void makeHists::BookAngularHist(ThreadHist<AngularFunction *>* &h, TString name, TString type, int nbinx, double* xbins, int nbiny, double* ybins, int nbinz, double* zbins)
{
 h = new ThreadHist<AngularFunction *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new AngularFunction(type, i);
   h->HistVector.at(i)->SetHist((TString)name + subName + tail, nbinx, xbins, nbiny, ybins, nbinz, zbins);
   tail = (TString)"_" + (int)i;
 }

 hist_angular.push_back(h);
}

void makeHists::BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<BkgHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new BkgHist(ProcessName);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }

 BkgHist_1d.push_back(h);
}

void makeHists::BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double* xbins)
{
 h = new ThreadHist<BkgHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new BkgHist(ProcessName);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins);
   tail = (TString)"_" + (int)i;
 }

 BkgHist_1d.push_back(h);
}

void makeHists::BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 h = new ThreadHist<BkgHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new BkgHist(ProcessName);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx, nbiny, lefty, righty);
   tail = (TString)"_" + (int)i;
 }

 BkgHist_1d.push_back(h);
}

void makeHists::BookBkgHist(ThreadHist<BkgHist *>* &h, TString ProcessName, TString name, TString title, int nbinx, double* xbins, int nbiny, double* ybins)
{
 h = new ThreadHist<BkgHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new BkgHist(ProcessName);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins, nbiny, ybins);
   tail = (TString)"_" + (int)i;
 }

 BkgHist_1d.push_back(h);
}

void makeHists::BookFakeHist(ThreadHist<FakeHist *>* &h, TString name, TString title, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<FakeHist *>(TotalThread);
 
 TString tail = ""; 
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new FakeHist(); 
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }
 
 FakeHist_1d.push_back(h);
}

void makeHists::BookFakeHist(ThreadHist<FakeHist *>* &h, TString name, TString title, int nbinx, double* xbins)
{
 h = new ThreadHist<FakeHist *>(TotalThread);
 
 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new FakeHist();           
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins);
   tail = (TString)"_" + (int)i;
 }

 FakeHist_1d.push_back(h);
}

void makeHists::BookCovHist(ThreadHist<CovHist *>* &h, TString name, TString title, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<CovHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new CovHist();
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }

 CovHist_1d.push_back(h);
}

void makeHists::BookMultiBinHist(ThreadHist<MultiBinHist *>* &h, vector<vector<double>> MultiBinVector, TString name, TString title, int nbinx, double* xbins)
{
 h = new ThreadHist<MultiBinHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new MultiBinHist(MultiBinVector);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, xbins);
   tail = (TString)"_" + (int)i;
 }

 MultiBinHist_1d.push_back(h);
}

void makeHists::BookResolutionHist(ThreadHist<ResolutionHist *>* &h, TString name, TString type, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<ResolutionHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new ResolutionHist(type, i);
   h->HistVector.at(i)->SetHist((TString)name + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }

 ResolutionHist_1d.push_back(h);
}

void makeHists::BookSysHist(ThreadHist<SysHist *>* &h, vector<TString> sysName, TString name, TString title, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<SysHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new SysHist(sysName);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }

 SysHist_1d.push_back(h);
}

void makeHists::BookMultiWeightHist(ThreadHist<MultiWeightHist *>* &h, int nWeight, TString name, TString title, int nbinx, double leftx, double rightx)
{
 h = new ThreadHist<MultiWeightHist *>(TotalThread);

 TString tail = "";
 for(int i = 0; i < TotalThread; i++){
   h->HistVector.at(i) = new MultiWeightHist(nWeight);
   h->HistVector.at(i)->DefineHist((TString)name + subName + tail, (TString)title + subName + tail, nbinx, leftx, rightx);
   tail = (TString)"_" + (int)i;
 }

 MultiWeightHist_1d.push_back(h);
}

void makeHists::MergeHists()
{
 if(TotalThread == 1){
   HaveMerged = true;
   return;
 }

 if(hist_1d.size() != 0) cout<<"Start to merge the 1D plot."<<endl;
 for(int ihist = 0; ihist < hist_1d.size(); ihist++){
   hist_1d.at(ihist)->Merge();
 }

 if(hist_2d.size() != 0) cout<<"Start to merge the 2D plot."<<endl;
 for(int ihist = 0; ihist < hist_2d.size(); ihist++){
   hist_2d.at(ihist)->Merge();
 }

 if(hist_3d.size() != 0) cout<<"Start to merge the 3D plot."<<endl;
 for(int ihist = 0; ihist < hist_3d.size(); ihist++){
   hist_3d.at(ihist)->Merge();
 }

 if(hist_angular.size() != 0) cout<<"Start to merge the Angular plot."<<endl;
 for(int ihist = 0; ihist < hist_angular.size(); ihist++){ 
   hist_angular.at(ihist)->Merge();
 } 

 if(BkgHist_1d.size() != 0) cout<<"Start to merge the Background plot."<<endl;
 for(int ihist = 0; ihist < BkgHist_1d.size(); ihist++){
   BkgHist_1d.at(ihist)->Merge();
 }

 if(FakeHist_1d.size() != 0) cout<<"Start to merge the Fake plot."<<endl;
 for(int ihist = 0; ihist < FakeHist_1d.size(); ihist++){
   FakeHist_1d.at(ihist)->Merge();
 }

 if(CovHist_1d.size() != 0) cout<<"Start to merge the Covariance plot."<<endl;
 for(int ihist = 0; ihist < CovHist_1d.size(); ihist++){
   CovHist_1d.at(ihist)->Merge();
 }

 if(MultiBinHist_1d.size() != 0) cout<<"Start to merge the MultiBin plot."<<endl;
 for(int ihist = 0; ihist < MultiBinHist_1d.size(); ihist++){
   MultiBinHist_1d.at(ihist)->Merge();
 }

 if(ResolutionHist_1d.size() != 0) cout<<"Start to merge the Resolution plot."<<endl;
 for(int ihist = 0; ihist < ResolutionHist_1d.size(); ihist++){
   ResolutionHist_1d.at(ihist)->Merge();
 }

 if(SysHist_1d.size() != 0) cout<<"Start to merge the Systematic plot."<<endl;
 for(int ihist = 0; ihist < SysHist_1d.size(); ihist++){
   SysHist_1d.at(ihist)->Merge();
 }

 if(MultiWeightHist_1d.size() != 0) cout<<"Start to merge the MultiWeight plot."<<endl;
 for(int ihist = 0; ihist < MultiWeightHist_1d.size(); ihist++){
   MultiWeightHist_1d.at(ihist)->Merge();
 }

 HaveMerged = true;
}

void makeHists::ResetHists()
{
 cout<<"Now, reset the histogram."<<endl;

 if(hist_1d.size() != 0) cout<<"Start to reset the 1D plot."<<endl;
 for(int ihist = 0; ihist < hist_1d.size(); ihist++){
   hist_1d.at(ihist)->Reset();
 }

 if(hist_2d.size() != 0) cout<<"Start to reset the 2D plot."<<endl;
 for(int ihist = 0; ihist < hist_2d.size(); ihist++){
   hist_2d.at(ihist)->Reset();
 }

 if(hist_3d.size() != 0) cout<<"Start to reset the 3D plot."<<endl;
 for(int ihist = 0; ihist < hist_3d.size(); ihist++){
   hist_3d.at(ihist)->Reset();
 }

 if(hist_angular.size() != 0) cout<<"Start to reset the Angular plot."<<endl;
 for(int ihist = 0; ihist < hist_angular.size(); ihist++){
   hist_angular.at(ihist)->Reset();
 }

 if(BkgHist_1d.size() != 0) cout<<"Start to reset the Background plot."<<endl;
 for(int ihist = 0; ihist < BkgHist_1d.size(); ihist++){
   BkgHist_1d.at(ihist)->Reset();
 }

 if(FakeHist_1d.size() != 0) cout<<"Start to reset the Fake plot."<<endl;
 for(int ihist = 0; ihist < FakeHist_1d.size(); ihist++){
   FakeHist_1d.at(ihist)->Reset();
 }

 if(CovHist_1d.size() != 0) cout<<"Start to reset the Covariance plot."<<endl;
 for(int ihist = 0; ihist < CovHist_1d.size(); ihist++){
   CovHist_1d.at(ihist)->Reset();
 }

 if(MultiBinHist_1d.size() != 0) cout<<"Start to reset the MultiBin plot."<<endl;
 for(int ihist = 0; ihist < MultiBinHist_1d.size(); ihist++){
   MultiBinHist_1d.at(ihist)->Reset();
 }

 if(ResolutionHist_1d.size() != 0) cout<<"Start to reset the Resolution plot."<<endl;
 for(int ihist = 0; ihist < ResolutionHist_1d.size(); ihist++){
   ResolutionHist_1d.at(ihist)->Reset();
 }

 if(SysHist_1d.size() != 0) cout<<"Start to reset the Systematic plot."<<endl;
 for(int ihist = 0; ihist < SysHist_1d.size(); ihist++){
   SysHist_1d.at(ihist)->Reset();
 }

 if(MultiWeightHist_1d.size() != 0) cout<<"Start to reset the MultiWeight plot."<<endl;
 for(int ihist = 0; ihist < MultiWeightHist_1d.size(); ihist++){
   MultiWeightHist_1d.at(ihist)->Reset();
 }

}

void makeHists::saveHists()
{
 hf->cd();

 cout<<"Now, save the histogram."<<endl;

 if(hist_1d.size() != 0) cout<<"Start to write the 1D plot."<<endl;
 for(int ihist = 0; ihist < hist_1d.size(); ihist++){
   hist_1d.at(ihist)->Save();
 }

 if(hist_2d.size() != 0) cout<<"Start to write the 2D plot."<<endl;
 for(int ihist = 0; ihist < hist_2d.size(); ihist++){
   hist_2d.at(ihist)->Save();
 }

 if(hist_3d.size() != 0) cout<<"Start to write the 3D plot."<<endl;
 for(int ihist = 0; ihist < hist_3d.size(); ihist++){
   hist_3d.at(ihist)->Save();
 }

 if(hist_angular.size() != 0) cout<<"Start to write the Angular plot."<<endl;
 for(int ihist = 0; ihist < hist_angular.size(); ihist++){
   hist_angular.at(ihist)->HistPtr(0)->GetAngular();
   hist_angular.at(ihist)->Save();
 }

 if(BkgHist_1d.size() != 0) cout<<"Start to write the Background plot."<<endl;
 for(int ihist = 0; ihist < BkgHist_1d.size(); ihist++){
   BkgHist_1d.at(ihist)->Save();
 }

 if(FakeHist_1d.size() != 0) cout<<"Start to write the Fake plot."<<endl;
 for(int ihist = 0; ihist < FakeHist_1d.size(); ihist++){
   cout<<getTime()<<" Save "<<FakeHist_1d.at(ihist)->at(0)->HistName<<" fake plot."<<endl;
   FakeHist_1d.at(ihist)->Save();
 }

 if(CovHist_1d.size() != 0) cout<<"Start to write the Covariance plot."<<endl;
 for(int ihist = 0; ihist < CovHist_1d.size(); ihist++){
   CovHist_1d.at(ihist)->Save();
 }

 if(MultiBinHist_1d.size() != 0) cout<<"Start to write the MultiBin plot."<<endl;
 for(int ihist = 0; ihist < MultiBinHist_1d.size(); ihist++){
   MultiBinHist_1d.at(ihist)->Save();
 }

 if(ResolutionHist_1d.size() != 0) cout<<"Start to write the Resolution plot."<<endl;
 for(int ihist = 0; ihist < ResolutionHist_1d.size(); ihist++){
   ResolutionHist_1d.at(ihist)->HistPtr(0)->FitResolution(false);
   ResolutionHist_1d.at(ihist)->Save();
 }

 if(SysHist_1d.size() != 0) cout<<"Start to write the Systematic plot."<<endl;
 for(int ihist = 0; ihist < SysHist_1d.size(); ihist++){
   SysHist_1d.at(ihist)->Save();
 }

 if(hist_1d.size() != 0 || hist_2d.size() != 0 || hist_3d.size() != 0 || BkgHist_1d.size() != 0) outputInformation();

 hf->Close();

}

