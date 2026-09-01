import graph
import time

def bfs(g, start_vertex):
    '''Returns a dictionary mapping each vertex that is accessible from 'start_vertex' (in the graph 'g')
        to an integer representing the length of the shortest path from start_vertex to it.
        Precond: start_vertex is a vertex of g
    '''
    dist = {}
    queue = [start_vertex]
    dist[start_vertex] = 0
    head_index = 0
    while head_index < len(queue):
        current_vert = queue[head_index]
        head_index += 1
        #print(current_vert)
        for x in g.parse_out(current_vert):
            if x not in dist.keys():
                queue.append(x)
                dist[x] = dist[current_vert] + 1
        #queue.remove(current_vert)
    return dist

def shortest_path(g, s, t):
    '''Retuns the shortest path from s to t in graph g, or None if t is not accessible from s.
        Precond: s and t are vertices of g.
    '''
    dist = bfs(g, s)
    print(f"dist={dist}")
    if t not in dist.keys():
        return None
    path = [t]
    current_vert = t
    while current_vert != s:
        for x in g.parse_in(current_vert):
            if x in dist.keys() and dist[x] == dist[current_vert] - 1:
                path.append(x)
                current_vert = x
                break
    path.reverse()
    return path

def test_bfs():
    #before = time.time()
    g = graph.small_graph()
    #n = 10000
    #g = graph.random_graph(n, 100*n)
    #dist = bfs(g, 0)
    path = shortest_path(g, 1, 4)
    #after = time.time()
    #print(f"Time={(after-before)*1000} ms")
    print(f"Path: {path}")

if __name__ == "__main__":
    test_bfs()
