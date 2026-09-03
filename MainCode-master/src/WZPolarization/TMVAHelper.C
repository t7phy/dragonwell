#include "WZPolarization/TMVAHelper.h"

TMVAHelper::TMVAHelper()
{
#ifdef USE_TMVA
 reader = new TMVA::Reader( "Color" );
#endif
}

void TMVAHelper::BookMVA(TString FileName)
{
#ifdef USE_TMVA
 reader->BookMVA("TQFirstBDTG_PolBKG_mTW", FileName);
#endif
}

void TMVAHelper::InputTree(TreeForWZPolarization *WZPolarizationTree)
{
 this->WZPolarizationTree = WZPolarizationTree;
}

void TMVAHelper::CalVariable()
{
 TLorentzVector Lep1;
 TLorentzVector Lep2;
 TLorentzVector Lep3;
 TLorentzVector Nu;

 Lep1.SetPtEtaPhiM(WZPolarizationTree->Lep1Pt, WZPolarizationTree->Lep1Eta, WZPolarizationTree->Lep1Phi, 0);
 Lep2.SetPtEtaPhiM(WZPolarizationTree->Lep2Pt, WZPolarizationTree->Lep2Eta, WZPolarizationTree->Lep2Phi, 0);
 Lep3.SetPtEtaPhiM(WZPolarizationTree->Lep3Pt, WZPolarizationTree->Lep3Eta, WZPolarizationTree->Lep3Phi, 0);
 Nu.SetPxPyPzE(WZPolarizationTree->Mpx, WZPolarizationTree->Mpy, WZPolarizationTree->Mpz, sqrt(WZPolarizationTree->Met * WZPolarizationTree->Met + WZPolarizationTree->Mpz * WZPolarizationTree->Mpz));

 float ZRapidity = (Lep1 + Lep2).Rapidity();

 CosThetaVAbs = fabs(WZPolarizationTree->CosThetaV);

 logM_WZ = log10(WZPolarizationTree->M_WZ) < 3.0 ? log10(WZPolarizationTree->M_WZ) : 3.0;

 logM_Z = WZPolarizationTree->M_Z < 101.2 ? WZPolarizationTree->M_Z : 101.2;
 logM_Z = WZPolarizationTree->M_Z > 81.0 ? WZPolarizationTree->M_Z : 81.0;

 logMet = log10(WZPolarizationTree->Met) < 2.6 ? log10(WZPolarizationTree->Met) : 2.6;
 logMet = logMet < 1.4 ? logMet : 1.4;

 logMt_W = log10(WZPolarizationTree->Mt_W) < 2.4 ? log10(WZPolarizationTree->Mt_W) : 2.4;
 logMt_W = logMt_W < 1.5 ? logMt_W : 1.5;

 logMt_WZ = log10(WZPolarizationTree->Mt_WZ) < 3.0 ? log10(WZPolarizationTree->Mt_WZ) : 3.0;
 logMt_WZ = logMt_WZ > 2.2 ? logMt_WZ : 2.2;

 logPt_W = log10(WZPolarizationTree->Pt_W) < 2.7 ? log10(WZPolarizationTree->Pt_W) : 2.7;
 logPt_W = logPt_W > 0.3 ? logPt_W : 0.3;

 logPt_Z = log10(WZPolarizationTree->Pt_Z) < 3.0 ? log10(WZPolarizationTree->Pt_Z) : 3.0;
 logPt_Z = logPt_Z > 0.3 ? logPt_Z : 0.3;

 R21 = WZPolarizationTree->R21;

 logPt_WZ = log10(WZPolarizationTree->Pt_WZ) < 2.7 ? log10(WZPolarizationTree->Pt_WZ) : 2.7;
 logPt_WZ = logPt_WZ > 0.0 ? logPt_WZ : 0.0;

 M_Z = WZPolarizationTree->M_Z;

 ZRapidityAbs = fabs(ZRapidity);

 Lep1EtaAbs = fabs(WZPolarizationTree->Lep1Eta);
 Lep1PhiAbs = fabs(WZPolarizationTree->Lep1Phi);
 logLep1Pt = log10(WZPolarizationTree->Lep1Pt) < 2.8 ? log10(WZPolarizationTree->Lep1Pt) : 2.8;

 Lep2EtaAbs = fabs(WZPolarizationTree->Lep2Eta);
 Lep2PhiAbs = fabs(WZPolarizationTree->Lep2Phi);
 logLep2Pt = log10(WZPolarizationTree->Lep2Pt) < 2.5 ? log10(WZPolarizationTree->Lep2Pt) : 2.5;

 Lep3EtaAbs = fabs(WZPolarizationTree->Lep3Eta);
 Lep3PhiAbs = fabs(WZPolarizationTree->Lep3Phi);
 logLep3Pt = log10(WZPolarizationTree->Lep3Pt) < 2.6 ? log10(WZPolarizationTree->Lep3Pt) : 2.6;

 CosThetaLepWAbs = fabs(WZPolarizationTree->CosThetaLepW);
 CosThetaLepZAbs = fabs(WZPolarizationTree->CosThetaLepZ);

 DeltaPhi_LepW_Met_Abs = fabs(Lep3.DeltaPhi(Nu));
 DeltaPhiLepWLepZ_Abs = fabs(WZPolarizationTree->DeltaPhiLepWLepZ);
 DeltaPhiLepWLepZWZFrame_Abs = fabs(WZPolarizationTree->DeltaPhiLepWLepZWZFrame);
 DeltaPhi_Lep1_Lep2_Abs = fabs(Lep1.DeltaPhi(Lep2));

 DY_3Z_Abs = fabs(WZPolarizationTree->DY_3Z) < 3.2 ? fabs(WZPolarizationTree->DY_3Z) : 3.2;
 DY_WZ_Abs = fabs(WZPolarizationTree->DY_WZ) < 3.2 ? fabs(WZPolarizationTree->DY_WZ) : 3.2;
 DY_3N_Abs = fabs(WZPolarizationTree->DY_3N) < 3.2 ? fabs(WZPolarizationTree->DY_3N) : 3.2;

 logWLepPt = log10(WZPolarizationTree->WLepPt) < 2.5 ? log10(WZPolarizationTree->WLepPt) : 2.5;
 logZLeadingLepPt = log10(WZPolarizationTree->ZLeadingLepPt) < 2.6 ? log10(WZPolarizationTree->ZLeadingLepPt) : 2.6;
 logZSubleadingLepPt = log10(WZPolarizationTree->ZSubleadingLepPt) < 2.8 ? log10(WZPolarizationTree->ZSubleadingLepPt) : 2.8;
 logZSubleadingLepPt2p6 = log10(WZPolarizationTree->ZSubleadingLepPt) < 2.6 ? log10(WZPolarizationTree->ZSubleadingLepPt) : 2.6;

 TotalWeightNoKFactor = WZPolarizationTree->TotalWeightNoKFactor;

 passHardWZInclusive = WZPolarizationTree->passHardWZInclusive;

 EventNumber = WZPolarizationTree->EventNumber;
 Weight = 1.0;
}

void TMVAHelper::AddVariable()
{
#ifdef USE_TMVA
/* reader->AddVariable("CosThetaV:=abs(VV_COSTHETAW)", &CosThetaVAbs);
 reader->AddVariable("MET:=min(log10(met_P4.Pt()),2.6)", &logMet);
 reader->AddVariable("MTW:=min(log10(VV_MTW),2.4)", &logMt_W);
 reader->AddVariable("MtWZ:=max(min(log10(MtWZ),3),2.1)", &logMt_WZ);
 reader->AddVariable("PTW:=max(min(log10(WMin_PT),2.7),0.3)", &logPt_W);
 reader->AddVariable("PTZ:=max(min(log10(Z_PT),3),0.3)", &logPt_Z);
 reader->AddVariable("R21:=(Z_PT>WMin_PT)*(WMin_PT/Z_PT)+(WMin_PT>Z_PT)*(Z_PT/WMin_PT)", &R21);
 reader->AddVariable("WZPT:=min(max(log10(VV_WZPT),0),2.7)", &logPt_WZ);
 reader->AddVariable("WZY:=abs(WMinZ_Y)", &DY_WZ_Abs);
 reader->AddVariable("Wlep_Eta:=abs((Wlep_P4.Eta()))", &Lep3EtaAbs);
 reader->AddVariable("Wlep_PT:=min(log10(Wlep_P4.Pt()),2.6)", &logLep3Pt);
 reader->AddVariable("Z_M:=Z_P4.M()", &M_Z);
 reader->AddVariable("Z_Y:=abs(Z_P4.Rapidity())", &ZRapidityAbs);
 reader->AddVariable("Zlep1_Eta:=abs((Zlep1_P4.Eta()))", &Lep1EtaAbs);
 reader->AddVariable("Zlep1_PT:=min(log10(Zlep1_P4.Pt()),2.8)", &logLep1Pt);
 reader->AddVariable("Zlep2_Eta:=abs((Zlep2_P4.Eta()))", &Lep2EtaAbs);
 reader->AddVariable("Zlep2_PT:=min(log10(Zlep2_P4.Pt()),2.5)", &logLep2Pt);
 reader->AddVariable("costhetalepW:=abs(VV_cosWthetastarHel*Wlep_Charge)", &CosThetaLepWAbs);
 reader->AddVariable("costhetalepZ:=abs(VV_cosZthetastarHel)", &CosThetaLepZAbs);
 reader->AddVariable("dPhi_lW_MET:=abs((Wlep_P4.Phi()-met_P4.Phi()))", &DeltaPhi_LepW_Met_Abs);
 reader->AddVariable("dPhi_lW_lZsc:=abs((Zlep1_Charge==Wlep_Charge)*(Wlep_P4.Phi()-Zlep1_P4.Phi())+(Zlep2_Charge==Wlep_Charge)*(Wlep_P4.Phi()-Zlep2_P4.Phi()))", &DeltaPhiLepWLepZ_Abs);
 reader->AddVariable("dPhi_lZ1_lZ2:=abs((Zlep1_P4.Phi()-Zlep2_P4.Phi()))", &DeltaPhi_Lep1_Lep2_Abs);
 reader->AddVariable("dY_lW_Z:=min(abs((Wlep_P4.Rapidity()-Z_P4.Rapidity())),3.2)", &DY_3Z_Abs);

 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("Weight:=1", &Weight);
*/
/* reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddSpectator("CosThetaV:=VV_COSTHETAW", &CosThetaVAbs);
 reader->AddSpectator("TotalWeightNoKFactor:=Total1NoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);
 reader->AddSpectator("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddSpectator("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 reader->AddSpectator("DY_3N:=min(abs(DY_3N),3.2)", &DY_3N_Abs);
 reader->AddSpectator("DY_WZ:=min(abs(DY_WZ),3.2)", &DY_WZ_Abs);
 reader->AddSpectator("DeltaPhiLepWLepZ:=abs(DeltaPhiLepWLepZ)", &DeltaPhiLepWLepZ_Abs);
 reader->AddSpectator("DeltaPhiLepWLepZWZFrame:=abs(DeltaPhiLepWLepZWZFrame)", &DeltaPhiLepWLepZWZFrame_Abs);
 reader->AddSpectator("Lep1Eta:=abs(Lep1Eta)", &Lep1EtaAbs);
 reader->AddSpectator("Lep1Phi:=abs(Lep1Phi)", &Lep1PhiAbs);
 reader->AddSpectator("Lep1Pt:=min(log10(Lep1Pt),2.6)", &logLep1Pt);
 reader->AddSpectator("Lep2Eta:=abs(Lep2Eta)", &Lep2EtaAbs);
 reader->AddSpectator("Lep2Phi:=abs(Lep2Phi)", &Lep2PhiAbs);
 reader->AddSpectator("Lep2Pt:=min(log10(Lep2Pt),2.8)", &logLep2Pt);
 reader->AddSpectator("Lep3Eta:=abs(Lep3Eta)", &Lep3EtaAbs);
 reader->AddSpectator("Lep3Phi:=abs(Lep3Phi)", &Lep3PhiAbs);
 reader->AddSpectator("Lep3Pt:=min(log10(Lep3Pt),2.5)", &logLep3Pt);
 reader->AddSpectator("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddSpectator("M_Z:=max(min(M_Z,101.2),81.0)", &logM_Z);
 reader->AddSpectator("Met:=max(min(log10(Met),2.6),1.4)", &logMet);
 reader->AddSpectator("Mt_W:=max(min(log10(Mt_W),2.4),1.5)", &logMt_W);
 reader->AddSpectator("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
 reader->AddSpectator("R21:=(Z_PT>WMin_PT)*(WMin_PT/Z_PT)+(WMin_PT>Z_PT)*(Z_PT/WMin_PT)", &R21);

 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddVariable("DeltaPhiLepWLepZ:=abs(DeltaPhiLepWLepZ)", &DeltaPhiLepWLepZ_Abs);
 reader->AddVariable("DeltaPhiLepWLepZWZFrame:=abs(DeltaPhiLepWLepZWZFrame)", &DeltaPhiLepWLepZWZFrame_Abs);
 reader->AddVariable("Lep1Phi:=abs(Lep1Phi)", &Lep1PhiAbs);
 reader->AddVariable("Lep2Eta:=abs(Lep2Eta)", &Lep2EtaAbs);
 reader->AddVariable("Lep2Phi:=abs(Lep2Phi)", &Lep2PhiAbs);
 reader->AddVariable("Lep3Pt:=min(log10(Lep3Pt),2.5)", &logLep3Pt);
 reader->AddVariable("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddVariable("M_Z:=max(min(M_Z,101.2),81.0)", &logM_Z);
 reader->AddVariable("Mt_W:=max(min(log10(Mt_W),2.4),1.5)", &logMt_W);
 reader->AddVariable("R21:=(Z_PT>WMin_PT)*(WMin_PT/Z_PT)+(WMin_PT>Z_PT)*(Z_PT/WMin_PT)", &R21);
 reader->AddSpectator("CosThetaV:=VV_COSTHETAW", &CosThetaVAbs);
 reader->AddSpectator("TotalWeightNoKFactor:=Total1NoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);
 reader->AddSpectator("DY_WZ:=min(abs(DY_WZ),3.2)", &DY_WZ_Abs);
 reader->AddSpectator("Lep1Eta:=abs(Lep1Eta)", &Lep1EtaAbs);
 reader->AddSpectator("Lep1Pt:=min(log10(Lep1Pt),2.6)", &logLep1Pt);
 reader->AddSpectator("Lep2Pt:=min(log10(Lep2Pt),2.8)", &logLep2Pt);
 reader->AddSpectator("Lep3Eta:=abs(Lep3Eta)", &Lep3EtaAbs);
 reader->AddSpectator("Lep3Phi:=abs(Lep3Phi)", &Lep3PhiAbs);
 reader->AddSpectator("Met:=max(min(log10(Met),2.6),1.4)", &logMet);
 reader->AddSpectator("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
*/


 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddVariable("DY_WZ:=min(abs(DY_WZ),3.2)", &DY_WZ_Abs);
 reader->AddVariable("Pt_WZ:=min(max(log10(Pt_WZ),0),2.7)", &logPt_WZ);
 reader->AddVariable("R21:=R21", &R21);
 reader->AddVariable("WLepPt:=min(log10(WLepPt),2.5)", &logWLepPt);
 reader->AddVariable("ZSubleadingLepPt:=min(log10(ZSubleadingLepPt),2.8)", &logZSubleadingLepPt);

 reader->AddSpectator("CosThetaV:=CosThetaV", &CosThetaVAbs);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);
 reader->AddSpectator("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 reader->AddSpectator("DY_3N:=min(abs(DY_3N),3.2)", &DY_3N_Abs);
 reader->AddSpectator("DeltaPhiLepWLepZ:=abs(DeltaPhiLepWLepZ)", &DeltaPhiLepWLepZ_Abs);
 reader->AddSpectator("DeltaPhiLepWLepZWZFrame:=abs(DeltaPhiLepWLepZWZFrame)", &DeltaPhiLepWLepZWZFrame_Abs);
 reader->AddSpectator("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddSpectator("Met:=max(min(log10(Met),2.6),1.4)", &logMet);
 reader->AddSpectator("Mt_W:=max(min(log10(Mt_W),2.4),1.5)", &logMt_W);
 reader->AddSpectator("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
 reader->AddSpectator("Pt_W:=max(min(log10(Pt_W),2.7),0.3)", &logPt_W);
 reader->AddSpectator("Pt_Z:=max(min(log10(Pt_Z),3),0.3)", &logPt_Z);
 reader->AddSpectator("ZLeadingLepPt:=min(log10(ZLeadingLepPt),2.6)", &logZLeadingLepPt);

#endif
}

double TMVAHelper::EvaluateMVA()
{
 double Value = 0.0;

#ifdef USE_TMVA
 Value = reader->EvaluateMVA("TQFirstBDTG_PolBKG_mTW");
#endif

 return Value;

}

void TMVAHelper::AddVariableSR()
{
#ifdef USE_TMVA
/* reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("DY_3N:=min(abs(DY_3N),3.2)", &DY_3N_Abs);
 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddVariable("Mt_W:=max(min(log10(Mt_W),2.4),1.5)", &logMt_W);
 reader->AddVariable("Pt_WZ:=min(max(log10(Pt_WZ),0),2.7)", &logPt_WZ);
 reader->AddVariable("R21:=R21", &R21);
 reader->AddVariable("WLepPt:=min(log10(WLepPt),2.5)", &logWLepPt);
 reader->AddVariable("ZSubleadingLepPt:=min(log10(ZSubleadingLepPt),2.8)", &logZSubleadingLepPt);

 reader->AddSpectator("CosThetaV:=abs(CosThetaV)", &CosThetaVAbs);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);
 reader->AddSpectator("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 reader->AddSpectator("DY_WZ:=min(abs(DY_WZ),3.2)", &DY_WZ_Abs);
 reader->AddSpectator("DeltaPhiLepWLepZ:=abs(DeltaPhiLepWLepZ)", &DeltaPhiLepWLepZ_Abs);
 reader->AddSpectator("DeltaPhiLepWLepZWZFrame:=abs(DeltaPhiLepWLepZWZFrame)", &DeltaPhiLepWLepZWZFrame_Abs);
 reader->AddSpectator("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddSpectator("Met:=max(min(log10(Met),2.6),1.4)", &logMet);
 reader->AddSpectator("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
 reader->AddSpectator("Pt_W:=max(min(log10(Pt_W),2.7),0.3)", &logPt_W);
 reader->AddSpectator("Pt_Z:=max(min(log10(Pt_Z),3),0.3)", &logPt_Z);
 reader->AddSpectator("ZLeadingLepPt:=min(log10(ZLeadingLepPt),2.6)", &logZLeadingLepPt);
*/

 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 //reader->AddVariable("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 reader->AddVariable("DY_3N:=min(abs(DY_3N),3.2)", &DY_3N_Abs);
 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddVariable("DY_WZ:=min(abs(DY_WZ),3.2)", &DY_WZ_Abs);
 reader->AddVariable("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddVariable("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
 reader->AddVariable("Pt_WZ:=min(max(log10(Pt_WZ),0),2.7)", &logPt_WZ);
 reader->AddVariable("Pt_Z:=max(min(log10(Pt_Z),3),0.3)", &logPt_Z);
 reader->AddVariable("R21:=R21", &R21);
 reader->AddVariable("WLepPt:=min(log10(WLepPt),2.5)", &logWLepPt);
 reader->AddVariable("ZSubleadingLepPt:=min(log10(ZSubleadingLepPt),2.8)", &logZSubleadingLepPt);

 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);

#endif
}

void TMVAHelper::AddVariableSR_NoPtV()
{
#ifdef USE_TMVA
 // No PtV 
 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddVariable("Met:=max(min(log10(Met),2.6),1.4)", &logMet);
 reader->AddVariable("Pt_WZ:=min(max(log10(Pt_WZ),0),2.7)", &logPt_WZ);
 reader->AddVariable("WLepPt:=min(log10(WLepPt),2.5)", &logWLepPt);
 reader->AddVariable("ZSubleadingLepPt:=min(log10(ZSubleadingLepPt),2.6)", &logZSubleadingLepPt2p6);
 
 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);
#endif
}

void TMVAHelper::AddVariableSR_OnlyDec()
{
#ifdef USE_TMVA
 // Only Dec
 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 
 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);

#endif
}

void TMVAHelper::AddVariableSR100()
{
#ifdef USE_TMVA
 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 //reader->AddVariable("DY_3N:=min(abs(DY_3N),3.2)", &DY_3N_Abs);
 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 //reader->AddVariable("DY_WZ:=min(abs(DY_WZ),3.2)", &DY_3Z_Abs);
 //reader->AddVariable("M_Z:=max(min(M_Z,101.2),81.0)", &logM_Z);
 reader->AddVariable("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddVariable("Met:=max(min(log10(Met),2.6),1.4)", &logMet); 
 reader->AddVariable("Mt_W:=max(min(log10(Mt_W),2.4),1.5)", &logMt_W);
 reader->AddVariable("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
 reader->AddVariable("Pt_WZ:=min(max(log10(Pt_WZ),0),2.7)", &logPt_WZ);
 reader->AddVariable("WLepPt:=min(log10(WLepPt),2.5)", &logWLepPt);
 reader->AddVariable("ZLeadingLepPt:=min(log10(ZLeadingLepPt),2.6)", &logZLeadingLepPt);
 reader->AddVariable("ZSubleadingLepPt:=min(log10(ZSubleadingLepPt),2.8)", &logZSubleadingLepPt);  

 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);

#endif
}

void TMVAHelper::AddVariableSR100_NoPtV()
 {
#ifdef USE_TMVA 
 // No PtV
 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);
 reader->AddVariable("DY_3Z:=min(abs(DY_3Z),3.2)", &DY_3Z_Abs);
 reader->AddVariable("M_WZ:=min(log10(M_WZ),3.0)", &logM_WZ);
 reader->AddVariable("Met:=max(min(log10(Met),2.6),1.4)", &logMet);
 reader->AddVariable("Mt_W:=max(min(log10(Mt_W),2.4),1.5)", &logMt_W);
 reader->AddVariable("Mt_WZ:=max(min(log10(Mt_WZ),3),2.2)", &logMt_WZ);
 reader->AddVariable("Pt_WZ:=min(max(log10(Pt_WZ),0),2.7)", &logPt_WZ);
 reader->AddVariable("WLepPt:=min(log10(WLepPt),2.5)", &logWLepPt);
 reader->AddVariable("ZLeadingLepPt:=min(log10(ZLeadingLepPt),2.6)", &logZLeadingLepPt);
 reader->AddVariable("ZSubleadingLepPt:=min(log10(ZSubleadingLepPt),2.8)", &logZSubleadingLepPt);

 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);
#endif
}

void TMVAHelper::AddVariableSR100_OnlyDec()
{
#ifdef USE_TMVA
 // Only Dec
 reader->AddVariable("CosThetaLepW:=abs(CosThetaLepW)", &CosThetaLepWAbs);
 reader->AddVariable("CosThetaLepZ:=abs(CosThetaLepZ)", &CosThetaLepZAbs);

 reader->AddSpectator("EventNumber:=EventNumber", &EventNumber);
 reader->AddSpectator("TotalWeightNoKFactor:=TotalWeightNoKFactor", &TotalWeightNoKFactor);
 reader->AddSpectator("passHardWZInclusive:=passHardWZInclusive", &passHardWZInclusive);

#endif
}


