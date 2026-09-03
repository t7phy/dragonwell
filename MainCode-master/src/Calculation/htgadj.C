#include "Calculation/CalcDIS.h"

void CalcDIS::DatAdj(DataPoint &m_data)
{

}

void CalcDIS::HtgAdj(DataPoint &m_data)
{
 if(m_data.Jtgt <= 2 || m_data.Jtgt >= 10 || (m_data.LHtg == 2 && m_data.Jsfn == 3)){
   return;
 }

 double origindata = m_data.origindata;

 if(m_data.LHtg == 3){ // htg88
   double x = m_data.x;
   double x2 = x * x;
   double x4 = x2 * x2;
   double df2 = 1.18 - 4.02 * x + 24.35 * x2 - 61.5 * x2 * x + 72.61 * x4 - 32.35 * x4 * x;

   m_data.data = origindata * df2;
 }
 else if(m_data.LHtg == 4){ // htgSLC
   double d0 =  4.58558707e-01;
   double d1 =  1.62185596e+01;
   double d2 = -1.79392859e+02;
   double d3 =  1.04313998e+03;
   double d4 = -3.53408342e+03;
   double d5 =  7.17002801e+03;
   double d6 = -8.56431003e+03;
   double d7 =  5.54039709e+03;
   double d8 = -1.49318167e+03;

   double x = m_data.x;
   double x2 = x * x;
   double x4 = x2 * x2;
   double x8 = x4 * x4;

   double emc1;
   if(x >= 0.07){
     emc1 = d0 + d1 * x + d2 * x2 + d3 * x * x2 + d4 * x4
          + d5 * x4 * x + d6 * x4 * x2 + d7 * x4 * x2 * x + d8 * x8;
   }
   else{
     emc1 = 0.95 + (x - 0.045) * 1.9544;
   }

   m_data.data = origindata / emc1;
 }
 else if(m_data.LHtg == 5){ // htg665
   double x = m_data.x;
   double x2 = x * x;
   double x4 = x2 * x2;

   double rat;
   if(x >= 0.01){
     rat = 0.73 + 7.0 * x - 52.9 * x2 + 173.8 * x2 * x - 263.9 * x4 + 150.0 * x4 * x;
   }
   else{
     rat = 0.71 + 6.8 * x - 31.1 * x2;
   }

   m_data.data = origindata / rat;
 }
 else{ // htgNMC
   double x = m_data.x;
   double emc = 1.118 - 0.4199 * x - 0.3597 * exp(-22.88 * x) + 1.872 * pow(x, 11.27);

   m_data.data = origindata / emc;
 }
}

