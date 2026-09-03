#include "Tools/Tools.h"

TH1D* IterativeBayesianUnfold(const TH1D* measured, const TH2D* response, int nIterations)
{
    // Mij = ( P(Ej|Ti) * P0(Ti) ) / ( (sum_l P(El|Ti)) * (sum_l P(Ej|Tl) * P(Tl)) )

    // response with efficiency:
    // P(Ej|Ti) / (sum_l P(El|Ti))

    // Mij = responseEff(j, i) * P0(Ti) / (sum_l P(Ej|Tl) * P(Tl))

    // Get prior from response
    TH1D* Truth = (TH1D *)response->ProjectionY("Truth", 1, response->GetNbinsX());
    TH1D* TruthNorm = (TH1D *)Truth->Clone("TruthNorm");
    TruthNorm->Scale(1.0 / Truth->Integral());

    // Calculate response with efficiency
    TH1D* EfficiencyInv = (TH1D *)response->ProjectionY("EfficiencyInv", 1, response->GetNbinsX());
    EfficiencyInv->Reset();
    TH2D* responseNorm = (TH2D *)response->Clone("responseNorm");
    responseNorm->Reset();
    TH2D* responseEff = (TH2D *)response->Clone("responseEff");
    responseEff->Reset();
    TH1D* Denom = (TH1D *)response->ProjectionX("Denom", 1, response->GetNbinsY());
    Denom->Reset();

    TH2D* Mij = new TH2D("Mij", "Mij", response->GetNbinsY(), 1, response->GetNbinsY(), response->GetNbinsX(), 1, response->GetNbinsX());

    for(int i = 1; i <= response->GetNbinsY(); i++){// truth axis
      double sum = 0.0;
      for(int j = 1; j <= response->GetNbinsX(); j++){// reco axis
        double r = response->GetBinContent(j, i) / Truth->GetBinContent(i);
        if(!isfinite(r)) r = 0.0;
        sum += r;
        responseEff->SetBinContent(j, i, r);
        responseNorm->SetBinContent(j, i, r);
      }
      double sum_inv = sum > 0.0 ? 1.0 / sum : 0.0;
      EfficiencyInv->SetBinContent(i, sum_inv);

      for(int j = 1; j <= response->GetNbinsX(); j++){// reco axis
        responseEff->SetBinContent(j, i, responseEff->GetBinContent(j, i) * EfficiencyInv->GetBinContent(i));
      }
    }

    // Iterative Bayesian unfolding
    for (int iter = 0; iter < nIterations; ++iter) {

      // Calculate denom
      for(int j = 1; j <= response->GetNbinsX(); j++){
        double sum = 0.0;
        for(int l = 1; l <= response->GetNbinsY(); l++){
          sum += responseNorm->GetBinContent(j, l) * TruthNorm->GetBinContent(l);
        }
        double sum_inv = sum > 0.0 ? 1.0 / sum : 0.0;
        Denom->SetBinContent(j, sum_inv);
      }

      for(int i = 1; i <= response->GetNbinsY(); i++){
        for(int j = 1; j <= response->GetNbinsX(); j++){
          double value = responseEff->GetBinContent(j, i) * TruthNorm->GetBinContent(i) * Denom->GetBinContent(j);
          Mij->SetBinContent(i, j, value);
        }
      }

      // apply Mij to estimate new truth
      for(int i = 1; i <= Mij->GetNbinsX(); i++){
        double sum = 0.0;
        for(int j = 1; j <= Mij->GetNbinsY(); j++){
          sum += Mij->GetBinContent(i, j) * measured->GetBinContent(j);
        }
        Truth->SetBinContent(i, sum);
        TruthNorm->SetBinContent(i, sum);
      }
      TruthNorm->Scale(1.0 / Truth->Integral());
    }

    return Truth;
}

