import parse

# Bits: most significant(boat)(cabbage)(goat)(wolf) least significant
class WolfGoatCabbageState:
    def __init__(self, t):
    """
    wolf goat cabbage and boat
    """
        self.state=t
    def __str__(self):
        return self.__repr__()
    def __repr__(self):
        # examples: WGCB-, WC-GB
        pass
    def __eq__(self, other):
        pass
    def __ne__(self, other):
        return not self.__eq__(other)
    def __hash__(self):
        pass
    def parse_neighbors(self):
        for i in range(4):
            
        pass

class WolfGoatCabbageGraph:
    def parse_out(self, x):
        return x.parse_neighbors()
        
    def parse_in(self, y):
        return y.parse_neighbors()
 
#    def is_edge(self, x, y):
#        pass
    def initial_state(self):
        return WolfGoatCabbageState((0,0,0,0))
    def final_state(self):
        return WolfGoatCabbageState((1,1,1,1))

if __name__ == "__main__":
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    path = parse.shortest_path(g, s, t)
    print(f"Solution: {path}")
