#include "Tools/SimpleFunction.h"

SimpleFunction::SimpleFunction()
{
 InputNonPert(0.3198, 0.5168, 0.0000, -0.1775, 5, 0.04);
}

void SimpleFunction::openFile(TString FileName)
{
 hf = new TFile(FileName, "RECREATE");
}

void SimpleFunction::InputVariable(double y)
{
 this->y = y;

 CalParameters();
}

void SimpleFunction::InputNonPert(double g1, double g2, double g3, double g4, double g5, double g6)
{
 this->g[0] = g1;
 this->g[1] = g2;
 this->g[2] = g3;
 this->g[3] = g4;
 this->g[4] = g5;
 this->g[5] = g6;
}

void SimpleFunction::CalParameters()
{
 x1 = (Q / ECM) * exp(y);
 x2 = (Q / ECM) * exp(y * (-1.0));

 if(isOutput) cout<<"y:  "<<y<<endl;
 if(isOutput) cout<<"x1: "<<x1<<endl;
 if(isOutput) cout<<"x2: "<<x2<<endl;
 if(isOutput) cout<<"Q:  "<<Q<<endl;
 if(isOutput) cout<<"Q0: "<<Q0<<endl;
 if(isOutput) cout<<"g:  "<<g[0]<<" "<<g[1]<<" "<<g[2]<<" "<<g[3]<<" "<<g[4]<<" "<<g[5]<<endl;
}

void SimpleFunction::SetFunction(TString FunctionName)
{
 if(FunctionName == "BLNY") myFunction = FunctionType::BLNY;
 if(FunctionName == "IY") myFunction = FunctionType::IY;
 if(FunctionName == "IY1") myFunction = FunctionType::IY1;
 if(FunctionName == "IY2") myFunction = FunctionType::IY2;
 if(FunctionName == "IY6") myFunction = FunctionType::IY6;

 this->FunctionName = FunctionName;
}

void SimpleFunction::CalFunction()
{
 switch(myFunction){
   case FunctionType::BLNY:
       BLNYFunction();
       break;
   case FunctionType::IY:
       IYFunction();
       break;
   case FunctionType::IY1:
       IY1Function();
       break;
   case FunctionType::IY2:
       IY2Function();
       break;
   case FunctionType::IY6:
       IY6Function();
       break;
 }

}

void SimpleFunction::BLNYFunction()
{
 double Q = (116.0 + 66.0) / 2.0;

 b2 = b * b;
 Function = (g[0]+g[2]*log(100*x1*x2)+g[1]*log(Q/2.0/Q0));

 cout<<"g1 contribution: "<<g[0]<<endl;
 cout<<"g2 contribution: "<<g[1]*log(Q/2.0/Q0)<<endl;
 cout<<"g3 contribution: "<<g[2]*log(100*x1*x2)<<endl;
}

void SimpleFunction::IYFunction()
{
 b2 = b * b;
 Function = (-b2*(g[0]+(g[1]+g[2]*b2)*log(Q/2.0/Q0)+g[3]*log(100*x1*x2)+g[4]*sinh(g[5]*y*y)));
}

void SimpleFunction::IY1Function()
{
 b2 = b * b;
// Function = exp(-b2*(g[0]+(g[1]+g[2]*b2)*log(Q/2.0/Q0)+g[3]*log(100*x1*x2)+g[4]*sinh(g[5]*fabs(y))+g[3]*0.5*log(1960.0/13000.0)));
 Function = exp(-b2*(g[4]*sinh(g[5]*fabs(y))));
}

void SimpleFunction::IY2Function()
{
 b2 = b * b;
// Function = exp(-b2*(g[0]+(g[1]+g[2]*b2)*log(Q/2.0/Q0)+g[3]*log(100*x1*x2)+g[4]*atan(g[5]*fabs(y))+g[3]*0.5*log(1960.0/13000.0)));
 Function = exp(-b2*(g[4]*atan(g[5]*fabs(y))));
}

void SimpleFunction::IY6Function()
{
 double yMax = 5.0;
 double MZ = 91.1876;
 double Q = (116.0 + 66.0) / 2.0;
 double ecm = 8000.0;

 b2 = b * b;
 Function = g[0]+(g[1]+g[2]*b2)*log(Q/MZ)+g[3]*log(1960/ecm)+g[4]*(tanh(g[5]*yMax)+tanh(g[5]*(fabs(y)-yMax)));

 cout<<"g1 contribution: "<<g[0]<<endl;
 cout<<"g2 contribution: "<<(g[1]+g[2]*b2)*log(Q/MZ)<<endl;
 cout<<"g4 contribution: "<<g[3]*log(1960/ecm)<<endl;
 cout<<"g5 contribution: "<<g[4]*(tanh(g[5]*yMax)+tanh(g[5]*(fabs(y)-yMax)))<<endl;
}

void SimpleFunction::DrawFunction(int nbin, double left, double right)
{
 iplot++;

 Plot[iplot] = new TH1D(FunctionName + "_" + (int)iplot, FunctionName + "_" + (int)iplot, nbin, left, right);

 for(int ibin = 1; ibin <= Plot[iplot]->GetNbinsX(); ibin++){
   this->b = Plot[iplot]->GetBinCenter(ibin);
   CalFunction();
   Plot[iplot]->SetBinContent(ibin, Function);
   Plot[iplot]->SetBinError(ibin, 0);

   if(isOutput) cout<<"b: "<<b<<" exponent: "<<Function<<endl;
 }

 hf->cd();
 Plot[iplot]->Write();
}

void SimpleFunction::SaveFile()
{
 hf->Close();
}

