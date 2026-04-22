from random import randint
import time
import random

from heapq import heappush, heappop

class Graph:
    def __init__ (self, n):
        self.__out_neighbors = {}
        self.__in_neighbors = {}
        self.__costs = {}
        
        for i in range(n):
            self.__out_neighbors[i] = []
            self.__in_neighbors[i] = []
            
    def add_edge(self, x, y, cost):
        self.__out_neighbors[x].append(y)
        self.__in_neighbors[y].append(x)
        self.__costs[(x, y)] = cost
        
    def parse_vertices(self):
        return self.__out_neighbors.keys()
        
    def parse_out(self, x):
        return list(self.__out_neighbors[x])
        
    def parse_in(self, x):
        return list(self.__in_neighbors[x])
        
#    def parse_in(self,y):
#        inbound_neighbors=[]
#        for x in self.__out_neighbors.keys():
#            if y in self.__out_neighbors[x]:
#                inbound_neighbors.append(x)
#        return inbound_neighbors
        
    def is_edge(self, x,y):
        return y in self.__out_neighbors[x]
            
    def cost(self, x, y):
        return self.__costs[(x, y)]

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
    added = 0
    while added < m :
        x = random.randint(0,n-1)
        y = random.randint(0,n-1)
        
        if g.is_edge(x,y):
            continue
        g.add_edge(x,y,1)
        added += 1
    after = time.time()    
    print(f"Generated: {(after-before)*1000}ms")
    return g

def test():
    g = small_graph()
    vertices = list(g.parse_vertices())
    print(f"vertices: type={type(vertices)}, members={dir(vertices)}")
    vertices.remove(1)
    print(f"vertices with property X={vertices}")
    neighbors = g.parse_out(2)
    neighbors.append(0)
    print_graph(g)
    
    
def dijkstra(g, s, t):
    """Executes Dijkstra's algorithm on graph g, with starting vertex s and stopping when reaching vertex t
    
       Returns a dictionary mapping each vertex accessible from s to the cost of the min cost walk from s to it
    """
    dist = {s:0}
    q = [s]
    
    while len(q) > 0:
        x = heappop(q)
        for y in g.parse_out(x):
            if y not in dist.keys() or dist[y] > dist[x] + g.cost(x, y):
                dist[y] = g.cost(x, y)
                heappush(q, y)
                
    

def min_cost_path_dijkstra(g, s, t):
    """Returns the path of minimum cost from s to t in graph g

    Args:
        g (_type_): _description_
        s (_type_): _description_
        t (_type_): _description_
    """
    
    dijkstra(g, s ,t)

if __name__ == "__main__":
    #test()
    #g = small_graph()
    #g = random_graph(5, 5)
    #print_graph(g)
    n = 100000
    g = random_graph(n, 10*n)
    check_performance(g)
