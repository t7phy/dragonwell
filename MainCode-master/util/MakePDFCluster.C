#include <iostream>
#include <fstream>
#include "CTEQHelper/ClusterPDF.h"

using namespace std;

int main(int argc, char** argv)
{
 vector<TString> PDFList;
 vector<TString> SummaryList;

 TString name;

 ifstream pdffile("pdf.list");
 while(pdffile >> name){
   PDFList.push_back(name);
 }

 ifstream sumfile("sum.list");
 while(sumfile >> name){
   SummaryList.push_back(name);
 }

 TString ReferencePDF = "Input/CT18A+nDev.00.pds";

 ClusterPDF* run = new ClusterPDF();
// run->PreparexFlavorVector();
// run->InputReferencePDF(ReferencePDF);
// run->InputSummaryList(SummaryList);
// run->InputPDFList(PDFList);
// run->OutputTSV("clusterPDF");

 run->PrepareGaussPoints(20, 0.35, 2, 4);
 run->InputReferencePDF(ReferencePDF);
 run->InputSummaryList(SummaryList);
 run->InputPDFList(PDFList);
 run->OutputTSV("clusterPDF_x0.3_nx40_pp830a");
 run->OutputRenyiEntropy("clusterPDF_x0.3_pp830a", 2);

 return 1;
}
