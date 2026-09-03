#include "Tools/DilutionReweighting.h"

DilutionReweighting::DilutionReweighting()
{

}

void DilutionReweighting::Initial()
{
 hf = new TFile("CMSCrossSection.root");

 CrossSection_uu = (TH3D *)hf->Get("ZMass_ZY_QT_uu");
 CrossSection_dd = (TH3D *)hf->Get("ZMass_ZY_QT_dd");
 CrossSection_ss = (TH3D *)hf->Get("ZMass_ZY_QT_ss");
 CrossSection_cc = (TH3D *)hf->Get("ZMass_ZY_QT_cc");
 CrossSection_bb = (TH3D *)hf->Get("ZMass_ZY_QT_bb");

 A0_uu_Plot = (TH3D *)hf->Get("A0_Mass_ZY_QT_uu");
 A0_dd_Plot = (TH3D *)hf->Get("A0_Mass_ZY_QT_dd");
 A0_ss_Plot = (TH3D *)hf->Get("A0_Mass_ZY_QT_ss");
 A0_cc_Plot = (TH3D *)hf->Get("A0_Mass_ZY_QT_cc");
 A0_bb_Plot = (TH3D *)hf->Get("A0_Mass_ZY_QT_bb");

 Dilution_uu_Residual = (TH3D *)hf->Get("CoefficientZMass_ZY_QT_uu_wrong_Residual");
 Dilution_dd_Residual = (TH3D *)hf->Get("CoefficientZMass_ZY_QT_dd_wrong_Residual");
 Dilution_uu_Average = (TH3D *)hf->Get("CoefficientZMass_ZY_QT_uu_wrong_Average");
 Dilution_dd_Average = (TH3D *)hf->Get("CoefficientZMass_ZY_QT_dd_wrong_Average");
 uuFittedSlope = (TH3D *)hf->Get("AFB_ZMass_ZY_QT_uu_FittedSlope");
 uuFittedOffset = (TH3D *)hf->Get("AFB_ZMass_ZY_QT_uu_FittedOffset");
 ddFittedSlope = (TH3D *)hf->Get("AFB_ZMass_ZY_QT_dd_FittedSlope");
 ddFittedOffset = (TH3D *)hf->Get("AFB_ZMass_ZY_QT_dd_FittedOffset");
}

double DilutionReweighting::GetCrossSection(double cos_theta, double Mass, double ZY, double QT, double stw, double P0u, double P0d)
{
 int MassBin = CrossSection_uu->FindBin(Mass, ZY, QT) % (CrossSection_uu->GetNbinsX() + 2);
 int ZYBin = (CrossSection_uu->FindBin(Mass, ZY, QT) / (CrossSection_uu->GetNbinsX() + 2)) % (CrossSection_uu->GetNbinsY() + 2);
 int QTBin = (CrossSection_uu->FindBin(Mass, ZY, QT) / (CrossSection_uu->GetNbinsX() + 2)) / (CrossSection_uu->GetNbinsY() + 2);

 int P0ZYBin = (Dilution_uu_Average->FindBin(0.5, ZY, QT) / (Dilution_uu_Average->GetNbinsX() + 2)) % (Dilution_uu_Average->GetNbinsY() + 2);
 int P0QTBin = (Dilution_uu_Average->FindBin(0.5, ZY, QT) / (Dilution_uu_Average->GetNbinsX() + 2)) / (Dilution_uu_Average->GetNbinsY() + 2);

 double L0_uu = CrossSection_uu->GetBinContent(MassBin, ZYBin, QTBin) * (3.0 / 8.0) * (0.1);
 double L0_dd = CrossSection_dd->GetBinContent(MassBin, ZYBin, QTBin) * (3.0 / 8.0) * (0.1);
 double L0_ss = CrossSection_ss->GetBinContent(MassBin, ZYBin, QTBin) * (3.0 / 8.0) * (0.1);
 double L0_cc = CrossSection_cc->GetBinContent(MassBin, ZYBin, QTBin) * (3.0 / 8.0) * (0.1);
 double L0_bb = CrossSection_bb->GetBinContent(MassBin, ZYBin, QTBin) * (3.0 / 8.0) * (0.1);

 double A0_uu = A0_uu_Plot->GetBinContent(MassBin, ZYBin, QTBin) * L0_uu;
 double A0_dd = A0_dd_Plot->GetBinContent(MassBin, ZYBin, QTBin) * L0_dd;
 double A0_ss = A0_ss_Plot->GetBinContent(MassBin, ZYBin, QTBin) * L0_ss;
 double A0_cc = A0_cc_Plot->GetBinContent(MassBin, ZYBin, QTBin) * L0_cc;
 double A0_bb = A0_bb_Plot->GetBinContent(MassBin, ZYBin, QTBin) * L0_bb;

 double P0uValue = 0.0;
 double P0dValue = 0.0;

 if(P0u < -900 || P0d < -900){
   P0uValue = Dilution_uu_Average->GetBinContent(1, ZYBin, QTBin);
   P0dValue = Dilution_dd_Average->GetBinContent(1, ZYBin, QTBin);
 }
 else{
   P0uValue = P0u;
   P0dValue = P0d;
 }

 double Delta_uu = Dilution_uu_Residual->GetBinContent(MassBin, ZYBin, QTBin);
 double Delta_dd = Dilution_dd_Residual->GetBinContent(MassBin, ZYBin, QTBin);

 double uuSlopeValue = uuFittedSlope->GetBinContent(MassBin, ZYBin, QTBin);
 double uuOffsetValue = uuFittedOffset->GetBinContent(MassBin, ZYBin, QTBin);
 double ddSlopeValue = ddFittedSlope->GetBinContent(MassBin, ZYBin, QTBin);
 double ddOffsetValue = ddFittedOffset->GetBinContent(MassBin, ZYBin, QTBin);

 double A4_uu = (8.0 / 3.0) * ((Delta_uu + P0uValue) * (uuSlopeValue * stw + uuOffsetValue) + (Delta_dd + P0dValue) * (ddSlopeValue * stw + ddOffsetValue)) * L0_uu;
 double A4_dd = (8.0 / 3.0) * ((Delta_uu + P0uValue) * (uuSlopeValue * stw + uuOffsetValue) + (Delta_dd + P0dValue) * (ddSlopeValue * stw + ddOffsetValue)) * L0_dd;
 double A4_ss = (8.0 / 3.0) * ((Delta_uu + P0uValue) * (uuSlopeValue * stw + uuOffsetValue) + (Delta_dd + P0dValue) * (ddSlopeValue * stw + ddOffsetValue)) * L0_ss;
 double A4_cc = (8.0 / 3.0) * ((Delta_uu + P0uValue) * (uuSlopeValue * stw + uuOffsetValue) + (Delta_dd + P0dValue) * (ddSlopeValue * stw + ddOffsetValue)) * L0_cc;
 double A4_bb = (8.0 / 3.0) * ((Delta_uu + P0uValue) * (uuSlopeValue * stw + uuOffsetValue) + (Delta_dd + P0dValue) * (ddSlopeValue * stw + ddOffsetValue)) * L0_bb;

 double Value = (L0_uu * (1 + cos_theta * cos_theta) + A0_uu * 0.5 * (1.0 - 3.0 * cos_theta * cos_theta) + A4_uu * (cos_theta))
              + (L0_dd * (1 + cos_theta * cos_theta) + A0_dd * 0.5 * (1.0 - 3.0 * cos_theta * cos_theta) + A4_dd * (cos_theta))
              + (L0_ss * (1 + cos_theta * cos_theta) + A0_ss * 0.5 * (1.0 - 3.0 * cos_theta * cos_theta) + A4_ss * (cos_theta))
              + (L0_cc * (1 + cos_theta * cos_theta) + A0_cc * 0.5 * (1.0 - 3.0 * cos_theta * cos_theta) + A4_cc * (cos_theta))
              + (L0_bb * (1 + cos_theta * cos_theta) + A0_bb * 0.5 * (1.0 - 3.0 * cos_theta * cos_theta) + A4_bb * (cos_theta));

 return Value;
}

double DilutionReweighting::GetReweightingFactor(double cos_theta, double Mass, double ZY, double QT, double stw, double P0u, double P0d)
{
 double Numer = GetCrossSection(cos_theta, Mass, ZY, QT, stw, P0u, P0d);
 double Denom = GetCrossSection(cos_theta, Mass, ZY, QT, 0.2315);

 double Value = Numer / Denom;

 return Value;
}
