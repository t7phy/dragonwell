#include "OptimizeHelper/DrawFraction.h"
#include "OptimizeHelper/FractionHist.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage ./DrawFraction filename rootname"<<endl;
   return 0;
 }

 double xbins1[27] = {60,62,64,66,68,70,72,74,76,78,80,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130};

 FractionHist* myhists = new FractionHist();

// myhists->openFile("Fraction_AFBSideband+Wasym15.root");
// myhists->DefineHist("AFB", "AFB", 26, xbins1);
// myhists->DefineHist("Wasymmetry", "Wasymmetry", 15, 1, 2.5);

// myhists->openFile("Fraction_AFBDiff_WWBoost.root");
// myhists->DefineHist("AFBDiff", "AFBDiff", 15, 0, 30);
// myhists->DefineHist("WWBoostAsymmetry", "WWBoostAsymmetry", 1, 0, 5);

// myhists->openFile("Fraction_HadronAFB_QuarkAFB.root");
// myhists->DefineHist("HadronAFB", "HadronAFB", 35, 60, 130);
// myhists->DefineHist("QuarkAFB", "QuarkAFB", 35, 60, 130);

// myhists->openFile("Fraction_QuarkAFB.root");
// myhists->DefineHist("QuarkAFB", "QuarkAFB", 35, 60, 130);

// myhists->openFile("Fraction_NormalizedMtW.root");
// myhists->DefineHist("MtW_CDF", "MtW_CDF", 50, 65, 90);

 int HighMassBin = 25;
 double HighMassBinning[26];
 HighMassBinning[0] = 1000.0;
 for(int i = 1; i <= 25; i++){HighMassBinning[i] = pow(10.0, 3.0 + log10(5.0) * i / 25.0);}

 myhists->openFile(argv[2]);
// myhists->DefineHist("AFB", "AFB", 30, 60, 120);
// myhists->DefineHist("WLeptonEtaAsymmetry", "WLeptonEtaAsymmetry", 20, 0, 2.4);
// myhists->DefineHist("ZHighMass", "ZHighMass", HighMassBin, HighMassBinning);
// myhists->DefineHist("WHighMassMT", "WHighMassMT", HighMassBin, HighMassBinning);
// myhists->DefineHist("JacobianAsymmetry", "JacobianAsymmetry", 21, 80.3265, 80.4315);
 myhists->DefineHist("LeptonPt", "LeptonPt", 22, 33, 44);

 DrawFraction run(argv[1]);
 run.LinkHist(myhists);
// run.SkipBin(1, 11);
 run.FillHist();

 myhists->saveHist();

 return 1;
}
