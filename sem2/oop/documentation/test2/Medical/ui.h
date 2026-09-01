#include "domain.h"

class UI {
private:
  Person &person;

public:
  UI(Person &person);
  void run();
  void printMenu();
  void addAnalysis();
  void getAll();
  void checkIll();
  void write();
};
