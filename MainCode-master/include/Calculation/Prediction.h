#ifndef Calculation_Prediction_h
#define Calculation_Prediction_h

#include "RootCommon.h"

#ifdef USE_APPLGRID
#include "Calculation/ApplGridHelper.h"
#endif

#include "Calculation/CalcDIS.h"
#include "Calculation/CalcVBP.h"

#ifdef USE_FNLO
#include "Calculation/FastNLOHelper.h"

class Prediction : public ApplGridHelper, public FastNLOHelper, public CalcDIS, public CalcVBP
{
 public:

 Prediction(std::string tablename) : FastNLOHelper(tablename) {}

 Prediction();
};

#endif

#endif
