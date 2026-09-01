#pragma once
#include "car.h"
#include <string>
#include <vector>

class Repo {
private:
  std::vector<Car> cars;

public:
  void addCar(const Car &car);
  bool deleteCar(const std::string &model, int year);
  std::vector<Car> getAllCars() const;
};
