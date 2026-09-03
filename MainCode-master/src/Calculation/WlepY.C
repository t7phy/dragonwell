#include "Calculation/CalcVBP.h"

void CalcVBP::WlepY(int Ibsn, int Ibem, int Itgt, double rs, double y, double ptmin, double &xsec)
{
 FortranArray1D<double> xa{1, 24};
 FortranArray1D<double> argp{1, 24};
 FortranArray1D<double> argm{1, 24};
 FortranArray1D<double> qa{1, 10};
 FortranArray1D<double> qb{1, 10};

 FortranArray2D<double> VKM2{1, NGN, 1, NGN};

 double ansp;

//  w/Z mass
 double xmw = vBnMas(Ibsn);
 double q = xmw;
 double s = rs * rs;
//
//  CDF uses pt(muon)>25     x=xmw/(2.*ptmin)
//
 double x = xmw / (2.0 * ptmin);
 double w = x + sqrt(x*x - 1.0);
 double xi= log(w);
//
//  In lowest order, the pt cut translates into simple 
//  limits on the xa integral
//
 double xamin = xmw / rs * exp(y - xi);
 double xamax = xmw / rs * exp(y + xi);
 if(xamax > 1.0) xamax = 1.0;
//
//  6-pt gaussian quadrature routine -- supplied below
//
// CPY  N=4 beacuse 4x6=24 for xa(24),argp(24),argm(24)

 gq11(xamin, xamax, 4, xa, argp, ansp);

 for(int j = 1; j <= 24; j++){
// CPY
   argp(j) = 0.0;
   argm(j) = 0.0;

   double xb = pow(xmw, 2.0) / (s * xa(j));

//
//  my parton distribution calls
//  replace with yours
//
   dist(xa(j), q, qa);
   dist(xb,    q, qb);
   double yh = y - 0.5 * log(xa(j) / xb);
   double st = 1.0 / cosh(yh);
   double ct = tanh(yh);

//==================================
//CPY 02/22/12; In the following two lines, the fcator st**2 is needed.
   double facp = pow((1.0 - ct), 2.0) * pow(st, 2.0);
   double facm = pow((1.0 + ct), 2.0) * pow(st, 2.0);

//==================================

//
//  notation is u,d,s,ubar,dbar,sbar,g,c,b 
//  for      i= 1,2,3,4,    5,   6,  7,8,9

   for(int IJ1 = 1; IJ1 <= 3; IJ1++){
     for(int IJ2 = 1; IJ2 <= 3; IJ2++){
       VKM2(IJ1, IJ2) = pow(VKM(IJ1, IJ2), 2.0);
     }
   }

   if((Ibem == -1) && (Itgt == 1)){
// For p-pbar
//  notation is u,d,s,ubar,dbar,sbar,g,c,b 
//  for      i= 1,2,3,4,    5,   6,  7,8,9

     if(Ibsn == 3){
// For W+ -> e^+ nu

       double term_u = qa(1)*(VKM2(1,1)*qb(2)+VKM2(1,2)*qb(3)+VKM2(1,3)*qb(9))
                     + qa(8)*(VKM2(2,1)*qb(2)+VKM2(2,2)*qb(3)+VKM2(2,3)*qb(9));

       double term_db = qb(4)*(VKM2(1,1)*qa(5)+VKM2(1,2)*qa(6)+VKM2(1,3)*qa(9))
                      + qb(8)*(VKM2(2,1)*qa(5)+VKM2(2,2)*qa(6)+VKM2(2,3)*qa(9));

       argp(j) = term_u * facp + term_db * facm;
     }
     else if(Ibsn == 2){
// For W- -> e- {\bar nu}

       double term_d = qb(1)*(VKM2(1,1)*qa(2)+VKM2(1,2)*qa(3)+VKM2(1,3)*qa(9))
                     + qb(8)*(VKM2(2,1)*qa(2)+VKM2(2,2)*qa(3)+VKM2(2,3)*qa(9));

       double term_ub = qa(4)*(VKM2(1,1)*qb(5)+VKM2(1,2)*qb(6)+VKM2(1,3)*qb(9))
                      + qa(8)*(VKM2(2,1)*qb(5)+VKM2(2,2)*qb(6)+VKM2(2,3)*qb(9));

       argm(j) = term_d * facm + term_ub * facp;
     }
     else{
       cout<<"Not yet implemented in wlepy.F Ibsn = "<<Ibsn<<endl;
       return;
     }
   }
   else if((Ibem == 1) && (Itgt == 1)){
// For p-p
//  notation is u,d,s,ubar,dbar,sbar,g,c,b 
//  for      i= 1,2,3,4,    5,   6,  7,8,9
     if(Ibsn == 3){
// For W+ -> e^+ nu
       double term_u = qa(1)*(VKM2(1,1)*qb(5)+VKM2(1,2)*qb(6)+VKM2(1,3)*qb(9))
                     + qa(8)*(VKM2(2,1)*qb(5)+VKM2(2,2)*qb(6)+VKM2(2,3)*qb(9));

       double term_db = qb(1)*(VKM2(1,1)*qa(5)+VKM2(1,2)*qa(6)+VKM2(1,3)*qa(9))
                      + qb(8)*(VKM2(2,1)*qa(5)+VKM2(2,2)*qa(6)+VKM2(2,3)*qa(9));

       argp(j) = term_u * facp + term_db * facm;
     }
     else if(Ibsn == 2){
// For W- -> e- {\bar nu}
       double term_d = qb(4)*(VKM2(1,1)*qa(2)+VKM2(1,2)*qa(3)+VKM2(1,3)*qa(9))
                     + qb(8)*(VKM2(2,1)*qa(2)+VKM2(2,2)*qa(3)+VKM2(2,3)*qa(9));

       double term_ub = qa(4)*(VKM2(1,1)*qb(2)+VKM2(1,2)*qb(3)+VKM2(1,3)*qb(9))
                      + qa(8)*(VKM2(2,1)*qb(2)+VKM2(2,2)*qb(3)+VKM2(2,3)*qb(9));

       argm(j) = term_d * facm + term_ub * facp;
     }
     else{
       cout<<"Not yet implemented in wlepy.F Ibsn = "<<Ibsn<<endl;
       return;
     }
   }
   else{
     cout<<"Not yet implemented in wlepy.F Ibem = "<<Ibem<<" Itgt = "<<Itgt<<endl;
     return;
   }

   argp(j) = argp(j) / xa(j);
   argm(j) = argm(j) / xa(j);
 }

 double ans;

 if(Ibsn == 3){
// For W+ -> e^+ nu
   gq11(xamin, xamax, 0, xa, argp, ans);
 }
 else if(Ibsn == 2){
// For W- -> e- {\bar nu}
   gq11(xamin, xamax, 0, xa, argm, ans);
 }
 else{                      // Ibsn   
   cout<<"Not yet implemented in wlepy.F (end)Ibsn = "<<Ibsn<<endl;
   return;
 }

//CPY 02/26/12: Here, we need to givean overall factor which includes the amplitude**2 of 
// (u dbar -> W^+* -> e+ nu) and other phase space fators.

// gamw is the width of W-boson (in GeV)
 double gamw = 2.1;
 double overall = (1.0/3.0/s) * (1.0/8.0) * pow(WCOUPL, 2.0) * (xmw/gamw);

//                                              X-section in pb - GeV**2
 double Xsec0 = 0.38937966 * 1e9;
 xsec = Xsec0 * ans * overall;
}

void CalcVBP::WlepAsymK(int Ird, int Ibsn, int Ibem, int Itgt, double rs, double y, double ptmin, double ptmax, double wp_kfac, double wm_kfac, double &asym)
{
//---------------------------------------------------------------------------
//pn12 Simplified WlepAsymK to ALWAYS read K factors as input parameters
//    wp_kfac and wm_kfac. Implemented a max PT cut on the decay lepton.
//CPY 02/22/12: To improve KM treatment and include b PDF contribution, 
//  with correct XMW, for Tevatron and LHC 
// Lai 2/10/12: minor revision to accommodate LHC data
//  Ird = 1: LO
//  Ird = 2: Resum with average k-factor obtained from CTEQ6.6M
//
//  Lai  2/2/10: revise K-factor treatment for Tevatron Run II
//  Lai 2/5/09: revise the Ird assignements (keep NLO choice)
//
//CPY 01/31/09: Generate K-factor for cteq6.6M pdf, from ResBos and LO calculations. 
// It is for e^+ from W^+ production at Tevatron Run-2 with \sqrt{S}=1960 GeV.
// Here, we ignore the energy dependence. (For TevatronRun-1 data, it should be 
// re-fit for \sqrt{S}=1800 GeV.)
// 
//  Lai 6/25/04 correct the incomplete implementation for read in from file
//              and clear up some unused/unnecessary stuff
//  Lai 4/2/97, 9/2/97, 9/16/97
//  add Ird switch for NLO and Resum K-factor
//  The K-factor parametrizations are obtained by RESBOS using CTEQ4M 
//  or read in from kfac.wasy file.
//
//  Ird = 1, LO
//
//  6/25/04 
//  Ird = 2, NLO with average k-factor obtained from CTEQ4M 
//  Ird = 3, Resum with average k-factor obtained from CTEQ4M 
//  Ird = 4, read in k-factor from kfac.wasy 
//---------------------------------------------------------------------------
//  calculates the LO w lepton asymmetry. See Barger and Phillips 
//  "Collider Physics" pgs 254-256. Note: theta-hat on pgs 255, 256 
//  is - (theta-hat) on page 254!  
//
//  J.F. Owens    June 30, 1994 ; modified, wkt 7/2/94
//
//  rs = sqrt(s)   y=lepton rapidity    ptmin=minimal pt of lepton

 double Q = vBnMas(Ibsn);
 double rtau = Q / rs;

//pn12 At the lowest order,  the integration over cos(theta_*)
//  in the CS frame for a fixed LEPTON rapidity y translates
//  into integration over the momentum fraction xa in the interval(s)
//  determined by the lower and upper cuts on the pT of the lepton.
//  If pT_lepton > pTmin, the integration proceeds over one interval
//  xamin < xa < xamax, where xamin and xamax are the functions 
//  of the sin(theta_*)_min = 2*pTmin/Q in the CS frame. 
//  If pTmin < pT_lepton < pTmax, the integration is carried out 
//  over two xa intervals 

//pn12 Combinations of ptmin and ptmax that determine integration limits

 double xkappa1 = Q/(2.0*ptmin);
 double xkappa2 = (Q/(2.0*ptmax)) > 1.0 ? Q/(2.0*ptmax) : 1.0;
 double w1 = xkappa1 + sqrt(pow(xkappa1, 2.0) - 1.0);
 double w2 = xkappa2 + sqrt(pow(xkappa2, 2.0) - 1.0);
 double rtauey = rtau * exp(y);

 double ansp = 0.0;
 double ansm = 0.0;

//pn12 Compute the integral over the first xa interval
 double xamin = rtauey/w1;
 double xamax = (rtauey/w2) < rtauey ? rtauey/w2 : rtauey;
 double tp, tm;
 ComputeBorn(Ibem, Itgt, xamin, xamax, rtau, Q, y, tp, tm);

 ansp = tp;
 ansm = tm;

//pn12 Compute the integral over the second xa interval; sum
//     two integrals together
 xamin = (rtauey*w2) > rtauey ? rtauey*w2 : rtauey;
 xamax = (rtauey*w1) < 1.0 ? rtauey*w1 : 1.0;
 if(xamin < 1.0){
   double tp, tm;
   ComputeBorn(Ibem, Itgt, xamin, xamax, rtau, Q, y, tp, tm);
   ansp = ansp + tp;
   ansm = ansm + tm;
 }
 if(Ird > 1){
// (N)NLO: multiply by a  K factor
   ansp = ansp*wp_kfac;
   ansm = ansm*wm_kfac;
 }                     // Ird>1

 asym=(ansp-ansm)/(ansp+ansm);
}

void CalcVBP::ComputeBorn(int Ibem, int Itgt, double xamin, double xamax, double rtau, double Q, double y, double &tp, double &tm)
{
//pn12 Computes the Born cross section by integrating xa over the 
// interval between xamin and xamax
//
//  6-pt gaussian quadrature routine -- supplied below
//
//CPY  N=4 beacuse 4x6=24 for xa(24),argp(24),argm(24)

 FortranArray1D<double> xa{1, 24};
 FortranArray1D<double> argp{1, 24};
 FortranArray1D<double> argm{1, 24};
 FortranArray1D<double> qa{1, 10};
 FortranArray1D<double> qb{1, 10};

 FortranArray2D<double> VKM2{1, NGN, 1, NGN};

 int NGN = 3;

 double ansp;// yfu remind this place, when N > 0, the ansp will not be changed
 gq11(xamin, xamax, 4, xa, argp, ansp);

 for(int j = 1; j <= 24; j++){
   double xb = pow(rtau, 2.0) / xa(j);
//
//  my parton distribution calls
//  replace with yours

   dist(xa(j), Q, qa);
   dist(xb,    Q, qb);
   double yh = y - 0.5 * log(xa(j) / xb);  //lepton rapidity in CS frame
   double st = 1.0 / cosh(yh);             //sin(theta_*) in CS frame
   double ct = tanh(yh);                   //cos(theta_*) in CS frame

//CPY 02/22/12; In the following two lines, the fcator st**2 is needed.
   double facp = pow((1.0 - ct), 2.0) * pow(st, 2.0);   //angular prefactors for LO structure
   double facm = pow((1.0 + ct), 2.0) * pow(st, 2.0);   //functions

   for(int IJ1 = 1; IJ1 <= 3; IJ1++){
     for(int IJ2 = 1; IJ2 <= 3; IJ2++){
       VKM2(IJ1, IJ2) = pow(VKM(IJ1, IJ2), 2.0);
     }
   }

   if((Ibem == -1) && (Itgt == 1)){
// For p-pbar
//  notation is u,d,s,ubar,dbar,sbar,g,c,b 
//  for      i= 1,2,3,4,    5,   6,  7,8,9

       double term_u = qa(1)*(VKM2(1,1)*qb(2)+VKM2(1,2)*qb(3)+VKM2(1,3)*qb(9))
                     + qa(8)*(VKM2(2,1)*qb(2)+VKM2(2,2)*qb(3)+VKM2(2,3)*qb(9));

       double term_db = qb(4)*(VKM2(1,1)*qa(5)+VKM2(1,2)*qa(6)+VKM2(1,3)*qa(9))
                      + qb(8)*(VKM2(2,1)*qa(5)+VKM2(2,2)*qa(6)+VKM2(2,3)*qa(9));

       argp(j) = term_u * facp + term_db * facm;

       double term_d = qb(1)*(VKM2(1,1)*qa(2)+VKM2(1,2)*qa(3)+VKM2(1,3)*qa(9))
                     + qb(8)*(VKM2(2,1)*qa(2)+VKM2(2,2)*qa(3)+VKM2(2,3)*qa(9));

       double term_ub = qa(4)*(VKM2(1,1)*qb(5)+VKM2(1,2)*qb(6)+VKM2(1,3)*qb(9))
                      + qa(8)*(VKM2(2,1)*qb(5)+VKM2(2,2)*qb(6)+VKM2(2,3)*qb(9));

       argm(j) = term_d * facm + term_ub * facp;
   }
   else if((Ibem == 1) && (Itgt == 1)){
// For p-p
//  notation is u,d,s,ubar,dbar,sbar,g,c,b 
//  for      i= 1,2,3,4,    5,   6,  7,8,9

      double term_u = qa(1)*(VKM2(1,1)*qb(5)+VKM2(1,2)*qb(6)+VKM2(1,3)*qb(9))
                    + qa(8)*(VKM2(2,1)*qb(5)+VKM2(2,2)*qb(6)+VKM2(2,3)*qb(9));

      double term_db = qb(1)*(VKM2(1,1)*qa(5)+VKM2(1,2)*qa(6)+VKM2(1,3)*qa(9))
                     + qb(8)*(VKM2(2,1)*qa(5)+VKM2(2,2)*qa(6)+VKM2(2,3)*qa(9));

      argp(j) = term_u * facp + term_db * facm;

      double term_d = qb(4)*(VKM2(1,1)*qa(2)+VKM2(1,2)*qa(3)+VKM2(1,3)*qa(9))
                    + qb(8)*(VKM2(2,1)*qa(2)+VKM2(2,2)*qa(3)+VKM2(2,3)*qa(9));

      double term_ub = qa(4)*(VKM2(1,1)*qb(2)+VKM2(1,2)*qb(3)+VKM2(1,3)*qb(9))
                     + qa(8)*(VKM2(2,1)*qb(2)+VKM2(2,2)*qb(3)+VKM2(2,3)*qb(9));

      argm(j) = term_d * facm + term_ub * facp;
   }
   else{
     cout<<"Not yet implemented in WlepAsymK.F"<<endl;
     return;
   }

   argp(j) = argp(j) / xa(j);
   argm(j) = argm(j) / xa(j);
 }

 gq11(xamin, xamax, 0, xa, argp, tp);
 gq11(xamin, xamax, 0, xa, argm, tm);
}

void CalcVBP::gq11(double XMIN, double XMAX, int N, FortranArray1D<double> &X, FortranArray1D<double> Y, double &W)
{
 if(N > 0){
   int K = 0;
   this->gq11_NSAVE = N;
   this->gq11_D = (XMAX - XMIN) / N;
   double XL = XMIN - gq11_D;
   for(int i = 1; i <= N; i++){
     XL = XL + gq11_D;
     for(int j = 1; j <= 6; j++){// yfu remind this place, fortran code is DO 200(not this loop)
       K = K + 1;
       X(K) = XL + gq11_D * gq11_V.at(j);
       // if D0 200, there should be another "break;" line
     }
   }
 }
 else if(N <= 0){
   W = 0.0;
   int K = 0;
   for(int i = 1; i <= gq11_NSAVE; i++){
     for(int j = 1; j <= 6; j++){
        K = K + 1;
        W = W + Y(K) * gq11_R.at(j);
     }
   }
   W = W * gq11_D;
 }
}

void CalcVBP::dist(double x, double q, FortranArray1D<double> &pd)
{
      pd (1) =  GetPDF(1, 1, x, q);
      pd (2) =  GetPDF(1, 2, x, q);
      pd (3) =  GetPDF(1, 3, x, q);
      pd (4) =  GetPDF(1, -1, x, q);
      pd (5) =  GetPDF(1, -2, x, q);
      pd (6) =  GetPDF(1, -3, x, q);
      pd (7) =  GetPDF(1, 0, x, q);
      pd (8) =  GetPDF(1, 4, x, q);
      pd (9) =  GetPDF(1, 5, x, q);
}

