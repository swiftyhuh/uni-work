#include "ui.h"
#include <algorithm>
#include <fstream>
#include <iostream>

void UI::run() {
  while (true) {
    printMenu();
    int option;
    std::cout << "> ";
    std::cin >> option;
    if (option == 1)
      this->addBuilding();
    else if (option == 2)
      this->getAllBuildings();
    else if (option == 3)
      this->getAllToBeRestored();
    else if (option == 4)
      this->getAllToBeDemolished();
    else if (option == 0) {
      std::cout << "Goodbye... \n";
      break;
    } else
      std::cout << "Invalid option.\n";
  }
}

void UI::printMenu() {
  std::cout
      << "Welcome !\n1. Add building\n2. Get all buildings\n3. Export all "
         "buildings to be restored\n4. Export all buildings to be "
         "demolished\n0. Exit\n";
}

void UI::addBuilding() {
  std::string address, type;
  int constructionYear;
  std::cout << "Type (House/Block): ";
  std::cin >> type;
  if (type == "House") {
    std::string htype;
    bool historical;
    std::cout << "Address: ";
    std::cin >> address;
    std::cout << "Construction Year: ";
    std::cin >> constructionYear;
    std::cout << "House type(One story, two stories, duplex): ";
    std::cin >> htype;
    std::cout << "Historical house(1/0): ";
    std::cin >> historical;
    bool found = false;
    for (auto b : buildings)
      if (b->getAddress() == address) {
        found = true;
        break;
      }
    if (found)
      std::cout << "Address already exist!\n";
    else
      buildings.push_back(
          new House(address, constructionYear, htype, historical));

  } else if (type == "Block") {
    int nrApartaments, nrApsOccupied;
    std::cout << "Address: ";
    std::cin >> address;
    std::cout << "Construction Year: ";
    std::cin >> constructionYear;
    std::cout << "Number of Apartaments: ";
    std::cin >> nrApartaments;
    std::cout << "Apartaments occupied: ";
    std::cin >> nrApsOccupied;
    bool found = false;
    for (auto b : buildings)
      if (b->getAddress() == address) {
        found = true;
        break;
      }
    if (found)
      std::cout << "Address already exists!\n";
    else
      buildings.push_back(
          new Block(address, constructionYear, nrApartaments, nrApsOccupied));
  } else
    std::cout << "Invalid type\n";
}

void UI::getAllBuildings() {
  std::vector<Building *> sorted = buildings;
  std::sort(sorted.begin(), sorted.end(), [](Building *a, Building *b) {
    return a->getYear() > b->getYear();
  });
  for (auto s : sorted)
    std::cout << s->toString() << "\n";
}

void UI::getAllToBeRestored() {
  std::string filename;
  std::cout << "Filename: ";
  std::cin >> filename;
  std::ofstream fout(filename);

  for (auto b : this->buildings)
    if (b->mustBeRestored())
      fout << b->toString() << "\n";
}

void UI::getAllToBeDemolished() {
  std::string filename;
  std::cout << "Filename: ";
  std::cin >> filename;
  std::ofstream fout(filename);

  for (auto b : this->buildings)
    if (b->canBeDemolished())
      fout << b->toString() << "\n";
}

void UI::addInitialBuildings() {
  this->buildings.push_back(new House("StradaA", 1900, "duplex", true));
  this->buildings.push_back(new Block("StradaB", 1960, 20, 1));
}
