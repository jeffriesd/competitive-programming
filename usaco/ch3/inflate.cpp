/*
ID: jeffrie1
LANG: C++
TASK: inflate
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("inflate.out");
  ifstream fin ("inflate.in");

  int M, N;
  // M is size of bag
  // N is number of item types

  fin >> M >> N;

  vi weights(N, 0);
  vi values (N, 0);

  for (int i = 0; i < N; i++) 
    fin >> values[i] >> weights[i];

  vi dp (M+1, 0);
  for (int i = 0; i < N; i++) 
    dp[weights[i]] = max(dp[weights[i]], values[i]);

  int maxtotal = 0;
  for (int j = 1; j <= M; j++) {
    for (int i = 0; i < N; i++) {
      if (j - weights[i] >= 0) {
        dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
        maxtotal = max(maxtotal, dp[j]);
      }
    }
  }
  fout << maxtotal << endl;


  return 0;
}
