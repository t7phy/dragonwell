#ifndef HistFormula_h
#define HistFormula_h
#include "RootCommon.h"
class HistFormula
{
 public:

 virtual void ProcessFormula();
 virtual void FindBracket(TString &formula, int &leftIndex, int &lastright, TString &subtmpformula);
 virtual void DecomposeExpression(TString &formula);
};
#endif
