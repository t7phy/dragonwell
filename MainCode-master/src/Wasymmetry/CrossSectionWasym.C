#ifndef CrossSectionWasym_cxx
#define CrossSectionWasym_cxx

#include <iostream>
#include "Wasymmetry/loopWasym.h"

double TreeForWasym::GetSumOfWeight(int nchannel)
{
    if(nchannel == 361100)
        return 5.12008e+7;
    else if (nchannel == 361101)
        return 5.13004e+7;
    else if (nchannel == 361102)
        return 4.92197e+6;
    else if (nchannel == 361103)
        return 3.74773e+7;
    else if (nchannel == 361104)
        return 3.70604e+7;
    else if (nchannel == 361105)
        return 3.92264e+6;
    else if (nchannel == 361106)
        return 1.47431e+7;
    else if (nchannel == 361107)
        return 1.44205e+7;
    else if (nchannel == 361108)
        return 979151;
    else if (nchannel == 363356)
        return 6548.4;
    else if (nchannel == 363358)
        return 469.582;
    else if (nchannel == 363359)
        return 3009.25;
    else if (nchannel == 363360)
        return 2956.62;
    else if (nchannel == 363489)
        return 1568.43;
    else if (nchannel == 364250)
        return 4264.98;
    else if (nchannel == 364253)
        return 3446.1;
    else if (nchannel == 364254)
        return 3383.58;
    else if (nchannel == 364255)
        return 2950.05;
    else if (nchannel == 410013)
        return 10000;
    else if (nchannel == 410014)
        return 10000;
    else if (nchannel == 410470)
        return 1.46044e+9;
    else if (nchannel == 410642)
        return 1.11027e+6;
    else if (nchannel == 410643)
        return 443511;
    else if (nchannel == 410644)
        return 20279.4;
    else if (nchannel == 410645)
        return 12676.8;
    else if (nchannel == -1)
        return 1;
    else{
        std::cout<<"Unknown channel number."<<std::endl;
        return -999;
    }
}

double TreeForWasym::GetCrossSection(int nchannel)
{
    if(nchannel == 361100)
        return 11610;
    else if (nchannel == 361101)
        return 11610;
    else if (nchannel == 361102)
        return 11610;
    else if (nchannel == 361103)
        return 8630;
    else if (nchannel == 361104)
        return 8630;
    else if (nchannel == 361105)
        return 8630;
    else if (nchannel == 361106)
        return 1957.95;
    else if (nchannel == 361107)
        return 1957.95;
    else if (nchannel == 361108)
        return 1957.95;
    else if (nchannel == 363356)
        return 2.19239;
    else if (nchannel == 363358)
        return 3.4329;
    else if (nchannel == 363359)
        return 24.719;
    else if (nchannel == 363360)
        return 24.724;
    else if (nchannel == 363489)
        return 11.42;
    else if (nchannel == 364250)
        return 1.2523;
    else if (nchannel == 364253)
        return 4.5832;
    else if (nchannel == 364254)
        return 12.501;
    else if (nchannel == 364255)
        return 3.235;
    else if (nchannel == 410013)
        return 35.8244;
    else if (nchannel == 410014)
        return 33.989;
    else if (nchannel == 410470)
        return 452.297;
    else if (nchannel == 410642)
        return 36.993;
    else if (nchannel == 410643)
        return 22.174;
    else if (nchannel == 410644)
        return 2.027;
    else if (nchannel == 410645)
        return 1.268;
    else if (nchannel == -1)
        return 1;
    else{
        std::cout<<"Unknown channel number."<<std::endl;
        return 1;
    }
}
#endif
