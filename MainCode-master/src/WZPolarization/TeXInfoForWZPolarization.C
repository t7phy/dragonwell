#include "WZPolarization/HistsWZPolarization.h"

void HistsWZPolarization::outputTeXInfo()
{
 TeXInfo["FakeClosure"].open("FakeClosure.tex");

 TeXInfo["FakeClosure"]<<"\\begin{table}[!th]"<<endl;
 TeXInfo["FakeClosure"]<<"\\begin{center}"<<endl;
 TeXInfo["FakeClosure"]<<"\\begin{tabular}{c c c c c }"<<endl;
 TeXInfo["FakeClosure"]<<"\\hline"<<endl;
 TeXInfo["FakeClosure"]<<"Channels	 &$\\mu\\mu\\mu$	   &$e\\mu\\mu$	        &$\\mu ee$	&$eee$ \\\\"<<endl;
 TeXInfo["FakeClosure"]<<"\\hline"<<endl;
 TeXInfo["FakeClosure"]<<fixed<<setprecision(2);
 TeXInfo["FakeClosure"]<<"        Sum of $Z$+jets, $t\\bar{t}$, and $Z+\\gamma$ & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(2);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(2);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(3);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(3);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(4);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(4);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(5);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Data->HistPtr(0))->GetBinError(5)<<" \\\\"<<endl;
 TeXInfo["FakeClosure"]<<"        Matrix result & "<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(2);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(2);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(3);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(3);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(4);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(4);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(5);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<(Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinError(5)<<" \\\\"<<endl;
 TeXInfo["FakeClosure"]<<"        "<<endl;
 TeXInfo["FakeClosure"]<<""<<endl;
 TeXInfo["FakeClosure"]<<"\\hline"<<endl;
 TeXInfo["FakeClosure"]<<"\\hline"<<endl;
 TeXInfo["FakeClosure"]<<"        ratio & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(2) / (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(2);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<DivideUncertainty(Channel->Inclusive_Data->HistPtr(0), (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist, 2);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(3) / (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(3);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<DivideUncertainty(Channel->Inclusive_Data->HistPtr(0), (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist, 3);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(4) / (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(4);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<DivideUncertainty(Channel->Inclusive_Data->HistPtr(0), (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist, 4);
 TeXInfo["FakeClosure"]<<" & "<<(Channel->Inclusive_Data->HistPtr(0))->GetBinContent(5) / (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist->GetBinContent(5);
 TeXInfo["FakeClosure"]<<"$\\pm$"<<DivideUncertainty(Channel->Inclusive_Data->HistPtr(0), (Channel->Inclusive_Fake->HistPtr(0))->FinalFakeHist, 5)<<" \\\\"<<endl;
 TeXInfo["FakeClosure"]<<"\\hline"<<endl;
 TeXInfo["FakeClosure"]<<"\\end{tabular}"<<endl;
 TeXInfo["FakeClosure"]<<"\\caption{Closure test of the Matrix Method using pseudo data.}"<<endl;
 TeXInfo["FakeClosure"]<<"\\label{tab:MM_closure}"<<endl;
 TeXInfo["FakeClosure"]<<"\\end{center}"<<endl;
 TeXInfo["FakeClosure"]<<"\\end{table}"<<endl;

}

