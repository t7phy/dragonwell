#include "HighMassDY/SysHMDY.h"

int main(int argc, char** argv)
{
 SysHMDY* run = new SysHMDY();
 run->ReadList("ElSys.list", "MuSys.list");

 return 1;
}
