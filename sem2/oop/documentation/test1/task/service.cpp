#include "service.h"
#include <algorithm>
#include <stdexcept>
Service::Service(Repo &repo) : repo{repo} {}

void Service::addTask(std::string description, int duration, int priority) {
  Task task = Task(description, duration, priority);
  std::vector<Task> tasks = this->repo.getAllTasks();
  for (int i = 0; i < tasks.size(); i++)
    if (tasks[i].getDescription() == task.getDescription())
      throw std::invalid_argument("Task already exist!\n");
  this->repo.addTask(task);
}

std::vector<Task> Service::getAllTasks() { return this->repo.getAllTasks(); }

std::vector<Task> Service::getSorted(int p) {
  std::vector<Task> tasks = this->repo.getAllTasks();
  std::vector<Task> sorted;
  for (int i = 0; i < tasks.size(); i++)
    if (tasks[i].getPriority() < p) {
      sorted.push_back(tasks[i]);
    }

  std::sort(sorted.begin(), sorted.end(),
            [](Task &a, Task &b) { return a.getDuration() > b.getDuration(); });
  return sorted;
}
