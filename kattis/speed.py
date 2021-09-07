# problem: https://open.kattis.com/problems/speedlimit

import sys

for line in sys.stdin:
  spl = line.split(" ")
  if len(spl) == 1:
    n = int(spl[0])
    if n == -1:
      break
    d = 0
    last_t = 0
    for i in range(n):
      s, t = input().split(" ")
      s = int(s)
      t = int(t)
      dt = t - last_t
      d += s * dt  
      last_t = t

    print(d, "miles")
