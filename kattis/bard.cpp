// problem: https://open.kattis.com/problems/bard

#include<bits/stdc++.h>
#include<set>
using namespace std;

template <class A>
void unionTo(set<A> & xs, set<A> & ys) {
  for (auto it = xs.begin(); it != xs.end(); it++) {
    ys.insert(*it); 
  }  
}

int main() {
  int N;
  int E;
  int k;

  cin >> N >> E;

  vector<set<int>> villagers(N);

  int songs = 0;
  for (int i = 0; i < E; i++) {
    cin >> k;
    set<int> present;
    int x;
    // keep track of all songs known by 
    // folks in attendance
    set<int> tonightSongs;

    // keep track of indices so 
    // we can loop through these villagers
    // again after figuring out what to
    // share
    vector<int> tonightInds;

    // read present villagers
    for (int j = 0; j < k; j++) {
      cin >> x;
      x--;
      present.insert(x);
      unionTo(villagers[x], tonightSongs);
      tonightInds.push_back(x);
    }
    // cout << "night " << i << endl;
    set<int> * shared;

    // was bard present
    if (present.find(0) != present.end()) {
      songs++;
      // cout << " -- new song -- \n" << "\t " << songs << endl;
      set<int> newSong = {songs};
      //shared = &newSong;
      //

      for (int j = 0; j < k; j++) {
        unionTo(newSong, villagers[tonightInds[j]]);
      }
    }
    else {
      // cout << "-- tonight songs -- " << endl;
      // cout << "\t";
      print_vec(tonightSongs);

      // shared = &tonightSongs;
      for (int j = 0; j < k; j++) {
        unionTo(tonightSongs, villagers[tonightInds[j]]);
      }
    }
  }

  // cout << " --- ans -- \n";
  for (int i = 0; i < N; i++) {
      // cout <<  " villager " << i << " size : " << villagers[i].size() << endl;
    if (villagers[i].size() >= songs) {
      cout << (i+1) << endl;
    }
  }
  
  return 0;
}
