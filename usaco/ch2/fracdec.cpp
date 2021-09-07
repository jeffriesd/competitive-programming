/*
ID: jeffrie1
LANG: C++
TASK: fracdec
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("fracdec.out");
  ifstream fin ("fracdec.in");

  stringstream ans;

  // - divide (add 0 to dividend)
  // - compute c = divisor // dividend
  //   add c to answer
  // - multiply 
  //    new div = c * divisor
  // - subtract
  //    dividend = dividend - new div
  //    if (dividend == 0)
  //        stop


  int N, D;
  fin >> N >> D;

  int a = 0;

  // get whole part of number
  while (N >= D) {
    a++;
    N -= D;
  }

  // integer answer
  if (N == 0) {
    fout << a << ".0" << endl;
    return 0;
  }
  ans << a << ".";

  unordered_map<int, int> visited;
  int i = 0;
  int c;
  int cycle = -1;
  vi digs;
  while (N != 0) {
    N *= 10;

    c = N / D;
    
    auto search = visited.find(N);
    if (search == end(visited))
      visited.insert({N, i});
    else {
      cycle = search->second;
      break;
    }
  
    digs.push_back(c);

    i++;
    N -= c * D;
  }
  

  for (int i = 0; i < digs.size(); i++) {
    if (i == cycle)
      ans << "(";
    ans << digs[i] ;
  }
  if (cycle >= 0)
    ans << ")";

  
  string anss = ans.str();

  // print 76-columns wide
  for (int i = 0; i < anss.size(); ) {
    for (int j = 0; j < 76 && i < anss.size(); j++, i++)
      fout << anss[i];
    fout << endl;
  }

  return 0;
}
