/*
ID: jeffrie1
LANG: C++
TASK: combo
*/

/* tags: modular arithmetic, brute force
 */
#include<bits/stdc++.h>
using namespace std;

int a, b, c; // fj combo
int x, y, z; // master combo
int N;

int close(int x, int y) {
  return min(abs(x-y), abs(N-abs(x-y))) <= 2;
}

bool valid(int i, int j, int k) {
  return (close(i, a) && close(j, b) && close(k, c))
      || (close(i, x) && close(j, y) && close(k, z));
}

int main() {
  ofstream fout ("combo.out");
  ifstream fin ("combo.in");
  fin >> N;

  fin >> a >> b >> c
      >> x >> y >> z;

  int total = 0;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++)
      for (int k = 1; k <= N; k++)
        if (valid(i, j, k)) total++;

  fout << total << endl;

  return 0;
}
