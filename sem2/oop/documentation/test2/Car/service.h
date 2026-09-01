#include "domain.h"
#include <vector>

class Service {
private:
  std::vector<Car *> cars;

public:
  void addCar(std::string bodyStyle, std::string engineType, int autonomy = 0);
  std::vector<Car *> getAllCars();
  std::vector<Car *> getCarsWithMaxPrice(double maxPrice);
  void writeToFile(std::string filename, double maxPrice);
  ~Service();
};
