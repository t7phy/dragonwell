#include "ReadInRoot/ResBosAngular.h"

using namespace std;

void ResBosAngular::LinkHist(HistsResBos* &myhists)
{
 this->myhists = myhists;
}

void ResBosAngular::WriteIn(TH1D* h1)
{
 for(int i = 0; i < 13; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 char* myDataLine;
 const char* split = ",";

 int ibin = 0;

 while(infile>>FileLine){
   ibin++;

   myDataLine = (char *)FileLine.c_str();

   char* WholeLine = strtok(myDataLine, split);

   for(int i = 1; i <= 10; i++){
     para = stod(WholeLine);
     if(i == 4) DataPoint = para;
     if(i == 5) StaErr = para;
     if(i == 7) SysErr = para;
     if(i == 9) RegBias = para;

     WholeLine = strtok(NULL, split);
   }
   cout<<"DataPoint = "<<DataPoint<<" StaErr = "<<StaErr<<" SysErr = "<<SysErr<<" RegBias = "<<RegBias<<endl;

   h1->SetBinContent(ibin, DataPoint);
   h1->SetBinError(ibin, sqrt(StaErr * StaErr + SysErr * SysErr + RegBias * RegBias));
 }
 infile.close();
}
