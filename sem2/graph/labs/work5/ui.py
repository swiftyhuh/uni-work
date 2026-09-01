from domain import Graph
from repo import read_graph, write_graph, random_graph
from service import lowest_cost_walk,connected_components, kruskal_mst, minimum_cost_hamiltonian_cycle

class UI:
    def __init__(self):
        self._graph = Graph()

    def _menu(self):
        print("""
=== Work 3 Graph Menu ===
 1.  Number of vertices and edges
 2.  List all vertices
 3.  List all edges
 4.  Check if edge exists
 5.  Add edge
 6.  Remove edge
 7.  Get cost of edge
 8.  Set cost of edge
 9.  Add vertex
 10. Remove vertex
 11. Get in/out degree of vertex
 12. Print inbound neighbors of vertex
 13. Print outbound neighbors of vertex
 14. Read graph from file
 15. Write graph to file
 16. Generate random graph
 17. Copy graph
 18. Find connected components
 19. Find lowest cost walk
 20. Find minimum spanning tree (Kruskal) 
 21. Find minimum cost Hamiltonian cycle
 0.  Exit
""")

    def run(self):
        while True:
            self._menu()
            choice = input("Enter choice: ").strip()
            try:
                if choice == "0":
                    break
                elif choice == "1":
                    print(f"Vertices: {self._graph.get_num_vertices()}, Edges: {self._graph.get_num_edges()}")
                elif choice == "2":
                    for v in self._graph.get_vertices():
                        print(v)
                elif choice == "3":
                    for x, y in self._graph.get_edges():
                        print(f"({x}, {y}) cost: {self._graph.get_cost(x, y)}")
                elif choice == "4":
                    x = int(input("From vertex: "))
                    y = int(input("To vertex: "))
                    print("Edge exists!" if self._graph.is_edge(x, y) else "Edge does not exist!")
                elif choice == "5":
                    x = int(input("From vertex: "))
                    y = int(input("To vertex: "))
                    c = int(input("Cost: "))
                    self._graph.add_edge(x, y, c)
                    print("Edge added!")
                elif choice == "6":
                    x = int(input("From vertex: "))
                    y = int(input("To vertex: "))
                    self._graph.remove_edge(x, y)
                    print("Edge removed!")
                elif choice == "7":
                    x = int(input("From vertex: "))
                    y = int(input("To vertex: "))
                    print(f"Cost: {self._graph.get_cost(x, y)}")
                elif choice == "8":
                    x = int(input("From vertex: "))
                    y = int(input("To vertex: "))
                    c = int(input("New cost: "))
                    self._graph.set_cost(x, y, c)
                    print("Cost updated!")
                elif choice == "9":
                    v = self._graph.add_vertex()
                    print(f"Vertex {v} added!")
                elif choice == "10":
                    v = int(input("Vertex to remove: "))
                    self._graph.remove_vertex(v)
                    print("Vertex removed!")
                elif choice == "11":
                    v = int(input("Vertex: "))
                    print(f"In-degree: {self._graph.in_degree(v)}, Out-degree: {self._graph.out_degree(v)}")
                elif choice == "12":
                    v = int(input("Vertex: "))
                    for u in self._graph.inbound(v):
                        print(u)
                elif choice == "13":
                    v = int(input("Vertex: "))
                    for u in self._graph.outbound(v):
                        print(u)
                elif choice == "14":
                    filename = input("Filename: ")
                    self._graph = read_graph(filename)
                    print("Graph loaded!")
                elif choice == "15":
                    filename = input("Filename: ")
                    write_graph(self._graph, filename)
                    print("Graph saved!")
                elif choice == "16":
                    n = int(input("Number of vertices: "))
                    m = int(input("Number of edges: "))
                    filename = input("Save to filename: ")
                    self._graph = random_graph(n, m)
                    write_graph(self._graph, filename)
                    print(f"Random graph generated and saved to {filename}!")
                elif choice == "17":
                    copy = self._graph.copy()
                    print(f"Graph copied! Copy has {copy.get_num_vertices()} vertices and {copy.get_num_edges()} edges.")
                elif choice == "18":
                    components = connected_components(self._graph)
                    print(f"Number of connected components: {len(components)}")
                    for i, component in enumerate(components):
                        print(f"Component {i+1}:")
                        print("Vertices:", list(component.get_vertices()))
                        print("Edges:")
                        for x, y in component.get_edges():
                            print(f"({x}, {y}) cost: {component.get_cost(x, y)}")
                elif choice == "19":
                    start = int(input("Start vertex: "))
                    end = int(input("End vertex: "))

                    walk, cost, message = lowest_cost_walk(self._graph, start, end)

                    if message is not None:
                        print(message)
                    else:
                        print("Lowest cost walk:", walk)
                        print("Cost:", cost)
                elif choice =="20":
                    mst, total_cost = kruskal_mst(self._graph)

                    print("Minimum spanning tree edges:")
                    for x,y,cost in mst:
                        print(f"({x},{y}) cost: {cost}")

                    print("Total cost: ", total_cost)
                elif choice == "21":
                    cycle, cost, message = minimum_cost_hamiltonian_cycle(self._graph)

                    if message is not None:
                        print(message)
                    else:
                        print("Minimum cost Hamiltonian cycle:", cycle)
                        print("Cost:", cost)
                else:
                    print("Invalid choice!")
            except ValueError as e:
                print(f"Error: {e}")
