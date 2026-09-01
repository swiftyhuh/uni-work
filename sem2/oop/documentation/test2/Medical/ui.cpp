#include "ui.h"

UI::UI(Person &person) : person(person) {}

void UI::run() {
  while (true) {
    printMenu();
    int option;
    std::cout << "> ";
    std::cin >> option;
    if (option == 1)
      this->addAnalysis();
    else if (option == 2)
      this->getAll();
    else if (option == 3)
      this->checkIll();
    else if (option == 4)
      this->write();
    else if (option == 0) {
      std::cout << "Goodbye... \n";
      break;
    } else
      std::cout << "Invalid option. \n";
  }
}

void UI::printMenu() {
  std::cout << "Welcome !\n1. Add analysis\n2. Show all analysis\n3. Check "
               "ill\n4. Write to file\n0. Exit\n";
}

void UI::addAnalysis() {
  std::string type, date;
  std::cout << "Type BMI/BP: ";
  std::cin >> type;
  std::cout << "Date: ";
  std::cin >> date;

  if (type == "BMI") {
    double value;
    std::cout << "Value: ";
    std::cin >> value;
    this->person.addAnalysis(new BMI(date, value));
  } else {
    int systolic, diastolic;
    std::cout << "Systolic: ";
    std::cin >> systolic;
    std::cout << "Diastolic: ";
    std::cin >> diastolic;
    this->person.addAnalysis(new BP(date, systolic, diastolic));
  }
}

void UI::getAll() {
  std::vector<MedicalAnalysis *> analyses = this->person.getAllAnalyses();
  for (auto a : analyses)
    std::cout << a->toString() << "\n";
}

void UI::checkIll() {
  int month;
  std::cout << "Month: ";
  std::cin >> month;

  if (this->person.isIll(month))
    std::cout << "The person is ill\n";
  else
    std::cout << "The person is not ill\n";
}

void UI::write() {
  std::string filename, date1, date2;
  std::cout << "Filename: ";
  std::cin >> filename;
  std::cout << "Start date: ";
  std::cin >> date1;
  std::cout << "End date: ";
  std::cin >> date2;

  this->person.writeToFile(filename, date1, date2);
}
