#ifndef ZmumuSelection_cxx
#define ZmumuSelection_cxx

#include <iostream>
#include "Wasymmetry/loopWasym.h"

using namespace std;

bool loopWasym::ZmumuSelection(int nchannel, TString SysName, EventWasym* event)
{
/* bool isSignal = false;
 int isys = myhists->FindSysIndex(SysName, "ZSignal_Muon");
 if(nchannel == 361107) isSignal = true;

 if(!isSignal) isys = -1;

// if(isTest) cout<<"Zmumu Selection: This is the systematic "<<isys<<" selection."<<endl;

 double RecoilPt, RecoilEta, RecoilPhi, W_MT;
 double EventWeight = (double)event->EventWeight_gen * (double)event->EventWeight_vertex * (double)event->SumETWeight;

 int CountElectron = 0;
 for(int i = 0; i < event->el_eta->size(); i++){
   if(!BaseLineElectron(event->el_pt->at(i), event->el_delta_z0->at(i), event->el_d0sig->at(i), event->el_eta->at(i), event->el_isMedium->at(i))) continue;
   CountElectron++;
 }

 int CountMuon = 0;
 int MuonID = -1;
 int AntiMuonID = -1;
 vector<int> MuonSize;
 for(int i = 0; i < event->mu_eta->size(); i++){
   if(!BaseLineMuon(event->mu_pt->at(i), event->mu_delta_z0->at(i), event->mu_d0sig->at(i), event->mu_eta->at(i))) continue;
   CountMuon++;
   MuonSize.push_back(i);
   if(event->mu_charge->at(i) < 0) MuonID = i;
   if(event->mu_charge->at(i) > 0) AntiMuonID = i;
 }

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 1, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(1, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(1, 1);

 if(CountElectron != 0 || CountMuon != 2) return false;

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 2, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(2, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(2, 1);

 if(event->mu_trigMatch->at(MuonSize.at(0)) != 1 && event->mu_trigMatch->at(MuonSize.at(1)) != 1) return false;

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 3, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(3, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(3, 1);

 if(event->mu_isolation_ptvarcone20->at(MuonSize.at(0)) / event->mu_pt->at(MuonSize.at(0)) > 0.1 || event->mu_isolation_ptvarcone20->at(MuonSize.at(1)) / event->mu_pt->at(MuonSize.at(1)) > 0.1) return false;

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 4, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(4, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(4, 1);

 if(event->mu_charge->at(MuonSize.at(0)) * event->mu_charge->at(MuonSize.at(1)) > 0) return false;

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 5, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(5, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(5, 1);

 if(event->mu_pt->at(MuonID) < 25000 || event->mu_pt->at(AntiMuonID) < 25000) return false;

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 6, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(6, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(6, 1);

 RecoilPt = event->Recoil;
 RecoilEta = 0;
 RecoilPhi = event->Recoil_Phi;

 Muon_reco.SetPtEtaPhiM(event->mu_pt->at(MuonID), event->mu_eta->at(MuonID), event->mu_phi->at(MuonID), 0);
 AntiMuon_reco.SetPtEtaPhiM(event->mu_pt->at(AntiMuonID), event->mu_eta->at(AntiMuonID), event->mu_phi->at(AntiMuonID), 0);
 ZBoson_reco = Muon_reco + AntiMuon_reco;

 double TriggerSF;
 double ScaleFactor1;
 double ScaleFactor2;

 if(!isData) TriggerSF = (1 - (1 - event->mu_trigmceff->at(MuonID) * event->mu_trigsf->at(MuonID)) * (1 - event->mu_trigmceff->at(AntiMuonID) * event->mu_trigsf->at(AntiMuonID))) / (1 - (1 - event->mu_trigmceff->at(MuonID)) * (1 - event->mu_trigmceff->at(AntiMuonID)));

 if(!isData) ScaleFactor1 = TotalWeight * EventWeight * event->mu_recosf->at(MuonID) * event->mu_ttvasf->at(MuonID) * event->mu_isosf->at(MuonID) * event->mu_trigsf->at(MuonID);
 if(!isData) ScaleFactor2 = TotalWeight * EventWeight * event->mu_recosf->at(AntiMuonID) * event->mu_ttvasf->at(AntiMuonID) * event->mu_isosf->at(AntiMuonID) * event->mu_trigsf->at(AntiMuonID);

 if(!isData) ScaleFactor = TotalWeight * EventWeight * event->mu_recosf->at(MuonID) * event->mu_ttvasf->at(MuonID) * event->mu_isosf->at(MuonID) * event->mu_recosf->at(AntiMuonID) * event->mu_ttvasf->at(AntiMuonID) * event->mu_isosf->at(AntiMuonID) * TriggerSF;
 if(isData) ScaleFactor = 1.0;

 if(ZBoson_reco.M() < 66000 || ZBoson_reco.M() > 116000) return false;

 if(isSignal) myhists->ZEvent_ZmmEvent_CutFlow_sys->at(iThread - 1)->Fill(isys, 7, 1);
 if(nchannel == -1) myhists->DataZEvent_ZmmEvent_CutFlow->at(iThread - 1)->Fill(7, 1);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmEvent_CutFlow_bkg->at(iThread - 1)->Fill(7, 1);

//start event selection
 if(isSignal) myhists->ZEvent_ZmmMass_reco_sys->at(iThread - 1)->Fill(isys, ZBoson_reco.M(), ScaleFactor);
 if(nchannel == -1) myhists->DataZEvent_ZmmMass_reco->at(iThread - 1)->Fill(ZBoson_reco.M(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmMass_reco_bkg->at(iThread - 1)->Fill(ZBoson_reco.M(), ScaleFactor);

 if(isSignal) myhists->ZEvent_ZmmPt_reco_sys->at(iThread - 1)->Fill(isys, ZBoson_reco.Pt(), ScaleFactor);
 if(nchannel == -1) myhists->DataZEvent_ZmmPt_reco->at(iThread - 1)->Fill(ZBoson_reco.Pt(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmPt_reco_bkg->at(iThread - 1)->Fill(ZBoson_reco.Pt(), ScaleFactor);

 if(isSignal) myhists->ZEvent_ZmmRapidity_reco_sys->at(iThread - 1)->Fill(isys, ZBoson_reco.Rapidity(), ScaleFactor);
 if(nchannel == -1) myhists->DataZEvent_ZmmRapidity_reco->at(iThread - 1)->Fill(ZBoson_reco.Rapidity(), ScaleFactor);
 if(nchannel != -1 && !isSignal) myhists->ZEvent_ZmmRapidity_reco_bkg->at(iThread - 1)->Fill(ZBoson_reco.Rapidity(), ScaleFactor);
*/
 return false;

}
#endif
