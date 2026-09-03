#ifndef CTEQHelper_sumReader_h
#define CTEQHelper_sumReader_h

#include "RootCommon.h"
#include "Tools/Tools.h"

using namespace std;

class sumReader
{
 public:

 ifstream data;

 TString FileName;

 int RUNS, PTS;
 double Chi2Wt, C_dof, Chi2R, Chi2F0, Chi2F, Chi2X;
 double LM_Var1, LM_Data1, LM_Coef1;

 sumReader();
 virtual void Initialize(const char* name);
};
#endif
