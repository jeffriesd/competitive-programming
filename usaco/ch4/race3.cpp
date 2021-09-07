/*
ID: jeffrie1
LANG: C++
TASK: race3
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;


class Graph {
  vvi adj;
  int src;
  int sink;
  public:
    Graph (vvi adj, int src, int sink) {
      this->adj = adj;
      this->src = src;
      this->sink = sink;
    }

    bool unavoidable(int x) {
      if (x == sink || x == src)
        return false;
      vb reach = reachable(src, x);
      // printf("sink = %d\n", sink);
      return ! reach[sink];
    }

    vb reachable(int s, int x) {
      // s - starting node
      // x - this node is not allowed

      // do a modified bfs
      // to check if x is 
      // unavoidable 
      //
      // dont allow any node to visit x in bfs

      queue<int> q;
      q.push(s);

      vb inqueue(adj.size());
      inqueue.assign(adj.size(), false);

      inqueue[s] = true;

      while (! q.empty()) {
        int cur = q.front();
                                                    
        q.pop();
        for (int v : adj[cur]) {
          // dont go to node x 
          if (v != x && ! inqueue[v]) {
            q.push(v);
            inqueue[v] = true;
          }
        }
      }

      return inqueue;
    }

    bool splitting(int x) {
      // node x is splitting iff
      // graph can be partitioned 
      // int G1, G2 s.t. 
      // G1 G2 disjoint in nodes and arrows
      // end(G1) = start(G2) = x
      //


      if (x == sink || x == src)
        return false;

      if (! unavoidable(x)) 
        return false;

      // x is splitting iff these
      // two sets are disjoint 
      vb srcReach = reachable(src, x);

      // if sink not reachable from x, 
      // x isn't splitting
      vb xreach = reachable(x, -1);
      if (! xreach[sink])
        return false;

      // check if the two sets form
      // a partition
      for (int i =0 ; i < adj.size(); i++) {
        if (!(srcReach[i] ^ xreach[i]))
          return false;
      }

      return true;
    }
};

int main() {
  ofstream fout ("race3.out");
  ifstream fin ("race3.in");


  vvi adj;

  int x;
  int i;
  for (i = 0; ; i++) {
    fin >> x;
    if (x == -1) break;
    adj.push_back(vi());

    for (int j = 0; ; j++) {
      if (x < 0) break;
      adj[i].push_back(x);
      fin >> x;
    }
  }

  Graph g = Graph(adj, 0, adj.size() - 1);

  vi u;
  vi s;
  for (int i = 0; i < adj.size(); i++) {
    if (g.unavoidable(i)) 
      u.push_back(i);

    if (g.splitting(i)) 
      s.push_back(i);
  }

  fout << u.size();
  for (int i = 0; i < u.size(); i++) 
    fout << " " << u[i];
  fout << endl;


  fout << s.size();
  for (int i = 0; i < s.size(); i++) {
    fout << " " << s[i];
  }
  fout << endl;

  // output: unavoidable points (excluding start/finish)
  // and splitting points 
  //
  // point is unavoidable iff
  // removing it from graph makes
  // goal unreachable 
  //
  // point S is splitting iff
  // point is neither start nor finish
  // and the graph can be partitioned into 
  // two disjoint graphs (no common arrows) 
  // with S as their only common point
  //
  //
  // splitting(x) implies unavoidable(x)
  //
  // unavoidable(x) is necessary for
  // splitting(x) 
  // - if x is splitting, then it 
  //  separates the start and goal 
  //
  // when is a node unavoidable but not 
  // splitting? if there are some
  // asymmetric arrows that
  // go across the partition (so it's 
  // not a true partition, but
  // the goal is still unreachable from the start)
 

  // easy to check if unavoidable
  // -- remove node and DFS from start
  // if goal reached, then return false
  //
  //  otherwise return true
  //
  // the set of reachable nodes (from the start)
  // form a potential partition
  //
  // if the remaining nodes are disjoint
  //  from reachable
  //  AND there are no arrows between
  //  these two sets, 
  //
  //  then it is also a splitting node 

  return 0;
}
