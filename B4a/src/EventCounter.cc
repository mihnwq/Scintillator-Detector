#include "EventCounter.hh"

#include <G4Types.hh>

G4int EventCounter::counter = 0;
G4double EventCounter::energy = 0.0;
std::vector<G4ThreeVector> EventCounter::photonStartingPositions;

std::vector<G4ThreeVector> EventCounter::photonStartingPositionsMax;
G4int EventCounter::maxCounter = 0;
G4double EventCounter::maxEnergy = 0.0;

std::vector<std::pair<G4int,G4ThreeVector>> EventCounter::muonData;
std::pair<G4int,G4ThreeVector> EventCounter::muonWithMaxPhotons;

G4int EventCounter::maxMuons = 0;