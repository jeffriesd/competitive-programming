/*
ID: jeffrie1
LANG: C++
TASK: wormhole
*/
#include<bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vb = vector<bool>;

#define FOR(i, n) for (int i = 0; i < n; i++)
#define LEFT(i) 2*i
#define RIGHT(i) 2*i+1
#define MAXN 12
int N; 
int total = 0;

// use 2N nodes 
// where
//
// odAdj[2i] = left neighbors of node i
// odAdj[2i+1] = right neighbors of node i
vector<vi> ogAdj(2*MAXN);

// bfs 
bool _hasCycle(int start, vector<vi> &adj, vb &visited) {
  queue<int> q;
  q.push(start);

  // local visited
  vb lv(2*N, false);

  int cur;
  while (! q.empty()) {
    cur = q.front(); q.pop();

    for (int nb : adj[cur]) {
      if (! lv[nb]) {
        visited[nb] = true;
        lv[nb] = true;
        q.push(nb);
      } else {
        return true;
      }
    }
  }
  return false;
}

void printAdj(vector<vi> adj) {
  FOR(i, 2*N) {
    cout << i << ": ";
    for (auto x : adj[i])
      cout << x << " ";
    cout << endl;
  }
}

// adj defines pairings (x, y) s.t. x < y
// holes 
bool hasCycle(vector<vi> adj) {
  // cout << "check cycle:" << endl;
  // printAdj(adj);

  vb visited (2*N, false);
  FOR(i, 2*N) {
    if (!visited[i]) {
      if (_hasCycle(i, adj, visited)) return true;    
    }
  }
  return false;
}

void swap(vi &arr, int i, int j) {
  int t = arr[i];
  arr[i] = arr[j];
  arr[j] = t;
}

// arr of length N
void solve(vi &arr, int li) {
  // base case -- we have a complete pairing
  if (N - li <= 2) {
    vector<vi> adjx (2*N);
    // copy contents
    FOR(i, 2*N) {
      for (int x : ogAdj[i])
        adjx[i].push_back(x);
    }
    // copy in pairings
    //
    // if (x, y) paired, then make edges
    // left(x) -> right(y) and
    // left(y) -> right(x)
    for (int i = 0; i < N; i+=2) {
      int lx = LEFT(arr[i]);
      int rx = RIGHT(arr[i]);
      int ly = LEFT(arr[i+1]);
      int ry = RIGHT(arr[i+1]);
  
      adjx[lx].push_back(ry);
      adjx[ly].push_back(rx);
    }

    if (hasCycle(adjx)) total++;
    return;
  }

  // recursive case to build complete pairing
  int ri = li + 1;
  for (int i = ri; i < N; i++) {
    swap(arr, ri, i);
    solve(arr, li+2);
    swap(arr, ri, i);
  }
}

int main() {
  ofstream fout ("wormhole.out");
  ifstream fin ("wormhole.in");

  fin >> N;

  unordered_map<int, vector<pair<int, int>>> xholes;

  int x, y;
  FOR(i, N) {
    fin >> x >> y; 

    if (xholes.find(y) == xholes.end()) {
      vector<pair<int, int>> h;
      xholes.insert({y , h});
    }
    xholes[y].push_back({x, i});
  }

  for (auto p : xholes) {
    x = p.first;
    if (p.second.size() > 1) {
      sort(p.second.begin(), p.second.end());
      for (int i = 1; i < p.second.size(); i++) {
        // make edge right(j) -> left(k)
        int j = p.second[i-1].second;
        int k = p.second[i].second;
        ogAdj[RIGHT(j)].push_back(LEFT(k));
      }
    }
  }

  vi inds (N);
  FOR(i, N) inds[i] = i;
  solve(inds, 0);

  fout << total << endl;
  cout << total << endl;
  
  return 0;
}



