#include "RootCommon.h"
#include "ElectroweakTheory/ZWidthDep.h"

Double_t myFunc(double* x, double* par)
{
   Float_t xx =x[0];
   Double_t f = TMath::Abs(par[0]*sin(par[1]*xx)/xx);
   return f;
}

int main(int argc, char** argv)
{
 ZWidthDep *run = new ZWidthDep();

 run->openFile("ZWidthDep.root");
// run->DrawReChiMassDerive(70, 60, 130, 0.1);
// run->DrawChiSquareMassDerive(70, 60, 130, 0.1);

 run->InputStw(0.2315);
 run->DrawAFB(280, 20, 300);
 run->DrawAFB(280, 20, 300, "ZU");
 run->DrawAFB(280, 20, 300, "ZD");
 run->DrawAFB(280, 20, 300, "ZU_Z");
 run->DrawAFB(280, 20, 300, "ZD_Z");
 run->DrawAFB(280, 20, 300, "ZU_ZGamma");
 run->DrawAFB(280, 20, 300, "ZD_ZGamma");

 run->DrawAFBStwDeriveMassDep(280, 20, 300, "ZU");
 run->DrawAFBStwDeriveMassDep(280, 20, 300, "ZD");

 run->DrawAFBStw(120, 0.2255, 0.2372, 91.0, "ZU");
 run->DrawAFBStw(120, 0.2255, 0.2372, 91.0, "ZD");

/* for(int i = 0; i < 70; i++){
   double mass = 60 + i;
   cout<<"Mass: "<<mass<<" Chi2: "<<run->ChiSquare(mass)<<endl;
 }

 for(int i = 0; i < 70; i++){
   double mass = 60 + i;
   cout<<"Mass: "<<mass<<" ReChi: "<<run->ReChi(mass)<<endl;
 }

 cout<<endl;
 cout<<"91.1876: Chi2: "<<run->ChiSquare(91.1876)<<endl;
 cout<<"91.1876: ReChi: "<<run->ReChi(91.1876)<<endl;
*/

 cout<<"alpha em: "<<run->pyalem(90.0 * 90.0)<<endl;

/* run->DrawAFB(700000, 60, 130);
 run->DrawDeltaO(700000, 0, 30);
 run->InputStw(0.2324);
 run->DrawAFB(700000, 60, 130);
 run->DrawDeltaO(700000, 0, 30);
 run->InputStw(0.2345);
 run->DrawAFB(700000, 60, 130);
 run->DrawDeltaO(700000, 0, 30);
*/

/* TFile* writefile = new TFile("ZWidthDep.root", "RECREATE");
 writefile->cd();

 TF1* AFB_1 = new TF1("AFBCurve_1", myFunc, 60, 130);
 AFB_1->SetParameters(2, 1);
 AFB_1->Draw();

 TGraph* AFBCurve_1 = new TGraph();
 AFBCurve_1->SetName("AFBCurve_1");
 AFBCurve_1->Apply(AFB_1);
 AFBCurve_1->Fit(AFB_1, 60, 130);
 AFBCurve_1->Write();

 writefile->Write();
 writefile->Close();
*/
// run->DrawAFBMassDerive(70, 60, 130, 0.1);

// for(int i = 0; i <= 70; i++){
//   double mass = 60 + i;
//   run->DrawAFBStwDerive(40, 0.2255, 0.2372, 0.00001, mass);
//   run->DrawReChiStwDerive(40, 0.2255, 0.2372, 0.00001, mass);
//   run->DrawChiSquareStwDerive(40, 0.2255, 0.2372, 0.00001, mass);
// }

/* run->DrawReChiStwDeriveMassDep(70, 60, 130);
 run->DrawChiSquareStwDeriveMassDep(70, 60, 130);

 run->DrawA41MassDerive(70, 60, 130, 0.1);
 run->DrawA41StwDeriveMassDep(70, 60, 130);
 run->DrawA42MassDerive(70, 60, 130, 0.1);
 run->DrawA42StwDeriveMassDep(70, 60, 130);

 run->DrawAFBStwDeriveMassDep(70, 60, 130);

 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.0);
 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.05);
 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.1);
 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.15);
 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.2);
 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.2315);
 run->DrawAFBMassStwDeriveMassDep(70, 60, 130, 0.25);


 run->DrawA4(7, 60, 130);
*/ 
 run->DrawL0(140, 60, 130);

 run->SaveFile();

 return 1;
}
