#include "DilutionFitting/FlavorSearch.h"

FlavorSearch::FlavorSearch()
{
 LogBin = Logspace(1e-5, 0.9999, 1000, 10.0);

 vector<double> xVector = Logspace(0.002154, 1e-2, 10, 10.0);
 for(int i = 0; i < xVector.size(); i++){
   xMap[i + 1] = xVector.at(i);
   xIndex[xVector.at(i)] = i + 1;
 }

 vector<double> QVector = {100.0};
 for(int i = 0; i < QVector.size(); i++){
   QMap[i + 1] = QVector.at(i);
   QIndex[QVector.at(i)] = i + 1;
 }

 isFixed.resize(NPar);
 for(int i = 0; i < NPar; i++){
   isFixed.at(i) = 0.5;
 }

 InitialValue.resize(NPar);
 for(int i = 0; i < NPar; i++){
   InitialValue.at(i) = 0.1;
 }
}

void FlavorSearch::InitialPDFAll(TString PDFName, int nSet)
{
#ifdef USE_LHAPDF
 for(int i = 0; i <= nSet; i++){
   PDF[make_pair(PDFName, i)] = LHAPDF::mkPDF(PDFName.Data(), i);
 }

 PDFType[PDFName] = "LHAPDF";

 PDFnSet[PDFName] = nSet;

 this->PDFName = PDFName;
#endif
}

void FlavorSearch::InitialCTEQPDF(TString GivenName, TString PDFFile, int iSet)
{
 cout<<PDFFile<<endl;

 CTPDF[make_pair(GivenName, iSet)] = new pdsReader();
 CTPDF[make_pair(GivenName, iSet)]->Initialize(PDFFile);
}

void FlavorSearch::InitialCTEQPDFAll(TString GivenName, vector<TString> PDFFiles)
{
 for(int i = 0; i < PDFFiles.size(); i++){
   InitialCTEQPDF(GivenName, PDFFiles.at(i), i);
 }

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = PDFFiles.size() - 1;

 this->PDFName = GivenName;
}

void FlavorSearch::InitialCTEQPDF(TString GivenName, pdsReader* pdf, int iSet)
{
 CTPDF[make_pair(GivenName, iSet)] = pdf;
}

void FlavorSearch::InitialCTEQPDFAll(TString GivenName, vector<pdsReader *> PDFFiles)
{
 for(int i = 0; i < PDFFiles.size(); i++){
   InitialCTEQPDF(GivenName, PDFFiles.at(i), i);
 }

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = PDFFiles.size() - 1;

 this->PDFName = GivenName;
}

void FlavorSearch::InitialCTEQPDFAll(TString GivenName, TString DirectoryName)
{
 DIR* PDFDir;

 struct dirent* ptr;

 if(!(PDFDir = opendir(DirectoryName.Data()))){
   cout<<"ERROR! Directory doesn't exist!"<<endl;
   return;
 }

 vector<TString> PDFFiles;

 while((ptr = readdir(PDFDir)) != 0){
   if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
     TString PDFFile = DirectoryName + "/" + ptr->d_name;
     PDFFiles.push_back(PDFFile);
   }
 }

 sort(PDFFiles.begin(), PDFFiles.end());
 for(int i = 0; i < PDFFiles.size(); i++){
   InitialCTEQPDF(GivenName, PDFFiles.at(i), i);
 }

 PDFType[GivenName] = "CTEQ";

 PDFnSet[GivenName] = PDFFiles.size() - 1;

 this->PDFName = GivenName;

 cout<<"nSet for "<<GivenName<<" is "<<PDFnSet[GivenName]<<endl;
}

void FlavorSearch::InitialAllFlavors()
{
 if(PDFType[PDFName] == "LHAPDF"){
   for(int iSet = 0; iSet <= PDFnSet[PDFName]; iSet++){
     for(int ix = 0; ix < xMap.size(); ix++){
       for(int iq = 0; iq < QMap.size(); iq++){
#ifdef USE_LHAPDF
         uPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(2, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         dPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(1, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         sPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(3, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         cPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(4, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         bPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(5, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         gPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(21, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         ubarPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(-2, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         dbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(-1, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         sbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(-3, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         cbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(-4, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         bbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = PDF[make_pair(PDFName, iSet)]->xfxQ(-5, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
#endif
       }
     }
   }
 }

 if(PDFType[PDFName] == "CTEQ"){
   for(int iSet = 0; iSet <= PDFnSet[PDFName]; iSet++){
     for(int ix = 0; ix < xMap.size(); ix++){
       for(int iq = 0; iq < QMap.size(); iq++){ 
         uPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(2, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         dPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(1, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         sPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(3, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         cPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(4, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         bPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(5, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         gPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(21, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         ubarPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-2, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         dbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-1, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         sbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-3, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         cbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-4, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
         bbarPDF[make_tuple(iSet, ix + 1, iq + 1)] = CTPDF[make_pair(PDFName, iSet)]->xfxQ(-5, xMap[ix + 1], QMap[iq + 1]) / xMap[ix + 1];
       }
     }
   }
 }

 global_uPDF = &uPDF;
 global_dPDF = &dPDF;
 global_sPDF = &sPDF;
 global_cPDF = &cPDF;
 global_bPDF = &bPDF;
 global_gPDF = &gPDF;
 global_ubarPDF = &ubarPDF;
 global_dbarPDF = &dbarPDF;
 global_sbarPDF = &sbarPDF;
 global_cbarPDF = &cbarPDF;
 global_bbarPDF = &bbarPDF;

 cout<<"Flavors are all initialized."<<endl;
}

void FlavorSearch::Fit(int ix, int iq)
{
 global_nSet = PDFnSet[PDFName];
 global_ix = ix;
 global_iq = iq;

 myMinuit = new TMinuitHelper(NPar);
 myMinuit->SetFCN(FlavorSearchFitting);

 myMinuit->Input(0, "par0", InitialValue.at(0), isFixed.at(0), -1.0, 1.0);
 myMinuit->Input(1, "par1", InitialValue.at(1), isFixed.at(1), -1.0, 1.0);
 myMinuit->Input(2, "par2", InitialValue.at(2), isFixed.at(2), -1.0, 1.0);
 myMinuit->Input(3, "par3", InitialValue.at(3), isFixed.at(3), -1.0, 1.0);
 myMinuit->Input(4, "par4", InitialValue.at(4), isFixed.at(4), -1.0, 1.0);
 myMinuit->Input(5, "par5", InitialValue.at(5), isFixed.at(5), -1.0, 1.0);
 myMinuit->Input(6, "par6", InitialValue.at(6), isFixed.at(6), -1.0, 1.0);
 myMinuit->Input(7, "par7", InitialValue.at(7), isFixed.at(7), -1.0, 1.0);
 myMinuit->Input(8, "par8", InitialValue.at(8), isFixed.at(8), -1.0, 1.0);
 myMinuit->Input(9, "par9", InitialValue.at(9), isFixed.at(9), -1.0, 1.0);
 myMinuit->Input(10, "par10", InitialValue.at(10), isFixed.at(10), -1.0, 1.0);
 myMinuit->Input(11, "par11", InitialValue.at(11), isFixed.at(11), -1.0, 1.0);
 myMinuit->Input(12, "par12", InitialValue.at(12), isFixed.at(12), -1.0, 1.0);
 myMinuit->Input(13, "par13", InitialValue.at(13), isFixed.at(13), -1.0, 1.0);
 myMinuit->Input(14, "par14", InitialValue.at(14), isFixed.at(14), -1.0, 1.0);
 myMinuit->Input(15, "par15", InitialValue.at(15), isFixed.at(15), -1.0, 1.0);
 myMinuit->Input(16, "par16", InitialValue.at(16), isFixed.at(16), -1.0, 1.0);
 myMinuit->Input(17, "par17", InitialValue.at(17), isFixed.at(17), -1.0, 1.0);
 myMinuit->Input(18, "par18", InitialValue.at(18), isFixed.at(18), -1.0, 1.0);
 myMinuit->Input(19, "par19", InitialValue.at(19), isFixed.at(19), -1.0, 1.0);
 myMinuit->Input(20, "par20", InitialValue.at(20), isFixed.at(20), -1.0, 1.0);
 myMinuit->Input(21, "par21", InitialValue.at(21), isFixed.at(21), -1.0, 1.0);

 myMinuit->Exec("SIMPLEX", 100000, 1);//tolerance*0.001
 myMinuit->Exec("MIGRAD", 100000, 0.001);
 Par = new double[NPar];
 ParError = new double[NPar];
 myMinuit->GetParametersAndError(Par, ParError);
 for(int i = 0; i < NPar; i++){
   cout<<fixed<<setprecision(4)<<"par["<<i<<"]: "<<Par[i]<<" Error: "<<ParError[i]<<endl;
 }
}

double FlavorSearch::CalculateCombination(int iSet, double x, double Q)
{
 double Value = 0.0;

 if(fabs(Par[6] * u(iSet, x, Q)
     + Par[7] * d(iSet, x, Q)
     + Par[8] * s(iSet, x, Q)
     + Par[9] * c(iSet, x, Q)
     + Par[10] * b(iSet, x, Q)) > 1e-10){
   Value =
      (Par[0] * ubar(iSet, x, Q)
     + Par[1] * dbar(iSet, x, Q)
     + Par[2] * sbar(iSet, x, Q)
     + Par[3] * cbar(iSet, x, Q)
     + Par[4] * bbar(iSet, x, Q)
     + Par[5] * g(iSet, x, Q)) /
      (Par[6] * u(iSet, x, Q)
     + Par[7] * d(iSet, x, Q)
     + Par[8] * s(iSet, x, Q)
     + Par[9] * c(iSet, x, Q)
     + Par[10] * b(iSet, x, Q))
     + Par[11] * u(iSet, x, Q)
     + Par[12] * d(iSet, x, Q)
     + Par[13] * s(iSet, x, Q)
     + Par[14] * c(iSet, x, Q)
     + Par[15] * b(iSet, x, Q)
     + Par[16] * ubar(iSet, x, Q)
     + Par[17] * dbar(iSet, x, Q)
     + Par[18] * sbar(iSet, x, Q)
     + Par[19] * cbar(iSet, x, Q)
     + Par[20] * bbar(iSet, x, Q)
     + Par[21] * g(iSet, x, Q);
 }

 return Value;
}

double FlavorSearch::CalculateCorrelation(double x, double Q)
{
 double Value = 0.0;

 vector<double> FlavorSet(PDFnSet[PDFName] + 1);
 for(int i = 0; i <= PDFnSet[PDFName]; i++){
   FlavorSet.at(i) = CalculateCombination(i, x, Q);
 }
 vector<double> Obs(PDFnSet[PDFName] / 2);
 vector<double> Combination(PDFnSet[PDFName] / 2);

 for(int i = 1; i <= PDFnSet[PDFName] / 2; i++){
   Obs.at(i - 1) = Observable.at(2 * i - 1) - Observable.at(2 * i);
   Combination.at(i - 1) = FlavorSet.at(2 * i - 1) - FlavorSet.at(2 * i);
 }

 Value = CosPhi(Combination, Obs);

 FlavorSet.clear();
 Obs.clear();
 Combination.clear();

 return Value;
}

void FlavorSearch::DrawCorrelation(TString subName)
{
 cout<<fixed<<setprecision(6)<<"Draw correlation for combination: the correlation at x = "<<xMap[global_ix]<<" is "<<CalculateCorrelation(xMap[global_ix], QMap[global_iq])<<endl;
 cout<<fixed<<setprecision(1)<<"("<<Par[0]<<"ubar + "<<Par[1]<<"dbar + "<<Par[2]<<"sbar + "<<Par[3]<<"cbar + "<<Par[4]<<"bbar + "<<Par[5]<<"gluon) / ";
 cout<<fixed<<setprecision(1)<<"("<<Par[6]<<"u + "<<Par[7]<<"d + "<<Par[8]<<"s + "<<Par[9]<<"c + "<<Par[10]<<"b)"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[11]<<"u + "<<Par[12]<<"d + "<<Par[13]<<"s + "<<Par[14]<<"c + "<<Par[15]<<"b + "<<Par[16]<<"gluon"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[17]<<"ubar + "<<Par[18]<<"dbar + "<<Par[19]<<"sbar + "<<Par[20]<<"cbar + "<<Par[21]<<"bbar"<<endl;

 TString HistName;
 HistName = (TString)"Correlation_Fit" + (int)global_ix;
 if(FixComb != "") HistName = "Correlation_" + FixComb;
 if(subName != "") HistName = "Correlation_" + subName;

 TH1D* h1 = new TH1D(HistName, HistName, LogBin.size() - 1, &LogBin[0]);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   vector<double> FlavorSet(PDFnSet[PDFName] + 1);
   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     FlavorSet.at(i) = CalculateCombination(i, h1->GetBinCenter(ibin), 100.0);
   }
   vector<double> Obs(PDFnSet[PDFName] / 2);
   vector<double> Combination(PDFnSet[PDFName] / 2);

   for(int i = 1; i <= PDFnSet[PDFName] / 2; i++){
     Obs.at(i - 1) = Observable.at(2 * i - 1) - Observable.at(2 * i);
     Combination.at(i - 1) = FlavorSet.at(2 * i - 1) - FlavorSet.at(2 * i);
   }

   double Correlation = CosPhi(Combination, Obs);

   h1->SetBinContent(ibin, Correlation);
   h1->SetBinError(ibin, 0);

   FlavorSet.clear();
   Obs.clear();
   Combination.clear();
 }

 hf->cd();

}

void FlavorSearch::IndividualContribution()
{
 vector<double> SavedPar(NPar);
 for(int i = 0; i < NPar; i++){
   SavedPar.at(i) = Par[i];
 }

 for(int i = 0; i < NPar; i++){
   for(int j = 0; j < NPar; j++){
     Par[j] = SavedPar.at(j);
   }
   Par[i] = 0.0;
   DrawCorrelation((TString)"RemovePar" + (int)i);
 }

}

void FlavorSearch::ScanAllCombinations()
{
 vector<double> SavedPar(NPar);
 for(int i = 0; i < NPar; i++){
   SavedPar.at(i) = Par[i];
 }

 vector<int> BineryNum(NPar);
 for(int i = 0; i < (int)pow(2, NPar); i++){
   if(i % 100000 == 0) cout<<i<<"th combination has been scaned."<<endl;

   BineryNum.at(0) = i / (int)pow(2, 21);
   BineryNum.at(1) = i % (int)pow(2, 21) / (int)pow(2, 20);
   BineryNum.at(2) = i % (int)pow(2, 20) / (int)pow(2, 19);
   BineryNum.at(3) = i % (int)pow(2, 19) / (int)pow(2, 18);
   BineryNum.at(4) = i % (int)pow(2, 18) / (int)pow(2, 17);
   BineryNum.at(5) = i % (int)pow(2, 17) / (int)pow(2, 16);
   BineryNum.at(6) = i % (int)pow(2, 16) / (int)pow(2, 15);
   BineryNum.at(7) = i % (int)pow(2, 15) / (int)pow(2, 14);
   BineryNum.at(8) = i % (int)pow(2, 14) / (int)pow(2, 13);
   BineryNum.at(9) = i % (int)pow(2, 13) / (int)pow(2, 12);
   BineryNum.at(10) = i % (int)pow(2, 12) / (int)pow(2, 11);
   BineryNum.at(11) = i % (int)pow(2, 11) / (int)pow(2, 10);
   BineryNum.at(12) = i % (int)pow(2, 10) / (int)pow(2, 9);
   BineryNum.at(13) = i % (int)pow(2, 9) / (int)pow(2, 8);
   BineryNum.at(14) = i % (int)pow(2, 8) / (int)pow(2, 7);
   BineryNum.at(15) = i % (int)pow(2, 7) / (int)pow(2, 6);
   BineryNum.at(16) = i % (int)pow(2, 6) / (int)pow(2, 5);
   BineryNum.at(17) = i % (int)pow(2, 5) / (int)pow(2, 4);
   BineryNum.at(18) = i % (int)pow(2, 4) / (int)pow(2, 3);
   BineryNum.at(19) = i % (int)pow(2, 3) / (int)pow(2, 2);
   BineryNum.at(20) = i % (int)pow(2, 2) / (int)pow(2, 1);
   BineryNum.at(21) = i % (int)pow(2, 1);

   int NIncluded = 0;
   for(int j = 0; j < NPar; j++){
     if(BineryNum.at(j) == 1){
       Par[j] = SavedPar.at(j);
       NIncluded++;
     }
     if(BineryNum.at(j) == 0) Par[j] = 0.0;
   }
   if(NIncluded == 8) EightCombination[CalculateCorrelation(xMap[global_ix], QMap[global_iq])] = BineryNum;
   if(NIncluded == 7) SevenCombination[CalculateCorrelation(xMap[global_ix], QMap[global_iq])] = BineryNum;
   if(NIncluded == 6) SixCombination[CalculateCorrelation(xMap[global_ix], QMap[global_iq])] = BineryNum;
   if(NIncluded == 5) FiveCombination[CalculateCorrelation(xMap[global_ix], QMap[global_iq])] = BineryNum;
   if(NIncluded == 4) FourCombination[CalculateCorrelation(xMap[global_ix], QMap[global_iq])] = BineryNum;

   BineryNum.clear();
   BineryNum.resize(NPar);
 }

 map<double, vector<int>>::iterator EightIter = EightCombination.end();
 map<double, vector<int>>::iterator SevenIter = SevenCombination.end();
 map<double, vector<int>>::iterator SixIter = SixCombination.end();
 map<double, vector<int>>::iterator FiveIter = FiveCombination.end();
 map<double, vector<int>>::iterator FourIter = FourCombination.end();
 EightIter--;
 SevenIter--;
 SixIter--;
 FiveIter--;
 FourIter--;

 cout<<"For 8 combination, the maximum correlation is "<<EightIter->first<<" the combination is"<<endl;
 for(int i = 0; i < NPar; i++){
   if(EightIter->second.at(i) == 1) Par[i] = SavedPar.at(i);
   if(EightIter->second.at(i) == 0) Par[i] = 0.0;
 }
 cout<<fixed<<setprecision(1)<<"("<<Par[0]<<"ubar + "<<Par[1]<<"dbar + "<<Par[2]<<"sbar + "<<Par[3]<<"cbar + "<<Par[4]<<"bbar + "<<Par[5]<<"gluon) / ";
 cout<<fixed<<setprecision(1)<<"("<<Par[6]<<"u + "<<Par[7]<<"d + "<<Par[8]<<"s + "<<Par[9]<<"c + "<<Par[10]<<"b)"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[11]<<"u + "<<Par[12]<<"d + "<<Par[13]<<"s + "<<Par[14]<<"c + "<<Par[15]<<"b + "<<Par[16]<<"gluon"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[17]<<"ubar + "<<Par[18]<<"dbar + "<<Par[19]<<"sbar + "<<Par[20]<<"cbar + "<<Par[21]<<"bbar"<<endl;

 cout<<"For 7 combination, the maximum correlation is "<<SevenIter->first<<" the combination is"<<endl;
 for(int i = 0; i < NPar; i++){
   if(SevenIter->second.at(i) == 1) Par[i] = SavedPar.at(i);
   if(SevenIter->second.at(i) == 0) Par[i] = 0.0;
 }
 cout<<fixed<<setprecision(1)<<"("<<Par[0]<<"ubar + "<<Par[1]<<"dbar + "<<Par[2]<<"sbar + "<<Par[3]<<"cbar + "<<Par[4]<<"bbar + "<<Par[5]<<"gluon) / ";
 cout<<fixed<<setprecision(1)<<"("<<Par[6]<<"u + "<<Par[7]<<"d + "<<Par[8]<<"s + "<<Par[9]<<"c + "<<Par[10]<<"b)"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[11]<<"u + "<<Par[12]<<"d + "<<Par[13]<<"s + "<<Par[14]<<"c + "<<Par[15]<<"b + "<<Par[16]<<"gluon"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[17]<<"ubar + "<<Par[18]<<"dbar + "<<Par[19]<<"sbar + "<<Par[20]<<"cbar + "<<Par[21]<<"bbar"<<endl;

 cout<<"For 6 combination, the maximum correlation is "<<SixIter->first<<" the combination is"<<endl;
 for(int i = 0; i < NPar; i++){
   if(SixIter->second.at(i) == 1) Par[i] = SavedPar.at(i);
   if(SixIter->second.at(i) == 0) Par[i] = 0.0;
 }
 cout<<fixed<<setprecision(1)<<"("<<Par[0]<<"ubar + "<<Par[1]<<"dbar + "<<Par[2]<<"sbar + "<<Par[3]<<"cbar + "<<Par[4]<<"bbar + "<<Par[5]<<"gluon) / ";
 cout<<fixed<<setprecision(1)<<"("<<Par[6]<<"u + "<<Par[7]<<"d + "<<Par[8]<<"s + "<<Par[9]<<"c + "<<Par[10]<<"b)"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[11]<<"u + "<<Par[12]<<"d + "<<Par[13]<<"s + "<<Par[14]<<"c + "<<Par[15]<<"b + "<<Par[16]<<"gluon"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[17]<<"ubar + "<<Par[18]<<"dbar + "<<Par[19]<<"sbar + "<<Par[20]<<"cbar + "<<Par[21]<<"bbar"<<endl;

 cout<<"For 5 combination, the maximum correlation is "<<FiveIter->first<<" the combination is"<<endl;
 for(int i = 0; i < NPar; i++){
   if(FiveIter->second.at(i) == 1) Par[i] = SavedPar.at(i);
   if(FiveIter->second.at(i) == 0) Par[i] = 0.0;
 }
 cout<<fixed<<setprecision(1)<<"("<<Par[0]<<"ubar + "<<Par[1]<<"dbar + "<<Par[2]<<"sbar + "<<Par[3]<<"cbar + "<<Par[4]<<"bbar + "<<Par[5]<<"gluon) / ";
 cout<<fixed<<setprecision(1)<<"("<<Par[6]<<"u + "<<Par[7]<<"d + "<<Par[8]<<"s + "<<Par[9]<<"c + "<<Par[10]<<"b)"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[11]<<"u + "<<Par[12]<<"d + "<<Par[13]<<"s + "<<Par[14]<<"c + "<<Par[15]<<"b + "<<Par[16]<<"gluon"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[17]<<"ubar + "<<Par[18]<<"dbar + "<<Par[19]<<"sbar + "<<Par[20]<<"cbar + "<<Par[21]<<"bbar"<<endl;

 cout<<"For 4 combination, the maximum correlation is "<<FourIter->first<<" the combination is"<<endl;
 for(int i = 0; i < NPar; i++){
   if(FourIter->second.at(i) == 1) Par[i] = SavedPar.at(i);
   if(FourIter->second.at(i) == 0) Par[i] = 0.0;
 }
 cout<<fixed<<setprecision(1)<<"("<<Par[0]<<"ubar + "<<Par[1]<<"dbar + "<<Par[2]<<"sbar + "<<Par[3]<<"cbar + "<<Par[4]<<"bbar + "<<Par[5]<<"gluon) / ";
 cout<<fixed<<setprecision(1)<<"("<<Par[6]<<"u + "<<Par[7]<<"d + "<<Par[8]<<"s + "<<Par[9]<<"c + "<<Par[10]<<"b)"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[11]<<"u + "<<Par[12]<<"d + "<<Par[13]<<"s + "<<Par[14]<<"c + "<<Par[15]<<"b + "<<Par[16]<<"gluon"<<endl;
 cout<<fixed<<setprecision(1)<<"+ "<<Par[17]<<"ubar + "<<Par[18]<<"dbar + "<<Par[19]<<"sbar + "<<Par[20]<<"cbar + "<<Par[21]<<"bbar"<<endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double FlavorSearch::CalculateSpecialCombination(int iSet, double x, double Q)
{
 double Value = 0.0;

 if(fabs(u(iSet, x, Q) - ubar(iSet, x, Q) - d(iSet, x, Q) - dbar(iSet, x, Q) + 5.5 * g(iSet, x, Q)) > 1e-20){
   Value = g(iSet, x, Q) / (u(iSet, x, Q) - ubar(iSet, x, Q) - d(iSet, x, Q) - dbar(iSet, x, Q) + 5.5 * g(iSet, x, Q));
 }

 return Value;
}

double FlavorSearch::CalculateSpecialCorrelation(double x, double Q)
{
 double Value = 0.0;

 vector<double> FlavorSet(PDFnSet[PDFName] + 1);
 for(int i = 0; i <= PDFnSet[PDFName]; i++){
   FlavorSet.at(i) = CalculateSpecialCombination(i, x, Q);
 }
 vector<double> Obs(PDFnSet[PDFName] / 2);
 vector<double> Combination(PDFnSet[PDFName] / 2);

 for(int i = 1; i <= PDFnSet[PDFName] / 2; i++){
   Obs.at(i - 1) = Observable.at(2 * i - 1) - Observable.at(2 * i);
   Combination.at(i - 1) = FlavorSet.at(2 * i - 1) - FlavorSet.at(2 * i);
 }

 Value = CosPhi(Combination, Obs);

 FlavorSet.clear();
 Obs.clear();
 Combination.clear();

 return Value;
}

void FlavorSearch::DrawSpecialCorrelation(TString subName)
{
 TString HistName;
 HistName = (TString)"Correlation_Fit" + (int)global_ix;
 if(FixComb != "") HistName = "Correlation_" + FixComb;
 if(subName != "") HistName = "Correlation_" + subName;

 TH1D* h1 = new TH1D(HistName, HistName, LogBin.size() - 1, &LogBin[0]);

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   vector<double> FlavorSet(PDFnSet[PDFName] + 1);
   for(int i = 0; i <= PDFnSet[PDFName]; i++){
     FlavorSet.at(i) = CalculateSpecialCombination(i, h1->GetBinCenter(ibin), 100.0);
   }
   vector<double> Obs(PDFnSet[PDFName] / 2);
   vector<double> Combination(PDFnSet[PDFName] / 2);

   for(int i = 1; i <= PDFnSet[PDFName] / 2; i++){
     Obs.at(i - 1) = Observable.at(2 * i - 1) - Observable.at(2 * i);
     Combination.at(i - 1) = FlavorSet.at(2 * i - 1) - FlavorSet.at(2 * i);
   }

   double Correlation = CosPhi(Combination, Obs);

   h1->SetBinContent(ibin, Correlation);
   h1->SetBinError(ibin, 0);

   FlavorSet.clear();
   Obs.clear();
   Combination.clear();
 }

 hf->cd();

}

