# problem: https://open.kattis.com/problems/goatrope

def main():
  gx, gy, x1, y1, x2, y2 = map(int, input().split())

  
  def dist(a, b, c, d):
    return ((c - a) ** 2 + (d - b) ** 2) ** .5


  mindist = float("inf")
  # left wall
  if gx < x1 and (gy < y2 and gy > y1):
    mindist = min(mindist, dist(gx, gy, x1, gy))
  # right wall
  if (gx > x2) and (gy < y2 and gy > y1):
    mindist = min(mindist, dist(gx, gy, x2, gy))
  # top wall
  if (gy > y2) and (gx < x2 and gx > x1):
    mindist = min(mindist, dist(gx, gy, gx, y2))   
  # bottom wall
  if (gy < y1) and (gx < x2 and gx > x1):
    mindist = min(mindist, dist(gx, gy, gx, y1))   


  # corners
  corners = [
    (x1, y1),
    (x1, y2),
    (x2, y1),
    (x2, y2),
  ]

  for x, y in corners:
    mindist = min(mindist, dist(gx, gy, x, y))

  print(mindist)

main()
