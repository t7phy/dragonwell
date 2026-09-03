#include "CTEQHelper/dtaReader.h"

dtaReader::dtaReader(TString FileName)
{
 data.open(FileName.Data(), ios::in);
}

dtaReader::dtaReader(TString FileName, TString subName)
{
 data.open(FileName.Data(), ios::in);

 this->subName = subName;
}

/////////////////////////////////////////////////////////////////////////////////

//inline
double dtaReader::GetSumOfReducedChi2(int id)
{
 return SumOfReducedChi2[id];
}

//inline
double dtaReader::GetAveReducedChi2(int id)
{
 return SumOfReducedChi2[id] / (double)DataNpt[id];
}

double dtaReader::GetChi2(int id)
{
 return DataChi2[id]->GetBinContent(1);
}

double dtaReader::GetSumOfChi2()
{
 return SumOfChi2;
}

/////////////////////////////////////////////////////////////////////////////////

void dtaReader::ReadFile()
{
 for(int i = 0; i < 2; i++){
   getline(data, FileLine);
   cout<<FileLine<<endl;
 }

 getline(data, FileLine);

 while(FileLine.find("DATA SET") != std::string::npos){

   string sDataID = FileLine.substr(FileLine.find("DATA SET") + 8, FileLine.find("; NORM Fac") - FileLine.find("DATA SET") - 8);
   string sNormFac = FileLine.substr(FileLine.find("; NORM Fac =") + 12, FileLine.find("; # of pts =") - FileLine.find("; NORM Fac =") - 12);
   string sNpt = FileLine.substr(FileLine.find("; # of pts =") + 12, FileLine.find("; chi^2 =") - FileLine.find("; # of pts =") - 12);
   string sChi2 = FileLine.substr(FileLine.find("; chi^2 =") + 9, FileLine.find("S=") - FileLine.find("; chi^2 =") - 9);
   string sSpartyness = FileLine.substr(FileLine.find("S=") + 2, FileLine.find("chi^2/N =") - FileLine.find("S=") - 2);
   string sChi2N = FileLine.substr(FileLine.find("chi^2/N =") + 10);
  
   TrimString(sDataID);
   TrimString(sNormFac);
   TrimString(sNpt);
   TrimString(sChi2);
   TrimString(sSpartyness);
   TrimString(sChi2N);
  
   DataID = stoi(sDataID.c_str());
   NormFac = stod(sNormFac.c_str());
   Npt = stoi(sNpt.c_str());
   Chi2 = stod(sChi2.c_str());
   Spartyness = stod(sSpartyness.c_str());
   Chi2N = stod(sChi2N.c_str());

   SumOfChi2 += Chi2;
  
   cout<<"DATA SET "<<DataID<<" ; NORM Fac = "<<NormFac<<" ; # of pts = "<<Npt<<" ; chi^2 = "<<Chi2<<" S= "<<Spartyness<<" chi^2/N = "<<Chi2N<<endl;
  
   getline(data, FileLine);
   cout<<FileLine<<endl;
  
   const char* split = "  ";
  
   if(FileLine.find("R^2, r(k)") != std::string::npos){
     string sNuisance = FileLine.substr(FileLine.find("R^2, r(k) =") + 12);
     TrimString(sNuisance);
  
     char* myDataLine;
     myDataLine = (char *)sNuisance.c_str();
  
     char* WholeLine = strtok(myDataLine, split);
     R2 = stod(WholeLine);   
     WholeLine = strtok(NULL, split);
     double rest = R2;
     double LastR = 0.0;
     while(rest > LastR){
       double r = stod(WholeLine);
       rk.push_back(r);
       rest = rest - r * r;
       WholeLine = strtok(NULL, split);
       LastR = r * r;
       //cout<<"r = "<<r<<" rest = "<<rest<<endl;
     }
  
     getline(data, FileLine);
     cout<<FileLine<<endl;
     cout<<endl;

     HasR2[DataID] = true;
   }
   else{
     HasR2[DataID] = false;
     cout<<endl;
   }

   xQpair[sDataID.c_str()] = {};
   FillData();
  
   rk.clear();

   getline(data, FileLine);
   //cout<<FileLine<<endl;
   getline(data, FileLine);
   //cout<<FileLine<<endl;
 }

 function<void(vector<TString>, TString)> CombinexQ = [&](vector<TString> Input, TString Output){
   TList graphs;

   vector<TGraphErrors *> tmpGraphs(Input.size());

   for(int i = 0; i < Input.size(); i++){
     if(xQplot.count(Input.at(i))){
       tmpGraphs.at(i) = (TGraphErrors *)xQplot.at(Input.at(i))->Clone();
       if(i > 0) tmpGraphs.at(i)->RemovePoint(0);
     }
   }

   for(int i = 0; i < Input.size(); i++){
     if(xQplot.count(Input.at(i))) graphs.Add(tmpGraphs.at(i));
   }

   xQplot[Output] = new TGraphErrors();
   if(graphs.GetSize() != 0) xQplot.at(Output)->Merge(&graphs);
   xQplot.at(Output)->SetName((TString)"Data_" + Output + "_xQplot" + subName);
   xQplot.at(Output)->SetTitle((TString)"Data_" + Output + "_xQplot" + subName);
   if(isLinkFile) xQplot.at(Output)->Write();
 };

 CombinexQ(vector<TString>{"101", "102"}, "BCDMS");
 CombinexQ(vector<TString>{"108", "109"}, "CDHSW");

}

void dtaReader::FillData()
{
 cout<<"Fill Data"<<DataID<<":"<<endl;

 if(isLinkFile) hf->cd();

 DataNameMap[DataID] = (TString)"E" + (int)DataID;

 DataSet.push_back(DataID);
 DataNpt[DataID] = Npt;

 DataNormFac[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_NormFac" + subName, (TString)"Data" + (int)DataID + (TString)"_NormFac" + subName, 1, 0, 1);
 DataChi2[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Chi2" + subName, (TString)"Data" + (int)DataID + (TString)"_Chi2" + subName, 1, 0, 1);
 DataSpartyness[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Spartyness" + subName, (TString)"Data" + (int)DataID + (TString)"_Spartyness" + subName, 1, 0, 1);
 DataChi2N[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Chi2N" + subName, (TString)"Data" + (int)DataID + (TString)"_Chi2N" + subName, 1, 0, 1);

 Y[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Y" + subName, (TString)"Data" + (int)DataID + (TString)"_Y" + subName, Npt, 0, Npt);
 Q[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Q" + subName, (TString)"Data" + (int)DataID + (TString)"_Q" + subName, Npt, 0, Npt);
 Rs[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Rs" + subName, (TString)"Data" + (int)DataID + (TString)"_Rs" + subName, Npt, 0, Npt);
 Exp[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Exp" + subName, (TString)"Data" + (int)DataID + (TString)"_Exp" + subName, Npt, 0, Npt);
 Theory[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Theory" + subName, (TString)"Data" + (int)DataID + (TString)"_Theory" + subName, Npt, 0, Npt);
 TotErr[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_TotErr" + subName, (TString)"Data" + (int)DataID + (TString)"_TotErr" + subName, Npt, 0, Npt);
 ExpOverFit[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_ExpOverFit" + subName, (TString)"Data" + (int)DataID + (TString)"_ExpOverFit" + subName, Npt, 0, Npt);
 ErrOverFit[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_ErrOverFit" + subName, (TString)"Data" + (int)DataID + (TString)"_ErrOverFit" + subName, Npt, 0, Npt);
 ChiSq[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_ChiSq" + subName, (TString)"Data" + (int)DataID + (TString)"_ChiSq" + subName, Npt, 0, Npt);
 Shift[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_Shift" + subName, (TString)"Data" + (int)DataID + (TString)"_Shift" + subName, Npt, 0, Npt);
 ShiftedData[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_ShiftedData" + subName, (TString)"Data" + (int)DataID + (TString)"_ShiftedData" + subName, Npt, 0, Npt);
 UnCorErr[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_UnCorErr" + subName, (TString)"Data" + (int)DataID + (TString)"_UnCorErr" + subName, Npt, 0, Npt);
 ReducedChi2[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_ReducedChi2" + subName, (TString)"Data" + (int)DataID + (TString)"_ReducedChi2" + subName, Npt, 0, Npt);
 lob[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_lob" + subName, (TString)"Data" + (int)DataID + (TString)"_lob" + subName, Npt, 0, Npt);

 DataNormFac[DataID]->SetBinContent(1, NormFac);
 DataNormFac[DataID]->SetBinError(1, 0.0);

 DataChi2[DataID]->SetBinContent(1, Chi2);
 DataChi2[DataID]->SetBinError(1, 0.0);

 DataSpartyness[DataID]->SetBinContent(1, Spartyness);
 DataSpartyness[DataID]->SetBinError(1, 0.0);

 DataChi2N[DataID]->SetBinContent(1, Chi2N);
 DataChi2N[DataID]->SetBinError(1, 0.0);


 if(rk.size() != 0){
   DataR2[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_R2" + subName, (TString)"Data" + (int)DataID + (TString)"_R2" + subName, 1, 0, 1);
   Datark[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_rk" + subName, (TString)"Data" + (int)DataID + (TString)"_rk" + subName, rk.size(), 0, (double)rk.size());

   DataR2[DataID]->SetBinContent(1, R2);
   DataR2[DataID]->SetBinError(1, 0.0);

   for(int i = 0; i < rk.size(); i++){
     Datark[DataID]->SetBinContent(i + 1, rk.at(i));
     Datark[DataID]->SetBinError(i + 1, 0.0);
   }
 }
 else{
   DataR2[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_R2" + subName, (TString)"Data" + (int)DataID + (TString)"_R2" + subName, 1, 0, 1);
   Datark[DataID] = new TH1D((TString)"Data" + (int)DataID + (TString)"_rk" + subName, (TString)"Data" + (int)DataID + (TString)"_rk" + subName, 1, 0, 1);

   DataR2[DataID]->SetBinContent(1, 0.0);
   DataR2[DataID]->SetBinError(1, 0.0);
   Datark[DataID]->SetBinContent(1, 0.0);
   Datark[DataID]->SetBinError(1, 0.0);
 }

 xQplot[TString::Format("%d", DataID)] = new TGraphErrors(Npt);
 xQplot.at(TString::Format("%d", DataID))->SetName((TString)"Data" + (int)DataID + (TString)"_xQplot" + subName);
 xQplot.at(TString::Format("%d", DataID))->SetTitle((TString)"Data" + (int)DataID + (TString)"_xQplot" + subName);

 double value;

 for(int i = 1; i <= Npt; i++){
   data >> value;
   Y[DataID]->SetBinContent(i, value);
   Y[DataID]->SetBinError(i, 0.0);

   data >> value;
   Q[DataID]->SetBinContent(i, value);
   Q[DataID]->SetBinError(i, 0.0);

   if(DataID / 100 == 1){
     xQpair.at(TString::Format("%d", DataID)).push_back(make_pair(Q[DataID]->GetBinContent(i), Y[DataID]->GetBinContent(i)));
     xQplot.at(TString::Format("%d", DataID))->SetPointX(i, Q[DataID]->GetBinContent(i));
     xQplot.at(TString::Format("%d", DataID))->SetPointY(i, Y[DataID]->GetBinContent(i));
   }

   data >> value;
   Rs[DataID]->SetBinContent(i, value);
   Rs[DataID]->SetBinError(i, 0.0);

   if(DataID == 201 || DataID == 203 || DataID == 204 || DataID == 206){
     double QValue = Q[DataID]->GetBinContent(i);
     double x1Value = Q[DataID]->GetBinContent(i) / Rs[DataID]->GetBinContent(i) * exp(Y[DataID]->GetBinContent(i));
     double x2Value = Q[DataID]->GetBinContent(i) / Rs[DataID]->GetBinContent(i) * exp(Y[DataID]->GetBinContent(i) * (-1.0));

     xQpair.at(TString::Format("%d", DataID)).push_back(make_pair(x1Value, QValue));
     xQpair.at(TString::Format("%d", DataID)).push_back(make_pair(x2Value, QValue));

     xQplot.at(TString::Format("%d", DataID))->SetPointX(i, x1Value);
     xQplot.at(TString::Format("%d", DataID))->SetPointY(i, QValue);
     xQplot.at(TString::Format("%d", DataID))->SetPointX(i + Npt, x2Value);
     xQplot.at(TString::Format("%d", DataID))->SetPointY(i + Npt, QValue);
   }

   data >> value;
   Exp[DataID]->SetBinContent(i, value);
   Exp[DataID]->SetBinError(i, 0.0);

   data >> value;
   Theory[DataID]->SetBinContent(i, value);
   Theory[DataID]->SetBinError(i, 0.0);

   data >> value;
   TotErr[DataID]->SetBinContent(i, value);
   TotErr[DataID]->SetBinError(i, 0.0);

   data >> value;
   ExpOverFit[DataID]->SetBinContent(i, value);
   ExpOverFit[DataID]->SetBinError(i, 0.0);

   data >> value;
   ErrOverFit[DataID]->SetBinContent(i, value);
   ErrOverFit[DataID]->SetBinError(i, 0.0);

   data >> value;
   ChiSq[DataID]->SetBinContent(i, value);
   ChiSq[DataID]->SetBinError(i, 0.0);

   data >> value;
   Shift[DataID]->SetBinContent(i, value);
   Shift[DataID]->SetBinError(i, 0.0);

   data >> value;
   ShiftedData[DataID]->SetBinContent(i, value);
   ShiftedData[DataID]->SetBinError(i, 0.0);

   data >> value;
   UnCorErr[DataID]->SetBinContent(i, value);
   UnCorErr[DataID]->SetBinError(i, 0.0);

   data >> value;
   ReducedChi2[DataID]->SetBinContent(i, value);
   ReducedChi2[DataID]->SetBinError(i, 0.0);

   if(HasR2[DataID]){
     data >> value;
     lob[DataID]->SetBinContent(i, value);
     lob[DataID]->SetBinError(i, 0.0);
   }
   else{
     lob[DataID]->SetBinContent(i, 0.0);
     lob[DataID]->SetBinError(i, 0.0);
   }
 }

 SumOfReducedChi2[DataID] = 0.0;
 for(int ibin = 1; ibin <= ReducedChi2[DataID]->GetNbinsX(); ibin++){
   SumOfReducedChi2[DataID] += fabs(ReducedChi2[DataID]->GetBinContent(ibin));
 }

 getline(data, FileLine);

 if(isLinkFile){
   hf->cd();
   xQplot.at(TString::Format("%d", DataID))->Write();
 }
}

