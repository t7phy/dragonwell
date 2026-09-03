#ifndef QBH_QBHFakeRate_h
#define QBH_QBHFakeRate_h

#include "RootCommon.h"
#include "Tools/Log.h"
#include "Analysis/treeDrawThread.h"

class QBHFakeRate
{
 public:

   TH2D* ElFakeEff;
   TH2D* MuFakeEff;
   TH2D* ElRealEff;
   TH2D* MuRealEff;
   TH2D* ElFakeTight;
   TH2D* ElFakeLoose;
   TH2D* MuFakeTight;
   TH2D* MuFakeLoose;
   TH2D* ElRealTight;
   TH2D* ElRealLoose;
   TH2D* MuRealTight;
   TH2D* MuRealLoose;

   TreeDrawThread* ElFakeTightJob;
   TreeDrawThread* ElFakeLooseJob;
   TreeDrawThread* MuFakeTightJob;
   TreeDrawThread* MuFakeLooseJob;
   TreeDrawThread* ElRealTightJob;
   TreeDrawThread* ElRealLooseJob;
   TreeDrawThread* MuRealTightJob;
   TreeDrawThread* MuRealLooseJob;

   vector<TString> RootNames;

   QBHFakeRate(){};
   virtual void GetFakeFactor(vector<TString> RootNames);

   Logstream myLog;
   virtual void LinkLog(Logstream log){this->myLog = log;}

   QBHFakeRate* Clone(int i){
     QBHFakeRate* ptr = new QBHFakeRate();
     ptr->ElFakeEff = (TH2D *)this->ElFakeEff->Clone((TString)"ElFakeEff_" + i);
     ptr->MuFakeEff = (TH2D *)this->MuFakeEff->Clone((TString)"MuFakeEff_" + i);
     ptr->ElRealEff = (TH2D *)this->ElRealEff->Clone((TString)"ElRealEff_" + i);
     ptr->MuRealEff = (TH2D *)this->MuRealEff->Clone((TString)"MuRealEff_" + i);
     ptr->ElFakeTight = (TH2D *)this->ElFakeTight->Clone((TString)"ElFakeTight_" + i);
     ptr->ElFakeLoose = (TH2D *)this->ElFakeLoose->Clone((TString)"ElFakeLoose_" + i);
     ptr->MuFakeTight = (TH2D *)this->MuFakeTight->Clone((TString)"MuFakeTight_" + i);
     ptr->MuFakeLoose = (TH2D *)this->MuFakeLoose->Clone((TString)"MuFakeLoose_" + i);
     ptr->ElRealTight = (TH2D *)this->ElRealTight->Clone((TString)"ElRealTight_" + i);
     ptr->ElRealLoose = (TH2D *)this->ElRealLoose->Clone((TString)"ElRealLoose_" + i);
     ptr->MuRealTight = (TH2D *)this->MuRealTight->Clone((TString)"MuRealTight_" + i);
     ptr->MuRealLoose = (TH2D *)this->MuRealLoose->Clone((TString)"MuRealLoose_" + i);

     return ptr;
   }
};

#endif
