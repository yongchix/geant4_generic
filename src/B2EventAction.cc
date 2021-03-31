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
/// \file B2EventAction.cc
/// \brief Implementation of the B2EventAction class

#include "B2EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include "B2TrackerHit.hh"

#include "TROOT.h"
#include "TApplication.h"
#include "TSystem.h"
#include "TH1.h"
#include "TH2.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TStopwatch.h"
#include "TTree.h"
#include "TRandom.h"

#include "UKALAnalysisManager.hh"

using namespace std; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::B2EventAction()
	: G4UserEventAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::~B2EventAction()
{
//	delete f1Res; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::EndOfEventAction(const G4Event* event)
{
	// get number of stored trajectories

	G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
	G4int n_trajectories = 0;
	if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

	// by Yongchi - for output 
	//G4double energySum = 0; 
	// G4int trackerID = G4SDManager::GetSDMpointer()->GetCollectionID("TrackerHitsCollection"); 
	// do the same thing for other detector (sensitive, of course) 
	// note that the name in the double quote above should match what is in DetectorConstruction


	// // periodic printing
	// G4int eventID = event->GetEventID();
	// if ( eventID < 100 || eventID % 100 == 0) {
	// 	// G4cout << ">>> Event: " << eventID  << G4endl;

	// 	// if ( trajectoryContainer ) {
	// 	//   G4cout << "    " << n_trajectories
	// 	//          << " trajectories stored in this event." << G4endl;
	// 	// }

	// 	// G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);

	// 	// if(hc->GetSize() > 0)
	// 	// 	G4cout << "    "  
	// 	// 		   << hc->GetSize() << " hits stored in this event" << G4endl;    
	// }


	G4int sampleID = G4SDManager::GetSDMpointer()->GetCollectionID("ukalSampleHitsCollection");  
	G4int hpgeID = G4SDManager::GetSDMpointer()->GetCollectionID("ukalHPGeHitsCollection"); 


	G4HCofThisEvent *HCE = event->GetHCofThisEvent(); 
	// B2TrackerHitsCollection *DHTracker = 0; 
	B2TrackerHitsCollection *DHCHPGe = 0; 
	B2TrackerHitsCollection *DHCSample = 0; 
	B2TrackerHitsCollection *DHCBGO = 0; 

	if(HCE) {
		// DHTracker = (B2TrackerHitsCollection*)HCE->GetHC(trackerID); 
		DHCSample = (B2TrackerHitsCollection*)HCE->GetHC(sampleID); 
		DHCHPGe = (B2TrackerHitsCollection*)HCE->GetHC(hpgeID); 
	}

	if(DHCSample) {
		int nHits = DHCSample->entries(); 
		G4double energyTotal = 0; 
		for(int i = 0; i < nHits; i++) {
			G4String particleName = (*DHCSample)[i]->GetParticlename(); 
			// cout << "Particle name = " << particleName << endl;
			G4double energy = (*DHCSample)[i]->GetEdep()/keV; 
			G4int stepNo = (*DHCSample)[i]->GetStepno(); 
			if(particleName == "e-") {
				energyTotal += energy; 
			}
		}
		//energyTotal = gRandom->Gaus(energyTotal, 0.01*energyTotal/2.35); 
		if(energyTotal > 0)
			energyTotal = gRandom->Gaus(energyTotal, energyTotal/100.0/2.35);
		UKALAnalysisManager *analysis = UKALAnalysisManager::GetInstance(); 
		if(energyTotal > 0) analysis->h1Sample->Fill(energyTotal); 
	}

	if(DHCHPGe) {
		int nHits = DHCHPGe->entries(); 
		G4double energyTotal = 0; 
		for(int i = 0; i < nHits; i++) {
			G4String particleName = (*DHCHPGe)[i]->GetParticlename(); 
			G4double energy = (*DHCHPGe)[i]->GetEdep()/keV; ///keV; 
			G4int stepNo = (*DHCHPGe)[i]->GetStepno(); 
			if(particleName == "e-" || particleName == "gamma") {
				energyTotal += energy; 
			}
			// energyTotal += energy; 
			// G4cout << "Particle type = " << particleName << G4endl; 
		}

		// add resolution to detectors
		if(energyTotal > 0) {
			UKALAnalysisManager *analysis = UKALAnalysisManager::GetInstance();
			if(energyTotal > 0) {
				// energyTotal = gRandom->Gaus(energyTotal, analysis->f1Res->Eval(energyTotal)); 
				energyTotal = gRandom->Gaus(energyTotal,
											analysis->f1Res->Eval(energyTotal));  
				analysis->h1HPGe->Fill(energyTotal); 
			}
		}
		

	}



	// if(DHTracker) {
	// 	int nHits = DHTracker->entries(); 
	// 	for(int i = 0; i < nHits; i++) {
	// 		G4String particleName = (*DHTracker)[i]->GetParticlename(); // check definition of hits
	// 		// G4cout << "Found a hit, name = " << particleName.c_str() << G4endl; 
	// 	}
	// }




}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
