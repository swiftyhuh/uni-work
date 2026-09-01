#include "car.h"

Car::Car(std::string manufacturer, std::string model, int year,
         std::string colour) {
  this->manufacturer = manufacturer;
  this->model = model;
  this->year = year;
  this->colour = colour;
}

std::string Car::getManufacturer() const { return this->manufacturer; }

std::string Car::getModel() const { return this->model; }

int Car::getYear() const { return this->year; }

std::string Car::getColour() const { return this->colour; }
