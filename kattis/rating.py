# problem: https://mausa20.kattis.com/problems/ratingproblems

N, k = map(int, input().split())

minsum = 0
maxsum = 0

for _ in range(k):
    r = int(input())
    minsum += r
    maxsum += r

for _ in range(N-k):
    minsum -= 3
    maxsum += 3


print(minsum / N , maxsum / N)

