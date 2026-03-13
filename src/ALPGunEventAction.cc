#include "ALPGunEventAction.hh"
#include "G4RootAnalysisManager.hh"

ALPGunEventAction::ALPGunEventAction()
: G4UserEventAction(),
  fEdep_absorber(0.),
  fEdep_ECal(0.),
  fEdep_leakage(0.)
{}

ALPGunEventAction::~ALPGunEventAction() {}

void ALPGunEventAction::BeginOfEventAction(const G4Event*)
{
    fEdep_absorber = 0.;
    fEdep_ECal = 0.;
    fEdep_leakage = 0.;
}

void ALPGunEventAction::AddEdep_absorber(G4double edep)
{
    fEdep_absorber += edep;
}

void ALPGunEventAction::AddEdep_ECal(G4double edep)
{
    fEdep_ECal += edep;
}

void ALPGunEventAction::AddEdep_leakage(G4double edep)
{
    fEdep_leakage += edep;
}

void ALPGunEventAction::EndOfEventAction(const G4Event*)
{
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, fEdep_absorber);
    analysisManager->FillNtupleDColumn(1, fEdep_ECal);
    analysisManager->FillNtupleDColumn(2, fEdep_leakage);
    analysisManager->AddNtupleRow();
}
