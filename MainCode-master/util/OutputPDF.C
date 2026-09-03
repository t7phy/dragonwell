#include "RootCommon.h"
#include "CTEQHelper/pdsReader.h"
#include "PDFHelper/PDFFigure.h"
#include "PDFHelper/PDFHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 5){
   cout<<"usage: OutputPDF FileName flavor x Q"<<endl;
   return 0;
 }

 int flavor = stoi(argv[2]);
 double x = stod(argv[3]);
 double Q = stod(argv[4]);

 pdsReader pdf;
 pdf.Initialize(argv[1]);
 cout<<"flavor = "<<flavor<<" x = "<<x<<" Q = "<<Q<<" PDF = "<<pdf.xfxQ(flavor, x, Q) / x<<endl;

 return 1;
}

