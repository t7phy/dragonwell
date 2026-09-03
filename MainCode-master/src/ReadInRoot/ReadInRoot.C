#include "ReadInRoot/ReadInRoot.h"

using namespace std;

ReadInRoot::ReadInRoot()
{
}

ReadInRoot::ReadInRoot(TString FileName)
{
 openFile(FileName);
}

ReadInRoot::~ReadInRoot()
{

}

void ReadInRoot::openFile(const char* FileName)
{
 infile.open(FileName, ios::in);
}

void ReadInRoot::LinkHist()
{

}
