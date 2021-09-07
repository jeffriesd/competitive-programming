# problem: https://open.kattis.com/problems/warehouse

from collections import defaultdict

def solve():
    n = int(input())
    toys = defaultdict(int)
    for _ in range(n):
        inp = input().split()
        t = inp[0]
        c = int(inp[1])
        toys[t] += c
    
    print(len(toys.keys()))
    tups = []
    for t in toys:
        tups.append((t, toys[t]))
    
    tups = sorted(tups, key = lambda x: x[0])
    tups = sorted(tups, key = lambda x: x[1], reverse = True)
    for (t, c) in tups:
        print(t, c)

def main():         
    t = int(input())

    for _ in range(t):
        solve()


main()
