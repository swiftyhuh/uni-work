#include "service.h"

class UI {
private:
  Service &service;

public:
  UI(Service &service);
  void run();
  void printMenu();
  void addCar();
  void getAllCars();
  void writeToFile();
};
