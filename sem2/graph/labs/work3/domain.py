import copy

class Graph:
    def __init__(self, num_vertices: int = 0):
        if num_vertices < 0:
            raise ValueError("Number of vertices must be non-negative")
        self._num_vertices = num_vertices
        self._next_id = num_vertices
        self._num_edges = 0
        self._cost = {}
        self._in = {}
        self._out = {}
        for i in range(num_vertices):
            self._in[i] = []
            self._out[i] = []

    def get_num_vertices(self):
        return self._num_vertices

    def get_num_edges(self):
        return self._num_edges
    # using yield for the parse function, instead of retuning a list, yield produces one value at a time when iterated
    def get_vertices(self):
        for v in self._out:
            yield v   # caller never gets a acces to internal dictionary, only see the values coming out one by one

    def get_edges(self):
        for e in self._cost:
            yield e

    def is_edge(self, x: int, y: int):
        return (x,y) in self._cost

    def get_cost(self, x: int, y: int):
        if not self.is_edge(x, y):
            raise ValueError(f"Edge ({x}, {y}) doesn't exist!")
        return self._cost[(x,y)]

    def set_cost(self, x: int, y: int, cost: int):
        if not self.is_edge(x,y):
            raise ValueError(f"Edge ({x}, {y}) doesn't exist!")
        self._cost[(x,y)] = cost

    def add_edge(self, x: int, y: int, cost: int):
        if x not in self._out or y not in self._in:
            raise ValueError(f"Vertex {x} or {y} doesn't exist!")
        if self.is_edge(x,y):
            raise ValueError(f"Edge ({x}, {y}) already exists!")
        self._cost[(x,y)] = cost
        self._in[y].append(x)
        self._out[x].append(y)
        self._num_edges += 1

    def remove_edge(self, x: int, y: int):
        if not self.is_edge(x,y):
            raise ValueError(f"Edge ({x},{y}) doesn't exist!")
        del self._cost[(x,y)]
        self._in[y].remove(x)
        self._out[x].remove(y)
        self._num_edges -= 1

    def add_vertex(self, v=None):
        if v is None: # it checks if we received an optional vertex id, if not it will create the next automatic ID
            v = self._next_id
            self._next_id += 1
        else:
            if v in self._out: # check if vertex already exists
                raise ValueError(f"Vertex {v} already exists!") # prevents duplicates
            if v >= self._next_id: # updates the atuoamtic counter so future automatic addition stay safe
                self._next_id = v + 1
        self._out[v] = []
        self._in[v] = []
        self._num_vertices += 1
        return v

    def remove_vertex(self, v: int):
        if v not in self._out:
            raise ValueError(f"Vertex {v} doesn't exist!")
        for x in list(self._out[v]):
            self.remove_edge(v, x)
        for x in list(self._in[v]):
            self.remove_edge(x, v)
        del self._out[v]
        del self._in[v]
        self._num_vertices -= 1

    def check_vertex(self, v: int):
        if v not in self._out:
            raise ValueError(f"Vertex {v} doesn't exist!")

    def in_degree(self, v: int):
        self.check_vertex(v)
        return len(self._in[v])

    def out_degree(self, v: int):
        self.check_vertex(v)
        return len(self._out[v])

    def outbound(self, v: int):
        self.check_vertex(v)
        for y in self._out[v]:
            yield y

    def inbound(self, v: int):
        self.check_vertex(v)
        for y in self._in[v]:
            yield y

    def copy(self):
        return copy.deepcopy(self)

    # this is how the graph its treated as undirected, by combining the in and out neighbors
    def neighbors(self, v:int):
        self.check_vertex(v)
        result = []
        seen = set()

        for y in self._out[v]:
            if y not in seen:
                seen.add(y)
                result.append(y)
        for y in self._in[v]:
            if y not in seen:
                seen.add(y)
                result.append(y)

        return result



