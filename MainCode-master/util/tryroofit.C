#include "RooFitHelper/RooFitHelper.h"

int main(int argc, char** argv)
{
#ifdef USE_ROOFIT
// RooRealVar x("x", "x", -10, 10);
// RooRealVar mean("mean", "mean of gaussian", 5, -10, 10);
// RooRealVar sigma("sigma", "width of gaussian", 0.5, 0.1, 10);
 
 // Build gaussian pdf in terms of x,mean and sigma
// RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);
 
 // Generate a dataset of 1000 events in x from gauss
// RooDataSet *data = gauss.generate(x, 10000);

 // cout<<x.getValV()<<" "<<mean.getValV()<<" "<<sigma.getValV()<<endl;

// TH1D* h1 = new TH1D("h1", "h1", 25, -10, 10);
// for(int i = 0; i < 10000; i++){
//   if(i % 1000 == 0) cout<<"1000 finished"<<endl;
//   h1->Fill(gRandom->Gaus(0, 3));
// }

/*
 RooRealVar x("x", "x", -20, 20);
 RooRealVar alpha("alpha", "alpha", 2, 0.1, 10);
 RooGenericPdf genpdf("genpdf", "genpdf", "(1+0.1*abs(x)+sin(sqrt(abs(x*alpha+0.1))))", RooArgSet(x, alpha));
 RooDataSet *data = genpdf.generate(x, 10000);

 RooRealVar x1 = RooRealVar("x", "x", -20, 20);
 RooRealVar alpha1 = RooRealVar("alpha", "alpha", 5, 0.1, 10);
 RooFitHelper *run = new RooFitHelper();
 run->Input(0, &x1);
 run->Input(1, &alpha1);
 run->FitFunction("(1+0.1*abs(x)+sin(sqrt(abs(x*alpha+0.1))))", RooArgSet(x1, alpha1), data);

 TF1* f1 = new TF1("f1", "sin(x)/x", 0, 10);
 run->PlotFunction(f1, 0.01, 20);
*/

 RooFitHelper* run = new RooFitHelper();
 run->openFile("roofit.root");
 run->Input(1, "x", "x", 0.0, 0.0, 10.0);
 run->AddGaussian(1, 1, 5, 0.5);
 run->AddGaussian(2, 1, 5, 1.0);

 run->Input(2, "a0", "a0", 0.5, 0.0, 1.0);
 run->Input(3, "a1", "a1", -0.2, 0.0, 1.0);
 run->AddPolynomial2(3, "Background", 1, 2, 3);

 run->Input(4, "sig1frac", "sig1frac", 0.8, 0.0, 1.0);
 run->AddPdf2(4, "Signal", 1, 2, 4);

 run->Input(5, "bkgfrac", "bkgfrac", 0.5, 0.0, 1.0);
 run->AddPdf2(5, "g1+g2+a", 4, 3, 5);

 run->Generate(5, 1, 1, 1000);
 run->GenerateHist(1, 1, 1, 10);

 run->FitTo(5, 1);
 run->FitToHist(5, 1);

 run->DrawPdf(1, 5, kSolid, kBlue, "hFull_model");
 run->DrawPdf(1, 3, kDashed, kRed, "hBkg");
 run->DrawPdf(1, 1, kDotted, kMagenta, "hsig1");
 run->DrawPdf(1, 2, kDotted, kGreen+2, "hsig2");

 run->SavePlot(1, "test_roofit.png");

 run->SaveFile();

#endif
 return 1;
}
