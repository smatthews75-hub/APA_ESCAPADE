# import sys
# from functools import lru_cache

# sys.setrecursionlimit(200005)

# def input(): return sys.stdin.readline().rstrip('\r\n')
# # input = sys.stdin.readline

# def input(): return sys.stdin.readline().rstrip('\r\n')
# # input = sys.stdin.readline

# def knapsack_topdown(minimal_protein: int, N: int, values: list[int], weights: list[int]):
#     # Using lru_cache with primitive integers

#     @lru_cache(maxsize=None)
#     def recursive(k: int, c: int) -> int:
#         # Base case
#         if k == 0: return 0, 0
#         # convert k currently considered items to 0 indexed 0 to N - 1
#         i = k - 1
#         # Option 1: do not take the current item
#         skip = recursive(k - 1, c)
#         # Cannot take the item if it's below the minimal protein required
#         if weights[i] > c: return skip
#         # Option 2: take the current item
#         take = values[i] + recursive(k - 1, c - weights[i])
#         return min(take, skip), taken

#     least_proteins, taken_foods = recursive(N, minimal_protein)
#     print(least_proteins, taken_foods)

# def solve():
#     N, P = tuple(map(int, input().split()))
#     food_names = [] # Descending order of favoritism, first is most favorite I FUCKING HATE LEXICOGRAPHIC CONSTRAINT
#     calories = [] # MINIMIZE
#     proteins = [] # AT LEAST P proteins

#     for _ in range(N):
#         text = input().split()
#         food_names.append(text[0])
#         calories.append(int(text[1]))
#         proteins.append(int(text[2]))
    
#     knapsack_topdown(P, N, calories, proteins)



# solve()

best_cals = float('inf')
best_mix = None
best_protein = -1

def all_(index, CAL, PRO, curr_sub, foods, target_PRO):
    global best_cals, best_mix, best_protein
    
    if index == len(foods):
        if PRO >= target_PRO:
            if CAL < best_cals:
                best_cals = CAL
                best_mix = list(curr_sub)
                best_protein = PRO

            elif CAL == best_cals:
                if curr_sub < best_mix:
                    best_mix = list(curr_sub)
                    best_protein = PRO
        return

    all_(index+1 , CAL, PRO, curr_sub, foods, target_PRO)

    nama, kalori, protein = foods[index]
    if CAL + kalori < best_cals:
        curr_sub.append(index)
        all_(index+1, CAL + kalori, PRO + protein, curr_sub, foods, target_PRO)
        curr_sub.pop() 

baris_pertama = input().split()
N = int(baris_pertama[0])
P = int(baris_pertama[1])

foods = []
for i in range(N):
    data = input().split()
    nama = data[0]
    kalori = int(data[1])
    protein = int(data[2])
    foods.append((nama, kalori, protein))
#print(foods)

all_(0, 0, 0, [], foods, P)

if best_mix is None:
    print("MUSTAHIL")
else:
    print(f"{best_cals} {len(best_mix)}")
    for idx in best_mix:
        print(foods[idx][0])