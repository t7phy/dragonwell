#include "RootCommon.h"
#include "Tools/Tools.h"

void Decomposition(vector<double> DATA, TMatrixD input)
{
 int MatrixRank = input.GetNcols();
 cout<<"Rank: "<<MatrixRank<<endl;

 TDecompSVD DecompM(input);
 TMatrixD U = DecompM.GetU();
 TVectorD S = DecompM.GetSig();
 TMatrixD V = DecompM.GetV();

 TMatrixD FinalBeta(MatrixRank, MatrixRank);
 TMatrixD CovarianceBeta(MatrixRank, MatrixRank);

 S.Print();

 TMatrixD SigmSqrt(MatrixRank, MatrixRank);
 for(int i = 0;  i < MatrixRank; i++){
   SigmSqrt[i][i] = sqrt(S[i]);
 }
 TMatrixD BT = U * SigmSqrt;

 cout << "================================================================"<< endl;
 cout << "###Decomposed result from Covariance matix for nuisance form [For ePump ErrorType 1 or 4]" << endl;
 cout << "###First use error type 4 to check decomposed result then back to error type 1 do updating[use same notation as fitting code]" << endl;

 for(int j = 0; j < MatrixRank; j++){
   for(int i = 0;  i < MatrixRank; i++){
      FinalBeta[j][i] = BT[j][i];
      printf("% -18.8G", BT[j][i] / DATA[j] * 100);
   }
   std::cout << std::endl;
 }

 cout<<"Real Beta:"<<endl;
 for(int j = 0; j < MatrixRank; j++){
   for(int i = 0;  i < MatrixRank; i++){
      cout << BT[j][i] << "  ";
   }
   std::cout << std::endl;
 }

 cout <<"================================================================"<< endl;
 cout << "###Correlation coefficient form [For ePump ErrorType 2] "<< endl;
 cout << "   #a              #b             CorrCoeff" << endl;

 for(int j = 0; j < MatrixRank; j++){
   for(int i = j; i < MatrixRank; i++){
     printf("   %-14d   %-14d% -18.8G\n",i + 1, j + 1, input[i][j] / sqrt(input[i][i]) / sqrt(input[j][j]));
   }
 }

 cout <<"================================================================"<< endl;
 cout <<"###Inverse Covariance Matrix form [For ePump ErrorType 3]" << endl;
 cout <<"Inverse Covariance Matrix:" << endl;
// TMatrixD InverseCovMatrix = CovMatrix;

// InverseCovMatrix.Invert();
// for(int i = 0; i < MatrixRank; i++){
//   cout <<"a=     "<< i + 1 << ",        b=      " << i + 1 <<",  "<<MatrixRank << endl;
//   for(int j = i; j < MatrixRank; j++){
//     printf("% -18.8G", InverseCovMatrix[j][i]);
//   }
//   cout << endl;
// }

 cout <<"================================================================"<< endl;
 cout <<"###Square sum of the Decomposed result. This should be equal total correlated SysError[For no unceorr syserror Case]" << endl;

 for(int j = 0; j < MatrixRank; j++){
   double sum = 0.0;
   for(int i = 0; i < MatrixRank; i++){
     sum += BT[j][i] * BT[j][i];
   }
   printf("% -18.8G\n", sqrt(sum));
 }

 TMatrixD BT_T = BT;
 BT_T = BT_T.Transpose(BT_T);

 TMatrixD Final = BT * BT_T;

 for(int i = 0; i < MatrixRank; i++){
   for(int j = 0; j < MatrixRank; j++){
     for(int k = 0; k < MatrixRank; k++){
       CovarianceBeta[i][j] += FinalBeta[i][k] * FinalBeta[j][k];
     }
   }
 }

 cout<<"Beta Covariance:"<<endl;
 for(int i = 0; i < MatrixRank; i++){
   for(int j = 0; j < MatrixRank; j++){
     cout<<CovarianceBeta[i][j]<<"  ";
   }
   cout<<endl;
 }

}

