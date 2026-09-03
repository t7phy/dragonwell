#include <iostream>
#include <vector>
#include "RootCommon.h"
#include "Uncertainty/PDFUncertainty.h"
#include "CompareDataTheory/CompareDataTheory.h"
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 TString DataName = "/Data/yfu/MainCode/run/AFBQuarkExtraction/If1363.00/MC_results.root";

 TFile* writefile = new TFile("HadronAFB_Results.root", "RECREATE");
 writefile->cd();

 TFile* file = new TFile(DataName);

 //DataS0 = (TH1D *)DataSlope->Clone((TString)"S0_PDF" + (int)i);
 double DataS0 =  0.226357;
 double MCS0 = 0.215951;

 TH3D* FZmass3D = (TH3D *)file->Get("FZMass_ZY_QT_qq");
 TH3D* BZmass3D = (TH3D *)file->Get("BZMass_ZY_QT_qq");
 TH3D* Dilution3D = (TH3D *)file->Get("Dilution_ZMass_ZY_QT");
 Apply3DDilution(FZmass3D, BZmass3D, Dilution3D);
 TH1D* AFBApply3DDilution = new TH1D("AFBApply3DDilution", "AFBApply3DDilution", 35, 60, 130);
 AFBFunction(FZmass3D, BZmass3D, AFBApply3DDilution);


 TH2D* FZmass2D = (TH2D *)file->Get("FZmass_ZY_qq");
 TH2D* BZmass2D = (TH2D *)file->Get("BZmass_ZY_qq");
 TH2D* Dilution2D = (TH2D *)file->Get("Dilution_ZMass_ZY");
 Apply2DDilution(FZmass2D, BZmass2D, Dilution2D);
 TH1D* AFBApply2DDilution = new TH1D("AFBApply2DDilution", "AFBApply2DDilution", 35, 60, 130);
 AFBFunction(FZmass2D, BZmass2D, AFBApply2DDilution);


 TH2D* FZmass2D_CF = (TH2D *)file->Get("FZmass_ZY_CF_qq");
 TH2D* BZmass2D_CF = (TH2D *)file->Get("BZmass_ZY_CF_qq");
 TH2D* Dilution2D_CF = (TH2D *)file->Get("Dilution_ZMass_ZY_CF");
 Apply2DDilution(FZmass2D_CF, BZmass2D_CF, Dilution2D_CF);
 TH1D* AFBApply2DDilution_CF = new TH1D("AFBApply2DDilution_CF", "AFBApply2DDilution_CF", 35, 60, 130);
 AFBFunction(FZmass2D_CF, BZmass2D_CF, AFBApply2DDilution_CF);


 TH1D* FZmass_uu = (TH1D *)file->Get("FZmass_uu");
 TH1D* FZmass_dd = (TH1D *)file->Get("FZmass_dd");
 TH1D* FZmass_gg = (TH1D *)file->Get("FZmass_gg");
 TH1D* BZmass_uu = (TH1D *)file->Get("BZmass_uu");
 TH1D* BZmass_dd = (TH1D *)file->Get("BZmass_dd");
 TH1D* BZmass_gg = (TH1D *)file->Get("BZmass_gg");
 TH1D* Dilution_uu = (TH1D *)file->Get("Dilution_ZMass_uu");
 TH1D* Dilution_dd = (TH1D *)file->Get("Dilution_ZMass_dd");
 ApplyDilution(FZmass_uu, BZmass_uu, Dilution_uu);
 ApplyDilution(FZmass_dd, BZmass_dd, Dilution_dd);
 ApplyDilution(FZmass_gg, BZmass_gg, Dilution_uu, true);
 TH1D* FZmass = (TH1D *)FZmass_uu->Clone("FZmass");
 FZmass->Add(FZmass_dd);
 FZmass->Add(FZmass_gg);
 TH1D* BZmass = (TH1D *)BZmass_uu->Clone("BZmass");
 BZmass->Add(BZmass_dd);
 BZmass->Add(BZmass_gg);
 TH1D* AFBApplyDilutionFlavor = new TH1D("AFBApplyDilutionFlavor", "AFBApplyDilutionFlavor", 35, 60, 130);
 AFBFunction(FZmass, BZmass, AFBApplyDilutionFlavor);

 TH1D* FZmass_CC_uu = (TH1D *)file->Get("FZmass_CC_uu");
 TH1D* FZmass_CC_dd = (TH1D *)file->Get("FZmass_CC_dd");
 TH1D* FZmass_CC_gg = (TH1D *)file->Get("FZmass_CC_gg");
 TH1D* BZmass_CC_uu = (TH1D *)file->Get("BZmass_CC_uu");
 TH1D* BZmass_CC_dd = (TH1D *)file->Get("BZmass_CC_dd");
 TH1D* BZmass_CC_gg = (TH1D *)file->Get("BZmass_CC_gg");
 TH1D* Dilution_CC_uu = (TH1D *)file->Get("Dilution_ZMass_CC_uu");
 TH1D* Dilution_CC_dd = (TH1D *)file->Get("Dilution_ZMass_CC_dd");
 ApplyDilution(FZmass_CC_uu, BZmass_CC_uu, Dilution_CC_uu);
 ApplyDilution(FZmass_CC_dd, BZmass_CC_dd, Dilution_CC_dd);
 ApplyDilution(FZmass_CC_gg, BZmass_CC_gg, Dilution_CC_uu, true);
 TH1D* FZmass_CC = (TH1D *)FZmass_CC_uu->Clone("FZmass_CC");
 FZmass_CC->Add(FZmass_CC_dd);
 FZmass_CC->Add(FZmass_CC_gg);
 TH1D* BZmass_CC = (TH1D *)BZmass_CC_uu->Clone("BZmass_CC");
 BZmass_CC->Add(BZmass_CC_dd);
 BZmass_CC->Add(BZmass_CC_gg);
 TH1D* AFBApplyDilutionFlavor_CC = new TH1D("AFBApplyDilutionFlavor_CC", "AFBApplyDilutionFlavor_CC", 35, 60, 130);
 AFBFunction(FZmass_CC, BZmass_CC, AFBApplyDilutionFlavor_CC);

 TH1D* FZmass_CF_uu = (TH1D *)file->Get("FZmass_CF_uu");
 TH1D* FZmass_CF_dd = (TH1D *)file->Get("FZmass_CF_dd");
 TH1D* FZmass_CF_gg = (TH1D *)file->Get("FZmass_CF_gg");
 TH1D* BZmass_CF_uu = (TH1D *)file->Get("BZmass_CF_uu");
 TH1D* BZmass_CF_dd = (TH1D *)file->Get("BZmass_CF_dd");
 TH1D* BZmass_CF_gg = (TH1D *)file->Get("BZmass_CF_gg");
 TH1D* Dilution_CF_uu = (TH1D *)file->Get("Dilution_ZMass_CF_uu");
 TH1D* Dilution_CF_dd = (TH1D *)file->Get("Dilution_ZMass_CF_dd");
 ApplyDilution(FZmass_CF_uu, BZmass_CF_uu, Dilution_CF_uu);
 ApplyDilution(FZmass_CF_dd, BZmass_CF_dd, Dilution_CF_dd);
 ApplyDilution(FZmass_CF_gg, BZmass_CF_gg, Dilution_CF_uu, true);
 TH1D* FZmass_CF = (TH1D *)FZmass_CF_uu->Clone("FZmass_CF");
 FZmass_CF->Add(FZmass_CF_dd);
 FZmass_CF->Add(FZmass_CF_gg);
 TH1D* BZmass_CF = (TH1D *)BZmass_CF_uu->Clone("BZmass_CF");
 BZmass_CF->Add(BZmass_CF_dd);
 BZmass_CF->Add(BZmass_CF_gg);
 TH1D* AFBApplyDilutionFlavor_CF = new TH1D("AFBApplyDilutionFlavor_CF", "AFBApplyDilutionFlavor_CF", 35, 60, 130);
 AFBFunction(FZmass_CF, BZmass_CF, AFBApplyDilutionFlavor_CF);




 TH1D* AFBHadron = (TH1D *)file->Get("AFB_Full");
 TH1D* AFBHadron_CC = (TH1D *)file->Get("AFB_CC");
 TH1D* AFBHadron_CF = (TH1D *)file->Get("AFB_CF");

 writefile->cd();
 AFBApply3DDilution->Write();
 AFBApply2DDilution->Write();
 AFBApply2DDilution_CF->Write();
 AFBApplyDilutionFlavor->Write();
 AFBApplyDilutionFlavor_CC->Write();
 AFBApplyDilutionFlavor_CF->Write();
 AFBHadron->Write();
 AFBHadron_CC->Write();
 AFBHadron_CF->Write();

 writefile->Close();
 return 1;
}
