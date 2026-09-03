#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{

// TString TemplatesName = "G2Template.list";
// TString DataName = "/ustcfs2/yfu/pku_resbos/TevatronGrids/CT18NNLO_Z/rootfile/Pseudodata/MC_results.root";
// TString VariableName = "ZPt_CDF";

// TemplateFittingNorm(TemplatesName, DataName, VariableName, 0.30, 1.08, 0.02);

 TString TemplatesName = "WMassTemplate.list";
 TString DataName = "/ustcfs2/yfu/pku_resbos/TevatronGrids/CT18NNLO/rootfile/Pseudodata/MC_results.root";
 TString VariableName = "NuPt_CDF";

 TemplateFittingNorm(TemplatesName, DataName, VariableName, 0.336, 0.435, 0.001);

 return 1;
}
