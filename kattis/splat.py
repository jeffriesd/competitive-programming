# problem: https://open.kattis.com/problems/splat

import sys
import math

class Circle:
    def __init__(self, x, y, v, color):
        self.x = float(x)
        self.y = float(y)
        self.v = float(v)
        self.r = (self.v / math.pi) ** .5
        self.color = color

def in_range(circle, x, y):
  d = ((circle.x - x) ** 2 + (circle.y - y) ** 2) ** .5
  return d < circle.r

def check_queries(circles, queries):
  for q in queries:
    x = q[0]
    y = q[1]
    
    color = "white"

    for c in reversed(circles):
      if in_range(c, x, y):    
        color = c.color
        break
    print(color)

 
def main():
    line_index = 0
    num_drops = 0
    num_queries = 0
    num_paintings = 0
    start_drops = 0
    start_queries = 0
    done = False 
    for line in sys.stdin:
        if line_index == 0:
          num_paintings = int(line)
        elif line_index == 1:
          num_drops = int(line)
          start_drops = line_index+1
          circles = []
        elif line_index < start_drops + num_drops:
          drop = line[:-1]
          x, y, v, c = drop.split(" ")
          c = Circle(x, y, v, c)
          circles.append(c)
        elif line_index == start_drops + num_drops:
          num_queries = int(line)
          queries = []
          start_queries = line_index+1
        elif line_index < start_queries + num_queries:
          q = line[:-1]
          x, y = q.split(" ")
          queries.append((float(x), float(y)))
          if line_index + 1 == start_queries + num_queries:
            check_queries(circles, queries)
            done = True
                                                        
                                          
        line_index += 1
        if done:
          line_index = 1
          done = False  
          
main()
