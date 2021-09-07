/*
ID: jeffrie1
LANG: C++
TASK: maze1
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;


#define MAXW 38
#define MAXH 100
#define INF 999999

int W, H;

// use 0 based indexing
bool wall[2*MAXH+1][2*MAXW+1];

int mindist[2*MAXH+1][2*MAXW+1];

int bfs(int i, int j) {
  bool visited[2*H+1][2*W+1] = {{ 0 }};

  queue<pair<int, pi>> q;
  q.push({0, { i, j }});
  visited[i][j] = true;

  int maxd = 0;


  int ii, jj;
  int di, dj;
  vector<pi> v = { {0, 1}, {0, -1}, {1, 0 }, {-1, 0}};
  pi p;
  int d;
  while (! q.empty()) {
    tie(d, p) = q.front();
    tie(i, j) = p;
    q.pop();

    maxd = max(maxd, d);
    mindist[i][j] = min(mindist[i][j], d);
    // printf("visit %d, %d: %d\n", i, j, d);

    for (pi &pp : v) {
      tie(di, dj) = pp;
      ii = i + 2*di;
      jj = j + 2*dj;
      // printf("maybe visit %d, %d  %d\n", ii, jj, wall[ii][jj]);
      if (ii < 0 || jj < 0 || ii >= 2*H || jj >= 2*W || visited[ii][jj] || wall[i+di][j+dj])
        continue;
      visited[ii][jj] = true;
      q.push({d+1, { ii, jj }});
    }
  }
  return maxd;
}


int main() {
  ofstream fout ("maze1.out");
  ifstream fin ("maze1.in");

  fin >> W >> H;
  string s;
  char c;

  vector<pi> exits;

  getline(fin, s); // get newline
  for (int i = 0; i < 2*H+1; i++) {
    getline(fin, s);
    for (int j = 0; j < 2*W+1; j++) {
      mindist[i][j] = INF;

      c = s[j];
      if (c == ' ') {
        wall[i][j] = false;
        // printf("walls[%d][%d] = false\n", i, j);

        if (i == 2*H) 
          exits.push_back({ i-1, j });
        else if (i == 0) 
          exits.push_back({ 1, j });
        else if (j == 2*W) 
          exits.push_back({ i, j-1 });
        else if (j == 0) 
          exits.push_back({ i, 1 });
      }
      else
        wall[i][j] = true;
    }
  }

  bfs(exits[0].first, exits[0].second) ;
  bfs(exits[1].first, exits[1].second) ;

  int maxd = 0;
  for (int i = 0; i < 2*H+1; i++) {
    for (int j = 0; j < 2*W+1; j++) {
      // if (mindist[i][j] == INF)
      //   cout << "- ";
      // else
      //   cout << mindist[i][j] << " " ;
      if (mindist[i][j] == INF) continue;
      maxd = max(maxd, 1+mindist[i][j]);
    }
    // cout << endl;
  }



  fout << maxd << endl;


  return 0;
}
