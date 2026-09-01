#include "domain.h"
#include <fstream>

std::string MedicalAnalysis::getDate() { return this->date; }

BMI::BMI(std::string date, double value) {
  this->value = value;
  this->date = date;
}

bool BMI::isResultOk() {
  if (this->value >= 18.5 && this->value <= 25)
    return true;
  return false;
}
std::string BMI::toString() {
  return "BMI || Date: " + this->date + " | Value: " + std::to_string(value);
}

BP::BP(std::string date, int systolicVal, int diastolicVal) {
  this->date = date;
  this->systolicVal = systolicVal;
  this->diastolicVal = diastolicVal;
}

bool BP::isResultOk() {
  if (this->systolicVal >= 90 && this->systolicVal <= 119) {
    if (this->diastolicVal >= 60 && this->diastolicVal <= 79)
      return true;
    else
      return false;
  } else
    return false;
}

std::string BP::toString() {
  return "BP || Date: " + this->date +
         " | Systolic: " + std::to_string(this->systolicVal) + " | Diastolic " +
         std::to_string(this->diastolicVal);
}

Person::Person(std::string name) { this->name = name; }

void Person::addAnalysis(MedicalAnalysis *a) { this->analyses.push_back(a); }

std::vector<MedicalAnalysis *> Person::getAllAnalyses() {
  return this->analyses;
}

std::vector<MedicalAnalysis *> Person::getAnalysesByMonth(int month) {
  std::vector<MedicalAnalysis *> temp = this->analyses;
  std::vector<MedicalAnalysis *> result;
  for (int i = 0; i < temp.size(); i++) {
    if (std::stoi(temp[i]->getDate().substr(5, 2)) == month)
      result.push_back(temp[i]);
  }
  return result;
}

bool Person::isIll(int month) {
  std::vector<MedicalAnalysis *> temp = this->getAnalysesByMonth(month);

  if (temp.size() == 0)
    return false;

  for (int i = 0; i < temp.size(); i++) {
    if (temp[i]->isResultOk())
      return false;
  }
  return true;
}

std::vector<MedicalAnalysis *>
Person::getAnalysesBetweenDates(std::string date1, std::string date2) {
  std::vector<MedicalAnalysis *> temp = this->analyses;
  std::vector<MedicalAnalysis *> result;
  for (MedicalAnalysis *elem : temp) {
    if (elem->getDate() >= date1 && elem->getDate() <= date2)
      result.push_back(elem);
  }
  return result;
}

void Person::writeToFile(std::string filename, std::string date1,
                         std::string date2) {
  std::ofstream fout(filename);
  for (MedicalAnalysis *elem : this->analyses)
    if (elem->getDate() >= date1 && elem->getDate() <= date2)
      fout << elem->toString() << "\n";
}

Person::~Person() {
  for (MedicalAnalysis *elem : this->analyses)
    delete elem;
}
