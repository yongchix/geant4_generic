#ifndef UKAL_ANALYSIS_MANAGER_HH
#define UKAL_ANALYSIS_MANAGER_HH

#include "globals.hh"

#include "TFile.h"
#include "TROOT.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TF1.h"

class UKALAnalysisMessenger; 

class UKALAnalysisManager {
    private: // why private???
        UKALAnalysisManager(); 
        UKALAnalysisMessenger *messenger; 

    public: 
        ~UKALAnalysisManager(); 
        static UKALAnalysisManager* GetInstance(); 
        void book(); 

    // create the root files and histograms
    // void FillTH2D(G4double x, G4double y, G4double energy); 
    //void FillTH1D(TH1D *h1, G4double energy); 
    //TH1D* GetHistogram(TH1D* h1) {return h1; }
    // save the result at the end of each run to the ROOT file
    void Save(); 

    private: 
        static UKALAnalysisManager* instance; 
    public: 
        TFile *outroot; 
        TH1D *h1Test; 
        TH1D *h1HPGe; 
        TH1D *h1Sample; 
        // 3d histogram
        TH3D *h3GammaCollection; 

    public: 
        void SetFilename(G4String name); 
        void SetDirname(G4String name); 
    private: 
        G4String filename; 
        G4String dirname; 

    public: 
        TF1 *f1Res; 
}; 






#endif