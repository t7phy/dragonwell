#include "CTEQHelper/PDFEvolve.h"

void PDFEvolve::InitializeCT25As(vector<TString> FlavorList, vector<int> FlagList)
{
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

   if(flavor == "str"){
     if(fun_str) delete fun_str;
     fun_str = new gfuns(flag);
     fun_str->SetParameter(Parameter[flavor]);
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

   if(flavor == "svl"){
     if(fun_svl) delete fun_svl;
     fun_svl = new gfuns(flag);
     fun_svl->SetParameter(Parameter[flavor]);
   }
 }

 NormalizationCT25As();

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
   return sNorm * (fun_str->fcn(x) + fun_svl->fcn(x)) / 2.0;
 };
 Q0_sbar = [&](double x) {
   return sbarNorm * (fun_str->fcn(x) - fun_svl->fcn(x)) / 2.0;
 };

}

void PDFEvolve::NormalizationCT25As()
{
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
 RemM = RemM - StrangeMomentum;

 double strInt = NumberIntegral("str");
 double svlInt = NumberIntegral("svl");
 double strxInt = MomentumIntegral("str");
 double svlxInt = MomentumIntegral("svl");

 double sNint =    0.5 * (strInt + svlInt);
 double sbarNint = 0.5 * (strInt - svlInt);

 double sMint =    0.5 * (strxInt + svlxInt);
 double sbarMint = 0.5 * (strxInt - svlxInt);

 sNorm = StrangeMomentum / (sMint + sNint / sbarNint * sbarMint); //!
 sbarNorm = sNorm * sNint / sbarNint; //!

 double LastSeaMomentum = RemM; //ubar+dbar
 double LastSeaxInt = MomentumIntegral("dpu");
 dpuNorm = LastSeaMomentum / LastSeaxInt;
 dmuNorm = 1.0;

 MomentumList.clear();
 B0List.clear();

 MomentumList.push_back(0.0);
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
 B0List.push_back(0.0);
 B0List.push_back(StrangeB0);

 if(dvMomentum < 0.0 || uvMomentum < 0.0 || gluonMomentum < 0.0 || LastSeaMomentum < 0.0 || StrangeMomentum < 0.0){
   cout<<"ERROR! Normalization crashes!"<<endl;
   cout<<"-3 = "<<StrangeMomentum<<endl;
   cout<<"-2 = "<<LastSeaMomentum<<endl;
   cout<<"-1 = "<<0.0<<endl;
   cout<<" 0 = "<<gluonMomentum<<endl;
   cout<<" 1 = "<<uvMomentum<<endl;
   cout<<" 2 = "<<dvMomentum<<endl;
 }

}

