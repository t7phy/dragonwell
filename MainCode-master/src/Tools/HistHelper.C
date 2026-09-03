#include "Tools/Tools.h"

void InverseHistXaxis(TH1D *h1, TH1D* &inverse_h1)
{
 if(!inverse_h1){
   inverse_h1 = (TH1D *)h1->Clone((TString)h1->GetName() + "_InverseXaxis");
 }

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   int nbin = h1->GetNbinsX() - ibin + 1;
   inverse_h1->SetBinContent(ibin, h1->GetBinContent(nbin));
   inverse_h1->SetBinError(ibin, h1->GetBinError(nbin));
 }

}

void InverseHistXaxis(TH2D *h1, TH2D* &inverse_h1)
{
 if(!inverse_h1){
   inverse_h1 = (TH2D *)h1->Clone((TString)h1->GetName() + "_InverseXaxis");
 }

 for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
   for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
     int nbin = h1->GetNbinsX() - ibinx + 1;
     inverse_h1->SetBinContent(ibinx, ibiny, h1->GetBinContent(nbin, ibiny));
     inverse_h1->SetBinError(ibinx, ibiny, h1->GetBinError(nbin, ibiny));
   }
 }
}

void ConstructTH2D(vector<TH1D *> hists, TH2D* &h2, double* BinningY)
{
 int nbinx = hists.at(0)->GetNbinsX();
 double BinningX[nbinx + 1];
 for(int ibin = 1; ibin <= nbinx; ibin++){
   BinningX[ibin - 1] = hists.at(0)->GetXaxis()->GetBinLowEdge(ibin);
 }
 BinningX[nbinx] = hists.at(0)->GetXaxis()->GetBinUpEdge(nbinx);

 int nbiny = hists.size();

 h2 = new TH2D(hists.at(0)->GetName() + (TString)"_Combined", hists.at(0)->GetName() + (TString)"_Combined", nbinx, BinningX, nbiny, BinningY);

 for(int ibinx = 1; ibinx <= nbinx; ibinx++){
   for(int ibiny = 1; ibiny <= nbiny; ibiny++){
     h2->SetBinContent(ibinx, ibiny, hists.at(ibiny - 1)->GetBinContent(ibinx));
     h2->SetBinError(ibinx, ibiny, hists.at(ibiny - 1)->GetBinError(ibinx));
   }
 }
}

void ConstructTH2D(vector<TH1D *> hists, TH2D* &h2, int nbiny)
{
 int nbinx = hists.at(0)->GetNbinsX();
 double BinningX[nbinx + 1];
 for(int ibin = 1; ibin <= nbinx; ibin++){
   BinningX[ibin - 1] = hists.at(0)->GetXaxis()->GetBinLowEdge(ibin);
 } 
 BinningX[nbinx] = hists.at(0)->GetXaxis()->GetBinUpEdge(nbinx);

 double BinningY[nbiny + 1];
 for(int ibin = 0; ibin <= nbiny; ibin++){
   BinningY[ibin] = ibin;
 }

 h2 = new TH2D(hists.at(0)->GetName() + (TString)"_Combined", hists.at(0)->GetName() + (TString)"_Combined", nbinx, BinningX, nbiny, BinningY);
   
 for(int ibinx = 1; ibinx <= nbinx; ibinx++){
   for(int ibiny = 1; ibiny <= nbiny; ibiny++){
     h2->SetBinContent(ibinx, ibiny, hists.at(ibiny - 1)->GetBinContent(ibinx));
     h2->SetBinError(ibinx, ibiny, hists.at(ibiny - 1)->GetBinError(ibinx));
   } 
 }
}

TH1D* GenPseudodata(double lumi, TH1D* h1, TString subName, int seed, bool isNorm)
{
 TH1D* data = static_cast<TH1D *>(h1->Clone((TString)h1->GetName() + (TString)"_" + subName));
 TRandom rand(seed);

 for(int ibin = 1; ibin <= data->GetNbinsX(); ibin++){
   double xsec = h1->GetBinContent(ibin);
   double mean = xsec * lumi;
   double nevents = static_cast<double>(rand.Poisson(mean));
   double error = std::sqrt(nevents);

   if(nevents < 0){nevents = 0.0; error = 0.0;}

   data->SetBinContent(ibin, nevents);
   data->SetBinError(ibin, error);
 }

 if(isNorm) data->Scale(1.0 / data->Integral());

 return data;
}

TH1D* GenPseudodataNoFluc(double lumi, TH1D* h1, TString subName, int seed, bool isNorm)
{
 TH1D* data = static_cast<TH1D *>(h1->Clone((TString)h1->GetName() + (TString)"_" + subName));
 TRandom rand(seed);

 for(int ibin = 1; ibin <= data->GetNbinsX(); ibin++){
   double xsec = h1->GetBinContent(ibin);
   double mean = xsec * lumi;
   double nevents = mean;
   double error = std::sqrt(nevents);

   if(nevents < 0){nevents = 0.0; error = 0.0;}

   data->SetBinContent(ibin, nevents);
   data->SetBinError(ibin, error);
 }

 if(isNorm) data->Scale(1.0 / data->Integral());

 return data;
}

TH2D* GenPseudodata(double lumi, TH2D* h1, TString subName, int seed, bool isNorm)
{
 TH2D* data = static_cast<TH2D *>(h1->Clone((TString)h1->GetName() + (TString)"_" + subName));
 TRandom rand(seed);

 for(int ibinx = 1; ibinx <= data->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= data->GetNbinsY(); ibiny++){
     double xsec = h1->GetBinContent(ibinx, ibiny);
     double mean = xsec * lumi;
     double nevents = static_cast<double>(rand.Poisson(mean));
     double error = std::sqrt(nevents);

     if(nevents < 0){nevents = 0.0; error = 0.0;}

     data->SetBinContent(ibinx, ibiny, nevents);
     data->SetBinError(ibinx, ibiny, error);
   }
 }

 if(isNorm) data->Scale(1.0 / data->Integral());

 return data;
}

TH2D* GenPseudodataNoFluc(double lumi, TH2D* h1, TString subName, int seed, bool isNorm)
{
 TH2D* data = static_cast<TH2D *>(h1->Clone((TString)h1->GetName() + (TString)"_" + subName));
 TRandom rand(seed);

 for(int ibinx = 1; ibinx <= data->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= data->GetNbinsY(); ibiny++){
     double xsec = h1->GetBinContent(ibinx, ibiny);
     double mean = xsec * lumi;
     double nevents = mean;
     double error = std::sqrt(nevents);

     if(nevents < 0){nevents = 0.0; error = 0.0;}

     data->SetBinContent(ibinx, ibiny, nevents);
     data->SetBinError(ibinx, ibiny, error);
   }
 }

 if(isNorm) data->Scale(1.0 / data->Integral());

 return data;
}

TH3D* GenPseudodata(double lumi, TH3D* h1, TString subName, int seed, bool isNorm)
{
 TH3D* data = static_cast<TH3D *>(h1->Clone((TString)h1->GetName() + (TString)"_" + subName));
 TRandom rand(seed);

 for(int ibinx = 1; ibinx <= data->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= data->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= data->GetNbinsZ(); ibinz++){
       double xsec = h1->GetBinContent(ibinx, ibiny, ibinz);
       double mean = xsec * lumi;
       double nevents = static_cast<double>(rand.Poisson(mean));
       double error = std::sqrt(nevents);

       if(nevents < 0){nevents = 0.0; error = 0.0;}

       data->SetBinContent(ibinx, ibiny, ibinz, nevents);
       data->SetBinError(ibinx, ibiny, ibinz, error);
     }
   }
 }

 if(isNorm) data->Scale(1.0 / data->Integral());

 return data;
}

TH3D* GenPseudodataNoFluc(double lumi, TH3D* h1, TString subName, int seed, bool isNorm)
{
 TH3D* data = static_cast<TH3D *>(h1->Clone((TString)h1->GetName() + (TString)"_" + subName));
 TRandom rand(seed);

 for(int ibinx = 1; ibinx <= data->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= data->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= data->GetNbinsZ(); ibinz++){
       double xsec = h1->GetBinContent(ibinx, ibiny, ibinz);
       double mean = xsec * lumi;
       double nevents = mean;
       double error = std::sqrt(nevents);

       if(nevents < 0){nevents = 0.0; error = 0.0;}

       data->SetBinContent(ibinx, ibiny, ibinz, nevents);
       data->SetBinError(ibinx, ibiny, ibinz, error);
     }
   }
 }

 if(isNorm) data->Scale(1.0 / data->Integral());

 return data;
}


void ChangeHistPercentErr(TH1D* &h1, double percent, TString type)
{
 if(percent > 1.0 && type == "Down"){
   cout<<"ERROR!"<<endl;
   return;
 }

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double Value;
   if(type == "Up") Value = (1.0 + percent) * h1->GetBinContent(ibin);
   if(type == "Down") Value = (1.0 - percent) * h1->GetBinContent(ibin);

   h1->SetBinContent(ibin, Value);
 }

}

void HistDivideBinWidth(TH1D* h1, TH1D* &h1Past)
{
 h1Past = (TH1D *)h1->Clone((TString)h1->GetName() + (TString)"_Final");

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double Value = h1->GetBinContent(ibin);
   double Error = h1->GetBinError(ibin);
   double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibin) - h1->GetXaxis()->GetBinLowEdge(ibin);
   h1Past->SetBinContent(ibin, Value / BinWidth);
   h1Past->SetBinError(ibin, Error / BinWidth);
 }
}

void HistDivideBinWidth(TH1D* h1, TH1D* &h1Past, double add_factor)
{
 h1Past = (TH1D *)h1->Clone((TString)h1->GetName() + (TString)"_Final");

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double Value = h1->GetBinContent(ibin);
   double Error = h1->GetBinError(ibin);
   double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibin) - h1->GetXaxis()->GetBinLowEdge(ibin);
   h1Past->SetBinContent(ibin, Value / BinWidth / add_factor);
   h1Past->SetBinError(ibin, Error / BinWidth / add_factor);
 }
}

void HistDivideBinWidth(TH2D* h1, TH2D* &h1Past, TString flag)
{
 h1Past = (TH2D *)h1->Clone((TString)h1->GetName() + (TString)"_Final");

 if(flag == "X"){
   for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
       double Value = h1->GetBinContent(ibinx, ibiny);
       double Error = h1->GetBinError(ibinx, ibiny);
       double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibinx) - h1->GetXaxis()->GetBinLowEdge(ibinx);
       h1Past->SetBinContent(ibinx, ibiny, Value / BinWidth);
       h1Past->SetBinError(ibinx, ibiny, Error / BinWidth);
     }
   }
 }

 if(flag == "Y"){
   for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
       double Value = h1->GetBinContent(ibinx, ibiny);
       double Error = h1->GetBinError(ibinx, ibiny);
       double BinWidth = h1->GetYaxis()->GetBinUpEdge(ibiny) - h1->GetYaxis()->GetBinLowEdge(ibiny);
       h1Past->SetBinContent(ibinx, ibiny, Value / BinWidth);
       h1Past->SetBinError(ibinx, ibiny, Error / BinWidth);
     }
   }
 }
}

void HistDivideBinWidth(TH3D* h1, TH3D* &h1Past, TString flag)
{
 h1Past = (TH3D *)h1->Clone((TString)h1->GetName() + (TString)"_Final");

 if(flag == "X"){
   for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= h1->GetNbinsZ(); ibinz++){
         double Value = h1->GetBinContent(ibinx, ibiny, ibinz);
         double Error = h1->GetBinError(ibinx, ibiny, ibinz);
         double BinWidth = h1->GetXaxis()->GetBinUpEdge(ibinx) - h1->GetXaxis()->GetBinLowEdge(ibinx);
         h1Past->SetBinContent(ibinx, ibiny, ibinz, Value / BinWidth);
         h1Past->SetBinError(ibinx, ibiny, ibinz, Error / BinWidth);
       }
     }
   }
 }

 if(flag == "Y"){
   for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= h1->GetNbinsZ(); ibinz++){
         double Value = h1->GetBinContent(ibinx, ibiny, ibinz);
         double Error = h1->GetBinError(ibinx, ibiny, ibinz);
         double BinWidth = h1->GetYaxis()->GetBinUpEdge(ibiny) - h1->GetYaxis()->GetBinLowEdge(ibiny);
         h1Past->SetBinContent(ibinx, ibiny, ibinz, Value / BinWidth);
         h1Past->SetBinError(ibinx, ibiny, ibinz, Error / BinWidth);
       }
     }
   }
 }

 if(flag == "Z"){
   for(int ibinx = 1; ibinx <= h1->GetNbinsX(); ibinx++){
     for(int ibiny = 1; ibiny <= h1->GetNbinsY(); ibiny++){
       for(int ibinz = 1; ibinz <= h1->GetNbinsZ(); ibinz++){
         double Value = h1->GetBinContent(ibinx, ibiny, ibinz);
         double Error = h1->GetBinError(ibinx, ibiny, ibinz);
         double BinWidth = h1->GetZaxis()->GetBinUpEdge(ibinz) - h1->GetZaxis()->GetBinLowEdge(ibinz);
         h1Past->SetBinContent(ibinx, ibiny, ibinz, Value / BinWidth);
         h1Past->SetBinError(ibinx, ibiny, ibinz, Error / BinWidth);
       }
     }
   }
 }
}

vector<double> GetHistBinning(TH1D* h)
{
 vector<double> Binning;

 int nbin = h->GetNbinsX();

 Binning.resize(nbin + 1);

 Binning.at(0) = h->GetXaxis()->GetBinLowEdge(1);
 for(int i = 1; i <= nbin; i++){
   Binning.at(i) = h->GetXaxis()->GetBinUpEdge(i);
 }

 return Binning;
}

void ApplyKFactorToHist(TH1D* Origin, TH1D* KFactor, TH1D* &HighOrder, double Cut)
{
 HighOrder = (TH1D *)Origin->Clone((TString)Origin->GetName() + (TString)"_HigherOrder");

 for(int ibin = 1; ibin <= Origin->GetNbinsX(); ibin++){
   double Value = 1.0;
   double Error = 0.0;
   if(Origin->GetBinCenter(ibin) < Cut){
     Value = Origin->GetBinContent(ibin);
     Error = Origin->GetBinError(ibin);
   }
   else{
     Value = Origin->GetBinContent(ibin) * KFactor->GetBinContent(ibin);
     Error = Origin->GetBinError(ibin);
   }

   HighOrder->SetBinContent(ibin, Value);
   HighOrder->SetBinError(ibin, Error);
 }

}

void DecompositeTH3DtoTH1D(vector<TH3D *> Input, vector<vector<TH1D *>> &Output)
{
 int nPlot = Input.at(0)->GetNbinsX() * Input.at(0)->GetNbinsY() * Input.at(0)->GetNbinsZ();

 Output.resize(nPlot);

 int iPlot = 0;
 for(int ibinx = 1; ibinx <= Input.at(0)->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= Input.at(0)->GetNbinsY(); ibiny++){
     for(int ibinz = 1; ibinz <= Input.at(0)->GetNbinsZ(); ibinz++){
       Output.at(iPlot).resize(Input.size());

       for(int i = 0; i < Input.size(); i++){
         TString HistName = Input.at(0)->GetName() + (TString)"_binx_" + (int)ibinx + (TString)"_biny_" + (int)ibiny + (TString)"_binz_" + (int)ibinz + (TString)"_PDF" + (int)i;
         Output.at(iPlot).at(i) = new TH1D(HistName, HistName, 1, 0, 1);
         Output.at(iPlot).at(i)->SetBinContent(1, Input.at(i)->GetBinContent(ibinx, ibiny, ibinz));
         Output.at(iPlot).at(i)->SetBinError(1, Input.at(i)->GetBinError(ibinx, ibiny, ibinz));
       }
       iPlot++;
     }
   }
 }

}

void DivideHist(TH1D* h1, TH1D* h2, TH1D* &Ratio)
{
 for(int ibin = 1; ibin <= Ratio->GetNbinsX(); ibin++){
   double Value = 0.0;
   if(fabs(h2->GetBinContent(ibin)) > 1e-20) Value = h1->GetBinContent(ibin) / h2->GetBinContent(ibin);
   Ratio->SetBinContent(ibin, Value);
   double Value1 = h1->GetBinContent(ibin);
   double Value2 = h2->GetBinContent(ibin);
   double Error1 = h1->GetBinError(ibin);
   double Error2 = h2->GetBinError(ibin);
   double Error = 0.0;
   if(fabs(h2->GetBinContent(ibin)) > 1e-20) Error = DivideUncertainty(Value1, Value2, Error1, Error2);
   Ratio->SetBinError(ibin, Error);
 }

}

TH1D* HistExtend(vector<TH1D *> hists)
{
 TH1D* h1;

 for(int i = 1; i < hists.size(); i++){
   int NBin1 = hists.at(i - 1)->GetNbinsX();
   double UpBand = hists.at(i - 1)->GetXaxis()->GetBinUpEdge(NBin1);
   double LowBand = hists.at(i)->GetXaxis()->GetBinUpEdge(1);
   if(UpBand > LowBand){
     cout<<"ERROR! The upper band of hist "<<i<<" is greater than the lower band of hist "<<i + 1<<endl;
   }
 }

 vector<double> Binning;
 for(int i = 0; i < hists.size(); i++){
   if(i == 0) Binning.push_back(hists.at(i)->GetXaxis()->GetBinLowEdge(1));
   for(int ibin = 1; ibin <= hists.at(i)->GetNbinsX(); ibin++){
     Binning.push_back(hists.at(i)->GetXaxis()->GetBinUpEdge(ibin));
   }
 }

 TString HistName = (TString)hists.at(0)->GetName() + (TString)"_Extended" + (int)hists.size();

 h1 = new TH1D(HistName, HistName, Binning.size() - 1, &Binning[0]);

 int Bin = 0;
 for(int i = 0; i < hists.size(); i++){
   for(int ibin = 1; ibin <= hists.at(i)->GetNbinsX(); ibin++){
     Bin++;
     h1->SetBinContent(Bin, hists.at(i)->GetBinContent(ibin));
     h1->SetBinError(Bin, hists.at(i)->GetBinError(ibin));
   }
 }

 return h1;
}

