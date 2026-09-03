#ifndef Figure_Figure_h
#define Figure_Figure_h

#include "RootCommon.h"

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

 virtual void Input(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void Input2D(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName = "");
 virtual void Input3D(int Number, const char* rootName, const char* histName, int binx, int biny, int binz, const char* legendName = "");
 virtual void InputError(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void ResetError(int Number, int ErrorNumber);
 virtual void Input2DError(int Number, const char* rootName, const char* histName, int binx, int biny, const char* legendName = "");
 virtual void InputTGraph(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void InputTree(int Number, const char* rootName, const char* treeName, const char* histName, int nbin, double left, double right, const char* VariableName, const char* WeightName, const char* legendName = "");
 virtual void Input(int Number, TH1D* h, const char* legendName = "");
 virtual void InputTF1(int Number, const char* rootName, const char* histName, const char* legendName = "");
 virtual void InputTF1(int Number, TF1* f, const char* legendName = "");
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
#endif

