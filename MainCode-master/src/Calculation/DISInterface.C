#include "Calculation/CalcDIS.h"

static pthread_mutex_t hoppet_mtx = PTHREAD_MUTEX_INITIALIZER;

void CalcDIS::GetPrediction(vector<double> &result)
{
#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
 if(doCalcN3LODIS) CloneHoppetSF();
#endif

 result.resize(m_datatable.size());

 for(int i = 0; i < result.size(); i++){
// for(int i = 160; i < 161; i++){
// for(int i = 81; i < 82; i++){
// for(int i = 0; i < 1; i++){
   //if(i != 0) continue;

   if(m_datatable.at(i).LdatAdj >= 1) DatAdj(m_datatable.at(i));
   if(m_datatable.at(i).LHtg >= 1) HtgAdj(m_datatable.at(i));

   m_disdata = m_datatable.at(i);

   m_disdata.jBn = m_disdata.Jbsn;
   m_disdata.jHd = m_disdata.Jtgt;
   m_disdata.iLptn1 = m_disdata.JBem;

   this->iOrdr  = m_disdata.iOrdr;
   this->iSchm  = m_disdata.iSchm;
   //this->Q0     = m_disdata.Q0;
   this->ScalFc = m_disdata.ScalFc;
   this->achi   = m_disdata.achi;

   if(m_disdata.Jsfn == -1){
     if(m_datatable.at(i).lob == 1){
       m_disdata.jPrc = 2;
     }
     else if(m_datatable.at(i).lob == 2){
       m_disdata.jPrc = 2;
       m_disdata.jHd = 2;
     }
     else{
       cout<<" No Such value of lob; inside chidis.F "<<endl;
     }
   }
   else if(m_disdata.Jsfn == -2){
     if(m_datatable.at(i).lob == 1){
       m_disdata.jPrc = 2;
     }
     else if(m_datatable.at(i).lob == 2){
       m_disdata.jPrc = 3;
       m_disdata.jHd = -1;
     }
     else{
       cout<<" No Such value of lob; inside chidis.F "<<endl;
     }
   }
   else if(m_disdata.Jsfn == -3){
     if(m_datatable.at(i).lob == 1){
       m_disdata.jPrc = 2;
     }
     else if(m_datatable.at(i).lob == 2){
       m_disdata.jPrc = 3;
       m_disdata.jHd = -1;
     }
     else{
       cout<<" No Such value of lob; inside chidis.F "<<endl;
     }
   }
   else{
     m_disdata.jPrc = m_disdata.Jsfn;
   }

   m_disdata.kProc = m_disdata.jPrc / 10; // First digit of process-switch
   if(m_disdata.kProc == 0){
     m_disdata.jSf = m_disdata.jPrc; // Total-incl. SFs
     m_disdata.iCmptn = m_disdata.jBn;
     m_disdata.iFSflv = 0;
   }
   else if(m_disdata.kProc == 1){
     m_disdata.jSf = m_disdata.jPrc % 10; // Semi-incl. SFs  with final heavy quark
     m_disdata.iCmptn = m_disdata.jBn;
     m_disdata.iFSflv = (int)(m_disdata.Param.at(0)); // Param(1) identifies the Flavor tag
   }
   else if(m_disdata.kProc == 2){
     m_disdata.jXs = m_disdata.jPrc % 10; // Total Incl. cross section measurement
     if(m_disdata.jXs != 5){
       m_disdata.iLptn1 = (int)(m_disdata.Param.at(0));
       m_disdata.iLptn2 = (int)(m_disdata.Param.at(1));
       m_disdata.CombinedProcesses = false; // separate data sets for each scattering process
     }
     else{
       m_disdata.jXs = 0; // reset for reduced Xsec
       m_disdata.CombinedProcesses = true; // combined data set for several scattering processes
     }// jXs.ne.5
     m_disdata.iFSflv = 0;
   }
   else if(m_disdata.kProc == 3){
     m_disdata.jXs = m_disdata.jPrc % 10;        // Semi-incl. xSec. with final heavy quark
     m_disdata.iLptn1 = (int)(m_disdata.Param.at(0));
     m_disdata.iLptn2 = (int)(m_disdata.Param.at(1));
     m_disdata.iFSflv = (int)(m_disdata.Param.at(2));  // Param(3) identifies the Flavor tag
   }

   CheckFlv(m_disdata.iFSflv);

   m_disdata.x = m_datatable.at(i).x;
   m_disdata.Q = sqrt(m_datatable.at(i).Q2);
   if(m_disdata.kProc == 2 || m_disdata.kProc == 3) m_disdata.y = m_datatable.at(i).y;
   if(m_disdata.kProc == 2 && m_disdata.CombinedProcesses){
     int lio = m_datatable.at(i).lob;
     m_disdata.iLptn1 = lio / 10;
     m_disdata.iLptn2 = (abs(lio) % 10) * lio / abs(lio);
   }

   this->iOrdr  = 0;
   m_datatable.at(i).theory_lo = CalculateDis();

   if(!m_datatable.at(i).isUseKFactor || fabs(m_datatable.at(i).kfactor_HighOrder) > 1e10){
     this->iOrdr = m_datatable.at(i).iOrdr;
     m_datatable.at(i).theory_nnlo = CalculateDis();
     m_datatable.at(i).kfactor_HighOrder = m_datatable.at(i).theory_nnlo / m_datatable.at(i).theory_lo;
     m_datatable.at(i).isUseKFactor = true;
   }

   //if(m_datatable.at(i).subType == "CcfrNbChXN" && i == 0){
   //  cout<<m_disdata.x<<"  "<<m_disdata.Q<<"  "<<m_disdata.y<<"  "<<m_disdata.iLptn1<<"  "<<m_disdata.iLptn2<<"  "<<m_disdata.jHd<<"  "<<m_disdata.iFSflv<<"  "<<m_disdata.jXs<<endl;
   //  cout<<i<<"  "<<m_datatable.at(i).theory_lo<<"  "<<m_datatable.at(i).theory_nnlo<<endl;
   //}


   double FitDt = m_datatable.at(i).theory_lo * m_datatable.at(i).kfactor_HighOrder;

   //double FitDt = CalculateDis();

   result.at(i) = FitDt;
   //cout<<"i = "<<i<<" result = "<<result.at(i)<<endl;
 }



}

void CalcDIS::InitializeData(Config setting, vector<DataPoint> DataTable)
{
 for(int i = 0; i < DataTable.size(); i++){
   DataTable.at(i).K_f = setting.LDis.at(0);
   DataTable.at(i).iSchm = setting.LDis.at(2);

   DataTable.at(i).LdatAdj = setting.LDis.at(1) / 10 % 10;
   DataTable.at(i).LHtg = setting.LDis.at(1) % 10;
  
   DataTable.at(i).ScalFc = setting.ThDis.at(0);
   DataTable.at(i).achi = setting.ThDis.at(1);
  
   DataTable.at(i).IorHrd = setting.IorHrd;
   DataTable.at(i).iOrdr = setting.IorHrd - 1;
 }

 this->CP = setting.CP;

 m_datatable = DataTable;
}

double CalcDIS::CalculateDis()
{
 double Result;
 if(m_disdata.kProc == 2 || m_disdata.kProc == 3){ // Return the Reduced Xsection
   if(!doCalcN3LODIS){
     Result = xSecLh(m_disdata.iLptn1, m_disdata.iLptn2, m_disdata.jHd, m_disdata.x, m_disdata.Q, m_disdata.y, m_disdata.iFSflv, m_disdata.jXs);
   }
   else{
     Result = xSecLh_N3LO(m_disdata.iLptn1, m_disdata.iLptn2, m_disdata.jHd, m_disdata.x, m_disdata.Q, m_disdata.y, m_disdata.iFSflv, m_disdata.jXs);
   }
 }
 else{             // Return a structure function or ratio
   double Prefactor;
   if(m_disdata.jSf == 0){// CalculateDIS returns F_L = F_2 - 2*x*F_1.
                          // StrFnGm returns F_{long} = F_2/(2*x) - F_1.
                          // Prefactor = F_L/F_{long}
     Prefactor = 2.0 * m_disdata.x;
   }
   else{        // For i=1,2,3 StrFnGm returns F_i/x
     Prefactor = m_disdata.x;
   }

   double sfp, sfn;
   if(m_disdata.jHd < 10){         // (SI)DIS on n(0), p(1), D(2), Cu(3), Fe(5)
     if(!doCalcN3LODIS){
       Result = StrFnGm(m_disdata.jHd, m_disdata.iCmptn, m_disdata.x, m_disdata.Q, m_disdata.jSf, m_disdata.iFSflv) * Prefactor;
     }
     else{
       Result = StrFnGm_N3LO(m_disdata.jHd, m_disdata.iCmptn, m_disdata.x, m_disdata.Q, m_disdata.jSf, m_disdata.iFSflv) * Prefactor;
     }
   }
   else if(m_disdata.jHd < 13){    // Combinations of SF's on p and n
     if(!doCalcN3LODIS){
       sfp = StrFnGm(1, m_disdata.iCmptn, m_disdata.x, m_disdata.Q, m_disdata.jSf, m_disdata.iFSflv) * Prefactor;
       sfn = StrFnGm(0, m_disdata.iCmptn, m_disdata.x, m_disdata.Q, m_disdata.jSf, m_disdata.iFSflv) * Prefactor;
     }
     else{
       sfp = StrFnGm_N3LO(1, m_disdata.iCmptn, m_disdata.x, m_disdata.Q, m_disdata.jSf, m_disdata.iFSflv) * Prefactor;
       sfn = StrFnGm_N3LO(0, m_disdata.iCmptn, m_disdata.x, m_disdata.Q, m_disdata.jSf, m_disdata.iFSflv) * Prefactor;
     }
     if(m_disdata.jHd == 10){      // Ratio : n/p
       Result = sfn / sfp;
     }
     else if(m_disdata.jHd == 11){ // Diff : p - n
       Result = sfp - sfn;
     }
     else if(m_disdata.jHd == 12){ // Ratio : "d"/2p
       Result = (sfn + sfp) / sfp / 2.0;
     }
   }
 }

 return Result;
}

void CalcDIS::CheckFlv(int iflv)
{
 if(iflv == 0 || (iflv >= -6 && iflv <= -4) || (iflv >= 4 && iflv <= 6) || (iflv >= 14 && iflv <= 16)){
   return;
 }
 else{
   cout<<"ChiDis: iflv read from data file = "<<iflv<<" is invalid!"<<endl;
   return;
 }
}
