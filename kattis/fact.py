# problem: https://open.kattis.com/problems/lastfactorialdigit

from math import factorial
t = int(input())

for _ in range(t):

    n = int(input())
    print(factorial(n) % 10)
