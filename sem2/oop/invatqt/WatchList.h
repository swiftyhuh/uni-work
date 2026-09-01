#pragma once

#include "Tutorial.h"
#include <string>
#include <vector>

class WatchList {
protected:
  std::vector<Tutorial> tutorials;
  std::string filename;

public:
  WatchList(std::string filename);

  virtual ~WatchList() = default;

  void add(Tutorial tutorial);
  void remove(std::string title, std::string presenter);
  std::vector<Tutorial> get_all();

  virtual void write_to_file() = 0;
  virtual void display() = 0;
};

class CSVWatchList : public WatchList {
public:
  CSVWatchList(std::string filename);

  void write_to_file() override;
  void display() override;
};

class HTMLWatchList : public WatchList {
public:
  HTMLWatchList(std::string filename);

  void write_to_file() override;
  void display() override;
};
