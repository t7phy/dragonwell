#include "Tools/LatexOutput.h"

LatexOutput::LatexOutput()
{

}

void LatexOutput::DataMC(TH1D* MC, TH1D* Data, TString Name)
{
 if(MC->GetNbinsX() != Data->GetNbinsX()){
   cout<<"ERROR! Data and MC don't match!"<<endl;
   return;
 }

 TString CaptionName = Name;
 CaptionName.ReplaceAll("_", " ");

 ofstream fout;
  fout.open(Name + (TString)".tex");

 fout<<"\\begin{table}[htbp]"<<endl;
 fout<<"    \\centering"<<endl;
 fout<<"    \\begin{tabular}{c|c|c|c|c}"<<endl;
 fout<<"      \\hline"<<endl;
 fout<<"      Range & Theory & Data & Data unc. & Theory - Data \\\\"<<endl;
 fout<<"      \\hline"<<endl;
 for(int ibin = 1; ibin <= MC->GetNbinsX(); ibin++){
   fout<<"      ";
   fout<<"$[$";
   fout<<fixed<<setprecision(GetNDigit(MC->GetXaxis()->GetBinLowEdge(ibin)))<<MC->GetXaxis()->GetBinLowEdge(ibin)<<", ";
   fout<<fixed<<setprecision(GetNDigit(MC->GetXaxis()->GetBinUpEdge(ibin)))<<MC->GetXaxis()->GetBinUpEdge(ibin)<<"$]$  &  ";
   fout<<setw(5)<<*right<<fixed<<setprecision(5)<<MC->GetBinContent(ibin)<<"  &  ";
   fout<<setw(5)<<*right<<fixed<<setprecision(5)<<Data->GetBinContent(ibin)<<"  &  ";
   fout<<setw(5)<<*right<<fixed<<setprecision(5)<<Data->GetBinError(ibin)<<"  &  ";
   fout<<setw(5)<<*right<<fixed<<setprecision(5)<<MC->GetBinContent(ibin) - Data->GetBinContent(ibin)<<"  ";
   fout<<"\\\\";
   fout<<endl;
 }
 fout<<"      \\hline"<<endl;
 fout<<"    \\end{tabular}"<<endl;
 fout<<"    \\caption{The comparison between data and theory prediction on "<<CaptionName<<".}"<<endl;
 fout<<"    \\label{tab:"<<Name<<"}"<<endl;
 fout<<"\\end{table}"<<endl;

 fout.close();
}

int LatexOutput::GetNDigit(double num)
{
 if(num < 0) num = num * (-1);
 if(num > 1.0) num = num - floor(num);
 num = num * 1e4;
 num = round(num);
 int Integer = (int)num;

 int N = 0;

 if(Integer == 0) N = 1;

 if(Integer % 1000 == 0) N = 1;
 if(Integer % 1000 != 0 && Integer % 100 == 0) N = 2;
 if(Integer % 100 != 0 && Integer % 10 == 0) N = 3;
 if(Integer % 10 != 0) N = 4;

 return N;
}


