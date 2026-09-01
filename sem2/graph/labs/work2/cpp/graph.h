#pragma once
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

class Graph {
private:
  int _numVertices;
  int _nextId;
  int _numEdges;
  std::map<std::pair<int, int>, int> cost;
  std::map<int, std::vector<int>> out;
  std::map<int, std::vector<int>> in;
  void checkVertex(int v) const;

public:
  Graph(int numVertices = 0);
  int getNumVertices() const;
  int getNumEdges() const;
  std::vector<int> getVertices() const;
  std::vector<std::pair<int, int>> getEdges() const;
  bool isEdge(int x, int y) const;
  int getCost(int x, int y) const;
  void setCost(int x, int y, int cost);
  void addEdge(int x, int y, int cost);
  void removeEdge(int x, int y);
  int addVertex();
  void removeVertex(int v);
  int inDegree(int v) const;
  int outDegree(int v) const;
  std::vector<int> outbound(int v) const;
  std::vector<int> inbound(int v) const;
  Graph copy() const;
};
