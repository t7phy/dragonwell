#include "ePumpHelper/PyePump.h"

PyePump::PyePump()
{

}

PyePump::~PyePump()
{
 if(writefile){
   writefile->Write();
   writefile->Close();
 }
}

void PyePump::Initialize(const char* name)
{
 writefile = new TFile("ePumpUpdate.root", "RECREATE");
 writefile->cd();

 EU = new ePumpHelper(name);
 EU->LinkFile(writefile);
}

void PyePump::Update()
{
 EU->Initial();
 if(!doCorrelationCosine) EU->TurnOffCorrelationCosine();
 EU->Update();

 isUpdatePDFOnly = true;
}

void PyePump::UpdateAlphaS(const char* name)
{
 if(!isUpdatePDFOnly){
   cout<<"Please run Update first"<<endl;
   return;
 }

 EU->ReadAlphaSInput(name);
}

void PyePump::UpdateParameter(const char* name)
{
 if(!isUpdatePDFOnly){
   cout<<"Please run Update first"<<endl;
   return;
 }

 EU->ReadParameterInput(name);
}

void PyePump::InputLMScanDrawList(std::vector<std::string> list)
{
 vector<TString> LMScanDrawList(list.size());

 for(int i = 0; i < list.size(); i++){
   LMScanDrawList.at(i) = list.at(i).c_str();
 }

 EU->InputLMScanDrawList(LMScanDrawList);
}

void PyePump::PDFLMScanModule(int flavor, double x, double Q, int isUpdate)
{
 EU->PDFLMScanModule(flavor, x, Q, isUpdate);
}

void PyePump::LMScanModule(const char* name, int iPoint, int isUpdate, const char* legend)
{
 EU->LMScanModule(name, iPoint, isUpdate, legend);
}

void PyePump::UpdateAlphaSLMScanPDF(int flavor, double x, double Q)
{
 EU->UpdateAlphaSLMScanPDF(flavor, x, Q);
}

void PyePump::UpdateAlphaSLMScanObservable(const char* name, int iPoint, const char* legend)
{
 EU->UpdateAlphaSLMScanObservable(name, iPoint, legend);
}

void PyePump::AlphaSObservableCorrelation(const char* name, int iPoint, const char* legend)
{
 EU->AlphaSObservableCorrelation(name, iPoint, legend);
}

void PyePump::InputL2SensitivityDrawList(std::vector<std::string> list)
{
 vector<TString> L2SensitivityDrawList(list.size());

 for(int i = 0; i < list.size(); i++){
   L2SensitivityDrawList.at(i) = list.at(i).c_str();
 }

 EU->InputL2SensitivityDrawList(L2SensitivityDrawList);
}

void PyePump::DrawL2Sensitivity(int flavor, double x, double Q, int isUpdate)
{
 if(isUpdate) EU->DrawUpdatedL2();

 EU->DrawL2SensitivityAll(flavor, Q);
 EU->CalcL2Sensitivity(flavor, x, Q);
}

void PyePump::SetLegend(const char* name, const char* legend)
{
 EU->SetLegend(name, legend);
}

void PyePump::TurnOnCorrelationCosine()
{
 doCorrelationCosine = true;
}

double PyePump::GetOldTheory(const char* DataName, int i)
{
 return EU->GetOldTheory(DataName, i);
}

double PyePump::GetNewTheory(const char* DataName, int i)
{
 return EU->GetNewTheory(DataName, i);
}

double PyePump::GetOldPDFError(const char* DataName, int i)
{
 return EU->GetOldPDFError(DataName, i);
}

double PyePump::GetNewPDFError(const char* DataName, int i)
{
 return EU->GetNewPDFError(DataName, i);
}

double PyePump::GetOldPDFCorrelation(const char* DataName1, const char* DataName2, int i, int j)
{
 return EU->GetOldPDFCorrelation(DataName1, DataName2, i, j);
}

double PyePump::GetNewPDFCorrelation(const char* DataName1, const char* DataName2, int i, int j)
{
 return EU->GetNewPDFCorrelation(DataName1, DataName2, i, j);
}

double PyePump::GetOldChi2(const char* DataName)
{
 return EU->GetOldChi2(DataName);
}

double PyePump::GetNewChi2(const char* DataName)
{
 return EU->GetNewChi2(DataName);
}

double PyePump::GetOldAlphaS()
{
 return EU->Old_AlphaS_GA;
}

double PyePump::GetNewAlphaS()
{
 return EU->New_AlphaS_GA;
}

double PyePump::GetOldAlphaSError()
{
 return EU->Old_Delta_AlphaS;
}

double PyePump::GetNewAlphaSError()
{
 return EU->New_Delta_AlphaS;
}

