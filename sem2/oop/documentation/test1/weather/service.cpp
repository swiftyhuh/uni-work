#include "service.h"
#include <stdexcept>

Service::Service(Repo &repo) : repo{repo} {}

void Service::addStation(std::string location, std::string name,
                         std::string sensors) {
  Station station = Station(location, name, sensors);
  std::vector<Station> stations = this->repo.getAllStations();
  for (int i = 0; i < stations.size(); i++)
    if (stations[i].getName() == station.getName() &&
        stations[i].getLocation() == station.getLocation())
      throw std::invalid_argument("The station already exists.\n");
  this->repo.addStation(station);
}

std::vector<Station> Service::getAllStations() {
  return this->repo.getAllStations();
}

std::string Station::getSensors() { return this->sensors; }
