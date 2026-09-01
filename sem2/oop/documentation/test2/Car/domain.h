#include <iostream>
#include <string>

class Engine {
protected:
  double basePrice;

public:
  Engine(double basePrice);
  virtual double getPrice() = 0;
  virtual std::string toString() = 0;
  virtual ~Engine() = default;
};

class Car {
protected:
  std::string bodyStyle;
  Engine *engine;

public:
  Car(std::string bodyStyle, Engine *engine);
  std::string toString();
  double computePrice();
  ~Car();
};

class ElectricEngine : public Engine {
private:
  int autonomy;

public:
  ElectricEngine(int autonomy);
  double getPrice() override;
  std::string toString() override;
};

class TurboEngine : public Engine {
public:
  TurboEngine();
  double getPrice() override;
  std::string toString() override;
};
