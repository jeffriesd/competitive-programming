// problem: https://open.kattis.com/problems/collusionontwowheels
//
// input: int N, N lines each with a 2d coordinate
//
// current solution: 
// - build complete undirected 
//   graph with the N points as nodes
//   and edge weights as manhattan distance
//   - O(N^2) because all pairwise points 
//
// - compute max distance md
//
// - binary search from 0 to md 
//   for minimum diameter of 
//   partitioned graphs
//   - each step of binary search 
//   involves O(N) bipartite check
//
// complexity: O(N^2 + N * log md) 
//
// further optimization: 
// - instead of binary searching
//   from 0 to md, could we 
//   just binary search among N things? 
//   - we could sort the edge weights
//     and binary search them. 
//   - this gives O(N^2 + N * log (N^2))
//              = O(N^2 + N * log N)
//     which is better when the 
//     order of magnitude of N 
//     is less than that of the max 
//     distance/edge weight

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define WHITE 1
#define BLACK 2

// number of customers
int N;

// manhattan distance between two points 
int taxi(int x1, int y1, int x2, int y2) {
  int dx = abs(x1 - x2);
  int dy = abs(y1 - y2);
  return dx + dy;
}

// manhattan distance between two pair<int> 
int taxip(pi p1, pi p2) {
  return taxi(p1.first, p1.second, p2.first, p2.second);
}

// is it possible to bicolor this graph?
bool _bicolor(vvi & adj, vi & visited, int i, int cl) {
  // visited[i] = 0 -- unvisited
  // visited[i] = 1 -- visited, colored white
  // visited[i] = 2 -- visited, colored black 
  visited[i] = cl;
  for (int nb : adj[i]) {
    if (! visited[nb]) 
      if (! _bicolor(adj, visited, nb, (WHITE + BLACK) - cl))
        return false;
    if (visited[nb] == cl) 
      return false;
  }
  return true;
}

// is it possible to bicolor this graph?
bool bicolor(vvi & adj) {
  vi visited (N, 0);
  // need to iterate through all nodes because there 
  // could be disjoint subgraphs 
  for (int i = 0; i < N; i++) 
    if (! visited[i])
      if (! _bicolor(adj, visited, i, BLACK))
        return false;
  return true;
}

vvi makeGraph(vector<pi> & customers, int d) {
  // make a graph with all edges
  // with weight <= d removed 
  vvi adj;

  // add edges between each pair of customers
  for (int i = 0; i < N; i++) {
    adj.push_back(vi());
    for (int j = 0; j < N; j++) {
      // skip self edges 
      if (i == j) continue;
      // skip edges with weight <= d 
      if (taxip(customers[i], customers[j]) > d) 
        adj[i].push_back(j);
    }
  }
  return adj;
}

/*
*  binary search for minimum distance md needed 
*  to partition groups so that 
* 
*  max(diam(g1), diam(g2)) <= md
* 
*  we can check whether it is possible to partition 
*  the groups in this way by: 
*  1) constructing a graph with all edges <= md removed
*  2) bicolor the modified graph 
*
*  why bicoloring works to test diameter: 
*  - if bicoloring is possible, then we can assign customers
*  to g1 and g2 based on their colors. Since all the 
*  edges >md go between the groups, only edges
*  <=md remaining within each group, so the 
*  diameter constraint is satisfied  
*
*  - if we have groupings g1 and g2 such that 
*  max(diam(g1), diam(g2)) <= md, then all 
*  edges >md are between the groups, which 
*  means we can bicolor the modified graph
* 
*  - therefore we can bicolor modified graph 
*  iff we can group with max(diam(g1), diam(g2)) <= md
*/
int binsearch(int lo, int hi, vector<pi> & customers) {
  if (lo >= hi) return lo; 
  int mid = (lo/2) + (hi/2);

  // check if mid can be decreased
  vvi adj = makeGraph(customers, mid);
  bool canLower = bicolor(adj);

  if (canLower) 
    return binsearch(lo, mid, customers);
  return binsearch(mid+1, hi, customers);
}

int main() {
  cin >> N;
  if (N <= 2)  {
    cout << 0 << endl;
    return 0;
  }

  vector<pi> customers; 

  int x, y;
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    customers.push_back({ x, y });
  }

  int maxdist = 0;
  for (int i = 0; i < N; i++) 
    for(int j = i; j < N; j++) 
      maxdist = max(maxdist, taxip(customers[i], customers[j]));

  // binary search for minimum of two diameters, md
  // (check whether customers be partitioned into 
  // groups g1, g2 so that max(diam(g1), diam(g2)) == md)
  cout << binsearch(0, maxdist, customers) << endl;

  return 0;
}
