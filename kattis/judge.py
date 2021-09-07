# problem: https://nadc21.kattis.com/problems/youbethejudge

from collections import defaultdict 
import sys

string = ""

def base10(nstr):
    for i in range(0,10):
        nstr = nstr.replace(str(i), "")
    return nstr == ""

def primes(n):
    # from https://www.geeksforgeeks.org/python-program-for-sieve-of-eratosthenes/
    if n == 0:
        return False
    if n == 1: 
        return False 
    if n == 2: 
        return True

    prime = defaultdict(lambda : True)
    prime[0] = False
    prime[1] = False 
    p = 2
    while p * p <= n:
        if prime[p]:
            for i in range(p, n+1, p):
                prime[i] = False
        p += 1

    return prime

def isprime(n):
    if n < 2: 
        return False
    if n == 2:
        return True

    for d in range(2, int(n ** .5) + 2):
        if d >= n: 
            break
        if n % d == 0:
            return False
    return True

def solve(string):
    xs = string.split()
    if len(xs) != 3:
        print(0)
        return 

    a, b, c = xs

    if base10(a) and base10(b) and base10(c):
        sa, sb, sc = a , b, c
        try:
            a = int(a)
        except:
            print(0)
            return
        try:
            b = int(b)
        except:
            print(0)
            return

        try:
            c = int(c)
        except:
            print(0)
            return

        # check for leading zeros 
        if len(sa) != len(str(int(sa))):
            print(0)
            return
        if len(sb) != len(str(int(sb))):
            print(0)
            return
        if len(sc) != len(str(int(sc))):
            print(0)
            return



        if (a <= 3) or (a > 10**9) or (a % 2 == 1):
            print(0) 
            return 
        if isprime(b) and isprime(c) and (a == b + c):
            print(1)
            return
        else:
            print(0)
            return
    else:
        print(0)
        return


ln = 0
for line in sys.stdin:
    ln += 1
    string += " " + line.strip()

solve(string)

