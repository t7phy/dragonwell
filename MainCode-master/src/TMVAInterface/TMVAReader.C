#include "TMVAInterface/TMVAReader.h"

TMVAReader::TMVAReader()
{

}

void TMVAReader::InputTree(TString FileName, TString TreeName)
{
 FileMap[FileName] = new TFile(FileName);
 TreeMap[make_pair(FileName, TreeName)] = (TTree *)FileMap[FileName]->Get(TreeName);
}

void TMVAReader::Initialize(TString ComponentName)
{
#ifdef USE_TMVA
 readerMap[ComponentName] = new TMVA::Reader("Color:!Silent");
#endif
}

void TMVAReader::BookMVA(TString ComponentName, TString MethodName, TString FileName)
{
#ifdef USE_TMVA
 readerMap[ComponentName]->BookMVA(MethodName, FileName);

 MethodMap[ComponentName] = MethodName;
#endif
}

void TMVAReader::AddVariable(TString Name)
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

 ValueMap[Name] = -999.0;
 ContentMap[Name] = -999.0;

 for(auto iter = readerMap.begin(); iter != readerMap.end(); iter++){
   iter->second->AddVariable(Name, &ValueMap[Name]);
 }
#endif
}

void TMVAReader::DefineHist(TString ComponentName, int nbin, double left, double right)
{
 HistMap[ComponentName] = new TH1D(ComponentName + "_BDTScore", ComponentName + "_BDTScore", nbin, left, right);
}

void TMVAReader::LoopTrees(TString ComponentName, vector<pair<TString, TString>> FileNames)
{
#ifdef USE_TMVA
 for(int iFile = 0; iFile < FileNames.size(); iFile++){
   int NEvents = TreeMap[FileNames.at(iFile)]->GetEntries();

   for(auto iter = ContentMap.begin(); iter != ContentMap.end(); iter++){
     TreeMap[FileNames.at(iFile)]->SetBranchAddress(iter->first, &(iter->second));
   }

   for(int iEvent = 0; iEvent < NEvents; iEvent++){
     TreeMap[FileNames.at(iFile)]->GetEntry(iEvent);

     for(auto iter = ContentMap.begin(); iter != ContentMap.end(); iter++){
       ValueMap[iter->first] = (Float_t)iter->second;
     }

     double BDT = readerMap[ComponentName]->EvaluateMVA(MethodMap[ComponentName]);
     HistMap[ComponentName]->Fill(BDT, 1.0);
   }
 }
#endif
}

TH1D* TMVAReader::RetrieveHist(TString ComponentName)
{
 return HistMap[ComponentName];
}

double TMVAReader::EvaluateMVA(TString ComponentName)
{
 double Value = 0.0;
#ifdef USE_TMVA
 Value = readerMap[ComponentName]->EvaluateMVA(MethodMap[ComponentName]);
#endif

 return Value;
}

