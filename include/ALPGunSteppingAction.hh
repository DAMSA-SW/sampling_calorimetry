#ifndef ALPGunSteppingAction_h
#define ALPGunSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "ALPGunEventAction.hh"
#include "globals.hh"

class G4LogicalVolume;

class ALPGunSteppingAction : public G4UserSteppingAction
{
  public:
    ALPGunSteppingAction(ALPGunEventAction* eventAction);
    virtual ~ALPGunSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
    ALPGunEventAction* fEventAction;   

  private:
    G4LogicalVolume* fScoringVolume1;
    G4LogicalVolume* fScoringVolume2;
    G4LogicalVolume* fScoringVolume3;
};

#endif
