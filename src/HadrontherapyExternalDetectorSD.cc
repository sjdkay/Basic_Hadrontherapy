
#include "HadrontherapyExternalDetectorSD.hh"
#include "HadrontherapyDetectorHit.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4Track.hh"
#include "HadrontherapyAnalysisManager.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////////////////////////////
HadrontherapyExternalDetectorSD::HadrontherapyExternalDetectorSD(G4String name):
    G4VSensitiveDetector(name)
{
    G4String HCname;
    collectionName.insert(HCname="HadrontherapyExternalDetectorHitsCollection");
    EDHitsCollection = NULL;
    sensitiveDetectorName = name;
}

/////////////////////////////////////////////////////////////////////////////
HadrontherapyExternalDetectorSD::~HadrontherapyDetectorSD()
{
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyExternalDetectorSD::Initialize(G4HCofThisEvent*)
{
//    EDHitsCollection = new HadrontherapyExternalDetectorHitsCollection(sensitiveDetectorName,
//	    collectionName[0]);
}

/////////////////////////////////////////////////////////////////////////////
G4bool HadrontherapyExternalDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    return true;
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyExternalDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    static G4int HCID = -1;
    if(HCID < 0)
    {
	HCID = GetCollectionID(0);
    }

    HCE -> AddHitsCollection(HCID,HitsCollection);
}

