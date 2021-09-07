"""
ID: jeffrie1
LANG: PYTHON3
TASK: pprime
"""
from math import *

primes = []
prpals = []
pals   = []


def numDigs(n):
    if n == 0: 
        return 1
    digs = 0
    while n > 0:
        n //= 10
        digs += 1
    return digs

def genPrimes(n):
    sieve = [True] * (n+1)
    sieve[0] = sieve[1] = False
    i = 2
    while i * i <= n:
        if sieve[i] and i * i <= n:
            for j in range(i * i, n+1, i):
                sieve[j] = False
        i += 1
    for i in range(n+1):
        if sieve[i]:
            primes.append(i)


def catDigs(l, r):
    return pow(10,  numDigs(r)) * l + r

def genPals(n, m):
    if n > m:
        return
    pals.append(n)

    for i in range(1, 10):
        genPals(catDigs(catDigs(i, n), i), m)

    for i in range(1, 10):
        j = 1
        while True:
            x = catDigs(catDigs(i * pow(10, j),  
                                  n * pow(10, j)), i)
            if x > m: 
                break

            genPals(x, m)
            j += 1


fin = open("pprime.in", "r")
fout = open("pprime.out", "w")

a, b = map(int, fin.readline().split())

for i in range(10):
    genPals(i, b)
    if i > 0:
        genPals(catDigs(i, i), b)

genPrimes(floor(sqrt(b)))

for pal in pals:
    comp = False
    if pal < 2:
        comp = True
    for pr in primes:
        if pr * pr > pal: 
            break
        if pal % pr == 0:
            comp = True
            break
    if (not comp) and pal >= a:
        prpals.append(pal)

for p in sorted(prpals):
    fout.write("{0}\n".format(int(p)))
