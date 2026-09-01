#pragma once
#include "weather.h"
#include <string>
#include <vector>

class Repo {
private:
  std::vector<Station> stations;

public:
  void addStation(Station station);
  std::vector<Station> &getAllStations();
};
