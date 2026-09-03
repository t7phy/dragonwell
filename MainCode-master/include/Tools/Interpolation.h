#ifndef Tools_Interpolation_h
#define Tools_Interpolation_h

#include "RootCommon.h"

using namespace std;

class Interpolation
{
 public:

 vector<double> XVector;
 vector<double> YVector;
 vector<double> ZVector;
 map<vector<int>, double> Points;

 vector<double> InterpX;
 vector<double> InterpY;
 vector<double> InterpZ;

 vector<double> PointsX;
 vector<double> PointsY;
 vector<double> PointsZ;

 int NInterpX = 2;
 int NInterpY = 2;
 int NInterpZ = 2;

 Interpolation();

 virtual void InitializeThreeD(vector<double> XVector, vector<double> YVector, vector<double> ZVector, map<vector<int>, double> Points);
 virtual double ThreeDInp(int NX, int NY, int NZ, double Xinp, double Yinp, double Zinp);
 virtual double Polint(vector<double> InpVector, vector<double> FuncVector, double Xinp);
 virtual int Locate(vector<double> Points, double Input); 
 virtual bool CheckPoint(vector<double> Points, double Input);
 virtual int MakeEven(int Position, int N, int iDD);

};

#endif
