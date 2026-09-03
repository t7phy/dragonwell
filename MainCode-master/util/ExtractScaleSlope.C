#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{

 if(argc != 2){
   cout<<"./ExtractScaleSlope Data"<<endl;
   return 0;
 }

 TString TemplatesName = "ScaleSlope.list";
 TString DataName = argv[1];

 TemplateFittingNorm(TemplatesName, DataName, "WPt_CDF_ScaleVari_Pseudodata_NoFluc", "WPt_CDF_Pseudodata_NoFluc", -0.98, 1.0, 0.02);

 return 1;
}


