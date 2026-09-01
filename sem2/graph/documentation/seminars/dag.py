import graph

def create_dag():
    g = graph.Graph(6)
    g.add_edge(4, 1, 1)
    g.add_edge(4, 2, 1)
    g.add_edge(2, 1, 1)
    g.add_edge(3, 2, 1)
    g.add_edge(4, 0, 1)
    g.add_edge(1, 5, 1)
    return g

def create_non_dag():
    g = create_dag()
    g.add_edge(5, 2, 1)
#    g.add_edge(2, 4, 1)
    return g

def toposort(g):
    '''Topologically sorts graph g.
        Returns the list of vertices of g in a topological order.
        Returns None if the graph cannot be topologically sorted
    '''
    in_degree = {}
    zero_in_degree_vertices = []
    sorted = []
    for x in g.parse_vertices():
        in_degree[x] = len(list(g.parse_in(x)))
        if in_degree[x] == 0:
            zero_in_degree_vertices.append(x)
    while len(zero_in_degree_vertices) > 0:
        x = zero_in_degree_vertices.pop()
        sorted.append(x)
        for y in g.parse_out(x):
            in_degree[y] -= 1
            if in_degree[y] == 0:
                zero_in_degree_vertices.append(y)
    if len(sorted) < len(in_degree):
        cycle = []
        visited = set()
        for x in g.parse_vertices():
            if in_degree[x] != 0:
                current = x
                break
        while current not in visited:
            cycle.append(current)
            visited.add(current)
            for x in g.parse_in(current):
                if in_degree[x] != 0:
                    current = x
        cycle.append(current)
        cycle.reverse()
        while cycle[-1] != current:
            cycle.pop()
        print(f"Cycle found: {cycle}")
        return None
    return sorted

def toposort_aux(x, g, visited, sorted):
    visited.add(x)
    for y in g.parse_in(x):
        if y not in visited:
            toposort_aux(y, g, visited, sorted)
    sorted.append(x)

def toposort2(g):
    visited = set()
    sorted = []
    for x in g.parse_vertices():
        if x not in visited:
            toposort_aux(x, g, visited, sorted)
    return sorted

def longest_path(g):
    '''Given a DAG g, finds the longest path in it.
        Returns the path as a list of vertices.
    '''
    sorted = toposort(g)
    w = {}
    for x in sorted:
        w[x] = 0
        for y in g.parse_in(x):
            if w[x] < w[y] + 1:
                w[x] = w[y] + 1
    print(f"w={w}")
    last_vertex = None
    for x in g.parse_vertices():
        if last_vertex is None or w[last_vertex] < w[x]:
            last_vertex = x
    path = [last_vertex]
    current = last_vertex
    while w[current] > 0:
        for x in g.parse_in(current):
            if w[current] == w[x] + 1:
                current = x
                break
        path.append(current)
    path.reverse()
    return path

def test_toposort():
    g = create_dag()
    sorted = toposort(g)
    print(f"Sorted = {sorted}")
    g = create_non_dag()
    sorted = toposort(g)
    print(f"\"Sorted\" non-DAG = {sorted}")
    g = create_dag()
    sorted = toposort2(g)
    print(f"Sorted = {sorted}")

def test_longest_path():
    g = create_dag()
    path = longest_path(g)
    print(f"Path={path}")

if __name__ == "__main__":
    test_toposort()
    #test_longest_path()

