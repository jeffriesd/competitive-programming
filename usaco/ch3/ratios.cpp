/*
ID: jeffrie1
LANG: C++
TASK: ratios
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("ratios.out");
  ifstream fin ("ratios.in");

  int ga, gb, gc;
  fin >> ga >> gb >> gc;

  int a1, a2, a3, b1, b2, b3, c1, c2, c3;
  fin >> a1 >> b1 >> c1;
  fin >> a2 >> b2 >> c2;
  fin >> a3 >> b3 >> c3;

  int a, b, c;
  
  // mininimum counts for mixture with correct ratio
  int minA, minB, minC, goalMult;
  minA = minB = minC = goalMult = -1;

  for (int k1 = 0; k1 <= 100; k1++) {
    for (int k2 = 0; k2 <= 100; k2++) {
      for (int k3 = 0; k3 <= 100; k3++) {
        if (k1 == 0 && k2 == 0 && k3 == 0) continue;
        a = k1 * a1 + k2 * a2 + k3 * a3;
        b = k1 * b1 + k2 * b2 + k3 * b3;
        c = k1 * c1 + k2 * c2 + k3 * c3;
        
        // handle goal value of 0
        if (ga == 0 && a != 0) continue;
        if (gb == 0 && b != 0) continue;
        if (gc == 0 && c != 0) continue;

        // check nonzero goals 
        vector<pi> check;
        if (ga > 0)
          check.push_back({a, ga});
        if (gb > 0)
          check.push_back({b, gb});
        if (gc > 0)
          check.push_back({c, gc});

        bool goodRatio = true;
        int c = -1;
        if (! check.empty()) {
          c = check[0].first / check[0].second;
          for (auto p : check) {
            if ((p.first % p.second) || ((p.first / p.second) != c)) {
              goodRatio = false;
              break;
            }
          }
        }
        if (goodRatio) {
          if (goalMult == -1 || k1 + k2 + k3 < minA + minB + minC) {
            minA = k1;
            minB = k2;
            minC = k3;
            goalMult = c;
          }
        }
      }
    }
  }

  if (goalMult < 0) 
    fout << "NONE" << endl;
  else 
    fout << minA << " " << minB << " " << minC << " " << goalMult << endl;

  return 0;
}
