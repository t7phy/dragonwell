#include "RooFitHelper/RooFitHelper.h"

RooFitHelper::RooFitHelper()
{

}

#ifdef USE_ROOFIT
void RooFitHelper::FitGaussian(RooDataSet *data)
{
 cout<<"Start FitGaussian()"<<endl;
 RooRealVar x("x", "x", -10, 10);
 RooRealVar mean("mean", "mean of gaussian", 1, -10, 10);
 RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);
 
 // Build gaussian pdf in terms of x,mean and sigma
 RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);
 gauss.fitTo(*data);

 mean.Print();
 sigma.Print();
}

void RooFitHelper::FitGaussian(TH1D *h1)
{
 cout<<"Start FitGaussian()"<<endl;
 RooRealVar x("x", "x", -10, 10);
 RooRealVar mean("mean", "mean of gaussian", 1, -10, 10);
 RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);

 // Build gaussian pdf in terms of x,mean and sigma
 RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);

 // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
 RooDataHist dh("dh", "dh", x, Import(*h1));
 gauss.fitTo(dh);

 mean.Print();
 sigma.Print();
}

void RooFitHelper::Input(int n, TString name, TString title, double center, double lower, double upper)
{
 m_Var[n] = new RooRealVar(name, title, center, lower, upper);

 VarNameMap[n] = name;

 npar++;
}

void RooFitHelper::Input(int n, TString name, TString title, double center)
{
 m_Var[n] = new RooRealVar(name, title, center);
 
 VarNameMap[n] = name;
 
 npar++;
}

void RooFitHelper::Input(int n, RooRealVar *var)
{
 m_Var[n] = var;

 npar++;
}

void RooFitHelper::AddGaussian(int n, int ivar, double mean, double sigma)
{
 PDFNameMap[n] = (TString)"Gaussian";

 m_Gaussian_mean[n] = new RooRealVar("mean", "mean of gaussian", mean);
 m_Gaussian_sigma[n] = new RooRealVar("sigma", "width of gaussian", sigma);

 // Build gaussian pdf in terms of x,mean and sigma
 m_Gaussian[n] = new RooGaussian("gauss", "gaussian PDF", *(m_Var[ivar]), *(m_Gaussian_mean[n]), *(m_Gaussian_sigma[n]));

 m_Pdf[n] = m_Gaussian[n];

 npdf++;
}

void RooFitHelper::AddPolynomial2(int n, TString name, int ivar, int var1, int var2)
{
 PDFNameMap[n] = (TString)name;

 m_Polynomial[n] = new RooChebychev(name, name, *(m_Var[ivar]), RooArgList(*(m_Var[var1]), *(m_Var[var2])));

 m_Pdf[n] = m_Polynomial[n];

 npdf++;
}

void RooFitHelper::AddPdf2(int n, TString name, int pdf1, int pdf2, int fraction)
{
 PDFNameMap[n] = name;

 m_AddPdf[n] = new RooAddPdf(name, name, RooArgList(*(m_Pdf[pdf1]), *(m_Pdf[pdf2])), RooArgList(*(m_Var[fraction])));

 m_Pdf[n] = m_AddPdf[n];

 npdf++;
}

void RooFitHelper::Generate(int n, int input, int output, int NData)
{
 m_DataSet[output] = m_Pdf[n]->generate(RooArgSet(*(m_Var[input])), NData);

 ndata++;
}

void RooFitHelper::GenerateHist(int output, int input, int idata, int nbinx)
{
 m_Canvas[output] = new TCanvas("c", "c", 800, 600);
 m_Canvas[output]->SetFillColor(0);
 m_Canvas[output]->cd();

 m_Var[input]->setBins(nbinx);

 m_DataHist[output] = new RooDataHist("dh", "binned version of d", RooArgSet(*(m_Var[input])), *(m_DataSet[idata]));
 m_DataHist[output]->Print("v");

 m_HistPlot[output] = m_Var[input]->frame((RooFit::Title("hist")));
 m_DataHist[output]->plotOn(m_HistPlot[output], RooFit::LineColor(kRed), RooFit::MarkerColor(kRed), RooFit::Name("hData"));

 m_HistPlot[output]->Draw();

 m_Legend[output] = new TLegend(0.6, 0.6, 0.8, 0.8);

 nhist++;
}

void RooFitHelper::FitTo(int imodel, int idata)
{
 cout<<"Start to fit for seperate data points:"<<endl;

 m_Pdf[imodel]->fitTo(*(m_DataSet[idata]));
}

void RooFitHelper::FitToHist(int imodel, int ihist)
{
 cout<<"Start to fit for histogram:"<<endl;

 m_Pdf[imodel]->fitTo(*(m_DataHist[ihist]));
}

void RooFitHelper::DrawPdf(int iplot, int ipdf, Style_t style, Color_t color, TString name)
{
 m_Pdf[ipdf]->plotOn(m_HistPlot[iplot], RooFit::Components(RooArgSet(*(m_Pdf[ipdf]))), RooFit::LineStyle(style), RooFit::LineColor(color), RooFit::Name(name));

 m_HistPlot[iplot]->Draw();

 m_Legend[iplot]->AddEntry(m_HistPlot[iplot]->findObject(name), name, "l");
}

void RooFitHelper::SavePlot(int iplot, TString name)
{
 m_Legend[iplot]->Draw("same");

 m_Canvas[iplot]->Update();
 m_Canvas[iplot]->SaveAs(name);
}

void RooFitHelper::FitFunction(TString func, RooArgSet var, RooDataSet *data)
{
 RooGenericPdf genpdf("genpdf", "genpdf", func, var);
 genpdf.fitTo(*data);

 for(int i = 0; i < npar; i++){
   m_Var[i]->Print();
 }
}

void RooFitHelper::FitFunction(TString func, RooArgSet var, TH1D* h1)
{
/*
 *  RooRealVar x1 = RooRealVar("x", "x", -20, 20);
 *  RooRealVar alpha1 = RooRealVar("alpha", "alpha", 5, 0.1, 10);
 *  RooFitHelper *run = new RooFitHelper();
 *  run->Input(0, &x1);
 *  run->Input(1, &alpha1);
 *  run->FitFunction("(1+0.1*abs(x)+sin(sqrt(abs(x*alpha+0.1))))", RooArgSet(x1, alpha1), h1);
 */

 RooRealVar x("x", "x", -10, 10);
 RooGenericPdf genpdf("genpdf", "genpdf", func, var);
 RooDataHist dh("dh", "dh", x, Import(*h1));
 genpdf.fitTo(dh);

 for(int i = 0; i < npar; i++){
   m_Var[i]->Print();
 }
}

void RooFitHelper::PlotFunction(TF1* f1, double left, double right)
{
/*
 *  TF1* f1 = new TF1("f1", "sin(x)/x", 0, 10);
 *  run->PlotFunction(f1, 0.01, 20);
 */

 RooRealVar x("x", "x", left, right);
 
 // Create binding of TF1 object to above observable
 RooAbsReal *rfa1 = bindFunction(f1, x);

 RooPlot *frame = x.frame(Title(f1->GetName()));
 rfa1->plotOn(frame);

 TCanvas *c = new TCanvas("myCanvas", "myCanvas", 800, 800);
 c->cd();
 gPad->SetLeftMargin(0.15);
 frame->GetYaxis()->SetTitleOffset(1.6);
 frame->Draw();
 c->SaveAs(f1->GetName() + (TString)".png");
}
#endif
