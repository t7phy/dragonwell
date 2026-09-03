#include "BATHelper/BCH1DHelper.h"

TH1D * GetSmallestIntervalHistogram(BCH1D h, double level)
{
   TH1D *fHistogram = (TH1D *)h.GetHistogram();

   // create a new histogram which will be returned and all yellow
   TH1D * hist_yellow = (TH1D*) fHistogram->Clone();
   hist_yellow->Reset();
   hist_yellow->SetFillStyle(1001);
   hist_yellow->SetFillColor(kYellow);

   // copy a temporary histogram
   int HIndex = 0;
   TH1D * hist_temp = (TH1D*) fHistogram->Clone(TString::Format("%s_%i",fHistogram->GetName(),(HIndex++)));
   double factor = hist_temp->Integral("");

   if(factor == 0)
      return 0;

   hist_temp->Scale(1. / factor);

   // here's the algorithm:
   // 1. find the maximum bin in the temporary histogram and copy it to
   // the yellow histogram.
   // 2. remove this bin from the temporary histogram.
   // 3. repeat this until a total of "level" probability is copied to
   // the yellow histogram.

   double sumprob = 0.0;

   while (sumprob < level)
   {
      // find maximum bin and value
      int bin = hist_temp->GetMaximumBin();
      double value = hist_temp->GetMaximum();

      // copy "1" into the corresponding bin in the yellow histogram
      hist_yellow->SetBinContent(bin, 1.0);

      // set the bin value in the temporary histogram to zero
      hist_temp->SetBinContent(bin, 0.0);

      // increase probability sum
      sumprob += value;
   }

   delete hist_temp;

   return hist_yellow;
}

std::vector<double> GetSmallestIntervals(BCH1D h, double content)
{
   TH1D* fHistogram = (TH1D *)h.GetHistogram();

   std::vector<double> v;

   TH1D * hist = GetSmallestIntervalHistogram(h, content);

   int nbins = hist->GetNbinsX();
   int ninter = 0;
   int lastbin = -1;

   double max = -1;
   double localmax = -1;
   double localmaxpos = -1;
   double localint = 0;
   bool flag = false;

   for (int i = 1; i <= nbins; ++i)
   {
      // interval starts here
      if (!flag && hist->GetBinContent(i) > 0.)
      {
         flag = true;
         v.push_back(hist->GetBinLowEdge(i));

         // remember start position of the interval
         lastbin = i;

         // increase number of intervals
         ninter++;

         // reset local maximum
         localmax = fHistogram->GetBinContent(i);
         localmaxpos = hist->GetBinLowEdge(i);

         // reset local integral
         localint = 0;
      }

      // interval stops here
      if ((flag && !(hist->GetBinContent(i) > 0.)) || (flag && i == nbins))
      {
         flag = false;
         v.push_back(hist->GetBinLowEdge(i) + hist->GetBinWidth(i));

         // set right bin to maximum if on edge
         if (i == nbins && localmax < fHistogram->GetBinContent(i))
            localmaxpos = hist->GetBinCenter(i) + 0.5 * hist->GetBinWidth(i);

         // find the absolute maximum
         if (localmax > max)
            max = localmax;

         // save local maximum
         v.push_back(localmax);
         v.push_back(localmaxpos);

         // save local integral
         v.push_back(localint);
      }

      // find local maximum
      if (i < nbins && localmax < fHistogram->GetBinContent(i))
      {
         localmax = fHistogram->GetBinContent(i);
         localmaxpos = hist->GetBinCenter(i);
      }

      // increase area
      localint += fHistogram->GetBinContent(i) / fHistogram->Integral();
   }

   // rescale absolute heights to relative heights
   for (int i = 0; i < ninter; ++i)
      v[i*5+2] = v.at(i*5+2) / max;

   return v;

}

TH1D* CalculateIntegratedHistogram(BCH2D h)
{
   TH1D* fIntegratedHistogram;

   TH2D* fHistogram = (TH2D *)h.GetHistogram();

   int nz = 100;

   double zmax = fHistogram->GetMaximum();
   double dz   = zmax / double(nz);

   double nx = fHistogram->GetNbinsX();
   double ny = fHistogram->GetNbinsY();

   // create histogram
   if (fIntegratedHistogram)
      delete fIntegratedHistogram;

   int HIndex = 0;
   fIntegratedHistogram = new TH1D(
         TString::Format("%s_int_prob_%d",fHistogram->GetName(),(HIndex++)), "", nz, 0.0, zmax);
   fIntegratedHistogram->SetXTitle("z");
   fIntegratedHistogram->SetYTitle("Integrated probability");
   fIntegratedHistogram->SetStats(kFALSE);

   // loop over histogram
   for (int ix = 1; ix <= nx; ix++)
      for (int iy = 1; iy <= ny; iy++)
      {
         int binmin = BCMath::Nint(fHistogram->GetBinContent(ix, iy) / dz);
         for (int i = binmin; i <= nz; i++)
            fIntegratedHistogram->SetBinContent(i,
                  fIntegratedHistogram->GetBinContent(i) +
                  fHistogram->GetBinContent(ix, iy));
      }

    return fIntegratedHistogram;
}

double GetLevel(TH1D* fIntegratedHistogram, double p)
{
   double quantiles[1];
   double probsum[1];
   probsum[0] = p;

   fIntegratedHistogram->GetQuantiles( 1, quantiles, probsum);

   return quantiles[0];
}

