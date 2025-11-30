//
// ************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ************************
//
//
/// \file B4/B4a/src/EventAction.cc
/// \brief Implementation of the B4a::EventAction class

#include "EventAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <iomanip>

#include "EventCounter.hh"
#include "PhotonMuonHelper.hh"
extern PhotonMuonHelper gPhotonMuonHelper;
namespace B4a
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void EventAction::BeginOfEventAction(const G4Event* event)
{
  // initialisation per event
  fEnergyAbs = 0.;
  fEnergyGap = 0.;
  fTrackLAbs = 0.;
  fTrackLGap = 0.;

  //Only needed in the event we should reset the variables after each event.
  EventCounter::BeginEvent();

  gPhotonMuonHelper.Clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  analysisManager->FillH1(0, fEnergyAbs);
  analysisManager->FillH1(1, fEnergyGap);
  analysisManager->FillH1(2, fTrackLAbs);
  analysisManager->FillH1(3, fTrackLGap);

  // fill ntuple
  analysisManager->FillNtupleDColumn(0,0, 500);
  analysisManager->FillNtupleDColumn(0,1, 800);
  analysisManager->FillNtupleDColumn(0,2, 500);
  analysisManager->FillNtupleDColumn(0,3, 500);


  // Salvezi datele (presupunând că ai creat coloanele 4 și 5 în RunAction)

  /*G4double photonCount = EventCounter::GetCounter();
  G4double energyCount = EventCounter::GetEnergy();
  std::vector<G4ThreeVector> photonStartingPositions = EventCounter::GetPhotonStartingPositions();*/

  G4double photonCount = EventCounter::GetMaxPhotonCount();
  G4double energyCount = EventCounter::GetMaxEnergy();
  std::vector<G4ThreeVector> photonStartingPositions = EventCounter::GetPhotonStartingPositionsMax();

  G4int maxPhotonsForMuon = EventCounter::GetMaxPhotonForMuon();
  G4ThreeVector maxMuonWithPhotonsPosition = EventCounter::GetGreediestMeuonPosition();

  G4cout<<"Here we have the maxPhotons for muon: " << maxPhotonsForMuon << " With his initial position: "<< maxMuonWithPhotonsPosition << G4endl;


  //G4cout<<"Photon count: "<<photonCount<<" have been detected "<< "with energy levels on: "<< energyCount<<G4endl;




  analysisManager->FillNtupleDColumn(0,4, photonCount);
  analysisManager->FillNtupleDColumn(0,5, energyCount);

  analysisManager->FillNtupleDColumn(0,6, maxPhotonsForMuon);
  analysisManager->FillNtupleDColumn(0,7, maxMuonWithPhotonsPosition.x());
  analysisManager->FillNtupleDColumn(0,8, maxMuonWithPhotonsPosition.y());
  analysisManager->FillNtupleDColumn(0,9, maxMuonWithPhotonsPosition.z());

  analysisManager->AddNtupleRow(0);
  AddVector(1, 2, 3, analysisManager, photonStartingPositions);



  // Print per event (modulo n)
  //
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ((printModulo > 0) && (eventID % printModulo == 0)) {
    G4cout << "   Absorber: total energy: " << std::setw(7) << G4BestUnit(fEnergyAbs, "Energy")
           << "       total track length: " << std::setw(7) << G4BestUnit(fTrackLAbs, "Length")
           << G4endl << "        Gap: total energy: " << std::setw(7)
           << G4BestUnit(fEnergyGap, "Energy") << "       total track length: " << std::setw(7)
           << G4BestUnit(fTrackLGap, "Length") << G4endl;

    G4cout << "--> End of event " << eventID << "\n" << G4endl;
  }
}

  void EventAction::AddVector(
    G4int col_px,
    G4int col_py,
    G4int col_pz,
    G4GenericAnalysisManager* analysisManager,
     std::vector<G4ThreeVector> vector)
{
  auto eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  for (int i = 0; i < vector.size(); i++)
  {
    analysisManager->FillNtupleIColumn(1, 0, eventID);     // event ID
    analysisManager->FillNtupleDColumn(1, col_px, vector[i].x());
    analysisManager->FillNtupleDColumn(1, col_py, vector[i].y());
    analysisManager->FillNtupleDColumn(1, col_pz, vector[i].z());

    analysisManager->AddNtupleRow(1);
  }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

}  // namespace B4a