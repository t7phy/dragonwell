#ifndef WZPolarizationTools_cxx
#define WZPolarizationTools_cxx

#include "Tools/Tools.h"
#include "TMath.h"
#include "TLorentzVector.h"

using namespace std;

//  W boson direction in the WZ rest frame wrt to the lab z axis
double CalculateCosThetaV(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab)
{
 TLorentzVector WZPropagator = WBoson_lab + ZBoson_lab;

 TLorentzVector WBoson_CMS = WBoson_lab;
 TLorentzVector ZBoson_CMS = ZBoson_lab;

 WBoson_CMS.Boost(-WZPropagator.BoostVector());
 ZBoson_CMS.Boost(-WZPropagator.BoostVector());

// double Value = cos(WBoson_CMS.Theta());
 double Value = WBoson_CMS.CosTheta();
// double Value = cos((WBoson_CMS.Vect()).Angle(WZPropagator.Vect()));

 return Value;
}

// W boson direction in the WZ rest frame wrt to the lab WZ axis
double CosAngle_W_WZ_lab(TLorentzVector W_lep, TLorentzVector W_Nu, TLorentzVector Z_lep_minus, TLorentzVector Z_lep_plus) {
   TLorentzVector W = W_lep + W_Nu;
   TLorentzVector Z = Z_lep_minus + Z_lep_plus;
   TLorentzVector WZ = W + Z; 

   TLorentzVector W_new = W;
   W_new.Boost((-1)*WZ.BoostVector());

   return cos((W_new.Vect()).Angle(WZ.Vect()));
}

double CalculateCosThetaLepW(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab, TLorentzVector WLepton_lab)
{
 TLorentzVector WBoson_CMS = WBoson_lab;
 TLorentzVector ZBoson_CMS = ZBoson_lab;
 TLorentzVector WLepton_CMS = WLepton_lab;

 TLorentzVector WZPropagator = WBoson_lab + ZBoson_lab;
 WBoson_CMS.Boost(-WZPropagator.BoostVector());
 ZBoson_CMS.Boost(-WZPropagator.BoostVector());
 WLepton_CMS.Boost(-WZPropagator.BoostVector());

 TLorentzVector WLepton_W_CMS = WLepton_CMS;
 WLepton_W_CMS.Boost(-WBoson_CMS.BoostVector());

 double Value = cos(WLepton_W_CMS.Angle(WBoson_CMS.Vect()));

 return Value;

}

double CalculateCosThetaLepZ(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab, TLorentzVector ZLepton_lab)
{
 TLorentzVector WBoson_CMS = WBoson_lab;
 TLorentzVector ZBoson_CMS = ZBoson_lab;
 TLorentzVector ZLepton_CMS = ZLepton_lab;

 TLorentzVector WZPropagator = WBoson_lab + ZBoson_lab;
 WBoson_CMS.Boost(-WZPropagator.BoostVector());
 ZBoson_CMS.Boost(-WZPropagator.BoostVector());
 ZLepton_CMS.Boost(-WZPropagator.BoostVector());

 TLorentzVector ZLepton_Z_CMS = ZLepton_CMS;
 ZLepton_Z_CMS.Boost(-ZBoson_CMS.BoostVector());
 
 double Value = cos(ZLepton_Z_CMS.Angle(ZBoson_CMS.Vect()));
 
 return Value;
}

double CalculateDY_WZ(TLorentzVector WBoson_lab, TLorentzVector ZBoson_lab)
{
 double Value = ZBoson_lab.Rapidity() - WBoson_lab.Rapidity();

 return Value;
}

double CalculateDY_3Z(TLorentzVector ZBoson_lab, TLorentzVector WLepton_lab)
{
 double Value = ZBoson_lab.Rapidity() - WLepton_lab.Rapidity();

 return Value;
}

double CalculateDY_3N(TLorentzVector ZLepton_lab, TLorentzVector WLepton_lab)
{
 double Value = ZLepton_lab.Rapidity() - WLepton_lab.Rapidity();

 return Value;
}

double CalculateNeutrinoPz(TLorentzVector Lepton, TLorentzVector Neutrino, double WMass)
{
 double Value;

 double Px2 = (Lepton.Px() + Neutrino.Px()) * (Lepton.Px() + Neutrino.Px());
 double Py2 = (Lepton.Py() + Neutrino.Py()) * (Lepton.Py() + Neutrino.Py());
 double Constant = Lepton.E() * Lepton.E() + Neutrino.Et() * Neutrino.Et() - Px2 - Py2 - Lepton.Pz() * Lepton.Pz() - WMass * WMass;
 double a = 4 * Lepton.E() * Lepton.E() - 4 * Lepton.Pz() * Lepton.Pz();
 double b = 4 * Constant * Lepton.Pz();
 double c = 4 * Lepton.E() * Lepton.E() * Neutrino.Et() * Neutrino.Et() - Constant * Constant;

 if((b * b - 4 * a * c) < 0){
   Value = ((-1) * b) / (2 * a);
 }
 else{
   double Value1 = ((-1) * b + sqrt(b * b - 4 * a * c)) / (2 * a);
   double Value2 = ((-1) * b - sqrt(b * b - 4 * a * c)) / (2 * a);
   if(fabs(Value1) < fabs(Value2)) Value = Value1;
   if(fabs(Value1) > fabs(Value2)) Value = Value2;
 }

 return Value;
}

double CalculateNeutrinoPz_Eta(TLorentzVector Lepton, TLorentzVector Neutrino, double WMass, int Charge)
{
 double Value;

 double Px2 = (Lepton.Px() + Neutrino.Px()) * (Lepton.Px() + Neutrino.Px());
 double Py2 = (Lepton.Py() + Neutrino.Py()) * (Lepton.Py() + Neutrino.Py());
 double Constant = Lepton.E() * Lepton.E() + Neutrino.Et() * Neutrino.Et() - Px2 - Py2 - Lepton.Pz() * Lepton.Pz() - WMass * WMass;
 double a = 4 * Lepton.E() * Lepton.E() - 4 * Lepton.Pz() * Lepton.Pz();
 double b = 4 * Constant * Lepton.Pz();
 double c = 4 * Lepton.E() * Lepton.E() * Neutrino.Et() * Neutrino.Et() - Constant * Constant;

 if((b * b - 4 * a * c) < 0){
   Value = ((-1) * b) / (2 * a);
 }
 else{
   double Value1 = ((-1) * b + sqrt(b * b - 4 * a * c)) / (2 * a);
   double Value2 = ((-1) * b - sqrt(b * b - 4 * a * c)) / (2 * a);

   TLorentzVector Neutrino1, Neutrino2, WBoson1, WBoson2;
   Neutrino1.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), Value1, sqrt(Neutrino.Et() * Neutrino.Et() + Value1 * Value1));
   Neutrino2.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), Value2, sqrt(Neutrino.Et() * Neutrino.Et() + Value2 * Value2));
   /*WBoson1 = Neutrino1 + Lepton;
   WBoson2 = Neutrino2 + Lepton;

   double cos_theta1, cos_theta2 = 0.0;
   if(Charge > 0) cos_theta1 = calculate_theta(WBoson1, Neutrino1, Lepton) * WBoson1.Rapidity() / fabs(WBoson1.Rapidity());
   if(Charge < 0) cos_theta1 = calculate_theta(WBoson1, Lepton, Neutrino1) * WBoson1.Rapidity() / fabs(WBoson1.Rapidity());
   if(Charge > 0) cos_theta2 = calculate_theta(WBoson2, Neutrino2, Lepton) * WBoson2.Rapidity() / fabs(WBoson2.Rapidity());
   if(Charge < 0) cos_theta2 = calculate_theta(WBoson2, Lepton, Neutrino2) * WBoson2.Rapidity() / fabs(WBoson2.Rapidity());

   if(Charge > 0){
     if((cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) < 0)) Value = Value1;
     else if((cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) < 0)) Value = Value2;
     else Value = fabs(fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > fabs(fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) ? Value2 : Value1;
   }
   if(Charge < 0){
     if((cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) < 0)) Value = Value2;
     else if((cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) < 0)) Value = Value1;
     else Value = fabs(fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > fabs(fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) ? Value2 : Value1;
   }
   */
   if(Charge > 0){
     Value = fabs(Neutrino1.Eta() - 2.0 * Lepton.Eta()) < fabs(Neutrino1.Eta() - 2.0 * Lepton.Eta()) ? Value1 : Value2;
   }
   if(Charge < 0){
     Value = fabs(Neutrino1.Eta() - 0.5 * Lepton.Eta()) < fabs(Neutrino1.Eta() - 0.5 * Lepton.Eta()) ? Value1 : Value2;
   }
 }

 return Value;
}

pair<double, int> CalculateNeutrinoPz_Eta2(TLorentzVector Lepton, TLorentzVector Neutrino, double WMass, int Charge)
{
 pair<double, int> Value;

 double Px2 = (Lepton.Px() + Neutrino.Px()) * (Lepton.Px() + Neutrino.Px());
 double Py2 = (Lepton.Py() + Neutrino.Py()) * (Lepton.Py() + Neutrino.Py());
 double Constant = Lepton.E() * Lepton.E() + Neutrino.Et() * Neutrino.Et() - Px2 - Py2 - Lepton.Pz() * Lepton.Pz() - WMass * WMass;
 double a = 4 * Lepton.E() * Lepton.E() - 4 * Lepton.Pz() * Lepton.Pz();
 double b = 4 * Constant * Lepton.Pz();
 double c = 4 * Lepton.E() * Lepton.E() * Neutrino.Et() * Neutrino.Et() - Constant * Constant;

 if((b * b - 4 * a * c) < 0){
   Value = make_pair(((-1) * b) / (2 * a), 0);
 }
 else{
   double Value1 = ((-1) * b + sqrt(b * b - 4 * a * c)) / (2 * a);
   double Value2 = ((-1) * b - sqrt(b * b - 4 * a * c)) / (2 * a);

   TLorentzVector Neutrino1, Neutrino2, WBoson1, WBoson2;
   Neutrino1.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), Value1, sqrt(Neutrino.Et() * Neutrino.Et() + Value1 * Value1));
   Neutrino2.SetPxPyPzE(Neutrino.Px(), Neutrino.Py(), Value2, sqrt(Neutrino.Et() * Neutrino.Et() + Value2 * Value2));
   WBoson1 = Neutrino1 + Lepton;
   WBoson2 = Neutrino2 + Lepton;

   double cos_theta1, cos_theta2 = 0.0;
   if(Charge > 0) cos_theta1 = calculate_theta(WBoson1, Neutrino1, Lepton) * WBoson1.Rapidity() / fabs(WBoson1.Rapidity());
   if(Charge < 0) cos_theta1 = calculate_theta(WBoson1, Lepton, Neutrino1) * WBoson1.Rapidity() / fabs(WBoson1.Rapidity());
   if(Charge > 0) cos_theta2 = calculate_theta(WBoson2, Neutrino2, Lepton) * WBoson2.Rapidity() / fabs(WBoson2.Rapidity());
   if(Charge < 0) cos_theta2 = calculate_theta(WBoson2, Lepton, Neutrino2) * WBoson2.Rapidity() / fabs(WBoson2.Rapidity());

   if(Charge > 0){
     if((cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) < 0)) Value = make_pair(Value1, 1);
     else if((cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) < 0)) Value = make_pair(Value2, 1);
     else Value = fabs(fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > fabs(fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) ? make_pair(Value2, 2) : make_pair(Value1, 2);
   }
   if(Charge < 0){
     if((cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) < 0)) Value = make_pair(Value2, 1);
     else if((cos_theta2 * (fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) > 0) && (cos_theta1 * (fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) < 0)) Value = make_pair(Value1, 1);
     else Value = fabs(fabs(Neutrino1.Eta()) - fabs(Lepton.Eta())) > fabs(fabs(Neutrino2.Eta()) - fabs(Lepton.Eta())) ? make_pair(Value2, 2) : make_pair(Value1, 2);
   }

 }

 return Value;
}

double CalculateDeltaPhiLepWLepZ(TLorentzVector ZLepton_lab, TLorentzVector WLepton_lab)
{
 double Value;

 Value = ZLepton_lab.DeltaPhi(WLepton_lab);

 return Value;
}

double CalculateDeltaPhiLepWLepZWZFrame(TLorentzVector ZLepton_lab, TLorentzVector WLepton_lab, TLorentzVector WZPropagator_lab)
{
 double Value;

 TLorentzVector ZLepton_CMS = ZLepton_lab;
 TLorentzVector WLepton_CMS = WLepton_lab;

 ZLepton_CMS.Boost(-WZPropagator_lab.BoostVector());
 WLepton_CMS.Boost(-WZPropagator_lab.BoostVector());

 if(ZLepton_lab.Pt() < 1e-10 || WLepton_lab.Pt() < 1e-10) return -99.0;

 Value = ZLepton_CMS.DeltaPhi(WLepton_CMS);

 return Value;
}

double CalculateR21(TLorentzVector ZBoson_lab, TLorentzVector WBoson_lab)
{
 double Value;

 Value = (ZBoson_lab.Pt() > WBoson_lab.Pt()) ? (WBoson_lab.Pt() / ZBoson_lab.Pt()) : (ZBoson_lab.Pt() / WBoson_lab.Pt());

 return Value;
}

#endif
