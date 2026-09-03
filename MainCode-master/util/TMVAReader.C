#include "RootCommon.h"
#include "Tools/Tools.h"
#include "TMVAInterface/TMVAReader.h"
#include "TMinuitHelper/TMinuitHelper.h"

using namespace std;

TH1D* global_Signal;
TH1D* global_Background;
TH1D* global_Data;

double Min_Chi2 = 10000000.0;

void FittingWrapper(Int_t &npbar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
 TH1D* Signal = (TH1D *)global_Signal->Clone("Signal");
 TH1D* Background = (TH1D *)global_Background->Clone("Background");
 TH1D* Data = (TH1D *)global_Data->Clone("Data");

 Signal->Scale(par[0]);
 Background->Scale(1 - par[0]);

 TH1D* Total = (TH1D *)Signal->Clone("Total");
 Total->Add(Background);

 Total->Scale(Data->Integral() / Total->Integral());

 double Chi2 = CalculateChi2(Total, Data);

 f = Chi2;

 if(f < Min_Chi2) Min_Chi2 = f;
 cout<<"Min Chi2 = "<<Min_Chi2<<endl;

 delete Signal;
 delete Background;
 delete Data;
 delete Total;
}

int main(int argc, char** argv)
{
 TMVAReader* reader = new TMVAReader();

 reader->InputTree("class_data.root", "signal");
 reader->InputTree("class_data.root", "background");
 reader->InputTree("real_data.root", "data");

 reader->Initialize("Signal");
 reader->Initialize("Background");
 reader->Initialize("Data");

 reader->AddVariable("X1");
 reader->AddVariable("X2");

 reader->BookMVA("Signal", "BDT", "dataset/weights/BDTClassification_BDT.weights.xml");
 reader->BookMVA("Background", "BDT", "dataset/weights/BDTClassification_BDT.weights.xml");
 reader->BookMVA("Data", "BDT", "dataset/weights/BDTClassification_BDT.weights.xml");

 reader->DefineHist("Signal", 100, -1, 1);
 reader->DefineHist("Background", 100, -1, 1);
 reader->DefineHist("Data", 100, -1, 1);

 reader->LoopTrees("Signal", vector<pair<TString, TString>>{make_pair("class_data.root", "signal")});
 reader->LoopTrees("Background", vector<pair<TString, TString>>{make_pair("class_data.root", "background")});
 reader->LoopTrees("Data", vector<pair<TString, TString>>{make_pair("real_data.root", "data")});

 TFile *file = new TFile("save.root", "RECREATE");
 file->cd();

 TH1D* Signal = reader->RetrieveHist("Signal");
 TH1D* Background = reader->RetrieveHist("Background");
 TH1D* Data = reader->RetrieveHist("Data");

 global_Signal = Signal;
 global_Background = Background;
 global_Data = Data;

 TMinuitHelper *myMinuit = new TMinuitHelper(8);
 myMinuit->SetFCN(FittingWrapper);
 myMinuit->Input(1, "Signal", 0.5, 0.1, 0.0, 1.0);
 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 double* SPar = new double[1];
 double* SParError = new double[1];
 myMinuit->GetParametersAndError(SPar, SParError);

 Signal->Write();
 Background->Write();
 Data->Write();

// file->Write();
 file->Close();

 return 1;
}

