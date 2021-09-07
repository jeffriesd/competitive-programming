// problem: https://open.kattis.com/problems/leftandright

#include<bits/stdc++.h>
using namespace std;

void print_vec(vector<int> a) {
  for (int i = 0; i < a.size(); i++)
    cout << a[i] << endl;
}

int main() {
  int n;
  cin >> n;

  vector<int> ans;
  char c;
  vector<pair<int, int>> ps;
  int left = n-1;
  bool inLs = false;
  for (int i = 0; i < n-1; i++) {
    cin >> c;
    if (c == 'L') {
      if (!inLs) left = i;
      inLs = true;
    }
    else {
      if (inLs) ps.push_back(make_pair(left, i-1));
      inLs = false;
    }
    ans.push_back(i+1);
  }
  if (inLs) ps.push_back(make_pair(left, n-1));
  ans.push_back(n);
  
  int right;
  for (auto it = ps.begin(); it != ps.end(); it++) {
    left  = max(0, it->first);
    right = min(n-1, it->second + 1);
    
    // print_vec(ans);
    // cout << "reverse " << left << " " << right << endl;
    reverse(begin(ans) + left, begin(ans) + right + 1);
  }


  print_vec(ans);

  return 0;
}
