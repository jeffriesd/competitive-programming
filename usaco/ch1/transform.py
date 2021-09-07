"""
ID: jeffrie1
LANG: PYTHON3
TASK: transform
"""
from math import sqrt

def rot90(sq):
    rotinds = []
    n = int(sqrt(len(sq)))
    i = 0
    for i in range(n):
        for j in range(n-1, -1, -1):
            rotinds.append(j*n + i)
    return [sq[i] for i in rotinds]
def rot180(sq):
    return rot90(rot90(sq))
def rot270(sq):
    return rot90(rot180(sq))
def refl(sq):
    rotinds = []
    n = int(sqrt(len(sq)))
    for i in range(n):
        for j in range(n-1, -1, -1):
            rotinds.append(j + i*n)
    return [sq[i] for i in rotinds]
def comb1(sq):
    return rot90(refl(sq))
def comb2(sq):
    return rot180(refl(sq))
def comb3(sq):
    return rot270(refl(sq))
def none(sq):
    return sq

fin = open("transform.in", "r")
fout = open("transform.out", "w")

n = int(fin.readline())
sq1 = [c for _ in range(n) for w in fin.readline().strip() for c in w]
sq2 = [c for _ in range(n) for w in fin.readline().strip() for c in w]


ans = 7
for (i, fs) in enumerate([[rot90], [rot180], [rot270], [refl], [comb1, comb2, comb3], [none]]):
    for f in fs:
        if sq2 == f(sq1):
            fout.write("{0}\n".format(i+1))
            exit()

fout.write("{0}\n".format(7))
fout.close()
