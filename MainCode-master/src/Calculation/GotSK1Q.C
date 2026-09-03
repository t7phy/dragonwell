#include "Calculation/CalcDIS.h"

void CalcDIS::GotSK1Q(int iHadx, int iPartx, double F2Mx, double x, double Q, double aMu, FortranArray1D<double> &SfnG)
{
//  NLO contribution to the general SfnG due to initial state quark parton iPrtn
//  without the EW coupling--the result is flavor-independent;
//  Also not included is the overall \alpha_s / 2pi factor.
//                             2006.02.10
//  Formulas based on Gottschalk, as corrected by Stefan Kretzer etal
//  Programmed by A. Belyaev, based on the SfZm05 structure (wkt)
//           ----------------------------------------------

 double Smll = 1e-6;
 double ER;
 int IR;

 CxNloSK_iHad      = iHadx;
 CxNloSK_iPart     = iPartx;
 CxNloSK_x         = x;
 CxNloSK_aMu       = aMu;
 CxNloSK_F2M       = F2Mx;
 CxNloSK_Q         = Q;

 DL = pow(Q, 2.0) / (pow(Q, 2.0) + pow(F2Mx, 2.0)); //lambda

 if(!isDefineSK1QFunctions) DefineFunctions_SK1Q();

 double Pdfnx = GetPDF(iHadx, iPartx, x, aMu);

 double FHQ0_N= AdzInt(HQ0_N, x, 1.0, aErr, rErr, ER, IR, 1, 1);

//  HQ0_D  is the delta term of h^q  
 double FHQ0_D= HQ0_D(DL)*Pdfnx;
//   HQ0_PM  is the multiplier of the Plus function in h^q  
//   HQ0_P   is the Plus function in h^q  
 double FHQ0_P=AdzInt(HQ0_P1, x, 1.0, aErr, rErr, ER, IR, 1, 1) - HQ0_PM(1.0) * Pdfnx * AdzInt(HQ0_P, 0.0, x, aErr, rErr, ER, IR, 1, 1);
//-----------------
 double FHQA_D= HQA_D(DL)*Pdfnx;

 FortranArray1D<double> FHQI{1, 3};
 double FHQB_P;

 for(int i = 1; i <= 3; i++){
   index_idxi = i;
   FHQI(i) = FHQ0_N+FHQ0_D+FHQ0_P+FHQA_D;
   for(int j = 1; j <= 3; j++){
     index_idxj = j;
     FHQB_P = AdzInt(HQB_P1, x, 1.0, aErr, rErr, ER, IR, 1, 1) - HQB_PM(1.0) * Pdfnx * AdzInt(HQB_P, 0.0, x, aErr, rErr, ER, IR, 1, 1);
     FHQI(i)=FHQI(i)+FHQB_P;

     //if(fabs(x - 0.248666) < 1e-3 && fabs(Q - 3.49571) < 1e-5){
     //  cout<<"FHQB_P = "<<FHQB_P<<" HQB_PM(1.0) = "<<HQB_PM(1.0)<<" Pdfnx = "<<Pdfnx<<endl;
     //}
   }
   //if(fabs(x - 0.248666) < 1e-3 && fabs(Q - 3.49571) < 1e-5){
   //  cout<<"GotSK1Q: FHQI = "<<FHQI(i)<<"  "<<FHQ0_N<<"  "<<FHQ0_D<<"  "<<FHQ0_P<<"  "<<FHQA_D<<endl;
   //}
 }

//-----------------      
 double F1 =  FHQI(1);
 double F2 =  FHQI(2);
 double F3 =  FHQI(3);

 SfnG(1) = F1      / 2.0;          // SfnG_1 = F1/2
 SfnG(3) = (F2-F1) / 2.0;          // SfnG_3 = Flong = (F2-F1)/2
 SfnG(2) = 0.0;        // Zero-mass case has no chirality-mixing terms
 SfnG(4) = 0.0;        // Zero-mass case has no chirality-mixing terms
 SfnG(5) = F3 /2.0;              // SfnG_5 = F3/2 
                           
                           
 if (fabs(Q/aMu - 1.0) > Smll){
   double Qmu1 = AdzInt(aPqq,  0.0, x, aErr, rErr, ER, IR, 1, 0) * Pdfnx;
   double Qmu2 = AdzInt(aPqqFxSK, x, 1.0, aErr, rErr, ER, IR, 1, 1);

   FortranArray1D<double> OmgLo{1, 5};
   OmgLo(1) = 0.5;
   OmgLo(2) = 0.0;
   OmgLo(3) = 0.0;
   OmgLo(4) = 0.0;
   OmgLo(5) = 0.5;

   for(int i = 1; i <= 5; i++){
     SfnG(i) = SfnG(i) + 2.0 * OmgLo(i) * log(Q / aMu) * (Qmu2 - Qmu1);
   }
 }

 for(int i = 1; i <= 5; i++){
   SfnG(i) = SfnG(i) * CF;// QCD color factor
 }

}

void CalcDIS::DefineFunctions_SK1Q()
{
 DKA = [&](double z){
   double Value = 0.0;
   if(z < (1.0 - 1e-9)) Value = 1.0/z*(1.0-z)*log(1.0-z);
   return Value;
 };

 HQ0_D = [&](double z){
   double Value = -(4.0+1.0/2.0/z+pow(Pi, 2.0)/3.0+(1.0+3.0*z)/2.0/z*DKA(z));
   return Value;
 };

 HQ0_N = [&](double z){
   double Pdfnxz = GetPDF(CxNloSK_iHad, CxNloSK_iPart, CxNloSK_x/z, CxNloSK_aMu);
   double Value = -(1.0+pow(z, 2.0))*log(z)/(1.0-z);
   Value = Value * Pdfnxz / z;
   return Value;
 };

 HQ0_P = [&](double z){
   double Value = (2.0*log(1.0-z)-log(1.0-DL*z))/(1.0-z);
   return Value;
 };

 HQ0_PM = [&](double z){
   double Value = 1.0+pow(z, 2.0);
   return Value;
 };

 HQ0_P1 = [&](double z){
   double Pdfnxz = GetPDF(CxNloSK_iHad, CxNloSK_iPart, CxNloSK_x/z, CxNloSK_aMu);
   double Pdfnx  = GetPDF(CxNloSK_iHad, CxNloSK_iPart,   CxNloSK_x, CxNloSK_aMu);

   double Value = HQ0_P(z)*(HQ0_PM(z)*Pdfnxz/z - HQ0_PM(1.0)*Pdfnx);
   return Value;
 };

 HQA_D = [&](double z){
   double Value = 0.0;
   if(index_idxi == 2) Value = DKA(DL);
   return Value;
 };

 HQB_P = [&](double z){
   double Value = 0.0;
   if(index_idxj==1){
     Value=1.0/(1.0-z);
   }
   else if(index_idxj==2){
     Value=1.0/(1.0-DL*z);
   }
   else if(index_idxj==3){
     Value=(1.0-z)/pow((1.0-DL*z), 2.0);
   }
   return Value;
 };

 HQB_PM = [&](double z){
   double Value = 0.0;
   if(index_idxj==1){
     if(index_idxi==1) Value=1.0-4.0*z+z*z;
     if(index_idxi==2) Value=2.0-2.0*z*z-2.0/z;
     if(index_idxi==3) Value=-1.0-z*z;
   }
   else if(index_idxj==2){
     if(index_idxi==1) Value=z-z*z;
     if(index_idxi==2) Value=2.0/z-1.0-z;
     if(index_idxi==3) Value=1.0-z;
   }
   else if(index_idxj==3){
     Value=0.5;
   }
   return Value;
 };

 HQB_P1 = [&](double z){
   double Pdfnxz = GetPDF(CxNloSK_iHad, CxNloSK_iPart, CxNloSK_x/z, CxNloSK_aMu);
   double Pdfnx  = GetPDF(CxNloSK_iHad, CxNloSK_iPart,   CxNloSK_x, CxNloSK_aMu);

   double Value = HQB_P(z)*(HQB_PM(z)*Pdfnxz/z - HQB_PM(1.0)*Pdfnx);
   return Value;
 };

 if(!isDefineQuarkFunctions) DefineFunctions_quark();

 aPqqFxSK = [&](double z){
   double Pdfnxz = GetPDF(CxNloSK_iHad, CxNloSK_iPart, CxNloSK_x/z, CxNloSK_aMu);
   double Pdfnx  = GetPDF(CxNloSK_iHad, CxNloSK_iPart,   CxNloSK_x, CxNloSK_aMu);

   double Value =  aPqq(z) * (Pdfnxz/z - Pdfnx);
   return Value;
 };

 isDefineSK1QFunctions = true;
}
