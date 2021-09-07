/*
ID: jeffrie1
LANG: C++
TASK: castle
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define WEST 1
#define NORTH 2
#define EAST 4
#define SOUTH 8

int M, N;
bool ** visited;
vvi walls;
// vector<pi> nbs;
int nbs [4][2] = {
  {-1, -1},
  {-1, -1},
  {-1, -1},
  {-1, -1}
};


void printRoom(vvi & walls) {

  cout << " +";
  for (int j = 1; j <= M; j++)
    cout << "---" ;
  cout << "+" << endl;

  cout << "  ";
  for (int j = 1; j <= M; j++) 
    cout << "_" << j << "|";
  cout << endl;

  for (int i = 1; i <= N; i++) {
    // north walls

    cout << " |";
    for (int j = 1; j <= M; j++) {
      if (walls[i][j] & NORTH)
        cout << "NNN";
      else
        cout << "   ";

    }
    cout << "|" << endl << i << "|";


    // west / east walls
    for (int j = 1; j <= M; j++) {
      if (walls[i][j] & EAST) {
        if (walls[i][j] & WEST) 
          cout << "W.E";
        else 
          cout << " .E";
      }
      else if (walls[i][j] & WEST) 
        cout << "W. ";
      else 
        cout << " . ";
    }
    cout << "|" << endl << " |";
    // south walls
    for (int j = 1; j <= M; j++) {
      if (walls[i][j] & SOUTH)
        cout << "SSS";
      else
        cout << "   ";
    }
    cout << "|" << endl;

  }

  cout << " +";
  for (int j = 1; j <= M; j++)
    cout << "---" ;
  cout << "+" << endl;
}


void clear(bool** x) {
  for (int i = 1; i <= N; i++) 
    memset(x[i], 0, sizeof(bool) * (M+1));
}

int dfs(int i, int j) {
  if (i < 1 || i > N || j < 1 || j > M) 
    return 0;
  // cout << "\tvisit " << i << ", " << j << endl;

  visited[i][j] = true;

  int roomSize = 1;

  if ((! (walls[i][j] & NORTH)) && (i > 1 && (! (walls[i-1][j] & SOUTH)) )) {
      if (! visited[i-1][j])
        roomSize += dfs(i-1, j);
        
  }
  else {
    nbs[0][0] = -1;
  }

  if ((! (walls[i][j] & SOUTH)) && (i < N && (! (walls[i+1][j] & NORTH)) )) {
      // nbs.push_back({i+1, j});
      nbs[1][0] = i+1;
      nbs[1][1] = j;
      if (! visited[i+1][j])
        roomSize += dfs(i+1, j);
  }
  else
    nbs[1][0] = -1;

  if ((! (walls[i][j] & WEST)) && (j > 1 && (! (walls[i][j-1] & EAST)) )) {
      if (! visited[i][j-1])
        roomSize += dfs(i, j-1);
  }
  else
    nbs[2][0] = -1;

  if ((! (walls[i][j] & EAST)) && (j < M && (! (walls[i][j+1] & WEST)) )) {
      nbs[3][0] = i;
      nbs[3][1] = j+1;
      if (! visited[i][j+1])
        roomSize += dfs(i, j+1);
  }
  else 
    nbs[3][0] = -1;

  return roomSize;
}

pi largestRoom() {
  clear(visited);
  int m = 1;

  int numRooms = 0;
  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++)
      if (! visited[i][j]) {
        // cout << "room at " << i << " " << j << endl;
        numRooms++;
        // visited[i][j] = true;
        m = max(m, dfs(i, j));
      }
  return {m, numRooms};
}

vi removeWall() {
  // try removing every wall


  // state for choosing optimal wall to remove
  // = {count, i, j, dir}
  vi maxState = {0, 0, 0, 0};

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= M; j++) {
      int w = walls[i][j];
      for (int dir : {NORTH, EAST}) {
        if (walls[i][j] & dir) {
          // cout << endl << endl;
          // printRoom(walls);

          walls[i][j] &= ~dir;
          // remove 'dual' wall
          if (dir == EAST && j <= M-1) 
            walls[i][j+1] &= ~WEST;
          else if (dir == NORTH && i > 1)
            walls[i-1][j] &= ~SOUTH;

          // DEBUG 
          // cout << endl << "remove wall " << i << " " << j << " " << (dir == NORTH ? "N" : "E") << endl;
          // printRoom(walls);

          pi p = largestRoom();

          // cout << i << " " << j << " " << "; " << (dir == NORTH ? "N" : "E")<< " " << p.first << endl;

          // break ties
          if (p.first == maxState[0]) {
            if (j < maxState[2] || (j == maxState[2] && i > maxState[1])) {
              maxState[1] = i;
              maxState[2] = j;
              maxState[3] = dir;
            }
          }
          if (p.first > maxState[0]) {
            maxState[0] = p.first;
            maxState[1] = i;
            maxState[2] = j;
            maxState[3] = dir;
          }

          walls[i][j] |=  dir;

          // restore dual wall
          if (dir == EAST && j <= M-1) 
            walls[i][j+1] |= WEST;
          else if (dir == NORTH && i > 1)
            walls[i-1][j] |= SOUTH;

        }
      }
    }
  return maxState;
}


int main() {
  ofstream fout ("castle.out");
  ifstream fin ("castle.in");

  fin >> M >> N;

  visited = (bool**) malloc((sizeof (bool*))*N+1);


  for (int i = 0; i < N+1; i++) {
    visited[i] = new bool[M+1];
  }

  for (int i = 0; i < N+1; i++) {
    vi wallrow(M+1, 0);
    walls.push_back(wallrow);
  }

  int x;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      fin >> x;
      walls[i][j] = x;
    }
  }


  pi p = largestRoom();
  // printRoom(walls);

  vi q = removeWall();

  fout << p.second << endl;   // number of rooms
  fout << p.first << endl;    // largest room size
  fout << q[0] << endl;
  fout << q[1] << " " << q[2] << " " << (q[3] == NORTH ? "N" : "E") << endl;

  return 0;
}
