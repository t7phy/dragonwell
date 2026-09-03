#include <iostream>
#include "RootCommon.h"
#include "PDFHelper/PDFHelper.h"

int main(int argc, char** argv)
{
 TFile* file = new TFile("PDFLumi.root", "RECREATE");

 PDFHelper* run = new PDFHelper();
 run->InitialPDF("CT18NNLO", 0);
 run->InitialPartonName();
 run->LinkFile(file);
 run->CalcPDFLumiUnc(100, 1000, 5000, 2, -2, "Symmetry", "CT18NNLO", 58);
 run->CalcPDFLumiUnc(100, 1000, 5000, 1, -1, "Symmetry", "CT18NNLO", 58);
 run->CalcPDFLumiUnc(100, 1000, 5000, 3, -3, "Symmetry", "CT18NNLO", 58);
 run->CalcPDFLumiUnc(100, 1000, 5000, 4, -4, "Symmetry", "CT18NNLO", 58);
 run->CalcPDFLumiUnc(100, 1000, 5000, 5, -5, "Symmetry", "CT18NNLO", 58);

 file->Write();
 file->Close();

 return 1;
}
