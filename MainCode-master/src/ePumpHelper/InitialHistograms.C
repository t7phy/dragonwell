#include "ePumpHelper/ePumpHelper.h"

void ePumpHelper::AddHistogram(TH1D* DataHist, vector<TH1D *> TheoryHist, TString DataName, double weight)
{
 int npt = DataHist->GetNbinsX();

 if(TheoryHist.size() != 2 * EU->Ni + 1){
   cout<<"ERROR! Theory size doesn't match with input card!"<<endl;
   return;
 }

 if(TheoryHist.at(0)->GetNbinsX() != DataHist->GetNbinsX()){
   cout<<"ERROR! Theory doesn't match with data!"<<endl;
 }

 ResizeNData(npt, weight);

 for(int ibin = 1; ibin <= TheoryHist.at(0)->GetNbinsX(); ibin++){
   EU->X0[EU->Ndata - 1][ibin - 1] = TheoryHist.at(0)->GetBinContent(ibin);
   for(int i = 0; i < 2 * EU->Ni + 1; i++){
     EU->Xmat[EU->Ndata - 1][ibin - 1][i] = TheoryHist.at(i)->GetBinContent(ibin);
     EU->XmatNew[EU->Ndata - 1][ibin - 1][i] = TheoryHist.at(i)->GetBinContent(ibin);
     EU->Xset[EU->Ndata - 1][i][ibin - 1] = TheoryHist.at(i)->GetBinContent(ibin);
   }
 }

 for(int ibin = 1; ibin <= TheoryHist.at(0)->GetNbinsX(); ibin++){
   for(int i = 0; i < EU->Ni; i++){
     EU->dX[EU->Ndata - 1][ibin - 1][i] = (TheoryHist.at(2 * i + 1)->GetBinContent(ibin) - TheoryHist.at(2 * i + 2)->GetBinContent(ibin)) / 2.0;
   }

   EU->XE[EU->Ndata - 1][ibin - 1] = DataHist->GetBinContent(ibin);
   EU->s[EU->Ndata - 1][ibin - 1] = DataHist->GetBinError(ibin);//Data Err
 }

 EU->dataset[EU->Ndata - 1] = DataName;

 EU->ConstructCm1(EU->Ndata - 1);

 EU->dChi2[EU->Ndata - 1] = EU->DeltaChiSquare(EU->X0[EU->Ndata - 1], EU->Ndata - 1);
 EU->dChi2Set[EU->Ndata - 1].resize(2 * EU->Ni + 1);
 EU->dChi2newSet[EU->Ndata - 1].resize(2 * EU->Ni + 1);

 for(int iEV = 0; iEV < 2 * EU->Ni + 1; iEV++){
   vector<double> TheoryTemplate(1);
   TheoryTemplate.at(0) = EU->Xmat[EU->Ndata - 1][0][iEV];
   EU->dChi2Set[EU->Ndata - 1][iEV] = EU->DeltaChiSquare(TheoryTemplate, EU->Ndata - 1);
   TheoryTemplate.clear();
 }

 EU->SetXdyn(EU->Ndata - 1);

//Calculate Old PDF Uncertainty
 for(int ibin = 1; ibin <= TheoryHist.at(0)->GetNbinsX(); ibin++){
   double Unc2 = 0.0;
   for(int i = 0; i < EU->Ni; i++){
     Unc2 += (EU->Xmat[EU->Ndata - 1][ibin - 1][2 * i + 1] - EU->Xmat[EU->Ndata - 1][ibin - 1][2 * i + 2]) * (EU->Xmat[EU->Ndata - 1][ibin - 1][2 * i + 1] - EU->Xmat[EU->Ndata - 1][ibin - 1][2 * i + 2]) / 4.0;
   }
   EU->OldPDFError[EU->Ndata - 1].at(ibin - 1) = sqrt(Unc2);
 }
}

void ePumpHelper::ResizeNData(int npt, double weight)
{
// EU->Ndata = EU->Ndata + 1;
 EU->Na.resize(EU->Ndata);
 EU->error_type.resize(EU->Ndata);
 EU->dataIncluded.resize(EU->Ndata);
 EU->weight.resize(EU->Ndata);
 EU->Xmat.resize(EU->Ndata);
 EU->XmatNew.resize(EU->Ndata);
 EU->FractionalContribution.resize(EU->Ndata);
 EU->Xset.resize(EU->Ndata);
 EU->dX.resize(EU->Ndata);
 EU->Xdyn.resize(EU->Ndata);
 EU->XXdyn.resize(EU->Ndata);
 EU->X0.resize(EU->Ndata);
 EU->X0new.resize(EU->Ndata);
 EU->Q.resize(EU->Ndata);
 EU->dChi2.resize(EU->Ndata);
 EU->dChi2new.resize(EU->Ndata);
 EU->dChi2Set.resize(EU->Ndata);
 EU->dChi2newSet.resize(EU->Ndata);
 EU->spartynessSave.resize(EU->Ndata);
 EU->spartynessNewSave.resize(EU->Ndata);
 EU->XE.resize(EU->Ndata);
 EU->Cm.resize(EU->Ndata);
 EU->rhocc.resize(EU->Ndata);
 EU->dataset.resize(EU->Ndata);
 EU->theoryset.resize(EU->Ndata);
 EU->error_type_all.resize(EU->Ndata);
 EU->weight_all.resize(EU->Ndata);
 EU->NewTheory.resize(EU->Ndata);
 EU->OldPDFError.resize(EU->Ndata);
 EU->NewPDFError.resize(EU->Ndata);
 EU->OldPDFCorrelation.resize(EU->Ndata);
 EU->NewPDFCorrelation.resize(EU->Ndata);
 for(int idata = 0; idata < EU->Ndata; idata++){
   EU->OldPDFCorrelation[idata].resize(EU->Ndata);
   EU->NewPDFCorrelation[idata].resize(EU->Ndata);
 }

 EU->s.resize(EU->Ndata);
 EU->s_sys.resize(EU->Ndata);
 EU->s_stat.resize(EU->Ndata);
 EU->beta.resize(EU->Ndata);
 EU->calAinvBeta.resize(EU->Ndata);
 EU->Nlam.resize(EU->Ndata);

//overall information

 EU->Na[EU->Ndata - 1] = npt;
 EU->dataIncluded[EU->Ndata - 1] = true;
 EU->error_type[EU->Ndata - 1] = npt;
 EU->weight[EU->Ndata - 1] = weight;//Weight

//theory information

 EU->X0[EU->Ndata - 1].resize(npt);
 EU->X0new[EU->Ndata - 1].resize(npt);
 EU->Xmat[EU->Ndata - 1].resize(npt);
 EU->XmatNew[EU->Ndata - 1].resize(npt);
 EU->FractionalContribution[EU->Ndata - 1].resize(npt);
 EU->Xset[EU->Ndata - 1].resize(2 * EU->Ni + 1);
 EU->dX[EU->Ndata - 1].resize(npt);
 EU->Q[EU->Ndata - 1].resize(npt);
 EU->NewTheory[EU->Ndata - 1].resize(npt);
 EU->OldPDFError[EU->Ndata - 1].resize(npt);
 EU->NewPDFError[EU->Ndata - 1].resize(npt);

 for(int i = 0; i < npt; i++){
   EU->Xmat[EU->Ndata - 1][i].resize(2 * EU->Ni + 1);
   EU->XmatNew[EU->Ndata - 1][i].resize(2 * EU->Ni + 1);
   EU->FractionalContribution[EU->Ndata - 1][i].resize(2 * EU->Ni + 1);
   EU->dX[EU->Ndata - 1][i].resize(EU->Ni);
   EU->Q[EU->Ndata - 1][i].resize(npt);
 }

 for(int i = 0; i < 2 * EU->Ni + 1; i++){
   EU->Xset[EU->Ndata - 1][i].resize(npt);
 }

//data information

 EU->XE[EU->Ndata - 1].resize(npt);
 EU->Cm[EU->Ndata - 1].resize(npt);
 for(int i = 0; i < npt; i++){
   EU->Cm[EU->Ndata - 1][i].resize(npt);
 }

 EU->Nlam[EU->Ndata - 1] = 0;
 EU->s[EU->Ndata - 1].resize(npt);
 EU->beta[EU->Ndata - 1].resize(npt);
 EU->calAinvBeta[EU->Ndata - 1].resize(npt);

}

