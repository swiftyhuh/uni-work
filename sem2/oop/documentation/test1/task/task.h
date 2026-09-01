#pragma once
#include <string>

class Task {
private:
  // task desciption, task duration and task priority
  std::string descripton;
  int duration, priority;

public:
  // constructor for task
  Task(std::string descripton = "", int duration = 0, int priority = 0);
  // return the task Description
  std::string getDescription();
  // return task duration
  int getDuration();
  // return task priority
  int getPriority();
};
