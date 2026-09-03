#include "ElectroweakTheory/ResBosEW.h"

ResBosEW::ResBosEW()
{
 initAlpha();
 InputStw(0.2315);
}

void ResBosEW::InputStw(double stw)
{
 this->sw2_eff = stw;

 InitialPara();
}

void ResBosEW::InitialPara()
{
 cws = mW*mW/mZ/mZ;
 sws = 1 - cws;

 cw = sqrt(cws);
 sw = sqrt(sws);

 alpha0 = sqrt(2.0)*mW*mW*GF*sws/M_PI;
 acoupl = 2.0*M_PI*alpha0;

// zcoupl_e = M_PI*alpha0/sws/cws;
// zcoupl_u = M_PI*alpha0/sws/cws;
// zcoupl_d = M_PI*alpha0/sws/cws;

///////////////////////////////////////////////
//From ResBos1
 double ALPI_MT=alphas(mT)/M_PI;
 double EW_DELRHO=3.0*GF*mT*mT/8.0/sqrt(2.0)/M_PI/M_PI;
 EW_DELRHO=EW_DELRHO*(1.0-2.0/3.0*(M_PI * M_PI/3.0+1.0)*ALPI_MT);

 rho_e = (1.0+EW_DELRHO) * (1.0+EW_DELRHO);
 rho_u = (1.0+EW_DELRHO) * (1.0+EW_DELRHO);
 rho_d = (1.0+EW_DELRHO) * (1.0+EW_DELRHO);

 zcoupl_e=sqrt(2.0)*mZ*mZ*GF*sqrt(rho_e);
 zcoupl_u=sqrt(2.0)*mZ*mZ*GF*sqrt(rho_u);
 zcoupl_d=sqrt(2.0)*mZ*mZ*GF*sqrt(rho_d);

///////////////////////////////////////////////

 wcoupl = sqrt(2.0)*mW*mW*GF/2.0;

 // Define couplings using EW class
 gvu=2*(0.5)-4*2.0/3.0*fabs(sw2_eff - 0.0001);
 gvd=2*(-0.5)-4*(-1.0/3.0)*fabs(sw2_eff - 0.0002);
 gvl=2*(-0.5)-4*(-1.0)*fabs(sw2_eff);
 gau=-1.0;
 gad=1.0;
 gal=1.0;
 gvu=gvu/2.0;
 gvd=gvd/2.0;
 gvl=gvl/2.0;
 gau=gau/2.0;
 gad=gad/2.0;
 gal=gal/2.0;

 FAC_e = sqrt(fabs(zcoupl_e));
 FAC_u = sqrt(fabs(zcoupl_u));
 FAC_d = sqrt(fabs(zcoupl_d));
 FAC_A = sqrt(2.0*fabs(acoupl))/2.0;

// EL_Z = (gvl-gal)*FAC_e/2.0;//ResBos2
// ER_Z = (gvl+gal)*FAC_e/2.0;//ResBos2
 EL_Z = (-0.5 + sw2_eff) * sqrt(fabs(zcoupl_e));//ResBos1
 ER_Z = sw2_eff * sqrt(fabs(zcoupl_e));//ResBos1

 QL_Z1 = (gvu-gau)*FAC_u/2.0;
 QR_Z1 = (gvu+gau)*FAC_u/2.0;
 QL_Z2 = (gvd-gad)*FAC_d/2.0;
 QR_Z2 = (gvd+gad)*FAC_d/2.0;

 QL_A1 = (2.0/3.0)*FAC_A;
 QR_A1 = (2.0/3.0)*FAC_A;
 QL_A2 = (-1.0/3.0)*FAC_A;
 QR_A2 = (-1.0/3.0)*FAC_A;
 EL_A = -1.0*FAC_A;
 ER_A = -1.0*FAC_A;

 // 0 corresponds to up-type quarks, 1 corresponds to down-type quarks
 CAA_E[0] = ( QL_A1*QL_A1 + QR_A1*QR_A1 )*( EL_A*EL_A + ER_A*ER_A );
 CAA_O[0] = ( QL_A1*QL_A1 - QR_A1*QR_A1 )*( EL_A*EL_A - ER_A*ER_A );
 CZZ_E[0] = ( QL_Z1*QL_Z1 + QR_Z1*QR_Z1 )*( EL_Z*EL_Z + ER_Z*ER_Z );
 CZZ_O[0] = ( QL_Z1*QL_Z1 - QR_Z1*QR_Z1 )*( EL_Z*EL_Z - ER_Z*ER_Z );
 CZA_E[0] = ( QL_Z1*QL_A1 + QR_Z1*QR_A1 )*( EL_Z*EL_A + ER_Z*ER_A );
 CZA_O[0] = ( QL_Z1*QL_A1 - QR_Z1*QR_A1 )*( EL_Z*EL_A - ER_Z*ER_A );
 CAA_E[1] = ( QL_A2*QL_A2 + QR_A2*QR_A2 )*( EL_A*EL_A + ER_A*ER_A );
 CAA_O[1] = ( QL_A2*QL_A2 - QR_A2*QR_A2 )*( EL_A*EL_A - ER_A*ER_A );
 CZZ_E[1] = ( QL_Z2*QL_Z2 + QR_Z2*QR_Z2 )*( EL_Z*EL_Z + ER_Z*ER_Z );
 CZZ_O[1] = ( QL_Z2*QL_Z2 - QR_Z2*QR_Z2 )*( EL_Z*EL_Z - ER_Z*ER_Z );
 CZA_E[1] = ( QL_Z2*QL_A2 + QR_Z2*QR_A2 )*( EL_Z*EL_A + ER_Z*ER_A );
 CZA_O[1] = ( QL_Z2*QL_A2 - QR_Z2*QR_A2 )*( EL_Z*EL_A - ER_Z*ER_A );

// cout<<"gvl = "<<gvl<<" gal = "<<gal<<" FAC = "<<FAC_e<<endl;
// cout<<"QL_Z = "<<QL_Z1<<" QL_A = "<<QL_A1<<" QR_Z = "<<QR_Z1<<" QR_A = "<<QR_A1<<endl;
// cout<<"EL_Z = "<<EL_Z<<" EL_A = "<<EL_A<<" ER_Z = "<<ER_Z<<" ER_A = "<<ER_A<<endl;
}

void ResBosEW::InitialPropagator(double Q)
{
 alpha0 = GetAlphaEM(0);
 double mz = mZ;
 double Propagator = pow(Q*Q-mz*mz,2)+pow(Q,4)*pow(gamZ/mz,2);

 zzProp = pow(Q,4)/Propagator;
 aaProp = 1.0;
 zaProp = Q*Q*(Q*Q-mz*mz)/Propagator;

// alphaQ2 = GetAlphaEM(Q*Q);//ResBos2
 alphaQ2 = pyalem(Q*Q);//ResBos1
 zaProp *= alphaQ2/alpha0;
 aaProp *= pow(alphaQ2/alpha0,2);

// cout<<"Q = "<<Q<<" AA_PROP = "<<aaProp<<" ZA_PROP = "<<zaProp<<" ZZ_PROP = "<<zzProp<<endl;
// cout<<"CAA_E = "<<CAA_E[0]<<" CZA_E = "<<CZA_E[0]<<" CZZ_E = "<<CZZ_E[0]<<endl;
// cout<<"CAA_O = "<<CAA_O[0]<<" CZA_O = "<<CZA_O[0]<<" CZZ_O = "<<CZZ_O[0]<<endl;

}

double ResBosEW::ZCrossSection(double mass, int iflag, TString Process)
{
 InitialPropagator(mass);

 if(abs(iflag) == 1) iMode = 0;//uubar
 if(abs(iflag) == 2) iMode = 1;//ddbar

 if(iflag > 0){
   if(Process == "") angularEven = 8.0 / 3.0;
   if(Process == "F") angularEven = 4.0 / 3.0;
   if(Process == "B") angularEven = 4.0 / 3.0;

   if(Process == "") angularOdd = 0.0;
   if(Process == "F") angularOdd = 1.0;
   if(Process == "B") angularOdd = - 1.0;
 }
 else if(iflag < 0){
   if(Process == "") angularEven = 8.0 / 3.0;
   if(Process == "F") angularEven = 4.0 / 3.0;
   if(Process == "B") angularEven = 4.0 / 3.0;
 
   if(Process == "") angularOdd = 0.0;
   if(Process == "F") angularOdd = - 1.0;
   if(Process == "B") angularOdd = 1.0;
 }

 coeffEven = aaProp*CAA_E[iMode] + 2.0*zaProp*CZA_E[iMode] + zzProp*CZZ_E[iMode];
 coeffOdd = aaProp*CAA_O[iMode] + 2.0*zaProp*CZA_O[iMode] + zzProp*CZZ_O[iMode];
 total = coeffEven*angularEven + coeffOdd*angularOdd;

 double FACTOR=2.0*(M_PI/3.0)*(4.0*2.0);

 return FACTOR*total;
}

double ResBosEW::GetAlphaEM(double Q2)
{
    // Fixed alpha_EM
    if(alphaEMOrder == 0) return alphaEM0;
    if(alphaEMOrder < 0) return alphaEMMz;

    // Running alpha_EM
    for(size_t i = 4; i != static_cast<size_t>(-1); --i)
        if(Q2 > Q2Step[i])
            return alphaEMStep[i] / (1. - betaEM[i] * alphaEMStep[i] * log(Q2/Q2Step[i]));

    return alphaEM0;

}

void ResBosEW::initAlpha() {
    // Read in order and values at 0 and m_Z
//    alphaEMOrder = settings -> GetSettingInt("AlphaEMOrder");
//    alphaEM0 = settings -> GetSettingDouble("AlphaEM0");
//    alphaEMMz = settings -> GetSettingDouble("AlphaEMMZ");
    alphaEMOrder = 1;
    alphaEM0 = 0.0072973531;
    alphaEMMz = 0.007763340902;

    // Get alpha_EM at matching scales and matching beta values
    if(alphaEMOrder <= 0) return;

    // Evolve from mZ to tau/charm
    alphaEMStep[4] = alphaEMMz / (1. + alphaEMMz * betaEM[4] * log(std::abs(mZ*mZ)/Q2Step[4]));
    alphaEMStep[3] = alphaEMStep[4] / (1. - alphaEMStep[4] * betaEM[3]
                   * log(Q2Step[3]/Q2Step[4]));

    // Evolve up from me to light-quark threshold
    alphaEMStep[0] = alphaEM0;
    alphaEMStep[1] = alphaEMStep[0]/(1. - alphaEMStep[0] * betaEM[0] * log(Q2Step[1]/Q2Step[0]));
    alphaEMStep[2] = alphaEMStep[1]/(1. - alphaEMStep[1] * betaEM[1] * log(Q2Step[2]/Q2Step[1]));

    // Interpolate beta between light-quark and tau/charm region
    betaEM[2] = (1./alphaEMStep[3] - 1./alphaEMStep[2])/log(Q2Step[2]/Q2Step[3]);
}

double ResBosEW::pyalem(double q2){
// Returns the running electromagnetic coupling alpha
//PN Stolen shamelessly from ResBos
//
//...Calculate real part of photon vacuum polarization.
//...For leptons simplify by using asymptotic (q^2 >> m^2) expressions.
//   For hadrons use parametrization of H. Burkhardt et al.
//   See R. Kleiss et al, CERN 89-08, vol. 3, pp. 129-131.
//csb___see also Phys.Lett.B356:398-403,1995

  double pi, alpha0, rpigg, aempi;
  pi = 3.1415926535897932;
  alpha0=1./137.04;//ResBos1
  //alpha0=0.0072973531;//ResBos2
  aempi= alpha0/(3.*pi);

  if (q2 < 2e-6)
    rpigg =0.0;
  else if(q2 < 0.09)
    rpigg = aempi*(13.4916 + log(q2)) + 0.00835*log(1.+q2);
  else if(q2 < 9.)
    rpigg=aempi*(16.3200+2.0*log(q2))+ 0.00238*log(1.0+3.927*q2);
  else if(q2 < 1e4)
    rpigg=aempi*(13.4955+3.0*log(q2))+0.00165+ 0.00299*log(1.0+q2);
  else
    rpigg=aempi*(13.4955+3.0*log(q2))+ 0.00221 + 0.00293*log(1.0+q2);

//...Calculate running alpha_em.
  return alpha0/(1.0-rpigg);
}//pyalem ->

double ResBosEW::alphas(double AMU)
{
 double ALPHAS;

 double QCDL=0.326;
 double AL4=QCDL;
 double AL5=AL4 * pow((AL4/mB), (2.0/23.0)) * pow((log(mB*mB/AL4/AL4)), (-963.0/13225.0));
 double AL6=AL5 * pow((AL5/mT), (2.0/21.0)) * pow((log(mT*mT/AL5/AL5)), (-321.0/3381.0));

 double XRAT = AMU * AMU;

 double sqrt_xrat = AMU;

 double RAT;
 double B0;
 double B1;

 if(sqrt_xrat > mT){
   RAT=log(XRAT/AL6/AL6);
   B0=12.0*3.14159/21.0;
   B1=6.0*(153.0-19.0*6.0)/21.0/21.0;
 }
 else if(sqrt_xrat > mB){
   RAT=log(XRAT/AL5/AL5);
   B0=12.0*3.14159/23.0;
   B1=6.0*(153.0-19.0*5.0)/23.0/23.0;
 }
 else{
   RAT=log(XRAT/AL4/AL4);
   B0=12.0*3.14159/25.0;
   B1=6.0*(153.0-19.0*4.0)/25.0/25.0;
 }
 ALPHAS=B0/RAT*(1.0-B1*log(RAT)/RAT);

 return ALPHAS;
}
