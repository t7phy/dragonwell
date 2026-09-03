#include "SpecialHist/MultiWeightHist.h"

MultiWeightHist::MultiWeightHist()
{

}

MultiWeightHist::MultiWeightHist(int nWeight)
{
 this->nWeight = nWeight;
 hist_vector.resize(nWeight);

}

void MultiWeightHist::DefineHist(TString name, TString title, int nbin, double left, double right)
{
 for(int i = 0; i < nWeight; i ++){
   hist_vector.at(i) = new TH1D(name + "_Weight_" + (int)(i + 1), title + "_Weight_" + (int)(i + 1), nbin, left, right);
   hist_vector.at(i)->Sumw2();
 }

 this->nbin = nbin;
 this->name = name;
}

void MultiWeightHist::DefineHist(TString name, TString title, int nbin, double* xbins)
{
 for(int i = 0; i < nWeight; i ++){
   hist_vector.at(i) = new TH1D(name + "_Weight_" + (int)(i + 1), title + "_Weight_" + (int)(i + 1), nbin, xbins);
   hist_vector.at(i)->Sumw2();
 }

 this->nbin = nbin;
 this->name = name;
}

void MultiWeightHist::Fill(double par1, vector<double> weights)
{
 for(int i = 0; i < nWeight; i++){
   hist_vector.at(i)->Fill(par1, weights.at(i));
 }
}

MultiWeightHist* MultiWeightHist::Clone(TString name)
{
 MultiWeightHist *hist = new MultiWeightHist(this->nWeight);

 hist->name = name;
 hist->nbin = this->nbin;

 for(int i = 0; i < this->nWeight; i++){
   hist->hist_vector.at(i) = (TH1D *)hist_vector.at(i)->Clone(name + "_Weight_" + (int)(i + 1));
 }

 return hist;
}

void MultiWeightHist::Add(MultiWeightHist *hist2)
{
 if(this->nWeight != hist2->nWeight){
   cout<<"ERROR! Weight size not matching."<<endl;
   return;
 }
 for(int i = 0; i < nWeight; i++){
   this->hist_vector.at(i)->Add((hist2->hist_vector).at(i));
 }
}

void MultiWeightHist::Divide(MultiWeightHist *hist2)
{
 if(this->nWeight != hist2->nWeight){
   cout<<"ERROR! Weight size not matching."<<endl;
   return;
 }
 for(int i = 0; i < nWeight; i++){
   this->hist_vector.at(i)->Divide((hist2->hist_vector).at(i));
 }
}

MultiWeightHist* MultiWeightHist::GetAsymHist(MultiWeightHist *hist2)
{
 MultiWeightHist *hist = Clone(this->name + "_AsymHist");

 if(this->nWeight != hist2->nWeight){
   cout<<"ERROR! Weight size not matching."<<endl;
   return hist;
 }

 hist->Reset();

 for(int i = 0; i < nWeight; i++){
   AFBFunction(this->GetHistPtr(i), hist2->GetHistPtr(i), hist->hist_vector.at(i));
 }

 return hist;
}

void MultiWeightHist::Reset()
{
 for(int i = 0; i < nWeight; i++){
   hist_vector.at(i)->Reset();
 }
}

void MultiWeightHist::DeleteHist()
{
 for(int i = 0; i < nWeight; i++){
   delete hist_vector.at(i);
 }
}

void MultiWeightHist::Write()
{
 for(int i = 0; i < nWeight; i++){
   hist_vector.at(i)->Write();
 }
}

