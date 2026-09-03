#include "TMVAInterface/TMVAInterface.h"

TMVAInterface::TMVAInterface()
{
#ifdef USE_TMVA
 TMVA::Tools::Instance();

 TMVA::Config::VariablePlotting myPlotting = TMVA::gConfig().GetVariablePlotting();
 myPlotting.fMaxNumOfAllowedVariablesForScatterPlots = 5;

#endif
}

void TMVAInterface::OutputFile(const char* name)
{
 isOpenOutput = true;

 output = new TFile(name, "RECREATE");
}

void TMVAInterface::DefineFactory(TString Name, TString Args)
{
#ifdef USE_TMVA
 if(!isOpenOutput){
   cout<<"ERROR! Please open the output file first."<<endl;
   return;
 }

 isOpenFactory = true;

 factory = new TMVA::Factory(Name, output, Args);

 dataloader = new TMVA::DataLoader("dataset");
#endif
}

void TMVAInterface::AddTree(TString FileName, TString TreeName, TString ComponentName, double weight)
{
#ifdef USE_TMVA
 if(!isOpenFactory){
   cout<<"ERROR! Please open the factory first."<<endl;
   return;
 }

 FileMap[FileName] = new TFile(FileName);
 TreeMap[make_pair(FileName, TreeName)] = (TTree *)FileMap[FileName]->Get(TreeName);

 dataloader->AddTree(TreeMap[make_pair(FileName, TreeName)], ComponentName, weight);
#endif
}

void TMVAInterface::AddVariable(TString Name)
{
#ifdef USE_TMVA
 if(TreeMap.size() == 0){
   cout<<"ERROR! Please call AddTree() first."<<endl;
   return;
 }

 map<pair<TString, TString>, TTree *>::iterator iter = TreeMap.begin();
 TTree* tree = iter->second;

 bool isInTree = false;
 for(int i = 0; i < tree->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree->GetListOfBranches()->At(i);
   TString name = branch->GetName();
   if(name == Name){
     isInTree = true;
     break;
   }
 }

 if(!isInTree){
   cout<<"ERROR! The variable name is not in the tree."<<endl;
   return;
 }

 dataloader->AddVariable(Name);

#endif
}

void TMVAInterface::PrepareTrainingAndTestTree(TCut cut, TString Args)
{
#ifdef USE_TMVA
 dataloader->PrepareTrainingAndTestTree(cut, Args);
#endif
}

#ifdef USE_TMVA
void TMVAInterface::BookMethod(TMVA::Types::EMVA method, TString title, TString Args)
{
 factory->BookMethod(dataloader, method, title, Args);
}
#endif

void TMVAInterface::Evaluate()
{
#ifdef USE_TMVA
 factory->TrainAllMethods();
 factory->TestAllMethods();
 factory->EvaluateAllMethods();

 output->Close();
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ////////////////
 //  Tutorial  //
 ////////////////

void TMVAInterface::FirstRegression()
{
#ifdef USE_TMVA
 TMVA::Tools myTool = TMVA::Tools::Instance();

 TMVA::Config::VariablePlotting myPlotting = TMVA::gConfig().GetVariablePlotting();
 myPlotting.fMaxNumOfAllowedVariablesForScatterPlots = 5;

 TString outfileName = "TMVA_Tutorial_reg_1.root";
 TFile *output = new TFile(outfileName, "RECREATE");

 //Create the factory object. Later you can choose the methods whose performance you'd like to investigate. The factory will then run the
 //performance analysis for you.

 //The first argument is the base of the name of all the weightfiles in the directory weight/

 //The second argument is the output file for the training results
 TMVA::Factory* factory = new TMVA::Factory("TMVARegression", output, "!V:!Silent:Color:!DrawProgressBar:Transformations=D,G:AnalysisType=Regression");

 TString trfile = "example_data/SM_ttbar.root";
 TFile *data = new TFile(trfile);
 TString trname = "tree";
 TTree* tree = (TTree *)data->Get(trname);

 //Define the input variables that shall be used for the MVA training
 TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");

 for(int i = 0; i < tree->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree->GetListOfBranches()->At(i);
   TString name = branch->GetName();
   if(!name.Contains("mtt")){
     dataloader->AddVariable(name);
   }
 }

 //Add the variable carrying the regression target
 dataloader->AddTarget("mtt_truth");

 //Register the regression tree
 dataloader->AddRegressionTree(tree, 1.0);

 //Apply some cuts Set the number of events for training, and use all remaining events in the trees after training for testing

 //If no numbers of events are given, half of the events in the tree are used for training, and the other half for testing
 TCut mycut("");
 dataloader->PrepareTrainingAndTestTree(mycut, "SplitMode=random:!V");

 //dataloader->PrepareTrainingAndTestTree(TCut(""), "nTrain_Regression=10000:SplitMode=Random:NormMode=NumEvents:!V");

 //Book MVA methods BDT
 factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT",
          "!H:!V:NTrees=100:MinNodeSize=1.0%:BoostType=AdaBoostR2:SeparationType=RegressionVariance:nCuts=20:PruneMethod=CostComplexity:PruneStrength=30");

 factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTG",
          "!H:!V:NTrees=2000::BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3:MaxDepth=4");

 //Neural network (MLP)
 //factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP",
 //         "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=20000:HiddenLayers=N+20:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15:!UseRegulator");

 //Run TMVA
 factory->TrainAllMethods();
 factory->TestAllMethods();
 factory->EvaluateAllMethods();

 output->Close();
#endif
}

void TMVAInterface::FirstRegressionApp()
{
#ifdef USE_TMVA
 //Setup TMVA
 TMVA::Tools myTool = TMVA::Tools::Instance();

 //Reader
 TMVA::Reader* reader = new TMVA::Reader("Color:!Silent");

 TString trfile = "example_data/SM_ttbar.root";
 TFile *data = new TFile(trfile);
 TTree *tree = (TTree *)data->Get("tree");

 //Set input variables
 map<TString, Float_t> branches;
 for(int i = 0; i < tree->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches[branchName] = -999.0;
   tree->SetBranchAddress(branchName, &branches[branchName]);
   if(!branchName.Contains("mtt")){
     reader->AddVariable(branchName, &branches[branchName]);
   }
 }

 TString methodName1 = "BDT";
 TString weightfile1 = "dataset/weights/TMVARegression_BDT.weights.xml";
 reader->BookMVA(methodName1, weightfile1);

 TString methodName2 = "BDTG";
 TString weightfile2 = "dataset/weights/TMVARegression_BDTG.weights.xml";
 reader->BookMVA(methodName2, weightfile2);

 int nevents = tree->GetEntries();

 TFile* writefile = new TFile("save.root", "RECREATE");
 writefile->cd();

 TH1D* h1 = new TH1D("mtt_truth_SM", "mtt_truth_SM", 200, 0, 2000);
 h1->Sumw2();
 TH1D* h2 = new TH1D("mtt_reco_SM", "mtt_reco_SM", 200, 0, 2000);
 h2->Sumw2();
 TH1D* h3 = new TH1D("BDT_SM", "BDT_SM", 200, 0, 2000);
 h3->Sumw2();
 TH1D* h4 = new TH1D("BDTG_SM", "BDTG_SM", 200, 0, 2000);
 h4->Sumw2();

 for(int iEvent = 0; iEvent < nevents; iEvent++){
   tree->GetEntry(iEvent);

   Float_t mtt_truth = branches["mtt_truth"];
   Float_t mtt_reco = branches["mtt_reco"];
   Float_t BDT = reader->EvaluateRegression(methodName1)[0];
   Float_t BDTG = reader->EvaluateRegression(methodName2)[0];

   h1->Fill(mtt_truth, 1.0);
   h2->Fill(mtt_reco, 1.0);
   h3->Fill(BDT, 1.0);
   h4->Fill(BDTG, 1.0);
 }

 writefile->Write();
 writefile->Close();
#endif
}

void TMVAInterface::FirstRegressionTest()
{
#ifdef USE_TMVA
 TString outfileName = "TMVA_Tutorial_reg_1.root";
 TFile* tfin = new TFile(outfileName, "READ");

 TTree *tree_train = (TTree *)tfin->Get("dataset/TrainTree");
 TTree *tree_test = (TTree *)tfin->Get("dataset/TestTree");

 map<TString, Float_t> branches;
 for(int i = 0; i < tree_train->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree_train->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches[branchName] = -999.0;
   tree_train->SetBranchAddress(branchName, &branches[branchName]);
 }

 for(int i = 0; i < tree_test->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree_test->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches[branchName] = -999.0;
   tree_test->SetBranchAddress(branchName, &branches[branchName]);
 }


 TFile* writefile = new TFile("saveTest.root", "RECREATE");
 writefile->cd();

 TH1D* h1 = new TH1D("mtt_truth_train", "mtt_truth_train", 200, 0, 2000);
 h1->Sumw2();
 TH1D* h2 = new TH1D("mtt_reco_train", "mtt_reco_train", 200, 0, 2000);
 h2->Sumw2();
 TH1D* h3 = new TH1D("BDT_train", "BDT_train", 200, 0, 2000);
 h3->Sumw2();
 TH1D* h4 = new TH1D("BDTG_train", "BDTG_train", 200, 0, 2000);
 h4->Sumw2();

 TH1D* h5 = new TH1D("mtt_truth_test", "mtt_truth_test", 200, 0, 2000);
 h5->Sumw2();
 TH1D* h6 = new TH1D("mtt_reco_test", "mtt_reco_test", 200, 0, 2000);
 h6->Sumw2();
 TH1D* h7 = new TH1D("BDT_test", "BDT_test", 200, 0, 2000);
 h7->Sumw2();
 TH1D* h8 = new TH1D("BDTG_test", "BDTG_test", 200, 0, 2000);
 h8->Sumw2();

 int nevents_train = tree_train->GetEntries();
 int nevents_test = tree_test->GetEntries();

 for(int iEvent = 0; iEvent < nevents_train; iEvent++){
   tree_train->GetEntry(iEvent);

   Float_t mtt_truth = branches["mtt_truth"];
   Float_t mtt_reco = branches["mtt_reco"];
   Float_t BDT = branches["BDT"];
   Float_t BDTG = branches["BDTG"];

   h1->Fill(mtt_truth, 1.0);
   h2->Fill(mtt_reco, 1.0);
   h3->Fill(BDT, 1.0);
   h4->Fill(BDTG, 1.0);
 }

 for(int iEvent = 0; iEvent < nevents_test; iEvent++){
   tree_test->GetEntry(iEvent);

   Float_t mtt_truth = branches["mtt_truth"];
   Float_t mtt_reco = branches["mtt_reco"];
   Float_t BDT = branches["BDT"];
   Float_t BDTG = branches["BDTG"];

   h5->Fill(mtt_truth, 1.0);
   h6->Fill(mtt_reco, 1.0);
   h7->Fill(BDT, 1.0);
   h8->Fill(BDTG, 1.0);
 }

 writefile->Write();
 writefile->Close();
#endif
}

void TMVAInterface::FirstClassification()
{
#ifdef USE_TMVA
 TMVA::Tools myTool = TMVA::Tools::Instance();

 TMVA::Config::VariablePlotting myPlotting = TMVA::gConfig().GetVariablePlotting();
 myPlotting.fMaxNumOfAllowedVariablesForScatterPlots = 5;

 TString outfileName = "TMVA_Tutorial_cla_1.root";
 TFile *output = new TFile(outfileName, "RECREATE");

 //Create the factory object. Later you can choose the methods whose performance you'd like to investigate. The factory is the only TMVA object you
 //have to interact with

 //The first argument is the base of the name of all the weightfiles in the directory weight/ The second argument is the output file for the training results
 TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", output, "!V:!Silent:Color:!DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

 TString trfile_B = "example_data/SM_ttbar.root";
 TString trfile_S = "example_data/Zp1TeV_ttbar.root";

 TFile *data_B = new TFile(trfile_B);
 TFile *data_S = new TFile(trfile_S);

 TString trname = "tree";

 TTree *tree_B = (TTree *)data_B->Get(trname);
 TTree *tree_S = (TTree *)data_S->Get(trname);

 TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");

 for(int i = 0; i < tree_S->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree_S->GetListOfBranches()->At(i);
   TString name = branch->GetName();
   if(!name.Contains("mtt_truth") && !name.Contains("weight") && !name.Contains("nlep") && !name.Contains("njets")){
     dataloader->AddVariable(name);
   }
 }

 //Add Signal and background trees
 dataloader->AddSignalTree(tree_S, 1.0);
 dataloader->AddBackgroundTree(tree_B, 1.0);

 //Tell the dataloader how to use the training and testing events

 //If no numbers of events are given, half of the events in the tree are used for training, and the other half for testing:
 //dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );

 //To also specify the number of testing events, use:
 //dataloader->PrepareTrainingAndTestTree( mycut, "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
 dataloader->PrepareTrainingAndTestTree(TCut(""), "nTrain_Signal=10000:nTrain_Background=10000:SplitMode=Random:NormMode=NumEvents:!V");

 //Generate model
 factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT", 
          "!H:!V:NTrees=100:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20");

 factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTG", 
          "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2");

 factory->TrainAllMethods();
 factory->TestAllMethods();
 factory->EvaluateAllMethods();

 output->Close();
#endif
}

void TMVAInterface::FirstClassificationApp()
{
#ifdef USE_TMVA
 //Setup TMVA
 TMVA::Tools myTool = TMVA::Tools::Instance();

 TMVA::Reader* reader = new TMVA::Reader("Color:!Silent");
 TMVA::Reader* reader_S = new TMVA::Reader("Color:!Silent");
 TMVA::Reader* reader_B = new TMVA::Reader("Color:!Silent");

 //Load data an unknown sample
 TString trfile = "example_data/Zp2TeV_ttbar.root";
 TFile *data = new TFile(trfile);
 TTree *tree = (TTree *)data->Get("tree");

 //Known signal
 TString trfile_S = "example_data/Zp1TeV_ttbar.root";
 TFile *data_S = new TFile(trfile_S);
 TTree *tree_S = (TTree *)data_S->Get("tree");

 //Known background
 TString trfile_B = "example_data/SM_ttbar.root";
 TFile *data_B = new TFile(trfile_B);
 TTree *tree_B = (TTree *)data_B->Get("tree");

 //Set input variables
 map<TString, Float_t> branches;
 for(int i = 0; i < tree->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches[branchName] = -999.0;
   tree->SetBranchAddress(branchName, &branches[branchName]);
   if(!branchName.Contains("mtt_truth") && !branchName.Contains("weight") && !branchName.Contains("nlep") && !branchName.Contains("njets")){
     reader->AddVariable(branchName, &branches[branchName]);
   }
 }

 map<TString, Float_t> branches_S;
 for(int i = 0; i < tree_S->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree_S->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches_S[branchName] = -999.0;
   tree_S->SetBranchAddress(branchName, &branches_S[branchName]);
   if(!branchName.Contains("mtt_truth") && !branchName.Contains("weight") && !branchName.Contains("nlep") && !branchName.Contains("njets")){
     reader_S->AddVariable(branchName, &branches_S[branchName]);
   }
 }

 map<TString, Float_t> branches_B;
 for(int i = 0; i < tree_B->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree_B->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches_B[branchName] = -999.0;
   tree_B->SetBranchAddress(branchName, &branches_B[branchName]);
   if(!branchName.Contains("mtt_truth") && !branchName.Contains("weight") && !branchName.Contains("nlep") && !branchName.Contains("njets")){
     reader_B->AddVariable(branchName, &branches_B[branchName]);
   }
 }

 TString methodName1 = "BDT";
 TString weightfile1 = "dataset/weights/TMVAClassification_BDT.weights.xml";
 reader->BookMVA(methodName1, weightfile1);
 reader_S->BookMVA(methodName1, weightfile1);
 reader_B->BookMVA(methodName1, weightfile1);

 TString methodName2 = "BDTG";
 TString weightfile2 = "dataset/weights/TMVAClassification_BDTG.weights.xml";
 reader->BookMVA(methodName2, weightfile2);
 reader_S->BookMVA(methodName2, weightfile2);
 reader_B->BookMVA(methodName2, weightfile2);

 TFile* writefile = new TFile("saveClassification.root", "RECREATE");
 writefile->cd();

 int nevents = 0;
 nevents = tree_S->GetEntries();

 TH1D *h1 = new TH1D("BDT_S", "BDT_S", 20, -1, 1);
 h1->Sumw2();
 TH1D *h2 = new TH1D("BDTG_S", "BDTG_S", 20, -1, 1);
 h2->Sumw2();

 for(int iEvent = 0; iEvent < nevents; iEvent++){
   tree_S->GetEntry(iEvent);

   double BDT = reader_S->EvaluateMVA(methodName1);
   double BDTG = reader_S->EvaluateMVA(methodName2);

   h1->Fill(BDT, 1.0);
   h2->Fill(BDTG, 1.0);
 }

 nevents = tree_B->GetEntries();

 TH1D *h3 = new TH1D("BDT_B", "BDT_B", 20, -1, 1);
 h3->Sumw2();
 TH1D *h4 = new TH1D("BDTG_B", "BDTG_B", 20, -1, 1);
 h4->Sumw2();

 for(int iEvent = 0; iEvent < nevents; iEvent++){
   tree_B->GetEntry(iEvent);

   double BDT = reader_B->EvaluateMVA(methodName1);
   double BDTG = reader_B->EvaluateMVA(methodName2);

   h3->Fill(BDT, 1.0);
   h4->Fill(BDTG, 1.0);
 }

 nevents = tree->GetEntries();

 TH1D *h5 = new TH1D("BDT_N", "BDT_N", 20, -1, 1);
 h5->Sumw2();
 TH1D *h6 = new TH1D("BDTG_N", "BDTG_N", 20, -1, 1);
 h6->Sumw2();

 for(int iEvent = 0; iEvent < nevents; iEvent++){
   tree->GetEntry(iEvent);

   double BDT = reader->EvaluateMVA(methodName1);
   double BDTG = reader->EvaluateMVA(methodName2);

   h5->Fill(BDT, 1.0);
   h6->Fill(BDTG, 1.0);
 }

 writefile->Write();
 writefile->Close();
#endif
}

void TMVAInterface::FirstClassificationTest()
{
#ifdef USE_TMVA

#endif
}

void TMVAInterface::TrainingANN()
{
#ifdef USE_TMVA
 //Create a new TMVA factory
 TMVA::Tools::Instance();
 TString outfileName("TMVA.root");
 TFile* outputFile = TFile::Open(outfileName, "RECREATE");

 TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", outputFile,
                                            "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

 //Load data
 TString trfile = "example_data/Zp2TeV_ttbar.root";
 TFile *data = new TFile(trfile);
 TTree *tree = (TTree *)data->Get("tree");

 TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");

 //Set input variables
 map<TString, Float_t> branches;
 for(int i = 0; i < tree->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches[branchName] = -999.0;
   tree->SetBranchAddress(branchName, &branches[branchName]);
   if(!branchName.Contains("mtt_truth") && !branchName.Contains("weight") && !branchName.Contains("nlep") && !branchName.Contains("njets")){
     dataloader->AddVariable(branchName, 'F');
   }
 }

 //Set signal and background
 dataloader->AddSignalTree(tree, 1.0);
 dataloader->AddBackgroundTree(tree, 1.0);

 //Set cuts
 TCut mycuts = "";
 TCut mycutb = "";

 //Prepare training and test samples
 dataloader->PrepareTrainingAndTestTree(mycuts, mycutb,
                                     "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");

 //Book ANN method
 factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=500:HiddenLayers=N+5:TestRate=5");

 //Train, test and evaluate all methods
 factory->TrainAllMethods();
 factory->TestAllMethods();
 factory->EvaluateAllMethods();

 //Save the output
 outputFile->Close();

 delete factory;  
#endif
}

void TMVAInterface::TestANN()
{
#ifdef USE_TMVA
 //Create a new TMVA factory
 TMVA::Tools::Instance();
 TString outfileName("TMVA.root");
 TFile* outputFile = TFile::Open(outfileName, "RECREATE");

 TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", outputFile,
                                            "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");

 //Load data
 TString trfile = "example_data/Zp2TeV_ttbar.root";
 TFile *data = new TFile(trfile);
 TTree *tree = (TTree *)data->Get("tree");

 TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");

 //Set input variables
 map<TString, Float_t> branches;
 for(int i = 0; i < tree->GetListOfBranches()->GetEntries(); i++){
   TBranch* branch = (TBranch *)tree->GetListOfBranches()->At(i);
   TString branchName = branch->GetName();
   branches[branchName] = -999.0;
   tree->SetBranchAddress(branchName, &branches[branchName]);
   if(!branchName.Contains("mtt_truth") && !branchName.Contains("weight") && !branchName.Contains("nlep") && !branchName.Contains("njets")){
     dataloader->AddVariable(branchName, 'F');
   }
 }

 //Set signal and background
 dataloader->AddSignalTree(tree, 1.0);
 dataloader->AddBackgroundTree(tree, 1.0);

 //Set cuts
 TCut mycuts = "";
 TCut mycutb = "";

 //Prepare training and test samples
 dataloader->PrepareTrainingAndTestTree(mycuts, mycutb,
                                     "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");

 //Book ANN method
 factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=500:HiddenLayers=N+5:TestRate=5");

 //Train, test and evaluate all methods
 factory->TrainAllMethods();
 factory->TestAllMethods();
 factory->EvaluateAllMethods();

 //Save the output
 outputFile->Close();

 delete factory;
#endif
}

