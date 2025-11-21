#include "DataVector.hh"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <vector>

#include "globals.hh" 
#include "G4ios.hh"    
#include "G4SystemOfUnits.hh"


using namespace std;

void DataVector::LoadFromFile(const G4String& filename , char comma) 
{
    values_.clear();

    ifstream infile(filename);
    if (!infile.is_open())
    {
        return;
    }


    std::ostringstream oss;
    oss << infile.rdbuf();
    string content = oss.str();
    infile.close();


    size_t commentPos;
    while ((commentPos = content.find_first_of("#/")) != string::npos)
    {
        size_t endPos = content.find('\n', commentPos);
        content.erase(commentPos, endPos - commentPos);
    }


    stringstream ss(content);
    string token;
    while (getline(ss, token, comma))
    {
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        if (!token.empty())
            values_.push_back(ParseToken(token));
    }

    if (!values_.empty())
        SortVector(true);

}

G4double DataVector::ParseToken(const string& token) 
{
    
    size_t starPos = token.find('*');
    string numStr, unitStr;

    if (starPos != string::npos) {
        numStr = token.substr(0, starPos);
        unitStr = token.substr(starPos + 1);
    } else {
        
        for (char c : token) 
        {
            if (isdigit(c) || c == '.' || c == '-' || c == '+' || c == 'e' || c == 'E')
                numStr += c;
            else
                unitStr += c;
        }
    }

    if (numStr.empty()) 
    {

        return 0.0;
    }

    G4double value = stod(numStr);

    if (!unitStr.empty()) 
    {
        G4double unitVal = G4UnitDefinition::GetValueOf(unitStr);
        if (unitVal != 0.0)
            return value * unitVal;

    }

    return value;
}

void DataVector::Print(const G4String& unit) const 
{
    G4double unitVal = G4UnitDefinition::GetValueOf(unit);
    if (unitVal == 0.0) unitVal = 1.0;

    for (size_t i = 0; i < values_.size(); ++i)
        G4cout << i << ": " << values_[i] / unitVal << " " << unit << G4endl;
}

G4double *DataVector::GetVector()
{
  return values_.data();
}

int DataVector::GetLength()
{
    return values_.size();
}

void DataVector::SortVector(bool ascending)
{

    std::sort(values_.begin(), values_.end(),
                [ascending](const G4double& a, const G4double& b) {
                    return ascending ? (a < b) : (a > b);
                });

}
