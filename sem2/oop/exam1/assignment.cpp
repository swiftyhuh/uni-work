#include "assignment.h"
#include <string>

Assignment::Assignment(std::string desc, int duration, std::string status) {
  this->desc = desc;
  this->duration = duration;
  this->status = status;
}

std::string Assignment::getDesc() { return this->desc; }

int Assignment::getDuration() { return this->duration; }

std::string Assignment::getStatus() { return this->status; }
