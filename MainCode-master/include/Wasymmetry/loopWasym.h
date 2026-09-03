#ifndef loopWasym_h
#define loopWasym_h

#include "Analysis/loopMC.h"

#include "Wasymmetry/HistsWasym.h"
#include "Wasymmetry/TreeForWasym.h"

using namespace std;

class EventWasym
{
 public:

 vector<float> *el_pt;
 vector<float> *el_eta;
 vector<float> *el_phi;
 vector<float> *el_delta_z0;
 vector<float> *el_d0sig;
 vector<bool>  *el_isMedium;
 vector<float> *el_charge;
 vector<float> *el_isolation_ptvarcone20;
 vector<bool>  *el_trigMatch;
 vector<bool>  *el_inrecoil;

 vector<float> *el_recosf;
 vector<float> *el_idsf;
 vector<float> *el_isosf;
 vector<float> *el_trigsf;
 vector<float> *el_trigmceff;

 vector<float> *mu_pt;
 vector<float> *mu_eta;
 vector<float> *mu_phi;
 vector<float> *mu_delta_z0;
 vector<float> *mu_d0sig;
 vector<float> *mu_charge;
 vector<float> *mu_isolation_ptvarcone20;
 vector<bool>  *mu_trigMatch;
 vector<bool>  *mu_inrecoil;

 vector<float> *mu_recosf;
 vector<float> *mu_ttvasf;
 vector<float> *mu_isosf;
 vector<float> *mu_trigsf;
 vector<float> *mu_trigmceff;

 Float_t         Recoil;
 Float_t         Recoil_Phi;

 Float_t         EventWeight_gen;
 Float_t         EventWeight_vertex;
 Float_t         SumETWeight;

 vector<float> *Truth_Lepton_Pt;
 vector<float> *Truth_Lepton_Eta;
 vector<float> *Truth_Lepton_Phi;
 vector<float> *Truth_Lepton_E;
 vector<int> *Truth_Lepton_ID;

 vector<float> *Truth_Neutrino_Pt;
 vector<float> *Truth_Neutrino_Eta;
 vector<float> *Truth_Neutrino_Phi;
 vector<float> *Truth_Neutrino_E;
 vector<int> *Truth_Neutrino_ID;

};

class loopWasym : public loopMC
{
 public:

 HistsWasym *myhists;

 TreeForWasym *WasymTree;

 bool isCut = false;
 bool OnlyNominal = true;

 double Lumi = 339.8;//pb-1

 double ScaleFactor;
 double LeptonEta, LeptonPt, LeptonPhi, LeptonEtaAbs;
 double AntiLeptonEta, AntiLeptonPt, AntiLeptonPhi, AntiLeptonEtaAbs;
 double NeutrinoPt;

 EventWasym DefaultEvent;
 EventWasym ProcessEvent;

 TLorentzVector ZBoson_reco;
 TLorentzVector Electron_reco;
 TLorentzVector Positron_reco;
 TLorentzVector Muon_reco;
 TLorentzVector AntiMuon_reco;

 TLorentzVector Lepton_reco;
 TLorentzVector Neutrino_reco;
 TLorentzVector Recoil_reco;
 TLorentzVector WBoson_reco;

 TLorentzVector Electron_truth;
 TLorentzVector Positron_truth;
 TLorentzVector Muon_truth;
 TLorentzVector AntiMuon_truth;
 TLorentzVector Neutrino_truth;
 TLorentzVector WBoson_truth;
 TLorentzVector ZBoson_truth;

 bool isWplusenuEvent = false;
 bool isWplusmunuEvent = false;
 bool isWplustaonuEvent = false;
 bool isWminusenuEvent = false;
 bool isWminusmunuEvent = false;
 bool isWminustaonuEvent = false;
 bool isZeeEvent = false;
 bool isZmumuEvent = false;
 bool isData = false;
 vector<bool> TypeVector;

 bool isElectron = false;
 bool isMuon = false;

 loopWasym(TString RootType);
 virtual void InputHist(HistsWasym* &myhists);
 virtual void InputTree(TreeForWasym *WasymTree);
 virtual void ReadTree(int ifile);
 virtual bool WenuSelection(int nchannel, TString SysName, EventWasym* event);
 virtual bool WmunuSelection(int nchannel, TString SysName, EventWasym* event);
 virtual bool ZeeSelection(int nchannel, TString SysName, EventWasym* event);
 virtual bool ZmumuSelection(int nchannel, TString SysName, EventWasym* event);
 virtual bool TruthWenuSelection(int nchannel, EventWasym* event);
 virtual bool TruthWmunuSelection(int nchannel, EventWasym* event);
 virtual bool BaseLineElectron(float el_pt, float el_delta_z0, float el_d0sig, float el_eta, bool el_isMedium);
 virtual bool BaseLineMuon(float mu_pt, float mu_delta_z0, float mu_d0sig, float mu_eta);
 virtual void RunAllSystematic();
 virtual void End(int RootNumber);
 virtual void Finish();
 virtual ~loopWasym();

};

#endif
