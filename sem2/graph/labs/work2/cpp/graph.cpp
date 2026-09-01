#include "graph.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

Graph::Graph(int numVertices) {
  if (numVertices < 0) {
    throw std::invalid_argument("Num of vertices must be a positive number!");
  }
  _numVertices = numVertices;
  _nextId = numVertices;
  _numEdges = 0;
  for (int i = 0; i < numVertices; i++) {
    out[i] = std::vector<int>();
    in[i] = std::vector<int>();
  }
}

int Graph::getNumVertices() const { return _numVertices; }

int Graph::getNumEdges() const { return _numEdges; }
// loop over internal map,extract what it needs, push into a new vector, return
// vector.
std::vector<int> Graph::getVertices() const {
  std::vector<int> vertices; // new vector copy
  for (auto &pair : out) // loop over internal (auto it tells the compiler that
                         // whatver type the map entry is, is good)
    vertices.push_back(
        pair.first); // extract and push into a new vector vertex id
  return vertices;
}

std::vector<std::pair<int, int>> Graph::getEdges() const {
  std::vector<std::pair<int, int>> edges;
  for (auto &pair : cost)
    edges.push_back(pair.first);
  return edges;
}

bool Graph::isEdge(int x, int y) const {
  return cost.count(std::make_pair(x, y)) > 0;
}

int Graph::getCost(int x, int y) const {
  if (!isEdge(x, y))
    throw std::invalid_argument("Edge doesn't exist!");
  return cost.at(std::make_pair(x, y));
}

void Graph::setCost(int x, int y, int c) {
  if (!isEdge(x, y))
    throw std::invalid_argument("Edge doesn't exist!");
  cost[std::make_pair(x, y)] = c;
}

void Graph::addEdge(int x, int y, int c) {
  if (out.count(x) == 0 || in.count(y) == 0)
    throw std::invalid_argument("Vertex doesn t exist!");
  if (isEdge(x, y))
    throw std::invalid_argument("Edge already exist!");
  cost[std::make_pair(x, y)] = c;
  in[y].push_back(x);
  out[x].push_back(y);
  _numEdges++;
}

void Graph::removeEdge(int x, int y) {
  if (!isEdge(x, y))
    throw std::invalid_argument("Edge doesn t exist!");
  cost.erase(std::make_pair(x, y));
  in[y].erase(std::find(in[y].begin(), in[y].end(), x));
  out[x].erase(std::find(out[x].begin(), out[x].end(), y));
  _numEdges--;
}

int Graph::addVertex() {
  int v = _nextId;
  _nextId++;
  out[v] = std::vector<int>();
  in[v] = std::vector<int>();
  _numVertices++;
  return v;
}

void Graph::removeVertex(int v) {
  checkVertex(v);
  std::vector<int> outCopy = out[v];
  for (int y : outCopy)
    removeEdge(v, y);
  std::vector<int> inCopy = in[v];
  for (int x : inCopy)
    removeEdge(x, v);
  out.erase(v);
  in.erase(v);
  _numVertices--;
}

void Graph::checkVertex(int v) const {
  if (out.count(v) == 0)
    throw std::invalid_argument("Vertex doesnt' exist!");
}

int Graph::inDegree(int v) const {
  checkVertex(v);
  return in.at(v).size();
}

int Graph::outDegree(int v) const {
  checkVertex(v);
  return out.at(v).size();
}

std::vector<int> Graph::outbound(int v) const {
  checkVertex(v);
  return out.at(v);
}

std::vector<int> Graph::inbound(int v) const {
  checkVertex(v);
  return in.at(v);
}

Graph Graph::copy() const { return *this; }
