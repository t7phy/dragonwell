#include "Calculation/CalcDIS.h"

double CalcDIS::F2ZMNS2(double x, double Q, double aMu, int iHad, int iPrtn, int Nptn1)
{
//marco=================================================================
// Separate implementation of ZM c2NS2 from A. Vogt hep-ph/0504242 
// This has been extrapolated from Liang's ZmVVA.f file
//marco=================================================================

 double ERR;
 int IER;

 double Ca = 3.0;
 double Zeta2 = 1.6449340668482264365;
 double Zeta3 = 1.2020569031595942854;

 if(x >= 1.0){
   return 0.0;
 }

 int F2L_NF_jNf = Nptn1;
 int F2L_NF_jPrtn = iPrtn;

 double F2LZM_x = x;
 double F2LZM_Q = Q;
 double F2LZM_bMu = aMu;

 int F2LHQhad_iHadn = iHad;

 double als4pi;
 als4pi = GetAlphaS(aMu) / Pi / 4.0;
 double aLm = log(Q * Q / F2LZM_bMu / F2LZM_bMu);

 int Nff = F2L_NF_jNf;

 double DL1 = log(1.0 - x);
 vector<double> Dkfac(7);
 for(int ip = 0; ip <= 6; ip++){
   Dkfac[ip] = pow(DL1, (double)(ip + 1)) / (double)(ip + 1);
 }

 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 double Qns0 = GetPDF(F2LHQhad_iHadn, F2L_NF_jPrtn, x, F2LZM_bMu) + GetPDF(F2LHQhad_iHadn, -F2L_NF_jPrtn, x, F2LZM_bMu);
 double Delta = (-338.513 + 46.8531 * (double)Nff + c2np2Dk0(Dkfac,Nff))*Qns0; //it recollects all the 
                                                                       //Dk terms coming from delta functions 
                                                                       //and plus distributions

 if(F2LZM_Q != F2LZM_bMu){
   Delta = Delta + (
       aLm * aLm * (CF * CF * (-8.0 * Zeta2 + 4.5) - 5.5 * Ca * CF + Nff * CF
       + c2mnp2Dk2a(Dkfac, Nff))
       + aLm * (CF * CF * (40.0 * Zeta3 - 12.0 * Zeta2 - 25.5)
       + Ca * CF * (-12.0 * Zeta3 + 88.0 / 3.0 * Zeta2 + 215.0 / 6.0)
       + Nff * CF * (-16.0 * Zeta2 - 19.0) / 3.0
       + c2mnp2Dk1a(Dkfac,Nff))) * Qns0;
 }


 // Define F2CnsQns2 Function
 F2CnsQns2 = [&](double y){
   double Qns = GetPDF(F2LHQhad_iHadn, F2L_NF_jPrtn, F2LZM_x/y, F2LZM_bMu) + GetPDF(F2LHQhad_iHadn, -F2L_NF_jPrtn, F2LZM_x/y, F2LZM_bMu);
   double Qns0 = GetPDF(F2LHQhad_iHadn, F2L_NF_jPrtn, F2LZM_x, F2LZM_bMu) + GetPDF(F2LHQhad_iHadn, -F2L_NF_jPrtn, F2LZM_x, F2LZM_bMu);

   int Nff = F2L_NF_jNf;

   double CL = c2np2a0(y,Nff);
   double Dk = c2np2Dk(Qns,Qns0,y,Nff);

   if(fabs(F2LZM_Q - F2LZM_bMu) > 1e-6){
     double aLm = log(F2LZM_Q * F2LZM_Q / F2LZM_bMu / F2LZM_bMu);
     CL = CL + (aLm * (aLm * c2mnp2a2(y, Nff) + c2mnp2a1(y, Nff)));
     Dk = Dk + (aLm * (aLm * c2mnp2Dk2(Qns, Qns0, y, Nff)
          + c2mnp2Dk1(Qns, Qns0, y, Nff)));
   }
   //cout<<"iHadn,jPrtn,x,bMu = "<<F2LHQhad_iHadn<<"  "<<F2L_NF_jPrtn<<"  "<<F2LZM_x<<"  "<<F2LZM_bMu<<endl;
   //cout<<"Qns,Qns0,CL,Dk = "<<Qns<<"  "<<Qns0<<"  "<<CL<<"  "<<Dk<<endl;

   return CL * Qns / y + Dk;
 };
 ///////////////////////////////////////////////////////////////////////////////////

 double a5 = 1.0 - 0.00000000001 * (1.0 - x);

 double sum =
              SMPSNF(F2CnsQns2,x + 0.00000000001*(a5-x),
                               x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.0000001*(a5-x),
                               x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.000001*(a5-x),
                               x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.00001*(a5-x),
                               x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.0001*(a5-x),
                               x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.001*(a5-x),
                               x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.01*(a5-x),
                               x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.1*(a5-x),
                               x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.9*(a5-x),
                               x + 0.99*(a5-x),16, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.99*(a5-x),
                               x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.999*(a5-x),
                               x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.9999*(a5-x),
                               x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.99999*(a5-x),
                               x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.999999*(a5-x),
                               x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CnsQns2,x + 0.9999999*(a5-x),a5,4, ERR, IER);

 double Value = pow((als4pi), 2.0) * (sum + Delta);
 //cout<<fixed<<setprecision(16)<<"AlphaS = "<<als4pi<<" "<<sum<<"  "<<Delta<<"  "<<c2np2Dk0(Dkfac,Nff)<<"  "<<Nff<<"  "<<Qns0<<"  "<<F2LZM_Q<<"  "<<F2LZM_bMu<<endl;

 return Value;
}

void CalcDIS::DefineFunctions_nnlo()
{
 Dkfun = [&](int i, double yy, double QA, double QA0){
   return pow((log(1.0 - yy)), (double)i) / (1.0 - yy) * (QA / yy - QA0);
 };

 c2np2Dk0 = [&](vector<double> Dk, int Nf){ // hep-ph/0504242 Eq. (4.8)
   return 128.0/9.0*Dk[3]
         +(-184.0/3.0 +(double)Nf*16.0/9.0)*Dk[2]
         +(-31.1052 -(double)Nf*232.0/27.0)*Dk[1]
         +(188.641 +(double)Nf*6.34888)*Dk[0];
 };

 c2np2a0 = [&](double y, int Nf){ // hep-ph/0504242 Eq. (4.8)
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   double Value = -17.74*pow(DL1, 3.0) + 72.24*DL1*DL1 -628.8*DL1 -181.0
                  -806.7*y + 0.719*y*pow(DL, 4.0) +DL*DL1*(37.75*DL-147.1*DL1)
                  -28.384*DL -20.7*DL*DL -80.0/27.0*pow(DL, 3.0)
                  +Nf*(-1.5*DL1*DL1 +24.87*DL1 -7.8109 -17.82*y -12.97*y*y
                  -0.185*y*pow(DL, 3.0) +8.113*DL*DL1 +16.0/3.0*DL +20.0/9.0*DL*DL);

   return Value;
 };

 c2np2Dk = [&](double QA, double QA0, double y, int Nf){
   vector<double> Dkk(4);
   Dkk.at(0)=Dkfun(0, y ,QA, QA0);
   Dkk.at(1)=Dkfun(1, y ,QA, QA0);
   Dkk.at(2)=Dkfun(2, y ,QA, QA0);
   Dkk.at(3)=Dkfun(3, y ,QA, QA0);

   return c2np2Dk0(Dkk,Nf);
 };

 c2s2aL = [&](double y, int Nf){ // hep-ph/0504242 Eq. (4.9)
// NNLO pure-singlet coefficient functions for F_2
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   double Value = Nf*((8.0/3.0*DL1*DL1 -32.0/3.0*DL1 +9.8937)*y1
                 +(9.57 -13.41*y +0.08*pow(DL1, 3.0))*y1*y1 +5.667*y*pow(DL, 3.0)
                 -DL*DL*DL1*(20.26-33.93*y) +43.36*y1*DL
                 -1.053*DL*DL +40.0/9.0*pow(DL, 3.0) +5.2903/y*y1*y1);

   return Value;
 };

 c2g2aL = [&](double y, int Nf){ // hep-ph/0504242 Eq. (4.10)
// NNLO gluon coefficient functions for F_2
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   double Value = Nf*(58.0/9.0*pow(DL1, 3.0) -24.0*DL1*DL1 -34.88*DL1 +30.586
                 -(25.08 +760.3*y+29.65*pow(DL1, 3.0))*y1 +1204.0*y*DL*DL
                 +DL*DL1*(293.8 +711.2*y +1043.0*DL) +115.6*DL
                 -7.109*DL*DL +70.0/9.0*pow(DL, 3.0) +11.9033/y*y1);

   return Value;
 };

 c2mnp2a2 = [&](double y, int Nf){
   double Ca = 3.0;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);
   double y1p = 1.0 + y;

   double Value = CF*CF*(-8.0*y1p*DL1-4.0*(1.0+y*y)/y1*DL+2.0*y1p*DL-10.0-2.0*y)
                 +Ca*CF*11.0/3.0*y1p + Nf*CF*(-2.0/3.0*y1p);

   return Value;
 };

 c2mnp2a1 = [&](double y, int Nf){
   double Ca = 3.0;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);
   double y1p = 1.0 + y;
   double DL1p = log(y1p);
   double y2p = 1+y*y;
   double Li2y = xLi(2,-y);               //dilogarithm
   double Li2y1 = xLi(2,y1);
   double Zeta2=1.6449340668482264365;

   double Value = CF*CF*(y2p/y1*(4.0*DL*DL-24.0*DL*DL1-6.0*DL)
                 +y2p/y1p*(4.0*DL*DL-16.0*Li2y-16.0*DL*DL1p-8.0*Zeta2)
                 +y1p*(4.0*Li2y1+4.0*DL*DL1-12.0*DL1*DL1-4.0*DL*DL+16.0*Zeta2)
                 +8.0*(2.0+3.0*y)*DL1-2.0*(3.0+11.0*y)*DL+2.0*(19.0+14.0*y))
                 +Ca*CF*(y2p/y1*(44.0/3.0*DL+2.0*DL*DL)
                 +y2p/y1p*(8.0*Li2y-2.0*DL*DL+8.0*DL*DL1p+4.0*Zeta2)
                 +y1p*(22.0/3.0*DL1+4.0*Zeta2)-(164.0+434.0*y)/9.0)
                 +Nf*CF*(-8.0/3.0*y2p/y1*DL-4.0/3.0*y1p*DL1+(32.0+68.0*y)/9.0);

   return Value;
 };

 c2ms2a2 = [&](double y, int Nf){
   double DL = log(y);
   double y1p = 1.0 + y;

   double Value = Nf*CF*Tf*(8.0*y1p*DL+4.0/3.0*(3.0-4.0*y*y-3.0*y+4.0/y));

   return Value;
 };

 c2ms2a1 = [&](double y, int Nf){
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);
   double y1p = 1.0 + y;
   double Li2y1 = xLi(2,y1);

   double Value = Nf*CF*Tf*(16.0*y1p*(Li2y1+DL*DL1-DL*DL)+32.0*y*y*DL
                 +8.0/3.0*(3.0-4.0*y*y-3.0*y+4.0/y)*DL1
                -16.0/9.0*(39.0+4.0*y*y-30.0*y-13.0/y));

   return Value;
 };

 c2mg2a2 = [&](double y, int Nf){
   double Ca = 3.0;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);
   double y1p = 1.0 + y;
   double tmp = 8.0 * (1.0+2.0*y*y-2.0*y)*DL1;
//marco
   double Value = Nf*(CF*Tf*(-4.0*(1.0+4.0*y*y-2.0*y)*DL+tmp-2.0+8.0*y)
                 +Ca*Tf*(8.0*(1.0+4.0*y)*DL+tmp //it should be Ca*Tf according to NPB383 1992 Eq.B.6 and not Ca*Cf
                +4.0/3.0*(3.0-31.0*y*y+24.0*y+4.0/y)));

   return Value;
 };

 c2mg2a1 = [&](double y, int Nf){
   double Ca = 3.0;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);
   double y1p = 1.0 + y;
   double DL1p = log(y1p);
   double Li2y = xLi(2,-y);               //dilogarithm
   double Li2y1 = xLi(2,y1);
   double Zeta2=1.6449340668482264365;
//marco
   double Value = Nf*(CF*Tf*(16.0*(1.0+2.0*y*y-2.0*y)*(DL1*DL1-2.0*Zeta2)
                 +8.0*(1.0+4.0*y*y-2.0*y)*DL*DL-8.0*(3.0+8.0*y*y-6.0*y)*DL*DL1
                 +8.0*(1.0+10.0*y*y-6.0*y)*DL+8.0*(1.0-2.0*y)*Li2y1
                 -4.0*(7.0+20.0*y*y-24.0*y)*DL1+4.0*(9.0+4.0*y*y-17.0*y))
                 +Ca*Tf*(32.0*y*(3.0-y)*DL*DL1 //it should be Ca*Tf according to NPB383 1992 Eq.B.6 and not Ca*Cf
                 -16.0*(1.0+2.0*y*y+2.0*y)*(DL*DL1p+Li2y)
                 -16.0*(1.0+3.0*y)*DL*DL+16.0*(1.0+4.0*y)*Li2y1
                 -16.0*(1.0+2.0*y*y)*Zeta2+8.0*y*(25.0*y-24.0)*DL
                 +8.0*(1.0+2.0*y*y-2.0*y)*DL1*DL1
                 -8.0/3.0*(3.0+67.0*y*y-60.0*y-4.0/y)*DL1
                 -4.0/9.0*(165.0-407.0*y*y+276.0*y-52.0/y)));

   return Value;
 };

 c2mnp2Dk2a = [&](vector<double> Dk, int Nf){
   double Ca = 3.0;
   return CF*CF*(16.0*Dk.at(1)+12.0*Dk.at(0)) -Ca*CF*22.0/3.0*Dk.at(0)+Nf*CF*4.0/3.0*Dk.at(0);
 };

 c2mnp2Dk1a = [&](vector<double> Dk, int Nf){
   double Ca = 3.0;
   double Zeta2=1.6449340668482264365;

   return CF*CF*(24.0*Dk.at(2)-12.0*Dk.at(1)-(32.0*Zeta2+45.0)*Dk.at(0))
         +Ca*CF*(-44.0/3.0*Dk.at(1)+(367.0/9.0-8.0*Zeta2)*Dk.at(0))
         +Nf*CF*(8.0/3.0*Dk.at(1)-58.0/9.0*Dk.at(0));
 };

 c2mnp2Dk2 = [&](double QA, double QA0, double y, int Nf){
   vector<double> Dkk(2);
   Dkk.at(0) = Dkfun(0,y,QA,QA0);
   Dkk.at(1) = Dkfun(1,y,QA,QA0);
   return c2mnp2Dk2a(Dkk, Nf);
 };

 c2mnp2Dk1 = [&](double QA, double QA0, double y, int Nf){
   vector<double> Dkk(3);
   Dkk.at(0) = Dkfun(0,y,QA,QA0);
   Dkk.at(1) = Dkfun(1,y,QA,QA0);
   Dkk.at(2) = Dkfun(2,y,QA,QA0);
   return c2mnp2Dk1a(Dkk, Nf);
 };

/////////////////////////////////////////////////////////////////////////////

 clnp2a = [&](double y, int Nf){
// (alpha_S^2) non-singlet coefficient functions for F_L
// References:
//   S. Moch, J. Vermaseren and A. Vogt, PLB606(2005)123-129
//   W.L. van Neerven, A. Vogt, NPB588(2000)345
//   W.L. van Neerven, A. Vogt, NPB568(2000)263
//   E.B. Zijlstra, W.L. van Neerven, PLB272(1991)127
//   S. Moch, J.A.M. Vermaseren, NPB573(2000)853
//   J.S. Guillen, et al., NPB353(1991)337

//marco11 Approximate expression
   double yy = y * y;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   return  128.0/9.0*y*DL1*DL1 -46.5*y*DL1-84.094*DL*DL1
          -37.338 +89.53*y +33.82*yy +y*DL*(32.9+18.41*DL)
          -128.0/9.0*DL +16.0/27.0*Nf*(6.0*y*DL1 -12.0*y*DL -25.0*y +6.0);
 };

 cls2aL = [&](double y, int Nf){
// NLO pure-singlet coefficient functions for F_L
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   return Nf*((15.94 -5.212*y)*y1*y1*DL1 +(0.421 +1.52*y)*DL*DL
         +28.09*y1*DL -(2.37/y -19.27)* pow(y1, 3.0));
 };

 clg2aL = [&](double y, int Nf){
// NLO gluon coefficient functions for F_L
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   return Nf*((94.74 -49.2*y)*y1*DL1*DL1 +864.8*y1*DL1
         +1161.0*y*DL1*DL +60.06*y*DL*DL +39.66*y1*DL
         -5.333*(1.0/y-1.0));
 };

 clmnp2a = [&](double y, int Nf){// factorization scale dependent term
   double Ca = 3.0;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   return CF*CF*(8.0*y*(2.0*DL1-DL)+4.0*(2.0+y))
         +Ca*CF*(-44.0/3.0*y)+Nf*CF*8.0/3.0*y;
 };

 clms2a = [&](double y, int Nf){
   double DL = log(y);

   return Nf*CF*Tf*(-32.0*y*DL -32.0/3.0*(3.0-2.0*y*y-1.0/y));
 };

 clmg2a = [&](double y, int Nf){
   double Ca = 3.0;
   double DL = log(y);
   double y1 = 1.0 - y;
   double DL1 = log(y1);

   return Nf*(CF*Tf*(32.0*y*DL +16.0*(1.0-2.0*y*y+y))
         +Ca*Tf*(64.0*y*y1*DL1-128.0*y*DL
         -32.0/3.0*(3.0-17.0*y*y+15.0*y-1.0/y)));
 };



 isDefineNNLOFunctions = true;
}

double CalcDIS::FLZMNS2(double x, double Q, double aMu, int iHad, int iPrtn, int Nptn1)
{
//marco=================================================================
// Separate implementation of ZM cLNS2 from A. Vogt hep-ph/0504242 
// This has been extrapolated from Liang's ZmVVA.f file
//marco=================================================================

 double ERR;
 int IER;

 int F2L_NF_jNf = Nptn1;
 int F2L_NF_jPrtn = iPrtn;

 double F2LZM_x = x;
 double F2LZM_Q = Q;
 double F2LZM_bMu = aMu;

 int F2LHQhad_iHadn = iHad;

 if(x >= 1.0){
   return 0.0;
 }

 double als4pi; 
 als4pi = GetAlphaS(aMu) / Pi / 4.0;
 double Qns0 = GetPDF(F2LHQhad_iHadn, F2L_NF_jPrtn, x, F2LZM_bMu) + GetPDF(F2LHQhad_iHadn, -F2L_NF_jPrtn, x, F2LZM_bMu);
 double Delta= -0.012 * Qns0;      //it recollects all the 
                                   //Dk terms coming from delta functions 
                                   //and plus distributions

 double a5 = 1.0 - 0.00000000001*(1.0-x);

 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 FLCnsQns2 = [&](double y){
   int Nff = F2L_NF_jNf;
   double Qns = GetPDF(F2LHQhad_iHadn, F2L_NF_jPrtn, F2LZM_x/y, F2LZM_bMu) + GetPDF(F2LHQhad_iHadn, -F2L_NF_jPrtn, F2LZM_x/y, F2LZM_bMu);
   double CL = clnp2a(y, Nff);
   if(fabs(F2LZM_Q - F2LZM_bMu) > 1e-6){
     double aLm = log(F2LZM_Q * F2LZM_Q / F2LZM_bMu / F2LZM_bMu);
     CL = CL + clmnp2a(y, Nff) * aLm;
   }

   return CL * Qns / y;
 };

 double sum =
              SMPSNF(FLCnsQns2, x + 0.00000000001*(a5-x),
                                x + 0.00000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.00000001*(a5-x),
                                x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.0000001*(a5-x),
                                x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.000001*(a5-x),
                                x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.00001*(a5-x),
                                x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.0001*(a5-x),
                                x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.001*(a5-x),
                                x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.01*(a5-x),
                                x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.1*(a5-x),
                                x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.9*(a5-x),
                                x + 0.99*(a5-x),16, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.99*(a5-x),
                                x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.999*(a5-x),
                                x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.9999*(a5-x),
                                x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.99999*(a5-x),
                                x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.999999*(a5-x),
                                x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCnsQns2, x + 0.9999999*(a5-x),a5,4, ERR, IER);

// include marco's  Divide by 2, to match with the normalization of F_{long}
 double Value = pow((als4pi), 2.0) * (sum + Delta) / 2.0;

 return Value;
}

double CalcDIS::F2ZMPS2(double x, double Q, double aMu, int iHad)
{
//marco=================================================================
// Separate implementation of ZM c2PS2 from A. Vogt hep-ph/0504242 
// This has been extrapolated from Liang's ZmVVA.f file
//marco=================================================================
//     The zero-mass NNLO pure singlet quark F2 for 1 quark flavor 
//     in the coefficient function (and singlet PDF for the global Nf flavors)

 double ERR;
 int IER;

 double F2LZM_x = x;
 double F2LZM_Q = Q;
 double F2LZM_bMu = aMu;

 int F2LHQhad_iHadn = iHad;

 if(x >= 1.0){
   return 0.0;
 }

 double als4pi; 
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 // Define Function
 F2CqQPS = [&](double y){
   int Nff = 1;
   double aLm = log(F2LZM_Q * F2LZM_Q / F2LZM_bMu / F2LZM_bMu);
   double Qs = GetPDF(F2LHQhad_iHadn, 20, F2LZM_x/y, F2LZM_bMu);
   double Qs0 = GetPDF(F2LHQhad_iHadn, 20, F2LZM_x, F2LZM_bMu);

   double CL = c2s2aL(y,Nff);         //only pure-singlet

   if(fabs(F2LZM_Q - F2LZM_bMu) > 1e-6){
// See Eq B.4 in Nucl Phys B383 by Zijlstra and Van Neerven, 
// there is no aLm dependence in the pure singlet case.  
// See also Nucl. Phys. B588 345 (2000) A. Vogt
     CL = CL + 0.0;
   }

   return CL * Qs / y;
 };
//////////////////////////////////////////////////////////////////////////
 double a5 = 1.0 - 0.00000000001 * (1.0 - x);

 double sum =
              SMPSNF(F2CqQPS, x + 0.00000000001*(a5-x),
                              x + 0.000000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.000000001*(a5-x),
                              x + 0.00000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.00000001*(a5-x),
                              x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.0000001*(a5-x),
                              x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.000001*(a5-x),
                              x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.00001*(a5-x),
                              x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.0001*(a5-x),
                              x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.001*(a5-x),
                              x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.01*(a5-x),
                              x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.1*(a5-x),
                              x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.9*(a5-x),
                              x + 0.99*(a5-x),32, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.99*(a5-x),
                              x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.999*(a5-x),
                              x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.9999*(a5-x),
                              x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.99999*(a5-x),
                              x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.999999*(a5-x),
                              x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.9999999*(a5-x),
                              x + 0.99999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.99999999*(a5-x),
                              x + 0.999999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CqQPS, x + 0.999999999*(a5-x),a5,4, ERR, IER);

 double Value = pow(als4pi, 2.0) * sum;

 return Value;
}

double CalcDIS::F2ZMG2(double x, double Q, double aMu, int iHad)
{
//marco=================================================================
// Separate implementation of ZM c2g2 from A. Vogt hep-ph/0504242 
// This has been extrapolated from Liang's ZmVVA.f file
//marco=================================================================
//     The zero-mass NNLO gluon contribution for 1 quark flavor 
//     in the coefficient function (and singlet PDF for the global Nf flavors)

 double ERR;
 int IER;

 double F2LZM_x = x;
 double F2LZM_Q = Q;
 double F2LZM_bMu = aMu;

 int F2LHQhad_iHadn = iHad;

 if(x >= 1.0){
   return 0.0;
 }

 double als4pi; 
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 // Define Function
 F2CgG = [&](double y){
   int Nff = 1;
   double CL = c2g2aL(y,Nff);
   if(fabs(F2LZM_Q - F2LZM_bMu) > 1e-6){
     double aLm = log(F2LZM_Q * F2LZM_Q / F2LZM_bMu / F2LZM_bMu);
     CL = CL + aLm * (aLm * c2mg2a2(y, Nff) + c2mg2a1(y, Nff));
   }

   double GG = GetPDFH(F2LHQhad_iHadn, 0, F2LZM_x/y, F2LZM_bMu);

   return CL * GG / y;
 };
/////////////////////////////////////////////////////////////////////////////
 double a5 = 1.0 - 0.00000000001 * (1.0 - x);

 double sum =
              SMPSNF(F2CgG, x + 0.00000000001*(a5-x),
                            x + 0.0000000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.0000000001*(a5-x),
                            x + 0.000000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.000000001*(a5-x),
                            x + 0.00000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.00000001*(a5-x),
                            x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.0000001*(a5-x),
                            x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.000001*(a5-x),
                            x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.00001*(a5-x),
                            x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.0001*(a5-x),
                            x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.001*(a5-x),
                            x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(F2CgG, x + 0.01*(a5-x),
                            x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(F2CgG, x + 0.1*(a5-x),
                            x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(F2CgG, x + 0.9*(a5-x),
                            x + 0.99*(a5-x),16, ERR, IER)
            + SMPSNF(F2CgG, x + 0.99*(a5-x),
                            x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(F2CgG, x + 0.999*(a5-x),
                            x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.9999*(a5-x),
                            x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.99999*(a5-x),
                            x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.999999*(a5-x),
                            x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.9999999*(a5-x),
                            x + 0.99999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.99999999*(a5-x),
                            x + 0.999999999*(a5-x),4, ERR, IER)
            + SMPSNF(F2CgG, x + 0.999999999*(a5-x),a5,4, ERR, IER);

 double Value = pow(als4pi, 2.0) * sum;

 return Value;
}

double CalcDIS::FLZMPS2(double x, double Q, double aMu, int iHad)
{
//marco=================================================================
// Separate implementation of ZM cLPS2 from A. Vogt hep-ph/0504242 
// This has been extrapolated from Liang's ZmVVA.f file
//marco=================================================================
//     The zero-mass NNLO pure singlet quark F2 for 1 quark flavor 
//     in the coefficient function (and singlet PDF for the global Nf flavors)

 double ERR;
 int IER;

 double F2LZM_x = x;
 double F2LZM_Q = Q;
 double F2LZM_bMu = aMu;

 int F2LHQhad_iHadn = iHad;

 if(x >= 1.0){
   return 0.0;
 }

 double als4pi; 
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 // Define Function
 FLCqQPS = [&](double y){
   int Nff = 1;
   double Qs = GetPDF(F2LHQhad_iHadn, 20, F2LZM_x/y, F2LZM_bMu);

   double CL= cls2aL(y,Nff);    // pure-singlet from Eq.5 in PLB606 123 2005 A. Vogt
   if(fabs(F2LZM_Q - F2LZM_bMu) > 1e-6){
     double aLm = log(F2LZM_Q * F2LZM_Q / F2LZM_bMu / F2LZM_bMu);
     CL = CL + clms2a(y,Nff)*aLm; //Eq B.3 NPB383 525 1992, Zijlstra, van Neeven
   }

   return CL * Qs / y;
 };


/////////////////////////////////////////////////////////////////////////////
 double a5 = 1.0 - 0.00000000001 * (1.0 - x);

 double sum =
              SMPSNF(FLCqQPS, x + 0.00000000001*(a5-x),
                              x + 0.0000000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.0000000001*(a5-x),
                              x + 0.000000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.000000001*(a5-x),
                              x + 0.00000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.00000001*(a5-x),
                              x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.0000001*(a5-x),
                              x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.000001*(a5-x),
                              x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.00001*(a5-x),
                              x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.0001*(a5-x),
                              x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.001*(a5-x),
                              x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.01*(a5-x),
                              x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.1*(a5-x),
                              x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.9*(a5-x),
                              x + 0.99*(a5-x),16, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.99*(a5-x),
                              x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.999*(a5-x),
                              x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.9999*(a5-x),
                              x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.99999*(a5-x),
                              x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.999999*(a5-x),
                              x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.9999999*(a5-x),
                              x + 0.99999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.99999999*(a5-x),
                              x + 0.999999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCqQPS, x + 0.999999999*(a5-x),a5,4, ERR, IER);

// includes marco's Divide by 2, to match with the normalization of F_{long}
 double Value = pow(als4pi, 2.0) * sum / 2.0;

 return Value;
}

double CalcDIS::FLZMG2(double x, double Q, double aMu, int iHad)
{
//marco=================================================================
// Separate implementation of ZM cLg2 from A. Vogt hep-ph/0504242 
// This has been extrapolated from Liang's ZmVVA.f file
//marco=================================================================
//     The zero-mass NNLO gluon FL for 1 quark flavor 
//     in the coefficient function 

 double ERR;
 int IER;

 double F2LZM_x = x;
 double F2LZM_Q = Q;
 double F2LZM_bMu = aMu;

 int F2LHQhad_iHadn = iHad;

 if(x >= 1.0){
   return 0.0;
 }

 double als4pi; 
 als4pi = GetAlphaS(aMu) / Pi / 4.0;

 if(!isDefineNNLOFunctions) DefineFunctions_nnlo();

 // Define Function
 FLCgG = [&](double y){
   int Nff = 1;
   double CL = clg2aL(y,Nff);

   if(fabs(F2LZM_Q - F2LZM_bMu) > 1e-6){
     double aLm = log(F2LZM_Q * F2LZM_Q / F2LZM_bMu / F2LZM_bMu);
     CL = CL + clmg2a(y,Nff) * aLm;
   }

   double GG = GetPDFH(F2LHQhad_iHadn, 0, F2LZM_x/y, F2LZM_bMu);

   return CL * GG / y;
 };

///////////////////////////////////////////////////////////////////////////////
 double a5 = 1.0 - 0.00000000001 * (1.0 - x);

 double sum =
              SMPSNF(FLCgG, x + 0.00000000001*(a5-x),
                            x + 0.000000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.000000001*(a5-x),
                            x + 0.00000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.00000001*(a5-x),
                            x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.0000001*(a5-x),
                            x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.000001*(a5-x),
                            x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.00001*(a5-x),
                            x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.0001*(a5-x),
                            x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.001*(a5-x),
                            x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(FLCgG, x + 0.01*(a5-x),
                            x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(FLCgG, x + 0.1*(a5-x),
                            x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(FLCgG, x + 0.9*(a5-x),
                            x + 0.99*(a5-x),16, ERR, IER)
            + SMPSNF(FLCgG, x + 0.99*(a5-x),
                            x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(FLCgG, x + 0.999*(a5-x),
                            x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.9999*(a5-x),
                            x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.99999*(a5-x),
                            x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.999999*(a5-x),
                            x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.9999999*(a5-x),
                            x + 0.99999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.99999999*(a5-x),
                            x + 0.999999999*(a5-x),4, ERR, IER)
            + SMPSNF(FLCgG, x + 0.999999999*(a5-x),a5,4, ERR, IER);

// include marco's Divide by 2, to match with the normalization of F_{long}
 double Value = pow(als4pi, 2.0) * sum  / 2.0;

 return Value;
}

