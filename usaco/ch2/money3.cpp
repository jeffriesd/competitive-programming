/*
ID: jeffrie1
LANG: C++
TASK: money
*/
#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

#define COINS 25
#define SUM 10000

long long S [SUM+1][COINS+1] = {{ 0 }};

int main() {
  ofstream fout ("money.out");
  ifstream fin ("money.in");

  int V, N;
  fin >> V >> N;
  int c;
  vi coins(V+1, 0);
  for (int j = 1; j <= V; j++) {
    fin >> coins[j];
  }
  
  // S[i][j] = number of ways to construct i using first j coins
  //
  // S[x][1] = 1 for x in coins
  // S[1][x] = 
  //
  //  
  // S[i][j] = S[i-coins[k]][j-1] for k < j
  //  
  // S[5][2] = ways to make 5 using only {1, 2}
  // S[5][3] = ways to make 5 using only {1,2,5}
  //            -- ways to make 
  //
  //    S[5][3] with last coin being 1
  //    S[5][3] with last coin being 2
  //    S[5][3] with last coin being 5
  //

  for (int amt = 1; amt <= N; amt++) {
    // j = number of coins to use
    for (int j = 1; j <= V; j++) {

      // make X cents with coin Y-cent coin (Y > X)
      // -- not possible -- same as previous answer
      if (amt < coins[j]) {
        S[amt][j] = S[amt][j-1]; 
        continue;
      }
  
      // try adding zero or more of coins[j] to 
      // previously constructed sums
      for (int k = 0; k*coins[j] <= amt; k++) {
        // construct amt solely from coins[j]
        if (amt - k*coins[j] == 0) 
          S[amt][j]++;
        else
          S[amt][j] += S[amt-k*coins[j]][j-1];
      }
    }
  }

  fout << S[N][V] << endl;

  return 0;
}




  // ways to construct 10 from 1, 2, 5
  //
  // S[1] = { 1 }
  // S[2] = { 1+1, 2 }
  // S[3] = { 1+2, 3 }
  // S[4] = {1 + (1+2), 1 + 3, 
  //         2 + (1+1), 2 + 2,
  //         3 + 1 } 
  //
  //    (1, 3) -- S[1] * S[3] = 2
  //    (2, 2) -- S[2] * S[2] = 
  //    (3, 1) -- don't count these
  //      
  // (5) + S[5]
  // S[5] = 
  //    (1) + S[4]
  //    S[4] = 1+
  //
  //
  // (2) + 8
  // -- 2 + 2 + 2 + 2
  // -- 1 + 




