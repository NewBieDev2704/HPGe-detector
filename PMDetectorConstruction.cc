#include "PMDetectorConstruction.hh"

PMDetectorConstruction::PMDetectorConstruction()
{
}

PMDetectorConstruction::~PMDetectorConstruction()
{
}

G4VPhysicalVolume *PMDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;

    G4NistManager *nist  = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *Pb = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *Cu = nist->FindOrBuildMaterial("G4_Cu");
    G4Material *Al = nist->FindOrBuildMaterial("G4_Al");
    G4Material *Ge = nist->FindOrBuildMaterial("G4_Ge");
    //G4Material *detMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m;
    G4double zWorld = 1. * m;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    
    G4Box *solidLead = new G4Box("solidLead", 200*mm, 200*mm, 285*mm);
    G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, Pb, "logicLead");
    G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0., 0., 0), logicLead, "physLead", logicWorld, false, checkOverlaps);

    G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
    leadVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(leadVisAtt);

    G4Box *h1 = new G4Box("air1", 100*mm, 100*mm, 225*mm);
    G4LogicalVolume *logicAir1 = new G4LogicalVolume(h1, worldMat, "logicalHol1");
    G4VPhysicalVolume *physh1 = new G4PVPlacement(0, G4ThreeVector(0, 0, -60*mm), logicAir1, "physh1", logicLead, false, checkOverlaps);

    G4Box *Copper = new G4Box("copper", 100*mm, 100*mm, 225*mm);
    G4LogicalVolume *logicCu = new G4LogicalVolume(Copper, Cu, "logicalCu");
    G4VPhysicalVolume *physCu = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCu, "physCu", logicAir1, false, checkOverlaps);

    G4VisAttributes *cuVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    cuVisAtt->SetForceSolid(true);
    logicCu->SetVisAttributes(cuVisAtt);

    G4Box *h2 = new G4Box("air2", 50*mm, 50*mm, 200*mm);
    G4LogicalVolume *logicAir2 = new G4LogicalVolume(h2, worldMat, "logicalHol2");
    G4VPhysicalVolume *physh2 = new G4PVPlacement(0, G4ThreeVector(0, 0, -25*mm), logicAir2, "physh2", logicCu, false, checkOverlaps);

    G4Tubs *Alum = new G4Tubs("al", 0*mm, 41.5*mm, 30.65*mm, 0*degree, 360*degree);
    G4LogicalVolume *logicAl = new G4LogicalVolume(Alum, Al, "logicalAl");
    G4VPhysicalVolume *physAl = new G4PVPlacement(0, G4ThreeVector(0, 0, +64.5*mm), logicAl, "physAl", logicAir2, false, checkOverlaps);
    
    G4Tubs *h3 = new G4Tubs("h3", 0*mm, 40.5*mm, 29.65*mm, 0*degree, 360*degree);
    G4LogicalVolume *logicAir3 = new G4LogicalVolume(h3, worldMat, "logicalHol3");
    G4VPhysicalVolume *physh3 = new G4PVPlacement(0, G4ThreeVector(0, 0, 0*mm), logicAir3, "physh3", logicAl, false, checkOverlaps);


    G4Tubs *solidDetector = new G4Tubs("solidDetector", 0*mm, 33.15*mm, 25.65*mm, 0*degree, 360*degree);
    logicDetector = new G4LogicalVolume(solidDetector, Ge, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0. , 0 * cm), logicDetector, "physDetector", logicAir3, false, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    /*G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *Pb = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *Cu = nist->FindOrBuildMaterial("G4_Cu");
    G4Material *Al = nist->FindOrBuildMaterial("G4_Al");
    G4Material *Ge = nist->FindOrBuildMaterial("G4_Ge");

    G4Box *solidWorld = new G4Box("SolidWorld", 1.*m, 1.*m, 1.*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

    G4Box *solidLead = new G4Box("SolidLead", 200*mm, 200*mm, 285*mm);
    G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, Pb, "logicalLead");
    G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicLead, "physLead", logicWorld, 0, true);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    detVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(detVisAtt);*/

    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDetector *sensDet = new PMSensitiveDetector("SensitveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}