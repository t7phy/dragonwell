#ifndef WZPol_TruthSelection_cxx
#define WZPol_TruthSelection_cxx

#include <iostream>
#include "WZPolarization/loopWZPolarization.h"

using namespace std;

bool loopWZPolarization::TruthSelection()
{
 if(!doTruthSelection) return false;

 TruthEvent.ResetEvent();

 int CountElectron = 0;
 vector<int> ElectronSize;

 int CountMuon = 0;
 vector<int> MuonSize;

 int CountNeutrino = 0;
 vector<int> NeutrinoSize;

 int ZLepton1Charge;

 isTauEvent = false;
 //cout<<"Event"<<endl;
 for(int i = 0; i < PreWZPolarizationTree->truth_eta->size(); i++){
   if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 11){
     CountElectron++;
     ElectronSize.push_back(i);
   }
   if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 13){
     CountMuon++;
     MuonSize.push_back(i);
   }
   if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 12 || fabs(PreWZPolarizationTree->truth_pid->at(i)) == 14){
     CountNeutrino++;
     NeutrinoSize.push_back(i);
   }

   if(TruthEvent.MCType == 364253){
     if(fabs(PreWZPolarizationTree->truth_pid->at(i)) == 15 || fabs(PreWZPolarizationTree->truth_pid->at(i)) == 16) isTauEvent = true;
   }
   //cout<<"i: "<<i<<" pid: "<<PreWZPolarizationTree->truth_pid->at(i)<<" mid: "<<PreWZPolarizationTree->truth_mid->at(i)<<endl;
 }

 if((CountElectron + CountMuon) != 3 || CountNeutrino != 1) return false;

 if(CountElectron == 1 && CountMuon == 2){
   Flavor = "emm";
   TLorentzVector Lepton1;
   Lepton1.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(ElectronSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(ElectronSize.at(0)), PreWZPolarizationTree->truth_phi->at(ElectronSize.at(0)), PreWZPolarizationTree->truth_e->at(ElectronSize.at(0)) / GeV);
   TLorentzVector Lepton2;
   Lepton2.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(MuonSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(MuonSize.at(0)), PreWZPolarizationTree->truth_phi->at(MuonSize.at(0)), PreWZPolarizationTree->truth_e->at(MuonSize.at(0)) / GeV);
   TLorentzVector Lepton3;
   Lepton3.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(MuonSize.at(1)) / GeV, PreWZPolarizationTree->truth_eta->at(MuonSize.at(1)), PreWZPolarizationTree->truth_phi->at(MuonSize.at(1)), PreWZPolarizationTree->truth_e->at(MuonSize.at(1)) / GeV);

   if(fabs(PreWZPolarizationTree->truth_pid->at(NeutrinoSize.at(0))) != 12) return false;
   if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) > 0) return false;

   TruthWLepton = Lepton1;
   TruthWNeutrino.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(NeutrinoSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_phi->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_e->at(NeutrinoSize.at(0)) / GeV);

   if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) > 0){
     TruthZLepton1 = Lepton3;
     TruthZLepton2 = Lepton2;
     ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(1));
   }

   if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) > 0){
     TruthZLepton1 = Lepton2;
     TruthZLepton2 = Lepton3;
     ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(0));
   }

 }

 if(CountElectron == 2 && CountMuon == 1){
   Flavor = "eem";
   TLorentzVector Lepton1;
   Lepton1.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(ElectronSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(ElectronSize.at(0)), PreWZPolarizationTree->truth_phi->at(ElectronSize.at(0)), PreWZPolarizationTree->truth_e->at(ElectronSize.at(0)) / GeV);
   TLorentzVector Lepton2;
   Lepton2.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(ElectronSize.at(1)) / GeV, PreWZPolarizationTree->truth_eta->at(ElectronSize.at(1)), PreWZPolarizationTree->truth_phi->at(ElectronSize.at(1)), PreWZPolarizationTree->truth_e->at(ElectronSize.at(1)) / GeV);
   TLorentzVector Lepton3;   
   Lepton3.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(MuonSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(MuonSize.at(0)), PreWZPolarizationTree->truth_phi->at(MuonSize.at(0)), PreWZPolarizationTree->truth_e->at(MuonSize.at(0)) / GeV);

   if(fabs(PreWZPolarizationTree->truth_pid->at(NeutrinoSize.at(0))) != 14) return false;
   if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) > 0) return false;

   TruthWLepton = Lepton3;
   TruthWNeutrino.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(NeutrinoSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_phi->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_e->at(NeutrinoSize.at(0)) / GeV);

   if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) > 0){
     TruthZLepton1 = Lepton2;
     TruthZLepton2 = Lepton1;
     ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1));
   }
   if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) > 0){
     TruthZLepton1 = Lepton1;
     TruthZLepton2 = Lepton2;
     ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0));
   }

 }

 if(CountElectron == 3 && CountMuon == 0){
   Flavor == "eee";
   TLorentzVector Lepton1;
   Lepton1.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(ElectronSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(ElectronSize.at(0)), PreWZPolarizationTree->truth_phi->at(ElectronSize.at(0)), PreWZPolarizationTree->truth_e->at(ElectronSize.at(0)) / GeV);
   TLorentzVector Lepton2;
   Lepton2.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(ElectronSize.at(1)) / GeV, PreWZPolarizationTree->truth_eta->at(ElectronSize.at(1)), PreWZPolarizationTree->truth_phi->at(ElectronSize.at(1)), PreWZPolarizationTree->truth_e->at(ElectronSize.at(1)) / GeV);
   TLorentzVector Lepton3;
   Lepton3.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(ElectronSize.at(2)) / GeV, PreWZPolarizationTree->truth_eta->at(ElectronSize.at(2)), PreWZPolarizationTree->truth_phi->at(ElectronSize.at(2)), PreWZPolarizationTree->truth_e->at(ElectronSize.at(2)) / GeV);

   if(fabs(PreWZPolarizationTree->truth_pid->at(NeutrinoSize.at(0))) != 12) return false;
   if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) > 0 && PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) > 0 && PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) > 0) return false;

   TruthWNeutrino.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(NeutrinoSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_phi->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_e->at(NeutrinoSize.at(0)) / GeV);

   if(fabs(PreWZPolarizationTree->truth_mid->at(ElectronSize.at(0))) == 24){
     TruthWLepton = Lepton1;

     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) > 0){
       TruthZLepton1 = Lepton3;
       TruthZLepton2 = Lepton2;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2));
     }

     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) > 0){
       TruthZLepton1 = Lepton2;
       TruthZLepton2 = Lepton3;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1));
     }

   }
   else if(fabs(PreWZPolarizationTree->truth_mid->at(ElectronSize.at(1))) == 24){
     TruthWLepton = Lepton2;

     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) > 0){
       TruthZLepton1 = Lepton3;
       TruthZLepton2 = Lepton1;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2));
     }

     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) > 0){
       TruthZLepton1 = Lepton1;
       TruthZLepton2 = Lepton3;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0));
     }


   }
   else if(fabs(PreWZPolarizationTree->truth_mid->at(ElectronSize.at(2))) == 24){
     TruthWLepton = Lepton3;

     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) > 0){
       TruthZLepton1 = Lepton2;
       TruthZLepton2 = Lepton1;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1));
     }

     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) > 0){
       TruthZLepton1 = Lepton1;
       TruthZLepton2 = Lepton2;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0));
     }

   }
   else{
     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) > 0){
       TruthZLepton1 = Lepton3;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2));

       TLorentzVector ZBoson1 = Lepton1 + Lepton3;
       TLorentzVector ZBoson2 = Lepton2 + Lepton3;

       if(fabs(ZBoson1.M() - ZPeakMass) < fabs(ZBoson2.M() - ZPeakMass)){
         TruthZLepton2 = Lepton1;
         TruthWLepton = Lepton2;
       }
       else{
         TruthZLepton2 = Lepton2;
         TruthWLepton = Lepton1;
       }
     }
     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) > 0){
       TruthZLepton1 = Lepton2;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1));

       TLorentzVector ZBoson1 = Lepton1 + Lepton2;
       TLorentzVector ZBoson2 = Lepton3 + Lepton2;
       
       if(fabs(ZBoson1.M() - ZPeakMass) < fabs(ZBoson2.M() - ZPeakMass)){
         TruthZLepton2 = Lepton1;
         TruthWLepton = Lepton3;
       }
       else{
         TruthZLepton2 = Lepton3;
         TruthWLepton = Lepton1;
       }
     }
     if(PreWZPolarizationTree->truth_pid->at(ElectronSize.at(1)) * PreWZPolarizationTree->truth_pid->at(ElectronSize.at(2)) > 0){
       TruthZLepton1 = Lepton1;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(ElectronSize.at(0));

       TLorentzVector ZBoson1 = Lepton2 + Lepton1;
       TLorentzVector ZBoson2 = Lepton3 + Lepton1;
       
       if(fabs(ZBoson1.M() - ZPeakMass) < fabs(ZBoson2.M() - ZPeakMass)){
         TruthZLepton2 = Lepton2;
         TruthWLepton = Lepton3;
       }
       else{
         TruthZLepton2 = Lepton3;
         TruthWLepton = Lepton2;
       }
     }

   }

 }

 if(CountElectron == 0 && CountMuon == 3){
   Flavor == "mmm";
   TLorentzVector Lepton1;
   Lepton1.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(MuonSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(MuonSize.at(0)), PreWZPolarizationTree->truth_phi->at(MuonSize.at(0)), PreWZPolarizationTree->truth_e->at(MuonSize.at(0)) / GeV);
   TLorentzVector Lepton2;
   Lepton2.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(MuonSize.at(1)) / GeV, PreWZPolarizationTree->truth_eta->at(MuonSize.at(1)), PreWZPolarizationTree->truth_phi->at(MuonSize.at(1)), PreWZPolarizationTree->truth_e->at(MuonSize.at(1)) / GeV);
   TLorentzVector Lepton3;
   Lepton3.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(MuonSize.at(2)) / GeV, PreWZPolarizationTree->truth_eta->at(MuonSize.at(2)), PreWZPolarizationTree->truth_phi->at(MuonSize.at(2)), PreWZPolarizationTree->truth_e->at(MuonSize.at(2)) / GeV);

   if(fabs(PreWZPolarizationTree->truth_pid->at(NeutrinoSize.at(0))) != 14) return false;
   if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) > 0 && PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) > 0 && PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) > 0) return false;

   TruthWNeutrino.SetPtEtaPhiE(PreWZPolarizationTree->truth_pt->at(NeutrinoSize.at(0)) / GeV, PreWZPolarizationTree->truth_eta->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_phi->at(NeutrinoSize.at(0)), PreWZPolarizationTree->truth_e->at(NeutrinoSize.at(0)) / GeV);

   if(fabs(PreWZPolarizationTree->truth_mid->at(MuonSize.at(0))) == 24){
     TruthWLepton = Lepton1;

     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) > 0){
       TruthZLepton1 = Lepton3;
       TruthZLepton2 = Lepton2;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(2));
     }

     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) > 0){
       TruthZLepton1 = Lepton2;
       TruthZLepton2 = Lepton3;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(1));
     }

   }
   else if(fabs(PreWZPolarizationTree->truth_mid->at(MuonSize.at(1))) == 24){
     TruthWLepton = Lepton2;

     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) > 0){
       TruthZLepton1 = Lepton3;
       TruthZLepton2 = Lepton1;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(2));
     }

     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) > 0){
       TruthZLepton1 = Lepton1;
       TruthZLepton2 = Lepton3;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(0));
     }


   }
   else if(fabs(PreWZPolarizationTree->truth_mid->at(MuonSize.at(2))) == 24){
     TruthWLepton = Lepton3;

     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) > 0){
       TruthZLepton1 = Lepton2;
       TruthZLepton2 = Lepton1;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(1));
     }

     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) > 0){
       TruthZLepton1 = Lepton1;
       TruthZLepton2 = Lepton2;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(0));
     }

   }
   else{
     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) > 0){
       TruthZLepton1 = Lepton3;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(2));

       TLorentzVector ZBoson1 = Lepton1 + Lepton3;
       TLorentzVector ZBoson2 = Lepton2 + Lepton3;

       if(fabs(ZBoson1.M() - ZPeakMass) < fabs(ZBoson2.M() - ZPeakMass)){
         TruthZLepton2 = Lepton1;
         TruthWLepton = Lepton2;
       }
       else{
         TruthZLepton2 = Lepton2;
         TruthWLepton = Lepton1;
       }
     }
     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(0)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) > 0){
       TruthZLepton1 = Lepton2;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(1));

       TLorentzVector ZBoson1 = Lepton1 + Lepton2;
       TLorentzVector ZBoson2 = Lepton3 + Lepton2;
       
       if(fabs(ZBoson1.M() - ZPeakMass) < fabs(ZBoson2.M() - ZPeakMass)){
         TruthZLepton2 = Lepton1;
         TruthWLepton = Lepton3;
       }
       else{
         TruthZLepton2 = Lepton3;
         TruthWLepton = Lepton1;
       }
     }
     if(PreWZPolarizationTree->truth_pid->at(MuonSize.at(1)) * PreWZPolarizationTree->truth_pid->at(MuonSize.at(2)) > 0){
       TruthZLepton1 = Lepton1;
       ZLepton1Charge = PreWZPolarizationTree->truth_pid->at(MuonSize.at(0));

       TLorentzVector ZBoson1 = Lepton2 + Lepton1;
       TLorentzVector ZBoson2 = Lepton3 + Lepton1;
       
       if(fabs(ZBoson1.M() - ZPeakMass) < fabs(ZBoson2.M() - ZPeakMass)){
         TruthZLepton2 = Lepton2;
         TruthWLepton = Lepton3;
       }
       else{
         TruthZLepton2 = Lepton3;
         TruthWLepton = Lepton2;
       }
     }

   }

 }

 TruthWBoson = TruthWLepton + TruthWNeutrino;
 TruthZBoson = TruthZLepton1 + TruthZLepton2;
 TruthWZPropagator = TruthWBoson + TruthZBoson;

 TruthEvent.Lep1Pt = TruthZLepton1.Pt();
 TruthEvent.Lep2Pt = TruthZLepton2.Pt();
 TruthEvent.Lep3Pt = TruthWLepton.Pt();

 TruthEvent.Lep1Eta = TruthZLepton1.Eta();
 TruthEvent.Lep2Eta = TruthZLepton2.Eta();
 TruthEvent.Lep3Eta = TruthWLepton.Eta();

 TruthEvent.Lep1Phi = TruthZLepton1.Phi();
 TruthEvent.Lep2Phi = TruthZLepton2.Phi();
 TruthEvent.Lep3Phi = TruthWLepton.Phi();

 TruthEvent.Flavor = Flavor;

 TruthEvent.M_WZ = TruthWZPropagator.M();
 TruthEvent.Mt_WZ = TruthWZPropagator.Mt();
 TruthEvent.M_Z = TruthZBoson.M();
 TruthEvent.Mt_W = CalculateTransverseMass(TruthWLepton, TruthWNeutrino);
 TruthEvent.Pt_W = TruthWBoson.Pt();
 TruthEvent.Pt_Z = TruthZBoson.Pt();
 TruthEvent.Pt_WZ = TruthWZPropagator.Pt();
 TruthEvent.Met = TruthWNeutrino.Pt();

 TruthEvent.Mpx = TruthWNeutrino.Px();
 TruthEvent.Mpy = TruthWNeutrino.Py();
 TruthEvent.Mpz = TruthWNeutrino.Pz();

 TruthEvent.DY_WZ = CalculateDY_WZ(TruthWBoson, TruthZBoson);
 TruthEvent.DY_3Z = CalculateDY_3Z(TruthZBoson, TruthWLepton);
 TruthEvent.DY_3N = (ZLepton1Charge < 0) ? CalculateDY_3N(TruthZLepton1, TruthWLepton) : CalculateDY_3N(TruthZLepton2, TruthWLepton);

 TruthEvent.CosThetaV = CalculateCosThetaV(TruthWBoson, TruthZBoson);
 TruthEvent.CosThetaLepW = CalculateCosThetaLepW(TruthWBoson, TruthZBoson, TruthWLepton);
 TruthEvent.CosThetaLepZ = (ZLepton1Charge < 0) ? CalculateCosThetaLepZ(TruthWBoson, TruthZBoson, TruthZLepton1) : CalculateCosThetaLepZ(TruthWBoson, TruthZBoson, TruthZLepton2);

 TruthEvent.DeltaPhiLepWLepZ = (ZLepton1Charge < 0) ? CalculateDeltaPhiLepWLepZ(TruthZLepton1, TruthWLepton) : CalculateDeltaPhiLepWLepZ(TruthZLepton2, TruthWLepton);
 TruthEvent.DeltaPhiLepWLepZWZFrame = (ZLepton1Charge < 0) ? CalculateDeltaPhiLepWLepZWZFrame(TruthZLepton1, TruthWLepton, TruthWZPropagator) : CalculateDeltaPhiLepWLepZWZFrame(TruthZLepton2, TruthWLepton, TruthWZPropagator);
 TruthEvent.R21 = CalculateR21(TruthZBoson, TruthWBoson);

 if(TruthEvent.Year == 1516) TruthEvent.Luminosity = Lumi1516;
 if(TruthEvent.Year == 17) TruthEvent.Luminosity = Lumi17;
 if(TruthEvent.Year == 18) TruthEvent.Luminosity = Lumi18;
 TruthEvent.NormSF = TruthEvent.Luminosity * TruthEvent.CrossSection / TruthEvent.SumOfWeight;

 double KFactor = 1.0;
 if(TruthEvent.MCType == 501793 || TruthEvent.MCType == 501794 || TruthEvent.MCType == 500291 || TruthEvent.MCType == 500295) KFactor = 1.34;
 if(TruthEvent.MCType == 501795 || TruthEvent.MCType == 501796 || TruthEvent.MCType == 500290 || TruthEvent.MCType == 500294) KFactor = 2.05;
 if(TruthEvent.MCType == 501797 || TruthEvent.MCType == 501798 || TruthEvent.MCType == 500292 || TruthEvent.MCType == 500296) KFactor = 2.10;
 if(TruthEvent.MCType == 501799 || TruthEvent.MCType == 501800 || TruthEvent.MCType == 500293 || TruthEvent.MCType == 500297) KFactor = 1.51;

 TruthEvent.Weight = PreWZPolarizationTree->TruthMCEventWeight * PreWZPolarizationTree->TruthMCPileupWeight;
 TruthEvent.WeightNormalized = TruthEvent.NormSF * TruthEvent.Weight;
 TruthEvent.TotalWeight = TruthEvent.WeightNormalized;

 TruthEvent.WeightNoKFactor = PreWZPolarizationTree->TruthMCEventWeight * PreWZPolarizationTree->TruthMCPileupWeight;
 TruthEvent.WeightNormalizedNoKFactor = TruthEvent.NormSF * TruthEvent.WeightNoKFactor;
 TruthEvent.TotalWeightNoKFactor = TruthEvent.WeightNormalizedNoKFactor;

 bool passMassWindow1 = (fabs(TruthZBoson.M() - ZPeakMass) < 20);
 bool passMassWindow4 = (fabs(TruthZBoson.M() - ZPeakMass) < 10);

 TruthEvent.passWZInclusive = (passMassWindow1)
                              && (TruthWNeutrino.Pt() > 25)
                              && (TruthZLepton1.Pt() > 15)
                              && (TruthZLepton2.Pt() > 15)
                              && (TruthWLepton.Pt() > 15);

 TruthEvent.passHardWZInclusive = (passMassWindow4)
                                  && (TruthWNeutrino.Pt() > 25)
                                  && (TruthZLepton1.Pt() > 15)
                                  && (TruthZLepton2.Pt() > 15)
                                  && (TruthWLepton.Pt() > 15)
                                  && (TruthEvent.Mt_W > 30);

 TruthEvent.passSignalRegion = (TruthEvent.Pt_Z > 200)
                               && (TruthEvent.Pt_WZ < 70);

 TruthEvent.passHighPtWZCR = (TruthEvent.Pt_Z > 200)
                             && (TruthEvent.Pt_WZ > 70);

 TruthEvent.passLowPtZCR = (TruthEvent.Pt_Z < 200)
                           && (TruthEvent.Pt_WZ < 70);

 TruthEvent.isTauEvent = isTauEvent;

 int DecayChannel = 0;
 if(TruthEvent.Flavor == "emm") DecayChannel = 1;
 if(TruthEvent.Flavor == "eem") DecayChannel = 2;
 if(TruthEvent.Flavor == "eee") DecayChannel = 3;
 if(TruthEvent.Flavor == "mmm") DecayChannel = 4;

 TruthEvent.EventNumber = PreWZPolarizationTree->TruthEventNumber;

 WZPolarizationTree->EventNumber = TruthEvent.EventNumber;
 WZPolarizationTree->Flavor = DecayChannel;
 WZPolarizationTree->NormSF = TruthEvent.NormSF;
 WZPolarizationTree->WeightSign = TruthEvent.WeightSign;
 WZPolarizationTree->WeightNormalized = TruthEvent.WeightNormalized;
 WZPolarizationTree->Weight = TruthEvent.Weight;
 WZPolarizationTree->TotalWeight = TruthEvent.TotalWeight;
 WZPolarizationTree->WeightNormalizedNoKFactor = TruthEvent.WeightNormalizedNoKFactor;
 WZPolarizationTree->WeightNoKFactor = TruthEvent.WeightNoKFactor;
 WZPolarizationTree->TotalWeightNoKFactor = TruthEvent.TotalWeightNoKFactor;
 WZPolarizationTree->M_WZ = TruthEvent.M_WZ;
 WZPolarizationTree->Mt_WZ = TruthEvent.Mt_WZ;
 WZPolarizationTree->M_Z = TruthEvent.M_Z;
 WZPolarizationTree->Mt_W = TruthEvent.Mt_W;
 WZPolarizationTree->Met = TruthEvent.Met;
 WZPolarizationTree->Lep1Pt = TruthEvent.Lep1Pt;
 WZPolarizationTree->Lep2Pt = TruthEvent.Lep2Pt;
 WZPolarizationTree->Lep3Pt = TruthEvent.Lep3Pt;
 WZPolarizationTree->Lep1Eta = TruthEvent.Lep1Eta;
 WZPolarizationTree->Lep2Eta = TruthEvent.Lep2Eta;
 WZPolarizationTree->Lep3Eta = TruthEvent.Lep3Eta;
 WZPolarizationTree->Lep1Phi = TruthEvent.Lep1Phi;
 WZPolarizationTree->Lep2Phi = TruthEvent.Lep2Phi;
 WZPolarizationTree->Lep3Phi = TruthEvent.Lep3Phi;
 WZPolarizationTree->Mpx = TruthEvent.Mpx;
 WZPolarizationTree->Mpy = TruthEvent.Mpy;
 WZPolarizationTree->Mpz = TruthEvent.Mpz;
 WZPolarizationTree->Pt_W = TruthEvent.Pt_W;
 WZPolarizationTree->Pt_Z = TruthEvent.Pt_Z;
 WZPolarizationTree->Pt_WZ = TruthEvent.Pt_WZ;
 WZPolarizationTree->CosThetaV = TruthEvent.CosThetaV;
 WZPolarizationTree->CosThetaLepW = TruthEvent.CosThetaLepW;
 WZPolarizationTree->CosThetaLepZ = TruthEvent.CosThetaLepZ;
 WZPolarizationTree->DY_WZ = TruthEvent.DY_WZ;
 WZPolarizationTree->DY_3Z = TruthEvent.DY_3Z;
 WZPolarizationTree->DY_3N = TruthEvent.DY_3N;
 WZPolarizationTree->DeltaPhiLepWLepZ = TruthEvent.DeltaPhiLepWLepZ;
 WZPolarizationTree->DeltaPhiLepWLepZWZFrame = TruthEvent.DeltaPhiLepWLepZWZFrame;
 WZPolarizationTree->R21 = TruthEvent.R21;

 WZPolarizationTree->isTauEvent = isTauEvent;

 return true;
}

#endif
