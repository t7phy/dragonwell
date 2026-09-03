#include "RootCommon.h"
#include "ePumpHelper/ePumpHelper.h"
#include "Figure/Figure.h"
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnUserCovariance.h"
#include "Minuit2/MnSimplex.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnMinimize.h"
#include "Minuit2/MnFumiliMinimize.h"
#include "Minuit2/MnHesse.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MnContours.h"
#include "Minuit2/MnPlot.h"
#include "Minuit2/MnPrint.h"
#include "Tools/OptimizeBinning.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 2 && argc != 3){
   cout<<"Please usage: ./UpdatePDF filename [AlphaS filename]"<<endl;
   return 0;
 }

/* class OptimizeBinning : public ROOT::Minuit2::FCNBase
 {
  public:

  double MinChi2 = 10.0;

  ePumpHelper* EU;
  TRandom3 r;

  TFile* InputFile;
  TH1D* DataHist;
  vector<TH1D *> TheoryHist;
  int nBin = 0;
  int nCluster = 10;
  TString InputName = "test";
  void SetInputName(TString input){InputName = input;}

  TString HistName = "ATLAS_Mll_HighMass_FineBin_Pseudodata_CT18NNLO";

  function<pair<TH1D*, vector<TH1D *>>(vector<int>)> ClusterHistogram;

  ROOT::Minuit2::MnUserParameters upar;
  vector<double> InitialParameters = {};
  virtual void Input(TString name, double central, double step, double left, double right){
    upar.Add(name.Data(), central, step);
    upar.SetLimits(name.Data(), left, right);
  }

  void Initialize(int nCluster){
    EU = new ePumpHelper(InputName);
    EU->Initial();
    EU->TurnOffCorrelationCosine();

    InputFile = new TFile("Pseudodata_CT18NNLO.root");
    DataHist = (TH1D *)InputFile->Get(HistName + (TString)"_0");
    TheoryHist.resize(EU->NEV * 2 + 1);
    for(int i = 0; i < TheoryHist.size(); i++){
      TheoryHist.at(i) = (TH1D *)InputFile->Get(HistName + (TString)"_" + i);
    }

    nBin = DataHist->GetNbinsX();

    this->nCluster = nCluster;

    for(int i = 0; i < nCluster; i++){
      double input = r.Uniform(0.009, 0.1);
      Input((TString)"Cluster_" + (i + 1), input, 0.1, 0.0, 0.5);
    }

    ClusterHistogram = [&](vector<int> Clusters){
  
      int nBin = Clusters.size();
  
      TH1D* tmpDataHist = new TH1D("tmp_Data", "tmp_Data", nBin, 0, nBin);
      vector<TH1D *> tmpTheoryHist(EU->NEV * 2 + 1);
      for(int i = 0; i < tmpTheoryHist.size(); i++){
        tmpTheoryHist.at(i) = new TH1D((TString)"tmp_Theory_" + i, (TString)"tmp_Theory_" + i, nBin, 0, nBin);
      }
  
      int FirstBin = 0;
      for(int icluster = 0; icluster < Clusters.size(); icluster++){
        double Value = 0.0, Error = 0.0;
        for(int ibin = FirstBin + 1; ibin <= FirstBin + Clusters.at(icluster); ibin++){
          Value += DataHist->GetBinContent(ibin);
          Error += DataHist->GetBinError(ibin) * DataHist->GetBinError(ibin);
          tmpDataHist->SetBinContent(icluster + 1, Value);
          tmpDataHist->SetBinError(icluster + 1, sqrt(Error));
        }
  
        for(int itheory = 0; itheory < tmpTheoryHist.size(); itheory++){
          double Value = 0.0, Error = 0.0;
          for(int ibin = FirstBin + 1; ibin <= FirstBin + Clusters.at(icluster); ibin++){
            Value += TheoryHist.at(itheory)->GetBinContent(ibin);
            Error += TheoryHist.at(itheory)->GetBinError(ibin) * TheoryHist.at(itheory)->GetBinError(ibin);
            tmpTheoryHist.at(itheory)->SetBinContent(icluster + 1, Value);
            tmpTheoryHist.at(itheory)->SetBinError(icluster + 1, sqrt(Error));
          }
        }
  
        FirstBin += Clusters.at(icluster);
      }
  
      pair<TH1D*, vector<TH1D *>> Histograms = make_pair(tmpDataHist, tmpTheoryHist);
  
      return Histograms;
    };
  }

  virtual double Up() const {return theErrorDef;}
  virtual double operator()(const std::vector<double>& par) const{
    double sum = 0.0;
    for(int i = 0; i < par.size(); i++){
      sum += par.at(i);
    }

    vector<double> normalized_par = par;
    for(int i = 0; i < par.size(); i++){
      normalized_par.at(i) = par.at(i) / sum;
    }

    int SumBins = 0;
    vector<int> Clusters(par.size());
    for(int i = 0; i < par.size(); i++){
      Clusters.at(i) = (int)(nBin * normalized_par.at(i));
      if(Clusters.at(i) == 0) Clusters.at(i) = 1;

      if(i < par.size() - 1) SumBins += Clusters.at(i);
    }

    Clusters.at(par.size() - 1) = nBin - SumBins;

    pair<TH1D*, vector<TH1D *>> Histograms = ClusterHistogram(Clusters);
    TH1D* DataHist = get<0>(Histograms);
    vector<TH1D *> TheoryHist = get<1>(Histograms);

    EU->AddHistogram(DataHist, TheoryHist, "ATLAS_Mll_HighMass_Input", 1.0);
    delete DataHist;
    for(int i = 0; i < TheoryHist.size(); i++){
      delete TheoryHist.at(i);
    }
    TheoryHist.clear();

    double NewParaError = EU->GetNewParaError();

    cout<<NewParaError<<"  Clusters: ";
    for(int i = 0; i < Clusters.size(); i++){
      cout<<Clusters.at(i)<<" ";
    }
    cout<<endl;

    //EU->ResetWeight();
    EU->ResetData();

    return NewParaError;
  }

  void Finalize(std::vector<double> par, std::vector<double> parerrs){
    double sum = 0.0;
    for(int i = 0; i < par.size(); i++){
      sum += par.at(i);
    }

    vector<double> normalized_par = par;
    for(int i = 0; i < par.size(); i++){
      normalized_par.at(i) = par.at(i) / sum;
    }

    int SumBins = 0;
    vector<int> Clusters(par.size());
    for(int i = 0; i < par.size(); i++){
      Clusters.at(i) = (int)(nBin * normalized_par.at(i));
      if(Clusters.at(i) == 0) Clusters.at(i) = 1;

      if(i < par.size() - 1) SumBins += Clusters.at(i);
    }

    Clusters.at(par.size() - 1) = nBin - SumBins;

    pair<TH1D*, vector<TH1D *>> Histograms = ClusterHistogram(Clusters);
    TH1D* DataHist = get<0>(Histograms);
    vector<TH1D *> TheoryHist = get<1>(Histograms);

    EU->AddHistogram(DataHist, TheoryHist, "ATLAS_Mll_HighMass_Input", 1.0);
    delete DataHist;
    for(int i = 0; i < TheoryHist.size(); i++){
      delete TheoryHist.at(i);
    }
    TheoryHist.clear();

    double NewParaError = EU->GetNewParaError();

    cout<<"Final: "<<NewParaError<<"  Clusters: ";
    for(int i = 0; i < Clusters.size(); i++){
      cout<<Clusters.at(i)<<" ";
    }
    cout<<endl;
  }
  private:
  double theErrorDef = 0.001;
 };

 ROOT::Minuit2::FunctionMinimum* min = nullptr;

 OptimizeBinning FCN;
 FCN.SetInputName(argv[1]);
 FCN.Initialize(20);
 ROOT::Minuit2::MnMigrad migrad(FCN, FCN.upar);
 min = new ROOT::Minuit2::FunctionMinimum(migrad(100000));

 ROOT::Minuit2::MnUserParameters FinalParam = min->UserParameters();
 vector<double> pars = FinalParam.Params();
 vector<double> parerrs = FinalParam.Errors();
 FCN.Finalize(pars, parerrs);
*/



 ePumpHelper* EU;

 TFile* InputFile;
 TH1D* DataHist;
 vector<TH1D *> TheoryHist;
 TString HistName = "ATLAS_Mll_HighMass_FineBin_Pseudodata_CT18NNLO";

 EU = new ePumpHelper(argv[1]);
 EU->Initial();
 EU->TurnOffCorrelationCosine();

 InputFile = new TFile("Pseudodata_CT18NNLO.root");
 DataHist = (TH1D *)InputFile->Get(HistName + (TString)"_0");
 TheoryHist.resize(EU->NEV * 2 + 1);
 for(int i = 0; i < TheoryHist.size(); i++){
   TheoryHist.at(i) = (TH1D *)InputFile->Get(HistName + (TString)"_" + i);
 }

 auto OptimizeFunction = [&](vector<int> Clusters){

   int SumClusters = 0;
   for(int i = 0; i < Clusters.size(); i++){
     SumClusters += Clusters.at(i);
   }

   cout<<"Input: SumCluster = "<<SumClusters<<"  Clusters: ";
   for(int i = 0; i < Clusters.size(); i++){
     cout<<Clusters.at(i)<<" ";
   }
   cout<<endl;

   int nBin = Clusters.size();

   TH1D* tmpDataHist = new TH1D("tmp_Data", "tmp_Data", nBin, 0, nBin);
   vector<TH1D *> tmpTheoryHist(EU->NEV * 2 + 1);
   for(int i = 0; i < tmpTheoryHist.size(); i++){
     tmpTheoryHist.at(i) = new TH1D((TString)"tmp_Theory_" + i, (TString)"tmp_Theory_" + i, nBin, 0, nBin);
   }

   int FirstBin = 0;
   for(int icluster = 0; icluster < Clusters.size(); icluster++){
     double Value = 0.0, Error = 0.0;
     for(int ibin = FirstBin + 1; ibin <= FirstBin + Clusters.at(icluster); ibin++){
       Value += DataHist->GetBinContent(ibin);
       Error += DataHist->GetBinError(ibin) * DataHist->GetBinError(ibin);
       tmpDataHist->SetBinContent(icluster + 1, Value);
       tmpDataHist->SetBinError(icluster + 1, sqrt(Error));
     }

     for(int itheory = 0; itheory < tmpTheoryHist.size(); itheory++){
       double Value = 0.0, Error = 0.0;
       for(int ibin = FirstBin + 1; ibin <= FirstBin + Clusters.at(icluster); ibin++){
         Value += TheoryHist.at(itheory)->GetBinContent(ibin);
         Error += TheoryHist.at(itheory)->GetBinError(ibin) * TheoryHist.at(itheory)->GetBinError(ibin);
         tmpTheoryHist.at(itheory)->SetBinContent(icluster + 1, Value);
         tmpTheoryHist.at(itheory)->SetBinError(icluster + 1, sqrt(Error));
       }
     }

     FirstBin += Clusters.at(icluster);
   }

   EU->AddHistogram(tmpDataHist, tmpTheoryHist, "ATLAS_Mll_HighMass_Input", 140.0 / 3000.0);
   delete tmpDataHist;
   for(int i = 0; i < TheoryHist.size(); i++){
     delete tmpTheoryHist.at(i);
   }
   tmpTheoryHist.clear();

   double NewParaError = EU->GetNewParaError();
    //EU->ResetWeight(); // don't use this method
   EU->ResetData();
   //EU->Update(); // for test

   return NewParaError;
 };

 auto OutputBinning = [&](vector<int> Clusters){
   vector<double> BinLowEdges;
   vector<double> BinUpEdges;
   int ibin = 1;
   for(int i = 0; i < Clusters.size(); i++){
     for(int j = 1; j <= Clusters.at(i); j++){
       if(j == 1) BinLowEdges.push_back(DataHist->GetXaxis()->GetBinLowEdge(ibin));
       if(j == Clusters.at(i)) BinUpEdges.push_back(DataHist->GetXaxis()->GetBinUpEdge(ibin));
       ibin++;
     }
   }

   cout<<"Binning: nBin = "<<BinLowEdges.size()<<endl;
   for(int i = 0; i < BinLowEdges.size(); i++){
     cout<<BinLowEdges.at(i)<<", ";
   }
   cout<<BinUpEdges.at(BinUpEdges.size() - 1)<<endl;
 };

/* OptimizeBinning* Optimizor = new OptimizeBinning(DataHist->GetNbinsX());
 Optimizor->SetFCN(OptimizeFunction);
 vector<int> OldClusters(0);
 vector<int> Clusters(0);
 vector<int> FinalClusters(0);
 double FinalError = 0.0;

 int nCluster = 2;
 Clusters = Optimizor->LoopClustersDouble(nCluster);

 int iIteration = 1;
 while(nCluster < Clusters.size() - 1){

   if(OldClusters.size() == Clusters.size()) nCluster++;

   if(OldClusters.size() != Clusters.size()){
     nCluster = 2;
     FinalClusters = Clusters;
   }

   iIteration++;
   cout<<"Try "<<iIteration<<" iteration, nCluster = "<<nCluster<<":"<<endl;
   OldClusters = Clusters;
   Clusters = Optimizor->LoopClustersDouble(nCluster);
 }

 cout<<"Final: nCluster = "<<FinalClusters.size()<<" Clusters: ";
 for(int i = 0; i < FinalClusters.size(); i++){
   cout<<FinalClusters.at(i)<<", ";
 }
 cout<<endl;
 cout<<"Final Error = "<<FinalError<<endl;
*/

 OptimizeBinning* Optimizor = new OptimizeBinning(DataHist->GetNbinsX());
 Optimizor->SetFCN(OptimizeFunction);
 Optimizor->Optimize();

// for test
/* vector<int> Clusters = {46, 2, 2, 3, 5, 1, 1, 5, 7, 8, 7, 1,
                          1, 1, 2, 3, 1, 1, 2, 1, 3, 1, 6, 7,
                          1, 1, 1, 1, 1, 1, 2, 2, 4, 6, 5, 1,
                          4, 1, 12, 6, 2, 3, 2, 1, 4, 1, 1, 1,
                          2, 1, 3, 2, 1, 3, 7, 3, 1, 6, 1, 7,
                          9, 3, 4, 8, 2, 1, 4, 6, 2, 2, 3};

// vector<int> Clusters = {14, 20, 25, 25, 30, 30, 40, 8, 12, 20, 30, 1, 7};
 double Error = OptimizeFunction(Clusters);
 cout<<"Error = "<<Error<<endl;
 OutputBinning(Clusters);
*/


/* Clusters = Optimizor->LoopClusters();
 while(OldClusters.size() != Clusters.size()){
   iIteration++;
   cout<<"Try "<<iIteration<<" iteration:"<<endl;
   OldClusters = Clusters;
   Clusters = Optimizor->LoopClusters();
 }
*/

 return 1;
}
