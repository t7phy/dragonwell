#include "ePump/ePumpHists.h"

using namespace std;

void ePumpHists::openFile(const char* fName)
{
 hf = new TFile(fName, "RECREATE");
}

void ePumpHists::bookHists(const char* histName, int ihist, int ibin)
{
 Observable_old[ihist] = new TH1D(histName + (TString)"_old", histName + (TString)"_old", ibin, 0, ibin);
 Observable_new[ihist] = new TH1D(histName + (TString)"_new", histName + (TString)"_new", ibin, 0, ibin);
 PDFError_old[ihist] = new TH1D(histName + (TString)"_oldPDFError", histName + (TString)"_oldPDFError", ibin, 0, ibin);
 PDFError_new[ihist] = new TH1D(histName + (TString)"_newPDFError", histName + (TString)"_newPDFError", ibin, 0, ibin);

}

void ePumpHists::bookHists(int ihist1, int ihist2, int ibin1, int ibin2)
{
 Correlation_old[ihist1][ihist2] = new TH2D((TString)"Correlation_old_" + (long)(ihist1 + 1) + (TString)"_" + (long)(ihist2 + 1), (TString)"Correlation_old_" + (long)(ihist1 + 1) + (TString)"_" + (long)(ihist2 + 1), ibin1, 0, ibin1, ibin2, 0, ibin2);
 Correlation_new[ihist1][ihist2] = new TH2D((TString)"Correlation_new_" + (long)(ihist1 + 1) + (TString)"_" + (long)(ihist2 + 1), (TString)"Correlation_new_" + (long)(ihist1 + 1) + (TString)"_" + (long)(ihist2 + 1), ibin1, 0, ibin1, ibin2, 0, ibin2);
}

void ePumpHists::saveHists()
{
 hf->cd();
 hf->Write();

 hf->Close();

}
