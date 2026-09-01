#pragma once
#include <string>

class Car {
private:
  std::string manufacturer, model;
  int year;
  std::string colour;

public:
  Car(std::string manufacturer = "", std::string model = "", int year = 2026,
      std::string colour = "");
  std::string getManufacturer() const;
  std::string getModel() const;
  int getYear() const;
  std::string getColour() const;
};
