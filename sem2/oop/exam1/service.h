#pragma once
#include "repo.h"

class Service {
private:
  Repo &repo;

public:
  Service(Repo &repo);
  // get every assignments, go trough them, check if there exist any assigment
  // with the same description, if yes then it throw an error, if not, it just
  // add it to the repo
  void addAssignment(std::string desc, int duration, std::string status);
  std::vector<Assignment> getAllAssignment();

  // goes trough all of assignments, sorted them by duration time
  std::vector<Assignment> getAllGrouped();
  // the second part of sorted function, that goes trough all of the assignments
  // and compute the sum of the assignment that are not finished.
  //
  int uncompleted();
};
