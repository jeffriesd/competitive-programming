// problem: https://open.kattis.com/problems/justpassingthrough

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define MAXR 500
#define MAXC 500
#define MAXN 10
#define INVALID -1
#define INF 9999999
int dp [MAXR][MAXC][MAXN+1];
int elevation [MAXR][MAXC];

int R, C, N;

void print(int k) {
  // debug print 
  printf("\nk = %d\n", k);
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (dp[i][j][k] == INF)
        cout << setw(3) << "_" << " ";
      else
        cout << setw(3) << dp[i][j][k] << " ";
    }
    cout << endl;
  }
  cout << endl;

}

bool pass(int i, int j) {
  if (i == 0 || j == 0 || i == R-1 || j == C-1) return false;
  if (elevation[i][j] == INVALID) return false;
  int e = elevation[i][j];

  // check north, south (should be valid and > e)
  if (elevation[i-1][j] == INVALID || elevation[i-1][j] <= e)
    return false;
  if (elevation[i+1][j] == INVALID || elevation[i+1][j] <= e)
    return false;
  // check east, west (should be < e)
  if (elevation[i][j-1] == INVALID || elevation[i][j-1] >= e)
    return false;
  if (elevation[i][j+1] == INVALID || elevation[i][j+1] >= e)
    return false;
  return true;
}

int main() {
  cin >> R >> C >> N;

  // R rows, C columns, must pass through exactly
  // N 'passes', i.e.
  // squares which have strictly lower elevations
  // to the east and west and strictly higher elevations
  // to north and south
  //
  // elevations appear to be integers though
  // problem does not explicitly state this
  //
  // want to find path which minimizes sum of elevations
  // and goes through exactly n passes
  //
  // solution: 
  // shortest path in DAG 
  // passing through n specific nodes
  //    - can create n copies of graph
  //    OR
  //    - two dimensional DP
  //
  //      DP[i][j][k] = shortest path to node i,j
  //                using exactly k passes
  //
  //      fill up from west to east, 
  //
  //        i.e. j = 0 to j = ..
  //      
  //
  //
  //  - all edges going into node with elevation x
  //    have weight x
  //      

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> elevation[i][j];
    }
  }

  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      for (int k = 0; k <= N; k++)
        dp[i][j][k] = INF;

  // fill up dp[i][0][0]
  // (West border - no passes by definition)
  for (int i = 0; i < R; i++) {
    if (elevation[i][0] != INVALID)
      dp[i][0][0] = elevation[i][0];
  }

  // fill up rest for k = 0
  for (int j = 1; j < C; j++) {
    for (int i = 0; i < R; i++) {
      if (elevation[i][j] == INVALID) continue;
      if (pass(i, j)) continue;

      int W, NW, SW;
      W = NW = SW = INF;

      // from west
      if (j > 0 && elevation[i][j-1] != INVALID)
        W = dp[i][j-1][0];
      // from northwest
      if (j > 0 && i > 0 && elevation[i-1][j-1] != INVALID)
        NW = dp[i-1][j-1][0];
      // from southwest
      if (j > 0 && i < R-1 && elevation[i+1][j-1] != INVALID)
        SW = dp[i+1][j-1][0];

      dp[i][j][0] = min(W, min(NW, SW)) + elevation[i][j];
    }
  }

  // print(0);

  int kk;
  for (int k = 1; k <= N; k++) {
    for (int j = 0; j < C; j++) {
      for (int i = 0; i < R; i++) {
        if (elevation[i][j] == INVALID) continue;
        // printf("i = %d, j = %d, k = %d, pass = %d\n", i, j, k, pass(i, j));

        // if current cell is a pass
        // build off of dp[][][k-1]
        kk = k;
        if (pass(i, j)) 
          kk--;
        int W, NW, SW;
        W = NW = SW = INF;

        // from west
        if (j > 0 && elevation[i][j-1] != INVALID)
          W = dp[i][j-1][kk];
        // from northwest
        if (j > 0 && i > 0 && elevation[i-1][j-1] != INVALID)
          NW = dp[i-1][j-1][kk];
        // from southwest
        if (j > 0 && i < R-1 && elevation[i+1][j-1] != INVALID)
          SW = dp[i+1][j-1][kk];

        // printf("W = %d, NW = %d, SW = %d ;; %d\n", W, NW, SW, elevation[i+1][j-1]);
        dp[i][j][k] = min(W, min(NW, SW)) + elevation[i][j];
      }
    }
    // print(k);
  }


  int shortest = INF;
  // find cell on east border with min distance
  for (int i = 0; i < R; i++) {
    if (elevation[i][C-1] == INVALID) continue;
    shortest = min(shortest, dp[i][C-1][N]);
  } 

  if (shortest == INF)
    cout << "impossible" << endl;
  else
    cout << shortest << endl;

  return 0;
}
