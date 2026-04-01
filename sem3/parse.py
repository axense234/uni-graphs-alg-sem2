import graph


def bfs(g, s):
    """Performs Breadth-First search in graph g starting from vertex s.
    Precondition: s must be in the graph
    
    
    Returns:
        tuple (dist, parent): 
            dist is a dict with keys all vertices accessible from s and dist[x]
            = shortest path from parent
            
            parent is a dict with keys all vertices accessible from s and parent[x]
            = the parent of x in the BFS tree, parent[s] = None


    Args:
        g (g): Graph
        s (any): starting vertex
    """
    
    que = []
    visited = set()
    
    dist = {}
    parent = {}
    
    dist[s] = 0
    parent[s] = None
    
    que.append(s)
    visited.add(s)
    
    while len(que) > 0:
        current = que.pop(0)
        
        for next in g.parse_out(current):
            if next in visited:
                continue
            
            visited.add(next)
            que.append(next)
            
            dist[next] = dist[current] + 1
            parent[next] = current
    
    return (dist, parent)
    
    
def shortest_path(g, s, t):
    """Computes the shortest path from s to t in graph g
    Precondition: s must be in the graph
    
    Returns:
        list of vertices (representing the shortest path from vertex s to t)
        None if there is no path
    
    Args:
        g (g): Graph
        s (any): starting vertex
        t (any): dest vertex
    """
    
    path = []
    dist, parent = bfs(g, s)
    
    
    current = t
    while current != s:
        path.append(current)
        current = parent[current]
    
    if len(path) == 0:
        return None
    
    path.append(s)
    return sorted(path, reverse=False)
    
    
def test_bfs():
    g = graph.small_graph()
    dist, parent = bfs(g, 1)
    print(f"dist={dist}")
    print(f"parent={parent}")
    
    path = shortest_path(g, 1, 4);
    print(f"path={path}")
        
    
if __name__ == "__main__":
    test_bfs()