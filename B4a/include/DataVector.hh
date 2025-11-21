#ifndef DATAVECTOR_HH
#define DATAVECTOR_HH

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class DataVector 
{
vector<G4double> values_;
G4double ParseToken(const string& token);

public:
    DataVector() = default;
    DataVector(const G4String& filename , char comma) { LoadFromFile(filename , comma); }

    void LoadFromFile(const G4String& filename, char comma);

    const vector<G4double>& GetValues() const { return values_; }
    void Print(const G4String& unit = "eV") const;
    
    G4double* GetVector();

    void SortVector(bool);

    int GetLength();

};

#endif
