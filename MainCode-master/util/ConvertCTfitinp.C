#include <iostream>
#include <fstream>
#include "RootCommon.h"

using namespace std;

std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(s[start])) start++;

    size_t end = s.size();
    while (end > start && std::isspace(s[end-1])) end--;

    return s.substr(start, end - start);
}

void parse_line(const std::string& line,
                std::string& flavor,
                std::vector<int>& list)
{
    size_t q1 = line.find('\'');
    size_t q2 = line.find('\'', q1 + 1);

    if (q1 == std::string::npos || q2 == std::string::npos) {
        throw std::runtime_error("Flavor quotes not found");
    }

    flavor = line.substr(q1 + 1, q2 - q1 - 1);
    flavor = trim(flavor);

    std::string rest = line.substr(q2 + 1);
    std::istringstream iss(rest);

    int value;
    std::vector<int> all;

    while (iss >> value) {
        all.push_back(value);
    }

    if (all.size() > 2)
        list.assign(all.begin() + 2, all.end());
    else
        list.clear();
}

void parse_line_double(const std::string& line,
                std::string& flavor,
                int& index,
                double& v1,
                double& v2,
                std::vector<double>& params)
{
    size_t q1 = line.find('\'');
    size_t q2 = line.find('\'', q1 + 1);
    if (q1 == std::string::npos || q2 == std::string::npos)
        throw std::runtime_error("Flavor quotes not found");

    flavor = trim(line.substr(q1 + 1, q2 - q1 - 1));

    std::string rest = line.substr(q2 + 1);
    std::istringstream iss(rest);

    iss >> index;
    iss >> v1;
    iss >> v2;

    params.clear();
    double x;
    while (iss >> x) {
        params.push_back(x);
    }
}

int main(int argc, char** argv)
{
 if(argc != 3){
   cout<<"Usage: ./ConvertCTfitinp fitinp Parameters.yml"<<endl;
   return 0;
 }

 string FileLine;

 vector<TString> FlavorList;
 vector<int> gfunList;
 vector<double> MomentumList;
 vector<double> B0List;
 vector<vector<int>> SwitchList;
 vector<vector<double>> ParameterList;
 vector<TString> NameList;
 vector<int> IndexList;

 ifstream Input(argv[1]);

 int Nflavor = 6;
 while(getline(Input, FileLine)){
   if(FileLine.find("++ 6") != std::string::npos) {
     stringstream LineString(FileLine);
     string skip;
     int Nfval, Nfsea;
     LineString >> skip >> skip >> Nfval >> Nfsea;
     Nflavor = Nfval - Nfsea;

     break;
   }
 }

 getline(Input, FileLine);
 getline(Input, FileLine);

 for(int i = 0; i < Nflavor; i++){
   getline(Input, FileLine);
   string flavor;
   vector<int> list;

   parse_line(FileLine, flavor, list);

   if(flavor == "3svl") FlavorList.push_back("svl");
   if(flavor == "2dvl") FlavorList.push_back("dv");
   if(flavor == "1uvl") FlavorList.push_back("uv");
   if(flavor == "0glu") FlavorList.push_back("gluon");
   if(flavor == "-1dmu") FlavorList.push_back("dmu");
   if(flavor == "-2dpu") FlavorList.push_back("dpu");
   if(flavor == "-3str") FlavorList.push_back("str");

   SwitchList.push_back(list);
 }

 getline(Input, FileLine);
 getline(Input, FileLine);

 for(int i = 0; i < Nflavor; i++){
   getline(Input, FileLine);
   string flavor;
   int gfun;
   double momentum;
   double B0;
   vector<double> list;

   parse_line_double(FileLine, flavor, gfun, momentum, B0, list);

   gfunList.push_back(gfun);
   MomentumList.push_back(momentum);
   B0List.push_back(B0);

   if(list.size() != SwitchList.at(i).size()) cout<<"WARNING! mismatch!"<<endl;
   ParameterList.push_back(list);
 }

 map<int, double> IndexParMap;

 for(int i = 0; i < SwitchList.size(); i++){
   for(int j = 0; j < SwitchList.at(i).size(); j++){
     IndexParMap[SwitchList.at(i).at(j)] = ParameterList.at(i).at(j);
   }
 }

 IndexParMap[10] = 0.0;
 IndexParMap[60] = 0.0;
 IndexParMap[71] = 1.0;
 IndexParMap[72] = 1.0;
 IndexParMap[73] = 1.0;

 while(getline(Input, FileLine)){
   if(FileLine.find("++ 9") != std::string::npos) {
     break;
   }
 }

 getline(Input, FileLine);
 getline(Input, FileLine);

 while (std::getline(Input, FileLine)) {

     if (FileLine.empty()) continue;

     if (FileLine.find("set print") != std::string::npos) {
         break;
     }

     std::istringstream iss(FileLine);

     int id;
     std::string name;
     double v1, v2;

     if (!(iss >> id >> name >> v1 >> v2))
         continue;

     if (!name.empty() && name.front() == '\'') name.erase(0,1);
     if (!name.empty() && name.back()  == '\'') name.pop_back();

     if(name == "alpha" || name == "mc" || name == "mb") continue;

     NameList.push_back(name.c_str());
     IndexList.push_back(id);
 }

 ofstream Output(argv[2]);

 Output << "Parameter:" << endl;

 for(int i = 0; i < IndexList.size(); i++){
   Output << "  - parameter: [";
   Output << setw(2) << IndexList.at(i);
   Output << ",  ";
   Output << NameList.at(i) << ",  ";
   Output << setw(8 + 5 - NameList.at(i).Length()) << *right << fixed << setprecision(5) << IndexParMap[IndexList.at(i)];
   Output << ",   0.05,   0.0,   1.0]" << endl;
 }

 Output << "PDFParameterization: # IFun = 1(CT18), 2(CT18As)" << endl;
 Output << "  IFun: 1" << endl;
 Output << "ShapeMatch:" << endl;
 for(int i = 0; i < FlavorList.size(); i++){
   Output << "  - parameter: [";
   Output << FlavorList.at(i);
   Output << ",";
   Output << setw(9 - FlavorList.at(i).Length())<<*right<<gfunList.at(i);
   Output << ", [";
   int MaxSize = SwitchList.at(i).size();
   if(MaxSize >= 15) MaxSize = 15;
   for(int ip = 0; ip < MaxSize; ip++){
     Output << setw(3) << *right << SwitchList.at(i).at(ip);
     if(ip != MaxSize - 1) Output << ",";
   }
   Output << "]]" << endl;
 }
 Output << "CentralValue:" << endl;
 Output << "             # flavor  momentum        B0        shape parameters" << endl;
 for(int i = 0; i < FlavorList.size(); i++){
   Output << "  - parameter: [";
   Output << FlavorList.at(i);
   Output << ",";
   Output << setw(15 - FlavorList.at(i).Length()) << *right << fixed << setprecision(7) << MomentumList.at(i);
   Output << ",";
   Output << setw(11) << *right << fixed << setprecision(7) << B0List.at(i);
   Output << ",  [";
   int MaxSize = ParameterList.at(i).size();
   if(MaxSize >= 15) MaxSize = 15;
   for(int ip = 0; ip < MaxSize; ip++){
     Output << setw(9) << *right << fixed << setprecision(5) << ParameterList.at(i).at(ip);
     if(ip != MaxSize - 1) Output << ",";
   }
   Output << "]]" << endl;
 }

 return 1;
}
