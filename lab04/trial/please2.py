def solve():
    N, M = map(int, input().split())
    adj = [[] for _ in range(N)]

    for _ in range(N):
        v, w = map(int, input().split())
        adj[v].append(w)
        adj[w].append(v)

    R, T = map(int, input().split())

    visited = [False] * N
    total_length = 0
    count = 0

    def dfs(node, length):
        nonlocal total_length, count
        if node == T:
            total_length += length
            count += 1
            return
        visited[node] = True
        for nxt in adj[node]:
            if not visited[nxt]:
                dfs(nxt, length+1)
        visited[node] = False

    visited[R] = True
    dfs(R, 0)

    if count == 0:
        print("N/A")
    else:
        avg = total_length/count
        print(f"{avg:.3f}")

solve()