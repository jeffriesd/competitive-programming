/*
ID: jeffrie1
LANG: C++
TASK: crypt1
*/
/* tags: modular arithmetic, brute force
 */
#include<bits/stdc++.h>
using namespace std;

int numDigs(int n) {
  return ceil(log(n) / log(10));
}

bool hasOnlyDigs(int n, set<int> &digs) {
  if (digs.find(n % 10) == digs.end()) return false;
  if (n / 10 == 0) return true; // no more digits
  return hasOnlyDigs(n / 10, digs);
}

bool checkMult(int a, int b, int c, int d, int e, set<int> &digs) {
  // if (a == 3 && b == 2 && c == 8 && d == 8 && e == 8) {
  // }
  int abc = c + 10 * b + 100 * a;
  int de = e + 10 * d;
  int p1 = e * abc;
  int p2 = d * abc;
  int sum = de*abc;
  return numDigs(p1) == 3
      && numDigs(p2) == 3
      && hasOnlyDigs(p1, digs)
      && hasOnlyDigs(p2, digs)
      && hasOnlyDigs(sum, digs);
}

int main() {
  ofstream fout ("crypt1.out");
  ifstream fin ("crypt1.in");

  int N; 
  fin >> N;
  
  set<int> digs;
  int d;
  for (int i = 0; i < N; i++) {
    fin >> d;
    digs.insert(d);
  }

  int total = 0;
  for (int a : digs)
    for (int b : digs)
      for (int c : digs)
        for (int d : digs)
          for (int e : digs)
            if (checkMult(a, b, c, d, e, digs)) {
              total++;
              // cout << a << b << c << d << e << endl;
            }
  fout << total << endl;
  return 0;
}
