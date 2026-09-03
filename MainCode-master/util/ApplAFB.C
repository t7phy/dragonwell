#include "Calculation/ApplGridHelper.h"

int main(int argc, char** argv)
{
 TString GridNameF_40_200 = "/ustcfs2/yfu/MCFM_Dilution/Forward_40_200/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_40_200 = "/ustcfs2/yfu/MCFM_Dilution/Backward_40_200/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_40_200 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYP_40_200/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_40_200 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYM_40_200/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_200_1000 = "/ustcfs2/yfu/MCFM_Dilution/Forward_200_1000/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_200_1000 = "/ustcfs2/yfu/MCFM_Dilution/Backward_200_1000/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_200_1000 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYP_200_1000/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_200_1000 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYM_200_1000/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_1000_3000 = "/ustcfs2/yfu/MCFM_Dilution/Forward_1000_3000/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_1000_3000 = "/ustcfs2/yfu/MCFM_Dilution/Backward_1000_3000/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_1000_3000 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYP_1000_3000/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_1000_3000 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYM_1000_3000/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_3000_5000 = "/ustcfs2/yfu/MCFM_Dilution/Forward_3000_5000/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_3000_5000 = "/ustcfs2/yfu/MCFM_Dilution/Backward_3000_5000/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_3000_5000 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYP_3000_5000/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_3000_5000 = "/ustcfs2/yfu/MCFM_Dilution/DilutionYM_3000_5000/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_500_5000 = "/ustcfs2/yfu/MCFM_Dilution/500_5000/Forward/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_500_5000 = "/ustcfs2/yfu/MCFM_Dilution/500_5000/Backward/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_500_5000 = "/ustcfs2/yfu/MCFM_Dilution/500_5000/DilutionYP/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_500_5000 = "/ustcfs2/yfu/MCFM_Dilution/500_5000/DilutionYM/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_500_1044 = "/ustcfs2/yfu/MCFM_Dilution/500_1044.65/Forward/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_500_1044 = "/ustcfs2/yfu/MCFM_Dilution/500_1044.65/Backward/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_500_1044 = "/ustcfs2/yfu/MCFM_Dilution/500_1044.65/DilutionYP/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_500_1044 = "/ustcfs2/yfu/MCFM_Dilution/500_1044.65/DilutionYM/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_1044_2624 = "/ustcfs2/yfu/MCFM_Dilution/1044.65_2624.04/Forward/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_1044_2624 = "/ustcfs2/yfu/MCFM_Dilution/1044.65_2624.04/Backward/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_1044_2624 = "/ustcfs2/yfu/MCFM_Dilution/1044.65_2624.04/DilutionYP/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_1044_2624 = "/ustcfs2/yfu/MCFM_Dilution/1044.65_2624.04/DilutionYM/grid-40-6-15-3-Z_DilutionYM.root";

 TString GridNameF_2624_5000 = "/ustcfs2/yfu/MCFM_Dilution/2624.04_5000/Forward/grid-40-6-15-3-Z_Forward.root";
 TString GridNameB_2624_5000 = "/ustcfs2/yfu/MCFM_Dilution/2624.04_5000/Backward/grid-40-6-15-3-Z_Backward.root";
 TString GridNameDilutionYP_2624_5000 = "/ustcfs2/yfu/MCFM_Dilution/2624.04_5000/DilutionYP/grid-40-6-15-3-Z_DilutionYP.root";
 TString GridNameDilutionYM_2624_5000 = "/ustcfs2/yfu/MCFM_Dilution/2624.04_5000/DilutionYM/grid-40-6-15-3-Z_DilutionYM.root";

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->openFile("save.root");
 grid->SetLuminosity(30000000.0);

 grid->InitialPDF("CT18NNLO", 0);

// grid->InitialGrid(GridNameF_40_200);
// grid->InitialGrid(GridNameB_40_200);
// grid->InitialGrid(GridNameDilutionYP_40_200);
// grid->InitialGrid(GridNameDilutionYM_40_200);

// grid->InitialGrid(GridNameF_200_1000);
// grid->InitialGrid(GridNameB_200_1000);
// grid->InitialGrid(GridNameDilutionYP_200_1000);
// grid->InitialGrid(GridNameDilutionYM_200_1000);

// grid->InitialGrid(GridNameF_1000_3000);
// grid->InitialGrid(GridNameB_1000_3000);
// grid->InitialGrid(GridNameDilutionYP_1000_3000);
// grid->InitialGrid(GridNameDilutionYM_1000_3000);

// grid->InitialGrid(GridNameF_3000_5000);
// grid->InitialGrid(GridNameB_3000_5000);
// grid->InitialGrid(GridNameDilutionYP_3000_5000);
// grid->InitialGrid(GridNameDilutionYM_3000_5000);

// grid->InitialGrid(GridNameF_500_5000);
// grid->InitialGrid(GridNameB_500_5000);
// grid->InitialGrid(GridNameDilutionYP_500_5000);
// grid->InitialGrid(GridNameDilutionYM_500_5000);

 grid->InitialGrid(GridNameF_500_1044);
 grid->InitialGrid(GridNameB_500_1044);
 grid->InitialGrid(GridNameDilutionYP_500_1044);
 grid->InitialGrid(GridNameDilutionYM_500_1044);

 grid->InitialGrid(GridNameF_1044_2624);
 grid->InitialGrid(GridNameB_1044_2624);
 grid->InitialGrid(GridNameDilutionYP_1044_2624);
 grid->InitialGrid(GridNameDilutionYM_1044_2624);

 grid->InitialGrid(GridNameF_2624_5000);
 grid->InitialGrid(GridNameB_2624_5000);
 grid->InitialGrid(GridNameDilutionYP_2624_5000);
 grid->InitialGrid(GridNameDilutionYM_2624_5000);

 //TH1D* AFB_40_200_CT18NNLO = grid->ConvoluteAFB(GridNameF_40_200, GridNameB_40_200, "_40_200");
 //TH1D* AFB_200_1000_CT18NNLO = grid->ConvoluteAFB(GridNameF_200_1000, GridNameB_200_1000, "_200_1000");
 //TH1D* AFB_1000_3000_CT18NNLO = grid->ConvoluteAFB(GridNameF_1000_3000, GridNameB_1000_3000, "_1000_3000");
 //TH1D* AFB_3000_5000_CT18NNLO = grid->ConvoluteAFB(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000");
 //TH1D* AFB_40_5000 = grid->AFBExtend(Forward, Backward, "", -1);
// vector<TString> Forward = {GridNameF_40_200, GridNameF_200_1000, GridNameF_1000_3000, GridNameF_3000_5000};
// vector<TString> Backward = {GridNameB_40_200, GridNameB_200_1000, GridNameB_1000_3000, GridNameB_3000_5000};
// vector<TString> subName = {"_40_200", "_200_1000", "_1000_3000", "_3000_5000"};

 vector<TString> Forward = {GridNameF_500_1044, GridNameF_1044_2624, GridNameF_2624_5000};
 vector<TString> Backward = {GridNameB_500_1044, GridNameB_1044_2624, GridNameB_2624_5000};
 vector<TString> subName = {"_500_1044", "_1044_2624", "_2624_5000"};
 vector<TString> YP = {GridNameDilutionYP_500_1044, GridNameDilutionYP_1044_2624, GridNameDilutionYP_2624_5000};
 vector<TString> YM = {GridNameDilutionYM_500_1044, GridNameDilutionYM_1044_2624, GridNameDilutionYM_2624_5000};

 grid->CalcAFBExtendPDFUnc(Forward, Backward, subName, -1, "Symmetry", "CT18NNLO", 58);
 grid->CalcAFBExtendPDFUnc(Forward, Backward, subName, 2, "Symmetry", "CT18NNLO", 58);
 grid->CalcAFBExtendPDFUnc(Forward, Backward, subName, 1, "Symmetry", "CT18NNLO", 58);
 grid->CalcDilutionExtendPDFUnc(YP, YM, subName, -1, "Symmetry", "CT18NNLO", 58);
 grid->CalcDilutionExtendPDFUnc(YP, YM, subName, 2, "Symmetry", "CT18NNLO", 58);
 grid->CalcDilutionExtendPDFUnc(YP, YM, subName, 1, "Symmetry", "CT18NNLO", 58);

 grid->InitialPDF("MSHT20nnlo_as118", 0);
 grid->CalcAFBExtendPDFUnc(Forward, Backward, subName, -1, "Symmetry68", "MSHT20nnlo_as118", 64);
 grid->CalcDilutionExtendPDFUnc(YP, YM, subName, -1, "Symmetry68", "MSHT20nnlo_as118", 64);

 grid->InitialPDF("NNPDF40_nnlo_as_01180", 0);
 grid->CalcAFBExtendPDFUnc(Forward, Backward, subName, -1, "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);
 grid->CalcDilutionExtendPDFUnc(YP, YM, subName, -1, "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);


/* vector<double> Lumi(100);
 for(int i = 0; i < Lumi.size(); i++){
   Lumi.at(i) = 3000000.0 + i * 3000000.0;
 }

 vector<TH1D *> AFB_vs_Lumi(Lumi.size());
 for(int i = 0; i < Lumi.size(); i++){
   grid->SetLuminosity(Lumi.at(i));
   //AFB_vs_Lumi.at(i) = grid->ConvoluteAFB(GridNameF_3000_5000, GridNameB_3000_5000, (TString)"_3000_5000_" + (int)Lumi.at(i));
   AFB_vs_Lumi.at(i) = grid->ConvoluteAFB(GridNameF_1000_3000, GridNameB_1000_3000, (TString)"_1000_3000_" + (int)Lumi.at(i));
 }

 vector<TH1D *> AFB_LumiDep(AFB_vs_Lumi.at(0)->GetNbinsX());
 for(int ibin = 0; ibin < AFB_LumiDep.size(); ibin++){
   AFB_LumiDep.at(ibin) = new TH1D((TString)"AFB_LumiDep_Bin_" + (int)(ibin + 1), (TString)"AFB_LumiDep_Bin_" + (int)(ibin + 1), 99, 1500, 301500);
   for(int ilumi = 0; ilumi < Lumi.size(); ilumi++){
     AFB_LumiDep.at(ibin)->SetBinContent(ilumi + 1, AFB_vs_Lumi.at(ilumi)->GetBinError(ibin + 1));
     AFB_LumiDep.at(ibin)->SetBinError(ilumi + 1, 0.0);
   }
 }
 TH1D* AFB_Constant = new TH1D("AFB_Constant", "AFB_Constant", 99, 1500, 301500);
 for(int ibin = 1; ibin <= AFB_Constant->GetNbinsX(); ibin++){
   AFB_Constant->SetBinContent(ibin, AFB_vs_Lumi.at(0)->GetBinContent(1));
   AFB_Constant->SetBinError(ibin, 0.0);
 }
*/

// grid->CalcAFBPDFUnc(GridNameF_40_200, GridNameB_40_200, "_40_200", "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_200_1000, GridNameB_200_1000, "_200_1000", "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_1000_3000, GridNameB_1000_3000, "_1000_3000", "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000", -1, "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000", 2, "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000", 1, "Symmetry", "CT18NNLO", 58);

// grid->CalcAFBPDFUnc(GridNameF_500_5000, GridNameB_500_5000, "_500_5000", -1, "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_500_5000, GridNameB_500_5000, "_500_5000", 2, "Symmetry", "CT18NNLO", 58);
// grid->CalcAFBPDFUnc(GridNameF_500_5000, GridNameB_500_5000, "_500_5000", 1, "Symmetry", "CT18NNLO", 58);

// grid->CalcDilutionPDFUnc(GridNameDilutionYP_40_200, GridNameDilutionYM_40_200, "_40_200", "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_200_1000, GridNameDilutionYM_200_1000, "_200_1000", "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_1000_3000, GridNameDilutionYM_1000_3000, "_1000_3000", "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_3000_5000, GridNameDilutionYM_3000_5000, "_3000_5000", -1, "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_3000_5000, GridNameDilutionYM_3000_5000, "_3000_5000", 2, "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_3000_5000, GridNameDilutionYM_3000_5000, "_3000_5000", 1, "Symmetry", "CT18NNLO", 58);

// grid->CalcDilutionPDFUnc(GridNameDilutionYP_500_5000, GridNameDilutionYM_500_5000, "_500_5000", -1, "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_500_5000, GridNameDilutionYM_500_5000, "_500_5000", 2, "Symmetry", "CT18NNLO", 58);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_500_5000, GridNameDilutionYM_500_5000, "_500_5000", 1, "Symmetry", "CT18NNLO", 58);

// grid->InitialPDF("MSHT20nnlo_as118", 0);
 //TH1D* AFB_40_200_MSHT20 = grid->ConvoluteAFB(GridNameF_40_200, GridNameB_40_200, "_40_200");
 //TH1D* AFB_200_1000_MSHT20 = grid->ConvoluteAFB(GridNameF_200_1000, GridNameB_200_1000, "_200_1000");
 //TH1D* AFB_1000_3000_MSHT20 = grid->ConvoluteAFB(GridNameF_1000_3000, GridNameB_1000_3000, "_1000_3000");
 //TH1D* AFB_3000_5000_MSHT20 = grid->ConvoluteAFB(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000");

// grid->CalcAFBPDFUnc(GridNameF_40_200, GridNameB_40_200, "_40_200", "Symmetry68", "MSHT20nnlo_as118", 64);
// grid->CalcAFBPDFUnc(GridNameF_200_1000, GridNameB_200_1000, "_200_1000", "Symmetry68", "MSHT20nnlo_as118", 64);
// grid->CalcAFBPDFUnc(GridNameF_1000_3000, GridNameB_1000_3000, "_1000_3000", "Symmetry68", "MSHT20nnlo_as118", 64);
// grid->CalcAFBPDFUnc(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000", -1, "Symmetry68", "MSHT20nnlo_as118", 64);

// grid->CalcAFBPDFUnc(GridNameF_500_5000, GridNameB_500_5000, "_500_5000", -1, "Symmetry68", "MSHT20nnlo_as118", 64);

// grid->CalcDilutionPDFUnc(GridNameDilutionYP_40_200, GridNameDilutionYM_40_200, "_40_200", "Symmetry68", "MSHT20nnlo_as118", 64);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_200_1000, GridNameDilutionYM_200_1000, "_200_1000", "Symmetry68", "MSHT20nnlo_as118", 64);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_1000_3000, GridNameDilutionYM_1000_3000, "_1000_3000", "Symmetry68", "MSHT20nnlo_as118", 64);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_3000_5000, GridNameDilutionYM_3000_5000, "_3000_5000", -1, "Symmetry68", "MSHT20nnlo_as118", 64);

// grid->CalcDilutionPDFUnc(GridNameDilutionYP_500_5000, GridNameDilutionYM_500_5000, "_500_5000", -1, "Symmetry68", "MSHT20nnlo_as118", 64);


// grid->InitialPDF("NNPDF40_nnlo_as_01180", 0);
 //TH1D* AFB_40_200_NNPDF40 = grid->ConvoluteAFB(GridNameF_40_200, GridNameB_40_200, "_40_200");
 //TH1D* AFB_200_1000_NNPDF40 = grid->ConvoluteAFB(GridNameF_200_1000, GridNameB_200_1000, "_200_1000");
 //TH1D* AFB_1000_3000_NNPDF40 = grid->ConvoluteAFB(GridNameF_1000_3000, GridNameB_1000_3000, "_1000_3000");
 //TH1D* AFB_3000_5000_NNPDF40 = grid->ConvoluteAFB(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000");

// grid->CalcAFBPDFUnc(GridNameF_40_200, GridNameB_40_200, "_40_200", "Symmetry68", "NNPDF40_nnlo_as_01180_hessian", 50);
// grid->CalcAFBPDFUnc(GridNameF_200_1000, GridNameB_200_1000, "_200_1000", "Symmetry68", "NNPDF40_nnlo_as_01180_hessian", 50);
// grid->CalcAFBPDFUnc(GridNameF_1000_3000, GridNameB_1000_3000, "_1000_3000", "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);
// grid->CalcAFBPDFUnc(GridNameF_3000_5000, GridNameB_3000_5000, "_3000_5000", -1, "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);

// grid->CalcAFBPDFUnc(GridNameF_500_5000, GridNameB_500_5000, "_500_5000", -1, "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);

// grid->CalcDilutionPDFUnc(GridNameDilutionYP_40_200, GridNameDilutionYM_40_200, "_40_200", "Symmetry68", "NNPDF40_nnlo_as_01180_hessian", 50);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_200_1000, GridNameDilutionYM_200_1000, "_200_1000", "Symmetry68", "NNPDF40_nnlo_as_01180_hessian", 50);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_1000_3000, GridNameDilutionYM_1000_3000, "_1000_3000", "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);
// grid->CalcDilutionPDFUnc(GridNameDilutionYP_3000_5000, GridNameDilutionYM_3000_5000, "_3000_5000", -1, "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);

// grid->CalcDilutionPDFUnc(GridNameDilutionYP_500_5000, GridNameDilutionYM_500_5000, "_500_5000", -1, "MonteCarlo", "NNPDF40_nnlo_as_01180", 100);


 grid->SaveFile();

 return 1;
}
