#include "Uncertainty/SystematicUncertainty.h"

SystematicUncertainty::SystematicUncertainty(map<TString, int> SysNameIndex, map<int, TString> SysNames)
{
 this->SysNameIndex = SysNameIndex;
 this->SysNames = SysNames;
}

void SystematicUncertainty::GetUncertainty(TString HistName, map<int, TH1D*> SysIndexMap)
{
 vector<double> SysUp;
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

   TString UncName = HistName + "_UncVariation_Bin_";
   UncName = UncName + (int)(ibin + 1);
   TString UncStatName = HistName + "_UncVariationStat_Bin_";
   UncStatName = UncStatName + (int)(ibin + 1);
   if(isSaveVariBin) UncVari[ibin + 1] = new TH1D(UncName, UncName, (SysIndexMap.size() - 1) / 2, 0.5, (SysIndexMap.size() - 1) / 2 + 0.5);
   if(isSaveVariBin) UncVariStat[ibin + 1] = new TH1D(UncStatName, UncStatName, (SysIndexMap.size() - 1) / 2, 0.5, (SysIndexMap.size() - 1) / 2 + 0.5);

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
     if(SysDownName.at(i) == "MET_SoftTrk_ScaleDown__1down"){
       SysDownName.at(i).ReplaceAll("Down__1down", "");
       SysUpName.at(i).ReplaceAll("Up__1up", "");
     }
     else{
       SysDownName.at(i).ReplaceAll("__1down", "");
       SysUpName.at(i).ReplaceAll("__1up", "");
     }

     if(SysDownName.at(i) != SysUpName.at(i)) cout<<"ERROR: Systematic up and down don't match."<<endl;

     double SysErrorDown = fabs(SysNominal - SysDown.at(i));
     double SysErrorUp = fabs(SysNominal - SysUp.at(i));
     if(SysErrorDown > SysErrorUp) SysError2 += SysErrorDown * SysErrorDown;
     if(SysErrorDown < SysErrorUp) SysError2 += SysErrorUp * SysErrorUp;

     if(isSaveVariBin){
//       if(SysErrorDown > SysErrorUp) UncVari[ibin + 1]->SetBinContent(i + 1, SysErrorDown);
//       if(SysErrorDown < SysErrorUp) UncVari[ibin + 1]->SetBinContent(i + 1, SysErrorUp);
       if(SysErrorDown > SysErrorUp) UncVari[ibin + 1]->SetBinError(i + 1, SysErrorDown);
       if(SysErrorDown < SysErrorUp) UncVari[ibin + 1]->SetBinError(i + 1, SysErrorUp);
     }
//     if(isSaveVariBin) UncVari[ibin + 1]->SetBinError(i + 1, 0);
     if(isSaveVariBin) UncVari[ibin + 1]->SetBinContent(i + 1, SysIndexMap[0]->GetBinContent(ibin + 1));
     if(isSaveVariBin) UncVari[ibin + 1]->GetXaxis()->SetBinLabel(i + 1, SysDownName.at(i));
     if(isSaveVariBin) UncVariStat[ibin + 1]->SetBinContent(i + 1, SysIndexMap[0]->GetBinContent(ibin + 1));
     if(isSaveVariBin) UncVariStat[ibin + 1]->SetBinError(i + 1, SysIndexMap[0]->GetBinError(ibin + 1));
     if(isSaveVariBin) UncVariStat[ibin + 1]->GetXaxis()->SetBinLabel(i + 1, SysDownName.at(i));
   }

   double StatError2 = SysIndexMap[0]->GetBinError(ibin + 1) * SysIndexMap[0]->GetBinError(ibin + 1);

   HistSysError->SetBinContent(ibin + 1, sqrt(SysError2 + StatError2));
 }

 for(int ibin = 0; ibin < HistMerge->GetNbinsX(); ibin++){
   HistMerge->SetBinError(ibin + 1, HistSysError->GetBinContent(ibin + 1));
   if(isSaveVariBin) UncVari[ibin + 1]->Write();
   if(isSaveVariBin) delete UncVari[ibin + 1];
   if(isSaveVariBin) UncVariStat[ibin + 1]->Write();
   if(isSaveVariBin) delete UncVariStat[ibin + 1];
 }
 HistSysError->Write();
 HistMerge->Write();

 delete HistSysError;
 delete HistMerge;

}
