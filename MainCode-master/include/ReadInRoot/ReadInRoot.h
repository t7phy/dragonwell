#ifndef ReadInRoot_h
#define ReadInRoot_h

#include "RootCommon.h"
#include "Tools/Tools.h"
#include "FileForEPUMP/FileForEPUMP.h"

using namespace std;

class ReadInRoot
{
 public:

 ifstream infile;

 TString skip;
 string FileLine;
 double para;

 ReadInRoot();
 ReadInRoot(TString FileName);
 virtual ~ReadInRoot();
 virtual void openFile(const char* FileName);
 virtual void LinkHist();
};
#endif
