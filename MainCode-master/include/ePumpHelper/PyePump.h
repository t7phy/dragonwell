#ifndef ePumpHelper_PyePump_h
#define ePumpHelper_PyePump_h

#include "ePumpHelper/ePumpHelper.h"

class PyePump
{
 public:

 ePumpHelper* EU;
 bool isUpdatePDFOnly = false;

 TFile* writefile = 0;

 bool doCorrelationCosine = false;

 PyePump();
 ~PyePump();

 void Initialize(const char* name);
 void Update();
 void UpdateAlphaS(const char* name);
 void UpdateParameter(const char* name);
 void InputLMScanDrawList(std::vector<std::string> list);
 void PDFLMScanModule(int flavor, double x, double Q, int isUpdate);
 void LMScanModule(const char* name, int iPoint, int isUpdate, const char* legend);
 void UpdateAlphaSLMScanPDF(int flavor, double x, double Q);
 void UpdateAlphaSLMScanObservable(const char* name, int iPoint, const char* legend);
 void AlphaSObservableCorrelation(const char* name, int iPoint, const char* legend);
 void InputL2SensitivityDrawList(std::vector<std::string> list);
 void DrawL2Sensitivity(int flavor, double x, double Q, int isUpdate);

 void SetLegend(const char* name, const char* legend);

 void TurnOnCorrelationCosine();
 double GetOldTheory(const char* DataName, int i);
 double GetNewTheory(const char* DataName, int i);
 double GetOldPDFError(const char* DataName, int i);
 double GetNewPDFError(const char* DataName, int i);
 double GetOldPDFCorrelation(const char* DataName1, const char* DataName2, int i, int j);
 double GetNewPDFCorrelation(const char* DataName1, const char* DataName2, int i, int j);
 double GetOldChi2(const char* DataName);
 double GetNewChi2(const char* DataName);
 double GetOldAlphaS();
 double GetNewAlphaS();
 double GetOldAlphaSError();
 double GetNewAlphaSError();
};
#endif
