#pragma once
#include "repo.h"
#include <vector>

class Service {
private:
  // links service with repo
  Repo &repo;

public:
  // constructor for service with a Repo
  Service(Repo &repo);
  // the logic behind addtask, it check if the task already exist if not it add
  // it
  void addTask(std::string description, int duration, int priority);
  // return the repo vectir with every task
  std::vector<Task> getAllTasks();
  // return the sorted vector based on capacity and duration
  std::vector<Task> getSorted(int p);
};
