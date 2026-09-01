#include "ui.h"
#include <iostream>
UI::UI(Service &service) : service{service} { this->startData(); }

void UI::startData() {
  this->service.addTask("Solve_OOP_assignment", 120, 1);
  this->service.addTask("Respond_to_emails", 45, 2);
  this->service.addTask("Eat_sushi", 30, 3);
  this->service.addTask("Visit_parent", 240, 1);
  this->service.addTask("Buy_a_jacket", 120, 2);
}

void UI::printMenu() {
  std::cout
      << "1. Add a task. \n2.Show all tasks.\n3.Show all task sorted.\n0. Exit";
}

void UI::addTask() {
  std::string description;
  int priority, duration;

  std::cout << "Description: ";
  std::cin >> description;
  std::cout << "Duration: ";
  std::cin >> duration;
  std::cout << "Priority: ";
  std::cin >> priority;
  this->service.addTask(description, duration, priority);
  std::cout << "Task added.\n";
}

void UI::getTasks() {
  std::vector<Task> tasks = this->service.getAllTasks();
  for (int i = 0; i < tasks.size(); i++)
    std::cout << tasks[i].getDescription() << " | " << tasks[i].getDuration()
              << " | " << tasks[i].getPriority() << "\n";
}

void UI::getSorted() {
  int p;
  std::cout << "Priority: ";
  std::cin >> p;
  std::vector<Task> sorted = this->service.getSorted(p);
  for (int i = 0; i < sorted.size(); i++)
    std::cout << sorted[i].getDescription() << " | " << sorted[i].getDuration()
              << " | " << sorted[i].getPriority() << "\n";
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
        this->addTask();
        break;
      case 2:
        this->getTasks();
        break;
      case 3:
        this->getSorted();
        break;
      case 0:
        std::cout << "goodbye...\n";
        return;
      default:
        std::cout << "Invalid input\n";
      }
    } catch (const std::exception &e) {
      std::cout << e.what() << "\n";
    }
  }
}
