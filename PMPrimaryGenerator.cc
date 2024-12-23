#include "PMPrimaryGenerator.hh"
#include "G4AnalysisManager.hh"


PMPrimaryGenerator::PMPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    // Particle position
    G4double x = 0. * m;
    G4double y = 0. * m;
    G4double z = 10 * mm;

    G4ThreeVector pos(x, y, z);

    // Particle direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = -1.;

    G4ThreeVector mom(px, py, pz);
    

    

    // Particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

    //ener = RandEner();

    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(1.46*MeV);
    fParticleGun->SetParticleDefinition(particle);
}

PMPrimaryGenerator::~PMPrimaryGenerator()
{
    delete fParticleGun;
}

void PMPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // Create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);


}

/*G4double PMPrimaryGenerator::RandEner(){
    G4double ener = 0;
    ener = 0.1 + G4UniformRand()*4.9;
    return ener;
}*/