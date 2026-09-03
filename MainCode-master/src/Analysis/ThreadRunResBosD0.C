#ifndef ThreadRunResBosD0_cxx
#define ThreadRunResBosD0_cxx

#include "Analysis/Common.h"

void ThreadRunResBosD0(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBosD0 *Run[TotalThread];
     TreeForResBosD0 *ResBosD0Tree[TotalThread];
     HistsResBosD0* myhists;

     myhists = new HistsResBosD0();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       ResBosD0Tree[j] = new TreeForResBosD0();
       if(process.isReweight) ResBosD0Tree[j]->Reweight();
       if(process.isFSR) ResBosD0Tree[j]->TurnOnFSR();
       if(process.isDilution) ResBosD0Tree[j]->TurnOnDilution();
       ResBosD0Tree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBosD0(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       if(process.newPDFset != -1) Run[j]->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) ResBosD0Tree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ResBosD0Tree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(ResBosD0Tree[j]);
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

     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;

}

void CondorRunResBosD0(Control process)
{
     loopResBosD0 *Run;
     TreeForResBosD0 *ResBosD0Tree;
     HistsResBosD0* myhists;

     myhists = new HistsResBosD0();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);

     ResBosD0Tree = new TreeForResBosD0();
     if(process.isReweight) ResBosD0Tree->Reweight();
     if(process.isFSR) ResBosD0Tree->TurnOnFSR();
     if(process.isDilution) ResBosD0Tree->TurnOnDilution();
     ResBosD0Tree->InputFile(process.RootNames);
     ResBosD0Tree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopResBosD0(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(ResBosD0Tree);
     Run->ConfigCut(process.CutFile);
     Run->InputECM(process.ECM);
     if(process.newPDFset != -1) Run->InputPDFReweightInfo(process.oldPDFName, process.newPDFName, process.oldPDFset, process.newPDFset);
     if(process.isTest) Run->Test();
     cout<<"Initialize the rootfile finish"<<endl;

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile);
       Run->ReadTree(ifile);
       Run->End(ifile);
     }
     Run->Finish();
     myhists->saveHists();
     delete myhists;

}
#endif
