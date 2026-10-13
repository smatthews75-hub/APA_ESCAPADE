def DFS(N, pos, val, path, A, options, results):
    # Base case: Reached or passed the end of the board
    if pos >= N:
        results.append((path, val))
        return

    new_val = val + A[pos]
    new_path = path + [pos]

    # Explore all arbitrary jump options
    for jump in options:
        # 1. Take the jump
        new_pos = pos + jump
        DFS(N, new_pos, new_val, new_path, A, options, results)
        
        # 2. The Out-of-Bounds Check (Pruning):
        # If this current jump was large enough to cross the finish line (pos >= N),
        # we immediately break. Because the options are sorted, all subsequent jumps
        # are guaranteed to be even larger, which would just create duplicate routes.
        if new_pos >= N: break

N = int(input())
A = list(map(int, input().split()))

# You can now define arbitrarily many jump options here
options = [1, 3] 

# CRITICAL: The options must be sorted ascending for the `break` pruning logic to work
options.sort()

all_routes = []
DFS(N, 0, 0, [], A, options, all_routes)

values = []
for idx, (path, val) in enumerate(all_routes, start=1):
    path_str = '->'.join(map(str, path))
    values.append(val)
    print(f"Route #{idx}: {path_str}->F; value = {val}.")

index_ = values.index(max(values)) + 1
print(f"Best: Route #{index_} with value {max(values)}.")