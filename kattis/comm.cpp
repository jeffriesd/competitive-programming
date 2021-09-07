// problem: https://open.kattis.com/problems/communicationssatellite

#include<bits/stdc++.h>
using namespace std;

using dish = tuple<int, int, int>;
using dist = pair<double, int>;

int main() {
  int n;
  cin >> n;

  int x, y, r;
  vector<dish> dishes;
  for (int i = 0; i < n; i++) {
    cin >> x >> y >> r; 
    dishes.push_back({x, y, r});
  }

  // minq
  priority_queue<dist, vector<dist>, greater<dist>> pq;
  pq.push(make_pair(0, 0));
  vector<bool> visited (n);

  int cur;
  double curW;
  double ans = 0;
  int j = 0;
  while (! pq.empty()) {
    tie(curW, cur) = pq.top();
    pq.pop(); 

    tie(x, y, r) = dishes[cur];

    if (visited[cur]) continue;
    visited[cur] = true;

    ans += curW;
    for (int i =0 ; i < n; i++) {
      if (visited[i]) continue;
     
      int xx, yy, rr; 
      tie(xx, yy, rr) = dishes[i];  
      int dx, dy;
      dx = x - xx;
      dy = y - yy;
      double dist = sqrt(dx * dx + dy * dy) - r - rr;
      pq.push(make_pair(dist, i));
    }
  }

  cout << setprecision(25) << ans << endl;

  return 0;

}



