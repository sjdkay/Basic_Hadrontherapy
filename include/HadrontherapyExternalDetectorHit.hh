#ifndef HadrontherapyExternalDetectorHit_h
#define HadrontherapyExternalDetectorHit_h 1


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"

class HadrontherapyExternalDetectorHit : public G4VHit
{
public:
  HadrontherapyExternalDetectorHit();
  HadrontherapyExternalDetectorHit(const HadrontherapyExternalDetectorHit&);
  virtual ~HadrontherapyExternalDetectorHit();

  const HadrontherapyExternalDetectorHit& operator=(const HadrontherapyExternalDetectorHit&);

  G4int operator==(const HadrontherapyExternalDetectorHit&) const;

//******************************MT
inline void* operator new(size_t);
inline void operator delete(void*);
//******************************MT

private:

  G4double energyDeposit; // Energy deposit associated with the hit
  G4double VertexEnergy;
  G4ThreeVector VertexPosition, VertexMomentum, position, momentum;
  G4ParticleDefinition* particle;
  G4int TrackID;

public:

    // Methods to get the information
    inline G4double GetEdep()
    {return energyDeposit;}
    inline G4double GetVertexE()
    {return VertexEnergy;}
    inline G4ThreeVector GetVertexPos()
    {return VertexPosition;}
    inline G4ThreeVector GetVertexMom()
    {return VertexMomentum;}
    inline G4ThreeVector GetPosition()
    {return position;}
    inline G4ThreeVector GetMomentum()
    {return momentum;}
    inline G4ParticleDefinition* GetParticle()
    {return particle;}
    inline G4int GetTrackID()
    {return TrackID;}

    // Methods to store the information of the hit
    inline void SetEdep(G4double eDep)
    {energyDeposit = eDep;}
    inline void addEdep(G4double eDep)
    {energyDeposit += eDep;}
    inline void SetVertexE(G4double EVert)
    {VertexEnergy = EVert;}
    inline void SetVertexPos(G4ThreeVector VertexPos)
    {VertexPosition = VertexPos;}
    inline void SetVertexMom(G4ThreeVector VertexMom)
    {VertexMomentum = VertexMom;}
    inline void SetPosition(G4ThreeVector pos)
    {position=pos;}
    inline void SetMomentum(G4ThreeVector mom)
    {momentum = mom;}
    inline void SetParticle(G4ParticleDefinition* pdef)
    {particle = pdef;}
    inline void SetTrackID(G4int TrID)
    {TrackID = TrID;}
};

typedef G4THitsCollection<HadrontherapyExternalDetectorHit> HadrontherapyExternalDetectorHitsCollection;
//******************************MT
extern G4ThreadLocal G4Allocator<HadrontherapyExternalDetectorHit>* HadrontherapyExternalDetectorHitAllocator;
//******************************MT

inline void* HadrontherapyExternalDetectorHit::operator new(size_t)
{

 if(!HadrontherapyExternalDetectorHitAllocator)
  HadrontherapyExternalDetectorHitAllocator= new G4Allocator<HadrontherapyExternalDetectorHit>;
 void *aHit;

 aHit = (void *) HadrontherapyExternalDetectorHitAllocator->MallocSingle();
 return aHit;

}

inline void HadrontherapyExternalDetectorHit::operator delete(void *aHit)
{
if(!HadrontherapyExternalDetectorHitAllocator)
  HadrontherapyExternalDetectorHitAllocator= new G4Allocator<HadrontherapyExternalDetectorHit>;

HadrontherapyExternalDetectorHitAllocator->FreeSingle((HadrontherapyExternalDetectorHit*) aHit);
}

#endif
