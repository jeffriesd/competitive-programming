"""
ID: jeffrie1
LANG: PYTHON3
TASK: runround
"""

fin = open("runround.in", "r")
fout = open("runround.out", "w")

N = int(fin.readline())


def runround(n): 
    digs = list(map(int, str(n)))
    numdigs = len(digs)
    remaining = set(digs)
    if len(remaining) < numdigs:
        return False

    curind = 0
    cur = digs[curind]
    nextdig = digs[(curind + cur) % numdigs]

    for i in range(1, numdigs+1):
        cur = nextdig
        nextdig = digs[curind]
        # print("ci = {0}, cur = {1}, nd = {2}".format(curind, cur, nextdig))
        # print("nd = ", nextdig)
        
        if nextdig == 0:
            return False
    
        if nextdig in remaining:
            # print("digs = ", digs)
            # print("rem = ", remaining)
            # print()
            remaining.remove(nextdig)
        else:
            return False
        # if nextdig != digs[i]:
        #     return False
        curind = (curind + nextdig) % numdigs

    # print(curind)
    if len(remaining) or curind != 0:
        return False
    return True

while True:
    N += 1
    if runround(N):
        fout.write("{}\n".format(N))
        exit()

fout.close()

