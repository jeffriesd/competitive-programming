/*
ID: jeffrie1
LANG: C++
TASK: ttwo
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define N 10
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int walls[N][N];

int rotate(int d) {
  return (d + 1) % 4;
}

pi movedir(int i, int j, int dir) {
  pi p;
  switch(dir) {
    case NORTH:
      p.first = i-1;
      p.second = j;
      return p;
    case EAST:
      p.first = i;
      p.second = j+1;
      return p;
    case SOUTH:
      p.first = i+1;
      p.second = j;
      return p;
    default:
      p.first = i;
      p.second = j-1;
      return p;
  }
}

bool blocked(int i, int j) {
  return i < 0 || j < 0 | i >= N || j >= N || walls[i][j];
}

bool move (pi &p, int dir) {
  int i, j;
  tie(i, j) = p;
  pi m = movedir(i, j, dir);

  if (blocked(m.first, m.second))
    return false;
  
  p.first = m.first;
  p.second = m.second;
  return true;
}

int main() {
  ofstream fout ("ttwo.out");
  ifstream fin ("ttwo.in");

  string s;

  pi john;
  pi cows;
  for (int i = 0; i < N; i++) {
    getline(fin, s);
    for (int j = 0; j < N; j++) {
      if (s[j] == '*')
          walls[i][j] = true;
      else {
        walls[i][j] = false;
        if (s[j] == 'C') {
          cows.first = i;
          cows.second = j;
        }
        if (s[j] == 'F') {
          john.first = i;
          john.second = j;
        }
      }
    }
  }

  int jd, cd;
  jd = cd = NORTH;
  int minutes = 0;
  
  bool visited[N][N][N][N][4][4] = { false };

  while (john.first != cows.first || john.second != cows.second) {
    if (visited[john.first][john.second][cows.first][cows.second][jd][cd]) {
      fout << 0 << endl;
      return 0;
    }
    visited[john.first][john.second][cows.first][cows.second][jd][cd] = true;

    if (! move(john, jd)) 
      jd = rotate(jd);
    if (! move(cows, cd))
      cd = rotate(cd);
    minutes++;
  }

  fout << minutes << endl;


  return 0;
}
