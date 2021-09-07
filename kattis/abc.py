# problem: https://open.kattis.com/problems/abc

def abc(l1, l2):
  a, b, c = sorted([int(x) for x in l1.split()])
  mapping = {"A": a, "B": b, "C": c}
  output = [mapping[x] for x in list(l2)]

  print("{0} {1} {2}".format(*output))


if __name__ == '__main__':
  l1 = input()
  l2 = input()
  abc(l1, l2)
  
    




