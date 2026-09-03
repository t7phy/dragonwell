#include "RootCommon.h"
#include "PDFHelper/PDFReweight.h"

using namespace std;

int main(int argc, char** argv)
{
 TString CDF_File = "/ustcfs2/yfu/pku_resbos/TevatronGrids/CT18NNLO/rootfile/w432+yk/save_LeptonPt_CDF.root";
 TString LHC_File = "/ustcfs2/yfu/MainCode/run/7TeVWMass/save_LeptonPt_LowQT_LHC_Pseudodata.root";

// TString CDF_File = "/ustcfs2/yfu/MainCode/run/TevatronWMass/CT18As/save_LeptonPt_CDF.root";
// TString LHC_File = "/ustcfs2/yfu/MainCode/run/7TeVWMass/CT18As/save_LeptonPt_LowQT_LHC_Pseudodata.root";

 TFile* file1 = new TFile(CDF_File);
 TFile* file2 = new TFile(LHC_File);

 int nSet = 58;

 vector<TH1D *> CDF_WMass(nSet + 1);
 vector<TH1D *> LHC_WMass(nSet + 1);

 for(int i = 0; i < nSet + 1; i++){
   CDF_WMass.at(i) = (TH1D *)file1->Get((TString)"WMassResult_PDF" + (int)i);
   LHC_WMass.at(i) = (TH1D *)file2->Get((TString)"WMassResult_PDF" + (int)i);
 }

 TFile* writefile = new TFile("WMassCorr_LeptonPt.root", "RECREATE");
 writefile->cd();

 TGraph* ellipse;
 TGraph* central;

 PDFReweight* run = new PDFReweight();
 run->DrawPartonCorrelation(CDF_WMass, LHC_WMass, ellipse, central, "Symmetry");

 ellipse->Write(ellipse->GetName());
 central->Write(central->GetName());

 writefile->Write();
 writefile->Close();

 return 1;
}

