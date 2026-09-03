#include <iostream>
#include <fstream>

#include "RootCommon.h"
#include <assert.h>
#include <yaml-cpp/yaml.h>

#define MLSERVERCONF "./ML_Alg.yaml"
#include "Calculation/Config.h"

using namespace std;

int main(int argc, char** argv)
{

/*
    YAML::Node GlobalPath;
    GlobalPath["data"] = "/msu/data/t3work12/yaofu/FittingCode/da/data2021.0324/";
    GlobalPath["applgrid"] = "/msu/data/t3work12/yaofu/FittingCode/ApplGridtables/";
    GlobalPath["fastnlo"] = "/msu/data/t3work12/yaofu/FittingCode/fastNLOtables/";

    YAML::Node Nodes;

    Nodes["LHCb7ZWrap"]["Path"] = "LHCb7ZWrap";
    Nodes["LHCb7ZWrap"]["DataType"] = "DrellYan";
    Nodes["LHCb7ZWrap"]["CalcMode"] = "ApplGrid";
    Nodes["LHCb7ZWrap"]["Collider"] = "LHC";
    Nodes["LHCb7ZWrap"]["subType"] = "LHCb7ZWrap";

    YAML::Node Appl;
    YAML::Node Appl1;
    YAML::Node Appl2;
    YAML::Node Appl3;
    Appl1["grid"] = "245_1.root";
    Appl2["grid"] = "245_2.root";
    Appl3["grid"] = "245_3.root";


    Nodes["LHCb7ZWrap"]["ApplGrid"].push_back("245_1.root");
    Nodes["LHCb7ZWrap"]["ApplGrid"].push_back("245_2.root");
    Nodes["LHCb7ZWrap"]["ApplGrid"].push_back("245_3.root");
    Nodes["LHCb7ZWrap"]["ApplRange"].push_back(vector<int>{1, 1, 17});
    Nodes["LHCb7ZWrap"]["ApplRange"].push_back(vector<int>{2, 1, 17});



    YAML::Node rootnode;


    assert(rootnode.IsNull());  //
    // 1.
    rootnode["DataInformation"]["GlobalPath"] = GlobalPath;  //
    rootnode["DataInformation"]["SingleData"] = Nodes;


    std::ofstream file(MLSERVERCONF);
    file << rootnode <<std::endl;
    file.close();
*/

/*
  YAML::Node parameter;
  parameter = YAML::LoadFile("Parameters.yml");
  YAML::Node Parameter = parameter["Parameter"];
  YAML::Node CentralValue = parameter["CentralValue"];

  cout<<Parameter.size()<<endl;
  cout<<Parameter[0]["parameter"][0].as<int>()<<endl;
  cout<<Parameter[0]["parameter"][1].as<string>()<<endl;
  cout<<Parameter[0]["parameter"][2].as<double>()<<endl;
  cout<<Parameter[0]["parameter"][3].as<double>()<<endl;
  cout<<Parameter[0]["parameter"][4].as<double>()<<endl;
  cout<<Parameter[0]["parameter"][5].as<double>()<<endl;
  cout<<Parameter[1]["parameter"][0].as<int>()<<endl;
  cout<<Parameter[1]["parameter"][1].as<string>()<<endl;
  cout<<Parameter[1]["parameter"][2].as<double>()<<endl;
  cout<<Parameter[1]["parameter"][3].as<double>()<<endl;
  cout<<Parameter[1]["parameter"][4].as<double>()<<endl;
  cout<<Parameter[1]["parameter"][5].as<double>()<<endl;
  cout<<CentralValue[0]["parameter"][0].as<string>()<<endl;
  cout<<CentralValue[0]["parameter"][1].as<double>()<<endl;
  cout<<CentralValue[0]["parameter"][2].as<double>()<<endl;
  cout<<CentralValue[0]["parameter"][3][0].as<double>()<<endl;
  cout<<CentralValue[0]["parameter"][3][1].as<double>()<<endl;
  cout<<CentralValue[0]["parameter"][3][2].as<double>()<<endl;
*/

// Config setting;
// setting.ParseDataList("DataList.yml");

 Config setting;
 setting.ParseParameter("Parameters.yml");
 setting.OutputNewParameterFile("NewParameters.yml");

/*
 YAML::Node data;
 data = YAML::LoadFile("ML_Alg.yaml");

 YAML::Node global = data["GlobalPath"];

 cout<<global["data"].as<string>()<<endl;
 cout<<global["applgrid"].as<string>()<<endl;

 YAML::Node SingleData = data["DataInformation"];
 YAML::Node LHCb7ZWrap = SingleData["LHCb7ZWrap"];
 cout<<LHCb7ZWrap["Path"].as<string>()<<endl;
 cout<<LHCb7ZWrap["DataType"].as<string>()<<endl;
 cout<<LHCb7ZWrap["CalcMode"].as<string>()<<endl;
 cout<<LHCb7ZWrap["Collider"].as<string>()<<endl;
 cout<<LHCb7ZWrap["subType"].as<string>()<<endl;
 cout<<LHCb7ZWrap["ApplGrid"].as<vector<string>>().size()<<endl;
 cout<<LHCb7ZWrap["ApplGrid"][0].as<string>()<<endl;
 cout<<LHCb7ZWrap["ApplGrid"][1].as<string>()<<endl;
 cout<<LHCb7ZWrap["ApplGrid"][2].as<string>()<<endl;
 cout<<LHCb7ZWrap["ApplRange"][0][0].as<int>()<<endl;
 cout<<LHCb7ZWrap["ApplRange"][0][1].as<int>()<<endl;
 cout<<LHCb7ZWrap["ApplRange"][0][2].as<int>()<<endl;
 cout<<LHCb7ZWrap["ApplRange"].size()<<endl;
 cout<<LHCb7ZWrap["FastNLO"].size()<<endl;
 cout<<LHCb7ZWrap["KFactor"].size()<<endl;
 cout<<LHCb7ZWrap["Systematic"].size()<<endl;
*/

/*
    // 2
    YAML::Node mlserver_node;
    try{
        mlserver_node = YAML::LoadFile(MLSERVERCONF);
        // cout << mlserver_node << endl;
    }catch(YAML::BadFile &e){
        perror("YAML::Load(MLSERVERCONF) failed.\n");
        return 1;
    }
    if(!mlserver_node["MLServer"] || !mlserver_node["MLServer"].IsMap())
    {
        printf("no MLServer\n");
        return 2;
    }
    YAML::Node ml_root_node = mlserver_node["MLServer"];
    for(YAML::const_iterator iter = ml_root_node.begin(); iter != ml_root_node.end(); ++iter)
    {
        string ChildName = iter->first.as<string>();
        printf("ChildName:%s\n", ChildName.c_str());
        // 
        if(0 == ChildName.compare("MultiAddr") && iter->second.IsSequence())
        {
            for(int i = 0; i < iter->second.size(); ++i)
            {
                if(iter->second[0]["ip"] && iter->second[0]["ip"].IsScalar())
                {
                    string str_ip = iter->second[0]["ip"].as<string>();
                    printf("str_ip:%s\n", str_ip.c_str());
                }
            }
        }else if(0 == ChildName.compare("Nodes") && iter->second.IsMap()) //
        {
            for(YAML::const_iterator node_iter = iter->second.begin(); node_iter != iter->second.end(); ++node_iter)
            {
                string node_name = node_iter->first.as<string>();
                if(0 == node_name.compare("Midware"))
                {
                    YAML::Node module_node = node_iter->second;
                    if(module_node["CpuModel"] && module_node["CpuModel"].IsScalar())
                    {
                        string str_cpu_model = module_node["CpuModel"].as<string>();
                        printf("str_cpu_model:%s\n", str_cpu_model.c_str());
                    }
                }
            }
        }else if(0 == ChildName.compare("Version") && iter->second.IsScalar())
        {
            string str_version = iter->second.as<string>();
            printf("str_version:%s\n", str_version.c_str());
        }
    }
*/
    
    //YAML::Emitter out;
    return 0;
}
