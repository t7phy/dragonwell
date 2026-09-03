#include "Calculation/Dataset.h"

void Dataset::InputOtherKFactor(TString path)
{
 ifstream kfactorfile(path);

 vector<vector<double>> KFactorTable;
 vector<TString> InputType;

 while(getline(kfactorfile, FileLine)){
   vector<double> LineVector;
   double Value;
   stringstream LineStream(FileLine);

   TString type;
   LineStream >> type;
   InputType.push_back(type);

   while(LineStream >> Value){
     LineVector.push_back(Value);
   }
   if(LineVector.size() == 0) break;

   KFactorTable.push_back(LineVector);//FullTable.at(i).at(j) is i row and j column
 }

 vector<OtherKFactor> OtherKFactorTable(KFactorTable.size());

 for(int i = 0; i < KFactorTable.size(); i++){
   if(InputType.at(i) == "Simple") OtherKFactorTable.at(i).type = KFactorType::Simple;
   else if(InputType.at(i) == "Linear") OtherKFactorTable.at(i).type = KFactorType::Linear;
   else if(InputType.at(i) == "Quadratic") OtherKFactorTable.at(i).type = KFactorType::Quadratic;

   OtherKFactorTable.at(i).parameters.resize(KFactorTable.at(i).size());
   for(int ip = 0; ip < KFactorTable.at(i).size(); ip++){
     OtherKFactorTable.at(i).parameters.at(ip) = KFactorTable.at(i).at(ip);
   }
 }

 OtherKFactorList.push_back(OtherKFactorTable);
}

void Dataset::ApplyOtherKFactor(vector<double> zVec)
{
 if(zVec.size() != OtherKFactorList.size()) cout<<"ERROR! Input parameter list doesn't match with other kfactor list."<<endl;

 FinalOtherKFactor.resize(OtherKFactorList.at(0).size());
 for(int i = 0; i < FinalOtherKFactor.size(); i++) FinalOtherKFactor.at(i) = 1.0;

 for(int i = 0; i < OtherKFactorList.size(); i++){
   double z = zVec.at(i);

   for(int ipoint = 0; ipoint < OtherKFactorList.at(i).size(); ipoint++){
     if(OtherKFactorList.at(i).at(ipoint).type == KFactorType::Simple){
       FinalOtherKFactor.at(ipoint) *= OtherKFactorList.at(i).at(ipoint).parameters.at(0);
     }
     else if(OtherKFactorList.at(i).at(ipoint).type == KFactorType::Linear){
       double A = OtherKFactorList.at(i).at(ipoint).parameters.at(0);
       FinalOtherKFactor.at(ipoint) *= (1.0 + A * z);
     }
     else if(OtherKFactorList.at(i).at(ipoint).type == KFactorType::Quadratic){
       double A = OtherKFactorList.at(i).at(ipoint).parameters.at(0);
       double B = OtherKFactorList.at(i).at(ipoint).parameters.at(1);
       double C = OtherKFactorList.at(i).at(ipoint).parameters.at(2);
       FinalOtherKFactor.at(ipoint) *= (1.0 + A * z * z + B * z + C);
     }
   }
 }

 if(subType == "cdfLasy" || subType == "cdfLasy_up" || subType == "cdfLasy2" || subType == "cdfLasy2_up"
 || subType == "d02Masy1" || subType == "d02Masy1_up" || subType == "CMS7Masy2" || subType == "CMS7Masy2_up"
 || subType == "CMS7Easy" || subType == "CMS7Easy_up" || subType == "d02Easy5" || subType == "d02Easy5_up"){

   if(FinalOtherKFactor.size() / 2 != m_data.size()) cout<<"ERROR! Other kfactor for "<<subType<<" doesn't match with data. kfactor size = "<<FinalOtherKFactor.size()<<"  data size = "<<m_data.size()<<endl;

   for(int i = 0; i < m_data.size(); i++){
     double wp_kfac0 = m_data.at(i).wp_kfac0;
     double wm_kfac0 = m_data.at(i).wm_kfac0;
     m_data.at(i).wp_kfac = wp_kfac0 * FinalOtherKFactor.at(i);
     m_data.at(i).wm_kfac = wm_kfac0 * FinalOtherKFactor.at(i + m_data.size());

     m_data.at(i).OtherKFactor = 1.0;
   }
 }
 else if(subType == "ATL7_WZ" || subType == "ATL7_WZ_up"){
   if(FinalOtherKFactor.size() != m_data.size()) cout<<"ERROR! Other kfactor for "<<subType<<" doesn't match with data. kfactor size = "<<FinalOtherKFactor.size()<<"  data size = "<<m_data.size()<<endl;

   for(int i = 0; i < 30; i++){
     m_data.at(i).OtherKFactor = FinalOtherKFactor.at(i);
   }
   for(int i = 30; i < 41; i++){
     double wp_kfac0 = m_data.at(i).wp_kfac0;
     double wm_kfac0 = m_data.at(i).wm_kfac0;
     m_data.at(i).wp_kfac = wp_kfac0 * FinalOtherKFactor.at(i - 30);
     m_data.at(i).wm_kfac = wm_kfac0 * FinalOtherKFactor.at(i - 9);

     m_data.at(i).OtherKFactor = 1.0;
   }
 }
 else if(subType == "LHCb8WZ"){
   if(FinalOtherKFactor.size() != m_data.size() + 8) cout<<"ERROR! Other kfactor for "<<subType<<" doesn't match with data. kfactor size = "<<FinalOtherKFactor.size()<<"  data size = "<<m_data.size()<<endl;

   for(int i = 0; i < m_data.size(); i++){
     m_data.at(i).OtherKFactor = FinalOtherKFactor.at(i);
   }
 }
 else{
   if(FinalOtherKFactor.size() != m_data.size()) cout<<"ERROR! Other kfactor for "<<subType<<" doesn't match with data. kfactor size = "<<FinalOtherKFactor.size()<<"  data size = "<<m_data.size()<<endl;

   for(int i = 0; i < m_data.size(); i++){
     m_data.at(i).OtherKFactor = FinalOtherKFactor.at(i);
   }
 }

}
