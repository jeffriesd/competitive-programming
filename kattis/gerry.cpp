// problem: https://naq19.kattis.com/problems/gerrymandering

#include<bits/stdc++.h>
using namespace std;

int main() {
  int p, d;
  cin >> p >> d;


  vector<int> as;
  vector<int> bs;
  for (int i = 0; i < d ; i++) {
    as.push_back(0);
    bs.push_back(0);
  }
  
  int di, a, b;
  for (int i = 0; i < p ; i++) {
    cin >> di >> a >> b; 
    di--;
    as[di] += a;
    bs[di] += b;
  }

  int tot = 0;
  int wa, wb;
  int tota = 0, totb = 0;
  int totwa = 0, totwb = 0, totv = 0 ;
  for (int i = 0; i < d ; i++) {
    a = as[i]; b = bs[i];
    tot = a + b;
    tota += a;
    totb += b;
    totv += a + b;

    if (a < b) { 
      cout << "B";
      wa = a;
      wb = b - (floor(tot / 2) + 1);
    }
    else { 
      cout << "A";
      wb = b ;
      wa = a - (floor(tot / 2) + 1);
    }
    totwa += wa;
    totwb += wb;
    // cout << " wb = " << wb << endl;
    // cout << " wa = " << wa << endl;
    // cout << " a + b = " << a + b << endl;
    // cout << "totv " << totv << endl;
    cout << " " << wa << " " << wb << endl;
  }

  cout << setprecision(20) << ((double)abs(totwa - totwb)) / totv << endl;
  return 0;
}
