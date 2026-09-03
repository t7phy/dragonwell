#include "Calculation/CalcDIS.h"

//
//-----------------------------------------------------------------------
// On the next-to-next-to-leading order QCD corrections     
// to heavy-quark production in deep-inelastic 
//    
// H. Kawamura, N. Lo Presti, S. Moch and A. Vogt
//-----------------------------------------------------------------------    
//
// The high-energy (small-x) limit of the 2-loop gluon coefficient function: 
// c2g2 in Eqs. (3.39) and (3.41)
//
//-----------------------------------------------------------------------
// ..The small-x piece of the 2-loop hq coefficient function: c2g2 
//   power ln(mu)^0
//
double CalcDIS::chx0g2(double x, double xi)
{
 int n1 = -1, n2 = 1, nw = 5;
 hplog5::CArr<1> Hc1; hplog5::CArr<2> Hc2; hplog5::CArr<3> Hc3; hplog5::CArr<4> Hc4; hplog5::CArr<5> Hc5;
 hplog5::HArr<1> Hr1; hplog5::HArr<2> Hr2; hplog5::HArr<3> Hr3; hplog5::HArr<4> Hr4; hplog5::HArr<5> Hr5;
 hplog5::HArr<1> Hi1; hplog5::HArr<2> Hi2; hplog5::HArr<3> Hi3; hplog5::HArr<4> Hi4; hplog5::HArr<5> Hi5;

 double z2 = 1.6449340668482264365;
 double z3 = 1.2020569031595942854;
 double z4 = 1.0823232337111381916;
 double z5 = 1.0369277551433699263;
 double pi = 3.14159265359;

 // ...Colour factors
 //
 double ca  = 3.0;
 double cf  = 4.0/3.0;
 double tf  = 1.0/2.0;

 // ...Some abbreviations
 //
 double LQm = log(xi);
 double argHPL = sqrt(xi/(xi+4.0));

 // ...The harmonic polylogs up to weight
 //
 hplog5Wrapper(argHPL, nw,
               Hc1, Hc2, Hc3, Hc4, Hc5,
               Hr1, Hr2, Hr3, Hr4, Hr5,
               Hi1, Hi2, Hi3, Hi4, Hi5,
               n1, n2);

 double Jfunction = 4.0/xi*argHPL*( Hr1(-1) + Hr1(1) );
 double Ifunction = 4.0/xi*argHPL*( Hr2(1,1) + Hr2(1,-1)
                   -Hr2(-1,1) - Hr2(-1,-1) );
 double Kfunction = 4.0/xi*argHPL*( Hr3(1,1,1) - Hr3(1,1,-1)
                  + Hr3(1,-1,1)  - Hr3(1,-1,-1)
                  - Hr3(-1,1,1)  + Hr3(-1,1,-1)
                  - Hr3(-1,-1,1) + Hr3(-1,-1,-1) );
 // Eq. (3.39)
 double Value = ca*ca * log(x) * 1.0/(32.0*pi*pi*pi) * (
              - 184.0/(27.0*xi)
              - 1.0/(3.0) * (1.0 - 1.0/xi) * Ifunction * log(1.0 + xi/4.0)
              - 1.0/(9.0) * (13.0 - 10.0/xi) * Ifunction
              - 1.0/(27.0) * (71.0 - 92.0/xi) * Jfunction
              + 1.0/(3.0) * (1.0 - 1.0/xi) * Kfunction );
 // asymptotics Eq. (3.41)
 //      chx0g2 = chx0g2 + ca**2 * dlog(x)/(256d0*pi**3) /xi * (
 //     & 32d0/9d0*LQm**3 + 208d0/9d0*LQm**2 
 //     & + (2272d0/27d0-64d0/3d0*z2)*LQm + 1472d0/27d0 - 416d0/9d0*z2 
 //     & + 128d0/3d0*z3 )

 return Value;
}

//
//-----------------------------------------------------------------------
// ..The small-x piece of the 2-loop hq coefficient function: c2g2 
//   from Catani and Hautmann
//   power ln(mu)^1
//
double CalcDIS::chxbg2(double x, double xi)
{
 int n1 = -1, n2 = 1, nw = 5;
 hplog5::CArr<1> Hc1; hplog5::CArr<2> Hc2; hplog5::CArr<3> Hc3; hplog5::CArr<4> Hc4; hplog5::CArr<5> Hc5;
 hplog5::HArr<1> Hr1; hplog5::HArr<2> Hr2; hplog5::HArr<3> Hr3; hplog5::HArr<4> Hr4; hplog5::HArr<5> Hr5;
 hplog5::HArr<1> Hi1; hplog5::HArr<2> Hi2; hplog5::HArr<3> Hi3; hplog5::HArr<4> Hi4; hplog5::HArr<5> Hi5;

 double z2 = 1.6449340668482264365;
 double z3 = 1.2020569031595942854;
 double z4 = 1.0823232337111381916;
 double z5 = 1.0369277551433699263;
 double pi = 3.14159265359;

 // ...Colour factors
 //
 double ca  = 3.0;
 double cf  = 4.0/3.0;
 double tf  = 1.0/2.0;

 // ...Some abbreviations
 //
 double LQm = log(xi);
 double argHPL = sqrt(xi/(xi+4.0));

 // ...The harmonic polylogs up to weight
 //
 hplog5Wrapper(argHPL, nw,
               Hc1, Hc2, Hc3, Hc4, Hc5,
               Hr1, Hr2, Hr3, Hr4, Hr5,
               Hi1, Hi2, Hi3, Hi4, Hi5,
               n1, n2);

 double Jfunction = 4.0/xi*argHPL*( Hr1(-1) + Hr1(1) );
 double Ifunction = 4.0/xi*argHPL*( Hr2(1,1) + Hr2(1,-1)
                   -Hr2(-1,1) - Hr2(-1,-1) );
 double Kfunction = 4.0/xi*argHPL*( Hr3(1,1,1) - Hr3(1,1,-1)
                  + Hr3(1,-1,1)  - Hr3(1,-1,-1)
                  - Hr3(-1,1,1)  + Hr3(-1,1,-1)
                  - Hr3(-1,-1,1) + Hr3(-1,-1,-1) );
 // Eq. (3.39)
 double Value = ca*ca * log(x) * 1.0/(32.0*pi*pi*pi) * (
              - 20.0/(9.0*xi)
              - 2.0/3.0 * (1.0 - 1.0/xi) * Ifunction
              - 1.0/9.0 * (13.0 - 10.0/xi) * Jfunction );
 // asymptotics Eq. (3.41)
 //double Value = ca*ca * log(x)/(256.0*pi*pi*pi) /xi * (
 //      + 32.0/3.0 * LQm*LQm + 416.0/9.0 * LQm
 //      + 160.0/9.0 - 64.0/3.0 * z2 );

 return Value;
}

//
//-----------------------------------------------------------------------
// ..The small-x piece of the 2-loop hq coefficient function: c2g2 
//   from Catani and Hautmann
//   power ln(mu)^2
//
double CalcDIS::chxbbg2(double x, double xi)
{
 int n1 = -1, n2 = 1, nw = 5;
 hplog5::CArr<1> Hc1; hplog5::CArr<2> Hc2; hplog5::CArr<3> Hc3; hplog5::CArr<4> Hc4; hplog5::CArr<5> Hc5;
 hplog5::HArr<1> Hr1; hplog5::HArr<2> Hr2; hplog5::HArr<3> Hr3; hplog5::HArr<4> Hr4; hplog5::HArr<5> Hr5;
 hplog5::HArr<1> Hi1; hplog5::HArr<2> Hi2; hplog5::HArr<3> Hi3; hplog5::HArr<4> Hi4; hplog5::HArr<5> Hi5;

 double z2 = 1.6449340668482264365;
 double z3 = 1.2020569031595942854;
 double z4 = 1.0823232337111381916;
 double z5 = 1.0369277551433699263;
 double pi = 3.14159265359;

 // ...Colour factors
 //
 double ca  = 3.0;
 double cf  = 4.0/3.0;
 double tf  = 1.0/2.0;

 // ...Some abbreviations
 //
 double LQm = log(xi);
 double argHPL = sqrt(xi/(xi+4.0));

 // ...The harmonic polylogs up to weight
 //
 hplog5Wrapper(argHPL, nw,
               Hc1, Hc2, Hc3, Hc4, Hc5,
               Hr1, Hr2, Hr3, Hr4, Hr5,
               Hi1, Hi2, Hi3, Hi4, Hi5,
               n1, n2);

 double Jfunction = 4.0/xi*argHPL*( Hr1(-1) + Hr1(1) );
 double Ifunction = 4.0/xi*argHPL*( Hr2(1,1) + Hr2(1,-1)
                   -Hr2(-1,1) - Hr2(-1,-1) );
 double Kfunction = 4.0/xi*argHPL*( Hr3(1,1,1) - Hr3(1,1,-1)
                  + Hr3(1,-1,1)  - Hr3(1,-1,-1)
                  - Hr3(-1,1,1)  + Hr3(-1,1,-1)
                  - Hr3(-1,-1,1) + Hr3(-1,-1,-1) );
 // Eq. (3.39)
 double Value = ca*ca * log(x) * 1.0/(32.0*pi*pi*pi) * (
              - 2.0/(3.0*xi)
              - 1.0/3.0 * (1.0 - 1.0/xi) * Jfunction );
 // asymptotics Eq. (3.41)
 //      chxbbg2 = chxbbg2 + ca**2 * dlog(x)/(256d0*pi**3) /xi * (
 //     &     32d0/3d0 * LQm + 16d0/3d0 )

 return Value;
}
