#include "ePumpHelper/ePumpHelper.h"

ePump* ePumpHelper::Clone(ePump* inputEU, TString MainName, int isNewPDF)
{
 if(isNewPDF){
   cout<<"**********************************************"<<endl;
   cout<<"****** Starting LM scan for updated PDF ******"<<endl;
   cout<<"**********************************************"<<endl;
 }

 DefineCombination();
 DefineDataLegend();
 NameTransfer();

 ePump* LMScan = new ePump("LMScan", 1.0);
 strcpy(LMScan->mainfile, MainName);
 LMScan->ReadInTheoryAndData();
 strcpy(LMScan->PDFoutfile, ((string)"LMScan/i2Tn3").c_str());
 LMScan->pdftype = PDF_format_type::NONE;
 strcpy(LMScan->mainfile, ((TString)"LMScan").Data());

 return LMScan;
}

ePump* ePumpHelper::Clone(ePump* inputEU)
{
 ePump* outputEU = new ePump("LMScan", 1.0);

 outputEU->Ndata = inputEU->Ndata;
 outputEU->Na = inputEU->Na;
 outputEU->error_type = inputEU->error_type;
 outputEU->dataIncluded = inputEU->dataIncluded;
 outputEU->weight = inputEU->weight;
 outputEU->Xmat = inputEU->Xmat;
 outputEU->XmatNew = inputEU->XmatNew;
 outputEU->FractionalContribution = inputEU->FractionalContribution;
 outputEU->Xset = inputEU->Xset;
 outputEU->dX = inputEU->dX;
 outputEU->Xdyn = inputEU->Xdyn;
 outputEU->XXdyn = inputEU->XXdyn;
 outputEU->X0 = inputEU->X0;
 outputEU->X0new = inputEU->X0new;
 outputEU->Q = inputEU->Q;
 outputEU->dChi2 = inputEU->dChi2;
 outputEU->dChi2new = inputEU->dChi2new;
 outputEU->dChi2Set = inputEU->dChi2Set;
 outputEU->dChi2newSet = inputEU->dChi2newSet;
 outputEU->spartynessSave = inputEU->spartynessSave;
 outputEU->spartynessNewSave = inputEU->spartynessNewSave;
 outputEU->XE = inputEU->XE;
 outputEU->Cm = inputEU->Cm;
 outputEU->rhocc = inputEU->rhocc;
 outputEU->dataset = inputEU->dataset;
 outputEU->theoryset = inputEU->theoryset;
 outputEU->error_type_all = inputEU->error_type_all;
 outputEU->weight_all = inputEU->weight_all;
 outputEU->NewTheory = inputEU->NewTheory;
 outputEU->OldPDFError = inputEU->OldPDFError;
 outputEU->NewPDFError = inputEU->NewPDFError;
 outputEU->OldPDFCorrelation = inputEU->OldPDFCorrelation;
 outputEU->NewPDFCorrelation = inputEU->NewPDFCorrelation;
 outputEU->s = inputEU->s;
 outputEU->s_sys = inputEU->s_sys;
 outputEU->s_stat = inputEU->s_stat;
 outputEU->beta = inputEU->beta;
 outputEU->CorrErrs = inputEU->CorrErrs;
 outputEU->calAinvBeta = inputEU->calAinvBeta;
 outputEU->Nlam = inputEU->Nlam;

 outputEU->Ni = inputEU->Ni;
 outputEU->M = inputEU->M;
 outputEU->A = inputEU->A;
 outputEU->L = inputEU->L;
 outputEU->LinvA = inputEU->LinvA;
 outputEU->TdynP = inputEU->TdynP;
 outputEU->TdynM = inputEU->TdynM;
 outputEU->TdynBar = inputEU->TdynBar;
 outputEU->TdynRMS = inputEU->TdynRMS;
 outputEU->OldPDF = inputEU->OldPDF;
 outputEU->NewPDF = inputEU->NewPDF;
 outputEU->OldPDFAlphaS = inputEU->OldPDFAlphaS;
 outputEU->NewPDFAlphaS = inputEU->NewPDFAlphaS;

 outputEU->suppressCCs();
 outputEU->pdftype = PDF_format_type::NONE;

 return outputEU;
}

void ePumpHelper::AddLMScanConstrain(ePump* &LMScan)
{
 LMScan->suppressCCs();
 LMScan->PerformLMScan();

 LMScan->Ndata = LMScan->Ndata + 1;
 LMScan->Na.resize(LMScan->Ndata);
 LMScan->error_type.resize(LMScan->Ndata);
 LMScan->dataIncluded.resize(LMScan->Ndata);
 LMScan->weight.resize(LMScan->Ndata);
 LMScan->Xmat.resize(LMScan->Ndata);
 LMScan->XmatNew.resize(LMScan->Ndata);
 LMScan->FractionalContribution.resize(LMScan->Ndata);
 LMScan->Xset.resize(LMScan->Ndata);
 LMScan->dX.resize(LMScan->Ndata);
 LMScan->Xdyn.resize(LMScan->Ndata);
 LMScan->XXdyn.resize(LMScan->Ndata);
 LMScan->X0.resize(LMScan->Ndata);
 LMScan->X0new.resize(LMScan->Ndata);
 LMScan->Q.resize(LMScan->Ndata);
 LMScan->dChi2.resize(LMScan->Ndata);
 LMScan->dChi2new.resize(LMScan->Ndata);
 LMScan->dChi2Set.resize(LMScan->Ndata);
 LMScan->dChi2newSet.resize(LMScan->Ndata);
 LMScan->spartynessSave.resize(LMScan->Ndata);
 LMScan->spartynessNewSave.resize(LMScan->Ndata);
 LMScan->XE.resize(LMScan->Ndata);
 LMScan->Cm.resize(LMScan->Ndata);
 LMScan->rhocc.resize(LMScan->Ndata);
 LMScan->dataset.resize(LMScan->Ndata);
 LMScan->theoryset.resize(LMScan->Ndata);
 LMScan->error_type_all.resize(LMScan->Ndata);
 LMScan->weight_all.resize(LMScan->Ndata);
 LMScan->NewTheory.resize(LMScan->Ndata);
 LMScan->OldPDFError.resize(LMScan->Ndata);
 LMScan->NewPDFError.resize(LMScan->Ndata);
 LMScan->OldPDFCorrelation.resize(LMScan->Ndata);
 LMScan->NewPDFCorrelation.resize(LMScan->Ndata);
 for(int idata = 0; idata < LMScan->Ndata; idata++){
   LMScan->OldPDFCorrelation[idata].resize(LMScan->Ndata);
   LMScan->NewPDFCorrelation[idata].resize(LMScan->Ndata);
   LMScan->isLMScanData[idata] = false;
 }

 LMScan->s.resize(LMScan->Ndata);
 LMScan->s_sys.resize(LMScan->Ndata);
 LMScan->s_stat.resize(LMScan->Ndata);
 LMScan->beta.resize(LMScan->Ndata);
 LMScan->CorrErrs.resize(LMScan->Ndata);
 LMScan->calAinvBeta.resize(LMScan->Ndata);
 LMScan->Nlam.resize(LMScan->Ndata);

//overall information

 LMScan->Na[LMScan->Ndata - 1] = 1;
 LMScan->dataIncluded[LMScan->Ndata - 1] = true;
 LMScan->error_type[LMScan->Ndata - 1] = 1;
 LMScan->weight[LMScan->Ndata - 1] = 1;//Weight

//theory information

 LMScan->X0[LMScan->Ndata - 1].resize(1);
 LMScan->X0new[LMScan->Ndata - 1].resize(1);
 LMScan->Xmat[LMScan->Ndata - 1].resize(1);
 LMScan->XmatNew[LMScan->Ndata - 1].resize(1);
 LMScan->FractionalContribution[LMScan->Ndata - 1].resize(1);
 LMScan->Xset[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 LMScan->dX[LMScan->Ndata - 1].resize(1);
 LMScan->Q[LMScan->Ndata - 1].resize(1);
 LMScan->NewTheory[LMScan->Ndata - 1].resize(1);
 LMScan->OldPDFError[LMScan->Ndata - 1].resize(1);
 LMScan->NewPDFError[LMScan->Ndata - 1].resize(1);

 LMScan->Xmat[LMScan->Ndata - 1][0].resize(2 * LMScan->Ni + 1);
 LMScan->XmatNew[LMScan->Ndata - 1][0].resize(2 * LMScan->Ni + 1);
 LMScan->FractionalContribution[LMScan->Ndata - 1][0].resize(2 * LMScan->Ni + 1);
 LMScan->dX[LMScan->Ndata - 1][0].resize(LMScan->Ni);
 LMScan->Q[LMScan->Ndata - 1][0].resize(1);

 for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
   LMScan->Xset[LMScan->Ndata - 1][i].resize(1);
 }


//update dynamical tolerance
/*
 double Chi2Central = 0.0;

 for(int idata = 0; idata < AllDataNames.size(); idata++){

   if(DataIncluded[AllDataNames.at(idata)] && fabs(DataWeight[AllDataNames.at(idata)]) > 1e-20) Chi2Central += NewChi2Set[AllDataNames.at(idata)].at(0);

 }


 for(int idata = 0; idata < AllDataNames.size(); idata++){

        for(int k = 0; k < 2 * EU->Ni + 1; k++){
          cout<<"idata = "<<idata<<" Ni = "<<k<<" Old Chi2 = "<<OldChi2Set[AllDataNames.at(idata)].at(k)<<endl;
          cout<<"idata = "<<idata<<" Ni = "<<k<<" New Chi2 = "<<NewChi2Set[AllDataNames.at(idata)].at(k)<<endl;
        }

 }


 for(int k = 0; k < EU->Ni; k++){

        double TP = 0.0, TM = 0.0;

        double Chi2EVSetPlus = 0.0;
        double Chi2EVSetMinus = 0.0;

        for(int idata = 0; idata < AllDataNames.size(); idata++){
          if(DataIncluded[AllDataNames.at(idata)] && fabs(DataWeight[AllDataNames.at(idata)]) > 1e-20) Chi2EVSetPlus += NewChi2Set[AllDataNames.at(idata)].at(2 * k + 1);
          if(DataIncluded[AllDataNames.at(idata)] && fabs(DataWeight[AllDataNames.at(idata)]) > 1e-20) Chi2EVSetMinus += NewChi2Set[AllDataNames.at(idata)].at(2 * k + 2);
        }

        TP = sqrt(Chi2EVSetPlus - Chi2Central);
        TM = sqrt(Chi2EVSetMinus - Chi2Central);

        cout<<"EV"<<k + 1<<": Central = "<<Chi2Central<<"  Plus = "<<Chi2EVSetPlus<<"  Plus - Central = "<<Chi2EVSetPlus - Chi2Central<<"  Minus = "<<Chi2EVSetMinus<<"  Minus - Central = "<<Chi2EVSetMinus - Chi2Central<<endl;

        if(isNewPDF){
          LMScan->TdynP[k] = TP;
          LMScan->TdynM[k] = TM;
          LMScan->TdynBar[k] = (TP + TM) / 2.0;
        }
 }

 if(isNewPDF){
   cout<<"Updated Dynamical Tolerance:"<<endl;
   cout<<"   i      TdynP[i]    TdynM[i]    TdynBar[i]  "<<endl;
 }

 for(int k = 0; k < EU->Ni; k++){

        if(isNewPDF){
          cout<<"  "<<setw(2)<<k+1<<setw(12)<<fixed<<setprecision(2)<<LMScan->TdynP[k]<<setw(12)<<LMScan->TdynM[k]<<setw(12)<<LMScan->TdynBar[k]<<endl;

          LMScan->TdynP[k] /= EU->Tfix;
          LMScan->TdynM[k] /= EU->Tfix;
          LMScan->TdynBar[k] /= EU->Tfix;
        }
 }
 //sleep(30);

//using updated theory information

 if(isNewPDF){
      for(int idata = 0; idata < LMScan->Ndata - 1; idata++){
     
        for(int ipoint = 0; ipoint < LMScan->X0[idata].size(); ipoint++){
     
          LMScan->X0[idata].at(ipoint) = GetNewTheory(AllDataNames.at(idata), ipoint);
     
          for(int iPDF = 0; iPDF < LMScan->Xmat[idata].at(0).size(); iPDF++){
            LMScan->Xmat[idata].at(ipoint).at(iPDF) = GetNewTheoryTemplate(AllDataNames.at(idata), ipoint, iPDF);
            LMScan->XmatNew[idata].at(ipoint).at(iPDF) = GetNewTheoryTemplate(AllDataNames.at(idata), ipoint, iPDF);
            LMScan->Xset[idata].at(iPDF).at(ipoint) = GetNewTheoryTemplate(AllDataNames.at(idata), ipoint, iPDF);
          }
     
          for(int i = 0; i < LMScan->Ni; i++){
            LMScan->dX[idata][ipoint][i] = (GetNewTheoryTemplate(AllDataNames.at(idata), ipoint, 2 * i + 1) - GetNewTheoryTemplate(AllDataNames.at(idata), ipoint, 2 * i + 2)) / 2.0;
          }
     
        }
     
        LMScan->dChi2[idata] = LMScan->DeltaChiSquare(LMScan->X0[idata], idata);
      
        for(int iEV = 0; iEV < 2 * LMScan->Ni + 1; iEV++){
          vector<double> TheoryTemplate(LMScan->X0[idata].size());
          for(int a=0;a<LMScan->X0[idata].size();a++){
            TheoryTemplate.at(a) = LMScan->Xmat[idata][a][iEV];
          }
          LMScan->dChi2Set[idata][iEV] = LMScan->DeltaChiSquare(TheoryTemplate, idata);
          cout<<"new Chi2: idata = "<<idata<<" iEV = "<<iEV<<" chi2 = "<<LMScan->dChi2Set[idata][iEV]<<endl;
          TheoryTemplate.clear();
        } 
     
        LMScan->SetXdyn(idata);
     
      }
 }
*/

//data information

 LMScan->XE[LMScan->Ndata - 1].resize(1);
 LMScan->Cm[LMScan->Ndata - 1].resize(1);
 LMScan->Cm[LMScan->Ndata - 1][0].resize(1);

 LMScan->Nlam[LMScan->Ndata - 1] = 0;
 LMScan->s[LMScan->Ndata - 1].resize(1);
 LMScan->beta[LMScan->Ndata - 1].resize(1);
 LMScan->CorrErrs[LMScan->Ndata - 1].resize(1);
 LMScan->calAinvBeta[LMScan->Ndata - 1].resize(1);

//reset all data's weight to zero
 for(int i = 0; i < LMScan->weight.size(); i++){
   LMScan->weight.at(i) = 0.0;
 }
}

void ePumpHelper::AddLMData(TString DataName, int ipoint)
{
 LMScan->X0[LMScan->Ndata - 1][0] = TheoryTemplate[DataName].at(ipoint).at(0);//Theory Point, from 0
 for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
   LMScan->Xmat[LMScan->Ndata - 1][0][i] = TheoryTemplate[DataName].at(ipoint).at(i);
   LMScan->XmatNew[LMScan->Ndata - 1][0][i] = TheoryTemplate[DataName].at(ipoint).at(i);
   LMScan->Xset[LMScan->Ndata - 1][i][0] = TheoryTemplate[DataName].at(ipoint).at(i);
 }

 for(int i = 0; i < LMScan->Ni; i++){
   LMScan->dX[LMScan->Ndata - 1][0][i] = (TheoryTemplate[DataName].at(ipoint).at(2 * i + 1) - TheoryTemplate[DataName].at(ipoint).at(2 * i + 2)) / 2.0;
 }

// LMScan->XE[LMScan->Ndata - 1][0] = DataPoint[DataName].at(ipoint);//Data Point, from 0
 LMScan->XE[LMScan->Ndata - 1][0] = TheoryTemplate[DataName].at(ipoint).at(0);//Data Point (to be the same as theory), from 0
 LMScan->s[LMScan->Ndata - 1][0] = 1.0;//Data Err
 LMScan->dataset[LMScan->Ndata - 1] = "LMConstrain";
 LMScan->SetLMScanData(LMScan->Ndata - 1);

 LMScan->ConstructCm1(LMScan->Ndata - 1);

 LMScan->dChi2[LMScan->Ndata - 1] = LMScan->DeltaChiSquare(LMScan->X0[LMScan->Ndata - 1], LMScan->Ndata - 1);
 LMScan->dChi2Set[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 LMScan->dChi2newSet[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);

 for(int iEV = 0; iEV < 2 * LMScan->Ni + 1; iEV++){
   vector<double> TheoryTemplate(1);
   TheoryTemplate.at(0) = LMScan->Xmat[LMScan->Ndata - 1][0][iEV];
   LMScan->dChi2Set[LMScan->Ndata - 1][iEV] = LMScan->DeltaChiSquare(TheoryTemplate, LMScan->Ndata - 1);
   TheoryTemplate.clear();
 }

 LMScan->SetXdyn(LMScan->Ndata - 1);

}

void ePumpHelper::AddLMPDF(int flavor, double x, double Q, int isNewPDF)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

// if(isNewPDF){
//   LMScan->X0[LMScan->Ndata - 1][0] = NewPDFSet.at(0)->Getf(flavor, x, Q);
//   for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
//     LMScan->Xmat[LMScan->Ndata - 1][0][i] = NewPDFSet.at(i)->Getf(flavor, x, Q);
//     LMScan->XmatNew[LMScan->Ndata - 1][0][i] = NewPDFSet.at(i)->Getf(flavor, x, Q);
//     LMScan->Xset[LMScan->Ndata - 1][i][0] = NewPDFSet.at(i)->Getf(flavor, x, Q);
//   }
// }
// if(!isNewPDF){
   LMScan->X0[LMScan->Ndata - 1][0] = OldPDFSet.at(0)->Getf(flavor, x, Q);
   for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
     LMScan->Xmat[LMScan->Ndata - 1][0][i] = OldPDFSet.at(i)->Getf(flavor, x, Q);
     LMScan->XmatNew[LMScan->Ndata - 1][0][i] = OldPDFSet.at(i)->Getf(flavor, x, Q);
     LMScan->Xset[LMScan->Ndata - 1][i][0] = OldPDFSet.at(i)->Getf(flavor, x, Q);
   }
// }

 for(int i = 0; i < LMScan->Ni; i++){
   //if(isNewPDF) LMScan->dX[LMScan->Ndata - 1][0][i] = (NewPDFSet.at(2 * i + 1)->Getf(flavor, x, Q) - NewPDFSet.at(2 * i + 2)->Getf(flavor, x, Q)) / 2.0;
   //if(!isNewPDF) LMScan->dX[LMScan->Ndata - 1][0][i] = (OldPDFSet.at(2 * i + 1)->Getf(flavor, x, Q) - OldPDFSet.at(2 * i + 2)->Getf(flavor, x, Q)) / 2.0;
   LMScan->dX[LMScan->Ndata - 1][0][i] = (OldPDFSet.at(2 * i + 1)->Getf(flavor, x, Q) - OldPDFSet.at(2 * i + 2)->Getf(flavor, x, Q)) / 2.0;
 }

 //if(isNewPDF) LMScan->XE[LMScan->Ndata - 1][0] = NewPDFSet.at(0)->Getf(flavor, x, Q);//Data Point (to be the same as theory), from 0
 //if(!isNewPDF) LMScan->XE[LMScan->Ndata - 1][0] = OldPDFSet.at(0)->Getf(flavor, x, Q);//Data Point (to be the same as theory), from 0
 LMScan->XE[LMScan->Ndata - 1][0] = OldPDFSet.at(0)->Getf(flavor, x, Q);//Data Point (to be the same as theory), from 0

 LMScan->s[LMScan->Ndata - 1][0] = 1.0;//Data Err
 LMScan->dataset[LMScan->Ndata - 1] = "LMConstrain";
 LMScan->SetLMScanData(LMScan->Ndata - 1);
 
 LMScan->ConstructCm1(LMScan->Ndata - 1);
 
 LMScan->dChi2[LMScan->Ndata - 1] = LMScan->DeltaChiSquare(LMScan->X0[LMScan->Ndata - 1], LMScan->Ndata - 1);
 LMScan->dChi2Set[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 LMScan->dChi2newSet[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 
 for(int iEV = 0; iEV < 2 * LMScan->Ni + 1; iEV++){
   vector<double> TheoryTemplate(1);
   TheoryTemplate.at(0) = LMScan->Xmat[LMScan->Ndata - 1][0][iEV];
   LMScan->dChi2Set[LMScan->Ndata - 1][iEV] = LMScan->DeltaChiSquare(TheoryTemplate, LMScan->Ndata - 1);
   TheoryTemplate.clear();
 }
 
 LMScan->SetXdyn(LMScan->Ndata - 1);

//Calculate Old PDF Uncertainty
 double Unc2 = 0.0;
 for(int i = 0; i < LMScan->Ni; i++){
   Unc2 += (LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 1] - LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 2]) * (LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 1] - LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 2]) / 4.0;
 }
 LMScan->OldPDFError[LMScan->Ndata - 1].at(0) = sqrt(Unc2);

}

void ePumpHelper::AddLMAlphaS(double Q)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 LMScan->X0[LMScan->Ndata - 1][0] = OldPDFSet.at(0)->CT14Alphas(Q);
 for(int i = 0; i < 2 * LMScan->Ni + 1; i++){
   LMScan->Xmat[LMScan->Ndata - 1][0][i] = OldPDFSet.at(i)->CT14Alphas(Q);
   LMScan->XmatNew[LMScan->Ndata - 1][0][i] = OldPDFSet.at(i)->CT14Alphas(Q);
   LMScan->Xset[LMScan->Ndata - 1][i][0] = OldPDFSet.at(i)->CT14Alphas(Q);
 }

 for(int i = 0; i < LMScan->Ni; i++){
   LMScan->dX[LMScan->Ndata - 1][0][i] = (OldPDFSet.at(2 * i + 1)->CT14Alphas(Q) - OldPDFSet.at(2 * i + 2)->CT14Alphas(Q)) / 2.0;
   cout<<fixed<<setprecision(4)<<2 * i + 1<<":  "<<OldPDFSet.at(2 * i + 1)->CT14Alphas(Q)<<"  "<<2 * i + 2<<":  "<<OldPDFSet.at(2 * i + 2)->CT14Alphas(Q)<<endl;
 }

 LMScan->XE[LMScan->Ndata - 1][0] = OldPDFSet.at(0)->CT14Alphas(Q);//Data Point (to be the same as theory), from 0
 cout<<fixed<<setprecision(4)<<"Data:  "<<OldPDFSet.at(0)->CT14Alphas(Q)<<endl;
 LMScan->s[LMScan->Ndata - 1][0] = 1.0;//Data Err
 LMScan->dataset[LMScan->Ndata - 1] = "LMConstrainAlphaS";
 LMScan->SetLMScanData(LMScan->Ndata - 1);

 LMScan->ConstructCm1(LMScan->Ndata - 1);

 LMScan->dChi2[LMScan->Ndata - 1] = LMScan->DeltaChiSquare(LMScan->X0[LMScan->Ndata - 1], LMScan->Ndata - 1);
 LMScan->dChi2Set[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);
 LMScan->dChi2newSet[LMScan->Ndata - 1].resize(2 * LMScan->Ni + 1);

 for(int iEV = 0; iEV < 2 * LMScan->Ni + 1; iEV++){
   vector<double> TheoryTemplate(1);
   TheoryTemplate.at(0) = LMScan->Xmat[LMScan->Ndata - 1][0][iEV];
   LMScan->dChi2Set[LMScan->Ndata - 1][iEV] = LMScan->DeltaChiSquare(TheoryTemplate, LMScan->Ndata - 1);
   TheoryTemplate.clear();
 }
 
 LMScan->SetXdyn(LMScan->Ndata - 1);

//Calculate Old PDF Uncertainty
 double Unc2 = 0.0;
 for(int i = 0; i < LMScan->Ni; i++){
   Unc2 += (LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 1] - LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 2]) * (LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 1] - LMScan->Xmat[LMScan->Ndata - 1][0][2 * i + 2]) / 4.0;
 }
 LMScan->OldPDFError[LMScan->Ndata - 1].at(0) = sqrt(Unc2);
 cout<<fixed<<setprecision(4)<<"Uncertainty of alpha_s = "<<sqrt(Unc2)<<endl;
}

void ePumpHelper::ScanLambda(TString DataName, int ipoint, int isNewPDF, TString TitleName)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 cout<<"Starting Lagrange Multiplier Scan"<<endl;

 if(isLinkFile) hf->cd();

 if(isNewPDF){
   for(int i = 0; i < EU->weight.size(); i++){
     LMScan->weight.at(i) = EU->weight.at(i);
   }
 }
 else{
   for(int i = 0; i < EU->weight.size(); i++){
     LMScan->weight.at(i) = 0.0;
   }
 }

 //1sigma uncertainty will be at +- 2 * Tsq / Delta_X

 int nScanPoint = 10;

 vector<double> LambdaSet(nScanPoint);
 vector<double> Chi2Set(nScanPoint);
 vector<double> BestFitSet(nScanPoint);
 double step = 8.0 * LMScan->Tsq / OldPDFError[DataName].at(ipoint) / ((double)nScanPoint / 2.0);
 for(int i = 0; i < LambdaSet.size(); i++){
   cout<<"Scan "<<i + 1<<endl;
   LambdaSet.at(i) = -8.0 * LMScan->Tsq / OldPDFError[DataName].at(ipoint) + step * i;

   LMScan->weight[LMScan->Ndata - 1] = LambdaSet.at(i);
   LMScan->ConstructUpdateMatrix();
   LMScan->UpdateObservables();

//   Chi2Set.at(i) = fabs(LMScan->Tsq / pow(OldPDFError[DataName].at(ipoint), 2.0) * pow((LMScan->NewTheory.at(LMScan->Ndata - 1).at(0) - LMScan->X0.at(LMScan->Ndata - 1).at(0)), 2.0));
   Chi2Set.at(i) = LMScan->Tsq * LMScan->NewLength * LMScan->NewLength;
   BestFitSet.at(i) = LMScan->NewTheory.at(LMScan->Ndata - 1).at(0);
 }

 double xmin = BestFitSet.at(0) - (BestFitSet.at(1) - BestFitSet.at(0));
 double xmax = BestFitSet.at(nScanPoint - 1) + (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));

 TString HistName = (TString)"LMScanResult_" + DataName + "_" + (int)(ipoint + 1);
 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");
 TString FittingName = (TString)"LMScanFitting_" + DataName + "_" + (int)(ipoint + 1);
 FittingName.ReplaceAll("/", "_");
 FittingName.ReplaceAll(".", "_");
 TString PointName = (TString)"LMScanPoint_" + DataName + "_" + (int)(ipoint + 1);
 PointName.ReplaceAll("/", "_");
 PointName.ReplaceAll(".", "_");

 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)] = new TGraph(nScanPoint);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetName(HistName);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetTitle(HistName);

 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)] = new TGraph(nScanPoint);
 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetName(PointName);
 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetTitle(PointName);

 for(int ibin = 1; ibin <= nScanPoint; ibin++){
   LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
   LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetPointY(ibin, Chi2Set.at(ibin - 1));
   LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
   LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->SetPointY(ibin, Chi2Set.at(ibin - 1));
   cout<<"ScanResult: Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Set.at(ibin - 1)<<endl;
 }
 LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->RemovePoint(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->RemovePoint(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetMarkerSize(2);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetLineWidth(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetLineColor(0);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetLineStyle(1);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->SetMarkerStyle(34);

 LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
 LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->Fit(LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)], "W");

 double par[3];
 LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)]->GetParameters(par);

 double Central = -par[1] / (2 * par[0]);
 double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
 double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
 double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);

 cout<<"T2 = "<<LMScan->Tsq<<endl;
 cout<<"MinChi2 = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;

 if(isLinkFile){
   LMScanResult[make_tuple(DataName, ipoint, isNewPDF)]->Write();
   LMScanFitting[make_tuple(DataName, ipoint, isNewPDF)]->Write();
   LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)]->Write();
 }

 ////////////////
 //  Plotting  //
 ////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TString FigureName;
 FigureName = (TString)"LMScan_" + DataName + "_Point" + (int)(ipoint + 1) + ".pdf";
 FigureName.ReplaceAll("/", "_");

 Graph* g;

 g = new Graph(FigureName, TitleName, "#Delta #chi^{2}");
 g->SetMode("CUSTOM");
 g->InputGraph(1, (TGraphErrors *)LMScanResult[make_tuple(DataName, ipoint, isNewPDF)], "");
 g->InputGraph(2, (TGraphErrors *)LMScanPoint[make_tuple(DataName, ipoint, isNewPDF)], "");
 g->Compare("MultiSimple");
 g->SetCustomPlot(1, 1, "AC");
 g->SetCustomPlot(1, 2, "Point");
 g->SetCustomPlotFormat(1, 2, kBlack);
 g->Draw();
 delete g;

 if(LMScanResult.count(make_tuple(DataName, ipoint, 0)) > 0 && LMScanResult.count(make_tuple(DataName, ipoint, 1)) > 0 && LMScanResult.count(make_tuple(DataName, ipoint, 2)) > 0){
   FigureName = (TString)"LMScan_" + DataName + "_Point" + (int)(ipoint + 1) + "_Compare3Plot.pdf";
   FigureName.ReplaceAll("/", "_");

   g = new Graph(FigureName, TitleName, "#Delta #chi^{2}");
   g->SetMode("CUSTOM");
   g->InputGraph(1, (TGraphErrors *)LMScanResult[make_tuple(DataName, ipoint, 0)], "Before update");
   g->InputGraph(2, (TGraphErrors *)LMScanPoint[make_tuple(DataName, ipoint, 0)], "");
   g->InputGraph(3, (TGraphErrors *)LMScanResult[make_tuple(DataName, ipoint, 1)], "After update (PDF only)");
   g->InputGraph(4, (TGraphErrors *)LMScanPoint[make_tuple(DataName, ipoint, 1)], "");
   g->InputGraph(5, (TGraphErrors *)LMScanResult[make_tuple(DataName, ipoint, 2)], "After update (PDF + #alpha_{S})");
   g->InputGraph(6, (TGraphErrors *)LMScanPoint[make_tuple(DataName, ipoint, 2)], "");
   g->Compare("MultiSimple");
   g->SetCustomPlot(1, 1, "AC");
   g->SetCustomPlot(1, 2, "Point");
   g->SetCustomPlot(1, 3, "AC");
   g->SetCustomPlot(1, 4, "Point");
   g->SetCustomPlot(1, 5, "AC");
   g->SetCustomPlot(1, 6, "Point");
   g->SetCustomPlotFormat(1, 1, kBlue);
   g->SetCustomPlotFormat(1, 2, kBlue+1);
   g->SetCustomPlotFormat(1, 3, kRed);
   g->SetCustomPlotFormat(1, 4, kRed+1);
   g->SetCustomPlotFormat(1, 5, kGreen);
   g->SetCustomPlotFormat(1, 6, kGreen+1);
   g->SetLegendPosition(0.05, 0.7, 0.5, 0.95);
   g->Draw();
 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

void ePumpHelper::ScanLambdaPDF(int flavor, double x, double Q, int isNewPDF)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 cout<<"Starting Lagrange Multiplier Scan"<<endl;

 if(isLinkFile) hf->cd();

 if(isNewPDF){
   for(int i = 0; i < EU->weight.size(); i++){
     LMScan->weight.at(i) = EU->weight.at(i);
   }
 }
 else{
   for(int i = 0; i < EU->weight.size(); i++){
     LMScan->weight.at(i) = 0.0;
   }
 }

 //1sigma uncertainty will be at +- 2 * Tsq / Delta_X

 int nScanPoint = 10;

 vector<double> LambdaSet(nScanPoint);
 vector<double> BestFitSet(nScanPoint);

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < AllDataNames.size(); idata++){
   Chi2Map[AllDataNames.at(idata)].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 double nTimesUnc = 1.0;
 //if(isNewPDF) nTimesUnc = 24.0;

 double step = nTimesUnc * LMScan->Tsq / LMScan->OldPDFError[LMScan->Ndata - 1].at(0) / ((double)nScanPoint / 2.0);
 for(int i = 0; i < LambdaSet.size(); i++){
   cout<<"Scan "<<i + 1<<endl;
   LMScan->ePout<<"Scan "<<i + 1<<endl;

   LambdaSet.at(i) = (-1.0) * nTimesUnc * LMScan->Tsq / LMScan->OldPDFError[LMScan->Ndata - 1].at(0) + step * i;

   LMScan->weight[LMScan->Ndata - 1] = LambdaSet.at(i);
   LMScan->ConstructUpdateMatrix();
   LMScan->UpdateObservables();

   BestFitSet.at(i) = LMScan->NewTheory.at(LMScan->Ndata - 1).at(0);
   double TotalDeltaChi2 = 0.0;
   for(int idata = 0; idata < AllDataNames.size(); idata++){
     //Chi2Map[AllDataNames.at(idata)].at(i) = LMScan->dChi2new.at(idata) - LMScan->dChi2.at(idata);
     //TotalDeltaChi2 += LMScan->dChi2new.at(idata) - LMScan->dChi2.at(idata);
     //Chi2Map[AllDataNames.at(idata)].at(i) = LMScan->dChi2new.at(idata);
     //TotalDeltaChi2 += LMScan->dChi2new.at(idata);

     Chi2Map[AllDataNames.at(idata)].at(i) = LMScan->DeltaChiSquareReal(LMScan->NewTheory.at(idata), idata);
   }

   // Calculate Total Delta Chi2, T^2 * sum z_i*2;
   //Chi2Map[(TString)"Total"].at(i) = TotalDeltaChi2;
   Chi2Map[(TString)"Total"].at(i) = LMScan->Tsq * pow(LMScan->NewLength, 2);
 }

 double BestFitSolution = Chi2Solution(BestFitSet, Chi2Map[(TString)"Total"]);//find the bestfit of the total chi2
 double SortingSolution = Chi2Solution(BestFitSet, Chi2Map[(TString)"Total"], LMScan->Tsq);//sorting

 double xmin = BestFitSet.at(0) - 20.0 * (BestFitSet.at(1) - BestFitSet.at(0));
 double xmax = BestFitSet.at(nScanPoint - 1) + 20.0 * (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));
 double PlotXMin = 0.0;
 double PlotXMax = 0.0;

 stringstream s_Qstring;
 TString Qstring;
 s_Qstring<<fixed<<setprecision(2)<<Q;
 Qstring = s_Qstring.str();

 stringstream s_xstring;
 stringstream s_xstring_fixed;
 TString xstring;
 TString xstring_fixed;
 s_xstring<<scientific<<setprecision(2)<<x;
 xstring = s_xstring.str();
 s_xstring_fixed<<fixed<<setprecision(2)<<x;
 xstring_fixed = s_xstring_fixed.str();

 map<double, TString> LMErrors;
 map<double, TString> ChiSquare1InverseMap;
 map<double, TString> ChiSquare2InverseMap;
 map<TString, double> ChiSquare1;
 map<TString, double> ChiSquare2;

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   TString HistName;
   if(isNewPDF) HistName = (TString)"UpdatedPDFLMScanOriginResult_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   if(!isNewPDF) HistName = (TString)"PDFLMScanOriginResult_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");

   TString FittingName;
   if(isNewPDF) FittingName = (TString)"UpdatedPDFLMScanOriginFitting_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   if(!isNewPDF) FittingName = (TString)"PDFLMScanOriginFitting_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");

   TString PointName;
   if(isNewPDF) PointName = (TString)"UpdatedPDFLMScanOriginPoint_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   if(!isNewPDF) PointName = (TString)"PDFLMScanOriginPoint_" + iter->first + "_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");

   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(HistName);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(HistName);
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(PointName);
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(PointName);
  
   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1) - BestFitSolution);
     PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     cout<<"ScanResult for Data "<<iter->first<<" : Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1)<<endl;
     LMScan->ePout<<"ScanResult for Data "<<iter->first<<" : Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1)<<endl;
   }
   PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerSize(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerColor(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineWidth(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineColor(0);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineStyle(1);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerStyle(34);
  
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Fit(PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)], "W");

   double par1 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(0);
   double par2 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(1);
   double par3 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(2);
   double newpar1 = par1;
   double newpar2 = -1.0 * (2.0 * par1 * BestFitSolution - par2);
   double newpar3 = par1 * BestFitSolution * BestFitSolution - par2 * BestFitSolution + par3;
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(0, newpar1);
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(1, newpar2);
   PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(2, newpar3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   HistName.ReplaceAll("PDFLMScanOriginResult", "PDFLMScanResult");
   FittingName.ReplaceAll("PDFLMScanOriginFitting", "PDFLMScanFitting");
   PointName.ReplaceAll("PDFLMScanOriginPoint", "PDFLMScanPoint");

   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(HistName);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(HistName);
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TGraph(nScanPoint);
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetName(PointName);
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(BestFitSolution);

     PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1) - BestFitSolution);
     PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     cout<<"ScanResult(After subtract) for Data "<<iter->first<<" : Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2<<endl;
     LMScan->ePout<<"ScanResult(After subtract) for Data "<<iter->first<<" : Lambda = "<<LambdaSet.at(ibin - 1)<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2<<endl;
   }
   PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->RemovePoint(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerSize(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerColor(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineWidth(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineColor(0);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetLineStyle(1);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetMarkerStyle(34);

   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetNpx(50000);
   PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Fit(PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)], "W");

   par1 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(0);
   par2 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(1);
   par3 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameter(2);
   newpar1 = par1;
   newpar2 = -1.0 * (2.0 * par1 * BestFitSolution - par2);
   newpar3 = par1 * BestFitSolution * BestFitSolution - par2 * BestFitSolution + par3;
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(0, newpar1);
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(1, newpar2);
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->SetParameter(2, newpar3);
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   double par[3];
   PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->GetParameters(par);
  
   double Central = -par[1] / (2 * par[0]);
   double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
   double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
   double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
   double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * LMScan->Tsq - 50.0))) / (2 * par[0]);
   double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * LMScan->Tsq - 50.0))) / (2 * par[0]);

   cout<<"T2 = "<<LMScan->Tsq<<endl;
   cout<<"MinChi2 for Data "<<iter->first<<" = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;
   LMScan->ePout<<"T2 = "<<LMScan->Tsq<<endl;
   LMScan->ePout<<"MinChi2 for Data "<<iter->first<<" = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;

   if(iter->first == "Total"){
     PlotXMin = Solution1;
     PlotXMax = Solution2;

     if(!isSetPDFLMScanXRange[make_tuple(flavor, x, Q)]){
       PDFLMScanPlotXMin[make_tuple(flavor, x, Q, isNewPDF)]  = Solution3;
       PDFLMScanPlotXMax[make_tuple(flavor, x, Q, isNewPDF)]  = Solution4;
     }

     SortingSolution = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);//sorting
   }

   double SortingSolutionChi2 = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(SortingSolution);

   //if(iter->first != "Total") LMErrors[SortingSolutionChi2 * (-1.0)] = iter->first;//sorting
   if(iter->first != "Total") LMErrors[(Solution2 - Solution1) / 2.0] = iter->first;//sorting
   if(iter->first != "Total") ChiSquare1[iter->first] = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMin);
   if(iter->first != "Total") ChiSquare2[iter->first] = PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMax);
   if(iter->first != "Total") ChiSquare1InverseMap[1.0 - PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMin)] = iter->first;
   if(iter->first != "Total") ChiSquare2InverseMap[1.0 - PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Eval(PlotXMax)] = iter->first;

   if(isLinkFile){
     PDFLMScanOriginResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanOriginFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanOriginPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanResult[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanFitting[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
     PDFLMScanPoint[make_tuple(iter->first, flavor, x, Q, isNewPDF)]->Write();
   }
 }

 ////////////////
 //  Plotting  //
 ////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TString FigureName;
 if(isNewPDF) FigureName = (TString)"PDFLMScanUpdated_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring + ".pdf";
 if(!isNewPDF) FigureName = (TString)"PDFLMScan_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring + ".pdf";
 TString XaxisName = TitleMap[flavor] + "(x = " + xstring_fixed + ", Q = " + Qstring + " GeV)";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, PDFLMScanFitting[make_tuple((TString)"Total", flavor, x, Q, isNewPDF)], "Total");

 int iplot = 2;

 if(LMScanDrawList.size() == 0){
   for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
     if(iplot >= 15) break;
     f->InputTF1(iplot, PDFLMScanFitting[make_tuple(iter->second, flavor, x, Q, isNewPDF)], DataLegend[NickNameMap[iter->second]]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < LMScanDrawList.size(); i++){
     f->InputTF1(i + 2, PDFLMScanFitting[make_tuple(LMScanDrawList.at(i), flavor, x, Q, isNewPDF)], DataLegend[NickNameMap[LMScanDrawList.at(i)]]);
   }
 }

 //f->InputTF1(iplot, PDFLMScanFitting[make_tuple("tabsCT18Am253/ZpT_as0118", flavor, x, Q, isNewPDF)], DataLegend[NickNameMap["tabsCT18Am253/ZpT_as0118"]]);

 double LegendYMin = 0.4;
 if(LMScanDrawList.size() >= 13) LegendYMin = 0.4 - (LMScanDrawList.size() - 13) * 0.05;

 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, LegendYMin, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(PDFLMScanPlotXMin[make_tuple(flavor, x, Q, isNewPDF)], PDFLMScanPlotXMax[make_tuple(flavor, x, Q, isNewPDF)]);
 f->SetCustomYRange(1, -20, 50);
 f->SetCustomXTitleOffset(1, 1.0);

 if(LMScanDrawList.size() == 0){
   for(int i = 2; i <= 16; i++){
     f->SetCustomLineStyle(1, i, PlotLineStyle[i]);
   }
 }
 else{
   for(int i = 1; i <= LMScanDrawList.size(); i++){
     f->SetCustomLineStyle(1, i + 1, PlotLineStyle[i + 1]);
   }
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();


 iplot = 2;
 for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
   //if(iplot >= 11) break;
   cout<<fixed<<setprecision(3)<<iter->second<<": "<<iter->first * (-1.0)<<endl;
   iplot++;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 LMErrors.clear();
 Chi2Map.clear();
}

void ePumpHelper::ScanLambdaAlphaS(double Q)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 cout<<"Starting Lagrange Multiplier Scan"<<endl;

 if(isLinkFile) hf->cd();

 //1sigma uncertainty will be at +- 2 * Tsq / Delta_X

 int nScanPoint = 20;//yfu search here

 vector<double> AlphaSSet(nScanPoint);
 vector<double> BestFitSet(nScanPoint);

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < AllDataNames.size(); idata++){
   Chi2Map[AllDataNames.at(idata)].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 double Old_AlphaS_GA = OldPDFSet.at(0)->CT14Alphas(Q);
 double Old_Delta_AlphaS = (OldPDFSet.at(1)->CT14Alphas(Q) - OldPDFSet.at(2)->CT14Alphas(Q)) / 2.0;
 double Old_Delta_AlphaS_up = OldPDFSet.at(1)->CT14Alphas(Q) - OldPDFSet.at(0)->CT14Alphas(Q);

 double step = (0.126 - 0.110) / (double)(nScanPoint - 1);
 for(int i = 0; i < AlphaSSet.size(); i++){
   cout<<"Scan "<<i + 1<<endl;
   AlphaSSet.at(i) = 0.110 + step * i;

   double TotalDeltaChi2 = 0.0;
   for(int idata = 0; idata < AllDataNames.size(); idata++){

     vector<double> TheoryVector(EU->Na[idata]);
     for(int ipoint = 0; ipoint < EU->Na[idata]; ipoint++){
       double Value = EU->Xmat.at(idata).at(ipoint).at(0);

       if((AlphaSSet.at(i) - Old_AlphaS_GA) * Old_Delta_AlphaS_up > 0){
         Value = Value + (AlphaSSet.at(i) - Old_AlphaS_GA) / Old_Delta_AlphaS * (EU->Xmat.at(idata).at(ipoint).at(1) - EU->Xmat.at(idata).at(ipoint).at(0));
       }
       else{
         Value = Value + (AlphaSSet.at(i) - Old_AlphaS_GA) / Old_Delta_AlphaS * (EU->Xmat.at(idata).at(ipoint).at(0) - EU->Xmat.at(idata).at(ipoint).at(2));
       }

       TheoryVector.at(ipoint) = Value;
     }

     Chi2Map[(TString)EU->dataset[idata]].at(i) = EU->DeltaChiSquareReal(TheoryVector, idata);
   }

   Chi2Map[(TString)"Total"].at(i) = EU->Tsq * pow((AlphaSSet.at(i) - Old_AlphaS_GA) / Old_Delta_AlphaS, 2);
 }

 BestFitSet = AlphaSSet;

 double BestFitSolution = Chi2Solution(BestFitSet, Chi2Map[(TString)"Total"]);//find the bestfit of the total chi2

 double xmax = BestFitSet.at(0) - 3.0 * (BestFitSet.at(1) - BestFitSet.at(0));
 double xmin = BestFitSet.at(nScanPoint - 1) + 3.0 * (BestFitSet.at(nScanPoint - 1) - BestFitSet.at(nScanPoint - 2));
 double PlotXMin = 0.0;
 double PlotXMax = 0.0;

 stringstream s_Qstring;
 TString Qstring;
 s_Qstring<<fixed<<setprecision(2)<<Q;
 Qstring = s_Qstring.str();

 map<double, TString> LMErrors;
 map<double, TString> ChiSquare1Map;
 map<double, TString> ChiSquare2Map;
 map<TString, double> ChiSquare1;
 map<TString, double> ChiSquare2;

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   TString HistName = (TString)"AlphaSLMScanOriginResult_" + iter->first;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");
   TString FittingName = (TString)"AlphaSLMScanOriginFitting_" + iter->first;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");
   TString PointName = (TString)"AlphaSLMScanOriginPoint_" + iter->first;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");


   AlphaSLMScanOriginResult[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetName(HistName);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetTitle(HistName);

   AlphaSLMScanOriginPoint[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetName(PointName);
   AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanOriginPoint[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1));
     cout<<"ScanResult for Data "<<iter->first<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1)<<endl;
   }
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->RemovePoint(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetMarkerSize(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetMarkerColor(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetLineWidth(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetLineColor(0);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetLineStyle(1);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->SetMarkerStyle(34);
   AlphaSLMScanOriginPoint[make_tuple(iter->first)]->RemovePoint(0);

   AlphaSLMScanOriginFitting[make_tuple(iter->first)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   AlphaSLMScanOriginResult[make_tuple(iter->first)]->Fit(AlphaSLMScanOriginFitting[make_tuple(iter->first)], "W");

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   HistName.ReplaceAll("AlphaSLMScanOriginResult", "AlphaSLMScanResult");
   FittingName.ReplaceAll("AlphaSLMScanOriginFitting", "AlphaSLMScanFitting");
   PointName.ReplaceAll("AlphaSLMScanOriginPoint", "AlphaSLMScanPoint");

   AlphaSLMScanResult[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetName(HistName);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetTitle(HistName);

   AlphaSLMScanPoint[make_tuple(iter->first)] = new TGraph(nScanPoint);
   AlphaSLMScanPoint[make_tuple(iter->first)]->SetName(PointName);
   AlphaSLMScanPoint[make_tuple(iter->first)]->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = AlphaSLMScanOriginFitting[make_tuple(iter->first)]->Eval(BestFitSolution);

     AlphaSLMScanResult[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanResult[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     AlphaSLMScanPoint[make_tuple(iter->first)]->SetPointX(ibin, BestFitSet.at(ibin - 1));
     AlphaSLMScanPoint[make_tuple(iter->first)]->SetPointY(ibin, Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2);
     cout<<"ScanResult for Data "<<iter->first<<" BestFit = "<<BestFitSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map[iter->first].at(ibin - 1) - DataOriginChi2<<endl;
   }
   AlphaSLMScanResult[make_tuple(iter->first)]->RemovePoint(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetMarkerSize(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetMarkerColor(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetLineWidth(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetLineColor(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetLineStyle(1);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetMarkerStyle(34);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetFillStyle(0);
   AlphaSLMScanResult[make_tuple(iter->first)]->SetFillColor(0);

   AlphaSLMScanPoint[make_tuple(iter->first)]->RemovePoint(0);

   AlphaSLMScanFitting[make_tuple(iter->first)] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") AlphaSLMScanFitting[make_tuple(iter->first)]->SetNpx(1000);
   AlphaSLMScanResult[make_tuple(iter->first)]->Fit(AlphaSLMScanFitting[make_tuple(iter->first)], "W");
   AlphaSLMScanFitting[make_tuple(iter->first)]->SetFillStyle(0);

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


   double par[3];
   AlphaSLMScanFitting[make_tuple(iter->first)]->GetParameters(par);

   double Central = -par[1] / (2 * par[0]);
   double MinChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);
   double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
   double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - LMScan->Tsq))) / (2 * par[0]);
   double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * LMScan->Tsq - 30.0))) / (2 * par[0]);
   double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - 2.0 * LMScan->Tsq - 30.0))) / (2 * par[0]);

   cout<<"T2 = "<<LMScan->Tsq<<endl;
   cout<<"MinChi2 for Data "<<iter->first<<" = "<<MinChi2<<" Central = "<<Central<<" Solution1 = "<<Solution1<<" Solution2 = "<<Solution2<<" Delta = "<<(Solution2 - Solution1) / 2.0<<endl;
   cout<<"Solution3 = "<<Solution3<<"  Solution4 = "<<Solution4<<"  xmin = "<<xmin<<"  xmax = "<<xmax<<endl;

   if(iter->first == "Total"){
     PlotXMin = Solution1;
     PlotXMax = Solution2;
     //AlphaSLMScanPlotXMin = Solution3;
     //AlphaSLMScanPlotXMax = Solution4;
     AlphaSLMScanPlotXMin = Solution3 < xmin ? xmin : Solution3;
     AlphaSLMScanPlotXMax = Solution4 > xmax ? xmax : Solution4;
   }

   if(iter->first != "Total") LMErrors[(Solution2 - Solution1) / 2.0] = iter->first;
   if(iter->first != "Total") ChiSquare1[iter->first] = AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMin);
   if(iter->first != "Total") ChiSquare2[iter->first] = AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMax);
   if(iter->first != "Total") ChiSquare1Map[AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMin)] = iter->first;
   if(iter->first != "Total") ChiSquare2Map[AlphaSLMScanFitting[make_tuple(iter->first)]->Eval(PlotXMax)] = iter->first;

   if(isLinkFile){
     AlphaSLMScanOriginResult[make_tuple(iter->first)]->Write();
     AlphaSLMScanOriginFitting[make_tuple(iter->first)]->Write();
     AlphaSLMScanOriginPoint[make_tuple(iter->first)]->Write();

     AlphaSLMScanResult[make_tuple(iter->first)]->Write();
     AlphaSLMScanFitting[make_tuple(iter->first)]->Write();
     AlphaSLMScanPoint[make_tuple(iter->first)]->Write();
   }
 }

 ////////////////
 //  Plotting  //
 ////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TString FigureName = (TString)"AlphaSLMScan.pdf";
 TString XaxisName = "#alpha_{s}(M_{Z})";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, AlphaSLMScanFitting[make_tuple((TString)"Total")], "Total");
 int iplot = 2;

 if(LMScanDrawList.size() == 0){
   for(auto iter = LMErrors.begin(); iter != LMErrors.end(); iter++){
     if(iplot >= 15) break;
     f->InputTF1(iplot, AlphaSLMScanFitting[make_tuple(iter->second)], DataLegend[NickNameMap[iter->second]]);
     iplot++;
   }
 }
 else{
   for(int i = 0; i < LMScanDrawList.size(); i++){
     f->InputTF1(i + 2, AlphaSLMScanFitting[make_tuple(LMScanDrawList.at(i))], DataLegend[NickNameMap[LMScanDrawList.at(i)]]);
   }
 }


 //f->InputTF1(iplot, AlphaSLMScanFitting[make_tuple("tabsCT18Am253/ZpT_as0118")], DataLegend[NickNameMap["tabsCT18Am253/ZpT_as0118"]]);

 double LegendYMin = 0.4; 
 if(LMScanDrawList.size() >= 13) LegendYMin = 0.4 - (LMScanDrawList.size() - 13) * 0.05;

 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, LegendYMin, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(AlphaSLMScanPlotXMin, AlphaSLMScanPlotXMax);
 f->SetCustomYRange(1, -20, 100);
 f->SetCustomXTitleOffset(1, 1.0);

 if(LMScanDrawList.size() == 0){
   for(int i = 2; i <= 16; i++){
     f->SetCustomLineStyle(1, i, PlotLineStyle[i]);
   }
 }
 else{
   for(int i = 1; i <= LMScanDrawList.size(); i++){
     f->SetCustomLineStyle(1, i + 1, PlotLineStyle[i + 1]);
   }
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

 iplot = 2;
 for(auto iter = ChiSquare2Map.begin(); iter != ChiSquare2Map.end(); iter++){
   //if(iplot >= 9) break;
   cout<<fixed<<setprecision(3)<<iter->second<<": "<<iter->first<<" Chi2 = "<<ChiSquare1[iter->second]<<" "<<ChiSquare2[iter->second]<<endl;
   iplot++;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 LMErrors.clear();
 Chi2Map.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////
// Plotting //
//////////////

void ePumpHelper::PDFLMScanPlotting(int flavor, double x, double Q, TString subName, vector<TString> DataList, int isNewPDF)
{
 stringstream s_Qstring;
 TString Qstring;
 s_Qstring<<fixed<<setprecision(2)<<Q;
 Qstring = s_Qstring.str();

 stringstream s_xstring;
 stringstream s_xstring_fixed;
 TString xstring;
 TString xstring_fixed;
 s_xstring<<scientific<<setprecision(2)<<x;
 xstring = s_xstring.str();
 s_xstring_fixed<<fixed<<setprecision(2)<<x;
 xstring_fixed = s_xstring_fixed.str();


 TString FigureName = (TString)"PDFLMScan_" + FlavorNameMap[flavor] + "_x" + xstring + "_Q" + Qstring + subName + ".pdf";
 TString XaxisName = TitleMap[flavor] + "(x = " + xstring_fixed + ", Q = " + Qstring + " GeV)";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, PDFLMScanFitting[make_tuple((TString)"Total", flavor, x, Q, isNewPDF)], "Total");
 int iplot = 2;
 for(int i = 0; i < DataList.size(); i++){
   cout<<"Adding data "<<DataList.at(i)<<" "<<FullNameMap[DataList.at(i)]<<"..."<<endl;
   f->InputTF1(iplot, PDFLMScanFitting[make_tuple(FullNameMap[DataList.at(i)], flavor, x, Q, isNewPDF)], DataLegend[DataList.at(i)]);
   iplot++;
 }
 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, 0.4, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(PDFLMScanPlotXMin[make_tuple(flavor, x, Q, isNewPDF)], PDFLMScanPlotXMax[make_tuple(flavor, x, Q, isNewPDF)]);
 f->SetCustomYRange(1, -20, 100);
 f->SetCustomXTitleOffset(1, 1.0);

 for(int i = 0; i < DataList.size(); i++){
   f->SetCustomLineStyle(1, i + 2, PlotLineStyle[i + 2]);
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

}

void ePumpHelper::AlphaSLMScanPlotting(double Q, TString subName, vector<TString> DataList)
{
 stringstream s_Qstring;
 TString Qstring;
 s_Qstring<<fixed<<setprecision(2)<<Q;
 Qstring = s_Qstring.str();

 TString FigureName = (TString)"AlphaSLMScan" + subName + ".pdf";
 TString XaxisName = "#alpha_{s}(M_{Z})";
 TString YaxisName = "#Delta #chi^{2}";

 Figure* f;

 f = new Figure(FigureName, XaxisName, YaxisName);
 f->SetMode("CUSTOM");
 f->InputTF1(1, AlphaSLMScanFitting[make_tuple((TString)"Total")], "Total");
 int iplot = 2;
 for(int i = 0; i < DataList.size(); i++){
   cout<<"Adding data "<<DataList.at(i)<<" "<<FullNameMap[DataList.at(i)]<<"..."<<endl;
   f->InputTF1(iplot, AlphaSLMScanFitting[make_tuple(FullNameMap[DataList.at(i)])], DataLegend[DataList.at(i)]);
   iplot++;
 }
 f->Compare("MultiSimple");
 f->SetCustomPlotFormat(1, 1, kBlack);
 f->SetCanvasSize(1400.0, 1200.0);
 f->SetLegendPosition(1.0, 0.4, 1.2, 0.9);
 f->SetCustomLegendSize(1, 0.025);
 f->SetCustomRightMargin(1, 0.2);
 f->SetCustomLeftMargin(1, 0.15);
 f->SetXRange(AlphaSLMScanPlotXMin, AlphaSLMScanPlotXMax);
 f->SetCustomYRange(1, -20, 100);
 f->SetCustomXTitleOffset(1, 1.0);

 for(int i = 0; i < DataList.size(); i++){
   f->SetCustomLineStyle(1, i + 2, PlotLineStyle[i + 2]);
 }

 f->SetCustomLineWidth(1, 1, 6);

 f->Draw();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ePumpHelper::LMScanModule(TString DataName, int ipoint, int isNewPDF, TString TitleName)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 LMScan = Clone(EU, EU->mainfile);
 AddLMScanConstrain(LMScan);
 AddLMData(DataName, ipoint);
 ScanLambda(DataName, ipoint, isNewPDF, TitleName);
 delete LMScan;
}

void ePumpHelper::PDFLMScanModule(int flavor, double x, double Q, int isNewPDF)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 LMScan = Clone(EU, EU->mainfile, isNewPDF);
 AddLMScanConstrain(LMScan);
 AddLMPDF(flavor, x, Q, isNewPDF);
 ScanLambdaPDF(flavor, x, Q, isNewPDF);
 delete LMScan;
}

void ePumpHelper::AlphaSLMScanModule(double Q)
{
 if(isTurnOffUpdatePDF){
   cout<<"ERROR! PDFs are not initialized!"<<endl;
   return;
 }

 LMScan = Clone(EU, EU->mainfile);
 AddLMScanConstrain(LMScan);
 AddLMAlphaS(Q);
 ScanLambdaAlphaS(Q);
 delete LMScan;
}

