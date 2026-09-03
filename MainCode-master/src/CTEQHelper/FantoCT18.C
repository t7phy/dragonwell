#include "CTEQHelper/PDFEvolve.h"

void PDFEvolve::InitializeFantoCT18(vector<TString> FlavorList, vector<int> FlagList)
{
 int Mellinxf = 0;
 int Mellinf = -1;

 if(!doReadSteer){
   readfantosteer_();
   doReadSteer = true;
 }

 map<TString, int> FlavorNameMap;
 for(int i = 0; i < FlavorList.size(); i++){
   FlavorNameMap[FlavorList.at(i)] = FlagList.at(i);
 }

 ifl_dv = FlavorNameMap.at("dv");
 ifl_uv = FlavorNameMap.at("uv");
 ifl_gluon = FlavorNameMap.at("gluon");
 ifl_ubar = FlavorNameMap.at("ubar");
 ifl_dbar = FlavorNameMap.at("dbar");
 ifl_str = FlavorNameMap.at("str");

 vector<double> Delta_dv;
 vector<double> Delta_uv;
 vector<double> Delta_gluon;
 vector<double> Delta_dmu;
 vector<double> Delta_dpu;
 vector<double> Delta_str;

 map<TString, vector<double>> FantoParameter;
 for(int ifl = 0; ifl < FlavorList.size(); ifl++){
   int NPar = Parameter.at(FlavorList.at(ifl)).size();
   FantoParameter[FlavorList.at(ifl)].resize(NPar + 1);
   FantoParameter.at(FlavorList.at(ifl)).at(0) = 1.0; // Normalization
   FantoParameter.at(FlavorList.at(ifl)).at(1) = Parameter.at(FlavorList.at(ifl)).at(0);// a1
   FantoParameter.at(FlavorList.at(ifl)).at(2) = Parameter.at(FlavorList.at(ifl)).at(1);// a2

   int Nm = getnm_(FlavorNameMap.at(FlavorList.at(ifl)));
   // FantoParameter.at(FlavorList.at(ifl)).at(3) is fixed parameter
   for(int i = 1; i <= Nm - 1; i++){
     FantoParameter.at(FlavorList.at(ifl)).at(i + 3) = Parameter.at(FlavorList.at(ifl)).at(i + 1);
   }
 }

 updatefantopars_(ifl_uv, &(FantoParameter.at("uv"))[0]);
 updatefantopars_(ifl_dv, &(FantoParameter.at("dv"))[0]);
 updatefantopars_(ifl_gluon, &(FantoParameter.at("gluon"))[0]);
 updatefantopars_(ifl_ubar, &(FantoParameter.at("ubar"))[0]);
 updatefantopars_(ifl_dbar, &(FantoParameter.at("dbar"))[0]);
 updatefantopars_(ifl_str, &(FantoParameter.at("str"))[0]);

 // Normalization
 //NormalizationFantoCT18();

 double RemM = 1.0;

 double uvInt = fantomellinmoment_(ifl_uv, Mellinf);
 uvNorm = 2.0 / uvInt;
 //cout<<uvInt<<"  "<<uvNorm<<endl;
 FantoParameter.at("uv")[0] = uvNorm;
 updatefantopars_(ifl_uv, &(FantoParameter.at("uv"))[0]);

 double dvInt = fantomellinmoment_(ifl_dv, Mellinf);
 dvNorm = 1.0 / dvInt;
 //cout<<dvInt<<"  "<<dvNorm<<endl;
 FantoParameter.at("dv")[0] = dvNorm;
 updatefantopars_(ifl_dv, &(FantoParameter.at("dv"))[0]);

 double uvxInt = fantomellinmoment_(ifl_uv, Mellinxf);
 double dvxInt = fantomellinmoment_(ifl_dv, Mellinxf);
 double uvMomentum = uvxInt;
 double dvMomentum = dvxInt;

 RemM = RemM - uvMomentum - dvMomentum;

 double gluonxInt = fantomellinmoment_(ifl_gluon, Mellinxf);
 gluonNorm = gluonMomentum / gluonxInt;
 FantoParameter.at("gluon")[0] = gluonNorm;
 updatefantopars_(ifl_gluon, &(FantoParameter.at("gluon"))[0]);

 RemM = RemM - gluonMomentum;

 double StrangeMomentum = RemM / 3.0 * StrangeB0;
 double sxInt = fantomellinmoment_(ifl_str, Mellinxf);
 sNorm = StrangeMomentum / sxInt; //!
 //cout<<RemM<<endl;
 //cout<<"sxInt = "<<sxInt<<"  sNorm = "<<sNorm<<endl;
 FantoParameter.at("str")[0] = sNorm;
 updatefantopars_(ifl_str, &(FantoParameter.at("str"))[0]);

 RemM = RemM - StrangeMomentum;

 double LastSeaMomentum = RemM; // ubar+dbar
 double LastSeaxInt = fantomellinmoment_(ifl_ubar, Mellinxf) + fantomellinmoment_(ifl_dbar, Mellinxf);
 dpuNorm = LastSeaMomentum / LastSeaxInt;
 FantoParameter.at("ubar")[0] = dpuNorm / 2.0; // the factor of 2.0 comes from the antiquark and sea quark contribution
 FantoParameter.at("dbar")[0] = dpuNorm / 2.0;
 updatefantopars_(ifl_ubar, &(FantoParameter.at("ubar"))[0]);
 updatefantopars_(ifl_dbar, &(FantoParameter.at("dbar"))[0]);

 MomentumList.clear();
 B0List.clear();

 double dbarMomentum = fantomellinmoment_(ifl_dbar, Mellinxf);
 double ubarMomentum = fantomellinmoment_(ifl_ubar, Mellinxf);

 MomentumList.push_back(dvMomentum);
 MomentumList.push_back(uvMomentum);
 MomentumList.push_back(gluonMomentum);
 MomentumList.push_back(dbarMomentum);
 MomentumList.push_back(ubarMomentum);
 MomentumList.push_back(StrangeMomentum);

 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(StrangeB0);

 // Prepare for PDFs in Q0
 Q0_gluon = [&](double x) {
   return fantopara_(ifl_gluon, x) / x;
 };
 Q0_uv = [&](double x) {
   return fantopara_(ifl_uv, x) / x;
 };
 Q0_dv = [&](double x) {
   return fantopara_(ifl_dv, x) / x;
 };
 Q0_ubar = [&](double x) {
   return fantopara_(ifl_ubar, x) / x;
 };
 Q0_dbar = [&](double x) {
   return fantopara_(ifl_dbar, x) / x;
 };
 Q0_u = [&](double x) {
   return Q0_uv(x) + Q0_ubar(x);
 };
 Q0_d = [&](double x) {
   return Q0_dv(x) + Q0_dbar(x);
 };
 Q0_s = [&](double x) {
   double splussbar = fantopara_(ifl_str, x) / x;
   double sminussbar_tem = 0.0;
   double sminussbar = splussbar * atan(sminussbar_tem) / atan(1.0) / 2.0;
   return (splussbar + sminussbar) / 2.0;
 };
 Q0_sbar = [&](double x) {
   double splussbar = fantopara_(ifl_str, x) / x;
   double sminussbar_tem = 0.0;
   double sminussbar = splussbar * atan(sminussbar_tem) / atan(1.0) / 2.0;
   return (splussbar - sminussbar) / 2.0;
 };


/* double x = 0.001;
 cout<<"x = 0.001 gluon = "<<fantopara_(ifl_gluon, x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 gluon = "<<fantopara_(ifl_gluon, x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 gluon = "<<fantopara_(ifl_gluon, x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 gluon = "<<fantopara_(ifl_gluon, x)<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 uv = "<<fantopara_(ifl_uv, x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 uv = "<<fantopara_(ifl_uv, x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 uv = "<<fantopara_(ifl_uv, x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 uv = "<<fantopara_(ifl_uv, x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 uv = "<<fantopara_(ifl_uv, x)<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 dv = "<<fantopara_(ifl_dv, x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 dv = "<<fantopara_(ifl_dv, x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 dv = "<<fantopara_(ifl_dv, x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 dv = "<<fantopara_(ifl_dv, x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 dv = "<<fantopara_(ifl_dv, x)<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 str = "<<fantopara_(ifl_str, x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 str = "<<fantopara_(ifl_str, x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 str = "<<fantopara_(ifl_str, x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 str = "<<fantopara_(ifl_str, x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 str = "<<fantopara_(ifl_str, x)<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 ubar = "<<fantopara_(ifl_ubar, x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 ubar = "<<fantopara_(ifl_ubar, x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 ubar = "<<fantopara_(ifl_ubar, x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 ubar = "<<fantopara_(ifl_ubar, x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 ubar = "<<fantopara_(ifl_ubar, x)<<endl;

 x = 1e-9;
 cout<<"x = 1e-9 dbar = "<<fantopara_(ifl_dbar, x)<<endl;
 x = 0.001;
 cout<<"x = 0.001 dbar = "<<fantopara_(ifl_dbar, x)<<endl;
 x = 0.01;
 cout<<"x = 0.01 dbar = "<<fantopara_(ifl_dbar, x)<<endl;
 x = 0.1;
 cout<<"x = 0.1 dbar = "<<fantopara_(ifl_dbar, x)<<endl;
 x = 0.4;
 cout<<"x = 0.4 dbar = "<<fantopara_(ifl_dbar, x)<<endl;
*/
}

void PDFEvolve::NormalizationFantoCT18()
{

}

void PDFEvolve::OutputFantoCT18()
{
 writefantoout_();
}
