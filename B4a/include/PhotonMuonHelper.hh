#pragma once
#include <unordered_map>
#include <unordered_set>

#include "G4ThreeVector.hh"

class PhotonMuonHelper {
public:
    std::unordered_map<G4int, G4ThreeVector> muonStartMap; // muon trackID → vertex
    std::unordered_map<G4int, G4int> parentMap;            // any trackID → parentID
    std::unordered_map<G4int, bool> isMuonFamily;
    std::unordered_set<G4int> muonsAlreadyHit;

    void Clear() {
        muonStartMap.clear();
        parentMap.clear();
        isMuonFamily.clear();
        muonsAlreadyHit.clear();
    }
};
