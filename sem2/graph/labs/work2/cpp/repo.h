#pragma once
#include "graph.h"
#include <string>

Graph readGraph(const std::string &filename);
void writeGraph(const Graph &graph, const std::string &filename);
Graph randomGraph(int n, int m);
