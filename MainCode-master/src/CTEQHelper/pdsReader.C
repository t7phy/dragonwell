#include "CTEQHelper/pdsReader.h"

pdsReader::pdsReader()
{
 MXPQX = (MXF+1+MaxVal) * MXQ * MXX;
 xvpow.resize(MXX + 1);

 fvec.resize(5);
 fij.resize(5);

 amass[1] = 0.001;
 amass[2] = 0.001;
 amass[3] = 0.200;
 amass[4] = 1.300;
 amass[5] = 4.750;
 amass[6] = 172.000;

 xpow = 1.0 / 3.0;
}

void pdsReader::Initialize(const char* name)
{
 pdf.open(name, std::ios::in);

 getline(pdf, FileLine);
 //std::cout<<FileLine<<std::endl;
 getline(pdf, FileLine);
 //std::cout<<FileLine<<std::endl;

 if(FileLine.find("ipk, Ordr") != std::string::npos){
   ipdsformat = 10;
   pdf >> ipk >> Dr >> Qalfa >> AlfaQ >> amass[1] >> amass[2] >> amass[3] >> amass[4] >> amass[5] >> amass[6];
   getline(pdf, FileLine);
   Iorder = Dr;

   getline(pdf, FileLine);
   //std::cout<<FileLine<<std::endl;
   if(FileLine.find("  IMASS") != std::string::npos){
     ipdsformat = 11;
     pdf >> aimass >> fswitch >> IPD0 >> IHDN >> IKNL >> Nfmx >> MxVal;
     getline(pdf, FileLine);
     Nfl = Nfmx;
   }
   else{
     pdf >> N0 >> N0 >> N0 >> Nfmx >> MxVal;
     getline(pdf, FileLine);
   }
 }
 else{
   ipdsformat = 6;
   pdf >> Dr >> fl >> Alambda >> amass[1] >> amass[2] >> amass[3] >> amass[4] >> amass[5] >> amass[6];
   getline(pdf, FileLine);
   Iorder = Dr;
   Nfl = fl;

   getline(pdf, FileLine);
   double dummy;
   pdf >> dummy >> dummy >> dummy >> Nfmx >> MxVal >> N0;
   getline(pdf, FileLine);
 }

 getline(pdf, FileLine);
 //std::cout<<FileLine<<std::endl;

 pdf >> NX >> NT >> JT >> NG >> NTL;
 getline(pdf, FileLine);

 if(NG > 0){
   for(int i = 1; i <= NG + 1; i++){
     getline(pdf, FileLine);
   }
 }

 getline(pdf, FileLine);
 //std::cout<<FileLine<<std::endl;

 if(ipdsformat >= 11){
   pdf >> QINI >> QMAX;
   qv.resize(NT + 1);
   TV.resize(NT + 1);
   AlsCTEQ.resize(NT + 1);
   for(int i = 0; i <= NT; i++){
     pdf >> qv.at(i) >> TV.at(i) >> AlsCTEQ.at(i);
   }
   getline(pdf, FileLine);
 }
 else{
   pdf >> QINI >> QMAX;
   qv.resize(NT + 1);
   TV.resize(NT + 1);
   AlsCTEQ.resize(NT + 1);
   for(int i = 0; i <= NT; i++){
     pdf >> qv.at(i) >> TV.at(i);
   }
   getline(pdf, FileLine);
 }

 qbase1 = qv.at(1) / exp(exp(TV.at(1)));
 qbase2 = qv.at(NT) / exp(exp(TV.at(NT)));

 if(fabs(qbase1 - qbase2) > 1e-5){
   std::cout<<"Readpds0: something wrong with qbase"<<std::endl;
   std::cout<<"qbase1, qbase2 = "<<qbase1<<" "<<qbase2<<std::endl;
   return;
 }
 else{
   qbase = (qbase1 + qbase2) / 2.0;
 }

 qbase = 0.1;// yfu test

 getline(pdf, FileLine);
 //std::cout<<FileLine<<std::endl;

 pdf >> XMIN >> aa;
 XV.resize(NX + 1);
 for(int i = 1; i <= NX; i++){
   pdf >> XV.at(i);
 }
 getline(pdf, FileLine);
 XV.at(0) = 0.0;

 Nblk = (NX + 1) * (NT + 1);
 Npts = Nblk * (Nfmx + 1 + MxVal);

 getline(pdf, FileLine);
 //std::cout<<FileLine<<std::endl;

 //UPD.resize(Npts + 1);
 UPD.resize(MXPQX + 1); // yfu 2025.9.7 don't forget initialization
 for(int i = Npts + 1; i < MXPQX + 1; i++){
   UPD.at(i) = 0.0;
 }
 //std::cout<<Npts+1<<std::endl;

 for(int i = 1; i <= Npts; i++){
   pdf >> UPD.at(i);
 }
 getline(pdf, FileLine);

 std::cout<<"Initialize PDF finished."<<std::endl;
 isetch = 1;
 ipdsset = 1;
}

void pdsReader::Initialize(int Nfmx, int MxVal, int NX, int NT, std::vector<double> XV, std::vector<double> qv, std::vector<double> TV, std::vector<double> AlsCTEQ, std::vector<double> UPD)
{
 this->Nfmx = Nfmx;
 this->MxVal = MxVal;

 this->NX = NX;
 this->NT = NT;

 this->XV = XV;
 this->qv = qv;
 this->TV = TV;
 this->AlsCTEQ = AlsCTEQ;
 this->UPD = UPD;

 this->QINI = qv.at(0);
 this->QMAX = qv.at(qv.size() - 1);

 qbase1 = qv.at(1) / exp(exp(TV.at(1)));
 qbase2 = qv.at(NT) / exp(exp(TV.at(NT)));

 if(fabs(qbase1 - qbase2) > 1e-5){
   std::cout<<"Readpds0: something wrong with qbase"<<std::endl;
   std::cout<<"qbase1, qbase2 = "<<qbase1<<" "<<qbase2<<std::endl;
   return;
 }
 else{
   qbase = (qbase1 + qbase2) / 2.0;
 }

 qbase = 0.1;// yfu test

 Nblk = (NX + 1) * (NT + 1);
 Npts = Nblk * (Nfmx + 1 + MxVal);

 //std::cout<<"Initialize PDF by clone finished."<<std::endl;
 isetch = 1;
 ipdsset = 1;
 ipdsformat = 11;

 AlfaQ = CT14Alphas(Qalfa);
}

void pdsReader::OutputPDF(const char* name)
{
 std::ofstream outPDF;
  outPDF.open(name);

 outPDF<<"PDF Table for Fit #: "<<name<<std::endl;
 outPDF<<"  ipk, Ordr, MZ, Alpha(MZ)        Qmass 1,  2,  3,         4,  5,  6"<<std::endl;
 outPDF<<"  "<<ipk;
 outPDF<<std::setw(5)<<std::fixed<<std::setprecision(0)<<Dr<<".";
 outPDF<<std::setw(8)<<std::fixed<<std::setprecision(4)<<Qalfa;
 outPDF<<std::setw(8)<<std::fixed<<std::setprecision(4)<<CT14Alphas(Qalfa);
 outPDF<<std::setw(9)<<std::fixed<<std::setprecision(3)<<amass[1];
 outPDF<<std::setw(9)<<std::fixed<<std::setprecision(3)<<amass[2];
 outPDF<<std::setw(9)<<std::fixed<<std::setprecision(3)<<amass[3];
 outPDF<<std::setw(9)<<std::fixed<<std::setprecision(3)<<amass[4];
 outPDF<<std::setw(9)<<std::fixed<<std::setprecision(3)<<amass[5];
 outPDF<<std::setw(9)<<std::fixed<<std::setprecision(3)<<amass[6]<<std::endl;
 outPDF<<"  IMASS, FSWITCH, IPD0, IHDN, IKNL, NfMx, Nfval"<<std::endl;
 outPDF<<"     "<<aimass;
 outPDF<<std::setw(11)<<std::fixed<<std::setprecision(4)<<fswitch;
 outPDF<<"     "<<IPD0<<"     "<<IHDN<<"     "<<IKNL<<"     "<<Nfmx<<"     "<<MxVal<<std::endl;
 outPDF<<"   NX,  NT,  JT,  NG, NTL(NG+1)"<<std::endl;
 outPDF<<"  "<<NX<<"   "<<NT<<"    "<<JT<<"    "<<NG<<"    "<<NTL<<std::endl;
 outPDF<<"QINI, QMAX, (QV0(I), TV0(I), ALPHAS(I), I =0, NT)"<<std::endl;
 outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<QINI;
 outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<QMAX<<std::endl;
 for(int i = 0; i <= NT; i++){
   outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<qv.at(i);
   outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<TV.at(i);
   outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<AlsCTEQ.at(i)<<std::endl;
 }
 outPDF<<"XMIN, XCR, (XV0(I), I =1, NX)"<<std::endl;
 outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<XMIN;
 outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<aa<<std::endl;
 for(int i = 1; i <= NX; i++){
   outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<XV.at(i);
   if(i % 6 == 0){
     outPDF<<std::endl;
   }
 }
 outPDF<<std::endl;
 outPDF<<"Parton Distribution Table:"<<std::endl;

 Nblk = (NX + 1) * (NT + 1);
 Npts = Nblk * (Nfmx + 1 + MxVal);
 for(int i = 1; i <= Npts; i++){
   outPDF<<std::setw(13)<<std::scientific<<std::uppercase<<std::setprecision(5)<<UPD.at(i);
   if(i % 6 == 0){
     outPDF<<std::endl;
   }
 }

 outPDF.close();
}

void pdsReader::CopyHeader(pdsReader* pdf)
{
 this->Nfmx = pdf->Nfmx;
 this->MxVal = pdf->MxVal;

 this->NX = pdf->NX;
 this->NT = pdf->NT;

 this->XV = pdf->XV;
 this->qv = pdf->qv;
 this->TV = pdf->TV;
 this->AlsCTEQ = pdf->AlsCTEQ;

 this->ipdsformat = pdf->ipdsformat;
 this->QINI = pdf->QINI;
 this->QMAX = pdf->QMAX;

 qbase1 = qv.at(1) / exp(exp(TV.at(1)));
 qbase2 = qv.at(NT) / exp(exp(TV.at(NT)));

 if(fabs(qbase1 - qbase2) > 1e-5){
   std::cout<<"Readpds0: something wrong with qbase"<<std::endl;
   std::cout<<"qbase1, qbase2 = "<<qbase1<<" "<<qbase2<<std::endl;
   return;
 }
 else{
   qbase = (qbase1 + qbase2) / 2.0;
 }

 qbase = 0.1;// yfu test

 Nblk = (NX + 1) * (NT + 1);
 Npts = Nblk * (Nfmx + 1 + MxVal);

 ipdsset = pdf->ipdsset;

 AlfaQ = CT14Alphas(Qalfa);
 //std::cout<<"Initialize the header of PDF file finished."<<std::endl;
}

void pdsReader::InputAlphaS(std::vector<double> AlsCTEQ)
{
 this->AlsCTEQ = AlsCTEQ;

 if(NT + 1 != AlsCTEQ.size()){
   std::cout<<"ERROR! Q grid doesn't match the AlphaS series!"<<std::endl;
 }

 AlfaQ = CT14Alphas(Qalfa);
}

void pdsReader::InputUPD(std::vector<double> UPD)
{
 this->UPD = UPD;

 //std::cout<<"Initialize PDF by clone finished."<<std::endl;
 isetch = 1;
 ipdsset = 1;
}

void pdsReader::FromLHAtoUPD(const char* PDFName, int PDFset)
{
#ifdef USE_LHAPDF
 LHAPDF::setPaths(getenv("LHAPDF_PDF_DIR"));//set PDF path
 LHAPDF::PDF* lha = LHAPDF::mkPDF(PDFName, PDFset);
#endif
 std::vector<double> pdf(13);

 std::vector<double> QVector = Input_Q;
 std::vector<double> xVector = Input_x;

 NT = QVector.size() - 1;
 NX = xVector.size() - 1;

 Nfmx = 5;
 MxVal = 5;

 int NfMx = Nfmx;

 Nblk = (NX + 1) * (NT + 1);
 Npts = Nblk * (Nfmx + 1 + MxVal);

 UPD.clear();
 UPD.resize(Npts + 1);

 int nRound = (NX + 1) * (NT + 1);
 int TotalFlavor = Nfmx + 1 + MxVal;
 for(int i = 1; i <= nRound; i++){
   int ix = (i - 1) % (NX + 1);
   int iq = ((i - ix - 1) / (NX + 1)) % (NT + 1);

#ifdef USE_LHAPDF
   for(int iflavor = -5; iflavor <= 5; iflavor++){
     pdf.at(iflavor + 6) = lha->xfxQ(iflavor, xVector.at(ix), QVector.at(iq));
   }
#endif

   if(fabs(xVector.at(ix)) > 1e-12){
     for(int iflv = -NfMx; iflv <= MxVal; iflv++){
       int LHAParton = iflv;
       if(iflv == 1) LHAParton = 2;
       else if(iflv == 2) LHAParton = 1;
       else if(iflv == -1) LHAParton = -2;
       else if(iflv == -2) LHAParton = -1;
       else LHAParton = iflv;

       UPD.at(i + (iflv + NfMx) * nRound) = pdf[LHAParton + 6] / xVector.at(ix);
     }
   }
   else{
     for(int iflv = -NfMx; iflv <= MxVal; iflv++){
       UPD.at(i + (iflv + NfMx) * nRound) = 0.0;
     }
   }

   for(int iflv = -NfMx; iflv <= MxVal; iflv++){
     if(UPD.at(i + (iflv + NfMx) * nRound) > 1e99){
       UPD.at(i + (iflv + NfMx) * nRound) = 0.0;
     }
   }
 }

 std::vector<double> TVector(QVector.size()), AlphaSVector(QVector.size());

 for(int i = 0; i < QVector.size(); i++){
   TVector.at(i) = log(log(QVector.at(i) / qbase));
#ifdef USE_LHAPDF
   AlphaSVector.at(i) = lha->alphasQ2(QVector.at(i) * QVector.at(i));
#endif
 }

 this->XV = xVector;
 this->qv = QVector;
 this->TV = TVector;
 this->AlsCTEQ = AlphaSVector;

 this->QINI = qv.at(0);
 this->QMAX = qv.at(qv.size() - 1);

 isetch = 1;
 ipdsset = 1;
 ipdsformat = 11;

 AlfaQ = CT14Alphas(Qalfa);
}

void pdsReader::l2pFullSet(const char* PDFName, int nSet)
{
// if(ipdsset != 1){
//   std::cout<<"CT14Pdf: the PDF table was not initialized"<<std::endl;
//   return;
// }

 char FileName[80];
 char num[3];

 for(int i = 0; i <= nSet; i++){
   FromLHAtoUPD(PDFName, i);
   std::strcpy(FileName, PDFName);
   std::strcat(FileName, ".");
   std::sprintf(num, "%02d", i);
   std::strcat(FileName, num);
   std::strcat(FileName, ".pds");
   OutputPDF(FileName);
 }

}

double pdsReader::CT14PDF(int iparton, double x, double Q)
{
 if(ipdsset != 1){
   std::cout<<"CT14Pdf: the PDF table was not initialized"<<std::endl;
   return 0.0;
 }

 if(x < 0.0 || (x - 1.0) > 1e-10){
   std::cout<<"X out of range in CT14Pdf: "<<x<<std::endl;
   return 0.0;
 }

 if(Q < 0.3){
   std::cout<<"Q out of range in CT14Pdf: "<<Q<<std::endl;
   return 0.0;
 }

 if(abs(iparton) > Nfmx){
   std::cout<<"Warning: Iparton out of range in CT14Pdf! "<<std::endl;
   std::cout<<"Iparton, MxFlvN0: "<<iparton<<" "<<Nfmx<<std::endl;
   return 0.0;
 }

 double PDF = PartonX12(iparton, x, Q);
 if(PDF < 0.0) PDF = 0.0;

 return PDF;
}

double pdsReader::PartonX12(int iparton, double xx, double QQ)
{
 if(isetch == 1){
   isetch = 0;

   xvpow.at(0) = 0.0;
   for(int i = 1; i <= NX; i++){
     xvpow.at(i) = pow(XV.at(i), xpow);
   }
 }
 else if((fabs(xx - X) < 1e-9) && (fabs(QQ - Q) < 1e-9)){
   //goto 99
 }

 this->X = xx;
 this->Q = QQ;
 tt = log(log(Q / qbase));

 JLX = -1;
 JU = NX + 1;

 while((JU - JLX) > 1){
   JM = (JU + JLX) / 2;
   if(this->X >= XV.at(JM)){
     JLX = JM;
   }
   else{
     JU = JM;
   }
 }

 if(JLX <= -1){
   std::cout<<"Severe error: x <= 0 in PartonX12! x = "<<this->X<<std::endl;
   return 0.0;
 }
 else if(JLX == 0){
   JX = 0;
 }
 else if(JLX <= NX - 2){
   JX = JLX - 1;
 }
 else if((JLX == NX - 1) || this->X < OneP){
   JX = JLX - 2;
 }
 else{
   std::cout<<"Severe error: x > 1 in PartonX12! x = "<<this->X<<std::endl;
   return 0.0;
 }

 ss = pow(this->X, xpow);

 double svec1 = 0.0;
 double svec2 = 0.0;
 double svec3 = 0.0;
 double svec4 = 0.0;
 double s12 = 0.0;
 double s13 = 0.0;
 double s24 = 0.0;
 double s34 = 0.0;
 double s1213 = 0.0;
 double s2434 = 0.0;
 double sdet = 0.0;
 double tmp = 0.0;
 if((JLX >= 2) && (JLX <= (NX - 2))){
   //initiation work for "interior bins": store the lattice points in s...
   svec1 = xvpow.at(JX);
   svec2 = xvpow.at(JX+1);
   svec3 = xvpow.at(JX+2);
   svec4 = xvpow.at(JX+3);

   s12 = svec1 - svec2;
   s13 = svec1 - svec3;
   s23 = svec2 - svec3;
   s24 = svec2 - svec4;
   s34 = svec3 - svec4;

   sy2 = ss - svec2;
   sy3 = ss - svec3;

   //constants needed for interpolating in s at fixed t lattice points...
   const1 = s13/s23;
   const2 = s12/s23;
   const3 = s34/s23;
   const4 = s24/s23;
   s1213 = s12 + s13;
   s2434 = s24 + s34;
   sdet = s12*s34 - s1213*s2434;
   tmp = sy2*sy3/sdet;
   const5 = (s34*sy2-s2434*sy3)*tmp/s12;
   const6 = (s1213*sy2-s12*sy3)*tmp/s34;

 }

//         --------------Now find lower end of interval containing Q, i.e.,
//                          get jq such that qv(jq) .le. q .le. qv(jq+1)...

 JLQ = -1;
 JU = NT + 1;

 while((JU - JLQ) > 1){
   JM = (JU + JLQ) / 2;
   if(tt >= TV.at(JM)){
     JLQ = JM;
   }
   else{
     JU = JM;
   }
 }

 if(JLQ <= 0){
   JQ = 0;
 }
 else if(JLQ <= NT - 2){
   JQ = JLQ - 1;
 }
 else{
   JQ = NT - 3;
 }

 double tvec1 = 0.0;
 double tvec2 = 0.0;
 double tvec3 = 0.0;
 double tvec4 = 0.0;
 double tmp1 = 0.0;
 double tmp2 = 0.0;
 double tdet = 0.0;
 if((JLQ >= 1) && (JLQ <= (NT - 2))){
   //store the lattice points in t...
   tvec1 = TV.at(JQ);
   tvec2 = TV.at(JQ+1);
   tvec3 = TV.at(JQ+2);
   tvec4 = TV.at(JQ+3);

   t12 = tvec1 - tvec2;
   t13 = tvec1 - tvec3;
   t23 = tvec2 - tvec3;
   t24 = tvec2 - tvec4;
   t34 = tvec3 - tvec4;

   ty2 = tt - tvec2;
   ty3 = tt - tvec3;

   tmp1 = t12 + t13;
   tmp2 = t24 + t34;

   tdet = t12*t34 - tmp1*tmp2;

   //std::cout<<std::fixed<<std::setprecision(16)<<"QQ,tt,tvec2,ty2, "<<QQ<<"  "<<tt<<"  "<<tvec2<<"  "<<ty2<<std::endl;
 }

//99

 int IP = 0;
 if(iparton > MxVal){
   IP = iparton * (-1);
 }
 else{
   IP = iparton;
 }

 int jtmp = ((IP + Nfmx)*(NT+1)+(JQ-1))*(NX+1)+JX+1;
 int J1 = 0;
 double Fx = 0.0;

 for(int i = 1; i <= nqvec; i++){
   J1 = jtmp + i * (NX + 1);

   if(JX == 0){
//                      For the first 4 x points, interpolate x^2*f(x,Q)
//                      This applies to the two lowest bins JLx = 0, 1
//            We can not put the JLx.eq.1 bin into the "interrior" section
//                           (as we do for q), since Upd(J1) is undefined.
     fij.at(1) = 0.0;
     fij.at(2) = UPD.at(J1 + 1) * pow(XV.at(1), 2.0);
     fij.at(3) = UPD.at(J1 + 2) * pow(XV.at(2), 2.0);
     fij.at(4) = UPD.at(J1 + 3) * pow(XV.at(3), 2.0);
//                 Use Polint which allows x to be anywhere w.r.t. the grid

     std::vector<double> tmp_xvpow = {xvpow.at(0), xvpow.at(1), xvpow.at(2), xvpow.at(3)};
     std::vector<double> tmp_fij = {fij.at(1), fij.at(2), fij.at(3), fij.at(4)};
     Polint4F(tmp_xvpow, tmp_fij, ss, Fx);
     tmp_xvpow.clear();
     tmp_fij.clear();

     if(this->X > 0.0) fvec.at(i) = Fx / pow(this->X, 2.0);
//                                              Pdf is undefined for x.eq.0
   }
   else if(JLX == (NX - 1)){
//                                                This is the highest x bin:
     std::vector<double> tmp_xvpow = {xvpow.at(NX - 3), xvpow.at(NX - 2), xvpow.at(NX - 1), xvpow.at(NX)};
     std::vector<double> tmp_UPD = {UPD.at(J1), UPD.at(J1 + 1), UPD.at(J1 + 2), UPD.at(J1 + 3)};
     Polint4F(tmp_xvpow, tmp_UPD, ss, Fx);
     tmp_xvpow.clear();
     tmp_UPD.clear();

     fvec.at(i) = Fx;

     //std::cout<<i<<" "<<fvec.at(i)<<std::endl;
   }
   else{
//                       for all interior points, use Jon's in-line function
//                              This applied to (JLx.Ge.2 .and. JLx.Le.Nx-2)
     double sf2 = UPD.at(J1 + 1);
     double sf3 = UPD.at(J1 + 2);

     double g1 =  sf2 * const1 - sf3 * const2;
     double g4 =  (-1.0) * sf2 * const3 + sf3 * const4;

     fvec.at(i) = (const5 * (UPD.at(J1) - g1) + const6 * (UPD.at(J1 + 3) - g4) + sf2 * sy3 - sf3 * sy2) / s23;

     //std::cout<<const5<<" "<<g1<<" "<<const6<<" "<<g4<<" "<<s23<<std::endl;
     //std::cout<<i<<" "<<fvec.at(i)<<std::endl;
   }
 }

//                                   We now have the four values Fvec(1:4)
//     interpolate in t...

 double ff = 0.0;

 if(JLQ <= 0){
//                         1st Q-bin, as well as extrapolation to lower Q
   std::vector<double> tmp_TV = {TV.at(0), TV.at(1), TV.at(2), TV.at(3)};
   std::vector<double> tmp_fvec = {fvec.at(1), fvec.at(2), fvec.at(3), fvec.at(4)};
   Polint4F(tmp_TV, tmp_fvec, tt, ff);
   tmp_TV.clear();
   tmp_fvec.clear();
 }
 else if(JLQ >= NT - 1){
//                         Last Q-bin, as well as extrapolation to higher Q
   std::vector<double> tmp_TV = {TV.at(NT - 3), TV.at(NT - 2), TV.at(NT - 1), TV.at(NT)};
   std::vector<double> tmp_fvec = {fvec.at(1), fvec.at(2), fvec.at(3), fvec.at(4)};
   Polint4F (tmp_TV, tmp_fvec, tt, ff);
   tmp_TV.clear();
   tmp_fvec.clear();
 }
 else{
//                         Interrior bins : (JLq.GE.1 .and. JLq.LE.Nt-2)
//       which include JLq.Eq.1 and JLq.Eq.Nt-2, since Upd is defined for
//                         the full range QV(0:Nt)  (in contrast to XV)
   double tf2 = fvec.at(2);
   double tf3 = fvec.at(3);

   double g1 = ( tf2 * t13 - tf3 * t12) / t23;
   double g4 = ( (-1.0) * tf2 * t34 + tf3 * t24) / t23;

   double h00 = ((t34 * ty2 - tmp2 * ty3) * (fvec.at(1) - g1) / t12 + (tmp1 * ty2 - t12 * ty3) * (fvec.at(4) - g4) / t34);

   ff = (h00 * ty2 * ty3 / tdet + tf2 * ty3 - tf3 * ty2) / t23;

   //if(xx >= 0.002003333333 && xx <= 0.002003333334 && QQ <= 7.8 && QQ >= 7.7 && iparton == 5){
   //  std::cout<<h00<<" "<<ty2<<" "<<ty3<<" "<<tdet<<" "<<tf2<<" "<<ty3<<" "<<tf3<<" "<<ty2<<" "<<t23<<std::endl;
   //}
 }

 return ff;
}

double pdsReader::CT14Alphas(double QQ)
{
 if(ipdsset != 1){
   std::cout<<"CT14Alphas: the PDF table was not initialized"<<std::endl;
   return 0.0;
 }

 if(ipdsformat < 11){
   std::cout<<"STOP in CT14alphas: the PDF table file has an older format"<<std::endl;
   std::cout<<"and does not include the table of QCD coupling values."<<std::endl;
   std::cout<<"You can still compute the PDFs, but do not call"<<std::endl;
   std::cout<<"the CT14alphas function for the interpolation of alpha_s."<<std::endl;
   return 0.0;
 }

 double Q = QQ;
 double tt = log(log(Q / qbase));

 JLQ = -1;
 JU = NT + 1;
 while(JU - JLQ > 1){
   JM = (JU + JLQ) / 2;
   if(tt >= TV.at(JM)){
     JLQ = JM;
   }
   else{
     JU = JM;
   }
 }

 if(JLQ <= 0){
   JQ = 0;
 }
 else if(JLQ <= NT - 2){
   JQ = JLQ - 1;
 }
 else{
   JQ = NT - 3;
 }

 double Alsout = 0.0;

 std::vector<double> tmp_TV = {TV.at(JQ), TV.at(JQ + 1), TV.at(JQ + 2), TV.at(JQ + 3)};
 std::vector<double> tmp_AlsCTEQ = {AlsCTEQ.at(JQ), AlsCTEQ.at(JQ + 1), AlsCTEQ.at(JQ + 2), AlsCTEQ.at(JQ + 3)};
 Polint4F(tmp_TV, tmp_AlsCTEQ, tt, Alsout);
 tmp_TV.clear();
 tmp_AlsCTEQ.clear();

 return Alsout;
}

void pdsReader::Polint4F(std::vector<double> XA, std::vector<double> YA, double X, double& Y)
{
 double H1 = XA.at(0) - X;
 double H2 = XA.at(1) - X;
 double H3 = XA.at(2) - X;
 double H4 = XA.at(3) - X;

 double W = YA.at(1) - YA.at(0);
 double DEN = W / (H1 - H2);
 double D1 = H2 * DEN;
 double C1 = H1 * DEN;

 W = YA.at(2) - YA.at(1);
 DEN = W / (H2 - H3);
 double D2 = H3 * DEN;
 double C2 = H2 * DEN;

 W = YA.at(3) - YA.at(2);
 DEN = W / (H3 - H4);
 double D3 = H4 * DEN;
 double C3 = H3 * DEN;

 W = C2 - D1;
 DEN = W / (H1 - H3);
 double CD1 = H3 * DEN;
 double CC1 = H1 * DEN;

 W = C3 - D2;
 DEN = W / (H2 - H4);
 double CD2 = H4 * DEN;
 double CC2 = H2 * DEN;

 W = CC2 - CD1;
 DEN = W / (H1 - H4);
 double DD1 = H4 * DEN;
 double DC1 = H1 * DEN;

 if((H3 + H4) < 0.0){
   Y = YA.at(3) + D3 + CD2 + DD1;
 }
 else if((H2 + H3) < 0.0){
   Y = YA.at(2) + D2 + CD1 + DC1;
 }
 else if((H1 + H2) < 0.0){
   Y = YA.at(1) + C2 + CD1 + DC1;
 }
 else{
   Y = YA.at(0) + C1 + CC1 + DC1;
 }

}

bool pdsReader::CheckGridConsistency(pdsReader* pdf)
{
 bool isConsistency = true;

 if(this->Nfmx != pdf->Nfmx){
   isConsistency = false;
   return isConsistency;
 }

 if(this->MxVal != pdf->MxVal){
   isConsistency = false;
   return isConsistency;
 }

 if(this->qv.size() != pdf->qv.size()){
   isConsistency = false;
   return isConsistency;
 }

 if(this->XV.size() != pdf->XV.size()){
   isConsistency = false;
   return isConsistency;
 }

 for(int i = 0; i < qv.size(); i++){
   if(fabs(this->qv.at(i) - pdf->qv.at(i)) > 1e-20){
     isConsistency = false;
     break;
   }
 }

 if(!isConsistency) return isConsistency;

 for(int i = 0; i < XV.size(); i++){
   if(fabs(this->XV.at(i) - pdf->XV.at(i)) > 1e-20){
     isConsistency = false;
     break;
   }
 }

 return isConsistency;
}

pdsReader* pdsReader::Average(std::vector<pdsReader *> PDFs)
{
 pdsReader* outputPDF = new pdsReader();
 outputPDF->CopyHeader(this);
 outputPDF->InputAlphaS(this->AlsCTEQ);

 std::vector<double> AverageUPD = this->UPD;

 std::vector<std::vector<double>> UPDs(PDFs.size());

 // Check consistency for x grid, q grid, Nfmx, MxVal
 std::vector<bool> isSameGrid(PDFs.size());

 for(int ipdf = 0; ipdf < PDFs.size(); ipdf++){
   isSameGrid.at(ipdf) = CheckGridConsistency(PDFs.at(ipdf));
 }

 for(int ipdf = 0; ipdf < PDFs.size(); ipdf++){

   if(isSameGrid.at(ipdf)){
     UPDs.at(ipdf) = PDFs.at(ipdf)->UPD;
   }
   else{
     // Using interpolation to promise correct results if PDFs use different grid points
     int Npts = (NX + 1) * (NT + 1) * (Nfmx + 1 + MxVal);
     UPDs.at(ipdf).resize(MXPQX + 1);
     for(int i = Npts + 1; i < MXPQX + 1; i++){
       UPDs.at(ipdf).at(i) = 0.0;
     }
  
     int nRound = (NX + 1) * (NT + 1);
     int TotalFlavor = Nfmx + 1 + MxVal;
     for(int i = 1; i <= nRound; i++){
       int ix = (i - 1) % (NX + 1);
       int iq = ((i - ix - 1) / (NX + 1)) % (NT + 1);
  
       if(fabs(XV.at(ix)) > 1e-12){
         for(int iflv = -Nfmx; iflv <= MxVal; iflv++){
           int LHAParton = iflv;
           if(iflv == 1) LHAParton = 2;
           else if(iflv == 2) LHAParton = 1;
           else if(iflv == -1) LHAParton = -2;
           else if(iflv == -2) LHAParton = -1;
           else LHAParton = iflv;
  
           UPDs.at(ipdf).at(i + (iflv + Nfmx) * nRound) = this->xfxQ(LHAParton, XV.at(ix), qv.at(iq)) / XV.at(ix);
         }
       }
       else{
         for(int iflv = -Nfmx; iflv <= MxVal; iflv++){
           UPDs.at(ipdf).at(i + (iflv + Nfmx) * nRound) = 0.0;
         }
       }
  
       for(int iflv = -Nfmx; iflv <= MxVal; iflv++){
         if(UPDs.at(ipdf).at(i + (iflv + Nfmx) * nRound) > 1e99){
           UPDs.at(ipdf).at(i + (iflv + Nfmx) * nRound) = 0.0;
         }
       }
     }
   }
 }

 for(int i = 0; i < UPD.size(); i++){
   for(int ipdf = 0; ipdf < PDFs.size(); ipdf++){
     UPD.at(i) += UPDs.at(ipdf).at(i);
     //UPD.at(i) = UPDs.at(ipdf).at(i); // for check
   }
   UPD.at(i) /= (1.0 + PDFs.size());
 }

 outputPDF->InputUPD(this->UPD);

 return outputPDF;
}

double pdsReader::xfxQ(int flavor, double x, double Q)
{
 //consistent notation with LHAPDF
 int CTParton = 0;
 if(flavor == 1) CTParton = 2;
 else if(flavor == 2) CTParton = 1;
 else if(flavor == -1) CTParton = -2;
 else if(flavor == -2) CTParton = -1;
 else CTParton = flavor;

 double Value = CT14PDF(CTParton, x, Q) * x;

 if(!std::isfinite(Value)) Value = 0.0;

 return Value;
}

double pdsReader::Getf(int flavor, double x, double Q)
{
 double Value = 0.0;

 if(fabs(flavor) <= 5) Value = xfxQ(flavor, x, muF * Q) / x;

 if(flavor == 6) Value = (xfxQ(2, x, muF * Q) / x) - (xfxQ(-2, x, muF * Q) / x);
 if(flavor == 7) Value = (xfxQ(1, x, muF * Q) / x) - (xfxQ(-1, x, muF * Q) / x);
 if(flavor == 8) Value = (xfxQ(3, x, muF * Q) / x) - (xfxQ(-3, x, muF * Q) / x);

 if(flavor == 9){//ubouv
   if(fabs((xfxQ(2, x, muF * Q) / x) - (xfxQ(-2, x, muF * Q) / x)) > 1e-20 ) Value = (xfxQ(-2, x, muF * Q) / x) / ((xfxQ(2, x, muF * Q) / x) - (xfxQ(-2, x, muF * Q) / x));
 }
 if(flavor == 10){//dbodv
   if(fabs((xfxQ(1, x, muF * Q) / x) - (xfxQ(-1, x, muF * Q) / x)) > 1e-20 ) Value = (xfxQ(-1, x, muF * Q) / x) / ((xfxQ(1, x, muF * Q) / x) - (xfxQ(-1, x, muF * Q) / x));
 }
 if(flavor == 11){//ubou
   if(fabs(xfxQ(2, x, muF * Q) / x) > 1e-20 ) Value = (xfxQ(-2, x, muF * Q) / x) / (xfxQ(2, x, muF * Q) / x);
 }
 if(flavor == 12){//dbod
   if(fabs(xfxQ(1, x, muF * Q) / x) > 1e-20 ) Value = (xfxQ(-1, x, muF * Q) / x) / (xfxQ(1, x, muF * Q) / x);
 }

 if(flavor == 13) Value = (xfxQ(0, x, muF * Q) / x) / 5.0;//gluon/5

 if(flavor == 14){//uod
   if(fabs(xfxQ(1, x, muF * Q) / x) > 1e-20 ) Value = (xfxQ(2, x, muF * Q) / x) / (xfxQ(1, x, muF * Q) / x);
 }

 if(flavor == 15){//ubodb
   if(fabs(xfxQ(-1, x, muF * Q) / x) > 1e-20 ) Value = (xfxQ(-2, x, muF * Q) / x) / (xfxQ(-1, x, muF * Q) / x);
 }

 if(flavor == 16){//uvodv
   if(fabs((xfxQ(1, x, muF * Q) / x) - (xfxQ(-1, x, muF * Q) / x)) > 1e-20 ) Value = ((xfxQ(2, x, muF * Q) / x) - (xfxQ(-2, x, muF * Q) / x)) / ((xfxQ(1, x, muF * Q) / x) - (xfxQ(-1, x, muF * Q) / x));
 }

 if(flavor == 17){//dbou
   if(fabs(xfxQ(2, x, muF * Q) / x) > 1e-20 ) Value = (xfxQ(-1, x, muF * Q) / x) / (xfxQ(2, x, muF * Q) / x);
 }

 if(flavor == 18){//ubod
   if(fabs(xfxQ(1, x, muF * Q) / x) > 1e-20 ) Value = (xfxQ(-2, x, muF * Q) / x) / (xfxQ(1, x, muF * Q) / x);
 }

 if(flavor == 19){//dboub
   if(fabs(xfxQ(-2, x, Q) / x) > 1e-20) Value = (xfxQ(-1, x, Q) / x) / (xfxQ(-2, x, Q) / x);
 }

 if(flavor == 20){//dou
   if(fabs(xfxQ(2, x, Q) / x) > 1e-20) Value = (xfxQ(1, x, Q) / x) / (xfxQ(2, x, Q) / x);
 }

 if(flavor == 21){//(s+sbar)/(ubar+dbar)
   double ssbr = xfxQ(3, x, muF * Q) / x + xfxQ(-3, x, muF * Q) / x;
   double udbr = xfxQ(-2, x, muF * Q) / x + xfxQ(-1, x, muF * Q) / x;
   if(fabs(udbr) < 1e-16) udbr = udbr / fabs(udbr) * 1e-16;
   Value = ssbr / udbr;
 }

 return Value;
}


