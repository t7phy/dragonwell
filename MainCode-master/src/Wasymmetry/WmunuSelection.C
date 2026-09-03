#ifndef WmunuSelection_cxx
#define WmunuSelection_cxx

#include <iostream>
#include "Wasymmetry/loopWasym.h"

using namespace std;

bool loopWasym::WmunuSelection(int nchannel, TString SysName, EventWasym* event)
{
/* bool isSignal = false;
 int isys = myhists->FindSysIndex(SysName, "WSignal_Muon");
 if(nchannel == 361101 || nchannel == 361104) isSignal = true;

 if(!isSignal) isys = -1;

// if(isTest) cout<<"Wmunu Selection: This is the systematic "<<isys<<" selection."<<endl;

 double RecoilPt, RecoilEta, RecoilPhi, W_MT;
 double EventWeight = (double)event->EventWeight_gen * (double)event->EventWeight_vertex * (double)event->SumETWeight;

 int CountElectron = 0;
 int MuonID = -1;
 for(int i = 0; i < event->el_eta->size(); i++){
   if(!BaseLineElectron(event->el_pt->at(i), event->el_delta_z0->at(i), event->el_d0sig->at(i), event->el_eta->at(i), event->el_isMedium->at(i))) continue;
   CountElectron++;
 }

 int CountMuon = 0;
 for(int i = 0; i < event->mu_eta->size(); i++){
   if(!BaseLineMuon(event->mu_pt->at(i), event->mu_delta_z0->at(i), event->mu_d0sig->at(i), event->mu_eta->at(i))) continue;
   CountMuon++;
   MuonID = i;
 }

 if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 1, 1);
 if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 1, 1);
 if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(1, 1);
 if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(1, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(1, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(1, 1);

 if(CountElectron != 0 || CountMuon != 1) return false;

 if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 2, 1);
 if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 2, 1);
 if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(2, 1);
 if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(2, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(2, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(2, 1);

 RecoilPt = event->Recoil;
 RecoilEta = 0;
 RecoilPhi = event->Recoil_Phi;

 Recoil_reco.SetPtEtaPhiM(RecoilPt, RecoilEta, RecoilPhi, 0);
 Lepton_reco.SetPtEtaPhiM(event->mu_pt->at(MuonID), event->mu_eta->at(MuonID), event->mu_phi->at(MuonID), 0);
 if(event->mu_inrecoil->at(MuonID)) Neutrino_reco = (Recoil_reco + Lepton_reco) * (-1);
 if(!event->mu_inrecoil->at(MuonID)) Neutrino_reco = Recoil_reco * (-1);
 WBoson_reco = Lepton_reco + Neutrino_reco;

 W_MT = CalculateTransverseMass(Lepton_reco, Neutrino_reco);

 if(!isData) ScaleFactor = TotalWeight * EventWeight * event->mu_recosf->at(MuonID) * event->mu_ttvasf->at(MuonID) * event->mu_isosf->at(MuonID) * event->mu_trigsf->at(MuonID);
 if(isData) ScaleFactor = 1.0;

//start event selection
 if(event->mu_charge->at(MuonID) < 0){
   LeptonEta = Lepton_reco.Eta();
   LeptonEtaAbs = fabs(Lepton_reco.Eta());
   LeptonPt = Lepton_reco.Pt();

   if(!event->mu_trigMatch->at(MuonID)) return false;
   if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 3, 1);
   if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(3, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(3, 1);

   if(event->mu_isolation_ptvarcone20->at(MuonID) / event->mu_pt->at(MuonID) > 0.1) return false;
   if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 4, 1);
   if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(4, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(4, 1);

   if(event->mu_pt->at(MuonID) < 25000) return false;
   if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 5, 1);
   if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(5, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(5, 1);

   if(Neutrino_reco.Pt() < 25000) return false;
   if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 6, 1);
   if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(6, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(6, 1);

   if(W_MT < 50000) return false;
   if(isSignal) myhists->WEvent_Muon_CutFlow_sys->at(iThread - 1)->Fill(isys, 7, 1);
   if(nchannel == -1) myhists->DataWEvent_Muon_CutFlow->at(iThread - 1)->Fill(7, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_CutFlow_bkg->at(iThread - 1)->Fill(7, 1);

   if(isSignal) myhists->WEvent_Muon_eta_sys->at(iThread - 1)->Fill(isys, LeptonEta, ScaleFactor);
   if(nchannel == -1) myhists->DataWEvent_Muon_eta->at(iThread - 1)->Fill(LeptonEta, ScaleFactor);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Muon_eta_bkg->at(iThread - 1)->Fill(LeptonEta, ScaleFactor);

 }

 if(event->mu_charge->at(MuonID) > 0){
   AntiLeptonEta = Lepton_reco.Eta();
   AntiLeptonEtaAbs = fabs(Lepton_reco.Eta());
   AntiLeptonPt = Lepton_reco.Pt();

   if(!event->mu_trigMatch->at(MuonID)) return false;
   if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 3, 1);
   if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(3, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(3, 1);

   if(event->mu_isolation_ptvarcone20->at(MuonID) / event->mu_pt->at(MuonID) > 0.1) return false;
   if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 4, 1);
   if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(4, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(4, 1);

   if(event->mu_pt->at(MuonID) < 25000) return false;
   if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 5, 1);
   if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(5, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(5, 1);

   if(Neutrino_reco.Pt() < 25000) return false;
   if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 6, 1);
   if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(6, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(6, 1);

   if(W_MT < 50000) return false;
   if(isSignal) myhists->WEvent_AntiMuon_CutFlow_sys->at(iThread - 1)->Fill(isys, 7, 1);
   if(nchannel == -1) myhists->DataWEvent_AntiMuon_CutFlow->at(iThread - 1)->Fill(7, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_CutFlow_bkg->at(iThread - 1)->Fill(7, 1);

   if(isSignal) myhists->WEvent_AntiMuon_eta_sys->at(iThread - 1)->Fill(isys, AntiLeptonEta, ScaleFactor);
   if(nchannel == -1) myhists->DataWEvent_AntiMuon_eta->at(iThread - 1)->Fill(AntiLeptonEta, ScaleFactor);
   if(nchannel != -1 && !isSignal) myhists->WEvent_AntiMuon_eta_bkg->at(iThread - 1)->Fill(AntiLeptonEta, ScaleFactor);

 }

 if(isSignal) myhists->WEvent_WmunuPt_reco_sys->at(iThread - 1)->Fill(isys, WBoson_reco.Pt(), ScaleFactor);
 if(nchannel == -1) myhists->DataWEvent_WmunuPt_reco->at(iThread - 1)->Fill(WBoson_reco.Pt(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->WEvent_WmunuPt_reco_bkg->at(iThread - 1)->Fill(WBoson_reco.Pt(), ScaleFactor);
*/
 return false;

}
#endif
