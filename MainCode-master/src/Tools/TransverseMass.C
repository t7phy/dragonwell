#ifndef WTRANSVERSEMASS
#define WTRANSVERSEMASS

#include "Tools/Tools.h"
#include "TMath.h"
#include "TLorentzVector.h"

double CalculateTransverseMass(TLorentzVector Lepton, TLorentzVector nu)
{
    double dPhi = Lepton.DeltaPhi(nu);
    double TMass = sqrt(2 * Lepton.Pt() * nu.Pt() * (1 - cos(dPhi)));
    return TMass;
}

#endif
