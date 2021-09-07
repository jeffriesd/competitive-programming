# problem: https://codeforces.com/contest/1073/problem/B

def main():
  n = int(input())

  idx = [None] * (n+1)
  
  maxidx = 0

  nums = list(map(int, input().split()))

  for index, n in enumerate(nums):
    idx[n] = index+1

  queries = list(map(int, input().split()))

  for q in queries:
    if idx[q] > maxidx:
      # move idx[q] things
      # print("idx[", q, "] = ", idx[q])
      print(idx[q] - maxidx, end=" ")
      maxidx = idx[q] 
      # print("max = ", maxidx)
    else:
      print(0, end=" ")
  print()


main()
