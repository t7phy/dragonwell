#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 double massrange[31] = {60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120};

 vector<TString> rootNames;
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 vector<TString> STWTemplates;
  infile.open("STWTemplate.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }

// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_nnpdf.root";
 TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/If1363.00/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/If1363.01/MC_results.root";
// TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/Pseudodata_0.2315/MC_results_AFBRotation.root";

 TString EtaRegion = "Full";

 TString VariableName = "AFB_" + EtaRegion;

 TFile* writefile = new TFile(VariableName + "_PDFResults.root", "RECREATE");
 writefile->cd();

 TString Var = "ZPt";

 TString SlopeZYName = "AFBSlope_" + Var + "_" + EtaRegion;
 TString QuarkSlopeZYName = "AFBQuarkSlope_" + Var + "_" + EtaRegion;
 TString S0FractionName = "AFBS0Fraction_" + Var + "_" + EtaRegion;

 if(EtaRegion == "Full") EtaRegion = "";
 if(EtaRegion == "CC") EtaRegion = "_CC";
 if(EtaRegion == "CF") EtaRegion = "_CF";

 TString Dilution2D_uu_Name = "Dilution_ZMass_" + Var + EtaRegion + "_uu";
 TString Dilution2D_dd_Name = "Dilution_ZMass_" + Var + EtaRegion + "_dd";

 TString FZmass_ZY_uu_Name = "FZmass_" + Var + EtaRegion + "_uu";
 TString FZmass_ZY_dd_Name = "FZmass_" + Var + EtaRegion + "_dd";
 TString FZmass_ZY_gg_Name = "FZmass_" + Var + EtaRegion + "_gg";
 TString BZmass_ZY_uu_Name = "BZmass_" + Var + EtaRegion + "_uu";
 TString BZmass_ZY_dd_Name = "BZmass_" + Var + EtaRegion + "_dd";
 TString BZmass_ZY_gg_Name = "BZmass_" + Var + EtaRegion + "_gg";

 TFile *DataFile = new TFile(DataName);
 TH1D *DataAFB = (TH1D *)DataFile->Get(VariableName);
 TH1D *DataSlopeZY = (TH1D *)DataFile->Get(SlopeZYName);
 TH1D *DataAFB_60_120 = (TH1D *)DataAFB->Rebin(30, VariableName, massrange);

 writefile->cd();
 DataAFB_60_120->Write();

 int FirstBin = 11;
 int LastBin = 20;

 TH1D *PDFS0[57];
 TH2D *Dilution_uu[57];
 TH2D *Dilution_dd[57];
 TH2D *DeltaD_uu[57];
 TH2D *DeltaD_dd[57];
 vector<TH1D *> PDFS0s;
 vector<TH2D *> Dilution_uus;
 vector<TH2D *> Dilution_dds;
 vector<TH2D *> DeltaD_uus;
 vector<TH2D *> DeltaD_dds;
 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));

   writefile->cd();
   TH1D* QuarkSlopeZY = (TH1D *)file->Get(QuarkSlopeZYName);
   TH1D* SlopeZY = (TH1D *)file->Get(SlopeZYName);
   TH2D* S0Fraction = (TH2D *)file->Get(S0FractionName);

   PDFS0[i] = (TH1D *)DataSlopeZY->Clone((TString)"S0_PDF" + (int)i);
   for(int ibin = 1; ibin <= PDFS0[i]->GetNbinsX(); ibin++){
     double S0FractionValue = S0Fraction->GetBinContent(1, ibin);
     //S0FractionValue = 1.0;

     PDFS0[i]->SetBinContent(ibin, (1 - DataSlopeZY->GetBinContent(ibin) / QuarkSlopeZY->GetBinContent(ibin) / S0FractionValue) / 2);
     PDFS0[i]->SetBinError(ibin, (DataSlopeZY->GetBinError(ibin) / QuarkSlopeZY->GetBinContent(ibin) / S0FractionValue) / 2);

     cout<<"Data S0: "<<PDFS0[i]->GetBinContent(ibin)<<endl;
   }

   Dilution_uu[i] = (TH2D *)file->Get(Dilution2D_uu_Name);
   Dilution_dd[i] = (TH2D *)file->Get(Dilution2D_dd_Name);
   DeltaD_uu[i] = (TH2D *)Dilution_uu[i]->Clone((TString)"DeltaD_uu_PDF" + (int)i);
   DeltaD_dd[i] = (TH2D *)Dilution_dd[i]->Clone((TString)"DeltaD_dd_PDF" + (int)i);

   for(int ibinx = 1; ibinx <= Dilution_uu[i]->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= Dilution_uu[i]->GetNbinsY(); ibiny++){
       double S0FractionValue = S0Fraction->GetBinContent(1, ibiny);
       //S0FractionValue = 1.0;

       double S0 = (1 - SlopeZY->GetBinContent(ibiny) / QuarkSlopeZY->GetBinContent(ibiny) / S0FractionValue) / 2;
       double S0Error = (SlopeZY->GetBinError(ibiny) / QuarkSlopeZY->GetBinContent(ibiny) / S0FractionValue) / 2;

       DeltaD_uu[i]->SetBinContent(ibinx, ibiny, Dilution_uu[i]->GetBinContent(ibinx, ibiny) - S0);
       DeltaD_uu[i]->SetBinError(ibinx, ibiny, sqrt(Dilution_uu[i]->GetBinError(ibinx, ibiny) * Dilution_uu[i]->GetBinError(ibinx, ibiny) + S0Error * S0Error));
       DeltaD_dd[i]->SetBinContent(ibinx, ibiny, Dilution_dd[i]->GetBinContent(ibinx, ibiny) - S0);
       DeltaD_dd[i]->SetBinError(ibinx, ibiny, sqrt(Dilution_dd[i]->GetBinError(ibinx, ibiny) * Dilution_dd[i]->GetBinError(ibinx, ibiny) + S0Error * S0Error));

       if(ibinx == 1) cout<<"MC S0: "<<S0<<endl;

     }
   }

   PDFS0s.push_back(PDFS0[i]);
   DeltaD_uus.push_back(DeltaD_uu[i]);
   DeltaD_dds.push_back(DeltaD_dd[i]);
 }


 TH1D *PDFHist[57];
 vector<TH1D *> PDFHists;

 for(int i = 0; i < 1; i++){
   TFile* file = new TFile(rootNames.at(i));

   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);
   TH2D* PDFDilution_uu = (TH2D *)file->Get(Dilution2D_uu_Name);
   TH2D* PDFDilution_dd = (TH2D *)file->Get(Dilution2D_dd_Name);

   TH2D* Dilution_uu = (TH2D *)DeltaD_uus.at(i)->Clone("Dilution_uu");
   TH2D* Dilution_dd = (TH2D *)DeltaD_dds.at(i)->Clone("Dilution_dd");
   ApplyS0(DeltaD_uus.at(i), Dilution_uu, PDFS0s.at(i));
   ApplyS0(DeltaD_dds.at(i), Dilution_dd, PDFS0s.at(i));

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, Dilution_uu, false, 0.0);
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, Dilution_dd, false, 0.0);
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, Dilution_uu, true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   PDFHist[i] = new TH1D((TString)"AFB_PDF" + (int)i, (TString)"AFB_PDF" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, PDFHist[i]);

   writefile->cd();
   TH1D *MCAFB = (TH1D *)file->Get(VariableName);
   MCAFB = (TH1D *)MCAFB->Rebin(30, VariableName + "_MCPDF" + (int)i, massrange);
   MCAFB->Write();

   PDFHist[i]->Write();
   PDFHists.push_back(PDFHist[i]);

 }

/* TH1D *STWHist[40];
 vector<TH1D *> STWHists;
 for(int i = 0; i < 40; i++){
   TFile* file = new TFile(STWTemplates.at(i));

   TH2D* FZmass_ZY_uu = (TH2D *)file->Get(FZmass_ZY_uu_Name);
   TH2D* FZmass_ZY_dd = (TH2D *)file->Get(FZmass_ZY_dd_Name);
   TH2D* FZmass_ZY_gg = (TH2D *)file->Get(FZmass_ZY_gg_Name);
   TH2D* BZmass_ZY_uu = (TH2D *)file->Get(BZmass_ZY_uu_Name);
   TH2D* BZmass_ZY_dd = (TH2D *)file->Get(BZmass_ZY_dd_Name);
   TH2D* BZmass_ZY_gg = (TH2D *)file->Get(BZmass_ZY_gg_Name);
   TH2D* PDFDilution_uu = (TH2D *)file->Get(Dilution2D_uu_Name);
   TH2D* PDFDilution_dd = (TH2D *)file->Get(Dilution2D_dd_Name);

   TH2D* Dilution_uu = (TH2D *)DeltaD_uus.at(0)->Clone("Dilution_uu");
   TH2D* Dilution_dd = (TH2D *)DeltaD_dds.at(0)->Clone("Dilution_dd");
   ApplyS0(DeltaD_uus.at(0), Dilution_uu, PDFS0s.at(0));
   ApplyS0(DeltaD_dds.at(0), Dilution_dd, PDFS0s.at(0));

   Apply2DDilution(FZmass_ZY_uu, BZmass_ZY_uu, Dilution_uu, false, 0.0);
   Apply2DDilution(FZmass_ZY_dd, BZmass_ZY_dd, Dilution_dd, false, 0.0);
   Apply2DDilution(FZmass_ZY_gg, BZmass_ZY_gg, Dilution_uu, true, 0.0);

   TH2D* FZmass2D = (TH2D *)FZmass_ZY_uu->Clone("FZmass2D");
   FZmass2D->Add(FZmass_ZY_dd);
   FZmass2D->Add(FZmass_ZY_gg);

   TH2D* BZmass2D = (TH2D *)BZmass_ZY_uu->Clone("BZmass2D");
   BZmass2D->Add(BZmass_ZY_dd);
   BZmass2D->Add(BZmass_ZY_gg);

   STWHist[i] = new TH1D((TString)"AFB_STW" + (int)i, (TString)"AFB_STW" + (int)i, FZmass2D->GetNbinsX(), FZmass2D->GetXaxis()->GetBinLowEdge(1), FZmass2D->GetXaxis()->GetBinUpEdge(FZmass2D->GetNbinsX()));

   AFBFunction(FZmass2D, BZmass2D, STWHist[i]);

   writefile->cd();
   STWHist[i]->Write();
   STWHists.push_back(STWHist[i]);
 }

 double ppAFBPDFUnc = 0.0;
 CompareDataTheory *run = new CompareDataTheory();
 run->LinkOutFile(writefile);
 run->InputBinRange(FirstBin, LastBin);
 run->GetPDFUncertainty(PDFHists, STWHists, ppAFBPDFUnc);


 TH1D *Chi2_DeltaS0 = new TH1D("Chi2_DeltaS0", "Chi2_DeltaS0", 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
 TF1 *FittingDeltaS0;
 for(int i = 0; i < STWHists.size(); i++){
   double Chi2 = CalculateChi2(DataAFB, STWHists.at(i), FirstBin, LastBin);
   Chi2_DeltaS0->SetBinContent(i, Chi2);
 }
 double stwDeltaS0, stwErrorDeltaS0;
 Chi2Fitting(Chi2_DeltaS0, FittingDeltaS0, stwDeltaS0, stwErrorDeltaS0);

 cout<<"DeltaS0: "<<endl;
 cout<<"Central value: "<<stwDeltaS0<<" Stat.unc: "<<stwErrorDeltaS0<<" PDF unc: "<<ppAFBPDFUnc<<endl;
*/
 writefile->cd();
 writefile->Write();

 return 1;

}
