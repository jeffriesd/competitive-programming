/*
ID: jeffrie1
LANG: C++
TASK: contact
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;
using umii = unordered_map<int, int>;

ofstream fout ("contact.out");
ifstream fin ("contact.in");

void printBits(vb &bs) {
  for (bool b : bs)
    fout << b;
}

void incr(unordered_map<vb, pi> & counts, vb &bs, int val) {
  auto p = counts.find(bs);
  if (p != counts.end()) {
    counts.erase(bs);
    counts.insert({bs, {p->second.first+ 1, val}});
  }
  else {
    counts.insert({bs, {1, val}});
  }
}

int main() {

  int A, B, N;
  fin >> A >> B >> N;

  string line;
  vb bits;
  while (fin >> line) 
    for (char &c : line) 
      bits.push_back(c == '1');

  // map bitstring to (count, numeric val)
  unordered_map<vb, pi> pats;

  int len = bits.size();
  for (int i = 0; i < len; i++) {
    int x = 0;
    // fill up binary number 
    // from left to right, e.g. if seq
    // is 
    //     1000111000
    // first 1   ... start at length A
    //       10
    //       100
    //       1000... up to length B
    //
    vb bs;
    for (int j = i ; j - i + 1 <= B && j < len; j++) {
      bs.push_back(bits[j]);

      x <<= 1;
      x |= bits[j];
      if (j - i + 1 >= A) {
        incr(pats, bs, x);
      }
    }
  }


  // print N most frequent sequences
  // need to sort based on 
  // <freq, length, num>
  // -- also store index of pattern
  
  vector<tuple<int, int, int, int>> order;
  vector<vb> patterns;
  int i = 0;
  int freq;
  for (auto p : pats) {
    patterns.push_back(p.first);
    // sort in decreasing order of freq
    freq = p.second.first;
    order.push_back({-freq, p.first.size(), p.second.second, i});
    i++;
  }

  // sort decreasing order of freq, 
  // shortest to longest length, increasing binary number, 
  sort(begin(order), end(order));
  
  set<int> freqsUsed;
  i = 1;
  int perLine = 0;
  for (auto p : order) {
    freq = get<0>(p);

    if (freqsUsed.find(freq) == end(freqsUsed)) {
      if (i > N) break;
      freqsUsed.insert(freq);
      
      if (i > 1) 
        fout << endl;
      fout << -freq << endl;
      printBits(patterns[get<3>(p)]);

      perLine = 1;
      i++;
    } 
    else {
      if (perLine == 6) {
        fout << endl;
        perLine = 0;
      }
      else
        fout << " "; 

      printBits(patterns[get<3>(p)]);
      perLine++;
    }
  }
  fout << endl;

  return 0;
}
