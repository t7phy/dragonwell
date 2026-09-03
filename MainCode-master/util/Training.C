#include <iostream>
#include "RootCommon.h"
#include "TMVAInterface/TMVAInterface.h"

using namespace std;

int main(int argc, char** argv)
{
 TMVAInterface* Training = new TMVAInterface();

 Training->OutputFile("BDT_Output.root");
 Training->DefineFactory("BDTClassification", "!V:!Silent:Color:!DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");
 Training->AddTree("class_data.root", "signal", "Signal", 1.0);
 Training->AddTree("class_data.root", "background", "Background", 1.0);
 Training->AddVariable("X1");
 Training->AddVariable("X2");
 Training->PrepareTrainingAndTestTree("", "SplitMode=random:!V");
#ifdef USE_TMVA
 Training->BookMethod(TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");
#endif
 Training->Evaluate();

 //test->FirstRegression();
 //test->FirstRegressionApp();
 //test->FirstRegressionTest();
 //test->FirstClassification();
 //test->FirstClassificationApp();

 return 1;
}

