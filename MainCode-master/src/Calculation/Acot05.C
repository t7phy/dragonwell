#include "Calculation/CalcDIS.h"

void CalcDIS::Acot0Q(int iHadn, int iPrtn, double F1M, double F2M, double x, double Q, double aMu, FortranArray1D<double> &SfnG)
{
//-----------------------------------------------------------------------------
//      Computes LO Hadron Structure Functions in the general irreducible set based on
//        symmetry considerations (cf. DisPac05 notes, originated in ACOT-II paper).
//  SfnG(1): transverse,   parity conserving amp. ~ g_V^2 + g_A^2 (g_R^2 + g_L^2) (=
//  SfnG(2): transverse,   parity conserving amp. ~ g_V^2 - g_A^2 (   g_V*g_A   )
//  SfnG(3): longitudinal, parity conserving amp. ~ g_V^2 + g_A^2 (g_R^2 + g_L^2)
//  SfnG(4): longitudinal, parity conserving amp. ~ g_V^2 - g_A^2 (   g_V*g_A   )
//  SfnG(5): transverse,   parity violating  amp. ~    g_V*g_A    (g_R^2 - g_L^2)
//
//        (x, Q) are input kinematic variables;
//        aMu is the factorization scale, which does not have to be equal to Q.
//        F1m/F2m are the masses of the initial/final state quark masses.
//-----------------------------------------------------------------------------

 FortranArray1D<double> OmgLo{1, 5};
                                            // Compute the partonic irreducible amp's
 Omg0(Q, F1M, F2M, OmgLo);
                                            // PDF factor
 double PdfTmp = GetPDF(iHadn, iPrtn, x, aMu);

 for(int i = 1; i <= 5; i++){
   SfnG(i) = OmgLo(i) * PdfTmp / 2.0; // 2d0 is the conversion factor due to def. of C_i
 }

 for(int i = 1; i <= 5; i++){
   if(!isfinite(SfnG(i))){
     cout<<"fatal error #1: SfnG["<<i<<"] = "<<SfnG(i)<<endl;
     return;
   }
 }
}

void CalcDIS::Omg0(double Q, double F1M, double F2M, FortranArray1D<double> &OmgLo)
{
//-----------------------------------------------------------------------------
//      Irreducible LO quark-initiated amplitudes OmgLo from ACOT-I paper, 
//                       Simplified from Table 7.
//-----------------------------------------------------------------------------

// xx      DELTA(A,B,C) = SQRT(A**2 + B**2 + C**2 - 2d0*(A*B+B*C+C*A))
//-----------------------------------------------------------------------------
 double F1M2  = pow(F1M, 2.0);
 double F2M2  = pow(F2M, 2.0);
 double Q2    = pow(Q, 2.0);
// xx      DEL   = DELTA(-Q2,F1M2,F2M2)
// replace delta by form that should be less sensitive to round-off (jcp 10/2013)
 double A = Q2 * (-1.0);
 double B = F1M2;
 double C = F2M2;
// first make A .ge. B .ge. C 
 if(B > A){
    double tmp = A;
    A = B;
    B = tmp;
 }
 if(C > A){
    double tmp = A;
    A = C;
    C = tmp;
 }
 if(C > B){
    double tmp = B;
    B = C;
    C = tmp;
 }

 double delsq = pow((A - B - C), 2.0) - 4.0 * B * C;
 double del;
 if(delsq >= 0.0){
    del = sqrt(delsq);
 }
 else{
   cout<<"Fatal delsq #1 = "<<delsq<<" A,B,C = "<<A<<" "<<B<<" "<<C<<endl;
   return;
 }

//-----------------------------------------------------------------------------
 OmgLo(1) = (Q2 + F1M2 + F2M2) / del;
 OmgLo(2) = -2.0 * F1M * F2M / del;
 OmgLo(5) = 1.0;              // This corresponds to C_a=g2L^2-g2R^2 (opposite of ACOT-II def.)

 OmgLo(3) = ((F1M2 + F2M2) + (pow((F1M2 - F2M2), 2.0) / Q2)) / del;
 OmgLo(4) = 2.0 * F1M * F2M / del;
}

void CalcDIS::Acot1G(int iHadn, double M2, double M1, double x, double Q, double vMu, FortranArray1D<double> &SfnG)
{
//-----------------------------------------------------------------------------
//     Computes NLO Hadron general SF SfnG --- Gluon Fusion term
//        These results are independent of final-state quark flavors;
//
//        For notation, see comment lines in Subroutine Acot0Q
//  From ACOT-II paper, except for change of definitions noted in these comments.
//-----------------------------------------------------------------------------
 double ERR;
 int IER;
 double CxNloG_x = x;
 double CxNloG_Q = Q;
 double CxNloG_F1m = M1;
 double CxNloG_F2m = M2;
 double CxNloG_aMu = vMu;
 int CxNloG_iHad = iHadn;
 int CxNloG_Ired;

 FortranArray1D<double> SfIred{1, 5};

 xNloG = [&](double z){
                                                // The gluon PDF
   double PdfTmp  = GetPDF(CxNloG_iHad, 0, z, CxNloG_aMu);
                                                // The Wilson Coeff.      
   double xHat = CxNloG_x / z;

   FortranArray1D<double> OmgNlo{1, 5};
   OmgG1(xHat, CxNloG_Q, CxNloG_F1m, CxNloG_F2m, OmgNlo);
   double Ftem = OmgNlo(CxNloG_Ired);           // Ired is the irreducible amp label
                                                // The integrand      
   return Ftem * PdfTmp / z;
 };

//                                    Limits of convolution integration      
 double z0 = x * ( pow((CxNloG_F1m + CxNloG_F2m), 2.0) + pow(Q, 2.0) ) / pow(Q, 2.0);
 double z1 = 1.0;
//                                            Test these limits
 if(z0 >= z1){
   cout<<"z0 >= z1 in Acot1G convolution, z0, z1 = "<<z0<<"  "<<z1<<endl;
   return;
 }

//                   Calculate the convolution integrals for the Ireducible amps
 for(int Ired = 1; Ired <= 5; Ired++){
   CxNloG_Ired = Ired;

   double a5 = 1.0 - 0.00000000001*(1.0-z0);

   SfIred(Ired) =
                  SMPSNF(xNloG,z0 + 0.00000000001*(a5-z0),
                               z0 + 0.000001*(a5-z0),4, ERR, IER)
                + SMPSNF(xNloG,z0 + 0.000001*(a5-z0),
                               z0 + 0.00001*(a5-z0),4, ERR, IER)
                + SMPSNF(xNloG,z0 + 0.00001*(a5-z0),
                               z0 + 0.0001*(a5-z0),4, ERR, IER)
                + SMPSNF(xNloG,z0 + 0.0001*(a5-z0),
                               z0 + 0.001*(a5-z0),4, ERR, IER)
                + SMPSNF(xNloG,z0 + 0.001*(a5-z0),
                               z0 + 0.01*(a5-z0),8, ERR, IER)
                + SMPSNF(xNloG,z0 + 0.01*(a5-z0),
                               z0 + 0.1*(a5-z0),16, ERR, IER)
                + SMPSNF(xNloG,z0 + 0.1*(a5-z0),a5,48, ERR, IER);

 }

//                                        Put on the QCD color factor

 for(int i = 1; i <= 5; i++){
   SfnG(i) = SfIred(i) * TR;
 }

 for(int i = 1; i <= 5; i++){
   if(!isfinite(SfnG(i))){
     cout<<"fatal error #2: SfnG["<<i<<"] = "<<SfnG(i)<<endl;
     return;
   }
 }
}

void CalcDIS::OmgG1(double x, double Q, double F1M, double F2M, FortranArray1D<double> &OmgNlo)
{
//-----------------------------------------------------------------------------
//      Irreducible NLO gluon-initiated amplitudes Omga_G: Eqs.(18)-(19). ACOT-II
//        Needed in the NLO convolution integral
//-----------------------------------------------------------------------------

 auto Delta = [&](double A, double B, double C){
   return sqrt(A*A + B*B + C*C - 2.0*(A*B+B*C+C*A));
 };

 double F1m2  = F1M*F1M;
 double F2m2  = F2M*F2M;
 double Q2    = Q*Q;

// replace delta by form that should be less sensitive to round-off (jcp 10/2013)
 double A = -Q2;
 double B = F1m2;
 double C = F2m2;

// first make |A| .ge |B| .ge. |C| 
 if(B > A){
   double tmp = A;
   A = B;
   B = tmp;
 }
 if(C > A){
   double tmp = A;
   A = C;
   C = tmp;
 }
 if(C > B){
   double tmp = B;
   B = C;
   C = tmp;
 }

 double delsq = pow((A-B-C), 2.0) - 4.0*B*C;
 double del;
 if(delsq >= 0.0){
   del = sqrt(delsq);
 }
 else{
   cout<<"Fatal delsq #2 = "<<delsq<<" A,B,C = "<<A<<"  "<<B<<"  "<<C<<endl;
   return;
 }
//-----------------------------------------------------------------------------

 double xMax = Q2 / (pow((F1M + F2M), 2.0) + Q2);
 if((x >= 1.0) || (x >= xMax)) return;

 double sMin = pow((F1M + F2M), 2.0);
 double qMin = sqrt( sMin * x/(1.0 - x) );
 if(Q <= qMin) return;

//     Cm-Energy for the hard process for this SHAT=S
 double S = Q2 * (1.0 / x - 1.0);
 if(S <= sMin) return;
 double RS = sqrt(S);

// xx      Del  = Delta(S, F1m2, F2m2)
//-----------------------------------------------------------------------------
// replace delta by form that should be less sensitive to round-off (jcp 10/2013)
 A = S;
 B = F1m2;
 C = F2m2;
// first make A .ge. B .ge. C 
 if(B > A){
   double tmp = A;
   A = B;
   B = tmp;
 }
 if(C > A){
   double tmp = A;
   A = C;
   C = tmp;
 }
 if(C > B){
   double tmp = B;
   B = C;
   C = tmp;
 }

 delsq = pow((A-B-C), 2.0) - 4.0*B*C;
 if(delsq >= 0.0){
   del = sqrt(delsq);
 }
 else{
   cout<<"Fatal delsq #3 = "<<delsq<<" A,B,C = "<<A<<"  "<<B<<"  "<<C<<endl;
   return;
 }

//-----------------------------------------------------------------------------

 double tLog = - log(4.0*F1m2*S/pow((S+F1m2-F2m2+del), 2.0));   // L_t of ACOT-II
 double uLog = - log(4.0*F2m2*S/pow((S-F1m2+F2m2+del), 2.0));   // L_u of ACOT-II

 double k  = ( Q2 + S)          /(2.0*RS);             //
 double p  = del/(2.0*RS);                             //
 double E1 = ( F1m2 - F2m2 + S) /(2.0*RS);             // Eq.(16) & above
 double E2 = (-F1m2 + F2m2 + S) /(2.0*RS);             //
 double Eq = (-Q2 + S)          /(2.0*RS);             //

  OmgNlo(1) = +tLog * (1.0/2.0 + E1*(E1/k-1.0)/k)                            // !
              +uLog * (1.0/2.0 + E2*(E2/k-1.0)/k)                            // !
              - 2.0 *p *Eq*Eq /(k*k *RS);                                    // !
                                                                             // !
  OmgNlo(2) = (2.0*F1M*F2M/(4.0*k*k*S))                                      // !
            * ((tLog + uLog)*(-F1m2 - F2m2 + S) - 4.0*p*RS);                 // !   Eq.(18)
                                                                             // !
  OmgNlo(5) = p*(F2m2 - F1m2)/(k*k*RS)                                       // !
   + tLog * (1.0/2.0 + E1*(E1/k-1.0)/k + F1m2*(F2m2-F1m2)/(2.0*k*k*S))       // !
   - uLog * (1.0/2.0 + E2*(E2/k-1.0)/k + F2m2*(F1m2-F2m2)/(2.0*k*k*S));      // !
                                                                             // 
  OmgNlo(3) = p*(pow((F2m2-F1m2), 2.0) + Q2*(2.0*Q2-F1m2-F2m2))/(k*k*Q2*RS)  // !
   - (tLog - uLog)*Eq*(F2m2 - F1m2)/(k*k*RS)                                 // !
   - (tLog + uLog)*(                                                         // !
     (F1m2 + F2m2)*(Q2*Q2 -pow((F2m2-F1m2), 2.0) -2.0*S*k*k) /(4.0*S*Q2*k*k) // !
      - Eq *(F1m2 + F2m2 - pow((F2m2-F1m2), 2.0)/Q2) /(2.0*k*k*RS)           // !   Eq.(19)
      + F1m2*F2m2 /(k*k*S) );                                                // !
                                                                             // !
  OmgNlo(4) = F1M*F2M* ( 2 *p /(k*k*RS)                                      // !
            - (tLog + uLog) *(1/Q2 + (S -F1m2 -F2m2)/(2.0*k*k*S)) );         // !

}

void CalcDIS::AcotSub(int iHadn, int iPrtn, double F1m, double F2m, double x, double Q, double vMu, FortranArray1D<double> &Subtr)
{
//-----------------------------------------------------------------------------
//     Computes singular part of NLO Gluon Fusion Structure Functions Acot05G
//        for one single quark flavor contribution;
//        If this quark flavor is "light", and it contributes to the summation
//        over the incoming partons in the factorization formula, then this contribution
//        must be subtracted.
//        For a given gauge-invariant pair of gluon-fusion diagrams, there are two of
//        singular contributions---one for each quark flavor (the same for NC case).
//        The calling program supplies g2chi, which contains all the flavor dependence;
//        summation over quark flavors is managed in the calling program.
//
//        For notation, see comment lines in Subroutine Acot0Q
//  From ACOT-II paper, except for change of definitions noted in these comments.
//-----------------------------------------------------------------------------

 double ErrEst;
 int iRet;

 double CxActSub_x = x;
 double CxActSub_aMu = vMu;
 int CxActSub_iHad = iHadn;

 xActSub = [&](double z){
//                             -------------
//                                           ! The gluon-->quark splitting fn
   double SpltFn = ( z*z + pow((1.0-z), 2.0) ) /2.0;
//                                           ! The gluon PDF
   double GluPdf  = GetPDF(CxActSub_iHad, 0, CxActSub_x/z, CxActSub_aMu);
//                                           ! The integrand
   return SpltFn * GluPdf / z;
 };

//                                               -----------------
//                                    Limits of convolution integration
 double z0 = x;
 double z1 = 1.0;

//                                            Test these limits
 if(z0 >= z1){
   cout<<"z0 >= z1 in Acot1Sub convolution, z0, z1 = "<<z0<<"  "<<z1<<endl;
   return;
 }

//                   Calculate the convolution integrals for the perturbative Pdf
// Simpson's rule is good enough for this one...
 double PertPdf = SMPSNF(xActSub, z0, z1, 48, ErrEst, iRet);

//                                          ! Add the pertinent factors
 PertPdf = PertPdf * log(pow((CxActSub_aMu/F1m), 2.0));
//                                              ---------------------
//                                      Get the LO irreducible parton amp Omg
//                                      In the SACOT scheme, set quark-parton mass = 0
 double aM1 = 0.0;
 FortranArray1D<double> OmgLo{1, 5};
 Omg0(Q, aM1, F2m, OmgLo);
//                                       ---- Put the two factors together, ----

 for(int i = 1; i <= 5; i++){
   Subtr(i) = OmgLo(i) * PertPdf * TR;
 }
//cout<<"F1m = "<<F1m<<" F2m = "<<F2m<<" x = "<<x<<" Q = "<<Q<<" vMu = "<<vMu<<endl;
//cout<<fixed<<setprecision(6)<<"PertPdf = "<<PertPdf<<endl;
//cout<<"OmgLo = "<<OmgLo[1]<<"  "<<OmgLo[2]<<"  "<<endl;
}



