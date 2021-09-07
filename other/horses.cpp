// problem: https://codingcompetitions.withgoogle.com/codejam/round/0000000000000130/0000000000000524

#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int main() {
  int T;
  cin >> T;

  double dest, H;
  for (int t = 0; t < T; t++) {
    cin >> dest;
    cin >> H;
    
    double maxX = -1;
    double sp, st;
    double x;
    for (int h = 0; h < H; h++) {
      cin >> st >> sp;
      x = (dest - st) / sp;
      maxX = max(x, maxX);
    }
    double ans = dest / maxX;
    cout << "Case #" << t+1 << ": " << fixed << setprecision(6) << ans << endl;
  
  }
}
