#include <iostream>
#include <fstream>
#include <RootCommon.h>
#include "Tools/Tools.h"

using namespace std;

int main(int argc, char** argv)
{
 ifstream infile;
  infile.open("data.list", ios::in);

 TString RootName;
 vector<TString> RootNames;

 while(infile>>RootName){
   RootNames.push_back(RootName);
 }

 TFile* file;
 TTree* tree;

 TBranch* b_runNumber;

 Long64_t runNumber;
 int Year;
 map<pair<int, int>, double> LumiMap;

 for(int i = 0; i < RootNames.size(); i++){
   if(RootNames.at(i).Contains("data15") || RootNames.at(i).Contains("data16") || RootNames.at(i).Contains("data17") || RootNames.at(i).Contains("data18")){
     file = new TFile(RootNames.at(i));
     tree = (TTree *)file->Get("metaTree");
     tree->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
     if(RootNames.at(i).Contains("data15") || RootNames.at(i).Contains("data16")) Year = 1516;
     if(RootNames.at(i).Contains("data17")) Year = 17;
     if(RootNames.at(i).Contains("data18")) Year = 18;
     tree->GetEntry(0);

     pair<int, int> Pair;
     Pair = make_pair(Year, runNumber);
     double Lumi = GetRunLuminosity(runNumber);
     LumiMap[Pair] = Lumi;
     delete file;
   }
 }

 double Lumi1516 = 0.0;
 double Lumi17 = 0.0;
 double Lumi18 = 0.0;

 for(map<pair<int, int>, double>::iterator iter = LumiMap.begin(); iter != LumiMap.end(); iter++){
   cout<<"Year: "<<(iter->first).first<<" runNumber: "<<(iter->first).second<<" Lumi: "<<iter->second<<endl;
   if((iter->first).first == 1516) Lumi1516 += iter->second;
   if((iter->first).first == 17) Lumi17 += iter->second;
   if((iter->first).first == 18) Lumi18 += iter->second;
 }

 cout<<endl;
 cout<<"Luminosity 1516: "<<Lumi1516<<endl;
 cout<<"Luminosity 17  : "<<Lumi17<<endl;
 cout<<"Luminosity 18  : "<<Lumi18<<endl;

 return 1;
}
