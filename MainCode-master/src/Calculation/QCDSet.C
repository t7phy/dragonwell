#include "Calculation/QCDSet.h"

QCDSet::QCDSet()
{
 PoleMass(1) = 0.001;
 PoleMass(2) = 0.001;
 PoleMass(3) = 0.2;
 PoleMass(4) = 1.3;
 PoleMass(5) = 4.75;
 PoleMass(6) = 172.0;
 PoleMass(7) = 0.0;
 PoleMass(8) = 0.0;
 PoleMass(9) = 0.0;

 MsbMass(1) = 0.00249;
 MsbMass(2) = 0.00505;
 MsbMass(3) = 0.101;
 MsbMass(4) = 1.27;
 MsbMass(5) = 4.19;
 MsbMass(6) = 172.0;
 MsbMass(7) = 0.0;
 MsbMass(8) = 0.0;
 MsbMass(9) = 0.0;

 for(int i = 1; i <= 10; i++){
   Amhat(i) = 1e15;
 }
}

void QCDSet::AlfSet(double QSin, double AlfSin)
{
 int iAlsEvl = 2;

 double QS = 2 * 99.0;
 double AlfS = 0.01;

 if(fabs(QSin) > 1e-7){
   QS=QSin;
   AlfS=AlfSin;
 }

 if(iAlsEvl == 2){
   m_Hoppet->SetAlphaSQ0(AlfS, QS);
   cout<<"WARNING! This part is not fully setup."<<endl;
 }
}

void QCDSet::MassSync(int imass)
{
 this->iMass = imass;

 auto Delta = [&](double x){
   return 1.2337 * x - 0.597 * pow(x, 2.0) + 0.230 * pow(x, 3.0);
 };

//pn11 Initialize alpha_s using the boundary condition from the previous run
 AlfSet(0.0, 0.0);

 for(int n = 1; n <= NfTotal; n++){
   double QMS = 0.0;
//pn11   Decide if the input mass is an on-shell or MSbar mass
   if(iMass == 0){
     QMS = PoleMass(n);
   }
   else if(iMass == 1){
     QMS = MsbMass(n);
   }
   else{
     cout<<"MassSync: iMass is not defined"<<endl;
     return;
   }
//pn11 Quarks with  masses lighter than AMN=0.5 GeV (in DatQCD) 
//     are light. Skip them.
   if (QMS <= 0.5) continue;

//pn11   Alpha_s is defined slightly above the threshold
   double alpi = GetAlphaS(QMS + 1e-5) / Pi;
   double Factor = 1.0;

   if(iMass == 0){
//marco11     Convert the pole mass to the MSbar mass according to
// Chetyrkin et.al., Comput.Phys.Commun.133:43-65,2000; hep-ph/0004189,
// Eq.(14)

     if(Norder >= 2){
       Factor = Factor - 4.0/3.0 * alpi;
     }

     MsbMass(n) = QMS * Factor;
   }
   else{
//marco11     Convert the MS bar mass to the pole mass according to
// Chetyrkin et.al., Comput.Phys.Commun.133:43-65,2000; hep-ph/0004189,
// Eq.(17). Here the pole mass actually means the on-shell mass
     if(Norder >= 2) Factor = Factor + 4.0/3.0 * alpi;
     if(Norder == 3){
//pn11 Number of active flavors slightly above the current MSbar
//pn11 mass, according to the current factorization scheme
       int NfActive = GetNfl(QMS + 1e-5);

       double Del = 0.0;
       for(int n2 = 1; n2 <= NfActive; n2++){
         Del = Del + Delta(MsbMass(n2) / QMS);
       }
// 13.1454= 307d0/32d0 + 2*ZETA2 + 2d0/3d0*dlog(2d0)-1d0/6d0*ZETA3
// -1.04137 = -71d0/144d0 -1d0/3d0 *ZETA2
       Factor = Factor + pow(alpi, 2.0) * (13.1454 -1.04137 * NfActive + 4.0/3.0 * Del);
     }
     if(Norder > 3){
       cout<<"WARNING: Conversion of the pole mass to MSbar mass "<<endl;
       cout<<"is not implemented for norder > 3"<<endl;
       return;
     }

     PoleMass(n) = QMS * Factor;
   }
 }

 MassSyncSet = true;
}

double QCDSet::aMass(int imassin, int I)
{
 double Value = 0.0;

 if(imassin != iMass && !MassSyncSet){
   cout<<"Quark masses are not synchronized; run MassSync to proceed"<<endl;
   return 0.0;
 }

 int II = abs(I);

 if(II >= 1 && II <= 6){
   if(imassin == 0) Value = PoleMass(II);
   else if(imassin == 1) Value = MsbMass(II);
   else{
     cout<<"AMASS: no such mass type imassin"<<endl;
   }
 }
 return Value;
}

int QCDSet::GetNfl(double amu)
{
//           NFL returns the number of active quark flavors.
//pn10 Revised and simplified to be used independently from CTEQ
//     alpha_s evolution
 if(!AmhatSet) SetAmhatf();

 int Nfl = NfTotal - NHeavyQuark; // NfTotal is the NF in fortran code

//pn10 either no heavy quarks, or amu in the non-pert. region
 if (NHeavyQuark == 0 || (amu <= 0.5)) return Nfl;

 for(int i = NfTotal - NHeavyQuark + 1; i <= NfTotal; i++){
   if(amu >= Amhat(i)){
     Nfl = i;
   }
   else{
     return Nfl;
   }
 }

 return Nfl;
}

void QCDSet::SetAmhatf()
{
// Sets switching points Amhatf between Nf and Nf+1 flavors, given the
// input quark masses QMS and rescaling factor Fswitch. The type of
// the input quark mass (on-shell or MSbar) is determined 
// by the flag iMass inside fitinp

//pn10 Do a preliminary separation between the light and heavy quarks, 
//    by assuming that quarks with  masses lighter than the
//    hard-wired scale AMN=0.5 GeV (in DatQCD) are automatically light, 
//    and the other quarks are heavy. If Lambda_QCD is calculated
//    explicitly in SetL1, the distinction will be refined in SetL1

 Amhat(0) = 0.0;
 NHeavyQuark = 0;

 FortranArray1D<double> QMS{1, 9};
 for(int n = 1; n <= NfTotal; n++){ // NfTotal is the NF in fortran code
   if(iMass == 0) QMS(n) = PoleMass(n);
   else if(iMass == 1) QMS(n) = MsbMass(n);

   if(QMS(n) <= 0.5){
//pn10 Quarks with on-shell masses below Amn are automatically treated
//     as massless 
     Amhat(n) = 0.0;
   }
   else{
//pn10 Quarks with on-shell masses above Amn are treated as massless
//     only if the switching point is below Amn 
     Amhat(n) = exp(0.0 * log(10.0)/2.0)*QMS(n);
     if(Amhat(n) <= 0.5){
        cout<<"WARNING! Nonpert. AMHAT(N) in SetAmhatf; setting AMHAT(N)=0"<<endl;
        Amhat(n) = 0.0;
     }
     else{                  //increment the number of heavy quarks
       NHeavyQuark=NHeavyQuark + 1;
     }
   }
 }
 AmhatSet = true;
}

void QCDSet::InitialPDF(TString PDFName, int iSet)
{
#ifdef USE_LHAPDF
 m_PDF = LHAPDF::mkPDF(PDFName.Data(), iSet);
#endif

 PDFType = PDFTypeEnum::CT_LHAPDF;
}

void QCDSet::InitialCTEQPDF(TString PDFFile)
{
 m_CTEQPDF = new pdsReader();
 m_CTEQPDF->Initialize(PDFFile);

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

void QCDSet::InitialCTEQPDF(pdsReader* pdf)
{
 if(m_CTEQPDF) delete m_CTEQPDF;

 m_CTEQPDF = new pdsReader();
 m_CTEQPDF->CopyHeader(pdf);
 m_CTEQPDF->InputAlphaS(pdf->AlsCTEQ);
 m_CTEQPDF->InputUPD(pdf->UPD);

 PDFType = PDFTypeEnum::CT_CTEQTable;
}

#ifdef USE_HOPPET
void QCDSet::InitialPDFbyHand(HoppetInterface* h)
{
 m_Hoppet = h;

 PDFType = PDFTypeEnum::CT_CTEQ;
}
#endif

double QCDSet::GetAlphaS(double Q)
{
 double Value;
#ifdef USE_HOPPET
 if(PDFType == PDFTypeEnum::CT_CTEQ) Value = m_Hoppet->EvolveAlphaS(Q);
#endif

#ifdef USE_LHAPDF
 if(PDFType == PDFTypeEnum::CT_LHAPDF) Value = m_PDF->alphasQ2(Q*Q);
#endif

 if(PDFType == PDFTypeEnum::CT_CTEQTable) Value = m_CTEQPDF->CT14Alphas(Q);

 return Value;
}
