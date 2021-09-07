/*
ID: jeffrie1
LANG: C++
TASK: milk
*/
#include<bits/stdc++.h>
using namespace std;

int main() {
  ofstream fout ("milk.out");
  ifstream fin ("milk.in");

  // 0 <= N <= 2,000,000 - total amount to purchase
  // 0 <= M <= 5,000 - number of farmers
  int N, M;
  fin >> N >> M;

  vector<pair<int, int>> prices;
  vector<int> units;
  int i, p, a;
  for (i = 0; i < M; i++) {
    fin >> p >> a; 
    prices.push_back({p, i});
    units.push_back(a);
  }
  sort(prices.begin(), prices.end());

  int total = 0;
  for (auto pi : prices) {
    tie(p, i) = pi;

    a = min(N, units[i]);
    total += a * p;
    N -= a;
    if (N == 0) break;
  }

  fout << total << endl;

  return 0;
}
