#ifndef TruthWSelection_cxx
#define TruthWSelection_cxx

#include <iostream>
#include "Wasymmetry/loopWasym.h"

using namespace std;

bool loopWasym::TruthWenuSelection(int nchannel, EventWasym* event)
{
 bool isSignal = false;
 if(nchannel == 361100 || nchannel == 361103) isSignal = true;
 if(!isSignal) return false;

 double TruthWeight = event->EventWeight_gen;

 if(event->Truth_Lepton_Pt->at(0) < 25000) return false;
 if(fabs(event->Truth_Lepton_Eta->at(0)) > 2.5) return false;
 if(event->Truth_Neutrino_Pt->at(0) < 25000) return false;

 if(event->Truth_Lepton_ID->at(0) == 11){
   Electron_truth.SetPtEtaPhiM(event->Truth_Lepton_Pt->at(0), event->Truth_Lepton_Eta->at(0), event->Truth_Lepton_Phi->at(0), 0.511 * 0.001);
   Neutrino_truth.SetPtEtaPhiM(event->Truth_Neutrino_Pt->at(0), event->Truth_Neutrino_Eta->at(0), event->Truth_Neutrino_Phi->at(0), 0);
   WBoson_truth = Electron_truth + Neutrino_truth;
 }
 if(event->Truth_Lepton_ID->at(0) == -11){
   Positron_truth.SetPtEtaPhiM(event->Truth_Lepton_Pt->at(0), event->Truth_Lepton_Eta->at(0), event->Truth_Lepton_Phi->at(0), 0.511 * 0.001);
   Neutrino_truth.SetPtEtaPhiM(event->Truth_Neutrino_Pt->at(0), event->Truth_Neutrino_Eta->at(0), event->Truth_Neutrino_Phi->at(0), 0);
   WBoson_truth = Positron_truth + Neutrino_truth;
 }

 if(WBoson_truth.Pt() < 50000) return false;

 if(event->Truth_Lepton_ID->at(0) == 11) myhists->TruthWEvent_Ele_eta->at(iThread - 1)->Fill(Electron_truth.Eta(), TruthWeight);
 if(event->Truth_Lepton_ID->at(0) == -11) myhists->TruthWEvent_Posi_eta->at(iThread - 1)->Fill(Positron_truth.Eta(), TruthWeight);

 return false;
}

bool loopWasym::TruthWmunuSelection(int nchannel, EventWasym* event)
{
 bool isSignal = false;
 if(nchannel == 361101 || nchannel == 361104) isSignal = true;
 if(!isSignal) return false;

 double TruthWeight = event->EventWeight_gen * event->EventWeight_vertex * event->SumETWeight;

 if(event->Truth_Lepton_Pt->at(0) < 25000) return false;
 if(fabs(event->Truth_Lepton_Eta->at(0)) > 2.5) return false;
 if(event->Truth_Neutrino_Pt->at(0) < 25000) return false;

 if(event->Truth_Lepton_ID->at(0) == 13){
   Muon_truth.SetPtEtaPhiM(event->Truth_Lepton_Pt->at(0), event->Truth_Lepton_Eta->at(0), event->Truth_Lepton_Phi->at(0), 105.0 * 0.001);
   Neutrino_truth.SetPtEtaPhiM(event->Truth_Neutrino_Pt->at(0), event->Truth_Neutrino_Eta->at(0), event->Truth_Neutrino_Phi->at(0), 0);
   WBoson_truth = Muon_truth + Neutrino_truth;
 }
 if(event->Truth_Lepton_ID->at(0) == -13){
   AntiMuon_truth.SetPtEtaPhiM(event->Truth_Lepton_Pt->at(0), event->Truth_Lepton_Eta->at(0), event->Truth_Lepton_Phi->at(0), 105.0 * 0.001);
   Neutrino_truth.SetPtEtaPhiM(event->Truth_Neutrino_Pt->at(0), event->Truth_Neutrino_Eta->at(0), event->Truth_Neutrino_Phi->at(0), 0);
   WBoson_truth = AntiMuon_truth + Neutrino_truth;
 }

 if(WBoson_truth.Pt() < 50000) return false;

 if(event->Truth_Lepton_ID->at(0) == 13) myhists->TruthWEvent_Muon_eta->at(iThread - 1)->Fill(Muon_truth.Eta(), TruthWeight);
 if(event->Truth_Lepton_ID->at(0) == -13) myhists->TruthWEvent_AntiMuon_eta->at(iThread - 1)->Fill(AntiMuon_truth.Eta(), TruthWeight);

 return false;

}
#endif
