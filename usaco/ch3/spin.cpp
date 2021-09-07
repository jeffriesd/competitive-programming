/*
ID: jeffrie1
LANG: C++
TASK: spin
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

// problem: given five circles rotating at different speeds
// and up to 5 'wedges' on each circle, 
// compute the earliest time (integer number of seconds) at which 
// all 5 circles have at least one of their wedges overlapping 
// some section (some interval of degrees)
//

// solution: after 360 seconds, all circles will have rotated
// 360*s_i  degrees, so they will all be in their initial position
//
// so simply check for t = 0s ... 360s,
// for degree = 0 ... 360,
// do all wheels include a wedge that covers degree d 
// at time t?
//
// represent wheels as vectors of pairs
// indicating their wedges

bool covers(int start, int size, int d) {
  if (d == start) return true;

  while (d < start)
    d += 360;

  return d <= start + size;
}


int main() {
  ofstream fout ("spin.out");
  ifstream fin ("spin.in");

  vector<vector<pi>> wheels;
  vi speeds;

  int s, n, x, y;
  for (int i = 0; i < 5; i++) {
    vector<pi> wheel;

    fin >> s >> n;
    speeds.push_back(s);
    for (int j = 0; j < n; j++) {
      fin >> x >> y;
      // x = start, y = number of degrees covered
      wheel.push_back({x , y});
    }
    wheels.push_back(wheel);
  }


  for (int t = 0; t <= 360; t++) {
    for (int d = 0; d < 360; d++) {

      // check if d is covered by each wheel
      // at time t
      bool allCovered = true;
      for (int wi = 0; wi < 5; wi++) {
        bool covered = false;
        // check each wedge
        for (pi &p : wheels[wi]) {
          tie(x, y) = p;
          // compute shift for this interval
          x = (x + ((speeds[wi] * t) % 360)) % 360;
          
          // if a single wedge contains d, stop 
          if (covers(x, y, d)) {
            covered = true;
            break;
          }
        }
        // if no wedges contained d, stop
        // checking d
        if (! covered) {
          allCovered = false;
          break;
        }
        //  check next wheel
      }
      if (allCovered) {
        fout << t << endl;
        return 0;
      }

    }
  }
  fout << "none" << endl;

  return 0;
}
