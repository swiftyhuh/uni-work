#pragma once
#include <string>
class Assignment {
private:
  std::string desc, status;
  int duration;

public:
  Assignment(std::string desc = "", int duration = 0, std::string status = "");
  std::string getDesc();
  std::string getStatus();
  int getDuration();
};
