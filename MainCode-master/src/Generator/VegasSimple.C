#include "Generator/VegasSimple.h"

VegasSimple::VegasSimple()
{
 vector<double> lower{0.0, 0.0, 0.0, 0.0, 0.0};
 vector<double> upper{1.0, 1.0, 1.0, 1.0, 1.0};

 SetIntegrationRange(lower, upper);

 InitialXi();

}

VegasSimple::VegasSimple(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim)
{
 this->It1 = it1;
 this->Ncall1 = ncall1;
 this->It2 = it2;
 this->Ncall2 = ncall2;
 this->RandomSeed = RandomSeed;
 this->NDimension = Ndim;

 vector<double> lower;
 vector<double> upper;

 for(int i = 0; i < Ndim; i++){
   lower.push_back(0.0);
   upper.push_back(1.0);
 }

 SetIntegrationRange(lower, upper);

 InitialXi();

}

VegasSimple::VegasSimple(int it1, int ncall1, int it2, int ncall2, int RandomSeed, int Ndim, vector<double> lower, vector<double> upper)
{
 this->It1 = it1;
 this->Ncall1 = ncall1;
 this->It2 = it2;
 this->Ncall2 = ncall2;
 this->RandomSeed = RandomSeed;
 this->NDimension = Ndim;

 SetIntegrationRange(lower, upper);

 InitialXi();

}

void VegasSimple::InitialXi()
{
 for(int i = 1; i <= Ng; i++){
   for(int j = 1; j <= NDimension; j++){
     Xi[(vector<int>{i, j})] = (double)(1.0 / (double)Ng) * (double)i;
   }
 }

}

void VegasSimple::Integration(bool isFirstCall)
{
 this->isFirstCall = isFirstCall;

 int ItMax = 10;
 int Ncall = 100;

 if(isFirstCall){
   ItMax = It1;
   Ncall = Ncall1;
 }
 if(!isFirstCall){
   ItMax = It2;
   Ncall = Ncall2;
 }

 double DV2G = 1.0 / (Ncall - 1.0);

 double deltaX, realX;
 vector<double> XVector(NDimension);

 cout<<*right<<setw(5)<<" INPUT PARAMETERS FOR VEGAS:  NDIM =  "<<NDimension<<"   NCALL = "<<Ncall<<", IT = 0, ITMX = "<<ItMax<<endl;
 cout<<" Iteration,    Integral,           Accumulated integral,    Chi**2/it'n"<<endl;

 for(int it = 1; it <= ItMax; it++){
   double TotalF = 0.0;
   double TotalF2 = 0.0;

   //Initialize the integration value and sigma(di)
   for(int j = 1; j <= NDimension; j++){
     for(int i = 1; i <= Ng; i++){
       IntegrationValue[(vector<int>{i, j})] = 0.0;
       IntegrationSigma[(vector<int>{i, j})] = 0.0;
     }
   }

   for(int icall = 1; icall <= Ncall; icall++){
     //Generate uniformly distributed random number in 0~1
     GenerateRandom();

     double WGT = 1.0 / (double)Ncall;
     for(int j = 1; j <= NDimension; j++){

       //////////////////////////////////////////
       //  calculate y*Ng, i(y), and delta(y)  //
       //                                      //
       //  0~1 random map to Ng intervals:     //
       //                                      //
       //  y*Ng: realY                         //
       //  i(y): (int)realY                    //
       //  delta(y): realY - (int)realY        //
       //                                      //
       //  (promise realY is greater than 1)   //
       //  (intY=floor(realY))                 //
       //  (then realY - intY > 0)             //
       //////////////////////////////////////////

       double realY = (1.0 - Random[j]) * (double)Ng + 1.0;

       int intY = (int)realY;
       YPosition[j] = intY;

       ////////////////////////////////////////////////////
       //  X is the real integration range               //
       //                                                //
       //  X(i) is initially the Ng intervals (i / Ng)   //
       //  then X(i) will be adaptively changed          //
       //                                                //
       //  realX = X(i - 1) + delta(y) * X(i)            //
       //                                                //
       //  XLower: lower of real integration range       //
       //  XUpper: upper of real integration range       //
       //  DeltaX: XUpper - XLower                       //
       //                                                //
       //  Final input is XLower + realX * DeltaX        //
       ////////////////////////////////////////////////////

       if(intY > 1){
         deltaX = Xi[(vector<int>{intY, j})] - Xi[(vector<int>{intY - 1, j})];
         realX = Xi[(vector<int>{intY - 1, j})] + (realY - (double)intY) * deltaX;
       }
       else if(intY == 1){
         deltaX = Xi[(vector<int>{1, j})];
         realX = (realY - (double)intY) * deltaX;
       }

       XVector.at(j - 1) = XLower[j] + realX * DeltaX[j];

       WGT = WGT * (double)Ng * DeltaX[j] * deltaX;
     }

     //Input final random numbers to the integrand
     double F;
     if(isSimpleFCN) F = WGT * (*fcn)(XVector, WGT);
     if(isInnerFCN) F = WGT * (this->*InnerFCN)(XVector, WGT);

     double F2 = F * F;

     TotalF += F;
     TotalF2 += F2;

     for(int j = 1; j <= NDimension; j++){
       IntegrationValue[(vector<int>{YPosition[j], j})] += F;
       IntegrationSigma[(vector<int>{YPosition[j], j})] += F2;
     }
   }//end ncall loop

   TotalF2 = sqrt(TotalF2 * Ncall);
   TotalF2 = (TotalF2 - TotalF) * (TotalF2 + TotalF);

   FinalIntegrationValue = TotalF;
   FinalIntegrationError = TotalF2;

   for(int j = 1; j <= NDimension; j++){
     IntegrationSigma[(vector<int>{YPosition[j], j})] += TotalF2;
   }

   FinalIntegrationError = FinalIntegrationError * DV2G;
   double FinalIntegrationValue2 = FinalIntegrationValue * FinalIntegrationValue;
   double Weight = FinalIntegrationValue2 / FinalIntegrationError;

   SIntegrationValue += FinalIntegrationValue * Weight;
   SIntegrationValue2 += FinalIntegrationValue2;
   SWeight += Weight;
   SChi2 += FinalIntegrationValue2 * Weight;

   double AverageIntegration = SIntegrationValue / SWeight;
   double SDelta = SWeight * it / SIntegrationValue2;
   double Chi2A = SDelta * (SChi2 / SWeight - AverageIntegration * AverageIntegration) / (it - 0.999);
   SDelta = sqrt(1.0 / SDelta);
   FinalIntegrationError = sqrt(FinalIntegrationError);

   cout<<*right<<setw(5)<<it<<"   ";
   cout<<*right<<fixed<<setprecision(3)<<setw(7)<<FinalIntegrationValue<<"  +/-  ";
   cout<<*right<<fixed<<setprecision(3)<<setw(7)<<FinalIntegrationError<<"    ";
   cout<<*right<<fixed<<setprecision(3)<<setw(7)<<AverageIntegration<<"  +/-  ";
   cout<<*right<<fixed<<setprecision(3)<<setw(7)<<SDelta<<"    ";
   cout<<*right<<fixed<<setprecision(3)<<setw(10)<<Chi2A<<endl;

   ResetXi();
 }//end iteration loop

}

void VegasSimple::ResetXi()
{
 map<int, double> DTotal;
 map<int, double> Ratio;
 map<int, double> Xin;
 for(int j = 1; j <= NDimension; j++){
   double X0 = IntegrationSigma[(vector<int>{1, j})];
   double XN = IntegrationSigma[(vector<int>{2, j})];

   IntegrationSigma[(vector<int>{1, j})] = (X0 + XN) / 2.0;//(1 + 2) / 2.0 
   DTotal[j] = IntegrationSigma[(vector<int>{1, j})];

   for(int i = 2; i <= Ng - 1; i++){
     IntegrationSigma[(vector<int>{i, j})] = X0 + XN;//(i - 1) + (i)
     X0 = XN;//(i - 1)
     XN = IntegrationSigma[(vector<int>{i + 1, j})];//(i + 1)
     IntegrationSigma[(vector<int>{i, j})] = (IntegrationSigma[(vector<int>{i, j})] + XN) / 3.0;//( (i - 1) + i + (i + 1) ) / 3.0
     DTotal[j] = DTotal[j] + IntegrationSigma[(vector<int>{i, j})];
   }
   IntegrationSigma[(vector<int>{Ng, j})] = (XN + X0) / 2.0;//( (Ng - 1) + Ng ) / 2.0
   DTotal[j] = DTotal[j] + IntegrationSigma[(vector<int>{Ng, j})];
 }

 for(int j = 1; j <= NDimension; j++){
   double delta_d = 0.0;
   for(int i = 1; i <= Ng; i++){
     Ratio[i] = 0.0;
     if(IntegrationSigma[(vector<int>{i, j})] <= 0.0){
       delta_d += Ratio[i];
     }
     else{
       double deltaX = DTotal[j] / IntegrationSigma[(vector<int>{i, j})];
       Ratio[i] = pow(((deltaX - 1.0) / deltaX / log(deltaX)), alpha);//Final di
       delta_d += Ratio[i];
     }
   }
   delta_d = delta_d / (double)Ng;//Final delta(d)

   double XN = 0.0;
   double DR = 0.0;
   double X0 = 0.0;
   int i = 0;
   for(int k = 0; i < Ng; ){
     while((delta_d - DR) > 1e-9){//if delta(d) > Sigma_i{di}
       k++;
       DR += Ratio[k];//+di
       X0 = XN;//X(k-1)
       XN = Xi[(vector<int>{k, j})];//X(k)
     }
     while((delta_d - DR) < 1e-9){//if delta(d) <= Sigma_i(di)
       i++;
       DR = DR - delta_d;
       Xin[i] = XN - (XN - X0) * DR / Ratio[k];
     }
   }
   for(int i = 1; i <= Ng - 1; i++){
     Xi[(vector<int>{i, j})] = Xin[i];
   }
   Xi[(vector<int>{Ng, j})] = 1.0;
 }

 DTotal.clear();
 Ratio.clear();
 Xin.clear();
}

void VegasSimple::GenerateRandom()
{
 for(int j = 1; j <= NDimension; j++){
   double seed, DL, DC, DU, DR;
   if(initRandom){
     initRandom = false;
     seed = (double)RandomSeed;
     DS[1] = (double)(int)(seed / DX24);
     DS[0] = seed - DS[1] * DX24;
   }
   DL = DS[0] * DM[0];
   DC = (double)(int)(DL / DX24);
   DL = DL - DC * DX24;
   DU = DS[0] * DM[1] + DS[1] * DM[0] + DC;
   DS[1] = DU - (double)(int)(DU / DX24) * DX24;
   DS[0] = DL;
   Random[j] = (DS[1] * DX24 + DS[0]) / DX48;
  
   while(fabs(Random[j]) < 1e-10){
     if(initRandom){
       initRandom = false;
       seed = (double)RandomSeed;
       DS[1] = (double)(int)(seed / DX24);
       DS[0] = seed - DS[1] * DX24;
     }
     DL = DS[0] * DM[0];
     DC = (double)(int)(DL / DX24);
     DL = DL - DC * DX24;
     DU = DS[0] * DM[1] + DS[1] * DM[0] + DC;
     DS[1] = DU - (double)(int)(DU / DX24) * DX24;
     DS[0] = DL;
     Random[j] = (DS[1] * DX24 + DS[0]) / DX48;
   }
 }
}

