#include "/mnt/home/fuyao3/figure/Graph.h"

void xQplot()
{
 function<double(double, double)> GetXMin = [&](double Q, double ECM){
   double x = pow(Q, 2) / pow(ECM, 2);
   return x;
 };

 function<vector<double>(double, double, int, double)> Logspace = [&](double start, double stop, int num, double base){
   double realStart = log(start) / log(base);
   double realEnd = log(stop) / log(base);
 
   std::vector<double> retval;
   retval.resize(num);
 
   for(int i = 0; i <= num - 1; i++){
     retval.at(i) = pow(base, realStart + (realEnd - realStart) * i / static_cast<double>(num - 1));
   }
 
   return retval;
 };

 vector<double> QVector = Logspace(10.0, 10000.0, 30, 10.0);
 vector<double> xVector(QVector.size());

 for(int i = 0; i < QVector.size(); i++){
   xVector.at(i) = GetXMin(QVector.at(i), 13000.0);
 }

 QVector.push_back(QVector.at(QVector.size() - 1));
 xVector.push_back(1.0);

 QVector.push_back(QVector.at(0));
 xVector.push_back(1.0);

 QVector.push_back(QVector.at(0));
 xVector.push_back(xVector.at(0));

 TGraphErrors* input = new TGraphErrors(QVector.size());
 for(int i = 0; i < QVector.size(); i++){
   input->SetPointX(i + 1, xVector.at(i));
   input->SetPointY(i + 1, QVector.at(i));
 }

 Graph* g;

 g = new Graph("region_xQ.pdf", "x", "Q [GeV]");
 g->SetMode("CUSTOM");
 g->InputGraph(1, input, "LHC 13 TeV");
 g->InputGraph(2, "save.root", "Data204_xQplot", "E866 pp xf");
 g->InputGraph(3, "save.root", "Data201_xQplot", "E605");
 g->InputGraph(4, "save.root", "Data160_xQplot", "HERA I + II");
 g->InputGraph(5, "save.root", "Data_BCDMS_xQplot", "BCDMS");
 g->InputGraph(6, "save.root", "Data_CDHSW_xQplot", "CDHSW");
 g->GetConvexHull(2);
 g->GetConvexHull(3);
 g->GetConvexHull(4);
 g->GetConvexHull(5);
 g->GetConvexHull(6);
 g->Compare("MultiSimple");
 g->SetCustomPlot(1, 1, "Fill");
 g->SetCustomPlot(1, 2, "Fill");
 g->SetCustomPlot(1, 3, "Fill");
 g->SetCustomPlot(1, 4, "Fill");
 g->SetCustomPlot(1, 5, "Fill");
 g->SetCustomPlot(1, 6, "Fill");
 g->SetCustomFillAlpha(1, 1,  0.1);
 g->SetCustomFillAlpha(1, 2,  1.0);
 g->SetCustomFillAlpha(1, 3,  1.0);
 g->SetCustomFillAlpha(1, 4,  1.0);
 g->SetCustomFillAlpha(1, 5,  0.9);
 g->SetCustomFillAlpha(1, 6,  0.9);
 g->SetCustomFillStyle(1, 1,  3001);
 g->SetCustomFillStyle(1, 2,  3002);
 g->SetCustomFillStyle(1, 3,  3001);
 g->SetCustomFillStyle(1, 4,  3004);
 g->SetCustomFillStyle(1, 5,  3001);
 g->SetCustomFillStyle(1, 6,  3006);
 g->SetCanvasSize(1000.0, 1000.0);
 g->CustomTopMargin[1] = 0.1125;
 g->CustomBottomMargin[1] = 0.075;
 g->SetLogX();
 g->SetLogY();
 g->SetXRange(1e-7, 1.0);
 g->SetCustomYRange(1, 0.5, 1e5);
 g->SetLegendPosition(0.1, 0.5, 0.5, 0.95);
 g->SetCustomLegendSize(1, 0.04);
 g->AddLine(1, GetXMin(100.0, 13000.0), 100.0, 1.0, 100.0);
 g->AddLine(2, GetXMin(1000.0, 13000.0), 1000.0, 1.0, 1000.0);
 g->AddLine(3, GetXMin(3000.0, 13000.0), 3000.0, 1.0, 3000.0);
 g->AddCustomText(1, GetXMin(120.0, 13000.0), 120.0, "M = 100 GeV");
 g->AddCustomText(2, GetXMin(1200.0, 13000.0), 1200.0, "M = 1 TeV");
 g->AddCustomText(3, GetXMin(3300.0, 13000.0), 3400.0, "M = 3 TeV");
 g->Draw();
}
