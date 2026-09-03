#ifndef QBH_HistsQBH_h
#define QBH_HistsQBH_h
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
#include <vector>
#include "Analysis/makeHists.h"
#include "QBH/TreeForQBH.h"
#include "QBH/loopQBH.h"

using namespace std;

class QBHHistGroup;
class HistsQBH;
class EventQBH;
class TreeForQBH;
class loopQBH;

class QBHHistGroup
{
 friend class HistsQBH;

 public:

 HistsQBH *fHist;
 int TotalThread;

 TString HistName = "";
 TString SystematicName = "";

 QBHHistGroup();
 virtual void Initial(int iThread, int MCType);
 virtual void Fill(int iThread, double par, double weight, EventQBH ProcessEvent);
 virtual void ResetHist();
 virtual void GetFinalData();

};

class HistsQBH : public makeHists
{
 friend class QBHHistGroup;

 TreeForQBH *fTree;

 public:

 HistsQBH();
 virtual void bookHists(int TotalThread);
 //virtual void bookProcessHists(TString ProcessName, TString subName);
 virtual void outputInformation();
 virtual void bookAllProcessHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void bookAllProcessHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(QBHHistGroup* &hist, TString name, TString title, int nbin, double* xbins);
 virtual void LinkClass(HistsQBH *hist);

 TString SystematicName = "";
 void InputSystematicName(TString SystematicName){this->SystematicName = SystematicName;};

 vector<QBHHistGroup *> hist_process;
 vector<TString> HistNames;

};
#endif
