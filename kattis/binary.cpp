// problem: https://open.kattis.com/problems/reversebinary
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  int N;
  cin >> N;

  vi bits;

  while (N > 0) {
    bits.push_back(N & 1);
    N /= 2; 
  }

  int m = 0; 

  for (int b : bits) {
    m <<= 1;
    m += b; 
  }

  cout << m << endl; 
  return 0;
}
