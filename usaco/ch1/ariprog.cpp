/*
ID: jeffrie1
LANG: C++
TASK: ariprog
*/
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using bi = vector<bool>;
using si = set<int>;
int N, M;
bool found = false;

ofstream fout ("ariprog.out");
ifstream fin ("ariprog.in");

// xs is sorted 
void countProgs(vi &xs, bi &bv, int b) {
  // chains[i] = number of values
  // in ari seq w common diff of b
  // ending at i
  vi chains (bv.size(), 1);

  // step through xs and for each
  // xs[i] check xs[i] - b
  for (int x : xs) {
    if (x - b >= 0) {
      // if x - b is present
      if (bv[x - b]) {
        chains[x] = chains[x-b] + 1;
        if (chains[x] >= N) {
          fout << (x - b*(N-1)) << " " << b << endl;
          found = true;
        }
      }
    }
  }  
}

int main() {
  fin >> N >> M;

  si bs;

  // bit vector 
  bi bv(125001, false);

  for (int p = 0; p <= M; p++) {
    for (int q = 0; q <= M; q++) {
      bs.insert(p*p + q*q); 
      bv[(p*p + q*q)] = true;
    }
  }
  vi bss(begin(bs), end(bs));
  sort(begin(bss), end(bss));

  // max value
  int m = bss[bss.size() - 1];

  for (int i = 1; i <= m / (N - 1); i++) 
    countProgs(bss, bv, i);

  if (! found )
    fout << "NONE" << endl;

  return 0;
}
