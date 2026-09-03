
// LPX Include(s)
#include "ZPrime/ZPrimeTripletSignalModule.h"

// ROOT Include(s)
#include <TLorentzVector.h>

// C++ Include(s)
#include <math.h>

using namespace std;

ZPrimeTripletSignalModule::ZPrimeTripletSignalModule(const std::string& name) :
  LPXSignalReweightingTool(name), classname(name.c_str()) {
}

ZPrimeTripletSignalModule::~ZPrimeTripletSignalModule() {
}

void ZPrimeTripletSignalModule::initialize() {
  return; 
}

void ZPrimeTripletSignalModule::execute(Double_t _sHat, Double_t _sHat_qq, Double_t _sHat_ll, Double_t _sHat_zp, Int_t _pdgId_q1, Int_t _pdgId_q2, Int_t _pdgId_l1, Int_t _pdgId_l2, TLorentzVector _vec_q1, TLorentzVector _vec_q2, TLorentzVector _vec_l1, TLorentzVector _vec_l2) {
  
  // cm energy
  sHat     = _sHat; 
  sHat_qq  = _sHat_qq;
  sHat_ll  = _sHat_ll;
  sHat_zp  = _sHat_zp;
  
  // quark pid
  pdgId_q1 = _pdgId_q1;
  pdgId_q2 = _pdgId_q2;

  // lepton pid
  pdgId_l1 = _pdgId_l1;
  pdgId_l2 = _pdgId_l2;

  // quark/lepton four vectors
  vec_q1 = _vec_q1;
  vec_q2 = _vec_q2;
  vec_l1 = _vec_l1;
  vec_l2 = _vec_l2;
  
  return;
}

void ZPrimeTripletSignalModule::execute(Double_t _sHat, Double_t _tHat, Double_t _uHat, Int_t _pdgId_q1, Int_t _pdgId_q2, Int_t _pdgId_l1, Int_t _pdgId_l2)
{
  sHat = _sHat;
  uHat = _uHat;
  tHat = _tHat;

  // quark pid
  if(_pdgId_q1 == 21 && _pdgId_q2 != 21){
    pdgId_q1 = _pdgId_q2 * (-1);
    pdgId_q2 = _pdgId_q2;
  }
  else if(_pdgId_q1 != 21 && _pdgId_q2 == 21){
    pdgId_q1 = _pdgId_q1;
    pdgId_q2 = _pdgId_q1 * (-1);
  }
  else if(_pdgId_q1 != 21 && _pdgId_q2 != 21){
    pdgId_q1 = _pdgId_q1;
    pdgId_q2 = _pdgId_q2;
  }
  else{
    pdgId_q1 = 0;
    pdgId_q2 = 0;
    std::cout<<"ERROR! gluon-gluon events."<<std::endl;
  }

  // lepton pid
  pdgId_l1 = _pdgId_l1;
  pdgId_l2 = _pdgId_l2;

  return;
}

void ZPrimeTripletSignalModule::setChannel(string channel) {
  
  if(channel=="electron") lepId=11; 
  if(channel=="muon")     lepId=13;
  if(channel=="tau")      lepId=15;
  
  // channel set check
  if(!(channel=="electron" || channel=="muon" || channel=="tau")) {
    std::cerr << "setChannel() -- Failed to set lepton final state. Exiting." << std::endl;
    return; 
  }

  return; 
}

void ZPrimeTripletSignalModule::setgmZMode(int mode) {

  // option 0 : full gamma/Z^0/Z'^0 structure
  // option 1 : only pure gamma contribution
  // option 2 : only pure Z^0 contribution
  // option 3 : only pure Z'^0 contribution
  // option 4 : only the gamma/Z^0 contribution
  // option 5 : only the gamma/Z'^0 contribution
  // option 6 : only the Z^0/Z'^0 contribution

  gmZmode = mode;
  
  // gmZmode set check
  if(gmZmode<0 || gmZmode>6) {
    std::cerr << "setgmZMode() -- Failed to set gmZmode. Exiting." << std::endl;
    return; 
  }
  
  return;
}

void ZPrimeTripletSignalModule::setZPrimeMass(const double &mass) {
  mZP = mass;
  return; 
}

void ZPrimeTripletSignalModule::setModelParametersSSM(const string &model) {

  // save this...
  m_model = model;
  m_modelClass = "SSM";

  // set SSM fermion left chiral charges
  gLPu = gL(2);  // up-type quarks
  gLPd = gL(1);  // down-type quarks
  gLPv = gL(12); // neutrinos
  gLPl = gL(11); // leptons

  // set SSM fermion right chiral charges
  gRPu = gR(2);  // up-type quarks
  gRPd = gR(1);  // down-type quarks
  gRPv = gR(12); // neutrinos
  gRPl = gR(11); // leptons
    
  // set left hand arrays
  gLPs[0] = 0; 
  gLPs[1] = gLPd; // d
  gLPs[2] = gLPu; // u
  gLPs[3] = gLPd; // s
  gLPs[4] = gLPu; // c
  gLPs[5] = gLPd; // b
  gLPs[6] = gLPu; // t
  gLPs[7] = gLPd; // b'
  gLPs[8] = gLPu; // t'
  gLPs[9] = 0;
  gLPs[10] = 0;
  gLPs[11] = gLPl; // e
  gLPs[12] = gLPv; // ve
  gLPs[13] = gLPl; // mu
  gLPs[14] = gLPv; // vmu
  gLPs[15] = gLPl; // tau
  gLPs[16] = gLPv; // vtau
  gLPs[17] = gLPl; // tau'
  gLPs[18] = gLPv; // vtau'

  // set right hand arrays
  gRPs[0] = 0; 
  gRPs[1] = gRPd; // d
  gRPs[2] = gRPu; // u
  gRPs[3] = gRPd; // s
  gRPs[4] = gRPu; // c
  gRPs[5] = gRPd; // b
  gRPs[6] = gRPu; // t
  gRPs[7] = gRPd; // b'
  gRPs[8] = gRPu; // t'
  gRPs[9] = 0;
  gRPs[10] = 0;
  gRPs[11] = gRPl; // e
  gRPs[12] = gRPv; // ve
  gRPs[13] = gRPl; // mu
  gRPs[14] = gRPv; // vmu
  gRPs[15] = gRPl; // tau
  gRPs[16] = gRPv; // vtau
  gRPs[17] = gRPl; // tau'
  gRPs[18] = gRPv; // vtau'

  // set gammaZP
  calcZPrimeBosonWidth();

  // set rw factor
  calcRW();

  return; 
}

void ZPrimeTripletSignalModule::setModelParametersE6(const string &model, const double &thetaE6User) {

  // save this...
  m_model = model;
  m_modelClass = "E6";

  // using Hewett, Rizzo angle convention...
  double thetaE6 = 0;
  if (model=="SQ")        thetaE6 = 0.62935* TMath::Pi();   // SQ model
  else if (model=="I")    thetaE6 = -1.0* TMath::ASin(TMath::Sqrt(5./8.)); // I model
  else if (model=="N")    thetaE6 = TMath::ASin(-1.0/4.0);	           // N model
  else if (model=="Psi")  thetaE6 = 0.0;	                           // Psi model
  else if (model=="Chi")  thetaE6 = TMath::Pi()/2.;                        // Chi model
  else if (model=="Eta")  thetaE6 = TMath::ASin(TMath::Sqrt(3./8.));       // Eta model
  else if (model=="User") thetaE6 = thetaE6User;                           // User Defined
  else {
    std::cerr << "setModelParameters() -- Failed to set an E6 model. Exiting." << std::endl;
    return;
  }

  // E6 charges are linear combination of Psi and Chi states
  double A = cos(thetaE6)/(2.0*sqrt(6.0));  // psi basis
  double B = sin(thetaE6)/(2.0*sqrt(10.0)); // chi basis
  
  // set E6 fermion left chiral charges
  gLPu = (1.0)*A-(-1.0)*B;
  gLPd = (1.0)*A-(-1.0)*B;
  gLPv = (1.0)*A-(3.0)*B;
  //gLPv =  (1.0)*A-(3.0)*B;  // with RH nu on
  gLPl = (1.0)*A-(3.0)*B;

  // set E6 fermion right chiral charges
  gRPu = (-1.0)*A-(1.0)*B;
  gRPd = (-1.0)*A-(-3.0)*B;
  gRPv = 0.0;
  //gRPv =  (-1.0)*A-(5.0)*B; // with RH nu on
  gRPl = (-1.0)*A-(1.0)*B;
  
  // set left hand arrays
  gLPs[0] = 0; 
  gLPs[1] = gLPd; // d
  gLPs[2] = gLPu; // u
  gLPs[3] = gLPd; // s
  gLPs[4] = gLPu; // c
  gLPs[5] = gLPd; // b
  gLPs[6] = gLPu; // t
  gLPs[7] = gLPd; // b'
  gLPs[8] = gLPu; // t'
  gLPs[9] = 0;
  gLPs[10] = 0;
  gLPs[11] = gLPl; // e
  gLPs[12] = gLPv; // ve
  gLPs[13] = gLPl; // mu
  gLPs[14] = gLPv; // vmu
  gLPs[15] = gLPl; // tau
  gLPs[16] = gLPv; // vtau
  gLPs[17] = gLPl; // tau'
  gLPs[18] = gLPv; // vtau'

  // set right hand arrays
  gRPs[0] = 0; 
  gRPs[1] = gRPd; // d
  gRPs[2] = gRPu; // u
  gRPs[3] = gRPd; // s
  gRPs[4] = gRPu; // c
  gRPs[5] = gRPd; // b
  gRPs[6] = gRPu; // t
  gRPs[7] = gRPd; // b'
  gRPs[8] = gRPu; // t'
  gRPs[9] = 0;
  gRPs[10] = 0;
  gRPs[11] = gRPl; // e
  gRPs[12] = gRPv; // ve
  gRPs[13] = gRPl; // mu
  gRPs[14] = gRPv; // vmu
  gRPs[15] = gRPl; // tau
  gRPs[16] = gRPv; // vtau
  gRPs[17] = gRPl; // tau'
  gRPs[18] = gRPv; // vtau'

  // set gammaZP
  calcZPrimeBosonWidth();

  // set rw factor
  calcRW();
  
  return; 
}

void ZPrimeTripletSignalModule::setModelParametersMin(const string &model, const double &gammaUser, const double &thetaMinUser) {
  
  // save this...
  m_model = model;
  m_modelClass = "Minimal";

  // initialize Minimal Model
  double gamma = 0; 
  double thetaMin = 0;
  
  if(model=="User") {                       // User Defined
    gamma    = gammaUser; 
    thetaMin = thetaMinUser;
  } else if(model=="BL") {                  // B-L Model
    gamma    = sqrt(5./8)*sw;
    thetaMin = TMath::ASin(0.0);
  } else if(model=="3R") {                  // 3R Model
    gamma    = sqrt(25./12)*sw;
    thetaMin = TMath::ASin(-sqrt(4./5));
  } else if(model=="Chi") {                 // Chi Model
    gamma    = sqrt(41./24)*sw;
    thetaMin = TMath::ASin(-sqrt(16./41));
  } else if(model=="Upper") {               // Upper boundary Model
    gamma    = gammaUser;
    thetaMin = atan(-1.19);
  } else if(model=="Lower") {               // Lower boundary Model
    gamma    = gammaUser;
    thetaMin = atan(1.43);
  } else {
    std::cerr << "setModelParameters() -- Failed to set a Minimal model. Exiting." << std::endl;
    return;
  }
  
  // some typical thetaMin values
  // { 0.0, -0.6747, -1.1071, -0.87,         0.96         };
  // { B-L, Chi,     3R,      arctan(-1.19), arctan(1.43) };

  // Minimal Z' couplings
  double g_BL = gamma*cos(thetaMin);
  double g_Y  = gamma*sin(thetaMin);
  // std::cout << g_BL << " " << g_Y << std::endl;
      
  // set Minimal Z' left chiral charges
  gLPu =  1/6.*g_Y + 1/3.*g_BL;
  gLPd =  1/6.*g_Y + 1/3.*g_BL;
  gLPv = -1/2.*g_Y - 1.*g_BL;
  gLPl = -1/2.*g_Y - 1.*g_BL;

  // set Minimal Z' right chiral charges
  gRPu =  2./3.*g_Y + 1/3.*g_BL;
  gRPd = -1./3.*g_Y + 1/3.*g_BL;
  gRPv =  0.0;
  //gRPv = 0.0*g_Y - 1.*g_BL; // with RH nu on
  gRPl = -1.*g_Y - 1.*g_BL;

  // inline double gLP(const int &pdgId) { return Y[pdgId]*g_Y + BL[pdgId]*g_BL; };
  
  // set left hand arrays
  gLPs[0] = 0;
  gLPs[1] = gLPd; // d
  gLPs[2] = gLPu; // u
  gLPs[3] = gLPd; // s
  gLPs[4] = gLPu; // c
  gLPs[5] = gLPd; // b
  gLPs[6] = gLPu; // t
  gLPs[7] = gLPd; // b'
  gLPs[8] = gLPu; // t'
  gLPs[9] = 0;
  gLPs[10] = 0;
  gLPs[11] = gLPl; // e
  gLPs[12] = gLPv; // ve
  gLPs[13] = gLPl; // mu
  gLPs[14] = gLPv; // vmu
  gLPs[15] = gLPl; // tau
  gLPs[16] = gLPv; // vtau
  gLPs[17] = gLPl; // tau'
  gLPs[18] = gLPv; // vtau'

  // set right hand arrays
  gRPs[0] = 0;
  gRPs[1] = gRPd; // d
  gRPs[2] = gRPu; // u
  gRPs[3] = gRPd; // s
  gRPs[4] = gRPu; // c
  gRPs[5] = gRPd; // b
  gRPs[6] = gRPu; // t
  gRPs[7] = gRPd; // b'
  gRPs[8] = gRPu; // t'
  gRPs[9] = 0;
  gRPs[10] = 0;
  gRPs[11] = gRPl; // e
  gRPs[12] = gRPv; // ve
  gRPs[13] = gRPl; // mu
  gRPs[14] = gRPv; // vmu
  gRPs[15] = gRPl; // tau
  gRPs[16] = gRPv; // vtau
  gRPs[17] = gRPl; // tau'
  gRPs[18] = gRPv; // vtau'
  
  // set gammaZP
  calcZPrimeBosonWidth();

  // set rw factor
  calcRW();
  
  return; 
}

void ZPrimeTripletSignalModule::setModelParametersTriplet(const std::string &model, const double &gTqUser, const double &gTlUser, const double &gPhiUser) {
  
  // save this...
  m_model = model;
  m_modelClass = "Triplet";
  
  // initialize triplet Model
  double gTq  = 0.; 
  double gTl  = 0.;
  gPhi = 0.;
  
  if(model=="User") {  // User Defined
    gTq  = gTqUser; 
    gTl  = gTlUser;
    gPhi = gPhiUser;
  } else {
    std::cerr << "setModelParameters() -- Failed to set triplet model. Exiting." << std::endl;
    return;
  }

  // set triplet fermion left chiral charges
  gLPu = (-0.5)*gTq; // up-type quarks
  gLPd = 0.5*gTq;    // down-type quarks
  gLPv = (-0.5)*gTl; // neutrinos
  gLPl = 0.5*gTl;    // leptons

  // set triplet fermion right chiral charges
  gRPu = 0.;         // up-type quarks
  gRPd = 0.;         // down-type quarks
  gRPv = 0.;         // neutrinos
  gRPl = 0.;         // leptons
    
  // set left hand arrays
  gLPs[0] = 0; 
  gLPs[1] = gLPd; // d
  gLPs[2] = gLPu; // u
  gLPs[3] = gLPd; // s
  gLPs[4] = gLPu; // c
  gLPs[5] = gLPd; // b
  gLPs[6] = gLPu; // t
  gLPs[7] = gLPd; // b'
  gLPs[8] = gLPu; // t'
  gLPs[9] = 0;
  gLPs[10] = 0;
  gLPs[11] = gLPl; // e
  gLPs[12] = gLPv; // ve
  gLPs[13] = gLPl; // mu
  gLPs[14] = gLPv; // vmu
  gLPs[15] = gLPl; // tau
  gLPs[16] = gLPv; // vtau
  gLPs[17] = gLPl; // tau'
  gLPs[18] = gLPv; // vtau'

  // set right hand arrays
  gRPs[0] = 0; 
  gRPs[1] = gRPd; // d
  gRPs[2] = gRPu; // u
  gRPs[3] = gRPd; // s
  gRPs[4] = gRPu; // c
  gRPs[5] = gRPd; // b
  gRPs[6] = gRPu; // t
  gRPs[7] = gRPd; // b'
  gRPs[8] = gRPu; // t'
  gRPs[9] = 0;
  gRPs[10] = 0;
  gRPs[11] = gRPl; // e
  gRPs[12] = gRPv; // ve
  gRPs[13] = gRPl; // mu
  gRPs[14] = gRPv; // vmu
  gRPs[15] = gRPl; // tau
  gRPs[16] = gRPv; // vtau
  gRPs[17] = gRPl; // tau'
  gRPs[18] = gRPv; // vtau'

  // set gammaZP
  calcZPrimeBosonWidth();

  // set rw factor
  calcRW();

  return; 
}

double ZPrimeTripletSignalModule::getRWFactor() {
  return rw;
}

double ZPrimeTripletSignalModule::getSH() {
  return sHat;
}

double ZPrimeTripletSignalModule::getGammaZP() {
  calcZPrimeBosonWidth();
  return gammaZP;
}

void ZPrimeTripletSignalModule::printEventInfo() {
  
  // incoming/outgoing fermion flavor
  int idAbs = abs(pdgId_q1);
  int idNew = abs(pdgId_l1);
   
  std::cout << " sqrtsH:   " << sqrt(sHat) << " GeV" << std::endl;
  std::cout << " quarkId:  " << idAbs      << ", leptonId: " << idNew << std::endl;
  std::cout << " SM:       " << sigmaSM    << ", BSM:     " << sigmaBSM << std::endl;

  return; 
}

void ZPrimeTripletSignalModule::printModelParameters() {
    
  // incoming/outgoing fermion flavor
  int idAbs = abs(pdgId_q1);
  int idNew = abs(pdgId_l1);
  
  std::cout << " model:    " << m_modelClass << ": " << m_model << std::endl;
  std::cout << "  Qq:      " << Q(idAbs)   << ", Ql:      " << Q(idNew) << std::endl;
  std::cout << "  gLq:     " << gL(idAbs)  << ", gLl:     " << gL(idNew) << std::endl;
  std::cout << "  gLq':    " << gLP(idAbs) << ", gLl':    " << gLP(idNew) << std::endl;
  std::cout << "  gRq:     " << gR(idAbs)  << ", gRl:     " << gR(idNew) << std::endl;
  std::cout << "  gRq':    " << gRP(idAbs) << ", gRl':    " << gRP(idNew) << std::endl;
  std::cout << "  gZ':     " << gZP << std::endl;
  std::cout << "  gammaZ': " << gammaZP << std::endl;
  std::cout << "  mZ':     " << mZP << std::endl;

  return; 
}

inline void ZPrimeTripletSignalModule::calcZPrimeBosonWidth() {
  
  // set gauge couplings to scale of mZ'
  e = sqrt(4.0*TMath::Pi()*alphaEM(mZP*mZP));
  gZP = e/(sw*cw);
  if(m_modelClass=="E6")      gZP = e*sqrt(5.0/(3.0*(1.0-sw2)));
  if(m_modelClass=="Triplet") gZP = 1.;
  //std::cout << "     gZP: " << gZP << std::endl; 
  
  // useful prefactors 
  double g0 = pow(gZP,2)*mZP/(24.0*TMath::Pi());
  double CF = 3; // color factor for number of quark colors

  // QCD radiative corrections
  double rQCD = 1.0 + alphaS(mZP*mZP)/TMath::Pi();
  
  // calculate Z' partial widths
  double gamma_nu = g0*(pow(gLP(12),2) + pow(gRP(12),2));        // Z' partial width to neutrinos
  double gamma_l  = g0*(pow(gLP(11),2) + pow(gRP(11),2));        // Z' partial width to charged leptons
  double gamma_d  = g0*CF*rQCD*(pow(gLP(1),2) + pow(gRP(1),2));  // Z' partial width to down-quarks
  double gamma_u  = g0*CF*rQCD*(pow(gLP(2),2) + pow(gRP(2),2));  // Z' partial width to light up-quarks
  //std::cout << "     Z' width to v: " << gamma_nu << std::endl;
  //std::cout << "     Z' width to l: " << gamma_l << std::endl;
  //std::cout << "     Z' width to d: " << gamma_d << std::endl;
  //std::cout << "     Z' width to u: " << gamma_u << std::endl;
  
  // Z' partial width to dibosons
  double gamma_H  = pow(gPhi,2)*mZP/(96.0*TMath::Pi());

  // include threshold factors for top decays
  double r = pow(m(6)/mZP,2);
  double gamma_t = g0*CF*rQCD*( 0.5*pow(gLP(6)+gRP(6),2)*(1+2.0*r) +
				0.5*pow(gLP(6)-gRP(6),2)*(1-4.0*r) )*sqrt(1-4.0*r);
  //std::cout << "     Z' width to t: " << gamma_t << std::endl;
  
  // calculate Z' total width by summing over partial widths
  gammaZP = 3.0*gamma_nu + 3.0*gamma_l + 3.0*gamma_d + 2.0*gamma_u;
  if(mZP > 2.0*m(6)) gammaZP += gamma_t;
  //std::cout << gammaZP << "   ";
  if (m_modelClass=="Triplet") gammaZP += gamma_H;
  //std::cout << gammaZP << std::endl;
  //std::cout << "     Z' Width: " << gammaZP << std::endl;
  
  return; 
}

inline void ZPrimeTripletSignalModule::calcBSMXS() {
  
  // calculate mandalstam invariants
  //double sH = (vec_q1 + vec_q2)*(vec_q1 + vec_q2);
  //double tH = (vec_q1 - vec_l1)*(vec_q1 - vec_l1);
  //double uH = (vec_q1 - vec_l2)*(vec_q1 - vec_l2);
  double sH = sHat;
  double tH = tHat;
  double uH = uHat;

  // and square them
  double sH2 = sH * sH;
  double tH2 = tH * tH;
  double uH2 = uH * uH;
  
  // initialize photon propagator
  complex<double> aPropagator(sH, 0.0);
  aPropagator = 1.0 / aPropagator;

  // initialize Z propagator
  complex<double> zPropagator(sH-mZ*mZ, sH*gammaZ/mZ);
  zPropagator = 1.0 / zPropagator;
  
  // initialize Z' amplitude
  complex<double> zPrimePropagator(sH-mZP*mZP, sH*gammaZP/mZP);
  zPrimePropagator = 1.0 / zPrimePropagator;
  
  // incoming/outgoing fermion flavor
  int idAbs = abs(pdgId_q1);
  int idNew = abs(pdgId_l1);

  // set gauge couplings to scale of event
  e = sqrt(4.0*TMath::Pi()*alphaEM(sH));
  gZ = e/(sw*cw);
  if(m_modelClass=="E6")      gZP = e*sqrt(5.0/(3.0*(1-sw2)));
  if(m_modelClass=="Triplet") gZP = 1.;

  // cross-section prefactor
  double sigma0 = 1./(16. * TMath::Pi() * sH2);  

  // construct chiral amplitudes
  complex<double> ameLL  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeLL  = gZ*gL(idAbs)*gZ*gL(idNew)*zPropagator;
  complex<double> zpmeLL = gZP*gLP(idAbs)*gZP*gLP(idNew)*zPrimePropagator;

  complex<double> ameRR  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeRR  = gZ*gR(idAbs)*gZ*gR(idNew)*zPropagator;
  complex<double> zpmeRR = gZP*gRP(idAbs)*gZP*gRP(idNew)*zPrimePropagator;

  complex<double> ameLR  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeLR  = gZ*gL(idAbs)*gZ*gR(idNew)*zPropagator;
  complex<double> zpmeLR = gZP*gLP(idAbs)*gZP*gRP(idNew)*zPrimePropagator;

  complex<double> ameRL  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeRL  = gZ*gR(idAbs)*gZ*gL(idNew)*zPropagator;
  complex<double> zpmeRL = gZP*gRP(idAbs)*gZP*gLP(idNew)*zPrimePropagator;

  // construct total amplitude based on user set gmZmode
  complex<double> meLL, meLR, meRL, meRR;
  if(gmZmode==0) {
    meLL = ameLL + zmeLL + zpmeLL;
    meLR = ameLR + zmeLR + zpmeLR;
    meRL = ameRL + zmeRL + zpmeRL;
    meRR = ameRR + zmeRR + zpmeRR;
  } else if(gmZmode==1) {
    meLL = ameLL;
    meLR = ameLR;
    meRL = ameRL;
    meRR = ameRR;
  } else if(gmZmode==2) {
    meLL = zmeLL;
    meLR = zmeLR;
    meRL = zmeRL;
    meRR = zmeRR;
  } else if(gmZmode==3) {
    meLL = zpmeLL;
    meLR = zpmeLR;
    meRL = zpmeRL;
    meRR = zpmeRR;
  } else if(gmZmode==4) {
    meLL = ameLL + zmeLL;
    meLR = ameLR + zmeLR;
    meRL = ameRL + zmeRL;
    meRR = ameRR + zmeRR;
  } else if(gmZmode==5) {
    meLL = ameLL + zpmeLL;
    meLR = ameLR + zpmeLR;
    meRL = ameRL + zpmeRL;
    meRR = ameRR + zpmeRR;
  } else if(gmZmode==6) {
    meLL = zmeLL + zpmeLL;
    meLR = zmeLR + zpmeLR;
    meRL = zmeRL + zpmeRL;
    meRR = zmeRR + zpmeRR;
  } else {
    std::cerr << "calcBSMXS() -- gmZmode set outside acceptable range. Exiting." << std::endl;
    return; 
  }
  
  // calculate dsigma/d(tHat)
  double sigma = sigma0 * uH2 * real(meLL*conj(meLL));
  sigma += sigma0 * uH2 * real(meRR*conj(meRR));
  sigma += sigma0 * tH2 * real(meLR*conj(meLR));
  sigma += sigma0 * tH2 * real(meRL*conj(meRL));
  
  /*
  // calculate sigma; integrated out angular terms
  double sigma = sigma0 * (3.*TMath::Pi()/2.) * real(meLL*conj(meLL));
  sigma += sigma0 * (3.*TMath::Pi()/2.) * real(meRR*conj(meRR));
  sigma += sigma0 * (3.*TMath::Pi()/2.) * real(meLR*conj(meLR));
  sigma += sigma0 * (3.*TMath::Pi()/2.) * real(meRL*conj(meRL));
  */

  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;
 
  // give sigma dimensions
  sigma *= 3.8938*pow(10,8); // GeV^2 * pB
  
  // set as member variable
  sigmaBSM = sigma;
  
  return; 
}

inline void ZPrimeTripletSignalModule::calcSMXS() {
  
  // calculate Mandalstam invariants
  //double sH = (vec_q1 + vec_q2)*(vec_q1 + vec_q2);
  //double tH = (vec_q1 - vec_l1)*(vec_q1 - vec_l1);
  //double uH = (vec_q1 - vec_l2)*(vec_q1 - vec_l2);
  double sH = sHat;
  double tH = tHat;
  double uH = uHat;

  // ...and square them
  double sH2 = sH * sH;
  double tH2 = tH * tH;
  double uH2 = uH * uH;
  
  // initialize photon propagator
  complex<double> aPropagator(sH, 0.0);
  aPropagator = 1.0 / aPropagator;

  // initialize Z propagator
  complex<double> zPropagator(sH-mZ*mZ, sH*gammaZ/mZ);
  zPropagator = 1.0 / zPropagator;
    
  // Incoming/Outgoing fermion flavor
  int idAbs = abs(pdgId_q1);
  int idNew = abs(pdgId_l1);
  
  // run gauge couplings to scale of event
  e = sqrt(4.0*TMath::Pi()*alphaEM(sH));
  gZ = e/(sw*cw);

  // cross-section prefactor
  double sigma0 = 1./(16. * TMath::Pi() * sH2);  

  // construct chiral amplitudes
  complex<double> meLL = e*Q(idAbs)*e*Q(idNew)*aPropagator
    + gZ*gL(idAbs)*gZ*gL(idNew)*zPropagator;

  complex<double> meRR = e*Q(idAbs)*e*Q(idNew)*aPropagator
    + gZ*gR(idAbs)*gZ*gR(idNew)*zPropagator;

  complex<double> meLR = e*Q(idAbs)*e*Q(idNew)*aPropagator
    + gZ*gL(idAbs)*gZ*gR(idNew)*zPropagator;

  complex<double> meRL = e*Q(idAbs)*e*Q(idNew)*aPropagator
    + gZ*gR(idAbs)*gZ*gL(idNew)*zPropagator;
  
  // calculate dsigma/d(tHat)
  double sigma = sigma0 * uH2 * real(meLL*conj(meLL));
  sigma += sigma0 * uH2 * real(meRR*conj(meRR));
  sigma += sigma0 * tH2 * real(meLR*conj(meLR));
  sigma += sigma0 * tH2 * real(meRL*conj(meRL));
  
  /*
  // calculate sigma; integrated out angular terms
  double sigma = sigma0 * (3.*TMath::Pi()/2.) * real(meLL*conj(meLL));
  sigma += sigma0 * (3.*TMath::Pi()/2.) * real(meRR*conj(meRR));
  sigma += sigma0 * (3.*TMath::Pi()/2.) * real(meLR*conj(meLR));
  sigma += sigma0 * (3.*TMath::Pi()/2.) * real(meRL*conj(meRL));
  */

  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;
 
  // give sigma dimensions
  sigma *= 3.8938*pow(10,8); // GeV^2 * pB
  
  // set as member variable
  sigmaSM = sigma;

  return; 
}

inline void ZPrimeTripletSignalModule::calcRW() {
  
  // calculate mandalstam invariants
  //double sH = (vec_q1 + vec_q2)*(vec_q1 + vec_q2);
  //double tH = (vec_q1 - vec_l1)*(vec_q1 - vec_l1);
  //double uH = (vec_q1 - vec_l2)*(vec_q1 - vec_l2);
  double sH = sHat;
  double tH = tHat;
  double uH = uHat;

  // and square them
  double sH2 = sH * sH;
  double tH2 = tH * tH;
  double uH2 = uH * uH;
  
  // incoming/outgoing fermion flavor
  int idAbs = abs(pdgId_q1);
  int idNew = abs(pdgId_l1);

  // calculate SM x-sec
  // ===================

  // set gauge couplings to scale of event
  e = sqrt(4.0*TMath::Pi()*alphaEM(sH));
  gZ = e/(sw*cw);

  // initialize photon propagator
  complex<double> aPropagator(sH, 0.0);
  aPropagator = 1.0 / aPropagator;

  // initialize Z propagator
  complex<double> zPropagator(sH-mZ*mZ, sH*gammaZ/mZ);
  zPropagator = 1.0 / zPropagator;
  
  // cross-section prefactor
  double sigma0 = 1./(16. * TMath::Pi() * sH2);  

  // construct chiral amplitudes for photon, Z
  complex<double> ameLL  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeLL  = gZ*gL(idAbs)*gZ*gL(idNew)*zPropagator;

  complex<double> ameRR  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeRR  = gZ*gR(idAbs)*gZ*gR(idNew)*zPropagator;

  complex<double> ameLR  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeLR  = gZ*gL(idAbs)*gZ*gR(idNew)*zPropagator;

  complex<double> ameRL  = e*Q(idAbs)*e*Q(idNew)*aPropagator;
  complex<double> zmeRL  = gZ*gR(idAbs)*gZ*gL(idNew)*zPropagator;

  // construct the total amplitude
  complex<double> meLL = ameLL + zmeLL;
  complex<double> meLR = ameLR + zmeLR;
  complex<double> meRL = ameRL + zmeRL;
  complex<double> meRR = ameRR + zmeRR;
  
  // calculate dsigma/d(tHat)
  double sigma = sigma0 * uH2 * real(meLL*conj(meLL));
  sigma += sigma0 * uH2 * real(meRR*conj(meRR));
  sigma += sigma0 * tH2 * real(meLR*conj(meLR));
  sigma += sigma0 * tH2 * real(meRL*conj(meRL));
  
  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;
 
  // give sigma dimensions
  sigma *= 3.8938*pow(10,8); // GeV^2 * pB
  
  // set as member variable
  sigmaSM = sigma;

  // calculate BSM x-sec
  // ===================
  
  // set gauge couplings to scale of event
  gZP = e/(sw*cw);
  if(m_modelClass=="E6")      gZP = e*sqrt(5.0/(3.0*(1-sw2)));
  if(m_modelClass=="Triplet") gZP = 1.;

  // initialize Z' amplitude
  complex<double> zPrimePropagator(sH-mZP*mZP, sH*gammaZP/mZP);
  zPrimePropagator = 1.0 / zPrimePropagator;

  // reset
  sigma = 0;

  // cross-section prefactor
  sigma0 = 1./(16. * TMath::Pi() * sH2);  

  // construct chiral amplitudes for Z'
  complex<double> zpmeLL = gZP*gLP(idAbs)*gZP*gLP(idNew)*zPrimePropagator;
  complex<double> zpmeRR = gZP*gRP(idAbs)*gZP*gRP(idNew)*zPrimePropagator;
  complex<double> zpmeLR = gZP*gLP(idAbs)*gZP*gRP(idNew)*zPrimePropagator;
  complex<double> zpmeRL = gZP*gRP(idAbs)*gZP*gLP(idNew)*zPrimePropagator;
  
  // construct total amplitude based on user set gmZmode
  if(gmZmode==0) {
    meLL = ameLL + zmeLL + zpmeLL;
    meLR = ameLR + zmeLR + zpmeLR;
    meRL = ameRL + zmeRL + zpmeRL;
    meRR = ameRR + zmeRR + zpmeRR;
  } else if(gmZmode==1) {
    meLL = ameLL;
    meLR = ameLR;
    meRL = ameRL;
    meRR = ameRR;
  } else if(gmZmode==2) {
    meLL = zmeLL;
    meLR = zmeLR;
    meRL = zmeRL;
    meRR = zmeRR;
  } else if(gmZmode==3) {
    meLL = zpmeLL;
    meLR = zpmeLR;
    meRL = zpmeRL;
    meRR = zpmeRR;
  } else if(gmZmode==4) {
    meLL = ameLL + zmeLL;
    meLR = ameLR + zmeLR;
    meRL = ameRL + zmeRL;
    meRR = ameRR + zmeRR;
  } else if(gmZmode==5) {
    meLL = ameLL + zpmeLL;
    meLR = ameLR + zpmeLR;
    meRL = ameRL + zpmeRL;
    meRR = ameRR + zpmeRR;
  } else if(gmZmode==6) {
    meLL = zmeLL + zpmeLL;
    meLR = zmeLR + zpmeLR;
    meRL = zmeRL + zpmeRL;
    meRR = zmeRR + zpmeRR;
  } else {
    std::cerr << "calcBSMXS() -- gmZmode set outside acceptable range. Exiting." << std::endl;
    return; 
  }
  
  // calculate dsigma/d(tHat)
  sigma = sigma0 * uH2 * real(meLL*conj(meLL));
  sigma += sigma0 * uH2 * real(meRR*conj(meRR));
  sigma += sigma0 * tH2 * real(meLR*conj(meLR));
  sigma += sigma0 * tH2 * real(meRL*conj(meRL));
  
  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;
 
  // give sigma dimensions
  sigma *= 3.8938*pow(10,8); // GeV^2 * pB
  
  // set as member variable
  sigmaBSM = sigma;

  // ... and this too
  rw = sigmaBSM/sigmaSM;
  //std::cout<<m_model<<"  "<<sigmaBSM<<"  "<<sigmaSM<<"  "<<rw<<std::endl;
  return; 
}

bool ZPrimeTripletSignalModule::isPythiaZeeMC(unsigned int DSID){
  if( (DSID >= 301540) && (DSID <= 301559) ) return true;
  return false;
}

bool ZPrimeTripletSignalModule::isPythiaZmumuMC(unsigned int DSID){
  if( (DSID >= 301560) && (DSID <= 301579) ) return true;
  return false;
}

/*
bool ZPrimeTripletSignalModule::isPythiaZtautauMC(unsigned int DSID){
  if( (DSID >= xxx) && (DSID <= yyy) ) return true;
  return false;
}
*/

bool ZPrimeTripletSignalModule::isPythiaZllMC(unsigned int DSID){
  if(isPythiaZeeMC(DSID)) return true;
  if(isPythiaZmumuMC(DSID)) return true;
  //if(isPythiaZtautauMC(DSID)) return true;
  return false;
}
