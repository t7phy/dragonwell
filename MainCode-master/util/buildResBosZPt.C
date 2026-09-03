#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage: buildResBosZPt path"<<endl;
   return 0;
 }

 ifstream origin;
  origin.open(argv[1], ios::in);

 string FileLine;

 ofstream file;
  file.open("ATLAS_rap_NoCorrPDFunc.dat");

 for(int i = 1; i <= 5; i++){
   getline(origin, FileLine);
 }

 double QMin, QMax, ymin, ymax, pT, pTmin, pTmax, data, uncorr, yk, eff;
 vector<double> corr(8);

 while(origin >> QMin){
   origin >> QMax >> ymin >> ymax >> pT >> pTmin >> pTmax >> data >> uncorr >> yk >> eff;
   origin >> corr.at(0) >> corr.at(1) >> corr.at(2) >> corr.at(3) >> corr.at(4) >> corr.at(5) >> corr.at(6) >> corr.at(7);

   file<<fixed<<setprecision(3)<<QMin<<"  ";
   file<<fixed<<setprecision(3)<<QMax<<"  ";
   file<<*right<<setw(5)<<*right<<fixed<<setprecision(3)<<ymin<<"  ";
   file<<*right<<setw(5)<<*right<<fixed<<setprecision(3)<<ymax<<"  ";
   file<<*right<<setw(7)<<*right<<fixed<<setprecision(3)<<pT<<"  ";
   file<<*right<<setw(7)<<*right<<fixed<<setprecision(4)<<pTmin<<"  ";
   file<<*right<<setw(7)<<*right<<fixed<<setprecision(4)<<pTmax<<"  ";
   file<<*right<<setw(8)<<uppercase<<scientific<<setprecision(3)<<data<<"  ";

   uncorr = sqrt(pow(uncorr, 2) + pow(corr.at(2) / 100.0 * data, 2) + pow(corr.at(3) / 100.0 * data, 2) + pow(corr.at(4) / 100.0 * data, 2) + pow(corr.at(5) / 100.0 * data, 2) + pow(corr.at(6) / 100.0 * data, 2) + pow(corr.at(7) / 100.0 * data, 2));

   file<<*right<<setw(8)<<uppercase<<scientific<<setprecision(3)<<uncorr<<"  ";

   file<<*right<<setw(5)<<fixed<<setprecision(3)<<yk<<"  ";
   file<<*right<<setw(8)<<fixed<<setprecision(8)<<eff<<"  ";
   file<<*right<<setw(5)<<*right<<fixed<<setprecision(3)<<corr.at(0)<<"  ";
   file<<*right<<setw(5)<<*right<<fixed<<setprecision(3)<<corr.at(1)<<endl;

 }


 return 1;
}

