// problem: https://leetcode.com/problems/wildcard-matching/

class Solution {
  public:
    bool match(char s , char p) {
      if (p == '*' || p == '?') return true;
      return p == s;
    }

    bool allstars(string s) {
      for (char c : s) 
        if (c != '*') return false;
      return true;
    } 

    bool isMatch(string s, string p) {
      int ls = s.length();
      int lp = p.length();

      if (ls == 0) return lp == 0 || allstars(p);
      if (lp == 0) return false;

      int sol [lp][ls] = {};


      // fill first row 
      for (int i = 0; i < ls; i++) {
        if (p[0] == '*')
          sol[0][i] = 1;
        else if (i == 0 && match(s[0], p[0])) 
          sol[0][0] = 1;
        else
          sol[0][i] = 0;
      }

      // fill first col -- if p[i] matches s[0]
      // sol[0][0] = match(s[0], p[0]);
      bool hit = false;
      for (int i = 0; i < lp; i++) {
        if (hit) { 
          if (p[i] == '*') sol[i][0] = 1;
          else break;
        }
        else {
          if (p[i] == '?' || p[i] == s[0]) {
            sol[i][0] = 1;
            hit = true;
          }
          else if (p[i] == '*') sol[i][0] = 1;
          else break;
        }
      }

      bool m;
      for (int i = 1; i < lp; i++) {
        for (int j = 1; j < ls; j++) {
          m = match(s[j], p[i]);
          sol[i][j] = m && (sol[i-1][j-1]
              || sol[i][j-1] && p[i] == '*'
              || sol[i-1][j] && p[i] == '*');

        }
      }

      return sol[lp-1][ls-1];
    }
};

