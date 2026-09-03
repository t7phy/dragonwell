#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "CTEQHelper/pdsReader.h"
#include "CTEQHelper/HoppetInterface.h"

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./p2lFullSet pdflist LHAPDFName"<<endl;
   return 0;
 }

 TString name;
 vector<TString> PDFList;

 ifstream infile(argv[1]);
 while(infile >> name){
   PDFList.push_back(name);
 }

 HoppetInterface* run = new HoppetInterface();
 for(int i = 0; i < PDFList.size(); i++){
   pdsReader* pdf = new pdsReader();
   pdf->Initialize(PDFList.at(i));
   run->InputCTEQPDF(pdf);
   run->OutputLHAPDFTable(argv[2], i);
   delete pdf;
 }

 return 1;
}
