/*
ID: jeffrie1
LANG: C++
TASK: shopping
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;
using umii = unordered_map<int, int>;

#define MAXC 1000
#define INF 1000000

vector<unordered_map<int, int>> offers;
vi initialAmts(MAXC, 0);
vi offerPrices;
vi prices (MAXC, 0);

// return length of shortest path
int dfs(vi & state, vi & amts, int curCost) {
  if (curCost == 0) return 0;

  // cout << "visit"  << endl;
  // for (int x : amts)
  //   cout << x << " " ;
  // cout << endl;


  int c, k;
  // keep track of min dist
  int mind = INF;
  for (int oi = 0; oi < offers.size(); oi++) {
    bool extend = true;
    int remainingCost = curCost;
    for (auto p : offers[oi]) {
      // offer p consumes k units
      // of item c
      tie(c, k) = p;
      if (amts[c] < k) { 
        extend = false;
        // break;
      }
      amts[c] -= k;

      remainingCost -= k * prices[c];
    } 

    if (extend) {
      state[oi]++;
      mind = min(mind, offerPrices[oi] + dfs(state, amts, remainingCost));
      // or just short cut and purchase remaining items at normal cost
      mind = min(mind, offerPrices[oi] + remainingCost);

      // reset state
      state[oi]--;
    }
    // reset amts
    for (auto p : offers[oi]) {
      // offer p consumes k units
      // of item c
      tie(c, k) = p;
      amts[c] += k;
    } 
  }    
  return mind;
}

int main() {
  ofstream fout ("shopping.out");
  ifstream fin ("shopping.in");

  int S; 
  fin >> S;
  int n;

  int c, k, p;
  
  vector<vector<pi>> baseOffers;
  vector<vector<pi>> voffers;
  vector<vector<pi>> genOffers;
  for (int i = 0; i < S; i++) {
    fin >> n;
    unordered_map<int, int> offer;

    vector<pi> voffer;
    for (int j = 0; j < n; j++) {
      fin >> c >> k;
      offer.insert({c, k});
      voffer.push_back({c, k});
    }
    voffers.push_back(voffer);
    genOffers.push_back(voffer);
    baseOffers.push_back(voffer);

    offers.push_back(offer);
    fin >> p;
    offerPrices.push_back(p);
  }

  vi finalState;

  int B;
  fin >> B;
  vi basketCodes; // item codes present in basket
  // map basket code to index in state space
  vi codeToInd (MAXC, -1);
  for (int i = 0; i < B; i++) {
    fin >> c >> k >> p;
    prices[c] = p;
    initialAmts[c] = k;
    basketCodes.push_back(c);
    codeToInd[c] = i;
    finalState.push_back(k);

    // add 'offers' to represent regular prices
    for (int j = 1; j <= 5; j++) {
      umii offer;
      offer.insert({c, j});
      offers.push_back(offer);
      offerPrices.push_back(prices[c] * j);
    }

  }

  // undiscounted cost 
  int cost = 0;
  for (int c = 0; c < MAXC; c++)
    cost += initialAmts[c] * prices[c];
  if (S == 0) {
    fout << cost << endl;
    return 0;
  }

  // states are B-tuples
  // indicating the count of each 
  // item type in basket
    
  // queue up states in reverse topological order
  // i.e. (0,0,0,0,0) first
  // and (5,5,5,5,5) last
  //
  // do knapsack style dp i.e.
  //
  // to compute shortest path 
  // from current state, 
  // try using every possible offer to 
  // extend a previous result
  queue<vi> states;
  
  vi startState (B, 0);

  queue<vi> nextStates;
  nextStates.push(startState);

  set<vi> allStates;

  while (! nextStates.empty()) {
    vi v (begin(nextStates.front()), end(nextStates.front()));
    nextStates.pop(); 
    states.push(v); 
    allStates.insert(v);

    for (int i = 0; i < B; i++) {
      if (v[i] < 5) {
        v[i]++;
        if (allStates.find(v) == allStates.end()) {
          nextStates.push(v);
          allStates.insert(v);
        }
        v[i]--;
      }
    }
  }

  map<vi, int> dist;
  dist.insert({startState, 0});
  
  // process in reverse topological order
  states.pop();
  while (! states.empty()) {
    vi curState = states.front();
    states.pop(); 

    if (dist.find(curState) == dist.end())
      dist.insert({curState, INF});

    // try extending previous result
    // using all offers
    vi tempState (begin(curState), end(curState));
    for (int oi = 0; oi < offers.size(); oi++) {
      // update state
      for (auto p : offers[oi]) {
        tie(c, k) = p;
        tempState[codeToInd[c]] -= k;
      }
      // search with updated state
      int prevDist; 
      if (dist.find(tempState) == dist.end()) 
        prevDist = INF;
      else
        prevDist = dist.find(tempState)->second;

      // restore state for next iter
      for (auto p : offers[oi]) {
        tie(c, k) = p;
        tempState[codeToInd[c]] += k;
      }
      int curdist = dist[curState];
      if (prevDist + offerPrices[oi] < curdist) 
        dist[curState] = prevDist + offerPrices[oi];
    }
  }

  fout << dist.find(finalState)->second << endl;

  return 0;
}
