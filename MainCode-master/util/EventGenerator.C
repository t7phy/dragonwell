#include <iostream>
#include "RootCommon.h"
#include "Generator/Generator.h"
#include "Generator/VegasSimple.h"

using namespace std;

int main(int argc, char** argv)
{
 int It1 = 10;
 int Ncall1 = 3000;
 int It2 = 30;
 int Ncall2 = 10000;
 int RandomSeed = 1234;

// vector<double> lower{-1.0, -1.0};
// vector<double> upper{1.0, 2.0};

 vector<double> lower{0.0};
 vector<double> upper{6.28};

 Generator* Event = new Generator(It1, Ncall1, It2, Ncall2, RandomSeed, 1, lower, upper);
 Event->Initial("Event.root", "tree");
 Event->DefineTree();
 Event->SetInnerFCN("Constant2D");
 Event->Integration();
 Event->Integration(false);
 Event->Close();

 return 1;
}
