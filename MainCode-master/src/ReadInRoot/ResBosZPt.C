#include "ReadInRoot/ResBosZPt.h"

using namespace std;

ResBosZPt::ResBosZPt()
{
}

ResBosZPt::ResBosZPt(TString FileName)
{
 openFile(FileName);
}

void ResBosZPt::LinkHist(HistsResBos* &myhists)
{
 this->myhists = myhists;
}

void ResBosZPt::WriteIn(TH1D* h1, int MaxColumn, bool isPercent)
{
 while(getline(infile, FileLine)){
   if(FileLine.find("#")!=std::string::npos){
     cout<<FileLine<<endl;
   }
   else{
     break;
   }
 }


 char* myDataLine;
 const char* split = ",";

 double* ePumpStaErr = new double[h1->GetNbinsX()];
 double* ePumpSysErr = new double[h1->GetNbinsX()];
 double* ePumpCorrSysErr = new double[h1->GetNbinsX()];

 int ibin = 0;

 do{
   ibin++;

   myDataLine = (char *)FileLine.c_str();

   char* WholeLine = strtok(myDataLine, split);

   if(MaxColumn == 8 || MaxColumn == 10){
     for(int i = 1; i <= MaxColumn; i++){
       para = stod(WholeLine);
       if(i == 4) DataPoint = para;
       if(i == 5) StaErr = para;
       if(i == 7) UnCorrSysErr = para;
       if(i == 9) CorrSysErr = para;

       WholeLine = strtok(NULL, split);
     }
   }
   else if(MaxColumn == 4){
     for(int i = 1; i <= MaxColumn; i++){
       para = stod(WholeLine);
       if(i == 2) DataPoint = para;
       if(i == 3) StaErr = para;

       WholeLine = strtok(NULL, split);
     }
   }
   else if(MaxColumn == 6){
     for(int i = 1; i <= MaxColumn; i++){
       para = stod(WholeLine);
       if(i == 4) DataPoint = para;
       if(i == 5) StaErr = para;
   
       WholeLine = strtok(NULL, split);
     }
   }

   //cout<<"DataPoint = "<<DataPoint<<" StaErr = "<<StaErr<<" SysErr = "<<UnCorrSysErr<<" RegBias = "<<CorrSysErr<<endl;

   if(isPercent){
     StaErr = DataPoint * StaErr / 100.0;
     UnCorrSysErr = DataPoint * UnCorrSysErr / 100.0;
     CorrSysErr = DataPoint * CorrSysErr / 100.0;
     LumiErr = DataPoint / 100.0;
   }

   h1->SetBinContent(ibin, DataPoint);
   //h1->SetBinError(ibin, sqrt(StaErr * StaErr + UnCorrSysErr * UnCorrSysErr + CorrSysErr * CorrSysErr + LumiErr * LumiErr));
   h1->SetBinError(ibin, sqrt(StaErr * StaErr + UnCorrSysErr * UnCorrSysErr));

   ePumpStaErr[ibin - 1] = StaErr;
   ePumpSysErr[ibin - 1] = UnCorrSysErr;
   ePumpCorrSysErr[ibin - 1] = CorrSysErr / DataPoint * 100.0;

   if(isOutput){
     cout<<fixed<<setprecision(4)<<QMin<<"  ";
     cout<<fixed<<setprecision(4)<<QMax<<"  ";
     cout<<fixed<<setprecision(2)<<yMin<<"  ";
     cout<<fixed<<setprecision(2)<<yMax<<"  ";
     cout<<fixed<<setprecision(4)<<h1->GetBinCenter(ibin)<<"  ";
     cout<<fixed<<setprecision(4)<<h1->GetXaxis()->GetBinLowEdge(ibin)<<"  ";
     cout<<fixed<<setprecision(4)<<h1->GetXaxis()->GetBinUpEdge(ibin)<<"  ";
     cout<<scientific<<uppercase<<setprecision(3)<<DataPoint<<"  ";
     cout<<scientific<<uppercase<<setprecision(3)<<StaErr<<"  ";
     cout<<fixed<<setprecision(3)<<UnCorrSysErr / DataPoint * 100.0<<"  ";
     cout<<fixed<<setprecision(3)<<CorrSysErr / DataPoint * 100.0<<"  "<<endl;
   }
 } while(infile>>FileLine);

 FileForEPUMP* file = new FileForEPUMP(h1->GetName());
 file->InputData(h1);
 file->InputStaErr(ePumpStaErr);
 file->InputSysErr(ePumpSysErr);
 file->InputCorrSysErr(ePumpCorrSysErr, "CorrErr");
 file->writedata();

 infile.close();
}

void ResBosZPt::ReadKFactor(TH1D* h1, TString NNLOName, TString NLOName)
{
 ifstream NNLOFile;
  NNLOFile.open(NNLOName);

 ifstream NLOFile;
  NLOFile.open(NLOName);

 for(int i = 0; i < 3; i++){
   getline(NNLOFile, FileLine);
   cout<<FileLine<<endl;
 }

 for(int i = 0; i < 3; i++){
   getline(NLOFile, FileLine);
   cout<<FileLine<<endl;
 }

/*
 while(getline(NNLOFile, FileLine)){
   if(FileLine.find("#")!=std::string::npos){
     cout<<FileLine<<endl;
   }
   else{
     break;
   }
 }

 while(getline(NLOFile, FileLine)){
   if(FileLine.find("#")!=std::string::npos){
     cout<<FileLine<<endl;
   } 
   else{
     break;
   }
 }
*/

 TH1D* NNLOHist = (TH1D *)h1->Clone((TString)h1->GetName() + (TString)"_NNLO");
 TH1D* NLOHist = (TH1D *)h1->Clone((TString)h1->GetName() + (TString)"_NLO");

 double skip = 0.0;
 int ibin = 0;
 while(NNLOFile >> skip){
   ibin++;
   NNLOFile >> skip >> skip;
   NNLOFile >> DataPoint;
   NNLOFile >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip;
   NNLOHist->SetBinContent(ibin, DataPoint);
   NNLOHist->SetBinError(ibin, 0.0);
 }

 ibin = 0;
 while(NLOFile >> skip){
   ibin++;
   NLOFile >> skip >> skip;
   NLOFile >> DataPoint;
   NLOFile >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip >> skip;
   NLOHist->SetBinContent(ibin, DataPoint);
   NLOHist->SetBinError(ibin, 0.0);
 }

 for(int ibin = 1; ibin <= h1->GetNbinsX(); ibin++){
   h1->SetBinContent(ibin, NNLOHist->GetBinContent(ibin) / NLOHist->GetBinContent(ibin));
   h1->SetBinError(ibin, 0.0);
 }

 delete NNLOHist;
 delete NLOHist;

 NNLOFile.close();
 NLOFile.close();
}

void ResBosZPt::GetTable(int id, TString y)
{
 for(int i = 0; i < 10; i++){
   getline(infile, FileLine);
   //cout<<FileLine<<endl;
 }

 char* myDataLine;
 const char* split = ",";

 int ibin = 0;

 while(infile>>FileLine){
   ibin++;

   myDataLine = (char *)FileLine.c_str();

   char* WholeLine = strtok(myDataLine, split);

   for(int i = 1; i <= 10; i++){
     para = stod(WholeLine);
     if(i == 1) pTPoint = para;
     if(i == 4) DataPoint = para;
     if(i == 5) StaErr = para;
     if(i == 7) UnCorrSysErr = para;
     if(i == 9) CorrSysErr = para;

     WholeLine = strtok(NULL, split);
   }
   StaErr = DataPoint * StaErr / 100.0;
   UnCorrSysErr = DataPoint * UnCorrSysErr / 100.0;
   LumiErr = CorrSysErr;

   if(pTPoint < 20.0){
     cout<<id<<"  ";
     cout<<fixed<<setprecision(3)<<91.187<<"  "<<91.187<<"  ";
     cout<<setw(5)<<*right<<fixed<<setprecision(3)<<pTPoint<<"  ";
     cout<<uppercase<<scientific<<setprecision(3)<<DataPoint<<"  ";
     cout<<uppercase<<scientific<<sqrt(StaErr * StaErr + UnCorrSysErr * UnCorrSysErr) * 1<<"  "<<"0.000E+00"<<"  "<<"0.000E+00"<<"   ";
     cout<<fixed<<setprecision(2)<<LumiErr<<"  "<<y<<"  "<<"9.119E+01"<<"   ";
     cout<<fixed<<setprecision(2)<<KFactor->GetBinContent(ibin)<<"  ";
     cout<<fixed<<setprecision(8)<<Efficiency->GetBinContent(ibin) * 0.03<<endl;

     DataPoints.push_back(DataPoint);
     DataErrors.push_back(sqrt(StaErr * StaErr + UnCorrSysErr * UnCorrSysErr) * 1);
     StaErrors.push_back(StaErr);
     UnCorrErrors.push_back(UnCorrSysErr);
     CorrErrors.push_back(CorrSysErr);
   }

 }

}

void ResBosZPt::InputDataFile(TString FileName_y1, TString FileName_y2)
{
 DataFile_y1 = new TFile(FileName_y1);
 DataFile_y2 = new TFile(FileName_y2); 
}

void ResBosZPt::GetEfficiency(TString histName)
{
 Efficiency = (TH1D *)DataFile_y2->Get(histName);
}

void ResBosZPt::GetKFactor(TString histName)
{
 TH1D *y2 = (TH1D *)DataFile_y2->Get(histName);
 TH1D *y1 = (TH1D *)DataFile_y1->Get(histName);

 KFactor = (TH1D *)y2->Clone("KFactor");
 KFactor->Divide(y1);

}

void ResBosZPt::GetDataAndErr(vector<double> &DataPoints, vector<double> &DataErrors)
{
 DataPoints = this->DataPoints;
 DataErrors = this->DataErrors;
}

void ResBosZPt::GetFullTable(vector<double> &DataPoints, vector<double> &StaErrors, vector<double> &UnCorrErrors, vector<double> &CorrErrors)
{
 DataPoints = this->DataPoints;
 StaErrors = this->StaErrors;
 UnCorrErrors = this->UnCorrErrors;
 CorrErrors = this->CorrErrors;
}
