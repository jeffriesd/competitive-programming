// problem: https://open.kattis.com/problems/fyi 

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {

  long N;
  cin >> N;

  if (N >= 5550000 && N <= 5559999)
    cout << 1;
  else
    cout << 0;
  cout << endl;

  return 0;
}
