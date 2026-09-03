#ifndef Control_h
#define Control_h

#include <iostream>
#include <fstream>
#include <string>
#include "TString.h"
#include <vector>
#include "Tools/Log.h"

using namespace std;

class Control
{
 public:

 int TotalThread = 0;
 bool isReweight = false;
 bool isFSR = false;
 bool isTest = false;
 bool isRunAllSystematic = false;
 TString RunType = "";
 TString RootType = "";
 TString FileList = "";
 TString SaveName = "";
 TString CutFile = "";
 TString SystematicList = "";
 TString oldPDFName = "";
 int oldPDFset = 0;
 TString newPDFName = "";
 int newPDFset = -1;
 double ECM;
 int isDilution = 0;
 bool PreRunReweightingFactor = false;
 bool Fitting = false;
 TString FittingData = "";
 int ProcessOption = 1;
 int doTruthSelection = 0;
 TString NtupleName = "";
 int Year = 0;
 bool doBkg = false;
 bool doControlRegion = false;
 int doFakeRate = 0;
 TString SystematicName = "";
 TString UpDn = "";
 TString SumOfWeightList = "";
 bool doPDFAndQCDUnc = false;
 TString ErrorType = "";
 int ErrorSet = 0;
 TString BDTFileList = "0";
 TString LWTNNFileList = "0";
 TString DataListFile = "";
 bool isPPbar = false;
 double OriginWMass = 80.385;
 double NewWMass = 80.385;
 double WWidth = 2.0895;
 TString CalibrationOption = "";
 double ScaleSlope = 0.0;
 double LeptonPtMin = -99.0;
 double LeptonPtMiddle = -99.0;
 double LeptonPtMax = -99.0;
 TString topDDList = "";
 TString TreeName = "nominal";
 TString HMDYisNormalRun = "NormalRun";
 TString HMDYFakeEffFile = "";
 TString ZPrimeisNormalRun = "NormalRun";
 TString ZPrimeFakeEffFile = "";
 TString ZPrimeKFactorFile = "";
 TString ZPrimeAngularFile = "";
 int MadGraphReweightID = 0;

//not input parameter
 TString RootName;
 vector<TString> RootNames;
 int TotalFileNumber;

 int NFilePerJob;
 int TotalRound = 1;
 bool OneFilePerJob = false;

 TString FittingFile = "";
 TString FittingHist = "";

 bool isBDT = false;
 bool isBDTSR = false;
 bool isOnlyDecSR = false;
 bool isNoPtVSR = false;
 bool isBDTSR100 = false;
 bool isOnlyDecSR100 = false;
 bool isNoPtVSR100 = false;
 TString BDTFile = "";
 TString BDTFileSR = "";
 TString BDTFileSR100 = "";

 bool isLWTNNNuPz = false;
 bool isLWTNNPolClassifier = false;
 bool isLWTNNNLOPol = false;
 TString NuPzEven = "";
 TString NuPzOdd = "";
 TString PolClassifierEven = "";
 TString PolClassifierOdd = "";
 TString DNNLLFile = "";
 TString DNNLTFile = "";
 TString DNNTLFile = "";
 TString DNNTTFile = "";

 vector<TString> DataList;

 vector<TString> topDDFile;
 vector<TString> TransferName_ee;
 vector<TString> TransferName_mm;

 Control(){}
 virtual void ReadFile(const char* FileName);
 Control& operator=(const Control &myClass);

 virtual void GetRunningType(int recall = 0);

 Logstream myLog;
 virtual void LinkLog(Logstream log){this->myLog = log;}

 virtual void Help();
};
#endif
