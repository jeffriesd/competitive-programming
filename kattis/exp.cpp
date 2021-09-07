// problem: https://open.kattis.com/problems/dicecup 

#include <bits/stdc++.h>
#include <string.h>
using namespace std;

int main() {


  int x, y;
  cin >> x >> y;

  int p = x + y+1;
  int ps[p] = { };

  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      ps[i+j]++;
    }
  }

  int m = -1;
  for (int i = 1; i < p; i++) 
    m = max(m, ps[i]);

  for (int i = 1; i < p; i++) {
    if (ps[i]  == m ) 
      cout << i << endl;
  }

  return 0;
}
