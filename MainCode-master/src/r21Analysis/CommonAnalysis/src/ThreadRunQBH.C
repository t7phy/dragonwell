#ifndef ThreadRunQBH_cxx
#define ThreadRunQBH_cxx

#include "Analysis/Common.h"

void ThreadRunQBH(Control process, HistsQBH* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopQBH *Run[TotalThread];
     TreeForQBH *QBHTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       QBHTree[j] = new TreeForQBH();
       QBHTree[j]->InputFile(process.RootNames);
       QBHTree[j]->LinkHist(myhists);

       Run[j] = new loopQBH(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);

       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) QBHTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           QBHTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(QBHTree[j]);

         cout<<"Thread No."<<j + 1<<": Initialize the rootfile finish"<<endl;
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

void ThreadRunPreQBH(Control process, HistsQBH* myhists)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopQBH *Run[TotalThread];
     TreeForPreQBH *QBHTree[TotalThread];

     for(int j = 0; j < TotalThread; j++){
       QBHTree[j] = new TreeForPreQBH();
       QBHTree[j]->InputFile(process.RootNames);
       if(!process.NtupleName.Contains("root")) QBHTree[j]->BkgSelection(process.NtupleName);

       Run[j] = new loopQBH(process.RootType);
       Run[j]->ProcessOption(process.ProcessOption);
       Run[j]->InputNtupleName(process.NtupleName);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       if(process.isTest) Run[j]->Test();
     }

     if(process.TotalFileNumber != (QBHTree[0]->RootNames).size()){
       process.TotalFileNumber = (QBHTree[0]->RootNames).size();
       process.GetRunningType(1);
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!process.OneFilePerJob) QBHTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(process.OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           QBHTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(QBHTree[j]);
         cout<<"Thread No."<<j + 1<<": Initialize the rootfile finish"<<endl;
       }

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

void CondorRunQBH(Control process, HistsQBH* myhists)
{
     loopQBH *Run;
     TreeForQBH *QBHTree;

     QBHTree = new TreeForQBH();
     QBHTree->InputFile(process.RootNames);
     QBHTree->LinkHist(myhists);

     QBHTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopQBH(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(QBHTree);
     Run->ConfigCut(process.CutFile);
     Run->iThread = 1;
     if(process.isTest) Run->Test();
     cout<<"Initialize the rootfile finish"<<endl;

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->ReadTree(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}

void CondorRunPreQBH(Control process, HistsQBH* myhists)
{
     loopQBH *Run;
     TreeForPreQBH *QBHTree;

     QBHTree = new TreeForPreQBH();
     QBHTree->InputFile(process.RootNames);
     if(!process.NtupleName.Contains("root")) QBHTree->BkgSelection(process.NtupleName);
     QBHTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopQBH(process.RootType);
     Run->ProcessOption(process.ProcessOption);
     Run->InputNtupleName(process.NtupleName);
     Run->InputHist(myhists);
     Run->InputTree(QBHTree);
     Run->ConfigCut(process.CutFile);
     Run->iThread = 1;
     if(process.isTest) Run->Test();
     cout<<"Initialize the rootfile finish"<<endl;

     for(int ifile = 0; ifile < Run->RootNames.size(); ifile++){
       Run->Initial(ifile);
       Run->PreLoop(ifile);
       Run->End(ifile);
     }
     Run->Finish();

}

#endif
