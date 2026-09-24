def DFS(N, pos, val, path, A):
    if pos >= N:
        yield path, val
        return

    new_val = val + A[pos]
    new_path = path + [pos]

    yield from DFS(N, pos + 1, new_val, new_path, A)
    if pos + 1 < N:
        yield from DFS(N, pos + 3, new_val, new_path, A)

N = int(input())
A = list(map(int, input().split()))
values = []
for idx, (path, val) in enumerate(DFS(N, 0, 0, [], A), start=1):
    path_str = '->'.join(map(str, path))
    values.append(val)
    print(f"Route #{idx}: {path_str}->F; value = {val}.")

index_ = values.index(max(values)) + 1
print(f"Best: Route #{index_} with value {max(values)}.")