#include "Tools/Tools.h"
#include "PDFHelper/PDFFigure.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "RootCommon.h"

int main(int argc, char** argv)
{
 vector<double> QValues;
 for(int i = 0; i < 680; i++){
   QValues.push_back(1.3 + i * 0.01);
 }

 PDFFigure* run = new PDFFigure();
 run->SetLegendPosition(0.2, 0.7, 0.8, 0.95);

 run->openFile("save.root");
 run->InitialPDFAll("NNPDF40_nnlo_as_01180_hessian", 100);
// run->InitialPDFAll("CT18ANNLO", 58);
 run->GenerateEigenAll("NNPDF40_nnlo_as_01180_hessian", "NNPDF40_nnlo_as_01180_hessian", "Symmetry", 100.0, 3);
 run->SaveFile();

 return 1;
}

