#ifndef Tools_DilutionReweighting_h
#define Tools_DilutionReweighting_h

#include "RootCommon.h"

class DilutionReweighting
{
 public:

 TFile *hf;

 TH3D* CrossSection_uu;
 TH3D* CrossSection_dd;
 TH3D* CrossSection_ss;
 TH3D* CrossSection_cc;
 TH3D* CrossSection_bb;

 TH3D* A0_uu_Plot;
 TH3D* A0_dd_Plot;
 TH3D* A0_ss_Plot;
 TH3D* A0_cc_Plot;
 TH3D* A0_bb_Plot;

 TH3D* Dilution_uu_Residual;
 TH3D* Dilution_dd_Residual;
 TH3D* Dilution_uu_Average;
 TH3D* Dilution_dd_Average;
 TH3D* uuFittedSlope;
 TH3D* uuFittedOffset;
 TH3D* ddFittedSlope;
 TH3D* ddFittedOffset;

 DilutionReweighting();
 virtual void Initial();
 virtual double GetCrossSection(double cos_theta, double Mass, double ZY, double QT, double stw, double P0u = -999.0, double P0d = -999.0);
 virtual double GetReweightingFactor(double cos_theta, double Mass, double ZY, double QT, double stw, double P0u, double P0d);
 virtual void Close(){delete hf;};

};

#endif

