#ifndef Calculation_Iterate_h
#define Calculation_Iterate_h

#include <filesystem>
#include "RootCommon.h"
#include "Calculation/PDFChi2.h"
#include "CTEQHelper/HoppetInterface.h"
#include "CTEQHelper/PDFEvolve.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/FastNLOHelper.h"
#include "Calculation/Dataset.h"
#include "Calculation/DataPoint.h"
#include "Calculation/Config.h"
#include "Calculation/QCDSet.h"
#include "Calculation/CTUtil.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnUserCovariance.h"
#include "Calculation/GlobalFittingCore.h"
#include <Eigen/Dense>

class Iterate
{
 public:

 double Tolerance = 10.0;
 int NPar = 0;
 TString Tier2Type = "CTEQ";
 double dmeasRequirement = 1e-5;

 GlobalFittingCore* m_instance;

 CTUtil* util = 0;

 Eigen::MatrixXd Hessian;

 Eigen::VectorXd xtrans;
 Eigen::MatrixXd wtrans;

 Eigen::VectorXd evec;
 Eigen::MatrixXd umat;

 Eigen::VectorXd tvec;
 Eigen::MatrixXd vmat;

 vector<double> NewParCentral;
 vector<double> ParStep;

 Iterate();
 virtual void Initialize();
 virtual void IterateHessianBasedPaper();
 virtual void IterateHessian();

 virtual void ProduceEVSet(TString name);
 virtual void EigenVectorShift(double distance, int ipar);

 virtual void CalcNewParOn(int ipar, double step);
 virtual void CalcNewParOff(int ipar, int jpar, double step1, double step2);

 virtual void UpdateParameters();

 virtual void OutputPDFTable(TString name, int iSet);
 virtual double GetChi2();
 virtual double GetTier2(TString type);

 virtual void ReadHessian(TString FileName);
 virtual void OutputHessian(TString FileName);
 virtual void ReadHessianFortran(TString FileName);
 virtual void OutputHessianFortran(TString FileName);

 virtual void InputHessian(ROOT::Minuit2::MnUserCovariance HessianMatrix){

   NPar = HessianMatrix.Nrow();
   Hessian = Eigen::MatrixXd(HessianMatrix.Nrow(), HessianMatrix.Nrow());
   for(int i = 0; i < HessianMatrix.Nrow(); i++){
     for(int j = 0; j < HessianMatrix.Nrow(); j++){
       Hessian(i, j) = HessianMatrix(i, j);
     }
   }

   // Get Sorted Eigen Values and Eigen Vectors
   Eigen::EigenSolver<Eigen::MatrixXd> es(Hessian);
   Eigen::MatrixXd D = es.pseudoEigenvalueMatrix();
   Eigen::MatrixXd V = es.pseudoEigenvectors();

   map<double, Eigen::VectorXd> SortEigenValues;
   for(int i = 0; i < HessianMatrix.Nrow(); i++){
     V.col(i).normalize();
     SortEigenValues[D(i, i) * (-1.0)] = V.col(i);
   }

   Eigen::MatrixXd SortedD = Eigen::MatrixXd::Identity(HessianMatrix.Nrow(), HessianMatrix.Nrow());
   Eigen::MatrixXd SortedV = Eigen::MatrixXd(HessianMatrix.Nrow(), HessianMatrix.Nrow());

   int iPar = 0;
   for(auto iter = SortEigenValues.begin(); iter != SortEigenValues.end(); iter++){
     SortedD(iPar, iPar) = iter->first * (-1.0);

     for(int i = 0; i < HessianMatrix.Nrow(); i++){
       SortedV(i, iPar) = iter->second(i);
     }
     iPar++;
   }
   SortEigenValues.clear();

   umat = Eigen::MatrixXd(HessianMatrix.Nrow(), HessianMatrix.Nrow());
   evec = Eigen::VectorXd(HessianMatrix.Nrow());

   for(int i = 0; i < HessianMatrix.Nrow(); i++){
     for(int j = 0; j < HessianMatrix.Nrow(); j++){
       umat(i, j) = SortedV(i, j);
     }
   }

   for(int i = 0; i < HessianMatrix.Nrow(); i++){
     evec(i) = SortedD(i, i);
   }

   // Calculate wtrans
   wtrans = Eigen::MatrixXd(HessianMatrix.Nrow(), HessianMatrix.Nrow());
   for(int i = 0; i < HessianMatrix.Nrow(); i++){
     for(int j = 0; j < HessianMatrix.Nrow(); j++){
       wtrans(i, j) = umat(i, j) / sqrt(evec(j));
     }
   }
   xtrans = Eigen::VectorXd(HessianMatrix.Nrow());

   OutputHessianFortran("Hessian_Minuit2.ev");
 }

};
#endif
