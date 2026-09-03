#include <iostream>
#include <TH1D.h>
#include <TROOT.h>
#include <TFile.h>
#include "TTree.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TF1.h>
#include "TH2D.h"
#include "THStack.h"
#include "TColor.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TMathText.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "png.h"
#include "pngconf.h"
#include "TLine.h"
#include "TArrow.h"

using namespace std;

class Figure
{
 public:

 TCanvas *MyN;
 TGaxis *axis1;

 TString myFigureName;
 TString myXTitle;
 TString myYTitle;

 TFile* file[100];
 TFile* PDFfile[100];
 TTree* tree[100];
 TH1D* h1[100];
 TH2D* h2[100];
 TF1* f1[100];
 TGraph* g1[100];
 TH1D* PDF1[100];
 TText* text[100];
 TMathText* mathtext[100];
 TText* CustomText[100];
 double CustomTextX[100];
 double CustomTextY[100];
 TMathText* CustomMathText[100];
 TGraph* graph[100];
 TStyle* myStyle[100];

 TH1D* tmph1[100];
 TH2D* tmph2[100];

 TLine* line[100];
 int LineCount = 0;

 TArrow* arrow[100];
 int ArrowCount = 0;

 TLegend *legend1;
 TLegend *legend2;
 TLegend *legend3;

 TString myLegendName[100];
 TString myCustomLegendName[10][100];
 TString myPDFLegendName[100];
 TString myText[100];
 TString myCustomText[100];
 int TextFont[100] = {132};
 TString PaintTextStyle[100];
 double HistBarOffset[100];
 int LegendNColumns = 1;
 int Legend2NColumns = 1;

 double legendxmin = 0.1;
 double legendxmax = 0.3;
 double legendymin = 0.6;
 double legendymax = 0.8;
 double legend2xmin = 0.1;
 double legend2xmax = 0.3;
 double legend2ymin = 0.6;
 double legend2ymax = 0.8;
 bool isDrawLegend2 = false;
 double TextX, TextY;
 double XRangeMin, XRangeMax, YRangeMin, YRangeMax;
 double BottomMargin, TopMargin, LeftMargin, RightMargin;
 double wmin, wmax;
 double ymin, ymax;

 double YTitleOffset = 1;

 double NumerPoint, DenomPoint, NumerError, DenomError;
 double DataPoint, DataError;

 double LegendTextSize;

 int ndiv;

 bool isSingle;
 bool isSingleRatio;
 bool isSimple;
 bool isRatio;
 bool isDelta;
 bool isDeltaSigma;
 bool isPDF;
 bool is2D;

 bool isInput;
 bool isInputPDFError;

 bool withPDFError;
 int Process;

 bool isHIST = false;
 bool isE0 = false;
 bool isE2 = false;
 bool isE3 = false;
 bool isE4 = false;
 bool isPMC = false;
 bool isPLC = false;

 bool isAddGaxis;

 bool isNorm;
 bool isLogX = false;
 bool isLogY = false;
 bool isXNoExponent = false;
 bool isMoreLogLabels = true;
 bool isEfficiency;

 bool isSetXRange;
 bool isSetYRange;
 bool isSetYRange0;

 bool isWsample;

 bool isRebin;
 int RebinType;
 double* rebin;
 int ngroup;

 bool DoSave;

 bool isDefineHist = false;

 bool isDivideBinWidth[500] = {false};
 bool isNormToOne[500] = {false};

 bool isHist[500] = {false};
 bool isFunction[500] = {false};
 bool isGraph[500] = {false};

 int FigureCount;
 int PDFFigureCount;
 int TextCount;
 int CustomTextCount;

 double PDFScaleFactor = 1.0;
 double PDFUncRangeMin;
 double PDFUncRangeMax;
 bool isSetPDFUncRange = false;

 int TotalPadNumber = 0;
 int CustomFigureCount[10] = {0};
 TH1D* Custom[10][500] = {0};
 TF1* CustomFunction[10][500] = {0};
 TGraph* CustomGraph[10][500] = {0};
 TMultiGraph* CustomMultiGraph[10] = {0};
 bool isCustomFunction[10][500] = {false};
 bool isCustomHist[10][500] = {false};
 bool isCustomGraph[10][500] = {false};
 bool isCustom = false;
 TString myPadName[10];
 TString CustomPlot[10][500];
 TString DrawStyle[100];
 bool isSetCustomYRange[10] = {0};
 double CustomYRangeMin[10];
 double CustomYRangeMax[10];
 double CustomLegendSize[10] = {0.04};
 double CustomXTitleSize[10] = {};
 double CustomXTitleOffset[10] = {};
 double CustomXLabelSize[10] = {};
 double CustomYTitleSize[10] = {};
 double CustomYTitleOffset[10] = {};
 double CustomYLabelSize[10] = {};

 int CustomNdivisions[10] = {1};

 double CustomBottomMargin[10] = {0.0};
 double CustomTopMargin[10] = {0.0};
 double CustomLeftMargin[10] = {0.0};
 double CustomRightMargin[10] = {0.0};

 double CustomPadYMax[10] = {0.0};
 double CustomPadYMin[10] = {0.0};
 double CustomPadXMax[10] = {0.0};
 double CustomPadXMin[10] = {0.0};

 bool isCustomGrid[10] = {true};

 map<pair<int, int>, Color_t> CustomColor;
 map<int, Color_t> myColor;

 TH1D* tmpHist[500];

 bool isFittingPlot = false;
 TFile* FittingFile;
 TF1* FittingPlot;

 TFile *ErrorFile[100];
 TH1D *HistError[100];
 bool isInputError = false;
 bool isResetError[10][500] = {0};
 TString ErrorLegendName[10];

 bool isOutput = false;

 double CanvasX = 1000.0;
 double CanvasY = 1000.0;

 Figure(const char* FigureName, const char* XTitle, const char* YTitle);
 virtual ~Figure();
 virtual void SetMode(const char* ModeName);
 virtual void SetPlot(const char* PlotMode);
 virtual void SetNorm();
 virtual void SetLogX();
 virtual void SetLogY();
 virtual void SetXNoExponent(){isXNoExponent = true;}
 virtual void SetMoreLogLabels(bool flag){isMoreLogLabels = flag;}
 virtual void SetEfficiency();
 virtual void SetWsample();
 virtual void DefineHist(int Number, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(int Number, TString name, TString title, int nbinx, double* xbins);
 virtual void DefineHist(int Number, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty);

 virtual void SetCustomPad(int TotalPadNumber);
 virtual void CustomSetting(int PadNumber, int histNumber1, int histNumber2 = 0, TString process = "");
 virtual void SetCustomPlotFormat(int PadNumber, int Number, Color_t Color, Style_t style = 8, bool isFilled = false);
 virtual void SetPadTitle(int PadNumber, const char* PadName);
 virtual void SetCustomYRange(int PadNumber, double ymin, double ymax);
 virtual void SetCustomLegendSize(int PadNumber, double size);
 virtual void SetCustomXTitleSize(int PadNumber, double size);
 virtual void SetCustomXTitleOffset(int PadNumber, double size);
 virtual void SetCustomXLabelSize(int PadNumber, double size);
 virtual void SetCustomYTitleSize(int PadNumber, double size);
 virtual void SetCustomYTitleOffset(int PadNumber, double size);
 virtual void SetCustomYLabelSize(int PadNumber, double size);
 virtual void SetCustomPadYPosition(int PadNumber, double ymin, double ymax);
 virtual void SetCustomPadXPosition(int PadNumber, double xmin, double xmax){this->CustomPadXMin[PadNumber] = xmin; this->CustomPadXMax[PadNumber] = xmax;};
 virtual void SetCustomMarkerSize(int PadNumber, int Number, double size);
 virtual void SetCustomLeftMargin(int PadNumber, double size){this->CustomLeftMargin[PadNumber] = size;};
 virtual void SetCustomRightMargin(int PadNumber, double size){this->CustomRightMargin[PadNumber] = size;};
 virtual void SetCustomNdivisions(int PadNumber, int ndiv);
 virtual void SetCustomGrid(int PadNumber, bool flag);
 virtual void SetCustomBarOffset(int PadNumber, int Number, double size);
 virtual void SetCustomLineStyle(int PadNumber, int Number, Style_t style);
 virtual void SetCustomLineWidth(int PadNumber, int Number, int width);
 virtual void DefineCustomHist(int Number, int histNumber1, int histNumber2 = 0, TString process = "", const char* LegendName = "");
 virtual void CustomNorm(int fig1, int fig2, int BaseOne = 1);
 virtual void SetCustomError(int PadNumber, int Number, int ErrorNumber, TString isFilled = "");
 virtual void AddFittingPlot(TString rootName, TString FittingName);
 virtual void IgnoreCustomError(int PadNumber, int Number);
 virtual void SetCustomPlot(int PadNumber, int Number, TString format);
 virtual void SetCanvasSize(double X, double Y){this->CanvasX = X; this->CanvasY = Y;};

 virtual void SetPaintTextStyle(int Number, TString style);
 virtual void SetBarOffset(int Number, double size);
 virtual void Define2DTextStyle(int Number);

 bool isSetPaintRange = false;
 double PaintMin = 0.0;
 double PaintMax = 1.0;
 virtual void SetPaintRange(double zmin, double zmax){
   isSetPaintRange = true;
   PaintMin = zmin;
   PaintMax = zmax;
 }

 virtual void Input(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName = "");
 virtual void Input2Dx(int Number, const char* rootName, const char* histName, int biny1, int biny2, const char* legendName = "");
 virtual void Input2Dy(int Number, const char* rootName, const char* histName, int binx1, int binx2, const char* legendName = "");
 virtual void Input3D(int Number, const char* rootName, const char* histName, int binx, int biny, int binz, const char* legendName = "");
 virtual void Input3Dyz(int Number, const char* rootName, const char* histName, int binx1, int binx2, const char* legendName = "");
 virtual void Input3Dx(int Number, const char* rootName, const char* histName, int biny1, int biny2, int binz1, int binz2, const char* legendName = "");
 virtual void Input3Dy(int Number, const char* rootName, const char* histName, int binx1, int binx2, int binz1, int binz2, const char* legendName = "");
 virtual void Input3Dz(int Number, const char* rootName, const char* histName, int binx1, int binx2, int biny1, int biny2, const char* legendName = "");
 virtual void InputError(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void ResetError(int Number, int ErrorNumber);
 virtual void Input2DError(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName = "");
 virtual void InputTGraph(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void InputTree(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName = "");
 virtual void Input(int Number, TH1D* h, const char* legendName = "");
 virtual void Input(int Number, TH2D* h, const char* legendName = "");
 virtual void InputTF1(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void InputEnsemble(int Number1, int Number2, int Number3, const char* rootName, const char* treeName, const char* branchName, const char* legendName = "");
 virtual void NormToOne(int Number);
 virtual void NormToOne(int Number, int FirstBin, int LastBin);
 virtual void ScalePlot(int Number, double scale);

 virtual void InputPDFError(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void AddText(int Number, const char* TextContent);
 virtual void AddLine(int Number, double x1, double y1, double x2, double y2);
 virtual void AddArrow(int Number, double x1, double y1, double x2, double y2, TString format, Color_t Color);
 virtual void AddCustomText(int Number, double x1, double y1, TString TextContent);

 virtual void SetProcess(int Process);
 virtual void SetPlotFormat(int Number, Color_t Color, Style_t style = 7);
 virtual void SetPDFPlotFormat(int Number, Color_t Color, Style_t style = 7);
 virtual void DivideBinWidth(int Number);
 virtual void FigureNorm(int Number);
 virtual void PDFScale(double PDFScaleFactor);
 virtual void SetPDFUncRange(double ymin, double ymax);
 virtual void SetXRange(double xmin, double xmax);
 virtual void SetYRange(double ymin, double ymax, int iPlot = 1);
 virtual void SetBaseLine(int Number);
 virtual void SetMultiRatio(int Number);
 virtual void SetMultiDeltaSigma(int Number);
 virtual void Divide(int numer, int denom);
 virtual void Output();
 virtual void Draw();
 virtual void DrawCorrelation(const char* fileName, const char* histName);
 virtual void AddGaxis(double wmin, double wmax, int ndiv);
 virtual void SaveFigure();
 virtual void Rebin(int Nbin, double* xbins);
 virtual void Rebin(int Nbin);
 virtual void SetLegendPosition(double xmin, double ymin, double xmax, double ymax);
 virtual void SetLegend2Position(double xmin, double ymin, double xmax, double ymax);
 virtual void SetLegendTextSize(double LegendTextSize);
 virtual void SetLegendNColumns(int n){this->LegendNColumns = n;};
 virtual void SetLegend2NColumns(int n){this->Legend2NColumns = n;};
 virtual void SetYTitleOffset(double offset);
 virtual void Compare(TString Option, TString isNorm = "");
 virtual void SetTextFont(int Number, int Font){TextFont[Number] = Font;};

 virtual double CalculateChi2(TH1D* h1, TH1D* h2);
};

Figure::Figure(const char* FigureName, const char* XTitle, const char* YTitle)
{
 FigureCount = 0;
 PDFFigureCount = 0;
 TextCount = 0;
 CustomTextCount = 0;

 isSingle = false;
 isSingleRatio = false;
 isSimple = false;
 isRatio = false;
 isDelta = false;
 isDeltaSigma = false;
 isPDF = false;
 is2D = false;

 isInput = false;
 isInputPDFError = false;

 withPDFError = false;
 Process = 0;

 isHIST = false;
 isE0 = false;

 isAddGaxis = false;

 isNorm = false;
 isLogX = false;
 isEfficiency = false;

 isSetXRange = false;
 isSetYRange = false;
 isSetYRange0 = false;

 isWsample = false;

 isRebin = false;
 RebinType = 0;

 DoSave = false;

 LegendTextSize = 0.04;

 myFigureName = FigureName;
 myXTitle = XTitle;
 myYTitle = YTitle;

// SetMode("CUSTOM");
 SetPlot("E0");
 SaveFigure();

 PaintTextStyle[1] = "6.2f";

 for(int i = 0; i < 10; i++){
   myStyle[i] = new TStyle((TString)"Style" + (int)i, (TString)"Style" + (int)i);
   myStyle[i]->SetTextFont(132);
   myStyle[i]->SetHatchesLineWidth(2);
   myStyle[i]->SetStatStyle(0);
   myStyle[i]->SetStatX(0);
   myStyle[i]->SetStatY(0);
   SetTextFont(i, 132);
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

}

Figure::~Figure()
{
}

void Figure::SetMode(const char* ModeName)
{
 TString myMode = ModeName;
 if(myMode == "SINGLE") isSingle = true;
 if(myMode == "SINGLERATIO") isSingleRatio = true;
 if(myMode == "SIMPLE") isSimple = true;
 if(myMode == "RATIO") isRatio = true;
 if(myMode == "DELTA") isDelta = true;
 if(myMode == "DELTASIGMA") isDeltaSigma = true;
 if(myMode == "PDF") isPDF = true;
 if(myMode == "2DFIGURE") {is2D = true; isSingle = true;}
 if(myMode == "CUSTOM") isCustom = true;
}

void Figure::SetPlot(const char* PlotMode)
{
 TString myPlotMode = PlotMode;
 isHIST = false;
 isE0 = false;
 isE2 = false;
 isE3 = false;
 isE4 = false;
 isPMC = false;
 isPLC = false;
 if(myPlotMode == "HIST"){
   isHIST = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "HIST";
     }
   }
 }
 else if(myPlotMode == "E0"){
   isE0 = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "E0";
     }
   }
 }
 else if(myPlotMode == "E2"){
   isE2 = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "E2";
     }
   }
 }
 else if(myPlotMode == "E3"){
   isE3 = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "E3";
     }
   }
 }
 else if(myPlotMode == "E4"){
   isE4 = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "E4";
     }
   }
 }
 else if(myPlotMode == "PMC"){
   isPMC = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "P";
     }
   }
 }
 else if(myPlotMode == "PLC"){
   isPLC = true;
   for(int i = 0; i < 4; i++){
     for(int j = 0; j < 50; j++){
       CustomPlot[i][j] = "L";
     }
   }
 }

}

void Figure::SetNorm()
{
 isNorm = true;
}

void Figure::SetLogX()
{
 isLogX = true;
}

void Figure::SetLogY()
{
 isLogY = true;
}

void Figure::SetEfficiency()
{
 isEfficiency = true;
}

void Figure::SetWsample()
{
 isWsample = true;
}

void Figure::SaveFigure()
{
 DoSave = true;
}

void Figure::Rebin(int Nbin)
{
 isRebin = true;
 RebinType = 1;
 ngroup = Nbin;
}

void Figure::Rebin(int Nbin, double* xbins)
{
 isRebin = true;
 RebinType = 2;
 rebin = xbins;
 ngroup = Nbin;
}

void Figure::SetLegendPosition(double xmin, double ymin, double xmax, double ymax)
{
 legendxmin = xmin;
 legendxmax = xmax;
 legendymin = ymin;
 legendymax = ymax;
}

void Figure::SetLegend2Position(double xmin, double ymin, double xmax, double ymax)
{
 isDrawLegend2 = true;

 legend2xmin = xmin;
 legend2xmax = xmax;
 legend2ymin = ymin;
 legend2ymax = ymax;
}

void Figure::SetLegendTextSize(double LegendTextSize)
{
 this->LegendTextSize = LegendTextSize;
}

void Figure::SetYTitleOffset(double offset)
{
 YTitleOffset = offset;
}

void Figure::Output()
{
 //if(!isInput) {cout<<"There is no input file."<<endl; return;}

 isOutput = true;
/* for(int i = 1; i < FigureCount + 1; i++)
 {
  for(int ibin = 0; ibin < h1[i]->GetNbinsX(); ibin++)
  {
   if(isE0) cout<<(h1[i]->GetBinCenter(ibin+1) - h1[i]->GetBinWidth(ibin+1) / 2)<<"~"<<(h1[i]->GetBinCenter(ibin+1) + h1[i]->GetBinWidth(ibin+1) / 2)<<"  "<<h1[i]->GetBinContent(ibin+1)<<"  "<<h1[i]->GetBinError(ibin+1)<<endl;

   if(isHIST) cout<<(h1[i]->GetBinCenter(ibin+1) - h1[i]->GetBinWidth(ibin+1) / 2)<<"~"<<(h1[i]->GetBinCenter(ibin+1) + h1[i]->GetBinWidth(ibin+1) / 2)<<"  "<<h1[i]->GetBinContent(ibin+1)<<endl;
  }
 }
*/
}

void Figure::DefineHist(int Number, TString name, TString title, int nbin, double left, double right)
{
 isDefineHist = true;
 h1[Number] = new TH1D(name, title, nbin, left, right);

 isRebin = false;
}

void Figure::DefineHist(int Number, TString name, TString title, int nbinx, double* xbins)
{
 isDefineHist = true;
 h1[Number] = new TH1D(name, title, nbinx, xbins);

 isRebin = false;
}

void Figure::DefineHist(int Number, TString name, TString title, int nbinx, double leftx, double rightx, int nbiny, double lefty, double righty)
{
 isDefineHist = true;
 h2[Number] = new TH2D(name, title, nbinx, leftx, rightx, nbiny, lefty, righty);

 isRebin = false;
}

void Figure::SetCustomPad(int TotalPadNumber)
{
 if(!isCustom){
   cout<<"Please set mode to CUSTOM"<<endl;
   return;
 }

 this->TotalPadNumber = TotalPadNumber;

 if(TotalPadNumber == 1){
   CustomXTitleSize[1] = 0.042;
   CustomXTitleOffset[1] = 1.2;
   CustomXLabelSize[1] = 0.04;
   CustomYTitleSize[1] = 0.05;
   CustomYTitleOffset[1] = 1.4;
   CustomYLabelSize[1] = 0.05;
   CustomLegendSize[1] = 0.045;
   CustomBottomMargin[1] = 0.15;
   CustomTopMargin[1] = 0.05;
   CustomLeftMargin[1] = 0.15;
   CustomRightMargin[1] = 0.05;
   CustomPadYMax[1] = 1.0;
   CustomPadYMin[1] = 0.01;
   CanvasX = 1000.0;
   CanvasY = 800.0;

   CustomNdivisions[1] = 505;
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

   CustomXTitleSize[2] = 0.12;
   CustomXTitleOffset[2] = 1;
   CustomXLabelSize[2] = 0.13;
   CustomYTitleSize[2] = 0.12;
   CustomYTitleOffset[2] = 0.4;
   CustomYLabelSize[2] = 0.12;
   CustomLegendSize[2] = 0.08;
   CustomBottomMargin[2] = 0.3;
   CustomTopMargin[2] = 0.0;
   CustomLeftMargin[2] = 0.15;
   CustomRightMargin[2] = 0.05;
   CustomPadYMax[2] = 0.25;
   CustomPadYMin[2] = 0.0;

   CustomNdivisions[1] = 505;
   CustomNdivisions[2] = 505;

   isCustomGrid[2] = true;

   CanvasX = 1000.0;
   CanvasY = 1000.0;
 }
 if(TotalPadNumber == 3){
   CustomYTitleSize[1] = 0.06;
   CustomYTitleOffset[1] = 0.8;
   CustomYLabelSize[1] = 0.04;
   CustomLegendSize[1] = 0.05;
   CustomBottomMargin[1] = 0.0;
   CustomTopMargin[1] = 0.15;
   CustomLeftMargin[1] = 0.15;
   CustomRightMargin[1] = 0.05;
   CustomPadYMax[1] = 1.0;
   CustomPadYMin[1] = 0.3;

   CustomXTitleSize[2] = 0.12;
   CustomXTitleOffset[2] = 1;
   CustomXLabelSize[2] = 0.12;
   CustomYTitleSize[2] = 0.2;
   CustomYTitleOffset[2] = 0.21;
   CustomYLabelSize[2] = 0.2;
   CustomLegendSize[2] = 0.025;
   CustomBottomMargin[2] = 0.0;
   CustomTopMargin[2] = 0.0;
   CustomLeftMargin[2] = 0.15;
   CustomRightMargin[2] = 0.05;
   CustomPadYMax[2] = 0.3;
   CustomPadYMin[2] = 0.18;

   CustomXTitleSize[3] = 0.15;
   CustomXTitleOffset[3] = 1;
   CustomXLabelSize[3] = 0.15;
   CustomYTitleSize[3] = 0.14;
   CustomYTitleOffset[3] = 0.31;
   CustomYLabelSize[3] = 0.15;
   CustomLegendSize[3] = 0.025;
   CustomBottomMargin[3] = 0.35;
   CustomTopMargin[3] = 0.0;
   CustomLeftMargin[3] = 0.15;
   CustomRightMargin[3] = 0.05;
   CustomPadYMax[3] = 0.18;
   CustomPadYMin[3] = 0.0;

   CustomNdivisions[1] = 505;
   CustomNdivisions[2] = 505;
   CustomNdivisions[3] = 505;

   isCustomGrid[2] = true;
   isCustomGrid[3] = true;

   CanvasX = 1000.0;
   CanvasY = 1000.0;
 }

}

//DefineCustomHist
void Figure::DefineCustomHist(int Number, int histNumber1, int histNumber2, TString process, const char* LegendName)
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
 if((TString)process == "Quadrature"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     tmpHist[Number]->SetBinContent(ibin, sqrt(h1[histNumber1]->GetBinContent(ibin) * h1[histNumber1]->GetBinContent(ibin) + h1[histNumber2]->GetBinContent(ibin) * h1[histNumber2]->GetBinContent(ibin)));
   }
 }
 if((TString)process == "InheritError"){
   for(int ibin = 1; ibin <= tmpHist[Number]->GetNbinsX(); ibin++){
     tmpHist[Number]->SetBinError(ibin, h1[histNumber2]->GetBinError(ibin));
   }
 }
 if((TString)process == "CombineError"){
   for(int ibin = 1; ibin <= tmpHist[Number]->GetNbinsX(); ibin++){
     double Error1 = tmpHist[Number]->GetBinError(ibin);
     double Error2 = h1[histNumber2]->GetBinError(ibin);
     double Error = sqrt(Error1 * Error1 + Error2 * Error2);
     tmpHist[Number]->SetBinError(ibin, Error);
   }
 }

 myLegendName[Number] = LegendName;

 int tmpNumber = Number;
 if(tmpNumber <= FigureCount) return;
 h1[tmpNumber] = (TH1D *)tmpHist[Number]->Clone((TString)"tmp_" + (int)Number);

 isHist[tmpNumber] = true;

 FigureCount++;

 if((TString)process == "") return;

}

//CustomSetting
void Figure::CustomSetting(int PadNumber, int histNumber1, int histNumber2, TString process)
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

 CustomFigureCount[PadNumber]++;

 int Number = CustomFigureCount[PadNumber];

 if(isHist[histNumber1]){
   Custom[PadNumber][Number] = (TH1D *)h1[histNumber1]->Clone((TString)"Custom_" + (int)PadNumber + (TString)"_" + (int)Number);
   isCustomHist[PadNumber][Number] = true;
 }
 if(isFunction[histNumber1]){
   CustomFunction[PadNumber][Number] = (TF1 *)f1[histNumber1]->Clone((TString)"CustomFunction_" + (int)PadNumber + (TString)"_" + (int)Number);

   isCustomFunction[PadNumber][Number] = true;
   if((TString)process != ""){
     cout<<"This is a function, no process setup."<<endl;
   }
 }
 if(isGraph[histNumber1]){
   CustomGraph[PadNumber][Number] = (TGraph *)g1[histNumber1]->Clone((TString)"CustomGraph_" + (int)PadNumber + (TString)"_" + (int)Number);
   isCustomGraph[PadNumber][Number] = true;
   CustomPlot[PadNumber][Number] = DrawStyle[histNumber1];
   if((TString)process != ""){
     cout<<"This is a Graph, no process setup."<<endl;
   }

 }

 myCustomLegendName[PadNumber][Number] = myLegendName[histNumber1];

 if((TString)process == "Plus"){
   Custom[PadNumber][Number]->Add(h1[histNumber2]);
 }
 if((TString)process == "Minus"){
   cout<<"Chi2 between hist "<<histNumber1<<" and hist "<<histNumber2<<": "<<CalculateChi2(h1[histNumber1], h1[histNumber2])<<endl;
   Custom[PadNumber][Number]->Add(h1[histNumber2], -1);
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     //Custom[PadNumber][Number]->SetBinError(ibin, 0);
   }
 }
 if((TString)process == "Divide"){
   cout<<"Chi2 between hist "<<histNumber1<<" and hist "<<histNumber2<<": "<<CalculateChi2(h1[histNumber1], h1[histNumber2])<<endl;
   //Custom[PadNumber][Number]->Divide(h1[histNumber2]);
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     double Numer = Custom[PadNumber][Number]->GetBinContent(ibin);
     double Denom = h1[histNumber2]->GetBinContent(ibin);
     double NumerError = Custom[PadNumber][Number]->GetBinError(ibin);
     double DenomError = h1[histNumber2]->GetBinError(ibin);
     double Value = 0.0;
     if(fabs(Denom) > 1e-9) Value = Numer / Denom;
     //double Error = sqrt(Numer * Numer * DenomError * DenomError + Denom * Denom * NumerError * NumerError) / (Denom * Denom);
     double Error = 0.0;
     if(fabs(Denom) > 1e-9) Error = NumerError / Denom;
     Custom[PadNumber][Number]->SetBinContent(ibin, Value);
     Custom[PadNumber][Number]->SetBinError(ibin, Error);
     //cout<<Numer<<"  "<<Denom<<"  "<<Value<<endl;  
  }
   if(isOutput){
     for(int ibin = 1; ibin <= Custom[PadNumber][Number]->GetNbinsX(); ibin++){
       cout<<"bin "<<ibin<<": "<<Custom[PadNumber][Number]->GetBinContent(ibin)<<" +- "<<Custom[PadNumber][Number]->GetBinError(ibin)<<endl;
     }
   }
 }
 if((TString)process == "Pull"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     Custom[PadNumber][Number]->SetBinContent(ibin, (h1[histNumber1]->GetBinContent(ibin) - h1[histNumber2]->GetBinContent(ibin)) / sqrt(h1[histNumber1]->GetBinError(ibin) * h1[histNumber1]->GetBinError(ibin) + h1[histNumber2]->GetBinError(ibin) * h1[histNumber2]->GetBinError(ibin)));
   }
 }
 if((TString)process == "Asymmetry"){
   for(int ibin = 1; ibin <= h1[histNumber1]->GetNbinsX(); ibin++){
     double Nf = h1[histNumber1]->GetBinContent(ibin);
     double Nb = h1[histNumber2]->GetBinContent(ibin);
     if(fabs(Nf + Nb) < 1e-10) continue;
     if(Nf < 1e-10) continue;
     if(Nb < 1e-10) continue;
  
     double AFB = (Nf - Nb) / (Nf + Nb);
  
     double NfError = h1[histNumber1]->GetBinError(ibin);
     double NbError = h1[histNumber2]->GetBinError(ibin);
     double AFBError = 2 * sqrt((Nf * NbError) * (Nf * NbError) + (Nb * NfError) * (Nb * NfError)) / ((Nf + Nb) * (Nf + Nb));
  
     Custom[PadNumber][Number]->SetBinContent(ibin, AFB);
     Custom[PadNumber][Number]->SetBinError(ibin, AFBError);
   }
 }

 if(isCustomHist[PadNumber][Number]) cout<<"Integral of "<<Custom[PadNumber][Number]->GetName()<<": "<<Custom[PadNumber][Number]->Integral()<<endl;

 if((TString)process == "") return;

}

void Figure::SetCustomPlotFormat(int PadNumber, int Number, Color_t Color, Style_t style, bool isFilled)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(isCustomHist[PadNumber][Number]){
   Custom[PadNumber][Number]->SetMarkerStyle(style);
   Custom[PadNumber][Number]->SetMarkerColor(Color);
   Custom[PadNumber][Number]->SetMarkerSize(1);
   Custom[PadNumber][Number]->SetLineWidth(4);
   Custom[PadNumber][Number]->SetLineColor(Color);
   Custom[PadNumber][Number]->SetLineStyle(1);
   if(isFilled){
     Custom[PadNumber][Number]->SetFillColor(Color);
     Custom[PadNumber][Number]->SetFillStyle(3354);
   }

   if(isE3 || isE4){
     Custom[PadNumber][Number]->SetFillColor(Color);
   }

   if(isPMC || isPLC){
     //Custom[PadNumber][Number]->SetFillColor(0);
     //Custom[PadNumber][Number]->SetLineColor(0);
     Custom[PadNumber][Number]->SetMarkerStyle(style);
     Custom[PadNumber][Number]->SetMarkerSize(1.5);
     Custom[PadNumber][Number]->SetBarWidth(0.1);
   }

   CustomColor[make_pair(PadNumber, Number)] = Color;
   //legend1->AddEntry(h1[Number], myLegendName[Number],"lpfe");
 }

 if(isCustomFunction[PadNumber][Number]){
   CustomFunction[PadNumber][Number]->SetMarkerStyle(style);
   CustomFunction[PadNumber][Number]->SetMarkerColor(Color);
   CustomFunction[PadNumber][Number]->SetMarkerSize(1);
   CustomFunction[PadNumber][Number]->SetLineWidth(4);
   CustomFunction[PadNumber][Number]->SetLineColor(Color);
   CustomFunction[PadNumber][Number]->SetLineStyle(1);

   CustomColor[make_pair(PadNumber, Number)] = Color;
 }

 if(isCustomGraph[PadNumber][Number]){
   if(CustomPlot[PadNumber][Number] == "sameL"){
     CustomGraph[PadNumber][Number]->SetLineWidth(4);
     CustomGraph[PadNumber][Number]->SetLineColor(Color);
     CustomGraph[PadNumber][Number]->SetLineStyle(2);
     CustomGraph[PadNumber][Number]->SetFillColor(Color);
   }
   if(CustomPlot[PadNumber][Number] == "sameF"){
     CustomGraph[PadNumber][Number]->SetLineWidth(0);
     CustomGraph[PadNumber][Number]->SetLineColor(kWhite);
     CustomGraph[PadNumber][Number]->SetLineStyle(0);
     CustomGraph[PadNumber][Number]->SetFillColor(Color);
   }

 }
}

void Figure::SetPadTitle(int PadNumber, const char* PadName)
{
 myPadName[PadNumber] = PadName;
}

void Figure::SetCustomYRange(int PadNumber, double ymin, double ymax)
{
 isSetCustomYRange[PadNumber] = true;

 CustomYRangeMin[PadNumber] = ymin;
 CustomYRangeMax[PadNumber] = ymax;
}

void Figure::SetCustomLegendSize(int PadNumber, double size)
{
 CustomLegendSize[PadNumber] = size;
}

void Figure::SetCustomXTitleSize(int PadNumber, double size)
{
 CustomXTitleSize[PadNumber] = size;
}

void Figure::SetCustomXTitleOffset(int PadNumber, double size)
{
 CustomXTitleOffset[PadNumber] = size;
}

void Figure::SetCustomXLabelSize(int PadNumber, double size)
{
 CustomXLabelSize[PadNumber] = size;
}

void Figure::SetCustomYTitleSize(int PadNumber, double size)
{
 CustomYTitleSize[PadNumber] = size;
}

void Figure::SetCustomYTitleOffset(int PadNumber, double size)
{
 CustomYTitleOffset[PadNumber] = size;
}

void Figure::SetCustomYLabelSize(int PadNumber, double size)
{
 CustomYLabelSize[PadNumber] = size;
}

void Figure::SetCustomPadYPosition(int PadNumber, double ymin, double ymax)
{
 CustomPadYMin[PadNumber] = ymin;
 CustomPadYMax[PadNumber] = ymax;
}

void Figure::SetCustomMarkerSize(int PadNumber, int Number, double size)
{
 Custom[PadNumber][Number]->SetMarkerSize(size);
}

void Figure::SetCustomNdivisions(int PadNumber, int ndiv)
{
 CustomNdivisions[PadNumber] = ndiv;
}

void Figure::SetCustomGrid(int PadNumber, bool flag)
{
 isCustomGrid[PadNumber] = flag;
}

void Figure::SetCustomLineStyle(int PadNumber, int Number, Style_t style)
{
 if(isCustomHist[PadNumber][Number]){
   Custom[PadNumber][Number]->SetLineStyle(style);
   Custom[PadNumber][Number]->SetMarkerSize(0);
 }
 if(isCustomFunction[PadNumber][Number]){
   CustomFunction[PadNumber][Number]->SetLineStyle(style);
 }
 if(isCustomGraph[PadNumber][Number]){
   CustomGraph[PadNumber][Number]->SetLineStyle(style);
 }
}

void Figure::SetCustomLineWidth(int PadNumber, int Number, int width)
{
 if(isCustomHist[PadNumber][Number]){
   Custom[PadNumber][Number]->SetLineWidth(width);
 }
 if(isCustomFunction[PadNumber][Number]){
   CustomFunction[PadNumber][Number]->SetLineWidth(width);
 }
 if(isCustomGraph[PadNumber][Number]){
   CustomGraph[PadNumber][Number]->SetLineWidth(width);
 }
}

void Figure::SetCustomBarOffset(int PadNumber, int Number, double size)
{
 Custom[PadNumber][Number]->SetBarOffset(size);
}

void Figure::CustomNorm(int fig1, int fig2, int BaseOne)
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

void Figure::SetCustomError(int PadNumber, int Number, int ErrorNumber, TString isFilled)
{
 if(!isInputError) return;

 if(!Custom[PadNumber][Number]){
   cout<<"Please set the relative customize plot at first."<<endl;
   return;
 }

 isResetError[PadNumber][Number] = true;

 for(int ibin = 0; ibin < Custom[PadNumber][Number]->GetNbinsX(); ibin++){
//   Custom[PadNumber][Number]->SetBinError(ibin + 1, HistError[ErrorNumber]->GetBinError(ibin + 1) / HistError[ErrorNumber]->GetBinContent(ibin + 1));
   Custom[PadNumber][Number]->SetBinError(ibin + 1, HistError[ErrorNumber]->GetBinError(ibin + 1));
 }

 Custom[PadNumber][Number]->SetFillStyle(3354);
 Custom[PadNumber][Number]->SetLineColor(CustomColor[make_pair(PadNumber, Number)]);
 Custom[PadNumber][Number]->SetMarkerColor(CustomColor[make_pair(PadNumber, Number)]);
 Custom[PadNumber][Number]->SetFillColor(CustomColor[make_pair(PadNumber, Number)]);
 Custom[PadNumber][Number]->SetMarkerSize(0);
 Custom[PadNumber][Number]->SetLineWidth(0);
 Custom[PadNumber][Number]->SetLineStyle(0);
// Custom[PadNumber][Number]->SetLineColor(kCyan);
// Custom[PadNumber][Number]->SetMarkerColor(kCyan);
// Custom[PadNumber][Number]->SetFillColor(kCyan);

 if(isFilled == "Filled"){
   Custom[PadNumber][Number]->SetFillStyle(3002);
   Custom[PadNumber][Number]->SetFillColor(CustomColor[make_pair(PadNumber, Number)]);
 }

 myCustomLegendName[PadNumber][Number] = ErrorLegendName[ErrorNumber];
}


void Figure::AddFittingPlot(TString rootName, TString FittingName)
{
 isFittingPlot = true;

 FittingFile = new TFile(rootName);
 FittingPlot = (TF1 *)FittingFile->Get(FittingName);
}

void Figure::IgnoreCustomError(int PadNumber, int Number)
{
 for(int i = 1; i <= Custom[PadNumber][Number]->GetNbinsX(); i++){
   Custom[PadNumber][Number]->SetBinError(i, 0);
 }

}

void Figure::SetCustomPlot(int PadNumber, int Number, TString format)
{
 CustomPlot[PadNumber][Number] = format;
 if(format == "P"){
   Custom[PadNumber][Number]->SetLineColor(0);
   Custom[PadNumber][Number]->SetMarkerSize(2);
 }
 if(format == "E2"){
   Custom[PadNumber][Number]->SetFillColor(CustomColor[make_pair(PadNumber, Number)]);
   Custom[PadNumber][Number]->SetFillColorAlpha(CustomColor[make_pair(PadNumber, Number)], 0.5);
   Custom[PadNumber][Number]->SetLineColorAlpha(CustomColor[make_pair(PadNumber, Number)], 0.0);
   //Custom[PadNumber][Number]->SetFillStyle(3002);
   Custom[PadNumber][Number]->SetMarkerSize(0);
   //Custom[PadNumber][Number]->SetFillStyle(3354);
 }
 if(format.Contains("bar")){
   Custom[PadNumber][Number]->SetFillColor(CustomColor[make_pair(PadNumber, Number)]);
 }
}

void Figure::Input(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 if(!is2D){
   if(!isDefineHist) h1[Number] = (TH1D *)file[Number]->Get(histName);
   if(isDefineHist){
     tmph1[Number] = (TH1D *)file[Number]->Get(histName);
     for(int ibin = 1; ibin <= tmph1[Number]->GetNbinsX(); ibin++){
       h1[Number]->SetBinContent(ibin, tmph1[Number]->GetBinContent(ibin));
       h1[Number]->SetBinError(ibin, tmph1[Number]->GetBinError(ibin));
     }
   }
 }
 if(is2D){
   if(!isDefineHist) h2[Number] = (TH2D *)file[Number]->Get(histName);
    if(isDefineHist){
      tmph2[Number] = (TH2D *)file[Number]->Get(histName);
      for(int ibinx = 1; ibinx <= tmph2[Number]->GetNbinsX(); ibinx++){
        for(int ibiny = 1; ibiny <= tmph2[Number]->GetNbinsY(); ibiny++){
          h2[Number]->SetBinContent(ibinx, ibiny, tmph2[Number]->GetBinContent(ibinx, ibiny));
          h2[Number]->SetBinError(ibinx, ibiny, tmph2[Number]->GetBinError(ibinx, ibiny));
        }
      }
    }
 }

 myLegendName[Number] = legendName;

 if(isRebin)
 {
  cout<<"Histogram has been rebinned."<<endl;
  if(RebinType == 1) h1[Number]->Rebin(ngroup);
  if(RebinType == 2) h1[Number] = (TH1D *)h1[Number]->Rebin(ngroup, histName, rebin);
  if(is2D) {cout<<"Error: 2D histogram cannot be rebined"<<endl; return;}
 }

// if(isNormToOne[Number]){
//   double xsec = h1[Number]->Integral();
//   h1[Number]->Scale(1.0 / xsec);
// }

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }
 if(!is2D) cout<<"Integral of "<<h1[Number]->GetName()<<": "<<h1[Number]->Integral()<<endl;
}

void Figure::Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH2D *hist_2D = (TH2D *)file[Number]->Get(histName);

 if(binx == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsX(), hist_2D->GetXaxis()->GetBinLowEdge(1), hist_2D->GetXaxis()->GetBinUpEdge(hist_2D->GetNbinsX()));
   if(!isDefineHist) h1[Number] = hist_2D->ProjectionX(hist_2D->GetName() + (TString)"_px_" + (int)biny, biny, biny);

   //for(int ibin = 1; ibin <= hist_2D->GetNbinsX(); ibin++){
   //  h1[Number]->SetBinContent(ibin, hist_2D->GetBinContent(ibin, biny));
   //  h1[Number]->SetBinError(ibin, hist_2D->GetBinError(ibin, biny));
   //}
 }
 else if(biny == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsY(), hist_2D->GetYaxis()->GetBinLowEdge(1), hist_2D->GetYaxis()->GetBinUpEdge(hist_2D->GetNbinsY()));
   if(!isDefineHist) h1[Number] = hist_2D->ProjectionY(hist_2D->GetName() + (TString)"_py_" + (int)binx, binx, binx);

   //for(int ibin = 1; ibin <= hist_2D->GetNbinsY(); ibin++){
   //  h1[Number]->SetBinContent(ibin, hist_2D->GetBinContent(binx, ibin));
   //  h1[Number]->SetBinError(ibin, hist_2D->GetBinError(binx, ibin));
   //}
 }

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }
}

void Figure::Input2Dx(int Number, const char* rootName, const char* histName, int biny1, int biny2, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;
 
 FigureCount++;
 
 file[Number] = new TFile(rootName);
 
 myLegendName[Number] = legendName;
 
 TH2D *hist_2D = (TH2D *)file[Number]->Get(histName);
 
 if(!isDefineHist) h1[Number] = hist_2D->ProjectionX(hist_2D->GetName() + (TString)"_px_" + (int)biny1 + "_" + (int)biny2, biny1, biny2);

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }
}

void Figure::Input2Dy(int Number, const char* rootName, const char* histName, int binx1, int binx2, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;
 
 FigureCount++;
 
 file[Number] = new TFile(rootName);
 
 myLegendName[Number] = legendName;
 
 TH2D *hist_2D = (TH2D *)file[Number]->Get(histName);
 
 if(!isDefineHist) h1[Number] = hist_2D->ProjectionY(hist_2D->GetName() + (TString)"_py_" + (int)binx1 + "_" + (int)binx2, binx1, binx2);

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }
}

void Figure::Input3D(int Number, const char* rootName, const char* histName, int binx, int biny, int binz, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;

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

void Figure::Input3Dyz(int Number, const char* rootName, const char* histName, int binx1, int binx2, const char* legendName = "")
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH3D *hist_3D = (TH3D *)file[Number]->Get(histName);

 h2[Number] = (TH2D *)hist_3D->Project3D("zy");
 h2[Number]->Reset();

 for(int ibiny = 1; ibiny <= hist_3D->GetNbinsY(); ibiny++){
   for(int ibinz = 1; ibinz <= hist_3D->GetNbinsZ(); ibinz++){
     double Value = 0.0;
     double Error = 0.0;
     for(int ibinx = binx1; ibinx <= binx2; ibinx++){
       Value += hist_3D->GetBinContent(ibinx, ibiny, ibinz);
       Error += pow(hist_3D->GetBinError(ibinx, ibiny, ibinz), 2);
     }

     h2[Number]->SetBinContent(ibiny, ibinz, Value);
     h2[Number]->SetBinError(ibiny, ibinz, sqrt(Error));
   }
 }
}

void Figure::Input3Dx(int Number, const char* rootName, const char* histName, int biny1, int biny2, int binz1, int binz2, const char* legendName = "")
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH3D *hist_3D = (TH3D *)file[Number]->Get(histName);

 if(!isDefineHist) h1[Number] = hist_3D->ProjectionX(hist_3D->GetName() + (TString)"_py_" + (int)biny1 + "_" + (int)biny2 + (TString)"_pz_" + (int)binz1 + "_" + (int)binz2, biny1, biny2, binz1, binz2);

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }

}

void Figure::Input3Dy(int Number, const char* rootName, const char* histName, int binx1, int binx2, int binz1, int binz2, const char* legendName = "")
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH3D *hist_3D = (TH3D *)file[Number]->Get(histName);

 if(!isDefineHist) h1[Number] = hist_3D->ProjectionY(hist_3D->GetName() + (TString)"_px_" + (int)binx1 + "_" + (int)binx2 + (TString)"_pz_" + (int)binz1 + "_" + (int)binz2, binx1, binx2, binz1, binz2);

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }

}

void Figure::Input3Dz(int Number, const char* rootName, const char* histName, int binx1, int binx2, int biny1, int biny2, const char* legendName = "")
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 myLegendName[Number] = legendName;

 TH3D *hist_3D = (TH3D *)file[Number]->Get(histName);

 if(!isDefineHist) h1[Number] = hist_3D->ProjectionZ(hist_3D->GetName() + (TString)"_px_" + (int)binx1 + "_" + (int)binx2 + (TString)"_py_" + (int)biny1 + "_" + (int)biny2, binx1, binx2, biny1, biny2);

 if(isDivideBinWidth[Number]){
   for(int ibin = 0; ibin < h1[Number]->GetNbinsX(); ibin ++){
//     cout<<(h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1))<<endl;
     h1[Number]->SetBinContent(ibin + 1, h1[Number]->GetBinContent(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
     h1[Number]->SetBinError(ibin + 1, h1[Number]->GetBinError(ibin + 1) / (h1[Number]->GetXaxis()->GetBinUpEdge(ibin + 1) - h1[Number]->GetXaxis()->GetBinLowEdge(ibin + 1)));
//     cout<<h1[Number]->GetBinContent(ibin + 1)<<endl;
   }
 }

}

void Figure::InputError(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInputError = true;

 ErrorFile[Number] = new TFile(rootName);

 HistError[Number] = (TH1D *)ErrorFile[Number]->Get(histName);

 HistError[Number]->SetFillStyle(3354);
 HistError[Number]->SetFillColor(kBlack);

 ErrorLegendName[Number] = (TString)legendName;
}

void Figure::ResetError(int Number, int ErrorNumber)
{
 for(int ibin = 1; ibin <= h1[Number]->GetNbinsX(); ibin++){
   h1[Number]->SetBinError(ibin, HistError[ErrorNumber]->GetBinError(ibin) / HistError[ErrorNumber]->GetBinContent(ibin) * h1[Number]->GetBinContent(ibin));
 }
//  isResetError[Number][ErrorNumber] = true;

}

void Figure::Input2DError(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName)
{
 isInputError = true;
 
 ErrorFile[Number] = new TFile(rootName);
 
 ErrorLegendName[Number] = (TString)legendName;
 
 TH2D *hist_2D = (TH2D *)ErrorFile[Number]->Get(histName);
 
 if(binx == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsX(), hist_2D->GetXaxis()->GetBinLowEdge(1), hist_2D->GetXaxis()->GetBinUpEdge(hist_2D->GetNbinsX()));
   HistError[Number] = hist_2D->ProjectionX(hist_2D->GetName() + (TString)"_px_" + (int)biny, biny, biny);
   
   for(int ibin = 1; ibin <= hist_2D->GetNbinsX(); ibin++){
     HistError[Number]->SetBinContent(ibin, hist_2D->GetBinContent(ibin, biny));
     HistError[Number]->SetBinError(ibin, hist_2D->GetBinError(ibin, biny));
   }
 }
 else if(biny == 0){
//   h1[Number] = new TH1D(legendName, legendName, hist_2D->GetNbinsY(), hist_2D->GetYaxis()->GetBinLowEdge(1), hist_2D->GetYaxis()->GetBinUpEdge(hist_2D->GetNbinsY()));
   HistError[Number] = hist_2D->ProjectionY(hist_2D->GetName() + (TString)"_py_" + (int)binx, binx, binx);
   
   for(int ibin = 1; ibin <= hist_2D->GetNbinsY(); ibin++){
     HistError[Number]->SetBinContent(ibin, hist_2D->GetBinContent(binx, ibin));
     HistError[Number]->SetBinError(ibin, hist_2D->GetBinError(binx, ibin));
   }
 }

}

void Figure::InputTGraph(int Number, const char* rootName, const char* histName, const char* legendName = "")
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 graph[Number] = (TGraph *)file[Number]->Get(histName);

 double* BinCenter = new double[graph[Number]->GetN() + 1];
 for(int i = 0; i < graph[Number]->GetN(); i++){
//   BinCenter[i + 1] = graph[Number]->GetPointX(i);
   double y;
   graph[Number]->GetPoint(i, BinCenter[i + 1], y);
 }
 double* Binning = new double[graph[Number]->GetN() + 1];
 Binning[0] = 2.0 * BinCenter[1] - BinCenter[2];
 for(int i = 1; i < graph[Number]->GetN() + 1; i++){
   Binning[i] = 2 * BinCenter[i] - Binning[i - 1];
 }

 for(int i = 0; i < graph[Number]->GetN() + 1; i++){
   cout<<i<<" "<<BinCenter[i]<<" "<<Binning[i]<<endl;
 }

 h1[Number] = new TH1D(histName, histName, graph[Number]->GetN(), Binning);

 for(int i = 1; i <= h1[Number]->GetNbinsX(); i++){
   double x, y;
   graph[Number]->GetPoint(i, x, y);
   h1[Number]->SetBinContent(i, y);
   h1[Number]->SetBinError(i, 0.0);
 }
}

void Figure::InputTree(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 file[Number] = new TFile(rootName);

 tree[Number] = (TTree *)file[Number]->Get(treeName);

 h1[Number] = new TH1D(histName, histName, nbin, left, right);
 tree[Number]->Draw((TString)VariableName + ">>" + h1[Number]->GetName(), WeightName, "goff");

 myLegendName[Number] = legendName;

}

void Figure::Input(int Number, TH1D* h, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;

 FigureCount++;

 myLegendName[Number] = legendName;

 if(!is2D){
   if(!isDefineHist) h1[Number] = h;
   if(isDefineHist){
     tmph1[Number] = h;
     for(int ibin = 1; ibin <= tmph1[Number]->GetNbinsX(); ibin++){
       h1[Number]->SetBinContent(ibin, tmph1[Number]->GetBinContent(ibin));
       h1[Number]->SetBinError(ibin, tmph1[Number]->GetBinError(ibin));
     }
   }
 }

}

void Figure::Input(int Number, TH2D* h, const char* legendName)
{
 isInput = true;
 isHist[Number] = true;
 
 FigureCount++;
 
 myLegendName[Number] = legendName;
 
 h2[Number] = h;
}

void Figure::InputTF1(int Number, const char* rootName, const char* histName, const char* legendName = "")
{
 isInput = true;

// FunctionCount++;
 FigureCount++;

// FunctionFile[Number] = new TFile(rootName);
 file[Number] = new TFile(rootName);

// f1[Number] = (TF1 *)FunctionFile[Number]->Get(histName);
 f1[Number] = (TF1 *)file[Number]->Get(histName);

 myLegendName[Number] = legendName;

 isFunction[Number] = true;
}

void Figure::InputEnsemble(int Number1, int Number2, int Number3, const char* rootName, const char* treeName, const char* branchName, const char* legendName = "")
{
 isInput = true;
 isGraph[Number1] = true;
 isGraph[Number2] = true;
 isGraph[Number3] = true;

 DrawStyle[Number1] = "sameF";
 DrawStyle[Number2] = "sameF";
 DrawStyle[Number3] = "sameL";

 file[Number1] = new TFile(rootName);

 tree[Number1] = (TTree *)file[Number1]->Get(treeName);

 TBranch* b_marg = tree[Number1]->GetBranch(branchName);
 TObjArray* objarr_leaves = b_marg->GetListOfLeaves();
 TLeaf* l_marg = b_marg->GetLeaf(objarr_leaves->At(0)->GetName());

 vector<double> vecLimit;

 for(int i = 0; i < tree[Number1]->GetEntries(); i++){
   tree[Number1]->GetEntry(i);
   double pelimit = l_marg->GetValue();
   vecLimit.push_back(pelimit);
 }

 sort(vecLimit.begin(), vecLimit.end());
 unsigned neg95 = unsigned(vecLimit.size() * (1 - .9545) / 2);
 unsigned neg68 = unsigned(vecLimit.size() * (1 - .6827) / 2);
 unsigned central = unsigned(vecLimit.size() * .5);
 unsigned pos68 = unsigned(vecLimit.size() * (1 + .6827) / 2);
 unsigned pos95 = unsigned(vecLimit.size() * (1 + .9545) / 2);

 cout<<"neg95: "<<vecLimit.at(neg95)<<endl;
 cout<<"neg68: "<<vecLimit.at(neg68)<<endl;
 cout<<"central: "<<vecLimit.at(central)<<endl;
 cout<<"pos68: "<<vecLimit.at(pos68)<<endl;
 cout<<"pos95: "<<vecLimit.at(pos95)<<endl;

 FigureCount++;
 g1[Number1] = new TGraph();
 FigureCount++;
 g1[Number2] = new TGraph();
 FigureCount++;
 g1[Number3] = new TGraph();

 for(int i = 0; i < 10; i++){
   int ipoint=g1[Number1]->GetN();
   g1[Number1]->SetPoint(ipoint, vecLimit.at(pos95), i * 5000);
 }
 for(int i = 10; i >= 0; --i){
   int ipoint=g1[Number1]->GetN();
   g1[Number1]->SetPoint(ipoint, vecLimit.at(neg95), i * 5000);
 }

 for(int i = 0; i < 10; i++){
   int ipoint=g1[Number2]->GetN();
   g1[Number2]->SetPoint(ipoint, vecLimit.at(pos68), i * 5000);
 }
 for(int i = 10; i >= 0; --i){
   int ipoint=g1[Number2]->GetN();
   g1[Number2]->SetPoint(ipoint, vecLimit.at(neg68), i * 5000);
 }

 for(int i = 0; i < 10; i++){
   int ipoint=g1[Number3]->GetN();
   g1[Number3]->SetPoint(ipoint, vecLimit.at(central), i * 5000);
 }


}

void Figure::NormToOne(int Number)
{
 isNormToOne[Number] = true;
 if(isNormToOne[Number]){
   double xsec = h1[Number]->Integral();
   h1[Number]->Scale(1.0 / xsec);
 }   
}

void Figure::NormToOne(int Number, int FirstBin, int LastBin)
{
 double xsec = h1[Number]->Integral(FirstBin, LastBin);
 h1[Number]->Scale(1.0 / xsec);

}

void Figure::ScalePlot(int Number, double scale)
{
 h1[Number]->Scale(scale);
}

void Figure::InputPDFError(int Number, const char* rootName, const char* histName, const char* legendName)
{
 isInputPDFError = true;

 withPDFError = true;

 PDFFigureCount++;

 PDFfile[Number] = new TFile(rootName);
 PDF1[Number] = (TH1D *)PDFfile[Number]->Get(histName);
 myPDFLegendName[Number] = legendName;

 if(isRebin) cout<<"WARNING: PDF uncertainty cannot be rebined!"<<endl;
}

void Figure::AddText(int Number, const char* TextContent)
{
 if(Number == 0) {cout<<"WARNING!! Please add text from No.1"<<endl;}
 myText[Number] = TextContent;

 TextCount++;
}

void Figure::AddLine(int Number, double x1, double y1, double x2, double y2)
{
 if(Number == 0) {cout<<"WARNING!! Please add line from No.1"<<endl;}

 line[Number] = new TLine(x1, y1, x2, y2);
 line[Number]->SetLineStyle(9);
 line[Number]->SetLineWidth(4);

 LineCount++;
}

void Figure::AddArrow(int Number, double x1, double y1, double x2, double y2, TString format, Color_t Color)
{
 if(Number == 0) {cout<<"WARNING!! Please add line from No.1"<<endl;}

 arrow[Number] = new TArrow(x1, y1, x2, y2, 0.03, format.Data());
 arrow[Number]->SetAngle(60);
 arrow[Number]->SetLineWidth(4);
 arrow[Number]->SetLineColor(Color);
 arrow[Number]->SetFillColor(Color);

 ArrowCount++;
}

void Figure::AddCustomText(int Number, double x1, double y1, TString TextContent)
{
 if(Number == 0) {cout<<"WARNING!! Please add text from No.1"<<endl;}
 myCustomText[Number] = TextContent;
 CustomTextX[Number] = x1;
 CustomTextY[Number] = y1;

 CustomTextCount++;
}

void Figure::SetProcess(int Process)
{
 this->Process = Process;
 if(Process == 1) cout<<"Scale Uncertainty"<<endl;
 if(Process == 2) cout<<"PDF Uncertainty"<<endl;
}

void Figure::SetPlotFormat(int Number, Color_t Color, Style_t style)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(!is2D){
   if(isSingle || isSingleRatio)
   {
    h1[Number]->SetMarkerStyle(style);
    h1[Number]->SetMarkerColor(Color);
    h1[Number]->SetMarkerSize(2);
    h1[Number]->SetLineWidth(0);
    h1[Number]->SetLineColor(Color);

//   legend1->AddEntry(h1[Number], myLegendName[Number],"lpfe");
   }
 }
}

void Figure::SetPaintTextStyle(int Number, TString style)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 PaintTextStyle[Number] = style;
}

void Figure::SetBarOffset(int Number, double size)
{
 HistBarOffset[Number] = size;
}

void Figure::Define2DTextStyle(int Number)
{
   TLatex text;
   text.SetTextFont(gStyle->GetTextFont());
   text.SetTextColor(h2[Number]->GetMarkerColor());
   text.SetTextSize(0.02*h2[Number]->GetMarkerSize());

   Double_t x, y, z, e, angle = 0;
   TString tt, tf;
   tf.Form("%s%s","%",PaintTextStyle[Number].Data());
   //if (Hoption.Text >= 1000) angle = Hoption.Text%1000;

      text.SetTextAlign(22);
      //if (Hoption.Text ==  1) angle = 0;
      text.SetTextAngle(angle);
      text.TAttText::Modify();
      //for (Int_t j=Hparam.yfirst; j<=Hparam.ylast;j++) {
      for (Int_t j=1; j<=h2[Number]->GetNbinsY();j++) {
         y    = h2[Number]->GetYaxis()->GetBinCenter(j);
         //if (Hoption.Logy) {
         //   if (y > 0)  y  = TMath::Log10(y);
         //   else continue;
         //}
         //for (Int_t i=Hparam.xfirst; i<=Hparam.xlast;i++) {
         for(Int_t i=1; i<=h2[Number]->GetNbinsX();i++) {
            Int_t bin  = j*(h2[Number]->GetXaxis()->GetNbins()+2) + i;
            x    = h2[Number]->GetXaxis()->GetBinCenter(i);
            //if (Hoption.Logx) {
            //   if (x > 0)  x  = TMath::Log10(x);
            //   else continue;
            //}
            //if (!IsInside(x,y)) continue;
            z = h2[Number]->GetBinContent(bin);
            //if (z < Hparam.zmin || (z == 0 && !Hoption.MinimumZero)) continue;
            //if (Hoption.Text>2000) {
            if (0) {
               e = h2[Number]->GetBinError(bin);
               tf.Form("#splitline{%s%s}{#pm %s%s}",
                                          "%",PaintTextStyle[Number].Data(),
                                          "%",PaintTextStyle[Number].Data());
               tt.Form(tf.Data(),z,e);
            } else {
               tt.Form(tf.Data(),z);
            }
            //text.PaintLatex(x,y+h2[Number]->GetBarOffset()*h2[Number]->GetYaxis()->GetBinWidth(j),
            //                angle,0.02*h2[Number]->GetMarkerSize(),tt.Data());
            text.DrawLatex(x,y+h2[Number]->GetBarOffset()*h2[Number]->GetYaxis()->GetBinWidth(j),
                            tt.Data());
         }
      }

}

void Figure::SetPDFPlotFormat(int Number, Color_t Color, Style_t style)
{
 if(!isInputPDFError) {cout<<"There is no input file."<<endl; return;}

 if(isSingle || isSingleRatio)
 {
  PDF1[Number]->SetMarkerStyle(style);
  PDF1[Number]->SetMarkerColor(Color);
  PDF1[Number]->SetMarkerSize(2);
  PDF1[Number]->SetLineWidth(0);
  PDF1[Number]->SetLineColor(Color);

// legend1->AddEntry(h1[Number], myLegendName[Number],"lpfe");
 }
}

void Figure::PDFScale(double PDFScaleFactor)
{
 this->PDFScaleFactor = PDFScaleFactor;
}

void Figure::SetPDFUncRange(double ymin, double ymax)
{
 if(!isPDF){
   cout<<"This option is only for stwPDF paper."<<endl;
   return;
 }

 isSetPDFUncRange = true;

 this->PDFUncRangeMin = ymin;
 this->PDFUncRangeMax = ymax;
}

void Figure::DivideBinWidth(int Number)
{
 isDivideBinWidth[Number] = true;
}

void Figure::FigureNorm(int Number)
{
 if(!isInput) return;

 double CrossSection = h1[Number]->Integral();
 h1[Number]->Scale(1.0 / CrossSection);
}

void Figure::SetXRange(double xmin, double xmax)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

// if(!is2D){
   //h1[1]->GetXaxis()->SetRangeUser(xmin, xmax);
   //if(withPDFError) PDF1[1]->GetXaxis()->SetRangeUser(xmin, xmax);

   this->XRangeMin = xmin;
   this->XRangeMax = xmax;
// }

 isSetXRange = true;
}

void Figure::SetYRange(double ymin, double ymax, int iPlot)
{
 if(is2D){
//  cout<<"SetYRange is only for single plot."<<endl;
//  cout<<"Other plot type please use other tools."<<endl;
     this->ymin = ymin;
     this->ymax = ymax;
  return;
 }

 isSetYRange = true;

 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(!is2D){
   if(iPlot == 0){
     isSetYRange0 = true;
     isSetYRange = false;
     this->ymin = ymin;
     this->ymax = ymax;
     return;
   }
   h1[iPlot]->GetYaxis()->SetRangeUser(ymin, ymax);
 }
}

void Figure::SetBaseLine(int Number)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(!is2D){
   h1[0] = (TH1D *)h1[Number]->Clone("h1");

   for(int i = 1; i < FigureCount + 1; i++)
   {
    h1[i]->Divide(h1[0]);
   }
 }
}

void Figure::SetMultiRatio(int Number)
{
 withPDFError = true;
 isInputPDFError = true;

 int iPlot = 1;
 while(iPlot <= FigureCount){
   PDF1[iPlot] = (TH1D *)h1[Number]->Clone("nominal");
   PDF1[iPlot]->Divide(h1[iPlot]);

   iPlot++;
 }
 PDFFigureCount = FigureCount;
}

void Figure::SetMultiDeltaSigma(int Number)
{
 withPDFError = true;
 isInputPDFError = true;

 int iPlot = 1;
 while(iPlot <= FigureCount){
   PDF1[iPlot] = (TH1D *)h1[Number]->Clone("nominal");

   for(int ibin = 1; ibin < h1[1]->GetNbinsX() + 1; ibin++)
   {
    PDF1[iPlot]->SetBinContent(ibin, (h1[Number]->GetBinContent(ibin) - h1[iPlot]->GetBinContent(ibin)) / sqrt(h1[iPlot]->GetBinError(ibin) * h1[iPlot]->GetBinError(ibin) + h1[Number]->GetBinError(ibin) * h1[Number]->GetBinError(ibin)));
    PDF1[iPlot]->SetBinError(ibin, h1[iPlot]->GetBinError(ibin));
   }

   iPlot++;
 }
 PDFFigureCount = FigureCount;
}

void Figure::Divide(int numer, int denom)
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

// h1[0] = (TH1D *)h1[denom]->Clone("h1");

 if(!is2D)
 {
  if(isEfficiency){
    for(int ibin = 1; ibin <= h1[numer]->GetNbinsX(); ibin++){
        NumerPoint = h1[numer]->GetBinContent(ibin);
        DenomPoint = h1[denom]->GetBinContent(ibin);
        NumerError = h1[numer]->GetBinError(ibin);
        DenomError = h1[denom]->GetBinError(ibin);

        DataPoint = NumerPoint / DenomPoint;
        DataError = sqrt(((DenomPoint - NumerPoint) * (DenomPoint - NumerPoint) * NumerError * NumerError / (DenomPoint * DenomPoint)) + (NumerPoint * NumerPoint * (NumerError * NumerError + DenomError * DenomError) / (DenomPoint * DenomPoint))) / DenomPoint;

        if(DenomPoint < 0.00000001) DataPoint = 0;
        if(DenomError < 0.00000001) DataError = 0;
//        cout<<" "<<NumerPoint<<" "<<NumerError<<" "<<DenomPoint<<" "<<DenomError<<" "<<DataPoint<<" "<<DataError<<endl;
        h1[numer]->SetBinContent(ibin, DataPoint);
        h1[numer]->SetBinError(ibin, DataError);
    }
  }

  if(!isEfficiency){
    h1[numer]->Divide(h1[denom]);
  }

  delete h1[denom];
 }
 if(is2D)
 {
  if(isEfficiency){
    for(int ibinx = 1; ibinx <= h2[numer]->GetNbinsX(); ibinx++){
       for(int ibiny = 1; ibiny <= h2[numer]->GetNbinsY(); ibiny++){
          NumerPoint = h2[numer]->GetBinContent(ibinx, ibiny);
          DenomPoint = h2[denom]->GetBinContent(ibinx, ibiny);
          NumerError = h2[numer]->GetBinError(ibinx, ibiny);
          DenomError = h2[denom]->GetBinError(ibinx, ibiny);

          DataPoint = NumerPoint / DenomPoint;
          DataError = sqrt(((DenomPoint - NumerPoint) * (DenomPoint - NumerPoint) * NumerError * NumerError / (DenomPoint * DenomPoint)) + (NumerPoint * NumerPoint * (NumerError * NumerError + DenomError * DenomError) / (DenomPoint * DenomPoint))) / DenomPoint;

          if(DenomPoint < 0.00000001) DataPoint = 0;
          if(DenomError < 0.00000001) DataError = 0;
          h2[numer]->SetBinContent(ibinx, ibiny, DataPoint);
          h2[numer]->SetBinError(ibinx, ibiny, DataError);
       }
    }
  }

  if(!isEfficiency){
    h2[numer]->Divide(h2[denom]);
  }
  
  delete h2[denom];
 }
 FigureCount--;
}

void Figure::AddGaxis(double wmin, double wmax, int ndiv)
{
 isAddGaxis = true;
 this->wmin = wmin;
 this->wmax = wmax;
 this->ndiv = ndiv;
}

void Figure::Compare(TString Option, TString isNorm)
{
 if(isNorm == "Norm"){
   for(int i = 1; i <= FigureCount; i++){
     CustomNorm(1, i, 1);
   }
 }
 else if(isNorm == "NormToOne"){
   for(int i = 1; i <= FigureCount; i++){
     NormToOne(i);
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
     CustomSetting(2, i, 1, "Pull");
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlotFormat(2, i, myColor[i]);
   }
   SetCustomYRange(2, -0.5, 0.5);
 }
 if(Option == "MultiDelta"){
   SetCustomPad(2);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     CustomSetting(2, i, 1, "Minus");
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlotFormat(2, i, myColor[i]);
   }
   SetCustomYRange(2, -0.5, 0.5);
   SetPadTitle(2, "Delta");
 }
 if(Option == "MultiRatio"){
   SetCustomPad(2);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     CustomSetting(2, i, 1, "Divide");
     SetCustomPlotFormat(1, i, myColor[i]);
     SetCustomPlotFormat(2, i, myColor[i]);
   }
   SetCustomYRange(2, 0.5, 1.5);
   SetPadTitle(2, "Ratio");
 }
 if(Option == "MultiSimple"){
   SetCustomPad(1);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     SetCustomPlotFormat(1, i, myColor[i]);
   }
 }
 if(Option == "PDF1"){
   SetPlot("E2");
   SetCustomPad(1);
   CustomSetting(1, 1);
   SetCustomPlotFormat(1, 1, kBlue, 8, true);
 }
 if(Option == "PDF2"){
   SetPlot("E2");
   SetCustomPad(1);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   SetCustomPlotFormat(1, 1, kBlue, 8, true);
   SetCustomPlotFormat(1, 2, kRed, 8, true);
   SetCustomPlot(1, 1, "E2");
   SetCustomPlot(1, 2, "E2");
 }
 if(Option == "PDF3"){
   SetPlot("E2");
   SetCustomPad(1);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   CustomSetting(1, 3);
   SetCustomPlotFormat(1, 1, kBlue, 8, true);
   SetCustomPlotFormat(1, 2, kRed, 8, true);
   SetCustomPlotFormat(1, 3, kGreen+1, 8, true);
   SetCustomPlot(1, 1, "E2");
   SetCustomPlot(1, 2, "E2");
   SetCustomPlot(1, 3, "E2");
 }
 if(Option == "PDF21"){
   SetPlot("L");
   SetCustomPad(1);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   CustomSetting(1, 3);
   SetCustomPlotFormat(1, 1, kBlue, 8, true);
   SetCustomPlotFormat(1, 2, kRed, 8, false);
   SetCustomPlotFormat(1, 3, kGreen+1, 8, false);
   SetCustomPlot(1, 1, "E2");
   SetCustomPlot(1, 2, "L");
   SetCustomPlot(1, 3, "L");
 }
 if(Option == "Updating"){
   SetPlot("E2");
   SetCustomPad(2);
   CustomSetting(1, 1);
   CustomSetting(1, 2);
   CustomSetting(2, 3);
   CustomSetting(2, 4);
   SetCustomPlotFormat(1, 1, kBlue, 8, true);
   SetCustomPlotFormat(1, 2, kRed, 8, true);
   SetCustomPlotFormat(2, 1, kBlue);
   SetCustomPlotFormat(2, 2, kRed);
 }
 if(Option == "TwoPlot"){
   SetCustomPad(2);
   SetLegendPosition(0.05, 0.5, 0.35, 0.95);
   //SetLegend2Position(0.05, 0.5, 0.35, 0.95);
   SetCustomPadYPosition(1, 0.5, 1);
   SetCustomPadYPosition(2, 0.0, 0.5);
   SetCustomGrid(2, false);
   SetCustomXLabelSize(2, 0.05);
   SetCustomYLabelSize(2, 0.045);
   SetCustomXTitleSize(2, 0.05);
   SetCustomYTitleSize(2, 0.055);
   SetCustomYTitleOffset(2, 1.0);
   SetCustomLegendSize(1, 0.035);
   SetCustomLegendSize(2, 0.035);
   SetCustomNdivisions(1, 505);
   SetCustomNdivisions(2, 505);
   CustomBottomMargin[2] = 0.15;
 }
 if(Option == "Systematic"){
   SetCustomPad(1);
   for(int i = 1; i <= FigureCount; i++){
     CustomSetting(1, i);
     SetCustomPlotFormat(1, i, myColor[i]);
   }
   SetCustomPadYPosition(1, 0.05, 1);
   CustomBottomMargin[1] = 0.4;
   CustomYTitleSize[1] = 0.02;
   CustomYTitleOffset[1] = 1.8;
   CustomYLabelSize[1] = 0.02;
   CustomXLabelSize[1] = 0.02;
 }
}

void Figure::Draw()
{
 if(!isInput) {cout<<"There is no input file."<<endl; return;}

 if(isPDF) isSingle = false;

 TPad *pad1;
 TPad *pad2;
 TPad *pad3;

 if(isSingle){
   /*************************/
   /*******Single Plot*******/
   /*************************/
   MyN = new TCanvas("MyN","MyN",1000,800);
   MyN->cd();

   if(isLogX) gPad->SetLogx();
   if(isLogY) gPad->SetLogy();

   if(!withPDFError){
     /*********************************/
     /***********Single Plot***********/
     /*******Set Pad Information*******/
     /*********************************/
     pad1 = new TPad("pad1", "pad1", 0, 0, 1.0, 1.0);

     BottomMargin = 0.1;
     TopMargin = 0.1;
     LeftMargin = 0.15;
     RightMargin = 0.05;
     pad1->SetBottomMargin(BottomMargin);
     pad1->SetTopMargin(TopMargin);
     pad1->SetLeftMargin(LeftMargin);
     pad1->SetRightMargin(RightMargin);
   }
   if(withPDFError){
     /****************************************/
     /*******Single Plot with PDF Error*******/
     /**********Set Pad Information***********/
     /****************************************/
     pad1 = new TPad("pad1", "pad1", 0, 0.3, 1.0, 1.0);

     BottomMargin = 0;
     TopMargin = 0.15;
     LeftMargin = 0.15;
     RightMargin = 0.05;
     pad1->SetBottomMargin(BottomMargin);
     pad1->SetTopMargin(TopMargin);
     pad1->SetLeftMargin(LeftMargin);
     pad1->SetRightMargin(RightMargin);
   }
//  pad1->SetGridx();
//  pad1->SetGridy();
   pad1->Draw();
   pad1->cd();

   if(!is2D){
     /*********************************/
     /***********Single Plot***********/
     /*******Set Plot Information******/
     /*********************************/
     h1[1]->SetTitle("");
     h1[1]->SetStats(0);

     h1[1]->GetXaxis()->SetTitle(myXTitle);
     h1[1]->GetXaxis()->SetTitleSize(0.04);
     h1[1]->GetXaxis()->SetTitleFont(72);
     h1[1]->GetXaxis()->SetTitleOffset(1);

     h1[1]->GetXaxis()->SetLabelSize(0.04);
     h1[1]->GetXaxis()->SetLabelFont(72);

     h1[1]->GetYaxis()->SetTitle(myYTitle);
     h1[1]->GetYaxis()->SetTitleSize(0.04);
     h1[1]->GetYaxis()->SetTitleFont(72);
     h1[1]->GetYaxis()->SetTitleOffset(YTitleOffset);

     h1[1]->GetYaxis()->SetLabelSize(0.03);
     h1[1]->GetYaxis()->SetLabelFont(72);

     h1[1]->SetMarkerStyle(7);
     h1[1]->SetMarkerSize(0);
     h1[1]->SetMarkerStyle(21);
     h1[1]->SetMarkerColor(kBlue+1);
     h1[1]->SetLineWidth(4);
     h1[1]->SetLineColor(kBlue+1);

     h1[1]->SetFillStyle(3544);
     h1[1]->SetFillColor(kBlack);
     if(isE0) h1[1]->Draw("E2");
     if(isHIST) h1[1]->Draw("HIST");

     gStyle->SetHatchesLineWidth(2);

     YRangeMax = h1[1]->GetMaximum();
     YRangeMin = h1[1]->GetMinimum();
     if(!isSetXRange){
       XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(h1[1]->GetNbinsX());
       XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
     }

     int iPlot = 2;
     while(iPlot <= FigureCount){
       if(isE0) h1[iPlot]->Draw("E0 same");
       if(isHIST) h1[iPlot]->Draw("HIST same");
       if(YRangeMax < h1[iPlot]->GetMaximum()) YRangeMax = h1[iPlot]->GetMaximum();
       if(YRangeMin > h1[iPlot]->GetMinimum()) YRangeMin = h1[iPlot]->GetMinimum();
       if(!isSetXRange){
         if(XRangeMax < h1[iPlot]->GetXaxis()->GetBinUpEdge(h1[iPlot]->GetNbinsX())) XRangeMax = h1[iPlot]->GetXaxis()->GetBinUpEdge(h1[iPlot]->GetNbinsX());
         if(XRangeMin > h1[iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = h1[iPlot]->GetXaxis()->GetBinLowEdge(1);
       }
       iPlot++;
     }

     if(isLogX) gPad->SetLogx();

     if(!isSetYRange){
       if(YRangeMin > 0) h1[1]->GetYaxis()->SetRangeUser(YRangeMin / 1.1, YRangeMax * 1.1);
       if(YRangeMin < 0) h1[1]->GetYaxis()->SetRangeUser(YRangeMin - (YRangeMax * 0.1), YRangeMax * 1.1); 
     }

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i < FigureCount + 1; i++){
       if(!((TString)myLegendName[i] == "")) legend1->AddEntry(h1[i], myLegendName[i],"lpfe");
     }
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(LegendTextSize);
     legend1->SetTextFont(72);
   }

   if(is2D){
     /**************************/
     /*********2D Plot**********/
     /**************************/
     LeftMargin = 0.0;
     RightMargin = 0.2;
     BottomMargin = 0.0;
     TopMargin = 0.0;
     pad1->SetRightMargin(RightMargin);
     h2[1]->SetTitle("");
     h2[1]->SetStats(0);

     h2[1]->GetXaxis()->SetTitle(myXTitle);
     h2[1]->GetXaxis()->SetTitleSize(0.04);
     h2[1]->GetXaxis()->SetTitleFont(42);
     h2[1]->GetXaxis()->SetTitleOffset(1);

     h2[1]->GetXaxis()->SetLabelSize(0.04);
     h2[1]->GetXaxis()->SetLabelFont(42);

     h2[1]->GetYaxis()->SetTitle(myYTitle);
     h2[1]->GetYaxis()->SetTitleSize(0.04);
     h2[1]->GetYaxis()->SetTitleFont(42);
     h2[1]->GetYaxis()->SetTitleOffset(1);

     h2[1]->GetYaxis()->SetLabelSize(0.03);
     h2[1]->GetYaxis()->SetLabelFont(42);

     h2[1]->GetYaxis()->SetNdivisions(505);

     if(isSetXRange) h2[1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetYRange) h2[1]->GetYaxis()->SetRangeUser(ymin, ymax);
     if(isLogX) gPad->SetLogx();
     if(isLogY) gPad->SetLogy();

     if(isSetPaintRange){
       h2[1]->SetMinimum(PaintMin);
       h2[1]->SetMaximum(PaintMax);
     }

     gStyle->SetTextFont(42);
     gStyle->SetTextSize(0.03);
//     gStyle->SetNumberContours(20);

     //gStyle->SetPalette(104);
//     int colors[3] = {kBlue-10, kBlue, kBlue+4};
//     gStyle->SetPalette(3, colors, 1.0);

//     double levels[10] = {kBlue+1, kBlue+2, kBlue+3, kBlue+4, kBlue+5, kBlue+6, kBlue+7, kBlue+8, kBlue+9, kBlue+10};
//     h2[1]->SetContour(200);
//     h2[1]->SetMaximum(1.0);
//     h2[1]->SetMinimum(0.8);
//     h2[1]->SetMarkerSize(1.4);
     if(h2[1]->GetMaximum() < 1.0) PaintTextStyle[1] = "6.2e";

     gStyle->SetPaintTextFormat(PaintTextStyle[1]);
//     myStyle[1]->SetPaintTextFormat(PaintTextStyle[1]);
//     myStyle[1]->cd();

     //h2[1]->UseCurrentStyle();

     h2[1]->SetBarOffset(HistBarOffset[1]);
     h2[1]->Draw("COLZ text45");

     //Define2DTextStyle(1);
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
     int iPlot = 2;
     while(iPlot <= FigureCount){
       gStyle->SetPaintTextFormat(PaintTextStyle[iPlot]);
       //myStyle[iPlot]->SetPaintTextFormat("0.0f");
       //myStyle[iPlot]->cd();

       h2[iPlot]->SetBarOffset(HistBarOffset[iPlot]);
       //h2[iPlot]->Draw("text same");
       //Define2DTextStyle(iPlot);
       iPlot++;
     }

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i < FigureCount + 1; i++){
       if(!((TString)myLegendName[i] == "")) legend1->AddEntry(h2[i], myLegendName[i],"lpfe");
     }
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(LegendTextSize);
     legend1->SetTextFont(72);
   }

   if(withPDFError){
     /****************************************/
     /*******Single Plot with PDF Error*******/
     /**********Set Plot Information**********/
     /****************************************/
     MyN->cd();
     pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);

     BottomMargin = 0.3;
     TopMargin = 0;
     LeftMargin = 0.15;
     RightMargin = 0.05;
     pad2->SetBottomMargin(BottomMargin);
     pad2->SetTopMargin(TopMargin);
     pad2->SetLeftMargin(LeftMargin);
     pad2->SetRightMargin(RightMargin);

     pad2->SetGridx();
     pad2->SetGridy();
     pad2->Draw();
     pad2->cd();


     PDF1[1]->SetTitle("");
     PDF1[1]->SetStats(0);

//     PDF1[1]->SetMarkerStyle(7);
     PDF1[1]->SetMarkerSize(0);
     PDF1[1]->SetMarkerStyle(21);
     PDF1[1]->SetMarkerColor(kBlue+1);
     PDF1[1]->SetLineWidth(4);
     PDF1[1]->SetLineColor(kBlue+1);

     PDF1[1]->SetFillStyle(3544);
     PDF1[1]->SetFillColor(kBlack);
     PDF1[1]->Draw("E0");
     int iPlot = 2;
     while(iPlot <= PDFFigureCount){
       PDF1[iPlot]->Draw("E0 same");
       iPlot++;
     }
     legend2 = new TLegend(legendxmin, legendymin, legendxmax, legendymax);
     for(int i = 1; i < FigureCount; i++){
       legend2->AddEntry(PDF1[i], myLegendName[i],"lpfe");
     }

     PDF1[1]->GetYaxis()->SetNdivisions(505);

     if(Process == 1) PDF1[1]->GetYaxis()->SetTitle("Scale Uncertainty");
     if(Process == 2) PDF1[1]->GetYaxis()->SetTitle("PDF Uncertainty");

     PDF1[1]->GetYaxis()->SetTitle("#frac{#Delta}{#sigma}");

     PDF1[1]->GetYaxis()->SetRangeUser(PDF1[1]->GetMinimum() / 1.01, PDF1[1]->GetMaximum() * 1.2);
     PDF1[1]->GetYaxis()->SetRangeUser(-3, 3);

     PDF1[1]->GetYaxis()->SetTitleSize(0.1);
     PDF1[1]->GetYaxis()->SetTitleFont(72);
     PDF1[1]->GetYaxis()->SetTitleOffset(0.4);

     PDF1[1]->GetYaxis()->SetLabelFont(73);// Absolute font size in pixel (precision 3)
     PDF1[1]->GetYaxis()->SetLabelSize(20);

     PDF1[1]->SetLineWidth(2);

     PDF1[1]->GetXaxis()->SetTitle(myXTitle);
     PDF1[1]->GetXaxis()->SetTitleSize(0.1);
     PDF1[1]->GetXaxis()->SetTitleFont(72);
     PDF1[1]->GetXaxis()->SetTitleOffset(1);

     PDF1[1]->GetXaxis()->SetLabelSize(0.1);
     PDF1[1]->GetXaxis()->SetLabelFont(72);

     if(isLogX) gPad->SetLogx();

     if(isAddGaxis){
//      axis1 = new TGaxis(LeftMargin, BottomMargin, 1 - RightMargin, BottomMargin, wmin, wmax, ndiv, "G");
//      axis1->Draw();
     }
   }
 }

 if((isRatio || isDelta || isDeltaSigma) && !isPDF){
   /****************************************/
   /*********Ratio/Delta/Pull Plot**********/
   /****************************************/
   double sum1 = h1[1]->Integral();
   double sum2 = h1[2]->Integral();
   if(isNorm) h1[1]->Scale(sum2 / sum1);

   MyN = new TCanvas("MyN","MyN",700,700);
   gStyle->SetGridWidth(1);
   MyN->cd();
   pad1 = new TPad("pad1", "pad1", 0, 0.25, 1.0, 1.0);
   BottomMargin = 0;
   TopMargin = 0.15;
   LeftMargin = 0.15;
   RightMargin = 0.05;
   pad1->SetBottomMargin(BottomMargin);
   pad1->SetTopMargin(TopMargin);
   pad1->SetLeftMargin(LeftMargin);
   pad1->SetRightMargin(RightMargin);
//   pad1->SetGridx();
//   pad1->SetGridy();
   pad1->Draw();
   pad1->cd();

   h1[1]->SetTitle("");
   h1[1]->SetStats(0);

   if(isE0){
     h1[1]->Draw("E0");
     h1[2]->Draw("E0 same");
   }
   if(isHIST){
     h1[1]->Draw("HIST");
     h1[2]->Draw("HIST same");
   }

//   h1[1]->GetXaxis()->SetTitle(myXTitle);
//   h1[1]->GetXaxis()->SetTitleSize(75);
//   h1[1]->GetXaxis()->SetTitleFont(72);
//   h1[1]->GetXaxis()->SetTitleOffset(1);

//   h1[1]->GetXaxis()->SetLabelSize(50);
//   h1[1]->GetXaxis()->SetLabelFont(72);

   h1[1]->GetYaxis()->SetTitle(myYTitle);
   h1[1]->GetYaxis()->SetTitleSize(0.06);
   h1[1]->GetYaxis()->SetTitleFont(42);
   h1[1]->GetYaxis()->SetTitleOffset(0.7);

   h1[1]->GetYaxis()->SetLabelSize(0.04);
   h1[1]->GetYaxis()->SetLabelFont(42);

   h1[1]->SetMarkerStyle(7);
   h1[1]->SetMarkerColor(kBlue+1);
   h1[1]->SetLineWidth(3);
   h1[1]->SetLineColor(kBlue+1);

   h1[2]->SetMarkerStyle(7);
   h1[2]->SetMarkerColor(kRed+1);
   h1[2]->SetLineWidth(3);
   h1[2]->SetLineColor(kRed+1);

   YRangeMax = h1[1]->GetMaximum();
   YRangeMin = h1[1]->GetMinimum();
   if(!isSetXRange){
     XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(h1[1]->GetNbinsX());
     XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
   }

   int iPlot = 2;
   while(iPlot <= FigureCount){
     if(YRangeMax < h1[iPlot]->GetMaximum()) YRangeMax = h1[iPlot]->GetMaximum();
     if(YRangeMin > h1[iPlot]->GetMinimum()) YRangeMin = h1[iPlot]->GetMinimum();

     if(!isSetXRange){
       if(XRangeMax < h1[iPlot]->GetXaxis()->GetBinUpEdge(h1[iPlot]->GetNbinsX())) XRangeMax = h1[iPlot]->GetXaxis()->GetBinUpEdge(h1[iPlot]->GetNbinsX());
       if(XRangeMin > h1[iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = h1[iPlot]->GetXaxis()->GetBinLowEdge(1);
     }
     iPlot++;
   }

   if(isLogX) gPad->SetLogx();

//   if(!isSetYRange){
//     if(YRangeMin > 0) h1[1]->GetYaxis()->SetRangeUser(YRangeMin / 1.1, YRangeMax * 1.1);
//     if(YRangeMin < 0) h1[1]->GetYaxis()->SetRangeUser(YRangeMin - (YRangeMax * 0.1), YRangeMax * 1.1);
//   }

   if(!isSetYRange) h1[1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.1, YRangeMax + fabs(YRangeMax) * 0.1);

   double textlength = (legendymax - legendymin) / 2;
   int iText = 0;
   while(iText<=TextCount){
     iText++;
     text[iText] = new TLatex();

     TextX = XRangeMin + (XRangeMax - XRangeMin) * legendxmin;
     TextY = (YRangeMax + fabs(YRangeMax) * 0.1) - (YRangeMax + fabs(YRangeMax) * 0.1 - YRangeMin + fabs(YRangeMin) * 0.1) * ((1 - legendymax) + iText * textlength);
     text[iText]->SetText(TextX, TextY, myText[iText]);
     text[iText]->SetTextSize(0.04);
     text[iText]->SetTextFont(42);
     text[iText]->Draw("same");
   }

   double steplength = legendymax - legendymin;
   legendymax = legendymax - (TextCount + 0.5) * 0.5 * steplength;
   legendymin = legendymin - (TextCount + 0.5) * 0.5 * steplength;

   legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

   legend1->AddEntry(h1[1], myLegendName[1],"lpfe");
   legend1->AddEntry(h1[2], myLegendName[2],"lpfe");
   legend1->SetNColumns(1);
   legend1->Draw("same");
   legend1->SetFillColor(0);
   legend1->SetFillStyle(0);
   legend1->SetLineColor(0);
   legend1->SetLineWidth(0);
   legend1->SetTextSize(0.04);
   legend1->SetTextFont(42);

   MyN->cd();
   pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.25);
   BottomMargin = 0.3;
   TopMargin = 0;
   LeftMargin = 0.15;
   RightMargin = 0.05;
   pad2->SetBottomMargin(BottomMargin);
   pad2->SetTopMargin(TopMargin);
   pad2->SetLeftMargin(LeftMargin);
   pad2->SetRightMargin(RightMargin);
   pad2->SetGridx();
   pad2->SetGridy();
   pad2->Draw();
   pad2->cd();

   h1[0] = (TH1D*)h1[1]->Clone("h0");

   if(isRatio) h1[0]->Divide(h1[2]);
   if(isDelta) h1[0]->Add(h1[2], -1);
   if(isDeltaSigma){
     for(int ibin = 1; ibin < h1[1]->GetNbinsX() + 1; ibin++){
       h1[0]->SetBinContent(ibin, (h1[1]->GetBinContent(ibin) - h1[2]->GetBinContent(ibin)) / sqrt(h1[1]->GetBinError(ibin) * h1[1]->GetBinError(ibin) + h1[2]->GetBinError(ibin) * h1[2]->GetBinError(ibin)));
     }
   }

   h1[0]->SetTitle("");
   h1[0]->SetStats(0);
   if(isE0) h1[0]->Draw("E0");
   if(isHIST) h1[0]->Draw("HIST");

   h1[0]->GetYaxis()->SetNdivisions(505);

   if(isRatio) h1[0]->GetYaxis()->SetTitle("#frac{" + myLegendName[1] + "}{" + myLegendName[2] + "}");
   if(isDelta) h1[0]->GetYaxis()->SetTitle("#Delta" + myYTitle);
   if(isDeltaSigma) h1[0]->GetYaxis()->SetTitle("#frac{#Delta}{#sigma}");

   if(!isSetYRange0) h1[0]->GetYaxis()->SetRangeUser(h1[0]->GetMinimum() / 1.01, h1[0]->GetMaximum() * 1.01);
   else h1[0]->GetYaxis()->SetRangeUser(ymin, ymax);

   h1[0]->GetYaxis()->SetTitleSize(0.1);
   h1[0]->GetYaxis()->SetTitleFont(42);
   h1[0]->GetYaxis()->SetTitleOffset(0.4);

   h1[0]->GetYaxis()->SetLabelFont(42);// Absolute font size in pixel (precision 3)
   h1[0]->GetYaxis()->SetLabelSize(0.1);

   h1[0]->SetLineWidth(2);

   h1[0]->GetXaxis()->SetTitle(myXTitle);
   h1[0]->GetXaxis()->SetTitleSize(0.12);
   h1[0]->GetXaxis()->SetTitleFont(42);
   h1[0]->GetXaxis()->SetTitleOffset(1);

   h1[0]->GetXaxis()->SetLabelSize(0.12);
   h1[0]->GetXaxis()->SetLabelFont(42);

   if(isLogX) gPad->SetLogx();
 }

 if(isPDF){
   /********************************************/
   /*********Ratio Plot with PDF Error**********/
   /********************************************/
   double sum1 = h1[1]->Integral();
   double sum2 = h1[2]->Integral();
   if(isNorm) h1[1]->Scale(sum2 / sum1);

   MyN = new TCanvas("MyN","MyN",700,700);
   gStyle->SetGridWidth(1);
   MyN->cd();
   pad1 = new TPad("pad1", "pad1", 0, 0.3, 1.0, 1.0);
   BottomMargin = 0;
   TopMargin = 0.15;
   LeftMargin = 0.15;
   RightMargin = 0.05;
   pad1->SetBottomMargin(BottomMargin);
   pad1->SetTopMargin(TopMargin);
   pad1->SetLeftMargin(LeftMargin);
   pad1->SetRightMargin(RightMargin);
//   pad1->SetGridx();
//   pad1->SetGridy();
   pad1->Draw();
   pad1->cd();

   h1[1]->SetTitle("");
   h1[1]->SetStats(0);

   if(isE0){
     h1[1]->Draw("E0");
     h1[2]->Draw("E0 same");
   }
   if(isHIST){
     h1[1]->Draw("HIST");
     h1[2]->Draw("HIST same");
   }

   h1[1]->GetYaxis()->SetTitle(myYTitle);
   h1[1]->GetYaxis()->SetTitleSize(0.06);
   h1[1]->GetYaxis()->SetTitleFont(42);
   h1[1]->GetYaxis()->SetTitleOffset(0.8);

   h1[1]->GetYaxis()->SetLabelSize(0.04);
   h1[1]->GetYaxis()->SetLabelFont(42);

   if(isLogX) gPad->SetLogx();

   YRangeMin = h1[1]->GetMinimum();
   YRangeMax = h1[1]->GetMaximum();
   if(!isSetXRange){
     XRangeMax = h1[1]->GetXaxis()->GetBinUpEdge(h1[1]->GetNbinsX());
     XRangeMin = h1[1]->GetXaxis()->GetBinLowEdge(1);
   }

   if(!isSetYRange) h1[1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.1, YRangeMax + fabs(YRangeMax) * 0.1);

   h1[1]->SetLineColor(kBlue+1);
   h1[1]->SetLineWidth(2);
   h1[1]->SetMarkerStyle(7);
   h1[1]->SetMarkerColor(4);

   h1[2]->SetLineColor(kRed);
   h1[2]->SetLineWidth(2);
   h1[2]->SetMarkerStyle(7);
   h1[2]->SetMarkerColor(2);

   double textlength = (legendymax - legendymin) / 2;
   int iText = 0;
   while(iText<=TextCount){
     iText++;
     text[iText] = new TLatex();

     TextX = XRangeMin + (XRangeMax - XRangeMin) * legendxmin;
     TextY = (YRangeMax + fabs(YRangeMax) * 0.1) - (YRangeMax + fabs(YRangeMax) * 0.1 - YRangeMin + fabs(YRangeMin) * 0.1) * ((1 - legendymax) + iText * textlength);
     text[iText]->SetText(TextX, TextY, myText[iText]);
     text[iText]->SetTextSize(0.04);
     text[iText]->SetTextFont(42);
     text[iText]->Draw("same");
   }

   double steplength = legendymax - legendymin;
   legendymax = legendymax - (TextCount + 0.5) * 0.5 * steplength;
   legendymin = legendymin - (TextCount + 0.5) * 0.5 * steplength;

   legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);
   legend1->SetNColumns(1);
   legend1->AddEntry(h1[1], myLegendName[1],"lpfe");
   legend1->AddEntry(h1[2], myLegendName[2],"lpfe");
   legend1->SetFillColor(0);
   legend1->SetFillStyle(0);
   legend1->SetLineColor(0);
   legend1->Draw("same");
   legend1->SetTextSize(0.04);
   legend1->SetTextFont(42);

   MyN->cd(); 
   pad2 = new TPad("pad2", "pad2", 0, 0.18, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0);
   pad2->SetLeftMargin(0.15);
   pad2->SetRightMargin(0.05);
   pad2->SetGridx();
   pad2->SetGridy();
   pad2->Draw();
   pad2->cd();

   h1[0] = (TH1D*)h1[1]->Clone("h0");

   if(isRatio) h1[0]->Divide(h1[2]);
   if(isDelta) h1[0]->Add(h1[2], -1);
   if(isDeltaSigma){
     for(int ibin = 1; ibin < h1[1]->GetNbinsX() + 1; ibin++){
       h1[0]->SetBinContent(ibin, (h1[1]->GetBinContent(ibin) - h1[2]->GetBinContent(ibin)) / sqrt(h1[1]->GetBinError(ibin) * h1[1]->GetBinError(ibin) + h1[2]->GetBinError(ibin) * h1[2]->GetBinError(ibin)));
     }
   }

   h1[0]->SetTitle("");
   h1[0]->SetStats(0);
   if(isE0) h1[0]->Draw("E0");
   if(isHIST) h1[0]->Draw("HIST");

   h1[0]->GetYaxis()->SetNdivisions(505);

   if(isRatio) h1[0]->GetYaxis()->SetTitle("#frac{" + myLegendName[1] + "}{" + myLegendName[2] + "}");
   if(isDelta) h1[0]->GetYaxis()->SetTitle("#Delta" + myYTitle);
   if(isDeltaSigma) h1[0]->GetYaxis()->SetTitle("#frac{#Delta}{#sigma}");

   if(!isSetYRange0){
     if(isRatio) h1[0]->GetYaxis()->SetRangeUser(h1[0]->GetMinimum() / 1.01, h1[0]->GetMaximum() * 1.01);
     if(isDelta || isDeltaSigma) h1[0]->GetYaxis()->SetRangeUser(h1[0]->GetMinimum() - 1, h1[0]->GetMaximum() + 1);
   }
   else h1[0]->GetYaxis()->SetRangeUser(ymin, ymax);

   h1[0]->GetYaxis()->SetTitleSize(0.2);
   h1[0]->GetYaxis()->SetTitleFont(42);
   h1[0]->GetYaxis()->SetTitleOffset(0.2);

   h1[0]->GetYaxis()->SetLabelFont(42);
   h1[0]->GetYaxis()->SetLabelSize(0.2);

   h1[0]->SetLineWidth(2);

   if(isLogX) gPad->SetLogx();

   MyN->cd();
   pad3 = new TPad("pad3", "pad3", 0, 0, 1, 0.18);
   pad3->SetTopMargin(0);
   pad3->SetBottomMargin(0.35);
   pad3->SetLeftMargin(0.15);
   pad3->SetRightMargin(0.05);
//   pad3->SetGridx();
//   pad3->SetGridy();
   pad3->Draw();
   pad3->cd();

   h1[3]->SetStats(0);
   h1[3]->SetTitle("");
   h1[4]->SetStats(0);
   h1[4]->SetTitle("");

   if(h1[3]) h1[3]->Scale(PDFScaleFactor);
   if(h1[4]) h1[4]->Scale(PDFScaleFactor);

   if(isSetPDFUncRange){
     h1[3]->GetYaxis()->SetRangeUser(PDFUncRangeMin, PDFUncRangeMax);
     h1[4]->GetYaxis()->SetRangeUser(PDFUncRangeMin, PDFUncRangeMax);
   }

   h1[3]->GetYaxis()->SetTitle("PDF Unc.");
   h1[3]->GetYaxis()->SetTitleSize(0.14);
   h1[3]->GetYaxis()->SetTitleFont(42);
   h1[3]->GetYaxis()->SetTitleOffset(0.31);

   h1[3]->GetYaxis()->SetNdivisions(505);
   h1[3]->GetYaxis()->SetLabelFont(42);
   h1[3]->GetYaxis()->SetLabelSize(0.08);

   h1[3]->GetXaxis()->SetTitle(myXTitle);
   h1[3]->GetXaxis()->SetTitleSize(0.15);
   h1[3]->GetXaxis()->SetTitleFont(42);
   h1[3]->GetXaxis()->SetTitleOffset(1);

   h1[3]->GetXaxis()->SetLabelFont(42);
   h1[3]->GetXaxis()->SetLabelSize(0.15);

   h1[4]->GetYaxis()->SetTitle("PDF Unc.");
   h1[4]->GetYaxis()->SetTitleSize(0.14);
   h1[4]->GetYaxis()->SetTitleFont(42);
   h1[4]->GetYaxis()->SetTitleOffset(0.31);

   h1[4]->GetYaxis()->SetNdivisions(505);
   h1[4]->GetYaxis()->SetLabelFont(42);
   h1[4]->GetYaxis()->SetLabelSize(0.08);

   h1[4]->GetXaxis()->SetTitle(myXTitle);
   h1[4]->GetXaxis()->SetTitleSize(0.15);
   h1[4]->GetXaxis()->SetTitleFont(42);
   h1[4]->GetXaxis()->SetTitleOffset(1);

   h1[4]->GetXaxis()->SetLabelFont(42);
   h1[4]->GetXaxis()->SetLabelSize(0.15);

   h1[3]->SetLineWidth(2);
   h1[3]->SetLineColor(kBlue);
   h1[4]->SetLineWidth(2);
   h1[4]->SetLineColor(kRed+1);

   h1[3]->SetFillColor(0);
   h1[4]->SetFillColor(0);

   h1[3]->Draw("E0");
   h1[4]->Draw("E0 same");

   if(isLogX) gPad->SetLogx();

   legend2 = new TLegend(0.19, 0.65, 0.49, 0.93);
   legend2->SetNColumns(1);
//   legend2->AddEntry(h1[3], "","lpfe");
//   legend2->AddEntry(h1[4], "","lpfe");
   legend2->SetFillColor(0);
   legend2->SetFillStyle(0);
   legend2->SetLineColor(0);
//   legend2->Draw("same");
   legend2->SetTextSize(0.13);
   legend2->SetTextFont(42);
 }



 /////////////////
 // StartCustom //
 /////////////////


 if(isCustom){
   MyN = new TCanvas("MyN","MyN",CanvasX,CanvasY);
   MyN->cd();
   if(isLogX) gPad->SetLogx();
   gStyle->SetGridWidth(1);

   if(TotalPadNumber == 1){
     pad1 = new TPad("pad1", "pad1", 0, CustomPadYMin[1], 1.0, CustomPadYMax[1]);

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

     if(isCustomHist[1][1]){

       if(isLogX) Custom[1][1]->GetXaxis()->SetMoreLogLabels();
       if(isXNoExponent) Custom[1][1]->GetXaxis()->SetNoExponent();

       if(isMoreLogLabels) Custom[1][1]->GetXaxis()->SetMoreLogLabels();
       else Custom[1][1]->GetXaxis()->SetMoreLogLabels(kFALSE);

       Custom[1][1]->SetTitle("");
       Custom[1][1]->SetStats(0);
  
       Custom[1][1]->GetXaxis()->SetTitle(myXTitle);
       Custom[1][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[1]);
       Custom[1][1]->GetXaxis()->SetTitleFont(132);
       Custom[1][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[1]);
       Custom[1][1]->GetXaxis()->SetNdivisions(505);

       Custom[1][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[1]);
       Custom[1][1]->GetXaxis()->SetLabelFont(132);
  
       Custom[1][1]->GetYaxis()->SetTitle(myYTitle);
       Custom[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
       Custom[1][1]->GetYaxis()->SetTitleFont(132);
       Custom[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);
       Custom[1][1]->GetYaxis()->SetNdivisions(CustomNdivisions[1]);
  
       Custom[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
       Custom[1][1]->GetYaxis()->SetLabelFont(132);
  
  //     Custom[1][1]->SetMarkerStyle(7);
  //     Custom[1][1]->SetMarkerSize(0);
  //     Custom[1][1]->SetMarkerStyle(21);
  //     Custom[1][1]->SetMarkerColor(kBlue+1);
  //     Custom[1][1]->SetLineWidth(4);
  //     Custom[1][1]->SetLineColor(kBlue+1);
  
  //     Custom[1][1]->SetFillStyle(3544);
  //     Custom[1][1]->SetFillColor(kBlack);
  
  
  //     if(isE0) Custom[1][1]->Draw("E0");
  //     if(isHIST) Custom[1][1]->Draw("HIST");
  //     if(isE0 && !isResetError[1][1]) Custom[1][1]->Draw("E0");
  //     if(isE2 && !isResetError[1][1]) Custom[1][1]->Draw("E2");
  //     if(isE3 && !isResetError[1][1]) Custom[1][1]->Draw("E3");
  //     if(isE4 && !isResetError[1][1]) Custom[1][1]->Draw("E4");
  //     if(isPMC && !isResetError[1][1]) Custom[1][1]->Draw("P0");
  //     if(isPLC && !isResetError[1][1]) Custom[1][1]->Draw("L");
  //     if(isHIST && !isResetError[1][1]) Custom[1][1]->Draw("HIST");
  
       if(!isResetError[1][1]) Custom[1][1]->Draw(CustomPlot[1][1]);
       if(isResetError[1][1]) Custom[1][1]->Draw("E2");
  
  //     if(isInputError){
  //       HistError[1]->Draw("E2 same");
  //     }
  
       if(isFittingPlot){
  //       FittingPlot->Draw("E0 same");
  //       FittingPlot->SetLineColor(kRed + 1);
       }
  
       gStyle->SetHatchesLineWidth(2);
  
       YRangeMax = Custom[1][1]->GetMaximum();
       YRangeMin = Custom[1][1]->GetMinimum();
       if(!isSetXRange){
         XRangeMax = Custom[1][1]->GetXaxis()->GetBinUpEdge(Custom[1][1]->GetNbinsX());
         XRangeMin = Custom[1][1]->GetXaxis()->GetBinLowEdge(1);
       }
  
       if(isLogY){
         Custom[1][1]->SetMinimum();
       }

     }

     if(isCustomFunction[1][1]){

       CustomFunction[1][1]->SetTitle("");

       CustomFunction[1][1]->GetXaxis()->SetTitle(myXTitle);
       CustomFunction[1][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[1]);
       CustomFunction[1][1]->GetXaxis()->SetTitleFont(132);
       CustomFunction[1][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[1]);
       CustomFunction[1][1]->GetXaxis()->SetNdivisions(505);

       CustomFunction[1][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[1]);
       CustomFunction[1][1]->GetXaxis()->SetLabelFont(132);

       CustomFunction[1][1]->GetYaxis()->SetTitle(myYTitle);
       CustomFunction[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
       CustomFunction[1][1]->GetYaxis()->SetTitleFont(132);
       CustomFunction[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);
       CustomFunction[1][1]->GetYaxis()->SetNdivisions(CustomNdivisions[1]);

       CustomFunction[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
       CustomFunction[1][1]->GetYaxis()->SetLabelFont(132);

       CustomFunction[1][1]->Draw();

       YRangeMax = CustomFunction[1][1]->GetMaximum();
       YRangeMin = CustomFunction[1][1]->GetMinimum();
       if(!isSetXRange){
         XRangeMax = CustomFunction[1][1]->GetMaximumX();
         XRangeMin = CustomFunction[1][1]->GetMinimumX();
       }

       if(isLogY){
         Custom[1][1]->SetMinimum();
       }

     }

     if(isCustomGraph[1][1]){

       CustomGraph[1][1]->SetTitle("");

       CustomGraph[1][1]->GetXaxis()->SetTitle(myXTitle);
       CustomGraph[1][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[1]);
       CustomGraph[1][1]->GetXaxis()->SetTitleFont(132);
       CustomGraph[1][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[1]);
       CustomGraph[1][1]->GetXaxis()->SetNdivisions(505);

       CustomGraph[1][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[1]);
       CustomGraph[1][1]->GetXaxis()->SetLabelFont(132);

       CustomGraph[1][1]->GetYaxis()->SetTitle(myYTitle);
       CustomGraph[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
       CustomGraph[1][1]->GetYaxis()->SetTitleFont(132);
       CustomGraph[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);
       CustomGraph[1][1]->GetYaxis()->SetNdivisions(CustomNdivisions[1]);

       CustomGraph[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
       CustomGraph[1][1]->GetYaxis()->SetLabelFont(132);

       CustomGraph[1][1]->Draw("L");
     }
  
       int iPlot = 2;
       while(iPlot <= CustomFigureCount[1]){

         if(isCustomHist[1][iPlot]){
           if(isLogY) Custom[1][iPlot]->SetMinimum();
           if(isLogX) Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels();
           if(isXNoExponent) Custom[1][iPlot]->GetXaxis()->SetNoExponent();

           if(isMoreLogLabels) Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels();
           else Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

           if(!isResetError[1][iPlot]) Custom[1][iPlot]->Draw((CustomPlot[1][iPlot] + " same").Data());
           if(isResetError[1][iPlot]){
              Custom[1][iPlot]->Draw("E2 same");
              Custom[1][1]->Draw("E0 same");
           }
           if(isResetError[1][iPlot]){
             iPlot++;
             continue;
           }
  
           if(YRangeMax < Custom[1][iPlot]->GetMaximum()) YRangeMax = Custom[1][iPlot]->GetMaximum();
           if(YRangeMin > Custom[1][iPlot]->GetMinimum()) YRangeMin = Custom[1][iPlot]->GetMinimum();
           if(!isSetXRange){
             if(XRangeMax < Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX())) XRangeMax = Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX());
             if(XRangeMin > Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1);
           }
         }
         if(isCustomFunction[1][iPlot]){
           if(isLogY) CustomFunction[1][iPlot]->SetMinimum();
           if(isLogX) CustomFunction[1][iPlot]->GetXaxis()->SetMoreLogLabels();
           if(isXNoExponent) CustomFunction[1][iPlot]->GetXaxis()->SetNoExponent();

           if(isMoreLogLabels) CustomFunction[1][iPlot]->GetXaxis()->SetMoreLogLabels();
           else CustomFunction[1][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

           if(!isResetError[1][iPlot]) CustomFunction[1][iPlot]->Draw("same");

           if(YRangeMax < CustomFunction[1][iPlot]->GetMaximum()) YRangeMax = CustomFunction[1][iPlot]->GetMaximum();
           if(YRangeMin > CustomFunction[1][iPlot]->GetMinimum()) YRangeMin = CustomFunction[1][iPlot]->GetMinimum();
           if(!isSetXRange){
             if(XRangeMax < CustomFunction[1][iPlot]->GetMaximumX()) XRangeMax = CustomFunction[1][iPlot]->GetMaximumX();
             if(XRangeMin > CustomFunction[1][iPlot]->GetMinimumX()) XRangeMin = CustomFunction[1][iPlot]->GetMinimumX();
           }
         }

         if(isCustomGraph[1][iPlot]){
           CustomGraph[1][iPlot]->Draw(CustomPlot[1][iPlot]);
         }

         iPlot++;
       }
  
     if(isLogY) pad1->SetLogy();
  
     if(!isSetCustomYRange[1]){
       //if(YRangeMin > 0) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin / 1.3, YRangeMax * 1.3);
       //if(YRangeMin < 0) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - (YRangeMin * 0.3), YRangeMax * 1.3);

       if(isCustomHist[1][1]){
         if(!isLogY) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.3, YRangeMax + fabs(YRangeMax) * 0.3);
       }
       if(isCustomFunction[1][1]){
         if(!isLogY) CustomFunction[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.3, YRangeMax + fabs(YRangeMax) * 0.3);
       }

     }

     if(isCustomHist[1][1]){
       if(isSetXRange) Custom[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     }
     if(isCustomFunction[1][1]){
       if(isSetXRange) CustomFunction[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     }


     if(isSetCustomYRange[1]){
       if(isCustomHist[1][1]) Custom[1][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);
       if(isCustomFunction[1][1]) CustomFunction[1][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);

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

  
     double textlength = (legendymax - legendymin) / (CustomFigureCount[1] / LegendNColumns);
     int iText = 1;
     while(iText<=TextCount){
       text[iText] = new TLatex();
//       text[iText] = new TMathText();
  
       TextX = XRangeMin + (XRangeMax - XRangeMin) * legendxmin;
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * legendxmin));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1 - legendymax) + iText * textlength);
       if(isLogY) TextY = pow(10, (log10(1.3 * YRangeMax) - ((log10(1.3 * YRangeMax) - log10(0.7 * YRangeMin)) * ((1 - legendymax) + iText * textlength))));
       cout<<"iText = "<<iText<<" TextX = "<<TextX<<" TextY = "<<TextY<<endl;
       text[iText]->SetText(TextX, TextY, myText[iText]);
       text[iText]->SetTextSize(CustomLegendSize[1]);
       text[iText]->SetTextFont(TextFont[iText]);
       text[iText]->Draw("same");
       iText++;
     }

     int iCustomText = 1;
     while(iCustomText <= CustomTextCount){
       CustomText[iCustomText] = new TLatex();
       double TextX, TextY;
       TextX = XRangeMin + (XRangeMax - XRangeMin) * CustomTextX[iCustomText];
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * CustomTextX[iCustomText]));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1.0 - CustomTextY[iCustomText]));
       if(isLogY) TextY = pow(10, (log10(1.3 * YRangeMax) - (log10(1.3 * YRangeMax) - log10(0.7 * YRangeMin)) * (1.0 - CustomTextY[iCustomText])));
       CustomText[iCustomText]->SetText(TextX, TextY, myCustomText[iCustomText]);
       CustomText[iCustomText]->SetTextSize(CustomLegendSize[1]);
       CustomText[iCustomText]->SetTextFont(TextFont[iText]);
       CustomText[iCustomText]->Draw("same");
       iCustomText++;
     }

     int iLine = 1;
     while(iLine <= LineCount){
       line[iLine]->Draw("same");
       iLine++;
     }

     int iArrow = 1;
     while(iArrow <= ArrowCount){
       arrow[iArrow]->Draw();
       iArrow++;
     }

     double steplength = legendymax - legendymin;
     legendymax = legendymax - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] / LegendNColumns)) * steplength;
     legendymin = legendymin - (TextCount + 0.5) * (1.0 / (CustomFigureCount[1] / LegendNColumns)) * steplength;
  
     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);
  
     for(int i = 1; i <= CustomFigureCount[1]; i++){
       if(!((TString)myCustomLegendName[1][i] == "") && !isResetError[1][i]){

         if(isCustomHist[1][i]){
           if(CustomPlot[1][i] == "E0" || CustomPlot[1][i] == "E5" || CustomPlot[1][i] == "E") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"pel");
           else if(CustomPlot[1][i] == "E2") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"fl");
           else if(CustomPlot[1][i] == "HIST") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"l");
           else legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"p");
           if(!((TString)myCustomLegendName[1][i] == "") && isResetError[1][i]) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lf");
         }

         if(isCustomFunction[1][i]){
           if(CustomPlot[1][i] == "E0") legend1->AddEntry(CustomFunction[1][i], myCustomLegendName[1][i],"l");
           else legend1->AddEntry(CustomFunction[1][i], myCustomLegendName[1][i],"l");
         }
         if(isCustomGraph[1][i]){
           if(CustomPlot[1][i] == "E0") legend1->AddEntry(CustomGraph[1][i], myCustomLegendName[1][i],"l");
           else legend1->AddEntry(CustomGraph[1][i], myCustomLegendName[1][i],"l");
         }
       }
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
     if(isLogX) Custom[1][1]->GetXaxis()->SetMoreLogLabels();
     if(isXNoExponent) Custom[1][1]->GetXaxis()->SetNoExponent();

     if(isMoreLogLabels) Custom[1][1]->GetXaxis()->SetMoreLogLabels();
     else Custom[1][1]->GetXaxis()->SetMoreLogLabels(kFALSE);

     Custom[1][1]->SetTitle("");
     Custom[1][1]->SetStats(0);

     Custom[1][1]->GetYaxis()->SetNdivisions(CustomNdivisions[1]);

     Custom[1][1]->GetYaxis()->SetTitle(myYTitle);
     Custom[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
     Custom[1][1]->GetYaxis()->SetTitleFont(132);
     Custom[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);

     Custom[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
     Custom[1][1]->GetYaxis()->SetLabelFont(132);

//     Custom[1][1]->SetMarkerStyle(7);
//     Custom[1][1]->SetMarkerColor(kBlue+1);
//     Custom[1][1]->SetLineWidth(3);
//     Custom[1][1]->SetLineColor(kBlue+1);

//     if(isE0 && !isResetError[1][1]) Custom[1][1]->Draw("E0");
//     if(isE2 && !isResetError[1][1]) Custom[1][1]->Draw("E2");
//     if(isE3 && !isResetError[1][1]) Custom[1][1]->Draw("E3");
//     if(isE4 && !isResetError[1][1]) Custom[1][1]->Draw("E4");
//     if(isPMC && !isResetError[1][1]) Custom[1][1]->Draw("P0");
//     if(isPLC && !isResetError[1][1]) Custom[1][1]->Draw("PL");
//     if(isHIST && !isResetError[1][1]) Custom[1][1]->Draw("HIST");

     if(!isResetError[1][1]) Custom[1][1]->Draw(CustomPlot[1][1]);
     if(isResetError[1][1]) Custom[1][1]->Draw("E2");

//     if(isInputError){
//       HistError[1]->Draw("E2 same");
//     }

     gStyle->SetHatchesLineWidth(2);

     YRangeMax = Custom[1][1]->GetMaximum();
     YRangeMin = Custom[1][1]->GetMinimum();
     if(!isSetXRange){
       XRangeMax = Custom[1][1]->GetXaxis()->GetBinUpEdge(Custom[1][1]->GetNbinsX());
       XRangeMin = Custom[1][1]->GetXaxis()->GetBinLowEdge(1);
     }

     if(isLogY){
       Custom[1][1]->SetMinimum();
     }

     int iPlot = 2;
     while(iPlot <= CustomFigureCount[1]){
      if(isLogX) Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels();
      if(isXNoExponent) Custom[1][iPlot]->GetXaxis()->SetNoExponent();

      if(isMoreLogLabels) Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels();
      else Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

      if(isLogY) Custom[1][iPlot]->SetMinimum();
      //cout<<"Integral of "<<Custom[1][iPlot]->GetName()<<": "<<Custom[1][iPlot]->Integral()<<endl;

//      if(isE0 && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E0 same");
//      if(isE2 && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E2 same");
//      if(isE3 && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E3 same");
//      if(isE4 && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E4 same");
//      if(isPMC && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("P0 same");
//      if(isPLC && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("PL same");
//      if(isHIST && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("HIST same");

      if(!isResetError[1][iPlot]) Custom[1][iPlot]->Draw((CustomPlot[1][iPlot] + " same").Data());
      if(isResetError[1][iPlot]){
        Custom[1][iPlot]->Draw("E2 same");
        for(int i = 1; i <= iPlot - 1; i++){
          Custom[1][i]->Draw("E0 same");
        }
      }
      if(isResetError[1][iPlot]){
        iPlot++;
        continue;
      }

      if(YRangeMax < Custom[1][iPlot]->GetMaximum()) YRangeMax = Custom[1][iPlot]->GetMaximum();
      if(YRangeMin > Custom[1][iPlot]->GetMinimum()) YRangeMin = Custom[1][iPlot]->GetMinimum();
      if(!isSetXRange){
        if(XRangeMax < Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX())) XRangeMax = Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX());
        if(XRangeMin > Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1);
      }
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();
     if(isLogY) gPad->SetLogy();

     if(!isSetYRange && !isLogY) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.3, YRangeMax + fabs(YRangeMax) * 0.3);

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

//     double textlength = (legendymax - legendymin) / 2;
     double textlength = (legendymax - legendymin) / CustomFigureCount[1];
     int iText = 1;
     while(iText<=TextCount){
       text[iText] = new TLatex();

       TextX = XRangeMin + (XRangeMax - XRangeMin) * (legendxmin + 0.01);
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * legendxmin));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1 - legendymax) + iText * textlength);
       if(isLogY) TextY = pow(10, (log10(1.3 * YRangeMax) - (log10(1.3 * YRangeMax) - log10(1.3 * YRangeMin)) * (((1 - legendymax) + iText * textlength))));
       text[iText]->SetText(TextX, TextY, myText[iText]);
       text[iText]->SetTextSize(CustomLegendSize[1]);
       text[iText]->SetTextFont(TextFont[iText]);
       text[iText]->Draw("same");
       cout<<"TextX = "<<TextX<<" TextY = "<<TextY<<" YRangeMin = "<<YRangeMin<<" YRangeMax = "<<YRangeMax<<endl;
       iText++;
     }

     int iCustomText = 1;
     while(iCustomText <= CustomTextCount){
       CustomText[iCustomText] = new TLatex();
       double TextX, TextY;
       TextX = XRangeMin + (XRangeMax - XRangeMin) * CustomTextX[iCustomText];
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * CustomTextX[iCustomText]));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1.0 - CustomTextY[iCustomText]));
       if(isLogY) TextY = pow(10, (log10(1.3 * YRangeMax) - (log10(1.3 * YRangeMax) - log10(0.7 * YRangeMin)) * (1.0 - CustomTextY[iCustomText])));
       CustomText[iCustomText]->SetText(TextX, TextY, myCustomText[iCustomText]);
       CustomText[iCustomText]->SetTextSize(CustomLegendSize[1]);
       CustomText[iCustomText]->SetTextFont(TextFont[iText]);
       CustomText[iCustomText]->Draw("same");
       iCustomText++;
     }

     double steplength = legendymax - legendymin;
//     legendymax = legendymax - (TextCount + 0.5) * 0.5 * steplength;
//     legendymin = legendymin - (TextCount + 0.5) * 0.5 * steplength;
//     legendymax = legendymax - (TextCount + 1.0 / CustomFigureCount[1]) * (1.0 / CustomFigureCount[1]) * steplength;
//     legendymin = legendymin - (TextCount + 1.0 / CustomFigureCount[1]) * (1.0 / CustomFigureCount[1]) * steplength;
     legendymax = legendymax - (TextCount + 0.5) * (1.0 / CustomFigureCount[1]) * steplength;
     legendymin = legendymin - (TextCount + 0.5) * (1.0 / CustomFigureCount[1]) * steplength;

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i < CustomFigureCount[1] + 1; i++){
       if(!((TString)myCustomLegendName[1][i] == "") && !isResetError[1][i]){
         if(CustomPlot[1][i] == "E0") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lfe");
         else if(CustomPlot[1][i] == "E2") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"fl");
         else if(CustomPlot[1][i] == "HIST") legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"l");
         else legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"p");
       }
       if(!((TString)myCustomLegendName[1][i] == "") && isResetError[1][i]) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lf");
//       if(!((TString)myCustomLegendName[1][i] == "")) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lpfe");
     }

     legend1->SetNColumns(LegendNColumns);
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(CustomLegendSize[1]);
     legend1->SetTextFont(132);

//     if(isE0 && !isResetError[1][1]) Custom[1][1]->Draw("E0");
//     if(isHIST && !isResetError[1][1]) Custom[1][1]->Draw("HIST");
//     if(isResetError[1][1]) Custom[1][1]->Draw("E2");

//     iPlot = 1;
//     while(iPlot <= CustomFigureCount[1]){
//      if(isE0 && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E0 same");
//      if(isHIST && !isResetError[1][iPlot]) Custom[1][iPlot]->Draw("HIST same");
//      if(isResetError[1][iPlot]) Custom[1][iPlot]->Draw("E2 same");
//      iPlot++;
//     }

     MyN->cd();
     pad2 = new TPad("pad2", "pad2", 0, CustomPadYMin[2], 1, CustomPadYMax[2]);

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
     Custom[2][1]->SetStats(0);

     Custom[2][1]->GetXaxis()->SetNdivisions(505);
     Custom[2][1]->GetYaxis()->SetNdivisions(CustomNdivisions[2]);

     YRangeMax = Custom[2][1]->GetMaximum();
     YRangeMin = Custom[2][1]->GetMinimum();
     iPlot = 2;
     while(iPlot <= CustomFigureCount[2]){
       if(YRangeMax < Custom[2][iPlot]->GetMaximum()) YRangeMax = Custom[2][iPlot]->GetMaximum();
       if(YRangeMin > Custom[2][iPlot]->GetMinimum()) YRangeMin = Custom[2][iPlot]->GetMinimum();
       iPlot++;
     }

     if(isSetXRange) Custom[2][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(!isSetCustomYRange[2]) Custom[2][1]->GetYaxis()->SetRangeUser(YRangeMin * 0.7, YRangeMax * 1.3);
     if(isSetCustomYRange[2]) Custom[2][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[2], CustomYRangeMax[2]);

     Custom[2][1]->GetYaxis()->SetTitle(myPadName[2]);
     Custom[2][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[2]);
     Custom[2][1]->GetYaxis()->SetTitleFont(132);
     Custom[2][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[2]);

     Custom[2][1]->GetYaxis()->SetLabelFont(132);// Absolute font size in pixel (precision 3)
     Custom[2][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[2]);

//     Custom[2][1]->SetLineWidth(2);

     Custom[2][1]->GetXaxis()->SetTitle(myXTitle);
     Custom[2][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[2]);
     Custom[2][1]->GetXaxis()->SetTitleFont(132);
     Custom[2][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[2]);

     Custom[2][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[2]);
     Custom[2][1]->GetXaxis()->SetLabelFont(132);


/*     if(isE0) Custom[2][1]->Draw("E0");
     if(isHIST) Custom[2][1]->Draw("HIST");

     iPlot = 1;
     while(iPlot <= CustomFigureCount[2]){
      if(isE0) Custom[2][iPlot]->Draw("E0 same");
      if(isHIST) Custom[2][iPlot]->Draw("HIST same");
      iPlot++;
     }
*/

//     if((isE0 || isE2) && !isResetError[2][1]) Custom[2][1]->Draw("E0");
//     if((isE3) && !isResetError[2][1]) Custom[2][1]->Draw("E3");
//     if((isE4) && !isResetError[2][1]) Custom[2][1]->Draw("E4");
//     if((isPMC) && !isResetError[2][1]) Custom[2][1]->Draw("P0");
//     if((isPLC) && !isResetError[2][1]) Custom[2][1]->Draw("PL");
//     if((isHIST) && !isResetError[2][1]) Custom[2][1]->Draw("HIST");

     if(!isResetError[2][1]) Custom[2][1]->Draw(CustomPlot[2][1]);
     if(isResetError[2][1]) Custom[2][1]->Draw("E2");

     iPlot = 1;
     while(iPlot <= CustomFigureCount[2]){
      if(isLogX) Custom[2][iPlot]->GetXaxis()->SetMoreLogLabels();
      if(isXNoExponent) Custom[2][iPlot]->GetXaxis()->SetNoExponent();

      if(isMoreLogLabels) Custom[2][iPlot]->GetXaxis()->SetMoreLogLabels();
      else Custom[2][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

//      if((isE0 || isE2) && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("E0 same");
//      if((isE3) && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("E3 same");
//      if((isE4) && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("E4 same");
//      if((isPMC) && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("P0 same");
//      if((isPLC) && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("PL same");
//      if((isHIST) && !isResetError[2][iPlot]) Custom[2][iPlot]->Draw("HIST same");

      if(!isResetError[2][iPlot]) Custom[2][iPlot]->Draw((CustomPlot[2][iPlot] + " same").Data());
      if(isResetError[2][iPlot]){ 
        Custom[2][iPlot]->Draw("E2 same");
        for(int i = 1; i <= iPlot - 1; i++){
          Custom[2][i]->Draw("E0 same");
        }
      }
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();

     if(isDrawLegend2){
       legend2 = new TLegend(legend2xmin * (1 - LeftMargin - RightMargin) + LeftMargin, legend2ymin * (1 - TopMargin - BottomMargin) + BottomMargin, legend2xmax * (1 - LeftMargin - RightMargin) + LeftMargin, legend2ymax * (1 - TopMargin - BottomMargin) + BottomMargin);

       for(int i = 1; i < CustomFigureCount[2] + 1; i++){
         if(!((TString)myCustomLegendName[2][i] == "") && !isResetError[2][i]) legend2->AddEntry(Custom[2][i], myCustomLegendName[2][i],"le");
         if(!((TString)myCustomLegendName[2][i] == "") && isResetError[2][i]) legend2->AddEntry(Custom[2][i], myCustomLegendName[2][i],"lf");
       }

       legend2->SetNColumns(Legend2NColumns);
       legend2->Draw("same");
       legend2->SetFillColor(0);
       legend2->SetFillStyle(0);
       legend2->SetLineColor(0);
       legend2->SetLineWidth(0);
       legend2->SetTextSize(CustomLegendSize[2]);
       legend2->SetTextFont(132);
     }

   }
   if(TotalPadNumber == 3){
     pad1 = new TPad("pad1", "pad1", 0, CustomPadYMin[1], 1.0, CustomPadYMax[1]);

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

     if(isLogX) Custom[1][1]->GetXaxis()->SetMoreLogLabels();
     if(isXNoExponent) Custom[1][1]->GetXaxis()->SetNoExponent();

     if(isMoreLogLabels) Custom[1][1]->GetXaxis()->SetMoreLogLabels();
     else Custom[1][1]->GetXaxis()->SetMoreLogLabels(kFALSE);

     Custom[1][1]->SetTitle("");
     Custom[1][1]->SetStats(0);

     Custom[1][1]->GetYaxis()->SetTitle(myYTitle);
     Custom[1][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[1]);
     Custom[1][1]->GetYaxis()->SetTitleFont(132);
     Custom[1][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[1]);

     Custom[1][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[1]);
     Custom[1][1]->GetYaxis()->SetLabelFont(132);

     //Custom[1][1]->SetMarkerStyle(7);
     //Custom[1][1]->SetMarkerColor(kBlue+1);
     //Custom[1][1]->SetLineWidth(3);
     //Custom[1][1]->SetLineColor(kBlue+1);

//     if(isE0) Custom[1][1]->Draw("E0");
//     if(isHIST) Custom[1][1]->Draw("HIST");
     Custom[1][1]->Draw(CustomPlot[1][1]);

     YRangeMax = Custom[1][1]->GetMaximum();
     YRangeMin = Custom[1][1]->GetMinimum();
     if(!isSetXRange){
       XRangeMax = Custom[1][1]->GetXaxis()->GetBinUpEdge(Custom[1][1]->GetNbinsX());
       XRangeMin = Custom[1][1]->GetXaxis()->GetBinLowEdge(1);
     }

     int iPlot = 1;
     while(iPlot <= CustomFigureCount[1]){
//      if(isE0) Custom[1][iPlot]->Draw("E0 same");
//      if(isHIST) Custom[1][iPlot]->Draw("HIST same");
      if(isLogX) Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels();
      if(isXNoExponent) Custom[1][iPlot]->GetXaxis()->SetNoExponent();

      if(isMoreLogLabels) Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels();
      else Custom[1][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

      Custom[1][iPlot]->Draw((CustomPlot[1][iPlot] + " same").Data());
      if(YRangeMax < Custom[1][iPlot]->GetMaximum()) YRangeMax = Custom[1][iPlot]->GetMaximum();
      if(YRangeMin > Custom[1][iPlot]->GetMinimum()) YRangeMin = Custom[1][iPlot]->GetMinimum();
      if(!isSetXRange){
        if(XRangeMax < Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX())) XRangeMax = Custom[1][iPlot]->GetXaxis()->GetBinUpEdge(Custom[1][iPlot]->GetNbinsX());
        if(XRangeMin > Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1)) XRangeMin = Custom[1][iPlot]->GetXaxis()->GetBinLowEdge(1);
      }
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();

     if(!isSetYRange) Custom[1][1]->GetYaxis()->SetRangeUser(YRangeMin - fabs(YRangeMin) * 0.3, YRangeMax + fabs(YRangeMax) * 0.3);

     if(isSetXRange) Custom[1][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[1]) Custom[1][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[1], CustomYRangeMax[1]);

     double textlength = (legendymax - legendymin) / 2;
     int iText = 1;
     while(iText<=TextCount){
       text[iText] = new TLatex();

       TextX = XRangeMin + (XRangeMax - XRangeMin) * legendxmin;
       if(isLogX) TextX = pow(10, (log10(XRangeMin) + (log10(XRangeMax) - log10(XRangeMin)) * legendxmin));
       TextY = (YRangeMax + fabs(YRangeMax) * 0.3) - (YRangeMax + fabs(YRangeMax) * 0.3 - YRangeMin + fabs(YRangeMin) * 0.3) * ((1 - legendymax) + iText * textlength);
       if(isLogY) TextY = pow(10, (log10(1.2 * YRangeMax) - (log10(1.3 * (YRangeMax - YRangeMin)) * ((1 - legendymax) + iText * textlength))));
       text[iText]->SetText(TextX, TextY, myText[iText]);
       text[iText]->SetTextSize(CustomLegendSize[1]);
       text[iText]->SetTextFont(TextFont[iText]);
       text[iText]->Draw("same");
       iText++;
     }

     double steplength = legendymax - legendymin;
     legendymax = legendymax - (TextCount + 0.5) * 0.5 * steplength;
     legendymin = legendymin - (TextCount + 0.5) * 0.5 * steplength;

     legend1 = new TLegend(legendxmin * (1 - LeftMargin - RightMargin) + LeftMargin, legendymin * (1 - TopMargin - BottomMargin) + BottomMargin, legendxmax * (1 - LeftMargin - RightMargin) + LeftMargin, legendymax * (1 - TopMargin - BottomMargin) + BottomMargin);

     for(int i = 1; i < CustomFigureCount[1] + 1; i++){
       if(!((TString)myCustomLegendName[1][i] == "") && !isResetError[1][i]) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lpfe");
       if(!((TString)myCustomLegendName[1][i] == "") && isResetError[1][i]) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lf");
//       if(!((TString)myCustomLegendName[1][i] == "")) legend1->AddEntry(Custom[1][i], myCustomLegendName[1][i],"lpfe");
     }

     legend1->SetNColumns(LegendNColumns);
     legend1->Draw("same");
     legend1->SetFillColor(0);
     legend1->SetFillStyle(0);
     legend1->SetLineColor(0);
     legend1->SetLineWidth(0);
     legend1->SetTextSize(CustomLegendSize[1]);
     legend1->SetTextFont(132);


     MyN->cd();
     pad2 = new TPad("pad2", "pad2", 0, CustomPadYMin[2], 1, CustomPadYMax[2]);

     BottomMargin = CustomBottomMargin[2];
     TopMargin = CustomTopMargin[2];
     LeftMargin = CustomLeftMargin[2];
     RightMargin = CustomRightMargin[2];

     pad2->SetTopMargin(TopMargin);
     pad2->SetBottomMargin(BottomMargin);
     pad2->SetLeftMargin(LeftMargin);
     pad2->SetRightMargin(RightMargin);
     if(isCustomGrid[2]) pad2->SetGridx();
     if(isCustomGrid[2]) pad2->SetGridy();
     pad2->Draw();
     pad2->cd();

     Custom[2][1]->SetTitle("");
     Custom[2][1]->SetStats(0);

     Custom[2][1]->GetYaxis()->SetNdivisions(CustomNdivisions[2]);

     if(!isSetYRange0) Custom[2][1]->GetYaxis()->SetRangeUser(Custom[2][1]->GetMinimum() / 1.01, Custom[2][1]->GetMaximum() * 1.01);
     else Custom[2][1]->GetYaxis()->SetRangeUser(ymin, ymax);

     if(isSetXRange) Custom[2][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[2]) Custom[2][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[2], CustomYRangeMax[2]);

     Custom[2][1]->GetYaxis()->SetTitle(myPadName[2]);
     Custom[2][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[2]);
     Custom[2][1]->GetYaxis()->SetTitleFont(132);
     Custom[2][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[2]);

     Custom[2][1]->GetYaxis()->SetLabelFont(132);// Absolute font size in pixel (precision 3)
     Custom[2][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[2]);

     Custom[2][1]->SetLineWidth(2);

     Custom[2][1]->GetXaxis()->SetTitle(myXTitle);
     Custom[2][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[2]);
     Custom[2][1]->GetXaxis()->SetTitleFont(132);
     Custom[2][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[2]);

     Custom[2][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[2]);
     Custom[2][1]->GetXaxis()->SetLabelFont(132);


//     if(isE0) Custom[2][1]->Draw("E0");
//     if(isHIST) Custom[2][1]->Draw("HIST");
     Custom[2][1]->Draw(CustomPlot[2][1]);

     iPlot = 1;
     while(iPlot <= CustomFigureCount[2]){
//      if(isE0) Custom[2][iPlot]->Draw("E0 same");
//      if(isHIST) Custom[2][iPlot]->Draw("HIST same");
      if(isLogX) Custom[2][iPlot]->GetXaxis()->SetMoreLogLabels();
      if(isXNoExponent) Custom[2][iPlot]->GetXaxis()->SetNoExponent();

      if(isMoreLogLabels) Custom[2][iPlot]->GetXaxis()->SetMoreLogLabels();
      else Custom[2][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

      Custom[2][iPlot]->Draw((CustomPlot[2][iPlot] + " same").Data());
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();

     MyN->cd();
     pad3 = new TPad("pad3", "pad3", 0, CustomPadYMin[3], 1, CustomPadYMax[3]);

     BottomMargin = CustomBottomMargin[3];
     TopMargin = CustomTopMargin[3];
     LeftMargin = CustomLeftMargin[3];
     RightMargin = CustomRightMargin[3];
     pad3->SetTopMargin(TopMargin);
     pad3->SetBottomMargin(BottomMargin);
     pad3->SetLeftMargin(LeftMargin);
     pad3->SetRightMargin(RightMargin);
     if(isCustomGrid[3]) pad3->SetGridx();
     if(isCustomGrid[3]) pad3->SetGridy();
     pad3->Draw();
     pad3->cd();

     Custom[3][1]->SetStats(0);
     Custom[3][1]->SetTitle("");

     Custom[3][1]->GetYaxis()->SetTitle(myPadName[3]);
     Custom[3][1]->GetYaxis()->SetTitleSize(CustomYTitleSize[3]);
     Custom[3][1]->GetYaxis()->SetTitleFont(132);
     Custom[3][1]->GetYaxis()->SetTitleOffset(CustomYTitleOffset[3]);

     Custom[3][1]->GetXaxis()->SetNdivisions(505);
     Custom[3][1]->GetYaxis()->SetNdivisions(CustomNdivisions[3]);
     Custom[3][1]->GetYaxis()->SetLabelFont(132);
     Custom[3][1]->GetYaxis()->SetLabelSize(CustomYLabelSize[3]);

     Custom[3][1]->GetXaxis()->SetTitle(myXTitle);
     Custom[3][1]->GetXaxis()->SetTitleSize(CustomXTitleSize[3]);
     Custom[3][1]->GetXaxis()->SetTitleFont(132);
     Custom[3][1]->GetXaxis()->SetTitleOffset(CustomXTitleOffset[3]);
     Custom[3][1]->GetXaxis()->SetNdivisions(505);

     Custom[3][1]->GetXaxis()->SetLabelFont(132);
     Custom[3][1]->GetXaxis()->SetLabelSize(CustomXLabelSize[3]);

     //Custom[3][1]->SetLineWidth(2);
     //Custom[3][1]->SetLineColor(kBlue);

     if(isSetXRange) Custom[3][1]->GetXaxis()->SetRangeUser(XRangeMin, XRangeMax);
     if(isSetCustomYRange[3]) Custom[3][1]->GetYaxis()->SetRangeUser(CustomYRangeMin[3], CustomYRangeMax[3]);

     Custom[3][1]->Draw(CustomPlot[3][1]);

     iPlot = 1;
     while(iPlot <= CustomFigureCount[3]){
//      if(isE0) Custom[3][iPlot]->Draw("E0 same");
//      if(isHIST) Custom[3][iPlot]->Draw("HIST same");
      if(isLogX) Custom[3][iPlot]->GetXaxis()->SetMoreLogLabels();
      if(isXNoExponent) Custom[3][iPlot]->GetXaxis()->SetNoExponent();

      if(isMoreLogLabels) Custom[3][iPlot]->GetXaxis()->SetMoreLogLabels();
      else Custom[3][iPlot]->GetXaxis()->SetMoreLogLabels(kFALSE);

      Custom[3][iPlot]->Draw((CustomPlot[3][iPlot] + " same").Data());
      iPlot++;
     }

     if(isLogX) gPad->SetLogx();

   }

 }

 if(DoSave) MyN->SaveAs(myFigureName);
// delete MyN;
}

void Figure::DrawCorrelation(const char* fileName, const char* histName)
{
 TFile* file = new TFile(fileName);
 TH2D *h1 = (TH2D *)file->Get(histName);

 TPad *pad1;

 MyN = new TCanvas("MyN","MyN",2500,2000);
 MyN->cd();
 pad1 = new TPad("pad1", "pad1", 0, 0, 1.0, 1.0);
 pad1->SetBottomMargin(0.1);
 pad1->SetTopMargin(0.1);
 pad1->SetLeftMargin(0.15);
 pad1->SetRightMargin(0.1);
 pad1->SetGridx();
 pad1->SetGridy();
 pad1->Draw();
 pad1->cd();

 h1->SetTitle("");
 h1->SetStats(0);

 h1->GetXaxis()->SetTitle(myXTitle);
 h1->GetXaxis()->SetTitleSize(0.04);
 h1->GetXaxis()->SetTitleFont(72);
 h1->GetXaxis()->SetTitleOffset(1);

 h1->GetXaxis()->SetLabelSize(0.04);
 h1->GetXaxis()->SetLabelFont(72);

 h1->GetYaxis()->SetTitle(myYTitle);
 h1->GetYaxis()->SetTitleSize(0.04);
 h1->GetYaxis()->SetTitleFont(72);
 h1->GetYaxis()->SetTitleOffset(1);

 h1->GetYaxis()->SetLabelSize(0.03);
 h1->GetYaxis()->SetLabelFont(72);

 gStyle->SetTextFont(72);
 h1->Draw("COLZ");

 if(DoSave) MyN->SaveAs(myFigureName);
 delete MyN;
}

double Figure::CalculateChi2(TH1D* h1, TH1D* h2)
{
 bool isOutput = false;

 double Chi2 = 0;
 double N1, N2, N1Error, N2Error;

 for(int ibinx = 0; ibinx < h1->GetNbinsX(); ibinx++)
 {
  N1 = h1->GetBinContent(ibinx + 1);
  N2 = h2->GetBinContent(ibinx + 1);

  N1Error = h1->GetBinError(ibinx + 1);
  N2Error = h2->GetBinError(ibinx + 1);

  if(isOutput) cout<<"bin "<<ibinx + 1<<" Ratio: "<<N1 / N2<<" : Difference: "<<(N1 - N2) * (N1 - N2)<<" Error: "<<(N1Error * N1Error + N2Error * N2Error)<<endl;

  if((N1Error * N1Error + N2Error * N2Error) < 0.00000000001){
    if(isOutput) cout<<"INFO: The denomenator is zero, skip this point."<<endl;
    continue;
  }

  Chi2 += (N1 - N2) * (N1 - N2) / (N1Error * N1Error + N2Error * N2Error);
 }

 if(isOutput) cout<<"Chi2: "<<Chi2<<endl;
 return Chi2;
}

