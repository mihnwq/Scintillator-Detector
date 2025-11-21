#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"
#include "tls.hh"

class HitAction : public G4VHit
{
public:
    HitAction();
    virtual ~HitAction();
    HitAction(const HitAction &right);

    const HitAction& operator = (const HitAction &right);
    G4int operator == (const HitAction &right) const;

    void Draw() override {;}
    void Print() override {;}

    inline void* operator new(size_t);
    inline void operator delete(void *);

public:
    inline void SetPhot1(double no) { phot1 = no; }
    inline double GetPhot1() const { return phot1; }

    inline void SetPhot2(double no) { phot2 = no; }
    inline double GetPhot2() const { return phot2; }

    inline void AddPhot1() { phot1++; }
    inline void AddPhot2() { phot2++; }

private:
    int phot1 = 0;
    int phot2 = 0;
};


typedef G4THitsCollection<HitAction> HitActionHitsCollection;


extern G4ThreadLocal G4Allocator<HitAction>* HitActionAllocator;


inline void* HitAction::operator new(size_t)
{
    if (!HitActionAllocator)
        HitActionAllocator = new G4Allocator<HitAction>;
    return HitActionAllocator->MallocSingle();
}

inline void HitAction::operator delete(void* aHit)
{
    if (!HitActionAllocator)
        HitActionAllocator = new G4Allocator<HitAction>;
    HitActionAllocator->FreeSingle(static_cast<HitAction *>(aHit));
}

#endif // HIT_HH
