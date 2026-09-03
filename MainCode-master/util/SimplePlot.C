#include <iostream>
#include <fstream>
#include "RootCommon.h"
#include "Figure/Figure.h"
#include "Figure/Graph.h"

using namespace std;

void ReadTable(TString FileName, TH1D* &h1, TString name, int iColumn)
{
    ifstream datafile(FileName);

    string FileLine;
    vector<double> result;

    vector<vector<double>> FullTable;
    while(getline(datafile, FileLine)){
      vector<double> LineVector;
      double Value;
      stringstream LineStream(FileLine);
      while(LineStream >> Value){
        LineVector.push_back(Value);
      }
      if(LineVector.size() == 0) break;

      FullTable.push_back(LineVector);//FullTable.at(i).at(j) is i row and j column
    }

    for(int i = 0; i < FullTable.size(); i++){
      result.push_back(FullTable.at(i).at(iColumn));
    }

    h1 = new TH1D(name, name, result.size(), 0, result.size());

    for(int i = 0; i < result.size(); i++){
      h1->SetBinContent(i + 1, result.at(i));
      h1->SetBinError(i + 1, 0.0);
    }
}

int main(int argc, char** argv)
{
 if(argc != 5){
   cout<<"Usage: ./SimplePlot datafile xColumn yColumn plotname"<<endl;
   return 0;
 }

 TString FileName = argv[1];
 int xColumn = stoi(argv[2]);
 int yColumn = stoi(argv[3]);
 TString HistName = argv[4];

 TH1D* hist;
 TH1D* hist_x;

 ReadTable(FileName, hist,   "hist",   yColumn);
 ReadTable(FileName, hist_x, "hist_x", xColumn);

 TGraphErrors* graph = new TGraphErrors(hist->GetNbinsX());
 for(int ibin = 1; ibin <= hist->GetNbinsX(); ibin++){
   graph->SetPointX(ibin, hist_x->GetBinContent(ibin));
   graph->SetPointY(ibin, hist->GetBinContent(ibin));
   cout<<hist_x->GetBinContent(ibin)<<"  "<<hist->GetBinContent(ibin)<<endl;
 }

 Graph* g = new Graph(HistName + ".png", "x", "y");
 g->SetMode("CUSTOM");
 g->InputGraph(1, graph, "");
 g->SetCustomPlotFormat(1, 1, kRed);
 g->SetCustomPlot(1, 1, "AC");
 g->SetCustomPad(1);
 g->Draw();

 return 1;
}
