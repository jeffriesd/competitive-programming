"""
ID: jeffrie1
LANG: PYTHON3
TASK: dualpal
"""
from math import log

def divrem(n, d):
    return (n // d, n - (d * (n // d)))

def mkDig(d):
    if d < 10:
        return d
    return chr((d - 10) + ord('A'))

def toBase(n, b):
    numStr = ""
    while n > 0:
        q, r = divrem(n, b)
        numStr = str(mkDig(r)) + numStr
        n = q
    return numStr

def pal(x):
    return list(x) == list(reversed(x))

def dualPal(x):
    numPals = 0
    for b in range(2, 11):
        if pal(toBase(x, b)):
            numPals += 1
        if numPals == 2:
            return True
    return False


fin = open("dualpal.in", "r")
fout = open("dualpal.out", "w")

n, s = map(int, fin.readline().split())

found = 0
x = s + 1
while found < n:
    if dualPal(x):
        fout.write("{0}\n".format(x))
        found += 1
    x += 1


fout.close()
