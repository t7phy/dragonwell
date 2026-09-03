#ifndef Calculation_Convolute_cxx
#define Calculation_Convolute_cxx

#include "RootCommon.h"
#include "Calculation/ApplGridHelper.h"
#include "Calculation/ThreadChi2.h"

void Convolute(vector<ApplGridHelper *> Theory)
{
     int TotalThread = Theory.size();

     pthread_t thread[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       cout<<"Thread No."<<j + 1<<" has created."<<endl;
       //sleep(1);
     }


     for(int j = 0; j < TotalThread; j++){
       cout<<"Thread No."<<j + 1<<" has finished."<<endl;
     }


}

#endif
