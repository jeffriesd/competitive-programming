/*
ID: jeffrie1
LANG: C++
TASK: skidesign
*/
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;

int N; // number of hills

int rangeSum(vi &psums, int l, int r) {
  if (l <= 0) return psums[r];
  return psums[min(r,N-1)] - psums[l-1];  
}

// calculate cost of squeezing every
// value into [l,r] with range sums
// where li, ri are defined as
// heights[li] is the maximum value < l
// heights[ri] is the minimum value > r
int cost(vi &psums, vi &sqsums, int l, int r, int li, int ri) {
  // there are li + 1 hills to the left
  // of [l, r]
  //
  // there are (N - ri) hills to the right 
  // of [l, r]

  // int lcost = (li + 1) * l - rangeSum(psums, 0, li);
  // int rcost = (N - ri) * (-r) + rangeSum(psums, ri, N-1);
  // return (lcost + rcost) * (lcost + rcost);

  int nl = li + 1;
  int nr = N - ri;
  int lcost = nl * (l * l) - (2 * l * rangeSum(psums, 0, li)) + rangeSum(sqsums, 0, li);
  int rcost = rangeSum(sqsums, ri, N-1) - (2 * r * rangeSum(psums, ri, N-1)) + nr * r  * r;
  return lcost + rcost;
}

int main() {
  ofstream fout ("skidesign.out");
  ifstream fin ("skidesign.in");

  fin >> N;
  int e;
  // counts[i] = n means
  // there are n hills of height i
  vi counts (101, 0);
  vi heights (N, 0);
  int l, r;
  l = 999; 
  r = 0;
  for (int i = 0; i < N; i++) {
    fin >> e;
    counts[e]++;
    l = min(l, e);
    r = max(r, e);
    heights[i] = e;
  }
  sort(heights.begin(), heights.end());

  // compute prefix sums
  vi psums (N, 0);
  vi sqsums (N, 0);
  psums[0] = heights[0];
  sqsums[0] = heights[0] * heights[0];
  for (int i = 1; i < N; i++) {
    psums[i] = psums[i-1] + heights[i];
    sqsums[i] = sqsums[i-1] + (heights[i] * heights[i]);
  }

  if (r - l <= 17) { 
    fout << 0 << endl;
    return 0;
  }

  // try each 17 unit long interval
  // in [l, r]

  int mincost = 9999999;
  int li, ri;
  li = ri = 0;

  for (int i = l; r - i > 17; i++) {
    // cout << "i = " << i << endl;
    while (heights[li+1] < i) li++;
    while (heights[ri] <= i + 17) ri++;
    int c = cost(psums, sqsums, i, i + 17, li, ri);
    // cout << "cost for " << i << ", " << i + 17 << " =  " << c << endl;
    mincost = min(mincost, c);
  }
  
  fout << mincost << endl;
    
  return 0;
}
