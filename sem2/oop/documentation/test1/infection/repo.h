#pragma once
#include "infection.h"
#include <string>
#include <vector>

class Repo {
private:
  std::vector<Patient> pats;

public:
  void addPatient(Patient pat);
  std::vector<Patient> &getAllPatients();
};
