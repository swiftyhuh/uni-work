#include <string>

class Building {
protected:
  std::string address;
  int constructionYear;

public:
  std::string getAddress();
  int getYear();
  virtual bool mustBeRestored() = 0;
  virtual bool canBeDemolished() = 0;
  virtual std::string toString() = 0;
  virtual ~Building() = default;
};

class Block : public Building {
private:
  int nrApartaments, nrApsOccupied;

public:
  Block(std::string address, int constructionYear, int nrApartaments,
        int nrApsOccupied);
  bool mustBeRestored() override;
  bool canBeDemolished() override;
  std::string toString() override;
};

class House : public Building {
private:
  std::string type;
  bool historical;

public:
  House(std::string address, int constructionYear, std::string type,
        bool historical);
  bool mustBeRestored() override;
  bool canBeDemolished() override;
  std::string toString() override;
};
