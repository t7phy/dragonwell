#ifndef Calculation_FastNLOHelper_h
#define Calculation_FastNLOHelper_h

#ifdef USE_FNLO

#include "RootCommon.h"
#include "Calculation/FortranArray.h"

#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#include "LHAPDF/Reweighting.h"
#endif

#ifdef USE_HOPPET
#include "CTEQHelper/HoppetInterface.h"
#endif

#include "CTEQHelper/pdsReader.h"
#include "fastnlotk/fastNLOReader.h"
#include "Calculation/QCDSet.h"

using namespace std;

class FastNLOHelper : public fastNLOReader, public QCDSet
{
 public:

 virtual bool InitPDF() {
   return true;
 }

#ifdef USE_LHAPDF
 LHAPDF::PDF* m_PDF;
#endif

#ifdef USE_HOPPET
 HoppetInterface* m_Hoppet;
#endif

 pdsReader* m_CTEQPDF = 0;

 QCDSet* m_qcd;
// FortranArray1D<double> Amhat{0, 10};

 FastNLOHelper(std::string tablename) : fastNLOReader(tablename){
   m_qcd = new QCDSet();
   m_qcd->SetAmhatf();
   Amhat = m_qcd->Amhat;
 }

 FastNLOHelper();
 virtual void InitialPDF(TString PDFName, int iSet);

#ifdef USE_HOPPET
 virtual void InitialPDFbyHand(HoppetInterface* h);
#endif

 virtual void InitialCTEQPDF(TString PDFFile);
 virtual void InitialCTEQPDF(pdsReader* pdf);

 virtual vector<double> GetXFX(double x, double muf) const;
 virtual double EvolveAlphas(double Q) const;


 //int NRAPMAX=5,NPTMAX=17,NBINTOTMAX=150,NXMAX=78;
 int NRAPMAX=6,NPTMAX=23,NBINTOTMAX=150,NXMAX=78; // Give larger value for initialization
 int NMAXSUBPROC=7,NSCALEBINMAX=1,NSCALEMAX=4;
 virtual void SetupOldPar(int nrapmax, int nptmax, int nbintotmax, int nxmax){
   NRAPMAX = nrapmax;
   NPTMAX = nptmax;
   NBINTOTMAX = nbintotmax;
   NXMAX = nxmax;
 }

 int itabversion;
 int ireaction;
 double ECMS, ixsecunits;
 FortranArray1D<TString> namelabel{1, 5};
 int iproc, ialgo;
 double jetres1, jetres2;
 int nord;
 FortranArray1D<int> npow{1, 6};
 FortranArray1D<TString> powlabel{1, 6};
 FortranArray1D<TString> codelabel{1, 6};
 FortranArray1D<long> nevt{1, 6};
 int nxtot, ixscheme, ipdfwgt, iref;
 int nbintot, ndimension;
 FortranArray1D<TString> dimlabel{1, 2};
 int nrapidity;
 FortranArray1D<double> rapbin{1, NRAPMAX+1};
 FortranArray1D<int> npt{1, NRAPMAX};
 FortranArray2D<double> ptbin{1, NRAPMAX, 1, NPTMAX+1};
 FortranArray2D<double> xlimit{1, NRAPMAX, 1, NPTMAX};
 TString scalelabel;
 int nscalebin;
 FortranArray3D<double> murval{1, NRAPMAX, 1, NPTMAX, 1, NSCALEBINMAX};
 FortranArray3D<double> mufval{1, NRAPMAX, 1, NPTMAX, 1, NSCALEBINMAX};
 int nscalevar;
 FortranArray1D<double> murscale{1, NSCALEMAX};
 FortranArray1D<double> mufscale{1, NSCALEMAX};
 int nxsum, nsubproc, nbin;
 FortranArray5D<double> array{1, NBINTOTMAX, 1, NXMAX, 1, NMAXSUBPROC, 1, 1+NSCALEMAX*2, 1, NSCALEBINMAX};
 FortranArray3D<double> result{1, NBINTOTMAX, 1, NMAXSUBPROC+1, 1, 3};
 FortranArray4D<double> pdf{1, NBINTOTMAX, 1, NXMAX, 1, NMAXSUBPROC, 1, NSCALEBINMAX};

 virtual void FT2007CC(TString FileName, double mur, double muf, int iprintflag, FortranArray2D<double> &xsec, TString subType);
 virtual void FT2007RD(TString FileName);
 virtual void FT2007GP(double muffactor);
 virtual void FT2007PL(int ireact, int i, int j, FortranArray2D<double> XPDF, FortranArray1D<double> &H);
 virtual void FT2007MT(double xmur, int ixmuf);
 virtual void FNPDF(double x, double Q, FortranArray1D<double> &newpdf);
 virtual double OFNALPHAS(double Q);

};

#endif

#endif
