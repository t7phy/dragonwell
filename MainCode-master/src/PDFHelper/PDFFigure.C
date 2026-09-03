#include "PDFHelper/PDFFigure.h"

PDFFigure::PDFFigure(TString Option)
{
 this->Option = Option;

 LogBin = Logspace(1e-5, 0.9999, 1000, 10.0);

 DefineCombination();

 DefinePlottingStyle();
}

void PDFFigure::InitialPDF(TString PDFName, int iSet)
{
#ifdef USE_LHAPDF
 PDF[make_pair(PDFName, iSet)] = LHAPDF::mkPDF(PDFName.Data(), iSet);

 PDFType[PDFName] = "LHAPDF";

 PDFLegendName[PDFName] = PDFName;
#endif
}

void PDFFigure::InitialSingleLHAPDF(TString PDFName, int iSet)
{
#ifdef USE_LHAPDF
 PDF[make_pair(PDFName, 0)] = LHAPDF::mkPDF(PDFName.Data(), iSet);

 PDFType[PDFName] = "LHAPDF";

 PDFLegendName[PDFName] = PDFName;

 PDFnSet[PDFName] = 0;
#endif
}

void PDFFigure::InitialPDFAll(TString PDFName, int nSet)
{
#ifdef USE_LHAPDF
 for(int i = 0; i <= nSet; i++){
   PDF[make_pair(PDFName, i)] = LHAPDF::mkPDF(PDFName.Data(), i);
 }

 PDFType[PDFName] = "LHAPDF";

 PDFnSet[PDFName] = nSet;

 PDFLegendName[PDFName] = PDFName;
#endif
}

void PDFFigure::InitialPDFAll(TString PDFName)
{
#ifdef USE_LHAPDF 
 LHAPDF::PDFSet allpdfset(PDFName.Data());
 PDFnSet[PDFName] = allpdfset.size() - 1;

 for(int i = 0; i <= PDFnSet[PDFName]; i++){
   PDF[make_pair(PDFName, i)] = LHAPDF::mkPDF(PDFName.Data(), i);
 }
 
 PDFType[PDFName] = "LHAPDF";
 
 PDFLegendName[PDFName] = PDFName;
#endif
}

void PDFFigure::InitialCTEQPDF(TString GivenName, TString PDFFile, int iSet)
{
 cout<<PDFFile<<endl;

 CTPDF[make_pair(GivenName, iSet)] = new pdsReader();
 CTPDF[make_pair(GivenName, iSet)]->Initialize(PDFFile);

 PDFType[GivenName] = "CTEQ";

 PDFLegendName[GivenName] = GivenName;
}

void PDFFigure::InitialCTEQPDFAll(TString GivenName, vector<TString> PDFFiles)
{
 for(int i = 0; i < PDFFiles.size(); i++){
   InitialCTEQPDF(GivenName, PDFFiles.at(i), i);
 }

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = PDFFiles.size() - 1;

 PDFLegendName[GivenName] = GivenName;
}

void PDFFigure::InitialCTEQPDF(TString GivenName, pdsReader* pdf, int iSet)
{
 CTPDF[make_pair(GivenName, iSet)] = pdf;

 PDFType[GivenName] = "CTEQ";

 PDFLegendName[GivenName] = GivenName;
}

void PDFFigure::InitialCTEQPDFAll(TString GivenName, vector<pdsReader *> PDFFiles)
{
 for(int i = 0; i < PDFFiles.size(); i++){
   InitialCTEQPDF(GivenName, PDFFiles.at(i), i);
 }

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = PDFFiles.size() - 1;

 PDFLegendName[GivenName] = GivenName;
}

void PDFFigure::InitialCTEQPDFAll(TString GivenName, TString DirectoryName)
{
 DIR* PDFDir;

 struct dirent* ptr;

 if(!(PDFDir = opendir(DirectoryName.Data()))){
   cout<<"ERROR! Directory doesn't exist!"<<endl;
   return;
 }

 //set<TString> PDFFiles;
 vector<TString> PDFFiles;

 while((ptr = readdir(PDFDir)) != 0){
   if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
     TString PDFFile = DirectoryName + "/" + ptr->d_name;
     PDFFiles.push_back(PDFFile);
   }
 }

 sort(PDFFiles.begin(), PDFFiles.end());
 for(int i = 0; i < PDFFiles.size(); i++){
   InitialCTEQPDF(GivenName, PDFFiles.at(i), i);
 }

// int iSet = 0;
// for(auto iter = PDFFiles.begin(); iter != PDFFiles.end(); iter++){
//   InitialCTEQPDF(GivenName, *iter, iSet);
//   iSet++;
// }

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = PDFFiles.size() - 1;

 PDFLegendName[GivenName] = GivenName;

 cout<<"nSet for "<<GivenName<<" is "<<PDFnSet[GivenName]<<endl;
}

void PDFFigure::InitialSingleCTEQPDF(TString GivenName, TString PDFFile)
{
 cout<<PDFFile<<endl;
 
 CTPDF[make_pair(GivenName, 0)] = new pdsReader();
 CTPDF[make_pair(GivenName, 0)]->Initialize(PDFFile);
 
 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = 0;
 
 PDFLegendName[GivenName] = GivenName;
}

void PDFFigure::InitialSingleCTEQPDF(TString GivenName, pdsReader* pdf)
{
 CTPDF[make_pair(GivenName, 0)] = pdf;

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = 0;

 PDFLegendName[GivenName] = GivenName;
}

void PDFFigure::GenerateErrorAll(vector<TString> PDFNames, vector<TString> ErrorTypes, double Q)
{
 vector<double> FlavorList;

 if(Option == "Nes") FlavorList = FlavorListNes;
 if(Option == "All") FlavorList = FlavorListAll;

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(2)<<Q;

 Qstring = s_Qstring.str();

 if(PDFNames.size() == 1) LegendYmin = 0.8;

 for(int i = 0; i < PDFNames.size(); i++){
   PreparePDFPlotAll(PDFNames.at(i), Q);
   PreparePDFRatioAll(PDFNames.at(i), Q, PDFNames.at(0));
   PreparePDFError(PDFNames.at(i), Q, ErrorTypes.at(i));
 }

 for(int flavor = 0; flavor < FlavorList.size(); flavor++){
   TString PlotName;
   if(PDFNames.size() == 1) PlotName = PDFNames.at(0) + "_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   if(PDFNames.size() == 2) PlotName = PDFNames.at(0) + "_" + PDFNames.at(1) + "_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   if(PDFNames.size() == 3) PlotName = PDFNames.at(0) + "_" + PDFNames.at(1) + "_" + PDFNames.at(2) + "_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   if(PDFNames.size() == 4) PlotName = PDFNames.at(0) + "_" + PDFNames.at(1) + "_" + PDFNames.at(2) + "_" + PDFNames.at(3) + "_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   if(PDFNames.size() == 5) PlotName = PDFNames.at(0) + "_" + PDFNames.at(1) + "_" + PDFNames.at(2) + "_" + PDFNames.at(3) + "_" + PDFNames.at(4) + "_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;

   Graph* g;

   g = new Graph(PlotName, "x", TitleMap[FlavorList.at(flavor)]);
   if(PDFNames.size() >= 1){
     if(abs(FlavorList.at(flavor)) <= 7){
       g->Input(1, xPDFPlot[make_tuple(PDFNames.at(0), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(0)]);
       g->Input(2, xPDFErrorPlus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
       g->Input(3, xPDFErrorMinus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
       g->Input(4, xPDFErrorCentral[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     }
     else{
       g->Input(1, PDFPlot[make_tuple(PDFNames.at(0), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(0)]);
       g->Input(2, PDFErrorPlus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
       g->Input(3, PDFErrorMinus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
       g->Input(4, PDFErrorCentral[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     }
     g->SetCustomPad(1);
     if(PlotNoFill[1]) g->IgnoreCustomError(1, 1);
     g->CustomSetting(1, 1);
     g->CustomSetting(1, 2);
     g->CustomSetting(1, 3);
     g->CustomSetting(1, 4);
     g->SetCustomPlotFormat(1, 1, PlotFillColor[1]);
     g->SetCustomPlotFormat(1, 2, PlotLineColor[1]);
     g->SetCustomPlotFormat(1, 3, PlotLineColor[1]);
     g->SetCustomPlotFormat(1, 4, PlotLineColor[1]);
     g->SetCustomPlot(1, 1, "Fill");
     g->SetCustomPlot(1, 2, "L");
     g->SetCustomPlot(1, 3, "L");
     g->SetCustomPlot(1, 4, "L");
     g->SetCustomFillAlpha(1, 1, 0.2);
     g->SetCustomFillStyle(1, 1, 1001);
     g->SetCustomLineWidth(1, 2, 3);
     g->SetCustomLineWidth(1, 3, 3);
     g->SetCustomLineWidth(1, 4, 3);
     if(PlotNoFill[1]) g->SetCustomFillAlpha(1, 1, 0.0);
     if(PlotNoFill[1]) g->SetCustomPlot(1, 1, "L");
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 1, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 2, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 3, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 4, 2);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 1, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 2, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 3, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 4, PlotLineStyle[1]);
     //g->SetCustomYRange(1, 0.8, 1.2);
     g->SetXRange(1e-5, 1);
     g->SetLogX();
     if(abs(FlavorList.at(flavor)) <= 5){
       g->SetLogY();
     }
   }
   if(PDFNames.size() >= 2){
     if(abs(FlavorList.at(flavor)) <= 7){
       g->Input(5, xPDFPlot[make_tuple(PDFNames.at(1), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(1)]);
       g->Input(6, xPDFErrorPlus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
       g->Input(7, xPDFErrorMinus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
       g->Input(8, xPDFErrorCentral[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     }
     else{
       g->Input(5, PDFPlot[make_tuple(PDFNames.at(1), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(1)]);
       g->Input(6, PDFErrorPlus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
       g->Input(7, PDFErrorMinus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
       g->Input(8, PDFErrorCentral[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     }
     if(PlotNoFill[2]) g->IgnoreCustomError(1, 5);
     g->CustomSetting(1, 5);
     g->CustomSetting(1, 6);
     g->CustomSetting(1, 7);
     g->CustomSetting(1, 8);
     g->SetCustomPlotFormat(1, 5, PlotFillColor[2]);
     g->SetCustomPlotFormat(1, 6, PlotLineColor[2]);
     g->SetCustomPlotFormat(1, 7, PlotLineColor[2]);
     g->SetCustomPlotFormat(1, 8, PlotLineColor[2]);
     g->SetCustomPlot(1, 5, "Fill");
     g->SetCustomPlot(1, 6, "L");
     g->SetCustomPlot(1, 7, "L");
     g->SetCustomPlot(1, 8, "L");
     g->SetCustomFillAlpha(1, 5, 0.2);
     g->SetCustomFillStyle(1, 5, 1001);
     g->SetCustomLineWidth(1, 6, 3);
     g->SetCustomLineWidth(1, 7, 3);
     g->SetCustomLineWidth(1, 8, 3);
     if(PlotNoFill[2]) g->SetCustomFillAlpha(1, 5, 0.0);
     if(PlotNoFill[2]) g->SetCustomPlot(1, 5, "L");
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 5, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 6, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 7, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 8, 2);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 5, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 6, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 7, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 8, PlotLineStyle[2]);
   }
   if(PDFNames.size() >= 3){ 
     if(abs(FlavorList.at(flavor)) <= 7){
       g->Input(9, xPDFPlot[make_tuple(PDFNames.at(2), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(2)]);
       g->Input(10, xPDFErrorPlus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
       g->Input(11, xPDFErrorMinus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
       g->Input(12, xPDFErrorCentral[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     }
     else{
       g->Input(9, PDFPlot[make_tuple(PDFNames.at(2), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(2)]);
       g->Input(10, PDFErrorPlus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
       g->Input(11, PDFErrorMinus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
       g->Input(12, PDFErrorCentral[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     }
     if(PlotNoFill[3]) g->IgnoreCustomError(1, 9);
     g->CustomSetting(1, 9);
     g->CustomSetting(1, 10);
     g->CustomSetting(1, 11);
     g->CustomSetting(1, 12);
     g->SetCustomPlotFormat(1, 9, PlotFillColor[3]);
     g->SetCustomPlotFormat(1, 10, PlotLineColor[3]);
     g->SetCustomPlotFormat(1, 11, PlotLineColor[3]);
     g->SetCustomPlotFormat(1, 12, PlotLineColor[3]);
     g->SetCustomPlot(1, 9, "Fill");
     g->SetCustomPlot(1, 10, "L");
     g->SetCustomPlot(1, 11, "L");
     g->SetCustomPlot(1, 12, "L");
     g->SetCustomFillAlpha(1, 9, 0.2);
     g->SetCustomFillStyle(1, 9, 1001);
     g->SetCustomLineWidth(1, 10, 3);
     g->SetCustomLineWidth(1, 11, 3);
     g->SetCustomLineWidth(1, 12, 3);
     if(PlotNoFill[3]) g->SetCustomFillAlpha(1, 9, 0.0);
     if(PlotNoFill[3]) g->SetCustomPlot(1, 9, "L");
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 9, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 10, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 11, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 12, 2);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 9, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 10, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 11, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 12, PlotLineStyle[3]);
   }
   if(PDFNames.size() >= 4){
     if(abs(FlavorList.at(flavor)) <= 7){
       g->Input(13, xPDFPlot[make_tuple(PDFNames.at(3), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(3)]);
       g->Input(14, xPDFErrorPlus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
       g->Input(15, xPDFErrorMinus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
       g->Input(16, xPDFErrorCentral[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     }
     else{
       g->Input(13, PDFPlot[make_tuple(PDFNames.at(3), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(3)]);
       g->Input(14, PDFErrorPlus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
       g->Input(15, PDFErrorMinus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
       g->Input(16, PDFErrorCentral[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     }
     if(PlotNoFill[4]) g->IgnoreCustomError(1, 13);
     g->CustomSetting(1, 13);
     g->CustomSetting(1, 14);
     g->CustomSetting(1, 15);
     g->CustomSetting(1, 16);
     g->SetCustomPlotFormat(1, 13, PlotFillColor[4]);
     g->SetCustomPlotFormat(1, 14, PlotLineColor[4]);
     g->SetCustomPlotFormat(1, 15, PlotLineColor[4]);
     g->SetCustomPlotFormat(1, 16, PlotLineColor[4]);
     g->SetCustomPlot(1, 13, "Fill");
     g->SetCustomPlot(1, 14, "L");
     g->SetCustomPlot(1, 15, "L");
     g->SetCustomPlot(1, 16, "L");
     g->SetCustomFillAlpha(1, 13, 0.2);
     g->SetCustomFillStyle(1, 13, 1001);
     g->SetCustomLineWidth(1, 14, 3);
     g->SetCustomLineWidth(1, 15, 3);
     g->SetCustomLineWidth(1, 16, 3);
     if(PlotNoFill[4]) g->SetCustomFillAlpha(1, 13, 0.0);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 13, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 14, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 15, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 16, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlot(1, 13, "L");
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 13, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 14, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 15, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 16, 2);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 13, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 14, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 15, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 16, PlotLineStyle[4]);
   }
   if(PDFNames.size() >= 5){
     if(abs(FlavorList.at(flavor)) <= 7){
       g->Input(17, xPDFPlot[make_tuple(PDFNames.at(4), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(4)]);
       g->Input(18, xPDFErrorPlus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
       g->Input(19, xPDFErrorMinus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
       g->Input(20, xPDFErrorCentral[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     }
     else{
       g->Input(17, PDFPlot[make_tuple(PDFNames.at(4), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(4)]);
       g->Input(18, PDFErrorPlus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
       g->Input(19, PDFErrorMinus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
       g->Input(20, PDFErrorCentral[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     }
     if(PlotNoFill[5]) g->IgnoreCustomError(1, 17);
     g->CustomSetting(1, 17);
     g->CustomSetting(1, 18);
     g->CustomSetting(1, 19);
     g->CustomSetting(1, 20);
     g->SetCustomPlotFormat(1, 17, PlotFillColor[5]);
     g->SetCustomPlotFormat(1, 18, PlotLineColor[5]);
     g->SetCustomPlotFormat(1, 19, PlotLineColor[5]);
     g->SetCustomPlotFormat(1, 20, PlotLineColor[5]);
     g->SetCustomPlot(1, 17, "Fill");
     g->SetCustomPlot(1, 18, "L");
     g->SetCustomPlot(1, 19, "L");
     g->SetCustomPlot(1, 20, "L");
     g->SetCustomFillAlpha(1, 17, 0.2);
     g->SetCustomFillStyle(1, 17, 1001);
     g->SetCustomLineWidth(1, 18, 3);
     g->SetCustomLineWidth(1, 19, 3);
     g->SetCustomLineWidth(1, 20, 3);
     if(PlotNoFill[5]) g->SetCustomFillAlpha(1, 17, 0.0);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 17, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 18, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 19, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 20, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlot(1, 17, "L");
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 17, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 18, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 19, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 20, 2);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 17, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 18, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 19, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 20, PlotLineStyle[5]);
   }

   g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
   g->SetTextLeftBias(TextLeftBias);
   g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
   g->Draw();
   delete g;

   PlotName.ReplaceAll("PDFPlot", "PDFRatio");
   g = new Graph(PlotName, "x", "PDF Ratio to " + PDFLegendName[PDFNames.at(0)]);
   if(PDFNames.size() >= 1){
     g->Input(1, PDFRatio[make_tuple(PDFNames.at(0), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(0)]);
     g->Input(2, PDFRatioErrorPlus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     g->Input(3, PDFRatioErrorMinus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     g->Input(4, PDFRatioErrorCentral[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     g->SetCustomPad(1);
     if(PlotNoFill[1]) g->IgnoreCustomError(1, 1);
     g->CustomSetting(1, 1);
     g->CustomSetting(1, 2);
     g->CustomSetting(1, 3);
     g->CustomSetting(1, 4);
     g->SetCustomPlotFormat(1, 1, PlotFillColor[1]);
     g->SetCustomPlotFormat(1, 2, PlotLineColor[1]);
     g->SetCustomPlotFormat(1, 3, PlotLineColor[1]);
     g->SetCustomPlotFormat(1, 4, PlotLineColor[1]);
     g->SetCustomPlot(1, 1, "Fill");
     g->SetCustomPlot(1, 2, "L");
     g->SetCustomPlot(1, 3, "L");
     g->SetCustomPlot(1, 4, "L");
     g->SetCustomFillAlpha(1, 1, 0.2);
     g->SetCustomFillStyle(1, 1, 1001);
     g->SetCustomLineWidth(1, 2, 3);
     g->SetCustomLineWidth(1, 3, 3);
     g->SetCustomLineWidth(1, 4, 3);
     if(PlotNoFill[1]) g->SetCustomFillAlpha(1, 1, 0.0);
     if(PlotNoFill[1]) g->SetCustomPlot(1, 1, "L");
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 1, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 2, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 3, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 4, 2);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 1, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 2, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 3, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 4, PlotLineStyle[1]);
     g->SetCustomYRange(1, PlotYMin[FlavorList.at(flavor)], PlotYMax[FlavorList.at(flavor)]);
     g->SetXRange(1e-5, 1);
     g->SetLogX();
   }
   if(PDFNames.size() >= 2){
     g->Input(5, PDFRatio[make_tuple(PDFNames.at(1), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(1)]);
     g->Input(6, PDFRatioErrorPlus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     g->Input(7, PDFRatioErrorMinus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     g->Input(8, PDFRatioErrorCentral[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[2]) g->IgnoreCustomError(1, 5);
     g->CustomSetting(1, 5);
     g->CustomSetting(1, 6);
     g->CustomSetting(1, 7);
     g->CustomSetting(1, 8);
     g->SetCustomPlotFormat(1, 5, PlotFillColor[2]);
     g->SetCustomPlotFormat(1, 6, PlotLineColor[2]);
     g->SetCustomPlotFormat(1, 7, PlotLineColor[2]);
     g->SetCustomPlotFormat(1, 8, PlotLineColor[2]);
     g->SetCustomPlot(1, 5, "Fill");
     g->SetCustomPlot(1, 6, "L");
     g->SetCustomPlot(1, 7, "L");
     g->SetCustomPlot(1, 8, "L");
     g->SetCustomFillAlpha(1, 5, 0.2);
     g->SetCustomFillStyle(1, 5, 1001);
     g->SetCustomLineWidth(1, 6, 3);
     g->SetCustomLineWidth(1, 7, 3);
     g->SetCustomLineWidth(1, 8, 3);
     if(PlotNoFill[2]) g->SetCustomFillAlpha(1, 5, 0.0);
     if(PlotNoFill[2]) g->SetCustomPlot(1, 5, "L");
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 5, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 6, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 7, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 8, 2);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 5, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 6, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 7, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 8, PlotLineStyle[2]);
   }
   if(PDFNames.size() >= 3){ 
     g->Input(9, PDFRatio[make_tuple(PDFNames.at(2), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(2)]);
     g->Input(10, PDFRatioErrorPlus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     g->Input(11, PDFRatioErrorMinus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     g->Input(12, PDFRatioErrorCentral[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[3]) g->IgnoreCustomError(1, 9);
     g->CustomSetting(1, 9);
     g->CustomSetting(1, 10);
     g->CustomSetting(1, 11);
     g->CustomSetting(1, 12);
     g->SetCustomPlotFormat(1, 9, PlotFillColor[3]);
     g->SetCustomPlotFormat(1, 10, PlotLineColor[3]);
     g->SetCustomPlotFormat(1, 11, PlotLineColor[3]);
     g->SetCustomPlotFormat(1, 12, PlotLineColor[3]);
     g->SetCustomPlot(1, 9, "Fill");
     g->SetCustomPlot(1, 10, "L");
     g->SetCustomPlot(1, 11, "L");
     g->SetCustomPlot(1, 12, "L");
     g->SetCustomFillAlpha(1, 9, 0.2);
     g->SetCustomFillStyle(1, 9, 1001);
     g->SetCustomLineWidth(1, 10, 3);
     g->SetCustomLineWidth(1, 11, 3);
     g->SetCustomLineWidth(1, 12, 3);
     if(PlotNoFill[3]) g->SetCustomFillAlpha(1, 9, 0.0);
     if(PlotNoFill[3]) g->SetCustomPlot(1, 9, "L");
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 9, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 10, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 11, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 12, 2);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 9, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 10, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 11, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 12, PlotLineStyle[3]);
   }
   if(PDFNames.size() >= 4){
     g->Input(13, PDFRatio[make_tuple(PDFNames.at(3), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(3)]);
     g->Input(14, PDFRatioErrorPlus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     g->Input(15, PDFRatioErrorMinus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     g->Input(16, PDFRatioErrorCentral[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[4]) g->IgnoreCustomError(1, 13);
     g->CustomSetting(1, 13);
     g->CustomSetting(1, 14);
     g->CustomSetting(1, 15);
     g->CustomSetting(1, 16);
     g->SetCustomPlotFormat(1, 13, PlotFillColor[4]);
     g->SetCustomPlotFormat(1, 14, PlotLineColor[4]);
     g->SetCustomPlotFormat(1, 15, PlotLineColor[4]);
     g->SetCustomPlotFormat(1, 16, PlotLineColor[4]);
     g->SetCustomPlot(1, 13, "Fill");
     g->SetCustomPlot(1, 14, "L");
     g->SetCustomPlot(1, 15, "L");
     g->SetCustomPlot(1, 16, "L");
     g->SetCustomFillAlpha(1, 13, 0.2);
     g->SetCustomFillStyle(1, 13, 1001);
     g->SetCustomLineWidth(1, 14, 3);
     g->SetCustomLineWidth(1, 15, 3);
     g->SetCustomLineWidth(1, 16, 3);
     if(PlotNoFill[4]) g->SetCustomFillAlpha(1, 13, 0.0);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 13, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 14, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 15, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 16, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlot(1, 13, "L");
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 13, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 14, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 15, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 16, 2);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 13, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 14, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 15, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 16, PlotLineStyle[4]);
   }
   if(PDFNames.size() >= 5){
     g->Input(17, PDFRatio[make_tuple(PDFNames.at(4), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(4)]);
     g->Input(18, PDFRatioErrorPlus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     g->Input(19, PDFRatioErrorMinus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     g->Input(20, PDFRatioErrorCentral[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[5]) g->IgnoreCustomError(1, 17);
     g->CustomSetting(1, 17);
     g->CustomSetting(1, 18);
     g->CustomSetting(1, 19);
     g->CustomSetting(1, 20);
     g->SetCustomPlotFormat(1, 17, PlotFillColor[5]);
     g->SetCustomPlotFormat(1, 18, PlotLineColor[5]);
     g->SetCustomPlotFormat(1, 19, PlotLineColor[5]);
     g->SetCustomPlotFormat(1, 20, PlotLineColor[5]);
     g->SetCustomPlot(1, 17, "Fill");
     g->SetCustomPlot(1, 18, "L");
     g->SetCustomPlot(1, 19, "L");
     g->SetCustomPlot(1, 20, "L");
     g->SetCustomFillAlpha(1, 17, 0.2);
     g->SetCustomFillStyle(1, 17, 1001);
     g->SetCustomLineWidth(1, 18, 3);
     g->SetCustomLineWidth(1, 19, 3);
     g->SetCustomLineWidth(1, 20, 3);
     if(PlotNoFill[5]) g->SetCustomFillAlpha(1, 17, 0.0);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 17, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 18, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 19, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 20, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlot(1, 17, "L");
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 17, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 18, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 19, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 20, 2);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 17, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 18, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 19, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 20, PlotLineStyle[5]);
   }

   g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
   g->SetTextLeftBias(TextLeftBias);
   g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
   g->Draw();
   delete g;

   PlotName.ReplaceAll("PDFRatio", "PDFRatioSelf");
   g = new Graph(PlotName, "x", "PDF Ratio");
   if(PDFNames.size() >= 1){
     g->Input(1, PDFRatioSelf[make_tuple(PDFNames.at(0), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(0)]);
     g->Input(2, PDFRatioSelfErrorPlus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     g->Input(3, PDFRatioSelfErrorMinus[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     g->Input(4, PDFRatioSelfErrorCentral[make_tuple(PDFNames.at(0), FlavorList.at(flavor), Q)], "");
     g->SetCustomPad(1);
     if(PlotNoFill[1]) g->IgnoreCustomError(1, 1);
     g->CustomSetting(1, 1);
     g->CustomSetting(1, 2);
     g->CustomSetting(1, 3);
     g->CustomSetting(1, 4);
     g->SetCustomPlotFormat(1, 1, PlotFillColor[1]);
     g->SetCustomPlotFormat(1, 2, PlotLineColor[1]);
     g->SetCustomPlotFormat(1, 3, PlotLineColor[1]);
     g->SetCustomPlotFormat(1, 4, PlotLineColor[1]);
     g->SetCustomPlot(1, 1, "Fill");
     g->SetCustomPlot(1, 2, "L");
     g->SetCustomPlot(1, 3, "L");
     g->SetCustomPlot(1, 4, "L");
     g->SetCustomFillAlpha(1, 1, 0.2);
     g->SetCustomFillStyle(1, 1, 1001);
     g->SetCustomLineWidth(1, 2, 3);
     g->SetCustomLineWidth(1, 3, 3);
     g->SetCustomLineWidth(1, 4, 3);
     if(PlotNoFill[1]) g->SetCustomFillAlpha(1, 1, 0.0);
     if(PlotNoFill[1]) g->SetCustomPlot(1, 1, "L");
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 1, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 2, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 3, 2);
     if(PlotNoFill[1]) g->SetCustomLineWidth(1, 4, 2);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 1, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 2, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 3, PlotLineStyle[1]);
     if(PlotNoFill[1]) g->SetCustomLineStyle(1, 4, PlotLineStyle[1]);
     g->SetCustomYRange(1, PlotYMin[FlavorList.at(flavor)], PlotYMax[FlavorList.at(flavor)]);
     g->SetXRange(1e-5, 1);
     g->SetLogX();
   }
   if(PDFNames.size() >= 2){
     g->Input(5, PDFRatioSelf[make_tuple(PDFNames.at(1), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(1)]);
     g->Input(6, PDFRatioSelfErrorPlus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     g->Input(7, PDFRatioSelfErrorMinus[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     g->Input(8, PDFRatioSelfErrorCentral[make_tuple(PDFNames.at(1), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[2]) g->IgnoreCustomError(1, 5);
     g->CustomSetting(1, 5);
     g->CustomSetting(1, 6);
     g->CustomSetting(1, 7);
     g->CustomSetting(1, 8);
     g->SetCustomPlotFormat(1, 5, PlotFillColor[2]);
     g->SetCustomPlotFormat(1, 6, PlotLineColor[2]);
     g->SetCustomPlotFormat(1, 7, PlotLineColor[2]);
     g->SetCustomPlotFormat(1, 8, PlotLineColor[2]);
     g->SetCustomPlot(1, 5, "Fill");
     g->SetCustomPlot(1, 6, "L");
     g->SetCustomPlot(1, 7, "L");
     g->SetCustomPlot(1, 8, "L");
     g->SetCustomFillAlpha(1, 5, 0.2);
     g->SetCustomFillStyle(1, 5, 1001);
     g->SetCustomLineWidth(1, 6, 3);
     g->SetCustomLineWidth(1, 7, 3);
     g->SetCustomLineWidth(1, 8, 3);
     if(PlotNoFill[2]) g->SetCustomFillAlpha(1, 5, 0.0);
     if(PlotNoFill[2]) g->SetCustomPlot(1, 5, "L");
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 5, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 6, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 7, 2);
     if(PlotNoFill[2]) g->SetCustomLineWidth(1, 8, 2);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 5, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 6, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 7, PlotLineStyle[2]);
     if(PlotNoFill[2]) g->SetCustomLineStyle(1, 8, PlotLineStyle[2]);
   }
   if(PDFNames.size() >= 3){ 
     g->Input(9, PDFRatioSelf[make_tuple(PDFNames.at(2), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(2)]);
     g->Input(10, PDFRatioSelfErrorPlus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     g->Input(11, PDFRatioSelfErrorMinus[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     g->Input(12, PDFRatioSelfErrorCentral[make_tuple(PDFNames.at(2), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[3]) g->IgnoreCustomError(1, 9);
     g->CustomSetting(1, 9);
     g->CustomSetting(1, 10);
     g->CustomSetting(1, 11);
     g->CustomSetting(1, 12);
     g->SetCustomPlotFormat(1, 9, PlotFillColor[3]);
     g->SetCustomPlotFormat(1, 10, PlotLineColor[3]);
     g->SetCustomPlotFormat(1, 11, PlotLineColor[3]);
     g->SetCustomPlotFormat(1, 12, PlotLineColor[3]);
     g->SetCustomPlot(1, 9, "Fill");
     g->SetCustomPlot(1, 10, "L");
     g->SetCustomPlot(1, 11, "L");
     g->SetCustomPlot(1, 12, "L");
     g->SetCustomFillAlpha(1, 9, 0.2);
     g->SetCustomFillStyle(1, 9, 1001);
     g->SetCustomLineWidth(1, 10, 3);
     g->SetCustomLineWidth(1, 11, 3);
     g->SetCustomLineWidth(1, 12, 3);
     if(PlotNoFill[3]) g->SetCustomFillAlpha(1, 9, 0.0);
     if(PlotNoFill[3]) g->SetCustomPlot(1, 9, "L");
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 9, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 10, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 11, 2);
     if(PlotNoFill[3]) g->SetCustomLineWidth(1, 12, 2);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 9, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 10, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 11, PlotLineStyle[3]);
     if(PlotNoFill[3]) g->SetCustomLineStyle(1, 12, PlotLineStyle[3]);
   }
   if(PDFNames.size() >= 4){
     g->Input(13, PDFRatioSelf[make_tuple(PDFNames.at(3), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(3)]);
     g->Input(14, PDFRatioSelfErrorPlus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     g->Input(15, PDFRatioSelfErrorMinus[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     g->Input(16, PDFRatioSelfErrorCentral[make_tuple(PDFNames.at(3), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[4]) g->IgnoreCustomError(1, 13);
     g->CustomSetting(1, 13);
     g->CustomSetting(1, 14);
     g->CustomSetting(1, 15);
     g->CustomSetting(1, 16);
     g->SetCustomPlotFormat(1, 13, PlotFillColor[4]);
     g->SetCustomPlotFormat(1, 14, PlotLineColor[4]);
     g->SetCustomPlotFormat(1, 15, PlotLineColor[4]);
     g->SetCustomPlotFormat(1, 16, PlotLineColor[4]);
     g->SetCustomPlot(1, 13, "Fill");
     g->SetCustomPlot(1, 14, "L");
     g->SetCustomPlot(1, 15, "L");
     g->SetCustomPlot(1, 16, "L");
     g->SetCustomFillAlpha(1, 13, 0.2);
     g->SetCustomFillStyle(1, 13, 1001);
     g->SetCustomLineWidth(1, 14, 3);
     g->SetCustomLineWidth(1, 15, 3);
     g->SetCustomLineWidth(1, 16, 3);
     if(PlotNoFill[4]) g->SetCustomFillAlpha(1, 13, 0.0);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 13, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 14, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 15, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlotFormat(1, 16, kBlue + 3);
     if(PlotNoFill[4]) g->SetCustomPlot(1, 13, "L");
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 13, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 14, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 15, 2);
     if(PlotNoFill[4]) g->SetCustomLineWidth(1, 16, 2);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 13, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 14, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 15, PlotLineStyle[4]);
     if(PlotNoFill[4]) g->SetCustomLineStyle(1, 16, PlotLineStyle[4]);
   }
   if(PDFNames.size() >= 5){
     g->Input(17, PDFRatioSelf[make_tuple(PDFNames.at(4), 0, FlavorList.at(flavor), Q)], PDFLegendName[PDFNames.at(4)]);
     g->Input(18, PDFRatioSelfErrorPlus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     g->Input(19, PDFRatioSelfErrorMinus[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     g->Input(20, PDFRatioSelfErrorCentral[make_tuple(PDFNames.at(4), FlavorList.at(flavor), Q)], "");
     if(PlotNoFill[5]) g->IgnoreCustomError(1, 17);
     g->CustomSetting(1, 17);
     g->CustomSetting(1, 18);
     g->CustomSetting(1, 19);
     g->CustomSetting(1, 20);
     g->SetCustomPlotFormat(1, 17, PlotFillColor[5]);
     g->SetCustomPlotFormat(1, 18, PlotLineColor[5]);
     g->SetCustomPlotFormat(1, 19, PlotLineColor[5]);
     g->SetCustomPlotFormat(1, 20, PlotLineColor[5]);
     g->SetCustomPlot(1, 17, "Fill");
     g->SetCustomPlot(1, 18, "L");
     g->SetCustomPlot(1, 19, "L");
     g->SetCustomPlot(1, 20, "L");
     g->SetCustomFillAlpha(1, 17, 0.2);
     g->SetCustomFillStyle(1, 17, 1001);
     g->SetCustomLineWidth(1, 18, 3);
     g->SetCustomLineWidth(1, 19, 3);
     g->SetCustomLineWidth(1, 20, 3);
     if(PlotNoFill[5]) g->SetCustomFillAlpha(1, 17, 0.0);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 17, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 18, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 19, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlotFormat(1, 20, kRed + 3);
     if(PlotNoFill[5]) g->SetCustomPlot(1, 17, "L");
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 17, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 18, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 19, 2);
     if(PlotNoFill[5]) g->SetCustomLineWidth(1, 20, 2);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 17, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 18, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 19, PlotLineStyle[5]);
     if(PlotNoFill[5]) g->SetCustomLineStyle(1, 20, PlotLineStyle[5]);
   }

   g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
   g->SetTextLeftBias(TextLeftBias);
   g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
   g->Draw();
   delete g;

 }
}

void PDFFigure::GenerateEigenAll(TString ErrorPDFName, TString EigenPDFName, TString ErrorType, double Q, int nEigenSet)
{
 vector<double> FlavorList;

 if(Option == "Nes") FlavorList = FlavorListNes;
 if(Option == "All") FlavorList = FlavorListAll;

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(2)<<Q;

 Qstring = s_Qstring.str();

 PreparePDFPlotAll(ErrorPDFName, Q);
 PreparePDFRatioAll(ErrorPDFName, Q, ErrorPDFName);
 PreparePDFError(ErrorPDFName, Q, ErrorType);

 if(ErrorPDFName != EigenPDFName){
   PreparePDFPlotAll(EigenPDFName, Q);
   for(int i = 0; i <= 2 * nEigenSet; i++){
     PreparePDFRatio(EigenPDFName, i, Q, ErrorPDFName);
   }
 }

 for(int flavor = 0; flavor < FlavorList.size(); flavor++){
   TString PlotName;
   if(nEigenSet == 1) PlotName = ErrorPDFName + "_" + EigenPDFName + "_Eigen1_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   if(nEigenSet == 2) PlotName = ErrorPDFName + "_" + EigenPDFName + "_Eigen1_Eigen2_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   if(nEigenSet == 3) PlotName = ErrorPDFName + "_" + EigenPDFName + "_Eigen1_Eigen2_Eigen3" + "_Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;

   Graph* g;

   g = new Graph(PlotName, "x", "PDF Ratio to " + PDFLegendName[ErrorPDFName]);
   g->Input(1, PDFRatioSelf[make_tuple(ErrorPDFName, 0, FlavorList.at(flavor), Q)], PDFLegendName[ErrorPDFName]);
   g->Input(2, PDFRatioSelfErrorPlus[make_tuple(ErrorPDFName, FlavorList.at(flavor), Q)], "");
   g->Input(3, PDFRatioSelfErrorMinus[make_tuple(ErrorPDFName, FlavorList.at(flavor), Q)], "");
   g->Input(4, PDFRatioSelfErrorCentral[make_tuple(ErrorPDFName, FlavorList.at(flavor), Q)], "");
   g->SetCustomPad(1);
   g->CustomSetting(1, 1);
   g->CustomSetting(1, 2);
   g->CustomSetting(1, 3);
   g->CustomSetting(1, 4);
   g->SetCustomPlotFormat(1, 1, PlotFillColor[1]);
   g->SetCustomPlotFormat(1, 2, PlotLineColor[1]);
   g->SetCustomPlotFormat(1, 3, PlotLineColor[1]);
   g->SetCustomPlotFormat(1, 4, PlotLineColor[1]);
   g->SetCustomPlot(1, 1, "Fill");
   g->SetCustomPlot(1, 2, "L");
   g->SetCustomPlot(1, 3, "L");
   g->SetCustomPlot(1, 4, "L");
   g->SetCustomFillAlpha(1, 1, 0.5);
   g->SetCustomYRange(1, PlotYMin[FlavorList.at(flavor)], PlotYMax[FlavorList.at(flavor)]);
   g->SetXRange(1e-5, 1);
   g->SetLogX();
   //g->SetLogY();

   for(int iEigen = 1; iEigen <= nEigenSet; iEigen++){
     char num[3];
     sprintf(num, "%02d", iEigen);

     if(nEigenSet == 1){
       if(ErrorType == "Symmetry") g->Input(4 + 2 * iEigen - 1, PDFRatio68CL[make_tuple(EigenPDFName, 2 * iEigen - 1, FlavorList.at(flavor), Q)], "PositiveDirection");
       if(ErrorType == "Symmetry68") g->Input(4 + 2 * iEigen - 1, PDFRatio[make_tuple(EigenPDFName, 2 * iEigen - 1, FlavorList.at(flavor), Q)], "PositiveDirection");
       if(ErrorType == "Symmetry") g->Input(4 + 2 * iEigen, PDFRatio68CL[make_tuple(EigenPDFName, 2 * iEigen, FlavorList.at(flavor), Q)], "NegativeDirection");
       if(ErrorType == "Symmetry68") g->Input(4 + 2 * iEigen, PDFRatio[make_tuple(EigenPDFName, 2 * iEigen, FlavorList.at(flavor), Q)], "NegativeDirection");
     }
     else{
       if(ErrorType == "Symmetry") g->Input(4 + 2 * iEigen - 1, PDFRatio68CL[make_tuple(EigenPDFName, 2 * iEigen - 1, FlavorList.at(flavor), Q)], (TString)"EV" + num);
       if(ErrorType == "Symmetry68") g->Input(4 + 2 * iEigen - 1, PDFRatio[make_tuple(EigenPDFName, 2 * iEigen - 1, FlavorList.at(flavor), Q)], (TString)"EV" + num);
       if(ErrorType == "Symmetry") g->Input(4 + 2 * iEigen, PDFRatio68CL[make_tuple(EigenPDFName, 2 * iEigen, FlavorList.at(flavor), Q)], "");
       if(ErrorType == "Symmetry68") g->Input(4 + 2 * iEigen, PDFRatio[make_tuple(EigenPDFName, 2 * iEigen, FlavorList.at(flavor), Q)], "");
     }
     g->CustomSetting(1, 4 + 2 * iEigen - 1);
     g->CustomSetting(1, 4 + 2 * iEigen);
     g->SetCustomPlotFormat(1, 4 + 2 * iEigen - 1, EigenLineColor[2 * iEigen - 1]);
     g->SetCustomPlotFormat(1, 4 + 2 * iEigen, EigenLineColor[2 * iEigen]);
     g->SetCustomPlot(1, 4 + 2 * iEigen - 1, "L");
     g->SetCustomPlot(1, 4 + 2 * iEigen, "L");
     g->SetCustomLineWidth(1, 4 + 2 * iEigen - 1, 2);
     g->SetCustomLineWidth(1, 4 + 2 * iEigen, 2);
     g->SetCustomLineStyle(1, 4 + 2 * iEigen - 1, EigenLineStyle[2 * iEigen - 1]);
     g->SetCustomLineStyle(1, 4 + 2 * iEigen, EigenLineStyle[2 * iEigen]);
   }

   g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
   g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
   g->Draw();
   delete g;
 }

}

void PDFFigure::GeneratexPDF(TString PDFName, TString ErrorType, vector<TString> FlavorType, double Q)
{
 vector<double> FlavorList(FlavorType.size());

 for(int i = 0; i < FlavorType.size(); i++){
   FlavorList.at(i) = FlavorNameIndex[FlavorType.at(i)];
 }

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(0)<<Q;

 Qstring = s_Qstring.str();

 PreparePDFPlotAll(PDFName, Q);
 PreparePDFRatioAll(PDFName, Q, PDFName);
 PreparePDFError(PDFName, Q, ErrorType);

 TString PlotName;
 PlotName = PDFName + "_Q" + Qstring + "_xPDFPlot" + saveMode;

 map<int, Color_t> FlavorColor;
 FlavorColor[0] = kGreen;
 FlavorColor[1] = kBlack;
 FlavorColor[2] = kBlue+1;
 FlavorColor[3] = kRed;
 FlavorColor[4] = kMagenta;
 FlavorColor[5] = kCyan+1;
 FlavorColor[6] = kYellow;
 FlavorColor[7] = kOrange;

 Graph* g;

 g = new Graph(PlotName, "x", "x*f(x,Q)");

 for(int flavor = 0; flavor < FlavorList.size(); flavor++){
   g->Input(flavor * 4 + 1, xPDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)], "");
   g->Input(flavor * 4 + 2, xPDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)], "");
   g->Input(flavor * 4 + 3, xPDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)], "");
   g->Input(flavor * 4 + 4, xPDFErrorCentral[make_tuple(PDFName, FlavorList.at(flavor), Q)], TitleMap[FlavorList.at(flavor)]);
   g->SetCustomPad(1);
   g->CustomSetting(1, flavor * 4 + 1);
   g->CustomSetting(1, flavor * 4 + 2);
   g->CustomSetting(1, flavor * 4 + 3);
   g->CustomSetting(1, flavor * 4 + 4);
   g->SetCustomPlotFormat(1, flavor * 4 + 1, FlavorColor[flavor]);
   g->SetCustomPlotFormat(1, flavor * 4 + 2, FlavorColor[flavor]);
   g->SetCustomPlotFormat(1, flavor * 4 + 3, FlavorColor[flavor]);
   g->SetCustomPlotFormat(1, flavor * 4 + 4, FlavorColor[flavor]);
   g->SetCustomPlot(1, flavor * 4 + 1, "FillL");
   g->SetCustomPlot(1, flavor * 4 + 2, "L");
   g->SetCustomPlot(1, flavor * 4 + 3, "L");
   g->SetCustomPlot(1, flavor * 4 + 4, "L");
   g->SetCustomLineWidth(1, flavor * 4 + 1, 2);
   g->SetCustomLineWidth(1, flavor * 4 + 2, 2);
   g->SetCustomLineWidth(1, flavor * 4 + 3, 2);
   g->SetCustomLineWidth(1, flavor * 4 + 4, 2);
   g->SetCustomFillStyle(1, flavor * 4 + 1, 1001);
   g->SetCustomFillAlpha(1, flavor * 4 + 1, 0.5);
   g->SetCustomYRange(1, 0.0, 1.0);
   g->SetXRange(1e-5, 1);
   g->SetLogX();
 }
 g->SetLegendPosition(0.85, 0.55, 0.99, 0.95);
 g->SetTextRightAlign();
 g->AddText(1, PDFLegendName[PDFName] + (TString)" at Q = " + Qstring + " GeV");
 g->SetXRange(1e-3, 1);
 g->Draw();
 delete g;

}

void PDFFigure::GenerateSinglePDFAll(vector<TString> ErrorPDFNames, vector<TString> SinglePDFNames, double Q)
{
 TString ErrorType = "Symmetry";

 vector<double> FlavorList;

 if(Option == "Nes") FlavorList = FlavorListNes;
 if(Option == "All") FlavorList = FlavorListAll;

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(1)<<Q;

 Qstring = s_Qstring.str();

 nErrorPDF = ErrorPDFNames.size();
 for(int i = 0; i < ErrorPDFNames.size(); i++){
   PreparePDFPlotAll(ErrorPDFNames.at(i), Q);
   PreparePDFRatioAll(ErrorPDFNames.at(i), Q, ErrorPDFNames.at(0));
   PreparePDFError(ErrorPDFNames.at(i), Q, ErrorType);
 }

 for(int i = 0; i < SinglePDFNames.size(); i++){
   PreparePDFPlotAll(SinglePDFNames.at(i), Q);
   if(ErrorPDFNames.size() != 0) PreparePDFRatioAll(SinglePDFNames.at(i), Q, ErrorPDFNames.at(0));
   else PreparePDFRatioAll(SinglePDFNames.at(i), Q, SinglePDFNames.at(0));
 }

 Graph* g;

 for(int flavor = 0; flavor < FlavorList.size(); flavor++){
   TString PlotName = "";

   for(int ipdf = 0; ipdf < ErrorPDFNames.size(); ipdf++){
     PlotName = PlotName + ErrorPDFNames.at(ipdf) + "_";
   }
   for(int ipdf = 0; ipdf < SinglePDFNames.size(); ipdf++){
     TString SinglePDFName = SinglePDFNames.at(ipdf);
     SinglePDFName.ReplaceAll(" ", "_");

     PlotName = PlotName + SinglePDFName + "_";
   }
   PlotName = PlotName + "Q" + Qstring + "_" + FlavorNameMap[FlavorList.at(flavor)] + "_PDFPlot" + saveMode;
   PlotNames.push_back(PlotName);

   g = new Graph(PlotName, "x", "x*f(x,Q)");
   g->SetCustomPad(1);

   for(int i = 0; i < ErrorPDFNames.size(); i++){
     if(abs(FlavorList.at(flavor)) <= 8){
       g->Input(i * 4 + 1, xPDFPlot[make_tuple(ErrorPDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[ErrorPDFNames.at(i)]);
       g->Input(i * 4 + 2, xPDFErrorPlus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
       g->Input(i * 4 + 3, xPDFErrorMinus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
       g->Input(i * 4 + 4, xPDFErrorCentral[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
     }
     else{
       g->Input(i * 4 + 1, PDFPlot[make_tuple(ErrorPDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[ErrorPDFNames.at(i)]);
       g->Input(i * 4 + 2, PDFErrorPlus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
       g->Input(i * 4 + 3, PDFErrorMinus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
       g->Input(i * 4 + 4, PDFErrorCentral[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
     }
     g->SetCustomPad(1);
     if(PlotNoFill[i + 1]) g->IgnoreCustomError(1, i * 4 + 1);
     g->CustomSetting(1, i * 4 + 1);
     g->CustomSetting(1, i * 4 + 2);
     g->CustomSetting(1, i * 4 + 3);
     g->CustomSetting(1, i * 4 + 4);
     g->SetCustomPlotFormat(1, i * 4 + 1, PlotFillColor[i + 1]);
     g->SetCustomPlotFormat(1, i * 4 + 2, PlotLineColor[i + 1]);
     g->SetCustomPlotFormat(1, i * 4 + 3, PlotLineColor[i + 1]);
     g->SetCustomPlotFormat(1, i * 4 + 4, PlotLineColor[i + 1]);
     g->SetCustomPlot(1, i * 4 + 1, "Fill");
     g->SetCustomPlot(1, i * 4 + 2, "L");
     g->SetCustomPlot(1, i * 4 + 3, "L");
     g->SetCustomPlot(1, i * 4 + 4, "L");
     g->SetCustomFillAlpha(1, i * 4 + 1, 0.2);
     g->SetCustomFillStyle(1, i * 4 + 1, 1001);
     g->SetCustomLineWidth(1, i * 4 + 2, 3);
     g->SetCustomLineWidth(1, i * 4 + 3, 3);
     g->SetCustomLineWidth(1, i * 4 + 4, 3);
     if(PlotNoFill[i + 1]) g->SetCustomFillAlpha(1, i * 4 + 1, 0.0);
     if(PlotNoFill[i + 1]) g->SetCustomPlot(1, i * 4 + 1, "L");
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 1, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 2, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 3, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 4, 4);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 1, PlotLineStyle[i + 1]);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 2, PlotLineStyle[i + 1]);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 3, PlotLineStyle[i + 1]);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 4, PlotLineStyle[i + 1]);
     if(abs(FlavorList.at(flavor)) <= 5) g->SetCustomYRange(1, 1e-1, 15);
     if(xPlotYMin.count(FlavorList.at(flavor)) > 0) g->SetCustomYRange(1, xPlotYMin.at(FlavorList.at(flavor)), xPlotYMax.at(FlavorList.at(flavor)));
     g->SetXRange(1e-5, 1);
     g->SetLogX();
     if(abs(FlavorList.at(flavor)) <= 5){
       g->SetLogY();
     }
   }
   for(int i = 0; i < SinglePDFNames.size(); i++){
     if(abs(FlavorList.at(flavor)) <= 7){
       g->Input(nErrorPDF * 4 + i + 1, xPDFPlot[make_tuple(SinglePDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[SinglePDFNames.at(i)]);
     }
     else{
       g->Input(nErrorPDF * 4 + i + 1, PDFPlot[make_tuple(SinglePDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[SinglePDFNames.at(i)]);
     }
     g->CustomSetting(1, nErrorPDF * 4 + i + 1);
     g->SetCustomPlotFormat(1, nErrorPDF * 4 + i + 1, PlotLineColor[nErrorPDF + i + 1]);
     g->SetCustomPlot(1, nErrorPDF * 4 + i + 1, "L");
     if(xPlotYMin.count(FlavorList.at(flavor)) > 0) g->SetCustomYRange(1, xPlotYMin.at(FlavorList.at(flavor)), xPlotYMax.at(FlavorList.at(flavor)));
   }

   if(abs(FlavorList.at(flavor)) <= 5) g->SetCustomYRange(1, 1e-5, 100);
   g->SetXRange(1e-5, 1);
   g->SetLogX();
   if(abs(FlavorList.at(flavor)) <= 5){
     g->SetLogY();
   }
   g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
   g->SetTextLeftBias(TextLeftBias);
   g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
   g->Draw();
   delete g;

   PlotName.ReplaceAll("PDFPlot", "PDFRatio");
   RatioPlotNames.push_back(PlotName);

   if(ErrorPDFNames.size() != 0) g = new Graph(PlotName, "x", "PDF Ratio to " + PDFLegendName[ErrorPDFNames.at(0)]);
   else g = new Graph(PlotName, "x", "PDF Ratio to " + PDFLegendName[SinglePDFNames.at(0)]);
   g->SetCustomPad(1);

   for(int i = 0; i < ErrorPDFNames.size(); i++){
     g->Input(i * 4 + 1, PDFRatio[make_tuple(ErrorPDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[ErrorPDFNames.at(i)]);
     g->Input(i * 4 + 2, PDFRatioErrorPlus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
     g->Input(i * 4 + 3, PDFRatioErrorMinus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
     g->Input(i * 4 + 4, PDFRatioErrorCentral[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");

     g->SetCustomPad(1);
     if(PlotNoFill[i + 1]) g->IgnoreCustomError(1, i * 4 + 1);
     g->CustomSetting(1, i * 4 + 1);
     g->CustomSetting(1, i * 4 + 2);
     g->CustomSetting(1, i * 4 + 3);
     g->CustomSetting(1, i * 4 + 4);
     g->SetCustomPlotFormat(1, i * 4 + 1, PlotFillColor[i + 1]);
     g->SetCustomPlotFormat(1, i * 4 + 2, PlotLineColor[i + 1]);
     g->SetCustomPlotFormat(1, i * 4 + 3, PlotLineColor[i + 1]);
     g->SetCustomPlotFormat(1, i * 4 + 4, PlotLineColor[i + 1]);
     g->SetCustomPlot(1, i * 4 + 1, "Fill");
     g->SetCustomPlot(1, i * 4 + 2, "L");
     g->SetCustomPlot(1, i * 4 + 3, "L");
     g->SetCustomPlot(1, i * 4 + 4, "L");
     g->SetCustomFillAlpha(1, i * 4 + 1, 0.2);
     g->SetCustomFillStyle(1, i * 4 + 1, 1001);
     g->SetCustomLineWidth(1, i * 4 + 2, 3);
     g->SetCustomLineWidth(1, i * 4 + 3, 3);
     g->SetCustomLineWidth(1, i * 4 + 4, 3);
     if(PlotNoFill[i + 1]) g->SetCustomFillAlpha(1, i * 4 + 1, 0.0);
     if(PlotNoFill[i + 1]) g->SetCustomPlot(1, i * 4 + 1, "L");
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 1, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 2, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 3, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 4, 2);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 1, PlotLineStyle[i + 1]);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 2, PlotLineStyle[i + 1]);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 3, PlotLineStyle[i + 1]);
     if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 4, PlotLineStyle[i + 1]);
     g->SetCustomYRange(1, 0.9, 1.1);
     g->SetXRange(1e-5, 1);
     g->SetLogX();
   }

   for(int i = 0; i < SinglePDFNames.size(); i++){
     g->Input(nErrorPDF * 4 + i + 1, PDFRatio[make_tuple(SinglePDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[SinglePDFNames.at(i)]);
     g->CustomSetting(1, nErrorPDF * 4 + i + 1);
     g->SetCustomPlotFormat(1, nErrorPDF * 4 + i + 1, PlotLineColor[nErrorPDF + i + 1]);
     g->SetCustomPlot(1, nErrorPDF * 4 + i + 1, "L");
     g->SetCustomLineWidth(1, nErrorPDF * 4 + i + 1, 3);
     if(nErrorPDF >= 2){
       g->SetCustomLineStyle(1, nErrorPDF * 4 + i + 1, PlotLineStyle[i + 2]);
     }
   }

   if(nErrorPDF != 0) g->SetCustomYRange(1, 0.8, 1.2);
   else if(nErrorPDF == 0) g->SetCustomYRange(1, 0.9, 1.1);

   g->SetXRange(1e-5, 1);
   g->SetLogX();
   g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
   g->SetTextLeftBias(TextLeftBias);
   g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
   g->Draw();
   delete g;

   if(nErrorPDF != 0){

     PlotName.ReplaceAll("PDFRatio", "PDFRatioSelf");
     RatioSelfPlotNames.push_back(PlotName);

     if(ErrorPDFNames.size() != 0) g = new Graph(PlotName, "x", "PDF Ratio");
     else g = new Graph(PlotName, "x", "PDF Ratio");
     g->SetCustomPad(1);

     for(int i = 0; i < ErrorPDFNames.size(); i++){
       g->Input(i * 4 + 1, PDFRatioSelf[make_tuple(ErrorPDFNames.at(i), 0, FlavorList.at(flavor), Q)], PDFLegendName[ErrorPDFNames.at(i)]);
       g->Input(i * 4 + 2, PDFRatioSelfErrorPlus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
       g->Input(i * 4 + 3, PDFRatioSelfErrorMinus[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");
       g->Input(i * 4 + 4, PDFRatioSelfErrorCentral[make_tuple(ErrorPDFNames.at(i), FlavorList.at(flavor), Q)], "");

       g->SetCustomPad(1);
       if(PlotNoFill[i + 1]) g->IgnoreCustomError(1, i * 4 + 1);
       g->CustomSetting(1, i * 4 + 1);
       g->CustomSetting(1, i * 4 + 2);
       g->CustomSetting(1, i * 4 + 3);
       g->CustomSetting(1, i * 4 + 4);
       g->SetCustomPlotFormat(1, i * 4 + 1, PlotFillColor[i + 1]);
       g->SetCustomPlotFormat(1, i * 4 + 2, PlotLineColor[i + 1]);
       g->SetCustomPlotFormat(1, i * 4 + 3, PlotLineColor[i + 1]);
       g->SetCustomPlotFormat(1, i * 4 + 4, PlotLineColor[i + 1]);
       g->SetCustomPlot(1, i * 4 + 1, "Fill");
       g->SetCustomPlot(1, i * 4 + 2, "L");
       g->SetCustomPlot(1, i * 4 + 3, "L");
       g->SetCustomPlot(1, i * 4 + 4, "L");
       g->SetCustomFillAlpha(1, i * 4 + 1, 0.2);
       g->SetCustomFillStyle(1, i * 4 + 1, 1001);
       g->SetCustomLineWidth(1, i * 4 + 2, 3);
       g->SetCustomLineWidth(1, i * 4 + 3, 3);
       g->SetCustomLineWidth(1, i * 4 + 4, 3);
       if(PlotNoFill[i + 1]) g->SetCustomFillAlpha(1, i * 4 + 1, 0.0);
       if(PlotNoFill[i + 1]) g->SetCustomPlot(1, i * 4 + 1, "L");
       if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 1, 2);
       if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 2, 2);
       if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 3, 2);
       if(PlotNoFill[i + 1]) g->SetCustomLineWidth(1, i * 4 + 4, 2);
       if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 1, PlotLineStyle[i + 1]);
       if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 2, PlotLineStyle[i + 1]);
       if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 3, PlotLineStyle[i + 1]);
       if(PlotNoFill[i + 1]) g->SetCustomLineStyle(1, i * 4 + 4, PlotLineStyle[i + 1]);
       g->SetCustomYRange(1, 0.9, 1.1);
       g->SetXRange(1e-5, 1);
       g->SetLogX();
     }

     g->SetCustomYRange(1, 0.8, 1.2);

     g->SetXRange(1e-5, 1);
     g->SetLogX();
     g->SetLegendPosition(LegendXmin, LegendYmin, LegendXmax, LegendYmax);
     g->SetTextLeftBias(TextLeftBias);
     g->AddText(1, TitleMap[FlavorList.at(flavor)] + (TString)"(x,Q) at Q = " + Qstring + " GeV " + (TString)" 68\% C.L.");
     g->Draw();
     delete g;
   }
 }
}

void PDFFigure::PreparePDFPlotAll(TString PDFName, double Q)
{
 vector<double> FlavorList;

 if(Option == "Nes") FlavorList = FlavorListNes;
 if(Option == "All") FlavorList = FlavorListAll;

 for(int flavor = 0; flavor < FlavorList.size(); flavor++){
   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     PDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)] = DrawPDFvsX(PDFName, i, FlavorList.at(flavor), Q);

     TString HistName = PDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)]->GetName();
     HistName.ReplaceAll("PDFvsX", "xPDFvsX");
     xPDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)] = (TH1D *)PDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)]->Clone(HistName);
     GetxPDF(PDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)], xPDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)]);
   }
 }
}

void PDFFigure::PreparePDFRatio(TString PDFName, int iSet, double Q, TString BaseName)
{
 vector<double> FlavorList;

 if(Option == "Nes") FlavorList = FlavorListNes;
 if(Option == "All") FlavorList = FlavorListAll;

 for(int flavor = 0; flavor < FlavorList.size(); flavor++){
   TString HistName = PDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->GetName();
   HistName.ReplaceAll("PDFvsX", "PDFRatio");
   PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)] = (TH1D *)PDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Divide(PDFPlot[make_tuple(BaseName, 0, FlavorList.at(flavor), Q)]);
   //GetRatio(PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)], PDFPlot[make_tuple(BaseName, 0, FlavorList.at(flavor), Q)]);
   RemoveErrors(PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]);
   PDFRatio68CL[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName + "_68CL");
   ConvertRatioTo68CL(PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)], PDFRatio68CL[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]);

   HistName.ReplaceAll("PDFRatio", "PDFRatioSelf");
   PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)] = (TH1D *)PDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Divide(PDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]);
   //GetRatio(PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)], PDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]);
   RemoveErrors(PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]);
   PDFRatioSelf68CL[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName + "_68CL");
   ConvertRatioTo68CL(PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)], PDFRatioSelf68CL[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]);

   if(iSet == 0){
     HistName = PDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->GetName();
     HistName.ReplaceAll("PDFvsX", "PDFErrorCentral");
     PDFErrorCentral[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName);

     HistName = xPDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->GetName();
     HistName.ReplaceAll("xPDFvsX", "xPDFErrorCentral");
     xPDFErrorCentral[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)xPDFPlot[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName);

     HistName = PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->GetName();
     HistName.ReplaceAll("PDFRatio", "PDFRatioErrorCentral");
     PDFRatioErrorCentral[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatio[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName);

     HistName = PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->GetName();
     HistName.ReplaceAll("PDFRatioSelf", "PDFRatioSelfErrorCentral");
     PDFRatioSelfErrorCentral[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatioSelf[make_tuple(PDFName, iSet, FlavorList.at(flavor), Q)]->Clone(HistName);
   }
 }

}

void PDFFigure::PreparePDFRatioAll(TString PDFName, double Q, TString BaseName)
{
 cout<<"Prepare PDF Ratio:"<<endl;

 for(int i = 0; i <= PDFnSet[PDFName]; i++){
   PreparePDFRatio(PDFName, i, Q, BaseName);
 }
}

void PDFFigure::PreparePDFError(TString PDFName, double Q, TString ErrorType)
{
 if(PDFnSet[PDFName] == 0){
   return;
 }

 cout<<"Prepare PDF Error:"<<endl;

 vector<double> FlavorList; 

 if(Option == "Nes") FlavorList = FlavorListNes;
 if(Option == "All") FlavorList = FlavorListAll;
 
 for(int flavor = 0; flavor < FlavorList.size(); flavor++){

   //Get PDF Uncertainty
   vector<TH1D *> PDFPlots(PDFnSet[PDFName] + 1);

   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     PDFPlots.at(i) = PDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)];
   }
   PDFUncertainty* unc = new PDFUncertainty();
   unc->Input1DPlot(ErrorType, PDFPlots, PDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   ApplyPDFError(PDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)], PDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   TString HistName = PDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]->GetName();
   HistName.ReplaceAll("PDFError", "PDFErrorPlus");
   PDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(PDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   RemoveErrors(PDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName.ReplaceAll("PDFErrorPlus", "PDFErrorMinus");
   PDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(PDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)], -1);
   RemoveErrors(PDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   PDFPlots.clear();

   //Get xPDF Uncertainty
   vector<TH1D *> xPDFPlots(PDFnSet[PDFName] + 1);

   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     xPDFPlots.at(i) = xPDFPlot[make_tuple(PDFName, i, FlavorList.at(flavor), Q)];
   }
   PDFUncertainty* xunc = new PDFUncertainty();
   xunc->Input1DPlot(ErrorType, xPDFPlots, xPDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   ApplyPDFError(xPDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)], xPDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName = xPDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]->GetName();
   HistName.ReplaceAll("PDFError", "PDFErrorPlus");
   xPDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)xPDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   xPDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(xPDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   RemoveErrors(xPDFErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName.ReplaceAll("PDFErrorPlus", "PDFErrorMinus");
   xPDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)xPDFPlot[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   xPDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(xPDFErrorPlot[make_tuple(PDFName, FlavorList.at(flavor), Q)], -1);
   RemoveErrors(xPDFErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   xPDFPlots.clear();

   //Get PDF Ratio Uncertainty
   vector<TH1D *> PDFRatios(PDFnSet[PDFName] + 1);

   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     PDFRatios.at(i) = PDFRatio[make_tuple(PDFName, i, FlavorList.at(flavor), Q)];
   }
   PDFUncertainty* ratiounc = new PDFUncertainty();
   ratiounc->Input1DPlot(ErrorType, PDFRatios, PDFRatioError[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   ApplyPDFError(PDFRatio[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)], PDFRatioError[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName = PDFRatioError[make_tuple(PDFName, FlavorList.at(flavor), Q)]->GetName();
   HistName.ReplaceAll("PDFError", "PDFErrorPlus");
   PDFRatioErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatio[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFRatioErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(PDFRatioError[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   RemoveErrors(PDFRatioErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName.ReplaceAll("PDFErrorPlus", "PDFErrorMinus");
   PDFRatioErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatio[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFRatioErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(PDFRatioError[make_tuple(PDFName, FlavorList.at(flavor), Q)], -1);
   RemoveErrors(PDFRatioErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   PDFRatios.clear();

   //Get PDF Ratio Uncertainty for self
   vector<TH1D *> PDFRatioSelfs(PDFnSet[PDFName] + 1);

   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     PDFRatioSelfs.at(i) = PDFRatioSelf[make_tuple(PDFName, i, FlavorList.at(flavor), Q)];
   }
   PDFUncertainty* ratioselfunc = new PDFUncertainty();
   ratioselfunc->Input1DPlot(ErrorType, PDFRatioSelfs, PDFRatioSelfError[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   ApplyPDFError(PDFRatioSelf[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)], PDFRatioSelfError[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName = PDFRatioSelfError[make_tuple(PDFName, FlavorList.at(flavor), Q)]->GetName();
   HistName.ReplaceAll("PDFError", "PDFErrorPlus");
   PDFRatioSelfErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatioSelf[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFRatioSelfErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(PDFRatioSelfError[make_tuple(PDFName, FlavorList.at(flavor), Q)]);
   RemoveErrors(PDFRatioSelfErrorPlus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   HistName.ReplaceAll("PDFErrorPlus", "PDFErrorMinus");
   PDFRatioSelfErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)] = (TH1D *)PDFRatioSelf[make_tuple(PDFName, 0, FlavorList.at(flavor), Q)]->Clone(HistName);
   PDFRatioSelfErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]->Add(PDFRatioSelfError[make_tuple(PDFName, FlavorList.at(flavor), Q)], -1);
   RemoveErrors(PDFRatioSelfErrorMinus[make_tuple(PDFName, FlavorList.at(flavor), Q)]);

   PDFRatioSelfs.clear();
 }

}

TH1D* PDFFigure::DrawPDFvsX(TString PDFName, int iSet, int flavor, double Q)
{
 if(isLinkFile) hf->cd();

 TH1D* h1;

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(2)<<Q;

 Qstring = s_Qstring.str();

 TString HistName = "PDFvsX_Q_" + Qstring + "_" + PDFName + "_iSet_" + (int)iSet + "_" + FlavorNameMap[flavor];
 h1 = new TH1D(HistName, HistName, LogBin.size() - 1, &LogBin[0]);
 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double BinCenter = h1->GetBinCenter(ibin);
   h1->SetBinContent(ibin, Getf(PDFName, iSet, flavor, BinCenter, Q));
   h1->SetBinError(ibin, 0.0);
 }

 return h1;
}

TH1D* PDFFigure::DrawPDFvsQ()
{
 TH1D* h1;

 return h1;
}

TH1D* PDFFigure::DrawPDFCorrelation(vector<TH1D *> Variable, TString PDFName, int flavor, double Q, TString ErrorType)
{
 TH1D* h1;

 stringstream s_Qstring;
 TString Qstring;

 s_Qstring<<fixed<<setprecision(2)<<Q;

 Qstring = s_Qstring.str();

 TString HistName;
 HistName = "PartonCorrelation_" +  (TString)Variable.at(0)->GetName() + "_Q" + Qstring + "_" + FlavorNameMap[flavor] + "_" + PDFName;

 vector<double> Parton1PDF;
 vector<vector<double>> Parton1PDFs;
 vector<double> Parton1ErrorPDF;
 vector<vector<double>> Parton1ErrorPDFs;

 h1 = new TH1D(HistName, HistName, LogBin.size() - 1, &LogBin[0]);

 for(int k = 0; k <= PDFnSet[PDFName]; k++){
   for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
     double BinCenter = h1->GetBinCenter(ibin);
     Parton1PDF.push_back(Getf(PDFName, k, flavor, BinCenter, Q));
   }
   Parton1PDFs.push_back(Parton1PDF);
   Parton1PDF.clear();
 }

 for(int k = 1; k <= PDFnSet[PDFName] / 2; k++){
   for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
     double Parton1ErrorValue = Parton1PDFs.at(2 * k - 1).at(ibin - 1) - Parton1PDFs.at(2 * k).at(ibin - 1);
     Parton1ErrorPDF.push_back(Parton1ErrorValue);
   }
   Parton1ErrorPDFs.push_back(Parton1ErrorPDF);
   Parton1ErrorPDF.clear();
 }

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   double Numer = 0.0;
   double Denom = 0.0;
   double DeltaX = 0.0;
   double DeltaY = 0.0;
   double DeltaX2 = 0.0;
   double DeltaY2 = 0.0;
   for(int k = 1; k <= PDFnSet[PDFName] / 2; k++){
     Numer += (Variable.at(2 * k - 1)->GetBinContent(1) - Variable.at(2 * k)->GetBinContent(1)) * Parton1ErrorPDFs.at(k - 1).at(ibin - 1) / 4.0;
     DeltaX2 += (Variable.at(2 * k - 1)->GetBinContent(1) - Variable.at(2 * k)->GetBinContent(1)) * (Variable.at(2 * k - 1)->GetBinContent(1) - Variable.at(2 * k)->GetBinContent(1)) / 4.0;
     DeltaY2 += Parton1ErrorPDFs.at(k - 1).at(ibin - 1) * Parton1ErrorPDFs.at(k - 1).at(ibin - 1) / 4.0;
   }
   DeltaX = sqrt(DeltaX2);
   DeltaY = sqrt(DeltaY2);
   Denom = DeltaX * DeltaY;

   h1->SetBinContent(ibin, Numer / Denom);
   h1->SetBinError(ibin, 0);
 }

 return h1;
}

double PDFFigure::Getf(TString PDFName, int iSet, int flavor, double x, double Q)
{
 double Value = 0.0;

 if(x >= 1.0) return 0.0;

#ifdef USE_LHAPDF
 if(abs(flavor) == 1 || abs(flavor) == 2 || abs(flavor) == 3 || abs(flavor) == 4 || abs(flavor) == 5 || abs(flavor) == 0){//u, d, s, c, b, gluon
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(flavor, x, Q) / x;
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(flavor, x, Q) / x;
 }

 if(flavor == 6){//uv
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x;
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x;
 }

 if(flavor == 7){//dv
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x;
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x;
 }

 if(flavor == 8){//s-sbar
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(3, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-3, x, Q) / x;
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(3, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-3, x, Q) / x;
 }

 if(flavor == 9){//ubouv
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) > 1e-10) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) > 1e-10) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x);
   }
 }

 if(flavor == 10){//dbodv
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
 }

 if(flavor == 11){//ubou
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x);
   }
 }

 if(flavor == 12){//dbod
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x);
   }
 }

 if(flavor == 13){//gluon / 5
   if(PDFType[PDFName] == "LHAPDF") Value = PDF[make_pair(PDFName, iSet)]->xfxQ(0, x, Q) / 5.0 / x;
   if(PDFType[PDFName] == "CTEQ") Value = CTPDF[make_pair(PDFName, iSet)]->xfxQ(0, x, Q) / 5.0 / x;
 }

 if(flavor == 14){//uod
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x);
   }
 }

 if(flavor == 15){//ubodb
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
 }

 if(flavor == 16){//uvodv
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x - CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
 }

 if(flavor == 17){//dbou
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x);
   }
 }

 if(flavor == 18){//ubod
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x);
   }
 }

 if(flavor == 19){//dboub
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x);
   }
 }

 if(flavor == 20){//dou
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, x, Q) / x);
   }
 }

 if(flavor == 21){//Rs
   if(PDFType[PDFName] == "LHAPDF"){
     if(fabs(PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x + PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (PDF[make_pair(PDFName, iSet)]->xfxQ(3, x, Q) / x + PDF[make_pair(PDFName, iSet)]->xfxQ(-3, x, Q) / x) / (PDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x + PDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
   if(PDFType[PDFName] == "CTEQ"){
     if(fabs(CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x + CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x) > 1e-20) Value = (CTPDF[make_pair(PDFName, iSet)]->xfxQ(3, x, Q) / x + CTPDF[make_pair(PDFName, iSet)]->xfxQ(-3, x, Q) / x) / (CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, x, Q) / x + CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, x, Q) / x);
   }
 }

#endif

 return Value;
}

void PDFFigure::OutputTexFile(TString name)
{
 ofstream texfile(name);

 texfile<<"\\documentclass[prd, aps, 11pt, amsfonts, amssymb, amsmath, onecolumn]{article}"<<endl;
 texfile<<"\\usepackage{graphicx, multirow,soul}"<<endl;
 if(nErrorPDF == 0){
   texfile<<"\\usepackage[top=1.0cm,bottom=1.5cm,left=1.5cm,right=1.5cm]{geometry}"<<endl;
 }
 else{
   //texfile<<"\\usepackage[a3paper,landscape,margin=1.5cm]{geometry}"<<endl;
   texfile<<"\\usepackage[paperwidth=42cm,paperheight=33cm,margin=1.5cm]{geometry}"<<endl;
 }
 texfile<<"\\usepackage{graphicx} % Required for inserting images"<<endl;
 texfile<<"\\usepackage{booktabs}"<<endl;
 texfile<<"\\usepackage{comment}"<<endl;
 texfile<<"\\usepackage{amssymb}"<<endl;
 texfile<<"\\usepackage{amsmath}"<<endl;
 texfile<<""<<endl;
 texfile<<"\\title{}"<<endl;
 texfile<<"\\author{}"<<endl;
 texfile<<"%\\date{August 2023}"<<endl;
 texfile<<""<<endl;
 texfile<<"\\begin{document}"<<endl;
 texfile<<""<<endl;
 texfile<<"%\\maketitle"<<endl;
 texfile<<""<<endl;

 if(nErrorPDF == 0){
   int nBlock = PlotNames.size() / 3;
   if(PlotNames.size() % 3 != 0) nBlock = nBlock + 1;
   for(int i = 0; i < nBlock; i++){
     texfile<<"\\begin{figure}"<<endl;
     texfile<<"    \\centering"<<endl;
     if(3 * i < PlotNames.size()) texfile<<"    \\includegraphics[width=0.45\\textwidth]{"<<PlotNames.at(3 * i)<<"}"<<endl;
     if(3 * i < PlotNames.size()) texfile<<"    \\includegraphics[width=0.45\\textwidth]{"<<RatioPlotNames.at(3 * i)<<"}"<<endl;
     if(3 * i + 1 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.45\\textwidth]{"<<PlotNames.at(3 * i + 1)<<"}"<<endl;
     if(3 * i + 1 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.45\\textwidth]{"<<RatioPlotNames.at(3 * i + 1)<<"}"<<endl;
     if(3 * i + 2 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.45\\textwidth]{"<<PlotNames.at(3 * i + 2)<<"}"<<endl;
     if(3 * i + 2 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.45\\textwidth]{"<<RatioPlotNames.at(3 * i + 2)<<"}"<<endl;
     texfile<<"    \\caption{}"<<endl;
     texfile<<"    \\label{fig:enter-label}"<<endl;
     texfile<<"\\end{figure}"<<endl;
     texfile<<""<<endl;
   }
 }
 else{
   int nBlock = PlotNames.size() / 3;
   if(PlotNames.size() % 3 != 0) nBlock = nBlock + 1;
   for(int i = 0; i < nBlock; i++){
     texfile<<"\\begin{figure}"<<endl;
     texfile<<"    \\centering"<<endl;
     if(3 * i < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<PlotNames.at(3 * i)<<"}"<<endl;
     if(3 * i < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<RatioPlotNames.at(3 * i)<<"}"<<endl;
     if(3 * i < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<RatioSelfPlotNames.at(3 * i)<<"}"<<endl;
     if(3 * i + 1 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<PlotNames.at(3 * i + 1)<<"}"<<endl;
     if(3 * i + 1 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<RatioPlotNames.at(3 * i + 1)<<"}"<<endl;
     if(3 * i + 1 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<RatioSelfPlotNames.at(3 * i + 1)<<"}"<<endl;
     if(3 * i + 2 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<PlotNames.at(3 * i + 2)<<"}"<<endl;
     if(3 * i + 2 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<RatioPlotNames.at(3 * i + 2)<<"}"<<endl;
     if(3 * i + 2 < PlotNames.size()) texfile<<"    \\includegraphics[width=0.32\\textwidth]{"<<RatioSelfPlotNames.at(3 * i + 2)<<"}"<<endl;
     texfile<<"    \\caption{}"<<endl;
     texfile<<"    \\label{fig:enter-label}"<<endl;
     texfile<<"\\end{figure}"<<endl;
     texfile<<""<<endl;
   }
 }

 texfile<<"\\end{document}"<<endl;
}

