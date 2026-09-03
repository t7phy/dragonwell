#include "Tools/SumOfWeightHelper.h"
#include "Tools/Tools.h"

SumOfWeightHelper::SumOfWeightHelper(const char* FileList)
{
 ifstream infile;
  infile.open(FileList, ios::in);
 TString RootName;

 while(infile>>RootName){
   RootNames.push_back(RootName);
 }
}

void SumOfWeightHelper::GetSumOfWeight()
{
/* Channels.push_back(345705);
 Channels.push_back(345706);
 Channels.push_back(361106);
 Channels.push_back(361107);
 Channels.push_back(361108);
 Channels.push_back(361292);
 Channels.push_back(361293);
 Channels.push_back(364242);
 Channels.push_back(364243);
 Channels.push_back(364244);
 Channels.push_back(364245);
 Channels.push_back(364246);
 Channels.push_back(364247);
 Channels.push_back(364248);
 Channels.push_back(364249);
 Channels.push_back(364250);
 Channels.push_back(364253);
 Channels.push_back(364254);
 Channels.push_back(364283);
 Channels.push_back(364284);
 Channels.push_back(364739);
 Channels.push_back(364740);
 Channels.push_back(364741);
 Channels.push_back(364742);
 Channels.push_back(366140);
 Channels.push_back(366141);
 Channels.push_back(366142);
 Channels.push_back(366143);
 Channels.push_back(366144);
 Channels.push_back(366145);
 Channels.push_back(366146);
 Channels.push_back(366147);
 Channels.push_back(366148);
 Channels.push_back(366149);
 Channels.push_back(366150);
 Channels.push_back(366151);
 Channels.push_back(366152);
 Channels.push_back(366153);
 Channels.push_back(366154);
 Channels.push_back(410155);
 Channels.push_back(410218);
 Channels.push_back(410219);
 Channels.push_back(410470);
 Channels.push_back(410550);
 Channels.push_back(410644);
 Channels.push_back(410645);
 Channels.push_back(410646);
 Channels.push_back(410647);
 Channels.push_back(410648);
 Channels.push_back(410649);
 Channels.push_back(410658);
 Channels.push_back(410659);
 Channels.push_back(500290);
 Channels.push_back(500291);
 Channels.push_back(500292);
 Channels.push_back(500293);
 Channels.push_back(500294);
 Channels.push_back(500295);
 Channels.push_back(500296);
 Channels.push_back(500297);
 Channels.push_back(501793);
 Channels.push_back(501794);
 Channels.push_back(501795);
 Channels.push_back(501796);
 Channels.push_back(501797);
 Channels.push_back(501798);
 Channels.push_back(501799);
 Channels.push_back(501800);
 Years.push_back(1516);
 Years.push_back(17);
 Years.push_back(18);
*/
 double SumOfWeight = 0.0;
 for(int ifile = 0; ifile < RootNames.size(); ifile++){
   int nchannel = GetRootType(RootNames.at(ifile));
   int Year = GetYear(RootNames.at(ifile));

   rootfile = new TFile(RootNames.at(ifile));
   metaTree = (TTree *)rootfile->Get("metaTree");
   metaTree->SetBranchAddress("totalWeightedEntries", &totalWeightedEntries, &b_totalWeightedEntries);
   metaTreeEntries = metaTree->GetEntries();

   pair<int, int> RootTypePair;
   RootTypePair = make_pair(nchannel, Year);
   if(SumOfWeightsMap.count(RootTypePair) == 0) SumOfWeightsMap[RootTypePair] = 0.0;

   for(int i = 0; i < metaTreeEntries; i++){
     metaTree->GetEntry(i);
     SumOfWeightsMap[RootTypePair] = SumOfWeightsMap[RootTypePair] + totalWeightedEntries;
   }

   //Luminosity
   if(RootNames.at(ifile).Contains("data15") || RootNames.at(ifile).Contains("data16") || RootNames.at(ifile).Contains("data17") || RootNames.at(ifile).Contains("data18")){
     int Year;
     metaTree->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
     if(RootNames.at(ifile).Contains("data15") || RootNames.at(ifile).Contains("data16")) Year = 1516;
     if(RootNames.at(ifile).Contains("data17")) Year = 17;
     if(RootNames.at(ifile).Contains("data18")) Year = 18;

     for(int i = 0; i < metaTree->GetEntries(); i++){
       metaTree->GetEntry(i);
       pair<int, int> Pair;
       Pair = make_pair(Year, runNumber);
       double Lumi = GetRunLuminosity(runNumber);
       LumiMap[Pair] = Lumi;
     }
   }

   delete metaTree;
   delete rootfile;
 }

 for(map<pair<int, int>, double>::iterator iter = LumiMap.begin(); iter != LumiMap.end(); iter++){
   if((iter->first).first == 1516) Lumi1516 += iter->second;
   if((iter->first).first == 17) Lumi17 += iter->second;
   if((iter->first).first == 18) Lumi18 += iter->second;
 }

 cout<<endl;
 cout<<"Luminosity 1516: "<<Lumi1516<<endl;
 cout<<"Luminosity 17  : "<<Lumi17<<endl;
 cout<<"Luminosity 18  : "<<Lumi18<<endl;

// for(auto iter = SumOfWeightsMap.begin(); iter != SumOfWeightsMap.end(); iter++){
//   cout<<"MC Type: "<<iter->first.first<<" Year: "<<iter->first.second<<" SumOfWeight: "<<iter->second<<endl;
// }

}

int SumOfWeightHelper::GetRootType(TString RootName)
{
 int nchannel;

 if(RootName.Contains("364253_")){
   nchannel = 364253;
 }
 else if(RootName.Contains("364991_")){
   nchannel = 364991;
 }
 else if(RootName.Contains("364992_")){
   nchannel = 364992;
 }
 else if(RootName.Contains("364993_")){
   nchannel = 364993;
 }
 else if(RootName.Contains("364994_")){
   nchannel = 364994;
 }
 else if(RootName.Contains("500290_")){
   nchannel = 500290;
 }
 else if(RootName.Contains("500291_")){
   nchannel = 500291;
 }
 else if(RootName.Contains("500292_")){
   nchannel = 500292;
 }
 else if(RootName.Contains("500293_")){
   nchannel = 500293;
 }
 else if(RootName.Contains("500294_")){
   nchannel = 500294;
 }
 else if(RootName.Contains("500295_")){
   nchannel = 500295;
 }
 else if(RootName.Contains("500296_")){
   nchannel = 500296;
 }
 else if(RootName.Contains("500297_")){
   nchannel = 500297;
 }
 else if(RootName.Contains("501793_")){
   nchannel = 501793;
 }
 else if(RootName.Contains("501794_")){
   nchannel = 501794;
 }
 else if(RootName.Contains("501795_")){
   nchannel = 501795;
 }
 else if(RootName.Contains("501796_")){
   nchannel = 501796;
 }
 else if(RootName.Contains("501797_")){
   nchannel = 501797;
 }
 else if(RootName.Contains("501798_")){
   nchannel = 501798;
 }
 else if(RootName.Contains("501799_")){
   nchannel = 501799;
 }
 else if(RootName.Contains("501800_")){
   nchannel = 501800;
 }
 else if(RootName.Contains("507019_")){
   nchannel = 507019;
 }
 else if(RootName.Contains("507020_")){
   nchannel = 507020;
 }
 else if(RootName.Contains("507021_")){
   nchannel = 507021;
 }
 else if(RootName.Contains("507022_")){
   nchannel = 507022;
 }
 else if(RootName.Contains("507023_")){
   nchannel = 507023;
 }
 else if(RootName.Contains("507024_")){
   nchannel = 507024;
 }
 else if(RootName.Contains("507025_")){
   nchannel = 507025;
 }
 else if(RootName.Contains("507026_")){
   nchannel = 507026;
 }
 else if(RootName.Contains("507027_")){
   nchannel = 507027;
 }
 else if(RootName.Contains("507028_")){
   nchannel = 507028;
 }
 else if(RootName.Contains("507029_")){
   nchannel = 507029;
 }
 else if(RootName.Contains("507030_")){
   nchannel = 507030;
 }
 else if(RootName.Contains("507031_")){
   nchannel = 507031;
 }
 else if(RootName.Contains("507032_")){
   nchannel = 507032;
 }
 else if(RootName.Contains("507033_")){
   nchannel = 507033;
 }
 else if(RootName.Contains("507034_")){
   nchannel = 507034;
 }
 else if(RootName.Contains("345705_")){ 
   nchannel = 345705;
 }
 else if(RootName.Contains("345706_")){ 
   nchannel = 345706;
 }
 else if(RootName.Contains("361106_")){ 
   nchannel = 361106;
 }
 else if(RootName.Contains("361107_")){ 
   nchannel = 361107;
 }
 else if(RootName.Contains("361108_")){ 
   nchannel = 361108;
 }
 else if(RootName.Contains("361292_")){ 
   nchannel = 361292;
 }
 else if(RootName.Contains("361293_")){ 
   nchannel = 361293;
 }
 else if(RootName.Contains("361601_")){
   nchannel = 361601;
 }
 else if(RootName.Contains("364242_")){ 
   nchannel = 364242;
 }
 else if(RootName.Contains("364243_")){ 
   nchannel = 364243;
 }
 else if(RootName.Contains("364244_")){ 
   nchannel = 364244;
 }
 else if(RootName.Contains("364245_")){ 
   nchannel = 364245;
 }
 else if(RootName.Contains("364246_")){ 
   nchannel = 364246;
 }
 else if(RootName.Contains("364247_")){ 
   nchannel = 364247;
 }
 else if(RootName.Contains("364248_")){ 
   nchannel = 364248;
 }
 else if(RootName.Contains("364249_")){ 
   nchannel = 364249;
 }
 else if(RootName.Contains("364250_")){ 
   nchannel = 364250;
 }
 else if(RootName.Contains("364254_")){ 
   nchannel = 364254;
 }
 else if(RootName.Contains("364283_")){ 
   nchannel = 364283;
 }
 else if(RootName.Contains("364284_")){ 
   nchannel = 364284;
 }
 else if(RootName.Contains("364739_")){ 
   nchannel = 364739;
 }
 else if(RootName.Contains("364740_")){ 
   nchannel = 364740;
 }
 else if(RootName.Contains("364741_")){ 
   nchannel = 364741;
 }
 else if(RootName.Contains("364742_")){ 
   nchannel = 364742;
 }
 else if(RootName.Contains("366140_")){ 
   nchannel = 366140;
 }
 else if(RootName.Contains("366141_")){ 
   nchannel = 366141;
 }
 else if(RootName.Contains("366142_")){ 
   nchannel = 366142;
 }
 else if(RootName.Contains("366143_")){ 
   nchannel = 366143;
 }
 else if(RootName.Contains("366144_")){ 
   nchannel = 366144;
 }
 else if(RootName.Contains("366145_")){ 
   nchannel = 366145;
 }
 else if(RootName.Contains("366146_")){ 
   nchannel = 366146;
 }
 else if(RootName.Contains("366147_")){ 
   nchannel = 366147;
 }
 else if(RootName.Contains("366148_")){ 
   nchannel = 366148;
 }
 else if(RootName.Contains("366149_")){ 
   nchannel = 366149;
 }
 else if(RootName.Contains("366150_")){ 
   nchannel = 366150;
 }
 else if(RootName.Contains("366151_")){ 
   nchannel = 366151;
 }
 else if(RootName.Contains("366152_")){ 
   nchannel = 366152;
 }
 else if(RootName.Contains("366153_")){ 
   nchannel = 366153;
 }
 else if(RootName.Contains("366154_")){ 
   nchannel = 366154;
 }
 else if(RootName.Contains("410155_")){ 
   nchannel = 410155;
 }
 else if(RootName.Contains("410218_")){ 
   nchannel = 410218;
 }
 else if(RootName.Contains("410219_")){ 
   nchannel = 410219;
 }
 else if(RootName.Contains("410470_")){ 
   nchannel = 410470;
 }
 else if(RootName.Contains("410550_")){ 
   nchannel = 410550;
 }
 else if(RootName.Contains("410644_")){ 
   nchannel = 410644;
 }
 else if(RootName.Contains("410645_")){ 
   nchannel = 410645;
 }
 else if(RootName.Contains("410646_")){ 
   nchannel = 410646;
 }
 else if(RootName.Contains("410647_")){ 
   nchannel = 410647;
 }
 else if(RootName.Contains("410648_")){ 
   nchannel = 410648;
 }
 else if(RootName.Contains("410649_")){ 
   nchannel = 410649;
 }
 else if(RootName.Contains("410658_")){ 
   nchannel = 410658;
 }
 else if(RootName.Contains("410659_")){ 
   nchannel = 410659;
 }
 else if(RootName.Contains("data15") || RootName.Contains("data16") || RootName.Contains("data17") || RootName.Contains("data18")){
   nchannel = -1;
 }
 else{
   nchannel = -999;
 }

 return nchannel;
}

int SumOfWeightHelper::GetYear(TString RootName)
{
 int Year = 0;
 if(RootName.Contains("MC16a") || RootName.Contains("sub30aM") || RootName.Contains("sub55aM") || RootName.Contains("data15") || RootName.Contains("data16")) Year = 1516;
 else if(RootName.Contains("MC16d") || RootName.Contains("sub30dM") || RootName.Contains("sub55dM") || RootName.Contains("data17")) Year = 17;
 else if(RootName.Contains("MC16e") || RootName.Contains("sub30eM") || RootName.Contains("sub55eM") || RootName.Contains("data18")) Year = 18;
 else Year = 0;

 return Year;
}

