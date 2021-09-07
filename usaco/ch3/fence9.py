"""
ID: jeffrie1
LANG: PYTHON3
TASK: fence9
"""

def gcd(a, b):
    return gcd(b, a % b) if b else a

def obtuse(n, m, p):
    y = 0
    total = 0
    if n == 0:
        y = m
    else:
        for x in range(1, n+1):
            while (y+1) / x < m / n:
                y += 1
            if x < n:
                total += y

    for x in range(n, p):
        while y >= m + (x-n)*(-m/(p-n)):
            y -= 1

        if y > 0 and x > 0:
            total += y

    return total

fin = open("fence9.in", "r")
fout = open("fence9.out", "w")

N, M, P = map(int, fin.readline().split())

total = 0

if P >= N:
    total = obtuse(N, M, P)
else:
    total = obtuse(N, M, N)
    total -= obtuse(N-P, M, N-P)
    total -= gcd(M, N-P) - 1

fout.write("{0}\n".format(total))




fout.close()

