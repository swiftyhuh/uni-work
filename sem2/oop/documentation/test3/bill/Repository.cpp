#include "Repository.h"
#include <fstream>
#include <sstream>

Repository::Repository(std::string filename) {
  this->filename = filename;
  this->loadFromFile();
}

void Repository::loadFromFile() {
  std::ifstream fin(this->filename);
  std::string line;
  while (std::getline(fin, line)) {
    std::stringstream ss(line);
    std::string company, serial, sumString, paidString;
    std::getline(ss, company, ';');
    std::getline(ss, serial, ';');
    std::getline(ss, sumString, ';');
    std::getline(ss, paidString, '\n');

    float sum = std::stof(sumString);
    bool paid = (paidString == " true");

    this->bills.push_back(Bill(company, serial, sum, paid));
  }
}

std::vector<Bill> Repository::getAll() { return this->bills; }
