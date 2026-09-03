#include "Calculation/QCDSet.h"

double QCDSet::GetPDF(int ihadron, int iparton, double x, double Q)
{
//pn11 Returns either the regular PDF for iparton=-6:6, or their
//     singlet and non-singlet combinations arising in NNLO evolution
//
//      iparton         PDF type
//        20             Singlet^+ and
//       -20             Singlet^- combinations:
//        Sigma_{+-} = Sum_{i=1}^{Nf} (q_i +- qbar_i)
//
//        21     : 20+nf     non-singlet q_i^+ and 
//       -(20+nf):-21       non-singlet q_i^- combinations:
//        q_i^{+-} = q_i +- qbar_i - Sigma^{+-}/Nf, i = 1:Nf
//
//        30     : Sum_{i=1}^{Nf} e_i^2 (q_i + qbar_i)
//
//========================================================================
// GroupName: Pdfs
// Description: user callable parton distribution functions
// ListOfFiles: pdf pdfh pdfp pdftst
//========================================================================
//========================================================================
//
// These callable parton distributions are, in order of generality:
//
//      FUNCTION Pdf (Ihadron, Iparton, X, Q, Ir)
//         It is now only a shell to make it compatible to existing 
//         programs calling the PDF function in this format.
//
//      FUNCTION PdfH (Ihadron, Iparton, X, Q)
//         This is mainly for Hadron targets other than the proton.
//
//      FUNCTION PdfP (LPRTN, XD, QD)
//         Parton distribution in proton.
//
// ========================================================================
 double Pdf = 0.0;

/* map<int, double> ei2 = { // 9*(frac. quark charge)^2
   {1, 4.0},
   {2, 1.0},
   {3, 1.0},
   {4, 4.0},
   {5, 1.0},
   {6, 4.0}
 };*/

 //cout<<ihadron<<"  "<<iparton<<"  "<<x<<"  "<<Q<<"  "<<endl;

 int nf = GetNfl(Q);  // the current number of active flavors
 int jparton = iparton;
 if(abs(jparton) <= nf){// return a "physical-flavor" PDF
   Pdf = GetPDFH(ihadron, jparton, x, Q); // for iparton=-6:6
 }
 else if(jparton == 30){// Sum_{i=1}^{Nf} e_i^2 (q_i + qbar_i)
   double sigma = 0.0;
   for(int i = 1; i <= nf; i++){
     sigma = sigma + (GetPDFH(ihadron, i, x, Q) + GetPDFH(ihadron, -i, x, Q)); //*ei2 we multiply by the charge outside
   }
   Pdf = sigma / 9.0;
 }
 else if(abs(jparton) >= 20 && abs(jparton) <= (20 + nf)){
                                           //return a (non-)singlet PDF
   int ipsign = jparton / abs(jparton);

   double sigma = 0.0;
   for(int i = 1; i <= nf; i++){
     sigma = sigma + GetPDFH(ihadron, i, x, Q) + ipsign * GetPDFH (ihadron, -i, x, Q);
   }

   if(abs(jparton) == 20){
     Pdf = sigma;
     return Pdf;
   }

   jparton = abs(jparton) - 20; //map jparton on 1:Nfl

   //Pdf = GetPDFH(ihadron, jparton, x, Q) + ipsign * GetPDFH(ihadron, -jparton, x, Q) - sigma / nf;//yfu: remind this place
   Pdf = GetPDFH(ihadron, jparton, x, Q) + ipsign * GetPDFH(ihadron, -nf, x, Q) - sigma / nf;//yfu: remind this place, this is consistent with the fortran code
 }
 else{
   cout<<"WARNING! Requested iparton exceeds Nfl: setting PDF=0.0"<<endl;
   cout<<"Iparton = "<<iparton<<endl;
   return 0.0;
 }

 return Pdf;
}

double QCDSet::GetPDFH(int ihadron, int iparton, double x, double Q)
{
//     -------------------------------------------------
//     Parton Distribution Functions inside Hadrons.
//
//     Revised 4/4/94 by HLL & WKT: 
//        PdfH retains its name and argument list for compatibility with all
//        existing programs which Call this function; PdfH switches between
//        target hadrons; 
//        PdfP is for proton target; it switches between different Iset's.
//
//     Ihadron = -1,  0,  1,  2,  3,  4,  5,  6 : 
//              pbar, n,  p,  D, Cu,  C, ~D, Fe 
//
//               5 is "isoscalar-corrected iron" hence = D
//
//         In all cases, adjust the Iparton label
//         to convert to the corresponding proton distribution which is
//         given in Function PdfP;
 double PdfH = 0.0;

 if(x <= 0.0 || (x - 1.0) >= 1e-10){
   cout<<"WARNING! X out of range in PdfH. x = "<<x<<endl;
   //cout<<"ihadron = "<<ihadron<<" iparton = "<<iparton<<" Q = "<<Q<<endl;
   return 0.0;
 }

//                   --- Conversion of  Ihadron  to proton distributions,
//                                     if necessary ---- 
 if(ihadron > 6 || ihadron < -1){
   cout<<"WARNING! Only Ihardon=-1,0,1,2,...,6 (pbar,n,p,D,*,) are active"<<endl;
   cout<<"ihadron = "<<ihadron<<endl;
   return 0.0;
 }

 int jp = abs(iparton);
 int Neff = GetNfl(Q);

// nfl(q) returns the number of `light' flavors at scale Q - effective
 if(jp > Neff){
//               if Jp > Neff, then set PdfH=0 and return
//         Call WARNI(IW, NWRT,
//     >    'Iparton out of range',
//     >    'Iparton', Iparton, -Neff,Neff,1)
   return 0.0;
 }

 if(jp == 1 || jp == 2){
//                                   Use Isospin symmetry n<->p  == u<->d
   int ipartner = 3 - jp;
   if(iparton < 0) ipartner = -ipartner;

   if(ihadron == 1) PdfH = GetPDFP(iparton, x, Q);
   else if(ihadron == -1) PdfH = GetPDFP(-iparton, x, Q);
   else if(ihadron == 0) PdfH = GetPDFP(ipartner, x, Q);
   else if(ihadron == 2 || ihadron == 4 || ihadron == 5) PdfH = (GetPDFP(iparton, x, Q) + GetPDFP(ipartner, x, Q)) / 2.0;
   else if(ihadron == 3) PdfH = ( 29.0 * GetPDFP(iparton, x, Q) + 35.0 * GetPDFP(ipartner, x, Q) ) / 64.0;
   else if(ihadron == 6) PdfH = ( 26.0 * GetPDFP(iparton, x, Q) + 30.0 * GetPDFP(ipartner, x, Q) ) / 56.0;
   else PdfH = 0.0;
 }
 else{
   PdfH = GetPDFP(iparton, x, Q);
 }

 return PdfH;
}

double QCDSet::GetPDFP(int iparton, double x, double Q)
{
 int LHAParton;
 if(iparton == 1) LHAParton = 2;
 else if(iparton == 2) LHAParton = 1;
 else if(iparton == -1) LHAParton = -2;
 else if(iparton == -2) LHAParton = -1;
 else LHAParton = iparton;

 if(x <= 0.0) return 0.0;

 double Value;

#ifdef USE_HOPPET
 if(PDFType == PDFTypeEnum::CT_CTEQ){
   double pdf[13];
   m_Hoppet->Evolve(x, Q, pdf);
   Value = pdf[LHAParton + 6] / x;
 }
#endif

#ifdef USE_LHAPDF
 if(PDFType == PDFTypeEnum::CT_LHAPDF){
   if(x >= 1.0) x = 1.0;
   Value = m_PDF->xfxQ(LHAParton, x, Q) / x;
 }
#endif

 if(PDFType == PDFTypeEnum::CT_CTEQTable){
   Value = m_CTEQPDF->xfxQ(LHAParton, x, Q) / x;
 }

 return Value;
}

