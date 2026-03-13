#include "ALPGunSteppingAction.hh"
#include "ALPGunEventAction.hh"
#include "ALPGunDetectorConstruction.hh"

#include "G4RootAnalysisManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4INCLGlobals.hh"
#include "G4String.hh"
#include "ALPGunTrackingInfo.hh"

ALPGunSteppingAction::ALPGunSteppingAction(ALPGunEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0)
{}

ALPGunSteppingAction::~ALPGunSteppingAction()
{}

void ALPGunSteppingAction::UserSteppingAction(const G4Step* step)
{
  auto analysisManager = G4RootAnalysisManager::Instance();
  // get volume of the current step
  if (!fScoringVolume1) { 
    const ALPGunDetectorConstruction* detectorConstruction
      = static_cast<const ALPGunDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume1 = detectorConstruction->GetScoringVolume1();   
    fScoringVolume2 = detectorConstruction->GetScoringVolume2();   
    fScoringVolume3 = detectorConstruction->GetScoringVolume3();   
  }
  G4Track* tr = step->GetTrack();

  G4String preVolume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName();
  G4String postVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume() != NULL ? step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName() : "null";
  
  if (preVolume == "Absorber") {fEventAction->AddEdep_absorber(step->GetTotalEnergyDeposit()/MeV);}
  if (preVolume == "ECal") {fEventAction->AddEdep_ECal(step->GetTotalEnergyDeposit()/MeV);}
  if (((preVolume == "Absorber") or (preVolume == "ECal")) and postVolume == "World") {
    fEventAction->AddEdep_leakage(tr->GetKineticEnergy()/MeV);
  }
}

