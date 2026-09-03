#include "WZPolarization/loopWZPolarization.h"

bool loopWZPolarization::genTruthLepton(TLorentzVector &ZLepton1, TLorentzVector &ZLepton2, TLorentzVector &WLepton, TLorentzVector &Neutrino)
{
 TruthEvent.ResetEvent();

 int CountElectron = 0;
 vector<int> ElectronSize;

 int CountMuon = 0;
 vector<int> MuonSize;

 int CountNeutrino = 0;
 vector<int> NeutrinoSize;

 int ZLepton1Charge;

 isTauEvent = false;

 cout<<"Event"<<endl;
 for(int i = 0; i < PreWZPolarizationTree->truth_eta->size() / 2; i++){
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

   cout<<"i: "<<i<<" pid: "<<PreWZPolarizationTree->truth_pid->at(i)<<" mid: "<<PreWZPolarizationTree->truth_mid->at(i)<<" eta: "<<PreWZPolarizationTree->truth_eta->at(i)<<endl;
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

 ZLepton1 = TruthZLepton1;
 ZLepton2 = TruthZLepton2;
 WLepton = TruthWLepton;
 Neutrino = TruthWNeutrino;

 TruthZLepton1.SetPtEtaPhiM(0,0,0,0);
 TruthZLepton2.SetPtEtaPhiM(0,0,0,0);
 TruthWLepton.SetPtEtaPhiM(0,0,0,0);
 TruthWNeutrino.SetPtEtaPhiM(0,0,0,0);

 return true;
}

