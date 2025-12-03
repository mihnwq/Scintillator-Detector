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
#include <unordered_set>

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "EventCounter.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "globals.hh"

#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "PhotonMuonHelper.hh"


using namespace B4;
extern PhotonMuonHelper gPhotonMuonHelper;
namespace B4a {
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



  SteppingAction::SteppingAction(const DetectorConstruction* detConstruction,
                                 EventAction* eventAction)
    :fDetConstruction(detConstruction), fEventAction(eventAction)
  {}

  EventCounter photonCpunter;



  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void SteppingAction::UserSteppingAction(const G4Step* step)
  {

    auto vol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();


    //if (!vol) return;

    G4String volName = vol->GetName();

    //G4cout<<"Volume "<<volName<<"\n";




    if ((step->GetTrack()->GetDefinition() == G4MuonPlus::MuonPlusDefinition() ||
        step->GetTrack()->GetDefinition() == G4MuonMinus::MuonMinusDefinition())
        && volName.find("physWorld") == std::string::npos ///Might need to change to postStep
        && step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary )
    {

      G4int trackID = step->GetTrack()->GetTrackID();
      if (gPhotonMuonHelper.muonsAlreadyHit.find(trackID) == gPhotonMuonHelper.muonsAlreadyHit.end())
      {
        gPhotonMuonHelper.muonsAlreadyHit.insert(trackID);
        G4ThreeVector pos = step->GetPreStepPoint()->GetPosition(); ///This too
        photonCpunter.AddMuon(pos);
        G4cout << "Muon first hit a volume at: " << pos << " TrackID: " << trackID << G4endl;
      }


      // EventCounter::AddMuonHit(muonHitPos);

    }else if (step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
    {
      // G4StepPoint* pre  = step->GetPreStepPoint();
      ///Needed to change to post volume, cause it determines the current volume you are touching,
      ///preVolume determines the last one
      G4StepPoint* post = step->GetPostStepPoint();

      //  G4VPhysicalVolume* prePV  = pre->GetPhysicalVolume();
      G4VPhysicalVolume* postPV = post->GetPhysicalVolume();

      if (post->GetStepStatus() == fGeomBoundary)
      {
        G4String volume = postPV->GetName();
        if (volume == "physCapDet1" || volName == "physCapDet2")
        {
          G4double energy = step->GetTrack()->GetKineticEnergy();
          G4ThreeVector startingPosition = step->GetTrack()->GetVertexPosition();

          const G4Track* photon = step->GetTrack();
          G4int parentID = photon->GetParentID();

          bool foundMuon = false;

        /*  while(parentID != 0)
          {

            if(gPhotonMuonHelper.isMuonFamily[parentID])
            {
              auto it = gPhotonMuonHelper.muonStartMap.find(parentID);
              if(it != gPhotonMuonHelper.muonStartMap.end())
              {
                foundMuon = true;
              }
              break;
            }

            auto itParent = gPhotonMuonHelper.parentMap.find(parentID);
            if(itParent == gPhotonMuonHelper.parentMap.end())
              break;

            parentID = itParent->second;

          }*/



          //G4cout<<"Was muon found? : "<<parentID<<G4endl;


        /*  if(foundMuon) {
            // G4cout<<"Found Muon for this photon!"<<G4endl;
            photonCpunter.IncreasePhotonAtMuon(parentID);
          }
*/
          G4int* muonFather = gPhotonMuonHelper.muonPtr[photon->GetTrackID()];

          if (muonFather != nullptr)
            G4cout<<"Found Muon for this photon! " <<*gPhotonMuonHelper.muonPtr[photon->GetTrackID()]<< G4endl;

          //

          photonCpunter.AddHit();

          // G4cout<<"Photon Hit the volume and escaped!"<<G4endl;

          photonCpunter.AddEnergy(energy);
          photonCpunter.AddVector(startingPosition);

          step->GetTrack()->SetTrackStatus(fStopAndKill);
        }

      }
    }


  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
}  // namespace B4a