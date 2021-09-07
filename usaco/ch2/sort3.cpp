/*
ID: jeffrie1
LANG: C++
TASK: sort3
*/
#include<bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int N;

//  sorted sequence will look like
//  11112222333333333
//
//  after counting number of 1s, 2s, 3s, 
//  we know the first |1s| slots should be 1s, 
//  slots from |1s|+1 to |1s|+|2s| should be 2s,
//  and |1s|+|2s|+1 to n should be 3s
//
//  when do we need to swap:
//    a.  1 in zone 2
//    b.  1 in zone 3
//    c.  2 in zone 1
//    d.  2 in zone 3
//    e.  3 in zone 1
//    f.  3 in zone 2
//  
//  if a(x) and c(y)
//  || b(x) and e(y):
//  || d(x) and f(y):
//      swap(x, y)
//  
//  if a(x) and d(y) and e(z)
//  || b(x) and f(y) and c(z):
//      swap(x, y)
//      swap(y, z)
//
//  x    y    z
//  -----------
//  3 .. 1 .. 2 swap (y, z)
//  3 .. 2 .. 1 swap (x, z)
//  1 .. 2 .. 3
//
//  x    y    z
//  -----------
//  3 .. 1 .. 2 swap (x, z)
//  2 .. 1 .. 3 swap (x, y)
//  1 .. 2 .. 3
int main() {
  ofstream fout ("sort3.out");
  ifstream fin ("sort3.in");

  fin >> N;
  vi ones;
  vi twos;
  vi thrs;

  vi xs;

  int n1, n2, n3;
  n1 = n2 = n3 = 0;

  for (int i = 0; i < N; i++) {
    int x;
    fin >> x;

    xs.push_back(x);

    if (x == 1) {
      ones.push_back(i);
      n1++;
    }
    else if (x == 2) {
     twos.push_back(i);
     n2++;
    }
    else  {
      thrs.push_back(i);
      n3++;
    }
  }

  int t2in1, t3in1, t3in2, t1in2, t1in3, t2in3;
  t2in1 = t3in1 = t3in2 = t1in2 = t1in3 = t2in3 = 0;

  for (int i = 0; i < N; i++) {
    if (i < n1) {
      if (xs[i] == 2)
        t2in1++;
      if (xs[i] == 3)
        t3in1++;
    }
    else if (i < n1 + n2) {
      if (xs[i] == 1)
        t1in2++;
      if (xs[i] == 3)
        t3in2++;

    }
    else {
      if (xs[i] == 1)
        t1in3++;
      if (xs[i] == 2)
        t2in3++;
    }
  }
  int swaps = 0;
  // swap 1s and 2s
  while (t2in1 > 0 && t1in2 > 0) {
    t2in1--;
    t1in2--;
    swaps++;
  }
  // swap 2s and 3s
  while (t2in3 > 0 && t3in2 > 0) {
    t2in3--;
    t3in2--;
    swaps++;
  }
  // swap 1s and 3s
  while (t3in1 > 0 && t1in3 > 0) {
    t3in1--;
    t1in3--;
    swaps++;
  }

  while (t1in2 > 0 && t2in3 > 0 && t3in1 > 0) {
    t1in2--; t2in3--; t3in1--; 
    swaps += 2;
  }

  while (t1in3 > 0 && t3in2 > 0 && t2in1 > 0) {
    t1in3--; t3in2--; t2in1--; 
    swaps += 2;
  }
    
  fout << swaps << endl;


  return 0;
}
