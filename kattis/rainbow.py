# problem: https://open.kattis.com/problems/rainbowroads

from collections import deque
from copy import deepcopy as copy

def main():
  N = int(input())

  start_graph = {n: set() for n in range(1, N+1)}
  colors = {n: {} for n in range(1, N+1)}

  for _ in range(N-1):
    a, b, c = map(int, input().split())

    start_graph[a].add(b)
    start_graph[b].add(a)
    colors[a][b] = c
    colors[b][a] = c

  def get_problem_nodes(graph):
    problem_nodes = []
    for node in graph:
      neighbors = graph[node]

      cur_colors = [colors[node][n] for n in neighbors]
      if len(set(cur_colors)) != len(cur_colors):
        problem_nodes.append(node)
    return problem_nodes


  def get_good(graph, problem_nodes):
    subgraphs = []

    good = set(range(1, N+1))
    for node in problem_nodes:
      neighbors = graph[node]

      cur_colors = [colors[node][n] for n in neighbors]
      visited = [False] * (N+1)
      for n in neighbors:
        color = colors[node][n]
        if cur_colors.count(color) > 1:
          # prune bad subtrees
          visited[n] = True

      # determine reachable nodes
      q = []
      q.append(node)
      reachable = set()
      while q:
        cur = q.pop()
        reachable.add(cur)
        visited[cur] = True

        for neighbor in graph[cur]:
          if not visited[neighbor]:
            q.append(neighbor)

      good = good.intersection(reachable)
      if len(good) == 0:
        return good

    return good 

  g = get_good(start_graph, get_problem_nodes(start_graph))
  print(len(g))
  for n in sorted(g):
    print(n)
 
main()

