#ifndef loopMC_h
#define loopMC_h

#include "RootCommon.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <pthread.h>
#include <mutex>

#include "Analysis/makeHists.h"

#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "PDFHelper/PDFReweight.h"
#include "ElectroweakTheory/ResBosEW.h"

#include "Tools/LatexOutput.h"

using namespace std;

class loopMC
{
 public:
 long Sta_TotalNumber;

 vector<TString> RootNames;
 TString RootType;

 vector<int> RootTypes;
 vector<double> CrossSections;
 vector<double> SumOfWeights;

 double TotalWeight;

 int TotalThread;
 int iThread;
 bool isThread;

 long NEvents;
 long TotalEntries[1000];

 long InitialEntry;
 long Nentries;

 int FirstFile, EndFile;
 bool OneFilePerJob = false;

 bool isTest = false;

 vector<TString> CutInfo;
 vector<double> CutLeft;
 vector<double> CutRight;

 double PDFReweightFactor = 1.0;
 bool isPDFReweight = false;
 TString oldPDFName = "";
 TString newPDFName = "";
 int oldPDFset = 0;
 int newPDFset = -1;
 PDFReweight *myPDFReweight;

 loopMC();
 virtual void InputThreadInfo(int TotalThread, int iThread);
 virtual void Initial(int ifile);
 virtual void OutputFileInfo();
 virtual void ConfigCut(const char* CutFile);
 virtual void Test() {isTest = true;}
 virtual void InputPDFReweightInfo(const char* oldPDFName, const char* newPDFName, int oldPDFset, int newPDFset);
 virtual void InitialPDFInfo(const char* oldPDFName, int oldPDFset);
 virtual void End();
 virtual ~loopMC();

 Logstream myLog;
 virtual void LinkLog(Logstream log){this->myLog = log;}

};
#endif
