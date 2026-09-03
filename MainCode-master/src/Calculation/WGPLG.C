#include "Calculation/CTUtil.h"

std::complex<double> CTUtil::WGPLG(int N, int M, double X)
{
 int IT,M1,N1,IX,NB;

 std::complex<double> Value;

 std::complex<double> Z,I,SK,SJ;

 FortranArray1D<std::complex<double>> V{0, 5};

 FortranArray1D<double> FCT{0, 4};
 FortranArray1D<double> SGN{0, 4};
 FortranArray1D<double> U{0, 4};
 FortranArray1D<int> NC{1, 10};
 FortranArray1D<int> INDEX{1, 31};

 I = std::complex<double>(0.0, 1.0);

 double Z0 = 0.0;
 double Z1 = 1.0;
 double HF = 0.5;
 double C1 = 4.0 / 3.0;
 double C2 = 1.0 / 3.0;

 FCT(0) = 1.0;
 FCT(1) = 1.0;
 FCT(2) = 2.0;
 FCT(3) = 6.0;
 FCT(4) = 24.0;

 SGN(0) = 1.0;
 SGN(1) = -1.0;
 SGN(2) = 1.0;
 SGN(3) = -1.0;
 SGN(4) = 1.0;

 INDEX(1) = 1;
 INDEX(2) = 2;
 INDEX(3) = 3;
 INDEX(4) = 4;
 for(int i = 5; i <= 10; i++) INDEX(i) = 0;
 INDEX(11) = 5;
 INDEX(12) = 6;
 INDEX(13) = 7;
 for(int i = 14; i <= 20; i++) INDEX(i) = 0;
 INDEX(21) = 8;
 INDEX(22) = 9;
 for(int i = 23; i <= 30; i++) INDEX(i) = 0;
 INDEX(31) = 10;

 NC(1) = 24;
 NC(2) = 26;
 NC(3) = 28;
 NC(4) = 30;
 NC(5) = 22;
 NC(6) = 24;
 NC(7) = 26;
 NC(8) = 19;
 NC(9) = 22;
 NC(10) = 17;

 if(N < 1 || N > 4 || M < 1 || M > 4 || (N+M) > 5){
   Z = 0.0;
   cout<<"ERROR! in WGPLG."<<endl; 
 }
 else if(X == 1){
   Z = m_WGPLG_const.S1(N,M);
 }
 else if(X > 2.0 || X < -1.0){
   double X1 = 1.0 / X;
   double H = C1 * X1 + C2;
   double ALFA = H + H;
   V(0) = 1.0;
   V(1) = log(-X + I*Z0);
   for(int L = 2; L <= N + M; L++){
     V(L) = V(1) * V(L-1) / (double)L;
   }
   SK = 0.0;
   for(int K = 0; K <= M - 1; K++){
     M1 = M - K;
     double R = pow(X1, M1) / (FCT(M1) * FCT(N-1));
     SJ = 0;
     for(int J = 0; J <= K; J++){
       N1 = N + K - J;
       int L = INDEX(10 * N1 + M1 - 10);
       double B1 = 0.0;
       double B2 = 0.0;
       double B0 = 0.0;
       for(int IT = NC(L); IT >= 0; IT--){
         B0 = m_WGPLG_const.A(IT,L) + ALFA * B1 - B2;
         B2 = B1;
         B1 = B0;
       }
       double Q = (FCT(N1-1) / FCT(K-J)) * (B0 - H * B2) * R / (double)pow(M1, N1);
       SJ = SJ + V(J) * Q;
     }
     SK = SK + SGN(K) * SJ;
   }
   SJ = 0.0;
   for(int J = 0; J <= N - 1; J++){
     SJ = SJ + V(J) * m_WGPLG_const.C(N-J,M);
   }
   Z = SGN(N) * SK + SGN(M) * (SJ + V(N+M));
 }
 else if(X > HF){
   double X1 = 1.0 - X;
   double H = C1 * X1 + C2;
   double ALFA = H + H;
   V(0) = 1.0;
   U(0) = 1.0;
   V(1) = log(X1 + I * Z0);
   U(1) = log(X);
   for(int L = 2; L <= M; L++){
     V(L) = V(1) * V(L-1) / (double)L;
   }
   for(int L = 2; L <= N; L++){
     U(L) = U(1) * U(L-1) / (double)L;
   }
   SK = 0.0;
   for(int K = 0; K <= N - 1; K++){
     M1 = N - K;
     double R = pow(X1, M1) / FCT(M1);
     SJ = 0.0;
     for(int J = 0; J <= M - 1; J++){
       N1 = M - J;
       int L = INDEX(10 * N1 + M1 - 10);
       double B1 = 0.0;
       double B2 = 0.0;
       double B0 = 0.0;
       for(int IT = NC(L); IT >= 0; IT--){
         B0 = m_WGPLG_const.A(IT,L) + ALFA * B1 - B2;
         B2 = B1;
         B1 = B0;
       }
       double Q = SGN(J) * (B0 - H * B2) * R / (double)pow(M1, N1);
       SJ = SJ + V(J) * Q;
     }
     SK = SK + U(K) * (m_WGPLG_const.S1(M1,M) - SJ);
   }
   Z = SK + SGN(M) * U(N) * V(M);
 }
 else{
   int L = INDEX(10 * N + M - 10);
   double H = C1 * X + C2;
   double ALFA = H + H;
   double B1 = 0.0;
   double B2 = 0.0;
   double B0 = 0.0;
   for(int IT = NC(L); IT >= 0; IT--){
     B0 = m_WGPLG_const.A(IT,L) + ALFA * B1 - B2;
     B2 = B1;
     B1 = B0;
   }
   Z = (B0 - H * B2) * pow(X, M) / (FCT(M) * (double)pow(M, N));
 }

 Value = Z;

 return Value;
}
