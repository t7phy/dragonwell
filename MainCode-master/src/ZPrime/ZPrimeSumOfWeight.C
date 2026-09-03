#include "ZPrime/ZPrimeSumOfWeight.h"

ZPrimeSumOfWeight::ZPrimeSumOfWeight(TString FileList)
{
 ifstream infile;
  infile.open(FileList, ios::in);
 TString RootName;

 while(infile>>RootName){
   RootNames.push_back(RootName);
 }
}

void ZPrimeSumOfWeight::GetSumOfWeight()
{
 double SumOfWeight = 0.0;
 for(int ifile = 0; ifile < RootNames.size(); ifile++){
   rootfile = new TFile(RootNames.at(ifile));
   metaTree = (TTree *)rootfile->Get("sumWeights");
   metaTree->SetBranchAddress("totalEventsWeighted", &totalEventsWeighted, &b_totalEventsWeighted);
   metaTree->SetBranchAddress("dsid", &dsid, &b_dsid);

   metaTreeEntries = metaTree->GetEntries();
   if(metaTreeEntries != 0) metaTree->GetEntry(0);
   if(metaTreeEntries == 0) continue;

   int nchannel = dsid;
   int Year = GetYear(RootNames.at(ifile));

   pair<int, int> RootTypePair;
   RootTypePair = make_pair(nchannel, Year);
   if(SumOfWeightsMap.count(RootTypePair) == 0) SumOfWeightsMap[RootTypePair] = 0.0;

   for(int i = 0; i < metaTreeEntries; i++){
     metaTree->GetEntry(i);

     //cout<<get<0>(RootTypePair)<<"  "<<get<1>(RootTypePair)<<"  "<<totalEventsWeighted<<endl;
     SumOfWeightsMap[RootTypePair] = SumOfWeightsMap[RootTypePair] + totalEventsWeighted;
   }

   delete metaTree;
   delete rootfile;
 }

 for(auto iter = SumOfWeightsMap.begin(); iter != SumOfWeightsMap.end(); iter++){
   cout<<"DSID: "<<std::get<0>(iter->first)<<"  Year: "<<std::get<1>(iter->first)<<"  SumOfWeights = "<<iter->second<<endl;
 }
}

TString ZPrimeSumOfWeight::GetRootType(TString name)
{
 TString RootType;

 if(name.Contains("nominal_Data")){
   RootType = "Data";
 }
 else if(name.Contains("DrellYan") || name.Contains("Ztoee") || name.Contains("Ztomumu")){
   RootType = "DrellYan";
 }
 else if(name.Contains("PI_")){
   RootType = "PhotonInduced";
 }
 else if(name.Contains("TopQuark") || name.Contains("singleTop")){
   RootType = "TopQuark";
 }
 else if(name.Contains("Diboson")){
   RootType = "Diboson";
 }
 else if(name.Contains("Triboson")){
   RootType = "Triboson";
 }
 else if(name.Contains("ttV")){
   RootType = "ttV";
 }
 else if(name.Contains("ntuple_MM") || name.Contains("matrix_Data_all_Dimuon")){
   RootType = "Wjets_DD";
 }
 else if(name.Contains("Ztautau")){
   RootType = "Ztautau";
 }
 else if(name.Contains("Wjets_")){
   RootType = "Wjets";
 }

 return RootType;
}

int ZPrimeSumOfWeight::GetYear(TString RootName)
{
 int Year = 0;
 if(RootName.Contains("mc16a")) Year = 1516;
 else if(RootName.Contains("mc16d")) Year = 17;
 else if(RootName.Contains("mc16e")) Year = 18;
 else Year = 0;

 return Year;
}

