"""
ID: jeffrie1
LANG: PYTHON3
TASK: preface
"""

from collections import defaultdict

fin = open("preface.in", "r")
fout = open("preface.out", "w")

N = int(fin.readline())

# defined up to 3500
def roman(digs):
    # print("digs = ", digs)
    if digs == []:
        return ""
    # goal = 1708
    #        
    # grab first digit
    
    digset = { 1: ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"],
               2: ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"],
               3: ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"],
               4: ["", "M", "MM", "MMM"]
             }
    ndigs = len(digs)

    return digset[ndigs][digs[0]] + roman(digs[1:])

counts = defaultdict(int)
for i in range(1, N+1):
    for c in roman(list(map(int, str(i)))):
        counts[c] += 1

for c in ["I", "V", "X", "L", "C", "D", "M"]:
    if counts[c]:
        fout.write("{0} {1}\n".format(c, counts[c]))

fout.close()

