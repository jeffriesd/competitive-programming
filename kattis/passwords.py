# problem: https://open.kattis.com/problems/password

import sys


def __main__():
  n = int(input())
  exp = 0.0

  probs = []
  for i in range(n):
    p, prob = input().split(" ")
    probs.append(float(prob))
  i = 1
  for prob in reversed(sorted(probs)):
    exp += i * prob
    i += 1
  print(exp)  

 
__main__() 
