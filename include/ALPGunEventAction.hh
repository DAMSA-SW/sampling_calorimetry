#ifndef ALPGunEventAction_h
#define ALPGunEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class ALPGunEventAction;

class ALPGunEventAction : public G4UserEventAction
{
public:
    ALPGunEventAction();
    virtual ~ALPGunEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void AddEdep_absorber(G4double edep_absorber);
    void AddEdep_ECal(G4double edep_Ecal);
    void AddEdep_leakage(G4double edep_leakage);

private:
    G4double fEdep_absorber;
    G4double fEdep_ECal;
    G4double fEdep_leakage;
};

#endif
