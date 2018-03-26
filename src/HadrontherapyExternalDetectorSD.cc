
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
    collectionName.insert(HCname="HadrontherapyExternalDetectorHitsCollection");
    EDHitsCollection = NULL;
    sensitiveDetectorName = name;
}

/////////////////////////////////////////////////////////////////////////////
HadrontherapyExternalDetectorSD::~HadrontherapyExternalDetectorSD()
{
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyExternalDetectorSD::Initialize(G4HCofThisEvent*)
{
    EDHitsCollection = new HadrontherapyExternalDetectorHitsCollection(sensitiveDetectorName,
	    collectionName[0]);
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

    if (edep==0.) return false;

    G4ThreeVector Position = aStep->GetPreStepPoint()->GetPosition();
    G4ThreeVector Momentum = aStep->GetPreStepPoint()->GetMomentum();
    G4ParticleDefinition *particleDef = theTrack -> GetDefinition();
    G4double EVert = theTrack -> GetVertexKineticEnergy();
    G4ThreeVector Vert = theTrack -> GetVertexPosition();
    G4ThreeVector VertMom = theTrack -> GetVertexMomentumDirection();

    G4cout << EVert/MeV << "   " << Vert(0)/cm << "   " << Vert(1)/cm << "   " << Vert(2)/cm <<G4endl;

    HadrontherapyExternalDetectorHit* detectorHit = new HadrontherapyExternalDetectorHit();

    detectorHit->AddEdep(edep);
    //detectorHit->SetPosition(Position);
    //detectorHit->SetMomentum(Momentum);
    //detectorHit->SetParticle(particleDef);

    EDHitsCollection->insert(detectorHit);

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

    HCE -> AddHitsCollection(HCID,EDHitsCollection);
}

