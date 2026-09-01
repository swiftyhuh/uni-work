#include "repo.h"
#include "weather.h"

void Repo::addStation(Station station) { this->stations.push_back(station); }

std::vector<Station> &Repo::getAllStations() { return this->stations; }
