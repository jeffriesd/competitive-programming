# problem: https://open.kattis.com/problems/bing

from collections import defaultdict

def __main__():
  n = int(input())
  word_counts = defaultdict(int)
  for _ in range(n):
    word = input()
    print(word_counts[word])
    for l in range(len(word)):
      word_counts[word[:l+1]] += 1

if __name__ == '__main__':
  __main__()
