// problem: https://open.kattis.com/problems/addemup

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

// upside down
// 1 - 1
// 2 - 2
// 3 ---
// 4 ---
// 5 - 5
// 6 - 9
// 7 ---
// 8 - 8
// 9 - 6
// 0 - 0

int numDigs(int n) {
  if (n == 0) return 1;

  int digs = 0;
  while (n > 0) {
    n /= 10; digs++;
  } return digs;
}

// 0-based indexing
int getDigAt(int n, int i) {
  int ri = numDigs(n) - 1 - i;
  return (n / (int)(pow(10, ri))) % 10;
}

// rotate x by 180
int flipDig(int x) {
  switch (x) { 
    case 1: return 1;
    case 2: return 2;
    case 5: return 5;
    case 6: return 9;
    case 8: return 8;
    case 9: return 6;
    case 0: return 0;
  }
  return -1;
}
long catDigs(long l, long r) {
  return pow(10,  numDigs(r)) * l + r;
}

// flip 1010
//
// 1010
// 0 + 101
// 0 + (1 + 01)
// 0 + (1 + (0 + 1))
//
int flipNum(int n) {
  int l = numDigs(n);
  if (l == 1)
    return flipDig(n);
  vi digs (l, 0);

  for (int i = 0; i < l; i++) {
    digs[i] = flipDig(getDigAt(n, l - i - 1));
    if (digs[i] < 0) return -1;
  }
  
  int x = 0;
  for (int d : digs)
    x = x * 10 + d;

  return x;
  
  // return catDigs(flipDig(getDigAt(n, l-1)), flipNum(n / 10));
}

void append(unordered_map<int, vi> & nums, int x, int i) {
  auto p = nums.find(x);
  if (p == nums.end()) {
    vi v;
    v.push_back(i);
    nums.insert({x, v});
  }
  else {
    p->second.push_back(i);
  }
}

int main() {
  int n;
  int s;
  cin >> n >> s;
  int x;

  // (x, i) in nums 
  // implies x is available at 
  // index i
  unordered_map<int, vi> nums;
  vector<pi> cards;

  for (int i = 0; i < n; i++) {
    cin >> x;

    cards.push_back({x, i});
    append(nums, x, i);
    if (flipNum(x) >= 0) {
      cards.push_back({flipNum(x), i});
      append(nums, flipNum(x), i);
    }
  }

  int i;
  for (auto &pp : cards) {
    tie(x, i) = pp;
    
    auto p = nums.find(s - x);
    if (p != nums.end())
      for (int j : p->second)
        if (j != i) {
          cout << "YES" << endl;
          return 0;
        }
  }
  cout << "NO" << endl;

  return 0;
}
