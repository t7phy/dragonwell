#include <iostream>
#include "ReadInRoot/ePumpOutput.h"
#include "Analysis/HistsResBos.h"
#include "RootCommon.h"

using namespace std;

int main(int argc, char** argv)
{
// HistsResBos* myhists = new HistsResBos();
// myhists->openFile("save.root");

// Run->LinkHist(myhists);

 TFile *file = new TFile("save.root", "RECREATE");
 file->cd();

 double FirstSTW = 0.2255 - 0.0003 / 2;
 double LastSTW = 0.2372 + 0.0003 / 2;
 TH2D* OldResults = new TH2D("OldResults", "OldResults", 33, 1.0, 33.0, 40, FirstSTW, LastSTW);
 TH2D* NewResults = new TH2D("NewResults", "NewResults", 33, 1.0, 33.0, 40, FirstSTW, LastSTW);
 TH2D* DeltaResults = new TH2D("DeltaResults", "DeltaResults", 33, 1.0, 33.0, 40, FirstSTW, LastSTW);

// myhists->saveHists();

 for(int i = 0; i < 40; i++){
   int STWINPUT = 2255 + 3 * i;
   ePumpOutput* Run = new ePumpOutput();
   Run->openFile((TString)"updated-by-FullAFB-" + (int)STWINPUT + (TString)".out");
   Run->WriteIn();
   TH1D* Old;
   TH1D* New;
   TH1D* Delta;
   Run->RetrieveHist(Old, New, Delta);
   for(int ibin = 1; ibin <= Old->GetNbinsX(); ibin++){
     OldResults->SetBinContent(ibin, i + 1, Old->GetBinContent(ibin));
     OldResults->SetBinError(ibin, i + 1, 0.0);
     NewResults->SetBinContent(ibin, i + 1, New->GetBinContent(ibin));
     NewResults->SetBinError(ibin, i + 1, 0.0);
     DeltaResults->SetBinContent(ibin, i + 1, Delta->GetBinContent(ibin));
     DeltaResults->SetBinError(ibin, i + 1, 0.0);
   }
 }

 file->Write();
 file->Close();

 cout<<"Master thread is end."<<endl;
 return 0;
}
