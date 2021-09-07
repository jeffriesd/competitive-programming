/*
ID: jeffrie1
LANG: C++
TASK: kimbits
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define MAXN 32
long long dp [MAXN+1][MAXN+1];

int numbits(int n) {
  int b = 0;
  while (n > 0) 
    n >>= 1;
  return b;
}

long long solve(int length, int ones, long long i) {
  if (i == 0) return 0;
  if (ones == 0) return 0;

  // find leading 1 bit
  int x = 1; 
  while (x <= MAXN && dp[x][ones] <= i) 
    x++;

  int nextInd;
  if (i == 1) nextInd = 0;
  else nextInd = i - dp[x-1][ones];

  return (1 << (x-1)) + solve(length - 1, ones - 1, nextInd);
}

int main() {
  ofstream fout ("kimbits.out");
  ifstream fin ("kimbits.in");

  int N, L;
  long long I;
  fin >> N >> L >> I;

  dp[0][0] = 0;
  dp[1][0] = 1;
  for (int j = 1; j <= N; j++) {
    dp[1][j] = 2;
    dp[0][j] = 0;
  }
  for (int i = 1; i <= N; i++) 
    dp[i][1] = i+1;

  for (int i = 2; i <= N; i++) 
    for (int j = 2; j <= N; j++) 
      dp[i][j] = dp[i-1][j] + dp[i-1][j-1];

  long long ans = solve(N, L, I-1);
  bitset<MAXN> bs (ans);
  // print bits without leading zeros
  for (int i = N-1; i >= 0; i--) 
    fout << bs[i];
  fout << endl;


  return 0;
}
