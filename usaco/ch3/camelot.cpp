/*
ID: jeffrie1
LANG: C++
TASK: camelot
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define MAXR 30
#define MAXC 30
#define MAXIND 900
#define INF 999999

int R, C;
// king coordinates
int kc, kr;

pi nboffsets [8];

// bounds check
int valid(int i, int j) {
  if (i < 0 || j < 0) return false;
  if (i >= R || j >= C) return false;

  return true;
}

// taxicab distance with diag movement
int kingdist(int i, int j, int ii, int jj) {
  int di = abs(i - ii);
  int dj = abs(j - jj);
  return max(di, dj); 
}

// map 2d coordinates to index into array of size [R * C]
int mapinds (int i, int j) {
  return i * C + j;
}

// map pointer to inds

int main() {
  ofstream fout ("camelot.out");
  ifstream fin ("camelot.in");

  nboffsets[0] = {1, 2};
  nboffsets[1] = {2, 1};
  nboffsets[2] = {-1, 2};
  nboffsets[3] = {-2, 1};
  nboffsets[4] = {-1, -2};
  nboffsets[5] = {-2, -1};
  nboffsets[6] = {1, -2};
  nboffsets[7] = {2, -1};

  fin >> R >> C;

  char col;
  int row;
  fin >> col >> row;
  kc = col - 'A';
  kr = row - 1;

  set<pi> knights;
  while (fin >> col >> row) 
    knights.insert({ row - 1, col - 'A' });

  if (knights.size() == 0) {
    fout << 0 << endl;
    return 0;
  }

  int i, j, d;
  int di, dj;

  // total dist for every knight to 
  // walk to i, j
  vvi knightTotal (R, vi(C, 0));
  // extra amount for king to reach i, j
  vvi extra (R, vi(C, INF));
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      knightTotal[i][j] = 0;
      extra[i][j] = INF;
    }


  vvi knightdist(R, vi(C));
  vvi pickupdist(R, vi(C));

  // for each knights
  int ki, kj;
  bool hasKing;
  for (auto p : knights) {
    tie(ki, kj) = p;

    // do bfs from ki, kj 
    // and account for whether knight has been picked up
    
    // init distances
    for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
        knightdist[i][j] = pickupdist[i][j] = INF;

    knightdist[ki][kj] = 0;

    set<pair<pi, pi>> dijkstra;
    // dijkstra = {{dist, noking}, {i, j}}
    // use 1 to indicate absence of king
    // so these are processed last 
    dijkstra.insert({{0, false}, {ki, kj}});

    while (! dijkstra.empty()) {
      auto p = dijkstra.begin();
      tie(d, hasKing) = p->first;
      tie(i, j) = p->second;
      dijkstra.erase(p);

      // printf("visit %d, %d; dist = %d\n", i, j, d);

      // if king is not currently with knight, 
      // try having king walk to current square
      if (! hasKing) {
        int dd = d + kingdist(i, j, kr, kc);
        if (dd < pickupdist[i][j]) {
          pickupdist[i][j] = dd; 
          dijkstra.insert({{dd, true}, {i, j}});
        }
      }

      // try all 8 neighbors 
      for (auto q : nboffsets) {
        tie(di, dj) = q;

        vvi * dist = !hasKing ? &knightdist : &pickupdist;

        if (valid(i+di, j+dj) && d + 1 < (*dist)[i + di][j + dj]) {
          (*dist)[i + di][j + dj] = d + 1;

          dijkstra.insert({{d+1, hasKing}, {i + di, j + dj}});
        }
      }
    }

    // compute extra for every square
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        int without = knightdist[i][j];
        int with = pickupdist[i][j];
        extra[i][j] = min(extra[i][j], with - without);
        knightTotal[i][j] += knightdist[i][j];
      }
    }
  }

  int mincost = INF;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      int cost = knightTotal[i][j] + extra[i][j];
      // cout << knightTotal[i][j] << endl;
      mincost = min(mincost, cost);
    }
  }

  fout << mincost << endl;


  return 0;
}
