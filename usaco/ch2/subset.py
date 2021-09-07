"""
ID: jeffrie1
LANG: PYTHON3
TASK: subset
"""


fin = open("subset.in", "r")
fout = open("subset.out", "w")

N = int(fin.readline())

sumn = [0, 1]
for i in range(2,N+1):
    sumn.append(sumn[i-1]+i)

if sumn[N] % 2 == 1:
    fout.write("{}\n".format(0))
    exit()

S = []
for _ in range(N+1):
    S.append([0] * (sumn[N]+1))

def getS(i, j):
    if i < 1 or i > N or j < 0 or j > sumn[N]:
        return 0
    return S[i][j]

S[1][0] = 0
S[1][1] = 1
for j in range(2, sumn[N]+1):
    S[1][i] = 0
for i in range(2, N+1):
    S[i][1] = 1

for i in range(2, N+1):
    for j in range(2, sumn[N]+1):
        S[i][j] = getS(i-1, j-i) + getS(i-1, j)


fout.write("{}\n".format(S[N][sumn[N] // 2]))
fout.close()


