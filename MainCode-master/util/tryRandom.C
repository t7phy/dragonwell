#include "Tools/Tools.h"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  vector<double> RandomList;
  GenGausRandomList(1.001, 0.001, RandomList, 1000);

  for(int i = 0; i < 1000; i++){
    cout<<RandomList.at(i)<<endl;
  }

  return 1;
}
