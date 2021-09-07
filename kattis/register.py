# problem: https://open.kattis.com/problems/register

_2 = 1
_3 = _2 *  2
_5 = _3 * 3
_7 = _5 * 5
_11 = _7 * 7
_13 = _11 * 11
_17 = _13 * 13
_19 = _17 * 17
full = _19 * 19 - 1

prlist = [_2, _3, _5, _7, _11, _13, _17, _19]

def opsleft(numlist):
  return full - sum(j * k for j, k in zip(prlist, numlist)) 

def main():
  numlist = [int(x) for x in input().split()]
  print(opsleft(numlist))

if __name__ == "__main__":
  main()
