#include "HadrontherapyExternalDetectorHit.hh"

//**********************MT
G4ThreadLocal G4Allocator<HadrontherapyExternalDetectorHit>* HadrontherapyExternalDetectorHitAllocator=0;
//**********************MT

HadrontherapyExternalDetectorHit::HadrontherapyExternalDetectorHit()
: G4VHit()
{
 energyDeposit = 0;
}

HadrontherapyExternalDetectorHit::~HadrontherapyExternalDetectorHit()
{
}

HadrontherapyExternalDetectorHit::HadrontherapyExternalDetectorHit(const HadrontherapyExternalDetectorHit& right)
  : G4VHit()
{
 energyDeposit = right.energyDeposit;
}

const HadrontherapyExternalDetectorHit& HadrontherapyExternalDetectorHit::operator=(const HadrontherapyExternalDetectorHit& right)
{
 energyDeposit = right.energyDeposit;
 return *this;
}
