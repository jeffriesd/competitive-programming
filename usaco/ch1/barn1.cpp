/*
ID: jeffrie1
LANG: C++
TASK: barn1
*/
#include<bits/stdc++.h>
using namespace std;

#define INF 999

int main() {
  ofstream fout ("barn1.out");
  ifstream fin ("barn1.in");
  
  // 1 <= M <= 50, the maximum number of boards that can be purchased 
  // 1 <= S <= 200, the total number of stalls; 
  // 1 <= C <= S the number of cows in the stalls, 
  // next C lines
  // 1 <= stall_number <= S
  //
  // calculate the minimum number of stalls that must be 
  // blocked in order to block all the stalls that have cows in them.  
  
  int M, S, C;
  fin >> M >> S >> C;

  set<int> pr;
  int j;
  vector<bool> bv (S+1);
  for (int i = 0; i < C; i++) {
    fin >> j; 
    pr.insert(j);
    bv[j] = true;
  }
  vector<int> present (pr.begin(), pr.end());
  sort(present.begin(), present.end());

  // if each stall can be covered individually, do it
  if (M >= present.size()) {
    fout << present.size() << endl;
    return 0;
  }

  // count gaps by length and merge greedily
  vector<pair<int, int>> gap_sizes;
  int li;
  int count = 0;
  int groups = 0;
  for (int i = 1; i <= S; i++) {
    if (bv[i]) {
      if (count > 0 || i == 1)
        groups++;
      if (count > 0 && li > 1) 
          gap_sizes.push_back({ count, li });
      li = i;
      count = 0;
    }
    else {
      if (count == 0) 
        li = i;
      count++;
    }

  }
  sort(gap_sizes.begin(), gap_sizes.end());

  int totalBlocked = C;
  int i = 0;
  while (groups > M) {
    totalBlocked += gap_sizes[i].first;
    groups--;
    i++;
  }

  fout << totalBlocked << endl;

  return 0;
}
