/*
 *  LPXSignalReweightingTool.cxx
 *  latest update on: Nov 17, 2016
 *  Authors: Daniel Hayden (daniel.hayden@cern.ch), 
 *           Christopher Willis (Christopher.Willis@cern.ch)
 */

#include "ZPrime/LPXSignalReweightingTool.h"

using namespace std;

LPXSignalReweightingTool::LPXSignalReweightingTool( const std::string& name ) {
  
  // MeV to GeV conversion factor
  GeV = 0.001;

  // CM Energy of LHC
  s = 13600.0;
  std::cout << " CM Energy" << std::endl;
  std::cout << " sqrtS: 13600 GeV"  << std::endl;

  // set Standard Model Parameters

  // Define electroweak scheme
  // For Pythia
  //GF  = 1.16637*pow(10,-5); // GeV^-2
  //mZ  = 91.1876;            // GeV, Pythia value
  //sw2 = 0.2312;             // sin^2 theta_W       

  // set derived quantities from scheme choice
  // For Pythia
  //mW  = mZ*sqrt(1-sw2);     // Born level
  //sw  = sqrt(sw2);
  //cw2 = 1-sw2;
  //cw  = sqrt(1-sw2);

  // For Powheg
  mZ  = 91.1876;
  mW  = 79.958059;
  double alphaem = 0.00781653;

  sw2 = 1.0 - pow(mW / mZ, 2);
  sw = sqrt(sw2);
  cw2 = 1.0 - sw2;
  cw = sqrt(1.0 - sw2);
  GF = TMath::Pi() * alphaem / (sqrt(2.0) * pow(mW, 2) * sw2);

  // set fermion charges based on PdgId
  qf[0] = 0; 
  qf[1] = -1./3.; // d
  qf[2] =  2./3.; // u
  qf[3] = -1./3.; // s
  qf[4] =  2./3.; // c
  qf[5] = -1./3.; // b
  qf[6] =  2./3.; // t
  qf[7] = -1./3.; // b'
  qf[8] =  2./3.; // t'
  qf[9] = 0;
  qf[10] =  0;
  qf[11] = -1.;   // e
  qf[12] =  0.;   // ve
  qf[13] = -1.;   // mu
  qf[14] =  0.;   // vmu
  qf[15] = -1.;   // tau
  qf[16] =  0.;   // vtau
  qf[17] = -1.;   // tau'
  qf[18] =  0.;   // vtau'

  // set fermion weak-isospin projections based on PdgId
  t3Lf[0] = 0; 
  t3Lf[1] = -1./2.;  // d
  t3Lf[2] =  1./2.;  // u
  t3Lf[3] = -1./2.;  // s
  t3Lf[4] =  1./2.;  // c
  t3Lf[5] = -1./2.;  // b
  t3Lf[6] =  1./2.;  // t
  t3Lf[7] = -1./2.;  // b'
  t3Lf[8] =  1./2.;  // t'
  t3Lf[9] = 0;
  t3Lf[10] =  0;
  t3Lf[11] = -1./2.; // e
  t3Lf[12] =  1./2.; // ve
  t3Lf[13] = -1./2.; // mu
  t3Lf[14] =  1./2.; // vmu
  t3Lf[15] = -1./2.; // tau
  t3Lf[16] =  1./2.; // vtau
  t3Lf[17] = -1./2.; // tau'
  t3Lf[18] =  1./2.; // vtau'

  // set fermion masses in GeV based on PdgId
  mass[0] = 0; 
  mass[1] = 0.33;  // d
  mass[2] = 0.33;  // u
  mass[3] = 0.50;  // s
  mass[4] = 1.50;  // c
  mass[5] = 4.80;  // b
  mass[6] = 171.0; // t
  mass[7] = 0.0;   // b'
  mass[8] = 0.0;   // t'
  mass[9] = 0.0;
  mass[10] = 0.0;
  mass[11] = 0.000511; // e
  mass[12] = 0.0;      // ve
  mass[13] = 0.10566;  // mu
  mass[14] = 0.0;      // vmu
  mass[15] = 1.77682;  // tau
  mass[16] = 0.0;      // vtau
  mass[17] = 0.0;      // tau'
  mass[18] = 0.0;      // vtau'

  // initialize quark mixing matrix: CKM Matrix
  CKMMatrix[0] = 0.97427;
  CKMMatrix[1] = 0.22536;
  CKMMatrix[2] = 0.00355;
  CKMMatrix[3] = 0.22522;
  CKMMatrix[4] = 0.97343;
  CKMMatrix[5] = 0.0414;
  CKMMatrix[6] = 0.00886;
  CKMMatrix[7] = 0.0405;
  CKMMatrix[8] = 0.99914;

  // ( ud us ub
  //   cd cs cb
  //   td ts tb )

  // initialize lepton mixing matrix: identity in SM
  LEPMatrix[0] = 1;
  LEPMatrix[1] = 0;
  LEPMatrix[2] = 0;
  LEPMatrix[3] = 0;
  LEPMatrix[4] = 1;
  LEPMatrix[5] = 0;
  LEPMatrix[6] = 0;
  LEPMatrix[7] = 0;
  LEPMatrix[8] = 1;

  // ( eve   evmu   evtau
  //   muve  muvmu  muvtau
  //   tauve tauvmu tauvtau )

  // set EM gauge coupling constant
  e = sqrt(4.0*TMath::Pi()*alphaEM(mZ*mZ));
  //std::cout << " e:  " << e << std::endl;

  // set Z Boson gauge coupling constant
  gZ = e/(sw*cw);
  //std::cout << " gZ: " << gZ << std::endl;

  // set SU(2)L gauge coupling constant
  g = e/sw;
  //std::cout << " g:  " << g << std::endl;

  // set Z Boson width
  gammaZ = calcZBosonWidth();
  //std::cout << " gamma Z: " << gammaZ << " GeV" << std::endl;

  // set W Boson width
  gammaW = calcWBosonWidth();
  //std::cout << " gamma W: " << gammaW << " GeV " << std::endl;

}

LPXSignalReweightingTool::~LPXSignalReweightingTool() {
}

void LPXSignalReweightingTool::initialize() {
  return;
}

/*
void LPXSignalReweightingTool::execute() {
  return;
}
*/

double LPXSignalReweightingTool::calcZBosonWidth() {
  
  // set EM gauge coupling constant at mZ scale
  double e = sqrt(4.0*TMath::Pi()*alphaEM(mZ*mZ));

  // set gauge coupling at mZ scale
  double gZ = e/(sw*cw);

  // useful prefactors 
  double g0 = pow(gZ,2)*mZ/(24.0*TMath::Pi());
  double CF = 3;
  
  // QCD radiative corrections
  double rQCD = 1 + alphaS(mZ*mZ)/TMath::Pi();

  // QED radiative corrections
  double rQED     = 1 + 3.*alphaEM(mZ*mZ)/(4.*TMath::Pi());
  double rQED_e   = 1 + 3.*alphaEM(mZ*mZ)/(4.*TMath::Pi())-6.*pow(m(11)/mZ,2);
  double rQED_mu  = 1 + 3.*alphaEM(mZ*mZ)/(4.*TMath::Pi())-6.*pow(m(13)/mZ,2);
  double rQED_tau = 1 + 3.*alphaEM(mZ*mZ)/(4.*TMath::Pi())-6.*pow(m(15)/mZ,2);

  // calculate Z partial widths
  double gamma_nu  = g0*(pow(gL(12),2) + pow(gR(12),2));                                     // Z partial width to neutrinos
  double gamma_e   = g0*(0.5*pow(gL(11)+gR(11),2)*rQED + 0.5*pow(gL(11)-gR(11),2)*rQED_e);   // Z partial width to electrons
  double gamma_mu  = g0*(0.5*pow(gL(13)+gR(13),2)*rQED + 0.5*pow(gL(13)-gR(13),2)*rQED_mu);  // Z partial width to muons
  double gamma_tau = g0*(0.5*pow(gL(15)+gR(15),2)*rQED + 0.5*pow(gL(15)-gR(15),2)*rQED_tau); // Z partial width to taus
  double gamma_d   = CF*g0*(pow(gL(1),2)*rQCD + pow(gR(1),2)*rQCD);                          // Z partial width to down-quarks
  double gamma_u   = CF*g0*(pow(gL(2),2)*rQCD + pow(gR(2),2)*rQCD);                          // Z partial width to up-quarks

  //std::cout << "     Z width to v:   " << gamma_nu << std::endl;
  //std::cout << "     Z width to e:   " << gamma_e << std::endl;
  //std::cout << "     Z width to mu:  " << gamma_mu << std::endl;
  //std::cout << "     Z width to tau: " << gamma_tau << std::endl;
  //std::cout << "     Z width to d:   " << gamma_d << std::endl;
  //std::cout << "     Z width to u:   " << gamma_u << std::endl;

  // calculate Z total width by summing over partial widths
  double gammaZ = 3.0*gamma_nu + gamma_e + gamma_mu + gamma_tau + 3.0*gamma_d + 2.0*gamma_u;
  
  return gammaZ; 
}

double LPXSignalReweightingTool::calcWBosonWidth() {
  
  // set EM gauge coupling constant at mW scale
  double e = sqrt(4.0*TMath::Pi()*alphaEM(mW*mW));

  // set SU(2) coupling constant at mW scale
  double g = e/sw;

  // useful prefactors
  double g0 = pow(g,2)*mW/(48.0*TMath::Pi());
  double CF = 3; // color factor for number of quark colors

  // QCD radiative corrections
  double rQCD = 1.0 + alphaS(mW*mW)/TMath::Pi();

  // W partial width to lepton/neutrino pairs
  double gamma_lv = g0;

  // W partial widths to up/light quark pairs
  double gamma_ud = CF*rQCD*g0*pow(VCKM(2,1),2);
  double gamma_us = CF*rQCD*g0*pow(VCKM(2,3),2);
  double gamma_ub = CF*rQCD*g0*pow(VCKM(2,5),2);

  // W partial widths to charm/light quark pairs
  double gamma_cd = CF*rQCD*g0*pow(VCKM(4,1),2);
  double gamma_cs = CF*rQCD*g0*pow(VCKM(4,3),2);
  double gamma_cb = CF*rQCD*g0*pow(VCKM(4,5),2);

  //std::cout << "     W width to lv: " << 3*gamma_lv << std::endl;
  //std::cout << "     W width to ud: " << gamma_ud << std::endl;
  //std::cout << "     W width to us: " << gamma_us << std::endl;
  //std::cout << "     W width to ub: " << gamma_ub << std::endl;
  //std::cout << "     W width to cd: " << gamma_cd << std::endl;
  //std::cout << "     W width to cs: " << gamma_cs << std::endl;
  //std::cout << "     W width to cb: " << gamma_cb << std::endl;

  // calculate the total width by summing over partial widths
  double gammaW = 3.0*gamma_lv 
    + (gamma_ud + gamma_us + gamma_ub) 
    + (gamma_cd +  gamma_cs + gamma_cb);

  return gammaW; 
}

// return particle width in GeV
double LPXSignalReweightingTool::width(int pdgId) {
  if(pdgId==23) return gammaZ;
  if(pdgId==24) return gammaW;
  std::cout << "SM width access failure" << std::endl;
  return -999;
}
 
double LPXSignalReweightingTool::VCKM(int pdgId1, int pdgId2) {

  pdgId1 = abs(pdgId1);
  pdgId2 = abs(pdgId2);
  
  // uq pairs
  if( (pdgId1==2 && pdgId2==1) || (pdgId2==2 && pdgId1==1) ) return CKMMatrix[0];
  if( (pdgId1==2 && pdgId2==3) || (pdgId2==2 && pdgId1==3) ) return CKMMatrix[1];
  if( (pdgId1==2 && pdgId2==5) || (pdgId2==2 && pdgId1==5) ) return CKMMatrix[2];
  
  // cq pairs
  if( (pdgId1==4 && pdgId2==1) || (pdgId2==4 && pdgId1==1) ) return CKMMatrix[3];
  if( (pdgId1==4 && pdgId2==3) || (pdgId2==4 && pdgId1==3) ) return CKMMatrix[4];
  if( (pdgId1==4 && pdgId2==5) || (pdgId2==4 && pdgId1==5) ) return CKMMatrix[5];
  
  // tq pairs
  if( (pdgId1==6 && pdgId2==1) || (pdgId2==6 && pdgId1==1) ) return CKMMatrix[6];
  if( (pdgId1==6 && pdgId2==3) || (pdgId2==6 && pdgId1==3) ) return CKMMatrix[7];
  if( (pdgId1==6 && pdgId2==5) || (pdgId2==6 && pdgId1==5) ) return CKMMatrix[8];
  
  std::cout << "VCKM element access failure" << std::endl;

  return -999;
}

double LPXSignalReweightingTool::VLEP(int pdgId1, int pdgId2) {

  pdgId1 = abs(pdgId1);
  pdgId2 = abs(pdgId2);

  // nue_l pairs
  if( (pdgId1==12 && pdgId2==11) || (pdgId2==12 && pdgId1==11) ) return LEPMatrix[0];
  if( (pdgId1==12 && pdgId2==13) || (pdgId2==12 && pdgId1==13) ) return LEPMatrix[1];
  if( (pdgId1==12 && pdgId2==15) || (pdgId2==12 && pdgId1==15) ) return LEPMatrix[2];
  
  // numu_l pairs
  if( (pdgId1==14 && pdgId2==11) || (pdgId2==14 && pdgId1==11) ) return LEPMatrix[3];
  if( (pdgId1==14 && pdgId2==13) || (pdgId2==14 && pdgId1==13) ) return LEPMatrix[4];
  if( (pdgId1==14 && pdgId2==15) || (pdgId2==14 && pdgId1==15) ) return LEPMatrix[5];
  
  // nutau_l pairs
  if( (pdgId1==16 && pdgId2==11) || (pdgId2==16 && pdgId1==11) ) return LEPMatrix[6];
  if( (pdgId1==16 && pdgId2==13) || (pdgId2==16 && pdgId1==13) ) return LEPMatrix[7];
  if( (pdgId1==16 && pdgId2==15) || (pdgId2==16 && pdgId1==15) ) return LEPMatrix[8];

  std::cout << "VLEP element access failure" << std::endl;

  return -999;
}
