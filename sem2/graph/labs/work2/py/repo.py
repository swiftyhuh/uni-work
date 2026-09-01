from domain import Graph
from random import randint

def read_graph(filename: str):
    with open(filename, "r") as f:
        data = f.read().split()
        n = int(data[0])
        m = int(data[1])
        if n < 0 or m < 0:
            raise ValueError("Number of vertices and edges must be non-negative")
        graph = Graph(n)
        for i in range(m):
            x = int(data[2 + i*3])
            y = int(data[2 + i*3 + 1])
            c = int(data[2 + i*3 + 2])
            graph.add_edge(x, y, c)
        return graph

def write_graph(graph: Graph, filename: str):
    vertices = list(graph.get_vertices())
    remap = {}
    for i, v in enumerate(vertices):
        remap[v] = i
    n = graph.get_num_vertices()
    m = graph.get_num_edges()
    with open(filename, "w") as f:
        f.write(f"{n} {m}\n")
        for x, y in graph.get_edges():
            c = graph.get_cost(x, y)
            f.write(f"{remap[x]} {remap[y]} {c}\n")

def random_graph(n: int, m: int):
    if n < 0 or m < 0:
        raise ValueError("Number of vertices must be a non zero positive number")
    if m > n*n:
        raise ValueError("Too many edges for the number of vertices")
    graph = Graph(n)
    added = 0
    while added < m:
        x = randint(0, n-1)
        y = randint(0, n-1)
        if not graph.is_edge(x, y):
            graph.add_edge(x, y, randint(1, 100))
            added += 1
    return graph
