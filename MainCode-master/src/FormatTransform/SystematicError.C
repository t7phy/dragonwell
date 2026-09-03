#include "FormatTransform/SystematicError.h"

SystematicError::SystematicError()
{
// InitialHistName();

}

SystematicError::~SystematicError()
{

}

void SystematicError::openFile(const char* FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void SystematicError::openHistFile(const char* FileName)
{
 HistFile = new TFile(FileName);
}

void SystematicError::openSysHistFile(TString FileName)
{
 int isys = -1;
 map<TString, int>::iterator sysIter;
 for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){
   SysHistMap[sysIter->first] = new TFile(FileName + "_" + sysIter->first + ".root");
   SysNames[sysIter->second] = sysIter->first;
 }

}

void SystematicError::InitialHistName()
{
 HistNames.push_back("DY_WZ");
 HistNames.push_back("DY_3Z");
 HistNames.push_back("Deep_DY_WZ_TT");
 HistNames.push_back("Deep_DY_3Z_TT");
 HistNames.push_back("Deep_DY_WZ_TT_DataSubtracted");
 HistNames.push_back("Deep_DY_3Z_TT_DataSubtracted");

 HistType["Deep_DY_WZ_TT"] = "Single";
 HistType["Deep_DY_3Z_TT"] = "Single";
 HistType["Deep_DY_WZ_TT_DataSubtracted"] = "Single";
 HistType["Deep_DY_3Z_TT_DataSubtracted"] = "Single";

// HistNames.push_back("CosThetaV");
// HistNames.push_back("DeltaPhiLepWLepZ");
// HistNames.push_back("DeltaPhiLepWLepZWZFrame");
}

void SystematicError::InitialFileStructure()
{
 hf->cd();

 for(auto regionName : regionNames){
   for(auto ProcessName : ProcessNames){
     FillHist(regionName, ProcessName);
   }
 }

}

void SystematicError::FillHist(TString regionName, TString ProcessName)
{
 hf->cd();

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   Sta_HistNumber++;

   TH1D *HistData;
   if(regionName != "Single" && HistType[HistNames.at(ihist)] != "Single"){
     HistData = (TH1D *)SysHistMap["nominal"]->Get(HistNames.at(ihist) + "_Data" + regionName);
     HistData->Write();
     //delete HistData;
   }

   TString HistName;
   if(regionName != "Single" && HistType[HistNames.at(ihist)] != "Single") HistName = HistNames.at(ihist) + "_" + regionName;
   if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") HistName = HistNames.at(ihist);
   cout<<"Hist "<<Sta_HistNumber<<": hist name: "<<HistName<<" region: "<<regionName<<" process: "<<ProcessName<<endl;
   TString OriginalHistName = HistNames.at(ihist);

   SysIndexMap.clear();

   map<TString, int>::iterator sysIter;
   for(sysIter = SysNameIndex.begin(); sysIter != SysNameIndex.end(); sysIter++){

     if(ProcessName == "Polarized"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       TH1D *HistTotal = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_Total");
       TH1D *HistLL = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_LL");
       TH1D *HistLT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_LT");
       TH1D *HistTL = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_TL");
       TH1D *HistTT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_TT");

       TH1D *HistMerge = (TH1D *)HistLL->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);
       HistMerge->Add(HistLT);
       HistMerge->Add(HistTL);
       HistMerge->Add(HistTT);

       SysIndexMap[sysIter->second] = HistMerge;

       if(sysIter->first == "nominal"){
         HistTotal->Write();
         HistLL->Write();
         HistLT->Write();
         HistTL->Write();
         HistTT->Write();
       }
       delete HistTotal;
       delete HistLL;
       delete HistLT;
       delete HistTL;
       delete HistTT;
     }

     if(ProcessName == "SignalWZ"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       TH1D *HistBkgZZ = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZZ");
       TH1D *HistBkgZjet = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZjet");
       TH1D *HistBkgVVV = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgVVV");
       TH1D *HistBkgWZEW = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgWZEW");
       TH1D *HistBkgZgamma = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZgamma");
       TH1D *HistBkgttbarV = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgttbarV");
       TH1D *HistBkgTop = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgTop");
       TH1D *HistBkgtZ = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgtZ");
       TH1D *HistBkgWZQCD = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_Total");

       TH1D *HistMerge = (TH1D *)HistBkgZZ->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);
       HistMerge->Add(HistBkgZjet);
       HistMerge->Add(HistBkgVVV);
       HistMerge->Add(HistBkgWZEW);
       HistMerge->Add(HistBkgZgamma);
       HistMerge->Add(HistBkgttbarV);
       HistMerge->Add(HistBkgTop);
       HistMerge->Add(HistBkgtZ);
       HistMerge->Add(HistBkgWZQCD);

       SysIndexMap[sysIter->second] = HistMerge;

       if(sysIter->first == "nominal"){
         HistBkgZZ->Write();
         HistBkgZjet->Write();
         HistBkgVVV->Write();
         HistBkgWZEW->Write();
         HistBkgZgamma->Write();
         HistBkgttbarV->Write();
         HistBkgTop->Write();
         HistBkgtZ->Write();
       }
       delete HistBkgZZ;
       delete HistBkgZjet;
       delete HistBkgVVV;
       delete HistBkgWZEW;
       delete HistBkgZgamma;
       delete HistBkgttbarV;
       delete HistBkgTop;
       delete HistBkgtZ;
       delete HistBkgWZQCD;
     }

     if(ProcessName == "SignalWZPolarized"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       TH1D *HistBkgZZ = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZZ");
       TH1D *HistBkgZjet = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZjet");
       TH1D *HistBkgVVV = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgVVV");
       TH1D *HistBkgWZEW = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgWZEW");
       TH1D *HistBkgZgamma = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZgamma");
       TH1D *HistBkgttbarV = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgttbarV");
       TH1D *HistBkgTop = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgTop");
       TH1D *HistBkgtZ = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgtZ");
       TH1D *HistFake = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_Fake");
       TH1D *HistLL = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_LL");
       TH1D *HistLT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_LT");
       TH1D *HistTL = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_TL");
       TH1D *HistTT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_TT");

       TH1D *HistMerge = (TH1D *)HistBkgZZ->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);
       //HistMerge->Add(HistBkgZjet);
       HistMerge->Add(HistBkgVVV);
       HistMerge->Add(HistBkgWZEW);
       //HistMerge->Add(HistBkgZgamma);
       HistMerge->Add(HistBkgttbarV);
       //HistMerge->Add(HistBkgTop);
       //HistMerge->Add(HistBkgtZ);
       HistMerge->Add(HistFake);
       HistMerge->Add(HistLL);
       HistMerge->Add(HistLT);
       HistMerge->Add(HistTL);
       HistMerge->Add(HistTT);

       SysIndexMap[sysIter->second] = HistMerge;

       if(sysIter->first == "nominal"){
         HistBkgZZ->Write();
         HistBkgVVV->Write();
         HistBkgWZEW->Write();
         HistBkgttbarV->Write();
         HistFake->Write();
         HistLL->Write();
         HistLT->Write();
         HistTL->Write();
         HistTT->Write();
       }

       delete HistBkgZZ;
       delete HistBkgZjet;
       delete HistBkgVVV;
       delete HistBkgWZEW;
       delete HistBkgZgamma;
       delete HistBkgttbarV;
       delete HistBkgTop;
       delete HistBkgtZ;
       delete HistFake;
       delete HistLL;
       delete HistLT;
       delete HistTL;
       delete HistTT;
     }

     if(ProcessName == "FakeBkg"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       TH1D *HistFake = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_Fake");

       TH1D *HistMerge = (TH1D *)HistFake->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);

       SysIndexMap[sysIter->second] = HistMerge;

       if(sysIter->first == "nominal"){
         HistFake->Write();
       }
       delete HistFake;
     }
     if(ProcessName == "Single"){
       if(HistType[OriginalHistName] == "Single"){

         if(regionName != "Single") continue;

         TH1D *Hist = (TH1D *)SysHistMap[sysIter->first]->Get(HistName);

         TH1D *HistMerge = (TH1D *)Hist->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);

         SysIndexMap[sysIter->second] = HistMerge;

         if(sysIter->first == "nominal"){
           Hist->Write();
         }
         delete Hist;
       }
     }
     if(ProcessName == "FinalTT"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       if(!((sysIter->first).Contains("PDF") || (sysIter->first).Contains("QCD"))){

         TH1D *HistBkgZZ = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgZZ");
         TH1D *HistBkgVVV = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgVVV");
         TH1D *HistBkgWZEW = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgWZEW");
         TH1D *HistBkgttbarV = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_BkgttbarV");
         TH1D *HistFake = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_Fake");
         TH1D *HistLL = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_LL");
         TH1D *HistLT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_LT");
         TH1D *HistTL = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_TL");

         TH1D *HistMerge = (TH1D *)HistData->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);
         HistMerge->Add(HistBkgZZ, -1);
         HistMerge->Add(HistBkgVVV, -1);
         HistMerge->Add(HistBkgWZEW, -1);
         HistMerge->Add(HistBkgttbarV, -1);
         HistMerge->Add(HistFake, -1);
         HistMerge->Add(HistLL, -1);
         HistMerge->Add(HistLT, -1);
         HistMerge->Add(HistTL, -1);

         SysIndexMap[sysIter->second] = HistMerge;

         delete HistBkgZZ;
         delete HistBkgVVV;
         delete HistBkgWZEW;
         delete HistBkgttbarV;
         delete HistFake;
         delete HistLL;
         delete HistLT;
         delete HistTL;
       }
       else{
         TH1D *HistFinalTT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_FinalTT");

         TH1D *HistMerge = (TH1D *)HistFinalTT->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);

         SysIndexMap[sysIter->second] = HistMerge;

         delete HistFinalTT;
       }
     }
     if(ProcessName == "TT"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       TH1D *HistTT = (TH1D *)SysHistMap[sysIter->first]->Get(HistName + "_TT");

       TH1D *HistMerge = (TH1D *)HistTT->Clone(HistName + "_" + ProcessName + "Merged_" + sysIter->first);

       SysIndexMap[sysIter->second] = HistMerge;

       if(sysIter->first == "nominal"){
         HistTT->Write();
       }
       delete HistTT;
     }
   }
   HistName = HistName + "_" + ProcessName;
   if(SysIndexMap.size() > 0) GetSystematicError(HistName, SysIndexMap);
 }

}

void SystematicError::GetSystematicError(TString HistName, map<int, TH1D*> SysIndexMap)
{
 hf->cd();

 SystematicUncertainty *unc = new SystematicUncertainty(SysNameIndex, SysNames);
 unc->SaveVariBin();
 unc->GetUncertainty(HistName, SysIndexMap);

 delete unc;

/* vector<double> SysUp;
 vector<double> SysDown;
 vector<TString> SysUpName;
 vector<TString> SysDownName;

 double SysError;
 double SysError2;
 double SysNominal;

 TH1D *HistSysError = (TH1D *)SysIndexMap[0]->Clone(HistName + "_SysError");
 HistSysError->Reset();

 TH1D *HistMerge = (TH1D *)SysIndexMap[0]->Clone(HistName + "_SysMerge");

 for(int ibin = 0; ibin < SysIndexMap[0]->GetNbinsX(); ibin++){

   SysUp.clear();
   SysDown.clear();
   SysUpName.clear();
   SysDownName.clear();
   SysError = 0.0;
   SysError2 = 0.0;
   SysNominal = SysIndexMap[0]->GetBinContent(ibin + 1);
   map<int, TH1D*>::iterator sysIter;

   for(sysIter = SysIndexMap.begin(); sysIter != SysIndexMap.end(); sysIter++){
     if(sysIter->first != 0 && sysIter->first % 2 != 0){
       SysDown.push_back(sysIter->second->GetBinContent(ibin + 1));
       SysDownName.push_back(SysNames[sysIter->first]);
     }
     if(sysIter->first != 0 && sysIter->first % 2 == 0){
       SysUp.push_back(sysIter->second->GetBinContent(ibin + 1));
       SysUpName.push_back(SysNames[sysIter->first]);
     }
   }

   for(int i = 0; i < SysDown.size(); i++){
     cout<<"Up: "<<SysUpName.at(i)<<" Down: "<<SysDownName.at(i)<<endl;
     double SysErrorDown = fabs(SysNominal - SysDown.at(i));
     double SysErrorUp = fabs(SysNominal - SysUp.at(i));
     if(SysErrorDown > SysErrorUp) SysError2 += SysErrorDown * SysErrorDown;
     if(SysErrorDown < SysErrorUp) SysError2 += SysErrorUp * SysErrorUp;
   }

   HistSysError->SetBinContent(ibin + 1, sqrt(SysError2));
 }
 HistSysError->Write();

 for(int ibin = 0; ibin < HistMerge->GetNbinsX(); ibin++){
   HistMerge->SetBinError(ibin + 1, HistSysError->GetBinContent(ibin + 1));
 }
 HistMerge->Write();

 delete HistSysError;
 delete HistMerge;
*/
}

void SystematicError::SaveFile()
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

void SystematicError::LinkHist(HistsWZPolarization *myhists)
{

 ////////////////////////////////////////////////////////////////
 //  Retrieve the SysNameIndex defined in HistsWZPolarization  //
 //  The systematic unc is calculated according to this list.  //
 //  HistNames is defined in HistsWZPolarization.              //
 ////////////////////////////////////////////////////////////////

 this->fHist = myhists;
 SysNameIndex = myhists->SysNameIndexSignalWZ;
// this->HistNames = myhists->HistNames;
}
