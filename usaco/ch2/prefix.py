"""
ID: jeffrie1
LANG: PYTHON3
TASK: prefix
"""

fin = open("prefix.in", "r")
fout = open("prefix.out", "w")

lines = "".join(fin.readlines())

primitives, sequence = lines.split(".")

sequence = "".join([s.strip() for s in sequence.split()])
primitives = [p.strip() for p in primitives.split()]

S = [False] * (len(sequence)+1)

def match(i, s, t):
    for (ti, tc) in enumerate(t):
        if i+ti > len(s): 
            return False
        if s[i+ti] != tc:
            return False
    return True

lens = []
P = len(primitives)
for p in primitives:
    l = len(p)
    lens.append(l)
    if match(0, sequence, p):
        S[l] = True

maxind = 0
for i in range(1, len(sequence)+1):
    for j in range(P):
        if i - lens[j] <= 0:
            continue
        if S[i-lens[j]] and match(i-lens[j], sequence, primitives[j]):
            maxind = max(maxind, i)
            S[i] = True
            break

fout.write("{}\n".format(maxind))

fout.close()

