#pragma once
#include "task.h"
#include <vector>

class Repo {
private:
  // create the vector that store every task
  std::vector<Task> tasks;

public:
  // add to the vector the task
  void addTask(Task task);
  // return everything that is in the vector
  std::vector<Task> &getAllTasks();
};
