// problem: https://open.kattis.com/problems/planina

#include <bits/stdc++.h>
#include <string.h>
using namespace std;

int main() {

  double x;
  cin >> x;

  cout << setprecision(10) << pow(pow(2, x) + 1, 2);
  return 0;
}
