#ifndef Calculation_QCDSet_h
#define Calculation_QCDSet_h

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

using namespace std;

enum class PDFTypeEnum {CT_CTEQ, CT_CTEQTable, CT_LHAPDF};

class QCDSet
{
 public:

#ifdef USE_LHAPDF
 LHAPDF::PDF* m_PDF;
#endif

#ifdef USE_HOPPET 
 HoppetInterface* m_Hoppet;
#endif

 pdsReader* m_CTEQPDF = 0;

 PDFTypeEnum PDFType;

 int NfTotal = 5;
 int iMass = 0;
 int Norder = 2;
 double Pi = 3.1415926536;
 bool AmhatSet = false;
 bool MassSyncSet = false;
 FortranArray1D<double> Amhat{0, 10};
 int NHeavyQuark;
 FortranArray1D<double> PoleMass{1, 9};
 FortranArray1D<double> MsbMass{1, 9};

 QCDSet();
 virtual void AlfSet(double QSin, double AlfSin);
 virtual void MassSync(int imass);
 virtual double aMass(int imassin, int I);
 virtual int GetNfl(double amu);
 virtual void SetAmhatf();

 virtual void SetPoleMasscbt(double mc, double mb, double mt){
   PoleMass(4) = mc;
   PoleMass(5) = mb;
   PoleMass(6) = mt;

   SetAmhatf();
 }

 virtual void SetNfTotal(int nf){
   this->NfTotal = nf;
 }

 // PDF
 virtual double GetPDF(int ihadron, int iparton, double x, double Q);
 virtual double GetPDFH(int ihadron, int iparton, double x, double Q);
 virtual double GetPDFP(int iparton, double x, double Q);

 virtual double GetAlphaS(double Q);

 virtual void InitialPDF(TString PDFName, int iSet);
 virtual void InitialCTEQPDF(TString PDFFile);
 virtual void InitialCTEQPDF(pdsReader* pdf);
 virtual void InitialPDFbyHand(HoppetInterface* h);

};
#endif
