# problem: https://leetcode.com/problems/unique-paths-ii/

class Solution:
    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        R = len(obstacleGrid)
        C = len(obstacleGrid[0])
        sol = [[0] * C for _ in range(R)]

        for r in range(1, R):
            for c in range(1, C):
                sol[r][c] = -obstacleGrid[r][c]

        for r in range(0, R):
            if not obstacleGrid[r][0] and (r == 0 or sol[r-1][0] == 1):
                sol[r][0] = 1
        for c in range(0, C):
            if not obstacleGrid[0][c] and (c == 0 or sol[0][c-1] == 1):
                sol[0][c] = 1

        for r in range(1, R):
            for c in range(1, C):
                if sol[r][c] < 0:
                    continue
                sol[r][c] = max(0, sol[r-1][c]) + max(0, sol[r][c-1])

        return max(0, sol[R-1][C-1])


