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
/// \file B2TrackerHit.cc
/// \brief Implementation of the B2TrackerHit class

#include "B2TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<B2TrackerHit>* B2TrackerHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerHit::B2TrackerHit()
	: G4VHit(),
	  fTrackID(-1),
	  fChamberNb(-1),
	  fEdep(0.),
	  fPos(G4ThreeVector()), 
	  edep(0) // this is very important
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerHit::~B2TrackerHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerHit::B2TrackerHit(const B2TrackerHit& right)
	: G4VHit()
{
	fTrackID   = right.fTrackID;
	fChamberNb = right.fChamberNb;
	fEdep      = right.fEdep;
	fPos       = right.fPos;

	// by Yongchi - refer to e16032 simulation
	edep = right.edep;
	pos = right.pos;
	gtime = right.gtime;
	stepno = right.stepno;
	parentno = right.parentno;
	particletype = right.particletype;
	processname = right.processname;
	particlename = right.particlename;
	parentname = right.parentname;
	parentenergy = right.parentenergy;
	parentmodir = right.parentmodir;
	kineticenergy = right.kineticenergy;

	volname = right.volname;
	volcopyno = right.volcopyno;
	trackno = right.trackno;
	prepos = right.prepos;
	postpos = right.postpos;
	deltapos = right.deltapos;

	fulldis = right.fulldis;

	stepleng = right.stepleng;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const B2TrackerHit& B2TrackerHit::operator=(const B2TrackerHit& right)
{
	fTrackID   = right.fTrackID;
	fChamberNb = right.fChamberNb;
	fEdep      = right.fEdep;
	fPos       = right.fPos;

	// by Yongchi - refer to e16032 simulation
	edep = right.edep;
	pos = right.pos;
	gtime = right.gtime;
	stepno = right.stepno;
	parentno = right.parentno;
	particletype = right.particletype;
	processname = right.processname;
	particlename = right.particlename;
	parentname = right.parentname;
	parentenergy = right.parentenergy;
	parentmodir = right.parentmodir;
	kineticenergy = right.kineticenergy;

	volname = right.volname;
	volcopyno = right.volcopyno;
	trackno = right.trackno;
	prepos = right.prepos;
	postpos = right.postpos;
	deltapos = right.deltapos;

	fulldis = right.fulldis;
	stepleng = right.stepleng;

	return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool B2TrackerHit::operator==(const B2TrackerHit& right) const
{
	return ( this == &right ) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerHit::Draw()
{
	G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	if(pVVisManager)
		{
			G4Circle circle(fPos);
			circle.SetScreenSize(4.);
			circle.SetFillStyle(G4Circle::filled);
			G4Colour colour(1.,0.,0.);
			G4VisAttributes attribs(colour);
			circle.SetVisAttributes(attribs);
			pVVisManager->Draw(circle);
		}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerHit::Print()
{
	// G4cout
	// 	<< "  trackID: " << fTrackID << " chamberNb: " << fChamberNb
	// 	<< "Edep: "
	// 	<< std::setw(7) << G4BestUnit(fEdep,"Energy")
	// 	<< " Position: "
	// 	<< std::setw(7) << G4BestUnit( fPos,"Length")
	// 	<< G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
