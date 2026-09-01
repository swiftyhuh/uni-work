#include "infection.h"

Patient::Patient(std::string name, int age, bool infected, int room) {
  this->name = name;
  this->age = age;
  this->infected = infected;
  this->room = room;
}

std::string Patient::getName() const { return this->name; }

int Patient::getAge() const { return this->age; }

bool Patient::getInfected() const { return this->infected; }

int Patient::getRoom() const { return this->room; }

void Patient::setInfected(bool infected) { this->infected = infected; }
