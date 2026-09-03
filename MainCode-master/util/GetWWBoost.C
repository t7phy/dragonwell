#include "PDFHelper/WWProduction.h"

int main(int argc, char** argv)
{
 WWProduction* data = new WWProduction();

 data->openFile("WWBoost.root");
 data->InitialPDF("CT18NNLO", 0);
 data->InputPDFnSet(56);

 data->DrawWWMass(20, 160, 400, 0, "Integral");
// data->DrawWWMass(10, 0, 300, 2, "");

// cout<<data->WWHadronCrossSectionY0Q(-5, 1, 40)<<endl;

// data->DrawWWQuarkMass(40, 150, 410, 1, "");
// data->DrawWWQuarkMass(40, 150, 410, 2, "");

// data->WWCrossSection(1, 130, 1.0);
// data->WWCrossSection(1, 130, 2.0);
// data->WWCrossSection(2, 130, 10.0);

/* data->DrawBoostAsymmetry(6, 0, 3, 0, "Integral");
 data->DrawBoostAsymmetry(6, 0, 3, 1, "Integral");
 data->DrawBoostAsymmetry(6, 0, 3, 2, "Integral");
 data->DrawBoostAsymmetry(6, 0, 3, 3, "Integral");
 data->DrawBoostAsymmetry(6, 0, 3, 4, "Integral");
 data->DrawBoostAsymmetry(6, 0, 3, 5, "Integral");
*/

/* cout<<data->WWCrossSection(1, 200, 3.0) * 1e6<<endl;
 cout<<data->WWCrossSection(1, 200, -3.0) * 1e6<<endl;
 cout<<data->WWCrossSection(-1, 200, 3.0) * 1e6<<endl;
 cout<<data->WWCrossSection(-1, 200, -3.0) * 1e6<<endl;
 cout<<data->GetF1F2YInput(1, 3.0, 200)<<endl;
 cout<<data->GetF1F2YInput(1, -3.0, 200)<<endl;
 cout<<data->GetF1F2YInput(-1, 3.0, 200)<<endl;
 cout<<data->GetF1F2YInput(-1, -3.0, 200)<<endl;
*/
 cout<<"uubar 1.0: "<<data->BoostCrossSectionTerm1(200, 1.0, 1, "")<<endl;
 cout<<"uubar 1.0: "<<data->BoostCrossSectionTerm2(200, 1.0, 1, "")<<endl;
 cout<<"uubar 1.0: "<<data->BoostCrossSectionTerm3(200, 1.0, 1, "")<<endl;
 cout<<"uubar 1.0: "<<data->BoostCrossSectionTerm4(200, 1.0, 1, "")<<endl;
 cout<<"ubaru 1.0: "<<data->BoostCrossSectionTerm1(200, 1.0, -1, "")<<endl;
 cout<<"ubaru 1.0: "<<data->BoostCrossSectionTerm2(200, 1.0, -1, "")<<endl;
 cout<<"ubaru 1.0: "<<data->BoostCrossSectionTerm3(200, 1.0, -1, "")<<endl;
 cout<<"ubaru 1.0: "<<data->BoostCrossSectionTerm4(200, 1.0, -1, "")<<endl;
 cout<<"uubar -1.0: "<<data->BoostCrossSectionTerm1(200, -1.0, 1, "")<<endl;
 cout<<"uubar -1.0: "<<data->BoostCrossSectionTerm2(200, -1.0, 1, "")<<endl;
 cout<<"uubar -1.0: "<<data->BoostCrossSectionTerm3(200, -1.0, 1, "")<<endl;
 cout<<"uubar -1.0: "<<data->BoostCrossSectionTerm4(200, -1.0, 1, "")<<endl;
 cout<<"ubaru -1.0: "<<data->BoostCrossSectionTerm1(200, -1.0, -1, "")<<endl;
 cout<<"ubaru -1.0: "<<data->BoostCrossSectionTerm2(200, -1.0, -1, "")<<endl;
 cout<<"ubaru -1.0: "<<data->BoostCrossSectionTerm3(200, -1.0, -1, "")<<endl;
 cout<<"ubaru -1.0: "<<data->BoostCrossSectionTerm4(200, -1.0, -1, "")<<endl;

 cout<<"ssbar 1.0: "<<data->BoostCrossSectionTerm1(200, 1.0, 3, "")<<endl;
 cout<<"ssbar 1.0: "<<data->BoostCrossSectionTerm2(200, 1.0, 3, "")<<endl;
 cout<<"ssbar 1.0: "<<data->BoostCrossSectionTerm3(200, 1.0, 3, "")<<endl;
 cout<<"ssbar 1.0: "<<data->BoostCrossSectionTerm4(200, 1.0, 3, "")<<endl;
 cout<<"sbars 1.0: "<<data->BoostCrossSectionTerm1(200, 1.0, -3, "")<<endl;
 cout<<"sbars 1.0: "<<data->BoostCrossSectionTerm2(200, 1.0, -3, "")<<endl;
 cout<<"sbars 1.0: "<<data->BoostCrossSectionTerm3(200, 1.0, -3, "")<<endl;
 cout<<"sbars 1.0: "<<data->BoostCrossSectionTerm4(200, 1.0, -3, "")<<endl;
 cout<<"ssbar -1.0: "<<data->BoostCrossSectionTerm1(200, -1.0, 3, "")<<endl;
 cout<<"ssbar -1.0: "<<data->BoostCrossSectionTerm2(200, -1.0, 3, "")<<endl;
 cout<<"ssbar -1.0: "<<data->BoostCrossSectionTerm3(200, -1.0, 3, "")<<endl;
 cout<<"ssbar -1.0: "<<data->BoostCrossSectionTerm4(200, -1.0, 3, "")<<endl;
 cout<<"sbars -1.0: "<<data->BoostCrossSectionTerm1(200, -1.0, -3, "")<<endl;
 cout<<"sbars -1.0: "<<data->BoostCrossSectionTerm2(200, -1.0, -3, "")<<endl;
 cout<<"sbars -1.0: "<<data->BoostCrossSectionTerm3(200, -1.0, -3, "")<<endl;
 cout<<"sbars -1.0: "<<data->BoostCrossSectionTerm4(200, -1.0, -3, "")<<endl;


/* double WPlus_uu = data->TotalBoostCrossSection(3.0, 2) + data->TotalBoostCrossSection(3.0, -2);
 double WMinus_uu = data->TotalBoostCrossSection(-3.0, 2) + data->TotalBoostCrossSection(-3.0, -2);
 double WPlus_dd = data->TotalBoostCrossSection(3.0, 1) + data->TotalBoostCrossSection(3.0, -1);
 double WMinus_dd = data->TotalBoostCrossSection(-3.0, 1) + data->TotalBoostCrossSection(-3.0, -1);
 double WPlus_ss = data->TotalBoostCrossSection(3.0, 3) + data->TotalBoostCrossSection(3.0, -3);
 double WMinus_ss = data->TotalBoostCrossSection(-3.0, 3) + data->TotalBoostCrossSection(-3.0, -3);

 cout<<WPlus_uu<<" "<<WMinus_uu<<" "<<(WPlus_uu - WMinus_uu) / (WPlus_uu + WMinus_uu)<<endl;
 cout<<WPlus_dd<<" "<<WMinus_dd<<" "<<(WPlus_dd - WMinus_dd) / (WPlus_dd + WMinus_dd)<<endl;
 cout<<WPlus_ss<<" "<<WMinus_ss<<" "<<(WPlus_ss - WMinus_ss) / (WPlus_ss + WMinus_ss)<<endl;
*/


 data->SaveFile();

 return 1;
}
