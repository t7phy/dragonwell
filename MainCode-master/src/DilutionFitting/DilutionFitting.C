#include "DilutionFitting/DilutionFitting.h"

DilutionFitting::DilutionFitting()
{

}

void DilutionFitting::GetAFBStwLinear()
{
 TString rootName;

 ifstream infile;
  infile.open("STWTemplate.list",ios::in);
 while(infile>>rootName){
  STWTemplates.push_back(rootName);
 }
 infile.close();

 for(int i = 0; i < 40; i++){
   STWInput[i] = 0.2255 + i * 0.0003;
 }

 int Index = 0;

 for(int i = FirstSTW; i < LastSTW; i++){

   FindSTW[STWInput[i]] = Index;
   Index++;

   STWFiles[i] = new TFile(STWTemplates.at(i));
 }

 for(int i = FirstSTW; i < LastSTW; i++){

   uuAFB[i] = (TH3D *)STWFiles[i]->Get(AFB_uu_Name);

   uuAFBs.push_back(uuAFB[i]);
 }

 for(int i = FirstSTW; i < LastSTW; i++){

   ddAFB[i] = (TH3D *)STWFiles[i]->Get(AFB_dd_Name);

   ddAFBs.push_back(ddAFB[i]);
 }

 uuSlopeAndOffset = new FitAFBStw();
 ddSlopeAndOffset = new FitAFBStw();

 uuSlopeAndOffset->Input(uuAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], uuLinearPlot, uuFittedSlope, uuFittedOffset);
 ddSlopeAndOffset->Input(ddAFBs, STWInput[FirstSTW], STWInput[LastSTW - 1], ddLinearPlot, ddFittedSlope, ddFittedOffset);

 for(int ibiny = 1; ibiny <= uuFittedSlope->GetNbinsY(); ibiny++){
   for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
     writefile->cd();

     uuFittedSlopeEnsemble[(vector<int>{ibiny, ibinz})] = uuFittedSlope->ProjectionX(uuFittedSlope->GetName() + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     uuFittedOffsetEnsemble[(vector<int>{ibiny, ibinz})] = uuFittedOffset->ProjectionX(uuFittedOffset->GetName() + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     ddFittedSlopeEnsemble[(vector<int>{ibiny, ibinz})] = ddFittedSlope->ProjectionX(ddFittedSlope->GetName() + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     ddFittedOffsetEnsemble[(vector<int>{ibiny, ibinz})] = ddFittedOffset->ProjectionX(ddFittedOffset->GetName() + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);

     uuFittedSlopeEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     uuFittedOffsetEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     ddFittedSlopeEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     ddFittedOffsetEnsemble[(vector<int>{ibiny, ibinz})]->Write();
   }
 }

 global_uuFittedSlopeEnsemble = &uuFittedSlopeEnsemble;
 global_uuFittedOffsetEnsemble = &uuFittedOffsetEnsemble;
 global_ddFittedSlopeEnsemble = &ddFittedSlopeEnsemble;
 global_ddFittedOffsetEnsemble = &ddFittedOffsetEnsemble;

 for(int i = FirstSTW; i < LastSTW; i++){
//   STWFiles[i]->Close();
   //delete STWFiles[i];
 }

// delete uuSlopeAndOffset;
// delete ddSlopeAndOffset;
}

void DilutionFitting::InitialData(TString DataName)
{
 this->DataName = DataName;

 TFile *DataFile = new TFile(DataName);

 TH3D *DataAFB = (TH3D *)DataFile->Get(AFBName);
 TH3D *Data_Dilution_uu = (TH3D *)DataFile->Get(Dilution_uu_Name);
 TH3D *Data_Dilution_dd = (TH3D *)DataFile->Get(Dilution_dd_Name);
 TH3D *Data_Delta_uu = (TH3D *)DataFile->Get(Delta_uu_Name);
 TH3D *Data_Delta_dd = (TH3D *)DataFile->Get(Delta_dd_Name);
 TH3D *Data_Pu = (TH3D *)DataFile->Get(AveDilution_uu_Name);
 TH3D *Data_Pd = (TH3D *)DataFile->Get(AveDilution_dd_Name);
 TH3D *Data_Xsec_uu = (TH3D *)DataFile->Get(Xsec_uu_Name);
 TH3D *Data_Xsec_dd = (TH3D *)DataFile->Get(Xsec_dd_Name);

 Data_Xsec_all = (TH3D *)DataFile->Get(Xsec_all_Name);

 TH3D *Data_uuRelativeXsec = (TH3D *)Data_Xsec_uu->Clone("uuRelativeXsec_Data");
 Data_uuRelativeXsec->Divide(Data_Xsec_all);

 TH3D *Data_ddRelativeXsec = (TH3D *)Data_Xsec_dd->Clone("ddRelativeXsec_Data");
 Data_ddRelativeXsec->Divide(Data_Xsec_all);

 for(int ibinx = 1; ibinx <= Data_Dilution_uu->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= Data_Dilution_uu->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= Data_Dilution_uu->GetNbinsZ(); ibinz++){
       double Value = 1.0 - 2.0 * Data_Dilution_uu->GetBinContent(ibinx, ibiny, ibinz);
       double Error = 2.0 * Data_Dilution_uu->GetBinError(ibinx, ibiny, ibinz);
       Data_Dilution_uu->SetBinContent(ibinx, ibiny, ibinz, Value);
       Data_Dilution_uu->SetBinError(ibinx, ibiny, ibinz, Error);
       Value = 1.0 - 2.0 * Data_Dilution_dd->GetBinContent(ibinx, ibiny, ibinz);
       Error = 2.0 * Data_Dilution_dd->GetBinError(ibinx, ibiny, ibinz);
       Data_Dilution_dd->SetBinContent(ibinx, ibiny, ibinz, Value);
       Data_Dilution_dd->SetBinError(ibinx, ibiny, ibinz, Error);
     }
   }
 }

 for(int ibiny = 1; ibiny <= DataAFB->GetNbinsY(); ibiny++){
   for(int ibinz = 1; ibinz <= DataAFB->GetNbinsZ(); ibinz++){
     writefile->cd();

     DataAFBEnsemble[(vector<int>{ibiny, ibinz})] = DataAFB->ProjectionX(DataAFB->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DataPuEnsemble[(vector<int>{ibiny, ibinz})] = Data_Pu->ProjectionX(Data_Pu->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DataPdEnsemble[(vector<int>{ibiny, ibinz})] = Data_Pd->ProjectionX(Data_Pd->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DataDeltauEnsemble[(vector<int>{ibiny, ibinz})] = Data_Delta_uu->ProjectionX(Data_Delta_uu->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DataDeltadEnsemble[(vector<int>{ibiny, ibinz})] = Data_Delta_dd->ProjectionX(Data_Delta_dd->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DatauuDilutionEnsemble[(vector<int>{ibiny, ibinz})] = Data_Dilution_uu->ProjectionX(Data_Dilution_uu->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DataddDilutionEnsemble[(vector<int>{ibiny, ibinz})] = Data_Dilution_dd->ProjectionX(Data_Dilution_dd->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DatauuRelativeXsecEnsemble[(vector<int>{ibiny, ibinz})] = Data_uuRelativeXsec->ProjectionX(Data_uuRelativeXsec->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
     DataddRelativeXsecEnsemble[(vector<int>{ibiny, ibinz})] = Data_ddRelativeXsec->ProjectionX(Data_ddRelativeXsec->GetName() + (TString)"_Data_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);

     DataAFBEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DataPuEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DataPdEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DataDeltauEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DataDeltadEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DatauuDilutionEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DataddDilutionEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DatauuRelativeXsecEnsemble[(vector<int>{ibiny, ibinz})]->Write();
     DataddRelativeXsecEnsemble[(vector<int>{ibiny, ibinz})]->Write();
   }
 }

 global_DataAFBEnsemble = &DataAFBEnsemble;
 global_DataPuEnsemble = &DataPuEnsemble;
 global_DataPdEnsemble = &DataPdEnsemble;
 global_DataDeltauEnsemble = &DataDeltauEnsemble;
 global_DataDeltadEnsemble = &DataDeltadEnsemble;
 global_DatauuDilutionEnsemble = &DatauuDilutionEnsemble;
 global_DataddDilutionEnsemble = &DataddDilutionEnsemble;
 global_DatauuRelativeXsecEnsemble = &DatauuRelativeXsecEnsemble;
 global_DataddRelativeXsecEnsemble = &DataddRelativeXsecEnsemble;

 cout<<"Initialize data finished."<<endl;

}

void DilutionFitting::OpenFile()
{
 writefile = new TFile("DilutionFitting.root", "RECREATE"); 
 writefile->cd();
}

void DilutionFitting::InitialTheory()
{
 TString rootName;

 ifstream infile;
  infile.open("theoryCC.list",ios::in);
 while(infile>>rootName){
  rootNames.push_back(rootName);
 }
 infile.close();

 for(int i = 0; i < rootNames.size(); i++){
   TFile* file = new TFile(rootNames.at(i));

   if(onlyCentral && i != 0) continue;

   //TH3D *DataAFB = (TH3D *)file->Get(AFBName);
   TH3D *Data_Dilution_uu = (TH3D *)file->Get(Dilution_uu_Name);
   TH3D *Data_Dilution_dd = (TH3D *)file->Get(Dilution_dd_Name);
   TH3D *Data_Delta_uu = (TH3D *)file->Get(Delta_uu_Name);
   TH3D *Data_Delta_dd = (TH3D *)file->Get(Delta_dd_Name);
   TH3D *Data_Pu = (TH3D *)file->Get(AveDilution_uu_Name);
   TH3D *Data_Pd = (TH3D *)file->Get(AveDilution_dd_Name);
   TH3D *Data_Xsec_uu = (TH3D *)file->Get(Xsec_uu_Name);
   TH3D *Data_Xsec_dd = (TH3D *)file->Get(Xsec_dd_Name);
   TH3D *Theory_Xsec_all = (TH3D *)file->Get(Xsec_all_Name);

   TH3D *Data_uuRelativeXsec = (TH3D *)Data_Xsec_uu->Clone((TString)"uuRelativeXsec_Theory_PDF" + (int)i);
   Data_uuRelativeXsec->Divide(Data_Xsec_all);

   TH3D *Data_ddRelativeXsec = (TH3D *)Data_Xsec_dd->Clone((TString)"ddRelativeXsec_Theory_PDF" + (int)i);
   Data_ddRelativeXsec->Divide(Data_Xsec_all);

   for(int ibinx = 1; ibinx <= Data_Dilution_uu->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= Data_Dilution_uu->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= Data_Dilution_uu->GetNbinsZ(); ibinz++){
         double Value = 1.0 - 2.0 * Data_Dilution_uu->GetBinContent(ibinx, ibiny, ibinz);
         double Error = 2.0 * Data_Dilution_uu->GetBinError(ibinx, ibiny, ibinz);
         Data_Dilution_uu->SetBinContent(ibinx, ibiny, ibinz, Value);
         Data_Dilution_uu->SetBinError(ibinx, ibiny, ibinz, Error);
         //if(ibiny == 2 && ibinz == 2) cout<<"Dilution uu bin "<<ibinx<<": "<<Data_Dilution_uu->GetBinContent(ibinx, 2, 2)<<endl;
         Value = 1.0 - 2.0 * Data_Dilution_dd->GetBinContent(ibinx, ibiny, ibinz);
         Error = 2.0 * Data_Dilution_dd->GetBinError(ibinx, ibiny, ibinz);
         Data_Dilution_dd->SetBinContent(ibinx, ibiny, ibinz, Value);
         Data_Dilution_dd->SetBinError(ibinx, ibiny, ibinz, Error);
         //if(ibiny == 2 && ibinz == 2) cout<<"Dilution dd bin "<<ibinx<<": "<<Data_Dilution_dd->GetBinContent(ibinx, 2, 2)<<endl;
       }
     }
   }

   for(int ibiny = 1; ibiny <= Data_Dilution_uu->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= Data_Dilution_uu->GetNbinsZ(); ibinz++){
       writefile->cd();

       //TheoryAFBEnsemble[(vector<int>{i, ibiny, ibinz})] = DataAFB->ProjectionX(DataAFB->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryPuEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_Pu->ProjectionX(Data_Pu->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryPdEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_Pd->ProjectionX(Data_Pd->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryDeltauEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_Delta_uu->ProjectionX(Data_Delta_uu->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryDeltadEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_Delta_dd->ProjectionX(Data_Delta_dd->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryuuDilutionEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_Dilution_uu->ProjectionX(Data_Dilution_uu->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryddDilutionEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_Dilution_dd->ProjectionX(Data_Dilution_dd->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryuuRelativeXsecEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_uuRelativeXsec->ProjectionX(Data_uuRelativeXsec->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);
       TheoryddRelativeXsecEnsemble[(vector<int>{i, ibiny, ibinz})] = Data_ddRelativeXsec->ProjectionX(Data_ddRelativeXsec->GetName() + (TString)"_Theory_PDF" + (int)i + (TString)"_py_" + (int)ibiny + (TString)"_pz_" + (int)ibinz, ibiny, ibiny, ibinz, ibinz);

       if(i == 0){
/*         TheoryPuEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryPdEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryDeltauEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryDeltadEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryuuDilutionEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryddDilutionEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryuuRelativeXsecEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryddRelativeXsecEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
*/       }
     }
   }
   if(i % 10 == 0) cout<<"No."<<i<<" Theory finished."<<endl;
 }

 global_TheoryAFBEnsemble = &TheoryAFBEnsemble;
 global_TheoryPuEnsemble = &TheoryPuEnsemble;
 global_TheoryPdEnsemble = &TheoryPdEnsemble;
 global_TheoryDeltauEnsemble = &TheoryDeltauEnsemble;
 global_TheoryDeltadEnsemble = &TheoryDeltadEnsemble;
 global_TheoryuuDilutionEnsemble = &TheoryuuDilutionEnsemble;
 global_TheoryddDilutionEnsemble = &TheoryddDilutionEnsemble;
 global_TheoryuuRelativeXsecEnsemble = &TheoryuuRelativeXsecEnsemble;
 global_TheoryddRelativeXsecEnsemble = &TheoryddRelativeXsecEnsemble;

 cout<<"Initialize theory finished."<<endl;
}

void DilutionFitting::InitialResult()
{
 for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
   writefile->cd();

   ResultPuEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Result_uu_QT" + (int)ibinz, (TString)"Result_uu_QT" + (int)ibinz, 4, 0, 4);
   ResultPdEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Result_dd_QT" + (int)ibinz, (TString)"Result_dd_QT" + (int)ibinz, 4, 0, 4);
   ResultStwEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Result_stw_QT" + (int)ibinz, (TString)"Result_stw_QT" + (int)ibinz, 4, 0, 4);
   ResultPuDeltaEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Delta_uu_QT" + (int)ibinz, (TString)"Delta_uu_QT" + (int)ibinz, 4, 0, 4);
   ResultPdDeltaEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Delta_dd_QT" + (int)ibinz, (TString)"Delta_dd_QT" + (int)ibinz, 4, 0, 4);
   ResultStwDeltaEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Delta_stw_QT" + (int)ibinz, (TString)"Delta_stw_QT" + (int)ibinz, 4, 0, 4);
   ResultPuDeltaMuncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"DeltaMunc_uu_QT" + (int)ibinz, (TString)"DeltaMunc_uu_QT" + (int)ibinz, 4, 0, 4);
   ResultPdDeltaMuncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"DeltaMunc_dd_QT" + (int)ibinz, (TString)"DeltaMunc_dd_QT" + (int)ibinz, 4, 0, 4);
   ResultStwDeltaMuncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"DeltaMunc_stw_QT" + (int)ibinz, (TString)"DeltaMunc_stw_QT" + (int)ibinz, 4, 0, 4);
   ResultPuFituncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Error_uu_QT" + (int)ibinz, (TString)"Error_uu_QT" + (int)ibinz, 4, 0, 4);
   ResultPdFituncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Error_dd_QT" + (int)ibinz, (TString)"Error_dd_QT" + (int)ibinz, 4, 0, 4);
   ResultStwFituncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"Error_stw_QT" + (int)ibinz, (TString)"Error_stw_QT" + (int)ibinz, 4, 0, 4);
   ResultPuPDFuncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"PDFunc_uu_QT" + (int)ibinz, (TString)"PDFunc_uu_QT" + (int)ibinz, 4, 0, 4);
   ResultPdPDFuncEnsemble[(vector<int>{ibinz})] = new TH1D((TString)"PDFunc_dd_QT" + (int)ibinz, (TString)"PDFunc_dd_QT" + (int)ibinz, 4, 0, 4);

   for(int i = 0; i < rootNames.size(); i++){
     writefile->cd();

     ResultPuDeltaMVariEnsemble[(vector<int>{i, ibinz})] = new TH1D((TString)"DeltaMVari_uu_PDF" + (int)i + (TString)"_QT" + (int)ibinz, (TString)"DeltaMVari_uu_PDF" + (int)i + (TString)"_QT" + (int)ibinz, 4, 0, 4);
     ResultPdDeltaMVariEnsemble[(vector<int>{i, ibinz})] = new TH1D((TString)"DeltaMVari_dd_PDF" + (int)i + (TString)"_QT" + (int)ibinz, (TString)"DeltaMVari_dd_PDF" + (int)i + (TString)"_QT" + (int)ibinz, 4, 0, 4);
     ResultStwDeltaMVariEnsemble[(vector<int>{i, ibinz})] = new TH1D((TString)"DeltaMVari_stw_PDF" + (int)i + (TString)"_QT" + (int)ibinz, (TString)"DeltaMVari_stw_PDF" + (int)i + (TString)"_QT" + (int)ibinz, 4, 0, 4);
   }
 }

 if(!onlyCentral){
   for(int ibiny = 1; ibiny <= 4; ibiny++){
     for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
       vector<TH1D *> PuTheory;
       vector<TH1D *> PdTheory;
       vector<TH1D *> DeltauTheory;
       vector<TH1D *> DeltadTheory;
       TH1D* PuError;
       TH1D* PdError;
       TH1D* DeltauError;
       TH1D* DeltadError;
       PDFUncertainty *unc_Pu = new PDFUncertainty();
       PDFUncertainty *unc_Pd = new PDFUncertainty();
       PDFUncertainty *unc_Deltau = new PDFUncertainty();
       PDFUncertainty *unc_Deltad = new PDFUncertainty();
       FileForEPUMP *file_Deltau = new FileForEPUMP((TString)"Deltau_ZY" + (int)ibiny + (TString)"_QT" + (int)ibinz);
       FileForEPUMP *file_Deltad = new FileForEPUMP((TString)"Deltad_ZY" + (int)ibiny + (TString)"_QT" + (int)ibinz);
       for(int i = 0; i < rootNames.size(); i++){
         PuTheory.push_back(TheoryPuEnsemble[(vector<int>{i, ibiny, ibinz})]);
         PdTheory.push_back(TheoryPdEnsemble[(vector<int>{i, ibiny, ibinz})]);
         DeltauTheory.push_back(TheoryDeltauEnsemble[(vector<int>{i, ibiny, ibinz})]);
         DeltadTheory.push_back(TheoryDeltadEnsemble[(vector<int>{i, ibiny, ibinz})]);
       }
       unc_Pu->Input1DPlot(ErrorType, PuTheory, PuError);
       unc_Pd->Input1DPlot(ErrorType, PdTheory, PdError);
       unc_Deltau->Input1DPlot(ErrorType, DeltauTheory, DeltauError);
       unc_Deltad->Input1DPlot(ErrorType, DeltadTheory, DeltadError);
       file_Deltau->InputData(TheoryDeltauEnsemble[(vector<int>{0, ibiny, ibinz})]);
       file_Deltau->InputTheory(unc_Deltau);
       file_Deltau->writedata();
       file_Deltau->writetheory();
       file_Deltad->InputData(TheoryDeltadEnsemble[(vector<int>{0, ibiny, ibinz})]);
       file_Deltad->InputTheory(unc_Deltad);
       file_Deltad->writedata();
       file_Deltad->writetheory();
       ResultPuPDFuncEnsemble[(vector<int>{ibinz})]->SetBinContent(ibiny, PuError->GetBinContent(1));
       ResultPuPDFuncEnsemble[(vector<int>{ibinz})]->SetBinError(ibiny, 0.0);
       ResultPdPDFuncEnsemble[(vector<int>{ibinz})]->SetBinContent(ibiny, PdError->GetBinContent(1));
       ResultPdPDFuncEnsemble[(vector<int>{ibinz})]->SetBinError(ibiny, 0.0);
       //Replace the Delta uncertainty to the PDF uncertainty
       for(int ibinx = 1; ibinx <= TheoryDeltauEnsemble[(vector<int>{0, ibiny, ibinz})]->GetNbinsX(); ibinx++){
         TheoryDeltauEnsemble[(vector<int>{0, ibiny, ibinz})]->SetBinError(ibinx, DeltauError->GetBinContent(ibinx));
         TheoryDeltadEnsemble[(vector<int>{0, ibiny, ibinz})]->SetBinError(ibinx, DeltadError->GetBinContent(ibinx));
       }
       ///////////////////////////////////////////////////////
       PuTheory.clear();
       PdTheory.clear();
       DeltauTheory.clear();
       DeltadTheory.clear();
       delete PuError;
       delete PdError;
       delete DeltauError;
       delete DeltadError;
       delete unc_Pu;
       delete unc_Pd;
       delete unc_Deltau;
       delete unc_Deltad;
       delete file_Deltau;
       delete file_Deltad;
     }
   }
   cout<<"Finished to calculate the original uncertainty on P0."<<endl;
 }

 for(int i = 0; i < rootNames.size(); i++){
   for(int ibiny = 1; ibiny <= uuFittedSlope->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
       writefile->cd();

       if(i == 0){
         TheoryPuEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryPdEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryDeltauEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryDeltadEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryuuDilutionEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryddDilutionEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryuuRelativeXsecEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
         TheoryddRelativeXsecEnsemble[(vector<int>{i, ibiny, ibinz})]->Write();
       }
     }
   }
 }

}

void DilutionFitting::UpdateDelta()
{
 ePumpHelper* EU = new ePumpHelper("test");
 EU->Update();

}

void DilutionFitting::Fitting(int iPDF, int iZY, int iQT)
{
 myMinuit = new TMinuitHelper(3);
 if(onlyCentral) iPDF = 0;
 global_iPDF = iPDF;
 global_iZY = iZY;
 global_iQT = iQT;
 myMinuit->SetFCN(udDilutionFitting);
 myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
 myMinuit->Input(1, "Pu", 0.2, 0.2, 0.0, 1.0);
 myMinuit->Input(2, "Pd", 0.2, 0.2, 0.0, 1.0);
 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 double* SPar = new double[3];
 double* SParError = new double[3];
 myMinuit->GetParametersAndError(SPar, SParError);
 cout<<"Fitted Pu: "<<SPar[1]<<" Delta: "<<SPar[1] - DataPuEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
 cout<<"Fitted Pd: "<<SPar[2]<<" Delta: "<<SPar[2] - DataPdEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
 cout<<"Fitted Pu Error: "<<SParError[1]<<" Fitted Pd Error: "<<SParError[2]<<endl;
 cout<<"Correlation between parameters: "<<myMinuit->GetCorrelation(2, 3)<<endl;

 ResultPuEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SPar[1]);
 ResultPuEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SPar[2]);
 ResultPdEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SPar[0]);
 ResultStwEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPuDeltaEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, fabs(SPar[1] - DataPuEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)));
 ResultPuDeltaEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdDeltaEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, fabs(SPar[2] - DataPdEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)));
 ResultPdDeltaEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwDeltaEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, fabs(SPar[0] - 0.2315));
 ResultStwDeltaEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPuFituncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SParError[1]);
 ResultPuFituncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdFituncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SParError[2]);
 ResultPdFituncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwFituncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SParError[0]);
 ResultStwFituncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);

 delete myMinuit;

 MinChi2 = 100000.0;
}

void DilutionFitting::FittingCorr(int iZY, int iQT)
{
 myMinuit = new TMinuitHelper(3);
 global_iZY = iZY;
 global_iQT = iQT;
 myMinuit->SetFCN(udDilutionFittingPDF);
 myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
 myMinuit->Input(1, "Pu", 0.2, 0.2, 0.0, 1.0);
 myMinuit->Input(2, "Pd", 0.2, 0.2, 0.0, 1.0);
 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 double* SPar = new double[3];
 double* SParError = new double[3];
 myMinuit->GetParametersAndError(SPar, SParError);
 cout<<"Fitted Pu: "<<SPar[1]<<" Delta: "<<SPar[1] - DataPuEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
 cout<<"Fitted Pd: "<<SPar[2]<<" Delta: "<<SPar[2] - DataPdEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
 cout<<"Fitted Pu Error: "<<SParError[1]<<" Fitted Pd Error: "<<SParError[2]<<endl;
 cout<<"Correlation between parameters: "<<myMinuit->GetCorrelation(2, 3)<<endl;

/* ResultPuEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SPar[1]);
 ResultPuEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SPar[2]);
 ResultPdEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SPar[0]);
 ResultStwEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPuDeltaEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, fabs(SPar[1] - DataPuEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)));
 ResultPuDeltaEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdDeltaEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, fabs(SPar[2] - DataPdEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)));
 ResultPdDeltaEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwDeltaEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, fabs(SPar[0] - 0.2315));
 ResultStwDeltaEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPuFituncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SParError[1]);
 ResultPuFituncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdFituncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SParError[2]);
 ResultPdFituncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwFituncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, SParError[0]);
 ResultStwFituncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
*/
 ResultPuDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, sqrt(SParError[1] * SParError[1] - ResultPuFituncEnsemble[(vector<int>{iQT})]->GetBinContent(iZY) * ResultPuFituncEnsemble[(vector<int>{iQT})]->GetBinContent(iZY)));
 ResultPuDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, sqrt(SParError[2] * SParError[2] - ResultPdFituncEnsemble[(vector<int>{iQT})]->GetBinContent(iZY) * ResultPdFituncEnsemble[(vector<int>{iQT})]->GetBinContent(iZY)));
 ResultPdDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, sqrt(SParError[0] * SParError[0] - ResultStwFituncEnsemble[(vector<int>{iQT})]->GetBinContent(iZY) * ResultStwFituncEnsemble[(vector<int>{iQT})]->GetBinContent(iZY)));
 ResultStwDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);

 delete myMinuit;

 MinChi2 = 100000.0;
}

void DilutionFitting::LinearFitting(int iPDF, int iZY, int iQT)
{
 myMinuit = new TMinuitHelper(5);
 if(onlyCentral) iPDF = 0;
 global_iPDF = iPDF;
 global_iZY = iZY;
 global_iQT = iQT;
 myMinuit->SetFCN(LinearDilutionFitting);
 myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
 myMinuit->Input(1, "Pu", 0.2, 0.2, 0.0, 1.0);
 myMinuit->Input(2, "Pd", 0.2, 0.2, 0.0, 1.0);
 myMinuit->Input(3, "uSlope", 0.0, 0.005, -0.01, 0.01);
 myMinuit->Input(4, "dSlope", 0.0, 0.005, -0.01, 0.01);
 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 double* SPar = new double[5];
 double* SParError = new double[5];
 myMinuit->GetParametersAndError(SPar, SParError);
 cout<<"Fitted Pu: "<<SPar[1]<<" Delta: "<<SPar[1] - DataPuEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
 cout<<"Fitted Pd: "<<SPar[2]<<" Delta: "<<SPar[2] - DataPdEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
 cout<<"Fitted Pu Error: "<<SParError[1]<<" Fitted Pd Error: "<<SParError[2]<<endl;
 double DatauSlope = (DatauuDilutionEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(DatauuDilutionEnsemble[(vector<int>{iZY, iQT})]->GetNbinsX()) - DatauuDilutionEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)) / (DatauuDilutionEnsemble[(vector<int>{iZY, iQT})]->GetXaxis()->GetBinCenter(DatauuDilutionEnsemble[(vector<int>{iZY, iQT})]->GetNbinsX()) - DatauuDilutionEnsemble[(vector<int>{iZY, iQT})]->GetXaxis()->GetBinCenter(1));
 double DatadSlope = (DataddDilutionEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(DataddDilutionEnsemble[(vector<int>{iZY, iQT})]->GetNbinsX()) - DataddDilutionEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)) / (DataddDilutionEnsemble[(vector<int>{iZY, iQT})]->GetXaxis()->GetBinCenter(DataddDilutionEnsemble[(vector<int>{iZY, iQT})]->GetNbinsX()) - DataddDilutionEnsemble[(vector<int>{iZY, iQT})]->GetXaxis()->GetBinCenter(1));
 cout<<"Fitted uSlope: "<<SPar[3]<<" Delta: "<<SPar[3] - DatauSlope<<endl;
 cout<<"Fitted dSlope: "<<SPar[4]<<" Delta: "<<SPar[4] - DatadSlope<<endl;
 cout<<"Fitted uSlope Error: "<<SParError[3]<<" Fitted dSlope Error: "<<SParError[4]<<endl;
 cout<<"Correlation between parameters: "<<myMinuit->GetCorrelation(2, 3)<<endl;
}

void DilutionFitting::DeltaInducedUnc(int iZY, int iQT)
{
 if(onlyCentral) return;

 for(int i = 0; i < rootNames.size(); i++){
   myMinuit = new TMinuitHelper(3);
   global_iPDF = i;
   global_iZY = iZY;
   global_iQT = iQT;
   myMinuit->SetFCN(udDilutionFitting);
   myMinuit->Input(0, "Stw", 0.2315, 0.01, 0.22, 0.24);
   myMinuit->Input(1, "Pu", ResultPuEnsemble[(vector<int>{iQT})]->GetBinContent(iZY), 0.2, 0.0, 1.0);
   myMinuit->Input(2, "Pd", ResultPdEnsemble[(vector<int>{iQT})]->GetBinContent(iZY), 0.2, 0.0, 1.0);

//   myMinuit->Input(1, "Pu", ResultPuEnsemble[(vector<int>{iQT})]->GetBinContent(iZY), 0.0, 0.0, 1.0);
//   myMinuit->Input(2, "Pd", ResultPdEnsemble[(vector<int>{iQT})]->GetBinContent(iZY), 0.0, 0.0, 1.0);

   myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
   myMinuit->Exec("MIGRAD", 100000, 0.001);
   double* SPar = new double[3];
   double* SParError = new double[3];
   myMinuit->GetParametersAndError(SPar, SParError);
   cout<<"Fitted Pu: "<<SPar[1]<<" Delta: "<<SPar[1] - DataPuEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
   cout<<"Fitted Pd: "<<SPar[2]<<" Delta: "<<SPar[2] - DataPdEnsemble[(vector<int>{iZY, iQT})]->GetBinContent(1)<<endl;
   cout<<"Fitted Pu Error: "<<SParError[1]<<" Fitted Pd Error: "<<SParError[2]<<endl;
   cout<<"Correlation between parameters: "<<myMinuit->GetCorrelation(2, 3)<<endl;
  
   ResultPuDeltaMVariEnsemble[(vector<int>{i, iQT})]->SetBinContent(iZY, SPar[1]);
   ResultPuDeltaMVariEnsemble[(vector<int>{i, iQT})]->SetBinError(iZY, 0.0);
   ResultPdDeltaMVariEnsemble[(vector<int>{i, iQT})]->SetBinContent(iZY, SPar[2]);
   ResultPdDeltaMVariEnsemble[(vector<int>{i, iQT})]->SetBinError(iZY, 0.0);
   ResultStwDeltaMVariEnsemble[(vector<int>{i, iQT})]->SetBinContent(iZY, SPar[0]);
   ResultStwDeltaMVariEnsemble[(vector<int>{i, iQT})]->SetBinError(iZY, 0.0);

   delete myMinuit;

   MinChi2 = 100000.0;
   cout<<"No."<<i<<" DeltaM Fitting finished."<<endl;
 }

 writefile->cd();

 vector<TH1D *> PuTheory;
 vector<TH1D *> PdTheory;
 vector<TH1D *> StwTheory;
 TH1D* PuError;
 TH1D* PdError;
 TH1D* StwError;
 PDFUncertainty *unc_Pu = new PDFUncertainty();
 PDFUncertainty *unc_Pd = new PDFUncertainty();
 PDFUncertainty *unc_Stw = new PDFUncertainty();
 for(int i = 0; i < rootNames.size(); i++){
   PuTheory.push_back(ResultPuDeltaMVariEnsemble[(vector<int>{i, iQT})]);
   PdTheory.push_back(ResultPdDeltaMVariEnsemble[(vector<int>{i, iQT})]);
   StwTheory.push_back(ResultStwDeltaMVariEnsemble[(vector<int>{i, iQT})]);
 }
 //unc_Pu->SaveVariBin();
 unc_Pu->Input1DPlot("Symmetry", PuTheory, PuError);
 //unc_Pd->SaveVariBin();
 unc_Pd->Input1DPlot("Symmetry", PdTheory, PdError);
 //unc_Stw->SaveVariBin();
 unc_Stw->Input1DPlot("Symmetry", StwTheory, StwError);
 ResultPuDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, PuError->GetBinContent(iZY));
 ResultPuDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultPdDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, PdError->GetBinContent(iZY));
 ResultPdDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 ResultStwDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinContent(iZY, StwError->GetBinContent(iZY));
 ResultStwDeltaMuncEnsemble[(vector<int>{iQT})]->SetBinError(iZY, 0.0);
 PuTheory.clear();
 PdTheory.clear();
 StwTheory.clear();
 delete PuError;
 delete PdError;
 delete StwError;
 delete unc_Pu;
 delete unc_Pd;
 delete unc_Stw;

}

void DilutionFitting::GetStwCombinedError()
{
 double CombinedStw = 0.0;
 double CombinedStwErr = 0.0;
 double CombinedErr = 0.0;
 double CombinedNumer = 0.0;
 double CombinedErrNumer = 0.0;

 for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
   for(int ibiny = 1; ibiny <= 4; ibiny++){
     if(fabs(ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny)) > 1e-10) CombinedErr += 1.0 / (ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny) * ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny));
     if(fabs(ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny)) > 1e-10) CombinedNumer += ResultStwEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny) / (ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny) * ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny));
   }
 }
 CombinedStw = CombinedNumer / CombinedErr;
 CombinedStwErr = 1.0 / sqrt(CombinedErr);

 cout<<"Combined stw = "<<CombinedStw<<endl;
 cout<<"Combined stw fitting error = "<<CombinedStwErr<<endl;

 CombinedStwErr = 0.0;

 for(int ibinz = 1; ibinz <= uuFittedSlope->GetNbinsZ(); ibinz++){
   for(int ibiny = 1; ibiny <= 4; ibiny++){
     if(fabs(ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny)) > 1e-10) CombinedErrNumer += ResultStwDeltaMuncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny) / (ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny) * ResultStwFituncEnsemble[(vector<int>{ibinz})]->GetBinContent(ibiny));
   }
 }

 CombinedStwErr = CombinedErrNumer / CombinedErr;

 cout<<"Combined stw DeltaM error = "<<CombinedStwErr<<endl;

}
