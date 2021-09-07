/*
ID: jeffrie1
LANG: C++
TASK: ditch
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;


#define INF 999999999

int ffbfs(int src, int sink, vvi & adj, vvi & cap, vi & par) {
  // bfs for ford fulkerson 
  // (edmonds-karp)
  //
  // returns length of augmenting path 
  fill(par.begin(), par.end(), -1);
  par[src] = -2;

  queue<pi> q;
  q.push({src, INF});

  while (! q.empty()) {
    int cur  = q.front().first;
    int flow = q.front().second;
    q.pop();

    for (int next : adj[cur]) {
      if (par[next] == -1 && cap[cur][next] > 0) {
        par[next] = cur;
        int mflow = min(flow, cap[cur][next]);
        if (next == sink) 
          return mflow;

        q.push({next, mflow});
      }
    }
  }
  // no path to sink
  return 0;
}


int fordFulkerson(int src, int sink, vvi & adj, vvi & cap) {
  // number of nodes
  int N = adj.size();

  // store parent ptrs 
  // for each source-to-sink path 
  vi par (N);

  int maxflow = 0;
  int newflow;
  while ((newflow = ffbfs(src, sink, adj, cap, par))) {
    // find augmenting path using bfs 
    // and stop when there are no more augmenting paths
    maxflow += newflow;

    // retrace path and update
    // capacities
    int cur = sink;
    // printf("path is :\n");
    while (cur != src) {
      int prev = par[cur];
    
      // printf("%d ", cur);
      cap[prev][cur] -= newflow;
      cap[cur][prev] += newflow;
      cur = prev;
    }
    // printf("\n");

  }
  return maxflow;
}


int main() {
  ofstream fout ("ditch.out");
  ifstream fin ("ditch.in");

  // standard maxflow problem 
  // for directed graph but
  // there can be multiple 
  // edges per pair of nodes 
  //
  // just expand each edge of capacity c 
  // into a node with one ingoing and one outgoing
  // edge of capacity c, e.g., 
  //
  // A -- (cap=c) --> B
  // becomes
  // A -- (cap=c) --> X -- (cap=c) --> B
  //
  // so if N and M are the number of nodes
  // and edges in the original graph, 
  // then the new number of nodes is N + M
  // and the new number of edges is 2M

  int N, M;
  fin >> M >> N;

  vvi adj(N+M, vi());
  vvi capacity(N+M, vi(N+M, 0));
  for (int i = 0; i < N+M; i++) 
    for (int j = 0; j < N+M; j++)  
      capacity[i][j] = 0;

  int s, e, c;
  int xi = N; // index of node created for each edge
  for (int i = 0; i < M; i++) {
    fin >> s >> e >> c;
    s--; 
    e--; // 0-based indexing

    // new node for this edge has
    // index (N + i)
    adj[s].push_back(xi);
    adj[xi].push_back(e);
    capacity[s][xi] = c;
    capacity[xi][e] = c;

    // add reverse edges
    adj[xi].push_back(s);
    adj[e].push_back(xi);
    xi++;
  }

  fout << fordFulkerson(0, N-1, adj, capacity) << endl;


  return 0;
}
