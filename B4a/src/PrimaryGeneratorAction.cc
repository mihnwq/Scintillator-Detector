//
// ********************************************************************
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
// ********************************************************************
//
//
/// \file B4/B4a/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the B4::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "G4AnalysisManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4OpticalPhoton.hh"
#include "G4Proton.hh"
#include <cmath>
#include<cstring>
#include<numbers>
namespace B4
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4long seed = time(0);
  CLHEP::HepRandom::setTheSeed(seed * G4UniformRand());

  G4int n_particle = 10;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  
  G4String particleName;
  
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName = "mu-");
  
  /*fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(6. * MeV);
  */
  fParticleGun->SetParticleDefinition(particle);
  
  fParticleGun->SetParticleEnergy(1. * GeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

///G4ThreeVector offset = G4ThreeVector(0.01, 0.09, 0.01);

void ParticleSourcePrinicpal(G4ParticleGun* fParticleGun)
{
    G4double PI = acos(-1);
   
    G4double x, y, z, x1, y1, z1;
    
    G4double phi, theta;


    x1 = (G4UniformRand() - 0.5) * 2.5 * cm;
    y1 = 0.5 * cm;
    z1 = (G4UniformRand() - 0.5) * 100. *cm ; 

    phi = G4UniformRand() * PI * 2;
    
    theta = G4UniformRand() * PI / 2;

    x= x1 + 10 * cm * sin(theta) * cos(phi);
    y= y1 + 10 * cm * cos(theta);
    z= z1 + 10 * cm * sin(phi) * sin(theta);

    G4double energy;

    energy = 3.0;

    fParticleGun->SetParticleEnergy(energy * GeV);

    G4ThreeVector mom(x1-x,y1-y,z1-z); //checked

    G4ThreeVector pos(x, y, z);
    G4long seed = time(0);
    CLHEP::HepRandom::setTheSeed(seed * G4UniformRand());
    fParticleGun->SetParticlePosition(pos);

    fParticleGun->SetParticleMomentumDirection(mom);

    G4AnalysisManager *man =  G4AnalysisManager::Instance();


    man->FillNtupleDColumn(0,8, phi);
    man->FillNtupleDColumn(0,9, theta);
    man->FillNtupleDColumn(0,5, x);
    man->FillNtupleDColumn(0,6, y);
    man->FillNtupleDColumn(0,7, z);
    man->FillNtupleDColumn(0,1, x1);
    man->FillNtupleDColumn(0,2, y1);
    man->FillNtupleDColumn(0,3, z1);

}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  // this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.


   G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
   
   ParticleSourcePrinicpal(fParticleGun);

   if(particle == G4OpticalPhoton::OpticalPhotonDefinition()) 
{ 
    G4double angle = G4UniformRand() * 360.0 * deg;

    G4ThreeVector normal(1., 0., 0.);

    G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
    G4ThreeVector product = normal.cross(kphoton);
    G4double modul2       = product * product;

    G4ThreeVector e_perpend(0., 0., 1.);
  
    if(modul2 > 0.)
      e_perpend = (1. / sqrt(modul2)) * product;

    G4ThreeVector e_paralle = e_perpend.cross(kphoton);

    G4ThreeVector polar = cos(angle) * e_paralle + sin(angle) * e_perpend;
    fParticleGun->SetParticlePolarization(polar);


}

    fParticleGun->GeneratePrimaryVertex(event);
  
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace B4
