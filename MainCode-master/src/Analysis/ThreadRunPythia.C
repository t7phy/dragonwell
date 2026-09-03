#ifndef ThreadRunPythia_cxx
#define ThreadRunPythia_cxx

#include "Analysis/Common.h"

void ThreadRunPythia(Control process, HistsPythia* myhists, int prerunFlag)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopPythia *Run[TotalThread];
     TreeForPythia *PythiaTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       PythiaTree[j] = new TreeForPythia();
       PythiaTree[j]->InputFile(process.RootNames);

       Run[j] = new loopPythia(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       if(process.newPDFset != -1) Run[j]->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);
       if(prerunFlag == 1) Run[j]->PreRunReweightingFactor();
       if(prerunFlag == 2) Run[j]->PostRunReweightingFactor();
       if(process.isPPbar) Run[j]->PPbarRun();
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) PythiaTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           PythiaTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(PythiaTree[j]);
         cout<<"Initialize the rootfile finish"<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_create(&thread[j], NULL, StartThread, Run[j]);
         cout<<"Thread No."<<j + 1<<" has created."<<endl;
         sleep(1);
       }

       for(int j = 0; j < TotalThread; j++){
         ifile = iround * TotalThread + j;
         if(OneFilePerJob && (iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;

         pthread_join(thread[j], NULL);
         cout<<"Thread No."<<j + 1<<" has finished."<<endl;
       }
     }

}

void CondorRunPythia(Control process, HistsPythia* myhists, int prerunFlag)
{
     loopPythia *Run;
     TreeForPythia *PythiaTree;

     PythiaTree = new TreeForPythia();
     PythiaTree->InputFile(process.RootNames);
     PythiaTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopPythia(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(PythiaTree);
     Run->ConfigCut(process.CutFile);
     Run->InputECM(process.ECM);
     if(process.newPDFset != -1) Run->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);
     if(prerunFlag == 1) Run->PreRunReweightingFactor();
     if(prerunFlag == 2) Run->PostRunReweightingFactor();
     if(process.isPPbar) Run->PPbarRun();
     if(process.isTest) Run->Test();
     cout<<"Initialize the rootfile finish"<<endl;

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile);
       Run->ReadTree(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}
#endif
