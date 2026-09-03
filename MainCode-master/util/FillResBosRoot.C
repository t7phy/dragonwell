#include "FillRoot/FillResBos.h"

using namespace std;

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"usage: ./FillResBosRoot infile outRoot"<<endl;
   return 1;
 }

 FillResBos run;
 run.Initial(argv[1], argv[2], "h10"); 
// run.Test();
 run.DefineTree();
 run.FillIn();

 return 1;
}
