import sys

sys.setrecursionlimit(200005)

def input(): return sys.stdin.readline().rstrip('\r\n')

def DFS_recursive(treasures_, options_):
    best_leaf = None
    best_total = -sys.maxsize

    current_visited = [0]
    current_jumps = []

    n = len(treasures_)

    def dfs(current_index, current_total):
        nonlocal best_leaf, best_total

        has_next = False

        # Explore all possible next jump options
        for jump in options_:
            next_index = current_index + jump

            # Skip out of bound next jumps
            if next_index < 0 or next_index >= n:
                continue

            # Now it is guaranteed to have next jumps
            has_next = True

            # Set the current progress
            current_visited.append(next_index)
            current_jumps.append(jump)

            # DEPTH FIRST SEARCH TO REACH CHILD NODES
            dfs(
                next_index,
                current_total + treasures_[next_index]
            )

            # When it reaches here undo the progress
            # to search for other child nodes
            current_visited.pop()
            current_jumps.pop()

        # If it reaches a child node where it can't jump anywhere else
        if not has_next:
            if current_total > best_total:
                best_total = current_total

                # Important:
                # We need to COPY the winning path.
                best_leaf = (
                    current_visited[:],
                    current_jumps[:]
                )

    dfs(0, treasures_[0])

    if best_leaf is None:
        return [], [], 0

    visited_sequence, jump_sequence = best_leaf

    return visited_sequence, jump_sequence, best_total


def solve():
    # get the treasure map
    n_ = int(input())
    treasures_ = list(map(int, input().split()))
    # get the jump options
    opt_ = int(input())
    options_ = list(map(int, input().split()))

    def print_res(treasures_, visited_sequence, jump_sequence, total):
        for node in visited_sequence: print(f"[{node}]:{treasures_[node]}", end=" ")
        print()
        for jump in jump_sequence: print(jump, end=" ")
        print()
        print(f"Max treasures : {total}")

    visited_sequence, jump_sequence, total = DFS_recursive(treasures_, options_)
    print_res(treasures_, visited_sequence, jump_sequence, total)


if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()