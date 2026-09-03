#include "FormatTransform/HistFormat.h"

HistFormat::HistFormat()
{
 InitialHistName();

}

HistFormat::~HistFormat()
{

}

void HistFormat::openFile(const char* FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void HistFormat::openHistFile(const char* FileName)
{
 HistFile = new TFile(FileName);
}

void HistFormat::openSysHistFile(TString FileName)
{
 int isys = -1;
 map<TString, int>::iterator sysIter;
 for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
   SysHistMap[sysIter->first] = new TFile(FileName + "_" + sysIter->first + ".root");
 }

}

void HistFormat::InitialHistName()
{
 HistNames.push_back("BDTScore");
 HistNames.push_back("BDTScoreSR");
// HistNames.push_back("DY_WZ");
// HistNames.push_back("DY_3Z");

// HistNames.push_back("Deep_DY_WZ_TT");
// HistNames.push_back("Deep_DY_3Z_TT");
// HistNames.push_back("Deep_DY_WZ_TT_DataSubtracted");
// HistNames.push_back("Deep_DY_3Z_TT_DataSubtracted");

// HistNames.push_back("CosThetaV");
// HistNames.push_back("DeltaPhiLepWLepZ");
// HistNames.push_back("DeltaPhiLepWLepZWZFrame");
}

void HistFormat::InitialFileStructure()
{
 hf->cd();

 TDirectory *RegionDir;
 TDirectory *SampleDir;
 TDirectory *CategoryDir;

 for(auto regionName : regionNames){
   RegionDir = hf->mkdir(regionName);

   for(auto sampleName : sampleNames){
     SampleDir = RegionDir->mkdir(sampleName);

     for(auto categoryName : categoryNames){
       CategoryDir = SampleDir->mkdir(categoryName);

       FillHist(regionName, sampleName, categoryName, CategoryDir);
     }
   }
 }

}

void HistFormat::FillHist(TString regionName, TString sampleName, TString categoryName, TDirectory *dir)
{
 hf->cd();

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   int isys = -1;
   map<TString, int>::iterator sysIter;
   for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
     Sta_HistNumber++;

     isys = sysIter->second;

     TString oldName;
     TString newName;
     TString oldregionName;
     TString oldsampleName;
     TString oldcategoryName;
     TString sysName;

     if(regionName == "WZInclusive") oldregionName = "Inclusive";
     if(regionName == "SR") oldregionName = "SignalPtWZ";
     if(regionName == "SRPtZ100") oldregionName = "SignalPtZ100";
     if(regionName == "LowPtZVR") oldregionName = "LowPtZCR";
     if(regionName == "HighPtWZVR") oldregionName = "HighPtWZCR";
     if(regionName == "PtWZ10CR") oldregionName = "PtWZ10CR";
     if(regionName == "PtWZ20CR") oldregionName = "PtWZ20CR";
     if(regionName == "PtWZ40CR") oldregionName = "PtWZ40CR";
     if(regionName == "PtWZ70CR") oldregionName = "LowPtWZCR";

     if(sampleName == "Data") oldsampleName = "Data";
     if(sampleName == "WZQCD") oldsampleName = "Total";
     if(sampleName == "WLZL") oldsampleName = "LL";
     if(sampleName == "WLZT") oldsampleName = "LT";
     if(sampleName == "WTZL") oldsampleName = "TL";
     if(sampleName == "WTZT") oldsampleName = "TT";
     if(sampleName == "ZZ") oldsampleName = "BkgZZ";
     if(sampleName == "WZEW") oldsampleName = "BkgWZEW";
     if(sampleName == "VVV") oldsampleName = "BkgVVV";
     if(sampleName == "ttbarV") oldsampleName = "BkgttbarV";
     if(sampleName == "Non-prompt") oldsampleName = "Fake";

     if(categoryName == "all") oldcategoryName = "";
     if(categoryName == "CatLL") oldcategoryName = "_WLZL";
     if(categoryName == "CatLT") oldcategoryName = "_WLZH";
     if(categoryName == "CatTL") oldcategoryName = "_WHZL";
     if(categoryName == "CatTT") oldcategoryName = "_WHZH";

     sysName = sysIter->first;
     if(sysName == "nominal") sysName = "nom";

     if(sampleName != "Pseudodata" && sampleName != "WZMixed" && sampleName != "WZRest"){
       oldName = HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_" + oldsampleName;
       newName = HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName;
       if(oldsampleName == "Data"){
         oldName = HistNames.at(ihist) + oldcategoryName + "_" + oldsampleName + oldregionName;
         newName = HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName;
         if(sysIter->first != "nominal") continue;
       }

       cout<<"Hist "<<Sta_HistNumber<<": Old hist name: "<<oldName<<" New hist name: "<<newName<<endl;

       TH1D *newHist = (TH1D *)((SysHistMap[sysIter->first]->Get(oldName))->Clone(newName));
       newHist->SetDirectory(dir);
       dir->cd();
       newHist->Write();
       delete newHist;
     }
     if(sampleName == "Pseudodata"){
       TH1D *HistBkgZZ = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_BkgZZ");
       TH1D *HistBkgVVV = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_BkgVVV");
       TH1D *HistBkgWZEW = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_BkgWZEW");
       TH1D *HistBkgttbarV = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_BkgttbarV");
       TH1D *HistBkgWZQCD = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_Total");
       TH1D *HistFake = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_Fake");

       TH1D *HistMerge = (TH1D *)HistBkgZZ->Clone(HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName);
       HistMerge->Add(HistBkgVVV);
       HistMerge->Add(HistBkgWZEW);
       HistMerge->Add(HistBkgttbarV);
       HistMerge->Add(HistBkgWZQCD);
       HistMerge->Add(HistFake);

       HistMerge->SetDirectory(dir);
       dir->cd();
       HistMerge->Write();
       delete HistMerge;
     }
     if(sampleName == "WZMixed"){
       if(!(sysName.Contains("PDF") || sysName.Contains("QCD"))){
         TH1D *HistLT = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_LT");
         TH1D *HistTL = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_TL");

         TH1D *HistMerge = (TH1D *)HistLT->Clone(HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName);
         HistMerge->Add(HistTL);

         HistMerge->SetDirectory(dir);
         dir->cd();
         HistMerge->Write();
         delete HistMerge;
       }
       else{
         TH1D *HistWZMixed = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_WZMixed");

         TH1D *HistMerge = (TH1D *)HistWZMixed->Clone(HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName);

         HistMerge->SetDirectory(dir);
         dir->cd();
         HistMerge->Write();
         delete HistMerge;
       }
     }
     if(sampleName == "WZRest"){
       if(!(sysName.Contains("PDF") || sysName.Contains("QCD"))){
         TH1D *HistLT = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_LT");
         TH1D *HistTL = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_TL");
         TH1D *HistTT = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_TT");

         TH1D *HistMerge = (TH1D *)HistLT->Clone(HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName);
         HistMerge->Add(HistTL);
         HistMerge->Add(HistTT);

         HistMerge->SetDirectory(dir);
         dir->cd();
         HistMerge->Write();
         delete HistMerge;
       }
       else{
         TH1D *HistWZRest = (TH1D *)SysHistMap[sysIter->first]->Get(HistNames.at(ihist) + oldcategoryName + "_" + oldregionName + "_WZRest");

         TH1D *HistMerge = (TH1D *)HistWZRest->Clone(HistNames.at(ihist) + "_" + regionName + "_" + sampleName + "_" + categoryName + "_" + sysName);

         HistMerge->SetDirectory(dir);
         dir->cd();
         HistMerge->Write();
         delete HistMerge;
       }
     }
   }
 }

}

void HistFormat::SaveFile()
{
 map<TString, int>::iterator sysIter;
 for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
   cout<<"Close the File: MC_results_"<<sysIter->first<<".root"<<endl;

   SysHistMap[sysIter->first]->Close();
   delete SysHistMap[sysIter->first];
 }

 hf->cd();

// hf->Write();
 hf->Close();
}

void HistFormat::LinkHist(HistsWZPolarization *myhists)
{
 this->fHist = myhists;
 SysNameIndex = myhists->SysNameIndexSignalWZ;
}
