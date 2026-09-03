#include "Calculation/CalcDIS.h"

double CalcDIS::FahiNNLO(double x, double Q, int iFn, int igq, int ord, int iAB, int nf, double mu, double mh)
{
 int iHadn = 1;

 double ERR;
 int IER;

 auto xCahi_x_xf = [&](double z){

   double xpdf = 0.0;
   if(igq == 0){ // gluon
     xpdf = GetPDF(iHadn, 0, z, Q) * z;
   }
   else if(igq == 1){ // singlet
     xpdf = GetPDF(iHadn, 20, z, Q) * z;
   }

   double Value = xCahi(iFn, igq, ord, iAB, nf, x/z, Q, mu, mh) * xpdf / z;

   //cout<<"z = "<<z<<"  xCahi: "<<xCahi(iFn, igq, ord, iAB, nf, x/z, Q, mu, mh)<<endl;
   return Value;
 };

 cout<<"xPDF: "<<GetPDF(iHadn, 0, x, Q) * x<<"  alphas = "<<GetAlphaS(Q)<<endl;
 cout<<"x = "<<x<<"  xCahi = "<<xCahi(iFn, igq, ord, iAB, nf, x, Q, mu, mh)<<"  xCahi_x_xf = "<<xCahi_x_xf(x/0.5)<<endl;

 double xmax = 1.0;

 double a5 = xmax - 0.00000000001 * (xmax - x);

 double sum =
              SMPSNF(xCahi_x_xf,x + 0.00000000001*(a5-x),
                                x + 0.0000001*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.0000001*(a5-x),
                                x + 0.000001*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.000001*(a5-x),
                                x + 0.00001*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.00001*(a5-x),
                                x + 0.0001*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.0001*(a5-x),
                                x + 0.001*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.001*(a5-x),
                                x + 0.01*(a5-x),8, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.01*(a5-x),
                                x + 0.1*(a5-x),16, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.1*(a5-x),
                                x + 0.9*(a5-x),32, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.9*(a5-x),
                                x + 0.99*(a5-x),16, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.99*(a5-x),
                                x + 0.999*(a5-x),8, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.999*(a5-x),
                                x + 0.9999*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.9999*(a5-x),
                                x + 0.99999*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.99999*(a5-x),
                                x + 0.999999*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.999999*(a5-x),
                                x + 0.9999999*(a5-x),4, ERR, IER)
            + SMPSNF(xCahi_x_xf,x + 0.9999999*(a5-x),a5,4, ERR, IER);

 return sum;
}

// igq = 0: gluon; igq = 1: quark
double CalcDIS::xCahi(int iFn, int igq, int ord, int iAB, int nf, double z, double q, double mu, double mh)
{
 double Value = 0.0;

 if(ord == 0){
   if(igq == 0){
     if(iAB == 1){
       Value = z * HQcoef0(iFn,z,q,mu,mh); //get the xC back
     }
     else if(iAB==2){
       Value = z * HQcoef0A(iFn,z,q,mu,mh);
     }
   }
   else{
     Value = 0.0;
   }
 }
 else if(ord == 1){
   if(igq == 0){
     Value = z * HQcoef(iFn,z,q,mu,mh);
   }
   else if(igq == 1){
     Value = z * HQhqlcoef(iFn,z,q,mu,mh);
   }
   else{
     Value = 0.0;
   }
 }
 else if(ord == 2){
   if(iFn == 2){
     Value = xC2hi20AB(igq,iAB,z,q,mu,mh,nf);
   }
   else{
     Value = 0.0;
   }
 }

 return Value;
}

double CalcDIS::xC2hi20AB(int igq, int iAB, double x, double q, double mu, double mh, int nf)
{
 double pi = 3.14159265359;
 double ca = 3.0;
 double cf = 4.0 / 3.0;

 double m2 = mh * mh;
 double mq2 = q * q;
 double mu2 = mu * mu;
 double Lmu = log(mu2/m2); // Keping
 //double Lmu = log(m2/mu2);
 double xi = mq2 / m2;
 double eta = xi / 4.0 * (1.0 - x) / x - 1.0;
 if(eta <= 0.0){
   return 0.0;
 }
 double rho = 1.0/(1.0+eta);
 double beta = sqrt(1.0 - rho);
 double xbj = x;

 double conv = xi / pi * pow((4.0*pi), 4); // default prefactor alphas/(4pi^2) eh^2 Q^2/m^2=>eh^2*as*xi/pi
                                           // expansion parameter:(4pi*alphas)^2->as^2=alphas/(4pi)

 double Value = 0.0;
 double Term1 = 0.0, Term2 = 0.0, Term3 = 0.0, Term4 = 0.0, Term5 = 0.0;
 if(igq == 0 && iAB == 1){
 // Eq. (4.17) use aQg30A here
   //Value = cgt2(eta,xi,nf)
   //  + beta*beta*beta/(1.0+exp(2.0*(xi-4.0)))*(chx0g2(xbj,xi)*
   //    (-log(eta)/log(xbj))+(0.007*pow((log(xi)/log(5.0)), 4)-0.28)/(1.0+20.0/exp(1.0*log(eta))) )
   //  + beta*(1.0-1.0/(1.0+exp(2.0*(xi-4.0))))*(+xbj*(H2g3L0(xbj,mq2,m2,nf)-aQg30(xbj)+aQgA30(xbj)
   //  -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,nf))*pi/xi/pow((4.0*pi), 4) );


   if(nf == 3){
     /*Term1 = cgt2(eta,xi,nf) * conv;

     Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2g3L0(xbj,mq2,m2,nf) - aQg30(xbj) + aQgA30(xbj)
                    -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,nf)) );

     Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (chx0g2(xbj,xi) * (-log(eta)/log(xbj)) 
           + (0.007*pow((log(xi)/log(5.0)), 4)-0.28) / (1.0+20.0/exp(1.0*log(eta)))) * conv;

     double Lmu_Term1 = cgt2br1(eta, xi) * conv;

     double Lmu_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                      * (H2g3L1(xbj,mq2,m2,nf)
                       - 4.0 / 3.0 * H2g2L0(xbj,mq2,m2,nf)
                       - (10.0 / 3.0 * ca + 2.0 * cf) * H2g1L0(xbj,mq2,m2,nf));

     double Lmu_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbg2(xbj,xi) * (-log(eta)/log(xbj)) * (-1.0)
                      + (0.16086 - 0.00711 * log(xi) - 0.00549 * log(xi) * log(xi)) / (1.0+20.0/exp(1.0*log(eta))) ) * conv;

     Term4 = Lmu * (Lmu_Term1 + Lmu_Term2 + Lmu_Term3);

     double Lmu2_Term1 = cgt2br2(eta, xi) * conv;

     double Lmu2_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                       * (H2g3L2(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * (H2g2L1(xbj,mq2,m2,nf) - 2.0 / 3.0 * H2g1L0(xbj,mq2,m2,nf))
                        + 4.0 / 9.0 * H2g1L0(xbj,mq2,m2,nf));
     
     double Lmu2_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbbg2(xbj,xi) * (-log(eta)/log(xbj))) * conv;

     Term5 = Lmu * Lmu * (Lmu2_Term1 + Lmu2_Term2 + Lmu2_Term3);
     */
   }
   else if(nf == 4){
     /*Term1 = cgt2(eta,xi,nf) * conv;

     Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2g3L0(xbj,mq2,m2,nf) - aQg30(xbj) + aQgA30(xbj)
                    -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,nf)) );

     double Term2_new = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * ( - aQgA30(xbj) + aQg30new(xbj)));

     Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (chx0g2(xbj,xi) * (-log(eta)/log(xbj))
           + (0.007*pow((log(xi)/log(5.0)), 4)-0.28) / (1.0+20.0/exp(1.0*log(eta)))) * conv;

     double Lmu_Term1 = cgt2br1(eta, xi) * conv;

     double Lmu_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                      * (H2g3L1(xbj,mq2,m2,nf)
                       - 4.0 / 3.0 * H2g2L0(xbj,mq2,m2,nf)
                       - (10.0 / 3.0 * ca + 2.0 * cf) * H2g1L0(xbj,mq2,m2,nf));

     double Lmu_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbg2(xbj,xi) * (-log(eta)/log(xbj)) * (-1.0)
                      + (0.16086 - 0.00711 * log(xi) - 0.00549 * log(xi) * log(xi)) / (1.0+20.0/exp(1.0*log(eta))) ) * conv;

     Term4 = Lmu * (Lmu_Term1 + Lmu_Term2 + Lmu_Term3);

     double Lmu2_Term1 = cgt2br2(eta, xi) * conv;

     double Lmu2_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                       * (H2g3L2(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * (H2g2L1(xbj,mq2,m2,nf) - 2.0 / 3.0 * H2g1L0(xbj,mq2,m2,nf))
                        + 4.0 / 9.0 * H2g1L0(xbj,mq2,m2,nf));

     double Lmu2_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbbg2(xbj,xi) * (-log(eta)/log(xbj))) * conv;

     Term5 = Lmu * Lmu * (Lmu2_Term1 + Lmu2_Term2 + Lmu2_Term3);


     double tmp_Term4 = GetxC2Hg3Lmu1(1, x, q, mu, mh);
     double tmp_Term5 = GetxC2Hg3Lmu2(1, x, q, mu, mh);

     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<q;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))));
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<beta * beta * beta / (1.0+exp(2.0*(xi-4.0)));
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term1;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term2;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term3;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu_Term1;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu_Term2;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu_Term3;
     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term4;

     double xc2hqg20a, xc2hqg21, xc2hqg22;
     c2hqg20a_xfitter(eta, xi, xc2hqg20a);
     c2hqg21_xfitter(eta, xi, xc2hqg21);
     c2hqg22_xfitter(eta, xi, xc2hqg22);

     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * xc2hqg21 * conv;
     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * tmp_Term4 * (-1.0);

     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term5;
     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu * xc2hqg22 * conv;
     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu * tmp_Term5<<endl;

     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu * Lmu2_Term1;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu * Lmu2_Term2;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu * Lmu2_Term3;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term5;
     //cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term1+Term2+Term3+Term4+Term5<<endl;
     */
   }

   double xc2hqg20a_xfitter, xc2hqg21_xfitter, xc2hqg22_xfitter;
   c2hqg20a_xfitter(eta, xi, xc2hqg20a_xfitter);
   c2hqg21_xfitter(eta, xi, xc2hqg21_xfitter);
   c2hqg22_xfitter(eta, xi, xc2hqg22_xfitter);

   double xc2hqg20a, xc2hqg21, xc2hqg22;
   //c2hqg21(eta, xi, xc2hqg21);
   //c2hqg22(eta, xi, xc2hqg22);
   double xc2hqg20a_newasym, xc2hqg21_newasym;
   c2hqg20a_newasym(eta, xi, xc2hqg20a_newasym);
   //c2hqg21_newasym(eta, xi, xc2hqg21_newasym);

   //double Term2_new = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
   //                 * (xbj * ( - aQgA30(xbj) + aQg30new(xbj)));

   //double xfitter = (xc2hqg20a + xc2hqg21*Lmu + xc2hqg22*Lmu*Lmu) * conv + Term2_new;

   double as = GetAlphaS(mu) / 4.0 / pi;
   double LM = log(mh*mh/mu/mu);
   double LQm = log(q*q/mh/mh);
   double asym = WILS3HQ_REGH2gS(2, x, as, LM, LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;
   Value = asym;

   //Value = (xc2hqg21*Lmu + xc2hqg22*Lmu*Lmu) * conv;
   //Value = xc2hqg21_newasym*Lmu * conv;

   double eta_dumping = 1.0 / (1.0 + exp(0.3 * (eta - 100.0)));
   //Value = cgt2(eta,xi,nf) * conv * eta_dumping;
   //Value = cgt2br1(eta, xi) * conv * Lmu;
   //Value = cgt2br2(eta, xi) * conv * Lmu * Lmu;

   //Value = xc2hqg20a_newasym * conv + cgt2(eta,xi,nf) * conv * (eta_dumping - 1.0) + xc2hqg21_xfitter * conv * Lmu + xc2hqg22_xfitter * conv * Lmu * Lmu;
   //Value = xc2hqg20a_newasym * conv + cgt2(eta,xi,nf) * conv * (eta_dumping - 1.0);

   //Value = (H2g3L0(xbj,mq2,m2,3) - aQg30(xbj) + aQg30new(xbj)
   //        -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,3)) * xbj;

   //Value = (H2g3L1(xbj,mq2,m2,3)
   //         - 4.0 / 3.0 * H2g2L0(xbj,mq2,m2,3)
   //         - (10.0 / 3.0 * ca + 2.0 * cf) * H2g1L0(xbj,mq2,m2,3)) * xbj * Lmu;

   //Value = (H2g3L2(xbj,mq2,m2,3)
   //         - 4.0 / 3.0 * (H2g2L1(xbj,mq2,m2,3) - 2.0 / 3.0 * H2g1L0(xbj,mq2,m2,3))
   //         + 4.0 / 9.0 * H2g1L0(xbj,mq2,m2,3)) * xbj * Lmu * Lmu;


   double deltax = 1.0;
   //double asym_plus = WILS3HQ_REGH2gS(3, x, as, deltax, LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;
   //double asym_minus = WILS3HQ_REGH2gS(3, x, as, deltax * (-1.0), LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;
   //double asym_Lmu0 = WILS3HQ_REGH2gS(3, x, as, 0.0, LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;
   //double asym_plus2 = WILS3HQ_REGH2gS(3, x, as, deltax * 2.0, LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;
   //double asym_minus2 = WILS3HQ_REGH2gS(3, x, as, deltax * (-2.0), LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;
   //double asym_Lmu1 = (8.0 * asym_plus - 8.0 * asym_minus - asym_plus2 + asym_minus2) / (12.0 * deltax);
   //double asym_Lmu2 = (asym_plus + asym_minus - 2.0 * asym_Lmu0) / (2.0 * deltax * deltax);
   //double asym_Lmu3 = (asym_plus2 - asym_minus2 - 2.0 * asym_plus + 2.0 * asym_minus) / (12.0 * deltax * deltax * deltax);

   //Value = asym_Lmu1 * LM + asym_Lmu2 * LM * LM;
   //double fxi = 1.0/(1.0+exp(0.01*(xi-90.0)));
   //Value = asym_Lmu0;

   //Value = asym * beta * (1.0 - fxi) + xfitter * beta * beta * beta * fxi;
   //Value = asym * (1.0 - fxi) + xfitter * fxi;

   //Value = xc2hqg20a * conv + asym_Lmu1 * LM + asym_Lmu2 * LM * LM + asym_Lmu3 * LM * LM * LM;
   //Value = asym_Lmu0 + (xc2hqg21*Lmu + xc2hqg22*Lmu*Lmu) * conv;
   //Value = WILS3HQ_REGH2gS(1, x, as, LM, LQm, (double)nf, 2.0 / 5.0) * x / as / as / as;

   //Value = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * asym + beta * beta * beta / (1.0+exp(2.0*(xi-4.0))) * xfitter;

   //Value = xc2hqg20a * conv + Term2_new;
   //Value = xc2hqg21*Lmu * conv;
   //Value = xc2hqg22*Lmu*Lmu * conv;

//   Value = Term1 + Term2 + Term3 + Term4 + Term5;

   //cout<<"\n Inside xC2hi 0 1: "<<Value<<"  "<<m2<<"  "<<mq2<<"  "<<nf<<endl;
 }
 else if(igq == 0 && iAB == 2){
 // Eqs. (4.18) and (4.25) use aQg30B here
   //Value = cgt2(eta,xi,nf)
   //  + beta*beta*beta/(1.0+exp(2.0*(xi-4.0)))*(chx0g2(xbj,xi)*
   //    (-log(eta)/log(xbj))+9.0/4.0*(0.0245*pow((log(xi)/log(5.0)), 2)-0.17)/(1.0+10.7/exp(0.8*log(eta))) )
   //  + beta*beta*beta*(1.0-1.0/(1.0+exp(2.0*(xi-4.0))))*(+xbj*(H2g3L0(xbj,mq2,m2,nf)-aQg30(xbj)+aQgB30(xbj)
   //  -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,nf))*pi/xi/pow((4.0*pi), 4) )
   //  + 2.0*cgt2pade(eta,xi)/(1.0+exp(2.0*(xi-4.0)));

   if(nf == 3){
     /*Term1 = (cgt2(eta,xi,nf) + 2.0*cgt2pade(eta,xi)/(1.0+exp(2.0*(xi-4.0)))) * conv;

     Term2 = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2g3L0(xbj,mq2,m2,nf) - aQg30(xbj) + aQgB30(xbj)
                    -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,nf)) );

     Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (chx0g2(xbj,xi) * (-log(eta)/log(xbj))
           + (0.055*pow((log(xi)/log(5.0)), 2)-0.423) / (1.0+10.7/exp(0.8*log(eta)))) * conv;

     double Lmu_Term1 = cgt2br1(eta, xi) * conv;

     double Lmu_Term2 = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                      * (H2g3L1(xbj,mq2,m2,nf)
                       - 4.0 / 3.0 * H2g2L0(xbj,mq2,m2,nf)
                       - (10.0 / 3.0 * ca + 2.0 * cf) * H2g1L0(xbj,mq2,m2,nf));

     double Lmu_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbg2(xbj,xi) * (-log(eta)/log(xbj)) * (-1.0)
                      + (0.16086 - 0.00711 * log(xi) - 0.00549 * log(xi) * log(xi)) / (1.0+10.7/exp(0.8*log(eta))) ) * conv;

     Term4 = Lmu * (Lmu_Term1 + Lmu_Term2 + Lmu_Term3);

     double Lmu2_Term1 = cgt2br2(eta, xi) * conv;

     double Lmu2_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                       * (H2g3L2(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * (H2g2L1(xbj,mq2,m2,nf) - 2.0 / 3.0 * H2g1L0(xbj,mq2,m2,nf))
                        + 4.0 / 9.0 * H2g1L0(xbj,mq2,m2,nf));
     
     double Lmu2_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbbg2(xbj,xi) * (-log(eta)/log(xbj))) * conv;

     Term5 = Lmu * Lmu * (Lmu2_Term1 + Lmu2_Term2 + Lmu2_Term3);
     */
   }
   else if(nf == 4){
     /*Term1 = (cgt2(eta,xi,nf) + 2.0*cgt2pade(eta,xi)/(1.0+exp(2.0*(xi-4.0)))) * conv;

     Term2 = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2g3L0(xbj,mq2,m2,nf) - aQg30(xbj) + aQgB30(xbj)
                    -(16.0/9.0*ca-15.0/2.0*cf)*H2g1L0(xbj,mq2,m2,nf)) );

     Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (chx0g2(xbj,xi) * (-log(eta)/log(xbj))
           + (0.055*pow((log(xi)/log(5.0)), 2)-0.423) / (1.0+10.7/exp(0.8*log(eta)))) * conv;

     double Lmu_Term1 = cgt2br1(eta, xi) * conv;

     double Lmu_Term2 = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj * (H2g3L1(xbj,mq2,m2,nf));

     double Lmu_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbg2(xbj,xi) * (-log(eta)/log(xbj)) * (-1.0)
                      + (0.16086 - 0.00711 * log(xi) - 0.00549 * log(xi) * log(xi)) / (1.0+10.7/exp(0.8*log(eta))) ) * conv;

     Term4 = Lmu * (Lmu_Term1 + Lmu_Term2 + Lmu_Term3);

     double Lmu2_Term1 = cgt2br2(eta, xi) * conv;

     double Lmu2_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0)))) * xbj
                       * (H2g3L2(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * (H2g2L1(xbj,mq2,m2,nf) - 2.0 / 3.0 * H2g1L0(xbj,mq2,m2,nf))
                        + 4.0 / 9.0 * H2g1L0(xbj,mq2,m2,nf));
     
     double Lmu2_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbbg2(xbj,xi) * (-log(eta)/log(xbj))) * conv;

     Term5 = Lmu * Lmu * (Lmu2_Term1 + Lmu2_Term2 + Lmu2_Term3);
     */
   }

   double xc2hqg20b, xc2hqg21, xc2hqg22;
   c2hqg20b_xfitter(eta, xi, xc2hqg20b);
   c2hqg21_xfitter(eta, xi, xc2hqg21);
   c2hqg22_xfitter(eta, xi, xc2hqg22);

   double Term2_new = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
                    * (xbj * ( - aQgB30(xbj) + aQg30new(xbj)));

   Value = (xc2hqg20b + xc2hqg21*Lmu + xc2hqg22*Lmu*Lmu) * conv + Term2_new;

//   Value = Term1 + Term2 + Term3 + Term4 + Term5;


   //cout<<"\n Inside xC2hi 0 2: "<<Value<<"  "<<m2<<"  "<<mq2<<"  "<<nf<<endl;
 }
 else if(igq == 1 && iAB == 1){
 // Eq. (4.21) 
   //Value = beta*beta*beta/(1.0+exp(2.0*(xi-4.0)))*(4.0/9.0*
   //    chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.004*pow((log(xi)/log(5.0)), 4)-0.125)/(1.0+20.0/exp(1.0*log(eta))) )
   //  + beta*(1.0-1.0/(1.0+exp(2.0*(xi-4.0))))*(xbj*(H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSA30(xbj))*pi/xi/pow((4.0*pi), 4) );

   if(nf == 3){
     /*Term1 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSA30(xbj)));

     Term2 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (cf / ca * chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.004*pow((log(xi)/log(5.0)), 4)-0.125)/(1.0+20.0/exp(1.0*log(eta))) ) * conv;

     Term3 = Lmu * xbj * (H2q3L1(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * H2q2L0(xbj,mq2,m2,nf));

     Term4 = Lmu * Lmu * xbj * (H2q3L2(xbj,mq2,m2,nf)
                              - 4.0 / 3.0 * H2q2L1(xbj,mq2,m2,nf));
     */
   }
   else if(nf == 4){
     /*Term1 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSA30(xbj)));

     Term2 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (cf / ca * chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.004*pow((log(xi)/log(5.0)), 4)-0.125)/(1.0+20.0/exp(1.0*log(eta))) ) * conv;

     Term3 = Lmu * xbj * (H2q3L1(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * H2q2L0(xbj,mq2,m2,nf));

     Term4 = Lmu * Lmu * xbj * (H2q3L2(xbj,mq2,m2,nf)
                              - 4.0 / 3.0 * H2q2L1(xbj,mq2,m2,nf));

     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<q;
     double tmp_Term3 = GetxC2Hq3Lmu1(1, x, q, mu, mh);
     double tmp_Term4 = GetxC2Hq3Lmu2(1, x, q, mu, mh);

     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term3;
     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * tmp_Term3 * (-1.0);

     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Term4;
     cout<<setw(14)<<*right<<scientific<<setprecision(5)<<Lmu * Lmu * tmp_Term4<<endl;
     */
   }

   //Value = Term1 + Term2 + Term3 + Term4;

   double xc2hqps20a, xc2hqps21, xc2hqps22;
   c2hqps20a(eta, xi, xc2hqps20a);
   c2hqps21(eta, xi, xc2hqps21);
   c2hqps22(eta, xi, xc2hqps22);

   double Term1_new = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
                   * (xbj * (-aQqPSA30(xbj) + aQqPS30new(xbj)));

   Value = (xc2hqps20a + xc2hqps21*Lmu + xc2hqps22*Lmu*Lmu) * conv + Term1_new;

   double as = GetAlphaS(mu) / 4.0 / pi;
   double LM = log(mh*mh/q/q);
   double LQ = 0.0;
   Value = WILS3HQ_REGH2qPS(3, x, as, LM, LQ, (double)nf, -2.0 / 5.0) * x / as / as / as;

   //cout<<"\n Inside xC2hi 1 1: "<<Value<<"  "<<m2<<"  "<<mq2<<"  "<<nf<<endl;
   //cout<<"Inside xC2hi20AB: "<<chx0g2(xbj,xi)<<"  "<<H2q3L0(xbj,mq2,m2,nf)<<"  "<<aQqPS30(xbj)<<"  "<<aQqPSA30(xbj)<<endl;
 }
 else if(igq == 1 && iAB == 2){
 // Eq. (4.22)
   //Value = beta*beta*beta/(1.0+exp(2.0*(xi-4.0)))*(4.0/9.0*
   //    chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.0245*pow((log(xi)/log(5.0)), 2)-0.17)/(1.0+10.7/exp(0.8*log(eta))) )
   //  + beta*beta*beta*(1.0-1.0/(1.0+exp(2.0*(xi-4.0))))*(xbj*(H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSB30(xbj))*pi/xi/pow((4.0*pi), 4) );

   if(nf == 3){
     /*Term1 = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSB30(xbj)));

     Term2 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (cf / ca * chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.0245*pow((log(xi)/log(5.0)), 2)-0.17)/(1.0+10.7/exp(0.8*log(eta))) ) * conv;

     Term3 = Lmu * xbj * (H2q3L1(xbj,mq2,m2,nf)
                        - 4.0 / 3.0 * H2q2L0(xbj,mq2,m2,nf));

     Term4 = Lmu * Lmu * xbj * (H2q3L2(xbj,mq2,m2,nf)
                              - 4.0 / 3.0 * H2q2L1(xbj,mq2,m2,nf));
     */
   }
   else if(nf == 4){
     /*Term1 = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (xbj * (H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSB30(xbj)));

     Term2 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (cf / ca * chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.0245*pow((log(xi)/log(5.0)), 2)-0.17)/(1.0+10.7/exp(0.8*log(eta))) ) * conv;

     Term3 = Lmu * xbj * (H2q3L1(xbj,mq2,m2,nf));

     Term4 = Lmu * Lmu * xbj * (H2q3L2(xbj,mq2,m2,nf));
     */
   }

   double xc2hqps20b, xc2hqps21, xc2hqps22;
   c2hqps20b(eta, xi, xc2hqps20b);
   c2hqps21(eta, xi, xc2hqps21);
   c2hqps22(eta, xi, xc2hqps22);

   double Term1_new = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
                   * (xbj * (-aQqPSB30(xbj) + aQqPS30new(xbj)));

   Value = (xc2hqps20b + xc2hqps21*Lmu + xc2hqps22*Lmu*Lmu) * conv + Term1_new;

//   Value = Term1 + Term2 + Term3 + Term4;

   //cout<<"\n Inside xC2hi 1 2: "<<Value<<"  "<<m2<<"  "<<mq2<<"  "<<nf<<endl;
 }
 else{
   cout<<"igq = "<<igq<<" iAB = "<<iAB<<" is not supported"<<endl;
   return 0.0;
 }

 //Value = Value * conv; // xC:q+qb

 //if(igq == 0){
 //  Value = Value + Lmu * xbj * H2g3L1(xbj,mq2,m2,nf) + Lmu * Lmu * xbj * H2g3L2(xbj,mq2,m2,nf); //xC:q+qb
 //}
 //else if(igq == 1){
 //  Value = Value + Lmu * xbj * H2q3L1(xbj,mq2,m2,nf) + Lmu * Lmu * xbj * H2q3L2(xbj,mq2,m2,nf); //xC:q+qb
 //}

 return Value;
}

double CalcDIS::GetxC2Hg3Lmu1(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), 0.118 / 2.0 / Pi); // AlphaS is not necessary here

 double xi = pow((Q / MQ), 2.0);

 double conv1 = 1.0 / (xi / Pi / x) / pow(4.0 * Pi, 4);
 double conv2 = 1.0 / (16.0 * Pi * xi / x) / pow(4.0 * Pi, 2);
 double conv = xi / Pi / x * pow((4.0*Pi), 4);

 double beta0 = 11.0 / 3.0 * CA - 2.0 / 3.0 * GetNfl(Q);
 double beta1 = 34.0 / 3.0 * CA * CA - 20.0 / 3.0 * CA * TR * GetNfl(Q) - 4.0 * CF * TR * GetNfl(Q);

 hoppet::grid_quant C2Hg0 = hoppet::grid_quant(Hoppet_grid);
 vector<double> yvals = C2Hg0.grid().y_values();

 for(int iy = 0; iy < C2Hg0.size(); iy++){
   double y = yvals.at(iy);
   C2Hg0[iy] = sf_C2Hg0(y, 1) * 4.0;
 }

 hoppet::grid_conv P1gg = hoppet::grid_conv(Hoppet_grid, sf_P1gg);
 hoppet::grid_quant Term1 = P1gg * C2Hg0 * 4.0 - C2Hg0 * beta1;
 Term1 = Term1 * conv1;

 hoppet::grid_quant C2HqL0 = hoppet::grid_quant(Hoppet_grid);
 for(int iy = 0; iy < C2HqL0.size(); iy++){
   double y = yvals.at(iy);
   C2HqL0[iy] = sf_C2HqL0(y, 1) * 8.0;
 }

 hoppet::grid_conv Pqg = hoppet::grid_conv(Hoppet_grid, sf_Pqg);
 hoppet::grid_quant Term2 = Pqg * C2HqL0 * 2.0 * (2.0 * GetNfl(Q));
 Term2 = Term2 * conv2;

 hoppet::grid_quant C2HgL0 = hoppet::grid_quant(Hoppet_grid);
 for(int iy = 0; iy < C2HgL0.size(); iy++){
   double y = yvals.at(iy);
   C2HgL0[iy] = sf_C2HgL0(y, 1) * 8.0;
 }

 hoppet::grid_conv Pgg = hoppet::grid_conv(Hoppet_grid, sf_Pgg);
 hoppet::grid_quant Term3 = Pgg * C2HgL0 * 2.0 - C2HgL0 * 2.0 * beta0;
 Term3 = Term3 * conv2;

 hoppet::grid_quant xC2Hg3Lmu1 = Term1 + Term2 + Term3;

 Value = xC2Hg3Lmu1.at_x(x) * conv;
#endif

 return Value;
}

double CalcDIS::GetxC2Hg3Lmu2(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), 0.118 / 2.0 / Pi); // AlphaS is not necessary here

 double xi = pow((Q / MQ), 2.0);

 double conv1 = 1.0 / (xi / Pi / x) / pow(4.0 * Pi, 4);
 double conv2 = 1.0 / (16.0 * Pi * xi / x) / pow(4.0 * Pi, 2);
 double conv = xi / Pi / x * pow((4.0*Pi), 4);

 double beta0 = 11.0 / 3.0 * CA - 2.0 / 3.0 * GetNfl(Q);
 double beta1 = 34.0 / 3.0 * CA * CA - 20.0 / 3.0 * CA * TR * GetNfl(Q) - 4.0 * CF * TR * GetNfl(Q);

 hoppet::grid_quant C2Hg0 = hoppet::grid_quant(Hoppet_grid);
 vector<double> yvals = C2Hg0.grid().y_values();

 for(int iy = 0; iy < C2Hg0.size(); iy++){
   double y = yvals.at(iy);
   C2Hg0[iy] = sf_C2Hg0(y, 1) * 4.0;
 }

 hoppet::grid_conv Pgg_1 = hoppet::grid_conv(Hoppet_grid, sf_Pgg);
 hoppet::grid_conv Pgg_2 = hoppet::grid_conv(Hoppet_grid, sf_Pgg);

 hoppet::grid_quant tmp_Term1 = Pgg_1 * C2Hg0;
 hoppet::grid_quant Term1 = Pgg_2 * tmp_Term1 * 2.0 * 2.0 * 0.5;
 Term1 = Term1 * conv1;

 hoppet::grid_conv Pgq = hoppet::grid_conv(Hoppet_grid, sf_Pgq);
 hoppet::grid_conv Pqg = hoppet::grid_conv(Hoppet_grid, sf_Pqg);

 hoppet::grid_quant tmp_Term2 = Pgq * C2Hg0;
 hoppet::grid_quant Term2 = Pqg * tmp_Term2 * 2.0 * 2.0 * 0.5 * (2.0 * GetNfl(Q));
 Term2 = Term2 * conv1;

 hoppet::grid_conv Pgg = hoppet::grid_conv(Hoppet_grid, sf_Pgg);
 hoppet::grid_quant Term3 = Pgg * C2Hg0 * 2.0 * (-3.0 / 2.0 * beta0) + C2Hg0 * beta0 * beta0;
 Term3 = Term3 * conv1;

 hoppet::grid_quant xC2Hg3Lmu2 = Term1 + Term2 + Term3;

 Value = xC2Hg3Lmu2.at_x(x) * conv;
#endif

 return Value;
}

double CalcDIS::GetxC2Hq3Lmu1(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), 0.118 / 2.0 / Pi); // AlphaS is not necessary here

 double xi = pow((Q / MQ), 2.0);

 double conv1 = 1.0 / (xi / Pi / x) / pow(4.0 * Pi, 4);
 double conv2 = 1.0 / (16.0 * Pi * xi / x) / pow(4.0 * Pi, 2);
 double conv = xi / Pi / x * pow((4.0*Pi), 4);

 double beta0 = 11.0 / 3.0 * CA - 2.0 / 3.0 * GetNfl(Q);
 double beta1 = 34.0 / 3.0 * CA * CA - 20.0 / 3.0 * CA * TR * GetNfl(Q) - 4.0 * CF * TR * GetNfl(Q);

 hoppet::grid_quant C2Hg0 = hoppet::grid_quant(Hoppet_grid);
 vector<double> yvals = C2Hg0.grid().y_values();

 for(int iy = 0; iy < C2Hg0.size(); iy++){
   double y = yvals.at(iy);
   C2Hg0[iy] = sf_C2Hg0(y, 1) * 4.0;
 }

 hoppet::grid_conv P1gq = hoppet::grid_conv(Hoppet_grid, sf_P1gq);
 hoppet::grid_quant Term1 = P1gq * C2Hg0 * 4.0;
 Term1 = Term1 * conv1;

 hoppet::grid_quant C2HgL0 = hoppet::grid_quant(Hoppet_grid);
 for(int iy = 0; iy < C2HgL0.size(); iy++){
   double y = yvals.at(iy);
   C2HgL0[iy] = sf_C2HgL0(y, 1) * 8.0;
 }

 hoppet::grid_conv Pgq = hoppet::grid_conv(Hoppet_grid, sf_Pgq);
 hoppet::grid_quant Term2 = Pgq * C2HgL0 * 2.0;
 Term2 = Term2 * conv2;

 hoppet::grid_quant C2HqL0 = hoppet::grid_quant(Hoppet_grid);
 for(int iy = 0; iy < C2HqL0.size(); iy++){
   double y = yvals.at(iy);
   C2HqL0[iy] = sf_C2HqL0(y, 1) * 8.0;
 }

 hoppet::grid_conv Pqq = hoppet::grid_conv(Hoppet_grid, sf_Pqq);
 hoppet::grid_quant Term3 = Pqq * C2HqL0 * 2.0 - C2HqL0 * 2.0 * beta0;
 Term3 = Term3 * conv2;

 hoppet::grid_quant xC2Hq3Lmu1 = Term1 + Term2 + Term3;

 Value = xC2Hq3Lmu1.at_x(x) * conv;
#endif

 return Value;
}

double CalcDIS::GetxC2Hq3Lmu2(int ihadron, double x, double Q, double QMu, double MQ)
{
 double Value = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 SetQQMuMQ(Q, QMu, MQ, GetNfl(Q), 0.118 / 2.0 / Pi); // AlphaS is not necessary here

 double xi = pow((Q / MQ), 2.0);

 double conv1 = 1.0 / (xi / Pi / x) / pow(4.0 * Pi, 4);
 double conv2 = 1.0 / (16.0 * Pi * xi / x) / pow(4.0 * Pi, 2);
 double conv = xi / Pi / x * pow((4.0*Pi), 4);

 double beta0 = 11.0 / 3.0 * CA - 2.0 / 3.0 * GetNfl(Q);
 double beta1 = 34.0 / 3.0 * CA * CA - 20.0 / 3.0 * CA * TR * GetNfl(Q) - 4.0 * CF * TR * GetNfl(Q);

 hoppet::grid_quant C2Hg0 = hoppet::grid_quant(Hoppet_grid);
 vector<double> yvals = C2Hg0.grid().y_values();

 for(int iy = 0; iy < C2Hg0.size(); iy++){
   double y = yvals.at(iy);
   C2Hg0[iy] = sf_C2Hg0(y, 1) * 4.0;
 }

 hoppet::grid_conv Pgg = hoppet::grid_conv(Hoppet_grid, sf_Pgg);
 hoppet::grid_conv Pgq = hoppet::grid_conv(Hoppet_grid, sf_Pgq);

 hoppet::grid_quant tmp_Term1 = Pgg * C2Hg0;
 hoppet::grid_quant Term1 = Pgq * tmp_Term1 * 2.0 * 2.0 * 0.5;
 Term1 = Term1 * conv1;

 hoppet::grid_conv Pqq = hoppet::grid_conv(Hoppet_grid, sf_Pqq);

 hoppet::grid_quant tmp_Term2 = Pqq * C2Hg0;
 hoppet::grid_quant Term2 = Pgq * tmp_Term2 * 2.0 * 2.0 * 0.5;
 Term2 = Term2 * conv1;

 hoppet::grid_quant Term3 = Pgq * C2Hg0 * 2.0 * (-3.0 / 2.0 * beta0);
 Term3 = Term3 * conv1;

 hoppet::grid_quant xC2Hq3Lmu2 = Term1 + Term2 + Term3;

 Value = xC2Hq3Lmu2.at_x(x) * conv;
#endif

 return Value;
}

