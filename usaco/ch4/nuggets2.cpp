/*
ID: jeffrie1
LANG: C++
TASK: nuggets
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;


#define MAXSIZE 256

int main() {
  ofstream fout ("nuggets.out");
  ifstream fin ("nuggets.in");

  int N;
  fin >> N;
  int size;

  int minsize = MAXSIZE; // max possible size is 256
  vi sizes;
  for (int i = 0; i < N; i++)  {
    fin >> size;
    sizes.push_back(size);

    minsize = min(minsize, size);
  }


  // if there are minsize reachable nums in a row, 
  // then all greater nums are reachable
  // unordered_set<int> reachable;

  bitset<257> reachable; 

  // keep track of set bits (should always increase or stay the same)
  int maxcount = 0;
  int maxcountconsec = 0;

  // clear bits 
  reachable.reset();
  reachable.set(1);

  // keep track of max unreachable number
  long unreachable = 0;

  unordered_set<string> visited_states;

  // count consecutive reachable 
  int consec = 0;
  // for (long i = 1; i < 2000; i++) {
  for (long i = 1; i <= 2000000000; i++) {


    bool reached = false;
    for (int s : sizes) {
      if (reachable[s]) {
        reached = true;
        break;
      }
    }

    if (reached) {
      reachable.set(0);
      consec++;
    }
    else {
      consec = 0;

      // set max unreachable number 
      unreachable = i;
    }

    if (consec >= minsize) 
      // ALL greater NUMBERS REACHABLE
      break;

    // if count doesn't increase for > 256 
    // iterations, then it never will 
    if (reachable.count() > maxcount) {
      maxcount = reachable.count();
      maxcountconsec = 0;
    }
    else {
      maxcountconsec++;
      if (maxcountconsec > MAXSIZE) {
        fout << 0 << endl;
        return 0;
      }
    }
    // move window 
    reachable <<= 1;
  }
  fout << unreachable << endl;

  return 0;
}
