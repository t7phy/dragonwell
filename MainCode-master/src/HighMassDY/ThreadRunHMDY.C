#ifndef ThreadRunHMDY_cxx
#define ThreadRunHMDY_cxx

#include "Analysis/Common.h"
#include "HighMassDY/topDDHelper.h"
#include "HighMassDY/SumOfWeight.h"

void ThreadRunHMDY(Control process, HistsHMDY* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopHMDY *Run[TotalThread];
     TreeForHMDY *HMDYTree[TotalThread];

     if(process.topDDList != "0" && process.topDDList != ""){
       topDDHelper* topDD = new topDDHelper();
       topDD->openFile(process.topDDFile.at(0));
       topDD->RetrieveHist(process.TransferName_ee.at(0), process.TransferName_mm.at(0));

       topDDHelper* topDD_HighMass_CosTheta = new topDDHelper(2);
       topDD_HighMass_CosTheta->openFile(process.topDDFile.at(1));
       topDD_HighMass_CosTheta->RetrieveHist(process.TransferName_ee.at(1), process.TransferName_mm.at(1));

       topDDHelper* topDD_HighMass_Rapidity = new topDDHelper(2);
       topDD_HighMass_Rapidity->openFile(process.topDDFile.at(2));
       topDD_HighMass_Rapidity->RetrieveHist(process.TransferName_ee.at(2), process.TransferName_mm.at(2));

       myhists->InputTopDD(topDD, topDD_HighMass_CosTheta, topDD_HighMass_Rapidity);
     }

     for(int j = 0; j < TotalThread; j++){
       HMDYTree[j] = new TreeForHMDY();
       HMDYTree[j]->InputFile(process.RootNames);
       HMDYTree[j]->InputSystematic(process.SystematicName);
       HMDYTree[j]->BkgSelection(process.NtupleName);
       HMDYTree[j]->LinkHist(myhists);

       Run[j] = new loopHMDY(process.RootType);
       if(process.HMDYFakeEffFile != "") Run[j]->InputFakeEff(process.HMDYFakeEffFile);

       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->InputHist(myhists);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->LinkLog(process.myLog);

       if(process.isTest) Run[j]->Test();
     }

     if(process.TotalFileNumber != (HMDYTree[0]->RootNames).size()){
       process.TotalFileNumber = (HMDYTree[0]->RootNames).size();
       process.GetRunningType(1);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!process.OneFilePerJob) HMDYTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(process.OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           HMDYTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(HMDYTree[j]);

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

void ThreadRunPreHMDY(Control process, HistsHMDY* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopHMDY *Run[TotalThread];
     TreeForPreHMDY *HMDYTree[TotalThread];

     HMDYSumOfWeight *mySumOfWeight = new HMDYSumOfWeight(process.SumOfWeightList);
     mySumOfWeight->GetSumOfWeight();
     cout<<"Get Sum of Weight finished."<<endl;

     for(int j = 0; j < TotalThread; j++){
       HMDYTree[j] = new TreeForPreHMDY();
       HMDYTree[j]->InputTreeName(process.TreeName);
       HMDYTree[j]->InputFile(process.RootNames);
       HMDYTree[j]->InputSumOfWeight(mySumOfWeight->SumOfWeightsMap);
       if(!process.NtupleName.Contains("root")) HMDYTree[j]->BkgSelection(process.NtupleName);

       Run[j] = new loopHMDY(process.RootType);
       Run[j]->ControlNormalRun(process.HMDYisNormalRun);
       Run[j]->ProcessOption(process.ProcessOption);
       Run[j]->InputNtupleName(process.NtupleName);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.isTest) Run[j]->Test();
       Run[j]->LinkLog(process.myLog);
     }

     if(process.TotalFileNumber != (HMDYTree[0]->RootNames).size()){
       process.TotalFileNumber = (HMDYTree[0]->RootNames).size();
       process.GetRunningType(1);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!process.OneFilePerJob) HMDYTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(process.OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           HMDYTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(HMDYTree[j]);
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

void CondorRunHMDY(Control process, HistsHMDY* myhists)
{
     loopHMDY *Run;
     TreeForHMDY *HMDYTree;

     if(process.topDDList != "0" && process.topDDList != ""){
       topDDHelper* topDD = new topDDHelper();
       topDD->openFile(process.topDDFile.at(0));
       topDD->RetrieveHist(process.TransferName_ee.at(0), process.TransferName_mm.at(0));

       topDDHelper* topDD_HighMass_CosTheta = new topDDHelper(2);
       topDD_HighMass_CosTheta->openFile(process.topDDFile.at(1));
       topDD_HighMass_CosTheta->RetrieveHist(process.TransferName_ee.at(1), process.TransferName_mm.at(1));

       topDDHelper* topDD_HighMass_Rapidity = new topDDHelper(2);
       topDD_HighMass_Rapidity->openFile(process.topDDFile.at(2));
       topDD_HighMass_Rapidity->RetrieveHist(process.TransferName_ee.at(2), process.TransferName_mm.at(2));

       myhists->InputTopDD(topDD, topDD_HighMass_CosTheta, topDD_HighMass_Rapidity);
     }

     HMDYTree = new TreeForHMDY();
     HMDYTree->InputFile(process.RootNames);
     HMDYTree->InputSystematic(process.SystematicName);
     HMDYTree->BkgSelection(process.NtupleName);
     HMDYTree->LinkHist(myhists);

     HMDYTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopHMDY(process.RootType);
     if(process.HMDYFakeEffFile != "") Run->InputFakeEff(process.HMDYFakeEffFile);

     Run->InputHist(myhists);
     Run->InputTree(HMDYTree);
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

void CondorRunPreHMDY(Control process, HistsHMDY* myhists)
{
     loopHMDY *Run;
     TreeForPreHMDY *HMDYTree;

     HMDYSumOfWeight *mySumOfWeight = new HMDYSumOfWeight(process.SumOfWeightList);
     mySumOfWeight->GetSumOfWeight();

     HMDYTree = new TreeForPreHMDY();
     HMDYTree->InputTreeName(process.TreeName);
     HMDYTree->InputFile(process.RootNames);
     HMDYTree->InputSumOfWeight(mySumOfWeight->SumOfWeightsMap);
     if(!process.NtupleName.Contains("root")) HMDYTree->BkgSelection(process.NtupleName);
     HMDYTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopHMDY(process.RootType);

     if(process.HMDYFakeEffFile != "") Run->InputFakeEff(process.HMDYFakeEffFile);

     Run->ControlNormalRun(process.HMDYisNormalRun);
     Run->ProcessOption(process.ProcessOption);
     Run->InputNtupleName(process.NtupleName);
     Run->InputHist(myhists);
     Run->InputTree(HMDYTree);
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
