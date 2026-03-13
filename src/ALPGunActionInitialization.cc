#include "ALPGunActionInitialization.hh"
#include "ALPGunPrimaryGeneratorAction.hh"
#include "ALPGunRunAction.hh"
#include "ALPGunSteppingAction.hh"

ALPGunActionInitialization::ALPGunActionInitialization()
{}

ALPGunActionInitialization::~ALPGunActionInitialization()
{}

void ALPGunActionInitialization::BuildForMaster() const
{
  SetUserAction(new ALPGunRunAction);
}

void ALPGunActionInitialization::Build() const
{
  SetUserAction(new ALPGunPrimaryGeneratorAction);
  SetUserAction(new ALPGunRunAction);
  auto eventAction = new ALPGunEventAction();
  SetUserAction(eventAction);
  SetUserAction(new ALPGunSteppingAction(eventAction));
}  

