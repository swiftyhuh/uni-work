#include "repo.h"

void Repo::addCar(const Car &car) { this->cars.push_back(car); }

std::vector<Car> Repo::getAllCars() const { return this->cars; }
