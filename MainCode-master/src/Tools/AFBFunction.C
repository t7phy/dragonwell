#ifndef AFBFunction_cxx
#define AFBFunction_cxx

#include "TH1D.h"
#include "Tools/Tools.h"

void AFBFunction(TH1D* FZmass, TH1D* BZmass, TH1D* &Draw_AFB)
{
 if(!Draw_AFB){
   Draw_AFB = (TH1D *)FZmass->Clone("h1");
   Draw_AFB->Reset();
 }

 double Nf, Nb, AFB, NfError, NbError, AFBError;

 for(int ibin = 0; ibin < FZmass->GetNbinsX(); ibin++){
   Nf = FZmass->GetBinContent(ibin + 1);
   Nb = BZmass->GetBinContent(ibin + 1);
   if(fabs(Nf + Nb) < 1e-10) continue;
   if(Nf < 1e-10) continue;
   if(Nb < 1e-10) continue;

   AFB = (Nf - Nb) / (Nf + Nb);

   NfError = FZmass->GetBinError(ibin + 1);
   NbError = BZmass->GetBinError(ibin + 1);
   AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));

   Draw_AFB->SetBinContent(ibin + 1, AFB);
   Draw_AFB->SetBinError(ibin + 1, AFBError);
 }

}

void AFBFunction(TH2D* FZmass, TH2D* BZmass, TH2D* &Draw_AFB)
{
 if(!Draw_AFB){
   Draw_AFB = (TH2D *)FZmass->Clone("h1");
   Draw_AFB->Reset();
 }

 double Nf, Nb, AFB, NfError, NbError, AFBError;

 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){
     Nf = FZmass->GetBinContent(ibinx + 1, ibiny + 1);
     Nb = BZmass->GetBinContent(ibinx + 1, ibiny + 1);
     if(fabs(Nf + Nb) < 1e-10) continue;
     if(Nf < 1e-10) continue;
     if(Nb < 1e-10) continue;

     AFB = (Nf - Nb) / (Nf + Nb);

     NfError = FZmass->GetBinError(ibinx + 1, ibiny + 1);
     NbError = BZmass->GetBinError(ibinx + 1, ibiny + 1);
     AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));

     Draw_AFB->SetBinContent(ibinx + 1, ibiny + 1, AFB);
     Draw_AFB->SetBinError(ibinx + 1, ibiny + 1, AFBError);
   }
 }
}

void AFBFunction(TH3D* FZmass, TH3D* BZmass, TH3D* &Draw_AFB)
{
 if(!Draw_AFB){
   Draw_AFB = (TH3D *)FZmass->Clone("h1");
   Draw_AFB->Reset();
 }

 double Nf, Nb, AFB, NfError, NbError, AFBError;

 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){
     for(int ibinz = 0; ibinz < FZmass->GetNbinsZ(); ibinz++){
       Nf = FZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);
       Nb = BZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);
       if(fabs(Nf + Nb) < 1e-10) continue;
       if(Nf < 1e-10) continue;
       if(Nb < 1e-10) continue;

       AFB = (Nf - Nb) / (Nf + Nb);

       NfError = FZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);
       NbError = BZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);
       AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));

       Draw_AFB->SetBinContent(ibinx + 1, ibiny + 1, ibinz + 1, AFB);
       Draw_AFB->SetBinError(ibinx + 1, ibiny + 1, ibinz + 1, AFBError);
     }
   }
 }
}

void GetAFBDiff(TH1D* AFB, TH1D* &AFBDiff)
{
 if(!AFBDiff){
   AFBDiff = new TH1D(AFB->GetName() + (TString)"_Diff", AFB->GetName() + (TString)"_Diff", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2);
 }

 if(AFB->GetNbinsX() != AFBDiff->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH1D* tmpAFBDiff = new TH1D(AFB->GetName() + (TString)"_Diff_tmp", AFB->GetName() + (TString)"_Diff_tmp", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2);

 for(int ibin = 1; ibin <= tmpAFBDiff->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = tmpAFBDiff->GetNbinsX() * 2 - (ibin - 1);

   double Diff = AFB->GetBinContent(FirstBin) - AFB->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB->GetBinError(FirstBin) * AFB->GetBinError(FirstBin) + AFB->GetBinError(LastBin) * AFB->GetBinError(LastBin));

   tmpAFBDiff->SetBinContent(ibin, Diff);
   tmpAFBDiff->SetBinError(ibin, DiffErr);
 }

 InverseHistXaxis(tmpAFBDiff, AFBDiff);

}

void GetAFBDiff(TH1D* AFB, TH1D* &AFBDiff, TH1D* &AFBDiff_ZPole, TH1D* &AFBDiff_Side)
{
 if(!AFBDiff){
   AFBDiff = new TH1D(AFB->GetName() + (TString)"_Diff", AFB->GetName() + (TString)"_Diff", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2);
 }

 if(!AFBDiff_ZPole){
   AFBDiff_ZPole = new TH1D(AFB->GetName() + (TString)"_Diff_ZPole", AFB->GetName() + (TString)"_Diff_ZPole", 5, 1, 5);
 }

 if(!AFBDiff_Side){
   AFBDiff_Side = new TH1D(AFB->GetName() + (TString)"_Diff_Side", AFB->GetName() + (TString)"_Diff_Side", 10, 1, 10);
 }


 if(AFB->GetNbinsX() != AFBDiff->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH1D* tmpAFBDiff = new TH1D(AFB->GetName() + (TString)"_Diff_tmp", AFB->GetName() + (TString)"_Diff_tmp", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2);

 for(int ibin = 1; ibin <= tmpAFBDiff->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = tmpAFBDiff->GetNbinsX() * 2 - (ibin - 1);

   double Diff = AFB->GetBinContent(FirstBin) - AFB->GetBinContent(LastBin);
   double DiffErr = sqrt(AFB->GetBinError(FirstBin) * AFB->GetBinError(FirstBin) + AFB->GetBinError(LastBin) * AFB->GetBinError(LastBin));

   if(ibin <= 10){
     AFBDiff_Side->SetBinContent(ibin, Diff);
     AFBDiff_Side->SetBinError(ibin, DiffErr);
   }
   else{
     AFBDiff_ZPole->SetBinContent(ibin - 10, Diff);
     AFBDiff_ZPole->SetBinError(ibin - 10, DiffErr);
   }

   tmpAFBDiff->SetBinContent(ibin, Diff);
   tmpAFBDiff->SetBinError(ibin, DiffErr);
 }

 InverseHistXaxis(tmpAFBDiff, AFBDiff);

}

void GetAFBDiff(TH2D* AFB, TH2D* &AFBDiff)
{
 if(!AFBDiff){
   AFBDiff = new TH2D(AFB->GetName() + (TString)"_Diff", AFB->GetName() + (TString)"_Diff", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2, AFB->GetNbinsY(), 1, AFB->GetNbinsY());
 }

 if(AFB->GetNbinsX() != AFBDiff->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH2D* tmpAFBDiff = new TH2D(AFB->GetName() + (TString)"_Diff_tmp", AFB->GetName() + (TString)"_Diff_tmp", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2, AFB->GetNbinsY(), 1, AFB->GetNbinsY());

 for(int ibiny = 1; ibiny <= tmpAFBDiff->GetNbinsY(); ibiny++){
   for(int ibinx = 1; ibinx <= tmpAFBDiff->GetNbinsX(); ibinx++){
     int FirstBin = ibinx;
     int LastBin = tmpAFBDiff->GetNbinsX() * 2 - (ibinx - 1);

     double Diff = AFB->GetBinContent(FirstBin, ibiny) - AFB->GetBinContent(LastBin, ibiny);
     double DiffErr = sqrt(AFB->GetBinError(FirstBin, ibiny) * AFB->GetBinError(FirstBin, ibiny) + AFB->GetBinError(LastBin, ibiny) * AFB->GetBinError(LastBin, ibiny));

     tmpAFBDiff->SetBinContent(ibinx, ibiny, Diff);
     tmpAFBDiff->SetBinError(ibinx, ibiny, DiffErr);
   }
 }

 InverseHistXaxis(tmpAFBDiff, AFBDiff);

 delete tmpAFBDiff;
}

void GetAFBSlopeAndOffset(TH2D* AFB, TH1D* &AFBSlope, TH1D* &AFBOffset)
{
 if(!AFBSlope){
   AFBSlope = new TH1D(AFB->GetName() + (TString)"_SlopeZY", AFB->GetName() + (TString)"_SlopeZY", AFB->GetNbinsY(), 1, AFB->GetNbinsY());
 }
 if(!AFBOffset){
   AFBOffset = new TH1D(AFB->GetName() + (TString)"_OffsetZY", AFB->GetName() + (TString)"_OffsetZY", AFB->GetNbinsY(), 1, AFB->GetNbinsY());
 }
 
 for(int ibiny = 1; ibiny <= AFB->GetNbinsY(); ibiny++){
   TH1D *AFBMass = new TH1D(AFB->GetName() + (TString)"_Mass_tmp", AFB->GetName() + (TString)"_Mass_tmp", AFB->GetNbinsX(), AFB->GetXaxis()->GetBinLowEdge(1), AFB->GetXaxis()->GetBinUpEdge(AFB->GetNbinsX()));

   for(int ibinx = 1; ibinx <= AFB->GetNbinsX(); ibinx++){
     AFBMass->SetBinContent(ibinx, AFB->GetBinContent(ibinx, ibiny));
     AFBMass->SetBinError(ibinx, AFB->GetBinError(ibinx, ibiny));
   }

   double xbins1[11] = {80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
   AFBMass = (TH1D *)AFBMass->Rebin(10, "AFBMass_80_100", xbins1);

   TF1 *Slope;
   double *par = new double[2];
   double *parErr = new double[2];
   LinearFitting(AFBMass, Slope, par, parErr);
   AFBSlope->SetBinContent(ibiny, par[0]);
   AFBSlope->SetBinError(ibiny, parErr[0]);
   AFBOffset->SetBinContent(ibiny, par[1]);
   AFBOffset->SetBinError(ibiny, parErr[1]);

   delete AFBMass;
   delete Slope;
 }
}

void GetAFBAve(TH1D* AFB, TH1D* &AFBAve)
{
 if(!AFBAve){
   AFBAve = new TH1D(AFB->GetName() + (TString)"_Ave", AFB->GetName() + (TString)"_Ave", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2);
 }

 if(AFB->GetNbinsX() != AFBAve->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH1D* tmpAFBAve = new TH1D(AFB->GetName() + (TString)"_Ave_tmp", AFB->GetName() + (TString)"_Ave_tmp", AFB->GetNbinsX() / 2, 1, AFB->GetNbinsX() / 2);

 for(int ibin = 1; ibin <= tmpAFBAve->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = tmpAFBAve->GetNbinsX() * 2 - (ibin - 1);

   double Ave = (AFB->GetBinContent(FirstBin) + AFB->GetBinContent(LastBin)) / 2;
   double AveErr = sqrt(AFB->GetBinError(FirstBin) * AFB->GetBinError(FirstBin) + AFB->GetBinError(LastBin) * AFB->GetBinError(LastBin)) / 2;

   tmpAFBAve->SetBinContent(ibin, Ave);
   tmpAFBAve->SetBinError(ibin, AveErr);
 }

 InverseHistXaxis(tmpAFBAve, AFBAve);

}

void AFBFraction(TH1D* uuAFB, TH1D* ddAFB, vector<TH1D *> Xsec, TH1D* &Fraction)
{
 if(!Fraction){
   Fraction = new TH1D(uuAFB->GetName() + (TString)"_Fraction", uuAFB->GetName() + (TString)"_Diff", uuAFB->GetNbinsX() / 2, 1, uuAFB->GetNbinsX() / 2);
 }

 if(uuAFB->GetNbinsX() != Fraction->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH1D* ccAFB = uuAFB;
 TH1D* ssAFB = ddAFB;
 TH1D* bbAFB = ddAFB;
 TH1D* uuXsec = Xsec.at(0);
 TH1D* ddXsec = Xsec.at(1);
 TH1D* ssXsec = Xsec.at(2);
 TH1D* ccXsec = Xsec.at(3);
 TH1D* bbXsec = Xsec.at(4);

 TH1D* tmpFraction = new TH1D(uuAFB->GetName() + (TString)"_Fraction_tmp", uuAFB->GetName() + (TString)"_Fraction_tmp", uuAFB->GetNbinsX() / 2, 1, uuAFB->GetNbinsX() / 2);

 for(int ibin = 1; ibin <= tmpFraction->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = tmpFraction->GetNbinsX() * 2 - (ibin - 1);

   double uuAFB1 = uuAFB->GetBinContent(FirstBin);
   double ddAFB1 = ddAFB->GetBinContent(FirstBin);
   double ssAFB1 = ssAFB->GetBinContent(FirstBin);
   double ccAFB1 = ccAFB->GetBinContent(FirstBin);
   double bbAFB1 = bbAFB->GetBinContent(FirstBin);

   double uuAFB2 = uuAFB->GetBinContent(LastBin);
   double ddAFB2 = ddAFB->GetBinContent(LastBin);
   double ssAFB2 = ssAFB->GetBinContent(LastBin);
   double ccAFB2 = ccAFB->GetBinContent(LastBin);
   double bbAFB2 = bbAFB->GetBinContent(LastBin);

   double uuXsec1 = uuXsec->GetBinContent(FirstBin);
   double ddXsec1 = ddXsec->GetBinContent(FirstBin);
   double ssXsec1 = ssXsec->GetBinContent(FirstBin);
   double ccXsec1 = ccXsec->GetBinContent(FirstBin);
   double bbXsec1 = bbXsec->GetBinContent(FirstBin);

   double uuXsec2 = uuXsec->GetBinContent(LastBin);
   double ddXsec2 = ddXsec->GetBinContent(LastBin);
   double ssXsec2 = ssXsec->GetBinContent(LastBin);
   double ccXsec2 = ccXsec->GetBinContent(LastBin);
   double bbXsec2 = bbXsec->GetBinContent(LastBin);

   double Ru1 = (uuAFB1 * uuXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Ru2 = (uuAFB2 * uuXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rd1 = (ddAFB1 * ddXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rd2 = (ddAFB2 * ddXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rs1 = (ssAFB1 * ssXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rs2 = (ssAFB2 * ssXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rc1 = (ccAFB1 * ccXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rc2 = (ccAFB2 * ccXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rb1 = (bbAFB1 * bbXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rb2 = (bbAFB2 * bbXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);

   double Value = (Ru1 - Rd1 - Ru2 + Rd2) / (Ru1 + Rd1 + Rs1 + Rc1 + Rb1 - Ru2 - Rd2 - Rs2 - Rc2 - Rb2);

   tmpFraction->SetBinContent(ibin, Value);
   tmpFraction->SetBinError(ibin, 0);
 }

 InverseHistXaxis(tmpFraction, Fraction);

 delete tmpFraction;
}

///////////////////////////////////
//     Function AFBS0Fraction    //
//  The number applied on Slope  //
///////////////////////////////////

void AFBS0Fraction(TH1D* uuAFB, TH1D* ddAFB, vector<TH1D *> Xsec, TH1D* &Fraction)
{
 if(!Fraction){
   Fraction = new TH1D(uuAFB->GetName() + (TString)"_Fraction", uuAFB->GetName() + (TString)"_Diff", uuAFB->GetNbinsX() / 2, 1, uuAFB->GetNbinsX() / 2);
 }

 if(uuAFB->GetNbinsX() != Fraction->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH1D* ccAFB = uuAFB;
 TH1D* ssAFB = ddAFB;
 TH1D* bbAFB = ddAFB;
 TH1D* uuXsec = Xsec.at(0);
 TH1D* ddXsec = Xsec.at(1);
 TH1D* ssXsec = Xsec.at(2);
 TH1D* ccXsec = Xsec.at(3);
 TH1D* bbXsec = Xsec.at(4);

 TH1D* tmpFraction = new TH1D(uuAFB->GetName() + (TString)"_S0Fraction_tmp", uuAFB->GetName() + (TString)"_S0Fraction_tmp", uuAFB->GetNbinsX() / 2, 1, uuAFB->GetNbinsX() / 2);

 for(int ibin = 1; ibin <= tmpFraction->GetNbinsX(); ibin++){
   int FirstBin = ibin;
   int LastBin = tmpFraction->GetNbinsX() * 2 - (ibin - 1);

   double uuAFB1 = uuAFB->GetBinContent(FirstBin);
   double ddAFB1 = ddAFB->GetBinContent(FirstBin);
   double ssAFB1 = ssAFB->GetBinContent(FirstBin);
   double ccAFB1 = ccAFB->GetBinContent(FirstBin);
   double bbAFB1 = bbAFB->GetBinContent(FirstBin);

   double uuAFB2 = uuAFB->GetBinContent(LastBin);
   double ddAFB2 = ddAFB->GetBinContent(LastBin);
   double ssAFB2 = ssAFB->GetBinContent(LastBin);
   double ccAFB2 = ccAFB->GetBinContent(LastBin);
   double bbAFB2 = bbAFB->GetBinContent(LastBin);

   double uuXsec1 = uuXsec->GetBinContent(FirstBin);
   double ddXsec1 = ddXsec->GetBinContent(FirstBin);
   double ssXsec1 = ssXsec->GetBinContent(FirstBin);
   double ccXsec1 = ccXsec->GetBinContent(FirstBin);
   double bbXsec1 = bbXsec->GetBinContent(FirstBin);

   double uuXsec2 = uuXsec->GetBinContent(LastBin);
   double ddXsec2 = ddXsec->GetBinContent(LastBin);
   double ssXsec2 = ssXsec->GetBinContent(LastBin);
   double ccXsec2 = ccXsec->GetBinContent(LastBin);
   double bbXsec2 = bbXsec->GetBinContent(LastBin);

   double Ru1 = (uuAFB1 * uuXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Ru2 = (uuAFB2 * uuXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rd1 = (ddAFB1 * ddXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rd2 = (ddAFB2 * ddXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rs1 = (ssAFB1 * ssXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rs2 = (ssAFB2 * ssXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rc1 = (ccAFB1 * ccXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rc2 = (ccAFB2 * ccXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
   double Rb1 = (bbAFB1 * bbXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
   double Rb2 = (bbAFB2 * bbXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);

   double Value = (Ru1 + Rd1 - Ru2 - Rd2) / (Ru1 + Rd1 + Rs1 + Rc1 + Rb1 - Ru2 - Rd2 - Rs2 - Rc2 - Rb2);

   tmpFraction->SetBinContent(ibin, Value);
   tmpFraction->SetBinError(ibin, 0);
 }

 InverseHistXaxis(tmpFraction, Fraction);

 delete tmpFraction;
}

void AFBS0Fraction(TH2D* uuAFB, TH2D* ddAFB, vector<TH2D *> Xsec, TH2D* &Fraction)
{
 if(!Fraction){
   Fraction = new TH2D(uuAFB->GetName() + (TString)"_Fraction", uuAFB->GetName() + (TString)"_Diff", uuAFB->GetNbinsX() / 2, 1, uuAFB->GetNbinsX() / 2, uuAFB->GetNbinsY(), 1, uuAFB->GetNbinsY());
 }

 if(uuAFB->GetNbinsX() != Fraction->GetNbinsX() * 2){
   cout<<"ERROR: binning not match"<<endl;
   return;
 }

 TH2D* ccAFB = uuAFB;
 TH2D* ssAFB = ddAFB;
 TH2D* bbAFB = ddAFB;
 TH2D* uuXsec = Xsec.at(0);
 TH2D* ddXsec = Xsec.at(1);
 TH2D* ssXsec = Xsec.at(2);
 TH2D* ccXsec = Xsec.at(3);
 TH2D* bbXsec = Xsec.at(4);

 TH2D* tmpFraction = new TH2D(uuAFB->GetName() + (TString)"_S0Fraction_tmp", uuAFB->GetName() + (TString)"_S0Fraction_tmp", uuAFB->GetNbinsX() / 2, 1, uuAFB->GetNbinsX() / 2, uuAFB->GetNbinsY(), 1, uuAFB->GetNbinsY());

 for(int ibiny = 1; ibiny <= tmpFraction->GetNbinsY(); ibiny++){
   for(int ibinx = 1; ibinx <= tmpFraction->GetNbinsX(); ibinx++){
     int FirstBin = ibinx;
     int LastBin = tmpFraction->GetNbinsX() * 2 - (ibinx - 1);

     double uuAFB1 = uuAFB->GetBinContent(FirstBin, ibiny);
     double ddAFB1 = ddAFB->GetBinContent(FirstBin, ibiny);
     double ssAFB1 = ssAFB->GetBinContent(FirstBin, ibiny);
     double ccAFB1 = ccAFB->GetBinContent(FirstBin, ibiny);
     double bbAFB1 = bbAFB->GetBinContent(FirstBin, ibiny);

     double uuAFB2 = uuAFB->GetBinContent(LastBin, ibiny);
     double ddAFB2 = ddAFB->GetBinContent(LastBin, ibiny);
     double ssAFB2 = ssAFB->GetBinContent(LastBin, ibiny);
     double ccAFB2 = ccAFB->GetBinContent(LastBin, ibiny);
     double bbAFB2 = bbAFB->GetBinContent(LastBin, ibiny);

     double uuXsec1 = uuXsec->GetBinContent(FirstBin, ibiny);
     double ddXsec1 = ddXsec->GetBinContent(FirstBin, ibiny);
     double ssXsec1 = ssXsec->GetBinContent(FirstBin, ibiny);
     double ccXsec1 = ccXsec->GetBinContent(FirstBin, ibiny);
     double bbXsec1 = bbXsec->GetBinContent(FirstBin, ibiny);

     double uuXsec2 = uuXsec->GetBinContent(LastBin, ibiny);
     double ddXsec2 = ddXsec->GetBinContent(LastBin, ibiny);
     double ssXsec2 = ssXsec->GetBinContent(LastBin, ibiny);
     double ccXsec2 = ccXsec->GetBinContent(LastBin, ibiny);
     double bbXsec2 = bbXsec->GetBinContent(LastBin, ibiny);

     double Ru1 = (uuAFB1 * uuXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
     double Ru2 = (uuAFB2 * uuXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
     double Rd1 = (ddAFB1 * ddXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
     double Rd2 = (ddAFB2 * ddXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
     double Rs1 = (ssAFB1 * ssXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
     double Rs2 = (ssAFB2 * ssXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
     double Rc1 = (ccAFB1 * ccXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
     double Rc2 = (ccAFB2 * ccXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);
     double Rb1 = (bbAFB1 * bbXsec1) / (uuXsec1 + ddXsec1 + ssXsec1 + ccXsec1 + bbXsec1);
     double Rb2 = (bbAFB2 * bbXsec2) / (uuXsec2 + ddXsec2 + ssXsec2 + ccXsec2 + bbXsec2);

     double Value = (Ru1 + Rd1 - Ru2 - Rd2) / (Ru1 + Rd1 + Rs1 + Rc1 + Rb1 - Ru2 - Rd2 - Rs2 - Rc2 - Rb2);

     tmpFraction->SetBinContent(ibinx, ibiny, Value);
     tmpFraction->SetBinError(ibinx, ibiny, 0);
   }
 }

 InverseHistXaxis(tmpFraction, Fraction);

 delete tmpFraction;
}

void AFBFunction(TH2D* FZmass, TH2D* BZmass, TH1D* &Draw_AFB)
{
 if(!Draw_AFB){

   int nbinx = FZmass->GetNbinsX();
   double* xbinning = new double[nbinx + 1];
   xbinning[0] = FZmass->GetXaxis()->GetBinLowEdge(1);
   for(int i = 1; i <= nbinx; i++){
     xbinning[i] = FZmass->GetXaxis()->GetBinUpEdge(i);
   }

   Draw_AFB = new TH1D("AFB", "AFB", nbinx, xbinning);
   Draw_AFB->Reset();
 }

 double AFB, AFBError;

 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){

   double Nf = 0;
   double Nb = 0;
   double NfError2 = 0;
   double NbError2 = 0;
   double NfError = 0;
   double NbError = 0;

   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){
     Nf = Nf + FZmass->GetBinContent(ibinx + 1, ibiny + 1);
     Nb = Nb + BZmass->GetBinContent(ibinx + 1, ibiny + 1);

     NfError2 = NfError2 + FZmass->GetBinError(ibinx + 1, ibiny + 1) * FZmass->GetBinError(ibinx + 1, ibiny + 1);
     NbError2 = NbError2 + BZmass->GetBinError(ibinx + 1, ibiny + 1) * BZmass->GetBinError(ibinx + 1, ibiny + 1);
   }
   NfError = sqrt(NfError2);
   NbError = sqrt(NbError2);

   if((Nf + Nb) < 1e-10) continue;

   AFB = (Nf - Nb) / (Nf + Nb);
   AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));

   Draw_AFB->SetBinContent(ibinx + 1, AFB);
   Draw_AFB->SetBinError(ibinx + 1, AFBError);
 }

}

void AFBFunction(TH3D* FZmass, TH3D* BZmass, TH1D* &Draw_AFB)
{
 if(!Draw_AFB){

   int nbinx = FZmass->GetNbinsX();
   double* xbinning = new double[nbinx + 1];
   xbinning[0] = FZmass->GetXaxis()->GetBinLowEdge(1);
   for(int i = 1; i <= nbinx; i++){
     xbinning[i] = FZmass->GetXaxis()->GetBinUpEdge(i);
   }

   Draw_AFB = new TH1D("AFB", "AFB", nbinx, xbinning);
   Draw_AFB->Reset();
 }

 double AFB, AFBError;

 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){

   double Nf = 0;
   double Nb = 0;
   double NfError2 = 0;
   double NbError2 = 0;
   double NfError = 0;
   double NbError = 0;

   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){
     for(int ibinz = 0; ibinz < FZmass->GetNbinsZ(); ibinz++){
       Nf = Nf + FZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);
       Nb = Nb + BZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);

       NfError2 = NfError2 + FZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1) * FZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);
       NbError2 = NbError2 + BZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1) * BZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);
     }
   }
   NfError = sqrt(NfError2);
   NbError = sqrt(NbError2);

   if((Nf + Nb) < 1e-10) continue;

   AFB = (Nf - Nb) / (Nf + Nb);
   AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));

   Draw_AFB->SetBinContent(ibinx + 1, AFB);
   Draw_AFB->SetBinError(ibinx + 1, AFBError);
 }

}

void ApplyS0(TH1D* DeltaD, TH1D* &Dilution, double S0, double S0Error)
{
 if(!Dilution){
   Dilution = (TH1D *)DeltaD->Clone("Dilution");
 }

 for(int ibin = 1; ibin <= DeltaD->GetNbinsX(); ibin++){
   Dilution->SetBinContent(ibin, DeltaD->GetBinContent(ibin) + S0);
   Dilution->SetBinError(ibin, S0Error);
 }
}

void ApplyS0(TH2D* DeltaD, TH2D* &Dilution, double S0, double S0Error)
{
 if(!Dilution){
   Dilution = (TH2D *)DeltaD->Clone("2DDilution");
 }

 for(int ibinx = 1; ibinx <= DeltaD->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= DeltaD->GetNbinsY(); ibiny++){
     Dilution->SetBinContent(ibinx, ibiny, DeltaD->GetBinContent(ibinx, ibiny) + S0);
     Dilution->SetBinError(ibinx, ibiny, S0Error);
   }
 }

}

void ApplyS0(TH2D* DeltaD, TH2D* &Dilution, TH1D* S0)
{
 if(!Dilution){
   Dilution = (TH2D *)DeltaD->Clone("2DDilution");
 }

 for(int ibinx = 1; ibinx <= DeltaD->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= DeltaD->GetNbinsY(); ibiny++){
     Dilution->SetBinContent(ibinx, ibiny, DeltaD->GetBinContent(ibinx, ibiny) + S0->GetBinContent(ibiny));
     Dilution->SetBinError(ibinx, ibiny, S0->GetBinError(ibiny));
   }
 }

}

void ApplyDelta(TH1D* Dilution_MC, TH1D* &Dilution_Data, double Delta)
{
 if(!Dilution_Data){
   Dilution_Data = (TH1D *)Dilution_MC->Clone("Dilution_Data");
 }

 for(int ibin = 1; ibin <= Dilution_MC->GetNbinsX(); ibin++){
   Dilution_Data->SetBinContent(ibin, Dilution_MC->GetBinContent(ibin) + Delta);
   //Dilution_Data->SetBinError(ibin, DeltaError);
 }
}

void ApplyDilution(TH1D* &FZmass, TH1D* &BZmass, TH1D* FDilution, TH1D* BDilution)
{
 for(int ibin = 1; ibin <= FZmass->GetNbinsX(); ibin++){
   double FDilutionFactor = FDilution->GetBinContent(ibin);
   double FDilutionError = FDilution->GetBinError(ibin);

   double BDilutionFactor = BDilution->GetBinContent(ibin);
   double BDilutionError = BDilution->GetBinError(ibin);

   double NF = FZmass->GetBinContent(ibin);
   double NB = BZmass->GetBinContent(ibin);
   double NFError = FZmass->GetBinError(ibin);
   double NBError = BZmass->GetBinError(ibin);

   double FBinContent = FZmass->GetBinContent(ibin) * (1 - FDilutionFactor) + BZmass->GetBinContent(ibin) * BDilutionFactor;
   double BBinContent = BZmass->GetBinContent(ibin) * (1 - BDilutionFactor) + FZmass->GetBinContent(ibin) * FDilutionFactor;

   double FBinError = sqrt(NF * NF * FDilutionError * FDilutionError + (1 - FDilutionFactor) * (1 - FDilutionFactor) * NFError * NFError + BDilutionFactor * BDilutionFactor * NBError * NBError + NB * NB * BDilutionError * BDilutionError);
   double BBinError = sqrt(NB * NB * BDilutionError * BDilutionError + (1 - BDilutionFactor) * (1 - BDilutionFactor) * NBError * NBError + FDilutionFactor * FDilutionFactor * NFError * NFError + NF * NF * FDilutionError * FDilutionError);

   FZmass->SetBinContent(ibin, FBinContent);
   FZmass->SetBinError(ibin, FBinError);
   BZmass->SetBinContent(ibin, BBinContent);
   BZmass->SetBinError(ibin, BBinError);
 }

}

void ApplyDilution(TH1D* &FZmass, TH1D* &BZmass, TH1D* Dilution, bool isGG)
{
 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){
   double DilutionFactor = Dilution->GetBinContent(ibinx + 1);
   double DilutionError = Dilution->GetBinError(ibinx + 1);
   if(isGG){
     DilutionFactor = 0.5;
     DilutionError = 0;
   }

   double FBinContent = FZmass->GetBinContent(ibinx + 1) * (1 - DilutionFactor) + BZmass->GetBinContent(ibinx + 1) * DilutionFactor;
   double BBinContent = BZmass->GetBinContent(ibinx + 1) * (1 - DilutionFactor) + FZmass->GetBinContent(ibinx + 1) * DilutionFactor;

   double NF = FZmass->GetBinContent(ibinx + 1);
   double NB = BZmass->GetBinContent(ibinx + 1);
   double NFError = FZmass->GetBinError(ibinx + 1);
   double NBError = BZmass->GetBinError(ibinx + 1);

   double FBinError = sqrt(NF * NF * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NFError * NFError + DilutionFactor * DilutionFactor * NBError * NBError + NB * NB * DilutionError * DilutionError);
   double BBinError = sqrt(NB * NB * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NBError * NBError + DilutionFactor * DilutionFactor * NFError * NFError + NF * NF * DilutionError * DilutionError);

   FZmass->SetBinContent(ibinx + 1, FBinContent);
   BZmass->SetBinContent(ibinx + 1, BBinContent);
   FZmass->SetBinError(ibinx + 1, FBinError);
   BZmass->SetBinError(ibinx + 1, BBinError);
 }
}

void Apply2DDilution(TH2D* &FZmass, TH2D* &BZmass, TH2D* Dilution, bool isGG, double S0)
{
 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){
     double DilutionFactor = Dilution->GetBinContent(ibinx + 1, ibiny + 1) + S0;
     double DilutionError = Dilution->GetBinError(ibinx + 1, ibiny + 1);
     if(isGG){
       DilutionFactor = 0.5;
       DilutionError = 0;
     }

     double FBinContent = FZmass->GetBinContent(ibinx + 1, ibiny + 1) * (1 - DilutionFactor) + BZmass->GetBinContent(ibinx + 1, ibiny + 1) * DilutionFactor;
     double BBinContent = BZmass->GetBinContent(ibinx + 1, ibiny + 1) * (1 - DilutionFactor) + FZmass->GetBinContent(ibinx + 1, ibiny + 1) * DilutionFactor;

     double NF = FZmass->GetBinContent(ibinx + 1, ibiny + 1);
     double NB = BZmass->GetBinContent(ibinx + 1, ibiny + 1);
     double NFError = FZmass->GetBinError(ibinx + 1, ibiny + 1);
     double NBError = BZmass->GetBinError(ibinx + 1, ibiny + 1);

     double FBinError = sqrt(NF * NF * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NFError * NFError + DilutionFactor * DilutionFactor * NBError * NBError + NB * NB * DilutionError * DilutionError);
     double BBinError = sqrt(NB * NB * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NBError * NBError + DilutionFactor * DilutionFactor * NFError * NFError + NF * NF * DilutionError * DilutionError);

     FZmass->SetBinContent(ibinx + 1, ibiny + 1, FBinContent);
     BZmass->SetBinContent(ibinx + 1, ibiny + 1, BBinContent);
     FZmass->SetBinError(ibinx + 1, ibiny + 1, FBinError);
     BZmass->SetBinError(ibinx + 1, ibiny + 1, BBinError);   
   }
 }
}

void Apply2DDilutionNY(TH2D* &FZmass, TH2D* &BZmass, TH2D* Dilution, bool isGG, vector<double> S0)
{
 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){ 
     double DilutionFactor = Dilution->GetBinContent(ibinx + 1, ibiny + 1) + S0.at(ibiny);
     double DilutionError = Dilution->GetBinError(ibinx + 1, ibiny + 1);
     if(isGG){
       DilutionFactor = 0.5;
       DilutionError = 0;
     }
     
     double FBinContent = FZmass->GetBinContent(ibinx + 1, ibiny + 1) * (1 - DilutionFactor) + BZmass->GetBinContent(ibinx + 1, ibiny + 1) * DilutionFactor;
     double BBinContent = BZmass->GetBinContent(ibinx + 1, ibiny + 1) * (1 - DilutionFactor) + FZmass->GetBinContent(ibinx + 1, ibiny + 1) * DilutionFactor;
     
     double NF = FZmass->GetBinContent(ibinx + 1, ibiny + 1);
     double NB = BZmass->GetBinContent(ibinx + 1, ibiny + 1);
     double NFError = FZmass->GetBinError(ibinx + 1, ibiny + 1);
     double NBError = BZmass->GetBinError(ibinx + 1, ibiny + 1);
     double FBinError = sqrt(NF * NF * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NFError * NFError + DilutionFactor * DilutionFactor * NBError * NBError + NB * NB * DilutionError * DilutionError);
     double BBinError = sqrt(NB * NB * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NBError * NBError + DilutionFactor * DilutionFactor * NFError * NFError + NF * NF * DilutionError * DilutionError);
     
     FZmass->SetBinContent(ibinx + 1, ibiny + 1, FBinContent);
     BZmass->SetBinContent(ibinx + 1, ibiny + 1, BBinContent);
     FZmass->SetBinError(ibinx + 1, ibiny + 1, FBinError);
     BZmass->SetBinError(ibinx + 1, ibiny + 1, BBinError);
   }
 }
}

void Apply3DDilution(TH3D* &FZmass, TH3D* &BZmass, TH3D* Dilution)
{
 for(int ibinx = 0; ibinx < FZmass->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < FZmass->GetNbinsY(); ibiny++){
     for(int ibinz = 0; ibinz < FZmass->GetNbinsZ(); ibinz++){
       double DilutionFactor = Dilution->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);
       double DilutionError = Dilution->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);
       double FBinContent = FZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1) * (1 - DilutionFactor) + BZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1) * DilutionFactor;
       double BBinContent = BZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1) * (1 - DilutionFactor) + FZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1) * DilutionFactor;

       double NF = FZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);
       double NB = BZmass->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);
       double NFError = FZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);
       double NBError = BZmass->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1);

       double FBinError = sqrt(NF * NF * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NFError * NFError + DilutionFactor * DilutionFactor * NBError * NBError + NB * NB * DilutionError * DilutionError);
       double BBinError = sqrt(NB * NB * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NBError * NBError + DilutionFactor * DilutionFactor * NFError * NFError + NF * NF * DilutionError * DilutionError);

       FZmass->SetBinContent(ibinx + 1, ibiny + 1, ibinz + 1, FBinContent);
       BZmass->SetBinContent(ibinx + 1, ibiny + 1, ibinz + 1, BBinContent);
       FZmass->SetBinError(ibinx + 1, ibiny + 1, ibinz + 1, FBinError);
       BZmass->SetBinError(ibinx + 1, ibiny + 1, ibinz + 1, BBinError);
     }
   }
 }
}

void GetAFBDilution(TH1D *Dilution, TH1D* &AFBDilution)
{
 AFBDilution = (TH1D *)Dilution->Clone((TString)"AFB" + Dilution->GetName());
 AFBDilution->Reset();

 for(int ibin = 1; ibin <= Dilution->GetNbinsX(); ibin++){
   double Value = 1 - 2 * Dilution->GetBinContent(ibin);
   double Error = 2 * Dilution->GetBinError(ibin);

   AFBDilution->SetBinContent(ibin, Value);
   AFBDilution->SetBinError(ibin, Error);
 }
}

void GetXsecFraction(TH1D *Numer, vector<TH1D *> Denom, TH1D* &Fraction)
{
 Fraction = (TH1D *)Numer->Clone((TString)"Fraction_" + Numer->GetName());
 Fraction->Reset();

 for(int ibin = 1; ibin <= Numer->GetNbinsX(); ibin++){
   double DenomValue = 0.0;
   double DenomError2 = 0.0;
   double DenomError = 0.0;
   for(int i = 0; i < Denom.size(); i++){
     DenomValue += Denom.at(i)->GetBinContent(ibin);
     DenomError2 += Denom.at(i)->GetBinError(ibin) * Denom.at(i)->GetBinError(ibin);
   }
   DenomError = sqrt(DenomError2);
   double NumerValue = Numer->GetBinContent(ibin);
   double NumerError = Numer->GetBinError(ibin);

   double Value = NumerValue / DenomValue;
   double Error = sqrt((DenomValue - NumerValue) * (DenomValue - NumerValue) * NumerError * NumerError + NumerValue * NumerValue * (NumerError * NumerError + DenomError * DenomError)) / (DenomValue * DenomValue);

   Fraction->SetBinContent(ibin, Value);
   Fraction->SetBinError(ibin, Error);
 }
}

void GetCoefficientDilution(TH1D* Dilution, TH1D* Fraction, TH1D* &CoefficientDilution)
{
 CoefficientDilution = (TH1D *)Dilution->Clone((TString)"Coefficient" + Dilution->GetName());
 CoefficientDilution->Reset();

 for(int ibin = 1; ibin <= Dilution->GetNbinsX(); ibin++){
   double Value1 = 1 - 2 * Dilution->GetBinContent(ibin);
   double Error1 = 2 * Dilution->GetBinError(ibin);
   double Value2 = Fraction->GetBinContent(ibin);
   double Error2 = Fraction->GetBinError(ibin);

   double Value = Value1 * Value2;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2);

   CoefficientDilution->SetBinContent(ibin, Value);
   CoefficientDilution->SetBinError(ibin, Error);
 }

}

void GetCoefficientDilution(TH1D* wrong, TH1D* total, TH1D* all, TH1D* &CoefficientDilution)
{
 CoefficientDilution = (TH1D *)wrong->Clone((TString)"Coefficient" + wrong->GetName());
 CoefficientDilution->Reset();

 TH1D* right = (TH1D *)total->Clone(total->GetName() + (TString)"_right");
 right->Add(wrong, -1);
 TH1D* other = (TH1D *)all->Clone(all->GetName() + (TString)"_other");
 other->Add(total, -1);

 for(int ibin = 1; ibin <= total->GetNbinsX(); ibin++){
   double Value1 = right->GetBinContent(ibin);
   double Error1 = right->GetBinError(ibin);

   double Value2 = wrong->GetBinContent(ibin);
   double Error2 = wrong->GetBinError(ibin);

   double Value3 = other->GetBinContent(ibin);
   double Error3 = other->GetBinError(ibin);

   if(fabs(Value1 + Value2 + Value3) < 1e-10) continue;

   double Value = (Value1 - Value2) / (Value1 + Value2 + Value3);
   double Error = sqrt((2.0 * Value2 + Value3) * (2.0 * Value2 + Value3) * Error1 * Error1 + (2.0 * Value1 + Value3) * (2.0 * Value1 + Value3) * Error2 * Error2 + (Value1 - Value2) * (Value1 - Value2) * Error3 * Error3) / ((Value1 + Value2 + Value3) * (Value1 + Value2 + Value3));

   CoefficientDilution->SetBinContent(ibin, Value);
   CoefficientDilution->SetBinError(ibin, Error);
 }

}

void GetCoefficientDilution(TH3D* wrong, TH3D* total, TH3D* all, TH3D* &CoefficientDilution)
{
 CoefficientDilution = (TH3D *)wrong->Clone((TString)"Coefficient" + wrong->GetName());
 CoefficientDilution->Reset();

 TH3D* right = (TH3D *)total->Clone(total->GetName() + (TString)"_right");
 right->Add(wrong, -1);
 TH3D* other = (TH3D *)all->Clone(all->GetName() + (TString)"_other");
 other->Add(total, -1);

 for(int ibinx = 1; ibinx <= total->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= total->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= total->GetNbinsZ(); ibinz++){
       double Value1 = right->GetBinContent(ibinx, ibiny, ibinz);
       double Error1 = right->GetBinError(ibinx, ibiny, ibinz);

       double Value2 = wrong->GetBinContent(ibinx, ibiny, ibinz);
       double Error2 = wrong->GetBinError(ibinx, ibiny, ibinz);

       double Value3 = other->GetBinContent(ibinx, ibiny, ibinz);
       double Error3 = other->GetBinError(ibinx, ibiny, ibinz);

       if(fabs(Value1 + Value2 + Value3) < 1e-10) continue;

       double Value = (Value1 - Value2) / (Value1 + Value2 + Value3);
       double Error = sqrt((2.0 * Value2 + Value3) * (2.0 * Value2 + Value3) * Error1 * Error1 + (2.0 * Value1 + Value3) * (2.0 * Value1 + Value3) * Error2 * Error2 + (Value1 - Value2) * (Value1 - Value2) * Error3 * Error3) / ((Value1 + Value2 + Value3) * (Value1 + Value2 + Value3));

       CoefficientDilution->SetBinContent(ibinx, ibiny, ibinz, Value);
       CoefficientDilution->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }
}

void GetDilutionAverage(TH1D* Dilution, TH1D* &DilutionAverage, TH1D* &Residual)
{
 int nbin = Dilution->GetNbinsX();
 vector<double> Value;
 vector<double> Error;
 vector<double> BinWidth;
 double MeanError;

 for(int ibin = 1; ibin <= nbin; ibin++){
   Value.push_back(Dilution->GetBinContent(ibin));
   Error.push_back(Dilution->GetBinError(ibin));
   BinWidth.push_back(Dilution->GetXaxis()->GetBinUpEdge(ibin) - Dilution->GetXaxis()->GetBinLowEdge(ibin));
 }

 double Mean = CalculateMean(Value, Error, BinWidth, MeanError);

 DilutionAverage = new TH1D(Dilution->GetName() + (TString)"_Average", Dilution->GetName() + (TString)"_Average", 1, 0, 1);
 DilutionAverage->SetBinContent(1, Mean);
 DilutionAverage->SetBinError(1, MeanError);

 Residual = (TH1D *)Dilution->Clone(Dilution->GetName() + (TString)"_Residual");
 Residual->Reset();

 for(int ibin = 1; ibin <= Dilution->GetNbinsX(); ibin++){
   double Value = Dilution->GetBinContent(ibin) - Mean;
   double Error = Dilution->GetBinError(ibin);

   Residual->SetBinContent(ibin, Value);
   Residual->SetBinError(ibin, Error);
 }

}

void GetDilutionAverage(TH3D* Dilution, TH3D* &DilutionAverage, TH3D* &Residual)
{
 int nbinx = 1;
 double xbinning[2] = {0.0, 1.0};

 int nbiny = Dilution->GetNbinsY();
 double* ybinning = new double[nbiny + 1];
 ybinning[0] = Dilution->GetYaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbiny; i++){
   ybinning[i] = Dilution->GetYaxis()->GetBinUpEdge(i);
 }

 int nbinz = Dilution->GetNbinsZ();
 double* zbinning = new double[nbinz + 1];
 zbinning[0] = Dilution->GetZaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbinz; i++){
   zbinning[i] = Dilution->GetZaxis()->GetBinUpEdge(i);
 }


 DilutionAverage = new TH3D(Dilution->GetName() + (TString)"_Average", Dilution->GetName() + (TString)"_Average", nbinx, xbinning, nbiny, ybinning, nbinz, zbinning);

 Residual = (TH3D *)Dilution->Clone(Dilution->GetName() + (TString)"_Residual");
 Residual->Reset();

 for(int ibiny = 1; ibiny <= Dilution->GetNbinsY(); ibiny++){
   for(int ibinz = 1; ibinz <= Dilution->GetNbinsZ(); ibinz++){
     int nbin = Dilution->GetNbinsX();
     vector<double> Value;
     vector<double> Error;
     vector<double> BinWidth;
     double MeanError = 0.0;
 
     for(int ibinx = 1; ibinx <= nbin; ibinx++){
       Value.push_back(Dilution->GetBinContent(ibinx, ibiny, ibinz));
       Error.push_back(Dilution->GetBinError(ibinx, ibiny, ibinz));
       BinWidth.push_back(Dilution->GetXaxis()->GetBinUpEdge(ibinx) - Dilution->GetXaxis()->GetBinLowEdge(ibinx));
     }
 
     double Mean = CalculateMean(Value, Error, BinWidth, MeanError);
 
     DilutionAverage->SetBinContent(1, ibiny, ibinz, Mean);
     DilutionAverage->SetBinError(1, ibiny, ibinz, MeanError);

     Value.clear();
     Error.clear();
     BinWidth.clear();
 
     for(int ibinx = 1; ibinx <= Dilution->GetNbinsX(); ibinx++){
       double Value = Dilution->GetBinContent(ibinx, ibiny, ibinz) - Mean;
       double Error = Dilution->GetBinError(ibinx, ibiny, ibinz);
   
       Residual->SetBinContent(ibinx, ibiny, ibinz, Value);
       Residual->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }
}

void GetDilutionMeta(TH1D* wrong, TH1D* total, TH1D* all, TH1D* &OneMinusTwoD, TH1D* &RelativeCrossSection)
{
 OneMinusTwoD = (TH1D *)wrong->Clone((TString)"OneMinusTwoD" + wrong->GetName());
 OneMinusTwoD->Reset();
 RelativeCrossSection = (TH1D *)wrong->Clone((TString)"RelativeCrossSection" + wrong->GetName());
 RelativeCrossSection->Reset();

 for(int ibinx = 1; ibinx <= total->GetNbinsX(); ibinx++){
   double Wrong = wrong->GetBinContent(ibinx);
   double WrongError = wrong->GetBinError(ibinx);
   double Total = total->GetBinContent(ibinx);
   double TotalError = total->GetBinError(ibinx);
   double All = all->GetBinContent(ibinx);
   double AllError = all->GetBinError(ibinx);

   double Value1 = 1.0 - 2.0 * Wrong / Total;
   double Error1 = 2.0 * sqrt(WrongError * WrongError * Total * Total + Wrong * Wrong * TotalError * TotalError) / Total / Total;
   double Value2 = Total / All;
   double Error2 = sqrt(Total * Total * AllError * AllError + TotalError * TotalError * All * All) / All / All;

   OneMinusTwoD->SetBinContent(ibinx, Value1);
   OneMinusTwoD->SetBinError(ibinx, Error1);
   RelativeCrossSection->SetBinContent(ibinx, Value2);
   RelativeCrossSection->SetBinError(ibinx, Error2);
 }
}

void GetDilutionMeta(TH3D* wrong, TH3D* total, TH3D* all, TH3D* &OneMinusTwoD, TH3D* &RelativeCrossSection)
{
 OneMinusTwoD = (TH3D *)wrong->Clone((TString)"OneMinusTwoD" + wrong->GetName());
 OneMinusTwoD->Reset();
 RelativeCrossSection = (TH3D *)wrong->Clone((TString)"RelativeCrossSection" + wrong->GetName());
 RelativeCrossSection->Reset();


 for(int ibinx = 1; ibinx <= total->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= total->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= total->GetNbinsZ(); ibinz++){
       double Wrong = wrong->GetBinContent(ibinx, ibiny, ibinz);
       double WrongError = wrong->GetBinError(ibinx, ibiny, ibinz);
       double Total = total->GetBinContent(ibinx, ibiny, ibinz);
       double TotalError = total->GetBinError(ibinx, ibiny, ibinz);
       double All = all->GetBinContent(ibinx, ibiny, ibinz);
       double AllError = all->GetBinError(ibinx, ibiny, ibinz);

       double Value1 = 1.0 - 2.0 * Wrong / Total;
       double Error1 = 2.0 * sqrt(WrongError * WrongError * Total * Total + Wrong * Wrong * TotalError * TotalError) / Total / Total;
       double Value2 = Total / All;
       double Error2 = sqrt(Total * Total * AllError * AllError + TotalError * TotalError * All * All) / All / All;

       OneMinusTwoD->SetBinContent(ibinx, ibiny, ibinz, Value1);
       OneMinusTwoD->SetBinError(ibinx, ibiny, ibinz, Error1);
       RelativeCrossSection->SetBinContent(ibinx, ibiny, ibinz, Value2);
       RelativeCrossSection->SetBinError(ibinx, ibiny, ibinz, Error2);
     }
   }
 }
}

void GetHadronAFB(TH1D* AFB_uu, TH1D* AFB_dd, TH1D* Dilution_uu, TH1D* Dilution_dd, TH1D* &AFB)
{
 if(!AFB){
   AFB = (TH1D *)AFB_uu->Clone(AFB_uu->GetName() + (TString)"_Hadron");
 }

 for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
   double Value1 = Dilution_uu->GetBinContent(ibin);
   double Value2 = AFB_uu->GetBinContent(ibin);
   double Value3 = Dilution_dd->GetBinContent(ibin);
   double Value4 = AFB_dd->GetBinContent(ibin);

   double Error1 = Dilution_uu->GetBinError(ibin);
   double Error2 = AFB_uu->GetBinError(ibin);
   double Error3 = Dilution_dd->GetBinError(ibin);
   double Error4 = AFB_dd->GetBinError(ibin);

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB->SetBinContent(ibin, Value);
   AFB->SetBinError(ibin, Error);
   cout<<Value1<<" "<<Value2<<" "<<Value3<<" "<<Value4<<" "<<Value<<endl;
 }
}

void GetHadronAFB(TH1D* AFB_uu, TH1D* AFB_dd, TH1D* Delta_uu, TH1D* Delta_dd, double P0u, double P0d, TH1D* &AFB)
{
 if(!AFB){
   AFB = (TH1D *)AFB_uu->Clone(AFB_uu->GetName() + (TString)"_Hadron");
 }

 for(int ibin = 1; ibin <= AFB_uu->GetNbinsX(); ibin++){
   double Value1 = Delta_uu->GetBinContent(ibin) + P0u;
   double Value2 = AFB_uu->GetBinContent(ibin);
   double Value3 = Delta_dd->GetBinContent(ibin) + P0d;
   double Value4 = AFB_dd->GetBinContent(ibin);

   double Error1 = Delta_uu->GetBinError(ibin);
   double Error2 = AFB_uu->GetBinError(ibin);
   double Error3 = Delta_dd->GetBinError(ibin);
   double Error4 = AFB_dd->GetBinError(ibin);

   double Value = Value1 * Value2 + Value3 * Value4;
   double Error = sqrt(Value2 * Value2 * Error1 * Error1 + Value1 * Value1 * Error2 * Error2 + Value4 * Value4 * Error3 * Error3 + Value3 * Value3 * Error4 * Error4);

   AFB->SetBinContent(ibin, Value);
   AFB->SetBinError(ibin, Error);
   cout<<Value1<<" "<<Value2<<" "<<Value3<<" "<<Value4<<" "<<Value<<endl;
 }
}

#endif
