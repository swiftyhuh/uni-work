#include "service.h"
#include <algorithm>
#include <stdexcept>

Service::Service(Repo &repo) : repo{repo} {}

void Service::addCar(std::string manufacter, std::string model, int year,
                     std::string colour) {
  Car car = Car(manufacter, model, year, colour);
  std::vector<Car> cars = this->repo.getAllCars();
  for (int i = 0; i < cars.size(); i++)
    if (cars[i].getModel() == car.getModel() &&
        cars[i].getYear() == car.getYear())
      throw std::invalid_argument("The car already exists.");
  this->repo.addCar(car);
}

void Service::deleteCar(const std::string &model, int year) {
  bool deleted = this->repo.deleteCar(model, year);
  if (!deleted)
    throw std::invalid_argument("The car does not exist.");
}

std::vector<Car> Service::getVintageSorted(int currentYear) {
  std::vector<Car> cars = this->repo.getAllCars();
  std::vector<Car> vintage;
  for (int i = 0; i < cars.size(); i++)
    if (cars[i].getYear() < currentYear - 45)
      vintage.push_back(cars[i]);
  std::sort(vintage.begin(), vintage.end(), [](const Car &a, const Car &b) {
    return a.getColour() < b.getColour();
  });
  return vintage;
}

std::vector<Car> Service::getAllSorted() {
  std::vector<Car> cars = this->repo.getAllCars();
  std::sort(cars.begin(), cars.end(), [](const Car &a, const Car &b) {
    if (a.getManufacturer() == b.getManufacturer())
      return a.getModel() < b.getModel();
    return a.getManufacturer() < b.getManufacturer();
  });
  return cars;
}
