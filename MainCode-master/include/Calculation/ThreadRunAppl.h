#ifndef Calculation_ThreadRunAppl_h
#define Calculation_ThreadRunAppl_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/PineAPPLHelper.h"
#include "Calculation/Config.h"

void* ThreadRunAppl(void* arg);
void* ThreadRunApplppbar(void* arg);

void* ThreadRunPineAPPL(void* arg);
void* ThreadRunPineAPPLppbar(void* arg);

#endif
