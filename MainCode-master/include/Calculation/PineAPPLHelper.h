#ifndef Calculation_PineAPPLHelper_h
#define Calculation_PineAPPLHelper_h

#include <LHAPDF/PDF.h>
#include <cstdint>

#ifdef USE_PINEAPPL
#include <pineappl_capi.h>
#endif

#ifdef USE_LHAPDF
#include "LHAPDF/LHAPDF.h"
#endif

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Tools/Log.h"
#include "Uncertainty/PDFUncertainty.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "CTEQHelper/HoppetInterface.h"
#include "Calculation/QCDSet.h"

using namespace std;

class PineAPPLHelper : public QCDSet
{
 public:

#ifdef USE_LHAPDF
 std::unique_ptr<LHAPDF::PDF> m_PDF1;
 std::unique_ptr<LHAPDF::PDF> m_PDF2;

 std::vector<LHAPDF::PDF*> m_PDFs;
#endif

 std::unique_ptr<pdsReader> m_CTEQPDF1;
 std::unique_ptr<pdsReader> m_CTEQPDF2;

 std::vector<pdsReader*> m_CTEQPDFs;

 void** pdf_states;

 TString PDFName;
 int iSet;

 TString GridName;

#ifdef USE_PINEAPPL
 pineappl_grid* grid;

 // how many channels does the grid have?
 pineappl_channels * channels;
#endif

 int nHardOrder = 2;

 std::size_t nPoints;
 std::size_t nDim;
 vector<double> results;

 vector<double> binx_left;
 vector<double> binx_right;
 vector<double> biny_left;
 vector<double> biny_right;
 vector<double> binz_left;
 vector<double> binz_right;

 vector<double> bin_limits;

 // how many perturbative orders does the grid contain?
 std::size_t orders;

 std::size_t channels_length;

 std::unique_ptr<bool[]> order_mask;

 std::unique_ptr<bool[]> channel_mask;

 PineAPPLHelper();

 virtual void InitialPDF(TString PDFName, int iSet);
 virtual void InitialCTEQPDF(pdsReader* pdf);
 virtual void InitialCTEQPDF(TString PDFFile);
 virtual void InitialGrid(TString GridName);
 virtual vector<double> Convolute();
 virtual vector<double> Convoluteppbar();
 virtual void DefaultConvolute();

 virtual void SetHardOrder(int order){this->nHardOrder = order;}
};
#endif
