# dist[v][k]
# minimum cost from start to v, using exactly k edges
# prev [v][k]
# previous vertex used to reach v with exactly k edges
#

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



