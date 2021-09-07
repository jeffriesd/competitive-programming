// problem: https://open.kattis.com/problems/mailbox

#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;


int sumN(int n) {
  return (n * (n+1)) >> 1;
}

// consider amounts of crackers fro [lo, hi]
int fun(vvvi & dp, int boxes, int lo, int hi) {
  if (dp[boxes][lo][hi] > 0) return dp[boxes][lo][hi];
  // if only 1 box
  if (boxes == 1) {
    // if cracker range is [3, 5] = 1 + 2 + 3 + 4 + 5 - (1 + 2) = 3 + 4 + 5
    return sumN(hi) - sumN(lo - 1); 
  }
  if (lo > hi) return 0;

  int ans = INT_MAX;
  for (int i = lo; i <= hi; i++) {
    ans = min(ans, i + max(
           // using i crackers breaks a box
           fun(dp, boxes - 1, lo, i-1),
           // using i crackers doesnt break
           fun(dp, boxes, i+1, hi)
         )
       ); 
  }
  dp[boxes][lo][hi] = ans;
  return ans;
}

int main() {
  int N; 
  cin >> N;
  int K = 11;
  int M = 101;

  int k, m;
  vvvi dp (K+1, vvi(M+1, vi(M+1, -1)));

  for (int i=0 ;i < N; i++) {
    cin >> k >> m; 
    cout << fun(dp, k, 1, m) << endl;  
  }

}
