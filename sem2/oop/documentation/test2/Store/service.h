#include "domain.h"
#include <vector>

class Service {
private:
  std::vector<Appliance *> appliances;

public:
  void addApliance(Appliance *a);
  std::vector<Appliance *> getAllAppliance();
  std::vector<Appliance *>
  getAllWithConsumedElectricityLessThan(double maxElectricity);
  void writeToFile(std::string filename);
};
