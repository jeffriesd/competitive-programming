// problem: https://open.kattis.com/problems/minorsetback

#include<bits/stdc++.h>
using namespace std;

int getA(double f) {
  return round(12 * ((log(f) - log(440.0)) / log(2.0)));
}

int main() {
  double a4 = 440.0;
  double l2 = log(2);

  int n;
  cin >> n;

  vector<bool> notes(12);
  vector<int> noteSeq;
   
  double f;
  int a;
  for (int i = 0; i < n; i++) {
    cin >> f; 

    a = getA(f);

    while (a < 0) a += 12;
    a %= 12;

    noteSeq.push_back(a);
    // cout << a << endl;
    notes[a] = true;
  }

  set<int> C = { 3, 5, 7, 8, 10, 0, 2 };
  set<int> Eb = { 6, 8, 10, 11, 1, 3, 5 };
  set<int> fs = { 9, 11, 0, 2, 4, 5, 7 };
  set<int> G = { 10, 0, 2, 3, 5, 7, 9 }; 
  set<int> g = { 10, 0, 1, 3, 5, 6, 8 }; 


  unordered_map<int, string> gnames({
    {10, "G"}, 
    {0, "A"}, 
    {1, "Bb"}, 
    {3, "C"}, 
   {5, "D"}, 
    {6, "Eb"}, 
    {8, "F"}, 
  });

  unordered_map<int, string> fsnames({
    {9, "F#"}, 
    {11, "G#"}, 
    {0, "A"}, 
    {2, "B"}, 
   {4, "C#"}, 
    {5, "D"}, 
    {7, "E"}, 
  });


  unordered_map<int, string> Ebnames({
    {6, "Eb"}, 
    {8, "F"}, 
    {10, "G"}, 
    {11, "Ab"}, 
   {1, "Bb"}, 
    {3, "C"}, 
    {5, "D"}, 
  });


  unordered_map<int, string> Gnames({
    {10, "G"}, 
    {0, "A"}, 
    {2, "B"}, 
    {3, "C"}, 
   {5, "D"}, 
    {7, "E"}, 
    {9, "F#"}, 
  });



  unordered_map<int, string> Cnames({
    {3, "C"}, 
    {5, "D"}, 
    {7, "E"}, 
    {8, "F"}, 
    {10, "G"}, 
    {0, "A"}, 
    {2, "B"}, 
  });
  
  vector<set<int>> keys = { G, C, Eb, fs, g };
  vector<string> keyNames = {"G major", "C major" , "Eb major", "F# minor", "G minor" };
  vector<unordered_map<int, string>> degNames = { Gnames, Cnames, Ebnames, fsnames, gnames };

  vector<bool> possible (5);
  for ( int k = 0; k < keys.size(); k++) {
    bool inKey = true;
    // cout << "key = " << keyNames[k] << endl;
    for (int i = 0; i < keys[k].size(); i++) {
      // are all present notes in the key?
      for (int j = 0; j < notes.size(); j++) {
        // cout << "note j = " << j  << " : " << notes[j] << endl;
        if (notes[j] && (keys[k].find(j) == keys[k].end())) {
          inKey = false;
          break;
        }
      }
      possible[k] = inKey;

      // if (inKey) {
      //   cout << "inkey " << keyNames[k] << endl;
      // }
    }  
  }

  int nump = 0;
  int pk = 0;
  for ( int k = 0; k < keys.size(); k++) {
    if (possible[k]) { 
      nump++;
      pk = k;
    }
  }

  if (nump != 1) {
    cout << "cannot determine key" << endl;
    return 0;
  }

  cout << keyNames[pk] << endl; 

  for (int n : noteSeq) {
    cout << degNames[pk][n] << endl;
  }  

  return 0;
}
