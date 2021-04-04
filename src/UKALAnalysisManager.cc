#include "UKALAnalysisManager.hh"
#include "UKALAnalysisMessenger.hh"

UKALAnalysisManager* UKALAnalysisManager::instance = 0; 

// constructor
UKALAnalysisManager::UKALAnalysisManager() {
    messenger = new UKALAnalysisMessenger(this); 
    outroot = 0; 
    h1Test = 0; 
}

// desctructor
UKALAnalysisManager::~UKALAnalysisManager() {
    delete messenger; 
    delete outroot; outroot = 0; 
    delete h1Test; h1Test = 0; 
    delete f1Res; 
}

UKALAnalysisManager* UKALAnalysisManager::GetInstance() {
    if(instance == 0)
        instance = new UKALAnalysisManager(); 

    return instance; 
}

void UKALAnalysisManager::book() {
    delete outroot; 

    //G4cout << "\n\n\n\n\nfilename = " << filename.c_str() << "\n\n\n\n\n" << G4endl; 

    f1Res = new TF1("f1Res", "pol3", 0, 5000); 
   	// set the resolution curve: energy resolution vs. energy
	f1Res->SetParameter(0, 0.309014); 
	f1Res->SetParameter(1, 0.000358818); 
	f1Res->SetParameter(2, -2.39312e-08); 
	f1Res->SetParameter(3, -1.93058e-11); 
	// f1Res->SetParameter(4, 8.10315e-13);
	// f1Res->SetParameter(5, 6.46717e-16);
	// f1Res->SetParameter(6, -1.62965e-19);


    // define the ROOT file
    outroot = new TFile(Form("B2_%s.root", filename.c_str()), 
                        "RECREATE"); 
    
    // define histograms here
    h1Test = new TH1D("h1Test", "Test", 4096*4, 0, 4096); 
    h1Sample = new TH1D("h1Sample", "Energy Deposition in Sample, gated on e-; keV; Counts/0.25 keV", 
                        4096*4, 0, 4096); 
    h1HPGe = new TH1D("h1HPGe", "Energy Deposition in HPGe, gated on e-; keV; Counts/0.25 keV", 
                      4096*4, 0, 4096);           
    // for gamma rays         
    h3GammaCollection = new TH3D("h3GammaCollection", "Production of #gamma Rays;x [mm];y [mm];z [mm]", 
                                 40, -10, 10, 
                                 40, -10, 10, 
                                 40, -10, 10); 
    
}

// void UKALAnalysisManager::FillTH1D(TH1D *h1, G4double energy) {
//     h1->Fill(energy); 
// }

void UKALAnalysisManager::Save() {
    if(outroot) {
        outroot->Write(); 
        outroot->Close(); 
    }
}

void UKALAnalysisManager::SetFilename(G4String name) {
    filename = name; 
}

void UKALAnalysisManager::SetDirname(G4String name) {
    dirname = name; 
}
