"""
ID: jeffrie1
LANG: PYTHON3
TASK: zerosum
"""
from collections import defaultdict


fin = open("zerosum.in", "r")
fout = open("zerosum.out", "w")

N = int(fin.readline())

S = []
for i in range(N+1):
    S.append(defaultdict(list))

# 
# S[i][j] 
#   = list of sequences summing to j
#     using integers 1..i
# max sum = sum(range(n+1))
# min sum = 1-23456789
#
# cap j at +/- N?
#

# at S[i], try extending with +i, -i
# or +/- (i-k)...(i-1)(i)

extend = [[], [1]]
for i in range(2, N+1):
    row = [i]
    for x in extend[i-1]:
        row.append(10*x + i)
    extend.append(row)



# print number with spaces
def spaced(n):
    return " ".join(str(n))

# S[i][j] = list of seqs ending with i which sum to j
#           
S[0][0] = [""]
for i in range(1, N+1):
    # try all blank (1 2 3 .. i)

    # try extending with +/- (i) up to (2...i)
    ei = i-1
    for e in extend[i]:
        # print("i = ", i , "  ei = ", ei , "  extend with " , e)
        # extend every sum 
        for j in S[ei]:
            for seq in S[ei][j]:
                # print(seq + "+" + spaced(e))
                if seq == "":
                    S[i][j+e].append(spaced(e))
                else:
                    S[i][j+e].append(seq + "+" + spaced(e))
                    S[i][j-e].append(seq + "-" + spaced(e))
        ei -= 1

for s in sorted(S[N][0]):
    fout.write("{}\n".format(s))

fout.close()

