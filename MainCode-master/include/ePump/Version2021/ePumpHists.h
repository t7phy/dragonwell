#ifndef ePumpHists_h
#define ePumpHists_h

#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"
#include "TString.h"
#include <vector>

class ePumpHists
{
 public:

 TFile* hf;

 TH1D* Observable_old[1000];
 TH1D* Observable_new[1000];
 TH1D* PDFError_old[1000];
 TH1D* PDFError_new[1000];

 TH2D* Correlation_old[1000][1000];
 TH2D* Correlation_new[1000][1000];

 virtual void openFile(const char* fName);
 virtual void bookHists(const char*, int ihist, int ibin);
 virtual void bookHists(int ihist1, int ihist2, int ibin1, int ibin2);
 virtual void saveHists();

};
#endif
