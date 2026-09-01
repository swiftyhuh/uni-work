#include "repo.h"
#include "assignment.h"

void Repo::addAssignment(Assignment assig) {
  this->assignments.push_back(assig);
}

std::vector<Assignment> &Repo::getAllAssignment() { return this->assignments; }
