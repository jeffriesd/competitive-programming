/*
ID: jeffrie1
LANG: C++
TASK: numtri
*/
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;

int main() {
  ofstream fout ("numtri.out");
  ifstream fin ("numtri.in");

  int N; 
  fin >> N;

  vector<vi> rows(N);

  int x;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      fin >> x;
      rows[i].push_back(x);
    }
  }


  vector<vi> sums(N);
  sums[0].push_back(rows[0][0]);

  int l, r;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      l = r = 0;
      if (j - 1 >= 0) {
        l = sums[i-1][j-1];      
      }   
      if (j < i)
        r = sums[i-1][j];
      sums[i].push_back(max(l, r) + rows[i][j]);
    }
  }

  int maxSum = 0;
  for (int x : sums[N-1])
    maxSum = max(maxSum, x);

  fout << maxSum << endl;

  return 0;
}
