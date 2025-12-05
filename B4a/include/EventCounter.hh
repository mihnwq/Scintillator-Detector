// EventCounter.h
#ifndef EVENTCOUNTER_H
#define EVENTCOUNTER_H

#include <G4ThreeVector.hh>

#include "G4Types.hh"
#include <iostream>
#include <vector>
#include "G4SystemOfUnits.hh"

class EventCounter {
public:
    static G4int counter;
    static G4double energy;
    static std::vector<G4ThreeVector> photonStartingPositions;

    static G4int maxCounter;
    static G4double maxEnergy;
    static std::vector<G4ThreeVector> photonStartingPositionsMax;


   static std::vector<std::pair<G4int, G4ThreeVector>> muonData;
    static std::pair<G4int, G4ThreeVector> muonWithMaxPhotons;
   static G4int maxMuons;

    static std::vector<G4int> photonCounter;
    static std::vector<G4ThreeVector> muonPositions;
    static std::vector<std::pair<G4ThreeVector,G4int>> muonDataPerEvent;
    // static std::vector<G4ThreeVector , G4int> muonPositions;

    EventCounter() {

    }


    static void BeginEvent()
    {
        counter = 0; // Reset per event
        energy = 0;
        photonStartingPositions.clear();
        muonData.clear();
     //   muonDataPerEvent.clear();
        //maxCOunter and maxEngery and the vectorMax never need to reset.
    }

    static void AddMuon(G4ThreeVector hitPosition)
    {
        muonData.push_back({0,hitPosition});

    }

    static void AddPhotonCOunt(G4int number) {
        photonCounter.push_back(number);
    }

    static G4int GetCountAt(G4int event) {
        return photonCounter[event];
    }

    static G4int GetNumberOfEvents() {
        return photonCounter.size();
    }


    static void AddMuonData(G4ThreeVector hitPosition) {
        muonDataPerEvent.push_back({hitPosition, 0});
    }

    static std::pair<G4ThreeVector,G4int> GetMeuonAT(G4int index) {
        return muonDataPerEvent[index];
    }

    static void SetEventAt(G4int eventIndex, G4int index) {
        muonDataPerEvent[index].second = eventIndex;
    }

    static G4int GetNumberOfMeuons() {
        return muonData.size();
    }

    static void IncreasePhotonAtMuon(G4int index)
    {
       index = GetMaxMuons() - index;

     muonData[index].first++;

       // G4cout<<"The index "<<index << " Has increased to: "<<muonData[index].first<<G4endl;

     G4int currentCOunt = muonData[index].first;

     if (currentCOunt > muonWithMaxPhotons.first)
     {
         muonWithMaxPhotons = muonData[index];
     }
    }

    static G4int GetMaxPhotonForMuon()
    {
        return muonWithMaxPhotons.first;
    }

    static G4ThreeVector GetGreediestMeuonPosition()
    {
        return muonWithMaxPhotons.second;
    }



    void AddHit() {
        counter++;
    }

    void AddEnergy(G4double energy1)
    {
        energy += energy1;
    }

    static G4double GetEnergy() {
        return energy;
    }


    static G4int GetCounter()
    {
        return counter;
    }

    static void AddVector(G4ThreeVector v)
    {
        photonStartingPositions.push_back(v);
    }

    static int GetVectorLength()
    {
     return photonStartingPositions.size();
    }

    static G4ThreeVector GetVectorAt(int index)
    {
        return photonStartingPositions[index];
    }

    static std::vector<G4ThreeVector> GetPhotonStartingPositions()
    {
        return photonStartingPositions;
    }

    static void SetPhotonsStartingPositions(std::vector<G4ThreeVector> v)
    {
        photonStartingPositions = v;
    }

    static G4int GetTotalMeuons() {
        return muonDataPerEvent.size();
    }

    ///For these to work one must call them at every end of event!
    static G4int GetMaxPhotonCount()
    {
        if (counter > maxCounter)
        {
            maxCounter = counter;
            photonStartingPositionsMax = photonStartingPositions;
        }


       return maxCounter;
    }

    static G4double GetMaxEnergy()
    {
        maxEnergy = (energy > maxEnergy) ? energy : maxEnergy;

        return maxEnergy;
    }

    static void SetMaxMuons(G4int max) {
        maxMuons = max;
    }

    static G4int GetMaxMuons()
    {
        return maxMuons;
    }

    static std::vector<G4ThreeVector> GetPhotonStartingPositionsMax()
    {
        return photonStartingPositionsMax;
    }


    static void EndEvent() {
        std::cout << "Event counter = " << counter << std::endl;
    }

};


#endif
