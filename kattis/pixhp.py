# problem: https://open.kattis.com/problems/pixelated

from collections import defaultdict

def main():
    n = int(input())

    sh = defaultdict(int)
    eh = defaultdict(int)
    sv = defaultdict(int)
    ev = defaultdict(int)
    
    inds = set()
    endps = []
    for _ in range(n):
        inp = input().split()
        d = inp[0]
        t, m, a = map(int, inp[1:])

        endps.append((d, t, m, a))
        if d == 'h':
            sh[a + 2 - m - t] += 1
            eh[a + 1 - t] += 1
            inds.add(a + 2 - m - t)
            inds.add(a + 1 - t)
        else:
            j = a - t + 1 
            sv[j - m + 1] += 1
            ev[j] += 1
            inds.add(j - m + 1)
            inds.add(j)
    
    inds = sorted(inds)

    numH = numV = 0
    activated = 0

    for i in inds:
       activated += numH * sv[i]
       numV += sv[i]
       activated += numV * sh[i]
       numH += sh[i]

       numV -= ev[i]
       numH -= eh[i]

    print(activated)

if __name__ == '__main__':
    main()
