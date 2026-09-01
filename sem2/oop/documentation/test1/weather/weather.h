#pragma once
#include <string>
#include <vector>
class Station {
private:
  std::string location, name, sensors;

public:
  Station(std::string location = "", std::string name = "",
          std::string sensors = "");
  std::string getLocation();
  std::string getName();
  std::string getSensors();
};
