#include "Tools/SimpleFunction.h"

int main(int argc, char** argv)
{
 SimpleFunction *run = new SimpleFunction();

 run->Output();

 cout<<"C3 = 1.3, bMax = 1.123: "<<endl;
 run->InputNonPert(0.94335, 0.10223, 0.0, -0.086237, 0.59944, 0.5);

 run->SetFunction("IY6");
 run->InputVariable(0.2);
 cout<<"y = 0.2:"<<endl;
 run->CalFunction();
 run->OutputFunction();

 cout<<"C3 = 2.0, bMax = 0.5:"<<endl;
 run->InputNonPert(2.69678, 0.533633, 0.0, -0.2, 2.9266, 0.5);

 run->SetFunction("IY6");
 run->InputVariable(0.2);
 cout<<"y = 0.2:"<<endl;
 run->CalFunction();
 run->OutputFunction();

 cout<<"C3 = 2.0, bMax = 0.5:"<<endl;
 run->InputNonPert(0.34483, 0.49333, -0.1858, 0.0, 0.0, 0.0);

 run->SetFunction("BLNY");
 run->InputVariable(0.2);
 cout<<"y = 0.2:"<<endl;
 run->CalFunction();
 run->OutputFunction();

/* run->InputVariable(0.6);
 cout<<"y = 0.6:"<<endl;
 run->CalFunction();
 run->OutputFunction();

 run->InputVariable(1.0);
 cout<<"y = 1.0:"<<endl;
 run->CalFunction();
 run->OutputFunction();

 run->InputVariable(1.4);
 cout<<"y = 1.4:"<<endl;
 run->CalFunction();
 run->OutputFunction();

 run->InputVariable(1.8);
 cout<<"y = 1.8:"<<endl;
 run->CalFunction();
 run->OutputFunction();

 run->InputVariable(2.2);
 cout<<"y = 2.2:"<<endl;
 run->CalFunction();
 run->OutputFunction();
*/

/* run->openFile("NonPertFunction.root");
 run->SetFunction("IY1");
 run->InputVariable(0.2);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(0.6);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(1.0);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(1.4);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(1.8);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(2.2);
 run->DrawFunction(100, 0, 0.5);
 run->SetFunction("IY2");
 run->InputVariable(0.2);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(0.6);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(1.0);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(1.4);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(1.8);
 run->DrawFunction(100, 0, 0.5);
 run->InputVariable(2.2);
 run->DrawFunction(100, 0, 0.5);

 run->SaveFile();
*/

 return 1;
}
