#include "PDFHelper/WWProduction.h"

WWProduction::WWProduction()
{
 QuarkCharge[1] = -1.0 / 3.0;
 QuarkCharge[2] = 2.0 / 3.0;
 QuarkCharge[3] = -1.0 / 3.0;
 QuarkCharge[4] = 2.0 / 3.0;
 QuarkCharge[5] = -1.0 / 3.0;

 I3Q[1] = -0.5;
 I3Q[2] = 0.5;
 I3Q[3] = -0.5;
 I3Q[4] = 0.5;
 I3Q[5] = -0.5;

 if(ncall != -1){
   step = -1.0;
   ResetIntegral();
   return;
 }
 if(step < 0){
   ncall = -1;
   ResetIntegral();
   return;
 }

}

void WWProduction::DrawWWMass(int bin, double left, double right, int iflag, TString Process)
{
 iWWMass++;

 TString HistName;
 if(iflag == 0) HistName = "WWMassAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "WWMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "WWMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 WWMassPlot[iWWMass] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= WWMassPlot[iWWMass]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;

   double BinLeft = WWMassPlot[iWWMass]->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight = WWMassPlot[iWWMass]->GetXaxis()->GetBinUpEdge(ibin);

   Value = IntegralWWHadronCrossSectionQ(BinLeft, BinRight, iflag);
   if(Value > 0) Error = sqrt(Value) * ErrorLevel;
   WWMassPlot[iWWMass]->SetBinContent(ibin, Value);
   WWMassPlot[iWWMass]->SetBinError(ibin, Error);
 }

 hf->cd();
}

void WWProduction::DrawWWQuarkMass(int bin, double left, double right, int iflag, TString Process)
{
 iWWQuarkMass++;
 
 TString HistName;
 if(iflag == 0) HistName = "WWQuarkMassAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "WWQuarkMassDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "WWQuarkMassUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 WWQuarkMassPlot[iWWQuarkMass] = new TH1D(HistName, HistName, bin, left, right);
 
 for(int ibin = 1; ibin <= WWQuarkMassPlot[iWWQuarkMass]->GetNbinsX(); ibin++){
   double Value = 0.0;
   double Error = 0.0;
   
   double BinLeft = WWQuarkMassPlot[iWWQuarkMass]->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight = WWQuarkMassPlot[iWWQuarkMass]->GetXaxis()->GetBinUpEdge(ibin);
   
   Value = IntegralWWQuarkCrossSectionQ(BinLeft, BinRight, iflag);
   if(Value > 0) Error = sqrt(Value) * ErrorLevel;
   WWQuarkMassPlot[iWWQuarkMass]->SetBinContent(ibin, Value);
   WWQuarkMassPlot[iWWQuarkMass]->SetBinError(ibin, Error);
 }
 
 hf->cd();
}

void WWProduction::DrawBoostAsymmetry(int bin, double left, double right, int iflag, TString Process)
{
 iBoostAsymmetry++;

 TString HistName;
 if(iflag == 0) HistName = "BoostAsymmetryAll_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 1) HistName = "BoostAsymmetryDownQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 2) HistName = "BoostAsymmetryUpQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 3) HistName = "BoostAsymmetryStrangeQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 4) HistName = "BoostAsymmetryCharmQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 if(iflag == 5) HistName = "BoostAsymmetryBottomQuark_" + PDFName + "_" + (int)iSet + "_" + Process;
 BoostAsymmetryPlot[iBoostAsymmetry] = new TH1D(HistName, HistName, bin, left, right);

 for(int ibin = 1; ibin <= BoostAsymmetryPlot[iBoostAsymmetry]->GetNbinsX(); ibin++){
   double Forward = 0.0;
   double Backward = 0.0;
   double ForwardError = 0.0;
   double BackwardError = 0.0;
   double Value = 0.0;
   double Error = 0.0;

   double BinLeft = BoostAsymmetryPlot[iBoostAsymmetry]->GetXaxis()->GetBinLowEdge(ibin);
   double BinRight = BoostAsymmetryPlot[iBoostAsymmetry]->GetXaxis()->GetBinUpEdge(ibin);

   if(iflag != 0){
     Forward = IntegralBoostCrossSection(BinLeft, BinRight, iflag) + IntegralBoostCrossSection(BinLeft, BinRight, iflag * (-1));
     Backward = IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), iflag) + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), iflag * (-1));
   }
   if(iflag == 0){
     Forward = IntegralBoostCrossSection(BinLeft, BinRight, 1) + IntegralBoostCrossSection(BinLeft, BinRight, -1)
             + IntegralBoostCrossSection(BinLeft, BinRight, 2) + IntegralBoostCrossSection(BinLeft, BinRight, -2)
             + IntegralBoostCrossSection(BinLeft, BinRight, 3) + IntegralBoostCrossSection(BinLeft, BinRight, -3)
             + IntegralBoostCrossSection(BinLeft, BinRight, 4) + IntegralBoostCrossSection(BinLeft, BinRight, -4)
             + IntegralBoostCrossSection(BinLeft, BinRight, 5) + IntegralBoostCrossSection(BinLeft, BinRight, -5);

     Backward = IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), 1) + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), -1)
              + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), 2) + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), -2)
              + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), 3) + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), -3)
              + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), 4) + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), -4)
              + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), 5) + IntegralBoostCrossSection(BinRight * (-1.0), BinLeft * (-1.0), -5);
   }
   if(Forward > 0) ForwardError = sqrt(Forward) * ErrorLevel;
   if(Backward > 0) ForwardError = sqrt(Backward) * ErrorLevel;

   Value = (Forward - Backward) / (Forward + Backward);
   Error = 2 * sqrt((Forward * BackwardError) * (Forward * BackwardError) + (Backward * ForwardError) * (Backward * ForwardError)) / ((Forward + Backward) * (Forward + Backward));

   BoostAsymmetryPlot[iBoostAsymmetry]->SetBinContent(ibin, Value);
   BoostAsymmetryPlot[iBoostAsymmetry]->SetBinError(ibin, Error);
 }

 hf->cd();

}

double WWProduction::CalT(int i, double Q, double Y0)
{
 double Value = 0.0;
 if(i > 0) Value = QuarkMass[i] * QuarkMass[i] + WMass * WMass - muF * muF * Q * Q * (exp(Y0) / (exp(Y0) + exp(Y0 * (-1.0))));
 if(i < 0) Value = QuarkMass[abs(i)] * QuarkMass[abs(i)] + WMass * WMass - muF * muF * Q * Q * (exp(Y0 * (-1.0)) / (exp(Y0) + exp(Y0 * (-1.0))));
 return Value;
}

double WWProduction::CalU(int i, double Q, double Y0)
{
 double Value = 0.0;
 if(i > 0) Value = QuarkMass[i] * QuarkMass[i] + WMass * WMass - muF * muF * Q * Q * (exp(Y0 * (-1.0)) / (exp(Y0) + exp(Y0 * (-1.0))));
 if(i < 0) Value = QuarkMass[abs(i)] * QuarkMass[abs(i)] + WMass * WMass - muF * muF * Q * Q * (exp(Y0) / (exp(Y0) + exp(Y0 * (-1.0))));
 return Value;
}

double WWProduction::Omega(double x)
{
 double Value = 0.0;
 if(x > 0) Value = 1.0;
 if(x < 0) Value = 0.0;
 return Value;
}

double WWProduction::CalA(int i, double Q, double Y0)
{
 double Value = 0.0;
 double Value1 = (CalT(i, Q, Y0) * CalU(i, Q, Y0) / (WMass * WMass * WMass * WMass) - 1.0);
 double Value2 = (0.25 - WMass * WMass / (muF * muF * Q * Q) + 3.0 * WMass * WMass * WMass * WMass / (muF * muF * muF * muF * Q * Q * Q * Q));
 Value = Value1 * Value2 + muF * muF * Q * Q / (WMass * WMass) - 4.0;

 if(Q < 2.0 * WMass) Value = 0.0;

 return Value;
}

double WWProduction::CalIstu(int i, double Q, double Y0)
{
 double Value = 0.0;
 double Value1 = (CalT(i, Q, Y0) * CalU(i, Q, Y0) / (WMass * WMass * WMass * WMass) - 1.0);
 double Value2 = (0.25 - WMass * WMass / (2.0 * muF * muF * Q * Q) - WMass * WMass * WMass * WMass / (muF * muF * Q * Q * CalT(i, Q, Y0)));
 Value = Value1 * Value2 + muF * muF * Q * Q / (WMass * WMass) - 2.0 + 2.0 * WMass * WMass / CalT(i, Q, Y0);

 if(Q < 2.0 * WMass) Value = 0.0;

 return Value;
}

double WWProduction::CalIsut(int i, double Q, double Y0)
{
 double Value = 0.0;
 double Value1 = (CalT(i, Q, Y0) * CalU(i, Q, Y0) / (WMass * WMass * WMass * WMass) - 1.0);
 double Value2 = (0.25 - WMass * WMass / (2.0 * muF * muF * Q * Q) - WMass * WMass * WMass * WMass / (muF * muF * Q * Q * CalU(i, Q, Y0)));
 Value = Value1 * Value2 + muF * muF * Q * Q / (WMass * WMass) - 2.0 + 2.0 * WMass * WMass / CalU(i, Q, Y0);

 if(Q < 2.0* WMass) Value = 0.0;

 return Value;
}

double WWProduction::CalEstu(int i, double Q, double Y0)
{
 double Value = 0.0;
 double Value1 = (CalT(i, Q, Y0) * CalU(i, Q, Y0) / (WMass * WMass * WMass * WMass) - 1.0);
 double Value2 = (0.25 + WMass * WMass * WMass * WMass / (CalT(i, Q, Y0) * CalT(i, Q, Y0)));
 Value = Value1 * Value2 + muF * muF * Q * Q / (WMass * WMass);

 if(Q < 2.0* WMass) Value = 0.0;

 return Value;
}

double WWProduction::CalEsut(int i, double Q, double Y0)
{
 double Value = 0.0;
 double Value1 = (CalT(i, Q, Y0) * CalU(i, Q, Y0) / (WMass * WMass * WMass * WMass) - 1.0);
 double Value2 = (0.25 + WMass * WMass * WMass * WMass / (CalU(i, Q, Y0) * CalU(i, Q, Y0)));
 Value = Value1 * Value2 + muF * muF * Q * Q / (WMass * WMass);

 if(Q < 2.0* WMass) Value = 0.0;

 return Value;
}

double WWProduction::WWCrossSection(int i, double Q, double Y0)
{
 double Value = 0.0;
 double fCharge = 0.0;
 double fI3Q = 0.0;

 if(i > 0) fCharge = QuarkCharge[i];
 else if(i < 0) fCharge = (-1.0) * QuarkCharge[abs(i)];

 if(i > 0) fI3Q = I3Q[i];
 else if(i < 0) fI3Q = (-1.0) * I3Q[abs(i)];

 double l = 2.0 * (fI3Q - fCharge * stw);
 double r = -2.0 * fCharge * stw;

 double Value1 = (   (fCharge + ((l + r) / (4.0 * stw)) * (muF * muF * Q * Q / (muF * muF * Q * Q - ZMass * ZMass)))
                   * (fCharge + ((l + r) / (4.0 * stw)) * (muF * muF * Q * Q / (muF * muF * Q * Q - ZMass * ZMass)))
                 +   (((l - r) / (4.0 * stw)) * (muF * muF * Q * Q / (muF * muF * Q * Q - ZMass * ZMass)))
                   * (((l - r) / (4.0 * stw)) * (muF * muF * Q * Q / (muF * muF * Q * Q - ZMass * ZMass)))  ) * CalA(abs(i), Q, Y0);

 double Value2 = (0.5 / stw) * (fCharge + (0.5 * l / stw) * (muF * muF * Q * Q / (muF * muF * Q * Q - ZMass * ZMass)))
               * (Omega(fCharge * (-1.0)) * CalIstu(abs(i), Q, Y0) - Omega(fCharge) * CalIsut(abs(i), Q, Y0));

 double Value3 = (1.0 / (8.0 * stw * stw)) * (Omega(fCharge * (-1.0)) * CalEstu(abs(i), Q, Y0) + Omega(fCharge) * CalEsut(abs(i), Q, Y0));

 Value = ((2.0 * TMath::Pi() * alphaEM0 * alphaEM0) / (3.0 * muF * muF * muF * muF * Q * Q * Q * Q)) * (Value1 + Value2 + Value3)
        * (muF * muF * Q * Q * (2.0 * exp(2.0 * Y0) / ((exp(2.0 * Y0) + 1.0) * (exp(2.0 * Y0) + 1.0)))) * 1e9 * 0.38937966;

// cout<<"A: "<<CalA(abs(i), Q, Y0)<<" Istu: "<<CalIstu(abs(i), Q, Y0)<<" Isut: "<<CalIsut(abs(i), Q, Y0)<<" Estu: "<<CalEstu(abs(i), Q, Y0)<<" Esut: "<<CalEsut(abs(i), Q, Y0)<<endl;
// cout<<"S: "<<Q * Q<<" T: "<<CalT(abs(i), Q, Y0)<<" U: "<<CalU(abs(i), Q, Y0)<<" S+T+U: "<<Q * Q + CalT(abs(i), Q, Y0) + CalU(abs(i), Q, Y0)<<endl;
// cout<<Value1<<" "<<Value2<<" "<<Value3<<" "<<Value<<endl;
// cout<<endl;

 if(Q < 2.0 * WMass) Value = 0.0;

 return Value;
}

double WWProduction::WWHadronCrossSectiony(double y, int i, double Q, double Y0)
{
 double Value = 0.0;

 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 if(fabs(Y0) > Y0max) Value = 0.0;
 else Value = GetF1F2YInput(i, y, Q) * WWCrossSection(i, Q, Y0);

 return Value;
}

double WWProduction::WWHadronCrossSectionY0(double Y0, int i, double Q, double y)
{
 double Value = 0.0;

 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 if(fabs(Y0) > Y0max) Value = 0.0;
 else Value = GetF1F2YInput(i, y, Q) * WWCrossSection(i, Q, Y0);

 return Value;
}

double WWProduction::WWQuarkCrossSectionY0Q(double Y0, int i, double Q)
{
 double Value = 0.0;

 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 if(fabs(Y0) > Y0max) Value = 0.0;
 else Value = WWCrossSection(i, Q, Y0);

 return Value;
}

double WWProduction::WWHadronCrossSectionY0Q(double Y0, int flavor, double Q)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 //cout<<"Start Integral WW CrossSection y: [-5.0, 5.0] Y0 "<<Y0<<" flavor "<<flavor<<" Q "<<Q<<endl;
 double Value = Simpson(&PDFHelper::WWHadronCrossSectiony, -5.0, 5.0, flavor, Q, Y0);

 return Value;
}

double WWProduction::WWHadronCrossSectionQ(double Q, int flavor)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 //cout<<"Start Integral WW CrossSection Y0: [-5.0, 5.0] Q = "<<Q<<" flavor "<<flavor<<endl;
 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;
 double Value = Simpson(&PDFHelper::WWHadronCrossSectionY0Q, Y0max * (-1.0), Y0max, (int)flavor, Q);

 return Value;
}

double WWProduction::WWQuarkCrossSectionQ(double Q, int flavor)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 double Y0max; 
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;
 double Value = Simpson(&PDFHelper::WWQuarkCrossSectionY0Q, Y0max * (-1.0), Y0max, flavor, Q);

 return Value;
}

double WWProduction::IntegralWWHadronCrossSectionQ(double left, double right, int flavor)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral WW CrossSection Mass: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::WWHadronCrossSectionQ, left, right, (int)flavor);

 return Value;
}

double WWProduction::IntegralWWQuarkCrossSectionQ(double left, double right, int flavor)
{
 ResetIntegral();
 ncall = 100;
 isOutput = false;
 cout<<"Start Integral WW Quark CrossSection Mass: ["<<left<<", "<<right<<"]"<<endl;
 double Value = Simpson(&PDFHelper::WWQuarkCrossSectionQ, left, right, flavor);

 return Value;
}

double WWProduction::BoostCrossSection(double Q, double Delta, int flavor, TString rest)
{
 double Value1 = 0.0, Value2 = 0.0, Value3 = 0.0, Value4 = 0.0;

 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value1 = 0.0;
 else Value1 = Simpson(&PDFHelper::WWHadronCrossSectiony, fabs(Delta / 2.0), 5.0, flavor, Q, Delta / 2.0);//x=2Y0, f(y)f(Y0)dydY0 = f(y)f(0.5x)d0.5x

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value2 = 0.0;
 else Value2 = Simpson(&PDFHelper::WWHadronCrossSectiony, -5.0, (-1.0) * fabs(Delta / 2.0), flavor, Q, (-1.0) * Delta / 2.0);//x=-2Y0, f(y)f(Y0)dydY0 = -f(y)f(-0.5x)d0.5x

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value3 = 0.0;
 else Value3 = Simpson(&PDFHelper::WWHadronCrossSectionY0, fabs(Delta / 2.0), Y0max, flavor, Q, Delta / 2.0);//x=2y, f(y)f(Y0)dydY0 = f(0.5x)f(Y0)d0.5x

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value4 = 0.0;
 else Value4 = Simpson(&PDFHelper::WWHadronCrossSectionY0, Y0max * (-1.0), (-1.0) * fabs(Delta / 2.0), flavor, Q, (-1.0) * Delta / 2.0);//x=-2y, f(y)f(Y0)dydY0 = -f(-0.5x)f(Y0)d0.5x


 double Value = Value1 + Value2 + Value3 + Value4;
 //cout<<"Delta: "<<Delta<<" Flavor: "<<flavor<<" "<<Value1<<" "<<Value2<<" "<<Value3<<" "<<Value4<<endl;
 return Value;

}

double WWProduction::BoostCrossSectionTerm1(double Q, double Delta, int flavor, TString rest)
{
 double Value = 0.0;

 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value = 0.0;
 else Value = Simpson(&PDFHelper::WWHadronCrossSectiony, fabs(Delta / 2.0), 5.0, flavor, Q, Delta / 2.0);//x=2Y0, f(y)f(Y0)dydY0 = f(y)f(0.5x)d0.5x

 return Value;
}

double WWProduction::BoostCrossSectionTerm2(double Q, double Delta, int flavor, TString rest)
{
 double Value = 0.0;
 
 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value = 0.0;
 else Value = Simpson(&PDFHelper::WWHadronCrossSectiony, -5.0, (-1.0) * fabs(Delta / 2.0), flavor, Q, (-1.0) * Delta / 2.0);//x=-2Y0, f(y)f(Y0)dydY0 = -f(y)f(-0.5x)d0.5x

 return Value;
}

double WWProduction::BoostCrossSectionTerm3(double Q, double Delta, int flavor, TString rest)
{
 double Value = 0.0;
 
 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value = 0.0;
 else Value = Simpson(&PDFHelper::WWHadronCrossSectionY0, fabs(Delta / 2.0), Y0max, flavor, Q, Delta / 2.0);//x=2y, f(y)f(Y0)dydY0 = f(0.5x)f(Y0)d0.5x

 return Value;
}

double WWProduction::BoostCrossSectionTerm4(double Q, double Delta, int flavor, TString rest)
{
 double Value = 0.0;
 
 double Y0max;
 if(Q > 2.0 * WMass) Y0max = fabs(log((2.0 * WMass) / (Q - sqrt(Q * Q - 4.0 * WMass * WMass))));
 else Y0max = 0.0;

 ResetIntegral();
 ncall = 100;
 isOutput = false;
 if(fabs(Delta / 2.0) > Y0max) Value = 0.0;
 else Value = Simpson(&PDFHelper::WWHadronCrossSectionY0, Y0max * (-1.0), (-1.0) * fabs(Delta / 2.0), flavor, Q, (-1.0) * Delta / 2.0);//x=-2y, f(y)f(Y0)dydY0 = -f(-0.5x)f(Y0)d0.5x

 return Value;
}

double WWProduction::TotalBoostCrossSection(double Delta, int flavor)
{
 double Value1 = 0.0, Value2 = 0.0, Value3 = 0.0;

 ResetIntegral();
 ncall = 10;
 isOutput = false;
 //cout<<"Integral Q in range [160, 400] flavor: "<<flavor<<" Delta: "<<Delta<<endl;
 Value2 = Simpson(&PDFHelper::BoostCrossSection, 160.0, 400.0, Delta, flavor, (TString)"");
 ResetIntegral();
 ncall = 100;
 isOutput = false;
// cout<<"Integral Q in range [400, 1000] flavor: "<<flavor<<" Delta: "<<Delta<<endl;
// Value3 = Simpson(&PDFHelper::BoostCrossSection, 400.0, 1000.0, Delta, flavor, (TString)"");

 double Value = Value1 + Value2 + Value3;

 return Value;
}

double WWProduction::IntegralBoostCrossSection(double left, double right, int flavor)
{
 ResetIntegral();
 ncall = 10;
 isOutput = false;
 cout<<"Integral Delta in range ["<<left<<", "<<right<<"] flavor: "<<flavor<<endl;
 double Value = Simpson(&PDFHelper::TotalBoostCrossSection, left, right, flavor);

 return Value;
}
