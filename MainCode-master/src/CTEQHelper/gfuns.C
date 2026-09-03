#include "CTEQHelper/gfuns.h"

gfuns::gfuns()
{

}

gfuns::gfuns(int flag)
{
 this->flag = flag;
}

double gfuns::fcn(double x)
{
 switch(this->flag){

   case 848: {
     //CT18NNLO gluon

     double aa1 = a1;
     double aa2;
     double y;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }

     y = sqrt(x);
     double cc1 = (3.0 + 2.0 * a1) / 3.0;
     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double gfun = exp(tem) * (
                            sinh(a3) *                     pow((1.0 - y), 3.0) + 
                            sinh(a4) * 3.0 * pow(y, 1.0) * pow((1.0 - y), 2.0) +
                                 cc1 * 3.0 * pow(y, 2.0) * pow((1.0 - y), 1.0) +
                                             pow(y, 3.0));
     return gfun;
   }

   case 981: {
     //CT18NNLO u valence/d valence

     double aa1 = a1;
     double aa2;
     double y;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }

     y = sqrt(x);
     double aa6 = 1.0 + a1 / 2.0;
     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double gfun = exp(tem) * (
                            sinh(a3) *                     pow((1.0 - y), 4.0) +
                            sinh(a4) * 4.0 * pow(y, 1.0) * pow((1.0 - y), 3.0) +
                            sinh(a5) * 6.0 * pow(y, 2.0) * pow((1.0 - y), 2.0) +
                                 aa6 * 4.0 * pow(y, 3.0) * pow((1.0 - y), 1.0) +
                                             pow(y, 4.0));
     return gfun;
   }

   case 218: {
     //CT18NNLO dpu

     double aa1 = a1;
     double aa2;
     double y;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{ 
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }
   
     y = 1.0 - pow(1.0 - sqrt(x), a3); 
     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);
   
     double poly1 = (                      pow((1.0 - y), 5.0) +
                 a4 * 5.0  * pow(y, 1.0) * pow((1.0 - y), 4.0) +
                 a5 * 10.0 * pow(y, 2.0) * pow((1.0 - y), 3.0) +
                 a6 * 10.0 * pow(y, 3.0) * pow((1.0 - y), 2.0) +
                 a7 * 5.0  * pow(y, 4.0) * pow((1.0 - y), 1.0) +
                             pow(y, 5.0));

     double poly2 = (                      pow((1.0 - y), 5.0) +
                a8  * 5.0  * pow(y, 1.0) * pow((1.0 - y), 4.0) +
                a9  * 10.0 * pow(y, 2.0) * pow((1.0 - y), 3.0) +
                a10 * 10.0 * pow(y, 3.0) * pow((1.0 - y), 2.0) +
                a11 * 5.0  * pow(y, 4.0) * pow((1.0 - y), 1.0) +
                a12 *        pow(y, 5.0));

     double dbar = exp(tem) * poly1;
     double ubar = exp(tem) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun = dbar + ubar;

     return gfun;
   }

   case 219: {
     //CT18NNLO dmu

     double aa1 = a1;
     double aa2;
     double y;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }

     y = 1.0 - pow(1.0 - sqrt(x), a3);
     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double poly1 = (                      pow((1.0 - y), 5.0) +
                 a4 * 5.0  * pow(y, 1.0) * pow((1.0 - y), 4.0) +
                 a5 * 10.0 * pow(y, 2.0) * pow((1.0 - y), 3.0) +
                 a6 * 10.0 * pow(y, 3.0) * pow((1.0 - y), 2.0) +
                 a7 * 5.0  * pow(y, 4.0) * pow((1.0 - y), 1.0) +
                             pow(y, 5.0));

     double poly2 = (                      pow((1.0 - y), 5.0) +
                a8  * 5.0  * pow(y, 1.0) * pow((1.0 - y), 4.0) +
                a9  * 10.0 * pow(y, 2.0) * pow((1.0 - y), 3.0) +
                a10 * 10.0 * pow(y, 3.0) * pow((1.0 - y), 2.0) +
                a11 * 5.0  * pow(y, 4.0) * pow((1.0 - y), 1.0) +
                a12 *        pow(y, 5.0));

     double dbar = exp(tem) * poly1;
     double ubar = exp(tem) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun;

     if(ubar > 0.0){
       double dou = dbar / ubar;
       double ratio = (dou - 1.0) / (dou + 1.0);
       gfun = tan(ratio * 3.1415926535897932 / 2.0);
     }
     else{
       gfun = 1e15;
     }

     return gfun;
   }

   case 220: {
     //CT18NNLO strange

     double aa1 = a1;
     double aa2;
     double y;
     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.1 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.1 * log(1 + exp(10.0 * a2));
     }

     y = 1.0 - pow(1.0 - sqrt(x), a3);
     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double gfun = exp(tem) * (            pow((1.0 - y), 5.0) +
                 a4 * 5.0  * pow(y, 1.0) * pow((1.0 - y), 4.0) +
                 a5 * 10.0 * pow(y, 2.0) * pow((1.0 - y), 3.0) +
                 a6 * 10.0 * pow(y, 3.0) * pow((1.0 - y), 2.0) +
                 a7 * 5.0  * pow(y, 4.0) * pow((1.0 - y), 1.0) +
                 a8 *        pow(y, 5.0));

     return gfun;
   }

   case 310: {
     // CT25prel d valence

     double xx = x;
     if(nPara >= 15 && (fabs(a13) >= 1e-12 || fabs(a14) >= 1e-12)){
       xx = xstretch(xx, a13, a14);
     }

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double aa3 = sinh(a3);
     double aa4 = sinh(a4);
     double aa5 = sinh(a5);

     double aa20 = 2.5;
     y = pow(xx, aa20);

     double bb6 = 1.0 + (aa1 - 1.0) * 0.25 / aa20;
     double bb7 = 1.0;

     double tem = (aa1 - 1.0) * log(xx) + (aa2 + a6 * (1.0 - xx)) * log(1.0 - xx);

     double poly = (aa3 *                      pow((1.0 - y), 4.0) +
                    aa4 *  4.0 * pow(y, 1.0) * pow((1.0 - y), 3.0) +
                    aa5 *  6.0 * pow(y, 2.0) * pow((1.0 - y), 2.0) +
                    bb6 *  4.0 * pow(y, 3.0) * pow((1.0 - y), 1.0) +
                    bb7 *        pow(y, 4.0)                );

     double gfun = exp(tem) * poly;

     return gfun;
   }

   case 705: {
     // CT25prel u valence

     double xx = x;
     if(nPara >= 15 && (fabs(a13) >= 1e-12 || fabs(a14) >= 1e-12)){
       xx = xstretch(xx, a13, a14);
     }

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double aa6 = (aa1 - 1.0) * (9.0 / 10.0);
     double aa7 = (aa1 - 1.0) * (2.0 / 5.0);
     double aa8 = 0.0;

     y = sqrt(xx);

     double tem = ((aa1 - 1.0) * log(xx) + aa2 * log(1.0 - xx) +
             a3 *                      pow((1.0 - y), 5.0) +
             a4 *  5.0 * pow(y, 1.0) * pow((1.0 - y), 4.0) +
             a5 * 10.0 * pow(y, 2.0) * pow((1.0 - y), 3.0) +
            aa6 * 10.0 * pow(y, 3.0) * pow((1.0 - y), 2.0) +
            aa7 *  5.0 * pow(y, 4.0) * pow((1.0 - y), 1.0) +
            aa8 *        pow(y, 5.0)                );

     double gfun = exp(tem);

     return gfun;
   }

   case 406: {
     // CT25prel gluon

     double xx = x;

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double aa5 = 0.1;
     y = pow(xx, aa5);

     double tem = (aa1 - 1.0) * log(xx) + aa2 * log(1.0 - xx);

     double aa3 = sinh(a3);
     double aa4 = sinh(a4);

     double aay = 2.0 * (aa4 - 1.0) + (1.0 - aa1) / aa5;

     double gfun = exp(tem + aay * (y - 1.0)) * (
                 aa3                     * pow((1.0 - y), 2.0) +
                 aa4 * 2.0 * pow(y, 1.0) * pow((1.0 - y), 1.0) +
                             pow(y, 2.0)            );

     return gfun;
   }

   case 205: {
     // CT25prel dmu

     double xx = x;
     if(nPara >= 15 && (fabs(a13) >= 1e-12 || fabs(a14) >= 1e-12)){
       xx = xstretch(xx, a13, a14);
     }

     double aa1 = a1;
     double aa2;
     double aa3;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     if(a3 > 4.0){
       aa3 = a3;
     }
     else if(a3 < -4.0){
       aa3 = 0.10 * exp(10.0 * a3);
     }
     else{
       aa3 = 0.10 * log(1.0 + exp(10.0 * a3));
     }

     double aa4 = exp(a4);
     y = 1.0 - pow((1.0 - sqrt(xx)), aa4);

     double tem2 = (aa1 - 1.0) * log(xx) + aa2 * log(1.0 - xx);
     double tem3 = (aa1 - 1.0) * log(xx) + aa3 * log(1.0 - xx);

     double aa5 = sinh(a5);
     double aa6 = sinh(a6);
     double aa7 = sinh(a7);
     double aa8 = exp(a8);

     double poly1 = (                      pow((1.0 - y), 5.0) +
              aa5  *  5.0 *  pow(y, 1.0) * pow((1.0 - y), 4.0) +
              aa6  * 10.0 *  pow(y, 2.0) * pow((1.0 - y), 3.0) +
              aa7  * 10.0 *  pow(y, 3.0) * pow((1.0 - y), 2.0) +
              aa8  *  5.0 *  pow(y, 4.0) * pow((1.0 - y), 1.0) +
              aa8  *         pow(y, 5.0)               );

     double  aa9 = sinh(a9);
     double aa10 = sinh(a10);
     double aa11 = sinh(a11);
     double aa12 = exp(a12);

     double poly2 = (                      pow((1.0 - y), 5.0) +
              aa9  *  5.0 *  pow(y, 1.0) * pow((1.0 - y), 4.0) +
              aa10 * 10.0 *  pow(y, 2.0) * pow((1.0 - y), 3.0) +
              aa11 * 10.0 *  pow(y, 3.0) * pow((1.0 - y), 2.0) +
              aa12 *  5.0 *  pow(y, 4.0) * pow((1.0 - y), 1.0) +
              aa12 *         pow(y, 5.0)               );

     double dbar = exp(tem2 + 2.0 * (1.0 - aa1) * sqrt(xx)) * poly1;
     double ubar = exp(tem3 + 2.0 * (1.0 - aa1) * sqrt(xx)) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun;

     if(ubar > 0.0){
       double dou = dbar / ubar;
       double ratio = (dou - 1.0) / (dou + 1.0);
       gfun = tan(ratio * 3.1415926535897932 / 2.0);
     }
     else{
       gfun = 1e15;
     }

     return gfun;
   }

   case 204: {
     // CT25prel dpu

     double xx = x;
     if(nPara >= 15 && (fabs(a13) >= 1e-12 || fabs(a14) >= 1e-12)){
       xx = xstretch(xx, a13, a14);
     }

     double aa1 = a1;
     double aa2;
     double aa3;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     if(a3 > 4.0){
       aa3 = a3;
     }
     else if(a3 < -4.0){
       aa3 = 0.10 * exp(10.0 * a3);
     }
     else{
       aa3 = 0.10 * log(1.0 + exp(10.0 * a3));
     }

     double aa4 = exp(a4);
     y = 1.0 - pow((1.0 - sqrt(xx)), aa4);

     double tem2 = (aa1 - 1.0) * log(xx) + aa2 * log(1.0 - xx);
     double tem3 = (aa1 - 1.0) * log(xx) + aa3 * log(1.0 - xx);

     double aa5 = sinh(a5);
     double aa6 = sinh(a6);
     double aa7 = sinh(a7);
     double aa8 = exp(a8);

     double poly1 = (                      pow((1.0 - y), 5.0) +
              aa5  *  5.0 *  pow(y, 1.0) * pow((1.0 - y), 4.0) +
              aa6  * 10.0 *  pow(y, 2.0) * pow((1.0 - y), 3.0) +
              aa7  * 10.0 *  pow(y, 3.0) * pow((1.0 - y), 2.0) +
              aa8  *  5.0 *  pow(y, 4.0) * pow((1.0 - y), 1.0) +
              aa8  *         pow(y, 5.0)               );

     double  aa9 = sinh(a9);
     double aa10 = sinh(a10);
     double aa11 = sinh(a11);
     double aa12 = exp(a12);

     double poly2 = (                      pow((1.0 - y), 5.0) +
              aa9  *  5.0 *  pow(y, 1.0) * pow((1.0 - y), 4.0) +
              aa10 * 10.0 *  pow(y, 2.0) * pow((1.0 - y), 3.0) +
              aa11 * 10.0 *  pow(y, 3.0) * pow((1.0 - y), 2.0) +
              aa12 *  5.0 *  pow(y, 4.0) * pow((1.0 - y), 1.0) +
              aa12 *         pow(y, 5.0)               );

     double dbar = exp(tem2 + 2.0 * (1.0 - aa1) * sqrt(xx)) * poly1;
     double ubar = exp(tem3 + 2.0 * (1.0 - aa1) * sqrt(xx)) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun = dbar + ubar;

     return gfun;
   }

   case 3319: {
     // CT25prel strange

     double xx = x;
     if(nPara >= 15 && (fabs(a13) >= 1e-12 || fabs(a14) >= 1e-12)){
       xx = xstretch(xx, a13, a14);
     }

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     y = pow(xx, a3);

     double tem = (aa1 - 1.0) * log(xx) + aa2 * log(1.0 - xx);

     double gfun = exp(tem) * (
                                               pow((1.0 - y), 5.0) +
                   a4  *  5.0  * pow(y, 1.0) * pow((1.0 - y), 4.0) +
                   a5  * 10.0  * pow(y, 2.0) * pow((1.0 - y), 3.0) +
                   a6  * 10.0  * pow(y, 3.0) * pow((1.0 - y), 2.0) +
                   a7  *  5.0  * pow(y, 4.0) * pow((1.0 - y), 1.0) +
                   a8  *         pow(y, 5.0)               );

     return gfun;
   }

   case 881: {
     // CT25 candidate 072 u valence

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     y = sqrt(x);

     double aa6 = (aa1 + 1.0) / 2.0;

     double tem = ((aa1 - 1.0) * log(x) + aa2 * log(1.0 - x) );

     double gfun = exp(tem) * (
                     sinh(a3) *                   pow((1.0 - y), 4) +
                     sinh(a4) * 4.0 * pow(y, 1) * pow((1.0 - y), 3) +
                     sinh(a5) * 6.0 * pow(y, 2) * pow((1.0 - y), 2) +
                          aa6 * 4.0 * pow(y, 3) * pow((1.0 - y), 1) +
                                      pow(y, 4)                );

     return gfun;
   }

   case 215: {
     // CT25 candidate 072 dmu

     double aa1 = a1;
     double aa2;
     double aa3;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     if(a3 > 4.0){
       aa3 = a3;
     }
     else if(a3 < -4.0){
       aa3 = 0.10 * exp(10.0 * a3);
     }
     else{
       aa3 = 0.10 * log(1.0 + exp(10.0 * a3));
     }

     double tem2 = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);
     double tem3 = (aa1 - 1.0) * log(x) + aa3 * log(1.0 - x);

     // map a4 to be sure aa4 is positive
     // if aa4 > 2, the mapping from x to y is not monotonic -- that happens
     // in the best fits
     double aa4 = exp(a4);
     y = sqrt(x) * (aa4 + (1.0 - aa4) * sqrt(x));

     double aaz = 0.0;
     double aax = a8  + 0.4 * (aa1 - 1.0) / (aa4 - 2.0);

     double poly1 = (aaz *       pow((1.0 - y), 5) +
         a5 *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a6 * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a7 * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a8 *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         aax *       pow(y, 5)               );

     double aa9  = sinh(a9);
     double aa10 = sinh(a10);
     double aa11 = sinh(a11);
     double aa12 = exp(a12);

     double poly2 = (             pow((1.0 - y), 4) +
         aa9  * 4.0 * pow(y, 1) * pow((1.0 - y), 3) +
         aa10 * 6.0 * pow(y, 2) * pow((1.0 - y), 2) +
         aa11 * 4.0 * pow(y, 3) * pow((1.0 - y), 1) +
         aa12 *       pow(y, 4)               );

     double dbar = exp(tem2 + poly1);
     double ubar = exp(tem3) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun;

     if(ubar > 0.0){
       double dou = dbar / ubar;
       double ratio = (dou - 1.0) / (dou + 1.0);
       gfun = tan(ratio * 3.1415926535897932 / 2.0);
     }
     else{
       gfun = 1e15;
     }

     return gfun;
   }

   case 214: {
     // CT25 candidate 072 dpu

     double aa1 = a1;
     double aa2;
     double aa3;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     if(a3 > 4.0){
       aa3 = a3;
     }
     else if(a3 < -4.0){
       aa3 = 0.10 * exp(10.0 * a3);
     }
     else{
       aa3 = 0.10 * log(1.0 + exp(10.0 * a3));
     }

     double tem2 = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);
     double tem3 = (aa1 - 1.0) * log(x) + aa3 * log(1.0 - x);

     // map a4 to be sure aa4 is positive
     // if aa4 > 2, the mapping from x to y is not monotonic -- that happens
     // in the best fits
     double aa4 = exp(a4);
     y = sqrt(x) * (aa4 + (1.0 - aa4) * sqrt(x));

     double aaz = 0.0;
     double aax = a8  + 0.4 * (aa1 - 1.0) / (aa4 - 2.0);

     double poly1 = (aaz *       pow((1.0 - y), 5) +
         a5 *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a6 * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a7 * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a8 *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         aax *       pow(y, 5)               );

     double aa9  = sinh(a9);
     double aa10 = sinh(a10);
     double aa11 = sinh(a11);
     double aa12 = exp(a12);

     double poly2 = (             pow((1.0 - y), 4) +
         aa9  * 4.0 * pow(y, 1) * pow((1.0 - y), 3) +
         aa10 * 6.0 * pow(y, 2) * pow((1.0 - y), 2) +
         aa11 * 4.0 * pow(y, 3) * pow((1.0 - y), 1) +
         aa12 *       pow(y, 4)               );

     double dbar = exp(tem2 + poly1);
     double ubar = exp(tem3) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun = dbar + ubar;

     return gfun;
   }

   case 99400: {
     // CT25 candidate 118 d valence, u valence, gluon, strange

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     y = pow(x, a3);

     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double poly=    (
                 a4  *                    pow((1.0 - y), 4) +
                 a5  *  4.0 * pow(y, 1) * pow((1.0 - y), 3) +
                 a6  *  6.0 * pow(y, 2) * pow((1.0 - y), 2) +
                 a7  *  4.0 * pow(y, 3) * pow((1.0 - y), 1) +
                 a8  *        pow(y, 4)               );

     double gfun = exp(tem + poly);

     return gfun;
   }

   case 99403: {
     // CT25 candidate 118 dmu

     double aa2;
     double aa4;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     if(a4 > 4.0){
       aa4 = a4;
     }
     else if(a4 < -4.0){
       aa4 = 0.10 * exp(10.0 * a4);
     }
     else{
       aa4 = 0.10 * log(1.0 + exp(10.0 * a4));
     }

     double tem1 = (a1 - 1.0) * log(x) + aa2 * log(1.0 - x);
     double tem2 = (a3 - 1.0) * log(x) + aa4 * log(1.0 - x);

     y = pow(x, a5);

     double poly1 = ( a6  *               pow((1.0 - y), 4) +
                 a7  *  4.0 * pow(y, 1) * pow((1.0 - y), 3) +
                 a8  *  6.0 * pow(y, 2) * pow((1.0 - y), 2) +
                 a9  *  4.0 * pow(y, 3) * pow((1.0 - y), 1) +
                 //a10 *        pow(y, 4)               );
                 0.0                                    );

     double poly2 = ( a11 *            pow((1.0 - y), 4) +
                 a12 *  4.0 * pow(y, 1) * pow((1.0 - y), 3) +
                 a13 *  6.0 * pow(y, 2) * pow((1.0 - y), 2) +
                 a14 *  4.0 * pow(y, 3) * pow((1.0 - y), 1) +
                 //a15 *        pow(y, 3)               );
                 0.0                                 );

     double ubar = exp(tem1 + poly1);
     double dbar = exp(tem2 + poly2);

     double gfun;

     if(ubar > 0.0){
       double dou = dbar / ubar;
       double ratio = (dou - 1.0) / (dou + 1.0);
       gfun = tan(ratio * 3.1415926535897932 / 2.0);
     }
     else{
       gfun = 1e15;
     }

     return gfun;
   }

   case 99404: {
     // CT25 candidate 118 dpu

     double aa2;
     double aa4;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     if(a4 > 4.0){
       aa4 = a4;
     }
     else if(a4 < -4.0){
       aa4 = 0.10 * exp(10.0 * a4);
     }
     else{
       aa4 = 0.10 * log(1.0 + exp(10.0 * a4));
     }

     double tem1 = (a1 - 1.0) * log(x) + aa2 * log(1.0 - x);
     double tem2 = (a3 - 1.0) * log(x) + aa4 * log(1.0 - x);

     y = pow(x, a5);

     double poly1 = ( a6  *               pow((1.0 - y), 4) +
                 a7  *  4.0 * pow(y, 1) * pow((1.0 - y), 3) +
                 a8  *  6.0 * pow(y, 2) * pow((1.0 - y), 2) +
                 a9  *  4.0 * pow(y, 3) * pow((1.0 - y), 1) +
                 //a10 *        pow(y, 4)               );
                 0.0                                    );

     double poly2 = ( a11 *            pow((1.0 - y), 4) +
                 a12 *  4.0 * pow(y, 1) * pow((1.0 - y), 3) +
                 a13 *  6.0 * pow(y, 2) * pow((1.0 - y), 2) +
                 a14 *  4.0 * pow(y, 3) * pow((1.0 - y), 1) +
                 //a15 *        pow(y, 3)               );
                 0.0                                 );

     double ubar = exp(tem1 + poly1);
     double dbar = exp(tem2 + poly2);

     double gfun = dbar + ubar;

     return gfun;
   }

   case 704: {
     // CT25 candidate 156 d valence

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double aa6 = (aa1 - 1.0) * (9.0 / 20.0);
     double aa7 = (aa1 - 1.0) / 5.0;
     double aa8 = 0.0;

     y = x;

     double tem = ((aa1 - 1.0) * log(x) + aa2 * log(1.0 - x) +
         a3  *                    pow((1.0 - y), 5) +
         a4  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a5  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         aa6 * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         aa7 *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         aa8 *        pow(y, 5)                );

     double gfun = exp(tem);

     return gfun;
   }

   case 253: {
     // CT25 candidate 156 gluon

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double aa5 = 1.0;
     y = pow(x, aa5);

     double aa6 = (aa1 - 1.0) * 7.0 / (12.0 * aa5);
     double aa7 = (aa1 - 1.0)/(4.0 * aa5);
     double aa8 = 0.0;

     double tem = ((aa1 - 1.0) * log(x) + aa2 * log(1.0 - x) +
         a3  *                    pow((1.0 - y), 4) +
         a4  *  4.0 * pow(y, 1) * pow((1.0 - y), 3) +
         aa6 *  6.0 * pow(y, 2) * pow((1.0 - y), 2) +
         aa7 *  4.0 * pow(y, 3) * pow((1.0 - y), 1) +
         aa8 *        pow(y, 4)                );

     double gfun = exp(tem);

     return gfun;
   }

   case 203: {
     // CT25 candidate 156 dmu

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     y = 1.0 - pow((1.0 - sqrt(x)), a3);

     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double poly1 = (             pow((1.0 - y), 5) +
         a4  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a5  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a6  * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a7  *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         a7  *        pow(y, 5)               );

     double poly2 = (             pow((1.0 - y), 5) +
         a8  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a9  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a10 * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a11 *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         a12 *        pow(y, 5)               );

     double dbar = exp(tem + 2.0 * (1.0 - aa1) * sqrt(x)) * poly1;
     double ubar = exp(tem + 2.0 * (1.0 - aa1) * sqrt(x)) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun;

     if(ubar > 0.0){
       double dou = dbar / ubar;
       double ratio = (dou - 1.0) / (dou + 1.0);
       gfun = tan(ratio * 3.1415926535897932 / 2.0);
     }
     else{
       gfun = 1e15;
     }

     return gfun;
   }

   case 202: {
     // CT25 candidate 156 dpu

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     y = 1.0 - pow((1.0 - sqrt(x)), a3);

     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double poly1 = (             pow((1.0 - y), 5) +
         a4  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a5  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a6  * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a7  *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         a7  *        pow(y, 5)               );

     double poly2 = (             pow((1.0 - y), 5) +
         a8  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a9  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a10 * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a11 *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         a12 *        pow(y, 5)               );

     double dbar = exp(tem + 2.0 * (1.0 - aa1) * sqrt(x)) * poly1;
     double ubar = exp(tem + 2.0 * (1.0 - aa1) * sqrt(x)) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun = dbar + ubar;

     return gfun;
   }

   case 586: {
     // CT25 candidate 169 d valence

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double aa6 = 1.6;

     y = sqrt(x);

     double aax = (aa1 - 1.0) * (2.0 / 3.0);
     double aay = 0.0;

     double tem = ((aa1 - 1.0) * log(x) + aa6 * log(1.0 - x) +
           a3 *                    pow((1.0 - y), 3) +
           a4 *  3.0 * pow(y, 1) * pow((1.0 - y), 2) +
          aax *  3.0 * pow(y, 2) * pow((1.0 - y), 1) +
          aay *        pow(y, 3)                );

     double gfun = exp(tem) * (1.0 + exp(a5) * pow((1 - x), (aa2 - aa6)));

     return gfun;
   }

   case 996: {
     // CT25 candidate 169 strange

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     y = 1.0 - pow((1.0 - sqrt(x)), a3);

     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double gfun = exp(tem) * (pow((1.0 - y), 4) + y);

     return gfun;
   }

   case 285: {
     // CT25 candidate 243 dmu

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double aa3 = exp(a3);

     y = sqrt(x) * (aa3 + (1.0 - aa3) * sqrt(x));

     double aax = (2.0 - 2.0 * aa1 + 5.0 * (aa3 - 2.0) * (1.0 - a7 / a8));
     double poly1 = (             pow((1.0 - y), 5) +
         a4  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a5  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a6  * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a7  *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         a8  *        pow(y, 5)               );

     double aay = (2.0 - 2.0 * aa1 + 4.0 * (aa3 - 2.0) * (1.0 - a11 / a12));
     double poly2 = (            pow((1.0 - y), 4) +
         a9  * 4.0 * pow(y, 1) * pow((1.0 - y), 3) +
         a10 * 6.0 * pow(y, 2) * pow((1.0 - y), 2) +
         a11 * 4.0 * pow(y, 3) * pow((1.0 - y), 1) +
         a12 *       pow(y, 4)               );

     double dbar = exp(tem + aax * sqrt(x)) * poly1;
     double ubar = exp(tem + aay * sqrt(x)) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun;

     if(ubar > 0.0){
       double dou = dbar / ubar;
       double ratio = (dou - 1.0) / (dou + 1.0);
       gfun = tan(ratio * 3.1415926535897932 / 2.0);
     }
     else{
       gfun = 1e15;
     }

     return gfun;
   }

   case 284: {
     // CT25 candidate 243 dpu

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     double tem = (aa1 - 1.0) * log(x) + aa2 * log(1.0 - x);

     double aa3 = exp(a3);

     y = sqrt(x) * (aa3 + (1.0 - aa3) * sqrt(x));

     double aax = (2.0 - 2.0 * aa1 + 5.0 * (aa3 - 2.0) * (1.0 - a7 / a8));
     double poly1 = (             pow((1.0 - y), 5) +
         a4  *  5.0 * pow(y, 1) * pow((1.0 - y), 4) +
         a5  * 10.0 * pow(y, 2) * pow((1.0 - y), 3) +
         a6  * 10.0 * pow(y, 3) * pow((1.0 - y), 2) +
         a7  *  5.0 * pow(y, 4) * pow((1.0 - y), 1) +
         a8  *        pow(y, 5)               );

     double aay = (2.0 - 2.0 * aa1 + 4.0 * (aa3 - 2.0) * (1.0 - a11 / a12));
     double poly2 = (            pow((1.0 - y), 4) +
         a9  * 4.0 * pow(y, 1) * pow((1.0 - y), 3) +
         a10 * 6.0 * pow(y, 2) * pow((1.0 - y), 2) +
         a11 * 4.0 * pow(y, 3) * pow((1.0 - y), 1) +
         a12 *       pow(y, 4)               );

     double dbar = exp(tem + aax * sqrt(x)) * poly1;
     double ubar = exp(tem + aay * sqrt(x)) * poly2;

     if(dbar < 0.0) dbar = 0.0;
     if(ubar < 0.0) ubar = 0.0;

     double gfun = dbar + ubar;

     return gfun;
   }

   case 8424: {
     // CT25As, s-sbar

     double aa1 = a1;
     double aa2;
     double y;

     if(a2 > 4.0){
       aa2 = a2;
     }
     else if(a2 < -4.0){
       aa2 = 0.10 * exp(10.0 * a2);
     }
     else{
       aa2 = 0.10 * log(1.0 + exp(10.0 * a2));
     }

     // Typically, a3=0.5d0
     y = pow(x, a3);

     // Map a4 to a number between 0 and 1.        
     double xzero = 1.0 / (1.0 + exp(a4));

     // Typically, fix a5 and a6 in the fitinp file. 
     double xmin = a5;
     double xmax = a6;
     double small = 1e-6;

     if(a5 > a6){
       xmin = a6;
       xmax = a5;
       a5 = xmin;
       a6 = xmax;
     }

     if(xmin < small){
       xmin = small;
     }

     if(xmax > 1.0){
       xmax = 1.0;
     }

     double tem = ((aa1 - 1.0) * log(x) + aa2 * log(1.0 - x) );

     // CPY Force it to have one crossing (s-sbar) =0 for x between xmin and xmax.
     double tem2 = (y - xmin) * (y - xzero) * (y - xmax);

     double gfun = exp(tem) * tem2;

     return gfun;
   }

   default: {
     return 0.0;
   }

 }
}

