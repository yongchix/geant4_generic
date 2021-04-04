// Created by Yongchi Xiao
// Initialized: 03/31/2021
// Based on Geant4 built-in example: FCALSteppingAction.hh/cc

#ifndef B2_STEPPING_ACTION
#define B2_STEPPING_ACTION

#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

using namespace std; 

class B2SteppingAction : public G4UserSteppingAction {
    public: 
        B2SteppingAction(); 
        virtual ~B2SteppingAction(); 
        virtual void UserSteppingAction(const G4Step*); 
    
    private: 
        G4int eventNo; 
        G4int idNow, idOld, idOut; 
        G4int nTracks, nSecondaries; 
        G4double secondaries[6000][12]; 
        G4double Edep; 

        G4ThreeVector primaryVertex, primaryDirection; 
        G4ThreeVector secondaryVertex, secondaryDirection; 
        G4ThreeVector distance; 

    public: 
        // added by Yongchi
        G4String particleNames[6000]; 


    public: 
        void Initialize(G4int); 
        G4double GetSecondaries(G4int, G4int); 
        G4double GetEdep(G4String); 
}; 





#endif