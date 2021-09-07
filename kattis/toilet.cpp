// problem: https://open.kattis.com/problems/toilet

#include<bits/stdc++.h>
using namespace std;

char flip(char c) {
  if (c == 'U') return 'D';
  return 'U';
}

int policy1(string s) {
  int flips = 0;
  char cur = s[0];
  char desired;
  for (int i = 1; i < s.length(); i++) {
    desired = s[i]; 
    // flip seat 
    if (desired != cur) {
      flips++; 
      cur = flip(cur);
    }
       
    if (cur != 'U')
      flips++;
    cur = 'U';
  }
  return flips;
}

int policy2(string s) {
  int flips = 0;
  char cur = s[0];
  char desired;
  for (int i = 1; i < s.length(); i++) {
    desired = s[i];
    if (desired != cur) {
      flips++;
      cur = flip(cur);
    }

    if (cur != 'D')
      flips++;
    cur = 'D';
  }
  return flips;
}

int policy3(string s) {

  int flips = 0;
  char cur = s[0];
  char desired;
  for (int i = 1; i < s.length(); i++) {
    desired = s[i];
    if (cur != desired) {
      flips++;
      cur = flip(cur);
    }
  }

  return flips;
}

int main() {
  string s;
  cin >> s;

  cout << policy1(s) << endl;
  cout << policy2(s) << endl;
  cout << policy3(s) << endl;

  return 0;
}
