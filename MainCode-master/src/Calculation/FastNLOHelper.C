#include "Calculation/FastNLOHelper.h"

#ifdef USE_FNLO

FastNLOHelper::FastNLOHelper()
{
//   m_qcd = new QCDSet();
//   m_qcd->SetNfTotal(NfTotal);
//   m_qcd->SetPoleMasscbt(PoleMass(4), PoleMass(5), PoleMass(6));
//   m_qcd->SetAmhatf();
//   Amhat = m_qcd->Amhat;
}

void FastNLOHelper::InitialPDF(TString PDFName, int iSet)
{
#ifdef USE_LHAPDF
 m_PDF = LHAPDF::mkPDF(PDFName.Data(), iSet);
#endif

 PDFType = PDFTypeEnum::CT_LHAPDF;
}

#ifdef USE_HOPPET
void FastNLOHelper::InitialPDFbyHand(HoppetInterface* h)
{
 m_Hoppet = h;

 PDFType = PDFTypeEnum::CT_CTEQ;
}
#endif

void FastNLOHelper::InitialCTEQPDF(TString PDFFile)
{
 m_CTEQPDF = new pdsReader();
 m_CTEQPDF->Initialize(PDFFile);

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

void FastNLOHelper::InitialCTEQPDF(pdsReader* pdf)
{
 if(m_CTEQPDF) delete m_CTEQPDF;

 m_CTEQPDF = new pdsReader();
 m_CTEQPDF->CopyHeader(pdf);
 m_CTEQPDF->InputAlphaS(pdf->AlsCTEQ);
 m_CTEQPDF->InputUPD(pdf->UPD);

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

vector<double> FastNLOHelper::GetXFX(double x, double muf) const
{
 vector<double> xfx(13);

 if(PDFType == PDFTypeEnum::CT_LHAPDF){
#ifdef USE_LHAPDF
   xfx.at(0  + 6) = m_PDF->xfxQ(0, x, muf);//gluon
   if(muf > Amhat(6)) xfx.at(-6 + 6) = m_PDF->xfxQ(-6, x, muf);//tbar
   if(muf > Amhat(5)) xfx.at(-5 + 6) = m_PDF->xfxQ(-5, x, muf);//bbar
   if(muf > Amhat(4)) xfx.at(-4 + 6) = m_PDF->xfxQ(-4, x, muf);//cbar
   xfx.at(-3 + 6) = m_PDF->xfxQ(-3, x, muf);//sbar
   xfx.at(-2 + 6) = m_PDF->xfxQ(-2, x, muf);//ubar
   xfx.at(-1 + 6) = m_PDF->xfxQ(-1, x, muf);//dbar
   xfx.at(1  + 6) = m_PDF->xfxQ(1, x, muf);//d
   xfx.at(2  + 6) = m_PDF->xfxQ(2, x, muf);//u
   xfx.at(3  + 6) = m_PDF->xfxQ(3, x, muf);//s
   if(muf > Amhat(4)) xfx.at(4  + 6) = m_PDF->xfxQ(4, x, muf);//c
   if(muf > Amhat(5)) xfx.at(5  + 6) = m_PDF->xfxQ(5, x, muf);//b
   if(muf > Amhat(6)) xfx.at(6  + 6) = m_PDF->xfxQ(6, x, muf);//t

#endif
 }

 if(PDFType == PDFTypeEnum::CT_CTEQ){
   double pdf[13];
#ifdef USE_HOPPET
   m_Hoppet->Evolve(x, muf, pdf);
#endif

   xfx.at(0  + 6) = pdf[0  + 6];//gluon
   if(muf > Amhat(6)) xfx.at(-6 + 6) = pdf[-6 + 6];//tbar
   if(muf > Amhat(5)) xfx.at(-5 + 6) = pdf[-5 + 6];//bbar
   if(muf > Amhat(4)) xfx.at(-4 + 6) = pdf[-4 + 6];//cbar
   xfx.at(-3 + 6) = pdf[-3 + 6];//sbar
   xfx.at(-2 + 6) = pdf[-2 + 6];//ubar
   xfx.at(-1 + 6) = pdf[-1 + 6];//dbar
   xfx.at(1  + 6) = pdf[1  + 6];//d
   xfx.at(2  + 6) = pdf[2  + 6];//u
   xfx.at(3  + 6) = pdf[3  + 6];//s
   if(muf > Amhat(4)) xfx.at(4  + 6) = pdf[4  + 6];//c
   if(muf > Amhat(5)) xfx.at(5  + 6) = pdf[5  + 6];//b
   if(muf > Amhat(6)) xfx.at(6  + 6) = pdf[6  + 6];//t

 }

 if(PDFType == PDFTypeEnum::CT_CTEQTable){
   xfx.at(0  + 6) = m_CTEQPDF->xfxQ(0, x, muf);//gluon
   if(muf > Amhat(6)) xfx.at(-6 + 6) = m_CTEQPDF->xfxQ(-6, x, muf);//tbar
   if(muf > Amhat(5)) xfx.at(-5 + 6) = m_CTEQPDF->xfxQ(-5, x, muf);//bbar
   if(muf > Amhat(4)) xfx.at(-4 + 6) = m_CTEQPDF->xfxQ(-4, x, muf);//cbar
   xfx.at(-3 + 6) = m_CTEQPDF->xfxQ(-3, x, muf);//sbar
   xfx.at(-2 + 6) = m_CTEQPDF->xfxQ(-2, x, muf);//ubar
   xfx.at(-1 + 6) = m_CTEQPDF->xfxQ(-1, x, muf);//dbar
   xfx.at(1  + 6) = m_CTEQPDF->xfxQ(1, x, muf);//d
   xfx.at(2  + 6) = m_CTEQPDF->xfxQ(2, x, muf);//u
   xfx.at(3  + 6) = m_CTEQPDF->xfxQ(3, x, muf);//s
   if(muf > Amhat(4)) xfx.at(4  + 6) = m_CTEQPDF->xfxQ(4, x, muf);//c
   if(muf > Amhat(5)) xfx.at(5  + 6) = m_CTEQPDF->xfxQ(5, x, muf);//b
   if(muf > Amhat(6)) xfx.at(6  + 6) = m_CTEQPDF->xfxQ(6, x, muf);//t
 }

 return xfx;
}

double FastNLOHelper::EvolveAlphas(double Q) const
{
 double Result = 0.0;

 if(PDFType == PDFTypeEnum::CT_LHAPDF){
#ifdef USE_LHAPDF
   Result = m_PDF->alphasQ2(Q*Q);
#endif
 }

 if(PDFType == PDFTypeEnum::CT_CTEQ){
#ifdef USE_HOPPET
   Result = m_Hoppet->EvolveAlphaS(Q);
#endif
 }

 if(PDFType == PDFTypeEnum::CT_CTEQTable){
   Result = m_CTEQPDF->CT14Alphas(Q);
 }

 return Result;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void FastNLOHelper::FT2007CC(TString FileName, double mur, double muf, int iprintflag, FortranArray2D<double> &xsect, TString subType)
{
 xsect.resize(1, NBINTOTMAX, 1, 3);

 int ixmur = 0, ixmuf = 0;
 for(int i = 1; i <= nscalevar; i++){
   if(fabs(mur / murscale(i) - 1.0) < 1e-10) ixmur = i;
   if(fabs(muf / mufscale(i) - 1.0) < 1e-10) ixmuf = i;
 }

 for(int nbin = 1; nbin <= nbintot; nbin++){
   for(int l = 1; l <= nord; l++){
     for(int m = 1; m <= nsubproc + 1; m++){
       result(nbin, m, l) = 0.0;
     }
     xsect(nbin, l) = 0.0;
   }
 }

 FT2007GP(mufscale(ixmuf));
 FT2007MT(mur, ixmuf);

// ----------------- final touches ------------------------------------
// - sum subprocesses / fill result array / fill 'XSECT' array
 for(int nbin = 1; nbin <= nbintot; nbin++){
   for(int iord = 1; iord <= nord; iord++){
     result(nbin, nsubproc + 1, iord) = 0.0;
     xsect(nbin, iord) = 0.0;
     for(int m = 1; m <= nsubproc; m++){
       result(nbin, m, iord) = result(nbin, m, iord);
       result(nbin, nsubproc + 1, iord) = result(nbin, nsubproc + 1, iord) + result(nbin, m, iord);
     }
     xsect(nbin, iord) = result(nbin, nsubproc + 1, iord);
   }
 }

 if(subType == "cdf2jtCor2"){
 //pn12 Final formatting of the cross section
 //     In our CDF Run-2 experimental data file, the lowest PT bin
 //     (52-62 GeV) is not included
 //     Pass only the cross section values for the PT bins included
 //     in the data file
   FortranArray2D<double> saved_xsect = xsect;
   xsect.fill(0.0);
   nbin = 0;
   int nbin2 = 0;
   for(int i = 1; i <= nrapidity; i++){
     for(int j = 2; j <= npt(i); j++){ // start from 2 to skip the lowest PT bin
       nbin = nbin + 1;
       for(int k = 1; k <= 3; k++){
         xsect(nbin, k) = saved_xsect(nbin2 + j, k);
       }
     }                 // j
     nbin2 = nbin2 + npt(i);
   }
 }
}

void FastNLOHelper::FT2007RD(TString FileName)
{
 cout<<"Reading "<<FileName<<endl;

 int iseparator = 1234567890;
 ifstream infile;
  infile.open(FileName, ios::in);

 int i;
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
 infile >> itabversion;
 if(itabversion != 14000){
   cout<<"#     ==> this usercode works only for version 1.4"<<endl;
   cout<<"#     ==> please get updated usercode from"<<endl;
   cout<<"#         http://hepforge.cedar.ac.uk/fastnlo "<<endl;
   return;
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 infile >> ireaction;
 infile >> ECMS;
 infile >> ixsecunits;
 for(int ii = 1; ii <= 5; ii++){
   infile >> namelabel(ii);
 }
 infile >> iproc;
 infile >> ialgo;
 infile >> jetres1;
 infile >> jetres2;
 infile >> nord;
 for(int ii = 1; ii <= nord; ii++){
   infile >> npow(ii);
 }
 for(int ii = 1; ii <= nord; ii++){
   infile >> powlabel(ii);
   infile >> codelabel(ii);
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 for(int ii = 1; ii <= nord; ii++){
   infile >> nevt(ii);
 }
 infile >> nxtot;
 infile >> ixscheme;
 infile >> ipdfwgt;
 infile >> iref;
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 infile >> nbintot;
 infile >> ndimension;
 for(int ii = 1; ii <= ndimension; ii++){
   infile >> dimlabel(ii);
 }
 infile >> nrapidity;
 for(int ii = 1; ii <= nrapidity + 1; ii++){
   infile >> rapbin(ii);
 }
 for(int ii = 1; ii <= nrapidity; ii++){
   infile >> npt(ii);
 }
 for(int ii = 1; ii <= nrapidity; ii++){
   for(int jj = 1; jj <= npt(ii) + 1; jj++){
     infile >> ptbin(ii, jj);
   }
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 for(int ii = 1; ii <= nrapidity; ii++){
   for(int jj = 1; jj <= npt(ii); jj++){
     infile >> xlimit(ii, jj);
   }
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 infile >> scalelabel;
 infile >> nscalebin;
 for(int ii = 1; ii <= nrapidity; ii++){
   for(int jj = 1; jj <= npt(ii); jj++){
     for(int kk = 1; kk <= nscalebin; kk++){
       infile >> murval(ii, jj, kk);
     }
   }
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 for(int ii = 1; ii <= nrapidity; ii++){
   for(int jj = 1; jj <= npt(ii); jj++){
     for(int kk = 1; kk <= nscalebin; kk++){
       infile >> mufval(ii, jj, kk);
     }
   }
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 infile >> nscalevar;
 for(int ii = 1; ii <= nscalevar; ii++){
   infile >> murscale(ii);
 }
 for(int ii = 1; ii <= nscalevar; ii++){
   infile >> mufscale(ii);
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }
// -----------------------------------------------------------------------
 if(ireaction == 2 || ireaction == 3){
   nxsum = (nxtot * nxtot + nxtot) / 2;
   nsubproc = 7;
 }
 else if(ireaction == 1){
   nxsum = nxtot;
   nsubproc = 3;
 }
 nbin = 0;
 for(int ii = 1; ii <= nrapidity; ii++){
   for(int jj = 1; jj <= npt(ii); jj++){
     nbin = nbin + 1;
     for(int kk = 1; kk <= nxsum; kk++){
       for(int mm = 1; mm <= nsubproc; mm++){
         for(int nn = 1; nn <= 1 + nscalevar * (nord - 1); nn++){
           for(int ll = 1; ll <= nscalebin; ll++){
             infile >> array(nbin, kk, mm, nn, ll);
           }
         }
       }
     }
   }
 }
 infile >> i;
 if(i != iseparator){
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   cout<<">>>>>   fastNLO error in table format "<<endl;
   cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
   return;
 }

 cout<<"Read Table finish"<<endl;
}


void FastNLOHelper::FT2007GP(double muffactor)
{
 double x1, x2, xlim, hxlim, hx, muf, reweight;
 FortranArray1D<double> H{1, 10};
 FortranArray1D<double> newpdf{-6, 6};
 FortranArray2D<double> xpdf{1, NXMAX, -6, 6};

 nbin = 0;
 for(int i = 1; i <= nrapidity; i++){
   for(int j = 1; j <= npt(i); j++){
     nbin = nbin + 1;
     xlim = xlimit(i, j);
     if(ixscheme == 2){
       hxlim = -sqrt(-log10(xlim));
     }
     else if(ixscheme == 1){
       hxlim = log10(xlim);
     }
     else if(ixscheme == 3){
       hxlim = log10(xlim) + xlim - 1.0;
     }
     else{
       cout<<"fastNLO - IXSCHEME "<<ixscheme<<" not available"<<endl;
       return;
     }
     for(int p = 1; p <= nscalebin; p++){
       muf = mufval(i, j, p) * muffactor;

// get PDFs(-6:6) directly from interface, reweight, copy into linear array
       for(int k = 1; k <= nxtot; k++){ // loop over all x-values
         hx = hxlim * (1.0 - (double)(k - 1) / (double)(nxtot)); // compute x1-value
         if(ixscheme == 2){
           x1 = pow(10, (-hx * hx));  // best scheme: sqrt(log10(1/x)
         }
         else if(ixscheme == 1){
           x1 = pow(10, hx);      // simple log10(1/x)
         }
         else{
           cout<<"fastNLO - IXSCHEME "<<ixscheme<<" not available"<<endl;
           return;
         }
         FNPDF(x1, muf, newpdf);
         reweight = 1.0;
         if(ipdfwgt == 1){ // standard fastNLO reweighting
           reweight = sqrt(x1) / pow((1.0 - 0.99 * x1), 3.0);
         }
         else if(ipdfwgt == 0){ // no reweighting
           reweight = 1.0;
         }
         else{
           cout<<"fastNLO - reweighting scheme not available: "<<ipdfwgt<<endl;
           return;
         }
         for(int l = -6; l <= 6; l++){
           xpdf(k, l) = newpdf(l) * reweight;
         }
       }
// - now fill main PDF array - compute different lin. comb for diff sub-proc
       int nx = 0;
       for(int k = 1; k <= nxtot; k++){
         int nx2limit = k;
         if(ireaction == 1) nx2limit = 1;
         for(int l = 1; l <= nx2limit; l++){
           nx=nx + 1;
           FT2007PL(ireaction, k, l, xpdf, H);
           for(int m = 1; m <= nsubproc; m++){
             pdf(nbin, nx, m, p) = H(m);
           }
         }
       }
     }
   }
 }
}

void FastNLOHelper::FT2007PL(int ireact, int i, int j, FortranArray2D<double> XPDF, FortranArray1D<double> &H)
{
 FortranArray1D<double> Q1{1, 6};
 FortranArray1D<double> QB1{1, 6};
 FortranArray1D<double> Q2{1, 6};
 FortranArray1D<double> QB2{1, 6};

 double SumQ1, SumQB1, SumQ2, SumQB2;
 double G1, G2, S, A;
// --- for DIS ---
 if(ireaction == 1){
   H(1) = XPDF(i, 0);       // Gluon
   H(2) = 0.0;                          // Sigma
   H(3) = 0.0;                          // Delta
   for(int k = 1; k <= 6; k++){
     H(2) = H(2) + XPDF(i, k) + XPDF(i, -k);
   }
   for(int k = 1; k <= 5; ){
     H(3) = H(3) + (XPDF(i, k) + XPDF(i, -k) + 4.0 * (XPDF(i, k+1) + XPDF(i, -k-1))) / 9.0;
     k = k + 2;
   }
 }
// --- for hadron-hadron ---
 else if(ireact == 2 || ireact == 3){ // pp/ppbar
   SumQ1  = 0.0;
   SumQB1 = 0.0;
   SumQ2  = 0.0;
   SumQB2 = 0.0;
   for(int k = 1; k <= 6; k++){
     Q1(k)  = XPDF(i, k);  // read x1
     QB1(k) = XPDF(i, -k);
     SumQ1  = SumQ1  + Q1(k);
     SumQB1 = SumQB1 + QB1(k);
     Q2(k)  = XPDF(j, k);  // read x2
     QB2(k) = XPDF(j, -k);
     SumQ2  = SumQ2  + Q2(k);
     SumQB2 = SumQB2 + QB2(k);
   }
   G1     = XPDF(i, 0);
   G2     = XPDF(j, 0);
//  -  compute S,A
   S = 0.0;
   A = 0.0;
   for(int k = 1; k <= 6; k++){
     S = S + (Q1(k) * Q2(k)) + (QB1(k) * QB2(k));
     A = A + (Q1(k) * QB2(k)) + (QB1(k) * Q2(k));
   }
//  - compute seven combinations
   H(1) = G1 * G2;
   H(2) = (SumQ1 + SumQB1) * G2;
   H(3) = G1 * (SumQ2 + SumQB2);
//  - for pp
   if(ireact == 2){
     H(4) = SumQ1 * SumQ2 + SumQB1 * SumQB2 - S;
     H(5) = S;
     H(6) = A;
     H(7) = SumQ1 * SumQB2 + SumQB1 * SumQ2 - A;
   }
//  - for p-pbar: swap combinations 4<->7 and 5<->6
   else if(ireact == 3){
     H(7) = SumQ1 * SumQ2 + SumQB1 * SumQB2 - S;
     H(6) = S;
     H(5) = A;
     H(4) = SumQ1 * SumQB2 + SumQB1 * SumQ2 - A;
   }
 }
 else{
   cout<<"    ireaction = "<<ireact<<endl;
   cout<<" this reaction is not yet defined"<<endl;
   return;
 }
}

void FastNLOHelper::FT2007MT(double xmur, int ixmuf)
{
 FortranArray1D<int> iposition{1, 5};
 double PI = 3.14159265358979323846;
 int NF = 5, CA = 3;
 double CF = 4.0 / 3.0;
 double beta0 = (11.0 * CA - 2.0 * NF) / 3.0;
 double beta1 = 34.0 * CA * CA / 3.0 - 2.0 * NF * (CF + 5.0 * CA / 3.0);
 double mur, as;
 FortranArray1D<double> aspow{1, 5};
 double coeff;

// - get the absolute order in alpha_s of the LO contribution
 int jord = npow(1);
// - vary renormalization scale around the value used in orig. calculation
 double logmu = log(xmur / murscale(ixmuf)); // change w.r.t. orig. calculation
 double scfac  = (double)(jord) * beta0 * logmu;          // NLO contrib.
 double scfac2a = (double)(jord + 1) * beta0 * logmu;     // NNLO contrib.
 double scfac2b = (double)(jord * (jord + 1)) / 2.0 * beta0 * beta0 * logmu * logmu + (double)(jord) * beta1 / 2.0 * logmu;           // NNLO contrib. continued

// - MW:  we may save time if we make the mur-variation later
//        for the whole contribution - instead of doing it for
//        each array element.

// - position of scale/order in array
 iposition(1) = 1;
 iposition(2) = 1 + ixmuf + (2 - 2) * nscalevar;
 iposition(3) = 1 + ixmuf + (3 - 2) * nscalevar;

// - loop over coefficient array
 nbin = 0;                  // continuos numbering for the final array
 for(int i = 1; i <= nrapidity; i++){ // (Pseudo-)Rapidity Bins
   for(int j = 1; j <= npt(i); j++){ // ET/pT Bins
     nbin = nbin + 1;         // continuous bin No.
     for(int l = 1; l <= nscalebin; l++){ // loop over all scale bins
       mur = xmur * murval(i, j, l); // set the ren. scale ...
       as = OFNALPHAS(mur); //    ... and get alpha_s
       for(int iord = 1; iord <= nord; iord++){
         aspow(iord) = pow(as, npow(iord));
       }
       for(int k = 1; k <= nxsum; k++){ // loop over all x bins
         for(int m = 1; m <= nsubproc; m++){ // loop over subprocesses
           for(int iord = 1; iord <= nord; iord++){ // relative order: 1 LO  2 NLO  3 NNLO ...
             if(iord == 1){ // LO contribution
               coeff = array(nbin, k, m, iposition(1), l);
             }
             else if(iord == 2){ // NLO contributions
               coeff = array(nbin, k, m, iposition(2), l) + scfac * array(nbin, k, m, 1, l);
             }
             else if(iord == 3){ // 2-loop threshold corr.
//
//     - the following works only for "true" higher orders (NNLO)
//     -> not for 2-loop threshold corrections (N. Kidonakis, Jan 10, 2006)
//     coeff = 
//c     +                       array(nbin,k,m,(1+ixmuf+(iord-2)*nscalevar),l)
//     +                       array(nbin,k,m,iposition(3),l)
//     +                       + scfac2a*array(nbin,k,m,(1+ixmuf))
//     +                       + scfac2b*array(nbin,k,m,1) 
//     
//     ... therefore the NLLO-NLL contributions are only available for mu_r=mu_f
//     -           in other words: for  log(mur/muf)=0
               if(logmu == 0.0){
                 coeff = array(nbin, k, m, iposition(3), l);
               }
               else{
                 coeff = 0.0;
               }
             }

// - for 'standard' fastNLO tables 
             if(iref == 0 || i <= (nrapidity / 2)){
               result(nbin,m,iord) = result(nbin, m, iord)
                                   + coeff 
                                   * aspow(iord) // multiply w/ (alpha-s/2pi)**n
                                   * pdf(nbin, k, m, l); // multiply with PDFs
             }
// - for 'reference' fastNLO tables including PDF/alphas
// - only relevant for fastNLO authors -> for precision studies
             else{
               if(l == 1){ // reference is stored in scale bin#1
                 result(nbin, m, iord) = result(nbin, m, iord) + coeff;
               }
             }
           }           // iord perturbative order
         }             // l scale-bins
       }               // m subprocess
     }                 // k x-bin
   }                   // j pt
 }                     // i rapidity

}

void FastNLOHelper::FNPDF(double x, double Q, FortranArray1D<double> &newpdf)
{
 vector<double> xfx = GetXFX(x, Q);
 for(int i = -6; i <= 6; i++){
   newpdf(i) = xfx.at(i + 6);
 }
}

double FastNLOHelper::OFNALPHAS(double Q)
{
 return EvolveAlphas(Q) / 3.14159265359 / 2.0;
}

#endif
