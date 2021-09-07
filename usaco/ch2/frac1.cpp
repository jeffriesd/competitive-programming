/*
ID: jeffrie1
LANG: C++
TASK: frac1
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("frac1.out");
  ifstream fin ("frac1.in");

  int N;
  fin >> N;

  vector<vb> sieve;
  for (int i = 0 ; i < N; i++) {
    vb s(N, false);
    sieve.push_back(s);
  }

  vector<pi> reduced;
  for (int num = 1; num <= N; num++) {
    for (int den = N; den > num; den--) {
      if (sieve[num][den]) continue; 

      reduced.push_back({num , den});
      int mult = 1;
      while (mult * num <= N && mult * den <= N) {
        sieve[mult*num][mult*den] = true;
        mult++;
      }
    }
  }

  sort(begin(reduced), end(reduced), 
    [](const pi & a, const pi & b) {
      // sort by real value of fraction 
      double x = a.first / (double)a.second;     
      double y = b.first / (double)b.second;     
      return x < y; // reversed
    });
  fout << "0/1" << endl;
  for (pi p : reduced)
    fout << p.first << "/" << p.second << endl;
  fout << "1/1" << endl;


  return 0;
}
