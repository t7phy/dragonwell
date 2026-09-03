#include "PDFHelper/PDFHelper.h"

//using namespace LHAPDF;

//extern pthread_mutex_t LHAPDFmtx;
//pthread_mutex_t LHAPDFmtx = PTHREAD_MUTEX_INITIALIZER;

PDFHelper::PDFHelper()
{
 if(ncall != -1){
   step = -1.0;
   ResetIntegral();
   //InitialPartonName();
   return;
 }
 if(step < 0){
   ncall = -1;
   ResetIntegral();
   //InitialPartonName();
   return;
 }

}

void PDFHelper::InitialPartonName()
{
 if(!isInitial) InitialPDF(PDFName, 0);

 PartonNameMap[2] = (TString)"u";
 PartonNameMap[1] = (TString)"d";
 PartonNameMap[3] = (TString)"s";
 PartonNameMap[4] = (TString)"c";
 PartonNameMap[5] = (TString)"b";
 PartonNameMap[-2] = (TString)"ubar";
 PartonNameMap[-1] = (TString)"dbar";
 PartonNameMap[-3] = (TString)"sbar";
 PartonNameMap[-4] = (TString)"cbar";
 PartonNameMap[-5] = (TString)"bbar";
 PartonNameMap[0] = (TString)"gluon";

 for(int i = 12; i <= 1000; i++){
   Getf(i, 0.1, 100);
 }

}

void PDFHelper::InitialPDFReweightFactor(const char* OldPDFName, const char* NewPDFName, int oldPDFset, int newPDFset)
{
#ifdef USE_LHAPDF
 LHAPDF::setPaths(getenv("LHAPDF_PDF_DIR"));//set PDF path
 pold = LHAPDF::mkPDF(OldPDFName, oldPDFset);
 pnew = LHAPDF::mkPDF(NewPDFName, newPDFset);

 PDFType = "LHAPDF";

 isInitial = true;
#endif
}

void PDFHelper::InitialCTEQPDFReweightFactor(const char* OldPDFName, const char* NewPDFName)
{
 CTEQpold = new pdsReader();
 CTEQpold->Initialize(OldPDFName);

 CTEQpnew = new pdsReader();
 CTEQpnew->Initialize(NewPDFName);

 PDFType = "CTEQ";

 isInitial = true;
}

double PDFHelper::GetPDFReweightFactor(int flavour1, int flavour2, double x1, double x2, double Q)
{
#ifdef USE_LHAPDF
 if(PDFType == "LHAPDF"){
   qnew[0] = pnew->xfxQ(flavour1, x1, Q);
   qold[0] = pold->xfxQ(flavour1, x1, Q);
   qnew[1] = pnew->xfxQ(flavour2, x2, Q);
   qold[1] = pold->xfxQ(flavour2, x2, Q);

   PDFweight = (qnew[0] * qnew[1]) / (qold[0] * qold[1]);
 }
#endif

 if(PDFType == "CTEQ"){
   qnew[0] = CTEQpnew->xfxQ(flavour1, x1, Q);
   qold[0] = CTEQpold->xfxQ(flavour1, x1, Q);
   qnew[1] = CTEQpnew->xfxQ(flavour2, x2, Q);
   qold[1] = CTEQpold->xfxQ(flavour2, x2, Q);

   PDFweight = (qnew[0] * qnew[1]) / (qold[0] * qold[1]);
 }

 return PDFweight;
}

double PDFHelper::GetOldPDF(int flavor1, int flavor2, double x1, double x2, double Q)
{
#ifdef USE_LHAPDF
 if(PDFType == "LHAPDF"){
   qold[0] = pold->xfxQ(flavor1, x1, Q);
   qold[1] = pold->xfxQ(flavor2, x2, Q);
 }
#endif

 if(PDFType == "CTEQ"){
   qold[0] = CTEQpold->xfxQ(flavor1, x1, Q);
   qold[1] = CTEQpold->xfxQ(flavor2, x2, Q);
 }

 return (qold[0] * qold[1]);
}

double PDFHelper::GetNewPDF(int flavor1, int flavor2, double x1, double x2, double Q)
{
#ifdef USE_LHAPDF
 if(PDFType == "LHAPDF"){
   qnew[0] = pnew->xfxQ(flavor1, x1, Q);
   qnew[1] = pnew->xfxQ(flavor2, x2, Q);
 }
#endif
 if(PDFType == "CTEQ"){
   qnew[0] = CTEQpnew->xfxQ(flavor1, x1, Q);
   qnew[1] = CTEQpnew->xfxQ(flavor2, x2, Q);
 }

 return (qnew[0] * qnew[1]);
}

void PDFHelper::InitialPDF(const char* PDFName, int PDFset)
{
#ifdef USE_LHAPDF
 LHAPDF::setPaths(getenv("LHAPDF_PDF_DIR"));//set PDF path
 pold = LHAPDF::mkPDF(PDFName, PDFset);
 porigin = LHAPDF::mkPDF(PDFName, 0);
#endif

 this->PDFName = PDFName;
 this->iSet = PDFset;

 isInitial = true;
}

void PDFHelper::InitialCTEQPDF(const char* PDFName, const char* GivenName, int PDFset)
{
 CTEQpold = new pdsReader();
 CTEQpold->Initialize(PDFName);

 PDFType = "CTEQ";

 this->PDFName = GivenName;
 this->iSet = PDFset;

 isInitial = true;
}


  ///////////////////
  ////  1D Plot  ////
  ///////////////////

TH1D* PDFHelper::DrawPDFLumi(int nbin, double Q1, double Q2, int flavor1, int flavor2)
{
 TH1D* h1;

 TString HistName = (TString)"PDFLumi_" + PDFName + "_" + iSet + "_" + PartonNameMap[flavor1] + PartonNameMap[flavor2];

 h1 = new TH1D(HistName, HistName, nbin, Q1, Q2);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinCenter = h1->GetBinCenter(ibin);
   double Lumi = PDFLumiIntegralX(BinCenter, flavor1, flavor2);

   h1->SetBinContent(ibin, Lumi);
   h1->SetBinError(ibin, 0.0);
 }

 return h1;
}

void PDFHelper::CalcPDFLumiUnc(int nbin, double Q1, double Q2, int flavor1, int flavor2, TString ErrorType, TString PDFName, int nSet)
{
 if(isLinkFile) hf->cd();

 cout<<"Calculate PDF uncertainty for parton luminosity:"<<endl;

 vector<TH1D *> HistVector(nSet + 1);
 TH1D* PDFError;
 for(int i = 0; i <= nSet; i++){
   cout<<PDFName<<"  "<<i<<endl;
   InitialPDF(PDFName, i);
   HistVector.at(i) = DrawPDFLumi(nbin, Q1, Q2, flavor1, flavor2);
 }

 cout<<"PDFUncertainty:"<<endl;
 PDFUncertainty* unc = new PDFUncertainty();
 unc->Input1DPlot(ErrorType, HistVector, PDFError);
}

  ////////////////////////////
  ////  PDF related plot  ////
  ////////////////////////////


  ///////////////////
  ////  2D Plot  ////
  ///////////////////


  ///////////////////////
  ////  Calculation  ////
  ///////////////////////


double PDFHelper::Getf(int flavor, double x, double Q)
{
 double Value;

#ifdef USE_LHAPDF
 if(x < 1.0){
   if(PDFType == "LHAPDF") Value = pold->xfxQ(flavor, x, muF * Q) / x;
   else if(PDFType == "CTEQ") Value = CTEQpold->xfxQ(flavor, x, muF * Q) / x;
 }
 else Value = 0.0;

 if(flavor == 12){//d / u
   if(x < 1.0) Value = (pold->xfxQ(1, x, muF * Q) / x) / (pold->xfxQ(2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"dou";
 }
 if(flavor == 13){//udbar + dubar
   if(x < 1.0) Value = ((pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x)) + ((pold->xfxQ(1, x, muF * Q) / x) * (pold->xfxQ(-2, x, muF * Q) / x));
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"udbpdub";
 }
 if(flavor == 14){//udbar / dubar
   if(x < 1.0) Value = ((pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x)) / ((pold->xfxQ(1, x, muF * Q) / x) * (pold->xfxQ(-2, x, muF * Q) / x));
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"udbodub";
 }
 if(flavor == 15){//udbar + dubar + g
   if(x < 1.0) Value = ((pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x)) + ((pold->xfxQ(1, x, muF * Q) / x) * (pold->xfxQ(-2, x, muF * Q) / x)) + (pold->xfxQ(21, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"udbpdubg";
 }
 if(flavor == 16){//u + d
   if(x < 1.0) Value = (pold->xfxQ(2, x, muF * Q) / x) + (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"upd";
 }
 if(flavor == 17){//u * d
   if(x < 1.0) Value = (pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"utimesd";
 }
 if(flavor == 18){//ubar * dbar
   if(x < 1.0) Value = (pold->xfxQ(-2, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"ubartimesdbar";
 }
 if(flavor == 19){//g * s
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) * (pold->xfxQ(3, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gtimess";
 }
 if(flavor == 20){//g * u
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) * (pold->xfxQ(2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gtimesu";
 }
 if(flavor == 21){//g * d
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) * (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gtimesd";
 }
 if(flavor == 22){//g * ubar
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) * (pold->xfxQ(-2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gtimesubar";
 }
 if(flavor == 23){//g * dbar
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gtimesdbar";
 }
 if(flavor == 24){//u / d
   if(x < 1.0) Value = (pold->xfxQ(2, x, muF * Q) / x) / (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"uod";
 }
 if(flavor == 25){//ubar / dbar
   if(x < 1.0) Value = (pold->xfxQ(-2, x, muF * Q) / x) / (pold->xfxQ(-1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"ubarodbar";
 }
 if(flavor == 26){//g / s
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) / (pold->xfxQ(3, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gos";
 }
 if(flavor == 27){//g / u
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) / (pold->xfxQ(2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gou";
 }
 if(flavor == 28){//g / d
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) / (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"god";
 }
 if(flavor == 29){//g / ubar
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) / (pold->xfxQ(-2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"goubar";
 }
 if(flavor == 30){//g / dbar
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x) / (pold->xfxQ(-1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"godbar";
 }
 if(flavor == 31){//d valance
   if(x < 1.0) Value = pold->xfxQ(1, x, muF * Q) / x - pold->xfxQ(-1, x, muF * Q) / x;
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"dv";
 }
 if(flavor == 32){//u valance
   if(x < 1.0) Value = pold->xfxQ(2, x, muF * Q) / x - pold->xfxQ(-2, x, muF * Q) / x;
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"uv";
 }
 if(flavor == 33){//dbar / d valance
   if(x < 1.0) Value = (pold->xfxQ(-1, x, muF * Q) / x) / (pold->xfxQ(1, x, muF * Q) / x - pold->xfxQ(-1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"dbodv";
 }
 if(flavor == 34){//ubar / u valance
   if(x < 1.0) Value = (pold->xfxQ(-2, x, muF * Q) / x) / (pold->xfxQ(2, x, muF * Q) / x - pold->xfxQ(-2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"ubouv";
 }
 if(flavor == 35){//u*ubar / d*dbar
   if(x < 1.0) Value = ((pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(-2, x, muF * Q) / x)) / ((pold->xfxQ(1, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x));
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"uubaroddbar";
 }
 if(flavor == 36){//u*dbar / d*ubar
   if(x < 1.0) Value = ((pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x)) / ((pold->xfxQ(1, x, muF * Q) / x) * (pold->xfxQ(-2, x, muF * Q) / x));
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"udbarodubar";
 }
 if(flavor == 37){//u*d / ubar*dbar
   if(x < 1.0) Value = ((pold->xfxQ(2, x, muF * Q) / x) * (pold->xfxQ(1, x, muF * Q) / x)) / ((pold->xfxQ(-2, x, muF * Q) / x) * (pold->xfxQ(-1, x, muF * Q) / x));
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"udoubardbar";
 }
 if(flavor == 38){//dbar / ubar
   if(x < 1.0) Value = (pold->xfxQ(-1, x, muF * Q) / x) / (pold->xfxQ(-2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"dbaroubar";
 }
 if(flavor == 39){//gluon
   if(x < 1.0) Value = (pold->xfxQ(0, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"gluon";
 }
 if(flavor == 40){//s - sbar
   if(x < 1.0) Value = (pold->xfxQ(3, x, muF * Q) / x) - (pold->xfxQ(-3, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"sv";
 }
 if(flavor == 41){//u - d
   if(x < 1.0) Value = (pold->xfxQ(2, x, muF * Q) / x) - (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"umd";
 }
 if(flavor == 42){//(s + sbar)/(ubar+dbar)
   if(x < 1.0){
     if(fabs((pold->xfxQ(-2, x, muF * Q) / x) + (pold->xfxQ(-1, x, muF * Q) / x)) > 1e-30){
       Value = ((pold->xfxQ(3, x, muF * Q) / x) + (pold->xfxQ(-3, x, muF * Q) / x)) / ((pold->xfxQ(-2, x, muF * Q) / x) + (pold->xfxQ(-1, x, muF * Q) / x));
     }
   }
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"ssbaroubardbar";
 }
 if(flavor == 43){//dbar / d
   if(x < 1.0) Value = (pold->xfxQ(-1, x, muF * Q) / x) / (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"dbod";
 }
 if(flavor == 44){//ubar / u
   if(x < 1.0) Value = (pold->xfxQ(-2, x, muF * Q) / x) / (pold->xfxQ(2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"ubou";
 }
 if(flavor == 45){//dbar / u
   if(x < 1.0) Value = (pold->xfxQ(-1, x, muF * Q) / x) / (pold->xfxQ(2, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"dbou";
 }
 if(flavor == 46){//ubar / d
   if(x < 1.0) Value = (pold->xfxQ(-2, x, muF * Q) / x) / (pold->xfxQ(1, x, muF * Q) / x);
   else Value = 0.0;
   PartonNameMap[flavor] = (TString)"ubod";
 }


#endif

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double PDFHelper::Getx1x2Combination(int flavor, double x1, double x2, double Q)
{
 double Value;

// if(x2 < 1e-9) x2 = (Q * Q) / (ECM * ECM * x1);
 if(x2 < 1e-9) x2 = (0.0015 / 0.031) * x1;

#ifdef USE_LHAPDF
 if(flavor == 1){//u(x1)ubar(x2)-u(x2)ubar(x1)
   if(x1 < 1.0 && x2 < 1.0) Value = uqk(x1, Q) * ubar(x2, Q) - uqk(x2, Q) * ubar(x1, Q);
   else Value = 0.0;
 }
 if(flavor == 2){//W asymmetry
   if(x1 < 1.0 && x2 < 1.0) Value = (uqk(x1, Q) * dbar(x2, Q) + uqk(x2, Q) * dbar(x1, Q) + uqk(x1, Q) * sbar(x2, Q) + uqk(x2, Q) * sbar(x1, Q)) / (ubar(x1, Q) * dqk(x2, Q) + ubar(x2, Q) * dqk(x1, Q) + ubar(x1, Q) * sqk(x2, Q) + ubar(x2, Q) * sqk(x1, Q));
   else Value = 0.0;
 }

#endif

 if(!isfinite(Value)) return 0.0;

 return Value;

}

double PDFHelper::GetfOrigin(int flavor, double x, double Q)
{
 double Value;

#ifdef USE_LHAPDF
 if(x < 1.0) Value = porigin->xfxQ(flavor, x, muF * Q) / x;
 else Value = 0.0;

 if(flavor == 10){//d valance
   if(x < 1.0) Value = porigin->xfxQ(1, x, muF * Q) / x - porigin->xfxQ(-1, x, muF * Q) / x;
   else Value = 0.0;
 }
 if(flavor == 20){//u valance
   if(x < 1.0) Value = porigin->xfxQ(2, x, muF * Q) / x - porigin->xfxQ(-2, x, muF * Q) / x;
   else Value = 0.0;
 }
 if(flavor == 100){//dbar / d valance
   if(x < 1.0) Value = (porigin->xfxQ(-1, x, muF * Q) / x) / (porigin->xfxQ(1, x, muF * Q) / x - porigin->xfxQ(-1, x, muF * Q) / x);
   else Value = 0.0;
 }
 if(flavor == 200){//ubar / u valance
   if(x < 1.0) Value = (porigin->xfxQ(-2, x, muF * Q) / x) / (porigin->xfxQ(2, x, muF * Q) / x - porigin->xfxQ(-2, x, muF * Q) / x);
   else Value = 0.0;
 }
#endif

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double PDFHelper::Getxf(int flavor, double x, double Q)
{
 double Value;

#ifdef USE_LHAPDF
 if(x < 1.0){
   if(PDFType == "LHAPDF") Value = pold->xfxQ(flavor, x, muF * Q);
   else if(PDFType == "CTEQ") Value = CTEQpold->xfxQ(flavor, x, muF * Q);
 }
 else Value = 0.0;
#endif

 if(!isfinite(Value)) return 0.0;
 
 return Value;
}

double PDFHelper::GetF1F2(int flavor, double x, double Q)
{
 double x1 = x;
 double x2 = (Q * Q) / (ECM * ECM * x1);
 double f1;
 double f2;

#ifdef USE_LHAPDF
 if(x1 < 1.0) f1 = pold->xfxQ(flavor, x1, muF * Q) / (x1);
 else f1 = 0.0;
 if(x2 < 1.0) f2 = pold->xfxQ(flavor * (-1), x2, muF * Q) / (x2);
 else f2 = 0.0;
#endif

 double Value = (f1 * f2 * 2.0 * Q) / (ECM * ECM * x1);

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double PDFHelper::GetF1F2dY(int flavor, double x, double Q)
{
 double x1 = x; 
 double x2 = (Q * Q) / (ECM * ECM * x1);
 double f1;
 double f2;

#ifdef USE_LHAPDF
 if(x1 < 1.0) f1 = pold->xfxQ(flavor, x1, muF * Q) / (x1);
 else f1 = 0.0;
 if(x2 < 1.0) f2 = pold->xfxQ(flavor * (-1), x2, muF * Q) / (x2);
 else f2 = 0.0; 
#endif

 double Value = (f1 * f2 * 2.0 * Q) / (ECM * ECM);
 
 if(!isfinite(Value)) return 0.0;
 
 return Value;
}

double PDFHelper::GetF1F2dYRight(int flavor, double x, double Q)
{
 double x1 = x;
 double x2 = (Q * Q) / (ECM * ECM * x1);
 double f1;
 double f2;

#ifdef USE_LHAPDF
 if(x1 < 1.0) f1 = pold->xfxQ(flavor, x1, muF * Q) / (x1);
 else f1 = 0.0;
 if(x2 < 1.0) f2 = pold->xfxQ(flavor * (-1), x2, muF * Q) / (x2);
 else f2 = 0.0;
#endif

 double Value = (f1 * f2 * 2.0 * Q) / (ECM * ECM);

 if(flavor < 0){//qbarq   qbar < q
   if(x1 > x2) return 0.0;
   else return Value;
 }
 if(flavor > 0){//qqbar   q > qbar
   if(x1 < x2) return 0.0;
   else return Value;
 }

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double PDFHelper::GetF1F2dYWrong(int flavor, double x, double Q)
{
 double x1 = x;
 double x2 = (Q * Q) / (ECM * ECM * x1);
 double f1;
 double f2;

#ifdef USE_LHAPDF
 if(x1 < 1.0) f1 = pold->xfxQ(flavor, x1, muF * Q) / (x1);
 else f1 = 0.0;
 if(x2 < 1.0) f2 = pold->xfxQ(flavor * (-1), x2, muF * Q) / (x2);
 else f2 = 0.0;
#endif

 double Value = (f1 * f2 * 2.0 * Q) / (ECM * ECM);

 //if(Value < 0) Value = 0.0;
 if(flavor < 0){//qbarq   qbar > q
   if(x1 < x2) return 0.0;
   else return Value;
 }
 if(flavor > 0){//qqbar   q < qbar
   if(x1 > x2) return 0.0;
   else return Value;
 }

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double PDFHelper::GetF1F2YInput(int flavor, double y, double Q)
{
 double x1 = (Q / ECM) * exp(y);
 double x2 = (Q / ECM) * exp(y * (-1));

 double Value = GetF1F2dY(flavor, x1, Q);

 return Value;
}

double PDFHelper::GetPDFLumi(double x, int flavor1, int flavor2, double Q)
{
 double Value = 0.0;
 double Value1 = 0.0;
 double Value2 = 0.0;
 double x1 = x;
 double x2 = Q * Q / ECM / ECM / x1;
#ifdef USE_LHAPDF
 if(x1 < 1.0) Value1 = pold->xfxQ(flavor1, x1, muF * Q) / x1;
 else Value1 = 0.0;

 if(x2 < 1.0) Value2 = pold->xfxQ(flavor2, x2, muF * Q) / x2;
 else Value2 = 0.0;

 Value = (Q * Q / ECM / ECM) * Value1 * Value2 / x1;
#endif

 return Value;
}

double PDFHelper::GetValence(int flavor, double x, double Q)
{
 double Value1;
 double Value2;

#ifdef USE_LHAPDF
 if(x < 1.0) Value1 = pold->xfxQ(abs(flavor), x, muF * Q) / x;
 else Value1 = 0.0;
 if(x < 1.0) Value2 = pold->xfxQ(abs(flavor) * (-1), x, muF * Q) / x;
 else Value2 = 0.0;
#endif

 double Value = Value1 - Value2;

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double PDFHelper::GetNormPDF(int flavor, double x, double Q)
{
 double f1Integral = PDFIntegral(Q, flavor);

 double left = log10((Q * Q) / (ECM * ECM));
 double right = 0.0;

// double Value = SimpsonLog10(&PDFReweight::Getf, left, right, flavor, mass);

 double Value = Getf(flavor, x, Q) / f1Integral;

 cout<<Getf(flavor, x, Q)<<" "<<Value<<" "<<f1Integral<<endl;

 return Value;
}

double PDFHelper::GetDilution(int flavor, double y, double q)
{
 double x1;
 double x2;

 if(y > 0){
   x1 = (q / ECM) * exp(y);
   x2 = (q / ECM) * exp(y * (-1));
 }
 else if(y < 0){
   x1 = (q / ECM) * exp(y * (-1));
   x2 = (q / ECM) * exp(y);
 }

 double wrong, right;

#ifdef USE_LHAPDF
 wrong = pold->xfxQ(flavor * (-1), x1, muF * q) * pold->xfxQ(flavor, x2, muF * q);
 right = pold->xfxQ(flavor, x1, muF * q) * pold->xfxQ(flavor * (-1), x2, muF * q);
#endif

 double Dilution = wrong / (wrong + right);

 return Dilution;
}


  ////////////////////
  ////  Integral  ////
  ////////////////////



double PDFHelper::CfCf(double mass, int flavor, TString Process)
{
 double left = log10((mass * mass) / (ECM * ECM));
 double right = -1.0;

 double Value = 0.0;

 if(Process == ""){
   left = log10((mass * mass) / (ECM * ECM));
   right = -1.0;

   ncall = 100;
   isOutput = false;
   Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);

   left = 0.1;
   right = 1.0;
   ncall = 100;
   isOutput = false;
   Value = Value + Simpson(&PDFHelper::GetF1F2, left, right, flavor, mass);
 }
 else if(Process == "Right"){
   if(flavor > 0){//qqbar   q > qbar
     left = log10(mass / ECM);//central
     right = -1.0;//maximum

     ncall = 100;
     isOutput = false;
     Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);

     left = 0.1;
     right = 1.0;
     ncall = 100;
     isOutput = false;
     Value = Value + Simpson(&PDFHelper::GetF1F2, left, right, flavor, mass);
   }
   if(flavor < 0){//qbarq   qbar < q
     left = log10((mass * mass) / (ECM * ECM));//minimum
     right = log10(mass / ECM);//central

     ncall = 100;
     isOutput = false;
     Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);
   }
 }
 else if(Process == "Wrong"){
   if(flavor < 0){//qbarq   qbar > q
     left = log10(mass / ECM);//central
     right = -1.0;//maximum

     ncall = 100;
     isOutput = false;
     Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);

     left = 0.1;
     right = 1.0;
     ncall = 100;
     isOutput = false;
     Value = Value + Simpson(&PDFHelper::GetF1F2, left, right, flavor, mass);
   }
   if(flavor > 0){//qqbar   q < qbar
     left = log10((mass * mass) / (ECM * ECM));//minimum
     right = log10(mass / ECM);//central

     ncall = 100;
     isOutput = false;
     Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);
   }
 }

 return Value;
}

double PDFHelper::CfCfQgtQbar(double mass, int flavor, TString Process)
{
 double left = log10((mass * mass) / (ECM * ECM));
 double right = -1.0;

 double Value = 0.0;

 if(flavor > 0){//qqbar   q > qbar
   left = log10(mass / ECM);//central
   right = -1.0;//maximum

   ncall = 100;
   isOutput = false;
   Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);

   left = 0.1;
   right = 1.0;
   ncall = 100;
   isOutput = false;
   Value = Value + Simpson(&PDFHelper::GetF1F2, left, right, flavor, mass);

 }
 if(flavor < 0){//qbarq   qbar < q
   left = log10((mass * mass) / (ECM * ECM));//minimum
   right = log10(mass / ECM);//central

   ncall = 100;
   isOutput = false;
   Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);
 }

 return Value;
}

double PDFHelper::CfCfQltQbar(double mass, int flavor, TString Process)
{
 double left = log10((mass * mass) / (ECM * ECM));
 double right = -1.0;
 
 double Value = 0.0;
 
 if(flavor < 0){//qbarq   qbar > q
   left = log10(mass / ECM);//central
   right = -1.0;//maximum
   
   ncall = 100;
   isOutput = false;
   Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);
   
   left = 0.1;
   right = 1.0;
   ncall = 100;
   isOutput = false;
   Value = Value + Simpson(&PDFHelper::GetF1F2, left, right, flavor, mass);
 
 }
 if(flavor > 0){//qqbar   q > qbar
   left = log10((mass * mass) / (ECM * ECM));//minimum
   right = log10(mass / ECM);//central
   
   ncall = 100;
   isOutput = false;
   Value = SimpsonLog10(&PDFHelper::GetF1F2, left, right, flavor, mass);
 }

 return Value;
}

double PDFHelper::PDFIntegral(double mass, int flavor)
{
 double left = -9.0;
// double left = log10((mass * mass) / (ECM * ECM));
 double right = -1.0;

 double Value = 0.0;

 ncall = 10000;
 isOutput = false;
 Value = SimpsonLog10(&PDFHelper::Getf, left, right, flavor, mass);

 left = 0.1;
 right = 1.0;
 ncall = 10000;
 isOutput = false;
 Value = Value + Simpson(&PDFHelper::Getf, left, right, flavor, mass);

 return Value;
}

double PDFHelper::xPDFIntegral(double mass, int flavor)
{
 double left = -9.0;
// double left = log10((mass * mass) / (ECM * ECM));
 double right = -1.0;

 double Value = 0.0;

 ncall = 10000;
 isOutput = false;
 Value = SimpsonLog10(&PDFHelper::Getxf, left, right, flavor, mass);

 left = 0.1;
 right = 1.0;
 ncall = 10000;
 isOutput = false;
 Value = Value + Simpson(&PDFHelper::Getxf, left, right, flavor, mass);

 return Value;
}

double PDFHelper::CfCfIntegral(double left, double right, int flavor, TString Process)
{
 double Value = 0.0;

 ncall = 100;
 isOutput = false;

 cout<<"Start Integral CfCf: ["<<left<<", "<<right<<"]"<<endl;
 Value = Simpson(&PDFHelper::CfCf, left, right, flavor, Process);

 return Value;
}

double PDFHelper::PDFLumiIntegralX(double Q, int flavor1, int flavor2)
{
 double Value = 0.0;

 ncall = 100;
 isOutput = false;

 cout<<"Start Integral PDF luminosity: flavor1 = "<<flavor1<<" flavor2 = "<<flavor2<<" Q = "<<Q<<endl;

 double left;
 double right;

 left = log10(Q * Q / ECM / ECM);
 right = -1.0;
 ncall = 100;
 isOutput = false;

 Value = SimpsonLog10(&PDFHelper::GetPDFLumi, left, right, flavor1, flavor2, Q);

 left = 0.1;
 right = 1.0;
 ncall = 100;
 isOutput = false;
 Value = Simpson(&PDFHelper::GetPDFLumi, left, right, flavor1, flavor2, Q);

 return Value;
}

double PDFHelper::PDFLumiIntegralQ(double Q1, double Q2, int flavor1, int flavor2)
{
 double Value = 0.0;

 ncall = 100;
 isOutput = false;

 Value = Simpson(&PDFHelper::PDFLumiIntegralX, Q1, Q2, flavor1, flavor2);

 return Value;
}

void PDFHelper::openFile(TString FileName)
{
 isLinkFile = true;

 hf = new TFile(FileName, "RECREATE");
}

void PDFHelper::LinkFile(TFile* hf)
{
 isLinkFile = true;

 this->hf = hf;
}

void PDFHelper::SaveFile()
{
 hf->cd();
 hf->Write();
 hf->Close();
}



  //////////////////////////
  ////  Integral micro  ////
  //////////////////////////


double PDFHelper::Simpson(double(PDFHelper::*fcn)(double), double left, double right)
{
 if(this->ncall == -1) this->ncall = (right - left) / this->step;
 if(this->step < 0) this->step = (right - left) / (double)(this->ncall);

 int ncall = this->ncall;
 double step = this->step; 
 bool isOutput = this->isOutput;
 double Value = 0.0;
 
 for(int i = 0; i < ncall; i++){
   double a = left + step * i; 
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;
   
   x1 = a;
   f1 = (this->*fcn)(x1);
   double term1 = f1;
   Value += f1;
   
   x1 = (a + b) / 2.0;
   f1 = (this->*fcn)(x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;
   
   x1 = b;
   f1 = (this->*fcn)(x1);
   double term3 = f1;
   Value += f1;

   if(i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
 }

 if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
 if(isOutput) cout<<endl;

 double Result = (step / 6.0) * Value;

 ResetIntegral();

 return Result;
}

double PDFHelper::SimpsonLog10(double(PDFHelper::*fcn)(double), double left, double right)
{
 if(this->ncall == -1) this->ncall = (right - left) / this->step;
 if(this->step < 0) this->step = (right - left) / (double)(this->ncall);
 
 int ncall = this->ncall;
 double step = this->step;
 bool isOutput = this->isOutput;
 double Value = 0.0;
 
 for(int i = 0; i < ncall; i++){
   double a = left + step * i; 
   double b = left + step * (i + 1);
   double x1 = 0.0;
   double f1 = 0.0;
   
   x1 = a;
   f1 = (this->*fcn)(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term1 = f1;
   Value += f1;
   
   x1 = (a + b) / 2.0;
   f1 = (this->*fcn)(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term2 = 4.0 * f1;
   Value += 4.0 * f1;
   
   x1 = b;
   f1 = (this->*fcn)(pow(10.0, x1)) * log(10) * pow(10.0, x1);
   double term3 = f1;
   Value += f1;

   if(i % (ncall / 10) == 0 && i != 0 && isOutput) cout<<"Integral "<<(i / (ncall / 10))<<"0%: "<<(step / 6.0) * Value<<endl;
 }

 if(isOutput) cout<<"Integral 100%: "<<(step / 6.0) * Value<<endl;
 if(isOutput) cout<<endl;

 double Result = (step / 6.0) * Value;

 ResetIntegral();

 return Result;
}

