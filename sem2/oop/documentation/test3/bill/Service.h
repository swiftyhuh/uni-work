#pragma once
#include "Repository.h"
#include <vector>

class Service {
private:
  Repository &repo;

public:
  Service(Repository &repo);
  std::vector<Bill> getAllSorted();
  std::vector<Bill> getFiltered(bool isPaid);
  float getTotalUnpaid(std::string company);
};
