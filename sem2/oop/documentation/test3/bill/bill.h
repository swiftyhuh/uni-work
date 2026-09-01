#pragma once

#include <iostream>

class Bill {
private:
  std::string compName, serialNumber;
  float sum;
  bool isPaid;

public:
  Bill(std::string compName, std::string serialNumber, float sum, bool isPaid);
  std::string getCompName();
  std::string getSerialNumber();
  float getSum();
  bool getPaid();
  std::string toString();
};
