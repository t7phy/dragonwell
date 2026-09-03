#include "ElectroweakTheory/ZWidthDep.h"

ZWidthDep::ZWidthDep()
{
 InputStw(0.2315);
 InputQuark(1);
}

void ZWidthDep::openFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void ZWidthDep::InputStw(double stw)
{
 this->stwl = stw;

 if(this->iflag == 1){
   this->stwQ = this->stwl - 0.0001;
 }

 if(this->iflag == 2){
   this->stwQ = this->stwl - 0.0002;
 }
 if(this->iflag == 3){
   this->stwQ = this->stwl;
 }

 this->gVq = (I3Q - 2.0 * ChargeQ * stwQ);
 this->gAq = I3Q;
 this->gVl = (I3l - 2.0 * (double)Chargel * stwl);
 this->gAl = I3l;

// cout<<"Effective weak mixing angle: "<<stwl<<endl;
// cout<<"gVq: "<<gVq<<endl;
// cout<<"gAq: "<<gAq<<endl;
// cout<<"gVl: "<<gVl<<endl;
// cout<<"gAl: "<<gAl<<endl;
}

void ZWidthDep::InputQuark(int iflag)
{
 this->iflag = iflag;

 if(iflag == 1){
   this->stwQ = stwl - 0.0001;
   this->ChargeQ = 2.0 / 3.0;
   this->I3Q = 0.5;
 }

 if(iflag == 2){
   this->stwQ = stwl - 0.0002;
   this->ChargeQ = - 1.0 / 3.0;
   this->I3Q = -0.5;
 }
 if(iflag == 3){
   this->stwQ = stwl;
   this->ChargeQ = -1.0;
   this->I3Q = -0.5;
 }

 this->gVq = (I3Q - 2.0 * ChargeQ * stwQ);
 this->gAq = I3Q;
 this->gVl = (I3l - 2.0 * (double)Chargel * stwl);
 this->gAl = I3l;
}

double ZWidthDep::ReChi(double mass)
{
 double Numer = mass * mass;
 double Denom = sqrt((ZPeakMass * ZPeakMass - mass * mass) * (ZPeakMass * ZPeakMass - mass * mass) + ZWidth * ZWidth * ZPeakMass * ZPeakMass);

 double onshell_stw = 1 - WPeakMass * WPeakMass / ZPeakMass / ZPeakMass;
// double onshell_stw = stwl;
 double factor = 1.0 / (4.0 * onshell_stw * (1 - onshell_stw));

 double cos_deltaR = (ZPeakMass * ZPeakMass - mass * mass) / sqrt((ZPeakMass * ZPeakMass - mass * mass) * (ZPeakMass * ZPeakMass - mass * mass) + ZWidth * ZWidth * ZPeakMass * ZPeakMass);

 double Value = (Numer / Denom) * factor * cos_deltaR;

 //cout<<"Mass: "<<mass<<" ReChi: "<<Value<<endl;

 return Value;
}

double ZWidthDep::ChiSquare(double mass)
{
 double Numer = mass * mass * mass * mass;
 double Denom = (ZPeakMass * ZPeakMass - mass * mass) * (ZPeakMass * ZPeakMass - mass * mass) + ZWidth * ZWidth * ZPeakMass * ZPeakMass;

 double onshell_stw = 1 - WPeakMass * WPeakMass / ZPeakMass / ZPeakMass;
// double onshell_stw = stwl;
 double factor = 1.0 / (4.0 * onshell_stw * (1 - onshell_stw));

 double Value = (Numer / Denom) * factor * factor;

 //cout<<"Mass: "<<mass<<" ChiSquare: "<<Value<<endl;

 return Value;
}

double ZWidthDep::CalL0(double mass)
{
 //1GeV^-2=0.38937966mb
 //1mb=10^9pb
 //Z->ll BR=0.03

 if(mass < 1e-6) return 0.0;

 double L01 = (double)Chargel * (double)Chargel * ChargeQ * ChargeQ;
 double L02 = (-2.0) * (double)Chargel * ChargeQ * gVq * gVl * ReChi(mass);
 double L03 = (gVq * gVq + gAq * gAq) * (gVl * gVl + gAl * gAl) * ChiSquare(mass);

 double Value = (L01 + L02 + L03) * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 //cout<<"Mass: "<<mass<<" L01: "<<L01<<" L02: "<<L02<<" L03: "<<L03<<" L0: "<<Value<<endl;

 return Value;
}

double ZWidthDep::CalL0Gamma(double mass)
{
 if(mass < 1e-6) return 0.0;

 double L01 = (double)Chargel * (double)Chargel * ChargeQ * ChargeQ;

 double Value = L01 * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 return Value;
}

double ZWidthDep::CalL0Interference(double mass)
{
 if(mass < 1e-6) return 0.0;

 double L02 = (-2.0) * (double)Chargel * ChargeQ * gVq * gVl * ReChi(mass);

 double Value = L02 * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 return Value;
}

double ZWidthDep::CalL0Z(double mass)
{
 if(mass < 1e-6) return 0.0;

 double L03 = (gVq * gVq + gAq * gAq) * (gVl * gVl + gAl * gAl) * ChiSquare(mass);

 double Value = L03 * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 return Value;
}

double ZWidthDep::CalA4(double mass)
{
 if(mass < 1e-6) return 0.0;

 double A41 = (-4.0) * (double)Chargel * ChargeQ * gAq * gAl * ReChi(mass);
 double A42 = 8.0 * gVq * gAq * gVl * gAl * ChiSquare(mass);

 double Value = (A41 + A42) * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 //cout<<"Mass: "<<mass<<" A41: "<<A41<<" A42: "<<A42<<" A4: "<<Value<<endl;

 return Value;
}

double ZWidthDep::CalA4Interference(double mass)
{
 if(mass < 1e-6) return 0.0;

 double A41 = (-4.0) * (double)Chargel * ChargeQ * gAq * gAl * ReChi(mass);

 double Value = A41 * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 return Value;
}

double ZWidthDep::CalA4Z(double mass)
{
 if(mass < 1e-6) return 0.0;

 double A42 = 8.0 * gVq * gAq * gVl * gAl * ChiSquare(mass);

 double Value = A42 * (M_PI * (pyalem(mass * mass)) * (pyalem(mass * mass)) / (mass * mass)) * 1e9 * 0.38937966;

 return Value;
}

double ZWidthDep::pyalem(double q2){
// Returns the running electromagnetic coupling alpha
//PN Stolen shamelessly from ResBos
//
//...Calculate real part of photon vacuum polarization.
//...For leptons simplify by using asymptotic (q^2 >> m^2) expressions.
//   For hadrons use parametrization of H. Burkhardt et al.
//   See R. Kleiss et al, CERN 89-08, vol. 3, pp. 129-131.
//csb___see also Phys.Lett.B356:398-403,1995

  double pi, alpha0, rpigg, aempi;
  pi = 3.1415927;
  alpha0=1./137.04;
  aempi= alpha0/(3.*pi);

  if (q2 < 2e-6)
    rpigg =0.0;
  else if(q2 < 0.09)
    rpigg = aempi*(13.4916 + log(q2)) + 0.00835*log(1.+q2);
  else if(q2 < 9.)
    rpigg=aempi*(16.3200+2.0*log(q2))+ 0.00238*log(1.0+3.927*q2);
  else if(q2 < 1e4)
    rpigg=aempi*(13.4955+3.0*log(q2))+0.00165+ 0.00299*log(1.0+q2);
  else
    rpigg=aempi*(13.4955+3.0*log(q2))+ 0.00221 + 0.00293*log(1.0+q2);

//...Calculate running alpha_em.
  return alpha0/(1.0-rpigg);
}//pyalem ->

double ZWidthDep::ZCrossSection(double mass, int iflag, TString Process)
{
 InputQuark(abs(iflag));

 if(iflag > 0){
   if(Process == "") return (8.0 / 3.0) * CalL0(mass);
   if(Process == "F") return (4.0 / 3.0) * CalL0(mass) + (1.0 / 2.0) * CalA4(mass);
   if(Process == "B") return (4.0 / 3.0) * CalL0(mass) - (1.0 / 2.0) * CalA4(mass);
 }
 else if(iflag < 0){
   if(Process == "") return (8.0 / 3.0) * CalL0(mass);
   if(Process == "F") return (4.0 / 3.0) * CalL0(mass) - (1.0 / 2.0) * CalA4(mass);
   if(Process == "B") return (4.0 / 3.0) * CalL0(mass) + (1.0 / 2.0) * CalA4(mass);
 }

 return 0.0;
}

double ZWidthDep::CalAFB(double mass, TString flag)
{
// double Value = (3.0 / 8.0) * ((double)CalA4(mass) / (double)CalL0(mass));
 InputQuark(1);
 double uA4 = CalA4(mass);
 double uL0 = CalL0(mass);
 double uA4_Z = CalA4Z(mass);
 double uL0_Z = CalL0Z(mass);
 double uA4_Interference = CalA4Interference(mass);
 double uL0_Interference = CalL0Interference(mass);
 InputQuark(2);
 double dA4 = CalA4(mass);
 double dL0 = CalL0(mass);
 double dA4_Z = CalA4Z(mass);
 double dL0_Z = CalL0Z(mass);
 double dA4_Interference = CalA4Interference(mass);
 double dL0_Interference = CalL0Interference(mass);


// double Value = (3.0 / 8.0) * ((uA4 + (980.0 / 920.0) * dA4) / (uL0 + (980.0 / 920.0) * dL0));
 double Value;
 if(flag == "") Value = (3.0 / 8.0) * ((uA4 + dA4) / (uL0 + dL0));
 if(flag == "ZU") Value = (3.0 / 8.0) * (uA4 / uL0);
 if(flag == "ZD") Value = (3.0 / 8.0) * (dA4 / dL0);
 if(flag == "ZU_Z") Value = (3.0 / 8.0) * (uA4_Z / uL0);
 if(flag == "ZU_ZGamma") Value = (3.0 / 8.0) * (uA4_Interference / uL0);
 if(flag == "ZD_Z") Value = (3.0 / 8.0) * (dA4_Z / dL0);
 if(flag == "ZD_ZGamma") Value = (3.0 / 8.0) * (dA4_Interference / dL0);

 //cout<<"Mass: "<<mass<<" AFB: "<<Value<<endl;

 return Value;
}

double CalAFBCurve(double x)
{
 return x+sin(x);
}

double ZWidthDep::ReChiMassDerive(double mass, double DeltaMass)
{
 double Value = (ReChi(mass + DeltaMass) - ReChi(mass - DeltaMass)) / (2.0 * DeltaMass);

 return Value;
}

double ZWidthDep::ReChiStwDerive(double stw, double DeltaStw, double mass)
{
 InputStw(stw + DeltaStw);
 double Value1 = ReChi(mass);

 InputStw(stw - DeltaStw);
 double Value2 = ReChi(mass);

 double Value = (Value1 - Value2) / (2.0 * DeltaStw);

 return Value;
}

double ZWidthDep::ChiSquareMassDerive(double mass, double DeltaMass)
{
 double Value = (ChiSquare(mass + DeltaMass) - ChiSquare(mass - DeltaMass)) / (2.0 * DeltaMass);

 return Value;
}

double ZWidthDep::ChiSquareStwDerive(double stw, double DeltaStw, double mass)
{
 InputStw(stw + DeltaStw);
 double Value1 = ChiSquare(mass);

 InputStw(stw - DeltaStw);
 double Value2 = ChiSquare(mass);

 double Value = (Value1 - Value2) / (2.0 * DeltaStw);

 return Value;

}

double ZWidthDep::CalA41(double mass)
{
 double A41 = (-4.0) * (double)Chargel * ChargeQ * gAq * gAl * ReChi(mass);
// double A41 = (-4.0) * (double)Chargel * ChargeQ * ReChi(mass);

 double L01 = (double)Chargel * (double)Chargel * ChargeQ * ChargeQ;
 double L02 = (-2.0) * (double)Chargel * ChargeQ * gVq * gVl * ReChi(mass);
 double L03 = (gVq * gVq + gAq * gAq) * (gVl * gVl + gAl * gAl) * ChiSquare(mass);
 
 double Value = L01 + L02 + L03;

 return A41 / Value;
}

double ZWidthDep::CalA42(double mass)
{
 double A42 = 8.0 * gVq * gAq * gVl * gAl * ChiSquare(mass);
// double A42 = 8.0 * ChiSquare(mass);

 double L01 = (double)Chargel * (double)Chargel * ChargeQ * ChargeQ;
 double L02 = (-2.0) * (double)Chargel * ChargeQ * gVq * gVl * ReChi(mass);
 double L03 = (gVq * gVq + gAq * gAq) * (gVl * gVl + gAl * gAl) * ChiSquare(mass);
 
 double Value = L01 + L02 + L03;

 return A42 / Value;
}

double ZWidthDep::A41MassDerive(double mass, double DeltaMass)
{
 double Value = (CalA41(mass + DeltaMass) - CalA41(mass - DeltaMass)) / (2.0 * DeltaMass);

 return Value;
}

double ZWidthDep::A41StwDerive(double stw, double DeltaStw, double mass)
{
 InputStw(stw + DeltaStw);
 double Value1 = CalA41(mass);

 InputStw(stw - DeltaStw);
 double Value2 = CalA41(mass);

 double Value = (Value1 - Value2) / (2.0 * DeltaStw);

 return Value;

}

double ZWidthDep::A42MassDerive(double mass, double DeltaMass)
{
 double Value = (CalA42(mass + DeltaMass) - CalA42(mass - DeltaMass)) / (2.0 * DeltaMass);

 return Value;
}

double ZWidthDep::A42StwDerive(double stw, double DeltaStw, double mass)
{
 InputStw(stw + DeltaStw);
 double Value1 = CalA42(mass);

 InputStw(stw - DeltaStw);
 double Value2 = CalA42(mass);

 double Value = (Value1 - Value2) / (2.0 * DeltaStw);

 return Value;

}

double ZWidthDep::AFBMassDerive(double mass, double DeltaMass)
{
 double Value = (CalAFB(mass + DeltaMass) - CalAFB(mass - DeltaMass)) / (2.0 * DeltaMass);

 return Value;
}

double ZWidthDep::AFBStwDerive(double stw, double DeltaStw, double mass, TString flag)
{
 InputStw(stw + DeltaStw);
 double Value1 = CalAFB(mass, flag);

 InputStw(stw - DeltaStw);
 double Value2 = CalAFB(mass, flag);

 double Value = (Value1 - Value2) / (2.0 * DeltaStw);
// double Value = Value1 - Value2;

 return Value;
}

double ZWidthDep::AFBMassStwDerive(double mass, double DeltaMass, double stw, double DeltaStw)
{
 InputStw(stw + DeltaStw);

 double Value1 = CalAFB(mass + DeltaMass);

 double Value2 = CalAFB(mass - DeltaMass);

 InputStw(stw - DeltaStw);

 double Value3 = CalAFB(mass + DeltaMass);

 double Value4 = CalAFB(mass - DeltaMass);

 double Value = (Value1 - Value2 - Value3 + Value4) / (4 * DeltaMass * DeltaStw);

 return Value;
}

void ZWidthDep::DrawReChiMassDerive(int bin, double left, double right, double DeltaMass)
{
 iReChi++;

 TString HistName = (TString)"ReChiMassDerive_" + (int)iReChi;
 plot_ReChiMassDerive[iReChi] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_ReChiMassDerive[iReChi]->GetBinCenter(i);
   plot_ReChiMassDerive[iReChi]->SetBinContent(i, ReChiMassDerive(BinCenter, DeltaMass));
   plot_ReChiMassDerive[iReChi]->SetBinError(i, 0);
 }

 hf->cd();
 plot_ReChiMassDerive[iReChi]->Write();
}

void ZWidthDep::DrawReChiStwDerive(int bin, double left, double right, double DeltaStw, double mass)
{
 iReChiStw++;

// TString HistName = (TString)"ReChiStwDerive_Delta" + (double)DeltaStw + (TString)"_Mass" + (double)mass;
 TString HistName = (TString)"ReChiStwDerive_Mass" + (double)mass;
 plot_ReChiStwDerive[iReChiStw] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_ReChiStwDerive[iReChiStw]->GetBinCenter(i);
   plot_ReChiStwDerive[iReChiStw]->SetBinContent(i, ReChiStwDerive(BinCenter, DeltaStw, mass));
   plot_ReChiStwDerive[iReChiStw]->SetBinError(i, 0);
 }

 hf->cd();
 plot_ReChiStwDerive[iReChiStw]->Write();
}

void ZWidthDep::DrawReChiStwDeriveMassDep(int bin, double left, double right)
{
 iReChiStwDeriveMassDep++;
 
 TString HistName = (TString)"ReChiStwDeriveMassDep_" + (int)iReChiStwDeriveMassDep;
 plot_ReChiStwDeriveMassDep[iReChiStwDeriveMassDep] = new TH1D(HistName, HistName, bin, left, right);
 
 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_ReChiStwDeriveMassDep[iReChiStwDeriveMassDep]->GetBinCenter(i);
   plot_ReChiStwDeriveMassDep[iReChiStwDeriveMassDep]->SetBinContent(i, ReChiStwDerive(0.2315, 0.00001, BinCenter));
   plot_ReChiStwDeriveMassDep[iReChiStwDeriveMassDep]->SetBinError(i, 0);
 }
 
 hf->cd();
 plot_ReChiStwDeriveMassDep[iReChiStwDeriveMassDep]->Write();
}

void ZWidthDep::DrawChiSquareMassDerive(int bin, double left, double right, double DeltaMass)
{
 iChiSquare++;

 TString HistName = (TString)"ChiSquareMassDerive_" + (int)iChiSquare;
 plot_ChiSquareMassDerive[iChiSquare] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_ChiSquareMassDerive[iChiSquare]->GetBinCenter(i);
   plot_ChiSquareMassDerive[iChiSquare]->SetBinContent(i, ChiSquareMassDerive(BinCenter, DeltaMass));
   plot_ChiSquareMassDerive[iChiSquare]->SetBinError(i, 0);
 }

 hf->cd();
 plot_ChiSquareMassDerive[iChiSquare]->Write();
}

void ZWidthDep::DrawChiSquareStwDerive(int bin, double left, double right, double DeltaStw, double mass)
{
 iChiSquareStw++;

// TString HistName = (TString)"ChiSquareStwDerive_Delta" + (double)DeltaStw + (TString)"_Mass" + (double)mass;
 TString HistName = (TString)"ChiSquareStwDerive_Mass" + (double)mass;
 plot_ChiSquareStwDerive[iReChiStw] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_ChiSquareStwDerive[iChiSquareStw]->GetBinCenter(i);
   plot_ChiSquareStwDerive[iChiSquareStw]->SetBinContent(i, ChiSquareStwDerive(BinCenter, DeltaStw, mass));
   plot_ChiSquareStwDerive[iChiSquareStw]->SetBinError(i, 0);
 }

 hf->cd();
 plot_ChiSquareStwDerive[iChiSquareStw]->Write();
}

void ZWidthDep::DrawChiSquareStwDeriveMassDep(int bin, double left, double right)
{
 iChiSquareStwDeriveMassDep++;

 TString HistName = (TString)"ChiSquareStwDeriveMassDep_" + (int)iChiSquareStwDeriveMassDep;
 plot_ChiSquareStwDeriveMassDep[iChiSquareStwDeriveMassDep] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_ChiSquareStwDeriveMassDep[iChiSquareStwDeriveMassDep]->GetBinCenter(i);
   plot_ChiSquareStwDeriveMassDep[iChiSquareStwDeriveMassDep]->SetBinContent(i, ChiSquareStwDerive(0.2315, 0.00001, BinCenter));
   plot_ChiSquareStwDeriveMassDep[iChiSquareStwDeriveMassDep]->SetBinError(i, 0);
 }

 hf->cd();
 plot_ChiSquareStwDeriveMassDep[iChiSquareStwDeriveMassDep]->Write();
}

void ZWidthDep::DrawA41MassDerive(int bin, double left, double right, double DeltaMass)
{
 iA41++;

 TString HistName = (TString)"A41MassDerive_" + (int)iA41;
 plot_A41MassDerive[iA41] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_A41MassDerive[iA41]->GetBinCenter(i);
   plot_A41MassDerive[iA41]->SetBinContent(i, A41MassDerive(BinCenter, DeltaMass));
   plot_A41MassDerive[iA41]->SetBinError(i, 0);
 }

 hf->cd();
 plot_A41MassDerive[iA41]->Write();
}

void ZWidthDep::DrawA41StwDeriveMassDep(int bin, double left, double right)
{
 iA41StwDeriveMassDep++;

 TString HistName = (TString)"A41StwDeriveMassDep_" + (int)iA41StwDeriveMassDep;
 plot_A41StwDeriveMassDep[iA41StwDeriveMassDep] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_A41StwDeriveMassDep[iA41StwDeriveMassDep]->GetBinCenter(i);
   plot_A41StwDeriveMassDep[iA41StwDeriveMassDep]->SetBinContent(i, A41StwDerive(0.2315, 0.00001, BinCenter));
   plot_A41StwDeriveMassDep[iA41StwDeriveMassDep]->SetBinError(i, 0);
 }

 hf->cd();
 plot_A41StwDeriveMassDep[iA41StwDeriveMassDep]->Write();
}

void ZWidthDep::DrawA42MassDerive(int bin, double left, double right, double DeltaMass)
{
 iA42++;

 TString HistName = (TString)"A42MassDerive_" + (int)iA42;
 plot_A42MassDerive[iA41] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_A42MassDerive[iA42]->GetBinCenter(i);
   plot_A42MassDerive[iA42]->SetBinContent(i, A42MassDerive(BinCenter, DeltaMass));
   plot_A42MassDerive[iA42]->SetBinError(i, 0);
 }

 hf->cd();
 plot_A42MassDerive[iA42]->Write();
}

void ZWidthDep::DrawA42StwDeriveMassDep(int bin, double left, double right)
{
 iA42StwDeriveMassDep++;
 
 TString HistName = (TString)"A42StwDeriveMassDep_" + (int)iA42StwDeriveMassDep;
 plot_A42StwDeriveMassDep[iA42StwDeriveMassDep] = new TH1D(HistName, HistName, bin, left, right);
 
 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_A42StwDeriveMassDep[iA42StwDeriveMassDep]->GetBinCenter(i);
   plot_A42StwDeriveMassDep[iA42StwDeriveMassDep]->SetBinContent(i, A42StwDerive(0.2315, 0.00001, BinCenter));
   plot_A42StwDeriveMassDep[iA42StwDeriveMassDep]->SetBinError(i, 0);
 }

 hf->cd();
 plot_A42StwDeriveMassDep[iA42StwDeriveMassDep]->Write();
}

void ZWidthDep::DrawAFB(int bin, double left, double right, TString flag)
{
 iAFB++;

 TString HistName = (TString)"AFB_"  + (int)iAFB;
 plot_AFB[iAFB] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_AFB[iAFB]->GetBinCenter(i);
   plot_AFB[iAFB]->SetBinContent(i, CalAFB(BinCenter, flag));
   plot_AFB[iAFB]->SetBinError(i, 0);
 }

 hf->cd();
 plot_AFB[iAFB]->Write();
}

void ZWidthDep::DrawAFBStw(int bin, double left, double right, double mass, TString flag)
{
 iAFBStw++;

 TString HistName = (TString)"AFBStw_"  + (int)iAFBStw;
 plot_AFBStw[iAFBStw] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_AFBStw[iAFBStw]->GetBinCenter(i);
   InputStw(BinCenter);
   plot_AFBStw[iAFBStw]->SetBinContent(i, CalAFB(mass, flag));
   plot_AFBStw[iAFBStw]->SetBinError(i, 0);
 }

 hf->cd();
 plot_AFBStw[iAFBStw]->Write();
}

void ZWidthDep::DrawAFBMassDerive(int bin, double left, double right, double DeltaMass)
{
 iAFBMassDerive++;

 TString HistName = (TString)"AFBMassDerive_" + (int)iAFBMassDerive;
 plot_AFBMassDerive[iAFBMassDerive] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_AFBMassDerive[iAFBMassDerive]->GetBinCenter(i);
   plot_AFBMassDerive[iAFBMassDerive]->SetBinContent(i, AFBMassDerive(BinCenter, DeltaMass));
   plot_AFBMassDerive[iAFBMassDerive]->SetBinError(i, 0);
 }

 hf->cd();
 plot_AFBMassDerive[iAFBMassDerive]->Write();
}

void ZWidthDep::DrawAFBStwDeriveMassDep(int bin, double left, double right, TString flag)
{
 iAFBStwDeriveMassDep++;
 
 TString HistName = (TString)"AFBStwDeriveMassDep_" + (int)iAFBStwDeriveMassDep;
 plot_AFBStwDeriveMassDep[iAFBStwDeriveMassDep] = new TH1D(HistName, HistName, bin, left, right);
 
 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_AFBStwDeriveMassDep[iAFBStwDeriveMassDep]->GetBinCenter(i);
   plot_AFBStwDeriveMassDep[iAFBStwDeriveMassDep]->SetBinContent(i, AFBStwDerive(0.2315, 0.00001, BinCenter, flag));
   plot_AFBStwDeriveMassDep[iAFBStwDeriveMassDep]->SetBinError(i, 0);
 }
 
 hf->cd();
 plot_AFBStwDeriveMassDep[iAFBStwDeriveMassDep]->Write();
}

void ZWidthDep::DrawAFBStwDerive(int bin, double left, double right, double DeltaStw, double mass, TString flag)
{
 iAFBStwDerive++;

// TString HistName = (TString)"AFBStwDerive_Delta" + (double)DeltaStw + (TString)"_Mass" + (double)mass;
 TString HistName = (TString)"AFBStwDerive_Mass" + (double)mass;
 plot_AFBStwDerive[iAFBStwDerive] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_AFBStwDerive[iAFBStwDerive]->GetBinCenter(i);
   plot_AFBStwDerive[iAFBStwDerive]->SetBinContent(i, AFBStwDerive(BinCenter, DeltaStw, mass, flag));
   plot_AFBStwDerive[iAFBStwDerive]->SetBinError(i, 0);
 }

 hf->cd();
 plot_AFBStwDerive[iAFBStwDerive]->Write();
}

void ZWidthDep::DrawAFBMassStwDeriveMassDep(int bin, double left, double right, double stw)
{
 iAFBMassStwDeriveMassDep++;

 TString HistName = (TString)"AFBMassStwDeriveMassDep_" + (int)iAFBMassStwDeriveMassDep;
 plot_AFBMassStwDeriveMassDep[iAFBMassStwDeriveMassDep] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_AFBMassStwDeriveMassDep[iAFBMassStwDeriveMassDep]->GetBinCenter(i);
   plot_AFBMassStwDeriveMassDep[iAFBMassStwDeriveMassDep]->SetBinContent(i, AFBMassStwDerive(BinCenter, 0.1, stw, 0.00001));
   plot_AFBMassStwDeriveMassDep[iAFBMassStwDeriveMassDep]->SetBinError(i, 0);
 }

 hf->cd();
 plot_AFBMassStwDeriveMassDep[iAFBMassStwDeriveMassDep]->Write();

}

void ZWidthDep::DrawA4(int bin, double left, double right)
{
 iA4++;

 TString HistName = (TString)"A4_" + (int)iA4;
 plot_A4[iA4] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_A4[iA4]->GetBinCenter(i);
   plot_A4[iA4]->SetBinContent(i, CalA4(BinCenter));
   plot_A4[iA4]->SetBinError(i, 0);
 }

 hf->cd();
 plot_A4[iA4]->Write();
}

void ZWidthDep::DrawL0(int bin, double left, double right)
{
 iL0++;

 TString HistName = (TString)"L0_" + (int)iL0;
 plot_L0[iL0] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_L0[iL0]->GetBinCenter(i);
   plot_L0[iL0]->SetBinContent(i, CalL0(BinCenter));
   plot_L0[iL0]->SetBinError(i, 0);
 }

 hf->cd();
 plot_L0[iL0]->Write();
}

void ZWidthDep::DrawDeltaO(int bin, double left, double right)
{
 iDeltaO++;

 TString HistName = (TString)"DeltaO_" + (int)iDeltaO;
 plot_DeltaO[iDeltaO] = new TH1D(HistName, HistName, bin, left, right);

 for(int i = 1; i <= bin; i++){
   double BinCenter = plot_DeltaO[iDeltaO]->GetBinCenter(i);
   plot_DeltaO[iDeltaO]->SetBinContent(i, CalAFB(90.0 - BinCenter) - CalAFB(90.0 + BinCenter));
   plot_DeltaO[iDeltaO]->SetBinError(i, 0);
 }

 hf->cd();
 plot_DeltaO[iDeltaO]->Write();
}

void ZWidthDep::DrawAFBCurve(double left, double right)
{
 iAFBCurve++;

 TString HistName = (TString)"AFBCurve_" + (int)iAFBCurve;
 plot_AFBCurve[iAFBCurve] = new TF1(HistName, "CalAFBCurve(x)", left, right);

 hf->cd();
 plot_AFBCurve[iAFBCurve]->Write();
}

void ZWidthDep::SaveFile()
{
 hf->Close();
}
