#include "Calculation/PDFChi2.h"

double PDFChi2::LMPenalty(TString LMType, vector<int> LM, vector<double> dM)
{
 double Value = 0.0;
 if(LMType == "ratioPDF"){
   double Xv;
   double vLM = dM.at(0);
   double X_0 = dM.at(1);
   double X_1 = dM.at(2);
   if(LM.size() == 1){
     double x = dM.at(3);
     double ssbr = setting.GetPDF(-3, x, setting.Qini) + setting.GetPDF(3, x, setting.Qini);
     double udbr = setting.GetPDF(-2, x, setting.Qini) + setting.GetPDF(-1, x, setting.Qini);
     if(fabs(udbr) < 1e-16) udbr = udbr / fabs(udbr) * 1e-16;
     Xv = ssbr / udbr;
   }
   if(Xv > X_0)      Value = vLM * pow((Xv - X_0), 2.0);
   else if(Xv < X_1) Value = vLM * pow((X_1 - Xv), 2.0);
 }
 else if(LMType == "LargeCoefficient"){
   double Xv;
   double vLM = dM.at(0);
   double sumsq = 0.0;
   for(auto iter = setting.ShapeParameterValue.begin(); iter != setting.ShapeParameterValue.end(); iter++){
     for(int i = 0; i < iter->second.size(); i++){
       if(iter->first != "str" || i <= 4){
         sumsq = sumsq + pow(iter->second.at(i), 2);
       }
     }
   }
   Xv = sumsq;
   double X_0 = 0.0;
   Value = vLM * (Xv - X_0);
 }
 else if(LMType == "SystematicShift"){
   int nshift = (int)(dM.size());
   double vLM = dM.at(0);
   if(LM.size() != 2 * nshift){
     cout<<"fatal Case(22): LM(0,I) = "<<LM.size()<<" != 2 * "<<nshift<<endl;
     return 0.0;
   }
   double sump = 0.0;
   for(int ishift = 1; ishift <= nshift; ishift++){
     int ID = LM.at(ishift * 2 - 2);

     if(IDtoIndex.count(ID) == 0) return 0.0;

     int Icorr = LM.at(ishift * 2 - 1);
     double wt = dM.at(ishift - 1);
     int Ncorr = AllData.at(IDtoIndex.at(ID))->lambda.size();
     double shift = 0.0;
     if(Icorr >= 1 && Icorr <= Ncorr){
       shift = AllData.at(IDtoIndex.at(ID))->lambda(Icorr - 1);
     }
     else{
       cout<<"fcn05: fatal Icorr,Ncorr="<<Icorr<<"  "<<Ncorr<<endl;
     }
     double pen = wt * pow(shift, 4.0);
     sump = sump + pen;
   }
   double X_0 = 0.0;
   double Xv = sump;
   Value = vLM * (Xv - X_0);
 }
 else if(LMType == "PDFLMScan"){
   double lambda = dM.at(0);
   double x = dM.at(1);
   double Q = dM.at(2);
   int flavor = LM.at(0);

   double Rs0 = 0.5;
   if(flavor == 21 && dM.size() == 4) Rs0 = dM.at(3);

//   Value = lambda * setting.GetPDF(flavor, x, Q);
//   Value = lambda * setting.GetPDF(flavor, x, Q) - log(1.0 - setting.GetPDF(flavor, x, Q));
   if(flavor == 21) Value = lambda * pow(setting.GetPDF(flavor, x, Q) - Rs0, 2);
   else Value = lambda * setting.GetPDF(flavor, x, Q);

   if(!isfinite(Value)) Value = 0.0;
//   cout<<"Lambda = "<<lambda<<" PDF = "<<setting.GetPDF(flavor, x, Q)<<" LM penalty = "<<Value<<endl;
//   cout<<"Additional penalty = "<<-log(1.0 - setting.GetPDF(flavor, x, Q))<<endl;
//   cout<<"Input Rs0 = "<<Rs0<<endl;
 }
 else if(LMType.Contains("PDFCombination")){
   double lambda = dM.at(0);
   double x = dM.at(1);
   double Q = dM.at(2);

   TString PDFCombination = LMType;
   PDFCombination.ReplaceAll("PDFCombination", "");
   TFormula PDFFormula("", PDFCombination);
   if(PDFCombination.Contains("[u]")) PDFFormula.SetParameter("u", setting.GetPDF(2, x, Q));
   if(PDFCombination.Contains("[d]")) PDFFormula.SetParameter("d", setting.GetPDF(1, x, Q));
   if(PDFCombination.Contains("[s]")) PDFFormula.SetParameter("s", setting.GetPDF(3, x, Q));
   if(PDFCombination.Contains("[c]")) PDFFormula.SetParameter("c", setting.GetPDF(4, x, Q));
   if(PDFCombination.Contains("[b]")) PDFFormula.SetParameter("b", setting.GetPDF(5, x, Q));
   if(PDFCombination.Contains("[ubar]")) PDFFormula.SetParameter("ubar", setting.GetPDF(-2, x, Q));
   if(PDFCombination.Contains("[dbar]")) PDFFormula.SetParameter("dbar", setting.GetPDF(-1, x, Q));
   if(PDFCombination.Contains("[sbar]")) PDFFormula.SetParameter("sbar", setting.GetPDF(-3, x, Q));
   if(PDFCombination.Contains("[cbar]")) PDFFormula.SetParameter("cbar", setting.GetPDF(-4, x, Q));
   if(PDFCombination.Contains("[bbar]")) PDFFormula.SetParameter("bbar", setting.GetPDF(-5, x, Q));
   if(PDFCombination.Contains("[g]")) PDFFormula.SetParameter("g", setting.GetPDF(0, x, Q));

   Value = lambda * PDFFormula.Eval(0);
   if(!isfinite(Value)) Value = 0.0;
   cout<<"Lambda = "<<lambda<<" PDF = "<<Value / lambda<<" LM penalty = "<<Value<<endl;
 }

 return Value;
}

