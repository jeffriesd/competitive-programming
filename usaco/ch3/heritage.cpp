/*
ID: jeffrie1
LANG: C++
TASK: heritage
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;
#define MAXN 27

ofstream fout ("heritage.out");
ifstream fin ("heritage.in");
vi inorder;
vi preorder;

void postorder(int ni, int nj, int pi, int pj) {
  if (nj < ni || pj < pi) return;
  if (nj == ni) {
    fout << (char)inorder[ni];
    return;
  }

  // root element is preorder[pi]
  int root = preorder[pi];

  // if no left subprob:
  if (root == inorder[ni]) {
    postorder(ni+1,nj,pi+1,pj);
    fout << (char)root;
    return;
  }
  // no right subprob
  if (root == inorder[nj]) {
    postorder(ni, nj-1, pi+1, pj);
    fout << (char)root;
    return;
  }

  int i = ni;
  unordered_set<int> inleft;
  while (inorder[i] != root) {
    inleft.insert(inorder[i]);
    i++;
  }

  int j = pi+1;
  while (inleft.find(preorder[j]) != inleft.end()) 
    j++;

  postorder(ni, i-1, pi+1, j-1);
  postorder(i+1, nj, j, pj);

  fout << (char)root;
}

int main() {
  string si, sp;
  fin >> si >> sp;
  for (int i = 0; i < si.size(); i++) {
    inorder.push_back(si[i]);
    preorder.push_back(sp[i]);
  }

  postorder(0, si.size() - 1, 0, si.size() - 1);
  fout << endl;

  return 0;
}
