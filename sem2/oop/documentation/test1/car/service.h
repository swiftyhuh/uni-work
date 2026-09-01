#pragma once
#include "repo.h"
#include <string>
#include <vector>

class Service {
private:
  Repo &repo;

public:
  Service(Repo &repo);
  void addCar(std::string manufacter, std::string model, int year,
              std::string colour);
  void deleteCar(const std::string &model, int year);
  std::vector<Car> getAllSorted();
  std::vector<Car> getVintageSorted(int currentYear);
};
