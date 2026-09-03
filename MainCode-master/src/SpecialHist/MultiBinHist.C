#include "SpecialHist/MultiBinHist.h"

MultiBinHist::MultiBinHist()
{

}

MultiBinHist::MultiBinHist(vector<vector<double>> MultiBinVector)
{
 this->MultiBinVector = MultiBinVector;

 MultiBin = new double*[MultiBinVector.size()];
 for(int i = 0; i < MultiBinVector.size(); i++){
   MultiBin[i] = new double[MultiBinVector.at(i).size()];

   for(int j = 0; j < MultiBinVector.at(i).size(); j++){
     MultiBin[i][j] = MultiBinVector.at(i).at(j);
   }
 }
}

void MultiBinHist::DefineHist(TString name, TString title, int nbin, double* xbins)
{
 for(int i = 0; i < MultiBinVector.size(); i++){
   myHist[i] = new TH2D(name + "_MultiBin" + (int)(i + 1), title + "_MultiBin" + (int)(i + 1), nbin, xbins, MultiBinVector.at(i).size() - 1, MultiBin[i]);
   myHist[i]->Sumw2();

   hist_vector.push_back(myHist[i]);
 }

 this->nbin = nbin;
 this->name = name;
}

void MultiBinHist::Fill(double par1, double par2, double weight)
{
 for(int i = 0; i < MultiBinVector.size(); i++){
   myHist[i]->Fill(par1, par2, weight);
 }
}

void MultiBinHist::Input(vector<TH2D *> hist_vector)
{
 this->hist_vector = hist_vector;

 this->nbin = hist_vector.at(0)->GetNbinsX();
 this->name = hist_vector.at(0)->GetName();

 for(int i = 0; i < hist_vector.size(); i++){
   myHist[i] = hist_vector.at(i);

   vector<double> tmpMultiBin;
   tmpMultiBin.push_back(hist_vector.at(i)->GetYaxis()->GetBinLowEdge(1));
   for(int ibiny = 1; ibiny <= hist_vector.at(i)->GetNbinsY(); ibiny++){
     tmpMultiBin.push_back(hist_vector.at(i)->GetYaxis()->GetBinUpEdge(ibiny));
   }
   this->MultiBinVector.push_back(tmpMultiBin);
   tmpMultiBin.clear();
 }

}

MultiBinHist* MultiBinHist::Clone(TString name)
{
 MultiBinHist *hist = new MultiBinHist(this->MultiBinVector);

 hist->name = name;
 hist->nbin = this->nbin;

 for(int i = 0; i < this->MultiBinVector.size(); i++){
   hist->myHist[i] = (TH2D *)myHist[i]->Clone(name + "_MultiBin" + (int)(i + 1));

   (hist->hist_vector).push_back(hist->myHist[i]);
 }

 return hist;
}

void MultiBinHist::Add(MultiBinHist *hist2)
{
 if(this->MultiBinVector.size() != hist2->MultiBinVector.size()){
   cout<<"ERROR! Binning not matching."<<endl;
   return;
 }
 for(int i = 0; i < MultiBinVector.size(); i++){
   this->myHist[i]->Add((hist2->hist_vector).at(i));
 }
}

void MultiBinHist::Divide(MultiBinHist *hist2)
{
 if(this->MultiBinVector.size() != hist2->MultiBinVector.size()){
   cout<<"ERROR! Binning not matching."<<endl;
   return;
 }
 for(int i = 0; i < MultiBinVector.size(); i++){
   this->myHist[i]->Divide((hist2->hist_vector).at(i));
 }
}

double MultiBinHist::Integral(int i)
{
 double Value = myHist[i]->Integral();

 return Value;
}

void MultiBinHist::Reset()
{
 for(int i = 0; i < MultiBinVector.size(); i++){
   myHist[i]->Reset();
 }
}

void MultiBinHist::DeleteHist()
{
 for(int i = 0; i < MultiBinVector.size(); i++){
   delete myHist[i];
 }
}

void MultiBinHist::Write()
{
 for(int i = 0; i < MultiBinVector.size(); i++){
   myHist[i]->Write();
 }
}

#ifndef SpecialHist_MultiBinHist_cxx
#define SpecialHist_MultiBinHist_cxx

void AFBFunction(MultiBinHist* FZmass, MultiBinHist* BZmass, MultiBinHist* &Draw_AFB)
{
 if(!Draw_AFB){
   Draw_AFB = FZmass->Clone("h1");
   Draw_AFB->Reset();
 }

 double Nf, Nb, AFB, NfError, NbError, AFBError;

 for(int imulti = 0; imulti < FZmass->hist_vector.size(); imulti++){
   for(int ibinx = 0; ibinx < (FZmass->hist_vector.at(imulti))->GetNbinsX(); ibinx++){
     for(int ibiny = 0; ibiny < (FZmass->hist_vector.at(imulti))->GetNbinsY(); ibiny++){
       Nf = (FZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1);
       Nb = (BZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1);
       if((Nf + Nb) < 1e-10) continue;

       AFB = (Nf - Nb) / (Nf + Nb);

       NfError = (FZmass->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);
       NbError = (BZmass->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);
       AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));

       (Draw_AFB->hist_vector.at(imulti))->SetBinContent(ibinx + 1, ibiny + 1, AFB);
       (Draw_AFB->hist_vector.at(imulti))->SetBinError(ibinx + 1, ibiny + 1, AFBError);
     }
   }
 }
}

void GetAFBDiff(MultiBinHist* AFB, MultiBinHist* &AFBDiff)
{
 if(!AFBDiff){
   AFBDiff = new MultiBinHist(AFB->MultiBinVector);
   double xbins[AFB->nbin / 2 + 1];
   for(int i = 0; i < AFB->nbin / 2 + 1; i++){xbins[i] = i + 1;}
   AFBDiff->DefineHist(AFB->name + (TString)"_Diff", AFB->name + (TString)"_Diff", AFB->nbin / 2, xbins);
 }

 MultiBinHist* tmpAFBDiff = new MultiBinHist(AFB->MultiBinVector);
 double xbins[AFB->nbin / 2 + 1];
 for(int i = 0; i < AFB->nbin / 2 + 1; i++){xbins[i] = i + 1;}
 tmpAFBDiff->DefineHist(AFB->name + (TString)"_Diff_tmp", AFB->name + (TString)"_Diff_tmp", AFB->nbin / 2, xbins);

 for(int imulti = 0; imulti < AFB->hist_vector.size(); imulti++){
   for(int ibiny = 1; ibiny <= (tmpAFBDiff->hist_vector.at(imulti))->GetNbinsY(); ibiny++){
     for(int ibinx = 1; ibinx <= (tmpAFBDiff->hist_vector.at(imulti))->GetNbinsX(); ibinx++){
       int FirstBin = ibinx;
       int LastBin = (tmpAFBDiff->hist_vector.at(imulti))->GetNbinsX() * 2 - (ibinx - 1);

       double Diff = (AFB->hist_vector.at(imulti))->GetBinContent(FirstBin, ibiny) - (AFB->hist_vector.at(imulti))->GetBinContent(LastBin, ibiny);
       double DiffErr = sqrt((AFB->hist_vector.at(imulti))->GetBinError(FirstBin, ibiny) * (AFB->hist_vector.at(imulti))->GetBinError(FirstBin, ibiny) + (AFB->hist_vector.at(imulti))->GetBinError(LastBin, ibiny) * (AFB->hist_vector.at(imulti))->GetBinError(LastBin, ibiny));

       (tmpAFBDiff->hist_vector.at(imulti))->SetBinContent(ibinx, ibiny, Diff);
       (tmpAFBDiff->hist_vector.at(imulti))->SetBinError(ibinx, ibiny, DiffErr);
     }
   }
 }

 InverseHistXaxis(tmpAFBDiff, AFBDiff);

 tmpAFBDiff->DeleteHist();
 delete tmpAFBDiff;
}

void ApplyDilution(MultiBinHist* &FZmass, MultiBinHist* &BZmass, MultiBinHist* Dilution, bool isGG, vector<double> S0)
{
 for(int imulti = 0; imulti < FZmass->hist_vector.size(); imulti++){
   for(int ibinx = 0; ibinx < (FZmass->hist_vector.at(imulti))->GetNbinsX(); ibinx++){
     for(int ibiny = 0; ibiny < (FZmass->hist_vector.at(imulti))->GetNbinsY(); ibiny++){
       double DilutionFactor = (Dilution->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1) + S0.at(imulti);
       double DilutionError = (Dilution->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);
       if(isGG){
         DilutionFactor = 0.5;
         DilutionError = 0;
       }

       double FBinContent = (FZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1) * (1 - DilutionFactor) + (BZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1) * DilutionFactor;
       double BBinContent = (BZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1) * (1 - DilutionFactor) + (FZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1) * DilutionFactor;

       double NF = (FZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1);
       double NB = (BZmass->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1);
       double NFError = (FZmass->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);
       double NBError = (BZmass->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);

       double FBinError = sqrt(NF * NF * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NFError * NFError + DilutionFactor * DilutionFactor * NBError * NBError + NB * NB * DilutionError * DilutionError);
       double BBinError = sqrt(NB * NB * DilutionError * DilutionError + (1 - DilutionFactor) * (1 - DilutionFactor) * NBError * NBError + DilutionFactor * DilutionFactor * NFError * NFError + NF * NF * DilutionError * DilutionError);

       (FZmass->hist_vector.at(imulti))->SetBinContent(ibinx + 1, ibiny + 1, FBinContent);
       (BZmass->hist_vector.at(imulti))->SetBinContent(ibinx + 1, ibiny + 1, BBinContent);
       (FZmass->hist_vector.at(imulti))->SetBinError(ibinx + 1, ibiny + 1, FBinError);
       (BZmass->hist_vector.at(imulti))->SetBinError(ibinx + 1, ibiny + 1, BBinError);
     }
   }
 }
}

void InverseHistXaxis(MultiBinHist *h1, MultiBinHist* &inverse_h1)
{
 if(!inverse_h1){
   inverse_h1 = new MultiBinHist(h1->MultiBinVector);
   inverse_h1 = h1->Clone((TString)h1->name + "_InverseXaxis");
 }

 for(int imulti = 0; imulti < h1->hist_vector.size(); imulti++){
   for(int ibiny = 1; ibiny <= (h1->hist_vector.at(imulti))->GetNbinsY(); ibiny++){
     for(int ibinx = 1; ibinx <= (h1->hist_vector.at(imulti))->GetNbinsX(); ibinx++){
       int nbin = (h1->hist_vector.at(imulti))->GetNbinsX() - ibinx + 1;
       (inverse_h1->hist_vector.at(imulti))->SetBinContent(ibinx, ibiny, (h1->hist_vector.at(imulti))->GetBinContent(nbin, ibiny));
       (inverse_h1->hist_vector.at(imulti))->SetBinError(ibinx, ibiny, (h1->hist_vector.at(imulti))->GetBinError(nbin, ibiny));
     }
   }
 }

}

double CalculateChi2(MultiBinHist* h1, MultiBinHist* h2)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int imulti = 0; imulti < h1->hist_vector.size(); imulti++){
   for(int ibinx = 0; ibinx < (h1->hist_vector.at(imulti))->GetNbinsX(); ibinx++){
     for(int ibiny = 0; ibiny < (h1->hist_vector.at(imulti))->GetNbinsY(); ibiny++){
       N1 = (h1->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1);
       N2 = (h2->hist_vector.at(imulti))->GetBinContent(ibinx + 1, ibiny + 1);

       N1Error = (h1->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);
       N2Error = (h2->hist_vector.at(imulti))->GetBinError(ibinx + 1, ibiny + 1);

       if(isOutput) cout<<"bin "<<ibinx + 1<<" N1: "<<N1<<" N2: "<<N2<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

       if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
         if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
         continue;
       }

       Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
     }
   }
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;

}


#endif
