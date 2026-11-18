import sys

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

N = int(input())

poverty_rates = []
for _ in range(N): poverty_rates.append(int(input()))

def calc(poverty_rates:list):
    bunsauce = [1] * N
    prev = poverty_rates[0]
    for i in range(1, N):
        current = poverty_rates[i]
        if prev < current: bunsauce[i] = bunsauce[i - 1] + 1
        prev = current

    prev = poverty_rates[-1]
    for i in range(N - 2, -1, -1):
        current = poverty_rates[i]
        if current > prev and bunsauce[i] <= bunsauce[i + 1] : 
            bunsauce[i] = bunsauce[i + 1] + 1
        prev = current

    return sum(bunsauce)

print(calc(poverty_rates))