#include "task.h"

Task::Task(std::string descripton, int duration, int priority) {
  this->descripton = descripton;
  this->duration = duration;
  this->priority = priority;
}

std::string Task::getDescription() { return this->descripton; }

int Task::getDuration() { return this->duration; }

int Task::getPriority() { return this->priority; }
