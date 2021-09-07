/*
ID: jeffrie1
LANG: C++
TASK: cowtour
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vd = vector<double>;
using si = set<int>;

#define INF 999999999
#define MAXN 150
int N;
vector<pi> coords;
vector<set<int>> adj;
double dist[MAXN][MAXN];

double eucdist(int i, int j) {
  int x1, x2, y1, y2;
  tie(x1, y1) = coords[i];
  tie(x2, y2) = coords[j];
  double dx = x1-x2;
  double dy = y1-y2;

  double d = sqrt(dx*dx + dy*dy);
  return d;
}

void floyd() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j)
        dist[i][j] = 0;
      else if (adj[i].find(j) != end(adj[i]))
        dist[i][j] = eucdist(i, j);
      else
        dist[i][j] = INF;
    }
  }

  for (int k = 0; k < N; k++) 
    for (int i = 0; i < N; i++) 
      for (int j = 0; j < N; j++) 
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

void dfs(vb & visited, int i, int ci, vi & verts) {
  verts.push_back(i);
  visited[i] = true; 

  for (int v : adj[i]) 
    if (! visited[v])
      dfs(visited, v, ci, verts);
}

vvi components() {
  vb visited (N, false);
  vvi compverts;

  int ci = 0;
  for (int u = 0; u < N; u++) {
    if (! visited[u]) {
      vi verts;
      dfs(visited, u, ci, verts);
      compverts.push_back(verts);
      ci++;
    }
  }
  return compverts;
}


int main() {
  ofstream fout ("cowtour.out");
  ifstream fin ("cowtour.in");

  fin >> N;
  for (int i = 0; i < N; i++) {
    pi p;
    fin >> p.first >> p.second;
    coords.push_back(p);
  }

  string s;
  for (int i = 0; i < N; i++) {
    fin >> s;
    set<int> verts;
    adj.push_back(verts);
    for (int j = 0; j < N; j++) {
      if (s[j] == '1')
        adj[i].insert(j);
    }
  }


  // floyd warshall
  floyd();

  vvi compverts = components();
  int numComps = compverts.size();

  // determine most distant vertex
  // for each vertex in each component
  vi fv (N, -1);
  // also compute diameter for each component
  vd diam(N, 0);
  // for (vi & comp : compverts) {
  for (int ci = 0; ci < numComps; ci++) {
    for (int u : compverts[ci]) {
      double maxd = 0;
      for (int v : compverts[ci]) {
        if (dist[u][v] >= maxd) {
          maxd = dist[u][v];
          fv[u] = v;
        }

        diam[ci] = max(dist[u][v], diam[ci]);
      }
    }
  }

  // try each pair of vertices
  // in each pair of connected comps

  double mindiam = INF;
  for (int i = 0; i < numComps; i++) {
    for (int j = i+1; j < numComps; j++) {
      for (int u : compverts[i]) {
        for (int v : compverts[j]) {
          double e = eucdist(u, v);

          // longest path going through e
          double m =  dist[u][fv[u]] + e + dist[v][fv[v]];

          if (dist[u][fv[u]] != dist[fv[u]][u] || dist[v][fv[v]] != dist[fv[v]][v]) {
            printf("oops\n");
            exit(0);
          }

          // printf("add edge (%d, %d): diam = %f;    dist = %f\n", u, v, m, e);

          // new diam is max of diam(i), diam(j), 
          double newdiam = max(max(diam[i], diam[j]), m); 

          mindiam = min(mindiam, newdiam);
        }
      }
    }
  }
  fout << fixed << setprecision(6) << mindiam << endl;

  return 0;
}

