#include "Tools/Tools.h"

TGraph* GenerateEllipse(double X0, double Y0, double DeltaX, double DeltaY, double cosphi)
{
/*
 * X = X0 + DeltaX * cos(theta)
 * Y = Y0 + DeltaY * cos(theta + phi)
 */

 vector<double> x;
 vector<double> y;

 double phi = acos(cosphi);

 double step = 0.01;
 int NPoint = 2.0 * TMath::Pi() / step + 1;

 for(int i = 0; i < NPoint; i++){
   double theta = (-1.0) * TMath::Pi() + step * i;
   double xValue = X0 + DeltaX * cos(theta);
   double yValue = Y0 + DeltaY * cos(theta + phi);
   x.push_back(xValue);
   y.push_back(yValue);
 }

 TGraph* f = new TGraph(x.size());
 for(int ibin = 0; ibin < x.size(); ibin++){
   f->SetPointX(ibin + 1, x.at(ibin));
   f->SetPointY(ibin + 1, y.at(ibin));
 }
 f->RemovePoint(0);

 return f;
}

