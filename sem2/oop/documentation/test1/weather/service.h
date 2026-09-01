#pragma once
#include "repo.h"

class Service {
private:
  Repo &repo;

public:
  Service(Repo &repo);
  void addStation(std::string location, std::string name, std::string sensors);
  std::vector<Station> getAllStations();
  std::vector<std::string> getSameSensor(std::string sensor);
};
