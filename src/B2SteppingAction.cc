#include <iostream>

#include "B2SteppingAction.hh"
#include "G4SteppingManager.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"

#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"

B2SteppingAction::B2SteppingAction() : idOld(-1), idOut(-1) {;}
B2SteppingAction::~B2SteppingAction() {;}

void B2SteppingAction::UserSteppingAction(const G4Step* astep) {
    // get edep
    G4double Edep = astep->GetTotalEnergyDeposit(); 

    // get track
    G4Track *aTrack = astep->GetTrack(); 

    // get touchable history
    G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aTrack->GetTouchable()); 

    // get track properties
    G4int trackID = aTrack->GetTrackID(); 
    G4int parentID = aTrack->GetParentID(); 

    // get associated particle
    const G4DynamicParticle *aDynamicParticle = aTrack->GetDynamicParticle(); 
    G4ParticleDefinition *aParticle = aTrack->GetDefinition(); 
    G4String particleName = aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName(); 
    G4cout << "stepping action : particle: " << particleName << G4endl; 


    idNow = eventNo + 10000*trackID + 100000000*parentID; 

    if(idNow != idOld) {
        idOld = idNow; 

        // get the primary particle
        if(trackID == 1 && parentID == 0 && (aTrack->GetCurrentStepNumber() == 1)) {
            primaryVertex = aTrack->GetVertexPosition(); 
            primaryDirection = aTrack->GetVertexMomentumDirection(); 

            nSecondaries = 1; 
            secondaries[nSecondaries][1] = aParticle->GetPDGEncoding(); 
            secondaries[nSecondaries][2] = primaryVertex.x(); 
            secondaries[nSecondaries][3] = primaryVertex.y(); 
            secondaries[nSecondaries][4] = primaryVertex.z(); 
            secondaries[nSecondaries][5] = aDynamicParticle->GetMomentum().x(); 
            secondaries[nSecondaries][6] = aDynamicParticle->GetMomentum().y(); 
            secondaries[nSecondaries][7] = aDynamicParticle->GetMomentum().z(); 
            secondaries[nSecondaries][8] = aDynamicParticle->GetTotalMomentum(); 
            secondaries[nSecondaries][9] = aDynamicParticle->GetTotalEnergy(); 
            secondaries[nSecondaries][10] = aDynamicParticle->GetKineticEnergy(); 

            particleNames[nSecondaries] = particleName; 

            // make some verbose here
        }

        // get secondaries here (inside the scattering sample)
        G4double DCACut = 2.0*mm; // from the original code
        G4String materialName = aTrack->GetMaterial()->GetName(); 
        G4ThreeVector trackPos = aTrack->GetVertexPosition(); 
        if(trackID != 1 
           && parentID == 1 
           && strcmp(materialName, "XeF2") == 0) {
               secondaryVertex = aTrack->GetVertexPosition(); 
               secondaryDirection = aTrack->GetVertexPosition(); 

               nSecondaries++; 
               secondaries[0][0] = nSecondaries; 
               secondaries[nSecondaries][1] = aParticle->GetPDGEncoding(); 
               secondaries[nSecondaries][2] = aTrack->GetVertexPosition().x(); 
               secondaries[nSecondaries][3] = aTrack->GetVertexPosition().y(); 
               secondaries[nSecondaries][4] = aTrack->GetVertexPosition().z(); 
               secondaries[nSecondaries][5] = aDynamicParticle->GetMomentum().x(); 
               secondaries[nSecondaries][6] = aDynamicParticle->GetMomentum().y(); 
               secondaries[nSecondaries][7] = aDynamicParticle->GetMomentum().z(); 
               secondaries[nSecondaries][8] = aDynamicParticle->GetTotalMomentum(); 
               secondaries[nSecondaries][9] = aDynamicParticle->GetTotalEnergy(); 
               secondaries[nSecondaries][10] = aDynamicParticle->GetKineticEnergy(); 

               particleNames[nSecondaries] = particleName; 
            //    G4cout << "secondary particle: " << particleName << G4endl; 
           }    
    }
}

void B2SteppingAction::Initialize(G4int nev) {
    eventNo = nev; 
    nTracks = 0; 
    Edep = 0; 
    nSecondaries = 0; 

    for(G4int i = 0; i < 6000; i++) {
        particleNames[i] = ""; 
        for(G4int j = 0; j < 11; j++) {
            secondaries[i][j] = 0; 
        }
    }
}

G4double B2SteppingAction::GetSecondaries(G4int i, G4int j) {
    return secondaries[i][j]; 
}