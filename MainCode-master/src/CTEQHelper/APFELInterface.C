#include "CTEQHelper/HoppetInterface.h"

PDFEvolve* APFELInstance;

void ExternalPDF(const double &x, const double &Q, double *pdf)
{
  pdf[ 0+6] = x * APFELInstance->GetPDFQ0(x, 0);
  pdf[ 3+6] = x * APFELInstance->GetPDFQ0(x, 3);
  pdf[-3+6] = x * APFELInstance->GetPDFQ0(x, -3);
  pdf[ 2+6] = x * APFELInstance->GetPDFQ0(x, 1);
  pdf[-2+6] = x * APFELInstance->GetPDFQ0(x, -1);
  pdf[ 1+6] = x * APFELInstance->GetPDFQ0(x, 2);
  pdf[-1+6] = x * APFELInstance->GetPDFQ0(x, -2);

  pdf[ 4+6] = 0.0;
  pdf[ 5+6] = 0.0;
  pdf[ 6+6] = 0.0;
  pdf[-4+6] = 0.0;
  pdf[-5+6] = 0.0;
  pdf[-6+6] = 0.0;

/*  cout<<"Call ExternalPDF: "<<endl;
  cout<<scientific<<setprecision(6)<<x<<endl;
  cout<<pdf[ 0+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, 0)<<endl;
  cout<<pdf[ 3+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, 3)<<endl;
  cout<<pdf[-3+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, -3)<<endl;
  cout<<pdf[ 2+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, 1)<<endl;
  cout<<pdf[-2+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, -1)<<endl;
  cout<<pdf[ 1+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, 2)<<endl;
  cout<<pdf[-1+6]<<"  "<<x<<"  "<<x * APFELInstance->GetPDFQ0(x, -2)<<endl;
*/
}

void HoppetInterface::InitializeAPFEL(PDFEvolve* p, double Q0)
{
  APFELInstance = p;

#ifdef USE_APFEL
  Qini = Q0;

  nloop = EvolveOrder;
  int PerturbativeOrder = nloop - 1;

  APFEL::SetVFNS();
  APFEL::SetPerturbativeOrder(PerturbativeOrder);
  APFEL::SetNumberOfGrids(3);
  APFEL::SetGridParameters(1,100,5,xmin);
  APFEL::SetGridParameters(2,60,5,1e-1);
  APFEL::SetGridParameters(3,40,5,8e-1);
  APFEL::SetAlphaEvolution("exact");
  APFEL::SetPDFEvolution("exactalpha");
  APFEL::SetPoleMasses(mc,mb,mt);
//  APFEL::SetMassScheme("FONLL-C");
  APFEL::SetMassScheme("ZM-VFNS");
  APFEL::SetMaxFlavourPDFs(NfMx);
  APFEL::SetMaxFlavourAlpha(NfMx);
  APFEL::SetQLimits(Qmin,Qmax);
  APFEL::SetAlphaQCDRef(AsQ0, Q0_as);
  APFEL::EnableWelcomeMessage(0);
 
  APFEL::SetZMass(ZMass);
  APFEL::SetGFermi(GF);
  APFEL::SetWMass(WMass);

//  APFEL::InputExternalPDF(ExternalPDF);
//  APFEL::SetPDFSet("CTEQ");

  if(isEvolveSmallx) APFEL::SetSmallxResummation(1, "NLL");

  APFEL::InitializeAPFEL();

  APFEL::InputExternalPDF(ExternalPDF);
  APFEL::SetPDFSet("CTEQ");
  APFEL::CachePDFsAPFEL(Q0);
#endif

 EvolveType = EvolveEnum::APFEL;
}

void HoppetInterface::EvolveAPFEL(double x, double Q, double* pdf)
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

// APFEL::EvolveAPFEL(Qini, Q);

 for(int i = -5; i <= 5; i++){
   pdf[i + 6] = APFEL::xPDFxQ(i, x, Q);
   //cout<<"x = "<<x<<" Q = "<<Q<<" flavor = "<<i<<" pdf = "<<pdf[i + 6]<<endl;
 }

#endif
}

double HoppetInterface::EvolveAlphaSAPFEL(double Q)
{
 double alphas = 0.0;
#ifdef USE_APFEL
 alphas = APFEL::AlphaQCD(Q);
#endif
 return alphas;
}
