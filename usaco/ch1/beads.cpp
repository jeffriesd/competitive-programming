/*
ID: jeffrie1
LANG: C++
TASK: beads
 */

#include<bits/stdc++.h>

using namespace std;

int left(int n, int i) {
  if (i == 0) return (n - 1);
  return i - 1;
}

int right(int n, int i) {
  return (i + 1) % n;
}

int checki(int n, string s, int i) {
  int li = left(n, i);
  int ri = i;
  int rn = 0;
  char cur = 'w';
  int ln = 0;
  //cout << "li = " << i << endl;
  while (ln < n) {
    if (s[li] == 'w') { }
    else if (cur == 'w') 
      cur = s[li];
    else if (s[li] != cur)
      break;
    //cout << s[li] << " ";
    ln++;
    li = left(n, li);
  }
  li = right(n, li);
  //cout << endl;

  //cout << "(li = " << li << "); ri = " << i << endl;
  cur = 'w';
  while (rn  < n) {
    if (ri == li) break;
    if (s[ri] == 'w') { }
    else if (cur == 'w') 
      cur = s[ri];
    else if (s[ri] != cur)
      break;
    //cout << s[ri] << " " ;
    rn++;
    ri = right(n, ri);
  }
  //cout << endl;

  return min(n, ln + rn);
}

int main() {
  ofstream fout ("beads.out");
  ifstream fin ("beads.in");

  int n;
  fin >> n;

  string s;
  fin >> s;
  
  int m = checki(n, s, 0);
  for (int i = 1; i < n; i++) {
    m = max(m, checki(n, s, i));
  }
  fout << m << endl;

  return 0;
}
