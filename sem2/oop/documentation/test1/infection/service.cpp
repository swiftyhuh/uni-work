#include "service.h"
#include <algorithm>
#include <stdexcept>

Service::Service(Repo &repo) : repo{repo} {}

void Service::addPatient(std::string name, int age, bool infected, int room) {
  Patient patient = Patient(name, age, infected, room);
  std::vector<Patient> patients = this->repo.getAllPatients();
  for (int i = 0; i < patients.size(); i++)
    if (patients[i].getName() == patient.getName())
      throw std::invalid_argument("The patient already exists.");
  this->repo.addPatient(patient);
}

std::vector<Patient> Service::getAllPatient() {
  return this->repo.getAllPatients();
}

std::vector<Patient> Service::getInfected(int checkage) {
  std::vector<Patient> &patients = this->repo.getAllPatients();
  std::vector<int> rooms;
  std::vector<Patient> infectedPatients;
  for (int i = 0; i < patients.size(); i++)
    if (patients[i].getInfected() == true)
      rooms.push_back(patients[i].getRoom());
  for (int i = 0; i < patients.size(); i++) {
    if (std::find(rooms.begin(), rooms.end(), patients[i].getRoom()) !=
            rooms.end() &&
        patients[i].getAge() > checkage) {
      patients[i].setInfected(true);
    }
  }
  for (int i = 0; i < patients.size(); i++)
    if (patients[i].getInfected() == true)
      infectedPatients.push_back(patients[i]);
  return infectedPatients;
}
