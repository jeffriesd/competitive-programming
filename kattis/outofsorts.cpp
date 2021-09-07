// problem: https://open.kattis.com/problems/outofsorts

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define INF 9999999999


class TreeNode {
  public:
    long val;
    bool marked;
    TreeNode * left; 
    TreeNode * right;

    TreeNode(long v) {
      left = nullptr;
      right = nullptr;
      val = v;
      marked = false;
    }

    // mark if val is below an upper bound 
    // or above a lower bound 
    void markTree(long upper, long lower) {
      if (val < upper || lower < val)
        marked = true;

      if (left)
        left->markTree(upper, min(lower, val));
      if (right)
        right->markTree(max(val, upper), lower);
    }

    int countMarked() {
      int nl = left  ? left->countMarked()  : 0;
      int nr = right ? right->countMarked() : 0;
      return (marked ? 1 : 0) + nl + nr;
    }


};

TreeNode * makeTree(vi & xs, int low, int high) {
  // make a tree consisting of elements
  // from xs[low] ... xs[high]
  //
  // build it bottom-up with middle element of 
  // sequence as the root 
  
  if (high < low) return nullptr;

  // int m = low + (high - low) / 2;
  int m = (high + low) / 2;
  // cout << xs[m] << endl;
  TreeNode * root = new TreeNode(xs[m]);
  root->left  = makeTree(xs, low, m-1);
  root->right = makeTree(xs, m+1, high);
  return root;
}


int main() {
  long n, m, a, c, x0;

  cin >> n >> m >> a >> c >> x0;

  vi seq(n, 0);
  long x = x0;
  for (int i = 0; i < n; i++) {
    x = (a * x + c) % m;
    seq[i] = x;
    // cout << x << endl;
  }

  TreeNode * root = makeTree(seq, 0, n-1);
  root->markTree(0, INF);
  cout << (n - root->countMarked()) << endl;

  return 0;
}
