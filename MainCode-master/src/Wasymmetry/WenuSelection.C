#ifndef WenuSelection_cxx
#define WenuSelection_cxx

#include <iostream>
#include "Wasymmetry/loopWasym.h"

using namespace std;

bool loopWasym::WenuSelection(int nchannel, TString SysName, EventWasym* event)
{
/* bool isSignal = false;
 int isys = myhists->FindSysIndex(SysName, "WSignal_Electron");
 if(nchannel == 361100 || nchannel == 361103) isSignal = true;

 if(!isSignal) isys = -1;

 if(isTest) cout<<"Wenu Selection: This is the systematic "<<isys<<" selection. systematic name is "<<SysName<<" nchannel is "<<nchannel<<endl;

 double RecoilPt, RecoilEta, RecoilPhi, W_MT;
 double EventWeight = (double)event->EventWeight_gen * (double)event->EventWeight_vertex * (double)event->SumETWeight;

 int CountElectron = 0;
 int ElectronID = -1;
 for(int i = 0; i < event->el_eta->size(); i++){
   if(!BaseLineElectron(event->el_pt->at(i), event->el_delta_z0->at(i), event->el_d0sig->at(i), event->el_eta->at(i), event->el_isMedium->at(i))) continue;
   CountElectron++;
   ElectronID = i;
 }

 int CountMuon = 0;
 for(int i = 0; i < event->mu_eta->size(); i++){
   if(!BaseLineMuon(event->mu_pt->at(i), event->mu_delta_z0->at(i), event->mu_d0sig->at(i), event->mu_eta->at(i))) continue;
   CountMuon++;
 }

 if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 1, 1);
 if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 1, 1);
 if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(1, 1);
 if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow->at(iThread - 1)->Fill(1, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(1, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(1, 1);

 if(CountElectron != 1 || CountMuon != 0) return false;

 if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 2, 1);
 if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 2, 1);
 if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(2, 1);
 if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow_>at(iThread - 1)->Fill(2, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(2, 1);
 if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(2, 1);

 RecoilPt = event->Recoil;
 RecoilEta = 0;
 RecoilPhi = event->Recoil_Phi;

 Recoil_reco.SetPtEtaPhiM(RecoilPt, RecoilEta, RecoilPhi, 0);
 Lepton_reco.SetPtEtaPhiM(event->el_pt->at(ElectronID), event->el_eta->at(ElectronID), event->el_phi->at(ElectronID), 0);
 if(event->el_inrecoil->at(ElectronID)) Neutrino_reco = (Recoil_reco + Lepton_reco) * (-1);
 if(!event->el_inrecoil->at(ElectronID)) Neutrino_reco = Recoil_reco * (-1);
 WBoson_reco = Lepton_reco + Neutrino_reco;

 W_MT = CalculateTransverseMass(Lepton_reco, Neutrino_reco);

 if(!isData) ScaleFactor = TotalWeight * EventWeight * event->el_recosf->at(ElectronID) * event->el_idsf->at(ElectronID) * event->el_isosf->at(ElectronID) * event->el_trigsf->at(ElectronID);
 if(isData) ScaleFactor = 1.0;

//start event selection
 if(event->el_charge->at(ElectronID) < 0){
   LeptonEta = Lepton_reco.Eta();
   LeptonEtaAbs = fabs(Lepton_reco.Eta());
   LeptonPt = Lepton_reco.Pt();

   if(!event->el_trigMatch->at(ElectronID)) return false;
   if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 3, 1);
   if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(3, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(3, 1);

   if(event->el_isolation_ptvarcone20->at(ElectronID) / event->el_pt->at(ElectronID) > 0.1) return false;
   if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 4, 1);
   if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(4, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(4, 1);

   if(event->el_pt->at(ElectronID) < 25000) return false;
   if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 5, 1);
   if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(5, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(5, 1);

   if(Neutrino_reco.Pt() < 25000) return false;
   if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 6, 1);
   if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(6, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(6, 1);

   if(W_MT < 50000) return false;
   if(isSignal) myhists->WEvent_Ele_CutFlow_sys->at(iThread - 1)->Fill(isys, 7, 1);
   if(nchannel == -1) myhists->DataWEvent_Ele_CutFlow->at(iThread - 1)->Fill(7, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_CutFlow_bkg->at(iThread - 1)->Fill(7, 1);

   if(isSignal) myhists->WEvent_Ele_eta_sys->at(iThread - 1)->Fill(isys, LeptonEta, ScaleFactor);
   if(nchannel == -1) myhists->DataWEvent_Ele_eta->at(iThread - 1)->Fill(LeptonEta, ScaleFactor);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Ele_eta_bkg->at(iThread - 1)->Fill(LeptonEta, ScaleFactor);

 }

 if(event->el_charge->at(ElectronID) > 0){
   AntiLeptonEta = Lepton_reco.Eta();
   AntiLeptonEtaAbs = fabs(Lepton_reco.Eta());
   AntiLeptonPt = Lepton_reco.Pt();

   if(!event->el_trigMatch->at(ElectronID)) return false;
   if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 3, 1);
   if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow->at(iThread - 1)->Fill(3, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(3, 1);

   if(event->el_isolation_ptvarcone20->at(ElectronID) / event->el_pt->at(ElectronID) > 0.1) return false;
   if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 4, 1);
   if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow->at(iThread - 1)->Fill(4, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(4, 1);

   if(event->el_pt->at(ElectronID) < 25000) return false;
   if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 5, 1);
   if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow->at(iThread - 1)->Fill(5, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(5, 1);

   if(Neutrino_reco.Pt() < 25000) return false;
   if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 6, 1);
   if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow->at(iThread - 1)->Fill(6, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(6, 1);

   if(W_MT < 50000) return false;
   if(isSignal) myhists->WEvent_Posi_CutFlow_sys->at(iThread - 1)->Fill(isys, 7, 1);
   if(nchannel == -1) myhists->DataWEvent_Posi_CutFlow->at(iThread - 1)->Fill(7, 1);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_CutFlow_bkg->at(iThread - 1)->Fill(7, 1);

   if(isSignal) myhists->WEvent_Posi_eta_sys->at(iThread - 1)->Fill(isys, AntiLeptonEta, ScaleFactor);
   if(nchannel == -1) myhists->DataWEvent_Posi_eta->at(iThread - 1)->Fill(AntiLeptonEta, ScaleFactor);
   if(nchannel != -1 && !isSignal) myhists->WEvent_Posi_eta_bkg->at(iThread - 1)->Fill(AntiLeptonEta, ScaleFactor);

 }

 if(isSignal) myhists->WEvent_WenuPt_reco_sys->at(iThread - 1)->Fill(isys, WBoson_reco.Pt(), ScaleFactor);
 if(nchannel == -1) myhists->DataWEvent_WenuPt_reco->at(iThread - 1)->Fill(WBoson_reco.Pt(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->WEvent_WenuPt_reco_bkg->at(iThread - 1)->Fill(WBoson_reco.Pt(), ScaleFactor);
*/
 return false;

}
#endif
