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

#ifndef HadrontherapyDetectorConstruction_H
#define HadrontherapyDetectorConstruction_H 1

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "HadrontherapyDetectorROGeometry.hh"
#include "HadrontherapyExternalDetectorSD.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4PVPlacement;
class HadrontherapyDetectorROGeometry;
class HadrontherapyDetectorMessenger;
class HadrontherapyDetectorSD;
class HadrontherapyMatrix;
class HadrontherapyLet;

class HadrontherapyDetectorConstruction
{
public:

  HadrontherapyDetectorConstruction(G4VPhysicalVolume*);

  ~HadrontherapyDetectorConstruction();

public:
static HadrontherapyDetectorConstruction* GetInstance();
  void InitializeDetectorROGeometry(HadrontherapyDetectorROGeometry*,
				    G4ThreeVector detectorToWorldPosition);
  G4VPhysicalVolume* motherPhys;
  HadrontherapyDetectorSD*         detectorSD; // Pointer to sensitive detector
  HadrontherapyExternalDetectorSD*         ExternalDetectorSD;

private:

  void ConstructPhantom();
  void ConstructDetector();
  void ConstructExternalDetector();
  void ParametersCheck();
  void CheckOverlaps();

public:
// Get detector position relative to WORLD
inline G4ThreeVector GetDetectorToWorldPosition()
  {
    return phantomPosition + detectorPosition;
  }
/////////////////////////////////////////////////////////////////////////////
// Get displacement between phantom and detector by detector position (center of), phantom (center of) and detector sizes
inline G4ThreeVector GetDetectorToPhantomPosition()
{
    return G4ThreeVector(PhantomThick1/2 - detectorSizeX/2 + detectorPosition.getX(),
                         phantomSizeY/2 - detectorSizeY/2 + detectorPosition.getY(),
                         phantomSizeZ/2 - detectorSizeZ/2 + detectorPosition.getZ()
		          );
}

/////////////////////////////////////////////////////////////////////////////
// Calculate (and set) detector position by displacement, phantom and detector sizes
inline void SetDetectorPosition()
  {
	  // Adjust detector position
	  detectorPosition.setX(detectorToPhantomPosition.getX() - PhantomThick1/2 + detectorSizeX/2);
	  detectorPosition.setY(detectorToPhantomPosition.getY() - phantomSizeY/2 + detectorSizeY/2);
	  detectorPosition.setZ(detectorToPhantomPosition.getZ() - phantomSizeZ/2 + detectorSizeZ/2);


  }
/////////////////////////////////////////////////////////////////////////////
// Check whether detector is inside phantom
inline bool IsInside(G4double detectorX,
		     G4double detectorY,
		     G4double detectorZ,
		     G4double phantomX,
		     G4double phantomY,
		     G4double phantomZ,
		     G4ThreeVector pos)
{
// Dimensions check... X Y and Z
// Firstly check what dimension we are modifying
	{
	    if (detectorX > phantomX)
		 {
		    G4cout << "Error: Detector X dimension must be smaller or equal to the corrispondent of the phantom" << G4endl;
		    return false;
		 }
	    if ( (phantomX - detectorX) < pos.getX())
	         {
		    G4cout << "Error: X dimension doesn't fit with detector to phantom relative position" << G4endl;
		    return false;
	         }
	}

	{
	    if (detectorY > phantomY)
		 {
		    G4cout << "Error: Detector Y dimension must be smaller or equal to the corrispondent of the phantom" << G4endl;
		    return false;
		 }
	    if ( (phantomY - detectorY) < pos.getY())
	     {
		   G4cout << "Error: Y dimension doesn't fit with detector to phantom relative position" << G4endl;
		   return false;
	     }
	}

	{
	    if (detectorZ > phantomZ)
		 {
		    G4cout << "Error: Detector Z dimension must be smaller or equal to the corrispondent of the phantom" << G4endl;
		    return false;
		 }
	    if ( (phantomZ - detectorZ) < pos.getZ())
	     {
		   G4cout << "Error: Z dimension doesn't fit with detector to phantom relative position" << G4endl;
		   return false;
	     }
	}

	return true;
}
/////////////////////////////////////////////////////////////////////////////

  G4bool  SetPhantomMaterial1(G4String material1);
  G4bool  SetPhantomMaterial2(G4String material2);
  void SetVoxelSize(G4double sizeX, G4double sizeY, G4double sizeZ);
  void SetDetectorSize(G4double sizeX, G4double sizeY, G4double sizeZ);
  void SetPhantomSize(G4double sizeX, G4double sizeY, G4double sizeZ);
  void SetPhantomPosition(G4ThreeVector);
  void SetPhantomMat1Thick(G4double Mat1Thick);
  void SetPhantomMat2Thick(G4double Mat2Thick);
  void SetDetectorToPhantomPosition(G4ThreeVector DetectorToPhantomPosition);
  void SetUseExternalDetector(G4int Use){UseExternalDetector=Use;};
  void UpdateGeometry();
  void PrintParameters();
  G4LogicalVolume* GetDetectorLogicalVolume(){ return detectorLogicalVolume;}

private:
  static HadrontherapyDetectorConstruction* instance;
  HadrontherapyDetectorMessenger* detectorMessenger;

  G4VisAttributes* skyBlue;
  G4VisAttributes* red, *blue, *DeathStar;

  HadrontherapyDetectorROGeometry* detectorROGeometry; // Pointer to ROGeometry
  HadrontherapyDetectorROGeometry* ExternalDetectorROGeometry; // Pointer to ROGeometry
  HadrontherapyMatrix*             matrix;
  HadrontherapyLet*                let;

  G4Box *phantom1 , *phantom2, *detector;
  G4Sphere *ExternalDetector;
  G4LogicalVolume *phantom1LogicalVolume, *phantom2LogicalVolume, *detectorLogicalVolume, *ExternalDetectorLogicalVolume;
  G4VPhysicalVolume *phantom1PhysicalVolume, *phantom2PhysicalVolume, *detectorPhysicalVolume, *ExternalDetectorPhysicalVolume;

  G4double phantomSizeX;
  G4double phantomSizeY;
  G4double phantomSizeZ;

  G4double detectorSizeX;
  G4double detectorSizeY;
  G4double detectorSizeZ;

  G4double PhantomThick1;
  G4double PhantomThick2;

  G4ThreeVector phantomPosition, phantom1Position, phantom2Position, detectorPosition, detectorToPhantomPosition; //  phantom center, detector center, detector to phantom relative position

  G4double sizeOfVoxelAlongX;
  G4double sizeOfVoxelAlongY;
  G4double sizeOfVoxelAlongZ;

  G4int numberOfVoxelsAlongX;
  G4int numberOfVoxelsAlongY;
  G4int numberOfVoxelsAlongZ;

  G4double volumeOfVoxel, massOfVoxel;

  G4Material *phantomMaterial, *detectorMaterial, *PhantomMaterial1, *PhantomMaterial2;
  G4Region* aRegion;

  G4int UseExternalDetector;
};
#endif
