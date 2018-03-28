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

#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4VVisManager.hh"

#include "HadrontherapyEventAction.hh"
#include "HadrontherapyDetectorHit.hh"
#include "HadrontherapyDetectorSD.hh"
#include "HadrontherapyExternalDetectorSD.hh"
#include "HadrontherapyExternalDetectorHit.hh"
#include "HadrontherapyDetectorConstruction.hh"
#include "HadrontherapyMatrix.hh"
#include "HadrontherapyEventActionMessenger.hh"
#include "HadrontherapyAnalysisManager.hh"

/////////////////////////////////////////////////////////////////////////////
HadrontherapyEventAction::HadrontherapyEventAction() :
  drawFlag("all" ),printModulo(10), pointerEventMessenger(0)
{
    DHitsCollectionID = -1;
    EDHitsCollectionID = -1;
    pointerEventMessenger = new HadrontherapyEventActionMessenger(this);
}

/////////////////////////////////////////////////////////////////////////////
HadrontherapyEventAction::~HadrontherapyEventAction()
{
    delete pointerEventMessenger;
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyEventAction::BeginOfEventAction(const G4Event* evt)
{
    G4int evtNb = evt->GetEventID();
    //printing survey
    if (evtNb%printModulo == 0)
     G4cout << "\n---> Begin of Event: " << evtNb << G4endl;

    G4SDManager* pSDManager = G4SDManager::GetSDMpointer();
    if(DHitsCollectionID == -1)
    DHitsCollectionID = pSDManager -> GetCollectionID("HadrontherapyDetectorHitsCollection");
    if(EDHitsCollectionID == -1)
    EDHitsCollectionID = pSDManager -> GetCollectionID("EDHitsCollection");
}

/////////////////////////////////////////////////////////////////////////////
void HadrontherapyEventAction::EndOfEventAction(const G4Event* evt)
{
    if(DHitsCollectionID < 0) return;
    if(EDHitsCollectionID < 0) return;

    G4HCofThisEvent* HCE = evt -> GetHCofThisEvent();
    G4HCofThisEvent* HCE2 = evt -> GetHCofThisEvent();

    // Clear voxels hit list
    HadrontherapyMatrix* matrix = HadrontherapyMatrix::GetInstance();
    HadrontherapyAnalysisManager* analysis =  HadrontherapyAnalysisManager::GetInstance();
    if (matrix) matrix -> ClearHitTrack();

    if(HCE)
    {
    HadrontherapyDetectorHitsCollection* CHC = (HadrontherapyDetectorHitsCollection*)(HCE -> GetHC(DHitsCollectionID));
    if(CHC)
        {
        if(matrix)
            {
            // Fill the matrix with the information: voxel and associated energy deposit
            // in the detector at the end of the event
            G4int HitCount = CHC -> entries();
            for (G4int h=0; h<HitCount; h++)
                {
                G4int i = ((*CHC)[h]) -> GetXID();
                G4int j = ((*CHC)[h]) -> GetYID();
                G4int k = ((*CHC)[h]) -> GetZID();
                G4double energyDeposit = ((*CHC)[h]) -> GetEdep();
                matrix -> Fill(i, j, k, energyDeposit/MeV);
                }
            }
        }
    }

    G4int TotalEDHits = 0;
    G4double TotalEDEDep = 0.;
    if (HCE2){
    HadrontherapyExternalDetectorHitsCollection* CHC2 = (HadrontherapyExternalDetectorHitsCollection*)(HCE2 -> GetHC(EDHitsCollectionID));
        if(CHC2){
            int n_hit = CHC2->entries();
            for ( int i = 0 ; i < n_hit; i++){
                G4double EDep = (*CHC2)[i]->GetEdep();
                G4ThreeVector position = (*CHC2)[i]->GetPosition();
                G4int TrackID = (*CHC2)[i]->GetTrackID();
                if(EDep >0){
                    TotalEDHits++;
                    TotalEDEDep += EDep;
                }
            }
            if(TotalEDEDep != 0) analysis->EDEnergyDeposit(TotalEDEDep / MeV);
            analysis->FillExternalDetectorNtuple(TotalEDEDep / MeV, TotalEDHits);
        }
    }
}

