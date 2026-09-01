#include "domain.h"

Engine::Engine(double basePrice) { this->basePrice = basePrice; }

double Engine::getPrice() { return this->basePrice; }

Car::Car(std::string bodyStyle, Engine *engine) {
  this->bodyStyle = bodyStyle;
  this->engine = engine;
}

double Car::computePrice() {
  if (this->bodyStyle == "Sedan")
    return 8000 + this->engine->getPrice();
  return 9000 + this->engine->getPrice();
}

std::string Car::toString() {
  return "Car | Body style: " + this->bodyStyle +
         " | Engine: " + this->engine->toString() +
         " | Price: " + std::to_string(this->computePrice());
}

ElectricEngine::ElectricEngine(int autonomy) : Engine(3000) {
  this->autonomy = autonomy;
}

double ElectricEngine::getPrice() {
  return this->basePrice + this->autonomy * 0.01;
}

std::string ElectricEngine::toString() {
  return "ElectricEngine | Autonomy : " + std::to_string(this->autonomy);
}

TurboEngine::TurboEngine() : Engine(3000) {}

double TurboEngine::getPrice() { return 8000 + this->basePrice + 100; }

std::string TurboEngine::toString() { return "Turbo engine"; }
