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
/// \file B2aDetectorMessenger.cc
/// \brief Implementation of the B2aDetectorMessenger class

#include "B2aDetectorMessenger.hh"
#include "B2aDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2aDetectorMessenger::B2aDetectorMessenger(B2aDetectorConstruction* Det)
	: G4UImessenger(),
	  fDetectorConstruction(Det)
{
	fB2Directory = new G4UIdirectory("/B2/");
	fB2Directory->SetGuidance("UI commands specific to this example.");

	fDetDirectory = new G4UIdirectory("/B2/det/");
	fDetDirectory->SetGuidance("Detector construction control");

	fTargMatCmd = new G4UIcmdWithAString("/B2/det/setTargetMaterial",this);
	fTargMatCmd->SetGuidance("Select Material of the Target.");
	fTargMatCmd->SetParameterName("choice",false);
	fTargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fChamMatCmd = new G4UIcmdWithAString("/B2/det/setChamberMaterial",this);
	fChamMatCmd->SetGuidance("Select Material of the Chamber.");
	fChamMatCmd->SetParameterName("choice",false);
	fChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/B2/det/stepMax",this);
	fStepMaxCmd->SetGuidance("Define a step max");
	fStepMaxCmd->SetParameterName("stepMax",false);
	fStepMaxCmd->SetUnitCategory("Length");
	fStepMaxCmd->AvailableForStates(G4State_Idle);

	// by Yongchi - for UKAL
	// add or remove detectors
	useGasCellCmd = new G4UIcmdWithABool("/UKAL_sim/det/UseGasCell", this); 
	useGasCellCmd->SetGuidance("place the gas cell"); 
	useGasCellCmd->SetParameterName("choice", false); 
	useGasCellCmd->AvailableForStates(G4State_PreInit); 
	// Scattering Sample
	useUKALSampleCmd = new G4UIcmdWithABool("/UKAL_sim/det/UseUKALSample", this); 
	useUKALSampleCmd->SetGuidance("activate UKAL Scattering Sample"); 
	useUKALSampleCmd->SetParameterName("choice", false); 
	useUKALSampleCmd->AvailableForStates(G4State_PreInit); 
	// HPGe
	useUKALHPGeCmd = new G4UIcmdWithABool("/UKAL_sim/det/UseUKALHPGe", this); 
	useUKALHPGeCmd->SetGuidance("activate HPGe"); 
	useUKALHPGeCmd->SetParameterName("choice", false); 
	useUKALHPGeCmd->AvailableForStates(G4State_PreInit); 
	//
	setUKALHPGeAngleCmd = new G4UIcmdWithADoubleAndUnit("/UKAL_sim/det/SetUKALHPGeAngle", this); 
	setUKALHPGeAngleCmd->SetGuidance("rotate the HPGe"); 
	setUKALHPGeAngleCmd->SetParameterName("angle", false); 
	// setUKALHPGeAngleCmd->SetUnitCategory("Length"); 
	setUKALHPGeAngleCmd->SetDefaultUnit("deg"); 
	setUKALHPGeAngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle); 
	// 
	setUKALHPGePosRadiusCmd = new G4UIcmdWithADoubleAndUnit("/UKAL_sim/det/SetUKALHPGePosRadius", this); 
	setUKALHPGePosRadiusCmd->SetGuidance("Move HPGe forward/backward"); 
	setUKALHPGePosRadiusCmd->SetParameterName("length", false); 
	// setUKALHPGePosRadiusCmd->SetUnitCategory("Length"); 
	setUKALHPGePosRadiusCmd->SetDefaultUnit("mm"); 
	setUKALHPGePosRadiusCmd->AvailableForStates(G4State_PreInit, G4State_Idle); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2aDetectorMessenger::~B2aDetectorMessenger()
{
	delete fTargMatCmd;
	delete fChamMatCmd;
	delete fStepMaxCmd;
	delete fB2Directory;
	delete fDetDirectory;

	delete useUKALSampleCmd; 
	delete useUKALHPGeCmd; 
	delete setUKALHPGePosRadiusCmd; 
	delete setUKALHPGeAngleCmd; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2aDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
	// if( command == fTargMatCmd )
	// 	{ fDetectorConstruction->SetTargetMaterial(newValue);}

	// if( command == fChamMatCmd )
	// 	{ fDetectorConstruction->SetChamberMaterial(newValue);}

	if( command == fStepMaxCmd ) {
		fDetectorConstruction
			->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
	}   

	// by Yongchi - for UKAL
	// add or remove detectors
	if(command == useGasCellCmd) {
		fDetectorConstruction->SetUseGasCell(useGasCellCmd->GetNewBoolValue(newValue)); 
	}
	if(command == useUKALSampleCmd) {
		fDetectorConstruction->SetUseUKALSample(useUKALSampleCmd->GetNewBoolValue(newValue)); 
	}
	if(command == useUKALHPGeCmd) {
		fDetectorConstruction->SetUseUKALHPGe(useUKALHPGeCmd->GetNewBoolValue(newValue)); 
	}

	// change detector positions
	if(command == setUKALHPGeAngleCmd) {
		fDetectorConstruction->SetDetectorPhi(360*degree - setUKALHPGeAngleCmd->GetNewDoubleValue(newValue)); 
	}
	if(command == setUKALHPGePosRadiusCmd) {
		fDetectorConstruction->SetDetectorPosRadius(setUKALHPGePosRadiusCmd->GetNewDoubleValue(newValue)); 
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
