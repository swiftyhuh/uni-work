#include "ui.h"
#include <iostream>
#include <stdexcept>
#include <string>

UI::UI() { _graph = Graph(); }

void UI::printMenu() {
  std::cout << "\n=== Directed Graph Menu ===\n";
  std::cout << " 1.  Number of vertices and edges\n";
  std::cout << " 2.  List all vertices\n";
  std::cout << " 3.  List all edges\n";
  std::cout << " 4.  Check if edge exists\n";
  std::cout << " 5.  Add edge\n";
  std::cout << " 6.  Remove edge\n";
  std::cout << " 7.  Get cost of edge\n";
  std::cout << " 8.  Set cost of edge\n";
  std::cout << " 9.  Add vertex\n";
  std::cout << " 10. Remove vertex\n";
  std::cout << " 11. Get in/out degree of vertex\n";
  std::cout << " 12. Print inbound neighbors\n";
  std::cout << " 13. Print outbound neighbors\n";
  std::cout << " 14. Read graph from file\n";
  std::cout << " 15. Write graph to file\n";
  std::cout << " 16. Generate random graph\n";
  std::cout << " 17. Copy graph\n";
  std::cout << " 0.  Exit\n";
  std::cout << "Enter choice: ";
}

void UI::run() {
  int choice;
  while (true) {
    printMenu();
    std::cin >> choice;
    try {
      if (choice == 0) {
        break;
      } else if (choice == 1) {
        std::cout << "Vertices: " << _graph.getNumVertices()
                  << ", Edges: " << _graph.getNumEdges() << "\n";
      } else if (choice == 2) {
        for (int v : _graph.getVertices())
          std::cout << v << "\n";
      } else if (choice == 3) {
        for (std::pair<int, int> e : _graph.getEdges())
          std::cout << "(" << e.first << ", " << e.second
                    << ") cost: " << _graph.getCost(e.first, e.second) << "\n";
      } else if (choice == 4) {
        int x, y;
        std::cout << "From vertex: ";
        std::cin >> x;
        std::cout << "To vertex: ";
        std::cin >> y;
        if (_graph.isEdge(x, y))
          std::cout << "Edge exists! \n";
        else
          std::cout << "Edge doesnt exists! \n";
      } else if (choice == 5) {
        int x, y, c;
        std::cout << "From vertex: ";
        std::cin >> x;
        std::cout << "To vertex: ";
        std::cin >> y;
        std::cout << "Cost: ";
        std::cin >> c;
        _graph.addEdge(x, y, c);
        std::cout << "Edge added! \n";
      } else if (choice == 6) {
        int x, y;
        std::cout << "From vertex: ";
        std::cin >> x;
        std::cout << "To vertex: ";
        std::cin >> y;
        _graph.removeEdge(x, y);
        std::cout << "Edge removed!\n";
      } else if (choice == 7) {
        int x, y;
        std::cout << "From vertex: ";
        std::cin >> x;
        std::cout << "To vertex: ";
        std::cin >> y;
        std::cout << "Cost: " << _graph.getCost(x, y) << "\n";
      } else if (choice == 8) {
        int x, y, c;
        std::cout << "From vertex: ";
        std::cin >> x;
        std::cout << "To vertex: ";
        std::cin >> y;
        std::cout << "New cost: ";
        std::cin >> c;
        _graph.setCost(x, y, c);
        std::cout << "Cost updated!\n";
      } else if (choice == 9) {
        int v = _graph.addVertex();
        std::cout << "Vertex " << v << " added!\n";
      } else if (choice == 10) {
        int v;
        std::cout << "Vertex to remove: ";
        std::cin >> v;
        _graph.removeVertex(v);
        std::cout << "Vertex removed!\n";
      } else if (choice == 11) {
        int v;
        std::cout << "Vertex: ";
        std::cin >> v;
        std::cout << "In-degree: " << _graph.inDegree(v)
                  << ", Out-degree: " << _graph.outDegree(v) << "\n";
      } else if (choice == 12) {
        int v;
        std::cout << "Vertex: ";
        std::cin >> v;
        for (int u : _graph.inbound(v))
          std::cout << u << "\n";
      } else if (choice == 13) {
        int v;
        std::cout << "Vertex: ";
        std::cin >> v;
        for (int u : _graph.outbound(v))
          std::cout << u << "\n";
      } else if (choice == 14) {
        std::string filename;
        std::cout << "Filename: ";
        std::cin >> filename;
        _graph = readGraph(filename);
        std::cout << "Graph loaded! \n";
      } else if (choice == 15) {
        std::string filename;
        std::cout << "Filename: ";
        std::cin >> filename;
        writeGraph(_graph, filename);
        std::cout << "Graph saved! \n";
      } else if (choice == 16) {
        int n, m;
        std::string filename;
        std::cout << "Number of vertices: ";
        std::cin >> n;
        std::cout << "Number of edges: ";
        std::cin >> m;
        std::cout << "Save to filename: ";
        std::cin >> filename;
        _graph = randomGraph(n, m);
        writeGraph(_graph, filename);
        std::cout << "Random graph generated and saved " << filename << "\n";
      } else if (choice == 17) {
        Graph copy = _graph.copy();
        std::cout << "Graph copied! Copy has " << copy.getNumVertices()
                  << " vertices and " << copy.getNumEdges() << " edes \n";
      } else {
        std::cout << "Invalid choice! \n";
      }
    } catch (std::invalid_argument &e) {
      std::cout << "Error: " << e.what() << "\n";
    }
  }
}
