/*
ID: jeffrie1
LANG: C++
TASK: stamps
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int K; // maximum number of stamps that can be used in one sum
int N; // total number of stamps

#define MAXSTAMPVAL 10000
#define TOTALSTAMPS 200
#define MAXCOST MAXSTAMPVAL * TOTALSTAMPS

int main() {
  ofstream fout ("stamps.out");
  ifstream fin ("stamps.in");

  fin >> K >> N;
  vi stamps(N, 0); // stamp values
  // assuming next N values are unique 
  // since we can use an arbitrary number of 
  // each stamp type (as long as total < K)
  int maxstamp = 0;
  for (int i = 0; i < N; i++)  {
    fin >> stamps[i];
    maxstamp = max(maxstamp, stamps[i]);
  }

  sort(begin(stamps), end(stamps));

  // max cost is if we use maximum value stamp K times
  int maxCost = maxstamp * K;
  

  vi dp (maxCost+1, K+1);
  // output highest number M 
  // s.t. we can create 1..M cents
  // using K stamps
  for (int x : stamps)
    dp[x] = 1;

  // do sieve to mark off reachable states
  int i;
  for (i = 1; i <= maxCost; i++) {

    for (int x : stamps) {
      if (i - x <= 0) continue;
      if (dp[i-x] >= K) continue; // can't add any
      dp[i] = min(dp[i], dp[i - x] + 1);
    }
    if (dp[i] > K) break;
  }
  fout << i-1 << endl;

  return 0;
}
