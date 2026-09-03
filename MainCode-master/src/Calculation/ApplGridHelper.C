#define Calculation_ApplGridHelper_cxx
#include "Calculation/ApplGridHelper.h"

#ifdef USE_LHAPDF
LHAPDF::PDF* LHAPDFInstance = 0;
#endif
HoppetInterface* HoppetInstance = 0;
pdsReader* CTEQPDFInstance = 0;
QCDSet* QCDInstance = 0;
pdsReader* ThreadCTEQPDFInstance[200] = {0};
QCDSet* ThreadQCDInstance[200] = {0};
int ApplGridCount = 0;

void evolvepdf_(const double& x, const double& Q, double* xf)
{
 for ( int i = -6 ; i <= 6 ; i++ ){
   xf[i + 6] = LHAPDFInstance->xfxQ(i, x, Q);
 }
}

double alphaspdf_(const double& Q)
{
 return LHAPDFInstance->alphasQ2(Q*Q);
}

void cteqevolvepdf_(const double& x, const double& Q, double* xf)
{
 HoppetInstance->Evolve(x, Q, xf);
}

void cteqevolvepdfpbar_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 HoppetInstance->Evolve(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void cteqevolvepdfcu_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 HoppetInstance->Evolve(x, Q, pdf);
 double neutronpdf[13];

 for ( int i = -6 ; i <= 6 ; i++ ){
   int in;
   if(i == 1) in = 2;
   else if(i == 2) in = 1;
   else if(i == -1) in = -2;
   else if(i == -2) in = -1;
   else in = i;
   neutronpdf[in + 6] = pdf[i + 6];
 }

 for ( int i = -6 ; i <= 6 ; i++ ){
   xf[i + 6] = (29.0 * pdf[i + 6] + 35.0 * neutronpdf[i + 6]) / 64.0;
 }

}

double cteqalphaspdf_(const double& Q)
{
 return HoppetInstance->EvolveAlphaS(Q);
}

void cteqtableevolvepdf_(const double& x, const double& Q, double* xf)
{
   xf[0  + 6] = CTEQPDFInstance->xfxQ(0, x, Q);//gluon
   if(Q > QCDInstance->Amhat(6)) xf[-6 + 6] = CTEQPDFInstance->xfxQ(-6, x, Q);//tbar
   if(Q > QCDInstance->Amhat(5)) xf[-5 + 6] = CTEQPDFInstance->xfxQ(-5, x, Q);//bbar
   if(Q > QCDInstance->Amhat(4)) xf[-4 + 6] = CTEQPDFInstance->xfxQ(-4, x, Q);//cbar
   xf[-3 + 6] = CTEQPDFInstance->xfxQ(-3, x, Q);//sbar
   xf[-2 + 6] = CTEQPDFInstance->xfxQ(-2, x, Q);//ubar
   xf[-1 + 6] = CTEQPDFInstance->xfxQ(-1, x, Q);//dbar
   xf[1  + 6] = CTEQPDFInstance->xfxQ(1, x, Q);//d
   xf[2  + 6] = CTEQPDFInstance->xfxQ(2, x, Q);//u
   xf[3  + 6] = CTEQPDFInstance->xfxQ(3, x, Q);//s
   if(Q > QCDInstance->Amhat(4)) xf[4  + 6] = CTEQPDFInstance->xfxQ(4, x, Q);//c
   if(Q > QCDInstance->Amhat(5)) xf[5  + 6] = CTEQPDFInstance->xfxQ(5, x, Q);//b
   if(Q > QCDInstance->Amhat(6)) xf[6  + 6] = CTEQPDFInstance->xfxQ(6, x, Q);//t
}

void cteqtableevolvepdfpbar_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
   pdf[0  + 6] = CTEQPDFInstance->xfxQ(0, x, Q);//gluon
   if(Q > QCDInstance->Amhat(6)) pdf[-6 + 6] = CTEQPDFInstance->xfxQ(-6, x, Q);//tbar
   if(Q > QCDInstance->Amhat(5)) pdf[-5 + 6] = CTEQPDFInstance->xfxQ(-5, x, Q);//bbar
   if(Q > QCDInstance->Amhat(4)) pdf[-4 + 6] = CTEQPDFInstance->xfxQ(-4, x, Q);//cbar
   pdf[-3 + 6] = CTEQPDFInstance->xfxQ(-3, x, Q);//sbar
   pdf[-2 + 6] = CTEQPDFInstance->xfxQ(-2, x, Q);//ubar
   pdf[-1 + 6] = CTEQPDFInstance->xfxQ(-1, x, Q);//dbar
   pdf[1  + 6] = CTEQPDFInstance->xfxQ(1, x, Q);//d
   pdf[2  + 6] = CTEQPDFInstance->xfxQ(2, x, Q);//u
   pdf[3  + 6] = CTEQPDFInstance->xfxQ(3, x, Q);//s
   if(Q > QCDInstance->Amhat(4)) pdf[4  + 6] = CTEQPDFInstance->xfxQ(4, x, Q);//c
   if(Q > QCDInstance->Amhat(5)) pdf[5  + 6] = CTEQPDFInstance->xfxQ(5, x, Q);//b
   if(Q > QCDInstance->Amhat(6)) pdf[6  + 6] = CTEQPDFInstance->xfxQ(6, x, Q);//t

 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void cteqtableevolvepdfcu_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
   pdf[0  + 6] = CTEQPDFInstance->xfxQ(0, x, Q);//gluon
   if(Q > QCDInstance->Amhat(6)) pdf[-6 + 6] = CTEQPDFInstance->xfxQ(-6, x, Q);//tbar
   if(Q > QCDInstance->Amhat(5)) pdf[-5 + 6] = CTEQPDFInstance->xfxQ(-5, x, Q);//bbar
   if(Q > QCDInstance->Amhat(4)) pdf[-4 + 6] = CTEQPDFInstance->xfxQ(-4, x, Q);//cbar
   pdf[-3 + 6] = CTEQPDFInstance->xfxQ(-3, x, Q);//sbar
   pdf[-2 + 6] = CTEQPDFInstance->xfxQ(-2, x, Q);//ubar
   pdf[-1 + 6] = CTEQPDFInstance->xfxQ(-1, x, Q);//dbar
   pdf[1  + 6] = CTEQPDFInstance->xfxQ(1, x, Q);//d
   pdf[2  + 6] = CTEQPDFInstance->xfxQ(2, x, Q);//u
   pdf[3  + 6] = CTEQPDFInstance->xfxQ(3, x, Q);//s
   if(Q > QCDInstance->Amhat(4)) pdf[4  + 6] = CTEQPDFInstance->xfxQ(4, x, Q);//c
   if(Q > QCDInstance->Amhat(5)) pdf[5  + 6] = CTEQPDFInstance->xfxQ(5, x, Q);//b
   if(Q > QCDInstance->Amhat(6)) pdf[6  + 6] = CTEQPDFInstance->xfxQ(6, x, Q);//t

 double neutronpdf[13];

 for ( int i = -6 ; i <= 6 ; i++ ){
   int in;
   if(i == 1) in = 2;
   else if(i == 2) in = 1;
   else if(i == -1) in = -2;
   else if(i == -2) in = -1;
   else in = i;
   neutronpdf[in + 6] = pdf[i + 6];
 }

 for ( int i = -6 ; i <= 6 ; i++ ){
   xf[i + 6] = (29.0 * pdf[i + 6] + 35.0 * neutronpdf[i + 6]) / 64.0;
 }

}

double cteqtablealphaspdf_(const double& Q)
{
 return CTEQPDFInstance->CT14Alphas(Q);
}

/////////////////////////////////////////////////////////////////////////////

void threadpdf1_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[1]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[1]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[1]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf2_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[2]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[2]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[2]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf3_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[3]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[3]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[3]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf4_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[4]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[4]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[4]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf5_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[5]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[5]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[5]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf6_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[6]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[6]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[6]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf7_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[7]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[7]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[7]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf8_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[8]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[8]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[8]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf9_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[9]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[9]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[9]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf10_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[10]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[10]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[10]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf11_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[11]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[11]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[11]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf12_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[12]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[12]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[12]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf13_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[13]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[13]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[13]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf14_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[14]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[14]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[14]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf15_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[15]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[15]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[15]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf16_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[16]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[16]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[16]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf17_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[17]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[17]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[17]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf18_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[18]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[18]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[18]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf19_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[19]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[19]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[19]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf20_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[20]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[20]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[20]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf21_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[21]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[21]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[21]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf22_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[22]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[22]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[22]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf23_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[23]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[23]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[23]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf24_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[24]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[24]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[24]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf25_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[25]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[25]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[25]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf26_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[26]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[26]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[26]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf27_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[27]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[27]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[27]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf28_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[28]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[28]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[28]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf29_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[29]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[29]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[29]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf30_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[30]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[30]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[30]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf31_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[31]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[31]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[31]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf32_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[32]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[32]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[32]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf33_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[33]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[33]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[33]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf34_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[34]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[34]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[34]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf35_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[35]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[35]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[35]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf36_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[36]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[36]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[36]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf37_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[37]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[37]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[37]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf38_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[38]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[38]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[38]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf39_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[39]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[39]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[39]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf40_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[40]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[40]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[40]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf41_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[41]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[41]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[41]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf42_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[42]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[42]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[42]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf43_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[43]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[43]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[43]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf44_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[44]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[44]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[44]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf45_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[45]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[45]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[45]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf46_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[46]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[46]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[46]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf47_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[47]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[47]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[47]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf48_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[48]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[48]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[48]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf49_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[49]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[49]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[49]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf50_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[50]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[50]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[50]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf51_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[51]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[51]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[51]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf52_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[52]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[52]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[52]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf53_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[53]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[53]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[53]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf54_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[54]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[54]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[54]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf55_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[55]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[55]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[55]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf56_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[56]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[56]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[56]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf57_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[57]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[57]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[57]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf58_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[58]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[58]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[58]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf59_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[59]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[59]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[59]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf60_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[60]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[60]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[60]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf61_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[61]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[61]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[61]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf62_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[62]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[62]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[62]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf63_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[63]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[63]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[63]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf64_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[64]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[64]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[64]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf65_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[65]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[65]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[65]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf66_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[66]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[66]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[66]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf67_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[67]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[67]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[67]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf68_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[68]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[68]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[68]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf69_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[69]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[69]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[69]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf70_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[70]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[70]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[70]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf71_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[71]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[71]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[71]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf72_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[72]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[72]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[72]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf73_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[73]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[73]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[73]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf74_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[74]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[74]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[74]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf75_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[75]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[75]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[75]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf76_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[76]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[76]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[76]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf77_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[77]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[77]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[77]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf78_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[78]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[78]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[78]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf79_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[79]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[79]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[79]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf80_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[80]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[80]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[80]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf81_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[81]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[81]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[81]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf82_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[82]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[82]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[82]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf83_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[83]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[83]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[83]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf84_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[84]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[84]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[84]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf85_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[85]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[85]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[85]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf86_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[86]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[86]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[86]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf87_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[87]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[87]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[87]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf88_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[88]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[88]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[88]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf89_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[89]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[89]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[89]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf90_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[90]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[90]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[90]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf91_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[91]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[91]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[91]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf92_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[92]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[92]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[92]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf93_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[93]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[93]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[93]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf94_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[94]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[94]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[94]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf95_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[95]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[95]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[95]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf96_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[96]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[96]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[96]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf97_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[97]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[97]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[97]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf98_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[98]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[98]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[98]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf99_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[99]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[99]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[99]->xfxQ(i, x, Q);
     }
   }
}

void threadpdf100_(const double& x, const double& Q, double* xf)
{
   for(int i = -6; i <= 6; i++){
     if(abs(i) >= 4){
       if(Q > ThreadQCDInstance[100]->Amhat(abs(i))) xf[i + 6] = ThreadCTEQPDFInstance[100]->xfxQ(i, x, Q);
     }
     else{
       xf[i + 6] = ThreadCTEQPDFInstance[100]->xfxQ(i, x, Q);
     }
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void threadpdfpbar1_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf1_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar2_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf2_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar3_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf3_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar4_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf4_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar5_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf5_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar6_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf6_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar7_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf7_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar8_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf8_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar9_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf9_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar10_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf10_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar11_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf11_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar12_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf12_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar13_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf13_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar14_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf14_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar15_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf15_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar16_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf16_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar17_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf17_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar18_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf18_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar19_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf19_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar20_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf20_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar21_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf21_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar22_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf22_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar23_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf23_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar24_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf24_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar25_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf25_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar26_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf26_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar27_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf27_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar28_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf28_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar29_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf29_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar30_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf30_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar31_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf31_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar32_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf32_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar33_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf33_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar34_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf34_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar35_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf35_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar36_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf36_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar37_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf37_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar38_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf38_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar39_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf39_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar40_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf40_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar41_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf41_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar42_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf42_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar43_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf43_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar44_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf44_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar45_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf45_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar46_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf46_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar47_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf47_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar48_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf48_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar49_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf49_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar50_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf50_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar51_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf51_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar52_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf52_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar53_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf53_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar54_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf54_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar55_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf55_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar56_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf56_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar57_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf57_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar58_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf58_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar59_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf59_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar60_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf60_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar61_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf61_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar62_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf62_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar63_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf63_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar64_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf64_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar65_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf65_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar66_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf66_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar67_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf67_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar68_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf68_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar69_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf69_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar70_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf70_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar71_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf71_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar72_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf72_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar73_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf73_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar74_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf74_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar75_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf75_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar76_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf76_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar77_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf77_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar78_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf78_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar79_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf79_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar80_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf80_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar81_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf81_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar82_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf82_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar83_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf83_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar84_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf84_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar85_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf85_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar86_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf86_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar87_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf87_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar88_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf88_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar89_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf89_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar90_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf90_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar91_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf91_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar92_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf92_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar93_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf93_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar94_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf94_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar95_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf95_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar96_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf96_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar97_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf97_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar98_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf98_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar99_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf99_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

void threadpdfpbar100_(const double& x, const double& Q, double* xf)
{
 double pdf[13];
 threadpdf100_(x, Q, pdf);
 for ( int i = 0 ; i < 13 ; i++ ) xf[i] = pdf[12 - i];
}

///////////////////////////////////////////////////////////////////////////////////////

double threadalphas1_(const double& Q)
{
 return ThreadCTEQPDFInstance[1]->CT14Alphas(Q);
}

double threadalphas2_(const double& Q)
{
 return ThreadCTEQPDFInstance[2]->CT14Alphas(Q);
}

double threadalphas3_(const double& Q)
{
 return ThreadCTEQPDFInstance[3]->CT14Alphas(Q);
}

double threadalphas4_(const double& Q)
{
 return ThreadCTEQPDFInstance[4]->CT14Alphas(Q);
}

double threadalphas5_(const double& Q)
{
 return ThreadCTEQPDFInstance[5]->CT14Alphas(Q);
}

double threadalphas6_(const double& Q)
{
 return ThreadCTEQPDFInstance[6]->CT14Alphas(Q);
}

double threadalphas7_(const double& Q)
{
 return ThreadCTEQPDFInstance[7]->CT14Alphas(Q);
}

double threadalphas8_(const double& Q)
{
 return ThreadCTEQPDFInstance[8]->CT14Alphas(Q);
}

double threadalphas9_(const double& Q)
{
 return ThreadCTEQPDFInstance[9]->CT14Alphas(Q);
}

double threadalphas10_(const double& Q)
{
 return ThreadCTEQPDFInstance[10]->CT14Alphas(Q);
}

double threadalphas11_(const double& Q)
{
 return ThreadCTEQPDFInstance[11]->CT14Alphas(Q);
}

double threadalphas12_(const double& Q)
{
 return ThreadCTEQPDFInstance[12]->CT14Alphas(Q);
}

double threadalphas13_(const double& Q)
{
 return ThreadCTEQPDFInstance[13]->CT14Alphas(Q);
}

double threadalphas14_(const double& Q)
{
 return ThreadCTEQPDFInstance[14]->CT14Alphas(Q);
}

double threadalphas15_(const double& Q)
{
 return ThreadCTEQPDFInstance[15]->CT14Alphas(Q);
}

double threadalphas16_(const double& Q)
{
 return ThreadCTEQPDFInstance[16]->CT14Alphas(Q);
}

double threadalphas17_(const double& Q)
{
 return ThreadCTEQPDFInstance[17]->CT14Alphas(Q);
}

double threadalphas18_(const double& Q)
{
 return ThreadCTEQPDFInstance[18]->CT14Alphas(Q);
}

double threadalphas19_(const double& Q)
{
 return ThreadCTEQPDFInstance[19]->CT14Alphas(Q);
}

double threadalphas20_(const double& Q)
{
 return ThreadCTEQPDFInstance[20]->CT14Alphas(Q);
}

double threadalphas21_(const double& Q)
{
 return ThreadCTEQPDFInstance[21]->CT14Alphas(Q);
}

double threadalphas22_(const double& Q)
{
 return ThreadCTEQPDFInstance[22]->CT14Alphas(Q);
}

double threadalphas23_(const double& Q)
{
 return ThreadCTEQPDFInstance[23]->CT14Alphas(Q);
}

double threadalphas24_(const double& Q)
{
 return ThreadCTEQPDFInstance[24]->CT14Alphas(Q);
}

double threadalphas25_(const double& Q)
{
 return ThreadCTEQPDFInstance[25]->CT14Alphas(Q);
}

double threadalphas26_(const double& Q)
{
 return ThreadCTEQPDFInstance[26]->CT14Alphas(Q);
}

double threadalphas27_(const double& Q)
{
 return ThreadCTEQPDFInstance[27]->CT14Alphas(Q);
}

double threadalphas28_(const double& Q)
{
 return ThreadCTEQPDFInstance[28]->CT14Alphas(Q);
}

double threadalphas29_(const double& Q)
{
 return ThreadCTEQPDFInstance[29]->CT14Alphas(Q);
}

double threadalphas30_(const double& Q)
{
 return ThreadCTEQPDFInstance[30]->CT14Alphas(Q);
}

double threadalphas31_(const double& Q)
{
 return ThreadCTEQPDFInstance[31]->CT14Alphas(Q);
}

double threadalphas32_(const double& Q)
{
 return ThreadCTEQPDFInstance[32]->CT14Alphas(Q);
}

double threadalphas33_(const double& Q)
{
 return ThreadCTEQPDFInstance[33]->CT14Alphas(Q);
}

double threadalphas34_(const double& Q)
{
 return ThreadCTEQPDFInstance[34]->CT14Alphas(Q);
}

double threadalphas35_(const double& Q)
{
 return ThreadCTEQPDFInstance[35]->CT14Alphas(Q);
}

double threadalphas36_(const double& Q)
{
 return ThreadCTEQPDFInstance[36]->CT14Alphas(Q);
}

double threadalphas37_(const double& Q)
{
 return ThreadCTEQPDFInstance[37]->CT14Alphas(Q);
}

double threadalphas38_(const double& Q)
{
 return ThreadCTEQPDFInstance[38]->CT14Alphas(Q);
}

double threadalphas39_(const double& Q)
{
 return ThreadCTEQPDFInstance[39]->CT14Alphas(Q);
}

double threadalphas40_(const double& Q)
{
 return ThreadCTEQPDFInstance[40]->CT14Alphas(Q);
}

double threadalphas41_(const double& Q)
{
 return ThreadCTEQPDFInstance[41]->CT14Alphas(Q);
}

double threadalphas42_(const double& Q)
{
 return ThreadCTEQPDFInstance[42]->CT14Alphas(Q);
}

double threadalphas43_(const double& Q)
{
 return ThreadCTEQPDFInstance[43]->CT14Alphas(Q);
}

double threadalphas44_(const double& Q)
{
 return ThreadCTEQPDFInstance[44]->CT14Alphas(Q);
}

double threadalphas45_(const double& Q)
{
 return ThreadCTEQPDFInstance[45]->CT14Alphas(Q);
}

double threadalphas46_(const double& Q)
{
 return ThreadCTEQPDFInstance[46]->CT14Alphas(Q);
}

double threadalphas47_(const double& Q)
{
 return ThreadCTEQPDFInstance[47]->CT14Alphas(Q);
}

double threadalphas48_(const double& Q)
{
 return ThreadCTEQPDFInstance[48]->CT14Alphas(Q);
}

double threadalphas49_(const double& Q)
{
 return ThreadCTEQPDFInstance[49]->CT14Alphas(Q);
}

double threadalphas50_(const double& Q)
{
 return ThreadCTEQPDFInstance[50]->CT14Alphas(Q);
}

double threadalphas51_(const double& Q)
{
 return ThreadCTEQPDFInstance[51]->CT14Alphas(Q);
}

double threadalphas52_(const double& Q)
{
 return ThreadCTEQPDFInstance[52]->CT14Alphas(Q);
}

double threadalphas53_(const double& Q)
{
 return ThreadCTEQPDFInstance[53]->CT14Alphas(Q);
}

double threadalphas54_(const double& Q)
{
 return ThreadCTEQPDFInstance[54]->CT14Alphas(Q);
}

double threadalphas55_(const double& Q)
{
 return ThreadCTEQPDFInstance[55]->CT14Alphas(Q);
}

double threadalphas56_(const double& Q)
{
 return ThreadCTEQPDFInstance[56]->CT14Alphas(Q);
}

double threadalphas57_(const double& Q)
{
 return ThreadCTEQPDFInstance[57]->CT14Alphas(Q);
}

double threadalphas58_(const double& Q)
{
 return ThreadCTEQPDFInstance[58]->CT14Alphas(Q);
}

double threadalphas59_(const double& Q)
{
 return ThreadCTEQPDFInstance[59]->CT14Alphas(Q);
}

double threadalphas60_(const double& Q)
{
 return ThreadCTEQPDFInstance[60]->CT14Alphas(Q);
}

double threadalphas61_(const double& Q)
{
 return ThreadCTEQPDFInstance[61]->CT14Alphas(Q);
}

double threadalphas62_(const double& Q)
{
 return ThreadCTEQPDFInstance[62]->CT14Alphas(Q);
}

double threadalphas63_(const double& Q)
{
 return ThreadCTEQPDFInstance[63]->CT14Alphas(Q);
}

double threadalphas64_(const double& Q)
{
 return ThreadCTEQPDFInstance[64]->CT14Alphas(Q);
}

double threadalphas65_(const double& Q)
{
 return ThreadCTEQPDFInstance[65]->CT14Alphas(Q);
}

double threadalphas66_(const double& Q)
{
 return ThreadCTEQPDFInstance[66]->CT14Alphas(Q);
}

double threadalphas67_(const double& Q)
{
 return ThreadCTEQPDFInstance[67]->CT14Alphas(Q);
}

double threadalphas68_(const double& Q)
{
 return ThreadCTEQPDFInstance[68]->CT14Alphas(Q);
}

double threadalphas69_(const double& Q)
{
 return ThreadCTEQPDFInstance[69]->CT14Alphas(Q);
}

double threadalphas70_(const double& Q)
{
 return ThreadCTEQPDFInstance[70]->CT14Alphas(Q);
}

double threadalphas71_(const double& Q)
{
 return ThreadCTEQPDFInstance[71]->CT14Alphas(Q);
}

double threadalphas72_(const double& Q)
{
 return ThreadCTEQPDFInstance[72]->CT14Alphas(Q);
}

double threadalphas73_(const double& Q)
{
 return ThreadCTEQPDFInstance[73]->CT14Alphas(Q);
}

double threadalphas74_(const double& Q)
{
 return ThreadCTEQPDFInstance[74]->CT14Alphas(Q);
}

double threadalphas75_(const double& Q)
{
 return ThreadCTEQPDFInstance[75]->CT14Alphas(Q);
}

double threadalphas76_(const double& Q)
{
 return ThreadCTEQPDFInstance[76]->CT14Alphas(Q);
}

double threadalphas77_(const double& Q)
{
 return ThreadCTEQPDFInstance[77]->CT14Alphas(Q);
}

double threadalphas78_(const double& Q)
{
 return ThreadCTEQPDFInstance[78]->CT14Alphas(Q);
}

double threadalphas79_(const double& Q)
{
 return ThreadCTEQPDFInstance[79]->CT14Alphas(Q);
}

double threadalphas80_(const double& Q)
{
 return ThreadCTEQPDFInstance[80]->CT14Alphas(Q);
}

double threadalphas81_(const double& Q)
{
 return ThreadCTEQPDFInstance[81]->CT14Alphas(Q);
}

double threadalphas82_(const double& Q)
{
 return ThreadCTEQPDFInstance[82]->CT14Alphas(Q);
}

double threadalphas83_(const double& Q)
{
 return ThreadCTEQPDFInstance[83]->CT14Alphas(Q);
}

double threadalphas84_(const double& Q)
{
 return ThreadCTEQPDFInstance[84]->CT14Alphas(Q);
}

double threadalphas85_(const double& Q)
{
 return ThreadCTEQPDFInstance[85]->CT14Alphas(Q);
}

double threadalphas86_(const double& Q)
{
 return ThreadCTEQPDFInstance[86]->CT14Alphas(Q);
}

double threadalphas87_(const double& Q)
{
 return ThreadCTEQPDFInstance[87]->CT14Alphas(Q);
}

double threadalphas88_(const double& Q)
{
 return ThreadCTEQPDFInstance[88]->CT14Alphas(Q);
}

double threadalphas89_(const double& Q)
{
 return ThreadCTEQPDFInstance[89]->CT14Alphas(Q);
}

double threadalphas90_(const double& Q)
{
 return ThreadCTEQPDFInstance[90]->CT14Alphas(Q);
}

double threadalphas91_(const double& Q)
{
 return ThreadCTEQPDFInstance[91]->CT14Alphas(Q);
}

double threadalphas92_(const double& Q)
{
 return ThreadCTEQPDFInstance[92]->CT14Alphas(Q);
}

double threadalphas93_(const double& Q)
{
 return ThreadCTEQPDFInstance[93]->CT14Alphas(Q);
}

double threadalphas94_(const double& Q)
{
 return ThreadCTEQPDFInstance[94]->CT14Alphas(Q);
}

double threadalphas95_(const double& Q)
{
 return ThreadCTEQPDFInstance[95]->CT14Alphas(Q);
}

double threadalphas96_(const double& Q)
{
 return ThreadCTEQPDFInstance[96]->CT14Alphas(Q);
}

double threadalphas97_(const double& Q)
{
 return ThreadCTEQPDFInstance[97]->CT14Alphas(Q);
}

double threadalphas98_(const double& Q)
{
 return ThreadCTEQPDFInstance[98]->CT14Alphas(Q);
}

double threadalphas99_(const double& Q)
{
 return ThreadCTEQPDFInstance[99]->CT14Alphas(Q);
}

double threadalphas100_(const double& Q)
{
 return ThreadCTEQPDFInstance[100]->CT14Alphas(Q);
}


/////////////////////////////////////////////////////////////////////////////

ApplGridHelper::ApplGridHelper()
{
 InitialSubProcName();

}

void ApplGridHelper::InitialPDF(TString PDFName, int iSet)
{
#ifdef USE_LHAPDF
 //LHAPDF::initPDFSet(PDFName.Data(), iSet);
 LHAPDFInstance = LHAPDF::mkPDF(PDFName.Data(), iSet);
#endif

 m_qcd = new QCDSet();
 m_qcd->SetNfTotal(NfTotal);
 m_qcd->SetPoleMasscbt(PoleMass(4), PoleMass(5), PoleMass(6));
 m_qcd->SetAmhatf();
 QCDInstance = m_qcd;

 this->PDFName = PDFName;
 this->iSet = iSet;

 PDFType = PDFTypeEnum::CT_LHAPDF;
}

void ApplGridHelper::InitialPDFbyHand(HoppetInterface* h)
{
 HoppetInstance = h;

 PDFType = PDFTypeEnum::CT_CTEQ;
}

void ApplGridHelper::InitialCTEQPDF(pdsReader* pdf)
{
 if(ThreadCTEQPDFInstance[iThread]) delete ThreadCTEQPDFInstance[iThread];

 ThreadCTEQPDFInstance[iThread] = new pdsReader();
 ThreadCTEQPDFInstance[iThread]->CopyHeader(pdf);
 ThreadCTEQPDFInstance[iThread]->InputAlphaS(pdf->AlsCTEQ);
 ThreadCTEQPDFInstance[iThread]->InputUPD(pdf->UPD);

 if(ThreadQCDInstance[iThread]) delete ThreadQCDInstance[iThread];

 ThreadQCDInstance[iThread] = new QCDSet();
 ThreadQCDInstance[iThread]->SetNfTotal(NfTotal);
 ThreadQCDInstance[iThread]->SetPoleMasscbt(PoleMass(4), PoleMass(5), PoleMass(6));
 ThreadQCDInstance[iThread]->SetAmhatf();

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

void ApplGridHelper::InitialCTEQPDF(TString PDFFile)
{
 CTEQPDFInstance = new pdsReader();
 CTEQPDFInstance->Initialize(PDFFile);

 m_qcd = new QCDSet();
 m_qcd->SetNfTotal(NfTotal);
 m_qcd->SetPoleMasscbt(PoleMass(4), PoleMass(5), PoleMass(6));
 m_qcd->SetAmhatf();
 QCDInstance = m_qcd;

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

void ApplGridHelper::DefaultConvolute(TString GridName)
{
#ifdef USE_APPLGRID
 appl::grid g((std::string)(GridName.Data()));

 g.trim();

 std::cout << g.getDocumentation() << std::endl;

 //std::vector<double>  xsec = g.vconvolute( evolvepdf_, alphaspdf_, order);
 g.setckm(ckm);

 TH1D* h1;

 if(PDFType == PDFTypeEnum::CT_LHAPDF) h1 = g.convolute( evolvepdf_, alphaspdf_, order);

 if(PDFType == PDFTypeEnum::CT_CTEQ) h1 = g.convolute( cteqevolvepdf_, cteqalphaspdf_, order);

 if(PDFType == PDFTypeEnum::CT_CTEQTable) h1 = g.convolute( cteqtableevolvepdf_, cteqtablealphaspdf_, order);

 //for ( int i=0 ; i<xsec.size() ; i++ ) std::cout << "xsec[" << i << "]\t= " << xsec[i] << std::endl;

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double left = h1->GetXaxis()->GetBinLowEdge(ibin);
   double right = h1->GetXaxis()->GetBinUpEdge(ibin);
   std::cout << "[" << left << ", " << right <<"]: "<<"xsec[" << ibin << "] = "<< h1->GetBinContent(ibin) << "  error = " << h1->GetBinError(ibin) << std::endl;
 }

#endif
}

void ApplGridHelper::DefaultConvoluteppbar(TString GridName)
{
#ifdef USE_APPLGRID
 appl::grid g((std::string)(GridName.Data()));

 g.trim();

 std::cout << g.getDocumentation() << std::endl;

 g.setckm(ckm);

 TH1D* h1;
 if(PDFType == PDFTypeEnum::CT_LHAPDF){
   _pdf = evolvepdf_;
   h1 = g.convolute( evolvepdf_, evolvepdfpbar_, alphaspdf_, order);
 }

 if(PDFType == PDFTypeEnum::CT_CTEQ){
   h1 = g.convolute( cteqevolvepdf_, cteqevolvepdfpbar_, cteqalphaspdf_, order);
 }

 if(PDFType == PDFTypeEnum::CT_CTEQTable){
   h1 = g.convolute( cteqtableevolvepdf_, cteqtableevolvepdfpbar_, cteqtablealphaspdf_, order);
 }

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double left = h1->GetXaxis()->GetBinLowEdge(ibin);
   double right = h1->GetXaxis()->GetBinUpEdge(ibin);
   std::cout << "[" << left << ", " << right <<"]: "<<"xsec[" << ibin << "] = "<< h1->GetBinContent(ibin) << "  error = " << h1->GetBinError(ibin) << std::endl;
 }

#endif
}

void ApplGridHelper::DefaultConvolutepCu(TString GridName)
{
#ifdef USE_APPLGRID
 appl::grid g((std::string)(GridName.Data()));

 g.trim();

 std::cout << g.getDocumentation() << std::endl;

 g.setckm(ckm);

 TH1D* h1;
 if(PDFType == PDFTypeEnum::CT_LHAPDF){
   _pdf = evolvepdf_;
   h1 = g.convolute( evolvepdf_, evolvepdfcu_, alphaspdf_, order);
 }

 if(PDFType == PDFTypeEnum::CT_CTEQ){
   h1 = g.convolute( cteqevolvepdf_, cteqevolvepdfcu_, cteqalphaspdf_, order);
 }

 if(PDFType == PDFTypeEnum::CT_CTEQTable){
   h1 = g.convolute( cteqtableevolvepdf_, cteqtableevolvepdfcu_, cteqtablealphaspdf_, order);
 }


 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double left = h1->GetXaxis()->GetBinLowEdge(ibin);
   double right = h1->GetXaxis()->GetBinUpEdge(ibin);
   std::cout << "[" << left << ", " << right <<"]: "<<"xsec[" << ibin << "] = "<< h1->GetBinContent(ibin) << "  error = " << h1->GetBinError(ibin) << std::endl;
 }

#endif
}

void ApplGridHelper::InitialGrid(TString GridName)
{
#ifdef USE_APPLGRID
 ApplGridMap[GridName] = new appl::grid((std::string)(GridName.Data()));

 ApplGridMap[GridName]->trim();
 ApplGridMap[GridName]->setckm(ckm);

 isInitial[GridName] = true;

 SavedGridName = GridName;

 ApplGridCount++;

 if(ApplGridCount >= 100){
   cout<<"WARNING! Additional threadpdf and threadalphas function should be defined for multiple-thread run."<<endl;
 }

 this->iThread = ApplGridCount;
#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void ApplGridHelper::InitialHistName(TString name)
{
 TheoryResultName = name;
}

void ApplGridHelper::DefaultConvoluteMacro(TString GridName, vector<double> &result)
{
#ifdef USE_APPLGRID
 vector<double> xsec;

 if(PDFType == PDFTypeEnum::CT_LHAPDF) xsec = ApplGridMap[GridName]->vconvolute( evolvepdf_, alphaspdf_, order);

 if(PDFType == PDFTypeEnum::CT_CTEQ) xsec = ApplGridMap[GridName]->vconvolute( cteqevolvepdf_, cteqalphaspdf_, order);

 if(PDFType == PDFTypeEnum::CT_CTEQTable) xsec = ApplGridMap[GridName]->vconvolute( cteqtableevolvepdf_, cteqtablealphaspdf_, order);

 for(int i = 0; i < xsec.size(); i++){
   if(isSetCut){
     double BinLeft = ApplGridMap[GridName]->obslow_internal(i);
     double BinRight = ApplGridMap[GridName]->obslow_internal(i) + ApplGridMap[GridName]->deltaobs_internal(i);
     bool RemovePoint = (BinLeft < BinLeftCut) || (BinRight > BinRightCut);
     if(RemovePoint) continue;
   }

   result.push_back(xsec.at(i) / 1000.0);
 }
#endif
}

void ApplGridHelper::DefaultConvoluteppbarMacro(TString GridName, vector<double> &result)
{
#ifdef USE_APPLGRID
 vector<double> xsec;

 if(PDFType == PDFTypeEnum::CT_LHAPDF) xsec = ApplGridMap[GridName]->vconvolute( evolvepdf_, evolvepdfpbar_, alphaspdf_, order);

 if(PDFType == PDFTypeEnum::CT_CTEQ) xsec = ApplGridMap[GridName]->vconvolute( cteqevolvepdf_, cteqevolvepdfpbar_, cteqalphaspdf_, order);

 if(PDFType == PDFTypeEnum::CT_CTEQTable) xsec = ApplGridMap[GridName]->vconvolute( cteqtableevolvepdf_, cteqtableevolvepdfpbar_, cteqtablealphaspdf_, order);

 for(int i = 0; i < xsec.size(); i++){
   double BinLeft = ApplGridMap[GridName]->obslow_internal(i);
   double BinRight = ApplGridMap[GridName]->obslow_internal(i) + ApplGridMap[GridName]->deltaobs_internal(i);
   bool RemovePoint = (BinLeft < BinLeftCut) || (BinRight > BinRightCut);
   if(RemovePoint) continue;
   result.push_back(xsec.at(i) / 1000.0);
 }
#endif
}

void ApplGridHelper::ThreadConvoluteMacro()
{
#ifdef USE_APPLGRID
 if(PDFType == PDFTypeEnum::CT_LHAPDF){
   cout<<"Multiple thread only works for CTEQ PDF."<<endl;
   return;
 }

 TString GridName = SavedGridName;

 appl_xsec.clear();

 vector<double> xsec;
 if(iThread == 1) xsec = ApplGridMap[GridName]->vconvolute( threadpdf1_, threadalphas1_, order);
 else if(iThread == 2) xsec = ApplGridMap[GridName]->vconvolute( threadpdf2_, threadalphas2_, order);
 else if(iThread == 3) xsec = ApplGridMap[GridName]->vconvolute( threadpdf3_, threadalphas3_, order);
 else if(iThread == 4) xsec = ApplGridMap[GridName]->vconvolute( threadpdf4_, threadalphas4_, order);
 else if(iThread == 5) xsec = ApplGridMap[GridName]->vconvolute( threadpdf5_, threadalphas5_, order);
 else if(iThread == 6) xsec = ApplGridMap[GridName]->vconvolute( threadpdf6_, threadalphas6_, order);
 else if(iThread == 7) xsec = ApplGridMap[GridName]->vconvolute( threadpdf7_, threadalphas7_, order);
 else if(iThread == 8) xsec = ApplGridMap[GridName]->vconvolute( threadpdf8_, threadalphas8_, order);
 else if(iThread == 9) xsec = ApplGridMap[GridName]->vconvolute( threadpdf9_, threadalphas9_, order);
 else if(iThread == 10) xsec = ApplGridMap[GridName]->vconvolute( threadpdf10_, threadalphas10_, order);
 else if(iThread == 11) xsec = ApplGridMap[GridName]->vconvolute( threadpdf11_, threadalphas11_, order);
 else if(iThread == 12) xsec = ApplGridMap[GridName]->vconvolute( threadpdf12_, threadalphas12_, order);
 else if(iThread == 13) xsec = ApplGridMap[GridName]->vconvolute( threadpdf13_, threadalphas13_, order);
 else if(iThread == 14) xsec = ApplGridMap[GridName]->vconvolute( threadpdf14_, threadalphas14_, order);
 else if(iThread == 15) xsec = ApplGridMap[GridName]->vconvolute( threadpdf15_, threadalphas15_, order);
 else if(iThread == 16) xsec = ApplGridMap[GridName]->vconvolute( threadpdf16_, threadalphas16_, order);
 else if(iThread == 17) xsec = ApplGridMap[GridName]->vconvolute( threadpdf17_, threadalphas17_, order);
 else if(iThread == 18) xsec = ApplGridMap[GridName]->vconvolute( threadpdf18_, threadalphas18_, order);
 else if(iThread == 19) xsec = ApplGridMap[GridName]->vconvolute( threadpdf19_, threadalphas19_, order);
 else if(iThread == 20) xsec = ApplGridMap[GridName]->vconvolute( threadpdf20_, threadalphas20_, order);
 else if(iThread == 21) xsec = ApplGridMap[GridName]->vconvolute( threadpdf21_, threadalphas21_, order);
 else if(iThread == 22) xsec = ApplGridMap[GridName]->vconvolute( threadpdf22_, threadalphas22_, order);
 else if(iThread == 23) xsec = ApplGridMap[GridName]->vconvolute( threadpdf23_, threadalphas23_, order);
 else if(iThread == 24) xsec = ApplGridMap[GridName]->vconvolute( threadpdf24_, threadalphas24_, order);
 else if(iThread == 25) xsec = ApplGridMap[GridName]->vconvolute( threadpdf25_, threadalphas25_, order);
 else if(iThread == 26) xsec = ApplGridMap[GridName]->vconvolute( threadpdf26_, threadalphas26_, order);
 else if(iThread == 27) xsec = ApplGridMap[GridName]->vconvolute( threadpdf27_, threadalphas27_, order);
 else if(iThread == 28) xsec = ApplGridMap[GridName]->vconvolute( threadpdf28_, threadalphas28_, order);
 else if(iThread == 29) xsec = ApplGridMap[GridName]->vconvolute( threadpdf29_, threadalphas29_, order);
 else if(iThread == 30) xsec = ApplGridMap[GridName]->vconvolute( threadpdf30_, threadalphas30_, order);
 else if(iThread == 31) xsec = ApplGridMap[GridName]->vconvolute( threadpdf31_, threadalphas31_, order);
 else if(iThread == 32) xsec = ApplGridMap[GridName]->vconvolute( threadpdf32_, threadalphas32_, order);
 else if(iThread == 33) xsec = ApplGridMap[GridName]->vconvolute( threadpdf33_, threadalphas33_, order);
 else if(iThread == 34) xsec = ApplGridMap[GridName]->vconvolute( threadpdf34_, threadalphas34_, order);
 else if(iThread == 35) xsec = ApplGridMap[GridName]->vconvolute( threadpdf35_, threadalphas35_, order);
 else if(iThread == 36) xsec = ApplGridMap[GridName]->vconvolute( threadpdf36_, threadalphas36_, order);
 else if(iThread == 37) xsec = ApplGridMap[GridName]->vconvolute( threadpdf37_, threadalphas37_, order);
 else if(iThread == 38) xsec = ApplGridMap[GridName]->vconvolute( threadpdf38_, threadalphas38_, order);
 else if(iThread == 39) xsec = ApplGridMap[GridName]->vconvolute( threadpdf39_, threadalphas39_, order);
 else if(iThread == 40) xsec = ApplGridMap[GridName]->vconvolute( threadpdf40_, threadalphas40_, order);
 else if(iThread == 41) xsec = ApplGridMap[GridName]->vconvolute( threadpdf41_, threadalphas41_, order);
 else if(iThread == 42) xsec = ApplGridMap[GridName]->vconvolute( threadpdf42_, threadalphas42_, order);
 else if(iThread == 43) xsec = ApplGridMap[GridName]->vconvolute( threadpdf43_, threadalphas43_, order);
 else if(iThread == 44) xsec = ApplGridMap[GridName]->vconvolute( threadpdf44_, threadalphas44_, order);
 else if(iThread == 45) xsec = ApplGridMap[GridName]->vconvolute( threadpdf45_, threadalphas45_, order);
 else if(iThread == 46) xsec = ApplGridMap[GridName]->vconvolute( threadpdf46_, threadalphas46_, order);
 else if(iThread == 47) xsec = ApplGridMap[GridName]->vconvolute( threadpdf47_, threadalphas47_, order);
 else if(iThread == 48) xsec = ApplGridMap[GridName]->vconvolute( threadpdf48_, threadalphas48_, order);
 else if(iThread == 49) xsec = ApplGridMap[GridName]->vconvolute( threadpdf49_, threadalphas49_, order);
 else if(iThread == 50) xsec = ApplGridMap[GridName]->vconvolute( threadpdf50_, threadalphas50_, order);
 else if(iThread == 51) xsec = ApplGridMap[GridName]->vconvolute( threadpdf51_, threadalphas51_, order);
 else if(iThread == 52) xsec = ApplGridMap[GridName]->vconvolute( threadpdf52_, threadalphas52_, order);
 else if(iThread == 53) xsec = ApplGridMap[GridName]->vconvolute( threadpdf53_, threadalphas53_, order);
 else if(iThread == 54) xsec = ApplGridMap[GridName]->vconvolute( threadpdf54_, threadalphas54_, order);
 else if(iThread == 55) xsec = ApplGridMap[GridName]->vconvolute( threadpdf55_, threadalphas55_, order);
 else if(iThread == 56) xsec = ApplGridMap[GridName]->vconvolute( threadpdf56_, threadalphas56_, order);
 else if(iThread == 57) xsec = ApplGridMap[GridName]->vconvolute( threadpdf57_, threadalphas57_, order);
 else if(iThread == 58) xsec = ApplGridMap[GridName]->vconvolute( threadpdf58_, threadalphas58_, order);
 else if(iThread == 59) xsec = ApplGridMap[GridName]->vconvolute( threadpdf59_, threadalphas59_, order);
 else if(iThread == 60) xsec = ApplGridMap[GridName]->vconvolute( threadpdf60_, threadalphas60_, order);
 else if(iThread == 61) xsec = ApplGridMap[GridName]->vconvolute( threadpdf61_, threadalphas61_, order);
 else if(iThread == 62) xsec = ApplGridMap[GridName]->vconvolute( threadpdf62_, threadalphas62_, order);
 else if(iThread == 63) xsec = ApplGridMap[GridName]->vconvolute( threadpdf63_, threadalphas63_, order);
 else if(iThread == 64) xsec = ApplGridMap[GridName]->vconvolute( threadpdf64_, threadalphas64_, order);
 else if(iThread == 65) xsec = ApplGridMap[GridName]->vconvolute( threadpdf65_, threadalphas65_, order);
 else if(iThread == 66) xsec = ApplGridMap[GridName]->vconvolute( threadpdf66_, threadalphas66_, order);
 else if(iThread == 67) xsec = ApplGridMap[GridName]->vconvolute( threadpdf67_, threadalphas67_, order);
 else if(iThread == 68) xsec = ApplGridMap[GridName]->vconvolute( threadpdf68_, threadalphas68_, order);
 else if(iThread == 69) xsec = ApplGridMap[GridName]->vconvolute( threadpdf69_, threadalphas69_, order);
 else if(iThread == 70) xsec = ApplGridMap[GridName]->vconvolute( threadpdf70_, threadalphas70_, order);
 else if(iThread == 71) xsec = ApplGridMap[GridName]->vconvolute( threadpdf71_, threadalphas71_, order);
 else if(iThread == 72) xsec = ApplGridMap[GridName]->vconvolute( threadpdf72_, threadalphas72_, order);
 else if(iThread == 73) xsec = ApplGridMap[GridName]->vconvolute( threadpdf73_, threadalphas73_, order);
 else if(iThread == 74) xsec = ApplGridMap[GridName]->vconvolute( threadpdf74_, threadalphas74_, order);
 else if(iThread == 75) xsec = ApplGridMap[GridName]->vconvolute( threadpdf75_, threadalphas75_, order);
 else if(iThread == 76) xsec = ApplGridMap[GridName]->vconvolute( threadpdf76_, threadalphas76_, order);
 else if(iThread == 77) xsec = ApplGridMap[GridName]->vconvolute( threadpdf77_, threadalphas77_, order);
 else if(iThread == 78) xsec = ApplGridMap[GridName]->vconvolute( threadpdf78_, threadalphas78_, order);
 else if(iThread == 79) xsec = ApplGridMap[GridName]->vconvolute( threadpdf79_, threadalphas79_, order);
 else if(iThread == 80) xsec = ApplGridMap[GridName]->vconvolute( threadpdf80_, threadalphas80_, order);
 else if(iThread == 81) xsec = ApplGridMap[GridName]->vconvolute( threadpdf81_, threadalphas81_, order);
 else if(iThread == 82) xsec = ApplGridMap[GridName]->vconvolute( threadpdf82_, threadalphas82_, order);
 else if(iThread == 83) xsec = ApplGridMap[GridName]->vconvolute( threadpdf83_, threadalphas83_, order);
 else if(iThread == 84) xsec = ApplGridMap[GridName]->vconvolute( threadpdf84_, threadalphas84_, order);
 else if(iThread == 85) xsec = ApplGridMap[GridName]->vconvolute( threadpdf85_, threadalphas85_, order);
 else if(iThread == 86) xsec = ApplGridMap[GridName]->vconvolute( threadpdf86_, threadalphas86_, order);
 else if(iThread == 87) xsec = ApplGridMap[GridName]->vconvolute( threadpdf87_, threadalphas87_, order);
 else if(iThread == 88) xsec = ApplGridMap[GridName]->vconvolute( threadpdf88_, threadalphas88_, order);
 else if(iThread == 89) xsec = ApplGridMap[GridName]->vconvolute( threadpdf89_, threadalphas89_, order);
 else if(iThread == 90) xsec = ApplGridMap[GridName]->vconvolute( threadpdf90_, threadalphas90_, order);
 else if(iThread == 91) xsec = ApplGridMap[GridName]->vconvolute( threadpdf91_, threadalphas91_, order);
 else if(iThread == 92) xsec = ApplGridMap[GridName]->vconvolute( threadpdf92_, threadalphas92_, order);
 else if(iThread == 93) xsec = ApplGridMap[GridName]->vconvolute( threadpdf93_, threadalphas93_, order);
 else if(iThread == 94) xsec = ApplGridMap[GridName]->vconvolute( threadpdf94_, threadalphas94_, order);
 else if(iThread == 95) xsec = ApplGridMap[GridName]->vconvolute( threadpdf95_, threadalphas95_, order);
 else if(iThread == 96) xsec = ApplGridMap[GridName]->vconvolute( threadpdf96_, threadalphas96_, order);
 else if(iThread == 97) xsec = ApplGridMap[GridName]->vconvolute( threadpdf97_, threadalphas97_, order);
 else if(iThread == 98) xsec = ApplGridMap[GridName]->vconvolute( threadpdf98_, threadalphas98_, order);
 else if(iThread == 99) xsec = ApplGridMap[GridName]->vconvolute( threadpdf99_, threadalphas99_, order);
 else if(iThread == 100) xsec = ApplGridMap[GridName]->vconvolute( threadpdf100_, threadalphas100_, order);
 for(int i = 0; i < xsec.size(); i++){
   if(isSetCut){
     double BinLeft = ApplGridMap[GridName]->obslow_internal(i);
     double BinRight = ApplGridMap[GridName]->obslow_internal(i) + ApplGridMap[GridName]->deltaobs_internal(i);
     bool RemovePoint = (BinLeft < BinLeftCut) || (BinRight > BinRightCut);
     if(RemovePoint) continue;
   }

   appl_xsec.push_back(xsec.at(i) / 1000.0);
 }
#endif
}

void ApplGridHelper::ThreadConvoluteppbarMacro()
{
#ifdef USE_APPLGRID
 if(PDFType == PDFTypeEnum::CT_LHAPDF){
   cout<<"Multiple thread only works for CTEQ PDF."<<endl;
   return;
 }

 TString GridName = SavedGridName;

 appl_xsec.clear();

 vector<double> xsec;
 if(iThread == 1) xsec = ApplGridMap[GridName]->vconvolute( threadpdf1_, threadpdfpbar1_, threadalphas1_, order);
 else if(iThread == 2) xsec = ApplGridMap[GridName]->vconvolute( threadpdf2_, threadpdfpbar2_, threadalphas2_, order);
 else if(iThread == 3) xsec = ApplGridMap[GridName]->vconvolute( threadpdf3_, threadpdfpbar3_, threadalphas3_, order);
 else if(iThread == 4) xsec = ApplGridMap[GridName]->vconvolute( threadpdf4_, threadpdfpbar4_, threadalphas4_, order);
 else if(iThread == 5) xsec = ApplGridMap[GridName]->vconvolute( threadpdf5_, threadpdfpbar5_, threadalphas5_, order);
 else if(iThread == 6) xsec = ApplGridMap[GridName]->vconvolute( threadpdf6_, threadpdfpbar6_, threadalphas6_, order);
 else if(iThread == 7) xsec = ApplGridMap[GridName]->vconvolute( threadpdf7_, threadpdfpbar7_, threadalphas7_, order);
 else if(iThread == 8) xsec = ApplGridMap[GridName]->vconvolute( threadpdf8_, threadpdfpbar8_, threadalphas8_, order);
 else if(iThread == 9) xsec = ApplGridMap[GridName]->vconvolute( threadpdf9_, threadpdfpbar9_, threadalphas9_, order);
 else if(iThread == 10) xsec = ApplGridMap[GridName]->vconvolute( threadpdf10_, threadpdfpbar10_, threadalphas10_, order);
 else if(iThread == 11) xsec = ApplGridMap[GridName]->vconvolute( threadpdf11_, threadpdfpbar11_, threadalphas11_, order);
 else if(iThread == 12) xsec = ApplGridMap[GridName]->vconvolute( threadpdf12_, threadpdfpbar12_, threadalphas12_, order);
 else if(iThread == 13) xsec = ApplGridMap[GridName]->vconvolute( threadpdf13_, threadpdfpbar13_, threadalphas13_, order);
 else if(iThread == 14) xsec = ApplGridMap[GridName]->vconvolute( threadpdf14_, threadpdfpbar14_, threadalphas14_, order);
 else if(iThread == 15) xsec = ApplGridMap[GridName]->vconvolute( threadpdf15_, threadpdfpbar15_, threadalphas15_, order);
 else if(iThread == 16) xsec = ApplGridMap[GridName]->vconvolute( threadpdf16_, threadpdfpbar16_, threadalphas16_, order);
 else if(iThread == 17) xsec = ApplGridMap[GridName]->vconvolute( threadpdf17_, threadpdfpbar17_, threadalphas17_, order);
 else if(iThread == 18) xsec = ApplGridMap[GridName]->vconvolute( threadpdf18_, threadpdfpbar18_, threadalphas18_, order);
 else if(iThread == 19) xsec = ApplGridMap[GridName]->vconvolute( threadpdf19_, threadpdfpbar19_, threadalphas19_, order);
 else if(iThread == 20) xsec = ApplGridMap[GridName]->vconvolute( threadpdf20_, threadpdfpbar20_, threadalphas20_, order);
 else if(iThread == 21) xsec = ApplGridMap[GridName]->vconvolute( threadpdf21_, threadpdfpbar21_, threadalphas21_, order);
 else if(iThread == 22) xsec = ApplGridMap[GridName]->vconvolute( threadpdf22_, threadpdfpbar22_, threadalphas22_, order);
 else if(iThread == 23) xsec = ApplGridMap[GridName]->vconvolute( threadpdf23_, threadpdfpbar23_, threadalphas23_, order);
 else if(iThread == 24) xsec = ApplGridMap[GridName]->vconvolute( threadpdf24_, threadpdfpbar24_, threadalphas24_, order);
 else if(iThread == 25) xsec = ApplGridMap[GridName]->vconvolute( threadpdf25_, threadpdfpbar25_, threadalphas25_, order);
 else if(iThread == 26) xsec = ApplGridMap[GridName]->vconvolute( threadpdf26_, threadpdfpbar26_, threadalphas26_, order);
 else if(iThread == 27) xsec = ApplGridMap[GridName]->vconvolute( threadpdf27_, threadpdfpbar27_, threadalphas27_, order);
 else if(iThread == 28) xsec = ApplGridMap[GridName]->vconvolute( threadpdf28_, threadpdfpbar28_, threadalphas28_, order);
 else if(iThread == 29) xsec = ApplGridMap[GridName]->vconvolute( threadpdf29_, threadpdfpbar29_, threadalphas29_, order);
 else if(iThread == 30) xsec = ApplGridMap[GridName]->vconvolute( threadpdf30_, threadpdfpbar30_, threadalphas30_, order);
 else if(iThread == 31) xsec = ApplGridMap[GridName]->vconvolute( threadpdf31_, threadpdfpbar31_, threadalphas31_, order);
 else if(iThread == 32) xsec = ApplGridMap[GridName]->vconvolute( threadpdf32_, threadpdfpbar32_, threadalphas32_, order);
 else if(iThread == 33) xsec = ApplGridMap[GridName]->vconvolute( threadpdf33_, threadpdfpbar33_, threadalphas33_, order);
 else if(iThread == 34) xsec = ApplGridMap[GridName]->vconvolute( threadpdf34_, threadpdfpbar34_, threadalphas34_, order);
 else if(iThread == 35) xsec = ApplGridMap[GridName]->vconvolute( threadpdf35_, threadpdfpbar35_, threadalphas35_, order);
 else if(iThread == 36) xsec = ApplGridMap[GridName]->vconvolute( threadpdf36_, threadpdfpbar36_, threadalphas36_, order);
 else if(iThread == 37) xsec = ApplGridMap[GridName]->vconvolute( threadpdf37_, threadpdfpbar37_, threadalphas37_, order);
 else if(iThread == 38) xsec = ApplGridMap[GridName]->vconvolute( threadpdf38_, threadpdfpbar38_, threadalphas38_, order);
 else if(iThread == 39) xsec = ApplGridMap[GridName]->vconvolute( threadpdf39_, threadpdfpbar39_, threadalphas39_, order);
 else if(iThread == 40) xsec = ApplGridMap[GridName]->vconvolute( threadpdf40_, threadpdfpbar40_, threadalphas40_, order);
 else if(iThread == 41) xsec = ApplGridMap[GridName]->vconvolute( threadpdf41_, threadpdfpbar41_, threadalphas41_, order);
 else if(iThread == 42) xsec = ApplGridMap[GridName]->vconvolute( threadpdf42_, threadpdfpbar42_, threadalphas42_, order);
 else if(iThread == 43) xsec = ApplGridMap[GridName]->vconvolute( threadpdf43_, threadpdfpbar43_, threadalphas43_, order);
 else if(iThread == 44) xsec = ApplGridMap[GridName]->vconvolute( threadpdf44_, threadpdfpbar44_, threadalphas44_, order);
 else if(iThread == 45) xsec = ApplGridMap[GridName]->vconvolute( threadpdf45_, threadpdfpbar45_, threadalphas45_, order);
 else if(iThread == 46) xsec = ApplGridMap[GridName]->vconvolute( threadpdf46_, threadpdfpbar46_, threadalphas46_, order);
 else if(iThread == 47) xsec = ApplGridMap[GridName]->vconvolute( threadpdf47_, threadpdfpbar47_, threadalphas47_, order);
 else if(iThread == 48) xsec = ApplGridMap[GridName]->vconvolute( threadpdf48_, threadpdfpbar48_, threadalphas48_, order);
 else if(iThread == 49) xsec = ApplGridMap[GridName]->vconvolute( threadpdf49_, threadpdfpbar49_, threadalphas49_, order);
 else if(iThread == 50) xsec = ApplGridMap[GridName]->vconvolute( threadpdf50_, threadpdfpbar50_, threadalphas50_, order);
 else if(iThread == 51) xsec = ApplGridMap[GridName]->vconvolute( threadpdf51_, threadpdfpbar51_, threadalphas51_, order);
 else if(iThread == 52) xsec = ApplGridMap[GridName]->vconvolute( threadpdf52_, threadpdfpbar52_, threadalphas52_, order);
 else if(iThread == 53) xsec = ApplGridMap[GridName]->vconvolute( threadpdf53_, threadpdfpbar53_, threadalphas53_, order);
 else if(iThread == 54) xsec = ApplGridMap[GridName]->vconvolute( threadpdf54_, threadpdfpbar54_, threadalphas54_, order);
 else if(iThread == 55) xsec = ApplGridMap[GridName]->vconvolute( threadpdf55_, threadpdfpbar55_, threadalphas55_, order);
 else if(iThread == 56) xsec = ApplGridMap[GridName]->vconvolute( threadpdf56_, threadpdfpbar56_, threadalphas56_, order);
 else if(iThread == 57) xsec = ApplGridMap[GridName]->vconvolute( threadpdf57_, threadpdfpbar57_, threadalphas57_, order);
 else if(iThread == 58) xsec = ApplGridMap[GridName]->vconvolute( threadpdf58_, threadpdfpbar58_, threadalphas58_, order);
 else if(iThread == 59) xsec = ApplGridMap[GridName]->vconvolute( threadpdf59_, threadpdfpbar59_, threadalphas59_, order);
 else if(iThread == 60) xsec = ApplGridMap[GridName]->vconvolute( threadpdf60_, threadpdfpbar60_, threadalphas60_, order);
 else if(iThread == 61) xsec = ApplGridMap[GridName]->vconvolute( threadpdf61_, threadpdfpbar61_, threadalphas61_, order);
 else if(iThread == 62) xsec = ApplGridMap[GridName]->vconvolute( threadpdf62_, threadpdfpbar62_, threadalphas62_, order);
 else if(iThread == 63) xsec = ApplGridMap[GridName]->vconvolute( threadpdf63_, threadpdfpbar63_, threadalphas63_, order);
 else if(iThread == 64) xsec = ApplGridMap[GridName]->vconvolute( threadpdf64_, threadpdfpbar64_, threadalphas64_, order);
 else if(iThread == 65) xsec = ApplGridMap[GridName]->vconvolute( threadpdf65_, threadpdfpbar65_, threadalphas65_, order);
 else if(iThread == 66) xsec = ApplGridMap[GridName]->vconvolute( threadpdf66_, threadpdfpbar66_, threadalphas66_, order);
 else if(iThread == 67) xsec = ApplGridMap[GridName]->vconvolute( threadpdf67_, threadpdfpbar67_, threadalphas67_, order);
 else if(iThread == 68) xsec = ApplGridMap[GridName]->vconvolute( threadpdf68_, threadpdfpbar68_, threadalphas68_, order);
 else if(iThread == 69) xsec = ApplGridMap[GridName]->vconvolute( threadpdf69_, threadpdfpbar69_, threadalphas69_, order);
 else if(iThread == 70) xsec = ApplGridMap[GridName]->vconvolute( threadpdf70_, threadpdfpbar70_, threadalphas70_, order);
 else if(iThread == 71) xsec = ApplGridMap[GridName]->vconvolute( threadpdf71_, threadpdfpbar71_, threadalphas71_, order);
 else if(iThread == 72) xsec = ApplGridMap[GridName]->vconvolute( threadpdf72_, threadpdfpbar72_, threadalphas72_, order);
 else if(iThread == 73) xsec = ApplGridMap[GridName]->vconvolute( threadpdf73_, threadpdfpbar73_, threadalphas73_, order);
 else if(iThread == 74) xsec = ApplGridMap[GridName]->vconvolute( threadpdf74_, threadpdfpbar74_, threadalphas74_, order);
 else if(iThread == 75) xsec = ApplGridMap[GridName]->vconvolute( threadpdf75_, threadpdfpbar75_, threadalphas75_, order);
 else if(iThread == 76) xsec = ApplGridMap[GridName]->vconvolute( threadpdf76_, threadpdfpbar76_, threadalphas76_, order);
 else if(iThread == 77) xsec = ApplGridMap[GridName]->vconvolute( threadpdf77_, threadpdfpbar77_, threadalphas77_, order);
 else if(iThread == 78) xsec = ApplGridMap[GridName]->vconvolute( threadpdf78_, threadpdfpbar78_, threadalphas78_, order);
 else if(iThread == 79) xsec = ApplGridMap[GridName]->vconvolute( threadpdf79_, threadpdfpbar79_, threadalphas79_, order);
 else if(iThread == 80) xsec = ApplGridMap[GridName]->vconvolute( threadpdf80_, threadpdfpbar80_, threadalphas80_, order);
 else if(iThread == 81) xsec = ApplGridMap[GridName]->vconvolute( threadpdf81_, threadpdfpbar81_, threadalphas81_, order);
 else if(iThread == 82) xsec = ApplGridMap[GridName]->vconvolute( threadpdf82_, threadpdfpbar82_, threadalphas82_, order);
 else if(iThread == 83) xsec = ApplGridMap[GridName]->vconvolute( threadpdf83_, threadpdfpbar83_, threadalphas83_, order);
 else if(iThread == 84) xsec = ApplGridMap[GridName]->vconvolute( threadpdf84_, threadpdfpbar84_, threadalphas84_, order);
 else if(iThread == 85) xsec = ApplGridMap[GridName]->vconvolute( threadpdf85_, threadpdfpbar85_, threadalphas85_, order);
 else if(iThread == 86) xsec = ApplGridMap[GridName]->vconvolute( threadpdf86_, threadpdfpbar86_, threadalphas86_, order);
 else if(iThread == 87) xsec = ApplGridMap[GridName]->vconvolute( threadpdf87_, threadpdfpbar87_, threadalphas87_, order);
 else if(iThread == 88) xsec = ApplGridMap[GridName]->vconvolute( threadpdf88_, threadpdfpbar88_, threadalphas88_, order);
 else if(iThread == 89) xsec = ApplGridMap[GridName]->vconvolute( threadpdf89_, threadpdfpbar89_, threadalphas89_, order);
 else if(iThread == 90) xsec = ApplGridMap[GridName]->vconvolute( threadpdf90_, threadpdfpbar90_, threadalphas90_, order);
 else if(iThread == 91) xsec = ApplGridMap[GridName]->vconvolute( threadpdf91_, threadpdfpbar91_, threadalphas91_, order);
 else if(iThread == 92) xsec = ApplGridMap[GridName]->vconvolute( threadpdf92_, threadpdfpbar92_, threadalphas92_, order);
 else if(iThread == 93) xsec = ApplGridMap[GridName]->vconvolute( threadpdf93_, threadpdfpbar93_, threadalphas93_, order);
 else if(iThread == 94) xsec = ApplGridMap[GridName]->vconvolute( threadpdf94_, threadpdfpbar94_, threadalphas94_, order);
 else if(iThread == 95) xsec = ApplGridMap[GridName]->vconvolute( threadpdf95_, threadpdfpbar95_, threadalphas95_, order);
 else if(iThread == 96) xsec = ApplGridMap[GridName]->vconvolute( threadpdf96_, threadpdfpbar96_, threadalphas96_, order);
 else if(iThread == 97) xsec = ApplGridMap[GridName]->vconvolute( threadpdf97_, threadpdfpbar97_, threadalphas97_, order);
 else if(iThread == 98) xsec = ApplGridMap[GridName]->vconvolute( threadpdf98_, threadpdfpbar98_, threadalphas98_, order);
 else if(iThread == 99) xsec = ApplGridMap[GridName]->vconvolute( threadpdf99_, threadpdfpbar99_, threadalphas99_, order);
 else if(iThread == 100) xsec = ApplGridMap[GridName]->vconvolute( threadpdf100_, threadpdfpbar100_, threadalphas100_, order);
 for(int i = 0; i < xsec.size(); i++){
   if(isSetCut){
     double BinLeft = ApplGridMap[GridName]->obslow_internal(i);
     double BinRight = ApplGridMap[GridName]->obslow_internal(i) + ApplGridMap[GridName]->deltaobs_internal(i);
     bool RemovePoint = (BinLeft < BinLeftCut) || (BinRight > BinRightCut);
     if(RemovePoint) continue;
   }

   appl_xsec.push_back(xsec.at(i) / 1000.0);
 }
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

TH1D* ApplGridHelper::Convolute(TString GridName, TString KFactorName)
{
 TH1D* h1;

 if(!isInitial[GridName]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return h1;
 }

#ifdef USE_APPLGRID
 ApplGridMap[GridName]->setckm(ckm);

 h1 = ApplGridMap[GridName]->convolute( evolvepdf_, alphaspdf_, order);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibin) - h1->GetXaxis()->GetBinLowEdge(ibin);
   double Value = h1->GetBinContent(ibin);
   h1->SetBinContent(ibin, Value * BinWidth / 1000.0);
   //cout<<"GridName: "<<GridName<<" ibin: "<<ibin<<" Value: "<<Value * BinWidth / 1000.0<<endl;
 }

 if(KFactorName != ""){
   vector<double> KFactors(h1->GetNbinsX());
   if(KFactorMap[KFactorName].size() == 0){
     cout<<"ERROR! KFactor file has not been initialized. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else if(KFactorMap[KFactorName].size() != KFactors.size()){
     cout<<"ERROR! KFactor file doesn't match to the convolute result. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else{
     KFactors = KFactorMap[KFactorName];
   }
   for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
     double Value = h1->GetBinContent(ibin);
     h1->SetBinContent(ibin, Value * KFactors.at(ibin - 1));
   }
 }

#endif

 return h1;
}

TH1D* ApplGridHelper::Convoluteppbar(TString GridName, TString KFactorName)
{
 TH1D* h1;

 if(!isInitial[GridName]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return h1;
 }

#ifdef USE_APPLGRID
 _pdf = evolvepdf_;

 ApplGridMap[GridName]->setckm(ckm);

 h1 = ApplGridMap[GridName]->convolute( evolvepdf_, evolvepdfpbar_, alphaspdf_, order);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibin) - h1->GetXaxis()->GetBinLowEdge(ibin);
   double Value = h1->GetBinContent(ibin);
   h1->SetBinContent(ibin, Value * BinWidth / 1000.0);
   //cout<<"GridName: "<<GridName<<" ibin: "<<ibin<<" Value: "<<Value<<" BinWidth: "<<BinWidth<<endl;
 }

 if(KFactorName != ""){
   vector<double> KFactors(h1->GetNbinsX());
   if(KFactorMap[KFactorName].size() == 0){
     cout<<"ERROR! KFactor file has not been initialized. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else if(KFactorMap[KFactorName].size() != KFactors.size()){
     cout<<"ERROR! KFactor file doesn't match to the convolute result. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else{
     KFactors = KFactorMap[KFactorName];
   }
   for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
     double Value = h1->GetBinContent(ibin);
     h1->SetBinContent(ibin, Value * KFactors.at(ibin - 1));
   }
 }

#endif

 return h1;
}


TH1D* ApplGridHelper::ConvoluteSubProc(TString GridName, int SubProc, TString KFactorName)
{
 TH1D* h1;

 if(!isInitial[GridName]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return h1;
 }

#ifdef USE_APPLGRID
 ApplGridMap[GridName]->setckm(ckm);

 h1 = ApplGridMap[GridName]->convolute_subproc(SubProc, evolvepdf_, alphaspdf_, order);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibin) - h1->GetXaxis()->GetBinLowEdge(ibin);
   double Value = h1->GetBinContent(ibin);
   h1->SetBinContent(ibin, Value * BinWidth / 1000.0);
   //cout<<"GridName: "<<GridName<<" SubProc: "<<SubProcName[SubProc]<<" ibin: "<<ibin<<" Value: "<<Value * BinWidth / 1000.0<<" BinWidth: "<<BinWidth<<endl;
 }

 if(KFactorName != ""){
   vector<double> KFactors(h1->GetNbinsX());
   if(KFactorMap[KFactorName].size() == 0){
     cout<<"ERROR! KFactor file has not been initialized. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else if(KFactorMap[KFactorName].size() != KFactors.size()){
     cout<<"ERROR! KFactor file doesn't match to the convolute result. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else{
     KFactors = KFactorMap[KFactorName];
   }
   for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
     double Value = h1->GetBinContent(ibin);
     h1->SetBinContent(ibin, Value * KFactors.at(ibin - 1));
   }
 }

#endif

 return h1;
}

TH1D* ApplGridHelper::ConvoluteppbarSubProc(TString GridName, int SubProc, TString KFactorName)
{
 TH1D* h1;

 if(!isInitial[GridName]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return h1;
 }

#ifdef USE_APPLGRID
 _pdf = evolvepdf_;

 ApplGridMap[GridName]->setckm(ckm);

 h1 = ApplGridMap[GridName]->convolute_subproc(SubProc, evolvepdf_, evolvepdfpbar_, alphaspdf_, order);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibin) - h1->GetXaxis()->GetBinLowEdge(ibin);
   double Value = h1->GetBinContent(ibin);
   h1->SetBinContent(ibin, Value * BinWidth / 1000.0);
cout<<"GridName: "<<GridName<<" SubProc: "<<SubProcName[SubProc]<<" ibin: "<<ibin<<" Value: "<<Value<<" BinWidth: "<<BinWidth<<endl;
 }

 if(KFactorName != ""){
   vector<double> KFactors(h1->GetNbinsX());
   if(KFactorMap[KFactorName].size() == 0){
     cout<<"ERROR! KFactor file has not been initialized. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else if(KFactorMap[KFactorName].size() != KFactors.size()){
     cout<<"ERROR! KFactor file doesn't match to the convolute result. KFactors have been set to 1.0"<<endl;
     for(int i = 0; i < KFactors.size(); i++){
       KFactors.at(i) = 1.0;
     }
   }
   else{
     KFactors = KFactorMap[KFactorName];
   }
   for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
     double Value = h1->GetBinContent(ibin);
     h1->SetBinContent(ibin, Value * KFactors.at(ibin - 1));
   }
 }

#endif

 return h1;
}

TH1D* ApplGridHelper::ConvoluteBasic(TString GridName, TString HistName, TString KFactorName)
{
 if(isLinkFile) hf->cd();

 TH1D* h1 = Convolute(GridName, KFactorName);

 h1->SetName(HistName + "_" + PDFName + "_" + (int)iSet);
 h1->SetTitle(HistName + "_" + PDFName + "_" + (int)iSet);

 if(isLinkFile) h1->Write();

 return h1;
}

TH1D* ApplGridHelper::ConvoluteppbarBasic(TString GridName, TString HistName, TString KFactorName)
{
 if(isLinkFile) hf->cd();

 TH1D* h1 = Convoluteppbar(GridName, KFactorName);

 h1->SetName(HistName + "_" + PDFName + "_" + (int)iSet);
 h1->SetTitle(HistName + "_" + PDFName + "_" + (int)iSet);

 if(isLinkFile) h1->Write();

 return h1;
}

TH1D* ApplGridHelper::ConvoluteSubProcBasic(TString GridName, TString SubProc, TString HistName, TString KFactorName)
{
 if(isLinkFile) hf->cd();

 TH1D* h1 = ConvoluteSubProc(GridName, SubProcIndex[SubProc], KFactorName);

 h1->SetName(HistName + "_" + SubProc + "_" + PDFName + "_" + (int)iSet);
 h1->SetTitle(HistName + "_" + SubProc + "_" + PDFName + "_" + (int)iSet);

 if(isLinkFile) h1->Write();

 return h1;
}

TH1D* ApplGridHelper::ConvoluteppbarSubProcBasic(TString GridName, TString SubProc, TString HistName, TString KFactorName)
{
 if(isLinkFile) hf->cd();

 TH1D* h1 = ConvoluteppbarSubProc(GridName, SubProcIndex[SubProc], KFactorName);

 h1->SetName(HistName + "_" + SubProc + "_" + PDFName + "_" + (int)iSet);
 h1->SetTitle(HistName + "_" + SubProc + "_" + PDFName + "_" + (int)iSet);

 if(isLinkFile) h1->Write();

 return h1;
}

TH1D* ApplGridHelper::ConvoluteCombineSubProcBasic(TString GridName, vector<TString> SubProcs, TString HistName, TString KFactorName)
{
 if(isLinkFile) hf->cd();

 vector<TH1D *> Histograms(SubProcs.size());

 for(int i = 0; i < Histograms.size(); i++){
   Histograms.at(i) = ConvoluteSubProc(GridName, SubProcIndex[SubProcs.at(i)], KFactorName);
 }

 TH1D* h1 = (TH1D *)Histograms.at(0)->Clone(HistName + "_" + PDFName + "_" + (int)iSet);

 h1->SetName(HistName + "_" + PDFName + "_" + (int)iSet);
 h1->SetTitle(HistName + "_" + PDFName + "_" + (int)iSet);

 for(int i = 1; i < Histograms.size(); i++){
   h1->Add(Histograms.at(i));
 }

 if(isLinkFile) h1->Write();

 return h1;
}

TH1D* ApplGridHelper::ConvoluteppbarCombineSubProcBasic(TString GridName, vector<TString> SubProcs, TString HistName, TString KFactorName)
{
 if(isLinkFile) hf->cd();

 vector<TH1D *> Histograms(SubProcs.size());

 for(int i = 0; i < Histograms.size(); i++){
   Histograms.at(i) = ConvoluteppbarSubProc(GridName, SubProcIndex[SubProcs.at(i)], KFactorName);
 }

 TH1D* h1 = (TH1D *)Histograms.at(0)->Clone(HistName + "_" + PDFName + "_" + (int)iSet);

 h1->SetName(HistName + "_" + PDFName + "_" + (int)iSet);
 h1->SetTitle(HistName + "_" + PDFName + "_" + (int)iSet);

 for(int i = 1; i < Histograms.size(); i++){
   h1->Add(Histograms.at(i));
 }

 if(isLinkFile) h1->Write();

 return h1;
}

///////////////////
//  Application  //
///////////////////

void ApplGridHelper::CalcP0(TString GridNameYP, TString GridNameYM, TString subName, double& P0u, double& P0d, vector<TString> KFactors)
{
 if(!isInitial[GridNameYP] || !isInitial[GridNameYM]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return;
 }

 TH1D* uubar_yp;
 TH1D* ug_yp;
 TH1D* gubar_yp;
 TH1D* ubaru_ym;
 TH1D* ubarg_ym;
 TH1D* gu_ym;

 TH1D* uubar_ym;
 TH1D* ug_ym;
 TH1D* gubar_ym;
 TH1D* ubaru_yp;
 TH1D* ubarg_yp;
 TH1D* gu_yp;

 TH1D* ddbar_yp;
 TH1D* dg_yp;
 TH1D* gdbar_yp;
 TH1D* dbard_ym;
 TH1D* dbarg_ym;
 TH1D* gd_ym;

 TH1D* ddbar_ym;
 TH1D* dg_ym;
 TH1D* gdbar_ym;
 TH1D* dbard_yp;
 TH1D* dbarg_yp;
 TH1D* gd_yp;

 TH1D* total_yp;
 TH1D* total_ym;

 TH1D* right_uubar;
 TH1D* wrong_uubar;
 TH1D* right_ddbar;
 TH1D* wrong_ddbar;
 TH1D* total;

 TString KFactor_uu_YP_right;
 TString KFactor_uu_YM_right;
 TString KFactor_uu_YM_wrong;
 TString KFactor_uu_YP_wrong;
 TString KFactor_dd_YP_right;
 TString KFactor_dd_YM_right;
 TString KFactor_dd_YM_wrong;
 TString KFactor_dd_YP_wrong;
 TString KFactor_total_YP;
 TString KFactor_total_YM;

 if(KFactors.size() != 0){
   KFactor_uu_YP_right = KFactors.at(0);
   KFactor_uu_YM_right = KFactors.at(1);
   KFactor_uu_YM_wrong = KFactors.at(2);
   KFactor_uu_YP_wrong = KFactors.at(3);
   KFactor_dd_YP_right = KFactors.at(4);
   KFactor_dd_YM_right = KFactors.at(5);
   KFactor_dd_YM_wrong = KFactors.at(6);
   KFactor_dd_YP_wrong = KFactors.at(7);
   KFactor_total_YP = KFactors.at(8);
   KFactor_total_YM = KFactors.at(9);
 }
 else{
   KFactor_uu_YP_right = "";
   KFactor_uu_YM_right = "";
   KFactor_uu_YM_wrong = "";
   KFactor_uu_YP_wrong = "";
   KFactor_dd_YP_right = "";
   KFactor_dd_YM_right = "";
   KFactor_dd_YM_wrong = "";
   KFactor_dd_YP_wrong = "";
   KFactor_total_YP = "";
   KFactor_total_YM = "";
 }

 uubar_yp = ConvoluteSubProc(GridNameYP, 80, KFactor_uu_YP_right);//uubar right
 ug_yp = ConvoluteSubProc(GridNameYP, 82, KFactor_uu_YP_right);
 gubar_yp = ConvoluteSubProc(GridNameYP, 58, KFactor_uu_YP_right);
 ubaru_ym = ConvoluteSubProc(GridNameYM, 40, KFactor_uu_YM_right);//ubaru right
 ubarg_ym = ConvoluteSubProc(GridNameYM, 38, KFactor_uu_YM_right);
 gu_ym = ConvoluteSubProc(GridNameYM, 62, KFactor_uu_YM_right);

 uubar_ym = ConvoluteSubProc(GridNameYM, 80, KFactor_uu_YM_wrong);//uubar wrong
 ug_ym = ConvoluteSubProc(GridNameYM, 82, KFactor_uu_YM_wrong);
 gubar_ym = ConvoluteSubProc(GridNameYM, 58, KFactor_uu_YM_wrong);
 ubaru_yp = ConvoluteSubProc(GridNameYP, 40, KFactor_uu_YP_wrong);//ubaru wrong
 ubarg_yp = ConvoluteSubProc(GridNameYP, 38, KFactor_uu_YP_wrong);
 gu_yp = ConvoluteSubProc(GridNameYP, 62, KFactor_uu_YP_wrong);

 ddbar_yp = ConvoluteSubProc(GridNameYP, 70, KFactor_dd_YP_right);//ddbar right
 dg_yp = ConvoluteSubProc(GridNameYP, 71, KFactor_dd_YP_right);
 gdbar_yp = ConvoluteSubProc(GridNameYP, 59, KFactor_dd_YP_right);
 dbard_ym = ConvoluteSubProc(GridNameYM, 50, KFactor_dd_YM_right);//dbard right
 dbarg_ym = ConvoluteSubProc(GridNameYM, 49, KFactor_dd_YM_right);
 gd_ym = ConvoluteSubProc(GridNameYM, 61, KFactor_dd_YM_right);

 ddbar_ym = ConvoluteSubProc(GridNameYM, 70, KFactor_dd_YM_wrong);//ddbar wrong
 dg_ym = ConvoluteSubProc(GridNameYM, 71, KFactor_dd_YM_wrong);
 gdbar_ym = ConvoluteSubProc(GridNameYM, 59, KFactor_dd_YM_wrong);
 dbard_yp = ConvoluteSubProc(GridNameYP, 50, KFactor_dd_YP_wrong);//dbard wrong
 dbarg_yp = ConvoluteSubProc(GridNameYP, 49, KFactor_dd_YP_wrong);
 gd_yp = ConvoluteSubProc(GridNameYP, 61, KFactor_dd_YP_wrong);

 total_yp = Convolute(GridNameYP, KFactor_total_YP);
 total_ym = Convolute(GridNameYM, KFactor_total_YM);

 right_uubar = (TH1D *)uubar_yp->Clone("right_uubar");
 right_uubar->Add(ug_yp);
 right_uubar->Add(gubar_yp);
 right_uubar->Add(ubaru_ym);
 right_uubar->Add(ubarg_ym);
 right_uubar->Add(gu_ym);

 wrong_uubar = (TH1D *)uubar_ym->Clone("wrong_uubar");
 wrong_uubar->Add(ug_ym);
 wrong_uubar->Add(gubar_ym);
 wrong_uubar->Add(ubaru_yp);
 wrong_uubar->Add(ubarg_yp);
 wrong_uubar->Add(gu_yp);

 right_ddbar = (TH1D *)ddbar_yp->Clone("right_ddbar");
 right_ddbar->Add(dg_yp);
 right_ddbar->Add(gdbar_yp);
 right_ddbar->Add(dbard_ym);
 right_ddbar->Add(dbarg_ym);
 right_ddbar->Add(gd_ym);

 wrong_ddbar = (TH1D *)ddbar_ym->Clone("wrong_ddbar");
 wrong_ddbar->Add(dg_ym);
 wrong_ddbar->Add(gdbar_ym);
 wrong_ddbar->Add(dbard_yp);
 wrong_ddbar->Add(dbarg_yp);
 wrong_ddbar->Add(gd_yp);

 total = (TH1D *)total_yp->Clone("total");
 total->Add(total_ym);

 TH1D* total_uubar = (TH1D *)wrong_uubar->Clone("total_uubar");
 total_uubar->Add(right_uubar);
 TH1D* total_ddbar = (TH1D *)wrong_ddbar->Clone("total_ddbar");
 total_ddbar->Add(right_ddbar);

 TH1D* relativeXsec_uubar = (TH1D *)total_uubar->Clone("RelativeCrossSection_uubar");
 relativeXsec_uubar->Divide(total);
 TH1D* relativeXsec_ddbar = (TH1D *)total_ddbar->Clone("RelativeCrossSection_ddbar");
 relativeXsec_ddbar->Divide(total);

 TH1D* Dilution_uu = (TH1D *)wrong_uubar->Clone("Dilution_uubar");
 Dilution_uu->Divide(total_uubar);
 TH1D* Dilution_dd = (TH1D *)wrong_ddbar->Clone("Dilution_ddbar");
 Dilution_dd->Divide(total_ddbar);

 TString HistName = PDFName + (TString)"_" + (int)iSet + subName;
 wrong_uubar->SetName((TString)"wrong_uubar_" + HistName);
 wrong_ddbar->SetName((TString)"wrong_ddbar_" + HistName);

 GetDilutionMeta(wrong_uubar, total_uubar, total, OneMinusTwoD_uu[HistName], RelativeCrossSection_uu[HistName]);
 GetDilutionMeta(wrong_ddbar, total_ddbar, total, OneMinusTwoD_dd[HistName], RelativeCrossSection_dd[HistName]);

 if(isLinkFile){
   hf->cd();
   OneMinusTwoD_uu[HistName]->Write();
   OneMinusTwoD_dd[HistName]->Write();
   RelativeCrossSection_uu[HistName]->Write();
   RelativeCrossSection_dd[HistName]->Write();
 }

 P0u = GetP0(right_uubar, wrong_uubar, total);
 P0d = GetP0(right_ddbar, wrong_ddbar, total);

 std::cout << "P0u: " << P0u << " P0d: " << P0d << std::endl;

}

void ApplGridHelper::CalcP0ppbar(TString GridName, TString subName, double& P0u, double& P0d, vector<TString> KFactors)
{
 if(!isInitial[GridName]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return;
 }

 TH1D* uubar;
 TH1D* ug;
 TH1D* gubar;
 TH1D* ubaru;
 TH1D* ubarg;
 TH1D* gu;

 TH1D* ddbar;
 TH1D* dg;
 TH1D* gdbar;
 TH1D* dbard;
 TH1D* dbarg;
 TH1D* gd;

 TString KFactor_uu_right;
 TString KFactor_uu_wrong;
 TString KFactor_dd_right;
 TString KFactor_dd_wrong;
 TString KFactor_total;

 if(KFactors.size() != 0){
   KFactor_uu_right = KFactors.at(0);
   KFactor_uu_wrong = KFactors.at(1);
   KFactor_dd_right = KFactors.at(2);
   KFactor_dd_wrong = KFactors.at(3);
   KFactor_total = KFactors.at(4);
 }
 else{
   KFactor_uu_right = "";
   KFactor_uu_wrong = "";
   KFactor_dd_right = "";
   KFactor_dd_wrong = "";
   KFactor_total = "";
 }

 uubar = ConvoluteppbarSubProc(GridName, 80, KFactor_uu_right);
 ug = ConvoluteppbarSubProc(GridName, 82, KFactor_uu_right);
 gubar = ConvoluteppbarSubProc(GridName, 58, KFactor_uu_right);
 ubaru = ConvoluteppbarSubProc(GridName, 40, KFactor_uu_wrong);
 ubarg = ConvoluteppbarSubProc(GridName, 38, KFactor_uu_wrong);
 gu = ConvoluteppbarSubProc(GridName, 62, KFactor_uu_wrong);

 ddbar = ConvoluteppbarSubProc(GridName, 70, KFactor_dd_right);
 dg = ConvoluteppbarSubProc(GridName, 71, KFactor_dd_right);
 gdbar = ConvoluteppbarSubProc(GridName, 59, KFactor_dd_right);
 dbard = ConvoluteppbarSubProc(GridName, 50, KFactor_dd_wrong);
 dbarg = ConvoluteppbarSubProc(GridName, 49, KFactor_dd_wrong);
 gd = ConvoluteppbarSubProc(GridName, 61, KFactor_dd_wrong);

 TH1D* right_uubar;
 TH1D* wrong_uubar;
 TH1D* right_ddbar;
 TH1D* wrong_ddbar;
 TH1D* total;

 total = Convoluteppbar(GridName, KFactor_total);

 right_uubar = (TH1D *)uubar->Clone("right_uubar");
 right_uubar->Add(ug);
 right_uubar->Add(gubar);

 wrong_uubar = (TH1D *)ubaru->Clone("wrong_uubar");
 wrong_uubar->Add(ubarg);
 wrong_uubar->Add(gu);

 right_ddbar = (TH1D *)ddbar->Clone("right_ddbar");
 right_ddbar->Add(dg);
 right_ddbar->Add(gdbar);

 wrong_ddbar = (TH1D *)dbard->Clone("wrong_ddbar");
 wrong_ddbar->Add(dbarg);
 wrong_ddbar->Add(gd);

 TH1D* total_uubar = (TH1D *)wrong_uubar->Clone("total_uubar");
 total_uubar->Add(right_uubar);
 TH1D* total_ddbar = (TH1D *)wrong_ddbar->Clone("total_ddbar");
 total_ddbar->Add(right_ddbar);

 TH1D* relativeXsec_uubar = (TH1D *)total_uubar->Clone("RelativeCrossSection_uubar");
 relativeXsec_uubar->Divide(total);
 TH1D* relativeXsec_ddbar = (TH1D *)total_ddbar->Clone("RelativeCrossSection_ddbar");
 relativeXsec_ddbar->Divide(total);

 TH1D* Dilution_uu = (TH1D *)wrong_uubar->Clone("Dilution_uubar");
 Dilution_uu->Divide(total_uubar);
 TH1D* Dilution_dd = (TH1D *)wrong_ddbar->Clone("Dilution_ddbar");
 Dilution_dd->Divide(total_ddbar);

 TString HistName = PDFName + (int)iSet + subName;
 wrong_uubar->SetName((TString)"ppbar_wrong_uubar_" + HistName);
 wrong_ddbar->SetName((TString)"ppbar_wrong_ddbar_" + HistName);

 GetDilutionMeta(wrong_uubar, total_uubar, total, OneMinusTwoD_uu[HistName], RelativeCrossSection_uu[HistName]);
 GetDilutionMeta(wrong_ddbar, total_ddbar, total, OneMinusTwoD_dd[HistName], RelativeCrossSection_dd[HistName]);

 if(isLinkFile){
   hf->cd();
   OneMinusTwoD_uu[HistName]->Write();
   OneMinusTwoD_dd[HistName]->Write();
   RelativeCrossSection_uu[HistName]->Write();
   RelativeCrossSection_dd[HistName]->Write();
 }

 P0u = GetP0(right_uubar, wrong_uubar, total);
 P0d = GetP0(right_ddbar, wrong_ddbar, total);

 std::cout << "P0u: " << P0u << " P0d: " << P0d << std::endl;

}

double ApplGridHelper::GetP0(TH1D* right, TH1D* wrong, TH1D* total)
{
 TH1D* Dilution = (TH1D *)right->Clone("Dilution");
 Dilution->Add(wrong, -1);
 Dilution->Divide(total);

 double Average = 0.0;
 double TotalWidth = 0.0;

 for(int i = 1; i <= Dilution->GetNbinsX(); i++){
   Average += Dilution->GetBinContent(i) * (Dilution->GetXaxis()->GetBinUpEdge(i) - Dilution->GetXaxis()->GetBinLowEdge(i));
   TotalWidth += Dilution->GetXaxis()->GetBinUpEdge(i) - Dilution->GetXaxis()->GetBinLowEdge(i);
 }
 Average = Average / TotalWidth;

 delete Dilution;

 return Average;
}

TH1D* ApplGridHelper::ConvoluteAFB(TString GridNameForward, TString GridNameBackward, TString subName, int flavor)
{
 if(isLinkFile) hf->cd();

 TH1D* AFB;
 if(!isInitial[GridNameForward] || !isInitial[GridNameBackward]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return AFB;
 }   

 TH1D* Forward;
 TH1D* Backward;

 if(flavor < 0){
   Forward = Convolute(GridNameForward);
   Backward = Convolute(GridNameBackward);
 }
 else if(flavor == 2){
   TH1D* uubar_f = ConvoluteSubProc(GridNameForward, SubProcIndex["uubar"]);//uubar forward
   TH1D* ug_f = ConvoluteSubProc(GridNameForward, SubProcIndex["ugluon"]);
   TH1D* gubar_f = ConvoluteSubProc(GridNameForward, SubProcIndex["gluonubar"]);
   TH1D* ubaru_f = ConvoluteSubProc(GridNameForward, SubProcIndex["ubaru"]);//ubaru forward
   TH1D* ubarg_f = ConvoluteSubProc(GridNameForward, SubProcIndex["ubargluon"]);
   TH1D* gu_f = ConvoluteSubProc(GridNameForward, SubProcIndex["gluonu"]);

   TH1D* uubar_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["uubar"]);//uubar backward
   TH1D* ug_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["ugluon"]);
   TH1D* gubar_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["gluonubar"]);
   TH1D* ubaru_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["ubaru"]);//ubaru backward
   TH1D* ubarg_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["ubargluon"]);
   TH1D* gu_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["gluonu"]);

   Forward = (TH1D *)uubar_f->Clone("Forward");
   Forward->Add(ug_f);
   Forward->Add(gubar_f);
   Forward->Add(ubaru_f);
   Forward->Add(ubarg_f);
   Forward->Add(gu_f);

   Backward = (TH1D *)uubar_b->Clone("Backward");
   Backward->Add(ug_b);
   Backward->Add(gubar_b);
   Backward->Add(ubaru_b);
   Backward->Add(ubarg_b);
   Backward->Add(gu_b);

   delete uubar_f;
   delete ug_f;
   delete gubar_f;
   delete ubaru_f;
   delete ubarg_f;
   delete gu_f;

   delete uubar_b;
   delete ug_b;
   delete gubar_b;
   delete ubaru_b;
   delete ubarg_b;
   delete gu_b;
 }
 else if(flavor == 1){
   TH1D* ddbar_f = ConvoluteSubProc(GridNameForward, SubProcIndex["ddbar"]);//ddbar forward
   TH1D* dg_f = ConvoluteSubProc(GridNameForward, SubProcIndex["dgluon"]);
   TH1D* gdbar_f = ConvoluteSubProc(GridNameForward, SubProcIndex["gluondbar"]);
   TH1D* dbard_f = ConvoluteSubProc(GridNameForward, SubProcIndex["dbard"]);//dbard forward
   TH1D* dbarg_f = ConvoluteSubProc(GridNameForward, SubProcIndex["dbargluon"]);
   TH1D* gd_f = ConvoluteSubProc(GridNameForward, SubProcIndex["gluond"]);

   TH1D* ddbar_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["ddbar"]);//ddbar backward
   TH1D* dg_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["dgluon"]);
   TH1D* gdbar_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["gluondbar"]);
   TH1D* dbard_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["dbard"]);//dbard backward
   TH1D* dbarg_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["dbargluon"]);
   TH1D* gd_b = ConvoluteSubProc(GridNameBackward, SubProcIndex["gluond"]);

   Forward = (TH1D *)ddbar_f->Clone("Forward");
   Forward->Add(dg_f);
   Forward->Add(gdbar_f);
   Forward->Add(dbard_f);
   Forward->Add(dbarg_f);
   Forward->Add(gd_f);

   Backward = (TH1D *)ddbar_b->Clone("Backward");
   Backward->Add(dg_b);
   Backward->Add(gdbar_b);
   Backward->Add(dbard_b);
   Backward->Add(dbarg_b);
   Backward->Add(gd_b);

   delete ddbar_f;
   delete dg_f;
   delete gdbar_f;
   delete dbard_f;
   delete dbarg_f;
   delete gd_f;

   delete ddbar_b;
   delete dg_b;
   delete gdbar_b;
   delete dbard_b;
   delete dbarg_b;
   delete gd_b;
 }

 if(isStatReweight){
   Forward = GenPseudodataNoFluc(Luminosity, Forward);
   Backward = GenPseudodataNoFluc(Luminosity, Backward);
 }

 TString HistName = PDFName + (TString)"_" + (int)iSet + subName;
 if(flavor < 0) AFB = (TH1D *)Forward->Clone((TString)"AFB_" + HistName);
 else if(flavor == 2) AFB = (TH1D *)Forward->Clone((TString)"AFB_uubar_" + HistName);
 else if(flavor == 1) AFB = (TH1D *)Forward->Clone((TString)"AFB_ddbar_" + HistName);

 AFB->Reset();

 AFBFunction(Forward, Backward, AFB);

 delete Forward;
 delete Backward;

 return AFB;
}

TH1D* ApplGridHelper::ConvoluteDilution(TString GridNameYP, TString GridNameYM, TString subName, int flavor)
{
 if(isLinkFile) hf->cd();

 TH1D* Dilution;
 if(!isInitial[GridNameYP] || !isInitial[GridNameYM]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return Dilution;
 }

 TH1D* uubar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["uubar"]);//uubar right
 TH1D* ug_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["ugluon"]);
 TH1D* gubar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluonubar"]);
 TH1D* ubaru_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["ubaru"]);//ubaru right
 TH1D* ubarg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["ubargluon"]);
 TH1D* gu_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluonu"]);

 TH1D* uubar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["uubar"]);//uubar wrong
 TH1D* ug_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["ugluon"]);
 TH1D* gubar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluonubar"]);
 TH1D* ubaru_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["ubaru"]);//ubaru wrong
 TH1D* ubarg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["ubargluon"]);
 TH1D* gu_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluonu"]);

 TH1D* ddbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["ddbar"]);//ddbar right
 TH1D* dg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["dgluon"]);
 TH1D* gdbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluondbar"]);
 TH1D* dbard_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["dbard"]);//dbard right
 TH1D* dbarg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["dbargluon"]);
 TH1D* gd_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluond"]);

 TH1D* ddbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["ddbar"]);//ddbar wrong
 TH1D* dg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["dgluon"]);
 TH1D* gdbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluondbar"]);
 TH1D* dbard_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["dbard"]);//dbard wrong
 TH1D* dbarg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["dbargluon"]);
 TH1D* gd_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluond"]);

 TH1D* ssbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["ssbar"]);//ssbar right
 TH1D* sg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["sgluon"]);
 TH1D* gsbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluonsbar"]);
 TH1D* sbars_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["sbars"]);//sbars right
 TH1D* sbarg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["sbargluon"]);
 TH1D* gs_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluons"]);

 TH1D* ssbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["ssbar"]);//ssbar wrong
 TH1D* sg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["sgluon"]);
 TH1D* gsbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluonsbar"]);
 TH1D* sbars_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["sbars"]);//sbars wrong
 TH1D* sbarg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["sbargluon"]);
 TH1D* gs_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluons"]);

 TH1D* ccbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["ccbar"]);//ccbar right
 TH1D* cg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["cgluon"]);
 TH1D* gcbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluoncbar"]);
 TH1D* cbarc_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["cbarc"]);//cbarc right
 TH1D* cbarg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["cbargluon"]);
 TH1D* gc_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluonc"]);

 TH1D* ccbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["ccbar"]);//ccbar wrong
 TH1D* cg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["cgluon"]);
 TH1D* gcbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluoncbar"]);
 TH1D* cbarc_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["cbarc"]);//cbarc wrong
 TH1D* cbarg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["cbargluon"]);
 TH1D* gc_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluonc"]);

 TH1D* bbbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["bbbar"]);//bbbar right
 TH1D* bg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["bgluon"]);
 TH1D* gbbar_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluonbbar"]);
 TH1D* bbarb_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["bbarb"]);//bbarb right
 TH1D* bbarg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["bbargluon"]);
 TH1D* gb_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluonb"]);

 TH1D* bbbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["bbbar"]);//bbbar wrong
 TH1D* bg_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["bgluon"]);
 TH1D* gbbar_ym = ConvoluteSubProc(GridNameYM, SubProcIndex["gluonbbar"]);
 TH1D* bbarb_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["bbarb"]);//bbarb wrong
 TH1D* bbarg_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["bbargluon"]);
 TH1D* gb_yp = ConvoluteSubProc(GridNameYP, SubProcIndex["gluonb"]);

 TH1D* right;
 TH1D* wrong;

 if(flavor < 0){
   right = (TH1D *)uubar_yp->Clone("right");
   right->Add(ug_yp);
   right->Add(gubar_yp);
   right->Add(ubaru_ym);
   right->Add(ubarg_ym);
   right->Add(gu_ym);
  
   wrong = (TH1D *)uubar_ym->Clone("wrong");
   wrong->Add(ug_ym);
   wrong->Add(gubar_ym);
   wrong->Add(ubaru_yp);
   wrong->Add(ubarg_yp);
   wrong->Add(gu_yp);
  
   right->Add(ddbar_yp);
   right->Add(dg_yp);
   right->Add(gdbar_yp);
   right->Add(dbard_ym);
   right->Add(dbarg_ym);
   right->Add(gd_ym);
  
   wrong->Add(ddbar_ym);
   wrong->Add(dg_ym);
   wrong->Add(gdbar_ym);
   wrong->Add(dbard_yp);
   wrong->Add(dbarg_yp);
   wrong->Add(gd_yp);
  
   right->Add(ssbar_yp);
   right->Add(sg_yp);
   right->Add(gsbar_yp);
   right->Add(sbars_ym);
   right->Add(sbarg_ym);
   right->Add(gs_ym);
  
   wrong->Add(ssbar_ym);
   wrong->Add(sg_ym);
   wrong->Add(gsbar_ym);
   wrong->Add(sbars_yp);
   wrong->Add(sbarg_yp);
   wrong->Add(gs_yp);
  
   right->Add(ccbar_yp);
   right->Add(cg_yp);
   right->Add(gcbar_yp);
   right->Add(cbarc_ym);
   right->Add(cbarg_ym);
   right->Add(gc_ym);
  
   wrong->Add(ccbar_ym);
   wrong->Add(cg_ym);
   wrong->Add(gcbar_ym);
   wrong->Add(cbarc_yp);
   wrong->Add(cbarg_yp);
   wrong->Add(gc_yp);
  
   right->Add(bbbar_yp);
   right->Add(bg_yp);
   right->Add(gbbar_yp);
   right->Add(bbarb_ym);
   right->Add(bbarg_ym);
   right->Add(gb_ym);
  
   wrong->Add(bbbar_ym);
   wrong->Add(bg_ym);
   wrong->Add(gbbar_ym);
   wrong->Add(bbarb_yp);
   wrong->Add(bbarg_yp);
   wrong->Add(gb_yp);
 }
 else if(flavor == 2){
   right = (TH1D *)uubar_yp->Clone("right");
   right->Add(ug_yp);
   right->Add(gubar_yp);
   right->Add(ubaru_ym);
   right->Add(ubarg_ym);
   right->Add(gu_ym);

   wrong = (TH1D *)uubar_ym->Clone("wrong");
   wrong->Add(ug_ym);
   wrong->Add(gubar_ym);
   wrong->Add(ubaru_yp);
   wrong->Add(ubarg_yp);
   wrong->Add(gu_yp);
 }
 else if(flavor == 1){
   right = (TH1D *)ddbar_yp->Clone("right");
   right->Add(dg_yp);
   right->Add(gdbar_yp);
   right->Add(dbard_ym);
   right->Add(dbarg_ym);
   right->Add(gd_ym);

   wrong = (TH1D *)ddbar_ym->Clone("wrong");
   wrong->Add(dg_ym);
   wrong->Add(gdbar_ym);
   wrong->Add(dbard_yp);
   wrong->Add(dbarg_yp);
   wrong->Add(gd_yp);
 }


 TH1D* total = (TH1D *)right->Clone("total");
 total->Add(wrong);

 TString HistName = PDFName + (TString)"_" + (int)iSet + subName;
 if(flavor < 0) Dilution = (TH1D *)wrong->Clone((TString)"Dilution_" + HistName);
 else if(flavor == 2) Dilution = (TH1D *)wrong->Clone((TString)"Dilution_uubar_" + HistName);
 else if(flavor == 1) Dilution = (TH1D *)wrong->Clone((TString)"Dilution_ddbar_" + HistName);

 Dilution->Divide(total);

 delete uubar_yp;
 delete ug_yp;
 delete gubar_yp;
 delete ubaru_ym;
 delete ubarg_ym;
 delete gu_ym;
 delete uubar_ym;
 delete ug_ym;
 delete gubar_ym;
 delete ubaru_yp;
 delete ubarg_yp;
 delete gu_yp;

 delete ddbar_yp;
 delete dg_yp;
 delete gdbar_yp;
 delete dbard_ym;
 delete dbarg_ym;
 delete gd_ym;
 delete ddbar_ym;
 delete dg_ym;
 delete gdbar_ym;
 delete dbard_yp;
 delete dbarg_yp;
 delete gd_yp;

 delete ssbar_yp;
 delete sg_yp;
 delete gsbar_yp;
 delete sbars_ym;
 delete sbarg_ym;
 delete gs_ym;
 delete ssbar_ym;
 delete sg_ym;
 delete gsbar_ym;
 delete sbars_yp;
 delete sbarg_yp;
 delete gs_yp;

 delete ccbar_yp;
 delete cg_yp;
 delete gcbar_yp;
 delete cbarc_ym;
 delete cbarg_ym;
 delete gc_ym;
 delete ccbar_ym;
 delete cg_ym;
 delete gcbar_ym;
 delete cbarc_yp;
 delete cbarg_yp;
 delete gc_yp;

 delete bbbar_yp;
 delete bg_yp;
 delete gbbar_yp;
 delete bbarb_ym;
 delete bbarg_ym;
 delete gb_ym;
 delete bbbar_ym;
 delete bg_ym;
 delete gbbar_ym;
 delete bbarb_yp;
 delete bbarg_yp;
 delete gb_yp;

 delete right;
 delete wrong;
 delete total;

 return Dilution;
}

TH1D* ApplGridHelper::ConvoluteBoostAsym(TString GridNameBoostPlus, TString GridNameBoostMinus, TString subName)
{
 if(isLinkFile) hf->cd();

 TH1D* BoostAsym;
 if(!isInitial[GridNameBoostPlus] || !isInitial[GridNameBoostMinus]){
   cout<<"ERROR! Please initialize grid first!"<<endl;
   return BoostAsym;
 }   

 TH1D* BoostPlus = Convolute(GridNameBoostPlus);
 TH1D* BoostMinus = Convolute(GridNameBoostMinus);

 if(isStatReweight){
   BoostPlus = GenPseudodataNoFluc(Luminosity, BoostPlus);
   BoostMinus = GenPseudodataNoFluc(Luminosity, BoostMinus);
 }

 TString HistName = PDFName + (TString)"_" + (int)iSet + subName;
 BoostAsym = (TH1D *)BoostPlus->Clone((TString)"BoostAsymmetry_" + HistName);
 BoostAsym->Reset();

 AFBFunction(BoostPlus, BoostMinus, BoostAsym);

 delete BoostPlus;
 delete BoostMinus;

 return BoostAsym;
}

TH1D* ApplGridHelper::AFBExtend(vector<TString> GridNamesForward, vector<TString> GridNamesBackward, vector<TString> subNames, int flavor)
{
 if(isLinkFile) hf->cd();

 vector<TH1D *> hists(GridNamesForward.size());

 for(int i = 0; i < hists.size(); i++){
   hists.at(i) = ConvoluteAFB(GridNamesForward.at(i), GridNamesBackward.at(i), subNames.at(i), flavor);
 }

 TH1D* h1 = HistExtend(hists);

 return h1;
}

TH1D* ApplGridHelper::DilutionExtend(vector<TString> GridNamesYP, vector<TString> GridNamesYM, vector<TString> subNames, int flavor)
{
 if(isLinkFile) hf->cd();
 
 vector<TH1D *> hists(GridNamesYP.size());
 
 for(int i = 0; i < hists.size(); i++){
   hists.at(i) = ConvoluteDilution(GridNamesYP.at(i), GridNamesYM.at(i), subNames.at(i), flavor);
 }
 
 TH1D* h1 = HistExtend(hists);
 
 return h1;
}

///////////////////////
//  PDF Uncertainty  //
///////////////////////

void ApplGridHelper::CalcPDFUnc(TString GridName, TString subName, TString PDFName, int nSet, TString KFactor, int FirstBin, int LastBin)
{
 if(isLinkFile) hf->cd();
 
 cout<<"Calculate PDF uncertainty:"<<endl;
 
 vector<TH1D *> HistVectorOrigin(nSet + 1);
 vector<TH1D *> HistVector(nSet + 1);
 TH1D* PDFError;
 for(int i = 0; i <= nSet; i++){
   InitialPDF(PDFName, i);
   HistVectorOrigin.at(i) = ConvoluteBasic(GridName, subName, KFactor);
   HistDivideBinWidth(HistVectorOrigin.at(i), HistVector.at(i));
 }

 cout<<"PDFUncertainty:"<<endl;
 FileForEPUMP* file = new FileForEPUMP(subName);
 file->InputTheory(HistVector);
 if(FirstBin != -1){
   file->writetheory(FirstBin, LastBin);
 }
 else{
   file->writetheory();
 }
}

void ApplGridHelper::CalcP0PDFUnc(TString GridNameYP, TString GridNameYM, TString subName, TString PDFName, int nSet, vector<TString> KFactors)
{
 double P0u;
 double P0d;
 for(int i = 0; i <= nSet; i++){
   InitialPDF(PDFName, i);
   CalcP0(GridNameYP, GridNameYM, subName, P0u, P0d, KFactors);
   std::cout << "PDF set: " << i << " P0u: " << P0u << " P0d: " << P0d << std::endl;
 }
}

void ApplGridHelper::CalcAFBPDFUnc(TString GridNameForward, TString GridNameBackward, TString subName, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors)
{
 if(isLinkFile) hf->cd();

 cout<<"Calculate PDF uncertainty for AFB:"<<endl;

 vector<TH1D *> HistVector(nSet + 1);
 TH1D* PDFError;
 for(int i = 0; i <= nSet; i++){
   cout<<PDFName<<"  "<<i<<endl;
   InitialPDF(PDFName, i);
   HistVector.at(i) = ConvoluteAFB(GridNameForward, GridNameBackward, subName, flavor);
 }

 cout<<"PDFUncertainty:"<<endl;
 PDFUncertainty* unc = new PDFUncertainty();
 unc->Input1DPlot(ErrorType, HistVector, PDFError);
}

void ApplGridHelper::CalcDilutionPDFUnc(TString GridNameYP, TString GridNameYM, TString subName, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors)
{
 if(isLinkFile) hf->cd();

 cout<<"Calculate PDF uncertainty for dilution:"<<endl;

 vector<TH1D *> HistVector(nSet + 1);
 TH1D* PDFError;
 for(int i = 0; i <= nSet; i++){
   cout<<PDFName<<"  "<<i<<endl;
   InitialPDF(PDFName, i);
   HistVector.at(i) = ConvoluteDilution(GridNameYP, GridNameYM, subName, flavor);
 }

 cout<<"PDFUncertainty:"<<endl;
 PDFUncertainty* unc = new PDFUncertainty();
 unc->Input1DPlot(ErrorType, HistVector, PDFError);
}

////////////////////////////////
//  PDF Uncertainty Extended  //
////////////////////////////////

void ApplGridHelper::CalcAFBExtendPDFUnc(vector<TString> GridNamesForward, vector<TString> GridNamesBackward, vector<TString> subNames, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors)
{
 if(isLinkFile) hf->cd();

 cout<<"Calculate PDF uncertainty for AFB:"<<endl;

 vector<TH1D *> HistVector(nSet + 1);
 TH1D* PDFError;
 for(int i = 0; i <= nSet; i++){
   cout<<PDFName<<"  "<<i<<endl;
   InitialPDF(PDFName, i);
   HistVector.at(i) = AFBExtend(GridNamesForward, GridNamesBackward, subNames, flavor);
 }

 cout<<"PDFUncertainty:"<<endl;
 PDFUncertainty* unc = new PDFUncertainty();
 unc->Input1DPlot(ErrorType, HistVector, PDFError);

 FileForEPUMP* file = new FileForEPUMP((TString)"AFB_" + PDFName + (TString)"_flavor" + (int)flavor + subNames.at(0));
 file->InputData(HistVector.at(0));
 file->InputTheory(unc);
 file->writedata();
 file->writetheory();
}

void ApplGridHelper::CalcDilutionExtendPDFUnc(vector<TString> GridNamesYP, vector<TString> GridNamesYM, vector<TString> subNames, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors)
{
 if(isLinkFile) hf->cd();

 cout<<"Calculate PDF uncertainty for Dilution:"<<endl;

 vector<TH1D *> HistVector(nSet + 1);
 TH1D* PDFError;
 for(int i = 0; i <= nSet; i++){
   cout<<PDFName<<"  "<<i<<endl;
   InitialPDF(PDFName, i);
   HistVector.at(i) = DilutionExtend(GridNamesYP, GridNamesYM, subNames, flavor);
 }

 cout<<"PDFUncertainty:"<<endl;
 PDFUncertainty* unc = new PDFUncertainty();
 unc->Input1DPlot(ErrorType, HistVector, PDFError);
}

