/*
ID: jeffrie1
LANG: C++
TASK: fence
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;
using msi = multiset<int>;
#define MAXF 501

void eulerTour(int cur, vi & tour, vector<msi> & adj) {
  if (adj[cur].size() == 0) {
    tour.push_back(cur);
    return;
  }

  vi neighbors (begin(adj[cur]), end(adj[cur]));

  for (int v : neighbors) {
    if (adj[cur].find(v) == adj[cur].end()) continue;
    // erase exactly one edge 
    // (must use ms.erase(ms.find(key)) rather 
    //  than ms.erase(key), which erases all 
    //  copies of a key)
    adj[cur].erase(adj[cur].find(v));
    adj[v].erase(adj[v].find(cur));    
    eulerTour(v, tour, adj);
  }
  tour.push_back(cur);
}

int main() {
  ofstream fout ("fence.out");
  ifstream fin ("fence.in");

  int F; 
  fin >> F;
  vector<msi> adj (MAXF, msi());

  si nodes;
  int i, j;
  int maxnode = 1;
  for (int k = 0; k < F; k++) {
    fin >> i >> j;
    adj[i].insert(j); 
    adj[j].insert(i);

    maxnode = max(maxnode, max(i, j));
    nodes.insert(i);
    nodes.insert(j);
  }

  // determine whether all even degree 
  // or all except two
  bool allEven = true;
  for (int i : nodes)
    if (adj[i].size() % 2) {
      allEven = false;
      break; 
    }

  set<vi> tours;
  for (int i = 1; i <= maxnode; i++) {
    if (adj[i].size() == 0) continue;
    if (! allEven && adj[i].size() % 2 == 0) continue;
    vi tour;
    vector<msi> adjj (begin(adj), end(adj));
    eulerTour(i, tour, adjj);
  
    reverse(begin(tour), end(tour));
    tours.insert(tour);
  }
  vi tour (tours.begin()->begin(), tours.begin()->end());
  for (int t : tour)
    fout << t << endl;

  return 0;
}
