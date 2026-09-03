#include "Calculation/ApplGridHelper.h"

int main(int argc, char** argv)
{
 TString GridNameYP1 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_0.0_1.0/grid-40-6-15-3-Z_y_0.0_1.0.root";
 TString GridNameYP2 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.0_1.25/grid-40-6-15-3-Z_y_1.0_1.25.root";
 TString GridNameYP3 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.25_1.5/grid-40-6-15-3-Z_y_1.25_1.5.root";
 TString GridNameYP4 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.5_2.4/grid-40-6-15-3-Z_y_1.5_2.4.root";

 TString GridNameYM1 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.0_0.0/grid-40-6-15-3-Z_y_-1.0_0.0.root";
 TString GridNameYM2 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.25_-1.0/grid-40-6-15-3-Z_y_-1.25_-1.0.root";
 TString GridNameYM3 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.5_-1.25/grid-40-6-15-3-Z_y_-1.5_-1.25.root";
 TString GridNameYM4 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-2.4_-1.5/grid-40-6-15-3-Z_y_-2.4_-1.5.root";

 TString GridNameD0 = "/msu/data/t3work5/yfu/MCFM_Dilution/ppbar/grid-40-6-15-3-Z_y_-5.0_5.0.root";

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->openFile("save.root");

 grid->InitialPDF("CT18NNLO", 0);

 grid->InitialGrid(GridNameYP1);
 grid->InitialGrid(GridNameYP2);
 grid->InitialGrid(GridNameYP3);
 grid->InitialGrid(GridNameYP4);
 grid->InitialGrid(GridNameYM1);
 grid->InitialGrid(GridNameYM2);
 grid->InitialGrid(GridNameYM3);
 grid->InitialGrid(GridNameYM4);

 TString uubar_wrong_subprocs = {""};


}
