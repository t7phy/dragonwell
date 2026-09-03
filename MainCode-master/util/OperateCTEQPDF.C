#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "CTEQHelper/pdsReader.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 5){
   cout<<"usage: OperateCTEQPDF [operator] output.pds input1.pds input2.pds"<<endl;
   return 0;
 }

 pdsReader* pdf1 = new pdsReader();
 pdf1->Initialize(argv[3]);

 pdsReader* pdf2 = new pdsReader();
 pdf2->Initialize(argv[4]);

 pdsReader* outputPDF;

 if((TString)argv[1] == "average"){
   outputPDF = pdf1->Average(vector<pdsReader *>{pdf2});
 }

 outputPDF->OutputPDF(argv[2]);

 return 1;
}
