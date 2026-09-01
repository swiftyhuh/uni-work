#include "ui.h"

int main() {
  Service service;
  service.addCar("Sedan", "Electric", 500);
  service.addCar("Convertible", "Turbo");
  service.addCar("Sedan", "Turbo");

  UI ui(service);
  ui.run();

  return 0;
}
