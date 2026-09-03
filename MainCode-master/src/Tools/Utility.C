#include "Tools/Tools.h"

vector<double> Logspace(double start, double stop, size_t num, double base)
{
 double realStart = log(start) / log(base);
 double realEnd = log(stop) / log(base);

 std::vector<double> retval;
 retval.resize(num);

 for(int i = 0; i <= num - 1; i++){
   retval.at(i) = pow(base, realStart + (realEnd - realStart) * i / static_cast<double>(num - 1));
 }

 return retval;
}

vector<double> CenterToBinning(vector<double> Q)
{
 vector<double> Binning(Q.size() + 1);
 Binning.at(0) = Q.at(0) * 1.5 - Q.at(1) * 0.5;
 Binning.at(Binning.size() - 1) = Q.at(Q.size() - 1) * 1.5 - Q.at(Q.size() - 2) * 0.5;
 for(int i = 1; i < Q.size(); i++){
   Binning.at(i) = (Q.at(i - 1) + Q.at(i)) * 0.5;
 }

 return Binning;
}

