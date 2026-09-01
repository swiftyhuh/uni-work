#pragma once
#include "assignment.h"
#include <vector>

class Repo {
private:
  std::vector<Assignment> assignments;

public:
  void addAssignment(Assignment assig);
  std::vector<Assignment> &getAllAssignment();
};
