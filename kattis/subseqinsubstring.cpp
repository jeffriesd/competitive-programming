// problem: https://open.kattis.com/problems/subsequencesinsubstrings

#include <bits/stdc++.h> 
#include <iostream>
#include <string.h>
using namespace std;

int main() {
  string s, t;
  cin >> s >> t;
  int slen = s.length();
  int tlen = t.length();

  if (slen == 1) {
    cout << (s[0] == t[0] ? 1 : 0);
    return 0;
  }

  long ans = 0;

  // int next [slen+1][26];
  vector<vector<int>> next (slen+1, vector<int>(26, -1));

  char c;
  for (int i = slen; i > 0; i--) {
    for (int j = 0, c = 'a'; c <= 'z'; c++, j++) {
      if (s[i-1] == c) next[i-1][j] = i;
      else next[i-1][j] = next[i][j];
    }
  }

  // iterate through starting indices
  int end;
  for (int i = 0; i <= slen; i++) {
    end = i;
    for (int j = 0; j < tlen && end != -1; j++) 
      end = next[end][t[j] - 'a'];
    if (end != -1) 
      ans += slen - end + 1;
  }

  cout << ans << endl;

  return 0;
}
