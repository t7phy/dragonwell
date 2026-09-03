#ifndef ZPrime_ThreadRunZPrime_cxx
#define ZPrime_ThreadRunZPrime_cxx

#include "Analysis/Common.h"
#include "ZPrime/ZPrimetopDDHelper.h"
#include "ZPrime/ZPrimeSumOfWeight.h"

void ThreadRunZPrime(Control process, HistsZPrime* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopZPrime *Run[TotalThread];
     TreeForZPrime *ZPrimeTree[TotalThread];

     if(process.topDDList != "0" && process.topDDList != ""){
       ZPrimetopDDHelper* topDD = new ZPrimetopDDHelper();
       topDD->openFile(process.topDDFile.at(0));
       topDD->RetrieveHist(process.TransferName_ee.at(0), process.TransferName_mm.at(0));

       ZPrimetopDDHelper* topDD_HighMass_CosTheta = new ZPrimetopDDHelper(2);
       topDD_HighMass_CosTheta->openFile(process.topDDFile.at(1));
       topDD_HighMass_CosTheta->RetrieveHist(process.TransferName_ee.at(1), process.TransferName_mm.at(1));

       ZPrimetopDDHelper* topDD_HighMass_Rapidity = new ZPrimetopDDHelper(2);
       topDD_HighMass_Rapidity->openFile(process.topDDFile.at(2));
       topDD_HighMass_Rapidity->RetrieveHist(process.TransferName_ee.at(2), process.TransferName_mm.at(2));

       myhists->InputTopDD(topDD, topDD_HighMass_CosTheta, topDD_HighMass_Rapidity);
     }

     for(int j = 0; j < TotalThread; j++){
       ZPrimeTree[j] = new TreeForZPrime();
       ZPrimeTree[j]->InputFile(process.RootNames);
       ZPrimeTree[j]->InputSystematic(process.SystematicName);
       ZPrimeTree[j]->BkgSelection(process.NtupleName);
       ZPrimeTree[j]->LinkHist(myhists);

       Run[j] = new loopZPrime(process.RootType);
       if(process.ZPrimeFakeEffFile != "") Run[j]->InputFakeEff(process.ZPrimeFakeEffFile);
       if(process.ZPrimeKFactorFile != "") Run[j]->InputKFactor(process.ZPrimeKFactorFile);
       if(process.ZPrimeAngularFile != "") Run[j]->InputAngularFile(process.ZPrimeAngularFile);

       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->InputHist(myhists);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->LinkLog(process.myLog);

       if(process.isTest) Run[j]->Test();
     }

     if(process.TotalFileNumber != (ZPrimeTree[0]->RootNames).size()){
       process.TotalFileNumber = (ZPrimeTree[0]->RootNames).size();
       process.GetRunningType(1);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!process.OneFilePerJob) ZPrimeTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(process.OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ZPrimeTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(ZPrimeTree[j]);

         cout<<"Thread No."<<j + 1<<": Initialize the rootfile finish"<<endl;
       }

       Run[0]->OutputFileInfo();

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(process.OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_create(&thread[j], NULL, StartThread, Run[j]);
         cout<<"Thread No."<<j + 1<<" has created."<<endl;
         sleep(1);
       }

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(process.OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_join(thread[j], NULL);
         cout<<"Thread No."<<j + 1<<" has finished."<<endl;
       }

     }

}

void ThreadRunPreZPrime(Control process, HistsZPrime* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopZPrime *Run[TotalThread];
     TreeForPreZPrime *ZPrimeTree[TotalThread];

     //ZPrimeSumOfWeight *mySumOfWeight = new ZPrimeSumOfWeight(process.SumOfWeightList);
     //mySumOfWeight->GetSumOfWeight();
     cout<<"Get Sum of Weight finished."<<endl;

     for(int j = 0; j < TotalThread; j++){
       ZPrimeTree[j] = new TreeForPreZPrime();
       ZPrimeTree[j]->InputTreeName(process.TreeName);
       ZPrimeTree[j]->InputFile(process.RootNames);
       //ZPrimeTree[j]->InputSumOfWeight(mySumOfWeight->SumOfWeightsMap);
       if(!process.NtupleName.Contains("root")) ZPrimeTree[j]->BkgSelection(process.NtupleName);

       Run[j] = new loopZPrime(process.RootType);
       if(process.ZPrimeFakeEffFile != "") Run[j]->InputFakeEff(process.ZPrimeFakeEffFile);
       if(process.ZPrimeKFactorFile != "") Run[j]->InputKFactor(process.ZPrimeKFactorFile);
       if(process.ZPrimeAngularFile != "") Run[j]->InputAngularFile(process.ZPrimeAngularFile);

       Run[j]->ControlNormalRun(process.ZPrimeisNormalRun);
       Run[j]->ProcessOption(process.ProcessOption);
       Run[j]->InputNtupleName(process.NtupleName);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.isTest) Run[j]->Test();
       Run[j]->LinkLog(process.myLog);
     }

     if(process.TotalFileNumber != (ZPrimeTree[0]->RootNames).size()){
       process.TotalFileNumber = (ZPrimeTree[0]->RootNames).size();
       process.GetRunningType(1);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!process.OneFilePerJob) ZPrimeTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(process.OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ZPrimeTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(ZPrimeTree[j]);
         cout<<"Thread No."<<j + 1<<": Initialize the rootfile finish"<<endl;
       }

       Run[0]->OutputFileInfo();

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(process.OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
         
         pthread_create(&thread[j], NULL, StartThread, Run[j]);
         cout<<"Thread No."<<j + 1<<" has created."<<endl;
         sleep(1);
       } 
       
       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(process.OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
         
         pthread_join(thread[j], NULL);
         cout<<"Thread No."<<j + 1<<" has finished."<<endl;
       } 
       
     }
     
}

void CondorRunZPrime(Control process, HistsZPrime* myhists)
{
     loopZPrime *Run;
     TreeForZPrime *ZPrimeTree;

     if(process.topDDList != "0" && process.topDDList != ""){
       ZPrimetopDDHelper* topDD = new ZPrimetopDDHelper();
       topDD->openFile(process.topDDFile.at(0));
       topDD->RetrieveHist(process.TransferName_ee.at(0), process.TransferName_mm.at(0));

       ZPrimetopDDHelper* topDD_HighMass_CosTheta = new ZPrimetopDDHelper(2);
       topDD_HighMass_CosTheta->openFile(process.topDDFile.at(1));
       topDD_HighMass_CosTheta->RetrieveHist(process.TransferName_ee.at(1), process.TransferName_mm.at(1));

       ZPrimetopDDHelper* topDD_HighMass_Rapidity = new ZPrimetopDDHelper(2);
       topDD_HighMass_Rapidity->openFile(process.topDDFile.at(2));
       topDD_HighMass_Rapidity->RetrieveHist(process.TransferName_ee.at(2), process.TransferName_mm.at(2));

       myhists->InputTopDD(topDD, topDD_HighMass_CosTheta, topDD_HighMass_Rapidity);
     }

     ZPrimeTree = new TreeForZPrime();
     ZPrimeTree->InputFile(process.RootNames);
     ZPrimeTree->InputSystematic(process.SystematicName);
     ZPrimeTree->BkgSelection(process.NtupleName);
     ZPrimeTree->LinkHist(myhists);

     ZPrimeTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopZPrime(process.RootType);
     if(process.ZPrimeFakeEffFile != "") Run->InputFakeEff(process.ZPrimeFakeEffFile);
     if(process.ZPrimeKFactorFile != "") Run->InputKFactor(process.ZPrimeKFactorFile);
     if(process.ZPrimeAngularFile != "") Run->InputAngularFile(process.ZPrimeAngularFile);

     Run->InputHist(myhists);
     Run->InputTree(ZPrimeTree);
     Run->ConfigCut(process.CutFile);
     Run->iThread = 1;
     if(process.isTest) Run->Test();
     Run->LinkLog(process.myLog);
     cout<<"Initialize the rootfile finish"<<endl;

     Run->OutputFileInfo();

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile);
       Run->ReadTree(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}

void CondorRunPreZPrime(Control process, HistsZPrime* myhists)
{
     loopZPrime *Run;
     TreeForPreZPrime *ZPrimeTree;

     //ZPrimeSumOfWeight *mySumOfWeight = new ZPrimeSumOfWeight(process.SumOfWeightList);
     //mySumOfWeight->GetSumOfWeight();
     cout<<"Get Sum of Weight finished."<<endl;

     ZPrimeTree = new TreeForPreZPrime();
     ZPrimeTree->InputTreeName(process.TreeName);
     ZPrimeTree->InputFile(process.RootNames);
     //ZPrimeTree->InputSumOfWeight(mySumOfWeight->SumOfWeightsMap);
     if(!process.NtupleName.Contains("root")) ZPrimeTree->BkgSelection(process.NtupleName);
     ZPrimeTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopZPrime(process.RootType);

     if(process.ZPrimeFakeEffFile != "") Run->InputFakeEff(process.ZPrimeFakeEffFile);
     if(process.ZPrimeKFactorFile != "") Run->InputKFactor(process.ZPrimeKFactorFile);
     if(process.ZPrimeAngularFile != "") Run->InputAngularFile(process.ZPrimeAngularFile);

     Run->ControlNormalRun(process.ZPrimeisNormalRun);
     Run->ProcessOption(process.ProcessOption);
     Run->InputNtupleName(process.NtupleName);
     Run->InputHist(myhists);
     Run->InputTree(ZPrimeTree);
     Run->ConfigCut(process.CutFile);
     Run->iThread = 1;
     if(process.isTest) Run->Test();
     Run->LinkLog(process.myLog);
     cout<<"Initialize the rootfile finish"<<endl;

     Run->OutputFileInfo();

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile);
       Run->PreLoop(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}

#endif
