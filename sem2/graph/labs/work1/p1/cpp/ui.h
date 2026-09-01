#pragma once
#include "graph.h"
#include "repo.h"

class UI {
private:
  Graph _graph;
  void printMenu();

public:
  UI();
  void run();
};
