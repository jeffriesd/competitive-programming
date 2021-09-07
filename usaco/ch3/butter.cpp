/*
ID: jeffrie1
LANG: C++
TASK: butter
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define INF 999999

int N, P, C;

void dijkstra(int s, vector<vector<pi>> & adj, vi & dist) {
  
  //dist.assign(P, INF);
  dist[s] = 0;

  // store edges as (dist[next], next)
  set<pi> q;
  q.insert({0, s});

  int d, next;
  while (! q.empty()) {
    auto e = q.begin();
    int cur = e->second;
    q.erase(e);

    for (auto edge : adj[cur]) {
      tie(d, next) = edge;
      if (dist[cur] + d < dist[next]) {
        q.erase({dist[next], next});
        dist[next] = dist[cur] + d;
        q.insert({dist[next], next});
      }
    }
  }
}


// problem: given graph with P (<= 800) vertices (pastures),
// find vertex v s.t. total sum of sp(u_i, v) for u_i, i = 1..N
// (distance from each cow to v along shortest path) is minimized

// solution: 
// floyd warshall - compute all pairwise distances
// then check every vertex

int main() {
  ofstream fout ("butter.out");
  ifstream fin ("butter.in");

  fin >> N >> P >> C;
  
  // number of cows at each vertex
  vi cows(P, 0);

  vector<vector<pi>> adj(P);
  // vvi dist(P, vi(P));

  int c;
  for (int i = 0; i < N; i++) {
    fin >> c;
    cows[c-1]++;
  }

  int x, y, d;
  for (int i = 0; i < C; i++) {
    fin >> x >> y >> d;
    x--; y--;
    // dist[x][y] = d;
    // dist[y][x] = d;

    adj[x].push_back({d, y});
    adj[y].push_back({d, x});
  }

  // N.B. - floyd-warshall (O(n^3)) is too slow for P = 800

  // run dijkstras (sparse version) P times -- O(P^2 log P)
  vvi alldist;
  for (int i = 0; i < P; i++) {
    vi dist_i(P, INF);
    dijkstra(i, adj, dist_i);
    alldist.push_back(dist_i);
  }


  int minTotal = INF;
  // try placing sugar cube at every vertex
  for (int i = 0; i < P; i++) {
    int totalDist = 0;
    for (int j = 0; j < P; j++)
      totalDist += alldist[i][j] * cows[j];
    minTotal = min(minTotal, totalDist);
  }
  fout << minTotal << endl;


  return 0;
}
