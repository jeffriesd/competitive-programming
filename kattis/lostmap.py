# problem: https://open.kattis.com/problems/lostmap

def main():
  n = int(input())

  edges = {}

  for i in range(1, n+1):
    line = list(map(int, input().split()))
    for j in range(1, n+1):
      if i < j:
        edges[(i, j)] = line[j-1]

  sorted_edges = sorted(edges, key=lambda d: edges[d])

  current_graph = {}
  num_edges = 0

  parent =[None]
  rank = [None]

  for node in range(1, n+1):
    parent.append(node)
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

  i = 0
  while num_edges < n - 1:
    u, v = sorted_edges[i]
    w = edges[(u, v)]
    i += 1

    x = find(parent, u)
    y = find(parent, v)

    if x != y:
      num_edges += 1
      print(u, v)
      union(parent, rank, x, y)

if __name__ == '__main__':
  main()
