#include "Calculation/CTUtil.h"

double CTUtil::AdzInt(function<double(double)> fcn, double a, double b, double aerr, double rerr, double &errest, int &IER, int IACTA, int IACTB)
{
//===========================================================================
// GroupName: Adzint
// Description: adaptive integration
// ListOfFiles: adzint adzcal adzspl intusz sglint totalz
//===========================================================================
//                                  Authors: Wu-Ki Tung and John C. Collins
// #Header: /Net/cteq06/users/wkt/1hep/1utl/RCS/Adzint.f,v 1.1 97/12/21 21:19:04 wkt Exp $
// #Log: Adzint.f,v $
// Revision 1.1  97/12/21  21:19:04  wkt
// Initial revision

 double Value = 0.0;

 double smll = 1e-20, sml = 1e-12;
 double fac0 = 2.0;
 adz_u.resize(MAXINT + 1);
 adz_v.resize(MAXINT + 1);
 adz_fu.resize(MAXINT + 1);
 adz_fv.resize(MAXINT + 1);
 adz_fw.resize(MAXINT + 1);
 adz_err.resize(MAXINT + 1);
 adz_result.resize(MAXINT + 1);


 IER = 0;
 if(aerr <= smll && rerr <= smll){
   cout<<"Both Aerr and Rerr are zero in ADZINT!"<<endl;
   return 0.0;
 }

 if(IACTA < 0 || IACTA > 2){
   cout<<" Illegal value of IACT in ADZINT call IACTA = "<<IACTA<<" IACTA set for regular open-end option."<<endl;
   IACTA = 1;
   IER = 2;
 }

 if(IACTB < 0 || IACTB > 2){
   cout<<" Illegal value of IACT in ADZINT call IACTB = "<<IACTB<<" IACTB set for regular open-end option."<<endl;
   IACTB = 1;
   IER = 3;
 }
 adz_ICTA = IACTA;
 adz_ICTB = IACTB;

 double ddx = b - a;
 if(ddx <= 0.0){
   Value = 0.0;
   IER = 4;
   if(ddx < 0.0){
     cout<<"B < A in AdzInt; check limits!!"<<endl;
     return 0.0;
   }
 }
 else if (ddx <= sml){
   Value = fcn(a + ddx / 2.0) * ddx;//yfu: remind this place fortran is ddx/2
   IER = 5;
   return Value;
 }

 adz_NUMINT = 3;
 double dx = ddx / adz_NUMINT;

 for(int i = 1; i <= adz_NUMINT; i++){
   if(i == 1){
     adz_u[1] = a;
     if(IACTA == 0){
        adz_fu[1] = fcn(adz_u[1]);
     }
     else{
//                            For the indeterminant end point, use the
//                            midpoint as a substitue for the endpoint.
       adz_fa = fcn(a + dx / 2.0);
     }
   }
   else{
     adz_u[i] = adz_v[i - 1];
     adz_fu[i] = adz_fv[i - 1];
   }

   if(i == adz_NUMINT){
     adz_v[i] = b;
     if(IACTB == 0){
       adz_fv[i] = fcn(adz_v[i]);
     }
     else{
       adz_IB = i;
       adz_fb = fcn(b - dx / 2.0);
     }
   }
   else{
       adz_v[i] = a + dx * i;
       adz_fv[i] = fcn(adz_v[i]);
   }
   ADZCAL(fcn,i);
 }

 TOTALZ();
//                                                   Adaptive procedure:
//Lai revised to ensure the accuracy requested and improve the speed
 double facMax = fac0 * MAXINT;
 double target = 0.0;

 while(1){// goto 20
   target = fabs(aerr) + fabs(rerr * adz_RES);  // targeted total error
   if(adz_ERS <= target || IER > 0){// goto 30
     Value = adz_RES;
     errest = adz_ERS;
     return Value;
   }
  
   int NUMOLD = adz_NUMINT;
   double facNum = sqrt((double)(NUMOLD) * fac0);

   while(NUMOLD == adz_NUMINT){
     for(int i = 1; i <= NUMOLD; i++){
       if(adz_err[i] * facNum > target) ADZSPL(fcn, i, IER);
     }              // I
     if(NUMOLD != adz_NUMINT){// !additional intervals were added
       break; // goto 20
     }
     else{
       facNum = facNum * fac0;
       if(facNum > facMax){ // goto 30
         Value = adz_RES;
         errest = adz_ERS;
         return Value;
       }
     }
   }// do loop if NUMOLD==NUMINT

 }// do loop if .not.(ERS<=Target .or. Ier>0)

 return Value;
}

void CTUtil::ADZSPL(function<double(double)> fcn, int i, int &IER)
{
 double tiny = 1e-20;

 if(adz_NUMINT >= MAXINT){
   IER = 1;
   return;
 }
 adz_NUMINT = adz_NUMINT + 1;

//                                                         New interval NUMINT
 if(i == adz_IB) adz_IB = adz_NUMINT;
 adz_u[adz_NUMINT] = (adz_u[i] + adz_v[i]) / 2.0;
 adz_v[adz_NUMINT] = adz_v[i];

 adz_fu[adz_NUMINT] = adz_fw[i];
 adz_fv[adz_NUMINT] = adz_fv[i];
//                                                         New interval I
 adz_v[i] =  adz_u[adz_NUMINT];
 adz_fv[i] = adz_fu[adz_NUMINT];
//                                                Save old Result and Error
 double OLDRES = adz_result[i];
 double OLDERR = adz_err[i];

 ADZCAL(fcn, i);
 ADZCAL(fcn, adz_NUMINT);
//                                                           Update result
 double DELRES = adz_result[i] + adz_result[adz_NUMINT] - OLDRES;
 adz_RES = adz_RES + DELRES;
//                              Good error estimate based on Simpson formula
 double GODERR = fabs(DELRES);
//                                                         Update new global 
 adz_ERS = adz_ERS + GODERR - OLDERR;
//                              Improve local error estimates proportionally
 double SUMERR = adz_err[i] + adz_err[adz_NUMINT];
 double FAC;
 if(SUMERR > tiny){
   FAC = GODERR / SUMERR;
 }
 else{
   FAC = 1.0;
 }

 adz_err[i]      = adz_err[i] * FAC;
 adz_err[adz_NUMINT] = adz_err[adz_NUMINT] * FAC;
}

void CTUtil::ADZCAL(function<double(double)> fcn, int i)
{
 double TEM, ER;

 double dx =  adz_v[i] - adz_u[i];
 double W  = (adz_u[i] + adz_v[i]) / 2.0;

 if(i == 1 && adz_ICTA > 0){
//                                                            Open LEFT end
   adz_fw[i] = adz_fa;
   adz_fa = fcn(adz_u[i] + dx / 4.0);

   SGLINT(adz_ICTA, adz_fa, adz_fw[i], adz_fv[i], dx, TEM, ER);
 }
 else if(i == adz_IB && adz_ICTB > 0){
//                                                           open RIGHT end
   adz_fw[i] = adz_fb;
   adz_fb = fcn(adz_v[i] - dx / 4.0);
   SGLINT(adz_ICTB, adz_fb, adz_fw[i], adz_fu[i], dx, TEM, ER);
 }
 else{
//                                                              Closed endS
   adz_fw[i] = fcn(W);
   TEM = dx * (adz_fu[i] + 4.0 * adz_fw[i] + adz_fv[i]) / 6.0;
//                                  Preliminary error Simpson - trapezoidal:
   ER  = dx * (adz_fu[i] - 2.0 * adz_fw[i] + adz_fv[i]) / 12.0;
 }

 adz_result[i] = TEM;
 adz_err   [i] = fabs(ER);
}

void CTUtil::SGLINT(int IACT, double F1, double F2, double F3, double dx, double &FINT, double &ESTER)
{
 double huge = 1e20;
//                                                   -=-=- sglint

//     Calculate end-interval using open-end algorithm based on function values
//     at three points at (1/4, 1/2, 1)DX from the indeterminant endpoint (0).

//                                                         Use quadratic formula
 double TEM = dx * (4.0*F1 + 3.0*F2 + 2.0*F3) / 9.0;
//                 Error est based on Diff between quadratic and linear integrals
 double ER  = dx * (4.0*F1 - 6.0*F2 + 2.0*F3) / 9.0;

//                          Invoke adaptive singular parametrization if IACT = 2
//                      Algorithm is based on the formula F(x) = AA + BB * x **CC
//                 where AA, BB & CC are determined from F(Dx/4), F(Dx/2) & F(Dx)

 if(IACT == 2){
   double T1 = F2 - F1;
   double T2 = F3 - F2;
   if(T1 * T2 <= 0.0){
     FINT = TEM;
     ESTER= ER;
     return;
   }
   double T3 = T2 - T1;
   if(fabs(T3) * huge < pow(T1, 2.0)){
     FINT = TEM;
     ESTER= ER;
     return;
   }
   double CC  = log (T2 / T1) / log(2.0);
   if(CC <= -0.8){
     FINT = TEM;
     ESTER= ER;
     return;
   }
   double BB  = pow(T1, 2.0) / T3;
   double AA  = (F1 * F3 - pow(F2, 2.0)) / T3;
//                                     Estimated integral based on A+Bx**C
   double TMP = dx * (AA + BB * pow(4.0, CC) / (CC + 1.0));
//                                  Error estimate based on the difference
   ER = TEM - TMP;
//                                         Use the improved integral value
   TEM= TMP;
 }
 FINT = TEM;
 ESTER= ER;
}

void CTUtil::TOTALZ()
{
 adz_RES = 0.0;
 adz_ERS = 0.0;
 for(int i = 1; i <= adz_NUMINT; i++){
   adz_RES = adz_RES + adz_result[i];
   adz_ERS = adz_ERS + adz_err[i];
 }

}

double CTUtil::GausInt(function<double(double)> fcn, double xl, double xr, double aerr, double rerr, double &ERR, int &IRT)
{
 int nmax = 100;

 vector<int> PTR = {0, 4, 10, 22, 46};// we don't use the PTR[0]
 vector<int> NORD = {0, 6, 12, 24, 48};// same as above

 vector<double> xlims(101);

 double TOLABS = aerr;
 double TOLREL = rerr;

 double Value = 0.0;

 int NLIMS = 2;
 xlims.at(1) = xl;
 xlims.at(2) = xr;

 double val = 0.0;
 bool isGOTO10 = false;
 while(1){// goto 10
   double AA = (xlims.at(NLIMS) - xlims.at(NLIMS-1)) / 2.0;
   double BB = (xlims.at(NLIMS) + xlims.at(NLIMS-1)) / 2.0;

   double tval = 0.0;
   for(int i = 1; i <= 3; i++){
     tval = tval + GausInt_W.at(i) * (fcn(BB + AA * GausInt_R.at(i)) + fcn(BB - AA * GausInt_R.at(i)));
   }
   tval = tval * AA;

   for(int j = 1; j <= 4; j++){
     val = 0.0;
     for(int i = PTR.at(j); i <= PTR.at(j) - 1 + NORD.at(j); i++){
       val = val + GausInt_W.at(i) * (fcn(BB + AA * GausInt_R.at(i)) + fcn(BB - AA * GausInt_R.at(i)));
     }
     val = val * AA;

     double TOL = TOLABS > (TOLREL * fabs(val)) ? TOLABS : (TOLREL * fabs(val));
     if(fabs(tval - val) < TOL){
       Value = Value + val;
       NLIMS = NLIMS - 2;
       if(NLIMS != 0){// goto 10
         isGOTO10 = true;
         break;
       }
       return Value;
     }
     tval = val;
   }

   if(isGOTO10){
     isGOTO10 = false;
     continue;
   }

   if(nmax == 2){
     Value = val;
     return Value;
   }
   if(NLIMS > (nmax - 2)){
     cout<<"GausInt = "<<Value<<"  "<<nmax<<"  "<<BB-AA<<"  "<<BB+AA<<endl;
     return Value;
   }
   xlims.at(NLIMS+1) = BB;
   xlims.at(NLIMS+2) = BB + AA;
   xlims.at(NLIMS) = BB;
   NLIMS = NLIMS+2;
 }

 return Value;
}

