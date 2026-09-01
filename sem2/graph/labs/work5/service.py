# dist[v][k]
# minimum cost from start to v, using exactly k edges
# prev [v][k]
# previous vertex used to reach v with exactly k edges
#
from domain import Graph


def dfs_component(graph, vertex, visited, component_vertices):
    """
    DFS from one vertex.

    graph - the graph
    vertex - the start vertex
    visited - set of visited vertices
    component_vertices - list where the vertices of the current component are stored

    Finds the vertices of one component
    """
    stack = [vertex]

    while stack:
        current = stack.pop()

        if current in visited:
            continue

        visited.add(current)
        component_vertices.append(current)

        for neighbor in graph.neighbors(current):
            if neighbor not in visited:
                stack.append(neighbor)


def build_component_graph(graph, component_vertices):
    """
    Builds a graph object for one connected component.

    graph - the original graph
    component_vertices - list of vertices from one component

    Returns a Graph object.
    """
    component = Graph()
    component_set = set(component_vertices)

    for vertex in component_vertices:
        component.add_vertex(vertex)

    for x, y in graph.get_edges():
        if x in component_set and y in component_set:
            cost = graph.get_cost(x, y)
            component.add_edge(x, y, cost)

    return component


def connected_components(graph):
    """
    Finds all connected components using DFS.

    graph - the graph

    Returns a list of Graph objects.
    """
    visited = set()
    result = []

    for vertex in graph.get_vertices():
        if vertex not in visited:
            component_vertices = []
            dfs_component(graph, vertex, visited, component_vertices)

            component_graph = build_component_graph(graph, component_vertices)
            result.append(component_graph)

    return result

def build_walk(prev, end, k):
    walk = []
    current = end
    current_k = k

    while current is not None:
        walk.append(current)
        current = prev[current][current_k]
        current_k -= 1

    walk.reverse()
    return walk

def fill_tables(graph, start):
    vertices = list(graph.get_vertices())
    n = len(vertices)

    dist = {}
    prev = {}

    for vertex in vertices:
        dist[vertex] = [None] * (n+1)
        prev[vertex] = [None] * (n+1)

    dist[start][0] = 0

    #min cost from start to v, using exactly k edges;
    for k in range(1,n+1):
        for x, y in graph.get_edges():
            cost = graph.get_cost(x,y)

            if dist[x][k-1] is not None:
                new_cost = dist[x][k-1] + cost
               
                # update dist and prev if we found a better cost for reaching y with k edges
                if dist[y][k] is None or new_cost < dist[y][k]:
                    dist[y][k] = new_cost
                    prev[y][k] = x

    return dist, prev

def lowest_cost_walk(graph, start, end):
    vertices = list(graph.get_vertices())
    n = len(vertices)

    dist,prev = fill_tables(graph, start)

    for vertex in vertices:
        old_best = None
        for k in range(n):
            #ignore unreachable vertices
            if dist[vertex][k] is not None:
                # update old best cost for reaching vertex with at most n-1 edges
                if old_best is None or dist[vertex][k] < old_best:
                    old_best = dist[vertex][k]
        # check the value for reaching vertex with n edges, if it's not None and it's better than old best, then we have a negative cost cycle accessible from the starting vertex
        if dist[vertex][n] is not None:
            if old_best is None or dist[vertex][n] < old_best:
                return None, None, "There is a negative cost cycle accesible from the starting vertex."
    
    best_cost = None
    best_k = None
    
    for k in range(n):
        if dist[end][k] is not None:
            #if is the first reacheable value or a cheaper one
            if best_cost is None or dist[end][k] < best_cost:
                # save the better cost, and the number of edges
                best_cost = dist[end][k]
                best_k = k

    # check no walk from start to end
    if best_cost is None:
        return None, None, "there is no walk."

    walk = build_walk(prev, end, best_k)
    return walk, best_cost, None

# WORK 4

#if u and v are already in the same connected component skips cuz its creates a cycle
def find(parent, vertex):
    # parent stores who is above each vertex
    while parent[vertex] != vertex:
        vertex = parent[vertex]
    return vertex

# if u and v are in different components(different representative) adding edge(u,v) its safe, so they merge
def union(parent, u , v):
    root_u = find(parent, u)
    root_v = find(parent, v)

    if root_u != root_v:
        parent[root_v] = root_u
    # so for each u,v edges, we are checking the parent, if tey have a diferent root addigs its safe, if not, they will craete a cycle


def kruskal_mst(graph):
# sorts the edges by cost, add the cheast that do not from cycles, build the minimum spanning tree and its total cost.
    parent = {}
    edges = []
    mst = []
    total_cost = 0;

    for vertex in graph.get_vertices():
        parent[vertex] = vertex

    # we get each edges, but we have it with cost being the first item because we are going to sort in term of cost
    for x, y in graph.get_edges():
        cost = graph.get_cost(x,y)
        edges.append((cost, x, y))

    edges.sort()

    for cost, x, y in edges:
        if find(parent, x) != find(parent, y):
            # if x and y are in different components we are adding it.
            mst.append((x,y,cost))
            total_cost +=cost
            union(parent, x, y)

    return mst, total_cost


# WORK 5

def backtrack_hamiltonian(graph, start, path, visited, current_cost, best_path,
  best_cost):
    if len(path) == len(list(graph.get_vertices())):#check if we already usedall vertices
        if graph.is_edge(path[-1], start): # check if we can return to the start vertex to form a cycle
            total_cost = current_cost + graph.get_cost(path[-1], start)
            if best_cost[0] is None or total_cost < best_cost[0]:
            # if this cycle its the first one that we found, or a cheaper one we save the cycle and the cost
                best_cost[0] = total_cost
                best_path[0] = path[:] + [start]
        return
    
    # gets the last vertex in the current path
    last = path[-1]
    # tries all outgoing neighbrs of last, and only use vertices not already in the path
    for neighbor in sorted(graph.outbound(last)):
        if neighbor not in visited:
            edge_cost = graph.get_cost(last, neighbor)
            new_cost = current_cost + edge_cost

            if best_cost[0] is not None and new_cost >= best_cost[0]:
                continue
            # if the partial ocst is already worse than the best know, we stop with this branch.

            visited.add(neighbor)
            path.append(neighbor)
            #chose thaat neighbor, and continue with the search


            backtrack_hamiltonian(graph, start, path, visited, new_cost, best_path, best_cost)

            path.pop()
            # recursive, backtrack and undo the choice and try the next neighbor
            visited.remove(neighbor)

def minimum_cost_hamiltonian_cycle(graph):
    vertices = sorted(list(graph.get_vertices()))

    if not vertices:
        return None, None, "There is no Hamiltonian cycle."

    start = vertices[0] # starting vertex, avoids duplicates cycles that are just rotations of each other.
    path = [start] 
    visited = {start}
    best_path = [None]
    best_cost = [None]
    
    backtrack_hamiltonian(graph, start, path, visited, 0, best_path, best_cost)

    if best_path[0] is None:
        return None, None, "There is no Hamiltonian cycle."

    return best_path[0], best_cost[0], None
