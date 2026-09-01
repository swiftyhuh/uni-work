from parse import shortest_path

class WolfGoatCabbageState:
    # self.data = bit pattern: bit 0 (rightmost) -> wolf, bit 1 -> goat, bit 2 -> cabbage, bit 3 -> boat
    def __init__(self, data):
        self.data = data
    def __str__(self):
        return self.__repr__()
    def __repr__(self):
        # examples: WGCB-, WC-GB
        items = "WGCB"
        ret = ""
        for i in range(4):
            if ((self.data >> i) & 1) == 0:
                ret += items[i]
        ret += "-"
        for i in range(4):
            if ((self.data >> i) & 1) == 1:
                ret += items[i]
        return ret

    def __eq__(self, other):
        if not isinstance(other, WolfGoatCabbageState):
            return False
        return self.data == other.data
    def __ne__(self, other):
        return not self.__eq__(other)
    def __hash__(self):
        return self.data
    def is_valid(self):
        # boat and goat are on the same side:
        if ((self.data >> 1) & 1) == ((self.data >> 3) & 1):
            return True
        # wolf and goat are on the same side:
        if ((self.data >> 1) & 1) == ((self.data >> 0) & 1):
            return False
        # cabbage and goat are on the same side:
        if ((self.data >> 1) & 1) == ((self.data >> 2) & 1):
            return False
        return True
    def parse_neighbors(self):
        for i in range(4):
            if ((self.data >> i) & 1) == ((self.data >> 3) & 1):
                next = WolfGoatCabbageState(self.data ^ ((1 << i) | (1 << 3)))
                if next.is_valid():
                    yield next

class WolfGoatCabbageGraph:
    def parse_out(self, x):
        return x.parse_neighbors()
        
    def parse_in(self, y):
        return y.parse_neighbors()
 
#    def is_edge(self, x, y):
#        pass
    def initial_state(self):
        return WolfGoatCabbageState(0)
    def final_state(self):
        return WolfGoatCabbageState(15)

if __name__ == "__main__":
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    print(f"s={s}")
    print(f"t={t}")
    path = shortest_path(g, s, t)
    print(f"Solution={path}")
