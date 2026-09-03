#ifndef Tools_OptimizeBinning_h
#define Tools_OptimizeBinning_h

#include "RootCommon.h"

using namespace std;

class OptimizeBinning
{
 public:

 int TotalBin = 0;
 double ErrorOptimizor = 0.0;
 vector<int> Clusters;
 vector<int> StartingClusters;
 function<double(vector<int>)> OptimizeFunction;

 OptimizeBinning(int nbin);
 virtual vector<int> LoopClusters();
 virtual vector<int> LoopClustersDouble(int nCluster);
 virtual vector<int> Optimize();
 virtual vector<int> AddingSubClusters(vector<int> BeforeSubClusters, vector<int> OnSubClusters, vector<int> AfterSubClusters);
 virtual void SetFCN(function<double(vector<int>)> fcn);
};
#endif
