#ifndef Calculation_N3LODIS_h
#define Calculation_N3LODIS_h

#ifdef USE_HOPPET
#include "hoppet.h"
#include "hoppet_oo.h"
#include "hoppet/base_types.h"
#include "hoppet/fortran_prototypes.h"
#endif

#include "RootCommon.h"
#include "Calculation/mDisPac.h"
#include "Calculation/CTUtil.h"
#include "Calculation/CalcDIS.h"

using namespace std;

void unpolarized_pdf_table_for_n3lo(const double &x, const double &Q, double *pdf);

#ifdef USE_HOPPET
extern "C" {
  double hoppet_get_C2LO_clone(void);
  double hoppet_get_CLLO_clone(void);
  double hoppet_get_C3LO_clone(void);
  void* hoppet_get_C2NLO_clone();
  void* hoppet_get_CLNLO_clone();
  void* hoppet_get_C3NLO_clone();
  void* hoppet_get_C2NNLO_clone();
  void* hoppet_get_CLNNLO_clone();
  void* hoppet_get_C3NNLO_clone();
  void* hoppet_get_C2N3LO_clone();
  void* hoppet_get_CLN3LO_clone();
  void* hoppet_get_C3N3LO_clone();
  void* hoppet_get_C2N3LO_fl11_clone();
  void* hoppet_get_CLN3LO_fl11_clone();
  void* hoppet_get_P_LO_clone();
  void* hoppet_get_P_NLO_clone();
  void* hoppet_get_P_NNLO_clone();
  void* hoppet_get_P_N3LO_clone();
}
#endif

class N3LODIS : public mDisPac, public CTUtil
{
 public:

 double C2LO;
 double CLLO;
 double C3LO;

#ifdef USE_HOPPET
 hoppet::split_mat C2NLO;
 hoppet::split_mat CLNLO;
 hoppet::split_mat C3NLO;

 hoppet::split_mat C2NNLO;
 hoppet::split_mat CLNNLO;
 hoppet::split_mat C3NNLO;

 hoppet::split_mat C2N3LO;
 hoppet::split_mat CLN3LO;
 hoppet::split_mat C3N3LO;
 hoppet::split_mat C2N3LO_fl11;
 hoppet::split_mat CLN3LO_fl11;

 hoppet::split_mat P_LO;
 hoppet::split_mat P_NLO;
 hoppet::split_mat P_NNLO;
 hoppet::split_mat P_N3LO;

 hoppet::grid_def grid;
 hoppet::grid_quant_2d hoppet_xpdf;

#endif

 N3LODIS();
 virtual void Initialize();

 int EvolveOrder = 3;
 int AlphaSOrder = 3;
 virtual void SetEvolveOrder(int order){this->EvolveOrder = order;}
 virtual void SetAlphaSOrder(int order){this->AlphaSOrder = order;}

#ifdef USE_HOPPET
 hoppet::split_mat split_mat_clone(void* ptr){
   auto p = static_cast<split_mat_f*>(ptr);
   if (!p) {
     throw std::runtime_error("input function pointer returned null");
   }
   return hoppet::split_mat(p);
 }
#endif

};
#endif
