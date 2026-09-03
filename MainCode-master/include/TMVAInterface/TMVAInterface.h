#ifndef TMVAInterface_TMVAInterface_h
#define TMVAInterface_TMVAInterface_h

#include "RootCommon.h"
#include "TCut.h"

#ifdef USE_TMVA
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "TMVA/Config.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Types.h"
#endif

using namespace std;

class TMVAInterface
{
 public:

 bool isOpenOutput = false;
 bool isOpenFactory = false;

 TFile *output;
#ifdef USE_TMVA
 TMVA::Factory *factory;
 TMVA::DataLoader *dataloader;
#endif

 map<TString, TFile *> FileMap;
 map<pair<TString, TString>, TTree *> TreeMap;

 TMVAInterface();
 virtual void OutputFile(const char* name);
 virtual void DefineFactory(TString Name, TString Args);
 virtual void AddTree(TString FileName, TString TreeName, TString ComponentName, double weight = 1.0);
 virtual void AddVariable(TString Name);
 virtual void PrepareTrainingAndTestTree(TCut cut, TString Args);
#ifdef USE_TMVA
 virtual void BookMethod(TMVA::Types::EMVA method, TString title, TString Args);
#endif
 virtual void Evaluate();

 ////////////////
 //  Tutorial  //
 ////////////////

 virtual void FirstRegression();
 virtual void FirstRegressionApp();
 virtual void FirstRegressionTest();
 virtual void FirstClassification();
 virtual void FirstClassificationApp();
 virtual void FirstClassificationTest();

 virtual void TrainingANN();
 virtual void TestANN();
};

#endif
