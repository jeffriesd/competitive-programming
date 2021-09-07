// problem:  https://codingcompetitions.withgoogle.com/codejam/round/0000000000000130/00000000000004c0

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

char getChar(int n) {
  return 'A' + (n );
}

int main() {
  int T;
  cin >> T;

  int P;
  for (int t = 0; t < T; t++) {
    cout << "Case #" << t +1 << ": ";
    cin >> P;
    priority_queue<pair<int, int>> heap;

    int numSens = 0;

    int numS;
    for  (int p = 0; p < P; p++) {
      cin >> numS;
      numSens += numS;
      heap.push({numS, p});
    }

    int numTop, numNext;
    while (numSens > 3) {
      auto top = heap.top();
      heap.pop();
      numTop = top.first;

      auto next = heap.top();
      numNext = next.first;

      // one from each
      if (numTop == numNext) {
        heap.pop();
        heap.push({numTop-1, top.second});
        heap.push({numNext-1, next.second});
        cout << getChar(top.second) << getChar(next.second) << " ";
      }
      else {
        heap.push({numTop-2, top.second}); 
        cout << getChar(top.second) << getChar(top.second) << " " ;
      }
      numSens -= 2;
    }

    // if 3 left remove one
    if (numSens == 3) {
      auto top = heap.top();
      heap.pop();
      heap.push({top.first - 1, top.second});
      cout << getChar(top.second) << " ";
    } 

    auto top = heap.top();
    int tp = top.second;
    heap.pop();
    auto next = heap.top();
    int n = next.second;
    heap.pop();

    cout << getChar(tp) << getChar(n) << endl;
  }

  return 0;
}
