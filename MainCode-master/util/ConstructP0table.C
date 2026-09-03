#include <iostream>
#include "RootCommon.h"
#include "Tools/Tools.h"
#include "FileForEPUMP/FileForEPUMP.h"
#include "ePumpHelper/ePumpHelper.h"
//#include "PDFHelper/PDFReweight.h"

using namespace std;

double GetCustomStatUnc(double sigma1, double sigma2, double coeff0, double coeff1)
{
 double Delta = 0.0;

 double a = coeff1 * coeff1;
 double b = (-1.0) * coeff1 * coeff1 * (sigma1 * sigma1 + sigma2 * sigma2);
 double c = (coeff1 * coeff1 - coeff0 * coeff0) * sigma1 * sigma1 * sigma2 * sigma2;

 Delta = ((-1.0) * b - sqrt(b * b - 4 * a * c)) / (2.0 * a);

 //cout<<"a: "<<a<<endl;
 //cout<<"b: "<<b<<endl;
 //cout<<"c: "<<c<<endl;

 return Delta;
}

int main(int argc, char** argv)
{
 if(argc != 2){
   cout<<"Usage ./ConstructP0table filename"<<endl;
   return 0;
 }

 TFile* file = new TFile("save.root", "RECREATE");

 ePumpHelper* EU = new ePumpHelper(argv[1]);
 EU->Initial();
 EU->Update();
 EU->LinkFile(file);

 TH1D* D05fbP0u_Data;
 vector<TH1D *> D05fbP0u_Theory;
 TH1D* D05fbP0d_Data;
 vector<TH1D *> D05fbP0d_Theory;

 TH1D* CMS8TeVP0u_Data;
 vector<TH1D *> CMS8TeVP0u_Theory;
 TH1D* CMS8TeVP0d_Data;
 vector<TH1D *> CMS8TeVP0d_Theory;

///////////////////////////////////////////////////////////////////////
 TH1D* D05fbP0_Data;
 vector<TH1D *> D05fbP0_Theory;

 TH1D* CMS8TeVP0_bin1_Data;
 vector<TH1D *> CMS8TeVP0_bin1_Theory;
 TH1D* CMS8TeVP0_bin2_Data;
 vector<TH1D *> CMS8TeVP0_bin2_Theory;
 TH1D* CMS8TeVP0_bin3_Data;
 vector<TH1D *> CMS8TeVP0_bin3_Theory;
 TH1D* CMS8TeVP0_bin4_Data;
 vector<TH1D *> CMS8TeVP0_bin4_Theory;

 TH1D* CMS8TeVP0_Data;
 vector<TH1D *> CMS8TeVP0_Theory;


 vector<double> D05fbP0_DataVector;
 vector<double> CMS8TeVP0_DataVector;

///////////////////////////////////////////////////////////////////////
 vector<TH1D *> D05fbP0Delta_Theory;

 vector<TH1D *> CMS8TeVP0u_bin1_Theory;
 vector<TH1D *> CMS8TeVP0d_bin1_Theory;
 vector<TH1D *> CMS8TeVP0Delta_bin1_Theory;
 vector<TH1D *> CMS8TeVP0u_bin2_Theory;
 vector<TH1D *> CMS8TeVP0d_bin2_Theory;
 vector<TH1D *> CMS8TeVP0Delta_bin2_Theory;
 vector<TH1D *> CMS8TeVP0u_bin3_Theory;
 vector<TH1D *> CMS8TeVP0d_bin3_Theory;
 vector<TH1D *> CMS8TeVP0Delta_bin3_Theory;
 vector<TH1D *> CMS8TeVP0u_bin4_Theory;
 vector<TH1D *> CMS8TeVP0d_bin4_Theory;
 vector<TH1D *> CMS8TeVP0Delta_bin4_Theory;


///////////////////////////////////////////////////////////////////////
 TH1D* D05fbAFB_Data;
 vector<TH1D *> D05fbAFB_Theory;

 TH1D* CMS8TeVAFB_Data;
 vector<TH1D *> CMS8TeVAFB_Theory;

///////////////////////////////////////////////////////////////////////

 EU->ConstructDataHist("test/D05fbP0u", D05fbP0u_Data);
 EU->ConstructTheoryHist("test/D05fbP0u", D05fbP0u_Theory);
 EU->ConstructDataHist("test/D05fbP0d", D05fbP0d_Data);
 EU->ConstructTheoryHist("test/D05fbP0d", D05fbP0d_Theory);

 EU->ConstructDataHist("test/CMS8TeVP0u", CMS8TeVP0u_Data);
 EU->ConstructTheoryHist("test/CMS8TeVP0u", CMS8TeVP0u_Theory);
 EU->ConstructDataHist("test/CMS8TeVP0d", CMS8TeVP0d_Data);
 EU->ConstructTheoryHist("test/CMS8TeVP0d", CMS8TeVP0d_Theory);

 EU->ConstructTheoryHist("test/D05fbAFB", D05fbAFB_Theory);
 EU->ConstructTheoryHist("test/CMS8TeVAFB", CMS8TeVAFB_Theory);

///////////////////////////////////////////////////////////////////////
 file->cd();

 D05fbP0_Data = new TH1D("D05fbP0_Data", "D05fbP0_Data", 2, 0, 2);
 D05fbP0_Data->SetBinContent(1, D05fbP0u_Data->GetBinContent(1));
 D05fbP0_Data->SetBinError(1, D05fbP0u_Data->GetBinError(1));
 D05fbP0_Data->SetBinContent(2, D05fbP0d_Data->GetBinContent(1));
 D05fbP0_Data->SetBinError(2, D05fbP0d_Data->GetBinError(1));

 D05fbP0_DataVector.push_back(D05fbP0u_Theory.at(0)->GetBinContent(1));
 D05fbP0_DataVector.push_back(D05fbP0d_Theory.at(0)->GetBinContent(1));

 CMS8TeVP0_bin1_Data = new TH1D("CMS8TeVP0_bin1_Data", "CMS8TeV_bin1_Data", 2, 0, 2);
 CMS8TeVP0_bin1_Data->SetBinContent(1, CMS8TeVP0u_Data->GetBinContent(1));
 CMS8TeVP0_bin1_Data->SetBinError(1, CMS8TeVP0u_Data->GetBinError(1));
 CMS8TeVP0_bin1_Data->SetBinContent(2, CMS8TeVP0d_Data->GetBinContent(1));
 CMS8TeVP0_bin1_Data->SetBinError(2, CMS8TeVP0d_Data->GetBinError(1));
 CMS8TeVP0_bin2_Data = new TH1D("CMS8TeVP0_bin2_Data", "CMS8TeV_bin2_Data", 2, 0, 2);
 CMS8TeVP0_bin2_Data->SetBinContent(1, CMS8TeVP0u_Data->GetBinContent(2));
 CMS8TeVP0_bin2_Data->SetBinError(1, CMS8TeVP0u_Data->GetBinError(2));
 CMS8TeVP0_bin2_Data->SetBinContent(2, CMS8TeVP0d_Data->GetBinContent(2));
 CMS8TeVP0_bin2_Data->SetBinError(2, CMS8TeVP0d_Data->GetBinError(2));
 CMS8TeVP0_bin3_Data = new TH1D("CMS8TeVP0_bin3_Data", "CMS8TeV_bin3_Data", 2, 0, 2);
 CMS8TeVP0_bin3_Data->SetBinContent(1, CMS8TeVP0u_Data->GetBinContent(3));
 CMS8TeVP0_bin3_Data->SetBinError(1, CMS8TeVP0u_Data->GetBinError(3));
 CMS8TeVP0_bin3_Data->SetBinContent(2, CMS8TeVP0d_Data->GetBinContent(3));
 CMS8TeVP0_bin3_Data->SetBinError(2, CMS8TeVP0d_Data->GetBinError(3));
 CMS8TeVP0_bin4_Data = new TH1D("CMS8TeVP0_bin4_Data", "CMS8TeV_bin4_Data", 2, 0, 2);
 CMS8TeVP0_bin4_Data->SetBinContent(1, CMS8TeVP0u_Data->GetBinContent(4));
 CMS8TeVP0_bin4_Data->SetBinError(1, CMS8TeVP0u_Data->GetBinError(4));
 CMS8TeVP0_bin4_Data->SetBinContent(2, CMS8TeVP0d_Data->GetBinContent(4));
 CMS8TeVP0_bin4_Data->SetBinError(2, CMS8TeVP0d_Data->GetBinError(4));

 CMS8TeVP0_Data = new TH1D("CMS8TeVP0_Data", "CMS8TeV_Data", 8, 0, 8);
 CMS8TeVP0_Data->SetBinContent(1, CMS8TeVP0u_Data->GetBinContent(1));
 CMS8TeVP0_Data->SetBinError(1, CMS8TeVP0u_Data->GetBinError(1));
 CMS8TeVP0_Data->SetBinContent(2, CMS8TeVP0d_Data->GetBinContent(1));
 CMS8TeVP0_Data->SetBinError(2, CMS8TeVP0d_Data->GetBinError(1));
 CMS8TeVP0_Data->SetBinContent(3, CMS8TeVP0u_Data->GetBinContent(2));
 CMS8TeVP0_Data->SetBinError(3, CMS8TeVP0u_Data->GetBinError(2));
 CMS8TeVP0_Data->SetBinContent(4, CMS8TeVP0d_Data->GetBinContent(2));
 CMS8TeVP0_Data->SetBinError(4, CMS8TeVP0d_Data->GetBinError(2));
 CMS8TeVP0_Data->SetBinContent(5, CMS8TeVP0u_Data->GetBinContent(3));
 CMS8TeVP0_Data->SetBinError(5, CMS8TeVP0u_Data->GetBinError(3));
 CMS8TeVP0_Data->SetBinContent(6, CMS8TeVP0d_Data->GetBinContent(3));
 CMS8TeVP0_Data->SetBinError(6, CMS8TeVP0d_Data->GetBinError(3));
 CMS8TeVP0_Data->SetBinContent(7, CMS8TeVP0u_Data->GetBinContent(4));
 CMS8TeVP0_Data->SetBinError(7, CMS8TeVP0u_Data->GetBinError(4));
 CMS8TeVP0_Data->SetBinContent(8, CMS8TeVP0d_Data->GetBinContent(4));
 CMS8TeVP0_Data->SetBinError(8, CMS8TeVP0d_Data->GetBinError(4));


 CMS8TeVP0_DataVector.push_back(CMS8TeVP0u_Theory.at(0)->GetBinContent(1));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0d_Theory.at(0)->GetBinContent(1));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0u_Theory.at(0)->GetBinContent(2));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0d_Theory.at(0)->GetBinContent(2));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0u_Theory.at(0)->GetBinContent(3));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0d_Theory.at(0)->GetBinContent(3));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0u_Theory.at(0)->GetBinContent(4));
 CMS8TeVP0_DataVector.push_back(CMS8TeVP0d_Theory.at(0)->GetBinContent(4));


 D05fbP0_Theory.resize(D05fbP0u_Theory.size());
 D05fbP0Delta_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0_bin1_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0_bin2_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0_bin3_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0_bin4_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0u_bin1_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0d_bin1_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0Delta_bin1_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0u_bin2_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0d_bin2_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0Delta_bin2_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0u_bin3_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0d_bin3_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0Delta_bin3_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0u_bin4_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0d_bin4_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0Delta_bin4_Theory.resize(D05fbP0u_Theory.size());
 CMS8TeVP0_Theory.resize(D05fbP0u_Theory.size());

 for(int i = 0; i < D05fbP0_Theory.size(); i++){
   D05fbP0_Theory.at(i) = new TH1D((TString)"D05fbP0_Theory" + (int)i, (TString)"D05fbP0_Theory" + (int)i, 2, 0, 2);
   D05fbP0_Theory.at(i)->SetBinContent(1, D05fbP0u_Theory.at(i)->GetBinContent(1));
   D05fbP0_Theory.at(i)->SetBinError(1, D05fbP0u_Theory.at(i)->GetBinError(1));
   D05fbP0_Theory.at(i)->SetBinContent(2, D05fbP0d_Theory.at(i)->GetBinContent(1));
   D05fbP0_Theory.at(i)->SetBinError(2, D05fbP0d_Theory.at(i)->GetBinError(1));

   D05fbP0Delta_Theory.at(i) = new TH1D((TString)"D05fbP0Delta_Theory" + (int)i, (TString)"D05fbP0Delta_Theory" + (int)i, 1, 0, 1);
   D05fbP0Delta_Theory.at(i)->SetBinContent(1, D05fbP0u_Theory.at(i)->GetBinContent(1) - D05fbP0d_Theory.at(i)->GetBinContent(1));
   D05fbP0Delta_Theory.at(i)->SetBinError(1, 0.0);

   CMS8TeVP0_bin1_Theory.at(i) = new TH1D((TString)"CMS8TeVP0_bin1_Theory" + (int)i, (TString)"CMS8TeVP0_bin1_Theory" + (int)i, 2, 0, 2);
   CMS8TeVP0_bin1_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0_bin1_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(1));
   CMS8TeVP0_bin1_Theory.at(i)->SetBinContent(2, CMS8TeVP0d_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0_bin1_Theory.at(i)->SetBinError(2, CMS8TeVP0d_Theory.at(i)->GetBinError(1));
   CMS8TeVP0_bin2_Theory.at(i) = new TH1D((TString)"CMS8TeVP0_bin2_Theory" + (int)i, (TString)"CMS8TeVP0_bin2_Theory" + (int)i, 2, 0, 2);
   CMS8TeVP0_bin2_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0_bin2_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(2));
   CMS8TeVP0_bin2_Theory.at(i)->SetBinContent(2, CMS8TeVP0d_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0_bin2_Theory.at(i)->SetBinError(2, CMS8TeVP0d_Theory.at(i)->GetBinError(2));
   CMS8TeVP0_bin3_Theory.at(i) = new TH1D((TString)"CMS8TeVP0_bin3_Theory" + (int)i, (TString)"CMS8TeVP0_bin3_Theory" + (int)i, 2, 0, 2);
   CMS8TeVP0_bin3_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0_bin3_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(3));
   CMS8TeVP0_bin3_Theory.at(i)->SetBinContent(2, CMS8TeVP0d_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0_bin3_Theory.at(i)->SetBinError(2, CMS8TeVP0d_Theory.at(i)->GetBinError(3));
   CMS8TeVP0_bin4_Theory.at(i) = new TH1D((TString)"CMS8TeVP0_bin4_Theory" + (int)i, (TString)"CMS8TeVP0_bin4_Theory" + (int)i, 2, 0, 2);
   CMS8TeVP0_bin4_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0_bin4_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(4));
   CMS8TeVP0_bin4_Theory.at(i)->SetBinContent(2, CMS8TeVP0d_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0_bin4_Theory.at(i)->SetBinError(2, CMS8TeVP0d_Theory.at(i)->GetBinError(4));

   CMS8TeVP0_Theory.at(i) = new TH1D((TString)"CMS8TeVP0_Theory" + (int)i, (TString)"CMS8TeVP0_Theory" + (int)i, 8, 0, 8);
   CMS8TeVP0_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(1));
   CMS8TeVP0_Theory.at(i)->SetBinContent(2, CMS8TeVP0d_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0_Theory.at(i)->SetBinError(2, CMS8TeVP0d_Theory.at(i)->GetBinError(1));
   CMS8TeVP0_Theory.at(i)->SetBinContent(3, CMS8TeVP0u_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0_Theory.at(i)->SetBinError(3, CMS8TeVP0u_Theory.at(i)->GetBinError(2));
   CMS8TeVP0_Theory.at(i)->SetBinContent(4, CMS8TeVP0d_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0_Theory.at(i)->SetBinError(4, CMS8TeVP0d_Theory.at(i)->GetBinError(2));
   CMS8TeVP0_Theory.at(i)->SetBinContent(5, CMS8TeVP0u_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0_Theory.at(i)->SetBinError(5, CMS8TeVP0u_Theory.at(i)->GetBinError(3));
   CMS8TeVP0_Theory.at(i)->SetBinContent(6, CMS8TeVP0d_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0_Theory.at(i)->SetBinError(6, CMS8TeVP0d_Theory.at(i)->GetBinError(3));
   CMS8TeVP0_Theory.at(i)->SetBinContent(7, CMS8TeVP0u_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0_Theory.at(i)->SetBinError(7, CMS8TeVP0u_Theory.at(i)->GetBinError(4));
   CMS8TeVP0_Theory.at(i)->SetBinContent(8, CMS8TeVP0d_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0_Theory.at(i)->SetBinError(8, CMS8TeVP0d_Theory.at(i)->GetBinError(4));


   CMS8TeVP0u_bin1_Theory.at(i) = new TH1D((TString)"CMS8TeVP0u_bin1_Theory" + (int)i, (TString)"CMS8TeVP0u_bin1_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0u_bin1_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0u_bin1_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(1));
   CMS8TeVP0d_bin1_Theory.at(i) = new TH1D((TString)"CMS8TeVP0d_bin1_Theory" + (int)i, (TString)"CMS8TeVP0d_bin1_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0d_bin1_Theory.at(i)->SetBinContent(1, CMS8TeVP0d_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0d_bin1_Theory.at(i)->SetBinError(1, CMS8TeVP0d_Theory.at(i)->GetBinError(1));
   CMS8TeVP0Delta_bin1_Theory.at(i) = new TH1D((TString)"CMS8TeVP0Delta_bin1_Theory" + (int)i, (TString)"CMS8TeVP0Delta_bin1_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0Delta_bin1_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(1) - CMS8TeVP0d_Theory.at(i)->GetBinContent(1));
   CMS8TeVP0Delta_bin1_Theory.at(i)->SetBinError(1, 0.0);
   CMS8TeVP0u_bin2_Theory.at(i) = new TH1D((TString)"CMS8TeVP0u_bin2_Theory" + (int)i, (TString)"CMS8TeVP0u_bin2_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0u_bin2_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0u_bin2_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(2));
   CMS8TeVP0d_bin2_Theory.at(i) = new TH1D((TString)"CMS8TeVP0d_bin2_Theory" + (int)i, (TString)"CMS8TeVP0d_bin2_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0d_bin2_Theory.at(i)->SetBinContent(1, CMS8TeVP0d_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0d_bin2_Theory.at(i)->SetBinError(1, CMS8TeVP0d_Theory.at(i)->GetBinError(2));
   CMS8TeVP0Delta_bin2_Theory.at(i) = new TH1D((TString)"CMS8TeVP0Delta_bin2_Theory" + (int)i, (TString)"CMS8TeVP0Delta_bin2_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0Delta_bin2_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(2) - CMS8TeVP0d_Theory.at(i)->GetBinContent(2));
   CMS8TeVP0Delta_bin2_Theory.at(i)->SetBinError(1, 0.0);
   CMS8TeVP0u_bin3_Theory.at(i) = new TH1D((TString)"CMS8TeVP0u_bin3_Theory" + (int)i, (TString)"CMS8TeVP0u_bin3_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0u_bin3_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0u_bin3_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(3));
   CMS8TeVP0d_bin3_Theory.at(i) = new TH1D((TString)"CMS8TeVP0d_bin3_Theory" + (int)i, (TString)"CMS8TeVP0d_bin3_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0d_bin3_Theory.at(i)->SetBinContent(1, CMS8TeVP0d_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0d_bin3_Theory.at(i)->SetBinError(1, CMS8TeVP0d_Theory.at(i)->GetBinError(3));
   CMS8TeVP0Delta_bin3_Theory.at(i) = new TH1D((TString)"CMS8TeVP0Delta_bin3_Theory" + (int)i, (TString)"CMS8TeVP0Delta_bin3_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0Delta_bin3_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(3) - CMS8TeVP0d_Theory.at(i)->GetBinContent(3));
   CMS8TeVP0Delta_bin3_Theory.at(i)->SetBinError(1, 0.0);
   CMS8TeVP0u_bin4_Theory.at(i) = new TH1D((TString)"CMS8TeVP0u_bin4_Theory" + (int)i, (TString)"CMS8TeVP0u_bin4_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0u_bin4_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0u_bin4_Theory.at(i)->SetBinError(1, CMS8TeVP0u_Theory.at(i)->GetBinError(4));
   CMS8TeVP0d_bin4_Theory.at(i) = new TH1D((TString)"CMS8TeVP0d_bin4_Theory" + (int)i, (TString)"CMS8TeVP0d_bin4_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0d_bin4_Theory.at(i)->SetBinContent(1, CMS8TeVP0d_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0d_bin4_Theory.at(i)->SetBinError(1, CMS8TeVP0d_Theory.at(i)->GetBinError(4));
   CMS8TeVP0Delta_bin4_Theory.at(i) = new TH1D((TString)"CMS8TeVP0Delta_bin4_Theory" + (int)i, (TString)"CMS8TeVP0Delta_bin4_Theory" + (int)i, 1, 0, 1);
   CMS8TeVP0Delta_bin4_Theory.at(i)->SetBinContent(1, CMS8TeVP0u_Theory.at(i)->GetBinContent(4) - CMS8TeVP0d_Theory.at(i)->GetBinContent(4));
   CMS8TeVP0Delta_bin4_Theory.at(i)->SetBinError(1, 0.0);

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 TH2D* D05fbP0_Covariance = new TH2D("D05fbP0_Covariance", "D05fbP0_Covariance", 2, 0, 2, 2, 0, 2);
 TH2D* D05fbP0_InverseCovariance = new TH2D("D05fbP0_InverseCovariance", "D05fbP0_InverseCovariance", 2, 0, 2, 2, 0, 2);
 TH2D* D05fbP0_StatCovariance = new TH2D("D05fbP0_StatCovariance", "D05fbP0_StatCovariance", 2, 0, 2, 2, 0, 2);
 TH2D* D05fbP0_Rest = new TH2D("D05fbP0_Rest", "D05fbP0_Rest", 2, 0, 2, 2, 0, 2);

 TH2D* CMS8TeVP0_bin1_Covariance = new TH2D("CMS8TeVP0_bin1_Covariance", "CMS8TeVP0_bin1_Covariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin1_InverseCovariance = new TH2D("CMS8TeVP0_bin1_InverseCovariance", "CMS8TeVP0_bin1_InverseCovariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin2_Covariance = new TH2D("CMS8TeVP0_bin2_Covariance", "CMS8TeVP0_bin2_Covariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin2_InverseCovariance = new TH2D("CMS8TeVP0_bin2_InverseCovariance", "CMS8TeVP0_bin2_InverseCovariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin3_Covariance = new TH2D("CMS8TeVP0_bin3_Covariance", "CMS8TeVP0_bin3_Covariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin3_InverseCovariance = new TH2D("CMS8TeVP0_bin3_InverseCovariance", "CMS8TeVP0_bin3_InverseCovariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin4_Covariance = new TH2D("CMS8TeVP0_bin4_Covariance", "CMS8TeVP0_bin4_Covariance", 2, 0, 2, 2, 0, 2);
 TH2D* CMS8TeVP0_bin4_InverseCovariance = new TH2D("CMS8TeVP0_bin4_InverseCovariance", "CMS8TeVP0_bin4_InverseCovariance", 2, 0, 2, 2, 0, 2);

 TH2D* CMS8TeVP0_Covariance = new TH2D("CMS8TeVP0_Covariance", "CMS8TeVP0_Covariance", 8, 0, 8, 8, 0, 8);
 TH2D* CMS8TeVP0_Covariance2 = new TH2D("CMS8TeVP0_Covariance2", "CMS8TeVP0_Covariance2", 8, 0, 8, 8, 0, 8);
 TH2D* CMS8TeVP0_InverseCovariance = new TH2D("CMS8TeVP0_InverseCovariance", "CMS8TeVP0_InverseCovariance", 8, 0, 8, 8, 0, 8);
 TH2D* CMS8TeVP0_InverseCovariance2 = new TH2D("CMS8TeVP0_InverseCovariance2", "CMS8TeVP0_InverseCovariance2", 8, 0, 8, 8, 0, 8);
 TH2D* CMS8TeVP0_StatCovariance = new TH2D("CMS8TeVP0_StatCovariance", "CMS8TeVP0_StatCovariance", 8, 0, 8, 8, 0, 8);
 TH2D* CMS8TeVP0_Rest = new TH2D("CMS8TeVP0_Rest", "CMS8TeVP0_Rest", 8, 0, 8, 8, 0, 8);


 D05fbP0_Covariance->SetBinContent(1, 1, D05fbP0_Data->GetBinError(1) * D05fbP0_Data->GetBinError(1));
 D05fbP0_Covariance->SetBinContent(1, 2, -0.957 * D05fbP0_Data->GetBinError(1) * D05fbP0_Data->GetBinError(2));
 D05fbP0_Covariance->SetBinContent(2, 1, -0.957 * D05fbP0_Data->GetBinError(2) * D05fbP0_Data->GetBinError(1));
 D05fbP0_Covariance->SetBinContent(2, 2, D05fbP0_Data->GetBinError(2) * D05fbP0_Data->GetBinError(2));

 CMS8TeVP0_bin1_Covariance->SetBinContent(1, 1, CMS8TeVP0_bin1_Data->GetBinError(1) * CMS8TeVP0_bin1_Data->GetBinError(1));
 CMS8TeVP0_bin1_Covariance->SetBinContent(1, 2, -0.9227 * CMS8TeVP0_bin1_Data->GetBinError(1) * CMS8TeVP0_bin1_Data->GetBinError(2));
 CMS8TeVP0_bin1_Covariance->SetBinContent(2, 1, -0.9227 * CMS8TeVP0_bin1_Data->GetBinError(2) * CMS8TeVP0_bin1_Data->GetBinError(1));
 CMS8TeVP0_bin1_Covariance->SetBinContent(2, 2, CMS8TeVP0_bin1_Data->GetBinError(2) * CMS8TeVP0_bin1_Data->GetBinError(2));
 CMS8TeVP0_bin2_Covariance->SetBinContent(1, 1, CMS8TeVP0_bin2_Data->GetBinError(1) * CMS8TeVP0_bin2_Data->GetBinError(1));
 CMS8TeVP0_bin2_Covariance->SetBinContent(1, 2, -0.93 * CMS8TeVP0_bin2_Data->GetBinError(1) * CMS8TeVP0_bin2_Data->GetBinError(2));
 CMS8TeVP0_bin2_Covariance->SetBinContent(2, 1, -0.93 * CMS8TeVP0_bin2_Data->GetBinError(2) * CMS8TeVP0_bin2_Data->GetBinError(1));
 CMS8TeVP0_bin2_Covariance->SetBinContent(2, 2, CMS8TeVP0_bin2_Data->GetBinError(2) * CMS8TeVP0_bin2_Data->GetBinError(2));
 CMS8TeVP0_bin3_Covariance->SetBinContent(1, 1, CMS8TeVP0_bin3_Data->GetBinError(1) * CMS8TeVP0_bin3_Data->GetBinError(1));
 CMS8TeVP0_bin3_Covariance->SetBinContent(1, 2, -0.933 * CMS8TeVP0_bin3_Data->GetBinError(1) * CMS8TeVP0_bin3_Data->GetBinError(2));
 CMS8TeVP0_bin3_Covariance->SetBinContent(2, 1, -0.933 * CMS8TeVP0_bin3_Data->GetBinError(2) * CMS8TeVP0_bin3_Data->GetBinError(1));
 CMS8TeVP0_bin3_Covariance->SetBinContent(2, 2, CMS8TeVP0_bin3_Data->GetBinError(2) * CMS8TeVP0_bin3_Data->GetBinError(2));
 CMS8TeVP0_bin4_Covariance->SetBinContent(1, 1, CMS8TeVP0_bin4_Data->GetBinError(1) * CMS8TeVP0_bin4_Data->GetBinError(1));
 CMS8TeVP0_bin4_Covariance->SetBinContent(1, 2, -0.9209 * CMS8TeVP0_bin4_Data->GetBinError(1) * CMS8TeVP0_bin4_Data->GetBinError(2));
 CMS8TeVP0_bin4_Covariance->SetBinContent(2, 1, -0.9209 * CMS8TeVP0_bin4_Data->GetBinError(2) * CMS8TeVP0_bin4_Data->GetBinError(1));
 CMS8TeVP0_bin4_Covariance->SetBinContent(2, 2, CMS8TeVP0_bin4_Data->GetBinError(2) * CMS8TeVP0_bin4_Data->GetBinError(2));

 for(int ibinx = 1; ibinx <= CMS8TeVP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= CMS8TeVP0_Covariance->GetNbinsY(); ibiny++){
     CMS8TeVP0_StatCovariance->SetBinContent(ibinx, ibiny, 0.0);
     CMS8TeVP0_StatCovariance->SetBinError(ibinx, ibiny, 0.0);
     CMS8TeVP0_Covariance->SetBinContent(ibinx, ibiny, 0.0);
     CMS8TeVP0_Covariance->SetBinError(ibinx, ibiny, 0.0);
     CMS8TeVP0_Covariance2->SetBinContent(ibinx, ibiny, 0.0);
     CMS8TeVP0_Covariance2->SetBinError(ibinx, ibiny, 0.0);
     CMS8TeVP0_InverseCovariance2->SetBinContent(ibinx, ibiny, 0.0);
     CMS8TeVP0_InverseCovariance2->SetBinError(ibinx, ibiny, 0.0);
     CMS8TeVP0_Rest->SetBinContent(ibinx, ibiny, 0.0);
     CMS8TeVP0_Rest->SetBinError(ibinx, ibiny, 0.0);
   }
 }

 for(int ibinx = 1; ibinx <= D05fbP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= D05fbP0_Covariance->GetNbinsY(); ibiny++){
     D05fbP0_StatCovariance->SetBinContent(ibinx, ibiny, 0.0);
     D05fbP0_StatCovariance->SetBinError(ibinx, ibiny, 0.0);
     D05fbP0_Rest->SetBinContent(ibinx, ibiny, 0.0);
     D05fbP0_Rest->SetBinError(ibinx, ibiny, 0.0);
   }
 }

 CMS8TeVP0_Covariance->SetBinContent(1, 1, CMS8TeVP0_bin1_Covariance->GetBinContent(1, 1));
 CMS8TeVP0_Covariance->SetBinContent(1, 2, CMS8TeVP0_bin1_Covariance->GetBinContent(1, 2));
 CMS8TeVP0_Covariance->SetBinContent(2, 1, CMS8TeVP0_bin1_Covariance->GetBinContent(2, 1));
 CMS8TeVP0_Covariance->SetBinContent(2, 2, CMS8TeVP0_bin1_Covariance->GetBinContent(2, 2));
 CMS8TeVP0_Covariance->SetBinContent(3, 3, CMS8TeVP0_bin2_Covariance->GetBinContent(1, 1));
 CMS8TeVP0_Covariance->SetBinContent(3, 4, CMS8TeVP0_bin2_Covariance->GetBinContent(1, 2));
 CMS8TeVP0_Covariance->SetBinContent(4, 3, CMS8TeVP0_bin2_Covariance->GetBinContent(2, 1));
 CMS8TeVP0_Covariance->SetBinContent(4, 4, CMS8TeVP0_bin2_Covariance->GetBinContent(2, 2));
 CMS8TeVP0_Covariance->SetBinContent(5, 5, CMS8TeVP0_bin3_Covariance->GetBinContent(1, 1));
 CMS8TeVP0_Covariance->SetBinContent(5, 6, CMS8TeVP0_bin3_Covariance->GetBinContent(1, 2));
 CMS8TeVP0_Covariance->SetBinContent(6, 5, CMS8TeVP0_bin3_Covariance->GetBinContent(2, 1));
 CMS8TeVP0_Covariance->SetBinContent(6, 6, CMS8TeVP0_bin3_Covariance->GetBinContent(2, 2));
 CMS8TeVP0_Covariance->SetBinContent(7, 7, CMS8TeVP0_bin4_Covariance->GetBinContent(1, 1));
 CMS8TeVP0_Covariance->SetBinContent(7, 8, CMS8TeVP0_bin4_Covariance->GetBinContent(1, 2));
 CMS8TeVP0_Covariance->SetBinContent(8, 7, CMS8TeVP0_bin4_Covariance->GetBinContent(2, 1));
 CMS8TeVP0_Covariance->SetBinContent(8, 8, CMS8TeVP0_bin4_Covariance->GetBinContent(2, 2));

 double D0_CustomStatUnc = 0.00000001;
 double CMS_bin1_CustomStatUnc = 0.00000001;
 double CMS_bin2_CustomStatUnc = 0.00000001;
 double CMS_bin3_CustomStatUnc = 0.00000001;
 double CMS_bin4_CustomStatUnc = 0.00000001;

 D0_CustomStatUnc = GetCustomStatUnc(D05fbP0_Data->GetBinError(1), D05fbP0_Data->GetBinError(2), -0.957, -0.9571);
 CMS_bin1_CustomStatUnc = GetCustomStatUnc(CMS8TeVP0_bin1_Data->GetBinError(1), CMS8TeVP0_bin1_Data->GetBinError(2), -0.9227, -0.9228);
 CMS_bin2_CustomStatUnc = GetCustomStatUnc(CMS8TeVP0_bin2_Data->GetBinError(1), CMS8TeVP0_bin2_Data->GetBinError(2), -0.93, -0.9301);
 CMS_bin3_CustomStatUnc = GetCustomStatUnc(CMS8TeVP0_bin3_Data->GetBinError(1), CMS8TeVP0_bin3_Data->GetBinError(2), -0.933, -0.9331);
 CMS_bin4_CustomStatUnc = GetCustomStatUnc(CMS8TeVP0_bin4_Data->GetBinError(1), CMS8TeVP0_bin4_Data->GetBinError(2), -0.9209, -0.9210);

 cout<<"D0_CustomStatUnc: "<<sqrt(D0_CustomStatUnc)<<endl;
 cout<<"CMS_bin1_CustomStatUnc: "<<sqrt(CMS_bin1_CustomStatUnc)<<endl;
 cout<<"CMS_bin2_CustomStatUnc: "<<sqrt(CMS_bin2_CustomStatUnc)<<endl;
 cout<<"CMS_bin3_CustomStatUnc: "<<sqrt(CMS_bin3_CustomStatUnc)<<endl;
 cout<<"CMS_bin4_CustomStatUnc: "<<sqrt(CMS_bin4_CustomStatUnc)<<endl;


 CMS8TeVP0_StatCovariance->SetBinContent(1, 1, CMS_bin1_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(2, 2, CMS_bin1_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(3, 3, CMS_bin2_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(4, 4, CMS_bin2_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(5, 5, CMS_bin3_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(6, 6, CMS_bin3_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(7, 7, CMS_bin4_CustomStatUnc);
 CMS8TeVP0_StatCovariance->SetBinContent(8, 8, CMS_bin4_CustomStatUnc);

 cout<<"CMS P0 Error:"<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin1_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin1_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin2_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin2_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin3_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin3_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin4_CustomStatUnc)<<endl;
 cout<<fixed<<setprecision(10)<<sqrt(CMS_bin4_CustomStatUnc)<<endl;

 cout<<"D0 P0 Error:"<<endl;
 cout<<sqrt(D0_CustomStatUnc)<<endl;
 cout<<sqrt(D0_CustomStatUnc)<<endl;

 D05fbP0_StatCovariance->SetBinContent(1, 1, D0_CustomStatUnc);
 D05fbP0_StatCovariance->SetBinContent(2, 2, D0_CustomStatUnc);

 for(int ibinx = 1; ibinx <= CMS8TeVP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= CMS8TeVP0_Covariance->GetNbinsY(); ibiny++){
     CMS8TeVP0_Rest->SetBinContent(ibinx, ibiny, CMS8TeVP0_Covariance->GetBinContent(ibinx, ibiny) - CMS8TeVP0_StatCovariance->GetBinContent(ibinx, ibiny));
//     CMS8TeVP0_Rest->SetBinContent(ibinx, ibiny, CMS8TeVP0_Covariance->GetBinContent(ibinx, ibiny));
   }
 }

 for(int ibinx = 1; ibinx <= D05fbP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= D05fbP0_Covariance->GetNbinsY(); ibiny++){
     D05fbP0_Rest->SetBinContent(ibinx, ibiny, D05fbP0_Covariance->GetBinContent(ibinx, ibiny) - D05fbP0_StatCovariance->GetBinContent(ibinx, ibiny));
//     D05fbP0_Rest->SetBinContent(ibinx, ibiny, D05fbP0_Covariance->GetBinContent(ibinx, ibiny));
   }
 }

 cout<<"CMS:"<<endl;

 for(int ibinx = 1; ibinx <= CMS8TeVP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= CMS8TeVP0_Covariance->GetNbinsY(); ibiny++){
     cout<<setw(6)<<fixed<<setprecision(6)<<CMS8TeVP0_Rest->GetBinContent(ibinx, ibiny)<<"   ";
   }
   cout<<endl;
 }

 cout<<"D0:"<<endl;
 for(int ibinx = 1; ibinx <= D05fbP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= D05fbP0_Covariance->GetNbinsY(); ibiny++){
     cout<<setw(6)<<fixed<<setprecision(6)<<D05fbP0_Rest->GetBinContent(ibinx, ibiny)<<"   ";
   }
   cout<<endl;
 }

 TMatrixD CMS_MatrixD(8, 8);
 TMatrixD D0_MatrixD(2, 2);

 for(int ibinx = 1; ibinx <= CMS8TeVP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= CMS8TeVP0_Covariance->GetNbinsY(); ibiny++){
     CMS_MatrixD[ibinx - 1][ibiny - 1] = CMS8TeVP0_Rest->GetBinContent(ibinx, ibiny);
   }
 }

 for(int ibinx = 1; ibinx <= D05fbP0_Covariance->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= D05fbP0_Covariance->GetNbinsY(); ibiny++){
     D0_MatrixD[ibinx - 1][ibiny - 1] = D05fbP0_Rest->GetBinContent(ibinx, ibiny);
   }
 }

 CMS8TeVP0_InverseCovariance2->SetBinContent(1, 1, 6.74607E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(1, 2, 6.16943E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(2, 1, 6.16943E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(2, 2, 6.62702E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(3, 3, 1.73029E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(3, 4, 1.48067E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(4, 3, 1.48067E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(4, 4, 1.46496E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(5, 5, 1.56110E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(5, 6, 1.23603E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(6, 5, 1.23603E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(6, 6, 1.12423E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(7, 7, 1.80526E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(7, 8, 1.89166E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(8, 7, 1.89166E+04);
 CMS8TeVP0_InverseCovariance2->SetBinContent(8, 8, 2.33739E+04);



 Decomposition(D05fbP0_DataVector, D0_MatrixD);
 Decomposition(CMS8TeVP0_DataVector, CMS_MatrixD);




 CalculateInverseMatrix(D05fbP0_Covariance, D05fbP0_InverseCovariance);
 CalculateInverseMatrix(CMS8TeVP0_bin1_Covariance, CMS8TeVP0_bin1_InverseCovariance);
 CalculateInverseMatrix(CMS8TeVP0_bin2_Covariance, CMS8TeVP0_bin2_InverseCovariance);
 CalculateInverseMatrix(CMS8TeVP0_bin3_Covariance, CMS8TeVP0_bin3_InverseCovariance);
 CalculateInverseMatrix(CMS8TeVP0_bin4_Covariance, CMS8TeVP0_bin4_InverseCovariance);
 CalculateInverseMatrix(CMS8TeVP0_Covariance, CMS8TeVP0_InverseCovariance);
 CalculateInverseMatrix(CMS8TeVP0_InverseCovariance2, CMS8TeVP0_Covariance2);



/* cout<<"Check inverse:"<<endl;
 cout<<""<<endl;
 cout<<"Inverse ePump Result:"<<endl;
 for(int ibinx = 1; ibinx <= CMS8TeVP0_Covariance2->GetNbinsX(); ibinx++){
   for(int ibiny = 1; ibiny <= CMS8TeVP0_Covariance2->GetNbinsY(); ibiny++){
     cout<<setw(6)<<fixed<<setprecision(6)<<CMS8TeVP0_Covariance2->GetBinContent(ibinx, ibiny)<<"   ";
   }
   cout<<endl;
 }
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 FileForEPUMP* file_D05fbP0 = new FileForEPUMP("D05fbP0");
 file_D05fbP0->InputData(D05fbP0_Data);
 file_D05fbP0->InputTheory(D05fbP0_Theory);
 file_D05fbP0->InputCovarianceMatrix(D05fbP0_InverseCovariance);
 file_D05fbP0->writedata();
 file_D05fbP0->writetheory();

 FileForEPUMP* file_CMS8TeVP0_bin1 = new FileForEPUMP("CMS8TeVP0_bin1");
 file_CMS8TeVP0_bin1->InputData(CMS8TeVP0_bin1_Data);
 file_CMS8TeVP0_bin1->InputTheory(CMS8TeVP0_bin1_Theory);
 file_CMS8TeVP0_bin1->InputCovarianceMatrix(CMS8TeVP0_bin1_InverseCovariance);
 file_CMS8TeVP0_bin1->writedata();
 file_CMS8TeVP0_bin1->writetheory();

 FileForEPUMP* file_CMS8TeVP0_bin2 = new FileForEPUMP("CMS8TeVP0_bin2");
 file_CMS8TeVP0_bin2->InputData(CMS8TeVP0_bin2_Data);
 file_CMS8TeVP0_bin2->InputTheory(CMS8TeVP0_bin2_Theory);
 file_CMS8TeVP0_bin2->InputCovarianceMatrix(CMS8TeVP0_bin2_InverseCovariance);
 file_CMS8TeVP0_bin2->writedata();
 file_CMS8TeVP0_bin2->writetheory();

 FileForEPUMP* file_CMS8TeVP0_bin3 = new FileForEPUMP("CMS8TeVP0_bin3");
 file_CMS8TeVP0_bin3->InputData(CMS8TeVP0_bin3_Data);
 file_CMS8TeVP0_bin3->InputTheory(CMS8TeVP0_bin3_Theory);
 file_CMS8TeVP0_bin3->InputCovarianceMatrix(CMS8TeVP0_bin3_InverseCovariance);
 file_CMS8TeVP0_bin3->writedata();
 file_CMS8TeVP0_bin3->writetheory();

 FileForEPUMP* file_CMS8TeVP0_bin4 = new FileForEPUMP("CMS8TeVP0_bin4");
 file_CMS8TeVP0_bin4->InputData(CMS8TeVP0_bin4_Data);
 file_CMS8TeVP0_bin4->InputTheory(CMS8TeVP0_bin4_Theory);
 file_CMS8TeVP0_bin4->InputCovarianceMatrix(CMS8TeVP0_bin4_InverseCovariance);
 file_CMS8TeVP0_bin4->writedata();
 file_CMS8TeVP0_bin4->writetheory();

 FileForEPUMP* file_CMS8TeVP0 = new FileForEPUMP("CMS8TeVP0");
 file_CMS8TeVP0->InputData(CMS8TeVP0_Data);
 file_CMS8TeVP0->InputTheory(CMS8TeVP0_Theory);
 file_CMS8TeVP0->InputCovarianceMatrix(CMS8TeVP0_InverseCovariance);
 file_CMS8TeVP0->writedata();
 file_CMS8TeVP0->writetheory();

 FileForEPUMP* file_D05fbAFB = new FileForEPUMP("D05fbAFB");
 file_D05fbAFB->InputData(D05fbAFB_Theory.at(0));
 file_D05fbAFB->writedata();

 FileForEPUMP* file_CMS8TeVAFB = new FileForEPUMP("CMS8TeVAFB");
 file_CMS8TeVAFB->InputData(CMS8TeVAFB_Theory.at(0));
 file_CMS8TeVAFB->writedata();

/*
 PDFReweight* PDFPlot = new PDFReweight();
 PDFPlot->openFile("Dilution.root");
 PDFPlot->InitialPDF("CT18NNLO", 0);
 PDFPlot->DrawPartonCorrelation(D05fbP0u_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(D05fbP0d_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(D05fbP0Delta_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin1_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin1_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin1_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin2_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin2_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin2_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin3_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin3_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin3_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0u_bin4_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0d_bin4_Theory, 41, 58, "Symmetry");
 PDFPlot->DrawPartonCorrelation(CMS8TeVP0Delta_bin4_Theory, 41, 58, "Symmetry");
 PDFPlot->SaveFile();
*/

 file->Write();
 file->Close();

 return 1;
}
