/*
ID: jeffrie1
LANG: C++
TASK: lgame
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("lgame.out");
  ifstream fin ("lgame.in");


  // words are 3-7 chars
  //
  // input (letters) is 3-7 chars
  //
  // so the maximun number of words 
  // that can be chained is 2 in a single score

  // precompute which words are possible
  // given input letters
  //
  // then maybe n^2 is fast enough?

  string s;
  fin >> s;

  // letter scores 
  unordered_map<char, int> values;
  values['a'] = 2;
  values['b'] = 5;
  values['c'] = 4;
  values['d'] = 4;
  values['e'] = 1;
  values['f'] = 6;
  values['g'] = 5;
  values['h'] = 5;
  values['i'] = 1;
  values['j'] = 7;
  values['k'] = 6;
  values['l'] = 3;
  values['m'] = 5;
  values['n'] = 2;
  values['o'] = 3;
  values['p'] = 5;
  values['q'] = 7;
  values['r'] = 2;
  values['s'] = 1;
  values['t'] = 2;
  values['u'] = 4;
  values['v'] = 6;
  values['w'] = 6;
  values['x'] = 7;
  values['y'] = 5;
  values['z'] = 7;

  unordered_map<char, int> letters;
  for (char c = 'a'; c <= 'z'; c++)
    letters.insert({c, 0});

  char c;
  for (int i = 0; i < s.size(); i++) {
    c = s[i];
    auto p = letters.find(c);
    int count = p->second;
    letters.erase(p);
    letters.insert({c , count + 1});
  }

  ifstream dfin ("lgame.dict");
  vector<string> words;

  
  while (dfin >> s) {
    if (! s.compare("."))
      break;

    bool include = true;

    // check letter counts
    for (char c = 'a'; c <= 'z'; c++) {
      int countt = count(s.begin(), s.end(), c);
      // printf("c = %c,  count = %d  letters[c] = %d\n",c,  countt, letters[c]);
      if (countt  > letters[c]) {
       include = false; 
       break;
      }
    }

    if (include) {
      words.push_back(s);

      // cout << "insert " << s << endl;
    }
  }

  // append empty string so single string output
  // becomes special case of pair of strings

  words.push_back("");
  sort(words.begin(), words.end());

  int maxscore = -1;
  vector<pi> maxwords; 

  // try every pair of words
  for (int i = 0; i < words.size(); i++) {
    unordered_map<char, int> lts (letters);

    s = words[i];

    // cout << "s = " << s << endl;

    int score1 = 0; 

    for (char c = 'a'; c <= 'z'; c++) {
      int countt = count(s.begin(), s.end(), c);

      score1 += countt * values[c];

      lts[c] = lts[c] - countt;
    }


    for (int j = i; j < words.size(); j++) {

      int score2 = 0;
      bool include = true;

      for (char c = 'a'; c <= 'z'; c++) {
        int countt = count(words[j].begin(), words[j].end(), c);
        score2 += countt * values[c];

        if (countt > lts[c]) {
          include = false;
          break;
        }
      }

      if (include) {
        if (score1 + score2 > maxscore) {
          // cout << "Score = " << score1 + score2 << " words= " << words[i] << ", " << words[j] << endl;

          maxwords.clear();
          maxscore = score1 + score2;
        }
        // cout << "add " << i << ", " << j << endl;
        if (score1 + score2 == maxscore)
          maxwords.push_back({i, j});
      }
    }
  }


  vector<string> strs;
  for (auto p : maxwords) {
    char * s = new char[20];
    char * sp = s;

    int len; 
    const char * w1 = words[p.first].c_str();
    sp += sprintf(sp, w1);

    // fout << words[p.first];
    if (words[p.first].size()) {
      sp += sprintf(sp, " ");
      // fout << " ";
    }
    const char * w2 = words[p.second].c_str();
    sprintf(sp, w2);
    // fout << words[p.second] << endl;
    strs.push_back(string(s));
  }

  sort(strs.begin(), strs.end());

  fout << maxscore << endl;

  for (string & s : strs)
    fout << s << endl;

  return 0;
}
