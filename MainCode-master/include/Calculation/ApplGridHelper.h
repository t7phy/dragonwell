#ifndef Calculation_ApplGridHelper_h
#define Calculation_ApplGridHelper_h

#include <iostream>
#include <string>
#include <vector>

#ifdef USE_APPLGRID
#include "appl_grid/appl_grid.h"
#include "appl_grid/appl_timer.h"
#endif

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "CTEQHelper/HoppetInterface.h"
#include "Calculation/QCDSet.h"

// lhapdf routines
#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
extern "C" void evolvepdf_(const double& , const double& , double* );
extern "C" double alphaspdf_(const double& Q);

extern "C" void cteqevolvepdf_(const double& , const double& , double* );
extern "C" void cteqevolvepdfpbar_(const double& , const double& , double* );
extern "C" void cteqevolvepdfcu_(const double& , const double& , double* );
extern "C" double cteqalphaspdf_(const double& Q);

extern "C" void cteqtableevolvepdf_(const double& , const double& , double* );
extern "C" void cteqtableevolvepdfpbar_(const double& , const double& , double* );
extern "C" void cteqtableevolvepdfcu_(const double& , const double& , double* );
extern "C" double cteqtablealphaspdf_(const double& Q);

extern "C" void threadpdf1_(const double& , const double& , double* );
extern "C" void threadpdf2_(const double& , const double& , double* );
extern "C" void threadpdf3_(const double& , const double& , double* );
extern "C" void threadpdf4_(const double& , const double& , double* );
extern "C" void threadpdf5_(const double& , const double& , double* );
extern "C" void threadpdf6_(const double& , const double& , double* );
extern "C" void threadpdf7_(const double& , const double& , double* );
extern "C" void threadpdf8_(const double& , const double& , double* );
extern "C" void threadpdf9_(const double& , const double& , double* );
extern "C" void threadpdf10_(const double& , const double& , double* );
extern "C" void threadpdf11_(const double& , const double& , double* );
extern "C" void threadpdf12_(const double& , const double& , double* );
extern "C" void threadpdf13_(const double& , const double& , double* );
extern "C" void threadpdf14_(const double& , const double& , double* );
extern "C" void threadpdf15_(const double& , const double& , double* );
extern "C" void threadpdf16_(const double& , const double& , double* );
extern "C" void threadpdf17_(const double& , const double& , double* );
extern "C" void threadpdf18_(const double& , const double& , double* );
extern "C" void threadpdf19_(const double& , const double& , double* );
extern "C" void threadpdf20_(const double& , const double& , double* );
extern "C" void threadpdf21_(const double& , const double& , double* );
extern "C" void threadpdf22_(const double& , const double& , double* );
extern "C" void threadpdf23_(const double& , const double& , double* );
extern "C" void threadpdf24_(const double& , const double& , double* );
extern "C" void threadpdf25_(const double& , const double& , double* );
extern "C" void threadpdf26_(const double& , const double& , double* );
extern "C" void threadpdf27_(const double& , const double& , double* );
extern "C" void threadpdf28_(const double& , const double& , double* );
extern "C" void threadpdf29_(const double& , const double& , double* );
extern "C" void threadpdf30_(const double& , const double& , double* );
extern "C" void threadpdf31_(const double& , const double& , double* );
extern "C" void threadpdf32_(const double& , const double& , double* );
extern "C" void threadpdf33_(const double& , const double& , double* );
extern "C" void threadpdf34_(const double& , const double& , double* );
extern "C" void threadpdf35_(const double& , const double& , double* );
extern "C" void threadpdf36_(const double& , const double& , double* );
extern "C" void threadpdf37_(const double& , const double& , double* );
extern "C" void threadpdf38_(const double& , const double& , double* );
extern "C" void threadpdf39_(const double& , const double& , double* );
extern "C" void threadpdf40_(const double& , const double& , double* );
extern "C" void threadpdf41_(const double& , const double& , double* );
extern "C" void threadpdf42_(const double& , const double& , double* );
extern "C" void threadpdf43_(const double& , const double& , double* );
extern "C" void threadpdf44_(const double& , const double& , double* );
extern "C" void threadpdf45_(const double& , const double& , double* );
extern "C" void threadpdf46_(const double& , const double& , double* );
extern "C" void threadpdf47_(const double& , const double& , double* );
extern "C" void threadpdf48_(const double& , const double& , double* );
extern "C" void threadpdf49_(const double& , const double& , double* );
extern "C" void threadpdf50_(const double& , const double& , double* );
extern "C" void threadpdf51_(const double& , const double& , double* );
extern "C" void threadpdf52_(const double& , const double& , double* );
extern "C" void threadpdf53_(const double& , const double& , double* );
extern "C" void threadpdf54_(const double& , const double& , double* );
extern "C" void threadpdf55_(const double& , const double& , double* );
extern "C" void threadpdf56_(const double& , const double& , double* );
extern "C" void threadpdf57_(const double& , const double& , double* );
extern "C" void threadpdf58_(const double& , const double& , double* );
extern "C" void threadpdf59_(const double& , const double& , double* );
extern "C" void threadpdf60_(const double& , const double& , double* );
extern "C" void threadpdf61_(const double& , const double& , double* );
extern "C" void threadpdf62_(const double& , const double& , double* );
extern "C" void threadpdf63_(const double& , const double& , double* );
extern "C" void threadpdf64_(const double& , const double& , double* );
extern "C" void threadpdf65_(const double& , const double& , double* );
extern "C" void threadpdf66_(const double& , const double& , double* );
extern "C" void threadpdf67_(const double& , const double& , double* );
extern "C" void threadpdf68_(const double& , const double& , double* );
extern "C" void threadpdf69_(const double& , const double& , double* );
extern "C" void threadpdf70_(const double& , const double& , double* );
extern "C" void threadpdf71_(const double& , const double& , double* );
extern "C" void threadpdf72_(const double& , const double& , double* );
extern "C" void threadpdf73_(const double& , const double& , double* );
extern "C" void threadpdf74_(const double& , const double& , double* );
extern "C" void threadpdf75_(const double& , const double& , double* );
extern "C" void threadpdf76_(const double& , const double& , double* );
extern "C" void threadpdf77_(const double& , const double& , double* );
extern "C" void threadpdf78_(const double& , const double& , double* );
extern "C" void threadpdf79_(const double& , const double& , double* );
extern "C" void threadpdf80_(const double& , const double& , double* );
extern "C" void threadpdf81_(const double& , const double& , double* );
extern "C" void threadpdf82_(const double& , const double& , double* );
extern "C" void threadpdf83_(const double& , const double& , double* );
extern "C" void threadpdf84_(const double& , const double& , double* );
extern "C" void threadpdf85_(const double& , const double& , double* );
extern "C" void threadpdf86_(const double& , const double& , double* );
extern "C" void threadpdf87_(const double& , const double& , double* );
extern "C" void threadpdf88_(const double& , const double& , double* );
extern "C" void threadpdf89_(const double& , const double& , double* );
extern "C" void threadpdf90_(const double& , const double& , double* );
extern "C" void threadpdf91_(const double& , const double& , double* );
extern "C" void threadpdf92_(const double& , const double& , double* );
extern "C" void threadpdf93_(const double& , const double& , double* );
extern "C" void threadpdf94_(const double& , const double& , double* );
extern "C" void threadpdf95_(const double& , const double& , double* );
extern "C" void threadpdf96_(const double& , const double& , double* );
extern "C" void threadpdf97_(const double& , const double& , double* );
extern "C" void threadpdf98_(const double& , const double& , double* );
extern "C" void threadpdf99_(const double& , const double& , double* );
extern "C" void threadpdf100_(const double& , const double& , double* );

extern "C" void threadpdfpbar1_(const double& , const double& , double* );
extern "C" void threadpdfpbar2_(const double& , const double& , double* );
extern "C" void threadpdfpbar3_(const double& , const double& , double* );
extern "C" void threadpdfpbar4_(const double& , const double& , double* );
extern "C" void threadpdfpbar5_(const double& , const double& , double* );
extern "C" void threadpdfpbar6_(const double& , const double& , double* );
extern "C" void threadpdfpbar7_(const double& , const double& , double* );
extern "C" void threadpdfpbar8_(const double& , const double& , double* );
extern "C" void threadpdfpbar9_(const double& , const double& , double* );
extern "C" void threadpdfpbar10_(const double& , const double& , double* );
extern "C" void threadpdfpbar11_(const double& , const double& , double* );
extern "C" void threadpdfpbar12_(const double& , const double& , double* );
extern "C" void threadpdfpbar13_(const double& , const double& , double* );
extern "C" void threadpdfpbar14_(const double& , const double& , double* );
extern "C" void threadpdfpbar15_(const double& , const double& , double* );
extern "C" void threadpdfpbar16_(const double& , const double& , double* );
extern "C" void threadpdfpbar17_(const double& , const double& , double* );
extern "C" void threadpdfpbar18_(const double& , const double& , double* );
extern "C" void threadpdfpbar19_(const double& , const double& , double* );
extern "C" void threadpdfpbar20_(const double& , const double& , double* );
extern "C" void threadpdfpbar21_(const double& , const double& , double* );
extern "C" void threadpdfpbar22_(const double& , const double& , double* );
extern "C" void threadpdfpbar23_(const double& , const double& , double* );
extern "C" void threadpdfpbar24_(const double& , const double& , double* );
extern "C" void threadpdfpbar25_(const double& , const double& , double* );
extern "C" void threadpdfpbar26_(const double& , const double& , double* );
extern "C" void threadpdfpbar27_(const double& , const double& , double* );
extern "C" void threadpdfpbar28_(const double& , const double& , double* );
extern "C" void threadpdfpbar29_(const double& , const double& , double* );
extern "C" void threadpdfpbar30_(const double& , const double& , double* );
extern "C" void threadpdfpbar31_(const double& , const double& , double* );
extern "C" void threadpdfpbar32_(const double& , const double& , double* );
extern "C" void threadpdfpbar33_(const double& , const double& , double* );
extern "C" void threadpdfpbar34_(const double& , const double& , double* );
extern "C" void threadpdfpbar35_(const double& , const double& , double* );
extern "C" void threadpdfpbar36_(const double& , const double& , double* );
extern "C" void threadpdfpbar37_(const double& , const double& , double* );
extern "C" void threadpdfpbar38_(const double& , const double& , double* );
extern "C" void threadpdfpbar39_(const double& , const double& , double* );
extern "C" void threadpdfpbar40_(const double& , const double& , double* );
extern "C" void threadpdfpbar41_(const double& , const double& , double* );
extern "C" void threadpdfpbar42_(const double& , const double& , double* );
extern "C" void threadpdfpbar43_(const double& , const double& , double* );
extern "C" void threadpdfpbar44_(const double& , const double& , double* );
extern "C" void threadpdfpbar45_(const double& , const double& , double* );
extern "C" void threadpdfpbar46_(const double& , const double& , double* );
extern "C" void threadpdfpbar47_(const double& , const double& , double* );
extern "C" void threadpdfpbar48_(const double& , const double& , double* );
extern "C" void threadpdfpbar49_(const double& , const double& , double* );
extern "C" void threadpdfpbar50_(const double& , const double& , double* );
extern "C" void threadpdfpbar51_(const double& , const double& , double* );
extern "C" void threadpdfpbar52_(const double& , const double& , double* );
extern "C" void threadpdfpbar53_(const double& , const double& , double* );
extern "C" void threadpdfpbar54_(const double& , const double& , double* );
extern "C" void threadpdfpbar55_(const double& , const double& , double* );
extern "C" void threadpdfpbar56_(const double& , const double& , double* );
extern "C" void threadpdfpbar57_(const double& , const double& , double* );
extern "C" void threadpdfpbar58_(const double& , const double& , double* );
extern "C" void threadpdfpbar59_(const double& , const double& , double* );
extern "C" void threadpdfpbar60_(const double& , const double& , double* );
extern "C" void threadpdfpbar61_(const double& , const double& , double* );
extern "C" void threadpdfpbar62_(const double& , const double& , double* );
extern "C" void threadpdfpbar63_(const double& , const double& , double* );
extern "C" void threadpdfpbar64_(const double& , const double& , double* );
extern "C" void threadpdfpbar65_(const double& , const double& , double* );
extern "C" void threadpdfpbar66_(const double& , const double& , double* );
extern "C" void threadpdfpbar67_(const double& , const double& , double* );
extern "C" void threadpdfpbar68_(const double& , const double& , double* );
extern "C" void threadpdfpbar69_(const double& , const double& , double* );
extern "C" void threadpdfpbar70_(const double& , const double& , double* );
extern "C" void threadpdfpbar71_(const double& , const double& , double* );
extern "C" void threadpdfpbar72_(const double& , const double& , double* );
extern "C" void threadpdfpbar73_(const double& , const double& , double* );
extern "C" void threadpdfpbar74_(const double& , const double& , double* );
extern "C" void threadpdfpbar75_(const double& , const double& , double* );
extern "C" void threadpdfpbar76_(const double& , const double& , double* );
extern "C" void threadpdfpbar77_(const double& , const double& , double* );
extern "C" void threadpdfpbar78_(const double& , const double& , double* );
extern "C" void threadpdfpbar79_(const double& , const double& , double* );
extern "C" void threadpdfpbar80_(const double& , const double& , double* );
extern "C" void threadpdfpbar81_(const double& , const double& , double* );
extern "C" void threadpdfpbar82_(const double& , const double& , double* );
extern "C" void threadpdfpbar83_(const double& , const double& , double* );
extern "C" void threadpdfpbar84_(const double& , const double& , double* );
extern "C" void threadpdfpbar85_(const double& , const double& , double* );
extern "C" void threadpdfpbar86_(const double& , const double& , double* );
extern "C" void threadpdfpbar87_(const double& , const double& , double* );
extern "C" void threadpdfpbar88_(const double& , const double& , double* );
extern "C" void threadpdfpbar89_(const double& , const double& , double* );
extern "C" void threadpdfpbar90_(const double& , const double& , double* );
extern "C" void threadpdfpbar91_(const double& , const double& , double* );
extern "C" void threadpdfpbar92_(const double& , const double& , double* );
extern "C" void threadpdfpbar93_(const double& , const double& , double* );
extern "C" void threadpdfpbar94_(const double& , const double& , double* );
extern "C" void threadpdfpbar95_(const double& , const double& , double* );
extern "C" void threadpdfpbar96_(const double& , const double& , double* );
extern "C" void threadpdfpbar97_(const double& , const double& , double* );
extern "C" void threadpdfpbar98_(const double& , const double& , double* );
extern "C" void threadpdfpbar99_(const double& , const double& , double* );
extern "C" void threadpdfpbar100_(const double& , const double& , double* );

extern "C" double threadalphas1_(const double& Q);
extern "C" double threadalphas2_(const double& Q);
extern "C" double threadalphas3_(const double& Q);
extern "C" double threadalphas4_(const double& Q);
extern "C" double threadalphas5_(const double& Q);
extern "C" double threadalphas6_(const double& Q);
extern "C" double threadalphas7_(const double& Q);
extern "C" double threadalphas8_(const double& Q);
extern "C" double threadalphas9_(const double& Q);
extern "C" double threadalphas10_(const double& Q);
extern "C" double threadalphas11_(const double& Q);
extern "C" double threadalphas12_(const double& Q);
extern "C" double threadalphas13_(const double& Q);
extern "C" double threadalphas14_(const double& Q);
extern "C" double threadalphas15_(const double& Q);
extern "C" double threadalphas16_(const double& Q);
extern "C" double threadalphas17_(const double& Q);
extern "C" double threadalphas18_(const double& Q);
extern "C" double threadalphas19_(const double& Q);
extern "C" double threadalphas20_(const double& Q);
extern "C" double threadalphas21_(const double& Q);
extern "C" double threadalphas22_(const double& Q);
extern "C" double threadalphas23_(const double& Q);
extern "C" double threadalphas24_(const double& Q);
extern "C" double threadalphas25_(const double& Q);
extern "C" double threadalphas26_(const double& Q);
extern "C" double threadalphas27_(const double& Q);
extern "C" double threadalphas28_(const double& Q);
extern "C" double threadalphas29_(const double& Q);
extern "C" double threadalphas30_(const double& Q);
extern "C" double threadalphas31_(const double& Q);
extern "C" double threadalphas32_(const double& Q);
extern "C" double threadalphas33_(const double& Q);
extern "C" double threadalphas34_(const double& Q);
extern "C" double threadalphas35_(const double& Q);
extern "C" double threadalphas36_(const double& Q);
extern "C" double threadalphas37_(const double& Q);
extern "C" double threadalphas38_(const double& Q);
extern "C" double threadalphas39_(const double& Q);
extern "C" double threadalphas40_(const double& Q);
extern "C" double threadalphas41_(const double& Q);
extern "C" double threadalphas42_(const double& Q);
extern "C" double threadalphas43_(const double& Q);
extern "C" double threadalphas44_(const double& Q);
extern "C" double threadalphas45_(const double& Q);
extern "C" double threadalphas46_(const double& Q);
extern "C" double threadalphas47_(const double& Q);
extern "C" double threadalphas48_(const double& Q);
extern "C" double threadalphas49_(const double& Q);
extern "C" double threadalphas50_(const double& Q);
extern "C" double threadalphas51_(const double& Q);
extern "C" double threadalphas52_(const double& Q);
extern "C" double threadalphas53_(const double& Q);
extern "C" double threadalphas54_(const double& Q);
extern "C" double threadalphas55_(const double& Q);
extern "C" double threadalphas56_(const double& Q);
extern "C" double threadalphas57_(const double& Q);
extern "C" double threadalphas58_(const double& Q);
extern "C" double threadalphas59_(const double& Q);
extern "C" double threadalphas60_(const double& Q);
extern "C" double threadalphas61_(const double& Q);
extern "C" double threadalphas62_(const double& Q);
extern "C" double threadalphas63_(const double& Q);
extern "C" double threadalphas64_(const double& Q);
extern "C" double threadalphas65_(const double& Q);
extern "C" double threadalphas66_(const double& Q);
extern "C" double threadalphas67_(const double& Q);
extern "C" double threadalphas68_(const double& Q);
extern "C" double threadalphas69_(const double& Q);
extern "C" double threadalphas70_(const double& Q);
extern "C" double threadalphas71_(const double& Q);
extern "C" double threadalphas72_(const double& Q);
extern "C" double threadalphas73_(const double& Q);
extern "C" double threadalphas74_(const double& Q);
extern "C" double threadalphas75_(const double& Q);
extern "C" double threadalphas76_(const double& Q);
extern "C" double threadalphas77_(const double& Q);
extern "C" double threadalphas78_(const double& Q);
extern "C" double threadalphas79_(const double& Q);
extern "C" double threadalphas80_(const double& Q);
extern "C" double threadalphas81_(const double& Q);
extern "C" double threadalphas82_(const double& Q);
extern "C" double threadalphas83_(const double& Q);
extern "C" double threadalphas84_(const double& Q);
extern "C" double threadalphas85_(const double& Q);
extern "C" double threadalphas86_(const double& Q);
extern "C" double threadalphas87_(const double& Q);
extern "C" double threadalphas88_(const double& Q);
extern "C" double threadalphas89_(const double& Q);
extern "C" double threadalphas90_(const double& Q);
extern "C" double threadalphas91_(const double& Q);
extern "C" double threadalphas92_(const double& Q);
extern "C" double threadalphas93_(const double& Q);
extern "C" double threadalphas94_(const double& Q);
extern "C" double threadalphas95_(const double& Q);
extern "C" double threadalphas96_(const double& Q);
extern "C" double threadalphas97_(const double& Q);
extern "C" double threadalphas98_(const double& Q);
extern "C" double threadalphas99_(const double& Q);
extern "C" double threadalphas100_(const double& Q);

#ifdef Calculation_ApplGridHelper_cxx
void (*_pdf)(const double& x, const double& Q, double* f) = 0;
extern "C" void evolvepdfpbar_(const double& x, const double& Q, double* f){
    double xf[13];
    _pdf( x, Q, xf );
    for ( int i = 0 ; i < 13 ; i++ ) f[i] = xf[12 - i];
}
extern "C" void evolvepdfcu_(const double& x, const double& Q, double* f){
    double xf[13];
    _pdf( x, Q, xf );
    double neutronpdf[13];

    for ( int i = -6 ; i <= 6 ; i++ ){
      int in;
      if(i == 1) in = 2;
      else if(i == 2) in = 1;
      else if(i == -1) in = -2;
      else if(i == -2) in = -1;
      else in = i;
      neutronpdf[in + 6] = xf[i + 6];
    }

    for ( int i = -6 ; i <= 6 ; i++ ){
      f[i + 6] = (29.0 * xf[i + 6] + 35.0 * neutronpdf[i + 6]) / 64.0;
    }
}
#endif

#endif

using namespace std;

class ApplGridHelper : public QCDSet
{
 public:

 int iThread = 0;

#ifdef USE_APPLGRID
 map<TString, appl::grid*> ApplGridMap;
#endif

 map<TString, bool> isInitial;

 TString PDFName;
 int iSet;

 int order = 1;

 QCDSet* m_qcd;

 TString SavedGridName = "";
 TH1D* TheoryResult;
 TString TheoryResultName;

 vector<double> appl_xsec;

 vector<double> ckm = {0.97427,0.22534,0.00351,0.2252,0.97344,0.0412,0.,0.,0.};

 ApplGridHelper();
 virtual void InitialPDF(TString PDFName, int iSet);
 virtual void InitialCTEQPDF(pdsReader* pdf);
 virtual void InitialCTEQPDF(TString PDFFile);
 virtual void InitialPDFbyHand(HoppetInterface* h);

 virtual void DefaultConvolute(TString GridName);
 virtual void DefaultConvoluteppbar(TString GridName);
 virtual void DefaultConvolutepCu(TString GridName);
 virtual void InitialGrid(TString GridName);

 virtual void InitialHistName(TString name);
 double BinLeftCut = -99999.0, BinRightCut = 99999.0;
 bool isSetCut = false;
 virtual void SetCut(double left, double right){BinLeftCut = left; BinRightCut = right; isSetCut = true;}
 virtual void DefaultConvoluteMacro(TString GridName, vector<double> &result);
 virtual void DefaultConvoluteppbarMacro(TString GridName, vector<double> &result);

 virtual void ThreadConvoluteMacro();
 virtual void ThreadConvoluteppbarMacro();

 virtual TString GetHistName(){return TheoryResultName;};
 virtual TH1D* GetResultPtr(){return TheoryResult;};
 virtual void DeleteResult(){delete TheoryResult;}

 virtual TH1D* Convolute(TString GridName, TString KFactorName = "");
 virtual TH1D* Convoluteppbar(TString GridName, TString KFactorName = "");
 virtual TH1D* ConvoluteSubProc(TString GridName, int SubProc, TString KFactorName = "");
 virtual TH1D* ConvoluteppbarSubProc(TString GridName, int SubProc, TString KFactorName = "");

 virtual TH1D* ConvoluteBasic(TString GridName, TString HistName, TString KFactorName = "");
 virtual TH1D* ConvoluteppbarBasic(TString GridName, TString HistName, TString KFactorName = "");
 virtual TH1D* ConvoluteSubProcBasic(TString GridName, TString SubProc, TString HistName, TString KFactorName = "");
 virtual TH1D* ConvoluteppbarSubProcBasic(TString GridName, TString SubProc, TString HistName, TString KFactorName = "");
 virtual TH1D* ConvoluteCombineSubProcBasic(TString GridName, vector<TString> SubProcs, TString HistName, TString KFactorName = "");
 virtual TH1D* ConvoluteppbarCombineSubProcBasic(TString GridName, vector<TString> SubProcs, TString HistName, TString KFactorName = "");

 map<TString, vector<double>> KFactorMap;
 virtual void ReadKFactor(TString FileName);

 map<TString, TH1D*> OneMinusTwoD_uu;
 map<TString, TH1D*> OneMinusTwoD_dd;
 map<TString, TH1D*> RelativeCrossSection_uu;
 map<TString, TH1D*> RelativeCrossSection_dd;

 virtual void CalcP0(TString GridNameYP, TString GridNameYM, TString subName, double& P0u, double& P0d, vector<TString> KFactors = {});
 virtual void CalcP0ppbar(TString GridName, TString subName, double& P0u, double& P0d, vector<TString> KFactors = {});
 virtual double GetP0(TH1D* right, TH1D* wrong, TH1D* total);

 virtual TH1D* ConvoluteAFB(TString GridNameForward, TString GridNameBackward, TString subName, int flavor = -1);
 virtual TH1D* ConvoluteDilution(TString GridNameYP, TString GridNameYM, TString subName, int flavor = -1);
 virtual TH1D* ConvoluteBoostAsym(TString GridNameBoostPlus, TString GridNameBoostMinus, TString subName);

 virtual TH1D* AFBExtend(vector<TString> GridNamesForward, vector<TString> GridNamesBackward, vector<TString> subNames, int flavor);
 virtual TH1D* DilutionExtend(vector<TString> GridNamesYP, vector<TString> GridNamesYM, vector<TString> subNames, int flavor);

 virtual void CalcPDFUnc(TString GridName, TString subName, TString PDFName, int nSet, TString KFactor, int FirstBin = -1, int LastBin = -1);
 virtual void CalcP0PDFUnc(TString GridNameYP, TString GridNameYM, TString subName, TString PDFName, int nSet, vector<TString> KFactors = {});
 virtual void CalcAFBPDFUnc(TString GridNameForward, TString GridNameBackward, TString subName, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors = {});
 virtual void CalcDilutionPDFUnc(TString GridNameYP, TString GridNameYM, TString subName, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors = {});

 virtual void CalcAFBExtendPDFUnc(vector<TString> GridNamesForward, vector<TString> GridNamesBackward, vector<TString> subNames, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors = {});
 virtual void CalcDilutionExtendPDFUnc(vector<TString> GridNamesYP, vector<TString> GridNamesYM, vector<TString> subNames, int flavor, TString ErrorType, TString PDFName, int nSet, vector<TString> KFactors = {});

 bool isLinkFile = false;
 TFile* hf;
 virtual void openFile(const char* name){hf = new TFile(name, "RECREATE"); hf->cd(); isLinkFile = true;}
 virtual void LinkFile(TFile* file){hf = file; hf->cd(); isLinkFile = true;}
 virtual void SaveFile(){hf->Write(); hf->Close();}

 virtual void GenerateKFactor(TString FileName, TH1D* KFactor);
 virtual void GenerateKFactor(TString FileName, TString GridName, TH1D* HighOrder, vector<TString> subProcs = {});
 virtual void GenerateKFactorppbar(TString FileName, TString GridName, TH1D* HighOrder, vector<TString> subProcs = {});

 bool isStatReweight = false;
 double Luminosity = 1.0;
 virtual void SetLuminosity(double lumi){this->isStatReweight = true; this->Luminosity = lumi;};

 virtual void SetNNLO(){order = 2;}

 map<int, TString> SubProcName;
 map<TString, int> SubProcIndex;
 virtual void InitialSubProcName(){
   SubProcName[0] = "bbarbbar";
   SubProcName[1] = "bbarcbar";
   SubProcName[2] = "bbarsbar";
   SubProcName[3] = "bbarubar";
   SubProcName[4] = "bbardbar";
   SubProcName[5] = "bbargluon";
   SubProcName[6] = "bbard";
   SubProcName[7] = "bbaru";
   SubProcName[8] = "bbars";
   SubProcName[9] = "bbarc";
   SubProcName[10] = "bbarb";
   SubProcName[11] = "cbarbbar";
   SubProcName[12] = "cbarcbar";
   SubProcName[13] = "cbarsbar";
   SubProcName[14] = "cbarubar";
   SubProcName[15] = "cbardbar";
   SubProcName[16] = "cbargluon";
   SubProcName[17] = "cbard";
   SubProcName[18] = "cbaru";
   SubProcName[19] = "cbars";
   SubProcName[20] = "cbarc";
   SubProcName[21] = "cbarb";
   SubProcName[22] = "sbarbbar";
   SubProcName[23] = "sbarcbar";
   SubProcName[24] = "sbarsbar";
   SubProcName[25] = "sbarubar";
   SubProcName[26] = "sbardbar";
   SubProcName[27] = "sbargluon";
   SubProcName[28] = "sbard";
   SubProcName[29] = "sbaru";
   SubProcName[30] = "sbars";
   SubProcName[31] = "sbarc";
   SubProcName[32] = "sbarb";
   SubProcName[33] = "ubarbbar";
   SubProcName[34] = "ubarcbar";
   SubProcName[35] = "ubarsbar";
   SubProcName[36] = "ubarubar";
   SubProcName[37] = "ubardbar";
   SubProcName[38] = "ubargluon";
   SubProcName[39] = "ubard";
   SubProcName[40] = "ubaru";
   SubProcName[41] = "ubars";
   SubProcName[42] = "ubarc";
   SubProcName[43] = "ubarb";
   SubProcName[44] = "dbarbbar";
   SubProcName[45] = "dbarcbar";
   SubProcName[46] = "dbarsbar";
   SubProcName[47] = "dbarubar";
   SubProcName[48] = "dbardbar";
   SubProcName[49] = "dbargluon";
   SubProcName[50] = "dbard";
   SubProcName[51] = "dbaru";
   SubProcName[52] = "dbars";
   SubProcName[53] = "dbarc";
   SubProcName[54] = "dbarb";
   SubProcName[55] = "gluonbbar";
   SubProcName[56] = "gluoncbar";
   SubProcName[57] = "gluonsbar";
   SubProcName[58] = "gluonubar";
   SubProcName[59] = "gluondbar";
   SubProcName[60] = "gluongluon";
   SubProcName[61] = "gluond";
   SubProcName[62] = "gluonu";
   SubProcName[63] = "gluons";
   SubProcName[64] = "gluonc";
   SubProcName[65] = "gluonb";
   SubProcName[66] = "dbbar";
   SubProcName[67] = "dcbar";
   SubProcName[68] = "dsbar";
   SubProcName[69] = "dubar";
   SubProcName[70] = "ddbar";
   SubProcName[71] = "dgluon";
   SubProcName[72] = "dd";
   SubProcName[73] = "du";
   SubProcName[74] = "ds";
   SubProcName[75] = "dc";
   SubProcName[76] = "db";
   SubProcName[77] = "ubbar";
   SubProcName[78] = "ucbar";
   SubProcName[79] = "usbar";
   SubProcName[80] = "uubar";
   SubProcName[81] = "udbar";
   SubProcName[82] = "ugluon";
   SubProcName[83] = "ud";
   SubProcName[84] = "uu";
   SubProcName[85] = "us";
   SubProcName[86] = "uc";
   SubProcName[87] = "ub";
   SubProcName[88] = "sbbar";
   SubProcName[89] = "scbar";
   SubProcName[90] = "ssbar";
   SubProcName[91] = "subar";
   SubProcName[92] = "sdbar";
   SubProcName[93] = "sgluon";
   SubProcName[94] = "sd";
   SubProcName[95] = "su";
   SubProcName[96] = "ss";
   SubProcName[97] = "sc";
   SubProcName[98] = "sb";
   SubProcName[99] = "cbbar";
   SubProcName[100] = "ccbar";
   SubProcName[101] = "csbar";
   SubProcName[102] = "cubar";
   SubProcName[103] = "cdbar";
   SubProcName[104] = "cgluon";
   SubProcName[105] = "cd";
   SubProcName[106] = "cu";
   SubProcName[107] = "cs";
   SubProcName[108] = "cc";
   SubProcName[109] = "cb";
   SubProcName[110] = "bbbar";
   SubProcName[111] = "bcbar";
   SubProcName[112] = "bsbar";
   SubProcName[113] = "bubar";
   SubProcName[114] = "bdbar";
   SubProcName[115] = "bgluon";
   SubProcName[116] = "bd";
   SubProcName[117] = "bu";
   SubProcName[118] = "bs";
   SubProcName[119] = "bc";
   SubProcName[120] = "bb";

   for(auto iter = SubProcName.begin(); iter != SubProcName.end(); iter++){
     SubProcIndex[iter->second] = iter->first;
   }
 }

};

#endif
