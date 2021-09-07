# problem: https://open.kattis.com/problems/golombrulers


import sys
from itertools import combinations

def all_combos(nums):
  combos = []
  size = nums.__len__()
  for i in range(size):
    for j in range(i, size):
      if i == j:
        continue
      combos.append((nums[i], nums[j]))
  return combos

def ruler(nums):
  
  maxval = max(nums)
  check = {i+1:False for i in range(maxval)}

  num_gotten = 0

  for x, y in all_combos(nums): 
    dist = abs(x - y)
    if check[dist]:
      return "not a ruler"
    else:
      check[dist] = True
      num_gotten += 1

  if num_gotten == maxval:
    return "perfect"

  m = "missing "
  for d in check:
    if not check[d]:
      m += str(d) + " "
  return m[:-1]

def __main__():
  for line in sys.stdin:
    strs = line.split(" ")
    ints = [int(x) for x in strs]
    print(ruler(ints)) 
__main__()
