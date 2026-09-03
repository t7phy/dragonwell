#include "Calculation/CalcDIS.h"

double CalcDIS::A2HGA(double Y)
{
 double DL  = log (Y);
 double DL1 = log (1.0-Y);
                                                                       
 double Value = - 24.89 / Y - 187.8 + 249.6 * Y - 146.8 * DL*DL * DL1
                - 1.556 * DL*DL*DL  - 3.292 * DL*DL  - 93.68 * DL
                - 1.111 * DL1*DL1*DL1 - 0.400 * DL1*DL1 - 2.770 * DL1;

 return Value;
}

double CalcDIS::A2HGC(double Y)
{
 double Value = - 0.006;

 return Value;
}

double CalcDIS::A2Hg_CTEQ(double z, double eps)
{
 double Zeta2 = 1.6449340668482264365;
 double Zeta3 = 1.2020569031595942854;
 double Ca = 3.0;

 double z1=1.0-z;
 double zz=z*z;
 double pqg=1.-2.*z+2.*zz;
 double DL=log(z);
 double DL1=log(z1);
 double DLp=log(1.+z);
 double dlm2u=log(eps);

 //double Li2z=xLi(2,-z);             //dilogarithm
 //double Li2z1=xLi(2,z1);
 //double Li3z= xLi(3,-z);            //trilogarithm
 //double Li3z1= xLi(3,z1);
 //double S12z=snp12(-z);             //Nielsen function
 //double S12z1=snp12(z1);

 double Li2z = std::real(WGPLG(1,1,-z));
 double Li2z1 = std::real(WGPLG(1,1,z1));
 double Li3z = std::real(WGPLG(2,1,-z));
 double Li3z1 = std::real(WGPLG(2,1,z1));
 double S12z = std::real(WGPLG(1,2,-z));
 double S12z1 = std::real(WGPLG(1,2,z1));

 double term1=CF*Tf*((8.*pqg)*DL1-(4.-8.*z+16.*zz)*DL-(2.-8.*z))
     +Ca*Tf*(-(8.*pqg)*DL1-(8.+32.*z)*DL-16./3./z-4.-32.*z
     +124./3.*zz)+Tf*Tf*(-16./3.*pqg);
 double term2=CF*Tf*(8.*pqg*(2.*DL*DL1-DL1*DL1+2.*Zeta2)-(4.-8.*z+16.*zz)
     *DL*DL-32.*z*z1*DL1-(12.-16.*z+32.*zz)*DL-56.+116.*z-80.*zz)
     +Ca*Tf*((16.+32.*z+32.*zz)*(Li2z+DL*DLp)+8.*pqg*DL1*DL1
     +(8.+16.*z)*DL*DL+32.*z*Zeta2+32.*z*z1*DL1
     -(8.+64.*z+352./3.*zz)*DL-160./9./z+16.-200.*z+1744./9.*zz);
 double term3a=CF*Tf*(pqg*(8.*Zeta3+4./3.*pow(DL1, 3.0)-8.*DL1*Li2z1+8.*Zeta2*DL
     -4.*DL*DL1*DL1+2./3.*pow(DL, 3.0)-8.*DL*Li2z1+8.*Li3z1-24.*S12z1)
     +zz*(-16.*Zeta2*DL+4./3.*pow(DL, 3.0)+16.*DL*Li2z1+32.*S12z1)
     -(4.+96.*z-64.*zz)*Li2z1-(4.-48.*z+40.*zz)*Zeta2
     -(8.+48.*z-24.*zz)*DL*DL1+(4.+8.*z-12.*zz)*DL1*DL1
     -(1.+12.*z-20.*zz)*DL*DL-(52.*z-48.*zz)*DL1
     -(16.+18.*z+48.*zz)*DL+26.-82.*z+80.*zz);
 double term3b=Ca*Tf*(pqg*(-4./3.*pow(DL1, 3.0)+8.*DL1*Li2z1-8.*Li3z1)
     +(1.+2.*z+2.*zz)*(-8.*Zeta2*DLp-16.*DLp*Li2z-8.*DL*DLp*DLp
     +4.*DL*DL*DLp+8.*DL*Li2z-8.*Li3z-16.*S12z)
     +(16.+64.*z)*(2.*S12z1+DL*Li2z1)-(4.+8.*z)/3.*pow(DL, 3.0)
     +(8.-32.*z+16.*zz)*Zeta3-(16.+64.*z)*Zeta2*DL+(16.+16.*zz)
     *(Li2z+DL*DLp)+(32./3./z+12.+64.*z-272./3.*zz)*Li2z1
     -(12.+48.*z-260./3.*zz+32./3./z)*Zeta2-4.*zz*DL*DL1
     -(2.+8.*z-10.*zz)*DL1*DL1+(2.+8.*z+46./3.*zz)*DL*DL
     +(4.+16.*z-16.*zz)*DL1-(56./3.+172./3*z+1600./9.*zz)*DL
     -448./27./z-4./3.-628./3.*z+6352./27.*zz);

 double Value = term1*dlm2u*dlm2u +term2*dlm2u +term3a+term3b;

 Value = Value / 4.0;

 return Value;
}

double CalcDIS::A2HqPS_CTEQ(double z, double eps)
{
 double Zeta2 = 1.6449340668482264365;

 double z1 = 1.0 - z;

 double DL = log(z);
 double dlm2u = log(eps);

 //Li2z1=xLi(2,z1)           !dilogarithm
 //S12z1=snp12(z1)
 double Li2z1 = std::real(WGPLG(1,1,z1));
 double S12z1 = std::real(WGPLG(1,2,z1));

 //typro (8+z)-&8(1+z)
 double term2 = CF*TR*(-8.*(1.+ z) * DL-16./3./z - 4.+4.*z+16./3.*z*z);
 double term1 = CF*TR*(8*(1+z)*DL*DL - (8. + 40.*z + 64./3.
                *z*z)*DL-160./9./z + 16. - 48.*z + 448./9.*z*z);
 double term0 = CF*TR*((1.+z)
                *(32.*S12z1+16.*DL*Li2z1 -16.*Zeta2*DL - 4./3.*DL*DL*DL) + (32./3.
                /z +8.-8.*z-32./3.*z*z)*Li2z1 + (-32./3./z -8.+8.*z +32./3.*z*z) 
                *Zeta2+(2.+10.*z+16./3.*z*z)*DL*DL - (56./3. + 88./3. * z   + 
                448./9.*z*z)*DL - 448./27./z - 4./3. -124./3.*z + 1600./27.*z*z);

 double Value = term0+term1*dlm2u+term2*dlm2u*dlm2u;

 Value = Value / 4.0; //HOPPET convention

 return Value;
}






void CalcDIS::DefineFunctions_HoppetSF()
{

// For HQACOT

 sf_A2PShg_vogt = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HGA(z);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = A2HGC(0.0);
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;

   Value = Value / 4.0; // HOPPET convention
#endif

   return Value;
 };

 sf_A2PShg = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){

     // these will need to be sorted out properly
     std::complex<double> s121mz = WGPLG(1, 2, 1.0 - z);
     std::complex<double> s12mz = WGPLG(1, 2, -z);
     std::complex<double> s211mz = WGPLG(2, 1, 1.0 - z);
     std::complex<double> s21mz = WGPLG(2, 1, -z);
     std::complex<double> s111mz = WGPLG(1, 1, 1.0 - z);
     std::complex<double> s11mz = WGPLG(1, 1, -z);

     double lnz = log(z);
     double lnz2 = lnz*lnz;
     double lnz3 = lnz2*lnz;

     double ln1mz = log(1.0 - z);
     double ln1mz2 = ln1mz*ln1mz;
     double ln1mz3 = ln1mz2*ln1mz;
     double ln1pz = log(1.0+z);
     double ln1pz2 = ln1pz*ln1pz;

     double zeta2 = 1.6449340668482264365;
     double zeta3 = 1.2020569031595942854;

     // C_F.T_r  PART                                                        
     std::complex<double> A01=(1-2.0*z+2.0*z*z)*(8.0*zeta3+4.0*ln1mz3/3.0 
                               -8.0*ln1mz*s111mz+8.0*zeta2*lnz-4.0*lnz*ln1mz2+2.0*lnz3 
                               /3.0-8.0*lnz*s111mz+8.0*s211mz-24.0*s121mz);
     std::complex<double> A02=-(4.0+96.0*z-64.0*z*z)*s111mz-(4.0-48.0*z 
                               +40.0*z*z)*zeta2-(8.0+48.0*z-24.0*z*z)*lnz*ln1mz 
                               +(4.0+8.0*z-12.0*z*z)*ln1mz2-(1.0+12.0*z-20.0*z*z) 
                               *lnz2-(52.0*z-48.0*z*z)*ln1mz-(16.0+18.0*z+48.0*z*z) 
                               *lnz+26.0-82.0*z+80.0*z*z+z*z*(-16.0*zeta2*lnz 
                               +4.0*lnz3/3.0+ 16.0*lnz*s111mz+ 32.0*s121mz);

     // c_a.t_r  part                                                        
     std::complex<double> B01=(1.0-2.0*z+2.0*z*z)*(-4.0*ln1mz3/3.0+8.0*ln1mz 
                               *s111mz-8.0*s211mz)+(1.0+2.0*z+2.0*z*z)*(-8.0*zeta2 
                               *ln1pz-16.0*ln1pz*s11mz-8.0*lnz*ln1pz2+
                               4.0*lnz2*ln1pz+8.0*lnz 
                               *s11mz-8.0*s21mz-16.0*s12mz)+(16.0+64.0*z)*(2.0*s121mz 
                               +lnz*s111mz)-(4.0+8.0*z)*lnz3/3.0+(8.0-32.0*z 
                               +16.0*z*z)*zeta3-(16.0+64.0*z)*zeta2*lnz;
     std::complex<double> B02=(16.0*z+16.0*z*z)*(s11mz+lnz*ln1pz)+(32.0/z/3.0+12.0 
                               +64.0*z-272.0*z*z/3.0)*s111mz-(12.0+48.0*z 
                               -260.0*z*z/3.0+32.0/z/3.0)*zeta2-4.0*z*z*lnz*ln1mz 
                               -(2.0+8.0*z-10.0*z*z)*ln1mz2+
                               (2.0+8.0*z+46.0*z*z/3.0)
                               *lnz2+(4.0+16.0*z-16.0*z*z)*ln1mz-(56.0/3.0+172.0*z 
                               /3.0+1600.0*z*z/9.0)*lnz-448.0/z/27.0-4.0/3.0 
                               -628.0*z/3.0+6352.0*z*z/27.0;

     Value = std::real(TR*(CF*(A01+A02) + CA*(B01+B02)));
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

 sf_A2PShq = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){

     // these will need to be sorted out properly
     std::complex<double> S121MZ = WGPLG(1, 2, 1.0 - z);
     std::complex<double> S111MZ = WGPLG(1, 1, 1.0 - z);

     double lnz = log(z);
     double lnz2 = lnz*lnz;
     double lnz3 = lnz2*lnz;

     double Zeta2 = 1.6449340668482264365;

     // C_F.T_r  PART                                                        
     std::complex<double> A0 = (1.0+z)*(32.0*S121MZ+16.0*lnz*S111MZ-16.0*Zeta2
                               *lnz-4.0*lnz3/3.0)+(32.0/z/3.0+8.0-8.0*z-32.0
                               *z*z/3.0)*S111MZ+(-32.0/z/3.0-8.0+8.0*z
                               +32.0*z*z/3.0)*Zeta2+(2.0+10.0*z+16.0*z*z/3.0)
                               *lnz2-(56.0/3.0+88.0*z/3.0+448.0*z*z/9.0)*lnz
                               -448.0/z/27.0-4.0/3.0-124.0*z/3.0+1600.0*z*z
                               /27.0;

     Value = TR * CF * std::real(A0);
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

 sf_A2Hg_CTEQ = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2Hg_CTEQ(z, (SFHQ_MQ/SFHQ_Mu) * (SFHQ_MQ/SFHQ_Mu));
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;
#endif

   return Value;
 };

 sf_A2HqPS_CTEQ = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double z = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = A2HqPS_CTEQ(z, (SFHQ_MQ/SFHQ_Mu) * (SFHQ_MQ/SFHQ_Mu));
   }
   
   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * z;
#endif

   return Value;
 };

// For F2FL_ZM

 cf_CqF2MSbar = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     double lnx = log(x);
     double ln1mx = log(1.0 - x);
     Value = CF*(2.0*(ln1mx/(1.0-x)) - 1.5/(1.0-x) - (1.0+x)*ln1mx
             - (1.0+x*x)/(1.0-x)*lnx + 3.0 + 2.0*x);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
     double ln1mx = log(1.0 - x); // spiacente di farlo due volte
     Value = Value - CF*(2.0*(ln1mx/(1.0-x)) - 1.5/(1.0-x));
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = -CF*(Pi*Pi/3.0 + 9.0*0.5);
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 cf_CgF2MSbar = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     double lnx = log(x);
     double ln1mx = log(1.0 - x);
     Value = TR*(((1.0-x)*(1.0-x)+x*x)*(ln1mx-lnx)-8.0*x*x+8.0*x-1.0);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 cf_CqFL = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = 2.0 * CF * x;
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 cf_CgFL = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = 4.0 * TR * x * (1.0 - x);
   }

   if(hoppet_cc_piece == hoppet::cc_VIRT || hoppet_cc_piece == hoppet::cc_REALVIRT){
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 cf_CqF3minusF2 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL || hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = Value - CF * (1.0 + x);
   }

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 cf_CqF3 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   Value = cf_CqF3minusF2(y, hoppet_cc_piece) + cf_CqF2MSbar(y, hoppet_cc_piece);
#endif

   return Value;
 };


 isDefineFunctions_HoppetSF = true;
}

