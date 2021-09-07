// problem: https://naq19.kattis.com/problems/missingnumbers 

#include<iostream>
using namespace std;
int main()
{

    int ctd[201];
    for (int i = 0; i < 201; i++)
        ctd[i] = 0;
    int max = 0;
    int t;
    cin >> t;
    while(cin >> t)
    {
        ctd[t] = 1;
        if (t > max) max = t;
    }
    bool flag = true;
    bool spacedout = false;
    for (int i = 1; i <= max; i++)
    {
        if(ctd[i] != 1)
        {
            if (spacedout) cout<<"\n";
            spacedout = true;
            cout << i;
            flag = false;
        }
    }
    if (flag) cout << "good job";
}
