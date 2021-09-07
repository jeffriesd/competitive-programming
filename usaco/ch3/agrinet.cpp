/*
ID: jeffrie1
LANG: C++
TASK: agrinet
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define MAXN 100
#define INF 99999999

int dist[MAXN][MAXN];
int treedist[MAXN];
bool included[MAXN] = { 0 };


int main() {
  ofstream fout ("agrinet.out");
  ifstream fin ("agrinet.in");

  int N;
  fin >> N;

  // prims algorithm - O(N^2)
  for (int i = 0; i < N; i++) 
    for (int j = 0 ; j < N; j++)
      fin >> dist[i][j];


  int mincost;
  int minedge;
  int cur = 0;
  int total = 0;
  
  for (int i = 0; i < N; i++) 
    treedist[i] = dist[cur][i];

  for (int i = 0; i < N - 1; i++) {
    included[cur] = true;
    

    mincost = INF;
    for (int j = 0; j < N; j++) {
      if (j == cur) continue;
      if (! included[j]) {
        if (treedist[j] < mincost) {
          mincost = treedist[j];
          minedge = j;
        }   
      }
    }

    total += mincost;
    cur = minedge;
    
    // must update distances
    for (int j = 0; j < N; j++)
      treedist[j] = min(dist[cur][j], treedist[j]);
  }
  
  fout << total << endl;

  return 0;
}
