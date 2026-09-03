#ifndef _PHI_H_
#define _PHI_H_
#include "Tools/Tools.h"
#include "TMath.h"
#include "TLorentzVector.h"
double calculate_phi(TLorentzVector Electron, TLorentzVector Positron, double myECM)
{
  double ECM = myECM;
  TLorentzVector dilepton = Electron + Positron;
  TVector3 boost          = -dilepton.BoostVector();

  TLorentzVector el(Electron.Px(), Electron.Py(), Electron.Pz(), Electron.E());
  TLorentzVector po(Positron.Px(), Positron.Py(), Positron.Pz(), Positron.E());
  el.Boost(boost);
  po.Boost(boost);

  TLorentzVector lab_z1(0.,0., ECM, ECM);
  TLorentzVector lab_z2(0.,0., ECM * (-1), ECM);
  lab_z1.Boost(boost);
  lab_z2.Boost(boost);

  TVector3 boson_frame  = (lab_z1.Vect().Unit()-lab_z2.Vect().Unit()).Unit();
  TVector3 yplant_frame = ((lab_z2.Vect().Unit()).Cross(lab_z1.Vect().Unit())).Unit();
  TVector3 xplant_frame = (yplant_frame.Cross(boson_frame)).Unit();

  TVector3 elec_vec     = el.Vect();
  double collins_phi    = atan2(elec_vec.Dot(yplant_frame), elec_vec.Dot(xplant_frame));
  return collins_phi;
}
#endif

