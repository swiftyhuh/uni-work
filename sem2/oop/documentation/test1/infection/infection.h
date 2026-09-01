#pragma once
#include <string>

class Patient {
private:
  std::string name;
  int age, room;
  bool infected;

public:
  Patient(std::string name = "", int age = 0, bool infected = false,
          int room = 0);
  std::string getName() const;
  int getAge() const;
  bool getInfected() const;
  int getRoom() const;
  void setInfected(bool infected);
};
