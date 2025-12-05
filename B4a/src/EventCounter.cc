#include "EventCounter.hh"

// ---------------------------------------------------------
// STATIC MEMBER DEFINITIONS
// You must have one line here for EVERY static variable in your .hh file
// ---------------------------------------------------------

// 1. Current Event Counters
G4int EventCounter::counter = 0;
G4double EventCounter::energy = 0.0;
std::vector<G4ThreeVector> EventCounter::photonStartingPositions;

// 2. Global Max/Statistics
G4int EventCounter::maxCounter = 0;
G4double EventCounter::maxEnergy = 0.0;
std::vector<G4ThreeVector> EventCounter::photonStartingPositionsMax;
G4int EventCounter::maxMuons = 0;

// 3. Data Storage
std::vector<std::pair<G4int, G4ThreeVector>> EventCounter::muonData;
std::pair<G4int, G4ThreeVector> EventCounter::muonWithMaxPhotons;

// 4. THE MISSING ONE (Fixes your current error)
std::vector<G4int> EventCounter::photonCounter;

// 5. Muon Positions
// Note: In your header, you had "std::vector<G4ThreeVector, G4int>" which is invalid syntax.
// Assuming you meant a vector of pairs, or just vectors:
// Use ONE of the following lines depending on how you fixed the header:
std::vector<G4ThreeVector> EventCounter::muonPositions;
std::vector<std::pair<G4ThreeVector, G4int>> EventCounter::muonDataPerEvent;

// OR if you used pairs:
// std::vector<std::pair<G4ThreeVector, G4int>> EventCounter::muonPositions;