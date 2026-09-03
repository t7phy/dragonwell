#include "ePumpHelper/ePumpHelper.h"
#include <Minuit2/FCNBase.h>
#include "Minuit2/FunctionMinimum.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnUserCovariance.h"
#include "Minuit2/MnSimplex.h"

void ePumpHelper::ReadParameterInput(TString FileName)
{
 DefineCombination();
 DefineDataLegend();
 NameTransfer();

 ifstream ParameterFile("Parameter.in");
 ParameterFile >> Old_Parameter >> Old_Parameter_up >> Old_Parameter_down;

 ParameterEU = new ePump(FileName, 1.0);// Parameter EV
 ParameterEU->ReadInTheoryAndData();

 ExtendedEU = new ePump(this->FileName + "_Parameter", 1.0);// N EV PDFs
 strcpy(ExtendedEU->mainfile, EU->mainfile);
 ExtendedEU->ReadInTheoryAndData();

 TString NewPDFOutName = ExtendedEU->PDFoutfile;
 NewPDFOutName.ReplaceAll("/", "_Parameter/");
 strcpy(ExtendedEU->PDFoutfile, NewPDFOutName.Data());
 strcpy(ExtendedEU->mainfile, (FileName + "_Parameter").Data());
 ExtendedEU->suppressCCs();

 myLog.Initial(cout, ExtendedEU->ePout);

 ExtendedEU->Ni = EU->Ni + 1;

 ExtendedEU->M.resize(EU->Ni + 1);
 ExtendedEU->A.resize(EU->Ni + 1);
 ExtendedEU->L.resize(EU->Ni + 1);
 ExtendedEU->LinvA.resize(EU->Ni + 1);
 ExtendedEU->TdynP.resize(EU->Ni + 1);
 ExtendedEU->TdynM.resize(EU->Ni + 1);
 ExtendedEU->TdynBar.resize(EU->Ni + 1);
 ExtendedEU->TdynRMS.resize(EU->Ni + 1);

 ExtendedEU->OldPDF.resize(2 * (EU->Ni + 1) + 1);
 ExtendedEU->NewPDF.resize(2 * (EU->Ni + 1) + 1);
 ExtendedEU->OldPDFAlphaS.resize(2 * (EU->Ni + 1) + 1);
 ExtendedEU->NewPDFAlphaS.resize(2 * (EU->Ni + 1) + 1);

 for(int i = 0; i < EU->Ni + 1; i++){
   ExtendedEU->M[i].resize(EU->Ni + 1);
   ExtendedEU->L[i].resize(EU->Ni + 1);
 }

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   ExtendedEU->dChi2Set[k].resize(2 * ExtendedEU->Ni + 1);
   ExtendedEU->dChi2newSet[k].resize(2 * ExtendedEU->Ni + 1);

   ExtendedEU->Xset[k].resize(2 * ExtendedEU->Ni + 1);

   for(int a = 0; a < ExtendedEU->Na[k]; a++){
     ExtendedEU->Xmat[k][a].resize(2 * ExtendedEU->Ni + 1);
     ExtendedEU->XmatNew[k][a].resize(2 * ExtendedEU->Ni + 1);
     ExtendedEU->FractionalContribution[k][a].resize(2 * ExtendedEU->Ni + 1); //yfu
     ExtendedEU->dX[k][a].resize(ExtendedEU->Ni);
   }

   for(int i = 0; i < 2 * ExtendedEU->Ni + 1; i++){
     ExtendedEU->Xset[k][i].resize(ExtendedEU->Na[k]);
   }
 }

 ExtendedEU->TdynRMS.at(ExtendedEU->Ni - 1) = ParameterEU->TdynRMS.at(0);
 ExtendedEU->TdynP.at(ExtendedEU->Ni - 1) = ParameterEU->TdynP.at(0);
 ExtendedEU->TdynM.at(ExtendedEU->Ni - 1) = ParameterEU->TdynM.at(0);
 ExtendedEU->TdynBar.at(ExtendedEU->Ni - 1) = ParameterEU->TdynBar.at(0);

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   for(int i = EU->Ni; i < ExtendedEU->Ni; i++){
     for(int a = 0; a < ExtendedEU->Na[k]; a++){
       ExtendedEU->Xmat[k][a][2*i+1] = ParameterEU->Xmat[k][a][2 * (i - EU->Ni) + 1];
       ExtendedEU->XmatNew[k][a][2*i+1] = ExtendedEU->Xmat[k][a][2 * i + 1]; //yfu
       ExtendedEU->Xset[k][2*i+1][a] = ExtendedEU->Xmat[k][a][2 * i + 1];

       ExtendedEU->Xmat[k][a][2*i+2] = ParameterEU->Xmat[k][a][2 * (i - EU->Ni) + 2];
       ExtendedEU->XmatNew[k][a][2*i+2] = ExtendedEU->Xmat[k][a][2 * i + 2]; //yfu
       ExtendedEU->Xset[k][2*i+2][a] = ExtendedEU->Xmat[k][a][2 * i + 2];
       ExtendedEU->dX[k][a][i] = (ParameterEU->Xmat[k][a][2 * (i - EU->Ni) + 1] - ParameterEU->Xmat[k][a][2 * (i - EU->Ni) + 2]) / 2.0;
     }
   }
 }

 for(int k = 0; k < EU->Ndata; k++){
   ExtendedEU->SetXdyn(k);
 }

 ExtendedEU->ConstructUpdateMatrix();
 ParameterUpdate_K.resize(ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   ParameterUpdate_K.at(i) = 0.0;
 }

 auto PrepareQuadratic = [&](int k){
   vector<double> Ktemp;
   double Rtemp = 0.0;
   double Ltemp = 0.0;
   vector<double> Qtemp;

   Ktemp.resize(ExtendedEU->Ni);
   Qtemp.resize(ExtendedEU->Na[k]);

   for(int a = 0; a < ExtendedEU->Na[k]; a++) {
     Qtemp[a] = 0.0;
     for(int b = 0; b < ExtendedEU->Na[k]; b++) {
       Qtemp[a] += ExtendedEU->Cm[k][a][b] * ExtendedEU->XXdyn[k][b][ExtendedEU->Ni - 1] / 2.0;
     }
   }

   for(int i = 0; i < ExtendedEU->Ni; i++){
     Ktemp[i] = 0.0;
     for(int a = 0; a < ExtendedEU->Na[k]; a++) {
       Ktemp[i] += ExtendedEU->Xdyn[k][a][i] * Qtemp[a];
     }

     Ktemp[i] *= (ExtendedEU->weight[k] / ExtendedEU->Tsq);
     ParameterUpdate_K[i] += Ktemp[i];
   }

   for(int a = 0; a < ExtendedEU->Na[k]; a++) {
     Rtemp += (ExtendedEU->X0[k][a] - ExtendedEU->XE[k][a]) * Qtemp[a];
     Ltemp += ExtendedEU->XXdyn[k][a][ExtendedEU->Ni - 1] / 2.0 * Qtemp[a];
   }

   Rtemp *= (ExtendedEU->weight[k] / ExtendedEU->Tsq * 2.0);
   Ltemp *= (ExtendedEU->weight[k] / ExtendedEU->Tsq);
   ParameterUpdate_R += Rtemp;
   ParameterUpdate_L += Ltemp;
 };

 for(int k = 0; k < ExtendedEU->Ndata; k++){
   if(ExtendedEU->dataIncluded[k]){
     PrepareQuadratic(k);
   }
 }

 ExtendedEU->pdftype = PDF_format_type::NONE;
 ExtendedEU->UpdateObservables();

 UpdateParameter();
 UpdateParameterPDFs();
 UpdateParameterObservables();

}

void ePumpHelper::UpdateParameter()
{
 Eigen::MatrixXd M = Eigen::MatrixXd(ExtendedEU->Ni, ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   for(int j = 0; j < ExtendedEU->Ni; j++){
     M(i, j) = ExtendedEU->M[i][j];
   }
 }

 Eigen::MatrixXd IplusM = Eigen::MatrixXd::Identity(ExtendedEU->Ni, ExtendedEU->Ni) + M;
 IplusM_inv = IplusM.inverse();

 Eigen::MatrixXd M_sub = Eigen::MatrixXd(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1);
 for(int i = 0; i < ExtendedEU->Ni - 1; i++){
   for(int j = 0; j < ExtendedEU->Ni - 1; j++){
     M_sub(i, j) = ExtendedEU->M[i][j];
   }
 }

 Eigen::MatrixXd IplusM_sub = Eigen::MatrixXd::Identity(ExtendedEU->Ni - 1, ExtendedEU->Ni - 1) + M_sub;
 IplusM_sub_inv = IplusM_sub.inverse();

 Eigen::VectorXd Msub_Vector = Eigen::VectorXd(ExtendedEU->Ni - 1);
 for(int i = 0; i < ExtendedEU->Ni - 1; i++){
   Msub_Vector(i) = ExtendedEU->M[ExtendedEU->Ni - 1][i];
 }

 Eigen::VectorXd AVector = Eigen::VectorXd(ExtendedEU->Ni - 1);
 for(int i = 0; i < ExtendedEU->Ni - 1; i++){
   AVector(i) = ExtendedEU->A[i];
 }

 Eigen::VectorXd KVector = Eigen::VectorXd(ExtendedEU->Ni - 1);
 for(int i = 0; i < ExtendedEU->Ni - 1; i++){
   KVector(i) = ParameterUpdate_K[i];
 }

 auto CalculateCoefficient = [&](void){
   double A0 = 0.0, A1 = 0.0, A2 = 0.0, A3 = 0.0, A4 = 0.0;

   Eigen::VectorXd IplusM_sub_inv_A = IplusM_sub_inv * AVector;
   Eigen::VectorXd IplusM_sub_inv_Msub = IplusM_sub_inv * Msub_Vector;
   Eigen::VectorXd IplusM_sub_inv_K = IplusM_sub_inv * KVector;

   A0 = AVector.dot(IplusM_sub_inv_A) * (-1.0);

   A1 = AVector.dot(IplusM_sub_inv_Msub)
      + Msub_Vector.dot(IplusM_sub_inv_A)
      - 2.0 * ExtendedEU->A[ExtendedEU->Ni - 1];

   A2 = AVector.dot(IplusM_sub_inv_K)
      - Msub_Vector.dot(IplusM_sub_inv_Msub)
      + KVector.dot(IplusM_sub_inv_A)
      + (1.0 + ExtendedEU->M[ExtendedEU->Ni - 1][ExtendedEU->Ni - 1] + ParameterUpdate_R);

   A3 = Msub_Vector.dot(IplusM_sub_inv_K) * (-1.0)
      - KVector.dot(IplusM_sub_inv_Msub)
      + 2.0 * ParameterUpdate_K[ExtendedEU->Ni - 1];

   A4 = KVector.dot(IplusM_sub_inv_K) * (-1.0)
      + ParameterUpdate_L;

   vector<double> Result = {A0, A1, A2, A3, A4};

   return Result;
 };

 auto SearchBestFitParameter = [&](vector<double> Coefficient){
   class ParameterFit : public ROOT::Minuit2::FCNBase{
     public:

     virtual double Up() const {return theErrorDef;}

     vector<double> Coefficients;
     
     virtual void Initialize(vector<double> coeff){
       Coefficients = coeff;
       Input("Parameter", 0.0, 0.05, -10.0, 10.0);
     }

     virtual double operator()(const std::vector<double>& par) const{
       double z = par.at(0);

       double Value = Coefficients.at(0)
                    + Coefficients.at(1) * z
                    + Coefficients.at(2) * z * z
                    + Coefficients.at(3) * z * z * z
                    + Coefficients.at(4) * z * z * z * z;

       return Value;
     }

     void setErrorDef(double def) {theErrorDef = def;}

     ROOT::Minuit2::MnUserParameters upar;
     virtual void Input(TString name, double central, double step, double left, double right){
       upar.Add(name.Data(), central, step);
       upar.SetLimits(name.Data(), left, right);
     }

     private:

     double theErrorDef = 1.0;
   };

   ParameterFit FCN;
   FCN.Initialize(Coefficient);
   ROOT::Minuit2::MnSimplex simplex(FCN, FCN.upar);
   ROOT::Minuit2::FunctionMinimum min = simplex(10000);
   ROOT::Minuit2::MnUserParameters FinalParam = min.UserParameters();
   vector<double> pars = FinalParam.Params();
   vector<double> parerrs = FinalParam.Errors();

   double Central = pars.at(0);
   int irt;

   auto F_zc = [&](double z){
     double Value = Coefficient.at(0)
                  + Coefficient.at(1) * z
                  + Coefficient.at(2) * z * z
                  + Coefficient.at(3) * z * z * z
                  + Coefficient.at(4) * z * z * z * z;
     return Value;
   };

   auto F_zc_up = [&](double z){
     double Value = F_zc(z) - F_zc(Central) - 1;

     return Value;
   };

   double Up = zbrnt(F_zc_up, Central, Central + 10.0, 0.001, irt);
   double Down = zbrnt(F_zc_up, Central - 10.0, Central, 0.001, irt);

   vector<double> Result = {Central, Up, Down};

   return Result;
 };

 auto GetNewBestFitPar = [&](double z){
   Eigen::VectorXd IplusM_sub_inv_A = IplusM_sub_inv * AVector;
   Eigen::VectorXd IplusM_sub_inv_Msub = IplusM_sub_inv * Msub_Vector;
   Eigen::VectorXd IplusM_sub_inv_K = IplusM_sub_inv * KVector;

   New_BestFit_Par = Eigen::VectorXd(ExtendedEU->Ni);

   for(int i = 0; i < ExtendedEU->Ni - 1; i++){
     New_BestFit_Par(i) = IplusM_sub_inv_A(i) - IplusM_sub_inv_Msub(i) * z - IplusM_sub_inv_K(i) * z * z;
     myLog<<i<<": z_"<<i<<" = ";
     myLog<<setw(10)<<scientific<<setprecision(3)<<IplusM_sub_inv_A(i)<<" - ";
     myLog<<setw(10)<<scientific<<setprecision(3)<<IplusM_sub_inv_Msub(i)<<" * ";
     myLog<<setw(5)<<fixed<<setprecision(3)<<z<<" - ";
     myLog<<setw(10)<<scientific<<setprecision(3)<<IplusM_sub_inv_K(i)<<" * ";
     myLog<<setw(5)<<fixed<<setprecision(3)<<z<<"^2 = ";
     myLog<<setw(6)<<fixed<<setprecision(3)<<New_BestFit_Par(i)<<endl;
   }
   New_BestFit_Par(ExtendedEU->Ni - 1) = z;
 };

 vector<double> Coefficient = CalculateCoefficient();
 vector<double> ZcResult = SearchBestFitParameter(Coefficient);

 New_Parameter = ZcResult.at(0);
 New_Parameter_up = ZcResult.at(1);
 New_Parameter_down = ZcResult.at(2);

 double OldDeltaUp = Old_Parameter_up - Old_Parameter;
 double OldDeltaDown = Old_Parameter - Old_Parameter_down;

 auto ZtoC = [&](double z){
   if(z >= 0.0) return Old_Parameter + z * OldDeltaUp;
   else return Old_Parameter + z * OldDeltaDown;
 };

 double Real_New_Parameter      = ZtoC(New_Parameter);
 double Real_New_Parameter_up   = ZtoC(New_Parameter_up);
 double Real_New_Parameter_down = ZtoC(New_Parameter_down);

 GetNewBestFitPar(New_Parameter);

 myLog<<fixed<<setprecision(4)<<"Original Parameter = "<<Old_Parameter<<endl;
 myLog<<fixed<<setprecision(4)<<"Updated Parameter = "<<Real_New_Parameter<<endl;
 myLog<<fixed<<setprecision(4)<<"Original Parameter up = "<<Old_Parameter_up<<"  Original Parameter down = "<<Old_Parameter_down<<endl;
 myLog<<fixed<<setprecision(4)<<"Updated Parameter up = "<<Real_New_Parameter_up<<"  Updated Parameter down = "<<Real_New_Parameter_down<<endl;
}

void ePumpHelper::UpdateParameterPDFs()
{
 vector<pdsReader *> OldParameterPDF;

 OldParameterPDF.resize(2 * ExtendedEU->Ni + 1);
 NewParameterPDF.resize(2 * ExtendedEU->Ni + 1);

 for(int i = 0; i < 2 * EU->Ni + 1; i++){
   OldParameterPDF.at(i) = new pdsReader();
   OldParameterPDF.at(i)->Initialize((TString)EU->PDFinfile + TString::Format(".%02d", i) + (TString)".pds");
   NewParameterPDF.at(i) = new pdsReader();
   NewParameterPDF.at(i)->Initialize((TString)EU->PDFinfile + TString::Format(".%02d", i) + (TString)".pds");
 }
 OldParameterPDF.at(2 * EU->Ni + 1) = new pdsReader();
 OldParameterPDF.at(2 * EU->Ni + 1)->Initialize((TString)ParameterEU->PDFinfile + TString::Format(".%02d", 1) + (TString)".pds");
 OldParameterPDF.at(2 * EU->Ni + 2) = new pdsReader();
 OldParameterPDF.at(2 * EU->Ni + 2)->Initialize((TString)ParameterEU->PDFinfile + TString::Format(".%02d", 2) + (TString)".pds");
 NewParameterPDF.at(2 * EU->Ni + 1) = new pdsReader();
 NewParameterPDF.at(2 * EU->Ni + 1)->Initialize((TString)ParameterEU->PDFinfile + TString::Format(".%02d", 1) + (TString)".pds");
 NewParameterPDF.at(2 * EU->Ni + 2) = new pdsReader();
 NewParameterPDF.at(2 * EU->Ni + 2)->Initialize((TString)ParameterEU->PDFinfile + TString::Format(".%02d", 2) + (TString)".pds");
 NewParameterOnlyPDF = new pdsReader();
 NewParameterOnlyPDF->Initialize((TString)EU->PDFinfile + TString::Format(".%02d", 0) + (TString)".pds");

 // Copy M
 Eigen::MatrixXd M = Eigen::MatrixXd(ExtendedEU->Ni, ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   for(int j = 0; j < ExtendedEU->Ni; j++){
     M(i, j) = ExtendedEU->M[i][j];
   }
 }

 // New best fit PDF eq.15
 vector<double> UPD = OldParameterPDF.at(0)->UPD;
 for(int i = 0; i < UPD.size(); i++){
   Eigen::VectorXd OldF(ExtendedEU->Ni);
   double Qf = 0.0;

   for(int iEV = 0; iEV < ExtendedEU->Ni; iEV++){

     double dx, ddx, tp, tm, tbar;

     if (ExtendedEU->T_flag == 1) {
         tp = ExtendedEU->TdynRMS[iEV];
         tm = ExtendedEU->TdynRMS[iEV];
         tbar = ExtendedEU->TdynRMS[iEV];
     } else {
         tp = ExtendedEU->TdynP[iEV];
         tm = ExtendedEU->TdynM[iEV];
         tbar = ExtendedEU->TdynBar[iEV];
     }

     TaylorCoeffs(dx, ddx, OldParameterPDF.at(0)->UPD.at(i), OldParameterPDF.at(2 * iEV + 1)->UPD.at(i), OldParameterPDF.at(2 * iEV + 2)->UPD.at(i), tp, tm, tbar);

     OldF(iEV) = dx;
     if(iEV == ExtendedEU->Ni - 1) Qf = ddx / 2.0;
   }
   double shift = New_BestFit_Par.dot(OldF) + Qf * New_BestFit_Par(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1); // eq.15
   NewParameterPDF.at(0)->UPD.at(i) = UPD.at(i) + shift;
   NewParameterOnlyPDF->UPD.at(i) = UPD.at(i) + OldF(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1) + Qf * New_BestFit_Par(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1);
 }

 // Parameter Error PDF eq.21 (DynTol: eq.A7)
 for(int i = 0; i < UPD.size(); i++){
   double up = NewParameterPDF.at(0)->UPD.at(i);
   double down = NewParameterPDF.at(0)->UPD.at(i);

   double dx, ddx, tp, tm, tbar;

   if (ExtendedEU->T_flag == 1) {
       tp = ExtendedEU->TdynRMS[EU->Ni];
       tm = ExtendedEU->TdynRMS[EU->Ni];
       tbar = ExtendedEU->TdynRMS[EU->Ni];
   } else {
       tp = ExtendedEU->TdynP[EU->Ni];
       tm = ExtendedEU->TdynM[EU->Ni];
       tbar = ExtendedEU->TdynBar[EU->Ni];
   }

   TaylorCoeffs(dx, ddx, OldParameterPDF.at(0)->UPD.at(i), OldParameterPDF.at(2 * EU->Ni + 1)->UPD.at(i), OldParameterPDF.at(2 * EU->Ni + 2)->UPD.at(i), tp, tm, tbar);

   double DeltaPDF1 = (OldParameterPDF.at(2 * EU->Ni + 1)->UPD.at(i) - OldParameterPDF.at(0)->UPD.at(i)) / tp;
   double DeltaPDF2 = (OldParameterPDF.at(0)->UPD.at(i) - OldParameterPDF.at(2 * EU->Ni + 2)->UPD.at(i)) / tm;

   double DeltaQf1 = ddx / 2.0;
   double DeltaQf2 = ddx / 2.0;

   for(int ii = 0; ii < EU->Ni; ii++){
     for(int jj = 0; jj < EU->Ni; jj++){

       double dx, ddx, tp, tm, tbar;
       double dx1, dx2;

       if (ExtendedEU->T_flag == 1) {
           tp = ExtendedEU->TdynRMS[jj];
           tm = ExtendedEU->TdynRMS[jj];
           tbar = ExtendedEU->TdynRMS[jj];
       } else {
           tp = ExtendedEU->TdynP[jj];
           tm = ExtendedEU->TdynM[jj];
           tbar = ExtendedEU->TdynBar[jj];
       }

       TaylorCoeffs(dx, ddx, OldParameterPDF.at(0)->UPD.at(i), OldParameterPDF.at(2 * jj + 1)->UPD.at(i), OldParameterPDF.at(2 * jj + 2)->UPD.at(i), tp, tm, tbar);

       dx1 = (OldParameterPDF.at(2 * jj + 1)->UPD.at(i) - OldParameterPDF.at(0)->UPD.at(i)) / tp;
       dx2 = (OldParameterPDF.at(0)->UPD.at(i) - OldParameterPDF.at(2 * jj + 2)->UPD.at(i)) / tm;

       DeltaPDF1 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx1;
       DeltaPDF2 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx2;

       DeltaQf1 -= ParameterUpdate_K.at(ii) * IplusM_sub_inv(ii, jj) * dx1;
       DeltaQf2 -= ParameterUpdate_K.at(ii) * IplusM_sub_inv(ii, jj) * dx2;
     }
   }

   up = up
      + (New_Parameter_up - New_Parameter) * DeltaPDF1
      + (New_Parameter_up * New_Parameter_up - New_Parameter * New_Parameter) * DeltaQf1;

   down = down
       - (New_Parameter - New_Parameter_down) * DeltaPDF2
       + (New_Parameter_down * New_Parameter_down - New_Parameter * New_Parameter) * DeltaQf2;

   NewParameterPDF.at(2 * EU->Ni + 1)->UPD.at(i) = up;
   NewParameterPDF.at(2 * EU->Ni + 2)->UPD.at(i) = down;
 }

 // Error PDF set after PDF+Parameter simultaneous fit eq.24
 for(int i = 0; i < UPD.size(); i++){
   double central = NewParameterPDF.at(0)->UPD.at(i);

   double dx, ddx, tp, tm, tbar;

   for(int iEV = 0; iEV < EU->Ni; iEV++){
     double f1 = 0.0, f2 = 0.0;

     for(int jEV = 0; jEV < EU->Ni; jEV++){

       if (ExtendedEU->T_flag == 1) {
           tp = ExtendedEU->TdynRMS[jEV];
           tm = ExtendedEU->TdynRMS[jEV];
           tbar = ExtendedEU->TdynRMS[jEV];
       } else {
           tp = ExtendedEU->TdynP[jEV];
           tm = ExtendedEU->TdynM[jEV];
           tbar = ExtendedEU->TdynBar[jEV];
       }

       double df1 = (OldParameterPDF.at(2 * jEV + 1)->UPD.at(i) - OldParameterPDF.at(0)->UPD.at(i)) / tp;
       double df2 = (OldParameterPDF.at(0)->UPD.at(i) - OldParameterPDF.at(2 * jEV + 2)->UPD.at(i)) / tm;
       f1 += ExtendedEU->U[jEV][iEV] * df1;
       f2 -= ExtendedEU->U[jEV][iEV] * df2;
     }
     f1 /= sqrt(ExtendedEU->Pweight + ExtendedEU->d[iEV]);
     f2 /= sqrt(ExtendedEU->Pweight + ExtendedEU->d[iEV]);
     f1 += central;
     f2 += central;

     NewParameterPDF.at(2 * iEV + 1)->UPD.at(i) = f1;
     NewParameterPDF.at(2 * iEV + 2)->UPD.at(i) = f2;
   }
 }

 NewParameterPDF.at(0)->OutputPDF((TString)ExtendedEU->PDFoutfile + (TString)".00.pds");

 for(int i = 0; i < ExtendedEU->Ni; i++){
   NewParameterPDF.at(2 * i + 1)->OutputPDF((TString)ExtendedEU->PDFoutfile + TString::Format(".%02d", 2 * i + 1) + (TString)".pds");
   NewParameterPDF.at(2 * i + 2)->OutputPDF((TString)ExtendedEU->PDFoutfile + TString::Format(".%02d", 2 * i + 2) + (TString)".pds");
 }
}

void ePumpHelper::UpdateParameterObservables()
{
 // Initialize vector of new observables
 NewObservableSet.resize(ExtendedEU->Ndata);
 ObservableDeltaParameter.resize(ExtendedEU->Ndata);
 ObservableDeltaParameterPlus.resize(ExtendedEU->Ndata);
 ObservableDeltaParameterMinus.resize(ExtendedEU->Ndata);
 NewObservableParameterOnly.resize(ExtendedEU->Ndata);
 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){
   NewObservableSet.at(idata).resize(ExtendedEU->Na[idata]);
   ObservableDeltaParameter.at(idata).resize(ExtendedEU->Na[idata]);
   ObservableDeltaParameterPlus.at(idata).resize(ExtendedEU->Na[idata]);
   ObservableDeltaParameterMinus.at(idata).resize(ExtendedEU->Na[idata]);
   NewObservableParameterOnly.at(idata).resize(ExtendedEU->Na[idata]);
   for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){
     NewObservableSet.at(idata).at(ipoint).resize(2 * ExtendedEU->Ni + 1);
   }
 }

 // Copy M
 Eigen::MatrixXd M = Eigen::MatrixXd(ExtendedEU->Ni, ExtendedEU->Ni);
 for(int i = 0; i < ExtendedEU->Ni; i++){
   for(int j = 0; j < ExtendedEU->Ni; j++){
     M(i, j) = ExtendedEU->M[i][j];
   }
 }

 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){

   for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){

     // New best fit observable eq.15
     double Central = ExtendedEU->Xmat[idata][ipoint][0];

     Eigen::VectorXd OldObservable(ExtendedEU->Ni);
     double Qf = 0.0;

     for(int iEV = 0; iEV < ExtendedEU->Ni; iEV++){

       double Up = ExtendedEU->Xmat[idata][ipoint][2 * iEV + 1];
       double Down = ExtendedEU->Xmat[idata][ipoint][2 * iEV + 2];

       double dx, ddx, tp, tm, tbar;

       if (ExtendedEU->T_flag == 1) {
           tp = ExtendedEU->TdynRMS[iEV];
           tm = ExtendedEU->TdynRMS[iEV];
           tbar = ExtendedEU->TdynRMS[iEV];
       } else {
           tp = ExtendedEU->TdynP[iEV];
           tm = ExtendedEU->TdynM[iEV];
           tbar = ExtendedEU->TdynBar[iEV];
       }

       TaylorCoeffs(dx, ddx, Central, Up, Down, tp, tm, tbar);

       OldObservable(iEV) = dx;
       if(iEV == ExtendedEU->Ni - 1) Qf = ddx / 2.0;
     }
     double shift = New_BestFit_Par.dot(OldObservable) + Qf * New_BestFit_Par(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1); // eq.15
     NewObservableSet.at(idata).at(ipoint).at(0) = Central + shift;
     NewObservableParameterOnly.at(idata).at(ipoint) = Central + OldObservable(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1) + Qf * New_BestFit_Par(ExtendedEU->Ni - 1) * New_BestFit_Par(ExtendedEU->Ni - 1);

     // Parameter Error observable eq.21 (DynTol: eq.A7)
     double up = NewObservableSet.at(idata).at(ipoint).at(0);
     double down = NewObservableSet.at(idata).at(ipoint).at(0);

     double dx, ddx, tp, tm, tbar;

     if (ExtendedEU->T_flag == 1) {
         tp = ExtendedEU->TdynRMS[EU->Ni];
         tm = ExtendedEU->TdynRMS[EU->Ni];
         tbar = ExtendedEU->TdynRMS[EU->Ni];
     } else {
         tp = ExtendedEU->TdynP[EU->Ni];
         tm = ExtendedEU->TdynM[EU->Ni];
         tbar = ExtendedEU->TdynBar[EU->Ni];
     }

     TaylorCoeffs(dx, ddx, Central, ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1], ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2], tp, tm, tbar);

     double DeltaPDF = dx;
     double DeltaPDF1 = (ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1] - Central) / tp;
     double DeltaPDF2 = (Central - ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2]) / tm;

     double DeltaQf = ddx / 2.0;
     double DeltaQf1 = ddx / 2.0;
     double DeltaQf2 = ddx / 2.0;

     for(int ii = 0; ii < EU->Ni; ii++){
       for(int jj = 0; jj < EU->Ni; jj++){

         double dx, ddx, tp, tm, tbar;
         double dx1, dx2;

         if (ExtendedEU->T_flag == 1) {
             tp = ExtendedEU->TdynRMS[jj];
             tm = ExtendedEU->TdynRMS[jj];
             tbar = ExtendedEU->TdynRMS[jj];
         } else {
             tp = ExtendedEU->TdynP[jj];
             tm = ExtendedEU->TdynM[jj];
             tbar = ExtendedEU->TdynBar[jj];
         }

         TaylorCoeffs(dx, ddx, Central, ExtendedEU->Xmat[idata][ipoint][2 * jj + 1], ExtendedEU->Xmat[idata][ipoint][2 * jj + 2], tp, tm, tbar);

         dx1 = (ExtendedEU->Xmat[idata][ipoint][2 * jj + 1] - Central) / tp;
         dx2 = (Central - ExtendedEU->Xmat[idata][ipoint][2 * jj + 2]) / tm;

         DeltaPDF -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx;
         DeltaPDF1 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx1;
         DeltaPDF2 -= M(ExtendedEU->Ni - 1, ii) * IplusM_sub_inv(ii, jj) * dx2;

         DeltaQf -= ParameterUpdate_K.at(ii) * IplusM_sub_inv(ii, jj) * dx;
         DeltaQf1 -= ParameterUpdate_K.at(ii) * IplusM_sub_inv(ii, jj) * dx1;
         DeltaQf2 -= ParameterUpdate_K.at(ii) * IplusM_sub_inv(ii, jj) * dx2;
       }
     }

     ObservableDeltaParameter.at(idata).at(ipoint) = DeltaPDF;
     ObservableDeltaParameterPlus.at(idata).at(ipoint) = DeltaPDF1;
     ObservableDeltaParameterMinus.at(idata).at(ipoint) = DeltaPDF2;

     up = up
        + (New_Parameter_up - New_Parameter) * DeltaPDF1
        + (New_Parameter_up * New_Parameter_up - New_Parameter * New_Parameter) * DeltaQf1;

     down = down
         - (New_Parameter - New_Parameter_down) * DeltaPDF2
         + (New_Parameter_down * New_Parameter_down - New_Parameter * New_Parameter) * DeltaQf2;

     NewObservableSet.at(idata).at(ipoint).at(2 * EU->Ni + 1) = up;
     NewObservableSet.at(idata).at(ipoint).at(2 * EU->Ni + 2) = down;
   }
 }

 myLog<<endl;
 myLog<<"---------------------------------------------------------------"<<endl;
 myLog<<"      Original and Updated Predictions and Uncertainties"<<endl;
 myLog<<"------------------------------------------------------------"<<endl;
 myLog<<endl;

 for(int idata = 0; idata < ExtendedEU->Ndata; idata++){

   myLog<<" For Observables X[a] in Data Set: "<<ExtendedEU->dataset[idata]<<endl<<endl;
   myLog<<"      a         X[a]          X+[a]         X-[a]       DXsym[a]"<<endl;

   for(int ipoint = 0; ipoint < ExtendedEU->Na[idata]; ipoint++){

     myLog<<"Old"<<setw(4)<<ipoint + 1<<"  ";
     myLog<<setw(14)<<setprecision(4)<<scientific<<ExtendedEU->Xmat[idata][ipoint][0];
     myLog<<setw(14)<<setprecision(4)<<scientific<<ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1];
     myLog<<setw(14)<<setprecision(4)<<scientific<<ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2];
     myLog<<setw(14)<<setprecision(4)<<scientific<<fabs(ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 2] - ExtendedEU->Xmat[idata][ipoint][2 * EU->Ni + 1]) / 2.0<<endl;
     myLog<<"New"<<setw(4)<<ipoint + 1<<"  ";
     myLog<<setw(14)<<setprecision(4)<<scientific<<NewObservableSet[idata][ipoint][0];
     myLog<<setw(14)<<setprecision(4)<<scientific<<NewObservableSet[idata][ipoint][2 * EU->Ni + 1];
     myLog<<setw(14)<<setprecision(4)<<scientific<<NewObservableSet[idata][ipoint][2 * EU->Ni + 2];
     myLog<<setw(14)<<setprecision(4)<<scientific<<fabs(NewObservableSet[idata][ipoint][2 * EU->Ni + 2] - NewObservableSet[idata][ipoint][2 * EU->Ni + 1]) / 2.0<<endl;
     myLog<<endl;
   }
 }
}

double ePumpHelper::zbrnt(function<double(double)> func, double x1, double x2, double tolin, int &irt)
{
//                                                   -=-=- zbrnt
//
//                          Return code  IRT = 1 : limits do not bracket a root;
//                                             2 : function call exceeds maximum
// appears to be Wijngaarden-Dekker-Brent algorithm zbrent from Numerical Recipes.
//
// www.ulib.org/webRoot/Books/Numerical_Recipes/bookfpdf/f9-3.pdf 
 double Value;

 int ITMAX = 1000;
 double EPS = 3e-12;

 irt = 0;
 double tol = fabs(tolin);          //modified so it can't change input TOLIN (jcp 11/4/02)
 double a = x1;
 double b = x2;
 double fa = func(a);
 double fb = func(b);

 if(fb * fa > 0.0){
   cout<<"Root must be bracketed for ZBRNT. Set = 0 fa = "<<fa<<" fb = "<<fb<<endl;
   cout<<"ZBRNT fatal error"<<endl;
   irt = 1;
   return 0.0;
 }

 double c = b;                       //Previously missing -- would matter if FC=0 -- (jcp 11/12/01)
 double fc = fb;

 double d, e;
 double tol1;
 double xm;
 double s, p, q, r;
 for(int iter = 1; iter <= ITMAX; iter++){
   if(fb * fc > 0.0){
     c = a;
     fc = fa;
     d = b - a;
     e = d;
   }
   if(fabs(fc) < fabs(fb)){
     a = b;
     b = c;
     c = a;
     fa = fb;
     fb = fc;
     fc = fa;
   }
   tol1 = 2.0 * EPS * fabs(b) + 0.5 * tol;
   xm = 0.5 * (c - b);
   if(fabs(xm) <= tol1 || fb == 0.0){
     Value = b;
     return Value;
   }
   if(fabs(e) >= tol1 && fabs(fa) > fabs(fb)){
     s = fb / fa;
     if(a == c){
       p = 2.0 * xm * s;
       q = 1.0 - s;
     }
     else{
       q = fa / fc;
       r = fb / fc;
       p = s * (2.0 * xm * q * (q - r) - (b - a) * (r - 1.0));
       q = (q - 1.0) * (r - 1.0) * (s - 1.0);
     }
     if(p > 0.0) q = q * (-1.0);
     p = fabs(p);
     double minValue = (3.0 * xm * q - fabs(tol1 * q)) < fabs(e * q) ? (3.0 * xm * q - fabs(tol1 * q)) : fabs(e * q);
     if((2.0 * p) < minValue){
       e = d;
       d = p / q;
     }
     else{
       d = xm;
       e = d;
     }
   }
   else{
     d = xm;
     e = d;
   }
   a = b;
   fa = fb;
   if(fabs(d) > tol1){
     b = b + d;
   }
   else{
     if(fabs(xm) < 1e-20) b = b + fabs(tol1);
     else b = b + fabs(tol1) * xm / fabs(xm);
   }
   fb = func(b);
 }

 cout<<"Warning: ZBRNT exceeding maximum iterations."<<endl;
 irt = 2;
 Value = b;

 return Value;
}

