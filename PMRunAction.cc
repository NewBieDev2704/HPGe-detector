#include "PMRunAction.hh"

PMRunAction::PMRunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateH1("E", "HPGe effeciency", 1000, 0.01 * MeV, 1.51 * MeV);

    analysisManager->CreateNtuple("Photons", "Photons");
    analysisManager->CreateNtupleIColumn("iEvent");
    //analysisManager->CreateNtupleDColumn("Energy");
    analysisManager->FinishNtuple(0);
}

PMRunAction::~PMRunAction()
{
}

void PMRunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");
}

void PMRunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();

    analysisManager->CloseFile();

    G4int runID = run->GetRunID();

    G4cout << "Finishing run " << runID << G4endl;
}