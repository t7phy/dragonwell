#include "ReadInRoot/MCFMWWBoost.h"

void MCFMWWBoost::LinkHist(HistsResBos* &myhists)
{
 this->myhists = myhists;
}

void MCFMWWBoost::WriteIn(TString VariableName)
{
 while(getline(infile, FileLine)){
   if(FileLine.find(VariableName.Data()) != std::string::npos){
     cout<<FileLine<<endl;
     break;
   }
 }

 char* myDataLine;
 const char* split = " ";

 int ibin = 0;

 vector<double> DataVector;

 while(getline(infile, FileLine)){
   ibin++;
   myDataLine = (char *)FileLine.c_str();
   char* WholeLine = strtok(myDataLine, split);

   DataVector.clear();
   while(WholeLine != NULL){
     TString skip = WholeLine;
     if(skip.Contains("+200")) break;
     para = stod(WholeLine);
     DataVector.push_back(para);
     WholeLine = strtok(NULL, split);
   }

   if(DataVector.size() == 4){
     DataPoint = DataVector.at(2);
     Uncertainty = DataVector.at(3);
   }

   if(DataVector.size() != 4) break;

   double BinWidth = DataHist[VariableName]->GetXaxis()->GetBinUpEdge(ibin) - DataHist[VariableName]->GetXaxis()->GetBinLowEdge(ibin);

   DataHist[VariableName]->SetBinContent(ibin, DataPoint / 1000.0);
   DataHist[VariableName]->SetBinError(ibin, Uncertainty / 1000.0);

   cout<<"Summary :   "<<DataHist[VariableName]->GetXaxis()->GetBinLowEdge(ibin)<<"  "<<DataHist[VariableName]->GetXaxis()->GetBinUpEdge(ibin)<<"  "<<DataPoint<<"  "<<Uncertainty<<endl;
 }

 DataHist[VariableName]->Write();

 infile.close();
}

void MCFMWWBoost::GetBinning(const char* name, TString VariableName)
{
 iplot++;

 ifstream myData;
   myData.open(name, ios::in);

 BinCenter = new double[200];
 DeltaBin = new double[200];

 while(getline(myData, FileLine)){
   if(FileLine.find(VariableName.Data()) != std::string::npos){
     break;
   }
 }

 char* myDataLine;
 const char* split = " ";

 vector<double> DataVector;

 while(getline(myData, FileLine)){
   myDataLine = (char *)FileLine.c_str();
   char* WholeLine = strtok(myDataLine, split);

   DataVector.clear();
   while(WholeLine != NULL){
     TString skip = WholeLine;
     if(skip.Contains("+200")) break;
     para = stod(WholeLine);
     DataVector.push_back(para);
     WholeLine = strtok(NULL, split);
   }

   if(DataVector.size() == 4){
     BinCenter[TotalBin] = DataVector.at(0);
     DeltaBin[TotalBin] = DataVector.at(1);
     TotalBin++;
   }

   if(DataVector.size() != 4) break;
 }

 Binning = new double[TotalBin + 1];
 Binning[0] = BinCenter[0] - DeltaBin[0];
 for(int i = 1; i < TotalBin + 1; i++){
   Binning[i] = BinCenter[i - 1] + DeltaBin[i - 1];
 }

 DataHist[VariableName] = new TH1D(VariableName + subName, VariableName + subName, TotalBin, Binning);

 TotalBin = 0;
 delete[] Binning;
 delete[] BinCenter;
 delete[] DeltaBin;
}

void MCFMWWBoost::GetAdditionalPlot()
{
/* BoostAsymmetry = (TH1D *)DataHist[5]->Clone((TString)"BoostAsymmetry_AllFlavor" + subName);
 BoostAsymmetry->Reset();

 AFBFunction(DataHist[5], DataHist[6], BoostAsymmetry);

 BoostAsymmetryW = (TH1D *)DataHist[7]->Clone((TString)"BoostAsymmetryW_AllFlavor" + subName);
 BoostAsymmetryW->Reset();

 AFBFunction(DataHist[7], DataHist[8], BoostAsymmetryW);

 BoostAsymmetry->Write();
 BoostAsymmetryW->Write();
*/

}

void MCFMWWBoost::ReadInMCFM_10_3(TString FileName, TH1D* &hist, int RemoveBins)
{
 ifstream infile;
  infile.open(FileName, ios::in);

 for(int i = 1; i <= 5; i++){
   getline(infile, FileLine);
 }

 for(int i = 0; i < RemoveBins; i++){
   int ibin = 1 + i;
   hist->SetBinContent(ibin, 1.0);
   hist->SetBinError(ibin, 0.1);
 }

 double xmin, xmax, cross, numerror;
 int ibin = 0;
 while(infile >> xmin){
   ibin++;
   infile >> xmax >> cross >> numerror;
   //hist->SetBinContent(RemoveBins + ibin, cross / (xmax - xmin));
   hist->SetBinContent(RemoveBins + ibin, cross / 1000.0);
   hist->SetBinError(RemoveBins + ibin, 0.0);
 }
 if(ibin + RemoveBins != hist->GetNbinsX()){
   cout<<"ERROR! Binning doesn't match to the input file."<<endl;
 }
}
