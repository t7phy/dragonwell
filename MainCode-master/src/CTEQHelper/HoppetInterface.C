#include "CTEQHelper/HoppetInterface.h"

PDFEvolve* Instance;

void PDF_init(const double &x, const double &Q, double *pdf)
{
  pdf[ 0+6] = x * Instance->GetPDFQ0(x, 0);
  pdf[ 3+6] = x * Instance->GetPDFQ0(x, 3);
  pdf[-3+6] = x * Instance->GetPDFQ0(x, -3);
  pdf[ 2+6] = x * Instance->GetPDFQ0(x, 1);
  pdf[-2+6] = x * Instance->GetPDFQ0(x, -1);
  pdf[ 1+6] = x * Instance->GetPDFQ0(x, 2);
  pdf[-1+6] = x * Instance->GetPDFQ0(x, -2);

  pdf[ 4+6] = 0.0;
  pdf[ 5+6] = 0.0;
  pdf[ 6+6] = 0.0;
  pdf[-4+6] = 0.0;
  pdf[-5+6] = 0.0;
  pdf[-6+6] = 0.0;
}

HoppetInterface::HoppetInterface()
{
 SetXArray();
 SetQArray();
}

void HoppetInterface::Initialize(PDFEvolve* p, double Q0)
{
 Instance = p;

 Qini = Q0;
 xmin = 1e-9;
 Qmin = 1.29;
 Qmax = 1e5;
 dy    = 0.2;
 nloop = EvolveOrder;

// ymax = log(1.0 / xmin) + 5.0;
 ymax = log(1.0 / xmin);
 dlnlnQ = dy / 4.0;
 order = -6;
 factscheme = 1;

#ifdef USE_HOPPET
 //hoppetStart(dy, nloop);
 hoppetStartExtended(ymax, dy, Qmin, Qmax, dlnlnQ, nloop, order, factscheme);
 hoppetSetPoleMassVFN(mc, mb, mt);
 hoppetEvolve(AsQ0, Q0_as, nloop, 1.0, PDF_init, Q0);
#endif

 EvolveType = EvolveEnum::Hoppet;
}

void HoppetInterface::Evolution(double x, double Q)
{
 double pdf[13];

#ifdef USE_HOPPET
 hoppetEval(x, Q, pdf);
#endif

 Instance->Setgluon(x, Q, pdf[ 0+6] / x);
 Instance->Setd    (x, Q, pdf[ 1+6] / x);
 Instance->Setdbar (x, Q, pdf[-1+6] / x);
 Instance->Setu    (x, Q, pdf[ 2+6] / x);
 Instance->Setubar (x, Q, pdf[-2+6] / x);
 Instance->Sets    (x, Q, pdf[ 3+6] / x);
 Instance->Setsbar (x, Q, pdf[-3+6] / x);
 Instance->Setc    (x, Q, pdf[ 4+6] / x);
 Instance->Setcbar (x, Q, pdf[-4+6] / x);
 Instance->Setb    (x, Q, pdf[ 5+6] / x);
 Instance->Setbbar (x, Q, pdf[-5+6] / x);

// hoppetDeleteAll();
}

void HoppetInterface::Evolve(double x, double Q, double* pdf)
{
#ifdef USE_HOPPET
 if(fabs(x) < 1e-12){
   for(int i = -5; i <= 5; i++){
     pdf[i + 6] = 0.0;
   }
   return;
 }

 if(log(1.0 / x) > ymax){
   for(int i = -5; i <= 5; i++){
     pdf[i + 6] = 0.0;
   }
   return;
 }

 hoppetEval(x, Q, pdf);

// for(int i = -5; i <= 5; i++){
//   cout<<"x = "<<x<<" Q = "<<Q<<" flavor = "<<i<<" pdf = "<<pdf[i + 6]<<endl;
// }

// make s = sbar
 //double s = pdf[ 3+6];
 //double sbar = pdf[ -3+6];
 //pdf[ 3+6] = (s + sbar) / 2.0;
 //pdf[-3+6] = (s + sbar) / 2.0;

#endif
}

double HoppetInterface::EvolveAlphaS(double Q)
{
 double alphas = 0.0;

 if(EvolveType == EvolveEnum::Hoppet){
   alphas = EvolveAlphaSHoppet(Q);
 }
 else if(EvolveType == EvolveEnum::APFELxx){
   alphas = EvolveAlphaSAPFELxx(Q);
 }
 else if(EvolveType == EvolveEnum::APFEL){
   alphas = EvolveAlphaSAPFEL(Q);
 }
 else if(EvolveType == EvolveEnum::InputUPD){
   alphas = m_cteqpdf->CT14Alphas(Q);
 }

 return alphas;
}

double HoppetInterface::EvolveAlphaSHoppet(double Q)
{
 double alphas = 0.0;
#ifdef USE_HOPPET
 alphas = hoppetAlphaS(Q);
#endif
 return alphas;
}

void HoppetInterface::InitializeAlphaS(double as, double q)
{
 Qini = 1.295;
 xmin = 1e-9;
 Qmin = 1.29;
 Qmax = 1e5;
 dy    = 0.2;
 nloop = AlphaSOrder;

 ymax = log(1.0 / xmin) + 5.0;
 dlnlnQ = dy / 4.0;
 order = -6;
 factscheme = 1;

#ifdef USE_HOPPET
 hoppetStartExtended(ymax, dy, Qmin, Qmax, dlnlnQ, nloop, order, factscheme);
 hoppetSetPoleMassVFN(mc, mb, mt);
 SetAlphaSQ0(as, q);
 hoppetPreEvolve(AsQ0, Q0_as, nloop, 1.0, Qini);

#endif

}

vector<double> HoppetInterface::ProduceUPD()
{
 vector<double> pdf(13);

 vector<double> UPD;

 // PUPD(ix, iq, ip) = UPD((ip + Nfmx)*(Nq+1)+iq)*(Nx+1)+ix+1)
 // Q: [0, nQ], x: [1, nX]

 int NT = QVector.size() - 1;
 int NX = xVector.size() - 1;
 int Npts = (NX + 1) * (NT + 1) * (NfMx + 1 + MxVal);
 UPD.resize(Npts + 1);

/*
 for(int i = 1; i <= Npts; i++){
   int ix = (i - 1) % (NX + 1);
   int iq = ((i - ix - 1) / (NX + 1)) % (NT + 1);
   int iflv = (i - (ix + 1) - iq * (NX + 1))/(NT + 1)/(NX + 1) - NfMx;

   cout<<i<<"  "<<ix<<"  "<<iq<<"  "<<iflv<<endl;

   int LHAParton = iflv;
   if(iflv == 1) LHAParton = 2;
   else if(iflv == 2) LHAParton = 1;
   else if(iflv == -1) LHAParton = -2;
   else if(iflv == -2) LHAParton = -1;
   else LHAParton = iflv;

   if(EvolveType == EvolveEnum::Hoppet){
     Evolve(xVector.at(ix), QVector.at(iq), &pdf[0]);
   }
   else if(EvolveType == EvolveEnum::APFELxx){
     EvolveAPFELxx(xVector.at(ix), QVector.at(iq), &pdf[0]);
   }
   else if(EvolveType == EvolveEnum::APFEL){
     EvolveAPFEL(xVector.at(ix), QVector.at(iq), &pdf[0]);
   }

   if(fabs(xVector.at(ix)) > 1e-12){
     UPD.at(i) = pdf[LHAParton + 6] / xVector.at(ix);
   }
   else{
     UPD.at(i) = 0.0;
   }

   if(UPD.at(i) > 1e99){
     UPD.at(i) = 0.0;
   }
 }
*/

 int nRound = (NX + 1) * (NT + 1);
 int TotalFlavor = NfMx + 1 + MxVal;
 for(int i = 1; i <= nRound; i++){
   int ix = (i - 1) % (NX + 1);
   int iq = ((i - ix - 1) / (NX + 1)) % (NT + 1);

   if(EvolveType == EvolveEnum::Hoppet){
     Evolve(xVector.at(ix), QVector.at(iq), &pdf[0]);
   }
   else if(EvolveType == EvolveEnum::APFELxx){
     EvolveAPFELxx(xVector.at(ix), QVector.at(iq), &pdf[0]);
   }
   else if(EvolveType == EvolveEnum::APFEL){
     EvolveAPFEL(xVector.at(ix), QVector.at(iq), &pdf[0]);
   }

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

 return UPD;
}

pdsReader* HoppetInterface::PrepareCTEQTable()
{
 pdsReader* pdf;

 vector<double> TVector(QVector.size()), AlphaSVector(QVector.size());

 for(int i = 0; i < QVector.size(); i++){
   TVector.at(i) = log(log(QVector.at(i) / qbase));
   AlphaSVector.at(i) = EvolveAlphaS(QVector.at(i));
 }

 vector<double> UPD = ProduceUPD();

 pdf = new pdsReader();
 pdf->Initialize(NfMx, MxVal, xVector.size() - 1, QVector.size() - 1, xVector, QVector, TVector, AlphaSVector, UPD);

 return pdf;
}

void HoppetInterface::OutputLHAPDFTable(TString name, int iSet)
{
 vector<double> pdf(13);

 TString PDFType;
 if(iSet == 0) PDFType = "central";
 else if(iSet != 0) PDFType = "error";

 TString PDFName;
 if(iSet < 10) PDFName = name + "_000" + iSet + ".dat";
 else if(iSet >= 10 && iSet < 100) PDFName = name + "_00" + iSet + ".dat";
 else if(iSet >= 100 && iSet < 1000) PDFName = name + "_0" + iSet + ".dat";
 else if(iSet >= 1000 && iSet < 10000) PDFName = name + "_" + iSet + ".dat";

 ofstream PDFTable(PDFName);
 ofstream InfoFile(name + ".info");

 vector<double> xVector = { 9.261360E-10,  1.131185E-09,  1.381633E-09,  1.687530E-09,  2.061154E-09,  2.517499E-09,  3.074880E-09,  3.755667E-09,  4.587182E-09,  5.602796E-09,  6.843271E-09,  8.358390E-09,
                            1.020896E-08,  1.246925E-08,  1.522998E-08,  1.860194E-08,  2.272046E-08,  2.775083E-08,  3.389494E-08,  4.139938E-08,  5.056531E-08,  6.176061E-08,  7.543458E-08,  9.213601E-08,
                            1.125352E-07,  1.374508E-07,  1.678828E-07,  2.050525E-07,  2.504516E-07,  3.059023E-07,  3.736299E-07,  4.563526E-07,  5.573904E-07,  6.807981E-07,  8.315287E-07,  1.015631E-06,
                            1.240495E-06,  1.515144E-06,  1.850601E-06,  2.260329E-06,  2.760773E-06,  3.372015E-06,  4.118589E-06,  5.030456E-06,  6.144212E-06,  7.504558E-06,  9.166088E-06,  1.119548E-05,
                            1.367420E-05,  1.670170E-05,  2.039950E-05,  2.491601E-05,  3.043248E-05,  3.717032E-05,  4.539993E-05,  5.545160E-05,  6.772874E-05,  8.272407E-05,  1.010394E-04,  1.234098E-04,
                            1.507331E-04,  1.841058E-04,  2.248673E-04,  2.746536E-04,  3.354626E-04,  4.097350E-04,  5.004514E-04,  6.112528E-04,  7.465858E-04,  9.118820E-04,  1.113775E-03,  1.360368E-03,
                            1.661557E-03,  2.029431E-03,  2.478752E-03,  3.027555E-03,  3.697864E-03,  4.516581E-03,  5.516564E-03,  6.737947E-03,  8.229747E-03,  1.005184E-02,  1.227734E-02,  1.499558E-02,
                            1.831564E-02,  2.237077E-02,  2.732372E-02,  3.337327E-02,  4.076220E-02,  4.978707E-02,  6.081006E-02,  7.427358E-02,  9.071795E-02,  1.108032E-01,  1.353353E-01,  1.446652E-01,
                            1.546383E-01,  1.652989E-01,  1.766944E-01,  1.888756E-01,  2.018965E-01,  2.158151E-01,  2.306932E-01,  2.465970E-01,  2.635971E-01,  2.817693E-01,  3.011942E-01,  3.219583E-01,
                            3.441538E-01,  3.678794E-01,  3.932407E-01,  4.203504E-01,  4.493290E-01,  4.803053E-01,  5.134171E-01,  5.488116E-01,  5.611440E-01,  5.737534E-01,  5.866462E-01,  5.998287E-01,
                            6.133075E-01,  6.270891E-01,  6.411804E-01,  6.555883E-01,  6.703200E-01,  6.853828E-01,  7.007840E-01,  7.165313E-01,  7.326325E-01,  7.490954E-01,  7.659283E-01,  7.831395E-01,
                            8.007374E-01,  8.187308E-01,  8.248179E-01,  8.309504E-01,  8.371284E-01,  8.433524E-01,  8.496227E-01,  8.559395E-01,  8.623034E-01,  8.687145E-01,  8.751733E-01,  8.816802E-01,
                            8.882354E-01,  8.948393E-01,  9.014924E-01,  9.081949E-01,  9.149472E-01,  9.217498E-01,  9.286029E-01,  9.355070E-01,  9.424624E-01,  9.494695E-01,  9.518168E-01,  9.541699E-01,
                            9.565287E-01,  9.588935E-01,  9.612640E-01,  9.636404E-01,  9.660227E-01,  9.684109E-01,  9.708050E-01,  9.732050E-01,  9.756110E-01,  9.780229E-01,  9.804407E-01,  9.828646E-01,
                            9.852944E-01,  9.877302E-01,  9.889504E-01,  9.901721E-01,  9.913953E-01,  9.926200E-01,  9.938462E-01,  9.950739E-01,  9.963031E-01,  9.975339E-01,  9.987662E-01,  1.000000E+00};


 PDFTable<<"PdfType: "<<PDFType<<endl;
 PDFTable<<"Format: lhagrid1"<<endl;

 PDFTable<<"---"<<endl;
 for(int i = 0; i < xVector.size(); i++){
   PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(i);
 }
 PDFTable<<endl;

 vector<double> Qsub1 = {1.295000E+00,  1.296656E+00,  1.298323E+00,  1.300000E+00 - 1e-15};
 for(int i = 0; i < Qsub1.size(); i++){
   PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << Qsub1.at(i);
 }
 PDFTable<<endl;
 PDFTable<<"            -5            -4            -3            -2            -1            21             1             2             3             4             5"<<endl;
 for(int ix = 0; ix < xVector.size(); ix++){
   for(int iq = 0; iq < Qsub1.size(); iq++){
     if(EvolveType == EvolveEnum::Hoppet){
       Evolve(xVector.at(ix), Qsub1.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::APFELxx){
       EvolveAPFELxx(xVector.at(ix), Qsub1.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::APFEL){
       EvolveAPFEL(xVector.at(ix), Qsub1.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::InputUPD){
       for(int iflv = -5; iflv <= 5; iflv++){
         pdf[iflv + 6] = m_cteqpdf->xfxQ(iflv, xVector.at(ix), Qsub1.at(iq));
       }
     }

     for(int iflavor = -5; iflavor <= 5; iflavor++){
       PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << pdf[iflavor + 6];
     }
     PDFTable<<endl;
   }
 }

 PDFTable<<"---"<<endl;
 for(int i = 0; i < xVector.size(); i++){
   PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(i);
 }
 PDFTable<<endl;

 vector<double> Qsub2 = {1.300000E+00 + 1e-15,  1.368242E+00,  1.454507E+00,  1.564755E+00,  1.707516E+00,  1.895298E+00,  2.146972E+00,  2.491923E+00,  2.977567E+00,  3.683559E+00,  4.750000E+00 - 1e-15};
 for(int i = 0; i < Qsub2.size(); i++){
   PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << Qsub2.at(i);
 }
 PDFTable<<endl;
 PDFTable<<"            -5            -4            -3            -2            -1            21             1             2             3             4             5"<<endl;
 for(int ix = 0; ix < xVector.size(); ix++){
   for(int iq = 0; iq < Qsub2.size(); iq++){
     if(EvolveType == EvolveEnum::Hoppet){
       Evolve(xVector.at(ix), Qsub2.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::APFELxx){
       EvolveAPFELxx(xVector.at(ix), Qsub2.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::APFEL){
       EvolveAPFEL(xVector.at(ix), Qsub2.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::InputUPD){
       for(int iflv = -5; iflv <= 5; iflv++){
         pdf[iflv + 6] = m_cteqpdf->xfxQ(iflv, xVector.at(ix), Qsub2.at(iq));
       }
     }

     for(int iflavor = -5; iflavor <= 5; iflavor++){
       PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << pdf[iflavor + 6];
     }
     PDFTable<<endl;
   }
 }

 PDFTable<<"---"<<endl;
 for(int i = 0; i < xVector.size(); i++){
   PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(i);
 }
 PDFTable<<endl;

 vector<double> Qsub3 = {  4.750000E+00 + 1e-15,  5.061854E+00,  5.408199E+00,  5.793870E+00,  6.224518E+00,  6.706769E+00,  7.248423E+00,  7.858693E+00,  8.548497E+00,  9.330833E+00,  1.022123E+01,
                                                  1.123831E+01,  1.240454E+01,  1.374706E+01,  1.529891E+01,  1.710042E+01,  1.920110E+01,  2.166202E+01,  2.455891E+01,  2.798620E+01,  3.206225E+01,
                                                  3.693635E+01,  4.279787E+01,  4.988856E+01,  5.851898E+01,  6.909086E+01,  8.212734E+01,  9.831471E+01,  1.185599E+02,  1.440707E+02,  1.764687E+02,
                                                  2.179489E+02,  2.715086E+02,  3.412769E+02,  4.329957E+02,  5.547267E+02,  7.179028E+02,  9.389066E+02,  1.241469E+03,  1.660352E+03,  2.247073E+03,
                                                  3.078914E+03,  4.273266E+03,  6.010798E+03,  8.573365E+03,  1.240693E+04,  1.822752E+04,  2.720251E+04,  4.126543E+04,  6.367217E+04,  1.000000E+05};
 for(int i = 0; i < Qsub3.size(); i++){
   PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << Qsub3.at(i);
 }
 PDFTable<<endl;
 PDFTable<<"            -5            -4            -3            -2            -1            21             1             2             3             4             5"<<endl;
 for(int ix = 0; ix < xVector.size(); ix++){
   for(int iq = 0; iq < Qsub3.size(); iq++){
     if(EvolveType == EvolveEnum::Hoppet){
       Evolve(xVector.at(ix), Qsub3.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::APFELxx){
       EvolveAPFELxx(xVector.at(ix), Qsub3.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::APFEL){
       EvolveAPFEL(xVector.at(ix), Qsub3.at(iq), &pdf[0]);
     }
     else if(EvolveType == EvolveEnum::InputUPD){
       for(int iflv = -5; iflv <= 5; iflv++){
         pdf[iflv + 6] = m_cteqpdf->xfxQ(iflv, xVector.at(ix), Qsub3.at(iq));
       }
     }

     for(int iflavor = -5; iflavor <= 5; iflavor++){
       PDFTable << setw(14) << *right << uppercase << scientific << setprecision(6) << pdf[iflavor + 6];
     }
     PDFTable<<endl;
   }
 }

 PDFTable<<"---"<<endl;

 InfoFile<<"SetDesc: \'\'"<<endl;
 InfoFile<<"Authors:"<<endl;
 InfoFile<<"Reference: arXiv:22xx.xxxxx"<<endl;
 InfoFile<<"Format: lhagrid1"<<endl;
 InfoFile<<"DataVersion:     1"<<endl;
 InfoFile<<"NumMembers:    59"<<endl;
 InfoFile<<"SetIndex: 14000"<<endl;
 InfoFile<<"Flavors: [-5, -4, -3, -2, -1, 21, 1, 2, 3, 4, 5]"<<endl;
 InfoFile<<"OrderQCD:     2"<<endl;
 InfoFile<<"FlavorScheme: variable"<<endl;
 InfoFile<<"NumFlavors: 5"<<endl;
 InfoFile<<"ErrorType: hessian"<<endl;
 InfoFile<<"ErrorConfLevel: 90"<<endl;
 InfoFile<<"ForcePositive: 0"<<endl;
 InfoFile<<"XMin:";
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(0) << endl;
 InfoFile<<"XMax:";
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(xVector.size() - 1) << endl;
 InfoFile<<"QMin:";
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << Qsub1.at(0) << endl;
 InfoFile<<"QMax:";
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << Qsub3.at(Qsub3.size() - 1) << endl;
 InfoFile<<"MZ:  91.1876"<<endl;
 InfoFile<<"MUp:   0.0010"<<endl;
 InfoFile<<"MDown:   0.0010"<<endl;
 InfoFile<<"MStrange:   0.2000"<<endl;
 InfoFile<<"MCharm:   1.3000"<<endl;
 InfoFile<<"MBottom:   4.7500"<<endl;
 InfoFile<<"MTop: 172.000"<<endl;
 InfoFile<<"AlphaS_MZ:  ";
 if(EvolveType == EvolveEnum::InputUPD){
   InfoFile<<fixed<<setprecision(6)<<m_cteqpdf->AlfaQ<<endl;
 }
 else{
   InfoFile<<fixed<<setprecision(6)<<EvolveAlphaS(Q0_as)<<endl;
 }
 InfoFile<<"AlphaS_OrderQCD:     2"<<endl;
 InfoFile<<"AlphaS_Type: ipol"<<endl;

 vector<double> QVector;
 for(int i = 0; i < Qsub1.size(); i++){
   if(i != Qsub1.size() - 1) QVector.push_back(Qsub1.at(i));
   else QVector.push_back(Qsub1.at(i) + 1e-15);
 }

 for(int i = 1; i < Qsub2.size(); i++){
   if(i != Qsub2.size() - 1 && i != 0) QVector.push_back(Qsub2.at(i));
   else if(i == 0) QVector.push_back(Qsub2.at(i) - 1e-15);
   else QVector.push_back(Qsub2.at(i) + 1e-15);
 }

 for(int i = 1; i < Qsub3.size(); i++){
   if(i != 0) QVector.push_back(Qsub3.at(i));
   else QVector.push_back(Qsub3.at(i) - 1e-15);
 }

 vector<double> AlphaSVector(QVector.size());
 for(int i = 0; i < QVector.size(); i++){
   AlphaSVector.at(i) = EvolveAlphaS(QVector.at(i));
 }

 InfoFile<<"AlphaS_Qs: [";
 InfoFile << setw(13) << *right << uppercase << scientific << setprecision(6) << QVector.at(0) << ",";
 for(int i = 1; i < QVector.size() - 1; i++){
   InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << QVector.at(i) << ",";
 }
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << QVector.at(QVector.size() - 1) << "]" << endl;

 InfoFile<<"AlphaS_Vals: [";
 InfoFile << setw(13) << *right << uppercase << scientific << setprecision(6) << AlphaSVector.at(0) << ",";
 for(int i = 1; i < AlphaSVector.size() - 1; i++){
   InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << AlphaSVector.at(i) << ",";
 }
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << AlphaSVector.at(AlphaSVector.size() - 1) << "]" << endl;

 InfoFile<<"xs: [";
 InfoFile << setw(13) << *right << uppercase << scientific << setprecision(6) << xVector.at(0) << ",";
 for(int i = 1; i < xVector.size() - 1; i++){
   InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(i) << ",";
 }
 InfoFile << setw(14) << *right << uppercase << scientific << setprecision(6) << xVector.at(xVector.size() - 1) << "]" << endl;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void HoppetInterface::SetQArray()
{
/* double lambda_eff_default = 0.1;
 double lambda_eff = (Qmin * 0.5 < lambda_eff_default) ? Qmin * 0.5 : lambda_eff_default;

 double lnlnQ_max = log(log(Qmax / lambda_eff));
 double lnlnQ_min = log(log(Qmin / lambda_eff));
 int nQ = (int)((lnlnQ_max - lnlnQ_min) / dlnlnQ) + 1;
 dlnlnQ = (lnlnQ_max - lnlnQ_min) / nQ;

 vector<double> QVector(nQ), TVector(nQ);

 cout<<"Qmax = "<<Qmax<<" Qmin = "<<Qmin<<endl;
 cout<<"nQ = "<<nQ<<" lnlnQ_max = "<<lnlnQ_max<<" lnlnQ_min = "<<lnlnQ_min<<" dlnlnQ = "<<dlnlnQ<<endl;
 for(int i = 0; i < nQ; i++){
   TVector.at(i) = lnlnQ_min + i * dlnlnQ;
   QVector.at(i) = exp(exp(TVector.at(i))) * lambda_eff;
   cout<<QVector.at(i)<<"  "<<TVector.at(i)<<endl;
 }
*/

 QVector = {
  1.29500E+00,  
  1.29875E+00,  
  1.46461E+00,  
  1.65924E+00,  
  1.89067E+00,  
  2.16749E+00,  
  2.50067E+00,  
  2.90430E+00,  
  3.39664E+00,  
  4.00145E+00,  
  4.75000E+00,  
  5.76715E+00,  
  7.07072E+00,  
  8.75819E+00,  
  1.09657E+01,  
  1.38856E+01,  
  1.77929E+01,  
  2.30855E+01,  
  3.03471E+01,  
  4.04448E+01,  
  5.46864E+01,  
  7.50724E+01,  
  1.04712E+02,  
  1.48517E+02,  
  2.14380E+02,  
  3.15212E+02,  
  4.72537E+02,  
  7.22946E+02,  
  1.12995E+03,  
  1.80616E+03,  
  2.95593E+03,  
  4.95886E+03,  
  8.53814E+03,  
  1.51079E+04,  
  2.75107E+04,  
  5.16275E+04,  
  1.00000E+05,  
    
 };

}

void HoppetInterface::SetXArray()
{
/* xVector.resize(nx + 1);

 xVector.at(0) = 0.0;

 double dz = 1.0 / (double)(nx - 1);

 for(int i = 1; i <= nx - 1; i++){
   double z = dz * (i - 1);
   double x = xfrmz(z);

   xVector.at(i) = x;
 }
 xVector.at(1) = xmin;
 xVector.at(nx) = 1.0;

 for(int i = 1; i <= nx; i++){
   cout<<"i = "<<i<<"  x = "<<xVector.at(i)<<endl;
 }
*/
 xVector = {0.0,
  9.26136E-10,  1.13119E-09,  1.38163E-09,  1.68753E-09,  2.06115E-09,  2.51750E-09,
  3.07488E-09,  3.75567E-09,  4.58718E-09,  5.60280E-09,  6.84327E-09,  8.35839E-09,
  1.02090E-08,  1.24693E-08,  1.52300E-08,  1.86019E-08,  2.27205E-08,  2.77508E-08,
  3.38949E-08,  4.13994E-08,  5.05653E-08,  6.17606E-08,  7.54346E-08,  9.21360E-08,
  1.12535E-07,  1.37451E-07,  1.67883E-07,  2.05052E-07,  2.50452E-07,  3.05902E-07,
  3.73630E-07,  4.56353E-07,  5.57390E-07,  6.80798E-07,  8.31529E-07,  1.01563E-06,
  1.24050E-06,  1.51514E-06,  1.85060E-06,  2.26033E-06,  2.76077E-06,  3.37202E-06,
  4.11859E-06,  5.03046E-06,  6.14421E-06,  7.50456E-06,  9.16609E-06,  1.11955E-05,
  1.36742E-05,  1.67017E-05,  2.03995E-05,  2.49160E-05,  3.04325E-05,  3.71703E-05,
  4.53999E-05,  5.01747E-05,  5.54516E-05,  6.12835E-05,  6.77287E-05,  7.48518E-05,
  8.27241E-05,  9.14242E-05,  1.01039E-04,  1.11666E-04,  1.23410E-04,  1.36389E-04,
  1.50733E-04,  1.66586E-04,  1.84106E-04,  2.03468E-04,  2.24867E-04,  2.48517E-04,
  2.74654E-04,  3.03539E-04,  3.35463E-04,  3.70744E-04,  4.09735E-04,  4.52827E-04,
  5.00451E-04,  5.53084E-04,  6.11253E-04,  6.75539E-04,  7.46586E-04,  8.25105E-04,
  9.11882E-04,  1.00779E-03,  1.11378E-03,  1.23091E-03,  1.36037E-03,  1.50344E-03,
  1.66156E-03,  1.83630E-03,  2.02943E-03,  2.24287E-03,  2.47875E-03,  2.73944E-03,
  3.02755E-03,  3.34597E-03,  3.69786E-03,  4.08677E-03,  4.51658E-03,  4.99159E-03,
  5.51656E-03,  6.09675E-03,  6.73795E-03,  7.44658E-03,  8.22975E-03,  9.09528E-03,
  1.00518E-02,  1.11090E-02,  1.22773E-02,  1.35686E-02,  1.49956E-02,  1.65727E-02,
  1.83156E-02,  2.02419E-02,  2.23708E-02,  2.47235E-02,  2.73237E-02,  3.01974E-02,
  3.33733E-02,  3.68832E-02,  4.07622E-02,  4.50492E-02,  4.97871E-02,  5.50232E-02,
  6.08101E-02,  6.72055E-02,  7.42736E-02,  8.20850E-02,  9.07180E-02,  1.00259E-01,
  1.10803E-01,  1.22456E-01,  1.35335E-01,  1.42274E-01,  1.49569E-01,  1.57237E-01,
  1.65299E-01,  1.73774E-01,  1.82684E-01,  1.92050E-01,  2.01897E-01,  2.12248E-01,
  2.23130E-01,  2.34570E-01,  2.46597E-01,  2.59240E-01,  2.72532E-01,  2.86505E-01,
  3.01194E-01,  3.16637E-01,  3.32871E-01,  3.49938E-01,  3.67879E-01,  3.86741E-01,
  4.06570E-01,  4.27415E-01,  4.49329E-01,  4.72367E-01,  4.96585E-01,  5.22046E-01,
  5.48812E-01,  5.62705E-01,  5.76950E-01,  5.91555E-01,  6.06531E-01,  6.21885E-01,
  6.37628E-01,  6.53770E-01,  6.70320E-01,  6.87289E-01,  7.04688E-01,  7.22527E-01,
  7.40818E-01,  7.59572E-01,  7.78801E-01,  7.98516E-01,  8.18731E-01,  8.25582E-01,
  8.32491E-01,  8.39457E-01,  8.46482E-01,  8.53565E-01,  8.60708E-01,  8.67911E-01,
  8.75173E-01,  8.82497E-01,  8.89882E-01,  8.97328E-01,  9.04837E-01,  9.12409E-01,
  9.20044E-01,  9.27743E-01,  9.35507E-01,  9.43335E-01,  9.51229E-01,  9.59189E-01,
  9.67216E-01,  9.75310E-01,  9.83471E-01,  9.91701E-01,  1.00000E+00
 };
}

double HoppetInterface::xfrmz(double z)
{
 double zlow = -10.0;
 double zhigh = 1.00002;
 double tem = 1e-4;
 double rer = 1e-4;

 double eps = tem * rer;

 double xla, xlb;

 int IRT;

 if(!isDefineZfrmx) DefineZfrmx();

 zfxl = [&](double xl){
   double za = z;
   double x = exp(xl);
   double tt = zfrmx(x) - za;

   return tt;
 };

 if(z <= zhigh && z > zlow){
   xla = log(xmin) * 1.5;
   xlb = 0.00001;
   tem = zbrnt(zfxl, xla, xlb, eps, IRT);
 }
 else{
   tem = 0.0;
 }

 return exp(tem);
}

double HoppetInterface::dxdz(double z)
{
 if(!isDefineZfrmx) DefineZfrmx();

 double Value;

 double x = xfrmz(z);
 double tem = dzdx(x);
 if(tem != 0.0){
   Value = 1.0 / tem;
 }
 else{
   cout<<"DXDZ is singular in DXDZ; DXDZ set=HUGE"<<endl;
   return 1e20;
 }

 return Value;
}

void HoppetInterface::DefineZfrmx()
{
 zfrmx_f = [&](double x){
   double cc = 0.1;
   return (XCR - xmin) * log(x / xmin) + log(XCR / xmin) * (x - xmin) * (1.0 + cc * 0.001 / ((1.001 - x) * (1.001 - xmin)));
 };

 zfrmx_d = [&](double x){
   double cc = 0.1;
   return (XCR - xmin) / x + log(XCR / xmin) * (1.0 + cc * 0.001 / pow((1.001 - x), 2.0));
 };

 zfrmx = [&](double x){
   double Value;
   if(x >= xmin){
     Value = zfrmx_f(x) / zfrmx_f(1.0);
   }
   else if(x >= 0.0){
     double xx = x > 1e-35 ? x : 1e-35;
     x = xx;
     Value = zfrmx_f(x) / zfrmx_f(1.0);
   }
   else{
     cout<<"X out of range in ZFRMX, Z set to 99."<<endl;
     return 0.0;
   }

   return Value;
 };

 dzdx = [&](double x){
   double Value;
   if(x >= xmin){
     Value = zfrmx_d(x) / zfrmx_f(1.0);
   }
   else if(x >= 0.0){
     double xx = x > 1e-35 ? x : 1e-35;
     x = xx;
     Value = zfrmx_d(x) / zfrmx_f(1.0);
   }
   else{
     cout<<"X out of range in DZDX, Z set to 99."<<endl;
     return 0.0;
   }

   return Value;
 };

 isDefineZfrmx = true;
}

