#include "SpecialHist/DataDriven.h"

DataDriven::DataDriven()
{
 FakeObjects = 3;
}

DataDriven::DataDriven(int nfake)
{
 FakeObjects = nfake;
}

void DataDriven::InputFakeRate(TH1D* ZElFakeRate, TH1D* ZMuFakeRate, TH1D* WElFakeRate, TH1D* WMuFakeRate)
{
 this->doFakeRate = 1;

 this->ZElFakeRate = ZElFakeRate;
 this->ZMuFakeRate = ZMuFakeRate;
 this->WElFakeRate = WElFakeRate;
 this->WMuFakeRate = WMuFakeRate;
}

void DataDriven::InputUpSysFakeRate(TH1D* ZElFakeRate, TH1D* ZMuFakeRate, TH1D* WElFakeRate, TH1D* WMuFakeRate)
{
 this->doFakeRate = 1;
 this->isInputUpSysFakeRate = true;

 this->ZElFakeRate_UpSys = ZElFakeRate;
 this->ZMuFakeRate_UpSys = ZMuFakeRate;
 this->WElFakeRate_UpSys = WElFakeRate;
 this->WMuFakeRate_UpSys = WMuFakeRate;
}

void DataDriven::InputDownSysFakeRate(TH1D* ZElFakeRate, TH1D* ZMuFakeRate, TH1D* WElFakeRate, TH1D* WMuFakeRate)
{
 this->doFakeRate = 1;
 this->isInputDownSysFakeRate = true;

 this->ZElFakeRate_DownSys = ZElFakeRate;
 this->ZMuFakeRate_DownSys = ZMuFakeRate;
 this->WElFakeRate_DownSys = WElFakeRate;
 this->WMuFakeRate_DownSys = WMuFakeRate;
}

void DataDriven::InputFakeEfficiency(TH1D* ZElFakeEff, TH1D* ZMuFakeEff, TH1D* WElFakeEff, TH1D* WMuFakeEff)
{
 this->doFakeRate = 2;

 this->ZElFakeEff = ZElFakeEff;
 this->ZMuFakeEff = ZMuFakeEff;
 this->WElFakeEff = WElFakeEff;
 this->WMuFakeEff = WMuFakeEff;
}

void DataDriven::InputRealEfficiency(TH1D* ZElRealEff, TH1D* ZMuRealEff, TH1D* WElRealEff, TH1D* WMuRealEff)
{
 this->doFakeRate = 2;

 this->ZElRealEff = ZElRealEff;
 this->ZMuRealEff = ZMuRealEff;
 this->WElRealEff = WElRealEff;
 this->WMuRealEff = WMuRealEff;
}

void DataDriven::GetIndex(double Lep1Pt, double Lep2Pt, double Lep3Pt, TString Flavor)
{
 isUnknown = false;
 if(Flavor == "eem"){
   Lep1_bin = ZElFakeRate->FindBin(Lep1Pt);
   Lep2_bin = ZElFakeRate->FindBin(Lep2Pt);
   Lep3_bin = WMuFakeRate->FindBin(Lep3Pt);

   FakeRate[0] = ZElFakeRate;
   FakeRate[1] = ZElFakeRate;
   FakeRate[2] = WMuFakeRate;

   FakeRate_UpSys[0] = ZElFakeRate_UpSys;
   FakeRate_UpSys[1] = ZElFakeRate_UpSys;
   FakeRate_UpSys[2] = WMuFakeRate_UpSys;

   FakeRate_DownSys[0] = ZElFakeRate_DownSys;
   FakeRate_DownSys[1] = ZElFakeRate_DownSys;
   FakeRate_DownSys[2] = WMuFakeRate_DownSys;
 }
 else if(Flavor == "mme"){
   Lep1_bin = ZMuFakeRate->FindBin(Lep1Pt);
   Lep2_bin = ZMuFakeRate->FindBin(Lep2Pt);
   Lep3_bin = WElFakeRate->FindBin(Lep3Pt);
 
   FakeRate[0] = ZMuFakeRate;
   FakeRate[1] = ZMuFakeRate;
   FakeRate[2] = WElFakeRate;

   FakeRate_UpSys[0] = ZMuFakeRate_UpSys;
   FakeRate_UpSys[1] = ZMuFakeRate_UpSys;
   FakeRate_UpSys[2] = WElFakeRate_UpSys;

   FakeRate_DownSys[0] = ZMuFakeRate_DownSys;
   FakeRate_DownSys[1] = ZMuFakeRate_DownSys;
   FakeRate_DownSys[2] = WElFakeRate_DownSys;
 }
 else if(Flavor == "eee"){
   Lep1_bin = ZElFakeRate->FindBin(Lep1Pt);
   Lep2_bin = ZElFakeRate->FindBin(Lep2Pt);
   Lep3_bin = WElFakeRate->FindBin(Lep3Pt);
 
   FakeRate[0] = ZElFakeRate;
   FakeRate[1] = ZElFakeRate;
   FakeRate[2] = WElFakeRate;

   FakeRate_UpSys[0] = ZElFakeRate_UpSys;
   FakeRate_UpSys[1] = ZElFakeRate_UpSys;
   FakeRate_UpSys[2] = WElFakeRate_UpSys;

   FakeRate_DownSys[0] = ZElFakeRate_DownSys;
   FakeRate_DownSys[1] = ZElFakeRate_DownSys;
   FakeRate_DownSys[2] = WElFakeRate_DownSys;
 }
 else if(Flavor == "mmm"){
   Lep1_bin = ZMuFakeRate->FindBin(Lep1Pt);
   Lep2_bin = ZMuFakeRate->FindBin(Lep2Pt);
   Lep3_bin = WMuFakeRate->FindBin(Lep3Pt);
 
   FakeRate[0] = ZMuFakeRate;
   FakeRate[1] = ZMuFakeRate;
   FakeRate[2] = WMuFakeRate;

   FakeRate_UpSys[0] = ZMuFakeRate_UpSys;
   FakeRate_UpSys[1] = ZMuFakeRate_UpSys;
   FakeRate_UpSys[2] = WMuFakeRate_UpSys;

   FakeRate_DownSys[0] = ZMuFakeRate_DownSys;
   FakeRate_DownSys[1] = ZMuFakeRate_DownSys;
   FakeRate_DownSys[2] = WMuFakeRate_DownSys;
 }
 else if(Flavor == "emm"){
   Lep1_bin = ZElFakeRate->FindBin(Lep1Pt);
   Lep2_bin = ZMuFakeRate->FindBin(Lep2Pt);
   Lep3_bin = WMuFakeRate->FindBin(Lep3Pt);

   FakeRate[0] = ZElFakeRate;
   FakeRate[1] = ZMuFakeRate;
   FakeRate[2] = WMuFakeRate;

   FakeRate_UpSys[0] = ZElFakeRate_UpSys;
   FakeRate_UpSys[1] = ZMuFakeRate_UpSys;
   FakeRate_UpSys[2] = WMuFakeRate_UpSys;

   FakeRate_DownSys[0] = ZElFakeRate_DownSys;
   FakeRate_DownSys[1] = ZMuFakeRate_DownSys;
   FakeRate_DownSys[2] = WMuFakeRate_DownSys;
 }
 else if(Flavor == "mee"){
   Lep1_bin = ZMuFakeRate->FindBin(Lep1Pt);
   Lep2_bin = ZElFakeRate->FindBin(Lep2Pt);
   Lep3_bin = WElFakeRate->FindBin(Lep3Pt);

   FakeRate[0] = ZMuFakeRate;
   FakeRate[1] = ZElFakeRate;
   FakeRate[2] = WElFakeRate;

   FakeRate_UpSys[0] = ZMuFakeRate_UpSys;
   FakeRate_UpSys[1] = ZElFakeRate_UpSys;
   FakeRate_UpSys[2] = WElFakeRate_UpSys;

   FakeRate_DownSys[0] = ZMuFakeRate_DownSys;
   FakeRate_DownSys[1] = ZElFakeRate_DownSys;
   FakeRate_DownSys[2] = WElFakeRate_DownSys;
 }
 else{
   isUnknown = true;
   F1 = -999.0;
 }

 if(!isUnknown){
   F1 = FakeRate[0]->GetBinContent(Lep1_bin);
   F2 = FakeRate[1]->GetBinContent(Lep2_bin);
   F3 = FakeRate[2]->GetBinContent(Lep3_bin);

   if(isInputUpSysFakeRate) F1_UpSys = FakeRate_UpSys[0]->GetBinContent(Lep1_bin);
   if(isInputUpSysFakeRate) F2_UpSys = FakeRate_UpSys[1]->GetBinContent(Lep2_bin);
   if(isInputUpSysFakeRate) F3_UpSys = FakeRate_UpSys[2]->GetBinContent(Lep3_bin);

   if(isInputDownSysFakeRate) F1_DownSys = FakeRate_DownSys[0]->GetBinContent(Lep1_bin);
   if(isInputDownSysFakeRate) F2_DownSys = FakeRate_DownSys[1]->GetBinContent(Lep2_bin);
   if(isInputDownSysFakeRate) F3_DownSys = FakeRate_DownSys[2]->GetBinContent(Lep3_bin);

   F1_UpStat = FakeRate[0]->GetBinContent(Lep1_bin) + FakeRate[0]->GetBinError(Lep1_bin);
   F2_UpStat = FakeRate[1]->GetBinContent(Lep2_bin) + FakeRate[1]->GetBinError(Lep2_bin);
   F3_UpStat = FakeRate[2]->GetBinContent(Lep3_bin) + FakeRate[2]->GetBinError(Lep3_bin);

   F1_DownStat = FakeRate[0]->GetBinContent(Lep1_bin) - FakeRate[0]->GetBinError(Lep1_bin);
   F2_DownStat = FakeRate[1]->GetBinContent(Lep2_bin) - FakeRate[1]->GetBinError(Lep2_bin);
   F3_DownStat = FakeRate[2]->GetBinContent(Lep3_bin) - FakeRate[2]->GetBinError(Lep3_bin);

   if(Lep1_bin > FakeRate[0]->GetNbinsX() || Lep1_bin == 0){
     F1 = 0.0; F1_UpStat = 0.0; F1_DownStat = 0.0;
   }
   if(Lep2_bin > FakeRate[1]->GetNbinsX() || Lep2_bin == 0){
     F2 = 0.0; F2_UpStat = 0.0; F2_DownStat = 0.0;
   }
   if(Lep3_bin > FakeRate[2]->GetNbinsX() || Lep3_bin == 0){
     F3 = 0.0; F3_UpStat = 0.0; F3_DownStat = 0.0;
   }

 }

 if(F1 < 0) F1 = 0.0;
 if(F2 < 0) F2 = 0.0;
 if(F3 < 0) F3 = 0.0;

 if(F1_UpStat < 0) F1_UpStat = 0.0;
 if(F2_UpStat < 0) F2_UpStat = 0.0;
 if(F3_UpStat < 0) F3_UpStat = 0.0;

 if(F1_DownStat < 0) F1_DownStat = 0.0;
 if(F2_DownStat < 0) F2_DownStat = 0.0;
 if(F3_DownStat < 0) F3_DownStat = 0.0;

 if(F1_UpSys < 0) F1_UpSys = 0.0;
 if(F2_UpSys < 0) F2_UpSys = 0.0;
 if(F3_UpSys < 0) F3_UpSys = 0.0;

 if(F1_DownSys < 0) F1_DownSys = 0.0;
 if(F2_DownSys < 0) F2_DownSys = 0.0;
 if(F3_DownSys < 0) F3_DownSys = 0.0;

 if(!isfinite(F1)) F1 = 0.0;
 if(!isfinite(F2)) F2 = 0.0;
 if(!isfinite(F3)) F3 = 0.0;

 if(!isfinite(F1_UpStat)) F1_UpStat = 0.0;
 if(!isfinite(F2_UpStat)) F2_UpStat = 0.0;
 if(!isfinite(F3_UpStat)) F3_UpStat = 0.0;

 if(!isfinite(F1_DownStat)) F1_DownStat = 0.0;
 if(!isfinite(F2_DownStat)) F2_DownStat = 0.0;
 if(!isfinite(F3_DownStat)) F3_DownStat = 0.0;

 if(!isfinite(F1_UpSys)) F1_UpSys = 0.0;
 if(!isfinite(F2_UpSys)) F2_UpSys = 0.0;
 if(!isfinite(F3_UpSys)) F3_UpSys = 0.0;

 if(!isfinite(F1_DownSys)) F1_DownSys = 0.0;
 if(!isfinite(F2_DownSys)) F2_DownSys = 0.0;
 if(!isfinite(F3_DownSys)) F3_DownSys = 0.0;

 if(isRunUpStat){
   F1 = F1_UpStat;
   F2 = F2_UpStat;
   F3 = F3_UpStat;
 }

 if(isRunDownStat){
   F1 = F1_DownStat;
   F2 = F2_DownStat;
   F3 = F3_DownStat;
 }

}

void DataDriven::GetIndexFullMatrix(double Lep1Pt, double Lep2Pt, double Lep3Pt, TString Flavor)
{
 isUnknown = false;
 vector<int> Index;
 if(Flavor == "eem"){
   Lep1_bin = ZElFakeEff->FindBin(Lep1Pt);
   Lep2_bin = ZElFakeEff->FindBin(Lep2Pt);
   Lep3_bin = WMuFakeEff->FindBin(Lep3Pt);

   FakeEff[0] = ZElFakeEff;
   FakeEff[1] = ZElFakeEff;
   FakeEff[2] = WMuFakeEff;

   RealEff[0] = ZElRealEff;
   RealEff[1] = ZElRealEff;
   RealEff[2] = WMuRealEff;

   Index.push_back(0);
   Index.push_back(Lep1_bin);
   Index.push_back(Lep2_bin);
   Index.push_back(Lep3_bin);

   InverseFakeMatrix = InverseFakeMatrixMap[Index];
   Index.clear();
 }
 else if(Flavor == "emm"){
   Lep1_bin = ZMuFakeEff->FindBin(Lep1Pt);
   Lep2_bin = ZMuFakeEff->FindBin(Lep2Pt);
   Lep3_bin = WElFakeEff->FindBin(Lep3Pt);

   FakeEff[0] = ZMuFakeEff;
   FakeEff[1] = ZMuFakeEff;
   FakeEff[2] = WElFakeEff;

   RealEff[0] = ZMuRealEff;
   RealEff[1] = ZMuRealEff;
   RealEff[2] = WElRealEff;

   Index.push_back(1);
   Index.push_back(Lep1_bin);
   Index.push_back(Lep2_bin);
   Index.push_back(Lep3_bin);

   InverseFakeMatrix = InverseFakeMatrixMap[Index];
   Index.clear();
 }
 else if(Flavor == "eee"){
   Lep1_bin = ZElFakeEff->FindBin(Lep1Pt);
   Lep2_bin = ZElFakeEff->FindBin(Lep2Pt);
   Lep3_bin = WElFakeEff->FindBin(Lep3Pt);

   FakeEff[0] = ZElFakeEff;
   FakeEff[1] = ZElFakeEff;
   FakeEff[2] = WElFakeEff;

   RealEff[0] = ZElRealEff;
   RealEff[1] = ZElRealEff;
   RealEff[2] = WElRealEff;

   Index.push_back(2);
   Index.push_back(Lep1_bin);
   Index.push_back(Lep2_bin);
   Index.push_back(Lep3_bin);

   InverseFakeMatrix = InverseFakeMatrixMap[Index];
   Index.clear();
 }
 else if(Flavor == "mmm"){
   Lep1_bin = ZMuFakeEff->FindBin(Lep1Pt);
   Lep2_bin = ZMuFakeEff->FindBin(Lep2Pt);
   Lep3_bin = WMuFakeEff->FindBin(Lep3Pt);

   FakeEff[0] = ZMuFakeEff;
   FakeEff[1] = ZMuFakeEff;
   FakeEff[2] = WMuFakeEff;

   RealEff[0] = ZMuRealEff;
   RealEff[1] = ZMuRealEff;
   RealEff[2] = WMuRealEff;

   Index.push_back(3);
   Index.push_back(Lep1_bin);
   Index.push_back(Lep2_bin);
   Index.push_back(Lep3_bin);

   InverseFakeMatrix = InverseFakeMatrixMap[Index];
   Index.clear();
 }
 else{
   isUnknown = true;
   InverseFakeMatrix = 0;
 }

 if(!isUnknown){
   f1 = FakeEff[0]->GetBinContent(Lep1_bin);
   f2 = FakeEff[1]->GetBinContent(Lep2_bin);
   f3 = FakeEff[2]->GetBinContent(Lep3_bin);
   e1 = RealEff[0]->GetBinContent(Lep1_bin);
   e2 = RealEff[1]->GetBinContent(Lep2_bin);
   e3 = RealEff[2]->GetBinContent(Lep3_bin);
 }

}

void DataDriven::GetMatrix(int iThread)
{
 FakeEff[0] = ZElFakeEff;
 FakeEff[1] = ZElFakeEff;
 FakeEff[2] = ZElFakeEff;

 for(int iFlavor = 0; iFlavor < 4; iFlavor++){
   for(int Lep1_bin = 1; Lep1_bin <= FakeEff[0]->GetNbinsX(); Lep1_bin++){
     for(int Lep2_bin = 1; Lep2_bin <= FakeEff[1]->GetNbinsX(); Lep2_bin++){
       for(int Lep3_bin = 1; Lep3_bin <= FakeEff[2]->GetNbinsX(); Lep3_bin++){

         vector<int> Index = {iFlavor, Lep1_bin, Lep2_bin, Lep3_bin};
         TString Flavor;
         if(iFlavor == 0) Flavor = "eem";
         if(iFlavor == 1) Flavor = "emm";
         if(iFlavor == 2) Flavor = "eee";
         if(iFlavor == 3) Flavor = "mmm";
         TString HistName = "FakeMatrix_" + Flavor + "_" + (int)Lep1_bin + "_" + (int)Lep2_bin + "_" + (int)Lep3_bin + "_Thread" + (int)iThread;
         FakeMatrixMap[Index] = new TH2D(HistName, HistName, 7, 1, 7, 7, 1, 7);
         HistName = "InverseFakeMatrix_" + Flavor + "_" + (int)Lep1_bin + "_" + (int)Lep2_bin + "_" + (int)Lep3_bin + "_Thread" + (int)iThread;
         InverseFakeMatrixMap[Index] = new TH2D(HistName, HistName, 7, 1, 7, 7, 1, 7);

         if(iFlavor == 0){
           FakeEff[0] = ZElFakeEff;
           FakeEff[1] = ZElFakeEff;
           FakeEff[2] = WMuFakeEff;

           RealEff[0] = ZElRealEff;
           RealEff[1] = ZElRealEff;
           RealEff[2] = WMuRealEff;
         }
         if(Flavor == 1){
           FakeEff[0] = ZMuFakeEff;
           FakeEff[1] = ZMuFakeEff;
           FakeEff[2] = WElFakeEff;

           RealEff[0] = ZMuRealEff;
           RealEff[1] = ZMuRealEff;
           RealEff[2] = WElRealEff;
         }
         if(Flavor == 2){
           FakeEff[0] = ZElFakeEff;
           FakeEff[1] = ZElFakeEff;
           FakeEff[2] = WElFakeEff;

           RealEff[0] = ZElRealEff;
           RealEff[1] = ZElRealEff;
           RealEff[2] = WElRealEff;
         }
         if(Flavor == 3){
           FakeEff[0] = ZMuFakeEff;
           FakeEff[1] = ZMuFakeEff;
           FakeEff[2] = WMuFakeEff;

           RealEff[0] = ZMuRealEff;
           RealEff[1] = ZMuRealEff;
           RealEff[2] = WMuRealEff;
         }

         f1 = FakeEff[0]->GetBinContent(Lep1_bin);
         f2 = FakeEff[1]->GetBinContent(Lep2_bin);
         f3 = FakeEff[2]->GetBinContent(Lep3_bin);
         e1 = RealEff[0]->GetBinContent(Lep1_bin);
         e2 = RealEff[1]->GetBinContent(Lep2_bin);
         e3 = RealEff[2]->GetBinContent(Lep3_bin);

         f1bar = 1 - f1;
         f2bar = 1 - f2;
         f3bar = 1 - f3;
         e1bar = 1 - e1;
         e2bar = 1 - e2;
         e3bar = 1 - e3;

         FakeMatrixMap[Index]->SetBinContent(1, 1, e1 * e2 * e3);
         FakeMatrixMap[Index]->SetBinContent(1, 2, e1 * e2 * f3);
         FakeMatrixMap[Index]->SetBinContent(1, 3, e1 * f2 * e3);
         FakeMatrixMap[Index]->SetBinContent(1, 4, f1 * e2 * e3);
         FakeMatrixMap[Index]->SetBinContent(1, 5, e1 * f2 * f3);
         FakeMatrixMap[Index]->SetBinContent(1, 6, f1 * e2 * f3);
         FakeMatrixMap[Index]->SetBinContent(1, 7, f1 * f2 * e3);

         FakeMatrixMap[Index]->SetBinContent(2, 1, e1 * e2 * e3bar);
         FakeMatrixMap[Index]->SetBinContent(2, 2, e1 * e2 * f3bar);
         FakeMatrixMap[Index]->SetBinContent(2, 3, e1 * f2 * e3bar);
         FakeMatrixMap[Index]->SetBinContent(2, 4, f1 * e2 * e3bar);
         FakeMatrixMap[Index]->SetBinContent(2, 5, e1 * f2 * f3bar);
         FakeMatrixMap[Index]->SetBinContent(2, 6, f1 * e2 * f3bar);
         FakeMatrixMap[Index]->SetBinContent(2, 7, f1 * f2 * e3bar);

         FakeMatrixMap[Index]->SetBinContent(3, 1, e1 * e2bar * e3);
         FakeMatrixMap[Index]->SetBinContent(3, 2, e1 * e2bar * f3);
         FakeMatrixMap[Index]->SetBinContent(3, 3, e1 * f2bar * e3);
         FakeMatrixMap[Index]->SetBinContent(3, 4, f1 * e2bar * e3);
         FakeMatrixMap[Index]->SetBinContent(3, 5, e1 * f2bar * f3);
         FakeMatrixMap[Index]->SetBinContent(3, 6, f1 * e2bar * f3);
         FakeMatrixMap[Index]->SetBinContent(3, 7, f1 * f2bar * e3);

         FakeMatrixMap[Index]->SetBinContent(4, 1, e1bar * e2 * e3);
         FakeMatrixMap[Index]->SetBinContent(4, 2, e1bar * e2 * f3);
         FakeMatrixMap[Index]->SetBinContent(4, 3, e1bar * f2 * e3);
         FakeMatrixMap[Index]->SetBinContent(4, 4, f1bar * e2 * e3);
         FakeMatrixMap[Index]->SetBinContent(4, 5, e1bar * f2 * f3);
         FakeMatrixMap[Index]->SetBinContent(4, 6, f1bar * e2 * f3);
         FakeMatrixMap[Index]->SetBinContent(4, 7, f1bar * f2 * e3);

         FakeMatrixMap[Index]->SetBinContent(5, 1, e1 * e2bar * e3bar);
         FakeMatrixMap[Index]->SetBinContent(5, 2, e1 * e2bar * f3bar);
         FakeMatrixMap[Index]->SetBinContent(5, 3, e1 * f2bar * e3bar);
         FakeMatrixMap[Index]->SetBinContent(5, 4, f1 * e2bar * e3bar);
         FakeMatrixMap[Index]->SetBinContent(5, 5, e1 * f2bar * f3bar);
         FakeMatrixMap[Index]->SetBinContent(5, 6, f1 * e2bar * f3bar);
         FakeMatrixMap[Index]->SetBinContent(5, 7, f1 * f2bar * e3bar);

         FakeMatrixMap[Index]->SetBinContent(6, 1, e1bar * e2 * e3bar);
         FakeMatrixMap[Index]->SetBinContent(6, 2, e1bar * e2 * f3bar);
         FakeMatrixMap[Index]->SetBinContent(6, 3, e1bar * f2 * e3bar);
         FakeMatrixMap[Index]->SetBinContent(6, 4, f1bar * e2 * e3bar);
         FakeMatrixMap[Index]->SetBinContent(6, 5, e1bar * f2 * f3bar);
         FakeMatrixMap[Index]->SetBinContent(6, 6, f1bar * e2 * f3bar);
         FakeMatrixMap[Index]->SetBinContent(6, 7, f1bar * f2 * e3bar);

         FakeMatrixMap[Index]->SetBinContent(7, 1, e1bar * e2bar * e3);
         FakeMatrixMap[Index]->SetBinContent(7, 2, e1bar * e2bar * f3);
         FakeMatrixMap[Index]->SetBinContent(7, 3, e1bar * f2bar * e3);
         FakeMatrixMap[Index]->SetBinContent(7, 4, f1bar * e2bar * e3);
         FakeMatrixMap[Index]->SetBinContent(7, 5, e1bar * f2bar * f3);
         FakeMatrixMap[Index]->SetBinContent(7, 6, f1bar * e2bar * f3);
         FakeMatrixMap[Index]->SetBinContent(7, 7, f1bar * f2bar * e3);

         CalculateInverseMatrix(FakeMatrixMap[Index], InverseFakeMatrixMap[Index]);

         Index.clear();
       }
     }
   }
 }

}

void DataDriven::InputFakeEfficiency(TH1D* ElFakeEff, TH1D* MuFakeEff)
{
 this->ElFakeEff = ElFakeEff;
 this->MuFakeEff = MuFakeEff;
}

void DataDriven::InputRealEfficiency(TH1D* ElRealEff, TH1D* MuRealEff)
{
 this->ElRealEff = ElRealEff;
 this->MuRealEff = MuRealEff;
}

void DataDriven::InputFakeEfficiency(TH2D* ElFakeEff, TH2D* MuFakeEff)
{
 this->ElFakeEff2D = ElFakeEff;
 this->MuFakeEff2D = MuFakeEff;
}

void DataDriven::InputRealEfficiency(TH2D* ElRealEff, TH2D* MuRealEff)
{
 this->ElRealEff2D = ElRealEff;
 this->MuRealEff2D = MuRealEff;
}

void DataDriven::GetIndex(double par, int Flavor)
{
 if(Flavor == 11){
   int ibin = ElFakeEff->FindBin(par);

   f1 = ElFakeEff->GetBinContent(ibin);
   e1 = ElRealEff->GetBinContent(ibin);
 }
 else if(Flavor == 13){
   int ibin = MuFakeEff->FindBin(par);
   
   f1 = MuFakeEff->GetBinContent(ibin);
   e1 = MuRealEff->GetBinContent(ibin);
 }

 if(f1 < 0.0) f1 = 0.0;
 if(e1 < 0.0) e1 = 0.0;
 if(!isfinite(f1)) f1 = 0.0;
 if(!isfinite(e1)) e1 = 0.0;
}

void DataDriven::GetIndex2D(double par1, double par2, int Flavor)
{
 if(Flavor == 11){
   int ibin = ElFakeEff2D->FindBin(par1, par2);
   int ibinx = ibin % (ElFakeEff2D->GetNbinsX() + 2);
   int ibiny = ibin / (ElFakeEff2D->GetNbinsX() + 2);

   f1 = ElFakeEff2D->GetBinContent(ibinx, ibiny);
   e1 = ElRealEff2D->GetBinContent(ibinx, ibiny);
 }
 else if(Flavor == 13){
   int ibin = MuFakeEff2D->FindBin(par1, par2);
   int ibinx = ibin % (MuFakeEff2D->GetNbinsX() + 2);
   int ibiny = ibin / (MuFakeEff2D->GetNbinsX() + 2);

   f1 = MuFakeEff2D->GetBinContent(ibinx, ibiny);
   e1 = MuRealEff2D->GetBinContent(ibinx, ibiny);
 }

 if(f1 < 0.0) f1 = 0.0;
 if(e1 < 0.0) e1 = 0.0;
 if(!isfinite(f1)) f1 = 0.0;
 if(!isfinite(e1)) e1 = 0.0;
}

