#include "/mnt/home/fuyao3/figure/Figure.h"

void get_kfactor()
{
 auto ReadMCFM = [&](TString Input, TString name){
   ifstream infile(Input);
   string FileLine;

   for(int i = 1; i <= 5; i++){
     getline(infile, FileLine);
   }

   double xmin, xmax, cross, numerror;
   vector<double> BinLowers;
   vector<double> BinUppers;
   vector<double> Xsecs;
   vector<double> Errors;
   while(infile >> xmin){
     infile >> xmax >> cross >> numerror;
     BinLowers.push_back(xmin);
     BinUppers.push_back(xmax);
     Xsecs.push_back(cross);
     Errors.push_back(numerror);
   }
   vector<double> Binning = BinLowers;
   Binning.push_back(BinUppers.at(BinUppers.size() - 1));

   TH1D* hist = new TH1D(name, name, Binning.size() - 1, &Binning[0]);

   for(int ibin = 1; ibin <= hist->GetNbinsX(); ibin++){
     hist->SetBinContent(ibin, Xsecs.at(ibin - 1));
     hist->SetBinError(ibin, Errors.at(ibin - 1));
   }

   return hist;
 };

 auto GetBinning = [&](TH1D* hist){
   vector<double> Binning;

   for(int ibin = 1; ibin <= hist->GetNbinsX(); ibin++){
     Binning.push_back(hist->GetXaxis()->GetBinLowEdge(ibin));
   }
   Binning.push_back(hist->GetXaxis()->GetBinUpEdge(hist->GetNbinsX()));

   return Binning;
 };

 auto LinkHists = [&](vector<TH1D *> Hists, TString name){
   vector<vector<double>> Binnings(Hists.size());
   for(int i = 0; i < Hists.size(); i++){
     Binnings.at(i) = GetBinning(Hists.at(i));
   }

   vector<double> Binning = Binnings.at(0);
   for(int i = 1; i < Hists.size(); i++){
     for(int iedge = 1; iedge < Binnings.at(i).size(); iedge++){
       Binning.push_back(Binnings.at(i).at(iedge));
     }
   }

   TH1D* hist = new TH1D(name, name, Binning.size() - 1, &Binning[0]);

   int bin = 1;
   for(int i = 0; i < Hists.size(); i++){
     for(int ibin = 1; ibin <= Hists.at(i)->GetNbinsX(); ibin++){
       hist->SetBinContent(bin, Hists.at(i)->GetBinContent(ibin));
       hist->SetBinError(bin, Hists.at(i)->GetBinError(ibin));
       bin++;
     }
   }

   return hist;
 };

 TString LOPath = "/mnt/home/fuyao3/Work/MCFM_HighMassDY/KFactor_ATLAS13p6TeV/CT18NNLO_MT_pds/LO/i2Tn3.00/Scale977/";
 TString NLOPath = "/mnt/home/fuyao3/Work/MCFM_HighMassDY/KFactor_ATLAS13p6TeV/CT18NNLO_MT_pds/NLO/i2Tn3.00/Scale977/";
 TString NNLOPath = "/mnt/home/fuyao3/Work/MCFM_HighMassDY/KFactor_ATLAS13p6TeV/CT18NNLO_MT_pds/NNLO/i2Tn3.00/Scale977/";

 TString LOtag = "Z_only_lo_";
 TString NLOtag = "Z_only_nlo_";
 TString NNLOtag = "Z_only_nnlo_";

 vector<TString> MassSlicesNames = {
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_120M180.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_180M250.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_250M400.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_400M600.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_600M800.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_800M1000.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_1000M1250.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_1250M1500.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_1500M1750.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_1750M2000.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_2000M2250.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_2250M2500.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_2500M2750.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_2750M3000.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_3000M3500.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_3500M4000.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_4000M4500.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_4500M5000.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_5000M6000.txt",
   "CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_ZPrime_1D_6000M7000.txt"
 };

 vector<TH1D *> Hists_LO(MassSlicesNames.size());
 vector<TH1D *> Hists_NLO(MassSlicesNames.size());
 vector<TH1D *> Hists_NNLO(MassSlicesNames.size());

 TH1D* Final_LO;
 TH1D* Final_NLO;
 TH1D* Final_NNLO;
 TH1D* ratio;

 TFile* writefile = new TFile("ZPrime_KFactor.root", "RECREATE");
 writefile->cd();

 // LO
 for(int i = 0; i < MassSlicesNames.size(); i++){
   TString HistName = MassSlicesNames.at(i);
   HistName.ReplaceAll("CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_", "");
   HistName.ReplaceAll(".txt", "");
   HistName = HistName + "_LO";
   Hists_LO.at(i) = ReadMCFM(LOPath + LOtag + MassSlicesNames.at(i), HistName);
   Hists_LO.at(i)->Write();
 }

 Final_LO = LinkHists(Hists_LO, "Final_LO");
 Final_LO->Write();

 // NLO
 for(int i = 0; i < MassSlicesNames.size(); i++){
   TString HistName = MassSlicesNames.at(i);
   HistName.ReplaceAll("CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_", "");
   HistName.ReplaceAll(".txt", "");
   HistName = HistName + "_NLO";
   Hists_NLO.at(i) = ReadMCFM(NLOPath + NLOtag + MassSlicesNames.at(i), HistName);
   Hists_NLO.at(i)->Write();
 }

 Final_NLO = LinkHists(Hists_NLO, "Final_NLO");
 Final_NLO->Write();

 // NNLO
 for(int i = 0; i < MassSlicesNames.size(); i++){
   TString HistName = MassSlicesNames.at(i);
   HistName.ReplaceAll("CT18NNLO_1.00_1.00_pt34cut13TeV_ATLAS13p6TeV_", "");
   HistName.ReplaceAll(".txt", "");
   HistName = HistName + "_NNLO";
   Hists_NNLO.at(i) = ReadMCFM(NNLOPath + NNLOtag + MassSlicesNames.at(i), HistName);
   Hists_NNLO.at(i)->Write();
 }

 Final_NNLO = LinkHists(Hists_NNLO, "Final_NNLO");
 Final_NNLO->Write();

 ratio = (TH1D *)Final_NNLO->Clone("KFactor");
 ratio->Divide(Final_NLO);
 ratio->Write();

 writefile->Close();
}

