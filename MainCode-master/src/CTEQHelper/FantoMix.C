#include "CTEQHelper/PDFEvolve.h"

void PDFEvolve::InitializeFantoMix(vector<TString> FlavorList, vector<int> FlagList)
{
 int Mellinxf = 0;
 int Mellinf = -1;

 if(!doReadSteer){
   readfantosteer_();
   doReadSteer = true;
 }

 for(int i = 0; i < FlavorList.size(); i++){
   TString flavor = FlavorList.at(i);
   int flag = FlagList.at(i);

   if(flavor == "gluon"){
     if(fun_gluon) delete fun_gluon;
     fun_gluon = new gfuns(flag);
     fun_gluon->SetParameter(Parameter[flavor]);
   }

   if(flavor == "uv"){
     if(fun_uv) delete fun_uv;
     fun_uv = new gfuns(flag);
     fun_uv->SetParameter(Parameter[flavor]);
   }

   if(flavor == "dv"){
     if(fun_dv) delete fun_dv;
     fun_dv = new gfuns(flag);
     fun_dv->SetParameter(Parameter[flavor]);
   }

   if(flavor == "dpu"){
     if(fun_dpu) delete fun_dpu;
     fun_dpu = new gfuns(flag);
     fun_dpu->SetParameter(Parameter[flavor]);
   }

   if(flavor == "dmu"){
     if(fun_dmu) delete fun_dmu;
     fun_dmu = new gfuns(flag);
     fun_dmu->SetParameter(Parameter[flavor]);
   }
 }

 map<TString, int> FlavorNameMap;
 for(int i = 0; i < FlavorList.size(); i++){
   FlavorNameMap[FlavorList.at(i)] = FlagList.at(i);
 }

 ifl_str = FlavorNameMap.at("str");

 vector<double> Delta_str;

 map<TString, vector<double>> FantoParameter;
 for(int ifl = 0; ifl < FlavorList.size(); ifl++){
   if(FlavorList.at(ifl) != "str") continue;

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

 updatefantopars_(ifl_str, &(FantoParameter.at("str"))[0]);

 // Normalization

 double RemM = 1.0;

 double uvInt = NumberIntegral("uv");
 double dvInt = NumberIntegral("dv");
 uvNorm = 2.0 / uvInt; //!
 dvNorm = 1.0 / dvInt; //!
 double uvxInt = MomentumIntegral("uv");
 double dvxInt = MomentumIntegral("dv");
 double uvMomentum = uvNorm * uvxInt;
 double dvMomentum = dvNorm * dvxInt;
 RemM = RemM - uvMomentum - dvMomentum;

 double gluonxInt = MomentumIntegral("gluon");
 gluonNorm = gluonMomentum / gluonxInt; //!
 RemM = RemM - gluonMomentum;

 double StrangeMomentum = RemM / 3.0 * StrangeB0;
 double sxInt = fantomellinmoment_(ifl_str, Mellinxf);
 sNorm = StrangeMomentum / sxInt; //!
 //cout<<RemM<<endl;
 //cout<<"sxInt = "<<sxInt<<"  sNorm = "<<sNorm<<endl;
 FantoParameter.at("str")[0] = sNorm;
 updatefantopars_(ifl_str, &(FantoParameter.at("str"))[0]);

 RemM = RemM - StrangeMomentum;

 double LastSeaMomentum = RemM; //ubar+dbar
 double LastSeaxInt = MomentumIntegral("dpu");
 dpuNorm = LastSeaMomentum / LastSeaxInt;
 dmuNorm = 1.0;

 MomentumList.clear();
 B0List.clear();

 MomentumList.push_back(dvMomentum);
 MomentumList.push_back(uvMomentum);
 MomentumList.push_back(gluonMomentum);
 MomentumList.push_back(0.0);//dmu
 MomentumList.push_back(LastSeaMomentum);
 MomentumList.push_back(StrangeMomentum);

 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(0.0);
 B0List.push_back(StrangeB0);

 // Prepare for PDFs in Q0
 Q0_gluon = [&](double x) {
   return gluonNorm * fun_gluon->fcn(x);
 };
 Q0_uv = [&](double x) {
   return uvNorm * fun_uv->fcn(x);
 };
 Q0_dv = [&](double x) {
   return dvNorm * fun_dv->fcn(x);
 };
 Q0_ubar = [&](double x) {
   double dpu_tem = dpuNorm * fun_dpu->fcn(x);
   double dmu_tem = dmuNorm * fun_dmu->fcn(x);
   double dpu = dpu_tem / 2.0;
   double dmu = dpu * atan(dmu_tem) / (2.0 * atan(1.0));
   return (dpu - dmu) / 2.0;
 };
 Q0_dbar = [&](double x) {
   double dpu_tem = dpuNorm * fun_dpu->fcn(x);
   double dmu_tem = dmuNorm * fun_dmu->fcn(x);
   double dpu = dpu_tem / 2.0;
   double dmu = dpu * atan(dmu_tem) / (2.0 * atan(1.0));
   return (dpu + dmu) / 2.0;
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

}

