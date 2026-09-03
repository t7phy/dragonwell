#ifndef ThreadRunWasym_cxx
#define ThreadRunWasym_cxx

#include "Analysis/Common.h"

void ThreadRunWasym(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopWasym *Run[TotalThread];
     TreeForWasym *WasymTree[TotalThread];
     HistsWasym* myhists;

     myhists = new HistsWasym();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     if(process.isRunAllSystematic) myhists->RunAllSystematic();
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       WasymTree[j] = new TreeForWasym();
       WasymTree[j]->InputFile(process.RootNames);

       Run[j] = new loopWasym(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.isRunAllSystematic) Run[j]->RunAllSystematic();
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) WasymTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           WasymTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(WasymTree[j]);
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

     cout<<"Thread: Start MergeHists Time:   "<<getTime()<<endl;
     myhists->MergeHists();
     myhists->saveHists();
     delete myhists;

}

void CondorRunWasym(Control process)
{
     loopWasym *Run;
     TreeForWasym *WasymTree;
     HistsWasym* myhists;

     myhists = new HistsWasym();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     if(process.isRunAllSystematic) myhists->RunAllSystematic();
     myhists->bookHists(1);

     WasymTree = new TreeForWasym();
     WasymTree->InputFile(process.RootNames);
     WasymTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopWasym(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(WasymTree);
     Run->ConfigCut(process.CutFile);
     if(process.isRunAllSystematic) Run->RunAllSystematic();
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
