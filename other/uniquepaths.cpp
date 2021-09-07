// problem: https://leetcode.com/problems/unique-paths/

class Solution {
public:
    int uniquePaths(int m, int n) {
        int sol[n][m] = {};
        sol[0][0] = 1;
        for (int c = 0; c < m; c++)
            sol[0][c] = 1;
        for (int r = 0; r < n; r++)
            sol[r][0] = 1;
        
        for (int r = 1; r < n; r++)
            for (int c = 1; c < m; c++)
                sol[r][c] = sol[r-1][c] + sol[r][c-1];
        return sol[n-1][m-1];
    }
};
