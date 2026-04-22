from parse import shortest_path

_list = ['G', 'W', 'C', 'B']

class WolfGoatCabbageState:
    def __init__(self, data):
        self.data = data
    def __str__(self):
        return self.__repr__()
    def __repr__(self):
        # examples: WGCB-, WC-GB
        value = ""
        for i in _list:
            if not self.data[i]:
                value += i
        value += '-'
        for i in _list:
            if self.data[i]:
                value += i
        return value
    def __eq__(self, other):
        if not isinstance(other, WolfGoatCabbageState):
            return False
        return self.data == other.data
    def __ne__(self, other):
        return not self.__eq__(other)
    def __hash__(self):
        val = 0
        
        for item in _list:
            val *= 2
            if self.data[item]:
                val += 1
        
        return val
    
    def parse_neighbors(self):
        for item in _list:
            next_dict = dict(self.data)
            if self.data[item] == self.data['B']:
                next_dict['B'] = not next_dict['B']
                next_dict[item] = not next_dict[item]
                next_state = WolfGoatCabbageState(next_dict)
                yield next_state

class WolfGoatCabbageGraph:
    def parse_out(self, x):
        return x.parse_neighbors()
        
    def parse_in(self, y):
        return y.parse_neighbors()
 
#    def is_edge(self, x, y):
#        pass
    def initial_state(self):
        data = {
            'G': False,
            'W': False,
            'C': False,
            'B': False
        }
        
        return WolfGoatCabbageState(data)
    def final_state(self):
        data = {
            'G': True,
            'W': True,
            'C': True,
            'B': True
        }
        return WolfGoatCabbageState(data)

if __name__ == "__main__":
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    print(f"s==s: {s==s}")
    print(f"s==t: {s==t}")
    print(f"s==None: {s==None}")
    print(f"s= {s}")
    print(f"t= {t}")
    path = shortest_path(g, s, t)
    print(f"Solution: {path}")
