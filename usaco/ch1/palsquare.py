"""
ID: jeffrie1
LANG: PYTHON3
TASK: palsquare
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


fin = open("palsquare.in", "r")
fout = open("palsquare.out", "w")

b = int(fin.readline())

for i in range(1, 301):
    ps = toBase(i*i, b)
    if pal(ps):
        fout.write("{0} {1}\n".format(toBase(i, b), ps))

fout.close()
