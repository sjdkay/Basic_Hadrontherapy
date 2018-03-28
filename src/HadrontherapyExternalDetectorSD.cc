
#include "HadrontherapyExternalDetectorSD.hh"
#include "HadrontherapyExternalDetectorHit.hh"
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
    collectionName.insert(HCname="EDHitsCollection");
    EDHitsCollection = NULL;
    sensitiveDetectorName = name;

    HCID = -1;
}

/////////////////////////////////////////////////////////////////////////////
HadrontherapyExternalDetectorSD::~HadrontherapyExternalDetectorSD()
{
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyExternalDetectorSD::Initialize(G4HCofThisEvent* HCE2)
{
    EDHitsCollection = new HadrontherapyExternalDetectorHitsCollection(sensitiveDetectorName,
	    collectionName[0]);
    if(HCID < 0){
        HCID = GetCollectionID(0);
    }
    HCE2->AddHitsCollection(HCID, EDHitsCollection);
}

/////////////////////////////////////////////////////////////////////////////
G4bool HadrontherapyExternalDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    HadrontherapyAnalysisManager* analysis = HadrontherapyAnalysisManager::GetInstance();

    G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
    G4VPhysicalVolume* volume = theTouchable->GetVolume();

    G4Track* theTrack = aStep  ->  GetTrack();
    G4double edep = aStep->GetTotalEnergyDeposit();
    G4int StepNo = theTrack -> GetCurrentStepNumber();
    G4int TID = theTrack->GetTrackID();

    if (edep==0.) return false;

    G4ThreeVector Position = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector Momentum = aStep->GetPreStepPoint()->GetMomentum();
    G4ParticleDefinition *particleDef = theTrack -> GetDefinition();
    G4double EVert = theTrack -> GetVertexKineticEnergy();
    G4ThreeVector Vert = theTrack -> GetVertexPosition();
    G4ThreeVector VertMom = theTrack -> GetVertexMomentumDirection();

    HadrontherapyExternalDetectorHit* detectorHit = new HadrontherapyExternalDetectorHit();

    detectorHit->addEdep(edep);
    detectorHit->SetPosition(Position);
    detectorHit->SetParticle(particleDef);
    detectorHit->SetTrackID(TID);
    //detectorHit->SetMomentum(Momentum);

    EDHitsCollection->insert(detectorHit);

    return true;
}

void HadrontherapyExternalDetectorSD::EndOfEvent(G4HCofThisEvent*)
{;}
