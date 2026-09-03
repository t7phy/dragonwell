#ifndef ThreadRunResBosCMS_cxx
#define ThreadRunResBosCMS_cxx

#include "Analysis/Common.h"

void ThreadRunResBosCMS(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopResBosCMS *Run[TotalThread];
     TreeForResBosCMS *ResBosCMSTree[TotalThread];
     HistsResBosCMS* myhists;
     myhists = new HistsResBosCMS();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);
     if(process.DataList.size() != 0) myhists->InputData(process.DataList);

     for(int j = 0; j < TotalThread; j++){
       ResBosCMSTree[j] = new TreeForResBosCMS();
       if(process.isReweight) ResBosCMSTree[j]->Reweight();
       if(process.isFSR) ResBosCMSTree[j]->TurnOnFSR();
       if(process.isDilution) ResBosCMSTree[j]->TurnOnDilution();
       ResBosCMSTree[j]->InputFile(process.RootNames);

       Run[j] = new loopResBosCMS(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       if(process.isTest) Run[j]->Test();
     }

     for(int iround = 0; iround < process.TotalRound; iround++){
       int ifile = 0;

       if(process.TotalRound > 1){
         cout<<"The "<<iround + 1<<" time for submit thread job."<<endl;
         cout<<endl;
       }

       for(int j = 0; j < TotalThread; j++){
         if(!OneFilePerJob) ResBosCMSTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           ResBosCMSTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(ResBosCMSTree[j]);
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

void CondorRunResBosCMS(Control process)
{
     loopResBosCMS *Run;
     TreeForResBosCMS *ResBosCMSTree;
     HistsResBosCMS* myhists;

     myhists = new HistsResBosCMS();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);
     if(process.DataList.size() != 0) myhists->InputData(process.DataList);

     ResBosCMSTree = new TreeForResBosCMS();
     if(process.isReweight) ResBosCMSTree->Reweight();
     if(process.isFSR) ResBosCMSTree->TurnOnFSR();
     if(process.isDilution) ResBosCMSTree->TurnOnDilution();
     ResBosCMSTree->InputFile(process.RootNames);
     ResBosCMSTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopResBosCMS(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(ResBosCMSTree);
     Run->ConfigCut(process.CutFile);
     Run->InputECM(process.ECM);
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
