#include "Uncertainty/FitAFBStw.h"

using namespace std;

int main(int argc, char** argv)
{
 FitAFBStw run("AFBCard.in");

 run.InputLumiAndXSec(20000.0, 1147.1);
 run.Main();

 return 1;
}
