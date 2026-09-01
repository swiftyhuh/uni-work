from random import randint
import time
import random

class Graph:
    def __init__(self, n:int):
        self.graph_list_outbound = {}
        self.graph_list_inbound = {}
        self.costs = {}
        for i in range(n):
            self.graph_list_outbound[i] = []
            self.graph_list_inbound[i] = []
            
    def add_edge(self, x, y, cost):
        '''If x or y (or both) do not exist as vertices, they are inserted.
            If (x,y) is already an edge, the cost is updated
        '''
        if x in self.graph_list_outbound.keys():
            if y not in self.graph_list_outbound[x]:
                self.graph_list_outbound[x].append(y)
        else:
            self.graph_list_outbound[x] = [y]
            
        if y in self.graph_list_inbound.keys():
            if x not in self.graph_list_inbound[y]:
                self.graph_list_inbound[y].append(x)
        else:
            self.graph_list_inbound[y] = [x]
    
        self.costs[(x,y)] = cost
        
    def parse_vertices(self):
        return self.graph_list_outbound.keys()

    def parse_out(self, x):
        return [y for y in self.graph_list_outbound[x]]
        
    def parse_in(self, y):
        return list(self.graph_list_inbound[y])
    
    def parse_in_old(self, x):
        result = []
        for (candidate_vertex, neighbors) in self.graph_list_outbound.items():
            if x in neighbors:
                result.append(candidate_vertex)
        return result
        
    def is_edge(self, x, y):
        return y in self.graph_list_outbound[x]
    
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
    g.add_edge(1,0,2)
    g.add_edge(1,3,2)
    g.add_edge(3,4,2)
    g.add_edge(4,5,2)
    g.add_edge(5,3,1)
    return g

def small_graph2():
    g =  Graph(['a', 'b', 'c'])
    g.add_edge('a', 'b', 1)
    g.add_edge('b', 'a', 4)
    g.add_edge('a', 'c', 8)
    g.add_edge('b', 'c', 3)
    return g

def random_graph(n, m):
    g = Graph(n)
    before = time.time()
    
    counter = 0
    while counter < m:
        x = randint(0, n-1)
        y = randint(0, n-1)
        
        if not g.is_edge(x, y):
            g.add_edge(x, y, 1)
            counter += 1
        
        
        
    after = time.time()
    print(f"Generated: {(after-before)*1000}ms")
    return g

if __name__ == "__main__":
    # g = small_graph()
    # g = random_graph(5, 10)
    # print_graph(g)
    n = 100000
    #g = random_graph(n, n*n)
    g = random_graph(n, 10*n)
    check_performance(g)
