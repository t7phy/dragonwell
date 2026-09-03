#include "HistsHerwig.h"

using namespace std;

void HistsHerwig::bookHists(int TotalThread)
{
 double rangeZPt[24] = {0,2.5,5,8,11.4,14.9,18.5,22,25.5,29,32.6,36.4,40.4,44.9,50.2,56.4,63.9,73.4,85.4,105,132,173,253,600};

 this->TotalThread = TotalThread;

 BookHist(FZmass_CC, "FZmass_CC", "FZmass_CC", 70, 60, 130);
 BookHist(BZmass_CC, "BZmass_CC", "BZmass_CC", 70, 60, 130);
 BookHist(FZmass_CF, "FZmass_CF", "FZmass_CF", 70, 60, 130);
 BookHist(BZmass_CF, "BZmass_CF", "BZmass_CF", 70, 60, 130);

 BookHist(ZPt, "ZPt", "ZPt", 500, 0, 500);
 BookHist(ZRapidity, "ZRapidity", "ZRapidity", 20, -5, 5);
 BookHist(ZMass, "ZMass", "ZMass", 70, 60, 130);

 BookHist(FZmass, "FZmass", "FZmass", 70, 60, 130);
 BookHist(BZmass, "BZmass", "BZmass", 70, 60, 130);

 BookHist(CosTheta, "CosTheta", "CosTheta", 20, -1, 1);
 BookHist(CollinsPhi, "phi", "phi", 200, -6.28, 6.28);
 BookHist(plot_phi_eta, "phi_eta", "phi_eta", 10000, 0, 10);

 BookHist(leptonPt, "leptonPt", "leptonPt", 20, 0, 100);
 BookHist(leptonEta, "leptonEta", "leptonEta", 20, -5, 5);

 BookAngularHist(A0_ZPt, "A0_ZPt", "A0", 23, rangeZPt);
 BookAngularHist(A1_ZPt, "A1_ZPt", "A1", 23, rangeZPt);
 BookAngularHist(A2_ZPt, "A2_ZPt", "A2", 23, rangeZPt);
 BookAngularHist(A3_ZPt, "A3_ZPt", "A3", 23, rangeZPt);
 BookAngularHist(A4_ZPt, "A4_ZPt", "A4", 23, rangeZPt);
 BookAngularHist(L0_ZPt, "L0_ZPt", "L0", 23, rangeZPt);

}

void HistsHerwig::InitialSysName()
{

}
