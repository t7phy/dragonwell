#include "Calculation/CalcVBP.h"

void CalcVBP::GetPrediction(vector<double> &result)
{
 double Rerr = 1e-6;
 int N1 = 2;
 double xMs = 2.0;

 result.resize(m_datatable.size());

 for(int i = 0; i < result.size(); i++){
   m_vbpdata = m_datatable.at(i);

   m_vbpdata.Rs = m_vbpdata.Param.at(0);
   m_vbpdata.aMissEtMin = m_vbpdata.Param.at(2);

   int Isfn = m_vbpdata.Isfn;
   if(Isfn >= 1 && Isfn <= 4){
     m_vbpdata.IXsc = 2;
   }
   else if(Isfn == 0 || (Isfn >= -12 && Isfn <= -1)){
     m_vbpdata.IXsc = 1;
   }
   else{
     cout<<"Isfn value for data block IB illegal in ChiVbp! "<<Isfn<<endl;
   }

   if(Isfn == 1){
     ixfx = 1;
   }
   else{
     ixfx = 0;
   }

   if(Isfn == -3 || Isfn == -4){
     m_vbpdata.Q = m_vbpdata.Param.at(1);
   }
   else if(Isfn == -6){
     m_vbpdata.BR = m_vbpdata.Param.at(1);
   }
   else if(Isfn == -9){
     if(m_vbpdata.lob == -1){// W-
       m_vbpdata.Ibsn = 2;
     }
     else if(m_vbpdata.lob == 1){// W+
       m_vbpdata.Ibsn = 3;
     }
     else if(m_vbpdata.lob == 0){// Z0
       m_vbpdata.Ibsn = 4;
       double st_cut = 2.0 * m_vbpdata.Ptmin / vBnMas(m_vbpdata.Ibsn);
       m_vbpdata.ct_cut = sqrt(1.0 - st_cut * st_cut);
     }
     else if(m_vbpdata.lob == 2){// W-lep asy
       m_vbpdata.Ibsn = 3;
       m_vbpdata.BR = 0.0;
     }
     m_vbpdata.Q = vBnMas(m_vbpdata.Ibsn);
   }

   // pn12  Initialize kinematics and common blocks
   m_vbpdata.tau = m_vbpdata.Q / m_vbpdata.Rs;
   m_vbpdata.ss = m_vbpdata.Rs * m_vbpdata.Rs;

   //pn12  Set kinematical common blocks for the VBP module; must be done 
   //      at this place to get correct scales, etc.
   //      Notice that, we got tgt/bem stuck in an unnatural order,
   //      for unknown historical reasons
   SetVBPVar(m_vbpdata.Rs, m_vbpdata.Q, m_vbpdata.Q, Rerr);
   KineLmt(m_vbpdata.ss, m_vbpdata.Q, xMs, m_vbpdata.yMx, m_vbpdata.ptMx);

                                  // Kinematics independent factors; N1 is set as 2
   double Fac0, Fac01;
   map<int, double> Fac1;
   XsFact(m_vbpdata.IXsc, m_vbpdata.Ibsn, Fac0, Fac01, Fac1, N1);
   //                          -----  Preliminaries for theoretical calculation
   //                                           X-section in nb - GeV**2
   double Xsec0 = 0.38937966 * 1e6;
                                    //  These factors are to match the X-sect
                                    //  returned by VBPDY (s*dsig/dy) below
                                    //  to measured cross-sections
   double Scle = 0.0;
   if(m_vbpdata.IXsc == 1){ // For VBP, this leads to s * d sig/ dy
     Scle = 1.0;
   }
   else if(m_vbpdata.IXsc == 2){ // For LPP, his leads to  Q**3 *d sig/dy d Q
     Scle = 2.0 * pow(m_vbpdata.tau, 2.0);
   }

   m_vbpdata.Xsec[1] = Xsec0 * Scle * Fac0;
   m_vbpdata.Xsec[2] = Xsec0 * Scle * Fac1[1];

   //                                                ---- Always calculate LO
   //                                            Set hard-cross-section calculation to LO
   m_vbpdata.iOrdr = 1;
   m_datatable.at(i).iOrdr = 1;             // CalculateVbp will return Born 
   m_datatable.at(i).theory_lo = CalculateVbp();
   double FitDt = 0.0;

   int NLO = 2;
   if(NLO >= 2){    // compute the one-loop or two-loop correction explicitly
     if(m_vbpdata.Isfn == -9 && m_vbpdata.lob != 2){
       FitDt = m_datatable.at(i).theory_lo;
     }
     else if(m_vbpdata.Isfn == -3){ // W asymmetry
       m_vbpdata.iOrdr = 2;
       m_datatable.at(i).iOrdr = 2;
       FitDt = CalculateVbp();
     }
     else if(m_vbpdata.Isfn == 4){ // yfu 2025.10.26 use two kfactors for neutron and proton
       m_vbpdata.iOrdr = 2;
       m_datatable.at(i).iOrdr = 2;
       FitDt = m_datatable.at(i).theory_lo; 
       if(!m_datatable.at(i).isUseKFactor || fabs(m_datatable.at(i).wp_kfac_internal) > 1e10 || fabs(m_datatable.at(i).wm_kfac_internal) > 1e10){
         FitDt = CalculateVbp();
         m_datatable.at(i).isUseKFactor = true;
         m_datatable.at(i).wp_kfac_internal = m_vbpdata.wp_kfac_internal;
         m_datatable.at(i).wm_kfac_internal = m_vbpdata.wm_kfac_internal;
       }
     }
     else{
       if(!m_datatable.at(i).isUseKFactor || fabs(m_datatable.at(i).kfactor_HighOrder) > 1e10){
         m_vbpdata.iOrdr = 2;
         m_datatable.at(i).iOrdr = 2;         // CalculateVbp will return (N)NLO
         m_datatable.at(i).theory_nnlo = CalculateVbp();
         m_datatable.at(i).kfactor_HighOrder = m_datatable.at(i).theory_nnlo / m_datatable.at(i).theory_lo;
         m_datatable.at(i).isUseKFactor = true;
       }

       FitDt = m_datatable.at(i).theory_lo * m_datatable.at(i).kfactor_HighOrder;
     }               // isfn == -9 .and. lob /= 2
   }                 // NLO >= 2

   result.at(i) = FitDt;
   //cout<<i<<"  "<<result.at(i)<<"  "<<m_datatable.at(i).theory_lo<<endl;
   //cout<<"i = "<<i<<" result = "<<result.at(i)<<" Born = "<<m_datatable.at(i).theory_lo<<" Data = "<<m_vbpdata.data<<endl;
 }
}

void CalcVBP::InitializeData(Config setting, vector<DataPoint> DataTable)
{
 for(int i = 0; i < DataTable.size(); i++){
   DataTable.at(i).K_f = setting.LVbp.at(0);
   DataTable.at(i).Iscl = (int)(setting.ThVbp.at(0));
   DataTable.at(i).Isch = setting.Isch;
   DataTable.at(i).IorHrd = setting.IorHrd;
 }

 this->CP = setting.CP;

 m_datatable = DataTable;
}

double CalcVBP::CalculateVbp()
{
 double Result = 0.0;
 SetVBPPar(m_vbpdata.Ibem, m_vbpdata.Itgt, m_vbpdata.Ibsn, m_vbpdata.iOrdr, m_vbpdata.Isch, m_vbpdata.Iscl);

 if(m_vbpdata.Isfn == -9){               // marco12 Combined W/Z sample
   if(m_vbpdata.lob == -1 || m_vbpdata.lob == 1){  // LO W- or W+ cross section
     WlepY(m_vbpdata.Ibsn, m_vbpdata.Ibem, m_vbpdata.Itgt, m_vbpdata.Rs, m_vbpdata.y, m_vbpdata.Ptmin, Result);
   }
   else if(m_vbpdata.lob == 0){                    // Z0 cross section
     double WxFac = 1e3 / m_vbpdata.ss * m_vbpdata.BR;
     Result = WxFac * m_vbpdata.Xsec[m_vbpdata.iOrdr] * VBPdy1(m_vbpdata.y);
// The cut on the PTmin of decay leptons implies a reduction rate by
//cpy              Result = Result*(3.0*ct_cut/4.0)*(1.0+ct_cut**2/3.0) 
     double Cut_eff = (3.0*m_vbpdata.ct_cut/4.0)*(1.0+pow(m_vbpdata.ct_cut, 2.0)/3.0);
     Result = Result*Cut_eff;
   }
   else if(m_vbpdata.lob == 2){                    // W charge asymmetry
     double PtEtMin = m_vbpdata.Ptmin > m_vbpdata.aMissEtMin ? m_vbpdata.Ptmin : m_vbpdata.aMissEtMin; // at LO, the lowest pTe
                   // constraint arises either from PTmin or Missing ET min
     WlepAsymK(m_vbpdata.iOrdr, m_vbpdata.Ibsn, m_vbpdata.Ibem, m_vbpdata.Itgt,
               m_vbpdata.Rs, m_vbpdata.y, PtEtMin, m_vbpdata.Ptmax, m_vbpdata.wp_kfac, m_vbpdata.wm_kfac, Result);
   }
   else{
     cout<<"Wrong lob in CalculateVbp"<<endl;
     return 0.0;
   }
 }
 else if(m_vbpdata.Isfn == -5){
// W-production (W+ or W-) Xsections (nb) in Y bins
   double WxFac = 1.0 / m_vbpdata.ss;
   Result = WxFac * m_vbpdata.Xsec[m_vbpdata.iOrdr] * Wprodint(m_vbpdata.Ymin, m_vbpdata.Ymax);
 }
 else if(m_vbpdata.Isfn == -6){
// W/Z-production Xsections (pb) in dsig/dy with branching ratio BR
   double WxFac = 1e3 / m_vbpdata.ss * m_vbpdata.BR;
   Result = WxFac * m_vbpdata.Xsec[m_vbpdata.iOrdr] * VBPdy1(m_vbpdata.y);
 }
 else if(m_vbpdata.Isfn == -3){
// W-lepton asymmetry
// Lai 3/27/97, 9/19/97, 6/25/04, 
// Lai 9/6/04 (replace LSW2 by LswEx(IB)) ,2/5/09
// Lai 1/5/10: K-fac determined by RS
// Ird=3: ReSum K-Fac (CTEQ6.6M) for RUN-1
// Ird=5: ReSum K-Fac (CTEQ6.6M) for RUN-2
   WlepAsymK(m_vbpdata.iOrdr, m_vbpdata.Ibsn, m_vbpdata.Ibem, m_vbpdata.Itgt,
             m_vbpdata.Rs, m_vbpdata.y, m_vbpdata.Ptmin, m_vbpdata.Ptmax, m_vbpdata.wp_kfac, m_vbpdata.wm_kfac, Result);
 }
 else if(m_vbpdata.Isfn == -4){
//  W-asymmetry, CP-even case: sigma(W+, y) = sigma(W-, -y)
//CPY This only holds for p-pbar collider (Tevatron), not for pp-collider (LHC) 

//CPY May 2015: 
//     Boson label: (IBN)   1,   2,   3,   4
//                       gamma   W+   W-   Z    

// yfu: all the data information are retrieved from Dataset.C
//   if(IorHrd==2) then
//      wp_kfac = ExDat( 7, Ipt)
//      wm_kfac = ExDat(8, Ipt)
//   else if (IorHrd==3) then
//      wp_kfac = ExDat( 9, Ipt)
//      wm_kfac = ExDat(10, Ipt)
//   endif

// This is for IBN=3 (W^-)
   double DSY2 = VBPdy1(m_vbpdata.y);
   DSY2 = DSY2 * m_vbpdata.wm_kfac;
   double DSY22 = VBPdy1(m_vbpdata.y * (-1.0));
   DSY22 = DSY22 * m_vbpdata.wp_kfac;

   Result = (DSY22 - DSY2) / (DSY22 + DSY2);
 }
 else if(m_vbpdata.Isfn == 3 || m_vbpdata.Isfn == 4){
// neutron
   int ihdn = 0;
   SetVBPPar(m_vbpdata.Ibem, ihdn, m_vbpdata.Ibsn, m_vbpdata.iOrdr, m_vbpdata.Isch, m_vbpdata.Iscl);
   double DsN = VBPdy1(m_vbpdata.y);
// proton
   ihdn = 1;
   SetVBPPar(m_vbpdata.Ibem, ihdn, m_vbpdata.Ibsn, m_vbpdata.iOrdr, m_vbpdata.Isch, m_vbpdata.Iscl);
   double DsP = VBPdy1(m_vbpdata.y);

   if(m_vbpdata.Isfn == 3){      // NA51
     Result = (DsP - DsN) / (DsP + DsN);
   }
   else{
     //cout<<DsN<<"  "<<DsP<<"  "<<m_vbpdata.wp_kfac<<"  "<<m_vbpdata.wm_kfac<<endl;
     if(m_vbpdata.iOrdr == 1){
       m_vbpdata.wp_lo = DsN;
       m_vbpdata.wm_lo = DsP;
     }
     else{
       m_vbpdata.wp_nlo = DsN;
       m_vbpdata.wm_nlo = DsP;
       m_vbpdata.wp_kfac_internal = m_vbpdata.wp_nlo / m_vbpdata.wp_lo;
       m_vbpdata.wm_kfac_internal = m_vbpdata.wm_nlo / m_vbpdata.wm_lo;
     }

     //cout<<DsN<<"  "<<DsP<<"  "<<m_vbpdata.wp_lo<<"  "<<m_vbpdata.wm_lo<<"  "<<m_vbpdata.wp_kfac_internal<<"  "<<m_vbpdata.wm_kfac_internal<<endl;

     DsN = m_vbpdata.wp_lo * m_vbpdata.wp_kfac_internal;
     DsP = m_vbpdata.wm_lo * m_vbpdata.wm_kfac_internal;

     DsN = DsN * m_vbpdata.wp_kfac; // yfu 2025.10.26 use two kfactors for neutron and proton
     DsP = DsP * m_vbpdata.wm_kfac;
     Result = (DsN + DsP) / DsP / 2.0;
   }

   //cout<<"  "<<m_vbpdata.iOrdr<<"   "<<DsN<<"   "<<DsP;
   //if(m_vbpdata.iOrdr == 2) cout<<endl;
 }
 else{
   Result = m_vbpdata.Xsec[m_vbpdata.iOrdr] * VBPdy1(m_vbpdata.y);
 }

 return Result;
}

double CalcVBP::Wprodint(double Y1, double Y2)
{
 double ERREST;
 int IER;

//CPY CHECK THE ALLOWED KINEMATICAL RANGE OF RAPIDITY

 auto ACOSH = [&](double x){
   return log(x + sqrt(x*x - 1.0));
 };

 auto Ymaximum = [&](double ECM, double Q_V, double QT_V){
   double T1 = ECM * ECM + Q_V * Q_V;
   double T2 = sqrt(QT_V * QT_V + Q_V * Q_V);
   double T3 = 2.0 * ECM * T2;
   return ACOSH(T1/T3);
 };

 double Y_MAX =  Ymaximum(m_vbpdata.Rs, m_vbpdata.Q, 0.0);
 double Y_MIN = -Y_MAX;
 if(Y1 < Y_MIN) Y1 = Y_MIN;
 if(Y2 > Y_MAX) Y2 = Y_MAX;

 function<double(double)> fun_vbpdy1 = bind(&CalcVBP::VBPdy1, this, _1);

 double Value = SMPSN1(fun_vbpdy1, Y1, Y2, 256, ERREST, IER);

 return Value;
}
