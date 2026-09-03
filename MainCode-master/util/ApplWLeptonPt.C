#include "Calculation/ApplGridHelper.h"

TString GridName_WPlus_LeptonPt = "/ustcfs2/yfu/MCFM_Dilution/WPlus_LeptonPt/grid-40-6-15-3-WPlus_WPlus_LeptonPt.root";
TString GridName_WMinus_LeptonPt = "/ustcfs2/yfu/MCFM_Dilution/WMinus_LeptonPt/grid-40-6-15-3-WMinus_WMinus_LeptonPt.root";
TString GridName_WPlus_Mass = "/ustcfs2/yfu/MCFM_Dilution/WPlus_Mass/grid-40-6-15-3-WPlus_WPlus_Mass.root";
TString GridName_WMinus_Mass = "/ustcfs2/yfu/MCFM_Dilution/WMinus_Mass/grid-40-6-15-3-WMinus_WMinus_Mass.root";
TString GridName_WPlus_WPt = "/ustcfs2/yfu/MCFM_Dilution/WPlus_WPt/grid-40-6-15-3-WPlus_WPlus_WPt.root";
TString GridName_WMinus_WPt = "/ustcfs2/yfu/MCFM_Dilution/WMinus_WPt/grid-40-6-15-3-WMinus_WMinus_WPt.root";
TString GridName_WPlus_LeptonEta = "/ustcfs2/yfu/MCFM_Dilution/WPlus_LeptonEta/grid-40-6-15-3-WPlus_WPlus_LeptonEta.root";
TString GridName_WPlus_NeutrinoEta = "/ustcfs2/yfu/MCFM_Dilution/WPlus_NeutrinoEta/grid-40-6-15-3-WPlus_WPlus_NeutrinoEta.root";
TString GridName_WMinus_LeptonEta = "/ustcfs2/yfu/MCFM_Dilution/WMinus_LeptonEta/grid-40-6-15-3-WMinus_WMinus_LeptonEta.root";
TString GridName_WMinus_NeutrinoEta = "/ustcfs2/yfu/MCFM_Dilution/WMinus_NeutrinoEta/grid-40-6-15-3-WMinus_WMinus_NeutrinoEta.root";
TString GridName_WPlus_WY = "/ustcfs2/yfu/MCFM_Dilution/WPlus_WY/grid-40-6-15-3-WPlus_WPlus_WY.root";
TString GridName_WMinus_WY = "/ustcfs2/yfu/MCFM_Dilution/WMinus_WY/grid-40-6-15-3-WMinus_WMinus_WY.root";

void ApplConvolute(ApplGridHelper* grid)
{
/* TH1D* WPlus_LeptonPt = grid->ConvoluteBasic(GridName_WPlus_LeptonPt, "WPlus_LeptonPt");
 TH1D* WMinus_LeptonPt = grid->ConvoluteBasic(GridName_WMinus_LeptonPt, "WMinus_LeptonPt");

 TH1D* WPlus_LeptonPt_udbar = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonPt, "udbar", "WPlus_LeptonPt");
 TH1D* WPlus_LeptonPt_ugluon = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonPt, "ugluon", "WPlus_LeptonPt");
 TH1D* WPlus_LeptonPt_gluondbar = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonPt, "gluondbar", "WPlus_LeptonPt");

 TH1D* WPlus_LeptonPt_udbar_Combine = grid->ConvoluteCombineSubProcBasic(GridName_WPlus_LeptonPt, vector<TString>{"udbar", "ugluon", "gluondbar"}, "WPlus_LeptonPt_udbar_Combine");

 TH1D* WMinus_LeptonPt_dubar = grid->ConvoluteSubProcBasic(GridName_WMinus_LeptonPt, "dubar", "WMinus_LeptonPt");

 TH1D* WPlus_WPt = grid->ConvoluteBasic(GridName_WPlus_WPt, "WPlus_WPt");
 TH1D* WMinus_WPt = grid->ConvoluteBasic(GridName_WMinus_WPt, "WMinus_WPt");

 TH1D* WPlus_WPt_udbar = grid->ConvoluteSubProcBasic(GridName_WPlus_WPt, "udbar", "WPlus_WPt");
 TH1D* WPlus_WPt_ugluon = grid->ConvoluteSubProcBasic(GridName_WPlus_WPt, "ugluon", "WPlus_WPt");
 TH1D* WPlus_WPt_gluondbar = grid->ConvoluteSubProcBasic(GridName_WPlus_WPt, "gluondbar", "WPlus_WPt");

 TH1D* WPlus_WPt_udbar_Combine = grid->ConvoluteCombineSubProcBasic(GridName_WPlus_WPt, vector<TString>{"udbar", "ugluon", "gluondbar"}, "WPlus_WPt_udbar_Combine");
*/

 TH1D* WPlus_LeptonEta = grid->ConvoluteBasic(GridName_WPlus_LeptonEta, "WPlus_LeptonEta");
 TH1D* WPlus_NeutrinoEta = grid->ConvoluteBasic(GridName_WPlus_NeutrinoEta, "WPlus_NeutrinoEta");
 TH1D* WMinus_LeptonEta = grid->ConvoluteBasic(GridName_WMinus_LeptonEta, "WMinus_LeptonEta");
 TH1D* WMinus_NeutrinoEta = grid->ConvoluteBasic(GridName_WMinus_NeutrinoEta, "WMinus_NeutrinoEta");

 TH1D* WPlus_WY = grid->ConvoluteBasic(GridName_WPlus_WY, "WPlus_WY");
 TH1D* WMinus_WY = grid->ConvoluteBasic(GridName_WMinus_WY, "WMinus_WY");

 TH1D* WPlus_WY_udbar = grid->ConvoluteSubProcBasic(GridName_WPlus_WY, "udbar", "WPlus_WY");
 TH1D* WPlus_WY_dbaru = grid->ConvoluteSubProcBasic(GridName_WPlus_WY, "dbaru", "WPlus_WY");
 TH1D* WMinus_WY_dubar = grid->ConvoluteSubProcBasic(GridName_WMinus_WY, "dubar", "WMinus_WY");
 TH1D* WMinus_WY_ubard = grid->ConvoluteSubProcBasic(GridName_WMinus_WY, "ubard", "WMinus_WY");

 TH1D* WPlus_WY_csbar = grid->ConvoluteSubProcBasic(GridName_WPlus_WY, "csbar", "WPlus_WY");
 TH1D* WPlus_WY_sbarc = grid->ConvoluteSubProcBasic(GridName_WPlus_WY, "sbarc", "WPlus_WY");
 TH1D* WMinus_WY_scbar = grid->ConvoluteSubProcBasic(GridName_WMinus_WY, "scbar", "WMinus_WY");
 TH1D* WMinus_WY_cbars = grid->ConvoluteSubProcBasic(GridName_WMinus_WY, "cbars", "WMinus_WY");

 TH1D* WPlus_LeptonEta_udbar = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonEta, "udbar", "WPlus_LeptonEta");
 TH1D* WPlus_LeptonEta_dbaru = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonEta, "dbaru", "WPlus_LeptonEta");
 TH1D* WMinus_LeptonEta_dubar = grid->ConvoluteSubProcBasic(GridName_WMinus_LeptonEta, "dubar", "WMinus_LeptonEta");
 TH1D* WMinus_LeptonEta_ubard = grid->ConvoluteSubProcBasic(GridName_WMinus_LeptonEta, "ubard", "WMinus_LeptonEta");

 TH1D* WPlus_LeptonEta_csbar = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonEta, "csbar", "WPlus_LeptonEta");
 TH1D* WPlus_LeptonEta_sbarc = grid->ConvoluteSubProcBasic(GridName_WPlus_LeptonEta, "sbarc", "WPlus_LeptonEta");
 TH1D* WMinus_LeptonEta_scbar = grid->ConvoluteSubProcBasic(GridName_WMinus_LeptonEta, "scbar", "WMinus_LeptonEta");
 TH1D* WMinus_LeptonEta_cbars = grid->ConvoluteSubProcBasic(GridName_WMinus_LeptonEta, "cbars", "WMinus_LeptonEta");


}

int main(int argc, char** argv)
{
/* TString GridName_WPlus_LeptonPt = "/ustcfs2/yfu/MCFM_Dilution/WPlus_LeptonPt/grid-40-6-15-3-WPlus_WPlus_LeptonPt.root";
 TString GridName_WMinus_LeptonPt = "/ustcfs2/yfu/MCFM_Dilution/WMinus_LeptonPt/grid-40-6-15-3-WMinus_WMinus_LeptonPt.root";
 TString GridName_WPlus_Mass = "/ustcfs2/yfu/MCFM_Dilution/WPlus_Mass/grid-40-6-15-3-WPlus_WPlus_Mass.root";
 TString GridName_WMinus_Mass = "/ustcfs2/yfu/MCFM_Dilution/WMinus_Mass/grid-40-6-15-3-WMinus_WMinus_Mass.root";
 TString GridName_WPlus_WPt = "/ustcfs2/yfu/MCFM_Dilution/WPlus_WPt/grid-40-6-15-3-WPlus_WPlus_WPt.root";
 TString GridName_WMinus_WPt = "/ustcfs2/yfu/MCFM_Dilution/WMinus_WPt/grid-40-6-15-3-WMinus_WMinus_WPt.root";
*/

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->openFile("save.root");
 grid->SetLuminosity(30000000.0);

 grid->InitialPDF("CT18NNLO", 0);

/* grid->InitialGrid(GridName_WPlus_LeptonPt);
 grid->InitialGrid(GridName_WMinus_LeptonPt);
 grid->InitialGrid(GridName_WPlus_WPt);
 grid->InitialGrid(GridName_WMinus_WPt);
*/
 grid->InitialGrid(GridName_WPlus_LeptonEta);
 grid->InitialGrid(GridName_WMinus_LeptonEta);
 grid->InitialGrid(GridName_WPlus_NeutrinoEta);
 grid->InitialGrid(GridName_WMinus_NeutrinoEta);
 grid->InitialGrid(GridName_WPlus_WY);
 grid->InitialGrid(GridName_WMinus_WY);

 ApplConvolute(grid);

 grid->InitialPDF("CT18AsNNLO", 0);
 ApplConvolute(grid);

 grid->InitialPDF("MSHT20nnlo_as118", 0);
 ApplConvolute(grid);

// grid->InitialPDF("NNPDF40_nnlo_as_01180_hessian", 0);
// ApplConvolute(grid);

// grid->InitialPDF("CT18ANNLO", 0);
// ApplConvolute(grid);

// grid->InitialPDF("CT18ANNLO_moreX", 0);
// ApplConvolute(grid);

// grid->InitialPDF("CT18ANNLO_TieJiun", 0);
// ApplConvolute(grid);

 grid->SaveFile();

 return 1;
}

