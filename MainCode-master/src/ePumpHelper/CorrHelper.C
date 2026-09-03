#include "ePumpHelper/ePumpHelper.h"

void ePumpHelper::DrawCorrChi2AndData(TString Data1, TString Data2)
{
 // Draw correlation between chi2 of Data1 and data points of Data2

 cout<<"Draw correlation between Chi2 of "<<Data1<<" and each data points of "<<Data2<<endl;

 if(isLinkFile) hf->cd();

 TString HistName = "CorrChi2AndData_" + Data1 + "_" + Data2;
 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");

 CorrHistChi2AndData[make_tuple(Data1, Data2)] = new TH1D(HistName, HistName, DataNPoints.at(Data2), 0, DataNPoints.at(Data2));

 vector<double> Chi2Set(NEV);

 for(int i = 0; i < NEV; i++){
   Chi2Set.at(i) = (OldChi2Set.at(Data1).at(2 * i + 2) - OldChi2Set.at(Data1).at(2 * i + 1)) / 2.0;
 }

 for(int ipoint = 0; ipoint < DataNPoints.at(Data2); ipoint++){
   vector<double> DataPointSet(NEV);
   for(int i = 0; i < NEV; i++){
     DataPointSet.at(i) = (TheoryTemplate.at(Data2).at(ipoint).at(2 * i + 2) - TheoryTemplate.at(Data2).at(ipoint).at(2 * i + 1)) / 2.0;
   }

   double Correlation = CalcCorrelation(Chi2Set, DataPointSet);
   CorrHistChi2AndData.at(make_tuple(Data1, Data2))->SetBinContent(ipoint + 1, Correlation);
   CorrHistChi2AndData.at(make_tuple(Data1, Data2))->SetBinError(ipoint + 1, 0.0);

   DataPointSet.clear();
 }

}

void ePumpHelper::DrawCorrChi2AndData(vector<TString> DataNames, TString Data2)
{
 // Draw correlation between chi2 of Data1 and data points of Data2

 cout<<"Draw correlation between sum of Chi2 of ";
 for(int i = 0; i < DataNames.size(); i++){
   cout<<DataNames.at(i);
   if(i != DataNames.size() - 1) cout<<", ";
 }
 cout<<" and each data points of "<<Data2<<endl;

 if(isLinkFile) hf->cd();

 TString HistName = "CorrChi2AndData_Sum_";
 for(int i = 0; i < DataNames.size(); i++){ 
   HistName = HistName + DataNames.at(i);
   if(i != DataNames.size() - 1) HistName = HistName + "_";
 }
 HistName = HistName + "_and_" + Data2;

 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");

 CorrHistSumChi2AndData[make_tuple(DataNames, Data2)] = new TH1D(HistName, HistName, DataNPoints.at(Data2), 0, DataNPoints.at(Data2));

 vector<double> Chi2Set(NEV);

 for(int i = 0; i < NEV; i++){
   double Chi2Up = 0.0;
   double Chi2Down = 0.0;
   for(int idata = 0; idata < DataNames.size(); idata++){
     Chi2Up += OldChi2Set.at(DataNames.at(idata)).at(2 * i + 2);
     Chi2Down += OldChi2Set.at(DataNames.at(idata)).at(2 * i + 1);
   }
   Chi2Set.at(i) = (Chi2Up - Chi2Down) / 2.0;
 }

 for(int ipoint = 0; ipoint < DataNPoints.at(Data2); ipoint++){
   vector<double> DataPointSet(NEV);
   for(int i = 0; i < NEV; i++){
     DataPointSet.at(i) = (TheoryTemplate.at(Data2).at(ipoint).at(2 * i + 2) - TheoryTemplate.at(Data2).at(ipoint).at(2 * i + 1)) / 2.0;
   }

   double Correlation = CalcCorrelation(Chi2Set, DataPointSet);
   CorrHistSumChi2AndData.at(make_tuple(DataNames, Data2))->SetBinContent(ipoint + 1, Correlation);
   CorrHistSumChi2AndData.at(make_tuple(DataNames, Data2))->SetBinError(ipoint + 1, 0.0);

   DataPointSet.clear();
 }

}

double ePumpHelper::CalcCorrelation(vector<double> A, vector<double> B)
{
 double corr = 0.0;

 if(A.size() != B.size()){
   cout<<"ERROR! Two observables don't match."<<endl;
   return 0.0;
 }

 double Numer = 0.0;
 double DeltaA = 0.0;
 double DeltaB = 0.0;
 for(int i = 0; i < A.size(); i++){
   Numer += A.at(i) * B.at(i);
   DeltaA += A.at(i) * A.at(i);
   DeltaB += B.at(i) * B.at(i);
 }

 if(fabs(DeltaA * DeltaB) > 1e-16) corr = Numer / sqrt(DeltaA * DeltaB);
 else corr = 0.0;

 return corr;
}
