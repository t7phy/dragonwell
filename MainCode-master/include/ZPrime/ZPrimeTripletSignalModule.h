/*
 *  ZPrimeTripletSignalModule.h
 *
 *  latest update on: Nov 17, 2016
 *  Authors: Daniel Hayden (daniel.hayden@cern.ch), 
 *           Christopher Willis (Christopher.Willis@cern.ch)
 *
 * Compute cross section for Drell-Yan + Z' Interaction in the 
 * q q-bar --> l+ l- process. This is used to (re)weight DY events 
 * from LO Pythia8 to any DY+Z' model desired. See twiki with 
 * examples and validation plots at xxx
 *
 * Code extracted from Pythia 8.215, see SigmaNewGaugeBoson class
 *
 * Inputs:  vec_q1    1st initial-state parton 4-momentum (in GeV)
 *          vec_q2    2nd initial-state parton 4-momentum (in GeV)
 *          vec_l1    1st final-state lepton 4-momentum (in GeV)
 *          vec_l2    2nd final-state lepton 4-momentum (in GeV)
 *          pdgId_q1  PDG ID for 1st initial-state parton
 *          pdgId_q2  PDG ID for 2nd initial-state parton
 *          pdgId_l1  PDG ID for 1st final-state lepton
 *          pdgId_l2  PDG ID for 2nd final-state lepton
 *          gLPu      up-type quark left chiral charge under U(1)'
 *          gLPd      down-type quark left chiral charge under U(1)'
 *          gLPv      neutrino left chiral charges under U(1)'
 *          gLPl      lepton left chiral charges under U(1)'
 *          gRPu      up-type quark right chiral charge under U(1)'
 *          gRPd      down-type quark right chiral charge under U(1)'
 *          gRPv      neutrino right chiral charges under U(1)'
 *          gRPl      lepton right chiral charges under U(1)'
 *          gZP       Z' gauge coupling constant
 */

#ifndef ZPrime_ZPRIMETRIPLETSIGNALMODULE_H_
#define ZPrime_ZPRIMETRIPLETSIGNALMODULE_H_

// C++ Include(s)
#include <iostream>
#include <string>
#include <complex>

#include <TMath.h>
#include <TLorentzVector.h>

// LPX Include(s)
#include "ZPrime/LPXSignalReweightingTool.h"

#include "Tools/Interpolation.h"

class ZPrimeTripletSignalModule : public LPXSignalReweightingTool {

 public:
  
  // default constructor
  ZPrimeTripletSignalModule(const std::string& name);
   
  // destructor
  virtual ~ZPrimeTripletSignalModule();

  // function initializing the tool
  virtual void initialize();

  // function executing the tool
  virtual void execute(Double_t _sHat, Double_t _sHat_qq, Double_t _sHat_ll, Double_t _sHat_zp, Int_t _pdgId_q1, Int_t _pdgId_q2, Int_t _pdgId_l1, Int_t _pdgId_l2, TLorentzVector _vec_q1, TLorentzVector _vec_q2, TLorentzVector _vec_l1, TLorentzVector _vec_l2);

  // yfu add another function executing the tool for NLO reweighting
  virtual void execute(Double_t _sHat, Double_t _tHat, Double_t _uHat, Int_t _pdgId_q1, Int_t _pdgId_q2, Int_t _pdgId_l1, Int_t _pdgId_l2);
  virtual void execute(Double_t _sHat, Double_t _tHat, Double_t _uHat, Int_t _pdgId_q1, Int_t _pdgId_q2, Int_t _pdgId_l1, Int_t _pdgId_l2, Double_t CosThetaCS, Double_t PhiCS, Double_t dilepton_mass, Double_t dilepton_pt, Double_t dilepton_rapidity);

  // set lepton channel final state flavor
  virtual void setChannel(std::string channel);

  // set DY/Z' interference details
  virtual void setgmZMode(int mode);
  
  // set Z' polemass
  virtual void setZPrimeMass(const double &mass);

  // initialize SSM
  virtual void setModelParametersSSM(const std::string &model);
  
  // initialize E6
  virtual void setModelParametersE6(const std::string &model, const double &thetaE6User=0);

  // initialize Minimal
  virtual void setModelParametersMin(const std::string &model, const double &gammaUser=0, const double &thetaMinUser=0);
  
  // initialize Triplet
  virtual void setModelParametersTriplet(const std::string &model, const double &gTqUser=0, const double &gTlUser=0, const double &gPhiUser=0);
  
  /*
  // set E6 model mixing angle
  virtual void setThetaE6(double thetaE6);
  
  // set Minimal model parameters
  virtual void setGammaMin(double gammaMin);

  // set Minimal model parameter
  virtual void setThetaMin(double thetaMin);
  */

  // get RW factor
  double getRWFactor();
  
  // get scale of partonic hard scatter
  double getSH();

  // get width of Z'
  double getGammaZP();
  
  // print event info
  void printEventInfo();
  
  // print model parameters for event
  void printModelParameters();


  // yfu defined for complete NLO reweighting
  Interpolation* A0_uu;
  Interpolation* A1_uu;
  Interpolation* A2_uu;
  Interpolation* A3_uu;
  Interpolation* A4_uu;
  Interpolation* A0_dd;
  Interpolation* A1_dd;
  Interpolation* A2_dd;
  Interpolation* A3_dd;
  Interpolation* A4_dd;
  Double_t CosThetaCS, PhiCS, dilepton_mass, dilepton_pt, dilepton_rapidity;

  void PrepareInterpolation(TString name);
  void calcRWNLO();

 private:
    
  // function to get fermion left-chiral charge under U(1)'
  inline double gLP(const int &pdgId) { return gLPs[pdgId]; };

  // function to get fermion right-chiral charge under U(1)'
  inline double gRP(const int &pdgId) { return gRPs[pdgId]; };

  // function to calculate Z' Boson Width
  inline void calcZPrimeBosonWidth();

  // function to calculate |a+Z+Z'|^2 differential cross-section at Leading Order
  inline void calcBSMXS();

  // function to calculate |a+Z|^2 differential cross-section at Leading Order
  inline void calcSMXS();
  
  // does both and saves ratio
  inline void calcRW();
  
  // check for correct dielectron MC
  bool isPythiaZeeMC(unsigned int DSID);

  // check for correct dimuon MC
  bool isPythiaZmumuMC(unsigned int DSID);

  // check for correct ditau MC
  bool isPythiaZtautauMC(unsigned int DSID);

  // check for correct dilepton MC
  bool isPythiaZllMC(unsigned int DSID);

  // initialized in initialize()
  // ===========================

  const char* classname;

  // initialized in execute()
  // ========================

  double sHat;
  double tHat;
  double uHat; 
  double sHat_qq;
  double sHat_ll;
  double sHat_zp;
  
  // quark pid
  int pdgId_q1;
  int pdgId_q2;

  // lepton pid
  int pdgId_l1;
  int pdgId_l2;

  // quark/lepton four vectors
  TLorentzVector vec_q1;
  TLorentzVector vec_q2;
  TLorentzVector vec_l1;
  TLorentzVector vec_l2;

  // initialized in setChannel()
  // ===========================
  
  int lepId;

  // initialized in setgmZMode()
  // ===========================

  int gmZmode;

  // initialized in setZPrimeMass()
  // ==============================

  double mZP;

  // initialized in calcZPrimeBosonWidth()
  // =====================================

  double gammaZP;

  // initialized in setModelParameters()
  // ===================================

  std::string m_model;
  std::string m_modelClass;

  // Z' gauge coupling constant
  double gZP;
  
  // gPhi coupling from HVT model
  double gPhi;

  // fermion left chiral charges under U(1)'
  double gLPu;
  double gLPd;
  double gLPv;
  double gLPl;
  double gLPs[19]; // array to contain the above values

  // fermion right chiral charges under U(1)'
  double gRPu;
  double gRPd;
  double gRPv;
  double gRPl;
  double gRPs[19]; // array to contain the above values
  
  //double thetaE6;
  //double gammaMin;
  //double thetaMin;

  // initialized in calcBSMXS()
  // ==========================

  double sigmaBSM;

  // initialized in calcSMXS()
  // =========================
  
  double sigmaSM;
  
  // reweighting factor
  // ==================

  double rw;

};

#endif /* ZPRIMETRIPLETSIGNALMODULE_H_ */
