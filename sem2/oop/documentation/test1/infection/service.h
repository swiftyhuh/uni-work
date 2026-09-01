#pragma once
#include "repo.h"
#include <vector>

class Service {
private:
  Repo &repo;

public:
  Service(Repo &repo);
  void addPatient(std::string name, int age, bool infected, int room);
  std::vector<Patient> getAllPatient();
  std::vector<Patient> getInfected(int checkage);
};
