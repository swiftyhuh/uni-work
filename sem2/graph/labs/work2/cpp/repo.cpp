#include "repo.h"
#include <fstream>
#include <stdexcept>

Graph readGraph(const std::string &filename) {
  std::ifstream fin(filename);
  if (!fin.is_open())
    throw std::invalid_argument("Cannot open file!");

  int n, m;
  fin >> n >> m;
  if (n < 0 || m < 0)
    throw std::invalid_argument(
        "Number of vertices and edges must be non-negative!");
  Graph graph(n);
  for (int i = 0; i < m; i++) {
    int x, y, c;
    fin >> x >> y >> c;
    graph.addEdge(x, y, c);
  }
  return graph;
}

void writeGraph(const Graph &graph, const std::string &filename) {
  std::ofstream fout(filename);
  if (!fout.is_open())
    throw std::invalid_argument("Cannot open file!");
  std::vector<int> vertices =
      graph.getVertices();  // return current vertx id in mess order
  std::map<int, int> remap; // create the new map
  for (int i = 0; i < vertices.size(); i++) // iterate trough 1 - n-1
    remap[vertices[i]] =
        i; // the current vertex ids is chane to a clean 0...n-1 sequence
  fout << graph.getNumVertices() << " " << graph.getNumEdges() << "\n";
  std::vector<std::pair<int, int>> edges = graph.getEdges();
  for (std::pair<int, int> e : edges) {
    int c = graph.getCost(e.first, e.second);
    fout << remap[e.first] << " " << remap[e.second] << " " << c << "\n";
  }
}

Graph randomGraph(int n, int m) {
  if (n < 0 || m < 0)
    throw std::invalid_argument(
        "Number of vertices and edges must be non-negative");
  if ((long long)n * n < m)
    throw std::invalid_argument("Too many edges for the number of vertices!");
  Graph graph(n);
  int added = 0;
  while (added < m) {
    int x = rand() % n;
    int y = rand() % n;
    if (!graph.isEdge(x, y)) {
      graph.addEdge(x, y, rand() % 100 + 1);
      added++;
    }
  }
  return graph;
}
