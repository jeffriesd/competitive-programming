// problem: https://open.kattis.com/problems/ingestion

#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
vvi dp;
vi meals;
int mm;
int dd;

int solve(int day, int m) {
  if (day >= dd) return 0;
  int eaten = min(meals[day], m);

  if (dp[day][m] >= 0) return dp[day][m];

  // eat and dont wait
  int ret = eaten + solve(day+1, floor(2 * (double)m / 3));
  // eat and wait 1
  ret = max(ret, eaten + solve(day+2, m));
  // eat and wait 2
  ret = max(ret, eaten + solve(day+3, mm));
  // dont eat 
  ret = max(ret, solve(day+1, m));

  return (dp[day][m] = ret);
}

int main() {
  int n, m;
  cin >> n >> m;
  mm = m;
  dd = n;
  dp = vvi(n, vi(m+1, -1));

  int x;
  for (int i = 0; i < n; i++) {
    cin >> x;
    meals.push_back(x);
  }

  cout << solve(0, m) << endl;

  return 0;
}
