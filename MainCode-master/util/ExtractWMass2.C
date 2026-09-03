#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{

 if(argc != 3){
   cout<<"./ExtractWMass2 Data Variable"<<endl;
   return 0;
 }

 TString TemplatesName = "WMassTemplate.list";
 TString DataName = argv[1];
 TString VariableName = argv[2];
// TString DataName = "/ustcfs2/yfu/pku_resbos/TevatronGrids/CT18NNLO/rootfile/Pseudodata/MC_results.root";
// TString VariableName = "MtW_CDF";

 TemplateFittingNorm(TemplatesName, DataName, VariableName, 0.336, 0.435, 0.001);

 return 1;
}

