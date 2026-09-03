#include "QBH/QBHFakeRate.h"

void QBHFakeRate::GetFakeFactor(vector<TString> RootNames)
{
 this->RootNames = RootNames;

 TString passTrig = "HLT_singleLep*HLT_singleJet*lepton_singleleptrigMatched";
 TString isEl = "(lepton1_isEl==1)";
 TString isMu = "(lepton1_isEl==0)";

 TString FakeCR = "(dphiLepJet>2.8)*(detaLepJet<3.25)*(metFinalTrkSignificance<3.5)";
 TString RealCR = "(dphiLepJet>2.8)*(detaLepJet<3.25)*(metFinalTrkSignificance>3.5)";

 TString passTight = "lepton1_isSig*lepton1_isIso*(n_signal_lep>0)";

 TString MCWeight = "mcEventWeight*beamSpotWeight*weight_gen*weight_lumi*weight_norm*weight_singleleptonTrigSF*weight_pileup*weight_lepton";
 TString MCWeightLoose = "mcEventWeight*beamSpotWeight*weight_gen*weight_lumi*weight_norm*weight_singleleptonTrigSF*weight_pileup";

 vector<TString> ElFakeTight_weight;
 vector<TString> ElFakeLoose_weight;
 vector<TString> MuFakeTight_weight;
 vector<TString> MuFakeLoose_weight;
 vector<TString> ElRealTight_weight;
 vector<TString> ElRealLoose_weight;
 vector<TString> MuRealTight_weight;
 vector<TString> MuRealLoose_weight;

 vector<TString> InputRootNames;

 for(int i = 0; i < RootNames.size(); i++){

   if(RootNames.at(i).Contains("Run3_data")){
     ElFakeTight_weight.push_back(passTrig + "*" + FakeCR + "*" + isEl + "*" + passTight);
     ElFakeLoose_weight.push_back(passTrig + "*" + FakeCR + "*" + isEl);
     MuFakeTight_weight.push_back(passTrig + "*" + FakeCR + "*" + isMu + "*" + passTight);
     MuFakeLoose_weight.push_back(passTrig + "*" + FakeCR + "*" + isMu);
     ElRealTight_weight.push_back("0");
     ElRealLoose_weight.push_back("0");
     MuRealTight_weight.push_back("0");
     MuRealLoose_weight.push_back("0");

     InputRootNames.push_back(RootNames.at(i));
   }
   else if(RootNames.at(i).Contains("Run3_singletop")
        || RootNames.at(i).Contains("Run3_ttbar")
        || RootNames.at(i).Contains("Run3_ttV")
        || RootNames.at(i).Contains("Run3_Wenu")
        || RootNames.at(i).Contains("Run3_Wmnu")
        || RootNames.at(i).Contains("Run3_Wtnu")
        || RootNames.at(i).Contains("Run3_Zee")
        || RootNames.at(i).Contains("Run3_Zmm")
        || RootNames.at(i).Contains("Run3_Ztt")
        || RootNames.at(i).Contains("Run3_diboson")){
     ElFakeTight_weight.push_back(MCWeight + "*(-1.0)" + "*" + passTrig + "*" + FakeCR + "*" + isEl + "*" + passTight);
     ElFakeLoose_weight.push_back(MCWeightLoose + "*(-1.0)" + "*" + passTrig + "*" + FakeCR + "*" + isEl); 
     MuFakeTight_weight.push_back(MCWeight + "*(-1.0)" + "*" + passTrig + "*" + FakeCR + "*" + isMu + "*" + passTight);
     MuFakeLoose_weight.push_back(MCWeightLoose + "*(-1.0)" + "*" + passTrig + "*" + FakeCR + "*" + isMu); 
     ElRealTight_weight.push_back(MCWeight + "*" + passTrig + "*" + RealCR + "*" + isEl + "*" + passTight);
     ElRealLoose_weight.push_back(MCWeightLoose + "*" + passTrig + "*" + RealCR + "*" + isEl); 
     MuRealTight_weight.push_back(MCWeight + "*" + passTrig + "*" + RealCR + "*" + isMu + "*" + passTight);
     MuRealLoose_weight.push_back(MCWeightLoose + "*" + passTrig + "*" + RealCR + "*" + isMu);

     InputRootNames.push_back(RootNames.at(i));
   }
 }

 ElFakeTightJob = new TreeDrawThread();
 ElFakeLooseJob = new TreeDrawThread();
 MuFakeTightJob = new TreeDrawThread();
 MuFakeLooseJob = new TreeDrawThread();
 ElRealTightJob = new TreeDrawThread();
 ElRealLooseJob = new TreeDrawThread();
 MuRealTightJob = new TreeDrawThread();
 MuRealLooseJob = new TreeDrawThread();

 ElFakeTightJob->InputFile(InputRootNames, "LJAlgo/nominal");
 ElFakeLooseJob->InputFile(InputRootNames, "LJAlgo/nominal");
 MuFakeTightJob->InputFile(InputRootNames, "LJAlgo/nominal");
 MuFakeLooseJob->InputFile(InputRootNames, "LJAlgo/nominal");
 ElRealTightJob->InputFile(InputRootNames, "LJAlgo/nominal");
 ElRealLooseJob->InputFile(InputRootNames, "LJAlgo/nominal");
 MuRealTightJob->InputFile(InputRootNames, "LJAlgo/nominal");
 MuRealLooseJob->InputFile(InputRootNames, "LJAlgo/nominal");

 ElFakeTightJob->DefineHist("ElFakeTight", "ElFakeTight", 2, 130, 500, 2, 0.0, 2.5);
 ElFakeLooseJob->DefineHist("ElFakeLoose", "ElFakeLoose", 2, 130, 500, 2, 0.0, 2.5);
 MuFakeTightJob->DefineHist("MuFakeTight", "MuFakeTight", 1, 130, 500, 1, 0.0, 2.5);
 MuFakeLooseJob->DefineHist("MuFakeLoose", "MuFakeLoose", 1, 130, 500, 1, 0.0, 2.5);
 ElRealTightJob->DefineHist("ElRealTight", "ElRealTight", 2, 130, 500, 2, 0.0, 2.5);
 ElRealLooseJob->DefineHist("ElRealLoose", "ElRealLoose", 2, 130, 500, 2, 0.0, 2.5);
 MuRealTightJob->DefineHist("MuRealTight", "MuRealTight", 1, 130, 500, 1, 0.0, 2.5);
 MuRealLooseJob->DefineHist("MuRealLoose", "MuRealLoose", 1, 130, 500, 1, 0.0, 2.5);

 ElFakeTightJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 ElFakeLooseJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 MuFakeTightJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 MuFakeLooseJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 ElRealTightJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 ElRealLooseJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 MuRealTightJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");
 MuRealLooseJob->InputVariableName("lepton1_pt", "fabs(lepton1_eta)");

 ElFakeTightJob->InputWeightInfo(ElFakeTight_weight);
 ElFakeLooseJob->InputWeightInfo(ElFakeLoose_weight);
 MuFakeTightJob->InputWeightInfo(MuFakeTight_weight);
 MuFakeLooseJob->InputWeightInfo(MuFakeLoose_weight);
 ElRealTightJob->InputWeightInfo(ElRealTight_weight);
 ElRealLooseJob->InputWeightInfo(ElRealLoose_weight);
 MuRealTightJob->InputWeightInfo(MuRealTight_weight);
 MuRealLooseJob->InputWeightInfo(MuRealLoose_weight);

 myLog<<LOG_INFO<<"submit Electron Fake Tight:"<<endl;
 ElFakeTightJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Electron Fake Loose:"<<endl;
 ElFakeLooseJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Muon Fake Tight:"<<endl;
 MuFakeTightJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Muon Fake Loose:"<<endl;
 MuFakeLooseJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Electron Real Tight:"<<endl;
 ElRealTightJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Electron Real Loose:"<<endl;
 ElRealLooseJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Muon Real Tight:"<<endl;
 MuRealTightJob->SubmitTreeDrawJobs();
 myLog<<LOG_INFO<<"submit Muon Real Loose:"<<endl;
 MuRealLooseJob->SubmitTreeDrawJobs();

 ElFakeTightJob->WaitTreeDrawJobs();
 ElFakeLooseJob->WaitTreeDrawJobs();
 MuFakeTightJob->WaitTreeDrawJobs();
 MuFakeLooseJob->WaitTreeDrawJobs();
 ElRealTightJob->WaitTreeDrawJobs();
 ElRealLooseJob->WaitTreeDrawJobs();
 MuRealTightJob->WaitTreeDrawJobs();
 MuRealLooseJob->WaitTreeDrawJobs();

 ElFakeTight = ElFakeTightJob->FinalHist2D;
 ElFakeLoose = ElFakeLooseJob->FinalHist2D;
 MuFakeTight = MuFakeTightJob->FinalHist2D;
 MuFakeLoose = MuFakeLooseJob->FinalHist2D;
 ElRealTight = ElRealTightJob->FinalHist2D;
 ElRealLoose = ElRealLooseJob->FinalHist2D;
 MuRealTight = MuRealTightJob->FinalHist2D;
 MuRealLoose = MuRealLooseJob->FinalHist2D;


 ElFakeEff = (TH2D *)ElFakeTight->Clone("ElFakeEff");
 ElFakeEff->Divide(ElFakeLoose);

 MuFakeEff = (TH2D *)MuFakeTight->Clone("MuFakeEff");
 MuFakeEff->Divide(MuFakeLoose);

 ElRealEff = (TH2D *)ElRealTight->Clone("ElRealEff");
 ElRealEff->Divide(ElRealLoose);

 MuRealEff = (TH2D *)MuRealTight->Clone("MuRealEff");
 MuRealEff->Divide(MuRealLoose);

 myLog<<LOG_INFO<<"Electron Fake Tight:"<<endl;
 for(int ibinx = 1; ibinx <= ElFakeTight->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= ElFakeTight->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<ElFakeTight->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ElFakeTight->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Electron Fake Loose:"<<endl;
 for(int ibinx = 1; ibinx <= ElFakeLoose->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= ElFakeLoose->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<ElFakeLoose->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ElFakeLoose->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Muon Fake Tight:"<<endl;
 for(int ibinx = 1; ibinx <= MuFakeTight->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= MuFakeTight->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<MuFakeTight->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<MuFakeTight->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Muon Fake Loose:"<<endl;
 for(int ibinx = 1; ibinx <= MuFakeLoose->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= MuFakeLoose->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<MuFakeLoose->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<MuFakeLoose->GetBinError(ibinx, ibiny)<<"  ";
   } 
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Electron Real Tight:"<<endl;
 for(int ibinx = 1; ibinx <= ElRealTight->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= ElRealTight->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<ElRealTight->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ElRealTight->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Electron Real Loose:"<<endl;
 for(int ibinx = 1; ibinx <= ElRealLoose->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= ElRealLoose->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<ElRealLoose->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ElRealLoose->GetBinError(ibinx, ibiny)<<"  ";
   } 
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Muon Real Tight:"<<endl;
 for(int ibinx = 1; ibinx <= MuRealTight->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= MuRealTight->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<MuRealTight->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<MuRealTight->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Muon Real Loose:"<<endl;
 for(int ibinx = 1; ibinx <= MuRealLoose->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= MuRealLoose->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<MuRealLoose->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<MuRealLoose->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Electron Fake efficiency:"<<endl;
 for(int ibinx = 1; ibinx <= ElFakeEff->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= ElFakeEff->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<ElFakeEff->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ElFakeEff->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Muon Fake efficiency:"<<endl;
 for(int ibinx = 1; ibinx <= MuFakeEff->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= MuFakeEff->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<MuFakeEff->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<MuFakeEff->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Electron Real efficiency:"<<endl;
 for(int ibinx = 1; ibinx <= ElRealEff->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= ElRealEff->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<ElRealEff->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<ElRealEff->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

 myLog<<LOG_INFO<<"Muon Real efficiency:"<<endl;
 for(int ibinx = 1; ibinx <= MuRealEff->GetNbinsX(); ibinx++){
   myLog<<LOG_INFO;
   for(int ibiny = 1; ibiny <= MuRealEff->GetNbinsY(); ibiny++){
     myLog<<fixed<<setprecision(3)<<MuRealEff->GetBinContent(ibinx, ibiny);
     myLog<<" +- ";
     myLog<<fixed<<setprecision(3)<<MuRealEff->GetBinError(ibinx, ibiny)<<"  ";
   }
   myLog<<endl;
 }

}
