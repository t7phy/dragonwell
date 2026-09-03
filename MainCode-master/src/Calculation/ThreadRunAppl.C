#include "Calculation/ThreadRunAppl.h"

void* ThreadRunAppl(void* arg)
{
 ApplGridHelper* ptr = (ApplGridHelper *)arg;

 ptr->ThreadConvoluteMacro();

 pthread_exit(NULL);
}

void* ThreadRunApplppbar(void* arg)
{
 ApplGridHelper* ptr = (ApplGridHelper *)arg;

 ptr->ThreadConvoluteppbarMacro();

 pthread_exit(NULL);
}

void* ThreadRunPineAPPL(void* arg)
{
 PineAPPLHelper* ptr = (PineAPPLHelper *)arg;

 vector<double> results = ptr->Convolute();

 pthread_exit(NULL);
}

void* ThreadRunPineAPPLppbar(void* arg)
{
 PineAPPLHelper* ptr = (PineAPPLHelper *)arg;

 vector<double> results = ptr->Convolute();

 pthread_exit(NULL);
}

