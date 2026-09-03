#include "Figure/Graph.h"

Graph::Graph(const char* FigureName, const char* XTitle, const char* YTitle)
{
 FigureCount = 0;
 TextCount = 0;

 isInput = false;

 isLogX = false;

 isSetXRange = false;

 myFigureName = FigureName;
 myXTitle = XTitle;
 myYTitle = YTitle;

 SaveFigure();

 for(int i = 0; i < 10; i++){
   myStyle[i] = new TStyle((TString)"Style" + (int)i, (TString)"Style" + (int)i);
   myStyle[i]->SetTextFont(32);
   myStyle[i]->SetHatchesLineWidth(2);
   myStyle[i]->SetStatStyle(0);
   myStyle[i]->SetStatX(0);
   myStyle[i]->SetStatY(0);
 }

 myColor[1] = (Color_t)kRed;
 myColor[2] = (Color_t)kBlue;
 myColor[3] = (Color_t)kGreen+1;
 myColor[4] = (Color_t)kOrange;
 myColor[5] = (Color_t)kCyan;
 myColor[6] = (Color_t)kYellow+2;
 myColor[7] = (Color_t)kMagenta;
 myColor[8] = (Color_t)kYellow+1;
 myColor[9] = (Color_t)kAzure-4;
 myColor[10] = (Color_t)kSpring+2;
 myColor[11] = (Color_t)kTeal;
 myColor[12] = (Color_t)kAzure+1;
 myColor[13] = (Color_t)kBlack;
 myColor[14] = (Color_t)kRed+1;
 myColor[15] = (Color_t)kBlue+1;
 myColor[16] = (Color_t)kGreen+2;
 myColor[17] = (Color_t)kOrange+1;
 myColor[18] = (Color_t)kCyan+1;
 myColor[19] = (Color_t)kYellow+3;
 myColor[20] = (Color_t)kMagenta+1;
 myColor[21] = (Color_t)kYellow+2;
 myColor[22] = (Color_t)kAzure-5;
 myColor[23] = (Color_t)kSpring+3;
 myColor[24] = (Color_t)kTeal+1;
 myColor[25] = (Color_t)kAzure+2;
 myColor[26] = (Color_t)kBlack+1;

 SetMode("CUSTOM");
 //InputCustomLimit(-99999.0, 99999.0, -99999.0, 99999.0);
}

Graph::~Graph()
{
 for(int PadNumber = 1; PadNumber <= TotalPadNumber; PadNumber++){
   for(int Number = 1; Number <= CustomFigureCount[PadNumber]; Number++){
     delete CustomHist[PadNumber][Number];
   }
 }

}

void Graph::SetMode(const char* ModeName)
{
 TString myMode = ModeName;
 if(myMode == "CUSTOM") isCustom = true;
}

void Graph::SetLegendPosition(double xmin, double ymin, double xmax, double ymax)
{
 legendxmin = xmin;
 legendxmax = xmax;
 legendymin = ymin;
 legendymax = ymax;
}

void Graph::SetLegend2Position(double xmin, double ymin, double xmax, double ymax)
{
 isDrawLegend2 = true;

 legend2xmin = xmin;
 legend2xmax = xmax;
 legend2ymin = ymin;
 legend2ymax = ymax;
}

void Graph::SetXRange(double xmin, double xmax)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 this->XRangeMin = xmin;
 this->XRangeMax = xmax;

 isSetXRange = true;
}


void Graph::DefineHist(int Number, TString name, TString title, int nbin, double left, double right)
{
 isDefineHist = true;
 h1[Number] = new TH1D(name, title, nbin, left, right);
}

void Graph::DefineHist(int Number, TString name, TString title, int nbinx, double* xbins)
{
 isDefineHist = true;
 h1[Number] = new TH1D(name, title, nbinx, xbins);
}

void Graph::SetCustomPad(int TotalPadNumber)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }

 this->TotalPadNumber = TotalPadNumber;

 if(TotalPadNumber == 1){
   CustomXTitleSize[1] = 0.042;
   CustomXTitleOffset[1] = 0.95;
   CustomXLabelSize[1] = 0.04;
   CustomYTitleSize[1] = 0.05;
   CustomYTitleOffset[1] = 1.25;
   CustomYLabelSize[1] = 0.05;
   CustomLegendSize[1] = 0.045;
   CustomBottomMargin[1] = 0.1;
   CustomTopMargin[1] = 0.05;
   CustomLeftMargin[1] = 0.15;
   CustomRightMargin[1] = 0.05;
   CustomPadYMax[1] = 1.0;
   CustomPadYMin[1] = 0.01;
   CustomPadXMax[1] = 1.0;
   CustomPadXMin[1] = 0.0;
   CustomNdivisions[1] = 505;
   CustomXNdivisions[1] = 505;
   CustomYNdivisions[1] = 510;
   CanvasX = 1000.0;
   CanvasY = 800.0;
 }
 if(TotalPadNumber == 2){
   CustomYTitleSize[1] = 0.055;
   CustomYTitleOffset[1] = 1.0;
   CustomYLabelSize[1] = 0.045;
   CustomLegendSize[1] = 0.045;
   CustomBottomMargin[1] = 0.0;
   CustomTopMargin[1] = 0.15;
   CustomLeftMargin[1] = 0.15;
   CustomRightMargin[1] = 0.05;
   CustomPadYMax[1] = 1.0;
   CustomPadYMin[1] = 0.25;
   CustomPadXMax[1] = 1.0;
   CustomPadXMin[1] = 0.0;

   CustomXTitleSize[2] = 0.12;
   CustomXTitleOffset[2] = 1;
   CustomXLabelSize[2] = 0.13;
   CustomYTitleSize[2] = 0.12;
   CustomYTitleOffset[2] = 0.4;
   CustomYLabelSize[2] = 0.12;
   CustomLegendSize[2] = 0.025;
   CustomBottomMargin[2] = 0.3;
   CustomTopMargin[2] = 0.0;
   CustomLeftMargin[2] = 0.15;
   CustomRightMargin[2] = 0.05;
   CustomPadYMax[2] = 0.25;
   CustomPadYMin[2] = 0.0;
   CustomPadXMax[2] = 1.0;
   CustomPadXMin[2] = 0.0;

   CustomNdivisions[2] = 505;
   CustomXNdivisions[2] = 505;
   CustomYNdivisions[2] = 505;

   isCustomGrid[2] = true;

   CanvasX = 1000.0;
   CanvasY = 1000.0;
 }
 if(TotalPadNumber == 3){
   CustomYTitleSize[1] = 0.06;
   CustomYTitleOffset[1] = 0.8;
   CustomYLabelSize[1] = 0.04;
   CustomLegendSize[1] = 0.025;
   CustomBottomMargin[1] = 0.0;
   CustomTopMargin[1] = 0.15;
   CustomLeftMargin[1] = 0.15;
   CustomRightMargin[1] = 0.05;
   CustomPadYMax[1] = 1.0;
   CustomPadYMin[1] = 0.3;
   CustomPadXMax[1] = 1.0;
   CustomPadXMin[1] = 0.0;

   CustomXTitleSize[2] = 0.12;
   CustomXTitleOffset[2] = 1;
   CustomXLabelSize[2] = 0.12;
   CustomYTitleSize[2] = 0.2;
   CustomYTitleOffset[2] = 0.3;
   CustomYLabelSize[2] = 0.2;
   CustomLegendSize[2] = 0.025;
   CustomBottomMargin[2] = 0.0;
   CustomTopMargin[2] = 0.0;
   CustomLeftMargin[2] = 0.15;
   CustomRightMargin[2] = 0.05;
   CustomPadYMax[2] = 0.3;
   CustomPadYMin[2] = 0.18;
   CustomPadXMax[2] = 1.0;
   CustomPadXMin[2] = 0.0;

   CustomXTitleSize[3] = 0.15;
   CustomXTitleOffset[3] = 1;
   CustomXLabelSize[3] = 0.15;
   CustomYTitleSize[3] = 0.14;
   CustomYTitleOffset[3] = 0.31;
   CustomYLabelSize[3] = 0.08;
   CustomLegendSize[3] = 0.025;
   CustomBottomMargin[3] = 0.35;
   CustomTopMargin[3] = 0.0;
   CustomLeftMargin[3] = 0.15;
   CustomRightMargin[3] = 0.05;
   CustomPadYMax[3] = 0.18;
   CustomPadYMin[3] = 0.0;
   CustomPadXMax[3] = 1.0;
   CustomPadXMin[3] = 0.0;

 }

}

void Graph::DefineCustomHist(int Number, int histNumber1, int histNumber2, TString process, const char* LegendName)
{
 tmpHist[Number] = (TH1D *)h1[histNumber1]->Clone("tmp");
 if((TString)process == "Plus"){
   tmpHist[Number]->Add(h1[histNumber2]);
 }
 if((TString)process == "Minus"){
   tmpHist[Number]->Add(h1[histNumber2], -1);
 }
 if((TString)process == "Divide"){
   tmpHist[Number]->Divide(h1[histNumber2]);
 }
 if((TString)process == "Pull"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     tmpHist[Number]->SetBinContent(ibin, (h1[histNumber1]->GetBinContent(ibin) - h1[histNumber2]->GetBinContent(ibin)) / sqrt(h1[histNumber1]->GetBinError(ibin) * h1[histNumber1]->GetBinError(ibin) + h1[histNumber2]->GetBinError(ibin) * h1[histNumber2]->GetBinError(ibin)));
   }
 }

 myLegendName[Number] = LegendName;

 if((TString)process == "") return;

 int tmpNumber = Number;
 if(tmpNumber <= FigureCount) return;
 h1[tmpNumber] = (TH1D *)tmpHist[Number]->Clone((TString)"tmp_" + (int)Number);

 FigureCount++;

}

void Graph::CustomSetting(int PadNumber, int histNumber1, int histNumber2, TString process)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }
 if(!isInput){
   cout<<"Please input at first"<<endl;
   return;
 }
 if(PadNumber > TotalPadNumber){
   cout<<"Out of pad range"<<endl;
   return;
 }

 if(isInputGraph[histNumber1]) return;

 CustomFigureCount[PadNumber]++;

 int Number = CustomFigureCount[PadNumber];

 CustomHist[PadNumber][Number] = (TH1D *)h1[histNumber1]->Clone((TString)"CustomHist_" + (int)PadNumber + (TString)"_" + (int)Number);
 myCustomLegendName[PadNumber][Number] = myLegendName[histNumber1];

 if((TString)process == "Plus"){
   CustomHist[PadNumber][Number]->Add(h1[histNumber2]);
 }
 if((TString)process == "Minus"){
   CustomHist[PadNumber][Number]->Add(h1[histNumber2], -1);
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
   }
 }
 if((TString)process == "Divide"){
   CustomHist[PadNumber][Number]->Divide(h1[histNumber2]);
   if(isOutput){
     for(int ibin = 1; ibin <= CustomHist[PadNumber][Number]->GetNbinsX(); ibin++){
       cout<<"bin "<<ibin<<": "<<CustomHist[PadNumber][Number]->GetBinContent(ibin)<<" +- "<<CustomHist[PadNumber][Number]->GetBinError(ibin)<<endl;
     }
   }
 }
 if((TString)process == "Pull"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     CustomHist[PadNumber][Number]->SetBinContent(ibin, (h1[histNumber1]->GetBinContent(ibin) - h1[histNumber2]->GetBinContent(ibin)) / sqrt(h1[histNumber1]->GetBinError(ibin) * h1[histNumber1]->GetBinError(ibin) + h1[histNumber2]->GetBinError(ibin) * h1[histNumber2]->GetBinError(ibin)));
   }
 }

 cout<<"Integral of "<<CustomHist[PadNumber][Number]->GetName()<<": "<<CustomHist[PadNumber][Number]->Integral()<<endl;

 Custom[PadNumber][Number] = new TGraphErrors(CustomHist[PadNumber][Number]->GetNbinsX());
 Custom[PadNumber][Number]->SetName((TString)"Custom_" + (int)PadNumber + (TString)"_" + (int)Number);

 int iPoint = 0;
 for(int ibin = 1; ibin <= CustomHist[PadNumber][Number]->GetNbinsX(); ibin++){
   iPoint++;
   double Value = CustomHist[PadNumber][Number]->GetBinContent(ibin);
   if(fabs(Value) > 1e-10) Custom[PadNumber][Number]->SetPointX(iPoint, CustomHist[PadNumber][Number]->GetBinCenter(ibin));
   if(fabs(Value) > 1e-10) Custom[PadNumber][Number]->SetPointY(iPoint, CustomHist[PadNumber][Number]->GetBinContent(ibin));
   double BinWidth = CustomHist[PadNumber][Number]->GetXaxis()->GetBinUpEdge(ibin) - CustomHist[PadNumber][Number]->GetXaxis()->GetBinLowEdge(ibin);
   BinWidth = 0.0;
   if(fabs(Value) > 1e-10) Custom[PadNumber][Number]->SetPointError(iPoint, BinWidth, CustomHist[PadNumber][Number]->GetBinError(ibin));
   if(isIgnoreError[PadNumber][Number]) Custom[PadNumber][Number]->SetPointError(iPoint, BinWidth, 0.0);
   //Custom[PadNumber][Number]->SetPointError(ibin, BinWidth, 0.0);
 }

 Custom[PadNumber][Number]->SetMinimum(CustomHist[PadNumber][Number]->GetMinimum());
 Custom[PadNumber][Number]->SetMaximum(CustomHist[PadNumber][Number]->GetMaximum());

 Custom[PadNumber][Number]->RemovePoint(0);
 for(int i = Custom[PadNumber][Number]->GetN(); i > 0; i--){
   if(fabs(Custom[PadNumber][Number]->GetPointY(i)) < 1e-10) Custom[PadNumber][Number]->RemovePoint(i);
 }
 if(isRemoveLastPoint[PadNumber][Number]) Custom[PadNumber][Number]->RemovePoint(CustomHist[PadNumber][Number]->GetNbinsX() + 1);

 if((TString)process == "") return;

}

void Graph::SetCustomPlotFormat(int PadNumber, int Number, Color_t Color, Style_t style, bool isFilled)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 //Custom[PadNumber][Number]->SetMarkerStyle(style);
 Custom[PadNumber][Number]->SetMarkerColor(Color);
 //Custom[PadNumber][Number]->SetMarkerSize(1.2);
 //Custom[PadNumber][Number]->SetLineWidth(3);
 Custom[PadNumber][Number]->SetLineColor(Color);
 //Custom[PadNumber][Number]->SetLineStyle(1);
 if(isFilled){
   Custom[PadNumber][Number]->SetFillColor(Color);
   Custom[PadNumber][Number]->SetFillStyle(3354);
 }

 TList *funcList = Custom[PadNumber][Number]->GetListOfFunctions();

 if(funcList && funcList->GetSize() > 0) {
   TObject *obj = funcList->At(0);
   TF1 *fit = dynamic_cast<TF1*>(obj);
   if(fit) {
     fit->SetLineColor(Color);
     fit->SetNpx(10000);
   }
   Custom[PadNumber][Number]->SetLineColor(0);
   Custom[PadNumber][Number]->SetLineWidth(0);
 }

 CustomColor[make_pair(PadNumber, Number)] = Color;
//   legend1->AddEntry(h1[Number], myLegendName[Number],"lpfe");
}

void Graph::SetPadTitle(int PadNumber, const char* PadName)
{
 myPadName[PadNumber] = PadName;
}

void Graph::SetCustomYRange(int PadNumber, double ymin, double ymax)
{
 isSetCustomYRange[PadNumber] = true;

 CustomYRangeMin[PadNumber] = ymin;
 CustomYRangeMax[PadNumber] = ymax;
}

void Graph::SetCustomLegendSize(int PadNumber, double size)
{
 CustomLegendSize[PadNumber] = size;
}

void Graph::SetCustomXTitleSize(int PadNumber, double size)
{
 CustomXTitleSize[PadNumber] = size;
}

void Graph::SetCustomXTitleOffset(int PadNumber, double size)
{
 CustomXTitleOffset[PadNumber] = size;
}

void Graph::SetCustomXLabelSize(int PadNumber, double size)
{
 CustomXLabelSize[PadNumber] = size;
}

void Graph::SetCustomYTitleSize(int PadNumber, double size)
{
 CustomYTitleSize[PadNumber] = size;
}

void Graph::SetCustomYTitleOffset(int PadNumber, double size)
{
 CustomYTitleOffset[PadNumber] = size;
}

void Graph::SetCustomYLabelSize(int PadNumber, double size)
{
 CustomYLabelSize[PadNumber] = size;
}

void Graph::SetCustomPadYPosition(int PadNumber, double ymin, double ymax)
{
 CustomPadYMin[PadNumber] = ymin;
 CustomPadYMax[PadNumber] = ymax;
}

void Graph::SetCustomNdivisions(int PadNumber, int ndiv)
{
 CustomNdivisions[PadNumber] = ndiv;
}

void Graph::SetCustomXNdivisions(int PadNumber, int ndiv)
{
 CustomXNdivisions[PadNumber] = ndiv;
}

void Graph::SetCustomYNdivisions(int PadNumber, int ndiv)
{
 CustomYNdivisions[PadNumber] = ndiv;
}

void Graph::SetCustomGrid(int PadNumber, bool flag)
{
 isCustomGrid[PadNumber] = flag;
}

void Graph::SetCustomBarOffset(int PadNumber, int Number, double size)
{
}

void Graph::SetCustomMarkerStyle(int PadNumber, int Number, Style_t style)
{
 Custom[PadNumber][Number]->SetMarkerStyle(style);
}

void Graph::SetCustomLineStyle(int PadNumber, int Number, Style_t style)
{
 Custom[PadNumber][Number]->SetLineStyle(style);
}

void Graph::SetCustomLineWidth(int PadNumber, int Number, double size)
{
 Custom[PadNumber][Number]->SetLineWidth(size);
}

void Graph::SetCustomFillStyle(int PadNumber, int Number, Style_t style)
{
 Custom[PadNumber][Number]->SetFillStyle(style);
}

void Graph::SetCustomFillAlpha(int PadNumber, int Number, double alpha)
{
 Custom[PadNumber][Number]->SetFillColorAlpha(CustomColor[make_pair(PadNumber, Number)], alpha);
}

void Graph::CustomNorm(int fig1, int fig2, int BaseOne)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }
 if(!isInput){
   cout<<"Please input at first"<<endl;
   return;
 }

 double figsum1 = h1[fig1]->Integral();
 double figsum2 = h1[fig2]->Integral();

 if(BaseOne == 1) h1[fig2]->Scale(figsum1 / figsum2);
 if(BaseOne == 2) h1[fig1]->Scale(figsum2 / figsum1);
}

void Graph::SetCustomPlot(int PadNumber, int Number, TString format)
{
 CustomPlot[PadNumber][Number] = format;
 if(format.Contains("AP") || format == "P"){
   Custom[PadNumber][Number]->SetMarkerSize(2);
   Custom[PadNumber][Number]->SetLineWidth(1504);
   Custom[PadNumber][Number]->SetLineStyle(1);
   Custom[PadNumber][Number]->SetMarkerStyle(45);
   Custom[PadNumber][Number]->SetMarkerStyle(8);
 }
 if(format == "AC" || format == "C"){
   Custom[PadNumber][Number]->SetMarkerSize(1);
   Custom[PadNumber][Number]->SetLineWidth(2);
   Custom[PadNumber][Number]->SetLineStyle(1);
   Custom[PadNumber][Number]->SetMarkerStyle(1);
   Custom[PadNumber][Number]->SetMarkerColor(1);

   TList *funcList = Custom[PadNumber][Number]->GetListOfFunctions();

   if(funcList && funcList->GetSize() > 0) {
     TObject *obj = funcList->At(0);
     TF1 *fit = dynamic_cast<TF1*>(obj);
     if(fit) {
       fit->SetLineWidth(2);
       fit->SetLineStyle(1);
     }
   }
 }
 if(format.Contains("Fill")){
   CustomPlot[PadNumber][Number] = "A3";
   Custom[PadNumber][Number]->SetMarkerSize(0);
   Custom[PadNumber][Number]->SetLineWidth(0);
   Custom[PadNumber][Number]->SetFillStyle(3002);
   Custom[PadNumber][Number]->SetFillColor(CustomColor[make_pair(PadNumber, Number)]);
   Custom[PadNumber][Number]->SetLineStyle(1);
   Custom[PadNumber][Number]->SetMarkerStyle(45);
   Custom[PadNumber][Number]->SetMarkerStyle(8);
   if(format == "FillL"){
     CustomLegendType[PadNumber][Number] = "lf";
     Custom[PadNumber][Number]->SetLineWidth(2);
     CustomPlot[PadNumber][Number] = "A3 L";
   }
   if(format == "Fill") CustomLegendType[PadNumber][Number] = "f";
 }
 if(format.Contains("FillByLine")){
   CustomPlot[PadNumber][Number] = "AFL";
   Custom[PadNumber][Number]->SetMarkerSize(0);
   Custom[PadNumber][Number]->SetLineWidth(0);
   Custom[PadNumber][Number]->SetFillStyle(3002);
   Custom[PadNumber][Number]->SetFillColor(CustomColor[make_pair(PadNumber, Number)]);
   Custom[PadNumber][Number]->SetLineStyle(1);
   Custom[PadNumber][Number]->SetMarkerStyle(45);
   Custom[PadNumber][Number]->SetMarkerStyle(8);
   CustomLegendType[PadNumber][Number] = "f";
 }
 if(format == "L"){
   CustomPlot[PadNumber][Number] = "AC";
   Custom[PadNumber][Number]->SetLineStyle(1);
   Custom[PadNumber][Number]->SetLineWidth(1);
   Custom[PadNumber][Number]->SetMarkerSize(0);
   Custom[PadNumber][Number]->SetMarkerStyle(0);
   Custom[PadNumber][Number]->SetMarkerColor(0);
   Custom[PadNumber][Number]->SetFillColor(0);
 }
 if(format.Contains("Point")){
   CustomPlot[PadNumber][Number] = "AP";
   Custom[PadNumber][Number]->SetMarkerSize(2);
   Custom[PadNumber][Number]->SetLineWidth(0);
   Custom[PadNumber][Number]->SetLineStyle(1);
   Custom[PadNumber][Number]->SetMarkerStyle(34);
   Custom[PadNumber][Number]->SetMarkerColor(CustomColor[make_pair(PadNumber, Number)]);
 }
}

void Graph::InputCustomLimit(double xmin, double xmax, double ymin, double ymax)
{
 CustomLimit[1][1] = new TGraphErrors(1);
 CustomLimit[1][1]->SetName("CustomLimit_1_1");
 CustomLimit[1][1]->SetPointX(1, xmin);
 CustomLimit[1][1]->SetPointY(1, ymin);
 CustomLimit[1][1]->RemovePoint(0);

 CustomLimit[1][2] = new TGraphErrors(1);
 CustomLimit[1][2]->SetName("CustomLimit_1_2");
 CustomLimit[1][2]->SetPointX(1, xmin);
 CustomLimit[1][2]->SetPointY(1, ymax);
 CustomLimit[1][2]->RemovePoint(0);

 CustomLimit[1][3] = new TGraphErrors(1);
 CustomLimit[1][3]->SetName("CustomLimit_1_3");
 CustomLimit[1][3]->SetPointX(1, xmax);
 CustomLimit[1][3]->SetPointY(1, ymin);
 CustomLimit[1][3]->RemovePoint(0);

 CustomLimit[1][4] = new TGraphErrors(1);
 CustomLimit[1][4]->SetName("CustomLimit_1_4");
 CustomLimit[1][4]->SetPointX(1, xmax);
 CustomLimit[1][4]->SetPointY(1, ymax);
 CustomLimit[1][4]->RemovePoint(0);
}

void Graph::Input(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInput = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 if(!isDefineHist) h1[Number] = (TH1D *)file[Number]->Get(histName);
 if(isDefineHist){
   tmph1[Number] = (TH1D *)file[Number]->Get(histName);
   for(int ibin = 1; ibin <= tmph1[Number]->GetNbinsX(); ibin++){
     h1[Number]->SetBinContent(ibin, tmph1[Number]->GetBinContent(ibin));
     h1[Number]->SetBinError(ibin, tmph1[Number]->GetBinError(ibin));
   }
 }

 myLegendName[Number] = legendName;

 cout<<"Integral of "<<h1[Number]->GetName()<<": "<<h1[Number]->Integral()<<endl;
}

void Graph::Input(int Number, vector<double> x, vector<double> y, const char* legendName)
{
 isInput = true;

 FigureCount++;

 Custom[1][Number] = new TGraphErrors(x.size());

 for(int ibin = 0; ibin < x.size(); ibin++){
   Custom[1][Number]->SetPointX(ibin + 1, x.at(ibin));
   Custom[1][Number]->SetPointY(ibin + 1, y.at(ibin));
   //Custom[1][Number]->SetPointError(ibin + 1, 0.0, 0.0);
 }
 Custom[1][Number]->RemovePoint(0);
}

void Graph::InputGraph(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInput = true;
 isInputGraph[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 TGraphErrors* g = (TGraphErrors *)file[Number]->Get(histName);
 Custom[1][Number] = (TGraphErrors *)g->Clone((TString)"CUSTOM_1_" + (int)Number);

 myLegendName[Number] = legendName;
 myCustomLegendName[1][Number] = legendName;

 Custom[1][Number]->RemovePoint(0);
 h1[Number] = (TH1D *)Custom[1][Number]->GetHistogram();

 CustomFigureCount[1]++;

 isDirectGraph = true;
}

void Graph::InputGraph(int Number, TGraphErrors* g, const char* legendName)
{
 isInput = true;
 isInputGraph[Number] = true;

 FigureCount++;

 Custom[1][Number] = (TGraphErrors *)g->Clone((TString)"CUSTOM_1_" + (int)Number);

 myLegendName[Number] = legendName;
 myCustomLegendName[1][Number] = legendName;

 Custom[1][Number]->RemovePoint(0);
 h1[Number] = (TH1D *)Custom[1][Number]->GetHistogram();

 CustomFigureCount[1]++;

 isDirectGraph = true;
}

void Graph::Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName)
{
 isInput = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH2D *hist_2D = (TH2D *)file[Number]->Get(histName);

 if(binx == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsX(), hist_2D->GetXaxis()->GetBinLowEdge(1), hist_2D->GetXaxis()->GetBinUpEdge(hist_2D->GetNbinsX()));
   if(!isDefineHist) h1[Number] = hist_2D->ProjectionX(hist_2D->GetName() + (TString)"_px_" + (int)biny, biny, biny);

   for(int ibin = 1; ibin <= hist_2D->GetNbinsX(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_2D->GetBinContent(ibin, biny));
     h1[Number]->SetBinError(ibin, hist_2D->GetBinError(ibin, biny));
   }
 }
 else if(biny == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsY(), hist_2D->GetYaxis()->GetBinLowEdge(1), hist_2D->GetYaxis()->GetBinUpEdge(hist_2D->GetNbinsY()));
   if(!isDefineHist) h1[Number] = hist_2D->ProjectionY(hist_2D->GetName() + (TString)"_py_" + (int)binx, binx, binx);

   for(int ibin = 1; ibin <= hist_2D->GetNbinsY(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_2D->GetBinContent(binx, ibin));
     h1[Number]->SetBinError(ibin, hist_2D->GetBinError(binx, ibin));
   }
 }


}

void Graph::Input3D(int Number, const char* rootName, const char* histName, int binx, int biny, int binz, const char* legendName)
{
 isInput = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH3D *hist_3D = (TH3D *)file[Number]->Get(histName);

 if(binx == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_3D->GetNbinsX(), hist_3D->GetXaxis()->GetBinLowEdge(1), hist_3D->GetXaxis()->GetBinUpEdge(hist_3D->GetNbinsX()));
   if(!isDefineHist) h1[Number] = hist_3D->ProjectionX(hist_3D->GetName() + (TString)"_px_" + (int)biny, biny, biny, binz, binz);

   for(int ibin = 1; ibin <= hist_3D->GetNbinsX(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_3D->GetBinContent(ibin, biny, binz));
     h1[Number]->SetBinError(ibin, hist_3D->GetBinError(ibin, biny, binz));
   }
 }
 else if(biny == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_3D->GetNbinsY(), hist_3D->GetYaxis()->GetBinLowEdge(1), hist_3D->GetYaxis()->GetBinUpEdge(hist_3D->GetNbinsY()));
   if(!isDefineHist) h1[Number] = hist_3D->ProjectionY(hist_3D->GetName() + (TString)"_py_" + (int)biny, binx, binx, binz, binz);

   for(int ibin = 1; ibin <= hist_3D->GetNbinsY(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_3D->GetBinContent(binx, ibin, binz));
     h1[Number]->SetBinError(ibin, hist_3D->GetBinError(binx, ibin, binz));
   }
 }
 else if(binz == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_3D->GetNbinsZ(), hist_3D->GetZaxis()->GetBinLowEdge(1), hist_3D->GetZaxis()->GetBinUpEdge(hist_3D->GetNbinsZ()));
   if(!isDefineHist) h1[Number] = hist_3D->ProjectionZ(hist_3D->GetName() + (TString)"_pz_" + (int)biny, binx, binx, biny, biny);

   for(int ibin = 1; ibin <= hist_3D->GetNbinsZ(); ibin++){
     h1[Number]->SetBinContent(ibin, hist_3D->GetBinContent(binx, biny, ibin));
     h1[Number]->SetBinError(ibin, hist_3D->GetBinError(binx, biny, ibin));
   }
 }

}

void Graph::Input(int Number, TH1D* h, const char* legendName)
{
 isInput = true;

 FigureCount++;

 myLegendName[Number] = legendName;

 h1[Number] = h;
}

void Graph::InputValueAndError(int Number, double Value, double Error, const char* legendName)
{
 Values[Number] = new TH1D((TString)"Values" + (int)Number, (TString)"Values" + (int)Number, 1, Value - Error / 2.0, Value + Error / 2.0);

 Values[Number]->SetBinContent(1, NData + 1 - Number);
 Values[Number]->SetBinError(1, 0.0);

 Input(Number, Values[Number], legendName);

 SetCustomYLabelSize(1, 0.0);
}

void Graph::GetConvexHull(int Number)
{
 function<double(pair<double,double>, pair<double,double>, pair<double,double>)> cross = [](const pair<double,double>& O,
                                                                                            const pair<double,double>& A,
                                                                                            const pair<double,double>& B){
   return (A.first - O.first) * (B.second - O.second) - (A.second - O.second) * (B.first - O.first);
 };

 function<vector<pair<double,double>>(vector<pair<double,double>>)> ConvexHull = [&](vector<pair<double,double>> pts){
    if (pts.size() <= 1) return pts;

    sort(pts.begin(), pts.end(), [](const auto& a, const auto& b){
        if (a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    });

    pts.erase(unique(pts.begin(), pts.end(), [](const auto& a, const auto& b){
        return a.first == b.first && a.second == b.second;
    }), pts.end());

    int n = pts.size(), m = 0;
    vector<pair<double,double>> H(2 * n);

    for (int i = 0; i < n; ++i) {
        while (m >= 2 && cross(H[m-2], H[m-1], pts[i]) <= 0) m--;
        H[m++] = pts[i];
    }

    for (int i = n - 2, t = m + 1; i >= 0; --i) {
        while (m >= t && cross(H[m-2], H[m-1], pts[i]) <= 0) m--;
        H[m++] = pts[i];
    }

    H.resize(max(0, m - 1));
    return H;
 };

 vector<pair<double, double>> originpts;

 //Custom[1][Number]->RemovePoint(0);
 for(int i = 1; i <= Custom[1][Number]->GetN(); i++){
   originpts.push_back(make_pair(Custom[1][Number]->GetPointX(i - 1), Custom[1][Number]->GetPointY(i - 1)));
   //cout<<"origin pts "<<i<<" "<<Custom[1][Number]->GetPointX(i - 1)<<" "<<Custom[1][Number]->GetPointY(i - 1)<<endl;
 }

 vector<pair<double, double>> pts = ConvexHull(originpts);
 delete Custom[1][Number];
 Custom[1][Number] = new TGraphErrors(pts.size() + 1);

 for(int i = 0; i < pts.size(); i++){
   Custom[1][Number]->SetPointX(i + 1, pts.at(i).first);
   Custom[1][Number]->SetPointY(i + 1, pts.at(i).second);
   //cout<< i + 1 << "  " << pts.at(i).first << "  " << pts.at(i).second << endl;
 }
 Custom[1][Number]->SetPointX(pts.size() + 1, pts.at(0).first);
 Custom[1][Number]->SetPointY(pts.size() + 1, pts.at(0).second);
 Custom[1][Number]->RemovePoint(0);
}

void Graph::NormToOne(int Number)
{
 isNormToOne[Number] = true;
 if(isNormToOne[Number]){
   double xsec = h1[Number]->Integral();
   h1[Number]->Scale(1.0 / xsec);
 }
}

void Graph::AddText(int Number, const char* TextContent)
{
 if(Number == 0) {cout<<"WARNING!! Please add text from No.1"<<endl;}
 myText[Number] = TextContent;

 TextCount++;
}

void Graph::AddLine(int Number, double x1, double y1, double x2, double y2)
{
 if(Number == 0) {cout<<"WARNING!! Please add line from No.1"<<endl;}

 line[Number] = new TLine(x1, y1, x2, y2);
 line[Number]->SetLineStyle(9);
 line[Number]->SetLineWidth(4);

 LineCount++;
}

void Graph::AddCustomText(int Number, double x, double y, TString TextContent)
{
 if(Number == 0) {cout<<"WARNING!! Please add text from No.1"<<endl;}
 CustomText[Number] = TextContent;
 CustomTextX[Number] = x;
 CustomTextY[Number] = y;

 CustomTextCount++;
}

void Graph::Compare(TString Option, TString isNorm)
{
 if(isNorm == "Norm"){
   for(int i = 1; i <= FigureCount; i++){
     CustomNorm(1, i, 1);
   }
 }

 if(Option == "Ratio"){
   SetCustomPad(2);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   CustomSetting(2, 1, 2, "Divide");
   SetCustomPlotFormat(1, 1, kBlue);
   SetCustomPlotFormat(1, 2, kRed);
   SetCustomPlotFormat(2, 1, kBlack);
   SetCustomYRange(2, 0.8, 1.2);
 }
 if(Option == "Delta"){
   SetCustomPad(2);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   CustomSetting(2, 1, 2, "Minus");
   SetCustomPlotFormat(1, 1, kBlue);
   SetCustomPlotFormat(1, 2, kRed);
   SetCustomPlotFormat(2, 1, kBlack);
   SetCustomYRange(2, -0.5, 0.5);
 }
 if(Option == "Pull"){
   SetCustomPad(2);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   CustomSetting(2, 1, 2, "Pull");
   SetCustomPlotFormat(1, 1, kBlue);
   SetCustomPlotFormat(1, 2, kRed);
   SetCustomPlotFormat(2, 1, kBlack);
   SetCustomYRange(2, -0.5, 0.5);
 }
 if(Option == "Simple"){
   SetCustomPad(1);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   SetCustomPlotFormat(1, 1, kBlue);
   SetCustomPlotFormat(1, 2, kRed);
 }
 if(Option == "MultiPull"){
   SetCustomPad(2);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     CustomSetting(2, 1, i, "Pull");
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlotFormat(2, i, myColor[i]);
   }
   SetCustomYRange(2, -0.5, 0.5);
 }
 if(Option == "MultiDelta"){
   SetCustomPad(2);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     CustomSetting(2, 1, i, "Minus");
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlotFormat(2, i, myColor[i]);
     SetCustomPlot(1, i, "AC");
   }
   SetCustomYRange(2, -0.5, 0.5);
 }
 if(Option == "MultiRatio"){
   SetCustomPad(2);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     CustomSetting(2, 1, i, "Divide");
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlotFormat(2, i, myColor[i]);
     SetCustomPlot(1, i, "AC");
   }
   SetCustomYRange(2, 0.5, 1.5);
 }
 if(Option == "MultiSimple"){
   SetCustomPad(1);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlot(1, i, "AC");
   }
 }
 if(Option == "PDF21"){
   //SetPlot("AL");
   SetCustomPad(1);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   SetCustomPlotFormat(1, 1, kBlue, 8, true);
   SetCustomPlotFormat(1, 2, kRed, 8, false);
   SetCustomPlot(1, 1, "E2");
   SetCustomPlot(1, 2, "AL");
 }

}

void Graph::Draw()
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 TPad *pad1;
 TPad *pad2;
 TPad *pad3;

 if(isCustom){
   MyN = new TCanvas("MyN","MyN", CanvasX,CanvasY);
   MyN->cd();
   if(isLogX) gPad->SetLogx();
   gStyle->SetGridWidth(1);

   if(TotalPadNumber == 1){
     pad1 = new TPad("pad1", "pad1", 0.0, CustomPadYMin[1], 1.0, CustomPadYMax[1]);
     CustomMultiGraph[1] = new TMultiGraph();

     for(int ilimit = 1; ilimit <= 4; ilimit++){
       //CustomMultiGraph[1]->Add(CustomLimit[1][ilimit], "AP");
     }

     BottomMargin = CustomBottomMargin[1];
     TopMargin = CustomTopMargin[1];
     LeftMargin = CustomLeftMargin[1];
     RightMargin = CustomRightMargin[1];
     pad1->SetBottomMargin(BottomMargin);
     pad1->SetTopMargin(TopMargin);
     pad1->SetLeftMargin(LeftMargin);
     pad1->SetRightMargin(RightMargin);
     pad1->Draw();
     pad1->cd();

     if(isLogX) gPad->SetLogx();

     Custom[1][1]->SetTitle("");
     //Custom[1][1]->SetStats(0);

     Custom[1][1]->GetXaxis()->SetTitle(myXTitle);
     Custom[1][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[1]);
     Custom[1][1]->GetXaxis()->SetTitleFont(132);
     Custom[1][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[1]);

     Custom[1][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[1]);
     Custom[1][1]->GetXaxis()->SetLabelFont(132);

     Custom[1][1]->GetYaxis()->SetTitle(myYTitle);
     Custom[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
     Custom[1][1]->GetYaxis()->SetTitleFont(132);
     Custom[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);

     Custom[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
     Custom[1][1]->GetYaxis()->SetLabelFont(132);

     //Custom[1][1]->Draw(CustomPlot[1][1]);

     if(isCustomGrid[1]) pad1->SetGridx();
     if(isCustomGrid[1]) pad1->SetGridy();

     gStyle->SetHatchesLineWidth(2);

     YRangeMax = Custom[1][1]->GetHistogram()->GetMaximum();
     YRangeMin = Custom[1][1]->GetHistogram()->GetMinimum();
     if(!isSetXRange){
       //XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(Custom[1][1]->GetN());
       //XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
       XRangeMax = Custom[1][1]->GetXaxis()->GetXmax();
       XRangeMin = Custom[1][1]->GetXaxis()->GetXmin();
     }

     Custom[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);

     CustomMultiGraph[1]->Add(Custom[1][1], CustomPlot[1][1]);

     if(isLogY){
       //Custom[1][1]->SetMinimum();
     }

     int iPlot = 2;
     while(iPlot <= CustomFigureCount[1]){
      //if(isLogY) Custom[1][iPlot]->SetMinimum();
      //Custom[1][iPlot]->Draw((CustomPlot[1][iPlot] + " same").Data());
      Custom[1][iPlot]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
      CustomMultiGraph[1]->Add(Custom[1][iPlot], CustomPlot[1][iPlot]);
      if(YRangeMax < Custom[1][iPlot]->GetHistogram()->GetMaximum()) YRangeMax = Custom[1][iPlot]->GetHistogram()->GetMaximum();
      if(YRangeMin > Custom[1][iPlot]->GetHistogram()->GetMinimum()) YRangeMin = Custom[1][iPlot]->GetHistogram()->GetMinimum();
      if(isSetXRange) Custom[1][iPlot]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
      if(isSetXRange) Custom[1][iPlot]->GetXaxis()->SetLimits(XRangeMin, XRangeMax);
      iPlot++;
     }
     CustomMultiGraph[1]->Draw(CustomPlot[1][1]);
     CustomMultiGraph[1]->GetYaxis()->SetTitle(myYTitle);
     CustomMultiGraph[1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
     CustomMultiGraph[1]->GetYaxis()->SetTitleFont(132);
     CustomMultiGraph[1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);
     CustomMultiGraph[1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
     CustomMultiGraph[1]->GetYaxis()->SetLabelFont(132);
     CustomMultiGraph[1]->GetYaxis()->SetNdivisions(CustomYNdivisions[1]);

     //CustomMultiGraph[1]->GetXaxis()->SetNdivisions(CustomXNdivisions[1]);
     CustomMultiGraph[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->GetXaxis()->SetTitle(myXTitle);
     CustomMultiGraph[1]->GetXaxis()->SetTitleSize(CustomXTitleSize[1]);
     CustomMultiGraph[1]->GetXaxis()->SetTitleFont(132);
     CustomMultiGraph[1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[1]);
     CustomMultiGraph[1]->GetXaxis()->SetLabelSize(CustomXLabelSize[1]);
     CustomMultiGraph[1]->GetXaxis()->SetLabelFont(132);
     if(isSetCustomYRange[1]) CustomMultiGraph[1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);

     if(isLogY) pad1->SetLogy();
     if(isLogY) MyN->SetLogy();

     if(!isSetCustomYRange[1]){
       if(!isLogY) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.3, YRangeMax + fabs(YRangeMax) * 0.3);
//       if(!isLogY){
//         Custom[1][1]->SetMinimum(YRangeMin - fabs(YRangeMin) * 0.3);
//         Custom[1][1]->SetMaximum(YRangeMax + fabs(YRangeMax) * 0.3);
//       }
       CustomYRangeMin[1] = YRangeMin - fabs(YRangeMin) * 0.3;
       CustomYRangeMax[1] = YRangeMax + fabs(YRangeMax) * 0.3;
     }

     if(isLogY){
       if(CustomYRangeMin[1] < 0.0) CustomYRangeMin[1] = 1e-1;
     }

     if(isSetXRange) Custom[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
//     if(isSetCustomYRange[1]){
       Custom[1][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);
//       Custom[1][1]->SetMinimum(CustomYRangeMin[1]);
//       Custom[1][1]->SetMaximum(CustomYRangeMax[1]);

       if(CustomYRangeMin[1] < 0.0){
         YRangeMin = CustomYRangeMin[1] / 1.3;
       }
       if(CustomYRangeMin[1] >= 0.0){
         YRangeMin = CustomYRangeMin[1] / 0.7;
       }
       if(CustomYRangeMax[1] < 0.0){
         YRangeMax = CustomYRangeMax[1] / 0.7;
       }
       if(CustomYRangeMax[1] >= 0.0){
         YRangeMax = CustomYRangeMax[1] / 1.3;
       }
//     }

     CustomMultiGraph[1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);

     gPad->Modified();
     CustomMultiGraph[1]->GetXaxis()->SetLimits(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->SetMinimum(CustomYRangeMin[1]);
     CustomMultiGraph[1]->SetMaximum(CustomYRangeMax[1]);
     MyN->Update();
     MyN->Modified();

     cout<<"YRangeMin: "<<YRangeMin<<" YRangeMax: "<<YRangeMax<<endl;
     cout<<"XRangeMin: "<<XRangeMin<<" XRangeMax: "<<XRangeMax<<endl;

     double textlength = (legendymax - legendymin) / (CustomFigureCount[1] / LegendNColumns);
     int iText = 1;
     while(iText<=TextCount){
       text[iText] = new TLatex();
//       text[iText] = new TMathText();

       TextX = XRangeMin + (XRangeMax - XRangeMin) * (legendxmin - TextLeftBias);
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * (legendxmin - TextLeftBias)));

       if(isRightAlign){
         TextX = XRangeMin + (XRangeMax - XRangeMin) * (legendxmin - myText[iText].Length() / 63.0);
         if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * (legendxmin - myText[iText].Length() / 63.0)));
       }

       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1 - legendymax) + iText * textlength);
       if(isLogY) TextY = pow(10, (log10(1.3 * YRangeMax) - ((log10(1.3 * YRangeMax) - log10(0.7 * YRangeMin)) * ((1 - legendymax) + iText * textlength))));
       text[iText]->SetText(TextX, TextY, myText[iText]);
       text[iText]->SetTextSize(CustomLegendSize[1]);
       if(isSetCustomTextSize[iText]){
         text[iText]->SetTextSize(CustomTextSize[iText]);
       }
       text[iText]->SetTextFont(72);
       text[iText]->Draw("same");
       iText++;
       cout<<log10(XRangeMin)<<" "<<(log10(XRangeMax) - log10(XRangeMin))<<" "<<endl;
       cout<<TextX<<" "<<TextY<<endl;
     }

     int iLine = 1;
     while(iLine <= LineCount){
       line[iLine]->Draw("same");
       iLine++;
     }

     int iCustomText = 1;
     while(iCustomText <= CustomTextCount){
       TText* text = new TLatex();
       text->SetText(CustomTextX[iCustomText], CustomTextY[iCustomText], CustomText[iCustomText]);
       text->SetTextSize(CustomLegendSize[1]);
       text->SetTextFont(42);
       text->Draw("same");
       iCustomText++;
     }

     double steplength = legendymax - legendymin;
     legendymax = legendymax - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] / LegendNColumns)) * steplength;
     legendymin = legendymin - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] / LegendNColumns)) * steplength;

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i <= CustomFigureCount[1]; i++){
       if(!((TString)myCustomLegendName[1][i] == "")){
         if(CustomPlot[1][i] == "AC" || CustomPlot[1][i] == "L"){
           TList *funcList = Custom[1][i]->GetListOfFunctions();
           if(funcList && funcList->GetSize() > 0){
             legend1->AddEntry(dynamic_cast<TF1*>(Custom[1][i]->GetListOfFunctions()->At(0)), myCustomLegendName[1][i],"l");
           }
           else{
             legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"l");
           }
         }

         if(CustomPlot[1][i] == "AP") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"p");
         if(CustomPlot[1][i].Contains("A3")) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i], CustomLegendType[1][i]);
         if(CustomPlot[1][i] == "AFL") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"f");
       }
       //if((TString)myCustomLegendName[1][i] == "") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i]);
     }
     legend1->SetNColumns(LegendNColumns);
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(CustomLegendSize[1]);
     legend1->SetTextFont(132);

   }

   if(TotalPadNumber == 2){
     pad1 = new TPad("pad1", "pad1", 0, CustomPadYMin[1], 1.0, CustomPadYMax[1]);
     CustomMultiGraph[1] = new TMultiGraph();

     BottomMargin = CustomBottomMargin[1];
     TopMargin = CustomTopMargin[1];
     LeftMargin = CustomLeftMargin[1];
     RightMargin = CustomRightMargin[1];
     pad1->SetBottomMargin(BottomMargin);
     pad1->SetTopMargin(TopMargin);
     pad1->SetLeftMargin(LeftMargin);
     pad1->SetRightMargin(RightMargin);
     pad1->Draw();
     pad1->cd();

     if(isLogX) gPad->SetLogx();

     Custom[1][1]->SetTitle("");
     //Custom[1][1]->SetStats(0);

     Custom[1][1]->GetYaxis()->SetTitle(myYTitle);
     Custom[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
     Custom[1][1]->GetYaxis()->SetTitleFont(132);
     Custom[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);

     Custom[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
     Custom[1][1]->GetYaxis()->SetLabelFont(132);

     //Custom[1][1]->Draw(CustomPlot[1][1]);
     CustomMultiGraph[1]->Add(Custom[1][1]);

     gStyle->SetHatchesLineWidth(2);

     YRangeMax = Custom[1][1]->GetHistogram()->GetMaximum();
     YRangeMin = Custom[1][1]->GetHistogram()->GetMinimum();
     if(!isSetXRange){
       XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(Custom[1][1]->GetN());
       XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
     }

     if(isLogY){
       Custom[1][1]->SetMinimum();
     }

     int iPlot = 2;
     while(iPlot <= CustomFigureCount[1]){
      if(isLogY) Custom[1][iPlot]->SetMinimum();
      //Custom[1][iPlot]->Draw((CustomPlot[1][iPlot] + " same").Data());
      CustomMultiGraph[1]->Add(Custom[1][iPlot]);
      if(YRangeMax < Custom[1][iPlot]->GetHistogram()->GetMaximum()) YRangeMax = Custom[1][iPlot]->GetHistogram()->GetMaximum();
      if(YRangeMin > Custom[1][iPlot]->GetHistogram()->GetMinimum()) YRangeMin = Custom[1][iPlot]->GetHistogram()->GetMinimum();
      if(isSetXRange) Custom[1][iPlot]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
      if(isSetXRange) Custom[1][iPlot]->GetXaxis()->SetLimits(XRangeMin, XRangeMax);
      if(!isSetXRange){
        if(XRangeMax < Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetN())) XRangeMax = Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetN());
        if(XRangeMin > Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1);
      }
      iPlot++;
     }
     CustomMultiGraph[1]->Draw(CustomPlot[1][1]);
     CustomMultiGraph[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->GetYaxis()->SetTitle(myYTitle);
     CustomMultiGraph[1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
     CustomMultiGraph[1]->GetYaxis()->SetTitleFont(132);
     CustomMultiGraph[1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);
     CustomMultiGraph[1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
     CustomMultiGraph[1]->GetYaxis()->SetLabelFont(132);
     if(isSetCustomYRange[1]) CustomMultiGraph[1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);
     if(isSetXRange) CustomMultiGraph[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);

     if(isLogX) gPad->SetLogx();
     if(isLogY) gPad->SetLogy();

     if(!isSetCustomYRange[1]){
       if(!isLogY) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.3, YRangeMax + fabs(YRangeMax) * 0.3);
       CustomYRangeMin[1] = YRangeMin - fabs(YRangeMin) * 0.3;
       CustomYRangeMax[1] = YRangeMax + fabs(YRangeMax) * 0.3;
     }

     if(isSetXRange) Custom[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[1]){
       if((!isLogY) || ((CustomYRangeMin[1] > 0) && (CustomYRangeMax[1]) > 0)){
          Custom[1][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);
       }
       if(CustomYRangeMin[1] < 0.0){
         YRangeMin = CustomYRangeMin[1] / 1.3;
       }
       if(CustomYRangeMin[1] >= 0.0){
         YRangeMin = CustomYRangeMin[1] / 0.7;
       }
       if(CustomYRangeMax[1] < 0.0){
         YRangeMax = CustomYRangeMax[1] / 0.7;
       }
       if(CustomYRangeMax[1] >= 0.0){
         YRangeMax = CustomYRangeMax[1] / 1.3;
       }
     }

     CustomMultiGraph[1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);

     gPad->Modified();
     CustomMultiGraph[1]->GetXaxis()->SetLimits(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[1]->SetMinimum(CustomYRangeMin[1]);
     CustomMultiGraph[1]->SetMaximum(CustomYRangeMax[1]);
     MyN->Update();
     MyN->Modified();

     cout<<"YRangeMin: "<<YRangeMin<<" YRangeMax: "<<YRangeMax<<endl;
     cout<<"XRangeMin: "<<XRangeMin<<" XRangeMax: "<<XRangeMax<<endl;

     double textlength = (legendymax - legendymin) / (CustomFigureCount[1] / LegendNColumns);
     int iText = 1;
     while(iText<=TextCount){
       text[iText] = new TLatex();

       TextX = XRangeMin + (XRangeMax - XRangeMin) * (legendxmin);
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (0 - log10(XRangeMin)) * legendxmin));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1 - legendymax) + iText * textlength);
       text[iText]->SetText(TextX, TextY, myText[iText]);
       text[iText]->SetTextSize(CustomLegendSize[1]);
       text[iText]->SetTextFont(72);
       text[iText]->Draw("same");
       iText++;
       cout<<log10(XRangeMin)<<" "<<(log10(XRangeMax) - log10(XRangeMin))<<" "<<endl;
       cout<<TextX<<" "<<TextY<<endl;
     }

     double steplength = legendymax - legendymin;
     legendymax = legendymax - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] / LegendNColumns)) * steplength;
     legendymin = legendymin - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] / LegendNColumns)) * steplength;

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i < CustomFigureCount[1] + 1; i++){
       if(!((TString)myCustomLegendName[1][i] == "")){
         if(CustomPlot[1][i] == "AC" || CustomPlot[1][i] == "L"){
           TList *funcList = Custom[1][i]->GetListOfFunctions();
           if(funcList && funcList->GetSize() > 0){
             legend1->AddEntry(dynamic_cast<TF1*>(Custom[1][i]->GetListOfFunctions()->At(0)), myCustomLegendName[1][i],"l");
           }
           else{
             legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"l");
           }
         }

         if(CustomPlot[1][i] == "AP") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"p");
         if(CustomPlot[1][i].Contains("A3")) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i], CustomLegendType[1][i]);
         if(CustomPlot[1][i] == "AFL") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"f");
       }
       //if((TString)myCustomLegendName[1][i] == "") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i]);
//       if(!((TString)myCustomLegendName[1][i] == "")) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"pe");
//       if(!((TString)myCustomLegendName[1][i] == "")) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lpfe");
     }

     legend1->SetNColumns(1);
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(CustomLegendSize[1]);
     legend1->SetTextFont(132);

     MyN->cd();
     pad2 = new TPad("pad2", "pad2", 0, CustomPadYMin[2], 1, CustomPadYMax[2]);
     CustomMultiGraph[2] = new TMultiGraph();

     BottomMargin = CustomBottomMargin[2];
     TopMargin = CustomTopMargin[2];
     LeftMargin = CustomLeftMargin[2];
     RightMargin = CustomRightMargin[2];
     pad2->SetBottomMargin(BottomMargin);
     pad2->SetTopMargin(TopMargin);
     pad2->SetLeftMargin(LeftMargin);
     pad2->SetRightMargin(RightMargin);
     if(isCustomGrid[2]) pad2->SetGridx();
     if(isCustomGrid[2]) pad2->SetGridy();
     pad2->Draw();
     pad2->cd();

     Custom[2][1]->SetTitle("");
     //Custom[2][1]->SetStats(0);

     Custom[2][1]->GetYaxis()->SetNdivisions(CustomNdivisions[2]);

     YRangeMax = Custom[2][1]->GetHistogram()->GetMaximum();
     YRangeMin = Custom[2][1]->GetHistogram()->GetMinimum();
     iPlot = 2;
     while(iPlot <= CustomFigureCount[2]){
       if(YRangeMax < Custom[2][iPlot]->GetHistogram()->GetMaximum()) YRangeMax = Custom[2][iPlot]->GetHistogram()->GetMaximum();
       if(YRangeMin > Custom[2][iPlot]->GetHistogram()->GetMinimum()) YRangeMin = Custom[2][iPlot]->GetHistogram()->GetMinimum();
       iPlot++;
     }

     if(isSetXRange) Custom[2][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(!isSetXRange){
       XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(Custom[2][1]->GetN());
       XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
     }
     if(!isSetCustomYRange[2]) Custom[2][1]->GetYaxis()->SetRangeUser(YRangeMin * 0.7, YRangeMax * 1.3);
     if(isSetCustomYRange[2]) Custom[2][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[2], CustomYRangeMax[2]);

     Custom[2][1]->GetYaxis()->SetTitle(myPadName[2]);
     Custom[2][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[2]);
     Custom[2][1]->GetYaxis()->SetTitleFont(132);
     Custom[2][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[2]);

     Custom[2][1]->GetYaxis()->SetLabelFont(132);// Absolute font size in pixel (precision 3)
     Custom[2][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[2]);

//     Custom[2][1]->SetLineWidth(2);

//     Custom[2][1]->GetXaxis()->SetTitle(myXTitle);
//     Custom[2][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[2]);
//     Custom[2][1]->GetXaxis()->SetTitleFont(32);
//     Custom[2][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[2]);

//     Custom[2][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[2]);
//     Custom[2][1]->GetXaxis()->SetLabelFont(132);


     //Custom[2][1]->Draw(CustomPlot[2][1]);
     CustomMultiGraph[2]->Add(Custom[2][1]);

     iPlot = 2;
     while(iPlot <= CustomFigureCount[2]){
      //Custom[2][iPlot]->Draw((CustomPlot[2][iPlot] + " same").Data());
      CustomMultiGraph[2]->Add(Custom[2][iPlot]);
      iPlot++;
     }
     pad2->cd();
     CustomMultiGraph[2]->Draw(CustomPlot[2][1]);
     CustomMultiGraph[2]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[2]->GetYaxis()->SetLabelFont(132);// Absolute font size in pixel (precision 3)
     CustomMultiGraph[2]->GetYaxis()->SetLabelSize(CustomYLabelSize[2]);
     CustomMultiGraph[2]->GetYaxis()->SetNdivisions(CustomYNdivisions[2]);
     CustomMultiGraph[2]->GetXaxis()->SetTitle(myXTitle);
     CustomMultiGraph[2]->GetXaxis()->SetTitleSize(CustomXTitleSize[2]);
     CustomMultiGraph[2]->GetXaxis()->SetTitleFont(132);
     CustomMultiGraph[2]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[2]);
     CustomMultiGraph[2]->GetXaxis()->SetLabelSize(CustomXLabelSize[2]);
     CustomMultiGraph[2]->GetXaxis()->SetLabelFont(132);
     if(isSetXRange) CustomMultiGraph[2]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[2]) CustomMultiGraph[2]->GetYaxis()->SetRangeUser(CustomYRangeMin[2], CustomYRangeMax[2]);

     if(isLogX) gPad->SetLogx();

     gPad->Modified();
     CustomMultiGraph[2]->GetXaxis()->SetLimits(XRangeMin, XRangeMax);
     CustomMultiGraph[2]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     CustomMultiGraph[2]->SetMinimum(CustomYRangeMin[2]);
     CustomMultiGraph[2]->SetMaximum(CustomYRangeMax[2]);
     MyN->Update();
     MyN->Modified();

     if(isDrawLegend2){
       legend2 = new TLegend(legend2xmin * (1 - LeftMargin - RightMargin) + LeftMargin, legend2ymin * (1 - TopMargin - BottomMargin) + BottomMargin, legend2xmax * (1 - LeftMargin - RightMargin) + LeftMargin, legend2ymax * (1 - TopMargin - BottomMargin) + BottomMargin);

       for(int i = 1; i < CustomFigureCount[2] + 1; i++){
         if(CustomPlot[2][i] == "AC" || CustomPlot[2][i] == "L"){
           TList *funcList = Custom[1][i]->GetListOfFunctions();
           if(funcList && funcList->GetSize() > 0){
             legend2->AddEntry(dynamic_cast<TF1*>(Custom[2][i]->GetListOfFunctions()->At(0)), myCustomLegendName[2][i],"l");
           }
           else{
             legend2->AddEntry(Custom[2][i], myCustomLegendName[2][i],"l");
           }
         }

         if(CustomPlot[2][i] == "AP") legend2->AddEntry(Custom[2][i], myCustomLegendName[2][i],"p");
         if(CustomPlot[2][i].Contains("A3")) legend2->AddEntry(Custom[2][i], myCustomLegendName[2][i], CustomLegendType[2][i]);
         if(CustomPlot[2][i] == "AFL") legend2->AddEntry(Custom[2][i], myCustomLegendName[2][i],"f");
       }

       legend2->SetNColumns(1);
       legend2->Draw("same");
       legend2->SetFillColor(0);
       legend2->SetFillStyle(0);
       legend2->SetLineColor(0);
       legend2->SetLineWidth(0);
       legend2->SetTextSize(CustomLegendSize[2]);
       legend2->SetTextFont(132);
     }

   }
 }

 if(DoSave) MyN->SaveAs(myFigureName);
// delete MyN;
}

