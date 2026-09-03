#ifndef InverseMatrix_cxx
#define InverseMatrix_cxx

#include "Tools/Tools.h"

using namespace std;

void RowExchange(int i, int j, TH2D* &Matrix)
{
 for(int k = 0; k < Matrix->GetNbinsX(); k++){
   double Element1 = Matrix->GetBinContent(i + 1, k + 1);
   double Element2 = Matrix->GetBinContent(j + 1, k + 1);
   Matrix->SetBinContent(i + 1, k + 1, Element2);
   Matrix->SetBinContent(j + 1, k + 1, Element1);
 }
}

void RowExchange(int i, int j, vector<vector<double>> &Matrix)
{
 for(int k = 0; k < Matrix.size(); k++){
   double Element1 = Matrix.at(i).at(k);
   double Element2 = Matrix.at(j).at(k);
   Matrix.at(i).at(k) = Element2;
   Matrix.at(j).at(k) = Element1;
 }
}

void RowTransform(int i, int j, double scale, TH2D* &Matrix)
{
 for(int k = 0; k < Matrix->GetNbinsX(); k++){
   double Element1 = Matrix->GetBinContent(i + 1, k + 1);
   double Element2 = Matrix->GetBinContent(j + 1, k + 1);
   Matrix->SetBinContent(i + 1, k + 1, Element1 + Element2 * scale);
 }
}

void RowTransform(int i, int j, double scale, vector<vector<double>> &Matrix)
{
 for(int k = 0; k < Matrix.size(); k++){
   double Element1 = Matrix.at(i).at(k);
   double Element2 = Matrix.at(j).at(k);
   Matrix.at(i).at(k) = Element1 + Element2 * scale;
 }
}

void RowScale(int i, double scale, TH2D* &Matrix)
{
 for(int k = 0; k < Matrix->GetNbinsX(); k++){
   double Element1 = Matrix->GetBinContent(i + 1, k + 1);
   Matrix->SetBinContent(i + 1, k + 1, Element1 * scale);
 }
}

void RowScale(int i, double scale, vector<vector<double>> &Matrix)
{
 for(int k = 0; k < Matrix.size(); k++){
   double Element1 = Matrix.at(i).at(k);
   Matrix.at(i).at(k) = Element1 * scale;
 }
}

void CalculateInverseMatrix(TH2D* Matrix, TH2D* &InverseMatrix)
{
 bool isOutput = false;
 if(isOutput) std::cout<<"Start to calculate inverse matrix."<<std::endl;

 if(!InverseMatrix) InverseMatrix = (TH2D *)Matrix->Clone("InverseMatrix");
 InverseMatrix->Reset();

 TH2D* OriginMatrix = (TH2D *)Matrix->Clone("OriginMatrix");

 if(isOutput){
   for(int i = 0; i < OriginMatrix->GetNbinsX(); i++){
     for(int j = 0; j < OriginMatrix->GetNbinsX(); j++){
       if(fabs(OriginMatrix->GetBinContent(i + 1, j + 1)) < 1e-10) cout<<0.0<<" ";
       else cout<<OriginMatrix->GetBinContent(i + 1, j + 1)<<" ";
     }
     cout<<endl;
   }
 }

 for(int i = 0; i < OriginMatrix->GetNbinsX(); i++){
   for(int j = 0; j < OriginMatrix->GetNbinsX(); j++){
     if(i == j) InverseMatrix->SetBinContent(i + 1, j + 1, 1.0);
     if(i != j) InverseMatrix->SetBinContent(i + 1, j + 1, 0.0);
   }
 }

 for(int i = 0; i < OriginMatrix->GetNbinsX(); i++){//index i is the diagnal term
   int diag = i;
   while(fabs(OriginMatrix->GetBinContent(diag + 1, i + 1)) < 1e-10){
     diag++;
   }
   RowExchange(i, diag, OriginMatrix);
   RowExchange(i, diag, InverseMatrix);
   //change the line order to make the diagnal terms not equals to zero

   for(int j = i + 1; j < OriginMatrix->GetNbinsX(); j++){//index j is the next row of diagnal term
     double scale = - OriginMatrix->GetBinContent(j + 1, i + 1) / OriginMatrix->GetBinContent(i + 1, i + 1);
     RowTransform(j, i, scale, OriginMatrix);
     RowTransform(j, i, scale, InverseMatrix);
   }

   double scale = 1.0 / OriginMatrix->GetBinContent(i + 1, i + 1);
   RowScale(i, scale, OriginMatrix);
   RowScale(i, scale, InverseMatrix);
 }

 for(int i = 0; i < OriginMatrix->GetNbinsX(); i++){//index i is front one of the diagnal term
   for(int j = i + 1; j < OriginMatrix->GetNbinsX(); j++){
     double scale = - OriginMatrix->GetBinContent(i + 1, j + 1);
     RowTransform(i, j, scale, OriginMatrix);
     RowTransform(i, j, scale, InverseMatrix);
   }
 }

 if(isOutput){
   for(int i = 0; i < OriginMatrix->GetNbinsX(); i++){
     for(int j = 0; j < OriginMatrix->GetNbinsX(); j++){
       cout<<InverseMatrix->GetBinContent(i + 1, j + 1)<<" ";
     }
     cout<<endl;
   }
 }

 delete OriginMatrix;
}

void CalculateInverseMatrix(vector<vector<double>> Matrix, vector<vector<double>> &InverseMatrix)
{
 bool isOutput = false;
 if(isOutput) std::cout<<"Start to calculate inverse matrix."<<std::endl;

 InverseMatrix.resize(Matrix.size());
 for(int i = 0; i < InverseMatrix.size(); i++){
   InverseMatrix.at(i).resize(Matrix.at(i).size());
 }

 vector<vector<double>> OriginMatrix = Matrix;

 if(isOutput){
   for(int i = 0; i < OriginMatrix.size(); i++){
     for(int j = 0; j < OriginMatrix.at(i).size(); j++){
       if(fabs(OriginMatrix.at(i).at(j)) < 1e-10) cout<<0.0<<" ";
       else cout<<OriginMatrix.at(i).at(j)<<" ";
     }
     cout<<endl;
   }
 }

 for(int i = 0; i < OriginMatrix.size(); i++){
   for(int j = 0; j < OriginMatrix.size(); j++){
     if(i == j) InverseMatrix.at(i).at(j) = 1.0;
     if(i != j) InverseMatrix.at(i).at(j) = 0.0;
   }
 }

 for(int i = 0; i < OriginMatrix.size(); i++){//index i is the diagnal term
   int diag = i;
   while(fabs(OriginMatrix.at(diag).at(i)) < 1e-10){
     diag++;
   }
   RowExchange(i, diag, OriginMatrix);
   RowExchange(i, diag, InverseMatrix);
   //change the line order to make the diagnal terms not equals to zero

   for(int j = i + 1; j < OriginMatrix.size(); j++){//index j is the next row of diagnal term
     double scale = - OriginMatrix.at(j).at(i) / OriginMatrix.at(i).at(i);
     RowTransform(j, i, scale, OriginMatrix);
     RowTransform(j, i, scale, InverseMatrix);
   }

   double scale = 1.0 / OriginMatrix.at(i).at(i);
   RowScale(i, scale, OriginMatrix);
   RowScale(i, scale, InverseMatrix);
 }

 for(int i = 0; i < OriginMatrix.size(); i++){//index i is front one of the diagnal term
   for(int j = i + 1; j < OriginMatrix.size(); j++){
     double scale = - OriginMatrix.at(i).at(j);
     RowTransform(i, j, scale, OriginMatrix);
     RowTransform(i, j, scale, InverseMatrix);
   }
 }

 if(isOutput){
   for(int i = 0; i < OriginMatrix.size(); i++){
     for(int j = 0; j < OriginMatrix.size(); j++){
       cout<<InverseMatrix.at(i).at(j)<<" ";
     }
     cout<<endl;
   }
 }

 OriginMatrix.clear();
}

#endif
