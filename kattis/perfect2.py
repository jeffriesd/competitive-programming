# problem: https://open.kattis.com/problems/perfectpowers


from collections import defaultdict
from functools import reduce
from math import *

def prod(xs):
  return reduce(lambda x,y:x*y, xs, 1)

def f(x, c, n):
  return (x * x + c) % n

def gcd(a, b):
  if b == 0:
    return a
  return gcd(b, a % b)

def isPrime(n):
  if n in {2, 3, 5, 7}:
    return True
  if n % 2 == 0: 
    return False
  if n % 3 == 0: 
    return False
  if n % 5 == 0: 
    return False
  if n % 7 == 0: 
    return False
  return True

def gcdOdd(start, counts):
  p = start
  while p >= 1:
    if p % 2 == 0:
      p -= 1
      continue
    common = True
    for c in counts:
      if c % p != 0:
        common = False
        break
    if common:
      break
    p -= 1
  return p
   

def findFactors(n):
  factors = defaultdict(int)
  f = 2
  while f * f <= n:
    while n % f == 0:
      factors[f] += 1
      n /= f
    f += 1

  if n > 1:
    factors[n] += 1

  return factors

def solve():
  y = int(input())
  neg = y < 0 
  y = abs(y)
  if y == 0: 
    exit(0)
  factors = findFactors(y)
  counts = list(factors.values())

  p = int(ceil(log(y, 2)))
  while p >= 1:
    divs = True
    for c in counts:
      if c % p != 0:
        divs = False
        break
    if divs and not neg:
      break
    if divs and neg and p % 2 == 1:
      break
    p -= 1

  print(int(p))
  

def main():
  while True:
    solve() 

if __name__ == '__main__':
  main()
