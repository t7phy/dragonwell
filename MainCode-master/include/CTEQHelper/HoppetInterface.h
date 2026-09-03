#ifndef CTEQHelper_HoppetInterface_h
#define CTEQHelper_HoppetInterface_h

#include "CTEQHelper/PDFEvolve.h"

#ifdef USE_HOPPET
#include "hoppet_v1.h"
#endif

#ifdef USE_APFEL
#include <emmintrin.h>  // SSE2
#include <smmintrin.h>  // SSE4
#include <xmmintrin.h>  // SSE
#include "APFEL/APFEL.h"
#include "APFEL/APFELevol.h"
#include "APFEL/APFELfwevol.h"
#include "APFELgrid/fastkernel.h"
#include "APFELgrid/transform.h"
#include "apfel/lhtoypdfs.h"
#include <apfel/apfelxx.h>
#include "apfel/initialiseevolution.h"
#include "apfel/integrator.h"
#include "apfel/tabulateobject.h"
#endif

#include "CTEQHelper/pdsReader.h"

void PDF_init(const double &x, const double &Q, double *pdf);
void ExternalPDF(const double &x, const double &Q, double *pdf);

enum class EvolveEnum {Hoppet, APFEL, APFELxx, InputUPD};

class HoppetInterface
{
 public:

 EvolveEnum EvolveType = EvolveEnum::Hoppet;

 double Qini = 1.29;
 double xmin = 1e-9;
 double Qmin = 1.29;
 double Qmax = 1e5;
 double dy    = 0.2;
 int    nloop = 3;
 
 double ymax = 20.723266;
 double dlnlnQ = 0.05;
 int    order = -6;
 int    factscheme = 1;

 double AsQ0 = 0.118;
 double Q0_as = 91.19;

 double qbase = 0.1;
 int NfMx = 5, MxVal = 5;

 double mc = 1.3;
 double mb = 4.75;
 double mt = 1e15;

 double ZMass = 91.1876;
 double WMass = 80.385;
 double GF = 1.16637e-5;

 HoppetInterface();
 virtual void Initialize(PDFEvolve* p, double Q0);
 virtual void Evolution(double x, double Q);

 virtual void Evolve(double x, double Q, double* pdf);
 virtual double EvolveAlphaS(double Q);
 virtual double EvolveAlphaSHoppet(double Q);
 virtual void SetAlphaSQ0(double as, double q){this->AsQ0 = as; this->Q0_as = q;}
 virtual void SetMcbt(double mc, double mb, double mt){
   this->mc = mc;
   this->mb = mb;
   this->mt = mt;
 }
 virtual void SetNfMax(int nfmx){this->NfMx = nfmx;}

 int EvolveOrder = 3;
 int AlphaSOrder = 3;
 virtual void SetEvolveOrder(int order){this->EvolveOrder = order;}
 virtual void SetAlphaSOrder(int order){this->AlphaSOrder = order;}

 virtual void InitializeAlphaS(double as, double q);

 virtual vector<double> ProduceUPD();
 virtual pdsReader* PrepareCTEQTable();
 virtual void OutputLHAPDFTable(TString name, int iSet);

 pdsReader* m_cteqpdf;
 virtual void InputCTEQPDF(pdsReader* p){
   m_cteqpdf = p;
   EvolveType = EvolveEnum::InputUPD;
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_APFEL
 const apfel::Grid APFEL_grid{ {apfel::SubGrid{100,1e-9,5}, apfel::SubGrid{100,0.09,5},
                                apfel::SubGrid{100,6e-1,5}, apfel::SubGrid{100,8.5e-1,5}}};

 apfel::TabulateObject<double> *APFEL_Alphas = 0;
 apfel::TabulateObject<apfel::Set<apfel::Distribution>> *TabulatedPDFs = 0;

#endif
 std::function<std::map<int, double>(double const&, double const&)> CTEQPDFs;
 std::function<double(double const&)> APFEL_as;

 virtual void InitializeAPFELxx(PDFEvolve* p, double Q0);
 virtual void EvolveAPFELxx(double x, double Q, double* pdf);
 virtual double EvolveAlphaSAPFELxx(double Q);

 virtual void InitializeAPFEL(PDFEvolve* p, double Q0);
 virtual void EvolveAPFEL(double x, double Q, double* pdf);
 virtual double EvolveAlphaSAPFEL(double Q);

 bool isEvolveQED = false;
 bool isEvolveSmallx = false;
 virtual void SetEvolveQED(){isEvolveQED = true;}
 virtual void SetEvolveSmallx(){isEvolveSmallx = true;}

////////////////////////////////////////////////////////////////////////////////////////////////////////

 double XCR = 2.0;
 int nx = 203;
 vector<double> QVector;
 vector<double> xVector;
 virtual void SetQArray();
 virtual void SetXArray();

 virtual double xfrmz(double z);
 virtual double dxdz(double z);

 function<double(double)> zfxl;
 function<double(double)> zfrmx_f;
 function<double(double)> zfrmx_d;
 function<double(double)> zfrmx;
 function<double(double)> dzdx;
 bool isDefineZfrmx = false;
 virtual void DefineZfrmx();

 virtual double zbrnt(function<double(double)> func, double x1, double x2, double tolin, int &irt);
};

#endif
