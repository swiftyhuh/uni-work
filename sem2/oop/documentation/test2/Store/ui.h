#include "domain.h"

class UI {
private:
  std::vector<Appliance *> appliances;

public:
  void run();
  void printMenu();
  void addAppliance();
}
