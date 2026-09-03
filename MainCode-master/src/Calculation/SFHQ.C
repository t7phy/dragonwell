#include "Calculation/CalcDIS.h"

void CalcDIS::SetQQMuMQ(double Qin, double Muin, double MQin, int nflin, double alfaso2pi)
{
 SFHQ_QQ = Qin;
 SFHQ_Mu = Muin;
 SFHQ_MQ = MQin;
 SFHQ_nfl = nflin;
 SFHQ_asA3 = alfaso2pi;
 SFHQ_LL = log(SFHQ_MQ * SFHQ_MQ / SFHQ_Mu / SFHQ_Mu);
}

void CalcDIS::DefineFunctions_SFHQ()
{
 sf_C2Hg0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hg0 = HQcoef0(2, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(C2Hg0)) C2Hg0 = 0.0;
   //cout<<x<<"  "<<SFHQ_QQ<<"  "<<SFHQ_Mu<<"  "<<SFHQ_MQ<<endl;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hg0; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hg0;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2Hg0A = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hg0A = HQcoef0A(2, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(C2Hg0A)) C2Hg0A = 0.0;

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hg0A; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hg0A;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHg0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHg0 = HQcoef0(0, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(CLHg0)) CLHg0 = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHg0; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHg0;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHg0A = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHg0A = HQcoef0A(0, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(CLHg0A)) CLHg0A = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHg0A; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHg0A;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2Hg = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hg = HQcoef(2, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(C2Hg)) C2Hg = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hg; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hg;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHg = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHg = HQcoef(0, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(CLHg)) CLHg = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHg; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHg;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2Hq = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hq = HQhqlcoef(2, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(C2Hq)) C2Hq = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hq; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hq;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHq = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHq = HQhqlcoef(0, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(CLHq)) CLHq = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHq; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHq;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2HgL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hg = HQcoef(2, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(C2Hg)) C2Hg = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hg; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hg;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHgL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHg = HQcoef(0, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(CLHg)) CLHg = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHg; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHg;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2HqL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hq = HQhqlcoef(2, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(C2Hq)) C2Hq = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hq; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hq;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHqL0 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHq = HQhqlcoef(0, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(CLHq)) CLHq = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHq; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHq;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2HgL1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hg = HQcoef(2, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ) - HQcoef(2, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(C2Hg)) C2Hg = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hg; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hg;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHgL1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHg = HQcoef(0, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ) - HQcoef(0, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(CLHg)) CLHg = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHg; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHg;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2HqL1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double C2Hq = HQhqlcoef(2, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ) - HQhqlcoef(2, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(C2Hq)) C2Hq = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = C2Hq; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = C2Hq;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_CLHqL1 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double CLHq = HQhqlcoef(0, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ) - HQhqlcoef(0, x, SFHQ_QQ, SFHQ_MQ, SFHQ_MQ);
   if(!isfinite(CLHq)) CLHq = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = CLHq; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = CLHq;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 sf_C2Hg3A = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double tmp = xCahi(2, 0, 2, 1, SFHQ_nfl, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(tmp)) tmp = 0.0;

   /*cout << std::setprecision(17);
   cout << "y=" << y << " x=" << x
        << " (x==0.2? " << (x==0.2) << ") "
        << " dx=" << (x-0.2) << "\n";
   cout << std::hexfloat << "x(hex)=" << x << std::defaultfloat << "\n";

   cout<<y<<"  "<<SFHQ_nfl<<"  "<<x<<"  "<<SFHQ_QQ<<"  "<<SFHQ_Mu<<"  "<<SFHQ_MQ<<"  "<<tmp<<endl;
   cout<<0.199928<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199928,  1.3,  1.3,  1.3)<<endl;
   cout<<0.199992<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199992,  1.3,  1.3,  1.3)<<endl;
   cout<<0.199939<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199939,  1.3,  1.3,  1.3)<<endl;
   cout<<0.199981<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199981,  1.3,  1.3,  1.3)<<endl;
   cout<<0.199953<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199953,  1.3,  1.3,  1.3)<<endl;
   cout<<0.199967<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199967,  1.3,  1.3,  1.3)<<endl;
   cout<<0.199921<<"  "<<xCahi(2, 0, 2, 1, 4,  0.199921,  1.3,  1.3,  1.3)<<endl;
   cout<<0.200000<<"  "<<xCahi(2, 0, 2, 1, 4,  0.2,       1.3,  1.3,  1.3)<<endl;
*/
#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = tmp; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = tmp;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value;
#endif

   return Value;
 };

 sf_C2Hg3B = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double tmp = xCahi(2, 0, 2, 2, SFHQ_nfl, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(tmp)) tmp = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = tmp; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = tmp;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value;
#endif

   return Value;
 };

 sf_C2Hq3A = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double tmp = xCahi(2, 1, 2, 1, SFHQ_nfl, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(tmp)) tmp = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = tmp; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = tmp;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value;
#endif

   return Value;
 };

 sf_C2Hq3B = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

   double tmp = xCahi(2, 1, 2, 2, SFHQ_nfl, x, SFHQ_QQ, SFHQ_Mu, SFHQ_MQ);
   if(!isfinite(tmp)) tmp = 0.0;
   //print*,x, QQ, Mu, MQ

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = tmp; //learn from HOPPET C2
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = tmp;
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = 0.0;
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5 * 0.5 * 0.5; // (as/4pi)->(as/2pi), q+qb->q

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value;
#endif

   return Value;
 };

 sf_C2ZMNS2 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     double x1 = 1.0 - x;
     double DL1 = log(1.0 - x);
     Value = c2np2a0(x, SFHQ_nfl)
           + 128.0/9.0*DL1*DL1*DL1/x1
           + (-184.0/3.0 +(double)SFHQ_nfl*16.0/9.0)*DL1*DL1/x1
           + (-31.1052 -(double)SFHQ_nfl*232.0/27.0)*DL1/x1
           + (188.641 +(double)SFHQ_nfl*6.34888)/x1; // reg + plus
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = c2np2a0(x, SFHQ_nfl); // reg
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     double x1 = 1.0 - x;
     double DL1 = log(1.0 - x);
     Value = - ( 128.0/9.0*DL1*DL1*DL1/x1
                + (-184.0/3.0 +(double)SFHQ_nfl*16.0/9.0)*DL1*DL1/x1
                + (-31.1052 -(double)SFHQ_nfl*232.0/27.0)*DL1/x1
                + (188.641 +(double)SFHQ_nfl*6.34888)/x1); // - plus
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = -338.513 + 46.8531 * (double)SFHQ_nfl; // delta
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5; // (as/4pi)->(as/2pi)

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif
   //cout<<x<<"  "<<hoppet_cc_piece<<"  "<<Value<<endl;
   //if(!isfinite(Value)) Value = 0.0;

   return Value;
 };

 sf_CLZMNS2 = [&](double y, int hoppet_cc_piece){
   double Value = 0.0;
   double x = exp(-y);

#if defined(USE_HOPPET) && defined(USE_HOPPET_CXX)
   if(hoppet_cc_piece == hoppet::cc_REAL){
     Value = clnp2a(x, SFHQ_nfl); // reg + plus
   }
   else if(hoppet_cc_piece == hoppet::cc_REALVIRT){
     Value = clnp2a(x, SFHQ_nfl); // reg
   }
   else if(hoppet_cc_piece == hoppet::cc_VIRT){
     Value = 0.0;
   }
   else if(hoppet_cc_piece == hoppet::cc_DELTA){
     Value = -0.012; // delta
   }
   else{
     Value = 0.0;
   }

   Value = Value * 0.5 * 0.5; // (as/4pi)->(as/2pi)

// include marco's  Divide by 2, to match with the normalization of F_{long}
   Value = Value / 2.0;

   if(hoppet_cc_piece != hoppet::cc_DELTA) Value = Value * x;
#endif

   return Value;
 };

 isDefineFunctions_SFHQ = true;
}

