#include "Tools/HistFormula.h"

using namespace std;

void HistFormula::FindBracket(TString &formula, int &leftIndex, int &lastright, TString &subtmpformula)
{
 int lastleft = -1;

 while(1){
   lastleft = formula.Index("(", leftIndex + 1);
   lastright = formula.Index(")");
   if(lastleft == -1 || lastright == -1) break;
   if(lastleft < lastright) leftIndex = lastleft;
   if(lastleft > lastright) break;
 }

 if(lastright == -1) return;
 while(formula(leftIndex - 1, 1) == "(" && formula(lastright + 1, 1) == ")"){
   formula.Remove(leftIndex - 1, 1);
   formula.Remove(lastright, 1);
   leftIndex = leftIndex - 1;
   lastright = lastright - 1;
 }

 while(lastleft != -1 && lastright != -1 && (formula(leftIndex - 1, 1) == "/" || formula(leftIndex - 1, 1) == "*")){
   if(formula(leftIndex - 2, 1) == "]") leftIndex = leftIndex - 4;
   if(((TString)formula(leftIndex - 2, 1)).IsDec() && formula(leftIndex - 3, 1) != "n") leftIndex = leftIndex - 2;
   if(formula(leftIndex - 3, 1) == "n") leftIndex = leftIndex - 12;
 }
 while(lastleft != -1 && lastright != -1 && (formula(lastright + 1, 1) == "/" || formula(lastright + 1, 1) == "*")){ 
   if(formula(lastright + 2, 1) == "[") lastright = lastright + 4;
   else if(((TString)formula(lastright + 2, 1)).IsDec()) lastright = lastright + 2;
   else if(formula(lastright + 2, 1) == "E") lastright = lastright + 12;
   else break;
 }

   subtmpformula = formula(leftIndex, lastright - leftIndex + 1);
   if(!subtmpformula.Contains("Expression")){
     formula = formula.Replace(leftIndex, lastright - leftIndex + 1, "Expression1");
     return;
   }
   if(subtmpformula.Contains("Expression4")){
     formula = formula.Replace(leftIndex, lastright - leftIndex + 1, "Expression5");
     return;
   }
   if(subtmpformula.Contains("Expression3")){
     formula = formula.Replace(leftIndex, lastright - leftIndex + 1, "Expression4");
     return;
   }
   if(subtmpformula.Contains("Expression2")){
     formula = formula.Replace(leftIndex, lastright - leftIndex + 1, "Expression3");
     return;
   }
   if(subtmpformula.Contains("Expression1")){
     formula = formula.Replace(leftIndex, lastright - leftIndex + 1, "Expression2");
     return;
   }

   return;
}

void HistFormula::DecomposeExpression(TString &formula)
{
 int leftIndex = -1;
 int lastleft = -1;
 int lastright = -1;
 cout<<formula<<endl;

 vector<TString> Para;
 vector<TString> Operator;
 vector<TString> BracketPara;
 vector<TString> BracketOperator;

 TString tmpformula = formula;

 while(tmpformula.Length() != 0){
   if(((TString)tmpformula(0, 1)).IsDec()){//k factor
     Para.push_back(tmpformula(0, 1));
     if(tmpformula.Length() != 1){
       Operator.push_back(tmpformula(1, 1));
       tmpformula.Remove(0, 2);
     }
     else{
       Operator.push_back("End");
       tmpformula.Remove(0, 1);
     }
   }
   if(((TString)tmpformula(0, 1)) == "["){//parameter
     Para.push_back(tmpformula(0, 3));
     if(tmpformula.Length() != 3){
       Operator.push_back(tmpformula(3, 1));
       tmpformula.Remove(0, 4);
     }
     else{
       Operator.push_back("End");
       tmpformula.Remove(0, 3);
     }
   }
   if(((TString)tmpformula(0, 1)) == "E"){//Expression
     Para.push_back(tmpformula(0, 11));
     if(tmpformula.Length() != 11){
       Operator.push_back(tmpformula(11, 1));
       tmpformula.Remove(0, 12);
     }
     else{
       Operator.push_back("End");
       tmpformula.Remove(0, 11);
     }
   }
   if(((TString)tmpformula(0, 1)) == "("){//bracket
     int leftIndex = tmpformula.Index("(");
     tmpformula.Remove(leftIndex, 1);
     Para.push_back("");

     while(((TString)tmpformula(0, 1)) != ")"){
       if(((TString)tmpformula(0, 1)).IsDec()){//k factor
         BracketPara.push_back(tmpformula(0, 1));
         if(((TString)tmpformula(1, 1)) == ")"){
           BracketOperator.push_back(")");
           tmpformula.Remove(0, 1);
         }
         else{
           BracketOperator.push_back(tmpformula(1, 1));
           tmpformula.Remove(0, 2);
         }
       }
       if(((TString)tmpformula(0, 1)) == "["){//parameter
         BracketPara.push_back(tmpformula(0, 3));
         if(((TString)tmpformula(3, 1)) == ")"){
           BracketOperator.push_back(")");
           tmpformula.Remove(0, 3);
         }
         else{
           BracketOperator.push_back(tmpformula(3, 1));
           tmpformula.Remove(0, 4);
         }
       }
       if(((TString)tmpformula(0, 1)) == "E"){//Expression
         BracketPara.push_back(tmpformula(0, 11));
         if(((TString)tmpformula(11, 1)) == ")"){
           BracketOperator.push_back(")");
           tmpformula.Remove(0, 11);
         }
         else{
           BracketOperator.push_back(tmpformula(11, 1));
           tmpformula.Remove(0, 12);
         }
       }
     }
     tmpformula.Remove(0, 1);
     if(tmpformula != ""){
       Operator.push_back(tmpformula(0, 1));
       tmpformula.Remove(0, 1);
     }
     else{
       Operator.push_back("(");
     }
   }//process bracket
 }

 for(int i = 0; i < Para.size(); i++){
   cout<<Para.at(i)<<" "<<Operator.at(i)<<" ";
 }
 for(int i = 0; i < BracketPara.size(); i++){
   cout<<BracketPara.at(i)<<" "<<BracketOperator.at(i)<<" ";
 }
 cout<<endl;

}

void HistFormula::ProcessFormula()
{
 TString formula = "([0] * ([0] - [1]) / ([0] + [1]) * [1] + ([2] + [3]) / ([2] - [3])) * ([3] + ([3] - [4]) / ([3] + [4]) + ([4] + [5]) + [6]) * (([7] + [8]))";
 formula.ReplaceAll(" ", "");
 TString tmpformula = formula;
 vector<int> CalLevel;
 map<TString, int> FormulaLevel;
 vector<TString> SubFormula;
 map<int, TString> Charactor;
 int FormulaPart = 0;

 if(tmpformula.Contains("(")){
   while(1){
     FormulaPart++;
     int leftIndex = -1;
     int lastleft = -1;
     int lastright = -1;
     TString subtmpformula;
     FindBracket(tmpformula, leftIndex, lastright, subtmpformula);

     DecomposeExpression(subtmpformula);
     SubFormula.push_back(subtmpformula);
     if(lastright == -1) break;
   }
 }

 for(int i = 0; i < SubFormula.size(); i++){
   cout<<SubFormula.at(i)<<endl;
 }

 cout<<formula<<endl;
 for(auto iter = Charactor.begin(); iter != Charactor.end(); iter++){
   cout<<iter->second<<endl;
 }

}
