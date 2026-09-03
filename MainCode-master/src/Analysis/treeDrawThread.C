#include "Analysis/treeDrawThread.h"

void* ThreadTreeDrawLinker(void* arg)
{
 TreeDrawMacro* ptr = (TreeDrawMacro *)arg;

 ptr->TreeDraw();

 pthread_exit(NULL);
}

void TreeDrawThread::SubmitTreeDrawJobs()
{
 threadTreeDraw.resize(TreeDrawVector.size());
 for(int i = 0; i < TreeDrawVector.size(); i++){
   pthread_create(&threadTreeDraw[i], NULL, ThreadTreeDrawLinker, TreeDrawVector.at(i));

   //cout<<"Thread No."<<i<<" has created."<<endl;
   sleep(1);
 }

}

void TreeDrawThread::WaitTreeDrawJobs()
{
 for(int i = 0; i < TreeDrawVector.size(); i++){
   pthread_join(threadTreeDraw[i], NULL);
   //cout<<"Thread No."<<i<<" has finished."<<endl;
 }

 GetFinalHist();
}

void TreeDrawThread::GetFinalHist()
{
 if(is1D){
   for(int i = 0; i < TreeDrawVector.size(); i++){
     FinalHist1D->Add(TreeDrawVector.at(i)->GetHist1DPtr());
   }
 }

 if(is2D){
   for(int i = 0; i < TreeDrawVector.size(); i++){

/*     cout<<RootNames.at(i)<<endl;
     cout<<WeightInfos.at(i)<<endl;
     TH2D* h2 = TreeDrawVector.at(i)->GetHist2DPtr();
     for(int ibinx = 1; ibinx <= h2->GetNbinsX(); ibinx++){
       for(int ibiny = 1; ibiny <= h2->GetNbinsY(); ibiny++){
         cout<<fixed<<setprecision(3)<<h2->GetBinContent(ibinx, ibiny);
         cout<<" +- ";
         cout<<fixed<<setprecision(3)<<h2->GetBinError(ibinx, ibiny)<<"  ";
       }
       cout<<endl;
     }
*/
     FinalHist2D->Add(TreeDrawVector.at(i)->GetHist2DPtr());
   }
 }

 for(int i = 0; i < TreeDrawVector.size(); i++){
   //delete TreeDrawVector.at(i);
 }

}

