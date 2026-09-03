#ifndef Figure_Graph_h
#define Figure_Graph_h

#include "RootCommon.h"

using namespace std;

class Graph
{
 public:

 TCanvas *MyN;

 TString myFigureName;
 TString myXTitle;
 TString myYTitle;

 TFile* file[100];

 TH1D* h1[100];
 TH2D* h2[100];

 TH1D* tmph1[100];

 TText* text[100];
 TMathText* mathtext[100];
 TStyle* myStyle[100];

 TLine* line[100];
 int LineCount = 0;

 TLegend *legend1;
 TLegend *legend2;
 TLegend *legend3;

 TString myLegendName[100];
 TString myCustomLegendName[10][100];
 TString myText[100];
 TString PaintTextStyle[100];
 TString CustomText[100];
 double CustomTextX[100];
 double CustomTextY[100];

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
 int LegendNColumns = 1;
 TString CustomLegendType[10][100];

 bool isInput;
 bool isInputGraph[100] = {false};
 bool isDirectGraph = false;

 bool isLogX = false;
 bool isLogY = false;

 bool DoSave = false;

 bool isDefineHist = false;

 int FigureCount;
 int TextCount;
 int CustomTextCount = 0;

 int TotalPadNumber = 0;
 int CustomFigureCount[10] = {0};
 TGraphErrors* Custom[10][500] = {0};
 TMultiGraph* CustomMultiGraph[10] = {0};
 TGraphErrors* CustomLimit[10][10] = {0};
 TH1D* CustomHist[10][500] = {0};
 TH1D* Values[500] = {0};
 int NData = 0;
 bool isCustom = false;
 TString myPadName[10];
 TString CustomPlot[10][500];
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
 int CustomXNdivisions[10] = {1};
 int CustomYNdivisions[10] = {1};

 double CustomBottomMargin[10] = {0.0};
 double CustomTopMargin[10] = {0.0};
 double CustomLeftMargin[10] = {0.0};
 double CustomRightMargin[10] = {0.0};

 double CustomPadYMax[10] = {0.0};
 double CustomPadYMin[10] = {0.0};
 double CustomPadXMax[10] = {0.0};
 double CustomPadXMin[10] = {0.0};

 bool isCustomGrid[10] = {false};

 bool isNormToOne[500] = {false};

 map<pair<int, int>, Color_t> CustomColor;
 map<int, Color_t> myColor;

 TH1D* tmpHist[500];

 bool isOutput = false;

 bool isSetXRange = false;

 double CanvasX = 1000.0;
 double CanvasY = 1000.0;

 Graph(const char* FigureName, const char* XTitle, const char* YTitle);
 virtual ~Graph();
 virtual void SetMode(const char* ModeName);
 virtual void SetLogX(){isLogX = true;};
 virtual void SetLogY(){isLogY = true;};
 virtual void DefineHist(int Number, TString name, TString title, int nbin, double left, double right);
 virtual void DefineHist(int Number, TString name, TString title, int nbinx, double* xbins);

 virtual void SetCustomPad(int TotalPadNumber);
 virtual void CustomSetting(int PadNumber, int histNumber1, int histNumber2 = 0, TString process = "");
 virtual void SetCustomPlotFormat(int PadNumber, int Number, Color_t Color, Style_t style = 21, bool isFilled = false);
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
 virtual void SetCustomLeftMargin(int PadNumber, double size){this->CustomLeftMargin[PadNumber] = size;};
 virtual void SetCustomRightMargin(int PadNumber, double size){this->CustomRightMargin[PadNumber] = size;};
 virtual void SetCustomNdivisions(int PadNumber, int ndiv);
 virtual void SetCustomXNdivisions(int PadNumber, int ndiv);
 virtual void SetCustomYNdivisions(int PadNumber, int ndiv);
 virtual void SetCustomGrid(int PadNumber, bool flag);
 virtual void SetCustomBarOffset(int PadNumber, int Number, double size);
 virtual void SetCustomMarkerStyle(int PadNumber, int Number, Style_t style);
 virtual void SetCustomLineStyle(int PadNumber, int Number, Style_t style);
 virtual void SetCustomLineWidth(int PadNumber, int Number, double size);
 virtual void SetCustomFillStyle(int PadNumber, int Number, Style_t style);
 virtual void SetCustomFillAlpha(int PadNumber, int Number, double alpha);
 virtual void DefineCustomHist(int Number, int histNumber1, int histNumber2 = 0, TString process = "", const char* LegendName = "");
 virtual void CustomNorm(int fig1, int fig2, int BaseOne = 1);
 virtual void SetCustomPlot(int PadNumber, int Number, TString format);
 virtual void SetCanvasSize(double X, double Y){this->CanvasX = X; this->CanvasY = Y;};

 virtual void InputCustomLimit(double xmin, double xmax, double ymin, double ymax);

 virtual void Input(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void Input(int Number, vector<double> x, vector<double> y, const char* legendName = "");
 virtual void InputGraph(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void InputGraph(int Number, TGraphErrors* g, const char* legendName = "");
 virtual void Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName = "");
 virtual void Input3D(int Number, const char* rootName, const char* histName, int binx, int biny, int binz, const char* legendName = "");
 virtual void Input(int Number, TH1D* h, const char* legendName = "");
 virtual void InputValueAndError(int Number, double Value, double Error, const char* legendName = "");
 virtual void InputNData(int NData){this->NData = NData;}
 virtual void GetConvexHull(int Number);

 virtual void NormToOne(int Number);

 virtual void SetXRange(double xmin, double xmax);

 virtual void AddText(int Number, const char* TextContent);
 virtual void AddLine(int Number, double x1, double y1, double x2, double y2);
 virtual void AddCustomText(int Number, double x, double y, TString TextContent);

 virtual void Draw();
 virtual void SaveFigure(){DoSave = true;};
 virtual void SetLegendPosition(double xmin, double ymin, double xmax, double ymax);
 virtual void SetLegend2Position(double xmin, double ymin, double xmax, double ymax);
 virtual void SetLegendNColumns(int n){this->LegendNColumns = n;};

 virtual void Compare(TString Option, TString isNorm = "");

 bool isRemoveLastPoint[10][500] = {false};
 virtual void RemoveLastPoint(int PadNumber, int Number){isRemoveLastPoint[PadNumber][Number] = true;};

 bool isIgnoreError[10][500] = {false};
 virtual void IgnoreCustomError(int PadNumber, int Number){isIgnoreError[PadNumber][Number] = true;}

 bool isRightAlign = false;
 virtual void SetTextRightAlign(){isRightAlign = true;}

 double TextLeftBias = 0.0;
 void SetTextLeftBias(double bias){TextLeftBias = bias;}

 double CustomTextSize[10] = {0.4};
 bool isSetCustomTextSize[10] = {false};
 void SetCustomTextSize(int n, double size){isSetCustomTextSize[n] = true; CustomTextSize[n] = size;}

};

#endif
