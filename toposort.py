def topo_sort_dfs(G, V):
    visited = set()
    result = []

    # (i) Sort all vertices by cost c_v ascending for the outer loop
    sorted_vertices = sorted(G.keys(), key=lambda v: V[v])

    def dfs_visit(v):
        visited.add(v)
        # (ii) Sort neighbors by cost c_u ascending before exploring
        sorted_neighbors = sorted(G.get(v, []), key=lambda u: V[u])
        for u in sorted_neighbors:
            if u not in visited:
                dfs_visit(u)
        result.append(v)

    for v in sorted_vertices:
        if v not in visited:
            dfs_visit(v)

    return result[::-1]  # Reverse post-order to get topological order

G = {
    "3":["1", "4"],
    "2":["1"]
}
V = {"1":2, "2":0, "3":0, "4":1} # how many edges going "in" to each node at the surface of the graph

print(topo_sort_dfs(G, V)) # ['2', '3', '1', '4']