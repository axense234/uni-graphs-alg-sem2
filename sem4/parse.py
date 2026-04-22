import graph

def bfs(g, s):
    '''Performs Breadth-First search in graph g starting from vertex s.
        Returns a tuple (dist, parent) where:
          dist is a dictionary with keys all vertices accessible from s and dist[x] = length of shodtest path from s to x
          parent is a dictionary with keys all vertices accessible from s and parent[x] = the parent of
            x in the BFS tree; parent[s] = None
        Precondition: s is a vertex of graph g
    '''
    dist = {}
    parent = {}
    
    que = []
    visited = set()
    dist[s]=0
    parent[s] = None
    que.append(s);
    visited.add(s);
    
    while len(que) > 0:
        current = que.pop(0);
        
        for next in g.parse_out(current):
            if next in visited:
                continue

            visited.add(next);
            que.append(next);
            dist[next]=dist[current]+1
            parent[next] = current
    
    return (dist, parent)

def shortest_path(g, s, t):
    '''Returns a list of vertices representing the shortest (min len) path from s to t in graph g.
        Returns None if there is no path.
        Precondition: s and t are vertices in graph g.
    '''
    dist,parent=bfs(g,s)
    if t not in parent.keys():
        return None
    current_vertex=t
    path=[]
    path.append(t)
    while current_vertex!=s:
        current_vertex=parent[current_vertex]
        path.append(current_vertex)
    path.reverse()
    return path
        
def test_bfs():
    g = graph.small_graph()
    dist, parent = bfs(g, 1)
    print(f"dist={dist}")
    print(f"parent={parent}")
    path = shortest_path(g, 5,0)
    print(f"Path={path}")

if __name__ == "__main__":
    test_bfs()
