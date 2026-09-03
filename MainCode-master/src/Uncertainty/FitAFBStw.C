#include "Uncertainty/FitAFBStw.h"

using namespace std;

FitAFBStw::FitAFBStw()
{

}

FitAFBStw::FitAFBStw(const char* cardfile)
{
 string FileLine;
 TString skip;
 int config;
 double config1;

 ifstream infile;
  infile.open(cardfile, ios::in);

//Number of stw input
 infile>>config;
 NStw = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;

//Range of fitting
 infile>>config1;
 left = config1;
 getline(infile, FileLine);
 cout<<config1<<FileLine<<endl;

 infile>>config1;
 right = config1;
 getline(infile, FileLine);
 cout<<config1<<FileLine<<endl;

 step = (right - left) / (NStw - 1);

//FZmass name
 infile>>skip;
 FName = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;

//BZmass name
 infile>>skip;
 BName = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;

//output name
 infile>>skip;
 outputName = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;

//file list
 infile>>skip;
 filelist = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;

//is Rebin
 infile>>config;
 isRebin = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;

 if(isRebin){
   infile>>skip;
   RebinFile = skip;
   getline(infile, FileLine);
   cout<<skip<<FileLine<<endl;
 }
 else if(!isRebin){
   cout<<"Not Rebin"<<endl;
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }
}

void FitAFBStw::Main()
{
 TString saveName = outputName;

 ifstream AFBfile;
  AFBfile.open(filelist, ios::in);

 TString rootName;

 double* xbins = new double[50];
 double BinEdge;
 int BinNumber = 0;
 int size = 1;

 if(isRebin){
   ifstream binning;
     binning.open(RebinFile, ios::in);

   while(binning>>BinEdge){
     xbins[BinNumber++] = BinEdge;
   }
   size = BinNumber;
 }

 TFile* writefile = new TFile(saveName, "RECREATE");

 if(!isInput){
   for(int i = 1; i <= NStw; i++){
    AFBfile>>rootName;

    file[i] = new TFile(rootName);

    FZmass[i] = (TH1D *)file[i]->Get(FName);
    BZmass[i] = (TH1D *)file[i]->Get(BName);

    if(isRebin){
      FZmass[i] = (TH1D *)FZmass[i]->Rebin(size - 1, "FZmass", xbins);
      BZmass[i] = (TH1D *)BZmass[i]->Rebin(size - 1, "BZmass", xbins);
    }

    if(isInputLumiAndXSec){
      double NEvents = FZmass[i]->GetBinContent(1) * Lumi;
      FZmass[i]->SetBinContent(1, NEvents);
      FZmass[i]->SetBinError(1, sqrt(NEvents));

      NEvents = BZmass[i]->GetBinContent(1) * Lumi;
      BZmass[i]->SetBinContent(1, NEvents);
      BZmass[i]->SetBinError(1, sqrt(NEvents));
    }

    h1[i] = (TH1D *)FZmass[i]->Clone("AFB_" + (long)(i));
    h1[i]->Reset();

    AFBFunction(FZmass[i], BZmass[i], h1[i]);
   }
 }

 if(isInput){
   for(int i = 0; i < v_Plot.size(); i++){
     h1[i + 1] = v_Plot.at(i);
   }
 }

 writefile->cd();

 TH1D* AFBValue = new TH1D("AFBValue", "AFBValue", NStw, left - step / 2.0, right + step / 2.0);
 TF1* fitting;
 double* par = new double[2];
 double* parErr = new double[2];

 for(int i = 1; i <= NStw; i++){
   AFBValue->SetBinContent(i, h1[i]->GetBinContent(1));
   AFBValue->SetBinError(i, h1[i]->GetBinError(1));
 }

 LinearFitting(AFBValue, fitting, par, parErr);
 fitting->Write();

 writefile->cd();

 writefile->Write();
 writefile->Close();
}

void FitAFBStw::Input(vector<TH1D *> v_Plot, double left, double right)
{
 isInput = true;

 this->v_Plot = v_Plot;

 NStw = v_Plot.size();

 this->left = left;
 this->right = right;
 step = (right - left) / (NStw - 1);
}

void FitAFBStw::Input(vector<TH1D *> v_Plot, double left, double right, vector<TH1D *> &v_LinearPlot, TH1D* &FittedSlope, TH1D* &FittedOffset)
{
 isInput = true;
 
 this->v_Plot = v_Plot;
 
 NStw = v_Plot.size();
 
 this->left = left;
 this->right = right;
 step = (right - left) / (NStw - 1);

 this->FittedSlope = (TH1D *)v_Plot.at(0)->Clone(v_Plot.at(0)->GetName() + (TString)"_FittedSlope");
 this->FittedSlope->Reset();
 this->FittedOffset = (TH1D *)v_Plot.at(0)->Clone(v_Plot.at(0)->GetName() + (TString)"_FittedOffset");
 this->FittedOffset->Reset();

 MultiFitting();

 v_LinearPlot = this->v_LinearPlot;
 FittedSlope = this->FittedSlope;
 FittedOffset = this->FittedOffset;
}

void FitAFBStw::Input(vector<TH3D *> v_Plot, double left, double right, vector<TH3D *> &v_LinearPlot, TH3D* &FittedSlope, TH3D* &FittedOffset)
{
 isInput = true;

 this->v_Plot_3d = v_Plot;

 NStw = v_Plot.size();

 this->left = left;
 this->right = right;
 step = (right - left) / (NStw - 1);

 this->FittedSlope_3d = (TH3D *)v_Plot.at(0)->Clone(v_Plot.at(0)->GetName() + (TString)"_FittedSlope");
 this->FittedSlope_3d->Reset();
 this->FittedOffset_3d = (TH3D *)v_Plot.at(0)->Clone(v_Plot.at(0)->GetName() + (TString)"_FittedOffset");
 this->FittedOffset_3d->Reset();

 MultiFitting3D();

 v_LinearPlot = this->v_LinearPlot_3d;
 FittedSlope = this->FittedSlope_3d;
 FittedOffset = this->FittedOffset_3d;
}

void FitAFBStw::Get1DLinearPlot(vector<TH1D *> &v_LinearPlot)
{
 v_LinearPlot = this->v_LinearPlot_1d;
}

void FitAFBStw::InputLumiAndXSec(double Lumi, double XSec)
{
 isInputLumiAndXSec = true;

 this->Lumi = Lumi;
 this->XSec = XSec;

 this->TotalEvents = Lumi * XSec;
}

void FitAFBStw::Fitting()
{
 TH1D* AFBValue = new TH1D("AFBValue", "AFBValue", NStw, left - step / 2.0, right + step / 2.0);
 TF1* fitting;
 double* par = new double[2];
 double* parErr = new double[2];

 for(int i = 1; i <= NStw; i++){
   AFBValue->SetBinContent(i, h1[i]->GetBinContent(1));
   AFBValue->SetBinError(i, h1[i]->GetBinError(1));
 }

 LinearFitting(AFBValue, fitting, par, parErr);
}

void FitAFBStw::MultiFitting()
{
 for(int ibin = 1; ibin <= v_Plot.at(0)->GetNbinsX(); ibin++){
   LinearPlot[ibin] = new TH1D(v_Plot.at(0)->GetName() + (TString)"AFBValue" + (int)ibin, v_Plot.at(0)->GetName() + (TString)"AFBValue" + (int)ibin, NStw, left - step / 2.0, right + step / 2.0);
   TF1* fitting;
   double* par = new double[2];
   double* parErr = new double[2];

   for(int i = 1; i <= NStw; i++){
     LinearPlot[ibin]->SetBinContent(i, v_Plot.at(i - 1)->GetBinContent(ibin));
     LinearPlot[ibin]->SetBinError(i, v_Plot.at(i - 1)->GetBinError(ibin));
   }

   LinearFitting(LinearPlot[ibin], fitting, par, parErr);
   FittedSlope->SetBinContent(ibin, par[0]);
   FittedSlope->SetBinError(ibin, parErr[0]);
   FittedOffset->SetBinContent(ibin, par[1]);
   FittedOffset->SetBinError(ibin, parErr[1]);

   v_LinearPlot.push_back(LinearPlot[ibin]);
 }

}

void FitAFBStw::MultiFitting3D()
{
 int iplot = 0;

 int nbinx = NStw;
 double* xbinning = new double[nbinx + 1];
 xbinning[0] = left - step / 2.0;
 for(int i = 1; i <= NStw; i++){
   xbinning[i] = left - step / 2.0 + step * i;
 }

 int nbiny = v_Plot_3d.at(0)->GetNbinsY();
 double* ybinning = new double[nbiny + 1];
 ybinning[0] = v_Plot_3d.at(0)->GetYaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbiny; i++){
   ybinning[i] = v_Plot_3d.at(0)->GetYaxis()->GetBinUpEdge(i);
 }

 int nbinz = v_Plot_3d.at(0)->GetNbinsZ();
 double* zbinning = new double[nbinz + 1];
 zbinning[0] = v_Plot_3d.at(0)->GetZaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinz; i++){
   zbinning[i] = v_Plot_3d.at(0)->GetZaxis()->GetBinUpEdge(i);
 }

 for(int ibinx = 1; ibinx <= v_Plot_3d.at(0)->GetNbinsX(); ibinx++){
   LinearPlot_3d[ibinx] = new TH3D(v_Plot_3d.at(0)->GetName() + (TString)"AFBValue" + (int)ibinx, v_Plot_3d.at(0)->GetName() + (TString)"AFBValue" + (int)ibinx, nbinx, xbinning, nbiny, ybinning, nbinz, zbinning);

   for(int ibiny = 1; ibiny <= v_Plot_3d.at(0)->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= v_Plot_3d.at(0)->GetNbinsZ(); ibinz++){
//       TH1D* LinearProjectionX = (TH1D *)LinearPlot_3d[ibinx]->ProjectionX(LinearPlot_3d[ibinx]->GetName() + (TString)"_px", ibiny, ibiny, ibinz, ibinz);
       iplot++;
       LinearPlot_1d[iplot] = (TH1D *)LinearPlot_3d[ibinx]->ProjectionX(LinearPlot_3d[ibinx]->GetName() + (TString)"_px_" + (int)ibiny + "_ybin_" + (int)ibinz + "_zbin", ibiny, ibiny, ibinz, ibinz);

       TF1* fitting;
       double* par = new double[2];
       double* parErr = new double[2];

       for(int i = 1; i <= NStw; i++){
//         LinearProjectionX->SetBinContent(i, v_Plot_3d.at(i - 1)->GetBinContent(ibinx, ibiny, ibinz));
//         LinearProjectionX->SetBinError(i, v_Plot_3d.at(i - 1)->GetBinError(ibinx, ibiny, ibinz));
         LinearPlot_1d[iplot]->SetBinContent(i, v_Plot_3d.at(i - 1)->GetBinContent(ibinx, ibiny, ibinz));
         LinearPlot_1d[iplot]->SetBinError(i, v_Plot_3d.at(i - 1)->GetBinError(ibinx, ibiny, ibinz));
         LinearPlot_3d[ibinx]->SetBinContent(i, ibiny, ibinz, v_Plot_3d.at(i - 1)->GetBinContent(ibinx, ibiny, ibinz));
         LinearPlot_3d[ibinx]->SetBinError(i, ibiny, ibinz, v_Plot_3d.at(i - 1)->GetBinError(ibinx, ibiny, ibinz));
       }

//       LinearFitting(LinearProjectionX, fitting, par, parErr);
       LinearFitting(LinearPlot_1d[iplot], fitting, par, parErr);
       FittedSlope_3d->SetBinContent(ibinx, ibiny, ibinz, par[0]);
       FittedSlope_3d->SetBinError(ibinx, ibiny, ibinz, parErr[0]);
       FittedOffset_3d->SetBinContent(ibinx, ibiny, ibinz, par[1]);
       FittedOffset_3d->SetBinError(ibinx, ibiny, ibinz, parErr[1]);

       v_LinearPlot_3d.push_back(LinearPlot_3d[ibinx]);
//       v_LinearPlot_1d.push_back(LinearProjectionX);
       v_LinearPlot_1d.push_back(LinearPlot_1d[iplot]);
     }
   }
 }
}

