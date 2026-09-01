#include "domain.h"
#include <string>

std::string Appliance::getId() { return this->id; }

Refrigerator::Refrigerator(std::string id, std::string electricityUsageClass,
                           bool hasFreezer) {
  this->id = id;
  this->electricityUsageClass = electricityUsageClass;
  this->hasFreezer = hasFreezer;
}

double Refrigerator::consumedElectricity() {
  if (this->electricityUsageClass == "A" && this->hasFreezer == true)
    return 30 * 3 + 20;
  else if (this->electricityUsageClass == "A" && this->hasFreezer == false)
    return 30 * 3;
  else if (this->electricityUsageClass == "A++" && this->hasFreezer == true)
    return 30 * 2 + 20;
  else
    return 30 * 2;
}

std::string Refrigerator::toString() {
  return "Refrigerator | Id: " + this->id +
         " | Electricity class: " + this->electricityUsageClass +
         " | Has freezer: " + std::to_string(hasFreezer);
}

DishWasher::DishWasher(std::string id, double consumedElectricityForOneHour) {
  this->id = id;
  this->consumedElectricityForOneHour = consumedElectricityForOneHour;
}

double DishWasher::consumedElectricity() {
  return this->consumedElectricityForOneHour * 20;
}

std::string DishWasher::toString() {
  return "DishWasher | Id: " + this->id +
         " | One hour: " + std::to_string(this->consumedElectricityForOneHour) +
         " | Monthly: " + std::to_string(this->consumedElectricity());
}
