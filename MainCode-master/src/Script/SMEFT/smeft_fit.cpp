#include "/home/yaofu/figure/Figure.h"

void smeft_fit()
{
 auto QuadraticFit = [&](vector<TH1D *> Hists, vector<double> Coefficients, TString OutputName){
   cout<<"QuadraticFit on "<<OutputName<<endl;

   OutputName.ReplaceAll("Re1111", "");

   if(Hists.size() != Coefficients.size()){
     cout<<"ERROR!"<<endl;
   }

   TString HistName = Hists.at(0)->GetName();
   int nPoints = Hists.at(0)->GetNbinsX();

   vector<TString> CoeffName(Coefficients.size());
   for(int i = 0; i < Coefficients.size(); i++){
     TString Coeff = TString::Format("%.1f", Coefficients.at(i));
     Coeff.ReplaceAll(".", "p");
     CoeffName.at(i) = Coeff;
   }

   double step = (Coefficients.at(1) - Coefficients.at(0));
   vector<double> Binning(Coefficients.size() + 1);
   for(int i = 0; i < Binning.size() - 1; i++){
     Binning.at(i) = Coefficients.at(i) - step / 2.0;
   }
   Binning.at(Binning.size() - 1) = Coefficients.at(Coefficients.size() - 1) + step / 2.0;

   vector<TH1D *> RawHist(Hists.size());

   for(int i = 0; i < Hists.size(); i++){
     RawHist.at(i) = (TH1D *)Hists.at(i)->Clone(HistName + "_" + CoeffName.at(i));
     RawHist.at(i)->SetName(HistName + "_" + CoeffName.at(i));
     RawHist.at(i)->SetTitle(HistName + "_" + CoeffName.at(i));
   }

   vector<TGraph *> OriginPoint(nPoints);
   vector<TH1D *> OriginHist(nPoints);
   vector<TF1 *> OriginFit(nPoints);

   ofstream kfactorfile(OutputName + "_kfactor.txt");

   for(int ipoint = 0; ipoint < nPoints; ipoint++){
     cout<<endl;
     cout<<"Point "<<ipoint + 1<<":"<<endl;

     TString Name = HistName + "Point_ibin" + (int)(ipoint + 1);

     OriginPoint.at(ipoint) = new TGraph(Coefficients.size());
     OriginPoint.at(ipoint)->SetName(Name);
     OriginPoint.at(ipoint)->SetTitle(Name);

     Name.ReplaceAll("Point", "Hist");

     OriginHist.at(ipoint) = new TH1D(Name, Name, Binning.size() - 1, &Binning[0]);

     for(int ic = 0; ic < Hists.size(); ic++){
       double BSM = Hists.at(ic)->GetBinContent(ipoint + 1);
       double SM = Hists.at(0)->GetBinContent(ipoint + 1);
       double Content = 0.0;
       if(fabs(SM) > 1e-20) Content = (BSM - SM) / SM;

       OriginPoint.at(ipoint)->SetPointX(ic, Coefficients.at(ic));
       OriginPoint.at(ipoint)->SetPointY(ic, Content);

       OriginHist.at(ipoint)->SetBinContent(ic + 1, Content);
       OriginHist.at(ipoint)->SetBinError(ic + 1, 0.0);

       cout<<ic + 1<<"   ";
       cout<<scientific<<Content<<"  "<<BSM<<"  "<<SM<<endl;
     }

     OriginPoint.at(ipoint)->SetMarkerSize(2);
     OriginPoint.at(ipoint)->SetLineWidth(0);
     OriginPoint.at(ipoint)->SetLineColor(0);
     OriginPoint.at(ipoint)->SetLineStyle(1);
     OriginPoint.at(ipoint)->SetMarkerStyle(34);

     Name.ReplaceAll("Hist", "Fitting");

     OriginFit.at(ipoint) = new TF1(Name, "[0]*x*x+[1]*x+[2]", 0.0, 1.0);

     if(fabs(OriginPoint.at(ipoint)->GetPointY(9)) > 1e-2){
       OriginPoint.at(ipoint)->Fit(OriginFit.at(ipoint), "W");
     }
     else{
       for(int ic = 0; ic < Hists.size(); ic++){
         double Content = OriginPoint.at(ipoint)->GetPointY(ic);
         OriginPoint.at(ipoint)->SetPointY(ic, Content * 1e6);
       }
       OriginPoint.at(ipoint)->Fit(OriginFit.at(ipoint), "W");

       for(int ic = 0; ic < Hists.size(); ic++){
         double Content = OriginPoint.at(ipoint)->GetPointY(ic);
         OriginPoint.at(ipoint)->SetPointY(ic, Content / 1e6);
       }
       double A = OriginFit.at(ipoint)->GetParameter(0) / 1e6;
       double B = OriginFit.at(ipoint)->GetParameter(1) / 1e6;
       double C = OriginFit.at(ipoint)->GetParameter(2) / 1e6;

       OriginFit.at(ipoint)->SetParameter(0, A);
       OriginFit.at(ipoint)->SetParameter(1, B);
       OriginFit.at(ipoint)->SetParameter(2, C);

       TF1* f_graph = OriginPoint.at(ipoint)->GetFunction(OriginFit.at(ipoint)->GetName());
       if (f_graph) {
           f_graph->SetParameter(0, A);
           f_graph->SetParameter(1, B);
           f_graph->SetParameter(2, C);
       }

       double ymin = OriginPoint.at(ipoint)->GetHistogram()->GetMinimum();
       double ymax = OriginPoint.at(ipoint)->GetHistogram()->GetMaximum();

       OriginPoint.at(ipoint)->GetHistogram()->SetMinimum(ymin);
       OriginPoint.at(ipoint)->GetHistogram()->SetMaximum(ymax);
     }

     double A = OriginFit.at(ipoint)->GetParameter(0);
     double B = OriginFit.at(ipoint)->GetParameter(1);
     double C = OriginFit.at(ipoint)->GetParameter(2);

     kfactorfile << "Quadratic ";
     kfactorfile << setw(13) << setprecision(5) << scientific << A;
     kfactorfile << setw(13) << setprecision(5) << scientific << B;
     kfactorfile << setw(13) << setprecision(5) << scientific << 0.0;
     kfactorfile << endl;
   }

   auto Result = make_tuple(RawHist, OriginPoint, OriginHist, OriginFit);

   return Result;
 };

 auto SaveResult = [&](TFile* file, tuple<vector<TH1D*>, vector<TGraph*>, vector<TH1D*>, vector<TF1*>> Result){
   file->cd();
   for(int i = 0; i < get<0>(Result).size(); i++){
     get<0>(Result).at(i)->Write();
   }
   for(int i = 0; i < get<1>(Result).size(); i++){
     get<1>(Result).at(i)->Write();
   }
   for(int i = 0; i < get<2>(Result).size(); i++){
     get<2>(Result).at(i)->Write();
   }
   for(int i = 0; i < get<3>(Result).size(); i++){
     get<3>(Result).at(i)->Write();
   }
 };

 TString Operator = "clq3Re1111";

 vector<double> Coefficients = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

 vector<TFile *> Files_LHC13TeV(Coefficients.size());
 vector<TFile *> Files_LHC8TeV(Coefficients.size());
 vector<TFile *> Files_LHC7TeV(Coefficients.size());
 vector<TFile *> Files_LHC5p02TeV(Coefficients.size());
 vector<TFile *> Files_Tevatron1p96TeV(Coefficients.size());
 vector<TFile *> Files_Tevatron1p8TeV(Coefficients.size());

 for(int i = 0; i < Coefficients.size(); i++){
   TString Coeff = TString::Format("%.1f", Coefficients.at(i));

   Files_LHC13TeV.at(i) = new TFile("LHC13TeV/SMEFT_" + Operator + "_c_" + Coeff + "/MC_results.root");
   Files_LHC8TeV.at(i) = new TFile("LHC8TeV/SMEFT_" + Operator + "_c_" + Coeff + "/MC_results.root");
   Files_LHC7TeV.at(i) = new TFile("LHC7TeV/SMEFT_" + Operator + "_c_" + Coeff + "/MC_results.root");
   Files_LHC5p02TeV.at(i) = new TFile("LHC5.02TeV/SMEFT_" + Operator + "_c_" + Coeff + "/MC_results.root");
   Files_Tevatron1p96TeV.at(i) = new TFile("Tevatron1.96TeV/SMEFT_" + Operator + "_c_" + Coeff + "/MC_results.root");
   Files_Tevatron1p8TeV.at(i) = new TFile("Tevatron1.8TeV/SMEFT_" + Operator + "_c_" + Coeff + "/MC_results.root");
 }

 vector<TH1D *> Xsec_1D_CC(Coefficients.size());
 vector<TH1D *> Xsec_1D_CF(Coefficients.size());
 vector<TH1D *> Xsec_2D_CC(Coefficients.size());
 vector<TH1D *> Xsec_2D_CF(Coefficients.size());
 vector<TH1D *> Xsec_3D_CC(Coefficients.size());
 vector<TH1D *> Xsec_3D_CF(Coefficients.size());
 vector<TH1D *> ZMass_CosTheta_uu(Coefficients.size());
 vector<TH1D *> ZMass_CosTheta_dd(Coefficients.size());
 vector<TH1D *> ZMass_CosTheta(Coefficients.size());
 vector<TH1D *> ZMass_HighMass(Coefficients.size());
 vector<TH1D *> ZMass_HighMass_Integral(Coefficients.size());
 vector<TH1D *> ZMass_FullMass(Coefficients.size());
 vector<TH1D *> ATLAS_Mll_HighMass(Coefficients.size());
 vector<TH1D *> ATLAS_costheta(Coefficients.size());
 vector<TH1D *> ATLAS_DilRapidity(Coefficients.size());
 vector<TH1D *> ATLAS_Mll_HighMass_costheta(Coefficients.size());
 vector<TH1D *> ATLAS_Mll_HighMass_DilRapidity(Coefficients.size());
 vector<TH1D *> ATLAS_HMDY_Xsec_3D(Coefficients.size());
 vector<TH1D *> PositiveLeptonEta(Coefficients.size());
 vector<TH1D *> NegativeLeptonEta(Coefficients.size());
 vector<TH1D *> WPlusMTEta(Coefficients.size());
 vector<TH1D *> WMinusMTEta(Coefficients.size());
 vector<TH1D *> WPlusMTEta_Above100(Coefficients.size());
 vector<TH1D *> WMinusMTEta_Above100(Coefficients.size());
 vector<TH1D *> WPlusMT(Coefficients.size());
 vector<TH1D *> WMinusMT(Coefficients.size());
 vector<TH1D *> WPlusMT_Above100(Coefficients.size());
 vector<TH1D *> WMinusMT_Above100(Coefficients.size());
 vector<TH1D *> WPlusHighMassMT(Coefficients.size());
 vector<TH1D *> WMinusHighMassMT(Coefficients.size());
 vector<TH1D *> WPlusHighMassMT_Integral(Coefficients.size());
 vector<TH1D *> WMinusHighMassMT_Integral(Coefficients.size());

 vector<TH1D *> E245(Coefficients.size());
 vector<TH1D *> E246(Coefficients.size());
 vector<TH1D *> E248(Coefficients.size());
 vector<TH1D *> E268(Coefficients.size());
 vector<TH1D *> E249(Coefficients.size());
 vector<TH1D *> E250(Coefficients.size());
 vector<TH1D *> E225(Coefficients.size());
 vector<TH1D *> E227(Coefficients.size());
 vector<TH1D *> E234(Coefficients.size());
 vector<TH1D *> E260(Coefficients.size());
 vector<TH1D *> E261(Coefficients.size());
 vector<TH1D *> E266(Coefficients.size());
 vector<TH1D *> E267(Coefficients.size());
 vector<TH1D *> E281(Coefficients.size());
 vector<TH1D *> E211(Coefficients.size());
 vector<TH1D *> E212(Coefficients.size());
 vector<TH1D *> E218(Coefficients.size());
 vector<TH1D *> E214(Coefficients.size());
 vector<TH1D *> E215(Coefficients.size());
 vector<TH1D *> E217(Coefficients.size());

 for(int i = 0; i < Coefficients.size(); i++){
   Xsec_1D_CC.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("Xsec_1D_CC");
   Xsec_1D_CF.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("Xsec_1D_CF");
   Xsec_2D_CC.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("Xsec_2D_CC_Final");
   Xsec_2D_CF.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("Xsec_2D_CF_Final");
   Xsec_3D_CC.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("Xsec_3D_CC_Final");
   Xsec_3D_CF.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("Xsec_3D_CF_Final");
   ZMass_CosTheta_uu.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ZMass_CosTheta_uu_Final");
   ZMass_CosTheta_dd.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ZMass_CosTheta_dd_Final");
   ZMass_CosTheta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ZMass_CosTheta_Final");
   ZMass_HighMass.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ZMass_HighMass");
   ZMass_HighMass_Integral.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ZMass_HighMass_Integral");
   ZMass_FullMass.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ZMass_FullMass");
   ATLAS_Mll_HighMass.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ATLAS_Mll_HighMass");
   ATLAS_costheta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ATLAS_costheta");
   ATLAS_DilRapidity.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ATLAS_DilRapidity");
   ATLAS_Mll_HighMass_costheta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ATLAS_Mll_HighMass_costheta_NewBinning");
   ATLAS_Mll_HighMass_DilRapidity.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ATLAS_Mll_HighMass_DilRapidity_NewBinning");
   ATLAS_HMDY_Xsec_3D.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("ATLAS_HMDY_Xsec_3D_Final");
   PositiveLeptonEta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("PositiveLeptonEta");
   NegativeLeptonEta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("NegativeLeptonEta");
   WPlusMTEta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WPlusMTEta_Final");
   WMinusMTEta.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WMinusMTEta_Final");
   WPlusMTEta_Above100.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WPlusMTEta_Above100_Final");
   WMinusMTEta_Above100.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WMinusMTEta_Above100_Final");
   WPlusMT.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WPlusMT");
   WMinusMT.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WMinusMT");
   WPlusMT_Above100.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WPlusMT_Above100");
   WMinusMT_Above100.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WMinusMT_Above100");
   WPlusHighMassMT.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WPlusHighMassMT");
   WMinusHighMassMT.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WMinusHighMassMT");
   WPlusHighMassMT_Integral.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WPlusHighMassMT_Integral");
   WMinusHighMassMT_Integral.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("WMinusHighMassMT_Integral");

   E245.at(i) = (TH1D *)Files_LHC7TeV.at(i)->Get("E245_Final");
   E246.at(i) = (TH1D *)Files_LHC8TeV.at(i)->Get("E246_Final");
   E248.at(i) = (TH1D *)Files_LHC7TeV.at(i)->Get("E248_Final");
   E268.at(i) = (TH1D *)Files_LHC7TeV.at(i)->Get("E268_Final");
   E249.at(i) = (TH1D *)Files_LHC8TeV.at(i)->Get("E249_Final");
   E250.at(i) = (TH1D *)Files_LHC8TeV.at(i)->Get("E250_Final");
   E225.at(i) = (TH1D *)Files_Tevatron1p8TeV.at(i)->Get("E225_Final");
   E227.at(i) = (TH1D *)Files_Tevatron1p96TeV.at(i)->Get("E227_Final");
   E234.at(i) = (TH1D *)Files_Tevatron1p96TeV.at(i)->Get("E234_Final");
   E260.at(i) = (TH1D *)Files_Tevatron1p96TeV.at(i)->Get("E260_Final");
   E261.at(i) = (TH1D *)Files_Tevatron1p96TeV.at(i)->Get("E261_Final");
   E266.at(i) = (TH1D *)Files_LHC7TeV.at(i)->Get("E266_Final");
   E267.at(i) = (TH1D *)Files_LHC7TeV.at(i)->Get("E267_Final");
   E281.at(i) = (TH1D *)Files_Tevatron1p96TeV.at(i)->Get("E281_Final");
   E211.at(i) = (TH1D *)Files_LHC8TeV.at(i)->Get("E211_Final");
   E212.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("E212_Final");
   E218.at(i) = (TH1D *)Files_LHC13TeV.at(i)->Get("E218_Final");
   E214.at(i) = (TH1D *)Files_LHC8TeV.at(i)->Get("E214_Final");
   E215.at(i) = (TH1D *)Files_LHC5p02TeV.at(i)->Get("E215_Final");
   E217.at(i) = (TH1D *)Files_LHC8TeV.at(i)->Get("E217_Final");
 }

 auto Result_Xsec_1D_CC                     = QuadraticFit(Xsec_1D_CC                     , Coefficients, "Xsec_1D_CC_" + Operator);
 auto Result_Xsec_1D_CF                     = QuadraticFit(Xsec_1D_CF                     , Coefficients, "Xsec_1D_CF_" + Operator);
 auto Result_Xsec_2D_CC                     = QuadraticFit(Xsec_2D_CC                     , Coefficients, "Xsec_2D_CC_" + Operator);
 auto Result_Xsec_2D_CF                     = QuadraticFit(Xsec_2D_CF                     , Coefficients, "Xsec_2D_CF_" + Operator);
 auto Result_Xsec_3D_CC                     = QuadraticFit(Xsec_3D_CC                     , Coefficients, "Xsec_3D_CC_" + Operator);
 auto Result_Xsec_3D_CF                     = QuadraticFit(Xsec_3D_CF                     , Coefficients, "Xsec_3D_CF_" + Operator);
 auto Result_ZMass_CosTheta_uu              = QuadraticFit(ZMass_CosTheta_uu              , Coefficients, "ZMass_CosTheta_uu_" + Operator);
 auto Result_ZMass_CosTheta_dd              = QuadraticFit(ZMass_CosTheta_dd              , Coefficients, "ZMass_CosTheta_dd_" + Operator);
 auto Result_ZMass_CosTheta                 = QuadraticFit(ZMass_CosTheta                 , Coefficients, "ZMass_CosTheta_" + Operator);
 auto Result_ZMass_HighMass                 = QuadraticFit(ZMass_HighMass                 , Coefficients, "ZMass_HighMass_" + Operator);
 auto Result_ZMass_HighMass_Integral        = QuadraticFit(ZMass_HighMass_Integral        , Coefficients, "ZMass_HighMass_Integral_" + Operator);
 auto Result_ZMass_FullMass                 = QuadraticFit(ZMass_FullMass                 , Coefficients, "ZMass_FullMass_" + Operator);
 auto Result_ATLAS_Mll_HighMass             = QuadraticFit(ATLAS_Mll_HighMass             , Coefficients, "ATLAS_Mll_HighMass_" + Operator);
 auto Result_ATLAS_costheta                 = QuadraticFit(ATLAS_costheta                 , Coefficients, "ATLAS_costheta_" + Operator);
 auto Result_ATLAS_DilRapidity              = QuadraticFit(ATLAS_DilRapidity              , Coefficients, "ATLAS_DilRapidity_" + Operator);
 auto Result_ATLAS_Mll_HighMass_costheta    = QuadraticFit(ATLAS_Mll_HighMass_costheta    , Coefficients, "ATLAS_Mll_HighMass_costheta_" + Operator);
 auto Result_ATLAS_Mll_HighMass_DilRapidity = QuadraticFit(ATLAS_Mll_HighMass_DilRapidity , Coefficients, "ATLAS_Mll_HighMass_DilRapidity_" + Operator);
 auto Result_ATLAS_HMDY_Xsec_3D             = QuadraticFit(ATLAS_HMDY_Xsec_3D             , Coefficients, "ATLAS_HMDY_Xsec_3D_" + Operator);
 auto Result_PositiveLeptonEta              = QuadraticFit(PositiveLeptonEta              , Coefficients, "PositiveLeptonEta_" + Operator);
 auto Result_NegativeLeptonEta              = QuadraticFit(NegativeLeptonEta              , Coefficients, "NegativeLeptonEta_" + Operator);
 auto Result_WPlusMTEta                     = QuadraticFit(WPlusMTEta                     , Coefficients, "WPlusMTEta_" + Operator);
 auto Result_WMinusMTEta                    = QuadraticFit(WMinusMTEta                    , Coefficients, "WMinusMTEta_" + Operator);
 auto Result_WPlusMTEta_Above100            = QuadraticFit(WPlusMTEta_Above100            , Coefficients, "WPlusMTEta_Above100_" + Operator);
 auto Result_WMinusMTEta_Above100           = QuadraticFit(WMinusMTEta_Above100           , Coefficients, "WMinusMTEta_Above100_" + Operator);
 auto Result_WPlusMT                        = QuadraticFit(WPlusMT                        , Coefficients, "WPlusMT_" + Operator);
 auto Result_WMinusMT                       = QuadraticFit(WMinusMT                       , Coefficients, "WMinusMT_" + Operator);
 auto Result_WPlusMT_Above100               = QuadraticFit(WPlusMT_Above100               , Coefficients, "WPlusMT_Above100_" + Operator);
 auto Result_WMinusMT_Above100              = QuadraticFit(WMinusMT_Above100              , Coefficients, "WMinusMT_Above100_" + Operator);
 auto Result_WPlusHighMassMT                = QuadraticFit(WPlusHighMassMT                , Coefficients, "WPlusHighMassMT_" + Operator);
 auto Result_WMinusHighMassMT               = QuadraticFit(WMinusHighMassMT               , Coefficients, "WMinusHighMassMT_" + Operator);
 auto Result_WPlusHighMassMT_Integral       = QuadraticFit(WPlusHighMassMT_Integral       , Coefficients, "WPlusHighMassMT_Integral_" + Operator);
 auto Result_WMinusHighMassMT_Integral      = QuadraticFit(WMinusHighMassMT_Integral      , Coefficients, "WMinusHighMassMT_Integral_" + Operator);

 auto Result_E245 = QuadraticFit(E245, Coefficients, "E245_" + Operator);
 auto Result_E246 = QuadraticFit(E246, Coefficients, "E246_" + Operator);
 auto Result_E248 = QuadraticFit(E248, Coefficients, "E248_" + Operator);
 auto Result_E268 = QuadraticFit(E268, Coefficients, "E268_" + Operator);
 auto Result_E249 = QuadraticFit(E249, Coefficients, "E249_" + Operator);
 auto Result_E250 = QuadraticFit(E250, Coefficients, "E250_" + Operator);
 auto Result_E225 = QuadraticFit(E225, Coefficients, "E225_" + Operator);
 auto Result_E227 = QuadraticFit(E227, Coefficients, "E227_" + Operator);
 auto Result_E234 = QuadraticFit(E234, Coefficients, "E234_" + Operator);
 auto Result_E260 = QuadraticFit(E260, Coefficients, "E260_" + Operator);
 auto Result_E261 = QuadraticFit(E261, Coefficients, "E261_" + Operator);
 auto Result_E266 = QuadraticFit(E266, Coefficients, "E266_" + Operator);
 auto Result_E267 = QuadraticFit(E267, Coefficients, "E267_" + Operator);
 auto Result_E281 = QuadraticFit(E281, Coefficients, "E281_" + Operator);
 auto Result_E211 = QuadraticFit(E211, Coefficients, "E211_" + Operator);
 auto Result_E212 = QuadraticFit(E212, Coefficients, "E212_" + Operator);
 auto Result_E218 = QuadraticFit(E218, Coefficients, "E218_" + Operator);
 auto Result_E214 = QuadraticFit(E214, Coefficients, "E214_" + Operator);
 auto Result_E215 = QuadraticFit(E215, Coefficients, "E215_" + Operator);
 auto Result_E217 = QuadraticFit(E217, Coefficients, "E217_" + Operator);

 TFile* writefile = new TFile("SMEFT_Fit.root", "RECREATE");

 SaveResult(writefile, Result_Xsec_1D_CC);
 SaveResult(writefile, Result_Xsec_1D_CF);
 SaveResult(writefile, Result_Xsec_2D_CC);
 SaveResult(writefile, Result_Xsec_2D_CF);
 SaveResult(writefile, Result_Xsec_3D_CC);
 SaveResult(writefile, Result_Xsec_3D_CF);
 SaveResult(writefile, Result_ZMass_CosTheta_uu);
 SaveResult(writefile, Result_ZMass_CosTheta_dd);
 SaveResult(writefile, Result_ZMass_CosTheta);
 SaveResult(writefile, Result_ZMass_HighMass);
 SaveResult(writefile, Result_ZMass_HighMass_Integral);
 SaveResult(writefile, Result_ZMass_FullMass);
 SaveResult(writefile, Result_ATLAS_Mll_HighMass);
 SaveResult(writefile, Result_ATLAS_costheta);
 SaveResult(writefile, Result_ATLAS_DilRapidity);
 SaveResult(writefile, Result_ATLAS_Mll_HighMass_costheta);
 SaveResult(writefile, Result_ATLAS_Mll_HighMass_DilRapidity);
 SaveResult(writefile, Result_ATLAS_HMDY_Xsec_3D);
 SaveResult(writefile, Result_PositiveLeptonEta);
 SaveResult(writefile, Result_NegativeLeptonEta);
 SaveResult(writefile, Result_WPlusMTEta);
 SaveResult(writefile, Result_WMinusMTEta);
 SaveResult(writefile, Result_WPlusMTEta_Above100);
 SaveResult(writefile, Result_WMinusMTEta_Above100);
 SaveResult(writefile, Result_WPlusMT);
 SaveResult(writefile, Result_WMinusMT);
 SaveResult(writefile, Result_WPlusMT_Above100);
 SaveResult(writefile, Result_WMinusMT_Above100);
 SaveResult(writefile, Result_WPlusHighMassMT);
 SaveResult(writefile, Result_WMinusHighMassMT);
 SaveResult(writefile, Result_WPlusHighMassMT_Integral);
 SaveResult(writefile, Result_WMinusHighMassMT_Integral);

 SaveResult(writefile, Result_E245);
 SaveResult(writefile, Result_E246);
 SaveResult(writefile, Result_E248);
 SaveResult(writefile, Result_E268);
 SaveResult(writefile, Result_E249);
 SaveResult(writefile, Result_E250);
 SaveResult(writefile, Result_E225);
 SaveResult(writefile, Result_E227);
 SaveResult(writefile, Result_E234);
 SaveResult(writefile, Result_E260);
 SaveResult(writefile, Result_E261);
 SaveResult(writefile, Result_E266);
 SaveResult(writefile, Result_E267);
 SaveResult(writefile, Result_E281);
 SaveResult(writefile, Result_E211);
 SaveResult(writefile, Result_E212);
 SaveResult(writefile, Result_E218);
 SaveResult(writefile, Result_E214);
 SaveResult(writefile, Result_E215);
 SaveResult(writefile, Result_E217);

}

