#ifndef DilutionFitting_FlavorSearch_h
#define DilutionFitting_FlavorSearch_h

#include <iostream>
#include <dirent.h>
#include <cstring>
#include "RootCommon.h"
#include "Tools/Tools.h"

#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif
#include "CTEQHelper/pdsReader.h"

#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

vector<double> *global_Observable;
int global_nSet;

map<tuple<int, int, int>, double> *global_uPDF;
map<tuple<int, int, int>, double> *global_dPDF;
map<tuple<int, int, int>, double> *global_sPDF;
map<tuple<int, int, int>, double> *global_cPDF;
map<tuple<int, int, int>, double> *global_bPDF;
map<tuple<int, int, int>, double> *global_gPDF;
map<tuple<int, int, int>, double> *global_ubarPDF;
map<tuple<int, int, int>, double> *global_dbarPDF;
map<tuple<int, int, int>, double> *global_sbarPDF;
map<tuple<int, int, int>, double> *global_cbarPDF;
map<tuple<int, int, int>, double> *global_bbarPDF;

int global_ix;
int global_iq;

double MinChi2_flavor = 100000.0;

void FlavorSearchFitting(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 map<tuple<int, int, int>, double> uPDF = (*global_uPDF);
 map<tuple<int, int, int>, double> dPDF = (*global_dPDF);
 map<tuple<int, int, int>, double> sPDF = (*global_sPDF);
 map<tuple<int, int, int>, double> cPDF = (*global_cPDF);
 map<tuple<int, int, int>, double> bPDF = (*global_bPDF);
 map<tuple<int, int, int>, double> gPDF = (*global_gPDF);
 map<tuple<int, int, int>, double> ubarPDF = (*global_ubarPDF);
 map<tuple<int, int, int>, double> dbarPDF = (*global_dbarPDF);
 map<tuple<int, int, int>, double> sbarPDF = (*global_sbarPDF);
 map<tuple<int, int, int>, double> cbarPDF = (*global_cbarPDF);
 map<tuple<int, int, int>, double> bbarPDF = (*global_bbarPDF);

 int ix = global_ix;
 int iq = global_iq;

 vector<double> FlavorSet(global_nSet + 1);

 for(int i = 0; i <= global_nSet; i++){
   if(fabs(par[6] * uPDF[make_tuple(i, ix, iq)]
     + par[7] * dPDF[make_tuple(i, ix, iq)]
     + par[8] * sPDF[make_tuple(i, ix, iq)]
     + par[9] * cPDF[make_tuple(i, ix, iq)]
     + par[10] * bPDF[make_tuple(i, ix, iq)]) > 1e-10){
     FlavorSet.at(i) = 
        (par[0] * ubarPDF[make_tuple(i, ix, iq)]
       + par[1] * dbarPDF[make_tuple(i, ix, iq)]
       + par[2] * sbarPDF[make_tuple(i, ix, iq)]
       + par[3] * cbarPDF[make_tuple(i, ix, iq)]
       + par[4] * bbarPDF[make_tuple(i, ix, iq)]
       + par[5] * gPDF[make_tuple(i, ix, iq)]) / 
        (par[6] * uPDF[make_tuple(i, ix, iq)]
       + par[7] * dPDF[make_tuple(i, ix, iq)]
       + par[8] * sPDF[make_tuple(i, ix, iq)]
       + par[9] * cPDF[make_tuple(i, ix, iq)]
       + par[10] * bPDF[make_tuple(i, ix, iq)])
       + par[11] * uPDF[make_tuple(i, ix, iq)]
       + par[12] * dPDF[make_tuple(i, ix, iq)]
       + par[13] * sPDF[make_tuple(i, ix, iq)]
       + par[14] * cPDF[make_tuple(i, ix, iq)]
       + par[15] * bPDF[make_tuple(i, ix, iq)]
       + par[16] * ubarPDF[make_tuple(i, ix, iq)]
       + par[17] * dbarPDF[make_tuple(i, ix, iq)]
       + par[18] * sbarPDF[make_tuple(i, ix, iq)]
       + par[19] * cbarPDF[make_tuple(i, ix, iq)]
       + par[20] * bbarPDF[make_tuple(i, ix, iq)]
       + par[21] * gPDF[make_tuple(i, ix, iq)];
   }
 }

 vector<double> FlavorCombination(global_nSet / 2);
 vector<double> Observable(global_nSet / 2);
 for(int i = 1; i <= global_nSet / 2; i++){
   Observable.at(i - 1) = global_Observable->at(2 * i - 1) - global_Observable->at(2 * i);
   FlavorCombination.at(i - 1) = FlavorSet.at(2 * i - 1) - FlavorSet.at(2 * i);
 }

 double Correlation = CosPhi(FlavorCombination, Observable);

 f = 1000.0 * (1 - fabs(Correlation));
 if(f < MinChi2_flavor) MinChi2_flavor = f;

 cout<<"Min Chi2 = "<<MinChi2_flavor<<endl;

}

class FlavorSearch
{
 public:

 TMinuitHelper* myMinuit;

#ifdef USE_LHAPDF
 map<pair<TString, int>, LHAPDF::PDF*> PDF;
#endif
 map<pair<TString, int>, pdsReader*> CTPDF;

 TString PDFName;
 map<TString, TString> PDFType;
 map<TString, int> PDFnSet;

 map<tuple<int, int, int>, double> uPDF;
 map<tuple<int, int, int>, double> dPDF;
 map<tuple<int, int, int>, double> sPDF;
 map<tuple<int, int, int>, double> cPDF;
 map<tuple<int, int, int>, double> bPDF;
 map<tuple<int, int, int>, double> gPDF;
 map<tuple<int, int, int>, double> ubarPDF;
 map<tuple<int, int, int>, double> dbarPDF;
 map<tuple<int, int, int>, double> sbarPDF;
 map<tuple<int, int, int>, double> cbarPDF;
 map<tuple<int, int, int>, double> bbarPDF;

 map<int, double> xMap;
 map<double, int> xIndex;
 map<int, double> QMap;
 map<double, int> QIndex;

 vector<double> LogBin;
 double* Par;
 double* ParError;
 int NPar = 22;
 vector<double> isFixed;
 vector<double> InitialValue;

 FlavorSearch();
 virtual void InitialPDFAll(TString PDFName, int nSet);
 virtual void InitialCTEQPDF(TString GivenName, TString PDFFile, int iSet);
 virtual void InitialCTEQPDFAll(TString GivenName, vector<TString> PDFFiles);
 virtual void InitialCTEQPDF(TString GivenName, pdsReader* pdf, int iSet);
 virtual void InitialCTEQPDFAll(TString GivenName, vector<pdsReader *> PDFFiles);
 virtual void InitialCTEQPDFAll(TString GivenName, TString DirectoryName);

 virtual void InitialAllFlavors();

 vector<double> Observable;
 virtual void InputObservable(vector<double> Observable){this->Observable = Observable; global_Observable = &(this->Observable);};

 virtual void TurnOffAll(){
   for(int i = 0; i < NPar; i++){
     isFixed.at(i) = 0.0; InitialValue.at(i) = 0.0;
   }
   InitialValue.at(6) = 1.0;
 }
 virtual void FixParameter(int i, double par){isFixed.at(i) = 0.0; InitialValue.at(i) = par;};
 virtual void FitParameter(int i){isFixed.at(i) = 0.5;};
 virtual void Fit(int ix, int iq);
 virtual double CalculateCombination(int iSet, double x, double Q);
 virtual double CalculateCorrelation(double x, double Q);
 virtual void DrawCorrelation(TString subName = "");
 virtual void IndividualContribution();

 virtual double CalculateSpecialCombination(int iSet, double x, double Q);
 virtual double CalculateSpecialCorrelation(double x, double Q);
 virtual void DrawSpecialCorrelation(TString subName = "");

 map<double, vector<int>> EightCombination;
 map<double, vector<int>> SevenCombination;
 map<double, vector<int>> SixCombination;
 map<double, vector<int>> FiveCombination;
 map<double, vector<int>> FourCombination;
 virtual void ScanAllCombinations();

 virtual void ResetParameters(){
   Par = new double[22];
   ParError = new double[22];
   for(int i = 0; i < 22; i++){
     Par[i] = 0.0;
   }
   Par[6] = 1.0;
 }

 TString FixComb = "";
 virtual void SetParameter(int i, double par){
   Par[i] = par;
   FixComb = "Fix";
 }

 virtual double u(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x;
   return Value;
 }
 virtual double d(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x;
   return Value;
 }
 virtual double s(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(3, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(3, x, Q) / x;
   return Value;
 }
 virtual double c(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(4, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(4, x, Q) / x;
   return Value;
 }
 virtual double b(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(5, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(5, x, Q) / x;
   return Value;
 }
 virtual double g(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(21, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(21, x, Q) / x;
   return Value;
 }
 virtual double ubar(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x;
   return Value;
 }
 virtual double dbar(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x;
   return Value;
 }
 virtual double sbar(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(-3, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-3, x, Q) / x;
   return Value;
 }
 virtual double cbar(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(-4, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-4, x, Q) / x;
   return Value;
 }
 virtual double bbar(int iSet, double x, double Q){
   double Value = 0.0;
#ifdef USE_LHAPDF
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(-5, x, Q) / x;
#endif
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-5, x, Q) / x;
   return Value;
 }

 TFile* hf;
 bool isLinkFile = false;
 virtual void openFile(TString name){hf = new TFile(name, "RECREATE"); hf->cd(); isLinkFile = true;}
 virtual void LinkFile(TFile* file){hf = file; hf->cd(); isLinkFile = true;}
 virtual void SaveFile(){hf->cd(); hf->Write(); hf->Close();}

};
#endif
