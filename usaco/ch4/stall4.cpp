/*
ID: jeffrie1
LANG: C++
TASK: stall4
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define INF 9999999

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



// use ford fulkerson 
int maxBipartiteMatching(int N, int M, vvi & adj) {
  // N - size of first group
  // M - size of second group
  //
  // adj is adjacency list of bipartite graph 
  // with all edges going from group N to group M
   
  // add dummy source and sink 
  int src  = N+M;
  int sink = N+M+1;
  vvi capacity(N+M+2, vi(N+M+2));
  for (int i = 0; i < N+M+2; i++) 
    for (int j = 0; j < N+M+2; j++)
      capacity[i][j] = 0;

  adj.push_back(vi());
  adj.push_back(vi());
  // add edges from source to cows
  for (int i = 0 ; i < N; i++) {
    adj[src].push_back(i);
    capacity[src][i] = 1;
    // add capacity for regular edges 
    for (int j : adj[i]) {
      capacity[i][j] = 1;
      // capacity[j][i] = 1;
    }
  }
  // add edges from stalls to sink
  for (int i = N; i < N + M; i++) {
    adj[i].push_back(sink);
    capacity[i][sink] = 1;
  }

  return fordFulkerson(src, sink, adj, capacity);
}



int main() {
  ofstream fout ("stall4.out");
  ifstream fin ("stall4.in");

  int N, M;
  fin >> N >> M;

  vvi adj(N + M, vi());
  int S;
  int c;
  for (int i = 0 ; i < N; i++) {
    fin >> S;
    for (int j = 0; j < S; j++) {
      fin >> c;
      c += N - 1; // use 0 based indexing
      adj[i].push_back(c);
      // NOTE have to add "matching" edge
      // in both directions for ford-fulkerson
      // to work correctly
      adj[c].push_back(i);
    }
  }

  fout << maxBipartiteMatching(N, M, adj) << endl;

  return 0;
}
