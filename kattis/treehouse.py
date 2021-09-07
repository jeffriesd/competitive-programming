# problem: https://open.kattis.com/problems/treehouses

from collections import defaultdict

G = 0
def main():
  n, e, p = map(int, input().split())

  edges = defaultdict(list)
  treehouses = {}
  
  for i in range(1,n+1):
    if i <= e:
      edges[G].append((i, 0))
    x, y = map(float, input().split())
    treehouses[i] = x, y

  def dist(a, b, c, d):
    return ((c - a) ** 2 + (d - b) ** 2) ** .5
    
  for i in range(1, p+1):
    a, b = map(int, input().split())

    xa, ya = treehouses[a]
    xb, yb = treehouses[b]
    d = dist(xa, ya, xb, yb)
    
    edges[a].append((b, d))
    edges[b].append((a, d))

  components = {}
  comp_indices = []
  def bfs(start, visited, comp_idx):

    q = [start]

    while q:
      cur = q.pop()
      visited[cur] = True
      components[cur] = comp_idx
      
      for neighbor, cost in edges[cur]:
        if not visited[neighbor]:
          q.append(neighbor)

  global_visited = [False] * (n + 1)
  all_visited = False
  comp_idx = 0
  for i in range(G, n+1):
    if not global_visited[i]:
      bfs(i, global_visited, comp_idx)
      comp_idx += 1

  
  sorted_edges = []
  for i in range(1, n+1):
    for j in range(i+1, n+1):
      if components[i] != components[j]:
        xi, yi = treehouses[i]
        xj, yj = treehouses[j]

        d = dist(xi, yi, xj, yj)
        ci = components[i]
        cj = components[j]
        sorted_edges.append((ci, cj, d))
  sorted_edges = sorted(sorted_edges, key=lambda e: e[2])

  # compute min spanning tree 
  num_edges = 0

  parent = []
  rank = []

  for comp in range(0, comp_idx):
    parent.append(comp)
    rank.append(0)

  def find(parent, i):
    if parent[i] == i:
      return i
    return find(parent, parent[i])

  def union(parent, rank, x, y):
    xroot = find(parent, x)
    yroot = find(parent, y)
    if rank[xroot] < rank[yroot]:
      parent[xroot] = yroot
    elif rank[xroot] > rank[yroot]:
      parent[yroot] = xroot

    else:
      parent[yroot] = xroot
      rank[xroot] += 1
  
  num_comp = comp_idx - 1

  i = 0
  total_d = 0
  while num_edges < num_comp:
    u, v, d = sorted_edges[i]
    i += 1

    x = find(parent, u)
    y = find(parent, v)

    if x != y:
      num_edges += 1
      union(parent, rank, x, y)
      total_d += d
  print(total_d)

main()
