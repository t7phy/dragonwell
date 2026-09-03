#include "FileForEPUMP/FileForEPUMP.h"

using namespace std;

FileForEPUMP::FileForEPUMP(const char* fileName)
{
 isSideband = false;
 isRebin = false;
 isAFB = false;
 isInputStaErr = false;
 isInputSysErr = false;
 isStatSmear = false;

 isInputCorrelationFile = false;
 CorrelationPlus = false;
 CorrelationZero = false;
 CorrelationMinus = false;

 Error_type = 1;
 myData.open((TString)fileName + ".data");
 myTheory.open((TString)fileName + ".theory");

 this->fileName = fileName;
}

FileForEPUMP::~FileForEPUMP()
{
}

void FileForEPUMP::SetAFB()
{
 isAFB = true;
}

void FileForEPUMP::SetSideband()
{
 isAFB = true;
 isSideband = true;

 cout<<"This is AFB sideband data"<<endl;
}

void FileForEPUMP::Rebin(int Nbin)
{
 isRebin = true;
 RebinType = 1;
 size = Nbin;
 cout<<"Histogram is rebined, RebinType = 1."<<endl;

 if(isInput) cout<<"WARNING: Rebin should be in front of input."<<endl;
}

void FileForEPUMP::Rebin(double *rebin, int Nbin)
{
 isRebin = true;
 RebinType = 2;
 xbins = rebin;
 size = Nbin;
 cout<<"Histogram is rebined, bin number = "<<size - 1<<endl;

 if(isInput) cout<<"WARNING: Rebin should be in front of input."<<endl;
}

void FileForEPUMP::RemoveSpecialBins(double left, double right)
{
 isRemoveBins = true;
 RemoveLeftBin = left;
 RemoveRightBin = right;
}

void FileForEPUMP::InputStaErr(double *myStaErr)
{
 isInputStaErr = true;
 StaErr = myStaErr;
}

void FileForEPUMP::InputSysErr(double *mySysErr)
{
 isInputSysErr = true;
 SysErr = mySysErr;
}

void FileForEPUMP::InputSysErr(vector<double> mySysErr)
{
 isInputSysErr = true;
 SysErr = new double[mySysErr.size()];

 for(int i = 0; i < mySysErr.size(); i++){
   SysErr[i] = mySysErr.at(i);
 }
}

void FileForEPUMP::InputCorrSysErr(double *myCorrSysErr, const char* CorrName)
{
 CountCorrSysErr++;

 isInputCorrSysErr = true;
 CorrSysErr[CountCorrSysErr] = myCorrSysErr;
 CorrSysName[CountCorrSysErr] = CorrName;
}

void FileForEPUMP::InputCorrSysErr(vector<double> myCorrSysErr, const char* CorrName)
{
 CountCorrSysErr++;

 isInputCorrSysErr = true;
 CorrSysErr[CountCorrSysErr] = new double[myCorrSysErr.size()];
 CorrSysName[CountCorrSysErr] = CorrName;

 for(int i = 0; i < myCorrSysErr.size(); i++){
   CorrSysErr[CountCorrSysErr][i] = myCorrSysErr.at(i);
 }

}

void FileForEPUMP::InputCorrelation(const char* rootName, const char* histName)
{
 Error_type = 2;
 isInputCorrelationFile = true;
 isInputCovarianceMatrix = false;

 CorrelationFile = new TFile(rootName);
 Correlation = (TH2D *)CorrelationFile->Get(histName);
}

void FileForEPUMP::InputCovarianceMatrix(const char* rootName, const char* histName)
{
 Error_type = 3;
 isInputCovarianceMatrix = true;
 isInputCorrelationFile = false;

 CovarianceFile = new TFile(rootName);
 CovarianceMatrix = (TH2D *)CovarianceFile->Get(histName);
}

void FileForEPUMP::InputCovarianceMatrix(TH2D* matrix)
{
 Error_type = 3;
 isInputCovarianceMatrix = true;
 CovarianceMatrix = matrix;
}

void FileForEPUMP::InputCorrelation(int iflag)
{
 Error_type = 2;
 isInputCorrelationFile = false;
 isInputCovarianceMatrix = false;

 if(iflag == 1) CorrelationPlus = true;
 if(iflag == 0) CorrelationZero = true;
 if(iflag == -1) CorrelationMinus = true;
}

void FileForEPUMP::InputData(const char* rootName, const char* histName, int iflag)
{
 isInput = true;

 file = new TFile(rootName);
 h1 = (TH1D *)file->Get(histName);

 if(isReweightStatistics) h1 = GenPseudodataNoFluc(CustomLuminosity, h1);

 if(isRebin && iflag == 1){
   if(RebinType == 1) h1->Rebin(size);
   if(RebinType == 2) h1 = (TH1D *)h1->Rebin(size - 1, "h1", xbins);
 }

}

void FileForEPUMP::InputData(const char* rootName, const char* histName1, const char* histName2, TString Process, int iflag)
{
 isInput = true;

 file = new TFile(rootName);
 h1 = (TH1D *)file->Get(histName1);
 h2 = (TH1D *)file->Get(histName2);

 if(isRebin && iflag == 1){
   if(RebinType == 1) h1->Rebin(size);
   if(RebinType == 1) h2->Rebin(size);
   if(RebinType == 2) h1 = (TH1D *)h1->Rebin(size - 1, "h1", xbins);
   if(RebinType == 2) h2 = (TH1D *)h2->Rebin(size - 1, "h2", xbins);
 }

 if(Process == "Add") h1->Add(h2);

}

void FileForEPUMP::InputData(const char* rootName, const char* histName1, const char* histName2, int iflag)
{
 isInput = true;

 file = new TFile(rootName);
 FZmass = (TH1D *)file->Get(histName1);
 BZmass = (TH1D *)file->Get(histName2);

 if(isRebin && iflag == 1){
   if(RebinType == 1) FZmass->Rebin(size);
   if(RebinType == 1) BZmass->Rebin(size);
   if(RebinType == 2) FZmass = (TH1D *)FZmass->Rebin(size - 1, "FZmass", xbins);
   if(RebinType == 2) BZmass = (TH1D *)BZmass->Rebin(size - 1, "BZmass", xbins);
 }

 isDataAFB = true;
 h1 = (TH1D *)FZmass->Clone("h1");
 h1->Reset();

}

void FileForEPUMP::InputData(const char* rootName1, const char* rootName2, const char* histName1, const char* histName2, const char* histName3, int iflag)
{
 isInput = true;

 file1 = new TFile(rootName1);
 file2 = new TFile(rootName2);
 Wplus = (TH1D *)file1->Get(histName1);
 Wminus = (TH1D *)file1->Get(histName2);
 ZRapidity = (TH1D *)file2->Get(histName3);

 if(isRebin && iflag == 1){
   if(RebinType == 1) Wplus->Rebin(size);
   if(RebinType == 1) Wminus->Rebin(size);
   if(RebinType == 1) ZRapidity->Rebin(size);
   if(RebinType == 2) Wplus = (TH1D *)Wplus->Rebin(size - 1, "Wplus", xbins);
   if(RebinType == 2) Wminus = (TH1D *)Wminus->Rebin(size - 1, "Wminus", xbins);
   if(RebinType == 2) ZRapidity = (TH1D *)ZRapidity->Rebin(size - 1, "ZRapidity", xbins);
 }

 isDataRefWZ = true;
 h1 = (TH1D *)Wplus->Clone("h1");
 h1->Reset();

}

void FileForEPUMP::Input2DData(const char* rootName, const char* histName1)
{
 isInput = true;
 isInput2D = true;

 file = new TFile(rootName);
 Hist2D_1 = (TH2D *)file->Get(histName1);

}

void FileForEPUMP::Input2DData(const char* rootName, const char* histName1, const char* histName2, TString Process)
{
 isInput = true;
 isInput2D = true;

 file = new TFile(rootName);
 Hist2D_1 = (TH2D *)file->Get(histName1);
 TH2D* h2 = (TH2D *)file->Get(histName2);

 if(Process == "Add") Hist2D_1->Add(h2);

}

void FileForEPUMP::Input2DData(const char* rootName, const char* histName, int ibin)
{
 isInput = true;

 file = new TFile(rootName);
 Hist2D_1 = (TH2D *)file->Get(histName);

 h1 = (TH1D *)Hist2D_1->ProjectionX("h1", ibin, ibin);

/* h1 = new TH1D("h1", "h1", Hist2D_1->GetNbinsX(), Hist2D_1->GetXaxis()->GetBinLowEdge(1), Hist2D_1->GetXaxis()->GetBinUpEdge(Hist2D_1->GetNbinsX()));

 for(int ibinx = 0; ibinx < Hist2D_1->GetNbinsX(); ibinx++){
   h1->SetBinContent(ibinx + 1, Hist2D_1->GetBinContent(ibinx + 1, ibin));
   h1->SetBinError(ibinx + 1, Hist2D_1->GetBinError(ibinx + 1, ibin));
 }
*/

}

void FileForEPUMP::Input2DData(const char* rootName, const char* histName, int ibinx, int ibiny)
{
 isInput = true;

 file = new TFile(rootName);
 Hist2D_1 = (TH2D *)file->Get(histName);

 if(ibinx == 0){
   h1 = (TH1D *)Hist2D_1->ProjectionX(Hist2D_1->GetName() + (TString)"_px_" + (int)ibiny, ibiny, ibiny);
 }

 if(ibiny == 0){
   h1 = (TH1D *)Hist2D_1->ProjectionY(Hist2D_1->GetName() + (TString)"_py_" + (int)ibinx, ibinx, ibinx);
 }
}

void FileForEPUMP::Input2DData(const char* rootName, const char* histName1, const char* histName2, int ibin, int iflag)
{
 isInput = true;

 file = new TFile(rootName);
 Hist2D_1 = (TH2D *)file->Get(histName1);
 Hist2D_2 = (TH2D *)file->Get(histName2);

 FZmass = new TH1D("FZmass", "FZmass", Hist2D_1->GetNbinsX(), Hist2D_1->GetXaxis()->GetBinLowEdge(1), Hist2D_1->GetXaxis()->GetBinUpEdge(Hist2D_1->GetNbinsX()));
 BZmass = new TH1D("BZmass", "BZmass", Hist2D_2->GetNbinsX(), Hist2D_2->GetXaxis()->GetBinLowEdge(1), Hist2D_2->GetXaxis()->GetBinUpEdge(Hist2D_2->GetNbinsX()));

 for(int ibinx = 0; ibinx < Hist2D_1->GetNbinsX(); ibinx++){
   FZmass->SetBinContent(ibinx + 1, Hist2D_1->GetBinContent(ibinx + 1, ibin));
   FZmass->SetBinError(ibinx + 1, Hist2D_1->GetBinError(ibinx + 1, ibin));

   BZmass->SetBinContent(ibinx + 1, Hist2D_2->GetBinContent(ibinx + 1, ibin));
   BZmass->SetBinError(ibinx + 1, Hist2D_2->GetBinError(ibinx + 1, ibin));
 }

 isDataAFB = true;
 h1 = (TH1D *)FZmass->Clone("h1");
 h1->Reset();

}

void FileForEPUMP::Input3DData(const char* rootName, const char* histName1)
{
 isInput = true;
 isInput3D = true;
 
 file = new TFile(rootName);
 Hist3D_1 = (TH3D *)file->Get(histName1);
 
}

void FileForEPUMP::Input3DData(const char* rootName, const char* histName1, int ibiny, int ibinz, int iflag)
{
 isInput = true;

 file = new TFile(rootName);
 Hist3D_1 = (TH3D *)file->Get(histName1);

 h1 = new TH1D("h1", "h1", Hist3D_1->GetNbinsX(), Hist3D_1->GetXaxis()->GetBinLowEdge(1), Hist3D_1->GetXaxis()->GetBinUpEdge(Hist3D_1->GetNbinsX()));

 for(int ibinx = 0; ibinx < Hist3D_1->GetNbinsX(); ibinx++){
   h1->SetBinContent(ibinx + 1, Hist3D_1->GetBinContent(ibinx + 1, ibiny, ibinz));
   h1->SetBinError(ibinx + 1, Hist3D_1->GetBinError(ibinx + 1, ibiny, ibinz));

 }

}

void FileForEPUMP::Input3DData(const char* rootName, const char* histName1, const char* histName2, int ibiny, int ibinz, int iflag)
{
 isInput = true;

 file = new TFile(rootName);
 Hist3D_1 = (TH3D *)file->Get(histName1);
 Hist3D_2 = (TH3D *)file->Get(histName2);

 FZmass = new TH1D("FZmass", "FZmass", Hist3D_1->GetNbinsX(), Hist3D_1->GetXaxis()->GetBinLowEdge(1), Hist3D_1->GetXaxis()->GetBinUpEdge(Hist3D_1->GetNbinsX()));
 BZmass = new TH1D("BZmass", "BZmass", Hist3D_2->GetNbinsX(), Hist3D_2->GetXaxis()->GetBinLowEdge(1), Hist3D_2->GetXaxis()->GetBinUpEdge(Hist3D_2->GetNbinsX()));

 for(int ibinx = 0; ibinx < Hist3D_1->GetNbinsX(); ibinx++){
   FZmass->SetBinContent(ibinx + 1, Hist3D_1->GetBinContent(ibinx + 1, ibiny, ibinz));
   FZmass->SetBinError(ibinx + 1, Hist3D_1->GetBinError(ibinx + 1, ibiny, ibinz));

   BZmass->SetBinContent(ibinx + 1, Hist3D_2->GetBinContent(ibinx + 1, ibiny, ibinz));
   BZmass->SetBinError(ibinx + 1, Hist3D_2->GetBinError(ibinx + 1, ibiny, ibinz));
 }

 isDataAFB = true;
 h1 = (TH1D *)FZmass->Clone("h1");
 h1->Reset();

}

/*void FileForEPUMP::InputData(const char* rootName1, const char* rootName2, const char* histName)
{
 file1 = new TFile(rootName1);
 file2 = new TFile(rootName2);
 FZmass = (TH1D *)file1->Get(histName);
 BZmass = (TH1D *)file2->Get(histName);
}
*/

void FileForEPUMP::InputTheory(vector<TString> rootNames, const char* histName)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos[ifile] = (TH1D *)files[ifile]->Get(histName);

   if(isReweightStatistics) histos[ifile] = GenPseudodataNoFluc(CustomLuminosity, histos[ifile], (TString)"Theory_" + (int)ifile);

   if(isRebin){
     if(RebinType == 1) histos[ifile]->Rebin(size);
     if(RebinType == 2) histos[ifile] = (TH1D *)histos[ifile]->Rebin(size - 1, "h1_" + (int)ifile, xbins);
   }

   v_histos.push_back(histos[ifile]);
 }
}

void FileForEPUMP::InputTheory(vector<TString> rootNames, const char* histName1, const char* histName2, TString Process)
{
 isInput = true;
 
 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos[ifile] = (TH1D *)files[ifile]->Get(histName1);
   TH1D* h2 = (TH1D *)files[ifile]->Get(histName2);

   if(isRebin){
     if(RebinType == 1) histos[ifile]->Rebin(size);
     if(RebinType == 1) h2->Rebin(size);
     if(RebinType == 2) histos[ifile] = (TH1D *)histos[ifile]->Rebin(size - 1, "h1_" + (int)ifile, xbins);
     if(RebinType == 2) h2 = (TH1D *)h2->Rebin(size - 1, "h2_" + (int)ifile, xbins);
   }

   if(Process == "Add") histos[ifile]->Add(h2);

   v_histos.push_back(histos[ifile]);
 } 
}  

void FileForEPUMP::InputTheory(vector<TString> rootNames, const char* histName1, const char* histName2)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames.at(ifile));
   histos1[ifile] = (TH1D *)files[ifile]->Get(histName1);
   histos2[ifile] = (TH1D *)files[ifile]->Get(histName2);
   if(isRebin){
     if(RebinType == 1) histos1[ifile]->Rebin(size);
     if(RebinType == 1) histos2[ifile]->Rebin(size);
     if(RebinType == 2) histos1[ifile] = (TH1D *)histos1[ifile]->Rebin(size - 1, "FZmass_" + (int)ifile, xbins);
     if(RebinType == 2) histos2[ifile] = (TH1D *)histos2[ifile]->Rebin(size - 1, "BZmass_" + (int)ifile, xbins);
   }

   histos[ifile] = (TH1D *)histos1[ifile]->Clone("TheoryHist_" + (int)ifile);
   histos[ifile]->Reset();

   v_histos.push_back(histos[ifile]);
   v_histos1.push_back(histos1[ifile]);
   v_histos2.push_back(histos2[ifile]);
 }

 isTheoryAFB = true;
}

void FileForEPUMP::InputTheory(vector<TString> rootNames1, vector<TString> rootNames2, const char* histName1, const char* histName2, const char* histName3)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames1.size(); ifile++){
   files1[ifile] = new TFile(rootNames1.at(ifile));
   files2[ifile] = new TFile(rootNames2.at(ifile));

   histos1[ifile] = (TH1D *)files1[ifile]->Get(histName1);
   histos2[ifile] = (TH1D *)files1[ifile]->Get(histName2);
   histos3[ifile] = (TH1D *)files2[ifile]->Get(histName3);

   if(isRebin){
     if(RebinType == 1) histos1[ifile]->Rebin(size);
     if(RebinType == 1) histos2[ifile]->Rebin(size);
     if(RebinType == 1) histos3[ifile]->Rebin(size);
     if(RebinType == 2) histos1[ifile] = (TH1D *)histos1[ifile]->Rebin(size - 1, "Wplus_" + (int)ifile, xbins);
     if(RebinType == 2) histos2[ifile] = (TH1D *)histos2[ifile]->Rebin(size - 1, "Wminus_" + (int)ifile, xbins);
     if(RebinType == 2) histos3[ifile] = (TH1D *)histos3[ifile]->Rebin(size - 1, "ZRapidity_" + (int)ifile, xbins);
   }

   histos[ifile] = (TH1D *)histos1[ifile]->Clone("TheoryHist_" + (int)ifile);
   histos[ifile]->Reset();

   v_histos.push_back(histos[ifile]);
   v_histos1.push_back(histos1[ifile]);
   v_histos2.push_back(histos2[ifile]);
   v_histos3.push_back(histos3[ifile]);
 }

 isTheoryRefWZ = true;
}

void FileForEPUMP::Input2DTheory(vector<TString> rootNames, const char* histName1)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos2d_1[ifile] = (TH2D *)files[ifile]->Get(histName1);

   v_histos2d.push_back(histos2d_1[ifile]);
 }

}

void FileForEPUMP::Input2DTheory(vector<TString> rootNames, const char* histName1, const char* histName2, TString Process)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos2d_1[ifile] = (TH2D *)files[ifile]->Get(histName1);
   TH2D* h2 = (TH2D *)files[ifile]->Get(histName2);

   if(Process == "Add") histos2d_1[ifile]->Add(h2);

   v_histos2d.push_back(histos2d_1[ifile]);
 }

}

void FileForEPUMP::Input2DTheory(vector<TString> rootNames, const char* histName, int ibin)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos2d_1[ifile] = (TH2D *)files[ifile]->Get(histName);

   histos[ifile] = (TH1D *)histos2d_1[ifile]->ProjectionX((TString)"FZmass_" + (int)ifile, ibin, ibin);

/*   histos[ifile] = new TH1D((TString)"FZmass_" + (int)ifile, (TString)"FZmass_" + (int)ifile, histos2d_1[ifile]->GetNbinsX(), histos2d_1[ifile]->GetXaxis()->GetBinLowEdge(1), histos2d_1[ifile]->GetXaxis()->GetBinUpEdge(histos2d_1[ifile]->GetNbinsX()));

   for(int ibinx = 0; ibinx < histos2d_1[ifile]->GetNbinsX(); ibinx++){
     histos[ifile]->SetBinContent(ibinx + 1, histos2d_1[ifile]->GetBinContent(ibinx + 1, ibin));
     histos[ifile]->SetBinError(ibinx + 1, histos2d_1[ifile]->GetBinError(ibinx + 1, ibin));
   }
*/
   v_histos.push_back(histos[ifile]);
 }

}

void FileForEPUMP::Input2DTheory(vector<TString> rootNames, const char* histName, int ibinx, int ibiny)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos2d_1[ifile] = (TH2D *)files[ifile]->Get(histName);

   if(ibinx == 0){
     histos[ifile] = (TH1D *)histos2d_1[ifile]->ProjectionX(histos2d_1[ifile]->GetName() + (TString)"_px_" + (int)ibiny + "_" + (int)ifile, ibiny, ibiny);
   }

   if(ibiny == 0){
     histos[ifile] = (TH1D *)histos2d_1[ifile]->ProjectionY(histos2d_1[ifile]->GetName() + (TString)"_py_" + (int)ibinx + "_" + (int)ifile, ibinx, ibinx);
   }

   v_histos.push_back(histos[ifile]);
 }

}

void FileForEPUMP::Input2DTheory(vector<TString> rootNames, const char* histName1, const char* histName2, int ibin)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos2d_1[ifile] = (TH2D *)files[ifile]->Get(histName1);
   histos2d_2[ifile] = (TH2D *)files[ifile]->Get(histName2);

   histos1[ifile] = new TH1D((TString)"FZmass_" + (int)ifile, (TString)"FZmass_" + (int)ifile, histos2d_1[ifile]->GetNbinsX(), histos2d_1[ifile]->GetXaxis()->GetBinLowEdge(1), histos2d_1[ifile]->GetXaxis()->GetBinUpEdge(histos2d_1[ifile]->GetNbinsX()));
   histos2[ifile] = new TH1D((TString)"BZmass_" + (int)ifile, (TString)"BZmass_" + (int)ifile, histos2d_2[ifile]->GetNbinsX(), histos2d_2[ifile]->GetXaxis()->GetBinLowEdge(1), histos2d_2[ifile]->GetXaxis()->GetBinUpEdge(histos2d_2[ifile]->GetNbinsX()));

   for(int ibinx = 0; ibinx < histos2d_1[ifile]->GetNbinsX(); ibinx++){
     histos1[ifile]->SetBinContent(ibinx + 1, histos2d_1[ifile]->GetBinContent(ibinx + 1, ibin));
     histos1[ifile]->SetBinError(ibinx + 1, histos2d_1[ifile]->GetBinError(ibinx + 1, ibin));

     histos2[ifile]->SetBinContent(ibinx + 1, histos2d_2[ifile]->GetBinContent(ibinx + 1, ibin));
     histos2[ifile]->SetBinError(ibinx + 1, histos2d_2[ifile]->GetBinError(ibinx + 1, ibin));
   }

   histos[ifile] = (TH1D *)histos1[ifile]->Clone("TheoryHist_" + (int)ifile);
   histos[ifile]->Reset();

   v_histos.push_back(histos[ifile]);
   v_histos1.push_back(histos1[ifile]);
   v_histos2.push_back(histos2[ifile]);
 }

 isTheoryAFB = true;
}

void FileForEPUMP::Input3DTheory(vector<TString> rootNames, const char* histName1)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos3d_1[ifile] = (TH3D *)files[ifile]->Get(histName1);

   v_histos3d.push_back(histos3d_1[ifile]);
 }

}

void FileForEPUMP::Input3DTheory(vector<TString> rootNames, const char* histName1, int ibiny, int ibinz)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos3d_1[ifile] = (TH3D *)files[ifile]->Get(histName1);

   histos[ifile] = new TH1D((TString)"h1_" + (int)ifile, (TString)"h1_" + (int)ifile, histos3d_1[ifile]->GetNbinsX(), histos3d_1[ifile]->GetXaxis()->GetBinLowEdge(1), histos3d_1[ifile]->GetXaxis()->GetBinUpEdge(histos3d_1[ifile]->GetNbinsX()));

   for(int ibinx = 0; ibinx < histos3d_1[ifile]->GetNbinsX(); ibinx++){
     histos[ifile]->SetBinContent(ibinx + 1, histos3d_1[ifile]->GetBinContent(ibinx + 1, ibiny, ibinz));
     histos[ifile]->SetBinError(ibinx + 1, histos3d_1[ifile]->GetBinError(ibinx + 1, ibiny, ibinz));

   }

   v_histos.push_back(histos[ifile]);
 }

}

void FileForEPUMP::Input3DTheory(vector<TString> rootNames, const char* histName1, const char* histName2, int ibiny, int ibinz)
{
 isInput = true;

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   files[ifile] = new TFile(rootNames[ifile]);
   histos3d_1[ifile] = (TH3D *)files[ifile]->Get(histName1);
   histos3d_2[ifile] = (TH3D *)files[ifile]->Get(histName2);

   histos1[ifile] = new TH1D((TString)"FZmass_" + (int)ifile, (TString)"FZmass_" + (int)ifile, histos3d_1[ifile]->GetNbinsX(), histos3d_1[ifile]->GetXaxis()->GetBinLowEdge(1), histos3d_1[ifile]->GetXaxis()->GetBinUpEdge(histos3d_1[ifile]->GetNbinsX()));
   histos2[ifile] = new TH1D((TString)"BZmass_" + (int)ifile, (TString)"BZmass_" + (int)ifile, histos3d_2[ifile]->GetNbinsX(), histos3d_2[ifile]->GetXaxis()->GetBinLowEdge(1), histos3d_2[ifile]->GetXaxis()->GetBinUpEdge(histos3d_2[ifile]->GetNbinsX()));

   for(int ibinx = 0; ibinx < histos3d_1[ifile]->GetNbinsX(); ibinx++){
     histos1[ifile]->SetBinContent(ibinx + 1, histos3d_1[ifile]->GetBinContent(ibinx + 1, ibiny, ibinz));
     histos1[ifile]->SetBinError(ibinx + 1, histos3d_1[ifile]->GetBinError(ibinx + 1, ibiny, ibinz));

     histos2[ifile]->SetBinContent(ibinx + 1, histos3d_2[ifile]->GetBinContent(ibinx + 1, ibiny, ibinz));
     histos2[ifile]->SetBinError(ibinx + 1, histos3d_2[ifile]->GetBinError(ibinx + 1, ibiny, ibinz));
   }

   histos[ifile] = (TH1D *)histos1[ifile]->Clone("TheoryHist_" + (int)ifile);
   histos[ifile]->Reset();

   v_histos.push_back(histos[ifile]);
   v_histos1.push_back(histos1[ifile]);
   v_histos2.push_back(histos2[ifile]);
 }

 isTheoryAFB = true;
}

void FileForEPUMP::InputTheory(vector<TString> rootNames1, vector<TString> rootNames2, const char* histName)
{
 for(int ifile = 0; ifile < rootNames1.size(); ifile++){
   files1[ifile] = new TFile(rootNames1[ifile]);
   files2[ifile] = new TFile(rootNames2[ifile]);
   histos1[ifile] = (TH1D *)files1[ifile]->Get(histName);
   histos2[ifile] = (TH1D *)files2[ifile]->Get(histName);

   if(isRebin){
     if(RebinType == 1) histos1[ifile]->Rebin(size);
     if(RebinType == 1) histos2[ifile]->Rebin(size);
     if(RebinType == 2) histos1[ifile] = (TH1D *)histos1[ifile]->Rebin(size - 1, "FZmass_" + (int)ifile, xbins);
     if(RebinType == 2) histos2[ifile] = (TH1D *)histos2[ifile]->Rebin(size - 1, "BZmass_" + (int)ifile, xbins);
   }

   histos[ifile] = (TH1D *)histos1[ifile]->Clone("TheoryHist_" + (int)ifile);
   histos[ifile]->Reset();

   v_histos.push_back(histos[ifile]);
   v_histos1.push_back(histos1[ifile]);
   v_histos2.push_back(histos2[ifile]);
 }

 isTheoryAFB = true;
}

void FileForEPUMP::InputTheory(PDFUncertainty *unc)
{
 isInput = true;

 if(!(unc->isInit)){
   cout<<"ERROR! Please input histograms for PDFUncertainty class at first."<<endl;
   return;
 }

 if(unc->isInit){
   if(unc->iflag == 1) v_histos = unc->hist_1d;
 }
}

void FileForEPUMP::InputTheory(TH1D *h1, int nSet)
{
 isInput = true;

 for(int i = 0; i < nSet; i++){
   v_histos.push_back(h1);
 }
}

void FileForEPUMP::InputTheory(vector<TH1D *> histos)
{
 isInput = true;

 v_histos = histos;
}

void FileForEPUMP::Input2DTheory(PDFUncertainty *unc)
{
 isInput = true;

 if(!(unc->isInit)){
   cout<<"ERROR! Please input histograms for PDFUncertainty class at first."<<endl;
   return;
 }

 if(unc->isInit){
   if(unc->iflag == 2) v_histos2d = unc->hist_2d;
 }
}

void FileForEPUMP::InputExtendedTheory(TString ParaName, vector<TString> rootNames, const char* histName)
{
 isInput = true;

 v_Extendedhistos[ParaName].resize(rootNames.size());

 for(int ifile = 0; ifile < rootNames.size(); ifile++){
   Extendedfiles[ifile] = new TFile(rootNames[ifile]);
   Extendedhistos[ifile] = (TH1D *)Extendedfiles[ifile]->Get(histName);

   if(isReweightStatistics) Extendedhistos[ifile] = GenPseudodataNoFluc(CustomLuminosity, Extendedhistos[ifile], (TString)"Theory_" + (int)ifile);

   if(isRebin){
     if(RebinType == 1) Extendedhistos[ifile]->Rebin(size);
     if(RebinType == 2) Extendedhistos[ifile] = (TH1D *)Extendedhistos[ifile]->Rebin(size - 1, "h1_" + (int)ifile, xbins);
   }

   v_Extendedhistos[ParaName].at(ifile) = Extendedhistos[ifile];
 }

 ParaNames.push_back(ParaName);
}

void FileForEPUMP::Normalization(int DataNormFactor, int TheoryNormFactor)
{
 if(isDataAFB || isTheoryAFB){
   cout<<"ERROR!! AFB cannot be normalized!"<<endl;
   return;
 }

 isNorm = true;

 this->DataNormFactor = DataNormFactor;
 this->TheoryNormFactor = TheoryNormFactor;

 DataCrossSection = h1->Integral();
 TheoryCrossSection = histos[0]->Integral();

 cout<<DataCrossSection<<endl;
 cout<<TheoryCrossSection<<endl;
}

void FileForEPUMP::SpecialStaError(double kFactor)
{
 StaErrorkFactor = kFactor;
}
 
void FileForEPUMP::writedata()
{
 doCallWriteData = true;

 this->DataNBin = 0;

 if(isDataAFB) AFBFunction(FZmass, BZmass, h1);
 if(isDataRefWZ) CalRefWZ(Wplus, Wminus, ZRapidity, h1);
 if(isNorm && !isStatSmear) h1->Scale((TheoryCrossSection / (double)TheoryNormFactor) / (DataCrossSection));
 if(isNorm && isStatSmear) h1->Scale(1 / (double)TheoryNormFactor);

 myData<<"* 2 NormError #_corr_sys     Ecm      |# grids|# KF|# col|"<<endl;
 myData<<"*  0.0          9         1960.0           888231"<<endl;

 if(Error_type == 1 || Error_type == 2){
   myData<<"# of corr_err   ,  Data Column,    StatErr Column,  UncSys Column,   corr_err Column"<<endl;
   if(CountCorrSysErr == 0) myData<<"      "<< (CountCorrSysErr + 2) <<"                  3             4                 6                 7"<<endl;
   if(CountCorrSysErr != 0) myData<<"      "<< (CountCorrSysErr) <<"                  3             4                 6                 7"<<endl;
   myData<<"left right DataPoint StatErr TotSys UncSys ";
   if(isInputCorrSysErr){
     for(int iCorr = 1; iCorr <= CountCorrSysErr; iCorr++){
       myData<<CorrSysName[iCorr]<<"  ";
     }
   }
   if(!isInputCorrSysErr) myData<<" Corr1 Corr2";
   myData<<endl;

   for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
     if(isSideband && (h1->GetXaxis()->GetBinLowEdge(ibin + 1) < 91.1876 && h1->GetXaxis()->GetBinUpEdge(ibin + 1) > 91.1876)) continue;
     if(isRemoveBins){
       if(fabs(h1->GetXaxis()->GetBinLowEdge(ibin + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibin + 1) - RemoveRightBin) < 0.000001) continue;
     }
     if(isSkipRange){
       if(h1->GetXaxis()->GetBinLowEdge(ibin + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibin + 1) < SkipRight) continue;
     }

     DataPoint = h1->GetBinContent(ibin+1) * DataPointkFactor;
     if(!isInputStaErr) StaError = h1->GetBinError(ibin+1) * StaErrorkFactor;
     if(isInputStaErr) StaError = StaErr[ibin];

     if(!isInputSysErr) UncError = 0;
     if(isInputSysErr) UncError = SysErr[ibin];

     DataWritenMap_1d[ibin + 1] = true;
     if(fabs(DataPoint)<1e-12 || !isfinite(DataPoint)){
       DataPoint=1E-12;
       StaError=1E-6;
       DataWritenMap_1d[ibin + 1] = false;
       continue;
     }

     if(DataOtherKFactor.size() != 0){
       DataPoint = DataPoint * DataOtherKFactor.at(ibin);
       StaError = StaError * DataOtherKFactor.at(ibin);
     }

     TotError = sqrt(StaError * StaError + UncError * UncError);

     Corr1 = 0;
     Corr2 = 0;

     myData<<setw(9) << *right << fixed << setprecision(3)<<h1->GetXaxis()->GetBinLowEdge(ibin + 1);
     myData<<setw(12) << *right << fixed << setprecision(3)<<h1->GetXaxis()->GetBinUpEdge(ibin + 1);
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<DataPoint;
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<StaError;
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<TotError;
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<UncError;
     this->DataNBin++;

     if(isInputCorrSysErr){
       for(int iCorr = 1; iCorr <= CountCorrSysErr; iCorr++){
//         Corr[iCorr] = CorrSysErr[iCorr][ibin] * 100 / DataPoint;
         Corr[iCorr] = CorrSysErr[iCorr][ibin];
         myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr[iCorr];
       }

     }
     if(!isInputCorrSysErr){
       myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr1;
       myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr2;
     }
     myData<<endl;

   }
 }

 if(Error_type == 2){
   myData<<"*: Correlation Matrix"<<endl;
   myData<<"#a        #b    CorrCoeff"<<endl;

   if(isInputCorrelationFile){
     for(int ibiny = 1; ibiny <= Correlation->GetNbinsY(); ibiny++){
       if(isRemoveBins){
         if(fabs(Correlation->GetYaxis()->GetBinLowEdge(ibiny + 1) - RemoveLeftBin) < 0.000001 && fabs(Correlation->GetYaxis()->GetBinUpEdge(ibiny + 1) - RemoveRightBin) < 0.000001) continue;
       }

       if(isSkipRange){
         if(Correlation->GetYaxis()->GetBinLowEdge(ibiny + 1) > SkipLeft && Correlation->GetYaxis()->GetBinUpEdge(ibiny + 1) < SkipRight) continue;
       }

       for(int ibinx = 1; ibinx <= Correlation->GetNbinsX(); ibinx++){
         if(isRemoveBins){
           if(fabs(Correlation->GetXaxis()->GetBinLowEdge(ibinx + 1) - RemoveLeftBin) < 0.000001 && fabs(Correlation->GetXaxis()->GetBinUpEdge(ibinx + 1) - RemoveRightBin) < 0.000001) continue;
         }

         if(isSkipRange){
           if(Correlation->GetXaxis()->GetBinLowEdge(ibinx + 1) > SkipLeft && Correlation->GetXaxis()->GetBinUpEdge(ibinx + 1) < SkipRight) continue;
         }

         if(ibinx >= ibiny){
           myData<<ibinx<<"  "<<ibiny<<"  "<<Correlation->GetBinContent(ibinx,ibiny)<<endl; 
         }
       }
     }
   }
   else if(isInputCovarianceMatrix){
     for(int ibiny = 1; ibiny <= CovarianceMatrix->GetNbinsY(); ibiny++){
       if(isRemoveBins){
         if(fabs(CovarianceMatrix->GetYaxis()->GetBinLowEdge(ibiny + 1) - RemoveLeftBin) < 0.000001 && fabs(CovarianceMatrix->GetYaxis()->GetBinUpEdge(ibiny + 1) - RemoveRightBin) < 0.000001) continue;
       }
       if(isSkipRange){
         if(CovarianceMatrix->GetYaxis()->GetBinLowEdge(ibiny + 1) > SkipLeft && CovarianceMatrix->GetYaxis()->GetBinUpEdge(ibiny + 1) < SkipRight) continue;
       }
       for(int ibinx = 1; ibinx <= CovarianceMatrix->GetNbinsX(); ibinx++){
         if(isRemoveBins){
           if(fabs(CovarianceMatrix->GetXaxis()->GetBinLowEdge(ibinx + 1) - RemoveLeftBin) < 0.000001 && fabs(CovarianceMatrix->GetXaxis()->GetBinUpEdge(ibinx + 1) - RemoveRightBin) < 0.000001) continue;
         }
         if(isSkipRange){
           if(CovarianceMatrix->GetXaxis()->GetBinLowEdge(ibinx + 1) > SkipLeft && CovarianceMatrix->GetXaxis()->GetBinUpEdge(ibinx + 1) < SkipRight) continue;
         }

         if(ibinx >= ibiny){
           if(ibinx == ibiny) StaCovariance = h1->GetBinError(ibinx) * StaErrorkFactor * h1->GetBinError(ibinx) * StaErrorkFactor;
           if(ibinx != ibiny) StaCovariance = 0;
           StaErrorX = h1->GetBinError(ibinx) * StaErrorkFactor;
           StaErrorY = h1->GetBinError(ibiny) * StaErrorkFactor;
           UncErrorX = sqrt(CovarianceMatrix->GetBinContent(ibinx, ibinx));
           UncErrorY = sqrt(CovarianceMatrix->GetBinContent(ibiny, ibiny));
           CorrelationCoefficient = (CovarianceMatrix->GetBinContent(ibinx, ibiny) + StaCovariance) / (sqrt(StaErrorX * StaErrorX + UncErrorX * UncErrorX) * sqrt(StaErrorY * StaErrorY + UncErrorY * UncErrorY));
           myData<<ibinx<<"  "<<ibiny<<"  "<<CorrelationCoefficient<<endl;
         }
       }
     }
   }
   else{
     for(int ibiny = 1; ibiny <= h1->GetNbinsX(); ibiny++){
       if(isRemoveBins){
         if(fabs(h1->GetXaxis()->GetBinLowEdge(ibiny + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibiny + 1) - RemoveRightBin) < 0.000001) continue;
       }
       if(isSkipRange){
         if(h1->GetXaxis()->GetBinLowEdge(ibiny + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibiny + 1) < SkipRight) continue;
       }
       for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
         if(isRemoveBins){
           if(fabs(h1->GetXaxis()->GetBinLowEdge(ibinx + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibinx + 1) - RemoveRightBin) < 0.000001) continue;
         }
         if(isSkipRange){
           if(h1->GetXaxis()->GetBinLowEdge(ibinx + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibinx + 1) < SkipRight) continue;
         }
         if(ibinx >= ibiny){
           if(CorrelationPlus) myData<<ibinx<<"  "<<ibiny<<"  "<<"1.0"<<endl;
           if(CorrelationZero){
             if(ibinx == ibiny)myData<<ibinx<<"  "<<ibiny<<"  "<<"1.0"<<endl;
             if(ibinx != ibiny)myData<<ibinx<<"  "<<ibiny<<"  "<<"0.0"<<endl;
           }
           if(CorrelationMinus){
             if(ibinx == ibiny)myData<<ibinx<<"  "<<ibiny<<"  "<<"1.0"<<endl;
             if(ibinx != ibiny)myData<<ibinx<<"  "<<ibiny<<"  "<<"-1.0"<<endl;
           }
         }
       }
     }
   }
   cout<<"The Correlation matrix has been writed"<<endl;
 }

 if(Error_type == 3){
   myData<<"Experimental Data Values"<<endl;

   for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
     if(isSideband && (h1->GetXaxis()->GetBinLowEdge(ibin + 1) < 91.1876 && h1->GetXaxis()->GetBinUpEdge(ibin + 1) > 91.1876)) continue;
     if(isRemoveBins){
       if(fabs(h1->GetXaxis()->GetBinLowEdge(ibin + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibin + 1) - RemoveRightBin) < 0.000001) continue;
     }
     if(isSkipRange){
       if(h1->GetXaxis()->GetBinLowEdge(ibin + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibin + 1) < SkipRight) continue;
     }

     DataPoint = h1->GetBinContent(ibin+1) * DataPointkFactor;
     myData<<DataPoint<<endl;
   }
   myData<<"*"<<endl;
   myData<<"* More comments here"<<endl;
   myData<<"*"<<endl;
   myData<<"Inverse Covariance Matrix:"<<endl;

   int EffectiveBins = 0;
   for(int ibiny = 1; ibiny <= CovarianceMatrix->GetNbinsY(); ibiny++){
     if(isRemoveBins){
       if(fabs(CovarianceMatrix->GetYaxis()->GetBinLowEdge(ibiny + 1) - RemoveLeftBin) < 1e-6 && fabs(CovarianceMatrix->GetYaxis()->GetBinUpEdge(ibiny + 1) - RemoveRightBin) < 1e-6) continue;
     }
     if(isSkipRange){
       if(CovarianceMatrix->GetYaxis()->GetBinLowEdge(ibiny + 1) > SkipLeft && CovarianceMatrix->GetYaxis()->GetBinUpEdge(ibiny + 1) < SkipRight) continue;
     }
     EffectiveBins++;
   }

   for(int ibinx = 1; ibinx <= CovarianceMatrix->GetNbinsX(); ibinx++){
     if(isRemoveBins){
       if(fabs(CovarianceMatrix->GetXaxis()->GetBinLowEdge(ibinx + 1) - RemoveLeftBin) < 1e-6 && fabs(CovarianceMatrix->GetXaxis()->GetBinUpEdge(ibinx + 1) - RemoveRightBin) < 1e-6) continue;
     }
     if(isSkipRange){
       if(CovarianceMatrix->GetXaxis()->GetBinLowEdge(ibinx + 1) > SkipLeft && CovarianceMatrix->GetXaxis()->GetBinUpEdge(ibinx + 1) < SkipRight) continue;
     }

     myData<<"a="<<ibinx<<", b="<<ibinx<<","<<EffectiveBins<<endl;

     for(int ibiny = ibinx; ibiny <= CovarianceMatrix->GetNbinsY(); ibiny++){
       if(isRemoveBins){
         if(fabs(CovarianceMatrix->GetYaxis()->GetBinLowEdge(ibiny + 1) - RemoveLeftBin) < 1e-6 && fabs(CovarianceMatrix->GetYaxis()->GetBinUpEdge(ibiny + 1) - RemoveRightBin) < 1e-6) continue;
       }
       if(isSkipRange){
         if(CovarianceMatrix->GetYaxis()->GetBinLowEdge(ibiny + 1) > SkipLeft && CovarianceMatrix->GetYaxis()->GetBinUpEdge(ibiny + 1) < SkipRight) continue;
       }

       myData<<scientific<<setprecision(5)<<CovarianceMatrix->GetBinContent(ibinx, ibiny)<<"   ";
     }
     myData<<endl;
   }
 }

 cout<<"The data has been writed"<<endl;

 if(file) delete file;
 if(file1) delete file1;
 if(file2) delete file2;
}

void FileForEPUMP::writedata(int FirstBin, int LastBin)
{
 doCallWriteData = true;

 this->DataNBin = 0;

 if(isDataAFB) AFBFunction(FZmass, BZmass, h1);
 if(isDataRefWZ) CalRefWZ(Wplus, Wminus, ZRapidity, h1);
 if(isNorm && !isStatSmear) h1->Scale((TheoryCrossSection / (double)TheoryNormFactor) / (DataCrossSection));
 if(isNorm && isStatSmear) h1->Scale(1 / (double)TheoryNormFactor);

 myData<<"* 2 NormError #_corr_sys     Ecm      |# grids|# KF|# col|"<<endl;
 myData<<"*  0.0          9         1960.0           888231"<<endl;

 if(Error_type == 1 || Error_type == 2){
   myData<<"# of corr_err   ,  Data Column,    StatErr Column,  UncSys Column,   corr_err Column"<<endl;
   if(CountCorrSysErr == 0) myData<<"      "<< (CountCorrSysErr + 2) <<"                  3             4                 6                 7"<<endl;
   if(CountCorrSysErr != 0) myData<<"      "<< (CountCorrSysErr) <<"                  3             4                 6                 7"<<endl;
   myData<<"left right DataPoint StatErr TotSys UncSys ";
   if(isInputCorrSysErr){
     for(int iCorr = 1; iCorr <= CountCorrSysErr; iCorr++){
       myData<<CorrSysName[iCorr]<<"  ";
     }
   }
   if(!isInputCorrSysErr) myData<<" Corr1 Corr2";
   myData<<endl;

   for(int ibin = FirstBin - 1; ibin <= LastBin - 1; ibin++){
     if(isSideband && (h1->GetXaxis()->GetBinLowEdge(ibin + 1) < 91.1876 && h1->GetXaxis()->GetBinUpEdge(ibin + 1) > 91.1876)) continue;
     if(isRemoveBins){
       if(fabs(h1->GetXaxis()->GetBinLowEdge(ibin + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibin + 1) - RemoveRightBin) < 0.000001) continue;
     }
     if(isSkipRange){
       if(h1->GetXaxis()->GetBinLowEdge(ibin + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibin + 1) < SkipRight) continue;
     }

     DataPoint = h1->GetBinContent(ibin+1) * DataPointkFactor;
     if(!isInputStaErr) StaError = h1->GetBinError(ibin+1) * StaErrorkFactor;
     if(isInputStaErr) StaError = StaErr[ibin];

     if(!isInputSysErr) UncError = 0;
     if(isInputSysErr) UncError = SysErr[ibin];

     if(fabs(DataPoint)<1e-12 || !isfinite(DataPoint)){
       DataPoint=1E-12;
       StaError=1E-6;
       continue;
     }

     TotError = sqrt(StaError * StaError + UncError * UncError);

     Corr1 = 0;
     Corr2 = 0;

     myData<<(h1->GetBinCenter(ibin+1) - h1->GetBinWidth(ibin+1) / 2)<<"  "<<(h1->GetBinCenter(ibin+1) + h1->GetBinWidth(ibin+1) / 2)<<"  "<<DataPoint<<"  "<<StaError<<"  "<<TotError<<"  "<<UncError<<"  ";
     this->DataNBin++;

     if(isInputCorrSysErr){
       for(int iCorr = 1; iCorr <= CountCorrSysErr; iCorr++){
//         Corr[iCorr] = CorrSysErr[iCorr][ibin] * 100 / DataPoint;
         Corr[iCorr] = CorrSysErr[iCorr][ibin];
         myData<<Corr[iCorr]<<"   ";
       }

     }
     if(!isInputCorrSysErr) myData<<Corr1<<"  "<<Corr2;
     myData<<endl;

   }
 }

}

void FileForEPUMP::write2Ddata()
{
 doCallWriteData = true;

 myData<<"* 2 NormError #_corr_sys     Ecm      |# grids|# KF|# col|"<<endl;
 myData<<"*  0.0          9         1960.0           888231"<<endl;
 myData<<"# of corr_err   ,  Data Column,    StatErr Column,  UncSys Column,   corr_err Column"<<endl;
 myData<<"      "<< (CountCorrSysErr + 2) <<"                  5             6                 8                 9"<<endl;
 myData<<"leftx  rightx  lefty  righty  DataPoint  StatErr  TotSys  UncSys ";
 if(isInputCorrSysErr){
   for(int iCorr = 1; iCorr <= CountCorrSysErr; iCorr++){
     myData<<CorrSysName[iCorr];
   }
 }
 myData<<" Corr1  Corr2"<<endl;

 for(int ibinx = 0; ibinx < Hist2D_1->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < Hist2D_1->GetNbinsY(); ibiny++){
     DataPoint = Hist2D_1->GetBinContent(ibinx + 1, ibiny + 1) * DataPointkFactor;
     if(!isInputStaErr) StaError = Hist2D_1->GetBinError(ibinx + 1, ibiny + 1) * StaErrorkFactor;
     //if(isInputStaErr) StaError = StaErr[ibin];
   
     if(!isInputSysErr) UncError = 0;
     //if(isInputSysErr) UncError = SysErr[ibin];
   
     DataWritenMap_2d[make_tuple(ibinx + 1, ibiny + 1)] = true;
     if(fabs(DataPoint)<1e-12){
       DataPoint=1E-12;
       StaError=1E-6;
       DataWritenMap_2d[make_tuple(ibinx + 1, ibiny + 1)] = false;
       continue;
     }

     if(isSkipRange){
       if(Hist2D_1->GetXaxis()->GetBinLowEdge(ibinx + 1) > xSkipLeft && Hist2D_1->GetXaxis()->GetBinUpEdge(ibinx + 1) < xSkipRight
       && Hist2D_1->GetYaxis()->GetBinLowEdge(ibiny + 1) > ySkipLeft && Hist2D_1->GetYaxis()->GetBinUpEdge(ibiny + 1) < ySkipRight) continue;
     }
   
     TotError = sqrt(StaError * StaError + UncError * UncError);
   
     Corr1 = 0;
     Corr2 = 0;

     myData<<setw(9) << *right << fixed << setprecision(3)<<Hist2D_1->GetXaxis()->GetBinLowEdge(ibinx + 1);
     myData<<setw(12) << *right << fixed << setprecision(3)<<Hist2D_1->GetXaxis()->GetBinUpEdge(ibinx + 1);
     myData<<setw(12) << *right << fixed << setprecision(3)<<Hist2D_1->GetYaxis()->GetBinLowEdge(ibiny + 1);
     myData<<setw(12) << *right << fixed << setprecision(3)<<Hist2D_1->GetYaxis()->GetBinUpEdge(ibiny + 1);
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<DataPoint;
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<StaError;
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<TotError;
     myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<UncError;
   
     if(!isInputCorrSysErr){
       myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr1;
       myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr2;
     }
     myData<<endl;   

   }
 }

 if(file) delete file;
 if(file1) delete file1;
 if(file2) delete file2;

}

void FileForEPUMP::write3Ddata()
{
 doCallWriteData = true;

 myData<<"* 2 NormError #_corr_sys     Ecm      |# grids|# KF|# col|"<<endl;
 myData<<"*  0.0          9         1960.0           888231"<<endl;
 myData<<"# of corr_err   ,  Data Column,    StatErr Column,  UncSys Column,   corr_err Column"<<endl;
 myData<<"      "<< (CountCorrSysErr + 2) <<"                  7             8                 10                 11"<<endl;
 myData<<"leftx  rightx  lefty  righty  leftz  rightz  DataPoint  StatErr  TotSys  UncSys ";
 if(isInputCorrSysErr){
   for(int iCorr = 1; iCorr <= CountCorrSysErr; iCorr++){
     myData<<CorrSysName[iCorr];
   }
 }
 myData<<" Corr1  Corr2"<<endl;

 for(int ibinx = 0; ibinx < Hist3D_1->GetNbinsX(); ibinx++){
   for(int ibiny = 0; ibiny < Hist3D_1->GetNbinsY(); ibiny++){
     for(int ibinz = 0; ibinz < Hist3D_1->GetNbinsZ(); ibinz++){
       DataPoint = Hist3D_1->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1) * DataPointkFactor;
       if(!isInputStaErr) StaError = Hist3D_1->GetBinError(ibinx + 1, ibiny + 1, ibinz + 1) * StaErrorkFactor;
       //if(isInputStaErr) StaError = StaErr[ibin];
   
       if(!isInputSysErr) UncError = 0;
       //if(isInputSysErr) UncError = SysErr[ibin];
   
       DataWritenMap_3d[make_tuple(ibinx + 1, ibiny + 1, ibinz + 1)] = true;
       if(fabs(DataPoint)<1e-12){
         DataPoint=1E-12;
         StaError=1E-6;
         DataWritenMap_3d[make_tuple(ibinx + 1, ibiny + 1, ibinz + 1)] = false;
         RemoveTag3D[make_tuple(ibinx + 1, ibiny + 1, ibinz + 1)] = true;
         continue;
       }
   
       TotError = sqrt(StaError * StaError + UncError * UncError);
   
       Corr1 = 0;
       Corr2 = 0;

       myData<<setw(9) << *right << fixed << setprecision(3)<<Hist3D_1->GetXaxis()->GetBinLowEdge(ibinx + 1);
       myData<<setw(12) << *right << fixed << setprecision(3)<<Hist3D_1->GetXaxis()->GetBinUpEdge(ibinx + 1);
       myData<<setw(12) << *right << fixed << setprecision(3)<<Hist3D_1->GetYaxis()->GetBinLowEdge(ibiny + 1);
       myData<<setw(12) << *right << fixed << setprecision(3)<<Hist3D_1->GetYaxis()->GetBinUpEdge(ibiny + 1);
       myData<<setw(12) << *right << fixed << setprecision(3)<<Hist3D_1->GetZaxis()->GetBinLowEdge(ibinz + 1);
       myData<<setw(12) << *right << fixed << setprecision(3)<<Hist3D_1->GetZaxis()->GetBinUpEdge(ibinz + 1);
       myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<DataPoint;
       myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<StaError;
       myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<TotError;
       myData<<setw(14) << *right << uppercase << scientific << setprecision(5)<<UncError;

       if(!isInputCorrSysErr){
         myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr1;
         myData<<setw(12) << *right << uppercase << scientific << setprecision(3)<<Corr2;
       }
       myData<<endl;
   
     }
   }
 }

 if(file) delete file;
 if(file1) delete file1;
 if(file2) delete file2;

}


void FileForEPUMP::writetheory()
{
 int TheoryNBin = 0;

 myTheory<<"Theory Column"<<endl;
 myTheory<<"      5"<<endl;

 for(int ifile = 0; ifile < v_histos.size(); ifile++){
   TheoryNBin = 0;

   if(isTheoryAFB) AFBFunction(v_histos1.at(ifile), v_histos2.at(ifile), v_histos.at(ifile));
   if(isTheoryRefWZ) CalRefWZ(v_histos1.at(ifile), v_histos2.at(ifile), v_histos3.at(ifile), v_histos.at(ifile));

   TH1D* h1 = v_histos.at(ifile);

   if(isNorm) h1->Scale(1 / (double)TheoryNormFactor);

   if(ifile<10) sprintf(pdfname," Data : If1363H.0%d.dta",ifile);
   else sprintf(pdfname," Data : If1363H.%d.dta",ifile);
   myTheory<<pdfname<<endl;

   for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
     if(isSideband && (h1->GetXaxis()->GetBinLowEdge(ibin + 1) < 91.1876 && h1->GetXaxis()->GetBinUpEdge(ibin + 1) > 91.1876)) continue;
     if(isRemoveBins){
       if(fabs(h1->GetXaxis()->GetBinLowEdge(ibin + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibin + 1) - RemoveRightBin) < 0.000001) continue;
     }
     if(isSkipRange){
       if(h1->GetXaxis()->GetBinLowEdge(ibin + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibin + 1) < SkipRight) continue;
     }

     DataPoint = h1->GetBinContent(ibin+1);

     if(!DataWritenMap_1d.at(ibin + 1)) continue;

     if(fabs(DataPoint)<1e-12){
       DataPoint=1E-12;
       continue;
     }

     TheoryNBin++;

     if(TheoryNBin > this->DataNBin){
       cout<<"WARNING! "<<fileName<<": The number of bin for theory "<<ifile<<" is not identical with the data. Remove the bin "<<ibin + 1<<endl;
       if(doCallWriteData) continue;
     }

     if(TheoryOtherKFactor.count(ifile) > 0){
       if(TheoryOtherKFactor.at(ifile).size() != 0){
         DataPoint = DataPoint * TheoryOtherKFactor.at(ifile).at(ibin);
       }
     }

     myTheory << setw(15) << scientific << uppercase << setprecision(3) << h1->GetXaxis()->GetBinLowEdge(ibin + 1);
     myTheory << setw(15) << scientific << uppercase << setprecision(3) << h1->GetXaxis()->GetBinUpEdge(ibin + 1);
     myTheory << setw(15) << scientific << uppercase << setprecision(3) << 0.0;
     myTheory << setw(15) << scientific << uppercase << setprecision(5) << 0.0;
     myTheory << setw(15) << scientific << uppercase << setprecision(5) << DataPoint;
     myTheory << endl;
   }
   if(TheoryNBin < this->DataNBin){
     cout<<"WARNING! "<<fileName<<": The number of bin for theory "<<ifile<<" is not identical with the data. "<<this->DataNBin - TheoryNBin<<" bin of theory is missed."<<endl;
   }
 }

 if(files[0]){
   for(int ifile = 0; ifile < v_histos.size(); ifile++){
     delete files[ifile];
   }
 }
 if(files1[0]){
   for(int ifile = 0; ifile < v_histos.size(); ifile++){
     delete files1[ifile];
   }
 }
 if(files2[0]){
   for(int ifile = 0; ifile < v_histos.size(); ifile++){
     delete files2[ifile];
   }
 }
}

void FileForEPUMP::writetheory(int FirstBin, int LastBin)
{
 int TheoryNBin = 0;

 myTheory<<"Theory Column"<<endl;
 myTheory<<"      5"<<endl;

 for(int ifile = 0; ifile < v_histos.size(); ifile++){
   TheoryNBin = 0;

   if(isTheoryAFB) AFBFunction(v_histos1.at(ifile), v_histos2.at(ifile), v_histos.at(ifile));
   if(isTheoryRefWZ) CalRefWZ(v_histos1.at(ifile), v_histos2.at(ifile), v_histos3.at(ifile), v_histos.at(ifile));

   TH1D* h1 = v_histos.at(ifile);

   if(isNorm) h1->Scale(1 / (double)TheoryNormFactor);

   if(ifile<10) sprintf(pdfname," Data : If1363H.0%d.dta",ifile);
   else sprintf(pdfname," Data : If1363H.%d.dta",ifile);
   myTheory<<pdfname<<endl;

   for(int ibin = FirstBin - 1; ibin <= LastBin - 1; ibin++){
     if(isSideband && (h1->GetXaxis()->GetBinLowEdge(ibin + 1) < 91.1876 && h1->GetXaxis()->GetBinUpEdge(ibin + 1) > 91.1876)) continue;
     if(isRemoveBins){
       if(fabs(h1->GetXaxis()->GetBinLowEdge(ibin + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibin + 1) - RemoveRightBin) < 0.000001) continue;
     }
     if(isSkipRange){
       if(h1->GetXaxis()->GetBinLowEdge(ibin + 1) > SkipLeft && h1->GetXaxis()->GetBinUpEdge(ibin + 1) < SkipRight) continue;
     }

     DataPoint = h1->GetBinContent(ibin+1);

     if(fabs(DataPoint)<0.00000001){
       DataPoint=1E-8;
       continue;
     }

     TheoryNBin++;

     if(TheoryNBin > this->DataNBin){
       cout<<"WARNING! "<<fileName<<": The number of bin for theory "<<ifile<<" is not identical with the data. Remove the bin "<<ibin + 1<<endl;
       if(doCallWriteData) continue;
     }

     myTheory << setw(15) << scientific << uppercase << setprecision(3) << h1->GetXaxis()->GetBinLowEdge(ibin + 1);
     myTheory << setw(15) << scientific << uppercase << setprecision(3) << h1->GetXaxis()->GetBinUpEdge(ibin + 1);
     myTheory << setw(15) << scientific << uppercase << setprecision(3) << 0.0;
     myTheory << setw(15) << scientific << uppercase << setprecision(5) << 0.0;
     myTheory << setw(15) << scientific << uppercase << setprecision(5) << DataPoint;
     myTheory << endl;
   }
   if(TheoryNBin < this->DataNBin){
     cout<<"WARNING! "<<fileName<<": The number of bin for theory "<<ifile<<" is not identical with the data. "<<this->DataNBin - TheoryNBin<<" bin of theory is missed."<<endl;
   }
 }

 if(files[0]){
   for(int ifile = 0; ifile < v_histos.size(); ifile++){
     delete files[ifile];
   }
 }
 if(files1[0]){
   for(int ifile = 0; ifile < v_histos.size(); ifile++){
     delete files1[ifile];
   }
 }
 if(files2[0]){
   for(int ifile = 0; ifile < v_histos.size(); ifile++){
     delete files2[ifile];
   }
 }

}

void FileForEPUMP::write2Dtheory()
{
 myTheory<<"Theory Column"<<endl;
 myTheory<<"      5"<<endl;

 for(int ifile = 0; ifile < v_histos2d.size(); ifile++){
   TH2D* h1 = v_histos2d.at(ifile);

   if(isNorm) h1->Scale(1 / (double)TheoryNormFactor);

   if(ifile<10) sprintf(pdfname, " Data : If1363H.0%d.dta", ifile);
   else sprintf(pdfname, " Data : If1363H.%d.dta", ifile);
   myTheory<<pdfname<<endl;

   for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++){
     for(int ibiny = 0; ibiny < h1->GetNbinsY(); ibiny++){

       DataPoint = h1->GetBinContent(ibinx + 1, ibiny + 1);

       if(!DataWritenMap_2d.at(make_tuple(ibinx + 1, ibiny + 1))) continue;

       if(fabs(DataPoint)<0.00000001){
         DataPoint=1E-8;
         continue;
       }

       if(isSkipRange){
         if(h1->GetXaxis()->GetBinLowEdge(ibinx + 1) > xSkipLeft && h1->GetXaxis()->GetBinUpEdge(ibinx + 1) < xSkipRight
         && h1->GetYaxis()->GetBinLowEdge(ibiny + 1) > ySkipLeft && h1->GetYaxis()->GetBinUpEdge(ibiny + 1) < ySkipRight) continue;
       }

       myTheory<<h1->GetXaxis()->GetBinLowEdge(ibinx + 1)<<"  "<<h1->GetXaxis()->GetBinUpEdge(ibinx + 1)<<"  "<<h1->GetYaxis()->GetBinLowEdge(ibiny + 1)<<"  "<<h1->GetYaxis()->GetBinUpEdge(ibiny + 1)<<"   "<<DataPoint<<endl;

     }
   }
 }
 if(files[0]){
   for(int ifile = 0; ifile < v_histos2d.size(); ifile++){
     delete files[ifile];
   }
 }
 if(files1[0]){
   for(int ifile = 0; ifile < v_histos2d.size(); ifile++){
     delete files1[ifile];
   }
 }
 if(files2[0]){
   for(int ifile = 0; ifile < v_histos2d.size(); ifile++){
     delete files2[ifile];
   }
 }

}

void FileForEPUMP::write3Dtheory()
{
 myTheory<<"Theory Column"<<endl;
 myTheory<<"      7"<<endl;

 for(int ifile = 0; ifile < v_histos3d.size(); ifile++){
   TH3D* h1 = v_histos3d.at(ifile);

   if(isNorm) h1->Scale(1 / (double)TheoryNormFactor);

   if(ifile<10) sprintf(pdfname, " Data : If1363H.0%d.dta", ifile);
   else sprintf(pdfname, " Data : If1363H.%d.dta", ifile);
   myTheory<<pdfname<<endl;

   for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++){
     for(int ibiny = 0; ibiny < h1->GetNbinsY(); ibiny++){
       for(int ibinz = 0; ibinz < h1->GetNbinsZ(); ibinz++){

         DataPoint = h1->GetBinContent(ibinx + 1, ibiny + 1, ibinz + 1);

         if(RemoveTag3D.count(make_tuple(ibinx + 1, ibiny + 1, ibinz + 1)) > 0){
           if(RemoveTag3D.at(make_tuple(ibinx + 1, ibiny + 1, ibinz + 1))) continue;
         }

         if(!DataWritenMap_3d.at(make_tuple(ibinx + 1, ibiny + 1, ibinz + 1))) continue;

         if(fabs(DataPoint)<0.00000001){
           DataPoint=1E-8;
           continue;
         }

         myTheory<<h1->GetXaxis()->GetBinLowEdge(ibinx + 1)<<"  "<<h1->GetXaxis()->GetBinUpEdge(ibinx + 1)<<"  "<<h1->GetYaxis()->GetBinLowEdge(ibiny + 1)<<"  "<<h1->GetYaxis()->GetBinUpEdge(ibiny + 1)<<"  "<<h1->GetZaxis()->GetBinLowEdge(ibinz + 1)<<"  "<<h1->GetZaxis()->GetBinUpEdge(ibinz + 1)<<"   "<<DataPoint<<endl;

       }
     }
   }
 }
 if(files[0]){
   for(int ifile = 0; ifile < v_histos3d.size(); ifile++){
     delete files[ifile];
   }
 }
 if(files1[0]){
   for(int ifile = 0; ifile < v_histos3d.size(); ifile++){
     delete files1[ifile];
   }
 }
 if(files2[0]){
   for(int ifile = 0; ifile < v_histos3d.size(); ifile++){
     delete files2[ifile];
   }
 }

}

void FileForEPUMP::writeExtendedtheory()
{
 for(int iPar = 0; iPar < ParaNames.size(); iPar++){
   ofstream ExtendedTheory;
    ExtendedTheory.open((TString)fileName + (TString)".theory." + ParaNames.at(iPar));

   ExtendedTheory<<"Theory Column"<<endl;
   ExtendedTheory<<"      1"<<endl;

   for(int ifile = 0; ifile < v_Extendedhistos[ParaNames.at(iPar)].size(); ifile++){
     TH1D* h1 = v_Extendedhistos[ParaNames.at(iPar)].at(ifile);
  
     if(isNorm) h1->Scale(1 / (double)TheoryNormFactor);
  
     if(ifile+1<10) sprintf(pdfname," Data : If1363H.0%d.dta",ifile+1);
     else sprintf(pdfname," Data : If1363H.%d.dta",ifile+1);
     ExtendedTheory<<pdfname<<endl;
  
     for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
       if(isSideband && (h1->GetXaxis()->GetBinLowEdge(ibin + 1) < 91.1876 && h1->GetXaxis()->GetBinUpEdge(ibin + 1) > 91.1876)) continue;
       if(isRemoveBins){
         if(fabs(h1->GetXaxis()->GetBinLowEdge(ibin + 1) - RemoveLeftBin) < 0.000001 && fabs(h1->GetXaxis()->GetBinUpEdge(ibin + 1) - RemoveRightBin) < 0.000001) continue;
       }
  
       DataPoint = h1->GetBinContent(ibin+1);
  
       if(fabs(DataPoint)<0.00000001){
         DataPoint=1E-8;
         continue;
       }
  
       ExtendedTheory<<DataPoint<<endl;
     }
   }
   ExtendedTheory.close();
 }

}

void FileForEPUMP::GetDataStaError()
{
 /************************************************/
 /*  Apply Gaussion Smearing on the data         */
 /*  Central value is from the theory prediction */
 /*  Stat. error is from the data                */
 /************************************************/

 isStatSmear = true;

 DataStaError1 = new double[1000];
 DataStaError2 = new double[1000];
 DataStaError3 = new double[1000];

 if(!isDataAFB && !isDataRefWZ && !isInput2D && !isInput3D){
   for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
     if(fabs(h1->GetBinContent(ibin + 1)) < 1e-10) DataStaError1[ibin] = 0.0;
     else DataStaError1[ibin] = h1->GetBinError(ibin + 1) / h1->GetBinContent(ibin + 1);
   }
   h1 = (TH1D *)(v_histos.at(0))->Clone("h1_SmearData");

   SmearHist(h1, DataStaError1);

   for(int ibin = 0; ibin < h1->GetNbinsX(); ibin++){
     h1->SetBinError(ibin + 1, DataStaError1[ibin] * h1->GetBinContent(ibin + 1));
   }

 }

 if(isInput2D){
//   DataStaError2D = new double* [1000];

//   for(int i = 0; i < 1000; i++){
//     DataStaError2D[i] = new double[1000];
//   }
   vector<vector<double>> DataStaError2D;
   vector<double> DataStaError;

   for(int ibinx = 0; ibinx < Hist2D_1->GetNbinsX(); ibinx++){
     DataStaError.clear();
     for(int ibiny = 0; ibiny < Hist2D_1->GetNbinsY(); ibiny++){
       double Error;
       if(fabs(Hist2D_1->GetBinContent(ibinx + 1, ibiny + 1)) < 1e-10) Error = 0.0;
       else Error = Hist2D_1->GetBinError(ibinx + 1, ibiny + 1) / Hist2D_1->GetBinContent(ibinx + 1, ibiny + 1);
       DataStaError.push_back(Error);
     }
     DataStaError2D.push_back(DataStaError);
   }
   Hist2D_1 = (TH2D *)(v_histos2d.at(0))->Clone("h2_SmearData");

   Smear2DHist(Hist2D_1, DataStaError2D);

   for(int ibinx = 0; ibinx < Hist2D_1->GetNbinsX(); ibinx++){
     for(int ibiny = 0; ibiny < Hist2D_1->GetNbinsY(); ibiny++){
       Hist2D_1->SetBinError(ibinx + 1, ibiny + 1, DataStaError2D.at(ibinx).at(ibiny) * Hist2D_1->GetBinContent(ibinx + 1, ibiny + 1));
     }
   }
 }

 if(isDataAFB){
   for(int ibin = 0; ibin < FZmass->GetNbinsX(); ibin++){
     DataStaError1[ibin] = FZmass->GetBinError(ibin + 1) / FZmass->GetBinContent(ibin + 1);
     DataStaError2[ibin] = BZmass->GetBinError(ibin + 1) / BZmass->GetBinContent(ibin + 1);
   }
   FZmass = (TH1D *)(v_histos1.at(0))->Clone("FZmass_SmearData");
   BZmass = (TH1D *)(v_histos2.at(0))->Clone("BZmass_SmearData");

   SmearHist(FZmass, DataStaError1);
   SmearHist(BZmass, DataStaError2);

   for(int ibin = 0; ibin < FZmass->GetNbinsX(); ibin++){
     FZmass->SetBinError(ibin + 1, DataStaError1[ibin] * FZmass->GetBinContent(ibin + 1));
     BZmass->SetBinError(ibin + 1, DataStaError2[ibin] * BZmass->GetBinContent(ibin + 1));
   }
 }

 if(isDataRefWZ){
   for(int ibin = 0; ibin < Wplus->GetNbinsX(); ibin++){
     DataStaError1[ibin] = Wplus->GetBinError(ibin + 1) / Wplus->GetBinContent(ibin + 1);
     DataStaError2[ibin] = Wminus->GetBinError(ibin + 1) / Wminus->GetBinContent(ibin + 1);
     DataStaError3[ibin] = ZRapidity->GetBinError(ibin + 1) / ZRapidity->GetBinContent(ibin + 1);
   }
   Wplus = (TH1D *)(v_histos1.at(0))->Clone("Wplus_SmearData");
   Wminus = (TH1D *)(v_histos2.at(0))->Clone("Wminus_SmearData");
   ZRapidity = (TH1D *)(v_histos3.at(0))->Clone("ZRapidity_SmearData");

   SmearHist(Wplus, DataStaError1);
   SmearHist(Wminus, DataStaError2);
   SmearHist(ZRapidity, DataStaError3);

   for(int ibin = 0; ibin < Wplus->GetNbinsX(); ibin++){
     Wplus->SetBinError(ibin + 1, DataStaError1[ibin] * Wplus->GetBinContent(ibin + 1));
     Wminus->SetBinError(ibin + 1, DataStaError2[ibin] * Wminus->GetBinContent(ibin + 1));
     ZRapidity->SetBinError(ibin + 1, DataStaError3[ibin] * ZRapidity->GetBinContent(ibin + 1));
   }
 }

}

void FileForEPUMP::InputOtherKFactor(TString path)
{
 ifstream kfactorfile(path);

 vector<vector<double>> KFactorTable;
 vector<TString> InputType;

 string FileLine;

 while(getline(kfactorfile, FileLine)){
   vector<double> LineVector;
   double Value;
   stringstream LineStream(FileLine);

   TString type;
   LineStream >> type;
   InputType.push_back(type);

   while(LineStream >> Value){
     LineVector.push_back(Value);
   }
   if(LineVector.size() == 0) break;

   KFactorTable.push_back(LineVector);//FullTable.at(i).at(j) is i row and j column
 }

 vector<OtherKFactor> OtherKFactorTable(KFactorTable.size());

 for(int i = 0; i < KFactorTable.size(); i++){
   if(InputType.at(i) == "Simple") OtherKFactorTable.at(i).type = KFactorType::Simple;
   else if(InputType.at(i) == "Linear") OtherKFactorTable.at(i).type = KFactorType::Linear;
   else if(InputType.at(i) == "Quadratic") OtherKFactorTable.at(i).type = KFactorType::Quadratic;

   OtherKFactorTable.at(i).parameters.resize(KFactorTable.at(i).size());
   for(int ip = 0; ip < KFactorTable.at(i).size(); ip++){
     OtherKFactorTable.at(i).parameters.at(ip) = KFactorTable.at(i).at(ip);
   }
 }

 OtherKFactorList.push_back(OtherKFactorTable);
}

void FileForEPUMP::ApplyOtherKFactor(int index, vector<double> zVec)
{
 if(zVec.size() != OtherKFactorList.size()) cout<<"ERROR! Input parameter list doesn't match with other kfactor list."<<endl;

 FinalOtherKFactor.resize(OtherKFactorList.at(0).size());
 for(int i = 0; i < FinalOtherKFactor.size(); i++) FinalOtherKFactor.at(i) = 1.0;

 for(int i = 0; i < OtherKFactorList.size(); i++){
   double z = zVec.at(i);

   for(int ipoint = 0; ipoint < OtherKFactorList.at(i).size(); ipoint++){
     if(OtherKFactorList.at(i).at(ipoint).type == KFactorType::Simple){
       FinalOtherKFactor.at(ipoint) *= OtherKFactorList.at(i).at(ipoint).parameters.at(0);
     }
     else if(OtherKFactorList.at(i).at(ipoint).type == KFactorType::Linear){
       double A = OtherKFactorList.at(i).at(ipoint).parameters.at(0);
       FinalOtherKFactor.at(ipoint) *= (1.0 + A * z);
     }
     else if(OtherKFactorList.at(i).at(ipoint).type == KFactorType::Quadratic){
       double A = OtherKFactorList.at(i).at(ipoint).parameters.at(0);
       double B = OtherKFactorList.at(i).at(ipoint).parameters.at(1);
       double C = OtherKFactorList.at(i).at(ipoint).parameters.at(2);
       FinalOtherKFactor.at(ipoint) *= (1.0 + A * z * z + B * z + C);
     }
   }
 }

 if(index < 0){
   DataOtherKFactor = FinalOtherKFactor;
 }
 else{
   TheoryOtherKFactor[index] = FinalOtherKFactor;
 }
}

void FileForEPUMP::End()
{
}
