#ifndef ResolutionHist_cxx
#define ResolutionHist_cxx
#include "SpecialHist/ResolutionHist.h"

using namespace std;

ResolutionHist::ResolutionHist(TString type, int iThread)
{
 iflag = 0;

 TRandom3 myR(0);
 x = myR.Integer(100000);

 this->iThread = iThread;
 this->type = type;
}

ResolutionHist::~ResolutionHist()
{
}

void ResolutionHist::SetHist(const char* histName, int NbinsX, double xmin, double xmax)
{
 iflag = 1;

 this->NbinsX = NbinsX;
 this->histName = histName;
 this->ResolutionHist1D = new TH1D(histName, histName, NbinsX, xmin, xmax);
 this->VariableHist1D = new TH1D("h1" + (TString)histName, "h1" + (TString)histName, NbinsX, xmin, xmax);

 TString Name = "";

 for(int i = 1; i < NbinsX + 1; i++){
   Name = (TString)histName + (TString)"_Resolution_" + (int)i + (TString)"bin";
   if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
   h1[i] = new TH1D(Name, Name, 100, -1, 1);
   h1[i]->Sumw2();
   hist_1d.push_back(h1[i]);

   f1[i] = new TF1((TString)Name + "_fitting", "gaus(0)", -1, 1);
 }

}

void ResolutionHist::SetHist(const char* histName, int NbinsX, double* xbins)
{
 iflag = 1;

 this->NbinsX = NbinsX;
 this->histName = histName;
 this->ResolutionHist1D = new TH1D(histName, histName, NbinsX, xbins);
 this->VariableHist1D = new TH1D("h1" + (TString)histName, "h1" + (TString)histName, NbinsX, xbins);

 TString Name = "";

 for(int i = 1; i < NbinsX + 1; i++){
   Name = (TString)histName + (TString)"_Resolution_" + (int)i + (TString)"bin";
   if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
   h1[i] = new TH1D(Name, Name, 100, -1, 1);
   h1[i]->Sumw2();
   hist_1d.push_back(h1[i]);

   f1[i] = new TF1((TString)Name + "_fitting", "gaus(0)", -1, 1);
 }

}

void ResolutionHist::SetHist(const char* histName, int NbinsX, double* xbins, int NbinsY, double* ybins)
{
 iflag = 2;

 this->NbinsX = NbinsX;
 this->NbinsY = NbinsY;
 this->histName = histName;
 this->ResolutionHist2D = new TH2D(histName, histName, NbinsX, xbins, NbinsY, ybins);
 this->VariableHist2D = new TH2D("h2" + (TString)histName, "h2" + (TString)histName, NbinsX, xbins, NbinsY, ybins);

 TString Name = "";

 for(int i = 1; i < NbinsX; i++){
   for(int j = 1; j < NbinsY; j++){
     Name = (TString)histName + (TString)"_Resolution_" + (int)i + (TString)"xbin_" + (int)j + (TString)"ybin";
     if(iThread != 0) Name = (TString)Name + (TString)"_" + (int)iThread;
     h2[i][j] = new TH1D(Name, Name, 100, -1, 1);
     h2[i][j]->Sumw2();

     f2[i][j] = new TF1((TString)Name + "_fitting", "gaus(0)", -1, 1);
   }
 }

}

void ResolutionHist::FillResolution(double myVariable)
{
 int bin = VariableHist1D->Fill(myVariable, weight);
 if(bin > 0)
 {
  h1[bin]->Fill(deltaE, weight);
 }
}

void ResolutionHist::FillResolution(double myVariable1, double myVariable2)
{
 int bin = VariableHist2D->Fill(myVariable1, myVariable2, weight);
 if(bin > 0)
 {
  h2[bin % (NbinsX + 2)][bin / (NbinsX + 2)]->Fill(deltaE, weight);
 }

}

void ResolutionHist::Fill(double deltaE, double weight)
{
 this->deltaE = deltaE;
 this->weight = weight;
}

void ResolutionHist::FitResolution(bool isDeleteHist)
{
 cout<<"Start to fit resolution. Using type "<<type<<endl;
 if(type != "Gaus" && type != "RMS"){
   cout<<"Using the default type Gaus"<<endl;
   type = "Gaus";
 }

 if(type == "RMS") isDeleteHist = true;

 if(iflag == 1){
   for(int i = 1; i < NbinsX + 1; i++){
     if(h1[i]->GetEntries() != 0){
       if(type == "Gaus"){
         h1[i]->Fit(f1[i], "W");
         f1[i]->GetParameters(par);
         ResolutionHist1D->SetBinContent(i, par[2]);
         ResolutionHist1D->SetBinError(i, 0);
       }
       if(type == "RMS"){
         ResolutionHist1D->SetBinContent(i, h1[i]->GetRMS());
         ResolutionHist1D->SetBinError(i, 0);
       }
     }
     else{
       cout<<"The No."<<i<<" bin doesn't have events, skip this bin."<<endl;
       ResolutionHist1D->SetBinContent(i, 0);
       ResolutionHist1D->SetBinError(i, 0);
     }
     if(isDeleteHist) delete h1[i];
     if(isDeleteHist) delete f1[i];
   }
   delete VariableHist1D;
 }

 if(iflag == 2){
   for(int i = 1; i < NbinsX + 1; i++){
     for(int j = 1; j < NbinsY + 1; j++){
       if(h2[i][j]->GetEntries() != 0){
         if(type == "Gaus"){
           h2[i][j]->Fit(f2[i][j], "W");
           f2[i][j]->GetParameters(par);
           ResolutionHist2D->SetBinContent(i, j, par[2]);
           ResolutionHist2D->SetBinError(i, j, 0);
         }
         if(type == "RMS"){
           ResolutionHist2D->SetBinContent(i, j, h2[i][j]->GetRMS());
           ResolutionHist2D->SetBinError(i, j, 0);
         }
       }
       else{
         cout<<"The No."<<i<<" No."<<j<<" bin doesn't have events, skip this bin."<<endl;
         ResolutionHist2D->SetBinContent(i, j, 0);
         ResolutionHist2D->SetBinError(i, j, 0);
       }
       if(isDeleteHist) delete h2[i][j];
       if(isDeleteHist) delete f2[i][j];
     }
   }
   delete VariableHist2D;
 }

}

void ResolutionHist::Add(ResolutionHist* hist1)
{
 for(int i = 0; i < hist_1d.size(); i++){
   hist_1d.at(i)->Add((hist1->hist_1d).at(i));
 }
}

void ResolutionHist::Reset()
{
 for(int i = 0; i < hist_1d.size(); i++){
   hist_1d.at(i)->Reset();
 }

 if(iflag == 1) ResolutionHist1D->Reset();
 if(iflag == 2) ResolutionHist2D->Reset();
}

void ResolutionHist::Write()
{
 if(iflag == 1) ResolutionHist1D->Write();
 if(iflag == 2) ResolutionHist2D->Write();
}

void ResolutionHist::End()
{
}
#endif
