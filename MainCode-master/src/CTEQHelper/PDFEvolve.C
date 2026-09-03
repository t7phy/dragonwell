#include "CTEQHelper/PDFEvolve.h"

PDFEvolve::PDFEvolve()
{
 PrepareIntegral();
}


void PDFEvolve::Initialize(int ifun, vector<TString> FlavorList, vector<int> FlagList)
{
 if(FlavorList.size() != FlagList.size()){
   cout<<"ERROR!"<<endl;
   return;
 }

 if(ifun == 1){//CT18
   InitializeCT18(FlavorList, FlagList);
 }
 else if(ifun == 2){//CT18As
   InitializeCT18As(FlavorList, FlagList);
 }
 else if(ifun == 3){//CT25As
   InitializeCT25As(FlavorList, FlagList);
 }
 else if(ifun == 999){//Fantomas CT18
   InitializeFantoCT18(FlavorList, FlagList);
 }
 else if(ifun == 99901){//Fantomas + gfun
   InitializeFantoMix(FlavorList, FlagList);
 }

}

void PDFEvolve::Normalization(int ifun)
{
 double RemM = 1.0;

 if(ifun == 1){//CT18
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
   double sxInt = MomentumIntegral("str");
   sNorm = StrangeMomentum / sxInt; //!
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

   //cout<<"-3 = "<<StrangeMomentum<<endl;
   //cout<<"-2 = "<<LastSeaMomentum<<endl;
   //cout<<"-1 = "<<0.0<<endl;
   //cout<<" 0 = "<<gluonMomentum<<endl;
   //cout<<" 1 = "<<uvMomentum<<endl;
   //cout<<" 2 = "<<dvMomentum<<endl;
 }

}

/////////////////////////////////////////////////////////////////////////////////////

double PDFEvolve::GetQ0Function(double z, TString flavor)
{
 double Value = 0.0;

 double x = pow(z, Ga);

 if(x < 1e-10 || x > 0.9999999999) return 0.0;

 if(flavor == "gluon") Value = fun_gluon->fcn(x) * (Ga * x / z);
 else if(flavor == "uv") Value = fun_uv->fcn(x) * (Ga * x / z);
 else if(flavor == "dv") Value = fun_dv->fcn(x) * (Ga * x / z);
 else if(flavor == "str") Value = fun_str->fcn(x) * (Ga * x / z);
 else if(flavor == "dpu") Value = fun_dpu->fcn(x) * (Ga * x / z);
 else if(flavor == "dmu") Value = fun_dmu->fcn(x) * (Ga * x / z);
 else if(flavor == "svl") Value = fun_svl->fcn(x) * (Ga * x / z);

 return Value;
}

double PDFEvolve::GetQ0xFunction(double z, TString flavor)
{
 double x = pow(z, Ga);

 return x * GetQ0Function(z, flavor);
}


double PDFEvolve::NumberIntegral(TString flavor)
{
 double Value = 0.0;

 auto f = bind(&PDFEvolve::GetQ0Function, this, _1, flavor);
 Value = PDFIntegral(f);

 return Value;
}

double PDFEvolve::MomentumIntegral(TString flavor)
{
 double Value = 0.0;

 auto f = bind(&PDFEvolve::GetQ0xFunction, this, _1, flavor);
 Value = PDFIntegral(f);

 return Value;
}

void PDFEvolve::PrepareIntegral()
{
 int npts = 10000;
 xvec.resize(npts + 1);
 wvec.resize(npts + 1);

 double c = 0.2;
 double p = 0.2;

 double x0 = pow(c, 1.0 / (1.0 - p));
 double z0 = (x0 + c * pow(x0, p)) / (1.0 + c);

 double u, z, wt, x, y, ypri;
 for(int i = 1; i <= npts; i++){
   u = (i - 0.5) / (double)npts;
   z = 1.0 - pow(u, 2.0);
   wt = 2.0 * u / (double)npts;

   if(z < z0){
     x = pow(z * (1.0 + c) / c, 1.0 / p);
   }
   else{
     x = 1.0 - (1.0 - z) * (1.0 + c) / (1.0 + p * c);
   }

   for(int iter = 1; iter <= 9; iter++){
     y = x + c * pow(x, p) - (1.0 + c) * z;
     ypri = 1.0 + c * p * pow(x, (p - 1.0));
     x = x - y / ypri;
     if((iter > 5) && (fabs(y) < 1e-10)) break;
   }

   xvec.at(i) = x;
   wvec.at(i) = wt * (1.0 + c) / (1.0 + c * p * pow(x, (p - 1.0)));
 }

}

double PDFEvolve::PDFIntegral(std::function<double(double)> fcn)
{
 double sum = 0.0;
 for(int i = 1; i <= xvec.size() - 1; i++){
   double x = xvec.at(i);
   sum += fcn(x) * wvec.at(i);
 }
 return sum;
}

///////////////////////////////////////////////////////////////////////////////////

void PDFEvolve::ParameterOutput()
{
/*
 cout<<endl;
 for(int iflavor = 0; iflavor < FlavorNameList.size(); iflavor++){
   cout<<"pdf->SetParameter(\""<<FlavorNameList.at(iflavor)<<"\",    vector<double>{";
   for(int i = 0; i < Parameter[FlavorNameList.at(iflavor)].size(); i++){
     cout<<setw(9)<<*right<<fixed<<setprecision(5)<<Parameter[FlavorNameList.at(iflavor)].at(i);
     if(i != Parameter[FlavorNameList.at(iflavor)].size() - 1) cout<<",";
   }
   cout<<"});"<<endl;
 }
 cout<<endl;
*/

 if(MomentumList.size() == 0){
   MomentumList.resize(FlavorNameList.size());
   B0List.resize(FlavorNameList.size());
 }

 cout<<endl;
 for(int i = 0; i < FlavorNameList.size(); i++){
   cout<<"  - parameter: [";
   cout<<FlavorNameList.at(i);
   cout<<",";
   cout<<setw(15 - FlavorNameList.at(i).Length())<<*right<<fixed<<setprecision(7)<<MomentumList.at(i);
   cout<<",";
   cout<<setw(11)<<*right<<fixed<<setprecision(7)<<B0List.at(i);
   cout<<",  [";
   for(int ip = 0; ip < Parameter.at(FlavorNameList.at(i)).size(); ip++){
     cout<<setw(9)<<*right<<fixed<<setprecision(5)<<Parameter.at(FlavorNameList.at(i)).at(ip);
     if(ip != Parameter.at(FlavorNameList.at(i)).size() - 1) cout<<",";
   }
   cout<<"]]"<<endl;
 }
 cout<<endl;

}

void PDFEvolve::pdsOutput()
{

}

