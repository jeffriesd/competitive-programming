"""
ID: jeffrie1
LANG: PYTHON3
TASK: namenum
"""
from collections import defaultdict
fin = open("namenum.in", "r")
fout = open("namenum.out", "w")

strNum = fin.readline().strip()
inputNum = int(strNum)


nummap = {
    "A" : 2, "B" : 2, "C" : 2,
    "D" : 3, "E" : 3, "F" : 3,
    "G" : 4, "H" : 4, "I" : 4,
    "J" : 5, "K" : 5, "L" : 5,
    "M" : 6, "N" : 6, "O" : 6,
    "P" : 7, "R" : 7, "S" : 7,
    "T" : 8, "U" : 8, "V" : 8,
    "W" : 9, "X" : 9, "Y" : 9,
}

letmap = defaultdict(list)
for k in nummap.keys():
    letmap[nummap[k]].append(k)

names = []
with open("dict.txt", "r") as dic:
    for line in dic.readlines():
        name = line.strip()
        if len(name) == len(str(strNum)):
            names.append(name)

noneValid = True
for name in names:
    fullMatch = True
    for (c, d) in zip(name, strNum):
        d = int(d)
        if not (c in letmap[d]):
            fullMatch = False
            break
    if fullMatch:
        noneValid = False
        fout.write("{0}\n".format(name))
if noneValid:
    fout.write("NONE\n")

fout.close()
