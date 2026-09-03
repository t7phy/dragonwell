#include "Tools/Interpolation.h"

Interpolation::Interpolation()
{

}

void Interpolation::InitializeThreeD(vector<double> XVector, vector<double> YVector, vector<double> ZVector, map<vector<int>, double> Points)
{
 this->XVector = XVector;
 this->YVector = YVector;
 this->ZVector = ZVector;
 this->Points = Points;
}

double Interpolation::ThreeDInp(int NX, int NY, int NZ, double Xinp, double Yinp, double Zinp)
{
 double Result = 0.0;

 this->NInterpX = NX;
 this->NInterpY = NY;
 this->NInterpZ = NZ;

 int LocateX = Locate(XVector, Xinp);
 int LocateY = Locate(YVector, Yinp);
 int LocateZ = Locate(ZVector, Zinp);

 LocateX = MakeEven(LocateX, XVector.size(), NX) - NX / 2 + 1;
 LocateY = MakeEven(LocateY, YVector.size(), NY) - NY / 2 + 1;
 LocateZ = MakeEven(LocateZ, ZVector.size(), NZ) - NZ / 2 + 1;

 //cout<<"LocateX: "<<LocateX<<" LocateY: "<<LocateY<<" LocateZ: "<<LocateZ<<endl;

 InterpX.resize(NInterpX);
 InterpY.resize(NInterpY);
 InterpZ.resize(NInterpZ);

 PointsX.resize(NInterpX);
 PointsY.resize(NInterpY);
 PointsZ.resize(NInterpZ);

 for(int i = 0; i < NInterpX; i++){
   InterpX.at(i) = XVector.at(LocateX + i);
 }
 for(int i = 0; i < NInterpY; i++){
   InterpY.at(i) = YVector.at(LocateY + i);
 }
 for(int i = 0; i < NInterpZ; i++){
   InterpZ.at(i) = ZVector.at(LocateZ + i);
 }

 for(int i = 0; i < NInterpX; i++){
   for(int j = 0; j < NInterpY; j++){
     for(int k = 0; k < NInterpZ; k++){
       PointsZ.at(k) = Points[(vector<int>{LocateX + i, LocateY + j, LocateZ + k})];
     }
     PointsY.at(j) = Polint(InterpZ, PointsZ, Zinp);
   }
   PointsX.at(i) = Polint(InterpY, PointsY, Yinp);
 }
 Result = Polint(InterpX, PointsX, Xinp);

 InterpX.clear();
 InterpY.clear();
 InterpZ.clear();

 PointsX.clear();
 PointsY.clear();
 PointsZ.clear();

 return Result;
}

double Interpolation::Polint(vector<double> InpVector, vector<double> FuncVector, double Xinp)
{
 int NMax = 10;
 vector<double> C(NMax);
 vector<double> D(NMax);

 double Yout = 0.0;
 double DY = 0.0;

 int N = InpVector.size();

 int NS = 1;

 double Diff = fabs(Xinp - InpVector.at(0));

 for(int i = 1; i <= N; i++){
   double DiffT = fabs(Xinp - InpVector.at(i - 1));
   if(DiffT < Diff){
     NS = i;
     Diff = DiffT;
   }
   C.at(i - 1) = FuncVector.at(i - 1);
   D.at(i - 1) = FuncVector.at(i - 1);
 }

 Yout = FuncVector.at(NS - 1);
 NS = NS - 1;

 for(int M = 1; M <= N - 1; M++){
   for(int J = 1; J <= N - M; J++){
     double H0 = InpVector.at(J - 1) - Xinp;
     double HP = InpVector.at(J + M - 1) - Xinp;
     double W = C.at(J) - D.at(J - 1);
     double Den = H0 - HP;
     if(fabs(Den) < 1e-20) cout<<" DEN = 0 in Polint"<<endl;
     Den = W / Den;
     D.at(J - 1) = HP * Den;
     C.at(J - 1) = H0 * Den;
   }
   if((2 * NS) < (N - M)){
     DY = C.at(NS);
   }
   else{
     DY = D.at(NS - 1);
     NS = NS - 1;
   }
   Yout = Yout + DY;
 }

 C.clear();
 D.clear();

 //cout<<"Polint: "<<Yout<<endl;

 return Yout;
}

int Interpolation::Locate(vector<double> Points, double Input)
{
 int Position = 0;

 int N = Points.size();

 int Lower = 0;
 int Upper = N + 1;

 int Middle = 0;
 while((Upper - Lower) > 1){
   Middle = (Lower + Upper) / 2;
   int logic1 = (Points.at(N - 1) > Points.at(0));
   int logic2 = (Input > Points.at(Middle - 1));

   if(logic1 == logic2){
     Lower = Middle;
   }
   else{
     Upper = Middle;
   }
 }

 Position = Lower - 1;

 if(Position < 0) Position = 0;
 //cout<<"Position: "<<Position<<endl;

 return Position;
}

bool Interpolation::CheckPoint(vector<double> Points, double Input)
{
 int N = Points.size() - 1;
 if(fabs((Points.at(N) - Input) * (Input - Points.at(1))) < 0.e-9){
   return false;
 }
 else{
   return true;
 }
}

int Interpolation::MakeEven(int Position, int N, int iDD)
{
 int Even = Position;

 if((Position + 1) < (iDD / 2)) Even = iDD / 2 - 1;
 if((Position + 1) >= (N - (iDD + 1) / 2)) Even = N - (iDD + 1) / 2 - 1;

 //cout<<"Position: "<<Position<<" (iDD / 2): "<<iDD / 2<<" (N - iDD / 2): "<<N - iDD / 2<<" Even: "<<Even<<endl;

 return Even;
}


