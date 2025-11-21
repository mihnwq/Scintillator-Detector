/// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The Geant4 software is copyright of the Copyright Holders of    *
// * the Geant4 Collaboration. It is provided under the terms and    *
// * conditions of the Geant4 Software License, included in the file *
// * LICENSE and available at http://cern.ch/geant4/license.          *
// *                                                                  *
// * Neither the authors of this software system, nor their employing*
// * institutes, nor the agencies providing financial support for    *
// * this work make any representation or warranty, express or       *
// * implied, regarding this software system or assume any liability *
// * for its use. Please see the license in the file LICENSE and URL *
// * above for the full disclaimer and limitation of liability.      *
// *                                                                  *
// * This code implementation is the result of the scientific and    *
// * technical work of the GEANT4 collaboration.                     *
// * By using, copying, modifying or distributing the software (or   *
// * any work based on the software) you agree to acknowledge its     *
// * use in resulting scientific publications and indicate your       *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file B4/B4a/include/DetectorConstruction.hh
/// \brief Definition of the B4::DetectorConstruction class

#ifndef B4DetectorConstruction_h
#define B4DetectorConstruction_h 

#include <G4Ellipsoid.hh>
#include <G4Polycone.hh>

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Threading.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

namespace B4
{

/// \class DetectorConstruction
/// \brief Defines materials and geometry of the calorimeter
///
/// The calorimeter is built as a box with a configurable number of layers.
/// Each layer consists of an absorber plate and a detection gap, replicated
/// along the calorimeter depth. Four main parameters define the calorimeter:
/// - absorber thickness
/// - gap thickness
/// - number of layers
/// - transverse size (square face)
///
/// A uniform transverse magnetic field can also be defined via
/// G4GlobalMagFieldMessenger.

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    // Get the scoring volume
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    // Construct the geometry
    G4VPhysicalVolume* Construct() override;

    // Optional specialized constructions
    void ConstructCherenkov();
    void ConstructScintillator();
    void ConstructTOF();
    void ConstructAtmosphere();
    void ConstructCell();


private:
    // Materials
    G4Material *SiO2, *H2O, *Aerogel, *worldMat, *NaI, *polystyrene, *PMMA, *TiO2;
    G4Material *WLS_Core;
    G4Element  *C, *Na, *I;

    // Solids
    G4SubtractionSolid *Scin_Box, *TiO2Box_with_groove, *TiO2cover;

    G4Tubs *solidCore, *solidCladding;

    //G4Ellipsoid* solidCore, *solidCladding;

    G4Box  *solidWorld, *solidRadiator, *solidDetector, *solidScintillator, *solidCapDet;
    G4Box  *Scin_FullBox, *scintilator_groove_box, *TiO2Box, *TiO2_groove;

    // Logical volumes
    G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector, *logicScintillator, *logicCapDet;
    G4LogicalVolume *logicScin, *logicCore, *logicCladding, *TiO2_logic;

    // Physical volumes
    G4VPhysicalVolume *physWorld, *physDetector, *physRadiator, *physScintillator, *physCapDet1, *physCapDet2;
    G4VPhysicalVolume *physScin, *physCore, *physCladding, *TiO2_phys;

    // Optical surfaces
    G4LogicalSkinSurface   *Core_Surface, *Cladding_Surface, *Scin_Surface, *DET_Surface, *TiO2_Surface;
    G4LogicalBorderSurface *TiO2_Scin, *Core_Cladding, *Cladding_Core, *Scin_TiO2, *Core_DET1, *Core_DET2;
    G4LogicalBorderSurface *Clad_World, *World_Clad, *Core_World, *World_Core, *Scin_World, *World_Scin;

    G4OpticalSurface *OpticalSurfaceScin;
    G4OpticalSurface *OpticalSurfaceCore;
    G4OpticalSurface *OpticalSurfaceTiO2;

    // Helper functions
    void DefineMaterials();

    // Messenger for UI commands
    G4GenericMessenger *fMessenger;

    // Scoring volume
    G4LogicalVolume *fScoringVolume;

    // Layout parameters
    G4int nRows, nCols;
    G4double xWorld, yWorld, zWorld;

    // Flags
    G4bool isCherenkov;
    G4bool isScintillator;
    G4bool isCell;
};

}  // namespace B4

#endif // B4DetectorConstruction_h

