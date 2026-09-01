#include "Service.h"
#include <algorithm>

Service::Service(Repository &repo) : repo(repo) {}

std::vector<Bill> Service::getAllSorted() {
  std::vector<Bill> bills = this->repo.getAll();

  std::sort(bills.begin(), bills.end(),
            [](Bill a, Bill b) { return a.getCompName() < b.getCompName(); });
  return bills;
}

std::vector<Bill> Service::getFiltered(bool isPaid) {
  std::vector<Bill> result;

  for (auto bill : this->repo.getAll())
    if (bill.getPaid() == isPaid)
      result.push_back(bill);
  return result;
}

float Service::getTotalUnpaid(std::string company) {
  float total = 0;

  for (auto bill : this->repo.getAll())
    if (bill.getCompName() == company && bill.getPaid() == false)
      total += bill.getSum();

  return total;
}
