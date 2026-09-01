#include "domain.h"
#include <vector>

class UI {
private:
  std::vector<Building *> buildings;

public:
  UI() = default;
  void run();
  void printMenu();
  void addBuilding();
  void getAllBuildings();
  void getAllToBeRestored();
  void getAllToBeDemolished();
  void addInitialBuildings();
};
