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
/// \file medical/electronScattering2/src/PhysicsList.cc
/// \brief Implementation of the PhysicsList class

#include "UKALPhysicsList.hh"
#include "UKALPhysicsListMessenger.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"

#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

// Hadrons
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4GenericIon.hh"

#include "G4SystemOfUnits.hh"

// Migrated from e16032 simulation framework
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
//
#include "G4RadioactiveDecay.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4DecayPhysics.hh"
//
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
//
// Useful for neutron scattering physics
#include "QGSP_BERT.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_FTFP_BERT.hh"
//
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsShieldingLEND.hh"
#include "G4LENDInelastic.hh"

// From example B03
#include "G4NeutronInelasticProcess.hh"
#include "G4CrossSectionInelastic.hh"
#include "G4NeutronInelasticXS.hh"

// 03/03/2021, by Yongchi
// refer to advanced/underground_physics/src/DMXPhysicsList.cc
#include "G4NuclearLevelData.hh"
#include "G4NuclideTable.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

UKALPhysicsList::UKALPhysicsList() 
: G4VModularPhysicsList(), fMessenger(0), fEmPhysicsList(0)
{
    fMessenger = new UKALPhysicsListMessenger(this);
    
    // // EM physics
    // fEmName = G4String("emstandard_opt4");
    // fEmPhysicsList = new G4EmStandardPhysics_option4(1);
    // if (verboseLevel>-1) {
    //     G4cout << "PhysicsList::Constructor with default list: <" 
    //            << fEmName << ">" << G4endl;
    // }

    // by Yongchi - for UKAL 
    // below are assumed as the default physics
    particleList = new G4DecayPhysics(); 
    raddecayList = new G4RadioactiveDecayPhysics(); 
    fEmPhysicsList = new G4EmLivermorePhysics(); 
    // hadPhysicsList = new G4HadronPhysicsShieldingLEND(); // LEND
    hadPhysicsList = 0; 


    G4LossTableManager::Instance();

    // 03/03/2020, by Yongchi
    // refer to advanced/underground_physics/src/DMXPhysicsList.cc
    G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
    deex->SetStoreICLevelData(true);
    // deex->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife()
    //                    /std::log(2.));
    deex->SetMaxLifeTime(1000*ms); 



    SetVerboseLevel(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

UKALPhysicsList::~UKALPhysicsList()
{
    delete fEmPhysicsList;
    // by Yongchi - for UKAL
    delete particleList; 
    delete raddecayList; 
    if(hadPhysicsList) delete hadPhysicsList; 

    if (nhadcomp > 0) {
    for(G4int i=0; i<nhadcomp; i++) {
      delete hadronPhys[i];
    }
  }

    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UKALPhysicsList::ConstructParticle()
{
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();
    
    // gamma
    G4Gamma::GammaDefinition();
    
    // optical photon
    G4OpticalPhoton::OpticalPhotonDefinition();
    
    // leptons
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();
    
    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
    
    // mesons
    G4MesonConstructor mConstructor;
    mConstructor.ConstructParticle();
    
    // barions
    G4BaryonConstructor bConstructor;
    bConstructor.ConstructParticle();
    
    // ions
    G4IonConstructor iConstructor;
    iConstructor.ConstructParticle();
    
    // Required by MT even if ion physics not used
    G4GenericIon::GenericIonDefinition();

    // migrated from e16032 simulation
    particleList->ConstructParticle(); 
    raddecayList->ConstructParticle(); 
    fEmPhysicsList->ConstructParticle(); 
    if(hadPhysicsList) hadPhysicsList->ConstructParticle(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UKALPhysicsList::ConstructProcess()
{
    AddTransportation();
    // EM
    fEmPhysicsList->ConstructProcess();
    // decays
    particleList->ConstructProcess(); 
    // raddecayList->ConstructProcess(); 
    // // hadroms
	// hadPhysicsList->ConstructProcess(); 

    // migrated from e16032 simulation
    G4RadioactiveDecay *radioactiveDecay = new G4RadioactiveDecay(); 
    radioactiveDecay->SetICM(true); 
    radioactiveDecay->SetARM(true); 
    G4PhysicsListHelper *ph = G4PhysicsListHelper::GetPhysicsListHelper(); 
    ph->RegisterProcess(radioactiveDecay, //G4GenericIon::GenericIon); 
                        //G4ParticleDefinition::IsGeneralIon()); 
                        G4GenericIon::GenericIon()); 
    //
    // deexcitation in case of atomic rearrangement
    G4UAtomicDeexcitation* de = new G4UAtomicDeexcitation();
    de->SetFluo(true);
    de->SetAuger(true);
    de->SetPIXE(false);
    G4LossTableManager::Instance()->SetAtomDeexcitation(de);    
    //
    
    // had
    if(nhadcomp > 0) {
        for(G4int i = 0; i < nhadcomp; i++) {
            hadronPhys[i]->ConstructProcess();
        }
    }
    if(hadPhysicsList) hadPhysicsList->ConstructProcess(); 
    G4cout << "Construction of Physics List Done! " << G4endl; 

    // AddDecay(); // see below
    // AddStepMax(); // see below
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// #include "G4Decay.hh"

// void UKALPhysicsList::AddDecay()
// {
//     // Add Decay Process
    
//     G4Decay* fDecayProcess = new G4Decay();
    
//     auto particleIterator=GetParticleIterator();
//     particleIterator->reset();
//     while( (*particleIterator)() ){
//         G4ParticleDefinition* particle = particleIterator->value();
//         G4ProcessManager* pmanager = particle->GetProcessManager();
        
//         if (fDecayProcess->IsApplicable(*particle) && 
//               !particle->IsShortLived()) {
            
//             pmanager ->AddProcess(fDecayProcess);
            
//             // set ordering for PostStepDoIt and AtRestDoIt
//             pmanager ->SetProcessOrdering(fDecayProcess, idxPostStep);
//             pmanager ->SetProcessOrdering(fDecayProcess, idxAtRest);
            
//         }
//     }
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// #include "StepMax.hh"

// void PhysicsList::AddStepMax()
// {
//     // Step limitation seen as a process
//     StepMax* stepMaxProcess = new StepMax();
    
//     auto particleIterator=GetParticleIterator();
//     particleIterator->reset();
//     while ((*particleIterator)()){
//         G4ParticleDefinition* particle = particleIterator->value();
//         G4ProcessManager* pmanager = particle->GetProcessManager();
        
//         if (stepMaxProcess->IsApplicable(*particle))
//         {
//             pmanager ->AddDiscreteProcess(stepMaxProcess);
//         }
//     }
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UKALPhysicsList::AddPhysicsList(const G4String& name)
{
    // if (verboseLevel>-1) {
    //     G4cout << "UKALPhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
    // }
    G4cout << "UKALPhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
    
    // if (name == fEmName) return;
    
    // if (name == "emstandard_opt0") {
        
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysics(1);
        
    // } else if (name == "emstandard_opt1") {
        
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysics_option1(1);
        
    // } else if (name == "emstandard_opt2") {
        
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysics_option2(1);
        
    // } else if (name == "emstandard_opt3") {
        
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysics_option3(1);

    // } else if (name == "emstandard_opt4") {
        
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysics_option4(1);

    // } else if (name == "emlowenergy") {
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmLowEPPhysics(1);

    // } else if (name == "emstandardSS") {
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysicsSS(1);

    // } else if (name == "emstandardWVI") {
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysicsWVI(1);

    // } else if (name == "emstandardGS") {
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmStandardPhysicsGS(1);

    // } else if (name == "emlivermore") {
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmLivermorePhysics(1);

    // } else if (name == "empenelope") {
    //     fEmName = name;
    //     delete fEmPhysicsList;
    //     fEmPhysicsList = new G4EmPenelopePhysics(1);

    // } 
    // below migrated from void UKAL_simPhysicsList::SelectPhysicsList(const G4String& name)
    //else 
    if(name == "Hadron" && !hadPhysicsList) {
        ; // do nothing as it was
    } else if(name == "QGSP_BERT_HP"  && !hadPhysicsList) {
        AddExtraBuilders(true);
        hadPhysicsList = new G4HadronPhysicsQGSP_BERT_HP(verboseLevel);
    } else if(name == "QGSP_BIC_HP"  && !hadPhysicsList) {
        AddExtraBuilders(true);
        hadPhysicsList = new G4HadronPhysicsQGSP_BIC_HP(verboseLevel);
    } else if(name == "LEND" && !hadPhysicsList) { // by Yongchi
        AddExtraBuilders(true); 
        hadPhysicsList = new G4HadronPhysicsShieldingLEND(verboseLevel);
    }
    // } else if(name == "LEND_Inelastic" && !hadPhysicsList) { // by Yongchi
    //     AddExtraBuilders(true); 
    //     hadPhysicsList = new G4LENDInelastic()
    // }

	else if(name == "LowEnergy_EM_Livermore") {
        delete fEmPhysicsList; 
        fEmPhysicsList = new G4EmLivermorePhysics();
    } else if(name == "Standard_EM") {
        delete fEmPhysicsList;
        fEmPhysicsList = new G4EmStandardPhysics();
    } else if(name == "Standard_EM2") {
        delete fEmPhysicsList; 
        fEmPhysicsList = new G4EmStandardPhysics_option2();
    }
    else if(name == "LowEnergy_EM_Penelope") {
        delete fEmPhysicsList;
        fEmPhysicsList = new G4EmPenelopePhysics();
    }
    //    
    else {
    
        G4ExceptionDescription description;
        description
          << "      "
          << "PhysicsList::AddPhysicsList: <" << name << "> is not defined";
        G4Exception("PhysicsList::AddPhysicsList",
                "electronScattering2_F001", FatalException, description);
    }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::AddExtraBuilders(G4bool flagHP) {
    nhadcomp = 5; // used to be 5
    hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
    // hadronPhys.push_back( new G4HadronElasticPhysics("elastic",verboseLevel,
    //						   flagHP));
    hadronPhys.push_back( new G4HadronElasticPhysics(verboseLevel));
    hadronPhys.push_back( new G4StoppingPhysics("stopping",verboseLevel));
    hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));
    hadronPhys.push_back( new G4NeutronTrackingCut("Neutron tracking cut"));
    // by Yongchi - ??? hadron inelastic physics???
    // hadronPhys.push_back( new 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::SetCuts() {
    SetCutValue(cutForGamma, "gamma"); 
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");
    G4cout << "world cuts are set" << G4endl;

    // G4Region* region = G4RegionStore::GetInstance()->GetRegion("UKALHPGe"); 
    // if( !DetectorCuts ) SetDetectorCut(cutForElectron);
    // region->SetProductionCuts(DetectorCuts);
    // G4cout << "Detector cuts are set" << G4endl;

    if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::SetCutForGamma(G4double cut) {
    cutForGamma = cut;
    SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::SetCutForElectron(G4double cut) {
    cutForElectron = cut;
    SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::SetCutForPositron(G4double cut) {
    cutForPositron = cut;
    SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::SetTargetCut(G4double cut) {
    if( !TargetCuts ) TargetCuts = new G4ProductionCuts();

    TargetCuts->SetProductionCut(cut, idxG4GammaCut);
    TargetCuts->SetProductionCut(cut, idxG4ElectronCut);
    TargetCuts->SetProductionCut(cut, idxG4PositronCut);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void UKALPhysicsList::SetDetectorCut(G4double cut) {
    if( !DetectorCuts ) DetectorCuts = new G4ProductionCuts();

    DetectorCuts->SetProductionCut(cut, idxG4GammaCut);
    DetectorCuts->SetProductionCut(cut, idxG4ElectronCut);
    DetectorCuts->SetProductionCut(cut, idxG4PositronCut);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
