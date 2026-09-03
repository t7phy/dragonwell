#ifndef ThreadRunFlavorAsym_cxx
#define ThreadRunFlavorAsym_cxx

#include "Analysis/Common.h"

void ThreadRunFlavorAsym(Control process)
{
     bool OneFilePerJob = process.OneFilePerJob;
     int TotalThread = process.TotalThread;

     pthread_t thread[TotalThread];

     loopFlavorAsym *Run[TotalThread];
     TreeForFlavorAsym *FlavorAsymTree[TotalThread];
     HistsFlavorAsym* myhists;

     myhists = new HistsFlavorAsym();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(TotalThread);

     for(int j = 0; j < TotalThread; j++){
       FlavorAsymTree[j] = new TreeForFlavorAsym();
       if(process.isReweight) FlavorAsymTree[j]->Reweight();
       if(process.isFSR) FlavorAsymTree[j]->TurnOnFSR();
       if(process.isDilution) FlavorAsymTree[j]->TurnOnDilution();
       FlavorAsymTree[j]->InputFile(process.RootNames);

       Run[j] = new loopFlavorAsym(process.RootType);
       Run[j]->InputHist(myhists);
       Run[j]->InputThreadInfo(TotalThread, j + 1);
       Run[j]->ConfigCut(process.CutFile);
       Run[j]->InputECM(process.ECM);
       //if(process.oldPDFName != "") Run[j]->InitialPDFInfo(process.oldPDFName, process.oldPDFset);
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
         if(!OneFilePerJob) FlavorAsymTree[j]->ConfigFile(process.NFilePerJob, iround);

         if(OneFilePerJob){
           ifile = iround * TotalThread + j;
           if((iround == process.TotalRound - 1) && ifile >= process.TotalFileNumber) continue;
           FlavorAsymTree[j]->ConfigFile(ifile);
         }

         Run[j]->InputTree(FlavorAsymTree[j]);
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

void CondorRunFlavorAsym(Control process)
{
     loopFlavorAsym *Run;
     TreeForFlavorAsym *FlavorAsymTree;
     HistsFlavorAsym* myhists;

     myhists = new HistsFlavorAsym();
     myhists->openFile(process.SaveName);
     myhists->LinkLog(process.myLog);
     myhists->bookHists(1);

     FlavorAsymTree = new TreeForFlavorAsym();
     if(process.isReweight) FlavorAsymTree->Reweight();
     if(process.isFSR) FlavorAsymTree->TurnOnFSR();
     if(process.isDilution) FlavorAsymTree->TurnOnDilution();
     FlavorAsymTree->InputFile(process.RootNames);
     FlavorAsymTree->ConfigFile(process.NFilePerJob, 0);

     Run = new loopFlavorAsym(process.RootType);
     Run->InputHist(myhists);
     Run->InputTree(FlavorAsymTree);
     Run->ConfigCut(process.CutFile);
     Run->InputECM(process.ECM);
     //if(process.oldPDFName != "") Run->InitialPDFInfo(process.oldPDFName, process.oldPDFset);
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
