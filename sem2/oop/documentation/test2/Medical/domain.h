#include <iostream>
#include <vector>

class MedicalAnalysis {
protected:
  std::string date;

public:
  std::string getDate();
  virtual bool isResultOk() = 0;
  virtual std::string toString() = 0;
  virtual ~MedicalAnalysis() = default;
};

class BMI : public MedicalAnalysis {
private:
  double value;

public:
  BMI(std::string date, double value);
  bool isResultOk() override;
  std::string toString() override;
  ~BMI() = default;
};

class BP : public MedicalAnalysis {
private:
  int systolicVal, diastolicVal;

public:
  BP(std::string date, int systolicVal, int diastolicVal);
  bool isResultOk() override;
  std::string toString() override;
  ~BP() = default;
};

class Person {
private:
  std::string name;
  std::vector<MedicalAnalysis *> analyses;

public:
  Person(std::string name = "");
  void addAnalysis(MedicalAnalysis *a);
  std::vector<MedicalAnalysis *> getAllAnalyses();
  std::vector<MedicalAnalysis *> getAnalysesByMonth(int month);
  bool isIll(int month);
  std::vector<MedicalAnalysis *> getAnalysesBetweenDates(std::string date1,
                                                         std::string date2);
  void writeToFile(std::string filename, std::string date1, std::string date2);
  ~Person();
};
