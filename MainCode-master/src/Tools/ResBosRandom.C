#include "Tools/Tools.h"

double ResBosRandom(int iseed)
{
 double Random;

 double DS[2] = {16651885.0, 2868876.0};
 double DM[2] = {15184245.0, 2651554.0};
 double DX24 = 16777216.0;
 double DX48 = 281474976710656.0;

 bool init = true;

 double seed, DL, DC, DU, DR;
 if(init){
   init = false;
   seed = (double)iseed;
   DS[1] = (double)(int)(seed / DX24);
   DS[0] = seed - DS[1] * DX24;
 }
 DL = DS[0] * DM[0];
 DC = (double)(int)(DL / DX24);
 DL = DL - DC * DX24;
 DU = DS[0] * DM[1] + DS[1] * DM[0] + DC;
 DS[1] = DU - (double)(int)(DU / DX24) * DX24;
 DS[0] = DL;
 Random = (DS[1] * DX24 + DS[0]) / DX48;

 while(fabs(Random) < 1e-10){
   if(init){
     init = false;
     seed = (double)iseed;
     DS[1] = (double)(int)(seed / DX24);
     DS[0] = seed - DS[1] * DX24;
   }
   DL = DS[0] * DM[0];
   DC = (double)(int)(DL / DX24);
   DL = DL - DC * DX24;
   DU = DS[0] * DM[1] + DS[1] * DM[0] + DC;
   DS[1] = DU - (double)(int)(DU / DX24) * DX24;
   DS[0] = DL;
   Random = (DS[1] * DX24 + DS[0]) / DX48;
 }
 return Random;

}
