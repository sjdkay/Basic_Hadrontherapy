// This has been edited to add many new histograms/nTuples and filling routines for them

#include "HadrontherapyAnalysisManager.hh"
#include "HadrontherapyMatrix.hh"
#include "HadrontherapyAnalysisFileMessenger.hh"
#include "G4SystemOfUnits.hh"
#include <time.h>

HadrontherapyAnalysisManager* HadrontherapyAnalysisManager::instance = 0;

HadrontherapyAnalysisManager::HadrontherapyAnalysisManager()
#ifdef G4ANALYSIS_USE_ROOT
:
analysisFileName("DoseDistribution2.root"),theTFile(0), histo1(0), histo2(0), histo3(0),
histo4(0), histo5(0), histo6(0), histo7(0), histo8(0), histo9(0), histo10(0), histo11(0), histo11b(0), histo11c(0), histo11d(0), histo11e(0), histo12(0), histo13(0), histo14(0), histo15(0), histo16(0), histo17(0),
histo18a(0), histo18b(0), histo19a(0), histo19b(0), histo20a(0), histo20b(0), histo21(0), histo22(0),
EDHist1(0),
kinFragNtuple(0),
kineticEnergyPrimaryNtuple(0),
ExternalDetectorNtuple(0),
PromptGammaNtuple(0),
doseFragNtuple(0),
fluenceFragNtuple(0),
letFragNtuple(0),
theROOTNtuple(0),
theROOTIonTuple(0),
fragmentNtuple(0),
metaData(0),
eventCounter(0)
#endif
{
    fMess = new HadrontherapyAnalysisFileMessenger(this);
}
/////////////////////////////////////////////////////////////////////////////

HadrontherapyAnalysisManager::~HadrontherapyAnalysisManager()
{
    delete fMess;
#ifdef G4ANALYSIS_USE_ROOT
    Clear();
#endif
}

HadrontherapyAnalysisManager* HadrontherapyAnalysisManager::GetInstance()
{
	if (instance == 0) instance = new HadrontherapyAnalysisManager;
	return instance;
}
#ifdef G4ANALYSIS_USE_ROOT
void HadrontherapyAnalysisManager::Clear()
{
    if (theTFile)
    {
	delete metaData;
	metaData = 0;

	delete fragmentNtuple;
	fragmentNtuple = 0;

	delete theROOTIonTuple;
	theROOTIonTuple = 0;

	delete theROOTNtuple;
	theROOTNtuple = 0;

	delete ExternalDetectorNtuple;
	ExternalDetectorNtuple = 0;

    delete PromptGammaNtuple;
	PromptGammaNtuple = 0;

	delete EDHist1;
	EDHist1 = 0;

    delete histo22;
	histo22 = 0;

	delete histo21;
	histo21 = 0;

    delete histo20b;
	histo20b = 0;

	delete histo20a;
	histo20a = 0;

    delete histo19b;
	histo19b = 0;

	delete histo19a;
	histo19a = 0;

	delete histo18b;
	histo18b = 0;

	delete histo18a;
	histo18a = 0;

	delete histo17;
	histo17 = 0;

	delete histo16;
	histo16 = 0;

	delete histo15;
	histo15 = 0;

	delete histo14;
	histo14 = 0;

	delete histo13;
	histo13 = 0;

	delete histo12;
	histo12 = 0;

    delete histo11e;
	histo11e = 0;

    delete histo11d;
	histo11d = 0;

	delete histo11c;
	histo11c = 0;

	delete histo11b;
	histo11b = 0;

	delete histo11;
	histo11 = 0;

	delete histo10;
	histo10 = 0;

	delete histo9;
	histo9 = 0;

	delete histo8;
	histo8 = 0;

	delete histo7;
	histo7 = 0;

	delete histo6;
	histo6 = 0;

	delete histo5;
	histo5 = 0;

	delete histo4;
	histo4 = 0;

	delete histo3;
	histo3 = 0;

	delete histo2;
	histo2 = 0;

	delete histo1;
	histo1 = 0;
    }
}
/////////////////////////////////////////////////////////////////////////////

void HadrontherapyAnalysisManager::SetAnalysisFileName(G4String aFileName)
{
	this->analysisFileName = aFileName;
}

	/////////////////////////////////////////////////////////////////////////////
G4bool HadrontherapyAnalysisManager::IsTheTFile()
{
    return (theTFile) ? true:false;
}
void HadrontherapyAnalysisManager::book()
{
	delete theTFile; // this is similar to theTFile->Close() => delete all associated variables created via new, moreover it delete itself.

	theTFile = new TFile(analysisFileName, "RECREATE");

	// Create the histograms with the energy deposit along the X axis
	histo1 = createHistogram1D("braggPeak","slice, energy", 100, 0., 100); //<different waterthicknesses are accoutned for in ROOT-analysis stage
	histo2 = createHistogram1D("h20","Secondary protons - slice, energy", 400, 0., 400.);
	histo3 = createHistogram1D("h30","Secondary neutrons - slice, energy", 400, 0., 400.);
	histo4 = createHistogram1D("h40","Secondary alpha - slice, energy", 400, 0., 400.);
	histo5 = createHistogram1D("h50","Secondary gamma - slice, energy", 400, 0., 400.);
	histo6 = createHistogram1D("h60","Secondary electron - slice, energy", 400, 0., 400.);
	histo7 = createHistogram1D("h70","Secondary triton - slice, energy", 400, 0., 400.);
	histo8 = createHistogram1D("h80","Secondary deuteron - slice, energy", 400, 0., 400.);
	histo9 = createHistogram1D("h90","Secondary pion - slice, energy", 400, 0., 400.);
	histo10 = createHistogram1D("h100","Energy distribution of secondary electrons", 70, 0., 70.);
	histo11 = createHistogram1D("h110","Energy distribution of secondary photons", 200, 0., 20.);
	histo11b = createHistogram1D("h110b", "Energy distribution of secondary photons", 198, 0.1, 10.);
	histo11c = createHistogram1D("h110c", "Energy distribution of secondary photons", 300, 2., 5.);
	histo11d = createHistogram1D("h110d", "X Position distirbution of secondary photons", 300, 0, 10);
    histo11e = createHistogram1D("h110e", "Energy distribution of secondary photons", 800, 3., 5.);
	histo12 = createHistogram1D("h120","Energy distribution of secondary deuterons", 70, 0., 70.);
	histo13 = createHistogram1D("h130","Energy distribution of secondary tritons", 70, 0., 70.);
	histo14 = createHistogram1D("h140","Energy distribution of secondary alpha particles", 70, 0., 70.);
	histo15 = createHistogram1D("heliumEnergyAfterPhantom","Energy distribution of secondary helium fragments after the phantom",
		70, 0., 500.);
	histo16 = createHistogram1D("hydrogenEnergyAfterPhantom","Energy distribution of secondary helium fragments after the phantom",
		70, 0., 500.);
    histo17 = createHistogram2D("h170", "Photon Energy Distribution as fn of X Position", 300, 0, 10, 300, 2., 5.);
    histo18a = createHistogram1D("h180a", "Energy distribution of secondary neutrons", 400, 0, 50);
    histo18b = createHistogram1D("h180b", "Energy distribution of secondary neutrons", 300, 2, 5);
    histo19a = createHistogram1D("h190a", "#theta distribution of secondary photons", 400, 0, 180);
    histo19b = createHistogram1D("h190b", "#phi distribution of secondary photons", 400, -180, 180);
    histo20a = createHistogram1D("h200a", "#theta distribution of secondary neutrons", 400, 0, 180);
    histo20b = createHistogram1D("h200b", "#phi distribution of secondary neutrons", 400, -180, 180);
    histo21 = createHistogram2D("h210" , "Energy Distribution as fn of #theta", 200, 0, 180, 200, 0.1, 10);
    histo22 = createHistogram2D("h220" , "Energy Distribution as fn of #phi", 200, -180, 180, 200, 0.1, 10);

    EDHist1 = createHistogram1D("EDHist1", "Energy Deposition in External Detector", 1000, 0, 10);

	kinFragNtuple  = new TNtuple("kinFragNtuple",
		"Kinetic energy by voxel & fragment",
		"i:j:k:A:Z:kineticEnergy");

	kineticEnergyPrimaryNtuple= new TNtuple("kineticEnergyPrimaryNtuple",
		"Kinetic energy by voxel of primary",
		"i:j:k:kineticEnergy");

    ExternalDetectorNtuple = new TNtuple("ExternalDetectorNtuple",
		"Energy by event",
		"Energy:Hits");

   PromptGammaNtuple = new TNtuple("PromptGammaNtuple",
		"Prompt Gamma Information",
		"ParentTrackID:Energy:VertexX:VertexY:VertexZ:Theta:Phi");

	doseFragNtuple = new TNtuple("doseFragNtuple",
		"Energy deposit by voxel & fragment",
		"i:j:k:A:Z:energy");

	fluenceFragNtuple = new TNtuple("fluenceFragNtuple",
		"Fluence by voxel & fragment",
		"i:j:k:A:Z:fluence");

	letFragNtuple = new TNtuple("letFragNtuple",
		"Let by voxel & fragment",
		"i:j:k:A:Z:letT:letD");

	theROOTNtuple =   new TNtuple("theROOTNtuple",
		"Energy deposit by slice",
		"i:j:k:energy");

	theROOTIonTuple = new TNtuple("theROOTIonTuple",
		"Generic ion information",
		"a:z:occupancy:energy");

	fragmentNtuple =  new TNtuple("fragmentNtuple",
		"Fragments",
		"A:Z:energy:posX:posY:posZ");

	metaData =        new TNtuple("metaData",
		"Metadata",
		"events:detectorDistance:waterThickness:beamEnergy:energyError:phantomCenterDistance");
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::FillEnergyDeposit(G4int i,
						     G4int j,
						     G4int k,
						     G4double energy)
{
	if (theROOTNtuple)
	{
		theROOTNtuple->Fill(i, j, k, energy);
	}
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::BraggPeak(G4int slice, G4double energy)
{
	histo1->SetBinContent(slice, energy); //This uses setbincontent instead of fill to get labels correct
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryProtonEnergyDeposit(G4int slice, G4double energy)
{
	histo2->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryNeutronEnergyDeposit(G4int slice, G4double energy)
{
	histo3->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryAlphaEnergyDeposit(G4int slice, G4double energy)
{
	histo4->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryGammaEnergyDeposit(G4int slice, G4double energy)
{
	histo5->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryElectronEnergyDeposit(G4int slice, G4double energy)
{
	histo6->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryTritonEnergyDeposit(G4int slice, G4double energy)
{
	histo7->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryDeuteronEnergyDeposit(G4int slice, G4double energy)
{
	histo8->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::SecondaryPionEnergyDeposit(G4int slice, G4double energy)
{
	histo9->Fill(slice, energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::electronEnergyDistribution(G4double energy)
{
	histo10->Fill(energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyDistribution(G4double energy)
{
	histo11->Fill(energy);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyDistributionb(G4double energy)
{
	histo11b->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyDistributionc(G4double energy)
{
	histo11c->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaPositionDistribution(G4double XPos)
{
	histo11d->Fill(XPos);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyDistributione(G4double energy)
{
	histo11e->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::deuteronEnergyDistribution(G4double energy)
{
	histo12->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::tritonEnergyDistribution(G4double energy)
{
	histo13->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::alphaEnergyDistribution(G4double energy)
{
	histo14->Fill(energy);
}
/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::heliumEnergy(G4double secondaryParticleKineticEnergy)
{
	histo15->Fill(secondaryParticleKineticEnergy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::hydrogenEnergy(G4double secondaryParticleKineticEnergy)
{
	histo16->Fill(secondaryParticleKineticEnergy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyPositionDistribution(G4double XPos, G4double energy)
{
	histo17->Fill(XPos, energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::neutronEnergyDistributiona(G4double energy)
{
	histo18a->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::neutronEnergyDistributionb(G4double energy)
{
	histo18b->Fill(energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaThetaDistribution(G4double Theta)
{
	histo19a->Fill(Theta);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaPhiDistribution(G4double Phi)
{
	histo19b->Fill(Phi);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::neutronThetaDistribution(G4double Theta)
{
	histo20a->Fill(Theta);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::neutronPhiDistribution(G4double Phi)
{
	histo20b->Fill(Phi);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyThetaDistribution(G4double theta, G4double energy)
{
	histo21->Fill(theta, energy);
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::gammaEnergyPhiDistribution(G4double phi, G4double energy)
{
	histo22->Fill(phi, energy);
}


	/////////////////////////////////////////////////////////////////////////////
	// FillKineticFragmentTuple create an ntuple where the voxel indexs, the atomic number and mass and the kinetic
	// energy of all the particles interacting with the phantom, are stored
void HadrontherapyAnalysisManager::FillKineticFragmentTuple(G4int i, G4int j, G4int k, G4int A, G4double Z, G4double kinEnergy)
{
    kinFragNtuple -> Fill(i, j, k, A, Z, kinEnergy);
}

	/////////////////////////////////////////////////////////////////////////////
	// FillKineticEnergyPrimaryNTuple creates a ntuple where the voxel indexs and the kinetic
	// energies of ONLY primary particles interacting with the phantom, are stored
void HadrontherapyAnalysisManager::FillKineticEnergyPrimaryNTuple(G4int i, G4int j, G4int k, G4double kinEnergy)
{
    kineticEnergyPrimaryNtuple -> Fill(i, j, k, kinEnergy);
}

	/////////////////////////////////////////////////////////////////////////////
	// This function is called only if ROOT is activated.
	// It is called by the HadrontherapyMatric.cc class file and it is used to create two ntuples containing
	// the total energy deposited and the fluence values, in each voxel and per any particle (primary
	// and secondary particles beam)
void HadrontherapyAnalysisManager::FillVoxelFragmentTuple(G4int i, G4int j, G4int k, G4int A, G4double Z, G4double energy, G4double fluence)
{
		// Fill the ntuple containing the voxel, mass and atomic number and the energy deposited
    doseFragNtuple ->    Fill( i, j, k, A, Z, energy );

		// Fill the ntuple containing the voxel, mass and atomic number and the fluence
	if (i==1 && Z==1) {
		fluenceFragNtuple -> Fill( i, j, k, A, Z, fluence );

	}
}

void HadrontherapyAnalysisManager::FillLetFragmentTuple(G4int i, G4int j, G4int k, G4int A, G4double Z, G4double letD)
{
  letFragNtuple -> Fill( i, j, k, A, Z, letD/MeV);
}
	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::FillFragmentTuple(G4int A, G4double Z, G4double energy, G4double posX, G4double posY, G4double posZ)
{
	fragmentNtuple->Fill(A, Z, energy, posX, posY, posZ);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::EDEnergyDeposit(G4double EDep)
{
	EDHist1->Fill(EDep);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::FillPromptGammaNtuple(G4int ParentTID, G4double energy, G4double PosX, G4double PosY, G4double PosZ, G4double Theta, G4double Phi)
{
	PromptGammaNtuple->Fill(ParentTID, energy, PosX, PosY, PosZ, Theta, Phi);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::FillExternalDetectorNtuple(G4double EDep, G4int nHits)
{
	ExternalDetectorNtuple->Fill(EDep, nHits);
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::genericIonInformation(G4int a,
														 G4double z,
														 G4int electronOccupancy,
														 G4double energy)
{
	if (theROOTIonTuple) {
		theROOTIonTuple->Fill(a, z, electronOccupancy, energy);
	}
}

	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::startNewEvent()
{
	eventCounter++;
}
	/////////////////////////////////////////////////////////////////////////////
void HadrontherapyAnalysisManager::setGeometryMetaData(G4double endDetectorPosition, G4double waterThickness, G4double phantomCenter)
{
	this->detectorDistance = endDetectorPosition;
	this->phantomDepth = waterThickness;
	this->phantomCenterDistance = phantomCenter;
}
void HadrontherapyAnalysisManager::setBeamMetaData(G4double meanKineticEnergy,G4double sigmaEnergy)
{
	this->beamEnergy = meanKineticEnergy;
	this->energyError = sigmaEnergy;
}
/////////////////////////////////////////////////////////////////////////////
// Flush data & close the file
void HadrontherapyAnalysisManager::flush()
{
    if (theTFile)
    {
	theTFile -> Write();
	theTFile -> Close();
    }
    theTFile = 0;
    eventCounter = 0;
}

#endif
