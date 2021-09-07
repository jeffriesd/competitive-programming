// problem: https://open.kattis.com/problems/faktor 

#include <bits/stdc++.h>
#include <string.h>
using namespace std;

int main() {

  double a, f;
  cin >> a >> f;

  cout << a * (f-1) + 1;

  return 0;
}
