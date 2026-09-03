#include "FillRoot/FillHepMC.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./FillSherpaWW infile outRoot"<<endl;
   return 1;
 }

 FillHepMC run;
 run.Initial(argv[1], argv[2], "WW"); 
// run.Test();
 run.DefineTree();
 run.FillIn();

 return 1;
}
