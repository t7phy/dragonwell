// LPX Include(s)
#include "ZPrime/ZPrimeTripletSignalModule.h"

// ROOT Include(s)
#include <TLorentzVector.h>

// C++ Include(s)
#include <math.h>

using namespace std;

void ZPrimeTripletSignalModule::execute(Double_t _sHat, Double_t _tHat, Double_t _uHat, Int_t _pdgId_q1, Int_t _pdgId_q2, Int_t _pdgId_l1, Int_t _pdgId_l2, Double_t CosThetaCS, Double_t PhiCS, Double_t dilepton_mass, Double_t dilepton_pt, Double_t dilepton_rapidity)
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

  this->CosThetaCS = CosThetaCS;
  this->PhiCS = PhiCS;
  this->dilepton_mass = dilepton_mass;
  this->dilepton_pt = dilepton_pt;
  this->dilepton_rapidity = dilepton_rapidity;

  return;
}

void ZPrimeTripletSignalModule::PrepareInterpolation(TString name)
{
 TFile* file = new TFile(name);

 TH3D* tmp_A0_uu = (TH3D *)file->Get("A0_Mass_QT_ZY_uu");
 TH3D* tmp_A1_uu = (TH3D *)file->Get("A1_Mass_QT_ZY_uu");
 TH3D* tmp_A2_uu = (TH3D *)file->Get("A2_Mass_QT_ZY_uu");
 TH3D* tmp_A3_uu = (TH3D *)file->Get("A3_Mass_QT_ZY_uu");
 TH3D* tmp_A4_uu = (TH3D *)file->Get("A4_Mass_QT_ZY_uu");
 TH3D* tmp_A0_dd = (TH3D *)file->Get("A0_Mass_QT_ZY_dd");
 TH3D* tmp_A1_dd = (TH3D *)file->Get("A1_Mass_QT_ZY_dd");
 TH3D* tmp_A2_dd = (TH3D *)file->Get("A2_Mass_QT_ZY_dd");
 TH3D* tmp_A3_dd = (TH3D *)file->Get("A3_Mass_QT_ZY_dd");
 TH3D* tmp_A4_dd = (TH3D *)file->Get("A4_Mass_QT_ZY_dd");

 auto GetGrid = [&](TH3D* hist){
   vector<double> XVector, YVector, ZVector;
   for(int ibinx = 1; ibinx <= hist->GetNbinsX(); ibinx++){
     XVector.push_back(hist->GetXaxis()->GetBinCenter(ibinx));
   }
   for(int ibiny = 1; ibiny <= hist->GetNbinsY(); ibiny++){
     YVector.push_back(hist->GetYaxis()->GetBinCenter(ibiny));
   }
   for(int ibinz = 1; ibinz <= hist->GetNbinsZ(); ibinz++){
     ZVector.push_back(hist->GetZaxis()->GetBinCenter(ibinz));
   }

   bool isSingleMassPoint = false;
   if(XVector.size() == 1){
     XVector = {0.0, 1000.0, 5000.0, 9000.0};
     isSingleMassPoint = true;
   }

   map<vector<int>, double> Points;
   for(int ibinx = 1; ibinx <= XVector.size(); ibinx++){
     for(int ibiny = 1; ibiny <= hist->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= hist->GetNbinsZ(); ibinz++){
         if(isSingleMassPoint){
           Points[(vector<int>{ibinx - 1, ibiny - 1, ibinz - 1})] = hist->GetBinContent(1, ibiny, ibinz);
         }
         else{
           Points[(vector<int>{ibinx - 1, ibiny - 1, ibinz - 1})] = hist->GetBinContent(ibinx, ibiny, ibinz);
         }
       }
     }
   }
   tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> Result = make_tuple(XVector, YVector, ZVector, Points);
   return Result;
 };

 A0_uu = new Interpolation();
 A1_uu = new Interpolation();
 A2_uu = new Interpolation();
 A3_uu = new Interpolation();
 A4_uu = new Interpolation();
 A0_dd = new Interpolation();
 A1_dd = new Interpolation();
 A2_dd = new Interpolation();
 A3_dd = new Interpolation();
 A4_dd = new Interpolation();

 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A0_uu_grid = GetGrid(tmp_A0_uu);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A1_uu_grid = GetGrid(tmp_A1_uu);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A2_uu_grid = GetGrid(tmp_A2_uu);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A3_uu_grid = GetGrid(tmp_A3_uu);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A4_uu_grid = GetGrid(tmp_A4_uu);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A0_dd_grid = GetGrid(tmp_A0_dd);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A1_dd_grid = GetGrid(tmp_A1_dd);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A2_dd_grid = GetGrid(tmp_A2_dd);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A3_dd_grid = GetGrid(tmp_A3_dd);
 tuple<vector<double>, vector<double>, vector<double>, map<vector<int>, double>> A4_dd_grid = GetGrid(tmp_A4_dd);

 A0_uu->InitializeThreeD(get<0>(A0_uu_grid), get<1>(A0_uu_grid), get<2>(A0_uu_grid), get<3>(A0_uu_grid));
 A1_uu->InitializeThreeD(get<0>(A1_uu_grid), get<1>(A1_uu_grid), get<2>(A1_uu_grid), get<3>(A1_uu_grid));
 A2_uu->InitializeThreeD(get<0>(A2_uu_grid), get<1>(A2_uu_grid), get<2>(A2_uu_grid), get<3>(A2_uu_grid));
 A3_uu->InitializeThreeD(get<0>(A3_uu_grid), get<1>(A3_uu_grid), get<2>(A3_uu_grid), get<3>(A3_uu_grid));
 A4_uu->InitializeThreeD(get<0>(A4_uu_grid), get<1>(A4_uu_grid), get<2>(A4_uu_grid), get<3>(A4_uu_grid));
 A0_dd->InitializeThreeD(get<0>(A0_dd_grid), get<1>(A0_dd_grid), get<2>(A0_dd_grid), get<3>(A0_dd_grid));
 A1_dd->InitializeThreeD(get<0>(A1_dd_grid), get<1>(A1_dd_grid), get<2>(A1_dd_grid), get<3>(A1_dd_grid));
 A2_dd->InitializeThreeD(get<0>(A2_dd_grid), get<1>(A2_dd_grid), get<2>(A2_dd_grid), get<3>(A2_dd_grid));
 A3_dd->InitializeThreeD(get<0>(A3_dd_grid), get<1>(A3_dd_grid), get<2>(A3_dd_grid), get<3>(A3_dd_grid));
 A4_dd->InitializeThreeD(get<0>(A4_dd_grid), get<1>(A4_dd_grid), get<2>(A4_dd_grid), get<3>(A4_dd_grid));

 file->Close();

 cout<<"Prepare Interpolation grid done."<<endl;
}

void ZPrimeTripletSignalModule::calcRWNLO()
{
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

  double Even_SM = real(meLR*conj(meLR)) + real(meRL*conj(meRL)) + real(meLL*conj(meLL)) + real(meRR*conj(meRR));
  double Odd_SM  = real(meLR*conj(meLR)) + real(meRL*conj(meRL)) - real(meLL*conj(meLL)) - real(meRR*conj(meRR));

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

  double Even_BSM = real(meLR*conj(meLR)) + real(meRL*conj(meRL)) + real(meLL*conj(meLL)) + real(meRR*conj(meRR));
  double Odd_BSM  = real(meLR*conj(meLR)) + real(meRL*conj(meRL)) - real(meLL*conj(meLL)) - real(meRR*conj(meRR));

  // If f fbar are quarks.
  if (idAbs < 9) sigma /= 3.;
 
  // give sigma dimensions
  sigma *= 3.8938*pow(10,8); // GeV^2 * pB
  
  // set as member variable
  sigmaBSM = sigma;

  // ... and this too
  rw = sigmaBSM/sigmaSM;

  int nMassInp = 3;
  int nQTInp = 3;
  int nZYInp = 3;

  double sigmaSM_Even, sigmaSM_Odd;
  if(idAbs == 2 || idAbs == 4 || idAbs == 6){
    sigmaSM_Even = (1.0 + CosThetaCS * CosThetaCS)
                 + 0.5 * A0_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (1.0 - 3.0 * CosThetaCS * CosThetaCS)
                 + A1_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (2.0 * sqrt(1.0 - CosThetaCS * CosThetaCS) * CosThetaCS * cos(PhiCS))
                 + 0.5 * A2_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * ((1.0 - CosThetaCS * CosThetaCS) * cos(2.0 * PhiCS));

    sigmaSM_Odd = A3_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (sqrt(1.0 - CosThetaCS * CosThetaCS) * cos(PhiCS))
                + A4_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (CosThetaCS);
  }
  else{
    sigmaSM_Even = (1.0 + CosThetaCS * CosThetaCS)
                 + 0.5 * A0_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (1.0 - 3.0 * CosThetaCS * CosThetaCS)
                 + A1_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (2.0 * sqrt(1.0 - CosThetaCS * CosThetaCS) * CosThetaCS * cos(PhiCS))
                 + 0.5 * A2_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * ((1.0 - CosThetaCS * CosThetaCS) * cos(2.0 * PhiCS));

    sigmaSM_Odd = A3_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (sqrt(1.0 - CosThetaCS * CosThetaCS) * cos(PhiCS))
                + A4_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity) * (CosThetaCS);
  }

  sigmaBSM = sigmaSM_Even * (Even_BSM / Even_SM) + sigmaSM_Odd * (Odd_BSM / Odd_SM);
  sigmaSM = sigmaSM_Even + sigmaSM_Odd;

  rw = sigmaBSM / sigmaSM;

  //std::cout<<"mass: "<<dilepton_mass<<"  pt: "<<dilepton_pt<<"  rapidity: "<<dilepton_rapidity<<"  CosTheta: "<<CosThetaCS<<"  Phi: "<<PhiCS<<std::endl;
  //std::cout<<"A0_uu: "<<A0_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A1_uu: "<<A1_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A2_uu: "<<A2_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A3_uu: "<<A3_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A4_uu: "<<A4_uu->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A0_dd: "<<A0_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A1_dd: "<<A1_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A2_dd: "<<A2_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A3_dd: "<<A3_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"A4_dd: "<<A4_dd->ThreeDInp(nMassInp, nQTInp, nZYInp, dilepton_mass, dilepton_pt, dilepton_rapidity)<<std::endl;
  //std::cout<<"Even_BSM: "<<Even_BSM<<"  Odd_BSM: "<<Odd_BSM<<"  Even_SM: "<<Even_SM<<"  Odd_SM: "<<Odd_SM<<std::endl;
  //std::cout<<"sigmaSM_Even: "<<sigmaSM_Even<<"  sigmaSM_Odd: "<<sigmaSM_Odd<<std::endl;
  //std::cout<<m_model<<"  "<<sigmaBSM<<"  "<<sigmaSM<<"  "<<rw<<std::endl;

  return; 

}
