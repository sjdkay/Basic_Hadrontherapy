#ifndef HadrontherapyExternalDetectorSD_h
#define HadrontherapyExternalDetectorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "HadrontherapyExternalDetectorHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class HadrontherapyExternalDetectorSD : public G4VSensitiveDetector
{
public:
    HadrontherapyExternalDetectorSD(G4String name);
    ~HadrontherapyExternalDetectorSD();

    std::ofstream ofs;
    void Initialize(G4HCofThisEvent*);

    G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);

    void EndOfEvent(G4HCofThisEvent*);

private:
    G4int HCID;
    HadrontherapyExternalDetectorHitsCollection *EDHitsCollection;
    G4String sensitiveDetectorName;
};
#endif


