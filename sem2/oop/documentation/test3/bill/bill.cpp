#include "bill.h"

Bill::Bill(std::string compName, std::string serialNumber, float sum,
           bool isPaid) {
  this->compName = compName;
  this->serialNumber = serialNumber;
  this->sum = sum;
  this->isPaid = isPaid;
}

std::string Bill::getCompName() { return this->compName; }

std::string Bill::getSerialNumber() { return this->serialNumber; }

float Bill::getSum() { return this->sum; }

bool Bill::getPaid() { return this->isPaid; }

std::string Bill::toString() {
  return this->compName + ";" + this->serialNumber + ";" +
         std::to_string(this->sum) + ";" + std::to_string(this->isPaid);
}
