#pragma once
#include "bill.h"
#include <vector>

class Repository {
private:
  std::vector<Bill> bills;
  std::string filename;

public:
  Repository(std::string filename);
  void loadFromFile();
  std::vector<Bill> getAll();
};
