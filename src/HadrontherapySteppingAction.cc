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
// Hadrontherapy advanced example for Geant4
// See more at: https://twiki.cern.ch/twiki/bin/view/Geant4/AdvancedExamplesHadrontherapy

#include "G4SteppingManager.hh"
#include "G4TrackVector.hh"
#include "HadrontherapySteppingAction.hh"
#include "G4ios.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4TrackVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4UserEventAction.hh"
#include "G4TransportationManager.hh"
#include "G4VSensitiveDetector.hh"
#include "HadrontherapyRunAction.hh"
#include "HadrontherapyAnalysisManager.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////////////////////////////
HadrontherapySteppingAction::HadrontherapySteppingAction( HadrontherapyRunAction *run)
{
    runAction = run;
}

/////////////////////////////////////////////////////////////////////////////
HadrontherapySteppingAction::~HadrontherapySteppingAction()
{
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapySteppingAction::UserSteppingAction(const G4Step* aStep)
{


G4StepPoint* PreStep = aStep->GetPreStepPoint();
G4StepPoint* PostStep = aStep->GetPostStepPoint();

G4TouchableHandle touchPreStep = PreStep->GetTouchableHandle();
G4TouchableHandle touchPostStep = PostStep->GetTouchableHandle();
//To get the current volume:
G4VPhysicalVolume* volumePre = touchPreStep->GetVolume();
G4VPhysicalVolume* volumePost =touchPostStep->GetVolume();

//To get its name:
G4String namePre = volumePre->GetName();
G4String namePost;

G4int EventNum = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();

if(volumePost){
 namePost = volumePost->GetName();
     }

G4Track* theTrack = aStep->GetTrack();
G4int TrackNumber = aStep -> GetTrack() -> GetTrackID();
G4int StepNumber = theTrack -> GetCurrentStepNumber();

    if( aStep->GetTrack()->GetVolume()->GetName() == "NewDetectorPhys"){
#ifdef G4ANALYSIS_USE_ROOT
	G4ParticleDefinition *def = aStep->GetTrack()->GetDefinition();
	G4double secondaryParticleKineticEnergy =  aStep->GetTrack()->GetKineticEnergy();
	G4String particleType = def->GetParticleType(); // particle type = nucleus for d, t, He3, alpha, and heavier nuclei
	G4String particleName = def->GetParticleName(); // e.g. for alpha: the name = "alpha" and type = "nucleus"
	if(particleType == "nucleus") {
	    G4int A = def->GetBaryonNumber();
	    G4double Z = def->GetPDGCharge();
	    G4double posX = aStep->GetTrack()->GetPosition().x() / cm;
	    G4double posY = aStep->GetTrack()->GetPosition().y() / cm;
	    G4double posZ = aStep->GetTrack()->GetPosition().z() / cm;
	    G4double energy = secondaryParticleKineticEnergy / A / MeV;

	    HadrontherapyAnalysisManager* analysisMgr =  HadrontherapyAnalysisManager::GetInstance();
	    analysisMgr->FillFragmentTuple(A, Z, energy, posX, posY, posZ);
	} else if(particleName == "proton") {   // proton (hydrogen-1) is a special case
	    G4double posX = aStep->GetTrack()->GetPosition().x() / cm ;
	    G4double posY = aStep->GetTrack()->GetPosition().y() / cm ;
	    G4double posZ = aStep->GetTrack()->GetPosition().z() / cm ;
	    G4double energy = secondaryParticleKineticEnergy * MeV;    // Hydrogen-1: A = 1, Z = 1
	    HadrontherapyAnalysisManager::GetInstance()->FillFragmentTuple(1, 1.0, energy, posX, posY, posZ);
	}

	G4String secondaryParticleName =  def -> GetParticleName();
	//G4cout <<"Particle: " << secondaryParticleName << G4endl;
	//G4cout <<"Energy: " << secondaryParticleKineticEnergy << G4endl;
	HadrontherapyAnalysisManager* analysis =  HadrontherapyAnalysisManager::GetInstance();
	//There is a bunch of stuff recorded with the energy 0, something should perhaps be done about this.
	if(secondaryParticleName == "proton") {
	    analysis->hydrogenEnergy(secondaryParticleKineticEnergy / MeV);
	}
	if(secondaryParticleName == "deuteron") {
	    analysis->hydrogenEnergy((secondaryParticleKineticEnergy/2) / MeV);
	}
	if(secondaryParticleName == "triton") {
	    analysis->hydrogenEnergy((secondaryParticleKineticEnergy/3) / MeV);
	}
	if(secondaryParticleName == "alpha") {
	    analysis->heliumEnergy((secondaryParticleKineticEnergy/4) / MeV);
	}
	if(secondaryParticleName == "He3"){
	    analysis->heliumEnergy((secondaryParticleKineticEnergy/3) / MeV);
	}
#endif

	aStep->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
    }

    // Electromagnetic and hadronic processes of primary particles in the phantom
    //setting phantomPhys correctly will break something here fixme
    if ((aStep -> GetTrack() -> GetTrackID() == 1) &&
	    (aStep -> GetTrack() -> GetVolume() -> GetName() == "PhantomPhys") &&
	    (aStep -> GetPostStepPoint() -> GetProcessDefinedStep() != NULL))
    {
	G4String process = aStep -> GetPostStepPoint() ->
	    GetProcessDefinedStep() -> GetProcessName();

	if ((process == "Transportation") || (process == "StepLimiter")) {;}
	else
	{
	    if ((process == "msc") || (process == "hLowEIoni") || (process == "hIoni"))
	    {
		runAction -> AddEMProcess();
	    }
	    else
	    {
		runAction -> AddHadronicProcess();

		if ( (process != "LElastic") && (process != "ProtonInelastic") && (process != "hElastic") )
		    G4cout << "Warning! Unknown proton process: "<< process << G4endl;
	    }
	}
    }

    // Retrieve information about the secondary particles originated in the phantom

    G4SteppingManager*  steppingManager = fpSteppingManager;

    if(TrackNumber != 1){
        if(StepNumber == 1){

            G4String volumeName = theTrack-> GetLogicalVolumeAtVertex() -> GetName();

            if(volumeName == "phantomLog" || volumeName == "DetectorLog"){

                G4String Name =  theTrack -> GetDefinition() -> GetParticleName();
                G4double EVert = theTrack -> GetVertexKineticEnergy();
                G4ThreeVector Vert = theTrack -> GetVertexPosition();
                G4ThreeVector VertMom = theTrack -> GetVertexMomentumDirection();
                G4double VertX = Vert(0);
                G4double Theta = VertMom.theta();
                G4double Phi = VertMom.phi();

                //G4cout << EventNum << "  " << TrackNumber << "   " << StepNumber << "   " << Name << "   " << Vert << G4endl;

                HadrontherapyAnalysisManager* analysis =  HadrontherapyAnalysisManager::GetInstance();

                if (Name == "e-")
                analysis -> electronEnergyDistribution(EVert/MeV);

                if (Name == "gamma"){
                    analysis -> gammaEnergyDistribution(EVert/MeV);
                    analysis -> gammaPositionDistribution(VertX/cm);
		    if(EVert/MeV > 0.1 && EVert/MeV < 10){
                        analysis -> gammaEnergyDistributionb(EVert/MeV);
                        analysis -> gammaEnergyThetaDistribution(Theta/degree, EVert/MeV);
                        analysis -> gammaEnergyPhiDistribution(Phi/degree, EVert/MeV);
                        analysis -> gammaThetaDistribution(Theta/degree);
                        analysis -> gammaPhiDistribution(Phi/degree);
                    }
                    if(EVert/MeV > 2 && EVert/MeV < 5){
                        analysis -> gammaEnergyDistributionc(EVert/MeV);
			analysis -> gammaEnergyPositionDistribution(VertX/cm, EVert/MeV);
		    }
                    //if(EVert/MeV > 3.5 && EVert/MeV < 3.9){
		    //  analysis -> gammaEnergyPositionDistribution(VertX/cm, EVert/MeV);
                    //}
                }
                if(Name == "neutron"){
                    analysis ->neutronEnergyDistributiona(EVert/MeV);
                    analysis -> neutronThetaDistribution(Theta/degree);
                    analysis -> neutronPhiDistribution(Phi/degree);
                    if(EVert/MeV > 2 && EVert/MeV < 5){
                        analysis ->neutronEnergyDistributionb(EVert/MeV);
                    }
                }

                if (Name == "deuteron")
                analysis -> deuteronEnergyDistribution(EVert/MeV);

                if (Name == "triton")
                analysis -> tritonEnergyDistribution(EVert/MeV);

                if (Name == "alpha")
                analysis -> alphaEnergyDistribution(EVert/MeV);

                G4double z = theTrack-> GetDynamicParticle() -> GetDefinition() -> GetPDGCharge();
                if (z > 0.)
                {
                G4int a = theTrack-> GetDynamicParticle() -> GetDefinition() -> GetBaryonNumber();
                G4int electronOccupancy = theTrack ->  GetDynamicParticle() -> GetTotalOccupancy();

                // If a generic ion is originated in the detector, its baryonic number, PDG charge,
                // total number of electrons in the orbitals are stored in a ntuple
                analysis -> genericIonInformation(a, z, electronOccupancy, EVert/MeV);
                }
            }
        }
    }
}





