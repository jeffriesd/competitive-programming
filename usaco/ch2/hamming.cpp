/*
ID: jeffrie1
LANG: C++
TASK: hamming
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int N, B, D;

// compute hamming dist in 
// number of matching bits time
int hamming(int x, int y) {
  int dist = 0;
  int diff = x ^ y;
  while (diff) {
    dist++;
    // flip rightmost 1
    diff &= ~(diff & -diff);

    // dist += diff & 1;
    // diff >>= 1;
  }
  return dist;
}

int main() {
  ofstream fout ("hamming.out");
  ifstream fin ("hamming.in");
  
  fin >> N >> B >> D;

  // find N bitstrings of length B
  // s.t. 
  // forall x y. hamming(x, y) >= D

  // solution: try including every bitstring

  bool add = true;
  vi bstrings;
  for (int bits = 0; bits < (1 << (B+1)); bits++) {
    bstrings.clear();
    bstrings.push_back(bits);


    for (int xbits = 0; xbits < (1 << (B+1)); xbits++) {
      if (bits == xbits) continue;

      add = true;
      for (int s : bstrings) {
        if (hamming(s, xbits) < D) { 
          add = false; 
          break; 
        }
      }
      if (add) 
        bstrings.push_back(xbits);

    }    
    if (bstrings.size() >= N) 
      break;
  }

  for (int i = 0; i < N; i++) {
    fout << bstrings[i];
    if ((i+1) % 10 == 0) fout << endl;
    else if (i < N - 1) fout << " ";
  }
  if (N % 10 != 0) fout << endl;


  return 0;
}
