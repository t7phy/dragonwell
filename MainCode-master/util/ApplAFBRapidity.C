#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Calculation/ApplGridHelper.h"

int main(int argc, char** argv)
{
 TString GridName_Forward = "/msu/data/t3work12/yaofu/MCFM_ApplGrid/AFB_Rapidity/Forward/grid-40-6-15-3-Z_Forward.root";
 TString GridName_Backward = "/msu/data/t3work12/yaofu/MCFM_ApplGrid/AFB_Rapidity/Backward/grid-40-6-15-3-Z_Backward.root";

 map<tuple<TString, int>, TH1D *> ForwardHist;
 map<tuple<TString, int>, TH1D *> BackwardHist;
 map<tuple<TString, int>, TH1D *> AFBHist;

 TFile* file = new TFile("save.root", "RECREATE");
 file->cd();

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->LinkFile(file);

 grid->InitialGrid(GridName_Forward);
 grid->InitialGrid(GridName_Backward);

 auto ApplConvolute = [&](ApplGridHelper* g, TString PDFName, int iSet){
   file->cd();

   g->InitialPDF(PDFName, iSet);
   ForwardHist[make_tuple(PDFName, iSet)] = g->ConvoluteBasic(GridName_Forward, "Forward_Rapidity");
   BackwardHist[make_tuple(PDFName, iSet)] = g->ConvoluteBasic(GridName_Backward, "Backward_Rapidity");

   AFBHist[make_tuple(PDFName, iSet)] = (TH1D *)ForwardHist.at(make_tuple(PDFName, iSet))->Clone((TString)"AFB_" + PDFName + "_" + iSet);
   AFBFunction(ForwardHist.at(make_tuple(PDFName, iSet)), BackwardHist.at(make_tuple(PDFName, iSet)), AFBHist.at(make_tuple(PDFName, iSet)));
 };

 ApplConvolute(grid, "CT18NNLO", 0);
 ApplConvolute(grid, "MSHT20nnlo_as118", 0);
 ApplConvolute(grid, "NNPDF31_nnlo_as_0118", 0);
 ApplConvolute(grid, "MSTW2008nnlo90cl", 0);

 grid->SaveFile();

 return 1;

}
