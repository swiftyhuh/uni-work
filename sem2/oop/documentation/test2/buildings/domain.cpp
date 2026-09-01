#include "domain.h"

std::string Building::getAddress() { return this->address; }

int Building::getYear() { return this->constructionYear; }

Block::Block(std::string address, int constructionYear, int nrApartaments,
             int nrApsOccupied) {
  this->address = address;
  this->constructionYear = constructionYear;
  this->nrApartaments = nrApartaments;
  this->nrApsOccupied = nrApsOccupied;
}

bool Block::mustBeRestored() {
  double percentage = (double)this->nrApsOccupied / this->nrApartaments * 100;
  if (2026 - this->constructionYear > 40 && percentage > 80)
    return true;
  return false;
}

bool Block::canBeDemolished() {
  double percentage = (double)this->nrApsOccupied / this->nrApartaments * 100;
  if (percentage < 5)
    return true;
  return false;
}

std::string Block::toString() {
  return "Block | Address: " + this->address +
         " | Year: " + std::to_string(this->constructionYear) +
         " | Apartaments: " + std::to_string(this->nrApartaments) +
         " | Occupied: " + std::to_string(this->nrApsOccupied);
}

House::House(std::string address, int constructionYear, std::string type,
             bool historical) {
  this->address = address;
  this->constructionYear = constructionYear;
  this->type = type;
  this->historical = historical;
}

bool House::mustBeRestored() {
  if (2026 - this->constructionYear > 100)
    return true;
  return false;
}

bool House::canBeDemolished() {
  if (this->historical == false)
    return true;
  return false;
}

std::string House::toString() {
  return "House | Address: " + this->address +
         " Year: " + std::to_string(constructionYear) + " Type: " + this->type +
         " Historical: " + std::to_string(historical);
}
