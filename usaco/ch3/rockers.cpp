/*
ID: jeffrie1
LANG: C++
TASK: rockers
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define INF 9999999

int main() {
  ofstream fout ("rockers.out");
  ifstream fin ("rockers.in");

  int N, T, M;

  // N - number of songs
  // T - maximum length of disk
  // M - number of disks / partitions
  
  fin >> N >> T >> M;

  // lengths of songs
  vi songs;
  int s;
  for (int i = 0; i < N; i++) {
    fin >> s; 
    if (s <= T)  // ignore any songs which don't fit on a disk
      songs.push_back(s);
  }
  // all songs have size <= T
  N = songs.size();

  // just try all subsets of songs

  int maxIncl = 0;
  int MAXMASK = 1 << N;
  for (int mask = 1; mask < MAXMASK; mask++) {
    // for each subset, greedily 
    // insert songs in order
    int ti = 0; // index into disks
    int tj = 0; // index into disks[ti]

    int numIncluded = 0;
    for (int i = 0; i < N; i++) {
      if (mask & (1 << i)) {
        // include songs[i]
        if (tj + songs[i] <= T) {
          tj += songs[i];  
        } else if (ti < M - 1) {
          ti++;
          tj = songs[i];
        }
        else {
          // dont update maxIncl
          numIncluded = -1;
          break;
        }
        numIncluded++;
      }
    }

    maxIncl = max(maxIncl, numIncluded);
  }



  fout << maxIncl << endl;

  return 0;
}
