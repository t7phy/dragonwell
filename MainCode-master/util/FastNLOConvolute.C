#include <iostream>
#include <fstream>
#include "Calculation/FastNLOHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"usage ./FastNLOConvolute filename"<<endl;
   return 0;
 }

 FastNLOHelper* run = new FastNLOHelper(argv[1]);
 run->InitialPDF("CT18NNLO", 0);

 vector<double> xsec = run->GetCrossSection();

 for(int i = 0; i < xsec.size(); i++){
   cout<<xsec.at(i)<<endl;
 }

 return 1;
}
