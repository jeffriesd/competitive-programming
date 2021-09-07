/*
ID: jeffrie1
LANG: C++
TASK: msquare
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define N 8

vi board (N+1);
vi goal (N+1);

void swap(vi & v, int i, int j) {
  int t = v[i];
  v[i] = v[j];
  v[j] = t;
}

void A(vi & v) {
  swap(v, 1, 8);
  swap(v, 2, 7);
  swap(v, 3, 6);
  swap(v, 4, 5);
}

void B(vi & v) {
  int t1 = v[4];
  int t2 = v[5];
  for (int i = 4; i >= 2; i--) 
    v[i] = v[i-1];
  for (int i = 5; i <= 7; i++)
    v[i] = v[i+1];
  v[1] = t1;
  v[8] = t2;
}

void C(vi & v) {
  int t = v[7];
  v[7] = v[6];
  v[6] = v[3];
  v[3] = v[2];
  v[2] = t;
}

bool finished(vi & v, vi & goal) {
  if (v.size() < goal.size()) return false;
  for (int i = 1; i <= 8; i++)
    if (v[i] != goal[i]) return false;
  return true;
}


bool unique(vi & v) {
  vi counts (N+1, 0);
  for (int x : v) {
    if (counts[x] > 0) return false;
    counts[x]++;
  }
  return true;
}

vector<pair<char, vi>>neighbors (vi & v) {
  vi vA (begin(v), end(v));
  A(vA);
  vi vB (begin(v), end(v));
  B(vB);
  vi vC (begin(v), end(v));
  C(vC);

  if (! unique(vA)) 
    exit(0);
  if (! unique(vB)) 
    exit(0);
  if (! unique(vC)) 
     exit(0);

  // cout << "before c transform" << endl;
  // for (int x : v)
  //   cout << x;
  // cout << endl;
  // cout << "After c transform" << endl;
  // for (int x : vC)
  //   cout << x;
  // cout << endl;
  return { {'A', vA}, {'B', vB}, {'C', vC}};
}
  
int main() {
  ofstream fout ("msquare.out");
  ifstream fin ("msquare.in");

  
  for (int i = 1; i <= 8; i++) {
    fin >> goal[i];
    board[i] = i;
  }

  if (finished(board, goal)) {
    fout << 0 << endl << endl;
    return 0;
  }

  set<vi> visited;
  queue<pair<vi, vector<char>>> q;
  vector<char> empty;
  q.push({ board, empty });

  vi xs, ys;
  vector<char> seq;
  char c;
  while (! q.empty()) {
    auto p = q.front(); 
    tie(xs, seq) = p;
    q.pop();
    
    for (auto pp : neighbors(xs)) {
      tie(c, ys) = pp;

      if (finished(ys, goal)) {
        fout << seq.size() + 1 << endl;
        for (char ch : seq)
          fout << ch;
        fout << c << endl;
        return 0;
      }

      if (visited.find(ys) == visited.end()) {
        vector<char> newseq (begin(seq), end(seq));
        newseq.push_back(c);
        visited.insert(ys);
        q.push({ys, newseq});
      }
    }    
  }

  return 0;
}
