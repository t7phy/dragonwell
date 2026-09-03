#include "Calculation/hplog5.h"

namespace hplog5 {

 hplog5::hplog5()
 {

 }

 //****************************************************************************
 //  hplog5: a subroutine for the evaluation of harmonic polylogarithms
 //          Version 1.0         15/11/2001
 //  upgraded to w=5 from hplog as described in:
 //  T.Gehrmann and E.Remiddi: Numerical Evaluation of the Harmonic
 //                            Polylogarithms up to Weight 4
 //                            (hep-ph/0107173; Comp.Phys.Comm. 141 (2001) 296)
 //  the harmonic polylogarithms are defined in:
 //  E.Remiddi and J.Vermaseren: Harmonic Polylogarithms
 //                            (hep-ph/9905237; Int.J.Mod.Phys. A15 (2000) 725)
 //  email:
 //  Thomas.Gehrmann@cern.ch and Ettore.Remiddi@bo.infn.it
 //
 //****************************************************************************
 void hplog5::mainWrapper(double x, int nw,
                          CArr<1>& Hc1, CArr<2>& Hc2, CArr<3>& Hc3, CArr<4>& Hc4, CArr<5>& Hc5,
                          HArr<1>& Hr1, HArr<2>& Hr2, HArr<3>& Hr3, HArr<4>& Hr4, HArr<5>& Hr5,
                          HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5,
                          int n1, int n2)
 {
  //****
  // x is the argument of the 1dHPL's (1 dimensional Harmonic PolyLogarithms)
  //   to be evaluated;
  // nw is the maximum weight of the required 1dHPL's;
  //    the maximum allowed value of nw of this implementation is 5;
  // Hc1,Hc2,Hc3,Hc4,Hc5 are the complex*16 values of the 1dHPL;
  //    they must all be supplied in the arguments even if some of them
  //    are not to be evaluated;
  // Hr1,Hr2,Hr3,Hr4,Hr5 are the double precision real parts of
  //    Hc1,Hc2,Hc3,Hc4,Hc5;
  // Hi1,Hi2,Hi3,Hi4,Hi5 are the double precision immaginary parts of
  //    Hc1,Hc2,Hc3,Hc4,Hc5 divided by pi=3.114159....
  // n1,n2 is the required range of indices, the allowed ranges are
  //    (0,1), (-1,0), (-1,1) ;
  //****

  constexpr double r2 = 1.4142135623730950488; // sqrt(2)

  if(nw < 1 || nw > 5) {
    throw std::invalid_argument("hplog5: nw must be 1..5");
  }

  // range checks (matches Fortran)
  if( (n1==-1 && n2==0) ) {
    fillred.infilldim = 2;
    fillred.infill = {0, 0, -1, 0};
  } else if( (n1==0 && n2==1) ) {
    fillred.infilldim = 2;
    fillred.infill = {0, 0, 1, 0};
  } else if( (n1==-1 && n2==1) ) {
    fillred.infilldim = 3;
    fillred.infill = {0, 0, -1, 1};
  } else {
    throw std::invalid_argument("hplog5: allowed (n1,n2) are (-1,0),(0,1),(-1,1)");
  }

  // init array index metadata
  Hc1.init(n1,n2); Hc2.init(n1,n2); Hc3.init(n1,n2); Hc4.init(n1,n2); Hc5.init(n1,n2);
  Hr1.init(n1,n2); Hr2.init(n1,n2); Hr3.init(n1,n2); Hr4.init(n1,n2); Hr5.init(n1,n2);
  Hi1.init(n1,n2); Hi2.init(n1,n2); Hi3.init(n1,n2); Hi4.init(n1,n2); Hi5.init(n1,n2);

  // setting the immaginary parts equal to zero
  psetzero(nw,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);

  // looking at the range of the argument
  //      r2 = sqrt(2.d0)
  double r2m1 = r2 - 1.0;
  double r2p1 = r2 + 1.0;

  if( (x > -r2m1) && (x <= r2m1) ) {
    peval1dhplat0(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  } else if( x == 1.0 ) {
    peval1dhplin1(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  } else if( (x > r2m1) && (x <= r2p1) ) {
    peval1dhplat1(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  } else if( x > r2p1 ) {
    peval1dhplatinf(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  } else if( x <= -r2p1 ) {
    peval1dhplatminf(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  } else if( x == -1.0 ) {
    peval1dhplinm1(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  } else if( (x > -r2p1) && (x <= -r2m1) ) {
    peval1dhplatm1(x,nw,Hc1,Hc2,Hc3,Hc4,Hc5,Hr1,Hr2,Hr3,Hr4,Hr5,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2);
    return;
  }

 }

 void hplog5::peval1dhplat0(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                             HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                             HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's in the 0-range  -(r2-1) < y <= (r2-1)
  // by direct series expansion (Bernoulli-accelerated)
  pfillh1(y, H1, HY1, Hi1, n1, n2);
  if ( nw == 1 ) return;

  pfillirr1dhplat0(y, nw, HY1, HY2, HY3, HY4, HY5, n1, n2);
  // then the reducible 1dHPL's
  pfillred1dhpl(nw, H1, H2, H3, H4, H5,
                    HY1, HY2, HY3, HY4, HY5,
                    Hi1, Hi2, Hi3, Hi4, Hi5, n1, n2);
 }

 void hplog5::peval1dhplin1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                             HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                             HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's for y=1 (explicit values are tabulated)
  double pi = 3.14159265358979324;
  // evaluate the irreducible 1dHPL's first
  pfillh1(y, H1, HY1, Hi1, n1, n2);
  if ( nw == 1 ) return;
  pfillirr1dhplin1(y, nw, HY1, HY2, HY3, HY4, HY5, n1, n2);
  // then the reducible 1dHPL's
  pfillred1dhpl(nw, H1, H2, H3, H4, H5,
                    HY1, HY2, HY3, HY4, HY5,
                    Hi1, Hi2, Hi3, Hi4, Hi5, n1, n2);
  if (n2 == 0) return;
  // correct the ill-defined entries
  HY2(1,0) = - HY2(0,1);
  Hi2(1,0) = 0.0;
  H2(1,0) = cdouble(HY2(1,0), Hi2(1,0)*pi);
  if ( nw == 2 ) return;
  HY3(1,0,0) = HY3(0,0,1);
  Hi3(1,0,0) = 0.0;
  H3(1,0,0) = cdouble(HY3(1,0,0), Hi3(1,0,0)*pi);
  if ( nw == 3 ) return;
  HY4(1,0,0,0) = -HY4(0,0,0,1);
  Hi4(1,0,0,0) = 0.0;
  H4(1,0,0,0) = cdouble(HY4(1,0,0,0), Hi4(1,0,0,0)*pi);
  if ( nw == 4 ) return;
  HY5(1,0,0,0,0) = HY5(0,0,0,0,1);
  Hi5(1,0,0,0,0) = 0.0;
  H5(1,0,0,0,0) = cdouble(HY5(1,0,0,0,0), Hi5(1,0,0,0,0)*pi);
 }

 void hplog5::peval1dhplat1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                             HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                             HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's in the 1-range  (r2-1) < y <= (r2+1)
  // evaluating first the H(..,r=(1-y)/(1+y)) by calling eval1dhplat0(r)
  // and then expressing H(..,y=(1-r)/(1+r)) in terms of H(..,r)

  // additional arrays required within this routine
  HArr<1> HR1; HArr<2> HR2; HArr<3> HR3; HArr<4> HR4; HArr<5> HR5;
  HR1.init(-1,1); HR2.init(-1,1); HR3.init(-1,1); HR4.init(-1,1); HR5.init(-1,1);
  // the nw = 1 case
  pfillh1(y, H1, HY1, Hi1, n1, n2);
  if ( nw == 1 ) return;
  // the nw > 1 case
  double r = (1.0 - y) / (1.0 + y);
  //      print*,' eval1dhplat1: y = ',y,', r = ',r
  // the whole (-1,1) range is in general needed for any pair (n1,n2)
  pfillirr1dhplat0(r, nw, HR1, HR2, HR3, HR4, HR5, -1, 1);
  // fillirr1dhplat1 takes care automatically of all the immaginary
  // parts as well as of the jump across y=1
  pfillirr1dhplat1(r, nw, HR1, HR2, HR3, HR4, HR5,
                          HY1, HY2, HY3, HY4, HY5,
                          Hi1, Hi2, Hi3, Hi4, Hi5, n1, n2);
  // then the reducible 1dHPL's
  pfillred1dhpl(nw, H1, H2, H3, H4, H5,
                    HY1, HY2, HY3, HY4, HY5,
                    Hi1, Hi2, Hi3, Hi4, Hi5, n1, n2);
 }

 void hplog5::peval1dhplatinf(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                               HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                               HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's in the inf-range  (r2+1) < abs(y)
  // evaluating first the H(..,x=1/y) by calling eval1dhplat0(x)
  // and then expressing H(..,y=1/x) in terms of H(..,x)

  // additional arrays required within this routine
  HArr<1> HX1; HArr<2> HX2; HArr<3> HX3; HArr<4> HX4; HArr<5> HX5;
  HX1.init(n1,n2); HX2.init(n1,n2); HX3.init(n1,n2); HX4.init(n1,n2); HX5.init(n1,n2);

  double pi = 3.14159265358979324;
  // the nw = 1 case
  pfillh1(y, H1, HY1, Hi1, n1, n2);
  if ( nw == 1 ) return;
  // the nw > 1 case
  double x = 1.0 / y;
  //      print*,' eval1dhplatinf: y = ',y,', x = ',x
  pfillirr1dhplat0(x, nw, HX1, HX2, HX3, HX4, HX5, n1, n2);
  // fillirr1dhplatinf takes care automatically of all the immaginary
  // parts as well as of the jump across y=1
  pfillirr1dhplatinf(x, nw, HX1, HX2, HX3, HX4, HX5,
                            HY1, HY2, HY3, HY4, HY5,
                            Hi1, Hi2, Hi3, Hi4, Hi5, n1, n2);
  // then the reducible 1dHPL's
  pfillred1dhpl(nw, H1, H2, H3, H4, H5,
                    HY1, HY2, HY3, HY4, HY5,
                    Hi1, Hi2, Hi3, Hi4, Hi5, n1, n2);
 }

 void hplog5::peval1dhplinm1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                              HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                              HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's for y=-1 (explicit values are tabulated)

  // additional arrays required within this routine
  CArr<1> G1; CArr<2> G2; CArr<3> G3; CArr<4> G4; CArr<5> G5;
  G1.init(-n2,-n1); G2.init(-n2,-n1); G3.init(-n2,-n1); G4.init(-n2,-n1); G5.init(-n2,-n1);
  HArr<1> GY1; HArr<2> GY2; HArr<3> GY3; HArr<4> GY4; HArr<5> GY5;
  GY1.init(-n2,-n1); GY2.init(-n2,-n1); GY3.init(-n2,-n1); GY4.init(-n2,-n1); GY5.init(-n2,-n1);
  HArr<1> Gi1; HArr<2> Gi2; HArr<3> Gi3; HArr<4> Gi4; HArr<5> Gi5;
  Gi1.init(-n2,-n1); Gi2.init(-n2,-n1); Gi3.init(-n2,-n1); Gi4.init(-n2,-n1); Gi5.init(-n2,-n1);

  std::array<int, 3> istorfill;
  IArr<1> nphase; nphase.init(-1, 1);
  nphase(-1) = -1;
  nphase(0) = 1;
  nphase(1) = -1;
  double pi = 3.14159265358979324;

  //      print*,' eval1dhplatm1: y = ',y
  if(fillred.infilldim == 2){
    for(int i = 1; i <= 2; i++){
      istorfill[i] = fillred.infill[i];
      fillred.infill[i] = -istorfill[i];
    }
  }
  // evaluate H(...,-y)
  psetzero(nw, Gi1, Gi2, Gi3, Gi4, Gi5, -n2, -n1);
  Gi1(0) = -1.0;
  peval1dhplin1(-y, nw, G1, G2, G3, G4, G5,
                        GY1, GY2, GY3, GY4, GY5,
                        Gi1, Gi2, Gi3, Gi4, Gi5, -n2, -n1);
  if (fillred.infilldim == 2){
    for(int i = 1; i <= 2; i++){
      fillred.infill[i] = istorfill[i];
    }
  }
  // fill the arrays H's
  for(int k1 = n1; k1 <= n2; k1++){
    int nph1 = nphase(k1);
    HY1(k1) =   nph1*GY1(-k1);
    Hi1(k1) = - nph1*Gi1(-k1);
    H1(k1)  = cdouble(HY1(k1),Hi1(k1)*pi);
    if ( nw > 1 ){
      for(int k2 = n1; k2 <= n2; k2++){
        int nph2 = nph1*nphase(k2);
        HY2(k1,k2) =   nph2*GY2(-k1,-k2);
        Hi2(k1,k2) = - nph2*Gi2(-k1,-k2);
        H2(k1,k2)  =   cdouble(HY2(k1,k2),Hi2(k1,k2)*pi);
        if ( nw > 2 ){
          for(int k3 = n1; k3 <= n2; k3++){
            int nph3 = nph2*nphase(k3);
            HY3(k1,k2,k3) =   nph3*GY3(-k1,-k2,-k3);
            Hi3(k1,k2,k3) = - nph3*Gi3(-k1,-k2,-k3);
            H3(k1,k2,k3)  =   cdouble(HY3(k1,k2,k3),Hi3(k1,k2,k3)*pi);
            if ( nw > 3 ){
              for(int k4 = n1; k4 <= n2; k4++){
                int nph4 = nph3*nphase(k4);
                HY4(k1,k2,k3,k4) =   nph4*GY4(-k1,-k2,-k3,-k4);
                Hi4(k1,k2,k3,k4) = - nph4*Gi4(-k1,-k2,-k3,-k4);
                H4(k1,k2,k3,k4)  =   cdouble(HY4(k1,k2,k3,k4),Hi4(k1,k2,k3,k4)*pi);
                if ( nw > 4 ){
                  for(int k5 = n1; k5 <= n2; k5++){
                    int nph5 = nph4*nphase(k5);
                    HY5(k1,k2,k3,k4,k5) =   nph5*GY5(-k1,-k2,-k3,-k4,-k5);
                    Hi5(k1,k2,k3,k4,k5) = - nph5*Gi5(-k1,-k2,-k3,-k4,-k5);
                    H5(k1,k2,k3,k4,k5)  =   cdouble(HY5(k1,k2,k3,k4,k5),Hi5(k1,k2,k3,k4,k5)*pi);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (n1 == 0) return;
// correct the ill-defined entries
  HY2(-1,0) = - HY2(0,-1);
  Hi2(-1,0) = Hi1(0)*HY1(-1);
  H2(-1,0) = cdouble(HY2(-1,0),Hi2(-1,0)*pi);
  if ( nw == 2 ) return;
  HY3(-1,0,0) = HY1(-1)*HY2(0,0)+HY3(0,0,-1);
  Hi3(-1,0,0) = HY1(-1)*Hi2(0,0)-HY2(0,-1)*Hi1(0);
  H3(-1,0,0) = cdouble(HY3(-1,0,0),Hi3(-1,0,0)*pi);
  if ( nw == 3 ) return;
  HY4(-1,0,0,0) = -HY2(0,-1)*HY2(0,0)-HY4(0,0,0,-1);
  Hi4(-1,0,0,0) = HY1(-1)*Hi3(0,0,0)+HY3(0,0,-1)*Hi1(0);
  H4(-1,0,0,0) = cdouble(HY4(-1,0,0,0),Hi4(-1,0,0,0)*pi);
  if ( nw == 4 ) return;
  HY5(-1,0,0,0,0) = HY4(0,0,0,0)*HY1(-1)+HY2(0,0)*HY3(0,0,-1)
                  + HY5(0,0,0,0,-1);
  Hi5(-1,0,0,0,0) = -HY2(0,-1)*Hi3(0,0,0)-HY4(0,0,0,-1)*Hi1(0);
  H5(-1,0,0,0,0) = cdouble(HY5(-1,0,0,0,0),Hi5(-1,0,0,0,0)*pi);
 }

 void hplog5::peval1dhplatm1(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                              HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                              HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's in the (-1)-range  -(r2+1) < y <= -(r2-1)
  // evaluating first the H(..,-y) by calling eval1dhplat1(-y),
  // and then expressing H(..,y) in terms of H(..,-y)

  // additional arrays required within this routine
  CArr<1> G1; CArr<2> G2; CArr<3> G3; CArr<4> G4; CArr<5> G5;
  G1.init(-n2,-n1); G2.init(-n2,-n1); G3.init(-n2,-n1); G4.init(-n2,-n1); G5.init(-n2,-n1);
  HArr<1> GY1; HArr<2> GY2; HArr<3> GY3; HArr<4> GY4; HArr<5> GY5;
  GY1.init(-n2,-n1); GY2.init(-n2,-n1); GY3.init(-n2,-n1); GY4.init(-n2,-n1); GY5.init(-n2,-n1);
  HArr<1> Gi1; HArr<2> Gi2; HArr<3> Gi3; HArr<4> Gi4; HArr<5> Gi5;
  Gi1.init(-n2,-n1); Gi2.init(-n2,-n1); Gi3.init(-n2,-n1); Gi4.init(-n2,-n1); Gi5.init(-n2,-n1);

  std::array<int, 3> istorfill;
  IArr<1> nphase; nphase.init(-1, 1);
  nphase(-1) = -1;
  nphase(0) = 1;
  nphase(1) = -1;
  double pi = 3.14159265358979324;

  //      print*,' eval1dhplatm1: y = ',y
  if(fillred.infilldim == 2){
    for(int i = 1; i <= 2; i++){
      istorfill[i] = fillred.infill[i];
      fillred.infill[i] = -istorfill[i];
    }
  }
  // evaluate H(...,-y)
  psetzero(nw, Gi1, Gi2, Gi3, Gi4, Gi5, -n2, -n1);
  Gi1(0) = -1.0;
  peval1dhplat1(-y, nw, G1, G2, G3, G4, G5,
                        GY1, GY2, GY3, GY4, GY5,
                        Gi1, Gi2, Gi3, Gi4, Gi5, -n2, -n1);
  if (fillred.infilldim == 2){
    for(int i = 1; i <= 2; i++){
      fillred.infill[i] = istorfill[i];
    }
  }
// fill the arrays H's
  for(int k1 = n1; k1 <= n2; k1++){
    int nph1 = nphase(k1);
    HY1(k1) =   nph1*GY1(-k1);
    Hi1(k1) = - nph1*Gi1(-k1);
    H1(k1)  =   cdouble(HY1(k1),Hi1(k1)*pi);
    if ( nw > 1 ){
      for(int k2 = n1; k2 <= n2; k2++){
        int nph2 = nph1*nphase(k2);
        HY2(k1,k2) =   nph2*GY2(-k1,-k2);
        Hi2(k1,k2) = - nph2*Gi2(-k1,-k2);
        H2(k1,k2)  =   cdouble(HY2(k1,k2),Hi2(k1,k2)*pi);
        if ( nw > 2 ){
          for(int k3 = n1; k3 <= n2; k3++){
            int nph3 = nph2*nphase(k3);
            HY3(k1,k2,k3) =   nph3*GY3(-k1,-k2,-k3);
            Hi3(k1,k2,k3) = - nph3*Gi3(-k1,-k2,-k3);
            H3(k1,k2,k3)  =   cdouble(HY3(k1,k2,k3),Hi3(k1,k2,k3)*pi);
            if ( nw > 3 ){
              for(int k4 = n1; k4 <= n2; k4++){
                int nph4 = nph3*nphase(k4);
                HY4(k1,k2,k3,k4) =   nph4*GY4(-k1,-k2,-k3,-k4);
                Hi4(k1,k2,k3,k4) = - nph4*Gi4(-k1,-k2,-k3,-k4);
                H4(k1,k2,k3,k4)  =   cdouble(HY4(k1,k2,k3,k4),Hi4(k1,k2,k3,k4)*pi);
                if ( nw > 4 ){
                  for(int k5 = n1; k5 <= n2; k5++){
                    int nph5 = nph4*nphase(k5);
                    HY5(k1,k2,k3,k4,k5) =   nph5*GY5(-k1,-k2,-k3,-k4,-k5);
                    Hi5(k1,k2,k3,k4,k5) = - nph5*Gi5(-k1,-k2,-k3,-k4,-k5);
                    H5(k1,k2,k3,k4,k5)  =   cdouble(HY5(k1,k2,k3,k4,k5),Hi5(k1,k2,k3,k4,k5)*pi);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

 }

 void hplog5::peval1dhplatminf(double y,int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                                HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates 1dhpl's in the (-1)-range y  <= -(r2+1)
  // evaluating first the H(..,-y) by calling eval1dhplatinf(-y),
  // and then expressing H(..,y) in terms of H(..,-y)

  // additional arrays required within this routine
  CArr<1> G1; CArr<2> G2; CArr<3> G3; CArr<4> G4; CArr<5> G5;
  G1.init(-n2,-n1); G2.init(-n2,-n1); G3.init(-n2,-n1); G4.init(-n2,-n1); G5.init(-n2,-n1);
  HArr<1> GY1; HArr<2> GY2; HArr<3> GY3; HArr<4> GY4; HArr<5> GY5;
  GY1.init(-n2,-n1); GY2.init(-n2,-n1); GY3.init(-n2,-n1); GY4.init(-n2,-n1); GY5.init(-n2,-n1);
  HArr<1> Gi1; HArr<2> Gi2; HArr<3> Gi3; HArr<4> Gi4; HArr<5> Gi5;
  Gi1.init(-n2,-n1); Gi2.init(-n2,-n1); Gi3.init(-n2,-n1); Gi4.init(-n2,-n1); Gi5.init(-n2,-n1);

  std::array<int, 3> istorfill;
  IArr<1> nphase; nphase.init(-1, 1);
  nphase(-1) = -1;
  nphase(0) = 1;
  nphase(1) = -1;
  double pi = 3.14159265358979324;

  //      print*,' eval1dhplatminf: y = ',y
  if(fillred.infilldim == 2){
    for(int i = 1; i <= 2; i++){
      istorfill[i] = fillred.infill[i];
      fillred.infill[i] = -istorfill[i];
    }
  }
  // evaluate H(...,-y)
  psetzero(nw, Gi1, Gi2, Gi3, Gi4, Gi5, -n2, -n1);
  Gi1(0) = -1.0;
  peval1dhplatinf(-y, nw, G1, G2, G3, G4, G5,
                          GY1, GY2, GY3, GY4, GY5,
                          Gi1, Gi2, Gi3, Gi4, Gi5, -n2, -n1);
  if (fillred.infilldim == 2){
    for(int i = 1; i <= 2; i++){
      fillred.infill[i] = istorfill[i];
    }
  }

  // fill the arrays H's
  for(int k1 = n1; k1 <= n2; k1++){
    int nph1 = nphase(k1);
    HY1(k1) =   nph1*GY1(-k1);
    Hi1(k1) = - nph1*Gi1(-k1);
    H1(k1)  =   cdouble(HY1(k1),Hi1(k1)*pi);
    if ( nw > 1 ){
      for(int k2 = n1; k2 <= n2; k2++){
        int nph2 = nph1*nphase(k2);
        HY2(k1,k2) =   nph2*GY2(-k1,-k2);
        Hi2(k1,k2) = - nph2*Gi2(-k1,-k2);
        H2(k1,k2)  =   cdouble(HY2(k1,k2),Hi2(k1,k2)*pi);
        if ( nw > 2 ){
          for(int k3 = n1; k3 <= n2; k3++){
            int nph3 = nph2*nphase(k3);
            HY3(k1,k2,k3) =   nph3*GY3(-k1,-k2,-k3);
            Hi3(k1,k2,k3) = - nph3*Gi3(-k1,-k2,-k3);
            H3(k1,k2,k3)  =   cdouble(HY3(k1,k2,k3),Hi3(k1,k2,k3)*pi);
            if ( nw > 3 ){
              for(int k4 = n1; k4 <= n2; k4++){
                int nph4 = nph3*nphase(k4);
                HY4(k1,k2,k3,k4) =   nph4*GY4(-k1,-k2,-k3,-k4);
                Hi4(k1,k2,k3,k4) = - nph4*Gi4(-k1,-k2,-k3,-k4);
                H4(k1,k2,k3,k4)  =   cdouble(HY4(k1,k2,k3,k4),Hi4(k1,k2,k3,k4)*pi);
                if ( nw > 4 ){
                  for(int k5 = n1; k5 <= n2; k5++){
                    int nph5 = nph4*nphase(k5);
                    HY5(k1,k2,k3,k4,k5) =   nph5*GY5(-k1,-k2,-k3,-k4,-k5);
                    Hi5(k1,k2,k3,k4,k5) = - nph5*Gi5(-k1,-k2,-k3,-k4,-k5);
                    H5(k1,k2,k3,k4,k5)  =   cdouble(HY5(k1,k2,k3,k4,k5),Hi5(k1,k2,k3,k4,k5)*pi);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

 }

 // Fortran: subroutine psetzero(nw,Hi1,Hi2,Hi3,Hi4,Hi5,n1,n2)
 void hplog5::psetzero(int nw, HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5,
                       int n1, int n2)
 {
   for(int k1=n1;k1<=n2;++k1){
     Hi1(k1)=0.0;
     if(nw>1){
       for(int k2=n1;k2<=n2;++k2){
         Hi2(k1,k2)=0.0;
         if(nw>2){
           for(int k3=n1;k3<=n2;++k3){
             Hi3(k1,k2,k3)=0.0;
             if(nw>3){
               for(int k4=n1;k4<=n2;++k4){
                 Hi4(k1,k2,k3,k4)=0.0;
                 if(nw>4){
                   for(int k5=n1;k5<=n2;++k5){
                     Hi5(k1,k2,k3,k4,k5)=0.0;
                   }
                 }
               }
             }
           }
         }
       }
     }
   }
 }

 void hplog5::psetzero(int nw, CArr<1>& Hc1, CArr<2>& Hc2, CArr<3>& Hc3, CArr<4>& Hc4, CArr<5>& Hc5,
                       int n1, int n2)
 {
   for(int k1=n1;k1<=n2;++k1){
     Hc1(k1)=0.0;
     if(nw>1){
       for(int k2=n1;k2<=n2;++k2){
         Hc2(k1,k2)=0.0;
         if(nw>2){
           for(int k3=n1;k3<=n2;++k3){
             Hc3(k1,k2,k3)=0.0;
             if(nw>3){
               for(int k4=n1;k4<=n2;++k4){
                 Hc4(k1,k2,k3,k4)=0.0;
                 if(nw>4){
                   for(int k5=n1;k5<=n2;++k5){
                     Hc5(k1,k2,k3,k4,k5)=0.0;
                   }
                 }
               }
             }
           }
         }
       }
     }
   }
 }

 void hplog5::pfillred1dhpl(int nw, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, CArr<5>& H5,
                                   HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                   HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)

 {
  // fills the reducible 1dhpl from the irreducible set
  double pinv = 0.318309886183790672;
  double pi   = 3.14159265358979324;
  // combining real and immaginary into the complex value
  for(int k1 = n1; k1 <= n2; k1++){
    for(int k2 = n1; k2 <= n2; k2++){
      H2(k1,k2) = cdouble(HY2(k1,k2),Hi2(k1,k2)*pi);
      if ( nw > 2 ){
        for(int k3 = n1; k3 <= n2; k3++){
          H3(k1,k2,k3) = cdouble(HY3(k1,k2,k3),Hi3(k1,k2,k3)*pi);
          if ( nw > 3 ){
            for(int k4 = n1; k4 <= n2; k4++){
              H4(k1,k2,k3,k4) = cdouble(HY4(k1,k2,k3,k4),Hi4(k1,k2,k3,k4)*pi);
              if ( nw > 4 ){
                for(int k5 = n1; k5 <= n2; k5++){
                  H5(k1,k2,k3,k4,k5) = cdouble(HY5(k1,k2,k3,k4,k5),Hi5(k1,k2,k3,k4,k5)*pi);
                }
              }
            }
          }
        }
      }
    }
  }
  // evaluating the reduced HPL's
  // iflag = 0 to suppress auxiliary printings of FILLREDHPLx
  int iflag = 0;
  for(int ia = 1; ia <= fillred.infilldim; ia++){
    for(int ib = ia; ib <= fillred.infilldim; ib++){
      pFILLREDHPL2(iflag, H1, H2, n1, n2, fillred.infill[ia], fillred.infill[ib]);
      if ( nw > 2 ){
        for(int ic = ib; ic <= fillred.infilldim; ic++){
          pFILLREDHPL3(iflag, H1, H2, H3, n1, n2, fillred.infill[ia], fillred.infill[ib], fillred.infill[ic]);
          if ( nw > 3 ){
            for(int id = ic; id <= fillred.infilldim; id++){
              pFILLREDHPL4(iflag, H1, H2, H3, H4, n1, n2, fillred.infill[ia], fillred.infill[ib], fillred.infill[ic], fillred.infill[id]);
            }
          }
        }
      }
    }
  }
  if (nw > 4) pFILLREDHPL5(iflag, H1, H2, H3, H4, H5, n1, n2);
  // extractin real and immaginary parts from the complex value
  for(int k1 = n1; k1 <= n2; k1++){
    for(int k2 = n1; k2 <= n2; k2++){
      HY2(k1,k2) = std::real(H2(k1,k2));
      Hi2(k1,k2) = std::imag(H2(k1,k2))*pinv;
      if ( nw > 2 ){
        for(int k3 = n1; k3 <= n2; k3++){
          HY3(k1,k2,k3) = std::real(H3(k1,k2,k3));
          Hi3(k1,k2,k3) = std::imag(H3(k1,k2,k3))*pinv;
          if ( nw > 3 ){
            for(int k4 = n1; k4 <= n2; k4++){
              HY4(k1,k2,k3,k4) = std::real(H4(k1,k2,k3,k4));
              Hi4(k1,k2,k3,k4) = std::imag(H4(k1,k2,k3,k4))*pinv;
              if ( nw > 4 ){
                for(int k5 = n1; k5 <= n2; k5++){
                  HY5(k1,k2,k3,k4,k5) = std::real(H5(k1,k2,k3,k4,k5));
                  Hi5(k1,k2,k3,k4,k5) = std::imag(H5(k1,k2,k3,k4,k5))*pinv;
                }
              }
            }
          }
        }
      }
    }
  }

 }

 void hplog5::pFILLREDHPL2(int iflag, CArr<1>& H1, CArr<2>& H2, int i1, int i2, int na, int nb)
 {
  // must be called with ordered indices na <= nb
  //      print*,' FILLREDHPL2, iflag =',iflag
  if ( na == nb ){
    H2(na,na) = 1.0/2.0*(H1(na) * H1(na));
  }
  else{
    H2(nb,na) = H1(na)*H1(nb) - H2(na,nb);
    if ( iflag == 1 ){
      pprinter2(na, nb);
    }
  }
 }

 void hplog5::pFILLREDHPL3(int iflag, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, int i1, int i2, int ia, int ib, int ic)
 {
  // must be called with "properly ordered" indices
  // note in particular the remapping of, say, (ia,ib,ic) into
  // (na,na,nb) of ReducerTest.out
  int na = ia;
  if ( (ia == ib) && (ib == ic) ){
  // case (na,na,na)
    H3(na,na,na) = 1.0/6.0*(H1(na) * H1(na) * H1(na));
  }
  // ic cannot be anymore equal to ia
  else if ( ic == ia ){
    cout<<" FILLREDHPL3, error 1, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<endl;
    return;
  }
  else if ( ia == ib ){
  // case (na,na,nb)
    int nb = ic;
    if ( iflag == 1 ){
      pprinter3(na,na,nb);
    }
    H3(na,nb,na) =   H1(na)*H2(na,nb) - 2.0 * H3(na,na,nb);
    H3(nb,na,na) =   1.0/2.0*H1(na)*H1(na)*H1(nb)
                   - H1(na)*H2(na,nb) + H3(na,na,nb);
  }
  // ib cannot be anymore equal to ia
  else if ( ib == ia ){
    cout<<" FILLREDHPL3, error 2, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<endl;
    return;
  }
  else if ( ib == ic ){
  // case (na,nb,nb)
    int nb = ib;
    if ( iflag == 1 ){
      pprinter3(na,nb,nb);
    }
    H3(nb,na,nb) =   H1(nb)*H2(na,nb) - 2.0*H3(na,nb,nb);
    H3(nb,nb,na) =   1.0/2.0*H1(na)*H1(nb)*H1(nb)
                   - H1(nb)*H2(na,nb) + H3(na,nb,nb);
  }
  // no need to protect against ic.eq.ib
  // when arriving here all indices are different
  else{
  // case (na,nb,nc)    all indices are different
    int nb = ib;
    int nc = ic;
    if ( iflag == 1 ){
      pprinter3(na,nb,nc);
      pprinter3(na,nc,nb);
    }
    H3(nb,na,nc) =   H1(nb)*H2(na,nc)
                   - H3(na,nb,nc) - H3(na,nc,nb);
    H3(nb,nc,na) =   H1(na)*H2(nb,nc)
                   - H1(nb)*H2(na,nc) + H3(na,nc,nb);
    H3(nc,na,nb) =   H1(nc)*H2(na,nb)
                   - H3(na,nb,nc) - H3(na,nc,nb);
    H3(nc,nb,na) =   H1(na)*H1(nb)*H1(nc) - H1(na)*H2(nb,nc)
                   - H1(nc)*H2(na,nb) + H3(na,nb,nc);
  }

 }

 void hplog5::pFILLREDHPL4(int iflag, CArr<1>& H1, CArr<2>& H2, CArr<3>& H3, CArr<4>& H4, int i1, int i2, int ia, int ib, int ic, int id)
 {
  // must be called with "properly ordered" indices
  // note in particular the remapping of, say, (ia,ib,ic) into
  // (na,na,nb) of ReducerTest.out
  int na = ia;
  if ( (ia == ib) && (ib == ic) && (ic == id) ){
  // case (na,na,na,na)
    H4(na,na,na,na) = 1.0/24.0*( H1(na) * H1(na) * H1(na) * H1(na));
  }
  // id cannot be anymore equal to ia
  else if ( id == ia ){
    cout<<" FILLREDHPL4, error 1, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<"  "<<id<<endl;
    return;
  }
  else if ( (ia == ib) && (ib == ic) ){
  // case (na,na,na,nb)
    int nb = id;
    H4(na,na,nb,na) =   H1(na)*H3(na,na,nb) - 3.0*H4(na,na,na,nb);
    H4(na,nb,na,na) =   1.0/2.0*H1(na)*H1(na)*H2(na,nb)
                      - 2.0*H1(na)*H3(na,na,nb) + 3.0*H4(na,na,na,nb);
    H4(nb,na,na,na) =   1.0/6.0*H1(na)*H1(na)*H1(na)*H1(nb)
                      - 1.0/2.0*H1(na)*H1(na)*H2(na,nb)
                      + H1(na)*H3(na,na,nb) - H4(na,na,na,nb);
    if ( iflag == 1 ){
      pprinter4(na,na,na,nb);
    }
  }
  // ic cannot be anymore equal to ia
  else if ( ic == ia ){
    cout<<" FILLREDHPL4, error 2, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<"  "<<id<<endl;
    return;
  }
  else if ( (ia == ib) && (ic == id) ){
  // case (na,na,nb,nb)
    int nb = ic;
    H4(na,nb,na,nb) = + 1.0/2.0*H2(na,nb)*H2(na,nb)
                      - 2.0*H4(na,na,nb,nb);
    H4(na,nb,nb,na) = + H1(na)*H3(na,nb,nb)
                      - 1.0/2.0*H2(na,nb)*H2(na,nb);
    H4(nb,na,na,nb) = + H1(nb)*H3(na,na,nb)
                      - 1.0/2.0*H2(na,nb)*H2(na,nb);
    H4(nb,na,nb,na) = + H1(na)*H1(nb)*H2(na,nb)
                      - 2.0*H1(na)*H3(na,nb,nb)
                      - 2.0*H1(nb)*H3(na,na,nb)
                      + 1.0/2.0*H2(na,nb)*H2(na,nb)
                      + 2.0*H4(na,na,nb,nb);
    H4(nb,nb,na,na) = + 1.0/4.0*H1(na)*H1(na)*H1(nb)*H1(nb)
                      - H1(na)*H1(nb)*H2(na,nb)
                      + H1(na)*H3(na,nb,nb)
                      + H1(nb)*H3(na,na,nb) - H4(na,na,nb,nb);
    if ( iflag == 1 ){
      pprinter4(na,na,nb,nb);
    }
  }
  else if ( ia == ib ){
  // case (na,na,nb,nc)
    int nb = ic;
    int nc = id;
    H4(na,nb,nc,na) = + H1(na)*H3(na,nb,nc) - 2.0*H4(na,na,nb,nc)
                      - H4(na,nb,na,nc);
    H4(na,nc,na,nb) = + H2(na,nb)*H2(na,nc) - 2.0*H4(na,na,nb,nc)
                      - 2.0*H4(na,na,nc,nb) - H4(na,nb,na,nc);
    H4(na,nc,nb,na) = + H1(na)*H3(na,nc,nb) - H2(na,nb)*H2(na,nc)
                      + 2.0*H4(na,na,nb,nc) + H4(na,nb,na,nc);
    H4(nb,na,na,nc) = + H1(nb)*H3(na,na,nc) - H4(na,na,nb,nc)
                      - H4(na,na,nc,nb) - H4(na,nb,na,nc);
    H4(nb,na,nc,na) = + H1(na)*H1(nb)*H2(na,nc)
                      - H1(na)*H3(na,nb,nc) - H1(na)*H3(na,nc,nb)
                      - 2.0*H1(nb)*H3(na,na,nc) + 2.0*H4(na,na,nb,nc)
                      + 2.0*H4(na,na,nc,nb) + H4(na,nb,na,nc);
    H4(nb,nc,na,na) = + 1.0/2.0*H1(na)*H1(na)*H2(nb,nc)
                      - H1(na)*H1(nb)*H2(na,nc)
                      + H1(na)*H3(na,nc,nb) + H1(nb)*H3(na,na,nc)
                      - H4(na,na,nc,nb);
    H4(nc,na,na,nb) = + H1(nc)*H3(na,na,nb) - H2(na,nb)*H2(na,nc)
                      + H4(na,na,nb,nc) + H4(na,na,nc,nb)
                      + H4(na,nb,na,nc);
    H4(nc,na,nb,na) = + H1(na)*H1(nc)*H2(na,nb)
                      - H1(na)*H3(na,nb,nc) - H1(na)*H3(na,nc,nb)
                      - 2.0*H1(nc)*H3(na,na,nb) + H2(na,nb)*H2(na,nc)
                      - H4(na,nb,na,nc);
    H4(nc,nb,na,na) = + 1.0/2.0*H1(na)*H1(na)*H1(nb)*H1(nc)
                      - 1.0/2.0*H1(na)*H1(na)*H2(nb,nc)
                      - H1(na)*H1(nc)*H2(na,nb)
                      + H1(na)*H3(na,nb,nc) + H1(nc)*H3(na,na,nb)
                      - H4(na,na,nb,nc);
    if ( iflag == 1 ){
      pprinter4(na,na,nb,nc);
      pprinter4(na,na,nc,nb);
      pprinter4(na,nb,na,nc);
    }
  }
  // ib cannot be anymore equal to ia
  else if ( ib == ia ){
    cout<<" FILLREDHPL4, error 3, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<"  "<<id<<endl;
    return;
  }
  else if ( (ib == ic) && (ic == id) ){
  // case (na,nb,nb,nb)
    int nb = ib;
    H4(nb,na,nb,nb) = + H1(nb)*H3(na,nb,nb) - 3.0*H4(na,nb,nb,nb);
    H4(nb,nb,na,nb) = + 1.0/2.0*H1(nb)*H1(nb)*H2(na,nb)
                      - 2.0*H1(nb)*H3(na,nb,nb) + 3.0*H4(na,nb,nb,nb);
    H4(nb,nb,nb,na) = + 1.0/6.0*H1(na)*H1(nb)*H1(nb)*H1(nb)
                      - 1.0/2.0*H1(nb)*H1(nb)*H2(na,nb)
                      + H1(nb)*H3(na,nb,nb) - H4(na,nb,nb,nb);
    if ( iflag == 1 ){
      pprinter4(na,nb,nb,nb);
    }
  }
  // id cannot be anymore equal to ib
  else if ( id == ib ){
    cout<<" FILLREDHPL4, error 4, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<"  "<<id<<endl;
    return;
  }
  else if ( ib == ic ){
  // case (na,nb,nb,nc)
    int nb = ib;
    int nc = id;
    H4(nb,na,nb,nc) = + H1(nb)*H3(na,nb,nc)
                      - 2.0*H4(na,nb,nb,nc) - H4(na,nb,nc,nb);
    H4(nb,na,nc,nb) = + H1(nb)*H3(na,nc,nb) - H4(na,nb,nc,nb)
                      - 2.0*H4(na,nc,nb,nb);
    H4(nb,nb,na,nc) = + 1.0/2.0*H1(nb)*H1(nb)*H2(na,nc)
                      - H1(nb)*H3(na,nb,nc) - H1(nb)*H3(na,nc,nb)
                      + H4(na,nb,nb,nc) + H4(na,nb,nc,nb)
                      + H4(na,nc,nb,nb);
    H4(nb,nb,nc,na) = + H1(na)*H3(nb,nb,nc)
                      - 1.0/2.0*H1(nb)*H1(nb)*H2(na,nc)
                      + H1(nb)*H3(na,nc,nb) - H4(na,nc,nb,nb);
    H4(nb,nc,na,nb) = - H1(nb)*H3(na,nb,nc) - H1(nb)*H3(na,nc,nb)
                      + H2(na,nb)*H2(nb,nc) + H4(na,nb,nc,nb)
                      + 2.0*H4(na,nc,nb,nb);
    H4(nb,nc,nb,na) = + H1(na)*H1(nb)*H2(nb,nc)
                      - 2.0*H1(na)*H3(nb,nb,nc)
                      + H1(nb)*H3(na,nb,nc)
                      - H2(na,nb)*H2(nb,nc) - H4(na,nb,nc,nb);
    H4(nc,na,nb,nb) = + H1(nc)*H3(na,nb,nb) - H4(na,nb,nb,nc)
                      - H4(na,nb,nc,nb) - H4(na,nc,nb,nb);
    H4(nc,nb,na,nb) = + H1(nb)*H1(nc)*H2(na,nb)
                      - 2.0*H1(nc)*H3(na,nb,nb)
                      - H2(na,nb)*H2(nb,nc) + 2.0*H4(na,nb,nb,nc)
                      + H4(na,nb,nc,nb);
    H4(nc,nb,nb,na) = + 1.0/2.0*H1(na)*H1(nb)*H1(nb)*H1(nc)
                      - H1(na)*H1(nb)*H2(nb,nc)
                      + H1(na)*H3(nb,nb,nc)
                      - H1(nb)*H1(nc)*H2(na,nb)
                      + H1(nc)*H3(na,nb,nb) + H2(na,nb)*H2(nb,nc)
                      - H4(na,nb,nb,nc);
    if ( iflag == 1 ){
      pprinter4(na,nb,nb,nc);
      pprinter4(na,nb,nc,nb);
      pprinter4(na,nc,nb,nb);
    }
  }
  // ic cannot be anymore equal to ib
  else if ( ic == ib ){
    cout<<" FILLREDHPL4, error 5, called with arguments "<<endl;
    cout<<"               "<<ia<<"  "<<ib<<"  "<<ic<<"  "<<id<<endl;
    return;
  }
  else if ( ic == id ){
  // case (na,nb,nc,nc)
    int nb = ib;
    int nc = ic;
    H4(nb,na,nc,nc) = + H1(nb)*H3(na,nc,nc) - H4(na,nb,nc,nc)
                      - H4(na,nc,nb,nc) - H4(na,nc,nc,nb);
    H4(nb,nc,na,nc) = - 2.0*H1(nb)*H3(na,nc,nc) + H2(na,nc)*H2(nb,nc)
                      + H4(na,nc,nb,nc) + 2.0*H4(na,nc,nc,nb);
    H4(nb,nc,nc,na) = + H1(na)*H3(nb,nc,nc) + H1(nb)*H3(na,nc,nc)
                      - H2(na,nc)*H2(nb,nc) - H4(na,nc,nc,nb);
    H4(nc,na,nb,nc) = + H1(nc)*H3(na,nb,nc) - 2.0*H4(na,nb,nc,nc)
                      - H4(na,nc,nb,nc);
    H4(nc,na,nc,nb) = + H1(nc)*H3(na,nc,nb) - H4(na,nc,nb,nc)
                      - 2.0*H4(na,nc,nc,nb);
    H4(nc,nb,na,nc) = + H1(nb)*H1(nc)*H2(na,nc)
                      - H1(nc)*H3(na,nb,nc) - H1(nc)*H3(na,nc,nb)
                      - H2(na,nc)*H2(nb,nc) + 2.0*H4(na,nb,nc,nc)
                      + H4(na,nc,nb,nc);
    H4(nc,nb,nc,na) = + H1(na)*H1(nc)*H2(nb,nc)
                      - 2.0*H1(na)*H3(nb,nc,nc)
                      - H1(nb)*H1(nc)*H2(na,nc)
                      + H1(nc)*H3(na,nc,nb) + H2(na,nc)*H2(nb,nc)
                      - H4(na,nc,nb,nc);
    H4(nc,nc,na,nb) = + 1.0/2.0*H1(nc)*H1(nc)*H2(na,nb)
                      - H1(nc)*H3(na,nb,nc) - H1(nc)*H3(na,nc,nb)
                      + H4(na,nb,nc,nc) + H4(na,nc,nb,nc)
                      + H4(na,nc,nc,nb);
    H4(nc,nc,nb,na) = + 1.0/2.0*H1(na)*H1(nb)*H1(nc)*H1(nc)
                      - H1(na)*H1(nc)*H2(nb,nc)
                      + H1(na)*H3(nb,nc,nc)
                      - 1.0/2.0*H1(nc)*H1(nc)*H2(na,nb)
                      + H1(nc)*H3(na,nb,nc) - H4(na,nb,nc,nc);
    if ( iflag == 1 ){
      pprinter4(na,nb,nc,nc);
      pprinter4(na,nc,nb,nc);
      pprinter4(na,nc,nc,nb);
    }
  }
  // no need to protect against id.eq.ic
  // when arriving here all indices are different
  else{
  // case (na,nb,nc,nd) all indices are different
    int nb = ib;
    int nc = ic;
    int nd = id;
    H4(nb,na,nc,nd) = + H1(nb)*H3(na,nc,nd) - H4(na,nb,nc,nd)
                      - H4(na,nc,nb,nd) - H4(na,nc,nd,nb);
    H4(nb,na,nd,nc) = + H1(nb)*H3(na,nd,nc) - H4(na,nb,nd,nc)
                      - H4(na,nd,nb,nc) - H4(na,nd,nc,nb);
    H4(nb,nc,na,nd) = - H1(nb)*H3(na,nc,nd) - H1(nb)*H3(na,nd,nc)
                      + H2(na,nd)*H2(nb,nc) + H4(na,nc,nb,nd)
                      + H4(na,nc,nd,nb) + H4(na,nd,nc,nb);
    H4(nb,nc,nd,na) = + H1(na)*H3(nb,nc,nd) + H1(nb)*H3(na,nd,nc)
                      - H2(na,nd)*H2(nb,nc) - H4(na,nd,nc,nb);
    H4(nb,nd,na,nc) = - H1(nb)*H3(na,nc,nd) - H1(nb)*H3(na,nd,nc)
                      + H2(na,nc)*H2(nb,nd) + H4(na,nc,nd,nb)
                      + H4(na,nd,nb,nc) + H4(na,nd,nc,nb);
    H4(nb,nd,nc,na) = + H1(na)*H3(nb,nd,nc) + H1(nb)*H3(na,nc,nd)
                      - H2(na,nc)*H2(nb,nd) - H4(na,nc,nd,nb);
    H4(nc,na,nb,nd) = + H1(nc)*H3(na,nb,nd) - H4(na,nb,nc,nd)
                      - H4(na,nb,nd,nc) - H4(na,nc,nb,nd);
    H4(nc,na,nd,nb) = + H1(nc)*H3(na,nd,nb) - H4(na,nc,nd,nb)
                      - H4(na,nd,nb,nc) - H4(na,nd,nc,nb);
    H4(nc,nb,na,nd) = + H1(nb)*H1(nc)*H2(na,nd)
                      - H1(nc)*H3(na,nb,nd) - H1(nc)*H3(na,nd,nb)
                      - H2(na,nd)*H2(nb,nc) + H4(na,nb,nc,nd)
                      + H4(na,nb,nd,nc) + H4(na,nd,nb,nc);
    H4(nc,nb,nd,na) = + H1(na)*H1(nc)*H2(nb,nd)
                      - H1(na)*H3(nb,nc,nd) - H1(na)*H3(nb,nd,nc)
                      - H1(nb)*H1(nc)*H2(na,nd)
                      + H1(nc)*H3(na,nd,nb) + H2(na,nd)*H2(nb,nc)
                      - H4(na,nd,nb,nc);
    H4(nc,nd,na,nb) = - H1(nc)*H3(na,nb,nd) - H1(nc)*H3(na,nd,nb)
                      + H2(na,nb)*H2(nc,nd) + H4(na,nb,nd,nc)
                      + H4(na,nd,nb,nc) + H4(na,nd,nc,nb);
    H4(nc,nd,nb,na) = + H1(na)*H1(nb)*H2(nc,nd)
                      - H1(na)*H1(nc)*H2(nb,nd)
                      + H1(na)*H3(nb,nd,nc) + H1(nc)*H3(na,nb,nd)
                      - H2(na,nb)*H2(nc,nd) - H4(na,nb,nd,nc);
    H4(nd,na,nb,nc) = + H1(nd)*H3(na,nb,nc) - H4(na,nb,nc,nd)
                      - H4(na,nb,nd,nc) - H4(na,nd,nb,nc);
    H4(nd,na,nc,nb) = + H1(nd)*H3(na,nc,nb) - H4(na,nc,nb,nd)
                      - H4(na,nc,nd,nb) - H4(na,nd,nc,nb);
    H4(nd,nb,na,nc) = + H1(nb)*H1(nd)*H2(na,nc)
                      - H1(nd)*H3(na,nb,nc) - H1(nd)*H3(na,nc,nb)
                      - H2(na,nc)*H2(nb,nd) + H4(na,nb,nc,nd)
                      + H4(na,nb,nd,nc) + H4(na,nc,nb,nd);
    H4(nd,nb,nc,na) = + H1(na)*H1(nd)*H2(nb,nc)
                      - H1(na)*H3(nb,nc,nd) - H1(na)*H3(nb,nd,nc)
                      - H1(nb)*H1(nd)*H2(na,nc)
                      + H1(nd)*H3(na,nc,nb) + H2(na,nc)*H2(nb,nd)
                      - H4(na,nc,nb,nd);
    H4(nd,nc,na,nb) = + H1(nc)*H1(nd)*H2(na,nb)
                      - H1(nd)*H3(na,nb,nc) - H1(nd)*H3(na,nc,nb)
                      - H2(na,nb)*H2(nc,nd) + H4(na,nb,nc,nd)
                      + H4(na,nc,nb,nd) + H4(na,nc,nd,nb);
    H4(nd,nc,nb,na) = + H1(na)*H1(nb)*H1(nc)*H1(nd)
                      - H1(na)*H1(nb)*H2(nc,nd)
                      - H1(na)*H1(nd)*H2(nb,nc)
                      + H1(na)*H3(nb,nc,nd)
                      - H1(nc)*H1(nd)*H2(na,nb)
                      + H1(nd)*H3(na,nb,nc)
                      + H2(na,nb)*H2(nc,nd) - H4(na,nb,nc,nd);
    if ( iflag == 1 ){
      pprinter4(na,nb,nc,nd);
      pprinter4(na,nb,nd,nc);
      pprinter4(na,nc,nb,nd);
      pprinter4(na,nc,nb,nd);
      pprinter4(na,nd,nb,nc);
      pprinter4(na,nd,nc,nb);
    }
  }
 }

 void hplog5::pprinter2(int na, int nb)
 {
    cout << "g [H(";
    psubprint(11, na);
    cout << ",";
    psubprint(11, nb);
    cout << ",y)] = H(";
    psubprint(11, na);
    cout << ",";
    psubprint(11, nb);
    cout << ",y) ; ";

    cout << "\n";

    cout << "id H(";
    psubprint(12, na);
    cout << ",";
    psubprint(12, nb);
    cout << ",y) = H[(";
    psubprint(12, na);
    cout << ",";
    psubprint(12, nb);
    cout << ",y)] ; ";

    cout << "\n";
 }

 void hplog5::pprinter3(int na, int nb, int nc)
 {
    cout << "g [H(";
    psubprint(11, na);
    cout << ",";
    psubprint(11, nb);
    cout << ",";
    psubprint(11, nc);

    cout << ",y)] = H(";
    psubprint(11, na);
    cout << ",";
    psubprint(11, nb);
    cout << ",";
    psubprint(11, nc);
    cout << ",y) ; ";
    cout << "\n";

    cout << "id H(";
    psubprint(12, na);
    cout << ",";
    psubprint(12, nb);
    cout << ",";
    psubprint(12, nc);

    cout << ",y) = H[(";
    psubprint(12, na);
    cout << ",";
    psubprint(12, nb);
    cout << ",";
    psubprint(12, nc);
    cout << ",y)] ; ";
    cout << "\n";
 }

 void hplog5::pprinter4(int na, int nb, int nc, int nd)
 {
    cout << "g [H(";
    psubprint(11, na); cout << ",";
    psubprint(11, nb); cout << ",";
    psubprint(11, nc); cout << ",";
    psubprint(11, nd);

    cout << ",y)] = H(";
    psubprint(11, na); cout << ",";
    psubprint(11, nb); cout << ",";
    psubprint(11, nc); cout << ",";
    psubprint(11, nd);
    cout << ",y) ; ";
    cout << "\n";

    cout << "id H(";
    psubprint(12, na); cout << ",";
    psubprint(12, nb); cout << ",";
    psubprint(12, nc); cout << ",";
    psubprint(12, nd);

    cout << ",y) = H[(";
    psubprint(12, na); cout << ",";
    psubprint(12, nb); cout << ",";
    psubprint(12, nc); cout << ",";
    psubprint(12, nd);
    cout << ",y)] ; ";
    cout << "\n";
 }

 void hplog5::psubprint(int n, int na)
 {
  if (na < 0) {
    cout << std::setw(2) << na;
  }
  else {
    cout << std::setw(1) << na;
  }
 }

 void hplog5::pFILLREDHPL5(int iflag, CArr<1>& HZ1, CArr<2>& HZ2, CArr<3>& HZ3, CArr<4>& HZ4, CArr<5>& HZ5, int n1, int n2)
 {
  // evaluating the expansions

  HZ5(0,0,0,0,0) =
       + 8.3333333333333333e-03*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(0);

  // (n1,n2) = (0,1) or (-1,1)
  if (    ( (n1 == 0)  && (n2 == 1) )
       || ( (n1 == -1) && (n2 == 1) ) ){

    HZ5(0,0,0,1,0) =
      + HZ1(0) *HZ4(0,0,0,1)
      - 4.0000000000000000e+00*HZ5(0,0,0,0,1);
    HZ5(0,0,1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,0,1)
      - 3.0000000000000000e+00*HZ1(0)*HZ4(0,0,0,1)
      + 6.0000000000000000e+00*HZ5(0,0,0,0,1);
    HZ5(0,0,1,1,0) =
      + HZ1(0) *HZ4(0,0,1,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,1)
      - HZ5(0,0,1,0,1);
    HZ5(0,1,0,0,0) =
      + 1.6666666666666666e-01*HZ1(0)*HZ1(0)*HZ1(0)*HZ2(0,1)
      - HZ1(0) *HZ1(0)*HZ3(0,0,1)
      + 3.0000000000000000e+00*HZ1(0)*HZ4(0,0,0,1)
      - 4.0000000000000000e+00*HZ5(0,0,0,0,1);
    HZ5(0,1,0,0,1) =
      + HZ2(0,1) *HZ3(0,0,1)
      - 6.0000000000000000e+00*HZ5(0,0,0,1,1)
      - 3.0000000000000000e+00*HZ5(0,0,1,0,1);
    HZ5(0,1,0,1,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ2(0,1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(0,0,1,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,0,1)
      + 1.2000000000000000e+01*HZ5(0,0,0,1,1)
      + 4.0000000000000000e+00*HZ5(0,0,1,0,1);
    HZ5(0,1,1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,1,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ2(0,1)*HZ2(0,1)
      + HZ2(0,1) *HZ3(0,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,1)
      - HZ5(0,0,1,0,1);
    HZ5(0,1,1,0,1) =
      + HZ2(0,1) *HZ3(0,1,1)
      - 6.0000000000000000e+00*HZ5(0,0,1,1,1)
      - 3.0000000000000000e+00*HZ5(0,1,0,1,1);
    HZ5(0,1,1,1,0) =
      + HZ1(0) *HZ4(0,1,1,1)
      - HZ2(0,1) *HZ3(0,1,1)
      + 4.0000000000000000e+00*HZ5(0,0,1,1,1)
      + 2.0000000000000000e+00*HZ5(0,1,0,1,1);
    HZ5(1,0,0,0,0) =
      + 4.1666666666666666e-02*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(1)
      - 1.6666666666666666e-01*HZ1(0)*HZ1(0)*HZ1(0)*HZ2(0,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,0,1)
      - HZ1(0) *HZ4(0,0,0,1)
      + HZ5(0,0,0,0,1);
    HZ5(1,0,0,0,1) =
      + HZ1(1) *HZ4(0,0,0,1)
      - HZ2(0,1) *HZ3(0,0,1)
      + 4.0000000000000000e+00*HZ5(0,0,0,1,1)
      + 2.0000000000000000e+00*HZ5(0,0,1,0,1);
    HZ5(1,0,0,1,0) =
      + HZ1(0) *HZ1(1)*HZ3(0,0,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ2(0,1)*HZ2(0,1)
      - 3.0000000000000000e+00*HZ1(1)*HZ4(0,0,0,1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,0,1)
      - 6.0000000000000000e+00*HZ5(0,0,0,1,1)
      - 3.0000000000000000e+00*HZ5(0,0,1,0,1);
    HZ5(1,0,0,1,1) =
      + HZ1(1) *HZ4(0,0,1,1)
      - 3.0000000000000000e+00*HZ5(0,0,1,1,1)
      - HZ5(0,1,0,1,1);
    HZ5(1,0,1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ1(1)*HZ2(0,1)
      - HZ1(0) *HZ1(0)*HZ3(0,1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ1(1)*HZ3(0,0,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ2(0,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(0,0,1,1)
      + 3.0000000000000000e+00*HZ1(1)*HZ4(0,0,0,1)
      - HZ2(0,1) *HZ3(0,0,1)
      + HZ5(0,0,1,0,1);
    HZ5(1,0,1,0,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ2(0,1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(0,0,1,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,1,1)
      + 1.2000000000000000e+01*HZ5(0,0,1,1,1)
      + 4.0000000000000000e+00*HZ5(0,1,0,1,1);
    HZ5(1,0,1,1,0) =
      + HZ1(0) *HZ1(1)*HZ3(0,1,1)
      - 3.0000000000000000e+00*HZ1(0)*HZ4(0,1,1,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ2(0,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,1,1)
      - 6.0000000000000000e+00*HZ5(0,0,1,1,1)
      - 3.0000000000000000e+00*HZ5(0,1,0,1,1);
    HZ5(1,0,1,1,1) =
      + HZ1(1) *HZ4(0,1,1,1)
      - 4.0000000000000000e+00*HZ5(0,1,1,1,1);
    HZ5(1,1,0,0,0) =
      + 8.3333333333333333e-02*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(1)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ1(1)*HZ2(0,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,1,1)
      + HZ1(0) *HZ1(1)*HZ3(0,0,1)
      - HZ1(0) *HZ4(0,0,1,1)
      - HZ1(1) *HZ4(0,0,0,1)
      + HZ5(0,0,0,1,1);
    HZ5(1,1,0,0,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,0,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ2(0,1)*HZ2(0,1)
      + HZ2(0,1) *HZ3(0,1,1)
      - 3.0000000000000000e+00*HZ5(0,0,1,1,1)
      - HZ5(0,1,0,1,1);
    HZ5(1,1,0,1,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(1)*HZ1(1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ1(1)*HZ3(0,1,1)
      + 3.0000000000000000e+00*HZ1(0)*HZ4(0,1,1,1)
      - HZ1(1) *HZ1(1)*HZ3(0,0,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ2(0,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(0,0,1,1)
      - HZ2(0,1) *HZ3(0,1,1)
      + HZ5(0,1,0,1,1);
    HZ5(1,1,0,1,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,1,1)
      - 3.0000000000000000e+00*HZ1(1)*HZ4(0,1,1,1)
      + 6.0000000000000000e+00*HZ5(0,1,1,1,1);
    HZ5(1,1,1,0,0) =
      + 8.3333333333333333e-02*HZ1(0)*HZ1(0)*HZ1(1)*HZ1(1)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(1)*HZ1(1)*HZ2(0,1)
      + HZ1(0) *HZ1(1)*HZ3(0,1,1)
      - HZ1(0) *HZ4(0,1,1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,0,1)
      - HZ1(1) *HZ4(0,0,1,1)
      + HZ5(0,0,1,1,1);
    HZ5(1,1,1,0,1) =
      + 1.6666666666666666e-01*HZ1(1)*HZ1(1)*HZ1(1)*HZ2(0,1)
      - HZ1(1) *HZ1(1)*HZ3(0,1,1)
      + 3.0000000000000000e+00*HZ1(1)*HZ4(0,1,1,1)
      - 4.0000000000000000e+00*HZ5(0,1,1,1,1);
    HZ5(1,1,1,1,0) =
      + 4.1666666666666666e-02*HZ1(0)*HZ1(1)*HZ1(1)*HZ1(1)*HZ1(1)
      - 1.6666666666666666e-01*HZ1(1)*HZ1(1)*HZ1(1)*HZ2(0,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,1,1)
      - HZ1(1) *HZ4(0,1,1,1)
      + HZ5(0,1,1,1,1);
    HZ5(1,1,1,1,1) =
      + 8.3333333333333333e-03*HZ1(1)*HZ1(1)*HZ1(1)*HZ1(1)*HZ1(1);
  }

  if (    ( (n1 == -1) && (n2 == 0) )
       || ( (n1 == -1) && (n2 == 1) ) ){

    HZ5(-1,-1,-1,-1,-1) =
      + 8.3333333333333333e-03*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(-1);
    HZ5(-1,-1,-1,-1,0) =
      + 4.1666666666666666e-02*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(0)
      - 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,-1,-1)
      - HZ1( -1)*HZ4(0,-1,-1,-1)
      + HZ5(0, -1,-1,-1,-1);
    HZ5(-1,-1,-1,0,-1) =
      + 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,-1)
      - HZ1( -1)*HZ1(-1)*HZ3(0,-1,-1)
      + 3.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,-1,-1)
      - 4.0000000000000000e+00*HZ5(0,-1,-1,-1,-1);
    HZ5(-1,-1,-1,0,0) =
      + 8.3333333333333333e-02*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ1(0)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,0,-1)
      + HZ1( -1)*HZ1(0)*HZ3(0,-1,-1)
      - HZ1( -1)*HZ4(0,0,-1,-1)
      - HZ1(0) *HZ4(0,-1,-1,-1)
      + HZ5(0,0, -1,-1,-1);
    HZ5(-1,-1,0,-1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,-1,-1)
      - 3.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,-1,-1)
      + 6.0000000000000000e+00*HZ5(0,-1,-1,-1,-1);
    HZ5(-1,-1,0,-1,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ2(0,-1)
      - HZ1( -1)*HZ1(-1)*HZ3(0,0,-1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(0)*HZ3(0,-1,-1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ2(0,-1)*HZ2(0,-1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(0,0,-1,-1)
      + 3.0000000000000000e+00*HZ1(0)*HZ4(0,-1,-1,-1)
      - HZ2(0, -1)*HZ3(0,-1,-1)
      + HZ5(0, -1,0,-1,-1);
    HZ5(-1,-1,0,0,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,0,-1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ2(0,-1)*HZ2(0,-1)
      + HZ2(0, -1)*HZ3(0,-1,-1)
      - HZ5(0, -1,0,-1,-1)
      - 3.0000000000000000e+00*HZ5(0,0,-1,-1,-1);
    HZ5(-1,-1,0,0,0) =
      + 8.3333333333333333e-02*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ1(0)*HZ1(0)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ2(0,-1)
      + HZ1( -1)*HZ1(0)*HZ3(0,0,-1)
      - HZ1( -1)*HZ4(0,0,0,-1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,-1,-1)
      - HZ1(0) *HZ4(0,0,-1,-1)
      + HZ5(0,0,0, -1,-1);
    HZ5(-1,0,-1,-1,-1) =
      + HZ1( -1)*HZ4(0,-1,-1,-1)
      - 4.0000000000000000e+00*HZ5(0,-1,-1,-1,-1);
    HZ5(-1,0,-1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(0,-1,-1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ2(0,-1)*HZ2(0,-1)
      - 3.0000000000000000e+00*HZ1(0)*HZ4(0,-1,-1,-1)
      + 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,-1,-1)
      - 3.0000000000000000e+00*HZ5(0,-1,0,-1,-1)
      - 6.0000000000000000e+00*HZ5(0,0,-1,-1,-1);
    HZ5(-1,0,-1,0,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ2(0,-1)*HZ2(0,-1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(0,0,-1,-1)
      - 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,-1,-1)
      + 4.0000000000000000e+00*HZ5(0,-1,0,-1,-1)
      + 1.2000000000000000e+01*HZ5(0,0,-1,-1,-1);
    HZ5(-1,0,-1,0,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ2(0,-1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(0)*HZ3(0,0,-1)
      + 3.0000000000000000e+00*HZ1(-1)*HZ4(0,0,0,-1)
      - HZ1(0) *HZ1(0)*HZ3(0,-1,-1)
      + 5.0000000000000000e-01*HZ1(0)*HZ2(0,-1)*HZ2(0,-1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(0,0,-1,-1)
      - HZ2(0, -1)*HZ3(0,0,-1)
      + HZ5(0,0, -1,0,-1);
    HZ5(-1,0,0,-1,-1) =
      + HZ1( -1)*HZ4(0,0,-1,-1)
      - HZ5(0, -1,0,-1,-1)
      - 3.0000000000000000e+00*HZ5(0,0,-1,-1,-1);
    HZ5(-1,0,0,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(0,0,-1)
      - 3.0000000000000000e+00*HZ1(-1)*HZ4(0,0,0,-1)
      - 5.0000000000000000e-01*HZ1(0)*HZ2(0,-1)*HZ2(0,-1)
      + 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,0,-1)
      - 3.0000000000000000e+00*HZ5(0,0,-1,0,-1)
      - 6.0000000000000000e+00*HZ5(0,0,0,-1,-1);
    HZ5(-1,0,0,0,-1) =
      + HZ1( -1)*HZ4(0,0,0,-1)
      - HZ2(0, -1)*HZ3(0,0,-1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,0,-1)
      + 4.0000000000000000e+00*HZ5(0,0,0,-1,-1);
    HZ5(-1,0,0,0,0) =
      + 4.1666666666666666e-02*HZ1(-1)*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(0)
      - 1.6666666666666666e-01*HZ1(0)*HZ1(0)*HZ1(0)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,0,-1)
      - HZ1(0) *HZ4(0,0,0,-1)
      + HZ5(0,0,0,0, -1);
    HZ5(0,-1,-1,-1,0) =
      + HZ1(0) *HZ4(0,-1,-1,-1)
      - HZ2(0, -1)*HZ3(0,-1,-1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,-1,-1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,-1,-1);
    HZ5(0,-1,-1,0,-1) =
      + HZ2(0, -1)*HZ3(0,-1,-1)
      - 3.0000000000000000e+00*HZ5(0,-1,0,-1,-1)
      - 6.0000000000000000e+00*HZ5(0,0,-1,-1,-1);
    HZ5(0,-1,-1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,-1,-1)
      - 5.0000000000000000e-01*HZ1(0)*HZ2(0,-1)*HZ2(0,-1)
      + HZ2(0, -1)*HZ3(0,0,-1)
      - HZ5(0,0, -1,0,-1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,-1);
    HZ5(0,-1,0,-1,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ2(0,-1)*HZ2(0,-1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(0,0,-1,-1)
      - 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,0,-1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,0,-1)
      + 1.2000000000000000e+01*HZ5(0,0,0,-1,-1);
    HZ5(0,-1,0,0,-1) =
      + HZ2(0, -1)*HZ3(0,0,-1)
      - 3.0000000000000000e+00*HZ5(0,0,-1,0,-1)
      - 6.0000000000000000e+00*HZ5(0,0,0,-1,-1);
    HZ5(0,-1,0,0,0) =
      + 1.6666666666666666e-01*HZ1(0)*HZ1(0)*HZ1(0)*HZ2(0,-1)
      - HZ1(0) *HZ1(0)*HZ3(0,0,-1)
      + 3.0000000000000000e+00*HZ1(0)*HZ4(0,0,0,-1)
      - 4.0000000000000000e+00*HZ5(0,0,0,0,-1);
    HZ5(0,0,-1,-1,0) =
      + HZ1(0) *HZ4(0,0,-1,-1)
      - HZ5(0,0, -1,0,-1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,-1);
    HZ5(0,0,-1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,0,-1)
      - 3.0000000000000000e+00*HZ1(0)*HZ4(0,0,0,-1)
      + 6.0000000000000000e+00*HZ5(0,0,0,0,-1);
    HZ5(0,0,0,-1,0) =
      + HZ1(0) *HZ4(0,0,0,-1)
      - 4.0000000000000000e+00*HZ5(0,0,0,0,-1);
  }

  if ( (n1 == -1) && (n2 == 1) ){

    HZ5(-1,-1,-1,0,1) =
      + 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(-1,0,1)
      + HZ1( -1)*HZ4(-1,-1,0,1)
      - HZ5(0, -1,-1,-1,1)
      - HZ5(0, -1,-1,1,-1)
      - HZ5(0, -1,1,-1,-1)
      - HZ5(0,1, -1,-1,-1);
    HZ5(-1,-1,-1,1,-1) =
      + HZ1( -1)*HZ4(-1,-1,-1,1)
      - 4.0000000000000000e+00*HZ5(-1,-1,-1,-1,1);
    HZ5(-1,-1,-1,1,0) =
      - 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(-1,0,1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,-1,1)
      - HZ1( -1)*HZ4(-1,-1,0,1)
      - HZ1( -1)*HZ4(-1,0,-1,1)
      - HZ1( -1)*HZ4(0,-1,-1,1)
      + HZ1(0) *HZ4(-1,-1,-1,1)
      + HZ5(0,1, -1,-1,-1);
    HZ5(-1,-1,0,-1,1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,-1,1)
      + HZ1( -1)*HZ4(-1,0,-1,1)
      + 3.0000000000000000e+00*HZ5(0,-1,-1,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,-1,1,-1)
      + HZ5(0, -1,1,-1,-1);
    HZ5(-1,-1,0,0,1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,0,1)
      + HZ1( -1)*HZ4(-1,0,0,1)
      + HZ5(0, -1,-1,0,1)
      + HZ5(0, -1,0,-1,1)
      + HZ5(0, -1,0,1,-1)
      + HZ5(0,0, -1,-1,1)
      + HZ5(0,0, -1,1,-1)
      + HZ5(0,0,1, -1,-1);
    HZ5(-1,-1,0,1,-1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,1)
      + 1.5000000000000000e+00*HZ1(-1)*HZ1(-1)*HZ3(-1,0,1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,-1,0,1)
      - HZ1( -1)*HZ4(-1,0,-1,1)
      + HZ5(0, -1,-1,1,-1)
      + 2.0000000000000000e+00*HZ5(0,-1,1,-1,-1)
      + 3.0000000000000000e+00*HZ5(0,1,-1,-1,-1);
    HZ5(-1,-1,0,1,0) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,0,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,0,0,1)
      - HZ1( -1)*HZ4(0,-1,0,1)
      + HZ1(0) *HZ4(-1,-1,0,1)
      - HZ5(0, -1,-1,0,1)
      - HZ5(0, -1,0,-1,1)
      - HZ5(0, -1,0,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,1,-1,-1);
    HZ5(-1,-1,0,1,1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,1,1)
      + HZ1( -1)*HZ4(-1,0,1,1)
      + HZ5(0, -1,-1,1,1)
      + HZ5(0, -1,1,-1,1)
      + HZ5(0, -1,1,1,-1)
      + HZ5(0,1, -1,-1,1)
      + HZ5(0,1, -1,1,-1)
      + HZ5(0,1,1, -1,-1);
    HZ5(-1,-1,1,-1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(-1,-1,1)
      - 3.0000000000000000e+00*HZ1(-1)*HZ4(-1,-1,-1,1)
      + 6.0000000000000000e+00*HZ5(-1,-1,-1,-1,1);
    HZ5(-1,-1,1,-1,0) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,-1,1)
      + HZ1( -1)*HZ1(0)*HZ3(-1,-1,1)
      + HZ1( -1)*HZ4(-1,0,-1,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,-1,1)
      - 3.0000000000000000e+00*HZ1(0)*HZ4(-1,-1,-1,1)
      - HZ2(0, -1)*HZ3(-1,-1,1)
      + HZ5(0, -1,1,-1,-1);
    HZ5(-1,-1,1,0,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,1)
      - 1.5000000000000000e+00*HZ1(-1)*HZ1(-1)*HZ3(-1,0,1)
      - HZ1( -1)*HZ1(-1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,-1,0,1)
      + HZ1( -1)*HZ4(-1,0,-1,1)
      + HZ2(0, -1)*HZ3(-1,-1,1)
      - HZ5(0, -1,1,-1,-1)
      - 3.0000000000000000e+00*HZ5(0,1,-1,-1,-1);
    HZ5(-1,-1,1,0,0) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,0,1)
      + HZ1( -1)*HZ4(-1,0,0,1)
      + HZ1( -1)*HZ4(0,-1,0,1)
      + HZ1( -1)*HZ4(0,0,-1,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,-1,1)
      - HZ1(0) *HZ4(-1,-1,0,1)
      - HZ1(0) *HZ4(-1,0,-1,1)
      - HZ1(0) *HZ4(0,-1,-1,1)
      + HZ5(0,0,1, -1,-1);
    HZ5(-1,-1,1,0,1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,0,1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,1,1)
      - HZ1( -1)*HZ4(0,1,-1,1)
      + HZ2(0,1) *HZ3(-1,-1,1)
      - HZ5(0,1, -1,-1,1)
      - HZ5(0,1, -1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,1,1,-1,-1);
    HZ5(-1,-1,1,1,-1) =
      + HZ1( -1)*HZ4(-1,-1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,-1,-1,1,1)
      - HZ5( -1,-1,1,-1,1);
    HZ5(-1,-1,1,1,0) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(0,1,1)
      + HZ1( -1)*HZ4(-1,0,1,1)
      + HZ1( -1)*HZ4(0,-1,1,1)
      + HZ1( -1)*HZ4(0,1,-1,1)
      + HZ1(0) *HZ4(-1,-1,1,1)
      - HZ2(0,1) *HZ3(-1,-1,1)
      + HZ5(0,1,1, -1,-1);
    HZ5(-1,0,-1,-1,1) =
      + HZ1( -1)*HZ4(0,-1,-1,1)
      - 3.0000000000000000e+00*HZ5(0,-1,-1,-1,1)
      - HZ5(0, -1,-1,1,-1);
    HZ5(-1,0,-1,0,1) =
      + HZ1( -1)*HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,0,1)
      - HZ5(0, -1,0,-1,1)
      - HZ5(0, -1,0,1,-1);
    HZ5(-1,0,-1,1,-1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,-1,1)
      - HZ1( -1)*HZ4(-1,0,-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,-1,1,-1,-1);
    HZ5(-1,0,-1,1,0) =
      - HZ1( -1)*HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(0,0,-1,1)
      + HZ1(0) *HZ4(-1,0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,-1,0,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,-1,1)
      + HZ5(0, -1,0,1,-1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,1,-1);
    HZ5(-1,0,-1,1,1) =
      + HZ1( -1)*HZ4(0,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,1,1)
      - HZ5(0, -1,1,-1,1)
      - HZ5(0, -1,1,1,-1);
    HZ5(-1,0,0,-1,1) =
      + HZ1( -1)*HZ4(0,0,-1,1)
      - HZ5(0, -1,0,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      - HZ5(0,0, -1,1,-1);
    HZ5(-1,0,0,0,1) =
      + HZ1( -1)*HZ4(0,0,0,1)
      - HZ2(0, -1)*HZ3(0,0,1)
      + HZ5(0,0, -1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,0,0,1,-1)
      + HZ5(0,0,1,0, -1);
    HZ5(-1,0,0,1,-1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,0,1)
      - HZ1( -1)*HZ4(-1,0,0,1)
      - HZ1( -1)*HZ4(0,-1,0,1)
      - HZ1( -1)*HZ4(0,0,-1,1)
      - HZ5(0, -1,0,1,-1)
      - HZ5(0,0, -1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,1,-1,-1);
    HZ5(-1,0,0,1,0) =
      - 3.0000000000000000e+00*HZ1(-1)*HZ4(0,0,0,1)
      + HZ1(0) *HZ4(-1,0,0,1)
      + 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,0,1)
      - HZ5(0,0, -1,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,1,0,-1);
    HZ5(-1,0,0,1,1) =
      + HZ1( -1)*HZ4(0,0,1,1)
      - HZ5(0, -1,0,1,1)
      - HZ5(0,0, -1,1,1)
      - HZ5(0,0,1, -1,1)
      - HZ5(0,0,1,1, -1);
    HZ5(-1,0,1,-1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,1)
      - HZ1( -1)*HZ1(-1)*HZ3(-1,0,1)
      - HZ1( -1)*HZ1(-1)*HZ3(0,-1,1)
      + HZ1( -1)*HZ4(-1,-1,0,1)
      + HZ1( -1)*HZ4(-1,0,-1,1)
      + HZ1( -1)*HZ4(0,-1,-1,1)
      - HZ5(0, -1,1,-1,-1)
      - 3.0000000000000000e+00*HZ5(0,1,-1,-1,-1);
    HZ5(-1,0,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(-1,0,1)
      + HZ1( -1)*HZ4(0,-1,0,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(0,0,-1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(-1,-1,0,1)
      - HZ1(0) *HZ4(-1,0,-1,1)
      - HZ2(0, -1)*HZ3(-1,0,1)
      - 2.0000000000000000e+00*HZ5(0,-1,0,-1,1)
      - HZ5(0, -1,0,1,-1)
      - 4.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,1,-1);
    HZ5(-1,0,1,-1,1) =
      + HZ1( -1)*HZ4(0,1,-1,1)
      - HZ5(0, -1,1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,1,-1,-1,1)
      - HZ5(0,1, -1,1,-1);
    HZ5(-1,0,1,0,-1) =
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(-1)*HZ3(0,0,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,0,0,1)
      + HZ1( -1)*HZ4(0,-1,0,1)
      + HZ2(0, -1)*HZ3(-1,0,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,1,-1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,1,-1)
      + 4.0000000000000000e+00*HZ5(0,0,1,-1,-1);
    HZ5(-1,0,1,0,0) =
      + 3.0000000000000000e+00*HZ1(-1)*HZ4(0,0,0,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,0,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(-1,0,0,1)
      - HZ1(0) *HZ4(0,-1,0,1)
      - HZ2(0, -1)*HZ3(0,0,1)
      + HZ5(0,0,1,0, -1);
    HZ5(-1,0,1,0,1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ2(0,1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(0,0,1,1)
      + HZ2(0,1) *HZ3(-1,0,1)
      + HZ2(0,1) *HZ3(0,-1,1)
      - HZ5(0, -1,1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,1,-1,1)
      + 4.0000000000000000e+00*HZ5(0,0,1,1,-1)
      + HZ5(0,1,0,1, -1);
    HZ5(-1,0,1,1,-1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,1,1)
      - HZ1( -1)*HZ4(-1,0,1,1)
      - HZ1( -1)*HZ4(0,-1,1,1)
      - HZ1( -1)*HZ4(0,1,-1,1)
      - HZ5(0, -1,1,1,-1)
      - HZ5(0,1, -1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,1,1,-1,-1);
    HZ5(-1,0,1,1,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ2(0,1)*HZ2(0,1)
      + HZ1(0) *HZ4(-1,0,1,1)
      - HZ2(0,1) *HZ3(-1,0,1)
      - HZ2(0,1) *HZ3(0,-1,1)
      + HZ5(0, -1,0,1,1)
      + HZ5(0, -1,1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,0,1,1,-1)
      - HZ5(0,1,0,1, -1);
    HZ5(-1,0,1,1,1) =
      + HZ1( -1)*HZ4(0,1,1,1)
      - HZ5(0, -1,1,1,1)
      - HZ5(0,1, -1,1,1)
      - HZ5(0,1,1, -1,1)
      - HZ5(0,1,1,1, -1);
    HZ5(-1,1,-1,-1,-1) =
      + 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(-1,1)
      - HZ1( -1)*HZ1(-1)*HZ3(-1,-1,1)
      + 3.0000000000000000e+00*HZ1(-1)*HZ4(-1,-1,-1,1)
      - 4.0000000000000000e+00*HZ5(-1,-1,-1,-1,1);
    HZ5(-1,1,-1,-1,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(0)*HZ3(-1,-1,1)
      - HZ1( -1)*HZ2(-1,1)*HZ2(0,-1)
      - HZ1( -1)*HZ4(0,-1,-1,1)
      + 3.0000000000000000e+00*HZ1(0)*HZ4(-1,-1,-1,1)
      + HZ2( -1,1)*HZ3(0,-1,-1)
      + 2.0000000000000000e+00*HZ2(0,-1)*HZ3(-1,-1,1)
      + HZ5(0, -1,-1,1,-1);
    HZ5(-1,1,-1,-1,1) =
      + HZ2( -1,1)*HZ3(-1,-1,1)
      - 6.0000000000000000e+00*HZ5(-1,-1,-1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,-1,1,-1,1);
    HZ5(-1,1,-1,0,-1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,-1,1)
      + HZ1( -1)*HZ2(-1,1)*HZ2(0,-1)
      - HZ1( -1)*HZ4(-1,0,-1,1)
      - 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,-1,-1)
      - 2.0000000000000000e+00*HZ2(0,-1)*HZ3(-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,-1,1,-1,-1);
    HZ5(-1,1,-1,0,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ2(-1,1)
      - HZ1( -1)*HZ4(0,0,-1,1)
      - HZ1(0) *HZ1(0)*HZ3(-1,-1,1)
      - HZ1(0) *HZ2(-1,1)*HZ2(0,-1)
      + HZ1(0) *HZ4(-1,0,-1,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(0,-1,-1,1)
      + HZ2( -1,1)*HZ3(0,0,-1)
      + HZ5(0,0, -1,1,-1);
    HZ5(-1,1,-1,0,1) =
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,1,1)
      + HZ1( -1)*HZ4(0,1,-1,1)
      + HZ2( -1,1)*HZ3(-1,0,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(-1,-1,1)
      - HZ5(0, -1,1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,1,1,-1)
      - HZ5(0,1, -1,1,-1);
    HZ5(-1,1,-1,1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ2(-1,1)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,-1,1,1)
      - 2.0000000000000000e+00*HZ2(-1,1)*HZ3(-1,-1,1)
      + 1.2000000000000000e+01*HZ5(-1,-1,-1,1,1)
      + 4.0000000000000000e+00*HZ5(-1,-1,1,-1,1);
    HZ5(-1,1,-1,1,0) =
      - HZ1( -1)*HZ4(0,1,-1,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ2(-1,1)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(-1,-1,1,1)
      - HZ2( -1,1)*HZ3(-1,0,1)
      - HZ2( -1,1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(-1,-1,1)
      + HZ5(0,1, -1,1,-1);
    HZ5(-1,1,0,-1,-1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(0,1)
      + HZ1( -1)*HZ1(-1)*HZ3(-1,0,1)
      - HZ1( -1)*HZ4(-1,-1,0,1)
      + HZ2( -1,1)*HZ3(0,-1,-1)
      + HZ5(0, -1,-1,1,-1)
      + 2.0000000000000000e+00*HZ5(0,-1,1,-1,-1)
      + 3.0000000000000000e+00*HZ5(0,1,-1,-1,-1);
    HZ5(-1,1,0,-1,0) =
      - HZ1( -1)*HZ1(0)*HZ3(-1,0,1)
      - HZ1( -1)*HZ1(0)*HZ3(0,-1,1)
      - HZ1( -1)*HZ4(0,-1,0,1)
      + HZ1(0) *HZ2(-1,1)*HZ2(0,-1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(-1,-1,0,1)
      + HZ1(0) *HZ4(-1,0,-1,1)
      - 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,0,-1)
      + HZ2(0, -1)*HZ3(-1,0,1)
      + HZ2(0, -1)*HZ3(0,-1,1)
      + HZ5(0, -1,0,1,-1);
    HZ5(-1,1,0,-1,1) =
      - 2.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,1,1)
      - HZ1( -1)*HZ4(0,1,-1,1)
      + HZ2( -1,1)*HZ3(0,-1,1)
      + HZ5(0, -1,1,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,1,1,-1)
      + 2.0000000000000000e+00*HZ5(0,1,-1,-1,1)
      + HZ5(0,1, -1,1,-1);
    HZ5(-1,1,0,0,-1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,0,1)
      - HZ1( -1)*HZ4(-1,0,0,1)
      + HZ2( -1,1)*HZ3(0,0,-1)
      - HZ2(0, -1)*HZ3(-1,0,1)
      - HZ2(0, -1)*HZ3(0,-1,1)
      - HZ5(0, -1,0,1,-1)
      - HZ5(0,0, -1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,1,-1,-1);
    HZ5(-1,1,0,0,0) =
      - HZ1( -1)*HZ4(0,0,0,1)
      + 1.6666666666666666e-01*HZ1(0)*HZ1(0)*HZ1(0)*HZ2(-1,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,0,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,-1,1)
      + HZ1(0) *HZ4(-1,0,0,1)
      + HZ1(0) *HZ4(0,-1,0,1)
      + HZ1(0) *HZ4(0,0,-1,1)
      + HZ5(0,0,0,1, -1);
    HZ5(-1,1,0,0,1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ2(0,1)*HZ2(0,1)
      + HZ2( -1,1)*HZ3(0,0,1)
      - HZ2(0,1) *HZ3(-1,0,1)
      - HZ2(0,1) *HZ3(0,-1,1)
      - HZ5(0,0,1, -1,1)
      - 2.0000000000000000e+00*HZ5(0,0,1,1,-1)
      - HZ5(0,1,0,1, -1);
    HZ5(-1,1,0,1,-1) =
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(-1)*HZ3(0,1,1)
      + HZ1( -1)*HZ2(-1,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,0,1,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(0,-1,1,1)
      + HZ1( -1)*HZ4(0,1,-1,1)
      - HZ2( -1,1)*HZ3(-1,0,1)
      - HZ2( -1,1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,1,-1,1,-1)
      + 4.0000000000000000e+00*HZ5(0,1,1,-1,-1);
    HZ5(-1,1,0,1,0) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ2(0,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(0,0,1,1)
      + HZ1(0) *HZ2(-1,1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(-1,0,1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(0,-1,1,1)
      - HZ1(0) *HZ4(0,1,-1,1)
      - 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,0,1)
      + HZ2(0,1) *HZ3(-1,0,1)
      + HZ2(0,1) *HZ3(0,-1,1)
      + HZ5(0,1,0,1, -1);
    HZ5(-1,1,0,1,1) =
      - 3.0000000000000000e+00*HZ1(-1)*HZ4(0,1,1,1)
      + HZ2( -1,1)*HZ3(0,1,1)
      + HZ5(0,1, -1,1,1)
      + 2.0000000000000000e+00*HZ5(0,1,1,-1,1)
      + 3.0000000000000000e+00*HZ5(0,1,1,1,-1);
    HZ5(-1,1,1,-1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(-1,1,1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ2(-1,1)*HZ2(-1,1)
      + HZ2( -1,1)*HZ3(-1,-1,1)
      - 3.0000000000000000e+00*HZ5(-1,-1,-1,1,1)
      - HZ5( -1,-1,1,-1,1);
    HZ5(-1,1,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(-1,1,1)
      - HZ1( -1)*HZ4(0,-1,1,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ2(-1,1)*HZ2(-1,1)
      + HZ2( -1,1)*HZ3(0,-1,1)
      - HZ2(0, -1)*HZ3(-1,1,1)
      + HZ5(0, -1,1,1,-1);
    HZ5(-1,1,1,-1,1) =
      + HZ2( -1,1)*HZ3(-1,1,1)
      - 6.0000000000000000e+00*HZ5(-1,-1,1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,1,-1,1,1);
    HZ5(-1,1,1,0,-1) =
      + HZ1( -1)*HZ1(-1)*HZ3(0,1,1)
      - HZ1( -1)*HZ2(-1,1)*HZ2(0,1)
      - HZ1( -1)*HZ4(-1,0,1,1)
      + HZ2( -1,1)*HZ3(-1,0,1)
      + HZ2(0, -1)*HZ3(-1,1,1)
      - HZ5(0, -1,1,1,-1)
      - HZ5(0,1, -1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,1,1,-1,-1);
    HZ5(-1,1,1,0,0) =
      - HZ1( -1)*HZ4(0,0,1,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,1,1)
      - HZ1(0) *HZ2(-1,1)*HZ2(0,1)
      + HZ1(0) *HZ4(-1,0,1,1)
      + HZ1(0) *HZ4(0,-1,1,1)
      + HZ1(0) *HZ4(0,1,-1,1)
      + HZ2( -1,1)*HZ3(0,0,1)
      + HZ5(0,0,1,1, -1);
    HZ5(-1,1,1,0,1) =
      + 3.0000000000000000e+00*HZ1(-1)*HZ4(0,1,1,1)
      - 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,1,1)
      + HZ2(0,1) *HZ3(-1,1,1)
      - HZ5(0,1,1, -1,1)
      - 3.0000000000000000e+00*HZ5(0,1,1,1,-1);
    HZ5(-1,1,1,1,-1) =
      + HZ1( -1)*HZ4(-1,1,1,1)
      - HZ2( -1,1)*HZ3(-1,1,1)
      + 4.0000000000000000e+00*HZ5(-1,-1,1,1,1)
      + 2.0000000000000000e+00*HZ5(-1,1,-1,1,1);
    HZ5(-1,1,1,1,0) =
      - HZ1( -1)*HZ4(0,1,1,1)
      + HZ1(0) *HZ4(-1,1,1,1)
      + HZ2( -1,1)*HZ3(0,1,1)
      - HZ2(0,1) *HZ3(-1,1,1)
      + HZ5(0,1,1,1, -1);
    HZ5(0,-1,-1,1,0) =
      + HZ1(0) *HZ4(0,-1,-1,1)
      - HZ5(0, -1,-1,0,1)
      - HZ5(0, -1,0,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,-1,1);
    HZ5(0,-1,0,0,1) =
      + HZ2(0, -1)*HZ3(0,0,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,-1)
      - HZ5(0,0,1,0, -1);
    HZ5(0,-1,0,1,0) =
      + HZ1(0) *HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,0,1)
      + 6.0000000000000000e+00*HZ5(0,0,0,-1,1)
      + 6.0000000000000000e+00*HZ5(0,0,0,1,-1)
      + 2.0000000000000000e+00*HZ5(0,0,1,0,-1);
    HZ5(0,-1,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(0,-1,1)
      - HZ1(0) *HZ4(-1,0,-1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(0,-1,-1,1)
      - HZ2(0, -1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,-1,1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,-1,1);
    HZ5(0,-1,1,0,-1) =
      + HZ2(0, -1)*HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,0,-1,1)
      - HZ5(0, -1,0,1,-1)
      - 4.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,1,-1);
    HZ5(0,-1,1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,-1,1)
      - HZ1(0) *HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(0,0,-1,1)
      + HZ2(0, -1)*HZ3(0,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,-1)
      - HZ5(0,0,1,0, -1);
    HZ5(0,-1,1,1,0) =
      + HZ1(0) *HZ4(0,-1,1,1)
      - HZ5(0, -1,0,1,1)
      - HZ5(0, -1,1,0,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,1,1);
    HZ5(0,0,-1,1,0) =
      + HZ1(0) *HZ4(0,0,-1,1)
      - HZ5(0,0, -1,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,1);
    HZ5(0,0,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(0,0,1)
      - HZ1(0) *HZ4(-1,0,0,1)
      - HZ1(0) *HZ4(0,-1,0,1)
      - HZ1(0) *HZ4(0,0,-1,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,-1)
      - HZ5(0,0,1,0, -1);
    HZ5(0,1,-1,-1,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ2(0,1)
      - HZ1( -1)*HZ1(0)*HZ3(-1,0,1)
      - HZ1( -1)*HZ1(0)*HZ3(0,-1,1)
      - HZ1( -1)*HZ2(0,-1)*HZ2(0,1)
      + HZ1(0) *HZ4(-1,-1,0,1)
      + HZ1(0) *HZ4(-1,0,-1,1)
      + HZ1(0) *HZ4(0,-1,-1,1)
      + HZ2(0, -1)*HZ3(-1,0,1)
      + HZ2(0, -1)*HZ3(0,-1,1)
      + HZ2(0,1) *HZ3(0,-1,-1)
      - HZ5(0, -1,-1,0,1)
      - HZ5(0, -1,0,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,-1,1);
    HZ5(0,1,-1,0,-1) =
      + HZ1( -1)*HZ2(0,-1)*HZ2(0,1)
      - HZ2(0, -1)*HZ3(-1,0,1)
      - HZ2(0, -1)*HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,-1,-1)
      + 2.0000000000000000e+00*HZ5(0,-1,-1,0,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,-1,1)
      + HZ5(0, -1,0,1,-1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,1,-1);
    HZ5(0,1,-1,0,0) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ2(0,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,0,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,-1,1)
      - HZ1(0) *HZ2(0,-1)*HZ2(0,1)
      + HZ1(0) *HZ4(0,-1,0,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(0,0,-1,1)
      + HZ2(0,1) *HZ3(0,0,-1)
      - HZ5(0,0, -1,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,1);
    HZ5(0,1,-1,0,1) =
      + HZ1( -1)*HZ2(0,1)*HZ2(0,1)
      - HZ2(0,1) *HZ3(-1,0,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,1,1)
      + HZ5(0, -1,1,0,1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,1,1)
      - 4.0000000000000000e+00*HZ5(0,0,1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,1,0,1,-1);
    HZ5(0,1,-1,1,0) =
      - HZ1( -1)*HZ2(0,1)*HZ2(0,1)
      + HZ1(0) *HZ4(0,1,-1,1)
      + HZ2(0,1) *HZ3(-1,0,1)
      + HZ2(0,1) *HZ3(0,-1,1)
      + 4.0000000000000000e+00*HZ5(0,0,1,1,-1)
      + 2.0000000000000000e+00*HZ5(0,1,0,1,-1);
    HZ5(0,1,0,-1,-1) =
      + HZ2(0,1) *HZ3(0,-1,-1)
      - HZ5(0, -1,-1,0,1)
      - HZ5(0, -1,0,-1,1)
      - HZ5(0, -1,0,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,1,-1,-1);
    HZ5(0,1,0,-1,0) =
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(0)*HZ3(0,0,1)
      + HZ1(0) *HZ2(0,-1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(-1,0,0,1)
      + HZ1(0) *HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,0,-1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,0,1)
      + 6.0000000000000000e+00*HZ5(0,0,0,-1,1)
      + 6.0000000000000000e+00*HZ5(0,0,0,1,-1)
      + 2.0000000000000000e+00*HZ5(0,0,1,0,-1);
    HZ5(0,1,0,-1,1) =
      + HZ2(0,1) *HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,0,1,1)
      - HZ5(0, -1,1,0,1)
      - 4.0000000000000000e+00*HZ5(0,0,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,0,1,-1,1);
    HZ5(0,1,0,0,-1) =
      + HZ2(0,1) *HZ3(0,0,-1)
      - HZ5(0,0, -1,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,-1)
      - 2.0000000000000000e+00*HZ5(0,0,1,0,-1);
    HZ5(0,1,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(0,1,1)
      - HZ1(0) *HZ4(-1,0,1,1)
      - HZ1(0) *HZ4(0,-1,1,1)
      - HZ1(0) *HZ4(0,1,-1,1)
      - HZ2(0, -1)*HZ3(0,1,1)
      + HZ2(0,1) *HZ3(0,-1,1)
      - HZ5(0, -1,0,1,1)
      - HZ5(0, -1,1,0,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,1,1);
    HZ5(0,1,1,0,-1) =
      + HZ2(0, -1)*HZ3(0,1,1)
      - HZ2(0,1) *HZ3(0,-1,1)
      + HZ5(0, -1,0,1,1)
      + HZ5(0, -1,1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,0,1,1,-1)
      - HZ5(0,1,0,1, -1);
    HZ5(1,-1,-1,-1,-1) =
      + 4.1666666666666666e-02*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(1)
      - 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ2(-1,1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(-1,-1,1)
      - HZ1( -1)*HZ4(-1,-1,-1,1)
      + HZ5( -1,-1,-1,-1,1);
    HZ5(1,-1,-1,-1,0) =
      + 1.6666666666666666e-01*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ2(-1,1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ2(0,-1)
      + HZ1( -1)*HZ1(0)*HZ3(-1,-1,1)
      + HZ1( -1)*HZ1(1)*HZ3(0,-1,-1)
      + HZ1( -1)*HZ2(-1,1)*HZ2(0,-1)
      - HZ1(0) *HZ4(-1,-1,-1,1)
      - HZ1(1) *HZ4(0,-1,-1,-1)
      - HZ2( -1,1)*HZ3(0,-1,-1)
      - HZ2(0, -1)*HZ3(-1,-1,1)
      + HZ5(0, -1,-1,-1,1);
    HZ5(1,-1,-1,-1,1) =
      + HZ1(1) *HZ4(-1,-1,-1,1)
      - HZ2( -1,1)*HZ3(-1,-1,1)
      + 4.0000000000000000e+00*HZ5(-1,-1,-1,1,1)
      + 2.0000000000000000e+00*HZ5(-1,-1,1,-1,1);
    HZ5(1,-1,-1,0,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ2(0,-1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(1)*HZ3(0,-1,-1)
      - HZ1( -1)*HZ2(-1,1)*HZ2(0,-1)
      + 3.0000000000000000e+00*HZ1(1)*HZ4(0,-1,-1,-1)
      + 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,-1,-1)
      + HZ2(0, -1)*HZ3(-1,-1,1)
      - 3.0000000000000000e+00*HZ5(0,-1,-1,-1,1)
      - HZ5(0, -1,-1,1,-1);
    HZ5(1,-1,-1,0,0) =
      + 2.5000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ1(0)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ2(-1,1)
      - HZ1( -1)*HZ1(0)*HZ1(1)*HZ2(0,-1)
      + HZ1( -1)*HZ1(1)*HZ3(0,0,-1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,-1,1)
      + HZ1(0) *HZ1(1)*HZ3(0,-1,-1)
      + HZ1(0) *HZ2(-1,1)*HZ2(0,-1)
      - HZ1(0) *HZ4(0,-1,-1,1)
      - HZ1(1) *HZ4(0,0,-1,-1)
      - HZ2( -1,1)*HZ3(0,0,-1)
      + HZ5(0,0, -1,-1,1);
    HZ5(1,-1,-1,0,1) =
      + HZ1(1) *HZ4(-1,-1,0,1)
      - HZ2( -1,1)*HZ3(-1,0,1)
      + HZ2(0,1) *HZ3(-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,1,1)
      - HZ5(0, -1,1,-1,1)
      - HZ5(0,1, -1,-1,1);
    HZ5(1,-1,-1,1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(-1,-1,1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ2(-1,1)*HZ2(-1,1)
      - 3.0000000000000000e+00*HZ1(1)*HZ4(-1,-1,-1,1)
      + 2.0000000000000000e+00*HZ2(-1,1)*HZ3(-1,-1,1)
      - 6.0000000000000000e+00*HZ5(-1,-1,-1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,-1,1,-1,1);
    HZ5(1,-1,-1,1,0) =
      + HZ1(0) *HZ1(1)*HZ3(-1,-1,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ2(-1,1)*HZ2(-1,1)
      - HZ1(1) *HZ4(-1,-1,0,1)
      - HZ1(1) *HZ4(-1,0,-1,1)
      - HZ1(1) *HZ4(0,-1,-1,1)
      + HZ2( -1,1)*HZ3(-1,0,1)
      + HZ2( -1,1)*HZ3(0,-1,1)
      - HZ2(0,1) *HZ3(-1,-1,1)
      + HZ5(0,1, -1,-1,1);
    HZ5(1,-1,-1,1,1) =
      + HZ1(1) *HZ4(-1,-1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,-1,1,1,1)
      - HZ5( -1,1,-1,1,1);
    HZ5(1,-1,0,-1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(0,-1,-1)
      - 3.0000000000000000e+00*HZ1(1)*HZ4(0,-1,-1,-1)
      - HZ2( -1,1)*HZ3(0,-1,-1)
      + 3.0000000000000000e+00*HZ5(0,-1,-1,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,-1,1,-1)
      + HZ5(0, -1,1,-1,-1);
    HZ5(1,-1,0,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ1(1)*HZ2(0,-1)
      + HZ1( -1)*HZ1(0)*HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(1)*HZ3(0,0,-1)
      - 2.0000000000000000e+00*HZ1(0)*HZ1(1)*HZ3(0,-1,-1)
      - HZ1(0) *HZ2(-1,1)*HZ2(0,-1)
      - HZ1(0) *HZ4(-1,0,-1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ2(0,-1)*HZ2(0,-1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(0,0,-1,-1)
      + 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,0,-1)
      - HZ2(0, -1)*HZ3(0,-1,1)
      + HZ5(0, -1,0,-1,1);
    HZ5(1,-1,0,-1,1) =
      + HZ1(1) *HZ4(-1,0,-1,1)
      - HZ2( -1,1)*HZ3(0,-1,1)
      + 4.0000000000000000e+00*HZ5(0,-1,-1,1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,1,-1,1);
    HZ5(1,-1,0,0,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(0,0,-1)
      - 5.0000000000000000e-01*HZ1(1)*HZ2(0,-1)*HZ2(0,-1)
      - HZ2( -1,1)*HZ3(0,0,-1)
      + HZ2(0, -1)*HZ3(0,-1,1)
      - HZ5(0, -1,0,-1,1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,-1,1)
      - HZ5(0,0, -1,1,-1);
    HZ5(1,-1,0,0,0) =
      + 1.6666666666666666e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ1(0)*HZ1(1)
      - 1.6666666666666666e-01*HZ1(0)*HZ1(0)*HZ1(0)*HZ2(-1,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ1(1)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(0,-1,1)
      + HZ1(0) *HZ1(1)*HZ3(0,0,-1)
      - HZ1(0) *HZ4(0,0,-1,1)
      - HZ1(1) *HZ4(0,0,0,-1)
      + HZ5(0,0,0, -1,1);
    HZ5(1,-1,0,0,1) =
      + HZ1(1) *HZ4(-1,0,0,1)
      - HZ2( -1,1)*HZ3(0,0,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,1,1)
      + HZ5(0, -1,1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,1,1)
      + HZ5(0,0,1, -1,1);
    HZ5(1,-1,0,1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(-1,0,1)
      - HZ1( -1)*HZ2(-1,1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(-1,-1,0,1)
      - HZ1(1) *HZ4(-1,0,-1,1)
      + HZ2( -1,1)*HZ3(-1,0,1)
      + HZ2( -1,1)*HZ3(0,-1,1)
      + HZ5(0, -1,1,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,1,1,-1)
      + 2.0000000000000000e+00*HZ5(0,1,-1,-1,1)
      + HZ5(0,1, -1,1,-1);
    HZ5(1,-1,0,1,0) =
      + HZ1(0) *HZ1(1)*HZ3(-1,0,1)
      - HZ1(0) *HZ2(-1,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(0,-1,1,1)
      + HZ1(0) *HZ4(0,1,-1,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(-1,0,0,1)
      - HZ1(1) *HZ4(0,-1,0,1)
      + 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,0,1)
      - 2.0000000000000000e+00*HZ5(0,-1,0,1,1)
      - HZ5(0, -1,1,0,1)
      - 4.0000000000000000e+00*HZ5(0,0,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,0,1,-1,1);
    HZ5(1,-1,0,1,1) =
      + HZ1(1) *HZ4(-1,0,1,1)
      - HZ2( -1,1)*HZ3(0,1,1)
      + 3.0000000000000000e+00*HZ5(0,-1,1,1,1)
      + 2.0000000000000000e+00*HZ5(0,1,-1,1,1)
      + HZ5(0,1,1, -1,1);
    HZ5(1,-1,1,-1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ2(-1,1)
      - HZ1( -1)*HZ1(-1)*HZ3(-1,1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(1)*HZ3(-1,-1,1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ2(-1,1)*HZ2(-1,1)
      + 2.0000000000000000e+00*HZ1(-1)*HZ4(-1,-1,1,1)
      + 3.0000000000000000e+00*HZ1(1)*HZ4(-1,-1,-1,1)
      - HZ2( -1,1)*HZ3(-1,-1,1)
      + HZ5( -1,-1,1,-1,1);
    HZ5(1,-1,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ1(1)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(0)*HZ3(-1,1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ1(1)*HZ3(-1,-1,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ2(-1,1)*HZ2(-1,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(-1,-1,1,1)
      - HZ1(1) *HZ2(-1,1)*HZ2(0,-1)
      + HZ1(1) *HZ4(-1,0,-1,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(0,-1,-1,1)
      - HZ2( -1,1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ2(0,-1)*HZ3(-1,1,1)
      + HZ5(0, -1,1,-1,1);
    HZ5(1,-1,1,-1,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ2(-1,1)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(-1,-1,1,1)
      - 2.0000000000000000e+00*HZ2(-1,1)*HZ3(-1,1,1)
      + 1.2000000000000000e+01*HZ5(-1,-1,1,1,1)
      + 4.0000000000000000e+00*HZ5(-1,1,-1,1,1);
    HZ5(1,-1,1,0,-1) =
      - HZ1( -1)*HZ1(1)*HZ3(-1,0,1)
      - HZ1( -1)*HZ1(1)*HZ3(0,-1,1)
      + HZ1( -1)*HZ2(-1,1)*HZ2(0,1)
      + HZ1(1) *HZ2(-1,1)*HZ2(0,-1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(-1,-1,0,1)
      + HZ1(1) *HZ4(-1,0,-1,1)
      - HZ2( -1,1)*HZ3(-1,0,1)
      - 2.0000000000000000e+00*HZ2(0,-1)*HZ3(-1,1,1)
      - HZ5(0, -1,1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,1,-1,-1,1)
      - HZ5(0,1, -1,1,-1);
    HZ5(1,-1,1,0,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ1(1)*HZ2(-1,1)
      - HZ1(0) *HZ1(0)*HZ3(-1,1,1)
      - HZ1(0) *HZ1(1)*HZ3(-1,0,1)
      - HZ1(0) *HZ1(1)*HZ3(0,-1,1)
      + HZ1(0) *HZ2(-1,1)*HZ2(0,1)
      - HZ1(0) *HZ4(0,1,-1,1)
      + HZ1(1) *HZ4(-1,0,0,1)
      + HZ1(1) *HZ4(0,-1,0,1)
      + HZ1(1) *HZ4(0,0,-1,1)
      - HZ2( -1,1)*HZ3(0,0,1)
      + HZ5(0,0,1, -1,1);
    HZ5(1,-1,1,0,1) =
      + HZ1(1) *HZ2(-1,1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(-1,0,1,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(0,-1,1,1)
      - HZ1(1) *HZ4(0,1,-1,1)
      + 2.0000000000000000e+00*HZ2(-1,1)*HZ3(0,1,1)
      - 2.0000000000000000e+00*HZ2(0,1)*HZ3(-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,1,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,1,1,-1,1);
    HZ5(1,-1,1,1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(-1,1,1)
      - 3.0000000000000000e+00*HZ1(-1)*HZ4(-1,1,1,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ2(-1,1)*HZ2(-1,1)
      + 2.0000000000000000e+00*HZ2(-1,1)*HZ3(-1,1,1)
      - 6.0000000000000000e+00*HZ5(-1,-1,1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,1,-1,1,1);
    HZ5(1,-1,1,1,0) =
      + HZ1(0) *HZ1(1)*HZ3(-1,1,1)
      - 3.0000000000000000e+00*HZ1(0)*HZ4(-1,1,1,1)
      - HZ1(1) *HZ2(-1,1)*HZ2(0,1)
      + HZ1(1) *HZ4(-1,0,1,1)
      + HZ1(1) *HZ4(0,-1,1,1)
      + HZ1(1) *HZ4(0,1,-1,1)
      - HZ2( -1,1)*HZ3(0,1,1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(-1,1,1)
      + HZ5(0,1,1, -1,1);
    HZ5(1,-1,1,1,1) =
      + HZ1(1) *HZ4(-1,1,1,1)
      - 4.0000000000000000e+00*HZ5(-1,1,1,1,1);
    HZ5(1,0,-1,-1,-1) =
      + HZ1(1) *HZ4(0,-1,-1,-1)
      - HZ5(0, -1,-1,-1,1)
      - HZ5(0, -1,-1,1,-1)
      - HZ5(0, -1,1,-1,-1)
      - HZ5(0,1, -1,-1,-1);
    HZ5(1,0,-1,-1,0) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ2(0,1)
      + HZ1( -1)*HZ1(0)*HZ3(-1,0,1)
      + HZ1( -1)*HZ2(0,-1)*HZ2(0,1)
      + HZ1(0) *HZ1(1)*HZ3(0,-1,-1)
      - HZ1(0) *HZ4(-1,-1,0,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ2(0,-1)*HZ2(0,-1)
      - HZ2(0, -1)*HZ3(-1,0,1)
      - HZ2(0,1) *HZ3(0,-1,-1)
      + HZ5(0, -1,-1,0,1);
    HZ5(1,0,-1,-1,1) =
      + HZ1(1) *HZ4(0,-1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,1,1)
      - HZ5(0, -1,1,-1,1)
      - HZ5(0,1, -1,-1,1);
    HZ5(1,0,-1,0,-1) =
      - HZ1( -1)*HZ2(0,-1)*HZ2(0,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ2(0,-1)*HZ2(0,-1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(0,0,-1,-1)
      + HZ2(0, -1)*HZ3(-1,0,1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,-1,-1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,0,1)
      - HZ5(0, -1,0,-1,1)
      - HZ5(0, -1,0,1,-1);
    HZ5(1,0,-1,0,0) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ2(0,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ1(1)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,0,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ1(1)*HZ3(0,0,-1)
      + HZ1(0) *HZ2(0,-1)*HZ2(0,1)
      - HZ1(0) *HZ4(0,-1,0,1)
      + 3.0000000000000000e+00*HZ1(1)*HZ4(0,0,0,-1)
      - HZ2(0,1) *HZ3(0,0,-1)
      + HZ5(0,0, -1,0,1);
    HZ5(1,0,-1,0,1) =
      - HZ1( -1)*HZ2(0,1)*HZ2(0,1)
      + HZ1(1) *HZ4(0,-1,0,1)
      + HZ2(0,1) *HZ3(-1,0,1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,-1,1)
      - 4.0000000000000000e+00*HZ5(0,-1,0,1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,1,0,1)
      - 4.0000000000000000e+00*HZ5(0,0,-1,1,1)
      + 4.0000000000000000e+00*HZ5(0,0,1,1,-1)
      + 2.0000000000000000e+00*HZ5(0,1,0,1,-1);
    HZ5(1,0,-1,1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(0,-1,1)
      - HZ1(1) *HZ4(-1,0,-1,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(0,-1,-1,1)
      - HZ5(0, -1,1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,1,1,-1)
      - HZ5(0,1, -1,1,-1);
    HZ5(1,0,-1,1,0) =
      + HZ1( -1)*HZ2(0,1)*HZ2(0,1)
      + HZ1(0) *HZ1(1)*HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ4(0,-1,1,1)
      - HZ1(0) *HZ4(0,1,-1,1)
      - HZ1(1) *HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(0,0,-1,1)
      - HZ2(0,1) *HZ3(-1,0,1)
      - HZ2(0,1) *HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,1,1)
      + HZ5(0, -1,1,0,1)
      + 4.0000000000000000e+00*HZ5(0,0,-1,1,1)
      - 4.0000000000000000e+00*HZ5(0,0,1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,1,0,1,-1);
    HZ5(1,0,-1,1,1) =
      + HZ1(1) *HZ4(0,-1,1,1)
      - 3.0000000000000000e+00*HZ5(0,-1,1,1,1)
      - HZ5(0,1, -1,1,1);
    HZ5(1,0,0,-1,-1) =
      + HZ1(1) *HZ4(0,0,-1,-1)
      - HZ2(0,1) *HZ3(0,-1,-1)
      + HZ5(0, -1,-1,0,1)
      + HZ5(0, -1,0,-1,1)
      + HZ5(0, -1,0,1,-1)
      + HZ5(0,0, -1,-1,1)
      + HZ5(0,0, -1,1,-1)
      + HZ5(0,0,1, -1,-1);
    HZ5(1,0,0,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ3(0,0,1)
      + HZ1(0) *HZ1(1)*HZ3(0,0,-1)
      - HZ1(0) *HZ2(0,-1)*HZ2(0,1)
      - HZ1(0) *HZ4(-1,0,0,1)
      - 3.0000000000000000e+00*HZ1(1)*HZ4(0,0,0,-1)
      + 2.0000000000000000e+00*HZ2(0,1)*HZ3(0,0,-1)
      - 2.0000000000000000e+00*HZ5(0,0,-1,0,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,-1,1)
      - 3.0000000000000000e+00*HZ5(0,0,0,1,-1)
      - HZ5(0,0,1,0, -1);
    HZ5(1,0,0,-1,1) =
      + HZ1(1) *HZ4(0,0,-1,1)
      - HZ2(0,1) *HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,-1,0,1,1)
      + HZ5(0, -1,1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,-1,1,1)
      + HZ5(0,0,1, -1,1);
    HZ5(1,0,0,0,-1) =
      + HZ1(1) *HZ4(0,0,0,-1)
      - HZ2(0,1) *HZ3(0,0,-1)
      + HZ5(0,0, -1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,0,-1,1)
      + 2.0000000000000000e+00*HZ5(0,0,0,1,-1)
      + HZ5(0,0,1,0, -1);
    HZ5(1,0,0,1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(0,0,1)
      - HZ1(1) *HZ4(-1,0,0,1)
      - HZ1(1) *HZ4(0,-1,0,1)
      - HZ1(1) *HZ4(0,0,-1,1)
      - HZ5(0,0,1, -1,1)
      - 2.0000000000000000e+00*HZ5(0,0,1,1,-1)
      - HZ5(0,1,0,1, -1);
    HZ5(1,0,1,-1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ2(0,1)
      - HZ1( -1)*HZ1(1)*HZ3(-1,0,1)
      - HZ1( -1)*HZ1(1)*HZ3(0,-1,1)
      + HZ1(1) *HZ4(-1,-1,0,1)
      + HZ1(1) *HZ4(-1,0,-1,1)
      + HZ1(1) *HZ4(0,-1,-1,1)
      - HZ5(0,1, -1,-1,1)
      - HZ5(0,1, -1,1,-1)
      - 2.0000000000000000e+00*HZ5(0,1,1,-1,-1);
    HZ5(1,0,1,-1,0) =
      + HZ1( -1)*HZ1(0)*HZ1(1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(0)*HZ3(0,1,1)
      - HZ1(0) *HZ1(1)*HZ3(-1,0,1)
      - HZ1(0) *HZ1(1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(-1,0,1,1)
      + 2.0000000000000000e+00*HZ1(0)*HZ4(0,-1,1,1)
      + HZ1(0) *HZ4(0,1,-1,1)
      - HZ1(1) *HZ2(0,-1)*HZ2(0,1)
      + HZ1(1) *HZ4(0,-1,0,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(0,0,-1,1)
      + 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,1,1)
      - HZ2(0,1) *HZ3(0,-1,1)
      + HZ5(0, -1,1,0,1);
    HZ5(1,0,1,-1,1) =
      + HZ1(1) *HZ4(0,1,-1,1)
      - 2.0000000000000000e+00*HZ5(0,1,-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,1,1,-1,1);
    HZ5(1,0,1,0,-1) =
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(1)*HZ3(0,0,1)
      + HZ1(1) *HZ2(0,-1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(-1,0,0,1)
      + HZ1(1) *HZ4(0,-1,0,1)
      - 2.0000000000000000e+00*HZ2(0,-1)*HZ3(0,1,1)
      + HZ2(0,1) *HZ3(0,-1,1)
      - HZ5(0, -1,1,0,1)
      + 2.0000000000000000e+00*HZ5(0,0,1,-1,1)
      + 4.0000000000000000e+00*HZ5(0,0,1,1,-1)
      + HZ5(0,1,0,1, -1);
    HZ5(1,0,1,1,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(0,1,1)
      - HZ1(1) *HZ4(-1,0,1,1)
      - HZ1(1) *HZ4(0,-1,1,1)
      - HZ1(1) *HZ4(0,1,-1,1)
      - HZ5(0,1,1, -1,1)
      - 3.0000000000000000e+00*HZ5(0,1,1,1,-1);
    HZ5(1,1,-1,-1,-1) =
      + 8.3333333333333333e-02*HZ1(-1)*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ2(-1,1)
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ3(-1,1,1)
      + HZ1( -1)*HZ1(1)*HZ3(-1,-1,1)
      - HZ1( -1)*HZ4(-1,-1,1,1)
      - HZ1(1) *HZ4(-1,-1,-1,1)
      + HZ5( -1,-1,-1,1,1);
    HZ5(1,1,-1,-1,0) =
      + 2.5000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(0)*HZ1(1)*HZ1(1)
      - HZ1( -1)*HZ1(0)*HZ1(1)*HZ2(-1,1)
      + HZ1( -1)*HZ1(0)*HZ3(-1,1,1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(1)*HZ1(1)*HZ2(0,-1)
      + HZ1(0) *HZ1(1)*HZ3(-1,-1,1)
      - HZ1(0) *HZ4(-1,-1,1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,-1,-1)
      + HZ1(1) *HZ2(-1,1)*HZ2(0,-1)
      - HZ1(1) *HZ4(0,-1,-1,1)
      - HZ2(0, -1)*HZ3(-1,1,1)
      + HZ5(0, -1,-1,1,1);
    HZ5(1,1,-1,-1,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,-1,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ2(-1,1)*HZ2(-1,1)
      + HZ2( -1,1)*HZ3(-1,1,1)
      - 3.0000000000000000e+00*HZ5(-1,-1,1,1,1)
      - HZ5( -1,1,-1,1,1);
    HZ5(1,1,-1,0,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(1)*HZ1(1)*HZ2(0,-1)
      + HZ1( -1)*HZ1(1)*HZ3(0,-1,1)
      - HZ1(1) *HZ1(1)*HZ3(0,-1,-1)
      - HZ1(1) *HZ2(-1,1)*HZ2(0,-1)
      - HZ1(1) *HZ4(-1,0,-1,1)
      + HZ2(0, -1)*HZ3(-1,1,1)
      - 2.0000000000000000e+00*HZ5(0,-1,-1,1,1)
      - HZ5(0, -1,1,-1,1)
      - HZ5(0, -1,1,1,-1);
    HZ5(1,1,-1,0,0) =
      + 2.5000000000000000e-01*HZ1(-1)*HZ1(0)*HZ1(0)*HZ1(1)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ1(1)*HZ2(-1,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(0)*HZ3(-1,1,1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(1)*HZ1(1)*HZ2(0,-1)
      + HZ1(0) *HZ1(1)*HZ3(0,-1,1)
      - HZ1(0) *HZ4(0,-1,1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,0,-1)
      - HZ1(1) *HZ4(0,0,-1,1)
      + HZ5(0,0, -1,1,1);
    HZ5(1,1,-1,0,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,0,1)
      - HZ1(1) *HZ2(-1,1)*HZ2(0,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(0,-1,1,1)
      + HZ1(1) *HZ4(0,1,-1,1)
      + HZ2(0,1) *HZ3(-1,1,1)
      - 3.0000000000000000e+00*HZ5(0,-1,1,1,1)
      - HZ5(0,1, -1,1,1);
    HZ5(1,1,-1,1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(1)*HZ1(1)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(1)*HZ3(-1,1,1)
      + 3.0000000000000000e+00*HZ1(-1)*HZ4(-1,1,1,1)
      - HZ1(1) *HZ1(1)*HZ3(-1,-1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ2(-1,1)*HZ2(-1,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(-1,-1,1,1)
      - HZ2( -1,1)*HZ3(-1,1,1)
      + HZ5( -1,1,-1,1,1);
    HZ5(1,1,-1,1,0) =
      + 5.0000000000000000e-01*HZ1(0)*HZ1(1)*HZ1(1)*HZ2(-1,1)
      - 2.0000000000000000e+00*HZ1(0)*HZ1(1)*HZ3(-1,1,1)
      + 3.0000000000000000e+00*HZ1(0)*HZ4(-1,1,1,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,0,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,-1,1)
      + HZ1(1) *HZ2(-1,1)*HZ2(0,1)
      - HZ1(1) *HZ4(0,1,-1,1)
      - HZ2(0,1) *HZ3(-1,1,1)
      + HZ5(0,1, -1,1,1);
    HZ5(1,1,-1,1,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,1,1)
      - 3.0000000000000000e+00*HZ1(1)*HZ4(-1,1,1,1)
      + 6.0000000000000000e+00*HZ5(-1,1,1,1,1);
    HZ5(1,1,0,-1,-1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ2(0,1)
      + HZ1( -1)*HZ1(1)*HZ3(-1,0,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,-1,-1)
      - HZ1(1) *HZ4(-1,-1,0,1)
      + HZ5(0, -1,-1,1,1)
      + HZ5(0, -1,1,-1,1)
      + HZ5(0, -1,1,1,-1)
      + HZ5(0,1, -1,-1,1)
      + HZ5(0,1, -1,1,-1)
      + HZ5(0,1,1, -1,-1);
    HZ5(1,1,0,-1,0) =
      - HZ1( -1)*HZ1(0)*HZ1(1)*HZ2(0,1)
      + HZ1( -1)*HZ1(0)*HZ3(0,1,1)
      + 5.0000000000000000e-01*HZ1(0)*HZ1(1)*HZ1(1)*HZ2(0,-1)
      + HZ1(0) *HZ1(1)*HZ3(-1,0,1)
      - HZ1(0) *HZ4(-1,0,1,1)
      - HZ1(1) *HZ1(1)*HZ3(0,0,-1)
      + HZ1(1) *HZ2(0,-1)*HZ2(0,1)
      - HZ1(1) *HZ4(0,-1,0,1)
      - HZ2(0, -1)*HZ3(0,1,1)
      + HZ5(0, -1,0,1,1);
    HZ5(1,1,0,-1,1) =
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,-1,1)
      - 2.0000000000000000e+00*HZ1(1)*HZ4(0,-1,1,1)
      - HZ1(1) *HZ4(0,1,-1,1)
      + 3.0000000000000000e+00*HZ5(0,-1,1,1,1)
      + 2.0000000000000000e+00*HZ5(0,1,-1,1,1)
      + HZ5(0,1,1, -1,1);
    HZ5(1,1,0,0,-1) =
      + HZ1( -1)*HZ1(1)*HZ3(0,0,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,0,-1)
      - HZ1(1) *HZ2(0,-1)*HZ2(0,1)
      - HZ1(1) *HZ4(-1,0,0,1)
      + HZ2(0, -1)*HZ3(0,1,1)
      - HZ5(0, -1,0,1,1)
      - HZ5(0,0, -1,1,1)
      - HZ5(0,0,1, -1,1)
      - HZ5(0,0,1,1, -1);
    HZ5(1,1,0,1,-1) =
      + 5.0000000000000000e-01*HZ1(-1)*HZ1(1)*HZ1(1)*HZ2(0,1)
      - 2.0000000000000000e+00*HZ1(-1)*HZ1(1)*HZ3(0,1,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,0,1)
      - 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,-1,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(-1,0,1,1)
      + 2.0000000000000000e+00*HZ1(1)*HZ4(0,-1,1,1)
      + HZ1(1) *HZ4(0,1,-1,1)
      + HZ5(0,1, -1,1,1)
      + 2.0000000000000000e+00*HZ5(0,1,1,-1,1)
      + 3.0000000000000000e+00*HZ5(0,1,1,1,-1);
    HZ5(1,1,1,-1,-1) =
      + 8.3333333333333333e-02*HZ1(-1)*HZ1(-1)*HZ1(1)*HZ1(1)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(1)*HZ1(1)*HZ2(-1,1)
      + HZ1( -1)*HZ1(1)*HZ3(-1,1,1)
      - HZ1( -1)*HZ4(-1,1,1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,-1,1)
      - HZ1(1) *HZ4(-1,-1,1,1)
      + HZ5( -1,-1,1,1,1);
    HZ5(1,1,1,-1,0) =
      + 1.6666666666666666e-01*HZ1(-1)*HZ1(0)*HZ1(1)*HZ1(1)*HZ1(1)
      - 5.0000000000000000e-01*HZ1(0)*HZ1(1)*HZ1(1)*HZ2(-1,1)
      + HZ1(0) *HZ1(1)*HZ3(-1,1,1)
      - HZ1(0) *HZ4(-1,1,1,1)
      - 1.6666666666666666e-01*HZ1(1)*HZ1(1)*HZ1(1)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(0,-1,1)
      - HZ1(1) *HZ4(0,-1,1,1)
      + HZ5(0, -1,1,1,1);
    HZ5(1,1,1,-1,1) =
      + 1.6666666666666666e-01*HZ1(1)*HZ1(1)*HZ1(1)*HZ2(-1,1)
      - HZ1(1) *HZ1(1)*HZ3(-1,1,1)
      + 3.0000000000000000e+00*HZ1(1)*HZ4(-1,1,1,1)
      - 4.0000000000000000e+00*HZ5(-1,1,1,1,1);
    HZ5(1,1,1,0,-1) =
      - 5.0000000000000000e-01*HZ1(-1)*HZ1(1)*HZ1(1)*HZ2(0,1)
      + HZ1( -1)*HZ1(1)*HZ3(0,1,1)
      + 1.6666666666666666e-01*HZ1(1)*HZ1(1)*HZ1(1)*HZ2(0,-1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,0,1)
      - HZ1(1) *HZ4(-1,0,1,1)
      - HZ5(0, -1,1,1,1)
      - HZ5(0,1, -1,1,1)
      - HZ5(0,1,1, -1,1)
      - HZ5(0,1,1,1, -1);
    HZ5(1,1,1,1,-1) =
      + 4.1666666666666666e-02*HZ1(-1)*HZ1(1)*HZ1(1)*HZ1(1)*HZ1(1)
      - 1.6666666666666666e-01*HZ1(1)*HZ1(1)*HZ1(1)*HZ2(-1,1)
      + 5.0000000000000000e-01*HZ1(1)*HZ1(1)*HZ3(-1,1,1)
      - HZ1(1) *HZ4(-1,1,1,1)
      + HZ5( -1,1,1,1,1);
  }

 }

 //************************************************************************
 //** the following routines contain th set of routines evaluating
 //** irreducible 1dhpl's for various values of the arguments
 //************************************************************************
 void hplog5::pfillh1(double y, CArr<1>& H1, HArr<1>& HY1, HArr<1>& Hi1, int n1, int n2)
 {
  // fillh1 evaluates the 1dhpl's of weight 1
  double pi = 3.14159265358979324;

  if ( n1 == -1){
    if ( y >= -1.0 ){
      HY1(-1) = log(1.0+y);
      Hi1(-1) = 0.0;
    }
    else if ( y < -1.0 ){
      HY1(-1) = log(-1.0-y);
      Hi1(-1) = 1.0;
    }
    H1(-1) = cdouble(HY1(-1), pi*Hi1(-1));
  }

  if ( y >= 0.0 ){
    HY1(0) = log(y);
    //Hi1(0) = 0.0;
  }
  else if ( y < 0.0 ){
    HY1(0) = log(-y);
    Hi1(0) = 1.0;
  }
  H1(0) = cdouble(HY1(0), pi*Hi1(0));
  if ( n2 == 1 ){
    if ( y >= 1.0 ){
      HY1(1) = - log(-1.0+y);
      Hi1(1) = 1.0;
    }
    else if ( y < 1.0 ){
      HY1(1) = - log(1.0-y);
      Hi1(1) = 0.0;
    }
    H1(1) = cdouble(HY1(1), pi*Hi1(1));
  }

 }

 void hplog5::pfillirr1dhplat0(double y, int nw, HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5, int n1, int n2)
 {
  // evaluate the HPL from their power series expansions
  // fillirr1dhplat0 is called by eval1dhplat0;
  // it is guaranteed that nw is in the range 1:4, and that (n1,n2)
  // take one of the pairs of values (0,1), (-1,0) or (-1,1)
  //
  // for y < 0 DOES NOT evaluates the immaginary part of H(0,y) = log(y)

  double u;
  double v;
  // evaluating the required 1dHPL of weight 1
  if ( n1 == -1){
  // 1+y = (1+ep)/(1-ep), ep = y/(2+y)
  // log(1+y) = log((1+y)/(1-y)) = 2*ep*(1+ep^2/3+ep^4/5+.....)
  // at y= -(r2-1) = - 0.4142135624, ep = - 0.26120387496
  // ep2 = 0.068227464296, ep2^13 = 6.9 x 10^(-16)
    double ep = y/(2.0+y);
    double e2 = ep*ep;
  //         v = log(1.d0+y)
    v = 2*ep*(1+e2*(1.0/ 3.0+e2*(1.0/ 5.0+e2*(1.0/ 7.0+e2*(1.0/ 9.0
               +e2*(1.0/11.0+e2*(1.0/13.0+e2*(1.0/15.0+e2*(1.0/17.0
               +e2*(1.0/19.0+e2*(1.0/21.0+e2*(1.0/23.0+e2*(1.0/25.0
               )))))))))))));
    HY1(-1) = v;
  }

  if (y >= 0.0){
    HY1(0) = log(y);
  }
  else{
    HY1(0) = log(-y);
  // the immaginary part is evaluated in the calling routine eval1dhplat0
  //       Hi1(0) = 1d0
  }

  if ( n2 == 1){
  // 1-y = (1-ep)/(1+ep), ep = y/(2-y)
    double ep = y/(2.0-y);
    double e2 = ep*ep;
  //         u = - log(1.d0-y)
    u = 2*ep*(1+e2*(1.0/ 3.0+e2*(1.0/ 5.0+e2*(1.0/ 7.0+e2*(1.0/ 9.0
               +e2*(1.0/11.0+e2*(1.0/13.0+e2*(1.0/15.0+e2*(1.0/17.0
               +e2*(1.0/19.0+e2*(1.0/21.0+e2*(1.0/23.0+e2*(1.0/25.0
               )))))))))))));
    HY1(1) = u;
  }

  if ( nw == 1 ) return;
  // from now on nw > 1
  // evaluating the Cebyshev polynomials for the expansions
  double ep = y;

  double tu01;
  double tu02;
  double tu03;
  double tu04;
  double tu05;
  double tu06;
  double tu07;
  double tu08;
  double tu09;
  double tu10;
  double tu11;
  double tu12;
  double tu13;

  double tv01;
  double tv02;
  double tv03;
  double tv04;
  double tv05;
  double tv06;
  double tv07;
  double tv08;
  double tv09;
  double tv10;
  double tv11;
  double tv12;
  double tv13;

  if ( n2 == 1){
    tu01 = 20.0/11.0*u;
    tu02 = 2.0*tu01*tu01 - 1.0;
    tu03 = 2.0*tu01*tu02 - tu01;
    tu04 = 2.0*tu01*tu03 - tu02;
    tu05 = 2.0*tu01*tu04 - tu03;
    tu06 = 2.0*tu01*tu05 - tu04;
    tu07 = 2.0*tu01*tu06 - tu05;
    tu08 = 2.0*tu01*tu07 - tu06;
    tu09 = 2.0*tu01*tu08 - tu07;
    tu10 = 2.0*tu01*tu09 - tu08;
    tu11 = 2.0*tu01*tu10 - tu09;
    tu12 = 2.0*tu01*tu11 - tu10;
    tu13 = 2.0*tu01*tu12 - tu11;
  }
  if ( n1 == -1 ){
    tv01 = 20.0/11.0*v;
    tv02 = 2.0*tv01*tv01 - 1.0;
    tv03 = 2.0*tv01*tv02 - tv01;
    tv04 = 2.0*tv01*tv03 - tv02;
    tv05 = 2.0*tv01*tv04 - tv03;
    tv06 = 2.0*tv01*tv05 - tv04;
    tv07 = 2.0*tv01*tv06 - tv05;
    tv08 = 2.0*tv01*tv07 - tv06;
    tv09 = 2.0*tv01*tv08 - tv07;
    tv10 = 2.0*tv01*tv09 - tv08;
    tv11 = 2.0*tv01*tv10 - tv09;
    tv12 = 2.0*tv01*tv11 - tv10;
    tv13 = 2.0*tv01*tv12 - tv11;
  }
  // evaluating the expansions
  // (n1,n2) = (0,1) or (-1,1)
  if (    ( (n1 == 0)  && (n2 == 1) )
       || ( (n1 == -1) && (n2 == 1) ) ){

    HY2(0,1) =
      - 3.781250000000000e-02
      + 5.534574473824441e-01*tu01
      - 3.781250000000000e-02*tu02
      + 1.151036617760703e-03*tu03
      - 8.659502433858922e-07*tu05
      + 1.109042494804544e-09*tu07
      - 1.624415058184216e-12*tu09
      + 2.528376460336939e-15*tu11;
  //    it would be wrong to write
  //    if ( nw.eq.2 ) return
  //    because the (n1.eq.-1).and.(n2.eq.1) case is not yet complete
    if ( nw > 2 ){
      HY3(0,0,1) =
       - 5.701592410758114e-02
       + 5.598247957892565e-01*tu01
       - 5.711486614505007e-02*tu02
       + 3.275603992203700e-03*tu03
       - 9.887255877938583e-05*tu04
       + 4.021153684652295e-07*tu05
       + 6.939288687864526e-08*tu06
       - 7.995347631322020e-10*tu07
       - 8.567978673919505e-11*tu08
       + 1.526387027481200e-12*tu09
       + 1.226899454816980e-13*tu10
       - 2.848614761014972e-15*tu11
       - 1.880542777479446e-16*tu12;
     HY3(0,1,1) =
       + 3.816894981500984e-02
       - 1.039843750000000e-02*tu01
       + 3.828760080995617e-02*tu02
       - 3.466145833333333e-03*tu03
       + 1.185518160084905e-04*tu04
       - 9.904555648775859e-08*tu06
       + 1.331803984518588e-10*tu08
       - 2.006389465106708e-13*tu10
       + 3.180731062055677e-16*tu12;
    }

    if ( nw > 3 ){
      HY4(0,0,0,1) =
       - 6.685228257646101e-02
       + 5.645990701998083e-01*tu01
       - 6.707912936340146e-02*tu02
       + 4.876429488624746e-03*tu03
       - 2.268732672568699e-04*tu04
       + 6.038494106229146e-06*tu05
       - 2.642577015932576e-08*tu06
       - 3.679843316593900e-09*tu07
       + 5.444046563879984e-11*tu08
       + 4.063821221202881e-12*tu09
       - 1.055985864474070e-13*tu10
       - 5.190408125225683e-15*tu11
       + 1.985464489219049e-16*tu12;
     HY4(0,0,1,1) =
       + 1.953236111099851e-02
       - 8.741612828671381e-03*tu01
       + 1.974116110893196e-02*tu02
       - 2.926558492394004e-03*tu03
       + 2.088576190269387e-04*tu04
       - 7.604351107741397e-06*tu05
       + 5.751031394942524e-08*tu06
       + 5.832253077603139e-09*tu07
       - 1.105713721511985e-10*tu08
       - 7.453416210082473e-12*tu09
       + 2.077758906032370e-13*tu10
       + 1.085601519719514e-14*tu11
       - 3.848312092795918e-16*tu12;
     HY4(0,1,1,1) =
       - 7.148925781250000e-04
       + 7.019393481825299e-03*tu01
       - 9.531901041666666e-04*tu02
       + 2.354287493676137e-03*tu03
       - 2.382975260416666e-04*tu04
       + 8.682904829408987e-06*tu05
       - 7.768198634676578e-09*tu07
       + 1.083130072188330e-11*tu09
       - 1.668810490326842e-14*tu11;
    }
    // nw > 3 endif

    if (nw > 4){
      HY5(0,0,0,0,1) =
       - 7.1883935399674661e-02
       + 5.6753782109711975e-01*tu01
       - 7.2212923207857999e-02*tu02
       + 5.8670869471466117e-03*tu03
       - 3.2928069579812269e-04*tu04
       + 1.2689437803900269e-05*tu05
       - 2.9273255639591246e-07*tu06
       + 1.0606320330117018e-09*tu07
       + 1.5490385851360920e-10*tu08
       - 2.2474559413025843e-12*tu09
       - 1.5435486840448295e-13*tu10
       + 4.3623305832897835e-15*tu11
       + 1.7529593826254750e-16*tu12;
     HY5(0,0,0,1,1) =
       + 1.0000521958818753e-02
       - 5.5972378484058781e-03*tu01
       + 1.0183616888857122e-02*tu02
       - 1.8839550865568384e-03*tu03
       + 1.8347215924120138e-04*tu04
       - 1.0930879320715947e-05*tu05
       + 3.7698877255509719e-07*tu06
       - 3.8459944472218428e-09*tu07
       - 2.4017837972601217e-10*tu08
       + 7.0263208823587761e-12*tu09
       + 2.5160915023993803e-13*tu10
       - 1.2783871754086183e-14*tu11
       - 2.8797679566416130e-16*tu12
       + 2.3134706555649888e-17*tu13;
     HY5(0,0,1,0,1) =
       + 1.9758848802070053e-02
       - 9.9630794104335436e-03*tu01
       + 2.0043658059117399e-02*tu02
       - 3.3447469330099638e-03*tu03
       + 2.8517465661196517e-04*tu04
       - 1.4231602601165430e-05*tu05
       + 3.6511844421403422e-07*tu06
       + 4.8298298252332493e-10*tu07
       - 2.8074265749907893e-10*tu08
       + 5.8456103354109943e-13*tu09
       + 3.7717268411948233e-13*tu10
       - 2.6564037404227836e-15*tu11
       - 5.7368628737502723e-16*tu12;
     HY5(0,0,1,1,1) =
       - 4.2151303147672207e-04
       + 2.4230392899354007e-03*tu01
       - 5.6276481104680303e-04*tu02
       + 8.2640657870678230e-04*tu03
       - 1.4169972575483287e-04*tu04
       + 1.1241768997510332e-05*tu05
       - 4.4757876435236780e-07*tu06
       + 4.0464701571442372e-09*tu07
       + 3.6693605986548572e-10*tu08
       - 8.1486736073711877e-12*tu09
       - 4.8362219356601919e-13*tu10
       + 1.5732397614617162e-14*tu11
       + 7.1637443194486341e-16*tu12
       - 2.9682648694764162e-17*tu13;
     HY5(0,1,0,1,1) =
       - 5.4016355841362305e-04
       + 3.5885207401063810e-03*tu01
       - 7.2088270891443272e-04*tu02
       + 1.2165742608270584e-03*tu03
       - 1.8111750748505087e-04*tu04
       + 1.2242347596998815e-05*tu05
       - 3.9805632127123734e-07*tu06
       + 1.3818410996670467e-09*tu07
       + 3.0027181656102247e-10*tu08
       - 2.5190497445473117e-12*tu09
       - 3.9056998701282666e-13*tu10
       + 4.6313279849969705e-15*tu11
       + 5.8249180278623573e-16*tu12;
     HY5(0,1,1,1,1) =
       + 3.6243571484950436e-04
       - 1.3106363932291666e-04*tu01
       + 4.8407754872309633e-04*tu02
       - 6.5531819661458333e-05*tu03
       + 1.2213913602645317e-04*tu04
       - 1.3106363932291666e-05*tu05
       + 4.9683501491940088e-07*tu06
       - 4.6646796570171982e-10*tu08
       + 6.6892469436720110e-13*tu10
       - 1.0496975350928139e-15*tu12;
    }
    // nw > 4 endif
  }
  // (n1,n2) = (0,1) or (-1,1) endif

  //**********
  // (n1,n2) = (-1,0) or (-1,1)
  if (    ( (n1 == -1) && (n2 == 0) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,-1) =
       + 3.781250000000000e-02
       + 5.534574473824441e-01*tv01
       + 3.781250000000000e-02*tv02
       + 1.151036617760703e-03*tv03
       - 8.659502433858922e-07*tv05
       + 1.109042494804544e-09*tv07
       - 1.624415058184216e-12*tv09
       + 2.528376460336939e-15*tv11;
    if ( nw > 2 ){
      HY3(0,0,-1) =
       + 5.701592410758114e-02
       + 5.598247957892565e-01*tv01
       + 5.711486614505007e-02*tv02
       + 3.275603992203700e-03*tv03
       + 9.887255877938583e-05*tv04
       + 4.021153684652295e-07*tv05
       - 6.939288687864526e-08*tv06
       - 7.995347631322020e-10*tv07
       + 8.567978673919505e-11*tv08
       + 1.526387027481200e-12*tv09
       - 1.226899454816980e-13*tv10
       - 2.848614761014972e-15*tv11
       + 1.880542777479446e-16*tv12;
     HY3(0,-1,-1) =
       + 3.816894981500984e-02
       + 1.039843750000000e-02*tv01
       + 3.828760080995617e-02*tv02
       + 3.466145833333333e-03*tv03
       + 1.185518160084905e-04*tv04
       - 9.904555648775859e-08*tv06
       + 1.331803984518588e-10*tv08
       - 2.006389465106708e-13*tv10
       + 3.180731062055677e-16*tv12;
    }

    if ( nw > 3 ){
      HY4(0,0,0,-1) =
       + 6.685228257646101e-02
       + 5.645990701998083e-01*tv01
       + 6.707912936340146e-02*tv02
       + 4.876429488624746e-03*tv03
       + 2.268732672568699e-04*tv04
       + 6.038494106229146e-06*tv05
       + 2.642577015932576e-08*tv06
       - 3.679843316593900e-09*tv07
       - 5.444046563879984e-11*tv08
       + 4.063821221202881e-12*tv09
       + 1.055985864474070e-13*tv10
       - 5.190408125225683e-15*tv11
       - 1.985464489219049e-16*tv12;
     HY4(0,0,-1,-1) =
       + 1.953236111099851e-02
       + 8.741612828671381e-03*tv01
       + 1.974116110893196e-02*tv02
       + 2.926558492394004e-03*tv03
       + 2.088576190269387e-04*tv04
       + 7.604351107741397e-06*tv05
       + 5.751031394942524e-08*tv06
       - 5.832253077603139e-09*tv07
       - 1.105713721511985e-10*tv08
       + 7.453416210082473e-12*tv09
       + 2.077758906032370e-13*tv10
       - 1.085601519719514e-14*tv11
       - 3.848312092795918e-16*tv12;
     HY4(0,-1,-1,-1) =
       + 7.148925781250000e-04
       + 7.019393481825299e-03*tv01
       + 9.531901041666666e-04*tv02
       + 2.354287493676137e-03*tv03
       + 2.382975260416666e-04*tv04
       + 8.682904829408987e-06*tv05
       - 7.768198634676578e-09*tv07
       + 1.083130072188330e-11*tv09
       - 1.668810490326842e-14*tv11;
    }
    // nw > 3 endif

    if ( nw > 4 ){
      HY5(0,0,0,0,-1) =
       + 7.1883935399674661e-02
       + 5.6753782109711975e-01*tv01
       + 7.2212923207857999e-02*tv02
       + 5.8670869471466117e-03*tv03
       + 3.2928069579812269e-04*tv04
       + 1.2689437803900269e-05*tv05
       + 2.9273255639591246e-07*tv06
       + 1.0606320330117018e-09*tv07
       - 1.5490385851360920e-10*tv08
       - 2.2474559413025843e-12*tv09
       + 1.5435486840448295e-13*tv10
       + 4.3623305832897835e-15*tv11
       - 1.7529593826254750e-16*tv12;
     HY5(0,0,0,-1,-1) =
       + 1.0000521958818753e-02
       + 5.5972378484058781e-03*tv01
       + 1.0183616888857122e-02*tv02
       + 1.8839550865568384e-03*tv03
       + 1.8347215924120138e-04*tv04
       + 1.0930879320715947e-05*tv05
       + 3.7698877255509719e-07*tv06
       + 3.8459944472218428e-09*tv07
       - 2.4017837972601217e-10*tv08
       - 7.0263208823587761e-12*tv09
       + 2.5160915023993803e-13*tv10
       + 1.2783871754086183e-14*tv11
       - 2.8797679566416130e-16*tv12
       - 2.3134706555649888e-17*tv13;
     HY5(0,0,-1,0,-1) =
       + 1.9758848802070053e-02
       + 9.9630794104335436e-03*tv01
       + 2.0043658059117399e-02*tv02
       + 3.3447469330099638e-03*tv03
       + 2.8517465661196517e-04*tv04
       + 1.4231602601165430e-05*tv05
       + 3.6511844421403422e-07*tv06
       - 4.8298298252332493e-10*tv07
       - 2.8074265749907893e-10*tv08
       - 5.8456103354109943e-13*tv09
       + 3.7717268411948233e-13*tv10
       + 2.6564037404227836e-15*tv11
       - 5.7368628737502723e-16*tv12;
     HY5(0,0,-1,-1,-1) =
       + 4.2151303147672207e-04
       + 2.4230392899354007e-03*tv01
       + 5.6276481104680303e-04*tv02
       + 8.2640657870678230e-04*tv03
       + 1.4169972575483287e-04*tv04
       + 1.1241768997510332e-05*tv05
       + 4.4757876435236780e-07*tv06
       + 4.0464701571442372e-09*tv07
       - 3.6693605986548572e-10*tv08
       - 8.1486736073711877e-12*tv09
       + 4.8362219356601919e-13*tv10
       + 1.5732397614617162e-14*tv11
       - 7.1637443194486341e-16*tv12
       - 2.9682648694764162e-17*tv13;
     HY5(0,-1,0,-1,-1) =
       + 5.4016355841362305e-04
       + 3.5885207401063810e-03*tv01
       + 7.2088270891443272e-04*tv02
       + 1.2165742608270584e-03*tv03
       + 1.8111750748505087e-04*tv04
       + 1.2242347596998815e-05*tv05
       + 3.9805632127123734e-07*tv06
       + 1.3818410996670467e-09*tv07
       - 3.0027181656102247e-10*tv08
       - 2.5190497445473117e-12*tv09
       + 3.9056998701282666e-13*tv10
       + 4.6313279849969705e-15*tv11
       - 5.8249180278623573e-16*tv12;
     HY5(0,-1,-1,-1,-1) =
       + 3.6243571484950436e-04
       + 1.3106363932291666e-04*tv01
       + 4.8407754872309633e-04*tv02
       + 6.5531819661458333e-05*tv03
       + 1.2213913602645317e-04*tv04
       + 1.3106363932291666e-05*tv05
       + 4.9683501491940088e-07*tv06
       - 4.6646796570171982e-10*tv08
       + 6.6892469436720110e-13*tv10
       - 1.0496975350928139e-15*tv12;
    }
    // nw > 4 endif
  }
  // (n1,n2) = (-1,0) or (-1,1) endif

  // (n1,n2) = (-1,1) -- completion
  if ( (n1 == -1) && (n2 == 1) ){
    HY2(-1,1) =
       - 2.924454241163343e-02
       + 3.845279287117326e-01*tu01
       - 2.925485694830038e-02*tu02
       + 1.097780471057338e-03*tu03
       - 1.029703135442673e-05*tu04
       - 7.265175511511970e-07*tu05
       + 1.747461299829753e-08*tu06
       + 7.707353556013722e-10*tu07
       - 3.064611747990741e-11*tu08
       - 8.531228176305706e-13*tu09
       + 5.331187822989144e-14*tu10
       + 8.500141365188675e-16*tu11
       - 6.931471805599453e-01*HY1(-1);
    if ( nw > 2 ){
      HY3(0,-1,1) =
       - 4.107537580582269e-02
       + 3.887609555197323e-01*tu01
       - 4.116162793629221e-02*tu02
       + 2.511526558054413e-03*tu03
       - 8.620496933228561e-05*tu04
       + 9.128023201466990e-07*tu05
       + 4.711634663963971e-08*tu06
       - 1.347359673414334e-09*tu07
       - 4.474345520888852e-11*tu08
       + 2.138249646727980e-12*tu09
       + 4.709915818801180e-14*tu10
       - 3.454431385666621e-15*tu11
       - 6.931471805599453e-01*HY2(0,-1);
     HY3(0,1,-1) =
       - 4.107537580582269e-02
       - 3.887609555197323e-01*tv01
       - 4.116162793629221e-02*tv02
       - 2.511526558054413e-03*tv03
       - 8.620496933228561e-05*tv04
       - 9.128023201466990e-07*tv05
       + 4.711634663963971e-08*tv06
       + 1.347359673414334e-09*tv07
       - 4.474345520888852e-11*tv08
       - 2.138249646727980e-12*tv09
       + 4.709915818801180e-14*tv10
       + 3.454431385666621e-15*tv11
       + 6.931471805599453e-01*HY2(0,1);
     HY3(-1,-1,1) =
       - 3.590863871372201e-02
       + 3.272029419300922e-01*tu01
       - 3.599657175069328e-02*tu02
       + 2.325685169395631e-03*tu03
       - 8.788997314012583e-05*tu04
       + 1.277831858501559e-06*tu05
       + 4.303730428865162e-08*tu06
       - 1.992295216809703e-09*tu07
       - 2.652932076676834e-11*tu08
       + 3.159865930142703e-12*tu09
       - 2.395589527593406e-15*tu10
       - 4.870947810519399e-15*tu11
       - 5.822405264650125e-01*HY1(-1)
       - 3.465735902799726e-01*HY1(-1)*HY1(-1);
     HY3(-1,1,1) =
       + 3.668493142404161e-02
       - 1.413123104773291e-01*tu01
       + 3.680167312678666e-02*tu02
       - 3.064044728536094e-03*tu03
       + 1.166524199994130e-04*tu04
       - 8.779983417383380e-07*tu05
       - 8.917940330502000e-08*tu06
       + 1.787575622706040e-09*tu07
       + 1.032182649980912e-10*tu08
       - 3.441821872732193e-12*tu09
       - 1.239218730863368e-13*tu10
       + 6.355731482672869e-15*tu11
       + 1.386175839607904e-16*tu12
       + 2.402265069591007e-01*HY1(-1);
    }

    if ( nw > 3 ){
      HY4(0,0,-1,1) =
       - 4.713463351559199e-02
       + 3.918037828258655e-01*tu01
       - 4.730698763577787e-02*tu02
       + 3.532784273601097e-03*tu03
       - 1.724036773635937e-04*tu04
       + 5.100573466380115e-06*tu05
       - 4.948996960052575e-08*tu06
       - 2.345390965359666e-09*tu07
       + 6.710522628543514e-11*tu08
       + 1.979867116023822e-12*tu09
       - 1.027163441987459e-13*tu10
       - 1.836436639605094e-15*tu11
       + 1.633620651699784e-16*tu12
       - 6.931471805599453e-01*HY3(0,0,-1);
     HY4(0,0,1,-1) =
       - 4.713463351559199e-02
       - 3.918037828258655e-01*tv01
       - 4.730698763577787e-02*tv02
       - 3.532784273601097e-03*tv03
       - 1.724036773635937e-04*tv04
       - 5.100573466380115e-06*tv05
       - 4.948996960052575e-08*tv06
       + 2.345390965359666e-09*tv07
       + 6.710522628543514e-11*tv08
       - 1.979867116023822e-12*tv09
       - 1.027163441987459e-13*tv10
       + 1.836436639605094e-15*tv11
       + 1.633620651699784e-16*tv12
       + 6.931471805599453e-01*HY3(0,0,1);
     HY4(0,-1,0,1) =
       - 5.610575179941452e-02
       + 4.649892609082033e-01*tu01
       - 5.631239161843284e-02*tu02
       + 4.220972769653239e-03*tu03
       - 2.066940413626322e-04*tu04
       + 6.100628682175971e-06*tu05
       - 5.412969106099992e-08*tu06
       - 3.230915912784154e-09*tu07
       + 9.249866333323043e-11*tu08
       + 2.685990764581699e-12*tu09
       - 1.543312114608473e-13*tu10
       - 2.036971731594398e-15*tu11
       + 2.517450307574790e-16*tu12
       - 8.224670334241132e-01*HY2(0,-1);
     HY4(0,-1,-1,1) =
       - 4.031271939759038e-02
       + 3.295217254379970e-01*tu01
       - 4.047097737450547e-02*tu02
       + 3.104955391145708e-03*tu03
       - 1.583251510732719e-04*tu04
       + 5.083334568184305e-06*tu05
       - 6.708598619683341e-08*tu06
       - 1.944278941559733e-09*tu07
       + 8.804863765356287e-11*tu08
       + 9.341312729419985e-13*tu09
       - 1.231746977889946e-13*tu10
       + 3.370647349658755e-16*tu11
       + 1.718647072955689e-16*tu12
       - 5.822405264650125e-01*HY2(0,-1)
       - 6.931471805599453e-01*HY3(0,-1,-1);
     HY4(0,-1,1,-1) =
       - 4.495764739674318e-02
       - 2.758514579198452e-01*tv01
       - 4.515130668959398e-02*tv02
       - 3.875995092451054e-03*tv03
       - 1.936768370518385e-04*tv04
       - 5.133195476137788e-06*tv05
       - 1.752786900562004e-08*tv06
       + 2.715518363893619e-09*tv07
       + 1.631155670579918e-11*tv08
       - 2.940721244025822e-12*tv09
       - 2.045219059123054e-14*tv10
       + 3.895696592051861e-15*tv11
       + 4.804530139182014e-01*HY2(0,-1)
       + 6.931471805599453e-01*HY3(0,-1,1);
     HY4(0,1,-1,-1) =
       - 2.782664607935622e-02
       - 1.410831481728889e-01*tv01
       - 2.801876266982354e-02*tv02
       - 2.997894208020603e-03*tv03
       - 1.921960113936824e-04*tv04
       - 7.016503666427137e-06*tv05
       - 7.928257765061337e-08*tv06
       + 4.388745575295455e-09*tv07
       + 1.381107719492586e-10*tv08
       - 4.341921500497716e-12*tv09
       - 2.375364913875066e-13*tv10
       + 4.522044546598701e-15*tv11
       + 4.033357472727688e-16*tv12
       + 2.402265069591007e-01*HY2(0,1);
     HY4(0,-1,1,1) =
       + 2.782664607935622e-02
       - 1.410831481728889e-01*tu01
       + 2.801876266982354e-02*tu02
       - 2.997894208020603e-03*tu03
       + 1.921960113936824e-04*tu04
       - 7.016503666427137e-06*tu05
       + 7.928257765061337e-08*tu06
       + 4.388745575295455e-09*tu07
       - 1.381107719492586e-10*tu08
       - 4.341921500497716e-12*tu09
       + 2.375364913875066e-13*tu10
       + 4.522044546598701e-15*tu11
       - 4.033357472727688e-16*tu12
       + 2.402265069591007e-01*HY2(0,-1);
     HY4(0,1,-1,1) =
       + 4.495764739674318e-02
       - 2.758514579198452e-01*tu01
       + 4.515130668959398e-02*tu02
       - 3.875995092451054e-03*tu03
       + 1.936768370518385e-04*tu04
       - 5.133195476137788e-06*tu05
       + 1.752786900562004e-08*tu06
       + 2.715518363893619e-09*tu07
       - 1.631155670579918e-11*tu08
       - 2.940721244025822e-12*tu09
       + 2.045219059123054e-14*tu10
       + 3.895696592051861e-15*tu11
       + 4.804530139182014e-01*HY2(0,1)
       - 6.931471805599453e-01*HY3(0,1,-1);
     HY4(0,1,1,-1) =
       + 4.031271939759038e-02
       + 3.295217254379970e-01*tv01
       + 4.047097737450547e-02*tv02
       + 3.104955391145708e-03*tv03
       + 1.583251510732719e-04*tv04
       + 5.083334568184305e-06*tv05
       + 6.708598619683341e-08*tv06
       - 1.944278941559733e-09*tv07
       - 8.804863765356287e-11*tv08
       + 9.341312729419985e-13*tv09
       + 1.231746977889946e-13*tv10
       + 3.370647349658755e-16*tv11
       - 1.718647072955689e-16*tv12
       - 5.822405264650125e-01*HY2(0,1)
       + 6.931471805599453e-01*HY3(0,1,1);
     HY4(-1,-1,-1,1) =
       - 3.768651335815766e-02
       + 3.043162147119780e-01*tu01
       - 3.784162844891144e-02*tu02
       + 2.958351024362477e-03*tu03
       - 1.551924666783514e-04*tu04
       + 5.216293832777793e-06*tu05
       - 7.726843592398867e-08*tu06
       - 1.910379383726989e-09*tu07
       + 1.073377838077624e-10*tu08
       + 4.147979000313175e-13*tu09
       - 1.506593045440627e-13*tu10
       + 1.921276747438603e-15*tu11
       + 1.977332880766160e-16*tu12
       - 5.372131936080402e-01*HY1(-1)
       - 2.911202632325062e-01*HY1(-1)*HY1(-1)
       - 1.155245300933242e-01*HY1(-1)*HY1(-1)*HY1(-1);
     HY4(-1,-1,1,1) =
       + 2.908893189635991e-02
       - 1.784837106345115e-01*tu01
       + 2.927117884632272e-02*tu02
       - 2.888221776586007e-03*tu03
       + 1.823501630828519e-04*tu04
       - 6.976883920991888e-06*tu05
       + 1.030302948541690e-07*tu06
       + 3.794029548474434e-09*tu07
       - 1.825184393299693e-10*tu08
       - 2.300206200729610e-12*tu09
       + 3.062629564489397e-13*tu10
       - 7.629393984387632e-16*tu11
       - 4.860728618463296e-16*tu12
       + 3.088253750968339e-01*HY1(-1)
       + 1.201132534795503e-01*HY1(-1)*HY1(-1);
     HY4(-1,1,1,1) =
       - 9.029205146496301e-03
       + 3.753824045412342e-02*tu01
       - 9.240717745810759e-03*tu02
       + 2.351153976182453e-03*tu03
       - 2.115782190216214e-04*tu04
       + 8.486524807740892e-06*tu05
       - 6.547885807612483e-08*tu06
       - 6.934422754020238e-09*tu07
       + 1.405695202725693e-10*tu08
       + 8.329441237576153e-12*tu09
       - 2.790404594803712e-13*tu10
       - 1.024489568815216e-14*tu11
       + 5.256388245544115e-16*tu12
       - 5.550410866482157e-02*HY1(-1);
    }
    // nw > 3 endif

    if ( nw > 4 ){
      HY5(-1,-1,-1,-1,1) =
       - 3.8228565672333040e-02
       + 2.9434499414685087e-01*tu01
       - 3.8424518843646597e-02*tu02
       + 3.2580449034204883e-03*tu03
       - 1.9620389859663782e-04*tu04
       + 8.5297225882767261e-06*tu05
       - 2.5065346065715455e-07*tu06
       + 3.4415061242343063e-09*tu07
       + 7.3821799422249131e-11*tu08
       - 4.2538624555519857e-12*tu09
       - 7.2315211312081768e-16*tu10
       + 5.3108417435543907e-15*tu11
       - 9.9323734178161058e-17*tu12
       - 5.1747906167389938e-01*HY1(-1)
       - 2.6860659680402010e-01*HY1(-1)*HY1(-1)
       - 9.7040087744168750e-02*HY1(-1)*HY1(-1)*HY1(-1)
       - 2.8881132523331054e-02*HY1(-1)*HY1(-1)*HY1(-1)*HY1(-1);
     HY5(-1,-1,-1,1,1) =
       + 2.7357462427685970e-02
       - 1.9031941959865697e-01*tu01
       + 2.7543492667729091e-02*tu02
       - 2.6605966861706822e-03*tu03
       + 1.8636146557007899e-04*tu04
       - 9.5345987092093788e-06*tu05
       + 3.3110554578258299e-07*tu06
       - 5.4595158175118823e-09*tu07
       - 1.1999359443095388e-10*tu08
       + 8.2902112001115834e-12*tu09
       - 1.2181518159922712e-14*tu10
       - 1.1713353633997384e-14*tu11
       + 2.3651675075246772e-16*tu12
       + 3.3160957134970784e-01*HY1(-1)
       + 1.5441268754841696e-01*HY1(-1)*HY1(-1)
       + 4.0037751159850118e-02*HY1(-1)*HY1(-1)*HY1(-1);
     HY5(-1,-1,1,-1,1) =
       + 4.1458814971381822e-02
       - 3.0303763301003844e-01*tu01
       + 4.1691982869997716e-02*tu02
       - 3.7240373018258494e-03*tu03
       + 2.3344990525159924e-04*tu04
       - 1.0247007230046718e-05*tu05
       + 2.8185771897077629e-07*tu06
       - 2.2751673303889503e-09*tu07
       - 1.4878969225475077e-10*tu08
       + 4.1341440052910325e-12*tu09
       + 1.2696091792274665e-13*tu10
       - 7.5007742483794021e-15*tu11
       - 8.1903610410494478e-17*tu12
       + 5.3075770941318154e-01*HY1(-1)
       + 2.6126533022459244e-01*HY1(-1)*HY1(-1)
       - 6.9314718055994530e-01*HY1(-1)*HY3(-1,-1,1)
       + 4.8045301391820142e-01*HY3(-1,-1,1)
       + 2.0794415416798359e+00*HY4(-1,-1,-1,1);
     HY5(-1,-1,1,1,1) =
       - 9.5924489184207016e-03
       + 5.2772883655818822e-02*tu01
       - 9.7366715772116844e-03*tu02
       + 1.4142029020952310e-03*tu03
       - 1.4463004412432978e-04*tu04
       + 9.8218990989160592e-06*tu05
       - 4.0715654417888680e-07*tu06
       + 6.7544293368802512e-09*tu07
       + 2.2866755156107150e-10*tu08
       - 1.2497892086833029e-11*tu09
       - 1.2173408174458276e-13*tu10
       + 2.1387606509664189e-14*tu11
       - 1.1689492941664195e-16*tu12
       - 3.4168851038812753e-17*tu13
       - 8.8326067366010207e-02*HY1(-1)
       - 2.7752054332410789e-02*HY1(-1)*HY1(-1);
     HY5(-1,1,-1,1,1) =
       - 1.8886299866599669e-02
       + 1.1916393884386234e-01*tu01
       - 1.9076154105183607e-02*tu02
       + 2.2711434786163337e-03*tu03
       - 1.9021198135197550e-04*tu04
       + 1.0646966480063299e-05*tu05
       - 3.5753730456224019e-07*tu06
       + 3.8528188610744423e-09*tu07
       + 2.0528377803607047e-10*tu08
       - 6.6747997821119625e-12*tu09
       - 1.7956391666197610e-13*tu10
       + 1.1491009542808092e-14*tu11
       + 1.3285418003675663e-16*tu12
       - 2.0437039310996688e-01*HY1(-1)
       + 2.4022650695910071e-01*HY1(-1)*HY2(-1,1)
       - 1.6651232599446473e-01*HY2(-1,1)
       - 4.8045301391820142e-01*HY3(-1,-1,1);
     HY5(-1,1,1,1,1) =
       + 1.8171632147206520e-03
       - 6.6063186750176729e-03*tu01
       + 1.9387809591623771e-03*tu02
       - 4.5816039839889645e-04*tu03
       + 1.2210356950937828e-04*tu04
       - 1.1632122874703951e-05*tu05
       + 4.8540847374707648e-07*tu06
       - 3.8582255619059790e-09*tu07
       - 4.1607939221717784e-10*tu08
       + 8.5808819391347779e-12*tu09
       + 5.1386964924538773e-13*tu10
       - 1.7412399897832375e-14*tu11
       - 6.4350879750488940e-16*tu12
       + 3.3295304169373632e-17*tu13
       + 9.6181291076284771e-03*HY1(-1);
     HY5(0,-1,-1,-1,1) =
       - 3.9520972886442092e-02
       + 3.0546490933012253e-01*tu01
       - 3.9720322777238976e-02*tu02
       + 3.3467933739052856e-03*tu03
       - 1.9959549584313573e-04*tu04
       + 8.5499586955813381e-06*tu05
       - 2.4553310777499893e-07*tu06
       + 3.2119489955423060e-09*tu07
       + 7.1927096749843198e-11*tu08
       - 3.7520798598557195e-12*tu09
       - 1.1440674588088539e-14*tu10
       + 4.6108325614199602e-15*tu11
       - 6.0832641844878483e-17*tu12
       - 5.3721319360804020e-01*HY2(0,-1)
       - 5.8224052646501250e-01*HY3(0,-1,-1)
       - 6.9314718055994530e-01*HY4(0,-1,-1,-1);
     HY5(0,-1,-1,0,1) =
       - 5.4931882964030792e-02
       + 4.2696670756984732e-01*tu01
       - 5.5201538838609055e-02*tu02
       + 4.6052217228062647e-03*tu03
       - 2.6995693356946050e-04*tu04
       + 1.1207715314455869e-05*tu05
       - 3.0093286122242289e-07*tu06
       + 2.9252018980885367e-09*tu07
       + 1.2606407378756556e-10*tu08
       - 4.4893551397064275e-12*tu09
       - 6.5916974412553446e-14*tu10
       + 6.6066633977237873e-15*tu11
       - 7.5128556447474642e-01*HY2(0,-1)
       - 8.2246703342411321e-01*HY3(0,-1,-1);
     HY5(0,-1,-1,1,-1) =
       - 3.4235225044469286e-02
       - 2.3328399380319120e-01*tv01
       - 3.4504895043303540e-02*tv02
       - 3.7912859711035303e-03*tv03
       - 2.6991423023257518e-04*tv04
       - 1.1593278610997365e-05*tv05
       - 2.4410984754189600e-07*tv06
       + 9.0404989403384568e-10*tv07
       + 1.2141001239198240e-10*tv08
       - 2.0560625998471416e-12*tv09
       - 1.4056423603087806e-13*tv10
       + 3.5816535397430763e-15*tv11
       + 2.0254744342336250e-16*tv12
       + 4.0357837932696163e-01*HY2(0,-1)
       + 4.8045301391820142e-01*HY3(0,-1,-1)
       + 6.9314718055994530e-01*HY4(0,-1,-1,1);
     HY5(0,-1,-1,1,1) =
       + 2.6517569052959506e-02
       - 1.7779971519631702e-01*tu01
       + 2.6707704581331518e-02*tu02
       - 2.6648397927870009e-03*tu03
       + 1.9046558373551644e-04*tu04
       - 9.7589088614312887e-06*tu05
       + 3.2991992381966999e-07*tu06
       - 4.8561819501772588e-09*tu07
       - 1.3539320891044926e-10*tu08
       + 7.2902837287752652e-12*tu09
       + 4.6565266727231378e-14*tu10
       - 1.0737158384822919e-14*tu11
       + 8.8429222559013066e-17*tu12
       + 3.0882537509683393e-01*HY2(0,-1)
       + 2.4022650695910071e-01*HY3(0,-1,-1);
     HY5(0,-1,0,-1,1) =
       - 4.6155088778537896e-02
       + 3.5912469692896398e-01*tu01
       - 4.6380859407450647e-02*tu02
       + 3.8633681101991486e-03*tu03
       - 2.2602267773980855e-04*tu04
       + 9.3668504249552797e-06*tu05
       - 2.5195369443104781e-07*tu06
       + 2.5727032623578792e-09*tu07
       + 9.5079191917240018e-11*tu08
       - 3.3913895763562877e-12*tu09
       - 5.3430708391974222e-14*tu10
       + 4.8668530674676388e-15*tu11
       - 6.3196619783816790e-01*HY2(0,-1)
       - 3.4657359027997265e-01*HY2(0,-1)*HY2(0,-1)
       + 1.3862943611198906e+00*HY4(0,0,-1,-1);
     HY5(0,-1,0,1,-1) =
       - 4.8531326139900090e-02
       - 3.2657418615138227e-01*tv01
       - 4.8786752720619143e-02*tv02
       - 4.3579589418437103e-03*tv03
       - 2.5565369900267449e-04*tv04
       - 9.9174468231600028e-06*tv05
       - 2.2703683570409072e-07*tv06
       - 1.2319581804863699e-09*tv07
       + 8.1382125029078829e-11*tv08
       + 1.0513084104970317e-12*tv09
       - 6.5723688498545463e-14*tv10
       - 1.2162924878946765e-15*tv11
       + 6.9118041556917233e-17*tv12
       + 5.7009070532142637e-01*HY2(0,-1)
       + 6.9314718055994530e-01*HY4(0,-1,0,1);
     HY5(0,-1,0,1,1) =
       + 1.7588255219497996e-02
       - 8.9173088210648816e-02*tu01
       + 1.7770012282463661e-02*tu02
       - 2.1943047496140125e-03*tu03
       + 1.8211824241696307e-04*tu04
       - 1.0254443539590487e-05*tu05
       + 3.6099159031901396e-07*tu06
       - 4.8590233971583916e-09*tu07
       - 1.8773473287955894e-10*tu08
       + 8.2188353537397648e-12*tu09
       + 1.2622338876212118e-13*tu10
       - 1.3549277713840031e-14*tu11
       - 2.2995013881263894e-17*tu12
       + 2.1790299145411898e-17*tu13
       + 1.5025711289494928e-01*HY2(0,-1);
     HY5(0,-1,1,-1,-1) =
       - 1.5970421220241350e-02
       - 9.8098905332736657e-02*tv01
       - 1.6167874610049324e-02*tv02
       - 2.1909422567422571e-03*tv03
       - 1.9780330842002595e-04*tv04
       - 1.1143616753061323e-05*tv05
       - 3.4970788285258598e-07*tv06
       - 2.4737298345971262e-09*tv07
       + 2.1049905271699688e-10*tv08
       + 3.6829751452188057e-12*tv09
       - 2.2984898297836793e-13*tv10
       - 5.8041435355729247e-15*tv11
       + 2.9753327209204345e-16*tv12
       + 1.6651232599446473e-01*HY2(0,-1)
       + 2.4022650695910071e-01*HY3(0,-1,1);
     HY5(0,-1,1,-1,1) =
       + 4.1824168833514614e-02
       - 2.9878381943835587e-01*tu01
       + 4.2063530444775636e-02*tu02
       - 3.8145573036522436e-03*tu03
       + 2.3963305636044003e-04*tu04
       - 1.0345567145401369e-05*tu05
       + 2.7130517497620301e-07*tu06
       - 1.7273255620176561e-09*tu07
       - 1.3978876407646153e-10*tu08
       + 2.7492226699257445e-12*tu09
       + 1.3553332679630927e-13*tu10
       - 4.7656087734784391e-15*tu11
       - 1.4423054189885051e-16*tu12
       + 5.2253066044918489e-01*HY2(0,-1)
       + 4.8045301391820142e-01*HY3(0,-1,1)
       - 6.9314718055994530e-01*HY4(0,-1,1,-1);
     HY5(0,-1,1,0,1) =
       + 3.1399803193734681e-02
       - 1.5922070722448512e-01*tu01
       + 3.1673651121964784e-02*tu02
       - 3.6733024485531673e-03*tu03
       + 2.7421207386188742e-04*tu04
       - 1.3254697744560554e-05*tu05
       + 3.6389461745542725e-07*tu06
       - 1.3701468350861509e-09*tu07
       - 2.5073096543709732e-10*tu08
       + 3.7881257959182565e-12*tu09
       + 2.8301894299500673e-13*tu10
       - 7.9052198960553283e-15*tu11
       - 3.4475230007347254e-16*tu12
       + 2.6957647953152780e-01*HY2(0,-1);
     HY5(0,-1,1,1,-1) =
       + 4.4239483860061491e-02
       + 3.2493754537326350e-01*tv01
       + 4.4462186515298750e-02*tv02
       + 3.8108642536456408e-03*tv03
       + 2.2293231798666157e-04*tv04
       + 8.9901447113222695e-06*tv05
       + 2.2959225139995976e-07*tv06
       + 2.1985163564934731e-09*tv07
       - 7.0460025669936385e-11*tv08
       - 2.1618428565949139e-12*tv09
       + 3.7961815108691857e-14*tv10
       + 2.5062265861081495e-15*tv11
       - 5.7009070532142637e-01*HY2(0,-1)
       - 5.8224052646501250e-01*HY3(0,-1,1)
       + 6.9314718055994530e-01*HY4(0,-1,1,1);
     HY5(0,-1,1,1,1) =
       - 6.7365547952682237e-03
       + 3.4286529141621258e-02*tu01
       - 6.8840170170275732e-03*tu02
       + 1.2704332689803235e-03*tu03
       - 1.4787767126158972e-04*tu04
       + 1.0413585642621615e-05*tu05
       - 4.1517140759699248e-07*tu06
       + 5.3439659402510695e-09*tu07
       + 2.7781700180675136e-10*tu08
       - 9.9205586909926692e-12*tu09
       - 2.7736473454099143e-13*tu10
       + 1.7683378840938849e-14*tu11
       + 2.7645451246534933e-16*tu12
       - 3.0721858829145982e-17*tu13
       - 5.5504108664821579e-02*HY2(0,-1);
     HY5(0,0,-1,-1,1) =
       - 4.2561833953883235e-02
       + 3.3089514249958932e-01*tu01
       - 4.2771142986440044e-02*tu02
       + 3.5688685742597137e-03*tu03
       - 2.0954973101068707e-04*tu04
       + 8.7544434158133471e-06*tu05
       - 2.4062186086108688e-07*tu06
       + 2.7728194984089187e-09*tu07
       + 7.6559566355403117e-11*tu08
       - 3.1501612342558870e-12*tu09
       - 3.3459877468585252e-14*tu10
       + 4.0333595766267801e-15*tu11
       - 5.8224052646501250e-01*HY3(0,0,-1)
       - 6.9314718055994530e-01*HY4(0,0,-1,-1);
     HY5(0,0,-1,0,1) =
       - 5.9694681535720023e-02
       + 4.6714213068105458e-01*tu01
       - 5.9979199873202721e-02*tu02
       + 4.9475467229010258e-03*tu03
       - 2.8481020227431533e-04*tu04
       + 1.1478749310592714e-05*tu05
       - 2.9173546427111336e-07*tu06
       + 2.2634918139358350e-09*tu07
       + 1.2923277934839262e-10*tu08
       - 3.4600488918561596e-12*tu09
       - 9.4505709251699823e-14*tu10
       + 5.3596484866903464e-15*tu11
       + 6.0838246089431129e-17*tu12
       - 8.2246703342411321e-01*HY3(0,0,-1);
     HY5(0,0,-1,1,-1) =
       - 4.1110148228889138e-02
       - 2.7597446804002515e-01*tv01
       - 4.1362136148261452e-02*tv02
       - 3.9264219532611858e-03*tv03
       - 2.5225247282294274e-04*tv04
       - 1.0792153931365190e-05*tv05
       - 2.6440687189609348e-07*tv06
       - 7.5507087052363252e-10*tv07
       + 1.4640592504212342e-10*tv08
       + 1.0410408318930554e-12*tv09
       - 1.7256282627937244e-13*tv10
       - 2.0115212902641882e-15*tv11
       + 2.4492838656439672e-16*tv12
       + 4.8045301391820142e-01*HY3(0,0,-1)
       + 6.9314718055994530e-01*HY4(0,0,-1,1);
     HY5(0,0,-1,1,1) =
       + 2.3290431799544722e-02
       - 1.3976916667674197e-01*tu01
       + 2.3484837128475192e-02*tu02
       - 2.5652450331604480e-03*tu03
       + 1.9474432423788960e-04*tu04
       - 1.0235257714295329e-05*tu05
       + 3.3882452171323895e-07*tu06
       - 4.1398941829422872e-09*tu07
       - 1.7065390810468420e-10*tu08
       + 6.5500661689981377e-12*tu09
       + 1.3171293231469574e-13*tu10
       - 1.0601060206261924e-14*tu11
       - 8.5654606012582514e-17*tu12
       + 2.4022650695910071e-01*HY3(0,0,-1);
     HY5(0,0,0,-1,1) =
       - 5.0232086741389027e-02
       + 3.9364648125763205e-01*tu01
       - 5.0470343357276722e-02*tu02
       + 4.1544817848152132e-03*tu03
       - 2.3850059599743822e-04*tu04
       + 9.5855250288941914e-06*tu05
       - 2.4388351988986297e-07*tu06
       + 2.0282340296972451e-09*tu07
       + 9.6515154204163078e-11*tu08
       - 2.5201744413354707e-12*tu09
       - 7.4636488424158657e-14*tu10
       + 3.7370382545755637e-15*tu11
       + 6.2133891701574733e-17*tu12
       - 6.9314718055994530e-01*HY4(0,0,0,-1);
     HY5(0,0,0,1,-1) =
       - 5.0232086741389027e-02
       - 3.9364648125763205e-01*tv01
       - 5.0470343357276722e-02*tv02
       - 4.1544817848152132e-03*tv03
       - 2.3850059599743822e-04*tv04
       - 9.5855250288941914e-06*tv05
       - 2.4388351988986297e-07*tv06
       - 2.0282340296972451e-09*tv07
       + 9.6515154204163078e-11*tv08
       + 2.5201744413354707e-12*tv09
       - 7.4636488424158657e-14*tv10
       - 3.7370382545755637e-15*tv11
       + 6.2133891701574733e-17*tv12
       + 6.9314718055994530e-01*HY4(0,0,0,1);
     HY5(0,0,1,-1,-1) =
       - 2.3290431799544722e-02
       - 1.3976916667674197e-01*tv01
       - 2.3484837128475192e-02*tv02
       - 2.5652450331604480e-03*tv03
       - 1.9474432423788960e-04*tv04
       - 1.0235257714295329e-05*tv05
       - 3.3882452171323895e-07*tv06
       - 4.1398941829422872e-09*tv07
       + 1.7065390810468420e-10*tv08
       + 6.5500661689981377e-12*tv09
       - 1.3171293231469574e-13*tv10
       - 1.0601060206261924e-14*tv11
       + 8.5654606012582514e-17*tv12
       + 2.4022650695910071e-01*HY3(0,0,1);
     HY5(0,0,1,-1,1) =
       + 4.1110148228889138e-02
       - 2.7597446804002515e-01*tu01
       + 4.1362136148261452e-02*tu02
       - 3.9264219532611858e-03*tu03
       + 2.5225247282294274e-04*tu04
       - 1.0792153931365190e-05*tu05
       + 2.6440687189609348e-07*tu06
       - 7.5507087052363252e-10*tu07
       - 1.4640592504212342e-10*tu08
       + 1.0410408318930554e-12*tu09
       + 1.7256282627937244e-13*tu10
       - 2.0115212902641882e-15*tu11
       - 2.4492838656439672e-16*tu12
       + 4.8045301391820142e-01*HY3(0,0,1)
       - 6.9314718055994530e-01*HY4(0,0,1,-1);
     HY5(0,0,1,0,-1) =
       - 5.9694681535720023e-02
       - 4.6714213068105458e-01*tv01
       - 5.9979199873202721e-02*tv02
       - 4.9475467229010258e-03*tv03
       - 2.8481020227431533e-04*tv04
       - 1.1478749310592714e-05*tv05
       - 2.9173546427111336e-07*tv06
       - 2.2634918139358350e-09*tv07
       + 1.2923277934839262e-10*tv08
       + 3.4600488918561596e-12*tv09
       - 9.4505709251699823e-14*tv10
       - 5.3596484866903464e-15*tv11
       + 6.0838246089431129e-17*tv12
       + 8.2246703342411321e-01*HY3(0,0,1);
     HY5(0,0,1,1,-1) =
       + 4.2561833953883235e-02
       + 3.3089514249958932e-01*tv01
       + 4.2771142986440044e-02*tv02
       + 3.5688685742597137e-03*tv03
       + 2.0954973101068707e-04*tv04
       + 8.7544434158133471e-06*tv05
       + 2.4062186086108688e-07*tv06
       + 2.7728194984089187e-09*tv07
       - 7.6559566355403117e-11*tv08
       - 3.1501612342558870e-12*tv09
       + 3.3459877468585252e-14*tv10
       + 4.0333595766267801e-15*tv11
       - 5.8224052646501250e-01*HY3(0,0,1)
       + 6.9314718055994530e-01*HY4(0,0,1,1);
     HY5(0,1,-1,-1,-1) =
       - 6.7365547952682237e-03
       - 3.4286529141621258e-02*tv01
       - 6.8840170170275732e-03*tv02
       - 1.2704332689803235e-03*tv03
       - 1.4787767126158972e-04*tv04
       - 1.0413585642621615e-05*tv05
       - 4.1517140759699248e-07*tv06
       - 5.3439659402510695e-09*tv07
       + 2.7781700180675136e-10*tv08
       + 9.9205586909926692e-12*tv09
       - 2.7736473454099143e-13*tv10
       - 1.7683378840938849e-14*tv11
       + 2.7645451246534933e-16*tv12
       + 3.0721858829145982e-17*tv13
       + 5.5504108664821579e-02*HY2(0,1);
     HY5(0,1,-1,-1,1) =
       + 4.4239483860061491e-02
       - 3.2493754537326350e-01*tu01
       + 4.4462186515298750e-02*tu02
       - 3.8108642536456408e-03*tu03
       + 2.2293231798666157e-04*tu04
       - 8.9901447113222695e-06*tu05
       + 2.2959225139995976e-07*tu06
       - 2.1985163564934731e-09*tu07
       - 7.0460025669936385e-11*tu08
       + 2.1618428565949139e-12*tu09
       + 3.7961815108691857e-14*tu10
       - 2.5062265861081495e-15*tu11
       + 5.7009070532142637e-01*HY2(0,1)
       - 5.8224052646501250e-01*HY3(0,1,-1)
       - 6.9314718055994530e-01*HY4(0,1,-1,-1);
     HY5(0,1,-1,1,-1) =
       + 4.1824168833514614e-02
       + 2.9878381943835587e-01*tv01
       + 4.2063530444775636e-02*tv02
       + 3.8145573036522436e-03*tv03
       + 2.3963305636044003e-04*tv04
       + 1.0345567145401369e-05*tv05
       + 2.7130517497620301e-07*tv06
       + 1.7273255620176561e-09*tv07
       - 1.3978876407646153e-10*tv08
       - 2.7492226699257445e-12*tv09
       + 1.3553332679630927e-13*tv10
       + 4.7656087734784391e-15*tv11
       - 1.4423054189885051e-16*tv12
       - 5.2253066044918489e-01*HY2(0,1)
       + 4.8045301391820142e-01*HY3(0,1,-1)
       + 6.9314718055994530e-01*HY4(0,1,-1,1);
     HY5(0,1,-1,1,1) =
       - 1.5970421220241350e-02
       + 9.8098905332736657e-02*tu01
       - 1.6167874610049324e-02*tu02
       + 2.1909422567422571e-03*tu03
       - 1.9780330842002595e-04*tu04
       + 1.1143616753061323e-05*tu05
       - 3.4970788285258598e-07*tu06
       + 2.4737298345971262e-09*tu07
       + 2.1049905271699688e-10*tu08
       - 3.6829751452188057e-12*tu09
       - 2.2984898297836793e-13*tu10
       + 5.8041435355729247e-15*tu11
       + 2.9753327209204345e-16*tu12
       - 1.6651232599446473e-01*HY2(0,1)
       + 2.4022650695910071e-01*HY3(0,1,-1);
     HY5(0,1,0,1,-1) =
       + 4.6155088778537896e-02
       + 3.5912469692896398e-01*tv01
       + 4.6380859407450647e-02*tv02
       + 3.8633681101991486e-03*tv03
       + 2.2602267773980855e-04*tv04
       + 9.3668504249552797e-06*tv05
       + 2.5195369443104781e-07*tv06
       + 2.5727032623578792e-09*tv07
       - 9.5079191917240018e-11*tv08
       - 3.3913895763562877e-12*tv09
       + 5.3430708391974222e-14*tv10
       + 4.8668530674676388e-15*tv11
       - 6.3196619783816790e-01*HY2(0,1)
       + 3.4657359027997265e-01*HY2(0,1)*HY2(0,1)
       - 1.3862943611198906e+00*HY4(0,0,1,1);
     HY5(0,1,1,-1,-1) =
       + 2.6517569052959506e-02
       + 1.7779971519631702e-01*tv01
       + 2.6707704581331518e-02*tv02
       + 2.6648397927870009e-03*tv03
       + 1.9046558373551644e-04*tv04
       + 9.7589088614312887e-06*tv05
       + 3.2991992381966999e-07*tv06
       + 4.8561819501772588e-09*tv07
       - 1.3539320891044926e-10*tv08
       - 7.2902837287752652e-12*tv09
       + 4.6565266727231378e-14*tv10
       + 1.0737158384822919e-14*tv11
       + 8.8429222559013066e-17*tv12
       - 3.0882537509683393e-01*HY2(0,1)
       + 2.4022650695910071e-01*HY3(0,1,1);
     HY5(0,1,1,-1,1) =
       - 3.4235225044469286e-02
       + 2.3328399380319120e-01*tu01
       - 3.4504895043303540e-02*tu02
       + 3.7912859711035303e-03*tu03
       - 2.6991423023257518e-04*tu04
       + 1.1593278610997365e-05*tu05
       - 2.4410984754189600e-07*tu06
       - 9.0404989403384568e-10*tu07
       + 1.2141001239198240e-10*tu08
       + 2.0560625998471416e-12*tu09
       - 1.4056423603087806e-13*tu10
       - 3.5816535397430763e-15*tu11
       + 2.0254744342336250e-16*tu12
       - 4.0357837932696163e-01*HY2(0,1)
       + 4.8045301391820142e-01*HY3(0,1,1)
       - 6.9314718055994530e-01*HY4(0,1,1,-1);
     HY5(0,1,1,1,-1) =
       - 3.9520972886442092e-02
       - 3.0546490933012253e-01*tv01
       - 3.9720322777238976e-02*tv02
       - 3.3467933739052856e-03*tv03
       - 1.9959549584313573e-04*tv04
       - 8.5499586955813381e-06*tv05
       - 2.4553310777499893e-07*tv06
       - 3.2119489955423060e-09*tv07
       + 7.1927096749843198e-11*tv08
       + 3.7520798598557195e-12*tv09
       - 1.1440674588088539e-14*tv10
       - 4.6108325614199602e-15*tv11
       - 6.0832641844878483e-17*tv12
       + 5.3721319360804020e-01*HY2(0,1)
       - 5.8224052646501250e-01*HY3(0,1,1)
       + 6.9314718055994530e-01*HY4(0,1,1,1);
    }
    // nw > 4 endif
  }
  // (n1,n2) = (-1,1) -- completion endif

 }

 void hplog5::pfillirr1dhplat1(double r, int nw, HArr<1>& HR1, HArr<2>& HR2, HArr<3>& HR3, HArr<4>& HR4, HArr<5>& HR5,
                                                 HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                 HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates the HPL for r2m1 < y < r2p1
  // fillirr1dhplat1 is called by eval1dhplat1 after calling
  // fillirr1dhplat0 with argument r=(1-y)/(1+y)
  // it is guaranteed that nw is in the range 2:4, and that (n1,n2)
  // take one of the pairs of values (0,1), (-1,0) or (-1,1)

  // (n1,n2) = (0,1) or (-1,1)
  if (    ( (n1 == 0)  && (n2 == 1) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,1) =
       + 1.6449340668482264e+00
       + 6.9314718055994530e-01*HR1(-1)
       - 5.0000000000000000e-01*HR1(-1)*HR1(-1)
       + HR1( -1)*HR1(0)
       - HR1( -1)*HR1(1)
       + HR1(0) *HR1(1)
       + 6.9314718055994530e-01*HR1(1)
       + HR2( -1,1)
       - HR2(0, -1)
       - HR2(0,1);
    if (r < 0.0){
      Hi2(0,1) =
       - HR1( -1)
       - HR1(1);
    }

    if ( nw > 2 ){
      HY3(0,0,1) =
       + 1.2020569031595942e+00
       - 1.6449340668482264e+00*HR1(-1)
       - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
       + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
       - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
       + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
       - HR1( -1)*HR1(0)*HR1(1)
       - 6.9314718055994530e-01*HR1(-1)*HR1(1)
       + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)
       + HR1( -1)*HR2(0,-1)
       + HR1( -1)*HR2(0,1)
       - 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)
       - 1.6449340668482264e+00*HR1(1)
       - 3.4657359027997265e-01*HR1(1)*HR1(1)
       - HR1(1) *HR2(-1,1)
       + HR1(1) *HR2(0,-1)
       + HR1(1) *HR2(0,1)
       - HR3( -1,-1,1)
       + HR3( -1,1,1)
       - HR3(0, -1,-1)
       - HR3(0, -1,1)
       - HR3(0,1, -1)
       - HR3(0,1,1);
      HY3(0,1,1) =
       + 1.2020569031595942e+00
       - 2.4022650695910071e-01*HR1(-1)
       + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
       - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
       + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
       - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
       - 6.9314718055994530e-01*HR1(-1)*HR1(0)
       - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)
       + HR1( -1)*HR1(0)*HR1(1)
       + 6.9314718055994530e-01*HR1(-1)*HR1(1)
       + HR1( -1)*HR2(-1,1)
       - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)
       - 6.9314718055994530e-01*HR1(0)*HR1(1)
       - HR1(0) *HR2(-1,1)
       + HR1(0) *HR2(0,-1)
       + HR1(0) *HR2(0,1)
       - 2.4022650695910071e-01*HR1(1)
       - 6.9314718055994530e-01*HR2(-1,1)
       + 6.9314718055994530e-01*HR2(0,-1)
       + 6.9314718055994530e-01*HR2(0,1)
       - HR3( -1,-1,1)
       - HR3(0, -1,-1)
       - HR3(0,0, -1)
       - HR3(0,0,1)
       - HR3(0,1, -1);
      if (r < 0.0){
        HY3(0,1,1) = HY3(0,1,1)
         + 4.9348022005446793e+00*HR1(-1)
         + 4.9348022005446793e+00*HR1(1);
        Hi3(0,0,1) =
         + 5.0000000000000000e-01*HR1(-1)*HR1(-1)
         + HR1( -1)*HR1(1)
         + 5.0000000000000000e-01*HR1(1)*HR1(1);
        Hi3(0,1,1) =
         + 6.9314718055994530e-01*HR1(-1)
         - 5.0000000000000000e-01*HR1(-1)*HR1(-1)
         + HR1( -1)*HR1(0)
         - HR1( -1)*HR1(1)
         + HR1(0) *HR1(1)
         + 6.9314718055994530e-01*HR1(1)
         + HR2( -1,1)
         - HR2(0, -1)
         - HR2(0,1);
      }
    }

    if ( nw > 3 ){
      HY4(0,0,0,1) =
        + 1.0823232337111381e+00
        - 1.2020569031595942e+00*HR1(-1)
        + 8.2246703342411321e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 1.6449340668482264e+00*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        - HR1( -1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR2(0,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,-1,1)
        + HR1( -1)*HR3(0,1,-1)
        + HR1( -1)*HR3(0,1,1)
        + 1.6666666666666666e-01*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        - 1.2020569031595942e+00*HR1(1)
        + 8.2246703342411321e-01*HR1(1)*HR1(1)
        + 1.1552453009332421e-01*HR1(1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,1)
        + HR1(1) *HR3(-1,-1,1)
        - HR1(1) *HR3(-1,1,1)
        + HR1(1) *HR3(0,-1,-1)
        + HR1(1) *HR3(0,-1,1)
        + HR1(1) *HR3(0,1,-1)
        + HR1(1) *HR3(0,1,1)
        + HR4( -1,-1,-1,1)
        - HR4( -1,-1,1,1)
        + HR4( -1,1,1,1)
        - HR4(0, -1,-1,-1)
        - HR4(0, -1,-1,1)
        - HR4(0, -1,1,-1)
        - HR4(0, -1,1,1)
        - HR4(0,1, -1,-1)
        - HR4(0,1, -1,1)
        - HR4(0,1,1, -1)
        - HR4(0,1,1,1);
      HY4(0,0,1,1) =
        + 2.7058080842778454e-01
        - 1.2020569031595942e+00*HR1(-1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - HR1( -1)*HR1(0)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR2(0,1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
        - HR1( -1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(0,1)
        - HR1( -1)*HR3(-1,-1,1)
        + HR1( -1)*HR3(-1,1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,0,-1)
        + HR1( -1)*HR3(0,0,1)
        + HR1( -1)*HR3(0,1,-1)
        + 2.5000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        + 3.4657359027997265e-01*HR1(0)*HR1(1)*HR1(1)
        + HR1(0) *HR1(1)*HR2(-1,1)
        - HR1(0) *HR1(1)*HR2(0,-1)
        - HR1(0) *HR1(1)*HR2(0,1)
        + HR1(0) *HR3(-1,-1,1)
        - HR1(0) *HR3(-1,1,1)
        + HR1(0) *HR3(0,-1,-1)
        + HR1(0) *HR3(0,-1,1)
        + HR1(0) *HR3(0,1,-1)
        + HR1(0) *HR3(0,1,1)
        - 1.2020569031595942e+00*HR1(1)
        + 1.2011325347955035e-01*HR1(1)*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR2(0,1)
        + HR1(1) *HR3(-1,-1,1)
        + HR1(1) *HR3(0,-1,-1)
        + HR1(1) *HR3(0,0,-1)
        + HR1(1) *HR3(0,0,1)
        + HR1(1) *HR3(0,1,-1)
        + 6.9314718055994530e-01*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR3(-1,1,1)
        + 6.9314718055994530e-01*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR3(0,1,1)
        + 2.0000000000000000e+00*HR4(-1,-1,-1,1)
        - HR4( -1,-1,1,1)
        - 2.0000000000000000e+00*HR4(0,-1,-1,-1)
        - HR4(0, -1,-1,1)
        - HR4(0, -1,1,-1)
        - HR4(0,0, -1,-1)
        - HR4(0,0, -1,1)
        - HR4(0,0,1, -1)
        - HR4(0,0,1,1)
        - 2.0000000000000000e+00*HR4(0,1,-1,-1)
        - HR4(0,1, -1,1)
        - HR4(0,1,1, -1);
      HY4(0,1,1,1) =
        + 1.0823232337111381e+00
        + 5.5504108664821579e-02*HR1(-1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(0)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
        - HR1( -1)*HR1(0)*HR2(-1,1)
        - 2.4022650695910071e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR3(-1,-1,1)
        + 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR1(1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(0,1)
        + 2.4022650695910071e-01*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR2(0,1)
        + HR1(0) *HR3(-1,-1,1)
        + HR1(0) *HR3(0,-1,-1)
        + HR1(0) *HR3(0,0,-1)
        + HR1(0) *HR3(0,0,1)
        + HR1(0) *HR3(0,1,-1)
        + 5.5504108664821579e-02*HR1(1)
        + 2.4022650695910071e-01*HR2(-1,1)
        - 2.4022650695910071e-01*HR2(0,-1)
        - 2.4022650695910071e-01*HR2(0,1)
        + 6.9314718055994530e-01*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR3(0,0,-1)
        + 6.9314718055994530e-01*HR3(0,0,1)
        + 6.9314718055994530e-01*HR3(0,1,-1)
        + HR4( -1,-1,-1,1)
        - HR4(0, -1,-1,-1)
        - HR4(0,0, -1,-1)
        - HR4(0,0,0, -1)
        - HR4(0,0,0,1)
        - HR4(0,0,1, -1)
        - HR4(0,1, -1,-1);
      if (r < 0.0){
        HY4(0,0,1,1) = HY4(0,0,1,1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)
          - 4.9348022005446793e+00*HR1(-1)*HR1(1)
          - 2.4674011002723396e+00*HR1(1)*HR1(1);
        HY4(0,1,1,1) = HY4(0,1,1,1)
          - 3.4205442319285582e+00*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)
          - 4.9348022005446793e+00*HR1(-1)*HR1(0)
          + 4.9348022005446793e+00*HR1(-1)*HR1(1)
          - 4.9348022005446793e+00*HR1(0)*HR1(1)
          - 3.4205442319285582e+00*HR1(1)
          - 4.9348022005446793e+00*HR2(-1,1)
          + 4.9348022005446793e+00*HR2(0,-1)
          + 4.9348022005446793e+00*HR2(0,1);
        Hi4(0,0,0,1) =
          - 1.666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 5.000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)
          - 1.666666666666666e-01*HR1(1)*HR1(1)*HR1(1);
        Hi4(0,0,1,1) =
          - 3.465735902799726e-01*HR1(-1)*HR1(-1)
          + 1.666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 5.000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          - HR1( -1)*HR1(0)*HR1(1)
          - 6.931471805599453e-01*HR1(-1)*HR1(1)
          + 5.000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)
          + HR1( -1)*HR2(0,-1)
          + HR1( -1)*HR2(0,1)
          - 5.000000000000000e-01*HR1(0)*HR1(1)*HR1(1)
          - 3.465735902799726e-01*HR1(1)*HR1(1)
          - HR1(1) *HR2(-1,1)
          + HR1(1) *HR2(0,-1)
          + HR1(1) *HR2(0,1)
          - HR3( -1,-1,1)
          + HR3( -1,1,1)
          - HR3(0, -1,-1)
          - HR3(0, -1,1)
          - HR3(0,1, -1)
          - HR3(0,1,1);
        Hi4(0,1,1,1) =
          + 1.404707559889125e+00*HR1(-1)
          + 3.465735902799726e-01*HR1(-1)*HR1(-1)
          - 1.666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 5.000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
          - 5.000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 6.931471805599453e-01*HR1(-1)*HR1(0)
          - 5.000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)
          + HR1( -1)*HR1(0)*HR1(1)
          + 6.931471805599453e-01*HR1(-1)*HR1(1)
          + HR1( -1)*HR2(-1,1)
          - 5.000000000000000e-01*HR1(0)*HR1(0)*HR1(1)
          - 6.931471805599453e-01*HR1(0)*HR1(1)
          - HR1(0) *HR2(-1,1)
          + HR1(0) *HR2(0,-1)
          + HR1(0) *HR2(0,1)
          + 1.404707559889125e+00*HR1(1)
          - 6.931471805599453e-01*HR2(-1,1)
          + 6.931471805599453e-01*HR2(0,-1)
          + 6.931471805599453e-01*HR2(0,1)
          - HR3( -1,-1,1)
          - HR3(0, -1,-1)
          - HR3(0,0, -1)
          - HR3(0,0,1)
          - HR3(0,1, -1);
      }
    }
    // nw > 3 endif

    if ( nw > 4 ){
      HY5(0,0,0,0,1) =
        + 1.0369277551433699e+00
        - 1.0823232337111381e+00*HR1(-1)
        + 6.0102845157979714e-01*HR1(-1)*HR1(-1)
        - 2.7415567780803773e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        + 1.2020569031595942e+00*HR1(-1)*HR1(1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(1)*HR1(1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        - HR1( -1)*HR1(1)*HR3(0,1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + HR1( -1)*HR4(0,-1,1,1)
        + HR1( -1)*HR4(0,1,-1,-1)
        + HR1( -1)*HR4(0,1,-1,1)
        + HR1( -1)*HR4(0,1,1,-1)
        + HR1( -1)*HR4(0,1,1,1)
        - 4.1666666666666666e-02*HR1(0)*HR1(1)*HR1(1)*HR1(1)*HR1(1)
        - 1.0823232337111381e+00*HR1(1)
        + 6.0102845157979714e-01*HR1(1)*HR1(1)
        - 2.7415567780803773e-01*HR1(1)*HR1(1)*HR1(1)
        - 2.8881132523331054e-02*HR1(1)*HR1(1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(1)*HR1(1)*HR1(1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 1.6666666666666666e-01*HR1(1)*HR1(1)*HR1(1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,1,1)
        - HR1(1) *HR4(-1,-1,-1,1)
        + HR1(1) *HR4(-1,-1,1,1)
        - HR1(1) *HR4(-1,1,1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,-1,1,-1)
        + HR1(1) *HR4(0,-1,1,1)
        + HR1(1) *HR4(0,1,-1,-1)
        + HR1(1) *HR4(0,1,-1,1)
        + HR1(1) *HR4(0,1,1,-1)
        + HR1(1) *HR4(0,1,1,1)
        - HR5( -1,-1,-1,-1,1)
        + HR5( -1,-1,-1,1,1)
        - HR5( -1,-1,1,1,1)
        + HR5( -1,1,1,1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - HR5(0, -1,1,-1,-1)
        - HR5(0, -1,1,-1,1)
        - HR5(0, -1,1,1,-1)
        - HR5(0, -1,1,1,1)
        - HR5(0,1, -1,-1,-1)
        - HR5(0,1, -1,-1,1)
        - HR5(0,1, -1,1,-1)
        - HR5(0,1, -1,1,1)
        - HR5(0,1,1, -1,-1)
        - HR5(0,1,1, -1,1)
        - HR5(0,1,1,1, -1)
        - HR5(0,1,1,1,1);
      HY5(0,0,0,1,1) =
        + 9.6551159989443734e-02
        - 2.7058080842778454e-01*HR1(-1)
        + 6.0102845157979714e-01*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,-1,1)
        - HR1( -1)*HR1(0)*HR3(0,1,-1)
        - HR1( -1)*HR1(0)*HR3(0,1,1)
        + 1.2020569031595942e+00*HR1(-1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(-1,1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,1,1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(-1,-1,1,1)
        + HR1( -1)*HR4(-1,1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1( -1)*HR4(0,0,-1,1)
        + HR1( -1)*HR4(0,0,1,-1)
        + HR1( -1)*HR4(0,0,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        + HR1( -1)*HR4(0,1,-1,1)
        + HR1( -1)*HR4(0,1,1,-1)
        - 8.3333333333333333e-02*HR1(0)*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        - 1.1552453009332421e-01*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(0,1)
        - HR1(0) *HR1(1)*HR3(-1,-1,1)
        + HR1(0) *HR1(1)*HR3(-1,1,1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR1(1)*HR3(0,-1,1)
        - HR1(0) *HR1(1)*HR3(0,1,-1)
        - HR1(0) *HR1(1)*HR3(0,1,1)
        - HR1(0) *HR4(-1,-1,-1,1)
        + HR1(0) *HR4(-1,-1,1,1)
        - HR1(0) *HR4(-1,1,1,1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,-1,1,-1)
        + HR1(0) *HR4(0,-1,1,1)
        + HR1(0) *HR4(0,1,-1,-1)
        + HR1(0) *HR4(0,1,-1,1)
        + HR1(0) *HR4(0,1,1,-1)
        + HR1(0) *HR4(0,1,1,1)
        - 2.7058080842778454e-01*HR1(1)
        + 6.0102845157979714e-01*HR1(1)*HR1(1)
        - 4.0037751159850118e-02*HR1(1)*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,0,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + HR1(1) *HR4(-1,-1,1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,-1,1,-1)
        + HR1(1) *HR4(0,0,-1,-1)
        + HR1(1) *HR4(0,0,-1,1)
        + HR1(1) *HR4(0,0,1,-1)
        + HR1(1) *HR4(0,0,1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        + HR1(1) *HR4(0,1,-1,1)
        + HR1(1) *HR4(0,1,1,-1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,1,1)
        - 6.9314718055994530e-01*HR4(-1,1,1,1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,1,1)
        + 6.9314718055994530e-01*HR4(0,1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,1)
        + 6.9314718055994530e-01*HR4(0,1,1,-1)
        + 6.9314718055994530e-01*HR4(0,1,1,1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        - HR5( -1,-1,1,1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - 2.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        - HR5(0, -1,1,-1,1)
        - HR5(0, -1,1,1,-1)
        - HR5(0,0, -1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,1,-1)
        - HR5(0,0, -1,1,1)
        - HR5(0,0,1, -1,-1)
        - HR5(0,0,1, -1,1)
        - HR5(0,0,1,1, -1)
        - HR5(0,0,1,1,1)
        - 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(0,1,-1,1,-1)
        - HR5(0,1, -1,1,1)
        - 2.0000000000000000e+00*HR5(0,1,1,-1,-1)
        - HR5(0,1,1, -1,1)
        - HR5(0,1,1,1, -1);
      HY5(0,0,1,0,1) =
        + 2.2881039760335375e-01
        - 8.1174242528335364e-01*HR1(-1)
        - 1.7721476084810206e+00*HR1(-1)*HR1(-1)
        + 2.7415567780803773e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,1)
        + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,1)
        + HR1( -1)*HR1(-1)*HR3(0,1,-1)
        - 1.6449340668482264e+00*HR1(-1)*HR1(0)*HR1(1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,1,1)
        - 3.5442952169620413e+00*HR1(-1)*HR1(1)
        + 8.2246703342411321e-01*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,1,-1)
        + 1.6449340668482264e+00*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        - HR1( -1)*HR2(0,-1)*HR2(0,1)
        + 1.6449340668482264e+00*HR1(-1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,1,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(-1,1,1,1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,1,1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,1,1,-1)
        - 8.2246703342411321e-01*HR1(0)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(0,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,1,1)
        + 3.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(-1,-1,1,1)
        + 3.0000000000000000e+00*HR1(0)*HR4(-1,1,1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,1,-1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,1,-1,-1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,1,-1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,1,1,-1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,1,1,1)
        - 8.1174242528335364e-01*HR1(1)
        - 1.7721476084810206e+00*HR1(1)*HR1(1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,1)
        + HR1(1) *HR1(1)*HR3(-1,-1,1)
        + HR1(1) *HR1(1)*HR3(0,-1,-1)
        + HR1(1) *HR1(1)*HR3(0,0,-1)
        + HR1(1) *HR1(1)*HR3(0,0,1)
        + HR1(1) *HR1(1)*HR3(0,1,-1)
        - 1.6449340668482264e+00*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR2(-1,1)*HR2(-1,1)
        + HR1(1) *HR2(-1,1)*HR2(0,-1)
        + HR1(1) *HR2(-1,1)*HR2(0,1)
        + 1.6449340668482264e+00*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        - HR1(1) *HR2(0,-1)*HR2(0,1)
        + 1.6449340668482264e+00*HR1(1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,1)*HR2(0,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,1,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,1,1)
        + 4.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,1,1)
        - 4.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,1,1)
        - 4.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,1,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,1,1,-1)
        + HR2( -1,1)*HR3(-1,1,1)
        + HR2(0, -1)*HR3(-1,-1,1)
        - HR2(0, -1)*HR3(-1,1,1)
        + HR2(0, -1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(0,-1,1)
        + HR2(0, -1)*HR3(0,1,-1)
        + HR2(0, -1)*HR3(0,1,1)
        + HR2(0,1) *HR3(-1,-1,1)
        - HR2(0,1) *HR3(-1,1,1)
        + HR2(0,1) *HR3(0,1,-1)
        + HR2(0,1) *HR3(0,1,1)
        - 1.6449340668482264e+00*HR3(-1,-1,1)
        + 1.6449340668482264e+00*HR3(-1,1,1)
        - 1.6449340668482264e+00*HR3(0,-1,-1)
        - 1.6449340668482264e+00*HR3(0,-1,1)
        - 1.6449340668482264e+00*HR3(0,1,-1)
        - 1.6449340668482264e+00*HR3(0,1,1)
        + 2.0794415416798359e+00*HR4(-1,-1,-1,1)
        - 2.0794415416798359e+00*HR4(-1,-1,1,1)
        + 2.0794415416798359e+00*HR4(-1,1,1,1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,1)
        - 2.0794415416798359e+00*HR4(0,-1,1,-1)
        - 2.0794415416798359e+00*HR4(0,-1,1,1)
        - 2.0794415416798359e+00*HR4(0,1,-1,-1)
        - 2.0794415416798359e+00*HR4(0,1,-1,1)
        - 2.0794415416798359e+00*HR4(0,1,1,-1)
        - 2.0794415416798359e+00*HR4(0,1,1,1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        - HR5( -1,-1,1,-1,1)
        - HR5( -1,1,-1,1,1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + HR5(0, -1,-1,0,1)
        + 5.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,1)
        - HR5(0, -1,0,-1,-1)
        + HR5(0, -1,0,1,1)
        + 5.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,1,-1,1)
        + HR5(0, -1,1,0,1)
        + 3.0000000000000000e+00*HR5(0,-1,1,1,-1)
        + 2.0000000000000000e+00*HR5(0,0,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,0,-1,1,-1)
        + 4.0000000000000000e+00*HR5(0,0,-1,1,1)
        + 2.0000000000000000e+00*HR5(0,0,1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,0,1,-1,1)
        + 7.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + 4.0000000000000000e+00*HR5(0,1,-1,-1,1)
        + 5.0000000000000000e+00*HR5(0,1,-1,1,-1)
        + 2.0000000000000000e+00*HR5(0,1,-1,1,1)
        - HR5(0,1,0,1, -1)
        - HR5(0,1,0,1,1)
        + 5.0000000000000000e+00*HR5(0,1,1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,1,1,-1,1)
        + 3.0000000000000000e+00*HR5(0,1,1,1,-1);
      HY5(0,0,1,1,1) =
        + 9.6551159989443734e-02
        - 1.0823232337111381e+00*HR1(-1)
        - 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,1)
        - 2.4022650695910071e-01*HR1(-1)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(-1,1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,0,-1)
        - HR1( -1)*HR1(0)*HR3(0,0,1)
        - HR1( -1)*HR1(0)*HR3(0,1,-1)
        - 5.5504108664821579e-02*HR1(-1)*HR1(1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(-1,-1,1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1( -1)*HR4(0,0,0,-1)
        + HR1( -1)*HR4(0,0,0,1)
        + HR1( -1)*HR4(0,0,1,-1)
        + HR1( -1)*HR4(0,1,-1,-1)
        - 8.3333333333333333e-02*HR1(0)*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        - 1.7328679513998632e-01*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,1,1)
        - 1.2011325347955035e-01*HR1(0)*HR1(1)*HR1(1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,1)
        - HR1(0) *HR1(1)*HR3(-1,-1,1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR1(1)*HR3(0,0,-1)
        - HR1(0) *HR1(1)*HR3(0,0,1)
        - HR1(0) *HR1(1)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        + HR1(0) *HR4(-1,-1,1,1)
        + 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,-1,1,-1)
        + HR1(0) *HR4(0,0,-1,-1)
        + HR1(0) *HR4(0,0,-1,1)
        + HR1(0) *HR4(0,0,1,-1)
        + HR1(0) *HR4(0,0,1,1)
        + 2.0000000000000000e+00*HR1(0)*HR4(0,1,-1,-1)
        + HR1(0) *HR4(0,1,-1,1)
        + HR1(0) *HR4(0,1,1,-1)
        - 1.0823232337111381e+00*HR1(1)
        - 2.7752054332410789e-02*HR1(1)*HR1(1)
        - 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,0,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        - HR1(1) *HR4(-1,-1,-1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,0,-1,-1)
        + HR1(1) *HR4(0,0,0,-1)
        + HR1(1) *HR4(0,0,0,1)
        + HR1(1) *HR4(0,0,1,-1)
        + HR1(1) *HR4(0,1,-1,-1)
        - 2.4022650695910071e-01*HR3(-1,-1,1)
        + 2.4022650695910071e-01*HR3(-1,1,1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,-1,1)
        - 2.4022650695910071e-01*HR3(0,1,-1)
        - 2.4022650695910071e-01*HR3(0,1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,1,1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,1)
        + 6.9314718055994530e-01*HR4(0,0,1,-1)
        + 6.9314718055994530e-01*HR4(0,0,1,1)
        + 1.3862943611198906e+00*HR4(0,1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,1)
        + 6.9314718055994530e-01*HR4(0,1,1,-1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,-1,1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0, -1,1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,1,-1)
        - HR5(0,0,0, -1,-1)
        - HR5(0,0,0, -1,1)
        - HR5(0,0,0,1, -1)
        - HR5(0,0,0,1,1)
        - 2.0000000000000000e+00*HR5(0,0,1,-1,-1)
        - HR5(0,0,1, -1,1)
        - HR5(0,0,1,1, -1)
        - 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        - HR5(0,1, -1,-1,1)
        - HR5(0,1, -1,1,-1)
        - HR5(0,1,1, -1,-1);
      HY5(0,1,0,1,1) =
        + 2.2881039760335375e-01
        + 4.0801720544311065e+00*HR1(-1)
        - 6.0102845157979714e-01*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        + HR1( -1)*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(-1)*HR3(-1,1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        + 1.2020569031595942e+00*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,0,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,1,-1)
        - 1.2020569031595942e+00*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(1)*HR3(0,0,-1)
        + HR1( -1)*HR1(1)*HR3(0,0,1)
        + HR1( -1)*HR1(1)*HR3(0,1,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(0,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,0,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,0,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,1,-1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,0,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,0,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(0,1)
        + HR1(0) *HR1(0)*HR3(-1,-1,1)
        - HR1(0) *HR1(0)*HR3(-1,1,1)
        + HR1(0) *HR1(0)*HR3(0,-1,-1)
        + HR1(0) *HR1(0)*HR3(0,-1,1)
        + HR1(0) *HR1(0)*HR3(0,1,-1)
        + HR1(0) *HR1(0)*HR3(0,1,1)
        + 1.2020569031595942e+00*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,0,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,0,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR2(-1,1)*HR2(-1,1)
        + HR1(0) *HR2(-1,1)*HR2(0,-1)
        + HR1(0) *HR2(-1,1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(0)*HR2(0,-1)*HR2(0,-1)
        - HR1(0) *HR2(0,-1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(0)*HR2(0,1)*HR2(0,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(0)*HR3(0,-1,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(0,1,-1)
        + 1.3862943611198906e+00*HR1(0)*HR3(0,1,1)
        + 4.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,1,1)
        - 4.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,0,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,0,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,0,1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,0,1,1)
        - 4.0000000000000000e+00*HR1(0)*HR4(0,1,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,1,1,-1)
        + 4.0801720544311065e+00*HR1(1)
        + 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        - 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        - 2.4022650695910071e-01*HR1(1)*HR2(0,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,0,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,0,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,0,0,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,0,0,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,0,1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        + 1.2020569031595942e+00*HR2(-1,1)
        - 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,1)
        - HR2( -1,1)*HR3(-1,-1,1)
        - HR2( -1,1)*HR3(0,-1,-1)
        - HR2( -1,1)*HR3(0,0,-1)
        - HR2( -1,1)*HR3(0,0,1)
        - HR2( -1,1)*HR3(0,1,-1)
        - 1.2020569031595942e+00*HR2(0,-1)
        - 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR2(0,-1)*HR2(0,1)
        + HR2(0, -1)*HR3(0,0,-1)
        + HR2(0, -1)*HR3(0,0,1)
        - 1.2020569031595942e+00*HR2(0,1)
        - 3.4657359027997265e-01*HR2(0,1)*HR2(0,1)
        + HR2(0,1) *HR3(0,-1,-1)
        + HR2(0,1) *HR3(0,0,-1)
        + HR2(0,1) *HR3(0,0,1)
        + 4.8045301391820142e-01*HR3(-1,-1,1)
        - 4.8045301391820142e-01*HR3(-1,1,1)
        + 4.8045301391820142e-01*HR3(0,-1,-1)
        + 4.8045301391820142e-01*HR3(0,-1,1)
        + 4.8045301391820142e-01*HR3(0,1,-1)
        + 4.8045301391820142e-01*HR3(0,1,1)
        + 2.7725887222397812e+00*HR4(-1,-1,-1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,1,1)
        - 2.7725887222397812e+00*HR4(0,-1,-1,-1)
        - 1.3862943611198906e+00*HR4(0,-1,-1,1)
        - 1.3862943611198906e+00*HR4(0,-1,1,-1)
        - 1.3862943611198906e+00*HR4(0,0,-1,-1)
        - 1.3862943611198906e+00*HR4(0,0,-1,1)
        - 1.3862943611198906e+00*HR4(0,0,1,-1)
        - 1.3862943611198906e+00*HR4(0,0,1,1)
        - 2.7725887222397812e+00*HR4(0,1,-1,-1)
        - 1.3862943611198906e+00*HR4(0,1,-1,1)
        - 1.3862943611198906e+00*HR4(0,1,1,-1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,1,-1,1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - HR5(0, -1,-1,0,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        + HR5(0, -1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        + 7.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        + HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,0,-1)
        - HR5(0,0, -1,0,1)
        + 2.0000000000000000e+00*HR5(0,0,-1,1,-1)
        + 5.0000000000000000e+00*HR5(0,0,1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,0,1,-1,1)
        - HR5(0,0,1,0, -1)
        - HR5(0,0,1,0,1)
        + 4.0000000000000000e+00*HR5(0,0,1,1,-1)
        + 7.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,1,-1,1,-1)
        + HR5(0,1,0,1, -1)
        + 2.0000000000000000e+00*HR5(0,1,1,-1,-1);
      HY5(0,1,1,1,1) =
        + 1.0369277551433699e+00
        - 9.6181291076284771e-03*HR1(-1)
        + 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.5504108664821579e-02*HR1(-1)*HR1(0)
        - 1.2011325347955035e-01*HR1(-1)*HR1(0)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(0)*HR1(0)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + 5.5504108664821579e-02*HR1(-1)*HR1(1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - 4.1666666666666666e-02*HR1(0)*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        - 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR2(0,-1)
        + 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR2(0,1)
        - 1.2011325347955035e-01*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,0,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,1,-1)
        - 5.5504108664821579e-02*HR1(0)*HR1(1)
        - 2.4022650695910071e-01*HR1(0)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(0)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(0)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,0,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,1,-1)
        - HR1(0) *HR4(-1,-1,-1,1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,0,-1,-1)
        + HR1(0) *HR4(0,0,0,-1)
        + HR1(0) *HR4(0,0,0,1)
        + HR1(0) *HR4(0,0,1,-1)
        + HR1(0) *HR4(0,1,-1,-1)
        - 9.6181291076284771e-03*HR1(1)
        - 5.5504108664821579e-02*HR2(-1,1)
        + 5.5504108664821579e-02*HR2(0,-1)
        + 5.5504108664821579e-02*HR2(0,1)
        - 2.4022650695910071e-01*HR3(-1,-1,1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,0,-1)
        - 2.4022650695910071e-01*HR3(0,0,1)
        - 2.4022650695910071e-01*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,0,-1)
        + 6.9314718055994530e-01*HR4(0,0,0,1)
        + 6.9314718055994530e-01*HR4(0,0,1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - HR5( -1,-1,-1,-1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0,0, -1,-1,-1)
        - HR5(0,0,0, -1,-1)
        - HR5(0,0,0,0, -1)
        - HR5(0,0,0,0,1)
        - HR5(0,0,0,1, -1)
        - HR5(0,0,1, -1,-1)
        - HR5(0,1, -1,-1,-1);
      if (r < 0.0){
        HY5(0,0,0,1,1) = HY5(0,0,0,1,1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(1)*HR1(1)
          + 8.2246703342411321e-01*HR1(1)*HR1(1)*HR1(1);
        HY5(0,0,1,1,1) = HY5(0,0,1,1,1)
          + 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(0)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 4.9348022005446793e+00*HR1(-1)*HR1(0)*HR1(1)
          + 3.4205442319285582e+00*HR1(-1)*HR1(1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(1)*HR1(1)
          - 4.9348022005446793e+00*HR1(-1)*HR2(0,-1)
          - 4.9348022005446793e+00*HR1(-1)*HR2(0,1)
          + 2.4674011002723396e+00*HR1(0)*HR1(1)*HR1(1)
          + 1.7102721159642791e+00*HR1(1)*HR1(1)
          + 4.9348022005446793e+00*HR1(1)*HR2(-1,1)
          - 4.9348022005446793e+00*HR1(1)*HR2(0,-1)
          - 4.9348022005446793e+00*HR1(1)*HR2(0,1)
          + 4.9348022005446793e+00*HR3(-1,-1,1)
          - 4.9348022005446793e+00*HR3(-1,1,1)
          + 4.9348022005446793e+00*HR3(0,-1,-1)
          + 4.9348022005446793e+00*HR3(0,-1,1)
          + 4.9348022005446793e+00*HR3(0,1,-1)
          + 4.9348022005446793e+00*HR3(0,1,1);
        HY5(0,1,0,1,1) = HY5(0,1,0,1,1)
          - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(-1,1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(0,-1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(0,1)
          - 4.9348022005446793e+00*HR1(1)*HR2(-1,1)
          + 4.9348022005446793e+00*HR1(1)*HR2(0,-1)
          + 4.9348022005446793e+00*HR1(1)*HR2(0,1)
          - 9.8696044010893586e+00*HR3(-1,-1,1)
          + 9.8696044010893586e+00*HR3(-1,1,1)
          - 9.8696044010893586e+00*HR3(0,-1,-1)
          - 9.8696044010893586e+00*HR3(0,-1,1)
          - 9.8696044010893586e+00*HR3(0,1,-1)
          - 9.8696044010893586e+00*HR3(0,1,1);
        HY5(0,1,1,1,1) = HY5(0,1,1,1,1)
          - 2.8732418312458363e+00*HR1(-1)
          - 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(0)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 3.4205442319285582e+00*HR1(-1)*HR1(0)
          + 2.4674011002723396e+00*HR1(-1)*HR1(0)*HR1(0)
          - 4.9348022005446793e+00*HR1(-1)*HR1(0)*HR1(1)
          - 3.4205442319285582e+00*HR1(-1)*HR1(1)
          - 4.9348022005446793e+00*HR1(-1)*HR2(-1,1)
          + 2.4674011002723396e+00*HR1(0)*HR1(0)*HR1(1)
          + 3.4205442319285582e+00*HR1(0)*HR1(1)
          + 4.9348022005446793e+00*HR1(0)*HR2(-1,1)
          - 4.9348022005446793e+00*HR1(0)*HR2(0,-1)
          - 4.9348022005446793e+00*HR1(0)*HR2(0,1)
          - 2.8732418312458363e+00*HR1(1)
          + 3.4205442319285582e+00*HR2(-1,1)
          - 3.4205442319285582e+00*HR2(0,-1)
          - 3.4205442319285582e+00*HR2(0,1)
          + 4.9348022005446793e+00*HR3(-1,-1,1)
          + 4.9348022005446793e+00*HR3(0,-1,-1)
          + 4.9348022005446793e+00*HR3(0,0,-1)
          + 4.9348022005446793e+00*HR3(0,0,1)
          + 4.9348022005446793e+00*HR3(0,1,-1);
        Hi5(0,0,0,0,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
          + 4.1666666666666666e-02*HR1(1)*HR1(1)*HR1(1)*HR1(1);
        Hi5(0,0,0,1,1) =
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
          - HR1( -1)*HR1(1)*HR2(0,-1)
          - HR1( -1)*HR1(1)*HR2(0,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,-1,1)
          + HR1( -1)*HR3(0,1,-1)
          + HR1( -1)*HR3(0,1,1)
          + 1.6666666666666666e-01*HR1(0)*HR1(1)*HR1(1)*HR1(1)
          + 1.1552453009332421e-01*HR1(1)*HR1(1)*HR1(1)
          + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(-1,1)
          - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
          - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,1)
          + HR1(1) *HR3(-1,-1,1)
          - HR1(1) *HR3(-1,1,1)
          + HR1(1) *HR3(0,-1,-1)
          + HR1(1) *HR3(0,-1,1)
          + HR1(1) *HR3(0,1,-1)
          + HR1(1) *HR3(0,1,1)
          + HR4( -1,-1,-1,1)
          - HR4( -1,-1,1,1)
          + HR4( -1,1,1,1)
          - HR4(0, -1,-1,-1)
          - HR4(0, -1,-1,1)
          - HR4(0, -1,1,-1)
          - HR4(0, -1,1,1)
          - HR4(0,1, -1,-1)
          - HR4(0,1, -1,1)
          - HR4(0,1,1, -1)
          - HR4(0,1,1,1);
        Hi5(0,0,1,0,1) =
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
          + 1.6449340668482264e+00*HR1(-1)*HR1(1)
          + HR1( -1)*HR1(1)*HR2(-1,1)
          + HR1( -1)*HR1(1)*HR2(0,-1)
          + HR1( -1)*HR1(1)*HR2(0,1)
          + HR1( -1)*HR3(-1,-1,1)
          - HR1( -1)*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,1,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,1,1)
          + 8.2246703342411321e-01*HR1(1)*HR1(1)
          - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(-1,1)
          + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
          + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(-1,-1,1)
          + 2.0000000000000000e+00*HR1(1)*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,1,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,1,1)
          - 3.0000000000000000e+00*HR4(-1,-1,-1,1)
          + 3.0000000000000000e+00*HR4(-1,-1,1,1)
          - 3.0000000000000000e+00*HR4(-1,1,1,1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,1)
          + 3.0000000000000000e+00*HR4(0,-1,1,-1)
          + 3.0000000000000000e+00*HR4(0,-1,1,1)
          + 3.0000000000000000e+00*HR4(0,1,-1,-1)
          + 3.0000000000000000e+00*HR4(0,1,-1,1)
          + 3.0000000000000000e+00*HR4(0,1,1,-1)
          + 3.0000000000000000e+00*HR4(0,1,1,1);
        Hi5(0,0,1,1,1) =
          - 7.0235377994456286e-01*HR1(-1)*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
          - HR1( -1)*HR1(0)*HR2(0,-1)
          - HR1( -1)*HR1(0)*HR2(0,1)
          - 1.4047075598891257e+00*HR1(-1)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
          - HR1( -1)*HR1(1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,1)
          - HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(-1,1,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,0,-1)
          + HR1( -1)*HR3(0,0,1)
          + HR1( -1)*HR3(0,1,-1)
          + 2.5000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR1(1)
          + 3.4657359027997265e-01*HR1(0)*HR1(1)*HR1(1)
          + HR1(0) *HR1(1)*HR2(-1,1)
          - HR1(0) *HR1(1)*HR2(0,-1)
          - HR1(0) *HR1(1)*HR2(0,1)
          + HR1(0) *HR3(-1,-1,1)
          - HR1(0) *HR3(-1,1,1)
          + HR1(0) *HR3(0,-1,-1)
          + HR1(0) *HR3(0,-1,1)
          + HR1(0) *HR3(0,1,-1)
          + HR1(0) *HR3(0,1,1)
          - 7.0235377994456286e-01*HR1(1)*HR1(1)
          + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(1)*HR2(0,1)
          + HR1(1) *HR3(-1,-1,1)
          + HR1(1) *HR3(0,-1,-1)
          + HR1(1) *HR3(0,0,-1)
          + HR1(1) *HR3(0,0,1)
          + HR1(1) *HR3(0,1,-1)
          + 6.9314718055994530e-01*HR3(-1,-1,1)
          - 6.9314718055994530e-01*HR3(-1,1,1)
          + 6.9314718055994530e-01*HR3(0,-1,-1)
          + 6.9314718055994530e-01*HR3(0,-1,1)
          + 6.9314718055994530e-01*HR3(0,1,-1)
          + 6.9314718055994530e-01*HR3(0,1,1)
          + 2.0000000000000000e+00*HR4(-1,-1,-1,1)
          - HR4( -1,-1,1,1)
          - 2.0000000000000000e+00*HR4(0,-1,-1,-1)
          - HR4(0, -1,-1,1)
          - HR4(0, -1,1,-1)
          - HR4(0,0, -1,-1)
          - HR4(0,0, -1,1)
          - HR4(0,0,1, -1)
          - HR4(0,0,1,1)
          - 2.0000000000000000e+00*HR4(0,1,-1,-1)
          - HR4(0,1, -1,1)
          - HR4(0,1,1, -1);
        Hi5(0,1,0,1,1) =
          - 1.2020569031595942e+00*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
          + HR1( -1)*HR1(0)*HR2(-1,1)
          + HR1( -1)*HR1(0)*HR2(0,-1)
          + HR1( -1)*HR1(0)*HR2(0,1)
          + HR1( -1)*HR1(1)*HR2(-1,1)
          + HR1( -1)*HR1(1)*HR2(0,-1)
          + HR1( -1)*HR1(1)*HR2(0,1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,1)
          + 2.0000000000000000e+00*HR1(-1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,0,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,0,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,1,-1)
          - HR1(0) *HR1(1)*HR2(-1,1)
          + HR1(0) *HR1(1)*HR2(0,-1)
          + HR1(0) *HR1(1)*HR2(0,1)
          - 2.0000000000000000e+00*HR1(0)*HR3(-1,-1,1)
          + 2.0000000000000000e+00*HR1(0)*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR1(0)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(0)*HR3(0,-1,1)
          - 2.0000000000000000e+00*HR1(0)*HR3(0,1,-1)
          - 2.0000000000000000e+00*HR1(0)*HR3(0,1,1)
          - 1.2020569031595942e+00*HR1(1)
          - 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(1)*HR2(0,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,0,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,0,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,1,-1)
          + 5.0000000000000000e-01*HR2(-1,1)*HR2(-1,1)
          - HR2( -1,1)*HR2(0,-1)
          - HR2( -1,1)*HR2(0,1)
          + 5.0000000000000000e-01*HR2(0,-1)*HR2(0,-1)
          + HR2(0, -1)*HR2(0,1)
          + 5.0000000000000000e-01*HR2(0,1)*HR2(0,1)
          - 1.3862943611198906e+00*HR3(-1,-1,1)
          + 1.3862943611198906e+00*HR3(-1,1,1)
          - 1.3862943611198906e+00*HR3(0,-1,-1)
          - 1.3862943611198906e+00*HR3(0,-1,1)
          - 1.3862943611198906e+00*HR3(0,1,-1)
          - 1.3862943611198906e+00*HR3(0,1,1)
          - 4.0000000000000000e+00*HR4(-1,-1,-1,1)
          + 2.0000000000000000e+00*HR4(-1,-1,1,1)
          + 4.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 2.0000000000000000e+00*HR4(0,-1,-1,1)
          + 2.0000000000000000e+00*HR4(0,-1,1,-1)
          + 2.0000000000000000e+00*HR4(0,0,-1,-1)
          + 2.0000000000000000e+00*HR4(0,0,-1,1)
          + 2.0000000000000000e+00*HR4(0,0,1,-1)
          + 2.0000000000000000e+00*HR4(0,0,1,1)
          + 4.0000000000000000e+00*HR4(0,1,-1,-1)
          + 2.0000000000000000e+00*HR4(0,1,-1,1)
          + 2.0000000000000000e+00*HR4(0,1,1,-1);
        Hi5(0,1,1,1,1) =
          - 1.0846773019780311e+00*HR1(-1)
          + 7.0235377994456286e-01*HR1(-1)*HR1(-1)
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          - 1.4047075598891257e+00*HR1(-1)*HR1(0)
          + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)
          + 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
          - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
          - HR1( -1)*HR1(0)*HR2(-1,1)
          + 1.4047075598891257e+00*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - HR1( -1)*HR3(-1,-1,1)
          + 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR1(1)
          + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR1(1)
          + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(-1,1)
          - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(0,-1)
          - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(0,1)
          - 1.4047075598891257e+00*HR1(0)*HR1(1)
          + 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(0)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(0)*HR2(0,1)
          + HR1(0) *HR3(-1,-1,1)
          + HR1(0) *HR3(0,-1,-1)
          + HR1(0) *HR3(0,0,-1)
          + HR1(0) *HR3(0,0,1)
          + HR1(0) *HR3(0,1,-1)
          - 1.0846773019780311e+00*HR1(1)
          - 1.4047075598891257e+00*HR2(-1,1)
          + 1.4047075598891257e+00*HR2(0,-1)
          + 1.4047075598891257e+00*HR2(0,1)
          + 6.9314718055994530e-01*HR3(-1,-1,1)
          + 6.9314718055994530e-01*HR3(0,-1,-1)
          + 6.9314718055994530e-01*HR3(0,0,-1)
          + 6.9314718055994530e-01*HR3(0,0,1)
          + 6.9314718055994530e-01*HR3(0,1,-1)
          + HR4( -1,-1,-1,1)
          - HR4(0, -1,-1,-1)
          - HR4(0,0, -1,-1)
          - HR4(0,0,0, -1)
          - HR4(0,0,0,1)
          - HR4(0,0,1, -1)
          - HR4(0,1, -1,-1);
      }
    }
    // nw > 4 endif
  }
  // (n1,n2) = (0,1) or (-1,1) endif
  //************

  // (n1,n2) = (-1,0) or (-1,1)
  if (    ( (n1 == -1) && (n2 == 0) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,-1) =
       + 8.2246703342411321e-01
       - 6.9314718055994530e-01*HR1(-1)
       + 5.0000000000000000e-01*HR1(-1)*HR1(-1)
       + HR1( -1)*HR1(1)
       - 6.9314718055994530e-01*HR1(1)
       - HR2( -1,1);
    if ( nw > 2 ){
      HY3(0,0,-1) =
        + 9.0154267736969571e-01
        - 8.2246703342411321e-01*HR1(-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)
        - 8.2246703342411321e-01*HR1(1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)
        + HR1(1) *HR2(-1,1)
        + HR3( -1,-1,1)
        - HR3( -1,1,1);
      HY3(0,-1,-1) =
        + 1.5025711289494928e-01
        - 2.4022650695910071e-01*HR1(-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)
        + HR1( -1)*HR2(-1,1)
        - 2.4022650695910071e-01*HR1(1)
        - 6.9314718055994530e-01*HR2(-1,1)
        - HR3( -1,-1,1);
    }

    if ( nw > 3 ){
      HY4(0,0,0,-1) =
        + 9.4703282949724591e-01
        - 9.0154267736969571e-01*HR1(-1)
        + 4.1123351671205660e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 8.2246703342411321e-01*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        - 9.0154267736969571e-01*HR1(1)
        + 4.1123351671205660e-01*HR1(1)*HR1(1)
        - 1.1552453009332421e-01*HR1(1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(-1,1)
        - HR1(1) *HR3(-1,-1,1)
        + HR1(1) *HR3(-1,1,1)
        - HR4( -1,-1,-1,1)
        + HR4( -1,-1,1,1)
        - HR4( -1,1,1,1);
      HY4(0,0,-1,-1) =
        + 8.7785671568655302e-02
        - 1.5025711289494928e-01*HR1(-1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
        - HR1( -1)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR3(-1,-1,1)
        + HR1( -1)*HR3(-1,1,1)
        - 1.5025711289494928e-01*HR1(1)
        + 1.2011325347955035e-01*HR1(1)*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
        + HR1(1) *HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR4(-1,-1,-1,1)
        - HR4( -1,-1,1,1);
      HY4(0,-1,-1,-1) =
        + 2.3752366322618485e-02
        - 5.5504108664821579e-02*HR1(-1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR3(-1,-1,1)
        - 5.5504108664821579e-02*HR1(1)
        - 2.4022650695910071e-01*HR2(-1,1)
        - 6.9314718055994530e-01*HR3(-1,-1,1)
        - HR4( -1,-1,-1,1);
    }
    // nw > 3 endif

    if ( nw > 4 ){
      HY5(0,0,0,0,-1) =
        + 9.7211977044690930e-01
        - 9.4703282949724591e-01*HR1(-1)
        + 4.5077133868484785e-01*HR1(-1)*HR1(-1)
        - 1.3707783890401886e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 4.1123351671205660e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 9.0154267736969571e-01*HR1(-1)*HR1(1)
        - 4.1123351671205660e-01*HR1(-1)*HR1(1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(1)*HR1(1)*HR1(1)*HR1(1)
        - 9.4703282949724591e-01*HR1(1)
        + 4.5077133868484785e-01*HR1(1)*HR1(1)
        - 1.3707783890401886e-01*HR1(1)*HR1(1)*HR1(1)
        + 2.8881132523331054e-02*HR1(1)*HR1(1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(1)*HR1(1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,1,1)
        + HR1(1) *HR4(-1,-1,-1,1)
        - HR1(1) *HR4(-1,-1,1,1)
        + HR1(1) *HR4(-1,1,1,1)
        + HR5( -1,-1,-1,-1,1)
        - HR5( -1,-1,-1,1,1)
        + HR5( -1,-1,1,1,1)
        - HR5( -1,1,1,1,1);
      HY5(0,0,0,-1,-1) =
        + 4.8936397049969063e-02
        - 8.7785671568655302e-02*HR1(-1)
        + 7.5128556447474642e-02*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 1.5025711289494928e-01*HR1(-1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(-1,1,1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(-1,-1,1,1)
        + HR1( -1)*HR4(-1,1,1,1)
        - 8.7785671568655302e-02*HR1(1)
        + 7.5128556447474642e-02*HR1(1)*HR1(1)
        - 4.0037751159850118e-02*HR1(1)*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + HR1(1) *HR4(-1,-1,1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,1,1)
        - 6.9314718055994530e-01*HR4(-1,1,1,1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        - HR5( -1,-1,1,1,1);
      HY5(0,0,-1,0,-1) =
        + 9.2748467341632644e-02
        - 1.6265466739742008e-01*HR1(-1)
        + 1.3478823976576390e-01*HR1(-1)*HR1(-1)
        - 1.3707783890401886e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 4.1123351671205660e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        + 2.6957647953152780e-01*HR1(-1)*HR1(1)
        - 4.1123351671205660e-01*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(-1,1,1,1)
        - 1.6265466739742008e-01*HR1(1)
        + 1.3478823976576390e-01*HR1(1)*HR1(1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        + HR1(1) *HR1(1)*HR3(-1,-1,1)
        + 8.2246703342411321e-01*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR2(-1,1)*HR2(-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,1,1)
        + 4.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,1,1)
        + HR2( -1,1)*HR3(-1,1,1)
        + 8.2246703342411321e-01*HR3(-1,-1,1)
        - 8.2246703342411321e-01*HR3(-1,1,1)
        + 2.0794415416798359e+00*HR4(-1,-1,-1,1)
        - 2.0794415416798359e+00*HR4(-1,-1,1,1)
        + 2.0794415416798359e+00*HR4(-1,1,1,1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        - HR5( -1,-1,1,-1,1)
        - HR5( -1,1,-1,1,1);
      HY5(0,0,-1,-1,-1) =
        + 9.6015684431298325e-03
        - 2.3752366322618485e-02*HR1(-1)
        + 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        + 5.5504108664821579e-02*HR1(-1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(-1,-1,1,1)
        - 2.3752366322618485e-02*HR1(1)
        + 2.7752054332410789e-02*HR1(1)*HR1(1)
        + 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + HR1(1) *HR4(-1,-1,-1,1)
        + 2.4022650695910071e-01*HR3(-1,-1,1)
        - 2.4022650695910071e-01*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,1,1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,-1,1,1);
      HY5(0,-1,0,-1,-1) =
        + 1.3531263989594243e-02
        - 3.2893195194356041e-02*HR1(-1)
        + 7.5128556447474642e-02*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(-1)*HR3(-1,1,1)
        + 1.5025711289494928e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(-1,1,1)
        + 4.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        - 3.2893195194356041e-02*HR1(1)
        - 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - 1.5025711289494928e-01*HR2(-1,1)
        + 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        + HR2( -1,1)*HR3(-1,-1,1)
        - 4.8045301391820142e-01*HR3(-1,-1,1)
        + 4.8045301391820142e-01*HR3(-1,1,1)
        - 2.7725887222397812e+00*HR4(-1,-1,-1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,1,1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,1,-1,1);
       HY5(0,-1,-1,-1,-1) =
        + 3.1350096016808622e-03
        - 9.6181291076284771e-03*HR1(-1)
        + 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.5504108664821579e-02*HR1(-1)*HR1(1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - 9.6181291076284771e-03*HR1(1)
        - 5.5504108664821579e-02*HR2(-1,1)
        - 2.4022650695910071e-01*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - HR5( -1,-1,-1,-1,1);
    }
    // nw > 4 endif
  }
  // (n1,n2) = (-1,0) or (-1,1) endif

  // (n1,n2) = (-1,1) -- completion
  if ( (n1 == -1) && (n2 == 1) ){
    HY2(-1,1) =
      + 5.8224052646501250e-01
      + 6.9314718055994530e-01*HR1(-1)
      - 5.0000000000000000e-01*HR1(-1)*HR1(-1)
      + HR1( -1)*HR1(0)
      - HR2(0, -1);
    if (r < 0.0){
      Hi2(-1,1) =
        - HR1( -1);
    }
    if ( nw > 2 ){
      HY3(0,-1,1) =
        + 2.4307035167006157e-01
        - 5.8224052646501250e-01*HR1(-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
        - HR1( -1)*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)
        - HR1( -1)*HR2(-1,1)
        + HR1( -1)*HR2(0,-1)
        + HR1(0) *HR2(-1,1)
        - 5.8224052646501250e-01*HR1(1)
        + HR1(1) *HR2(0,-1)
        + 6.9314718055994530e-01*HR2(-1,1)
        + HR3( -1,-1,1)
        - HR3(0, -1,-1)
        - HR3(0, -1,1);
      HY3(0,1,-1) =
        + 5.0821521280468485e-01
        + 1.0626935403832139e+00*HR1(-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)
        - HR1( -1)*HR2(-1,1)
        - HR1( -1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)
        + 1.0626935403832139e+00*HR1(1)
        - HR1(1) *HR2(0,-1)
        + 6.9314718055994530e-01*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(0,-1)
        - 6.9314718055994530e-01*HR2(0,1)
        + HR3( -1,-1,1)
        + 2.0000000000000000e+00*HR3(0,-1,-1)
        + HR3(0, -1,1)
        + HR3(0,1, -1);
      HY3(-1,-1,1) =
        + 9.4753004230127705e-02
        - 5.8224052646501250e-01*HR1(-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
        + HR1( -1)*HR2(0,-1)
        - HR3(0, -1,-1);
      HY3(-1,1,1) =
        + 5.3721319360804020e-01
        - 2.4022650695910071e-01*HR1(-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)
        + HR1(0) *HR2(0,-1)
        + 6.9314718055994530e-01*HR2(0,-1)
        - HR3(0, -1,-1)
        - HR3(0,0, -1);
      if (r < 0.0){
        HY3(-1,1,1) = HY3(-1,1,1)
          + 4.9348022005446793e+00*HR1(-1);
        Hi3(0,-1,1) =
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)
          + HR1( -1)*HR1(1)
          - HR2( -1,1);
        Hi3(0,1,-1) =
          - 6.9314718055994530e-01*HR1(-1)
          - 6.9314718055994530e-01*HR1(1);
        Hi3(-1,-1,1) =
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1);
        Hi3(-1,1,1) =
          + 6.9314718055994530e-01*HR1(-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)
          + HR1( -1)*HR1(0)
          - HR2(0, -1);
      }
    }

    if ( nw > 3 ){
      HY4(0,0,-1,1) =
        + 1.1787599965050932e-01
        - 2.4307035167006157e-01*HR1(-1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 5.8224052646501250e-01*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
        + HR1( -1)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR3(-1,-1,1)
        - HR1( -1)*HR3(-1,1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,-1,1)
        - HR1(0) *HR1(1)*HR2(-1,1)
        - HR1(0) *HR3(-1,-1,1)
        + HR1(0) *HR3(-1,1,1)
        - 2.4307035167006157e-01*HR1(1)
        + 2.9112026323250625e-01*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
        - HR1(1) *HR3(-1,-1,1)
        + HR1(1) *HR3(0,-1,-1)
        + HR1(1) *HR3(0,-1,1)
        - 6.9314718055994530e-01*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR3(-1,1,1)
        - 2.0000000000000000e+00*HR4(-1,-1,-1,1)
        + HR4( -1,-1,1,1)
        - HR4(0, -1,-1,-1)
        - HR4(0, -1,-1,1)
        - HR4(0, -1,1,-1)
        - HR4(0, -1,1,1);
      HY4(0,0,1,-1) =
        + 1.7284527823898438e-01
        - 5.0821521280468485e-01*HR1(-1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
        - 1.0626935403832139e+00*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
        + HR1( -1)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(0,1)
        + HR1( -1)*HR3(-1,-1,1)
        - HR1( -1)*HR3(-1,1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
        - HR1( -1)*HR3(0,-1,1)
        - HR1( -1)*HR3(0,1,-1)
        - 3.4657359027997265e-01*HR1(0)*HR1(1)*HR1(1)
        - 5.0821521280468485e-01*HR1(1)
        - 5.3134677019160696e-01*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(1)*HR2(0,1)
        - HR1(1) *HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
        - HR1(1) *HR3(0,-1,1)
        - HR1(1) *HR3(0,1,-1)
        - 6.9314718055994530e-01*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR3(0,1,1)
        - 2.0000000000000000e+00*HR4(-1,-1,-1,1)
        + HR4( -1,-1,1,1)
        + 3.0000000000000000e+00*HR4(0,-1,-1,-1)
        + 2.0000000000000000e+00*HR4(0,-1,-1,1)
        + 2.0000000000000000e+00*HR4(0,-1,1,-1)
        + HR4(0, -1,1,1)
        + 2.0000000000000000e+00*HR4(0,1,-1,-1)
        + HR4(0,1, -1,1)
        + HR4(0,1,1, -1);
      HY4(0,-1,0,1) =
        + 2.0293560632083841e-01
        - 3.8889584616810632e-01*HR1(-1)
        + 8.2246703342411321e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        - HR1( -1)*HR1(0)*HR2(-1,1)
        + 1.6449340668482264e+00*HR1(-1)*HR1(1)
        - HR1( -1)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR3(-1,1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,1,-1)
        + HR1(0) *HR1(1)*HR2(-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR3(-1,1,1)
        - 3.8889584616810632e-01*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR3(-1,-1,1)
        + HR1(1) *HR3(0,-1,-1)
        + HR1(1) *HR3(0,1,-1)
        - 1.6449340668482264e+00*HR2(-1,1)
        - 5.0000000000000000e-01*HR2(-1,1)*HR2(-1,1)
        + HR2( -1,1)*HR2(0,-1)
        + HR2( -1,1)*HR2(0,1)
        + 1.3862943611198906e+00*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR3(-1,1,1)
        + 4.0000000000000000e+00*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR4(-1,-1,1,1)
        - HR4(0, -1,-1,-1)
        - HR4(0, -1,-1,1)
        - HR4(0,1, -1,-1)
        - HR4(0,1, -1,1);
      HY4(0,-1,-1,1) =
        + 3.4159126166513913e-02
        - 9.4753004230127705e-02*HR1(-1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR2(-1,1)
        + 5.8224052646501250e-01*HR1(-1)*HR1(1)
        - HR1( -1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR3(-1,-1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1(0) *HR3(-1,-1,1)
        - 9.4753004230127705e-02*HR1(1)
        + HR1(1) *HR3(0,-1,-1)
        - 5.8224052646501250e-01*HR2(-1,1)
        + HR2( -1,1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR3(-1,-1,1)
        + HR4( -1,-1,-1,1)
        - HR4(0, -1,-1,-1)
        - HR4(0, -1,-1,1);
      HY4(0,-1,1,-1) =
        + 5.4653052738263652e-02
        - 2.1407237086670622e-01*HR1(-1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
        - 1.0626935403832139e+00*HR1(-1)*HR1(1)
        + HR1( -1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        - HR1( -1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
        - 2.1407237086670622e-01*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
        - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
        + 1.0626935403832139e+00*HR2(-1,1)
        - HR2( -1,1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR3(0,-1,1)
        + HR4( -1,-1,-1,1)
        + 3.0000000000000000e+00*HR4(0,-1,-1,-1)
        + 2.0000000000000000e+00*HR4(0,-1,-1,1)
        + HR4(0, -1,1,-1);
      HY4(0,1,-1,-1) =
        + 1.1412342741606084e-01
        + 4.7533770109129867e-01*HR1(-1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(0)
        - 2.4022650695910071e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        - HR1( -1)*HR3(-1,-1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR1(0)*HR1(1)
        + 4.7533770109129867e-01*HR1(1)
        - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
        + HR1(1) *HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR2(-1,1)
        - 2.4022650695910071e-01*HR2(0,-1)
        - 2.4022650695910071e-01*HR2(0,1)
        + 6.9314718055994530e-01*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR3(0,1,-1)
        + HR4( -1,-1,-1,1)
        - 3.0000000000000000e+00*HR4(0,-1,-1,-1)
        - HR4(0, -1,-1,1)
        - HR4(0, -1,1,-1)
        - HR4(0,1, -1,-1);
      HY4(0,-1,1,1) =
        + 9.3097125991768577e-02
        - 5.3721319360804020e-01*HR1(-1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
        + HR1( -1)*HR1(0)*HR2(-1,1)
        - HR1( -1)*HR1(0)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        + HR1( -1)*HR3(-1,-1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(-1,1)
        - HR1(0) *HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
        - HR1(0) *HR3(-1,-1,1)
        + HR1(0) *HR3(0,-1,-1)
        + HR1(0) *HR3(0,-1,1)
        - 5.3721319360804020e-01*HR1(1)
        - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
        + HR1(1) *HR3(0,-1,-1)
        + HR1(1) *HR3(0,0,-1)
        - 2.4022650695910071e-01*HR2(-1,1)
        - 6.9314718055994530e-01*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR3(0,-1,1)
        - HR4( -1,-1,-1,1)
        - 2.0000000000000000e+00*HR4(0,-1,-1,-1)
        - HR4(0, -1,-1,1)
        - HR4(0, -1,1,-1)
        - HR4(0,0, -1,-1)
        - HR4(0,0, -1,1);
      HY4(0,1,-1,1) =
        + 1.9355535381306524e-01
        + 1.4780047665430420e+00*HR1(-1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.8224052646501250e-01*HR1(-1)*HR1(0)
        + HR1( -1)*HR1(0)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR2(0,-1)
        - 5.8224052646501250e-01*HR1(-1)*HR1(1)
        + HR1( -1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        + HR1( -1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR3(0,0,-1)
        + 5.8224052646501250e-01*HR1(0)*HR1(1)
        + HR1(0) *HR1(1)*HR2(0,-1)
        - HR1(0) *HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR3(0,-1,-1)
        - HR1(0) *HR3(0,-1,1)
        - HR1(0) *HR3(0,1,-1)
        + 1.4780047665430420e+00*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
        - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR3(0,0,-1)
        + 5.8224052646501250e-01*HR2(-1,1)
        - HR2( -1,1)*HR2(0,-1)
        - 5.8224052646501250e-01*HR2(0,-1)
        + 5.0000000000000000e-01*HR2(0,-1)*HR2(0,-1)
        + HR2(0, -1)*HR2(0,1)
        - 5.8224052646501250e-01*HR2(0,1)
        - 6.9314718055994530e-01*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR3(0,1,-1)
        - HR4( -1,-1,-1,1)
        + 4.0000000000000000e+00*HR4(0,-1,-1,-1)
        + 2.0000000000000000e+00*HR4(0,-1,-1,1)
        - HR4(0, -1,0,1)
        + HR4(0, -1,1,-1)
        + 2.0000000000000000e+00*HR4(0,0,-1,-1)
        + HR4(0,1, -1,-1);
      HY4(0,1,1,-1) =
        + 4.3369237704895519e-01
        - 1.1073038989294665e+00*HR1(-1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 1.0626935403832139e+00*HR1(-1)*HR1(0)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
        + 1.0626935403832139e+00*HR1(-1)*HR1(1)
        - HR1( -1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR3(-1,-1,1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,0,-1)
        - 3.4657359027997265e-01*HR1(0)*HR1(0)*HR1(1)
        - 1.0626935403832139e+00*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(0)*HR2(0,1)
        - 1.1073038989294665e+00*HR1(1)
        + HR1(1) *HR3(0,-1,-1)
        + HR1(1) *HR3(0,0,-1)
        - 1.0626935403832139e+00*HR2(-1,1)
        + HR2( -1,1)*HR2(0,-1)
        + 1.0626935403832139e+00*HR2(0,-1)
        - 5.0000000000000000e-01*HR2(0,-1)*HR2(0,-1)
        - HR2(0, -1)*HR2(0,1)
        + 1.0626935403832139e+00*HR2(0,1)
        - 6.9314718055994530e-01*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR3(0,0,-1)
        - 6.9314718055994530e-01*HR3(0,0,1)
        - 6.9314718055994530e-01*HR3(0,1,-1)
        - HR4( -1,-1,-1,1)
        - HR4(0, -1,-1,1)
        + HR4(0, -1,0,1)
        + HR4(0,0, -1,1)
        + HR4(0,0,1, -1)
        + HR4(0,1, -1,-1);
      HY4(-1,-1,-1,1) =
        + 1.4134237214990008e-02
        - 9.4753004230127705e-02*HR1(-1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + HR1( -1)*HR3(0,-1,-1)
        - HR4(0, -1,-1,-1);
      HY4(-1,-1,1,1) =
        + 4.0758239159309251e-02
        - 5.3721319360804020e-01*HR1(-1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - HR1( -1)*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
        + HR1( -1)*HR3(0,-1,-1)
        + HR1( -1)*HR3(0,0,-1)
        + HR1(0) *HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR4(0,-1,-1,-1)
        - HR4(0,0, -1,-1);
      HY4(-1,1,1,1) =
        + 5.1747906167389938e-01
        + 5.5504108664821579e-02*HR1(-1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 2.4022650695910071e-01*HR1(-1)*HR1(0)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR2(0,-1)
        + HR1(0) *HR3(0,-1,-1)
        + HR1(0) *HR3(0,0,-1)
        - 2.4022650695910071e-01*HR2(0,-1)
        + 6.9314718055994530e-01*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR3(0,0,-1)
        - HR4(0, -1,-1,-1)
        - HR4(0,0, -1,-1)
        - HR4(0,0,0, -1);
      if (r < 0.0){
        HY4(0,-1,1,1) = HY4(0,-1,1,1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)
          - 4.9348022005446793e+00*HR1(-1)*HR1(1)
          + 4.9348022005446793e+00*HR2(-1,1);
        HY4(0,1,1,-1) = HY4(0,1,1,-1)
          + 3.4205442319285582e+00*HR1(-1)
          + 3.4205442319285582e+00*HR1(1);
        HY4(-1,-1,1,1) = HY4(-1,-1,1,1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1);
        HY4(-1,1,1,1) = HY4(-1,1,1,1)
          - 3.4205442319285582e+00*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)
          - 4.9348022005446793e+00*HR1(-1)*HR1(0)
          + 4.9348022005446793e+00*HR2(0,-1);
        Hi4(0,0,-1,1) =
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)
          + HR1(1) *HR2(-1,1)
          + HR3( -1,-1,1)
          - HR3( -1,1,1);
        Hi4(0,0,1,-1) =
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
          + 6.9314718055994530e-01*HR1(-1)*HR1(1)
          + 3.4657359027997265e-01*HR1(1)*HR1(1);
        Hi4(0,-1,0,1) =
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          + HR1( -1)*HR2(-1,1)
          - HR1(1) *HR2(-1,1)
          - 2.0000000000000000e+00*HR3(-1,-1,1)
          + 2.0000000000000000e+00*HR3(-1,1,1);
        Hi4(0,-1,-1,1) =
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          + HR1( -1)*HR2(-1,1)
          - HR3( -1,-1,1);
        Hi4(0,-1,1,-1) =
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
          + 6.9314718055994530e-01*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR2(-1,1);
        Hi4(0,1,-1,-1) =
          - 2.4022650695910071e-01*HR1(-1)
          - 2.4022650695910071e-01*HR1(1);
        Hi4(0,-1,1,1) =
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          - HR1( -1)*HR1(0)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR1(1)
          - HR1( -1)*HR2(-1,1)
          + HR1( -1)*HR2(0,-1)
          + HR1(0) *HR2(-1,1)
          + HR1(1) *HR2(0,-1)
          + 6.9314718055994530e-01*HR2(-1,1)
          + HR3( -1,-1,1)
          - HR3(0, -1,-1)
          - HR3(0, -1,1);
        Hi4(0,1,-1,1) =
          - 5.8224052646501250e-01*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)
          - HR1( -1)*HR2(-1,1)
          - HR1( -1)*HR2(0,-1)
          - 5.8224052646501250e-01*HR1(1)
          - HR1(1) *HR2(0,-1)
          + HR3( -1,-1,1)
          + 2.0000000000000000e+00*HR3(0,-1,-1)
          + HR3(0, -1,1)
          + HR3(0,1, -1);
        Hi4(0,1,1,-1) =
          + 1.0626935403832139e+00*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
          + 6.9314718055994530e-01*HR1(-1)*HR1(0)
          - 6.9314718055994530e-01*HR1(-1)*HR1(1)
          + 6.9314718055994530e-01*HR1(0)*HR1(1)
          + 1.0626935403832139e+00*HR1(1)
          + 6.9314718055994530e-01*HR2(-1,1)
          - 6.9314718055994530e-01*HR2(0,-1)
          - 6.9314718055994530e-01*HR2(0,1);
        Hi4(-1,-1,-1,1) =
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1);
        Hi4(-1,-1,1,1) =
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
          + HR1( -1)*HR2(0,-1)
          - HR3(0, -1,-1);
        Hi4(-1,1,1,1) =
          + 1.4047075598891257e+00*HR1(-1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)
          - 6.9314718055994530e-01*HR1(-1)*HR1(0)
          - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)
          + HR1(0) *HR2(0,-1)
          + 6.9314718055994530e-01*HR2(0,-1)
          - HR3(0, -1,-1)
          - HR3(0,0, -1);
      }
    }
    // nw > 3 endif

    if ( nw > 4 ){
      HY5(-1,-1,-1,-1,1) =
        + 1.8016537870380179e-03
        - 1.4134237214990008e-02*HR1(-1)
        + 4.7376502115063852e-02*HR1(-1)*HR1(-1)
        - 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        - HR5(0, -1,-1,-1,-1);
      HY5(-1,-1,-1,1,1) =
        + 3.8760673146652637e-03
        - 4.0758239159309251e-02*HR1(-1)
        + 2.6860659680402010e-01*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - HR5(0,0, -1,-1,-1);
      HY5(-1,-1,1,-1,1) =
        + 6.2154684604081354e-03
        - 8.7985537010508960e-02*HR1(-1)
        - 7.3900238327152102e-01*HR1(-1)*HR1(-1)
        + 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        + HR2(0, -1)*HR3(0,-1,-1)
        - 5.8224052646501250e-01*HR3(0,-1,-1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - HR5(0, -1,0,-1,-1);
      HY5(-1,-1,1,1,1) =
        + 1.8530786065466613e-02
        - 5.1747906167389938e-01*HR1(-1)
        - 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,0,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1( -1)*HR4(0,0,0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,0,0, -1,-1);
      HY5(-1,1,-1,1,1) =
        + 3.8880058841843904e-02
        + 1.9248049955307152e+00*HR1(-1)
        - 2.6860659680402010e-01*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 5.3721319360804020e-01*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,0,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,0,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,0,-1)
        + HR1(0) *HR1(0)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR2(0,-1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(0)*HR3(0,-1,-1)
        - 4.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,0,-1,-1)
        - 5.3721319360804020e-01*HR2(0,-1)
        - 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        + HR2(0, -1)*HR3(0,0,-1)
        + 4.8045301391820142e-01*HR3(0,-1,-1)
        - 2.7725887222397812e+00*HR4(0,-1,-1,-1)
        - 1.3862943611198906e+00*HR4(0,0,-1,-1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + HR5(0, -1,0,-1,-1)
        + 7.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,0, -1,0,-1);
      HY5(-1,1,1,1,1) =
        + 5.0840057924226870e-01
        - 9.6181291076284771e-03*HR1(-1)
        + 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 5.5504108664821579e-02*HR1(-1)*HR1(0)
        - 1.2011325347955035e-01*HR1(-1)*HR1(0)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(0)*HR1(0)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,0,-1)
        + 2.4022650695910071e-01*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,0,-1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,0,-1,-1)
        + HR1(0) *HR4(0,0,0,-1)
        + 5.5504108664821579e-02*HR2(0,-1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,0,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,0,-1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0,0, -1,-1,-1)
        - HR5(0,0,0, -1,-1)
        - HR5(0,0,0,0, -1);
      HY5(0,-1,-1,-1,1) =
        + 4.1914400448554060e-03
        - 1.4134237214990008e-02*HR1(-1)
        + 4.7376502115063852e-02*HR1(-1)*HR1(-1)
        - 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + 9.4753004230127705e-02*HR1(-1)*HR1(1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1(0) *HR4(-1,-1,-1,1)
        - 1.4134237214990008e-02*HR1(1)
        + HR1(1) *HR4(0,-1,-1,-1)
        - 9.4753004230127705e-02*HR2(-1,1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(-1,-1,1)
        - 5.8224052646501250e-01*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + HR5( -1,-1,-1,-1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1);
      HY5(0,-1,-1,0,1) =
        + 3.0172237496701167e-02
        - 7.7340900566758219e-02*HR1(-1)
        + 1.9444792308405316e-01*HR1(-1)*HR1(-1)
        - 2.7415567780803773e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + 3.8889584616810632e-01*HR1(-1)*HR1(1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        + 1.6449340668482264e+00*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - HR1( -1)*HR2(-1,1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,1,-1,-1)
        - HR1(0) *HR1(1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR2(-1,1)*HR2(-1,1)
        - 7.7340900566758219e-02*HR1(1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,1,-1,-1)
        - 3.8889584616810632e-01*HR2(-1,1)
        + 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        + 2.0000000000000000e+00*HR2(-1,1)*HR3(-1,-1,1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + HR2( -1,1)*HR3(0,1,-1)
        + HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0,1) *HR3(-1,-1,1)
        - 1.6449340668482264e+00*HR3(-1,-1,1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - 6.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        - 3.0000000000000000e+00*HR5(-1,-1,1,-1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0,1, -1,-1,-1)
        - HR5(0,1, -1,-1,1);
      HY5(0,-1,-1,1,-1) =
        + 5.9459097989450212e-03
        - 2.3275066086727564e-02*HR1(-1)
        + 1.0703618543335311e-01*HR1(-1)*HR1(-1)
        + 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + 2.1407237086670622e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        - 1.0626935403832139e+00*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - 2.3275066086727564e-02*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 2.1407237086670622e-01*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        - HR2(0, -1)*HR3(-1,-1,1)
        + 1.0626935403832139e+00*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + HR5( -1,-1,-1,-1,1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + HR5(0, -1,-1,1,-1);
      HY5(0,-1,-1,1,1) =
        + 8.7734377821481916e-03
        - 4.0758239159309251e-02*HR1(-1)
        + 2.6860659680402010e-01*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        + 5.3721319360804020e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,-1,1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - HR1(0) *HR4(-1,-1,-1,1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        - 4.0758239159309251e-02*HR1(1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,0,-1,-1)
        - 5.3721319360804020e-01*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + HR2( -1,1)*HR3(0,0,-1)
        - 2.4022650695910071e-01*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - HR5( -1,-1,-1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0,0, -1,-1,-1)
        - HR5(0,0, -1,-1,1);
      HY5(0,-1,0,-1,1) =
        + 1.7042475614121991e-02
        - 4.5512223866526096e-02*HR1(-1)
        + 1.2153517583503078e-01*HR1(-1)*HR1(-1)
        - 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(-1,1,1)
        + 2.4307035167006157e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,-1,1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(-1,1,1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR2(-1,1)*HR2(-1,1)
        + 4.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,1,1)
        - 4.5512223866526096e-02*HR1(1)
        - 5.8224052646501250e-01*HR1(1)*HR2(-1,1)
        + HR1(1) *HR2(-1,1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        + 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,1,-1)
        - 2.4307035167006157e-01*HR2(-1,1)
        - 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        - HR2( -1,1)*HR3(-1,-1,1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + HR2( -1,1)*HR3(0,-1,1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR2(0,-1)*HR3(-1,1,1)
        - 1.1644810529300250e+00*HR3(-1,-1,1)
        + 1.1644810529300250e+00*HR3(-1,1,1)
        + 2.7725887222397812e+00*HR4(-1,-1,-1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,1,1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,1,-1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,1,-1,-1)
        - HR5(0, -1,1,-1,1);
      HY5(0,-1,0,1,-1) =
        + 2.2495758621687517e-02
        - 6.9368034302854577e-02*HR1(-1)
        + 2.5410760640234242e-01*HR1(-1)*HR1(-1)
        + 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        + HR1( -1)*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(-1)*HR3(-1,1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + 5.0821521280468485e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(1)*HR3(0,-1,1)
        + HR1( -1)*HR1(1)*HR3(0,1,-1)
        - 1.0626935403832139e+00*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        + HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(-1,1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - HR1( -1)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(-1,1,1)
        - 6.9368034302854577e-02*HR1(1)
        + 1.0626935403832139e+00*HR1(1)*HR2(-1,1)
        - HR1(1) *HR2(-1,1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - HR1(1) *HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        - 5.0821521280468485e-01*HR2(-1,1)
        - 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,1)
        - HR2( -1,1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        - HR2( -1,1)*HR3(0,-1,1)
        - HR2( -1,1)*HR3(0,1,-1)
        - 2.0000000000000000e+00*HR2(0,-1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(-1,1,1)
        + 2.1253870807664278e+00*HR3(-1,-1,1)
        - 2.1253870807664278e+00*HR3(-1,1,1)
        + 2.7725887222397812e+00*HR4(-1,-1,-1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,1,1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,1,-1,1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + HR5(0, -1,-1,1,-1)
        + HR5(0, -1,1,-1,-1)
        + HR5(0, -1,1,-1,1)
        + 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,1,-1,-1,1)
        + HR5(0,1, -1,1,-1);
      HY5(0,-1,0,1,1) =
        + 3.0833054551948363e-02
        - 1.1285749644390297e-01*HR1(-1)
        + 6.0102845157979714e-01*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        - HR1( -1)*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(-1,1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,1,-1)
        + 1.2020569031595942e+00*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        + 4.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1( -1)*HR4(0,0,1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(-1,1)
        - HR1(0) *HR1(0)*HR3(-1,-1,1)
        + HR1(0) *HR1(0)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,-1,1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR1(1)*HR3(0,1,-1)
        + 5.0000000000000000e-01*HR1(0)*HR2(-1,1)*HR2(-1,1)
        - HR1(0) *HR2(-1,1)*HR2(0,-1)
        - HR1(0) *HR2(-1,1)*HR2(0,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(-1,1,1)
        - 4.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,1,1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,1,-1,-1)
        + HR1(0) *HR4(0,1,-1,1)
        - 1.1285749644390297e-01*HR1(1)
        - 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,0,-1,-1)
        + HR1(1) *HR4(0,0,1,-1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        - 1.2020569031595942e+00*HR2(-1,1)
        + 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,1)
        + HR2( -1,1)*HR3(-1,-1,1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + HR2( -1,1)*HR3(0,0,-1)
        + HR2( -1,1)*HR3(0,0,1)
        + HR2( -1,1)*HR3(0,1,-1)
        - 4.8045301391820142e-01*HR3(-1,-1,1)
        + 4.8045301391820142e-01*HR3(-1,1,1)
        - 2.7725887222397812e+00*HR4(-1,-1,-1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,1,1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0,0, -1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - HR5(0,0,1, -1,-1)
        - HR5(0,0,1, -1,1)
        - 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,1,-1,-1,1)
        - HR5(0,1, -1,1,-1);
      HY5(0,-1,1,-1,-1) =
        + 9.4133341974174110e-03
        - 5.0916764064292634e-02*HR1(-1)
        - 2.3766885054564933e-01*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR1(0)*HR1(1)
        - 4.7533770109129867e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + 2.4022650695910071e-01*HR1(0)*HR2(-1,1)
        - 5.0916764064292634e-02*HR1(1)
        + 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + 4.7533770109129867e-01*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR3(-1,-1,1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + HR5( -1,-1,-1,-1,1)
        - 6.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,1,-1,-1);
      HY5(0,-1,1,-1,1) =
        + 1.3833955759762555e-02
        - 8.7985537010508960e-02*HR1(-1)
        - 7.3900238327152102e-01*HR1(-1)*HR1(-1)
        + 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR1(-1)*HR1(0)*HR1(1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        - 1.4780047665430420e+00*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR2(-1,1)*HR2(0,-1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,-1)
        + 5.8224052646501250e-01*HR1(0)*HR2(-1,1)
        + HR1(0) *HR2(-1,1)*HR2(0,-1)
        - HR1(0) *HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,1)
        - HR1(0) *HR4(0,-1,1,-1)
        - 8.7985537010508960e-02*HR1(1)
        + 5.8224052646501250e-01*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        - 4.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        + 1.4780047665430420e+00*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,0,-1)
        - HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0, -1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(0,-1,1)
        + 5.8224052646501250e-01*HR3(-1,-1,1)
        - 5.8224052646501250e-01*HR3(0,-1,-1)
        - 5.8224052646501250e-01*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        - 1.3862943611198906e+00*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - HR5( -1,-1,-1,-1,1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        + HR5(0, -1,1,-1,-1);
      HY5(0,-1,1,0,1) =
        + 7.6026642213084631e-02
        - 3.5228267839753708e-01*HR1(-1)
        - 1.7721476084810206e+00*HR1(-1)*HR1(-1)
        + 2.7415567780803773e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,1)
        + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,1)
        + HR1( -1)*HR1(-1)*HR3(0,1,-1)
        - 1.6449340668482264e+00*HR1(-1)*HR1(0)*HR1(1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + HR1( -1)*HR1(0)*HR3(0,-1,1)
        + HR1( -1)*HR1(0)*HR3(0,1,-1)
        - 3.5442952169620413e+00*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,1,-1)
        - 1.6449340668482264e+00*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        + HR1( -1)*HR2(-1,1)*HR2(0,-1)
        + HR1( -1)*HR2(-1,1)*HR2(0,1)
        + 1.6449340668482264e+00*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - HR1( -1)*HR4(0,-1,0,1)
        - HR1( -1)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        + HR1(0) *HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,-1)
        + HR1(0) *HR1(1)*HR3(0,-1,1)
        + HR1(0) *HR1(1)*HR3(0,1,-1)
        + 1.6449340668482264e+00*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR2(-1,1)*HR2(-1,1)
        + HR1(0) *HR2(-1,1)*HR2(0,-1)
        + HR1(0) *HR2(-1,1)*HR2(0,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,1,1)
        - HR1(0) *HR4(0,1,-1,-1)
        - HR1(0) *HR4(0,1,-1,1)
        - 3.5228267839753708e-01*HR1(1)
        + 1.6449340668482264e+00*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - 4.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - HR1(1) *HR4(0,-1,0,1)
        - HR1(1) *HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        + 3.5442952169620413e+00*HR2(-1,1)
        - 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,0,-1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,0,1)
        - 2.0000000000000000e+00*HR2(-1,1)*HR3(0,1,-1)
        - HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0, -1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(0,-1,1)
        - HR2(0,1) *HR3(-1,-1,1)
        + 1.6449340668482264e+00*HR3(-1,-1,1)
        - 1.6449340668482264e+00*HR3(0,-1,-1)
        - 1.6449340668482264e+00*HR3(0,-1,1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,1)
        - 1.3862943611198906e+00*HR4(0,-1,1,-1)
        - 1.3862943611198906e+00*HR4(0,-1,1,1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + 6.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        + 3.0000000000000000e+00*HR5(-1,-1,1,-1,1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + HR5(0, -1,-1,0,1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,0,-1,-1)
        + HR5(0, -1,0,1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,0,1,1)
        + 3.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        + HR5(0, -1,1,-1,1)
        + HR5(0, -1,1,0,1)
        + 2.0000000000000000e+00*HR5(0,-1,1,1,-1)
        + 2.0000000000000000e+00*HR5(0,0,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,0,-1,1,-1)
        + 4.0000000000000000e+00*HR5(0,0,-1,1,1)
        + 2.0000000000000000e+00*HR5(0,0,1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,0,1,-1,1)
        + 4.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,1,-1,-1,1)
        + HR5(0,1, -1,1,-1);
      HY5(0,-1,1,1,-1) =
        + 2.2801059128486651e-02
        - 2.0286579517988963e-01*HR1(-1)
        + 5.5365194946473328e-01*HR1(-1)*HR1(-1)
        - 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 1.0626935403832139e+00*HR1(-1)*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        + 1.1073038989294665e+00*HR1(-1)*HR1(1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,-1)
        + 1.0626935403832139e+00*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 1.0626935403832139e+00*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        - 1.0626935403832139e+00*HR1(0)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,-1,1)
        - 2.0286579517988963e-01*HR1(1)
        - 1.0626935403832139e+00*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,0,-1)
        - 1.1073038989294665e+00*HR2(-1,1)
        + HR2( -1,1)*HR3(0,-1,-1)
        + HR2( -1,1)*HR3(0,0,-1)
        + HR2(0, -1)*HR3(-1,-1,1)
        - HR2(0, -1)*HR3(0,-1,-1)
        - HR2(0, -1)*HR3(0,-1,1)
        - 1.0626935403832139e+00*HR3(-1,-1,1)
        + 1.0626935403832139e+00*HR3(0,-1,-1)
        + 1.0626935403832139e+00*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 1.3862943611198906e+00*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR4(0,0,-1,-1)
        - 6.9314718055994530e-01*HR4(0,0,-1,1)
        - HR5( -1,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + HR5(0, -1,-1,1,-1)
        + HR5(0, -1,0,-1,-1)
        + HR5(0, -1,0,-1,1)
        + HR5(0, -1,1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,0,-1,-1,1)
        + HR5(0,0, -1,1,-1);
      HY5(0,-1,1,1,1) =
        + 3.9984858137537496e-02
        - 5.1747906167389938e-01*HR1(-1)
        - 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,0,-1)
        - 5.5504108664821579e-02*HR1(-1)*HR1(1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1( -1)*HR4(0,0,0,-1)
        + 1.6666666666666666e-01*HR1(0)*HR1(0)*HR1(0)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR1(1)*HR3(0,0,-1)
        + 2.4022650695910071e-01*HR1(0)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,1)
        + HR1(0) *HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,-1,1,-1)
        + HR1(0) *HR4(0,0,-1,-1)
        + HR1(0) *HR4(0,0,-1,1)
        - 5.1747906167389938e-01*HR1(1)
        + 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,0,-1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,0,-1,-1)
        + HR1(1) *HR4(0,0,0,-1)
        + 5.5504108664821579e-02*HR2(-1,1)
        + 2.4022650695910071e-01*HR3(-1,-1,1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,-1)
        + 6.9314718055994530e-01*HR4(0,0,-1,1)
        + HR5( -1,-1,-1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0, -1,1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,1,-1)
        - HR5(0,0,0, -1,-1)
        - HR5(0,0,0, -1,1);
      HY5(0,0,-1,-1,1) =
        + 1.2444228784499648e-02
        - 3.4159126166513913e-02*HR1(-1)
        + 4.7376502115063852e-02*HR1(-1)*HR1(-1)
        - 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(-1,1,1)
        + 9.4753004230127705e-02*HR1(-1)*HR1(1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(-1,-1,1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        - HR1(0) *HR1(1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        + HR1(0) *HR4(-1,-1,1,1)
        - 3.4159126166513913e-02*HR1(1)
        + 4.7376502115063852e-02*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        + 5.8224052646501250e-01*HR1(1)*HR2(-1,1)
        - HR1(1) *HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - HR1(1) *HR4(-1,-1,-1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        - HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0, -1)*HR3(-1,1,1)
        + 5.8224052646501250e-01*HR3(-1,-1,1)
        - 5.8224052646501250e-01*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,-1,1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0, -1,-1,1,1);
      HY5(0,0,-1,0,1) =
        + 1.0679981350605469e-01
        - 2.0293560632083841e-01*HR1(-1)
        + 1.9444792308405316e-01*HR1(-1)*HR1(-1)
        - 2.7415567780803773e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(-1,1,1)
        + 3.8889584616810632e-01*HR1(-1)*HR1(1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(-1,1,1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,1,-1,-1)
        + HR1( -1)*HR4(0,1,-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(-1,1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(0)*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(-1,1,1,1)
        - 2.0293560632083841e-01*HR1(1)
        + 1.9444792308405316e-01*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        - HR1(1) *HR1(1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,1,-1)
        + 1.6449340668482264e+00*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(1)*HR2(-1,1)*HR2(-1,1)
        - HR1(1) *HR2(-1,1)*HR2(0,-1)
        - HR1(1) *HR2(-1,1)*HR2(0,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,1,1)
        - 4.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,1,-1,-1)
        + HR1(1) *HR4(0,1,-1,1)
        - HR2( -1,1)*HR3(-1,1,1)
        - HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0, -1)*HR3(-1,1,1)
        - HR2(0,1) *HR3(-1,-1,1)
        + HR2(0,1) *HR3(-1,1,1)
        + 1.6449340668482264e+00*HR3(-1,-1,1)
        - 1.6449340668482264e+00*HR3(-1,1,1)
        - 2.0794415416798359e+00*HR4(-1,-1,-1,1)
        + 2.0794415416798359e+00*HR4(-1,-1,1,1)
        - 2.0794415416798359e+00*HR4(-1,1,1,1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        + HR5( -1,-1,1,-1,1)
        + HR5( -1,1,-1,1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - HR5(0,1, -1,-1,-1)
        - HR5(0,1, -1,-1,1)
        - HR5(0,1, -1,1,-1)
        - HR5(0,1, -1,1,1);
      HY5(0,0,-1,1,-1) =
        + 1.6991592326175436e-02
        - 5.4653052738263652e-02*HR1(-1)
        + 1.0703618543335311e-01*HR1(-1)*HR1(-1)
        + 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 2.1407237086670622e-01*HR1(-1)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,1)
        - HR1( -1)*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,1,1)
        - 5.4653052738263652e-02*HR1(1)
        + 1.0703618543335311e-01*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        + HR1(1) *HR1(1)*HR3(0,-1,-1)
        - 1.0626935403832139e+00*HR1(1)*HR2(-1,1)
        + HR1(1) *HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        - HR1(1) *HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,1)
        - HR1(1) *HR4(0,-1,1,-1)
        + HR2(0, -1)*HR3(-1,-1,1)
        - HR2(0, -1)*HR3(-1,1,1)
        - 1.0626935403832139e+00*HR3(-1,-1,1)
        + 1.0626935403832139e+00*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,1,1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,1,1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,-1,1,1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,1)
        + 2.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        + HR5(0, -1,1,-1,1)
        + HR5(0, -1,1,1,-1);
      HY5(0,0,-1,1,1) =
        + 2.4107342184124538e-02
        - 9.3097125991768577e-02*HR1(-1)
        + 2.6860659680402010e-01*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,-1,1)
        + 5.3721319360804020e-01*HR1(-1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(-1,-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + HR1( -1)*HR4(0,0,-1,-1)
        + HR1( -1)*HR4(0,0,-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        + HR1(0) *HR1(1)*HR3(-1,-1,1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR1(1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        - HR1(0) *HR4(-1,-1,1,1)
        + HR1(0) *HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,-1,1,-1)
        + HR1(0) *HR4(0,-1,1,1)
        - 9.3097125991768577e-02*HR1(1)
        + 2.6860659680402010e-01*HR1(1)*HR1(1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,0,-1)
        + 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        + HR1(1) *HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,-1,1,-1)
        + HR1(1) *HR4(0,0,-1,-1)
        + HR1(1) *HR4(0,0,-1,1)
        + 2.4022650695910071e-01*HR3(-1,-1,1)
        - 2.4022650695910071e-01*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,1,1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,1,1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,-1,1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - 2.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        - HR5(0, -1,1,-1,1)
        - HR5(0, -1,1,1,-1)
        - HR5(0,0, -1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,1,-1)
        - HR5(0,0, -1,1,1);
      HY5(0,0,0,-1,1) =
        + 5.9142607400864533e-02
        - 1.1787599965050932e-01*HR1(-1)
        + 1.2153517583503078e-01*HR1(-1)*HR1(-1)
        - 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        + 2.4307035167006157e-01*HR1(-1)*HR1(1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(1)*HR3(-1,1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,-1,1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(-1,-1,1,1)
        - HR1( -1)*HR4(-1,1,1,1)
        + HR1( -1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + HR1( -1)*HR4(0,-1,1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(-1,1)
        + HR1(0) *HR1(1)*HR3(-1,-1,1)
        - HR1(0) *HR1(1)*HR3(-1,1,1)
        + HR1(0) *HR4(-1,-1,-1,1)
        - HR1(0) *HR4(-1,-1,1,1)
        + HR1(0) *HR4(-1,1,1,1)
        - 1.1787599965050932e-01*HR1(1)
        + 1.2153517583503078e-01*HR1(1)*HR1(1)
        - 9.7040087744168750e-02*HR1(1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - HR1(1) *HR4(-1,-1,1,1)
        + HR1(1) *HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,-1,1,-1)
        + HR1(1) *HR4(0,-1,1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,1,1)
        + 6.9314718055994530e-01*HR4(-1,1,1,1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        + HR5( -1,-1,1,1,1)
        - HR5(0, -1,-1,-1,-1)
        - HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - HR5(0, -1,1,-1,-1)
        - HR5(0, -1,1,-1,1)
        - HR5(0, -1,1,1,-1)
        - HR5(0, -1,1,1,1);
      HY5(0,0,0,1,-1) =
        + 7.4276054639867797e-02
        - 1.7284527823898438e-01*HR1(-1)
        + 2.5410760640234242e-01*HR1(-1)*HR1(-1)
        + 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        + 5.0821521280468485e-01*HR1(-1)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(1)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(1)*HR3(0,-1,1)
        + HR1( -1)*HR1(1)*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,1,1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(-1,-1,1,1)
        - HR1( -1)*HR4(-1,1,1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,1,-1)
        - HR1( -1)*HR4(0,-1,1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        - HR1( -1)*HR4(0,1,-1,1)
        - HR1( -1)*HR4(0,1,1,-1)
        + 1.1552453009332421e-01*HR1(0)*HR1(1)*HR1(1)*HR1(1)
        - 1.7284527823898438e-01*HR1(1)
        + 2.5410760640234242e-01*HR1(1)*HR1(1)
        + 1.7711559006386898e-01*HR1(1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(1)*HR1(1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(-1,-1,1)
        + HR1(1) *HR1(1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,1)
        + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        - HR1(1) *HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,1,-1)
        - HR1(1) *HR4(0,-1,1,1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        - HR1(1) *HR4(0,1,-1,1)
        - HR1(1) *HR4(0,1,1,-1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,1,1)
        + 6.9314718055994530e-01*HR4(-1,1,1,1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,1,1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,1)
        - 6.9314718055994530e-01*HR4(0,1,1,-1)
        - 6.9314718055994530e-01*HR4(0,1,1,1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        + HR5( -1,-1,1,1,1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,1)
        + 3.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,1,1,-1)
        + HR5(0, -1,1,1,1)
        + 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,1,-1,1,-1)
        + HR5(0,1, -1,1,1)
        + 2.0000000000000000e+00*HR5(0,1,1,-1,-1)
        + HR5(0,1,1, -1,1)
        + HR5(0,1,1,1, -1);
      HY5(0,0,1,-1,-1) =
        + 2.5535023438634211e-02
        - 1.1412342741606084e-01*HR1(-1)
        - 2.3766885054564933e-01*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR1(0)*HR1(1)
        - 4.7533770109129867e-01*HR1(-1)*HR1(1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(-1,-1,1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + HR1( -1)*HR4(0,1,-1,-1)
        - 1.2011325347955035e-01*HR1(0)*HR1(1)*HR1(1)
        - 1.1412342741606084e-01*HR1(1)
        - 2.3766885054564933e-01*HR1(1)*HR1(1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR1(1)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        - HR1(1) *HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,-1,1,-1)
        + HR1(1) *HR4(0,1,-1,-1)
        - 2.4022650695910071e-01*HR3(-1,-1,1)
        + 2.4022650695910071e-01*HR3(-1,1,1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,-1,1)
        - 2.4022650695910071e-01*HR3(0,1,-1)
        - 2.4022650695910071e-01*HR3(0,1,1)
        - 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(-1,-1,1,1)
        + 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,1)
        + 1.3862943611198906e+00*HR4(0,-1,1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,1,1)
        + 1.3862943611198906e+00*HR4(0,1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,1)
        + 6.9314718055994530e-01*HR4(0,1,1,-1)
        - 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + HR5( -1,-1,-1,1,1)
        - 6.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - 3.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        - HR5(0, -1,1,-1,1)
        - HR5(0, -1,1,1,-1)
        - 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        - HR5(0,1, -1,-1,1)
        - HR5(0,1, -1,1,-1)
        - HR5(0,1,1, -1,-1);
      HY5(0,0,1,-1,1) =
        + 3.6321732111088421e-02
        - 1.9355535381306524e-01*HR1(-1)
        - 7.3900238327152102e-01*HR1(-1)*HR1(-1)
        + 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        + HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(-1)*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR1(-1)*HR1(0)*HR1(1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + HR1( -1)*HR1(0)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + HR1( -1)*HR1(0)*HR3(0,-1,1)
        + HR1( -1)*HR1(0)*HR3(0,1,-1)
        - 1.4780047665430420e+00*HR1(-1)*HR1(1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,-1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        - HR1( -1)*HR2(0,-1)*HR2(0,1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(-1,-1,1,1)
        - 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,1)
        + HR1( -1)*HR4(0,-1,0,1)
        - HR1( -1)*HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - HR1( -1)*HR4(0,1,-1,-1)
        - 2.9112026323250625e-01*HR1(0)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(0)*HR1(1)*HR1(1)*HR2(0,-1)
        + HR1(0) *HR1(1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,-1)
        + HR1(0) *HR1(1)*HR3(0,-1,1)
        + HR1(0) *HR1(1)*HR3(0,1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR4(-1,-1,-1,1)
        - HR1(0) *HR4(-1,-1,1,1)
        - 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,1,-1)
        - HR1(0) *HR4(0,-1,1,1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,1,-1,-1)
        - HR1(0) *HR4(0,1,-1,1)
        - HR1(0) *HR4(0,1,1,-1)
        - 1.9355535381306524e-01*HR1(1)
        - 7.3900238327152102e-01*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        + HR1(1) *HR1(1)*HR3(0,-1,-1)
        + HR1(1) *HR1(1)*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR1(1)*HR2(-1,1)
        + HR1(1) *HR2(-1,1)*HR2(0,-1)
        + 5.8224052646501250e-01*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        - HR1(1) *HR2(0,-1)*HR2(0,1)
        + 5.8224052646501250e-01*HR1(1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        + HR1(1) *HR4(-1,-1,-1,1)
        - 4.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,1)
        + HR1(1) *HR4(0,-1,0,1)
        - HR1(1) *HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        - HR1(1) *HR4(0,1,-1,-1)
        + HR2(0, -1)*HR3(-1,-1,1)
        - HR2(0, -1)*HR3(-1,1,1)
        + HR2(0, -1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(0,-1,1)
        + HR2(0, -1)*HR3(0,1,-1)
        + HR2(0, -1)*HR3(0,1,1)
        - 5.8224052646501250e-01*HR3(-1,-1,1)
        + 5.8224052646501250e-01*HR3(-1,1,1)
        - 5.8224052646501250e-01*HR3(0,-1,-1)
        - 5.8224052646501250e-01*HR3(0,-1,1)
        - 5.8224052646501250e-01*HR3(0,1,-1)
        - 5.8224052646501250e-01*HR3(0,1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,1,1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        - 1.3862943611198906e+00*HR4(0,-1,-1,1)
        - 1.3862943611198906e+00*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,1,1)
        - 1.3862943611198906e+00*HR4(0,1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,1)
        - 6.9314718055994530e-01*HR4(0,1,1,-1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,-1,1,1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,1)
        - HR5(0, -1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        - HR5(0, -1,0,1,-1)
        - HR5(0, -1,0,1,1)
        + 3.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        + HR5(0, -1,1,-1,1)
        + HR5(0, -1,1,1,-1)
        + 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + HR5(0,1, -1,-1,1)
        + HR5(0,1, -1,1,-1)
        + HR5(0,1,1, -1,-1);
      HY5(0,0,1,0,-1) =
        + 1.8615775173851248e-01
        - 5.6852588003909690e-01*HR1(-1)
        - 6.6068813489808640e-01*HR1(-1)*HR1(-1)
        + 1.3707783890401886e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 4.1123351671205660e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1123351671205660e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        - 8.2246703342411321e-01*HR1(-1)*HR1(0)*HR1(1)
        - 1.3213762697961728e+00*HR1(-1)*HR1(1)
        + 4.1123351671205660e-01*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        + 8.2246703342411321e-01*HR1(-1)*HR2(0,-1)
        + 8.2246703342411321e-01*HR1(-1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,1,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(-1,1,1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,1,-1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        + HR1( -1)*HR4(0,1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,1,1,-1)
        - 4.1123351671205660e-01*HR1(0)*HR1(1)*HR1(1)
        - 5.6852588003909690e-01*HR1(1)
        - 6.6068813489808640e-01*HR1(1)*HR1(1)
        - 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(1)*HR1(1)*HR2(0,1)
        - HR1(1) *HR1(1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,1,-1)
        - 8.2246703342411321e-01*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(1)*HR2(-1,1)*HR2(-1,1)
        + 8.2246703342411321e-01*HR1(1)*HR2(0,-1)
        + 8.2246703342411321e-01*HR1(1)*HR2(0,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(1)*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,1,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,1,1)
        - 4.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(-1,-1,1,1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,-1,1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        + HR1(1) *HR4(0,1,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,1,1,-1)
        - HR2( -1,1)*HR3(-1,1,1)
        - 8.2246703342411321e-01*HR3(-1,-1,1)
        + 8.2246703342411321e-01*HR3(-1,1,1)
        - 8.2246703342411321e-01*HR3(0,-1,-1)
        - 8.2246703342411321e-01*HR3(0,-1,1)
        - 8.2246703342411321e-01*HR3(0,1,-1)
        - 8.2246703342411321e-01*HR3(0,1,1)
        - 2.0794415416798359e+00*HR4(-1,-1,-1,1)
        + 2.0794415416798359e+00*HR4(-1,-1,1,1)
        - 2.0794415416798359e+00*HR4(-1,1,1,1)
        + 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        + 2.0794415416798359e+00*HR4(0,-1,-1,1)
        + 2.0794415416798359e+00*HR4(0,-1,1,-1)
        + 2.0794415416798359e+00*HR4(0,-1,1,1)
        + 2.0794415416798359e+00*HR4(0,1,-1,-1)
        + 2.0794415416798359e+00*HR4(0,1,-1,1)
        + 2.0794415416798359e+00*HR4(0,1,1,-1)
        + 2.0794415416798359e+00*HR4(0,1,1,1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        + 7.0000000000000000e+00*HR5(-1,-1,-1,1,1)
        + HR5( -1,-1,1,-1,1)
        + HR5( -1,1,-1,1,1)
        - 6.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - 4.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - HR5(0, -1,-1,1,1)
        - 5.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,-1,1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,1,1,-1)
        - 6.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,1,-1,-1,1)
        - 4.0000000000000000e+00*HR5(0,1,-1,1,-1)
        - HR5(0,1, -1,1,1)
        - 5.0000000000000000e+00*HR5(0,1,1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,1,1,-1,1)
        - 3.0000000000000000e+00*HR5(0,1,1,1,-1);
      HY5(0,0,1,1,-1) =
        + 5.7353571803049304e-02
        - 4.3369237704895519e-01*HR1(-1)
        + 5.5365194946473328e-01*HR1(-1)*HR1(-1)
        - 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 1.0626935403832139e+00*HR1(-1)*HR1(0)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,1)
        + 1.1073038989294665e+00*HR1(-1)*HR1(1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(1)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        - HR1( -1)*HR1(1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,0,-1)
        - 1.0626935403832139e+00*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + HR1( -1)*HR2(0,-1)*HR2(0,1)
        - 1.0626935403832139e+00*HR1(-1)*HR2(0,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,0,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        + HR1( -1)*HR4(-1,-1,1,1)
        + HR1( -1)*HR4(0,-1,-1,1)
        - HR1( -1)*HR4(0,-1,0,1)
        - HR1( -1)*HR4(0,0,-1,1)
        - HR1( -1)*HR4(0,0,1,-1)
        - HR1( -1)*HR4(0,1,-1,-1)
        + 1.7328679513998632e-01*HR1(0)*HR1(0)*HR1(1)*HR1(1)
        + 5.3134677019160696e-01*HR1(0)*HR1(1)*HR1(1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,1,1)
        - 4.3369237704895519e-01*HR1(1)
        + 5.5365194946473328e-01*HR1(1)*HR1(1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR3(0,0,-1)
        + 1.0626935403832139e+00*HR1(1)*HR2(-1,1)
        - HR1(1) *HR2(-1,1)*HR2(0,-1)
        - 1.0626935403832139e+00*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        + HR1(1) *HR2(0,-1)*HR2(0,1)
        - 1.0626935403832139e+00*HR1(1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,0,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,0,1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,1,-1)
        + HR1(1) *HR4(-1,-1,-1,1)
        + HR1(1) *HR4(0,-1,-1,1)
        - HR1(1) *HR4(0,-1,0,1)
        - HR1(1) *HR4(0,0,-1,1)
        - HR1(1) *HR4(0,0,1,-1)
        - HR1(1) *HR4(0,1,-1,-1)
        - HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0, -1)*HR3(-1,1,1)
        - HR2(0, -1)*HR3(0,-1,-1)
        - HR2(0, -1)*HR3(0,-1,1)
        - HR2(0, -1)*HR3(0,1,-1)
        - HR2(0, -1)*HR3(0,1,1)
        + 1.0626935403832139e+00*HR3(-1,-1,1)
        - 1.0626935403832139e+00*HR3(-1,1,1)
        + 1.0626935403832139e+00*HR3(0,-1,-1)
        + 1.0626935403832139e+00*HR3(0,-1,1)
        + 1.0626935403832139e+00*HR3(0,1,-1)
        + 1.0626935403832139e+00*HR3(0,1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(-1,-1,1,1)
        - 1.3862943611198906e+00*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR4(0,0,-1,-1)
        - 6.9314718055994530e-01*HR4(0,0,-1,1)
        - 6.9314718055994530e-01*HR4(0,0,1,-1)
        - 6.9314718055994530e-01*HR4(0,0,1,1)
        - 1.3862943611198906e+00*HR4(0,1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,1)
        - 6.9314718055994530e-01*HR4(0,1,1,-1)
        + 3.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,-1,1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - HR5(0, -1,-1,1,1)
        + HR5(0, -1,0,-1,-1)
        + HR5(0, -1,0,-1,1)
        + HR5(0, -1,0,1,-1)
        + HR5(0, -1,0,1,1)
        + HR5(0, -1,1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,0,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,0,-1,1,-1)
        + HR5(0,0, -1,1,1)
        + 2.0000000000000000e+00*HR5(0,0,1,-1,-1)
        + HR5(0,0,1, -1,1)
        + HR5(0,0,1,1, -1)
        + 3.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        + HR5(0,1, -1,-1,1)
        + HR5(0,1, -1,1,-1)
        + HR5(0,1,1, -1,-1);
      HY5(0,1,-1,-1,-1) =
        + 1.9555438852482933e-02
        + 1.2679858379652411e-01*HR1(-1)
        - 2.7752054332410789e-02*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.5504108664821579e-02*HR1(-1)*HR1(0)
        - 5.5504108664821579e-02*HR1(-1)*HR1(1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(0,-1,-1,-1)
        + 5.5504108664821579e-02*HR1(0)*HR1(1)
        + 1.2679858379652411e-01*HR1(1)
        - 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - HR1(1) *HR4(0,-1,-1,-1)
        + 5.5504108664821579e-02*HR2(-1,1)
        - 5.5504108664821579e-02*HR2(0,-1)
        - 5.5504108664821579e-02*HR2(0,1)
        + 2.4022650695910071e-01*HR3(-1,-1,1)
        + 4.8045301391820142e-01*HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR3(0,-1,1)
        + 2.4022650695910071e-01*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        + HR5( -1,-1,-1,-1,1)
        + 4.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + HR5(0, -1,-1,-1,1)
        + HR5(0, -1,-1,1,-1)
        + HR5(0, -1,1,-1,-1)
        + HR5(0,1, -1,-1,-1);
      HY5(0,1,-1,-1,1) =
        + 2.8668668263701248e-02
        + 2.3517979306082505e-01*HR1(-1)
        - 4.7376502115063852e-02*HR1(-1)*HR1(-1)
        + 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + 9.4753004230127705e-02*HR1(-1)*HR1(0)
        + HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - 9.4753004230127705e-02*HR1(-1)*HR1(1)
        + HR1( -1)*HR1(1)*HR3(0,-1,-1)
        - 5.8224052646501250e-01*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 5.8224052646501250e-01*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        + 9.4753004230127705e-02*HR1(0)*HR1(1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        + HR1(0) *HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,-1,1,-1)
        + HR1(0) *HR4(0,1,-1,-1)
        + 2.3517979306082505e-01*HR1(1)
        - 5.8224052646501250e-01*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 9.4753004230127705e-02*HR2(-1,1)
        - HR2( -1,1)*HR3(0,-1,-1)
        - 9.4753004230127705e-02*HR2(0,-1)
        - HR2(0, -1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR2(0,-1)*HR3(0,-1,-1)
        - HR2(0, -1)*HR3(0,-1,1)
        - HR2(0, -1)*HR3(0,1,-1)
        - 9.4753004230127705e-02*HR2(0,1)
        + HR2(0,1) *HR3(0,-1,-1)
        + 5.8224052646501250e-01*HR3(-1,-1,1)
        + 1.1644810529300250e+00*HR3(0,-1,-1)
        + 5.8224052646501250e-01*HR3(0,-1,1)
        + 5.8224052646501250e-01*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 2.0794415416798359e+00*HR4(0,-1,-1,-1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - HR5( -1,-1,-1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - HR5(0, -1,-1,0,1)
        - HR5(0, -1,-1,1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,0,-1,-1)
        - HR5(0, -1,1,-1,-1)
        + 6.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,1, -1,-1,-1);
      HY5(0,1,-1,1,-1) =
        + 4.7069633474401836e-02
        + 6.4210078767232862e-01*HR1(-1)
        - 1.0703618543335311e-01*HR1(-1)*HR1(-1)
        - 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        + 2.1407237086670622e-01*HR1(-1)*HR1(0)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        - 2.1407237086670622e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        + 1.0626935403832139e+00*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        + 1.0626935403832139e+00*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,0,-1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        + 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        + 2.1407237086670622e-01*HR1(0)*HR1(1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,-1,1)
        - 6.9314718055994530e-01*HR1(0)*HR3(0,1,-1)
        + 6.4210078767232862e-01*HR1(1)
        + 1.0626935403832139e+00*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,0,-1)
        + 4.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        + 2.1407237086670622e-01*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        - 2.1407237086670622e-01*HR2(0,-1)
        + 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR2(0,-1)*HR2(0,1)
        + HR2(0, -1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(0,-1,1)
        + HR2(0, -1)*HR3(0,1,-1)
        - 2.1407237086670622e-01*HR2(0,1)
        - 2.0000000000000000e+00*HR2(0,1)*HR3(0,-1,-1)
        - 1.0626935403832139e+00*HR3(-1,-1,1)
        - 2.1253870807664278e+00*HR3(0,-1,-1)
        - 1.0626935403832139e+00*HR3(0,-1,1)
        - 1.0626935403832139e+00*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 2.7725887222397812e+00*HR4(0,-1,-1,-1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,0,1)
        + 6.9314718055994530e-01*HR4(0,-1,1,-1)
        + 1.3862943611198906e+00*HR4(0,0,-1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - HR5( -1,-1,-1,-1,1)
        - 8.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 4.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,0,1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - 4.0000000000000000e+00*HR5(0,-1,0,-1,-1)
        + HR5(0, -1,0,-1,1)
        + HR5(0, -1,0,1,-1)
        - HR5(0, -1,1,-1,-1)
        - 1.2000000000000000e+01*HR5(0,0,-1,-1,-1)
        - HR5(0,1, -1,-1,-1);
      HY5(0,1,-1,1,1) =
        + 8.2208743029471844e-02
        + 1.9248049955307152e+00*HR1(-1)
        - 2.6860659680402010e-01*HR1(-1)*HR1(-1)
        + 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 8.3333333333333333e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 5.3721319360804020e-01*HR1(-1)*HR1(0)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(0)*HR3(0,0,-1)
        - 5.3721319360804020e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(1)*HR3(0,0,-1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        - 2.4022650695910071e-01*HR1(-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(0,0,-1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR1(-1)*HR4(0,0,0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR1(1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(-1,-1,1)
        + HR1(0) *HR1(0)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,-1,1)
        + 5.0000000000000000e-01*HR1(0)*HR1(0)*HR3(0,1,-1)
        + 5.3721319360804020e-01*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR1(0)*HR1(1)*HR3(0,0,-1)
        + HR1(0) *HR2(-1,1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(0)*HR2(0,-1)*HR2(0,-1)
        - HR1(0) *HR2(0,-1)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,1,-1)
        + HR1(0) *HR4(-1,-1,-1,1)
        - 4.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,-1,-1,1)
        + HR1(0) *HR4(0,-1,0,1)
        - HR1(0) *HR4(0,-1,1,-1)
        - 2.0000000000000000e+00*HR1(0)*HR4(0,0,-1,-1)
        - HR1(0) *HR4(0,1,-1,-1)
        + 1.9248049955307152e+00*HR1(1)
        - 2.4022650695910071e-01*HR1(1)*HR2(0,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        + 1.3862943611198906e+00*HR1(1)*HR3(0,0,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(0,0,0,-1)
        + 5.3721319360804020e-01*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        - HR2( -1,1)*HR3(0,-1,-1)
        - HR2( -1,1)*HR3(0,0,-1)
        - 5.3721319360804020e-01*HR2(0,-1)
        - 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR2(0,-1)*HR2(0,1)
        + HR2(0, -1)*HR3(0,0,-1)
        - 5.3721319360804020e-01*HR2(0,1)
        + HR2(0,1) *HR3(0,-1,-1)
        + HR2(0,1) *HR3(0,0,-1)
        + 2.4022650695910071e-01*HR3(-1,-1,1)
        + 4.8045301391820142e-01*HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR3(0,-1,1)
        + 2.4022650695910071e-01*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 2.7725887222397812e+00*HR4(0,-1,-1,-1)
        - 1.3862943611198906e+00*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,0,1)
        - 6.9314718055994530e-01*HR4(0,-1,1,-1)
        - 1.3862943611198906e+00*HR4(0,0,-1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        + HR5( -1,-1,-1,-1,1)
        + 7.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - HR5(0, -1,-1,0,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        + HR5(0, -1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        - HR5(0, -1,0,1,-1)
        + HR5(0, -1,1,-1,-1)
        + 7.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        + HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,0,-1)
        - HR5(0,0, -1,0,1)
        + HR5(0,1, -1,-1,-1);
      HY5(0,1,0,1,-1) =
        + 1.4122347902560834e-01
        + 1.4132080497842155e+00*HR1(-1)
        - 2.5410760640234242e-01*HR1(-1)*HR1(-1)
        - 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,1)
        - HR1( -1)*HR1(-1)*HR3(-1,-1,1)
        + HR1( -1)*HR1(-1)*HR3(-1,1,1)
        - HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,1,-1)
        + 5.0821521280468485e-01*HR1(-1)*HR1(0)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(0,1)
        - 5.0821521280468485e-01*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,1)
        + 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(1)*HR3(0,-1,1)
        - HR1( -1)*HR1(1)*HR3(0,1,-1)
        + 1.0626935403832139e+00*HR1(-1)*HR2(-1,1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(-1,1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        + 1.0626935403832139e+00*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR2(0,-1)*HR2(0,-1)
        - HR1( -1)*HR2(0,-1)*HR2(0,1)
        + 1.0626935403832139e+00*HR1(-1)*HR2(0,1)
        + 1.3862943611198906e+00*HR1(-1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,0,-1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,0,1)
        - 1.3862943611198906e+00*HR1(-1)*HR3(0,1,-1)
        + 4.0000000000000000e+00*HR1(-1)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(-1,-1,1,1)
        + 4.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + HR1( -1)*HR4(0,-1,0,1)
        + HR1( -1)*HR4(0,-1,1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,1)
        + 2.0000000000000000e+00*HR1(-1)*HR4(0,0,1,-1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,1,-1,-1)
        + 5.0821521280468485e-01*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR1(0)*HR1(1)*HR2(0,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(-1,-1,1)
        + 1.3862943611198906e+00*HR1(0)*HR3(-1,1,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(0)*HR3(0,-1,1)
        - 1.3862943611198906e+00*HR1(0)*HR3(0,1,-1)
        - 1.3862943611198906e+00*HR1(0)*HR3(0,1,1)
        + 1.4132080497842155e+00*HR1(1)
        - 1.0626935403832139e+00*HR1(1)*HR2(-1,1)
        + HR1(1) *HR2(-1,1)*HR2(0,-1)
        + 1.0626935403832139e+00*HR1(1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(1)*HR2(0,-1)*HR2(0,-1)
        - HR1(1) *HR2(0,-1)*HR2(0,1)
        + 1.0626935403832139e+00*HR1(1)*HR2(0,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(-1,-1,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,-1,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,0,-1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,0,1)
        - 1.3862943611198906e+00*HR1(1)*HR3(0,1,-1)
        - 3.0000000000000000e+00*HR1(1)*HR4(-1,-1,-1,1)
        + 4.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + HR1(1) *HR4(0,-1,0,1)
        + HR1(1) *HR4(0,-1,1,-1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,0,-1,1)
        + 2.0000000000000000e+00*HR1(1)*HR4(0,0,1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,1,-1,-1)
        + 5.0821521280468485e-01*HR2(-1,1)
        + 3.4657359027997265e-01*HR2(-1,1)*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,1)
        + HR2( -1,1)*HR3(-1,-1,1)
        + 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        + HR2( -1,1)*HR3(0,-1,1)
        + HR2( -1,1)*HR3(0,1,-1)
        - 5.0821521280468485e-01*HR2(0,-1)
        + 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR2(0,-1)*HR2(0,1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(-1,-1,1)
        - 2.0000000000000000e+00*HR2(0,-1)*HR3(-1,1,1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(0,-1,1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(0,1,-1)
        + 2.0000000000000000e+00*HR2(0,-1)*HR3(0,1,1)
        - 5.0821521280468485e-01*HR2(0,1)
        + 3.4657359027997265e-01*HR2(0,1)*HR2(0,1)
        - 2.0000000000000000e+00*HR2(0,1)*HR3(0,-1,-1)
        - HR2(0,1) *HR3(0,-1,1)
        - 2.1253870807664278e+00*HR3(-1,-1,1)
        + 2.1253870807664278e+00*HR3(-1,1,1)
        - 2.1253870807664278e+00*HR3(0,-1,-1)
        - 2.1253870807664278e+00*HR3(0,-1,1)
        - 2.1253870807664278e+00*HR3(0,1,-1)
        - 2.1253870807664278e+00*HR3(0,1,1)
        - 2.7725887222397812e+00*HR4(-1,-1,-1,1)
        + 1.3862943611198906e+00*HR4(-1,-1,1,1)
        + 2.7725887222397812e+00*HR4(0,-1,-1,-1)
        + 1.3862943611198906e+00*HR4(0,-1,-1,1)
        + 1.3862943611198906e+00*HR4(0,-1,1,-1)
        + 1.3862943611198906e+00*HR4(0,0,-1,-1)
        + 1.3862943611198906e+00*HR4(0,0,-1,1)
        + 1.3862943611198906e+00*HR4(0,0,1,-1)
        + 1.3862943611198906e+00*HR4(0,0,1,1)
        + 2.7725887222397812e+00*HR4(0,1,-1,-1)
        + 1.3862943611198906e+00*HR4(0,1,-1,1)
        + 1.3862943611198906e+00*HR4(0,1,1,-1)
        - 7.0000000000000000e+00*HR5(-1,-1,-1,-1,1)
        - HR5( -1,-1,1,-1,1)
        - 8.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 4.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,0,1)
        - 2.0000000000000000e+00*HR5(0,-1,-1,1,-1)
        - 4.0000000000000000e+00*HR5(0,-1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        - HR5(0, -1,0,1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,1,-1,-1)
        - HR5(0, -1,1,-1,1)
        + HR5(0, -1,1,0,1)
        - 1.2000000000000000e+01*HR5(0,0,-1,-1,-1)
        - 4.0000000000000000e+00*HR5(0,0,-1,-1,1)
        - 4.0000000000000000e+00*HR5(0,0,-1,1,-1)
        - 4.0000000000000000e+00*HR5(0,0,1,-1,-1)
        - 2.0000000000000000e+00*HR5(0,0,1,-1,1)
        - 4.0000000000000000e+00*HR5(0,0,1,1,-1)
        - 7.0000000000000000e+00*HR5(0,1,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,1,-1,-1,1)
        - 2.0000000000000000e+00*HR5(0,1,-1,1,-1)
        - HR5(0,1,0,1, -1)
        - 2.0000000000000000e+00*HR5(0,1,1,-1,-1);
      HY5(0,1,1,-1,-1) =
        + 1.0254618242743082e-01
        - 6.0337978402921669e-01*HR1(-1)
        + 2.3766885054564933e-01*HR1(-1)*HR1(-1)
        - 4.0037751159850118e-02*HR1(-1)*HR1(-1)*HR1(-1)
        + 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 1.2011325347955035e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        - 4.7533770109129867e-01*HR1(-1)*HR1(0)
        - 1.2011325347955035e-01*HR1(-1)*HR1(0)*HR1(0)
        + 2.4022650695910071e-01*HR1(-1)*HR1(0)*HR1(1)
        + 4.7533770109129867e-01*HR1(-1)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        + HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + 2.4022650695910071e-01*HR1(-1)*HR2(-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        + HR1( -1)*HR4(-1,-1,-1,1)
        - 2.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        - HR1( -1)*HR4(0,0,-1,-1)
        - 1.2011325347955035e-01*HR1(0)*HR1(0)*HR1(1)
        - 4.7533770109129867e-01*HR1(0)*HR1(1)
        - 2.4022650695910071e-01*HR1(0)*HR2(-1,1)
        + 2.4022650695910071e-01*HR1(0)*HR2(0,-1)
        + 2.4022650695910071e-01*HR1(0)*HR2(0,1)
        - 6.0337978402921669e-01*HR1(1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(1)*HR3(0,0,-1)
        - 2.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        - HR1(1) *HR4(0,0,-1,-1)
        - 4.7533770109129867e-01*HR2(-1,1)
        + 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        - HR2( -1,1)*HR3(0,-1,-1)
        + 4.7533770109129867e-01*HR2(0,-1)
        - 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR2(0,-1)*HR2(0,1)
        + 4.7533770109129867e-01*HR2(0,1)
        + HR2(0,1) *HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(-1,-1,1)
        - 2.4022650695910071e-01*HR3(0,-1,-1)
        - 2.4022650695910071e-01*HR3(0,0,-1)
        - 2.4022650695910071e-01*HR3(0,0,1)
        - 2.4022650695910071e-01*HR3(0,1,-1)
        - 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,0,1)
        + 6.9314718055994530e-01*HR4(0,0,-1,1)
        + 6.9314718055994530e-01*HR4(0,0,1,-1)
        + 6.9314718055994530e-01*HR4(0,1,-1,-1)
        - HR5( -1,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        - HR5(0, -1,-1,0,1)
        + HR5(0, -1,-1,1,-1)
        + HR5(0, -1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        - HR5(0, -1,0,1,-1)
        + 3.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - HR5(0,0, -1,1,-1)
        - HR5(0,0,1, -1,-1)
        - HR5(0,1, -1,-1,-1);
      HY5(0,1,1,-1,1) =
        + 1.7692012816527167e-01
        - 2.4370424139224501e+00*HR1(-1)
        + 7.3900238327152102e-01*HR1(-1)*HR1(-1)
        - 9.7040087744168750e-02*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(0)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR2(0,-1)
        - 2.9112026323250625e-01*HR1(-1)*HR1(-1)*HR1(1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR1(-1)*HR3(0,-1,-1)
        - HR1( -1)*HR1(-1)*HR3(0,0,-1)
        - 1.4780047665430420e+00*HR1(-1)*HR1(0)
        - 2.9112026323250625e-01*HR1(-1)*HR1(0)*HR1(0)
        + 5.8224052646501250e-01*HR1(-1)*HR1(0)*HR1(1)
        + HR1( -1)*HR1(0)*HR1(1)*HR2(0,-1)
        - HR1( -1)*HR1(0)*HR3(-1,-1,1)
        - HR1( -1)*HR1(0)*HR3(0,-1,-1)
        - HR1( -1)*HR1(0)*HR3(0,0,-1)
        + 1.4780047665430420e+00*HR1(-1)*HR1(1)
        + 6.9314718055994530e-01*HR1(-1)*HR1(1)*HR2(0,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR1(-1)*HR1(1)*HR3(0,0,-1)
        + 5.8224052646501250e-01*HR1(-1)*HR2(-1,1)
        - HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(0,0,-1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,-1,-1,-1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,0,-1,-1)
        + 3.0000000000000000e+00*HR1(-1)*HR4(0,0,0,-1)
        - 2.9112026323250625e-01*HR1(0)*HR1(0)*HR1(1)
        - 1.4780047665430420e+00*HR1(0)*HR1(1)
        - HR1(0) *HR1(1)*HR3(0,-1,-1)
        - HR1(0) *HR1(1)*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR1(0)*HR2(-1,1)
        - HR1(0) *HR2(-1,1)*HR2(0,-1)
        + 5.8224052646501250e-01*HR1(0)*HR2(0,-1)
        + 5.0000000000000000e-01*HR1(0)*HR2(0,-1)*HR2(0,-1)
        + HR1(0) *HR2(0,-1)*HR2(0,1)
        + 5.8224052646501250e-01*HR1(0)*HR2(0,1)
        + HR1(0) *HR4(-1,-1,-1,1)
        + HR1(0) *HR4(0,-1,-1,1)
        - HR1(0) *HR4(0,-1,0,1)
        - HR1(0) *HR4(0,0,-1,1)
        - HR1(0) *HR4(0,0,1,-1)
        - HR1(0) *HR4(0,1,-1,-1)
        - 2.4370424139224501e+00*HR1(1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,-1,-1)
        - 6.9314718055994530e-01*HR1(1)*HR3(0,0,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,-1,-1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,0,-1,-1)
        + 3.0000000000000000e+00*HR1(1)*HR4(0,0,0,-1)
        - 1.4780047665430420e+00*HR2(-1,1)
        - 6.9314718055994530e-01*HR2(-1,1)*HR2(0,-1)
        + 2.0000000000000000e+00*HR2(-1,1)*HR3(0,-1,-1)
        + 2.0000000000000000e+00*HR2(-1,1)*HR3(0,0,-1)
        + 1.4780047665430420e+00*HR2(0,-1)
        + 3.4657359027997265e-01*HR2(0,-1)*HR2(0,-1)
        + 6.9314718055994530e-01*HR2(0,-1)*HR2(0,1)
        + HR2(0, -1)*HR3(-1,-1,1)
        + HR2(0, -1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR2(0,-1)*HR3(0,0,-1)
        + HR2(0, -1)*HR3(0,1,-1)
        + 1.4780047665430420e+00*HR2(0,1)
        - 2.0000000000000000e+00*HR2(0,1)*HR3(0,-1,-1)
        - 2.0000000000000000e+00*HR2(0,1)*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR3(-1,-1,1)
        - 5.8224052646501250e-01*HR3(0,-1,-1)
        - 5.8224052646501250e-01*HR3(0,0,-1)
        - 5.8224052646501250e-01*HR3(0,0,1)
        - 5.8224052646501250e-01*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        + 6.9314718055994530e-01*HR4(0,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,0,1)
        - 6.9314718055994530e-01*HR4(0,0,-1,1)
        - 6.9314718055994530e-01*HR4(0,0,1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        + HR5( -1,-1,-1,-1,1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,0,1)
        - HR5(0, -1,-1,1,-1)
        - 3.0000000000000000e+00*HR5(0,-1,0,-1,-1)
        + 2.0000000000000000e+00*HR5(0,-1,0,-1,1)
        + HR5(0, -1,0,1,-1)
        - 9.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        + HR5(0,0, -1,-1,1)
        + 3.0000000000000000e+00*HR5(0,0,-1,0,-1)
        + 2.0000000000000000e+00*HR5(0,0,-1,0,1)
        + HR5(0,0, -1,1,-1)
        + 6.0000000000000000e+00*HR5(0,0,0,-1,-1)
        + 3.0000000000000000e+00*HR5(0,0,0,-1,1)
        + 3.0000000000000000e+00*HR5(0,0,0,1,-1)
        + HR5(0,0,1, -1,-1)
        + HR5(0,0,1,0, -1)
        + HR5(0,1, -1,-1,-1);
      HY5(0,1,1,1,-1) =
        + 4.0707197178331534e-01
        + 1.0681889964961481e+00*HR1(-1)
        - 5.5365194946473328e-01*HR1(-1)*HR1(-1)
        + 1.7711559006386898e-01*HR1(-1)*HR1(-1)*HR1(-1)
        - 2.8881132523331054e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 8.3333333333333333e-03*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
        + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
        - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(-1,1)
        - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR2(0,-1)
        - 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(0)
        - 1.7328679513998632e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
        + 5.3134677019160696e-01*HR1(-1)*HR1(-1)*HR1(1)
        - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR2(0,-1)
        + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(-1,-1,1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,-1,-1)
        + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR3(0,0,-1)
        + 1.1073038989294665e+00*HR1(-1)*HR1(0)
        + 5.3134677019160696e-01*HR1(-1)*HR1(0)*HR1(0)
        + 1.1552453009332421e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
        - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
        - 1.0626935403832139e+00*HR1(-1)*HR1(0)*HR1(1)
        - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR2(-1,1)
        - 1.1073038989294665e+00*HR1(-1)*HR1(1)
        + HR1( -1)*HR1(1)*HR3(0,-1,-1)
        + HR1( -1)*HR1(1)*HR3(0,0,-1)
        - 1.0626935403832139e+00*HR1(-1)*HR2(-1,1)
        + HR1( -1)*HR2(-1,1)*HR2(0,-1)
        - 6.9314718055994530e-01*HR1(-1)*HR3(-1,-1,1)
        - HR1( -1)*HR4(-1,-1,-1,1)
        - HR1( -1)*HR4(0,-1,-1,-1)
        - HR1( -1)*HR4(0,0,-1,-1)
        - HR1( -1)*HR4(0,0,0,-1)
        + 1.1552453009332421e-01*HR1(0)*HR1(0)*HR1(0)*HR1(1)
        + 5.3134677019160696e-01*HR1(0)*HR1(0)*HR1(1)
        + 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(-1,1)
        - 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(0,-1)
        - 3.4657359027997265e-01*HR1(0)*HR1(0)*HR2(0,1)
        + 1.1073038989294665e+00*HR1(0)*HR1(1)
        + 1.0626935403832139e+00*HR1(0)*HR2(-1,1)
        - 1.0626935403832139e+00*HR1(0)*HR2(0,-1)
        - 1.0626935403832139e+00*HR1(0)*HR2(0,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(-1,-1,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,-1,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,0,-1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,0,1)
        + 6.9314718055994530e-01*HR1(0)*HR3(0,1,-1)
        + 1.0681889964961481e+00*HR1(1)
        - HR1(1) *HR4(0,-1,-1,-1)
        - HR1(1) *HR4(0,0,-1,-1)
        - HR1(1) *HR4(0,0,0,-1)
        + 1.1073038989294665e+00*HR2(-1,1)
        - HR2( -1,1)*HR3(0,-1,-1)
        - HR2( -1,1)*HR3(0,0,-1)
        - 1.1073038989294665e+00*HR2(0,-1)
        - HR2(0, -1)*HR3(-1,-1,1)
        - HR2(0, -1)*HR3(0,-1,-1)
        + HR2(0, -1)*HR3(0,0,-1)
        - HR2(0, -1)*HR3(0,1,-1)
        - 1.1073038989294665e+00*HR2(0,1)
        + HR2(0,1) *HR3(0,-1,-1)
        + HR2(0,1) *HR3(0,0,-1)
        + 1.0626935403832139e+00*HR3(-1,-1,1)
        + 1.0626935403832139e+00*HR3(0,-1,-1)
        + 1.0626935403832139e+00*HR3(0,0,-1)
        + 1.0626935403832139e+00*HR3(0,0,1)
        + 1.0626935403832139e+00*HR3(0,1,-1)
        + 6.9314718055994530e-01*HR4(-1,-1,-1,1)
        - 6.9314718055994530e-01*HR4(0,-1,-1,-1)
        - 6.9314718055994530e-01*HR4(0,0,-1,-1)
        - 6.9314718055994530e-01*HR4(0,0,0,-1)
        - 6.9314718055994530e-01*HR4(0,0,0,1)
        - 6.9314718055994530e-01*HR4(0,0,1,-1)
        - 6.9314718055994530e-01*HR4(0,1,-1,-1)
        + HR5( -1,-1,-1,-1,1)
        + 2.0000000000000000e+00*HR5(0,-1,-1,-1,-1)
        + HR5(0, -1,-1,-1,1)
        - HR5(0, -1,-1,0,1)
        + 2.0000000000000000e+00*HR5(0,-1,0,-1,-1)
        - HR5(0, -1,0,-1,1)
        + 6.0000000000000000e+00*HR5(0,0,-1,-1,-1)
        - HR5(0,0, -1,-1,1)
        - 2.0000000000000000e+00*HR5(0,0,-1,0,-1)
        - HR5(0,0, -1,0,1)
        - 4.0000000000000000e+00*HR5(0,0,0,-1,-1)
        - 2.0000000000000000e+00*HR5(0,0,0,-1,1)
        - 2.0000000000000000e+00*HR5(0,0,0,1,-1)
        + HR5(0,0,1, -1,-1)
        - HR5(0,0,1,0, -1)
        + HR5(0,1, -1,-1,-1);
      if (r < 0.0){
        HY5(-1,-1,-1,1,1) = HY5(-1,-1,-1,1,1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1);
        HY5(-1,-1,1,1,1) = HY5(-1,-1,1,1,1)
          + 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(0)
          - 4.9348022005446793e+00*HR1(-1)*HR2(0,-1)
          + 4.9348022005446793e+00*HR3(0,-1,-1);
        HY5(-1,1,-1,1,1) = HY5(-1,1,-1,1,1)
          - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(0,-1)
          - 9.8696044010893586e+00*HR3(0,-1,-1);
        HY5(-1,1,1,1,1) = HY5(-1,1,1,1,1)
          - 2.8732418312458363e+00*HR1(-1)
          - 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(0)
          + 3.4205442319285582e+00*HR1(-1)*HR1(0)
          + 2.4674011002723396e+00*HR1(-1)*HR1(0)*HR1(0)
          - 4.9348022005446793e+00*HR1(0)*HR2(0,-1)
          - 3.4205442319285582e+00*HR2(0,-1)
          + 4.9348022005446793e+00*HR3(0,-1,-1)
          + 4.9348022005446793e+00*HR3(0,0,-1);
        HY5(0,-1,-1,1,1) = HY5(0,-1,-1,1,1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          - 4.9348022005446793e+00*HR1(-1)*HR2(-1,1)
          + 4.9348022005446793e+00*HR3(-1,-1,1);
        HY5(0,-1,0,1,1) = HY5(0,-1,0,1,1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          - 4.9348022005446793e+00*HR1(-1)*HR2(-1,1)
          + 4.9348022005446793e+00*HR1(1)*HR2(-1,1)
          + 9.8696044010893586e+00*HR3(-1,-1,1)
          - 9.8696044010893586e+00*HR3(-1,1,1);
        HY5(0,-1,1,1,-1) = HY5(0,-1,1,1,-1)
          - 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          - 3.4205442319285582e+00*HR1(-1)*HR1(1)
          + 3.4205442319285582e+00*HR2(-1,1);
        HY5(0,-1,1,1,1) = HY5(0,-1,1,1,1)
          + 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(0)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 4.9348022005446793e+00*HR1(-1)*HR1(0)*HR1(1)
          + 3.4205442319285582e+00*HR1(-1)*HR1(1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(-1,1)
          - 4.9348022005446793e+00*HR1(-1)*HR2(0,-1)
          - 4.9348022005446793e+00*HR1(0)*HR2(-1,1)
          - 4.9348022005446793e+00*HR1(1)*HR2(0,-1)
          - 3.4205442319285582e+00*HR2(-1,1)
          - 4.9348022005446793e+00*HR3(-1,-1,1)
          + 4.9348022005446793e+00*HR3(0,-1,-1)
          + 4.9348022005446793e+00*HR3(0,-1,1);
        HY5(0,0,-1,1,1) = HY5(0,0,-1,1,1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 2.4674011002723396e+00*HR1(-1)*HR1(1)*HR1(1)
          - 4.9348022005446793e+00*HR1(1)*HR2(-1,1)
          - 4.9348022005446793e+00*HR3(-1,-1,1)
          + 4.9348022005446793e+00*HR3(-1,1,1);
        HY5(0,0,1,1,-1) = HY5(0,0,1,1,-1)
          - 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          - 3.4205442319285582e+00*HR1(-1)*HR1(1)
          - 1.7102721159642791e+00*HR1(1)*HR1(1);
        HY5(0,1,-1,1,1) = HY5(0,1,-1,1,1)
          - 8.2246703342411321e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 2.4674011002723396e+00*HR1(-1)*HR1(-1)*HR1(1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(-1,1)
          + 4.9348022005446793e+00*HR1(-1)*HR2(0,-1)
          + 4.9348022005446793e+00*HR1(1)*HR2(0,-1)
          - 4.9348022005446793e+00*HR3(-1,-1,1)
          - 9.8696044010893586e+00*HR3(0,-1,-1)
          - 4.9348022005446793e+00*HR3(0,-1,1)
          - 4.9348022005446793e+00*HR3(0,1,-1);
        HY5(0,1,1,-1,-1) = HY5(0,1,1,-1,-1)
          + 1.1854702951709319e+00*HR1(-1)
          + 1.1854702951709319e+00*HR1(1);
        HY5(0,1,1,-1,1) = HY5(0,1,1,-1,1)
          + 2.8732418312458363e+00*HR1(-1)
          + 2.8732418312458363e+00*HR1(1);
        HY5(0,1,1,1,-1) = HY5(0,1,1,1,-1)
          - 5.2441824215877001e+00*HR1(-1)
          + 1.7102721159642791e+00*HR1(-1)*HR1(-1)
          - 3.4205442319285582e+00*HR1(-1)*HR1(0)
          + 3.4205442319285582e+00*HR1(-1)*HR1(1)
          - 3.4205442319285582e+00*HR1(0)*HR1(1)
          - 5.2441824215877001e+00*HR1(1)
          - 3.4205442319285582e+00*HR2(-1,1)
          + 3.4205442319285582e+00*HR2(0,-1)
          + 3.4205442319285582e+00*HR2(0,1);
        Hi5(-1,-1,-1,-1,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1);
        Hi5(-1,-1,-1,1,1) =
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + HR1( -1)*HR3(0,-1,-1)
          - HR4(0, -1,-1,-1);
        Hi5(-1,-1,1,-1,1) =
          + 2.9112026323250625e-01*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,-1);
        Hi5(-1,-1,1,1,1) =
          - 7.0235377994456286e-01*HR1(-1)*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
          - HR1( -1)*HR1(0)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,0,-1)
          + HR1(0) *HR3(0,-1,-1)
          + 6.9314718055994530e-01*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR4(0,-1,-1,-1)
          - HR4(0,0, -1,-1);
        Hi5(-1,1,-1,1,1) =
          - 5.3721319360804020e-01*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + HR1( -1)*HR1(0)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,0,-1)
          - 2.0000000000000000e+00*HR1(0)*HR3(0,-1,-1)
          + 5.0000000000000000e-01*HR2(0,-1)*HR2(0,-1)
          - 1.3862943611198906e+00*HR3(0,-1,-1)
          + 4.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 2.0000000000000000e+00*HR4(0,0,-1,-1);
        Hi5(-1,1,1,1,1) =
          - 1.0846773019780311e+00*HR1(-1)
          + 7.0235377994456286e-01*HR1(-1)*HR1(-1)
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
          - 1.4047075598891257e+00*HR1(-1)*HR1(0)
          + 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)
          + 1.6666666666666666e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(0)
          - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(0)*HR2(0,-1)
          + HR1(0) *HR3(0,-1,-1)
          + HR1(0) *HR3(0,0,-1)
          + 1.4047075598891257e+00*HR2(0,-1)
          + 6.9314718055994530e-01*HR3(0,-1,-1)
          + 6.9314718055994530e-01*HR3(0,0,-1)
          - HR4(0, -1,-1,-1)
          - HR4(0,0, -1,-1)
          - HR4(0,0,0, -1);
        Hi5(0,-1,-1,-1,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + HR1( -1)*HR3(-1,-1,1)
          - HR4( -1,-1,-1,1);
        Hi5(0,-1,-1,0,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + HR1( -1)*HR3(-1,-1,1)
          + HR1(1) *HR3(-1,-1,1)
          - 5.0000000000000000e-01*HR2(-1,1)*HR2(-1,1);
        Hi5(0,-1,-1,1,-1) =
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR3(-1,-1,1);
        Hi5(0,-1,-1,1,1) =
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          - HR1( -1)*HR1(0)*HR2(-1,1)
          - HR1( -1)*HR1(1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1(0) *HR3(-1,-1,1)
          + HR1(1) *HR3(0,-1,-1)
          + HR2( -1,1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR3(-1,-1,1)
          + HR4( -1,-1,-1,1)
          - HR4(0, -1,-1,-1)
          - HR4(0, -1,-1,1);
        Hi5(0,-1,0,-1,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + HR1( -1)*HR1(1)*HR2(-1,1)
          + 2.0000000000000000e+00*HR1(-1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(-1,-1,1)
          + 5.0000000000000000e-01*HR2(-1,1)*HR2(-1,1)
          - 4.0000000000000000e+00*HR4(-1,-1,-1,1)
          + 2.0000000000000000e+00*HR4(-1,-1,1,1);
        Hi5(0,-1,0,1,-1) =
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          - 1.3862943611198906e+00*HR3(-1,-1,1)
          + 1.3862943611198906e+00*HR3(-1,1,1);
        Hi5(0,-1,0,1,1) =
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
          - HR1( -1)*HR1(0)*HR2(-1,1)
          - HR1( -1)*HR1(1)*HR2(-1,1)
          - HR1( -1)*HR1(1)*HR2(0,-1)
          - HR1( -1)*HR1(1)*HR2(0,1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(-1,-1,1)
          + 2.0000000000000000e+00*HR1(-1)*HR3(-1,1,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,1,-1)
          + HR1(0) *HR1(1)*HR2(-1,1)
          + 2.0000000000000000e+00*HR1(0)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(0)*HR3(-1,1,1)
          + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          + 2.0000000000000000e+00*HR1(1)*HR3(-1,-1,1)
          + HR1(1) *HR3(0,-1,-1)
          + HR1(1) *HR3(0,1,-1)
          - 5.0000000000000000e-01*HR2(-1,1)*HR2(-1,1)
          + HR2( -1,1)*HR2(0,-1)
          + HR2( -1,1)*HR2(0,1)
          + 1.3862943611198906e+00*HR3(-1,-1,1)
          - 1.3862943611198906e+00*HR3(-1,1,1)
          + 4.0000000000000000e+00*HR4(-1,-1,-1,1)
          - 2.0000000000000000e+00*HR4(-1,-1,1,1)
          - HR4(0, -1,-1,-1)
          - HR4(0, -1,-1,1)
          - HR4(0,1, -1,-1)
          - HR4(0,1, -1,1);
        Hi5(0,-1,1,-1,-1) =
          + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
          + 2.4022650695910071e-01*HR1(-1)*HR1(1)
          - 2.4022650695910071e-01*HR2(-1,1);
        Hi5(0,-1,1,-1,1) =
          + 2.9112026323250625e-01*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.8224052646501250e-01*HR1(-1)*HR1(1)
          + HR1( -1)*HR1(1)*HR2(0,-1)
          - HR1( -1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
          - 5.8224052646501250e-01*HR2(-1,1)
          - HR2( -1,1)*HR2(0,-1)
          + HR4( -1,-1,-1,1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 2.0000000000000000e+00*HR4(0,-1,-1,1)
          + HR4(0, -1,1,-1);
        Hi5(0,-1,1,0,1) =
          + 8.2246703342411321e-01*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,1)
          + 1.6449340668482264e+00*HR1(-1)*HR1(1)
          + HR1( -1)*HR1(1)*HR2(0,-1)
          + HR1( -1)*HR1(1)*HR2(0,1)
          - HR1( -1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - HR1( -1)*HR3(0,-1,1)
          - HR1( -1)*HR3(0,1,-1)
          - HR1(1) *HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
          - HR1(1) *HR3(0,-1,1)
          - HR1(1) *HR3(0,1,-1)
          - 1.6449340668482264e+00*HR2(-1,1)
          + 5.0000000000000000e-01*HR2(-1,1)*HR2(-1,1)
          - HR2( -1,1)*HR2(0,-1)
          - HR2( -1,1)*HR2(0,1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,1)
          + 2.0000000000000000e+00*HR4(0,-1,1,-1)
          + 2.0000000000000000e+00*HR4(0,-1,1,1)
          + HR4(0,1, -1,-1)
          + HR4(0,1, -1,1);
        Hi5(0,-1,1,1,-1) =
          - 5.3134677019160696e-01*HR1(-1)*HR1(-1)
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
          - 1.0626935403832139e+00*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          + 1.0626935403832139e+00*HR2(-1,1)
          + 6.9314718055994530e-01*HR3(-1,-1,1)
          - 6.9314718055994530e-01*HR3(0,-1,-1)
          - 6.9314718055994530e-01*HR3(0,-1,1);
        Hi5(0,-1,1,1,1) =
          - 7.0235377994456286e-01*HR1(-1)*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(0)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(0)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
          + HR1( -1)*HR1(0)*HR2(-1,1)
          - HR1( -1)*HR1(0)*HR2(0,-1)
          - 1.4047075598891257e+00*HR1(-1)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          + HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,0,-1)
          - 5.0000000000000000e-01*HR1(0)*HR1(0)*HR2(-1,1)
          - HR1(0) *HR1(1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
          - HR1(0) *HR3(-1,-1,1)
          + HR1(0) *HR3(0,-1,-1)
          + HR1(0) *HR3(0,-1,1)
          - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          + HR1(1) *HR3(0,-1,-1)
          + HR1(1) *HR3(0,0,-1)
          + 1.4047075598891257e+00*HR2(-1,1)
          - 6.9314718055994530e-01*HR3(-1,-1,1)
          + 6.9314718055994530e-01*HR3(0,-1,-1)
          + 6.9314718055994530e-01*HR3(0,-1,1)
          - HR4( -1,-1,-1,1)
          - 2.0000000000000000e+00*HR4(0,-1,-1,-1)
          - HR4(0, -1,-1,1)
          - HR4(0, -1,1,-1)
          - HR4(0,0, -1,-1)
          - HR4(0,0, -1,1);
        Hi5(0,0,-1,-1,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          - HR1( -1)*HR1(1)*HR2(-1,1)
          - HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(-1,1,1)
          + HR1(1) *HR3(-1,-1,1)
          + 2.0000000000000000e+00*HR4(-1,-1,-1,1)
          - HR4( -1,-1,1,1);
        Hi5(0,0,-1,0,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          - HR1( -1)*HR1(1)*HR2(-1,1)
          - HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(-1,1,1)
          + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(-1,1)
          + 2.0000000000000000e+00*HR1(1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(-1,1,1)
          + 3.0000000000000000e+00*HR4(-1,-1,-1,1)
          - 3.0000000000000000e+00*HR4(-1,-1,1,1)
          + 3.0000000000000000e+00*HR4(-1,1,1,1);
        Hi5(0,0,-1,1,-1) =
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
          + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          + 6.9314718055994530e-01*HR3(-1,-1,1)
          - 6.9314718055994530e-01*HR3(-1,1,1);
        Hi5(0,0,-1,1,1) =
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(0)*HR1(1)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
          + HR1( -1)*HR1(1)*HR2(-1,1)
          - HR1( -1)*HR1(1)*HR2(0,-1)
          + HR1( -1)*HR3(-1,-1,1)
          - HR1( -1)*HR3(-1,1,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,-1,1)
          - HR1(0) *HR1(1)*HR2(-1,1)
          - HR1(0) *HR3(-1,-1,1)
          + HR1(0) *HR3(-1,1,1)
          - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          - HR1(1) *HR3(-1,-1,1)
          + HR1(1) *HR3(0,-1,-1)
          + HR1(1) *HR3(0,-1,1)
          - 6.9314718055994530e-01*HR3(-1,-1,1)
          + 6.9314718055994530e-01*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR4(-1,-1,-1,1)
          + HR4( -1,-1,1,1)
          - HR4(0, -1,-1,-1)
          - HR4(0, -1,-1,1)
          - HR4(0, -1,1,-1)
          - HR4(0, -1,1,1);
        Hi5(0,0,0,-1,1) =
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(1)*HR1(1)*HR1(1)
          - 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(-1,1)
          - HR1(1) *HR3(-1,-1,1)
          + HR1(1) *HR3(-1,1,1)
          - HR4( -1,-1,-1,1)
          + HR4( -1,-1,1,1)
          - HR4( -1,1,1,1);
        Hi5(0,0,0,1,-1) =
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
          - 1.1552453009332421e-01*HR1(1)*HR1(1)*HR1(1);
        Hi5(0,0,1,-1,-1) =
          + 1.2011325347955035e-01*HR1(-1)*HR1(-1)
          + 2.4022650695910071e-01*HR1(-1)*HR1(1)
          + 1.2011325347955035e-01*HR1(1)*HR1(1);
        Hi5(0,0,1,-1,1) =
          + 2.9112026323250625e-01*HR1(-1)*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 2.5000000000000000e-01*HR1(-1)*HR1(-1)*HR1(1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.8224052646501250e-01*HR1(-1)*HR1(1)
          + HR1( -1)*HR1(1)*HR2(-1,1)
          + HR1( -1)*HR1(1)*HR2(0,-1)
          + HR1( -1)*HR3(-1,-1,1)
          - HR1( -1)*HR3(-1,1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - HR1( -1)*HR3(0,-1,1)
          - HR1( -1)*HR3(0,1,-1)
          + 2.9112026323250625e-01*HR1(1)*HR1(1)
          + 5.0000000000000000e-01*HR1(1)*HR1(1)*HR2(0,-1)
          - HR1(1) *HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
          - HR1(1) *HR3(0,-1,1)
          - HR1(1) *HR3(0,1,-1)
          - 2.0000000000000000e+00*HR4(-1,-1,-1,1)
          + HR4( -1,-1,1,1)
          + 3.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 2.0000000000000000e+00*HR4(0,-1,-1,1)
          + 2.0000000000000000e+00*HR4(0,-1,1,-1)
          + HR4(0, -1,1,1)
          + 2.0000000000000000e+00*HR4(0,1,-1,-1)
          + HR4(0,1, -1,1)
          + HR4(0,1,1, -1);
        Hi5(0,0,1,0,-1) =
          + 4.1123351671205660e-01*HR1(-1)*HR1(-1)
          + 8.2246703342411321e-01*HR1(-1)*HR1(1)
          + 4.1123351671205660e-01*HR1(1)*HR1(1);
        Hi5(0,0,1,1,-1) =
          - 5.3134677019160696e-01*HR1(-1)*HR1(-1)
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
          - 1.0626935403832139e+00*HR1(-1)*HR1(1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(1)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,1)
          - 3.4657359027997265e-01*HR1(0)*HR1(1)*HR1(1)
          - 5.3134677019160696e-01*HR1(1)*HR1(1)
          - 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(1)*HR2(0,1)
          - 6.9314718055994530e-01*HR3(-1,-1,1)
          + 6.9314718055994530e-01*HR3(-1,1,1)
          - 6.9314718055994530e-01*HR3(0,-1,-1)
          - 6.9314718055994530e-01*HR3(0,-1,1)
          - 6.9314718055994530e-01*HR3(0,1,-1)
          - 6.9314718055994530e-01*HR3(0,1,1);
        Hi5(0,1,-1,-1,-1) =
          - 5.5504108664821579e-02*HR1(-1)
          - 5.5504108664821579e-02*HR1(1);
        Hi5(0,1,-1,-1,1) =
          - 9.4753004230127705e-02*HR1(-1)
          - 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          - HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(0,-1,-1)
          - 9.4753004230127705e-02*HR1(1)
          + HR1(1) *HR3(0,-1,-1)
          + HR4( -1,-1,-1,1)
          - 3.0000000000000000e+00*HR4(0,-1,-1,-1)
          - HR4(0, -1,-1,1)
          - HR4(0, -1,1,-1)
          - HR4(0,1, -1,-1);
        Hi5(0,1,-1,1,-1) =
          - 2.1407237086670622e-01*HR1(-1)
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          - 2.1407237086670622e-01*HR1(1)
          - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR3(-1,-1,1)
          + 1.3862943611198906e+00*HR3(0,-1,-1)
          + 6.9314718055994530e-01*HR3(0,-1,1)
          + 6.9314718055994530e-01*HR3(0,1,-1);
        Hi5(0,1,-1,1,1) =
          - 5.3721319360804020e-01*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          - 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(0)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR1(0)*HR1(1)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          + 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + HR1( -1)*HR1(0)*HR2(-1,1)
          + HR1( -1)*HR1(0)*HR2(0,-1)
          + HR1( -1)*HR1(1)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          + HR1( -1)*HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(-1)*HR3(0,0,-1)
          + HR1(0) *HR1(1)*HR2(0,-1)
          - HR1(0) *HR3(-1,-1,1)
          - 2.0000000000000000e+00*HR1(0)*HR3(0,-1,-1)
          - HR1(0) *HR3(0,-1,1)
          - HR1(0) *HR3(0,1,-1)
          - 5.3721319360804020e-01*HR1(1)
          + 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,-1,-1)
          - 2.0000000000000000e+00*HR1(1)*HR3(0,0,-1)
          - HR2( -1,1)*HR2(0,-1)
          + 5.0000000000000000e-01*HR2(0,-1)*HR2(0,-1)
          + HR2(0, -1)*HR2(0,1)
          - 6.9314718055994530e-01*HR3(-1,-1,1)
          - 1.3862943611198906e+00*HR3(0,-1,-1)
          - 6.9314718055994530e-01*HR3(0,-1,1)
          - 6.9314718055994530e-01*HR3(0,1,-1)
          - HR4( -1,-1,-1,1)
          + 4.0000000000000000e+00*HR4(0,-1,-1,-1)
          + 2.0000000000000000e+00*HR4(0,-1,-1,1)
          - HR4(0, -1,0,1)
          + HR4(0, -1,1,-1)
          + 2.0000000000000000e+00*HR4(0,0,-1,-1)
          + HR4(0,1, -1,-1);
        Hi5(0,1,0,1,-1) =
          - 5.0821521280468485e-01*HR1(-1)
          + 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(-1)*HR2(0,1)
          - 5.0821521280468485e-01*HR1(1)
          + 6.9314718055994530e-01*HR1(1)*HR2(-1,1)
          - 6.9314718055994530e-01*HR1(1)*HR2(0,-1)
          - 6.9314718055994530e-01*HR1(1)*HR2(0,1)
          + 1.3862943611198906e+00*HR3(-1,-1,1)
          - 1.3862943611198906e+00*HR3(-1,1,1)
          + 1.3862943611198906e+00*HR3(0,-1,-1)
          + 1.3862943611198906e+00*HR3(0,-1,1)
          + 1.3862943611198906e+00*HR3(0,1,-1)
          + 1.3862943611198906e+00*HR3(0,1,1);
        Hi5(0,1,1,-1,-1) =
          + 4.7533770109129867e-01*HR1(-1)
          - 1.2011325347955035e-01*HR1(-1)*HR1(-1)
          + 2.4022650695910071e-01*HR1(-1)*HR1(0)
          - 2.4022650695910071e-01*HR1(-1)*HR1(1)
          + 2.4022650695910071e-01*HR1(0)*HR1(1)
          + 4.7533770109129867e-01*HR1(1)
          + 2.4022650695910071e-01*HR2(-1,1)
          - 2.4022650695910071e-01*HR2(0,-1)
          - 2.4022650695910071e-01*HR2(0,1);
        Hi5(0,1,1,-1,1) =
          + 1.4780047665430420e+00*HR1(-1)
          - 2.9112026323250625e-01*HR1(-1)*HR1(-1)
          + 4.1666666666666666e-02*HR1(-1)*HR1(-1)*HR1(-1)*HR1(-1)
          + 1.6666666666666666e-01*HR1(-1)*HR1(-1)*HR1(-1)*HR1(1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(-1,1)
          - 5.0000000000000000e-01*HR1(-1)*HR1(-1)*HR2(0,-1)
          + 5.8224052646501250e-01*HR1(-1)*HR1(0)
          - 5.8224052646501250e-01*HR1(-1)*HR1(1)
          - HR1( -1)*HR1(1)*HR2(0,-1)
          + HR1( -1)*HR3(-1,-1,1)
          + HR1( -1)*HR3(0,-1,-1)
          + HR1( -1)*HR3(0,0,-1)
          + 5.8224052646501250e-01*HR1(0)*HR1(1)
          + 1.4780047665430420e+00*HR1(1)
          + HR1(1) *HR3(0,-1,-1)
          + HR1(1) *HR3(0,0,-1)
          + 5.8224052646501250e-01*HR2(-1,1)
          + HR2( -1,1)*HR2(0,-1)
          - 5.8224052646501250e-01*HR2(0,-1)
          - 5.0000000000000000e-01*HR2(0,-1)*HR2(0,-1)
          - HR2(0, -1)*HR2(0,1)
          - 5.8224052646501250e-01*HR2(0,1)
          - HR4( -1,-1,-1,1)
          - HR4(0, -1,-1,1)
          + HR4(0, -1,0,1)
          + HR4(0,0, -1,1)
          + HR4(0,0,1, -1)
          + HR4(0,1, -1,-1);
        Hi5(0,1,1,1,-1) =
          + 3.2877511713386177e-02*HR1(-1)
          + 5.3134677019160696e-01*HR1(-1)*HR1(-1)
          - 1.1552453009332421e-01*HR1(-1)*HR1(-1)*HR1(-1)
          + 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(0)
          - 3.4657359027997265e-01*HR1(-1)*HR1(-1)*HR1(1)
          - 1.0626935403832139e+00*HR1(-1)*HR1(0)
          - 3.4657359027997265e-01*HR1(-1)*HR1(0)*HR1(0)
          + 6.9314718055994530e-01*HR1(-1)*HR1(0)*HR1(1)
          + 1.0626935403832139e+00*HR1(-1)*HR1(1)
          + 6.9314718055994530e-01*HR1(-1)*HR2(-1,1)
          - 3.4657359027997265e-01*HR1(0)*HR1(0)*HR1(1)
          - 1.0626935403832139e+00*HR1(0)*HR1(1)
          - 6.9314718055994530e-01*HR1(0)*HR2(-1,1)
          + 6.9314718055994530e-01*HR1(0)*HR2(0,-1)
          + 6.9314718055994530e-01*HR1(0)*HR2(0,1)
          + 3.2877511713386177e-02*HR1(1)
          - 1.0626935403832139e+00*HR2(-1,1)
          + 1.0626935403832139e+00*HR2(0,-1)
          + 1.0626935403832139e+00*HR2(0,1)
          - 6.9314718055994530e-01*HR3(-1,-1,1)
          - 6.9314718055994530e-01*HR3(0,-1,-1)
          - 6.9314718055994530e-01*HR3(0,0,-1)
          - 6.9314718055994530e-01*HR3(0,0,1)
          - 6.9314718055994530e-01*HR3(0,1,-1);
      }
    }
    // nw > 4 endif
  }
  // (n1,n2) = (-1,1) -- completion endif

 }

 void hplog5::pfillirr1dhplatinf(double x, int nw, HArr<1>& HX1, HArr<2>& HX2, HArr<3>& HX3, HArr<4>& HX4, HArr<5>& HX5,
                                                   HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5,
                                                   HArr<1>& Hi1, HArr<2>& Hi2, HArr<3>& Hi3, HArr<4>& Hi4, HArr<5>& Hi5, int n1, int n2)
 {
  // evaluates the HPL for y > r2p1
  // fillirr1dhplatinf is called by eval1dhplatinf after calling
  // fillirr1dhplat0 with argument r=1/y
  // it is guaranteed that nw is in the range 2:4, and that (n1,n2)
  // take one of the pairs of values (0,1), (-1,0) or (-1,1)

  // (n1,n2) = (0,1) or (-1,1)
  if (    ( (n1 == 0)  && (n2 == 1) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,1) =
       + 3.2898681336964528e+00
       - 5.0000000000000000e-01*HX1(0)*HX1(0)
       - HX2(0,1);
    Hi2(0,1) =
       - HX1(0);
    if ( nw > 2 ){
      HY3(0,0,1) =
        - 3.2898681336964528e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX3(0,0,1);
      HY3(0,1,1) =
        + 1.2020569031595942e+00
        + 4.9348022005446793e+00*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX2(0,1)
        + HX3(0,0,1)
        - HX3(0,1,1);
      Hi3(0,0,1) =
        + 5.000000000000000e-01*HX1(0)*HX1(0);
      Hi3(0,1,1) =
        + 1.6449340668482264e+00
        - 5.0000000000000000e-01*HX1(0)*HX1(0)
        - HX2(0,1);
    }

    if ( nw > 3 ){
      HY4(0,0,0,1) =
        + 2.1646464674222763e+00
        + 1.6449340668482264e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX4(0,0,0,1);
      HY4(0,0,1,1) =
        + 2.1646464674222763e+00
        - 1.2020569031595942e+00*HX1(0)
        - 2.4674011002723396e+00*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX3(0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1,1);
      HY4(0,1,1,1) =
        - 5.1410353601279064e+00
        + 2.4674011002723396e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        + HX1(0) *HX3(0,0,1)
        - HX1(0) *HX3(0,1,1)
        + 4.9348022005446793e+00*HX2(0,1)
        - HX4(0,0,0,1)
        + HX4(0,0,1,1)
        - HX4(0,1,1,1);
      Hi4(0,0,0,1) =
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0);
      Hi4(0,0,1,1) =
        - 1.2020569031595942e+00
        - 1.6449340668482264e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX3(0,0,1);
      Hi4(0,1,1,1) =
        + 1.6449340668482264e+00*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX2(0,1)
        + HX3(0,0,1)
        - HX3(0,1,1);
    }
    // nw > 3 endif

    if ( nw > 4 ){
      HY5(0,0,0,0,1) =
        - 2.1646464674222763e+00*HX1(0)
        - 5.4831135561607547e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX5(0,0,0,0,1);
      HY5(0,0,0,1,1) =
        - 2.9176809454512223e+00
        - 2.1646464674222763e+00*HX1(0)
        + 6.0102845157979714e-01*HX1(0)*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX4(0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        - HX5(0,0,0,1,1);
      HY5(0,0,1,0,1) =
        + 3.7615063806157047e+00
        - 1.0823232337111381e+00*HX1(0)
        - 1.2020569031595942e+00*HX1(0)*HX1(0)
        + 5.4831135561607547e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 3.2898681336964528e+00*HX3(0,0,1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        - HX5(0,0,1,0,1);
      HY5(0,0,1,1,1) =
        + 3.0142321054406660e+00
        + 5.1410353601279064e+00*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + HX1(0) *HX4(0,0,1,1)
        - 4.9348022005446793e+00*HX3(0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        - 2.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1,1,1);
      HY5(0,1,0,1,1) =
        - 1.5553916327150548e+00
        + 8.1174242528335364e-01*HX1(0)
        - 6.0102845157979714e-01*HX1(0)*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        - HX1(0) *HX1(0)*HX3(0,0,1)
        - 4.9348022005446793e+00*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        + 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,1)
        - 1.2020569031595942e+00*HX2(0,1)
        - HX2(0,1) *HX3(0,0,1)
        + 9.8696044010893586e+00*HX3(0,0,1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        + 7.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1,0,1)
        + HX5(0,1,0,1,1);
      HY5(0,1,1,1,1) =
        + 1.0369277551433699e+00
        - 4.0587121264167682e+00*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,1)
        + 4.9348022005446793e+00*HX1(0)*HX2(0,1)
        - HX1(0) *HX4(0,0,0,1)
        + HX1(0) *HX4(0,0,1,1)
        - HX1(0) *HX4(0,1,1,1)
        - 4.9348022005446793e+00*HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,1,1)
        + HX5(0,0,0,0,1)
        - HX5(0,0,0,1,1)
        + HX5(0,0,1,1,1)
        - HX5(0,1,1,1,1);
      Hi5(0,0,0,0,1) =
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0);
      Hi5(0,0,0,1,1) =
        + 1.0823232337111381e+00
        + 1.2020569031595942e+00*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX4(0,0,0,1);
      Hi5(0,0,1,0,1) =
        - 3.2469697011334145e+00
        - 2.4041138063191885e+00*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(0,0,1)
        + 3.0000000000000000e+00*HX4(0,0,0,1);
      Hi5(0,0,1,1,1) =
        + 1.8940656589944918e+00
        - 8.2246703342411321e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX3(0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1,1);
      Hi5(0,1,0,1,1) =
        - 2.4352272758500609e+00
        - 1.2020569031595942e+00*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,1)
        - 1.6449340668482264e+00*HX2(0,1)
        + 5.0000000000000000e-01*HX2(0,1)*HX2(0,1)
        + 4.0000000000000000e+00*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,1,1);
      Hi5(0,1,1,1,1) =
        - 8.1174242528335364e-01
        + 8.2246703342411321e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        + HX1(0) *HX3(0,0,1)
        - HX1(0) *HX3(0,1,1)
        + 1.6449340668482264e+00*HX2(0,1)
        - HX4(0,0,0,1)
        + HX4(0,0,1,1)
        - HX4(0,1,1,1);
    }
    // nw > 4 endif
  }
  // (n1,n2) = (0,1) or (-1,1) endif
  //**********

  // (n1,n2) = (-1,0) or (-1,1)
  if (    ( (n1 == -1) && (n2 == 0) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,-1) =
      + 1.6449340668482264e+00
      + 5.0000000000000000e-01*HX1(0)*HX1(0)
      - HX2(0, -1);
    if ( nw > 2 ){
      HY3(0,0,-1) =
        - 1.6449340668482264e+00*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX3(0,0, -1);
      HY3(0,-1,-1) =
        + 1.2020569031595942e+00
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(0,-1)
        - HX3(0, -1,-1)
        - HX3(0,0, -1);
    }

    if ( nw > 3 ){
      HY4(0,0,0,-1) =
        + 1.8940656589944918e+00
        + 8.2246703342411321e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX4(0,0,0, -1);
      HY4(0,0,-1,-1) =
        - 1.8940656589944918e+00
        - 1.2020569031595942e+00*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(0,0,-1)
        + HX4(0,0, -1,-1)
        + 2.0000000000000000e+00*HX4(0,0,0,-1);
      HY4(0,-1,-1,-1) =
        + 1.0823232337111381e+00
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        + HX1(0) *HX3(0,-1,-1)
        + HX1(0) *HX3(0,0,-1)
        - HX4(0, -1,-1,-1)
        - HX4(0,0, -1,-1)
        - HX4(0,0,0, -1);
    }

    if ( nw > 4 ){
      HY5(0,0,0,0,-1) =
        - 1.8940656589944918e+00*HX1(0)
        - 2.7415567780803773e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX5(0,0,0,0, -1);
      HY5(0,0,0,-1,-1) =
        + 3.0142321054406660e+00
        + 1.8940656589944918e+00*HX1(0)
        + 6.0102845157979714e-01*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX4(0,0,0,-1)
        - HX5(0,0,0, -1,-1)
        - 3.0000000000000000e+00*HX5(0,0,0,0,-1);
      HY5(0,0,-1,0,-1) =
        - 8.1023197211680719e+00
        - 5.1410353601279064e+00*HX1(0)
        - 1.2020569031595942e+00*HX1(0)*HX1(0)
        - 2.7415567780803773e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 1.6449340668482264e+00*HX3(0,0,-1)
        - HX5(0,0, -1,0,-1)
        + 7.0000000000000000e+00*HX5(0,0,0,0,-1);
      HY5(0,0,-1,-1,-1) =
        - 3.0142321054406660e+00
        - 1.0823232337111381e+00*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + HX5(0,0, -1,-1,-1)
        + 2.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,-1);
      HY5(0,-1,0,-1,-1) =
        + 7.4873046836069432e+00
        + 3.2469697011334145e+00*HX1(0)
        + 6.0102845157979714e-01*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - HX1(0) *HX1(0)*HX3(0,0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,-1)
        + 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - 1.2020569031595942e+00*HX2(0,-1)
        + HX2(0, -1)*HX3(0,0,-1)
        + HX5(0, -1,0,-1,-1)
        - HX5(0,0, -1,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,-1);
      HY5(0,-1,-1,-1,-1) =
        + 1.0369277551433699e+00
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX4(0,-1,-1,-1)
        + HX1(0) *HX4(0,0,-1,-1)
        + HX1(0) *HX4(0,0,0,-1)
        - HX5(0, -1,-1,-1,-1)
        - HX5(0,0, -1,-1,-1)
        - HX5(0,0,0, -1,-1)
        - HX5(0,0,0,0, -1);
    }
    // nw > 4 endif
  }
  // (n1,n2) = (-1,0) or (-1,1) endif

  // (n1,n2) = (-1,1) -- completion
  if ( (n1 == -1) && (n2 == 1) ){
    HY2(-1,1) =
      + 2.4674011002723396e+00
      + HX1( -1)*HX1(0)
      - 5.0000000000000000e-01*HX1(0)*HX1(0)
      + HX2( -1,1)
      - HX2(0, -1)
      - HX2(0,1);
    Hi2(-1,1) =
      - 6.9314718055994530e-01
      + HX1( -1)
      - HX1(0);
    if ( nw > 2 ){
      HY3(0,-1,1) =
        - 2.5190015545588625e+00
        - 2.4674011002723396e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX2(0,-1)
        - HX3(0, -1,1)
        + 2.0000000000000000e+00*HX3(0,0,-1)
        + HX3(0,0,1);
      HY3(0,1,-1) =
        + 4.3220869092982539e+00
        + 2.4674011002723396e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(0,1)
        - HX3(0,0, -1)
        - 2.0000000000000000e+00*HX3(0,0,1)
        - HX3(0,1, -1);
      HY3(-1,-1,1) =
        - 2.7620719062289241e+00
        + 2.4674011002723396e+00*HX1(-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)
        - 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)
        - HX1( -1)*HX2(0,-1)
        - HX1( -1)*HX2(0,1)
        - 2.4674011002723396e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX3( -1,-1,1)
        + HX3(0, -1,-1)
        + HX3(0,0, -1)
        + HX3(0,0,1)
        + HX3(0,1, -1);
      HY3(-1,1,1) =
        + 2.7620719062289241e+00
        - 4.9348022005446793e+00*HX1(-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)
        + 4.9348022005446793e+00*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(-1,1)
        - HX1(0) *HX2(0,-1)
        - HX1(0) *HX2(0,1)
        + HX3( -1,1,1)
        - HX3(0, -1,1)
        + HX3(0,0, -1)
        + HX3(0,0,1)
        - HX3(0,1,1);
      Hi3(0,-1,1) =
        + 8.2246703342411321e-01
        + 6.9314718055994530e-01*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)
        - HX2(0, -1);
      Hi3(0,1,-1) =
        - 6.9314718055994530e-01*HX1(0);
      Hi3(-1,-1,1) =
        + 2.4022650695910071e-01
        - 6.9314718055994530e-01*HX1(-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)
        - HX1( -1)*HX1(0)
        + 6.9314718055994530e-01*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0);
      Hi3(-1,1,1) =
        + 1.8851605738073271e+00
        + HX1( -1)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)
        + HX2( -1,1)
        - HX2(0, -1)
        - HX2(0,1);
    }

    if ( nw > 3 ){
      HY4(0,0,-1,1) =
        + 3.9234217222028759e+00
        + 2.5190015545588625e+00*HX1(0)
        + 1.2337005501361698e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX3(0,0,-1)
        + HX4(0,0, -1,1)
        - 3.0000000000000000e+00*HX4(0,0,0,-1)
        - HX4(0,0,0,1);
      HY4(0,0,1,-1) =
        - 4.1940025306306604e+00
        - 4.3220869092982539e+00*HX1(0)
        - 1.2337005501361698e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(0,0,1)
        + HX4(0,0,0, -1)
        + 3.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1, -1);
      HY4(0,-1,0,1) =
        + 9.4703282949724591e-01
        + 1.8030853547393914e+00*HX1(0)
        + 1.6449340668482264e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - 3.2898681336964528e+00*HX2(0,-1)
        + HX4(0, -1,0,1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1)
        - HX4(0,0,0,1);
      HY4(0,-1,-1,1) =
        + 2.5209599327464717e+00
        + 2.7620719062289241e+00*HX1(0)
        + 1.2337005501361698e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - HX1(0) *HX3(0,-1,-1)
        - HX1(0) *HX3(0,0,-1)
        - 2.4674011002723396e+00*HX2(0,-1)
        + 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1)
        - HX4(0, -1,-1,1)
        + HX4(0, -1,0,1)
        + HX4(0,0, -1,1)
        - HX4(0,0,0,1);
      HY4(0,-1,1,-1) =
        - 8.5266539820739622e+00
        - 5.5241438124578482e+00*HX1(0)
        - 1.2337005501361698e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        + HX1(0) *HX3(0,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX3(0,0,1)
        + 2.4674011002723396e+00*HX2(0,-1)
        - 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1)
        - HX4(0, -1,0,1)
        - HX4(0, -1,1,-1)
        + 2.0000000000000000e+00*HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX4(0,0,-1,1)
        + 4.0000000000000000e+00*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1, -1);
      HY4(0,1,-1,-1) =
        + 5.8027584430066521e+00
        + 2.7620719062289241e+00*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        + HX1(0) *HX3(0,0,-1)
        + 2.0000000000000000e+00*HX1(0)*HX3(0,0,1)
        + HX1(0) *HX3(0,1,-1)
        - HX4(0,0, -1,-1)
        - 2.0000000000000000e+00*HX4(0,0,0,-1)
        - 3.0000000000000000e+00*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,1,-1)
        - HX4(0,1, -1,-1);
      HY4(0,-1,1,1) =
        + 6.2689427375197987e-01
        - 2.7620719062289241e+00*HX1(0)
        - 2.4674011002723396e+00*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - HX1(0) *HX3(0,-1,1)
        + 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX3(0,0,1)
        + 4.9348022005446793e+00*HX2(0,-1)
        - HX4(0, -1,1,1)
        + 2.0000000000000000e+00*HX4(0,0,-1,1)
        - 3.0000000000000000e+00*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1,1);
      HY4(0,1,-1,1) =
        - 4.3326514514433017e+00
        - 1.3169446513992682e+00*HX1(0)
        - 1.2337005501361698e+00*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        - HX1(0) *HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,1)
        - HX1(0) *HX3(0,1,-1)
        + HX2(0, -1)*HX2(0,1)
        - 2.4674011002723396e+00*HX2(0,1)
        + 5.0000000000000000e-01*HX2(0,1)*HX2(0,1)
        - HX4(0, -1,0,1)
        - 3.0000000000000000e+00*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1)
        + 4.0000000000000000e+00*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,1,1)
        - HX4(0,1, -1,1);
      HY4(0,1,1,-1) =
        - 1.5001934240460787e-01
        + 4.0790165576281924e+00*HX1(0)
        + 1.2337005501361698e+00*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        - HX1(0) *HX3(0,0,1)
        + HX1(0) *HX3(0,1,1)
        - HX2(0, -1)*HX2(0,1)
        + 2.4674011002723396e+00*HX2(0,1)
        - 5.0000000000000000e-01*HX2(0,1)*HX2(0,1)
        + HX4(0, -1,0,1)
        + 2.0000000000000000e+00*HX4(0,0,-1,1)
        - HX4(0,0,0, -1)
        + HX4(0,0,1, -1)
        - HX4(0,1,1, -1);
      HY4(-1,-1,-1,1) =
        + 2.4278628067547031e+00
        - 2.7620719062289241e+00*HX1(-1)
        + 1.2337005501361698e+00*HX1(-1)*HX1(-1)
        + 1.6666666666666666e-01*HX1(-1)*HX1(-1)*HX1(-1)*HX1(0)
        - 2.5000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX2(0,1)
        - 2.4674011002723396e+00*HX1(-1)*HX1(0)
        + 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + HX1( -1)*HX3(0,-1,-1)
        + HX1( -1)*HX3(0,0,-1)
        + HX1( -1)*HX3(0,0,1)
        + HX1( -1)*HX3(0,1,-1)
        + 2.7620719062289241e+00*HX1(0)
        + 1.2337005501361698e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX4( -1,-1,-1,1)
        - HX4(0, -1,-1,-1)
        - HX4(0,0, -1,-1)
        - HX4(0,0,0, -1)
        - HX4(0,0,0,1)
        - HX4(0,0,1, -1)
        - HX4(0,1, -1,-1);
      HY4(-1,-1,1,1) =
        + 2.0293560632083841e+00
        + 2.7620719062289241e+00*HX1(-1)
        - 2.4674011002723396e+00*HX1(-1)*HX1(-1)
        + 2.5000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        + 4.9348022005446793e+00*HX1(-1)*HX1(0)
        - 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        - HX1( -1)*HX1(0)*HX2(0,-1)
        - HX1( -1)*HX1(0)*HX2(0,1)
        - HX1( -1)*HX3(0,-1,1)
        + HX1( -1)*HX3(0,0,-1)
        + HX1( -1)*HX3(0,0,1)
        - HX1( -1)*HX3(0,1,1)
        - 2.7620719062289241e+00*HX1(0)
        - 2.4674011002723396e+00*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX3(-1,-1,1)
        + HX1(0) *HX3(0,-1,-1)
        + HX1(0) *HX3(0,0,-1)
        + HX1(0) *HX3(0,0,1)
        + HX1(0) *HX3(0,1,-1)
        + HX4( -1,-1,1,1)
        + HX4(0, -1,-1,1)
        + HX4(0, -1,1,-1)
        - HX4(0,0, -1,-1)
        + HX4(0,0, -1,1)
        - 2.0000000000000000e+00*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX4(0,0,0,1)
        - HX4(0,0,1, -1)
        + HX4(0,0,1,1)
        + HX4(0,1, -1,1)
        + HX4(0,1,1, -1);
      HY4(-1,1,1,1) =
        - 6.4865749331714713e+00
        - 4.9348022005446793e+00*HX1(-1)*HX1(0)
        + 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + 2.4674011002723396e+00*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(-1,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        + HX1(0) *HX3(-1,1,1)
        - HX1(0) *HX3(0,-1,1)
        + HX1(0) *HX3(0,0,-1)
        + HX1(0) *HX3(0,0,1)
        - HX1(0) *HX3(0,1,1)
        - 4.9348022005446793e+00*HX2(-1,1)
        + 4.9348022005446793e+00*HX2(0,-1)
        + 4.9348022005446793e+00*HX2(0,1)
        + HX4( -1,1,1,1)
        - HX4(0, -1,1,1)
        + HX4(0,0, -1,1)
        - HX4(0,0,0, -1)
        - HX4(0,0,0,1)
        + HX4(0,0,1,1)
        - HX4(0,1,1,1);
      Hi4(0,0,-1,1) =
        - 9.0154267736969571e-01
        - 8.2246703342411321e-01*HX1(0)
        - 3.4657359027997265e-01*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX3(0,0, -1);
      Hi4(0,0,1,-1) =
        + 3.4657359027997265e-01*HX1(0)*HX1(0);
      Hi4(0,-1,0,1) =
        + 1.8030853547393914e+00
        + 8.2246703342411321e-01*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(0,-1)
        - 2.0000000000000000e+00*HX3(0,0,-1);
      Hi4(0,-1,-1,1) =
        + 4.8170908494321862e-01
        - 2.4022650695910071e-01*HX1(0)
        - 3.4657359027997265e-01*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(0,-1)
        + 6.9314718055994530e-01*HX2(0,-1)
        - HX3(0, -1,-1)
        - HX3(0,0, -1);
      Hi4(0,-1,1,-1) =
        + 5.7009070532142637e-01
        + 4.8045301391820142e-01*HX1(0)
        + 3.4657359027997265e-01*HX1(0)*HX1(0)
        - 6.9314718055994530e-01*HX2(0,-1);
      Hi4(0,1,-1,-1) =
        - 2.4022650695910071e-01*HX1(0);
      Hi4(0,-1,1,1) =
        - 2.7620719062289241e+00
        - 1.8851605738073271e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX2(0,-1)
        - HX3(0, -1,1)
        + 2.0000000000000000e+00*HX3(0,0,-1)
        + HX3(0,0,1);
      Hi4(0,1,-1,1) =
        + 2.6736902858507163e+00
        + 1.3029200473423146e+00*HX1(0)
        + 3.4657359027997265e-01*HX1(0)*HX1(0)
        + 1.6666666666666665e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(0,1)
        + 6.9314718055994530e-01*HX2(0,1)
        - HX3(0,0, -1)
        - 2.0000000000000000e+00*HX3(0,0,1)
        - HX3(0,1, -1);
      Hi4(0,1,1,-1) =
        + 1.1401814106428527e+00
        + 5.8224052646501250e-01*HX1(0)
        - 3.4657359027997265e-01*HX1(0)*HX1(0)
        - 6.9314718055994530e-01*HX2(0,1);
      Hi4(-1,-1,-1,1) =
        - 5.5504108664821579e-02
        + 2.4022650695910071e-01*HX1(-1)
        - 3.4657359027997265e-01*HX1(-1)*HX1(-1)
        + 1.6666666666666666e-01*HX1(-1)*HX1(-1)*HX1(-1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)
        + 6.9314718055994530e-01*HX1(-1)*HX1(0)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)
        - 2.4022650695910071e-01*HX1(0)
        - 3.4657359027997265e-01*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0);
      Hi4(-1,-1,1,1) =
        - 2.4532465311320902e+00
        + 1.8851605738073271e+00*HX1(-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)
        - 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)
        - HX1( -1)*HX2(0,-1)
        - HX1( -1)*HX2(0,1)
        - 1.8851605738073271e+00*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX3( -1,-1,1)
        + HX3(0, -1,-1)
        + HX3(0,0, -1)
        + HX3(0,0,1)
        + HX3(0,1, -1);
      Hi4(-1,1,1,1) =
        - 5.5504108664821579e-02
        - 1.6449340668482264e+00*HX1(-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)
        + 1.6449340668482264e+00*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX2(-1,1)
        - HX1(0) *HX2(0,-1)
        - HX1(0) *HX2(0,1)
        + HX3( -1,1,1)
        - HX3(0, -1,1)
        + HX3(0,0, -1)
        + HX3(0,0,1)
        - HX3(0,1,1);
    }

    if ( nw > 4 ){
      HY5(-1,-1,-1,-1,1) =
        - 2.1900870176160439e+00
        + 2.4278628067547031e+00*HX1(-1)
        - 1.3810359531144620e+00*HX1(-1)*HX1(-1)
        + 4.1123351671205660e-01*HX1(-1)*HX1(-1)*HX1(-1)
        + 4.1666666666666666e-02*HX1(-1)*HX1(-1)*HX1(-1)*HX1(-1)*HX1(0)
        - 8.3333333333333333e-02*HX1(-1)*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(-1)*HX1(-1)*HX1(-1)*HX2(0,-1)
        - 1.6666666666666666e-01*HX1(-1)*HX1(-1)*HX1(-1)*HX2(0,1)
        - 1.2337005501361698e+00*HX1(-1)*HX1(-1)*HX1(0)
        + 8.3333333333333333e-02*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,-1,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,1,-1)
        + 2.7620719062289241e+00*HX1(-1)*HX1(0)
        + 1.2337005501361698e+00*HX1(-1)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(-1)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1( -1)*HX4(0,-1,-1,-1)
        - HX1( -1)*HX4(0,0,-1,-1)
        - HX1( -1)*HX4(0,0,0,-1)
        - HX1( -1)*HX4(0,0,0,1)
        - HX1( -1)*HX4(0,0,1,-1)
        - HX1( -1)*HX4(0,1,-1,-1)
        - 2.4278628067547031e+00*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX5( -1,-1,-1,-1,1)
        + HX5(0, -1,-1,-1,-1)
        + HX5(0,0, -1,-1,-1)
        + HX5(0,0,0, -1,-1)
        + HX5(0,0,0,0, -1)
        + HX5(0,0,0,0,1)
        + HX5(0,0,0,1, -1)
        + HX5(0,0,1, -1,-1)
        + HX5(0,1, -1,-1,-1);
      HY5(-1,-1,-1,1,1) =
        - 5.5581622138319701e+00
        + 2.0293560632083841e+00*HX1(-1)
        + 1.3810359531144620e+00*HX1(-1)*HX1(-1)
        - 8.2246703342411321e-01*HX1(-1)*HX1(-1)*HX1(-1)
        + 8.3333333333333333e-02*HX1(-1)*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        + 2.4674011002723396e+00*HX1(-1)*HX1(-1)*HX1(0)
        - 8.3333333333333333e-02*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,-1,1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX3(0,1,1)
        - 2.7620719062289241e+00*HX1(-1)*HX1(0)
        - 2.4674011002723396e+00*HX1(-1)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(-1)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1( -1)*HX1(0)*HX3(0,-1,-1)
        + HX1( -1)*HX1(0)*HX3(0,0,-1)
        + HX1( -1)*HX1(0)*HX3(0,0,1)
        + HX1( -1)*HX1(0)*HX3(0,1,-1)
        + HX1( -1)*HX4(0,-1,-1,1)
        + HX1( -1)*HX4(0,-1,1,-1)
        - HX1( -1)*HX4(0,0,-1,-1)
        + HX1( -1)*HX4(0,0,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,0,0,1)
        - HX1( -1)*HX4(0,0,1,-1)
        + HX1( -1)*HX4(0,0,1,1)
        + HX1( -1)*HX4(0,1,-1,1)
        + HX1( -1)*HX4(0,1,1,-1)
        - 2.0293560632083841e+00*HX1(0)
        + 1.3810359531144620e+00*HX1(0)*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX4(-1,-1,-1,1)
        - HX1(0) *HX4(0,-1,-1,-1)
        - HX1(0) *HX4(0,0,-1,-1)
        - HX1(0) *HX4(0,0,0,-1)
        - HX1(0) *HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,-1)
        - HX1(0) *HX4(0,1,-1,-1)
        + HX5( -1,-1,-1,1,1)
        - HX5(0, -1,-1,-1,1)
        - HX5(0, -1,-1,1,-1)
        - HX5(0, -1,1,-1,-1)
        + HX5(0,0, -1,-1,-1)
        - HX5(0,0, -1,-1,1)
        - HX5(0,0, -1,1,-1)
        + 2.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - HX5(0,0,0, -1,1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        + 2.0000000000000000e+00*HX5(0,0,0,1,-1)
        - HX5(0,0,0,1,1)
        + HX5(0,0,1, -1,-1)
        - HX5(0,0,1, -1,1)
        - HX5(0,0,1,1, -1)
        - HX5(0,1, -1,-1,1)
        - HX5(0,1, -1,1,-1)
        - HX5(0,1,1, -1,-1);
      HY5(-1,-1,1,-1,1) =
        + 9.2329419831013177e+00
        - 3.3856186219460558e+00*HX1(-1)
        + 6.5847232569963413e-01*HX1(-1)*HX1(-1)
        + 1.2337005501361698e+00*HX1(-1)*HX1(-1)*HX1(0)
        - 8.3333333333333333e-02*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX2(0,1)
        + HX1( -1)*HX1(-1)*HX3(0,-1,1)
        - HX1( -1)*HX1(-1)*HX3(0,0,-1)
        - HX1( -1)*HX1(-1)*HX3(0,0,1)
        + HX1( -1)*HX1(-1)*HX3(0,1,1)
        - 1.3169446513992682e+00*HX1(-1)*HX1(0)
        - 1.2337005501361698e+00*HX1(-1)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(-1)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(0,1)
        + HX1( -1)*HX1(0)*HX3(-1,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,-1,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,0,1)
        - 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,1,-1)
        - 2.4674011002723396e+00*HX1(-1)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX2(0,-1)*HX2(0,-1)
        + HX1( -1)*HX2(0,-1)*HX2(0,1)
        - 2.4674011002723396e+00*HX1(-1)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(-1)*HX2(0,1)*HX2(0,1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,-1,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,-1,1,-1)
        + 2.0000000000000000e+00*HX1(-1)*HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,0,-1,1)
        + 4.0000000000000000e+00*HX1(-1)*HX4(0,0,0,-1)
        + 4.0000000000000000e+00*HX1(-1)*HX4(0,0,0,1)
        + 2.0000000000000000e+00*HX1(-1)*HX4(0,0,1,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,0,1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,1,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX4(0,1,1,-1)
        + 3.3856186219460558e+00*HX1(0)
        + 6.5847232569963413e-01*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(-1,-1,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,-1)
        - 3.0000000000000000e+00*HX1(0)*HX4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,-1,-1,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,-1,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,1,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,1,-1,-1)
        - HX2(0, -1)*HX3(-1,-1,1)
        - HX2(0, -1)*HX3(0,-1,-1)
        - HX2(0, -1)*HX3(0,1,-1)
        - HX2(0,1) *HX3(-1,-1,1)
        - HX2(0,1) *HX3(0,1,-1)
        + 2.4674011002723396e+00*HX3(-1,-1,1)
        + 2.4674011002723396e+00*HX3(0,-1,-1)
        + 2.4674011002723396e+00*HX3(0,0,-1)
        + 2.4674011002723396e+00*HX3(0,0,1)
        + 2.4674011002723396e+00*HX3(0,1,-1)
        + HX5( -1,-1,1,-1,1)
        + 3.0000000000000000e+00*HX5(0,-1,-1,-1,1)
        - HX5(0, -1,-1,0,1)
        + 2.0000000000000000e+00*HX5(0,-1,-1,1,-1)
        + HX5(0, -1,0,-1,-1)
        - HX5(0, -1,0,-1,1)
        + 2.0000000000000000e+00*HX5(0,-1,1,-1,-1)
        + HX5(0,0, -1,-1,1)
        - HX5(0,0, -1,0,-1)
        - HX5(0,0, -1,0,1)
        + 2.0000000000000000e+00*HX5(0,0,-1,1,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        - 7.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 2.0000000000000000e+00*HX5(0,0,1,-1,-1)
        + 3.0000000000000000e+00*HX5(0,0,1,-1,1)
        - HX5(0,0,1,0, -1)
        - HX5(0,0,1,0,1)
        + 4.0000000000000000e+00*HX5(0,0,1,1,-1)
        + 3.0000000000000000e+00*HX5(0,1,-1,-1,1)
        + 2.0000000000000000e+00*HX5(0,1,-1,1,-1)
        + HX5(0,1,0,1, -1)
        + 2.0000000000000000e+00*HX5(0,1,1,-1,-1);
      HY5(-1,-1,1,1,1) =
        + 5.5581622138319701e+00
        - 6.4865749331714713e+00*HX1(-1)
        - 2.4674011002723396e+00*HX1(-1)*HX1(-1)*HX1(0)
        + 8.3333333333333333e-02*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + 2.4674011002723396e+00*HX1(-1)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(-1)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(0,1)
        - HX1( -1)*HX1(0)*HX3(0,-1,1)
        + HX1( -1)*HX1(0)*HX3(0,0,-1)
        + HX1( -1)*HX1(0)*HX3(0,0,1)
        - HX1( -1)*HX1(0)*HX3(0,1,1)
        + 4.9348022005446793e+00*HX1(-1)*HX2(0,-1)
        + 4.9348022005446793e+00*HX1(-1)*HX2(0,1)
        - HX1( -1)*HX4(0,-1,1,1)
        + HX1( -1)*HX4(0,0,-1,1)
        - HX1( -1)*HX4(0,0,0,-1)
        - HX1( -1)*HX4(0,0,0,1)
        + HX1( -1)*HX4(0,0,1,1)
        - HX1( -1)*HX4(0,1,1,1)
        + 6.4865749331714713e+00*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(-1,-1,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,-1)
        + HX1(0) *HX4(-1,-1,1,1)
        + HX1(0) *HX4(0,-1,-1,1)
        + HX1(0) *HX4(0,-1,1,-1)
        - HX1(0) *HX4(0,0,-1,-1)
        + HX1(0) *HX4(0,0,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,-1)
        + HX1(0) *HX4(0,0,1,1)
        + HX1(0) *HX4(0,1,-1,1)
        + HX1(0) *HX4(0,1,1,-1)
        - 4.9348022005446793e+00*HX3(-1,-1,1)
        - 4.9348022005446793e+00*HX3(0,-1,-1)
        - 4.9348022005446793e+00*HX3(0,0,-1)
        - 4.9348022005446793e+00*HX3(0,0,1)
        - 4.9348022005446793e+00*HX3(0,1,-1)
        + HX5( -1,-1,1,1,1)
        + HX5(0, -1,-1,1,1)
        + HX5(0, -1,1,-1,1)
        + HX5(0, -1,1,1,-1)
        - HX5(0,0, -1,-1,1)
        - HX5(0,0, -1,1,-1)
        + HX5(0,0, -1,1,1)
        + HX5(0,0,0, -1,-1)
        - 2.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        + HX5(0,0,0,1, -1)
        - 2.0000000000000000e+00*HX5(0,0,0,1,1)
        - HX5(0,0,1, -1,1)
        - HX5(0,0,1,1, -1)
        + HX5(0,0,1,1,1)
        + HX5(0,1, -1,1,1)
        + HX5(0,1,1, -1,1)
        + HX5(0,1,1,1, -1);
      HY5(-1,1,-1,1,1) =
        - 7.7439193717015657e-01
        + 8.5393570350547734e-01*HX1(-1)
        + 2.7620719062289241e+00*HX1(-1)*HX1(0)
        + 2.4674011002723396e+00*HX1(-1)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(-1)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(-1,1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(0)*HX1(0)*HX2(0,1)
        + 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,0,1)
        + 2.0000000000000000e+00*HX1(-1)*HX1(0)*HX3(0,1,1)
        - 4.9348022005446793e+00*HX1(-1)*HX2(-1,1)
        - 4.9348022005446793e+00*HX1(-1)*HX2(0,-1)
        - 4.9348022005446793e+00*HX1(-1)*HX2(0,1)
        + 3.0000000000000000e+00*HX1(-1)*HX4(0,-1,1,1)
        - 3.0000000000000000e+00*HX1(-1)*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX1(-1)*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX1(-1)*HX4(0,0,0,1)
        - 3.0000000000000000e+00*HX1(-1)*HX4(0,0,1,1)
        + 3.0000000000000000e+00*HX1(-1)*HX4(0,1,1,1)
        - 8.5393570350547734e-01*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(-1,1)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        - HX1(0) *HX1(0)*HX3(-1,-1,1)
        - HX1(0) *HX1(0)*HX3(0,-1,-1)
        - HX1(0) *HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX1(0)*HX3(0,0,1)
        - HX1(0) *HX1(0)*HX3(0,1,-1)
        + 4.9348022005446793e+00*HX1(0)*HX2(-1,1)
        + 5.0000000000000000e-01*HX1(0)*HX2(-1,1)*HX2(-1,1)
        - HX1(0) *HX2(-1,1)*HX2(0,-1)
        - HX1(0) *HX2(-1,1)*HX2(0,1)
        - 4.9348022005446793e+00*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        + HX1(0) *HX2(0,-1)*HX2(0,1)
        - 4.9348022005446793e+00*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(-1,-1,1,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,-1,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,-1,1,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        + 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,1,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,1,1,-1)
        + 2.7620719062289241e+00*HX2(-1,1)
        - HX2( -1,1)*HX3(0,-1,1)
        + HX2( -1,1)*HX3(0,0,-1)
        + HX2( -1,1)*HX3(0,0,1)
        - HX2( -1,1)*HX3(0,1,1)
        - 2.7620719062289241e+00*HX2(0,-1)
        - HX2(0, -1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        - 2.7620719062289241e+00*HX2(0,1)
        + HX2(0,1) *HX3(0,-1,1)
        - HX2(0,1) *HX3(0,0,-1)
        - HX2(0,1) *HX3(0,0,1)
        + 9.8696044010893586e+00*HX3(-1,-1,1)
        + 9.8696044010893586e+00*HX3(0,-1,-1)
        + 9.8696044010893586e+00*HX3(0,0,-1)
        + 9.8696044010893586e+00*HX3(0,0,1)
        + 9.8696044010893586e+00*HX3(0,1,-1)
        + HX5( -1,1,-1,1,1)
        - 2.0000000000000000e+00*HX5(0,-1,-1,1,1)
        + HX5(0, -1,0,-1,1)
        - HX5(0, -1,0,1,1)
        - 2.0000000000000000e+00*HX5(0,-1,1,-1,1)
        - HX5(0, -1,1,0,1)
        - 3.0000000000000000e+00*HX5(0,-1,1,1,-1)
        + 4.0000000000000000e+00*HX5(0,0,-1,-1,1)
        + HX5(0,0, -1,0,-1)
        + HX5(0,0, -1,0,1)
        + 3.0000000000000000e+00*HX5(0,0,-1,1,-1)
        - 4.0000000000000000e+00*HX5(0,0,-1,1,1)
        + 7.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        + 7.0000000000000000e+00*HX5(0,0,0,1,1)
        + 2.0000000000000000e+00*HX5(0,0,1,-1,1)
        + HX5(0,0,1,0, -1)
        + HX5(0,0,1,0,1)
        + 3.0000000000000000e+00*HX5(0,0,1,1,-1)
        - 2.0000000000000000e+00*HX5(0,1,-1,1,1)
        + HX5(0,1,0,1,1)
        - 2.0000000000000000e+00*HX5(0,1,1,-1,1)
        - 3.0000000000000000e+00*HX5(0,1,1,1,-1);
      HY5(-1,1,1,1,1) =
        + 2.1900870176160439e+00
        + 4.0587121264167682e+00*HX1(-1)
        - 2.4674011002723396e+00*HX1(-1)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(-1)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 4.0587121264167682e+00*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(-1,1)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(-1,1,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,1)
        - 4.9348022005446793e+00*HX1(0)*HX2(-1,1)
        + 4.9348022005446793e+00*HX1(0)*HX2(0,-1)
        + 4.9348022005446793e+00*HX1(0)*HX2(0,1)
        + HX1(0) *HX4(-1,1,1,1)
        - HX1(0) *HX4(0,-1,1,1)
        + HX1(0) *HX4(0,0,-1,1)
        - HX1(0) *HX4(0,0,0,-1)
        - HX1(0) *HX4(0,0,0,1)
        + HX1(0) *HX4(0,0,1,1)
        - HX1(0) *HX4(0,1,1,1)
        - 4.9348022005446793e+00*HX3(-1,1,1)
        + 4.9348022005446793e+00*HX3(0,-1,1)
        - 4.9348022005446793e+00*HX3(0,0,-1)
        - 4.9348022005446793e+00*HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,1,1)
        + HX5( -1,1,1,1,1)
        - HX5(0, -1,1,1,1)
        + HX5(0,0, -1,1,1)
        - HX5(0,0,0, -1,1)
        + HX5(0,0,0,0, -1)
        + HX5(0,0,0,0,1)
        - HX5(0,0,0,1,1)
        + HX5(0,0,1,1,1)
        - HX5(0,1,1,1,1);
      HY5(0,-1,-1,-1,1) =
        - 2.1501021594785064e+00
        - 2.4278628067547031e+00*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + 2.4674011002723396e+00*HX1(0)*HX2(0,-1)
        - HX1(0) *HX4(0,-1,-1,-1)
        - HX1(0) *HX4(0,0,-1,-1)
        - HX1(0) *HX4(0,0,0,-1)
        + 2.7620719062289241e+00*HX2(0,-1)
        + HX2(0, -1)*HX3(0,-1,-1)
        - HX2(0, -1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        - 2.4674011002723396e+00*HX3(0,-1,-1)
        - 2.4674011002723396e+00*HX3(0,0,-1)
        - HX5(0, -1,-1,-1,1)
        + HX5(0, -1,-1,0,1)
        - 2.0000000000000000e+00*HX5(0,-1,0,-1,-1)
        + HX5(0, -1,0,-1,1)
        - 4.0000000000000000e+00*HX5(0,0,-1,-1,-1)
        + HX5(0,0, -1,-1,1)
        + 2.0000000000000000e+00*HX5(0,0,-1,0,-1)
        + HX5(0,0, -1,0,1)
        + 6.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 2.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 2.0000000000000000e+00*HX5(0,0,0,0,-1)
        + HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1,0, -1);
      HY5(0,-1,-1,0,1) =
        + 2.6781232869596824e+00
        + 2.0293560632083841e-01*HX1(0)
        - 9.0154267736969571e-01*HX1(0)*HX1(0)
        - 5.4831135561607547e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + 3.2898681336964528e+00*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        + 1.8030853547393914e+00*HX2(0,-1)
        + HX2(0, -1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        - 3.2898681336964528e+00*HX3(0,-1,-1)
        - 3.2898681336964528e+00*HX3(0,0,-1)
        + HX5(0, -1,-1,0,1)
        - HX5(0,0, -1,0,-1)
        + HX5(0,0, -1,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 2.0000000000000000e+00*HX5(0,0,0,0,-1)
        + HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1,0, -1);
      HY5(0,-1,-1,1,-1) =
        + 7.5170363885043517e+00
        + 7.2835884202641093e+00*HX1(0)
        + 2.7620719062289241e+00*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - 2.4674011002723396e+00*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        + HX1(0) *HX4(0,-1,-1,1)
        - HX1(0) *HX4(0,-1,0,1)
        - HX1(0) *HX4(0,0,-1,1)
        + HX1(0) *HX4(0,0,0,1)
        - 5.5241438124578482e+00*HX2(0,-1)
        - HX2(0, -1)*HX3(0,-1,-1)
        + 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,-1)
        + 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,1)
        + 2.4674011002723396e+00*HX3(0,-1,-1)
        + 2.4674011002723396e+00*HX3(0,0,-1)
        - HX5(0, -1,-1,0,1)
        - HX5(0, -1,-1,1,-1)
        + 3.0000000000000000e+00*HX5(0,-1,0,-1,-1)
        - HX5(0, -1,0,-1,1)
        + HX5(0, -1,0,1,-1)
        + 6.0000000000000000e+00*HX5(0,0,-1,-1,-1)
        - 2.0000000000000000e+00*HX5(0,0,-1,-1,1)
        - 3.0000000000000000e+00*HX5(0,0,-1,0,-1)
        - HX5(0,0, -1,0,1)
        + HX5(0,0, -1,1,-1)
        - 9.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,1)
        - 7.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 2.0000000000000000e+00*HX5(0,0,1,0,-1);
      HY5(0,-1,-1,1,1) =
        - 6.8749092010391177e+00
        - 2.0293560632083841e+00*HX1(0)
        + 1.3810359531144620e+00*HX1(0)*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - 4.9348022005446793e+00*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        - HX1(0) *HX4(0,-1,-1,1)
        + HX1(0) *HX4(0,-1,0,1)
        + HX1(0) *HX4(0,0,-1,1)
        - HX1(0) *HX4(0,0,0,1)
        - 2.7620719062289241e+00*HX2(0,-1)
        - HX2(0, -1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,-1,-1)
        + 4.9348022005446793e+00*HX3(0,0,-1)
        - HX5(0, -1,-1,1,1)
        + HX5(0, -1,0,-1,1)
        + HX5(0, -1,0,1,1)
        + 2.0000000000000000e+00*HX5(0,0,-1,-1,1)
        + HX5(0,0, -1,0,-1)
        + HX5(0,0, -1,1,1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 2.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        - HX5(0,0,0,1,1)
        + HX5(0,0,1,0, -1);
      HY5(0,-1,0,-1,1) =
        - 5.6642178198849788e+00
        - 3.4847341165810188e+00*HX1(0)
        - 1.2595007772794312e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + HX1(0) *HX1(0)*HX3(0,0,-1)
        + 2.4674011002723396e+00*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,-1)
        - 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 2.5190015545588625e+00*HX2(0,-1)
        - 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        - 4.9348022005446793e+00*HX3(0,0,-1)
        + HX5(0, -1,0,-1,1)
        + 4.0000000000000000e+00*HX5(0,0,-1,0,-1)
        + 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        + 1.2000000000000000e+01*HX5(0,0,0,-1,-1)
        + 2.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 8.0000000000000000e+00*HX5(0,0,0,0,-1)
        + HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1,0, -1);
      HY5(0,-1,0,1,-1) =
        - 3.4903562040510891e-01
        + 3.0788629039393420e+00*HX1(0)
        + 2.1610434546491269e+00*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + HX1(0) *HX1(0)*HX3(0,0,-1)
        - 2.4674011002723396e+00*HX1(0)*HX2(0,-1)
        - HX1(0) *HX4(0,-1,0,1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + HX1(0) *HX4(0,0,0,1)
        - 4.3220869092982539e+00*HX2(0,-1)
        + HX2(0, -1)*HX3(0,0,-1)
        + 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,0,-1)
        + HX5(0, -1,0,1,-1)
        - 3.0000000000000000e+00*HX5(0,0,-1,0,-1)
        - 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        - 6.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - 6.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,1)
        - 7.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 2.0000000000000000e+00*HX5(0,0,1,0,-1);
      HY5(0,-1,0,1,1) =
        - 6.6327319875542747e+00
        - 3.8557765200959298e+00*HX1(0)
        + 6.0102845157979714e-01*HX1(0)*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - HX1(0) *HX1(0)*HX3(0,0,-1)
        - 4.9348022005446793e+00*HX1(0)*HX2(0,-1)
        + HX1(0) *HX4(0,-1,0,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - HX1(0) *HX4(0,0,0,1)
        - 1.2020569031595942e+00*HX2(0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        + 9.8696044010893586e+00*HX3(0,0,-1)
        + HX5(0, -1,0,1,1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        - HX5(0,0,0,1,1)
        + HX5(0,0,1,0, -1);
      HY5(0,-1,1,-1,-1) =
        - 1.4571792178347941e+01
        - 7.2835884202641093e+00*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,1)
        + HX1(0) *HX1(0)*HX3(0,0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        + HX1(0) *HX4(0,-1,0,1)
        + HX1(0) *HX4(0,-1,1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        - 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,-1)
        + 2.7620719062289241e+00*HX2(0,-1)
        - HX2(0, -1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        - HX5(0, -1,0,-1,-1)
        - HX5(0, -1,0,1,-1)
        - HX5(0, -1,1,-1,-1)
        + HX5(0,0, -1,0,-1)
        - 2.0000000000000000e+00*HX5(0,0,-1,1,-1)
        + 7.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 7.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 6.0000000000000000e+00*HX5(0,0,0,0,1)
        + 6.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1, -1,-1)
        + HX5(0,0,1,0, -1);
      HY5(0,-1,1,-1,1) =
        + 8.4053642852001231e+00
        + 3.3856186219460558e+00*HX1(0)
        + 6.5847232569963413e-01*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,1)
        - HX1(0) *HX1(0)*HX3(0,0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 2.4674011002723396e+00*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,-1)*HX2(0,-1)
        - HX1(0) *HX4(0,-1,0,1)
        - HX1(0) *HX4(0,-1,1,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        + 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + HX1(0) *HX4(0,0,1,-1)
        - 1.3169446513992682e+00*HX2(0,-1)
        + HX2(0, -1)*HX3(0,-1,1)
        + 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,-1)
        + 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,1)
        - 2.4674011002723396e+00*HX3(0,-1,1)
        + 4.9348022005446793e+00*HX3(0,0,-1)
        + 2.4674011002723396e+00*HX3(0,0,1)
        - 3.0000000000000000e+00*HX5(0,-1,0,-1,1)
        - HX5(0, -1,1,-1,1)
        + HX5(0, -1,1,0,1)
        - 4.0000000000000000e+00*HX5(0,0,-1,-1,1)
        - 4.0000000000000000e+00*HX5(0,0,-1,0,-1)
        - 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        - 1.2000000000000000e+01*HX5(0,0,0,-1,-1)
        - 2.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 8.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        - 9.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1, -1,1)
        - 3.0000000000000000e+00*HX5(0,0,1,0,-1)
        - HX5(0,0,1,0,1);
      HY5(0,-1,1,0,1) =
        - 4.5667800194983164e-01
        - 3.4847341165810188e+00*HX1(0)
        - 1.2020569031595942e+00*HX1(0)*HX1(0)
        + 5.4831135561607547e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,1)
        - HX1(0) *HX1(0)*HX3(0,0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 3.2898681336964528e+00*HX1(0)*HX2(0,-1)
        - HX1(0) *HX4(0,-1,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 2.4041138063191885e+00*HX2(0,-1)
        + 2.0000000000000000e+00*HX2(0,-1)*HX3(0,0,1)
        - 3.2898681336964528e+00*HX3(0,-1,1)
        + 6.5797362673929057e+00*HX3(0,0,-1)
        + 3.2898681336964528e+00*HX3(0,0,1)
        + HX5(0, -1,1,0,1)
        - 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        - 6.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 2.0000000000000000e+00*HX5(0,0,1,0,-1)
        - HX5(0,0,1,0,1);
      HY5(0,-1,1,1,-1) =
        + 8.0778313134277241e+00
        + 6.7309350447071233e-01*HX1(0)
        - 2.0395082788140962e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,1)
        - HX1(0) *HX1(0)*HX3(0,0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 2.4674011002723396e+00*HX1(0)*HX2(0,-1)
        + HX1(0) *HX4(0,-1,1,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,1)
        + 4.0790165576281924e+00*HX2(0,-1)
        - HX2(0, -1)*HX3(0,-1,1)
        - HX2(0, -1)*HX3(0,0,-1)
        - HX2(0, -1)*HX3(0,0,1)
        + 2.4674011002723396e+00*HX3(0,-1,1)
        - 4.9348022005446793e+00*HX3(0,0,-1)
        - 2.4674011002723396e+00*HX3(0,0,1)
        + 2.0000000000000000e+00*HX5(0,-1,0,-1,1)
        - HX5(0, -1,0,1,1)
        - HX5(0, -1,1,0,1)
        - HX5(0, -1,1,1,-1)
        + 4.0000000000000000e+00*HX5(0,0,-1,-1,1)
        + 3.0000000000000000e+00*HX5(0,0,-1,0,-1)
        + 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        + 2.0000000000000000e+00*HX5(0,0,-1,1,-1)
        - 2.0000000000000000e+00*HX5(0,0,-1,1,1)
        + 6.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 6.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 2.0000000000000000e+00*HX5(0,0,0,0,1)
        + 4.0000000000000000e+00*HX5(0,0,0,1,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,1)
        + 2.0000000000000000e+00*HX5(0,0,1,0,-1)
        + HX5(0,0,1,0,1)
        + HX5(0,0,1,1, -1);
      HY5(0,-1,1,1,1) =
        + 6.9367501878022481e+00
        + 6.4865749331714713e+00*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,-1,1)
        + HX1(0) *HX1(0)*HX3(0,0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 4.9348022005446793e+00*HX1(0)*HX2(0,-1)
        - HX1(0) *HX4(0,-1,1,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + HX1(0) *HX4(0,0,1,1)
        + 4.9348022005446793e+00*HX3(0,-1,1)
        - 9.8696044010893586e+00*HX3(0,0,-1)
        - 4.9348022005446793e+00*HX3(0,0,1)
        - HX5(0, -1,1,1,1)
        + 2.0000000000000000e+00*HX5(0,0,-1,1,1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 4.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        - 2.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1,1,1);
      HY5(0,0,-1,-1,1) =
        - 9.1165552893555038e-01
        - 2.5209599327464717e+00*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX4(0,0,-1,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 2.4674011002723396e+00*HX3(0,0,-1)
        + HX5(0,0, -1,-1,1)
        - HX5(0,0, -1,0,-1)
        - HX5(0,0, -1,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - HX5(0,0,0, -1,1)
        - 2.0000000000000000e+00*HX5(0,0,0,0,-1)
        + HX5(0,0,0,0,1);
      HY5(0,0,-1,0,-1) =
        - 8.1023197211680719e+00
        - 5.1410353601279064e+00*HX1(0)
        - 1.2020569031595942e+00*HX1(0)*HX1(0)
        - 2.7415567780803773e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 1.6449340668482264e+00*HX3(0,0,-1)
        - HX5(0,0, -1,0,-1)
        + 7.0000000000000000e+00*HX5(0,0,0,0,-1);
      HY5(0,0,-1,0,1) =
        + 2.0434339691042511e+00
        - 9.4703282949724591e-01*HX1(0)
        - 9.0154267736969571e-01*HX1(0)*HX1(0)
        - 5.4831135561607547e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 3.2898681336964528e+00*HX3(0,0,-1)
        - HX5(0,0, -1,0,1)
        - 6.0000000000000000e+00*HX5(0,0,0,0,-1)
        + HX5(0,0,0,0,1);
      HY5(0,0,-1,1,-1) =
        + 1.2874316759375889e+01
        + 8.5266539820739622e+00*HX1(0)
        + 2.7620719062289241e+00*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + HX1(0) *HX4(0,0,0,1)
        - 2.4674011002723396e+00*HX3(0,0,-1)
        + HX5(0,0, -1,0,-1)
        + HX5(0,0, -1,0,1)
        + HX5(0,0, -1,1,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,1)
        - HX5(0,0,0,1, -1);
      HY5(0,0,-1,1,1) =
        - 4.2205881177506120e+00
        - 6.2689427375197987e-01*HX1(0)
        + 1.3810359531144620e+00*HX1(0)*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX4(0,0,-1,1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - HX1(0) *HX4(0,0,0,1)
        - 4.9348022005446793e+00*HX3(0,0,-1)
        + HX5(0,0, -1,1,1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 6.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        - HX5(0,0,0,1,1);
      HY5(0,0,0,-1,1) =
        - 4.8071216221292780e+00
        - 3.9234217222028759e+00*HX1(0)
        - 1.2595007772794312e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX4(0,0,0,-1)
        - HX5(0,0,0, -1,1)
        + 4.0000000000000000e+00*HX5(0,0,0,0,-1)
        + HX5(0,0,0,0,1);
      HY5(0,0,0,1,-1) =
        + 5.2683829003001246e+00
        + 4.1940025306306604e+00*HX1(0)
        + 2.1610434546491269e+00*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX4(0,0,0,1)
        - HX5(0,0,0,0, -1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,1)
        - HX5(0,0,0,1, -1);
      HY5(0,0,1,-1,-1) =
        - 9.4096904031705199e+00
        - 5.8027584430066521e+00*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - HX1(0) *HX4(0,0,0,-1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,-1)
        + HX5(0,0,0, -1,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 6.0000000000000000e+00*HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1, -1,-1);
      HY5(0,0,1,-1,1) =
        + 8.7596705482058876e+00
        + 4.3326514514433017e+00*HX1(0)
        + 6.5847232569963413e-01*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + HX1(0) *HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + HX1(0) *HX4(0,0,1,-1)
        + 2.4674011002723396e+00*HX3(0,0,1)
        + HX5(0,0,0, -1,1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        + HX5(0,0,1, -1,1)
        - HX5(0,0,1,0, -1)
        - HX5(0,0,1,0,1);
      HY5(0,0,1,0,-1) =
        - 6.8544356072335814e+00
        - 5.0057449559140141e+00*HX1(0)
        - 9.0154267736969571e-01*HX1(0)*HX1(0)
        + 2.7415567780803773e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 1.6449340668482264e+00*HX3(0,0,1)
        - HX5(0,0,0,0, -1)
        + 6.0000000000000000e+00*HX5(0,0,0,0,1)
        - HX5(0,0,1,0, -1);
      HY5(0,0,1,1,-1) =
        + 3.2887945813357094e+00
        + 1.5001934240460787e-01*HX1(0)
        - 2.0395082788140962e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,1)
        - 2.4674011002723396e+00*HX3(0,0,1)
        + HX5(0,0,0,0, -1)
        - 2.0000000000000000e+00*HX5(0,0,0,0,1)
        + HX5(0,0,0,1, -1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1,0, -1)
        + HX5(0,0,1,0,1)
        + HX5(0,0,1,1, -1);
      HY5(0,1,-1,-1,-1) =
        + 7.4845537829591132e+00
        + 2.4278628067547031e+00*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX1(0)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,-1)
        + HX1(0) *HX4(0,0,-1,-1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,-1)
        + HX1(0) *HX4(0,1,-1,-1)
        - HX5(0,0, -1,-1,-1)
        - 2.0000000000000000e+00*HX5(0,0,0,-1,-1)
        - 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 4.0000000000000000e+00*HX5(0,0,0,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 2.0000000000000000e+00*HX5(0,0,1,-1,-1)
        - HX5(0,1, -1,-1,-1);
      HY5(0,1,-1,-1,1) =
        + 7.4122526767078634e-02
        + 3.0440340948125761e+00*HX1(0)
        + 1.3810359531144620e+00*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX1(0)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,-1)
        + 2.4674011002723396e+00*HX1(0)*HX2(0,1)
        - HX1(0) *HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,-1)
        - HX1(0) *HX4(0,1,-1,-1)
        + HX2(0, -1)*HX3(0,1,-1)
        + 2.7620719062289241e+00*HX2(0,1)
        - HX2(0,1) *HX3(0,-1,-1)
        - HX2(0,1) *HX3(0,0,-1)
        - HX2(0,1) *HX3(0,0,1)
        + HX2(0,1) *HX3(0,1,-1)
        - 2.4674011002723396e+00*HX3(0,0,-1)
        - 4.9348022005446793e+00*HX3(0,0,1)
        - 2.4674011002723396e+00*HX3(0,1,-1)
        + HX5(0, -1,-1,0,1)
        + HX5(0, -1,0,-1,1)
        + HX5(0,0, -1,-1,1)
        + HX5(0,0, -1,0,-1)
        + 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,-1)
        + 4.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 2.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        + 6.0000000000000000e+00*HX5(0,0,0,1,-1)
        + 6.0000000000000000e+00*HX5(0,0,0,1,1)
        - 2.0000000000000000e+00*HX5(0,0,1,-1,1)
        + 2.0000000000000000e+00*HX5(0,0,1,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,1,0,1)
        - 4.0000000000000000e+00*HX5(0,0,1,1,-1)
        - HX5(0,1, -1,-1,1)
        - 2.0000000000000000e+00*HX5(0,1,0,1,-1);
      HY5(0,1,-1,1,-1) =
        - 1.8385793928455058e+01
        - 9.4736868115712082e+00*HX1(0)
        - 2.7620719062289241e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX1(0)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,-1)
        - HX1(0) *HX2(0,-1)*HX2(0,1)
        - 2.4674011002723396e+00*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        + HX1(0) *HX4(0,-1,0,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        - 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,1)
        + HX1(0) *HX4(0,1,-1,1)
        - HX2(0, -1)*HX3(0,1,-1)
        - 5.5241438124578482e+00*HX2(0,1)
        + 2.0000000000000000e+00*HX2(0,1)*HX3(0,-1,-1)
        + 2.0000000000000000e+00*HX2(0,1)*HX3(0,0,-1)
        + 2.0000000000000000e+00*HX2(0,1)*HX3(0,0,1)
        - HX2(0,1) *HX3(0,1,-1)
        + 2.4674011002723396e+00*HX3(0,0,-1)
        + 4.9348022005446793e+00*HX3(0,0,1)
        + 2.4674011002723396e+00*HX3(0,1,-1)
        - 2.0000000000000000e+00*HX5(0,-1,-1,0,1)
        - 2.0000000000000000e+00*HX5(0,-1,0,-1,1)
        - HX5(0, -1,0,1,-1)
        - 4.0000000000000000e+00*HX5(0,0,-1,-1,1)
        - HX5(0,0, -1,0,-1)
        - 3.0000000000000000e+00*HX5(0,0,-1,0,1)
        - 3.0000000000000000e+00*HX5(0,0,-1,1,-1)
        - 9.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 7.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 8.0000000000000000e+00*HX5(0,0,0,0,1)
        - 2.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 1.2000000000000000e+01*HX5(0,0,0,1,1)
        - 2.0000000000000000e+00*HX5(0,0,1,0,-1)
        - 4.0000000000000000e+00*HX5(0,0,1,0,1)
        + 4.0000000000000000e+00*HX5(0,0,1,1,-1)
        - HX5(0,1, -1,1,-1)
        + 3.0000000000000000e+00*HX5(0,1,0,1,-1);
      HY5(0,1,-1,1,1) =
        + 7.0189712804378578e-01
        - 8.5393570350547734e-01*HX1(0)
        - 1.3810359531144620e+00*HX1(0)*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX1(0)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,-1)
        + HX1(0) *HX2(0,-1)*HX2(0,1)
        - 4.9348022005446793e+00*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        - HX1(0) *HX4(0,-1,0,1)
        - 3.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX1(0)*HX4(0,0,0,-1)
        + 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,1)
        - HX1(0) *HX4(0,1,-1,1)
        - 2.7620719062289241e+00*HX2(0,1)
        + HX2(0,1) *HX3(0,-1,1)
        - HX2(0,1) *HX3(0,0,-1)
        - HX2(0,1) *HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,0,-1)
        + 9.8696044010893586e+00*HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,1,-1)
        - 2.0000000000000000e+00*HX5(0,-1,0,1,1)
        - HX5(0, -1,1,0,1)
        + HX5(0,0, -1,0,1)
        - 5.0000000000000000e+00*HX5(0,0,-1,1,1)
        + 6.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 6.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 7.0000000000000000e+00*HX5(0,0,0,0,1)
        + 7.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1,0,1)
        - HX5(0,1, -1,1,1)
        + HX5(0,1,0,1,1);
      HY5(0,1,0,1,-1) =
        - 1.0648543070067714e+01
        - 4.6326901362525175e+00*HX1(0)
        - 2.1610434546491269e+00*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        + HX1(0) *HX1(0)*HX3(0,0,1)
        - 2.4674011002723396e+00*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        - 4.0000000000000000e+00*HX1(0)*HX4(0,0,0,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,1,1)
        - 4.3220869092982539e+00*HX2(0,1)
        + HX2(0,1) *HX3(0,0,-1)
        + 2.0000000000000000e+00*HX2(0,1)*HX3(0,0,1)
        + 4.9348022005446793e+00*HX3(0,0,1)
        - HX5(0,0, -1,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        + HX5(0,0,0,0, -1)
        + 8.0000000000000000e+00*HX5(0,0,0,0,1)
        - 2.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 1.2000000000000000e+01*HX5(0,0,0,1,1)
        - 2.0000000000000000e+00*HX5(0,0,1,0,-1)
        - 4.0000000000000000e+00*HX5(0,0,1,0,1)
        + HX5(0,1,0,1, -1);
      HY5(0,1,1,-1,-1) =
        + 3.7073850386582300e+00
        + 4.4002966535502479e+00*HX1(0)
        + 1.3810359531144620e+00*HX1(0)*HX1(0)
        - 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,1)
        + HX1(0) *HX2(0,-1)*HX2(0,1)
        + 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        - HX1(0) *HX4(0,-1,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        + HX1(0) *HX4(0,0,0,-1)
        - HX1(0) *HX4(0,0,1,-1)
        + HX1(0) *HX4(0,1,1,-1)
        + 2.7620719062289241e+00*HX2(0,1)
        - HX2(0,1) *HX3(0,-1,-1)
        - HX2(0,1) *HX3(0,0,-1)
        - HX2(0,1) *HX3(0,0,1)
        + HX5(0, -1,-1,0,1)
        + HX5(0, -1,0,-1,1)
        + HX5(0, -1,0,1,-1)
        + 2.0000000000000000e+00*HX5(0,0,-1,-1,1)
        + HX5(0,0, -1,0,1)
        + 2.0000000000000000e+00*HX5(0,0,-1,1,-1)
        - HX5(0,0,0, -1,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - 3.0000000000000000e+00*HX5(0,0,0,0,-1)
        - 2.0000000000000000e+00*HX5(0,0,0,0,1)
        + 3.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1, -1,-1)
        + HX5(0,0,1,0,1)
        - 2.0000000000000000e+00*HX5(0,0,1,1,-1)
        - HX5(0,1,0,1, -1)
        - HX5(0,1,1, -1,-1);
      HY5(0,1,1,-1,1) =
        - 1.0133791970287534e+01
        - 5.5757170132531547e+00*HX1(0)
        - 6.5847232569963413e-01*HX1(0)*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,1)
        - HX1(0) *HX2(0,-1)*HX2(0,1)
        - 2.4674011002723396e+00*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX2(0,1)*HX2(0,1)
        + HX1(0) *HX4(0,-1,0,1)
        + 2.0000000000000000e+00*HX1(0)*HX4(0,0,-1,1)
        - HX1(0) *HX4(0,0,0,-1)
        + HX1(0) *HX4(0,0,1,-1)
        - HX1(0) *HX4(0,1,1,-1)
        + HX2(0, -1)*HX3(0,1,1)
        - 1.3169446513992682e+00*HX2(0,1)
        - 2.0000000000000000e+00*HX2(0,1)*HX3(0,-1,1)
        + 2.0000000000000000e+00*HX2(0,1)*HX3(0,0,-1)
        + 2.0000000000000000e+00*HX2(0,1)*HX3(0,0,1)
        + HX2(0,1) *HX3(0,1,1)
        + 2.4674011002723396e+00*HX3(0,0,1)
        - 2.4674011002723396e+00*HX3(0,1,1)
        + 3.0000000000000000e+00*HX5(0,-1,0,1,1)
        + 2.0000000000000000e+00*HX5(0,-1,1,0,1)
        - 2.0000000000000000e+00*HX5(0,0,-1,0,1)
        + 6.0000000000000000e+00*HX5(0,0,-1,1,1)
        - 7.0000000000000000e+00*HX5(0,0,0,-1,1)
        + 4.0000000000000000e+00*HX5(0,0,0,0,-1)
        + 3.0000000000000000e+00*HX5(0,0,0,0,1)
        - 3.0000000000000000e+00*HX5(0,0,0,1,-1)
        - 9.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1, -1,1)
        - HX5(0,0,1,0, -1)
        - 3.0000000000000000e+00*HX5(0,0,1,0,1)
        - 6.0000000000000000e+00*HX5(0,0,1,1,1)
        - 3.0000000000000000e+00*HX5(0,1,0,1,1)
        - HX5(0,1,1, -1,1);
      HY5(0,1,1,1,-1) =
        + 7.7484048807851773e-01
        - 5.6922216412839301e-02*HX1(0)
        + 2.0395082788140962e+00*HX1(0)*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)*HX1(0)
        + 8.3333333333333333e-03*HX1(0)*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(0)*HX1(0)*HX1(0)*HX2(0,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,0,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX3(0,1,1)
        + 2.4674011002723396e+00*HX1(0)*HX2(0,1)
        + HX1(0) *HX4(0,0,0,1)
        - HX1(0) *HX4(0,0,1,1)
        + HX1(0) *HX4(0,1,1,1)
        - HX2(0, -1)*HX3(0,1,1)
        + 4.0790165576281924e+00*HX2(0,1)
        + HX2(0,1) *HX3(0,-1,1)
        - HX2(0,1) *HX3(0,0,-1)
        - HX2(0,1) *HX3(0,0,1)
        - HX2(0,1) *HX3(0,1,1)
        - 2.4674011002723396e+00*HX3(0,0,1)
        + 2.4674011002723396e+00*HX3(0,1,1)
        - HX5(0, -1,0,1,1)
        - HX5(0, -1,1,0,1)
        + HX5(0,0, -1,0,1)
        - 2.0000000000000000e+00*HX5(0,0,-1,1,1)
        + 3.0000000000000000e+00*HX5(0,0,0,-1,1)
        - HX5(0,0,0,0, -1)
        - 2.0000000000000000e+00*HX5(0,0,0,0,1)
        + 2.0000000000000000e+00*HX5(0,0,0,1,-1)
        + 6.0000000000000000e+00*HX5(0,0,0,1,1)
        + HX5(0,0,1,0, -1)
        + 2.0000000000000000e+00*HX5(0,0,1,0,1)
        + HX5(0,0,1,1, -1)
        + 4.0000000000000000e+00*HX5(0,0,1,1,1)
        + 2.0000000000000000e+00*HX5(0,1,0,1,1)
        - HX5(0,1,1,1, -1);
      Hi5(-1,-1,-1,-1,1) =
        + 9.6181291076284771e-03
        - 5.5504108664821579e-02*HX1(-1)
        + 1.2011325347955035e-01*HX1(-1)*HX1(-1)
        - 1.1552453009332421e-01*HX1(-1)*HX1(-1)*HX1(-1)
        + 4.1666666666666666e-02*HX1(-1)*HX1(-1)*HX1(-1)*HX1(-1)
        - 1.6666666666666666e-01*HX1(-1)*HX1(-1)*HX1(-1)*HX1(0)
        + 3.4657359027997265e-01*HX1(-1)*HX1(-1)*HX1(0)
        + 2.5000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        - 2.4022650695910071e-01*HX1(-1)*HX1(0)
        - 3.4657359027997265e-01*HX1(-1)*HX1(0)*HX1(0)
        - 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + 5.5504108664821579e-02*HX1(0)
        + 1.2011325347955035e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0);
      Hi5(-1,-1,-1,1,1) =
        + 2.3395367393886929e+00
        - 2.4532465311320902e+00*HX1(-1)
        + 9.4258028690366357e-01*HX1(-1)*HX1(-1)
        + 1.6666666666666666e-01*HX1(-1)*HX1(-1)*HX1(-1)*HX1(0)
        - 2.5000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX2(0,1)
        - 1.8851605738073271e+00*HX1(-1)*HX1(0)
        + 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + HX1( -1)*HX3(0,-1,-1)
        + HX1( -1)*HX3(0,0,-1)
        + HX1( -1)*HX3(0,0,1)
        + HX1( -1)*HX3(0,1,-1)
        + 2.4532465311320902e+00*HX1(0)
        + 9.4258028690366357e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX4( -1,-1,-1,1)
        - HX4(0, -1,-1,-1)
        - HX4(0,0, -1,-1)
        - HX4(0,0,0, -1)
        - HX4(0,0,0,1)
        - HX4(0,0,1, -1)
        - HX4(0,1, -1,-1);
      Hi5(-1,-1,1,-1,1) =
        - 5.1782796940106865e+00
        + 3.1962209462999012e+00*HX1(-1)
        - 6.5146002367115732e-01*HX1(-1)*HX1(-1)
        - 3.4657359027997265e-01*HX1(-1)*HX1(-1)*HX1(0)
        - 2.5000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(-1)*HX1(-1)*HX2(0,1)
        + 1.3029200473423146e+00*HX1(-1)*HX1(0)
        + 3.4657359027997265e-01*HX1(-1)*HX1(0)*HX1(0)
        + 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + HX1( -1)*HX1(0)*HX2(0,-1)
        + HX1( -1)*HX1(0)*HX2(0,1)
        + 6.9314718055994530e-01*HX1(-1)*HX2(0,-1)
        + 6.9314718055994530e-01*HX1(-1)*HX2(0,1)
        + HX1( -1)*HX3(-1,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX3(0,-1,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX3(0,0,1)
        - 2.0000000000000000e+00*HX1(-1)*HX3(0,1,-1)
        - 3.1962209462999012e+00*HX1(0)
        - 6.5146002367115732e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(-1,-1,1)
        - HX1(0) *HX3(0,-1,-1)
        - HX1(0) *HX3(0,0,-1)
        - HX1(0) *HX3(0,0,1)
        - HX1(0) *HX3(0,1,-1)
        - 6.9314718055994530e-01*HX3(-1,-1,1)
        - 6.9314718055994530e-01*HX3(0,-1,-1)
        - 6.9314718055994530e-01*HX3(0,0,-1)
        - 6.9314718055994530e-01*HX3(0,0,1)
        - 6.9314718055994530e-01*HX3(0,1,-1)
        - 3.0000000000000000e+00*HX4(-1,-1,-1,1)
        + 3.0000000000000000e+00*HX4(0,-1,-1,-1)
        + 3.0000000000000000e+00*HX4(0,0,-1,-1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX4(0,0,0,1)
        + 3.0000000000000000e+00*HX4(0,0,1,-1)
        + 3.0000000000000000e+00*HX4(0,1,-1,-1);
      Hi5(-1,-1,1,1,1) =
        + 3.1512791646720465e+00
        - 5.5504108664821579e-02*HX1(-1)
        - 8.2246703342411321e-01*HX1(-1)*HX1(-1)
        + 2.5000000000000000e-01*HX1(-1)*HX1(-1)*HX1(0)*HX1(0)
        + 1.6449340668482264e+00*HX1(-1)*HX1(0)
        - 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        - HX1( -1)*HX1(0)*HX2(0,-1)
        - HX1( -1)*HX1(0)*HX2(0,1)
        - HX1( -1)*HX3(0,-1,1)
        + HX1( -1)*HX3(0,0,-1)
        + HX1( -1)*HX3(0,0,1)
        - HX1( -1)*HX3(0,1,1)
        + 5.5504108664821579e-02*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX3(-1,-1,1)
        + HX1(0) *HX3(0,-1,-1)
        + HX1(0) *HX3(0,0,-1)
        + HX1(0) *HX3(0,0,1)
        + HX1(0) *HX3(0,1,-1)
        + HX4( -1,-1,1,1)
        + HX4(0, -1,-1,1)
        + HX4(0, -1,1,-1)
        - HX4(0,0, -1,-1)
        + HX4(0,0, -1,1)
        - 2.0000000000000000e+00*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX4(0,0,0,1)
        - HX4(0,0,1, -1)
        + HX4(0,0,1,1)
        + HX4(0,1, -1,1)
        + HX4(0,1,1, -1);
      Hi5(-1,1,-1,1,1) =
        - 5.6883244754482793e+00
        + 2.9285842322233888e+00*HX1(-1)
        + 1.8851605738073271e+00*HX1(-1)*HX1(0)
        - 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + HX1( -1)*HX1(0)*HX2(-1,1)
        + HX1( -1)*HX1(0)*HX2(0,-1)
        + HX1( -1)*HX1(0)*HX2(0,1)
        + 2.0000000000000000e+00*HX1(-1)*HX3(0,-1,1)
        - 2.0000000000000000e+00*HX1(-1)*HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(-1)*HX3(0,0,1)
        + 2.0000000000000000e+00*HX1(-1)*HX3(0,1,1)
        - 2.9285842322233888e+00*HX1(0)
        - 9.4258028690366357e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(-1,1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(-1,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,-1,-1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,1,-1)
        + 1.8851605738073271e+00*HX2(-1,1)
        + 5.0000000000000000e-01*HX2(-1,1)*HX2(-1,1)
        - HX2( -1,1)*HX2(0,-1)
        - HX2( -1,1)*HX2(0,1)
        - 1.8851605738073271e+00*HX2(0,-1)
        + 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1)
        + HX2(0, -1)*HX2(0,1)
        - 1.8851605738073271e+00*HX2(0,1)
        + 5.0000000000000000e-01*HX2(0,1)*HX2(0,1)
        - 2.0000000000000000e+00*HX4(-1,-1,1,1)
        - 2.0000000000000000e+00*HX4(0,-1,-1,1)
        - 2.0000000000000000e+00*HX4(0,-1,1,-1)
        + 2.0000000000000000e+00*HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX4(0,0,-1,1)
        + 4.0000000000000000e+00*HX4(0,0,0,-1)
        + 4.0000000000000000e+00*HX4(0,0,0,1)
        + 2.0000000000000000e+00*HX4(0,0,1,-1)
        - 2.0000000000000000e+00*HX4(0,0,1,1)
        - 2.0000000000000000e+00*HX4(0,1,-1,1)
        - 2.0000000000000000e+00*HX4(0,1,1,-1);
      Hi5(-1,1,1,1,1) =
        - 8.0212429617572516e-01
        - 1.6449340668482264e+00*HX1(-1)*HX1(0)
        + 1.6666666666666666e-01*HX1(-1)*HX1(0)*HX1(0)*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(-1,1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        + HX1(0) *HX3(-1,1,1)
        - HX1(0) *HX3(0,-1,1)
        + HX1(0) *HX3(0,0,-1)
        + HX1(0) *HX3(0,0,1)
        - HX1(0) *HX3(0,1,1)
        - 1.6449340668482264e+00*HX2(-1,1)
        + 1.6449340668482264e+00*HX2(0,-1)
        + 1.6449340668482264e+00*HX2(0,1)
        + HX4( -1,1,1,1)
        - HX4(0, -1,1,1)
        + HX4(0,0, -1,1)
        - HX4(0,0,0, -1)
        - HX4(0,0,0,1)
        + HX4(0,0,1,1)
        - HX4(0,1,1,1);
      Hi5(0,-1,-1,-1,1) =
        + 5.2709719078152786e-01
        + 5.5504108664821579e-02*HX1(0)
        + 1.2011325347955035e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - 6.9314718055994530e-01*HX1(0)*HX2(0,-1)
        + HX1(0) *HX3(0,-1,-1)
        + HX1(0) *HX3(0,0,-1)
        - 2.4022650695910071e-01*HX2(0,-1)
        + 6.9314718055994530e-01*HX3(0,-1,-1)
        + 6.9314718055994530e-01*HX3(0,0,-1)
        - HX4(0, -1,-1,-1)
        - HX4(0,0, -1,-1)
        - HX4(0,0,0, -1);
      Hi5(0,-1,-1,0,1) =
        - 3.3822601053473068e-01
        - 1.0517997902646449e+00*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        + HX1(0) *HX3(0,-1,-1)
        + HX1(0) *HX3(0,0,-1)
        + 8.2246703342411321e-01*HX2(0,-1)
        - 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1);
      Hi5(0,-1,-1,1,-1) =
        + 3.3389529407850318e-01
        - 1.6651232599446473e-01*HX1(0)
        - 2.4022650695910071e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 6.9314718055994530e-01*HX1(0)*HX2(0,-1)
        + 4.8045301391820142e-01*HX2(0,-1)
        - 6.9314718055994530e-01*HX3(0,-1,-1)
        - 6.9314718055994530e-01*HX3(0,0,-1);
      Hi5(0,-1,-1,1,1) =
        + 2.0079271680389850e+00
        + 2.4532465311320902e+00*HX1(0)
        + 9.4258028690366357e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - HX1(0) *HX3(0,-1,-1)
        - HX1(0) *HX3(0,0,-1)
        - 1.8851605738073271e+00*HX2(0,-1)
        + 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1)
        - HX4(0, -1,-1,1)
        + HX4(0, -1,0,1)
        + HX4(0,0, -1,1)
        - HX4(0,0,0,1);
      Hi5(0,-1,0,-1,1) =
        + 3.0521251417144869e+00
        + 1.5335088752078636e+00*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - 6.9314718055994530e-01*HX1(0)*HX2(0,-1)
        + 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - 8.2246703342411321e-01*HX2(0,-1)
        + 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1)
        + 1.3862943611198906e+00*HX3(0,0,-1)
        - 2.0000000000000000e+00*HX4(0,0,-1,-1)
        - 4.0000000000000000e+00*HX4(0,0,0,-1);
      Hi5(0,-1,0,1,-1) =
        + 1.2498035299465379e+00
        + 5.7009070532142637e-01*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 6.9314718055994530e-01*HX1(0)*HX2(0,-1)
        - 1.3862943611198906e+00*HX3(0,0,-1);
      Hi5(0,-1,0,1,1) =
        - 6.0880681896251523e-01
        + 1.0517997902646449e+00*HX1(0)
        + 8.2246703342411321e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - 1.6449340668482264e+00*HX2(0,-1)
        + HX4(0, -1,0,1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1)
        - HX4(0,0,0,1);
      Hi5(0,-1,1,-1,-1) =
        + 1.9757838252848865e-01
        + 1.6651232599446473e-01*HX1(0)
        + 1.2011325347955035e-01*HX1(0)*HX1(0)
        - 2.4022650695910071e-01*HX2(0,-1);
      Hi5(0,-1,1,-1,1) =
        - 5.7090374034238681e+00
        - 3.1962209462999012e+00*HX1(0)
        - 6.5146002367115732e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        + 6.9314718055994530e-01*HX1(0)*HX2(0,-1)
        + HX1(0) *HX3(0,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX3(0,0,1)
        + 1.3029200473423146e+00*HX2(0,-1)
        - 5.0000000000000000e-01*HX2(0,-1)*HX2(0,-1)
        + 6.9314718055994530e-01*HX3(0,-1,1)
        - 1.3862943611198906e+00*HX3(0,0,-1)
        - 6.9314718055994530e-01*HX3(0,0,1)
        - HX4(0, -1,0,1)
        - HX4(0, -1,1,-1)
        + 2.0000000000000000e+00*HX4(0,0,-1,-1)
        - 2.0000000000000000e+00*HX4(0,0,-1,1)
        + 4.0000000000000000e+00*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1, -1);
      Hi5(0,-1,1,0,1) =
        - 5.6493805840032952e+00
        - 2.6736902858507163e+00*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        + HX1(0) *HX3(0,-1,1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        - HX1(0) *HX3(0,0,1)
        - HX4(0, -1,0,1)
        - 2.0000000000000000e+00*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1)
        + 3.0000000000000000e+00*HX4(0,0,0,1);
      Hi5(0,-1,1,1,-1) =
        - 2.3933959928473851e+00
        - 1.7102721159642791e+00*HX1(0)
        - 2.9112026323250625e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        - 6.9314718055994530e-01*HX1(0)*HX2(0,-1)
        + 5.8224052646501250e-01*HX2(0,-1)
        - 6.9314718055994530e-01*HX3(0,-1,1)
        + 1.3862943611198906e+00*HX3(0,0,-1)
        + 6.9314718055994530e-01*HX3(0,0,1);
      Hi5(0,-1,1,1,1) =
        + 3.2396052320380567e+00
        + 5.5504108664821579e-02*HX1(0)
        - 8.2246703342411321e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,-1)
        - HX1(0) *HX3(0,-1,1)
        + 2.0000000000000000e+00*HX1(0)*HX3(0,0,-1)
        + HX1(0) *HX3(0,0,1)
        + 1.6449340668482264e+00*HX2(0,-1)
        - HX4(0, -1,1,1)
        + 2.0000000000000000e+00*HX4(0,0,-1,1)
        - 3.0000000000000000e+00*HX4(0,0,0,-1)
        - 2.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1,1);
      Hi5(0,0,-1,-1,1) =
        - 1.3569495655898781e+00
        - 4.8170908494321862e-01*HX1(0)
        + 1.2011325347955035e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(0,0,-1)
        - 6.9314718055994530e-01*HX3(0,0,-1)
        + HX4(0,0, -1,-1)
        + 2.0000000000000000e+00*HX4(0,0,0,-1);
      Hi5(0,0,-1,0,1) =
        - 2.8410984884917377e+00
        - 1.8030853547393914e+00*HX1(0)
        - 4.1123351671205660e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(0,0,-1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1);
      Hi5(0,0,-1,1,-1) =
        - 6.2490176497326899e-01
        - 5.7009070532142637e-01*HX1(0)
        - 2.4022650695910071e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 6.9314718055994530e-01*HX3(0,0,-1);
      Hi5(0,0,-1,1,1) =
        + 3.8055457225523666e+00
        + 2.7620719062289241e+00*HX1(0)
        + 9.4258028690366357e-01*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + HX1(0) *HX3(0,0,-1)
        + HX4(0,0, -1,1)
        - 3.0000000000000000e+00*HX4(0,0,0,-1)
        - HX4(0,0,0,1);
      Hi5(0,0,0,-1,1) =
        + 9.4703282949724591e-01
        + 9.0154267736969571e-01*HX1(0)
        + 4.1123351671205660e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX4(0,0,0, -1);
      Hi5(0,0,0,1,-1) =
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0);
      Hi5(0,0,1,-1,-1) =
        + 1.2011325347955035e-01*HX1(0)*HX1(0);
      Hi5(0,0,1,-1,1) =
        - 3.5336454555719528e+00
        - 2.6736902858507163e+00*HX1(0)
        - 6.5146002367115732e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - HX1(0) *HX3(0,0,1)
        - 6.9314718055994530e-01*HX3(0,0,1)
        + HX4(0,0,0, -1)
        + 3.0000000000000000e+00*HX4(0,0,0,1)
        + HX4(0,0,1, -1);
      Hi5(0,0,1,0,-1) =
        + 4.1123351671205660e-01*HX1(0)*HX1(0);
      Hi5(0,0,1,1,-1) =
        - 8.3320235329769199e-01
        - 1.1401814106428527e+00*HX1(0)
        - 2.9112026323250625e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 6.9314718055994530e-01*HX3(0,0,1);
      Hi5(0,1,-1,-1,-1) =
        - 5.5504108664821579e-02*HX1(0);
      Hi5(0,1,-1,-1,1) =
        + 3.4402173672056757e+00
        + 1.0517997902646449e+00*HX1(0)
        - 1.2011325347955035e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        - 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        - 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        - 6.9314718055994530e-01*HX1(0)*HX2(0,1)
        + HX1(0) *HX3(0,0,-1)
        + 2.0000000000000000e+00*HX1(0)*HX3(0,0,1)
        + HX1(0) *HX3(0,1,-1)
        - 2.4022650695910071e-01*HX2(0,1)
        + 6.9314718055994530e-01*HX3(0,0,-1)
        + 1.3862943611198906e+00*HX3(0,0,1)
        + 6.9314718055994530e-01*HX3(0,1,-1)
        - HX4(0,0, -1,-1)
        - 2.0000000000000000e+00*HX4(0,0,0,-1)
        - 3.0000000000000000e+00*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,1,-1)
        - HX4(0,1, -1,-1);
      Hi5(0,1,-1,1,-1) =
        + 1.8532608833279382e+00
        + 1.0926213657706112e+00*HX1(0)
        + 2.4022650695910071e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 6.9314718055994530e-01*HX1(0)*HX2(0,1)
        + 4.8045301391820142e-01*HX2(0,1)
        - 6.9314718055994530e-01*HX3(0,0,-1)
        - 1.3862943611198906e+00*HX3(0,0,1)
        - 6.9314718055994530e-01*HX3(0,1,-1);
      Hi5(0,1,-1,1,1) =
        - 5.4839540823383124e+00
        - 2.9285842322233888e+00*HX1(0)
        - 9.4258028690366357e-01*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        - HX1(0) *HX3(0,0,-1)
        - 2.0000000000000000e+00*HX1(0)*HX3(0,0,1)
        - HX1(0) *HX3(0,1,-1)
        + HX2(0, -1)*HX2(0,1)
        - 1.8851605738073271e+00*HX2(0,1)
        + 5.0000000000000000e-01*HX2(0,1)*HX2(0,1)
        - HX4(0, -1,0,1)
        - 3.0000000000000000e+00*HX4(0,0,-1,1)
        + 3.0000000000000000e+00*HX4(0,0,0,-1)
        + 4.0000000000000000e+00*HX4(0,0,0,1)
        - 2.0000000000000000e+00*HX4(0,0,1,1)
        - HX4(0,1, -1,1);
      Hi5(0,1,0,1,-1) =
        + 1.6664047065953839e+00
        + 6.3196619783816790e-01*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 6.9314718055994530e-01*HX1(0)*HX2(0,1)
        - 1.3862943611198906e+00*HX3(0,0,1);
      Hi5(0,1,1,-1,-1) =
        + 3.9515676505697730e-01
        + 3.0882537509683393e-01*HX1(0)
        - 1.2011325347955035e-01*HX1(0)*HX1(0)
        - 2.4022650695910071e-01*HX2(0,1);
      Hi5(0,1,1,-1,1) =
        + 1.3317828347103277e+00
        + 2.2701119065237547e+00*HX1(0)
        + 6.5146002367115732e-01*HX1(0)*HX1(0)
        + 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        + 4.1666666666666666e-02*HX1(0)*HX1(0)*HX1(0)*HX1(0)
        + 5.0000000000000000e-01*HX1(0)*HX1(0)*HX2(0,1)
        + 6.9314718055994530e-01*HX1(0)*HX2(0,1)
        - HX1(0) *HX3(0,0,1)
        + HX1(0) *HX3(0,1,1)
        - HX2(0, -1)*HX2(0,1)
        + 1.3029200473423146e+00*HX2(0,1)
        - 5.0000000000000000e-01*HX2(0,1)*HX2(0,1)
        - 6.9314718055994530e-01*HX3(0,0,1)
        + 6.9314718055994530e-01*HX3(0,1,1)
        + HX4(0, -1,0,1)
        + 2.0000000000000000e+00*HX4(0,0,-1,1)
        - HX4(0,0,0, -1)
        + HX4(0,0,1, -1)
        - HX4(0,1,1, -1);
      Hi5(0,1,1,1,-1) =
        - 9.5774727708194543e-01
        + 6.0296821703481255e-01*HX1(0)
        + 2.9112026323250625e-01*HX1(0)*HX1(0)
        - 1.1552453009332421e-01*HX1(0)*HX1(0)*HX1(0)
        - 6.9314718055994530e-01*HX1(0)*HX2(0,1)
        + 5.8224052646501250e-01*HX2(0,1)
        + 6.9314718055994530e-01*HX3(0,0,1)
        - 6.9314718055994530e-01*HX3(0,1,1);
    }
    // nw > 4 endif
  }
  // (n1,n2) = (-1,1) -- completion endif
 }

 void hplog5::pfillirr1dhplin1(double y, int nw, HArr<1>& HY1, HArr<2>& HY2, HArr<3>& HY3, HArr<4>& HY4, HArr<5>& HY5, int n1, int n2)
 {
  // evaluates the irreducible HPL for y =1
  // it is guaranteed that nw is in the range 2:4, and that (n1,n2)
  // take one of the pairs of values (0,1), (-1,0) or (-1,1)

  // (n1,n2) = (0,1) or (-1,1)
  if (    ( (n1 == 0)  && (n2 == 1) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,1) =
      + 1.6449340668482264e+00;
    if (nw > 2){
      HY3(0,0,1) =
        + 1.2020569031595942e+00;
      HY3(0,1,1) =
        + 1.2020569031595942e+00;
    }

    if (nw > 3){
      HY4(0,0,0,1) =
        + 1.0823232337111381e+00;
      HY4(0,0,1,1) =
        + 2.7058080842778454e-01;
      HY4(0,1,1,1) =
        + 1.0823232337111381e+00;
    }

    if (nw > 4){
      HY5(0,0,0,0,1) =
        + 1.0369277551433699e+00;
      HY5(0,0,0,1,1) =
        + 9.6551159989443734e-02;
      HY5(0,0,1,0,1) =
        + 2.2881039760335375e-01;
      HY5(0,0,1,1,1) =
        + 9.6551159989443734e-02;
      HY5(0,1,0,1,1) =
        + 2.2881039760335375e-01;
      HY5(0,1,1,1,1) =
        + 1.0369277551433699e+00;
    }
  }
  // (n1,n2) = (0,1) or (-1,1) endif
  //**********

  // (n1,n2) = (-1,0) or (-1,1)
  if (    ( (n1 == -1) && (n2 == 0) )
       || ( (n1 == -1) && (n2 == 1) ) ){
    HY2(0,-1) =
      + 8.2246703342411321e-01;
    if (nw > 2){
      HY3(0,-1,-1) =
        + 1.5025711289494928e-01;
      HY3(0,0,-1) =
        + 9.0154267736969571e-01;
    }

    if (nw > 3){
      HY4(0,-1,-1,-1) =
        + 2.3752366322618485e-02;
      HY4(0,0,-1,-1) =
        + 8.7785671568655302e-02;
      HY4(0,0,0,-1) =
        + 9.4703282949724591e-01;
    }

    if (nw > 4){
      HY5(0,0,0,0,-1) =
        + 9.7211977044690930e-01;
      HY5(0,0,0,-1,-1) =
        + 4.8936397049969063e-02;
      HY5(0,0,-1,0,-1) =
        + 9.2748467341632644e-02;
      HY5(0,0,-1,-1,-1) =
        + 9.6015684431298325e-03;
      HY5(0,-1,0,-1,-1) =
        + 1.3531263989594243e-02;
      HY5(0,-1,-1,-1,-1) =
        + 3.1350096016808622e-03;
    }
  }
  // (n1,n2) = (-1,0) or (-1,1) endif

  // (n1,n2) = (-1,1) -- completion
  if ( (n1 == -1) && (n2 == 1) ){
    HY2(-1,1) =
      + 5.8224052646501250e-01;
    if (nw > 2){
      HY3(0,-1,1) =
        + 2.4307035167006157e-01;
      HY3(0,1,-1) =
        + 5.0821521280468485e-01;
      HY3(-1,-1,1) =
        + 9.4753004230127705e-02;
      HY3(-1,1,1) =
        + 5.3721319360804020e-01;
    }

    if (nw > 3){
      HY4(0,0,-1,1) =
        + 1.1787599965050932e-01;
      HY4(0,0,1,-1) =
        + 1.7284527823898438e-01;
      HY4(0,-1,0,1) =
        + 2.0293560632083841e-01;
      HY4(0,-1,-1,1) =
        + 3.4159126166513913e-02;
      HY4(0,-1,1,-1) =
        + 5.4653052738263652e-02;
      HY4(0,1,-1,-1) =
        + 1.1412342741606084e-01;
      HY4(0,-1,1,1) =
        + 9.3097125991768577e-02;
      HY4(0,1,-1,1) =
        + 1.9355535381306524e-01;
      HY4(0,1,1,-1) =
        + 4.3369237704895519e-01;
      HY4(-1,-1,-1,1) =
        + 1.4134237214990008e-02;
      HY4(-1,-1,1,1) =
        + 4.0758239159309251e-02;
      HY4(-1,1,1,1) =
        + 5.1747906167389938e-01;
    }

    if (nw > 4){
      HY5(-1,-1,-1,-1,1) =
        + 1.8016537870380179e-03;
      HY5(-1,-1,-1,1,1) =
        + 3.8760673146652637e-03;
      HY5(-1,-1,1,-1,1) =
        + 6.2154684604081354e-03;
      HY5(-1,-1,1,1,1) =
        + 1.8530786065466613e-02;
      HY5(-1,1,-1,1,1) =
        + 3.8880058841843904e-02;
      HY5(-1,1,1,1,1) =
        + 5.0840057924226870e-01;
      HY5(0,-1,-1,-1,1) =
        + 4.1914400448554060e-03;
      HY5(0,-1,-1,0,1) =
        + 3.0172237496701167e-02;
      HY5(0,-1,-1,1,-1) =
        + 5.9459097989450212e-03;
      HY5(0,-1,-1,1,1) =
        + 8.7734377821481916e-03;
      HY5(0,-1,0,-1,1) =
        + 1.7042475614121991e-02;
      HY5(0,-1,0,1,-1) =
        + 2.2495758621687517e-02;
      HY5(0,-1,0,1,1) =
        + 3.0833054551948363e-02;
      HY5(0,-1,1,-1,-1) =
        + 9.4133341974174110e-03;
      HY5(0,-1,1,-1,1) =
        + 1.3833955759762555e-02;
      HY5(0,-1,1,0,1) =
        + 7.6026642213084631e-02;
      HY5(0,-1,1,1,-1) =
        + 2.2801059128486651e-02;
      HY5(0,-1,1,1,1) =
        + 3.9984858137537496e-02;
      HY5(0,0,-1,-1,1) =
        + 1.2444228784499648e-02;
      HY5(0,0,-1,0,1) =
        + 1.0679981350605469e-01;
      HY5(0,0,-1,1,-1) =
        + 1.6991592326175436e-02;
      HY5(0,0,-1,1,1) =
        + 2.4107342184124538e-02;
      HY5(0,0,0,-1,1) =
        + 5.9142607400864533e-02;
      HY5(0,0,0,1,-1) =
        + 7.4276054639867797e-02;
      HY5(0,0,1,-1,-1) =
        + 2.5535023438634211e-02;
      HY5(0,0,1,-1,1) =
        + 3.6321732111088421e-02;
      HY5(0,0,1,0,-1) =
        + 1.8615775173851248e-01;
      HY5(0,0,1,1,-1) =
        + 5.7353571803049304e-02;
      HY5(0,1,-1,-1,-1) =
        + 1.9555438852482933e-02;
      HY5(0,1,-1,-1,1) =
        + 2.8668668263701248e-02;
      HY5(0,1,-1,1,-1) =
        + 4.7069633474401836e-02;
      HY5(0,1,-1,1,1) =
        + 8.2208743029471844e-02;
      HY5(0,1,0,1,-1) =
        + 1.4122347902560834e-01;
      HY5(0,1,1,-1,-1) =
        + 1.0254618242743082e-01;
      HY5(0,1,1,-1,1) =
        + 1.7692012816527167e-01;
      HY5(0,1,1,1,-1) =
        + 4.0707197178331534e-01;
    }
  }
  // (n1,n2) = (-1,1) -- completion endif
 }


}// namespace hplog5
