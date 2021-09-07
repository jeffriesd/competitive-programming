# problem: https://open.kattis.com/problems/shatteredcake

W = int(input())
N = int(input())


area = 0 
for _ in range(N):
    w, l = map(int, input().split())

    area += w * l 

print(area // W)

