#ifndef Common_cxx
#define Common_cxx

#include "Analysis/Common.h"

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* StartThread(void* arg)
{
 loopMC* tmp = (loopMC *)arg;
 
 if(tmp->RootType == "Wasymmetry"){
   loopWasym* ptr = (loopWasym *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile); 
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }
 
 if(tmp->RootType == "ResBos" || tmp->RootType == "ResBosEnergyScale" || tmp->RootType == "CalibrationForResBos"){
   loopResBos* ptr = (loopResBos *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile); 
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }
     
     ptr->End(ifile);
     
     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "ResBosW"){
   loopResBosW* ptr = (loopResBosW *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }
     
     ptr->End(ifile);
     
     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "ResBosWTev" || tmp->RootType == "FittingCDFSmear"){
   loopResBosWTev* ptr = (loopResBosWTev *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "Pythia"){
   loopPythia* ptr = (loopPythia *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "PythiaW"){
   loopPythiaW* ptr = (loopPythiaW *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "PythiaWW"){
   loopPythiaWW* ptr = (loopPythiaWW *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "Herwig"){
   loopHerwig* ptr = (loopHerwig *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }
 
 if(tmp->RootType == "FwdReco"){
   loopFwdReco* ptr = (loopFwdReco *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "WZPolarization"){
   loopWZPolarization* ptr = (loopWZPolarization *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->InitialSys(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "PreWZPolarization"){
   loopWZPolarization* ptr = (loopWZPolarization *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->PreLoop(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "Custom"){
   loopCustom* ptr = (loopCustom *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "CellInfo"){
   loopCellInfo* ptr = (loopCellInfo *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "SherpaWW"){
   loopSherpaWW* ptr = (loopSherpaWW *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "ResBosCMS" || tmp->RootType == "FittingCMSData"){
   loopResBosCMS* ptr = (loopResBosCMS *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "ResBosD0"){
   loopResBosD0* ptr = (loopResBosD0 *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "FlavorAsym"){
   loopFlavorAsym* ptr = (loopFlavorAsym *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "ResBosHighMassZ"){
   loopResBosHighMassZ* ptr = (loopResBosHighMassZ *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "MadGraph"){
   loopMadGraph* ptr = (loopMadGraph *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "QBH"){
   loopQBH* ptr = (loopQBH *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "PreQBH"){
   loopQBH* ptr = (loopQBH *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->PreLoop(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "HMDY"){
   loopHMDY* ptr = (loopHMDY *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "PreHMDY"){
   loopHMDY* ptr = (loopHMDY *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->PreLoop(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "ZPrime"){
   loopZPrime* ptr = (loopZPrime *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->ReadTree(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 if(tmp->RootType == "PreZPrime"){
   loopZPrime* ptr = (loopZPrime *)arg;
   for(int ifile = ptr->FirstFile; ifile < ptr->EndFile; ifile++){
     ptr->Initial(ifile);
     ptr->PreLoop(ifile);

     if(pthread_mutex_lock(&mtx) != 0){
       cout<<"Error: lock failed"<<endl;
     }

     ptr->End(ifile);

     if(pthread_mutex_unlock(&mtx) != 0){
       cout<<"Error: unlock failed"<<endl;
     }
   }
   ptr->Finish();
 }

 sleep(0.1);
 pthread_exit(NULL);
}

#endif
