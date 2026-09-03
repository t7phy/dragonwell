#ifndef ZeeSelection_cxx
#define ZeeSelection_cxx

#include <iostream>
#include "Wasymmetry/loopWasym.h"

using namespace std;

bool loopWasym::ZeeSelection(int nchannel, TString SysName, EventWasym* event)
{
/* bool isSignal = false;
 int isys = myhists->FindSysIndex(SysName, "ZSignal_Electron");
 if(nchannel == 361106) isSignal = true;

 if(!isSignal) isys = -1;

// if(isTest) cout<<"Zee Selection: This is the systematic "<<isys<<" selection."<<endl;

 double RecoilPt, RecoilEta, RecoilPhi, W_MT;
 double EventWeight = (double)event->EventWeight_gen * (double)event->EventWeight_vertex * (double)event->SumETWeight;

 int CountElectron = 0;
 int ElectronID = -1;
 int PositronID = -1;
 vector<int> ElectronSize;
 for(int i = 0; i < event->el_eta->size(); i++){
   if(!BaseLineElectron(event->el_pt->at(i), event->el_delta_z0->at(i), event->el_d0sig->at(i), event->el_eta->at(i), event->el_isMedium->at(i))) continue;
   CountElectron++;
   ElectronSize.push_back(i);
   if(event->el_charge->at(i) < 0) ElectronID = i;
   if(event->el_charge->at(i) > 0) PositronID = i;
 }

 int CountMuon = 0;
 for(int i = 0; i < event->mu_eta->size(); i++){
   if(!BaseLineMuon(event->mu_pt->at(i), event->mu_delta_z0->at(i), event->mu_d0sig->at(i), event->mu_eta->at(i))) continue;
   CountMuon++;
 }

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 1, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(1, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(1, 1);

 if(CountElectron != 2 || CountMuon != 0) return false;

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 2, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(2, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(2, 1);

 if(event->el_trigMatch->at(ElectronSize.at(0)) != 1 && event->el_trigMatch->at(ElectronSize.at(1)) != 1) return false;

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 3, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(3, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(3, 1);

 if(event->el_isolation_ptvarcone20->at(ElectronSize.at(0)) / event->el_pt->at(ElectronSize.at(0)) > 0.1 || event->el_isolation_ptvarcone20->at(ElectronSize.at(1)) / event->el_pt->at(ElectronSize.at(1)) > 0.1) return false;

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 4, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(4, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(4, 1);

 if(event->el_charge->at(ElectronSize.at(0)) * event->el_charge->at(ElectronSize.at(1)) > 0) return false;

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 5, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(5, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(5, 1);

 if(event->el_pt->at(ElectronID) < 25000 || event->el_pt->at(PositronID) < 25000) return false;

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 6, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(6, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(6, 1);

 RecoilPt = event->Recoil;
 RecoilEta = 0;
 RecoilPhi = event->Recoil_Phi;

 Electron_reco.SetPtEtaPhiM(event->el_pt->at(ElectronID), event->el_eta->at(ElectronID), event->el_phi->at(ElectronID), 0);
 Positron_reco.SetPtEtaPhiM(event->el_pt->at(PositronID), event->el_eta->at(PositronID), event->el_phi->at(PositronID), 0);
 ZBoson_reco = Electron_reco + Positron_reco;

 double TriggerSF;
 double ScaleFactor1;
 double ScaleFactor2;

 if(!isData) TriggerSF = (1 - (1 - event->el_trigmceff->at(ElectronID) * event->el_trigsf->at(ElectronID)) * (1 - event->el_trigmceff->at(PositronID) * event->el_trigsf->at(PositronID))) / (1 - (1 - event->el_trigmceff->at(ElectronID)) * (1 - event->el_trigmceff->at(PositronID)));

 if(!isData) ScaleFactor1 = TotalWeight * EventWeight * event->el_recosf->at(ElectronID) * event->el_idsf->at(ElectronID) * event->el_isosf->at(ElectronID) * event->el_trigsf->at(ElectronID);
 if(!isData) ScaleFactor2 = TotalWeight * EventWeight * event->el_recosf->at(PositronID) * event->el_idsf->at(PositronID) * event->el_isosf->at(PositronID) * event->el_trigsf->at(PositronID);

 if(!isData) ScaleFactor = TotalWeight * EventWeight * event->el_recosf->at(ElectronID) * event->el_idsf->at(ElectronID) * event->el_isosf->at(ElectronID) * event->el_recosf->at(PositronID) * event->el_idsf->at(PositronID) * event->el_isosf->at(PositronID) * TriggerSF;
 if(isData) ScaleFactor = 1.0;

 if(ZBoson_reco.M() < 66000 || ZBoson_reco.M() > 116000) return false;

 if(isSignal) myhists->ZEvent_ZeeEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 7, 1);
 if(nchannel == -1) myhists->DataZEvent_ZeeEvent_CutFlow->at(iThread - 1)->Fill(7, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeEvent_CutFlow_bkg->at(iThread - 1)->Fill(7, 1);

//start event selection

 if(isSignal) myhists->ZEvent_ZeeMass_reco_sys->at(iThread - 1)->Fill(isys, ZBoson_reco.M(), ScaleFactor);
 if(nchannel == -1) myhists->DataZEvent_ZeeMass_reco->at(iThread - 1)->Fill(ZBoson_reco.M(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeMass_reco_bkg->at(iThread - 1)->Fill(ZBoson_reco.M(), ScaleFactor);

 if(isSignal) myhists->ZEvent_ZeePt_reco_sys->at(iThread - 1)->Fill(isys, ZBoson_reco.Pt(), ScaleFactor);
 if(nchannel == -1) myhists->DataZEvent_ZeePt_reco->at(iThread - 1)->Fill(ZBoson_reco.Pt(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeePt_reco_bkg->at(iThread - 1)->Fill(ZBoson_reco.Pt(), ScaleFactor);

 if(isSignal) myhists->ZEvent_ZeeRapidity_reco_sys->at(iThread - 1)->Fill(isys, ZBoson_reco.Rapidity(), ScaleFactor);
 if(nchannel == -1) myhists->DataZEvent_ZeeRapidity_reco->at(iThread - 1)->Fill(ZBoson_reco.Rapidity(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZeeRapidity_reco_bkg->at(iThread - 1)->Fill(ZBoson_reco.Rapidity(), ScaleFactor);
*/
 return false;

}
#endif
