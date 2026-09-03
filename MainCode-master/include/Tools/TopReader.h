#ifndef Tools_TopReader_h
#define Tools_TopReader_h

#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

class TopReader
{
 public:

 ifstream data;
 std::string FileLine;

 vector<double> BinCenters;
 vector<double> Binning;
 vector<double> Values;
 vector<double> Errors;

 TopReader(const char* name);
 virtual void Initialize(const char* name);
 TH1D* outputHistogram(const char* name);
};
#endif
