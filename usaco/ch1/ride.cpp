/*
ID: jeffrie1
LANG: C++
TASK: ride
 */

#include<bits/stdc++.h>
// #include <iostream>
// #include <fstream>
// #include <string>

using namespace std;

int main() {
  ofstream fout ("ride.out");
  ifstream fin ("ride.in");
  int a,b;
  a = b = 1;

  string s1, s2;
  fin >> s1 >> s2;

  int y;
  for (char c : s1) {
    a *= (c - 'A') + 1;
  }
  for (char c : s2) 
    b *= (c - 'A') + 1;
 
  if (a % 47 == b % 47)
    fout << "GO" << endl;
  else
    fout << "STAY" << endl;

  return 0;
}
