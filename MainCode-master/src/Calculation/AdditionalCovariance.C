#include "Calculation/Dataset.h"

void Dataset::InputAdditionalCorrMatrix(vector<TString> names)
{
 isAdditionalCovariance = true;

 AdditionalCorrMatrixNames = names;

 for(int i = 0; i < AdditionalCorrMatrixNames.size(); i++){
   ReadCovarianceMatrix(AdditionalCorrMatrixNames.at(i));
 }

 GetCovarianceMatrix();
}

void Dataset::ReadCovarianceMatrix(TString name)
{
 vector<TString> MatrixType;
 vector<TString> MatrixName;
 vector<bool> MatrixKeepDiagonal;
 std::vector<std::vector<std::vector<double>>> MatrixContent;

 function<std::vector<std::vector<double>>(std::vector<std::vector<TString>>)> Str2D = [&](std::vector<std::vector<TString>> V2D){
   std::vector<std::vector<double>> VV;

   for(int i = 0; i < V2D.size(); i++){
     std::vector<double> V1;
     for(int j = 0; j < V2D.at(i).size(); j++){
       V1.push_back(V2D.at(i).at(j).Atof());
     }
     VV.push_back(V1);
   }

   return VV;
 };

 ifstream CorrMatrixFile(name);

 string line;
 vector<TString> FullMatrixFile;

 while(getline(CorrMatrixFile, line)){
   FullMatrixFile.push_back(line.c_str());
 }

 std::vector<std::vector<TString>> Config = GetLinesTokenized(FullMatrixFile, "BeginConfiguration", "EndConfiguration", true, true, " ,=\t", "#");
 std::map<TString, std::vector<TString>> mConfig = ListAnalyzer(Config);

 // ReadMatrix
 if(mConfig.count("MatrixList") > 0){
   auto my_matrix_list = mConfig["MatrixList"];
   for (auto i : my_matrix_list){
     auto List = Str2Tok(i,":");
     // MatrixType
     if (List[0].BeginsWith("CorrelationMatrix")) {
             MatrixType.push_back( "CorrelationMatrix");
     }
     else if (List[0].BeginsWith("CovarianceMatrix")) {
             MatrixType.push_back( "CovarianceMatrix");
     }
     else {
             std::cout << "Error: Unknown Matrix Type\n Matrix Type  can be CorrelationMatrix or CovarianceMatrix " << List[0] << std::endl;
             exit(1);
     }
     MatrixName.push_back(List[0]);
     //Matrix content
     MatrixContent.push_back(Str2D(GetLinesTokenized(FullMatrixFile, "Begin" + List[0], "End" + List[0], true, true, " ,=\t", "#")));
     // Matrix Digonal elements treatment
     List.resize(2);
     List[1].ToLower();
     if ( List[1] =="" || List[1].BeginsWith("t") || List[1].BeginsWith("y") ){
             MatrixKeepDiagonal.push_back(true);
     }
     else{
             MatrixKeepDiagonal.push_back(false);
     }
   }
 }
 else {
   std::cout << "Error: No MatrixList found in the configuration file" << std::endl;
   exit(1);
 }

 // check Matrix size
 size_t MatrixSize = MatrixContent[0].size();
 for (size_t i = 0; i < MatrixContent.size(); i++){
   if (MatrixType[i] == "CorrelationMatrix"){
     auto M = MatrixContent[i];
     // check matrix size
     for (size_t j = 0; j < M.size(); j++){
       if (M[j].size() - 1 != MatrixSize){
         std::cout << "Error: Matrix " << MatrixName[i] << " is not square" << std::endl;
         std::cout << "Matrix size: " << MatrixSize << ", but there is " << M[j].size() - 1 << " element at line " << j + 1 << std::endl;
         exit(1);
       }
     }
   }
   else if (MatrixType[i] == "CovarianceMatrix"){
     auto M = MatrixContent[i];
     for (size_t j = 0; j < M.size(); j++){
       if (M[j].size() != MatrixSize){
         std::cout << "Error: Matrix " << MatrixName[i] << " is not square" << std::endl;
         std::cout << "Matrix size: " << MatrixSize << ", but there is " << M[j].size() - 1 << " element at line " << j + 1 << std::endl;
       }
     }
   }
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 function<bool(std::vector<std::vector<double>>)> IsSymetricMatrix = [&](std::vector<std::vector<double>> Matrix){
   bool result = true;
   // check if matrix is square
   for ( size_t i = 0; i < Matrix.size(); i++ ){
     if (Matrix.size() != Matrix[i].size()){
       result = false;
       break;
     }
   }

   if (!result ) {
     std::cout << "Matrix is not square: " << result << std::endl;
     return result;
   }

   // check if matrix is symetric
   for ( size_t i = 0; i < Matrix.size(); i++ ){
     for ( size_t j = 0; j < Matrix[i].size(); j++ ){
       if ( Matrix[i][j] != Matrix[j][i] ){
         result = false;
         break;
       }
     }
   }

   return result;
 };

 function<std::pair<std::vector<double >, std::vector<std::vector<double>>>(std::vector<std::vector<double>>)> SplitCorrelationMatrix = [&](std::vector<std::vector<double>> Matrix){
   std::vector<double> CorValTmp;
   std::vector<std::vector<double>> CorMatrixTmp;
   std::vector<double> tmp;
   for (size_t i = 0; i < Matrix.size(); i++){
     tmp= Matrix[i];
     CorValTmp.push_back(tmp[0]);
     tmp.erase(tmp.begin());
     CorMatrixTmp.push_back(tmp);
   }
   return std::make_pair(CorValTmp,CorMatrixTmp);
 };

 function<std::vector<std::vector<double>>(std::vector<std::vector<double>>)> ConstructCovMatrixUsingCorMatrix = [&](std::vector<std::vector<double>> Matrix){
   auto s= SplitCorrelationMatrix(Matrix);
   std::vector<double> CorVal = s.first;
   std::vector<std::vector<double>> CorMatrix = s.second;

   std::vector<std::vector<double>> CovMatrix(CorVal.size(),std::vector<double>(CorVal.size(),0.0));

   if (IsSymetricMatrix(CorMatrix)){
     for (size_t i = 0; i < CorVal.size(); i++){
       for (size_t j = i; j < CorVal.size(); j++){
         CovMatrix[i][j] = CorVal[i]*CorMatrix[i][j]*CorVal[j];
         CovMatrix[j][i] = CovMatrix[i][j];
       }
     }
   }

   return CovMatrix;
 };

 if(MatrixContent[0].size() != NPoints){
   cout<<"ERROR! Additional correlation matrix doesn't match with data table!"<<endl;
 }

 AdditionalCovMatrixMap[name] = std::vector<std::vector<double>>(NPoints, std::vector<double>(NPoints, 0.0));

 for (size_t i = 0; i < MatrixContent.size(); i++){
   std::vector<std::vector<double>> M(MatrixContent[i].size(), std::vector<double>(MatrixContent[i].size(), 0.0));

   if (MatrixType[i] == "CorrelationMatrix"){  
     M = ConstructCovMatrixUsingCorMatrix(MatrixContent[i]);
   }
   else if  (MatrixType[i] == "CovarianceMatrix"){
     if (IsSymetricMatrix(MatrixContent[i])){
       M = MatrixContent[i];
     }
   }
   
   if (!MatrixKeepDiagonal[i]){ 
     for (size_t j = 0; j < M.size(); j++){
       M[j][j] = 0.0;
     }
   }

   for (size_t j = 0; j < M.size(); j++){
     for (size_t k = 0; k < M.size(); k++){
       AdditionalCovMatrixMap.at(name)[j][k] += M[j][k];
     }
   }
 }

}

void Dataset::GetCovarianceMatrix()
{
 AdditionalCovariance = Eigen::MatrixXd::Zero(NPoints, NPoints);

 for(auto iter = AdditionalCovMatrixMap.begin(); iter != AdditionalCovMatrixMap.end(); iter++){
   for(int i = 0; i < iter->second.size(); i++){
     for(int j = 0; j < iter->second.at(i).size(); j++){
       AdditionalCovariance(i, j) += iter->second.at(i).at(j);
     }
   }
 }
}

void Dataset::PrepareLLT()
{
 // V0 = S^2 + AdditionalCovariance
 Eigen::MatrixXd V0 = AdditionalCovariance;

 for(int i = 0; i < m_data.size(); i++){
   V0(i, i) += UnCorr(i) * UnCorr(i);
 }

 // V0 = L * L^T
 Eigen::LLT<Eigen::MatrixXd> chol(V0);
 LMatrix = chol.matrixL();

 // W = L^{-1} * beta
 WMatrix = LMatrix.triangularView<Eigen::Lower>().solve(beta);

 isPrepareLLT = true;
}

