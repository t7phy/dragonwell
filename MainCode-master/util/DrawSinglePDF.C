#include <cstdlib>
#include <string>
#include "Tools/Tools.h"
#include "PDFHelper/PDFFigure.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "RootCommon.h"

int main(int argc, char** argv)
{
 if(argc < 4){
   cout<<"usage ./DrawPDF n [PDFName1] [LegendName1] [PDFName2] [LegendName2] ..."<<endl;
   return 0;
 }

 int nErrorPDF = stoi(argv[1]) / 10;
 int nSinglePDF = stoi(argv[1]) % 10;

 int nPDF = nErrorPDF + nSinglePDF;

 vector<TString> PDFName(10);
 vector<TString> LegendName(10);

 bool misMatch = false;
 if((nPDF == 1 && argc != 4) || (nPDF != 1 && argc == 4)) misMatch = true;
 if((nPDF == 2 && argc != 6) || (nPDF != 2 && argc == 6)) misMatch = true;
 if((nPDF == 3 && argc != 8) || (nPDF != 3 && argc == 8)) misMatch = true;
 if((nPDF == 4 && argc != 10) || (nPDF != 4 && argc == 10)) misMatch = true;
 if((nPDF == 5 && argc != 12) || (nPDF != 5 && argc == 12)) misMatch = true;
 if((nPDF == 6 && argc != 14) || (nPDF != 6 && argc == 14)) misMatch = true;

 if(misMatch){
   cout<<"usage ./DrawPDF n [PDFName1] [LegendName1] [PDFName2] [LegendName2] ..."<<endl;
   return 0;
 }

 PDFFigure* run = new PDFFigure();
 //run->SetLegendPosition(0.01, 0.7, 0.8, 0.95);
 //run->SetTextLeftBias(0.0);

 run->openFile("PDFFigure.root");
 for(int i = 1; i <= nErrorPDF; i++){
   TString PDFName = argv[i * 2];
   if(PDFName.Contains("lha_")){
     PDFName.ReplaceAll("lha_", "");
     run->InitialPDFAll(PDFName);
   }
   else{
     run->InitialCTEQPDFAll(PDFName, PDFName);
   }
   run->SetLegendName(PDFName, argv[i * 2 + 1]);
   LegendName.at(i) = argv[i * 2 + 1];
 }

 vector<TString> ErrorPDFNames(nErrorPDF);

 for(int i = 1; i <= nErrorPDF; i++){
   TString PDFName = argv[i * 2];
   PDFName.ReplaceAll("lha_", "");
   ErrorPDFNames.at(i - 1) = PDFName;
 }

 vector<TString> SinglePDFNames(nSinglePDF);

 for(int i = 1; i <= nSinglePDF; i++){
   TString PDFName = argv[nErrorPDF * 2 + i * 2];
   if(PDFName.Contains("lha_")){
     PDFName.ReplaceAll("lha_", "");
     run->InitialSingleLHAPDF(PDFName, 0);
     SinglePDFNames.at(i - 1) = PDFName;
     LegendName.at(i + nErrorPDF) = argv[nErrorPDF * 2 + i * 2 + 1];
   }
   else{
     run->InitialSingleCTEQPDF(argv[nErrorPDF * 2 + i * 2 + 1], argv[nErrorPDF * 2 + i * 2]);
     SinglePDFNames.at(i - 1) = argv[nErrorPDF * 2 + i * 2 + 1];
     LegendName.at(i + nErrorPDF) = argv[nErrorPDF * 2 + i * 2 + 1];
   }
 }

 int LegendLengthMax = 0;

 for(int i = 0; i < LegendName.size(); i++){
   if(LegendName.at(i).Length() > LegendLengthMax) LegendLengthMax = LegendName.at(i).Length();
 }

 double LegendLeftBias = 0.2 * (LegendLengthMax - 18) / 7;
 LegendLeftBias = LegendLeftBias > 0.39 ? 0.39 : LegendLeftBias;
 if(LegendLeftBias < 0) LegendLeftBias = 0;

 run->SetLegendPosition(run->LegendXmin - LegendLeftBias, run->LegendYmin, run->LegendXmax, run->LegendYmax);
 run->SetTextLeftBias(run->TextLeftBias - LegendLeftBias);

 run->SetupNesFlavorList(vector<TString>{"gluon", "u", "d", "s", "c", "b", "ubar", "dbar", "uv", "dv", "dbou", "ubod", "ubou", "dbod", "dboub", "dou", "Rs"});

////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////

 run->GenerateSinglePDFAll(ErrorPDFNames, SinglePDFNames, 100.0);
 run->GenerateSinglePDFAll(ErrorPDFNames, SinglePDFNames, 1.3);

 TString TexFileName = "";
 for(int i = 1; i <= nErrorPDF + nSinglePDF; i++){
   TString LegendName = argv[i * 2 + 1];
   LegendName.ReplaceAll(" ", "_");
   LegendName.ReplaceAll("+", "");
   LegendName.ReplaceAll("(", "_");
   LegendName.ReplaceAll(")", "_");

   TexFileName = TexFileName + LegendName + "_";
 }
 TexFileName = TexFileName + "Q100.tex";
 run->OutputTexFile(TexFileName);

 TString command = (TString)"pdflatex "+ TexFileName;
 system(command.Data());

// run->GenerateErrorAll(vector<TString>{(TString)argv[1], (TString)argv[2]}, vector<TString>{"Symmetry", "Symmetry"}, 100.0);

// run->SetupNesFlavorList(vector<TString>{"u", "d", "s", "c", "b", "ubar", "dbar", "sbar", "cbar", "bbar", "gluon", "gluon5"});
// run->GenerateErrorAll(vector<TString>{"CT18NNLO", "CT18ANNLO"}, vector<TString>{"Symmetry", "Symmetry"}, 100.0);
// run->SetLegendName("CT18NNLO", "CT18");
// run->SetYRange(0.0, 2.0);
// run->GeneratexPDF("CT18NNLO", "Symmetry", vector<TString>{"s", "gluon5", "u", "d", "dbar", "ubar", "c"}, 2.0);
// run->GeneratexPDF("CT18NNLO", "Symmetry", vector<TString>{"s", "gluon5", "u", "d", "dbar", "ubar", "c", "b"}, 100.0);
 run->SaveFile();

 //vector<double> xValues = {0.0001, 0.001, 0.01, 0.1, 0.3, 0.5, 0.7, 0.9};

/* PDFFigure *data = new PDFFigure();
 data->openFile("PDFFigure.root");

 data->InitialPDF(1, "CT18NNLO");
 data->InputPDFnSet(1, 58);
 data->InitialPDF(2, "MSHT20nnlo_as118");
 data->InputPDFnSet(2, 64);
 data->InitialPDF(3, "NNPDF40_nnlo_as_01180_hessian");
 data->InputPDFnSet(3, 50);
 data->SetCL68(1);
 data->SetCL68(2);
*/

/*
 data->InitialPDF(1, "NNPDF40_nlo_as_01180");
 data->InitialPDF(2, "NNPDF40_nnlo_as_01180_hessian");
 data->InitialPDF(3, "MSHT20nnlo_as118");
 data->InitialPDF(4, "CT18ANNLO_moreX");

 for(int i = 0; i < xValues.size(); i++){
   TH1D* gluon1 = data->DrawPDFvsQ(1, 0, xValues.at(i), QValues);
   TH1D* c1 = data->DrawPDFvsQ(1, 4, xValues.at(i), QValues);
   TH1D* cbar1 = data->DrawPDFvsQ(1, -4, xValues.at(i), QValues);
   TH1D* b1 = data->DrawPDFvsQ(1, 5, xValues.at(i), QValues);
   TH1D* bbar1 = data->DrawPDFvsQ(1, -5, xValues.at(i), QValues);

   TH1D* gluon2 = data->DrawPDFvsQ(2, 0, xValues.at(i), QValues);
   TH1D* c2 = data->DrawPDFvsQ(2, 4, xValues.at(i), QValues);
   TH1D* cbar2 = data->DrawPDFvsQ(2, -4, xValues.at(i), QValues);
   TH1D* b2 = data->DrawPDFvsQ(2, 5, xValues.at(i), QValues);
   TH1D* bbar2 = data->DrawPDFvsQ(2, -5, xValues.at(i), QValues);

   TH1D* gluon3 = data->DrawPDFvsQ(3, 0, xValues.at(i), QValues);
   TH1D* c3 = data->DrawPDFvsQ(3, 4, xValues.at(i), QValues);
   TH1D* cbar3 = data->DrawPDFvsQ(3, -4, xValues.at(i), QValues);
   TH1D* b3 = data->DrawPDFvsQ(3, 5, xValues.at(i), QValues);
   TH1D* bbar3 = data->DrawPDFvsQ(3, -5, xValues.at(i), QValues);

   TH1D* gluon4 = data->DrawPDFvsQ(4, 0, xValues.at(i), QValues);
   TH1D* c4 = data->DrawPDFvsQ(4, 4, xValues.at(i), QValues);
   TH1D* cbar4 = data->DrawPDFvsQ(4, -4, xValues.at(i), QValues);
   TH1D* b4 = data->DrawPDFvsQ(4, 5, xValues.at(i), QValues);
   TH1D* bbar4 = data->DrawPDFvsQ(4, -5, xValues.at(i), QValues);

   gluon1->Write();
   gluon2->Write();
   gluon3->Write();
   gluon4->Write();
   c1->Write();
   c2->Write();
   c3->Write();
   c4->Write();
   cbar1->Write();
   cbar2->Write();
   cbar3->Write();
   cbar4->Write();
   b1->Write();
   b2->Write();
   b3->Write();
   b4->Write();
   bbar1->Write();
   bbar2->Write();
   bbar3->Write();
   bbar4->Write();
 }
*/

// vector<double> xValues = Logspace(1e-5, 1, 500, 10);

// data->InitialPDF(1, "CT18NNLO", 0);
// data->InitialPDF(2, "CT18NNLO", 1);
// data->InitialPDF(3, "CT18NNLO", 2);
// data->InitialCTEQPDF(1, "i2Tn3.58/i2Tn3.00.pds", "CT18NNLO", 0);
// data->InitialCTEQPDF(2, "i2Tn3.58/i2Tn3.01.pds", "CT18NNLO", 1);
// data->InitialCTEQPDF(3, "i2Tn3.58/i2Tn3.02.pds", "CT18NNLO", 2);

// TH1D* dbar_0 = data->DrawPDFvsX(1, -1, 100.0, xValues);
// TH1D* dbar_1 = data->DrawPDFvsX(2, -1, 100.0, xValues);
// TH1D* dbar_2 = data->DrawPDFvsX(3, -1, 100.0, xValues);

/* data->GetPDFCentral(1, 13);
 data->GetPDFCentral(1, 14);
 data->GetPDFCentral(1, 18);
 data->GetPDFCentral(1, 19);
 data->GetPDFCentral(2, 13);
 data->GetPDFCentral(2, 14);
 data->GetPDFCentral(2, 18);
 data->GetPDFCentral(2, 19);
 data->GetPDFCentral(3, 13);
 data->GetPDFCentral(3, 14);
 data->GetPDFCentral(3, 18);
 data->GetPDFCentral(3, 19);
*/

// data->TimeX();

// data->CompareTwoPDFWithError(1);
// data->CompareTwoPDFWithError(13);
// data->CompareTwoPDFWithError(14);
// data->CompareTwoPDFWithError(15);

// data->GetPDFRatio(1, 1, 2);
// data->GetPDFEigenRatio(2, 1, 0, 40);
// data->ComparePDFWithEigen(1, 2, 13);
// data->ComparePDFWithEigen(1, 3, 14);
// data->ComparePDFWithEigen(2, 3, 13);
// data->ComparePDFWithEigen(2, 3, 14);


// data->GetPDFCentral(1, 7);
// data->GetPDFCentral(1, 12);

// TH1D* Y = new TH1D("Y", "Y", 20, -5, 5);
// double Q = 90.0;

/* for(int i = 1; i <= Y->GetNbinsX(); i++){
   double x1 = (Q / 6500.0) * exp(Y->GetBinCenter(i));
   double x2 = (Q / 6500.0) * exp(Y->GetBinCenter(i) * (-1.0));
   cout<<"Y: ";
   cout<<left<<setw(6)<<fixed<<setprecision(3)<<Y->GetBinCenter(i);
   cout<<" x1:";
   cout<<left<<setw(10)<<fixed<<setprecision(5)<<x1;
   cout<<" x2:";
   cout<<left<<setw(10)<<fixed<<setprecision(5)<<x2;
   cout<<" u/ub(x1):";
   cout<<left<<setw(10)<<fixed<<setprecision(7)<<data->Getf(1, 16, x1, Q);
   cout<<" u/ub(x2): ";
   cout<<left<<setw(10)<<fixed<<setprecision(7)<<data->Getf(1, 16, x2, Q)<<endl;
   cout<<"Y: ";
   cout<<left<<setw(6)<<fixed<<setprecision(3)<<Y->GetBinCenter(i);
   cout<<" x1:";
   cout<<left<<setw(10)<<fixed<<setprecision(5)<<x1;
   cout<<" x2:";
   cout<<left<<setw(10)<<fixed<<setprecision(5)<<x2;
   cout<<" d/db(x1):";
   cout<<left<<setw(10)<<setprecision(7)<<data->Getf(1, 17, x1, Q);
   cout<<" d/db(x2): ";
   cout<<left<<setw(10)<<setprecision(7)<<data->Getf(1, 17, x2, Q)<<endl;
 }
*/

// data->SaveFile();

 return 1;
}
