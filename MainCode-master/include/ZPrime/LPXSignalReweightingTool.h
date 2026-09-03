/*
 *  LPXSignalReweightingTool.h
 *  latest update on: Nov 17, 2016
 *  Authors: Daniel Hayden (daniel.hayden@cern.ch), 
 *           Christopher Willis (Christopher.Willis@cern.ch)
 */

#ifndef ZPrime_LPXSIGNALREWEIGHTINGTOOL_H_
#define ZPrime_LPXSIGNALREWEIGHTINGTOOL_H_

// C++ Include(s)
#include <iostream>
#include <string>
#include <complex>

#include <TMath.h>
#include <TLorentzVector.h>

class LPXSignalReweightingTool {

 public:

  // default constructor
  LPXSignalReweightingTool(const std::string& name);

  // destructor
  virtual ~LPXSignalReweightingTool();
     
  // Function initializing the tool
  virtual void initialize();
  
  // Function executing the tool
  //virtual void execute();
    
 protected:
  
  // calculate running of alphaEM
  inline double alphaEM(const double &Q2) {
    //double alphaEMmZ = 0.00781751;  // Pythia aEM value
    double alphaEMmZ = 0.00781653;  // Powheg aEM value
    double b         = 0.725;       // Pythia mystery value
    return alphaEMmZ/(1.0-b*alphaEMmZ*log(Q2/(mZ*mZ)));
  };
  
  // calculate running of alphaS
  inline double alphaS(const double &Q2) {
    double b0 = 0.557042;
    double QCDL = 0.151142;
    return 1.0/(b0*log(Q2/(QCDL*QCDL)));
  };

  // calculates Z Boson Width at LO
  double calcZBosonWidth();

  // calculates W Boson Width at LO
  double calcWBosonWidth();
  
  // ==============

  // function to get fermion charge
  inline double Q(const int &pdgId) { return qf[pdgId]; };

  // function to get fermion weak isospin projection
  inline double T3L(const int &pdgId) { return t3Lf[pdgId]; };

  // function to get fermion weak hypercharge
  //double Y(int pdgId);

  // function to get fermion baryon number
  //double B(int pdgId);

  // function to get fermion lepton number
  //double L(int pdgId);
  
  // function to get fermion B-L number
  //double BL(int pdgId);

  // function to get fermion left-chiral charge gL
  inline double gL(const int &pdgId) { return t3Lf[pdgId] - qf[pdgId]*sw2; };

  // function to get fermion right-chiral charge gR
  inline double gR(const int &pdgId) { return 0.0 - qf[pdgId]*sw2; };

  // function to get fermion mass in GeV
  inline double m(const int &pdgId) { return mass[pdgId]; };

  // function to get particle width in GeV
  double width(int pdgId);
  
  // ==============
  
  // function to get CKM element
  double VCKM(int pdgId1, int pdgId2);

  // function to get "lepton-CKM" element
  double VLEP(int pdgId1, int pdgId2);

  // ==============
  
  // MeV to GeV conversion factor
  double GeV;

  // CM Energy of LHC
  double s;

  // electroweak scheme
  double GF;
  double mZ;
  double sw2;

  // derived quantities from scheme choice
  double mW;
  double sw;
  double cw2;
  double cw;
  double gammaZ;
  double gammaW;

  // SM Fermion Quantum Numbers (matches Pythia ordering)
  
  // fermion (electric) charges
  double qf[19]; 

  // fermion weak-isospin projections
  double t3Lf[19];

  // fermion masses
  double mass[19];

  // CMK, lepton mixing matrices
  double CKMMatrix[9];
  double LEPMatrix[9];

  // EM gauge coupling constant
  double e;

  // Z Boson gauge coupling constant
  double gZ;
  
  // SU(2)L gauge coupling constant
  double g;
  
 private:
  
  const char* classname;

  std::string m_useAlgorithm;

};


#endif /* LPXSIGNALREWEIGHTINGTOOL_H_ */
