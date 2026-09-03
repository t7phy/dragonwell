#include "Calculation/CalcVBP.h"

CalcVBP::CalcVBP()
{

}

void CalcVBP::SetVBPPar(int Ihd1, int Ihd2, int Jbsn, int Jord, int Jschm, int Jscal)
{
 this->Nbm  = Ihd1;
 this->Ntg  = Ihd2;
 this->IBsn = Jbsn;
 this->IOrd = Jord;

//                       iSchm = 0/1  corresponds to msbar/DIS schemes
//pn12 The DIS scheme is disabled in the NNLO version
 if(Jschm != 0){
   cout<<"SetVbpPar: only MS-bar scheme is supported"<<endl;
   return;
 }

 int schm = Jschm;
                       // iScal = 0  : scale Amu = Q
                       //       = 1  : scale Amu is treated as indep. variable.
 int scal = Jscal;
                                                      // Use ParVbp to set LL and LM as well.

 this->Ischm = Jschm;
 if(this->Ischm == 0){
   this->LM = true;
 }
 else if(Ischm == 1){
   this->LM = false;
 }
 else{
   cout<<"ISCHM can only be 0 (msbar) or 1 (DIS)."<<endl;
   return;
 }

 this->Iscal = Jscal;
 if(this->Iscal == 0){
                                       // if LL=.False., must set Amu=Q
   this->LL = false;
   this->aMu = this->Q;
 }
 else if(this->Iscal == 1){
                                       // if LL=.True., let Amu be an indep. var
   this->LL = true;
 }
 else{
   cout<<"iScal can only be 0 (Amu=Q) or 1 (Amu.Ne.Q)."<<endl;
   return;
 }

}

void CalcVBP::SetVBPVar(double Rs, double Qq, double Scle, double Rerr)
{
 this->Rts = Rs;
 this->Q = Qq;
//                              Set Amu only if Iscal = 0 (.Not. LL)
 if(!LL) this->aMu = Scle;
 this->Rer = Rerr;
}

double CalcVBP::VBPdy1(double y)
{
// These comments are included in the lead subprogram to survive forsplit.
//
//===========================================================================
// GroupName: VbpXsc
// Description: cross-section calculations and some auxilaries
// ListOfFiles: vbpdy1 wlepasymk gq11 dist
//===========================================================================
//
// #Header: /Net/d2a/wkt/1hep/3vbp/RCS/VbpXsc.f,v 1.2 98/08/16 21:21:07 wkt Exp $ 
// #Log: VbpXsc.f,v $
// Revision 1.2  98/08/16  21:21:07  wkt
// Modifications induced by changes from EwkPac5 to EwkPac6.
//   SetEwk changed; Setup and Call of EW coupling constants changed.
// 
// Revision 1.1  98/08/05  23:53:48  wkt
// Initial revision
// 
//                             Input parameters are in the common block /STCOM/
//
//                             Output crossection is normalized to the simple
//                             parton formula in the tree approximation.
//
//                             1-loop corrections are normalized to Born term;
//                             Formulas are from Kubar et.al. (Nucl.Phys.B175)

 double Value = 0.0;

 double sml = 1e-6;
 double Er1, ER;
 int IER1, IER;

 int nflt = GetNfl(this->aMu);

 double tau = this->Q / this->Rts;
 this->xa   = exp( y) * tau;
 this->xb   = exp(-y) * tau;
 this->ia = 0;
 this->ib = 0;

// jfo  mods for E866 xf
 double xffac = 1.0;
 if(ixfx == 1) xffac = 1.0 / (xa + xb);

// jfo
//                         Leading Order and 1-loop QQ and GQ terms 
 double SIGLO = 0.0;
 double SG1QQ = 0.0;
 double SG1GQ = 0.0;

 for(int i = -nflt; i <= nflt; i++){
   fa0[i] = GetPDF(Nbm, i, xa, aMu);
   fb0[i] = GetPDF(Ntg, i, xb, aMu);
 }

 if(!isDefineVBPFunctions) DefineFunctions_VBP();

//                                           ...............Quark-Antiquark Part
 for(ia = -nflt; ia <= nflt; ia++){
   if(ia == 0) continue;
   for(ib = -nflt; ib <= nflt; ib++){
     double CPL2 = EwCpl2An(ia, IBsn, ib);
     if(CPL2 > sml){
//                                                            Born Term
       double Parton1 = fa0[ia];
       double Parton2 = fb0[ib];
       double Parton  = Parton1 * Parton2;
// jfo
       double TBorn   = CPL2 * Parton * xffac;
       //cout<<ia<<"  "<<ib<<"  "<<CPL2<<"  "<<Parton<<"  "<<TBorn<<"  "<<xa<<"  "<<xb<<"  "<<aMu<<endl;
       SIGLO = SIGLO + TBorn;
       if(IOrd != 1){
//                                                                  Q - Q Terms
//                                                   Term 1
         double QQ1 = 1. + (5.0 / 3.0) * pow(Pi, 2.0)
                    - (3.0 / 2.0) * log(xa * xb / (1.0 - xa) / (1.0 - xb))
                    + 2.0 * log(xa / (1.0 - xa)) * log(xb / (1.0 - xb));
         double TERM1  = (2.0 / 3.0) * CPL2 * QQ1 * Parton;
// jfo
         SG1QQ = SG1QQ + TERM1 * xffac;
         if(LM || LL){
// replace by non-adaptive
// **           TMP1 = ADZINT(FMSQ,ZRO,XA,AER,RER,ER1,IER1,1,1)
           double TMP1 = SMPSNF(FMSQ,0.00000000001,
                                  xa*0.99999999999,64, Er1, IER1);

// **           TMP2 = ADZINT(FMSQ,ZRO,XB,AER,RER,ER2,IER2,1,1)      
           double TMP2 = SMPSNF(FMSQ,0.00000000001,
                                  xb*0.99999999999,64, Er1, IER1);
           double TERM1M = ( TMP1+TMP2 ) * CPL2 * Parton;
           SG1QQ = SG1QQ + TERM1M;
         }
//                                                                Term 2
// **         TMP3 = ADZINT(QQ2,XA,ONE,AER,RER,ER,IER,1,1)

         double a5 = 1.0 - 0.00000000001*(1.0-xa);

         double TMP3 =
                SMPSNF(QQ2,xa + 0.00000000001*(a5-xa),
                           xa + 0.000001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ2,xa + 0.000001*(a5-xa),
                           xa + 0.00001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ2,xa + 0.00001*(a5-xa),
                           xa + 0.0001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ2,xa + 0.0001*(a5-xa),
                           xa + 0.001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ2,xa + 0.001*(a5-xa),
                           xa + 0.01*(a5-xa),8, ER, IER)
              + SMPSNF(QQ2,xa + 0.01*(a5-xa),
                           xa + 0.1*(a5-xa),16, ER, IER)
              + SMPSNF(QQ2,xa + 0.1*(a5-xa),a5,32, ER, IER);

         double TERM2 = (2./3.) * CPL2 * TMP3 * fb0[ib];
         SG1QQ = SG1QQ + TERM2;
//                                                                Term 3
// **         TMP4 = ADZINT(QQ3,XB,ONE,AER,RER,ER,IER,1,1)

         a5 = 1.0 - 0.00000000001*(1.0-xb);

         double TMP4 =
                SMPSNF(QQ3,xb + 0.00000000001*(a5-xb),
                           xb + 0.000001*(a5-xb),4, ER, IER)
              + SMPSNF(QQ3,xb + 0.000001*(a5-xb),
                           xb + 0.00001*(a5-xb),4, ER, IER)
              + SMPSNF(QQ3,xb + 0.00001*(a5-xb),
                           xb + 0.0001*(a5-xb),4, ER, IER)
              + SMPSNF(QQ3,xb + 0.0001*(a5-xb),
                           xb + 0.001*(a5-xb),4, ER, IER)
              + SMPSNF(QQ3,xb + 0.001*(a5-xb),
                           xb + 0.01*(a5-xb),8, ER, IER)
              + SMPSNF(QQ3,xb + 0.01*(a5-xb),
                           xb + 0.1*(a5-xb),16, ER, IER)
              + SMPSNF(QQ3,xb + 0.1*(a5-xb),a5,32, ER, IER);

         double TERM3 = (2./3.) * CPL2 * fa0[ia] * TMP4;
         SG1QQ = SG1QQ + TERM3;
//                                                                Term 4
// **         TMP5 = ADZINT(QQ4A,XA,ONE,AER,RER,ER,IER,1,1)

         a5 = 1.0 - 0.0000000001*(1.0-xa);

         double TMP5 =
                SMPSNF(QQ4A,xa + 0.0000000001*(a5-xa),
                            xa + 0.0000001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ4A,xa + 0.0000001*(a5-xa),
                            xa + 0.000001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ4A,xa + 0.000001*(a5-xa),
                            xa + 0.00001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ4A,xa + 0.00001*(a5-xa),
                            xa + 0.0001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ4A,xa + 0.0001*(a5-xa),
                            xa + 0.001*(a5-xa),4, ER, IER)
              + SMPSNF(QQ4A,xa + 0.001*(a5-xa),
                            xa + 0.01*(a5-xa),4, ER, IER)
              + SMPSNF(QQ4A,xa + 0.01*(a5-xa),
                            xa + 0.1*(a5-xa),8, ER, IER)
              + SMPSNF(QQ4A,xa + 0.1*(a5-xa),a5,16, ER, IER);

         double TERM4 = (4./3.) * CPL2 * TMP5;
         SG1QQ = SG1QQ + TERM4;
       }
     }
   }
 }

//                                               ...............Gluon-Quark Part
//
//Lai 4/15/10: adjust the lower limit treatment for adzint to avoid instability
 if(IOrd != 1){
   ia = 0;
   for(ib = -nflt; ib <= nflt; ib++){
     if(ib != 0){
       double CPL2 = EwCpl2Cn(ib, IBsn);
       if(CPL2 > sml){
//                                                              Term 1
// **                TMP6 = ADZINT(GQ1,XA,ONE,AER,RER,ER,IER,1,1)

         double a5 = 1.0 - 0.0000000001*(1.0-xa);

         double TMP6 =
                SMPSNF(GQ1,xa + 0.0000000001*(a5-xa),
                           xa + 0.000001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ1,xa + 0.000001*(a5-xa),
                           xa + 0.00001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ1,xa + 0.00001*(a5-xa),
                           xa + 0.0001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ1,xa + 0.0001*(a5-xa),
                           xa + 0.001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ1,xa + 0.001*(a5-xa),
                           xa + 0.01*(a5-xa),4, ER, IER)
              + SMPSNF(GQ1,xa + 0.01*(a5-xa),
                           xa + 0.1*(a5-xa),8, ER, IER)
              + SMPSNF(GQ1,xa + 0.1*(a5-xa),a5,16, ER, IER);

         double TERM5 = (1./2.) * CPL2 * TMP6 * fb0[ib];
// jfo
         SG1GQ = SG1GQ + TERM5;
//                                                               Term 2
// **                TMP7 = ADZINT(GQ2A,XA,ONE,AER,RER,ER,IER,1,1)

         a5 = 1.0 - 0.00000000001*(1.0-xa);

         double TMP7 =
                SMPSNF(GQ2A,xa + 0.00000000001*(a5-xa),
                            xa + 0.00001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ2A,xa + 0.00001*(a5-xa),
                            xa + 0.0001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ2A,xa + 0.0001*(a5-xa),
                            xa + 0.001*(a5-xa),4, ER, IER)
              + SMPSNF(GQ2A,xa + 0.001*(a5-xa),
                            xa + 0.01*(a5-xa),4, ER, IER)
              + SMPSNF(GQ2A,xa + 0.01*(a5-xa),
                            xa + 0.1*(a5-xa),8, ER, IER)
              + SMPSNF(GQ2A,xa + 0.1*(a5-xa),a5,16, ER, IER);

         double TERM6  = (1./2.) * CPL2 * TMP7;
         SG1GQ = SG1GQ + TERM6;
       }
     }
   }

//                                            ..................Quark-Gluon Part
   ib = 0;
   for(ia = -nflt; ia <= nflt; ia++){
     if(ia != 0){
       double CPL2 = EwCpl2Cn(ia, IBsn);
//                                                              Term 1
// **             TMP8 = ADZINT(QG1,XB,ONE,AER,RER,ER,IER,1,1)

       double a5 = 1.0 - 0.0000000001*(1.0-xb);

       double TMP8 =
              SMPSNF(QG1,xb + 0.00000000001*(a5-xb),
                         xb + 0.000000001*(a5-xb),4, ER, IER)
            + SMPSNF(QG1,xb + 0.000000001*(a5-xb),
                         xb + 0.00000001*(a5-xb),4, ER, IER)
            + SMPSNF(QG1,xb + 0.00000001*(a5-xb),
                         xb + 0.0000001*(a5-xb),4, ER, IER)
            + SMPSNF(QG1,xb + 0.0000001*(a5-xb),
                         xb + 0.000001*(a5-xb),4, ER, IER)
            + SMPSNF(QG1,xb + 0.000001*(a5-xb),
                         xb + 0.00001*(a5-xb),4, ER, IER)
            + SMPSNF(QG1,xb + 0.00001*(a5-xb),
                         xb + 0.0001*(a5-xb),4, ER, IER)
            + SMPSNF(QG1,xb + 0.0001*(a5-xb),
                         xb + 0.001*(a5-xb),8, ER, IER)
            + SMPSNF(QG1,xb + 0.001*(a5-xb),
                         xb + 0.01*(a5-xb),16, ER, IER)
            + SMPSNF(QG1,xb + 0.01*(a5-xb),
                         xb + 0.1*(a5-xb),32, ER, IER)
            + SMPSNF(QG1,xb + 0.1*(a5-xb),a5,64, ER, IER);

       double TERM7  = .5 * CPL2 * TMP8 * fa0[ia];
// jfo
       SG1GQ = SG1GQ + TERM7;
//                                                                Term 2
// **             TMP9 = ADZINT(QG2A,XB,ONE,AER,RER,ER,IER,1,1)

       a5 = 1.0 - 0.00000000001*(1.0-xb);

       double TMP9 =
              SMPSNF(QG2A,xb + 0.00000000001*(a5-xb),
                          xb + 0.000001*(a5-xb),4, ER, IER)
            + SMPSNF(QG2A,xb + 0.000001*(a5-xb),
                          xb + 0.00001*(a5-xb),4, ER, IER)
            + SMPSNF(QG2A,xb + 0.00001*(a5-xb),
                          xb + 0.0001*(a5-xb),4, ER, IER)
            + SMPSNF(QG2A,xb + 0.0001*(a5-xb),
                          xb + 0.001*(a5-xb),4, ER, IER)
            + SMPSNF(QG2A,xb + 0.001*(a5-xb),
                          xb + 0.01*(a5-xb),8, ER, IER)
            + SMPSNF(QG2A,xb + 0.01*(a5-xb),
                          xb + 0.1*(a5-xb),16, ER, IER)
            + SMPSNF(QG2A,xb + 0.1*(a5-xb),a5,32, ER, IER);

// ----------------------------------------------------------------------------------------
//          nuse = intusz(xvec,fvec)
//          write(*,409) y, nuse
//409       format(1x,'VBPDY1(',f12.6,') TERM8 uses NADZINT=',I5)
//          do i = 1, nuse
//             if((i .le. 2) .or. 
//     >          (i .ge. nuse-1) .or. 
//     >          (mod(i,10) .eq. 5)) then
//             write(*,500) i,xvec(i),fvec(i)
//500          format(1x,'xvec(',i5,')=',f13.8,' fvec=',e12.5)
//             endif
//          enddo
// ----------------------------------------------------------------------------------------
       double TERM8  = .5 * CPL2 * TMP9;
       SG1GQ = SG1GQ + TERM8;
     }
   }
 }

//                                            ...........................Done
 double SIGNLO = SIGLO + GetAlphaS(aMu) / Pi * (SG1QQ + SG1GQ);
 if(IOrd == 1){
   Value = SIGLO;
 }
 else{
   Value = SIGNLO;
 }
 //cout<<SIGLO<<"  "<<SIGNLO<<"  "<<SG1QQ<<"  "<<SG1GQ<<endl;
 return Value;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Define Functions //


void CalcVBP::DefineFunctions_VBP()
{
 FMSQ = [&](double zz){
   double CF = 1.33333333333333;
   double TR = 0.5;

   double z = zz;
   if(fabs(1.0 - z) < 1e-15 || z < 1e-15){
     cout<<"Z out of range in FMSQ; Z = "<<z<<endl;
   }
   double xffac = 1.0;
   if(ixfx == 1) xffac = 1.0 / (xa + xb);

   double TMP = 0.0;
//                                 Add mu dependent part: essentially Pff of A-P
   if(LL) TMP = log(Q / aMu) * CF * (1. + z*z) / (1.0 - z);
//
//                                 Add DIS to MSbar part: essentially C2q Wilson
   if(LM) TMP = TMP + CF / 2. *
                   ( ( 1.+ z*z ) / ( 1. - z ) * log( z/(1. - z) )
                     + 3./2. / ( 1.- z ) - 3. - 2. * z );
// jfo      
   return TMP * xffac;
 };

 FMSG = [&](double zz){
   double CF = 1.33333333333333;
   double TR = 0.5;

   double z = zz;
   if(fabs(1.0 - z) < 1e-15 || z < 1e-15){
     cout<<"Z out of range in FMSG; Z = "<<z<<endl;
   }
   double xffac = 1.0;
   if(ixfx == 1) xffac = 1.0 / (xa + xb);

   double TMP = 0.0;
//                                 Add mu dependent part: essentially Pfg of A-P
   if(LL) TMP = log(aMu / Q) * TR * ( z * z + pow((1.0 - z), 2.0) );

//                                 Add DIS to MSbar part: essentially C2g Wilson
   if(LM) TMP = TMP + TR / 2.0 *
           ( ( z * z + pow((1.0 - z), 2.0) ) * ( log( z / (1.0 - z) ) + 1.0 )
             - 6.0 * z * ( 1.0 - z ) );

// jfo
   return TMP * xffac;
 };

 QQ2 = [&](double ta){
   double Value = 0.0;
   double FA = GetPDF(Nbm, ia, ta, aMu);

// jfo E866 xf mods
   double alfx = 2.*xa/(ta+xa);
   double xffac=1.0;
   if(ixfx == 1){
     alfx = (xa+xb)/(ta+xb);
     xffac=1./(xa+xb);
   }
   double F1  = (ta*ta + xa*xa) / (ta*ta)
              * log( alfx *(1.-xb) / xb ) * FA;
// jfo     >    * LOG( 2. * XA *(1.-XB) / XB / (TA + XA) ) * FA
   double F1S = 2. * log( (1.-xb) / xb )  * fa0[ia];

   Value = Value + ( F1 - F1S) / ( ta - xa );
//
   double F2  = (3./2.) * FA;
   double F2S = (3./2.) * fa0[ia];

   Value = Value + ( F2 - F2S) / (ta - xa);
//
   double F3 = ( - 2./ta - 3 * xa / (ta*ta) ) * FA;
   Value = Value + F3;
// jfo
   Value = Value*xffac;
//                            Add terms due to Rnorm scheme & scale corrections
   if(LM || LL){
     Value = Value - (3./2.) * (1./ta) * FMSQ(xa/ta)
            * (FA - fa0[ia] * xa / ta);
   }
// jfo  xffac adjusted as needed in fmsq
   return Value;
 };


 QQ3 = [&](double tb){
   double Value = 0.0;
   double FB = GetPDF(Ntg, ib, tb, aMu);

// jfo E866 xf mods
   double alfx = 2.0 * xb / (tb + xb);
   double xffac = 1.0;
   if(ixfx == 1){
     alfx = (xa+xb)/(tb+xa);
     xffac = 1.0/(xa+xb);
   }
   double F1  = (tb*tb + xb*xb) / (tb*tb) * log(alfx * (1.0 - xa) / xa ) * FB;
// jfo     >     * LOG( 2. * XB *(1.-XA) / XA / (TB + XB) ) * FB
   double F1S = 2.0 * log((1.0 - xa) / xa) * fb0[ib];
   Value = Value + ( F1 - F1S) / ( tb - xb );
//
   double F2  = (3./2.) * FB;
   double F2S = (3./2.) * fb0[ib];
   Value = Value + ( F2 - F2S) / (tb - xb);
//
   double F3 = ( - 2./tb - 3 * xb / (tb * tb) ) * FB;
   Value = Value + F3;
// jfo
   Value = Value * xffac;

//                   Factor 3/2 to compensate relative normalization  with above
   if(LM || LL){
     Value = Value - (3./2.) * (1./tb) * FMSQ(xb / tb) * (FB - fb0[ib] * xb/tb);
   }

   return Value;
 };

 GASTOT = [&](double ta, double tb, double xa, double xb, double TAU){
   double Value = 0.0;

   if(ixfx == 1){
     Value = (ta + tb) * (TAU * TAU + pow((ta * tb), 2.0)) / 2.0 / pow((ta * tb), 2.0) / (ta + xb) / (tb + xa);
   }
   else{
     Value = (TAU + ta * tb) * ( TAU * TAU + pow((ta * tb), 2.0)) / pow((ta * tb), 2.0) / (ta + xa) / (tb + xb);
   }

   return Value;
 };

 HASTOT = [&](double ta, double tb, double xa, double xb, double TAU){
   double Value = 0.0;

   if(ixfx == 1){
     Value = -1.0 / ta / tb / (ta + tb);
   }
   else{
     Value = -2.0 * TAU * ( TAU + ta * tb) / ta / tb / pow((ta * xb + tb * xa), 2.0);
   }

   return Value;
 };

 QQ4B = [&](double ttb){
   double Value = 0.0;

   double tb = ttb;

   double TAU = xa*xb;

   double FB = GetPDF(Ntg, ib, tb, aMu);

// jfo  E866 xf mods
   double xffac = 1.0;
   if(ixfx == 1){
     xffac = 1.0 / (xa + xb);
   }
// jfo
//      II = II + 1
//       If (II.eq.1) Print *, 'Tau, Xa, Ta, Xb, Tb, Fa, Fb  in QQ4B:'
//      If (II.le.200) Print '(1pE12.5, 6E12.5)', Tau,Xa,Ta,Xb,Tb,Fa,Fb      
   Value = 1.0 / (qq4_ta - xa) / (tb - xb) *
              (GASTOT(qq4_ta, tb, xa, xb, TAU) * qq4_fa * FB
              - ( pow((xa/qq4_ta), 2.0) + 1.0) / 2.0 * qq4_fa * fb0[ib] * xffac
              - ( pow((xb/tb), 2.0) + 1.0) / 2.0 * fa0[ia] * FB * xffac
              + fa0[ia] * fb0[ib] * xffac)
              + HASTOT(qq4_ta, tb, xa, xb, TAU) * qq4_fa * FB;

   return Value;
 };

 QQ4A = [&](double tta){
   double ER;
   int IER;

   double Value = 0.0;

   qq4_ta = tta;
   qq4_fa = GetPDF(Nbm, ia, qq4_ta, aMu);

   double a5 = 1.0 - 0.00000000001*(1.0-xb);

   Value =
           SMPSN2(QQ4B,xb + 0.00000000001*(a5-xb),
                       xb + 0.000001*(a5-xb),4, ER, IER)
         + SMPSN2(QQ4B,xb + 0.000001*(a5-xb),
                       xb + 0.00001*(a5-xb),4, ER, IER)
         + SMPSN2(QQ4B,xb + 0.00001*(a5-xb),
                       xb + 0.0001*(a5-xb),4, ER, IER)
         + SMPSN2(QQ4B,xb + 0.0001*(a5-xb),
                       xb + 0.001*(a5-xb),4, ER, IER)
         + SMPSN2(QQ4B,xb + 0.001*(a5-xb),
                       xb + 0.01*(a5-xb),8, ER, IER)
         + SMPSN2(QQ4B,xb + 0.01*(a5-xb),
                       xb + 0.1*(a5-xb),16, ER, IER)
         + SMPSN2(QQ4B,xb + 0.1*(a5-xb),a5,32, ER, IER);

   return Value;
 };

 GQ1 = [&](double ta){
   double Value = 0.0;

   if(ia != 0){
     cout<<"IA .NE. 0 in GQ1; IA = "<<ia<<endl;
   }
// jfo E866 xf mods

   double alfx = 2.0 * xa / (ta + xa);
   double xffac = 1.0;
   if(ixfx == 1){
     alfx = (xa+xb)/(ta+xb);
     xffac = 1.0/(xa+xb);
   }
//                                                   gluon distr.
   double FA = GetPDF(Nbm, ia, ta, aMu);
   double FACTOR = (xa * xa + pow((ta - xa), 2.0) ) / 2.0 / pow(ta, 3.0)
                 * log(alfx * (1.0 - xb ) / xb)
                 + 1.0 / 2.0 / ta
                 - 3.0 * xa * (ta - xa) / pow(ta, 3.0);
   FACTOR = FACTOR * xffac;
// jfo     >         * LOG( 2.* XA * (1. - XB ) / XB / ( TA + XA ) )
// jfo     >      + 1./ 2. / TA
// jfo     >      - 3. * XA * ( TA - XA ) / TA**3
   Value = FACTOR * FA;

//                     Factor 2 to compensate relative normalization  with above
// jfo xffac adjusted in fmsg as needed
   if(LM || LL){
      Value = Value - 2.0 * (1.0 / ta) * FMSG(xa / ta) * FA;
   }

   return Value;
 };

 QG1 = [&](double tb){
   double Value = 0.0;

   if(ib != 0){
     cout<<"IB .NE. 0 in QG1; IB = "<<ib<<endl;
   }
// jfo E866 xf mods

   double alfx = 2.0 * xb / (tb + xb);
   double xffac = 1.0;
   if(ixfx == 1){
     alfx = (xa+xb)/(tb+xa);
     xffac = 1.0/(xa+xb);
   }

   double FB = GetPDF(Ntg, ib, tb, aMu);
   double FACTOR = ( xb * xb + pow((tb - xb), 2.0) ) / 2.0 / pow(tb, 3.0)
                 * log( alfx * (1.0 - xa ) / xa )
                 + 1.0 / 2.0 / tb
                 - 3. * xb * ( tb - xb ) / pow(tb, 3.0);
   FACTOR = FACTOR * xffac;
// jfo     >         * LOG( 2.* XB * (1. - XA ) / XA / ( TB + XB ) )
// jfo     >      + 1./ 2. / TB
// jfo     >      - 3. * XB * ( TB - XB ) / TB**3
   Value = FACTOR * FB;

//                     Factor 2 to compensate relative normalization  with above
// jfo  xffac adjusted in fmsg as needed
   if(LM || LL){
     Value = Value - 2.0 * (1.0 / tb) * FMSG(xb / tb) * FB;
   }

   return Value;
 };

 GCSTOT = [&](double ta, double tb, double xa, double xb, double TAU){
   double Value = 0.0;

   if(ixfx == 1){
     Value = (TAU * TAU + pow((TAU - ta * tb), 2.0)) / 2.0 / pow(ta, 3.0) / pow(tb, 2.0) / (tb + xa);
   }
   else{
     Value = xb * ( TAU + ta * tb ) * ( pow(TAU, 2.0) +
                  pow((TAU - ta * tb), 2.0) )
                  / pow(ta, 3.0) / pow(tb, 2.0) / ( ta * xb + tb * xa ) / ( tb + xb );
   }

   return Value;
 };

 HCSTOT = [&](double ta, double tb, double xa, double xb, double TAU){
   double Value = 0.0;

   if(ixfx == 1){
     Value = (ta * (tb + xa) * (tb - xb) + 2.0 * TAU * (ta + tb)) / 2.0 / pow(ta, 2.0) / pow(tb, 2.0) / pow((ta + tb), 2.0);
   }
   else{
     Value =  TAU * (TAU + ta * tb )
                  * ( ta * pow(tb, 2.0) * xa + TAU *
                    ( ta * xb + 2.0 * tb * xa) )
                    / pow((ta * tb), 2.0) / pow((ta * xb + tb * xa), 3.0);
   }

   return Value;
 };

 GQ2B = [&](double ttb){
   gq2_tb = ttb;

   double xffac = 1.0;
   if(ixfx == 1){
     xffac = 1.0/(xa+xb);
   }
   double TAU = xa * xb;
   double FB = GetPDF(Ntg, ib, gq2_tb, aMu);
   double Value = 1.0 / (gq2_tb - xb) *
                  (GCSTOT(gq2_ta, gq2_tb, xa, xb, TAU) * FB
                - (xa * xa + pow((xa - gq2_ta), 2.0)) / pow(gq2_ta, 3.0) / 2.0 * fb0[ib] * xffac )
                + HCSTOT(gq2_ta, gq2_tb, xa, xb, TAU) * FB;

   return Value;
 };

 QG2B = [&](double tta){
   gq2_ta = tta;

   double xffac = 1.0;
   if(ixfx == 1){
     xffac = 1.0/(xa+xb);
   }
   double TAU = xa * xb;
   double FA = GetPDF(Nbm, ia, gq2_ta, aMu);
   double Value = 1.0 / (gq2_ta - xa) *
                  (GCSTOT(gq2_tb, gq2_ta, xb, xa, TAU) * FA
                - (xb * xb + pow((xb - gq2_tb), 2.0)) / pow(gq2_tb, 3.0) / 2.0 * fa0[ia] * xffac )
                + HCSTOT(gq2_tb, gq2_ta, xb, xa, TAU) * FA;

   return Value;
 };

 GQ2A = [&](double tta){
   double ER;
   int IER;

   gq2_ta = tta;

   double a5 = 1.0 - 0.00000000001*(1.0-xb);

   double TMP1 =
                 SMPSN2(GQ2B,xb + 0.00000000001*(a5-xb),
                             xb + 0.000001*(a5-xb),4, ER, IER)
               + SMPSN2(GQ2B,xb + 0.000001*(a5-xb),
                             xb + 0.00001*(a5-xb),4, ER, IER)
               + SMPSN2(GQ2B,xb + 0.00001*(a5-xb),
                             xb + 0.0001*(a5-xb),4, ER, IER)
               + SMPSN2(GQ2B,xb + 0.0001*(a5-xb),
                             xb + 0.001*(a5-xb),4, ER, IER)
               + SMPSN2(GQ2B,xb + 0.001*(a5-xb),
                             xb + 0.01*(a5-xb),4, ER, IER)
               + SMPSN2(GQ2B,xb + 0.01*(a5-xb),
                             xb + 0.1*(a5-xb),8, ER, IER)
               + SMPSN2(GQ2B,xb + 0.1*(a5-xb),a5,16, ER, IER);


   return GetPDF(Nbm, ia, gq2_ta, aMu) * TMP1;
 };

 QG2A = [&](double ttb){
   double ER;
   int IER;

   gq2_tb = ttb;

   double a5 = 1.0 - 0.0000000001*(1.0-xa);

   double TMP2 =
                 SMPSN2(QG2B,xa + 0.00000000001*(a5-xa),
                             xa + 0.000001*(a5-xa),4, ER, IER)
               + SMPSN2(QG2B,xa + 0.000001*(a5-xa),
                             xa + 0.00001*(a5-xa),4, ER, IER)
               + SMPSN2(QG2B,xa + 0.00001*(a5-xa),
                             xa + 0.0001*(a5-xa),4, ER, IER)
               + SMPSN2(QG2B,xa + 0.0001*(a5-xa),
                             xa + 0.001*(a5-xa),4, ER, IER)
               + SMPSN2(QG2B,xa + 0.001*(a5-xa),
                             xa + 0.01*(a5-xa),4, ER, IER)
               + SMPSN2(QG2B,xa + 0.01*(a5-xa),
                             xa + 0.1*(a5-xa),8, ER, IER)
               + SMPSN2(QG2B,xa + 0.1*(a5-xa),a5,16, ER, IER);


   return GetPDF(Ntg, ib, gq2_tb, aMu) * TMP2;
 };




 isDefineVBPFunctions = true;
}
