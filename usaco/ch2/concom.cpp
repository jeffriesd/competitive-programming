/*
ID: jeffrie1
LANG: C++
TASK: concom
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define NUM_C 100


int owns [NUM_C+1][NUM_C+1] = { { 0 } };
// bool controls [NUM_C+1][NUM_C+1] = { { false } };

int main() {
  ofstream fout ("concom.out");
  ifstream fin ("concom.in");

  int N;
  fin >> N;

  vvi controls(NUM_C+1);

  int x, y, p;
  for (int i = 1; i <= N; i++) {
    fin >> x >> y >> p;
    owns[x][y] = p;

    if (p > 50) {
      // cout << "p" << x << y << endl;
      controls[x].push_back(y);
    }
  }
  for (int i = 1; i <= NUM_C; i++)
    controls[i].push_back(i);

  // to update controls
  // to check for transitive control
  // (third option in problem description)
  // we need need to check all controls[i][j]
  // that currently = false
  //
  // controls[i][j] = true
  //  iff there are K companies controlled 
  //  by [i] s.t. 
  //
  //  sum_{j=1..K} { owns[i][x_j] } > 50
  

  // NOTE 
  // updating control does not cause
  // ownership percentages to update


  // find all pairs (h, s)
  // s.t. h controls s
  
  // S[i] = how many companies are controlled by  
  //        company i 
  //
  // S[1] -- check controls[1][-]
  //         and maintain vector v 
  //         where v[j] = % owned of company j 
  //         by companies controlled by 1
  //
  //         if v[j] > 50 for some j,
  //         set controls[1][j] and 
  //         add it to 
  






  for (int ci = 1; ci <= NUM_C; ci++) {
    vi ownedBySub (NUM_C+1, 0);
    // how much is owned by subsidiaries of company ci?
    for (int si = 0; si < controls[ci].size(); si++) {
      int sub  = controls[ci][si];
      // printf("ci = %d, sub = %d\n", ci, sub);
        
        
      // if (ci == sub) continue;
      for (int k = 1; k <= NUM_C; k++) {
        if (ci == k) continue;
        // not interested in companies already controlled by ci
        if (find(begin(controls[ci]), end(controls[ci]), k) != end(controls[ci]))
          continue;

        ownedBySub[k] += owns[sub][k];
        
        // printf("ci = %d, sub = %d, k = %d, obs[%d] = %d\n", ci, sub, k , k, ownedBySub[k]);
      
        if (ownedBySub[k] > 50) {
          controls[ci].push_back(k);
        }
      }
    }
  }


  for (int i = 1; i <= NUM_C; i++) {
    sort(begin(controls[i]), end(controls[i]));
    for (int c : controls[i]) {
      if (i == c) continue;
      fout << i << " " << c << endl;
    }
  }
  

  return 0;
}
