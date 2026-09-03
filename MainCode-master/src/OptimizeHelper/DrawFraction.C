#include "OptimizeHelper/DrawFraction.h"

using namespace std;

DrawFraction::DrawFraction(const char* FracFile)
{
 infile.open(FracFile, ios::in);
}

void DrawFraction::LinkHist(FractionHist* myhists)
{
 this->myhists = myhists;
}

void DrawFraction::FillHist()
{
 while(getline(infile, FileLine)){
   if(FileLine.find("Fractional contribution of Optimized")!=std::string::npos){
     cout<<FileLine<<endl;
     break;
   }
 }

 for(int i = 0; i < 3; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 while(infile >> DataSet){
//   if(DataSet != iDataSet) break;

   infile >> iObs;

   if(DataSet == SkipBinsDataSet && iObs >= SkipBins) iObs = iObs + 1;
   for(int i = 1; i <= EVMax; i++){
     infile >> DataPoint;
     myhists->Fill(DataSet, i, iObs, DataPoint);
   }
 }

}

void DrawFraction::SkipBin(int iDataSet, int ibin)
{
 this->SkipBins = ibin;
 this->SkipBinsDataSet = iDataSet;
}
