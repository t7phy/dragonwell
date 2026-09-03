#include "Calculation/GlobalFittingCore.h"

void GlobalFittingCore::ParameterScan()
{
 TFile* writefile = new TFile("ParameterScan.root", "RECREATE");
 writefile->cd();

 int nScanPoint = 11;

 vector<double> ParameterSet = {-5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

 if(nScanPoint != ParameterSet.size()) cout<<"ERROR! Check the ParameterSet input!"<<endl;

 map<TString, vector<double>> Chi2Map;
 for(int idata = 0; idata < m_fcn->AllData.size(); idata++){
   Chi2Map[m_fcn->AllData.at(idata)->m_name].resize(nScanPoint);
 }
 Chi2Map[(TString)"Total"].resize(nScanPoint);

 // Get BestFit Chi2
// ROOT::Minuit2::MnMigrad migrad(*this, this->upar);
// ROOT::Minuit2::FunctionMinimum min = migrad(10000);
// FCN.Finalize();
// m_fcn->Chi2(false, true);

 vector<double> pars = GetInitialParameters();
 vector<double> parerrs;

 // Scan Lambda
 for(int i = 0; i < nScanPoint; i++){
   cout<<"Scan "<<i + 1<<endl;

   TString SavedLMScanResult = (TString)"Parameters_c" + TString::Format("%.1f", ParameterSet.at(i)) + (TString)".yml";

   std::filesystem::path file_path = SavedLMScanResult.Data();

   cout<<"Reading from "<<SavedLMScanResult<<endl;

   ReadingNewParaFile(SavedLMScanResult);

   this->ResetFit();

   pars = newsetting.GetInitialParameters();

   // y-axis
   for(int idata = 0; idata < m_fcn->AllChi2.size(); idata++){
     Chi2Map.at(m_fcn->AllData.at(idata)->m_name).at(i) = m_fcn->AllChi2.at(idata);
   }
   Chi2Map.at((TString)"Total").at(i) = m_fcn->FitChi2;

 }

 double BestFitSolution = Chi2Solution(ParameterSet, Chi2Map.at((TString)"Total"));//find the bestfit of the total chi2

 double xmin = ParameterSet.at(0) - (ParameterSet.at(1) - ParameterSet.at(0));
 double xmax = ParameterSet.at(nScanPoint - 1) + (ParameterSet.at(nScanPoint - 1) - ParameterSet.at(nScanPoint - 2));

 for(auto iter = Chi2Map.begin(); iter != Chi2Map.end(); iter++){

   writefile->cd();

   TString HistName;
   HistName = (TString)"ParameterLMScanOriginResult_" + iter->first;
   HistName.ReplaceAll("/", "_");
   HistName.ReplaceAll(".", "_");
   HistName.ReplaceAll("-", "m");

   TString FittingName;
   FittingName = (TString)"ParameterLMScanOriginFitting_" + iter->first;
   FittingName.ReplaceAll("/", "_");
   FittingName.ReplaceAll(".", "_");
   FittingName.ReplaceAll("-", "m");

   TString PointName;
   PointName = (TString)"ParameterLMScanOriginPoint_" + iter->first;
   PointName.ReplaceAll("/", "_");
   PointName.ReplaceAll(".", "_");
   PointName.ReplaceAll("-", "m");

   ParameterLMScanOriginResult[iter->first] = new TGraph(nScanPoint);
   ParameterLMScanOriginResult.at(iter->first)->SetName(HistName);
   ParameterLMScanOriginResult.at(iter->first)->SetTitle(HistName);

   ParameterLMScanOriginPoint[iter->first] = new TGraph(nScanPoint);
   ParameterLMScanOriginPoint.at(iter->first)->SetName(PointName);
   ParameterLMScanOriginPoint.at(iter->first)->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     ParameterLMScanOriginResult.at(iter->first)->SetPointX(ibin, ParameterSet.at(ibin - 1));
     ParameterLMScanOriginResult.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1));
     ParameterLMScanOriginPoint.at(iter->first)->SetPointX(ibin, ParameterSet.at(ibin - 1));
     ParameterLMScanOriginPoint.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1));
     cout<<"ScanResult for Data "<<iter->first<<": Parameter = "<<ParameterSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map.at(iter->first).at(ibin - 1)<<endl;
   }
   ParameterLMScanOriginResult.at(iter->first)->RemovePoint(0);
   ParameterLMScanOriginResult.at(iter->first)->SetMarkerSize(0);
   ParameterLMScanOriginResult.at(iter->first)->SetMarkerColor(0);
   ParameterLMScanOriginResult.at(iter->first)->SetLineWidth(0);
   ParameterLMScanOriginResult.at(iter->first)->SetLineColor(0);
   ParameterLMScanOriginResult.at(iter->first)->SetLineStyle(1);
   ParameterLMScanOriginResult.at(iter->first)->SetMarkerStyle(34);
   ParameterLMScanOriginPoint.at(iter->first)->RemovePoint(0);

   ParameterLMScanOriginFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") ParameterLMScanOriginFitting.at(iter->first)->SetNpx(50000);
   ParameterLMScanOriginResult.at(iter->first)->Fit(ParameterLMScanOriginFitting.at(iter->first), "W");

   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   HistName.ReplaceAll("ParameterLMScanOriginResult", "ParameterLMScanResult");
   FittingName.ReplaceAll("ParameterLMScanOriginFitting", "ParameterLMScanFitting");
   PointName.ReplaceAll("ParameterLMScanOriginPoint", "ParameterLMScanPoint");

   ParameterLMScanResult[iter->first] = new TGraph(nScanPoint);
   ParameterLMScanResult.at(iter->first)->SetName(HistName);
   ParameterLMScanResult.at(iter->first)->SetTitle(HistName);

   ParameterLMScanPoint[iter->first] = new TGraph(nScanPoint);
   ParameterLMScanPoint.at(iter->first)->SetName(PointName);
   ParameterLMScanPoint.at(iter->first)->SetTitle(PointName);

   for(int ibin = 1; ibin <= nScanPoint; ibin++){
     double DataOriginChi2 = ParameterLMScanOriginFitting.at(iter->first)->Eval(BestFitSolution);

     ParameterLMScanResult.at(iter->first)->SetPointX(ibin, ParameterSet.at(ibin - 1));
     ParameterLMScanResult.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2);
     ParameterLMScanPoint.at(iter->first)->SetPointX(ibin, ParameterSet.at(ibin - 1));
     ParameterLMScanPoint.at(iter->first)->SetPointY(ibin, Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2);
     cout<<"ScanResult for Data "<<iter->first<<": Parameter = "<<ParameterSet.at(ibin - 1)<<" Chi2 = "<<Chi2Map.at(iter->first).at(ibin - 1) - DataOriginChi2<<endl;
   }
   ParameterLMScanResult.at(iter->first)->RemovePoint(0);
   ParameterLMScanResult.at(iter->first)->SetMarkerSize(0);
   ParameterLMScanResult.at(iter->first)->SetMarkerColor(0);
   ParameterLMScanResult.at(iter->first)->SetLineWidth(0);
   ParameterLMScanResult.at(iter->first)->SetLineColor(0);
   ParameterLMScanResult.at(iter->first)->SetLineStyle(1);
   ParameterLMScanResult.at(iter->first)->SetMarkerStyle(34);
   ParameterLMScanPoint.at(iter->first)->RemovePoint(0);

   ParameterLMScanFitting[iter->first] = new TF1(FittingName, "[0]*x*x+[1]*x+[2]", xmin, xmax);
   if(iter->first == "Total") ParameterLMScanFitting.at(iter->first)->SetNpx(50000);
   ParameterLMScanResult.at(iter->first)->Fit(ParameterLMScanFitting.at(iter->first), "W");

   ParameterLMScanOriginResult.at(iter->first)->Write();
   ParameterLMScanOriginFitting.at(iter->first)->Write();
   ParameterLMScanOriginPoint.at(iter->first)->Write();
   ParameterLMScanResult.at(iter->first)->Write();
   ParameterLMScanFitting.at(iter->first)->Write();
   ParameterLMScanPoint.at(iter->first)->Write();
 }

 double par[3];
 ParameterLMScanOriginFitting.at("Total")->GetParameters(par);

 double Central = -par[1] / (2 * par[0]);
 double BestChi2 = (4 * par[0] * par[2] - par[1] * par[1]) / (4 * par[0]);

 double Solution1 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 100.0))) / (2 * par[0]);
 double Solution2 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 100.0))) / (2 * par[0]);
 double Solution3 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 230.0))) / (2 * par[0]);
 double Solution4 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 230.0))) / (2 * par[0]);
 double Solution1_T37 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 37.0))) / (2 * par[0]);
 double Solution2_T37 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 37.0))) / (2 * par[0]);
 double Solution1_T10 = (-par[1] - sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 10.0))) / (2 * par[0]);
 double Solution2_T10 = (-par[1] + sqrt(par[1] * par[1] - 4.0 * par[0] * (par[2] - BestChi2 - 10.0))) / (2 * par[0]);

 cout<<"T2 = 100:"<<endl;
 cout<<"Parameter = "<<fixed<<setprecision(10)<<Central<<" + "<<Solution2 - Central<<" - "<<Central - Solution1<<endl;
 cout<<"Parameter up = "<<Solution2<<endl;
 cout<<"Parameter down = "<<Solution1<<endl;
 cout<<"T2 = 37:"<<endl;
 cout<<"Parameter = "<<Central<<" + "<<Solution2_T37 - Central<<" - "<<Central - Solution1_T37<<endl;
 cout<<"Parameter up = "<<Solution2_T37<<endl;
 cout<<"Parameter down = "<<Solution1_T37<<endl;
 cout<<"T2 = 10:"<<endl;
 cout<<"Parameter = "<<Central<<" + "<<Solution2_T10 - Central<<" - "<<Central - Solution1_T10<<endl;
 cout<<"Parameter up = "<<Solution2_T10<<endl;
 cout<<"Parameter down = "<<Solution1_T10<<endl;

 writefile->Close();
}
