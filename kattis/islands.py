# problem: https://open.kattis.com/problems/islands 

import sys

class Node:
  def __init__(self, data, link=None):
    self.data = data
    self.link = link

class Stack:
  def __init__(self):
    self.head = None

  def push(self, e):
    self.head = Node(e, self.head)

  def pop(self):
    data = self.head.data
    self.head = self.head.link
    return data

  def peek(self):
    if self.head is None:
      return 0
    return self.head.data

  def print(self):
    cur = self.head
    while cur is not None:
      print(cur.data, end=" ")
      cur = cur.link
    print()

def islands(seq):
  islands = 0
  stack = Stack()
  prev_highest = 2000
  for i in seq:
    prev_highest = 2000
    while stack.peek() > i:
      p = stack.pop()
      if p < prev_highest:
        #print("  new prev_high = %s" % p)
        prev_highest = p
        islands += 1
      #print("stack = ", end=" ")
      #stack.print()
    stack.push(i)

  return islands


def main():
  num_cases = int(input())

  for _ in range(num_cases):
    line = input().split(" ")
    k = int(line[0])
    seq = [int(x) for x in line[1:]]
    print(k, islands(seq))

main()
    
