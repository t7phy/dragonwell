#include "ePumpHelper/ePumpHelper.h"

ePumpHelper::ePumpHelper(const char* filename)
{
 DefineCombination();

 FileName = (TString)filename;

 EU = new ePump(filename, 1.0);

 SaveHist();
 //Initial();
}

void ePumpHelper::Initial()
{
 isUpdate = true;
 isOptimize = false;

 EU->ReadInTheoryAndData();
 if(EU->pdftype == PDF_format_type::NONE) isTurnOffUpdatePDF = true;

 for(int i = 0; i < EU->dataset.size(); i++){
   AllDataNames.push_back((TString)(EU->dataset.at(i).c_str()));

   DataIndex[(TString)(EU->dataset.at(i).c_str())] = i;
   DataErrorType[(TString)(EU->dataset.at(i).c_str())] = EU->error_type_all.at(i);
   DataWeight[(TString)(EU->dataset.at(i).c_str())] = EU->weight_all.at(i);
   DataIncluded[(TString)(EU->dataset.at(i).c_str())] = EU->dataIncluded.at(i);
   DataNPoints[(TString)(EU->dataset.at(i).c_str())] = EU->Na.at(i);

   DataPoint[(TString)(EU->dataset.at(i).c_str())] = EU->XE.at(i);
   DataTotalErr[(TString)(EU->dataset.at(i).c_str())] = EU->s.at(i);

   TheoryTemplate[(TString)(EU->dataset.at(i).c_str())] = EU->Xmat.at(i);
   NEV = EU->Ni;
 }

 DefineDataLegend();
 NameTransfer();

 //TurnOffUpdatePDF();
}

void ePumpHelper::Update()
{
 isUpdate = true;
 isOptimize = false;

 cout<<"Start updating PDF:"<<endl;

 EU->ConstructUpdateMatrix();
 EU->UpdateObservables();

 for(int i = 0; i < EU->dataset.size(); i++){
   OldTheory[(TString)(EU->dataset.at(i).c_str())] = EU->X0.at(i);
   NewTheory[(TString)(EU->dataset.at(i).c_str())] = EU->NewTheory.at(i);
   OldPDFError[(TString)(EU->dataset.at(i).c_str())] = EU->OldPDFError.at(i);
   NewPDFError[(TString)(EU->dataset.at(i).c_str())] = EU->NewPDFError.at(i);
   OldChi2[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2.at(i);
   NewChi2[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2new.at(i);
   OldSpartyness[(TString)(EU->dataset.at(i).c_str())] = EU->spartynessSave.at(i);
   NewSpartyness[(TString)(EU->dataset.at(i).c_str())] = EU->spartynessNewSave.at(i);

   //OldChi2Set[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2Set.at(i);
   NewChi2Set[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2newSet.at(i);

   NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())] = EU->XmatNew.at(i);

   for(int j = 0; j < EU->dataset.size(); j++){
     if(doCorrelationCosine) OldPDFCorrelation[(vector<TString>{(TString)(EU->dataset.at(i).c_str()), (TString)(EU->dataset.at(j).c_str())})] = EU->OldPDFCorrelation.at(i).at(j);
     if(doCorrelationCosine) NewPDFCorrelation[(vector<TString>{(TString)(EU->dataset.at(i).c_str()), (TString)(EU->dataset.at(j).c_str())})] = EU->NewPDFCorrelation.at(i).at(j);
   }

 }

 if(DoSaveHist){
   EU->SaveHists();
 }

 //CalNewPDFUnc();
 //CalNewPDFCorr();

 GetUpdateParameter();
 ReadParameterList();
 if(isUpdateExtendPara){
   //ConstructUpdateMatrixExtended();
   //UpdateObservablesExtended();
 }

 if(!isTurnOffUpdatePDF) InitialUpdatedPDF();
}

void ePumpHelper::InitialOptimize()
{
 isOptimize = true;
 isUpdate = false;

 EU->ReadInTheory_Optimize();

 for(int i = 0; i < EU->dataset.size(); i++){
   AllDataNames.push_back((TString)(EU->dataset.at(i).c_str()));

   DataIndex[(TString)(EU->dataset.at(i).c_str())] = i;
   DataNPoints[(TString)(EU->dataset.at(i).c_str())] = EU->Na.at(i);

   TheoryTemplate[(TString)(EU->dataset.at(i).c_str())] = EU->Xmat.at(i);
   NEV = EU->Ni;
 }

}

void ePumpHelper::Optimize()
{
 isOptimize = true;
 isUpdate = false;

 EU->ConstructOptimizeMatrix();
 EU->OptimizeObservables();

 for(int i = 0; i < EU->dataset.size(); i++){
   OptimizeTheoryTemplate[(TString)(EU->dataset.at(i).c_str())] = EU->XmatNew.at(i);
   FractionalContribution[(TString)(EU->dataset.at(i).c_str())] = EU->FractionalContribution.at(i);
 } 

 for(int i = 0; i < EU->dataset.size(); i++){
   vector<TH1D *> FractionHist(NEV);

   for(int iEV = 0; iEV < NEV; iEV++){
     TString HistName = AllDataNames.at(i);
     HistName.ReplaceAll("/", "_");
     HistName.ReplaceAll(".", "_");
     HistName = HistName + "_FractionalContribution_EV" + (int)(iEV + 1);
     FractionHist.at(iEV) = new TH1D(HistName, HistName, DataNPoints[(TString)(EU->dataset.at(i).c_str())], 0, DataNPoints[(TString)(EU->dataset.at(i).c_str())]);

     for(int ipoint = 0; ipoint < DataNPoints[(TString)(EU->dataset.at(i).c_str())]; ipoint++){
       FractionHist.at(iEV)->SetBinContent(ipoint + 1, FractionalContribution[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(iEV));
       FractionHist.at(iEV)->SetBinError(ipoint + 1, 0.0);
     }
   }
   FractionalContributionHist[(TString)(EU->dataset.at(i).c_str())] = FractionHist;
 }

 if(!isTurnOffUpdatePDF) InitialUpdatedPDF();
}

void ePumpHelper::InitialUpdatedPDF()
{
 if(EU->pdftype != PDF_format_type::CTEQ) return;

 PDFSample = new pdsReader();
 PDFSample->Initialize((TString)EU->PDFinfile + (TString)".00.pds");

 OldPDFSet.resize(2 * NEV + 1);
 NewPDFSet.resize(2 * NEV + 1);

 for(int i = 0; i < 2 * NEV + 1; i++){
   OldPDFSet.at(i) = new pdsReader();
   OldPDFSet.at(i)->CopyHeader(PDFSample);
   OldPDFSet.at(i)->InputAlphaS(EU->OldPDFAlphaS.at(i));
   OldPDFSet.at(i)->InputUPD(EU->OldPDF.at(i));
   NewPDFSet.at(i) = new pdsReader();
   NewPDFSet.at(i)->CopyHeader(PDFSample);
   NewPDFSet.at(i)->InputAlphaS(EU->OldPDFAlphaS.at(i));
   NewPDFSet.at(i)->InputUPD(EU->NewPDF.at(i));
 }

 OldEVSet = new EVsets();
 OldEVSet->InitializePDF(OldPDFSet);

 NewEVSet = new EVsets();
 NewEVSet->InitializePDF(NewPDFSet);

}

void ePumpHelper::CalcL2Sensitivity(int flavor, double x, double Q)
{
 if(isTurnOffUpdatePDF) return;
 if(EU->pdftype != PDF_format_type::CTEQ) return;

 map<TString, double> L2SensitivityResult;
 map<double, TString> L2Inverse;

 if(!isPrepareOldChi2){
   EU->PrepareOldChi2();
   for(int i = 0; i < EU->dataset.size(); i++){
     OldChi2Set[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2Set.at(i);
   }
   isPrepareOldChi2 = true;
 }

 for(auto iter = OldChi2Set.begin(); iter != OldChi2Set.end(); iter++){
   TString DataName = iter->first;
   double L2 = OldEVSet->CalcL2Sensitivity(OldChi2Set[DataName], DataNPoints[DataName], flavor, x, Q);
   L2SensitivityResult[DataName] = L2;
   L2Inverse[1.0 - L2] = DataName;
 }

 cout<<"L2 Sensitivity:"<<endl;
 int iplot = 1;
 for(auto iter = L2Inverse.begin(); iter != L2Inverse.end(); iter++){
   //if(iplot >= 8) break;
   cout<<fixed<<setprecision(3)<<iter->second<<": "<<L2SensitivityResult[iter->second]<<endl;
   iplot++;
 }

 stringstream s_Qstring;
 TString Qstring;
 s_Qstring<<fixed<<setprecision(2)<<Q;
 Qstring = s_Qstring.str();

 TString FigureName = (TString)"L2Sensitivity_" + FlavorNameMap[flavor] + "_Q" + Qstring + "_Top15.pdf";
 TString YAxisName = "L_{2} Sensitivity";
 if(isDrawAbsoluteL2) YAxisName = "|L_{2} Sensitivity|";

 Graph* g;
 g = new Graph(FigureName, "x", YAxisName);
 g->SetMode("CUSTOM");

 if(L2SensitivityDrawList.size() == 0){
   iplot = 1;
   for(auto iter = L2Inverse.begin(); iter != L2Inverse.end(); iter++){
     if(iplot >= 16) break;

     if(!isDrawUpdatedL2) g->Input(iplot, OldL2Sensitivity[make_tuple(iter->second, flavor, Q)], DataLegend[NickNameMap[iter->second]]);
     else g->Input(iplot, NewL2Sensitivity[make_tuple(iter->second, flavor, Q)], DataLegend[NickNameMap[iter->second]]);

     iplot++;
   }
 }
 else{
   for(int i = 0; i < L2SensitivityDrawList.size(); i++){
     if(!isDrawUpdatedL2) g->Input(i + 1, OldL2Sensitivity[make_tuple(L2SensitivityDrawList.at(i), flavor, Q)], DataLegend[NickNameMap[L2SensitivityDrawList.at(i)]]);
     else g->Input(i + 1, NewL2Sensitivity[make_tuple(L2SensitivityDrawList.at(i), flavor, Q)], DataLegend[NickNameMap[L2SensitivityDrawList.at(i)]]);
   }
 }

 double LegendYMin = 0.4;
 if(L2SensitivityDrawList.size() >= 13) LegendYMin = 0.4 - (L2SensitivityDrawList.size() - 13) * 0.05;

 g->Compare("MultiSimple");
 g->SetLogX();

 bool InsideLegend = false;

 if(!InsideLegend){
   g->SetCanvasSize(1400.0, 800.0);
   g->SetLegendPosition(1.0, LegendYMin, 1.3, 0.95);
   g->SetCustomLegendSize(1, 0.04);
   g->SetCustomRightMargin(1, 0.25);
   g->SetCustomLeftMargin(1, 0.1);
   g->SetCustomYTitleOffset(1, 1.0);
   g->SetXRange(1e-5, 0.85);
   g->SetCustomXLabelSize(1, 0.04);
   g->AddText(1, TitleMap[flavor] + " at Q = " + TString::Format("%.1f", Q) + " GeV");
   g->SetTextLeftBias(0.7);
   g->SetCustomTextSize(1, 0.04);
 }
 else{
   g->SetCanvasSize(1400.0, 800.0);
   g->SetLegendPosition(0.03, 0.73, 0.9, 0.95);
   g->SetTextLeftBias(-0.07);
   g->SetCustomLegendSize(1, 0.05);
   g->SetCustomRightMargin(1, 0.1);
   g->SetCustomLeftMargin(1, 0.1);
   g->SetCustomYTitleOffset(1, 1.0);
   g->SetXRange(1e-5, 0.85);
   g->SetCustomXLabelSize(1, 0.04);
   g->AddText(1, TitleMap[flavor] + " at Q = " + TString::Format("%.1f", Q) + " GeV");
   g->SetCustomTextSize(1, 0.06);
   g->SetLegendNColumns(2);
   g->SetLogY();
 }

 if(L2SensitivityDrawList.size() == 0){
   for(int i = 1; i <= 15; i++){
     g->SetCustomLineStyle(1, i, PlotLineStyle[i + 1]);
   }
 }
 else{
   for(int i = 1; i <= L2SensitivityDrawList.size(); i++){
     g->SetCustomLineStyle(1, i, PlotLineStyle[i + 1]);
   }
 }

 g->Draw();

 isDrawUpdatedL2 = false;
}

void ePumpHelper::DrawL2Sensitivity(TString DataName, int flavor, double Q)
{
 // New L2 sensitivity is not correct
 // The beta is not updated in the calculation of new Chi2

 if(isTurnOffUpdatePDF) return;
 if(EU->pdftype != PDF_format_type::CTEQ) return;

 if(!isPrepareOldChi2){
   EU->PrepareOldChi2();
   for(int i = 0; i < EU->dataset.size(); i++){
     OldChi2Set[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2Set.at(i);
   }
   isPrepareOldChi2 = true;
 } 

 TString HistName = DataName;
 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");

 TString OldHistName = HistName + "_" + FlavorNameMap[flavor] + "_" + TString::Format("%.2f", Q) + "_Old";
 TString NewHistName = HistName + "_" + FlavorNameMap[flavor] + "_" + TString::Format("%.2f", Q) + "_New";

 OldHistName.ReplaceAll(".", "_");
 NewHistName.ReplaceAll(".", "_");

 if(isDrawAbsoluteL2){
   OldEVSet->DrawAbsoluteL2();//yfu
   NewEVSet->DrawAbsoluteL2();
 }

 OldL2Sensitivity[make_tuple(DataName, flavor, Q)] = OldEVSet->DrawL2Sensitivity(OldChi2Set[DataName], DataNPoints[DataName], OldHistName, flavor, Q);
 NewL2Sensitivity[make_tuple(DataName, flavor, Q)] = NewEVSet->DrawL2Sensitivity(NewChi2Set[DataName], DataNPoints[DataName], NewHistName, flavor, Q);

 if(isLinkFile){
   hf->cd();
   OldL2Sensitivity[make_tuple(DataName, flavor, Q)]->Write();
   NewL2Sensitivity[make_tuple(DataName, flavor, Q)]->Write();
 }
}

void ePumpHelper::DrawL2SensitivityAll(int flavor, double Q)
{
 if(isLinkFile) hf->cd();

 if(!isPrepareOldChi2){
   EU->PrepareOldChi2();
   for(int i = 0; i < EU->dataset.size(); i++){
     OldChi2Set[(TString)(EU->dataset.at(i).c_str())] = EU->dChi2Set.at(i);
   }
   isPrepareOldChi2 = true;
 }

 for(auto iter = OldChi2Set.begin(); iter != OldChi2Set.end(); iter++){
   DrawL2Sensitivity(iter->first, flavor, Q);
 }
}

void ePumpHelper::CalNewPDFUnc()
{
 for(int i = 0; i < EU->dataset.size(); i++){
   vector<double> PDFUnc(DataNPoints[(TString)(EU->dataset.at(i).c_str())]);
   for(int ipoint = 0; ipoint < DataNPoints[(TString)(EU->dataset.at(i).c_str())]; ipoint++){
     double Unc = 0.0;
     double Unc2 = 0.0;
     for(int iEV = 0; iEV < NEV; iEV++){
       Unc2 += pow(NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 2), 2);
     }
     Unc = sqrt(Unc2) / 2.0;
     PDFUnc.at(ipoint) = Unc;
   }
   NewPDFErrorTmp[(TString)(EU->dataset.at(i).c_str())] = PDFUnc;
 }
}

void ePumpHelper::CalNewPDFCorr()
{
 for(int i = 0; i < EU->dataset.size(); i++){
   for(int j = 0; j < EU->dataset.size(); j++){
     vector<vector<double>> NewCorr(DataNPoints[(TString)(EU->dataset.at(i).c_str())]);

     for(int ipoint = 0; ipoint < DataNPoints[(TString)(EU->dataset.at(i).c_str())]; ipoint++){
       NewCorr.at(ipoint).resize(DataNPoints[(TString)(EU->dataset.at(j).c_str())]);

       for(int jpoint = 0; jpoint < DataNPoints[(TString)(EU->dataset.at(j).c_str())]; jpoint++){

         double Corr = 0.0;

         double Numer = 0.0;
         double Denom = 0.0;
         double DeltaX = 0.0;
         double DeltaY = 0.0;
         double DeltaX2 = 0.0;
         double DeltaY2 = 0.0;
         for(int iEV = 0; iEV < NEV; iEV++){
           Numer += (NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 2))
                  * (NewTheoryTemplate[(TString)(EU->dataset.at(j).c_str())].at(jpoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(j).c_str())].at(jpoint).at(2 * iEV + 2)) / 4.0;
           DeltaX2 += (NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 2))
                    * (NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(i).c_str())].at(ipoint).at(2 * iEV + 2)) / 4.0;
           DeltaY2 += (NewTheoryTemplate[(TString)(EU->dataset.at(j).c_str())].at(jpoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(j).c_str())].at(jpoint).at(2 * iEV + 2))
                    * (NewTheoryTemplate[(TString)(EU->dataset.at(j).c_str())].at(jpoint).at(2 * iEV + 1) - NewTheoryTemplate[(TString)(EU->dataset.at(j).c_str())].at(jpoint).at(2 * iEV + 2)) / 4.0;
         }//end iEV
         DeltaX = sqrt(DeltaX2);
         DeltaY = sqrt(DeltaY2);
         Denom = DeltaX * DeltaY;

         Corr = Numer / Denom;
         NewCorr.at(ipoint).at(jpoint) = Corr;
       }// end j point
     }// end i point
     NewPDFCorrelationTmp[(vector<TString>{(TString)(EU->dataset.at(i).c_str()), (TString)(EU->dataset.at(j).c_str())})] = NewCorr;
   }// end j data
 }// end i data

}

void ePumpHelper::ProcessWeightFunction(vector<TString> DataNames)
{
 vector<double> Weights = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 15.0, 20.0, 30.0, 40.0, 50.0};
// vector<double> Weights = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

 for(int idata = 0; idata < AllDataNames.size(); idata++){
   NewTheoryWeightFunction[AllDataNames.at(idata)].resize(NewTheory[AllDataNames.at(idata)].size());
   NewPDFErrorWeightFunction[AllDataNames.at(idata)].resize(NewPDFError[AllDataNames.at(idata)].size());
   NewTheoryWeightHist[AllDataNames.at(idata)].resize(NewTheory[AllDataNames.at(idata)].size());
   NewPDFErrorWeightHist[AllDataNames.at(idata)].resize(NewPDFError[AllDataNames.at(idata)].size());

   for(int ipoint = 0; ipoint < NewTheory[AllDataNames.at(idata)].size(); ipoint++){
     NewTheoryWeightFunction[AllDataNames.at(idata)].at(ipoint).resize(Weights.size());
     NewPDFErrorWeightFunction[AllDataNames.at(idata)].at(ipoint).resize(Weights.size());

     TString HistName = AllDataNames.at(idata);
     HistName.ReplaceAll("/", "_");
     HistName.ReplaceAll(".", "_");
     HistName = HistName + "_NewTheoryWeightFunction_bin" + (int)(ipoint + 1);
     NewTheoryWeightHist[AllDataNames.at(idata)].at(ipoint) = new TH1D(HistName, HistName, Weights.size() - 1, &Weights[0]);

     HistName = AllDataNames.at(idata);
     HistName.ReplaceAll("/", "_");
     HistName.ReplaceAll(".", "_");
     HistName = HistName + "_NewPDFErrorWeightFunction_bin" + (int)(ipoint + 1);
     NewPDFErrorWeightHist[AllDataNames.at(idata)].at(ipoint) = new TH1D(HistName, HistName, Weights.size() - 1, &Weights[0]);
   }

   NewChi2WeightFunction[AllDataNames.at(idata)].resize(Weights.size());
   NewChi2NptWeightFunction[AllDataNames.at(idata)].resize(Weights.size());
   NewSpartynessWeightFunction[AllDataNames.at(idata)].resize(Weights.size());

   TString HistName = AllDataNames.at(idata);
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName = HistName + "_NewChi2WeightFunction";
   NewChi2WeightHist[AllDataNames.at(idata)] = new TH1D(HistName, HistName, Weights.size() - 1, &Weights[0]);

   HistName = AllDataNames.at(idata);
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName = HistName + "_NewChi2NptWeightFunction";
   NewChi2NptWeightHist[AllDataNames.at(idata)] = new TH1D(HistName, HistName, Weights.size() - 1, &Weights[0]);

   HistName = AllDataNames.at(idata);
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName = HistName + "_NewSpartynessWeightFunction";
   NewSpartynessWeightHist[AllDataNames.at(idata)] = new TH1D(HistName, HistName, Weights.size() - 1, &Weights[0]);

 }

 for(int i = 0; i < Weights.size(); i++){
   ResetUpdate();
   for(int idata = 0; idata < DataNames.size(); idata++){
     SetDataWeight(DataNames.at(idata), Weights.at(i));
   }
   TurnOffCorrelationCosine();
   Update();

   for(int idata = 0; idata < AllDataNames.size(); idata++){
     for(int ipoint = 0; ipoint < NewTheory[AllDataNames.at(idata)].size(); ipoint++){
       NewTheoryWeightFunction[AllDataNames.at(idata)].at(ipoint).at(i) = NewTheory[AllDataNames.at(idata)].at(ipoint);
       NewPDFErrorWeightFunction[AllDataNames.at(idata)].at(ipoint).at(i) = NewPDFError[AllDataNames.at(idata)].at(ipoint);

       NewTheoryWeightHist[AllDataNames.at(idata)].at(ipoint)->SetBinContent(i + 1, NewTheory[AllDataNames.at(idata)].at(ipoint));
       NewTheoryWeightHist[AllDataNames.at(idata)].at(ipoint)->SetBinError(i + 1, 0.0);
       NewPDFErrorWeightHist[AllDataNames.at(idata)].at(ipoint)->SetBinContent(i + 1, NewPDFError[AllDataNames.at(idata)].at(ipoint));
       NewPDFErrorWeightHist[AllDataNames.at(idata)].at(ipoint)->SetBinError(i + 1, 0.0);
     }

     NewChi2WeightFunction[AllDataNames.at(idata)].at(i) = NewChi2[AllDataNames.at(idata)];
     NewChi2NptWeightFunction[AllDataNames.at(idata)].at(i) = NewChi2[AllDataNames.at(idata)] / (double) NewTheory[AllDataNames.at(idata)].size();
     NewSpartynessWeightFunction[AllDataNames.at(idata)].at(i) = NewSpartyness[AllDataNames.at(idata)];

     NewChi2WeightHist[AllDataNames.at(idata)]->SetBinContent(i + 1, NewChi2[AllDataNames.at(idata)]);
     NewChi2WeightHist[AllDataNames.at(idata)]->SetBinError(i + 1, 0.0);

     NewChi2NptWeightHist[AllDataNames.at(idata)]->SetBinContent(i + 1, NewChi2[AllDataNames.at(idata)] / (double) NewTheory[AllDataNames.at(idata)].size());
     NewChi2NptWeightHist[AllDataNames.at(idata)]->SetBinError(i + 1, 0.0);

     NewSpartynessWeightHist[AllDataNames.at(idata)]->SetBinContent(i + 1, NewSpartyness[AllDataNames.at(idata)]);
     NewSpartynessWeightHist[AllDataNames.at(idata)]->SetBinError(i + 1, 0.0);
   }
 }

 if(isLinkFile){
   hf->cd();
   for(int idata = 0; idata < AllDataNames.size(); idata++){
     for(int ipoint = 0; ipoint < NewTheory[AllDataNames.at(idata)].size(); ipoint++){
       NewTheoryWeightHist[AllDataNames.at(idata)].at(ipoint)->Write();
       NewPDFErrorWeightHist[AllDataNames.at(idata)].at(ipoint)->Write();
     }
     NewChi2WeightHist[AllDataNames.at(idata)]->Write();
     NewChi2NptWeightHist[AllDataNames.at(idata)]->Write();
     NewSpartynessWeightHist[AllDataNames.at(idata)]->Write();
   }
 }

}

////////////////////////////////////////////////////////////////////////

void ePumpHelper::OutputResult(TString DataName)
{
 for(int i = 0; i < OldTheory[DataName].size(); i++){
   cout<<fixed<<setprecision(5)<<OldTheory[DataName].at(i)<<"  "<<OldPDFError[DataName].at(i)<<endl;
   cout<<fixed<<setprecision(5)<<NewTheory[DataName].at(i)<<"  "<<NewPDFError[DataName].at(i)<<endl;
   cout<<endl;
 }
}

void ePumpHelper::OutputCorrelation(TString Data1, TString Data2)
{
 cout<<"Old/New Correlation between "<<Data1<<" and "<<Data2<<endl;
 for(int i = 0; i < OldTheory[Data1].size(); i++){
   for(int j = 0; j < OldTheory[Data2].size(); j++){
     cout<<fixed<<setprecision(3)<<GetOldPDFCorrelation(Data1, Data2, i, j)<<"/"<<GetNewPDFCorrelation(Data1, Data2, i, j)<<"  ";
   }
   cout<<endl;
 }
}

//////////////////////////////////////////////////////////////////////////

void ePumpHelper::ConstructDataHist(TString DataName, TH1D* &Data)
{
 if(isLinkFile) hf->cd();

 TString HistName = DataName;
 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");
 HistName = HistName + "_Data";

 Data = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Data->GetNbinsX(); ibin++){
   Data->SetBinContent(ibin, DataPoint[DataName].at(ibin - 1));
   Data->SetBinError(ibin, DataTotalErr[DataName].at(ibin - 1));
 }
}

TH1D* ePumpHelper::ConstructDataHist(TString DataName)
{
 TString HistName = DataName;
 HistName.ReplaceAll("/", "_");
 HistName.ReplaceAll(".", "_");
 HistName = HistName + "_Data";

 TH1D* Data = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Data->GetNbinsX(); ibin++){
   Data->SetBinContent(ibin, DataPoint[DataName].at(ibin - 1));
   Data->SetBinError(ibin, DataTotalErr[DataName].at(ibin - 1));
 }

 return Data;
}

void ePumpHelper::ConstructTheoryHist(TString DataName, vector<TH1D *> &Theory)
{
 if(isLinkFile) hf->cd();

 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");

 Theory.resize(2 * NEV + 1);

 for(int iPDF = 0; iPDF < Theory.size(); iPDF++){
   TString HistName = OriginHistName + (TString)"_Theory" + (int)iPDF;
   Theory.at(iPDF) = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

   for(int ibin = 1; ibin <= Theory.at(iPDF)->GetNbinsX(); ibin++){
     Theory.at(iPDF)->SetBinContent(ibin, GetTheoryTemplate(DataName, ibin - 1, iPDF));
     Theory.at(iPDF)->SetBinError(ibin, 0.0);
   }
 }

}

vector<TH1D *> ePumpHelper::ConstructTheoryHist(TString DataName)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");

 vector<TH1D *> Theory;
 Theory.resize(2 * NEV + 1);

 for(int iPDF = 0; iPDF < Theory.size(); iPDF++){
   TString HistName = OriginHistName + (TString)"_Theory" + (int)iPDF;
   Theory.at(iPDF) = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

   for(int ibin = 1; ibin <= Theory.at(iPDF)->GetNbinsX(); ibin++){
     Theory.at(iPDF)->SetBinContent(ibin, GetTheoryTemplate(DataName, ibin - 1, iPDF));
     Theory.at(iPDF)->SetBinError(ibin, 0.0);
   }
 }

 return Theory;
}

vector<TH1D *> ePumpHelper::ConstructNewTheoryHist(TString DataName)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");

 vector<TH1D *> Theory;
 Theory.resize(2 * NEV + 1);

 for(int iPDF = 0; iPDF < Theory.size(); iPDF++){
   TString HistName = OriginHistName + (TString)"_NewTheory" + (int)iPDF;
   Theory.at(iPDF) = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

   for(int ibin = 1; ibin <= Theory.at(iPDF)->GetNbinsX(); ibin++){
     Theory.at(iPDF)->SetBinContent(ibin, GetNewTheoryTemplate(DataName, ibin - 1, iPDF));
     Theory.at(iPDF)->SetBinError(ibin, 0.0);
   }
 }

 return Theory;
}

vector<TH1D *> ePumpHelper::ConstructOptimizeTheoryHist(TString DataName)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");

 vector<TH1D *> Theory;
 Theory.resize(2 * NEV + 1);

 for(int iPDF = 0; iPDF < Theory.size(); iPDF++){
   TString HistName = OriginHistName + (TString)"_OptimizedTheory" + (int)iPDF;
   Theory.at(iPDF) = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

   for(int ibin = 1; ibin <= Theory.at(iPDF)->GetNbinsX(); ibin++){
     Theory.at(iPDF)->SetBinContent(ibin, GetOptimizeTheoryTemplate(DataName, ibin - 1, iPDF));
     Theory.at(iPDF)->SetBinError(ibin, 0.0);
   }
 }

 return Theory;
}

void ePumpHelper::ConstructOldPDFErrorHist(TString DataName, TString subName, TH1D* &Hist, TString type)
{
 if(isLinkFile) hf->cd();

 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_OldPDFError" + subName;

 Hist = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Hist->GetNbinsX(); ibin++){
   double Value = OldPDFError[DataName].at(ibin - 1);
   if(type == "Relative") Value = OldPDFError[DataName].at(ibin - 1) / OldTheory[DataName].at(ibin - 1);
   Hist->SetBinContent(ibin, Value);
   Hist->SetBinError(ibin, 0.0);
 }
}

TH1D* ePumpHelper::ConstructOldPDFErrorHist(TString DataName, TString subName, TString type)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_OldPDFError" + subName;

 TH1D* Hist = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Hist->GetNbinsX(); ibin++){
   double Value = OldPDFError[DataName].at(ibin - 1);
   if(type == "Relative") Value = OldPDFError[DataName].at(ibin - 1) / OldTheory[DataName].at(ibin - 1);
   Hist->SetBinContent(ibin, Value);
   Hist->SetBinError(ibin, 0.0);
 }

 return Hist;
}

TH1D* ePumpHelper::ConstructOldPDFErrorHist(TString DataName, TString subName, TString type, int FirstBin, int LastBin)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_OldPDFError" + subName;

 TH1D* Hist = new TH1D(HistName, HistName, LastBin - FirstBin + 1, 0, LastBin - FirstBin + 1);

 for(int ibin = FirstBin; ibin <= LastBin; ibin++){
   double Value = OldPDFError[DataName].at(ibin - 1);
   if(type == "Relative") Value = OldPDFError[DataName].at(ibin - 1) / OldTheory[DataName].at(ibin - 1);
   Hist->SetBinContent(ibin - FirstBin + 1, Value);
   Hist->SetBinError(ibin - FirstBin + 1, 0.0);
 }

 return Hist;
}

void ePumpHelper::ConstructNewPDFErrorHist(TString DataName, TString subName, TH1D* &Hist, TString type)
{
 if(isLinkFile) hf->cd();

 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_NewPDFError" + subName;

 Hist = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Hist->GetNbinsX(); ibin++){
   double Value = NewPDFError[DataName].at(ibin - 1);
   if(type == "Relative") Value = NewPDFError[DataName].at(ibin - 1) / NewTheory[DataName].at(ibin - 1);
   Hist->SetBinContent(ibin, Value);
   Hist->SetBinError(ibin, 0.0);
 }
}

TH1D* ePumpHelper::ConstructNewPDFErrorHist(TString DataName, TString subName, TString type)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_NewPDFError" + subName;

 TH1D* Hist = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Hist->GetNbinsX(); ibin++){
   double Value = NewPDFError[DataName].at(ibin - 1);
   if(type == "Relative") Value = NewPDFError[DataName].at(ibin - 1) / NewTheory[DataName].at(ibin - 1);
   Hist->SetBinContent(ibin, Value);
   Hist->SetBinError(ibin, 0.0);
 }

 return Hist;
}

TH1D* ePumpHelper::ConstructNewPDFErrorHist(TString DataName, TString subName, TString type, int FirstBin, int LastBin)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_NewPDFError" + subName;
 
 TH1D* Hist = new TH1D(HistName, HistName, LastBin - FirstBin + 1, 0, LastBin - FirstBin + 1);
 
 for(int ibin = FirstBin; ibin <= LastBin; ibin++){
   double Value = NewPDFError[DataName].at(ibin - 1);
   if(type == "Relative") Value = NewPDFError[DataName].at(ibin - 1) / NewTheory[DataName].at(ibin - 1);
   Hist->SetBinContent(ibin - FirstBin + 1, Value);
   Hist->SetBinError(ibin - FirstBin + 1, 0.0);
 }
 
 return Hist;
}

TH1D* ePumpHelper::ConstructOldTheoryWithPDFError(TString DataName, TString subName)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_OldTheory" + subName;

 TH1D* Hist = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Hist->GetNbinsX(); ibin++){
   Hist->SetBinContent(ibin, OldTheory[DataName].at(ibin - 1));
   Hist->SetBinError(ibin, OldPDFError[DataName].at(ibin - 1));
 }

 return Hist;
}

TH1D* ePumpHelper::ConstructNewTheoryWithPDFError(TString DataName, TString subName)
{
 TString OriginHistName = DataName;
 OriginHistName.ReplaceAll("/", "_");
 OriginHistName.ReplaceAll(".", "_");
 TString HistName = OriginHistName + "_NewTheory" + subName;

 TH1D* Hist = new TH1D(HistName, HistName, DataNPoints[DataName], 0, DataNPoints[DataName]);

 for(int ibin = 1; ibin <= Hist->GetNbinsX(); ibin++){
   Hist->SetBinContent(ibin, NewTheory[DataName].at(ibin - 1));
   Hist->SetBinError(ibin, NewPDFError[DataName].at(ibin - 1));
 }

 return Hist;
}

void ePumpHelper::SaveAllHist()
{
 if(isLinkFile) hf->cd();

 for(int i = 0; i < AllDataNames.size(); i++){
   TH1D* OldPDFError = ConstructOldPDFErrorHist(AllDataNames.at(i), "", "Relative");
   TH1D* NewPDFError = ConstructNewPDFErrorHist(AllDataNames.at(i), "", "Relative");
   OldPDFError->Write();
   NewPDFError->Write();

/*
   for(int iflavor = -5; iflavor <= 5; iflavor++){
     if(iflavor == 0){
       DrawL2Sensitivity(AllDataNames.at(i), 21, 100.0);
     }
     else{
       DrawL2Sensitivity(AllDataNames.at(i), iflavor, 100.0);
     }
   }
*/
 }
}

void ePumpHelper::SaveOptimizeHist()
{
 if(isLinkFile) hf->cd();

 for(int i = 0; i < AllDataNames.size(); i++){
   vector<TH1D *> Hists = ConstructTheoryHist(AllDataNames.at(i));
   vector<TH1D *> OptimizeHists = ConstructOptimizeTheoryHist(AllDataNames.at(i));

   for(int ihist = 0; ihist < Hists.size(); ihist++){
     Hists.at(ihist)->Write();
   }

   for(int ihist = 0; ihist < OptimizeHists.size(); ihist++){
     OptimizeHists.at(ihist)->Write();
   }

   for(int iEV = 0; iEV < NEV; iEV++){
     FractionalContributionHist[AllDataNames.at(i)].at(iEV)->Write();
   }
 }
}

//////////////////////////////////////////////////////////////////////////

void ePumpHelper::SetDataWeight(TString DataName, double w)
{
 int Index = DataIndex[DataName];

 EU->weight.at(Index) = w;
}

void ePumpHelper::ResetWeight()
{
 for(int i = 0; i < EU->weight.size(); i++){
   EU->weight.at(i) = 0.0;
 }

}

void ePumpHelper::TurnOnData(TString DataName)
{
 int Index = DataIndex[DataName];
 EU->dataIncluded.at(Index) = true;

 TString Datafile = DataName + ".data";

 switch (DataErrorType[DataName]) {
     case 1: EU->ReadInData1((char *)Datafile.Data(),Index);
             break;
     case 2: EU->ReadInData2((char *)Datafile.Data(),Index);
             break;
     case 3: EU->ReadInData3((char *)Datafile.Data(),Index);
             break;
     default: { cerr<<"  Error Type must be 1, 2, or 3."<<endl;
                exit(1);
     }
 }

 DataNPoints[DataName] = EU->Na.at(Index);
 DataPoint[DataName].resize(DataNPoints[DataName]);
 DataTotalErr[DataName].resize(DataNPoints[DataName]);
 for(int i = 0; i < DataPoint[DataName].size(); i++){
   DataPoint[DataName].at(i) = EU->XE.at(Index).at(i);
   DataTotalErr[DataName].at(i) = EU->s.at(Index).at(i);
 }

}

void ePumpHelper::ResetData()
{
 for(int i = 0; i < EU->dataIncluded.size(); i++){
   EU->dataIncluded.at(i) = false;
 }
}

void ePumpHelper::ResetUpdate()
{
 OldTheory.clear();
 NewTheory.clear();
 OldPDFError.clear();
 NewPDFError.clear();
 if(doCorrelationCosine) OldPDFCorrelation.clear();
 if(doCorrelationCosine) NewPDFCorrelation.clear();

 OldChi2.clear();
 NewChi2.clear();
 OldSpartyness.clear();
 NewSpartyness.clear();

 ResetWeight();
}

void ePumpHelper::SaveHist()
{
 DoSaveHist = true;
 EU->SaveHist();
}

void ePumpHelper::TurnOffCorrelationCosine()
{
 doCorrelationCosine = false;
 EU->suppressCCs();
}

void ePumpHelper::TurnOffUpdatePDF()
{
 isTurnOffUpdatePDF = true;
 EU->pdftype = PDF_format_type::NONE;
}

