#include "repo.h"
#include "infection.h"

void Repo::addPatient(Patient pat) { this->pats.push_back(pat); }

std::vector<Patient> &Repo::getAllPatients() { return this->pats; }
