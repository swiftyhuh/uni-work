#include "ui.h"
#include <iostream>
#include <string>

UI::UI(Service &service) : service{service} { this->startData(); }

void UI::startData() {
  this->service.addCar("Fiat", "Bravo", 2007, "red");
  this->service.addCar("Fiat", "Idea", 2003, "black");
  this->service.addCar("Audi", "A5", 2007, "blue");
  this->service.addCar("BMW", "Coupe", 2013, "pink");
  this->service.addCar("Ford", "Fiesta", 1976, "yellow");
}

void UI::printMenu() {
  std::cout << "1. Add a car. \n";
  std::cout << "2. Delete a car. \n";
  std::cout << "3. Show all cars. \n";
  std::cout << "4. Show vintage cars. \n";
  std::cout << "0. Exit \n";
}

void UI::addCar() {
  std::string man, model, colour, yearStr;
  int year;
  std::cout << "Manufacturer: ";
  std::getline(std::cin, man);
  std::cout << "Model: ";
  std::getline(std::cin, model);
  std::cout << "Year: ";
  std::getline(std::cin, yearStr);
  year = stoi(yearStr);
  std::cout << "Colour: ";
  std::getline(std::cin, colour);
  this->service.addCar(man, model, year, colour);
  std::cout << "Car was added successfully. \n";
}

void UI::deleteCar() {
  std::string model, yearStr;
  int year;
  std::cout << "Model: ";
  std::getline(std::cin, model);
  std::cout << "Year: ";
  std::getline(std::cin, yearStr);
  year = std::stoi(yearStr);
  this->service.deleteCar(model, year);
  std::cout << "Car removed successfully. \n";
}

void UI::showAll() {
  std::vector<Car> cars = this->service.getAllSorted();
  for (int i = 0; i < cars.size(); i++)
    std::cout << cars[i].getManufacturer() << " | " << cars[i].getModel()
              << " | " << cars[i].getYear() << " | " << cars[i].getColour()
              << "\n";
}

void UI::showVintage() {
  std::string yearStr;
  int year;
  std::cout << "Current year: ";
  std::getline(std::cin, yearStr);
  year = std::stoi(yearStr);
  std::vector<Car> vintage = this->service.getVintageSorted(year);
  for (int i = 0; i < vintage.size(); i++)
    std::cout << vintage[i].getManufacturer() << " | " << vintage[i].getModel()
              << " | " << vintage[i].getYear() << " | "
              << vintage[i].getColour() << "\n";
}

void UI::run() {
  std::cout << "Welcome\n";
  while (true) {
    this->printMenu();
    try {
      std::string optionStr;
      int option;
      std::cout << "> ";
      std::getline(std::cin, optionStr);
      option = std::stoi(optionStr);
      switch (option) {
      case 1:
        this->addCar();
        break;
      case 2:
        this->deleteCar();
        break;
      case 3:
        this->showAll();
        break;
      case 4:
        this->showVintage();
        break;
      case 0:
        std::cout << "Goodbye... \n";
        return;
      default:
        std::cout << "Invalid input. \n";
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
    }
  }
}
