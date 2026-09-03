#ifndef ThreadRunSherpaWW_cxx
#define ThreadRunSherpaWW_cxx

#include "Analysis/Common.h"

void ThreadRunSherpaWW(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopSherpaWW *Run[TotalThread];
     TreeForSherpaWW *SherpaWWTree[TotalThread];
     HistsSherpaWW* myhists;

     myhists = new HistsSherpaWW();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       SherpaWWTree[j] = new TreeForSherpaWW();
       SherpaWWTree[j]->InputFile(process.RootNames);

       Run[j] = new loopSherpaWW(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputErrorSet(process.ErrorSet);
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) SherpaWWTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           SherpaWWTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(SherpaWWTree[j]);
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

void CondorRunSherpaWW(Control process)
{
     loopSherpaWW *Run;
     TreeForSherpaWW *SherpaWWTree;
     HistsSherpaWW* myhists;

     myhists = new HistsSherpaWW();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);

     SherpaWWTree = new TreeForSherpaWW();
     SherpaWWTree->InputFile(process.RootNames);
     SherpaWWTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopSherpaWW(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(SherpaWWTree);
     Run->ConfigCut(process.CutFile);
     Run->InputErrorSet(process.ErrorSet);
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
