#include "Calculation/CalcDIS.h"

void CalcDIS::MakeCoeffTable(TString FunctionName)
{
 vector<double> dlaeta = {
      -6.0, -5.83333333, -5.66666667, -5.5, -5.33333333,
      -5.16666667, -5.0, -4.83333333, -4.66666667, -4.5,
      -4.33333333, -4.16666667, -4.0, -3.83333333,
      -3.66666667, -3.5, -3.33333333, -3.16666667, -3.0,
      -2.83333333, -2.66666667, -2.5, -2.33333333,
      -2.16666667, -2.0, -1.83333333, -1.66666667, -1.5,
      -1.33333333, -1.16666667, -1.0, -0.83333333, -0.66666667,
      -0.5, -0.33333333, -0.16666667, 0.0, 0.16666667,
       0.33333333, 0.5, 0.66666667, 0.83333333, 1.0,
       1.16666667, 1.33333333, 1.5, 1.66666667, 1.83333333,
       2.0, 2.16666667, 2.33333333, 2.5, 2.66666667,
       2.83333333, 3.0, 3.16666667, 3.33333333, 3.5,
       3.66666667, 3.83333333, 4.0, 4.16666667, 4.33333333,
       4.5, 4.66666667, 4.83333333, 5.0, 5.16666667,
       5.33333333, 5.5, 5.66666667, 5.83333333, 6.0
 };

 vector<double> dlaxi = {
      -3.0, -2.83333333, -2.66666667, -2.5, -2.33333333,
      -2.16666667, -2.0, -1.83333333, -1.66666667, -1.5,
      -1.33333333,-1.16666667, -1.0,-0.83333333,-0.66666667,
      -0.5, -0.33333333, -0.16666667, 0.0, 0.16666667,
       0.33333333, 0.5, 0.66666667, 0.83333333, 1.0,
       1.16666667, 1.33333333, 1.5, 1.66666667, 1.83333333,
       2.0, 2.16666667, 2.33333333, 2.5, 2.66666667,
       2.83333333, 3.0, 3.16666667, 3.33333333, 3.5,
       3.66666667, 3.83333333, 4.0, 4.16666667, 4.33333333,
       4.5, 4.66666667, 4.83333333, 5.0
 };

 cout<<endl;
 cout<<endl;
 cout<<"Copy the following to the .h file:"<<endl;
 cout<<endl;
 cout<<endl;

 cout<<" virtual void "<<FunctionName<<"(double eta, double xi, double &Value);"<<endl;
 cout<<" FortranArray2D<double> "<<FunctionName<<"_calcpts;"<<endl;
 cout<<" FortranArray1D<double> "<<FunctionName<<"_dlaeta;"<<endl;
 cout<<" FortranArray1D<double> "<<FunctionName<<"_dlaxi;"<<endl;

 cout<<endl;
 cout<<endl;
 cout<<"Copy the following to the .C file:"<<endl;
 cout<<endl;
 cout<<endl;

 cout<<"void CalcDIS::"<<FunctionName<<"(double eta, double xi, double &Value)"<<endl;
 cout<<"{"<<endl;
 cout<<" if(!isInitialhqnnloMatrix) InitialhqnnloMatrix();"<<endl;
 cout<<" int neta = 73, nxi = 49;"<<endl;
 cout<<""<<endl;
 cout<<" int ixi, ieta;"<<endl;
 cout<<" double dleta = log10(eta);"<<endl;
 cout<<" double dlxi = log10(xi);"<<endl;
 cout<<" if (dlxi <= "<<FunctionName<<"_dlaxi(1)) dlxi = "<<FunctionName<<"_dlaxi(1);"<<endl;
 cout<<" if (dlxi >= "<<FunctionName<<"_dlaxi(nxi)) dlxi = "<<FunctionName<<"_dlaxi(nxi);"<<endl;
 cout<<" if (dleta >= "<<FunctionName<<"_dlaeta(neta)) dleta = "<<FunctionName<<"_dlaeta(neta);"<<endl;
 cout<<" if (dleta <= "<<FunctionName<<"_dlaeta(1)) dleta = "<<FunctionName<<"_dlaeta(1);"<<endl;
 cout<<" locate("<<FunctionName<<"_dlaeta,neta, dleta, ieta);"<<endl;
 cout<<" locate("<<FunctionName<<"_dlaxi, nxi, dlxi, ixi);"<<endl;
 cout<<"//     interpolating between the appropriate points"<<endl;
 cout<<" double delxi = 1.0 / 6.0;"<<endl;
 cout<<" double deleta = 1.0 / 6.0;"<<endl;
 cout<<"//  lagrange 3-pt."<<endl;
 cout<<" if (ixi <= 2) ixi = 2;"<<endl;
 cout<<" if (ixi >= 48) ixi = 48;"<<endl;
 cout<<" if (ieta <= 2) ieta = 2;"<<endl;
 cout<<" if (ieta >= 72) ieta = 72;"<<endl;
 cout<<""<<endl;
 cout<<" double pxi = (dlxi - "<<FunctionName<<"_dlaxi(ixi)) / delxi;"<<endl;
 cout<<""<<endl;
 cout<<" FortranArray1D<double> f{-1, 1};"<<endl;
 cout<<""<<endl;
 cout<<" f(-1) = pxi * (pxi - 1.0) / 2.0 * "<<FunctionName<<"_calcpts(ieta - 1, ixi - 1) +"<<endl;
 cout<<"         (1.0 - pxi * pxi) * "<<FunctionName<<"_calcpts(ieta - 1, ixi) +"<<endl;
 cout<<"         pxi * (pxi + 1.0) / 2.0 * "<<FunctionName<<"_calcpts(ieta - 1, ixi + 1);"<<endl;
 cout<<""<<endl;
 cout<<" f(0) = pxi * (pxi - 1.0) / 2.0 * "<<FunctionName<<"_calcpts(ieta, ixi - 1) +"<<endl;
 cout<<"        (1.0 - pxi * pxi) * "<<FunctionName<<"_calcpts(ieta, ixi) +"<<endl;
 cout<<"        pxi * (pxi + 1.0) / 2.0 * "<<FunctionName<<"_calcpts(ieta, ixi + 1);"<<endl;
 cout<<""<<endl;
 cout<<" f(1) = pxi * (pxi - 1.0) / 2.0 * "<<FunctionName<<"_calcpts(ieta + 1, ixi - 1) +"<<endl;
 cout<<"        (1.0 - pxi * pxi) * "<<FunctionName<<"_calcpts(ieta + 1, ixi) +"<<endl;
 cout<<"        pxi * (pxi + 1.0) / 2.0 * "<<FunctionName<<"_calcpts(ieta + 1, ixi + 1);"<<endl;
 cout<<""<<endl;
 cout<<" double peta = (dleta - "<<FunctionName<<"_dlaeta(ieta)) / deleta;"<<endl;
 cout<<""<<endl;
 cout<<" Value = peta * (peta - 1.0) / 2.0 * f(-1) +"<<endl;
 cout<<"         (1.0 - peta * peta) * f(0) +"<<endl;
 cout<<"         peta * (peta + 1.0) / 2.0 * f(1);"<<endl;
 cout<<"}"<<endl;

 cout<<endl;

 cout<<" neta = 73, nxi = 49;"<<endl;
 cout<<""<<endl;
 cout<<" "<<FunctionName<<"_calcpts.resize(1, neta, 1, nxi);"<<endl;
 cout<<""<<endl;

 int nf = 3;
 double pi = TMath::Pi();
 double m2 = 1.3 * 1.3;
 double mh = 1.3;

 for(int ixi = 0; ixi < dlaxi.size(); ixi++){
   cout<<" tmp = {"<<endl;
   for(int ieta = 0; ieta < dlaeta.size(); ieta++){
     double xi = pow(10.0, dlaxi.at(ixi));
     double eta = pow(10.0, dlaeta.at(ieta));
     double conv = xi / pi * pow((4.0*pi), 4);

     double ca = 3.0;
     double cf = 4.0 / 3.0;
     double rho = 1.0/(1.0+eta);
     double beta = sqrt(1.0 - rho);
     double xbj = xi / (4.0 * eta + 4.0 + xi);
     double mq2 = xi * m2;
     double mu2 = mq2 + 4.0 * m2;
     double mu = sqrt(mu2);
     double LQm = log(mq2/mh/mh);
     double as = GetAlphaS(mu) / 4.0 / pi;

     /*
     double Term1 = cgt2(eta,xi,nf);

     double asym_Lmu0 = WILS3HQ_REGH2gS(3, xbj, as, 0.0, LQm, (double)nf, 2.0 / 5.0) * xbj / as / as / as;

     double Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
           * (asym_Lmu0) / conv;

     double Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
           * (chx0g2(xbj,xi) * (-log(eta)/log(xbj))
           + (0.007*pow((log(xi)/log(5.0)), 4)-0.28) / (1.0+20.0/exp(1.0*log(eta))));

     double Value = Term1 + Term2 + Term3;
     //cout<<"  q = "<<sqrt(mq2)<<"  Term1 = "<<Term1<<"  Term2 = "<<Term2<<"  Term3 = "<<Term3<<"  Value = "<<Value<<endl;
     */

     double Value = (H2g3L1(xbj,mq2,m2,nf)
                     - 4.0 / 3.0 * H2g2L0(xbj,mq2,m2,nf)
                     - (10.0 / 3.0 * ca + 2.0 * cf) * H2g1L0(xbj,mq2,m2,nf)) * xbj / conv;


     /*
     double Lmu_Term1 = cgt2br1(eta, xi);

     double deltax = 1.0;
     double asym_plus = WILS3HQ_REGH2gS(3, xbj, as, deltax, LQm, (double)nf, 2.0 / 5.0) * xbj / as / as / as;
     double asym_minus = WILS3HQ_REGH2gS(3, xbj, as, deltax * (-1.0), LQm, (double)nf, 2.0 / 5.0) * xbj / as / as / as;
     double asym_plus2 = WILS3HQ_REGH2gS(3, xbj, as, deltax * 2.0, LQm, (double)nf, 2.0 / 5.0) * xbj / as / as / as;
     double asym_minus2 = WILS3HQ_REGH2gS(3, xbj, as, deltax * (-2.0), LQm, (double)nf, 2.0 / 5.0) * xbj / as / as / as;
     double asym_Lmu1 = (8.0 * asym_plus - 8.0 * asym_minus - asym_plus2 + asym_minus2) / (12.0 * deltax);

     double Lmu_Term2 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
                      * (asym_Lmu1 * (-1.0)) / conv;

     double Lmu_Term3 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
                      * (chxbg2(xbj,xi) * (-log(eta)/log(xbj)) * (-1.0)
                      + (0.16086 - 0.00711 * log(xi) - 0.00549 * log(xi) * log(xi)) / (1.0+20.0/exp(1.0*log(eta))) );

     double Value = Lmu_Term1 + Lmu_Term2 + Lmu_Term3;
     */

     /*
     double c2g_Lmu = GetxC2Hg3Lmu1(1, xbj, sqrt(mq2), sqrt(mu2), mh) / conv;
     double Value = c2g_Lmu * (-1.0);
     */

     /*
     double c2g_Lmu2 = GetxC2Hg3Lmu2(1, xbj, sqrt(mq2), sqrt(mu2), mh) / conv;
     double Value = c2g_Lmu2;
     */


     /*
     double c2q_Term1 = beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
             * (xbj * (H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSA30(xbj))) / conv;

     double c2q_Term2 = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
             * (cf / ca * chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.004*pow((log(xi)/log(5.0)), 4)-0.125)/(1.0+20.0/exp(1.0*log(eta))) );

     double Value = c2q_Term1 + c2q_Term2;
     */

     /*
     double c2q_Term1B = beta * beta * beta * (1.0-1.0/(1.0+exp(2.0*(xi-4.0))))
             * (xbj * (H2q3L0(xbj,mq2,m2,nf)-aQqPS30(xbj)+aQqPSB30(xbj))) / conv;

     double c2q_Term2B = beta * beta * beta / (1.0+exp(2.0*(xi-4.0)))
             * (cf / ca * chx0g2(xbj,xi)*(-log(eta)/log(xbj))+(0.0245*pow((log(xi)/log(5.0)), 2)-0.17)/(1.0+10.7/exp(0.8*log(eta))) );

     double Value = c2q_Term1B + c2q_Term2B;
     */

     /*
     double c2q_Term3 = GetxC2Hq3Lmu1(1, xbj, sqrt(mq2), sqrt(mu2), mh) / conv;
     double Value = c2q_Term3 * (-1.0);
     */

     /*
     double c2q_Term4 = GetxC2Hq3Lmu2(1, xbj, sqrt(mq2), sqrt(mu2), mh) / conv;
     double Value = c2q_Term4;
     */

     if(ieta % 5 == 0) cout<<"       ";
     cout<<setw(11)<<scientific<<setprecision(4)<<Value;
     if(ieta != dlaeta.size() - 1) cout<<",";
     if(ieta == dlaeta.size() - 1) cout<<"};"<<endl;
     if((ieta - 4) % 5 == 0) cout<<endl;
   }
   cout<<""<<endl;
   cout<<" for(int j = 1; j <= neta; j++){"<<endl;
   cout<<"   "<<FunctionName<<"_calcpts(j, "<<ixi + 1<<") = tmp.at(j - 1);"<<endl;
   cout<<" }"<<endl;
   cout<<" tmp.clear();"<<endl;
   cout<<""<<endl;
 }

 cout<<" tmp = {"<<endl;
 cout<<"      -6.0, -5.83333333, -5.66666667, -5.5, -5.33333333,"<<endl;
 cout<<"      -5.16666667, -5.0, -4.83333333, -4.66666667, -4.5,"<<endl;
 cout<<"      -4.33333333, -4.16666667, -4.0, -3.83333333,"<<endl;
 cout<<"      -3.66666667, -3.5, -3.33333333, -3.16666667, -3.0,"<<endl;
 cout<<"      -2.83333333, -2.66666667, -2.5, -2.33333333,"<<endl;
 cout<<"      -2.16666667, -2.0, -1.83333333, -1.66666667, -1.5,"<<endl;
 cout<<"      -1.33333333, -1.16666667, -1.0, -0.83333333, -0.66666667,"<<endl;
 cout<<"      -0.5, -0.33333333, -0.16666667, 0.0, 0.16666667,"<<endl;
 cout<<"       0.33333333, 0.5, 0.66666667, 0.83333333, 1.0,"<<endl;
 cout<<"       1.16666667, 1.33333333, 1.5, 1.66666667, 1.83333333,"<<endl;
 cout<<"       2.0, 2.16666667, 2.33333333, 2.5, 2.66666667,"<<endl;
 cout<<"       2.83333333, 3.0, 3.16666667, 3.33333333, 3.5,"<<endl;
 cout<<"       3.66666667, 3.83333333, 4.0, 4.16666667, 4.33333333,"<<endl;
 cout<<"       4.5, 4.66666667, 4.83333333, 5.0, 5.16666667,"<<endl;
 cout<<"       5.33333333, 5.5, 5.66666667, 5.83333333, 6.0"<<endl;
 cout<<" };"<<endl;
 cout<<""<<endl;
 cout<<" "<<FunctionName<<"_dlaeta.resize(1, neta);"<<endl;
 cout<<" for(int j = 1; j <= neta; j++){"<<endl;
 cout<<"   "<<FunctionName<<"_dlaeta(j) = tmp.at(j - 1);"<<endl;
 cout<<" }"<<endl;
 cout<<" tmp.clear();"<<endl;
 cout<<""<<endl;
 cout<<" tmp = {"<<endl;
 cout<<"      -3.0, -2.83333333, -2.66666667, -2.5, -2.33333333,"<<endl;
 cout<<"      -2.16666667, -2.0, -1.83333333, -1.66666667, -1.5,"<<endl;
 cout<<"      -1.33333333,-1.16666667, -1.0,-0.83333333,-0.66666667,"<<endl;
 cout<<"      -0.5, -0.33333333, -0.16666667, 0.0, 0.16666667,"<<endl;
 cout<<"       0.33333333, 0.5, 0.66666667, 0.83333333, 1.0,"<<endl;
 cout<<"       1.16666667, 1.33333333, 1.5, 1.66666667, 1.83333333,"<<endl;
 cout<<"       2.0, 2.16666667, 2.33333333, 2.5, 2.66666667,"<<endl;
 cout<<"       2.83333333, 3.0, 3.16666667, 3.33333333, 3.5,"<<endl;
 cout<<"       3.66666667, 3.83333333, 4.0, 4.16666667, 4.33333333,"<<endl;
 cout<<"       4.5, 4.66666667, 4.83333333, 5.0"<<endl;
 cout<<" };"<<endl;
 cout<<""<<endl;
 cout<<" "<<FunctionName<<"_dlaxi.resize(1, nxi);"<<endl;
 cout<<" for(int j = 1; j <= nxi; j++){"<<endl;
 cout<<"   "<<FunctionName<<"_dlaxi(j) = tmp.at(j - 1);"<<endl;
 cout<<" }"<<endl;
 cout<<" tmp.clear();"<<endl;
 cout<<""<<endl;
 cout<<"////////////////////////////////////////////////////////////////////////////////////////////"<<endl;

}
