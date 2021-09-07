// problem: https://open.kattis.com/problems/ragingriver

#include<bits/stdc++.h>
#define LEFT 0
#define RIGHT 1
#define INF INT_MAX
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vpii = vector<pii>;

class Edge {
  public:
    int from, to;
    int cost;
    int cap;
    int revInd;

    Edge(int f, int t, int cs, int cp, int ri) {
      from = f;
      to = t;
      cost = cs;
      cap = cp;
      revInd = ri;
    }
};

using ve = vector<Edge>;
using vve = vector<ve>;


void shortestPaths(int s, vve & edges, vi & d, vpii & p) {
  fill(d.begin(), d.end(), INF);
  fill(p.begin(), p.end(), make_pair(-1, -1));
  d[s] = 0;
  vector<bool> inq(d.size(), false);
  queue<int> q;
  q.push(s);
  
  while (! q.empty()) {
    int u = q.front(); 
    q.pop();
    inq[u] = false;
    for (int ei = 0; ei < edges[u].size(); ei++) {
      Edge ed = edges[u][ei];
      if (ed.cap > 0 && d[u] + ed.cost < d[ed.to]) {
        d[ed.to] = d[u] + ed.cost;
        // parent stores (prevNode, indexOfThisNodeInPrevNodeAdj)
        p[ed.to] = make_pair(u, ei);
        if (! inq[ed.to]) {
          q.push(ed.to);
          inq[ed.to] = true;
        }
      }
    }
  }
}
int main() {
  int P, V, E;

  cin >> P >> V >> E;

  // adjacency list for each
  // node will be a pair of lists
  // (forward, reversed

  vvi adj (V+2, vi());
  vvi cap (V+2, vi(V+2, 0));

  vve edges (V+2, ve());

  int x, y;
  
  for (int i = 0; i < E; i++) {
    cin >> x >> y;
    // shift everything up so
    // L = 0, R = 1
    x += 2; y += 2;

    // fw edge x -> y -- store index of its bw edge
    //    bw edge y -> x (cap 0, cost -1) -- store index of fw edge
    
    // fw edge y -> x

    // add two edges x -> y
    int fwi, bwi;
    fwi = edges[x].size();
    bwi = edges[y].size();
    edges[x].push_back(Edge(x, y, 1, 1, bwi));
    edges[y].push_back(Edge(y, x, -1, 0, fwi));
      
    fwi = edges[y].size();
    bwi = edges[x].size();
    edges[y].push_back(Edge(y, x, 1, 1, bwi));
    edges[x].push_back(Edge(x, y, -1, 0, fwi));

  }

  // do max flow
  int flow = 0;
  int cost = 0;
  vi dist(V+2);
  vpii parent(V+2); 
  int newFlow;

  while (flow < P) {
    shortestPaths(LEFT, edges, dist, parent);
    if (dist[RIGHT] == INF) break;

    int f = P - flow;
    int cur = RIGHT;
    int prevNode;
    int ei;
    while (cur != LEFT) {
      prevNode = parent[cur].first;
      ei = parent[cur].second;
      f = min(f, edges[prevNode][ei].cap);
      cur = prevNode;
    }

    // apply flow
    flow += f;
    cost += f * dist[RIGHT];
    cur = RIGHT;
    Edge * fw, * bw;
    while (cur != LEFT) {
      prevNode = parent[cur].first;
      ei = parent[cur].second;
      
      fw = &edges[prevNode][ei];
      // cout << "fw edge: " << fw->from-2<<", " << fw->to -2<< endl;
      // subtract from forwards edge...
      // get reversed edge
      bw = &edges[cur][fw->revInd];

      fw->cap -= f;
      bw->cap += f;

      cur = prevNode;
    }
    // cout << endl;
  }

  if (flow < P) 
    cout << P - flow << " people left behind" << endl;
  else cout << cost << endl;

  return 0;
}




