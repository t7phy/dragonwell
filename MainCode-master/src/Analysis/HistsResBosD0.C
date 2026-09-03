#include "Analysis/HistsResBosD0.h"

using namespace std;

void HistsResBosD0::bookHists(int TotalThread)
{
 int D0_mass_bin = 13;
 double RangeD0Mass[14] = {50.0, 60.0, 70.0, 75.0, 81.0, 86.5, 89.5, 92.0, 97.0, 105.0, 115.0, 130.0, 180.0, 250.0};

 int D0_ZPt_bin = 1;
 double RangeD0ZPt[2] = {0.0, 10000.0};

 int D0_ZY_bin = 1;
 double RangeD0ZY[2] = {0.0, 5.0};

 this->TotalThread = TotalThread;

 Book3DHist(FZMass_ZY_QT, "FZMass_ZY_QT", "FZMass_ZY_QT", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(BZMass_ZY_QT, "BZMass_ZY_QT", "BZMass_ZY_QT", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);

 Book3DHist(ZMass_ZY_QT, "ZMass_ZY_QT", "ZMass_ZY_QT", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(FZMass_ZY_QT_uu, "FZMass_ZY_QT_uu", "FZMass_ZY_QT_uu", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(BZMass_ZY_QT_uu, "BZMass_ZY_QT_uu", "BZMass_ZY_QT_uu", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(FZMass_ZY_QT_dd, "FZMass_ZY_QT_dd", "FZMass_ZY_QT_dd", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(BZMass_ZY_QT_dd, "BZMass_ZY_QT_dd", "BZMass_ZY_QT_dd", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);

 Book3DHist(ZMass_ZY_QT_uu, "ZMass_ZY_QT_uu", "ZMass_ZY_QT_uu", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_dd, "ZMass_ZY_QT_dd", "ZMass_ZY_QT_dd", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_ss, "ZMass_ZY_QT_ss", "ZMass_ZY_QT_ss", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_cc, "ZMass_ZY_QT_cc", "ZMass_ZY_QT_cc", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_bb, "ZMass_ZY_QT_bb", "ZMass_ZY_QT_bb", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);

 Book3DHist(ZMass_ZY_QT_uu_total, "ZMass_ZY_QT_uu_total", "ZMass_ZY_QT_uu_total", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_uu_wrong, "ZMass_ZY_QT_uu_wrong", "ZMass_ZY_QT_uu_wrong", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_dd_total, "ZMass_ZY_QT_dd_total", "ZMass_ZY_QT_dd_total", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);
 Book3DHist(ZMass_ZY_QT_dd_wrong, "ZMass_ZY_QT_dd_wrong", "ZMass_ZY_QT_dd_wrong", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);

 Book3DHist(ZMass_ZY_QT_uu_right, "ZMass_ZY_QT_uu_right", "ZMass_ZY_QT_uu_right", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);

 Book3DHist(ZMass_ZY_QT_dd_right, "ZMass_ZY_QT_dd_right", "ZMass_ZY_QT_dd_right", D0_mass_bin, RangeD0Mass, D0_ZY_bin, RangeD0ZY, D0_ZPt_bin, RangeD0ZPt);

}

void HistsResBosD0::outputInformation()
{
 AFB_Mass_ZY_ZPt = (TH3D *)FZMass_ZY_QT->at(0)->Clone("AFB_ZMass_ZY_QT");
 AFB_Mass_ZY_ZPt->Reset();

 AFB_Mass_ZY_ZPt_uu = (TH3D *)FZMass_ZY_QT_uu->at(0)->Clone("AFB_ZMass_ZY_QT_uu");
 AFB_Mass_ZY_ZPt_uu->Reset();
 AFB_Mass_ZY_ZPt_dd = (TH3D *)FZMass_ZY_QT_dd->at(0)->Clone("AFB_ZMass_ZY_QT_dd");
 AFB_Mass_ZY_ZPt_dd->Reset();

 //AFB vs Mass ZY ZPt
 AFBFunction(FZMass_ZY_QT->at(0), BZMass_ZY_QT->at(0), AFB_Mass_ZY_ZPt);

 //quark level AFB vs Mass ZY ZPt
 AFBFunction(FZMass_ZY_QT_uu->at(0), BZMass_ZY_QT_uu->at(0), AFB_Mass_ZY_ZPt_uu);
 AFBFunction(FZMass_ZY_QT_dd->at(0), BZMass_ZY_QT_dd->at(0), AFB_Mass_ZY_ZPt_dd);

 //Dilution
 GetCoefficientDilution(ZMass_ZY_QT_uu_wrong->at(0), ZMass_ZY_QT_uu_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_uu);
 GetCoefficientDilution(ZMass_ZY_QT_dd_wrong->at(0), ZMass_ZY_QT_dd_total->at(0), ZMass_ZY_QT->at(0), CoefficientDilution_ZMass_ZY_QT_dd);

 GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_uu, DilutionAverage_ZMass_ZY_QT_uu, ResidualDilution_ZMass_ZY_QT_uu);
 GetDilutionAverage(CoefficientDilution_ZMass_ZY_QT_dd, DilutionAverage_ZMass_ZY_QT_dd, ResidualDilution_ZMass_ZY_QT_dd);

 GetDilutionMeta(ZMass_ZY_QT_uu_wrong->at(0), ZMass_ZY_QT_uu_total->at(0), ZMass_ZY_QT->at(0), OneMinusTwoD_uu, RelativeCrossSection_uu);
 GetDilutionMeta(ZMass_ZY_QT_dd_wrong->at(0), ZMass_ZY_QT_dd_total->at(0), ZMass_ZY_QT->at(0), OneMinusTwoD_dd, RelativeCrossSection_dd);

 hf->cd();
 
 AFB_Mass_ZY_ZPt->Write();
 
 AFB_Mass_ZY_ZPt_uu->Write();
 AFB_Mass_ZY_ZPt_dd->Write();
 
 CoefficientDilution_ZMass_ZY_QT_uu->Write();
 CoefficientDilution_ZMass_ZY_QT_dd->Write();
 
 DilutionAverage_ZMass_ZY_QT_uu->Write();
 DilutionAverage_ZMass_ZY_QT_dd->Write();
 
 ResidualDilution_ZMass_ZY_QT_uu->Write();
 ResidualDilution_ZMass_ZY_QT_dd->Write();
 
 OneMinusTwoD_uu->Write();
 OneMinusTwoD_dd->Write();
 
 RelativeCrossSection_uu->Write();
 RelativeCrossSection_dd->Write();

}

void HistsResBosD0::InitialSysName()
{

}
