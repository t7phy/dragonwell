#include "Tools/OptimizeBinning.h"

OptimizeBinning::OptimizeBinning(int nbin)
{
 TotalBin = nbin;
 StartingClusters.resize(nbin);
 for(int i = 0; i < StartingClusters.size(); i++){
   StartingClusters.at(i) = 1;
 }
}

vector<int> OptimizeBinning::LoopClusters()
{
 // For the n th bin, try to cluster with the n-1 th bin, then cluster with the n+1 bin

 cout<<"StartingClusters: nCluster = "<<StartingClusters.size()<<"  Clusters: ";
 for(int i = 0; i < StartingClusters.size(); i++){
   cout<<StartingClusters.at(i)<<" ";
 }
 cout<<endl;

 TotalBin = StartingClusters.size();

 double MinError = 100.0;
 double NewError = 100.0;
 Clusters.clear();

 int NumberOfLastCluster = 0;

 vector<int> tmpClusters;

 int iPoint = 1;
 while(iPoint <= StartingClusters.size()){
   if(Clusters.size() != 0){

     // try to cluster with the previous cluster
     map<double, vector<int>> ClusterMap;
     for(int i = 0; i < NumberOfLastCluster; i++){
       tmpClusters.clear();
       tmpClusters = Clusters;
       int nNewPoint = 0;
       for(int j = 0; j <= i; j++){
         nNewPoint += StartingClusters.at(iPoint - 1 - j);
       }
       tmpClusters.at(tmpClusters.size() - 1) = tmpClusters.at(tmpClusters.size() - 1) - (nNewPoint - StartingClusters.at(iPoint - 1));
       tmpClusters.push_back(StartingClusters.at(iPoint - 1) + (nNewPoint - StartingClusters.at(iPoint - 1)));

       vector<int> tmpClusters0 = tmpClusters;

       for(int ibin = iPoint + 1; ibin <= StartingClusters.size(); ibin++){
         tmpClusters.push_back(StartingClusters.at(ibin - 1));
       }

       NewError = OptimizeFunction(tmpClusters);
       ClusterMap[NewError] = tmpClusters0;
     }

     auto Iter = ClusterMap.begin();
     MinError = Iter->first;
     Clusters = Iter->second;
     ClusterMap.clear();

     int SumClusters = 0;
     for(int i = 0; i < Clusters.size(); i++){
       SumClusters += Clusters.at(i);
     }

     iPoint++; // move to the next point
     if(iPoint > StartingClusters.size()) break;

     // try to cluster with behind bins
     NewError = MinError;
     int nNewPoint = 0;
     NumberOfLastCluster = 2;
//     map<double, tuple<int, int, int>> ClusterPointMap; // Method 2
     do { // Method 1
//     for(int i = iPoint; i <= StartingClusters.size(); i++){ // Method 2
       ErrorOptimizor = NewError;
       tmpClusters.clear();
       tmpClusters = Clusters;
       nNewPoint += StartingClusters.at(iPoint - 1);
       tmpClusters.at(tmpClusters.size() - 1) += nNewPoint;
       for(int ibin = iPoint + 1; ibin <= StartingClusters.size(); ibin++){
         tmpClusters.push_back(StartingClusters.at(ibin - 1));
       }
       NewError = OptimizeFunction(tmpClusters);
       iPoint++;
       NumberOfLastCluster++;
//       ClusterPointMap[NewError] = make_tuple(nNewPoint, iPoint - 1, NumberOfLastCluster - 1); // Method 2
//     } // Method 2
     } while(NewError < ErrorOptimizor && iPoint <= StartingClusters.size()); // Method 1

     if(NewError < MinError) MinError = NewError; // Method 1

     iPoint--; // Method 1
     Clusters.at(Clusters.size() - 1) += nNewPoint - StartingClusters.at(iPoint - 1); // Method 1
     NumberOfLastCluster--; // Method 1
     NumberOfLastCluster--; // Method 1
//     iPoint = get<1>(ClusterPointMap.begin()->second) + 1; // Method 2
//     Clusters.at(Clusters.size() - 1) += get<0>(ClusterPointMap.begin()->second); // Method 2
//     MinError = ClusterPointMap.begin()->first; // Method 2
//     NumberOfLastCluster = get<2>(ClusterPointMap.begin()->second); // Method 2
//     ClusterPointMap.clear(); // Method 2
   }
   else if(Clusters.size() == 0){ // First Loop
//     map<double, pair<int, int>> ClusterPointMap; // Method 2

     int nNewPoint = 0;
     do { // Method 1
//     for(int i = 1; i <= StartingClusters.size() - 1; i++){ // Method 2
       ErrorOptimizor = NewError;
       tmpClusters.clear();
       tmpClusters.resize(1);
       nNewPoint += StartingClusters.at(iPoint - 1);
       tmpClusters.at(0) = nNewPoint;
       for(int ibin = iPoint + 1; ibin <= StartingClusters.size(); ibin++){
         tmpClusters.push_back(StartingClusters.at(ibin - 1));
       }
       NewError = OptimizeFunction(tmpClusters);
       iPoint++;
//       ClusterPointMap[NewError] = make_pair(tmpClusters.at(0), iPoint - 1); // Method 2
//     } // Method 2
     } while(NewError < ErrorOptimizor && iPoint <= StartingClusters.size()); // Method 1

     if(NewError < MinError) MinError = NewError; // Method 1

     iPoint--; // Method 1
     Clusters.resize(1); // Method 1
     Clusters.at(0) = nNewPoint - StartingClusters.at(iPoint - 1); // Method 1
     NumberOfLastCluster = iPoint - 1; // Method 1
//     iPoint = get<1>(ClusterPointMap.begin()->second) + 1; // Method 2
//     Clusters.resize(1); // Method 2
//     Clusters.at(0) = get<0>(ClusterPointMap.begin()->second); // Method 2
//     MinError = ClusterPointMap.begin()->first; // Method 2
//     NumberOfLastCluster = iPoint - 1; // Method 2
//     ClusterPointMap.clear(); // Method 2
   }
 }

 cout<<"Final: "<<MinError<<"  nCluster = "<<Clusters.size()<<"  Clusters: ";
 for(int i = 0; i < Clusters.size(); i++){
   cout<<Clusters.at(i)<<" ";
 }
 cout<<endl;

 StartingClusters.clear();
 StartingClusters = Clusters;
 TotalBin = StartingClusters.size();

 return Clusters;
}

vector<int> OptimizeBinning::LoopClustersDouble(int nCluster)
{
 cout<<"StartingClusters: nCluster = "<<StartingClusters.size()<<"  Clusters: ";
 for(int i = 0; i < StartingClusters.size(); i++){
   cout<<StartingClusters.at(i)<<" ";
 }
 cout<<endl;

 double MinError = 100.0;
 double NewError = 100.0;
 Clusters.clear();

 double StartingError = OptimizeFunction(StartingClusters);

 map<double, vector<int>> ClusterMap;
 for(int iPoint = 1; iPoint <= StartingClusters.size() - (nCluster - 1); iPoint++){
   // before iPoint
   for(int i = 1; i < iPoint; i++){
     Clusters.push_back(StartingClusters.at(i - 1));
   }

   // At iPoint
   int NewPoint = StartingClusters.at(iPoint - 1);
   for(int inew = 1; inew < nCluster; inew++){
     NewPoint += StartingClusters.at(iPoint + (inew - 1));
   }
   //int NewPoint = StartingClusters.at(iPoint - 1) + StartingClusters.at(iPoint);
   Clusters.push_back(NewPoint);

   // after iPoint
   for(int i = iPoint + nCluster; i <= StartingClusters.size(); i++){
     Clusters.push_back(StartingClusters.at(i - 1));
   }

   NewError = OptimizeFunction(Clusters);
   ClusterMap[NewError] = Clusters;
   Clusters.clear();
 }

 MinError = ClusterMap.begin()->first;
 if(MinError < StartingError){
   StartingClusters = ClusterMap.begin()->second;
 }
 else{
   cout<<"Smallest Error = "<<MinError<<" Previous MinError = "<<StartingError<<" Stop here."<<endl;
   cout<<"Final: "<<MinError<<" Previous MinError = "<<StartingError<<"  nCluster = "<<StartingClusters.size()<<"  Clusters: ";
   for(int i = 0; i < StartingClusters.size(); i++){
     cout<<StartingClusters.at(i)<<" ";
   }
   cout<<endl;

   //StartingClusters = ClusterMap.begin()->second;
   return StartingClusters;
 }

 ClusterMap.clear();

 bool HaveSubClusters = false;
 vector<bool> IsSinglePoint(StartingClusters.size());
 for(int i = 0; i < IsSinglePoint.size(); i++){
   IsSinglePoint.at(i) = true;
 }

 do{
   int nUnit = 0;
   int SubClusterStart = 0;
   int SubClusterEnd = 0;
   vector<int> BeforeSubClusters(0);
   vector<int> OnSubClusters(0);
   vector<int> AfterSubClusters(0);
  
   // Finding subclusters
   HaveSubClusters = false;
  
   for(int iPoint = 1; iPoint <= StartingClusters.size(); iPoint++){
     if(StartingClusters.at(iPoint - 1) == 1 && IsSinglePoint.at(iPoint - 1)){
       nUnit++;

       if(iPoint == StartingClusters.size()){
         if(nUnit >= nCluster + 3){
           SubClusterStart = StartingClusters.size() + 1 - nUnit;
           SubClusterEnd = StartingClusters.size();
           HaveSubClusters = true;
         }
       }

       continue;
     }
  
     if(StartingClusters.at(iPoint - 1) != 1 || !IsSinglePoint.at(iPoint - 1)){
       if(nUnit >= nCluster + 3){
         /*for(int ibefore = 1; ibefore <= iPoint - nUnit - 1; ibefore++){
           BeforeSubClusters.push_back(StartingClusters.at(ibefore - 1));
         }
         for(int i = 1; i <= nUnit; i++){
           OnSubClusters.push_back(1);
         }
         for(int iafter = iPoint; iafter <= StartingClusters.size(); iafter++){
           AfterSubClusters.push_back(StartingClusters.at(iafter - 1));
         }*/
         SubClusterStart = iPoint - nUnit;
         SubClusterEnd = iPoint - 1;
         HaveSubClusters = true;
         break;
       }
       else{
         nUnit = 0;
         continue;
       }
     }
   }

   HaveSubClusters = false; // force not entering this routine

   if(HaveSubClusters){
     ClusterMap.clear();
     for(int iPoint = SubClusterStart + 1; iPoint <= SubClusterEnd - 2; iPoint++){
       // before iPoint
       for(int i = 1; i < iPoint; i++){
         Clusters.push_back(StartingClusters.at(i - 1));
       }
    
       // At iPoint
       int NewPoint = StartingClusters.at(iPoint - 1);
       for(int inew = 1; inew < nCluster; inew++){
         NewPoint += StartingClusters.at(iPoint + (inew - 1));
       }
       //int NewPoint = StartingClusters.at(iPoint - 1) + StartingClusters.at(iPoint);
       Clusters.push_back(NewPoint);
    
       // after iPoint
       for(int i = iPoint + nCluster; i <= StartingClusters.size(); i++){
         Clusters.push_back(StartingClusters.at(i - 1));
       }
    
       NewError = OptimizeFunction(Clusters);
       ClusterMap[NewError] = Clusters;
       Clusters.clear();
     }
  
     NewError = ClusterMap.begin()->first;
     if(NewError < MinError){
       StartingClusters = ClusterMap.begin()->second;

       IsSinglePoint.resize(StartingClusters.size());
       for(int i = 0; i < IsSinglePoint.size(); i++){
         IsSinglePoint.at(i) = true;
       }
     }
     else{
       IsSinglePoint.resize(StartingClusters.size());
       for(int i = 0; i < IsSinglePoint.size(); i++){
         IsSinglePoint.at(i) = true;
       }

       for(int iPoint = SubClusterStart + 1; iPoint <= SubClusterEnd - 2; iPoint++){
         IsSinglePoint.at(iPoint - 1) = false;
       }
     }
   }
 } while(HaveSubClusters);

 cout<<"Final: "<<MinError<<"  nCluster = "<<StartingClusters.size()<<"  Clusters: ";
 for(int i = 0; i < StartingClusters.size(); i++){
   cout<<StartingClusters.at(i)<<" ";
 }
 cout<<endl;

 return StartingClusters;
}

vector<int> OptimizeBinning::Optimize()
{
 vector<int> OldClusters(0);
 vector<int> NewClusters(0);
 vector<int> FinalClusters(0);
 double FinalError = 0.0;

 int nCluster = 2;
 NewClusters = LoopClustersDouble(nCluster);

 int iIteration = 1;
 while(nCluster < NewClusters.size() - 1){

   if(OldClusters.size() == NewClusters.size()) nCluster++;

   if(OldClusters.size() != NewClusters.size()){
     nCluster = 2;
     FinalClusters = NewClusters;
   }

   iIteration++;
   cout<<"Try "<<iIteration<<" iteration, nCluster = "<<nCluster<<":"<<endl;
   OldClusters = NewClusters;
   NewClusters = LoopClustersDouble(nCluster);
 }

 cout<<"Final: nCluster = "<<FinalClusters.size()<<" Clusters: ";
 for(int i = 0; i < FinalClusters.size(); i++){
   cout<<FinalClusters.at(i)<<", ";
 }

 FinalError = OptimizeFunction(FinalClusters);

 cout<<endl;
 cout<<"Final Error = "<<FinalError<<endl;

 return FinalClusters;
}

vector<int> OptimizeBinning::AddingSubClusters(vector<int> BeforeSubClusters, vector<int> OnSubClusters, vector<int> AfterSubClusters)
{
 vector<int> NewClusters(0);
 for(int i = 0; i < BeforeSubClusters.size(); i++){
   Clusters.push_back(BeforeSubClusters.at(i));
 }
 for(int i = 0; i < OnSubClusters.size(); i++){
   Clusters.push_back(OnSubClusters.at(i));
 }
 for(int i = 0; i < AfterSubClusters.size(); i++){
   Clusters.push_back(AfterSubClusters.at(i));
 }

 return NewClusters;
}

void OptimizeBinning::SetFCN(function<double(vector<int>)> fcn)
{
 OptimizeFunction = fcn;
}
