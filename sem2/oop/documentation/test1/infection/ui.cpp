#include "ui.h"
#include <iostream>

UI::UI(Service &service) : service{service} { this->startData(); }

void UI::startData() {
  this->service.addPatient("Jessica", 19, false, 2);
  this->service.addPatient("Bella", 30, false, 1);
  this->service.addPatient("Scott", 85, false, 2);
  this->service.addPatient("Anna", 37, true, 8);
  this->service.addPatient("Andrew", 62, false, 3);
}

void UI::printMenu() {
  std::cout << "1. Add a patient. \n2. Show all patients. \n3. Update "
               "infection status \n0. Exit \n";
}

void UI::addPatient() {
  std::string name;
  int age, room;
  bool infected;

  std::cout << "Name: ";
  std::cin >> name;
  std::cout << "Age: ";
  std::cin >> age;
  std::cout << "Infected: ";
  std::cin >> infected;
  std::cout << "Room: ";
  std::cin >> room;

  this->service.addPatient(name, age, infected, room);
  std::cout << "Patient added.\n";
}

void UI::getAllPateints() {
  std::vector<Patient> patients = this->service.getAllPatient();
  for (int i = 0; i < patients.size(); i++)
    std::cout << patients[i].getName() << " | " << patients[i].getAge() << " | "
              << patients[i].getInfected() << " | " << patients[i].getRoom()
              << "\n";
}

void UI::updateInfection() {
  int checkage;
  std::cout << "Age: ";
  std::cin >> checkage;
  std::vector<Patient> infectedPatients = this->service.getInfected(checkage);
  for (int i = 0; i < infectedPatients.size(); i++)
    std::cout << infectedPatients[i].getName() << " | "
              << infectedPatients[i].getAge() << " | "
              << infectedPatients[i].getInfected() << " | "
              << infectedPatients[i].getRoom() << "\n";
}

void UI::run() {
  std::cout << "Welcome\n";
  while (true) {
    this->printMenu();
    try {
      int option;
      std::cout << "> ";
      std::cin >> option;
      switch (option) {
      case 1:
        this->addPatient();
        break;
      case 2:
        this->getAllPateints();
        break;
      case 3:
        this->updateInfection();
        break;
      case 0:
        std::cout << "Goodbye...\n";
        return;
      default:
        std::cout << "Invalid input. \n";
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
    }
  }
}
