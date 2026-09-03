#ifndef PHI_ETA_H
#define PHI_ETA_H
#include "Tools/Tools.h"
#include "TMath.h"
#include "TLorentzVector.h"
double calculate_phi_eta(TLorentzVector Electron, TLorentzVector Positron)
{
 double pi = 3.1415926535897932384626;
 double delta_phi = Electron.DeltaPhi(Positron);
 double cos_theta_eta = tanh((Electron.Eta() - Positron.Eta()) / 2.0);
 double sin_theta_eta = cos_theta_eta > 1.0 ? 0.0 : sqrt(1.0 - cos_theta_eta * cos_theta_eta);
 double phi_eta = tan((pi - delta_phi) / 2.0) * sin_theta_eta;
 return fabs(phi_eta);
}
#endif
