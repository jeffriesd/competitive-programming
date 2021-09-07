/*
ID: jeffrie1
LANG: C++
TASK: sprime
*/
#include<bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vb = vector<bool>;
using si = set<int>;

int N;

int numDigs(int n) {
  if (n == 0) return 1;

  int digs = 0;
  while (n > 0) {
    n /= 10; digs++;
  } return digs;
}

long catDigs(long l, long r) {
  return pow(10,  numDigs(r)) * l + r;
}

bool isPrime(int x) {
  if (x % 2 == 0) return false;
  for (int i = 3; i * i <= x; i += 2)
    if (x % i == 0) return false;
  return true;
}

void genSPrimes(vector<vi> &sp, int n, int l) {
  // l = numDigs(n)
  if (l > N) return;
  sp[l].push_back(n);
  
  // only try odd endings 
  for (int x = 1; x < 10; x += 2) {
    int nx = 10*n + x;
    if (isPrime(nx) && l < N)
      genSPrimes(sp, nx, l+1);
  }
}

int main() {
  ofstream fout ("sprime.out");
  ifstream fin ("sprime.in");

  fin >> N;

  vector<vi> sprimes(N+1);
  for (int x : { 2, 3, 5, 7 }) {
    genSPrimes(sprimes, x, 1);
  }

  for (int x : sprimes[N])
    fout << x << endl;

  return 0;
}
