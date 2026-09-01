#include "ui.h"
#include <iostream>

UI::UI(Service &service) : service{service} { this->stardData(); }

void UI::stardData() {
  this->service.addAssignment("OOP_assignment", 120, "Not_Started");
  this->service.addAssignment("Science_Project", 240, "In_Progress");
  this->service.addAssignment("English_Essay", 180, "Completed");
  this->service.addAssignment("Lab_Report", 150, "Not_Started");
  this->service.addAssignment("Math_Homework", 40, "In_Progress");
}

void UI::printMenu() {
  std::cout << "1. Add assignment\n2. Show all assignments\n3. Show Sorted\n0. "
               "Exit\n";
}

void UI::addAssignment() {
  std::string desc, status;
  int duration;
  std::cout << "Desc: \n";
  std::cin >> desc;
  std::cout << "Duration: \n";
  std::cin >> duration;
  std::cout << "Status: \n";
std:
  std::cin >> status;
  this->service.addAssignment(desc, duration, status);
  std::cout << "Assignment added! \n";
}

void UI::getAll() {
  std::vector<Assignment> assignments = this->service.getAllAssignment();
  for (int i = 0; i < assignments.size(); i++)
    std::cout << assignments[i].getDesc() << " | "
              << assignments[i].getDuration() << " | "
              << assignments[i].getStatus() << "\n";
}

void UI::getAllSorted() {
  std::vector<Assignment> sorted = this->service.getAllGrouped();
  for (int i = 0; i < sorted.size(); i++)
    std::cout << sorted[i].getDesc() << " | " << sorted[i].getDuration()
              << " | " << sorted[i].getStatus() << "\n";
  int time = this->service.uncompleted();
  std::cout << time << "\n";
}

void UI::run() {
  std::cout << "Hello! \n";
  while (true) {
    this->printMenu();
    try {
      int option;
      std::cout << "> ";
      std::cin >> option;

      switch (option) {
      case 1:
        this->addAssignment();
        break;
      case 2:
        this->getAll();
        break;
      case 3:
        this->getAllSorted();
        break;
      case 0:
        std::cout << "Goodbye... \n";
        return;
      default:
        std::cout << "Invalid input \n";
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
    }
  }
}
