/*
ID: jeffrie1
LANG: C++
TASK: friday
*/

#include<bits/stdc++.h>

using namespace std;

string dd(int d) {
  switch (d) {
    case 0: return "Sat";
    case 1: return "Sun";  
    case 2: return "Mon";  
    case 3: return "Tue";  
    case 4: return "Wed";  
    case 5: return "Thu";  
    case 6: return "Fri";  
  }
  return "unknown";
}

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int ny;
    fin >> ny;

    vector<int> dc (7, 0);
    // j f m A m J jl a S o N d
    vector<int> mdays = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int FEB = 1;

    // for each year
    bool leap;
    int day = 2; // starting on monday but 0 = Sat, 1 = Sun
    for (int y = 1900; y < 1900+ny; y++) {
      leap = ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);

      for (int m = 0; m < 12; m++) {
        int mds = (m == FEB && leap) ? 29 : mdays[m];
          
        for (int d = 0; d < mds; d++) {
          if (d == 12) 
            dc[day]++;
          day = (day + 1) % 7; 
        }
      }
    }

    for (int i = 0; i < dc.size() - 1; i++) 
      fout << dc[i] << " ";
    fout << dc[dc.size() - 1] << endl;


    return 0;
}
