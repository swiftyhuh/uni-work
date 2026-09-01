#include "service.h"
#include <algorithm>
#include <fstream>

void Service::addCar(std::string bodyStyle, std::string engineType,
                     int autonomy) {
  if (engineType == "Electric")
    this->cars.push_back(new Car(bodyStyle, new ElectricEngine(autonomy)));
  else
    this->cars.push_back(new Car(bodyStyle, new TurboEngine()));
}

std::vector<Car *> Service::getAllCars() { return this->cars; }

std::vector<Car *> Service::getCarsWithMaxPrice(double maxPrice) {
  std::vector<Car *> result;
  for (auto c : this->cars)
    if (c->computePrice() <= maxPrice)
      result.push_back(c);

  std::sort(result.begin(), result.end(), [](Car *a, Car *b) {
    return a->computePrice() < b->computePrice();
  });
  return result;
}

void Service::writeToFile(std::string filename, double maxPrice) {
  std::ofstream fout(filename);
  std::vector<Car *> result = this->getCarsWithMaxPrice(maxPrice);
  for (auto c : result)
    fout << c->toString() << "\n";
}

Service::~Service() {
  for (auto c : this->cars)
    delete c;
}
