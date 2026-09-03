#include "Calculation/CalcDIS.h"

void CalcDIS::SFnConv(FortranArray1D<double> SFnIred, FortranArray1D<double> g2chi, FortranArray1D<double> &SFnTen, FortranArray1D<double> &SFnHel)
{
//                  ------------------------------
//     Given the Ireducible set of structure functions,
//       Parity conserving: 
//              transverse/longitudinal, chirality symmetric/mixed SFnIred(1,2,3,4)
//       Parity violating, transverse, chirality anti-symmetric    SFnIred(5) ;
//     and the chiral coupling combinations,
//       g2chi(1,2,3)             (symmetric/mixed/anti-symmetric) ,
//         1 : gLq(1)*gLq(2) + gRq(1)*gRq(2) 
//         2 : gLq(1)*gRq(2) + gRq(1)*gLq(2)       ! (1,2) refer to the two VecBoson vertices
//         3 : gLq(1)*gLq(2) - gRq(1)*gRq(2)
//     this simple routine returns the Helicity Structure Functions, 
//       SFnHel(-1:1)             (F_Left/Long./Right) 
//     and the Tensor Structure Functions,
//       SFnTen(1,2,3), defined as F_1/2/3:
//       F_1 = F_L + F_R              (2.F_transverse = 2.F_1^conventional)  
//       F_2 = F_L + F_R + 2.F_long   (F_2^conventional / x)
//       F_3 = F_L - F_R
//                  ------------------------------

//                                                 parity-conserving combinations
 double TransPC   = g2chi(1) * SFnIred(1) + g2chi(2) * SFnIred(2);
 SFnHel(0) = g2chi(1) * SFnIred(3) + g2chi(2) * SFnIred(4);
//                                                  parity-violating Piece   
 double TransPV   = g2chi(3) * SFnIred(5);

 SFnHel( 1) = TransPC - TransPV;
 SFnHel(-1) = TransPC + TransPV;

 SFnTen(1) = 2.0 * TransPC;
 SFnTen(2) = SFnTen(1) + 2.0 * SFnHel(0);    // A Power-law correction factor omitted here
 SFnTen(3) = 2.0 * TransPV;                  // A Power-law correction factor omitted here

/* cout<<"SFnIred[1, 5] = ";
 for(int i = 1; i <= 5; i++){
   cout<<SFnIred(i)<<"  ";
 }
 cout<<endl;
 cout<<"g2chi[1, 3] = ";
 for(int i = 1; i <= 3; i++){
   cout<<g2chi(i)<<"  ";
 }
 cout<<endl;
*/
 //cout<<"SFnHel( 1) = "<<SFnHel( 1)<<" SFnHel(-1) = "<<SFnHel(-1)<<endl;
 //cout<<"SFnTen(1) = "<<SFnTen(1)<<" SFnTen(2) = "<<SFnTen(2)<<" SFnTen(3) = "<<SFnTen(3)<<endl;

}

void CalcDIS::F2LConvNC(double F2o, double FLo, FortranArray1D<double> &SFnTen, FortranArray1D<double> &SFnHel)
{
//pn11 Construct tensor and helicity structure functions SFnTen and
//     SFnHel from input structure functions F2, FL
//
//     Currently works for neutral-current DIS only

                    // input variables Flo3,F2o,F3o3 inherited from parent.
 SFnHel(0)= FLo;
 SFnTen(2)= F2o;
 SFnTen(3)= 0.0; // No F_3 structure function for the moment

 SFnTen(1) = SFnTen(2)- 2.0 * SFnHel(0);
 SFnHel(1) =(SFnTen(1)- SFnTen(3))/2.0;
 SFnHel(-1)=(SFnTen(1)+ SFnTen(3))/2.0;

}

