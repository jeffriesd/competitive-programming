/*
ID: jeffrie1
LANG: C++
TASK: holstein
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int V, G;
vi reqs;
vvi scoops;

ofstream fout ("holstein.out");
ifstream fin ("holstein.in");


void printVec(vi * v) {
  for (int i = 0; i < v->size(); i++) {
    fout << v->at(i);
    if (i < v->size() - 1)
      fout << " ";
  }
  fout << endl;
}


int enough(vi * state) {
  vi vit(V, 0);
  for (int i = 0; i < state->size(); i++) {
    for (int j = 0; j < V; j++) {
      vit[j] += scoops[state->at(i) - 1][j];
    }
  }
  for (int j = 0; j < V; j++)
    if (vit[j] < reqs[j]) return false;
  return true;
}

int main() {

  // number of vitamins types
  fin >> V;
  int r;
  for (int i = 0; i < V; i++) {
    fin >> r;
    reqs.push_back(r);
  }

  // number of feed types
  fin >> G;
  // matrix of feed/vitamin types
  // where scoops[i][j] = amount of vitamin j in food type i
  for (int i = 0; i < G; i++) {
    vi v(V, 0);
    for (int j = 0; j < V; j++) 
      fin >> v[j];
    scoops.push_back(v);
  }
  
  // solution: 
  // bfs through sorted permutations of feed types
  //
  // queue = { 1 , 2, 3 }
  //
  // bfs:
  // 1
  // 2
  // 3
  // 1 1 
  // 1 2
  // 1 3
  // 2 2
  // 2 3
  // 3 3
  // ....

  queue<vi> q;
  for (int i = 1; i <= G; i++) {
    vi v = { i };
    q.push(v);
  }

  set<vi> visited;
  while (! q.empty()) {
    vi state (begin(q.front()), end(q.front()));
    q.pop();


    if (enough(&state)) {
      fout << state.size() << " ";
      printVec(&state);
      break;
    }
    
    for (int next = 1 + state[state.size() - 1]; next <= G; next++) {
      vi newstate (begin(state), end(state));
      newstate.push_back(next);

      if (visited.find(newstate) == visited.end()) {

        visited.insert(newstate);
        q.push(newstate);
      }
    }
  }

  return 0;
}

