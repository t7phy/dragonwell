#include "ePump/ePumpHists.h"

using namespace std;

void ePumpHists::openFile(const char* fName)
{
 hf = new TFile(fName, "RECREATE");

 hf->cd();
}

void ePumpHists::bookHists(const char* histName, int ihist, int ibin)
{
 hf->cd();

 Observable_old[ihist] = new TH1D((TString)histName + (TString)"_old", (TString)histName + (TString)"_old", ibin, 0, ibin);
 Observable_new[ihist] = new TH1D((TString)histName + (TString)"_new", (TString)histName + (TString)"_new", ibin, 0, ibin);
 ObservableData_old[ihist] = new TH1D((TString)histName + (TString)"_oldData", (TString)histName + (TString)"_oldData", ibin, 0, ibin);
 ObservableData_new[ihist] = new TH1D((TString)histName + (TString)"_newData", (TString)histName + (TString)"_newData", ibin, 0, ibin);
 PDFError_old[ihist] = new TH1D((TString)histName + (TString)"_oldPDFError", (TString)histName + (TString)"_oldPDFError", ibin, 0, ibin);
 PDFError_new[ihist] = new TH1D((TString)histName + (TString)"_newPDFError", (TString)histName + (TString)"_newPDFError", ibin, 0, ibin);

 nHist++;
}

void ePumpHists::bookHists(int ihist1, int ihist2, int ibin1, int ibin2)
{
 hf->cd();

 Correlation_old[ihist1][ihist2] = new TH2D((TString)"Correlation_old_" + (int)(ihist1 + 1) + (TString)"_" + (int)(ihist2 + 1), (TString)"Correlation_old_" + (int)(ihist1 + 1) + (TString)"_" + (int)(ihist2 + 1), ibin1, 0, ibin1, ibin2, 0, ibin2);
 Correlation_new[ihist1][ihist2] = new TH2D((TString)"Correlation_new_" + (int)(ihist1 + 1) + (TString)"_" + (int)(ihist2 + 1), (TString)"Correlation_new_" + (int)(ihist1 + 1) + (TString)"_" + (int)(ihist2 + 1), ibin1, 0, ibin1, ibin2, 0, ibin2);

}

void ePumpHists::saveHists()
{
 cout<<"save histogram for ePumpHist, nHist = "<<nHist<<endl;

 hf->cd();
 hf->Write();
/* for(int i = 1; i <= nHist; i++){
   Observable_old[i]->Write();
   Observable_new[i]->Write();
   PDFError_old[i]->Write();
   PDFError_new[i]->Write();
   for(int j = 1; j <= nHist; j++){
     Correlation_old[i][j]->Write();
     Correlation_new[i][j]->Write();
   }
 }
*/

 hf->Close();

}
