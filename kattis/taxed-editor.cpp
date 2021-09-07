// problem: ?
//
// input: int n, m 
//
// n books which each have a length and deadline
// m books can go past deadline 
//
// current solution: 
// 
// 
// Binary search for minimum reading speed. 
// Given a reading speed r, we need to know
// whether (n -  m) books can be read 
// without going past deadline. Any (n - m) 
// books will do, and we don't explicitly 
// need to compute which ones should get left out. 
//
//    assertion: we can prove that the (n - m) 
//    books should always be read in order
//    of their deadlines. i.e., there is no 
//    reason to read books with later deadlines
//    first (it won't allow you to read a higher
//    number of books) 
//
// to compute whether (n - m) books can be 
// read with speed r, we will sort the books
// by deadline and scan from left to right. 
//
// we compute S where S[i] is the 
// number of books 1..i that can be 
// read at speed r
//
// To compute S[i], we need to 
// try including book i and not including it. 
//
// if book i is included, then it will take 
// d = (length[i] / r) days to read. thus we 
// want to look at subproblem solutions for 1..i-1
// that have finishing times <= (deadline - d)
// (since book i should be read last, and it takes
// d days to read after the previous ones). 
//
// so we need to maintain a list of 
// (finishing time, # books read) 
// sorted on the finishing time, 
// where there is at most one entry
// for each finishing time 
// and with the number of books read 
// strictly increasing from one entry to the next. 
//
// and we need to be able to binary search in it
// for lower bound of (deadline - d), i.e., 
// the most recent finishing time. but we also need
// to insert the current solution. so we need a bst. 
//
// use map<int, int> mapping from finish times to # books read. 
//
// so when proccesing book i: 
// - d = length[i] / r
// - finish_t = deadline[i] - d
// - (ft , num_nd) = find latest finishing time ft s.t. ft < finish_t
// - new_ft = finish_t + d
// - insert(new_ft, num_nd+1)
// - possibly prune map[new_ft+1] to keep it strictly increasing
//
// // should we only look at most recent finish ? 
// // it will have the most books finished, but maybe this is too greedy? 
//
//
// X---Y---===D
//
// a-1 a   d=3
//
// if we extend Y, we get a+1 books read at Y+d,
// but if we extend X we get a books read at X+d. 
// is it possibly that extending X could be better than Y
// by giving an earlier total finish time? i.e., can 
//
// X+d < Y? 
//
// let k = Y - X, so Y = X + k 
//
// X+d < X+k
//
// it just has to be that d < k. Then X+d < Y. 
// so it (maybe?) could be necessary 
// for future solutions to include 
// other subproblem solutions besides the most 
// recently available one. 
//
// anyways, which previous subproblems should we extend? 
// we have a list of (ft, nb) where each entry is increasing nb. 
// if we can "improve" the list i.e., deliver more books at an earlier 
// finish time, we should do so. but which previous subproblems should
// be considered? 
//
// naive approach for exercise: 
// - go to each previous entry (ft, nb)
// - compute (ft + d, nb + 1) 
// - check whether any entries need to be removed
// - should only need to check previous entry 
//   for (nb + 1)
//
//
//
//
//
// we also maintain a list: 
//
// - sorted list of finishing times
//
//  
//
//

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define WHITE 1
#define BLACK 2

// number of customers
int N;

// manhattan distance between two points 
int taxi(int x1, int y1, int x2, int y2) {
  int dx = abs(x1 - x2);
  int dy = abs(y1 - y2);
  return dx + dy;
}

// manhattan distance between two pair<int> 
int taxip(pi p1, pi p2) {
  return taxi(p1.first, p1.second, p2.first, p2.second);
}

// is it possible to bicolor this graph?
bool _bicolor(vvi & adj, vi & visited, int i, int cl) {
  // visited[i] = 0 -- unvisited
  // visited[i] = 1 -- visited, colored white
  // visited[i] = 2 -- visited, colored black 
  visited[i] = cl;
  for (int nb : adj[i]) {
    if (! visited[nb]) 
      if (! _bicolor(adj, visited, nb, (WHITE + BLACK) - cl))
        return false;
    if (visited[nb] == cl) 
      return false;
  }
  return true;
}

// is it possible to bicolor this graph?
bool bicolor(vvi & adj) {
  vi visited (N, 0);
  // need to iterate through all nodes because there 
  // could be disjoint subgraphs 
  for (int i = 0; i < N; i++) 
    if (! visited[i])
      if (! _bicolor(adj, visited, i, BLACK))
        return false;
  return true;
}

vvi makeGraph(vector<pi> & customers, int d) {
  // make a graph with all edges
  // with weight <= d removed 
  vvi adj;

  // add edges between each pair of customers
  for (int i = 0; i < N; i++) {
    adj.push_back(vi());
    for (int j = 0; j < N; j++) {
      // skip self edges 
      if (i == j) continue;
      // skip edges with weight <= d 
      if (taxip(customers[i], customers[j]) > d) 
        adj[i].push_back(j);
    }
  }
  return adj;
}

/*
*  binary search for minimum distance md needed 
*  to partition groups so that 
* 
*  max(diam(g1), diam(g2)) <= md
* 
*  we can check whether it is possible to partition 
*  the groups in this way by: 
*  1) constructing a graph with all edges <= md removed
*  2) bicolor the modified graph 
*
*  why bicoloring works to test diameter: 
*  - if bicoloring is possible, then we can assign customers
*  to g1 and g2 based on their colors. Since all the 
*  edges >md go between the groups, only edges
*  <=md remaining within each group, so the 
*  diameter constraint is satisfied  
*
*  - if we have groupings g1 and g2 such that 
*  max(diam(g1), diam(g2)) <= md, then all 
*  edges >md are between the groups, which 
*  means we can bicolor the modified graph
* 
*  - therefore we can bicolor modified graph 
*  iff we can group with max(diam(g1), diam(g2)) <= md
*/
int binsearch(int lo, int hi, vector<pi> & customers) {
  if (lo >= hi) return lo; 
  int mid = (lo/2) + (hi/2);

  // check if mid can be decreased
  vvi adj = makeGraph(customers, mid);
  bool canLower = bicolor(adj);

  if (canLower) 
    return binsearch(lo, mid, customers);
  return binsearch(mid+1, hi, customers);
}

int main() {
  cin >> N;
  if (N <= 2)  {
    cout << 0 << endl;
    return 0;
  }

  vector<pi> customers; 

  int x, y;
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    customers.push_back({ x, y });
  }

  int maxdist = 0;
  for (int i = 0; i < N; i++) 
    for(int j = i; j < N; j++) 
      maxdist = max(maxdist, taxip(customers[i], customers[j]));

  // binary search for minimum of two diameters, md
  // (check whether customers be partitioned into 
  // groups g1, g2 so that max(diam(g1), diam(g2)) == md)
  cout << binsearch(0, maxdist, customers) << endl;

  return 0;
}
