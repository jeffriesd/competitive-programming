// problem: https://open.kattis.com/problems/thecolonizationofelgarizm

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define BLACK 1
#define WHITE 2

void append(unordered_map<int, vi> & nums, int x, int i) {
  auto p = nums.find(x);
  if (p == nums.end()) {
    vi v;
    v.push_back(i);
    nums.insert({x, v});
  }
  else {
    p->second.push_back(i);
  }
}


// is it possible to bicolor this graph?
bool color(vector<vi> & adj, vi & visited, int i, int cl) {
  visited[i] = cl;

  for (int nb : adj[i]) {
    if (! visited[nb]) {
      if (! color(adj, visited, nb, (WHITE + BLACK) - cl))
        return false;
    }
    else if (visited[nb] == cl) {
      return false;
    }
  }
  return true;
}

// simple bicoloring problem
// 
// if group X on node i
//
// i -> j
//   -> k
//   -> h
//
// then all its neighbors 
// must be occupied by group Y
// (otherwise group Y would not get
// the resource denoted by that edge)
int main() {
  int M; // number of islands
  int N; // number of "resources" (edges)

  cin >> M >> N;
  unordered_map<int, vi> resources;
  vector<vi> adj (M);

  // edges.

  int x;
  for (int i = 0; i < M; i++) {
    cin >> x;
    while (x > 0) {
      append(resources, x, i);
      cin >> x;
    }
  }

  int y;
  for (auto &p : resources) {
    x = p.second[0];
    y = p.second[1];
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // visited[i] = 1 <- black
  // visited[i] = 2 <- white
  vi visited (M, 0);
  for (int i = 0; i < M; i++) {
    if (! visited[i]) {
      if (! color(adj, visited, i, BLACK)) {
        cout << "NO" << endl;
        return 0;
      }
    }
  }

  cout << "YES" << endl;


  return 0;
}
