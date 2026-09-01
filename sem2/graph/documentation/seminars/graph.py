from random import randint
import time

class Graph:
    def __init__(self,number_vertices):
        self._outbound_neighbours = {}
        self._inbound_neighbours = {}
        self._cost = {}
        
        self._number_vertices=number_vertices
        for i in range(number_vertices):
            self._outbound_neighbours[i]=[]
            self._inbound_neighbours[i]=[]
            
    def add_edge(self,x,y,cost):
        if x not in self._outbound_neighbours.keys():
            raise Exception()
        if y not in self._outbound_neighbours.keys():
            raise Exception()
        if  self.is_edge(x,y):
            raise Exception()
        
        self._cost[(x,y)] = cost
        self._outbound_neighbours[x].append(y)
        self._inbound_neighbours[y].append(x)
        
    def is_edge(self,x,y):
       return (x,y) in self._cost
       
    def parse_vertices(self):
        return self._outbound_neighbours.keys()
        
    def parse_out(self, x):
        return list(self._outbound_neighbours[x])
        
    def parse_in(self, y):
        return list(self._inbound_neighbours[y])

#    def parse_in(self, y):
#        ret = []
#        for x in self._outbound_neighbours.keys():
#            if y in self._outbound_neighbours[x]:
#                ret.append(x)
#        return ret

def print_graph(g):
    print ("Outbound")
    for x in g.parse_vertices():
        s = f"{x}:"
        for y in g.parse_out(x):
            s += f" {y}"
        print(s)
    print ("Inbound")
    for x in g.parse_vertices():
        s = f"{x}:"
        for y in g.parse_in(x):
            s += f" {y}"
        print(s)

def check_performance(g):
    before = time.time()
    for x in g.parse_vertices():
        for y in g.parse_out(x):
            pass
    after = time.time()
    print(f"Outbound: {(after-before)*1000}ms")
    before = time.time()
    for x in g.parse_vertices():
        for y in g.parse_in(x):
            pass
    after = time.time()
    print(f"Inbound: {(after-before)*1000}ms")

def small_graph():
    g =  Graph(6)
    g.add_edge(0,1,1)
    g.add_edge(0,3,4)
    g.add_edge(0,5,8)
    g.add_edge(1,1,3)
    #g.add_edge(1,0,2)
    g.add_edge(1,3,2)
    g.add_edge(3,4,2)
    g.add_edge(4,5,2)
    g.add_edge(5,3,1)
    return g

def generate_dense_graph(g, n, m):
    slots_left = n*n
    edges_left = m
    for i in range(n):
        for j in range(n):
            if randint(0, slots_left-1) < edges_left:
                g.add_edge(i, j, 1)
                edges_left -= 1
            slots_left -= 1

def generate_sparse_graph(g, n, m):
    i = 0
    collisions = 0
    while i<m:
        x = randint(0,n-1)
        y = randint(0,n-1)
        if not g.is_edge(x,y):
            g.add_edge(x,y,1)
            i += 1
        else:
            collisions += 1
    print(f"Collisions = {collisions}")

def random_graph(n, m):
    before = time.time()
    g = Graph(n)
    if 2*m > n*n:
        generate_dense_graph(g, n, m)
    else:
        generate_sparse_graph(g, n, m)
    after = time.time()
    print(f"Generated in {(after-before)*1000} ms")
    return g

if __name__ == "__main__":
    #g = small_graph()
    #g = random_graph(5, 10)
    #print_graph(g)
    n = 10000
    #g = random_graph(n, n*n//2-1)
    g = random_graph(n, 10*n)
    check_performance(g)
