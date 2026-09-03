#include "Calculation/ApplGridHelper.h"

int main(int argc, char** argv)
{
 TString GridName_WPlusZ_BoostPlus = "/msu/data/t3work5/yfu/MCFM_Dilution/DibosonBoost/WPlusZ_BoostPlus/grid-40-6-15-3-WPlusZ_BoostPlus.root";
 TString GridName_WPlusZ_BoostMinus = "/msu/data/t3work5/yfu/MCFM_Dilution/DibosonBoost/WPlusZ_BoostMinus/grid-40-6-15-3-WPlusZ_BoostMinus.root";
 TString GridName_WMinusZ_BoostPlus = "/msu/data/t3work5/yfu/MCFM_Dilution/DibosonBoost/WMinusZ_BoostPlus/grid-40-6-15-3-WMinusZ_BoostPlus.root";
 TString GridName_WMinusZ_BoostMinus = "/msu/data/t3work5/yfu/MCFM_Dilution/DibosonBoost/WMinusZ_BoostMinus/grid-40-6-15-3-WMinusZ_BoostMinus.root";

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->openFile("save.root");
 grid->SetLuminosity(30000000.0);

 grid->InitialPDF("CT18NNLO", 0);

 grid->InitialGrid(GridName_WPlusZ_BoostPlus);
 grid->InitialGrid(GridName_WPlusZ_BoostMinus);
 grid->InitialGrid(GridName_WMinusZ_BoostPlus);
 grid->InitialGrid(GridName_WMinusZ_BoostMinus);

 TH1D* WPlusZ_BoostAsym_CT18NNLO = grid->ConvoluteBoostAsym(GridName_WPlusZ_BoostPlus, GridName_WPlusZ_BoostMinus, "_WPlusZ");
 TH1D* WMinusZ_BoostAsym_CT18NNLO = grid->ConvoluteBoostAsym(GridName_WMinusZ_BoostPlus, GridName_WMinusZ_BoostMinus, "_WMinusZ");

 grid->InitialPDF("MSHT20nnlo_as118", 0);
 TH1D* WPlusZ_BoostAsym_MSHT20 = grid->ConvoluteBoostAsym(GridName_WPlusZ_BoostPlus, GridName_WPlusZ_BoostMinus, "_WPlusZ");
 TH1D* WMinusZ_BoostAsym_MSHT20 = grid->ConvoluteBoostAsym(GridName_WMinusZ_BoostPlus, GridName_WMinusZ_BoostMinus, "_WMinusZ");

 grid->InitialPDF("NNPDF40_nnlo_as_01180_hessian", 0);
 TH1D* WPlusZ_BoostAsym_NNPDF40 = grid->ConvoluteBoostAsym(GridName_WPlusZ_BoostPlus, GridName_WPlusZ_BoostMinus, "_WPlusZ");
 TH1D* WMinusZ_BoostAsym_NNPDF40 = grid->ConvoluteBoostAsym(GridName_WMinusZ_BoostPlus, GridName_WMinusZ_BoostMinus, "_WMinusZ");

 grid->SaveFile();

 return 1;
}
