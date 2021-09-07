# problem: https://open.kattis.com/problems/pokerhand

from collections import defaultdict
def main():
  
  cards = input().split()

  counts = defaultdict(int)
  for c in cards:
    r, s = c
    counts[r] += 1


  print(max(counts.values()))

main()
