#include <iostream>

class Appliance {
protected:
  std::string id;

public:
  std::string getId();
  virtual double consumedElectricity() = 0;
  virtual std::string toString() = 0;
  virtual ~Appliance() = default;
};

class Refrigerator : public Appliance {
private:
  std::string electricityUsageClass;
  bool hasFreezer;

public:
  Refrigerator(std::string id, std::string electricityUsageClass,
               bool hasFreezer);
  double consumedElectricity() override;
  std::string toString() override;
};

class DishWasher : public Appliance {
private:
  double consumedElectricityForOneHour;

public:
  DishWasher(std::string id, double consumedElectricityForOneHour);
  double consumedElectricity() override;
  std::string toString() override;
};
