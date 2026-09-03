#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "ePumpHelper/ePumpHelper.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"Usage ./CustomUpdateResBosHighMass filename"<<endl;
   return 0;
 }

 TFile* file = new TFile("save.root", "RECREATE");

 ePumpHelper* EU = new ePumpHelper(argv[1]);
 EU->Initial();
 EU->Update();
 EU->LinkFile(file);

 TH1D* OldPDFError;
 EU->ConstructOldPDFErrorHist("test/WHighMassMT", "", OldPDFError, "Relative");
 TH1D* OldPDFErrorWPlus;
 EU->ConstructOldPDFErrorHist("test/WPlusHighMassMT", "", OldPDFErrorWPlus, "Relative");
 TH1D* OldPDFErrorWMinus;
 EU->ConstructOldPDFErrorHist("test/WMinusHighMassMT", "", OldPDFErrorWMinus, "Relative");


 EU->ResetUpdate();
 EU->SetDataWeight("test/PositiveLeptonEta", 1.0);
 EU->SetDataWeight("test/NegativeLeptonEta", 1.0);
 EU->Update();
 TH1D* NewPDFError_WEta;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WEta", NewPDFError_WEta, "Relative");
 TH1D* NewPDFErrorWPlus_WEta;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WEta", NewPDFErrorWPlus_WEta, "Relative");
 TH1D* NewPDFErrorWMinus_WEta;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WEta", NewPDFErrorWMinus_WEta, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/PositiveLeptonPt", 1.0);
 EU->SetDataWeight("test/NegativeLeptonPt", 1.0);
 EU->Update();
 TH1D* NewPDFError_WLepPt;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WLepPt", NewPDFError_WLepPt, "Relative");
 TH1D* NewPDFErrorWPlus_WLepPt;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WLepPt", NewPDFErrorWPlus_WLepPt, "Relative");
 TH1D* NewPDFErrorWMinus_WLepPt;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WLepPt", NewPDFErrorWMinus_WLepPt, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/PositiveLeptonPtEta", 1.0);
 EU->SetDataWeight("test/NegativeLeptonPtEta", 1.0);
 EU->Update();
 TH1D* NewPDFError_WLepPtEta;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WLepPtEta", NewPDFError_WLepPtEta, "Relative");
 TH1D* NewPDFErrorWPlus_WLepPtEta;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WLepPtEta", NewPDFErrorWPlus_WLepPtEta, "Relative");
 TH1D* NewPDFErrorWMinus_WLepPtEta;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WLepPtEta", NewPDFErrorWMinus_WLepPtEta, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/WPlusMT", 1.0);
 EU->SetDataWeight("test/WMinusMT", 1.0);
 EU->Update();
 TH1D* NewPDFError_WMT;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WMT", NewPDFError_WMT, "Relative");
 TH1D* NewPDFErrorWPlus_WMT;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WMT", NewPDFErrorWPlus_WMT, "Relative");
 TH1D* NewPDFErrorWMinus_WMT;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WMT", NewPDFErrorWMinus_WMT, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/PositiveLeptonPtEta", 1.0);
 EU->SetDataWeight("test/NegativeLeptonPtEta", 1.0);
 EU->SetDataWeight("test/AFB_Mass_ZY_CC", 1.0);
 EU->SetDataWeight("test/AFB_Mass_ZY_CF", 1.0);
 EU->Update();
 TH1D* NewPDFError_WLepPtEta_AFB;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WLepPtEta_AFB", NewPDFError_WLepPtEta_AFB, "Relative");
 TH1D* NewPDFErrorWPlus_WLepPtEta_AFB;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WLepPtEta_AFB", NewPDFErrorWPlus_WLepPtEta_AFB, "Relative");
 TH1D* NewPDFErrorWMinus_WLepPtEta_AFB;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WLepPtEta_AFB", NewPDFErrorWMinus_WLepPtEta_AFB, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/PositiveLeptonPtEta", 1.0);
 EU->SetDataWeight("test/NegativeLeptonPtEta", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CC", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CF", 1.0);
 EU->Update();
 TH1D* NewPDFError_WLepPtEta_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WLepPtEta_ZXsec_2D", NewPDFError_WLepPtEta_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWPlus_WLepPtEta_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WLepPtEta_ZXsec_2D", NewPDFErrorWPlus_WLepPtEta_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWMinus_WLepPtEta_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WLepPtEta_ZXsec_2D", NewPDFErrorWMinus_WLepPtEta_ZXsec_2D, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/PositiveLeptonPtEta", 1.0);
 EU->SetDataWeight("test/NegativeLeptonPtEta", 1.0);
 EU->SetDataWeight("test/AFB_Mass_ZY_CC", 1.0);
 EU->SetDataWeight("test/AFB_Mass_ZY_CF", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CC", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CF", 1.0);
 EU->Update();
 TH1D* NewPDFError_WLepPtEta_AFB_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_WLepPtEta_AFB_ZXsec_2D", NewPDFError_WLepPtEta_AFB_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWPlus_WLepPtEta_AFB_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_WLepPtEta_AFB_ZXsec_2D", NewPDFErrorWPlus_WLepPtEta_AFB_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWMinus_WLepPtEta_AFB_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_WLepPtEta_AFB_ZXsec_2D", NewPDFErrorWMinus_WLepPtEta_AFB_ZXsec_2D, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/Xsec_2D_CC", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CF", 1.0);
 EU->Update();
 TH1D* NewPDFError_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_ZXsec_2D", NewPDFError_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWPlus_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_ZXsec_2D", NewPDFErrorWPlus_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWMinus_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_ZXsec_2D", NewPDFErrorWMinus_ZXsec_2D, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/AFB_Mass_ZY_CC", 1.0);
 EU->SetDataWeight("test/AFB_Mass_ZY_CF", 1.0);
 EU->Update();
 TH1D* NewPDFError_AFB;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_AFB", NewPDFError_AFB, "Relative");
 TH1D* NewPDFErrorWPlus_AFB;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_AFB", NewPDFErrorWPlus_AFB, "Relative");
 TH1D* NewPDFErrorWMinus_AFB;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_AFB", NewPDFErrorWMinus_AFB, "Relative");

 EU->ResetUpdate();
 EU->SetDataWeight("test/AFB_Mass_ZY_CC", 1.0);
 EU->SetDataWeight("test/AFB_Mass_ZY_CF", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CC", 1.0);
 EU->SetDataWeight("test/Xsec_2D_CF", 1.0);
 EU->Update();
 TH1D* NewPDFError_AFB_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WHighMassMT", "_updated_by_AFB_ZXsec_2D", NewPDFError_AFB_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWPlus_AFB_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WPlusHighMassMT", "_updated_by_AFB_ZXsec_2D", NewPDFErrorWPlus_AFB_ZXsec_2D, "Relative");
 TH1D* NewPDFErrorWMinus_AFB_ZXsec_2D;
 EU->ConstructNewPDFErrorHist("test/WMinusHighMassMT", "_updated_by_AFB_ZXsec_2D", NewPDFErrorWMinus_AFB_ZXsec_2D, "Relative");


 file->Write();
 file->Close();

 return 1;

}
