#include "Calculation/CTUtil.h"

double CTUtil::SMPSNF(function<double(double)> fcn, double A, double B, int nx, double &err, int ier)
{
 double Value = 0.0;
 double trpz = 0.0;
 err = 0.0;
 int mxpt = 1000;
 vector<double> x(mxpt + 1);

 if(nx == 1){
   Value = 0.0;
   return Value;
 }

 if(nx < 0 || nx > mxpt){
   cout<<"nx = "<<nx<<" out of range in SIMPSON INTEGRATION ROUTINE"<<endl;
   return 0.0;
 }

 double dx = (B - A) / (double)(nx - 1);
 if(dx <= 0.0){
   cout<<"DX <= 0 in SMPSNF, DX = "<<dx<<endl;
   return 0.0;
 }

 for(int i = 1; i <= nx; i++){
   x.at(i) = (A * (nx - i) + B * (i - 1)) / (double)(nx - 1);
   //cout<<"x("<<i<<") = "<<x.at(i)<<endl;
 }

 if(nx == 2){
   Value = (fcn(x[1]) + fcn(x[2])) * dx / 2.0;
 }
 else if(nx == 3){
   Value = (fcn(x[1]) + 4.0 * fcn(x[2]) + fcn(x[3])) * dx / 3.0;
 }
 else if(nx == 4){
   Value = ((fcn(x[1]) + 4.0 * fcn(x[2]) + fcn(x[3])) / 3.0 + (fcn(x[2]) * (-1.0) + 8.0 * fcn(x[3]) + 5.0 * fcn(x[4])) / 12.0 ) * dx;
 }
 else if(nx > 4){
   double se = fcn(x[2]);
   double so = 0.0;
   int NM1 = nx - 1;
   for(int i = 4; i <= NM1; ){
     int IM1 = i - 1;
     se = se + fcn(x[i]);
     so = so + fcn(x[IM1]);
     i = i + 2;
   }
   int ms = nx % 2;
   if(ms == 1){
     Value = (fcn(x[1]) + 4.0 * se + 2.0 * so + fcn(x[nx])) * dx / 3.0;
     trpz = (fcn(x[1]) + 2.0 * (se + so) + fcn(x[nx])) * dx / 2.0;
   }
   else{
     Value =(fcn(x[1]) + 4.0 * se + 2.0 * so + fcn(x[NM1])) * dx / 3.0 +(fcn(x[NM1-1]) * (-1.0) + 8.0 * fcn(x[NM1]) + 5.0 * fcn(x[nx])) * dx / 12.0;
     trpz = (fcn(x[1]) + 2.0 * (se + so + fcn(x[NM1])) + fcn(x[nx])) * dx / 2.0;
   }
   err = Value - trpz;
 }

 return Value;
}

double CTUtil::SMPSN1(function<double(double)> fcn, double A, double B, int nx, double &err, int IER)
{
// jcp: IER is not used -- should remove it here and in all calls!
//                                                  -=-=- smpsn2
//
//                       Does integral of FN(X)*dx from A TO B by SIMPSON'S METHOD
//
//                       Double precision version of SMPSN
//
//                       Input:          External function:      FN
//                                       Lower limit      :      A
//                                       Upper limit      :      B
//                                       Number of points :      Nx
//
//                       Uses (Nx-1) evenly spaced intervals.
//
//                       Output:         error estimate:         ERR
//                                       error code    :         IER
//

 double Value = 0.0;
 double trpz = 0.0;
 err = 0.0;
 int mxpt = 1000;
 vector<double> x(mxpt + 1);

 if(nx == 1){
   Value = 0.0;
   return Value;
 }

 if(nx < 0 || nx > mxpt){
   cout<<"nx = "<<nx<<" out of range in SIMPSON INTEGRATION ROUTINE"<<endl;
   return 0.0;
 }

 double dx = (B - A) / (double)(nx - 1);
 if(dx <= 0.0){
   cout<<"DX <= 0 in SMPSNF, DX = "<<dx<<endl;
   return 0.0;
 }

 for(int i = 1; i <= nx; i++){
   x.at(i) = (A * (nx - i) + B * (i - 1)) / (double)(nx - 1);
 }

 if(nx == 2){
   Value = (fcn(x[1]) + fcn(x[2])) * dx / 2.0;
 }
 else if(nx == 3){
   Value = (fcn(x[1]) + 4.0 * fcn(x[2]) + fcn(x[3])) * dx / 3.0;
 }
 else if(nx == 4){
   Value = ((fcn(x[1]) + 4.0 * fcn(x[2]) + fcn(x[3])) / 3.0 + (fcn(x[2]) * (-1.0) + 8.0 * fcn(x[3]) + 5.0 * fcn(x[4])) / 12.0 ) * dx;
 }
 else if(nx > 4){
   double se = fcn(x[2]);
   double so = 0.0;
   int NM1 = nx - 1;
   for(int i = 4; i <= NM1; ){
     int IM1 = i - 1;
     se = se + fcn(x[i]);
     so = so + fcn(x[IM1]);
     i = i + 2;
   }
   int ms = nx % 2;
   if(ms == 1){
     Value = (fcn(x[1]) + 4.0 * se + 2.0 * so + fcn(x[nx])) * dx / 3.0;
     trpz = (fcn(x[1]) + 2.0 * (se + so) + fcn(x[nx])) * dx / 2.0;
   }
   else{
     Value =(fcn(x[1]) + 4.0 * se + 2.0 * so + fcn(x[NM1])) * dx / 3.0 +(fcn(x[NM1-1]) * (-1.0) + 8.0 * fcn(x[NM1]) + 5.0 * fcn(x[nx])) * dx / 12.0;
     trpz = (fcn(x[1]) + 2.0 * (se + so + fcn(x[NM1])) + fcn(x[nx])) * dx / 2.0;
   }
   err = Value - trpz;
 }

 return Value;
}

double CTUtil::SMPSN2(function<double(double)> fcn, double A, double B, int nx, double &err, int IER)
{
// jcp: IER is not used -- should remove it here and in all calls!
//                                                  -=-=- smpsn2
//
//                       Does integral of FN(X)*dx from A TO B by SIMPSON'S METHOD
//
//                       Double precision version of SMPSN
//
//                       Input:          External function:      FN
//                                       Lower limit      :      A
//                                       Upper limit      :      B
//                                       Number of points :      Nx
//
//                       Uses (Nx-1) evenly spaced intervals.
//
//                       Output:         error estimate:         ERR
//                                       error code    :         IER
//

 double Value = 0.0;
 double trpz = 0.0;
 err = 0.0;
 int mxpt = 1000;
 vector<double> x(mxpt + 1);

 if(nx == 1){
   Value = 0.0;
   return Value;
 }

 if(nx < 0 || nx > mxpt){
   cout<<"nx = "<<nx<<" out of range in SIMPSON INTEGRATION ROUTINE"<<endl;
   return 0.0;
 }

 double dx = (B - A) / (double)(nx - 1);
 if(dx <= 0.0){
   cout<<"DX <= 0 in SMPSNF, DX = "<<dx<<endl;
   return 0.0;
 }

 for(int i = 1; i <= nx; i++){
   x.at(i) = (A * (nx - i) + B * (i - 1)) / (double)(nx - 1);
 }

 if(nx == 2){
   Value = (fcn(x[1]) + fcn(x[2])) * dx / 2.0;
 }
 else if(nx == 3){
   Value = (fcn(x[1]) + 4.0 * fcn(x[2]) + fcn(x[3])) * dx / 3.0;
 }
 else if(nx == 4){
   Value = ((fcn(x[1]) + 4.0 * fcn(x[2]) + fcn(x[3])) / 3.0 + (fcn(x[2]) * (-1.0) + 8.0 * fcn(x[3]) + 5.0 * fcn(x[4])) / 12.0 ) * dx;
 }
 else if(nx > 4){
   double se = fcn(x[2]);
   double so = 0.0;
   int NM1 = nx - 1;
   for(int i = 4; i <= NM1; ){
     int IM1 = i - 1;
     se = se + fcn(x[i]);
     so = so + fcn(x[IM1]);
     i = i + 2;
   }
   int ms = nx % 2;
   if(ms == 1){
     Value = (fcn(x[1]) + 4.0 * se + 2.0 * so + fcn(x[nx])) * dx / 3.0;
     trpz = (fcn(x[1]) + 2.0 * (se + so) + fcn(x[nx])) * dx / 2.0;
   }
   else{
     Value =(fcn(x[1]) + 4.0 * se + 2.0 * so + fcn(x[NM1])) * dx / 3.0 +(fcn(x[NM1-1]) * (-1.0) + 8.0 * fcn(x[NM1]) + 5.0 * fcn(x[nx])) * dx / 12.0;
     trpz = (fcn(x[1]) + 2.0 * (se + so + fcn(x[NM1])) + fcn(x[nx])) * dx / 2.0;
   }
   err = Value - trpz;
 }

 return Value;
}

