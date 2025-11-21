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
/// \file B4/B4a/src/SteppingAction.cc
/// \brief Implementation of the B4a::SteppingAction class

#include "SteppingAction.hh"

#include <G4OpticalPhoton.hh>

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "globals.hh"


using namespace B4;

namespace B4a
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(const DetectorConstruction* detConstruction,
                               EventAction* eventAction)
  : fDetConstruction(detConstruction), fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  /*
  // Collect energy and track length step by step

  // get volume of the current step
    if (!fScoringVolume) {
        const auto detConstruction = static_cast<const DetectorConstruction*>(
          G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detConstruction->GetScoringVolume();
    }

    // get volume of the current step
    G4LogicalVolume* volume =
      step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // check if we are in scoring volume
    if (volume != fScoringVolume) return;

    // collect energy deposited in this step
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);

  // 1. Obținem volumul în care se află particula
  auto vol= step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // Verificăm dacă volumul există (pentru siguranță)
  if (!vol) return;

  // 2. Verificăm dacă particula este în detectorul tău ("physCapDet1" sau "physCapDet2")
  // Folosim un check parțial pe nume ca să le prindem pe ambele
  G4String volName = vol->GetName();

  if (volName.contains("physCapDet") )
  {
    // 3. Verificăm dacă particula este un Foton Optic
    if (step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
    {
      // 4. Verificăm dacă fotonul ABIA A INTRAT în volum (Boundary)
      // Asta previne numărarea de mai multe ori a aceluiași foton
      // dacă face mai mulți pași în interiorul detectorului.
      if (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary)
      {
        // Luăm energia fotonului
        G4double energy = step->GetTrack()->GetKineticEnergy();

        // Trimitem datele către EventAction
        fEventAction->AddPhotonData(energy);

        // OPȚIONAL: Oprim fotonul aici (simulăm absorbția totală)
        // Dacă nu faci asta, fotonul ar putea ieși și intra iar.
        step->GetTrack()->SetTrackStatus(fStopAndKill);
      }
    }
  }*/

  auto vol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // Verificăm dacă volumul există (pentru siguranță)
  //if (!vol) return;

  G4String volName = vol->GetName();
  //G4cout << volName;
  // ====================================================================
  // LOGICA PENTRU FOTONI OPTICI (DEBUG + SALVARE)
  // ====================================================================

  // Verificăm dacă particula este un Foton Optic
  if (step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  {
    // --- SECVENȚA DE DEBUG SOLICITATĂ ---
    // Printează o singură dată ca să știm că există măcar UN foton în toată simularea
    static bool mesajAfisat = false;
    if (!mesajAfisat) {
      G4cout << "!!! EVRIKA: Am detectat un foton optic în simulare! !!!" << G4endl;
      mesajAfisat = true;
    }

    // --- VERIFICARE DETECTOR ---
    // Verificăm dacă suntem în detectorii tăi ("physCapDet1" sau "physCapDet2")
   // G4cout << volName << std::endl;
    if (volName.find("physCapDet") != std::string::npos)
    {
      // Print de debug pentru fiecare lovitură
      G4cout << "--> Foton lovit in detector: " << volName << G4endl;

      // --- LOGICA DE SALVARE A DATELOR ---
      // Verificăm dacă fotonul ABIA A INTRAT în volum (Boundary)
      // Ca să nu îl numărăm de două ori dacă face pași mici în interior
      if (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) {
        // Luăm energia fotonului
        G4double energy = step->GetTrack()->GetKineticEnergy();

        G4int count = 0;
        if (energy>0)
          count++;
        // Trimitem datele către EventAction
        // (Asigură-te că ai metoda AddPhotonData în EventAction.hh)
        fEventAction->AddPhotonData(energy);
       // fEventAction->AddPhotonData(count);
        // Oprim fotonul aici (simulăm absorbția totală de către SiPM)
        step->GetTrack()->SetTrackStatus(fStopAndKill);
      }
    }
  }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B4a