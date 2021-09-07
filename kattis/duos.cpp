// problem: https://mausa20.kattis.com/problems/dominatingduos

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define INF 99999999

int main() {

  int N;
  cin >> N;
  vi heights;

  for (int i = 0; i < N; i++) {
    int x ;
    cin >> x;
    heights.push_back(x);
  }

  vi stack;
  int npairs = 0;

  for (int i = 0; i < N; i++) {
    // npairs += stack.size();
    // cout << "x  = " << heights[i] << "stack size = " << stack.size() << endl;
    for (int j = stack.size()-1; j >= 0; j--) {
      npairs++;
      if (stack[j] > heights[i])
        break;
    }

    while (stack.size() && stack.back() < heights[i]) {
      stack.pop_back();
    }
    stack.push_back(heights[i]);
  }

  cout << npairs << endl;

  return 0;
}
