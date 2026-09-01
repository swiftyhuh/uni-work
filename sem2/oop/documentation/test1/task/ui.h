#pragma once
#include "service.h"

class UI {
private:
  Service &service;

public:
  UI(Service &service);
  void run();
  void printMenu();
  void startData();
  void addTask();
  void getTasks();
  void getSorted();
};
