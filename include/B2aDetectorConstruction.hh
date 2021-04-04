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
/// \file B2aDetectorConstruction.hh
/// \brief Definition of the B2aDetectorConstruction class

#ifndef B2aDetectorConstruction_h
#define B2aDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class B2aDetectorMessenger;

class UKALMaterial; 
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"

/// Detector construction class to define materials, geometry
/// and global uniform magnetic field.

class B2aDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    B2aDetectorConstruction();
    virtual ~B2aDetectorConstruction();

public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // Set methods
    // void SetTargetMaterial (G4String );
    // void SetChamberMaterial(G4String );
    void SetMaxStep (G4double );
    void SetCheckOverlaps(G4bool );

private:     // by Yongchi - for UKAL
    G4bool fUseGasCell; 
    G4bool fUseUKALSample; 
    G4bool fUseUKALHPGe; 
    G4bool fUseUKALBGO; 
public:     // by Yongchi - for UKAL
    void SetUseGasCell(G4bool value) {fUseGasCell = value; }
    void SetUseUKALSample(G4bool value) {fUseUKALSample = value; }
    void SetUseUKALHPGe(G4bool value) {fUseUKALHPGe = value; }
    void SetDetectorPhi(G4double value) {hpgePhi = value; }
    void SetDetectorPosRadius(G4double value) {hpgePosRadius = value; }

private:
    // methods
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    G4int fNbOfChambers;
 
    G4LogicalVolume*   fLogicTarget;     // pointer to the logical Target
    G4LogicalVolume**  fLogicChamber;    // pointer to the logical Chamber

    G4Material*        fTargetMaterial;  // pointer to the target  material
    G4Material*        fChamberMaterial; // pointer to the chamber material

    //------------------------------------------------------------------------
    // by Yongchi 
    G4Material *gasCellMater; 
    G4Material *sampleMater; 
    G4Material *hpgeMater; 
    // by Yongchi - for UKAL
    UKALMaterial *managerUKALMaterial; 
    // gas cell
    G4Tubs *solidGasCell; 
    G4LogicalVolume *logicGasCell; 
    G4VPhysicalVolume *physiGasCell; 
    G4double fGasCell_zpos; 
    G4ThreeVector fGasCellPos; 
    // sample
    G4Tubs *solidUKALSample; 
    G4LogicalVolume *logicUKALSample; 
    G4VPhysicalVolume *physiUKALSample; 
    G4double fUKALSample_zpos; 
    G4ThreeVector fUKALSamplePos;
    // by Yongchi - add the hpge detector
    G4double hpgePhi; 
    G4double hpgePosRadius; 
    G4Tubs *solidUKALHPGe; 
    G4LogicalVolume *logicUKALHPGe; 
    G4VPhysicalVolume *physiUKALHPGe; 
    G4double fUKALHPGe_zpos; 
    G4ThreeVector fUKALHPGePos;    
    //------------------------------------------------------------------------
    


    G4UserLimits* fStepLimit;            // pointer to user step limits

    B2aDetectorMessenger*  fMessenger;   // messenger

    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
	// magnetic field messenger
    
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
