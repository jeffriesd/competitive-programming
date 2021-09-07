// problem: https://open.kattis.com/problems/retribution

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int distsqrd (pi & p1, pi & p2) {
  int x1, y1, x2, y2;
  tie(x1, y1) = p1;
  tie(x2, y2) = p2;
  int dx = x1 - x2;
  int dy = y1 - y2;
  
  return (dx*dx + dy*dy);
}

int main() {

  int N, M, P;
  cin >> N >> M >> P;

  vector<pi> judges;
  vector<pi> tars;
  vector<pi> feathers;

  int x, y;
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    judges.push_back({x, y});
  }

  for (int i = 0; i < M; i++) {
    cin >> x >> y;
    tars.push_back({x, y});
  }

  for (int i = 0; i < P; i++) {
    cin >> x >> y;
    feathers.push_back({x, y});
  }
  // store all pairwise distances
  // between judges and tars
  // and then sort by first entry
  // entry {d, {j, t}} means 
  // judge j and tar t have distance d
  vector<pair<int, pi>> distJT;
  vector<pair<int, pi>> distJF;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) 
      distJT.push_back({distsqrd(judges[i], tars[j]), {i, j}});

    for (int j = 0; j < P; j++) 
      distJF.push_back({distsqrd(judges[i], feathers[j]), {i, j}});
  }

  sort(begin(distJT), end(distJT));
  sort(begin(distJF), end(distJF));


  vb assignedJudge(N, false);
  vb assignedTar (M, false);
  vb assignedFeather (P, false);

  int nassigned = 0;

  double sum = 0;
  int d, j, t;
  for (auto &p : distJT) {
    if (nassigned == N) break;
    d = p.first;
    tie(j, t) = p.second;
    if (assignedJudge[j] || assignedTar[t]) continue;

    sum += sqrt(d);
    assignedJudge[j] = true;
    assignedTar[t] = true;
    nassigned++;
  }

  fill(begin(assignedJudge), end(assignedJudge), false);

  nassigned = 0;
  for (auto &p : distJF) {
    if (nassigned == N) break;
    d = p.first;
    tie(j, t) = p.second;
    if (assignedJudge[j] || assignedFeather[t]) continue;

    sum += sqrt(d);
    assignedJudge[j] = true;
    assignedFeather[t] = true;
    nassigned++;
  }
    
  cout << fixed << setprecision(6) << sum << endl;

  return 0;
}
