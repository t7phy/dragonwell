//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 12 14:40:34 2020 by ROOT version 6.14/04
// from TTree Tree/Tree
// found on file: Zee_20M_FSRon_NNPDF31nnloas0118.root
//////////////////////////////////////////////////////////

#ifndef TreeForPythiaWW_h
#define TreeForPythiaWW_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

using namespace std;

class TreeForPythiaWW
{
 public :

   TFile *rootfile[1000];
   TTree *fChain[1000];
   long TotalEntries[1000];

   vector<TString> RootNames;

   vector<int> RootTypes;
   vector<double> CrossSections;
   vector<double> SumOfWeights;
   int nchannel;
   double CrossSection;
   double SumOfWeight;

   int FirstFile, EndFile;
   bool OneFilePerJob = false;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        GammaPx[10];
   Double_t        GammaPy[10];
   Double_t        GammaPz[10];
   Double_t        GammaE[10];
   Int_t           GammaMother[10];
   Int_t           GammaNumber;
   Double_t        ElectronPx;
   Double_t        ElectronPy;
   Double_t        ElectronPz;
   Double_t        ElectronE;
   Int_t           ElectronFlavor;
   Double_t        eNeutrinoPx;
   Double_t        eNeutrinoPy;
   Double_t        eNeutrinoPz;
   Double_t        eNeutrinoE;
   Double_t        MuonPx;
   Double_t        MuonPy;
   Double_t        MuonPz;
   Double_t        MuonE;
   Int_t           MuonFlavor;
   Double_t        mNeutrinoPx;
   Double_t        mNeutrinoPy;
   Double_t        mNeutrinoPz;
   Double_t        mNeutrinoE;
   Int_t           quark_flavour[2];
   Double_t        QuarkPx[2];
   Double_t        QuarkPy[2];
   Double_t        QuarkPz[2];
   Double_t        QuarkE[2];

/*   Double_t        AntiLeptonPx;
   Double_t        AntiLeptonPy;
   Double_t        AntiLeptonPz;
   Double_t        AntiLeptonE;
   Int_t           AntiLeptonID;
   Double_t        LeptonPx;
   Double_t        LeptonPy;
   Double_t        LeptonPz;
   Double_t        LeptonE;
   Int_t           LeptonID;
   Double_t        QuarkPx;
   Double_t        QuarkPy;
   Double_t        QuarkPz;
   Double_t        QuarkE;
   Int_t           QuarkID;
   Double_t        AntiQuarkPx;
   Double_t        AntiQuarkPy;
   Double_t        AntiQuarkPz;
   Double_t        AntiQuarkE;
   Int_t           AntiQuarkID;
*/
   // List of branches
   TBranch        *b_GammaPx;   //!
   TBranch        *b_GammaPy;   //!
   TBranch        *b_GammaPz;   //!
   TBranch        *b_Gamma;   //!
   TBranch        *b_GammaMother;   //!
   TBranch        *b_GammaNumber;   //!
   TBranch        *b_ElectronPx;   //!
   TBranch        *b_ElectronPy;   //!
   TBranch        *b_ElectronPz;   //!
   TBranch        *b_ElectronE;   //!
   TBranch        *b_ElectronFlavor;   //!
   TBranch        *b_eNeutrinoPx;   //!
   TBranch        *b_eNeutrinoPy;   //!
   TBranch        *b_eNeutrinoPz;   //!
   TBranch        *b_eNeutrinoE;   //!
   TBranch        *b_MuonPx;   //!
   TBranch        *b_MuonPy;   //!
   TBranch        *b_MuonPz;   //!
   TBranch        *b_MuonE;   //!
   TBranch        *b_MuonFlavor;   //!
   TBranch        *b_mNeutrinoPx;   //!
   TBranch        *b_mNeutrinoPy;   //!
   TBranch        *b_mNeutrinoPz;   //!
   TBranch        *b_mNeutrinoE;   //!
   TBranch        *b_quark_flavour;   //!
   TBranch        *b_QuarkPx;   //!
   TBranch        *b_QuarkPy;   //!
   TBranch        *b_QuarkPz;   //!
   TBranch        *b_QuarkE;   //!

/*   TBranch        *b_AntiLeptonPx;   //!
   TBranch        *b_AntiLeptonPy;   //!
   TBranch        *b_AntiLeptonPz;   //!
   TBranch        *b_AntiLeptonE;   //!
   TBranch        *b_AntiLeptonID;   //!
   TBranch        *b_LeptonPx;   //!
   TBranch        *b_LeptonPy;   //!
   TBranch        *b_LeptonPz;   //!
   TBranch        *b_LeptonE;   //!
   TBranch        *b_LeptonID;   //!
   TBranch        *b_QuarkPx;   //!
   TBranch        *b_QuarkPy;   //!
   TBranch        *b_QuarkPz;   //!
   TBranch        *b_QuarkE;   //!
   TBranch        *b_QuarkID;   //!
   TBranch        *b_AntiQuarkPx;   //!
   TBranch        *b_AntiQuarkPy;   //!
   TBranch        *b_AntiQuarkPz;   //!
   TBranch        *b_AntiQuarkE;   //!
   TBranch        *b_AntiQuarkID;   //!
*/
   TreeForPythiaWW();
   virtual ~TreeForPythiaWW();
   virtual void ConfigFile(int NFilePerJob, int iRound);
   virtual void ConfigFile(int ifile);
   virtual void InputFile(vector<TString> RootNames);
   virtual void SetBranch(int ifile);
   virtual void GetEntry(int ifile, long i);
   virtual void Init();
};

#endif

#ifdef TreeForPythiaWW_cxx

void TreeForPythiaWW::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
}

#endif
