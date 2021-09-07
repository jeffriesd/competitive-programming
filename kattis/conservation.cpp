// problem: https://open.kattis.com/problems/conservation

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

class Node {
  public :
    int lab;
    // vi neighbors;
    // set<int> in;
    set<int> out;
    bool marked; 
    int depth;
    int numIn;
    Node(int labNum) {
      lab = labNum; 
      marked = false;
      depth = 0;
      numIn = 0;
    }
    void addIn(int i) {
      // in.insert(i);
      numIn++;      
    }

    void delIn(int i) {
      // in.erase(i);
      numIn--;
    }

    bool source() {
      return numIn == 0;
    }
};


class NodeSets {
  public:
    set<int> lab1;
    set<int> lab2;
    set<int> * labs;
    vector<Node> nodes;

    NodeSets(vector<Node> nodes) {
      this->nodes = nodes;
      labs = new set<int>[3];
      labs[1] = lab1;
      labs[2] = lab2;
    }


    /** insertSource
     *    insert into source sets
     *
     *    invariants: 
     *      - only in source/lab set if not yet marked
     */
    void insertSource(int n) {
      labs[nodes[n].lab].insert(n);
    }

    // remove from set and remove outgoing edges
    // -- only called if not previously marked
    void markNode(int n) {
      // cout << "mark " << n+1 << endl;
      nodes[n].marked = true;
      int end;
      for (auto it= nodes[n].out.begin(); 
           it != nodes[n].out.end(); it++) 
      {
        end = *it;
        if (nodes[end].marked) continue;

        nodes[end].delIn(n);
        if (nodes[end].source())
          insertSource(end);
      }
    }

    bool visit(int li) {
      if (labs[li].empty()) return false;
      bool any = false;
      while (! labs[li].empty()) {
        // pick element and remove it
        int src = *labs[li].begin();
        // cout << " visit src " << src << endl;
        labs[li].erase(labs[li].begin());
        markNode(src);
        any = true;
      }
      return any;
    }

    int ans(int start) {
      int cur = start;
      int cross = 0;
      bool v;
      while (!(labs[1].empty() && labs[2].empty())) {
        // cout << " on side " << cur << endl;
        if ((v = visit(cur)) && !labs[(3-cur)].empty()) {
          cross++;
        }
        cur = 3 - cur;
      } 
      // cout << cross << endl;
      return cross;
    }

};


void solve() {

  int n, m;
  cin >> n >> m;

  vector<Node> nodes;

  int lab; 
  for (int i = 0; i < n; i++) { 
    cin >> lab;
    nodes.push_back(Node(lab));
  }

  int x, y; 
  set<Node> sources;
  for (int i = 0; i < m; i++) {
    cin >> x >> y; 
    x--; y--; // use 0 based indexing
    // nodes[x].neighbors.push_back(y);
    nodes[x].out.insert(y);
    nodes[y].addIn(x);
  }

  NodeSets labs(nodes);

  for (int i = 0; i < n; i++) 
    if (nodes[i].source()) { 
      labs.insertSource(i);
    }

  NodeSets labs2(nodes);

  for (int i = 0; i < n; i++) 
    if (nodes[i].source()) { 
      labs2.insertSource(i);
    }

  int t1 = labs.ans(1);
  int t2 = labs2.ans(2);
  // cout << t1 << " " << t2 << endl;
  cout << min(t1, t2)  << endl;
}
int main() {
  int T;
  cin >> T; 

  for (int ti = 0; ti < T; ti++) {
    // cout << "-- case " << ti << "--" << endl;
    solve();
  }

  return 0;
}

