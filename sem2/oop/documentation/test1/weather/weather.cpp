#include "weather.h"

Station::Station(std::string location, std::string name, std::string sensors) {
  this->location = location;
  this->name = name;
  this->sensors = sensors;
}

std::string Station::getLocation() { return this->location; }

std::string Station::getName() { return this->name; }

std::string Station::getSensors() { return this->sensors; }
