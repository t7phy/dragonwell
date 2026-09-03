#ifndef WZPolSelection_cxx
#define WZPolSelection_cxx

#include <iostream>
#include "WZPolarization/loopWZPolarization.h"

using namespace std;

void loopWZPolarization::GetCutInformation()
{
 TLorentzVector ZBoson;
 TLorentzVector WBoson;
 TLorentzVector WZBoson;
 TLorentzVector ThreeLepton;

 passZZVeto = ((PreWZPolarizationTree->nSoftElectrons + PreWZPolarizationTree->nSoftMuons) < 4);

 SelectedEvent.ZLepton1 = SelectedEvent.Lepton1;
 SelectedEvent.ZLepton2 = SelectedEvent.Lepton2;
 SelectedEvent.WLepton = SelectedEvent.Lepton3;

 SelectedEvent.Mt_W = CalculateTransverseMass(SelectedEvent.WLepton.P4, SelectedEvent.WNeutrino.P4);

 passSFOS = (SelectedEvent.m_Channel == 1 || SelectedEvent.m_Channel == 2 || SelectedEvent.m_Channel == 3 || SelectedEvent.m_Channel == 4);

 ZBoson = SelectedEvent.ZLepton1.P4 + SelectedEvent.ZLepton2.P4;
 WBoson = SelectedEvent.WLepton.P4 + SelectedEvent.WNeutrino.P4;
 ThreeLepton = ZBoson + SelectedEvent.WLepton.P4;
 WZBoson = ZBoson + WBoson;
 passMassWindow1 = (fabs(ZBoson.M() - ZPeakMass) < 20);
 passMassWindow2 = ZBoson.M() > 81 && ZBoson.M() < 106;
 passMassWindow3 = ((SelectedEvent.ZLepton2.P4 + SelectedEvent.WLepton.P4).M() - ZPeakMass) < 20;
 passMassWindow4 = (fabs(ZBoson.M() - ZPeakMass) < 10);
 bool passMassWindow5 = ZBoson.M() > 85 && ZBoson.M() < 96;
 bool pass3lMassWindow = ThreeLepton.M() > 87 && ThreeLepton.M() < 93;
 SelectedEvent.M_3l = ThreeLepton.M();

// if(PreWZPolarizationTree->EventNumber == 47357312){//yfu
//   cout<<47357312<<endl;
//   cout<<fixed<<setprecision(10)<<ZBoson.M()<<endl;//yfu
//   cout<<fixed<<setprecision(10)<<SelectedEvent.ZLepton1.P4.Pt()<<" "<<SelectedEvent.ZLepton1.P4.Eta()<<" "<<SelectedEvent.ZLepton1.P4.Phi()<<" "<<SelectedEvent.ZLepton1.P4.E()<<endl;
//   cout<<fixed<<setprecision(10)<<SelectedEvent.ZLepton2.P4.Pt()<<" "<<SelectedEvent.ZLepton2.P4.Eta()<<" "<<SelectedEvent.ZLepton2.P4.Phi()<<" "<<SelectedEvent.ZLepton2.P4.E()<<endl;
// }
// if(PreWZPolarizationTree->EventNumber == 20644247){//yfu
//   cout<<"20644247"<<endl;
//   cout<<fixed<<setprecision(10)<<ZBoson.M()<<endl;//yfu
//   cout<<fixed<<setprecision(10)<<SelectedEvent.ZLepton1.P4.Pt()<<" "<<SelectedEvent.ZLepton1.P4.Eta()<<" "<<SelectedEvent.ZLepton1.P4.Phi()<<" "<<SelectedEvent.ZLepton1.P4.E()<<endl;
//   cout<<fixed<<setprecision(10)<<SelectedEvent.ZLepton2.P4.Pt()<<" "<<SelectedEvent.ZLepton2.P4.Eta()<<" "<<SelectedEvent.ZLepton2.P4.Phi()<<" "<<SelectedEvent.ZLepton2.P4.E()<<endl;
// }


 if(SelectedEvent.ZLepton1.pdgID == 11){
   SelectedEvent.ZLepton1.IPID = (fabs(SelectedEvent.ZLepton1.d0Sig) < 5.0);
//   SelectedEvent.ZLepton1.ZTightIso = SelectedEvent.ZLepton1.FCHighPtIso;
//   SelectedEvent.ZLepton1.ZTightIsoWeight = SelectedEvent.ZLepton1.FCHighPtIsoWeight;
   SelectedEvent.ZLepton1.ZTightIso = SelectedEvent.ZLepton1.HighPtCaloOnlyIso;
   SelectedEvent.ZLepton1.ZTightIsoWeight = SelectedEvent.ZLepton1.HighPtCaloOnly_MediumID_IsoWeight;

//   SelectedEvent.ZLepton1.ZTightIso = SelectedEvent.ZLepton1.FCTightIso;
//   SelectedEvent.ZLepton1.ZTightIsoWeight = SelectedEvent.ZLepton1.FCTightIsoWeight;
//   SelectedEvent.ZLepton1.WTightIso = SelectedEvent.ZLepton1.FCTightIso;
//   SelectedEvent.ZLepton1.WTightIsoWeight = SelectedEvent.ZLepton1.FCTightIsoWeight;
   SelectedEvent.ZLepton1.WTightIso = SelectedEvent.ZLepton1.Tight_VarRadIso;
   SelectedEvent.ZLepton1.WTightIsoWeight = SelectedEvent.ZLepton1.Tight_VarRad_TightID_IsoWeight;
 }
 else if(SelectedEvent.ZLepton1.pdgID == 13){
   SelectedEvent.ZLepton1.IPID = (fabs(SelectedEvent.ZLepton1.d0Sig) < 3.0);
   SelectedEvent.ZLepton1.ZTightIso = SelectedEvent.ZLepton1.PflowLooseIso;
   SelectedEvent.ZLepton1.ZTightIsoWeight = SelectedEvent.ZLepton1.PflowLooseIsoWeight;
//   SelectedEvent.ZLepton1.ZTightIso = SelectedEvent.ZLepton1.PflowTightIso;
//   SelectedEvent.ZLepton1.ZTightIsoWeight = SelectedEvent.ZLepton1.PflowTightIsoWeight;
   SelectedEvent.ZLepton1.WTightIso = SelectedEvent.ZLepton1.PflowTightIso;
   SelectedEvent.ZLepton1.WTightIsoWeight = SelectedEvent.ZLepton1.PflowTightIsoWeight;
 }

 if(SelectedEvent.ZLepton2.pdgID == 11){
   SelectedEvent.ZLepton2.IPID = (fabs(SelectedEvent.ZLepton2.d0Sig) < 5.0);
//   SelectedEvent.ZLepton2.ZTightIso = SelectedEvent.ZLepton2.FCHighPtIso;
//   SelectedEvent.ZLepton2.ZTightIsoWeight = SelectedEvent.ZLepton2.FCHighPtIsoWeight;
   SelectedEvent.ZLepton2.ZTightIso = SelectedEvent.ZLepton2.HighPtCaloOnlyIso;
   SelectedEvent.ZLepton2.ZTightIsoWeight = SelectedEvent.ZLepton2.HighPtCaloOnly_MediumID_IsoWeight;

//   SelectedEvent.ZLepton2.ZTightIso = SelectedEvent.ZLepton2.FCTightIso;
//   SelectedEvent.ZLepton2.ZTightIsoWeight = SelectedEvent.ZLepton2.FCTightIsoWeight;
//   SelectedEvent.ZLepton2.WTightIso = SelectedEvent.ZLepton2.FCTightIso;
//   SelectedEvent.ZLepton2.WTightIsoWeight = SelectedEvent.ZLepton2.FCTightIsoWeight;
   SelectedEvent.ZLepton2.WTightIso = SelectedEvent.ZLepton2.Tight_VarRadIso;
   SelectedEvent.ZLepton2.WTightIsoWeight = SelectedEvent.ZLepton2.Tight_VarRad_TightID_IsoWeight;
 }
 else if(SelectedEvent.ZLepton2.pdgID == 13){
   SelectedEvent.ZLepton2.IPID = (fabs(SelectedEvent.ZLepton2.d0Sig) < 3.0);
   SelectedEvent.ZLepton2.ZTightIso = SelectedEvent.ZLepton2.PflowLooseIso;
   SelectedEvent.ZLepton2.ZTightIsoWeight = SelectedEvent.ZLepton2.PflowLooseIsoWeight;
//   SelectedEvent.ZLepton2.ZTightIso = SelectedEvent.ZLepton2.PflowTightIso;
//   SelectedEvent.ZLepton2.ZTightIsoWeight = SelectedEvent.ZLepton2.PflowTightIsoWeight;
   SelectedEvent.ZLepton2.WTightIso = SelectedEvent.ZLepton2.PflowTightIso;
   SelectedEvent.ZLepton2.WTightIsoWeight = SelectedEvent.ZLepton2.PflowTightIsoWeight;
 }

 if(SelectedEvent.WLepton.pdgID == 11){
   SelectedEvent.WLepton.IPID = (fabs(SelectedEvent.WLepton.d0Sig) < 5.0);
//   SelectedEvent.WLepton.ZTightIso = SelectedEvent.WLepton.FCHighPtIso;
//   SelectedEvent.WLepton.ZTightIsoWeight = SelectedEvent.WLepton.FCHighPtIsoWeight;
   SelectedEvent.WLepton.ZTightIso = SelectedEvent.WLepton.HighPtCaloOnlyIso;
   SelectedEvent.WLepton.ZTightIsoWeight = SelectedEvent.WLepton.HighPtCaloOnly_MediumID_IsoWeight;

//   SelectedEvent.WLepton.ZTightIso = SelectedEvent.WLepton.FCTightIso;
//   SelectedEvent.WLepton.ZTightIsoWeight = SelectedEvent.WLepton.FCTightIsoWeight;
//   SelectedEvent.WLepton.WTightIso = SelectedEvent.WLepton.FCTightIso;
//   SelectedEvent.WLepton.WTightIsoWeight = SelectedEvent.WLepton.FCTightIsoWeight;
   SelectedEvent.WLepton.WTightIso = SelectedEvent.WLepton.Tight_VarRadIso;
   SelectedEvent.WLepton.WTightIsoWeight = SelectedEvent.WLepton.Tight_VarRad_TightID_IsoWeight;
 }
 else if(SelectedEvent.WLepton.pdgID == 13){
   SelectedEvent.WLepton.IPID = (fabs(SelectedEvent.WLepton.d0Sig) < 3.0);
   SelectedEvent.WLepton.ZTightIso = SelectedEvent.WLepton.PflowLooseIso;
   SelectedEvent.WLepton.ZTightIsoWeight = SelectedEvent.WLepton.PflowLooseIsoWeight;
//   SelectedEvent.WLepton.ZTightIso = SelectedEvent.WLepton.PflowTightIso;
//   SelectedEvent.WLepton.ZTightIsoWeight = SelectedEvent.WLepton.PflowTightIsoWeight;
   SelectedEvent.WLepton.WTightIso = SelectedEvent.WLepton.PflowTightIso;
   SelectedEvent.WLepton.WTightIsoWeight = SelectedEvent.WLepton.PflowTightIsoWeight;
 }

// SelectedEvent.ZLepton1.Level = (1 + SelectedEvent.ZLepton1.FCTightIso) * (1 + SelectedEvent.ZLepton1.mediumID + SelectedEvent.ZLepton1.tightID);
// SelectedEvent.ZLepton2.Level = (1 + SelectedEvent.ZLepton2.FCTightIso) * (1 + SelectedEvent.ZLepton2.mediumID + SelectedEvent.ZLepton2.tightID);
// SelectedEvent.WLepton.Level = (1 + SelectedEvent.WLepton.FCTightIso) * (1 + SelectedEvent.WLepton.mediumID + SelectedEvent.WLepton.tightID);
 SelectedEvent.ZLepton1.Level = (1 + SelectedEvent.ZLepton1.ZTightIso) * (1 + SelectedEvent.ZLepton1.mediumID + SelectedEvent.ZLepton1.tightID) * (SelectedEvent.ZLepton1.isBaseline);
 SelectedEvent.ZLepton2.Level = (1 + SelectedEvent.ZLepton2.ZTightIso) * (1 + SelectedEvent.ZLepton2.mediumID + SelectedEvent.ZLepton2.tightID) * (SelectedEvent.ZLepton2.isBaseline);
 SelectedEvent.WLepton.Level = (1 + SelectedEvent.WLepton.WTightIso) * (1 + SelectedEvent.WLepton.mediumID + SelectedEvent.WLepton.tightID) * (SelectedEvent.WLepton.isBaseline);

 SelectedEvent.ZLepton1.WLevel = (1 + SelectedEvent.ZLepton1.WTightIso) * (1 + SelectedEvent.ZLepton1.mediumID + SelectedEvent.ZLepton1.tightID) * (SelectedEvent.ZLepton1.isBaseline);
 SelectedEvent.ZLepton2.WLevel = (1 + SelectedEvent.ZLepton2.WTightIso) * (1 + SelectedEvent.ZLepton2.mediumID + SelectedEvent.ZLepton2.tightID) * (SelectedEvent.ZLepton2.isBaseline);
 SelectedEvent.WLepton.WLevel = (1 + SelectedEvent.WLepton.WTightIso) * (1 + SelectedEvent.WLepton.mediumID + SelectedEvent.WLepton.tightID) * (SelectedEvent.WLepton.isBaseline);
 SelectedEvent.ZLepton1.ZLevel = (1 + SelectedEvent.ZLepton1.ZTightIso) * (1 + SelectedEvent.ZLepton1.mediumID + SelectedEvent.ZLepton1.tightID) * (SelectedEvent.ZLepton1.isBaseline);
 SelectedEvent.ZLepton2.ZLevel = (1 + SelectedEvent.ZLepton2.ZTightIso) * (1 + SelectedEvent.ZLepton2.mediumID + SelectedEvent.ZLepton2.tightID) * (SelectedEvent.ZLepton2.isBaseline);
 SelectedEvent.WLepton.ZLevel = (1 + SelectedEvent.WLepton.ZTightIso) * (1 + SelectedEvent.WLepton.mediumID + SelectedEvent.WLepton.tightID) * (SelectedEvent.WLepton.isBaseline);

 bool AdditionalCondition1 = false;
 if(fabs(SelectedEvent.ZLepton1.pdgID) == 11) AdditionalCondition1 = SelectedEvent.ZLepton1.IPID;
 if(fabs(SelectedEvent.ZLepton1.pdgID) == 13) AdditionalCondition1 = SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.mediumID;
// AdditionalCondition1 = AdditionalCondition1 * SelectedEvent.ZLepton1.isBaseline;
// AdditionalCondition1 = AdditionalCondition1 * SelectedEvent.ZLepton1.FCLooseIso;
 bool AdditionalCondition2 = false;
 if(fabs(SelectedEvent.ZLepton2.pdgID) == 11) AdditionalCondition2 = SelectedEvent.ZLepton2.IPID;
 if(fabs(SelectedEvent.ZLepton2.pdgID) == 13) AdditionalCondition2 = SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.mediumID;
// AdditionalCondition2 = AdditionalCondition2 * SelectedEvent.ZLepton2.isBaseline;
// AdditionalCondition2 = AdditionalCondition2 * SelectedEvent.ZLepton2.FCLooseIso;
 bool AdditionalCondition3 = false;
 if(fabs(SelectedEvent.WLepton.pdgID) == 11) AdditionalCondition3 = SelectedEvent.WLepton.IPID;
 if(fabs(SelectedEvent.WLepton.pdgID) == 13) AdditionalCondition3 = SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.mediumID;
// AdditionalCondition3 = AdditionalCondition3 * SelectedEvent.WLepton.isBaseline;
// AdditionalCondition3 = AdditionalCondition3 * SelectedEvent.WLepton.FCLooseIso;

 bool AdditionalCondition = false;
 AdditionalCondition = AdditionalCondition1 && AdditionalCondition2 && AdditionalCondition3;
// AdditionalCondition = SelectedEvent.passThreeBaseline;

 SelectedEvent.dR_Lep1_Lep2 = SelectedEvent.ZLepton1.P4.DeltaR(SelectedEvent.ZLepton2.P4);
 SelectedEvent.dR_Lep1_Lep3 = SelectedEvent.ZLepton1.P4.DeltaR(SelectedEvent.WLepton.P4);
 SelectedEvent.dR_Lep2_Lep3 = SelectedEvent.ZLepton2.P4.DeltaR(SelectedEvent.WLepton.P4);

 SelectedEvent.passDeltaR = (SelectedEvent.dR_Lep1_Lep2 > 0.2)
                            && (SelectedEvent.dR_Lep1_Lep3 > 0.3)
                            && (SelectedEvent.dR_Lep2_Lep3 > 0.3);

 SelectedEvent.passThreeBaseline = SelectedEvent.ZLepton1.isBaseline && SelectedEvent.ZLepton2.isBaseline && SelectedEvent.WLepton.isBaseline;

 passZZCR = (!passZZVeto)
            && (SelectedEvent.m_Channel >= 1 && SelectedEvent.m_Channel <= 4)
            && (passMassWindow4)
            && (SelectedEvent.Mt_W > 30)
            && (SelectedEvent.WLepton.P4.Pt() > 20)
            && (SelectedEvent.passDeltaR);

 passTopCR = (passZZVeto)
            && (passMassWindow4)
            && (SelectedEvent.Mt_W > 30)
            && (SelectedEvent.WLepton.P4.Pt() > 20)
            && (SelectedEvent.passDeltaR)
            && (SelectedEvent.m_Channel >= 1 || SelectedEvent.m_Channel <= 4)
            && (SelectedEvent.NBjets == 0);

 passZFakeElCR = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)   //W Fake Electron
                 && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
                 && (passZZVeto)
                 && (SelectedEvent.m_Channel == 2)//mme
                 && (passMassWindow4)
                 && (AdditionalCondition)
                 //&& (SelectedEvent.WNeutrino.P4.Pt() < 30) //to be added after systematic
                 && (SelectedEvent.WLepton.P4.Pt() > 20);//promise to be same with inclusive region
//                 && (SelectedEvent.Mt_W < 40);

 SelectedEvent.passZFakeElCR_UpSys = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)   //W Fake Electron
                                  && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
                                  && (passZZVeto)
                                  && (SelectedEvent.m_Channel == 2)//mme
                                  && (passMassWindow4)
                                  && (AdditionalCondition)
                                  && (SelectedEvent.WLepton.P4.Pt() > 20)//promise to be same with inclusive region
                                  && (SelectedEvent.WNeutrino.P4.Pt() < 30)
                                  && (SelectedEvent.Mt_W < 40);

 SelectedEvent.passZFakeElCR_DownSys = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)   //W Fake Electron
                                    && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
                                    && (passZZVeto)
                                    && (SelectedEvent.m_Channel == 2)//mme
                                    && (passMassWindow4)
                                    && (AdditionalCondition)
                                    && (SelectedEvent.WLepton.P4.Pt() > 20)//promise to be same with inclusive region
                                    && (SelectedEvent.WNeutrino.P4.Pt() < 30)
                                    && (SelectedEvent.Mt_W < 20);

 passZFakeMuCR = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)   //W Fake Muon
                 && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
                 && (passZZVeto)
                 && (SelectedEvent.m_Channel == 3)//eem
                 && (passMassWindow4)
                 && (AdditionalCondition)
                 //&& (SelectedEvent.WNeutrino.P4.Pt() < 30) //to be added after systematic
                 && (SelectedEvent.WLepton.P4.Pt() > 20);//promise to be same with inclusive region
//                 && (SelectedEvent.Mt_W < 30);
//                 && (fabs(SelectedEvent.WLepton.d0Sig) > 3.0);

 passTopElCR = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 6)   //Z Fake Electron
               && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 6)
               && (passZZVeto)
               && (AdditionalCondition)
               && (SelectedEvent.m_Channel == 6)//mee
               //&& (SelectedEvent.WNeutrino.P4.Pt() > 25) //to be added after systematic
               && (SelectedEvent.NBjets > 0)
               && (SelectedEvent.WLepton.P4.Pt() < SelectedEvent.ZLepton2.P4.Pt())
               && (fabs(SelectedEvent.WLepton.d0Sig) > fabs(SelectedEvent.ZLepton2.d0Sig))
               && (fabs(SelectedEvent.ZLepton2.d0Sig) < 1.0)
               && (passMassWindow4)
               && (SelectedEvent.NBjets == 1);

 passTopMuCR =  (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 6)   //Z Fake Muon
               && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 6)
               && (passZZVeto)
               && (AdditionalCondition)
               && (SelectedEvent.m_Channel == 5)//emm
               //&& (SelectedEvent.WNeutrino.P4.Pt() > 25) //to be added after systematic
               && (SelectedEvent.NBjets > 0)
               && (SelectedEvent.WLepton.P4.Pt() < SelectedEvent.ZLepton2.P4.Pt())
               && (fabs(SelectedEvent.WLepton.d0Sig) > fabs(SelectedEvent.ZLepton2.d0Sig))
               && (fabs(SelectedEvent.ZLepton2.d0Sig) < 1.0)
               && (passMassWindow4) 
               && (SelectedEvent.NBjets == 1);

 passWZInclusive = (passZZVeto)
                   && (SelectedEvent.m_Channel >= 1 && SelectedEvent.m_Channel <= 4)//SFOS
                   && (passMassWindow1)
                   && (SelectedEvent.WNeutrino.P4.Pt() > 25);

 passHardWZInclusive = (passZZVeto)
                       && (SelectedEvent.m_Channel >= 1 && SelectedEvent.m_Channel <= 4)//SFOS
                       && (passMassWindow4)
                       && (SelectedEvent.Mt_W > 30)
                       && (SelectedEvent.WLepton.P4.Pt() > 20)
                       && (SelectedEvent.passDeltaR);

 passWZInclusiveNoMET = (passZZVeto)
                       && (SelectedEvent.m_Channel >= 1 && SelectedEvent.m_Channel <= 4)//SFOS
                       && (passMassWindow4);

 passTopEnrichCR = (passZZVeto)
               && (SelectedEvent.m_Channel == 5 || SelectedEvent.m_Channel == 6)
               && (SelectedEvent.WNeutrino.P4.Pt() > 25)
               && (SelectedEvent.NBjets > 0)
               && (SelectedEvent.WLepton.P4.Pt() < SelectedEvent.ZLepton2.P4.Pt());

 passTruthMatch1 = SelectedEvent.ZLepton1.truthMatched;
 passTruthMatch2 = SelectedEvent.ZLepton2.truthMatched;
 passTruthMatch3 = SelectedEvent.WLepton.truthMatched;

 passZCondition1 = SelectedEvent.ZLepton1.ZLevel >= 4;
 passZCondition2 = SelectedEvent.ZLepton2.ZLevel >= 4;
 passZCondition3 = SelectedEvent.WLepton.ZLevel >= 4;

 passWCondition1 = SelectedEvent.ZLepton1.WLevel >= 6;
 passWCondition2 = SelectedEvent.ZLepton2.WLevel >= 6;
 passWCondition3 = SelectedEvent.WLepton.WLevel >= 6;

 passMediumID1 = SelectedEvent.ZLepton1.mediumID;
 passMediumID2 = SelectedEvent.ZLepton2.mediumID;
 passMediumID3 = SelectedEvent.WLepton.mediumID;
 passTightID1 = SelectedEvent.ZLepton1.tightID;
 passTightID2 = SelectedEvent.ZLepton2.tightID;
 passTightID3 = SelectedEvent.WLepton.tightID;

 passIPID1 = SelectedEvent.ZLepton1.IPID;
 passIPID2 = SelectedEvent.ZLepton2.IPID;
 passIPID3 = SelectedEvent.WLepton.IPID;

 passTTT = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level >= 6);

 passTTL = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level < 6);

 passTLT = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level < 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level >= 6);

 passLTT = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level < 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level >= 6);

 passTLL = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level >= 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level < 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level < 6);

 passLTL = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level < 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level >= 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level < 6);

 passLLT = (SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton1.Level < 4)
           && (SelectedEvent.ZLepton2.IPID && SelectedEvent.ZLepton2.Level < 4)
           && (AdditionalCondition)
           && (SelectedEvent.WLepton.IPID && SelectedEvent.WLepton.Level >= 6);

 passWZInclusiveLoose = passWZInclusive;
 passHardWZInclusiveLoose = passHardWZInclusive;

 passWZInclusive = passWZInclusive * passTTT;
 passHardWZInclusive = passHardWZInclusive * passTTT;

 passZCondition = SelectedEvent.WLepton.ZLevel >= 4;
 passWCondition = SelectedEvent.WLepton.WLevel >= 6;

 SelectedEvent.passZZCR = passZZCR;
 SelectedEvent.passTopCR = passTopCR;
 SelectedEvent.passZFakeElCR = passZFakeElCR;
 SelectedEvent.passZFakeMuCR = passZFakeMuCR;
 SelectedEvent.passTopElCR = passTopElCR;
 SelectedEvent.passTopMuCR = passTopMuCR;
 SelectedEvent.passWZInclusive = passWZInclusive;
 SelectedEvent.passHardWZInclusive = passHardWZInclusive;
 SelectedEvent.passWZInclusiveLoose = passWZInclusiveLoose;
 SelectedEvent.passHardWZInclusiveLoose = passHardWZInclusiveLoose;
 SelectedEvent.passWZqqSR = passWZqqSR;
 SelectedEvent.passWZqqCR = passWZqqCR;
 SelectedEvent.passWZVBSSR = passWZVBSSR;
 SelectedEvent.passWZVBSCR = passWZVBSCR;
 SelectedEvent.passWZInclusiveNoMET = passWZInclusiveNoMET;
 SelectedEvent.passTopEnrichCR = passTopEnrichCR;
 SelectedEvent.passTTT = passTTT;
 SelectedEvent.passTTL = passTTL;
 SelectedEvent.passTLT = passTLT;
 SelectedEvent.passLTT = passLTT;
 SelectedEvent.passTLL = passTLL;
 SelectedEvent.passLTL = passLTL;
 SelectedEvent.passLLT = passLLT;
 SelectedEvent.passZCondition = passZCondition;
 SelectedEvent.passWCondition = passWCondition;

 SelectedEvent.passTruthMatch1 = passTruthMatch1;
 SelectedEvent.passTruthMatch2 = passTruthMatch2;
 SelectedEvent.passTruthMatch3 = passTruthMatch3;

 SelectedEvent.passZCondition1 = passZCondition1;
 SelectedEvent.passZCondition2 = passZCondition2;
 SelectedEvent.passZCondition3 = passZCondition3;

 SelectedEvent.passWCondition1 = passWCondition1;
 SelectedEvent.passWCondition2 = passWCondition2;
 SelectedEvent.passWCondition3 = passWCondition3;

 SelectedEvent.passMediumID1 = passMediumID1;
 SelectedEvent.passMediumID2 = passMediumID2;
 SelectedEvent.passMediumID3 = passMediumID3;
 SelectedEvent.passTightID1 = passTightID1;
 SelectedEvent.passTightID2 = passTightID2;
 SelectedEvent.passTightID3 = passTightID3;

 SelectedEvent.passIPID1 = passIPID1;
 SelectedEvent.passIPID2 = passIPID2;
 SelectedEvent.passIPID3 = passIPID3;

 if(SelectedEvent.MCType != -1){
//   if(SelectedEvent.ZLepton1.pdgID == 11) SelectedEvent.Lep1WeightZ = SelectedEvent.ZLepton1.mediumIDWeight * SelectedEvent.ZLepton1.FCTightIsoWeight * SelectedEvent.ZLepton1.recoWeight;
//   if(SelectedEvent.ZLepton1.pdgID == 13) SelectedEvent.Lep1WeightZ = SelectedEvent.ZLepton1.mediumIDWeight * SelectedEvent.ZLepton1.FCTightIsoWeight * SelectedEvent.ZLepton1.IPWeight;
//   if(SelectedEvent.ZLepton2.pdgID == 11) SelectedEvent.Lep2WeightZ = SelectedEvent.ZLepton2.mediumIDWeight * SelectedEvent.ZLepton2.FCTightIsoWeight * SelectedEvent.ZLepton2.recoWeight;
//   if(SelectedEvent.ZLepton2.pdgID == 13) SelectedEvent.Lep2WeightZ = SelectedEvent.ZLepton2.mediumIDWeight * SelectedEvent.ZLepton2.FCTightIsoWeight * SelectedEvent.ZLepton2.IPWeight;
//   if(SelectedEvent.WLepton.pdgID == 11) SelectedEvent.Lep3WeightW = SelectedEvent.WLepton.tightIDWeight * SelectedEvent.WLepton.FCTightIsoWeight * SelectedEvent.WLepton.recoWeight;
//   if(SelectedEvent.WLepton.pdgID == 13) SelectedEvent.Lep3WeightW = SelectedEvent.WLepton.tightIDWeight * SelectedEvent.WLepton.FCTightIsoWeight * SelectedEvent.WLepton.IPWeight;
   if(SelectedEvent.ZLepton1.pdgID == 11) SelectedEvent.Lep1WeightZ = SelectedEvent.ZLepton1.mediumIDWeight * SelectedEvent.ZLepton1.ZTightIsoWeight * SelectedEvent.ZLepton1.recoWeight;
   if(SelectedEvent.ZLepton1.pdgID == 13) SelectedEvent.Lep1WeightZ = SelectedEvent.ZLepton1.mediumIDWeight * SelectedEvent.ZLepton1.ZTightIsoWeight * SelectedEvent.ZLepton1.IPWeight;
   if(SelectedEvent.ZLepton1.pdgID == 11) SelectedEvent.Lep1WeightW = SelectedEvent.ZLepton1.tightIDWeight * SelectedEvent.ZLepton1.WTightIsoWeight * SelectedEvent.ZLepton1.recoWeight;
   if(SelectedEvent.ZLepton1.pdgID == 13) SelectedEvent.Lep1WeightW = SelectedEvent.ZLepton1.tightIDWeight * SelectedEvent.ZLepton1.WTightIsoWeight * SelectedEvent.ZLepton1.IPWeight;

   if(SelectedEvent.ZLepton2.pdgID == 11) SelectedEvent.Lep2WeightZ = SelectedEvent.ZLepton2.mediumIDWeight * SelectedEvent.ZLepton2.ZTightIsoWeight * SelectedEvent.ZLepton2.recoWeight;
   if(SelectedEvent.ZLepton2.pdgID == 13) SelectedEvent.Lep2WeightZ = SelectedEvent.ZLepton2.mediumIDWeight * SelectedEvent.ZLepton2.ZTightIsoWeight * SelectedEvent.ZLepton2.IPWeight;
   if(SelectedEvent.ZLepton2.pdgID == 11) SelectedEvent.Lep2WeightW = SelectedEvent.ZLepton2.tightIDWeight * SelectedEvent.ZLepton2.WTightIsoWeight * SelectedEvent.ZLepton2.recoWeight;
   if(SelectedEvent.ZLepton2.pdgID == 13) SelectedEvent.Lep2WeightW = SelectedEvent.ZLepton2.tightIDWeight * SelectedEvent.ZLepton2.WTightIsoWeight * SelectedEvent.ZLepton2.IPWeight;

   if(SelectedEvent.WLepton.pdgID == 11) SelectedEvent.Lep3WeightZ = SelectedEvent.WLepton.mediumIDWeight * SelectedEvent.WLepton.ZTightIsoWeight * SelectedEvent.WLepton.recoWeight;
   if(SelectedEvent.WLepton.pdgID == 13) SelectedEvent.Lep3WeightZ = SelectedEvent.WLepton.mediumIDWeight * SelectedEvent.WLepton.ZTightIsoWeight * SelectedEvent.WLepton.IPWeight;
   if(SelectedEvent.WLepton.pdgID == 11) SelectedEvent.Lep3WeightW = SelectedEvent.WLepton.tightIDWeight * SelectedEvent.WLepton.WTightIsoWeight * SelectedEvent.WLepton.recoWeight;
   if(SelectedEvent.WLepton.pdgID == 13) SelectedEvent.Lep3WeightW = SelectedEvent.WLepton.tightIDWeight * SelectedEvent.WLepton.WTightIsoWeight * SelectedEvent.WLepton.IPWeight;


   if(SelectedEvent.ZLepton1.pdgID == 11) SelectedEvent.Lep1MediumIDWeight = SelectedEvent.ZLepton1.mediumIDWeight;
   if(SelectedEvent.ZLepton1.pdgID == 13) SelectedEvent.Lep1TightIDWeight = SelectedEvent.ZLepton1.tightIDWeight;
   if(SelectedEvent.ZLepton1.pdgID == 11) SelectedEvent.Lep1MediumIsoWeight = SelectedEvent.ZLepton1.ZTightIsoWeight * SelectedEvent.ZLepton1.recoWeight;
   if(SelectedEvent.ZLepton1.pdgID == 13) SelectedEvent.Lep1TightIsoWeight = SelectedEvent.ZLepton1.WTightIsoWeight * SelectedEvent.ZLepton1.IPWeight;

   if(SelectedEvent.ZLepton2.pdgID == 11) SelectedEvent.Lep2MediumIDWeight = SelectedEvent.ZLepton2.mediumIDWeight;
   if(SelectedEvent.ZLepton2.pdgID == 13) SelectedEvent.Lep2TightIDWeight = SelectedEvent.ZLepton2.tightIDWeight;
   if(SelectedEvent.ZLepton2.pdgID == 11) SelectedEvent.Lep2MediumIsoWeight = SelectedEvent.ZLepton2.ZTightIsoWeight * SelectedEvent.ZLepton2.recoWeight;
   if(SelectedEvent.ZLepton2.pdgID == 13) SelectedEvent.Lep2TightIsoWeight = SelectedEvent.ZLepton2.WTightIsoWeight * SelectedEvent.ZLepton2.IPWeight;

   if(SelectedEvent.WLepton.pdgID == 11) SelectedEvent.Lep3MediumIDWeight = SelectedEvent.WLepton.mediumIDWeight;
   if(SelectedEvent.WLepton.pdgID == 13) SelectedEvent.Lep3TightIDWeight = SelectedEvent.WLepton.tightIDWeight;
   if(SelectedEvent.WLepton.pdgID == 11) SelectedEvent.Lep3MediumIsoWeight = SelectedEvent.WLepton.ZTightIsoWeight * SelectedEvent.WLepton.recoWeight;
   if(SelectedEvent.WLepton.pdgID == 13) SelectedEvent.Lep3TightIsoWeight = SelectedEvent.WLepton.WTightIsoWeight * SelectedEvent.WLepton.IPWeight;
 }

 //if(PreWZPolarizationTree->EventNumber == 47357312){//yfu
 //  cout<<47357312<<endl;
 //  cout<<SelectedEvent.ZLepton1.mediumIDWeight<<"  "<<SelectedEvent.ZLepton1.ZTightIsoWeight<<"  "<<SelectedEvent.ZLepton1.IPWeight<<endl;
 //  cout<<SelectedEvent.ZLepton2.mediumIDWeight<<"  "<<SelectedEvent.ZLepton2.ZTightIsoWeight<<"  "<<SelectedEvent.ZLepton2.IPWeight<<endl;
 //  cout<<SelectedEvent.WLepton.tightIDWeight<<"  "<<SelectedEvent.WLepton.WTightIsoWeight<<"  "<<SelectedEvent.WLepton.recoWeight<<endl;
 //}

 passNuPt = (SelectedEvent.WNeutrino.P4.Pt() > 25);

/* if(PreWZPolarizationTree->EventNumber == 35183){
   cout<<"MCEventWeight: "<<PreWZPolarizationTree->MCEventWeight<<endl;
   cout<<"PileupWeight: "<<PreWZPolarizationTree->MCPileupWeight<<endl;
   cout<<"JetWeight: "<<PreWZPolarizationTree->JetWeight<<endl;
   cout<<endl;
   cout<<"ZLepton1:"<<endl;
   cout<<"Flavor: "<<SelectedEvent.ZLepton1.pdgID<<" mediumIDWeight: "<<SelectedEvent.ZLepton1.mediumIDWeight<<" ZTightIsoWeight: "<<SelectedEvent.ZLepton1.ZTightIsoWeight<<" recoWeight: "<<SelectedEvent.ZLepton1.recoWeight<<" IPWeight: "<<SelectedEvent.ZLepton1.IPWeight<<endl;
   cout<<endl;
   cout<<"ZLepton2:"<<endl;
   cout<<"Flavor: "<<SelectedEvent.ZLepton2.pdgID<<" mediumIDWeight: "<<SelectedEvent.ZLepton2.mediumIDWeight<<" ZTightIsoWeight: "<<SelectedEvent.ZLepton2.ZTightIsoWeight<<" recoWeight: "<<SelectedEvent.ZLepton2.recoWeight<<" IPWeight: "<<SelectedEvent.ZLepton2.IPWeight<<endl;
   cout<<endl;
   cout<<"WLepton:"<<endl;
   cout<<"Flavor: "<<SelectedEvent.WLepton.pdgID<<" tightIDWeight: "<<SelectedEvent.WLepton.tightIDWeight<<" WTightIsoWeight: "<<SelectedEvent.WLepton.WTightIsoWeight<<" recoWeight: "<<SelectedEvent.WLepton.recoWeight<<" IPWeight: "<<SelectedEvent.WLepton.IPWeight<<endl;
   cout<<endl;
   cout<<"TotalWeight: "<<PreWZPolarizationTree->MCEventWeight * PreWZPolarizationTree->MCPileupWeight * PreWZPolarizationTree->JetWeight * SelectedEvent.Lep1WeightZ * SelectedEvent.Lep2WeightZ * SelectedEvent.Lep3WeightW<<endl;
 }
*/

}

void loopWZPolarization::FillZLepton1CutFlow()
{
 if(SelectedEvent.ZLepton1.pdgID == 11){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "all", 1, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass SFOS", 1, isNominal);
   if(!SelectedEvent.ZLepton1.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass baseline", 1, isNominal);
   if(!SelectedEvent.ZLepton1.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass IPID", 1, isNominal);
   if(!SelectedEvent.ZLepton1.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass mediumID", 1, isNominal);
   if(!SelectedEvent.ZLepton1.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass ZTightIso", 1, isNominal);

   if(!SelectedEvent.ZLepton1.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass tightID", 1, isNominal);
   if(!SelectedEvent.ZLepton1.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass WTightIso", 1, isNominal);

 }
 if(SelectedEvent.ZLepton1.pdgID == 13){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "all", 1, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass SFOS", 1, isNominal);
   if(!SelectedEvent.ZLepton1.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass baseline", 1, isNominal);
   if(!SelectedEvent.ZLepton1.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass IPID", 1, isNominal);
   if(!SelectedEvent.ZLepton1.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass mediumID", 1, isNominal);
   if(!SelectedEvent.ZLepton1.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass ZTightIso", 1, isNominal);

   if(!SelectedEvent.ZLepton1.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass tightID", 1, isNominal);
   if(!SelectedEvent.ZLepton1.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass WTightIso", 1, isNominal);

 }

}

void loopWZPolarization::FillZLepton2CutFlow()
{
 if(SelectedEvent.ZLepton2.pdgID == 11){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "all", 1, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass SFOS", 1, isNominal);
   if(!SelectedEvent.ZLepton2.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass baseline", 1, isNominal);
   if(!SelectedEvent.ZLepton2.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass IPID", 1, isNominal);
   if(!SelectedEvent.ZLepton2.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass mediumID", 1, isNominal);
   if(!SelectedEvent.ZLepton2.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass ZTightIso", 1, isNominal);

   if(!SelectedEvent.ZLepton2.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass tightID", 1, isNominal);
   if(!SelectedEvent.ZLepton2.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass WTightIso", 1, isNominal);
 
 }
 if(SelectedEvent.ZLepton2.pdgID == 13){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "all", 1, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass SFOS", 1, isNominal);
   if(!SelectedEvent.ZLepton2.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass baseline", 1, isNominal);
   if(!SelectedEvent.ZLepton2.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass IPID", 1, isNominal);
   if(!SelectedEvent.ZLepton2.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass mediumID", 1, isNominal);
   if(!SelectedEvent.ZLepton2.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass ZTightIso", 1, isNominal);

   if(!SelectedEvent.ZLepton2.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass tightID", 1, isNominal);
   if(!SelectedEvent.ZLepton2.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass WTightIso", 1, isNominal);
 }
}

void loopWZPolarization::FillWLeptonCutFlow()
{
 if(SelectedEvent.WLepton.pdgID == 11){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "all", 1, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass SFOS", 1, isNominal);
   if(!SelectedEvent.WLepton.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass baseline", 1, isNominal);
   if(!SelectedEvent.WLepton.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass IPID", 1, isNominal);

   if(!SelectedEvent.WLepton.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass mediumID", 1, isNominal);
   if(!SelectedEvent.WLepton.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass ZTightIso", 1, isNominal);

   if(!(SelectedEvent.WLepton.P4.Pt() > 20)) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass W lepton pt > 20", 1, isNominal);

   if(!SelectedEvent.WLepton.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass tightID", 1, isNominal);
   if(!SelectedEvent.WLepton.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_CutFlow, WZPolarizationTree->Electron_CutNameMap, "pass WTightIso", 1, isNominal);
 }
 if(SelectedEvent.WLepton.pdgID == 13){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "all", 1, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass SFOS", 1, isNominal);
   if(!SelectedEvent.WLepton.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass baseline", 1, isNominal);
   if(!SelectedEvent.WLepton.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass IPID", 1, isNominal);

   if(!SelectedEvent.WLepton.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass mediumID", 1, isNominal);
   if(!SelectedEvent.WLepton.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass ZTightIso", 1, isNominal);

   if(!(SelectedEvent.WLepton.P4.Pt() > 20)) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass W lepton pt > 20", 1, isNominal);

   if(!SelectedEvent.WLepton.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass tightID", 1, isNominal);
   if(!SelectedEvent.WLepton.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_CutFlow, WZPolarizationTree->Muon_CutNameMap, "pass WTightIso", 1, isNominal);
 }
}

void loopWZPolarization::FillCutFlow()
{
 if(!passSFOS) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass SFOS", 1, isNominal);

 if(!(SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton2.IPID && SelectedEvent.WLepton.IPID)) return;
 if(!(SelectedEvent.passThreeBaseline)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass d0Sig + LooseIso", 1, isNominal);

 if(!(SelectedEvent.WLepton.P4.Pt() > 20)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass W lepton pt > 20", 1, isNominal);

 if(!(SelectedEvent.ZLepton1.mediumID && SelectedEvent.ZLepton2.mediumID && SelectedEvent.WLepton.tightID)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass tight id", 1, isNominal);

 //if(!(SelectedEvent.ZLepton1.ZTightIso && SelectedEvent.ZLepton2.ZTightIso && SelectedEvent.WLepton.ZTightIso)) return;
 //if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass ZTight isolation", 1, isNominal);

 if(!(SelectedEvent.ZLepton1.ZTightIso && SelectedEvent.ZLepton2.ZTightIso && SelectedEvent.WLepton.WTightIso)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass WTight isolation", 1, isNominal);

// if(!(SelectedEvent.ZLepton1.ZTightIso && SelectedEvent.ZLepton2.ZTightIso && SelectedEvent.WLepton.ZTightIso)) return;
// if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass ZTight isolation", 1, isNominal);

// if(!(SelectedEvent.ZLepton1.FCLooseIso && SelectedEvent.ZLepton2.FCLooseIso && SelectedEvent.WLepton.FCLooseIso)) return;
// if(!(SelectedEvent.passTTT)) return;
// if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass TTT", 1, isNominal);

 if(!PassTrig) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass trigger", 1, isNominal);

 if(!passLeadingLepPt) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass leading lepton pt", 1, isNominal);

 if(!passZZVeto) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass ZZVeto", 1, isNominal);

 if(!passMassWindow4) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass Mass Window", 1, isNominal);

 if(!(SelectedEvent.Mt_W > 30)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass Mt_W", 1, isNominal);

 if(!SelectedEvent.passDeltaR) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass DeltaR", 1, isNominal);

 if(!passHardWZInclusive) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass WZInclusive", 1, isNominal);

 if(!SelectedEvent.passTTT) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass TTT", 1, isNominal);

 if(!(SelectedEvent.Lep3Ambiguity <= 0)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass Ambiguity", 1, isNominal);

 if(SelectedEvent.Pt_Z < 200) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "ZPt < 200GeV", 1, isNominal);

 if(SelectedEvent.Pt_WZ > 70) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "Pt_WZ > 70GeV", 1, isNominal);

// EventNumber.insert(PreWZPolarizationTree->EventNumber);
}

void loopWZPolarization::FillZLepton1WeightedCutFlow()
{
 double weight = SelectedEvent.Lep1WeightZ;

 if(SelectedEvent.ZLepton1.pdgID == 11){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "all", weight, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass SFOS", weight, isNominal);
   if(!SelectedEvent.ZLepton1.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass baseline", weight, isNominal);
   if(!SelectedEvent.ZLepton1.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass IPID", weight, isNominal);
   if(!SelectedEvent.ZLepton1.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass mediumID", weight, isNominal);
   if(!SelectedEvent.ZLepton1.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass ZTightIso", weight, isNominal);

   if(!SelectedEvent.ZLepton1.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass tightID", weight, isNominal);
   if(!SelectedEvent.ZLepton1.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass WTightIso", weight, isNominal);

 }
 if(SelectedEvent.ZLepton1.pdgID == 13){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "all", weight, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass SFOS", weight, isNominal);
   if(!SelectedEvent.ZLepton1.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass baseline", weight, isNominal);
   if(!SelectedEvent.ZLepton1.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass IPID", weight, isNominal);
   if(!SelectedEvent.ZLepton1.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass mediumID", weight, isNominal);
   if(!SelectedEvent.ZLepton1.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass ZTightIso", weight, isNominal);

   if(!SelectedEvent.ZLepton1.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass tightID", weight, isNominal);
   if(!SelectedEvent.ZLepton1.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass WTightIso", weight, isNominal);

 }
}

void loopWZPolarization::FillZLepton2WeightedCutFlow()
{
 double weight = SelectedEvent.Lep2WeightZ;

 if(SelectedEvent.ZLepton2.pdgID == 11){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "all", weight, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass SFOS", weight, isNominal);
   if(!SelectedEvent.ZLepton2.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass baseline", weight, isNominal);
   if(!SelectedEvent.ZLepton2.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass IPID", weight, isNominal);
   if(!SelectedEvent.ZLepton2.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass mediumID", weight, isNominal);
   if(!SelectedEvent.ZLepton2.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass ZTightIso", weight, isNominal);

   if(!SelectedEvent.ZLepton2.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass tightID", weight, isNominal);
   if(!SelectedEvent.ZLepton2.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass WTightIso", weight, isNominal);
 
 }
 if(SelectedEvent.ZLepton2.pdgID == 13){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "all", weight, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass SFOS", weight, isNominal);
   if(!SelectedEvent.ZLepton2.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass baseline", weight, isNominal);
   if(!SelectedEvent.ZLepton2.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass IPID", weight, isNominal);
   if(!SelectedEvent.ZLepton2.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass mediumID", weight, isNominal);
   if(!SelectedEvent.ZLepton2.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass ZTightIso", weight, isNominal);

   if(!SelectedEvent.ZLepton2.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass tightID", weight, isNominal);
   if(!SelectedEvent.ZLepton2.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass WTightIso", weight, isNominal);
 }
}

void loopWZPolarization::FillWLeptonWeightedCutFlow()
{
 double weight = SelectedEvent.Lep3WeightW;

 if(SelectedEvent.WLepton.pdgID == 11){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "all", weight, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass SFOS", weight, isNominal);
   if(!SelectedEvent.WLepton.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass baseline", weight, isNominal);
   if(!SelectedEvent.WLepton.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass IPID", weight, isNominal);

   if(!SelectedEvent.WLepton.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass mediumID", weight, isNominal);
   if(!SelectedEvent.WLepton.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass ZTightIso", weight, isNominal);

   if(!(SelectedEvent.WLepton.P4.Pt() > 20)) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass W lepton pt > 20", weight, isNominal);

   if(!SelectedEvent.WLepton.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass tightID", weight, isNominal);
   if(!SelectedEvent.WLepton.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Electron_WeightedCutFlow, WZPolarizationTree->Electron_WeightedCutNameMap, "pass WTightIso", weight, isNominal);
 }
 if(SelectedEvent.WLepton.pdgID == 13){
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "all", weight, isNominal);
   if(!passSFOS) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass SFOS", weight, isNominal);
   if(!SelectedEvent.WLepton.isBaseline) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass baseline", weight, isNominal);
   if(!SelectedEvent.WLepton.IPID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass IPID", weight, isNominal);

   if(!SelectedEvent.WLepton.mediumID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass mediumID", weight, isNominal);
   if(!SelectedEvent.WLepton.ZTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass ZTightIso", weight, isNominal);

   if(!(SelectedEvent.WLepton.P4.Pt() > 20)) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass W lepton pt > 20", weight, isNominal);

   if(!SelectedEvent.WLepton.tightID) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass tightID", weight, isNominal);
   if(!SelectedEvent.WLepton.WTightIso) return;
   WZPolarizationTree->updateCutFlow(WZPolarizationTree->Muon_WeightedCutFlow, WZPolarizationTree->Muon_WeightedCutNameMap, "pass WTightIso", weight, isNominal);
 }
}

void loopWZPolarization::FillWeightedCutFlow()
{
 double weight = SelectedEvent.TotalWeightNoKFactor;

 if(!passSFOS) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass SFOS", weight, isNominal);

 if(!(SelectedEvent.ZLepton1.IPID && SelectedEvent.ZLepton2.IPID && SelectedEvent.WLepton.IPID)) return;
 if(!(SelectedEvent.passThreeBaseline)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass d0Sig + LooseIso", weight, isNominal);

 if(!(SelectedEvent.WLepton.P4.Pt() > 20)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass W lepton pt > 20", weight, isNominal);

 if(!(SelectedEvent.ZLepton1.mediumID && SelectedEvent.ZLepton2.mediumID && SelectedEvent.WLepton.tightID)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass tight id", weight, isNominal);

 //if(!(SelectedEvent.ZLepton1.ZTightIso && SelectedEvent.ZLepton2.ZTightIso && SelectedEvent.WLepton.ZTightIso)) return;
 //if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass ZTight isolation", weight, isNominal);

 if(!(SelectedEvent.ZLepton1.ZTightIso && SelectedEvent.ZLepton2.ZTightIso && SelectedEvent.WLepton.WTightIso)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass WTight isolation", weight, isNominal);

// if(!(SelectedEvent.ZLepton1.ZTightIso && SelectedEvent.ZLepton2.ZTightIso && SelectedEvent.WLepton.ZTightIso)) return;
// if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass ZTight isolation", weight, isNominal);

// if(!(SelectedEvent.ZLepton1.FCLooseIso && SelectedEvent.ZLepton2.FCLooseIso && SelectedEvent.WLepton.FCLooseIso)) return;
// if(!(SelectedEvent.passTTT)) return;
// if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass TTT", weight, isNominal);

 if(!PassTrig) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass trigger", weight, isNominal);

 if(!passLeadingLepPt) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass leading lepton pt", weight, isNominal);

 if(!passZZVeto) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass ZZVeto", weight, isNominal);

 if(!passMassWindow4) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass Mass Window", weight, isNominal);

 if(!(SelectedEvent.Mt_W > 30)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass Mt_W", weight, isNominal);

 if(!SelectedEvent.passDeltaR) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass DeltaR", weight, isNominal);

 if(!passHardWZInclusive) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "pass WZInclusive", weight, isNominal);

 if(!(SelectedEvent.Lep3Ambiguity <= 0)) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_CutFlow, WZPolarizationTree->Event_CutNameMap, "pass Ambiguity", weight, isNominal);

 if(SelectedEvent.Pt_Z < 200) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "ZPt < 200GeV", weight, isNominal);

 if(SelectedEvent.Pt_WZ > 70) return;
 if(JustGenerateTree) WZPolarizationTree->updateCutFlow(WZPolarizationTree->Event_WeightedCutFlow, WZPolarizationTree->Event_WeightedCutNameMap, "Pt_WZ > 70GeV", weight, isNominal);
}

bool loopWZPolarization::PassZZControlRegion(Lepton Lepton1, Lepton Lepton2, Lepton Lepton3, TLorentzVector Neutrino, TString Flavor)
{

 return true;
}

#endif
