#include "ALPGunDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "ALPGunRunAction.hh"
ALPGunDetectorConstruction::ALPGunDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume1(0),
  fScoringVolume2(0),
  fScoringVolume3(0)
{
  messenger = new G4GenericMessenger(this, "/detector/", "Detector properties");
  messenger->DeclarePropertyWithUnit("absorberLength","cm", m_absorberLength)
        .SetGuidance("Set detector absorber length")
        .SetStates(G4State_PreInit, G4State_Idle);

  messenger->DeclarePropertyWithUnit("ECalLength","cm", m_ECalLength)
        .SetGuidance("Set gap length")
        .SetStates(G4State_PreInit, G4State_Idle);

  messenger->DeclareProperty("absorberMaterial", m_absorber_mat)
        .SetGuidance("Set absorber material")
        .SetStates(G4State_PreInit, G4State_Idle);

  messenger->DeclareProperty("ECalMaterial", m_ECal_mat)
        .SetGuidance("Set ECal material")
        .SetStates(G4State_PreInit, G4State_Idle);
}

ALPGunDetectorConstruction::~ALPGunDetectorConstruction()
{
  delete messenger;
}

G4VPhysicalVolume* ALPGunDetectorConstruction::Construct()
{  

    // === Parameters ===
    G4double absorberLength = m_absorberLength;  // Replace with your desired x
    G4double ECalLength = m_ECalLength;    // Replace with your desired y
    G4double detectorLength = absorberLength + ECalLength;
    G4double detectorWidth = 12.0 * cm;     // Arbitrary transverse size

    // === Materials ===
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* absorber_mat = nist->FindOrBuildMaterial(m_absorber_mat);
    G4Material* ECal_mat = nist->FindOrBuildMaterial(m_ECal_mat);

    // === World Volume ===
    G4double worldSizeZ = ECalLength*1.5;
    G4Box* solidWorld = new G4Box("World", 0.1 * m, 0.1 * m, worldSizeZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0,
                                                     G4ThreeVector(),
                                                     logicWorld,
                                                     "World",
                                                     0,
                                                     false,
                                                     0,
                                                     true);



    G4Box* solidAbsorber = new G4Box("Absorber", detectorWidth/2, detectorWidth/2, absorberLength/2);
    G4LogicalVolume* logicAbsorber = new G4LogicalVolume(solidAbsorber, absorber_mat, "Absorber");
    new G4PVPlacement(0, G4ThreeVector(0, 0, absorberLength/2), logicAbsorber, "Absorber", logicWorld, false, 0, true);

    G4Box* solidECal = new G4Box("ECal", detectorWidth/2, detectorWidth/2, ECalLength/2);
    G4LogicalVolume* logicECal = new G4LogicalVolume(solidECal, ECal_mat, "ECal");
    new G4PVPlacement(0, G4ThreeVector(0, 0, absorberLength + ECalLength/2), logicECal, "ECal", logicWorld, false, 0, true);

  
    fScoringVolume1 = logicWorld;
    fScoringVolume2 = logicAbsorber;
    fScoringVolume3 = logicECal;
 
    return physWorld;
}

