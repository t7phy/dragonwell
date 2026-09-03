#ifndef _COS_THETA_H_
#define _COS_THETA_H_
#include "Tools/Tools.h"
#include "TMath.h"
#include "TLorentzVector.h"
double calculate_theta(TLorentzVector Zboson, TLorentzVector Electron, TLorentzVector Positron) //define lorentz variables (four dimensions)
{
  double cos_theta;
  cos_theta=1.0/(sqrt(Zboson.M()*Zboson.M()+Zboson.Pt()*Zboson.Pt())*Zboson.M()) * ((Electron.E()+Electron.Pz())*(Positron.E()-Positron.Pz())-(Positron.E()+Positron.Pz())*(Electron.E()-Electron.Pz()));
  if(cos_theta > 1.0) cos_theta = 1.0;
  if(cos_theta < -1.0) cos_theta = -1.0;
  return cos_theta;
}
#endif
