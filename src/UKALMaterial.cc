#include "UKALMaterial.hh"

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include <vector>
#include <iomanip>
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"  

using namespace std; 

UKALMaterial::UKALMaterial() {
    G4NistManager* man = G4NistManager::Instance();

    Ge = new G4Material("Ge", 32., 72.61*g/mole, 5.325*g/cm3);

	isotopeT = new G4Isotope("isotopeT", 1, 3); 
	elementT = new G4Element("Tritium", "T", 1); 
	elementT->AddIsotope(isotopeT, 100*perCent); 

    isotopeXe136 = new G4Isotope("isotopeXe136", 54, 136); 
	elementXe136 = new G4Element("Xenon136", "Xe136", 1); 
	elementXe136->AddIsotope(isotopeXe136, 100*perCent); 

	isotopeF19   = new G4Isotope("isotopeF19", 9, 19); 
	elementF19   = new G4Element("Fluorine19", "F19", 1); //9, 18.998*g/mole); 
	elementF19->AddIsotope(isotopeF19, 100*perCent); 

    // Yongchi - Scattering Sample Material at UKAL
	XeF2  = new G4Material("XeF2", 4.448*g/cm3, 2); 
	XeF2->AddElement(elementXe136, 1); 
	XeF2->AddElement(elementF19, 2); 
	// tritium gas
	T2 = new G4Material("T2", 0.00026929013*g/cm3, 1, kStateGas);
	T2->AddElement(elementT, 1); 
}

UKALMaterial::~UKALMaterial() {
    ; 
}