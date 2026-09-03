#include "ReadInRoot/CMSAFB.h"

using namespace std;

void CMSAFB::LinkHist(HistsResBos* &myhists)
{
 this->myhists = myhists;
}

void CMSAFB::WriteIn(TH1D* &h1)
{
 for(int i = 0; i < 4; i++){
   getline(infile, FileLine);
   cout<<FileLine<<endl;
 }

 char* myDataLine;
 const char* split = ",";

 int ibin = 0;

 while(infile>>FileLine){
   myDataLine = (char *)FileLine.c_str();

   char* WholeLine = strtok(myDataLine, split);

   for(int i = 1; i <= 8; i++){
     para = stod(WholeLine);
     if(i == 2) BinLeft = para;
     if(i == 3) BinRight = para;
     if(i == 4) DataPoint = para;
     if(i == 5) StaErr = para;
     if(i == 7) SysErr = para;

     WholeLine = strtok(NULL, split);
   }

   if(!(BinRight > 150.0 || BinLeft < 60.0)){
     ibin++;

     cout<<"DataPoint = "<<DataPoint<<" StaErr = "<<StaErr<<" SysErr = "<<SysErr<<endl;

     h1->SetBinContent(ibin, DataPoint);
     h1->SetBinError(ibin, sqrt(StaErr * StaErr + SysErr * SysErr));
   }
 }
 infile.close();
}
