#include "Tools/Tools.h"
#include "TFile.h"
#include "TH1D.h"
#include "TString.h"

using namespace std;

int main(int argc, char** argv)
{
 TString rootName;
 TFile *file;
 TH1D *plot_AFB;
 TH1D *AFB_PDFError;

 double *AFBValue = new double[1000];
 double *PDFError = new double[1000];

 double AFB_Central, AFB_RMS;
 double PDFError_Central, PDFError_RMS;
 double TotalPDFError;

 TFile *writefile = new TFile("PDFError.root", "RECREATE");
 TH1D *newAFB = new TH1D("AFB", "AFB", 35, 60, 130);
 TH1D *newAFB_RMS = new TH1D("AFB_RMS", "AFB_RMS", 35, 60, 130);
 TH1D *newPDFError = new TH1D("PDFError", "PDFError", 35, 60, 130);
 TH1D *newPDFError_RMS = new TH1D("PDFError_RMS", "PDFError_RMS", 35, 60, 130);
 TH1D *TotalError = new TH1D("TotalPDFError", "TotalPDFError", 35, 60, 130);


 for(int ibin = 0; ibin < 35; ibin++){
   for(int i = 0; i < 1000; i++){
     rootName = (TString)"/lustre/AtlUser/yfu/MainCode/run/CorrelationStudy/CorrTestSmallStaErr/JOB" + (int)(i + 1) + (TString)"/test.root";
     file = new TFile(rootName);
     plot_AFB = (TH1D *)file->Get("Observable_1_new");
     AFB_PDFError = (TH1D *)file->Get("Observable_1_newPDFError");

     AFBValue[i] = plot_AFB->GetBinContent(ibin + 1);
     PDFError[i] = AFB_PDFError->GetBinContent(ibin + 1);
     delete file;
   }

   AFB_Central = CalculateMean(AFBValue);
   AFB_RMS = CalculateRMS(AFBValue);

   PDFError_Central = CalculateMean(PDFError);
   PDFError_RMS = CalculateRMS(PDFError);

   newAFB->SetBinContent(ibin + 1, AFB_Central);
   newAFB->SetBinError(ibin + 1, 0);
   newAFB_RMS->SetBinContent(ibin + 1, AFB_RMS);
   newAFB_RMS->SetBinError(ibin + 1, 0);

   newPDFError->SetBinContent(ibin + 1, PDFError_Central);
   newPDFError->SetBinError(ibin + 1, 0);
   newPDFError_RMS->SetBinContent(ibin + 1, PDFError_RMS);
   newPDFError_RMS->SetBinError(ibin + 1, 0);

   TotalPDFError = sqrt(AFB_RMS * AFB_RMS + PDFError_Central * PDFError_Central);
   TotalError->SetBinContent(ibin + 1, TotalPDFError);
   TotalError->SetBinError(ibin + 1, 0);
   cout<<"AFB RMS = "<<AFB_RMS<<" PDFError RMS = "<<PDFError_RMS<<endl;
 }

 writefile->cd();
 writefile->Write();
 writefile->Close();
 return 0;
}
