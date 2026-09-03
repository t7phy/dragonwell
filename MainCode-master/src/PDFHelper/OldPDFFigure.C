#ifndef PDFHelper_OldPDFFigure_cxx
#define PDFHelper_OldPDFFigure_cxx

#include "PDFHelper/OldPDFFigure.h"

#ifdef USE_LHAPDF
using namespace LHAPDF;
#endif

OldPDFFigure::OldPDFFigure()
{
#ifdef USE_LHAPDF
 setPaths(getenv("LHAPDF_PDF_DIR"));//set PDF path
#endif

 for(int i = 0; i < 5000; i++){
   LogBin[i] = pow(10, (5.0 / 3.0) * log10((i + 1) / 5000.0));
 }

 isInitialPDF[1] = false;
 isInitialPDF[2] = false;
 isInitialPDF[3] = false;

 CLFactor[1] = 1.0;
 CLFactor[2] = 1.0;
 CLFactor[3] = 1.0;

 DefineCombination();
}

void OldPDFFigure::InitialPDF(int iPDF, const char* PDFName, int PDFset)
{
#ifdef USE_LHAPDF
 myPDF[iPDF] = LHAPDF::mkPDF(PDFName, PDFset);

 PDFNameMap[iPDF] = PDFName;

 PDFErrorIndex[iPDF] = PDFset;

 isInitialPDF[iPDF] = true;

 PDFType[iPDF] = "LHAPDF";
#endif
}

void OldPDFFigure::InitialCTEQPDF(int iPDF, TString PDFName, TString GivenName, int PDFset)
{
// CTPDF[iPDF] = new pdsReader();
// CTPDF[iPDF]->Initialize(PDFName);
 CTPDFIndex[make_pair((TString)GivenName, PDFset)] = new pdsReader();
 CTPDFIndex[make_pair((TString)GivenName, PDFset)]->Initialize(PDFName);

 PDFNameMap[iPDF] = GivenName;
 PDFNameIndex[GivenName] = iPDF;

 PDFErrorIndex[iPDF] = PDFset;

 isInitialPDF[iPDF] = true;

 PDFType[iPDF] = "CTEQ";

}

void OldPDFFigure::InitialCTEQPDFSets(int iPDF, vector<TString> PDFNames, TString GivenName)
{
 for(int i = 0; i < PDFNames.size(); i++){
   InitialCTEQPDF(iPDF, PDFNames.at(i), GivenName, i);
 }

 CTPDFnSet[(TString)GivenName] = PDFNames.size();
}

void OldPDFFigure::InitialErrorPDF(int iPDF, const char* PDFName, int PDFset)
{
#ifdef USE_LHAPDF
 myPDF[iPDF] = LHAPDF::mkPDF(PDFName, PDFset);

 PDFType[iPDF] = "LHAPDF";
#endif
}

void OldPDFFigure::InitialPDF1(const char* PDFName, int PDFset)
{
#ifdef USE_LHAPDF
 myPDF[1] = LHAPDF::mkPDF(PDFName, PDFset);
 this->PDFName = PDFName;
 this->iSet = PDFset;

 PDFNameMap[1] = PDFName;

 isInitialPDF[1] = true;

 PDFType[1] = "LHAPDF";
#endif
}

void OldPDFFigure::InitialPDF2(const char* PDFName, int PDFset)
{
#ifdef USE_LHAPDF
 myPDF[2] = LHAPDF::mkPDF(PDFName, PDFset);

 this->PDFName = PDFName;
 this->iSet = PDFset;

 PDFNameMap[2] = PDFName;

 isInitialPDF[2] = true;

 PDFType[2] = "LHAPDF";
#endif
}

void OldPDFFigure::InitialTwoPDF(const char* PDFName1, const char* PDFName2, int PDFset1, int PDFset2)
{
#ifdef USE_LHAPDF
 myPDF[1] = LHAPDF::mkPDF(PDFName1, PDFset1);
 myPDF[2] = LHAPDF::mkPDF(PDFName2, PDFset2);

 this->PDFName1 = PDFName1;
 this->iSet1 = PDFset1;
 this->PDFName2 = PDFName2;
 this->iSet2 = PDFset2;

 PDFNameMap[1] = PDFName1;
 PDFNameMap[2] = PDFName2;

 isInitialPDF[1] = true;
 isInitialPDF[2] = true;

 PDFType[1] = "LHAPDF";
 PDFType[2] = "LHAPDF";
#endif
}

void OldPDFFigure::InputPDFnSet(int iPDF, int nSet)
{
 nSetMap[iPDF] = nSet;
}

void OldPDFFigure::CompareTwoPDFWithError(int flavor)
{
// GetPDFRatio(2, 1, flavor);
 GetPDFRatio(1, 1, flavor);
 GetPDFRatio(2, 2, flavor);
}

void OldPDFFigure::ComparePDFWithEigen(int flavor)
{
 GetPDFRatio(2, 2, flavor);
 GetPDFEigenRatio(1, 2, 1, flavor);
 GetPDFEigenRatio(1, 2, 2, flavor);

 vector<int> Index1 = {1, 2, 1, flavor};
 vector<int> Index2 = {1, 2, 2, flavor};
 vector<int> Index = {1, 2, flavor};

 TString HistName = "PDFEigenError_" + PDFNameMap[1] + "_" + PDFNameMap[2] + "_" + FlavorNameMap[flavor];
 PDFEigenErrorPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);
 for(int ibin = 1; ibin <= nBin; ibin++){
   double Error = fabs(PDFEigenRatioPlot[Index1]->GetBinContent(ibin) - PDFEigenRatioPlot[Index2]->GetBinContent(ibin)) / 2.0;
   PDFEigenErrorPlot[Index]->SetBinContent(ibin, 1.0);
   PDFEigenErrorPlot[Index]->SetBinError(ibin, Error);
 }
 hf->cd();
}

void OldPDFFigure::ComparePDFWithEigen(int iPDF1, int iPDF2, int flavor)
{
 GetPDFRatio(iPDF2, iPDF2, flavor);
 GetPDFEigenRatio(iPDF1, iPDF2, 1, flavor);
 GetPDFEigenRatio(iPDF1, iPDF2, 2, flavor);

 vector<int> Index1 = {iPDF1, iPDF2, 1, flavor};
 vector<int> Index2 = {iPDF1, iPDF2, 2, flavor};
 vector<int> Index = {iPDF1, iPDF2, flavor};

 TString HistName = "PDFEigenError_" + PDFNameMap[iPDF1] + "_" + PDFNameMap[iPDF2] + "_" + FlavorNameMap[flavor];
 PDFEigenErrorPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);
 for(int ibin = 1; ibin <= nBin; ibin++){
   double Error = fabs(PDFEigenRatioPlot[Index1]->GetBinContent(ibin) - PDFEigenRatioPlot[Index2]->GetBinContent(ibin)) / 2.0;
   PDFEigenErrorPlot[Index]->SetBinContent(ibin, 1.0);
   PDFEigenErrorPlot[Index]->SetBinError(ibin, Error);
 }
 hf->cd();
}

void OldPDFFigure::GetPDFEigenRatio(int iPDF1, int iPDF2, int Eigen, int flavor)
{
 /**********************************************************/
 /* Calculate the PDF1 eigen set ratio to PDF2 central set */
 /* same with s21 option in CPP                            */
 /**********************************************************/
 if(!isInitialPDF[iPDF1] || !isInitialPDF[iPDF2]){
   cout<<"ERROR! Please initialize the PDF at first!"<<endl;
   return;
 }

 GetPDFCentral(iPDF1, flavor);
 GetPDFCentral(iPDF2, flavor);
 GetPDFEigen(iPDF1, Eigen, flavor);

 vector<int> Index = {iPDF1, iPDF2, Eigen, flavor};
 vector<int> Index1 = {iPDF1, Eigen, flavor};
 pair<int, int> Index2 = make_pair(iPDF2, flavor);

 if(!PDFEigenRatioPlot[Index]){
   TString HistName = "PDFEigenRatio_" + PDFNameMap[iPDF1] + "_Eigen" + (int)Eigen + "_" + PDFNameMap[iPDF2] + "_" + FlavorNameMap[flavor];
   PDFEigenRatioPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);
   for(int ibin = 1; ibin <= nBin; ibin++){
     double Numer = PDFEigenPlot[Index1]->GetBinContent(ibin);
     double Denom = PDFCentralPlot[Index2]->GetBinContent(ibin);
     double Value = (Denom + (Numer - Denom) / CLFactor[iPDF1]) / Denom;
     PDFEigenRatioPlot[Index]->SetBinContent(ibin, Value);
     PDFEigenRatioPlot[Index]->SetBinError(ibin, 0.0);
   }
 }

 hf->cd();
}

void OldPDFFigure::GetPDFRatio(int iPDF1, int iPDF2, int flavor)
{
 /************************************/
 /* Calculate the PDF1 ratio to PDF2 */
 /* with PDF uncertainty             */
 /* same with s20 option in CPP      */
 /************************************/

 if(!isInitialPDF[iPDF1] || !isInitialPDF[iPDF2]){
   cout<<"ERROR! Please initialize the PDF at first!"<<endl;
   return;
 }

 GetPDFCentral(iPDF1, flavor);
 GetPDFCentral(iPDF2, flavor);
 GetPDFError(iPDF1, flavor);
 GetPDFError(iPDF2, flavor);

 vector<int> Index = {iPDF1, iPDF2, flavor};
 pair<int, int> Index1 = make_pair(iPDF1, flavor);
 pair<int, int> Index2 = make_pair(iPDF2, flavor);

 if(!PDFCentralRatioPlot[Index] && !PDFErrorPlusRatioPlot[Index] && !PDFErrorMinusRatioPlot[Index]){
   TString HistName = "PDFCentralRatio_" + PDFNameMap[iPDF1] + "_" + PDFNameMap[iPDF2] + "_" + FlavorNameMap[flavor];
   PDFCentralRatioPlot[Index] = (TH1D *)PDFCentralPlot[Index1]->Clone(HistName);
   PDFCentralRatioPlot[Index]->Divide(PDFCentralPlot[Index2]);

   HistName = "PDFErrorPlusRatio_" + PDFNameMap[iPDF1] + "_" + PDFNameMap[iPDF2] + "_" + FlavorNameMap[flavor];
   PDFErrorPlusRatioPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);

   HistName = "PDFErrorMinusRatio_" + PDFNameMap[iPDF1] + "_" + PDFNameMap[iPDF2] + "_" + FlavorNameMap[flavor];
   PDFErrorMinusRatioPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);

   for(int ibin = 1; ibin <= nBin; ibin++){
     double Value1 = PDFCentralPlot[Index1]->GetBinContent(ibin);
     double Value2 = PDFCentralPlot[Index2]->GetBinContent(ibin);
     double Error1 = PDFErrorPlusPlot[Index1]->GetBinContent(ibin);
     double Error2 = PDFErrorPlusPlot[Index2]->GetBinContent(ibin);

     double Value = sqrt(Value1 * Value1 * Error2 * Error2 + Value2 * Value2 * Error1 * Error1) / (Value2 * Value2);
     double Central = PDFCentralRatioPlot[Index]->GetBinContent(ibin);
     PDFErrorPlusRatioPlot[Index]->SetBinContent(ibin, Value + Central);
     PDFErrorPlusRatioPlot[Index]->SetBinError(ibin, 0.0);
     PDFErrorMinusRatioPlot[Index]->SetBinContent(ibin, Value * (-1.0) + Central);
     PDFErrorMinusRatioPlot[Index]->SetBinError(ibin, 0.0);
     PDFCentralRatioPlot[Index]->SetBinError(ibin, Value);
   }
 }

 hf->cd();
}

void OldPDFFigure::GetPDFCentral(int iPDF, int flavor)
{
 /************************************************/
 /* Calculate the PDF prediction for central PDF */
 /************************************************/

 if(!isInitialPDF[iPDF]){
   cout<<"ERROR! Please initialize the PDF at first!"<<endl;
   return;
 }

 InitialErrorPDF(iPDF, PDFNameMap[iPDF], 0);

 pair<int, int> Index = make_pair(iPDF, flavor);

 if(!PDFCentralPlot[Index]){
   TString HistName = "PDFCentral_" + PDFNameMap[iPDF] + "_" + FlavorNameMap[flavor];
   PDFCentralPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);

   for(int ibin = 1; ibin <= nBin; ibin++){
     double BinCenter = PDFCentralPlot[Index]->GetBinCenter(ibin);
     double Value = Getf(iPDF, flavor, BinCenter, 91.1876);
     if(isTimeX) Value = Value * BinCenter;

     PDFCentralPlot[Index]->SetBinContent(ibin, Value);
     PDFCentralPlot[Index]->SetBinError(ibin, 0.0);
   }
 }

 hf->cd();
}

void OldPDFFigure::GetPDFEigen(int iPDF, int Eigen, int flavor)
{
 /**************************************************/
 /* Calculate the PDF prediction for one eigen PDF */
 /**************************************************/

 if(!isInitialPDF[iPDF]){
   cout<<"ERROR! Please initialize the PDF at first!"<<endl;
   return;
 }
 
 InitialErrorPDF(iPDF, PDFNameMap[iPDF], Eigen);

 vector<int> Index = {iPDF, Eigen, flavor};

 if(!PDFEigenPlot[Index]){
   TString HistName = "PDFEigen_" + PDFNameMap[iPDF] + "_Eigen" + (int)Eigen + "_" + FlavorNameMap[flavor];
   PDFEigenPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);
   
   for(int ibin = 1; ibin <= nBin; ibin++){
     double BinCenter = PDFEigenPlot[Index]->GetBinCenter(ibin);
     double Value = Getf(iPDF, flavor, BinCenter, 91.1876);
     
     PDFEigenPlot[Index]->SetBinContent(ibin, Value);
     PDFEigenPlot[Index]->SetBinError(ibin, 0.0);
   }
 }
 
 hf->cd();
}

void OldPDFFigure::GetPDFError(int iPDF, int flavor)
{
 /*************************************************/
 /* Calculate the PDF error for all PDF error set */
 /*************************************************/

 if(!isInitialPDF[iPDF]){
   cout<<"ERROR! Please initialize the PDF at first!"<<endl;
   return;
 }

 pair<int, int> Index = make_pair(iPDF, flavor);

 if(!PDFErrorPlusPlot[Index] && !PDFErrorMinusPlot[Index]){
   TString HistName = "PDFErrorPlus_" + PDFNameMap[iPDF] + "_" + FlavorNameMap[flavor];
   PDFErrorPlusPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);
   HistName = "PDFErrorMinus_" + PDFNameMap[iPDF] + "_" + FlavorNameMap[flavor];
   PDFErrorMinusPlot[Index] = new TH1D(HistName, HistName, nBin, LogBin);

   vector<double> Parton1PDF;
   vector<vector<double>> Parton1PDFs;
   vector<double> Parton1ErrorPDF;
   vector<vector<double>> Parton1ErrorPDFs;

   for(int k = 0; k <= nSetMap[iPDF]; k++){
     InitialErrorPDF(iPDF, PDFNameMap[iPDF], k);
     for(int ibin = 1; ibin <= nBin; ibin++){
       Parton1PDF.push_back(Getf(iPDF, flavor, PDFErrorPlusPlot[Index]->GetBinCenter(ibin), 91.1876));
     }
     Parton1PDFs.push_back(Parton1PDF);
     Parton1PDF.clear();
   }

   for(int k = 1; k <= nSetMap[iPDF] / 2; k++){
     for(int ibin = 1; ibin <= nBin; ibin++){
       double Parton1ErrorValue = Parton1PDFs.at(2 * k - 1).at(ibin - 1) - Parton1PDFs.at(2 * k).at(ibin - 1);
       Parton1ErrorPDF.push_back(Parton1ErrorValue);
     }
     Parton1ErrorPDFs.push_back(Parton1ErrorPDF);
     Parton1ErrorPDF.clear();
   }

   for(int ibin = 1; ibin <= nBin; ibin++){
     double DeltaX = 0.0;
     double DeltaX2 = 0.0;
     for(int k = 1; k <= nSetMap[iPDF] / 2; k++){
       DeltaX2 += Parton1ErrorPDFs.at(k - 1).at(ibin - 1) * Parton1ErrorPDFs.at(k - 1).at(ibin - 1) / 4.0;
     }
     DeltaX = sqrt(DeltaX2) / CLFactor[iPDF];

     PDFErrorPlusPlot[Index]->SetBinContent(ibin, DeltaX);
     PDFErrorPlusPlot[Index]->SetBinError(ibin, 0);

     PDFErrorMinusPlot[Index]->SetBinContent(ibin, DeltaX * (-1.0));
     PDFErrorMinusPlot[Index]->SetBinError(ibin, 0);
   }
 }

 hf->cd();

}

TH1D* OldPDFFigure::DrawPDFvsX(int iPDF, int flavor, double Q, vector<double> X)
{
 TH1D* h1;

#ifdef USE_LHAPDF
 vector<double> Binning(X.size() + 1);
 Binning.at(0) = X.at(0) * 1.5 - X.at(1) * 0.5;
 Binning.at(Binning.size() - 1) = X.at(X.size() - 1) * 1.5 - X.at(X.size() - 2) * 0.5;
 for(int i = 1; i < X.size(); i++){
   Binning.at(i) = (X.at(i - 1) + X.at(i)) * 0.5;
 }

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(2)<<Q;

 Qstring = s_Qstring.str();

 TString HistName = "PDFvsX_Q_" + Qstring + "_" + PDFNameMap[iPDF] + "_iSet_" + PDFErrorIndex[iPDF] + "_" + FlavorNameMap[flavor];
 h1 = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinCenter = h1->GetBinCenter(ibin);
   h1->SetBinContent(ibin, Getf(iPDF, flavor, BinCenter, Q));
   h1->SetBinError(ibin, 0.0);
 }

#endif
 return h1;
}

TH1D* OldPDFFigure::DrawPDFvsQ(int iPDF, int flavor, double x, vector<double> Q)
{
 TH1D* h1;

#ifdef USE_LHAPDF
 vector<double> Binning(Q.size() + 1);
 Binning.at(0) = Q.at(0) * 1.5 - Q.at(1) * 0.5;
 Binning.at(Binning.size() - 1) = Q.at(Q.size() - 1) * 1.5 - Q.at(Q.size() - 2) * 0.5;
 for(int i = 1; i < Q.size(); i++){
   Binning.at(i) = (Q.at(i - 1) + Q.at(i)) * 0.5;
 }

 stringstream s_xstring;
 TString xstring;

 if(x < 1e-4){
   s_xstring<<fixed<<setprecision(5)<<x;
 }
 else if(x >= 1e-4 && x < 1e-3){
   s_xstring<<fixed<<setprecision(4)<<x;
 }
 else if(x >= 1e-3 && x < 1e-2){
   s_xstring<<fixed<<setprecision(3)<<x;
 }
 else if(x >= 1e-2 && x < 1e-1){
   s_xstring<<fixed<<setprecision(2)<<x;
 }
 else if(x >= 1e-1 && x < 1){
   s_xstring<<fixed<<setprecision(1)<<x;
 }

 xstring = s_xstring.str();

 TString HistName = "PDFvsQ_x_" + xstring + "_" + PDFNameMap[iPDF] + "_iSet_" + PDFErrorIndex[iPDF] + "_" + FlavorNameMap[flavor];
 h1 = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinCenter = h1->GetBinCenter(ibin);
   h1->SetBinContent(ibin, Getf(iPDF, flavor, x, BinCenter));
   h1->SetBinError(ibin, 0.0);
 }

#endif

 return h1;
}

double OldPDFFigure::Getf(int iPDF, int flavor, double x, double Q, int iSet)
{
 double Value;
 
#ifdef USE_LHAPDF
 if(abs(flavor) == 1 || abs(flavor) == 2 || abs(flavor) == 3 || abs(flavor) == 4 || abs(flavor) == 5){//d, u, s, c, b
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(flavor, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(flavor, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 0){//gluon
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(21, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(21, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 6){//dbar
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 7){//ubar
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 8){//sbar
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(-3, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-3, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 9){//cbar
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(-4, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-4, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 10){//bbar
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(-5, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-5, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 11){//d valance
   if(x < 1.0){ 
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(1, x, muF * Q) / x - myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(1, x, muF * Q) / x - CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 12){//u valance
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = myPDF[iPDF]->xfxQ(2, x, muF * Q) / x - myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x;
     if(PDFType[iPDF] == "CTEQ") Value = CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(2, x, muF * Q) / x - CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x;
   }
   else Value = 0.0;
 }
 if(flavor == 13){//dbar / d valance
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(1, x, muF * Q) / x - myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(1, x, muF * Q) / x - CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 14){//ubar / u valance
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(2, x, muF * Q) / x - myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(2, x, muF * Q) / x - CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 15){//ubar / dbar
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 16){//d / dbar
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(1, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(1, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 17){//u / ubar
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(2, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(2, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 18){//dbar / d
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(1, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(1, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 19){//ubar / u 
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x) / (myPDF[iPDF]->xfxQ(2, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x) / (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(2, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 if(flavor == 20){//dv - uv
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = ((myPDF[iPDF]->xfxQ(1, x, muF * Q) / x) - (myPDF[iPDF]->xfxQ(-1, x, muF * Q) / x))
                                         - ((myPDF[iPDF]->xfxQ(2, x, muF * Q) / x) - (myPDF[iPDF]->xfxQ(-2, x, muF * Q) / x));
     if(PDFType[iPDF] == "CTEQ") Value = ((CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(1, x, muF * Q) / x) - (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-1, x, muF * Q) / x))
                                       - ((CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(2, x, muF * Q) / x) - (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-2, x, muF * Q) / x));
   }
 }
 if(flavor == 40){//s - sbar
   if(x < 1.0){
     if(PDFType[iPDF] == "LHAPDF") Value = (myPDF[iPDF]->xfxQ(3, x, muF * Q) / x) - (myPDF[iPDF]->xfxQ(-3, x, muF * Q) / x);
     if(PDFType[iPDF] == "CTEQ") Value = (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(3, x, muF * Q) / x) - (CTPDFIndex[make_pair(PDFNameMap[iPDF], iSet)]->xfxQ(-3, x, muF * Q) / x);
   }
   else Value = 0.0;
 }
 
#endif

 if(!isfinite(Value)) return 0.0;
 
 return Value;
}

double OldPDFFigure::Getxf(int iPDF, int flavor, double x, double Q)
{
 double Value;
#ifdef USE_LHAPDF
 if(x < 1.0) Value = myPDF[iPDF]->xfxQ(flavor, x, muF * Q);
 else Value = 0.0;
#endif

 if(!isfinite(Value)) return 0.0;

 return Value;
}

double OldPDFFigure::GetfError(TString PDFName, int flavor, double x, double Q, TString ErrorType)
{
 double Error = 0.0;
 double Error2 = 0.0;

 vector<double> Values(CTPDFnSet[PDFName]);

 for(int i = 0; i < Values.size(); i++){
   Values.at(i) = Getf(PDFNameIndex[PDFName], flavor, x, Q, i);
   //cout<<i<<":  "<<Values.at(i)<<endl;
 }

 if(ErrorType == "Symmetry"){
   for(int i = 1; i < (Values.size() - 1) / 2; i++){
     Error2 += (Values.at(2 * i) - Values.at(2 * i - 1)) * (Values.at(2 * i) - Values.at(2 * i - 1)) / 4.0;
   }

   Error = fabs(sqrt(Error2) / Values.at(0)) / 1.645;
 }

 return Error;
}

void OldPDFFigure::DefineCombination()
{
 FlavorNameMap[0] = "gluon";
 FlavorNameMap[1] = "d";
 FlavorNameMap[2] = "u";
 FlavorNameMap[3] = "s";
 FlavorNameMap[4] = "c";
 FlavorNameMap[5] = "b";
 FlavorNameMap[-1] = "dbar";
 FlavorNameMap[-2] = "ubar";
 FlavorNameMap[-3] = "sbar";
 FlavorNameMap[-4] = "cbar";
 FlavorNameMap[-5] = "bbar";

 FlavorNameMap[6] = "dbar";
 FlavorNameMap[7] = "ubar";
 FlavorNameMap[8] = "sbar";
 FlavorNameMap[9] = "cbar";
 FlavorNameMap[10] = "bbar";
 FlavorNameMap[11] = "dv";
 FlavorNameMap[12] = "uv";
 FlavorNameMap[13] = "dbodv";
 FlavorNameMap[14] = "ubouv";
 FlavorNameMap[15] = "ubodb";
 FlavorNameMap[16] = "dodb";
 FlavorNameMap[17] = "uoub";
 FlavorNameMap[18] = "dbod";
 FlavorNameMap[19] = "ubou";
 FlavorNameMap[20] = "dvmuv";
 FlavorNameMap[40] = (TString)"sv";
}

void OldPDFFigure::openFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
 hf->cd();
}

void OldPDFFigure::SaveFile()
{
 hf->cd();
 hf->Write();
 hf->Close();
}

#endif
