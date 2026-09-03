#include "Uncertainty/PDFUncertainty.h"

using namespace std;

PDFUncertainty::PDFUncertainty(const char* cardfile)
{
 string FileLine;
 TString skip;
 int config;
 isRatio = false;

 isWasymmetry = false;

 ifstream infile;
  infile.open(cardfile, ios::in);

/*
56                          *NPDF
1                           *dimention
1                           *output
0                           *isRatio
Dilution_ZRapidity                    *histName
Symmetry                    *Error_type
theoryCC.list                 *filelist
0                           *isRebin
binning.txt                 *Rebinfile

***
Dilution_ZMass_uu                   *forwardZmass
Dilution_ZMass_dd                   *backwardZmass
*/

//Number of PDF set
 infile>>config;
 NPDFs = config;
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
//Process
 infile>>skip;
 Process = skip;
 getline(infile, FileLine);
 cout<<skip<<FileLine<<endl;
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

//is Rebin
 infile>>config;
 isRebin = config;
 getline(infile, FileLine);
 cout<<config<<FileLine<<endl;

 if(isRebin){
   if(iflag == 2){
     cout<<"ERROR!! 2D histogram cannot be rebined!"<<endl;
     return;
   }
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

//AFB need two histogram
 if(histName == "AFB" || histName == "Wasymmetry" || Process == "Delta" || Process == "Ratio"){
   infile>>skip;

   infile>>skip;
   FName = skip;
   getline(infile, FileLine);
   cout<<skip<<FileLine<<endl;

   infile>>skip;
   BName = skip;
   getline(infile, FileLine);
   cout<<skip<<FileLine<<endl;
 }

 if(histName == "Wasymmetry") isWasymmetry = true;
}

PDFUncertainty::PDFUncertainty()
{
 isWritefile = false;
 isReadfile = false;
 isSaveVariBin = false;
 isSaveCovariance = false;
 isSaveCorrelation = false;

}

void PDFUncertainty::Main()
{
 isInit = true;

 TString saveName = histName + "_PDFError_" + ErrorType + ".root";

 ifstream PDFfile;
  PDFfile.open(filelist, ios::in);

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

 if(isWritefile) writefile = new TFile(saveName, "RECREATE");

 for(int i = 0; i < NPDFs + 1; i++){
   PDFfile>>rootName;

   if(isWasymmetry){
     if(isReadfile) file1[i] = new TFile(rootName);

     PDFfile>>rootName;
     if(isReadfile) file2[i] = new TFile(rootName);
   }

   else{
     if(isReadfile) file[i] = new TFile(rootName);
   }

   if(histName == "AFB"){
     FZmass[i] = (TH1D *)file[i]->Get(FName);
     BZmass[i] = (TH1D *)file[i]->Get(BName);

     if(isRebin){
       FZmass[i] = (TH1D *)FZmass[i]->Rebin(size - 1, "FZmass", xbins);
       BZmass[i] = (TH1D *)BZmass[i]->Rebin(size - 1, "BZmass", xbins);
     }

     h1[i] = (TH1D *)FZmass[i]->Clone("AFB_" + (long)(i));
     h1[i]->Reset();

     PDFUncertainty::AFBFunction(FZmass[i], BZmass[i], h1[i], i);
   }

   else if(isWasymmetry){
     FZmass[i] = (TH1D *)file1[i]->Get(FName);
     BZmass[i] = (TH1D *)file2[i]->Get(BName);

     if(isRebin){
       FZmass[i] = (TH1D *)FZmass[i]->Rebin(size - 1, "wp_eta_abs", xbins);
       BZmass[i] = (TH1D *)BZmass[i]->Rebin(size - 1, "wm_eta_abs", xbins);
     }

     h1[i] = (TH1D *)FZmass[i]->Clone("Wasymmetry_" + (long)(i));
     h1[i]->Reset();

     PDFUncertainty::AFBFunction(FZmass[i], BZmass[i], h1[i], i);
   }

   else if(Process == "Ratio"){
     FZmass[i] = (TH1D *)file[i]->Get(FName);
     BZmass[i] = (TH1D *)file[i]->Get(BName);

     if(isRebin){
       FZmass[i] = (TH1D *)FZmass[i]->Rebin(size - 1, "FZmass", xbins);
       BZmass[i] = (TH1D *)BZmass[i]->Rebin(size - 1, "BZmass", xbins);
     }

     h1[i] = (TH1D *)FZmass[i]->Clone(histName + (long)i);
     h1[i]->Divide(BZmass[i]);
     PDF1D[i] = (TH1D *)h1[i]->Clone(histName + "_PDF" + (int)i);
   }

   else if(Process == "Delta"){
     FZmass[i] = (TH1D *)file[i]->Get(FName);
     BZmass[i] = (TH1D *)file[i]->Get(BName);

     if(isRebin){
       FZmass[i] = (TH1D *)FZmass[i]->Rebin(size - 1, "FZmass", xbins);
       BZmass[i] = (TH1D *)BZmass[i]->Rebin(size - 1, "BZmass", xbins);
     }

     h1[i] = (TH1D *)FZmass[i]->Clone(histName + (long)i);
     h1[i]->Add(BZmass[i], -1);
     PDF1D[i] = (TH1D *)h1[i]->Clone(histName + "_PDF" + (int)i);
   }

   else{
     if(iflag == 1) h1[i] = (TH1D *)file[i]->Get(histName);
     if(iflag == 2) h2[i] = (TH2D *)file[i]->Get(histName);
     if(iflag == 1) PDF1D[i] = (TH1D *)h1[i]->Clone(histName + "_PDF" + (int)i);
     if(iflag == 2) PDF2D[i] = (TH2D *)h2[i]->Clone(histName + "_PDF" + (int)i);

     if(isRebin) h1[i] = (TH1D *)h1[i]->Rebin(size - 1, histName, xbins);
   }

   if(iflag == 1) hist_1d.push_back(h1[i]);
   if(iflag == 2) hist_2d.push_back(h2[i]);
 }

 if(isWritefile) writefile->cd();

 for(int i = 0; i < NPDFs + 1; i++){
   if(iflag == 1) PDF1D[i]->Write();
   if(iflag == 2) PDF2D[i]->Write();
 }

 if(iflag == 1) PDFCentral1D = (TH1D *)h1[0]->Clone(histName + "_PDFCentral");
 if(iflag == 2) PDFCentral2D = (TH2D *)h2[0]->Clone(histName + "_PDFCentral");

 if(iflag == 1) PDFError1D = (TH1D *)h1[1]->Clone(histName + "_PDFError");
 if(iflag == 1) PDFErrorPlus1D = (TH1D *)h1[1]->Clone(histName + "_PDFErrorPlus");
 if(iflag == 1) PDFErrorMinus1D = (TH1D *)h1[1]->Clone(histName + "_PDFErrorMinus");
 if(iflag == 1) PDFEnvelopePlus1D = (TH1D *)h1[0]->Clone(histName + "_PDFEnvelopePlus");
 if(iflag == 1) PDFEnvelopeMinus1D = (TH1D *)h1[0]->Clone(histName + "_PDFEnvelopeMinus");
 if(iflag == 2) PDFError2D = (TH2D *)h2[1]->Clone(histName + "_PDFError");

 if(iflag == 1) PDFStatError1D = (TH1D *)h1[0]->Clone(histName + "_PDFStatError");
 if(iflag == 2) PDFStatError2D = (TH2D *)h2[0]->Clone(histName + "_PDFStatError");

 if(iflag == 1) PDFStatError1D->Reset();
 if(iflag == 2) PDFStatError2D->Reset();

 if(iflag == 1){
   if(isSaveCovariance) Covariance = new TH2D("CovMatrix_PDFError", "CovMatrix_PDFError", h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX(), h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX());
   if(isSaveCorrelation) Correlation = new TH2D("Correlation_PDFError", "Correlation_PDFError", h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX(), h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX());
 }

 if(iflag == 1){
   for(int ibin = 1; ibin <= h1[0]->GetNbinsX(); ibin++){
     PDFStatError1D->SetBinContent(ibin, PDFCentral1D->GetBinError(ibin));
   }
 }

 if(iflag == 2){
   for(int ibinx = 1; ibinx <= h2[0]->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h2[0]->GetNbinsY(); ibiny++){
       PDFStatError2D->SetBinContent(ibinx, ibiny, PDFCentral2D->GetBinError(ibinx, ibiny));
     }
   }
 }

 GetPDFUncertainty();

 if(isWritefile) writefile->Write();
 if(isWritefile) writefile->Close();
}

void PDFUncertainty::Input1DPlot(TString ErrorType, vector<TH1D *> Hists, TH1D* &PDFError)
{
 isInit = true;

 this->ErrorType = ErrorType;

 iflag = 1;

 NPDFs = Hists.size() - 1;

 for(int i = 0; i < NPDFs + 1; i++){
   h1[i] = Hists.at(i);
   hist_1d.push_back(h1[i]);
 }

 histName = h1[0]->GetName();
 PDFError1D = (TH1D *)h1[0]->Clone(histName + "_PDFError");
 PDFCentral1D = (TH1D *)h1[0]->Clone(histName + "_PDFCentral");

 if(iflag == 1){
   if(isSaveCovariance) Covariance = new TH2D("CovMatrix_PDFError", "CovMatrix_PDFError", h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX(), h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX());
   if(isSaveCorrelation) Correlation = new TH2D("Correlation_PDFError", "Correlation_PDFError", h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX(), h1[0]->GetNbinsX(), 1, h1[0]->GetNbinsX());
 }

 GetPDFUncertainty();
 PDFError = this->PDFError1D;
}

void PDFUncertainty::Input1DPlot(TString ErrorType, vector<TH1D *> Hists, TH1D* &PDFError, TH1D* &PDFEnvelopePlus, TH1D* &PDFEnvelopeMinus)
{
 isInit = true;

 this->ErrorType = ErrorType;

 iflag = 1;

 NPDFs = Hists.size() - 1;

 for(int i = 0; i < NPDFs + 1; i++){
   h1[i] = Hists.at(i);
   hist_1d.push_back(h1[i]);
 }

 histName = h1[0]->GetName();
 PDFError1D = (TH1D *)h1[0]->Clone(histName + "_PDFError");
 PDFEnvelopePlus1D = (TH1D *)h1[0]->Clone(histName + "_PDFEnvelopePlus");
 PDFEnvelopePlus1D->Reset();
 PDFEnvelopeMinus1D = (TH1D *)h1[0]->Clone(histName + "_PDFEnvelopeMinus");
 PDFEnvelopeMinus1D->Reset();
 PDFCentral1D = (TH1D *)h1[0]->Clone(histName + "_PDFCentral");

 GetPDFUncertainty();
 PDFError = this->PDFError1D;
 PDFEnvelopePlus = this->PDFEnvelopePlus1D;
 PDFEnvelopeMinus = this->PDFEnvelopeMinus1D;
}

void PDFUncertainty::Input2DPlot(TString ErrorType, vector<TH2D *> Hists, TH2D* &PDFError)
{
 isInit = true;

 this->ErrorType = ErrorType;

 iflag = 2;

 NPDFs = Hists.size() - 1;

 for(int i = 0; i < NPDFs + 1; i++){
   h2[i] = Hists.at(i);
   hist_2d.push_back(h2[i]);
 }

 histName = h2[0]->GetName();
 PDFError2D = (TH2D *)h2[0]->Clone(histName + "_PDFError");
 PDFCentral2D = (TH2D *)h2[0]->Clone(histName + "_PDFCentral");

 GetPDFUncertainty();
 PDFError = this->PDFError2D;
}

void PDFUncertainty::GetPDFUncertainty()
{
 double Unc2 = 0;
 double Unc = 0;

 if(iflag == 1){

   if(ErrorType == "Symmetry" || ErrorType == "Symmetry68" || ErrorType == "SymmetryNorm" || ErrorType == "Symmetry68Norm"){
     if(ErrorType == "SymmetryNorm" || ErrorType == "Symmetry68Norm"){
       double Norm = h1[0]->Integral();
       h1[0]->Scale(1.0 / Norm);
       for(int i = 1; i < NPDFs + 1; i++){
         double Norm = h1[i]->Integral();
         h1[i]->Scale(1.0 / Norm);
       }
     }

     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs / 2, 0.5, NPDFs / 2 + 0.5);

       for(int i = 1; i < NPDFs / 2 + 1; i++){
         Unc2 += (h1[2 * i]->GetBinContent(ibin) - h1[2 * i - 1]->GetBinContent(ibin)) * (h1[2 * i]->GetBinContent(ibin) - h1[2 * i - 1]->GetBinContent(ibin)) / 4.0;
         if(isOutput) cout<<i<<"  "<<(h1[2 * i]->GetBinContent(ibin) - h1[2 * i - 1]->GetBinContent(ibin))<<endl;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, fabs(h1[2 * i]->GetBinContent(ibin) - h1[2 * i - 1]->GetBinContent(ibin)));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       Unc = sqrt(Unc2);
       if(ErrorType == "Symmetry" || ErrorType == "SymmetryNorm") Unc = Unc / 1.645;
       PDFError1D->SetBinContent(ibin, Unc);
       //PDFError1D->SetBinError(ibin, PDFCentral1D->GetBinError(ibin));
       PDFError1D->SetBinError(ibin, 0);
       PDFCentral1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin));
       PDFCentral1D->SetBinError(ibin, Unc);
     }
   }
   if(ErrorType == "EnvelopNorm"){
     double Norm = h1[0]->Integral();
     //h1[0]->Scale(1.0 / Norm);
     for(int i = 1; i < NPDFs + 1; i++){
       double Norm = h1[i]->Integral();
       h1[i]->Scale(h1[0]->Integral() / Norm);
     }

     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs, 0.5, NPDFs + 0.5);

       for(int i = 1; i < NPDFs + 1; i++){
         Unc2 = fabs(h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin));
         if(Unc2 >= Unc) Unc = Unc2;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       Unc = Unc / 1.645;
       PDFError1D->SetBinContent(ibin, Unc);
       //PDFError1D->SetBinError(ibin, PDFCentral1D->GetBinError(ibin));
       PDFError1D->SetBinError(ibin, 0);
       PDFCentral1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin));
       PDFCentral1D->SetBinError(ibin, Unc);
     }
   }
   if(ErrorType == "EnvelopScale"){
     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs, 0.5, NPDFs + 0.5);

       for(int i = 1; i < NPDFs + 1; i++){
         Unc2 = fabs(h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin));
         if(Unc2 >= Unc) Unc = Unc2;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       PDFError1D->SetBinContent(ibin, Unc);
       //PDFError1D->SetBinError(ibin, PDFCentral1D->GetBinError(ibin));
       PDFError1D->SetBinError(ibin, 0);
       PDFCentral1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin));
       PDFCentral1D->SetBinError(ibin, Unc);
     }
   }
   if(ErrorType == "EnvelopScaleTwoSide"){
     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;
       double Unc2Abs = 0.0;
       double UncAbs = 0.0;
       double Unc2Plus = 0.0;
       double UncPlus = 0.0;
       double Unc2Minus = 0.0;
       double UncMinus = 0.0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs, 0.5, NPDFs + 0.5);

       for(int i = 1; i < NPDFs + 1; i++){
         Unc2Abs = fabs(h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin));
         Unc2 = h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin);
         Unc2Plus = h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin);
         Unc2Minus = h1[i]->GetBinContent(ibin) - h1[0]->GetBinContent(ibin);
         if(Unc2Abs >= UncAbs) UncAbs = Unc2Abs;
         if(Unc2Abs >= UncAbs) Unc = Unc2;
         if(Unc2Plus >= UncPlus) UncPlus = Unc2Plus;
         if(Unc2Minus <= UncMinus) UncMinus = Unc2Minus;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       PDFEnvelopePlus1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin) + UncPlus);
       PDFEnvelopePlus1D->SetBinError(ibin, 0.0);
       PDFEnvelopeMinus1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin) + UncMinus);
       PDFEnvelopeMinus1D->SetBinError(ibin, 0.0);
       PDFCentral1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin));
       PDFError1D->SetBinContent(ibin, UncAbs);
       PDFError1D->SetBinError(ibin, 0);
     }
   }
   if(ErrorType == "EnvelopScaleShape"){
     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;
       double Unc2Plus = 0.0;
       double UncPlus = 0.0;
       double Unc2Minus = 0.0;
       double UncMinus = 0.0;
       int IndexPlus = 0;
       int IndexMinus = 0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs, 0.5, NPDFs + 0.5);

       for(int i = 1; i < NPDFs + 1; i++){
         Unc2Plus = h1[i]->GetBinContent(1) - h1[0]->GetBinContent(1);
         Unc2Minus = h1[i]->GetBinContent(1) - h1[0]->GetBinContent(1);
         if(Unc2Plus >= UncPlus){
           UncPlus = Unc2Plus;
           IndexPlus = i;
         }
         if(Unc2Minus <= UncMinus){
           UncMinus = Unc2Minus;
           IndexMinus = i;
         }

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }
       PDFEnvelopePlus1D->SetBinContent(ibin, h1[IndexPlus]->GetBinContent(ibin));
       PDFEnvelopePlus1D->SetBinError(ibin, 0.0);
       PDFEnvelopeMinus1D->SetBinContent(ibin, h1[IndexMinus]->GetBinContent(ibin));
       PDFEnvelopeMinus1D->SetBinError(ibin, 0.0);
     }
   }
   if(ErrorType == "Asymmetry"){
     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs, 0.5, NPDFs + 0.5);

       for(int i = 1; i <= NPDFs; i++){
         Unc2 += ((h1[i]->GetBinContent(ibin) - PDFCentral1D->GetBinContent(ibin)) * (h1[i]->GetBinContent(ibin) - PDFCentral1D->GetBinContent(ibin))) / 2;
         if(isOutput) cout<<i<<"  "<<h1[i]->GetBinContent(ibin)<<"  "<<h1[i]->GetBinError(ibin)<<endl;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, h1[i]->GetBinError(ibin));
       }
       Unc = sqrt(Unc2);
       PDFError1D->SetBinContent(ibin, Unc);
     }
   }

   if(ErrorType == "MonteCarlo"){
     for(int ibin = 1; ibin <= h1[0]->GetNbinsX(); ibin++){
       Unc2 = 0;
       Unc = 0;

       TString UncName = histName + "_UncVariation_Bin_";
       UncName = UncName + (long)ibin;
       if(isSaveVariBin) UncVari[ibin] = new TH1D(UncName, UncName, NPDFs, 0.5, NPDFs + 0.5);
       for(int i = 1; i <= NPDFs; i++){
         if(isOutput) cout<<i<<"  "<<h1[i]->GetBinContent(ibin)<<endl;

         if(isSaveVariBin) UncVari[ibin]->SetBinContent(i, h1[i]->GetBinContent(ibin));
         if(isSaveVariBin) UncVari[ibin]->SetBinError(i, 0);
       }

       double maximum = 0.0;
       double minimum = 0.0;
       if(isSaveVariBin) maximum = UncVari[ibin]->GetMaximum();
       if(isSaveVariBin) minimum = UncVari[ibin]->GetMinimum();
       TString MCName = histName + "_MCVari_Bin_";
       MCName = MCName + (long)ibin;
       if(isSaveMCVari) MCVari[ibin] = new TH1D(MCName, MCName, 10, minimum, maximum);
       vector<double> MCVariVector;
       for(int i = 1; i <= NPDFs; i++){
         if(isSaveMCVari && h1[i]->GetBinContent(ibin) < maximum && h1[i]->GetBinContent(ibin) > minimum) MCVari[ibin]->Fill(h1[i]->GetBinContent(ibin), 1);
         if(isSaveMCVari && h1[i]->GetBinContent(ibin) > maximum || h1[i]->GetBinContent(ibin) < minimum) cout<<"ERROR: in PDFUncertainty.C, please enlarge the range for calculate RMS. minimum = "<<minimum<<" maximum = "<<maximum<<" h1["<<i<<"]->GetBinContent("<<ibin<<") = "<<h1[i]->GetBinContent(ibin)<<endl;

         ParX[ibin].push_back(h1[i]->GetBinContent(ibin));
         ParY[ibin].push_back(h1[i]->GetBinContent(ibin));

         MCVariVector.push_back(h1[i]->GetBinContent(ibin));
       }
       Unc = CalculateRMS(MCVariVector);
       MCVariVector.clear();
       PDFError1D->SetBinContent(ibin, Unc);
       PDFError1D->SetBinError(ibin, 0);
       PDFCentral1D->SetBinContent(ibin, h1[0]->GetBinContent(ibin));
       PDFCentral1D->SetBinError(ibin, Unc);

       if(isSaveVariBin) UncVari[ibin]->Write();
       if(isSaveMCVari) MCVari[ibin]->Write();
     }
     for(int ibinx = 1; ibinx <= h1[1]->GetNbinsX(); ibinx++){
       for(int ibiny = 1; ibiny <= h1[1]->GetNbinsX(); ibiny++){
         if(isSaveCovariance) CovarianceValue = CalculateCovariance(ParX[ibinx], MCVari[ibinx]->GetMean(), ParY[ibiny], MCVari[ibiny]->GetMean());
         if(isSaveCovariance) Covariance->SetBinContent(ibinx, ibiny, CovarianceValue);
         if(isSaveCorrelation) Correlation->SetBinContent(ibinx, ibiny, CovarianceValue / (PDFError1D->GetBinContent(ibinx) * PDFError1D->GetBinContent(ibiny)));
       }
     }
     for(int ibin = 1; ibin <= h1[1]->GetNbinsX(); ibin++){
       if(isSaveMCVari) delete MCVari[ibin];
     }
   }

 }

 if(iflag == 2){
   for(int ibinx = 1; ibinx <= h2[1]->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h2[1]->GetNbinsY(); ibiny++){
       Unc2 = 0;
       Unc = 0;
       for(int i = 1; i < NPDFs / 2 + 1; i++){
         Unc2 += (h2[2 * i]->GetBinContent(ibinx, ibiny) - h2[2 * i - 1]->GetBinContent(ibinx, ibiny)) * (h2[2 * i]->GetBinContent(ibinx, ibiny) - h2[2 * i - 1]->GetBinContent(ibinx, ibiny)) / 4;
       }
       Unc = sqrt(Unc2);
       PDFError2D->SetBinContent(ibinx, ibiny, Unc);
     }
   }
 }  

}

PDFUncertainty::~PDFUncertainty()
{

}

void PDFUncertainty::AFBFunction(TH1D* FZmass, TH1D* BZmass, TH1D* &Draw_AFB, int i)
{
 double Nf, Nb, AFB, NfError, NbError, AFBError;

// Draw_AFB = (TH1D *)FZmass->Clone("AFB_" + (long)(i));
// Draw_AFB->Reset();

 for (int ibin = 0; ibin < FZmass->GetNbinsX(); ibin++)
 {
  Nf = FZmass->GetBinContent(ibin + 1);
  Nb = BZmass->GetBinContent(ibin + 1);
  AFB = (Nf - Nb) / (Nf + Nb);
  
  NfError = FZmass->GetBinError(ibin + 1);
  NbError = BZmass->GetBinError(ibin + 1);
  AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));
  
  Draw_AFB->SetBinContent(ibin + 1, AFB);
  Draw_AFB->SetBinError(ibin + 1, AFBError);
 }
}
