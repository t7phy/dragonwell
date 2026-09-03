#include "Calculation/ApplGridHelper.h"

int main(int argc, char** argv)
{
 if(argc != 2 && argc != 3){
   cout<<"Please usage ./ApplConvolute GridName [Beam Type]"<<endl;
   return 0;
 }

// TString GridNameYP1 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_0.0_1.0/grid-40-6-15-3-Z_y_0.0_1.0.root";
// TString GridNameYP2 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.0_1.25/grid-40-6-15-3-Z_y_1.0_1.25.root";
// TString GridNameYP3 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.25_1.5/grid-40-6-15-3-Z_y_1.25_1.5.root";
// TString GridNameYP4 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_1.5_2.4/grid-40-6-15-3-Z_y_1.5_2.4.root";

// TString GridNameYM1 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.0_0.0/grid-40-6-15-3-Z_y_-1.0_0.0.root";
// TString GridNameYM2 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.25_-1.0/grid-40-6-15-3-Z_y_-1.25_-1.0.root";
// TString GridNameYM3 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-1.5_-1.25/grid-40-6-15-3-Z_y_-1.5_-1.25.root";
// TString GridNameYM4 = "/msu/data/t3work5/yfu/MCFM_Dilution/Z_only/y_-2.4_-1.5/grid-40-6-15-3-Z_y_-2.4_-1.5.root";

// TString GridNameD0 = "/msu/data/t3work5/yfu/MCFM_Dilution/ppbar/grid-40-6-15-3-Z_y_-5.0_5.0.root";

// TString GridName = "/msu/data/t3work5/yfu/MCFM_Dilution/WW/grid-40-6-15-3-WPlusZ_WPlusZ.root";

 TString GridName = argv[1];

 ApplGridHelper* grid;

 grid = new ApplGridHelper();
 grid->openFile("saveApplConvolute.root");

/* grid->ReadKFactor("CMS_dd_YM_right_Y1.kf");
 grid->ReadKFactor("CMS_dd_YM_right_Y2.kf");
 grid->ReadKFactor("CMS_dd_YM_right_Y3.kf");
 grid->ReadKFactor("CMS_dd_YM_right_Y4.kf");
 grid->ReadKFactor("CMS_dd_YM_wrong_Y1.kf");
 grid->ReadKFactor("CMS_dd_YM_wrong_Y2.kf");
 grid->ReadKFactor("CMS_dd_YM_wrong_Y3.kf");
 grid->ReadKFactor("CMS_dd_YM_wrong_Y4.kf");
 grid->ReadKFactor("CMS_dd_YP_right_Y1.kf");
 grid->ReadKFactor("CMS_dd_YP_right_Y2.kf");
 grid->ReadKFactor("CMS_dd_YP_right_Y3.kf");
 grid->ReadKFactor("CMS_dd_YP_right_Y4.kf");
 grid->ReadKFactor("CMS_dd_YP_wrong_Y1.kf");
 grid->ReadKFactor("CMS_dd_YP_wrong_Y2.kf");
 grid->ReadKFactor("CMS_dd_YP_wrong_Y3.kf");
 grid->ReadKFactor("CMS_dd_YP_wrong_Y4.kf");
 grid->ReadKFactor("CMS_total_YM_Y1.kf");
 grid->ReadKFactor("CMS_total_YM_Y2.kf");
 grid->ReadKFactor("CMS_total_YM_Y3.kf");
 grid->ReadKFactor("CMS_total_YM_Y4.kf");
 grid->ReadKFactor("CMS_total_YP_Y1.kf");
 grid->ReadKFactor("CMS_total_YP_Y2.kf");
 grid->ReadKFactor("CMS_total_YP_Y3.kf");
 grid->ReadKFactor("CMS_total_YP_Y4.kf");
 grid->ReadKFactor("CMS_uu_YM_right_Y1.kf");
 grid->ReadKFactor("CMS_uu_YM_right_Y2.kf");
 grid->ReadKFactor("CMS_uu_YM_right_Y3.kf");
 grid->ReadKFactor("CMS_uu_YM_right_Y4.kf");
 grid->ReadKFactor("CMS_uu_YM_wrong_Y1.kf");
 grid->ReadKFactor("CMS_uu_YM_wrong_Y2.kf");
 grid->ReadKFactor("CMS_uu_YM_wrong_Y3.kf");
 grid->ReadKFactor("CMS_uu_YM_wrong_Y4.kf");
 grid->ReadKFactor("CMS_uu_YP_right_Y1.kf");
 grid->ReadKFactor("CMS_uu_YP_right_Y2.kf");
 grid->ReadKFactor("CMS_uu_YP_right_Y3.kf");
 grid->ReadKFactor("CMS_uu_YP_right_Y4.kf");
 grid->ReadKFactor("CMS_uu_YP_wrong_Y1.kf");
 grid->ReadKFactor("CMS_uu_YP_wrong_Y2.kf");
 grid->ReadKFactor("CMS_uu_YP_wrong_Y3.kf");
 grid->ReadKFactor("CMS_uu_YP_wrong_Y4.kf");
 grid->ReadKFactor("D0_dd_right.kf");
 grid->ReadKFactor("D0_dd_wrong.kf");
 grid->ReadKFactor("D0_total.kf");
 grid->ReadKFactor("D0_uu_right.kf");
 grid->ReadKFactor("D0_uu_wrong.kf");

 vector<TString> KFactors_CMS_Y1 = {"CMS_uu_YP_right_Y1.kf", "CMS_uu_YM_right_Y1.kf", "CMS_uu_YM_wrong_Y1.kf", "CMS_uu_YP_wrong_Y1.kf",
                                    "CMS_dd_YP_right_Y1.kf", "CMS_dd_YM_right_Y1.kf", "CMS_dd_YM_wrong_Y1.kf", "CMS_dd_YP_wrong_Y1.kf",
                                    "CMS_total_YP_Y1.kf", "CMS_total_YM_Y1.kf"};

 vector<TString> KFactors_CMS_Y2 = {"CMS_uu_YP_right_Y2.kf", "CMS_uu_YM_right_Y2.kf", "CMS_uu_YM_wrong_Y2.kf", "CMS_uu_YP_wrong_Y2.kf",
                                    "CMS_dd_YP_right_Y2.kf", "CMS_dd_YM_right_Y2.kf", "CMS_dd_YM_wrong_Y2.kf", "CMS_dd_YP_wrong_Y2.kf",
                                    "CMS_total_YP_Y2.kf", "CMS_total_YM_Y2.kf"};

 vector<TString> KFactors_CMS_Y3 = {"CMS_uu_YP_right_Y3.kf", "CMS_uu_YM_right_Y3.kf", "CMS_uu_YM_wrong_Y3.kf", "CMS_uu_YP_wrong_Y3.kf",
                                    "CMS_dd_YP_right_Y3.kf", "CMS_dd_YM_right_Y3.kf", "CMS_dd_YM_wrong_Y3.kf", "CMS_dd_YP_wrong_Y3.kf",
                                    "CMS_total_YP_Y3.kf", "CMS_total_YM_Y3.kf"};

 vector<TString> KFactors_CMS_Y4 = {"CMS_uu_YP_right_Y4.kf", "CMS_uu_YM_right_Y4.kf", "CMS_uu_YM_wrong_Y4.kf", "CMS_uu_YP_wrong_Y4.kf",
                                    "CMS_dd_YP_right_Y4.kf", "CMS_dd_YM_right_Y4.kf", "CMS_dd_YM_wrong_Y4.kf", "CMS_dd_YP_wrong_Y4.kf",
                                    "CMS_total_YP_Y4.kf", "CMS_total_YM_Y4.kf"};

 vector<TString> KFactors_D0 = {"D0_uu_right.kf", "D0_uu_wrong.kf", "D0_dd_right.kf", "D0_dd_wrong.kf", "D0_total.kf"};
*/

 grid->InitialPDF("CT18NNLO", 0);
 //grid->InitialCTEQPDF("i2Tn3.00.pds");

 //vector<double> xsec;
 //grid->InitialGrid(GridName);
 //grid->DefaultConvoluteMacro(GridName, xsec);
 if(argc == 2) grid->DefaultConvolute(GridName);
 if(argc == 3){
   if(stoi(argv[2]) == 1) grid->DefaultConvolute(GridName);
   else if(stoi(argv[2]) == -1) grid->DefaultConvoluteppbar(GridName);
   else if(stoi(argv[2]) == 3) grid->DefaultConvolutepCu(GridName);
 }
 //grid->DefaultConvoluteppbar(GridNameD0YP);
 //grid->DefaultConvolute(GridNameD0YP);

 double P0u, P0d;
// grid->CalcP0ppbar(GridNameD0, "", P0u, P0d, KFactors_D0);

// grid->InitialPDF("MSHT20nnlo_as118", 0);
// grid->CalcP0ppbar(GridNameD0, "", P0u, P0d);

// grid->InitialPDF("NNPDF31_nnlo_as_0118", 0);
// grid->CalcP0ppbar(GridNameD0, "", P0u, P0d);

// grid->ConvoluteppbarSubProc(GridNameD0, 80);
// grid->ConvoluteppbarSubProc(GridNameD0, 82);
// grid->ConvoluteppbarSubProc(GridNameD0, 58);
// grid->Convoluteppbar(GridNameD0);
 
// grid->InitialGrid(GridNameYP1);
// grid->InitialGrid(GridNameYP2);
// grid->InitialGrid(GridNameYP3);
// grid->InitialGrid(GridNameYP4);
// grid->InitialGrid(GridNameYM1);
// grid->InitialGrid(GridNameYM2);
// grid->InitialGrid(GridNameYM3);
// grid->InitialGrid(GridNameYM4);

// grid->ConvoluteSubProc(GridNameYP4, 80);//uubar right
// grid->ConvoluteSubProc(GridNameYP4, 82);
// grid->ConvoluteSubProc(GridNameYP4, 58);
// grid->ConvoluteSubProc(GridNameYM4, 40);//ubaru right
// grid->ConvoluteSubProc(GridNameYM4, 38);
// grid->ConvoluteSubProc(GridNameYM4, 62);

// grid->ConvoluteSubProc(GridNameYM4, 80);//uubar wrong
// grid->ConvoluteSubProc(GridNameYM4, 82);
// grid->ConvoluteSubProc(GridNameYM4, 58);
// grid->ConvoluteSubProc(GridNameYP4, 40);//ubaru wrong
// grid->ConvoluteSubProc(GridNameYP4, 38);
// grid->ConvoluteSubProc(GridNameYP4, 62);

// grid->Convolute(GridNameYP4);
// grid->Convolute(GridNameYM4);

// grid->CalcP0(GridNameYP1, GridNameYM1, "_Y1", P0u, P0d, KFactors_CMS_Y1);
// grid->CalcP0(GridNameYP2, GridNameYM2, "_Y2", P0u, P0d, KFactors_CMS_Y2);
// grid->CalcP0(GridNameYP3, GridNameYM3, "_Y3", P0u, P0d, KFactors_CMS_Y3);
// grid->CalcP0(GridNameYP4, GridNameYM4, "_Y4", P0u, P0d, KFactors_CMS_Y4);

/* grid->InitialPDF("MSHT20nnlo_as118", 0);
 grid->CalcP0(GridNameYP1, GridNameYM1, "_Y1", P0u, P0d);
 grid->CalcP0(GridNameYP2, GridNameYM2, "_Y2", P0u, P0d);
 grid->CalcP0(GridNameYP3, GridNameYM3, "_Y3", P0u, P0d);
 grid->CalcP0(GridNameYP4, GridNameYM4, "_Y4", P0u, P0d);

 grid->InitialPDF("NNPDF31_nnlo_as_0118", 0);
 grid->CalcP0(GridNameYP1, GridNameYM1, "_Y1", P0u, P0d);
 grid->CalcP0(GridNameYP2, GridNameYM2, "_Y2", P0u, P0d);
 grid->CalcP0(GridNameYP3, GridNameYM3, "_Y3", P0u, P0d);
 grid->CalcP0(GridNameYP4, GridNameYM4, "_Y4", P0u, P0d);
*/
 grid->SaveFile();

 //grid->CalcP0PDFUnc(GridNameYP1, GridNameYM1, "_Y1", "CT18NNLO", 58);
 //grid->CalcP0PDFUnc(GridNameYP2, GridNameYM2, "_Y2", "CT18NNLO", 58);
 //grid->CalcP0PDFUnc(GridNameYP3, GridNameYM3, "_Y3", "CT18NNLO", 58);
 //grid->CalcP0PDFUnc(GridNameYP4, GridNameYM4, "_Y4", "CT18NNLO", 58);

/* vector<TH1D *> XSec_SubProc(121);
 TH1D* XSec;
 double SumOfSubProc = 0.0;

 XSec = grid->Convoluteppbar(GridNameD0YP);

 for(int i = 0; i < 121; i++){
   XSec_SubProc.at(i) = grid->ConvoluteppbarSubProc(GridNameD0YP, i);
   cout<<"SubProc: "<<i<<" "<<XSec_SubProc.at(i)->Integral()<<" "<<XSec_SubProc.at(i)->Integral() / XSec->Integral()<<endl;
   SumOfSubProc += XSec_SubProc.at(i)->Integral();
 }

 cout<<"Total: "<<XSec->Integral()<<endl;
 cout<<"SumOfSubProc: "<<SumOfSubProc<<endl;
*/

 return 1;
}
