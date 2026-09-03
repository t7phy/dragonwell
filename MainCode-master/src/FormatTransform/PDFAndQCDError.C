#include "FormatTransform/PDFAndQCDError.h"

PDFAndQCDError::PDFAndQCDError()
{
 InitialHistName();

}

PDFAndQCDError::~PDFAndQCDError()
{

}

void PDFAndQCDError::openFile(const char* FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void PDFAndQCDError::openHistFile(const char* FileName)
{
 HistFile = new TFile(FileName);
}

void PDFAndQCDError::openPDFHistFile(TString FileName, TString ProcessName, int size)
{
 this->ProcessName = ProcessName;

 TFile* file = new TFile(FileName + "_nominal.root");
 FileList.push_back(file);
 for(int iunc = 0; iunc < size; iunc++){
   TFile* file = new TFile(FileName + "_" + ProcessName + (int)iunc + ".root");
   FileList.push_back(file);
 }

}

void PDFAndQCDError::InitialHistName()
{
 HistNames.push_back("BDTScore");
 HistNames.push_back("BDTScoreSR");
 HistNames.push_back("DY_WZ");
 HistNames.push_back("DY_3Z");
 HistNames.push_back("Deep_DY_WZ_TT");
 HistNames.push_back("Deep_DY_3Z_TT");
 HistNames.push_back("Deep_DY_WZ_TT_DataSubtracted");
 HistNames.push_back("Deep_DY_3Z_TT_DataSubtracted");

 HistType["BDTScore"] = "WZMixed";
 HistType["BDTScoreSR"] = "WZMixed";
 HistType["DY_WZ"] = "WZMixed";
 HistType["DY_3Z"] = "WZMixed";
 HistType["Deep_DY_WZ_TT"] = "Single";
 HistType["Deep_DY_3Z_TT"] = "Single";
 HistType["Deep_DY_WZ_TT_DataSubtracted"] = "Single";
 HistType["Deep_DY_3Z_TT_DataSubtracted"] = "Single";

// HistNames.push_back("CosThetaV");
// HistNames.push_back("DeltaPhiLepWLepZ");
// HistNames.push_back("DeltaPhiLepWLepZWZFrame");
}

void PDFAndQCDError::InitialFileStructure()
{
 hf->cd();

 for(auto regionName : regionNames){
   for(auto ProcessName : ProcessNames){
     FillHist(regionName, ProcessName);
   }
 }

}

void PDFAndQCDError::FillHist(TString regionName, TString ProcessName)
{
 hf->cd();

 for(int ihist = 0; ihist < HistNames.size(); ihist++){
   Sta_HistNumber++;

   TH1D *HistData;
   if(regionName != "Single" && HistType[HistNames.at(ihist)] != "Single"){
     HistData = (TH1D *)FileList.at(0)->Get(HistNames.at(ihist) + "_Data" + regionName);
     HistData->Write();
     //delete HistData;
   }

   TString HistName;
   if(regionName != "Single" && HistType[HistNames.at(ihist)] != "Single") HistName = HistNames.at(ihist) + "_" + regionName;
   if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") HistName = HistNames.at(ihist);
   TString OriginalHistName = HistNames.at(ihist);
   cout<<"Hist "<<Sta_HistNumber<<": hist name: "<<HistName<<" region: "<<regionName<<" process: "<<ProcessName<<endl;

   HistVector.clear();
   for(int iunc = 0; iunc < FileList.size(); iunc++){

     if(ProcessName == "Polarized"){
       TH1D *HistLL = (TH1D *)FileList.at(iunc)->Get(HistName + "_LL");
       TH1D *HistLT = (TH1D *)FileList.at(iunc)->Get(HistName + "_LT");
       TH1D *HistTL = (TH1D *)FileList.at(iunc)->Get(HistName + "_TL");
       TH1D *HistTT = (TH1D *)FileList.at(iunc)->Get(HistName + "_TT");

       HistMerge = (TH1D *)HistLL->Clone(HistName + "_" + ProcessName);
       HistMerge->Add(HistLT);
       HistMerge->Add(HistTL);
       HistMerge->Add(HistTT);

       HistVector.push_back(HistMerge);

       delete HistLL;
       delete HistLT;
       delete HistTL;
       delete HistTT;

     }

     if(ProcessName == "WZQCD"){
       TH1D *HistTotal = (TH1D *)FileList.at(iunc)->Get(HistName + "_Total");

       HistMerge = (TH1D *)HistTotal->Clone(HistName + "_" + ProcessName);

       HistVector.push_back(HistMerge);

       delete HistTotal;

     }

     if(ProcessName == "Single"){
       if(HistType[OriginalHistName] == "Single"){
         if(regionName != "Single") continue;

         TH1D *Hist = (TH1D *)FileList.at(iunc)->Get(HistName);

         HistMerge = (TH1D *)Hist->Clone(HistName + "_" + ProcessName);

         HistVector.push_back(HistMerge);

       }
     }

     if(ProcessName == "WZMixed"){
       if(HistType[OriginalHistName] == "WZMixed"){
         if(regionName == "Single") continue;

         TH1D *HistLT = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_LT");
         TH1D *HistTL = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_TL");

         HistMerge = (TH1D *)HistLT->Clone(OriginalHistName + "_" + regionName + "_" + ProcessName);
         HistMerge->Add(HistTL);

         HistVector.push_back(HistMerge);

         HistName = OriginalHistName + "_" + regionName + "_WZMixed";

         delete HistLT;
         delete HistTL;

       }
     }

     if(ProcessName == "WZRest"){
       if(HistType[OriginalHistName] == "WZMixed"){
         if(regionName == "Single") continue;

         TH1D *HistLT = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_LT");
         TH1D *HistTL = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_TL");
         TH1D *HistTT = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_TT");

         HistMerge = (TH1D *)HistLT->Clone(OriginalHistName + "_" + regionName + "_" + ProcessName);
         HistMerge->Add(HistTL);
         HistMerge->Add(HistTT);

         HistVector.push_back(HistMerge);

         HistName = OriginalHistName + "_" + regionName + "_WZRest";

         delete HistLT;
         delete HistTL;

       }
     }

     if(ProcessName == "FinalTT"){
       if(regionName == "Single" || HistType[HistNames.at(ihist)] == "Single") continue;

       TH1D *HistBkgZZ = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_BkgZZ");
       TH1D *HistBkgVVV = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_BkgVVV");
       TH1D *HistBkgWZEW = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_BkgWZEW");
       TH1D *HistBkgttbarV = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_BkgttbarV");
       TH1D *HistFake = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_Fake");
       TH1D *HistLL = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_LL");
       TH1D *HistLT = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_LT");
       TH1D *HistTL = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_TL");

       HistMerge = (TH1D *)HistData->Clone(OriginalHistName + "_" + regionName + "_" + ProcessName);
       HistMerge->Add(HistBkgZZ, -1);
       HistMerge->Add(HistBkgVVV, -1);
       HistMerge->Add(HistBkgWZEW, -1);
       HistMerge->Add(HistBkgttbarV, -1);
       HistMerge->Add(HistFake, -1);
       HistMerge->Add(HistLL, -1);
       HistMerge->Add(HistLT, -1);
       HistMerge->Add(HistTL, -1);

       HistVector.push_back(HistMerge);

       HistName = OriginalHistName + "_" + regionName + "_FinalTT";

       delete HistBkgZZ;
       delete HistBkgVVV;
       delete HistBkgWZEW;
       delete HistBkgttbarV;
       delete HistFake;
       delete HistLL;
       delete HistLT;
       delete HistTL;
     }

     if(ProcessName != "Single" && ProcessName != "WZMixed" && ProcessName != "FinalTT" && ProcessName != "WZRest"){
       if(regionName == "Single") continue;
       if(HistType[OriginalHistName] == "Single") continue;

       TH1D *HistTotal = (TH1D *)FileList.at(iunc)->Get(OriginalHistName + "_" + regionName + "_" + ProcessName);

       HistMerge = (TH1D *)HistTotal->Clone(OriginalHistName + "_" + regionName + "_" + ProcessName);

       HistVector.push_back(HistMerge);

       HistName = OriginalHistName + "_" + regionName + "_" + ProcessName;

       delete HistTotal;

     }

   }

   HistName = HistName;
   if(HistVector.size() > 0) GetPDFAndQCDError(HistName, HistVector);
 }

}

void PDFAndQCDError::GetPDFAndQCDError(TString HistName, vector<TH1D *> HistVector)
{
 hf->cd();

 if(this->ProcessName == "PDF"){
   PDFUncertainty *unc = new PDFUncertainty();
   TH1D* PDFMerged;
   TH1D* PDFError;
   TH1D* PDFFinal;
//   unc->SaveVariBin();
//   unc->SaveMCVari();
   unc->Input1DPlot("MonteCarlo", HistVector, PDFError);

   PDFMerged = (TH1D *)HistVector.at(0)->Clone(HistName + "_PDFMerged");
   PDFFinal = (TH1D *)HistVector.at(0)->Clone(HistName);
   for(int ibin = 0; ibin < PDFMerged->GetNbinsX(); ibin++){
     PDFMerged->SetBinError(ibin + 1, PDFError->GetBinContent(ibin + 1));
     PDFFinal->SetBinContent(ibin + 1, PDFMerged->GetBinContent(ibin + 1) + PDFError->GetBinContent(ibin + 1));
   }
   PDFMerged->Write();
   PDFError->Write();
   PDFFinal->Write();

   delete PDFMerged;
   delete PDFError;
   delete PDFFinal;

   delete unc;
 }
 if(this->ProcessName == "QCD"){
   PDFUncertainty *unc = new PDFUncertainty();
   TH1D* ScaleMerged;
   TH1D* ScaleError;
   TH1D* ScaleFinal;
   unc->Input1DPlot("EnvelopNorm", HistVector, ScaleError);

   ScaleMerged = (TH1D *)HistVector.at(0)->Clone(HistName + "_ScaleMerged");
   ScaleFinal = (TH1D *)HistVector.at(0)->Clone(HistName);
   for(int ibin = 0; ibin < ScaleMerged->GetNbinsX(); ibin++){
     ScaleMerged->SetBinError(ibin + 1, ScaleError->GetBinContent(ibin + 1));
     ScaleFinal->SetBinContent(ibin + 1, ScaleMerged->GetBinContent(ibin + 1) + ScaleError->GetBinContent(ibin + 1));
   }
   ScaleMerged->Write();
   ScaleError->Write();
   ScaleFinal->Write();

   delete ScaleMerged;
   delete ScaleError;
   delete ScaleFinal;

   delete unc;
 }


}

void PDFAndQCDError::SaveFile()
{
 for(int iunc = 0; iunc < FileList.size(); iunc++){
   if(iunc == 0) cout<<"Close the File: MC_results_nominal.root"<<endl;
   if(iunc != 0) cout<<"Close the File: MC_results_"<<ProcessName<<iunc-1<<".root"<<endl;

   FileList.at(iunc)->Close();
   delete FileList.at(iunc);
 }

 hf->cd();

// hf->Write();
 hf->Close();
}

void PDFAndQCDError::LinkHist(HistsWZPolarization *myhists)
{
 this->fHist = myhists;
// this->HistNames = myhists->HistNames;
}
