/*
ID: jeffrie1
LANG: C++
TASK: milk3
*/
#include<bits/stdc++.h>
using namespace std;
using state = tuple<int, int, int>;
using vs = vector<state>;
using vi = vector<int>;

int A, B, C;

vs neighbors(state s) {
  int a, b, c;
  tie(a, b, c) = s;
  vs nbs;

  // pour a b
  // a c
  if (a > 0) {
    int ab = min(B - b, a);
    nbs.push_back({a -  ab, b + ab, c}); 
    int ac = min(C - c, a);
    nbs.push_back({a - ac, b, c + ac});
  }
  // b a
  // b c
  if (b > 0) {
    int ba = min(A - a, b);
    nbs.push_back({a + ba, b - ba, c});
    int bc = min(C - c, b);
    nbs.push_back({a, b - bc, c + bc});
  }
  // c a 
  // c b  
  if (c > 0) {
    int ca = min(A - a, c);
    nbs.push_back({a + ca, b, c - ca});
    int cb = min(B - b, c);
    nbs.push_back({a, b + cb, c - cb});
  }
  return nbs;
}

int main() {
  ofstream fout ("milk3.out");
  ifstream fin ("milk3.in");
  fin >> A >> B >> C;
  queue<state> q;

  set<state> visited;

  set<int> cvalues;
  q.push({0, 0, C});
  while (!q.empty()) {
    state cur = q.front();
    q.pop();

    // check if A is empty
    if (get<0>(cur) == 0)
      cvalues.insert(get<2>(cur));

    for (state s : neighbors(cur)) {
      // not visited
      if (visited.find(s) == visited.end()) {
        visited.insert(s);
        q.push(s);
      }
    }
  }
  vi cv (begin(cvalues), end(cvalues));
  sort(begin(cv), end(cv));

  for (int i = 0; i < cv.size() - 1; i++)
    fout << cv[i] << " ";
  fout << cv[cv.size() - 1] << endl;

  return 0;
}
