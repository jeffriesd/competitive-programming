// problem: https://open.kattis.com/problems/uniquedice

#include<bits/stdc++.h> 
using namespace std;
  
using vi = vector<int>;

vi savedVec;

void printVec(vector<int> & v) {
  for (int i : v) cout << i << " ";
  cout << endl;
}

class Die {
  public:
    int top, bot, fr, bk, l, r;
    Die(int t, int b, int f, int bck, int left, int right) {
      top = t; 
      bot = b;
      fr = f;
      bk = bck;
      l = left;
      r = right;
    }

  bool checkRotations(map<vi, int> & ds) {
    Die d = topTop();
    for (int i = 0; i < 4; i++) {
      vi dv = { d.top, d.bot, d.fr, d.bk, d.l, d.r };
      // cout << "try "; printVec(dv);
      if (ds.find(dv) != ds.end()) { 
        savedVec = dv;
        return true;
      }
      d = d.rotLeft();
    }
    return false;
  }

  bool checkPermutations(map<vi, int> & ds) {
    return topTop().checkRotations(ds)
      || leftTop().checkRotations(ds)
      || rightTop().checkRotations(ds)
      || frontTop().checkRotations(ds)
      || backTop().checkRotations(ds)
      || botTop().checkRotations(ds);
  }

  Die topTop() {
    return Die(top, bot, fr, bk, l, r); 
  }

  Die rotLeft() {
    return Die(top, bot, l, r, bk, fr); 
  }
  
  Die leftTop() {
    return Die(l, r, fr, bk, bot, top);
  } 

  Die rightTop() {
    return Die(r, l, fr, bk, top, bot);
  } 

  Die frontTop() {
    return Die(fr, bk, bot, top, l, r);
  } 
  
  Die backTop() {
    // top bot fr bak l r
    return Die(bk, fr, top, bot, l, r);
  } 

  Die botTop() {
    return frontTop().frontTop();
  } 
};


int main() {
  int n; cin >> n;      

  int top, bot, front, back, left, right;

  map<vi, int> ds;
  int ans = 1;
  for (int i = 0 ; i < n; i++) {
    cin >> top >> bot >> front >> back >> left >> right; 
    Die d(top, bot, front, back, left, right);
    vector<int> dv ({top, bot, front, back, left, right});

    if (d.checkPermutations(ds)) {
      // cout << "saved vec  "; printVec(savedVec);
      ans = max(ans, ++ds[savedVec]);
    }
    else {
      ds.insert(make_pair(dv, 1));
    }
  }
  cout << ans << endl;

  return 0;
}
