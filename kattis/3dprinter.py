# problem: https://open.kattis.com/problems/3dprinter

def get_neighbors(s, p, d):
  return [(s+p-i, p+i, d+1) for i in range(p+1)]

def days(pred, end):
  cur = end
  days = 0
  print(end)
  while cur != (0, 1):
    cur, move = pred[cur]
    print(cur)
    days += 1
  return days
    
def _main(goal):

  queue = [(0, 1, 0)]
  visited = set() 
  pred = {}
  
  while queue:
    s, p, d = queue[0]
    if s >= goal:
      return d
    for move, n in enumerate(get_neighbors(s, p, d)):
      if n not in visited:
        pred[n] = ((s, p), move)
        queue.append(n)
    queue = queue[1:]
    visited.add((s, p))

def main(goal):
  
  mystats = 0
  printers = 1
  days = 0

  while mystats < goal:
    if goal - mystats > printers:
      printers *= 2
    else:
      mystats += printers
    days += 1

  return days


if __name__ == '__main__':
  n = int(input())
  print(main(n))
