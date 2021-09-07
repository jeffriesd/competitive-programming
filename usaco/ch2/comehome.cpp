/*
ID: jeffrie1
LANG: C++
TASK: comehome
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define K 26
#define N 2*K
#define BARN 2*K-1

#define INF 999999999

int dist[N][N];

// a-z and A-Z is 2*L
int mapchar(char c) {
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + K;
  if (c >= 'a' && c <= 'z')
    return c - 'a';
}

char unmapchar(int i) {
  if (i < K)
    return i + 'a';
  return (i - K) + 'A';
}

void floyd() {
  for (int i = 0 ; i < N; i++) 
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        // printf("dist[%c][%c] = %d\n", unmapchar(i), unmapchar(j), dist[i][j]);
      }
    }
}

int main() {
  ofstream fout ("comehome.out");
  ifstream fin ("comehome.in");

  int P;
  fin >> P;

  for (auto& row : dist) 
    for (auto & x : row)
      x = INF;
  
  char a, b;
  int d;
  for (int i = 0; i < P; i++) {
    fin >> a >> b >> d;
    int ia, ib;
    ia = mapchar(a);
    ib = mapchar(b);
    dist[ia][ib] = min(d, dist[ia][ib]);
    dist[ib][ia] = min(d, dist[ia][ib]);
  }

  for (int i = 0; i < N; i++)
    dist[i][i] = 0;

  floyd();
  
  int m = INF;
  char c;
  // cows only live in capital letters
  for (int i = K; i < BARN; i++) {
    // printf("%c %d\n", unmapchar(i), dist[i][BARN]);
    if (dist[i][BARN] < m) { 
      c = unmapchar(i);      
      m = dist[i][BARN];
    }
  }
  fout << c << " " <<  m << endl;


  return 0;
}
