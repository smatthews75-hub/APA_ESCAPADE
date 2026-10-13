def topo_sort_dfs(G, C_v):
    visited = set()
    result = []

    # (i) Sort all vertices by cost c_v ascending for the outer loop
    sorted_vertices = sorted(G.keys(), key=lambda v: C_v[v])

    def dfs_visit(v):
        visited.add(v)
        # (ii) Sort neighbors by cost c_v ascending before exploring
        sorted_neighbors = sorted(G.get(v, []), key=lambda u: C_v[u])
        for u in sorted_neighbors:
            if u not in visited:
                dfs_visit(u)
        result.append(v) # WHY PUSH LAST ? THIS MAKES REVERSING MANDATORY ? CAN I PUSH FIRST RIGHT AFTER VISITED

    for v in sorted_vertices:
        if v not in visited:
            dfs_visit(v)

    return result[::-1]  # Reverse post-order to get topological order

# G = {
#     "3":["1", "4"],
#     "2":["1"]
# }
# C_v = {"1":2, "2":0, "3":0, "4":1} # how many edges going "in" to each node at the surface of the graph

G = {
    "3":["1", "4"],
    "2":["1"]
}
C_v = {"1":2, "2":0, "3":0, "4":1} # how many edges going "in" to each node at the surface of the graph


print(topo_sort_dfs(G, C_v)) # ['2', '3', '1', '4']