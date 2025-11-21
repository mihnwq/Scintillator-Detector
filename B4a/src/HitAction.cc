#include "HitAction.hh"

HitAction::HitAction():G4VHit()
{}
HitAction::~HitAction()
{}

G4ThreadLocal G4Allocator<HitAction>* HitActionAllocator = nullptr;