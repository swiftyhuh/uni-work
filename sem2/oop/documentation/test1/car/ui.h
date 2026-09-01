#pragma once
#include "service.h"

class UI {
private:
  Service &service;

public:
  UI(Service &service);
  void run();
  void printMenu();
  void addCar();
  void deleteCar();
  void showAll();
  void showVintage();
  void startData();
};
