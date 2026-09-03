#include "ReadInRoot/ResBosNonPertFit.h"

void ResBosNonPertFit::LinkHist(HistsResBos* &myhists)
{
 this->myhists = myhists;
}

void ResBosNonPertFit::WriteIn(TString ExperimentName)
{
 while(getline(infile, FileLine)){
   if(FileLine.find(((TString)"Summary :  Experiment: " + ExperimentName).Data()) != std::string::npos){
     cout<<FileLine<<endl;
     break;
   }
 }

 for(int i = 0; i < 3; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 char* myDataLine;
 const char* split = " ";
 
 int ibin = 0;
 
 while(getline(infile, FileLine)){
//   if(FileLine.find("Experiment") != std::string::npos || FileLine.find("Final Result") != std::string::npos) break;
   if(FileLine == "Summary : ") break;
   ibin++;
   myDataLine = (char *)FileLine.c_str();
   char* WholeLine = strtok(myDataLine, split);

   for(int i = 1; i <= 6; i++){
     if(i >= 3) para = stod(WholeLine);
     if(i == 3) TheoryPoint = para;
     if(i == 4) DataPoint = para;
     if(i == 5) Uncertainty = para;
     if(i == 6) Residue = para;

     WholeLine = strtok(NULL, split);
   }

   TheoryHist[iplot]->SetBinContent(ibin, TheoryPoint);
   TheoryHist[iplot]->SetBinError(ibin, 0);
   DataHist[iplot]->SetBinContent(ibin, DataPoint);
   DataHist[iplot]->SetBinError(ibin, Uncertainty);
   OriginalDataHist[iplot]->SetBinContent(ibin, DataPoint);
   OriginalDataHist[iplot]->SetBinError(ibin, UnCorrErr);

   cout<<"Summary :   "<<TheoryPoint<<"  "<<DataPoint<<"  "<<Uncertainty<<"  "<<Residue<<endl;
 }

 TheoryHist[iplot]->Write();
 DataHist[iplot]->Write();
 OriginalDataHist[iplot]->Write();

 infile.close();
}

void ResBosNonPertFit::GetBinning(const char* name, int DataID, TString ExperimentName)
{
 iplot++;

 ifstream ptData;
   ptData.open(name, ios::in);

 BinCenter = new double[200];

 char* myDataLine;
 const char* split = " ";

 while(getline(ptData, FileLine)){

   myDataLine = (char *)FileLine.c_str();
   char* WholeLine = strtok(myDataLine, split);

   DataType = stoi(WholeLine);
   if(DataType == DataID){
     TotalBin++;
     for(int i = 1; i <= 13; i++){
       if(i > 1) para = stod(WholeLine);
       if(i == 4) BinCenter[TotalBin] = para;

       WholeLine = strtok(NULL, split);
     }
   }
 }

 Binning = new double[TotalBin + 1];
 Binning[0] = 0.0;
 for(int i = 1; i < TotalBin + 1; i++){
   Binning[i] = 2 * BinCenter[i] - Binning[i - 1];
 }

 DataHist[iplot] = new TH1D(ExperimentName + "_Data", ExperimentName + "_Data", TotalBin, Binning);
 DataHist[iplot]->Sumw2();
 TheoryHist[iplot] = new TH1D(ExperimentName + "_Theory", ExperimentName + "_Theory", TotalBin, Binning);
 TheoryHist[iplot]->Sumw2();
 OriginalDataHist[iplot] = new TH1D(ExperimentName + "_OriginalData", ExperimentName + "_OriginalData", TotalBin, Binning);
 OriginalDataHist[iplot]->Sumw2();

 TotalBin = 0;
 delete[] Binning;

 ptData.close();
}

void ResBosNonPertFit::WriteIn()
{
 iplot = 1;

 int ibin = 0;

 for(int i = 0; i < 4; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 while(infile >> QMin){
   infile >> QMax >> ymin >> ymax;
   ibin++;

   infile >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> reducedChi2;
   TheoryHist[iplot]->SetBinContent(ibin, TheoryPoint);
   TheoryHist[iplot]->SetBinError(ibin, 0.0);
   DataHist[iplot]->SetBinContent(ibin, ShiftData);
   DataHist[iplot]->SetBinError(ibin, UnCorrErr);
   OriginalDataHist[iplot]->SetBinContent(ibin, DataPoint);
   OriginalDataHist[iplot]->SetBinError(ibin, UnCorrErr);
   ReducedChi2[iplot]->SetBinContent(ibin, reducedChi2);
   ReducedChi2[iplot]->SetBinError(ibin, 0.0);

   if(ibin == Nbin){
     ibin = 0;
     iplot++;
   }
 }

/* while(infile >> QMin){
   infile >> QMax >> ymin >> ymax;
   ibin++;
   if(ibin == 1) SavedYmax = ymax;
   if(ibin == 1) SavedQMax = QMax;

   if(ymax == SavedYmax && QMax == SavedQMax){
     infile >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> reducedChi2;
     TheoryHist[iplot]->SetBinContent(ibin, TheoryPoint);
     TheoryHist[iplot]->SetBinError(ibin, 0.0);
     DataHist[iplot]->SetBinContent(ibin, ShiftData);
     DataHist[iplot]->SetBinError(ibin, UnCorrErr);
     OriginalDataHist[iplot]->SetBinContent(ibin, DataPoint);
     OriginalDataHist[iplot]->SetBinError(ibin, UnCorrErr);
   }

   if(ymax > SavedYmax || QMax > SavedQMax){
     ibin = 1;
     infile >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> reducedChi2;
     SavedYmax = ymax;
     SavedQMax = QMax;
     iplot++;

     TheoryHist[iplot]->SetBinContent(ibin, TheoryPoint);
     TheoryHist[iplot]->SetBinError(ibin, 0.0);
     DataHist[iplot]->SetBinContent(ibin, ShiftData);
     DataHist[iplot]->SetBinError(ibin, UnCorrErr);
     OriginalDataHist[iplot]->SetBinContent(ibin, DataPoint);
     OriginalDataHist[iplot]->SetBinError(ibin, UnCorrErr);
   }
 }
*/

 for(int iplot = 1; iplot <= TotalPlot; iplot++){
   TheoryHist[iplot]->Write();
   DataHist[iplot]->Write();
   OriginalDataHist[iplot]->Write();
   ReducedChi2[iplot]->Sumw2();
 }

}

void ResBosNonPertFit::CopyHist(TString ExperimentName, TH1D* h1, int nPlot)
{
 for(int iplot = 1; iplot <= nPlot; iplot++){
   DataHist[iplot] = (TH1D *)h1->Clone(ExperimentName + "_" + (int)iplot + "_Data");
   DataHist[iplot]->Sumw2();
   TheoryHist[iplot] = (TH1D *)h1->Clone(ExperimentName + "_" + (int)iplot + "_Theory");
   TheoryHist[iplot]->Sumw2();
   OriginalDataHist[iplot] = (TH1D *)h1->Clone(ExperimentName + "_" + (int)iplot + "_OriginalData");
   OriginalDataHist[iplot]->Sumw2();
   ReducedChi2[iplot] = (TH1D *)h1->Clone(ExperimentName + "_" + (int)iplot + "_ReducedChi2");
   ReducedChi2[iplot]->Sumw2();
 }

 this->Nbin = h1->GetNbinsX();
 this->TotalPlot = nPlot;
}

void ResBosNonPertFit::GetBinning(const char* name)
{
 iplot++;
 
 ifstream ptData;
   ptData.open(name, ios::in);
   
 TString ExperimentName;
 ptData >> skip >> ExperimentName;

 for(int i = 0; i < 4; i++){
   getline(ptData, FileLine);
   cout<<FileLine<<endl;
 }

 BinCenter = new double[200];

 TotalBin = 0;

 while(ptData >> QMin){
   ptData >> QMax >> ymin >> ymax;
   TotalBin++;
   if(TotalBin == 1) SavedYmax = ymax;
   if(TotalBin == 1) SavedQMax = QMax;

   if(ymax == SavedYmax && QMax == SavedQMax){
//     ptData >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> pdfErr >> reducedChi2;
     ptData >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> reducedChi2;
     BinCenter[TotalBin] = pT;
   }

   if(ymax > SavedYmax || QMax > SavedQMax){
     TotalBin--;
     Binning = new double[TotalBin + 1];
     Binning[0] = 0.0;
     for(int i = 1; i < TotalBin + 1; i++){
       Binning[i] = 2 * BinCenter[i] - Binning[i - 1];
     }

     DataHist[iplot] = new TH1D(ExperimentName + "_" + (int)iplot + "_Data", ExperimentName + "_" + (int)iplot + "_Data", TotalBin, Binning);
     DataHist[iplot]->Sumw2();
     TheoryHist[iplot] = new TH1D(ExperimentName + "_" + (int)iplot + "_Theory", ExperimentName + "_" + (int)iplot + "_Theory", TotalBin, Binning);
     TheoryHist[iplot]->Sumw2();
     OriginalDataHist[iplot] = new TH1D(ExperimentName + "_" + (int)iplot + "_OriginalData", ExperimentName + "_" + (int)iplot + "_OriginalData", TotalBin, Binning);
     OriginalDataHist[iplot]->Sumw2();

     delete[] Binning;
     iplot++;

     TotalBin = 1;
//     ptData >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> pdfErr >> reducedChi2;
     ptData >> pT >> DataPoint >> TheoryPoint >> Uncertainty >> Chi2 >> Shift >> ShiftData >> UnCorrErr >> reducedChi2;
     BinCenter[TotalBin] = pT;
     SavedYmax = ymax;
     SavedQMax = QMax;
   }
 }

 Binning = new double[TotalBin + 1];
 Binning[0] = 0.0;
// Binning[0] = 2.0 * BinCenter[1] - BinCenter[2];
 for(int i = 1; i < TotalBin + 1; i++){
   Binning[i] = 2 * BinCenter[i] - Binning[i - 1];
//   Binning[i] = BinCenter[i];
 }

 DataHist[iplot] = new TH1D(ExperimentName + "_" + (int)iplot + "_Data", ExperimentName + "_" + (int)iplot + "_Data", TotalBin, Binning);
 DataHist[iplot]->Sumw2();
 TheoryHist[iplot] = new TH1D(ExperimentName + "_" + (int)iplot + "_Theory", ExperimentName + "_" + (int)iplot + "_Theory", TotalBin, Binning);
 TheoryHist[iplot]->Sumw2();
 OriginalDataHist[iplot] = new TH1D(ExperimentName + "_" + (int)iplot + "_OriginalData", ExperimentName + "_" + (int)iplot + "_OriginalData", TotalBin, Binning);
 OriginalDataHist[iplot]->Sumw2();

 delete[] Binning;

 TotalPlot = iplot;

 ptData.close();

}

void ResBosNonPertFit::Get2DPlot()
{
 iplot2D++;

 vector<TH1D *> DataHists;
 vector<TH1D *> TheoryHists;
 vector<TH1D *> OriginalDataHists;

 for(int i = 1; i<= TotalPlot; i++){
   DataHists.push_back(DataHist[i]);
   TheoryHists.push_back(TheoryHist[i]);
   OriginalDataHists.push_back(OriginalDataHist[i]);
 }

// double BinningY[7] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
// ConstructTH2D(DataHists, Data2D[iplot2D], BinningY);
// ConstructTH2D(TheoryHists, Theory2D[iplot2D], BinningY);

 ConstructTH2D(DataHists, Data2D[iplot2D], TotalPlot);
 ConstructTH2D(TheoryHists, Theory2D[iplot2D], TotalPlot);
 ConstructTH2D(OriginalDataHists, OriginalData2D[iplot2D], TotalPlot);

 Data2D[iplot2D]->Write();
 Theory2D[iplot2D]->Write();
 OriginalData2D[iplot2D]->Write();
}

void ResBosNonPertFit::RetrieveHist(TString Type, int Index, TH1D* &hist)
{
 if(Type == "Theory") hist = this->TheoryHist[Index];
}
