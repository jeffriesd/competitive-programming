/*
ID: jeffrie1
LANG: C++
TASK: fact4
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("fact4.out");
  ifstream fin ("fact4.in");

  int N; 
  fin >> N;

  if (N == 1) { 
    fout << 1 << endl;
    return 0;
  }

  // sieve primes
  vb sieve(N+1, true);
  vi primes; 

  sieve[0] = sieve[1] = false;
  for (int i = 2; i <= N; i++) {
    if (sieve[i]) {
      primes.push_back(i);
      for (int j = i * i; j <= N; j += i){
        sieve[j] = false;
      }
    }
  }

  vi factors (primes.size(), 0);
  for (int i = 2; i <= N; i++) {
    int x = i;
    
    // factorize x
    for (int j = 0; j < primes.size() && x > 1; j++) {
      while (x % primes[j] == 0) {
        x /= primes[j];
        factors[j]++;
      }
    }
  }
  
  // remove (2, 5) pairs
  // primes[0] = 2
  // primes[1] = 3
  // primes[2] = 5
  int dropped = min(factors[0], factors[2]);
  factors[0] -= dropped; 
  factors[2] -= dropped;

  // compute product % 10
  int dig = 1;
  for (int i = 0; i < factors.size(); i++) {
    for (int j = 0; j < factors[i]; j++)
      dig = (dig * (primes[i] % 10)) % 10;
  }

  fout << dig << endl;

  return 0;
}
