// problem: https://open.kattis.com/problems/grandpabernie

#include<bits/stdc++.h>
using namespace std;

class Trips {
  public:
    map<string, vector<int>> trips;
    Trips() {
    }

    void insert(string s, int y) {
      auto it = trips.find(s);
      if (it == trips.end()) {
        vector<int> v;
        trips[s] = v;
      }
      trips[s].push_back(y);
    }

    void sortAll() {
      for (auto it = trips.begin(); it != trips.end(); it++) {
        sort(it->second.begin(), it->second.end());
      } 
    }

    int ans(string s, int k) {
      return trips[s][k-1];
    }

};

int main() {
  int n;
  cin >> n;

  string c; 
  int m;
  Trips t;
  for (int i = 0; i < n; i++) {
    cin >> c >> m;
    t.insert(c, m);
  }

  t.sortAll();

  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    cin >> c >> m;
    cout << t.ans(c, m) << endl;
  }


  return 0;
}
