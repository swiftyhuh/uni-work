#include "repo.h"
#include "task.h"

void Repo::addTask(Task task) { this->tasks.push_back(task); }

std::vector<Task> &Repo::getAllTasks() { return this->tasks; }
