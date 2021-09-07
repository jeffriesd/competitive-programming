/*
ID: jeffrie1
LANG: C++
TASK: range
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define MAXN 256

int rangeSum(vvi & prefixSums, int i, int j, int ii, int jj) {
  int sum = 0;
  sum = prefixSums[ii][jj];
  // subtract horizontal region above row i
  if (i > 0)
    sum -= prefixSums[i-1][jj];
  // subtract vertical region left of column j
  if (j > 0)
    sum -= prefixSums[ii][j-1];
  // add back doubly subtracted region
  // in top left corner
  if (i > 0 && j > 0)
    sum += prefixSums[i-1][j-1];

  return sum;
}

int main() {
  ofstream fout ("range.out");
  ifstream fin ("range.in");

  int N;
  fin >> N;
  vector<vb> field (N, vb(N));
  string s;
  for (int i = 0; i < N; i++) {
    fin >> s;
    for (int j = 0; j < N; j++)
      field[i][j] = s[j] == '1'; 
  }

  vvi prefixRows(N, vi(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (j == 0) 
        prefixRows[i][j] = field[i][j];
      else
        prefixRows[i][j] = prefixRows[i][j-1] + field[i][j];
    }
  }

  // 2d prefix sums
  vvi prefixSums(N, vi(N));
  prefixSums[0][0] = field[0][0];
  // fill first column
  for (int i = 1; i < N; i++) 
    prefixSums[i][0] = prefixSums[i-1][0] + field[i][0];
  // fill first row
  for (int j = 1; j < N; j++)
    prefixSums[0][j] = prefixSums[0][j-1] + field[0][j];

  for (int i = 1; i < N; i++) {
    for (int j = 1; j < N; j++) {
      prefixSums[i][j] = prefixSums[i-1][j] + prefixRows[i][j-1] + field[i][j];
    }
  }

  vi squareSizes (N+1, 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 2; max(i+k-1, j+k-1) < N; k++) {
        if (rangeSum(prefixSums, i, j, i+k-1, j+k-1) == k*k)
          squareSizes[k]++;
      }
    }
  }
  for (int i = 1; i <= N; i++) {
    if (squareSizes[i] > 0)
      fout << i << " " << squareSizes[i] << endl;
  }

  return 0;
}
