#include "TrackingAction.hh"
#include "PhotonMuonHelper.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4Track.hh"

extern PhotonMuonHelper gPhotonMuonHelper;

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    G4int trackID = track->GetTrackID();
    G4int parentID = track->GetParentID();


    gPhotonMuonHelper.parentMap[trackID] = parentID;

//meun -> electron -> .. ->photonu
    auto def = track->GetDefinition();
    if(def == G4MuonMinus::MuonMinusDefinition() ||
       def == G4MuonPlus::MuonPlusDefinition())
    {
        gPhotonMuonHelper.muonStartMap[trackID] = track->GetVertexPosition();
        gPhotonMuonHelper.isMuonFamily[trackID] = true;
       // G4cout << "One muon found at the start position:"<<gPhotonMuonHelper.muonStartMap[trackID] << "Also now he makes part of the family"<<gPhotonMuonHelper.isMuonFamily[trackID]<< G4endl;
        return;

    }

    if(gPhotonMuonHelper.isMuonFamily[parentID])
        gPhotonMuonHelper.isMuonFamily[trackID] = true;
}
