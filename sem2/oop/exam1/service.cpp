#include "service.h"
#include "assignment.h"
#include <algorithm>
#include <stdexcept>

Service::Service(Repo &repo) : repo{repo} {}

void Service::addAssignment(std::string desc, int duration,
                            std::string status) {
  std::vector<Assignment> assignments = this->repo.getAllAssignment();
  Assignment assignment = Assignment(desc, duration, status);
  for (int i = 0; i < assignments.size(); i++)
    if (assignments[i].getDesc() == assignment.getDesc())
      throw std::invalid_argument(
          "There exist another assingment with the same description\n");
  this->repo.addAssignment(assignment);
}

std::vector<Assignment> Service::getAllAssignment() {
  return this->repo.getAllAssignment();
}
// a b c d e f g h i j k l m n o p q r s t u v
std::vector<Assignment> Service::getAllGrouped() {
  std::vector<Assignment> assignments = this->repo.getAllAssignment();
  for (int i = 0; i < assignments.size(); i++)
    std::sort(assignments.begin(), assignments.end(),
              [](Assignment &a, Assignment &b) {
                return a.getDuration() > b.getDuration();
              });
  return assignments;
}

int Service::uncompleted() {
  int sum = 0;
  std::vector<Assignment> assignments = this->repo.getAllAssignment();
  for (int i = 0; i < assignments.size(); i++) {
    if (assignments[i].getStatus() == "Not_Started" ||
        assignments[i].getStatus() == "In_Progress")
      sum = sum + assignments[i].getDuration();
  }
  return sum;
}
