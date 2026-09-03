#ifndef ThreadChi2_cxx
#define ThreadChi2_cxx

#include "Calculation/ThreadChi2.h"

pthread_mutex_t ApplMutex = PTHREAD_MUTEX_INITIALIZER;

void* ThreadChi2(void* arg)
{
 Dataset* ptr = (Dataset *)arg;

 if(ptr->CalcMode == "ApplGrid"){
   if(pthread_mutex_lock(&ApplMutex) != 0){
     cout<<"Error: lock failed"<<endl;
   }
 }

 ptr->GetPrediction();

 if(ptr->CalcMode == "ApplGrid"){
   if(pthread_mutex_unlock(&ApplMutex) != 0){
     cout<<"Error: unlock failed"<<endl;
   }
 }

 //sleep(0.1);
 pthread_exit(NULL);

}

void* ThreadCalcChi2(void* arg)
{
 Dataset* ptr = (Dataset *)arg;

 bool is_print = false;

 if(ptr->is_print) is_print = true;

 if(is_print){
   if(pthread_mutex_lock(&ApplMutex) != 0){
     cout<<"Error: lock failed"<<endl;
   }
 }

 ptr->PrepareChi2();
 double Chi2 = ptr->Chi2(false);

 if(is_print){
   if(pthread_mutex_unlock(&ApplMutex) != 0){
     cout<<"Error: unlock failed"<<endl;
   }
 }

 //sleep(0.1);
 pthread_exit(NULL);

}

#endif
