#include "SpecialHist/UnfoldHist.h"

using namespace std;

UnfoldHist::UnfoldHist()
{

}

void UnfoldHist::DefineHist(TString name, TString title, int nbin_reco, double left_reco, double right_reco, int nbin_truth, double left_truth, double right_truth)
{
 RecoHist = new TH1D(name + (TString)"_Reco", title + (TString)"_Reco", nbin_reco, left_reco, right_reco);
 TruthHist = new TH1D(name + (TString)"_Truth", title + (TString)"_Truth", nbin_truth, left_truth, right_truth);

 TruthToReco.resize(nbin_truth);
 for(int i = 0; i < TruthToReco.size(); i++){
   TString HistName = name + (TString)"_TruthToReco_TruthBin" + (int)(i + 1);
   TString HistTitle = title + (TString)"_TruthToReco_TruthBin" + (int)(i + 1);
   TruthToReco.at(i) = new TH1D(HistName, HistTitle, nbin_reco, left_reco, right_reco);
 }

 RecoToTruth.resize(nbin_reco);
 for(int i = 0; i < RecoToTruth.size(); i++){
   TString HistName = name + (TString)"_RecoToTruth_RecoBin" + (int)(i + 1);
   TString HistTitle = title + (TString)"_RecoToTruth_RecoBin" + (int)(i + 1);
   RecoToTruth.at(i) = new TH1D(HistName, HistTitle, nbin_truth, left_truth, right_truth);
 }

 this->nbin_reco = nbin_reco;
 this->nbin_truth = nbin_truth;
 this->name = name;
}

void UnfoldHist::DefineHist(TString name, TString title, int nbin_reco, double* xbins_reco, int nbin_truth, double* xbins_truth)
{
 RecoHist = new TH1D(name + (TString)"_Reco", title + (TString)"_Reco", nbin_reco, xbins_reco);
 TruthHist = new TH1D(name + (TString)"_Truth", title + (TString)"_Truth", nbin_truth, xbins_truth);

 TruthToReco.resize(nbin_truth);
 for(int i = 0; i < TruthToReco.size(); i++){
   TString HistName = name + (TString)"_TruthToReco_TruthBin" + (int)(i + 1);
   TString HistTitle = title + (TString)"_TruthToReco_TruthBin" + (int)(i + 1);
   TruthToReco.at(i) = new TH1D(HistName, HistTitle, nbin_reco, xbins_reco);
 }

 RecoToTruth.resize(nbin_reco); for(int i = 0; i < RecoToTruth.size(); i++){
   TString HistName = name + (TString)"_RecoToTruth_RecoBin" + (int)(i + 1);
   TString HistTitle = title + (TString)"_RecoToTruth_RecoBin" + (int)(i + 1);
   RecoToTruth.at(i) = new TH1D(HistName, HistTitle, nbin_truth, xbins_truth);
 }

 this->nbin_reco = nbin_reco;
 this->nbin_truth = nbin_truth;
 this->name = name;
}

void UnfoldHist::Fill(double reco, double truth, double weight)
{
 RecoHist->Fill(reco, weight);
 TruthHist->Fill(truth, weight);

 int RecoBin = RecoHist->FindBin(reco);
 RecoToTruth.at(RecoBin - 1)->Fill(truth, weight);

 int TruthBin = TruthHist->FindBin(truth);
 TruthToReco.at(TruthBin - 1)->Fill(reco, weight);

}

void UnfoldHist::Unfolding()
{
 ResponseMatrix = new TH2D("ResponseMatrix", "ResponseMatrix", nbin_reco, 1, nbin_reco, nbin_truth, 1, nbin_truth);

 for(int i = 0; i < TruthToReco.size(); i++){
   TruthToReco.at(i)->Scale(1.0 / TruthToReco.at(i)->Integral());
 }

 RecoHist->Scale(1.0 / RecoHist->Integral());

 PriorHist[1] = (TH1D *)TruthHist->Clone(name + (TString)"_PriorHist_Iter1");
 PriorHist[1]->Scale(1.0 / PriorHist[1]->Integral());

}

void UnfoldHist::DeleteHist()
{
}

void UnfoldHist::Add(UnfoldHist* hist1)
{
}

void UnfoldHist::Reset()
{
}

void UnfoldHist::Write()
{
}

