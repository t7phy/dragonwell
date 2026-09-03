#include "CompareDataTheory/CompareDataTheory.h"

CompareDataTheory::CompareDataTheory()
{

}

void CompareDataTheory::OpenFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void CompareDataTheory::InputDataCentral(TH1D* DataPlot, int isGetError)
{
 hf->cd();

 this->DataPlot = (TH1D *)DataPlot->Clone("DataPlot");

 DataNbins = this->DataPlot->GetNbinsX();

 if(isOutput){
   for(int ibin = 0; ibin < DataPlot->GetNbinsX(); ibin++){
     cout<<"Data Point No."<<ibin + 1<<": "<<DataPlot->GetBinContent(ibin + 1)<<" Error: "<<DataPlot->GetBinError(ibin + 1)<<endl;
   }
   cout<<endl;
 }

 TotalDataCovariance = new TH2D("TotalDataCovariance", "TotalDataCovariance", DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);

 if(isGetError == 1){
   DataCovariance[DataCovCount] = new TH2D((TString)"DataCovariance" + (int)DataCovCount, (TString)"DataCovariance" + (int)DataCovCount, DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);

   if(isOutput) cout<<"Data Statistic Covariance:"<<endl;
   for(int ibinx = 0; ibinx < DataNbins; ibinx++){
     for(int ibiny = 0; ibiny < DataNbins; ibiny++){
       if(ibinx == ibiny) DataCovariance[DataCovCount]->SetBinContent(ibinx + 1, ibiny + 1, DataPlot->GetBinError(ibinx + 1) * DataPlot->GetBinError(ibiny + 1));
       if(isOutput) cout<<DataCovariance[DataCovCount]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
     }
     if(isOutput) cout<<endl;
   }

   if(isOutput) cout<<endl;

   DataCovCount++;
 }

}

void CompareDataTheory::InputDataStaCorrelation(TH2D* Correlation, TH1D* StaErr)
{
 hf->cd();

 DataCovariance[DataCovCount] = new TH2D((TString)"DataCovariance" + (int)DataCovCount, (TString)"DataCovariance" + (int)DataCovCount, DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);

 if(isOutput) cout<<"Data Statistic Covariance:"<<endl;
 for(int ibinx = 0; ibinx < DataNbins; ibinx++){
   for(int ibiny = 0; ibiny < DataNbins; ibiny++){
     DataCovariance[DataCovCount]->SetBinContent(ibinx + 1, ibiny + 1, Correlation->GetBinContent(ibinx + 1, ibiny + 1) * StaErr->GetBinContent(ibinx + 1) * StaErr->GetBinContent(ibiny + 1));
     if(isOutput) cout<<DataCovariance[DataCovCount]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
   }
   if(isOutput) cout<<endl;
 }

 if(isOutput) cout<<endl;

 DataCovCount++;

}

void CompareDataTheory::InputDataCovariance(TH2D* Covariance)
{
 hf->cd();

 DataCovariance[DataCovCount] = (TH2D *)Covariance->Clone((TString)"DataCovariance" + (int)DataCovCount);

 if(isOutput) cout<<"Data Covariance:"<<endl;
 for(int ibinx = 0; ibinx < DataNbins; ibinx++){
   for(int ibiny = 0; ibiny < DataNbins; ibiny++){
     if(isOutput) cout<<DataCovariance[DataCovCount]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
   }
   if(isOutput) cout<<endl;
 }

 if(isOutput) cout<<endl;

 DataCovCount++;
}

void CompareDataTheory::InputDataStaErr(TH1D* StaErr)
{
 hf->cd();
  DataCovariance[DataCovCount] = new TH2D((TString)"DataCovariance" + (int)DataCovCount, (TString)"DataCovariance" + (int)DataCovCount, DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);
 
 if(isOutput) cout<<"Data Statistic Covariance:"<<endl;
 for(int ibinx = 0; ibinx < DataNbins; ibinx++){
   for(int ibiny = 0; ibiny < DataNbins; ibiny++){
     if(ibinx == ibiny) DataCovariance[DataCovCount]->SetBinContent(ibinx + 1, ibiny + 1, StaErr->GetBinContent(ibinx + 1) * StaErr->GetBinContent(ibiny + 1));
     if(isOutput) cout<<DataCovariance[DataCovCount]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
   }
   if(isOutput) cout<<endl;
 }
 
 if(isOutput) cout<<endl;
 
 DataCovCount++;

}

void CompareDataTheory::InputDataSysErr(vector<TH1D *> DataSysErr)
{
 hf->cd();

 for(int i = 0; i < DataSysErr.size(); i++){
   DataError[i] = (TH1D *)DataSysErr.at(i)->Clone((TString)"DataSysErr" + (int)(i + 1));
   DataCovariance[DataCovCount] = new TH2D((TString)"DataCovariance" + (int)DataCovCount, (TString)"DataCovariance" + (int)DataCovCount, DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);

   if(isOutput) cout<<"Data Systematic Covariance No."<<i + 1<<":"<<endl;
   for(int ibinx = 0; ibinx < DataNbins; ibinx++){
     for(int ibiny = 0; ibiny < DataNbins; ibiny++){
       DataCovariance[DataCovCount]->SetBinContent(ibinx + 1, ibiny + 1, 1.0 * DataError[i]->GetBinContent(ibinx + 1) * DataError[i]->GetBinContent(ibiny + 1));
       if(isUnCorrSys && ibinx == ibiny) DataCovariance[DataCovCount]->SetBinContent(ibinx + 1, ibiny + 1, 1.0 * DataError[i]->GetBinContent(ibinx + 1) * DataError[i]->GetBinContent(ibiny + 1));
       if(isUnCorrSys && ibinx != ibiny) DataCovariance[DataCovCount]->SetBinContent(ibinx + 1, ibiny + 1, 0.0);
       if(isOutput) cout<<DataCovariance[DataCovCount]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
     }
     if(isOutput) cout<<endl;
   }

   if(isOutput) cout<<endl;

   DataCovCount++;
 }

 if(isOutput){
   for(int ibin = 0; ibin < DataNbins; ibin++){
     cout<<"Data Systematic Error: Point No."<<ibin + 1<<": ";
     for(int i = 0; i < DataSysErr.size();i++){
       cout<<DataSysErr.at(i)->GetBinContent(ibin + 1)<<" ";  
     }
     cout<<endl;
   }
   cout<<endl;
 }

}

void CompareDataTheory::GetTotalDataCovariance()
{
 hf->cd();

 cout<<"Number of Data Covariance is "<<DataCovCount - 1<<endl;
 for(int i = 1; i < DataCovCount; i++){
   TotalDataCovariance->Add(DataCovariance[i]);
 }

 if(isOutput) cout<<"Data Total Covariance:"<<endl;
 for(int ibinx = 0; ibinx < DataNbins; ibinx++){
   for(int ibiny = 0; ibiny < DataNbins; ibiny++){
     if(isOutput) cout<<TotalDataCovariance->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
   }
   if(isOutput) cout<<endl;
 }
 if(isOutput) cout<<endl;
}

void CompareDataTheory::InputTheoryCentral(vector<TH1D *> TheoryPlotList)
{
 hf->cd();

 for(int i = 0; i < TheoryPlotList.size(); i++){
   this->TheoryPlot[TheoryPlotCount] = (TH1D *)TheoryPlotList.at(i)->Clone((TString)"TheoryPlot" + (int)TheoryPlotCount);
   if(isOutput){
     for(int ibin = 0; ibin < TheoryPlot[TheoryPlotCount]->GetNbinsX(); ibin++){
       cout<<"Theory No."<<i + 1<<" Data Point No."<<ibin + 1<<": "<<TheoryPlot[TheoryPlotCount]->GetBinContent(ibin + 1)<<" Error: "<<TheoryPlot[TheoryPlotCount]->GetBinError(ibin + 1)<<endl;
     }
     cout<<endl;
   }

   TheoryNbins = this->TheoryPlot[TheoryPlotCount]->GetNbinsX();
   if(DataNbins != TheoryNbins) cout<<"ERROR! The number of bins is not identical between data and theory."<<endl;

   TotalTheoryCovariance[TheoryPlotCount] = new TH2D((TString)"TotalTheoryCovariance" + (int)TheoryPlotCount, (TString)"TotalTheoryCovariance" + (int)TheoryPlotCount, DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);

   TheoryStaCovariance[TheoryPlotCount] = new TH2D((TString)"TheoryStaCovariance" + (int)TheoryPlotCount, (TString)"TheoryStaCovariance" + (int)TheoryPlotCount, DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);

   if(isOutput) cout<<"Theory Statistic Covariance No."<<i + 1<<":"<<endl;
   for(int ibinx = 0; ibinx < DataNbins; ibinx++){
     for(int ibiny = 0; ibiny < DataNbins; ibiny++){
       if(ibinx == ibiny) TheoryStatCov = TheoryPlot[TheoryPlotCount]->GetBinError(ibinx + 1) * TheoryPlot[TheoryPlotCount]->GetBinError(ibiny + 1);
       if(ibinx != ibiny) TheoryStatCov = 0.0;
       TheoryStaCovariance[TheoryPlotCount]->SetBinContent(ibinx + 1, ibiny + 1, TheoryStatCov);
       if(isOutput) cout<<TheoryStaCovariance[TheoryPlotCount]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
     }
     if(isOutput) cout<<endl;
   }
   if(isOutput) cout<<endl;

   Ratio[TheoryPlotCount] = (TH1D *)TheoryPlot[TheoryPlotCount]->Clone((TString)"Ratio" + (int)TheoryPlotCount);
   Ratio[TheoryPlotCount]->Divide(DataPlot);

   TheoryPlotCount++;
 }

}

void CompareDataTheory::InputTheoryPDFCovariance(TH2D* Covariance)
{
 hf->cd();

 isPDFCovariance = true;

 this->TheoryPDFCovariance = (TH2D *)Covariance->Clone("TheoryPDFCovariance");

 if(isOutput) cout<<"Theory PDF Covariance:"<<endl;
 for(int ibinx = 0; ibinx < DataNbins; ibinx++){
   for(int ibiny = 0; ibiny < DataNbins; ibiny++){
     if(isOutput) cout<<TheoryPDFCovariance->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
   }
   if(isOutput) cout<<endl;
 }
 if(isOutput) cout<<endl;

}

void CompareDataTheory::GetTotalTheoryCovariance()
{
 hf->cd();

 cout<<"There are "<<TheoryPlotCount - 1<<" plots."<<endl;

 for(int i = 1; i < TheoryPlotCount; i++){
   TotalTheoryCovariance[i]->Add(TheoryStaCovariance[i]);
   if(isPDFCovariance) TotalTheoryCovariance[i]->Add(TheoryPDFCovariance);

   if(isOutput) cout<<"Theory Total Covariance No."<<i<<":"<<endl;
   for(int ibinx = 0; ibinx < DataNbins; ibinx++){
     for(int ibiny = 0; ibiny < DataNbins; ibiny++){
       if(isOutput) cout<<TotalTheoryCovariance[i]->GetBinContent(ibinx + 1, ibiny + 1)<<"  ";
     }
     if(isOutput) cout<<endl;
   }
   if(isOutput) cout<<endl;
 }

}

void CompareDataTheory::InputTemplateRange(int size, double left, double right)
{
 hf->cd();

 this->left = left;
 this->right = right;
 this->size = size;

 Chi2Hist = new TH1D("Chi2Hist", "Chi2Hist", size, left, right);
}

void CompareDataTheory::InputTheoryTemplate(vector<TH1D *> TheoryTemplate)
{
 hf->cd();

 for(int i = 0; i < TheoryTemplate.size(); i++){
   TemplateStaCovariance[i] = new TH2D((TString)"TemplateStaCovariance" + (int)(i + 1), (TString)"TemplateStaCovariance" + (int)(i + 1), DataNbins, 1, DataNbins, DataNbins, 1, DataNbins);
   for(int ibinx = 0; ibinx < DataNbins; ibinx++){
     for(int ibiny = 0; ibiny < DataNbins; ibiny++){
       if(ibinx == ibiny) TheoryStatCov = TheoryTemplate.at(i)->GetBinError(ibinx + 1) * TheoryTemplate.at(i)->GetBinError(ibiny + 1);
       if(ibinx != ibiny) TheoryStatCov = 0.0;
       TemplateStaCovariance[i]->SetBinContent(ibinx + 1, ibiny + 1, TheoryStatCov);
     }
   }
   TemplateCovariance[i] = (TH2D *)TemplateStaCovariance[i]->Clone((TString)"TemplateCovariance" + (int)(i + 1));
   if(isPDFCovariance) TemplateCovariance[i]->Add(TheoryPDFCovariance);
   TemplateCovariance[i]->Add(TotalDataCovariance);
   if(isIgnoreTemplateStatistic) TemplateCovariance[i] = (TH2D *)TotalDataCovariance->Clone((TString)"TemplateTotalCovariance" + (int)(i + 1));

   CalculateInverseMatrix(TemplateCovariance[i], TemplateInverseCovariance[i]);
   TemplateChi2[i] = CalculateChi2(DataPlot, TheoryTemplate.at(i), TemplateInverseCovariance[i]); 
//   TemplateChi2[i] = CalculateChi2(DataPlot, TheoryTemplate.at(i));

   Chi2Hist->SetBinContent(i + 1, TemplateChi2[i]);
   Chi2Hist->SetBinError(i + 1, 0);

   TheoryTemplate.at(i)->Write();

   RatioTemplate[i] = (TH1D *)TheoryTemplate.at(i)->Clone((TString)"RatioTemplate" + (int)(i + 1));
   RatioTemplate[i]->Divide(DataPlot);
   RatioTemplate[i]->Write();
 }

 Chi2Fitting(Chi2Hist, FitHist);
 FitHist->Write();
}

void CompareDataTheory::FitAFBStw(vector<TH1D *> v_Plot)
{
 hf->cd();

 TH1D* AFBStw = new TH1D("AFBStw", "AFBStw", size, left, right);
 for(int i = 0; i < v_Plot.size(); i++){
   AFBStw->SetBinContent(i + 1, v_Plot.at(i)->GetBinContent(1));
   AFBStw->SetBinError(i + 1, 0);
 }

 TF1* fitting;
 double *par = new double[2];
 double *parErr = new double[2];
 LinearFitting(AFBStw, fitting, par, parErr);

 fitting->Write();
}

void CompareDataTheory::GetChi2()
{
 hf->cd();

 for(int i = 1; i < TheoryPlotCount; i++){
   TotalCovariance[i] = (TH2D *)TotalTheoryCovariance[i]->Clone("TotalCovariance");
   TotalCovariance[i]->Add(TotalDataCovariance);

   CalculateInverseMatrix(TotalCovariance[i], InverseCovariance[i]);

   Chi2[i] = CalculateChi2(DataPlot, TheoryPlot[i], InverseCovariance[i]);
   Sigma[i] = TranslateChi2ToGaussSigma(Chi2[i], DataNbins);
   cout<<"Theory No."<<i<<" Chi2 = "<<Chi2[i]<<" "<<Sigma[i]<<" Sigma"<<endl;
 }
}

void CompareDataTheory::GetPDFUncertainty(vector<TH1D *> PDFHists, vector<TH1D *> STWHists, double &PDFUnc)
{
 vector<TH1D *> Hists;
 TH1D *PDFError;

 if(isLinkFile) outFile->cd();

 for(int iPDF = 0; iPDF < PDFHists.size(); iPDF++){
   TH1D *Chi2Hist = new TH1D(PDFHists.at(0)->GetName() + (TString)"Chi2_" + (int)iPDF, PDFHists.at(0)->GetName() + (TString)"Chi2_" + (int)iPDF, 40, 0.2255 - 0.0003 / 2, 0.2372 + 0.0003 / 2);
   TF1 *Fitting;
   for(int i = 0; i < STWHists.size(); i++){
     double Chi2;
     if(!isInputBinRange) Chi2 = CalculateChi2(PDFHists.at(iPDF), STWHists.at(i));
     if(isInputBinRange) Chi2 = CalculateChi2(PDFHists.at(iPDF), STWHists.at(i), FirstBin, LastBin);

     Chi2Hist->SetBinContent(i, Chi2);
   }
   double stw, stwError;
   Chi2Fitting(Chi2Hist, Fitting, stw, stwError);
   TH1D *Result = new TH1D((TString)PDFHists.at(iPDF)->GetName() + "_ExtractResult_PDF" + (int)iPDF, (TString)PDFHists.at(iPDF)->GetName() + "_ExtractResult_PDF" + (int)iPDF, 1, 0, 1);
   Result->SetBinContent(1, stw);
   Result->SetBinError(1, stwError);
   Hists.push_back(Result);

   if(isLinkFile) Chi2Hist->Write();

   delete Chi2Hist;
   delete Fitting;
 }

 PDFUncertainty *unc = new PDFUncertainty();
 unc->Input1DPlot("Symmetry", Hists, PDFError);

 cout<<"************  Results  ************"<<endl;
 cout<<"Central :"<<Hists.at(0)->GetBinContent(1)<<endl;
 cout<<"Sta Error:"<<Hists.at(0)->GetBinError(1)<<endl;
 cout<<"PDF Error: "<<PDFError->GetBinContent(1)<<endl;
 cout<<"***********************************"<<endl;

 PDFUnc = PDFError->GetBinContent(1);
}

void CompareDataTheory::LinkOutFile(TFile* &outFile)
{
 isLinkFile = true;

 this->outFile = outFile;
}

void CompareDataTheory::InputBinRange(int FirstBin, int LastBin)
{
 isInputBinRange = true;

 this->FirstBin = FirstBin;
 this->LastBin = LastBin;
}

void CompareDataTheory::Save()
{
 hf->cd();

 hf->Write();
 hf->Close();
}
