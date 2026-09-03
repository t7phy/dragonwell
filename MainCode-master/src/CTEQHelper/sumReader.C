#include "CTEQHelper/sumReader.h"

sumReader::sumReader()
{

}

void sumReader::Initialize(const char* name)
{
 FileName = name;

 data.open(name);  
 if (!data) {
     std::cerr << "ERROR! Open file failed" << std::endl;
     return;
 }

 std::vector<std::string> buffer;
 std::string line;
 while (std::getline(data, line)) {
     buffer.push_back(line);
 }
 data.close();

 int lastIndex = -1;
 for (int i = 0; i < (int)buffer.size(); i++) {
     if (buffer[i].find("Chi2R") != std::string::npos) {
         lastIndex = i;
     }
 }

 if (lastIndex != -1 && lastIndex + 2 < (int)buffer.size()) {
     //std::cout << buffer[lastIndex + 1] << std::endl;
     //std::cout << buffer[lastIndex + 2] << std::endl;
 } else {
     std::cerr << "ERROR! Find Chi2R failed" << std::endl;
 }

 std::vector<std::string> targetLines = {
     buffer[lastIndex + 1],
     buffer[lastIndex + 2]
 };

 std::istringstream iss(targetLines.at(1));
 std::string tag;
 iss >> tag;

 iss >> RUNS >> PTS >> Chi2Wt >> C_dof >> Chi2R >> Chi2F0 >> Chi2F >> Chi2X
     >> LM_Var1 >> LM_Data1 >> LM_Coef1;

 /*std::cout << "RUNS     = " << RUNS << "\n"
           << "PTS      = " << PTS << "\n"
           << "Chi2Wt   = " << Chi2Wt << "\n"
           << "C/dof    = " << C_dof << "\n"
           << "Chi2R    = " << Chi2R << "\n"
           << "Chi2F0   = " << Chi2F0 << "\n"
           << "Chi2F    = " << Chi2F << "\n"
           << "Chi2X    = " << Chi2X << "\n"
           << "LM-Var1  = " << LM_Var1 << "\n"
           << "LM-Data1 = " << LM_Data1 << "\n"
           << "LM-Coef1 = " << LM_Coef1 << "\n";

 for (const auto& l : targetLines) {
     std::istringstream iss(l);
     std::string tag;
     iss >> tag;

     std::vector<double> numbers;
     double val;
     while (iss >> val) {
         numbers.push_back(val);
     }

     std::cout << tag << ": ";
     for (double v : numbers) {
         std::cout << v << " ";
     }
     std::cout << std::endl;
 }
 */
}

