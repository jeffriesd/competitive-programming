// problem:  https://naq19.kattis.com/problems/summertrip
//
// fenwick tree code is from https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/

#include <bits/stdc++.h>
using namespace std;
  
// Returns sum of arr[0..index]. This function assumes 
// that the array is preprocessed and partial sums of 
// array elements are stored in BITree[]. 
int getSum(int BITree[], int index) 
{ 
    int sum = 0; // Iniialize result 
  
    index = index + 1; 
  
    // Traverse ancestors of BITree[index] 
    while (index>0) 
    { 
        // Add current element of BITree to sum 
        sum += BITree[index]; 
  
        // Move index to parent node in getSum View 
        index -= index & (-index); 
    } 
    return sum; 
} 
  
// Updates a node in Binary Index Tree (BITree) at given index 
// in BITree. The given value 'val' is added to BITree[i] and  
// all of its ancestors in tree. 
void update(int BITree[], int n, int index, int val) 
{ 
    // index in BITree[] is 1 more than the index in arr[] 
    index = index + 1; 
  
    // Traverse all ancestors and add 'val' 
    while (index <= n) 
    { 
    // Add 'val' to current node of BI Tree 
    BITree[index] += val; 
  
    // Update index to that of parent in update View 
    index += index & (-index); 
    } 
} 
  
// Constructs and returns a Binary Indexed Tree for given 
// array of size n. 
int *constructBITree(int arr[], int n) 
{ 
    // Create and initialize BITree[] as 0 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0; 
  
    // Store the actual values in BITree[] using update() 
    for (int i=0; i<n; i++) 
        update(BITree, n, i, arr[i]); 
  
    // Uncomment below lines to see contents of BITree[] 
    //for (int i=1; i<=n; i++) 
    //     cout << BITree[i] << " "; 
  
    return BITree; 
} 

int rangeSum(int * tree, int i, int j) {
  if (i == 0)
    return getSum(tree, j);
  return getSum(tree, j) - getSum(tree, i - 1);
}

int main() {
  string s;
  cin >> s;
  int n = s.size();

  char c;
  int sum = 0;
  // table[c] = index of most recently processed 
  //            occurence of c
  unordered_map<char, int> table;

  // construct bi tree of all 0s
  int * arr = new int[s.size()];
  int * tree = constructBITree(arr, s.size());

  int endpoints = 0 ;
  for (int i = 0; i < s.size(); i++) {
    c = s[i]; 
    auto p = table.find(c);
    if (p != table.end()) {
      // if current character appears
      // previously in s

      int oldind = p->second;
      // just update table
      table.erase(c);
      table.insert(make_pair(c, i));

      // oldind      i
      //      c .... c 
      //
      // decrement tree[oldind] because 
      // oldind can't be used as a left endpoint
      // in the future 
      // because there would be another c (at index i)
      // in the subsequence, which violates the uniqueness of endpoints constraint
      update(tree, n, oldind, -1);
      update(tree, n, i, 1);

      int rs = rangeSum(tree, oldind+1, i-1);
      // cout << "oi = " << oldind << endl;
      // cout << "rs for " << c << " is " << rs << endl;
      sum += rs;
    }
    else {
      // if current character does not appear
      // previously in string, then 
      sum += endpoints;
      table.insert(make_pair(c, i));
      update(tree, n, i, 1);
      endpoints++;      
    }
  }

  cout << sum << endl;
  return 0;
}
