import graph

def bfs(g, s, t=None):
    '''Performs a Breadth-First Search in graph g starting from vertex s, stopping when finding vertex t
        or after visiting all accessible vertices if t==None.
        Returns a tuple of dictionaries (dist, parent), where
          - dist[x] = the length of the shortest path from s to x (only for accessible vertices)
          - parent[x] = parent of x in BFS tree = previous vertex, just before x, on the shourtest path from s to x
              parent[s] = None
        Preconditions: s and (if not None) t are vertices of graph g.
    '''
    dist = {s:0}
    parent = {s:None}
    queue = [s]
    while len(queue) > 0:
        current = queue.pop(0)
        for child in g.parse_out(current):
            if child not in dist.keys():
                dist[child] = dist[current] + 1
                parent[child] = current
                if child == t:
                    return (dist, parent)
                queue.append(child)
        
    return (dist, parent)

def shortest_path(g, s, t):
    '''Returns a list of vertices representing the shortest path form vertex s to vertex t in the graph g.
        Returns None if there is no path.
        Preconditions: s and t are vertices of graph g.
    '''
    dist, parent = bfs(g, s, t)
    if t not in parent.keys():
        return None
    path = []
    current = t
    while current != s:
        path.append(current)
        current = parent[current]
    path.append(s)
    path.reverse()
    return path

def test_bfs():
    g = graph.small_graph()
    dist, parent = bfs(g, 1, 3)
    print(f"dist={dist}")
    print(f"parent={parent}")
    path = shortest_path(g, 1, 3)
    print(f"Path={path}")

if __name__ == "__main__":
    test_bfs()
