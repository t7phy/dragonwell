#include "ScaleUncertainty.h"

using namespace std;
ScaleUncertainty::ScaleUncertainty(const char* cardfile)
{
 string FileLine;
 TString skip;
 int config;

 ifstream infile;
  infile.open(cardfile, ios::in);

//////////ScaleCard.in/////////////
/*
15       	*Number of scale
8 	  	*Scale central set
1          	*histogram dimension
1         	*isOutput
ZPt           	*histogram name
Asymmetry  	*ErrorType
theory.list  	*file list
*/
/////////////////////////////////

//Number of scale choices
 infile>>config;
 NScales = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;
//Canoninal scale serial number
 infile>>config;
 ScaleCentral = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;
//histogram dimension
 infile>>config;
 iflag = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;
//is Output
 infile>>config;
 isOutput = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;
//histogram name
 infile>>skip;
 histName = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;
//Error type
 infile>>skip;
 ErrorType = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;
//file list
 infile>>skip;
 filelist = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;
}

ScaleUncertainty::ScaleUncertainty()
{
 isOutput = false;
}

void ScaleUncertainty::Main()
{
 TString saveName = histName + "_ScaleError.root";

 ifstream scalefile;
  scalefile.open(filelist, ios::in);

 TString rootName;

 TFile* writefile = new TFile(saveName, "RECREATE");

 for(int i = 1; i < NScales + 1; i++){
  scalefile>>rootName;
  file[i] = new TFile(rootName);
  if(iflag == 1) h1[i] = (TH1D *)file[i]->Get(histName);
  if(iflag == 2) h2[i] = (TH2D *)file[i]->Get(histName);
 }

 if(iflag == 1) h1[0] = h1[ScaleCentral];
 if(iflag == 2) h2[0] = h2[ScaleCentral];

 writefile->cd();
 if(iflag == 1) ScaleCentral1D = (TH1D *)h1[0]->Clone(histName + "_ScaleCentral");
 if(iflag == 2) ScaleCentral2D = (TH2D *)h2[0]->Clone(histName + "_ScaleCentral");

 if(iflag == 1) ScaleError1D = (TH1D *)h1[1]->Clone(histName + "_ScaleError");
 if(iflag == 1) ScaleErrorUp1D = (TH1D *)h1[1]->Clone(histName + "_ScaleErrorUp");
 if(iflag == 1) ScaleErrorDown1D = (TH1D *)h1[1]->Clone(histName + "_ScaleErrorDown");

 if(iflag == 2) ScaleError2D = (TH2D *)h2[1]->Clone(histName + "_ScaleError");

 if(iflag == 1) ScaleStatError1D = (TH1D *)h1[1]->Clone(histName + "_ScaleStatError");
 if(iflag == 2) ScaleStatError2D = (TH2D *)h2[1]->Clone(histName + "_ScaleStatError");

 if(iflag == 1) ScaleStatError1D->Reset();
 if(iflag == 2) ScaleStatError2D->Reset();

 if(iflag == 1){
    for(int i = 1; i < NScales + 1;i++){
        ScalePlot1D[i] = (TH1D *)h1[i]->Clone(histName + "_Scale" + (long)(900 + i));
    }
 }
 if(iflag == 2){
    for(int i = 1; i < NScales + 1;i++){
        ScalePlot2D[i] = (TH2D *)h2[i]->Clone(histName + "_Scale" + (long)(900 + i));
    }
 }

 if(iflag == 1){
  for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
   ScaleStatError1D->SetBinContent(ibin, ScaleCentral1D->GetBinError(ibin));
  }
 }

 if(iflag == 2){
  for(int ibinx = 1; ibinx <= h2[1]->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= h2[1]->GetNbinsY(); ibiny++){
   ScaleStatError2D->SetBinContent(ibinx, ibiny, ScaleCentral2D->GetBinError(ibinx, ibiny));
   }
  }
 }

 GetScaleUncertainty();

 writefile->Write();
 writefile->Close();
}

void ScaleUncertainty::Input1DPlot(TString ErrorType, vector<TH1D *> Hists, TH1D* &ScaleError)
{
 this->ErrorType = ErrorType;

 iflag = 1;

 NScales = Hists.size() - 1;

 for(int i = 0; i < NScales + 1; i++){
   h1[i] = Hists.at(i);
 }

 histName = h1[0]->GetName();
 ScaleError1D = (TH1D *)h1[1]->Clone(histName + "_ScaleError");

 GetScaleUncertainty();
 ScaleError = this->ScaleError1D;
}

void ScaleUncertainty::GetScaleUncertainty()
{
 double Unc2 = 0;
 double Unc = 0;
 double UncUp = 0;
 double UncDown = 0;

 if(iflag == 1){
   for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
     Unc2 = 0;
     Unc = 0;
     if(isOutput) cout<<"ibin = "<<ibin<<endl;

     TString UncName = histName + "_UncVariation_Bin_";
     UncName = UncName + (long)ibin;
     if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NScales, 0.5, NScales + 0.5);

     if(ErrorType == "Symmetry"){
       for(int i = 1; i < NScales + 1; i++){
         Unc2 = fabs(h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin));
         if(isOutput) cout<<"Scale"<<i + 900<<" = "<<h1[i]->GetBinContent(ibin)<<endl;
         if(Unc2 >= Unc) Unc = Unc2;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       ScaleError1D->SetBinContent(ibin, Unc);
       ScaleError1D->SetBinError(ibin, 0);
     }
     if(ErrorType == "Asymmetry"){
       for(int i = 1; i < NScales + 1; i++){
         Unc2 = h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin);
         if(isOutput) cout<<"Scale"<<i + 900<<" = "<<h1[i]->GetBinContent(ibin)<<endl;
         if(Unc2 >= UncUp) UncUp = Unc2;
         if(Unc2 <= UncDown) UncDown = Unc2;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       ScaleErrorUp1D->SetBinContent(ibin, UncUp);
       ScaleErrorUp1D->SetBinError(ibin, 0);
       ScaleErrorDown1D->SetBinContent(ibin, UncDown);
       ScaleErrorDown1D->SetBinError(ibin, 0);
     }

     if(isSaveVariBin) UncVari[ibin]->Write();
   }
 }

 if(iflag == 2){
   for(int ibinx = 1; ibinx <= h2[1]->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h2[1]->GetNbinsY(); ibiny++){
       Unc2 = 0;
       Unc = 0;
       if(isOutput) cout<<"ibinx = "<<ibinx<<" ibiny = "<<ibiny<<endl;

       if(ErrorType = "Symmetry"){
         for(int i = 1; i < NScales + 1; i++){
           Unc2 = fabs(h2[i]->GetBinContent(ibinx, ibiny) - h2[ScaleCentral]->GetBinContent(ibinx, ibiny));
           if(isOutput) cout<<"Scale"<<i + 900<<" = "<<h2[i]->GetBinContent(ibinx, ibiny)<<endl;
           if(Unc2 >= Unc) Unc = Unc2;
         }
         ScaleError2D->SetBinContent(ibinx, ibiny, Unc);
         ScaleError2D->SetBinError(ibinx, ibiny, 0);
       }

      if(ErrorType = "Asymmetry"){
         for(int i = 1; i < NScales + 1; i++){
           Unc2 = h2[i]->GetBinContent(ibinx, ibiny) - h2[ScaleCentral]->GetBinContent(ibinx, ibiny);
           if(isOutput) cout<<"Scale"<<i + 900<<" = "<<h2[i]->GetBinContent(ibinx, ibiny)<<endl;
           if(Unc2 >= UncUp) UncUp = Unc2;
           if(Unc2 <= UncDown) UncDown = Unc2;
         }
         ScaleErrorUp2D->SetBinContent(ibinx, ibiny, UncUp);
         ScaleErrorUp2D->SetBinError(ibinx, ibiny, 0);
         ScaleErrorDown2D->SetBinContent(ibinx, ibiny, UncDown);
         ScaleErrorDown2D->SetBinError(ibinx, ibiny, 0);
       }

     }
   }
 }  

}

ScaleUncertainty::~ScaleUncertainty()
{

}
