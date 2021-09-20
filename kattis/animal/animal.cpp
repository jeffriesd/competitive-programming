#include<bits/stdc++.h>
#include "splay.h"
using namespace std;
using vi = vector<int>;

const int LP = -1;
const int RP = -2;
const int COMMA = -3;

// hash function for splay tree
struct TreeHash {
  std::size_t operator()(const SplayTree& t) const {
    if (t.root == nullptr) return 0;
    return 0;
    // return t.root->hash; 
  }
};


class Node { 
  public:
    Node * parent;
    Node * left; 
    Node * right; 
    Node() : parent(nullptr), 
      left(nullptr), right(nullptr) {}

    virtual string toString() = 0;
    virtual bool isLeaf() = 0;
    virtual int getNum() = 0;

    void printInorder() {
      if (left != nullptr)
        left->printInorder();
      cout << " " << toString() << " ";
      if (right != nullptr)
        right->printInorder();
    }
}; 

class AnimalLeaf : public Node {
  public: 
    int animalNum; 
    AnimalLeaf(int a) : Node(), animalNum(a) {}

    string toString() {
      return to_string(animalNum);
    }

    bool isLeaf() { return true; } 
    int getNum() { return animalNum; } 
};

class InternalNode : public Node {
  public:
    int numLeaves; 

    InternalNode() 
      : Node(), numLeaves(0) { }

    string toString() {
      return "X";
    }

    int getNum() { 
      throw "error";
    }

    bool isLeaf() { return false; } 
};

// precondition: N > 2 
//
// construct a tree whose 
// leaves are ints 1...N
Node* readInput(string &s) {
  int num = 0;
  vi structure; 
  for (char c : s) {
    if (isdigit(c)) {
      // process digit 
      num *= 10;
      num += c - '0';
    }
    else {
      // if num is non-zero, 
      // we just finished reading a
      // number
      if (num > 0) {
        structure.push_back(num);
        num = 0;
      }

      // handle other symbols 
      if (c == '(') 
        structure.push_back(LP);
      else if (c == ',') 
        structure.push_back(COMMA);
      else if (c == ')') 
        structure.push_back(RP);
    }
  }

  // cout << "structure = " << endl;
  // for (int x : structure) 
  //   cout << x << " " ;
  // cout << endl;


  // build tree from structure 
  Node * cur = new InternalNode();
  for (int x : structure) {
    if (x > 0) { // actual number to add
      Node * p = cur->parent;
      // create new leaf where placeholder
      // internal node was 
      Node * newNode = new AnimalLeaf(x);
      newNode->parent = p;
      if (p->left == cur)
        p->left = newNode;
      else if (p->right == cur)
        p->right = newNode;
      // delete placeholder internal node 
      delete cur;
      // move cur back to parent 
      cur = p;
    }
    else if (x == LP) {
      cur->left = new InternalNode();
      cur->left->parent = cur;
      cur = cur->left;
    }
    else if (x == COMMA) {
      // go right 
      cur->right = new InternalNode();
      cur->right->parent = cur;
      cur = cur->right;
    }
    else if (x == RP) {
      if (cur->parent != nullptr)
        cur = cur->parent;
    }
  }
  return cur; 
}


// return a set of hashes representing the 
// groups contained in this AnimalTree subtree 
//
// return a splay tree and update results 
// SplayTree *buildGroups(Node* t, unordered_set<SplayTree, TreeHash> &results) {
SplayTree *buildGroups(Node* t, unordered_set<ll> &results) {
  if (t == nullptr) return new SplayTree();;

  if (t->isLeaf()) {
    SplayTree *st = new SplayTree(); 
    st->insert(t->getNum());

    // add hash of singleton tree to results
    results.insert(st->root->key);
    // results.insert(*st);

    return st; 
  }

  // allLeft = 
  //   (possibly empty) splay tree 
  //   containing all leaves of left 
  SplayTree *allLeft  = buildGroups(t->left,  results);
  SplayTree *allRight = buildGroups(t->right, results);

  int lsize = allLeft->getSize();
  int rsize = allRight->getSize();

  // WLOG allLeft is smaller than allRight
  if (lsize > rsize) {
    SplayTree *t = allLeft;
    allLeft = allRight;
    allRight = t;
  }

  // merge smaller tree into larger by 
  // inserting all keys of allLeft into allRight
  vi inorder; 
  allLeft->getInorder(inorder);
  for (int x : inorder) 
    allRight->insert(x);

  // add hash of this subtree to results 
  // TODO check for collisions 
  results.insert(allRight->root->hash);
  // results.insert(*allRight);

  // TODO delete left tree 
  delete allLeft;

  return allRight;
}


ll solve(int N, Node* t1, Node* t2) {
  if (N == 1) return 1;
  if (N == 2) return 3; 

  // traverse both trees 
  // unordered_set<SplayTree, TreeHash> alice; 
  // unordered_set<SplayTree, TreeHash> bob;
  unordered_set<ll> alice; 
  unordered_set<ll> bob;

  // TODO deal with collisions.. 
  // current solution just adds all hashes
  // and assumes same hash -> same object 

  buildGroups(t1, alice);
  buildGroups(t2, bob);
  
  int common = 0;
  for (ll x : alice)
    if (bob.find(x) != bob.end())
      common++;

  return common;
}

int main() {
  int N; 
  cin >> N; 


  // read parenthesis inputs
  string s1, s2; 
  cin >> s1 >> s2; 

  Node* t1 = readInput(s1);
  Node* t2 = readInput(s2);

  cout << solve(N, t1, t2) << endl;

  return 0;
}
