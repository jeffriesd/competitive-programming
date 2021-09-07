/*
ID: jeffrie1
LANG: C++
TASK: gift1
 */

#include<bits/stdc++.h>
// #include <iostream>
// #include <fstream>
// #include <string>

using namespace std;

int main() {
  ofstream fout ("gift1.out");
  ifstream fin ("gift1.in");

  unordered_map<string, int> accs;
  
  int np; 
  fin >> np;
  
  string s, s2;
  vector<string> names;
  for (int i = 0; i < np; i++) {
    fin >> s;
    names.push_back(s);
    accs[s] = 0;
  }

  int c, n;
  int each;
  for (int i = 0; i < np ; i++) {
    fin >> s;
    fin >> c >> n;

    if (n == 0) continue;

    each = c / n;
    accs[s] -= c;
    accs[s] += (c - (each * n));
    for (int j = 0; j < n; j++) {
      fin >> s2;
      accs[s2] += each;
    }
  } 

  for (string ns : names)
    fout << ns << " " << accs[ns] << endl;

  return 0;
}
