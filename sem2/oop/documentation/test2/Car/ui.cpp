#include "ui.h"
#include <iostream>

UI::UI(Service &service) : service(service) {}

void UI::printMenu() {
  std::cout << "1. Add car\n";
  std::cout << "2. Show all cars\n";
  std::cout << "3. Write to file\n";
  std::cout << "0. Exit\n";
}

void UI::addCar() {
  std::string bodyStyle, engineType;
  std::cout << "Body style (Sedan/Convertible): ";
  std::cin >> bodyStyle;
  std::cout << "Engine type (Electric/Turbo): ";
  std::cin >> engineType;

  if (engineType == "Electric") {
    int autonomy;
    std::cout << "Autonomy: ";
    std::cin >> autonomy;
    this->service.addCar(bodyStyle, engineType, autonomy);
  } else {
    this->service.addCar(bodyStyle, engineType);
  }

  std::vector<Car *> cars = this->service.getAllCars();
  std::cout << "Price: " << cars[cars.size() - 1]->computePrice() << "\n";
}

void UI::getAllCars() {
  std::vector<Car *> cars = this->service.getAllCars();

  for (auto c : cars)
    std::cout << c->toString() << "\n";
}

void UI::writeToFile() {
  std::string filename;
  double maxPrice;

  std::cout << "Filename: ";
  std::cin >> filename;
  std::cout << "Max price: ";
  std::cin >> maxPrice;

  this->service.writeToFile(filename, maxPrice);
}

void UI::run() {
  while (true) {
    this->printMenu();
    int option;
    std::cout << "> ";
    std::cin >> option;

    if (option == 1)
      this->addCar();
    else if (option == 2)
      this->getAllCars();
    else if (option == 3)
      this->writeToFile();
    else if (option == 0)
      break;
    else
      std::cout << "Invalid option.\n";
  }
}
