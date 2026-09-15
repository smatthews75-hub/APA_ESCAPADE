import sys

sys.setrecursionlimit(200005)

def input(): return sys.stdin.readline().rstrip('\r\n')

def build_result(pool, leaf_node):
    if leaf_node == -1: return [], [], 0

    idx, total, parent, jump = pool[leaf_node]

    visited_sequence = []
    jump_sequence = []

    cur = leaf_node

    while cur != -1:
        idx, _, parent, jump = pool[cur]

        visited_sequence.append(idx)

        if parent != -1: jump_sequence.append(jump)

        cur = parent

    visited_sequence.reverse()
    jump_sequence.reverse()

    return visited_sequence, jump_sequence, total

def update_best_leaf(best_leaf, best_total, candidate_leaf, candidate_total):
    """
    Same strict-greater semantics as the C++ version.

    Ties keep whichever leaf was found first.
    """
    if candidate_total <= best_total: return best_leaf, best_total

    return candidate_leaf, candidate_total


def DFS_stack(treasures_:list, options_:list):
    # treasure_idx, total, parent, jump_action
    pool = [(0, treasures_[0], -1, 0)]
    best_leaf = -1 # start with none
    best_total = -sys.maxsize # start with minimal

    # Python list is naturally stack.
    traversal_stack = [0] # pool index

    n = len(treasures_)

    while traversal_stack:
        current_pool_idx = traversal_stack.pop()

        current_idx, current_total, _, _ = pool[current_pool_idx]

        has_next = False

        # Explore all possible next jump options
        for jump in options_:
            next_index = current_idx + jump

            # Skip out of bound next jumps
            if next_index < 0 or next_index >= n:
                continue

            # Now it is guaranteed to have next jumps
            has_next = True

            # Record the next step as a child of current_pool_idx.
            # O(1), no path copy.
            pool.append((
                next_index, # next index to be checked, the child
                current_total + treasures_[next_index], # next treasure size
                current_pool_idx, # record parent
                jump # record teh jump action
            ))

            traversal_stack.append(len(pool) - 1)

        # If it reaches a child node where it can't jump anywhere else
        if not has_next:
            best_leaf, best_total = update_best_leaf(
                best_leaf,
                best_total,
                current_pool_idx,
                current_total
            )

    return build_result(pool, best_leaf)


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

    visited_sequence, jump_sequence, total = DFS_stack(treasures_, options_)
    print_res(treasures_, visited_sequence, jump_sequence, total)


if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()