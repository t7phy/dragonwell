#include "Calculation/CalcDIS.h"

//
//-----------------------------------------------------------------------
// On the next-to-next-to-leading order QCD corrections     
// to heavy-quark production in deep-inelastic 
//    
// H. Kawamura, N. Lo Presti, S. Moch and A. Vogt
//-----------------------------------------------------------------------    
//
// Fit result for the mu- and nf-independent part of the heavy-quark gluon 
// and pure-singlet quark operator matrix element:
// aQg30 in Eqs. (3.49) and (3.50)
// aQqPS30 in Eq. (3.52), H2qPS3 in Eq. (3.53)
//
//-----------------------------------------------------------------------
// ..The 3-loop fit of the constant contribution to the gluon OME: aQg30 
//   see Eq. (3.49) and (3.50) for scheme A and B
//
double CalcDIS::aQg30(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double aQgA30 =
       354.1002 * dl1*dl1*dl1 + 479.3838 * dl1*dl1 - 7856.784 * (2.0-x)
     - 6233.530 * dl*dl  + 9416.621 * dx     + 1548.891 * dx * dl;

 double aQgB30 =
      - 2658.323 * dl1*dl1 - 7449.948 * dl1 - 7460.002 * (2.0-x)
      + 3178.819 * dl*dl  + 4710.725 * dx  + 1548.891 * dx * dl;

 //      aQg30 = aQgA30
 //      aQg30 = aQgB30
 double Value = (aQgA30+aQgB30)/2.0;

 return Value;
}

double CalcDIS::aQgA30(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double Value =
       354.1002 * dl1*dl1*dl1 + 479.3838 * dl1*dl1 - 7856.784 * (2.0-x)
     - 6233.530 * dl*dl  + 9416.621 * dx     + 1548.891 * dx * dl;

 return Value;
}

double CalcDIS::aQgB30(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double Value =
      - 2658.323 * dl1*dl1 - 7449.948 * dl1 - 7460.002 * (2.0-x)
      + 3178.819 * dl*dl  + 4710.725 * dx  + 1548.891 * dx * dl;

 return Value;
}

double CalcDIS::aQg30new(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double A3 = 0.1029568;
 double A2 = 0.3776366;
 double A1 = 0.1395957;
 double B1 = 0.1809674;
 double B2 = -0.01683145;
 double C1 = -2.7079e-5;
 double C2 = -2.3892e-6;

 double Value = (A3 * dl1*dl1*dl1 + A2 * dl1*dl1 + A1 * dl1 + B1 * (2.0 - x) + 
                 B2 * dl*dl       + C1 * dx      + C2 * dx * dl) * 2000.0 / x;

 return Value;
}

//-----------------------------------------------------------------------
// ..The 3-loop fit of the constant contribution to the gluon OME: aQqPS30 
//   see Eq. (3.52) and (3.53) for scheme A and B
double CalcDIS::aQqPS30(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double aQqPSA30 =
      (1.0-x) *(
        232.9555  * dl1*dl1*dl1 + 1309.528 * dl1*dl1 - 31729.716 * x*x
      + 66638.193 * x      + 2825.641 * dx )
      + 41850.518 * x * dl + 688.3960  * dx * dl;


 double aQqPSB30 =
      (1.0-x) *(
         126.3546 * dl1*dl1 + 353.8539 * dl1    + 6787.608 * x
       + 3780.192 * dx )   + 8571.165 * x * dl - 2346.893 * dl*dl
       + 688.3960 * dx * dl;

 //      aQqPS30 = aQqPSA30
 //      aQqPS30 = aQqPSB30
 double Value = (aQqPSA30+aQqPSB30)/2.0;

 return Value;
}

double CalcDIS::aQqPSA30(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double Value =
      (1.0-x) *(
        232.9555  * dl1*dl1*dl1 + 1309.528 * dl1*dl1 - 31729.716 * x*x
      + 66638.193 * x      + 2825.641 * dx )
      + 41850.518 * x * dl + 688.3960  * dx * dl;

 return Value;
}

double CalcDIS::aQqPSB30(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double Value =
      (1.0-x) *(
         126.3546 * dl1*dl1 + 353.8539 * dl1    + 6787.608 * x
       + 3780.192 * dx )   + 8571.165 * x * dl - 2346.893 * dl*dl
       + 688.3960 * dx * dl;

 return Value;
}

double CalcDIS::aQqPS30new(double x)
{
 double dx  = 1.0/x;
 double x1  = 1.0-x;
 double dl  = log(x);
 double dl1 = log(x1);

 double Aq3 = 3.25604502e-1;
 double Aq2 = 1.29477583;
 double Bq1 = -4.78396428;
 double Bq2 = 2.07586331;
 double Cq1 = -2.18152598e-4;
 double Cq2 = 5.62487033e-1;
 double Cq3 = -1.84671661e-5;

 double Value = ((1.0 - x) * (Aq3 * dl1*dl1*dl1 + Aq2 * dl1*dl1 +
                              Bq1 * x*x         + Bq2 * x + Cq1 * dx)
                + Cq2 * x * dl + Cq3 * dx * dl) * 2000.0 / x;

 return Value;
}

