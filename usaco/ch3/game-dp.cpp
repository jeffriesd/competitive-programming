/*
ID: jeffrie1
LANG: C++
TASK: game1
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;
int score1 = 0;
int score2 = 0;

void swap(int & x, int & y) {
  int t = x;
  x = y;
  y = t;
}

int main() {
  ofstream fout ("game1.out");
  ifstream fin ("game1.in");

  int N;
  fin >> N;
  vi board(N, 0);
  for (int i = 0; i < N; i++) 
    fin >> board[i];

  // dp[i][j] = (x, y) 
  // indicates the optimal scores
  // for board[i]...board[j]
  // where x is the score of the player 
  // who moves first
  //
  // fill up length-k segments for 
  // k = 1..N
  vector<vector<pi>> dp (N, vector<pi>(N));
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      dp[i][j] = {0, 0};
  for (int i = 0; i < N; i++) {
    dp[i][i] = { board[i] , 0 };
  }

  for (int k = 1; k < N; k++) {
    for (int i = 0; i + k < N; i++) {
      // to find optimal score for 
      // i...i+k, try taking left element
      // and using optimal score for i+1..i+k
      //
      // or take rightmost and use optimal score
      // for i...i+k-1
      int ifleft = board[i];
      int p1left, p2left;
      tie(p2left, p1left) = dp[i+1][i+k];

      int ifright = board[i+k];
      int p1right, p2right;
      tie(p2right, p1right) = dp[i][i+k-1];

      if (ifleft + p1left > ifright + p1right) {
        dp[i][i+k] = { ifleft + p1left, p2left };
      }
      else {
        dp[i][i+k] = { ifright + p1right, p2right };
      }
    } 
  }

  pi p = dp[0][N-1];
  fout << p.first << " " << p.second << endl;

  return 0;
}
