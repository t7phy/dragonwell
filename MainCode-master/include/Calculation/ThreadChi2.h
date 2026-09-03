#ifndef Calculation_ThreadChi2_h
#define Calculation_ThreadChi2_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Calculation/Dataset.h"
#include "Calculation/Config.h"

using namespace std;

extern pthread_mutex_t ApplMutex;

void* ThreadChi2(void* arg);
void* ThreadCalcChi2(void* arg);

void Convolute(vector<ApplGridHelper *> Theory);

void GlobalFitting_TMinuit(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);
void FittingPDF();

#endif
