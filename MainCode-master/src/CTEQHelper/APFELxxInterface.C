#include "CTEQHelper/HoppetInterface.h"

using namespace apfel;

void HoppetInterface::InitializeAPFELxx(PDFEvolve* p, double Q0)
{
#ifdef USE_APFEL
  Qini = Q0;

  vector<double> Thresholds = {0.0, 0.0, 0.0, mc, mb, mt};
  nloop = EvolveOrder;
  int PerturbativeOrder = nloop - 1;

  apfel::SetVerbosityLevel(0);
  apfel::Banner();
  apfel::AlphaQCD a(AsQ0, Q0_as, Thresholds, PerturbativeOrder);

  if(!APFEL_Alphas) delete APFEL_Alphas;
  APFEL_Alphas = new apfel::TabulateObject<double>(a, 100, Qmin, Qmax, 5);

  APFEL_as = [&] (double const& mu) -> double{ return APFEL_Alphas->Evaluate(mu); };

  CTEQPDFs = [&] (double const& x, double const&) -> std::map<int, double>{

    double dnv  = x * p->GetPDFQ0(x, 2) - x * p->GetPDFQ0(x, -2); // PDFEvolve uses CTEQ flavor notation, d for 2, u for 1
    double upv  = x * p->GetPDFQ0(x, 1) - x * p->GetPDFQ0(x, -1);
    double glu  = x * p->GetPDFQ0(x, 0);
    double dbar = x * p->GetPDFQ0(x, -2);
    double ubar = x * p->GetPDFQ0(x, -1);
    double sbar = x * p->GetPDFQ0(x, -3);

    // Construct QCD evolution basis conbinations.
    double const Gluon   = glu;
    double const Singlet = dnv + 2 * dbar + upv + 2 * ubar + 2 * sbar;
    double const T3      = upv + 2 * ubar - dnv - 2 * dbar;
    double const T8      = upv + 2 * ubar + dnv + 2 * dbar - 4 * sbar;
    double const Valence = upv + dnv;
    double const V3      = upv - dnv;

    // Fill in map in the QCD evolution basis.
    std::map<int, double> QCDEvMap;
    QCDEvMap[0]  = Gluon;
    QCDEvMap[1]  = Singlet;
    QCDEvMap[2]  = Valence;
    QCDEvMap[3]  = T3;
    QCDEvMap[4]  = V3;
    QCDEvMap[5]  = T8;
    QCDEvMap[6]  = Valence;
    QCDEvMap[7]  = Singlet;
    QCDEvMap[8]  = Valence;
    QCDEvMap[9]  = Singlet;
    QCDEvMap[10] = Valence;
    QCDEvMap[11] = Singlet;
    QCDEvMap[12] = Valence;

    return QCDEvMap;
 };

 // Initialize QCD evolution objects
 const auto DglapObj = InitializeDglapObjectsQCD(APFEL_grid, Thresholds);

 // Construct the DGLAP object
 const auto EvolvedPDFs = BuildDglap(DglapObj, CTEQPDFs, Q0, PerturbativeOrder, APFEL_as);

 if(!TabulatedPDFs) delete TabulatedPDFs;
 TabulatedPDFs = new apfel::TabulateObject<apfel::Set<apfel::Distribution>> (*EvolvedPDFs, 50, Qmin, Qmax, 3);

#endif
 EvolveType = EvolveEnum::APFELxx;
}

void HoppetInterface::EvolveAPFELxx(double x, double Q, double* pdf)
{
#ifdef USE_APFEL
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

 const std::map<int, apfel::Distribution> APFEL_PDFs = apfel::QCDEvToPhys(TabulatedPDFs->Evaluate(Q).GetObjects());

 for(int i = -5; i <= 5; i++){
   pdf[i + 6] = APFEL_PDFs.at(i).Evaluate(x);
   //cout<<"x = "<<x<<" Q = "<<Q<<" flavor = "<<i<<" pdf = "<<pdf[i + 6]<<endl;
 }

#endif
}

double HoppetInterface::EvolveAlphaSAPFELxx(double Q)
{
 double Value = 0.0;
#ifdef USE_APFEL
 Value = APFEL_as(Q);
#endif
 return Value;
}
