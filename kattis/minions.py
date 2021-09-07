# problem: https://open.kattis.com/problems/airconditioned

class Node:
  def __init__(self, data, link = None):
    self.data = data
    self.link = link

class Stack:
  def __init__(self):
    self.head = None
    self.size = 0
 
  def push(self, x):
    self.head = Node(x, self.head)
    self.size += 1
  
  def pop(self):
    if self.head is None:
      return -1
    data = self.head.data
    self.head = self.head.link
    self.size -= 1
    return data 
 
  def peek(self):
    if self.head is None:
      return -1
    return self.head.data

  def print(self):
    n = self.head
    while n is not None:
      print(n.data, end=" ")
      n = n.link
    print()

  def empty(self):
    return self.head is None
    
  def size(self):
    return self.size
 
def update_ranges(new_range, ranges):
  new_x = new_range[0]
  new_y = new_range[1]
  i = 0
  #print(ranges)
  for r in ranges:
    if new_x <= r[1] and new_x >= r[0]:
      newmax = min([new_y, r[1]])
      ranges[i] = (new_x, newmax)
      #print(ranges, "new r = ",ranges[i])
      return
    i += 1
  ranges.append(new_range)

def minimum(minions):
  minions = sorted(minions)
  temps = []
  for i in range(minions.__len__()):
    if (i < minion.__len__() - 1):
      cur = minions[i]
      next = minions[i+1]
      
      for t in range(cur[0], cur[1] + 1):
        if temps.__contains__(t):
          break

def stack_min(lowers, uppers):
  rooms = 0
  lstack = Stack()
  rstack = Stack()
 
  lowers.print()
  uppers.print() 
  rstack.push(uppers.pop())
  lstack.push(lowers.pop())
 
  while not (lowers.empty() and uppers.empty()):
    if rstack.peek() >= lstack.peek():
      print("left = ", end="")
      lstack.print()
      print("right = ", end="")
      rstack.print()
      print()
      if lowers.peek() != -1:
        lstack.push(lowers.pop())
    if rstack.peek() < lstack.peek():
      print("left = ", end="")
      lstack.print()
      print("right = ", end="")
      rstack.print()
      print() 
      if (uppers.peek() != -1):
        rstack.push(uppers.pop()) 
      rooms += 1
    elif not rstack.empty():
      rstack.push(uppers.pop()) 
      rooms += 1
 
    if (lowers.size == 0 and uppers.size <= 1):
      break 
    print(lowers.size, uppers.size)
    
  return rooms 
      

def make_stacks(ranges):
  lstack = Stack()
  rstack = Stack()
  for r in reversed(ranges):
    lstack.push(int(r[0]))
    rstack.push(int(r[1]))
  
  return lstack, rstack 

def __main__():

  n = int(input())
  ranges = []
  unsorted = []
  for _ in range(n):
    x, y = input().split()
    unsorted.append((int(x), int(y)))
  sorted_order = sorted(unsorted)
  for r in sorted_order:
    update_ranges(r, ranges)
  #print(sorted_order)
  #print(ranges)
  print(ranges.__len__()) 

__main__()
