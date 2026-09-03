#include "Calculation/CalcDIS.h"

double CalcDIS::AnalyticC1A1(double z)
{
   double eps = pow((SFHQ_MQ / SFHQ_Mu), 2.0); //m^2/mu^2
   double QQ = SFHQ_QQ;
   double bmu = SFHQ_Mu;
   double Zeta2=1.6449340668482264365;

   double z1 = z;

   double ConvC1A1 = CF*Tf*(20.0 - 48.0*z1 + 64.0*z1*z1 + 24.0*Zeta2
       - 48.0*z1*Zeta2 + 64.0*z1*z1*Zeta2 + 28.0*log(1.0 - z1)
       - 64.0*z1*log(1.0 - z1)
       + 48.0*z1*z1*log(1.0 - z1) - 8.0*pow(log(1.0 - z1), 2.0)
       + 16.0*z1*pow(log(1.0 - z1), 2.0)
       - 16.0*z1*z1*pow(log(1.0 - z1), 2.0)
       + 4.0*log(z1) + 32.0*z1*log(z1)
       - 48.0*z1*z1*log(z1)- 4.0*pow(log(z1), 2.0) + 8.0*z1*pow(log(z1), 2.0)
       - 16.0*z1*z1*pow(log(z1), 2.0) - 16.0*xLi(2,1.0 - z1)
       + 32.0*z1*xLi(2,1.0 - z1) - 32.0*z1*z1*xLi(2,1.0 - z1)
       - 8.0*xLi(2,z1)+ 16.0*z1*xLi(2,z1) - 32.0*z1*z1*xLi(2,z1))
       *log(eps);

   if(QQ != bmu){
      ConvC1A1 = ConvC1A1 + CF*Tf*(4.0 - 16.0*z1 - 16.0*log(1.0 - z1)
         + 32.0*z1*log(1.0 - z1) - 32.0*z1*z1*log(1.0 - z1)
         + 8.0*log(z1) - 16.0*z1*log(z1)
         + 32.0*z1*z1*log(z1))*log(eps)*log(QQ*QQ/bmu/bmu);
   }

   return ConvC1A1;
}

double CalcDIS::A2HgL0(double z)
{
 double Zeta3 = 1.2020569031595942854;

 double Value = 0.0;

 std::complex<double> res;

 res = CA*TR*(-1.3333333333333333-448.0/(27.0*z)-(628.0*z)/3.+(6352.0*z*z)/27.0- 
 (Pi*Pi*(12.0+32.0/(3.*z)+48.0*z-(260.0*z*z)/3.0))/6.+(4.0+16.0*z-16.0*z*z)*log(1.0-z)- 
 (2.0+8.0*z-10.0*z*z)*log(1.0-z)*log(1.0-z)-(Pi*Pi*(16.0+64.0*z)*log(z))/6.- 
 (18.666666666666668+(172.0*z)/3.+(1600.0*z*z)/9.0)*log(z)-4*z*z*log(1- 
 z)*log(z)+(2.0+8.0*z+(46.0*z*z)/3.0)*log(z)*log(z)-(1.3333333333333333+ 
 (8*z)/3.)*log(z)*log(z)*log(z)+(12.0+32.0/(3.*z)+64*z-(272*z*z)/3.)*WGPLG(1,1,1-z)+(16 
 +64*z)*(2.0*WGPLG(1,2,1-z)+log(z)*WGPLG(1,1,1-z))+(16*z+ // yfu change 16*z to 16
// +64*z)*(2.0*WGPLG(1,2,1-z)+log(z)*WGPLG(1,1,1-z))+(16+ // yfu new
 16*z*z)*(log(z)*log(1+z)+WGPLG(1,1,-z))+(1-2*z+2*z*z)*((-4*log(1- 
 z)*log(1-z)*log(1-z))/3.+8.0*log(1-z)*WGPLG(1,1,1-z)-8.0*WGPLG(2,1,1-z))+(1+2*z+ 
 2*z*z)*(-16.0*WGPLG(1,2,-z)-(4*Pi*Pi*log(1+z))/3.+4*log(z)*log(z)*log(1+z)- 
 8*log(z)*log(1+z)*log(1+z)+8*log(z)*WGPLG(1,1,-z)-16.0*log(1+z)*WGPLG(1,1,-z)- 
 8.0*WGPLG(2,1,-z))+(8-32*z+16*z*z)*Zeta3)+CF*TR*(26-82*z+80*z*z- 
 (Pi*Pi*(4-48*z+40*z*z))/6.-(52*z-48*z*z)*log(1-z)+(4+8*z- 
 12*z*z)*log(1-z)*log(1-z)-(16+18*z+48*z*z)*log(z)-(8+48*z-24*z*z)*log(1- 
 z)*log(z)-(1+12*z-20*z*z)*log(z)*log(z)-(4+96*z-64*z*z)*WGPLG(1,1,1-z)+ 
 z*z*(32.0*WGPLG(1,2,1-z)-(8*Pi*Pi*log(z))/3.+(4*log(z)*log(z)*log(z))/3.+ 
 16.0*log(z)*WGPLG(1,1,1-z))+(1-2*z+2*z*z)*(-24.0*WGPLG(1,2,1-z)+(4*log(1- 
 z)*log(1-z)*log(1-z))/3.+(4*Pi*Pi*log(z))/3.-4*log(1-z)*log(1-z)*log(z)+(2*log(z)*log(z)*log(z))/3.- 
 8.0*log(1-z)*WGPLG(1,1,1-z)-8.0*log(z)*WGPLG(1,1,1-z)+8.0*WGPLG(2,1,1-z)+ 
 8*Zeta3));

 Value = std::real(res);

 return Value;
}

double CalcDIS::A2HgL1(double z)
{
 double Value = 0.0;

 std::complex<double> res;

 res = CF*TR*(-56+116*z-80*z*z-32*(1-z)*z*log(1-z)-(12-16*z+32*z*z)*log(z)-(4 
 -8*z+16*z*z)*log(z)*log(z)+(8-16*z+16*z*z)*(Pi*Pi/3.-log(1-z)*log(1-z)+2*log(1- 
 z)*log(z)))+CA*TR*(16-160/(9.*z)-200*z+(16*Pi*Pi*z)/3.+(1744*z*z)/9.+ 
 32*(1-z)*z*log(1-z)+(8-16*z+16*z*z)*log(1-z)*log(1-z)-(8+64*z+ 
 (352*z*z)/3.)*log(z)+(8+16*z)*log(z)*log(z)+(16+32*z+32*z*z)*(log(z)*log(1 
 +z)+WGPLG(1,1,-z)));

 Value = std::real(res);

 return Value;
}

double CalcDIS::A2HgL2(double z)
{
 double Value = (-16*TR*TR*((1-z)*(1-z)+z*z))/3.+CA*TR*(-4-16/(3.*z)-32*z+(124*z*z)/3.+ 
 (-8+16*z-16*z*z)*log(1-z)-(8+32*z)*log(z))+CF*TR*(-2+8*z+(8-16*z+ 
 16*z*z)*log(1-z)-(4-8*z+16*z*z)*log(z));

 return Value;
}

double CalcDIS::A2HqPSL0(double z)
{
 double Value = 0.0;

 std::complex<double> res;

 res = CF*TR*(-1.3333333333333333-448/(27.*z)-(124*z)/3.+(1600*z*z)/27.+ 
 (Pi*Pi*(-8-32/(3.*z)+8*z+(32*z*z)/3.))/6.-(18.666666666666668+(88*z)/3. 
 +(448*z*z)/9.)*log(z)+(2+10*z+(16*z*z)/3.)*log(z)*log(z)+(8+32/(3.*z)-8*z- 
 (32*z*z)/3.)*WGPLG(1,1,1-z)+(1+z)*(32.0*WGPLG(1,2,1-z)- 
 (8*Pi*Pi*log(z))/3.-(4*log(z)*log(z)*log(z))/3.+16*log(z)*WGPLG(1,1,1-z)));

 Value = std::real(res);

 return Value;

}

double CalcDIS::A2HqPSL1(double z)
{
 double Value = CF*TR*(16-160/(9.*z)-48*z+(448*z*z)/9.-(8+40*z+(64*z*z)/3.)*log(z)+ 
 8*(1+z)*log(z)*log(z)); // yfu change 8+8z to 8+z
// (8.0+z)*log(z)*log(z)); // yfu new

 return Value;
}

double CalcDIS::A2HqPSL2(double z)
{
 double Value = CF*TR*(-4-16/(3.*z)+4*z+(16*z*z)/3.-8*(1+z)*log(z));

 return Value;
}

void CalcDIS::DefineFunctions_OME()
{
 sf_Pqg = [&](double y, int hoppet_cc_piece){
   double x = exp(-y);
   double Value = 0.0;
   double tr = 0.5;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = tr * (x * x + (1.0 - x) * (1.0 - x));
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value - 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_Pgq = [&](double y, int hoppet_cc_piece){
   double x = exp(-y);
   double Value = 0.0;
   double cf = 4.0 / 3.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = cf * (1.0 + (1.0 - x) * (1.0 - x)) / x;
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value - 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_Pgg = [&](double y, int hoppet_cc_piece){
   double x = exp(-y);
   double Value = 0.0;
   double cf = 4.0 / 3.0;
   double ca = 3.0;
   int nf = SFHQ_nfl;
   double tr = 0.5;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = 2.0 * ca * (x / (1.0 - x) + (1.0 - x) / x + x * (1.0 - x));
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value - 2.0 * ca * 1.0 / (1.0 - x);
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = (11.0 * ca - 4.0 * nf * tr) / 6.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_Pqq = [&](double y, int hoppet_cc_piece){
   double x = exp(-y);
   double Value = 0.0;
   double cf = 4.0 / 3.0;
   double ca = 3.0;
   int nf = SFHQ_nfl;
   double tr = 0.5;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = cf * (1.0 + x * x) / (1.0 - x);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value - cf * 2.0 / (1.0 - x);
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = cf * 3.0 * 0.5;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_P1gg = [&](double y, int hoppet_cc_piece){
   double x = exp(-y);
   double Value = 0.0;
   double cf = 4.0 / 3.0;
   double ca = 3.0;
   int nf = SFHQ_nfl;
   double tr = 0.5;
   double Zeta3 = 1.2020569031595942854;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     double lnx = log(x);
     double ln1mx = log(1.0 - x);
     double pgg   = (1.0 / (1.0 - x) + 1.0/x -2.0 + x*(1.0-x));
     double pggmx = (1.0 / (1.0 + x) - 1.0/x -2.0 - x*(1.0+x));
     double S2x   = -2.0*xLi(2,-x) + 0.5 * lnx*lnx - 2.0*lnx*log(1.0+x) - Pi*Pi /6.0;

     Value = CF*Tf*(-16.0 + 4/(3.0*x) + 8*x + (20*x*x)/3.0 - lnx*lnx*(2
            + 2*x)- lnx*(6 + 10*x)) + CA*Tf*(2 - (20*pgg)/9.0 - 2*x -
            (4*lnx*(1 + x))/3.0 + (26*(-(1/x) + x*x))/9.0) + CA*CA
            *(pgg*(7.444444444444445 - 4*ln1mx*lnx + lnx*lnx - Pi*Pi
            /3.0) + 2*pggmx*S2x + (27*(1 - x))/2.0 + 4*lnx*lnx*(1 + x)
            + (67*(-(1/x) + x*x))/9.0 - lnx*(8.333333333333334 -
            (11*x)/3.0 + (44*x*x)/3.0));
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     double dpgg = -1.0/(1.0-x);
     Value = Value + CA*CA*dpgg*(67.0/9.0 - Pi*Pi/3.0) - (20*CA
            *dpgg*Tf)/9.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = (-4*CA*Tf)/3.0 - CF*Tf + CA*CA*(8.0/3.0
            + 3*Zeta3);
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_P1gq = [&](double y, int hoppet_cc_piece){
   double x = exp(-y);
   double Value = 0.0;
   double cf = 4.0 / 3.0;
   double ca = 3.0;
   int nf = SFHQ_nfl;
   double tr = 0.5;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)

   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     double lnx = log(x);
     double ln1mx = log(1.0 - x);
     double pgq   = (1.0 + (1.0-x)*(1.0-x))/x;
     double pgqmx = -(1.0 + (1.0+x)*(1.0+x))/x;
     double S2x   = -2.0*xLi(2,-x) + 0.5 * lnx*lnx - 2.0*lnx*log(1.0+x) - Pi*Pi /6.0;
     Value = CF*Tf*(-((2.2222222222222223 + (4*ln1mx)/3.0)*pgq) - (4
            *x)/3.0) + CF*CF*(-2.5 - (3*ln1mx + ln1mx*ln1mx)*pgq - lnx
            *lnx*(1 - x/2.0) - (7*x)/2.0 - 2*ln1mx*x + lnx*(2 + (7*x)
            /2.0)) + CA*CF*(3.111111111111111 + pgq*(0.5 + (11
            *ln1mx)/3. + ln1mx*ln1mx - 2*ln1mx*lnx + lnx*lnx/2.0 - Pi*Pi
            /6.0) + pgqmx*S2x + (65*x)/18.0 + 2*ln1mx*x + (44*x*x)
            /9.0 + lnx*lnx*(4 + x) - lnx*(12 + 5*x + (8*x*x)/3.0));
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value + 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_A1Hg = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;

   double x = exp(-y);
   Value = -2.0 * sf_Pqg(y, hoppet_cc_piece); //with as=alfas/2pi and f_{H+Hb}

   return Value;
 };

 sf_a1bhg = [&](double y, int hoppet_cc_piece){
   double zeta2 = 1.6449340668482264365;
 
   double Value = 0.0;
 
   double x = exp(-y);
   Value = -1.0 / 8.0 * zeta2 * sf_Pqg(y, hoppet_cc_piece); //xPqg
 
   return Value;
 };

 sf_AnalyticC1A1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = AnalyticC1A1(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2HgL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HgL0(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2HgL1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HgL1(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2HgL2 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HgL2(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2HqPSL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HqPSL0(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2HqPSL1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HqPSL1(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2HqPSL2 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HqPSL2(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A3HgLL = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = VFNSmod_QG(z, (double)SFHQ_nfl, SFHQ_asA3 / 2.0, SFHQ_LL);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 8.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A3HqPSLL = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = VFNSmod_PS(z, (double)SFHQ_nfl, SFHQ_asA3 / 2.0, SFHQ_LL);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 8.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A3HgL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     //Value = VFNSmod_AQG(z, (double)SFHQ_nfl, SFHQ_asA3 / 2.0, SFHQ_LL);
     Value = aQg30new(z) * SFHQ_asA3 * SFHQ_asA3 * SFHQ_asA3; // same as Hoppet alphas2pi convention, factor of 2 is divided later
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 8.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A3HqPSL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = VFNSmod_APS1(z, (double)SFHQ_nfl, SFHQ_asA3 / 2.0, SFHQ_LL) + VFNSmod_APS2(z, (double)SFHQ_nfl, SFHQ_asA3 / 2.0, SFHQ_LL);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 8.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A3Hg_ome = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = ome_AQg_reg_coeff_as(3, SFHQ_LL, (double)SFHQ_nfl, z) * SFHQ_asA3 * SFHQ_asA3 * SFHQ_asA3;
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 8.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A3HqPS_ome = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = ome_AQqPS_reg_coeff_as(3, SFHQ_LL, (double)SFHQ_nfl, z) * SFHQ_asA3 * SFHQ_asA3 * SFHQ_asA3;
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 8.0; // HOPPET convention
#endif

   return Value;
 };

 isDefineFunctions_OME = true;
}


