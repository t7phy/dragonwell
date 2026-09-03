#include "Tools/Tools.h"

void TrimString(std::string &s)
{
 if(s.empty()){
   return;
 }
 s.erase(0,s.find_first_not_of(" "));
 s.erase(s.find_last_not_of(" ") + 1);
}

bool isInteger(const std::string &str) {
 std::istringstream iss(str);
 int number;
 if (!(iss >> number)) return false;
 else return true;
 //cout<<"isInteger: "<<iss.get()<<"   "<<iss.eof()<<endl;
 //return iss.get() == iss.eof();
}

bool isFloat(const std::string &str) {
 std::istringstream iss(str);
 float number;
 char dot = '.';
 if (!(iss >> number)) return false;
 else return true;
 //if (iss >> std::noskipws >> dot >> number) return false;
 //return iss.get() == iss.eof();
}

std::vector<std::string> Tokenizestring(std::string line, std::string delimiters, std::string commentString, bool KeepQuote)
{
// This function is copied from Alim

    std::vector<std::string> tokens;
    std::string token;
    bool insideQuotes = false;
    char currentQuoteChar = '\0'; // Track the type of quotation mark (single or double) currently enclosing the text in a string.

    for (char c : line)
    {
        if (!insideQuotes && commentString.find(c) != std::string::npos)
        {
            break;
        }

        if ((c == '"' || c == '\'') && (!insideQuotes || c == currentQuoteChar))
        {
            if (!insideQuotes)
            {
                insideQuotes = true;
                currentQuoteChar = c;
            }
            else
            {
                insideQuotes = false;
                currentQuoteChar = '\0';
            }

            if (KeepQuote)
            {
                token += c;
            }
        }
        else if (!insideQuotes && delimiters.find(c) != std::string::npos)
        {
            if (!token.empty())
            {
                tokens.push_back(std::move(token));
                token.clear();
            }
        }
        else
        {
            token += c;
        }
    }

    if (!token.empty())
    {
        tokens.push_back(std::move(token));
    }

    return tokens;
}

std::vector<TString> Str2Tok(TString str, TString delimiters, TString commentString, bool KeepQuote)
{
// This function is copied from Alim

    auto tokens = Tokenizestring(str.Data(), delimiters.Data(), commentString.Data(), KeepQuote);
    std::vector<TString> result(tokens.begin(), tokens.end());
    return result;
}

std::vector<std::vector<TString>> GetLinesTokenized(vector<TString> FullFile, TString BeginTag, TString EndTag, bool RemoveEmptyLine, bool RemoveTag, TString Delimiter, TString CommentString)
{
// This function is copied from Alim

    std::vector<std::vector<TString>> Result;

    map<TString, int> TagMaps;
    vector<vector<TString>> File22DVector;

    for(int i = 0; i < FullFile.size(); i++){
      File22DVector.push_back(Str2Tok(FullFile.at(i), Delimiter, CommentString));
    }

    for(size_t i = 0; i < File22DVector.size(); i++){
       if(File22DVector.at(i).size() > 0)
            TagMaps[File22DVector.at(i).at(0)] = i + 1;
    }

    int BeginLine, EndLine;
    if (TagMaps.count(BeginTag) > 0)
    {
        BeginLine = TagMaps.at(BeginTag);
    }
    else
    {
        std::cout << " Tag = " << BeginTag << " not found " << std::endl;
        //exit(1);
        return Result; // do nothing if did not find Tag
    }

    if (TagMaps.count(EndTag) > 0)
    {
        EndLine = TagMaps.at(EndTag);
    }
    else
    {
        std::cout << " Tag = " << BeginTag << " not found " << std::endl;
        exit(1);
    }

    function<std::vector<std::vector<TString>>(int, int)> f_GetLinesTokenized = [&](int LineBegin, int LineEnd){
      if (LineEnd == -1)
          LineEnd = File22DVector.size();
      if (LineBegin < 1 || LineBegin > LineEnd || LineEnd > (int)File22DVector.size())
      {
          std::cout << "Illigal requirement LineBegin < 1 or LineBegin > LineEnd or LineEnd out of range" << std::endl;
          exit(1);
      }
      std::vector<std::vector<TString>> tmp;
      for (int i = LineBegin; i <= LineEnd; i++)
          tmp.push_back(File22DVector.at(i - 1));
      return tmp;
    };

    if (RemoveTag)
    {
        Result = f_GetLinesTokenized(BeginLine + 1, EndLine - 1);
    }
    else
    {
        Result = f_GetLinesTokenized(BeginLine, EndLine);
    }

    if (RemoveEmptyLine)
    {
        Result.erase(std::remove_if(Result.begin(), Result.end(), [](const std::vector<TString> &v) { return v.empty(); }), Result.end());
    }

    return Result;
}

std::map<TString, std::vector<TString>> ListAnalyzer(const std::vector<std::vector<TString>> &VectorList)
{
// This function is copied from Alim

    std::map<TString, std::vector<TString>> resultMap;
    
    // Iterate through each vector in VectorList
    for (const auto &vec : VectorList)
    {   
        if (vec.empty())
            continue; // Skip empty vectors
        
        TString key = vec[0];
        std::vector<TString> values(vec.begin() + 1, vec.end()); // Get values excluding the key
        
        // Check if key needs substitution
        values[0] = values[0].Strip(values[0].kBoth); // remove leading and trailing empty char
        if (values[0].BeginsWith("${") && values[0].EndsWith("}"))
        {   
            TString variableName = values[0](2, values[0].Length() - 3); // Extract variable name without ${ and }
            
            // Look up the variable name in resultMap to get its current value(s)
            auto it = resultMap.find(variableName);
            if (it != resultMap.end())
            {   
                values = resultMap.at(variableName);
                // values.insert(values.begin(), it->second.begin(), it->second.end());  // Substitute values
            }
            else
            {   
                std::cerr << "Warning: Variable " << variableName.Data() << " not found!" << std::endl;
            }
            
            // Use original key for storage or decide how to handle variables.
            resultMap[key] = values;
        }
        else
        {   
            resultMap[key] = values; // Directly store without substitution
        }
    }
    
    return resultMap;
}

