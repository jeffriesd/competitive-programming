"""
ID: jeffrie1
LANG: PYTHON3
TASK: milk2
"""
from collections import defaultdict

fin = open("milk2.in", "r")
fout = open("milk2.out", "w")

START = 0
END = 1

n = int(fin.readline())

times = []
for i in range(n):
    s, t = map(int, fin.readline().split())
    # each entry is (time, index, START/END)
    times.append((s, i, START))
    times.append((t, i, END))
fin.close()

present = set()
empty = set()
times = sorted(times, key=lambda t: t[0])

groupedTimes = defaultdict(list)
for (t, i, x) in times:
    groupedTimes[t].append((i, x))

maxPresent = 0
maxEmpty   = 0
emptyStart = times[0][0]

for t in sorted(groupedTimes.keys()):
    group = groupedTimes[t]
    startEnd = [False, False] 
    wasEmpty = not present
    for (i, x) in group:
        startEnd[x] = True
        if x is START:
            present.add(i)
        else:
            present.remove(i)

    # if this time was the end of a milking period
    # if this time was start of a milking period

    if startEnd[START] and startEnd[END]:
        pass        
    elif startEnd[START]: # only starts 
        if wasEmpty:
            start = t
            maxEmpty = max(maxEmpty, t - emptyStart)
    else:   # only ends
        if not present:
            emptyStart = t
            maxPresent = max(maxPresent, t - start)

fout.write("{0} {1}\n".format(maxPresent, maxEmpty))
fout.close()
